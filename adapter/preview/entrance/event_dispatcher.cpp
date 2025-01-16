/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/entrance/event_dispatcher.h"

#include <map>

#include "adapter/preview/entrance/ace_container.h"
#include "adapter/preview/entrance/ace_view_preview.h"
#include "adapter/preview/entrance/editing/text_input_client_mgr.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "core/common/container_scope.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::Platform {
namespace {

const wchar_t UPPER_CASE_A = L'A';
const wchar_t LOWER_CASE_A = L'a';
const wchar_t CASE_0 = L'0';
const std::wstring NUM_SYMBOLS = L")!@#$%^&*(";
const std::map<MMI::KeyCode, wchar_t> PRINTABEL_SYMBOLS = {
    { MMI::KeyCode::KEY_GRAVE, L'`' },
    { MMI::KeyCode::KEY_MINUS, L'-' },
    { MMI::KeyCode::KEY_EQUALS, L'=' },
    { MMI::KeyCode::KEY_LEFT_BRACKET, L'[' },
    { MMI::KeyCode::KEY_RIGHT_BRACKET, L']' },
    { MMI::KeyCode::KEY_BACKSLASH, L'\\' },
    { MMI::KeyCode::KEY_SEMICOLON, L';' },
    { MMI::KeyCode::KEY_APOSTROPHE, L'\'' },
    { MMI::KeyCode::KEY_COMMA, L',' },
    { MMI::KeyCode::KEY_PERIOD, L'.' },
    { MMI::KeyCode::KEY_SLASH, L'/' },
    { MMI::KeyCode::KEY_SPACE, L' ' },
    { MMI::KeyCode::KEY_NUMPAD_DIVIDE, L'/' },
    { MMI::KeyCode::KEY_NUMPAD_MULTIPLY, L'*' },
    { MMI::KeyCode::KEY_NUMPAD_SUBTRACT, L'-' },
    { MMI::KeyCode::KEY_NUMPAD_ADD, L'+' },
    { MMI::KeyCode::KEY_NUMPAD_DOT, L'.' },
    { MMI::KeyCode::KEY_NUMPAD_COMMA, L',' },
    { MMI::KeyCode::KEY_NUMPAD_EQUALS, L'=' },
};

const std::map<MMI::KeyCode, wchar_t> SHIFT_PRINTABEL_SYMBOLS = {
    { MMI::KeyCode::KEY_GRAVE, L'~' },
    { MMI::KeyCode::KEY_MINUS, L'_' },
    { MMI::KeyCode::KEY_EQUALS, L'+' },
    { MMI::KeyCode::KEY_LEFT_BRACKET, L'{' },
    { MMI::KeyCode::KEY_RIGHT_BRACKET, L'}' },
    { MMI::KeyCode::KEY_BACKSLASH, L'|' },
    { MMI::KeyCode::KEY_SEMICOLON, L':' },
    { MMI::KeyCode::KEY_APOSTROPHE, L'\"' },
    { MMI::KeyCode::KEY_COMMA, L'<' },
    { MMI::KeyCode::KEY_PERIOD, L'>' },
    { MMI::KeyCode::KEY_SLASH, L'?' },
};

void ConvertTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, TouchEvent& event)
{
    event.id = pointerEvent->id;
    event.x = pointerEvent->x;
    event.y = pointerEvent->y;
    event.screenX = pointerEvent->screenX;
    event.screenY = pointerEvent->screenY;
    event.type = static_cast<TouchType>(static_cast<size_t>(pointerEvent->type));
    event.pullType = static_cast<TouchType>(static_cast<size_t>(pointerEvent->pullType));
    event.time = pointerEvent->time;
    event.size = pointerEvent->size;
    event.force = pointerEvent->force;
    event.tiltX = pointerEvent->tiltX;
    event.tiltY = pointerEvent->tiltY;
    event.deviceId = pointerEvent->deviceId;
    event.sourceType = static_cast<SourceType>(static_cast<int32_t>(pointerEvent->sourceType));
    event.sourceTool = static_cast<SourceTool>(static_cast<int32_t>(pointerEvent->sourceTool));
    event.pointerEvent = pointerEvent;
    TouchPoint pointer { .id = event.id,
        .x = event.x,
        .y = event.y,
        .screenX = event.screenX,
        .screenY = event.screenY,
        .downTime = event.time,
        .size = event.size,
        .force = event.force,
        .isPressed = (event.type == TouchType::DOWN) };
    event.pointers.emplace_back(pointer);
}

void ConvertKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent, KeyEvent& event)
{
    event.code = static_cast<KeyCode>(static_cast<int32_t>(keyEvent->code));
    event.key = keyEvent->key;
    event.action = static_cast<KeyAction>(static_cast<int32_t>(keyEvent->action));
    for (auto& item : keyEvent->pressedCodes) {
        event.pressedCodes.push_back(static_cast<KeyCode>(static_cast<int32_t>(item)));
    }
    event.repeatTime = keyEvent->repeatTime;
    event.timeStamp = keyEvent->timeStamp;
    event.metaKey = keyEvent->metaKey;
    event.deviceId = keyEvent->deviceId;
    event.sourceType = static_cast<SourceType>(static_cast<int32_t>(keyEvent->sourceType));
    event.rawKeyEvent = keyEvent;
    event.enableCapsLock = keyEvent->enableCapsLock_;
    event.numLock = keyEvent->enableNumLock_;
}

} // namespace

Offset GetTouchEventOriginOffset(const TouchEvent& event)
{
    if (event.pointerEvent) {
        for (auto& item : event.pointerEvent->pointers) {
            return Offset(item.x, item.y);
        }
    }
    return Offset();
}

TimeStamp GetTouchEventOriginTimeStamp(const TouchEvent& event)
{
    if (event.pointerEvent) {
        return event.pointerEvent->time;
    }
    return event.time;
}

void UpdatePressedKeyCodes(std::vector<KeyCode>& pressedKeyCodes) {}

EventDispatcher::EventDispatcher() {}

EventDispatcher::~EventDispatcher() = default;

void EventDispatcher::Initialize()
{
    LOGI("Initialize event dispatcher");
    // Initial the proxy of Input method
    TextInputClientMgr::GetInstance().InitTextInputProxy();
    // Register the idle event callback function.
#ifndef ENABLE_ROSEN_BACKEND
    IdleCallback idleNoticeCallback = [](int64_t deadline) {
        EventDispatcher::GetInstance().DispatchIdleEvent(deadline);
    };
    FlutterDesktopSetIdleCallback(controller_, idleNoticeCallback);
#else
    // rosen process idle
#endif
}

void EventDispatcher::DispatchIdleEvent(int64_t deadline)
{
    ACE_SCOPED_TRACE("DispatchIdleEvent");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        return;
    }

    auto aceView = AceType::DynamicCast<AceViewPreview>(container->GetAceView());
    if (!aceView) {
        return;
    }

    aceView->ProcessIdleEvent(deadline);
}

static void GetMouseEventAction(int32_t action, OHOS::Ace::MouseEvent& mouseEvent)
{
    switch (action) {
        case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_DOWN:
            mouseEvent.action = MouseAction::PRESS;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_BUTTON_UP:
            mouseEvent.action = MouseAction::RELEASE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW:
            mouseEvent.action = MouseAction::WINDOW_ENTER;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_LEAVE_WINDOW:
            mouseEvent.action = MouseAction::WINDOW_LEAVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_MOVE:
            mouseEvent.action = MouseAction::MOVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_DOWN:
            mouseEvent.action = MouseAction::PRESS;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_MOVE:
            mouseEvent.action = MouseAction::MOVE;
            break;
        case OHOS::MMI::PointerEvent::POINTER_ACTION_PULL_UP:
            mouseEvent.action = MouseAction::RELEASE;
            break;
        default:
            mouseEvent.action = MouseAction::NONE;
            break;
    }
}

static void GetMouseEventButton(int32_t button, Ace::MouseEvent& mouseEvent)
{
    switch (button) {
        case MMI::PointerEvent::MOUSE_BUTTON_LEFT:
            mouseEvent.button = MouseButton::LEFT_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_RIGHT:
            mouseEvent.button = MouseButton::RIGHT_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_MIDDLE:
            mouseEvent.button = MouseButton::MIDDLE_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_SIDE:
            mouseEvent.button = MouseButton::BACK_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_EXTRA:
            mouseEvent.button = MouseButton::SIDE_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_FORWARD:
            mouseEvent.button = MouseButton::FORWARD_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_BACK:
            mouseEvent.button = MouseButton::BACK_BUTTON;
            break;
        case MMI::PointerEvent::MOUSE_BUTTON_TASK:
            mouseEvent.button = MouseButton::TASK_BUTTON;
            break;
        default:
            mouseEvent.button = MouseButton::NONE_BUTTON;
            break;
    }
}

