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

#include "adapter/preview/entrance/ace_ability.h"
#include "adapter/preview/entrance/ace_view_preview.h"

#ifdef INIT_ICU_DATA_PATH
#include "unicode/putil.h"
#endif

#include <ui/rs_surface_node.h>
#include <ui/rs_ui_director.h>

#include "include/core/SkFontMgr.h"
#include "previewer/include/window.h"

#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/ace_container.h"
#include "adapter/preview/entrance/event_dispatcher.h"
#include "adapter/preview/entrance/rs_dir_asset_provider.h"
#include "adapter/preview/external/ability/stage/stage_context.h"
#include "adapter/preview/inspector/inspector_client.h"
#include "core/common/resource/resource_configuration.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"
#include "frameworks/core/common/ace_engine.h"
#ifdef COMPONENT_TEST_ENABLED
#include "frameworks/component_test/test_config.h"
#endif // COMPONENT_TEST_ENABLED

namespace OHOS::Ace::Platform {
namespace {

constexpr char ASSET_PATH_SHARE[] = "share";
#ifdef WINDOWS_PLATFORM
constexpr char DELIMITER[] = "\\";
constexpr char ASSET_PATH_SHARE_STAGE[] = "resources\\base\\profile";
#else
constexpr char DELIMITER[] = "/";
constexpr char ASSET_PATH_SHARE_STAGE[] = "resources/base/profile";
#endif

void SetFontMgrConfig(const std::string& containerSdkPath)
{
    // To check if use ohos or container fonts.
    std::string runtimeOS = "OHOS_Container";
    std::string containerFontBasePath = containerSdkPath + DELIMITER + "resources" + DELIMITER + "fonts" + DELIMITER;
    RSDirAssetProvider dirAsset(containerFontBasePath);
    std::vector<std::string> fileList;
    dirAsset.GetAssetList("", fileList);
    if (containerSdkPath.empty() || fileList.empty()) {
        runtimeOS = "OHOS";
        containerFontBasePath = "";
    }
    SkFontMgr::SetFontMgrConfig(runtimeOS, containerFontBasePath);
}

std::string GetCustomAssetPath(std::string assetPath)
{
    if (assetPath.empty()) {
        LOGW("AssetPath is null.");
        return std::string();
    }
    std::string customAssetPath;
    if (OHOS::Ace::Framework::EndWith(assetPath, DELIMITER)) {
        assetPath = assetPath.substr(0, assetPath.size() - 1);
    }
    customAssetPath = assetPath.substr(0, assetPath.find_last_of(DELIMITER) + 1);
    return customAssetPath;
}

inline void DumpAceRunArgs(const AceRunArgs& runArgs)
{
#ifdef ACE_DEBUG
    LOGI("runArgs.pageProfile: %{private}s", runArgs.pageProfile.c_str());
    LOGI("runArgs.asset: %{private}s", runArgs.assetPath.c_str());
    LOGI("runArgs.systemResources: %{private}s", runArgs.systemResourcesPath.c_str());
    LOGI("runArgs.appResources: %{private}s", runArgs.appResourcesPath.c_str());
    LOGI("runArgs.themeId: %{private}u", runArgs.themeId);
    LOGI("runArgs.deviceConfig.orientation: %{private}d", static_cast<int>(runArgs.deviceConfig.orientation));
    LOGI("runArgs.deviceConfig.density: %{private}lf", runArgs.deviceConfig.density);
    LOGI("runArgs.deviceConfig.deviceType: %{private}d", static_cast<int>(runArgs.deviceConfig.deviceType));
    LOGI("runArgs.deviceConfig.fontRatio: %{private}lf", runArgs.deviceConfig.fontRatio);
    LOGI("runArgs.deviceConfig.colorMode: %{private}d", static_cast<int>(runArgs.deviceConfig.colorMode));
    LOGI("runArgs.url: %{private}s", runArgs.url.c_str());
    LOGI("runArgs.windowTitle: %{private}s", runArgs.windowTitle.c_str());
    LOGI("runArgs.isRound: %{private}s", runArgs.isRound ? "true" : "false");
    LOGI("runArgs.viewWidth: %{private}d", runArgs.viewWidth);
    LOGI("runArgs.viewHeight: %{private}d", runArgs.viewHeight);
    LOGI("runArgs.deviceWidth: %{private}d", runArgs.deviceWidth);
    LOGI("runArgs.deviceHeight: %{private}d", runArgs.deviceHeight);
#endif
}

} // namespace

NG::SafeAreaInsets ConvertAvoidArea(const OHOS::Rosen::AvoidArea& avoidArea)
{
    return NG::SafeAreaInsets({ avoidArea.leftRect_.posX_, avoidArea.leftRect_.posX_ + avoidArea.leftRect_.width_ },
        { avoidArea.topRect_.posY_, avoidArea.topRect_.posY_ + avoidArea.topRect_.height_ },
        { avoidArea.rightRect_.posX_, avoidArea.rightRect_.posX_ + avoidArea.rightRect_.width_ },
        { avoidArea.bottomRect_.posY_, avoidArea.bottomRect_.posY_ + avoidArea.bottomRect_.height_ });
}

NG::SafeAreaInsets GetViewSafeAreaByType(OHOS::Rosen::AvoidAreaType type, sptr<OHOS::Rosen::Window> rsWindow)
{
    CHECK_NULL_RETURN(rsWindow, {});
    Rosen::AvoidArea avoidArea;
    Rosen::WMError ret = rsWindow->GetAvoidAreaByType(type, avoidArea);
    if (ret == Rosen::WMError::WM_OK) {
        auto safeAreaInsets = ConvertAvoidArea(avoidArea);
        LOGI("SafeArea get success, area type is:%{public}d insets area is:%{public}s", static_cast<int32_t>(type),
            safeAreaInsets.ToString().c_str());
        return safeAreaInsets;
    }
    return {};
}

class IIgnoreViewSafeAreaListenerPreview  : public OHOS::Rosen::IIgnoreViewSafeAreaListener {
public:
    explicit IIgnoreViewSafeAreaListenerPreview(int32_t instanceId) : instanceId_(instanceId) {}
    ~IIgnoreViewSafeAreaListenerPreview() = default;

