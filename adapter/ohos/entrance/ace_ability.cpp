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

#include "adapter/ohos/entrance/ace_ability.h"

#include "ability_process.h"
#include "display_type.h"
#include "init_data.h"
#include "res_config.h"
#include "resource_manager.h"
#include "string_wrapper.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

#include "adapter/ohos/entrance/ace_application_info.h"
#include "adapter/ohos/entrance/ace_container.h"
#include "adapter/ohos/entrance/flutter_ace_view.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/log/log.h"
#include "base/utils/system_properties.h"
#include "core/common/frontend.h"
#include "core/common/plugin_manager.h"

namespace OHOS {
namespace Ace {
namespace {

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

FrontendType GetFrontendTypeFromManifest(const std::string& packagePathStr, const std::string& srcPath)
{
    std::string manifest = std::string("assets/js/default/manifest.json");
    if (!srcPath.empty()) {
        manifest = "assets/js/" + srcPath + "/manifest.json";
    }
    auto manifestPath = packagePathStr + manifest;
    char realPath[PATH_MAX] = { 0x00 };
    if (realpath(manifestPath.c_str(), realPath) == nullptr) {
        LOGE("realpath fail! filePath: %{private}s, fail reason: %{public}s", manifestPath.c_str(), strerror(errno));
        LOGE("return default frontend: JS frontend.");
        return FrontendType::JS;
    }
    std::unique_ptr<FILE, decltype(&fclose)> file(fopen(realPath, "rb"), fclose);
    if (!file) {
        LOGE("open file failed, filePath: %{private}s, fail reason: %{public}s", manifestPath.c_str(), strerror(errno));
        LOGE("return default frontend: JS frontend.");
        return FrontendType::JS;
    }
    if (std::fseek(file.get(), 0, SEEK_END) != 0) {
        LOGE("seek file tail error, return default frontend: JS frontend.");
        return FrontendType::JS;
    }

    long size = std::ftell(file.get());
    if (size == -1L) {
        return FrontendType::JS;
    }
    char* fileData = new (std::nothrow) char[size];
    if (fileData == nullptr) {
        LOGE("new json buff failed, return default frontend: JS frontend.");
        return FrontendType::JS;
    }
    rewind(file.get());
    std::unique_ptr<char[]> jsonStream(fileData);
    size_t result = std::fread(jsonStream.get(), 1, size, file.get());
    if (result != (size_t)size) {
        LOGE("read file failed, return default frontend: JS frontend.");
        return FrontendType::JS;
    }

    std::string jsonString(jsonStream.get(), jsonStream.get() + size);
    auto rootJson = JsonUtil::ParseJsonString(jsonString);
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
class AcePlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit AcePlatformEventCallback(AcePlatformFinish onFinish) : onFinish_(onFinish) {}

    ~AcePlatformEventCallback() = default;

    virtual void OnFinish() const
    {
        LOGI("AcePlatformEventCallback OnFinish");
        if (onFinish_) {
            onFinish_();
        }
    }

    virtual void OnStatusBarBgColorChanged(uint32_t color)
    {
        LOGI("AcePlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    AcePlatformFinish onFinish_;
};

int32_t AceAbility::instanceId_ = 0;
const std::string AceAbility::START_PARAMS_KEY = "__startParams";
const std::string AceAbility::PAGE_URI = "url";
const std::string AceAbility::CONTINUE_PARAMS_KEY = "__remoteData";

REGISTER_AA(AceAbility)

void AceAbility::OnStart(const Want& want)
{
    Ability::OnStart(want);
    LOGI("AceAbility::OnStart called");

    SetHwIcuDirectory();

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
    } else {
       LOGW("resourceManager is null.");
       AceApplicationInfo::GetInstance().SetLocale("", "", "", "");
    }

    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    if (moduleInfo != nullptr) {
        packagePathStr += "/" + moduleInfo->name + "/";
    }
    std::shared_ptr<AbilityInfo> info = GetAbilityInfo();
    std::string srcPath = "";
    if (info != nullptr && !info->srcPath.empty()) {
        srcPath = info->srcPath;
    }
    if (info != nullptr && !info->bundleName.empty()) {
        AceApplicationInfo::GetInstance().SetPackageName(info->bundleName);
    }

    FrontendType frontendType = GetFrontendTypeFromManifest(packagePathStr, srcPath);
    bool isArkApp = GetIsArkFromConfig(packagePathStr);

    std::string moduleName = info->moduleName;
    std::shared_ptr<ApplicationInfo> appInfo = GetApplicationInfo();
    std::vector<ModuleInfo> moduleList = appInfo->moduleInfos;

    std::string resPath;
    for (auto module : moduleList) {
        if (module.moduleName == moduleName) {
            resPath = module.moduleSourceDir + "/assets/" + module.moduleName + "/";
            break;
        }
    }

    AceApplicationInfo::GetInstance().SetDebug(appInfo->debug, want.GetBoolParam("debugApp", false));

    // create container
    Platform::AceContainer::CreateContainer(abilityId_, frontendType, isArkApp, srcPath, this,
        std::make_unique<AcePlatformEventCallback>([this]() { TerminateAbility(); }));
    auto container = Platform::AceContainer::GetContainer(abilityId_);
    if (!container) {
        LOGE("container is null, set configuration failed.");
    } else {
        auto aceResCfg = container->GetResourceConfiguration();
        aceResCfg.SetOrientation(SystemProperties::GetDevcieOrientation());
        aceResCfg.SetDensity(SystemProperties::GetResolution());
        aceResCfg.SetDeviceType(SystemProperties::GetDeviceType());
        container->SetResourceConfiguration(aceResCfg);
        container->SetPackagePathStr(resPath);
    }
    PluginManager::GetInstance().SetAceAbility(this);
    // create view.
    auto flutterAceView = Platform::FlutterAceView::CreateView(abilityId_);
    OHOS::sptr<OHOS::Rosen::Window> window = Ability::GetWindow();

    // register surface change callback
    OHOS::sptr<OHOS::Rosen::IWindowChangeListener> thisAbility(this);
    window->RegisterWindowChangeListener(thisAbility);

    Platform::FlutterAceView::SurfaceCreated(flutterAceView, window);

    // set metrics
    int32_t width = window->GetRect().width_;
    int32_t height = window->GetRect().height_;
    LOGI("AceAbility: windowConfig: width: %{public}d, height: %{public}d", width, height);

    flutter::ViewportMetrics metrics;
    metrics.physical_width = width;
    metrics.physical_height = height;
    metrics.device_pixel_ratio = density_;
    Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);

    if (srcPath.empty()) {
        auto assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);
    } else {
        auto assetBasePathStr = { "assets/js/" + srcPath + "/" };
        Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);
    }

