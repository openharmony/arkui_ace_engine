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

#include "adapter/ohos/entrance/ui_content_impl.h"

#include <atomic>
#include <cinttypes>

#include "ability_context.h"
#include "ability_info.h"
#include "configuration.h"
#include "dm/display_manager.h"
#include "init_data.h"
#include "ipc_skeleton.h"
#include "js_runtime_utils.h"
#include "locale_config.h"
#include "native_reference.h"
#include "service_extension_context.h"
#include "wm_common.h"

#include "base/log/log_wrapper.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/transaction/rs_transaction.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/dialog_container.h"
#include "adapter/ohos/entrance/file_asset_provider.h"
#include "adapter/ohos/entrance/form_utils_impl.h"
#include "adapter/ohos/entrance/hap_asset_provider.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "adapter/ohos/osal/page_url_checker_ohos.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"
#include "base/geometry/rect.h"
#include "base/i18n/localization.h"
#include "base/log/ace_checker.h"
#include "base/log/ace_performance_check.h"
#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/perfmonitor/perf_monitor.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/common/flutter/flutter_asset_manager.h"
#include "core/common/resource/resource_manager.h"
#include "core/image/image_file_cache.h"
#ifdef FORM_SUPPORTED
#include "core/common/form_manager.h"
#endif
#include "core/common/layout_inspector.h"
#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif
#include "core/pipeline_ng/pipeline_context.h"
#ifdef NG_BUILD
#include "frameworks/bridge/declarative_frontend/ng/declarative_frontend_ng.h"
#endif

namespace OHOS::Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string START_PARAMS_KEY = "__startParams";
const std::string ACTION_VIEWDATA = "ohos.want.action.viewData";

} // namespace

