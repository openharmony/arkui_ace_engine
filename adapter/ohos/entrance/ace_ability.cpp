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

#include "adapter/ohos/entrance/ace_ability.h"

#include <ui/rs_surface_node.h>

#include "ability_process.h"
#include "dm/display_manager.h"
#include "form_utils_impl.h"
#include "ohos/init_data.h"
#include "ipc_skeleton.h"
#include "res_config.h"
#include "resource_manager.h"
#include "session_info.h"
#include "string_wrapper.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/ace_new_pipe_judgement.h"
#include "adapter/ohos/entrance/ace_view_ohos.h"
#include "adapter/ohos/entrance/capability_registry.h"
#include "adapter/ohos/entrance/plugin_utils_impl.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/geometry/rect.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/container_scope.h"
#include "core/common/form_manager.h"
#include "core/common/frontend.h"
#include "core/common/layout_inspector.h"
#include "core/common/plugin_manager.h"
#include "core/common/plugin_utils.h"
#include "core/image/image_file_cache.h"
namespace OHOS {
namespace Ace {
namespace {

const std::string ABS_BUNDLE_CODE_PATH = "/data/app/el1/bundle/public/";
const std::string LOCAL_BUNDLE_CODE_PATH = "/data/storage/el1/bundle/";
const std::string FILE_SEPARATOR = "/";
const std::string ACTION_VIEWDATA = "ohos.want.action.viewData";
constexpr int32_t PLATFORM_VERSION_TEN = 10;

FrontendType GetFrontendType(const std::string& frontendType)
{
    if (frontendType == "normal") {
        return FrontendType::JS;
    } else if (frontendType == "form") {
        return FrontendType::JS_CARD;
    } else if (frontendType == "declarative") {
        return FrontendType::DECLARATIVE_JS;
    } else {
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
        return FrontendType::JS;
    }
    auto rootJson = JsonUtil::ParseJsonString(jsonStr);
    if (rootJson == nullptr) {
        return FrontendType::JS;
    }
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
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStartAbility(const std::string& address) override
    {
        LOGI("AcePlatformEventCallback OnStartAbility");
        CHECK_NULL_VOID(onStartAbility_);
        onStartAbility_(address);
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

void AceWindowListener::OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnSizeChange(info, rsTransaction);
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

void AceWindowListener::OnSizeChange(OHOS::Rosen::Rect rect, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnSizeChange(rect, reason, rsTransaction);
}

void AceWindowListener::OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco)
{
    CHECK_NULL_VOID(callbackOwner_);
    callbackOwner_->OnModeChange(mode, hasDeco);
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

void AceWindowListener::OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea avoidArea, OHOS::Rosen::AvoidAreaType type)
{
    CHECK_NULL_VOID(callbackOwner_);
    return callbackOwner_->OnAvoidAreaChanged(avoidArea, type);
}

AceAbility::AceAbility() = default;

void AceAbility::OnStart(const Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    Ability::OnStart(want, sessionInfo);
    abilityId_ = Container::GenerateId<FA_CONTAINER>();
    static std::once_flag onceFlag;
    auto abilityContext = GetAbilityContext();
    auto cacheDir = abilityContext->GetCacheDir();
    std::call_once(onceFlag, [abilityContext, cacheDir]() {
        SetHwIcuDirectory();
        Container::UpdateCurrent(INSTANCE_ID_PLATFORM);
        CapabilityRegistry::Register();
        AceApplicationInfo::GetInstance().SetPackageName(abilityContext->GetBundleName());
        AceApplicationInfo::GetInstance().SetDataFileDirPath(abilityContext->GetFilesDir());
        AceApplicationInfo::GetInstance().SetApiTargetVersion(abilityContext->GetApplicationInfo()->apiTargetVersion);
        AceApplicationInfo::GetInstance().SetAppVersionName(abilityContext->GetApplicationInfo()->versionName);
        AceApplicationInfo::GetInstance().SetAppVersionCode(abilityContext->GetApplicationInfo()->versionCode);
        AceApplicationInfo::GetInstance().SetUid(IPCSkeleton::GetCallingUid());
        AceApplicationInfo::GetInstance().SetPid(IPCSkeleton::GetCallingRealPid());
        ImageFileCache::GetInstance().SetImageCacheFilePath(cacheDir);
        ImageFileCache::GetInstance().SetCacheFileInfo();
        AceEngine::InitJsDumpHeadSignal();
    });
    AceNewPipeJudgement::InitAceNewPipeConfig();
    // now choose pipeline using param set as package name, later enable for all.
    auto apiCompatibleVersion = abilityContext->GetApplicationInfo()->apiCompatibleVersion;
    auto apiReleaseType = abilityContext->GetApplicationInfo()->apiReleaseType;
    auto apiTargetVersion = abilityContext->GetApplicationInfo()->apiTargetVersion;
    auto useNewPipe = AceNewPipeJudgement::QueryAceNewPipeEnabledFA(
        AceApplicationInfo::GetInstance().GetPackageName(), apiCompatibleVersion, apiTargetVersion, apiReleaseType);
    LOGI("AceAbility OnStart called, apiCompatibleVersion: %{public}d, apiTargetVersion: %{public}d, "
         "and apiReleaseType: %{public}s, useNewPipe: %{public}d",
        apiCompatibleVersion, apiTargetVersion, apiReleaseType.c_str(), useNewPipe);
    OHOS::sptr<OHOS::Rosen::Window> window = Ability::GetWindow();
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
        LOGI("deviceWidth: %{public}d, deviceHeight: %{public}d, default density: %{public}f", deviceWidth,
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
    CHECK_NULL_VOID(moduleInfo);
    packagePathStr += "/" + moduleInfo->package + "/";
    std::shared_ptr<AbilityInfo> info = GetAbilityInfo();
    std::string srcPath;
    if (info != nullptr && !info->srcPath.empty()) {
        srcPath = info->srcPath;
    }
    if (info != nullptr && !info->bundleName.empty()) {
        AceApplicationInfo::GetInstance().SetPackageName(info->bundleName);
    }

    bool isHap = moduleInfo ? !moduleInfo->hapPath.empty() : false;
    std::string& packagePath = isHap ? moduleInfo->hapPath : packagePathStr;
    FrontendType frontendType = GetFrontendTypeFromManifest(packagePath, srcPath, isHap);
    useNewPipe = useNewPipe && (frontendType == FrontendType::ETS_CARD || frontendType == FrontendType::DECLARATIVE_JS);
#ifdef ENABLE_ROSEN_BACKEND
    std::shared_ptr<OHOS::Rosen::RSUIDirector> rsUiDirector;
#ifndef NG_BUILD
    if (SystemProperties::GetRosenBackendEnabled() && !useNewPipe) {
        rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        auto surfaceNode = window->GetSurfaceNode();
        rsUiDirector->SetRSSurfaceNode(surfaceNode);
        rsUiDirector->SetCacheDir(cacheDir);
        rsUiDirector->Init();
    }
#endif
#endif
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

#ifdef PLUGIN_COMPONENT_SUPPORTED
    auto pluginUtils = std::make_shared<PluginUtilsImpl>();
    PluginManager::GetInstance().SetAceAbility(this, pluginUtils);
#endif
#ifdef FORM_SUPPORTED
    auto formUtils = std::make_shared<FormUtilsImpl>();
    FormManager::GetInstance().SetFormUtils(formUtils);
#endif
    // create container
    Platform::AceContainer::CreateContainer(abilityId_, frontendType, srcPath, shared_from_this(),
        std::make_unique<AcePlatformEventCallback>([this]() { TerminateAbility(); },
            [this](const std::string& address) {
                AAFwk::Want want;
                want.AddEntity(Want::ENTITY_BROWSER);
                want.SetUri(address);
                want.SetAction(ACTION_VIEWDATA);
                this->StartAbility(want);
            }),
        false, useNewPipe);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    container->SetToken(token_);
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
        LOGI("Container modal is enabled.");
        container->SetWindowModal(WindowModal::CONTAINER_MODAL);
    }
    container->SetWindowName(window->GetWindowName());
    container->SetWindowId(window->GetWindowId());
    SubwindowManager::GetInstance()->AddContainerId(window->GetWindowId(), abilityId_);
    // create view.
    auto aceView = Platform::AceViewOhos::CreateView(abilityId_);
    Platform::AceViewOhos::SurfaceCreated(aceView, window);

    if (srcPath.empty()) {
        auto assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    } else {
        auto assetBasePathStr = { "assets/js/" + srcPath + "/", std::string("assets/js/share/"),
            std::string("assets/js/") };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    }

#ifndef NG_BUILD
    if (!useNewPipe) {
        Ace::Platform::UIEnvCallback callback = nullptr;
#ifdef ENABLE_ROSEN_BACKEND
        callback = [window, id = abilityId_, aceView, rsUiDirector](
                       const OHOS::Ace::RefPtr<OHOS::Ace::PipelineContext>& context) mutable {
            if (rsUiDirector) {
                rsUiDirector->SetUITaskRunner(
                    [taskExecutor = Platform::AceContainer::GetContainer(id)->GetTaskExecutor(), id](
                        const std::function<void()>& task, uint32_t delay) {
                        ContainerScope scope(id);
                        taskExecutor->PostDelayedTask(
                            task, TaskExecutor::TaskType::UI, delay, "ArkUIRenderServiceTask", PriorityType::HIGH);
                    }, id);
                if (context != nullptr) {
                    context->SetRSUIDirector(rsUiDirector);
                }
                LOGI("Init Rosen Backend");
            }
        };
#endif
        // set view
        Platform::AceContainer::SetView(aceView, density_, 0, 0, window, callback);
    } else {
        Platform::AceContainer::SetViewNew(aceView, density_, 0, 0, window);
    }
#else
    Platform::AceContainer::SetViewNew(aceView, density_, 0, 0, window);
#endif

    Platform::AceViewOhos::SurfaceChanged(aceView, 0, 0, deviceHeight >= deviceWidth ? 0 : 1);

    // action event handler
    auto&& actionEventHandler = [this](const std::string& action) {
        auto eventAction = JsonUtil::ParseJsonString(action);
        auto bundleName = eventAction->GetValue("bundleName");
        auto abilityName = eventAction->GetValue("abilityName");
        auto params = eventAction->GetValue("params");
        auto bundle = bundleName->GetString();
        auto ability = abilityName->GetString();
        LOGI("on Action called to event handler, bundle:%{public}s ability:%{public}s, params:%{public}s",
            bundle.c_str(), ability.c_str(), params->GetString().c_str());
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
            CHECK_NULL_RETURN(window, rect);
            auto windowRect = window->GetRect();
            rect.SetRect(windowRect.posX_, windowRect.posY_, windowRect.width_, windowRect.height_);
            return rect;
        });
        auto rsConfig = window->GetKeyboardAnimationConfig();
        KeyboardAnimationCurve curveIn = {
            rsConfig.curveIn.curveType_, rsConfig.curveIn.curveParams_, rsConfig.curveIn.duration_};
        KeyboardAnimationCurve curveOut = {
            rsConfig.curveOut.curveType_, rsConfig.curveOut.curveParams_, rsConfig.curveOut.duration_};
        KeyboardAnimationConfig config = {curveIn, curveOut};
        context->SetKeyboardAnimationConfig(config);
        context->SetMinPlatformVersion(apiCompatibleVersion);

        if (apiCompatibleVersion >= PLATFORM_VERSION_TEN && context->GetIsAppWindow()) {
            context->UpdateSystemSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_SYSTEM));
            context->UpdateCutoutSafeArea(container->GetViewSafeAreaByType(Rosen::AvoidAreaType::TYPE_CUTOUT));
        }
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

