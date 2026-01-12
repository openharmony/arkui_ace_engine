/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "arkts_dynamic_uicontent_impl.h"

#include <atomic>
#include <cinttypes>
#include <optional>

#include "ability_context.h"
#include "ability_info.h"
#include "bundlemgr/bundle_mgr_proxy.h"
#include "configuration.h"
#include "if_system_ability_manager.h"
#include "ipc_skeleton.h"
#include "iservice_registry.h"
#include "js_runtime_utils.h"
#include "locale_config.h"
#include "native_reference.h"
#include "ohos/init_data.h"
#include "application_context.h"
#ifdef RESOURCE_SCHEDULE_SERVICE_ENABLE
#include "res_sched_client.h"
#include "res_type.h"
#include "resource_manager.h"
#endif // RESOURCE_SCHEDULE_SERVICE_ENABLE
#include "service_extension_context.h"
#include "system_ability_definition.h"
#include "wm_common.h"

#include "base/log/log_wrapper.h"
#include "base/memory/referenced.h"
#include "base/ressched/ressched_report.h"
#include "base/thread/background_task_executor.h"
#include "base/utils/utils.h"
#include "core/common/multi_thread_build_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/animation_utils.h"

#if !defined(ACE_UNITTEST)
#include "core/components_ng/base/transparent_node_detector.h"
#endif

#include "core/components_ng/property/safe_area_insets.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/cj_utils/cj_utils.h"
#include "adapter/ohos/entrance/dialog_container.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/form_utils_impl.h"
#include "adapter/ohos/entrance/aps_monitor_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/ui_event_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/navigation_route_ohos.h"
#include "adapter/ohos/osal/page_url_checker_ohos.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "adapter/ohos/osal/resource_adapter_impl_v2.h"
#include "adapter/ohos/osal/thp_extra_manager_impl.h"
#include "adapter/ohos/osal/view_data_wrap_ohos.h"
#include "arkts_dynamic_renderer_loader.h"
#include "base/geometry/rect.h"
#include "base/i18n/localization.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/thread/background_task_executor.h"
#include "base/thread/task_dependency_manager.h"
#include "base/utils/system_properties.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "bridge/arkts_frontend/arkts_dynamic_frontend.h"
#include "core/common/ace_engine.h"
#include "core/common/asset_manager_impl.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/modal_ui_extension.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/xcollie/xcollieInterface.h"
#include "core/components/theme/shadow_theme.h"
#include "core/components/popup/popup_theme.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/container_modal/container_modal_view.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_view_enhance.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"
#include "core/image/image_file_cache.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifdef FORM_SUPPORTED
#include "core/common/form_manager.h"
#endif
#include "core/common/layout_inspector.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#ifdef NG_BUILD
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#endif

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "screen_session_manager_client.h"

namespace OHOS::Ace::NG {
namespace {
const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string ACTION_VIEWDATA = "ohos.want.action.viewData";
const int32_t REQUEST_CODE = -1;

void AddSetAppColorModeToResConfig(
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context, ResourceConfiguration& aceResCfg)
{
    CHECK_NULL_VOID(context);
    auto config = context->GetConfiguration();
    CHECK_NULL_VOID(config);
    auto colorModeIsSetByApp = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::COLORMODE_IS_SET_BY_APP);
    if (!colorModeIsSetByApp.empty()) {
        aceResCfg.SetColorModeIsSetByApp(true);
    }
}

void AddResConfigInfo(
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context, ResourceConfiguration& aceResCfg)
{
    if (!context || !context->GetResourceManager()) {
        return;
    }
    auto resourceManager = context->GetResourceManager();
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    CHECK_NULL_VOID(resConfig);
    CHECK_NULL_VOID(resourceManager);
    resourceManager->GetResConfig(*resConfig);
    aceResCfg.SetMcc(resConfig->GetMcc());
    aceResCfg.SetMnc(resConfig->GetMnc());
    aceResCfg.SetAppHasDarkRes(resConfig->GetAppDarkRes());
    auto preferredLocaleInfo = resConfig->GetPreferredLocaleInfo();
    if (preferredLocaleInfo != nullptr) {
        std::string preferredLanguage = preferredLocaleInfo->getLanguage();
        std::string script = preferredLocaleInfo->getScript();
        std::string country = preferredLocaleInfo->getCountry();
        AceApplicationInfo::GetInstance().SetLocale(preferredLanguage.c_str(), country.c_str(), script.c_str(), "");

        std::string preferredLanguageTag = preferredLanguage;
        if (!script.empty()) {
            preferredLanguageTag += "-" + script;
        }
        if (!country.empty()) {
            preferredLanguageTag += "-" + country;
        }
        aceResCfg.SetPreferredLanguage(preferredLanguageTag);
    }
}

using ContentFinishCallback = std::function<void()>;
using ContentStartAbilityCallback = std::function<void(const std::string& address)>;
class ContentEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit ContentEventCallback(ContentFinishCallback onFinish) : onFinish_(onFinish) {}
    ContentEventCallback(ContentFinishCallback onFinish, ContentStartAbilityCallback onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility)
    {}
    ~ContentEventCallback() override = default;

