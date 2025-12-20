/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/hap_asset_provider_impl.h"

#include "bundle_mgr_interface.h"
#include "extractor.h"
#include "if_system_ability_manager.h"
#include "iservice_registry.h"
#include "system_ability_definition.h"

#include "base/log/ace_trace.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace {
namespace {
constexpr char BUNDLE_REQUEST_TAG[] = "@bundle:";
constexpr char MERGE_ABC_PATH[] = "ets/modules.abc";
constexpr char SPLIT_TAG = '/';
constexpr size_t BUNDLE_START_POS = 8;
constexpr size_t BUNDLE_AND_MODULE_SIZE = 2;

bool GetHspModulePath(const std::string& hspBundleName, const std::string& hspModuleName, std::string& hspPath)
{
    auto systemAbilityMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (!systemAbilityMgr) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to request ex module buffer, SystemAbilityManager is none");
        return false;
    }
    auto bundleMgr =
        iface_cast<AppExecFwk::IBundleMgr>(systemAbilityMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID));
    if (!bundleMgr) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to request ex module buffer, SystemAbilityManager is none");
        return false;
    }

    auto currentBundleName = Container::CurrentBundleName();
    if (currentBundleName.empty()) {
        // use hsp bundleName instead.
        currentBundleName = hspBundleName;
    }
    std::vector<AppExecFwk::BaseSharedBundleInfo> baseSharedBundleInfos;
    if (bundleMgr->GetBaseSharedBundleInfos(currentBundleName, baseSharedBundleInfos,
        AppExecFwk::GetDependentBundleInfoFlag::GET_APP_SERVICE_HSP_BUNDLE_INFO) != 0) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "GetBaseSharedBundleInfos failed");
        return false;
    }
    for (const auto& info : baseSharedBundleInfos) {
        if ((info.bundleName == hspBundleName) && (info.moduleName == hspModuleName)) {
            hspPath = info.hapPath;
        }
    }
    if (hspPath.empty()) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "current %{private}s/%{private}s is not installed",
            hspBundleName.c_str(), hspModuleName.c_str());
        return false;
    }
    return true;
}

} // namespace

bool HapAssetProviderImpl::Initialize(
    const std::string& hapPath, const std::vector<std::string>& assetBasePaths, bool useCache)
{
    ACE_SCOPED_TRACE("Initialize");
    if (hapPath.empty() || assetBasePaths.empty()) {
        LOGE("the packagePath or assetBasePath is empty");
        return false;
    }

    bool newCreate = false;
    loadPath_ = AbilityBase::ExtractorUtil::GetLoadFilePath(hapPath);
    if (!useCache) {
        AbilityBase::ExtractorUtil::DeleteExtractor(loadPath_);
    }
    runtimeExtractor_ = AbilityBase::ExtractorUtil::GetExtractor(loadPath_, newCreate);
    CHECK_NULL_RETURN(runtimeExtractor_, false);
    assetBasePaths_ = assetBasePaths;
    hapPath_ = hapPath;
    return true;
}

void HapAssetProviderImpl::Reload()
{
    bool newCreate = false;
    AbilityBase::ExtractorUtil::DeleteExtractor(loadPath_);
    runtimeExtractor_ = AbilityBase::ExtractorUtil::GetExtractor(loadPath_, newCreate);
    if (!runtimeExtractor_) {
        LOGW("GetExtractor failed:%{public}s", loadPath_.c_str());
    }
}

bool HapAssetProviderImpl::IsValid() const
{
    return true;
}

std::unique_ptr<AssetMapping> HapAssetProviderImpl::GetAsMapping(const std::string& assetName) const
{
    ACE_SCOPED_TRACE("GetAsMapping");
    std::lock_guard<std::mutex> lock(mutex_);

    CHECK_NULL_RETURN(runtimeExtractor_, nullptr);
    for (const auto& basePath : assetBasePaths_) {
        std::string fileName = basePath + assetName;
        bool hasFile = runtimeExtractor_->HasEntry(fileName);
        if (!hasFile) {
            continue;
        }
        std::ostringstream osstream;
        hasFile = runtimeExtractor_->GetFileBuffer(fileName, osstream);
        if (!hasFile) {
            continue;
        }
        return std::make_unique<HapAssetImplMapping>(osstream);
    }
    return nullptr;
}