static void ConvertMouseEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, Ace::MouseEvent& mouseEvent)
{
    mouseEvent.id = pointerEvent->id;
    mouseEvent.x = pointerEvent->x;
    mouseEvent.y = pointerEvent->y;
    mouseEvent.screenX = pointerEvent->screenX;
    mouseEvent.screenY = pointerEvent->screenY;
    GetMouseEventAction(pointerEvent->pointerAction_, mouseEvent);
    GetMouseEventButton(pointerEvent->buttonId_, mouseEvent);
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.targetDisplayId = pointerEvent->targetDisplayId_;
    mouseEvent.deviceId = pointerEvent->deviceId;
    std::set<int32_t> buttonSet = pointerEvent->pressedButtons_;
    if (pointerEvent->pressedButtons_.empty()) {
        pointerEvent->pressedButtons_.insert(pointerEvent->buttonId_);
    }
    uint32_t buttons = 0;
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_LEFT)) {
        buttons &= static_cast<uint32_t>(MouseButton::LEFT_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_RIGHT)) {
        buttons &= static_cast<uint32_t>(MouseButton::RIGHT_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_MIDDLE)) {
        buttons &= static_cast<uint32_t>(MouseButton::MIDDLE_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_SIDE)) {
        buttons &= static_cast<uint32_t>(MouseButton::SIDE_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_EXTRA)) {
        buttons &= static_cast<uint32_t>(MouseButton::EXTRA_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_FORWARD)) {
        buttons &= static_cast<uint32_t>(MouseButton::FORWARD_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_BACK)) {
        buttons &= static_cast<uint32_t>(MouseButton::BACK_BUTTON);
    }
    if (buttonSet.end() != buttonSet.find(MMI::PointerEvent::MOUSE_BUTTON_TASK)) {
        buttons &= static_cast<uint32_t>(MouseButton::TASK_BUTTON);
    }
    mouseEvent.pressedButtons = static_cast<int32_t>(buttons);
}

static void GetAxisEventAction(int32_t action, Ace::AxisEvent& event)
{
    switch (action) {
        case MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN:
            event.action = Ace::AxisAction::BEGIN;
            break;
        case MMI::PointerEvent::POINTER_ACTION_AXIS_UPDATE:
            event.action = Ace::AxisAction::UPDATE;
            break;
        case MMI::PointerEvent::POINTER_ACTION_AXIS_END:
            event.action = Ace::AxisAction::END;
            break;
        default:
            event.action = Ace::AxisAction::NONE;
            break;
    }
}

static double GetAxisValue(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, MMI::PointerEvent::AxisType axis)
{
    double axisValue {};
    if ((axis >= MMI::PointerEvent::AXIS_TYPE_UNKNOWN) && (axis < MMI::PointerEvent::AXIS_TYPE_MAX)) {
        axisValue = pointerEvent->axisValues_[axis];
    }
    return axisValue;
}

static void ConvertAxisEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent, Ace::AxisEvent& event)
{
    event.id = pointerEvent->id;
    event.x = pointerEvent->x;
    event.y = pointerEvent->y;
    event.screenX = pointerEvent->screenX;
    event.screenY = pointerEvent->screenY;
    event.horizontalAxis = GetAxisValue(pointerEvent, MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_HORIZONTAL);
    event.verticalAxis = GetAxisValue(pointerEvent, MMI::PointerEvent::AxisType::AXIS_TYPE_SCROLL_VERTICAL);
    event.pinchAxisScale = GetAxisValue(pointerEvent, MMI::PointerEvent::AxisType::AXIS_TYPE_PINCH);
    event.rotateAxisAngle = GetAxisValue(pointerEvent, MMI::PointerEvent::AxisType::AXIS_TYPE_ROTATE);
    GetAxisEventAction(pointerEvent->pointerAction_, event);
    event.isRotationEvent = (pointerEvent->pointerAction_ >= MMI::PointerEvent::POINTER_ACTION_ROTATE_BEGIN) &&
                            (pointerEvent->pointerAction_ <= MMI::PointerEvent::POINTER_ACTION_ROTATE_END);
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    event.pointerEvent = pointerEvent;
}

bool EventDispatcher::DispatchTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    ACE_SCOPED_TRACE("DispatchTouchEvent");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, false);
    auto aceView = AceType::DynamicCast<AceViewPreview>(container->GetAceView());
    CHECK_NULL_RETURN(aceView, false);
    if (pointerEvent->sourceType == MMI::PointerEvent::SOURCE_TYPE_MOUSE) {
        if (pointerEvent->pointerAction_ >= MMI::PointerEvent::POINTER_ACTION_AXIS_BEGIN &&
            pointerEvent->pointerAction_ <= MMI::PointerEvent::POINTER_ACTION_AXIS_END) {
            OHOS::Ace::AxisEvent axisEvent;
            ConvertAxisEvent(pointerEvent, axisEvent);
            return aceView->HandleAxisEvent(axisEvent);
        } else {
            OHOS::Ace::MouseEvent mouseEvent;
            ConvertMouseEvent(pointerEvent, mouseEvent);
            return aceView->HandleMouseEvent(mouseEvent);
        }
    }

    TouchEvent touchEvent;
    ConvertTouchEvent(pointerEvent, touchEvent);
    return aceView->HandleTouchEvent(touchEvent);
}