    auto windowRect = window->GetRect();
    if (!windowRect.IsUninitializedRect()) {
        LOGW("notify window rect explicitly");
        OnSizeChange(windowRect, OHOS::Rosen::WindowSizeChangeReason::UNDEFINED);
    }
    // run page.
    Platform::AceContainer::RunPage(abilityId_, parsedPageUrl, want.GetStringParam(START_PARAMS_KEY));

    if (!remoteData_.empty()) {
        Platform::AceContainer::OnRestoreData(abilityId_, remoteData_);
    }
    LayoutInspector::SetCallback(abilityId_);
}

void AceAbility::OnStop()
{
    LOGI("AceAbility OnStop called ");
    Ability::OnStop();
    Platform::AceContainer::DestroyContainer(abilityId_);
    abilityId_ = -1;
}

void AceAbility::OnActive()
{
    LOGI("AceAbility OnActive called ");
    // AbilityManager will miss first OnForeground notification
    if (isFirstActive_) {
        Platform::AceContainer::OnShow(abilityId_);
        isFirstActive_ = false;
    }
    Ability::OnActive();
    Platform::AceContainer::OnActive(abilityId_);
}

void AceAbility::OnForeground(const Want& want)
{
    LOGI("AceAbility OnForeground called ");
    Ability::OnForeground(want);
    Platform::AceContainer::OnShow(abilityId_);
}

void AceAbility::OnBackground()
{
    LOGI("AceAbility OnBackground called ");
    Ability::OnBackground();
    Platform::AceContainer::OnHide(abilityId_);
}

void AceAbility::OnInactive()
{
    LOGI("AceAbility OnInactive called ");
    Ability::OnInactive();
    Platform::AceContainer::OnInactive(abilityId_);
}

void AceAbility::OnBackPressed()
{
    LOGI("AceAbility OnBackPressed called ");
    if (!Platform::AceContainer::OnBackPressed(abilityId_)) {
        Ability::OnBackPressed();
    }
}

void AceAbility::OnNewWant(const Want& want)
{
    LOGI("AceAbility OnNewWant called ");
    Ability::OnNewWant(want);
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(abilityId_, params);
    std::string data = want.ToString();
    Platform::AceContainer::OnNewWant(abilityId_, data);
}

void AceAbility::OnRestoreAbilityState(const PacMap& inState)
{
    LOGI("AceAbility OnRestoreAbilityState called ");
    Ability::OnRestoreAbilityState(inState);
}

void AceAbility::OnSaveAbilityState(PacMap& outState)
{
    LOGI("AceAbility OnSaveAbilityState called ");
    Ability::OnSaveAbilityState(outState);
}

void AceAbility::OnConfigurationUpdated(const Configuration& configuration)
{
    Ability::OnConfigurationUpdated(configuration);

    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [weakContainer = WeakPtr<Platform::AceContainer>(container), configuration]() {
            auto container = weakContainer.Upgrade();
            CHECK_NULL_VOID(container);
            Platform::ParsedConfig parsedConfig;
            parsedConfig.colorMode = configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_COLORMODE);
            parsedConfig.deviceAccess =
                configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::INPUT_POINTER_DEVICE);
            parsedConfig.languageTag = configuration.GetItem(OHOS::AppExecFwk::GlobalConfigurationKey::SYSTEM_LANGUAGE);
            parsedConfig.direction = configuration.GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DIRECTION);
            parsedConfig.densitydpi =
                configuration.GetItem(OHOS::AppExecFwk::ConfigurationInner::APPLICATION_DENSITYDPI);
            container->UpdateConfiguration(parsedConfig, configuration.GetName());
        },
        TaskExecutor::TaskType::UI, "ArkUIAbilityUpdateConfiguration");
    LOGI("AceAbility OnConfigurationUpdated called End, name:%{public}s", configuration.GetName().c_str());
}

