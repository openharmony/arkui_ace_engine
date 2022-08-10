/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/components_ng/base/view_abstract.h"
#include "core/gestures/click_recognizer.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_click_function.h"

namespace OHOS::Ace::Framework {

void JSInteractableView::JsOnTouch(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnTouch");

    if (!args[0]->IsFunction()) {
        LOGW("the info is not touch function");
        return;
    }

    RefPtr<JsTouchFunction> jsOnTouchFunc = AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onTouch = [execCtx = args.GetExecutionContext(), func = std::move(jsOnTouchFunc)](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onTouch");
        func->Execute(info);
    };
    NG::ViewAbstract::SetOnTouch(std::move(onTouch));
}

void JSInteractableView::JsOnKey(const JSCallbackInfo& args) {}

void JSInteractableView::JsOnHover(const JSCallbackInfo& args) {}

void JSInteractableView::JsOnPan(const JSCallbackInfo& args) {}

void JSInteractableView::JsOnDelete(const JSCallbackInfo& info) {}

void JSInteractableView::JsTouchable(const JSCallbackInfo& info) {}

void JSInteractableView::JsOnClick(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGW("the info is not click function");
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onClick = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc)](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };
    NG::ViewAbstract::SetOnClick(std::move(onClick));
}

EventMarker JSInteractableView::GetClickEventMarker(const JSCallbackInfo& info)
{
    return EventMarker();
}

RefPtr<Gesture> JSInteractableView::GetTapGesture(const JSCallbackInfo& info, int32_t countNum, int32_t fingerNum)
{
    return nullptr;
}

RefPtr<Gesture> JSInteractableView::GetRemoteMessageTapGesture(const JSCallbackInfo& info) {}

void JSInteractableView::SetFocusable(bool focusable) {}

void JSInteractableView::SetFocusNode(bool isFocusNode) {}

void JSInteractableView::JsOnAppear(const JSCallbackInfo& info) {}

void JSInteractableView::JsOnDisAppear(const JSCallbackInfo& info) {}

void JSInteractableView::JsOnAccessibility(const JSCallbackInfo& info) {}

void JSInteractableView::UpdateEventTarget(NodeId id, BaseEventInfo& info) {}

EventMarker JSInteractableView::GetEventMarker(const JSCallbackInfo& info, const std::vector<std::string>& keys)
{
    return EventMarker();
}

void JSInteractableView::JsCommonRemoteMessage(const JSCallbackInfo& info) {}

void JSInteractableView::JsRemoteMessage(const JSCallbackInfo& info, EventMarker& eventMarker) {}

std::function<void()> JSInteractableView::GetRemoteMessageEventCallback(const JSCallbackInfo& info)
{
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto actionValue = obj->GetProperty("action");
    std::string action;
    if (actionValue->IsString()) {
        action = actionValue->ToString();
    }
    auto abilityValue = obj->GetProperty("ability");
    std::string ability;
    if (abilityValue->IsString()) {
        ability = abilityValue->ToString();
    }
    auto paramsObj = obj->GetProperty("params");
    std::string params;
    if (paramsObj->IsObject()) {
        params = paramsObj->ToString();
    }
    auto eventCallback = [action, ability, params]() {
        LOGE("JSInteractableView::JsRemoteMessage. eventMarker");
        if (action.compare("message") == 0) {
            // onCall
        } else if (action.compare("route") == 0) {
            // startAbility
            LOGE("JSInteractableView::JsRemoteMessage: Unsupported Windows and Mac platforms to start APP.");
        } else {
            LOGE("action's name is not message or route.");
        }
    };

    return eventCallback;
}

} // namespace OHOS::Ace::Framework
