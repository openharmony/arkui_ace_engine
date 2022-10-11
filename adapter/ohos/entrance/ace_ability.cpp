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

#include "adapter/ohos/entrance/ace_ability.h"

#include <regex>
#include <ui/rs_surface_node.h>

#include "ability_process.h"
#include "display_type.h"
#include "dm/display_manager.h"
#include "init_data.h"
#include "ipc_skeleton.h"
#include "res_config.h"
#include "resource_manager.h"
#include "string_wrapper.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/geometry/rect.h"
#include "base/log/log.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/frontend.h"
#include "core/common/plugin_manager.h"
#include "core/common/plugin_utils.h"

namespace OHOS {
namespace Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
static int32_t g_instanceId = 0;

FrontendType GetFrontendType(const std::string& frontendType)
{
    if (frontendType == "normal") {
        return FrontendType::JS;
    } else if (frontendType == "form") {
        return FrontendType::JS_CARD;
    } else if (frontendType == "declarative") {
        return FrontendType::DECLARATIVE_JS;
    } else {
        LOGW("frontend type not supported. return default frontend: JS frontend.");
        return FrontendType::JS;
    }
}

FrontendType GetFrontendTypeFromManifest(const std::string& packagePath, const std::string& srcPath, bool isHap)
{
    std::string manifest = std::string("assets/js/default/manifest.json");
    if (!srcPath.empty()) {
        manifest = "assets/js/" + srcPath + "/manifest.json";
    }
    std::string jsonStr = isHap ? GetStringFromHap(packagePath, manifest) : GetStringFromFile(packagePath, manifest);
    if (jsonStr.empty()) {
        LOGE("return default frontend: JS frontend.");
        return FrontendType::JS;
    }
    auto rootJson = JsonUtil::ParseJsonString(jsonStr);
    auto mode = rootJson->GetObject("mode");
    if (mode != nullptr) {
        if (mode->GetString("syntax") == "ets" || mode->GetString("type") == "pageAbility") {
            return FrontendType::DECLARATIVE_JS;
        }
    }
    return GetFrontendType(rootJson->GetString("type"));
}

} // namespace

using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;

using AcePlatformFinish = std::function<void()>;
using AcePlatformStartAbility = std::function<void(const std::string& address)>;
class AcePlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit AcePlatformEventCallback(AcePlatformFinish onFinish) : onFinish_(onFinish) {}
    AcePlatformEventCallback(AcePlatformFinish onFinish, AcePlatformStartAbility onStartAbility)
        : onFinish_(onFinish), onStartAbility_(onStartAbility)
    {}

    ~AcePlatformEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("AcePlatformEventCallback OnFinish");
        if (onFinish_) {
            onFinish_();
        }
    }

    void OnStartAbility(const std::string& address) override
    {
        LOGI("AcePlatformEventCallback OnStartAbility");
        if (onStartAbility_) {
            onStartAbility_(address);
        }
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("AcePlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    AcePlatformFinish onFinish_;
    AcePlatformStartAbility onStartAbility_;
};

const std::string AceAbility::START_PARAMS_KEY = "__startParams";
const std::string AceAbility::PAGE_URI = "url";
const std::string AceAbility::CONTINUE_PARAMS_KEY = "__remoteData";

REGISTER_AA(AceAbility)
void AceWindowListener::OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnDrag(x, y, event);
}

void AceWindowListener::OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnSizeChange(info);
}

void AceWindowListener::SetBackgroundColor(uint32_t color)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->SetBackgroundColor(color);
}

uint32_t AceWindowListener::GetBackgroundColor()
{
    CHECK_NULL_RETURN(callbackOwner_, 0);
    return callbackOwner_->GetBackgroundColor();
}

void AceWindowListener::OnSizeChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnSizeChange(rect, reason);
}

void AceWindowListener::OnModeChange(OHOS::Rosen::WindowMode mode)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnModeChange(mode);
}

bool AceWindowListener::OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const
{
    CHECK_NULL_RETURN(callbackOwner_, false);
    return callbackOwner_->OnInputEvent(keyEvent);
}

bool AceWindowListener::OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const
{
    CHECK_NULL_RETURN(callbackOwner_, false);
    return callbackOwner_->OnInputEvent(pointerEvent);
}

