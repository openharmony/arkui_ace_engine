/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "native_reference.h"
#include "service_extension_context.h"
#include "adapter/ohos/osal/pixel_map_ohos.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/file_asset_provider.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "adapter/ohos/entrance/hap_asset_provider.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/geometry/rect.h"
#include "base/log/log.h"
#include "base/log/ace_trace.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/flutter/flutter_asset_manager.h"
#include "core/common/plugin_manager.h"

namespace OHOS::Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string START_PARAMS_KEY = "__startParams";

} // namespace

static std::atomic<int32_t> gInstanceId = 0;
static std::atomic<int32_t> gSubWindowInstanceId = 100000;
static std::atomic<int32_t> gSubInstanceId = 1000000;
const std::string SUBWINDOW_PREFIX = "ARK_APP_SUBWINDOW_";
const int32_t REQUEST_CODE = -1;

using ContentFinishCallback = std::function<void()>;
using ContentStartAbilityCallback = std::function<void(const std::string& address)>;
class ContentEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit ContentEventCallback(ContentFinishCallback onFinish) : onFinish_(onFinish) {}
    ContentEventCallback(ContentFinishCallback onFinish, ContentStartAbilityCallback onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility) {}
    ~ContentEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("UIContent OnFinish");
        if (onFinish_) {
            onFinish_();
        }
    }

    void OnStartAbility(const std::string& address) override
    {
        LOGI("UIContent OnStartAbility");
        if (onStartAbility_) {
            onStartAbility_(address);
        }
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("UIContent OnStatusBarBgColorChanged");
    }

private:
    ContentFinishCallback onFinish_;
    ContentStartAbilityCallback onStartAbility_;
};

extern "C" ACE_EXPORT void* OHOS_ACE_CreateUIContent(void* context, void* runtime)
{
    LOGI("Ace lib loaded, CreateUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AbilityRuntime::Context*>(context), runtime);
}

extern "C" ACE_EXPORT void* OHOS_ACE_CreateSubWindowUIContent(void* ability)
{
    LOGI("Ace lib loaded, Create SubWindowUIContent.");
    return new UIContentImpl(reinterpret_cast<OHOS::AppExecFwk::Ability*>(ability));
}

class OccupiedAreaChangeListener : public OHOS::Rosen::IOccupiedAreaChangeListener {
public:
    explicit OccupiedAreaChangeListener(int32_t instanceId) : instanceId_(instanceId) {}
    ~OccupiedAreaChangeListener() = default;

    void OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
    {
        auto rect = info->rect_;
        auto type = info->type_;
        Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
        LOGI("UIContent::OccupiedAreaChange rect:%{public}s type: %{public}d", keyboardRect.ToString().c_str(), type);
        if (type == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT) {
            auto container = Platform::AceContainer::GetContainer(instanceId_);
            if (!container) {
                LOGE("container may be destroyed.");
                return;
            }
            auto taskExecutor = container->GetTaskExecutor();
            if (!taskExecutor) {
                LOGE("OnSizeChange: taskExecutor is null.");
                return;
            }

            ContainerScope scope(instanceId_);
            taskExecutor->PostTask([container, keyboardRect] {
                auto context = container->GetPipelineContext();
                if (context) {
                    context->OnVirtualKeyboardAreaChange(keyboardRect);
                }
            }, TaskExecutor::TaskType::UI);
        }
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
        LOGI("DragWindowListener::OnDrag called.");
        auto flutterAceView =
            static_cast<Platform::FlutterAceView*>(Platform::AceContainer::GetContainer(instanceId_)->GetView());
        if (!flutterAceView) {
            LOGE("DragWindowListener::OnDrag flutterAceView is null");
            return;
        }

        DragEventAction action;
        switch (event) {
            case OHOS::Rosen::DragEvent::DRAG_EVENT_END:
                action = DragEventAction::DRAG_EVENT_END;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_MOVE:
            case OHOS::Rosen::DragEvent::DRAG_EVENT_OUT:
                action = DragEventAction::DRAG_EVENT_MOVE;
                break;
            case OHOS::Rosen::DragEvent::DRAG_EVENT_IN:
            default:
                action = DragEventAction::DRAG_EVENT_START;
                break;
        }

        flutterAceView->ProcessDragEvent(x, y, action);
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
        if (!container) {
            LOGE("OnTouchOutside: container may be destroyed.");
            return;
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("OnTouchOutside: taskExecutor is null.");
            return;
        }

        ContainerScope scope(instanceId_);
        taskExecutor->PostTask([] { SubwindowManager::GetInstance()->ClearMenu(); }, TaskExecutor::TaskType::UI);
    }

private:
    int32_t instanceId_ = -1;
};

UIContentImpl::UIContentImpl(OHOS::AbilityRuntime::Context* context, void* runtime) : runtime_(runtime)
{
    if (context == nullptr) {
        LOGE("context is nullptr");
        return;
    }
    const auto& obj = context->GetBindingObject();
    auto ref = obj->Get<NativeReference>();
    auto object = AbilityRuntime::ConvertNativeValueTo<NativeObject>(ref->Get());
    auto weak = static_cast<std::weak_ptr<AbilityRuntime::Context>*>(object->GetNativePointer());
    context_ = *weak;
    LOGI("Create UIContentImpl successfully.");
}

UIContentImpl::UIContentImpl(OHOS::AppExecFwk::Ability* ability)
{
    if (ability == nullptr) {
        LOGE("ability is nullptr");
        return;
    }
    auto weak = static_cast<std::weak_ptr<AbilityRuntime::Context>>(ability->GetAbilityContext());
    context_ = weak;
    LOGI("Create UIContentImpl successfully.");
}

void UIContentImpl::DestroyUIDirector()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }
    auto rsUIDirector = pipelineContext->GetRSUIDirector();
    if (!rsUIDirector) {
        return;
    }
    LOGI("Destroying old rsUIDirectory");
    rsUIDirector->Destroy();
}

