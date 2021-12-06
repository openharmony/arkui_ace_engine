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

#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H

#include <memory>

#include "axis_event.h"
#include "context/context.h"
#include "key_event.h"
#include "pointer_event.h"
#include "touch_event.h"
#include "native_engine/native_value.h"
#include "runtime.h"
#include "viewport_config.h"
#include "wm/window.h"

namespace OHOS::Ace {

#define ACE_EXPORT __attribute__((visibility("default")))

class ACE_EXPORT UIContent {
public:
    static std::unique_ptr<UIContent> Create(OHOS::AbilityRuntime::Context* context);

    virtual ~UIContent() = default;

    // UI content lifecycles
    virtual void Initialize(OHOS::Rosen::Window* window, const std::string& url, NativeValue* storage) = 0;
    virtual void Foreground() = 0;
    virtual void Background() = 0;
    virtual void Focus() = 0;
    virtual void UnFocus() = 0;
    virtual void Destroy() = 0;

    // UI content event process
    virtual bool ProcessBackPressed() = 0;
    virtual bool ProcessPointerEvent(const OHOS::MMI::PointerEvent& pointerEvent) = 0;
    virtual bool ProcessKeyEvent(const OHOS::MMI::KeyEvent& keyEvent) = 0;
    virtual bool ProcessAxisEvent(const OHOS::MMI::AxisEvent& axisEvent) = 0;
    virtual bool ProcessVsyncEvent(uint64_t timeStampNanos) = 0;
    virtual void UpdateViewportConfig(const ViewportConfig& config) = 0;

    // interface for test
    virtual bool ProcessTouchEvent(const OHOS::TouchEvent& touchEvent) = 0;
    virtual void SetRuntime(OHOS::AbilityRuntime::Runtime* runtime) = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_ACE_UI_CONTENT_H