static std::atomic<int32_t> gInstanceId = 0;
static std::atomic<int32_t> gSubWindowInstanceId = 100000;
static std::atomic<int32_t> gSubInstanceId = 1000000;
const std::string SUBWINDOW_PREFIX = "ARK_APP_SUBWINDOW_";
const std::string SUBWINDOW_TOAST_DIALOG_PREFIX = "ARK_APP_SUBWINDOW_TOAST_DIALOG_";
const int32_t REQUEST_CODE = -1;

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

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    LOGI("Ace lib loaded, CreateUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateFormContent(void* context, void* runtime, bool isCard)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Ace lib loaded, CreateFormUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime, isCard);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    TAG_LOGI(AceLogTag::ACE_SUB_WINDOW, "Ace lib loaded, Create SubWindowUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

class OccupiedAreaChangeListener : public OHOS::Rosen::IOccupiedAreaChangeListener {
public:
    explicit OccupiedAreaChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~OccupiedAreaChangeListener() = default;

    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
        const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
    {
        auto rect = info->rect_;
        auto type = info->type_;
        Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        LOGI("UIContent OccupiedAreaChange rect:%{public}s type: %{public}d", keyboardRect.ToString().c_str(), type);
        if (type == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT) {
            auto container = Platform::AceContainer::GetContainer(instanceId_);
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            ContainerScope scope(instanceId_);
            taskExecutor->PostTask(
                [container, keyboardRect, rsTransaction] {
                    auto context = container->GetPipelineContext();
                    CHECK_NULL_VOID(context);
                    context->OnVirtualKeyboardAreaChange(keyboardRect, rsTransaction);
                },
                TaskExecutor::TaskType::UI);
        }
    }

private:
    int32_t instanceId_ = -1;
};

class AvoidAreaChangedListener : public OHOS::Rosen::IAvoidAreaChangedListener {
public:
    explicit AvoidAreaChangedListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~AvoidAreaChangedListener() = default;

    void OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type) override
    {
        LOGI("UIContent OnAvoidAreaChanged type:%{public}d, topRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height%{public}d; bottomRect: avoidArea:x:%{public}d, y:%{public}d, "
             "width:%{public}d, height%{public}d",
            type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
            (int32_t)avoidArea.topRect_.height_, avoidArea.bottomRect_.posX_, avoidArea.bottomRect_.posY_,
            (int32_t)avoidArea.bottomRect_.width_, (int32_t)avoidArea.bottomRect_.height_);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto pipeline = container->GetPipelineContext();
        CHECK_NULL_VOID(pipeline);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto safeArea = ConvertAvoidArea(avoidArea);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [pipeline, safeArea, type] {
                if (type == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM) {
                    pipeline->UpdateSystemSafeArea(safeArea);
                } else if (type == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT) {
                    pipeline->UpdateCutoutSafeArea(safeArea);
                }
            },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

class DragWindowListener : public OHOS::Rosen::IWindowDragListener {
public:
    explicit DragWindowListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~DragWindowListener() = default;
    void OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
    {
        TAG_LOGI(AceLogTag::ACE_DRAG, "DragWindowListener::OnDrag called.");
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        int32_t instanceId = instanceId_;
        if (container->IsSubContainer()) {
            instanceId = container->GetParentId();
        }
        auto aceView = static_cast<Platform::AceViewOhos*>(Platform::AceContainer::GetContainer(instanceId)->GetView());
        CHECK_NULL_VOID(aceView);
        DragEventAction action;
        switch (event) {
            case OHOS::Rosen::DragEvent::DRAG_EVENT_END:
                action = DragEventAction::DRAG_EVENT_END;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_OUT:
                action = DragEventAction::DRAG_EVENT_OUT;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_MOVE:
                action = DragEventAction::DRAG_EVENT_MOVE;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_IN:
            default:
                action = DragEventAction::DRAG_EVENT_START;
                break;
        }
#ifndef ENABLE_DRAG_FRAMEWORK
        aceView->ProcessDragEvent(x, y, action);
#endif // ENABLE_DRAG_FRAMEWORK
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
        LOGI("window is touching outside. instance id is %{public}d", instanceId_);
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(instanceId_);
        taskExecutor->PostTask(
            [instanceId = instanceId_] {
                SubwindowManager::GetInstance()->ClearMenu();
                SubwindowManager::GetInstance()->ClearMenuNG(instanceId, false, true);
                SubwindowManager::GetInstance()->HidePopupNG(-1, instanceId);
            },
            TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime) : runtime_(runtime)
{
    CHECK_NULL_VOID(context);
    context_ = context->weak_from_this();
    LOGI("Create UIContentImpl successfully.");
}

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime, bool isCard)
    : runtime_(runtime), isFormRender_(isCard)
{
    CHECK_NULL_VOID(context);
    bundleName_ = context->GetBundleName();
    auto hapModuleInfo = context->GetHapModuleInfo();
    CHECK_NULL_VOID(hapModuleInfo);
    moduleName_ = hapModuleInfo->name;
    hapPath_ = hapModuleInfo->hapPath;
    isBundle_ = (hapModuleInfo->compileMode == AppExecFwk::CompileMode::JS_BUNDLE);
    SetConfiguration(context->GetConfiguration());
    context_ = context->weak_from_this();
    TAG_LOGI(AceLogTag::ACE_FORM, "Create form UIContentImpl successfully.");
}

UIContentImpl::UIContentImpl(OHOS::AppExecFwk::Ability* ability)
{
    CHECK_NULL_VOID(ability);
    context_ = ability->GetAbilityContext();
    LOGI("Create UIContentImpl successfully.");
}

void UIContentImpl::DestroyUIDirector()
{
#ifndef NG_BUILD
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
#ifdef ENABLE_ROSEN_BACKEND
    auto rsUIDirector = pipelineContext->GetRSUIDirector();
    CHECK_NULL_VOID(rsUIDirector);
    LOGI("Destroying old rsUIDirectory");
    rsUIDirector->Destroy();
#endif
#endif
}

void UIContentImpl::DestroyCallback() const
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(nullptr);
}

void UIContentImpl::InitializeInner(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage, bool isNamedRouter)
{
    if (window && StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
        CommonInitialize(window, contentInfo, storage);
        return;
    }
    if (window) {
        CommonInitialize(window, contentInfo, storage);
    }

    // ArkTSCard need no window : 梳理所有需要window和不需要window的场景
    if (isFormRender_ && !window) {
        LOGI("CommonInitializeForm url = %{public}s", contentInfo.c_str());
        CommonInitializeForm(window, contentInfo, storage);
    }

    LOGI("Initialize startUrl = %{public}s", startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "", isNamedRouter);
    LOGD("Initialize UIContentImpl done.");
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

void UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url, napi_value storage)
{
    InitializeInner(window, url, storage, false);
}

void UIContentImpl::InitializeByName(OHOS::Rosen::Window* window, const std::string& name, napi_value storage)
{
    InitializeInner(window, name, storage, true);
}

void UIContentImpl::Initialize(
    OHOS::Rosen::Window* window, const std::string& url, napi_value storage, uint32_t focusWindowId)
{
    if (window) {
        CommonInitialize(window, url, storage);
    }
    if (focusWindowId != 0) {
        LOGI("UIExtension host window id:%{public}u", focusWindowId);
        Platform::AceContainer::GetContainer(instanceId_)->SetFocusWindowId(focusWindowId);
    }

    LOGI("UIExtension startUrl = %{public}s", startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
    auto distributedUI = std::make_shared<NG::DistributedUI>();
    uiManager_ = std::make_unique<DistributedUIManager>(instanceId_, distributedUI);
    Platform::AceContainer::GetContainer(instanceId_)->SetDistributedUI(distributedUI);
}

napi_value UIContentImpl::GetUINapiContext()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    ContainerScope scope(instanceId_);
    napi_value result = nullptr;
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, result);
    if (frontend->GetType() == FrontendType::DECLARATIVE_JS) {
#ifdef NG_BUILD
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontendNG>(frontend);
#else
        auto declarativeFrontend = AceType::DynamicCast<DeclarativeFrontend>(frontend);
#endif
        CHECK_NULL_RETURN(declarativeFrontend, result);
        return declarativeFrontend->GetContextValue();
    }

    return result;
}

void UIContentImpl::Restore(OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    CommonInitialize(window, contentInfo, storage);
    startUrl_ = Platform::AceContainer::RestoreRouterStack(instanceId_, contentInfo);
    if (startUrl_.empty()) {
        LOGW("UIContent Restore start url is empty");
    }
    LOGI("Restore startUrl = %{public}s", startUrl_.c_str());
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
}

std::string UIContentImpl::GetContentInfo() const
{
    LOGI("UIContent GetContentInfo");
    return Platform::AceContainer::GetContentInfo(instanceId_);
}

// ArkTSCard start
void UIContentImpl::CommonInitializeForm(
    OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "Initialize CommonInitializeForm start.");
    ACE_FUNCTION_TRACE();
    window_ = window;
    startUrl_ = contentInfo;

    if (window_) {
        if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
            InitializeSubWindow(window_, true);
            return;
        }
        if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_PREFIX)) {
            InitializeSubWindow(window_);
            return;
        }
    }

    auto context = context_.lock();
    static std::once_flag onceFlag;
    if (!isFormRender_) {
        std::call_once(onceFlag, [&context]() {
            LOGD("Initialize for current process.");
            SetHwIcuDirectory();
            Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
            AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
            AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
            AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
            AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
            AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingPid());
            CapabilityRegistry::Register();
            ImageFileCache::GetInstance().SetImageCacheFilePath(context->GetCacheDir());
            ImageFileCache::GetInstance().SetCacheFileInfo();
        });
    }

    bool useNewPipe = true;
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        LOGD("UIContent: deviceWidth: %{public}d, deviceHeight: %{public}d, default density: %{public}f", deviceWidth,
            deviceHeight, density);
    }

    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    if (context) {
        auto resourceManager = context->GetResourceManager();
        if (resourceManager != nullptr) {
            resourceManager->GetResConfig(*resConfig);
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
                SystemProperties::SetColorMode(ColorMode::DARK);
                LOGI("UIContent set dark mode");
            } else {
                SystemProperties::SetColorMode(ColorMode::LIGHT);
                LOGI("UIContent set light mode");
            }
            SystemProperties::SetDeviceAccess(
                resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
        }
    }

    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
    } else {
        auto extensionContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
        if (extensionContext) {
            info = extensionContext->GetAbilityInfo();
        } else {
            LOGE("context is not AbilityContext or ExtensionContext.");
        }
    }
    if (info) {
        AceApplicationInfo::GetInstance().SetAbilityName(info->name);
    }

    RefPtr<FlutterAssetManager> flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context != nullptr ? context->GetApplicationInfo() : nullptr;
    auto hapModuleInfo = context != nullptr ? context->GetHapModuleInfo() : nullptr;
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    std::string resPath;
    std::string pageProfile;
    LOGI("Initialize UIContent isModelJson:%{public}s", isModelJson ? "true" : "false");
    if (isFormRender_) {
        TAG_LOGD(AceLogTag::ACE_FORM, "Initialize UIContent form assetProvider");
        std::vector<std::string> basePaths;
        basePaths.emplace_back("assets/js/" + moduleName_ + "/");
        basePaths.emplace_back("assets/js/share/");
        basePaths.emplace_back("");
        basePaths.emplace_back("js/");
        basePaths.emplace_back("ets/");
        auto assetProvider = CreateAssetProvider(hapPath_, basePaths, false);
        if (assetProvider) {
            LOGE("push card asset provider to queue.");
            flutterAssetManager->PushBack(std::move(assetProvider));
        }
    } else {
        if (isModelJson) {
            std::string hapPath = info != nullptr ? info->hapPath : "";
            LOGD("hapPath:%{public}s", hapPath.c_str());
            // first use hap provider
            if (flutterAssetManager && !hapPath.empty()) {
                auto assetProvider = AceType::MakeRefPtr<HapAssetProvider>();
                if (assetProvider->Initialize(hapPath, { "", "ets/", "resources/base/profile/" })) {
                    LOGD("Push HapAssetProvider to queue.");
                    flutterAssetManager->PushBack(std::move(assetProvider));
                }
            }

            if (appInfo) {
                std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
                for (const auto& module : moduleList) {
                    if (module.moduleName == moduleName) {
                        std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                        auto moduleSourceDir =
                            std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                        resPath = moduleSourceDir + "/";
                        break;
                    }
                }
            }

            // second use file provider, will remove later
            LOGD("In stage mode, resPath:%{private}s", resPath.c_str());
            auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
            if (flutterAssetManager && !resPath.empty()) {
                auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
                if (assetProvider->Initialize(resPath, assetBasePathStr)) {
                    LOGD("Push AssetProvider to queue.");
                    flutterAssetManager->PushBack(std::move(assetProvider));
                }
            }

            if (hapModuleInfo) {
                pageProfile = hapModuleInfo->pages;
                const std::string profilePrefix = "$profile:";
                if (pageProfile.compare(0, profilePrefix.size(), profilePrefix) == 0) {
                    pageProfile = pageProfile.substr(profilePrefix.length()).append(".json");
                }
                LOGD("In stage mode, pageProfile:%{public}s", pageProfile.c_str());
            } else {
                LOGE("In stage mode, can't get hap info.");
            }
        } else {
            auto packagePathStr = context->GetBundleCodeDir();
            if (hapModuleInfo != nullptr) {
                packagePathStr += "/" + hapModuleInfo->package + "/";
            }
            std::string srcPath = "";
            if (info != nullptr && !info->srcPath.empty()) {
                srcPath = info->srcPath;
            }

            auto assetBasePathStr = { "assets/js/" + (srcPath.empty() ? "default" : srcPath) + "/",
                std::string("assets/js/share/") };

            if (flutterAssetManager && !packagePathStr.empty()) {
                auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
                if (assetProvider->Initialize(packagePathStr, assetBasePathStr)) {
                    LOGD("Push AssetProvider to queue.");
                    flutterAssetManager->PushBack(std::move(assetProvider));
                }
            }

            if (appInfo) {
                std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
                for (const auto& module : moduleList) {
                    if (module.moduleName == moduleName) {
                        std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                        auto moduleSourceDir =
                            std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                        resPath = moduleSourceDir + "/assets/" + module.moduleName + "/";
                        break;
                    }
                }
            }
        }
    }

    std::string hapPath; // hap path in sandbox
    if (!moduleHapPath.empty()) {
        if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
            hapPath = moduleHapPath;
        } else {
            auto pos = moduleHapPath.find_last_of('/');
            if (pos != std::string::npos) {
                hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
                LOGD("In Stage mode, hapPath:%{private}s", hapPath.c_str());
            }
        }
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(nullptr, pluginUtils);
#endif
    // create container
    if (runtime_) {
        instanceId_ = gInstanceId.fetch_add(1, std::memory_order_relaxed);
    } else {
        instanceId_ = gSubWindowInstanceId.fetch_add(1, std::memory_order_relaxed);
    }
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
    auto container =
        AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, context_, info,
            std::make_unique<ContentEventCallback>(
                [window = window_] {
                    CHECK_NULL_VOID(window);
                    window->PerformBack();
                },
                [context = context_](const std::string& address) {
                    auto sharedContext = context.lock();
                    CHECK_NULL_VOID(sharedContext);
                    auto abilityContext =
                        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                    CHECK_NULL_VOID(abilityContext);
                    LOGI("start ability with url = %{private}s", address.c_str());
                    AAFwk::Want want;
                    want.AddEntity(Want::ENTITY_BROWSER);
                    want.SetUri(address);
                    want.SetAction(ACTION_VIEWDATA);
                    abilityContext->StartAbility(want, REQUEST_CODE);
                }),
            false, false, useNewPipe);

    CHECK_NULL_VOID(container);
    container->SetIsFormRender(isFormRender_);
    container->SetIsFRSCardContainer(isFormRender_);
    if (window_) {
        container->SetWindowName(window_->GetWindowName());
        container->SetWindowId(window_->GetWindowId());
    }

    if (context) {
        auto token = context->GetToken();
        container->SetToken(token);
    }

    // Mark the relationship between windowId and containerId, it is 1:1
    if (window) {
        SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    }
    AceEngine::Get().AddContainer(instanceId_, container);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetPageProfile(pageProfile);
    container->Initialize();
    ContainerScope scope(instanceId_);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(container);
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
    aceResCfg.SetColorMode(SystemProperties::GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    if (isFormRender_) {
        resPath = "/data/bundles/" + bundleName_ + "/" + moduleName_ + "/";
        hapPath = hapPath_;
    }
    TAG_LOGI(AceLogTag::ACE_FORM, "CommonInitializeForm resPath = %{public}s hapPath = %{public}s", resPath.c_str(),
        hapPath.c_str());
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    container->SetAssetManager(flutterAssetManager);
    if (!isFormRender_) {
        container->SetBundlePath(context->GetBundleCodeDir());
        container->SetFilesDataPath(context->GetFilesDir());
    }

    if (window_) {
        if (window_->IsDecorEnable()) {
            LOGD("Container modal is enabled.");
            container->SetWindowModal(WindowModal::CONTAINER_MODAL);
        }

        dragWindowListener_ = new DragWindowListener(instanceId_);
        window_->RegisterDragListener(dragWindowListener_);
        occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
        window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
    }

    // create ace_view
    Platform::AceViewOhos* aceView = nullptr;
    if (isFormRender_) {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, true, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    } else {
        aceView = Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
        Platform::AceViewOhos::SurfaceCreated(aceView, window_);
    }

    if (isFormRender_) {
        LOGD("Platform AceContainer SetViewNew is card formWidth=%{public}f, formHeight=%{public}f", formWidth_,
            formHeight_);
        Platform::AceContainer::SetViewNew(aceView, density, formWidth_, formHeight_, window_);
        auto frontend = AceType::DynamicCast<FormFrontendDeclarative>(container->GetFrontend());
        CHECK_NULL_VOID(frontend);
        frontend->SetBundleName(bundleName_);
        frontend->SetModuleName(moduleName_);
        // arkTSCard only support "esModule" compile mode
        frontend->SetIsBundle(false);
    } else {
        Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
    }

    // after frontend initialize
    if (window_ && window_->IsFocused()) {
        LOGD("UIContentImpl: focus again");
        Focus();
    }

    if (isFormRender_ && !isFormRenderInit_) {
        container->UpdateFormSharedImage(formImageDataMap_);
        container->UpdateFormData(formData_);
        isFormRenderInit_ = true;
    }

    if (isFormRender_) {
        Platform::AceViewOhos::SurfaceChanged(aceView, formWidth_, formHeight_, deviceHeight >= deviceWidth ? 0 : 1);
        // Set sdk version in module json mode for form
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            LOGD("SetMinPlatformVersion is %{public}d", appInfo->apiCompatibleVersion);
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    } else {
        Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    }
    // Set sdk version in module json mode
    if (isModelJson) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            LOGD("SetMinPlatformVersion is %{public}d", appInfo->apiCompatibleVersion);
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    }
    if (runtime_ && !isFormRender_) { // ArkTSCard not support inherit local strorage from context
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context->GetBindingObject()->Get<NativeReference>());
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(
                reinterpret_cast<NativeReference*>(ref), context->GetBindingObject()->Get<NativeReference>());
        }
    }
}