void UIContentImpl::Initialize(OHOS::Rosen::Window* window, const std::string& url, NativeValue* storage)
{
    CommonInitialize(window, url, storage);
    LOGI("Initialize startUrl = %{public}s", startUrl_.c_str());
    // run page.
    Platform::AceContainer::RunPage(
        instanceId_, Platform::AceContainer::GetContainer(instanceId_)->GeneratePageId(), startUrl_, "");
    LOGD("Initialize UIContentImpl done.");
}

void UIContentImpl::Restore(OHOS::Rosen::Window* window, const std::string& contentInfo, NativeValue* storage)
{
    CommonInitialize(window, contentInfo, storage);
    startUrl_ = Platform::AceContainer::RestoreRouterStack(instanceId_, contentInfo);
    if (startUrl_.empty()) {
        LOGW("UIContent Restore start url is empty");
    }
    LOGI("Restore startUrl = %{public}s", startUrl_.c_str());
    Platform::AceContainer::RunPage(
        instanceId_, Platform::AceContainer::GetContainer(instanceId_)->GeneratePageId(), startUrl_, "");
    LOGI("Restore UIContentImpl done.");
}

std::string UIContentImpl::GetContentInfo() const
{
    LOGI("UIContent GetContentInfo");
    return Platform::AceContainer::GetContentInfo(instanceId_);
}