    void SetIgnoreViewSafeArea(bool ignoreViewSafeArea)
    {
        LOGD("[instanceId_:%{public}d]: SetIgnoreViewSafeArea:%{public}u", instanceId_, ignoreViewSafeArea);
        auto container = AceEngine::Get().GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipelineContext = container->GetPipelineContext();
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostSyncTask(
            [&pipelineContext, container, ignoreSafeArea = ignoreViewSafeArea]() {
                pipelineContext->SetIgnoreViewSafeArea(ignoreSafeArea);
            },
            TaskExecutor::TaskType::UI, "ArkUISetIgnoreViewSafeArea");
    }

private:
    int32_t instanceId_ = -1;
};

class AvoidAreaChangedListenerPreview : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AvoidAreaChangedListenerPreview(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvoidAreaChangedListenerPreview() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type)
    {
        LOGD("Avoid area changed, type:%{public}d, topRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height:%{public}d; bottomRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height:%{public}d",
            type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
            (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
            (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_);
        auto container = Platform::AceContainer::GetContainerInstance(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipeline = container->GetPipelineContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
            systemSafeArea_ = ConvertAvoidArea(avoidArea);
        } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
            navigationBar_ = ConvertAvoidArea(avoidArea);
        } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT) {
            cutoutSafeArea_ = ConvertAvoidArea(avoidArea);
        }
        auto safeArea = systemSafeArea_;
        auto navSafeArea = navigationBar_;
        auto cutoutSafeArea = cutoutSafeArea_;
        taskExecutor->PostTask(
            [pipeline, safeArea, navSafeArea, cutoutSafeArea, type, avoidArea] {
                if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
                    pipeline->UpdateSystemSafeArea(safeArea);
                } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
                    pipeline->UpdateNavSafeArea(navSafeArea);
                } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT && pipeline->GetUseCutout()) {
                    pipeline->UpdateCutoutSafeArea(cutoutSafeArea);
                }
                // for ui extension component
                pipeline->UpdateOriginAvoidArea(avoidArea, static_cast<uint32_t>(type));
            },
            TaskExecutor::TaskType::UI, "ArkUIUpdateOriginAvoidArea");
    }

