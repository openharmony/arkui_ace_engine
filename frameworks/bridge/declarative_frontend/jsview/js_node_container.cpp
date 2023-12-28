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

#include <unistd.h>

#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_base_node.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/core/common/container_scope.h"
#include "frameworks/core/components_ng/pattern/node_container/node_container_model_ng.h"

namespace OHOS::Ace {
namespace {
const char* NODE_CONTAINER_ID = "nodeContainerId_";
const char* NODEPTR_OF_UINODE = "nodePtr_";
constexpr int32_t INVALID_NODE_CONTAINER_ID = -1;
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
    NodeContainerModel::GetInstance()->Create();
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    if (info.Length() < 1 || !info[0]->IsObject() || info[0]->IsNull()) {
        frameNode->RemoveChildAtIndex(0);
        frameNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto object = JSRef<JSObject>::Cast(info[0]);

    // clear the nodeContainerId_ in pre controller;
    NodeContainerModel::GetInstance()->ResetController();

    // set a function to reset the nodeContainerId_ in controller;
    auto resetFunc = [firstArg = JSWeak<JSObject>(object)]() {
        CHECK_NULL_VOID(!firstArg.IsEmpty());
        JSObject args = firstArg.Lock().Get();
        args->SetProperty(NODE_CONTAINER_ID, INVALID_NODE_CONTAINER_ID);
    };
    NodeContainerModel::GetInstance()->BindController(std::move(resetFunc));
    auto execCtx = info.GetExecutionContext();
    auto child = GetNodeByNodeController(object, execCtx);
    // set the nodeContainerId_ to nodeController
    JSObject firstArg = JSRef<JSObject>::Cast(info[0]).Get();
    firstArg->SetProperty(NODE_CONTAINER_ID, frameNode->GetId());

    if (child) {
        frameNode->RemoveChildAtIndex(0);
        frameNode->AddChild(child);
        auto pattern = frameNode->GetPattern<NG::NodeContainerPattern>();
        CHECK_NULL_VOID(pattern);
        pattern->OnAddBaseNode();
    } else {
        frameNode->RemoveChildAtIndex(0);
    }
    frameNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

RefPtr<NG::UINode> JSNodeContainer::GetNodeByNodeController(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    // get the function to makeNode
    JSRef<JSVal> jsMakeNodeFunc = object->GetProperty("makeNode");
    if (!jsMakeNodeFunc->IsFunction()) {
        return nullptr;
    }

    auto jsFunc = JSRef<JSFunc>::Cast(jsMakeNodeFunc);
    RefPtr<JsFunction> jsMake = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), jsFunc);
    NodeContainerModel::GetInstance()->SetMakeFunction([func = std::move(jsMake), execCtx]() -> RefPtr<NG::UINode> {
        JAVASCRIPT_EXECUTION_SCOPE(execCtx);
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        auto frontend = container->GetFrontend();
        CHECK_NULL_RETURN(frontend, nullptr);
        auto context = frontend->GetContextValue();
        auto jsVal = JsConverter::ConvertNapiValueToJsVal(context);
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

    auto context = GetCurrentContext();
    JSRef<JSVal> result = jsFunc->Call(object, 1, &context);
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
}

void JSNodeContainer::SetOnAppearFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto showCallback = object->GetProperty("aboutToAppear");
    CHECK_NULL_VOID(showCallback->IsFunction());
    RefPtr<JsFunction> jsAppearFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(showCallback));
    auto onAppear = [func = std::move(jsAppearFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    ViewAbstractModel::GetInstance()->SetOnAppear(onAppear);
}

void JSNodeContainer::SetOnDisappearFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto dismissCallback = object->GetProperty("aboutToDisappear");
    CHECK_NULL_VOID(dismissCallback->IsFunction());
    RefPtr<JsFunction> jsDisappearFunc =
        AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(object), JSRef<JSFunc>::Cast(dismissCallback));
    auto onDisappear = [func = std::move(jsDisappearFunc), execCtx]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        func->Execute();
    };
    ViewAbstractModel::GetInstance()->SetOnDisAppear(onDisappear);
}

void JSNodeContainer::SetOnTouchEventFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto onTouchEventCallback = object->GetProperty("onTouchEvent");
    CHECK_NULL_VOID(onTouchEventCallback->IsFunction());
    RefPtr<JsTouchFunction> jsOnTouchFunc =
        AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSFunc>::Cast(onTouchEventCallback));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onTouch = [execCtx, func = std::move(jsOnTouchFunc), node = frameNode](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    NodeContainerModel::GetInstance()->SetOnTouchEvent(std::move(onTouch));
}

void JSNodeContainer::SetOnResizeFunc(const JSRef<JSObject>& object, JsiExecutionContext execCtx)
{
    auto aboutToResize = object->GetProperty("aboutToResize");
    CHECK_NULL_VOID(aboutToResize->IsFunction());
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
    NodeContainerModel::GetInstance()->SetOnResize(onResize);
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
    JSClass<JSNodeContainer>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSNodeContainer>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSNodeContainer>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSNodeContainer>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSNodeContainer>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSNodeContainer>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);

    JSClass<JSNodeContainer>::InheritAndBind<JSViewAbstract>(globalObj);
}
} // namespace OHOS::Ace::Framework
