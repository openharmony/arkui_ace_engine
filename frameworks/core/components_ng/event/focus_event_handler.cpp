/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "focus_event_handler.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_constants.h"
#include "core/components/theme/app_theme.h"
#include "core/event/focus_axis_event.h"
#include "core/event/key_event.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/event/crown_event.h"
namespace OHOS::Ace::NG {
FocusIntension FocusEvent::GetFocusIntension(const NonPointerEvent& event)
{
    if (event.eventType != UIInputEventType::KEY) {
        return FocusIntension::NONE;
    }
    const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event);
    if (keyEvent.isPreIme || keyEvent.action != KeyAction::DOWN) {
        return FocusIntension::NONE;
    }
    // Arrow key event is used to trasfer focus regardless of its pressed keys
    switch (keyEvent.code) {
        case KeyCode::KEY_DPAD_UP:
            return FocusIntension::UP;
        case KeyCode::KEY_DPAD_DOWN:
            return FocusIntension::DOWN;
        case KeyCode::KEY_DPAD_LEFT:
            return FocusIntension::LEFT;
        case KeyCode::KEY_DPAD_RIGHT:
            return FocusIntension::RIGHT;
        default:;
    }

    if (keyEvent.pressedCodes.size() != 1) {
        return keyEvent.IsExactlyShiftWith(KeyCode::KEY_TAB) ? FocusIntension::SHIFT_TAB : FocusIntension::NONE;
    }
    switch (keyEvent.code) {
        case KeyCode::KEY_TAB:
            return FocusIntension::TAB;
        case KeyCode::KEY_MOVE_HOME:
            return FocusIntension::HOME;
        case KeyCode::KEY_MOVE_END:
            return FocusIntension::END;
        case KeyCode::KEY_ENTER:
        case KeyCode::KEY_NUMPAD_ENTER:
            return FocusIntension::SELECT;
        case KeyCode::KEY_SPACE:
            return FocusIntension::SPACE;
        default:;
    }
    return GetFocusIntensionFromKey(keyEvent.keyIntention);
}

FocusIntension FocusEvent::GetFocusIntensionFromKey(KeyIntention keyIntention)
{
    switch (keyIntention) {
        case KeyIntention::INTENTION_SELECT:
            return FocusIntension::SELECT;
        case KeyIntention::INTENTION_ESCAPE:
            return FocusIntension::ESC;
        case KeyIntention::INTENTION_HOME:
            return FocusIntension::HOME;
        default:;
            return FocusIntension::NONE;
    }
}

bool FocusEventHandler::HasCustomKeyEventDispatch(const FocusEvent& event)
{
    if (event.event.eventType != UIInputEventType::KEY) {
        return false;
    }
    const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event.event);
    if (keyEvent.isPreIme) {
        return false;
    }
    return GetOnKeyEventDispatchCallback() != nullptr;
}

bool FocusEventHandler::HandleCustomEventDispatch(const FocusEvent& event)
{
    auto onKeyEventDispatchCallback = GetOnKeyEventDispatchCallback();
    if (onKeyEventDispatchCallback) {
        const KeyEvent& keyEvent = static_cast<const KeyEvent&>(event.event);
        auto info = KeyEventInfo(keyEvent);
        return onKeyEventDispatchCallback(info);
    }
    return false;
}

bool FocusEventHandler::OnFocusEvent(const FocusEvent& event)
{
    if (!IsCurrentFocus()) {
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "node: %{public}s/%{public}d cannot handle key event because is not current focus",
            GetFrameName().c_str(), GetFrameId());
        return false;
    }

    if (HasCustomKeyEventDispatch(event)) {
        return HandleCustomEventDispatch(event);
    }

    if (focusType_ == FocusType::SCOPE) {
        return OnFocusEventScope(event);
    }
    if (focusType_ == FocusType::NODE) {
        return OnFocusEventNode(event);
    }
    TAG_LOGW(AceLogTag::ACE_FOCUS, "Current node focus type: %{public}d is invalid.", focusType_);
    return false;
}

