/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ace_container.h"

#include <ani.h>

#include "auto_fill_manager.h"
#include "bundlemgr/bundle_mgr_proxy.h"
#include "if_system_ability_manager.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "iservice_registry.h"
#include "scene_board_judgement.h"
#include "ui/rs_surface_node.h"
#include "ui_extension_context.h"
#include "system_ability_definition.h"
#include "wm_common.h"

#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/cj_utils/cj_utils.h"
#include "adapter/ohos/entrance/data_ability_helper_standard.h"
#include "adapter/ohos/entrance/file_asset_provider_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider_impl.h"
#include "adapter/ohos/entrance/high_contrast_observer.h"
#include "adapter/ohos/entrance/mmi_event_convertor.h"
#include "adapter/ohos/entrance/ui_content_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/page_viewport_config_ohos.h"
#include "adapter/ohos/osal/resource_adapter_impl_v2.h"
#include "adapter/ohos/osal/system_bar_style_ohos.h"
#include "adapter/ohos/osal/view_data_wrap_ohos.h"
#include "adapter/ohos/osal/window_utils.h"
#include "base/i18n/localization.h"
#include "base/log/event_report.h"
#include "base/log/jank_frame_report.h"
#include "base/memory/referenced.h"
#include "base/thread/background_task_executor.h"
#include "base/subwindow/subwindow_manager.h"
#include "bridge/card_frontend/card_frontend.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "bridge/js_frontend/js_frontend.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/common/ace_application_info.h"
#include "core/common/ace_engine.h"
#include "core/common/plugin_manager.h"
#include "core/common/resource/resource_manager.h"
#include "core/common/resource/resource_wrapper.h"
#include "core/common/task_executor_impl.h"
#include "core/common/text_field_manager.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/image_provider/image_decoder.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/pattern/text_field/text_field_pattern.h"
#include "core/components_ng/render/adapter/form_render_window.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_window.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
#include "adapter/ohos/entrance/ace_rosen_sync_task.h"
#endif

#include "base/ressched/ressched_report.h"

#include "accessibility_config.h"

namespace OHOS::Ace::Platform {
namespace {
constexpr uint32_t DIRECTION_KEY = 0b1000;
constexpr uint32_t DENSITY_KEY = 0b0100;
constexpr uint32_t POPUPSIZE_HEIGHT = 0;
constexpr uint32_t POPUPSIZE_WIDTH = 0;
constexpr int32_t SEARCH_ELEMENT_TIMEOUT_TIME = 1500;
constexpr int32_t POPUP_CALCULATE_RATIO = 2;
constexpr int32_t POPUP_EDGE_INTERVAL = 8;
constexpr int32_t POPUP_MIN_EDGE = 1;
constexpr uint32_t DEFAULT_WINDOW_TYPE = 1;
const char ENABLE_DEBUG_BOUNDARY_KEY[] = "persist.ace.debug.boundary.enabled";
const char ENABLE_TRACE_LAYOUT_KEY[] = "persist.ace.trace.layout.enabled";
const char ENABLE_TRACE_INPUTEVENT_KEY[] = "persist.ace.trace.inputevent.enabled";
const char ENABLE_SECURITY_DEVELOPERMODE_KEY[] = "const.security.developermode.state";
const char ENABLE_DEBUG_STATEMGR_KEY[] = "persist.ace.debug.statemgr.enabled";
const char ENABLE_PERFORMANCE_MONITOR_KEY[] = "persist.ace.performance.monitor.enabled";
const char IS_FOCUS_ACTIVE_KEY[] = "persist.gesture.smart_gesture_enable";
std::mutex g_mutexFormRenderFontFamily;
constexpr uint32_t RES_TYPE_CROWN_ROTATION_STATUS = 129;
constexpr int32_t EXTENSION_HALF_SCREEN_MODE = 2;
constexpr int32_t DARK_RES_DUMP_MIN_SIZE = 3;
constexpr size_t RESOURCE_CACHE_DEFAULT_SIZE = 5;
#ifdef _ARM64_
const std::string ASSET_LIBARCH_PATH = "/lib/arm64";
#else
const std::string ASSET_LIBARCH_PATH = "/lib/arm";
#endif
constexpr uint32_t OHOS_THEME_ID = 125829872;

#ifndef NG_BUILD
constexpr char ARK_ENGINE_SHARED_LIB[] = "libace_engine_ark.z.so";
const char* GetEngineSharedLibrary()
{
    return ARK_ENGINE_SHARED_LIB;
}
#endif

inline void SetSystemBarPropertyEnableFlag(Rosen::SystemBarProperty& property)
{
    property.settingFlag_ = static_cast<Rosen::SystemBarSettingFlag>(
        static_cast<uint32_t>(property.settingFlag_) |
        static_cast<uint32_t>(Rosen::SystemBarSettingFlag::ENABLE_SETTING));
}

std::string StringifyAvoidAreas(const std::map<OHOS::Rosen::AvoidAreaType, OHOS::Rosen::AvoidArea>& avoidAreas)
{
    std::string res = "[";
    std::for_each(avoidAreas.begin(), avoidAreas.end(), [&res](const auto& avoidArea) {
        res =
            res + "(" + std::to_string(static_cast<int32_t>(avoidArea.first)) + "," + avoidArea.second.ToString() + ")";
    });
    res = res + "]";
    return res;
}

class WindowOrientationChangeListener : public OHOS::Rosen::IWindowOrientationChangeListener {
public:
    explicit WindowOrientationChangeListener(int32_t instanceId, WeakPtr<NG::NavigationManager> mgr)
        : instanceId_(instanceId), mgr_(mgr) {}
    ~WindowOrientationChangeListener() = default;

    void OnOrientationChange() override
    {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "window orientation change");
        auto container = AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipeline = container->GetPipelineContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto task = [mgr = mgr_, instanceId = instanceId_]() {
            ContainerScope scope(instanceId);
            auto navMgr = mgr.Upgrade();
            CHECK_NULL_VOID(navMgr);
            navMgr->OnOrientationChanged();
        };
        if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            task();
            return;
        }
        taskExecutor->PostSyncTask(std::move(task), TaskExecutor::TaskType::UI,
            "ArkUIOnOrientationChange", PriorityType::VIP);
    }

private:
    int32_t instanceId_ = -1;
    WeakPtr<NG::NavigationManager> mgr_;
};

constexpr char DECLARATIVE_ARK_ENGINE_SHARED_LIB[] = "libace_engine_declarative_ark.z.so";
const char* GetDeclarativeSharedLibrary()
{
    return DECLARATIVE_ARK_ENGINE_SHARED_LIB;
}

void LoadSystemThemeFromJson(const RefPtr<AssetManager>& assetManager, const RefPtr<PipelineBase>& pipelineContext,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    CHECK_NULL_VOID(assetManager);
    CHECK_NULL_VOID(pipelineContext);
    CHECK_NULL_VOID(context);
    auto hapModuleInfo = context->GetHapModuleInfo();
    CHECK_NULL_VOID(hapModuleInfo);
    std::string themeConfigFilePath = hapModuleInfo->systemTheme;
    if (themeConfigFilePath.empty()) {
        LOGW("not found systemTheme in HapModuleInfo, loading default OHOS_THEME");
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        themeManager->SetSystemThemeId(OHOS_THEME_ID);
        return;
    }
    constexpr char profilePrefix[] = "$profile:";
    constexpr char themeConfigDefaultName[] = "theme_config";
    constexpr char jsonSubfix[] = ".json";
    constexpr char themePrefix[] = "$theme:";
    if (!StringUtils::StartWith(themeConfigFilePath,
        std::string(profilePrefix) + std::string(themeConfigDefaultName))) { // start with: "$profile:theme_config"
        LOGW("path: %{public}s doesn't start with %{public}s%{public}s, loading default OHOS_THEME",
            themeConfigFilePath.c_str(), profilePrefix, themeConfigDefaultName);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_VOID(themeManager);
        themeManager->SetSystemThemeId(OHOS_THEME_ID);
        return;
    }
    themeConfigFilePath = themeConfigFilePath.substr(sizeof(profilePrefix) - 1) + jsonSubfix; // e.g. theme_config.json
    std::string themeJsonContent;
    bool loadThemeJsonFlag =
        OHOS::Ace::Framework::GetAssetContentImpl(assetManager, themeConfigFilePath, themeJsonContent);
    if (loadThemeJsonFlag) {
        auto themeRootJson = JsonUtil::ParseJsonString(themeJsonContent);
        if (themeRootJson) {
            std::string systemThemeValue = themeRootJson->GetString("systemTheme", ""); // e.g. $theme:125829872
            if (!systemThemeValue.empty() && StringUtils::StartWith(systemThemeValue, themePrefix) &&
                systemThemeValue.size() > sizeof(themePrefix) - 1) {
                auto systemThemeId = StringUtils::StringToInt(systemThemeValue.substr(sizeof(themePrefix) - 1));
                auto themeManager = pipelineContext->GetThemeManager();
                CHECK_NULL_VOID(themeManager);
                themeManager->SetSystemThemeId(systemThemeId);
                auto checkTheme = themeManager->GetSystemTheme();
                LOGI("get systemThemeId from json success, systemTheme id = %{public}d", checkTheme);
            } else {
                LOGW("get systemThemeId from json failed, not a valid id");
            }
        } else {
            LOGW("get systemThemeId from json failed, parse theme json file failed");
        }
    } else {
        LOGW("get systemTheme id from json failed, %{public}s not found", themeConfigFilePath.c_str());
    }
}

void InitResourceAndThemeManager(const RefPtr<PipelineBase>& pipelineContext, const RefPtr<AssetManager>& assetManager,
    const ColorScheme& colorScheme, const ResourceInfo& resourceInfo,
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& context,
    const std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& abilityInfo, bool clearCache = false)
{
    std::string bundleName = "";
    std::string moduleName = "";
    if (context) {
        bundleName = context->GetBundleName();
        moduleName = context->GetHapModuleInfo()->name;
    } else if (abilityInfo) {
        bundleName = abilityInfo->bundleName;
        moduleName = abilityInfo->moduleName;
    } else {
        auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
        CHECK_NULL_VOID(systemAbilityMgr);
        auto bundleObj = systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
        CHECK_NULL_VOID(bundleObj);
        auto bundleMgrProxy = iface_cast<AppExecFwk::IBundleMgr>(bundleObj);
        CHECK_NULL_VOID(bundleMgrProxy);
        AppExecFwk::BundleInfo bundleInfo;
        bundleMgrProxy->GetBundleInfoForSelf(
            static_cast<int32_t>(AppExecFwk::GetBundleInfoFlag::GET_BUNDLE_INFO_WITH_HAP_MODULE), bundleInfo);
        bundleName = bundleInfo.name;
        moduleName = bundleInfo.entryModuleName;                
    }
    int32_t instanceId = pipelineContext->GetInstanceId();
    RefPtr<ResourceAdapter> resourceAdapter = nullptr;
    if (context && context->GetResourceManager()) {
        resourceAdapter = AceType::MakeRefPtr<ResourceAdapterImplV2>(context->GetResourceManager(), resourceInfo);
    } else if (ResourceManager::GetInstance().IsResourceAdapterRecord(bundleName, moduleName, instanceId)) {
        resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(bundleName, moduleName, instanceId);
    }

    if (resourceAdapter == nullptr) {
        resourceAdapter = ResourceAdapter::CreateV2();
        resourceAdapter->Init(resourceInfo);
    }

    ThemeConstants::InitDeviceType();
    auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>(resourceAdapter);
    pipelineContext->SetThemeManager(themeManager);
    LoadSystemThemeFromJson(assetManager, pipelineContext, context);
    themeManager->SetColorScheme(colorScheme);
    themeManager->LoadCustomTheme(assetManager);
    themeManager->LoadResourceThemes();

    if (clearCache) {
        ResourceManager::GetInstance().Reset();
    }

    auto defaultBundleName = "";
    auto defaultModuleName = "";
    ResourceManager::GetInstance().AddResourceAdapter(
        defaultBundleName, defaultModuleName, instanceId, resourceAdapter, true);
    if (!bundleName.empty() && !moduleName.empty()) {
        ResourceManager::GetInstance().RegisterMainResourceAdapter(bundleName, moduleName, instanceId, resourceAdapter);
        ResourceManager::GetInstance().RegisterMainResourceAdapter(
            bundleName, moduleName, INSTANCE_ID_UNDEFINED, resourceAdapter);
    }
}

void InitNavigationManagerCallback(const RefPtr<NG::PipelineContext>& context)
{
    CHECK_NULL_VOID(context);
    auto navMgr = context->GetNavigationManager();
    CHECK_NULL_VOID(navMgr);
    auto getColorCallback = [weakContext = WeakPtr(context)](const std::string& name, Color& color) -> bool {
        auto context = weakContext.Upgrade();
        CHECK_NULL_RETURN(context, false);
        RefPtr<ResourceAdapter> resourceAdapter = nullptr;
        RefPtr<ThemeConstants> themeConstants = nullptr;
        if (SystemProperties::GetResourceDecoupling()) {
            auto container = Container::GetContainer(context->GetInstanceId());
            CHECK_NULL_RETURN(container, false);
            auto resourceObject = AceType::MakeRefPtr<ResourceObject>(
                container->GetBundleName(), container->GetModuleName(), context->GetInstanceId());
            resourceAdapter = ResourceManager::GetInstance().GetOrCreateResourceAdapter(resourceObject);
            CHECK_NULL_RETURN(resourceAdapter, false);
        } else {
            auto themeManager = context->GetThemeManager();
            CHECK_NULL_RETURN(themeManager, false);
            themeConstants = themeManager->GetThemeConstants();
            CHECK_NULL_RETURN(themeConstants, false);
        }
        auto resourceWrapper = AceType::MakeRefPtr<ResourceWrapper>(themeConstants, resourceAdapter);
        CHECK_NULL_RETURN(resourceWrapper, false);
        color = resourceWrapper->GetColorByName(name);
        return true;
    };
    navMgr->SetGetSystemColorCallback(std::move(getColorCallback));
}

std::string EncodeBundleAndModule(const std::string& bundleName, const std::string& moduleName)
{
    return bundleName + " " + moduleName;
}

void DecodeBundleAndModule(const std::string& encode, std::string& bundleName, std::string& moduleName)
{
    std::vector<std::string> tokens;
    StringUtils::StringSplitter(encode, ' ', tokens);
    bundleName = tokens[0];
    moduleName = tokens[1];
}

void ReleaseStorageReference(void* sharedRuntime, NativeReference* storage)
{
    if (sharedRuntime && storage) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(sharedRuntime);
        auto env = reinterpret_cast<napi_env>(nativeEngine);
        napi_delete_reference(env, reinterpret_cast<napi_ref>(storage));
    }
}

void ParseLanguage(ConfigurationChange& configurationChange, const std::string& languageTag)
{
    std::string language;
    std::string script;
    std::string region;
    Localization::ParseLocaleTag(languageTag, language, script, region, false);
    if (!language.empty() || !script.empty() || !region.empty()) {
        configurationChange.languageUpdate = true;
        AceApplicationInfo::GetInstance().SetLocale(language, region, script, "");
    }
}

void ReleaseStorageReference(void* sharedRuntime, void* storage)
{
    if (sharedRuntime && storage) {
        auto* env = reinterpret_cast<ani_env*>(sharedRuntime);
        env->GlobalReference_Delete(reinterpret_cast<ani_object>(storage));
    }
}
} // namespace

AceContainer::AceContainer(int32_t instanceId, FrontendType type, std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility,
    std::unique_ptr<PlatformEventCallback> callback, bool useCurrentEventRunner, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), aceAbility_(aceAbility), useCurrentEventRunner_(useCurrentEventRunner)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SetUsePartialUpdate();
        }
    }
    InitializeTask();
    platformEventCallback_ = std::move(callback);
    useStageModel_ = false;
    auto ability = aceAbility_.lock();
    if (ability) {
        abilityInfo_ = ability->GetAbilityInfo();
    }
    SubscribeHighContrastChange();
}

AceContainer::AceContainer(int32_t instanceId, FrontendType type,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool isSubAceContainer, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SetUsePartialUpdate();
        }
    }
    if (!isSubContainer_) {
        InitializeTask();
    }
    platformEventCallback_ = std::move(callback);
    useStageModel_ = true;
    SubscribeHighContrastChange();
}

// for DynamicComponent
AceContainer::AceContainer(int32_t instanceId, FrontendType type,
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext,
    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo, std::unique_ptr<PlatformEventCallback> callback,
    std::shared_ptr<TaskWrapper> taskWrapper, bool useCurrentEventRunner, bool isSubAceContainer, bool useNewPipeline)
    : instanceId_(instanceId), type_(type), runtimeContext_(std::move(runtimeContext)),
      abilityInfo_(std::move(abilityInfo)), useCurrentEventRunner_(useCurrentEventRunner),
      isSubContainer_(isSubAceContainer)
{
    ACE_DCHECK(callback);
    if (useNewPipeline) {
        SetUseNewPipeline();
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            SetUsePartialUpdate();
        }
    }
    if (!isSubContainer_) {
        InitializeTask(taskWrapper);
    }
    platformEventCallback_ = std::move(callback);
    useStageModel_ = true;
    SubscribeHighContrastChange();
}

AceContainer::AceContainer(int32_t instanceId, FrontendType type) : instanceId_(instanceId), type_(type)
{
    auto taskExecutorImpl = Referenced::MakeRefPtr<TaskExecutorImpl>();
    taskExecutorImpl->InitPlatformThread(true);
    taskExecutor_ = taskExecutorImpl;
    GetSettings().useUIAsJSThread = true;
    GetSettings().usePlatformAsUIThread = true;
    GetSettings().usingSharedRuntime = true;
}

AceContainer::~AceContainer()
{
    std::lock_guard lock(destructMutex_);
    LOGI("Container Destroyed");
    UnsubscribeHighContrastChange();
}

void AceContainer::InitializeTask(std::shared_ptr<TaskWrapper> taskWrapper)
{
    RefPtr<TaskExecutorImpl> taskExecutorImpl;
    if (taskWrapper != nullptr) {
        taskExecutorImpl = Referenced::MakeRefPtr<TaskExecutorImpl>(taskWrapper);
    } else {
        taskExecutorImpl = Referenced::MakeRefPtr<TaskExecutorImpl>();
    }
    taskExecutorImpl->InitPlatformThread(useCurrentEventRunner_);
    taskExecutor_ = taskExecutorImpl;
    // No need to create JS Thread for DECLARATIVE_JS
    if (type_ == FrontendType::DECLARATIVE_JS || type_ == FrontendType::DECLARATIVE_CJ) {
        GetSettings().useUIAsJSThread = true;
    } else {
        taskExecutorImpl->InitJsThread();
    }
}

bool AceContainer::IsKeyboard()
{
    if (uiWindow_ == nullptr) {
        return false;
    }
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_INPUT_METHOD_FLOAT;
}

void AceContainer::Initialize()
{
    ContainerScope scope(instanceId_);
    // For DECLARATIVE_JS frontend use UI as JS Thread, so InitializeFrontend after UI thread created.
    if (type_ != FrontendType::DECLARATIVE_JS && type_ != FrontendType::DECLARATIVE_CJ) {
        InitializeFrontend();
    }
}

bool AceContainer::MaybeRelease()
{
    CHECK_NULL_RETURN(taskExecutor_, true);
    if (taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::PLATFORM)) {
        LOGI("Destroy AceContainer on PLATFORM thread.");
        return true;
    } else {
        std::lock_guard lock(destructMutex_);
        LOGI("Post Destroy AceContainer Task to PLATFORM thread.");
        return !taskExecutor_->PostTask(
            [this] { delete this; }, TaskExecutor::TaskType::PLATFORM, "ArkUIAceContainerDestroy");
    }
}

void AceContainer::Destroy()
{
    LOGI("AceContainer Destroy begin");
    ContainerScope scope(instanceId_);
    RemoveWatchSystemParameter();
    RemoveUISessionCallbacks();
    ReleaseResourceAdapter();
    if (pipelineContext_ && taskExecutor_) {
        // 1. Destroy Pipeline on UI thread.
        RefPtr<PipelineBase> context;
        {
            std::lock_guard<std::mutex> lock(pipelineMutex_);
            context.Swap(pipelineContext_);
        }
        auto uiTask = [context]() { context->Destroy(); };
        if (GetSettings().usePlatformAsUIThread) {
            uiTask();
        } else {
            taskExecutor_->PostTask(uiTask, TaskExecutor::TaskType::UI, "ArkUIPipelineDestroy");
        }

        if (isSubContainer_) {
            // SubAceContainer just return.
            return;
        }

        // 2. Destroy Frontend on JS thread.
        RefPtr<Frontend> frontend;
        {
            std::lock_guard<std::mutex> lock(frontendMutex_);
            frontend.Swap(frontend_);
        }
        auto jsTask = [frontend]() {
            auto lock = frontend->GetLock();
            frontend->Destroy();
        };
        frontend->UpdateState(Frontend::State::ON_DESTROY);
        if (GetSettings().usePlatformAsUIThread && GetSettings().useUIAsJSThread) {
            jsTask();
        } else {
            taskExecutor_->PostTask(jsTask, TaskExecutor::TaskType::JS, "ArkUIFrontendDestroy");
        }
    }
    DestroyToastSubwindow(instanceId_);
    DestroySelectOverlaySubwindow(instanceId_);
    RegisterContainerHandler(nullptr);
    resRegister_.Reset();
    assetManager_.Reset();
}

void AceContainer::DestroyView()
{
    ContainerScope scope(instanceId_);
    std::lock_guard<std::mutex> lock(viewMutex_);
    aceView_ = nullptr;
}

