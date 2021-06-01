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

#include "adapter/preview/entrance/ace_ability.h"

#include <thread>

#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/ace_container.h"
#include "frameworks/bridge/common/inspector/inspector_client.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"

namespace OHOS::Ace::Platform {

std::atomic<bool> AceAbility::loopRunning_ = true;

namespace {

// JS frontend maintain the page ID self, so it's useless to pass page ID from platform
// layer, neither OpenHarmony or Windows.
constexpr int32_t UNUSED_PAGE_ID = 1;

// Different with mobile, we don't support multi-instances in Windows, because we only want
// preivew UI effect, it doesn't make scense to create multi ability in one process.
constexpr int32_t ACE_INSTANCE_ID = 0;

constexpr char ASSET_PATH_SHARE[] = "share";
#ifdef WINDOWS_PLATFORM
constexpr char DELIMITER[] = "\\";
#else
constexpr char DELIMITER[] = "/";
#endif

#ifdef USE_GLFW_WINDOW
// Screen Density Coefficient/Base Density = Resolution/ppi
constexpr double SCREEN_DENSITY_COEFFICIENT_PHONE = 1080.0 * 160.0 / 480.0;
constexpr double SCREEN_DENSITY_COEFFICIENT_WATCH = 466.0 * 160 / 320.0;
constexpr double SCREEN_DENSITY_COEFFICIENT_TABLE = 2560.0 * 160.0 / 280.0;
constexpr double SCREEN_DENSITY_COEFFICIENT_TV = 3840.0 * 160.0 / 640.0;
#endif
} // namespace

std::unique_ptr<AceAbility> AceAbility::CreateInstance(AceRunArgs& runArgs)
{
    LOGI("Start create AceAbility instance");
    bool initSucceeded = FlutterDesktopInit();
    if (!initSucceeded) {
        LOGE("Could not create window; AceDesktopInit failed.");
        return nullptr;
    }

    AceApplicationInfo::GetInstance().SetLocale(runArgs.language, runArgs.region, runArgs.script, "");

    auto controller = FlutterDesktopCreateWindow(
        runArgs.deviceWidth, runArgs.deviceHeight, runArgs.windowTitle.c_str(), runArgs.onRender);
    auto aceAbility = std::make_unique<AceAbility>(runArgs);
    aceAbility->SetGlfwWindowController(controller);
    return aceAbility;
}

bool AceAbility::DispatchTouchEvent(const TouchPoint& event)
{
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

    std::promise<bool> touchPromise;
    std::future<bool> touchFuture = touchPromise.get_future();
    container->GetTaskExecutor()->PostTask(
        [aceView, event, &touchPromise]() {
            bool isHandled = aceView->HandleTouchEvent(event);
            touchPromise.set_value(isHandled);
        },
        TaskExecutor::TaskType::PLATFORM);
    return touchFuture.get();
}

bool AceAbility::DispatchBackPressedEvent()
{
    LOGI("DispatchBackPressedEvent start ");
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
    container->GetTaskExecutor()->PostTask(
        [container, context, &backPromise]() {
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

AceAbility::AceAbility(const AceRunArgs& runArgs) : runArgs_(runArgs)
{
    SystemProperties::InitDeviceInfo(runArgs_.deviceWidth, runArgs_.deviceHeight,
        runArgs_.orientation == DeviceOrientation::PORTRAIT ? 0 : 1, runArgs_.resolution, runArgs_.isRound);
    SystemProperties::InitDeviceType(runArgs_.deviceType);
    SystemProperties::SetColorMode(runArgs_.colorMode == OHOS::Ace::Platform::ColorMode::DARK ?
        OHOS::Ace::ColorMode::DARK : OHOS::Ace::ColorMode::LIGHT);
    if (runArgs_.formsEnabled) {
        LOGI("CreateContainer with JS_CARD frontend");
        AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::JS_CARD);
    } else {
        LOGI("CreateContainer with JS frontend");
        AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::JS);
    }
}

AceAbility::~AceAbility()
{
    if (controller_) {
        FlutterDesktopDestroyWindow(controller_);
    }
    FlutterDesktopTerminate();
}

std::string GetCustomAssetPath(std::string assetPath)
{
    if (assetPath.empty()) {
        LOGE("AssetPath is null.");
        return std::string();
    }
    std::string customAssetPath;
    if (OHOS::Ace::Framework::EndWith(assetPath, DELIMITER)) {
        assetPath = assetPath.substr(0, assetPath.size() - 1);
    }
    customAssetPath = assetPath.substr(0, assetPath.find_last_of(DELIMITER) + 1);
    return customAssetPath;
}

void AceAbility::InitEnv()
{
    AceContainer::AddAssetPath(
        ACE_INSTANCE_ID, "", { runArgs_.assetPath, GetCustomAssetPath(runArgs_.assetPath).append(ASSET_PATH_SHARE) });

    AceContainer::SetResourcesPathAndThemeStyle(ACE_INSTANCE_ID, runArgs_.resourcesPath,
                                                runArgs_.themeId, runArgs_.colorMode);

    auto view = new FlutterAceView(ACE_INSTANCE_ID);
    AceContainer::SetView(view, runArgs_.resolution, runArgs_.deviceWidth, runArgs_.deviceHeight);
    IdleCallback idleNoticeCallback = [view](int64_t deadline) { view->ProcessIdleEvent(deadline); };
    FlutterDesktopSetIdleCallback(controller_, idleNoticeCallback);

    // Should make it possible to update surface changes by using viewWidth and viewHeight.
    view->NotifySurfaceChanged(runArgs_.deviceWidth, runArgs_.deviceHeight);
    view->NotifyDensityChanged(runArgs_.resolution);
}

void AceAbility::Start()
{
    AceContainer::RunPage(ACE_INSTANCE_ID, UNUSED_PAGE_ID, runArgs_.url, "");
    RunEventLoop();
}

void AceAbility::Stop()
{
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        return;
    }

    container->GetTaskExecutor()->PostTask([]() { loopRunning_ = false; }, TaskExecutor::TaskType::PLATFORM);
}

#ifdef USE_GLFW_WINDOW
void AdaptDeviceType(AceRunArgs& runArgs)
{
    if (runArgs.deviceType == DeviceType::PHONE) {
        runArgs.resolution = runArgs.deviceWidth / SCREEN_DENSITY_COEFFICIENT_PHONE;
    } else if (runArgs.deviceType == DeviceType::WATCH) {
        runArgs.resolution = runArgs.deviceWidth / SCREEN_DENSITY_COEFFICIENT_WATCH;
    } else if (runArgs.deviceType == DeviceType::TABLET) {
        runArgs.resolution = runArgs.deviceWidth / SCREEN_DENSITY_COEFFICIENT_TABLE;
    } else if (runArgs.deviceType == DeviceType::TV) {
        runArgs.resolution = runArgs.deviceWidth / SCREEN_DENSITY_COEFFICIENT_TV;
    } else {
        LOGE("DeviceType not supported");
    }
}
#endif

void AceAbility::RunEventLoop()
{
    while (!FlutterDesktopWindowShouldClose(controller_) && loopRunning_) {
        FlutterDesktopWaitForEvents(controller_);
#ifdef USE_GLFW_WINDOW
        auto window = FlutterDesktopGetWindow(controller_);
        int width;
        int height;
        FlutterDesktopGetFramebufferSize(window, &width, &height);
        if (width != runArgs_.deviceWidth || height != runArgs_.deviceHeight) {
            AdaptDeviceType(runArgs_);
            SurfaceChanged(runArgs_.orientation, width, height, runArgs_.resolution);
        }
#endif
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    loopRunning_ = true;

    // Currently exit loop is only to restart the AceContainer for real-time preivew case.
    // Previewer background thread will release the AceAbility instance and create new one,
    // then call the InitEnv() and Start() again.
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGE("container is null");
        FlutterDesktopDestroyWindow(controller_);
        controller_ = nullptr;
        return;
    }
    auto viewPtr = container->GetAceView();
    AceContainer::DestroyContainer(ACE_INSTANCE_ID);

    FlutterDesktopDestroyWindow(controller_);
    if (viewPtr != nullptr) {
        delete viewPtr;
        viewPtr = nullptr;
    }
    controller_ = nullptr;
}

void AceAbility::SurfaceChanged(
    const DeviceOrientation& orientation, const int32_t& width, const int32_t& height, const double& resolution)
{
    SystemProperties::InitDeviceInfo(
        width, height, orientation == DeviceOrientation::PORTRAIT ? 0 : 1, resolution, runArgs_.isRound);
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGE("container is null, SurfaceChanged failed.");
        return;
    }

    auto viewPtr = container->GetAceView();
    if (viewPtr == nullptr) {
        LOGE("aceView is null, SurfaceChanged failed.");
        return;
    }
    viewPtr->NotifySurfaceChanged(width, height);
    viewPtr->NotifyDensityChanged(resolution);
    runArgs_.orientation = orientation;
    runArgs_.deviceWidth = width;
    runArgs_.deviceHeight = height;
    runArgs_.resolution = resolution;
}

std::string AceAbility::GetJSONTree()
{
    std::string jsonTreeStr;
    OHOS::Ace::Framework::InspectorClient::GetInstance().AssembleJSONTreeStr(jsonTreeStr);
    return jsonTreeStr;
}

std::string AceAbility::GetDefaultJSONTree()
{
    std::string defaultJsonTreeStr;
    OHOS::Ace::Framework::InspectorClient::GetInstance().AssembleDefaultJSONTreeStr(defaultJsonTreeStr);
    return defaultJsonTreeStr;
}

} // namespace OHOS::Ace::Platform