void AceAbility::OnAbilityResult(int requestCode, int resultCode, const OHOS::AAFwk::Want& resultData)
{
    LOGI("AceAbility OnAbilityResult called ");
    AbilityProcess::GetInstance()->OnAbilityResult(this, requestCode, resultCode, resultData);
}

bool AceAbility::OnStartContinuation()
{
    LOGI("AceAbility OnStartContinuation called.");
    bool ret = Platform::AceContainer::OnStartContinuation(abilityId_);
    return ret;
}

bool AceAbility::OnSaveData(OHOS::AAFwk::WantParams& saveData)
{
    LOGI("AceAbility OnSaveData called.");
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
    return true;
}

bool AceAbility::OnRestoreData(OHOS::AAFwk::WantParams& restoreData)
{
    LOGI("AceAbility OnRestoreData called.");
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
    return true;
}

void AceAbility::OnCompleteContinuation(int result)
{
    Ability::OnCompleteContinuation(result);
    LOGI("AceAbility OnCompleteContinuation called.");
    Platform::AceContainer::OnCompleteContinuation(abilityId_, result);
}

void AceAbility::OnRemoteTerminated()
{
    LOGI("AceAbility OnRemoteTerminated called.");
    Platform::AceContainer::OnRemoteTerminated(abilityId_);
}