private:
    NG::SafeAreaInsets systemSafeArea_;
    NG::SafeAreaInsets navigationBar_;
    NG::SafeAreaInsets cutoutSafeArea_;
    int32_t instanceId_ = -1;
};

AceAbility::AceAbility(const AceRunArgs& runArgs) : runArgs_(runArgs)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        Container::UpdateCurrent(ACE_INSTANCE_ID);
    });
    SystemProperties::SetExtSurfaceEnabled(!runArgs.containerSdkPath.empty());
    SystemProperties::InitDeviceInfo(runArgs.deviceWidth, runArgs.deviceHeight,
        runArgs.deviceConfig.orientation == DeviceOrientation::PORTRAIT ? 0 : 1, runArgs.deviceConfig.density,
        runArgs.isRound);
    SystemProperties::InitDeviceType(runArgs.deviceConfig.deviceType);
    SystemProperties::SetColorMode(runArgs.deviceConfig.colorMode);
    InitializeAppInfo();
    if (runArgs_.aceVersion == AceVersion::ACE_1_0) {
        if (runArgs_.formsEnabled) {
            LOGI("CreateContainer with JS_CARD frontend");
            AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::JS_CARD, false);
        } else {
            LOGI("CreateContainer with JS frontend");
            AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::JS, false);
        }
    } else if (runArgs_.aceVersion == AceVersion::ACE_2_0) {
        if (runArgs_.formsEnabled) {
            LOGI("CreateContainer with ETS_CARD frontend");
            AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::ETS_CARD, useNewPipeline_);
        } else {
            LOGI("CreateContainer with JSDECLARATIVE frontend");
            AceContainer::CreateContainer(ACE_INSTANCE_ID, FrontendType::DECLARATIVE_JS, useNewPipeline_);
        }
    } else {
        LOGW("UnKnown frontend type");
    }
    AceContainer::SetComponentModeFlag(runArgs.isComponentMode);
    SetConfigChanges(runArgs.configChanges);
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    container->SetContainerSdkPath(runArgs.containerSdkPath);
    container->SetInstallationFree(installationFree_);
    container->SetLabelId(labelId_);
    auto config = container->GetResourceConfiguration();
    config.SetDeviceType(SystemProperties::GetDeviceType());
    config.SetOrientation(SystemProperties::GetDeviceOrientation());
    config.SetDensity(SystemProperties::GetResolution());
    config.SetColorMode(SystemProperties::GetColorMode());
    config.SetFontRatio(runArgs.deviceConfig.fontRatio);
    container->SetResourceConfiguration(config);
    container->SetBundleName(bundleName_);
    container->SetModuleName(moduleName_);
    container->SetApiTargetVersion(AceApplicationInfo::GetInstance().GetApiTargetVersion());
    InitializeClipboard();
}

AceAbility::~AceAbility()
{
    AceContainer::DestroyContainer(ACE_INSTANCE_ID);
}

void AceAbility::SetMockModuleList(const std::map<std::string, std::string>& mockJsonInfo)
{
    // only support the stage model
    if (runArgs_.projectModel == ProjectModel::STAGE) {
        auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
        CHECK_NULL_VOID(container);
        container->SetMockModuleList(mockJsonInfo);
    }
}

std::unique_ptr<AceAbility> AceAbility::CreateInstance(AceRunArgs& runArgs)
{
    DumpAceRunArgs(runArgs);
    LOGI("Start create AceAbility instance");
#ifdef INIT_ICU_DATA_PATH
    std::string icuPath = ".";
    u_setDataDirectory(icuPath.c_str());
#endif
    AceApplicationInfo::GetInstance().SetLocale(runArgs.language, runArgs.region, runArgs.script, "");
    SetFontMgrConfig(runArgs.containerSdkPath);
    EventDispatcher::GetInstance().Initialize();
    auto aceAbility = std::make_unique<AceAbility>(runArgs);
    return aceAbility;
}