void UIContentImpl::SetConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (config == nullptr) {
        LOGW("config is nullptr, set localeInfo to default");
        UErrorCode status = U_ZERO_ERROR;
        icu::Locale locale = icu::Locale::forLanguageTag(Global::I18n::LocaleConfig::GetSystemLanguage(), status);
        AceApplicationInfo::GetInstance().SetLocale(locale.getLanguage(), locale.getCountry(), locale.getScript(), "");
        SystemProperties::SetColorMode(ColorMode::LIGHT);
        return;
    }

    LOGI("SetConfiguration");
    auto colorMode = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    auto deviceAccess = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    auto languageTag = config->GetItem(OHOS::AAFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    if (!colorMode.empty()) {
        LOGD("SetConfiguration colorMode: %{public}s", colorMode.c_str());
        if (colorMode == "dark") {
            SystemProperties::SetColorMode(ColorMode::DARK);
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
        }
    }

    if (!deviceAccess.empty()) {
        // Event of accessing mouse or keyboard
        LOGD("SetConfiguration deviceAccess: %{public}s", deviceAccess.c_str());
        SystemProperties::SetDeviceAccess(deviceAccess == "true");
    }

    if (!languageTag.empty()) {
        LOGD("SetConfiguration languageTag: %{public}s", languageTag.c_str());
        std::string language;
        std::string script;
        std::string region;
        Localization::ParseLocaleTag(languageTag, language, script, region, false);
        if (!language.empty() || !script.empty() || !region.empty()) {
            AceApplicationInfo::GetInstance().SetLocale(language, region, script, "");
        }
    }
}

