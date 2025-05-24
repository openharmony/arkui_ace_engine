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
#include "js_native_api.h"
#include "js_native_api_types.h"

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
#include "base/log/log_wrapper.h"
#include "frameworks/base/log/log.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/js_frontend/js_frontend.h"
#include "frameworks/core/common/ace_engine.h"
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

NG::SafeAreaInsets ConvertAvoidArea(const OHOS::Rosen::AvoidArea& avoidArea)
{
    return NG::SafeAreaInsets({ avoidArea.leftRect_.posX_, avoidArea.leftRect_.posX_ + avoidArea.leftRect_.width_ },
        { avoidArea.topRect_.posY_, avoidArea.topRect_.posY_ + avoidArea.topRect_.height_ },
        { avoidArea.rightRect_.posX_, avoidArea.rightRect_.posX_ + avoidArea.rightRect_.width_ },
        { avoidArea.bottomRect_.posY_, avoidArea.bottomRect_.posY_ + avoidArea.bottomRect_.height_ });
}

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

class IIgnoreViewSafeAreaListener : public OHOS::Rosen::IIgnoreViewSafeAreaListener {
public:
    explicit IIgnoreViewSafeAreaListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~IIgnoreViewSafeAreaListener() = default;

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

class AvoidAreaChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AvoidAreaChangedListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvoidAreaChangedListener() = default;

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
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [pipeline, safeArea, navSafeArea, cutoutSafeArea, type, avoidArea] {
                if (type == Rosen::AvoidAreaType::TYPE_SYSTEM) {
                    pipeline->UpdateSystemSafeArea(safeArea);
                } else if (type == Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR) {
                    pipeline->UpdateNavSafeArea(navSafeArea);
                } else if (type == Rosen::AvoidAreaType::TYPE_CUTOUT) {
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

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateFormContent(void* context, void* runtime, bool isCard)
{
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime, isCard);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime)
    : instanceId_(ACE_INSTANCE_ID), runtime_(runtime)
{
    // 基于Options的方式传递参数
    CHECK_NULL_VOID(context);
    context_ = context->weak_from_this();
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
    targetVersion_ = options.targetVersion;
    auto releaseType = options.releaseType;
    bool enablePartialUpdate = options.enablePartialUpdate;
    useNewPipeline_ = AceNewPipeJudgement::QueryAceNewPipeEnabledStage(
        "", compatibleVersion_, targetVersion_, releaseType, !enablePartialUpdate);
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard)
    : instanceId_(ACE_INSTANCE_ID), runtime_(runtime), isFormRender_(isCard)
{
    LOGI("The constructor is used to support ets card, isFormRender_ = %{public}d", isFormRender_);
    if (context) {
        auto options = context->GetOptions();
        bundleName_ = options.bundleName;
        moduleName_ = options.moduleName;
    }
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

UIContentErrorCode UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url,
    napi_value storage)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    errorCode = CommonInitialize(window, url, storage);
    CHECK_ERROR_CODE_RETURN(errorCode);
    errorCode = AceContainer::RunPage(instanceId_, url, "");
    return errorCode;
}

UIContentErrorCode UIContentImpl::InitializeByName(
    OHOS::Rosen::Window* window, const std::string& name, napi_value storage)
{
    return InitializeInner(window, name, storage, true);
}

UIContentErrorCode UIContentImpl::InitializeInner(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, bool isNamedRouter)
{
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    if (window) {
        errorCode = CommonInitialize(window, contentInfo, storage);
        CHECK_ERROR_CODE_RETURN(errorCode);
    }
    LOGI("[%{public}s][%{public}s][%{public}d]: Initialize: %{public}s, isNameRouter: %{public}d", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, startUrl_.c_str(), isNamedRouter);
    return Platform::AceContainer::RunPage(instanceId_, startUrl_, "", isNamedRouter);
}

std::string UIContentImpl::GetContentInfo(ContentInfoType type) const
{
    return AceContainer::GetContentInfo(instanceId_, type);
}

UIContentErrorCode UIContentImpl::CommonInitialize(OHOS::Rosen::Window* window,
    const std::string& contentInfo, napi_value storage)
{
    auto context = context_.lock();
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
#ifdef INIT_ICU_DATA_PATH
        std::string icuPath = ".";
        u_setDataDirectory(icuPath.c_str());
#endif
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        ClipboardProxy::GetInstance()->SetDelegate(std::make_unique<Platform::ClipboardProxyImpl>());
    });
    rsWindow_ = window;
    CHECK_NULL_RETURN(rsWindow_, UIContentErrorCode::NULL_WINDOW);
    startUrl_ = contentInfo;
    AceApplicationInfo::GetInstance().SetLocale(language_, region_, script_, "");
    AceApplicationInfo::GetInstance().SetApiTargetVersion(targetVersion_);
    SetFontMgrConfig(containerSdkPath_);
    EventDispatcher::GetInstance().Initialize();
    SystemProperties::SetExtSurfaceEnabled(!containerSdkPath_.empty());
    SystemProperties::InitDeviceInfo(deviceWidth_, deviceHeight_,
        deviceConfig_.orientation == DeviceOrientation::PORTRAIT ? 0 : 1, deviceConfig_.density, isRound_);
    SystemProperties::InitDeviceType(deviceConfig_.deviceType);
    LOGI("CreateContainer with JSDECLARATIVE frontend, set MinPlatformVersion to %{public}d", compatibleVersion_);
    AceContainer::CreateContainer(instanceId_, FrontendType::DECLARATIVE_JS, useNewPipeline_);
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetAbilityContext(context_);
    container->SetContainerSdkPath(containerSdkPath_);
    container->SetIsFRSCardContainer(false);
    container->SetBundleName(bundleName_);
    container->SetModuleName(moduleName_);
    container->SetColorMode(deviceConfig_.colorMode);
    LOGI("Save bundle %{public}s, module %{public}s", bundleName_.c_str(), moduleName_.c_str());
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
    config.SetColorMode(container->GetColorMode());
    config.SetFontRatio(deviceConfig_.fontRatio);
    container->SetResourceConfiguration(config);
    container->SetPageProfile(pageProfile_);
    container->SetApiTargetVersion(targetVersion_);
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
        instanceId_, systemResourcesPath_, containerSdkPath_, appResourcesPath_, themeId_, deviceConfig_.colorMode);

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
    AceContainer::SetView(view, rsWindow_, deviceConfig_.density, deviceWidth_, deviceHeight_, callback);
    // Drive the native engine with the platform thread.
    container->RunNativeEngineLoop();
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetMinPlatformVersion(compatibleVersion_);
        pipelineContext->SetDisplayWindowRectInfo(
            Rect(Offset(0.0f, 0.0f), Size(deviceWidth_, deviceHeight_)));
    }
    container->InitializeAppConfig(assetPath_, bundleName_, moduleName_, compileMode_);
    AceContainer::AddRouterChangeCallback(instanceId_, onRouterChange_);
    // Should make it possible to update surface changes by using viewWidth and viewHeight.
    view->NotifySurfaceChanged(deviceWidth_, deviceHeight_);
    view->NotifyDensityChanged(deviceConfig_.density);
    avoidAreaChangedListener_ = new AvoidAreaChangedListener(instanceId_);
    rsWindow_->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
    ignoreViewSafeAreaListener_ = new IIgnoreViewSafeAreaListener(instanceId_);
    window->RegisterIgnoreViewSafeAreaListener(ignoreViewSafeAreaListener_);
    OHOS::Rosen::AvoidArea avoidArea;
    rsWindow_->GetAvoidAreaByType(OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM, avoidArea);
    avoidAreaChangedListener_->OnAvoidAreaChanged(avoidArea, OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM);
    rsWindow_->GetAvoidAreaByType(OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR, avoidArea);
    avoidAreaChangedListener_->OnAvoidAreaChanged(avoidArea, OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR);
    if (runtime_) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context);
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(reinterpret_cast<NativeReference*>(ref), context);
        }
    }
    return UIContentErrorCode::NO_ERRORS;
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
        TaskExecutor::TaskType::UI, "ArkUIGetAppBackgroundColor");

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
        TaskExecutor::TaskType::UI, "ArkUISetAppBackgroundColor");
}