void AceAbility::InitEnv()
{
    std::vector<std::string> paths;
    paths.push_back(runArgs_.assetPath);
    std::string appResourcesPath(runArgs_.appResourcesPath);
    if (!OHOS::Ace::Framework::EndWith(appResourcesPath, DELIMITER)) {
        appResourcesPath.append(DELIMITER);
    }
    if (runArgs_.projectModel == ProjectModel::STAGE) {
        // eTS Card
        if (runArgs_.aceVersion == AceVersion::ACE_2_0 && runArgs_.formsEnabled) {
            paths.push_back(runArgs_.assetPath + DELIMITER + "ets");
        }
        paths.push_back(appResourcesPath);
        paths.push_back(appResourcesPath + ASSET_PATH_SHARE_STAGE);
    } else {
        paths.push_back(GetCustomAssetPath(runArgs_.assetPath) + ASSET_PATH_SHARE);
    }
    if (!runArgs_.containerSdkPath.empty()) {
        paths.push_back(runArgs_.containerSdkPath);
    }
    AceContainer::AddAssetPath(ACE_INSTANCE_ID, "", paths);
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    if (runArgs_.projectModel == ProjectModel::STAGE) {
        auto pkgcontextinfo = Referenced::MakeRefPtr<StagePkgContextInfo>();
        pkgcontextinfo->SetPkgNameList(runArgs_.packageNameList);
        pkgcontextinfo->SetPkgContextInfoAndAliasMap(runArgs_.pkgContextInfoJsonStringMap);
        container->SetPkgContextInfo(pkgcontextinfo);
        if (runArgs_.formsEnabled) {
            container->SetStageCardConfig(runArgs_.pageProfile, runArgs_.url);
        } else {
            container->SetPageProfile((runArgs_.pageProfile.empty() ? "" : runArgs_.pageProfile + ".json"));
        }
    }
    AceContainer::SetResourcesPathAndThemeStyle(ACE_INSTANCE_ID, runArgs_.systemResourcesPath,
        runArgs_.containerSdkPath, runArgs_.appResourcesPath, runArgs_.themeId, runArgs_.deviceConfig.colorMode);

    auto view = AceViewPreview::CreateView(ACE_INSTANCE_ID);
    auto window = GetWindow();
    avoidAreaChangedListener_ = new AvoidAreaChangedListenerPreview(ACE_INSTANCE_ID);
    window->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
    ignoreViewSafeAreaListener_ = new IIgnoreViewSafeAreaListenerPreview(ACE_INSTANCE_ID);
    window->RegisterIgnoreViewSafeAreaListener(ignoreViewSafeAreaListener_);
    UIEnvCallback callback = [window, id = ACE_INSTANCE_ID](const OHOS::Ace::RefPtr<PipelineContext>& context) mutable {
        CHECK_NULL_VOID(context);
        CHECK_NULL_VOID(window);
        auto director = OHOS::Rosen::RSUIDirector::Create();
        CHECK_NULL_VOID(director);
        director->SetRSSurfaceNode(window->GetSurfaceNode());
        auto container = AceContainer::GetContainerInstance(id);
        CHECK_NULL_VOID(container);
        auto func = [taskExecutor = container->GetTaskExecutor(), id](
            const std::function<void()>& task, uint32_t delay) {
            CHECK_NULL_VOID(taskExecutor);
            ContainerScope scope(id);
            taskExecutor->PostDelayedTask(
                task, TaskExecutor::TaskType::UI, delay, "ArkUIRenderServiceTask", PriorityType::HIGH);
        };
        director->SetUITaskRunner(func, id);
        director->Init();
        context->SetRSUIDirector(director);
    };

    if (runArgs_.aceVersion == AceVersion::ACE_2_0) {
        AceContainer::SetView(
            view, window, runArgs_.deviceConfig.density, runArgs_.deviceWidth, runArgs_.deviceHeight, callback);
        AceContainer::RunPage(ACE_INSTANCE_ID, runArgs_.url, "");
    } else {
        AceContainer::RunPage(ACE_INSTANCE_ID, runArgs_.url, "");
        AceContainer::SetView(
            view, window, runArgs_.deviceConfig.density, runArgs_.deviceWidth, runArgs_.deviceHeight, callback);
    }
    // Drive the native engine with the platform thread.
    container->RunNativeEngineLoop();
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        LOGI("Set MinPlatformVersion to %{public}d", compatibleVersion_);
        pipelineContext->SetMinPlatformVersion(compatibleVersion_);
        pipelineContext->SetDisplayWindowRectInfo(
            Rect(Offset(0.0f, 0.0f), Size(runArgs_.deviceWidth, runArgs_.deviceHeight)));
    }
    container->InitializeAppConfig(runArgs_.assetPath, bundleName_, moduleName_, compileMode_);
    pipelineContext->UpdateSystemSafeArea(GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_SYSTEM, window));
    if (pipelineContext->GetUseCutout()) {
        pipelineContext->UpdateCutoutSafeArea(GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_CUTOUT, window));
    }
    pipelineContext->UpdateNavSafeArea(GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR, window));
    AceContainer::AddRouterChangeCallback(ACE_INSTANCE_ID, runArgs_.onRouterChange);
    OHOS::Ace::Framework::InspectorClient::GetInstance().RegisterFastPreviewErrorCallback(runArgs_.onError);
    // Should make it possible to update surface changes by using viewWidth and viewHeight.
    view->NotifySurfaceChanged(runArgs_.deviceWidth, runArgs_.deviceHeight);
    view->NotifyDensityChanged(runArgs_.deviceConfig.density);
}