bool AceWindowListener::OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const
{
    CHECK_NULL_RETURN(callbackOwner_, false);
    return callbackOwner_->OnInputEvent(axisEvent);
}

AceAbility::AceAbility() = default;

void AceAbility::OnStart(const Want& want)
{
    Ability::OnStart(want);
    LOGI("AceAbility::OnStart called");
    abilityId_ = g_instanceId++;
    static std::once_flag onceFlag;
    auto abilityContext = GetAbilityContext();
    std::call_once(onceFlag, [abilityContext]() {
        LOGI("Initialize for current process.");
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        CapabilityRegistry::Register();
        AceApplicationInfo::GetInstance().SetPackageName(abilityContext->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(abilityContext->GetFilesDir());
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingPid());
        ImageCache::SetImageCacheFilePath(abilityContext->GetCacheDir());
        ImageCache::SetCacheFileInfo();
        AceEngine::InitJsDumpHeadSignal();
    });
    AceNewPipeJudgement::InitAceNewPipeConfig();
    // TODO: now choose pipeline using param set as package name, later enable for all.
    auto apiCompatibleVersion = abilityContext->GetApplicationInfo()->apiCompatibleVersion;
    auto apiReleaseType = abilityContext->GetApplicationInfo()->apiReleaseType;
    auto useNewPipe = AceNewPipeJudgement::QueryAceNewPipeEnabled(
        AceApplicationInfo::GetInstance().GetPackageName(), apiCompatibleVersion, apiReleaseType);
    LOGI("AceAbility: apiCompatibleVersion: %{public}d, and apiReleaseType: %{public}s, useNewPipe: %{public}d",
        apiCompatibleVersion, apiReleaseType.c_str(), useNewPipe);
    OHOS::sptr<OHOS::Rosen::Window> window = Ability::GetWindow();
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector) {
            rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());
            rsUiDirector->SetCacheDir(abilityContext->GetCacheDir());
            rsUiDirector->Init();
        }
    }

    std::shared_ptr<AceAbility> self = std::static_pointer_cast<AceAbility>(shared_from_this());
    OHOS::sptr<AceWindowListener> aceWindowListener = new AceWindowListener(self);
    // register surface change callback and window mode change callback
    window->RegisterWindowChangeListener(aceWindowListener);
    // register drag event callback
    window->RegisterDragListener(aceWindowListener);
    // register Occupied Area callback
    window->RegisterOccupiedAreaChangeListener(aceWindowListener);
    // register ace ability handler callback
    window->SetAceAbilityHandler(aceWindowListener);
    // register input consumer callback
    std::shared_ptr<AceWindowListener> aceInputConsumer = std::make_shared<AceWindowListener>(self);
    window->SetInputEventConsumer(aceInputConsumer);

    int32_t deviceWidth = 0;
    int32_t deviceHeight = 0;
    auto defaultDisplay = Rosen::DisplayManager::GetInstance().GetDefaultDisplay();
    if (defaultDisplay) {
        density_ = defaultDisplay->GetVirtualPixelRatio();
        deviceWidth = defaultDisplay->GetWidth();
        deviceHeight = defaultDisplay->GetHeight();
        LOGI("AceAbility: deviceWidth: %{public}d, deviceHeight: %{public}d, default density: %{public}f", deviceWidth,
            deviceHeight, density_);
    }
    SystemProperties::InitDeviceInfo(deviceWidth, deviceHeight, deviceHeight >= deviceWidth ? 0 : 1, density_, false);
    SystemProperties::SetColorMode(ColorMode::LIGHT);

    std::unique_ptr<Global::Resource::ResConfig> resConfig(Global::Resource::CreateResConfig());
    auto resourceManager = GetResourceManager();
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
        } else {
            LOGW("localeInfo is null.");
            AceApplicationInfo::GetInstance().SetLocale("", "", "", "");
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
    } else {
        LOGW("resourceManager is null.");
        AceApplicationInfo::GetInstance().SetLocale("", "", "", "");
    }

    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    if (moduleInfo != nullptr) {
        packagePathStr += "/" + moduleInfo->package + "/";
    }
    std::shared_ptr<AbilityInfo> info = GetAbilityInfo();
    std::string srcPath;
    if (info != nullptr && !info->srcPath.empty()) {
        srcPath = info->srcPath;
    }
    if (info != nullptr && !info->bundleName.empty()) {
        AceApplicationInfo::GetInstance().SetPackageName(info->bundleName);
    }

    bool isHap = !moduleInfo->hapPath.empty();
    std::string& packagePath = isHap ? moduleInfo->hapPath : packagePathStr;
    FrontendType frontendType = GetFrontendTypeFromManifest(packagePath, srcPath, isHap);
    bool isArkApp = GetIsArkFromConfig(packagePath, isHap);

    AceApplicationInfo::GetInstance().SetAbilityName(info ? info->name : "");
    std::string moduleName = info ? info->moduleName : "";
    std::string moduleHapPath = info ? info->hapPath : "";

    std::shared_ptr<ApplicationInfo> appInfo = GetApplicationInfo();
    std::vector<ModuleInfo> moduleList = appInfo->moduleInfos;

    std::string resPath;
    for (const auto& module : moduleList) {
        if (module.moduleName == moduleName && info != nullptr) {
            std::regex pattern(ABS_BUNDLE_CODE_PATH + info->bundleName + FILE_SEPARATOR);
            auto moduleSourceDir = std::regex_replace(module.moduleSourceDir, pattern, LOCAL_BUNDLE_CODE_PATH);
            resPath = moduleSourceDir + "/assets/" + module.moduleName + FILE_SEPARATOR;
            break;
        }
    }
    std::string hapPath;
    if (!moduleHapPath.empty()) {
        if (moduleHapPath.find(ABS_BUNDLE_CODE_PATH) == std::string::npos) {
            hapPath = moduleHapPath;
        } else {
            auto pos = moduleHapPath.find_last_of('/');
            if (pos != std::string::npos) {
                hapPath = LOCAL_BUNDLE_CODE_PATH + moduleHapPath.substr(pos + 1);
                LOGI("In FA mode, hapPath:%{private}s", hapPath.c_str());
            }
        }
    }

    AceApplicationInfo::GetInstance().SetDebug(appInfo->debug, want.GetBoolParam("debugApp", false));

    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(this, pluginUtils);

    // create container
    Platform::AceContainer::CreateContainer(abilityId_, frontendType, isArkApp, srcPath, shared_from_this(),
        std::make_unique<AcePlatformEventCallback>([this]() { TerminateAbility(); },
            [this](const std::string& address) {
                AAFwk::Want want;
                want.AddEntity(Want::ENTITY_BROWSER);
                want.SetParam("address", address);
                this->StartAbility(want);
            }),
        false, useNewPipe);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("container is null, set configuration failed.");
        return;
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
    container->SetBundlePath(abilityContext->GetBundleCodeDir());
    container->SetFilesDataPath(abilityContext->GetFilesDir());
    if (window->IsDecorEnable()) {
        LOGI("AceAbility: Container modal is enabled.");
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }
    container->SetWindowName(window->GetWindowName());
    container->SetWindowId(window->GetWindowId());
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), abilityId_);
    // create view.
    auto flutterAceView = Platform::FlutterAceView::CreateView(abilityId_);
    Platform::FlutterAceView::SurfaceCreated(flutterAceView, window);

    if (srcPath.empty()) {
        auto assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    } else {
        auto assetBasePathStr = { "assets/js/" + srcPath + "/", std::string("assets/js/share/") };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    }

    /* Note: DO NOT modify the sequence of adding libPath  */
    std::string nativeLibraryPath = appInfo->nativeLibraryPath;
    std::string quickFixLibraryPath = appInfo->appQuickFix.deployedAppqfInfo.nativeLibraryPath;
    std::vector<std::string> libPaths;
    if (!quickFixLibraryPath.empty()) {
        std::string libPath = GenerateFullPath(GetBundleCodePath(), quickFixLibraryPath);
        libPaths.push_back(libPath);
        LOGI("napi quick fix lib path = %{private}s", libPath.c_str());
    }
    if (!nativeLibraryPath.empty()) {
        std::string libPath = GenerateFullPath(GetBundleCodePath(), nativeLibraryPath);
        libPaths.push_back(libPath);
        LOGI("napi lib path = %{private}s", libPath.c_str());
    }
    if (!libPaths.empty()) {
        Platform::AceContainer::AddLibPath(abilityId_, libPaths);
    }

    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [window, id = abilityId_, flutterAceView, rsUiDirector](
                       const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) mutable {
            if (rsUiDirector) {
                rsUiDirector->SetUITaskRunner(
                    [taskExecutor = Platform::AceContainer::GetContainer(id)->GetTaskExecutor(), id](
                        const std::function<void()>& task) {
                        ContainerScope scope(id);
                        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
                    });
                if (context != nullptr) {
                    context->SetRSUIDirector(rsUiDirector);
                }
                flutterAceView->InitIOManager(Platform::AceContainer::GetContainer(id)->GetTaskExecutor());
                LOGI("Init Rosen Backend");
            } else {
                LOGI("not Init Rosen Backend");
            }
        };