void AceContainer::InitializeFrontend()
{
    auto aceAbility = aceAbility_.lock();
    if (type_ == FrontendType::JS) {
#ifndef NG_BUILD
        frontend_ = Frontend::Create();
        auto jsFrontend = AceType::DynamicCast<JsFrontend>(frontend_);
        auto& loader = Framework::JsEngineLoader::Get(GetEngineSharedLibrary());
        auto jsEngine = loader.CreateJsEngine(instanceId_);
        jsEngine->AddExtraNativeObject("ability", aceAbility.get());
        EngineHelper::AddEngine(instanceId_, jsEngine);
        jsFrontend->SetJsEngine(jsEngine);
        jsFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
        jsFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
#endif
    } else if (type_ == FrontendType::JS_CARD) {
#ifndef NG_BUILD
        AceApplicationInfo::GetInstance().SetCardType();
        frontend_ = AceType::MakeRefPtr<CardFrontend>();
#endif
    } else if (type_ == FrontendType::DECLARATIVE_JS) {
        if (isFormRender_) {
#ifdef FORM_SUPPORTED
            LOGI("Init Form Frontend");
            frontend_ = AceType::MakeRefPtr<FormFrontendDeclarative>();
            auto cardFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
            auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
            RefPtr<Framework::JsEngine> jsEngine;
            if (GetSettings().usingSharedRuntime) {
                jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
            } else {
                jsEngine = loader.CreateJsEngine(instanceId_);
            }
            jsEngine->AddExtraNativeObject("ability", aceAbility.get());
            EngineHelper::AddEngine(instanceId_, jsEngine);
            cardFrontend->SetJsEngine(jsEngine);
            cardFrontend->SetPageProfile(pageProfile_);
            cardFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
            cardFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
            // Card front
            cardFrontend->SetRunningCardId(0); // ArkTsCard : nodeId, Host->FMS->FRS->innersdk
            cardFrontend->SetIsFormRender(true);
#endif
        } else if (!isSubContainer_) {
#ifdef NG_BUILD
            frontend_ = AceType::MakeRefPtr<DeclarativeFrontendNG>();
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
            frontend_ = AceType::MakeRefPtr<DeclarativeFrontend>();
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
            auto& loader = Framework::JsEngineLoader::GetDeclarative(GetDeclarativeSharedLibrary());
            RefPtr<Framework::JsEngine> jsEngine;
            if (GetSettings().usingSharedRuntime) {
                jsEngine = loader.CreateJsEngineUsingSharedRuntime(instanceId_, sharedRuntime_);
            } else {
                jsEngine = loader.CreateJsEngine(instanceId_);
            }
            jsEngine->AddExtraNativeObject("ability", aceAbility.get());
            auto pageUrlCheckFunc =
                [id = instanceId_](const std::string& url, const std::function<void()>& callback,
                    const std::function<void(int32_t, const std::string&)>& silentInstallErrorCallBack) {
                    ContainerScope scope(id);
                    auto container = Container::Current();
                    CHECK_NULL_VOID(container);
                    auto pageUrlChecker = container->GetPageUrlChecker();
                    CHECK_NULL_VOID(pageUrlChecker);
                    pageUrlChecker->LoadPageUrl(url, callback, silentInstallErrorCallBack);
                };
            jsEngine->SetPageUrlCheckFunc(std::move(pageUrlCheckFunc));
            EngineHelper::AddEngine(instanceId_, jsEngine);
            declarativeFrontend->SetJsEngine(jsEngine);
            declarativeFrontend->SetPageProfile(pageProfile_);
            declarativeFrontend->SetNeedDebugBreakPoint(AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint());
            declarativeFrontend->SetDebugVersion(AceApplicationInfo::GetInstance().IsDebugVersion());
        } else {
            frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
            return;
        }
    } else if (type_ == FrontendType::DECLARATIVE_CJ) {
        LOGD("cj Frontend");
        if (!isSubContainer_) {
            auto cjFrontend = CJUtils::LoadCjFrontend(useNewPipeline_, useStageModel_);
            if (cjFrontend == nullptr) {
                LOGE("Create cj frontend failed.");
                return;
            }
            frontend_ = AceType::Claim(reinterpret_cast<Frontend*>(cjFrontend));
        } else {
            frontend_ = OHOS::Ace::Platform::AceContainer::GetContainer(parentId_)->GetFrontend();
            return;
        }
    } else if (type_ == FrontendType::ARK_TS) {
        frontend_ = MakeRefPtr<ArktsFrontend>(sharedRuntime_);
    } else {
        LOGE("Frontend type not supported");
        EventReport::SendAppStartException(AppStartExcepType::FRONTEND_TYPE_ERR);
        return;
    }
    ACE_DCHECK(frontend_);
    auto abilityInfo = abilityInfo_.lock();
    std::shared_ptr<AppExecFwk::AbilityInfo> info = aceAbility ? aceAbility->GetAbilityInfo() : abilityInfo;
    if (info && info->isLauncherAbility) {
        frontend_->DisallowPopLastPage();
    }
    frontend_->Initialize(type_, taskExecutor_);
}

RefPtr<AceContainer> AceContainer::GetContainer(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, nullptr);
    auto aceContainer = AceType::DynamicCast<AceContainer>(container);
    return aceContainer;
}

bool MarkRemoveOverlayInSubwindow(const RefPtr<Subwindow> subwindow, int32_t instanceId)
{
    if (subwindow && subwindow->GetShown()) {
        auto subContainerId = SubwindowManager::GetInstance()->GetSubContainerId(instanceId);
        if (subContainerId < 0) {
            return false;
        }
        ContainerScope scope(subContainerId);
        auto overlayManager = subwindow->GetOverlayManager();
        CHECK_NULL_RETURN(overlayManager, false);
        return overlayManager->RemoveOverlayInSubwindow();
    }
    return false;
}

bool AceContainer::RemoveOverlayBySubwindowManager(int32_t instanceId)
{
    auto sortSubwindow = SubwindowManager::GetInstance()->GetSortSubwindow(instanceId);
    for (const auto& subwindow : sortSubwindow) {
        if (!MarkRemoveOverlayInSubwindow(subwindow, instanceId)) {
            continue;
        }
        return true;
    }
    return false;
}

std::shared_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetAbilityContext()
{
    auto context = runtimeContext_.lock();
    if (context == nullptr) {
        LOGW("runtimeContext_ is null.");
    }

    return context;
}

std::shared_ptr<void> AceContainer::SerializeValue(
    const std::shared_ptr<Framework::JsValue>& jsValue)
{
    ContainerScope scope(instanceId_);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    CHECK_NULL_RETURN(declarativeFrontend, nullptr);
    auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(
        declarativeFrontend->GetJsEngine());
    CHECK_NULL_RETURN(jsEngine, nullptr);
    return jsEngine->SerializeValue(jsValue);
}

void AceContainer::TriggerModuleSerializer()
{
    ContainerScope scope(instanceId_);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    CHECK_NULL_VOID(declarativeFrontend);
    auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(
        declarativeFrontend->GetJsEngine());
    CHECK_NULL_VOID(jsEngine);
    jsEngine->TriggerModuleSerializer();
}

void AceContainer::SetJsContextWithDeserialize(const std::shared_ptr<void>& recoder)
{
    ContainerScope scope(instanceId_);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    CHECK_NULL_VOID(declarativeFrontend);
    auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(declarativeFrontend->GetJsEngine());
    CHECK_NULL_VOID(jsEngine);
    jsEngine->SetJsContextWithDeserialize(recoder);
}

void AceContainer::SetJsContext(const std::shared_ptr<Framework::JsValue>& jsContext)
{
    ContainerScope scope(instanceId_);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    CHECK_NULL_VOID(declarativeFrontend);
    auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(declarativeFrontend->GetJsEngine());
    CHECK_NULL_VOID(jsEngine);
    jsEngine->SetJsContext(jsContext);
}

std::shared_ptr<Framework::JsValue> AceContainer::GetJsContext()
{
    ContainerScope scope(instanceId_);
#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    CHECK_NULL_RETURN(declarativeFrontend, nullptr);
    auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(declarativeFrontend->GetJsEngine());
    CHECK_NULL_RETURN(jsEngine, nullptr);
    return jsEngine->GetJsContext();
}

bool AceContainer::OnBackPressed(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    // When the container is for overlay, it need close the overlay first.
    if (container->IsSubContainer()) {
#ifdef NG_BUILD
        TAG_LOGI(AceLogTag::ACE_UIEVENT, "back press for remove overlay node");
        ContainerScope scope(instanceId);
        auto subPipelineContext = DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
        CHECK_NULL_RETURN(subPipelineContext, false);
        auto overlayManager = subPipelineContext->GetOverlayManager();
        CHECK_NULL_RETURN(overlayManager, false);
        return overlayManager->RemoveOverlayInSubwindow();
#else
        if (container->IsUseNewPipeline()) {
            TAG_LOGI(AceLogTag::ACE_UIEVENT, "back press for remove overlay node");
            ContainerScope scope(instanceId);
            auto subPipelineContext = DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_RETURN(subPipelineContext, false);
            auto textfieldMgr = DynamicCast<NG::TextFieldManagerNG>(subPipelineContext->GetTextFieldManager());
            if (textfieldMgr) {
                auto lastRequestKeyboardNodeId = textfieldMgr->GetLastRequestKeyboardId();
                auto lastRequestKeyboardNode = DynamicCast<NG::FrameNode>(
                    ElementRegister::GetInstance()->GetUINodeById(lastRequestKeyboardNodeId));
                if (lastRequestKeyboardNode && lastRequestKeyboardNode->GetPageId() == -1 &&
                    textfieldMgr->OnBackPressed()) {
                    LOGI("textfield consumed backpressed event");
                    return true;
                }
            }
            auto overlayManager = subPipelineContext->GetOverlayManager();
            CHECK_NULL_RETURN(overlayManager, false);
            if (overlayManager->RemoveOverlayInSubwindow()) {
                TAG_LOGI(AceLogTag::ACE_UIEVENT, "subwindow consumed backpressed event");
                return true;
            }
            instanceId = SubwindowManager::GetInstance()->GetParentContainerId(instanceId);
        } else {
            SubwindowManager::GetInstance()->CloseMenu();
            TAG_LOGI(AceLogTag::ACE_UIEVENT, "Menu consumed backpressed event");
            return true;
        }
#endif
    }
    // remove overlay through SubwindowManager if subwindow unfocused.
    if (RemoveOverlayBySubwindowManager(instanceId)) {
        TAG_LOGI(AceLogTag::ACE_UIEVENT, "subwindow consumed backpressed event");
        return true;
    }
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    if (context->PopPageStackOverlay()) {
        return true;
    }
    return context->CallRouterBackToPopPage();
}

void AceContainer::OnShow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (!container->UpdateState(Frontend::State::ON_SHOW)) {
        return;
    }

    auto jsTask = [container, front = container->GetFrontend()]() {
        if (front && !container->IsSubContainer()) {
            front->UpdateState(Frontend::State::ON_SHOW);
            front->OnShow();
        }
    };

    auto uiTask = [container]() {
        std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap;
        container->GetCardFrontendMap(cardFrontendMap);
        for (const auto& [_, weakCardFront] : cardFrontendMap) {
            auto cardFront = weakCardFront.Upgrade();
            if (!cardFront) {
                LOGE("cardFront is null");
                continue;
            }
            cardFront->OnShow();
        }
        auto pipelineBase = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineBase);
        pipelineBase->OnShow();
        pipelineBase->SetForegroundCalled(true);
    };

    // stege model needn't post task when already run on UI
    if (container->GetSettings().useUIAsJSThread && taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        jsTask();
        uiTask();
    } else {
        taskExecutor->PostTask(jsTask, TaskExecutor::TaskType::JS, "ArkUIFrontendShow");
        taskExecutor->PostTask(uiTask, TaskExecutor::TaskType::UI, "ArkUICardFrontendShow");
    }
}

void AceContainer::OnHide(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (!container->UpdateState(Frontend::State::ON_HIDE)) {
        return;
    }
    std::unordered_map<int64_t, WeakPtr<Frontend>> cardFrontendMap;
    container->GetCardFrontendMap(cardFrontendMap);

    auto jsTask = [container, front = container->GetFrontend(), cardFrontendMap]() {
        if (front && !container->IsSubContainer()) {
            front->UpdateState(Frontend::State::ON_HIDE);
            front->OnHide();
            front->TriggerGarbageCollection();
        }
        for (const auto& [_, weakCardFront] : cardFrontendMap) {
            auto cardFront = weakCardFront.Upgrade();
            if (!cardFront) {
                LOGE("cardFront is null");
                continue;
            }
            cardFront->TriggerGarbageCollection();
        }
    };

    auto uiTask = [container, cardFrontendMap]() {
        for (const auto& [_, weakCardFront] : cardFrontendMap) {
            auto cardFront = weakCardFront.Upgrade();
            if (!cardFront) {
                LOGE("cardFront is null");
                continue;
            }
            cardFront->OnHide();
        }
        auto pipelineBase = container->GetPipelineContext();
        CHECK_NULL_VOID(pipelineBase);
        pipelineBase->OnHide();
    };

    // stege model needn't post task when already run on UI
    if (container->GetSettings().useUIAsJSThread && taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
        jsTask();
        uiTask();
    } else {
        taskExecutor->PostTask(jsTask, TaskExecutor::TaskType::JS, "ArkUIFrontendHide");
        taskExecutor->PostTask(uiTask, TaskExecutor::TaskType::UI, "ArkUICardFrontendHide");
    }
}

void AceContainer::OnActive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer() && front->GetState() != Frontend::State::ON_ACTIVE) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend, instanceId]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    ContainerScope scope(instanceId);
                    frontend->UpdateState(Frontend::State::ON_ACTIVE);
                    frontend->OnActive();
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIFrontendActive");
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnActive failed.");
                return;
            }
            ContainerScope scope(container->GetInstanceId());
            pipelineContext->WindowFocus(true);
            pipelineContext->ChangeDarkModeBrightness();
        },
        TaskExecutor::TaskType::UI, "ArkUIWindowFocus");
}

void AceContainer::OnInactive(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer() && front->GetState() != Frontend::State::ON_INACTIVE) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend, instanceId]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    ContainerScope scope(instanceId);
                    frontend->UpdateState(Frontend::State::ON_INACTIVE);
                    frontend->OnInactive();
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIFrontendInactive");
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnInactive failed.");
                return;
            }
            ContainerScope scope(container->GetInstanceId());
            pipelineContext->WindowFocus(false);
            pipelineContext->ChangeDarkModeBrightness();
            if (container->IsSceneBoardWindow()) {
                JankFrameReport::GetInstance().FlushRecord();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIWindowUnfocus");
}

void AceContainer::ActiveWindow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend, instanceId]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    ContainerScope scope(instanceId);
                    frontend->UpdateState(Frontend::State::ON_ACTIVE);
                    frontend->OnActive();
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIFrontendActive",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, ActiveWindow failed.");
                return;
            }
            ContainerScope scope(container->GetInstanceId());
            pipelineContext->WindowActivate(true);
            pipelineContext->ChangeDarkModeBrightness();
        },
        TaskExecutor::TaskType::UI, "ArkUIWindowActivate", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void AceContainer::UnActiveWindow(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    auto front = container->GetFrontend();
    if (front && !container->IsSubContainer()) {
        WeakPtr<Frontend> weakFrontend = front;
        taskExecutor->PostTask(
            [weakFrontend, instanceId]() {
                auto frontend = weakFrontend.Upgrade();
                if (frontend) {
                    ContainerScope scope(instanceId);
                    frontend->UpdateState(Frontend::State::ON_INACTIVE);
                    frontend->OnInactive();
                }
            },
            TaskExecutor::TaskType::JS, "ArkUIFrontendInactive",
            TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
    }

    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("pipeline context is null, OnInactive failed.");
                return;
            }
            ContainerScope scope(container->GetInstanceId());
            pipelineContext->WindowActivate(false);
            pipelineContext->ChangeDarkModeBrightness();
            if (container->IsSceneBoardWindow()) {
                JankFrameReport::GetInstance().FlushRecord();
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIWindowUnActivate", TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}

void AceContainer::OnNewWant(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnNewWant(data);
}

bool AceContainer::OnStartContinuation(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    return front->OnStartContinuation();
}

std::string AceContainer::OnSaveData(int32_t instanceId)
{
    std::string result = "false";
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, result);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, result);
    front->OnSaveData(result);
    return result;
}

bool AceContainer::OnRestoreData(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    return front->OnRestoreData(data);
}

void AceContainer::OnCompleteContinuation(int32_t instanceId, int result)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnCompleteContinuation(result);
}

void AceContainer::OnRemoteTerminated(int32_t instanceId)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnRemoteTerminated();
}

void AceContainer::OnConfigurationUpdated(int32_t instanceId, const std::string& configuration)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnConfigurationUpdated(configuration);
}

void AceContainer::OnNewRequest(int32_t instanceId, const std::string& data)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    front->OnNewRequest(data);
}

void AceContainer::InitializeCallback()
{
    ACE_FUNCTION_TRACE();
    ACE_DCHECK(aceView_ && taskExecutor_ && pipelineContext_);
    auto touchPassMode = AceApplicationInfo::GetInstance().GetTouchEventPassMode();
    int32_t debugMode = SystemProperties::GetTouchAccelarate();
    if (debugMode != static_cast<int32_t>(touchPassMode)) {
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "Debug touch pass mode %{public}d", debugMode);
        touchPassMode = static_cast<TouchPassMode>(debugMode);
        AceApplicationInfo::GetInstance().SetTouchEventPassMode(touchPassMode);
    }
    pipelineContext_->SetTouchAccelarate(touchPassMode == TouchPassMode::ACCELERATE);
    pipelineContext_->SetTouchPassThrough(touchPassMode == TouchPassMode::PASS_THROUGH);
    auto&& touchEventCallback = [context = pipelineContext_, id = instanceId_](const TouchEvent& event,
                                    const std::function<void()>& markProcess,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->CheckAndLogLastReceivedTouchEventInfo(event.touchEventId, event.type);
        auto touchTask = [context, event, markProcess, node]() {
            if (event.type == TouchType::HOVER_ENTER || event.type == TouchType::HOVER_MOVE ||
                event.type == TouchType::HOVER_EXIT || event.type == TouchType::HOVER_CANCEL) {
                context->OnAccessibilityHoverEvent(event, node);
            } else if (event.IsPenHoverEvent()) {
                context->OnPenHoverEvent(event, node);
            } else {
                if (node) {
                    context->OnTouchEvent(event, node, false);
                } else {
                    context->OnTouchEvent(event, false);
                }
            }
            CHECK_NULL_VOID(markProcess);
            markProcess();
            context->CheckAndLogLastConsumedTouchEventInfo(event.touchEventId, event.type);
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            touchTask();
            return;
        }
        context->GetTaskExecutor()->PostTask(
            touchTask, TaskExecutor::TaskType::UI, "ArkUIAceContainerTouchEvent", PriorityType::VIP);
    };
    aceView_->RegisterTouchEventCallback(touchEventCallback);

    auto&& mouseEventCallback = [context = pipelineContext_, id = instanceId_](const MouseEvent& event,
                                    const std::function<void()>& markProcess,
                                    const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->CheckAndLogLastReceivedMouseEventInfo(event.touchEventId, event.action);
        auto mouseTask = [context, event, markProcess, node]() {
            if (node) {
                context->OnMouseEvent(event, node);
            } else {
                context->OnMouseEvent(event);
            }
            CHECK_NULL_VOID(markProcess);
            markProcess();
            context->CheckAndLogLastConsumedMouseEventInfo(event.touchEventId, event.action);
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            mouseTask();
            return;
        }
        context->GetTaskExecutor()->PostTask(
            mouseTask, TaskExecutor::TaskType::UI, "ArkUIAceContainerMouseEvent", PriorityType::VIP);
    };
    aceView_->RegisterMouseEventCallback(mouseEventCallback);

    auto&& axisEventCallback = [context = pipelineContext_, id = instanceId_](const AxisEvent& event,
                                   const std::function<void()>& markProcess,
                                   const RefPtr<OHOS::Ace::NG::FrameNode>& node) {
        ContainerScope scope(id);
        context->CheckAndLogLastReceivedAxisEventInfo(event.touchEventId, event.action);
        auto axisTask = [context, event, markProcess, node]() {
            if (node) {
                context->OnAxisEvent(event, node);
            } else {
                context->OnAxisEvent(event);
            }
            CHECK_NULL_VOID(markProcess);
            markProcess();
            context->CheckAndLogLastConsumedAxisEventInfo(event.touchEventId, event.action);
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            axisTask();
            return;
        }
        context->GetTaskExecutor()->PostTask(
            axisTask, TaskExecutor::TaskType::UI, "ArkUIAceContainerAxisEvent", PriorityType::VIP);
    };
    aceView_->RegisterAxisEventCallback(axisEventCallback);

    auto&& nonPointerEventCallback = [context = pipelineContext_, id = instanceId_](
                                         const NonPointerEvent& event, const std::function<void()>& markProcess) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, &event, &result, id, markProcess]() {
                ContainerScope scope(id);
                result = context->OnNonPointerEvent(event);
                CHECK_NULL_VOID(markProcess);
                markProcess();
            },
            TaskExecutor::TaskType::UI, "ArkUIAceContainerNonPointerEvent", PriorityType::VIP);
        return result;
    };
    aceView_->RegisterNonPointerEventCallback(nonPointerEventCallback);

    auto&& crownEventCallback = [context = pipelineContext_, id = instanceId_](
                                    const CrownEvent& event, const std::function<void()>& markProcess) {
        if (event.action == CrownAction::BEGIN || event.action == CrownAction::END) {
            std::unordered_map<std::string, std::string> mapPayload;
            ResSchedReport::GetInstance().ResSchedDataReport(
                RES_TYPE_CROWN_ROTATION_STATUS, static_cast<int32_t>(event.action), mapPayload);
        }
        ContainerScope scope(id);
        auto crownTask = [context, event, markProcess, id]() {
            ContainerScope scope(id);
            context->OnNonPointerEvent(event);
            CHECK_NULL_VOID(markProcess);
            markProcess();
        };
        auto uiTaskRunner = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        if (uiTaskRunner.IsRunOnCurrentThread()) {
            crownTask();
            return;
        }
        context->GetTaskExecutor()->PostTask(
            crownTask, TaskExecutor::TaskType::UI, "ArkUIAceContainerCrownEvent", PriorityType::VIP);
    };
    aceView_->RegisterCrownEventCallback(crownEventCallback);

    auto&& rotationEventCallback = [context = pipelineContext_, id = instanceId_](const RotationEvent& event) {
        ContainerScope scope(id);
        bool result = false;
        context->GetTaskExecutor()->PostSyncTask(
            [context, event, &result]() { result = context->OnRotationEvent(event); }, TaskExecutor::TaskType::UI,
            "ArkUIAceContainerRotationEvent");
        return result;
    };
    aceView_->RegisterRotationEventCallback(rotationEventCallback);

    auto&& viewChangeCallback = [context = pipelineContext_, id = instanceId_](int32_t width, int32_t height,
                                    WindowSizeChangeReason type,
                                    const std::shared_ptr<Rosen::RSTransaction>& rsTransaction) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE_COMMERCIAL("ViewChangeCallback(%d, %d)", width, height);
        auto callback = [context, width, height, type, rsTransaction]() {
            context->OnSurfaceChanged(width, height, type, rsTransaction);
        };
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if ((container->IsUseStageModel() && type == WindowSizeChangeReason::ROTATION) ||
            taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            callback();
        } else {
            taskExecutor->PostTask(callback, TaskExecutor::TaskType::UI, "ArkUISubwindowResizeWindow");
        }
    };
    aceView_->RegisterViewChangeCallback(viewChangeCallback);

    auto&& viewPositionChangeCallback = [context = pipelineContext_, id = instanceId_](int32_t posX, int32_t posY) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("ViewPositionChangeCallback(%d, %d)", posX, posY);
        context->GetTaskExecutor()->PostTask(
            [context, posX, posY]() { context->OnSurfacePositionChanged(posX, posY); },
            TaskExecutor::TaskType::UI, "ArkUISurfacePositionChanged");
    };
    aceView_->RegisterViewPositionChangeCallback(viewPositionChangeCallback);

    auto&& densityChangeCallback = [context = pipelineContext_, id = instanceId_](double density) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("DensityChangeCallback(%lf)", density);
        auto callback = [context, density, id]() {
            context->OnSurfaceDensityChanged(density);
            if (context->IsNeedReloadDensity()) {
                auto container = Container::GetContainer(id);
                CHECK_NULL_VOID(container);
                auto aceContainer = DynamicCast<AceContainer>(container);
                CHECK_NULL_VOID(aceContainer);
                aceContainer->NotifyDensityUpdate(density);
                context->SetIsNeedReloadDensity(false);
            }
        };
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            callback();
        } else {
            taskExecutor->PostTask(callback, TaskExecutor::TaskType::UI, "ArkUISurfaceDensityChanged");
        }
    };
    aceView_->RegisterDensityChangeCallback(densityChangeCallback);

    auto&& transformHintChangeCallback = [context = pipelineContext_, id = instanceId_](uint32_t transform) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("TransformHintChangeCallback(%d)", transform);
        auto callback = [context, transform]() { context->OnTransformHintChanged(transform); };
        auto taskExecutor = context->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            callback();
        } else {
            taskExecutor->PostTask(callback, TaskExecutor::TaskType::UI, "ArkUITransformHintChanged");
        }
    };
    aceView_->RegisterTransformHintChangeCallback(transformHintChangeCallback);

    auto&& systemBarHeightChangeCallback = [context = pipelineContext_, id = instanceId_](
                                               double statusBar, double navigationBar) {
        ContainerScope scope(id);
        ACE_SCOPED_TRACE("SystemBarHeightChangeCallback(%lf, %lf)", statusBar, navigationBar);
        context->GetTaskExecutor()->PostTask(
            [context, statusBar, navigationBar]() { context->OnSystemBarHeightChanged(statusBar, navigationBar); },
            TaskExecutor::TaskType::UI, "ArkUISystemBarHeightChanged");
    };
    aceView_->RegisterSystemBarHeightChangeCallback(systemBarHeightChangeCallback);

    auto&& surfaceDestroyCallback = [context = pipelineContext_, id = instanceId_]() {
        ContainerScope scope(id);
        context->GetTaskExecutor()->PostTask(
            [context]() { context->OnSurfaceDestroyed(); }, TaskExecutor::TaskType::UI, "ArkUISurfaceDestroyed");
    };
    aceView_->RegisterSurfaceDestroyCallback(surfaceDestroyCallback);
    InitDragEventCallback();
}

