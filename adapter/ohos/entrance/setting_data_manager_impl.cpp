/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/setting_data_manager_impl.h"

#include <charconv>

#include "iservice_registry.h"
#include "system_ability_definition.h"
#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

#include "base/log/log_wrapper.h"

namespace OHOS::Ace {
namespace {
constexpr const char* SETTING_DATA_URI =
    "datashare:///com.ohos.settingsdata/entry/settingsdata/SETTINGSDATA?Proxy=true";
constexpr const char* SETTING_DATA_USER_URI_PREFIX =
    "datashare:///com.ohos.settingsdata/entry/settingsdata/USER_SETTINGSDATA_";
constexpr const char* SETTING_DATA_USER_URI_SUFFIX = "?Proxy=true";
constexpr const char* SETTING_DATA_EXT_URI = "datashare:///com.ohos.settingsdata.DataAbility";
constexpr const char* SETTING_DATA_KEY_URI = "&key=";
constexpr const char* SETTING_DATA_COLUMN_KEYWORD = "KEYWORD";
constexpr const char* SETTING_DATA_COLUMN_VALUE = "VALUE";
constexpr int32_t INDEX0 = 0;
constexpr int32_t USER100 = 100;
} // namespace

SettingDataManager& SettingDataManager::GetInstance()
{
    static SettingDataManagerImpl instance;
    return instance;
}

int32_t SettingDataManagerImpl::Initialize()
{
    std::lock_guard guard(initializeMutex_);
    if (isInitialized_) {
        return ERR_OK;
    }
    const auto saMgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (saMgr == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::saMgr is null");
        return ERR_NO_INIT;
    }
    const auto remoteObj = saMgr->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (remoteObj == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::remoteObj is null");
        return ERR_NO_INIT;
    }
    remoteObject_ = remoteObj;
    isInitialized_ = true;
    return ERR_OK;
}

bool SettingDataManagerImpl::IsInitialized() const
{
    return isInitialized_;
}

int32_t SettingDataManagerImpl::GetCurrentUserId()
{
#ifdef OS_ACCOUNT_EXISTS
    std::vector<int32_t> ids;
    auto code = AccountSA::OsAccountManager::QueryActiveOsAccountIds(ids);
    if (code != ERR_OK || ids.empty()) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::no active user.");
        return INVALID_USER_ID;
    }
    TAG_LOGD(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::GetCurrentUserId:%{public}d", ids[0]);
    return ids[0];
#else
    return INVALID_USER_ID;
#endif
}

int32_t SettingDataManagerImpl::RegisterObserver(
    const std::string& key, const DataUpdateFunc& updateFunc, const int32_t userId)
{
    if (!isInitialized_) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::not initialized");
        return ERR_NO_INIT;
    }

    std::lock_guard guard(observersMutex_);
    const std::string observerName = GenerateObserverName(key, userId);
    const auto& iter = observers_.find(observerName);
    if (iter != observers_.end()) {
        return ERR_OK;
    }

    sptr<SettingDataObserver> observer = CreateObserver(key, updateFunc, userId);
    int32_t code = RegisterObserverInner(observer);
    if (code != ERR_OK) {
        return code;
    }
    observers_.emplace(observerName, observer);
    return ERR_OK;
}

int32_t SettingDataManagerImpl::UnregisterObserver(const std::string& key, const int32_t userId)
{
    const std::string observerName = GenerateObserverName(key, userId);
    std::lock_guard guard(observersMutex_);
    const auto& iter = observers_.find(observerName);
    if (iter == observers_.end()) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::observerName: %{public}s is not found",
            observerName.c_str());
        return ERR_INVALID_VALUE;
    }
    if (iter->second == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::observerName: %{public}s observer is null",
            observerName.c_str());
        observers_.erase(iter);
        return ERR_INVALID_OPERATION;
    }

    int32_t code = UnregisterObserverInner(iter->second);
    observers_.erase(iter);
    return code;
}

int32_t SettingDataManagerImpl::GetStringValue(const std::string& key, std::string& value, const int32_t userId) const
{
    std::string uriString;
    std::shared_ptr<DataShare::DataShareHelper> helper;
    CreateDataShareHelperAndUri(userId, key, uriString, helper);
    if (helper == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::helper is null, userId: %{public}d", userId);
        return ERR_NO_INIT;
    }

    std::vector<std::string> columns = { SETTING_DATA_COLUMN_VALUE };
    DataShare::DataSharePredicates predicates;
    predicates.EqualTo(SETTING_DATA_COLUMN_KEYWORD, key);
    Uri uri(uriString);
    auto result = helper->Query(uri, predicates, columns);
    ReleaseDataShareHelper(helper);
    if (result == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "SettingDataManager::query return null, key: %{public}s, userId: %{public}d", key.c_str(), userId);
        return ERR_INVALID_OPERATION;
    }
    int32_t count = 0;
    result->GetRowCount(count);
    if (count == 0) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::not found, key: %{public}s, userId: %{public}d",
            key.c_str(), userId);
        result->Close();
        return ERR_NAME_NOT_FOUND;
    }

    result->GoToRow(INDEX0);
    int32_t code = result->GetString(INDEX0, value);
    if (code != 0) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "SettingDataManager::get string failed, key: %{public}s, userId: %{public}d, ret: %{public}d", key.c_str(),
            userId, code);
        result->Close();
        return ERR_INVALID_VALUE;
    }
    result->Close();
    return ERR_OK;
}