#endif
        // set view
        Platform::AceContainer::SetView(flutterAceView, density_, 0, 0, window, callback);
    } else {
        Platform::AceContainer::SetViewNew(flutterAceView, density_, 0, 0, window);
    }

    Platform::FlutterAceView::SurfaceChanged(flutterAceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);

    // action event handler
    auto&& actionEventHandler = [this](const std::string& action) {
        LOGI("on Action called to event handler");

        auto eventAction = JsonUtil::ParseJsonString(action);
        auto bundleName = eventAction->GetValue("bundleName");
        auto abilityName = eventAction->GetValue("abilityName");
        auto params = eventAction->GetValue("params");
        auto bundle = bundleName->GetString();
        auto ability = abilityName->GetString();
        LOGI("bundle:%{public}s ability:%{public}s, params:%{public}s", bundle.c_str(), ability.c_str(),
            params->GetString().c_str());
        if (bundle.empty() || ability.empty()) {
            LOGE("action ability or bundle is empty");
            return;
        }

        AAFwk::Want want;
        want.SetElementName(bundle, ability);
        this->StartAbility(want);
    };

    // set window id & action event handler
    auto context = Platform::AceContainer::GetContainer(abilityId_)->GetPipelineContext();
    if (context) {
        context->SetActionEventHandler(actionEventHandler);
        context->SetGetWindowRectImpl([window]() -> Rect {
            Rect rect;
            if (!window) {
                return rect;
            }
            auto windowRect = window->GetRect();
            rect.SetRect(windowRect.posX_, windowRect.posY_, windowRect.width_, windowRect.height_);
            return rect;
        });
    }

    // get url
    std::string parsedPageUrl;
    if (!remotePageUrl_.empty()) {
        parsedPageUrl = remotePageUrl_;
    } else if (!pageUrl_.empty()) {
        parsedPageUrl = pageUrl_;
    } else if (want.HasParameter(PAGE_URI)) {
        parsedPageUrl = want.GetStringParam(PAGE_URI);
    } else {
        parsedPageUrl = "";
    }

    // run page.
    Platform::AceContainer::RunPage(abilityId_, Platform::AceContainer::GetContainer(abilityId_)->GeneratePageId(),
        parsedPageUrl, want.GetStringParam(START_PARAMS_KEY));

    if (!remoteData_.empty()) {
        Platform::AceContainer::OnRestoreData(abilityId_, remoteData_);
    }
    LOGI("AceAbility::OnStart called End");
}