void UIContentImpl::SetWindowContainerColor(uint32_t activeColor, uint32_t inactiveColor)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "[%{public}s][%{public}s][%{public}d]: SetWindowContainerColor:"
        "active color %{public}u, inactive color %{public}u",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, activeColor, inactiveColor);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, activeColor, inactiveColor]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetWindowContainerColor(Color(activeColor), Color(inactiveColor));
        },
        TaskExecutor::TaskType::UI, "ArkUISetWindowContainerColor");
}

bool UIContentImpl::ProcessBackPressed()
{
    LOGI("Process Back Pressed Event");
    return EventDispatcher::GetInstance().DispatchBackPressedEvent();
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    return EventDispatcher::GetInstance().DispatchTouchEvent(pointerEvent);
}

bool UIContentImpl::ProcessPointerEventWithCallback(
    const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent, const std::function<void()>& callback)
{
    auto result = EventDispatcher::GetInstance().DispatchTouchEvent(pointerEvent);
    if (callback) {
        callback();
    }
    return result;
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& keyEvent, bool isPreIme)
{
    // previewer never gets preIme-key event because there is no window
    return EventDispatcher::GetInstance().DispatchKeyEvent(keyEvent);
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    return false;
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config) {}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config,
    const std::shared_ptr<Global::Resource::ResourceManager>& resourceManager) {}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction,
    const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas,
    const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    LOGI("ViewportConfig: %{public}s", config.ToString().c_str());
    auto container = AceContainer::GetContainerInstance(instanceId_);
    CHECK_NULL_VOID(container);
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);
    context->SetDisplayWindowRectInfo(
        Rect(Offset(config.Left(), config.Top()), Size(config.Width(), config.Height())));
    auto viewPtr = AceType::DynamicCast<AceViewPreview>(container->GetAceView());
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

void UIContentImpl::SetStatusBarItemColor(uint32_t color)
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->SetStatusBarItemColor(IsDarkColor(color));
}

void UIContentImpl::OnConfigurationChanged(const DeviceConfig& newConfig)
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

void UIContentImpl::SurfaceChanged(
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

void UIContentImpl::LoadDocument(const std::string& url, const std::string& componentName,
    Platform::SystemParams& systemParams)
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

std::string UIContentImpl::GetJSONTree()
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

bool UIContentImpl::OperateComponent(const std::string& attrsJson)
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
} // namespace OHOS::Ace