    // set view
    Platform::AceContainer::SetView(flutterAceView, density_, width, height);
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, width, height, 0);

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

    // action event hadnler
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
        // want.SetParam(Constants::PARAM_FORM_IDENTITY_KEY, std::to_string(formJsInfo_.formId));
        this->StartAbility(want);
    };

    // set window id & action event handler
    auto context = Platform::AceContainer::GetContainer(abilityId_)->GetPipelineContext();
    if (context != nullptr) {
        context->SetActionEventHandler(actionEventHandler);
    }

#ifdef ENABLE_ROSEN_BACKEND
    if (SystemProperties::GetRosenBackendEnabled()) {
        auto rsUiDirector = OHOS::Rosen::RSUIDirector::Create();
        if (rsUiDirector != nullptr) {
            rsUiDirector->SetRSSurfaceNode(window->GetSurfaceNode());

            // todo regist on size change()
            window->RegisterWindowChangeListener(thisAbility);

            rsUiDirector->SetSurfaceNodeSize(width, height);
            rsUiDirector->SetUITaskRunner(
                [taskExecutor = Platform::AceContainer::GetContainer(abilityId_)->GetTaskExecutor()]
                    (const std::function<void()>& task) {
                        taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
                    });
            if (context != nullptr) {
                context->SetRSUIDirector(rsUiDirector);
            }
            rsUiDirector->Init();
            LOGI("Init Rosen Backend");
        }
    } else {
        LOGI("not Init Rosen Backend");
    }
#else
    LOGI("no macro Init Rosen Backend");
#endif

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
#ifdef ENABLE_ROSEN_BACKEND
    if (auto context = Platform::AceContainer::GetContainer(abilityId_)->GetPipelineContext()) {
        context->SetRSUIDirector(nullptr);
    }
#endif
    Ability::OnStop();
    Platform::AceContainer::DestroyContainer(abilityId_);
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

void AceAbility::OnPointerEvent(std::shared_ptr<MMI::PointerEvent>& pointerEvent)
{
    LOGI("AceAbility::OnPointerEvent called ");
    auto flutterAceView = static_cast<Platform::FlutterAceView*>(
        Platform::AceContainer::GetContainer(abilityId_)->GetView());
    if (!flutterAceView) {
        LOGE("flutterAceView is null");
        return;
    }
    flutterAceView->DispatchTouchEvent(flutterAceView, pointerEvent);
}

void AceAbility::OnNewWant(const Want& want)
{
    LOGI("AceAbility::OnNewWant called ");
    Ability::OnNewWant(want);
    std::string params = want.GetStringParam(START_PARAMS_KEY);
    Platform::AceContainer::OnNewRequest(abilityId_, params);
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
    LOGI("AceAbility::OnConfigurationUpdated called End");
}

void AceAbility::OnAbilityResult(int requestCode, int resultCode, const OHOS::AAFwk::Want& resultData)
{
    LOGI("AceAbility::OnAbilityResult called ");
    AbilityProcess::GetInstance()->OnAbilityResult(this, requestCode, resultCode, resultData);
    LOGI("AceAbility::OnAbilityResult called End");
}

void AceAbility::OnRequestPermissionsFromUserResult(
    int requestCode, const std::vector<std::string>& permissions, const std::vector<int>& grantResults)
{
    LOGI("AceAbility::OnRequestPermissionsFromUserResult called ");
    AbilityProcess::GetInstance()->OnRequestPermissionsFromUserResult(this, requestCode, permissions, grantResults);
    LOGI("AceAbility::OnRequestPermissionsFromUserResult called End");
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

void AceAbility::OnSizeChange(OHOS::Rosen::Rect rect)
{
    uint32_t width = rect.width_;
    uint32_t height = rect.height_;
#ifdef ENABLE_ROSEN_BACKEND
    auto context = Platform::AceContainer::GetContainer(abilityId_)->GetPipelineContext();
    if (context) {
        auto rsUIDirector = context->GetRSUIDirector();
        if (rsUIDirector) {
            rsUIDirector->SetSurfaceNodeSize(width, height);
        } else {
            LOGE("ceAbility::OnSizeChange rsUIDirector is null.");
        }
    } else {
        LOGE("ceAbility::OnSizeChange pipline context is null.");
    }

#endif
    auto flutterAceView = static_cast<Platform::FlutterAceView*>(
        Platform::AceContainer::GetContainer(abilityId_)->GetView());

    if (!flutterAceView) {
        LOGE("flutterAceView is null");
        return;
    }

    flutter::ViewportMetrics metrics;
    metrics.physical_width = width;
    metrics.physical_height = height;
    metrics.device_pixel_ratio = density_;
    Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, width, height, 0);
}

} // namespace Ace
} // namespace OHOS
