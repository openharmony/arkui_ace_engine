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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EVENT_DISPATCHER_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EVENT_DISPATCHER_H

#include "base/memory/referenced.h"
#include "base/utils/singleton.h"
#include "base/utils/macros.h"
#include "core/event/key_event.h"
#include "core/event/touch_event.h"
#include "core/common/clipboard/clipboard_proxy.h"
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"

namespace OHOS::Ace::Platform {

using CallbackGetKeyboardStatus = std::function< bool(void) >;

class ACE_FORCE_EXPORT_WITH_PREVIEW EventDispatcher : public Singleton<EventDispatcher> {
    DECLARE_SINGLETON(EventDispatcher);
public:
    void Initialize();
    void SetGlfwWindowController(const FlutterDesktopWindowControllerRef& controller);
    void DispatchIdleEvent(int64_t deadline);
    bool DispatchTouchEvent(const TouchEvent& event);
    bool DispatchBackPressedEvent();
    bool DispatchInputMethodEvent(unsigned int code_point);
    bool DispatchKeyEvent(const KeyEvent& event);
    void RegisterCallbackGetCapsLockStatus(CallbackGetKeyboardStatus callback);
    void RegisterCallbackGetNumLockStatus(CallbackGetKeyboardStatus callback);

private:
    // Process all printable characters. If the input method is used, this function is invalid.
    bool HandleTextKeyEvent(const KeyEvent& event);
    FlutterDesktopWindowControllerRef controller_ = nullptr;
    CallbackGetKeyboardStatus callbackGetCapsLockStatus_;
    CallbackGetKeyboardStatus callbackGetNumLockStatus_;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EVENT_DISPATCHER_H