void AceAbility::InitializeClipboard() const
{
    ClipboardProxy::GetInstance()->SetDelegate(std::make_unique<Platform::ClipboardProxyImpl>());
}

void AceAbility::OnBackPressed() const
{
    LOGI("Process Back Pressed Event");
    EventDispatcher::GetInstance().DispatchBackPressedEvent();
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const
{
    return EventDispatcher::GetInstance().DispatchTouchEvent(pointerEvent);
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const
{
    return EventDispatcher::GetInstance().DispatchKeyEvent(keyEvent);
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const
{
    return false;
}

bool AceAbility::OnInputMethodEvent(const unsigned int codePoint) const
{
    return EventDispatcher::GetInstance().DispatchInputMethodEvent(codePoint);
}

void AceAbility::InitializeAppInfo()
{
    RefPtr<Context> context =
        Context::CreateContext(runArgs_.projectModel == ProjectModel::STAGE, runArgs_.appResourcesPath);
    if (runArgs_.projectModel == ProjectModel::STAGE) {
        auto stageContext = AceType::DynamicCast<StageContext>(context);
        CHECK_NULL_VOID(stageContext);
        auto appInfo = stageContext->GetAppInfo();
        CHECK_NULL_VOID(appInfo);
        auto hapModuleInfo = stageContext->GetHapModuleInfo();
        CHECK_NULL_VOID(hapModuleInfo);
        bundleName_ = appInfo->GetBundleName();
        moduleName_ = hapModuleInfo->GetModuleName();
        compileMode_ = hapModuleInfo->GetCompileMode();
        compatibleVersion_ = appInfo->GetMinAPIVersion();
        auto targetVersion = appInfo->GetTargetAPIVersion();
        AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(targetVersion));
        auto releaseType = appInfo->GetApiReleaseType();
        bool enablePartialUpdate = hapModuleInfo->GetPartialUpdateFlag();
        // only app should have menubar, card don't need
        if (!runArgs_.formsEnabled) {
            installationFree_ = appInfo->IsInstallationFree();
            labelId_ = hapModuleInfo->GetLabelId();
        }
        useNewPipeline_ = AceNewPipeJudgement::QueryAceNewPipeEnabledStage(
            "", compatibleVersion_, targetVersion, releaseType, !enablePartialUpdate);
    } else {
        auto faContext = AceType::DynamicCast<FaContext>(context);
        CHECK_NULL_VOID(faContext);
        auto appInfo = faContext->GetAppInfo();
        CHECK_NULL_VOID(appInfo);
        auto hapModuleInfo = faContext->GetHapModuleInfo();
        CHECK_NULL_VOID(hapModuleInfo);
        bundleName_ = appInfo->GetBundleName();
        compatibleVersion_ = appInfo->GetMinAPIVersion();
        auto targetVersion = appInfo->GetTargetAPIVersion();
        auto releaseType = appInfo->GetApiReleaseType();
        useNewPipeline_ =
            AceNewPipeJudgement::QueryAceNewPipeEnabledFA("", compatibleVersion_, targetVersion, releaseType);
    }
#ifdef COMPONENT_TEST_ENABLED
    if (runArgs_.isComponentTestMode && runArgs_.componentTestConfig != "") {
        ComponentTest::ParseComponentTestConfig(runArgs_.componentTestConfig);
    }
#endif // COMPONENT_TEST_ENABLED
}

void AceAbility::SetConfigChanges(const std::string& configChanges)
{
    if (configChanges == "") {
        return;
    }
    std::vector<std::string> configChangesSplitter;
    OHOS::Ace::StringUtils::StringSplitter(configChanges, ',', configChangesSplitter);
    for (const auto& singleConfig : configChangesSplitter) {
        if (singleConfig == "locale") {
            configChanges_.watchLocale = true;
            continue;
        } else if (singleConfig == "layout") {
            configChanges_.watchLayout = true;
            continue;
        } else if (singleConfig == "fontSize") {
            configChanges_.watchFontSize = true;
            continue;
        } else if (singleConfig == "orientation") {
            configChanges_.watchOrientation = true;
            continue;
        } else if (singleConfig == "density") {
            configChanges_.watchDensity = true;
            continue;
        } else {
            LOGW("unsupported config %{public}s", singleConfig.c_str());
        }
    }
}

void AceAbility::OnConfigurationChanged(const DeviceConfig& newConfig)
{
    if (newConfig.colorMode == runArgs_.deviceConfig.colorMode) {
        return;
    }
    int32_t width = runArgs_.deviceWidth;
    int32_t height = runArgs_.deviceHeight;
    SurfaceChanged(runArgs_.deviceConfig.orientation, runArgs_.deviceConfig.density, width, height);
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGW("container is null, change configuration failed.");
        return;
    }
    container->UpdateDeviceConfig(newConfig);
    runArgs_.deviceConfig.colorMode = newConfig.colorMode;
    if (container->GetType() == FrontendType::DECLARATIVE_JS) {
        container->NativeOnConfigurationUpdated(ACE_INSTANCE_ID);
    }
}

void AceAbility::SurfaceChanged(
    const DeviceOrientation& orientation, const double& resolution, int32_t& width, int32_t& height,
    WindowSizeChangeReason type)
{
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    auto viewPtr = AceType::DynamicCast<AceViewPreview>(container->GetAceView());
    CHECK_NULL_VOID(viewPtr);
    // Need to change the window resolution and then change the rendering resolution. Otherwise, the image may not adapt
    // to the new window after the window is modified.
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);
    context->SetDisplayWindowRectInfo(Rect(Offset(0, 0), Size(width, height)));
    SystemProperties::InitDeviceInfo(
        width, height, orientation == DeviceOrientation::PORTRAIT ? 0 : 1, resolution, runArgs_.isRound);
    DeviceConfig deviceConfig = runArgs_.deviceConfig;
    deviceConfig.orientation = orientation;
    deviceConfig.density = resolution;
    container->UpdateDeviceConfig(deviceConfig);
    viewPtr->NotifyDensityChanged(resolution);
    viewPtr->NotifySurfaceChanged(width, height, type);
    if ((orientation != runArgs_.deviceConfig.orientation && configChanges_.watchOrientation) ||
        (resolution != runArgs_.deviceConfig.density && configChanges_.watchDensity) ||
        ((width != runArgs_.deviceWidth || height != runArgs_.deviceHeight) && configChanges_.watchLayout)) {
        container->NativeOnConfigurationUpdated(ACE_INSTANCE_ID);
    }
    if (orientation != runArgs_.deviceConfig.orientation || resolution != runArgs_.deviceConfig.density) {
        container->NotifyConfigurationChange(false, ConfigurationChange({ false, false, true }));
    }
    runArgs_.deviceConfig.orientation = orientation;
    runArgs_.deviceConfig.density = resolution;
    runArgs_.deviceWidth = width;
    runArgs_.deviceHeight = height;
}