int32_t SettingDataManagerImpl::GetInt32ValueStrictly(
    const std::string& key, int32_t& value, const int32_t userId) const
{
    std::string valueString;
    int32_t code = GetStringValue(key, valueString, userId);
    if (code != ERR_OK) {
        return static_cast<int32_t>(code);
    }
    int32_t convertedValue;
    auto res = std::from_chars(valueString.c_str(), valueString.c_str() + valueString.size(), convertedValue);
    if (res.ec != std::errc()) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "SettingDataManager::key: %{public}s, userId: %{public}d, value: %{public}s failed to convert to int",
            key.c_str(), userId, valueString.c_str());
        return ERR_INVALID_VALUE;
    }
    if (std::to_string(convertedValue) != valueString) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "SettingDataManager::key: %{public}s, userId: %{public}d, value: %{public}s is not strict int", key.c_str(),
            userId, valueString.c_str());
        return ERR_INVALID_VALUE;
    }
    value = convertedValue;
    return ERR_OK;
}

int32_t SettingDataManagerImpl::RegisterObserverInner(const sptr<SettingDataObserver>& observer) const
{
    if (observer == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::observer is null");
        return ERR_INVALID_OPERATION;
    }

    std::string uriString;
    std::shared_ptr<DataShare::DataShareHelper> helper;
    CreateDataShareHelperAndUri(observer->GetUserId(), observer->GetKey(), uriString, helper);
    if (helper == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::helper is null, userId: %{public}d",
            observer->GetUserId());
        return ERR_NO_INIT;
    }

    const Uri uri(uriString);
    helper->RegisterObserver(uri, observer);
    ReleaseDataShareHelper(helper);
    TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::register observer key: %{public}s, userId: %{public}d",
        observer->GetKey().c_str(), observer->GetUserId());
    return ERR_OK;
}

int32_t SettingDataManagerImpl::UnregisterObserverInner(const sptr<SettingDataObserver>& observer) const
{
    if (observer == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::observer is null");
        return ERR_INVALID_OPERATION;
    }

    std::string uriString;
    std::shared_ptr<DataShare::DataShareHelper> helper;
    CreateDataShareHelperAndUri(observer->GetUserId(), observer->GetKey(), uriString, helper);
    if (helper == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::helper is null");
        return ERR_NO_INIT;
    }

    const Uri uri(uriString);
    helper->UnregisterObserver(uri, observer);
    ReleaseDataShareHelper(helper);
    return ERR_OK;
}

void SettingDataManagerImpl::CreateDataShareHelperAndUri(const int32_t userId, const std::string& key, std::string& uri,
    std::shared_ptr<DataShare::DataShareHelper>& helper) const
{
    if (userId == INVALID_USER_ID) {
        uri = AssembleUri(key);
        helper = CreateDataShareHelper();
    } else {
        uri = AssembleUserDbUri(userId, key);
        helper = CreateUserDbDataShareHelper(userId);
    }
}

std::shared_ptr<DataShare::DataShareHelper> SettingDataManagerImpl::CreateDataShareHelper() const
{
    if (remoteObject_ == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::remoteObject_ is null");
        return nullptr;
    }
    const auto [errCode, helper] =
        DataShare::DataShareHelper::Create(remoteObject_, SETTING_DATA_URI, SETTING_DATA_EXT_URI);
    if (errCode != DataShare::E_OK) {
        TAG_LOGW(
            AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::create data share helper failed: %{public}d", errCode);
        return nullptr;
    }
    return helper;
}

std::shared_ptr<DataShare::DataShareHelper> SettingDataManagerImpl::CreateUserDbDataShareHelper(
    const int32_t userId) const
{
    if (remoteObject_ == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::remoteObject_ is null");
        return nullptr;
    }
    std::string userUri = SETTING_DATA_USER_URI_PREFIX + std::to_string(userId) + SETTING_DATA_USER_URI_SUFFIX;
    const auto [errCode, helper] = DataShare::DataShareHelper::Create(remoteObject_, userUri, SETTING_DATA_EXT_URI);
    if (errCode != DataShare::E_OK) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT,
            "SettingDataManager::create user data share helper failed: %{public}d, userId: %{public}d", errCode,
            userId);
        return nullptr;
    }
    return helper;
}

bool SettingDataManagerImpl::ReleaseDataShareHelper(const std::shared_ptr<DataShare::DataShareHelper>& helper)
{
    if (helper == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::helper is null");
        return false;
    }
    if (!helper->Release()) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::release data share helper failed");
        return false;
    }
    return true;
}

std::string SettingDataManagerImpl::GenerateObserverName(const std::string& key, const int32_t userId)
{
    return key + "::" + std::to_string(userId);
}

sptr<SettingDataObserver> SettingDataManagerImpl::CreateObserver(
    const std::string& key, const SettingDataObserver::UpdateFunc& updateFunc, const int32_t userId)
{
    sptr<SettingDataObserver> observer = sptr<SettingDataObserver>::MakeSptr();
    if (observer == nullptr) {
        TAG_LOGW(AceLogTag::ACE_VISUAL_EFFECT, "SettingDataManager::observer is null");
        return observer;
    }
    observer->SetKey(key);
    observer->SetUpdateFunc(updateFunc);
    observer->SetUserId(userId);
    return observer;
}

std::string SettingDataManagerImpl::AssembleUri(const std::string& key)
{
    std::string uriString = SETTING_DATA_URI;
    uriString.append(SETTING_DATA_KEY_URI + key);
    return uriString;
}

std::string SettingDataManagerImpl::AssembleUserDbUri(const int32_t userId, const std::string& key)
{
    std::string uriString = SETTING_DATA_USER_URI_PREFIX;
    uriString.append(std::to_string(userId) + SETTING_DATA_USER_URI_SUFFIX);
    uriString.append(SETTING_DATA_KEY_URI + key);
    return uriString;
}
} // namespace OHOS::Ace