std::shared_ptr<Rosen::RSSurfaceNode> UIContentImpl::GetFormRootNode()
{
    return Platform::AceContainer::GetFormSurfaceNode(instanceId_);
}
// ArkTSCard end

void UIContentImpl::CommonInitialize(OHOS::Rosen::Window* window, const std::string& contentInfo, napi_value storage)
{
    ACE_FUNCTION_TRACE();
    window_ = window;
    CHECK_NULL_VOID(window_);
    startUrl_ = contentInfo;
    if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_TOAST_DIALOG_PREFIX)) {
        InitializeSubWindow(window_, true);
        return;
    }
    if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_PREFIX)) {
        InitializeSubWindow(window_);
        return;
    }
    auto context = context_.lock();
    CHECK_NULL_VOID(context);
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&context]() {
        LOGD("Initialize for current process.");
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
        if (abilityContext) {
            int32_t missionId = -1;
            abilityContext->GetMissionId(missionId);
            AceApplicationInfo::GetInstance().SetMissionId(missionId);
        }
        AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
        AceApplicationInfo::GetInstance().SetApiTargetVersion(context->GetApplicationInfo()->apiTargetVersion);
        AceApplicationInfo::GetInstance().SetAppVersionName(context->GetApplicationInfo()->versionName);
        AceApplicationInfo::GetInstance().SetAppVersionCode(context->GetApplicationInfo()->versionCode);
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingPid());
        CapabilityRegistry::Register();
        ImageFileCache::GetInstance().SetImageCacheFilePath(context->GetCacheDir());
        ImageFileCache::GetInstance().SetCacheFileInfo();
    });
    AceNewPipeJudgement::InitAceNewPipeConfig();
    auto apiCompatibleVersion = context->GetApplicationInfo()->apiCompatibleVersion;
    auto apiReleaseType = context->GetApplicationInfo()->apiReleaseType;
    auto apiTargetVersion = context->GetApplicationInfo()->apiTargetVersion;
    const auto& hapModuleInfo = context->GetHapModuleInfo();
    std::vector<OHOS::AppExecFwk::Metadata> metaData;
    if (hapModuleInfo) {
        metaData = hapModuleInfo->metadata;
    }
    bool closeArkTSPartialUpdate = std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
        return metaDataItem.name == "ArkTSPartialUpdate" && metaDataItem.value == "false";
    });

    bool isDelayedUpdateOnInactive = std::any_of(metaData.begin(), metaData.end(), [](const auto& metaDataItem) {
        return metaDataItem.name == "delayedUpdateOnInactive" && metaDataItem.value == "true";
    });
    AceApplicationInfo::GetInstance().SetDelayedUpdateOnInactive(isDelayedUpdateOnInactive);

    auto useNewPipe =
        AceNewPipeJudgement::QueryAceNewPipeEnabledStage(AceApplicationInfo::GetInstance().GetPackageName(),
            apiCompatibleVersion, apiTargetVersion, apiReleaseType, closeArkTSPartialUpdate);
    LOGI("UIContent: apiCompatibleVersion: %{public}d, apiTargetVersion: %{public}d, and apiReleaseType: %{public}s, "
         "useNewPipe: %{public}d, isDelayedUpdateOnInactive: %{public}d",
        apiCompatibleVersion, apiTargetVersion, apiReleaseType.c_str(), useNewPipe, isDelayedUpdateOnInactive);
#ifndef NG_BUILD
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector) {
            rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
            rsUiDirector->SetCacheDir(context->GetCacheDir());
            rsUiDirector->Init();
        }
    }
