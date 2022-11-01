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

#include "adapter/ohos/entrance/ace_data_ability.h"

#include "res_config.h"
#include "resource_manager.h"

#include "adapter/ohos/entrance/pa_container.h"
#include "adapter/ohos/entrance/pa_engine/pa_backend.h"
#include "adapter/ohos/entrance/platform_event_callback.h"
#include "adapter/ohos/entrance/utils.h"
#include "base/log/log.h"
#include "core/common/ace_engine.h"
#include "core/common/backend.h"

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
        if (onFinish_) {
            onFinish_();
        }
    }

    void OnStatusBarBgColorChanged(uint32_t color) override
    {
        LOGI("DataPlatformEventCallback OnStatusBarBgColorChanged");
    }

private:
    DataPlatformFinish onFinish_;
};

int32_t AceDataAbility::instanceId_ = 200000;
const std::string AceDataAbility::START_PARAMS_KEY = "__startParams";
const std::string AceDataAbility::URI = "url";

REGISTER_AA(AceDataAbility)
void AceDataAbility::OnStart(const OHOS::AAFwk::Want& want)
{
    Ability::OnStart(want);
    LOGI("AceDataAbility::OnStart called");

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
    if (moduleInfo == nullptr) {
        return;
    }
    packagePathStr += "/" + moduleInfo->package + "/";
    // init data ability
    bool isHap = !moduleInfo->hapPath.empty();
    std::string& packagePath = isHap ? moduleInfo->hapPath : packagePathStr;
    BackendType backendType = BackendType::DATA;
    bool isArkApp = GetIsArkFromConfig(packagePath, isHap);

    Platform::PaContainer::CreateContainer(abilityId_, backendType, isArkApp, this,
        std::make_unique<DataPlatformEventCallback>([this]() { TerminateAbility(); }));

    AceEngine::InitJsDumpHeadSignal();
    std::shared_ptr<AbilityInfo> info = GetAbilityInfo();
    if (info != nullptr && !info->srcPath.empty()) {
        LOGI("AceDataAbility::OnStart assetBasePathStr: %{public}s, parsedUrl: %{public}s",
            info->srcPath.c_str(), parsedUrl.c_str());
        auto assetBasePathStr = { "assets/js/" + info->srcPath + "/" };
        Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    } else {
        LOGI("AceDataAbility::OnStart parsedUrl: %{public}s", parsedUrl.c_str());
        auto assetBasePathStr = { std::string("assets/js/default/"), std::string("assets/js/share/") };
        Platform::PaContainer::AddAssetPath(abilityId_, packagePathStr, moduleInfo->hapPath, assetBasePathStr);
    }
    std::shared_ptr<ApplicationInfo> appInfo = GetApplicationInfo();
    if (appInfo) {
        /* Note: DO NOT modify the sequence of adding libPath  */
        std::string nativeLibraryPath = appInfo->nativeLibraryPath;
        std::string quickFixLibraryPath = appInfo->appQuickFix.deployedAppqfInfo.nativeLibraryPath;
        std::vector<std::string> libPaths;
        if (!quickFixLibraryPath.empty()) {
            std::string libPath = GenerateFullPath(GetBundleCodePath(), quickFixLibraryPath);
            libPaths.push_back(libPath);
            LOGI("napi quick fix lib path = %{private}s", libPath.c_str());
        }
        if (!nativeLibraryPath.empty()) {
            std::string libPath = GenerateFullPath(GetBundleCodePath(), nativeLibraryPath);
            libPaths.push_back(libPath);
            LOGI("napi lib path = %{private}s", libPath.c_str());
        }
        if (!libPaths.empty()) {
            Platform::PaContainer::AddLibPath(abilityId_, libPaths);
        }
    }

    // run data ability
    Platform::PaContainer::RunPa(abilityId_, parsedUrl, want);

    LOGI("AceDataAbility::OnStart called End");
}

void AceDataAbility::OnStop()
{
    LOGI("AceDataAbility::OnStop called");
    Ability::OnStop();
    Platform::PaContainer::DestroyContainer(abilityId_);
    LOGI("AceDataAbility::OnStop called End");
}

