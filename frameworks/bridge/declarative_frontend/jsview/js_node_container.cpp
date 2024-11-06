/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "bridge/declarative_frontend/jsview/js_node_container.h"

#include <functional>
#include <mutex>
#include <unistd.h>

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/ui_context_helper.h"
#include "bridge/declarative_frontend/jsview/js_base_node.h"
#include "core/common/container_scope.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/node_container/node_container_model_ng.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"

namespace OHOS::Ace {
namespace {
const char* NODE_CONTAINER_ID = "_nodeContainerId";
const char* INTERNAL_FIELD_VALUE = "_value";
const char* NODEPTR_OF_UINODE = "nodePtr_";
constexpr int32_t INVALID_NODE_CONTAINER_ID = -1;

void BindFunc(const Framework::JSCallbackInfo& info, const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(!frameNode->HasOnNodeDestroyCallback());
    EcmaVM* vm = info.GetVm();
    auto global = JSNApi::GetGlobalObject(vm);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "__RemoveFromNodeControllerMap__");
    auto obj = global->Get(vm, funcName);
    if (obj->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> detachFunc = obj;
        frameNode->SetOnNodeDestroyCallback([vm, func = panda::CopyableGlobal(vm, detachFunc)](int32_t nodeId) {
            panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, nodeId) };
            func->Call(vm, func.ToLocal(), params, ArraySize(params));
        });
    }
}

void AddToNodeControllerMap(EcmaVM* vm, int32_t nodeId, const Framework::JSRef<Framework::JSObject>& object)
{
    auto global = JSNApi::GetGlobalObject(vm);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "__AddToNodeControllerMap__");
    auto obj = global->Get(vm, funcName);
    if (obj->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> attachFunc = obj;
        panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, nodeId),
            panda::CopyableGlobal(vm, object->GetLocalHandle()).ToLocal() };
        attachFunc->Call(vm, attachFunc, params, ArraySize(params));
    }
}
} // namespace

std::unique_ptr<NodeContainerModel> NodeContainerModel::instance_;
std::mutex NodeContainerModel::mutex_;

NodeContainerModel* NodeContainerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::NodeContainerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::NodeContainerModelNG());
            } else {
                LOGE("NodeContainerModelNG is not supported in OldPipeline.");
                return nullptr;
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSNodeContainer::Create(const JSCallbackInfo& info)
{
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    nodeContainerModelInstance->Create();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (info.Length() < 1 || !info[0]->IsObject() || info[0]->IsNull()) {
        frameNode->RemoveChildAtIndex(0);
        frameNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        ResetNodeController();
        return;
    }
    auto object = JSRef<JSObject>::Cast(info[0]);

    JSObject firstArg = JSRef<JSObject>::Cast(info[0]).Get();
    auto nodeContainerId = frameNode->GetId();
    // check if it's the same object, and if it is, return it;
    auto internalField = firstArg->GetProperty(NODE_CONTAINER_ID);
    if (internalField->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(internalField);
        auto insideId = obj->GetProperty(INTERNAL_FIELD_VALUE);
        if (insideId->IsNumber()) {
            auto id = insideId->ToNumber<int32_t>();
            if (id == nodeContainerId) {
                return;
            }
        }
    }
    // clear the _nodeContainerId in pre controller;
    nodeContainerModelInstance->ResetController();

    BindFunc(info, AceType::Claim(frameNode));
    AddToNodeControllerMap(info.GetVm(), frameNode->GetId(), object);
    // set a function to reset the _nodeContainerId in controller;
    auto resetFunc = [firstArg = JSWeak<JSObject>(object)]() {
        CHECK_NULL_VOID(!firstArg.IsEmpty());
        JSObject args = firstArg.Lock().Get();
        auto internalField = args->GetProperty(NODE_CONTAINER_ID);
        CHECK_NULL_VOID(internalField->IsObject());
        auto obj = JSRef<JSObject>::Cast(internalField);
        obj->SetProperty(INTERNAL_FIELD_VALUE, INVALID_NODE_CONTAINER_ID);
    };
    nodeContainerModelInstance->BindController(std::move(resetFunc));
    auto execCtx = info.GetExecutionContext();

    SetNodeController(object, execCtx);
    // set the _nodeContainerId to nodeController
    if (internalField->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(internalField);
        obj->SetProperty(INTERNAL_FIELD_VALUE, nodeContainerId);
    }
    nodeContainerModelInstance->FireMakeNode();
}

void JSNodeContainer::SetNodeController(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    // get the function to makeNode
    JSRef<JSVal> jsMakeNodeFunc = object->GetProperty("__makeNode__");
    if (!jsMakeNodeFunc->IsFunction()) {
        ResetNodeController();
        return;
    }
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);

    auto jsFunc = JSRef<JSFunc>::Cast(jsMakeNodeFunc);
    auto containerId = Container::CurrentId();
    RefPtr<JsFunction> jsMake = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), jsFunc);
    nodeContainerModelInstance->SetMakeFunction(
        [func = std::move(jsMake), containerId, execCtx]() -> RefPtr<NG::UINode> {
            JAVASCRIPT_EXECUTION_SCOPE(execCtx);
            ContainerScope scope(containerId);
            panda::Local<panda::JSValueRef> uiContext = NG::UIContextHelper::GetUIContext(execCtx.vm_, containerId);
            auto jsVal = JSRef<JSVal>::Make(uiContext);
            JSRef<JSVal> result = func->ExecuteJS(1, &jsVal);
            if (result.IsEmpty() || !result->IsObject()) {
                return nullptr;
            }
            JSRef<JSObject> obj = JSRef<JSObject>::Cast(result);
            JSRef<JSVal> nodeptr = obj->GetProperty(NODEPTR_OF_UINODE);
            if (nodeptr.IsEmpty()) {
                return nullptr;
            }
            const auto* vm = nodeptr->GetEcmaVM();
            auto* node = nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value();
            auto* uiNode = reinterpret_cast<NG::UINode*>(node);
            CHECK_NULL_RETURN(uiNode, nullptr);
            return AceType::Claim(uiNode);
        });

    SetOnAppearFunc(object, execCtx);
    SetOnDisappearFunc(object, execCtx);
    SetOnResizeFunc(object, execCtx);
    SetOnTouchEventFunc(object, execCtx);
}

