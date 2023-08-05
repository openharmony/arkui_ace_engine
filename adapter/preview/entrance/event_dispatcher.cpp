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
    for (auto& item : pointerEvent->pointers) {
        TouchPoint pointer;
        pointer.id = item.id;
        pointer.x = item.x;
        pointer.y = item.y;
        pointer.screenX = item.screenX;
        pointer.screenY = item.screenY;
        pointer.downTime = item.downTime;
        pointer.size = item.size;
        pointer.force = item.force;
        pointer.tiltX = item.tiltX;
        pointer.tiltY = item.tiltY;
        pointer.sourceTool = static_cast<SourceTool>(static_cast<int32_t>(item.sourceTool));
        pointer.isPressed = item.isPressed;
        event.pointers.emplace_back(pointer);
    }
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
}

} // namespace

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
        LOGE("container is null");
        return;
    }

    auto aceView = container->GetAceView();
    if (!aceView) {
        LOGE("aceView is null");
        return;
    }

    aceView->ProcessIdleEvent(deadline);
}

bool EventDispatcher::DispatchTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    ACE_SCOPED_TRACE("DispatchTouchEvent");
    LOGI("Dispatch touch event");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, false);
    auto aceView = container->GetAceView();
    CHECK_NULL_RETURN(aceView, false);
    TouchEvent event;
    ConvertTouchEvent(pointerEvent, event);
    return aceView->HandleTouchEvent(event);
}

bool EventDispatcher::DispatchBackPressedEvent()
{
    ACE_SCOPED_TRACE("DispatchBackPressedEvent");
    LOGI("Dispatch back pressed event");
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
                LOGW("context is nullptr.");
                return;
            }
            bool canBack = false;
            if (context->IsLastPage()) {
                LOGW("Can't back because this is the last page!");
            } else {
                canBack = context->CallRouterBackToPopPage();
            }
            backPromise.set_value(canBack);
        },
        TaskExecutor::TaskType::PLATFORM);
    return backFuture.get();
}

bool EventDispatcher::DispatchInputMethodEvent(unsigned int codePoint)
{
    ACE_SCOPED_TRACE("DispatchInputMethodEvent");
    LOGI("Dispatch input method event");
    return TextInputClientMgr::GetInstance().AddCharacter(static_cast<wchar_t>(codePoint));
}

bool EventDispatcher::DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent)
{
    ACE_SCOPED_TRACE("DispatchKeyEvent");
    LOGI("Dispatch key event");
    if (HandleTextKeyEvent(keyEvent)) {
        LOGI("The event is related to the input component and has been handled successfully.");
        return true;
    }
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, false);
    auto aceView = container->GetAceView();
    CHECK_NULL_RETURN(aceView, false);

    KeyEvent event;
    ConvertKeyEvent(keyEvent, event);
    return aceView->HandleKeyEvent(event);
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
