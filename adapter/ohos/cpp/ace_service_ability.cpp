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
#include "frameworks/bridge/pa_backend/pa_backend.h"

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
    auto assetBasePathStr = {std::string("assets/js/default/"), std::string("assets/js/share/")};
    Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, assetBasePathStr);

    // run service
    Platform::PaContainer::RunPa(
        abilityId_, parsedUrl, want.GetStringParam(START_PARAMS_KEY));

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
    Ability::OnConnect(want);
    auto wantJson = JsonUtil::Create(true);
    wantJson->Put("abilityName", want.GetOperation().GetAbilityName().c_str());
    wantJson->Put("bundleName", want.GetOperation().GetBundleName().c_str());
    auto wantInfo = wantJson->ToString();
    auto ret = Platform::PaContainer::OnConnect(abilityId_, wantInfo);
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
    auto wantJson = JsonUtil::Create(true);
    wantJson->Put("abilityName", want.GetOperation().GetAbilityName().c_str());
    wantJson->Put("bundleName", want.GetOperation().GetBundleName().c_str());
    auto wantInfo = wantJson->ToString();
    Platform::PaContainer::OnDisConnect(abilityId_, wantInfo);
    LOGI("AceServiceAbility::OnDisconnect end");
}
}
} // namespace OHOS::Ace