void JSNodeContainer::ResetNodeController()
{
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    nodeContainerModelInstance->ResetController();
    nodeContainerModelInstance->SetMakeFunction(nullptr);
    nodeContainerModelInstance->SetOnTouchEvent(nullptr);
    nodeContainerModelInstance->SetOnResize(nullptr);
    nodeContainerModelInstance->SetOnAppear(nullptr);
    nodeContainerModelInstance->SetOnDisAppear(nullptr);
    ViewAbstractModel::GetInstance()->SetOnAttach(nullptr);
    ViewAbstractModel::GetInstance()->SetOnDetach(nullptr);
}

void JSNodeContainer::SetOnAppearFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto showCallback = object->GetProperty("aboutToAppear");
    CHECK_NULL_VOID(showCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsAppearFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(showCallback));
    auto onAppear = [func = std::move(jsAppearFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    nodeContainerModelInstance->SetOnAppear(onAppear);
}

void JSNodeContainer::SetOnDisappearFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto dismissCallback = object->GetProperty("aboutToDisappear");
    CHECK_NULL_VOID(dismissCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsDisappearFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(dismissCallback));
    auto onDisappear = [func = std::move(jsDisappearFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    nodeContainerModelInstance->SetOnDisAppear(onDisappear);
}

void JSNodeContainer::SetOnTouchEventFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onTouchEventCallback = object->GetProperty("onTouchEvent");
    CHECK_NULL_VOID(onTouchEventCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsTouchFunction> jsOnTouchFunc =
        AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(onTouchEventCallback));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTouch = [execCtx, func = std::move(jsOnTouchFunc), node = frameNode](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    nodeContainerModelInstance->SetOnTouchEvent(std::move(onTouch));
}

void JSNodeContainer::SetOnResizeFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto aboutToResize = object->GetProperty("aboutToResize");
    CHECK_NULL_VOID(aboutToResize->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsAboutToResizeFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(aboutToResize));
    auto onResize = [func = std::move(jsAboutToResizeFunc), execCtx](const NG::SizeF& size) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSObjTemplate> objectTemplate = JSRef<JSObjTemplate>::New();
        objectTemplate->SetInternalFieldCount(1);
        JSRef<JSObject> obj = objectTemplate->NewInstance();
        obj->SetProperty<double>("width", PipelineBase::Px2VpWithCurrentDensity(size.Width()));
        obj->SetProperty<double>("height", PipelineBase::Px2VpWithCurrentDensity(size.Height()));
        JSRef<JSVal> param = JSRef<JSVal>::Cast(obj);
        func->ExecuteJS(1, &param);
    };
    nodeContainerModelInstance->SetOnResize(onResize);
}

JSRef<JSVal> JSNodeContainer::GetCurrentContext()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, JSRef<JSVal>());
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, JSRef<JSVal>());
    auto context = frontend->GetContextValue();
    auto jsVal = JsConverter::ConvertNapiValueToJsVal(context);
    return jsVal;
}

void JSNodeContainer::JSBind(BindingTarget globalObj)
{
    JSClass<JSNodeContainer>::Declare("NodeContainer");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSNodeContainer>::StaticMethod("create", &JSNodeContainer::Create, opt);
    JSClass<JSNodeContainer>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSNodeContainer>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNodeContainer>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSNodeContainer>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNodeContainer>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNodeContainer>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSNodeContainer>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSNodeContainer>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);

    JSClass<JSNodeContainer>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
