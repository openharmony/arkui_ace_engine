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

#include "adapter/ohos/entrance/ace_data_ability.h"

#include "adapter/ohos/entrance/pa_engine/pa_backend.h"
#include "core/common/ace_engine.h"

namespace OHOS {
namespace Ace {

using namespace OHOS::AAFwk;
using namespace OHOS::AppExecFwk;

using DataPlatformFinish = std::function<void()>;
class DataPlatformEventCallback final : public Platform::PlatformEventCallback {
public:
    explicit DataPlatformEventCallback(DataPlatformFinish onFinish) : onFinish_(onFinish) {}

    ~DataPlatformEventCallback() override = default;

    void OnFinish() const override
    {
        LOGI("DataPlatformEventCallback OnFinish");
        CHECK_NULL_VOID(onFinish_);
        onFinish_();
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("DataPlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    DataPlatformFinish onFinish_;
};

const std::string AceDataAbility::START_PARAMS_KEY = "__startParams";
const std::string AceDataAbility::URI = "url";

REGISTER_AA(AceDataAbility)

AceDataAbility::AceDataAbility()
{
    abilityId_ = Container::GenerateId<PA_DATA_CONTAINER>();
}

void AceDataAbility::OnStart(const OHOS::AAFwk::Want& want, sptr<AAFwk::SessionInfo> sessionInfo)
{
    Ability::OnStart(want, sessionInfo);
    LOGI("AceDataAbility OnStart called");

    // get url
    std::string parsedUrl;
    if (want.HasParameter(URI)) {
        parsedUrl = want.GetStringParam(URI);
    } else {
        parsedUrl = "data.js";
    }

    // get asset
    auto packagePathStr = GetBundleCodePath();
    auto moduleInfo = GetHapModuleInfo();
    CHECK_NULL_VOID(moduleInfo);
    packagePathStr += "/" + moduleInfo->package + "/";
    std::shared_ptr<AbilityInfo> abilityInfo = GetAbilityInfo();

    // init data ability
    BackendType backendType = BackendType::DATA;
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
        std::make_unique<DataPlatformEventCallback>([this]() { TerminateAbility(); }));
    Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);

    // run data ability
    Platform::PaContainer::RunPa(abilityId_, parsedUrl, want);
}

void AceDataAbility::OnStop()
{
    LOGI("AceDataAbility OnStop called");
    Ability::OnStop();
    Platform::PaContainer::DestroyContainer(abilityId_);
}

int32_t AceDataAbility::Insert(const Uri& uri, const NativeRdb::ValuesBucket& value)
{
    LOGI("AceDataAbility Insert called");
    int32_t ret = Platform::PaContainer::Insert(abilityId_, uri, value);
    return ret;
}

std::shared_ptr<NativeRdb::AbsSharedResultSet> AceDataAbility::Query(
    const Uri& uri, const std::vector<std::string>& columns,
    const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility Query called");
    auto resultSet = Platform::PaContainer::Query(abilityId_, uri, columns, predicates);
    return resultSet;
}

int32_t AceDataAbility::Update(const Uri& uri, const NativeRdb::ValuesBucket& value,
    const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility Update called");
    int32_t ret = Platform::PaContainer::Update(abilityId_, uri, value, predicates);
    return ret;
}

int32_t AceDataAbility::Delete(const Uri& uri, const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility Delete called");
    int32_t ret = Platform::PaContainer::Delete(abilityId_, uri, predicates);
    return ret;
}

int32_t AceDataAbility::BatchInsert(const Uri& uri, const std::vector<NativeRdb::ValuesBucket>& values)
{
    LOGI("AceDataAbility BatchInsert called");
    int32_t ret = Platform::PaContainer::BatchInsert(abilityId_, uri, values);
    return ret;
}

std::string AceDataAbility::GetType(const Uri& uri)
{
    LOGI("AceDataAbility GetType called");
    std::string ret = Platform::PaContainer::GetType(abilityId_, uri);
    return ret;
}

std::vector<std::string> AceDataAbility::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    LOGI("AceDataAbility GetFileTypes called");
    std::vector<std::string> ret = Platform::PaContainer::GetFileTypes(abilityId_, uri, mimeTypeFilter);
    return ret;
}

int32_t AceDataAbility::OpenFile(const Uri& uri, const std::string& mode)
{
    LOGI("AceDataAbility OpenFile called");
    int32_t ret = Platform::PaContainer::OpenFile(abilityId_, uri, mode);
    return ret;
}

int32_t AceDataAbility::OpenRawFile(const Uri& uri, const std::string& mode)
{
    LOGI("AceDataAbility OpenRawFile called");
    int32_t ret = Platform::PaContainer::OpenRawFile(abilityId_, uri, mode);
    return ret;
}

Uri AceDataAbility::NormalizeUri(const Uri& uri)
{
    LOGI("AceDataAbility NormalizeUri called");
    Uri ret = Platform::PaContainer::NormalizeUri(abilityId_, uri);
    return ret;
}

Uri AceDataAbility::DenormalizeUri(const Uri& uri)
{
    LOGI("AceDataAbility DenormalizeUri called");
    Uri ret = Platform::PaContainer::DenormalizeUri(abilityId_, uri);
    return ret;
}

std::shared_ptr<AppExecFwk::PacMap> AceDataAbility::Call(const Uri& uri,
    const std::string& method, const std::string& arg, const AppExecFwk::PacMap& pacMap)
{
    std::shared_ptr<AppExecFwk::PacMap> ret = Platform::PaContainer::Call(abilityId_, uri, method, arg, pacMap);
    return ret;
}
} // namespace Ace
} // namespace OHOS