int32_t AceDataAbility::Insert(const Uri& uri, const NativeRdb::ValuesBucket& value)
{
    LOGI("AceDataAbility::Insert called");
    int32_t ret = Platform::PaContainer::Insert(abilityId_, uri, value);
    LOGI("AceDataAbility::Insert called End");
    return ret;
}

std::shared_ptr<NativeRdb::AbsSharedResultSet> AceDataAbility::Query(
    const Uri& uri, const std::vector<std::string>& columns,
    const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility::Query called");
    auto resultSet = Platform::PaContainer::Query(abilityId_, uri, columns, predicates);
    LOGI("AceDataAbility::Query called End");
    return resultSet;
}

int32_t AceDataAbility::Update(const Uri& uri, const NativeRdb::ValuesBucket& value,
    const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility::Update called");
    int32_t ret = Platform::PaContainer::Update(abilityId_, uri, value, predicates);
    LOGI("AceDataAbility::Update called End");
    return ret;
}

int32_t AceDataAbility::Delete(const Uri& uri, const NativeRdb::DataAbilityPredicates& predicates)
{
    LOGI("AceDataAbility::Delete called");
    int32_t ret = Platform::PaContainer::Delete(abilityId_, uri, predicates);
    LOGI("AceDataAbility::Delete called End");
    return ret;
}

int32_t AceDataAbility::BatchInsert(const Uri& uri, const std::vector<NativeRdb::ValuesBucket>& values)
{
    LOGI("AceDataAbility::BatchInsert called");
    int32_t ret = Platform::PaContainer::BatchInsert(abilityId_, uri, values);
    LOGI("AceDataAbility::BatchInsert called End");
    return ret;
}

std::string AceDataAbility::GetType(const Uri& uri)
{
    LOGI("AceDataAbility::GetType called");
    std::string ret = Platform::PaContainer::GetType(abilityId_, uri);
    LOGI("AceDataAbility::GetType called End");
    return ret;
}

std::vector<std::string> AceDataAbility::GetFileTypes(const Uri& uri, const std::string& mimeTypeFilter)
{
    LOGI("AceDataAbility::GetFileTypes called");
    std::vector<std::string> ret = Platform::PaContainer::GetFileTypes(abilityId_, uri, mimeTypeFilter);
    LOGI("AceDataAbility::GetFileTypes called End");
    return ret;
}

int32_t AceDataAbility::OpenFile(const Uri& uri, const std::string& mode)
{
    LOGI("AceDataAbility::OpenFile called");
    int32_t ret = Platform::PaContainer::OpenFile(abilityId_, uri, mode);
    LOGI("AceDataAbility::OpenFile called End");
    return ret;
}

int32_t AceDataAbility::OpenRawFile(const Uri& uri, const std::string& mode)
{
    LOGI("AceDataAbility::OpenRawFile called");
    int32_t ret = Platform::PaContainer::OpenRawFile(abilityId_, uri, mode);
    LOGI("AceDataAbility::OpenRawFile called End");
    return ret;
}

Uri AceDataAbility::NormalizeUri(const Uri& uri)
{
    LOGI("AceDataAbility::NormalizeUri called");
    Uri ret = Platform::PaContainer::NormalizeUri(abilityId_, uri);
    LOGI("AceDataAbility::NormalizeUri called End");
    return ret;
}

Uri AceDataAbility::DenormalizeUri(const Uri& uri)
{
    LOGI("AceDataAbility::DenormalizeUri called");
    Uri ret = Platform::PaContainer::DenormalizeUri(abilityId_, uri);
    LOGI("AceDataAbility::DenormalizeUri called End");
    return ret;
}

std::shared_ptr<AppExecFwk::PacMap> AceDataAbility::Call(const Uri& uri,
    const std::string& method, const std::string& arg, const AppExecFwk::PacMap& pacMap)
{
    LOGD("AceDataAbility::Call called");
    std::shared_ptr<AppExecFwk::PacMap> ret = Platform::PaContainer::Call(abilityId_, uri, method, arg, pacMap);
    return ret;
}
} // namespace Ace
} // namespace OHOS