void AceAbility::OnStop()
{
    LOGI("AceAbility::OnStop called ");
    Ability::OnStop();
    Platform::AceContainer::DestroyContainer(abilityId_);
    abilityId_ = -1;
    LOGI("AceAbility::OnStop called End");
}

void AceAbility::OnActive()
{
    LOGI("AceAbility::OnActive called ");
    Ability::OnActive();
    Platform::AceContainer::OnActive(abilityId_);
    LOGI("AceAbility::OnActive called End");
}

void AceAbility::OnForeground(const Want& want)
{
    LOGI("AceAbility::OnForeground called ");
    Ability::OnForeground(want);
    Platform::AceContainer::OnShow(abilityId_);
    LOGI("AceAbility::OnForeground called End");
}

void AceAbility::OnBackground()
{
    LOGI("AceAbility::OnBackground called ");
    Ability::OnBackground();
    Platform::AceContainer::OnHide(abilityId_);
    LOGI("AceAbility::OnBackground called End");
}

void AceAbility::OnInactive()
{
    LOGI("AceAbility::OnInactive called ");
    Ability::OnInactive();
    Platform::AceContainer::OnInactive(abilityId_);
    LOGI("AceAbility::OnInactive called End");
}

void AceAbility::OnBackPressed()
{
    LOGI("AceAbility::OnBackPressed called ");
    if (!Platform::AceContainer::OnBackPressed(abilityId_)) {
        LOGI("AceAbility::OnBackPressed: passed to Ability to process");
        Ability::OnBackPressed();
    }
    LOGI("AceAbility::OnBackPressed called End");
}