bool EventDispatcher::DispatchBackPressedEvent()
{
    ACE_SCOPED_TRACE("DispatchBackPressedEvent");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, false);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, false);

    std::promise<bool> backPromise;
    std::future<bool> backFuture = backPromise.get_future();
    auto weak = AceType::WeakClaim(AceType::RawPtr(context));
    container->GetTaskExecutor()->PostTask(
        [weak, &backPromise]() {
            auto context = weak.Upgrade();
            if (context == nullptr) {
                return;
            }
            bool canBack = false;
            if (!context->IsLastPage()) {
                canBack = context->CallRouterBackToPopPage();
            }
            backPromise.set_value(canBack);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUICallRouterBackToPopPage");
    return backFuture.get();
}

bool EventDispatcher::DispatchInputMethodEvent(unsigned int codePoint)
{
    ACE_SCOPED_TRACE("DispatchInputMethodEvent");
    return TextInputClientMgr::GetInstance().AddCharacter(static_cast<wchar_t>(codePoint));
}

bool EventDispatcher::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    ACE_SCOPED_TRACE("DispatchKeyEvent");
    if (HandleTextKeyEvent(keyEvent)) {
        return true;
    }
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, false);
    auto aceView = AceType::DynamicCast<AceViewPreview>(container->GetAceView());
    CHECK_NULL_RETURN(aceView, false);

    KeyEvent event;
    ConvertKeyEvent(keyEvent, event);
    event.isPreIme = true;
    if (!aceView->HandleKeyEvent(event)) {
        event.isPreIme = false;
        return aceView->HandleKeyEvent(event);
    }
    return true;
}

bool EventDispatcher::HandleTextKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    // Only the keys involved in the input component are processed here, and the other keys will be forwarded.
    if (!TextInputClientMgr::GetInstance().IsValidClientId()) {
        return false;
    }

    const static size_t maxKeySizes = 2;
    wchar_t keyChar;
    if (keyEvent->pressedCodes.size() == 1) {
        auto iterCode = PRINTABEL_SYMBOLS.find(keyEvent->code);
        if (iterCode != PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (MMI::KeyCode::KEY_0 <= keyEvent->code && keyEvent->code <= MMI::KeyCode::KEY_9) {
            keyChar = static_cast<wchar_t>(keyEvent->code) - static_cast<wchar_t>(MMI::KeyCode::KEY_0) + CASE_0;
        } else if (MMI::KeyCode::KEY_NUMPAD_0 <= keyEvent->code && keyEvent->code <= MMI::KeyCode::KEY_NUMPAD_9) {
            if (!keyEvent->enableNumLock_) {
                return true;
            }
            keyChar = static_cast<wchar_t>(keyEvent->code) - static_cast<wchar_t>(MMI::KeyCode::KEY_NUMPAD_0) + CASE_0;
        } else if (MMI::KeyCode::KEY_A <= keyEvent->code && keyEvent->code <= MMI::KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(keyEvent->code) - static_cast<wchar_t>(MMI::KeyCode::KEY_A);
            keyChar += (keyEvent->enableCapsLock_ ? UPPER_CASE_A : LOWER_CASE_A);
        } else {
            return false;
        }
    } else if (keyEvent->pressedCodes.size() == maxKeySizes &&
               keyEvent->pressedCodes[0] == MMI::KeyCode::KEY_SHIFT_LEFT) {
        auto iterCode = SHIFT_PRINTABEL_SYMBOLS.find(keyEvent->code);
        if (iterCode != SHIFT_PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (MMI::KeyCode::KEY_A <= keyEvent->code && keyEvent->code <= MMI::KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(keyEvent->code) - static_cast<wchar_t>(MMI::KeyCode::KEY_A);
            keyChar += (keyEvent->enableCapsLock_ ? LOWER_CASE_A : UPPER_CASE_A);
        } else if (MMI::KeyCode::KEY_0 <= keyEvent->code && keyEvent->code <= MMI::KeyCode::KEY_9) {
            keyChar = NUM_SYMBOLS[static_cast<int32_t>(keyEvent->code) - static_cast<int32_t>(MMI::KeyCode::KEY_0)];
        } else {
            return false;
        }
    } else {
        return false;
    }
    if (keyEvent->action != MMI::KeyAction::DOWN) {
        return true;
    }
    return TextInputClientMgr::GetInstance().AddCharacter(keyChar);
}

} // namespace OHOS::Ace::Platform
