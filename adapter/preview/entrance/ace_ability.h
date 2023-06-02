/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
#include <thread>

#ifdef ENABLE_ROSEN_BACKEND
#include "glfw_render_context.h"
#else
#include "flutter/shell/platform/glfw/public/flutter_glfw.h"
#endif

#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/external/window/window.h"
#include "base/utils/macros.h"
#include "adapter/preview/external/multimodalinput/key_event.h"
#include "adapter/preview/external/multimodalinput/axis_event.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "adapter/preview/entrance/clipboard/clipboard_impl.h"
#include "adapter/preview/entrance/clipboard/clipboard_proxy_impl.h"

namespace OHOS::Ace::Platform {

struct ConfigChanges {
    bool watchLocale = false;
    bool watchLayout = false;
    bool watchFontSize = false;
    bool watchOrientation = false;
    bool watchDensity = false;
};

struct SystemParams {
    int32_t deviceWidth { 0 };
    int32_t deviceHeight { 0 };
    bool isRound = false;
    double density { 1.0 };
    std::string language = "zh";
    std::string region = "CN";
    std::string script = "";
    OHOS::Ace::DeviceType deviceType { DeviceType::PHONE };
    OHOS::Ace::ColorMode colorMode { ColorMode::LIGHT };
    OHOS::Ace::DeviceOrientation orientation { DeviceOrientation::PORTRAIT };
};

#ifndef ENABLE_ROSEN_BACKEND
using GlfwController = FlutterDesktopWindowControllerRef;
#else
using GlfwController = std::shared_ptr<OHOS::Rosen::GlfwRenderContext>;
#endif

class ACE_FORCE_EXPORT_WITH_PREVIEW AceAbility {
public:
    explicit AceAbility(const AceRunArgs& runArgs);
    ~AceAbility();

    // Be called in Previewer frontend thread, which is not ACE platform thread.    
    static std::unique_ptr<AceAbility> CreateInstance(AceRunArgs& runArgs);    
    void InitEnv();    
    void Start();
    static void Stop();
    void InitializeClipboard(CallbackSetClipboardData cbkSetData, CallbackGetClipboardData cbkGetData) const;
    void OnBackPressed() const;
    bool OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const;
    bool OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const;
    bool OnInputMethodEvent(const unsigned int codePoint) const;

    void OnConfigurationChanged(const DeviceConfig& newConfig);
    void SurfaceChanged(
        const DeviceOrientation& orientation, const double& resolution, int32_t& width, int32_t& height);
    void ReplacePage(const std::string& url, const std::string& params);
    void LoadDocument(const std::string& url, const std::string& componentName, SystemParams& systemParams);

    std::string GetJSONTree();
    std::string GetDefaultJSONTree();
    bool OperateComponent(const std::string& attrsJson);
    GlfwController GetGlfwWindowController()
    {
        return controller_;
    }

    void SetWindow(sptr<OHOS::Rosen::Window> rsWindow)
    {
        rsWindow_ = rsWindow;
    }

    sptr<OHOS::Rosen::Window> GetWindow()
    {
        return rsWindow_;
    }

private:
    void RunEventLoop();

    void SetConfigChanges(const std::string& configChanges);

    void SetGlfwWindowController(const GlfwController &controller)
    {
        controller_ = controller;
    }

    // flag indicating if the glfw message loop should be running.
    static std::atomic<bool> loopRunning_;
    AceRunArgs runArgs_;
    ConfigChanges configChanges_;
    GlfwController controller_ = nullptr;
    sptr<OHOS::Rosen::Window> rsWindow_;
};

} // namespace OHOS::Ace::Platform

#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_ACE_ABILITY_H