std::vector<std::unique_ptr<AssetMapping>> HapAssetProviderImpl::GetAsMappingFromI18n(
    const std::string& assetName) const
{
    ACE_SCOPED_TRACE("GetAsMappingFromI18n");
    std::lock_guard<std::mutex> lock(mutex_);

    std::vector<std::unique_ptr<AssetMapping>> i18nVector;
    CHECK_NULL_RETURN(runtimeExtractor_, i18nVector);
    for (const auto& basePath : assetBasePaths_) {
        std::string fileName = basePath + assetName;
        bool hasFile = runtimeExtractor_->HasEntry(fileName);
        if (!hasFile) {
            continue;
        }
        std::ostringstream osstream;
        hasFile = runtimeExtractor_->GetFileBuffer(fileName, osstream);
        if (!hasFile) {
            continue;
        }
        i18nVector.push_back(std::make_unique<HapAssetImplMapping>(osstream));
    }
    return i18nVector;
}

std::string HapAssetProviderImpl::GetAssetPath(const std::string& assetName, bool isAddHapPath)
{
    std::lock_guard<std::mutex> lock(mutex_);
    CHECK_NULL_RETURN(runtimeExtractor_, "");
    for (const auto& basePath : assetBasePaths_) {
        std::string fileName = basePath + assetName;
        bool hasFile = runtimeExtractor_->HasEntry(fileName);
        if (!hasFile) {
            continue;
        }
        return isAddHapPath ? (hapPath_ + "/" + basePath) : fileName;
    }
    LOGI("Cannot find base path of %{public}s", assetName.c_str());
    return "";
}

void HapAssetProviderImpl::GetAssetList(const std::string& path, std::vector<std::string>& assetList)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!runtimeExtractor_) {
        LOGW("RuntimeExtractor null:%{public}s", loadPath_.c_str());
        return;
    }
    for (const auto& basePath : assetBasePaths_) {
        std::string assetPath = basePath + path;
        bool res = runtimeExtractor_->IsDirExist(assetPath);
        if (!res) {
            continue;
        }
        res = runtimeExtractor_->GetFileList(assetPath, assetList);
        if (!res) {
            continue;
        }
        return;
    }
    LOGI("Cannot Get File List from %{public}s", path.c_str());
}

bool HapAssetProviderImpl::GetFileInfo(const std::string& fileName, MediaFileInfo& fileInfo) const
{
    std::lock_guard<std::mutex> lock(mutex_);
    CHECK_NULL_RETURN(runtimeExtractor_, false);
    OHOS::AbilityBase::FileInfo fileInfoAbility;
    auto state = runtimeExtractor_->GetFileInfo(fileName, fileInfoAbility);
    if (!state) {
        LOGE("GetFileInfo failed, fileName=%{public}s", fileName.c_str());
        return false;
    }
    fileInfo.fileName = fileInfoAbility.fileName;
    fileInfo.offset = fileInfoAbility.offset;
    fileInfo.length = fileInfoAbility.length;
    fileInfo.lastModTime = fileInfoAbility.lastModTime;
    fileInfo.lastModDate = fileInfoAbility.lastModDate;
    return true;
}

bool ReadHspModuleBuffer(const std::string& request, uint8_t** buffer, size_t* bufferSize)
{
    if (request.empty() || buffer == nullptr || bufferSize == nullptr) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to request ex module buffer, path is empty");
        return false;
    }
    if (!StringUtils::StartWith(request, BUNDLE_REQUEST_TAG)) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to request ex module buffer, path is not @bundle");
        return false;
    }
    std::vector<std::string> paths;
    StringUtils::StringSplitter(request.substr(BUNDLE_START_POS), SPLIT_TAG, paths);
    if (paths.size() < BUNDLE_AND_MODULE_SIZE) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to request ex module buffer, path is illegal");
        return false;
    }
    auto hspBundleName = paths[0];
    auto hspModuleName = paths[1];
    std::string hspPath;
    if (!GetHspModulePath(hspBundleName, hspModuleName, hspPath)) {
        return false;
    }
    bool newCreate = false;
    auto extractor = AbilityBase::ExtractorUtil::GetExtractor(hspPath, newCreate);
    if (!extractor) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to create extractor");
        return false;
    }
    auto data = extractor->GetSafeData(MERGE_ABC_PATH);
    if (!data) {
        TAG_LOGE(AceLogTag::ACE_DEFAULT_DOMAIN, "fail to get merge abc");
        return false;
    }
    *buffer = data->GetDataPtr();
    *bufferSize = data->GetDataLen();
    return true;
}

} // namespace OHOS::Ace