bool FocusEventHandler::OnFocusEventScope(const FocusEvent& event)
{
    ACE_DCHECK(IsCurrentFocus());
    auto lastFocusNode = lastWeakFocusNode_.Upgrade();
    if (lastFocusNode && lastFocusNode->OnFocusEvent(event)) {
        TAG_LOGD(AceLogTag::ACE_FOCUS,
            "OnKeyEvent: Node %{public}s/%{public}d will not handle Event(type:%{private}d). "
            "Because its child %{public}s/%{public}d already has consumed this event.",
            GetFrameName().c_str(), GetFrameId(), event.event.eventType, lastFocusNode->GetFrameName().c_str(),
            lastFocusNode->GetFrameId());
        return true;
    }
    return OnFocusEventNode(event);
}

bool FocusEventHandler::OnFocusEventNode(const FocusEvent& focusEvent)
{
    ACE_DCHECK(IsCurrentFocus());

    bool ret = false;
    if (focusEvent.event.eventType == UIInputEventType::KEY) {
        const KeyEvent& keyEvent = static_cast<const KeyEvent&>(focusEvent.event);
        ret = HandleKeyEvent(keyEvent, focusEvent.intension);
    }
    if (focusEvent.event.eventType == UIInputEventType::FOCUS_AXIS) {
        const FocusAxisEvent& focusAxisEvent = static_cast<const FocusAxisEvent&>(focusEvent.event);
        return HandleFocusAxisEvent(focusAxisEvent);
    }
    if (focusEvent.event.eventType == UIInputEventType::CROWN) {
        const CrownEvent& crownEvent = static_cast<const CrownEvent&>(focusEvent.event);
        return HandleCrownEvent(crownEvent);
    }

    auto keyProcessingMode = static_cast<KeyProcessingMode>(GetKeyProcessingMode());
    if (keyProcessingMode == KeyProcessingMode::ANCESTOR_EVENT) {
        return ret;
    }
    return ret ? true : HandleFocusTravel(focusEvent);
}

int32_t FocusEventHandler::GetKeyProcessingMode()
{
    auto frameNode = GetFrameNode();
    CHECK_NULL_RETURN(frameNode, static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION));
    auto context = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(context, static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION));
    auto focusManager = context->GetOrCreateFocusManager();
    CHECK_NULL_RETURN(focusManager, static_cast<int32_t>(KeyProcessingMode::FOCUS_NAVIGATION));
    return static_cast<int32_t>(focusManager->GetKeyProcessingMode());
}

bool FocusEventHandler::HandleKeyEvent(const KeyEvent& event, FocusIntension intension)
{
    // ReDispatch event will not be consumed again.
    if (event.isRedispatch) {
        return false;
    }

    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto info = KeyEventInfo(event);
    if (event.HasKey(KeyCode::KEY_META_LEFT) || event.HasKey(KeyCode::KEY_META_RIGHT)) {
        info.SetMetaKey(1);
    }
    if (event.isPreIme) {
        return OnKeyPreIme(info, event);
    }

    bool retInternal = OnKeyEventNodeInternal(event);
    bool retCallback = OnKeyEventNodeUser(info, event);
    if (retInternal || retCallback) {
        return true;
    }
    // Handle on click
    auto appTheme = pipeline->GetTheme<AppTheme>();
    CHECK_NULL_RETURN(appTheme, false);
    if (!pipeline->GetIsFocusActive() && (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) ||
                                             !appTheme->NeedFocusHandleClick())) {
        return false;
    }
    if (intension == FocusIntension::SELECT && !IsTabStop()) {
        intension = FocusIntension::SPACE;
    }
    auto ret = false;
    if (intension == FocusIntension::SPACE) {
        ret = OnClick(event);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnClick: Node %{public}s/%{public}d handle KeyEvent("
            SEC_PLD(%{private}d) ", %{public}d) return: %{public}d",
            GetFrameName().c_str(), GetFrameId(), SEC_PARAM(event.code), event.action, ret);
    }
    return ret;
}