#endif
#endif
    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    int32_t devicePhysicalWidth = 0;
    int32_t devicePhysicalHeight = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        devicePhysicalWidth = defaultDisplay->GetPhysicalWidth();
        devicePhysicalHeight = defaultDisplay->GetPhysicalHeight();
        LOGD("UIContent: deviceWidth: %{public}d, deviceHeight: %{public}d, devicePhysicalWidth=%{public}d, "
             "devicePhysicalHeight=%{public}d, default density: %{public}f",
            deviceWidth, deviceHeight, devicePhysicalWidth, devicePhysicalHeight, density);
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
    SystemProperties::SetDevicePhysicalWidth(devicePhysicalWidth);
    SystemProperties::SetDevicePhysicalHeight(devicePhysicalHeight);
    // Initialize performance check parameters
    AceChecker::InitPerformanceParameters();
    AcePerformanceCheck::Start();
    SystemProperties::SetColorMode(ColorMode::LIGHT);

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    auto resourceManager = context->GetResourceManager();
    if (resourceManager != nullptr) {
        resourceManager->GetResConfig(*resConfig);
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
            SystemProperties::SetColorMode(ColorMode::DARK);
            LOGD("UIContent set dark mode");
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
            LOGD("UIContent set light mode");
        }
        SystemProperties::SetDeviceAccess(
            resConfig->GetInputDevice() == Global::Resource::InputDevice::INPUTDEVICE_POINTINGDEVICE);
    }

    auto abilityContext = OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(context);
    std::shared_ptr<OHOS::AppExecFwk::AbilityInfo> info;
    if (abilityContext) {
        info = abilityContext->GetAbilityInfo();
    } else {
        auto extensionContext =
            OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::ExtensionContext>(context);
        if (!extensionContext) {
            LOGE("context is not AbilityContext or ExtensionContext.");
            return;
        }
        info = extensionContext->GetAbilityInfo();
    }
    if (info) {
        AceApplicationInfo::GetInstance().SetAbilityName(info->name);
    }

    RefPtr<FlutterAssetManager> flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context->GetApplicationInfo();
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string moduleHapPath = info != nullptr ? info->hapPath : "";
    std::string resPath;
    std::string pageProfile;
    LOGI("Initialize UIContent isModelJson:%{public}s", isModelJson ? "true" : "false");
    if (isModelJson) {
        std::string hapPath = info != nullptr ? info->hapPath : "";
        LOGD("hapPath:%{public}s", hapPath.c_str());
        // first use hap provider
        if (flutterAssetManager && !hapPath.empty()) {
            auto assetProvider = AceType::MakeRefPtr<HapAssetProvider>();
            if (assetProvider->Initialize(hapPath, { "", "ets/", "resources/base/profile/" })) {
                LOGD("Push HapAssetProvider to queue.");
                flutterAssetManager->PushBack(std::move(assetProvider));
            }
        }

        if (appInfo) {
            std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
            for (const auto& module : moduleList) {
                if (module.moduleName == moduleName) {
                    std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                    auto moduleSourceDir = std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                    resPath = moduleSourceDir + "/";
                    break;
                }
            }
        }

        // second use file provider, will remove later
        LOGD("In stage mode, resPath:%{private}s", resPath.c_str());
        auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
        if (flutterAssetManager && !resPath.empty()) {
            auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
            if (assetProvider->Initialize(resPath, assetBasePathStr)) {
                LOGD("Push AssetProvider to queue.");
                flutterAssetManager->PushBack(std::move(assetProvider));
            }
        }

        if (hapModuleInfo) {
            pageProfile = hapModuleInfo->pages;
            const std::string profilePrefix = "$profile:";
            if (pageProfile.compare(0, profilePrefix.size(), profilePrefix) == 0) {
                pageProfile = pageProfile.substr(profilePrefix.length()).append(".json");
            }
            LOGD("In stage mode, pageProfile:%{public}s", pageProfile.c_str());
        } else {
            LOGE("In stage mode, can't get hap info.");
        }
    } else {
        auto packagePathStr = context->GetBundleCodeDir();
        if (hapModuleInfo != nullptr) {
            packagePathStr += "/" + hapModuleInfo->package + "/";
        }
        std::string srcPath = "";
        if (info != nullptr && !info->srcPath.empty()) {
            srcPath = info->srcPath;
        }

        auto assetBasePathStr = { "assets/js/" + (srcPath.empty() ? "default" : srcPath) + "/",
            std::string("assets/js/share/") };

        if (flutterAssetManager && !packagePathStr.empty()) {
            auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
            if (assetProvider->Initialize(packagePathStr, assetBasePathStr)) {
                LOGD("Push AssetProvider to queue.");
                flutterAssetManager->PushBack(std::move(assetProvider));
            }
        }

        if (appInfo) {
            std::vector<OHOS::AppExecFwk::ModuleInfo> moduleList = appInfo->moduleInfos;
            for (const auto& module : moduleList) {
                if (module.moduleName == moduleName) {
                    std::regex pattern(ABS_BUNDLE_CODE_PATH + bundleName + FILE_SEPARATOR);
                    auto moduleSourceDir = std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
                    resPath = moduleSourceDir + "/assets/" + module.moduleName + "/";
                    break;
                }
            }
        }
    }

    std::string hapPath; // hap path in sandbox
    if (!moduleHapPath.empty()) {
        if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
            hapPath = moduleHapPath;
        } else {
            auto pos = moduleHapPath.find_last_of('/');
            if (pos != std::string::npos) {
                hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
                LOGD("In Stage mode, hapPath:%{private}s", hapPath.c_str());
            }
        }
    }

#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(nullptr, pluginUtils);
#endif
    // create container
    if (runtime_) {
        instanceId_ = gInstanceId.fetch_add(1, std::memory_order_relaxed);
    } else {
        instanceId_ = gSubWindowInstanceId.fetch_add(1, std::memory_order_relaxed);
    }
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
    auto container =
        AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, context_, info,
            std::make_unique<ContentEventCallback>(
                [window = window_] {
                    CHECK_NULL_VOID(window);
                    window->PerformBack();
                },
                [context = context_](const std::string& address) {
                    auto sharedContext = context.lock();
                    CHECK_NULL_VOID(sharedContext);
                    auto abilityContext =
                        OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                    CHECK_NULL_VOID(abilityContext);
                    LOGI("start ability with url = %{private}s", address.c_str());
                    AAFwk::Want want;
                    want.AddEntity(Want::ENTITY_BROWSER);
                    want.SetUri(address);
                    want.SetAction(ACTION_VIEWDATA);
                    abilityContext->StartAbility(want, REQUEST_CODE);
                }),
            false, false, useNewPipe);
    CHECK_NULL_VOID(container);
    container->SetWindowName(window_->GetWindowName());
    container->SetWindowId(window_->GetWindowId());
    auto token = context->GetToken();
    container->SetToken(token);
    container->SetPageUrlChecker(AceType::MakeRefPtr<PageUrlCheckerOhos>(context, info));
    // Mark the relationship between windowId and containerId, it is 1:1
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    if (runtime_) {
        container->GetSettings().SetUsingSharedRuntime(true);
        container->SetSharedRuntime(runtime_);
    } else {
        container->GetSettings().SetUsingSharedRuntime(false);
    }
    container->SetPageProfile(pageProfile);
    container->Initialize();
    ContainerScope scope(instanceId_);
    auto front = container->GetFrontend();
    if (front) {
        front->UpdateState(Frontend::State::ON_CREATE);
        front->SetJsMessageDispatcher(container);
    }
    auto aceResCfg = container->GetResourceConfiguration();
    aceResCfg.SetOrientation(SystemProperties::GetDeviceOrientation());
    aceResCfg.SetDensity(SystemProperties::GetResolution());
    aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
    aceResCfg.SetColorMode(SystemProperties::GetColorMode());
    aceResCfg.SetDeviceAccess(SystemProperties::GetDeviceAccess());
    container->SetResourceConfiguration(aceResCfg);
    container->SetPackagePathStr(resPath);
    container->SetHapPath(hapPath);
    container->SetAssetManager(flutterAssetManager);
    container->SetBundlePath(context->GetBundleCodeDir());
    container->SetFilesDataPath(context->GetFilesDir());
    container->SetModuleName(hapModuleInfo->moduleName);
    container->SetIsModule(hapModuleInfo->compileMode == AppExecFwk::CompileMode::ES_MODULE);
    // for atomic service
    container->SetInstallationFree(hapModuleInfo && hapModuleInfo->installationFree);
    if (hapModuleInfo->installationFree) {
        container->SetSharePanelCallback(
            [context = context_](const std::string& bundleName, const std::string& abilityName) {
                auto sharedContext = context.lock();
                CHECK_NULL_VOID(sharedContext);
                auto abilityContext =
                    OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
                CHECK_NULL_VOID(abilityContext);
                auto abilityInfo = abilityContext->GetAbilityInfo();
                AAFwk::Want want;
                want.SetParam("abilityName", abilityInfo->name);
                want.SetParam("bundleName", abilityInfo->bundleName);
                want.SetParam("moduleName", abilityInfo->moduleName);
                want.SetParam("hostPkgName", abilityInfo->bundleName);
                want.SetElementName(bundleName, abilityName);
                abilityContext->StartAbility(want, REQUEST_CODE);
            });
    }

    if (window_->IsDecorEnable()) {
        LOGD("Container modal is enabled.");
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
    window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);

    // create ace_view
    auto aceView =
        Platform::AceViewOhos::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
    Platform::AceViewOhos::SurfaceCreated(aceView, window_);