void UIContentImpl::CommonInitialize(OHOS::Rosen::Window* window, const std::string& contentInfo, NativeValue* storage)
{
    ACE_FUNCTION_TRACE();
    window_ = window;
    startUrl_ = contentInfo;
    if (!window_) {
        LOGE("Null window, can't initialize UI content");
        return;
    }
    if (StringUtils::StartWith(window->GetWindowName(), SUBWINDOW_PREFIX)) {
        InitializeSubWindow(window_);
        return;
    }
    auto context = context_.lock();
    if (!context) {
        LOGE("context is null");
        return;
    }
    LOGI("Initialize UIContentImpl start.");
    static std::once_flag onceFlag;
    std::call_once(onceFlag, [&context]() {
        LOGI("Initialize for current process.");
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        AceApplicationInfo::GetInstance().SetProcessName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetPackageName(context->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(context->GetFilesDir());
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingPid());
        CapabilityRegistry::Register();
        ImageCache::SetImageCacheFilePath(context->GetCacheDir());
        ImageCache::SetCacheFileInfo();
    });
    bool useNewPipe = AceApplicationInfo::GetInstance().GetPackageName() == SystemProperties::GetNewPipePkg();
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector) {
            rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
            rsUiDirector->SetCacheDir(context->GetCacheDir());
            rsUiDirector->Init();
        }
    }

    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    float density = 1.0f;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        LOGI("UIContent: deviceWidth: %{public}d, deviceHeight: %{public}d, default density: %{public}f", deviceWidth,
            deviceHeight, density);
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density, false);
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
            LOGI("UIContent set dark mode");
        } else {
            SystemProperties::SetColorMode(ColorMode::LIGHT);
            LOGI("UIContent set light mode");
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
    AceApplicationInfo::GetInstance().SetAbilityName(info->name);

    RefPtr<FlutterAssetManager> flutterAssetManager = Referenced::MakeRefPtr<FlutterAssetManager>();
    bool isModelJson = info != nullptr ? info->isModuleJson : false;
    std::string moduleName = info != nullptr ? info->moduleName : "";
    auto appInfo = context->GetApplicationInfo();
    auto bundleName = info != nullptr ? info->bundleName : "";
    std::string resPath;
    std::string pageProfile;
    LOGI("Initialize UIContent isModelJson:%{public}s", isModelJson ? "true" : "false");
    if (isModelJson) {
        std::string hapPath = info->hapPath;
        LOGI("hapPath:%{public}s", hapPath.c_str());
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
        LOGI("In stage mode, resPath:%{private}s", resPath.c_str());
        auto assetBasePathStr = { std::string("ets/"), std::string("resources/base/profile/") };
        if (flutterAssetManager && !resPath.empty()) {
            auto assetProvider = AceType::MakeRefPtr<FileAssetProvider>();
            if (assetProvider->Initialize(resPath, assetBasePathStr)) {
                LOGD("Push AssetProvider to queue.");
                flutterAssetManager->PushBack(std::move(assetProvider));
            }
        }

        auto hapInfo = context->GetHapModuleInfo();
        if (hapInfo) {
            pageProfile = hapInfo->pages;
            const std::string profilePrefix = "$profile:";
            if (pageProfile.compare(0, profilePrefix.size(), profilePrefix) == 0) {
                pageProfile = pageProfile.substr(profilePrefix.length()).append(".json");
            }
            LOGI("In stage mode, pageProfile:%{public}s", pageProfile.c_str());
        } else {
            LOGE("In stage mode, can't get hap info.");
        }
    } else {
        auto packagePathStr = context->GetBundleCodeDir();
        auto moduleInfo = context->GetHapModuleInfo();
        if (moduleInfo != nullptr) {
            packagePathStr += "/" + moduleInfo->package + "/";
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
    if (appInfo && flutterAssetManager) {
        /* Note: DO NOT modify the sequence of adding libPath  */
        std::string nativeLibraryPath = appInfo->nativeLibraryPath;
        std::string quickFixLibraryPath = appInfo->appQuickFix.deployedAppqfInfo.nativeLibraryPath;
        std::vector<std::string> libPaths;
        if (!quickFixLibraryPath.empty()) {
            std::string libPath = GenerateFullPath(context->GetBundleCodeDir(), quickFixLibraryPath);
            libPaths.push_back(libPath);
            LOGI("napi quick fix lib path = %{private}s", libPath.c_str());
        }
        if (!nativeLibraryPath.empty()) {
            std::string libPath = GenerateFullPath(context->GetBundleCodeDir(), nativeLibraryPath);
            libPaths.push_back(libPath);
            LOGI("napi lib path = %{private}s", libPath.c_str());
        }
        if (!libPaths.empty()) {
            flutterAssetManager->SetLibPath(libPaths);
        }
    }

    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(nullptr, pluginUtils);
    // create container
    if (runtime_) {
        instanceId_ = gInstanceId.fetch_add(1, std::memory_order_relaxed);
    } else {
        instanceId_ = gSubWindowInstanceId.fetch_add(1, std::memory_order_relaxed);
    }
    auto container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, true,
        context_, info, std::make_unique<ContentEventCallback>([context = context_] {
            auto sharedContext = context.lock();
            if (!sharedContext) {
                return;
            }
            auto abilityContext =
                OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
            if (abilityContext) {
                abilityContext->CloseAbility();
            }
        }, [context = context_](const std::string& address) {
            auto sharedContext = context.lock();
            if (!sharedContext) {
                return;
            }
            auto abilityContext =
                OHOS::AbilityRuntime::Context::ConvertTo<OHOS::AbilityRuntime::AbilityContext>(sharedContext);
            if (abilityContext) {
                LOGI("start ability with url = %{private}s", address.c_str());
                AAFwk::Want want;
                want.AddEntity(Want::ENTITY_BROWSER);
                want.SetParam("address", address);
                abilityContext->StartAbility(want, REQUEST_CODE);
            }
        }), false, false, useNewPipe);
    if (!container) {
        LOGE("Create container is null.");
        return;
    }
    container->SetWindowName(window_->GetWindowName());
    container->SetWindowId(window_->GetWindowId());

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
    container->SetAssetManager(flutterAssetManager);
    container->SetBundlePath(context->GetBundleCodeDir());
    container->SetFilesDataPath(context->GetFilesDir());

    if (window_->IsDecorEnable()) {
        LOGI("Container modal is enabled.");
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }

    // create ace_view
    auto flutterAceView =
        Platform::FlutterAceView::CreateView(instanceId_, false, container->GetSettings().usePlatformAsUIThread);
    Platform::FlutterAceView::SurfaceCreated(flutterAceView, window_);
    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [window, id = instanceId_, container, flutterAceView, rsUiDirector](
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
                    flutterAceView->InitIOManager(container->GetTaskExecutor());
                    LOGD("UIContent Init Rosen Backend");
            }
        };
#endif
        // set view
        Platform::AceContainer::SetView(flutterAceView, density, 0, 0, window_, callback);
    } else {
        Platform::AceContainer::SetViewNew(flutterAceView, density, 0, 0, window_);
    }
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);
    // Set sdk version in module json mode
    if (isModelJson) {
        auto pipeline = container->GetPipelineContext();
        if (pipeline && appInfo) {
            LOGI("SetMinPlatformVersion code is %{public}d", appInfo->minCompatibleVersionCode);
            pipeline->SetMinPlatformVersion(appInfo->minCompatibleVersionCode);
        }
    }
    if (runtime_) {
        auto nativeEngine = reinterpret_cast<NativeEngine*>(runtime_);
        if (!storage) {
            container->SetLocalStorage(nullptr, context->GetBindingObject()->Get<NativeReference>());
        } else {
            LOGI("SetLocalStorage %{public}d", storage->TypeOf());
            container->SetLocalStorage(
                nativeEngine->CreateReference(storage, 1), context->GetBindingObject()->Get<NativeReference>());
        }
    }
    InitWindowCallback(info);
}