void AceAbility::ReplacePage(const std::string& url, const std::string& params)
{
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    container->GetFrontend()->ReplacePage(url, params);
}

void AceAbility::LoadDocument(const std::string& url, const std::string& componentName, SystemParams& systemParams)
{
    LOGI("Component Preview start:%{public}s, ", componentName.c_str());
    AceApplicationInfo::GetInstance().ChangeLocale(systemParams.language, systemParams.region);
    runArgs_.isRound = systemParams.isRound;
    SurfaceChanged(systemParams.orientation, systemParams.density, systemParams.deviceWidth, systemParams.deviceHeight);
    DeviceConfig deviceConfig = {
        .orientation = systemParams.orientation,
        .density = systemParams.density,
        .deviceType = systemParams.deviceType,
        .colorMode = systemParams.colorMode,
    };
    OnConfigurationChanged(deviceConfig);
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_VOID(container);
    container->LoadDocument(url, componentName);
    LOGI("Component Preview end");
}

std::string AceAbility::GetJSONTree()
{
    LOGI("Inspector start");
    std::string jsonTreeStr;
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, "");
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, "");
    taskExecutor->PostSyncTask(
        [&jsonTreeStr] { OHOS::Ace::Framework::InspectorClient::GetInstance().AssembleJSONTreeStr(jsonTreeStr); },
        TaskExecutor::TaskType::UI, "ArkUIGetJsonTreeStr");
    LOGI("Inspector end");
    return jsonTreeStr;
}