void AceAbility::OnSizeChange(const OHOS::Rosen::Rect& rect, OHOS::Rosen::WindowSizeChangeReason reason,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    LOGI("width: %{public}u, height: %{public}u, left: %{public}d, top: %{public}d", rect.width_, rect.height_,
        rect.posX_, rect.posY_);
    SystemProperties::SetDeviceOrientation(rect.height_ >= rect.width_ ? 0 : 1);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    container->SetWindowPos(rect.posX_, rect.posY_);
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetDisplayWindowRectInfo(
            Rect(Offset(rect.posX_, rect.posY_), Size(rect.width_, rect.height_)));
        pipelineContext->SetIsLayoutFullScreen(
            Ability::GetWindow()->GetMode() == Rosen::WindowMode::WINDOW_MODE_FULLSCREEN);
        auto isNeedAvoidWindowMode = SystemProperties::GetNeedAvoidWindow() &&
            (Ability::GetWindow()->GetMode() == Rosen::WindowMode::WINDOW_MODE_FLOATING ||
            Ability::GetWindow()->GetMode() == Rosen::WindowMode::WINDOW_MODE_SPLIT_PRIMARY ||
            Ability::GetWindow()->GetMode() == Rosen::WindowMode::WINDOW_MODE_SPLIT_SECONDARY);
        pipelineContext->SetIsNeedAvoidWindow(isNeedAvoidWindowMode);
    }
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [rect, density = density_, reason, container, rsTransaction]() {
            auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
            CHECK_NULL_VOID(aceView);
            ViewportConfig config(rect.width_, rect.height_, density);
            Platform::AceViewOhos::SetViewportMetrics(aceView, config);
            Platform::AceViewOhos::SurfaceChanged(aceView, rect.width_, rect.height_,
                rect.height_ >= rect.width_ ? 0 : 1, static_cast<WindowSizeChangeReason>(reason), rsTransaction);
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUIAbilitySurfaceChanged");
}