void AceAbility::OnNewWant(const Want& want)
{
    LOGI("AceAbility::OnNewWant called ");
    Ability::OnNewWant(want);
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(abilityId_, params);
    std::string data = want.ToString();
    Platform::AceContainer::OnNewWant(abilityId_, data);
    LOGI("AceAbility::OnNewWant called End");
}

void AceAbility::OnRestoreAbilityState(const PacMap& inState)
{
    LOGI("AceAbility::OnRestoreAbilityState called ");
    Ability::OnRestoreAbilityState(inState);
    LOGI("AceAbility::OnRestoreAbilityState called End");
}

void AceAbility::OnSaveAbilityState(PacMap& outState)
{
    LOGI("AceAbility::OnSaveAbilityState called ");
    Ability::OnSaveAbilityState(outState);
    LOGI("AceAbility::OnSaveAbilityState called End");
}

void AceAbility::OnConfigurationUpdated(const Configuration& configuration)
{
    LOGI("AceAbility::OnConfigurationUpdated called ");
    Ability::OnConfigurationUpdated(configuration);
    Platform::AceContainer::OnConfigurationUpdated(abilityId_, configuration.GetName());

    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("AceAbility container is null");
        return;
    }
    auto colorMode = configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
    auto deviceAccess = configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
    auto languageTag = configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
    container->UpdateConfiguration(colorMode, deviceAccess, languageTag);
    LOGI("AceAbility::OnConfigurationUpdated called End, name:%{public}s", configuration.GetName().c_str());
}

void AceAbility::OnAbilityResult(int requestCode, int resultCode, const OHOS::AAFwk::Want& resultData)
{
    LOGI("AceAbility::OnAbilityResult called ");
    AbilityProcess::GetInstance()->OnAbilityResult(this, requestCode, resultCode, resultData);
    LOGI("AceAbility::OnAbilityResult called End");
}

bool AceAbility::OnStartContinuation()
{
    LOGI("AceAbility::OnStartContinuation called.");
    bool ret = Platform::AceContainer::OnStartContinuation(abilityId_);
    LOGI("AceAbility::OnStartContinuation finish.");
    return ret;
}

bool AceAbility::OnSaveData(OHOS::AAFwk::WantParams& saveData)
{
    LOGI("AceAbility::OnSaveData called.");
    std::string data = Platform::AceContainer::OnSaveData(abilityId_);
    if (data == "false") {
        return false;
    }
    auto json = JsonUtil::ParseJsonString(data);
    if (!json) {
        return false;
    }
    if (json->Contains(PAGE_URI)) {
        saveData.SetParam(PAGE_URI, OHOS::AAFwk::String::Box(json->GetString(PAGE_URI)));
    }
    if (json->Contains(CONTINUE_PARAMS_KEY)) {
        std::string params = json->GetObject(CONTINUE_PARAMS_KEY)->ToString();
        saveData.SetParam(CONTINUE_PARAMS_KEY, OHOS::AAFwk::String::Box(params));
    }
    LOGI("AceAbility::OnSaveData finish.");
    return true;
}