void AceContainer::InitDragEventCallback()
{
    // Ensure drag callbacks are registered for dynamic components
    if (!isFormRender_ || isDynamicRender_) {
        auto&& dragEventCallback = [context = pipelineContext_, id = instanceId_](const DragPointerEvent& pointerEvent,
                                       const DragEventAction& action, const RefPtr<NG::FrameNode>& node) {
            ContainerScope scope(id);
            CHECK_NULL_VOID(context);
            auto callback = [context, pointerEvent, action, node, id]() {
                ContainerScope scope(id);
                context->OnDragEvent(pointerEvent, action, node);
            };
            auto taskExecutor = context->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            auto uiTaskRunner = SingleTaskExecutor::Make(taskExecutor, TaskExecutor::TaskType::UI);
            if (uiTaskRunner.IsRunOnCurrentThread()) {
                callback();
                return;
            }
            taskExecutor->PostTask(
                callback, TaskExecutor::TaskType::UI, "ArkUIAceContainerDragEvent", PriorityType::VIP);
        };
        aceView_->RegisterDragEventCallback(dragEventCallback);
    }
}

void AceContainer::CreateContainer(int32_t instanceId, FrontendType type, const std::string& instanceName,
    std::shared_ptr<OHOS::AppExecFwk::Ability> aceAbility, std::unique_ptr<PlatformEventCallback> callback,
    bool useCurrentEventRunner, bool useNewPipeline)
{
    auto aceContainer = AceType::MakeRefPtr<AceContainer>(
        instanceId, type, aceAbility, std::move(callback), useCurrentEventRunner, useNewPipeline);
    AceEngine::Get().AddContainer(instanceId, aceContainer);
    aceContainer->Initialize();
    ContainerScope scope(instanceId);
    auto front = aceContainer->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(aceContainer);
    }

    auto jsFront = AceType::DynamicCast<JsFrontend>(front);
    CHECK_NULL_VOID(jsFront);
    jsFront->SetInstanceName(instanceName);
}

void AceContainer::DestroyContainer(int32_t instanceId, const std::function<void()>& destroyCallback)
{
    SubwindowManager::GetInstance()->CloseDialog(instanceId);
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    container->Destroy();
    // unregister watchdog before stop thread to avoid UI_BLOCK report
    AceEngine::Get().UnRegisterFromWatchDog(instanceId);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);

    taskExecutor->PostSyncTask([] { LOGI("Wait UI thread..."); }, TaskExecutor::TaskType::UI, "ArkUIWaitLog");
    taskExecutor->PostSyncTask([] { LOGI("Wait JS thread..."); }, TaskExecutor::TaskType::JS, "ArkUIWaitLog");

    container->DestroyView(); // Stop all threads(ui,gpu,io) for current ability.
    auto removeContainerTask = [instanceId, destroyCallback] {
        LOGI("Remove on Platform thread...");
        EngineHelper::RemoveEngine(instanceId);
        AceEngine::Get().RemoveContainer(instanceId);
        CHECK_NULL_VOID(destroyCallback);
        destroyCallback();
    };
    if (container->GetSettings().usePlatformAsUIThread) {
        removeContainerTask();
    } else {
        taskExecutor->PostTask(removeContainerTask, TaskExecutor::TaskType::PLATFORM, "ArkUIAceContainerRemove");
    }
}

void AceContainer::SetView(const RefPtr<AceView>& view, double density, int32_t width, int32_t height,
    sptr<OHOS::Rosen::Window> rsWindow, UIEnvCallback callback)
{
    CHECK_NULL_VOID(view);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_VOID(container);
#ifdef ENABLE_ROSEN_BACKEND
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
    window->Init();
#else
    auto platformWindow = PlatformWindow::Create(view);
    CHECK_NULL_VOID(platformWindow);
    auto window = std::make_shared<Window>(std::move(platformWindow));
#endif
    AceContainer::SetUIWindow(view->GetInstanceId(), rsWindow);
    container->AttachView(window, view, density, width, height, rsWindow->GetWindowId(), callback);
}

UIContentErrorCode AceContainer::SetViewNew(
    const RefPtr<AceView>& view, double density, float width, float height, sptr<OHOS::Rosen::Window> rsWindow)
{
#ifdef ENABLE_ROSEN_BACKEND
    CHECK_NULL_RETURN(view, UIContentErrorCode::NULL_POINTER);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(view->GetInstanceId()));
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, UIContentErrorCode::NULL_POINTER);
    AceContainer::SetUIWindow(view->GetInstanceId(), rsWindow);

    if (container->isFormRender_) {
        auto window = std::make_shared<FormRenderWindow>(taskExecutor, view->GetInstanceId());
        container->AttachView(window, view, density, width, height, view->GetInstanceId(), nullptr);
    } else {
        auto window = std::make_shared<NG::RosenWindow>(rsWindow, taskExecutor, view->GetInstanceId());
        window->Init();
        container->AttachView(window, view, density, width, height, rsWindow->GetWindowId(), nullptr);
    }

    return UIContentErrorCode::NO_ERRORS;
#endif
}

void AceContainer::SetUIWindow(int32_t instanceId, sptr<OHOS::Rosen::Window> uiWindow)
{
    CHECK_NULL_VOID(uiWindow);
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    container->SetUIWindowInner(uiWindow);
    if (!container->IsSceneBoardWindow()) {
        ResourceManager::GetInstance().SetResourceCacheSize(RESOURCE_CACHE_DEFAULT_SIZE);
    } else {
        OHOS::Rosen::RSUIDirector::SetTypicalResidentProcess(true);
    }
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindow(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetUIWindowInner();
}

OHOS::AppExecFwk::Ability* AceContainer::GetAbility(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetAbilityInner().lock().get();
}

OHOS::AbilityRuntime::Context* AceContainer::GetRuntimeContext(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, nullptr);
    return container->GetRuntimeContextInner().lock().get();
}

UIContentErrorCode AceContainer::RunPage(
    int32_t instanceId, const std::string& content, const std::string& params, bool isNamedRouter)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);

    auto aceContainer = DynamicCast<AceContainer>(container);
    CHECK_NULL_RETURN(aceContainer, UIContentErrorCode::NULL_POINTER);
    bool isStageModel = aceContainer->IsUseStageModel();
    bool isFormRender = aceContainer->IsFormRender();
    if (isStageModel && content.size() == 0) {
        return UIContentErrorCode::NULL_URL;
    }

    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, UIContentErrorCode::NULL_POINTER);

    if (front->GetType() != FrontendType::DECLARATIVE_CJ && !isFormRender && !isNamedRouter && isStageModel &&
        !CheckUrlValid(content, container->GetHapPath())) {
        return UIContentErrorCode::INVALID_URL;
    }

    if (isNamedRouter) {
        return front->RunPageByNamedRouter(content, params);
    }

    return front->RunPage(content, params);
}

UIContentErrorCode AceContainer::RunPage(
    int32_t instanceId, const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, UIContentErrorCode::NULL_POINTER);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, UIContentErrorCode::NULL_POINTER);
    return front->RunPage(content, params);
}

bool AceContainer::RunDynamicPage(
    int32_t instanceId, const std::string& content, const std::string& params, const std::string& entryPoint)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    front->RunDynamicPage(content, params, entryPoint);
    return true;
}

bool AceContainer::PushPage(int32_t instanceId, const std::string& content, const std::string& params)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, false);
    front->PushPage(content, params);
    return true;
}

bool AceContainer::UpdatePage(int32_t instanceId, int32_t pageId, const std::string& content)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, false);
    ContainerScope scope(instanceId);
    auto context = container->GetPipelineContext();
    CHECK_NULL_RETURN(context, false);
    return context->CallRouterBackToPopPage();
}

class FillRequestCallback : public AbilityRuntime::IFillRequestCallback {
public:
    FillRequestCallback(WeakPtr<NG::PipelineContext> pipelineContext, const RefPtr<NG::FrameNode>& node,
        AceAutoFillType autoFillType, bool isNative = true, const std::function<void()>& onFinish = nullptr)
        : pipelineContext_(pipelineContext), node_(node), autoFillType_(autoFillType), isNative_(isNative),
          onFinish_(onFinish)
    {}
    virtual ~FillRequestCallback() = default;
    void OnFillRequestSuccess(const AbilityBase::ViewData& viewData) override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "called OnFillRequestSuccess, pageUrl=[%{private}zu]",
            viewData.pageUrl.size());
        ProcessOnFinish();
        auto pipelineContext = pipelineContext_.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto viewDataWrap = ViewDataWrap::CreateViewDataWrap(viewData);
        CHECK_NULL_VOID(viewDataWrap);
        if (!isNative_) {
            auto node = node_.Upgrade();
            CHECK_NULL_VOID(node);
            taskExecutor->PostTask(
                [viewDataWrap, node, autoFillType = autoFillType_]() {
                    if (node) {
                        node->NotifyFillRequestSuccess(viewDataWrap, nullptr, autoFillType);
                    }
                },
                TaskExecutor::TaskType::UI, "ArkUINotifyWebFillRequestSuccess");
            return;
        }

        taskExecutor->PostTask(
            [viewDataWrap, pipelineContext, autoFillType = autoFillType_]() {
                if (pipelineContext) {
                    pipelineContext->NotifyFillRequestSuccess(autoFillType, viewDataWrap);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUINotifyFillRequestSuccess");
    }

    void OnFillRequestFailed(int32_t errCode, const std::string& fillContent, bool isPopup) override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "called, errCode: %{public}d", errCode);
        ProcessOnFinish();
        auto pipelineContext = pipelineContext_.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        auto node = node_.Upgrade();
        CHECK_NULL_VOID(node);
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [errCode, pipelineContext, node, fillContent, isPopup]() {
                if (pipelineContext) {
                    pipelineContext->NotifyFillRequestFailed(node, errCode, fillContent, isPopup);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUINotifyFillRequestFailed");
    }

    void onPopupConfigWillUpdate(AbilityRuntime::AutoFill::AutoFillCustomConfig& config) override
    {
        // Non-native component like web/xcomponent
        // The offset needs to be calculated based on the placement
        if (isNative_ || !config.targetSize.has_value() || !config.placement.has_value()) {
            return;
        }
        AbilityRuntime::AutoFill::PopupOffset offset;
        offset.deltaX = GetPopupConfigWillUpdateX(config);
        offset.deltaY = GetPopupConfigWillUpdateY(config);
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "PopupOffset x:%{public}f,y:%{public}f", offset.deltaX, offset.deltaY);
        config.targetOffset = offset;
        config.placement = AbilityRuntime::AutoFill::PopupPlacement::BOTTOM;
    }

    void SetFocusedRect(AbilityBase::Rect rect)
    {
        rect_ = rect;
    }

    void SetWindowRect(Rosen::Rect rect)
    {
        windowRect_ = rect;
    }

private:
    double GetPopupConfigWillUpdateY(AbilityRuntime::AutoFill::AutoFillCustomConfig& config)
    {
        auto node = node_.Upgrade();
        CHECK_NULL_RETURN(node, 0);
        auto rectf = node->GetRectWithRender();
        double deltaY = 0;
        AbilityRuntime::AutoFill::PopupPlacement placement = config.placement.value();
        AbilityRuntime::AutoFill::PopupSize size = config.targetSize.value();

        auto trans = node->GetTransformRelativeOffset();
        auto bottomAvoidHeight = GetBottomAvoidHeight();
        auto edge = PipelineBase::Vp2PxWithCurrentDensity(POPUP_EDGE_INTERVAL);
        auto minEdge = PipelineBase::Vp2PxWithCurrentDensity(POPUP_MIN_EDGE);

        bool isBottom = placement == AbilityRuntime::AutoFill::PopupPlacement::BOTTOM ||
                        placement == AbilityRuntime::AutoFill::PopupPlacement::BOTTOM_LEFT ||
                        placement == AbilityRuntime::AutoFill::PopupPlacement::BOTTOM_RIGHT;
        if ((windowRect_.height_ - rectf.Height() - trans.GetY()) >
                   (size.height + edge * POPUP_CALCULATE_RATIO + bottomAvoidHeight)) {
            // popup will display at the bottom of the container
            if (isBottom) {
                deltaY = rect_.top + rect_.height - rectf.Height() - trans.GetY();
            } else {
                deltaY = rect_.top - rectf.Height() - size.height - trans.GetY() - edge * POPUP_CALCULATE_RATIO;
            }
        } else if (rectf.GetY() > size.height + edge + minEdge) {
            if (isBottom) {
                deltaY = rect_.top - trans.GetY() + rect_.height + size.height + edge * POPUP_CALCULATE_RATIO;
            } else {
                deltaY = rect_.top - trans.GetY();
            }
        } else {
            // popup will display in the middle of the container
            if (isBottom) {
                deltaY = rect_.top + rect_.height - ((rectf.Height() - size.height) / POPUP_CALCULATE_RATIO) -
                         trans.GetY() + edge;
            } else {
                deltaY = rect_.top - ((rectf.Height() + size.height) / POPUP_CALCULATE_RATIO) - trans.GetY() - edge;
            }
        }
        return deltaY;
    }

    double GetPopupConfigWillUpdateX(AbilityRuntime::AutoFill::AutoFillCustomConfig& config)
    {
        auto node = node_.Upgrade();
        CHECK_NULL_RETURN(node, 0);
        auto rectf = node->GetTransformRectRelativeToWindow();
        double deltaX = 0;
        AbilityRuntime::AutoFill::PopupPlacement placement = config.placement.value();
        AbilityRuntime::AutoFill::PopupSize size = config.targetSize.value();

        if (placement == AbilityRuntime::AutoFill::PopupPlacement::TOP_LEFT ||
            placement == AbilityRuntime::AutoFill::PopupPlacement::BOTTOM_LEFT) {
            double edgeDist = (rectf.Width() - size.width) / POPUP_CALCULATE_RATIO;
            deltaX = rect_.left - rectf.Left() - edgeDist;
            if (deltaX > edgeDist) {
                deltaX = edgeDist;
            }
            if (rect_.left + size.width > windowRect_.width_) {
                deltaX = windowRect_.width_ - size.width - edgeDist;
            }
            if (edgeDist + size.width > windowRect_.width_) {
                deltaX = 0;
            }
        }

        if (placement == AbilityRuntime::AutoFill::PopupPlacement::TOP_RIGHT ||
            placement == AbilityRuntime::AutoFill::PopupPlacement::BOTTOM_RIGHT) {
            double edgeDist = (rectf.Width() - size.width) / POPUP_CALCULATE_RATIO;
            deltaX = edgeDist + rect_.left + rect_.width - rectf.Width();
            if ((deltaX < -DBL_EPSILON) && (std::fabs(deltaX) > edgeDist)) {
                deltaX = -edgeDist;
            }
        }
        return deltaX;
    }

    uint32_t GetBottomAvoidHeight()
    {
        auto containerId = Container::CurrentId();
        RefPtr<NG::PipelineContext> pipelineContext;
        if (containerId >= MIN_SUBCONTAINER_ID) {
            auto parentContainerId = SubwindowManager::GetInstance()->GetParentContainerId(containerId);
            auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
            CHECK_NULL_RETURN(parentContainer, 0);
            pipelineContext = AceType::DynamicCast<NG::PipelineContext>(parentContainer->GetPipelineContext());
        } else {
            pipelineContext = NG::PipelineContext::GetCurrentContext();
        }
        CHECK_NULL_RETURN(pipelineContext, 0);
        auto safeAreaManager = pipelineContext->GetSafeAreaManager();
        CHECK_NULL_RETURN(safeAreaManager, 0);
        return safeAreaManager->GetSystemSafeArea().bottom_.Length();
    }

    void ProcessOnFinish()
    {
        if (!onFinish_) {
            return;
        }
        auto pipelineContext = pipelineContext_.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [onFinish = std::move(onFinish_)]() mutable {
                if (onFinish) {
                    onFinish();
                    onFinish = nullptr;
                }
            },
            TaskExecutor::TaskType::UI, "FillRequestCallbackProcessOnFinish");
    }

    WeakPtr<NG::PipelineContext> pipelineContext_ = nullptr;
    WeakPtr<NG::FrameNode> node_ = nullptr;
    AceAutoFillType autoFillType_ = AceAutoFillType::ACE_UNSPECIFIED;
    bool isNative_ = true;
    AbilityBase::Rect rect_;
    Rosen::Rect windowRect_ { 0, 0, 0, 0 };
    std::function<void()> onFinish_;
};

bool AceContainer::UpdatePopupUIExtension(const RefPtr<NG::FrameNode>& node, uint32_t autoFillSessionId, bool isNative)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "UpdatePopupUIExtension called");
    CHECK_NULL_RETURN(node, false);
    CHECK_NULL_RETURN(uiWindow_, false);
    auto uiContent = uiWindow_->GetUIContent();
    auto uiContentImpl = reinterpret_cast<UIContentImpl*>(uiContent);
    CHECK_NULL_RETURN(uiContentImpl, false);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    auto autoFillContainerNode = node->GetFirstAutoFillContainerNode();
    uiContentImpl->DumpViewData(autoFillContainerNode, viewDataWrap, true);
    auto viewDataWrapOhos = AceType::DynamicCast<ViewDataWrapOhos>(viewDataWrap);
    CHECK_NULL_RETURN(viewDataWrapOhos, false);
    auto viewData = viewDataWrapOhos->GetViewData();
    if (!isNative) {
        OverwritePageNodeInfo(node, viewData);
    }
    AbilityRuntime::AutoFillManager::GetInstance().UpdateCustomPopupUIExtension(autoFillSessionId, viewData);
    return true;
}

bool AceContainer::ClosePopupUIExtension(uint32_t autoFillSessionId)
{
    AbilityRuntime::AutoFillManager::GetInstance().CloseUIExtension(autoFillSessionId);
    return true;
}

HintToTypeWrap AceContainer::PlaceHolderToType(const std::string& onePlaceHolder)
{
    HintToTypeWrap hintToTypeWrap;
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    CHECK_NULL_RETURN(viewDataWrap, hintToTypeWrap);
    auto viewDataWrapOhos = AceType::DynamicCast<ViewDataWrapOhos>(viewDataWrap);
    CHECK_NULL_RETURN(viewDataWrapOhos, hintToTypeWrap);
    std::vector<std::string> placeHolder;
    std::vector<int> intType;
    std::vector<std::string> metadata;
    placeHolder.push_back(onePlaceHolder);
    auto isSuccess = viewDataWrapOhos->LoadHint2Type(placeHolder, intType, metadata);
    if (!isSuccess) {
        TAG_LOGE(AceLogTag::ACE_AUTO_FILL, "Load Hint2Type Failed !");
        return hintToTypeWrap;
    }
    if (intType.empty()) {
        return hintToTypeWrap;
    }
    hintToTypeWrap.autoFillType = static_cast<AceAutoFillType>(viewDataWrapOhos->HintToAutoFillType(intType[0]));
    if (!metadata.empty()) {
        hintToTypeWrap.metadata = metadata[0];
    }
    return hintToTypeWrap;
}

void AceContainer::FillAutoFillViewData(const RefPtr<NG::FrameNode>& node, RefPtr<ViewDataWrap>& viewDataWrap)
{
    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(viewDataWrap);
    auto nodeInfoWraps = viewDataWrap->GetPageNodeInfoWraps();
    auto pattern = node->GetPattern<NG::TextFieldPattern>();
    CHECK_NULL_VOID(pattern);
    auto autoFillUserName = pattern->GetAutoFillUserName();
    auto autoFillNewPassword = pattern->GetAutoFillNewPassword();
    if (!autoFillUserName.empty()) {
        for (auto nodeInfoWrap : nodeInfoWraps) {
            if (!nodeInfoWrap) {
                continue;
            }
            auto metadataObject = JsonUtil::ParseJsonString(nodeInfoWrap->GetMetadata());
            if (nodeInfoWrap->GetAutoFillType() == AceAutoFillType::ACE_USER_NAME) {
                nodeInfoWrap->SetValue(autoFillUserName);
                viewDataWrap->SetUserSelected(true);
                break;
            } else if (nodeInfoWrap->GetAutoFillType() == AceAutoFillType::ACE_UNSPECIFIED && metadataObject &&
                       metadataObject->Contains("type")) {
                metadataObject->Put("username", autoFillUserName.c_str());
                nodeInfoWrap->SetMetadata(metadataObject->ToString());
                viewDataWrap->SetUserSelected(true);
            }
        }
        pattern->SetAutoFillUserName("");
    }
    if (!autoFillNewPassword.empty()) {
        for (auto nodeInfoWrap : nodeInfoWraps) {
            if (nodeInfoWrap && nodeInfoWrap->GetAutoFillType() == AceAutoFillType::ACE_NEW_PASSWORD) {
                nodeInfoWrap->SetValue(autoFillNewPassword);
                pattern->SetAutoFillNewPassword("");
                break;
            }
        }
    }
}

void AceContainer::OverwritePageNodeInfo(const RefPtr<NG::FrameNode>& frameNode, AbilityBase::ViewData& viewData)
{
    // Non-native component like web/xcomponent, does not have PageNodeInfo
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    std::vector<AbilityBase::PageNodeInfo> nodeInfos;
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    pattern->DumpViewDataPageNode(viewDataWrap);
    auto infos = viewDataWrap->GetPageNodeInfoWraps();
    for (const auto& info : infos) {
        if (!info) {
            continue;
        }
        AbilityBase::PageNodeInfo node;
        node.id = info->GetId();
        node.depth = -1;
        node.autoFillType = static_cast<AbilityBase::AutoFillType>(info->GetAutoFillType());
        node.isFocus = info->GetIsFocus();
        node.value = info->GetValue();
        node.placeholder = info->GetPlaceholder();
        node.metadata = info->GetMetadata();
        NG::RectF rectF = info->GetPageNodeRect();
        node.rect.left = rectF.GetX();
        node.rect.top = rectF.GetY();
        node.rect.width = rectF.Width();
        node.rect.height = rectF.Height();
        nodeInfos.emplace_back(node);
    }
    viewData.nodes = nodeInfos;
    viewData.pageUrl = viewDataWrap->GetPageUrl();
}