void AceAbility::OnModeChange(OHOS::Rosen::WindowMode mode, bool hasDeco)
{
    LOGI("OnModeChange, window mode is %{public}d", mode);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(abilityId_);
    taskExecutor->PostTask(
        [container, mode, hasDeco]() {
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->ShowContainerTitle(mode == OHOS::Rosen::WindowMode::WINDOW_MODE_FLOATING, hasDeco);
        },
        TaskExecutor::TaskType::UI, "ArkUIWindowModeChange");
}

void AceAbility::OnSizeChange(const sptr<OHOS::Rosen::OccupiedAreaChangeInfo>& info,
    const std::shared_ptr<OHOS::Rosen::RSTransaction>& rsTransaction)
{
    auto rect = info->rect_;
    auto type = info->type_;
    Rect keyboardRect = Rect(rect.posX_, rect.posY_, rect.width_, rect.height_);
    LOGI("AceAbility OccupiedAreaChange rect:%{public}s type: %{public}d", keyboardRect.ToString().c_str(), type);
    if (type == OHOS::Rosen::OccupiedAreaType::TYPE_INPUT) {
        auto container = Platform::AceContainer::GetContainer(abilityId_);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        ContainerScope scope(abilityId_);
        taskExecutor->PostTask(
            [container, keyboardRect, rsTransaction] {
                auto context = container->GetPipelineContext();
                CHECK_NULL_VOID(context);
                context->OnVirtualKeyboardAreaChange(keyboardRect, rsTransaction);
            },
            TaskExecutor::TaskType::UI, "ArkUIAbilityVirtualKeyboardAreaChange");
    }
}

void AceAbility::Dump(const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    ContainerScope scope(abilityId_);
    taskExecutor->PostSyncTask(
        [container, params, &info] { container->Dump(params, info); },
        TaskExecutor::TaskType::UI, "ArkUIAbilityDump");
}