#ifndef NG_BUILD
    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [window, id = instanceId_, container, aceView, rsUiDirector](
                       const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) {
            if (rsUiDirector) {
                ACE_SCOPED_TRACE("OHOS::Rosen::RSUIDirector::Create()");
                rsUiDirector->SetUITaskRunner(
                    [taskExecutor = container->GetTaskExecutor(), id](const std::function<void()>& task) {
                        ContainerScope scope(id);
                        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
                    });
                auto context = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
                if (context != nullptr) {
                    context->SetRSUIDirector(rsUiDirector);
                }
                LOGD("UIContent Init Rosen Backend");
            }
        };
#endif
        // set view
        Platform::AceContainer::SetView(aceView, density, 0, 0, window_, callback);
    } else {
        Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
    }
#else
    Platform::AceContainer::SetViewNew(aceView, density, 0, 0, window_);
#endif

    // after frontend initialize
    if (window_->IsFocused()) {
        LOGI("UIContentImpl: focus again");
        Focus();
    }

    Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    auto pipeline = container->GetPipelineContext();
    // Use metadata to control the center-alignment of text at line height.
    bool halfLeading = std::any_of(metaData.begin(), metaData.end(),
        [](const auto& metaDataItem) { return metaDataItem.name == "half_leading" && metaDataItem.value == "true"; });
    pipeline->SetHalfLeading(halfLeading);
    if (pipeline) {
        auto rsConfig = window_->GetKeyboardAnimationConfig();
        KeyboardAnimationConfig config = { rsConfig.curveType_, rsConfig.curveParams_, rsConfig.durationIn_,
            rsConfig.durationOut_ };
        pipeline->SetKeyboardAnimationConfig(config);
    }
    // Set sdk version in module json mode
    if (isModelJson) {
        if (pipeline && appInfo) {
            LOGI("SetMinPlatformVersion is %{public}d", appInfo->apiCompatibleVersion);
            pipeline->SetMinPlatformVersion(appInfo->apiCompatibleVersion);
        }
    }
    if (runtime_) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context->GetBindingObject()->Get<NativeReference>());
        } else {
            auto env = reinterpret_cast<napi_env>(nativeEngine);
            napi_ref ref = nullptr;
            napi_create_reference(env, storage, 1, &ref);
            container->SetLocalStorage(
                reinterpret_cast<NativeReference*>(ref), context->GetBindingObject()->Get<NativeReference>());
        }
    }

    InitializeSafeArea(container);

    // set container temp dir
    if (abilityContext) {
        if (!abilityContext->GetTempDir().empty()) {
            container->SetTempDir(abilityContext->GetTempDir());
        }
    } else {
        LOGI("UIContentImpl::OnStart abilityContext is null");
    }

    LayoutInspector::SetCallback(instanceId_);
}

void UIContentImpl::InitializeSafeArea(const RefPtr<Platform::AceContainer>& container)
{
    constexpr static int32_t PLATFORM_VERSION_TEN = 10;
    auto pipeline = container->GetPipelineContext();
    if (pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow()) {
        avoidAreaChangedListener_ = new AvoidAreaChangedListener(instanceId_);
        window_->RegisterAvoidAreaChangeListener(avoidAreaChangedListener_);
        pipeline->UpdateSystemSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_SYSTEM));
        pipeline->UpdateCutoutSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_CUTOUT));
    }
}

void UIContentImpl::Foreground()
{
    LOGI("UIContentImpl: window foreground");
    Platform::AceContainer::OnShow(instanceId_);
    // set the flag isForegroundCalled to be true
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetForegroundCalled(true);
}

void UIContentImpl::Background()
{
    LOGI("UIContentImpl: window background");
    Platform::AceContainer::OnHide(instanceId_);
}

void UIContentImpl::ReloadForm(const std::string& url)
{
    startUrl_ = url;
    LOGI("ReloadForm startUrl = %{public}s", startUrl_.c_str());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto flutterAssetManager = AceType::DynamicCast<FlutterAssetManager>(container->GetAssetManager());
    flutterAssetManager->ReloadProvider();
    container->UpdateResource();
    Platform::AceContainer::RunPage(instanceId_, startUrl_, "");
}

void UIContentImpl::Focus()
{
    LOGI("UIContentImpl: window focus");
    Platform::AceContainer::OnActive(instanceId_);
}

void UIContentImpl::UnFocus()
{
    LOGI("UIContentImpl: window unFocus");
    Platform::AceContainer::OnInactive(instanceId_);
}

void UIContentImpl::Destroy()
{
    LOGI("UIContentImpl: window destroy");

    if (isFormRender_) {
        LOGD("Remove card for bundle %{public}s, module %{public}s", bundleName_.c_str(), moduleName_.c_str());
        ResourceManager::GetInstance().RemoveResourceAdapter(bundleName_, moduleName_);
    }

    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    // stop performance check and output json file
    AcePerformanceCheck::Stop();
    if (AceType::InstanceOf<Platform::DialogContainer>(container)) {
        Platform::DialogContainer::DestroyContainer(instanceId_);
    } else {
        Platform::AceContainer::DestroyContainer(instanceId_);
    }
}

void UIContentImpl::OnNewWant(const OHOS::AAFwk::Want& want)
{
    LOGI("UIContent OnNewWant");
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(instanceId_, params);
}