    void OnFinish() const override
    {
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStartAbility(const std::string& address) override
    {
        CHECK_NULL_VOID(onStartAbility_);
        onStartAbility_(address);
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("StatusBarBgColorChanged: %{public}u", color);
    }

private:
    ContentFinishCallback onFinish_;
    ContentStartAbilityCallback onStartAbility_;
};

void GetAbilityInfoByAbilityContext(const std::weak_ptr<OHOS::AbilityRuntime::Context>& context,
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> &info)
{
    auto contextRef = context.lock();
    if (!contextRef) {
        LOGE("context is null.");
        return;
    }

    auto abilityContext =
        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(contextRef);
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
        return;
    }

    auto extensionContext =
        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(contextRef);
    if (extensionContext) {
        info = extensionContext->GetAbilityInfo();
    }
}
}

std::shared_ptr<ArktsDynamicUIContentImpl> ArktsDynamicUIContentImpl::Create(OHOS::AbilityRuntime::Context* context,
    void* aniEnv, VMType vmType, const DcCreateParam& param)
{
    return std::make_shared<ArktsDynamicUIContentImpl>(context, aniEnv, vmType, param);
}

ArktsDynamicUIContentImpl::ArktsDynamicUIContentImpl(OHOS::AbilityRuntime::Context* context,
    void* aniEnv, VMType vmType, const DcCreateParam& param)
    : UIContentImpl(context, aniEnv, vmType)
{
    isFormRender_ = param.isFormRender;
    aceLogTag_ = param.aceLogTag;
    CHECK_NULL_VOID(context);
    auto hapModuleInfo = context->GetHapModuleInfo();
    hapPath_ = hapModuleInfo->hapPath;
    isBundle_ = (hapModuleInfo->compileMode == AppExecFwk::CompileMode::JS_BUNDLE);
    StoreConfiguration(context->GetConfiguration());
    TAG_LOGI(aceLogTag_, "create ArktsDynamicUIContentImpl");
}

ArktsDynamicUIContentImpl::~ArktsDynamicUIContentImpl()
{
    TAG_LOGI(aceLogTag_, "destory ArktsDynamicUIContentImpl");
}

