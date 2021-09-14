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

#include "adapter/ohos/cpp/ace_service_ability.h"
#include "adapter/ohos/cpp/pa_container.h"
#include "adapter/ohos/cpp/platform_event_callback.h"

#include "base/log/log.h"
#include "core/common/backend.h"
#include "form_constants.h"
#include "res_config.h"
#include "resource_manager.h"

namespace OHOS {
namespace Ace {
using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;

using ServicePlatformFinish = std::function<void()>;
class ServicePlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit ServicePlatformEventCallback(ServicePlatformFinish onFinish) : onFinish_(onFinish) {}

    ~ServicePlatformEventCallback() = default;

    virtual void OnFinish() const
    {
        LOGI("ServicePlatformEventCallback OnFinish");
        if (onFinish_) {
            onFinish_();
        }
    }

    virtual void OnStatusBarBgColorChanged(uint32_t color)
    {
        LOGI("ServicePlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    ServicePlatformFinish onFinish_;
};

int32_t AceServiceAbility::instanceId_ = 100000;
const std::string AceServiceAbility::START_PARAMS_KEY = "__startParams";
const std::string AceServiceAbility::URI = "url";


REGISTER_AA(AceServiceAbility)
void AceServiceAbility::OnStart(const OHOS::AAFwk::Want &want)
{
    Ability::OnStart(want);
    LOGI("AceServiceAbility::OnStart called");

    if (type_ == BackendType::FORM) {
        LOGI("AceServiceAbility::OnStart is form");
        return;
    }

    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "service.js";
    }

    // init service
    BackendType backendType = BackendType::SERVICE;
    Platform::PaContainer::CreateContainer(
        abilityId_, backendType, this,
        std::make_unique<ServicePlatformEventCallback>([this]() {
            TerminateAbility();
        }));

    // get asset
    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    if (moduleInfo != nullptr) {
        packagePathStr += "/" + moduleInfo->name + "/";
    }
    std::shared_ptr<AbilityInfo> info = GetAbilityInfo();
    if (info != nullptr && !info->srcPath.empty()) {
        LOGI("AceServiceAbility::OnStar assetBasePathStr: %{public}s, parsedUrl: %{public}s",
            info->srcPath.c_str(), parsedUrl.c_str());
        auto assetBasePathStr = { "assets/js/default/" + info->srcPath };
        Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);
    } else {
        LOGI("AceServiceAbility::OnStar parsedUrl: %{public}s", parsedUrl.c_str());
        auto assetBasePathStr = {std::string("assets/js/default/"), std::string("assets/js/share/")};
        Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);
    }

    // run service
    Platform::PaContainer::RunPa(abilityId_, parsedUrl, want);
    LOGI("AceServiceAbility::OnStart called End");
}

void AceServiceAbility::OnStop()
{
    LOGI("AceServiceAbility::OnStop called ");
    Ability::OnStop();
    Platform::PaContainer::DestroyContainer(abilityId_);
    LOGI("AceServiceAbility::OnStop called End");
}

sptr<IRemoteObject> AceServiceAbility::OnConnect(const Want &want)
{
    LOGI("AceServiceAbility::OnConnect start");
    if (type_ == BackendType::FORM) {
        LOGI("AceServiceAbility::OnConnect is form");
        return GetFormRemoteObject();
    }
    Ability::OnConnect(want);
    auto ret = Platform::PaContainer::OnConnect(abilityId_, want);
    if (ret == nullptr) {
        LOGE("AceServiceAbility::OnConnect, the iremoteObject is null");
        return nullptr;
    }
    LOGI("AceServiceAbility::OnConnect end");
    return ret;
}

void AceServiceAbility::OnDisconnect(const Want &want)
{
    LOGI("AceServiceAbility::OnDisconnect start");
    Ability::OnDisconnect(want);
    Platform::PaContainer::OnDisConnect(abilityId_, want);
    LOGI("AceServiceAbility::OnDisconnect end");
}

OHOS::AppExecFwk::FormProviderInfo AceServiceAbility::OnCreate(const OHOS::AAFwk::Want& want)
{
    LOGI("AceServiceAbility::OnCreate called");
    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "app.js";
    }

    int32_t wantId = abilityId_;
    if (want.HasParameter(AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY)) {
        std::string wantIdStr = want.GetStringParam(AppExecFwk::Constants::PARAM_FORM_IDENTITY_KEY);
        wantId = atoi(wantIdStr.c_str());
        LOGI("AceServiceAbility:: wantId = %{public}s, %{public}d", wantIdStr.c_str(), wantId);
    } else {
        LOGE("AceServiceAbility:: has not formId in want");
    }

    // init service
    BackendType backendType = BackendType::FORM;
    Platform::PaContainer::CreateContainer(
        wantId, backendType, this,
        std::make_unique<ServicePlatformEventCallback>([this]() {
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

    // run service
    Platform::PaContainer::RunPa(wantId, parsedUrl, want);

    OHOS::AppExecFwk::FormProviderInfo formProviderInfo;
    formProviderInfo.SetFormData(Platform::PaContainer::GetFormData(wantId));
    std::string formData = formProviderInfo.GetFormData().GetDataString();
    LOGI("AceServiceAbility::OnCreate return ok, formData: %{public}s", formData.c_str());
    return formProviderInfo;
}

void AceServiceAbility::OnDelete(const int64_t formId)
{
    Platform::PaContainer::OnDelete(formId);
}

void AceServiceAbility::OnTriggerEvent(const int64_t formId, const std::string& message)
{
    Platform::PaContainer::OnTriggerEvent(formId, message);
}

void AceServiceAbility::OnUpdate(const int64_t formId)
{
    Platform::PaContainer::OnUpdate(formId);
}

void AceServiceAbility::OnCastTemptoNormal(const int64_t formId)
{
    Platform::PaContainer::OnCastTemptoNormal(formId);
}

void AceServiceAbility::OnVisibilityChanged(const std::map<int64_t, int32_t>& formEventsMap)
{
    Platform::PaContainer::OnVisibilityChanged(formEventsMap);
}

void AceServiceAbility::OnAcquireState(const OHOS::AAFwk::Want& want)
{
    Platform::PaContainer::OnAcquireState(want);
}

}
} // namespace OHOS::Ace
