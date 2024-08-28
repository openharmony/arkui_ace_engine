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

#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

#include "jsapp/rich/external/EventHandler.h"
#include "previewer/include/window.h"

#include "adapter/preview/entrance/ace_ability.h"
#include "adapter/preview/entrance/ace_run_args.h"
#include "adapter/preview/entrance/samples/event_adapter.h"
#include "base/log/log.h"
#include "base/utils/device_config.h"
#include "base/utils/utils.h"
#include "adapter/preview/entrance/ace_preview_helper.h"

namespace {
constexpr int MAX_ARGS_COUNT = 2;
constexpr char MODEL_STAGE[] = "stage";
// card default width and height:
// 2*1 (150*54)
// 2*2 (150*150)
// 4*2 (320*150)
// 4*4 (320*344)
constexpr int32_t CARD_DEFAULT_WIDTH = 320;
constexpr int32_t CARD_DEFAULT_HEIGHT = 344;
#ifdef MAC_PLATFORM
const std::string assetPathJs = "/Volumes/SSD2T/daily-test/preview/js/default_card";
const std::string assetPathEtsStage = "/Volumes/SSD2T/daily-test/preview/js/default_card_stage/js";
const std::string appResourcesPath = "/Volumes/SSD2T/daily-test/preview/js/AppResources";
const std::string appResourcesPathStage = "/Volumes/SSD2T/daily-test/preview/js/default_card_stage";
const std::string systemResourcesPath = "/Volumes/SSD2T/daily-test/preview/js/SystemResources";
constexpr double density = 2;
#elif WINDOWS_PLATFORM
const std::string assetPathJs = "D:\\Workspace\\preview\\js\\default_card";
const std::string assetPathEtsStage = "D:\\Workspace\\preview\\js\\default_card_stage\\ets";
const std::string appResourcesPath = "D:\\Workspace\\preview\\js\\AppResources\\assets\\entry";
const std::string appResourcesPathStage = "D:\\Workspace\\preview\\js\\default_card_stage";
const std::string systemResourcesPath = "D:\\Workspace\\preview\\js\\SystemResources\\assets\\entry";
constexpr double density = 1;
#else
const std::string assetPathJs = "/home/ubuntu/demo/preview/js/default_card";
const std::string assetPathEtsStage = "/home/ubuntu/demo/preview/js/default_card_stage";
const std::string appResourcesPath = "/home/ubuntu/demo/preview/js/AppResources";
const std::string appResourcesPathStage = "/home/ubuntu/demo/preview/js/default_card_stage";
const std::string systemResourcesPath = "/home/ubuntu/demo/preview/js/SystemResources";
constexpr double density = 2;
#endif
const std::string pageProfile = "form_config";
const std::string jsCardUrl = "widget/pages/index/index";
const std::string eTSCardUrl = "./ets/widget/pages/card.ets";

auto&& renderCallback = [](
    const void*, const size_t bufferSize, const int32_t width, const int32_t height, const uint64_t) -> bool {
    LOGI("OnRender: bufferSize = %{public}zu, [width, height] = [%{public}d, %{public}d]", bufferSize, width, height);
    return true;
};

auto&& pageCallback = [](const std::string currentPagePath) -> bool {
    LOGI("OnRouterChange: current page: %s", currentPagePath.c_str());
    return true;
};

} // namespace

int main(int argc, const char* argv[])
{
    OHOS::Ace::Platform::AceRunArgs args = {
        .assetPath = assetPathJs,
        .systemResourcesPath = systemResourcesPath,
        .appResourcesPath = appResourcesPath,
        .deviceConfig.density = density,
        .deviceConfig.colorMode = OHOS::Ace::ColorMode::DARK,
        .url = jsCardUrl,
        .windowTitle = "ACE card",
        .deviceWidth = CARD_DEFAULT_WIDTH,
        .deviceHeight = CARD_DEFAULT_HEIGHT,
        .formsEnabled = true,
        .onRender = std::move(renderCallback),
        .onRouterChange = std::move(pageCallback),
    };
    if (argc == MAX_ARGS_COUNT && !std::strcmp(argv[1], MODEL_STAGE)) {
        args.assetPath = assetPathEtsStage;
        args.appResourcesPath = appResourcesPathStage;
        args.aceVersion = OHOS::Ace::Platform::AceVersion::ACE_2_0;
        args.projectModel = OHOS::Ace::Platform::ProjectModel::STAGE;
        args.pageProfile = pageProfile;
        args.url = eTSCardUrl;
    }

    // Initialize and create the glfw window.
    auto ctx = OHOS::Rosen::GlfwRenderContext::GetGlobal();
    if (!ctx->Init()) {
        LOGI("Failed to initialize the glfw.");
        return -1;
    }
    ctx->CreateGlfwWindow(args.deviceWidth, args.deviceHeight, true);
    OHOS::Ace::Sample::EventAdapter::GetInstance().Initialize(ctx);
    OHOS::Ace::Platform::AcePreviewHelper::GetInstance()->
        SetCallbackOfPostTask(OHOS::AppExecFwk::EventHandler::PostTask);
    OHOS::Ace::Platform::AcePreviewHelper::GetInstance()->
        SetCallbackOfIsCurrentRunnerThread(OHOS::AppExecFwk::EventHandler::IsCurrentRunnerThread);

    // Create the ace ability
    auto ability = OHOS::Ace::Platform::AceAbility::CreateInstance(args);
    CHECK_NULL_RETURN(ability, -1);

    auto&& keyEventCallback = [&ability](
                                  const std::shared_ptr<KeyEvent>& keyEvent) { ability->OnInputEvent(keyEvent); };
    OHOS::Ace::Sample::EventAdapter::GetInstance().RegisterKeyEventCallback(keyEventCallback);

    auto&& pointerEventCallback = [&ability](const std::shared_ptr<PointerEvent>& pointerEvent) {
        ability->OnInputEvent(pointerEvent);
    };
    OHOS::Ace::Sample::EventAdapter::GetInstance().RegisterPointerEventCallback(pointerEventCallback);

    auto&& inspectorCallback = [&ability]() {
        constexpr char FILE_NAME[] = "InspectorTree.json";
        std::string jsonTreeStr = ability->GetJSONTree();
        std::ofstream fileCleaner(FILE_NAME, std::ios_base::out);
        std::ofstream fileWriter(FILE_NAME, std::ofstream::app);
        fileWriter << jsonTreeStr;
        fileWriter << std::endl;
        fileWriter.close();
    };
    OHOS::Ace::Sample::EventAdapter::GetInstance().RegisterInspectorCallback(inspectorCallback);

    OHOS::Rosen::WMError errCode;
    OHOS::sptr<OHOS::Rosen::WindowOption> sp = nullptr;
    auto window = OHOS::Rosen::Window::Create("previewer", sp, nullptr, errCode);
    window->CreateSurfaceNode("preview_surface", args.onRender);
    ability->SetWindow(window);

    ability->InitEnv();
    LOGI("Ace initialize done. run event loop now");
    while (!ctx->WindowShouldClose()) {
        OHOS::AppExecFwk::EventHandler::Run();
        ctx->PollEvents();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    LOGI("Successfully exit the application.");
    return 0;
}