std::string AceAbility::GetDefaultJSONTree()
{
    std::string defaultJsonTreeStr;
    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    CHECK_NULL_RETURN(container, "");
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, "");
    taskExecutor->PostSyncTask(
        [&defaultJsonTreeStr] {
            OHOS::Ace::Framework::InspectorClient::GetInstance().AssembleDefaultJSONTreeStr(defaultJsonTreeStr);
        },
        TaskExecutor::TaskType::UI, "ArkUIGetDefaultJsonTreeStr");
    return defaultJsonTreeStr;
}

bool AceAbility::OperateComponent(const std::string& attrsJson)
{
    LOGI("Fast Preview start");
    auto root = JsonUtil::ParseJsonString(attrsJson);
    if (!root || !root->IsValid()) {
        LOGE("Fast Preview failed: the attrsJson is illegal json format");
        return false;
    }

    auto container = AceContainer::GetContainerInstance(ACE_INSTANCE_ID);
    if (!container) {
        LOGE("Fast Preview failed: container is null");
        return false;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("Fast Preview failed: taskExecutor is null");
        return false;
    }
    taskExecutor->PostTask(
        [attrsJson, instanceId = ACE_INSTANCE_ID] {
            ContainerScope scope(instanceId);
            bool result = OHOS::Ace::Framework::InspectorClient::GetInstance().OperateComponent(attrsJson);
            if (!result) {
                OHOS::Ace::Framework::InspectorClient::GetInstance().CallFastPreviewErrorCallback(attrsJson);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIOperateComponent");
    LOGI("Fast Preview end");
    return true;
}

void AceAbility::SetWindow(sptr<OHOS::Rosen::Window> rsWindow)
{
    rsWindow_ = rsWindow;
}

sptr<OHOS::Rosen::Window> AceAbility::GetWindow()
{
    return rsWindow_;
}

} // namespace OHOS::Ace::Platform