void UIContentImpl::Foreground()
{
    LOGI("UIContentImpl: window foreground");
    Platform::AceContainer::OnShow(instanceId_);
    // set the flag isForegroundCalled to be true
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("get container(id=%{public}d) failed", instanceId_);
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        LOGE("get pipeline context failed");
        return;
    }
    pipelineContext->SetForegroundCalled(true);
}

void UIContentImpl::Background()
{
    LOGI("UIContentImpl: window background");
    Platform::AceContainer::OnHide(instanceId_);
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
    Platform::AceContainer::DestroyContainer(instanceId_);
}

void UIContentImpl::OnNewWant(const OHOS::AAFwk::Want& want)
{
    LOGI("UIContent OnNewWant");
    Platform::AceContainer::OnShow(instanceId_);
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(instanceId_, params);
}

uint32_t UIContentImpl::GetBackgroundColor()
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("GetBackgroundColor failed: container is null. return 0x000000");
        return 0x000000;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("GetBackgroundColor failed: taskExecutor is null.");
        return 0x000000;
    }
    ContainerScope scope(instanceId_);
    uint32_t bgColor = 0x000000;
    taskExecutor->PostSyncTask([&bgColor, container]() {
            if (!container) {
                LOGE("Post sync task GetBackgroundColor failed: container is null. return 0x000000");
                return;
            }
            auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (!pipelineContext) {
                LOGE("Post sync task GetBackgroundColor failed: pipeline is null. return 0x000000");
                return;
            }
            bgColor = pipelineContext->GetAppBgColor().GetValue();
        }, TaskExecutor::TaskType::UI);

    LOGI("UIContentImpl::GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}

void UIContentImpl::SetBackgroundColor(uint32_t color)
{
    LOGI("UIContentImpl::SetBackgroundColor color is %{public}u", color);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("SetBackgroundColor failed: container is null.");
        return;
    }
    ContainerScope scope(instanceId_);
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("SetBackgroundColor failed: taskExecutor is null.");
        return;
    }
    taskExecutor->PostSyncTask([container, bgColor = color]() {
        auto pipelineContext = container->GetPipelineContext();
        if (!pipelineContext) {
            LOGE("SetBackgroundColor failed, pipeline context is null.");
            return;
        }
        pipelineContext->SetAppBgColor(Color(bgColor));
    }, TaskExecutor::TaskType::UI);
}