void FillAutoFillCustomConfig(
    const RefPtr<NG::FrameNode>& node, AbilityRuntime::AutoFill::AutoFillCustomConfig& customConfig, bool isNative)
{
    CHECK_NULL_VOID(node);
    AbilityRuntime::AutoFill::PopupSize popupSize;
    popupSize.height = POPUPSIZE_HEIGHT;
    popupSize.width = POPUPSIZE_WIDTH;
    customConfig.targetSize = popupSize;
    customConfig.isShowInSubWindow = false;
    customConfig.nodeId = node->GetId();
    customConfig.isEnableArrow = false;
    if (!isNative) {
        // web component will manually destroy the popup
        customConfig.isAutoCancel = true;
    }
}

void GetFocusedElementRect(const AbilityBase::ViewData& viewData, AbilityBase::Rect& rect)
{
    for (const auto& info : viewData.nodes) {
        if (info.isFocus) {
            rect = info.rect;
        }
    }
}

int32_t AceContainer::RequestAutoFill(const RefPtr<NG::FrameNode>& node, AceAutoFillType autoFillType,
    bool isNewPassWord, bool& isPopup, uint32_t& autoFillSessionId, bool isNative,
    const std::function<void()>& onFinish, const std::function<void()>& onUIExtNodeBindingCompleted)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "called, autoFillType: %{public}d", static_cast<int32_t>(autoFillType));
    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_RETURN(node, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    CHECK_NULL_RETURN(pipelineContext, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    CHECK_NULL_RETURN(uiWindow_, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    auto uiContent = uiWindow_->GetUIContent();
    CHECK_NULL_RETURN(uiContent, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    auto uiContentImpl = reinterpret_cast<UIContentImpl*>(uiContent);
    CHECK_NULL_RETURN(uiContentImpl, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    CHECK_NULL_RETURN(viewDataWrap, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    auto autoFillContainerNode = node->GetFirstAutoFillContainerNode();
    uiContentImpl->DumpViewData(autoFillContainerNode, viewDataWrap, true);
    FillAutoFillViewData(node, viewDataWrap);
    auto callback = std::make_shared<FillRequestCallback>(pipelineContext, node, autoFillType, isNative, onFinish);
    auto viewDataWrapOhos = AceType::DynamicCast<ViewDataWrapOhos>(viewDataWrap);
    CHECK_NULL_RETURN(viewDataWrapOhos, AceAutoFillError::ACE_AUTO_FILL_DEFAULT);
    auto viewData = viewDataWrapOhos->GetViewData();
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "isNewPassWord is: %{public}d", isNewPassWord);
    if (isNewPassWord) {
        callback->OnFillRequestSuccess(viewData);
        return AceAutoFillError::ACE_AUTO_FILL_SUCCESS;
    }
    if (!isNative) {
        OverwritePageNodeInfo(node, viewData);
        AbilityBase::Rect rect;
        GetFocusedElementRect(viewData, rect);
        callback->SetFocusedRect(rect);
        callback->SetWindowRect(uiWindow_->GetRect());
    }
    AbilityRuntime::AutoFill::AutoFillCustomConfig customConfig;
    FillAutoFillCustomConfig(node, customConfig, isNative);
    AbilityRuntime::AutoFill::AutoFillRequest autoFillRequest;
    autoFillRequest.config = customConfig;
    autoFillRequest.autoFillType = static_cast<AbilityBase::AutoFillType>(autoFillType);
    autoFillRequest.autoFillCommand = AbilityRuntime::AutoFill::AutoFillCommand::FILL;
    autoFillRequest.viewData = viewData;
    autoFillRequest.doAfterAsyncModalBinding = std::move(onUIExtNodeBindingCompleted);
    AbilityRuntime::AutoFill::AutoFillResult result;
    auto resultCode =
        AbilityRuntime::AutoFillManager::GetInstance().RequestAutoFill(uiContent, autoFillRequest, callback, result);
    if (resultCode == AceAutoFillError::ACE_AUTO_FILL_SUCCESS) {
        isPopup = result.isPopup;
        autoFillSessionId = result.autoFillSessionId;
    }
    return resultCode;
}

bool AceContainer::IsNeedToCreatePopupWindow(const AceAutoFillType& autoFillType)
{
    return AbilityRuntime::AutoFillManager::GetInstance().IsNeedToCreatePopupWindow(
        static_cast<AbilityBase::AutoFillType>(autoFillType));
}

class SaveRequestCallback : public AbilityRuntime::ISaveRequestCallback {
public:
    SaveRequestCallback(WeakPtr<NG::PipelineContext> pipelineContext, const std::function<void()>& onFinish)
        : pipelineContext_(pipelineContext), onFinish_(onFinish)
    {}
    virtual ~SaveRequestCallback() = default;
    void OnSaveRequestSuccess() override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "OnSaveRequestSuccess called");
        ProcessOnFinish();
    }

    void OnSaveRequestFailed() override
    {
        TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "OnSaveRequestFailed called");
        ProcessOnFinish();
    }

    void ProcessOnFinish()
    {
        if (!onFinish_) {
            return;
        }
        auto pipelineContext = pipelineContext_.Upgrade();
        CHECK_NULL_VOID(pipelineContext);
        auto taskExecutor = pipelineContext->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [onFinish = std::move(onFinish_)]() mutable {
                if (onFinish) {
                    onFinish();
                    onFinish = nullptr;
                }
            },
            TaskExecutor::TaskType::UI, "ProcessOnFinish");
    }

private:
    WeakPtr<NG::PipelineContext> pipelineContext_ = nullptr;
    std::function<void()> onFinish_;
};

bool AceContainer::RequestAutoSave(const RefPtr<NG::FrameNode>& node, const std::function<void()>& onFinish,
    const std::function<void()>& onUIExtNodeBindingCompleted, bool isNative, int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_AUTO_FILL, "RequestAutoSave called");
    CHECK_NULL_RETURN(uiWindow_, false);
    auto uiContent = uiWindow_->GetUIContent();
    auto uiContentImpl = reinterpret_cast<UIContentImpl*>(uiContent);
    CHECK_NULL_RETURN(uiContentImpl, false);
    auto viewDataWrap = ViewDataWrap::CreateViewDataWrap();
    uiContentImpl->DumpViewData(node, viewDataWrap, false, true);

    auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_RETURN(pipelineContext, false);
    auto callback = std::make_shared<SaveRequestCallback>(pipelineContext, onFinish);
    auto viewDataWrapOhos = AceType::DynamicCast<ViewDataWrapOhos>(viewDataWrap);
    CHECK_NULL_RETURN(viewDataWrapOhos, false);
    auto viewData = viewDataWrapOhos->GetViewData();
    if (!isNative) {
        OverwritePageNodeInfo(node, viewData);
    }
    AbilityRuntime::AutoFill::AutoFillRequest autoFillRequest;
    autoFillRequest.viewData = viewData;
    autoFillRequest.autoFillCommand = AbilityRuntime::AutoFill::AutoFillCommand::SAVE;
    autoFillRequest.autoFillType = ViewDataWrap::ViewDataToType(viewData);
    autoFillRequest.doAfterAsyncModalBinding = std::move(onUIExtNodeBindingCompleted);
    if (instanceId != -1) {
        auto uiWindow = GetUIWindow(instanceId);
        CHECK_NULL_RETURN(uiWindow, false);
        uiContent = uiWindow->GetUIContent();
        CHECK_NULL_RETURN(uiContent, false);
    }
    AbilityRuntime::AutoFill::AutoFillResult result;
    if (AbilityRuntime::AutoFillManager::GetInstance().RequestAutoSave(uiContent, autoFillRequest, callback, result) !=
        0) {
        return false;
    }
    return true;
}

std::shared_ptr<NavigationController> AceContainer::GetNavigationController(const std::string& navigationId)
{
    CHECK_NULL_RETURN(pipelineContext_, nullptr);
    return pipelineContext_->GetNavigationController(navigationId);
}

void AceContainer::SetHapPath(const std::string& hapPath)
{
    if (hapPath.empty()) {
        LOGW("SetHapPath, Use .index to load resource");
        return;
    }
    LOGI("SetHapPath, Use hap path to load resource");
    webHapPath_ = hapPath;
    resourceInfo_.SetHapPath(hapPath);
    SystemProperties::SetUnZipHap(false);
}

void AceContainer::Dispatch(
    const std::string& group, std::vector<uint8_t>&& data, int32_t id, bool replyToComponent) const
{
    return;
}

void AceContainer::DispatchPluginError(int32_t callbackId, int32_t errorCode, std::string&& errorMessage) const
{
    auto front = GetFrontend();
    CHECK_NULL_VOID(front);
    ContainerScope scope(instanceId_);
    taskExecutor_->PostTask(
        [front, callbackId, errorCode, errorMessage = std::move(errorMessage)]() mutable {
            front->TransferJsPluginGetError(callbackId, errorCode, std::move(errorMessage));
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIDispatchPluginError");
}

bool AceContainer::Dump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    bool isDynamicUiContent = GetUIContentType() == UIContentType::DYNAMIC_COMPONENT;
    if (isDynamicUiContent) {
        return DumpDynamicUiContent(params, info);
    }

    return DumpCommon(params, info);
}

bool AceContainer::DumpCommon(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    if (isDumping_.test_and_set()) {
        LOGW("another dump is still running");
        return false;
    }
    ContainerScope scope(instanceId_);
    auto result = false;
    paramUie_.assign(params.begin(), params.end());
    if (std::find(params.begin(), params.end(), "-simplify") != params.end()) {
        paramUie_.push_back("-nouie");
    }
    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    CHECK_NULL_RETURN(ostream, false);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    if (IsUIExtensionWindow()) {
        DumpLog::GetInstance().SetUIExtFlag(true);
    }
    auto context = runtimeContext_.lock();
    DumpLog::GetInstance().Print("bundleName:" + context->GetHapModuleInfo()->bundleName);
    DumpLog::GetInstance().Print("moduleName:" + context->GetHapModuleInfo()->moduleName);
    result = DumpInfo(params);
    const auto& infoFile = DumpLog::GetInstance().GetDumpFile();
    auto* ostringstream = static_cast<std::ostringstream*>(infoFile.get());
    info.emplace_back(ostringstream->str());
    DumpLog::GetInstance().Reset();
    if (!result) {
        DumpLog::ShowDumpHelp(info);
    }
    isDumping_.clear();
    return true;
}

bool AceContainer::DumpDynamicUiContent(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    LOGI("DumpDynamicUiContent");
    ContainerScope scope(instanceId_);
    paramUie_.assign(params.begin(), params.end());
    if (std::find(params.begin(), params.end(), "-simplify") != params.end()) {
        paramUie_.push_back("-nouie");
    }
    return DumpInfo(params);
}

bool AceContainer::DumpInfo(const std::vector<std::string>& params)
{
    if (aceView_ && aceView_->Dump(params)) {
        return true;
    }

    if (OnDumpInfo(params)) {
        return true;
    }

    if (DumpRSNodeByStringID(params)) {
        return true;
    }

    if (DumpExistDarkRes(params)) {
        return true;
    }
    CHECK_NULL_RETURN(pipelineContext_, false);
    return pipelineContext_->Dump(params);
}

bool AceContainer::DumpExistDarkRes(const std::vector<std::string>& params)
{
    if (!params.empty() && params[0] == "-existdarkresbyid" && (params.size() >= DARK_RES_DUMP_MIN_SIZE)) {
        DumpLog::GetInstance().Print("------------DumpExistDarkResByID------------");
        auto bundleName = params[1];
        auto moduleName = params[2];
        auto resourceId = params[3];
        auto resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(bundleName, moduleName, instanceId_);
        if (!resourceAdapter) {
            DumpLog::GetInstance().Print(1, "Cannot find resourceAdapter with bundleName:" + bundleName +
                ", moduleName:" + moduleName);
            return true;
        }
        bool existDarkRes = resourceAdapter->ExistDarkResById(resourceId);
        DumpLog::GetInstance().Print(1, std::string(existDarkRes ? "" : "Doesn't ") +
            "Exit dark res with resourceId:" + resourceId);
        return true;
    }
    if (!params.empty() && params[0] == "-existdarkresbyname" && (params.size() > DARK_RES_DUMP_MIN_SIZE)) {
        DumpLog::GetInstance().Print("------------DumpExistDarkResByName------------");
        auto bundleName = params[1];
        auto moduleName = params[2];
        auto resourceName = params[3];
        auto resourceType = params[4];
        auto resourceAdapter = ResourceManager::GetInstance().GetResourceAdapter(bundleName, moduleName, instanceId_);
        if (!resourceAdapter) {
            DumpLog::GetInstance().Print(1, "Cannot find resourceAdapter with bundleName:" + bundleName +
                ", moduleName:" + moduleName);
            return true;
        }
        bool existDarkRes = resourceAdapter->ExistDarkResByName(resourceName, resourceType);
        DumpLog::GetInstance().Print(1, std::string(existDarkRes ? "" : "Doesn't ") +
            "Exit dark res with resourceName:" + resourceName + ", resourceType:" + resourceType);
        return true;
    }
    return false;
}

bool AceContainer::DumpRSNodeByStringID(const std::vector<std::string>& params)
{
    if (!params.empty() && params[0] == "-rsnodebyid" && (params.size() > 1)) {
        DumpLog::GetInstance().Print("------------DumpRSNodeByStringID------------");
        DumpLog::GetInstance().Print(1, "Query by stringid: " + params[1]);
        auto frameNode = NG::Inspector::GetFrameNodeByKey(params[1], true, true);
        if (!frameNode) {
            DumpLog::GetInstance().Print(1, "RSNode Not Found.");
            return true;
        }
        auto renderContext = AceType::DynamicCast<NG::RosenRenderContext>(frameNode->GetRenderContext());
        CHECK_NULL_RETURN(renderContext, true);
        auto rsNode = renderContext->GetRSNode();
        DumpLog::GetInstance().Print(
            1, "RSNode " + (rsNode ? ("name: " + rsNode->GetNodeName() + ", nodeId: " + std::to_string(rsNode->GetId()))
                                   : "Not Found."));
        return true;
    }
    return false;
}

bool AceContainer::OnDumpInfo(const std::vector<std::string>& params)
{
    if (!params.empty() && params[0] == "-basicinfo") {
        DumpLog::GetInstance().Print("BasicInfo: ");
        DumpLog::GetInstance().Print(1, "InstanceId: " + std::to_string(instanceId_));
        DumpLog::GetInstance().Print(1,
            "FrontendType: " + std::to_string(static_cast<typename std::underlying_type<FrontendType>::type>(type_)));
        DumpLog::GetInstance().Print(1, "NewPipeline: " + std::string(IsUseNewPipeline() ? "true" : "false"));
        DumpLog::GetInstance().Print(1, "WindowName: " + windowName_);
        DumpLog::GetInstance().Print(
            1, "WindowState: " +
                   (!frontend_ ? "frontend is null"
                               : std::to_string(static_cast<typename std::underlying_type<Frontend::State>::type>(
                                     frontend_->GetState()))));
        DumpLog::GetInstance().Print(1, "Language: " + AceApplicationInfo::GetInstance().GetLocaleTag());
        DumpLog::GetInstance().Print(
            1, "RTL: " + std::string(AceApplicationInfo::GetInstance().IsRightToLeft() ? "true" : "false"));
        DumpLog::GetInstance().Print(
            1, "ColorMode: " + std::string(GetColorMode() == ColorMode::DARK ? "Dark" : "Light"));
        DumpLog::GetInstance().Print(1,
            "DeviceOrientation: " + std::string(SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE
                                                    ? "Landscape"
                                                    : "Portrait"));
        DumpLog::GetInstance().Print(1, "Resolution: " + std::to_string(SystemProperties::GetDeviceWidth()) + "*" +
                                            std::to_string(SystemProperties::GetDeviceHeight()));
        if (pipelineContext_) {
            DumpLog::GetInstance().Print(1, "AppBgColor: " + pipelineContext_->GetAppBgColor().ColorToString());
            DumpLog::GetInstance().Print(1, "Density: " + std::to_string(pipelineContext_->GetDensity()));
            DumpLog::GetInstance().Print(1, "ViewScale: " + std::to_string(pipelineContext_->GetViewScale()));
            DumpLog::GetInstance().Print(
                1, "DisplayWindowRect: " + pipelineContext_->GetDisplayWindowRectInfo().ToString());
            DumpLog::GetInstance().Print(1, "vsyncID: " + std::to_string(pipelineContext_->GetFrameCount()));
        }
        DumpLog::GetInstance().Print(1, "ApiVersion: " + SystemProperties::GetApiVersion());
        DumpLog::GetInstance().Print(1, "ReleaseType: " + SystemProperties::GetReleaseType());
        DumpLog::GetInstance().Print(1, "DeviceType: " + SystemProperties::GetParamDeviceType());
        return true;
    }
    return false;
}

void AceContainer::TriggerGarbageCollection()
{
    ContainerScope scope(instanceId_);
#if !defined(OHOS_PLATFORM) || !defined(ENABLE_NATIVE_VIEW)
    // GPU and IO thread is standalone while disable native view
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::GPU, "ArkUIPurgeMallocCache");
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::IO, "ArkUIPurgeMallocCache");
#endif
    taskExecutor_->PostTask([] { PurgeMallocCache(); }, TaskExecutor::TaskType::UI, "ArkUIPurgeMallocCache");
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            if (sp) {
                sp->TriggerGarbageCollection();
            }
            PurgeMallocCache();
        },
        TaskExecutor::TaskType::JS, "ArkUITriggerGarbageCollection");
}

void AceContainer::DumpHeapSnapshot(bool isPrivate)
{
    taskExecutor_->PostTask(
        [isPrivate, frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            CHECK_NULL_VOID(sp);
            sp->DumpHeapSnapshot(isPrivate);
        },
        TaskExecutor::TaskType::JS, "ArkUIDumpHeapSnapshot");
}

void AceContainer::DestroyHeapProfiler()
{
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            CHECK_NULL_VOID(sp);
            sp->DestroyHeapProfiler();
        },
        TaskExecutor::TaskType::JS, "ArkUIDestroyHeapProfiler");
}

void AceContainer::ForceFullGC()
{
    taskExecutor_->PostTask(
        [frontend = WeakPtr<Frontend>(frontend_)] {
            auto sp = frontend.Upgrade();
            CHECK_NULL_VOID(sp);
            sp->ForceFullGC();
        },
        TaskExecutor::TaskType::JS, "ArkUIForceFullGC");
}

