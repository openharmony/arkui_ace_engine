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

#include "base/log/log.h"
#include "base/log/ace_trace.h"
#include "core/common/container_scope.h"
#include "adapter/preview/entrance/ace_container.h"
#include "adapter/preview/entrance/editing/text_input_client_mgr.h"
#include "adapter/preview/entrance/flutter_ace_view.h"

namespace OHOS::Ace::Platform {
namespace {

const wchar_t UPPER_CASE_A = L'A';
const wchar_t LOWER_CASE_A = L'a';
const wchar_t CASE_0 = L'0';
const std::wstring NUM_SYMBOLS = L")!@#$%^&*(";
const std::map<KeyCode, wchar_t> PRINTABEL_SYMBOLS = {
    {KeyCode::KEY_GRAVE, L'`'},
    {KeyCode::KEY_MINUS, L'-'},
    {KeyCode::KEY_EQUALS, L'='},
    {KeyCode::KEY_LEFT_BRACKET, L'['},
    {KeyCode::KEY_RIGHT_BRACKET, L']'},
    {KeyCode::KEY_BACKSLASH, L'\\'},
    {KeyCode::KEY_SEMICOLON, L';'},
    {KeyCode::KEY_APOSTROPHE, L'\''},
    {KeyCode::KEY_COMMA, L','},
    {KeyCode::KEY_PERIOD, L'.'},
    {KeyCode::KEY_SLASH, L'/'},
    {KeyCode::KEY_SPACE, L' '},
    {KeyCode::KEY_NUMPAD_DIVIDE, L'/'},
    {KeyCode::KEY_NUMPAD_MULTIPLY, L'*'},
    {KeyCode::KEY_NUMPAD_SUBTRACT, L'-'},
    {KeyCode::KEY_NUMPAD_ADD, L'+'},
    {KeyCode::KEY_NUMPAD_DOT, L'.'},
    {KeyCode::KEY_NUMPAD_COMMA, L','},
    {KeyCode::KEY_NUMPAD_EQUALS, L'='},
};

const std::map<KeyCode, wchar_t> SHIFT_PRINTABEL_SYMBOLS = {
    {KeyCode::KEY_GRAVE, L'~'},
    {KeyCode::KEY_MINUS, L'_'},
    {KeyCode::KEY_EQUALS, L'+'},
    {KeyCode::KEY_LEFT_BRACKET, L'{'},
    {KeyCode::KEY_RIGHT_BRACKET, L'}'},
    {KeyCode::KEY_BACKSLASH, L'|'},
    {KeyCode::KEY_SEMICOLON, L':'},
    {KeyCode::KEY_APOSTROPHE, L'\"'},
    {KeyCode::KEY_COMMA, L'<'},
    {KeyCode::KEY_PERIOD, L'>'},
    {KeyCode::KEY_SLASH, L'?'},
};

}

EventDispatcher::EventDispatcher()
{}

EventDispatcher::~EventDispatcher() = default;

void EventDispatcher::SetGlfwWindowController(const FlutterDesktopWindowControllerRef& controller)
{
    controller_ = controller;
}

void EventDispatcher::Initialize()
{
    LOGI("Initialize event dispatcher");
    // Initial the proxy of Input method
    TextInputClientMgr::GetInstance().InitTextInputProxy();
    // Register the idle event callback function.
#ifndef ENABLE_ROSEN_BACKEND
    IdleCallback idleNoticeCallback = [] (int64_t deadline) {
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

bool EventDispatcher::DispatchTouchEvent(const TouchEvent& event)
{
    ACE_SCOPED_TRACE("DispatchTouchEvent");
    LOGI("Dispatch touch event");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGE("container is null");
        return false;
    }

    auto aceView = container->GetAceView();
    if (!aceView) {
        LOGE("aceView is null");
        return false;
    }

    return aceView->HandleTouchEvent(event);
}

bool EventDispatcher::DispatchBackPressedEvent()
{
    ACE_SCOPED_TRACE("DispatchBackPressedEvent");
    LOGI("Dispatch back pressed event");
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        return false;
    }

    auto context = container->GetPipelineContext();
    if (!context) {
        return false;
    }

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

bool EventDispatcher::DispatchInputMethodEvent(unsigned int code_point)
{
    ACE_SCOPED_TRACE("DispatchInputMethodEvent");
    LOGI("Dispatch input method event");
    return TextInputClientMgr::GetInstance().AddCharacter(static_cast<wchar_t>(code_point));
}

bool EventDispatcher::DispatchKeyEvent(const KeyEvent& event)
{
    ACE_SCOPED_TRACE("DispatchKeyEvent");
    LOGI("Dispatch key event");
    if (HandleTextKeyEvent(event)) {
        LOGI("The event is related to the input component and has been handled successfully.");
        return true;
    }
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGE("container is null");
        return false;
    }

    auto aceView = container->GetAceView();
    if (!aceView) {
        LOGE("aceView is null");
        return false;
    }
#ifdef USE_GLFW_WINDOW
    container->GetTaskExecutor()->PostTask(
        [aceView, event]() {
            aceView->HandleKeyEvent(event);
        },
        TaskExecutor::TaskType::UI);
    return true;
#else
    return aceView->HandleKeyEvent(event);
#endif
}

void EventDispatcher::RegisterCallbackGetCapsLockStatus(CallbackGetKeyboardStatus callback)
{
    if (callback) {
        callbackGetCapsLockStatus_ = callback;
    }
}

void EventDispatcher::RegisterCallbackGetNumLockStatus(CallbackGetKeyboardStatus callback)
{
    if (callback) {
        callbackGetNumLockStatus_ = callback;
    }
}

bool EventDispatcher::HandleTextKeyEvent(const KeyEvent& event)
{
    // Only the keys involved in the input component are processed here, and the other keys will be forwarded.
    if (!TextInputClientMgr::GetInstance().IsValidClientId()) {
        return false;
    }

    bool enableCapsLock = callbackGetCapsLockStatus_ && callbackGetCapsLockStatus_();
    bool enableNumLock = callbackGetNumLockStatus_ && callbackGetNumLockStatus_();
    const static size_t maxKeySizes = 2;
    wchar_t keyChar;
    if (event.pressedCodes.size() == 1) {
        auto iterCode = PRINTABEL_SYMBOLS.find(event.code);
        if (iterCode != PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_0) + CASE_0;
        } else if (KeyCode::KEY_NUMPAD_0 <= event.code && event.code <= KeyCode::KEY_NUMPAD_9) {
            if (!enableNumLock) {
                return true;
            }
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_NUMPAD_0) + CASE_0;
        } else if (KeyCode::KEY_A <= event.code && event.code <= KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_A);
            keyChar += (enableCapsLock ? UPPER_CASE_A : LOWER_CASE_A);
        } else {
            return false;
        }
    } else if (event.pressedCodes.size() == maxKeySizes && event.pressedCodes[0] == KeyCode::KEY_SHIFT_LEFT) {
        auto iterCode = SHIFT_PRINTABEL_SYMBOLS.find(event.code);
        if (iterCode != SHIFT_PRINTABEL_SYMBOLS.end()) {
            keyChar = iterCode->second;
        } else if (KeyCode::KEY_A <= event.code && event.code <= KeyCode::KEY_Z) {
            keyChar = static_cast<wchar_t>(event.code) - static_cast<wchar_t>(KeyCode::KEY_A);
            keyChar += (enableCapsLock ? LOWER_CASE_A : UPPER_CASE_A);
        } else if (KeyCode::KEY_0 <= event.code && event.code <= KeyCode::KEY_9) {
            keyChar = NUM_SYMBOLS[static_cast<int32_t>(event.code) - static_cast<int32_t>(KeyCode::KEY_0)];
        } else {
            return false;
        }
    } else {
        return false;
    }
#ifdef USE_GLFW_WINDOW
    return true;
#else
    if (event.action != KeyAction::DOWN) {
        return true;
    }
    return TextInputClientMgr::GetInstance().AddCharacter(keyChar);
#endif
}

} // namespace OHOS::Ace::Platform
