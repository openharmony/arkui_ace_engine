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

#include "adapter/ohos/entrance/ace_service_ability.h"

#include "res_config.h"
#include "resource_manager.h"
#include "session_info.h"

#include "adapter/ohos/entrance/pa_container.h"
#include "adapter/ohos/entrance/pa_engine/pa_backend.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/common/backend.h"

namespace OHOS {
namespace Ace {

using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;

using ServicePlatformFinish = std::function<void()>;
class ServicePlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit ServicePlatformEventCallback(ServicePlatformFinish onFinish) : onFinish_(onFinish) {}

    ~ServicePlatformEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("ServicePlatformEventCallback OnFinish");
        CHECK_NULL_VOID_NOLOG(onFinish_);
        onFinish_();
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
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
void AceServiceAbility::OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    Ability::OnStart(want, sessionInfo);
    LOGI("AceServiceAbility::OnStart called");
    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "service.js";
    }

    // get asset
    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    CHECK_NULL_VOID_NOLOG(moduleInfo);
    packagePathStr += "/" + moduleInfo->package + "/";
    auto abilityInfo = GetAbilityInfo();

    // init service
    BackendType backendType = BackendType::SERVICE;
    SrcLanguage srcLanguage = SrcLanguage::ETS;
    if (abilityInfo != nullptr && !abilityInfo->srcLanguage.empty()) {
        if (abilityInfo->srcLanguage == "js") {
            srcLanguage = SrcLanguage::JS;
        }
    }

    std::shared_ptr<Platform::WorkerPath> workerPath = std::make_shared<Platform::WorkerPath>();
    workerPath->packagePathStr = packagePathStr;

    std::vector<std::string> assetBasePathStr;
    AceEngine::InitJsDumpHeadSignal();
    if (abilityInfo != nullptr && !abilityInfo->srcPath.empty()) {
        LOGI("AceServiceAbility::OnStar assetBasePathStr: %{public}s, parsedUrl: %{public}s",
            abilityInfo->srcPath.c_str(), parsedUrl.c_str());
        assetBasePathStr = { "assets/js/" + abilityInfo->srcPath + "/", std::string("assets/js/") };
    } else {
        LOGI("AceServiceAbility::OnStar parsedUrl: %{public}s", parsedUrl.c_str());
        assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
    }

    workerPath->assetBasePathStr = assetBasePathStr;

    Platform::PaContainerOptions options;
    options.type = backendType;
    options.language = srcLanguage;
    options.hapPath = moduleInfo->hapPath;
    options.workerPath = workerPath;

    Platform::PaContainer::CreateContainer(abilityId_, this, options,
        std::make_unique<ServicePlatformEventCallback>([this]() { TerminateAbility(); }));
    Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);

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

sptr<IRemoteObject> AceServiceAbility::OnConnect(const Want& want)
{
    LOGI("AceServiceAbility::OnConnect start");
    Ability::OnConnect(want);
    auto ret = Platform::PaContainer::OnConnect(abilityId_, want);
    if (ret == nullptr) {
        LOGE("AceServiceAbility::OnConnect, the iremoteObject is null");
        return nullptr;
    }
    LOGI("AceServiceAbility::OnConnect end");
    return ret;
}

void AceServiceAbility::OnDisconnect(const Want& want)
{
    LOGI("AceServiceAbility::OnDisconnect start");
    Ability::OnDisconnect(want);
    Platform::PaContainer::OnDisConnect(abilityId_, want);
    LOGI("AceServiceAbility::OnDisconnect end");
}

void AceServiceAbility::OnCommand(const AAFwk::Want &want, bool restart, int startId)
{
    LOGI("AceServiceAbility::OnCommand start");
    Ability::OnCommand(want, restart, startId);
    Platform::PaContainer::OnCommand(want, startId, abilityId_);
    LOGI("AceServiceAbility::OnCommand end");
}
} // namespace Ace
} // namespace OHOS