void AceContainer::SetLocalStorage(
    NativeReference* storage, const std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    ContainerScope scope(instanceId_);
    taskExecutor_->PostSyncTask(
        [frontend = WeakPtr<Frontend>(frontend_), storage,
            contextWeak = std::weak_ptr<OHOS::AbilityRuntime::Context>(context), id = instanceId_,
            sharedRuntime = sharedRuntime_] {
            auto sp = frontend.Upgrade();
            auto contextRef = contextWeak.lock();
            if (!sp || !contextRef) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
#ifdef NG_BUILD
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(sp);
#else
            auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(sp);
#endif
            if (!declarativeFrontend) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
            auto jsEngine = declarativeFrontend->GetJsEngine();
            if (!jsEngine) {
                ReleaseStorageReference(sharedRuntime, storage);
                return;
            }
            if (contextRef->GetBindingObject() && contextRef->GetBindingObject()->Get<NativeReference>()) {
                jsEngine->SetContext(id, contextRef->GetBindingObject()->Get<NativeReference>());
            }
            if (storage) {
                jsEngine->SetLocalStorage(id, storage);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUISetLocalStorage");
}

void AceContainer::SetAniLocalStorage(void* storage, const std::shared_ptr<OHOS::AbilityRuntime::Context>& context)
{
    ContainerScope scope(instanceId_);
    taskExecutor_->PostSyncTask([frontend = WeakPtr<Frontend>(frontend_), storage,
                                    contextWeak = std::weak_ptr<OHOS::AbilityRuntime::Context>(context),
                                    id = instanceId_, sharedRuntime = sharedRuntime_] {
        auto sp = frontend.Upgrade();
        auto contextRef = contextWeak.lock();
        if (!sp || !contextRef) {
            ReleaseStorageReference(sharedRuntime, storage);
            return;
        }
        auto arktsFrontend = AceType::DynamicCast<ArktsFrontend>(sp);
        if (!arktsFrontend) {
            ReleaseStorageReference(sharedRuntime, storage);
            return;
        }
        arktsFrontend->RegisterLocalStorage(id, storage);
    }, TaskExecutor::TaskType::UI, "ArkUISetAniLocalStorage");
}

void AceContainer::AddAssetPath(int32_t instanceId, const std::string& packagePath, const std::string& hapPath,
    const std::vector<std::string>& paths)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    RefPtr<AssetManagerImpl> assetManagerImpl;
    if (container->assetManager_) {
        assetManagerImpl = AceType::DynamicCast<AssetManagerImpl>(container->assetManager_);
    } else {
        assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
        container->assetManager_ = assetManagerImpl;
        if (container->type_ != FrontendType::DECLARATIVE_JS && container->type_ != FrontendType::DECLARATIVE_CJ) {
            container->frontend_->SetAssetManager(assetManagerImpl);
        }
    }
    CHECK_NULL_VOID(assetManagerImpl);
    if (!hapPath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<HapAssetProviderImpl>();
        if (assetProvider->Initialize(hapPath, paths)) {
            LOGI("Push AssetProvider to queue.");
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
    if (!packagePath.empty()) {
        auto assetProvider = AceType::MakeRefPtr<FileAssetProviderImpl>();
        if (assetProvider->Initialize(packagePath, paths)) {
            LOGI("Push AssetProvider to queue.");
            assetManagerImpl->PushBack(std::move(assetProvider));
        }
    }
}

void AceContainer::AddLibPath(int32_t instanceId, const std::vector<std::string>& libPath)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    RefPtr<AssetManager> assetManagerImpl;
    if (container->assetManager_) {
        assetManagerImpl = AceType::DynamicCast<AssetManagerImpl>(container->assetManager_);
    } else {
        assetManagerImpl = Referenced::MakeRefPtr<AssetManagerImpl>();
        container->assetManager_ = assetManagerImpl;
        if (container->type_ != FrontendType::DECLARATIVE_JS && container->type_ != FrontendType::DECLARATIVE_CJ) {
            container->frontend_->SetAssetManager(assetManagerImpl);
        }
    }
    CHECK_NULL_VOID(assetManagerImpl);
    assetManagerImpl->SetLibPath("default", libPath);
}

void AceContainer::SetIsFormRender(bool isFormRender)
{
    OHOS::Rosen::RSUIDirector::SetTypicalResidentProcess(isFormRender);
    isFormRender_ = isFormRender;
}

void AceContainer::AttachView(std::shared_ptr<Window> window, const RefPtr<AceView>& view, double density, float width,
    float height, uint32_t windowId, UIEnvCallback callback)
{
    aceView_ = view;
    auto instanceId = aceView_->GetInstanceId();
    auto taskExecutorImpl = AceType::DynamicCast<TaskExecutorImpl>(taskExecutor_);
    if (!isSubContainer_) {
        auto aceView = AceType::DynamicCast<AceViewOhos>(aceView_);
        ACE_DCHECK(aceView != nullptr);
        taskExecutorImpl->InitOtherThreads(aceView->GetThreadModelImpl());
    }
    ContainerScope scope(instanceId);
    if (type_ == FrontendType::DECLARATIVE_JS || type_ >= FrontendType::DECLARATIVE_CJ) {
        // For DECLARATIVE_JS frontend display UI in JS thread temporarily.
        taskExecutorImpl->InitJsThread(false);
        InitializeFrontend();
        auto front = GetFrontend();
        if (front) {
            front->UpdateState(Frontend::State::ON_CREATE);
            front->SetJsMessageDispatcher(AceType::Claim(this));
            front->SetAssetManager(assetManager_);
        }
    } else if (type_ != FrontendType::JS_CARD) {
        aceView_->SetCreateTime(createTime_);
    }
    resRegister_ = aceView_->GetPlatformResRegister();
    auto uiTranslateManager = std::make_shared<UiTranslateManagerImpl>();
#ifndef NG_BUILD
    if (useNewPipeline_) {
        pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
            window, taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<NG::TextFieldManagerNG>());
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
        UiSessionManager::GetInstance()->SaveTranslateManager(uiTranslateManager, instanceId_);
        if (pipeline) {
            LOGI("set translateManager to pipeline, instanceId:%{public}d", pipeline->GetInstanceId());
            pipeline->SaveTranslateManager(uiTranslateManager);
        } else {
            LOGE("pipeline invalid,only new ArkUI pipeline support UIsession");
        }
    } else {
        LOGI("Create old pipeline.");
        pipelineContext_ = AceType::MakeRefPtr<PipelineContext>(
            window, taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
        pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<TextFieldManager>());
    }
#else
    pipelineContext_ = AceType::MakeRefPtr<NG::PipelineContext>(
        window, taskExecutor_, assetManager_, resRegister_, frontend_, instanceId);
    pipelineContext_->SetTextFieldManager(AceType::MakeRefPtr<NG::TextFieldManagerNG>());
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    UiSessionManager::GetInstance()->SaveTranslateManager(uiTranslateManager, instanceId_);
    if (pipeline) {
        LOGI("set translateManager to pipeline, instanceId:%{public}d", pipeline->GetInstanceId());
        pipeline->SaveTranslateManager(uiTranslateManager);
    } else {
        LOGE("pipeline invalid,only new ArkUI pipeline support UIsession");
    }
#endif
    RegisterOrientationChangeListener();
    RegisterUIExtDataConsumer();
    RegisterUIExtDataSendToHost();
    RegisterAvoidInfoCallback();

#ifdef FORM_SUPPORTED
    if (isFormRender_) {
        pipelineContext_->SetIsFormRender(isFormRender_);
        pipelineContext_->SetIsDynamicRender(isDynamicRender_);
        auto cardFrontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
        if (cardFrontend) {
            cardFrontend->SetTaskExecutor(taskExecutor_);
            cardFrontend->SetLoadCardCallBack(WeakPtr<PipelineBase>(pipelineContext_));
        }
    }
#endif

    if (isDynamicRender_) {
        pipelineContext_->SetIsDynamicRender(isDynamicRender_);
    }

    auto windowDensityCallback = [weak = WeakClaim(this)]() {
        auto container = weak.Upgrade();
        CHECK_NULL_RETURN(container, 0.0);
        return container->GetWindowDensity();
    };
    pipelineContext_->RegisterWindowDensityCallback(std::move(windowDensityCallback));

    pipelineContext_->SetRootSize(density, width, height);
    if (isFormRender_) {
        pipelineContext_->OnSurfaceDensityChanged(density);
    }
    pipelineContext_->SetIsRightToLeft(AceApplicationInfo::GetInstance().IsRightToLeft());
    pipelineContext_->SetWindowId(windowId);
    pipelineContext_->SetWindowModal(windowModal_);
    if (uiWindow_) {
        bool isAppWindow = uiWindow_->IsAppWindow();
        bool isSystemWindow = uiWindow_->IsSystemWindow();
        bool isSceneBoardWindow = uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD;
        pipelineContext_->SetIsAppWindow(isAppWindow);
        auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
        if (pipeline) {
            auto safeAreaManager = pipeline->GetSafeAreaManager();
            if (safeAreaManager) {
                safeAreaManager->SetWindowTypeConfig(isAppWindow, isSystemWindow, isSceneBoardWindow);
            }
        }
    }
    if (installationFree_) {
        pipelineContext_->SetInstallationFree(installationFree_);
        pipelineContext_->SetSharePanelCallback(std::move(sharePanelCallback_));
        std::shared_ptr<AppExecFwk::AbilityInfo> info = abilityInfo_.lock();
        if (info != nullptr) {
            pipelineContext_->SetAppLabelId(info->labelId);
        }
    }
    if (isSubContainer_) {
        pipelineContext_->SetIsSubPipeline(true);
    }

    pipelineContext_->SetDrawDelegate(aceView_->GetDrawDelegate());
    InitWindowCallback();
    InitializeCallback();

    auto&& finishEventHandler = [weak = WeakClaim(this), instanceId] {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container)] {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnFinish();
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleFinishEvent");
    };
    pipelineContext_->SetFinishEventHandler(finishEventHandler);

    auto&& startAbilityHandler = [weak = WeakClaim(this), instanceId](const std::string& address) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), address]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbility(address);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleStartAbility");
    };
    pipelineContext_->SetStartAbilityHandler(startAbilityHandler);

    auto&& startAbilityOnQueryHandler = [weak = WeakClaim(this), instanceId](const std::string& queryWord) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), queryWord]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbilityOnQuery(queryWord);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleStartAbilityOnQuery");
    };
    pipelineContext_->SetStartAbilityOnQueryHandler(startAbilityOnQueryHandler);

    auto fontManager = pipelineContext_->GetFontManager();
    auto&& startAbilityOnInstallAppInStoreHandler = [weak = WeakClaim(this), instanceId](const std::string& appName) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), appName]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbilityOnInstallAppInStore(appName);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleStartAbilityOnInstallAppInStore");
    };
    if (fontManager) {
        fontManager->SetStartAbilityOnInstallAppInStoreHandler(startAbilityOnInstallAppInStoreHandler);
    }

    auto&& startAbilityOnJumpBrowserHandler = [weak = WeakClaim(this), instanceId](const std::string& appName) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), appName]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbilityOnJumpBrowser(appName);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleStartAbilityOnJumpBrowser");
    };
    if (fontManager) {
        fontManager->SetStartAbilityOnJumpBrowserHandler(startAbilityOnJumpBrowserHandler);
    }

    auto&& openLinkOnMapSearchHandler = [weak = WeakClaim(this), instanceId](const std::string& address) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), address]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnOpenLinkOnMapSearch(address);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleOpenLinkOnMapSearch");
    };
    if (fontManager) {
        fontManager->SetOpenLinkOnMapSearchHandler(openLinkOnMapSearchHandler);
    }

    auto&& startAbilityOnCalendar = [weak = WeakClaim(this), instanceId](
                                        const std::map<std::string, std::string>& params) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak = WeakPtr<AceContainer>(container), params]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                container->OnStartAbilityOnCalendar(params);
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIHandleStartAbilityOnCalendar");
    };
    if (fontManager) {
        fontManager->SetStartAbilityOnCalendar(startAbilityOnCalendar);
    }
    auto&& setStatusBarEventHandler = [weak = WeakClaim(this), instanceId](const Color& color) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        ContainerScope scope(instanceId);
        auto context = container->GetPipelineContext();
        CHECK_NULL_VOID(context);
        context->GetTaskExecutor()->PostTask(
            [weak, color = color.GetValue()]() {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                if (container->platformEventCallback_) {
                    container->platformEventCallback_->OnStatusBarBgColorChanged(color);
                }
            },
            TaskExecutor::TaskType::PLATFORM, "ArkUIStatusBarColorChanged");
    };
    pipelineContext_->SetStatusBarEventHandler(setStatusBarEventHandler);

    auto uiExtensionEventCallback = [weak = WeakClaim(this)](uint32_t eventId) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        container->FireUIExtensionEventCallback(eventId);
    };
    pipelineContext_->SetUIExtensionEventCallback(uiExtensionEventCallback);

    auto accessibilityEventCallback = [weak = WeakClaim(this)](uint32_t eventId, int64_t parameter) {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        container->FireAccessibilityEventCallback(eventId, parameter);
    };
    pipelineContext_->SetAccessibilityEventCallback(accessibilityEventCallback);

    if (GetSettings().usePlatformAsUIThread) {
        FrameReport::GetInstance().Init();
    } else {
        taskExecutor_->PostTask([] { FrameReport::GetInstance().Init(); },
            TaskExecutor::TaskType::UI, "ArkUIFrameReportInit");
    }

    // Load custom style at UI thread before frontend attach, for loading style before building tree.
    auto initThemeManagerTask = [pipelineContext = pipelineContext_, assetManager = assetManager_,
                                    colorScheme = colorScheme_, resourceInfo = resourceInfo_,
                                    context = runtimeContext_.lock(), abilityInfo = abilityInfo_.lock()]() {
        ACE_SCOPED_TRACE("OHOS::LoadThemes()");

        if (SystemProperties::GetResourceDecoupling()) {
            InitResourceAndThemeManager(pipelineContext, assetManager, colorScheme, resourceInfo, context, abilityInfo);
        } else {
            ThemeConstants::InitDeviceType();
            auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
            pipelineContext->SetThemeManager(themeManager);
            themeManager->InitResource(resourceInfo);
            themeManager->SetColorScheme(colorScheme);
            themeManager->LoadCustomTheme(assetManager);
            themeManager->LoadResourceThemes();
        }
        auto themeManager = pipelineContext->GetThemeManager();
        if (themeManager) {
            pipelineContext->SetAppBgColor(themeManager->GetBackgroundColor());
        }
    };

    auto setupRootElementTask = [context = pipelineContext_, callback, isSubContainer = isSubContainer_,
        isDialogContainer = IsDialogContainer()]() {
        if (callback != nullptr) {
            callback(AceType::DynamicCast<PipelineContext>(context));
        }
        if (!isSubContainer && !isDialogContainer) {
            context->SetupRootElement();
        }
    };

    if (GetSettings().usePlatformAsUIThread) {
        initThemeManagerTask();
        setupRootElementTask();
        auto newPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
        if (newPipeline) {
            InitNavigationManagerCallback(newPipeline);
        }
    } else {
        taskExecutor_->PostTask(initThemeManagerTask, TaskExecutor::TaskType::UI, "ArkUIInitThemeManager");
        taskExecutor_->PostTask(setupRootElementTask, TaskExecutor::TaskType::UI, "ArkUISetupRootElement");
    }

    aceView_->Launch();

#ifdef NG_BUILD
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend_);
#else
    auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend_);
#endif
    if (declarativeFrontend) {
        auto jsEngine = AceType::DynamicCast<Framework::JsiDeclarativeEngine>(declarativeFrontend->GetJsEngine());
        if (jsEngine && !isFormRender_) {
            // register state profiler callback
            jsEngine->JsStateProfilerResgiter();
            jsEngine->JsSetAceDebugMode();
        }
    }

    if (!isSubContainer_) {
        // Only MainWindow instance in FA model will be registered to watch dog.
        if (!GetSettings().usingSharedRuntime && !AceApplicationInfo::GetInstance().IsNeedDebugBreakPoint()) {
            AceEngine::Get().RegisterToWatchDog(instanceId, taskExecutor_, GetSettings().useUIAsJSThread);
        }
        frontend_->AttachPipelineContext(pipelineContext_);
    } else if (frontend_->GetType() == FrontendType::DECLARATIVE_JS) {
        if (declarativeFrontend) {
            declarativeFrontend->AttachSubPipelineContext(pipelineContext_);
        }
        return;
    }

    auto dataAbilityHelperImpl = [ability = GetAbilityInner(), runtimeContext = runtimeContext_,
                                     useStageModel = useStageModel_]() {
        return AceType::MakeRefPtr<DataAbilityHelperStandard>(ability.lock(), runtimeContext.lock(), useStageModel);
    };
    auto dataProviderManager = MakeRefPtr<DataProviderManagerStandard>(dataAbilityHelperImpl);
    pipelineContext_->SetDataProviderManager(dataProviderManager);

#if defined(ENABLE_ROSEN_BACKEND) and !defined(UPLOAD_GPU_DISABLED)
    pipelineContext_->SetPostRTTaskCallBack([pipelineWeak =
        AceType::WeakClaim(AceType::RawPtr(pipelineContext_))](std::function<void()>&& task) {
        auto syncTask = std::make_shared<AceRosenSyncTask>(std::move(task));
        if (!SystemProperties::GetMultiInstanceEnabled()) {
            Rosen::RSTransactionProxy::GetInstance()->ExecuteSynchronousTask(syncTask);
        } else {
            auto pipeline = pipelineWeak.Upgrade();
            CHECK_NULL_VOID(pipeline);
            auto rsUiDirector = pipeline->GetWindow()->GetRSUIDirector();
            auto rsUiContext = rsUiDirector->GetRSUIContext();
            if (rsUiDirector && rsUiContext) {
                rsUiContext->GetRSTransaction()->ExecuteSynchronousTask(syncTask);
            } else {
                Rosen::RSTransactionProxy::GetInstance()->ExecuteSynchronousTask(syncTask);
            }
        }
    });
#endif
    if (IsUIExtensionWindow()) {
        auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
        CHECK_NULL_VOID(ngPipeline);
        auto uiExtManager = ngPipeline->GetUIExtensionManager();
        CHECK_NULL_VOID(uiExtManager);
        uiExtManager->SendPageModeRequestToHost(ngPipeline);
        auto accessibilityManager = ngPipeline->GetAccessibilityManager();
        CHECK_NULL_VOID(accessibilityManager);
        accessibilityManager->RegisterUIExtGetPageModeCallback(uiExtManager);
    }
}

void AceContainer::SetUIWindowInner(sptr<OHOS::Rosen::Window> uiWindow)
{
    uiWindow_ = uiWindow;
}

sptr<OHOS::Rosen::Window> AceContainer::GetUIWindowInner() const
{
    return uiWindow_;
}

std::weak_ptr<OHOS::AppExecFwk::Ability> AceContainer::GetAbilityInner() const
{
    return aceAbility_;
}

std::weak_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetRuntimeContextInner() const
{
    return runtimeContext_;
}

bool AceContainer::IsLauncherContainer()
{
    auto runtime = runtimeContext_.lock();
    if (!runtime) {
        return false;
    }
    auto info = runtime->GetApplicationInfo();
    return info ? info->isLauncherApp : false;
}

bool AceContainer::IsTransparentBg() const
{
    CHECK_NULL_RETURN(pipelineContext_, true);
    Color bgColor = pipelineContext_->GetAppBgColor();
    std::string bgOpacity = bgColor.ColorToString().substr(0, 3);
    std::string transparentOpacity = "#00";
    return bgColor == Color::TRANSPARENT || bgOpacity == transparentOpacity;
}

void AceContainer::SetWindowStyle(int32_t instanceId, WindowModal windowModal, ColorScheme colorScheme)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId);
    container->SetWindowModal(windowModal);
    container->SetColorScheme(colorScheme);
}

void AceContainer::SetDialogCallback(int32_t instanceId, FrontendDialogCallback callback)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    if (front && front->GetType() == FrontendType::JS) {
        front->SetDialogCallback(callback);
    }
}

std::pair<RouterRecoverRecord, UIContentErrorCode> AceContainer::RestoreRouterStack(
    int32_t instanceId, const std::string& contentInfo, ContentInfoType type)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NULL_POINTER));
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, std::make_pair(RouterRecoverRecord(), UIContentErrorCode::NULL_POINTER));
    return front->RestoreRouterStack(contentInfo, type);
}

std::string AceContainer::GetContentInfo(int32_t instanceId, ContentInfoType type)
{
    auto container = AceEngine::Get().GetContainer(instanceId);
    CHECK_NULL_RETURN(container, "");
    ContainerScope scope(instanceId);
    auto front = container->GetFrontend();
    CHECK_NULL_RETURN(front, "");
    return front->GetContentInfo(type);
}

void AceContainer::SetWindowPos(int32_t left, int32_t top)
{
    CHECK_NULL_VOID(frontend_);
    auto accessibilityManager = frontend_->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->SetWindowPos(left, top, windowId_);
}

void AceContainer::InitializeSubContainer(int32_t parentContainerId)
{
    auto parentContainer = AceEngine::Get().GetContainer(parentContainerId);
    CHECK_NULL_VOID(parentContainer);
    auto taskExec = parentContainer->GetTaskExecutor();
    taskExecutor_ = AceType::DynamicCast<TaskExecutorImpl>(std::move(taskExec));
    auto parentSettings = parentContainer->GetSettings();
    GetSettings().useUIAsJSThread = parentSettings.useUIAsJSThread;
    GetSettings().usePlatformAsUIThread = parentSettings.usePlatformAsUIThread;
    GetSettings().usingSharedRuntime = parentSettings.usingSharedRuntime;
}

void AceContainer::InitWindowCallback()
{
    if (!pipelineContext_ || !uiWindow_) {
        return;
    }
    auto& windowManager = pipelineContext_->GetWindowManager();
    std::shared_ptr<AppExecFwk::AbilityInfo> info = abilityInfo_.lock();
    if (info != nullptr) {
        windowManager->SetAppLabelId(info->labelId);
        windowManager->SetAppIconId(info->iconId);
    }
    windowManager->SetWindowMinimizeCallBack([window = uiWindow_]() { window->Minimize(); });
    windowManager->SetWindowMaximizeCallBack([window = uiWindow_]() { window->Maximize(); });
    windowManager->SetWindowMaximizeFloatingCallBack([window = uiWindow_]() { window->MaximizeFloating(); });
    windowManager->SetWindowRecoverCallBack([window = uiWindow_]() { window->Recover(); });
    windowManager->SetWindowCloseCallBack([window = uiWindow_]() { window->Close(); });
    windowManager->SetWindowStartMoveCallBack([window = uiWindow_]() { window->StartMove(); });
    windowManager->SetPerformBackCallback([window = uiWindow_]() { window->PerformBack(); });
    windowManager->SetWindowIsStartMovingCallBack(
        [window = uiWindow_]() -> bool { return static_cast<bool>(window->IsStartMoving()); });
    windowManager->SetWindowSplitPrimaryCallBack(
        [window = uiWindow_]() { window->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY); });
    windowManager->SetWindowSplitSecondaryCallBack(
        [window = uiWindow_]() { window->SetWindowMode(Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY); });
    windowManager->SetWindowGetModeCallBack(
        [window = uiWindow_]() -> WindowMode { return static_cast<WindowMode>(window->GetWindowMode()); });
    windowManager->SetWindowGetIsMidSceneCallBack([window = uiWindow_](bool& isMidScene) -> int32_t {
        return static_cast<int32_t>(window->GetIsMidScene(isMidScene));
    });
    windowManager->SetWindowGetTypeCallBack(
        [window = uiWindow_]() -> WindowType { return static_cast<WindowType>(window->GetType()); });
    windowManager->SetWindowSetMaximizeModeCallBack([window = uiWindow_](MaximizeMode mode) {
        window->SetGlobalMaximizeMode(static_cast<Rosen::MaximizeMode>(mode));
    });
    windowManager->SetWindowGetMaximizeModeCallBack(
        [window = uiWindow_]() -> MaximizeMode { return static_cast<MaximizeMode>(window->GetGlobalMaximizeMode()); });
    windowManager->SetGetSystemBarStyleCallBack([window = uiWindow_]() -> RefPtr<SystemBarStyle> {
        return SystemBarStyleOhos::GetCurrentSystemBarStyle(window);
    });
    windowManager->SetSetSystemBarStyleCallBack([window = uiWindow_](const RefPtr<SystemBarStyle>& style) {
        SystemBarStyleOhos::SetSystemBarStyle(window, style);
    });
    windowManager->SetWindowSetSystemBarEnabledCallback([window = uiWindow_](SystemBarType type,
        std::optional<bool> enable, std::optional<bool> needAnimation) -> bool {
            CHECK_NULL_RETURN(window, false);
            return AceContainer::SetSystemBarEnabled(window, type, enable, needAnimation);
        });
    windowManager->SetGetCurrentViewportConfigCallback(
        [weakContainer = WeakClaim(this)]() -> RefPtr<PageViewportConfig> {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_RETURN(container, nullptr);
            return container->GetCurrentViewportConfig();
        });
    windowManager->SetGetTargetViewportConfigCallback([weakContainer = WeakClaim(this)](
        std::optional<Orientation> orientation, std::optional<bool> enableStatusBar,
        std::optional<bool> statusBarAnimation, std::optional<bool> enableNavIndicator) -> RefPtr<PageViewportConfig> {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_RETURN(container, nullptr);
            return container->GetTargetViewportConfig(
                orientation, enableStatusBar, statusBarAnimation, enableNavIndicator);
        });
    windowManager->SetSetRequestedOrientationCallback(
        [window = uiWindow_](std::optional<Orientation> orientation, bool needAnimation) {
            auto ori = Rosen::Orientation::INVALID;
            if (orientation.has_value()) {
                ori = static_cast<Rosen::Orientation>(static_cast<int32_t>(orientation.value()));
            }
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "SetRequestedOrientation ori:%{public}d, needAnimation:%{public}d",
                static_cast<int32_t>(ori), needAnimation);
            window->SetRequestedOrientation(ori, needAnimation);
        });
    windowManager->SetGetRequestedOrientationCallback(
        [window = uiWindow_]() -> Orientation {
            auto ori = window->GetRequestedOrientation();
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "GetRequestedOrientation ori:%{public}d", static_cast<int32_t>(ori));
            return static_cast<Orientation>(static_cast<int32_t>(ori));
        });
    windowManager->SetIsFullScreenWindowCallback(
        [window = uiWindow_]() -> bool {
            return window->GetWindowMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN;
        });
    windowManager->SetIsPcOrPadFreeMultiWindowModeCallback(
        [window = uiWindow_]() -> bool { return window->IsPcOrPadFreeMultiWindowMode(); });
    windowManager->SetGetFreeMultiWindowModeEnabledStateCallback(
        [window = uiWindow_]() -> bool { return window->GetFreeMultiWindowModeEnabledState(); });
    windowManager->SetWindowCallNativeCallback([window = uiWindow_](const std::string& name, const std::string& value) {
        window->OnContainerModalEvent(name, value);
    });

    windowManager->SetWindowUseImplicitAnimationCallBack([window = uiWindow_](bool useImplicit) {
        TAG_LOGI(AceLogTag::ACE_SHEET, "useImplicit : %{public}d", useImplicit);
        window->UseImplicitAnimation(useImplicit);
    });

    windowManager->SetHeightBreakpointCallback(
        [window = pipelineContext_->GetWindow()]() -> HeightBreakpoint {
        CHECK_NULL_RETURN(window, HeightBreakpoint::HEIGHT_SM);
        HeightLayoutBreakPoint layoutHeightBreakpoints =
            SystemProperties::GetHeightLayoutBreakpoints();
        return window->GetHeightBreakpoint(layoutHeightBreakpoints);
    });
    windowManager->SetWidthBreakpointCallback(
        [window = pipelineContext_->GetWindow()]() -> WidthBreakpoint {
        CHECK_NULL_RETURN(window, WidthBreakpoint::WIDTH_SM);
        WidthLayoutBreakPoint layoutWidthBreakpoints =
            SystemProperties::GetWidthLayoutBreakpoints();
        return window->GetWidthBreakpoint(layoutWidthBreakpoints);
    });

    pipelineContext_->SetGetWindowRectImpl([window = uiWindow_]() -> Rect {
        Rect rect;
        CHECK_NULL_RETURN(window, rect);
        auto windowRect = window->GetRect();
        rect.SetRect(windowRect.posX_, windowRect.posY_, windowRect.width_, windowRect.height_);
        return rect;
    });

    pipelineContext_->InitGetGlobalWindowRectCallback([window = uiWindow_]() -> Rect {
        Rect rect;
        CHECK_NULL_RETURN(window, rect);
        auto globalDisplayWindowRect = window->GetGlobalDisplayRect();
        rect.SetRect(globalDisplayWindowRect.posX_, globalDisplayWindowRect.posY_, globalDisplayWindowRect.width_,
            globalDisplayWindowRect.height_);
        return rect;
    });
}