void AceAbility::OnDrag(int32_t x, int32_t y, OHOS::Rosen::DragEvent event)
{
    LOGI("AceAbility OnDrag called ");
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
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

    aceView->ProcessDragEvent(x, y, action);
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::PointerEvent>& pointerEvent) const
{
    auto container = AceType::DynamicCast<Platform::AceContainer>(AceEngine::Get().GetContainer(abilityId_));
    CHECK_NULL_RETURN(container, false);
    container->SetCurPointerEvent(pointerEvent);
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    CHECK_NULL_RETURN(aceView, false);
    aceView->DispatchTouchEvent(aceView, pointerEvent);
    return true;
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::KeyEvent>& keyEvent) const
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_RETURN(container, false);
    auto aceView = AceType::DynamicCast<Platform::AceViewOhos>(container->GetAceView());
    CHECK_NULL_RETURN(aceView, false);
    int32_t keyCode = keyEvent->GetKeyCode();
    int32_t keyAction = keyEvent->GetKeyAction();
    if (keyCode == MMI::KeyEvent::KEYCODE_BACK && keyAction == MMI::KeyEvent::KEY_ACTION_UP) {
        LOGI("OnInputEvent: Platform AceContainer OnBackPressed called");
        if (Platform::AceContainer::OnBackPressed(abilityId_)) {
            return true;
        }
        return false;
    }
    LOGI("OnInputEvent: dispatch key to arkui");
    if (aceView->DispatchKeyEvent(aceView, keyEvent)) {
        return true;
    }
    return false;
}

bool AceAbility::OnInputEvent(const std::shared_ptr<MMI::AxisEvent>& axisEvent) const
{
    return false;
}

void AceAbility::SetBackgroundColor(uint32_t color)
{
    LOGI("AceAbilityHandler SetBackgroundColor color is %{public}u", color);
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_VOID(container);
    ContainerScope scope(abilityId_);
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

uint32_t AceAbility::GetBackgroundColor()
{
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    CHECK_NULL_RETURN(container, 0x000000);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, 0x000000);
    ContainerScope scope(abilityId_);
    uint32_t bgColor = 0x000000;
    taskExecutor->PostSyncTask(
        [&bgColor, container]() {
            CHECK_NULL_VOID(container);
            auto pipelineContext = container->GetPipelineContext();
            CHECK_NULL_VOID(pipelineContext);
            bgColor = pipelineContext->GetAppBgColor().GetValue();
        },
        TaskExecutor::TaskType::UI, "ArkUIAbilityGetAppBackgroundColor");

    LOGI("AceAbilityHandler GetBackgroundColor, value is %{public}u", bgColor);
    return bgColor;
}

void AceAbility::OnAvoidAreaChanged(const OHOS::Rosen::AvoidArea& avoidArea, OHOS::Rosen::AvoidAreaType type)
{
    auto container = Platform::AceContainer::GetContainer((abilityId_));
    CHECK_NULL_VOID(container);
    auto pipeline = container->GetPipelineContext();
    CHECK_NULL_VOID(
        pipeline && pipeline->GetMinPlatformVersion() >= PLATFORM_VERSION_TEN && pipeline->GetIsAppWindow());
    LOGI("AceAbility OnAvoidAreaChanged type:%{public}d, avoidArea:topRect:x:%{public}d, y:%{public}d, "
         "width:%{public}d, height%{public}d",
        type, avoidArea.topRect_.posX_, avoidArea.topRect_.posY_, (int32_t)avoidArea.topRect_.width_,
        (int32_t)avoidArea.topRect_.height_);
    auto taskExecutor = container->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    auto safeArea = ConvertAvoidArea(avoidArea);
    ContainerScope scope(abilityId_);
    taskExecutor->PostTask(
        [pipeline, safeArea, type]() {
            if (type == OHOS::Rosen::AvoidAreaType::TYPE_SYSTEM) {
                pipeline->UpdateSystemSafeArea(safeArea);
            } else if (type == OHOS::Rosen::AvoidAreaType::TYPE_CUTOUT) {
                pipeline->UpdateCutoutSafeArea(safeArea);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIAbilityAvoidAreaChanged");
}

} // namespace Ace
} // namespace OHOS
