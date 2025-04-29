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

#include "core/common/ace_engine.h"

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
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("ServicePlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    ServicePlatformFinish onFinish_;
};

const std::string AceServiceAbility::START_PARAMS_KEY = "__startParams";
const std::string AceServiceAbility::URI = "url";

REGISTER_AA(AceServiceAbility)

AceServiceAbility::AceServiceAbility()
{
    abilityId_ = Container::GenerateId<PA_SERVICE_CONTAINER>();
}

void AceServiceAbility::OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    Ability::OnStart(want, sessionInfo);
    LOGI("AceServiceAbility OnStart called");
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
    CHECK_NULL_VOID(moduleInfo);
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

    Platform::PaContainer::CreateContainer(abilityId_, this, options,
        std::make_unique<ServicePlatformEventCallback>([this]() { TerminateAbility(); }));
    Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);

    // run service
    Platform::PaContainer::RunPa(abilityId_, parsedUrl, want);
}

void AceServiceAbility::OnStop()
{
    LOGI("AceServiceAbility OnStop called ");
    Ability::OnStop();
    Platform::PaContainer::DestroyContainer(abilityId_);
}

sptr<IRemoteObject> AceServiceAbility::OnConnect(const Want& want)
{
    LOGI("AceServiceAbility OnConnect start");
    Ability::OnConnect(want);
    auto ret = Platform::PaContainer::OnConnect(abilityId_, want);
    if (ret == nullptr) {
        LOGE("AceServiceAbility OnConnect, the iremoteObject is null");
        return nullptr;
    }
    return ret;
}

void AceServiceAbility::OnDisconnect(const Want& want)
{
    LOGI("AceServiceAbility OnDisconnect start");
    Ability::OnDisconnect(want);
    Platform::PaContainer::OnDisConnect(abilityId_, want);
}

void AceServiceAbility::OnCommand(const AAFwk::Want &want, bool restart, int startId)
{
    LOGI("AceServiceAbility OnCommand start");
    Ability::OnCommand(want, restart, startId);
    Platform::PaContainer::OnCommand(want, startId, abilityId_);
}
} // namespace Ace
} // namespace OHOS