NG::SafeAreaInsets AceContainer::GetViewSafeAreaByType(
    OHOS::Rosen::AvoidAreaType type, std::optional<NG::RectF> windowRect)
{
    CHECK_NULL_RETURN(uiWindow_, {});
    Rosen::AvoidArea avoidArea;
    Rosen::WMError ret;
    if (windowRect.has_value()) {
        auto rect = windowRect.value();
        Rosen::Rect rosenRect = { static_cast<int32_t>(rect.GetX()), static_cast<int32_t>(rect.GetY()),
            static_cast<uint32_t>(rect.Width()), static_cast<uint32_t>(rect.Height()) };
        ret = uiWindow_->GetAvoidAreaByType(type, avoidArea, rosenRect);
    } else {
        ret = uiWindow_->GetAvoidAreaByType(type, avoidArea);
    }
    if (ret == Rosen::WMError::WM_OK) {
        auto safeAreaInsets = ConvertAvoidArea(avoidArea);
        TAG_LOGD(ACE_SAFE_AREA, "SafeArea get success, type :%{public}d, insets :%{public}s",
            static_cast<int32_t>(type), safeAreaInsets.ToString().c_str());
        return safeAreaInsets;
    }
    return {};
}

NG::SafeAreaInsets AceContainer::GetKeyboardSafeArea()
{
    CHECK_NULL_RETURN(uiWindow_, {});
    Rosen::AvoidArea avoidArea;
    Rosen::WMError ret = uiWindow_->GetAvoidAreaByType(Rosen::AvoidAreaType::TYPE_KEYBOARD, avoidArea);
    if (ret == Rosen::WMError::WM_OK) {
        return ConvertAvoidArea(avoidArea);
    }
    return {};
}

Rosen::AvoidArea AceContainer::GetAvoidAreaByType(Rosen::AvoidAreaType type, int32_t apiVersion)
{
    CHECK_NULL_RETURN(uiWindow_, {});
    Rosen::AvoidArea avoidArea;
    Rosen::Rect rect;
    Rosen::WMError ret = uiWindow_->GetAvoidAreaByType(type, avoidArea, rect, apiVersion);
    if (ret == Rosen::WMError::WM_OK) {
        return avoidArea;
    }
    return {};
}

uint32_t AceContainer::GetStatusBarHeight()
{
    CHECK_NULL_RETURN(uiWindow_, 0);
    return static_cast<uint32_t>(uiWindow_->GetStatusBarHeight());
}

std::shared_ptr<OHOS::AbilityRuntime::Context> AceContainer::GetAbilityContextByModule(
    const std::string& bundle, const std::string& module)
{
    auto context = runtimeContext_.lock();
    CHECK_NULL_RETURN(context, nullptr);
    if (!isFormRender_ && !bundle.empty() && !module.empty()) {
        std::string encode = EncodeBundleAndModule(bundle, module);
        if (taskExecutor_->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            RecordResAdapter(encode);
        } else {
            taskExecutor_->PostTask(
                [encode, instanceId = instanceId_]() -> void {
                    auto container = AceContainer::GetContainer(instanceId);
                    CHECK_NULL_VOID(container);
                    container->RecordResAdapter(encode);
                },
                TaskExecutor::TaskType::UI, "ArkUIRecordResAdapter");
        }
    }
    return isFormRender_ ? nullptr : context->CreateModuleContext(bundle, module);
}

void AceContainer::CheckAndSetFontFamily()
{
    CHECK_NULL_VOID(pipelineContext_);
    auto fontManager = pipelineContext_->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (fontManager->IsUseAppCustomFont()) {
        return;
    }
    std::string familyName = "";
    std::string path = "/data/themes/a/app";
    if (!IsFontFileExistInPath(path)) {
        path = "/data/themes/b/app";
        if (!IsFontFileExistInPath(path)) {
            return;
        }
    }
    path = path.append("/fonts/");
    auto fontFamilyNames = GetFontFamilyName(path);
    if (fontFamilyNames.empty()) {
        TAG_LOGI(AceLogTag::ACE_FONT, "FontFamilyNames is empty");
        return;
    }
    familyName = fontFamilyNames[0];
    std::vector<std::string> fullPath;
    for (const auto& fontFamilyName : fontFamilyNames) {
        fullPath.push_back(path + fontFamilyName);
    }
    if (isFormRender_) {
        // Resolve garbled characters caused by FRS multi-thread async
        std::lock_guard<std::mutex> lock(g_mutexFormRenderFontFamily);
        fontManager->SetFontFamily(familyName.c_str(), fullPath);
    } else {
        fontManager->SetFontFamily(familyName.c_str(), fullPath);
    }
}

void AceContainer::SetFontScaleAndWeightScale(int32_t instanceId)
{
    float fontScale = SystemProperties::GetFontScale();
    float fontWeightScale = SystemProperties::GetFontWeightScale();
    Container::SetFontScale(instanceId, fontScale);
    Container::SetFontWeightScale(instanceId, fontWeightScale);
}

void AceContainer::SetFontScaleAndWeightScale(
    const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange)
{
    if (!parsedConfig.fontScale.empty()) {
        TAG_LOGD(AceLogTag::ACE_FONT, "parsedConfig fontScale: %{public}s", parsedConfig.fontScale.c_str());
        CHECK_NULL_VOID(pipelineContext_);
        float fontSizeScale = StringUtils::StringToFloat(parsedConfig.fontScale);
        if (fontSizeScale != pipelineContext_->GetFontScale()) {
            SetFontScale(instanceId_, fontSizeScale);
            configurationChange.fontScaleUpdate = true;
        }
    }
    if (!parsedConfig.fontWeightScale.empty()) {
        TAG_LOGD(AceLogTag::ACE_FONT, "parsedConfig fontWeightScale: %{public}s", parsedConfig.fontWeightScale.c_str());
        CHECK_NULL_VOID(pipelineContext_);
        float fontWeightScale = StringUtils::StringToFloat(parsedConfig.fontWeightScale);
        if (fontWeightScale != pipelineContext_->GetFontWeightScale()) {
            SetFontWeightScale(instanceId_, fontWeightScale);
            configurationChange.fontWeightScaleUpdate = true;
        }
    }
}

void AceContainer::ReleaseResourceAdapter()
{
    for (auto& encode : resAdapterRecord_) {
        std::string bundleName;
        std::string moduleName;
        DecodeBundleAndModule(encode, bundleName, moduleName);
        ResourceManager::GetInstance().RemoveResourceAdapter(bundleName, moduleName, instanceId_);
    }
    resAdapterRecord_.clear();

    if (isFormRender_) {
        auto runtimeContext = runtimeContext_.lock();
        if (runtimeContext) {
            auto bundleName = runtimeContext->GetBundleName();
            auto moduleName = runtimeContext->GetHapModuleInfo()->name;
            ResourceManager::GetInstance().RemoveResourceAdapter(bundleName, moduleName, instanceId_);
        }
    }
}

DeviceOrientation AceContainer::ProcessDirectionUpdate(
    const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange)
{
    if (!parsedConfig.direction.empty()) {
        auto resDirection = DeviceOrientation::ORIENTATION_UNDEFINED;
        if (parsedConfig.direction == "horizontal") {
            resDirection = DeviceOrientation::LANDSCAPE;
        } else if (parsedConfig.direction == "vertical") {
            resDirection = DeviceOrientation::PORTRAIT;
        }
        configurationChange.directionUpdate = true;
        return resDirection;
    }
    return DeviceOrientation::ORIENTATION_UNDEFINED;
}

void AceContainer::ProcessThemeUpdate(const ParsedConfig& parsedConfig, ConfigurationChange& configurationChange)
{
    if (!parsedConfig.themeTag.empty()) {
        std::unique_ptr<JsonValue> json = JsonUtil::ParseJsonString(parsedConfig.themeTag);
        int fontUpdate = json->GetInt("fonts");
        configurationChange.fontUpdate = configurationChange.fontUpdate || fontUpdate;
        int iconUpdate = json->GetInt("icons");
        configurationChange.iconUpdate = iconUpdate;
        int skinUpdate = json->GetInt("skin");
        if (!skinUpdate && lastThemeHasSkin_) {
            configurationChange.skinUpdate = true;
        } else {
            configurationChange.skinUpdate = skinUpdate;
        }
        lastThemeHasSkin_ = skinUpdate;
        if ((isDynamicRender_ || isFormRender_) && fontUpdate) {
            CheckAndSetFontFamily();
        }
    }
}

void AceContainer::BuildResConfig(
    ResourceConfiguration& resConfig, ConfigurationChange& configurationChange, const ParsedConfig& parsedConfig)
{
    if (!parsedConfig.colorMode.empty()) {
        ProcessColorModeUpdate(resConfig, configurationChange, parsedConfig);
    }
    if (!parsedConfig.deviceAccess.empty()) {
        // Event of accessing mouse or keyboard
        SystemProperties::SetDeviceAccess(parsedConfig.deviceAccess == "true");
        resConfig.SetDeviceAccess(parsedConfig.deviceAccess == "true");
    }
    if (!parsedConfig.languageTag.empty()) {
        ParseLanguage(configurationChange, parsedConfig.languageTag);
        resConfig.SetLanguage(parsedConfig.languageTag);
    }
    if (!parsedConfig.fontFamily.empty()) {
        auto fontManager = pipelineContext_->GetFontManager();
        CHECK_NULL_VOID(fontManager);
        configurationChange.fontUpdate = true;
        fontManager->SetAppCustomFont(parsedConfig.fontFamily);
    }
    if (!parsedConfig.direction.empty()) {
        resConfig.SetOrientation(ProcessDirectionUpdate(parsedConfig, configurationChange));
    }
    if (!parsedConfig.densitydpi.empty()) {
        configurationChange.dpiUpdate = true;
    }
    ProcessThemeUpdate(parsedConfig, configurationChange);
    if (!parsedConfig.colorModeIsSetByApp.empty()) {
        resConfig.SetColorModeIsSetByApp(true);
    }
    if (!parsedConfig.mcc.empty()) {
        resConfig.SetMcc(StringUtils::StringToUint(parsedConfig.mcc));
    }
    if (!parsedConfig.mnc.empty()) {
        resConfig.SetMnc(StringUtils::StringToUint(parsedConfig.mnc));
    }
}

void AceContainer::ProcessColorModeUpdate(
    ResourceConfiguration& resConfig, ConfigurationChange& configurationChange, const ParsedConfig& parsedConfig)
{
    configurationChange.colorModeUpdate = true;
    if (SystemProperties::ConfigChangePerform()) {
        // reread all cache color of ark theme when configuration updates
        NG::TokenThemeStorage::GetInstance()->CacheResetColor();
    } else {
        // clear cache of ark theme instances when configuration updates
        NG::TokenThemeStorage::GetInstance()->CacheClear();
    }
    if (parsedConfig.colorMode == "dark") {
        SetColorMode(ColorMode::DARK);
        SetColorScheme(ColorScheme::SCHEME_DARK);
        resConfig.SetColorMode(ColorMode::DARK);
    } else {
        SetColorMode(ColorMode::LIGHT);
        SetColorScheme(ColorScheme::SCHEME_LIGHT);
        resConfig.SetColorMode(ColorMode::LIGHT);
    }
}

void AceContainer::UpdateColorMode(uint32_t colorMode)
{
    ACE_SCOPED_TRACE("AceContainer::UpdateColorMode %u", colorMode);
    CHECK_NULL_VOID(pipelineContext_);
    if (SystemProperties::ConfigChangePerform()) {
        pipelineContext_->ClearImageCache();
        NG::ImageDecoder::ClearPixelMapCache();
    }
    auto themeManager = pipelineContext_->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    if (!IsUseCustomBg() && !IsTransparentBg()) {
        Color color = themeManager->GetBackgroundColor();
        pipelineContext_->SetAppBgColor(color);
        ACE_SCOPED_TRACE("AceContainer::UpdateColorMode pipeline bgcolor %s", color.ColorToString().c_str());
    }
    pipelineContext_->SetIsSystemColorChange(true);
    pipelineContext_->NotifyColorModeChange(colorMode);
}

void AceContainer::CheckForceVsync(const ParsedConfig& parsedConfig)
{
    // the application is in the background and the dark and light colors are switched.
    if (pipelineContext_ && !pipelineContext_->GetOnShow() && !parsedConfig.colorMode.empty()) {
        pipelineContext_->SetBackgroundColorModeUpdated(true);
        auto window = pipelineContext_->GetWindow();
        if (window) {
            window->SetForceVsyncRequests(true);
        }
    }
}

void  AceContainer::OnFrontUpdated(
    const ConfigurationChange& configurationChange, const std::string& configuration)
{
    auto front = GetFrontend();
    CHECK_NULL_VOID(front);
    if (!configurationChange.directionUpdate && !configurationChange.dpiUpdate) {
        front->OnConfigurationUpdated(configuration);
    }
}

void AceContainer::UpdateSubContainerDensity(ResourceConfiguration& resConfig)
{
    if (instanceId_ >= MIN_SUBCONTAINER_ID) {
        auto parentContainer = Platform::AceContainer::GetContainer(GetParentId());
        CHECK_NULL_VOID(parentContainer);
        auto parentPipeline = parentContainer->GetPipelineContext();
        CHECK_NULL_VOID(parentPipeline);
        resConfig.SetDensity(parentPipeline->GetDensity());
    }
}

void AceContainer::UpdateConfiguration(
    const ParsedConfig& parsedConfig, const std::string& configuration, bool abilityLevel)
{
    if (!parsedConfig.IsValid()) {
        LOGW("AceContainer::OnConfigurationUpdated param is empty");
        return;
    }
    CheckForceVsync(parsedConfig);
    ConfigurationChange configurationChange;
    CHECK_NULL_VOID(pipelineContext_);
    auto themeManager = pipelineContext_->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto resConfig = GetResourceConfiguration();
    BuildResConfig(resConfig, configurationChange, parsedConfig);
    if (!parsedConfig.preferredLanguage.empty()) {
        ParseLanguage(configurationChange, parsedConfig.preferredLanguage);
        resConfig.SetPreferredLanguage(parsedConfig.preferredLanguage);
    }
    // The density of sub windows needs to be consistent with the main window.
    UpdateSubContainerDensity(resConfig);

    SetFontScaleAndWeightScale(parsedConfig, configurationChange);
    SetResourceConfiguration(resConfig);
    if (!abilityLevel) {
        themeManager->UpdateConfig(resConfig);
        if (SystemProperties::GetResourceDecoupling()) {
            ResourceManager::GetInstance().UpdateResourceConfig(resConfig, !parsedConfig.themeTag.empty());
        }
    }
    themeManager->LoadResourceThemes();
    if (SystemProperties::ConfigChangePerform() && configurationChange.OnlyColorModeChange()) {
        OnFrontUpdated(configurationChange, configuration);
        UpdateColorMode(static_cast<uint32_t>(resConfig.GetColorMode()));
        return;
    }
    OnFrontUpdated(configurationChange, configuration);
#ifdef PLUGIN_COMPONENT_SUPPORTED
    if (configurationChange.IsNeedUpdate()) {
        OHOS::Ace::PluginManager::GetInstance().UpdateConfigurationInPlugin(resConfig);
    }
#endif
    pipelineContext_->SaveConfigurationConfig(configurationChange);
    NotifyConfigurationChange(!parsedConfig.deviceAccess.empty(), configurationChange);
    NotifyConfigToSubContainers(parsedConfig, configuration);
    // change color mode and theme to clear image cache
    pipelineContext_->ClearImageCache();
    NG::ImageDecoder::ClearPixelMapCache();
}

void AceContainer::UpdateConfigurationSyncForAll(const ParsedConfig& parsedConfig, const std::string& configuration)
{
    if (!parsedConfig.IsValid()) {
        LOGW("AceContainer::OnConfigurationUpdated param is empty");
        return;
    }

    if (!parsedConfig.fontId.empty()) {
        CheckAndSetFontFamily();
    }
}

void AceContainer::NotifyConfigToSubContainers(const ParsedConfig& parsedConfig, const std::string& configuration)
{
    for (auto& item : configurationChangedCallbacks_) {
        if (item.second) {
            item.second(parsedConfig, configuration);
        }
    }
}

void AceContainer::FlushReloadTask(bool needReloadTransition, const ConfigurationChange& configurationChange)
{
    auto pipeline = GetPipelineContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    if (configurationChange.directionUpdate &&
        (themeManager->GetResourceLimitKeys() & DIRECTION_KEY) == 0) {
        return;
    }
    if (configurationChange.colorModeUpdate && !IsUseCustomBg() &&
        !IsTransparentBg()) {
        pipeline->SetAppBgColor(themeManager->GetBackgroundColor());
    }
    pipeline->NotifyConfigurationChange();
    pipeline->FlushReload(configurationChange);
    if (needReloadTransition) {
        // reload transition animation
        pipeline->FlushReloadTransition();
    }
    pipeline->ChangeDarkModeBrightness();
}

void AceContainer::NotifyConfigurationChange(bool needReloadTransition, const ConfigurationChange& configurationChange)
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    if (useStageModel_) {
        taskExecutor->PostTask(
            [instanceId = instanceId_, weak = WeakClaim(this), needReloadTransition, configurationChange]() {
                ContainerScope scope(instanceId);
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                auto frontend = container->GetFrontend();
                if (frontend) {
                    LOGI("AceContainer UpdateConfiguration frontend MarkNeedUpdate");
                    frontend->FlushReload();
                }
                container->FlushReloadTask(needReloadTransition, configurationChange);
                },
            TaskExecutor::TaskType::UI, "ArkUINotifyConfigurationChange", PriorityType::VIP);
        return;
    }
    taskExecutor->PostTask(
        [instanceId = instanceId_, weak = WeakClaim(this), needReloadTransition, configurationChange]() {
            ContainerScope scope(instanceId);
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto frontend = container->GetFrontend();
            if (frontend) {
                LOGI("AceContainer UpdateConfiguration frontend MarkNeedUpdate");
                frontend->FlushReload();
            }
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [instanceId, weak, needReloadTransition, configurationChange]() {
                    ContainerScope scope(instanceId);
                    auto container = weak.Upgrade();
                    CHECK_NULL_VOID(container);
                    container->FlushReloadTask(needReloadTransition, configurationChange);
                },
                TaskExecutor::TaskType::UI, "ArkUIFlushReloadTransition");
        },
        TaskExecutor::TaskType::JS, "ArkUINotifyConfigurationChange");
}

void AceContainer::HotReload()
{
    auto taskExecutor = GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [instanceId = instanceId_, weak = WeakClaim(this)]() {
            ContainerScope scope(instanceId);
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            LOGI("AceContainer Flush Frontend for HotReload");
            frontend->HotReload();

            auto pipeline = container->GetPipelineContext();
            CHECK_NULL_VOID(pipeline);
            ConfigurationChange configurationChange { .hotReloadUpdate = true };
            pipeline->FlushReload(configurationChange);
        },
        TaskExecutor::TaskType::UI, "ArkUIHotReload");
}

void AceContainer::SetToken(sptr<IRemoteObject>& token)
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    if (token) {
        token_ = token;
    }
}

sptr<IRemoteObject> AceContainer::GetToken()
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    if (token_) {
        return token_;
    }
    LOGE("fail to get Token");
    return nullptr;
}

void AceContainer::SetParentToken(sptr<IRemoteObject>& token)
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    if (token) {
        parentToken_ = token;
    }
}

sptr<IRemoteObject> AceContainer::GetParentToken()
{
    std::lock_guard<std::mutex> lock(cardTokensMutex_);
    return parentToken_;
}

// ArkTsCard start
std::shared_ptr<Rosen::RSSurfaceNode> AceContainer::GetFormSurfaceNode(int32_t instanceId)
{
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_RETURN(context, nullptr);
    auto window = static_cast<FormRenderWindow*>(context->GetWindow());
    CHECK_NULL_RETURN(window, nullptr);
    return window->GetRSSurfaceNode();
}

void AceContainer::UpdateFormData(const std::string& data)
{
#ifdef FORM_SUPPORTED
    auto frontend = AceType::DynamicCast<FormFrontendDeclarative>(frontend_);
    CHECK_NULL_VOID(frontend);
    frontend->UpdateData(data);
#endif
}

void AceContainer::UpdateFormSharedImage(const std::map<std::string, sptr<AppExecFwk::FormAshmem>>& imageDataMap)
{
    std::vector<std::string> picNameArray;
    std::vector<int> fileDescriptorArray;
    std::vector<int> byteLenArray;
    if (!imageDataMap.empty()) {
        for (auto& imageData : imageDataMap) {
            picNameArray.push_back(imageData.first);
            fileDescriptorArray.push_back(imageData.second->GetAshmemFd());
            byteLenArray.push_back(imageData.second->GetAshmemSize());
            TAG_LOGI(ACE_FORM, "picName:%{public}s, fd:%{public}d, size:%{public}d", imageData.first.c_str(),
                imageData.second->GetAshmemFd(), imageData.second->GetAshmemSize());
        }
        GetNamesOfSharedImage(picNameArray);
        UpdateSharedImage(picNameArray, byteLenArray, fileDescriptorArray);
    }
}

void AceContainer::UpdateResource()
{
    // Reload theme and resource
    CHECK_NULL_VOID(pipelineContext_);

    if (SystemProperties::GetResourceDecoupling()) {
        auto context = runtimeContext_.lock();
        auto abilityInfo = abilityInfo_.lock();
        if (pipelineContext_->IsFormRender()) {
            ReleaseResourceAdapter();
        }
        InitResourceAndThemeManager(
            pipelineContext_, assetManager_, colorScheme_, resourceInfo_, context, abilityInfo, true);
    } else {
        ThemeConstants::InitDeviceType();
        auto themeManager = AceType::MakeRefPtr<ThemeManagerImpl>();
        pipelineContext_->SetThemeManager(themeManager);
        themeManager->InitResource(resourceInfo_);
        themeManager->SetColorScheme(colorScheme_);
        themeManager->LoadCustomTheme(assetManager_);
        themeManager->LoadResourceThemes();
    }

    auto cache = pipelineContext_->GetImageCache();
    if (cache) {
        cache->Clear();
    }
}

void AceContainer::GetNamesOfSharedImage(std::vector<std::string>& picNameArray)
{
    if (picNameArray.empty()) {
        LOGE("picNameArray is null!");
        return;
    }
    auto context = AceType::DynamicCast<NG::PipelineContext>(GetPipelineContext());
    CHECK_NULL_VOID(context);
    auto sharedImageManager = context->GetOrCreateSharedImageManager();
    auto nameSize = picNameArray.size();
    for (uint32_t i = 0; i < nameSize; i++) {
        // get name of picture
        auto name = picNameArray[i];
        sharedImageManager->AddPictureNamesToReloadMap(std::move(name));
    }
}

