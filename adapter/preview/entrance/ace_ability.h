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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_ABILITY_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_ABILITY_H

#include <atomic>

#include "flutter/shell/platform/glfw/public/flutter_glfw.h"

#include "adapter/preview/entrance/ace_run_args.h"
#include "core/gestures/touch_event.h"

#ifndef ACE_PREVIEW_EXPORT
#ifdef _WIN32
#define ACE_PREVIEW_EXPORT __declspec(dllexport)
#elif defined(__APPLE__)
#define ACE_PREVIEW_EXPORT __attribute__((visibility("default")))
#endif
#endif // ACE_PREVIEW_EXPORT

namespace OHOS::Ace::Platform {

class ACE_PREVIEW_EXPORT AceAbility {

public:
    static std::unique_ptr<AceAbility> CreateInstance(AceRunArgs& runArgs);

    // Be called in Previewer frontend thread, which is not ACE platform thread.
    static void Stop();
    static bool DispatchTouchEvent(const TouchPoint& event);
    static bool DispatchBackPressedEvent();

    explicit AceAbility(const AceRunArgs& runArgs);
    ~AceAbility();

    void InitEnv();
    void Start();
    void SurfaceChanged(
        const DeviceOrientation& orientation, const int32_t& width, const int32_t& height, const double& resolution);
    std::string GetJSONTree();
    std::string GetDefaultJSONTree();

private:
    void RunEventLoop();

    void SetGlfwWindowController(const FlutterDesktopWindowControllerRef& controller)
    {
        controller_ = controller;
    }

    // flag indicating if the glfw message loop should be running.
    static std::atomic<bool> loopRunning_;

    AceRunArgs runArgs_;
    FlutterDesktopWindowControllerRef controller_ = nullptr;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_ABILITY_H