void ArktsDynamicUIContentImpl::InitializeArktsDynamicUIContentImpl(const DynamicInitialConfig& config)
{
    if (uIContentType_ != UIContentType::DYNAMIC_COMPONENT) {
        TAG_LOGW(aceLogTag_, "UIContentType is not DYNAMIC_COMPONENT");
        return;
    }

    isDynamicRender_ = true;
    if (!config.hapPath.empty()) {
        hapPath_ = config.hapPath;
    }

    hostInstanceId_ = config.hostInstanceId;
    registerComponents_ = config.registerComponents;
    auto entryPoint = config.entryPoint;
    hostWindowInfo_ = config.hostWindowInfo;
    auto taskWrapper = ArktsDynamicRendererLoader::GetInstance().CreatEaWorkerTaskWrapper(
        config.hostInstanceId, config.workerId);
    if (taskWrapper == nullptr) {
        TAG_LOGE(aceLogTag_, "CreatEaWorkerTaskWrapper failed");
        return;
    }

    taskWrapper_.reset(taskWrapper);
    CommonInitializeDc(config.abcPath);
    AddWatchSystemParameter();

    TAG_LOGI(aceLogTag_, "[%{public}s][%{public}s][%{public}d]: InitializeDynamic, startUrl"
         ": %{public}s, entryPoint: %{public}s, hapPath: %{public}s", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, startUrl_.c_str(), entryPoint.c_str(), hapPath_.c_str());
    Platform::AceContainer::RunDynamicPage(instanceId_, startUrl_, "", entryPoint);
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

UIContentErrorCode ArktsDynamicUIContentImpl::CommonInitializeDc(const std::string& contentInfo)
{
    ACE_FUNCTION_TRACE();
    startUrl_ = contentInfo;
    auto errorCode = UIContentErrorCode::NO_ERRORS;
    CommonInitializeConfiguration();
    CommonInitializeAceApplicationInfo();
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    CommonInitializeDeviceInfo(deviceWidth, deviceHeight, density);
    TAG_LOGI(aceLogTag_,
        "[%{public}s][%{public}s][%{public}d]: CommonInitializeDc virtualPixelRatio: %{public}f, deviceWidth: "
        "%{public}d, deviceHeight: %{public}d",
        bundleName_.c_str(), moduleName_.c_str(), instanceId_, density, deviceWidth, deviceHeight);
    ColorMode colorMode = ColorMode::LIGHT;
    CommonInitializeResourceManager(colorMode);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    GetAbilityInfoByAbilityContext(context_, info);
    if (info) {
        AceApplicationInfo::GetInstance().SetAbilityName(info->name);
    }

    RefPtr<AssetManagerImpl> assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
    CommonInitializeAssetManager(assetManagerImpl);
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    // create container
    auto container = CreateAceContainer(info);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    container->SetColorMode(colorMode);
    std::string pageProfile;
    container->SetPageProfile(pageProfile);
    container->Initialize();
    container->SetAssetManager(assetManagerImpl);
    AfterContainerInitialize();

    // create ace_view
    RefPtr<Platform::AceViewOhos> aceView = CreateAceView(density);
    CHECK_NULL_RETURN(aceView, UIContentErrorCode::NULL_POINTER);
    // after frontend initialize
    HandleCommonInitializeWindowFocus();
    HandleSurfaceChanged(aceView, deviceWidth, deviceHeight, isModelJson);
    return errorCode;
}

void ArktsDynamicUIContentImpl::CommonInitializeConfiguration()
{
    auto context = context_.lock();
    if (!context) {
        TAG_LOGE(aceLogTag_, "context is null.");
        return;
    }

    auto configuration = context->GetConfiguration();
    std::unordered_map<std::string, DeviceType> typeMap = { { "phone", DeviceType::PHONE },
        { "tv", DeviceType::TV }, { "watch", DeviceType::WATCH }, { "car", DeviceType::CAR },
        { "tablet", DeviceType::TABLET }, { "2in1", DeviceType::TWO_IN_ONE }, { "wearable", DeviceType::WEARABLE },
        { "UNKNOWN", DeviceType::UNKNOWN } };
    if (configuration) {
        auto type = configuration->GetItem(OHOS::AAFwk::GlobalConfigurationKey::DEVICE_TYPE);
        if (typeMap.find(type) != typeMap.end()) {
            SystemProperties::SetDeviceType(typeMap[type]);
        }
    } else {
        TAG_LOGI(aceLogTag_, "configuration is nullptr,use default type");
    }
}

void ArktsDynamicUIContentImpl::CommonInitializeAceApplicationInfo()
{
    auto context = context_.lock();
    if (!context) {
        TAG_LOGE(aceLogTag_, "context is null.");
        return;
    }

    if (isFormRender_) {
        TAG_LOGI(aceLogTag_, "No need InitializeAceApplicationInfo due to isFormRender true.");
        return;
    }

    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&context]() {
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingRealPid());
        CapabilityRegistry::Register();
        ImageFileCache::GetInstance().SetImageCacheFilePath(context->GetCacheDir());
    });
}

void ArktsDynamicUIContentImpl::CommonInitializeDeviceInfo(
    int32_t &deviceWidth, int32_t &deviceHeight, float &density)
{
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        auto displayInfo = defaultDisplay->GetDisplayInfo();
        if (displayInfo) {
            density = displayInfo->GetDensityInCurResolution();
        }
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
    }
    SystemProperties::ReadSystemParametersCallOnce();
    SystemProperties::InitDeviceInfo(
        deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
}

