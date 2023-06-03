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

#include "adapter/preview/external/multimodalinput/axis_event.h"
#include "adapter/preview/external/multimodalinput/key_event.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/singleton.h"
#include "core/common/clipboard/clipboard_proxy.h"
#ifndef ENABLE_ROSEN_BACKEND
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"
#endif

namespace OHOS::Ace::Platform {

class ACE_FORCE_EXPORT EventDispatcher : public Singleton<EventDispatcher> {
    DECLARE_SINGLETON(EventDispatcher);

public:
    void Initialize();
    void DispatchIdleEvent(int64_t deadline);
    bool DispatchTouchEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent);
    bool DispatchBackPressedEvent();
    bool DispatchInputMethodEvent(unsigned int codePoint);
    bool DispatchKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent);
#ifndef ENABLE_ROSEN_BACKEND
    void SetGlfwWindowController(const FlutterDesktopWindowControllerRef& controller)
    {
        controller_ = controller;
    }
#endif

private:
    // Process all printable characters. If the input method is used, this function is invalid.
    bool HandleTextKeyEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent);
#ifndef ENABLE_ROSEN_BACKEND
    FlutterDesktopWindowControllerRef controller_ = nullptr;
#endif
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ENTRANCE_EVENT_DISPATCHER_H