bool UIContentImpl::ProcessBackPressed()
{
    LOGI("ProcessBackPressed: Platform::AceContainer::OnBackPressed called");
    if (Platform::AceContainer::OnBackPressed(instanceId_)) {
        LOGI("ProcessBackPressed: Platform::AceContainer::OnBackPressed return true");
        return true;
    }
    LOGI("ProcessBackPressed: Platform::AceContainer::OnBackPressed return false");
    return false;
}

bool UIContentImpl::ProcessPointerEvent(const std::shared_ptr<OHOS::MMI::PointerEvent>& pointerEvent)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container) {
        auto aceView = static_cast<Platform::FlutterAceView*>(container->GetAceView());
        Platform::FlutterAceView::DispatchTouchEvent(aceView, pointerEvent);
        return true;
    }
    return false;
}

bool UIContentImpl::ProcessKeyEvent(const std::shared_ptr<OHOS::MMI::KeyEvent>& touchEvent)
{
    LOGI("AceAbility::OnKeyUp called,touchEvent info: keyCode is %{private}d,"
         "keyAction is %{public}d, keyActionTime is %{public}" PRId64,
        touchEvent->GetKeyCode(), touchEvent->GetKeyAction(), touchEvent->GetActionTime());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (container) {
        auto aceView = static_cast<Platform::FlutterAceView*>(container->GetAceView());
        return Platform::FlutterAceView::DispatchKeyEvent(aceView, touchEvent);
    }
    return false;
}

bool UIContentImpl::ProcessAxisEvent(const std::shared_ptr<OHOS::MMI::AxisEvent>& axisEvent)
{
    LOGI("UIContent ProcessAxisEvent");
    return false;
}

bool UIContentImpl::ProcessVsyncEvent(uint64_t timeStampNanos)
{
    LOGI("UIContent ProcessVsyncEvent");
    return false;
}