void ArktsDynamicUIContentImpl::CommonInitializeResourceManager(ColorMode &colorMode)
{
    auto context = context_.lock();
    if (!context) {
        TAG_LOGE(aceLogTag_, "context is null.");
        return;
    }

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    auto resourceManager = context->GetResourceManager();
    if (resourceManager != nullptr) {
        resourceManager->GetResConfig(*resConfig);
        if (resConfig == nullptr) {
            TAG_LOGE(aceLogTag_, "init resConfig failed!");
            return;
        }
        auto localeInfo = resConfig->GetLocaleInfo();
        Platform::AceApplicationInfoImpl::GetInstance().SetResourceManager(resourceManager);
        if (localeInfo != nullptr) {
            auto language = localeInfo->getLanguage();
            auto region = localeInfo->getCountry();
            auto script = localeInfo->getScript();
            AceApplicationInfo::GetInstance().SetLocale((language == nullptr) ? "" : language,
                (region == nullptr) ? "" : region, (script == nullptr) ? "" : script, "");
        }
        if (resConfig->GetColorMode() == OHOS::Global::Resource::ColorMode::DARK) {
            colorMode = ColorMode::DARK;
            TAG_LOGI(aceLogTag_, "Set dark mode");
        } else {
            colorMode = ColorMode::LIGHT;
            TAG_LOGI(aceLogTag_, "Set light mode");
        }

        SystemProperties::SetDeviceAccess(
            resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
        return;
    }

    auto config = context->GetConfiguration();
    if (config) {
        auto configColorMode = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
        colorMode = configColorMode == "dark" ? ColorMode::DARK : ColorMode::LIGHT;
    }
}

void ArktsDynamicUIContentImpl::CommonInitializeAssetManager(const RefPtr<AssetManager>& assetManager)
{
    if (!assetManager) {
        TAG_LOGE(aceLogTag_, "assetManager is null.");
        return;
    }

    std::vector<std::string> basePaths;
    basePaths.emplace_back("assets/js/" + moduleName_ + "/");
    basePaths.emplace_back("assets/js/share/");
    basePaths.emplace_back("");
    basePaths.emplace_back("js/");
    basePaths.emplace_back("ets/");
    auto assetProvider = CreateAssetProviderImpl(hapPath_, basePaths, false);
    if (assetProvider) {
        assetManager->PushBack(std::move(assetProvider));
    }
}

RefPtr<Platform::AceContainer> ArktsDynamicUIContentImpl::CreateAceContainer(
    const std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& info)
{
    if (runtime_) {
        instanceId_ = Container::GenerateId<STAGE_CONTAINER>();
    } else {
        instanceId_ = Container::GenerateId<FA_SUBWINDOW_CONTAINER>();
    }
    if (isDynamicRender_) {
        ContainerScope::UpdateLocalCurrent(instanceId_);
    }
    auto frontendType = FrontendType::DECLARATIVE_JS;
    if (vmType_ == VMType::ARK_NATIVE) {
        frontendType = FrontendType::ARK_TS;
    }
    auto container =
        AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, frontendType, context_, info,
            std::make_unique<ContentEventCallback>(
                [window = window_] {
                    CHECK_NULL_VOID(window);
                    window->PerformBack();
                },
                [context = context_, aceLogTag = aceLogTag_](const std::string& address) {
                    auto sharedContext = context.lock();
                    CHECK_NULL_VOID(sharedContext);
                    auto abilityContext =
                        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                    CHECK_NULL_VOID(abilityContext);
                    TAG_LOGI(aceLogTag, "Start ability: %{private}s", address.c_str());
                    AAFwk::Want want;
                    want.AddEntity(Want::ENTITY_BROWSER);
                    want.SetUri(address);
                    want.SetAction(ACTION_VIEWDATA);
                    abilityContext->StartAbility(want, REQUEST_CODE);
                }), taskWrapper_, false, false, true);
    if (container == nullptr) {
        TAG_LOGE(aceLogTag_, "Create container failed.");
        return nullptr;
    }
    container->SetIsFormRender(isFormRender_);
    container->SetIsDynamicRender(isDynamicRender_);
    container->SetUIContentType(uIContentType_);
    container->SetRegisterComponents(registerComponents_);
    container->SetIsFRSCardContainer(isFormRender_);
    if (window_) {
        container->SetWindowName(window_->GetWindowName());
        container->SetWindowId(window_->GetWindowId());
    }
    auto context = context_.lock();
    if (context) {
        auto token = context->GetToken();
        container->SetToken(token);
    }

    auto appInfo = context != nullptr ? context->GetApplicationInfo() : nullptr;
    if (appInfo) {
        container->SetApiTargetVersion(appInfo->apiTargetVersion);
    }
    if (window_) {
        SubwindowManager::GetInstance()->AddContainerId(window_->GetWindowId(), instanceId_);
    }
    AceEngine::Get().AddContainer(instanceId_, container);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    return container;
}