void AceContainer::UpdateSharedImage(
    std::vector<std::string>& picNameArray, std::vector<int32_t>& byteLenArray, std::vector<int>& fileDescriptorArray)
{
    auto context = GetPipelineContext();
    CHECK_NULL_VOID(context);
    if (picNameArray.empty() || byteLenArray.empty() || fileDescriptorArray.empty()) {
        LOGE("array is null! when try UpdateSharedImage");
        return;
    }
    auto nameArraySize = picNameArray.size();
    if (nameArraySize != byteLenArray.size()) {
        LOGE("nameArraySize does not equal to fileDescriptorArraySize, please check!");
        return;
    }
    if (nameArraySize != fileDescriptorArray.size()) {
        LOGE("nameArraySize does not equal to fileDescriptorArraySize, please check!");
        return;
    }
    // now it can be assured that all three arrays are of the same size

    std::string picNameCopy;
    for (uint32_t i = 0; i < nameArraySize; i++) {
        // get name of picture
        auto picName = picNameArray[i];
        // save a copy of picName and ReleaseStringUTFChars immediately to avoid memory leak
        picNameCopy = picName;

        // get fd ID
        auto fd = fileDescriptorArray[i];

        auto newFd = dup(fd);
        if (newFd < 0) {
            LOGE("dup fd fail, fail reason: %{public}s, fd: %{public}d, picName: %{private}s, length: %{public}d",
                strerror(errno), fd, picNameCopy.c_str(), byteLenArray[i]);
            continue;
        }

        auto ashmem = Ashmem(newFd, byteLenArray[i]);
        GetImageDataFromAshmem(picNameCopy, ashmem, context, byteLenArray[i]);
        ashmem.UnmapAshmem();
        ashmem.CloseAshmem();
    }
}

void AceContainer::GetImageDataFromAshmem(
    const std::string& picName, Ashmem& ashmem, const RefPtr<PipelineBase>& pipelineContext, int len)
{
    bool ret = ashmem.MapReadOnlyAshmem();
    // if any exception causes a [return] before [AddSharedImage], the memory image will not show because [RenderImage]
    // will never be notified to start loading.
    if (!ret) {
        LOGE("MapReadOnlyAshmem fail, fail reason: %{public}s, picName: %{private}s, length: %{public}d, "
             "fd: %{public}d",
            strerror(errno), picName.c_str(), len, ashmem.GetAshmemFd());
        return;
    }
    const uint8_t* imageData = reinterpret_cast<const uint8_t*>(ashmem.ReadFromAshmem(len, 0));
    if (imageData == nullptr) {
        LOGE("imageData is nullptr, errno is: %{public}s, picName: %{private}s, length: %{public}d, fd: %{public}d",
            strerror(errno), picName.c_str(), len, ashmem.GetAshmemFd());
        return;
    }
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
    CHECK_NULL_VOID(context);
    RefPtr<SharedImageManager> sharedImageManager = context->GetOrCreateSharedImageManager();
    if (sharedImageManager) {
        // read image data from shared memory and save a copy to sharedImageManager
        sharedImageManager->AddSharedImage(picName, std::vector<uint8_t>(imageData, imageData + len));
    }
}

bool AceContainer::IsSceneBoardWindow()
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD;
}

bool AceContainer::IsCrossAxisWindow()
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetCrossAxisState() == Rosen::CrossAxisState::STATE_CROSS;
}

bool AceContainer::IsUIExtensionWindow()
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_UI_EXTENSION;
}

void AceContainer::FireUIExtensionEventCallback(uint32_t eventId)
{
    if (!IsUIExtensionWindow()) {
        return;
    }
    ACE_SCOPED_TRACE("FireUIExtensionEventCallback event[%u]", eventId);
    uiWindow_->NotifyExtensionEventAsync(eventId);
}

bool AceContainer::IsSceneBoardEnabled()
{
    return Rosen::SceneBoardJudgement::IsSceneBoardEnabled();
}
// ArkTsCard end

bool AceContainer::IsMainWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW;
}

bool AceContainer::IsSubWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_APP_SUB_WINDOW;
}

bool AceContainer::IsDialogWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() == Rosen::WindowType::WINDOW_TYPE_DIALOG;
}

bool AceContainer::IsSystemWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetType() >= Rosen::WindowType::ABOVE_APP_SYSTEM_WINDOW_BASE &&
           uiWindow_->GetType() <= Rosen::WindowType::ABOVE_APP_SYSTEM_WINDOW_END;
}

uint32_t AceContainer::GetParentWindowType() const
{
    CHECK_NULL_RETURN(uiWindow_, DEFAULT_WINDOW_TYPE);
    return static_cast<uint32_t>(uiWindow_->GetParentWindowType());
}

uint32_t AceContainer::GetWindowType() const
{
    CHECK_NULL_RETURN(uiWindow_, DEFAULT_WINDOW_TYPE);
    return static_cast<uint32_t>(uiWindow_->GetType());
}

bool AceContainer::IsHostMainWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetParentWindowType() == Rosen::WindowType::WINDOW_TYPE_APP_MAIN_WINDOW;
}

bool AceContainer::IsHostSubWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetParentWindowType() == Rosen::WindowType::WINDOW_TYPE_APP_SUB_WINDOW;
}

bool AceContainer::IsHostDialogWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetParentWindowType() == Rosen::WindowType::WINDOW_TYPE_DIALOG;
}

bool AceContainer::IsHostSystemWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetParentWindowType() >= Rosen::WindowType::ABOVE_APP_SYSTEM_WINDOW_BASE &&
           uiWindow_->GetParentWindowType() <= Rosen::WindowType::ABOVE_APP_SYSTEM_WINDOW_END;
}

bool AceContainer::IsHostSceneBoardWindow() const
{
    CHECK_NULL_RETURN(uiWindow_, false);
    return uiWindow_->GetParentWindowType() == Rosen::WindowType::WINDOW_TYPE_SCENE_BOARD;
}

uint32_t AceContainer::GetParentMainWindowId(uint32_t currentWindowId) const
{
    uint32_t parentMainWindowId = 0;
    if (uiWindow_) {
        parentMainWindowId = uiWindow_->GetParentMainWindowId(currentWindowId);
        if (parentMainWindowId == 0) {
            TAG_LOGE(AceLogTag::ACE_SUB_WINDOW,
                "GetParentMainWindowId, current windowId: %{public}d, main windowId: %{public}d", currentWindowId,
                parentMainWindowId);
        }
    } else {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Window in container is nullptr when getting main windowId");
    }
    return parentMainWindowId;
}

void AceContainer::SetCurPointerEvent(const std::shared_ptr<MMI::PointerEvent>& currentEvent)
{
    std::lock_guard<std::mutex> lock(pointerEventMutex_);
    CHECK_NULL_VOID(currentEvent);
    currentPointerEvent_ = currentEvent;
    auto pointerAction = currentEvent->GetPointerAction();
    if (pointerAction == MMI::PointerEvent::POINTER_ACTION_PULL_IN_WINDOW ||
        pointerAction == MMI::PointerEvent::POINTER_ACTION_ENTER_WINDOW) {
        return;
    }
    MMI::PointerEvent::PointerItem pointerItem;
    currentEvent->GetPointerItem(currentEvent->GetPointerId(), pointerItem);
    int32_t originId = pointerItem.GetOriginPointerId();
    currentEvents_[originId] = currentEvent;
    auto callbacksIter = stopDragCallbackMap_.begin();
    while (callbacksIter != stopDragCallbackMap_.end()) {
        auto pointerId = callbacksIter->first;
        MMI::PointerEvent::PointerItem pointerItem;
        if (!currentEvent->GetPointerItem(pointerId, pointerItem) || !pointerItem.IsPressed() ||
            pointerAction == MMI::PointerEvent::POINTER_ACTION_CANCEL) {
            for (const auto& callback : callbacksIter->second) {
                if (callback) {
                    callback();
                }
            }
            callbacksIter = stopDragCallbackMap_.erase(callbacksIter);
        } else {
            ++callbacksIter;
        }
    }
}

bool AceContainer::GetCurPointerEventInfo(DragPointerEvent& dragPointerEvent, StopDragCallback&& stopDragCallback)
{
    std::lock_guard<std::mutex> lock(pointerEventMutex_);
    MMI::PointerEvent::PointerItem pointerItem;
    auto iter = currentEvents_.find(dragPointerEvent.pointerId);
    if (iter == currentEvents_.end()) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Can not find PointerEvent, pointerId: %{public}d.", dragPointerEvent.pointerId);
        return false;
    }

    auto currentPointerEvent = iter->second;
    CHECK_NULL_RETURN(currentPointerEvent, false);
    dragPointerEvent.pointerId = currentPointerEvent->GetPointerId();
    if (!currentPointerEvent->GetPointerItem(dragPointerEvent.pointerId, pointerItem)) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Can not find pointerItem, pointerId: %{public}d.", dragPointerEvent.pointerId);
        return false;
    }
    if (!pointerItem.IsPressed()) {
        TAG_LOGW(AceLogTag::ACE_DRAG, "Current pointer is not pressed, pointerId: %{public}d.",
            dragPointerEvent.pointerId);
        return false;
    }
    dragPointerEvent.sourceType = currentPointerEvent->GetSourceType();
    if (currentPointerEvent->GetSourceType() == OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN) {
        dragPointerEvent.displayX = NearZero(pointerItem.GetDisplayXPos())
                                        ? pointerItem.GetDisplayX()
                                        : static_cast<float>(pointerItem.GetDisplayXPos());
        dragPointerEvent.displayY = NearZero(pointerItem.GetDisplayYPos())
                                        ? pointerItem.GetDisplayY()
                                        : static_cast<float>(pointerItem.GetDisplayYPos());
        dragPointerEvent.windowX = NearZero(pointerItem.GetWindowXPos())
                                       ? pointerItem.GetWindowX()
                                       : static_cast<float>(pointerItem.GetWindowXPos());
        dragPointerEvent.windowY = NearZero(pointerItem.GetWindowYPos())
                                       ? pointerItem.GetWindowY()
                                       : static_cast<float>(pointerItem.GetWindowYPos());
    } else {
        dragPointerEvent.displayX = pointerItem.GetDisplayX();
        dragPointerEvent.displayY = pointerItem.GetDisplayY();
        dragPointerEvent.windowX = pointerItem.GetWindowX();
        dragPointerEvent.windowY = pointerItem.GetWindowY();
    }
    dragPointerEvent.globalDisplayX = pointerItem.GetGlobalX();
    dragPointerEvent.globalDisplayY = pointerItem.GetGlobalY();
    dragPointerEvent.deviceId = pointerItem.GetDeviceId();
    dragPointerEvent.sourceTool = static_cast<SourceTool>(pointerItem.GetToolType());
    dragPointerEvent.displayId = currentPointerEvent->GetTargetDisplayId();
    dragPointerEvent.pointerEventId = currentPointerEvent->GetId();
    dragPointerEvent.originId = pointerItem.GetOriginPointerId();
    RegisterStopDragCallback(dragPointerEvent.pointerId, std::move(stopDragCallback));
    return true;
}

bool AceContainer::GetCurPointerEventSourceType(int32_t& sourceType)
{
    std::lock_guard<std::mutex> lock(pointerEventMutex_);
    CHECK_NULL_RETURN(currentPointerEvent_, false);
    MMI::PointerEvent::PointerItem pointerItem;
    sourceType = currentPointerEvent_->GetSourceType();
    return true;
}

void AceContainer::RegisterStopDragCallback(int32_t pointerId, StopDragCallback&& stopDragCallback)
{
    auto iter = stopDragCallbackMap_.find(pointerId);
    if (iter != stopDragCallbackMap_.end()) {
        iter->second.emplace_back(std::move(stopDragCallback));
    } else {
        std::list<StopDragCallback> list;
        list.emplace_back(std::move(stopDragCallback));
        stopDragCallbackMap_.emplace(pointerId, list);
    }
}

bool AceContainer::GetLastMovingPointerPosition(DragPointerEvent& dragPointerEvent)
{
    std::lock_guard<std::mutex> lock(pointerEventMutex_);
    auto iter = currentEvents_.find(dragPointerEvent.originId);
    if (iter == currentEvents_.end()) {
        return false;
    }
    MMI::PointerEvent::PointerItem pointerItem;
    auto currentPointerEvent = iter->second;
    CHECK_NULL_RETURN(currentPointerEvent, false);
    if (!currentPointerEvent->GetPointerItem(currentPointerEvent->GetPointerId(), pointerItem) ||
        !pointerItem.IsPressed()) {
        return false;
    }
    if (currentPointerEvent->GetSourceType() == OHOS::MMI::PointerEvent::SOURCE_TYPE_TOUCHSCREEN) {
        dragPointerEvent.displayX = NearZero(pointerItem.GetDisplayXPos())
                                        ? pointerItem.GetDisplayX()
                                        : static_cast<float>(pointerItem.GetDisplayXPos());
        dragPointerEvent.displayY = NearZero(pointerItem.GetDisplayYPos())
                                        ? pointerItem.GetDisplayY()
                                        : static_cast<float>(pointerItem.GetDisplayYPos());
        dragPointerEvent.windowX = NearZero(pointerItem.GetWindowXPos())
                                       ? pointerItem.GetWindowX()
                                       : static_cast<float>(pointerItem.GetWindowXPos());
        dragPointerEvent.windowY = NearZero(pointerItem.GetWindowYPos())
                                       ? pointerItem.GetWindowY()
                                       : static_cast<float>(pointerItem.GetWindowYPos());
    } else {
        dragPointerEvent.displayX = pointerItem.GetDisplayX();
        dragPointerEvent.displayY = pointerItem.GetDisplayY();
        dragPointerEvent.windowX = pointerItem.GetWindowX();
        dragPointerEvent.windowY = pointerItem.GetWindowY();
    }
    dragPointerEvent.globalDisplayX = pointerItem.GetGlobalX();
    dragPointerEvent.globalDisplayY = pointerItem.GetGlobalY();
    return true;
}

void AceContainer::SearchElementInfoByAccessibilityIdNG(
    int64_t elementId, int32_t mode, int64_t baseParent, std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTaskTimeout(
        [weak = WeakClaim(this), elementId, mode, baseParent, &output]() {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            auto accessibilityManager = frontend->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            accessibilityManager->SearchElementInfoByAccessibilityIdNG(elementId, mode, output, ngPipeline, baseParent);
        },
        TaskExecutor::TaskType::UI, SEARCH_ELEMENT_TIMEOUT_TIME, "ArkUISearchElementInfoById");
}

void AceContainer::SearchElementInfosByTextNG(int64_t elementId, const std::string& text, int64_t baseParent,
    std::list<Accessibility::AccessibilityElementInfo>& output)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTaskTimeout(
        [weak = WeakClaim(this), elementId, &text, baseParent, &output]() {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            auto accessibilityManager = frontend->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            accessibilityManager->SearchElementInfosByTextNG(elementId, text, output, ngPipeline, baseParent);
        },
        TaskExecutor::TaskType::UI, SEARCH_ELEMENT_TIMEOUT_TIME, "ArkUISearchElementInfoByText");
}

void AceContainer::FindFocusedElementInfoNG(
    int64_t elementId, int32_t focusType, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTaskTimeout(
        [weak = WeakClaim(this), elementId, focusType, baseParent, &output]() {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            auto accessibilityManager = frontend->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            accessibilityManager->FindFocusedElementInfoNG(elementId, focusType, output, ngPipeline, baseParent);
        },
        TaskExecutor::TaskType::UI, SEARCH_ELEMENT_TIMEOUT_TIME, "ArkUIFindFocusedElementInfo");
}

void AceContainer::FocusMoveSearchNG(
    int64_t elementId, int32_t direction, int64_t baseParent, Accessibility::AccessibilityElementInfo& output)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostSyncTaskTimeout(
        [weak = WeakClaim(this), elementId, direction, baseParent, &output]() {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            auto accessibilityManager = frontend->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            accessibilityManager->FocusMoveSearchNG(elementId, direction, output, ngPipeline, baseParent);
        },
        TaskExecutor::TaskType::UI, SEARCH_ELEMENT_TIMEOUT_TIME, "ArkUIFocusMoveSearch");
}

bool AceContainer::NotifyExecuteAction(
    int64_t elementId, const std::map<std::string, std::string>& actionArguments, int32_t action, int64_t offset)
{
    bool IsExecuted = false;
    CHECK_NULL_RETURN(taskExecutor_, IsExecuted);
    taskExecutor_->PostSyncTaskTimeout(
        [weak = WeakClaim(this), elementId, &actionArguments, action, offset, &IsExecuted]() {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto frontend = container->GetFrontend();
            CHECK_NULL_VOID(frontend);
            auto accessibilityManager = frontend->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            IsExecuted =
                accessibilityManager->ExecuteExtensionActionNG(elementId, actionArguments, action, ngPipeline, offset);
        },
        TaskExecutor::TaskType::UI, SEARCH_ELEMENT_TIMEOUT_TIME, "ArkUIExecuteExtensionAction");
    return IsExecuted;
}

void AceContainer::HandleAccessibilityHoverEvent(
    float pointX, float pointY, int32_t sourceType, int32_t eventType, int64_t timeMs)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), pointX, pointY, sourceType, eventType, timeMs] {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            ContainerScope scope(container->GetInstanceId());
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto root = ngPipeline->GetRootElement();
            CHECK_NULL_VOID(root);
            auto accessibilityManagerNG = ngPipeline->GetAccessibilityManagerNG();
            CHECK_NULL_VOID(accessibilityManagerNG);
            accessibilityManagerNG->HandleAccessibilityHoverEvent(root, pointX, pointY, sourceType, eventType, timeMs);
        },
        TaskExecutor::TaskType::UI, "ArkUIHandleAccessibilityHoverEvent");
}

void AceContainer::FireAccessibilityEventCallback(uint32_t eventId, int64_t parameter)
{
    CHECK_NULL_VOID(taskExecutor_);
    taskExecutor_->PostTask(
        [weak = WeakClaim(this), eventId, parameter] {
            auto container = weak.Upgrade();
            CHECK_NULL_VOID(container);
            ContainerScope scope(container->GetInstanceId());
            auto pipelineContext = container->GetPipelineContext();
            auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
            CHECK_NULL_VOID(ngPipeline);
            auto accessibilityManager = ngPipeline->GetAccessibilityManager();
            CHECK_NULL_VOID(accessibilityManager);
            accessibilityManager->FireAccessibilityEventCallback(eventId, parameter);
        },
        TaskExecutor::TaskType::UI, "ArkUIHandleAccessibilityEventCallback");
}

std::vector<Ace::RectF> AceContainer::GetOverlayNodePositions()
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_RETURN(pipeline, {});
    return pipeline->GetOverlayNodePositions();
}

void AceContainer::RegisterOverlayNodePositionsUpdateCallback(
    const std::function<void(std::vector<Ace::RectF>)>&& callback)
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(pipeline);
    pipeline->RegisterOverlayNodePositionsUpdateCallback(std::move(callback));
}

void AceContainer::TerminateUIExtension()
{
    if (!IsUIExtensionWindow()) {
        return;
    }
    auto sharedContext = runtimeContext_.lock();
    auto uiExtensionContext = AbilityRuntime::Context::ConvertTo<AbilityRuntime::UIExtensionContext>(sharedContext);
    CHECK_NULL_VOID(uiExtensionContext);
    uiExtensionContext->TerminateSelf();
}

void AceContainer::RequestAtomicServiceTerminate()
{
    if (!IsUIExtensionWindow()) {
        TAG_LOGE(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "Not uiextension window.");
        return;
    }
    auto sharedContext = runtimeContext_.lock();
    auto uiExtensionContext = AbilityRuntime::Context::ConvertTo<AbilityRuntime::UIExtensionContext>(sharedContext);
    CHECK_NULL_VOID(uiExtensionContext);
    uiExtensionContext->RequestComponentTerminate();
}

bool AceContainer::UIExtensionIsHalfScreen()
{
    if (!IsUIExtensionWindow()) {
        return false;
    }
    auto sharedContext = runtimeContext_.lock();
    auto uiExtensionContext = AbilityRuntime::Context::ConvertTo<AbilityRuntime::UIExtensionContext>(sharedContext);
    CHECK_NULL_RETURN(uiExtensionContext, false);
    return uiExtensionContext->GetScreenMode() == EXTENSION_HALF_SCREEN_MODE;
}

Rosen::WMError AceContainer::RegisterAvoidAreaChangeListener(sptr<Rosen::IAvoidAreaChangedListener>& listener)
{
    if (!uiWindow_) {
        return Rosen::WMError::WM_DO_NOTHING;
    }
    return uiWindow_->RegisterAvoidAreaChangeListener(listener);
}

Rosen::WMError AceContainer::UnregisterAvoidAreaChangeListener(sptr<Rosen::IAvoidAreaChangedListener>& listener)
{
    if (!uiWindow_) {
        return Rosen::WMError::WM_DO_NOTHING;
    }
    return uiWindow_->UnregisterAvoidAreaChangeListener(listener);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_HotReloadPage()
{
    AceEngine::Get().NotifyContainers([](const RefPtr<Container>& container) {
        LOGI("starting hotReload");
#ifndef NG_BUILD
        if (Container::IsCurrentUseNewPipeline()) {
            container->HotReload();
        } else {
            container->NotifyConfigurationChange(true);
        }
#else
        container->HotReload();
#endif
    });
}

bool AceContainer::NeedFullUpdate(uint32_t limitKey)
{
    auto themeManager = pipelineContext_->GetThemeManager();
    if (!themeManager || (themeManager->GetResourceLimitKeys() & limitKey) == 0) {
        return false;
    }
    return true;
}

void AceContainer::NotifyDensityUpdate(double density)
{
    bool fullUpdate = NeedFullUpdate(DENSITY_KEY);
    auto frontend = GetFrontend();
    if (frontend) {
        frontend->FlushReload();
    }
    UpdateResourceDensity(density, fullUpdate);
    ConfigurationChange configurationChange { .dpiUpdate = true };
    pipelineContext_->FlushReload(configurationChange, fullUpdate);
}

void AceContainer::NotifyDirectionUpdate()
{
    bool fullUpdate = NeedFullUpdate(DIRECTION_KEY);
    if (fullUpdate) {
        ConfigurationChange configurationChange { .directionUpdate = true };
        pipelineContext_->FlushReload(configurationChange, fullUpdate);
    }
}

void AceContainer::RenderLayoutBoundary(bool isDebugBoundary)
{
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    CHECK_NULL_VOID(renderBoundaryManager_);
    renderBoundaryManager_->PostTaskRenderBoundary(isDebugBoundary, container);
}

void AceContainer::AddWatchSystemParameter()
{
    auto task = [weak = WeakClaim(this)] {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        auto rawPtr = static_cast<void*>(Referenced::RawPtr(container));
        CHECK_NULL_VOID(rawPtr);
        SystemProperties::AddWatchSystemParameter(
            ENABLE_TRACE_LAYOUT_KEY, rawPtr, SystemProperties::EnableSystemParameterTraceLayoutCallback);
        SystemProperties::AddWatchSystemParameter(
            ENABLE_TRACE_INPUTEVENT_KEY, rawPtr, SystemProperties::EnableSystemParameterTraceInputEventCallback);
        SystemProperties::AddWatchSystemParameter(ENABLE_SECURITY_DEVELOPERMODE_KEY, rawPtr,
            SystemProperties::EnableSystemParameterSecurityDevelopermodeCallback);
        SystemProperties::AddWatchSystemParameter(
            ENABLE_DEBUG_STATEMGR_KEY, rawPtr, SystemProperties::EnableSystemParameterDebugStatemgrCallback);
        SystemProperties::AddWatchSystemParameter(
            ENABLE_DEBUG_BOUNDARY_KEY, rawPtr, SystemProperties::EnableSystemParameterDebugBoundaryCallback);
        SystemProperties::AddWatchSystemParameter(ENABLE_PERFORMANCE_MONITOR_KEY, rawPtr,
            SystemProperties::EnableSystemParameterPerformanceMonitorCallback);
        SystemProperties::AddWatchSystemParameter(
            IS_FOCUS_ACTIVE_KEY, rawPtr, SystemProperties::OnFocusActiveChanged);
    };
    BackgroundTaskExecutor::GetInstance().PostTask(task);
}

void AceContainer::RemoveUISessionCallbacks()
{
    UiSessionManager::GetInstance()->RemoveSaveGetCurrentInstanceId(instanceId_);
}

void AceContainer::RemoveWatchSystemParameter()
{
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_TRACE_LAYOUT_KEY, this, SystemProperties::EnableSystemParameterTraceLayoutCallback);
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_TRACE_INPUTEVENT_KEY, this, SystemProperties::EnableSystemParameterTraceInputEventCallback);
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_SECURITY_DEVELOPERMODE_KEY, this, SystemProperties::EnableSystemParameterSecurityDevelopermodeCallback);
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_DEBUG_STATEMGR_KEY, this, SystemProperties::EnableSystemParameterDebugStatemgrCallback);
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_DEBUG_BOUNDARY_KEY, this, SystemProperties::EnableSystemParameterDebugBoundaryCallback);
    SystemProperties::RemoveWatchSystemParameter(
        ENABLE_PERFORMANCE_MONITOR_KEY, this, SystemProperties::EnableSystemParameterPerformanceMonitorCallback);
    SystemProperties::RemoveWatchSystemParameter(IS_FOCUS_ACTIVE_KEY, this, SystemProperties::OnFocusActiveChanged);
}