uint32_t UIContentImpl::GetBackgroundColor()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
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

    LOGI("UIContentImpl GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}

void UIContentImpl::SetBackgroundColor(uint32_t color)
{
    LOGI("UIContentImpl: SetBackgroundColor color is %{public}u", color);
    auto container = AceEngine::Get().GetContainer(instanceId_);
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
    LOGI("UIContentImpl: ProcessBackPressed: Platform::AceContainer::OnBackPressed called");
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, false);
    bool ret = false;
    taskExecutor->PostSyncTask(
        [container, this, &ret]() {
            if (AceType::InstanceOf<Platform::DialogContainer>(container)) {
                if (Platform::DialogContainer::OnBackPressed(instanceId_)) {
                    LOGI("UIContentImpl ProcessBackPressed DialogContainer return true");
                    ret = true;
                }
            } else {
                LOGI("UIContentImpl ProcessBackPressed AceContainer");
                PerfMonitor::GetPerfMonitor()->RecordInputEvent(LAST_UP, UNKNOWN_SOURCE, 0);
                if (Platform::AceContainer::OnBackPressed(instanceId_)) {
                    LOGI("UIContentImpl ProcessBackPressed AceContainer return true");
                    ret = true;
                }
            }
        },
        TaskExecutor::TaskType::UI);
    return ret;
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(instanceId_));
    CHECK_NULL_RETURN(container, false);
    container->SetCurPointerEvent(pointerEvent);
    if (pointerEvent->GetPointerAction() != MMI::PointerEvent::POINTER_ACTION_MOVE) {
        auto info = Platform::AceContainer::GetContentInfo(instanceId_);
        TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "PointerEvent Process to ui_content, eventInfo: id:%{public}d, "
            "WindowName = %{public}s, WindowId = %{public}d, ViewWidth = %{public}d, ViewHeight = %{public}d, "
            "ViewPosX = %{public}d, ViewPosY = %{public}d, ContentInfo = %{public}s",
            pointerEvent->GetId(), container->GetWindowName().c_str(), container->GetWindowId(),
            container->GetViewWidth(), container->GetViewHeight(), container->GetViewPosX(),
            container->GetViewPosY(), info.c_str());
    }
    auto aceView = static_cast<Platform::AceViewOhos*>(container->GetView());
    Platform::AceViewOhos::DispatchTouchEvent(aceView, pointerEvent);
    return true;
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& touchEvent)
{
    TAG_LOGI(AceLogTag::ACE_INPUTTRACKING, "KeyEvent Process to ui_content, eventInfo: id:%{public}d, "
        "keyEvent info: keyCode is %{public}d, "
        "keyAction is %{public}d, keyActionTime is %{public}" PRId64,
        touchEvent->GetId(), touchEvent->GetKeyCode(), touchEvent->GetKeyAction(),
        touchEvent->GetActionTime());
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, false);
    auto aceView = static_cast<Platform::AceViewOhos*>(container->GetView());
    return Platform::AceViewOhos::DispatchKeyEvent(aceView, touchEvent);
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    LOGD("UIContentImpl ProcessAxisEvent");
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    LOGD("UIContentImpl ProcessVsyncEvent");
    return false;
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    LOGI("UIContentImpl: UpdateConfiguration called");
    CHECK_NULL_VOID(config);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weakContainer = WeakPtr<Platform::AceContainer>(container), config]() {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_VOID(container);
            Platform::ParsedConfig parsedConfig;
            parsedConfig.colorMode = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
            parsedConfig.deviceAccess = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
            parsedConfig.languageTag = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
            parsedConfig.direction = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DIRECTION);
            parsedConfig.densitydpi = config->GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DENSITYDPI);
            container->UpdateConfiguration(parsedConfig, config->GetName());
            LOGI("UIContentImpl: UpdateConfiguration called End, name:%{public}s", config->GetName().c_str());
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    LOGI("UIContentImpl: UpdateViewportConfig %{public}s", config.ToString().c_str());
    SystemProperties::SetResolution(config.Density());
    SystemProperties::SetDeviceOrientation(config.Orientation());
    ContainerScope scope(instanceId_);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto task = [config, container, reason, rsTransaction, rsWindow = window_]() {
        container->SetWindowPos(config.Left(), config.Top());
        auto pipelineContext = container->GetPipelineContext();
        if (pipelineContext) {
            pipelineContext->SetDisplayWindowRectInfo(
                Rect(Offset(config.Left(), config.Top()), Size(config.Width(), config.Height())));
            if (rsWindow) {
                pipelineContext->SetIsLayoutFullScreen(
                    rsWindow->GetMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN);
            }
            if (reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
                pipelineContext->FlushBuild();
            }
        }
        auto aceView = static_cast<Platform::AceViewOhos*>(container->GetAceView());
        CHECK_NULL_VOID(aceView);
        Platform::AceViewOhos::SetViewportMetrics(aceView, config);
        Platform::AceViewOhos::SurfaceChanged(aceView, config.Width(), config.Height(), config.Orientation(),
            static_cast<WindowSizeChangeReason>(reason), rsTransaction);
        Platform::AceViewOhos::SurfacePositionChanged(aceView, config.Left(), config.Top());
        if (reason == OHOS::Rosen::WindowSizeChangeReason::DRAG_START) {
            SubwindowManager::GetInstance()->ClearToastInSubwindow();
        }
    };
    if (container->IsUseStageModel() && reason == OHOS::Rosen::WindowSizeChangeReason::ROTATION) {
        task();
    } else {
        taskExecutor->PostTask(task, TaskExecutor::TaskType::PLATFORM);
    }
}

void UIContentImpl::SetIgnoreViewSafeArea(bool ignoreViewSafeArea)
{
    LOGI("UIContentImpl: SetIgnoreViewSafeArea:%{public}u", ignoreViewSafeArea);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto pipeline = container->GetPipelineContext();
    const static int32_t PLATFORM_VERSION_TEN = 10;
    CHECK_NULL_VOID(
        pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow());
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, ignoreSafeArea = ignoreViewSafeArea]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetIgnoreViewSafeArea(ignoreSafeArea);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateWindowMode(OHOS::Rosen::WindowMode mode, bool hasDeco)
{
    LOGI("UIContentImpl: UpdateWindowMode, window mode is %{public}d, hasDeco is %{public}d", mode, hasDeco);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, mode, hasDeco]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->ShowContainerTitle(mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING, hasDeco);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    LOGI("HideWindowTitleButton hideSplit: %{public}d, hideMaximize: %{public}d, hideMinimize: %{public}d", hideSplit,
        hideMaximize, hideMinimize);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, hideSplit, hideMaximize, hideMinimize]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetContainerButtonHide(hideSplit, hideMaximize, hideMinimize);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto ret = taskExecutor->PostSyncTaskTimeout(
        [&]() { container->Dump(params, info); }, TaskExecutor::TaskType::UI, 1500); // timeout 1.5s
    if (!ret) {
        LOGE("DumpInfo failed");
    }
}

void UIContentImpl::InitializeSubWindow(OHOS::Rosen::Window* window, bool isDialog)
{
    window_ = window;
    LOGI("The window name is %{public}s", window->GetWindowName().c_str());
    CHECK_NULL_VOID(window_);
    RefPtr<Container> container;
    instanceId_ = gSubInstanceId.fetch_add(1, std::memory_order_relaxed);

    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext;
    if (isDialog) {
        container = AceType::MakeRefPtr<Platform::DialogContainer>(instanceId_, FrontendType::DECLARATIVE_JS);
    } else {
#ifdef NG_BUILD
        container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
            runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                // Sub-window ,just return.
                LOGI("Content event callback");
            }),
            false, true, true);
