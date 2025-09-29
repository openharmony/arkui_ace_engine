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

namespace OHOS::Ace {
namespace {
const char* NODE_CONTAINER_ID = "_nodeContainerId";
const char* INTERNAL_FIELD_VALUE = "_value";
const char* NODEPTR_OF_UINODE = "nodePtr_";
constexpr int32_t INVALID_NODE_CONTAINER_ID = -1;

void RemoveFromNodeControllerMap(EcmaVM* vm, int32_t nodeId)
{
    auto global = JSNApi::GetGlobalObject(vm);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "__RemoveFromNodeControllerMap__");
    auto obj = global->Get(vm, funcName);
    if (obj->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> detachFunc = obj;
        auto func = panda::CopyableGlobal(vm, detachFunc);
        panda::Local<panda::JSValueRef> params[] = { panda::NumberRef::New(vm, nodeId) };
        func->Call(vm, func.ToLocal(), params, ArraySize(params));
    }
}

void BindFunc(const Framework::JSCallbackInfo& info, const RefPtr<NG::FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(!frameNode->HasOnNodeDestroyCallback());
    EcmaVM* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    auto global = JSNApi::GetGlobalObject(vm);
    auto funcName = panda::StringRef::NewFromUtf8(vm, "__RemoveFromNodeControllerMap__");
    auto obj = global->Get(vm, funcName);
    auto nodeContainerEventHub = frameNode->GetOrCreateEventHub<NG::NodeContainerEventHub>();
    auto weakEventHub = AceType::WeakClaim(AceType::RawPtr(nodeContainerEventHub));
    if (obj->IsFunction(vm)) {
        frameNode->SetOnNodeDestroyCallback([vm, weakEventHub](int32_t nodeId) {
            auto eventHub = weakEventHub.Upgrade();
            CHECK_NULL_VOID(eventHub);
            eventHub->FireOnWillUnbind(nodeId);
            RemoveFromNodeControllerMap(vm, nodeId);
            eventHub->FireOnUnbind(nodeId);
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
    EcmaVM* vm = info.GetVm();
    CHECK_NULL_VOID(vm);
    // check if it's the same object, and if it is, return it;
    auto internalField = firstArg->GetProperty(NODE_CONTAINER_ID);
    if (internalField->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(internalField);
        auto insideId = obj->GetProperty(INTERNAL_FIELD_VALUE);
        if (insideId->IsNumber()) {
            auto id = insideId->ToNumber<int32_t>();
            if (id == nodeContainerId) {
                return;
            } else if (id != INVALID_NODE_CONTAINER_ID) {
                JSNodeContainer::FireOnWillUnbind(nodeContainerId);
                RemoveFromNodeControllerMap(vm, id);
                JSNodeContainer::FireOnUnbind(nodeContainerId);
            }
        }
    }
    // clear the _nodeContainerId in pre controller;
    nodeContainerModelInstance->ResetController();

    BindFunc(info, AceType::Claim(frameNode));
    // set a function to reset the _nodeContainerId in controller;
    auto resetFunc = [firstArg = JSWeak<JSObject>(object), nodeContainerId, vm]() {
        JSNodeContainer::ResetNodeContainerId(firstArg, nodeContainerId, vm);
    };
    nodeContainerModelInstance->BindController(std::move(resetFunc));
    auto execCtx = info.GetExecutionContext();

    SetNodeController(object, execCtx);
    JSNodeContainer::FireOnWillBind(nodeContainerId);
    AddToNodeControllerMap(vm, nodeContainerId, object);
    // set the _nodeContainerId to nodeController
    if (internalField->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(internalField);
        obj->SetProperty(INTERNAL_FIELD_VALUE, nodeContainerId);
    }
    JSNodeContainer::FireOnBind(nodeContainerId);
    nodeContainerModelInstance->FireMakeNode();
}

void JSNodeContainer::ResetNodeContainerId(const JSWeak<JSObject>& firstArg, int32_t nodeContainerId, EcmaVM* vm)
{
    CHECK_NULL_VOID(!firstArg.IsEmpty());
    JSObject args = firstArg.Lock().Get();
    auto internalField = args->GetProperty(NODE_CONTAINER_ID);
    CHECK_NULL_VOID(internalField->IsObject());
    auto obj = JSRef<JSObject>::Cast(internalField);
    auto insideId = obj->GetProperty(INTERNAL_FIELD_VALUE);
    if (insideId->IsNumber()) {
        auto id = insideId->ToNumber<int32_t>();
        if (id != nodeContainerId) {
            return;
        }
    }
    JSNodeContainer::FireOnWillUnbind(nodeContainerId);
    RemoveFromNodeControllerMap(vm, nodeContainerId);
    obj->SetProperty(INTERNAL_FIELD_VALUE, INVALID_NODE_CONTAINER_ID);
    JSNodeContainer::FireOnUnbind(nodeContainerId);
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
    SetOnAttachFunc(object, execCtx);
    SetOnDetachFunc(object, execCtx);
    SetOnWillBindFunc(object, execCtx);
    SetOnWillUnbindFunc(object, execCtx);
    SetOnBindFunc(object, execCtx);
    SetOnUnbindFunc(object, execCtx);
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
    nodeContainerModelInstance->SetOnWillBind(nullptr);
    nodeContainerModelInstance->SetOnWillUnbind(nullptr);
    nodeContainerModelInstance->SetOnBind(nullptr);
    nodeContainerModelInstance->SetOnUnbind(nullptr);
    nodeContainerModelInstance->SetOnAttach(nullptr);
    nodeContainerModelInstance->SetOnDetach(nullptr);
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

void JSNodeContainer::SetOnAttachFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto showCallback = object->GetProperty("onAttach");
    CHECK_NULL_VOID(showCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsAttachFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(showCallback));
    auto onAttach = [func = std::move(jsAttachFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    nodeContainerModelInstance->SetOnAttach(onAttach);
}

void JSNodeContainer::SetOnDetachFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto dismissCallback = object->GetProperty("onDetach");
    CHECK_NULL_VOID(dismissCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsDetachFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(dismissCallback));
    auto onDetach = [func = std::move(jsDetachFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    nodeContainerModelInstance->SetOnDetach(onDetach);
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

void JSNodeContainer::SetOnWillBindFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onWillBindCallback = object->GetProperty("onWillBind");
    CHECK_NULL_VOID(onWillBindCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsOnWillBindFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(onWillBindCallback));
    auto onWillBind = [execCtx, func = std::move(jsOnWillBindFunc)](int32_t containerId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> nodeContainerIndex = JSRef<JSVal>::Make(ToJSValue(containerId));
        func->ExecuteJS(1, &nodeContainerIndex);
    };
    nodeContainerModelInstance->SetOnWillBind(std::move(onWillBind));
}

void JSNodeContainer::SetOnWillUnbindFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onWillUnbindCallback = object->GetProperty("onWillUnbind");
    CHECK_NULL_VOID(onWillUnbindCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsOnWillUnbindFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(onWillUnbindCallback));
    auto onWillUnbind = [execCtx, func = std::move(jsOnWillUnbindFunc)](int32_t containerId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> nodeContainerIndex = JSRef<JSVal>::Make(ToJSValue(containerId));
        func->ExecuteJS(1, &nodeContainerIndex);
    };
    nodeContainerModelInstance->SetOnWillUnbind(std::move(onWillUnbind));
}

void JSNodeContainer::SetOnBindFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onBindCallback = object->GetProperty("onBind");
    CHECK_NULL_VOID(onBindCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsOnBindFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(onBindCallback));
    auto onBind = [execCtx, func = std::move(jsOnBindFunc)](int32_t containerId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> nodeContainerIndex = JSRef<JSVal>::Make(ToJSValue(containerId));
        func->ExecuteJS(1, &nodeContainerIndex);
    };
    nodeContainerModelInstance->SetOnBind(std::move(onBind));
}

void JSNodeContainer::SetOnUnbindFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onUnbindCallback = object->GetProperty("onUnbind");
    CHECK_NULL_VOID(onUnbindCallback->IsFunction());
    NodeContainerModel* nodeContainerModelInstance = NodeContainerModel::GetInstance();
    CHECK_NULL_VOID(nodeContainerModelInstance);
    RefPtr<JsFunction> jsOnUnbindFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(onUnbindCallback));
    auto onUnbind = [execCtx, func = std::move(jsOnUnbindFunc)](int32_t containerId) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        JSRef<JSVal> nodeContainerIndex = JSRef<JSVal>::Make(ToJSValue(containerId));
        func->ExecuteJS(1, &nodeContainerIndex);
    };
    nodeContainerModelInstance->SetOnUnbind(std::move(onUnbind));
}

RefPtr<NG::NodeContainerPattern> JSNodeContainer::GetNodeContainerPattern(int32_t containerId)
{
    auto uiNode = ElementRegister::GetInstance()->GetUINodeById(containerId);
    if (!uiNode) {
        return nullptr;
    }
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        auto frameNode = AceType::DynamicCast<NG::FrameNode>(uiNode);
        if (frameNode) {
            return frameNode->GetPattern<NG::NodeContainerPattern>();
        }
    }
    return nullptr;
}

void JSNodeContainer::FireOnWillBind(int32_t containerId)
{
    auto nodeContainerPattern = JSNodeContainer::GetNodeContainerPattern(containerId);
    if (nodeContainerPattern) {
        nodeContainerPattern->FireOnWillBind(containerId);
    }
}

void JSNodeContainer::FireOnWillUnbind(int32_t containerId)
{
    auto nodeContainerPattern = JSNodeContainer::GetNodeContainerPattern(containerId);
    if (nodeContainerPattern) {
        nodeContainerPattern->FireOnWillUnbind(containerId);
    }
}

void JSNodeContainer::FireOnBind(int32_t containerId)
{
    auto nodeContainerPattern = JSNodeContainer::GetNodeContainerPattern(containerId);
    if (nodeContainerPattern) {
        nodeContainerPattern->FireOnBind(containerId);
    }
}

void JSNodeContainer::FireOnUnbind(int32_t containerId)
{
    auto nodeContainerPattern = JSNodeContainer::GetNodeContainerPattern(containerId);
    if (nodeContainerPattern) {
        nodeContainerPattern->FireOnUnbind(containerId);
    }
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