bool AceAbility::OnRestoreData(OHOS::AAFwk::WantParams& restoreData)
{
    LOGI("AceAbility::OnRestoreData called.");
    if (restoreData.HasParam(PAGE_URI)) {
        auto value = restoreData.GetParam(PAGE_URI);
        OHOS::AAFwk::IString* ao = OHOS::AAFwk::IString::Query(value);
        if (ao != nullptr) {
            remotePageUrl_ = OHOS::AAFwk::String::Unbox(ao);
        }
    }
    if (restoreData.HasParam(CONTINUE_PARAMS_KEY)) {
        auto value = restoreData.GetParam(CONTINUE_PARAMS_KEY);
        OHOS::AAFwk::IString* ao = OHOS::AAFwk::IString::Query(value);
        if (ao != nullptr) {
            remoteData_ = OHOS::AAFwk::String::Unbox(ao);
        }
    }
    LOGI("AceAbility::OnRestoreData finish.");
    return true;
}

void AceAbility::OnCompleteContinuation(int result)
{
    Ability::OnCompleteContinuation(result);
    LOGI("AceAbility::OnCompleteContinuation called.");
    Platform::AceContainer::OnCompleteContinuation(abilityId_, result);
    LOGI("AceAbility::OnCompleteContinuation finish.");
}

void AceAbility::OnRemoteTerminated()
{
    LOGI("AceAbility::OnRemoteTerminated called.");
    Platform::AceContainer::OnRemoteTerminated(abilityId_);
    LOGI("AceAbility::OnRemoteTerminated finish.");
}

void AceAbility::OnSizeChange(const OHOS::Rosen::Rect& rect, OHOS::Rosen::WindowSizeChangeReason reason)
{
    LOGI("AceAbility::OnSizeChange width: %{public}u, height: %{public}u, left: %{public}d, top: %{public}d",
        rect.width_, rect.height_, rect.posX_, rect.posY_);
    SystemProperties::SetDeviceOrientation(rect.height_ >= rect.width_ ? 0 : 1);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("OnSizeChange: container is null.");
        return;
    }
    container->SetWindowPos(rect.posX_, rect.posY_);
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetDisplayWindowRectInfo(
            Rect(Offset(rect.posX_, rect.posY_), Size(rect.width_, rect.height_)));
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("OnSizeChange: taskExecutor is null.");
        return;
    }
    taskExecutor->PostTask(
        [rect, density = density_, reason, container]() {
            auto flutterAceView = static_cast<Platform::FlutterAceView*>(container->GetView());
            if (!flutterAceView) {
                LOGE("OnSizeChange: flutterAceView is null.");
                return;
            }
            flutter::ViewportMetrics metrics;
            metrics.physical_width = rect.width_;
            metrics.physical_height = rect.height_;
            metrics.device_pixel_ratio = density;
            Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);
            Platform::FlutterAceView::SurfaceChanged(flutterAceView, rect.width_, rect.height_,
                rect.height_ >= rect.width_ ? 0 : 1, static_cast<WindowSizeChangeReason>(reason));
        },
        TaskExecutor::TaskType::PLATFORM);
}

void AceAbility::OnModeChange(OHOS::Rosen::WindowMode mode)
{
    LOGI("OnModeChange, window mode is %{public}d", mode);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("OnModeChange failed, get container(id=%{public}d) failed", abilityId_);
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("OnModeChange failed: taskExecutor is null.");
        return;
    }
    ContainerScope scope(abilityId_);
    taskExecutor->PostTask(
        [container, mode]() {
            auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
            if (!pipelineContext) {
                LOGE("OnModeChange failed, pipeline context is null.");
                return;
            }
            if (mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FULLSCREEN ||
                mode == OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
                mode == OHOS::Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY) {
                pipelineContext->ShowContainerTitle(false);
            } else {
                pipelineContext->ShowContainerTitle(true);
            }
        },
        TaskExecutor::TaskType::UI);
}

void AceAbility::OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info)
{
    auto rect = info->rect_;
    auto type = info->type_;
    Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
    LOGI("AceAbility::OccupiedAreaChange rect:%{public}s type: %{public}d", keyboardRect.ToString().c_str(), type);
    if (type == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT) {
        auto container = Platform::AceContainer::GetContainer(abilityId_);
        if (!container) {
            LOGE("container may be destroyed.");
            return;
        }
        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            LOGE("OnSizeChange: taskExecutor is null.");
            return;
        }

        ContainerScope scope(abilityId_);
        taskExecutor->PostTask(
            [container, keyboardRect] {
                auto context = container->GetPipelineContext();
                if (context) {
                    context->OnVirtualKeyboardAreaChange(keyboardRect);
                }
            },
            TaskExecutor::TaskType::UI);
    }
}

