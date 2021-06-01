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

#include "adapter/ohos/cpp/ace_ability.h"

#include "adapter/ohos/cpp/ace_container.h"
#include "adapter/ohos/cpp/flutter_ace_view.h"
#include "base/log/log.h"
#include "core/common/ace_application_info.h"
#include "core/common/frontend.h"
#include "init_data.h"
#include "touch_event.h"

#include "locale_info.h"
#include "res_config.h"
#include "resource_manager.h"

namespace OHOS {
namespace Ace {
namespace {
FrontendType GetFrontendTypeFromManifest(const std::string& packagePathStr)
{
    auto manifestPath = packagePathStr + std::string("assets/js/default/manifest.json");
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
    std::string frontendType = rootJson->GetString("type");
    if (frontendType == "normal") {
        return FrontendType::JS;
    } else if (frontendType == "form") {
        return FrontendType::JS_CARD;
    } else if (frontendType == "declarative") {
        return FrontendType::DECLARATIVE_JS;
    } else {
        LOGE("frontend type not supported. return default frontend: JS frontend.");
        return FrontendType::JS;
    }
}
}

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
        AceApplicationInfo::GetInstance().SetResourceManager(resourceManager);
        if (localeInfo != nullptr) {
            auto language = localeInfo->GetLanguage();
            auto region = localeInfo->GetRegion();
            auto script = localeInfo->GetScript();
            AceApplicationInfo::GetInstance().SetLocale(
                (language == nullptr) ? "" : language,
                (region == nullptr) ? "" : region,
                (script == nullptr) ? "" : script,
                "");
        }
    }

    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    if (moduleInfo != nullptr) {
        packagePathStr += "/" + moduleInfo->name + "/";
    }
    FrontendType frontendType = GetFrontendTypeFromManifest(packagePathStr);

    // create container
    Platform::AceContainer::CreateContainer(
        abilityId_, frontendType, this,
        std::make_unique<AcePlatformEventCallback>([this]() {
            TerminateAbility();
        }));
    // create view.
    auto flutterAceView = Platform::FlutterAceView::CreateView(abilityId_);
    OHOS::Window* window = Ability::GetWindow().get();

    auto&& touchEventCallback = [aceView = flutterAceView](OHOS::TouchEvent event) -> bool {
        LOGD("RegistOnTouchCb touchEventCallback called");
        return aceView->DispatchTouchEvent(aceView, event);
    };
    window->RegistOnTouchCb(touchEventCallback);

    Platform::FlutterAceView::SurfaceCreated(flutterAceView, window);

    // set metrics
    BufferRequestConfig windowConfig;
    window->GetRequestConfig(windowConfig);
    LOGI("AceAbility: windowConfig: width: %{public}d, height: %{public}d", windowConfig.width, windowConfig.height);

    flutter::ViewportMetrics metrics;
    metrics.physical_width = windowConfig.width;
    metrics.physical_height = windowConfig.height;
    Platform::FlutterAceView::SetViewportMetrics(flutterAceView, metrics);

    // add asset path.
    auto assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
    Platform::AceContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);
    // set view
    Platform::AceContainer::SetView(flutterAceView, density_, windowConfig.width, windowConfig.height);
    Platform::FlutterAceView::SurfaceChanged(flutterAceView, windowConfig.width, windowConfig.height, 0);

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
    Platform::AceContainer::RunPage(
        abilityId_, Platform::AceContainer::GetContainer(abilityId_)->GeneratePageId(),
        parsedPageUrl, want.GetStringParam(START_PARAMS_KEY));

    Platform::AceContainer::OnRestoreData(abilityId_, remoteData_);
    LOGI("AceAbility::OnStart called End");
}

void AceAbility::OnStop()
{
    LOGI("AceAbility::OnStop called ");
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
    LOGI("AceAbility::OnConfigurationUpdated called End");
}

}
} // namespace OHOS::Ace