#else
        if (Container::IsCurrentUseNewPipeline()) {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
                runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                    LOGI("Content event callback");
                }),
                false, true, true);
        } else {
            container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS,
                runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
                    // Sub-window ,just return.
                    LOGI("Content event callback");
                }),
                false, true);
        }
#endif
    }
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    touchOutsideListener_ = new TouchOutsideListener(instanceId_);
    window_->RegisterTouchOutsideListener(touchOutsideListener_);
    dragWindowListener_ = new DragWindowListener(instanceId_);
    window_->RegisterDragListener(dragWindowListener_);
    occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
    window_->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
}

void UIContentImpl::SetNextFrameLayoutCallback(std::function<void()>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetNextFrameLayoutCallback(std::move(callback));
}

void UIContentImpl::NotifyMemoryLevel(int32_t level)
{
    LOGI("Receive Memory level notification, level: %{public}d", level);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    pipelineContext->NotifyMemoryLevel(level);
}

void UIContentImpl::SetAppWindowTitle(const std::string& title)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    LOGI("set app title");
    pipelineContext->SetAppTitle(title);
}

void UIContentImpl::SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    LOGI("set app icon");
    pipelineContext->SetAppIcon(AceType::MakeRefPtr<PixelMapOhos>(pixelMap));
}

void UIContentImpl::UpdateFormData(const std::string& data)
{
    if (isFormRenderInit_) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        container->UpdateFormData(data);
    } else {
        formData_ = data;
    }
}

void UIContentImpl::UpdateFormSharedImage(const std::map<std::string, sptr<OHOS::AppExecFwk::FormAshmem>>& imageDataMap)
{
    if (isFormRenderInit_) {
        auto container = Platform::AceContainer::GetContainer(instanceId_);
        CHECK_NULL_VOID(container);
        container->UpdateFormSharedImage(imageDataMap);
    } else {
        formImageDataMap_ = imageDataMap;
    }
}

void UIContentImpl::SetActionEventHandler(std::function<void(const std::string& action)>&& actionCallback)
{
    CHECK_NULL_VOID(actionCallback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetActionEventHandler(std::move(actionCallback));
}

void UIContentImpl::SetFormLinkInfoUpdateHandler(std::function<void(const std::vector<std::string>&)>&& callback)
{
    CHECK_NULL_VOID(callback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    pipelineContext->SetFormLinkInfoUpdateHandler(std::move(callback));
}

void UIContentImpl::SetErrorEventHandler(std::function<void(const std::string&, const std::string&)>&& errorCallback)
{
    CHECK_NULL_VOID(errorCallback);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto front = container->GetFrontend();
    CHECK_NULL_VOID(front);
    return front->SetErrorEventHandler(std::move(errorCallback));
}

void UIContentImpl::OnFormSurfaceChange(float width, float height)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    ContainerScope scope(instanceId_);
    auto density = pipelineContext->GetDensity();
    pipelineContext->SetRootSize(density, width, height);
    pipelineContext->OnSurfaceChanged(width, height);
}

void UIContentImpl::SetFormBackgroundColor(const std::string& color)
{
    LOGI("UIContentImpl: SetFormBackgroundColor color is %{public}s", color.c_str());
    if (!Rosen::RSSystemProperties::GetUniRenderEnabled()) {
        // cannot set transparent background effects in not-uniform-render mode
        return;
    }
    Color bgColor;
    if (!Color::ParseColorString(color, bgColor)) {
        return;
    }
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostSyncTask(
        [container, bgColor]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetAppBgColor(bgColor);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::GetResourcePaths(std::vector<std::string>& resourcesPaths, std::string& assetRootPath,
    std::vector<std::string>& assetBasePaths, std::string& resFolderName)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
        },
        TaskExecutor::TaskType::PLATFORM);
}

void UIContentImpl::SetResourcePaths(const std::vector<std::string>& resourcesPaths, const std::string& assetRootPath,
    const std::vector<std::string>& assetBasePaths)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, resourcesPaths, assetRootPath, assetBasePaths]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            auto flutterAssetManager = pipelineContext->GetAssetManager();
            CHECK_NULL_VOID(flutterAssetManager);
            auto themeManager = pipelineContext->GetThemeManager();
            CHECK_NULL_VOID(themeManager);

            if (resourcesPaths.empty() && assetRootPath.empty()) {
                LOGE("Reload old resource");
                return;
            }

            if (!assetRootPath.empty()) {
                LOGD("new FileAssetProvider, assetRootPath: %{private}s", assetRootPath.c_str());
                auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
                if (assetProvider->Initialize(assetRootPath, assetBasePaths)) {
                    flutterAssetManager->PushBack(std::move(assetProvider));
                }
                return;
            }

            for (auto iter = resourcesPaths.begin(); iter != resourcesPaths.end(); iter++) {
                LOGD("new HapAssetProvider, iter: %{private}s", iter->c_str());
                auto assetProvider = AceType::MakeRefPtr<HapAssetProvider>();
                if (assetProvider->Initialize(*iter, assetBasePaths)) {
                    flutterAssetManager->PushBack(std::move(assetProvider));
                }
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void UIContentImpl::SetIsFocusActive(bool isFocusActive)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, isFocusActive]() {
            auto pipelineContext = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->SetIsFocusActive(isFocusActive);
        },
        TaskExecutor::TaskType::UI);
}

void UIContentImpl::UpdateResource()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([container]() { container->UpdateResource(); }, TaskExecutor::TaskType::UI);
}

int32_t UIContentImpl::CreateModalUIExtension(
    const AAFwk::Want& want, const ModalUIExtensionCallbacks& callbacks, const ModalUIExtensionConfig& config)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_RETURN(container, 0);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0);
    int32_t sessionId = 0;
    taskExecutor->PostSyncTask(
        [container, &sessionId, want, callbacks = callbacks, config = config]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            sessionId = overlay->CreateModalUIExtension(want, callbacks, config.isProhibitBack);
        },
        TaskExecutor::TaskType::UI);
    LOGI("UIExtension create modal page end, sessionId=%{public}d", sessionId);
    return sessionId;
}

void UIContentImpl::CloseModalUIExtension(int32_t sessionId)
{
    LOGI("UIExtension close modal page start, sessionId=%{public}d", sessionId);
    if (sessionId == 0) {
        LOGW("UIExtension refuse to close modal page");
        return;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, sessionId]() {
            auto pipeline = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
            CHECK_NULL_VOID(pipeline);
            auto overlay = pipeline->GetOverlayManager();
            CHECK_NULL_VOID(overlay);
            overlay->CloseModalUIExtension(sessionId);
        },
        TaskExecutor::TaskType::UI);
}
} // namespace OHOS::Ace
