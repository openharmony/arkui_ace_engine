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

#include "adapter/ohos/entrance/pa_engine/pa_backend.h"

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
        TAG_LOGI(AceLogTag::ACE_FORM, "FormPlatformEventCallback OnFinish");
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        TAG_LOGI(AceLogTag::ACE_FORM, "FormPlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    FormPlatformFinish onFinish_;
};

const std::string AceFormAbility::START_PARAMS_KEY = "__startParams";
const std::string AceFormAbility::URI = "url";

REGISTER_AA(AceFormAbility)

AceFormAbility::AceFormAbility()
{
    instanceId_ = Container::GenerateId<PA_FORM_CONTAINER>();
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
        assetBasePathStr = { "assets/js/" + abilityInfo->srcPath + "/", std::string("assets/js/") };
    } else {
        assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
    }

    workerPath->assetBasePathStr = assetBasePathStr;

    Platform::PaContainerOptions options;
    options.type = backendType;
    options.language = srcLanguage;
    options.hapPath = moduleInfo->hapPath;
    options.workerPath = workerPath;

    Platform::PaContainer::CreateContainer(
        instanceId_, this, options, std::make_unique<FormPlatformEventCallback>([this]() { TerminateAbility(); }));
    Platform::PaContainer::AddAssetPath(instanceId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);

    // run form ability
    Platform::PaContainer::RunPa(instanceId_, parsedUrl, want);
}

OHOS::AppExecFwk::FormProviderInfo AceFormAbility::OnCreate(const OHOS::AAFwk::Want& want)
{
    std::string formId = want.GetStringParam(AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY);
    Platform::PaContainer::OnCreate(instanceId_, want);
    OHOS::AppExecFwk::FormProviderInfo formProviderInfo;
    formProviderInfo.SetFormData(Platform::PaContainer::GetFormData(instanceId_));
    std::string formData = formProviderInfo.GetFormData().GetDataString();
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnCreate formId = %{public}s, formData: %{public}s", formId.c_str(),
        formData.c_str());
    return formProviderInfo;
}

void AceFormAbility::OnDelete(const int64_t formId)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnDelete called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnDelete(instanceId_, formId);
}

void AceFormAbility::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnTriggerEvent called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnTriggerEvent(instanceId_, formId, message);
}

AppExecFwk::FormState AceFormAbility::OnAcquireFormState(const OHOS::AAFwk::Want& want)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnAcquireState called");
    int32_t formState = Platform::PaContainer::OnAcquireFormState(instanceId_, want);
    if (formState <= (int32_t)AppExecFwk::FormState::UNKNOWN || formState > (int32_t)AppExecFwk::FormState::READY) {
        return AppExecFwk::FormState::UNKNOWN;
    } else {
        return (AppExecFwk::FormState)formState;
    }
}

void AceFormAbility::OnUpdate(const int64_t formId, const WantParams& wantParams)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnUpdate params called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnUpdate(instanceId_, formId);
}

void AceFormAbility::OnCastTemptoNormal(const int64_t formId)
{
    TAG_LOGI(
        AceLogTag::ACE_FORM, "AceFormAbility OnCastTemptoNormal called: %{public}s", std::to_string(formId).c_str());
    Platform::PaContainer::OnCastTemptoNormal(instanceId_, formId);
}

void AceFormAbility::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnVisibilityChanged called");
    Platform::PaContainer::OnVisibilityChanged(instanceId_, formEventsMap);
}

bool AceFormAbility::OnShare(int64_t formId, OHOS::AAFwk::WantParams& wantParams)
{
    return Platform::PaContainer::OnShare(instanceId_, formId, wantParams);
}

void AceFormAbility::OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnStart start");
    Ability::OnStart(want, sessionInfo);
    LoadFormEnv(want);
}

void AceFormAbility::OnStop()
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnStop start ");
    Ability::OnStop();
}

sptr<IRemoteObject> AceFormAbility::OnConnect(const Want& want)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnConnect start");
    Ability::OnConnect(want);
    return GetFormRemoteObject();
}

void AceFormAbility::OnDisconnect(const Want& want)
{
    TAG_LOGI(AceLogTag::ACE_FORM, "AceFormAbility OnDisconnect start");
    Ability::OnDisconnect(want);
}

sptr<IRemoteObject> AceFormAbility::GetFormRemoteObject()
{
    if (formProviderRemoteObject_ == nullptr) {
        sptr<FormProviderClient> providerClient = new (std::nothrow) FormProviderClient();
        std::shared_ptr<Ability> thisAbility = this->shared_from_this();
        if (thisAbility == nullptr) {
            TAG_LOGE(AceLogTag::ACE_FORM, "Get form remote object failed, ability is nullptr");
            return nullptr;
        }
        providerClient->SetOwner(thisAbility);
        formProviderRemoteObject_ = providerClient->AsObject();
    }
    return formProviderRemoteObject_;
}
} // namespace OHOS::Ace
