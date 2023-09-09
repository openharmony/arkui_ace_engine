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

#include "adapter/ohos/entrance/ace_form_ability.h"

#include "form_provider_client.h"
#include "res_config.h"
#include "resource_manager.h"
#include "session_info.h"

#include "adapter/ohos/entrance/pa_container.h"
#include "adapter/ohos/entrance/pa_engine/pa_backend.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/backend.h"

namespace OHOS::Ace {
using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;
using FormPlatformFinish = std::function<void()>;
class FormPlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit FormPlatformEventCallback(FormPlatformFinish onFinish) : onFinish_(onFinish) {}

    ~FormPlatformEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("FormPlatformEventCallback OnFinish");
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("FormPlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    FormPlatformFinish onFinish_;
};

int32_t AceFormAbility::instanceId_ = 300000;
const std::string AceFormAbility::START_PARAMS_KEY = "__startParams";
const std::string AceFormAbility::URI = "url";

REGISTER_AA(AceFormAbility)

AceFormAbility::AceFormAbility()
{
    instanceId_++;
}

void AceFormAbility::LoadFormEnv(const OHOS::AAFwk::Want& want)
{
    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "form.js";
    }

    // get asset
    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    CHECK_NULL_VOID(moduleInfo);
    packagePathStr += "/" + moduleInfo->package + "/";
    std::shared_ptr<AbilityInfo> abilityInfo = GetAbilityInfo();

    // init form ability
    BackendType backendType = BackendType::FORM;
    SrcLanguage srcLanguage = SrcLanguage::ETS;
    if (abilityInfo != nullptr && !abilityInfo->srcLanguage.empty()) {
        if (abilityInfo->srcLanguage == "js") {
            srcLanguage = SrcLanguage::JS;
        }
    }

    std::shared_ptr<Platform::WorkerPath> workerPath = std::make_shared<Platform::WorkerPath>();
    workerPath->packagePathStr = packagePathStr;
    std::vector<std::string> assetBasePathStr;

    if (abilityInfo != nullptr && !abilityInfo->srcPath.empty()) {
        LOGI("AceFormAbility srcPath:%{public}s url:%{public}s", abilityInfo->srcPath.c_str(), parsedUrl.c_str());
        assetBasePathStr = { "assets/js/" + abilityInfo->srcPath + "/", std::string("assets/js/") };
    } else {
        LOGI("AceFormAbility parsedUrl:%{public}s", parsedUrl.c_str());
        assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
    }

    workerPath->assetBasePathStr = assetBasePathStr;

    Platform::PaContainerOptions options;
    options.type = backendType;
    options.language = srcLanguage;
    options.hapPath = moduleInfo->hapPath;
    options.workerPath = workerPath;

    Platform::PaContainer::CreateContainer(instanceId_, this, options,
        std::make_unique<FormPlatformEventCallback>([this]() { TerminateAbility(); }));
    Platform::PaContainer::AddAssetPath(instanceId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);

    // run form ability
    Platform::PaContainer::RunPa(instanceId_, parsedUrl, want);
}

OHOS::AppExecFwk::FormProviderInfo AceFormAbility::OnCreate(const OHOS::AAFwk::Want& want)
{
    std::string formId = want.GetStringParam(AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY);
    LOGI("AceFormAbility::OnCreate formId = %{public}s.", formId.c_str());
    Platform::PaContainer::OnCreate(instanceId_, want);
    OHOS::AppExecFwk::FormProviderInfo formProviderInfo;
    formProviderInfo.SetFormData(Platform::PaContainer::GetFormData(instanceId_));
    std::string formData = formProviderInfo.GetFormData().GetDataString();
    LOGI("AceFormAbility::OnCreate return ok, formData: %{public}s", formData.c_str());
    return formProviderInfo;
}

void AceFormAbility::OnDelete(const int64_t formId)
{
    LOGI("AceFormAbility::OnDelete called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnDelete(instanceId_, formId);
}

void AceFormAbility::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    LOGI("AceFormAbility::OnTriggerEvent called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnTriggerEvent(instanceId_, formId, message);
}

AppExecFwk::FormState AceFormAbility::OnAcquireFormState(const OHOS::AAFwk::Want &want)
{
    LOGI("AceFormAbility::OnAcquireState called");
    int32_t formState = Platform::PaContainer::OnAcquireFormState(instanceId_, want);
    if (formState <= (int32_t) AppExecFwk::FormState::UNKNOWN || formState > (int32_t) AppExecFwk::FormState::READY) {
        return AppExecFwk::FormState::UNKNOWN;
    } else {
        return (AppExecFwk::FormState) formState;
    }
}

void AceFormAbility::OnUpdate(const int64_t formId)
{
    LOGI("AceFormAbility::OnUpdate called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnUpdate(instanceId_, formId);
}

void AceFormAbility::OnCastTemptoNormal(const int64_t formId)
{
    LOGI("AceFormAbility::OnCastTemptoNormal called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnCastTemptoNormal(instanceId_, formId);
}

void AceFormAbility::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    LOGI("AceFormAbility::OnVisibilityChanged called");
    Platform::PaContainer::OnVisibilityChanged(instanceId_, formEventsMap);
}

bool AceFormAbility::OnShare(int64_t formId, OHOS::AAFwk::WantParams &wantParams)
{
    LOGD("AceFormAbility::OnShare called");
    return Platform::PaContainer::OnShare(instanceId_, formId, wantParams);
}

void AceFormAbility::OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    LOGI("AceFormAbility::OnStart start");
    Ability::OnStart(want, sessionInfo);
    LoadFormEnv(want);
}

void AceFormAbility::OnStop()
{
    LOGI("AceFormAbility::OnStop start ");
    Ability::OnStop();
}

sptr<IRemoteObject> AceFormAbility::OnConnect(const Want& want)
{
    LOGI("AceFormAbility::OnConnect start");
    Ability::OnConnect(want);
    return GetFormRemoteObject();
}

void AceFormAbility::OnDisconnect(const Want& want)
{
    LOGI("AceFormAbility::OnDisconnect start");
    Ability::OnDisconnect(want);
}

sptr<IRemoteObject> AceFormAbility::GetFormRemoteObject()
{
    LOGD("Get form remote object start");
    if (formProviderRemoteObject_ == nullptr) {
        sptr<FormProviderClient> providerClient = new (std::nothrow) FormProviderClient();
        std::shared_ptr<Ability> thisAbility = this->shared_from_this();
        if (thisAbility == nullptr) {
            LOGE("Get form remote object failed, ability is nullptr");
            return nullptr;
        }
        providerClient->SetOwner(thisAbility);
        formProviderRemoteObject_ = providerClient->AsObject();
    }
    LOGD("Get form remote object end");
    return formProviderRemoteObject_;
}
} // namespace OHOS::Ace