void AceContainer::UpdateResourceOrientation(int32_t orientation)
{
    DeviceOrientation newOrientation = WindowUtils::GetDeviceOrientation(orientation);
    auto resConfig = GetResourceConfiguration();
    resConfig.SetOrientation(newOrientation);
    if (SystemProperties::GetResourceDecoupling()) {
        ResourceManager::GetInstance().UpdateResourceConfig(resConfig, false);
    }
    SetResourceConfiguration(resConfig);
}

void AceContainer::UpdateResourceDensity(double density, bool isUpdateResConfig)
{
    auto resConfig = GetResourceConfiguration();
    resConfig.SetDensity(density);
    SetResourceConfiguration(resConfig);
    if (SystemProperties::GetResourceDecoupling() && (isUpdateResConfig || !IsSceneBoardWindow())) {
        ResourceManager::GetInstance().UpdateResourceConfig(resConfig, false);
    }
}

void AceContainer::RegisterUIExtDataConsumer()
{
    ACE_FUNCTION_TRACE();
    if (!IsUIExtensionWindow()) {
        return;
    }
    CHECK_NULL_VOID(uiWindow_);
    auto dataHandler = uiWindow_->GetExtensionDataHandler();
    CHECK_NULL_VOID(dataHandler);
    auto uiExtDataConsumeCallback = [weak = WeakClaim(this)](SubSystemId id, uint32_t customId, AAFwk::Want&& data,
                                        std::optional<AAFwk::Want>& reply) -> int32_t {
        auto container = weak.Upgrade();
        CHECK_NULL_RETURN(container, 0);
        container->DispatchUIExtDataConsume(static_cast<NG::UIContentBusinessCode>(customId), data, reply);
        return 0;
    };
    auto result = dataHandler->RegisterDataConsumer(SubSystemId::ARKUI_UIEXT, std::move(uiExtDataConsumeCallback));
    if (result != Rosen::DataHandlerErr::OK) {
        TAG_LOGW(
            AceLogTag::ACE_UIEXTENSIONCOMPONENT, "RegisterUIExtDataConsumer fail, same subSystemId repeate registe.");
    }
}

void AceContainer::UnRegisterUIExtDataConsumer()
{
    ACE_FUNCTION_TRACE();
    if (!IsUIExtensionWindow()) {
        return;
    }
    CHECK_NULL_VOID(uiWindow_);
    auto dataHandler = uiWindow_->GetExtensionDataHandler();
    CHECK_NULL_VOID(dataHandler);
    dataHandler->UnregisterDataConsumer(SubSystemId::ARKUI_UIEXT);
}

void AceContainer::DispatchUIExtDataConsume(
    NG::UIContentBusinessCode code, const AAFwk::Want& data, std::optional<AAFwk::Want>& reply)
{
    ACE_FUNCTION_TRACE();
    CHECK_NULL_VOID(taskExecutor_);
    if (reply.has_value()) {
        taskExecutor_->PostSyncTask(
            [weak = WeakClaim(this), code, data, &reply] {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                ContainerScope scop(container->GetInstanceId());
                auto pipelineContext = container->GetPipelineContext();
                auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
                CHECK_NULL_VOID(ngPipeline);
                auto uiExtManager = ngPipeline->GetUIExtensionManager();
                CHECK_NULL_VOID(uiExtManager);
                uiExtManager->DispatchBusinessDataConsumeReply(code, data, reply);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIxtDispatchDataConsumeReplyCallback");
    } else {
        taskExecutor_->PostTask(
            [weak = WeakClaim(this), code, data] {
                auto container = weak.Upgrade();
                CHECK_NULL_VOID(container);
                ContainerScope scop(container->GetInstanceId());
                auto pipelineContext = container->GetPipelineContext();
                auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext);
                CHECK_NULL_VOID(ngPipeline);
                auto uiExtManager = ngPipeline->GetUIExtensionManager();
                CHECK_NULL_VOID(uiExtManager);
                uiExtManager->DispatchBusinessDataConsume(code, data);
            },
            TaskExecutor::TaskType::UI, "ArkUIUIxtDispatchDataConsumeCallback");
    }
}

void AceContainer::DispatchExtensionDataToHostWindow(uint32_t code, const AAFwk::Want& data, int32_t persistentId)
{
    CHECK_NULL_VOID(uiWindow_);
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "DispatchExtensionDataToHostWindow code=%{public}u, want=%{public}s, persistentId=%{public}d.",
        code, data.ToString().c_str(), persistentId);
    uiWindow_->OnExtensionMessage(code, persistentId, data);
}

bool AceContainer::FireUIExtDataSendToHost(
    NG::UIContentBusinessCode code, const AAFwk::Want& data, NG::BusinessDataSendType type)
{
    if (code == NG::UIContentBusinessCode::UNDEFINED) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExt send data to host fail, businessCode is invalid.");
        return false;
    }
    if (!IsUIExtensionWindow()) {
        return false;
    }
    CHECK_NULL_RETURN(uiWindow_, false);
    auto dataHandler = uiWindow_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    if (type == NG::BusinessDataSendType::ASYNC) {
        dataHandler->SendDataAsync(SubSystemId::ARKUI_UIEXT, static_cast<uint32_t>(code), data);
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExt sent data to host async success, businessCode=%{public}d.",
            code);
        return true;
    }
    auto result = dataHandler->SendDataSync(SubSystemId::ARKUI_UIEXT, static_cast<uint32_t>(code), data);
    if (result != DataHandlerErr::OK) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExt sent data to host sync fail, businessCode=%{public}d, result=%{public}d.", code,
            static_cast<uint32_t>(result));
        return false;
    }
    TAG_LOGI(
        AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExt sent data to host async success, businessCode=%{public}d.", code);
    return true;
}

bool AceContainer::FireUIExtDataSendToHostReply(
    NG::UIContentBusinessCode code, const AAFwk::Want& data, AAFwk::Want& reply)
{
    if (code == NG::UIContentBusinessCode::UNDEFINED) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT, "UIExt send data to host fail, businessCode is invalid.");
        return false;
    }
    if (!IsUIExtensionWindow()) {
        return false;
    }
    CHECK_NULL_RETURN(uiWindow_, false);
    auto dataHandler = uiWindow_->GetExtensionDataHandler();
    CHECK_NULL_RETURN(dataHandler, false);
    auto result = dataHandler->SendDataSync(SubSystemId::ARKUI_UIEXT, static_cast<uint32_t>(code), data, reply);
    if (result != DataHandlerErr::OK) {
        TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
            "UIExt sent data to host sync reply fail, businessCode=%{public}d, result=%{public}d.", code,
            static_cast<uint32_t>(result));
        return false;
    }
    TAG_LOGI(AceLogTag::ACE_UIEXTENSIONCOMPONENT,
        "UIExt sent data to host sync reply success, businessCode=%{public}d.", code);
    return true;
}

void AceContainer::RegisterUIExtDataSendToHost()
{
    auto uiExtDataSendSyncReply = [weak = WeakClaim(this)](
        uint32_t customId, const AAFwk::Want& data, AAFwk::Want& reply) -> bool {
        auto container = weak.Upgrade();
        CHECK_NULL_RETURN(container, false);
        return container->FireUIExtDataSendToHostReply(
            static_cast<NG::UIContentBusinessCode>(customId), data, reply);
    };
    auto uiExtDataSend = [weak = WeakClaim(this)](
        uint32_t customId, const AAFwk::Want& data, NG::BusinessDataSendType type) -> bool {
        auto container = weak.Upgrade();
        CHECK_NULL_RETURN(container, false);
        return container->FireUIExtDataSendToHost(
            static_cast<NG::UIContentBusinessCode>(customId), data, type);
    };
    auto ngPipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(ngPipeline);
    auto uiExtManager = ngPipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtManager);
    uiExtManager->RegisterBusinessSendToHostReply(uiExtDataSendSyncReply);
    uiExtManager->RegisterBusinessSendToHost(uiExtDataSend);
}

void AceContainer::SetDrawReadyEventCallback()
{
    CHECK_NULL_VOID(uiWindow_);
    auto surfaceNode = uiWindow_->GetSurfaceNode();
    CHECK_NULL_VOID(surfaceNode);
    auto callback = [weak = WeakClaim(this)]() {
        auto container = weak.Upgrade();
        CHECK_NULL_VOID(container);
        container->FireUIExtensionEventCallback(static_cast<int>(NG::UIExtCallbackEventId::ON_DRAW_FIRST));
    };
    surfaceNode->SetBufferAvailableCallback(callback);
}

Rect AceContainer::GetDisplayAvailableRect() const
{
    if (!uiWindow_) {
        TAG_LOGW(AceLogTag::ACE_WINDOW, "uiwindow is null, can't get displayId");
        return Rect();
    }

    return displayManager_->GetDisplayAvailableRect(uiWindow_->GetDisplayId());
}

Rect AceContainer::GetFoldExpandAvailableRect() const
{
    return displayManager_->GetFoldExpandAvailableRect();
}

void AceContainer::GetExtensionConfig(AAFwk::WantParams& want)
{
    CHECK_NULL_VOID(uiWindow_);
    uiWindow_->GetExtensionConfig(want);
}

void AceContainer::SetIsFocusActive(bool isFocusActive)
{
    auto pipelineContext = DynamicCast<NG::PipelineContext>(GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetIsFocusActive(isFocusActive);
}

bool AceContainer::CloseWindow(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "AceContainer CloseWindow begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Close();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "AceContainer CloseWindow Failed to close the window.");
        return false;
    }
    sptr<OHOS::Rosen::Window> uiWindow = nullptr;
    AceContainer::SetUIWindow(instanceId, uiWindow);
    return true;
}

bool AceContainer::HideWindow(int32_t instanceId)
{
    TAG_LOGI(AceLogTag::ACE_DIALOG, "AceContainer HideWindow begin");
    auto container = AceType::DynamicCast<AceContainer>(AceEngine::Get().GetContainer(instanceId));
    CHECK_NULL_RETURN(container, false);
    auto window = container->GetUIWindowInner();
    CHECK_NULL_RETURN(window, false);
    OHOS::Rosen::WMError ret = window->Hide();
    if (ret != OHOS::Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_DIALOG, "AceContainer HideWindow Failed to hide the window.");
        return false;
    }
    sptr<OHOS::Rosen::Window> uiWindow = nullptr;
    AceContainer::SetUIWindow(instanceId, uiWindow);
    return true;
}

void AceContainer::RegisterAvoidInfoCallback()
{
    RegisterAvoidInfoDataProcessCallback();

#ifdef WINDOW_SCENE_SUPPORTED
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(pipeline);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(avoidInfoMgr);
    auto uiExtMgr = pipeline->GetUIExtensionManager();
    CHECK_NULL_VOID(uiExtMgr);
    auto checkTask = [weakMgr = WeakPtr(uiExtMgr)]() {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->NotifyUECProviderIfNeedded();
    };
    auto registerCallback = [weakMgr = WeakPtr(uiExtMgr)](NG::UECAvoidInfoConsumer&& consumer) {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        mgr->RegisterBusinessDataConsumeCallback(NG::UIContentBusinessCode::NOTIFY_AVOID_INFO_CHANGE, consumer);
    };
    auto requestCallback = [weakMgr = WeakPtr(uiExtMgr)]() {
        auto mgr = weakMgr.Upgrade();
        CHECK_NULL_VOID(mgr);
        AAFwk::Want want;
        mgr->SendBusinessToHost(
            NG::UIContentBusinessCode::GET_AVOID_INFO, std::move(want), NG::BusinessDataSendType::ASYNC);
    };
    pipeline->AddPersistAfterLayoutTask(std::move(checkTask));
    avoidInfoMgr->SetRegisterUECAvoidInfoConsumerCallback(std::move(registerCallback));
    avoidInfoMgr->SetRequestAvoidInfoCallback(std::move(requestCallback));
#endif
}

void AceContainer::RegisterAvoidInfoDataProcessCallback()
{
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(pipeline);
    auto avoidInfoMgr = pipeline->GetAvoidInfoManager();
    CHECK_NULL_VOID(avoidInfoMgr);
    auto parseCallback = [](const AAFwk::Want& want, NG::ContainerModalAvoidInfo& info) {
        if (!want.HasParameter("needAvoid")) {
            TAG_LOGW(AceLogTag::ACE_NAVIGATION, "Invalid want for ContainerModalAvoidInfo");
            return false;
        }
        bool needAvoid = want.GetBoolParam("needAvoid", false);
        int32_t titleHeight = want.GetIntParam("titleHeight", 0);
        float x = want.GetFloatParam("controlBottonsRectX", 0);
        float y = want.GetFloatParam("controlBottonsRectY", 0);
        float w = want.GetFloatParam("controlBottonsRectW", 0);
        float h = want.GetFloatParam("controlBottonsRectH", 0);
        info.needAvoid = needAvoid;
        info.titleHeight = titleHeight;
        info.controlBottonsRect.SetRect(x, y, w, h);
        return true;
    };
    auto buildCallback = [](const NG::ContainerModalAvoidInfo& info, AAFwk::Want& want) {
        want.SetParam("needAvoid", info.needAvoid);
        want.SetParam("titleHeight", info.titleHeight);
        want.SetParam("controlBottonsRectX", info.controlBottonsRect.GetX());
        want.SetParam("controlBottonsRectY", info.controlBottonsRect.GetY());
        want.SetParam("controlBottonsRectW", info.controlBottonsRect.Width());
        want.SetParam("controlBottonsRectH", info.controlBottonsRect.Height());
    };
    avoidInfoMgr->SetParseAvoidInfoCallback(std::move(parseCallback));
    avoidInfoMgr->SetBuildAvoidInfoCallback(std::move(buildCallback));
}

RefPtr<PageViewportConfig> AceContainer::GetCurrentViewportConfig() const
{
    auto config = AceType::MakeRefPtr<PageViewportConfigOhos>();
    CHECK_NULL_RETURN(config, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_RETURN(context, nullptr);
    auto mgr = context->GetSafeAreaManager();
    CHECK_NULL_RETURN(mgr, nullptr);
    config->SetPipelineContext(WeakPtr(context));

    ViewportConfig viewportConfig;
    // the position is not needed, set it to (0, 0)
    viewportConfig.SetPosition(0, 0);
    int32_t width = static_cast<int32_t>(context->GetRootWidth());
    int32_t height = static_cast<int32_t>(context->GetRootHeight());
    auto displayOri = static_cast<int32_t>(GetCurrentDisplayOrientation());
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "current displayOri:%{public}d, width:%{public}d, height:%{public}d",
        displayOri, width, height);
    viewportConfig.SetSize(width, height);
    viewportConfig.SetOrientation(displayOri);
    config->SetViewportConfig(viewportConfig);

    AvoidAreaInfo avoidAreas;
    auto insets = mgr->GetSystemSafeArea();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "current TYPE_SYSTEM safeArea:%{public}s", insets.ToString().c_str());
    auto systemAvoidArea = ConvertAvoidArea(insets, width, height);
    avoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM, systemAvoidArea);
    insets = mgr->GetCutoutSafeArea();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "current TYPE_CUTOUT safeArea:%{public}s", insets.ToString().c_str());
    auto cutoutArea = ConvertAvoidArea(insets, width, height);
    avoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT, cutoutArea);
    insets = mgr->GetNavSafeArea();
    TAG_LOGI(AceLogTag::ACE_NAVIGATION,
        "current TYPE_NAVIGATION_INDICATOR safeArea:%{public}s", insets.ToString().c_str());
    auto navArea = ConvertAvoidArea(insets, width, height);
    avoidAreas.emplace(OHOS::Rosen::AvoidAreaType::TYPE_NAVIGATION_INDICATOR, navArea);
    config->SetAvoidAreas(avoidAreas);

    return config;
}

RefPtr<PageViewportConfig> AceContainer::GetTargetViewportConfig(
    std::optional<Orientation> orientation, std::optional<bool> enableStatusBar,
    std::optional<bool> statusBarAnimation, std::optional<bool> enableNavIndicator) const
{
    CHECK_NULL_RETURN(uiWindow_, nullptr);
    auto config = AceType::MakeRefPtr<PageViewportConfigOhos>();
    CHECK_NULL_RETURN(config, nullptr);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_RETURN(context, nullptr);
    config->SetPipelineContext(WeakPtr(context));

    std::map<Rosen::WindowType, Rosen::SystemBarProperty> properties;
    if (enableStatusBar.has_value()) {
        auto property = uiWindow_->GetSystemBarPropertyByType(Rosen::WindowType::WINDOW_TYPE_STATUS_BAR);
        property.enable_ = enableStatusBar.value();
        property.enableAnimation_ = statusBarAnimation.value_or(false);
        SetSystemBarPropertyEnableFlag(property);
        properties.emplace(Rosen::WindowType::WINDOW_TYPE_STATUS_BAR, property);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "GetTargetViewportInfo with enableStatusBar:%{public}d, statusBarAnimation:%{public}d",
            enableStatusBar.value(), statusBarAnimation.value_or(false));
    }
    if (enableNavIndicator.has_value()) {
        auto property = uiWindow_->GetSystemBarPropertyByType(Rosen::WindowType::WINDOW_TYPE_NAVIGATION_INDICATOR);
        property.enable_ = enableNavIndicator.value();
        SetSystemBarPropertyEnableFlag(property);
        properties.emplace(Rosen::WindowType::WINDOW_TYPE_NAVIGATION_INDICATOR, property);
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "GetTargetViewportInfo with enableNavIndicator:%{public}d",
            enableNavIndicator.value());
    }
    Rosen::Orientation ori = Rosen::Orientation::INVALID;
    if (orientation.has_value()) {
        ori = static_cast<Rosen::Orientation>(static_cast<int32_t>(orientation.value()));
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "GetTargetViewportInfo with orientation:%{public}d", static_cast<int32_t>(ori));
    }

    ViewportConfig viewportConfig;
    AvoidAreaInfo avoidAreas;
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "get targetConfigInfo with ori:%{public}d", static_cast<int32_t>(ori));
    auto ret = uiWindow_->GetTargetOrientationConfigInfo(ori, properties, viewportConfig, avoidAreas);
    if (Rosen::WMError::WM_OK != ret) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Failed to get targetOrientationInfo from window, error:%{public}d",
            static_cast<int32_t>(ret));
        return nullptr;
    }

    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "ViewportConfig: %{public}s, SafeAreas:%{public}s",
        viewportConfig.ToString().c_str(), StringifyAvoidAreas(avoidAreas).c_str());
    config->SetViewportConfig(viewportConfig);
    config->SetAvoidAreas(avoidAreas);

    return config;
}

void AceContainer::RegisterOrientationChangeListener()
{
    CHECK_NULL_VOID(uiWindow_);
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(context);
    auto navigationMgr = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationMgr);
    auto listener = new WindowOrientationChangeListener(GetInstanceId(), WeakPtr(navigationMgr));
    if (uiWindow_->RegisterOrientationChangeListener(listener) != Rosen::WMError::WM_OK) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Failed to register Orientation change listener");
    }
}

bool AceContainer::SetSystemBarEnabled(const sptr<OHOS::Rosen::Window>& window, SystemBarType type,
    std::optional<bool> enable, std::optional<bool> animation)
{
    CHECK_NULL_RETURN(window, false);
    Rosen::WindowType winType;
    switch (type) {
        case SystemBarType::STATUS:
            winType = Rosen::WindowType::WINDOW_TYPE_STATUS_BAR;
            break;
        case SystemBarType::NAVIGATION_INDICATOR:
            winType = Rosen::WindowType::WINDOW_TYPE_NAVIGATION_INDICATOR;
            break;
        default:
            return false;
    }

    std::optional<Rosen::SystemBarProperty> newProperty;
    if (enable.has_value()) {
        auto property = window->GetSystemBarPropertyByType(winType);
        property.enable_ = enable.value();
        property.enableAnimation_ = animation.value_or(false);
        SetSystemBarPropertyEnableFlag(property);
        newProperty = property;
        TAG_LOGI(AceLogTag::ACE_NAVIGATION,
            "Set page-level SystemBar: type:%{public}d, enable:%{public}d, animation:%{public}d",
            static_cast<int32_t>(winType), enable.value(), animation.value_or(false));
    } else {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "Clear page-level SystemBar type:%{public}d",
            static_cast<int32_t>(winType));
    }
    if (Rosen::WMError::WM_OK != window->SetSystemBarPropertyForPage(winType, newProperty)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "Failed to set page-level systemBar property");
        return false;
    }
    return true;
}

void AceContainer::SubscribeHighContrastChange()
{
    if (!Rosen::RSUIDirector::IsHybridRenderEnabled()) {
        return;
    }
    if (highContrastObserver_ != nullptr) {
        return;
    }
    auto& config = AccessibilityConfig::AccessibilityConfig::GetInstance();
    if (!config.InitializeContext()) {
        return;
    }
    highContrastObserver_ = std::make_shared<HighContrastObserver>(WeakClaim(this));
    config.SubscribeConfigObserver(AccessibilityConfig::CONFIG_ID::CONFIG_HIGH_CONTRAST_TEXT, highContrastObserver_);
}

void AceContainer::UnsubscribeHighContrastChange()
{
    if (highContrastObserver_ == nullptr) {
        return;
    }
    auto& config = AccessibilityConfig::AccessibilityConfig::GetInstance();
    if (config.InitializeContext()) {
        config.UnsubscribeConfigObserver(
            AccessibilityConfig::CONFIG_ID::CONFIG_HIGH_CONTRAST_TEXT, highContrastObserver_);
    }
    highContrastObserver_ = nullptr;
}

void AceContainer::DistributeIntentInfo(const std::string& intentInfoSerialized, bool isColdStart,
    const std::function<void()>&& loadPageCallback)
{
    // set router intent info
    auto front = GetFrontend();
    CHECK_NULL_VOID(front);
    front->SetRouterIntentInfo(intentInfoSerialized, isColdStart, std::move(loadPageCallback));
    // set navigation intent info
    auto context = AceType::DynamicCast<NG::PipelineContext>(pipelineContext_);
    CHECK_NULL_VOID(context);
    auto navigationManager = context->GetNavigationManager();
    CHECK_NULL_VOID(navigationManager);
    navigationManager->SetNavigationIntentInfo(intentInfoSerialized, isColdStart);
}

UIContentErrorCode AceContainer::RunIntentPage()
{
    auto front = GetFrontend();
    CHECK_NULL_RETURN(front, UIContentErrorCode::NULL_POINTER);
    return front->RunIntentPage();
}
} // namespace OHOS::Ace::Platform
