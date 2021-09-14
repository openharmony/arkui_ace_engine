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

#include "adapter/ohos/cpp/ace_form_ability.h"

#include "adapter/ohos/cpp/pa_container.h"
#include "adapter/ohos/cpp/platform_event_callback.h"
#include "base/log/log.h"
#include "core/common/backend.h"
#include "frameworks/bridge/pa_backend/pa_backend.h"
#include "res_config.h"
#include "resource_manager.h"

namespace OHOS::Ace {
using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;

using FormPlatformFinish = std::function<void()>;
class FormPlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit FormPlatformEventCallback(FormPlatformFinish onFinish) : onFinish_(onFinish) {}

    ~FormPlatformEventCallback() = default;

    virtual void OnFinish() const
    {
        LOGI("FormPlatformEventCallback OnFinish");
        if (onFinish_) {
            onFinish_();
        }
    }

    virtual void OnStatusBarBgColorChanged(uint32_t color)
    {
        LOGI("FormPlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    FormPlatformFinish onFinish_;
};

const std::string AceFormAbility::URI = "url";

REGISTER_AA(AceFormAbility)

void AceFormAbility::OnStart(const OHOS::AAFwk::Want &want)
{
    LOGI("AceFormAbility::OnStart start");
    Ability::OnStart(want);
    return;
}

void AceFormAbility::OnStop()
{
    LOGI("AceFormAbility::OnStop start ");
    Ability::OnStop();
    return;
}

sptr<IRemoteObject> AceFormAbility::OnConnect(const Want &want)
{
    LOGI("AceFormAbility::OnConnect start");
    Ability::OnConnect(want);
    return GetFormRemoteObject();
}

void AceFormAbility::OnDisconnect(const Want &want)
{
    LOGI("AceFormAbility::OnDisconnect start");
    Ability::OnDisconnect(want);
    return;
}

OHOS::AppExecFwk::FormProviderInfo AceFormAbility::OnCreate(const OHOS::AAFwk::Want& want)
{
    LOGI("AceFormAbility::OnCreate called");

    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "form.js";
    }

    std::string wantIdStr = want.GetStringParam(AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY);
    int32_t wantId = atoi(wantIdStr.c_str());
    LOGI("AceFormAbility:: wantId = %{public}s, %{public}d", wantIdStr.c_str(), wantId);

    // init from ability
    BackendType backendType = BackendType::FORM;
    Platform::PaContainer::CreateContainer(
        wantId, backendType, this,
        std::make_unique<FormPlatformEventCallback>([this]() {
            TerminateAbility();
        }));

    // get asset
    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    if (moduleInfo != nullptr) {
        packagePathStr += "/" + moduleInfo->name + "/";
    }
    auto assetBasePathStr = {std::string("assets/js/default/"), std::string("assets/js/share/")};
    Platform::PaContainer::AddAssetPath(wantId, packagePathStr, assetBasePathStr);

    // run form ability
    Platform::PaContainer::RunPa(wantId, parsedUrl, want);

    OHOS::AppExecFwk::FormProviderInfo formProviderInfo;
    formProviderInfo.SetFormData(Platform::PaContainer::GetFormData(wantId));
    std::string formData = formProviderInfo.GetFormData().GetDataString();
    LOGI("AceFormAbility::OnCreate return ok, formData: %{public}s", formData.c_str());
    return formProviderInfo;
}

void AceFormAbility::OnDelete(const int64_t formId)
{
    Platform::PaContainer::OnDelete(formId);
}

void AceFormAbility::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    Platform::PaContainer::OnTriggerEvent(formId, message);
}

void AceFormAbility::OnUpdate(const int64_t formId)
{
    Platform::PaContainer::OnUpdate(formId);
}

void AceFormAbility::OnCastTemptoNormal(const int64_t formId)
{
    Platform::PaContainer::OnCastTemptoNormal(formId);
}

void AceFormAbility::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    Platform::PaContainer::OnVisibilityChanged(formEventsMap);
}

void AceFormAbility::OnAcquireState(const OHOS::AAFwk::Want& want)
{
    Platform::PaContainer::OnAcquireState(want);
}

} // namespace OHOS::Ace
