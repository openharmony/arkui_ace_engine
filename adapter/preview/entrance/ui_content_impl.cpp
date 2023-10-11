/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/preview/entrance/ui_content_impl.h"

#include <ui/rs_surface_node.h>
#include <ui/rs_ui_director.h>

#include "include/core/SkFontMgr.h"

#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "adapter/preview/entrance/ace_application_info.h"
#include "adapter/preview/entrance/ace_container.h"
#include "adapter/preview/entrance/clipboard/clipboard_impl.h"
#include "adapter/preview/entrance/clipboard/clipboard_proxy_impl.h"
#include "adapter/preview/entrance/event_dispatcher.h"
#include "adapter/preview/entrance/rs_dir_asset_provider.h"
#include "adapter/preview/external/multimodalinput/axis_event.h"
#include "adapter/preview/external/multimodalinput/key_event.h"
#include "adapter/preview/external/multimodalinput/pointer_event.h"
#include "adapter/preview/inspector/inspector_client.h"
#include "frameworks/base/log/log.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"
#ifdef INIT_ICU_DATA_PATH
#include "unicode/putil.h"
#endif

#include "frameworks/simulator/common/include/context.h"

namespace OHOS::Ace {

using namespace Platform;

namespace {

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
    LOGI("Runtime OS is %{public}s, and the container fontBasePath is %{public}s", runtimeOS.c_str(),
        containerFontBasePath.c_str());
    SkFontMgr::SetFontMgrConfig(runtimeOS, containerFontBasePath);
}

} // namespace

using ContentFinishCallback = std::function<void()>;
using ContentStartAbilityCallback = std::function<void(const std::string& address)>;
class ContentEventCallback final : public PlatformEventCallback {
public:
    explicit ContentEventCallback(ContentFinishCallback onFinish) : onFinish_(onFinish) {}
    ContentEventCallback(ContentFinishCallback onFinish, ContentStartAbilityCallback onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility)
    {}
    ~ContentEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("UIContent OnFinish");
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStartAbility(const std::string& address) override
    {
        LOGI("UIContent OnStartAbility");
        CHECK_NULL_VOID(onStartAbility_);
        onStartAbility_(address);
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("UIContent OnStatusBarBgColorChanged");
    }

private:
    ContentFinishCallback onFinish_;
    ContentStartAbilityCallback onStartAbility_;
};

class DragWindowListener : public OHOS::Rosen::IWindowDragListener {
public:
    explicit DragWindowListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~DragWindowListener() = default;
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
    {
        LOGI("[Engine Log] The feature is not supported on the previewer, and instanceId_ = %{public}d", instanceId_);
    }

private:
    int32_t instanceId_ = -1;
};

class TouchOutsideListener : public OHOS::Rosen::ITouchOutsideListener {
public:
    explicit TouchOutsideListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~TouchOutsideListener() = default;