void UIContentImpl::UpdateConfiguration(const std::shared_ptr<OHOS::AppExecFwk::Configuration>& config)
{
    if (!config) {
        LOGE("UIContent null config");
        return;
    }
    Platform::AceContainer::OnConfigurationUpdated(instanceId_, (*config).GetName());
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("UIContent container is null");
        return;
    }
    auto colorMode = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    auto deviceAccess = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    auto languageTag = config->GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    container->UpdateConfiguration(colorMode, deviceAccess, languageTag);
    LOGI("UIContentImpl::UpdateConfiguration called End, name:%{public}s", config->GetName().c_str());
}

void UIContentImpl::UpdateViewportConfig(const ViewportConfig& config, OHOS::Rosen::WindowSizeChangeReason reason)
{
    LOGI("UIContent UpdateViewportConfig %{public}s", config.ToString().c_str());
    SystemProperties::SetResolution(config.Density());
    SystemProperties::SetDeviceOrientation(config.Height() >= config.Width() ? 0 : 1);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("UpdateViewportConfig: container is null.");
        return;
    }
    container->SetWindowPos(config.Left(), config.Top());
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("UpdateViewportConfig: taskExecutor is null.");
        return;
    }
    taskExecutor->PostTask([config, container, reason]() {
            auto aceView = static_cast<Platform::FlutterAceView*>(container->GetAceView());
            if (!aceView) {
                LOGE("UpdateViewportConfig: aceView is null.");
                return;
            }
            flutter::ViewportMetrics metrics;
            metrics.physical_width = config.Width();
            metrics.physical_height = config.Height();
            metrics.device_pixel_ratio = config.Density();
            Platform::FlutterAceView::SetViewportMetrics(aceView, metrics);
            Platform::FlutterAceView::SurfaceChanged(aceView, config.Width(), config.Height(), config.Orientation(),
                static_cast<WindowSizeChangeReason>(reason));
            Platform::FlutterAceView::SurfacePositionChanged(aceView, config.Left(), config.Top());
        }, TaskExecutor::TaskType::PLATFORM);
}

void UIContentImpl::UpdateWindowMode(OHOS::Rosen::WindowMode mode)
{
    LOGI("UpdateWindowMode, window mode is %{public}d", mode);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask([container, mode]() {
        auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
        if (!pipelineContext) {
            LOGE("UpdateWindowMode failed, pipeline context is null.");
            return;
        }
        if (mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FULLSCREEN ||
            mode == OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            mode == OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
            pipelineContext->ShowContainerTitle(false);
        } else {
            pipelineContext->ShowContainerTitle(true);
        }
    }, TaskExecutor::TaskType::UI);
}

void UIContentImpl::HideWindowTitleButton(bool hideSplit, bool hideMaximize, bool hideMinimize)
{
    LOGI("HideWindowTitleButton hideSplit: %{public}d, hideMaximize: %{public}d, hideMinimize: %{public}d",
        hideSplit, hideMaximize, hideMinimize);
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(instanceId_);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [container, hideSplit, hideMaximize, hideMinimize]() {
            auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (!pipelineContext) {
                LOGE("pipeline context is null.");
                return;
            }
            pipelineContext->SetContainerButtonHide(hideSplit, hideMaximize, hideMinimize);
        }, TaskExecutor::TaskType::UI);
}

void UIContentImpl::DumpInfo(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("get container(id=%{public}d) failed", instanceId_);
        return;
    }
    auto pipelineContext = container->GetPipelineContext();
    if (!pipelineContext) {
        LOGE("get pipeline context failed");
        return;
    }
    pipelineContext->DumpInfo(params, info);
}