void AceAbility::Dump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("container may be destroyed.");
        return;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("OnSizeChange: taskExecutor is null.");
        return;
    }
    ContainerScope scope(abilityId_);
    taskExecutor->PostSyncTask(
        [container, params, &info] {
            auto context = container->GetPipelineContext();
            if (context != nullptr) {
                context->DumpInfo(params, info);
            }
        },
        TaskExecutor::TaskType::UI);
}

void AceAbility::OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
{
    LOGI("AceAbility::OnDrag called ");
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("container may be destroyed.");
        return;
    }
    auto flutterAceView = static_cast<Platform::FlutterAceView*>(container->GetView());
    if (!flutterAceView) {
        LOGE("AceAbility::OnDrag flutterAceView is null");
        return;
    }

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

    flutterAceView->ProcessDragEvent(x, y, action);
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("OnPointerInputEvent: container may be destroyed.");
        return false;
    }
    auto flutterAceView = static_cast<Platform::FlutterAceView*>(container->GetView());
    if (!flutterAceView) {
        LOGE("OnPointerInputEvent: flutterAceView is null.");
        return false;
    }
    flutterAceView->DispatchTouchEvent(flutterAceView, pointerEvent);
    return true;
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("OnInputEvent: container may be destroyed.");
        return false;
    }
    auto flutterAceView = static_cast<Platform::FlutterAceView*>(container->GetView());
    if (!flutterAceView) {
        LOGI("OnInputEvent: flutterAceView is null, keyboard event does not take effect.");
        return false;
    }
    int32_t keyCode = keyEvent->GetKeyCode();
    int32_t keyAction = keyEvent->GetKeyAction();
    if (keyCode == MMI::KeyEvent::KEYCODE_BACK && keyAction == MMI::KeyEvent::KEY_ACTION_UP) {
        LOGI("OnInputEvent: Platform::AceContainer::OnBackPressed called");
        if (Platform::AceContainer::OnBackPressed(abilityId_)) {
            LOGI("OnInputEvent: Platform::AceContainer::OnBackPressed return true");
            return true;
        }
        LOGI("OnInputEvent: Platform::AceContainer::OnBackPressed return false");
        return false;
    }
    LOGI("OnInputEvent: dispatch key to arkui");
    if (flutterAceView->DispatchKeyEvent(flutterAceView, keyEvent)) {
        LOGI("OnInputEvent: arkui consumed this key event");
        return true;
    }
    LOGI("OnInputEvent: arkui do not consumed this key event");
    return false;
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const
{
    return false;
}

void AceAbility::SetBackgroundColor(uint32_t color)
{
    LOGI("AceAbilityHandler::SetBackgroundColor color is %{public}u", color);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("SetBackgroundColor failed: container is null.");
        return;
    }
    ContainerScope scope(abilityId_);
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("SetBackgroundColor failed: taskExecutor is null.");
        return;
    }
    taskExecutor->PostSyncTask(
        [container, bgColor = color]() {
            auto pipelineContext = container->GetPipelineContext();
            if (!pipelineContext) {
                LOGE("SetBackgroundColor failed, pipeline context is null.");
                return;
            }
            pipelineContext->SetAppBgColor(Color(bgColor));
        },
        TaskExecutor::TaskType::UI);
}

uint32_t AceAbility::GetBackgroundColor()
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("AceAbilityHandler GetBackgroundColor failed: container is null. return 0x000000");
        return 0x000000;
    }
    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        LOGE("AceAbilityHandler GetBackgroundColor failed: taskExecutor is null.");
        return 0x000000;
    }
    ContainerScope scope(abilityId_);
    uint32_t bgColor = 0x000000;
    taskExecutor->PostSyncTask(
        [&bgColor, container]() {
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
        },
        TaskExecutor::TaskType::UI);

    LOGI("AceAbilityHandler::GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}
} // namespace Ace
} // namespace OHOS