bool FocusEventHandler::HandleFocusAxisEvent(const FocusAxisEvent& event)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto onFocusAxisCallback = GetOnFocusAxisCallback();
    CHECK_NULL_RETURN(onFocusAxisCallback, false);
    auto info = FocusAxisEventInfo(event);
    auto eventHub = node->GetOrCreateEventHub<EventHub>();
    if (eventHub) {
        auto targetImpl = eventHub->CreateGetEventTargetImpl();
        info.SetTarget(targetImpl().value_or(EventTarget()));
    }
    onFocusAxisCallback(info);
    return info.IsStopPropagation();
}

bool FocusEventHandler::HandleCrownEvent(const CrownEvent& CrownEvent)
{
    ACE_DCHECK(IsCurrentFocus());
    bool retCallback = false;
    auto onCrownEventCallback = GetOnCrownCallback();
    if (onCrownEventCallback) {
        CrownEventInfo crownInfo(CrownEvent);
        onCrownEventCallback(crownInfo);
        retCallback = crownInfo.IsStopPropagation();
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnCrownEventUser: Node %{public}s/%{public}d handle CrownAction:%{public}d",
            GetFrameName().c_str(), GetFrameId(), CrownEvent.action);
    } else {
        retCallback = ProcessOnCrownEventInternal(CrownEvent);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnCrownEventInternal: Node %{public}s/%{public}d handle CrownAction:%{public}d",
            GetFrameName().c_str(), GetFrameId(), CrownEvent.action);
    }
    return retCallback;
}

bool FocusEventHandler::ProcessOnCrownEventInternal(const CrownEvent& event)
{
    bool result = false;
    auto onCrownEventCallbackInternal = GetOnCrownEventInternal();
    if (onCrownEventCallbackInternal) {
        onCrownEventCallbackInternal(event);
        result = true;
    }
    return result;
}

bool FocusEventHandler::OnKeyPreIme(KeyEventInfo& info, const KeyEvent& keyEvent)
{
    TAG_LOGD(AceLogTag::ACE_FOCUS,
        "node: %{public}s/%{public}d try to handle OnKeyPreIme by "
        "code:%{private}d/action:%{public}d/isPreIme:%{public}d",
        GetFrameName().c_str(), GetFrameId(), keyEvent.code, keyEvent.action, keyEvent.isPreIme);
    auto onKeyPreIme = GetOnKeyPreIme();
    if (onKeyPreIme) {
        bool retPreIme = onKeyPreIme(info);
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        auto eventManager = pipeline->GetEventManager();
        if (eventManager) {
            eventManager->SetIsKeyConsumed(retPreIme);
        }
        TAG_LOGI(AceLogTag::ACE_FOCUS, "node: %{public}s/%{public}d handle OnKeyPreIme",
            GetFrameName().c_str(), GetFrameId());
        return info.IsStopPropagation();
    } else if (GetFrameName() == V2::UI_EXTENSION_COMPONENT_ETS_TAG ||
               GetFrameName() == V2::EMBEDDED_COMPONENT_ETS_TAG) {
        TAG_LOGI(AceLogTag::ACE_FOCUS, "node: %{public}s/%{public}d try to process OnKeyEventInternal",
            GetFrameName().c_str(), GetFrameId());
        return ProcessOnKeyEventInternal(keyEvent);
    } else {
        return false;
    }
}

