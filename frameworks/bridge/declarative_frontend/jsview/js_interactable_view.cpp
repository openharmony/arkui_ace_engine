/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/gestures/click_recognizer.h"
#include "core/pipeline/base/single_child.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_touch_handler.h"
#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSInteractableView::JsOnTouch(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnTouch");
    if (args[0]->IsFunction()) {
        auto nodeId = ViewStackProcessor::GetInstance()->GetCurrentInspectorNodeId();
        RefPtr<JsTouchFunction> jsOnTouchFunc = AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onTouchId = EventMarker(
            [execCtx = args.GetExecutionContext(), func = std::move(jsOnTouchFunc), nodeId](BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                UpdateEventTarget(nodeId, *info);
                auto touchInfo = TypeInfoHelper::DynamicCast<TouchEventInfo>(info);
                func->Execute(*touchInfo);
            },
            "onTouch");
        auto touchComponent = ViewStackProcessor::GetInstance()->GetTouchListenerComponent();
        touchComponent->SetOnTouchId(onTouchId);
    }
}

void JSInteractableView::JsOnKey(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsKeyFunction> jsOnKeyFunc = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onKeyId = EventMarker(
            [execCtx = args.GetExecutionContext(), func = std::move(jsOnKeyFunc)](BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                auto keyInfo = TypeInfoHelper::DynamicCast<KeyEventInfo>(info);
                func->Execute(*keyInfo);
            },
            "onKey", 0);
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        focusableComponent->SetFocusable(true);
        focusableComponent->SetOnKeyId(onKeyId);
    }
}

void JSInteractableView::JsOnHover(const JSCallbackInfo& args)
{
    if (args[0]->IsFunction()) {
        RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(args[0]));
        auto onHoverId = [execCtx = args.GetExecutionContext(), func = std::move(jsOnHoverFunc)](bool info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(info);
        };
        auto mouseComponent = ViewStackProcessor::GetInstance()->GetMouseListenerComponent();
        mouseComponent->SetOnHoverId(onHoverId);
    }
}

void JSInteractableView::JsOnPan(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnPan");
    if (args[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSPanHandler* handler = obj->Unwrap<JSPanHandler>();
        if (handler) {
            handler->CreateComponent(args);
        }
    }
}

void JSInteractableView::JsOnDelete(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnDelete");
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDeleteFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));
        auto onDeleteId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsOnDeleteFunc)]() {
            LOGD("onDelete callback");
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute();
        });
        auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
        focusableComponent->SetOnDeleteId(onDeleteId);
    }
}

void JSInteractableView::JsTouchable(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        auto mainComponent = ViewStackProcessor::GetInstance()->GetMainComponent();
        if (!mainComponent) {
            return;
        }
        mainComponent->SetTouchable(info[0]->ToBoolean());
    }
}

void JSInteractableView::JsOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto click = ViewStackProcessor::GetInstance()->GetBoxComponent();
        click->SetOnClick(GetTapGesture(info));
    }
}

EventMarker JSInteractableView::GetClickEventMarker(const JSCallbackInfo& info)
{
    auto nodeId = ViewStackProcessor::GetInstance()->GetCurrentInspectorNodeId();
    RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onClickId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), nodeId]
        (const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        auto clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
        auto newInfo = *clickInfo;
        UpdateEventTarget(nodeId, newInfo);
        func->Execute(newInfo);
    });
    return onClickId;
}

RefPtr<Gesture> JSInteractableView::GetTapGesture(const JSCallbackInfo& info)
{
    auto nodeId = ViewStackProcessor::GetInstance()->GetCurrentInspectorNodeId();
    RefPtr<Gesture> tapGesture = AceType::MakeRefPtr<TapGesture>();
    RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    tapGesture->SetOnActionId([execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), nodeId]
        (GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        UpdateEventTarget(nodeId, info);
        func->Execute(info);
    });
    return tapGesture;
}

void JSInteractableView::SetFocusable(bool focusable)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent();
    if (focusableComponent) {
        focusableComponent->SetFocusable(focusable);
    }
}
void JSInteractableView::SetFocusNode(bool isFocusNode)
{
    auto focusableComponent = ViewStackProcessor::GetInstance()->GetFocusableComponent(false);
    if (focusableComponent) {
        focusableComponent->SetFocusNode(!isFocusNode);
    }
}

void JSInteractableView::JsOnAppear(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(),
            JSRef<JSFunc>::Cast(info[0]));

        auto onAppearId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGI("About to call JsOnAppear method on js");
            func->Execute();
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        component->SetOnAppearEventId(onAppearId);
    }
}

void JSInteractableView::JsOnDisAppear(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onDisAppearId = EventMarker([execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGD("Start to call JsOnDisAppear method on js");
            func->Execute();
        });
        auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
        component->SetOnDisappearEventId(onDisAppearId);
    }
}

void JSInteractableView::JsOnAccessibility(const JSCallbackInfo& info)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    if (!component) {
        return;
    }

    int32_t inspectorId = StringUtils::StringToInt(component->GetInspectorId());
    auto accessibilityNode = JSViewAbstract::GetAccessibilityNodeById(inspectorId);
    if (accessibilityNode) {
        std::vector<std::string> keys = { "eventType" };
        accessibilityNode->SetFocusChangeEventMarker(GetEventMarker(info, keys));
    }
}

void JSInteractableView::UpdateEventTarget(NodeId id, BaseEventInfo& info)
{
    auto container = Container::Current();
    if (!container) {
        LOGE("fail to get container");
        return;
    }
    auto context = container->GetPipelineContext();
    if (!context) {
        LOGE("fail to get context");
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("fail to get accessibility manager");
        return;
    }
    accessibilityManager->UpdateEventTarget(id, info);
}

EventMarker JSInteractableView::GetEventMarker(const JSCallbackInfo& info, const std::vector<std::string>& keys)
{
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return EventMarker();
    }

    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto eventMarker = EventMarker(
        [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), keys](const std::string& param) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            func->Execute(keys, param);
        });
    return eventMarker;
}

} // namespace OHOS::Ace::Framework