    void OnTouchOutside() const
    {
        LOGI("[Engine Log] The feature is not supported on the previewer, and instanceId_ = %{public}d", instanceId_);
    }

private:
    int32_t instanceId_ = -1;
};

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    LOGI("Ace lib loaded, CreateUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateFormContent(void* context, void* runtime, bool isCard)
{
    LOGI("Ace lib loaded, CreateFormUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime, isCard);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    LOGI("Ace lib loaded, Create SubWindowUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime)
    : instanceId_(ACE_INSTANCE_ID), runtime_(runtime)
{
    // 基于Options的方式传递参数
    auto options = context->GetOptions();
    assetPath_ = options.assetPath;
    systemResourcesPath_ = options.systemResourcePath;
    appResourcesPath_ = options.appResourcePath;
    containerSdkPath_ = options.containerSdkPath;
    language_ = options.language;
    region_ = options.region;
    script_ = options.script;
    themeId_ = options.themeId;
    deviceWidth_ = options.deviceWidth;
    deviceHeight_ = options.deviceHeight;
    isRound_ = options.isRound;
    onRouterChange_ = options.onRouterChange;
    deviceConfig_.orientation = static_cast<DeviceOrientation>(options.deviceConfig.orientation);
    deviceConfig_.deviceType = static_cast<DeviceType>(options.deviceConfig.deviceType);
    deviceConfig_.colorMode = static_cast<ColorMode>(options.deviceConfig.colorMode);
    deviceConfig_.density = options.deviceConfig.density;
    deviceConfig_.fontRatio = options.deviceConfig.fontRatio;

    bundleName_ = options.bundleName;
    compatibleVersion_ = options.compatibleVersion;
    installationFree_ = options.installationFree;
    labelId_ = options.labelId;
    moduleName_ = options.moduleName;
    compileMode_ = options.compileMode;
    pageProfile_ = options.pageProfile;
    const std::string profilePrefix = "$profile:";
    if (pageProfile_.compare(0, profilePrefix.size(), profilePrefix) == 0) {
        pageProfile_ = pageProfile_.substr(profilePrefix.length()).append(".json");
    }
    auto targetVersion = options.targetVersion;
    auto releaseType = options.releaseType;
    bool enablePartialUpdate = options.enablePartialUpdate;
    useNewPipeline_ = AceNewPipeJudgement::QueryAceNewPipeEnabledStage(
        "", compatibleVersion_, targetVersion, releaseType, !enablePartialUpdate);
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard)
    : instanceId_(ACE_INSTANCE_ID), runtime_(runtime), isFormRender_(isCard)
{
    LOGI("The constructor is used to support ets card, isFormRender_ = %{public}d", isFormRender_);
}

UIContentImpl::UIContentImpl(OHOS::AppExecFwk::Ability* ability) : instanceId_(ACE_INSTANCE_ID) {}

void UIContentImpl::DestroyUIDirector()
{
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    auto rsUIDirector = pipelineContext->GetRSUIDirector();
    CHECK_NULL_VOID(rsUIDirector);
    rsUIDirector->Destroy();
}

void UIContentImpl::DestroyCallback() const
{
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(nullptr);
}

void UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    CommonInitialize(window, url, storage);
    AceContainer::RunPage(instanceId_, url, "");
}

std::string UIContentImpl::GetContentInfo() const
{
    LOGI("UIContent GetContentInfo");
    return AceContainer::GetContentInfo(instanceId_);
}

void UIContentImpl::CommonInitialize(OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        LOGI("Initialize for current process.");
#ifdef INIT_ICU_DATA_PATH
        std::string icuPath = ".";
        u_setDataDirectory(icuPath.c_str());
#endif
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        ClipboardProxy::GetInstance()->SetDelegate(std::make_unique<Platform::ClipboardProxyImpl>());
    });
    rsWindow_ = window;

    AceApplicationInfo::GetInstance().SetLocale(language_, region_, script_, "");
    SetFontMgrConfig(containerSdkPath_);
    EventDispatcher::GetInstance().Initialize();
    SystemProperties::SetExtSurfaceEnabled(!containerSdkPath_.empty());
    SystemProperties::InitDeviceInfo(deviceWidth_, deviceHeight_,
        deviceConfig_.orientation == DeviceOrientation::PORTRAIT ? 0 : 1, deviceConfig_.density, isRound_);
    SystemProperties::InitDeviceType(deviceConfig_.deviceType);
    SystemProperties::SetColorMode(deviceConfig_.colorMode);
    LOGI("CreateContainer with JSDECLARATIVE frontend");
    AceContainer::CreateContainer(instanceId_, FrontendType::DECLARATIVE_JS, useNewPipeline_);
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    container->SetContainerSdkPath(containerSdkPath_);
    container->SetIsFRSCardContainer(false);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetInstallationFree(installationFree_);
    container->SetLabelId(labelId_);
    auto config = container->GetResourceConfiguration();
    config.SetDeviceType(SystemProperties::GetDeviceType());
    config.SetOrientation(SystemProperties::GetDeviceOrientation());
    config.SetDensity(SystemProperties::GetResolution());
    config.SetColorMode(SystemProperties::GetColorMode());
    config.SetFontRatio(deviceConfig_.fontRatio);
    container->SetResourceConfiguration(config);
    container->SetPageProfile(pageProfile_);
    std::vector<std::string> paths;
    paths.push_back(assetPath_);
    std::string appResourcesPath(appResourcesPath_);
    if (!OHOS::Ace::Framework::EndWith(appResourcesPath, DELIMITER)) {
        appResourcesPath.append(DELIMITER);
    }
    paths.push_back(appResourcesPath);
    paths.push_back(appResourcesPath + ASSET_PATH_SHARE_STAGE);
    if (!containerSdkPath_.empty()) {
        paths.push_back(containerSdkPath_);
    }
    AceContainer::AddAssetPath(instanceId_, "", paths);
    AceContainer::SetResourcesPathAndThemeStyle(
        instanceId_, systemResourcesPath_ + "/entry", appResourcesPath_, themeId_, deviceConfig_.colorMode);

    auto view = AceViewPreview::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
    UIEnvCallback callback = [window = rsWindow_, id = instanceId_](
                                 const OHOS::Ace::RefPtr<PipelineContext>& context) mutable {
        CHECK_NULL_VOID(context);
        CHECK_NULL_VOID(window);
        auto director = OHOS::Rosen::RSUIDirector::Create();
        CHECK_NULL_VOID(director);
        director->SetRSSurfaceNode(window->GetSurfaceNode());
        auto container = AceContainer::GetContainerInstance(id);
        CHECK_NULL_VOID(container);
        auto func = [taskExecutor = container->GetTaskExecutor(), id](const std::function<void()>& task) {
            CHECK_NULL_VOID(taskExecutor);
            ContainerScope scope(id);
            taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
        };
        director->SetUITaskRunner(func);
        director->Init();
        context->SetRSUIDirector(director);
    };
    AceContainer::SetView(view, rsWindow_, deviceConfig_.density, deviceWidth_, deviceHeight_, callback);
    // Drive the native engine with the platform thread.
    container->RunNativeEngineLoop();
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        LOGI("Set MinPlatformVersion to %{public}d", compatibleVersion_);
        pipelineContext->SetMinPlatformVersion(compatibleVersion_);
    }
    container->InitializeStageAppConfig(assetPath_, bundleName_, moduleName_, compileMode_);
    AceContainer::AddRouterChangeCallback(instanceId_, onRouterChange_);
    // Should make it possible to update surface changes by using viewWidth and viewHeight.
    view->NotifySurfaceChanged(deviceWidth_, deviceHeight_);
    view->NotifyDensityChanged(deviceConfig_.density);
}