void ArktsDynamicUIContentImpl::AfterContainerInitialize()
{
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container == nullptr) {
        TAG_LOGE(aceLogTag_, "container is nullptr");
        return;
    }

    auto context = context_.lock();
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(container);
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
    aceResCfg.SetColorMode(container->GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    aceResCfg.SetLanguage(AceApplicationInfo::GetInstance().GetLocaleTag());
    AddResConfigInfo(context, aceResCfg);

    if (isDynamicRender_) {
        auto runtimeContext = Platform::AceContainer::GetRuntimeContext(hostInstanceId_);
        if (runtimeContext) {
            AddSetAppColorModeToResConfig(runtimeContext->shared_from_this(), aceResCfg);
        }
    } else {
        AddSetAppColorModeToResConfig(context, aceResCfg);
    }

    std::string hapPath; // hap path in sandbox
    std::string resPath;
    if (isDynamicRender_) {
        if (std::regex_match(hapPath_, std::regex(".*\\.hap"))) {
            hapPath = hapPath_;
        } else {
            resPath = hapPath_;
        }
    } else if (isFormRender_) {
        resPath = "/data/bundles/" + bundleName_ + "/" + moduleName_ + "/";
        hapPath = hapPath_;
    }

    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    if (!isFormRender_) {
        container->SetBundlePath(context->GetBundleCodeDir());
        container->SetFilesDataPath(context->GetFilesDir());
    }

    TAG_LOGI(aceLogTag_,
        "[%{public}s][%{public}s][%{public}d]: AfterContainerInitialize "
        "resPath = %{public}s, hapPath = %{public}s.", bundleName_.c_str(),
        moduleName_.c_str(), instanceId_, resPath.c_str(), hapPath.c_str());
}

RefPtr<Platform::AceViewOhos> ArktsDynamicUIContentImpl::CreateAceView(float &density)
{
    RefPtr<Platform::AceViewOhos> aceView = nullptr;
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container == nullptr) {
        TAG_LOGE(aceLogTag_, "container is nullptr");
        return aceView;
    }

    if (isFormRender_ && !isDynamicRender_) {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, true, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    } else {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    }

    auto errorCode = UIContentErrorCode::NO_ERRORS;
    if (isFormRender_) {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, round(formWidth_),
            round(formHeight_), window_);
        if (errorCode > 0) {
            return aceView;
        }

        auto frontend = AceType::DynamicCast<ArktsDynamicFrontend>(container->GetFrontend());
        CHECK_NULL_RETURN(frontend, aceView);
        frontend->SetBundleName(bundleName_);
        frontend->SetModuleName(moduleName_);
        // arkTSCard only support "esModule" compile mode
        frontend->SetIsBundle(false);
        container->SetBundleName(bundleName_);
    } else {
        errorCode = Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
        if (errorCode > 0) {
            return aceView;
        }
    }

    if (isDynamicRender_) {
        if (hostWindowInfo_.focusWindowId != 0) {
            container->SetFocusWindowId(hostWindowInfo_.focusWindowId);
        }

        if (hostWindowInfo_.realHostWindowId > 0) {
            container->SetRealHostWindowId(hostWindowInfo_.realHostWindowId);
        }
        TAG_LOGI(aceLogTag_, "DynamicRender: focusWindowId: %{public}u, realHostWindowId: %{public}d",
            hostWindowInfo_.focusWindowId, hostWindowInfo_.realHostWindowId);
    }

    return aceView;
}

void ArktsDynamicUIContentImpl::HandleCommonInitializeWindowFocus()
{
    if (window_ && window_->IsFocused()) {
        Focus();
    }
}

void ArktsDynamicUIContentImpl::HandleSurfaceChanged(
    const RefPtr<Platform::AceViewOhos>& aceView, int32_t deviceWidth, int32_t deviceHeight, bool isModelJson)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container == nullptr) {
        TAG_LOGE(aceLogTag_, "container is nullptr");
        return;
    }

    auto context = context_.lock();
    auto appInfo = context != nullptr ? context->GetApplicationInfo() : nullptr;
    if (isFormRender_) {
        Platform::AceViewOhos::SurfaceChanged(aceView, round(formWidth_), round(formHeight_),
            deviceHeight >= deviceWidth ? 0 : 1);
        container->CheckAndSetFontFamily();
        SetFontScaleAndWeightScale(container, instanceId_);
        // Set sdk version in module json mode for form
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
            pipeline->SetApiTargetVersion(container->GetApiTargetVersion());
        }
    } else {
        Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    }

    if (isModelJson) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
            pipeline->SetApiTargetVersion(container->GetApiTargetVersion());
        }
    }
    if (context) {
        UpdateFontScale(context->GetConfiguration());
    }
}
} // namespace OHOS::Ace::NG