void UIContentImpl::InitWindowCallback(const std::shared_ptr<OHOS::AppExecFwk::AbilityInfo>& info)
{
    LOGI("UIContent InitWindowCallback");
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("InitWindowCallback failed, container(id=%{public}d) is null.", instanceId_);
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        LOGE("InitWindowCallback failed, pipelineContext is null.");
        return;
    }
    auto& window = window_;
    if (!window) {
        LOGE("InitWindowCallback failed, window is null.");
        return;
    }
    if (info != nullptr) {
        pipelineContext->SetAppLabelId(info->labelId);
        pipelineContext->SetAppIconId(info->iconId);
    }

    pipelineContext->SetWindowMinimizeCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Minimize()); });

    pipelineContext->SetWindowMaximizeCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Maximize()); });

    pipelineContext->SetWindowRecoverCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Recover()); });

    pipelineContext->SetWindowCloseCallBack(
        [window]() -> bool { return (OHOS::Rosen::WMError::WM_OK == window->Close()); });

    pipelineContext->SetWindowStartMoveCallBack([window]() { window->StartMove(); });

    pipelineContext->SetWindowSplitCallBack([window]() -> bool {
        return (
            OHOS::Rosen::WMError::WM_OK == window->SetWindowMode(OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY));
    });

    pipelineContext->SetWindowGetModeCallBack([window]() -> WindowMode { return (WindowMode)window->GetMode(); });

    pipelineContext->SetGetWindowRectImpl([window]() -> Rect {
        Rect rect;
        if (!window) {
            return rect;
        }
        auto windowRect = window->GetRect();
        rect.SetRect(windowRect.posX_, windowRect.posY_, windowRect.width_, windowRect.height_);
        return rect;
    });

    dragWindowListener_ = new DragWindowListener(instanceId_);
    window->RegisterDragListener(dragWindowListener_);
    occupiedAreaChangeListener_ = new OccupiedAreaChangeListener(instanceId_);
    window->RegisterOccupiedAreaChangeListener(occupiedAreaChangeListener_);
}

void UIContentImpl::InitializeSubWindow(OHOS::Rosen::Window* window)
{
    window_ = window;
    LOGI("The window name is %{public}s", window->GetWindowName().c_str());
    if (!window_) {
        LOGE("Null window, can't initialize UI content");
        return;
    }

    RefPtr<Platform::AceContainer> container;
    instanceId_ = gSubInstanceId.fetch_add(1, std::memory_order_relaxed);

    std::weak_ptr<OHOS::AppExecFwk::AbilityInfo> abilityInfo;
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext;
    container = AceType::MakeRefPtr<Platform::AceContainer>(instanceId_, FrontendType::DECLARATIVE_JS, true,
        runtimeContext, abilityInfo, std::make_unique<ContentEventCallback>([] {
            // Sub-window ,just return.
            LOGI("Content event callback");
        }),
        false, true);
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), instanceId_);
    AceEngine::Get().AddContainer(instanceId_, container);
    touchOutsideListener_ = new TouchOutsideListener(instanceId_);
    window_->RegisterTouchOutsideListener(touchOutsideListener_);
}

void UIContentImpl::SetNextFrameLayoutCallback(std::function<void()>&& callback)
{
    if (!callback) {
        LOGI("set callback to nullptr");
        return;
    }
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    if (!container) {
        LOGE("get container(id=%{public}d) failed", instanceId_);
        return;
    }
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        LOGE("get pipeline context failed");
        return;
    }
    pipelineContext->SetNextFrameLayoutCallback(std::move(callback));
}

void UIContentImpl::NotifyMemoryLevel(int32_t level)
{
    LOGI("Receive memory level notification, level: %{public}d", level);
}

void UIContentImpl::SetAppWindowTitle(const std::string& title)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    LOGI("set app title");
    pipelineContext->SetAppTitle(title);
}

void UIContentImpl::SetAppWindowIcon(const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    auto container = Platform::AceContainer::GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(pipelineContext);
    LOGI("set app icon");
    pipelineContext->SetAppIcon(AceType::MakeRefPtr<PixelMapOhos>(pixelMap));
}
} // namespace OHOS::Ace