void UIContentImpl::Destroy()
{
    LOGI("UIContentImpl: window destroy");
    AceContainer::DestroyContainer(instanceId_);
}

uint32_t UIContentImpl::GetBackgroundColor()
{
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_RETURN(container, 0x000000);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0x000000);
    ContainerScope scope(instanceId_);
    uint32_t bgColor = 0x000000;
    taskExecutor->PostSyncTask(
        [&bgColor, container]() {
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            bgColor = pipelineContext->GetAppBgColor().GetValue();
        },
        TaskExecutor::TaskType::UI);

    LOGI("UIContentImpl::GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}

void UIContentImpl::SetBackgroundColor(uint32_t color)
{
    LOGI("UIContentImpl: SetBackgroundColor color is %{public}u", color);
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor = color]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(Color(bgColor));
        },
        TaskExecutor::TaskType::UI);
}

bool UIContentImpl::ProcessBackPressed()
{
    LOGI("Process Back Pressed Event");
    return EventDispatcher::GetInstance().DispatchBackPressedEvent();
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    LOGI("Process MMI::PointerEvent");
    return EventDispatcher::GetInstance().DispatchTouchEvent(pointerEvent);
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent)
{
    LOGI("Process MMI::KeyEvent");
    return EventDispatcher::GetInstance().DispatchKeyEvent(keyEvent);
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    LOGI("Process MMI::AxisEvent");
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    LOGI("Process VsyncEvent");
    return false;
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) {}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    LOGI("ViewportConfig: %{public}s", config.ToString().c_str());
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto viewPtr = container->GetAceView();
    CHECK_NULL_VOID(viewPtr);
    SystemProperties::InitDeviceInfo(
        config.Width(), config.Height(), config.Height() >= config.Width() ? 0 : 1, config.Density(), false);
    deviceConfig_.orientation =
        config.Height() >= config.Width() ? DeviceOrientation::PORTRAIT : DeviceOrientation::LANDSCAPE;
    deviceConfig_.density = config.Density();
    // Unlike the real machine, previewer require updating device configuration information to change window size.
    container->UpdateDeviceConfig(deviceConfig_);
    viewPtr->NotifyDensityChanged(config.Density());
    viewPtr->NotifySurfaceChanged(config.Width(), config.Height());
}

void UIContentImpl::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    container->Dump(params, info);
}

void UIContentImpl::SetNextFrameLayoutCallback(std::function<void()>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(std::move(callback));
}

void UIContentImpl::NotifyMemoryLevel(int32_t level)
{
    LOGI("Receive Memory level notification, level: %{public}d", level);
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    pipelineContext->NotifyMemoryLevel(level);
}

int32_t UIContentImpl::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config)
{
    return 0;
}

void UIContentImpl::CloseModalUIExtension(int32_t sessionId) {}
} // namespace OHOS::Ace