bool FocusEventHandler::OnClick(const KeyEvent& event)
{
    auto onClickCallback = GetOnClickCallback();
    if (onClickCallback) {
        auto info = GestureEvent();
        info.SetTimeStamp(event.timeStamp);
        auto geometryNode = GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, false);
        auto rect = geometryNode->GetFrameRect();
        auto centerToWindow = Offset((rect.Left() + rect.Right()) / 2, (rect.Top() + rect.Bottom()) / 2);
        auto centerToNode = Offset((rect.Right() - rect.Left()) / 2, (rect.Bottom() - rect.Top()) / 2);
        info.SetGlobalLocation(centerToWindow);
        info.SetLocalLocation(centerToNode);
        info.SetSourceDevice(event.sourceType);
        info.SetDeviceId(event.deviceId);
        info.SetInputEventType(InputEventType::KEYBOARD);
        auto node = GetFrameNode();
        CHECK_NULL_RETURN(node, false);
        auto pipelineContext = node->GetContextRefPtr();
        if (pipelineContext) {
            auto windowOffset = pipelineContext->GetCurrentWindowRect().GetOffset() + centerToWindow;
            auto globalWindowOffset = pipelineContext->GetGlobalDisplayWindowRect().GetOffset() + centerToWindow;
            info.SetScreenLocation(windowOffset);
            info.SetGlobalDisplayLocation(globalWindowOffset);
        }
        info.SetSourceTool(SourceTool::UNKNOWN);
        auto eventHub = node->GetOrCreateEventHub<EventHub>();
        if (eventHub) {
            auto targetImpl = eventHub->CreateGetEventTargetImpl();
            info.SetTarget(targetImpl().value_or(EventTarget()));
        }
        onClickCallback(info);
        return true;
    }
    return false;
}

bool FocusEventHandler::OnKeyEventNodeInternal(const KeyEvent& keyEvent)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    bool isBypassInner = keyEvent.IsKey({ KeyCode::KEY_TAB }) && pipeline && pipeline->IsTabJustTriggerOnKeyEvent();
    auto retInternal = false;
    if (isNodeNeedKey_) {
        retInternal =  ProcessOnKeyEventInternal(keyEvent);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnKeyEventInteral Node process self: Node %{public}s/%{public}d"
            "handle KeyEvent(" SEC_PLD(%{private}d) ", %{public}d) "
            "return: %{public}d",
            GetFrameName().c_str(), GetFrameId(), SEC_PARAM(keyEvent.code), keyEvent.action, retInternal);
        return retInternal;
    }
    if (!isBypassInner && !onKeyEventsInternal_.empty()) {
        retInternal = ProcessOnKeyEventInternal(keyEvent);
        TAG_LOGI(AceLogTag::ACE_FOCUS,
            "OnKeyEventInteral: Node %{public}s/%{public}d"
            "handle KeyEvent(" SEC_PLD(%{private}d) ", %{public}d) "
            "return: %{public}d",
            GetFrameName().c_str(), GetFrameId(), SEC_PARAM(keyEvent.code), keyEvent.action, retInternal);
    }
    return retInternal;
}

bool FocusEventHandler::OnKeyEventNodeUser(KeyEventInfo& info, const KeyEvent& keyEvent)
{
    auto node = GetFrameNode();
    CHECK_NULL_RETURN(node, false);
    auto* pipeline = node->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto retCallback = false;
    auto onKeyEventCallback = GetOnKeyCallback();
    if (onKeyEventCallback) {
        auto result = onKeyEventCallback(info);
        retCallback = info.IsStopPropagation() || result;
        auto eventManager = pipeline->GetEventManager();
        PrintOnKeyEventUserInfo(keyEvent, retCallback);
    }

    auto onJSFrameNodeKeyCallback = GetJSFrameNodeOnKeyCallback();
    if (onJSFrameNodeKeyCallback) {
        onJSFrameNodeKeyCallback(info);
        retCallback = info.IsStopPropagation();
        PrintOnKeyEventUserInfo(keyEvent, retCallback);
    }
    return retCallback;
}

void FocusEventHandler::PrintOnKeyEventUserInfo(const KeyEvent& keyEvent, bool retCallback)
{
    TAG_LOGI(AceLogTag::ACE_FOCUS,
        "OnKeyEventUser: Node %{public}s/%{public}d"
        "handle KeyEvent(" SEC_PLD(%{private}d) ", %{public}d) return: %{public}d",
        GetFrameName().c_str(), GetFrameId(), SEC_PARAM(keyEvent.code), keyEvent.action, retCallback);
}

bool FocusEventHandler::ProcessOnKeyEventInternal(const KeyEvent& event)
{
    bool result = false;
    for (const auto& onKeyEvent : onKeyEventsInternal_) {
        auto callback = onKeyEvent.second;
        if (callback && callback(event)) {
            result = true;
        }
    }
    return result;
}
} // namespace OHOS::Ace::NG