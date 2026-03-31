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

#include "adapter/ohos/entrance/data_share_observer_helper.h"

#include "adapter/ohos/entrance/ace_container.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"

#include "datashare_helper.h"
#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace {

constexpr const char *SETTING_URI_PROXY_PREFIX = "datashare:///com.ohos.settingsdata/entry/settingsdata/"
                                          "USER_SETTINGSDATA_";
constexpr const char *SETTING_URI_PROXY_SUFFIX = "?Proxy=true";
constexpr const char *SETTINGS_DATA_EXT_URI = "datashare:///com.ohos.settingsdata.DataAbility";
constexpr const char *SETTING_COLUMN_KEYWORD = "KEYWORD";
constexpr const char *SETTING_COLUMN_VALUE = "VALUE";
constexpr const char *SETTINGS_DATA_SMART_EDGE_KEY = "luo_shu_state_info"; //sceneboard.smartedge.status
constexpr const char *SETTINGS_DATA_SMART_EDGE_VALUE = "luoShuState"; //smartEdgeState
constexpr const int WAIT_TIME = 100; // 100ms

// SettingsDataObserver implementation
DataShareObserverHelper::SettingsDataObserver::SettingsDataObserver(
    const std::string& key, int32_t userId, DataShareObserverCallBack&& callback)
    : userId_(userId), key_(key), callback_(std::move(callback))
{}

void DataShareObserverHelper::SettingsDataObserver::OnChangeInner(bool isPostToUITask)
{
    if (callback_) {
        callback_(value_, userId_, isPostToUITask);
    }
}

void DataShareObserverHelper::SettingsDataObserver::OnChange()
{
    OnChangeInner();
}

// DataShareObserverHelper implementation
DataShareObserverHelper::DataShareObserverHelper(
    const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext,
    const WeakPtr<Platform::AceContainer>& container, bool useStageModel)
    : runtimeContext_(runtimeContext), container_(container), useStageModel_(useStageModel)
{}

std::shared_ptr<DataShare::DataShareHelper> DataShareObserverHelper::CreateDataShareHelper(int32_t userId)
{
    auto SETTING_URI_PROXY = std::string(SETTING_URI_PROXY_PREFIX) + std::to_string(userId) +
        std::string(SETTING_URI_PROXY_SUFFIX);
    auto context = runtimeContext_.lock();
    CHECK_NULL_RETURN(useStageModel_ && context && context->GetToken(), nullptr);
    auto [ret, helper] = DataShare::DataShareHelper::Create(context->GetToken(), SETTING_URI_PROXY,
        SETTINGS_DATA_EXT_URI, WAIT_TIME);
    return helper;
}

bool DataShareObserverHelper::ReleaseDataShareHelper(std::shared_ptr<DataShare::DataShareHelper> helper)
{
    CHECK_NULL_RETURN(helper, false);
    if (!helper->Release()) {
        LOGE("DataShareHelper, release helper failed");
        return false;
    }
    return true;
}

Uri DataShareObserverHelper::MakeUri(const std::string &key, int32_t userId)
{
    Uri uri(std::string(SETTING_URI_PROXY_PREFIX) + std::to_string(userId) +
        std::string(SETTING_URI_PROXY_SUFFIX) + "&key=" + key);
    return uri;
}

int32_t DataShareObserverHelper::GetActiveOsAccountId(void)
{
    std::vector<int32_t> accountIds;
#ifdef OS_ACCOUNT_EXISTS
    int ret = AccountSA::OsAccountManager::QueryActiveOsAccountIds(accountIds);
    if (ret != 0 || accountIds.empty()) {
        LOGE("DataShareHelper, QueryActiveOsAccountIds failed ret:%{public}d", ret);
        return INVALID_USER_ID;
    }
#else  // OS_ACCOUNT_EXISTS
    LOGW("DataShareHelper, os account part not exists, use default id.");
    accountIds.push_back(0);
#endif // OS_ACCOUNT_EXISTS
    return accountIds.front();
}

int32_t DataShareObserverHelper::RegisterObserver(const std::string& key, DataShareObserverCallBack&& func)
{
    auto it = observerMap_.find(key);
    if (it != observerMap_.end()) {
        return DataShareObserverErrorCode::SUCCESS;
    }
    auto userId = GetActiveOsAccountId();
    CHECK_NULL_RETURN(userId > INVALID_USER_ID, DataShareObserverErrorCode::ERR_INVALID_USER_ID);
    // Create new DataShareHelper each time
    auto helper = CreateDataShareHelper(userId);
    CHECK_NULL_RETURN(helper, DataShareObserverErrorCode::ERR_HELPER_NULL);
    sptr<SettingsDataObserver> observer = new (std::nothrow) SettingsDataObserver(key, userId, std::move(func));
    CHECK_NULL_RETURN(observer, DataShareObserverErrorCode::ERR_OBSERVER_ALLOC_FAILED);
    auto uri = MakeUri(key, userId);
    auto ret = helper->RegisterObserver(uri, observer);
    // Release DataShareHelper
    ReleaseDataShareHelper(helper);
    if (ret != DataShareObserverErrorCode::SUCCESS) {
        return ret;
    }
    observerMap_[key] = observer;
    observer->OnChangeInner(false);
    return DataShareObserverErrorCode::SUCCESS;
}

int32_t DataShareObserverHelper::UnregisterObserver(const std::string& key)
{
    auto it = observerMap_.find(key);
    if (it == observerMap_.end()) {
        LOGI("DataShareHelper, Observer for key '%{public}s' not found", key.c_str());
        return DataShareObserverErrorCode::SUCCESS;
    }
    auto dataObserver = it->second;
    CHECK_NULL_RETURN(dataObserver, DataShareObserverErrorCode::ERR_OBSERVER_NOT_FOUND);
    auto userId = dataObserver->userId_;
    CHECK_NULL_RETURN(userId > INVALID_USER_ID, DataShareObserverErrorCode::ERR_INVALID_USER_ID);
    // Create new DataShareHelper each time
    auto helper = CreateDataShareHelper(userId);
    CHECK_NULL_RETURN(helper, DataShareObserverErrorCode::ERR_HELPER_NULL);
    auto uri = MakeUri(key, userId);
    auto ret = helper->UnregisterObserver(uri, dataObserver);
    // Release DataShareHelper
    ReleaseDataShareHelper(helper);
    if (ret != DataShareObserverErrorCode::SUCCESS) {
        return ret;
    }
    observerMap_.erase(it);
    return DataShareObserverErrorCode::SUCCESS;
}

int32_t DataShareObserverHelper::GetValue(const std::string &key, std::string &value)
{
    return GetValueByUserId(key, value, GetActiveOsAccountId());
}

bool DataShareObserverHelper::QuerySmartEdgeState()
{
    bool isWatchOrWearable = SystemProperties::GetDeviceType() == DeviceType::WATCH ||
        SystemProperties::GetDeviceType() == DeviceType::WEARABLE;
    CHECK_NULL_RETURN(!isWatchOrWearable, false);
    std::string newestRawValue;
    if (auto ret = GetValueByUserId(SETTINGS_DATA_SMART_EDGE_KEY, newestRawValue, GetActiveOsAccountId()); ret) {
        LOGE("DataShareHelper, GetValueByUserId failed, ret: %{public}d", ret);
        return false;
    }
    auto jsonObject = JsonUtil::ParseJsonString(newestRawValue);
    bool isInSmartEdgeState = false;
    if (jsonObject && jsonObject->Contains(SETTINGS_DATA_SMART_EDGE_VALUE)) {
        isInSmartEdgeState = jsonObject->GetInt(SETTINGS_DATA_SMART_EDGE_VALUE, 0);
    }
    LOGI("DataShareHelper, isInSmartEdgeState: %{public}d", isInSmartEdgeState);
    return isInSmartEdgeState;
}

int32_t DataShareObserverHelper::GetValueByUserId(const std::string &key, std::string &value, int32_t userId)
{
    CHECK_NULL_RETURN(userId > INVALID_USER_ID, DataShareObserverErrorCode::ERR_INVALID_USER_ID);
    auto helper = CreateDataShareHelper(userId);
    if (helper == nullptr) {
        return DataShareObserverErrorCode::ERR_HELPER_NULL;
    }
    std::vector<std::string> columns;
    DataShare::DataSharePredicates predicates;
    predicates.EqualTo(SETTING_COLUMN_KEYWORD, key);
    Uri uri = MakeUri(key, userId);
    auto resultSet = helper->Query(uri, predicates, columns);
    ReleaseDataShareHelper(helper);
    if (resultSet == nullptr) {
        return DataShareObserverErrorCode::ERR_QUERY_RESULTSET_NULL;
    }
    int32_t count = 0;
    resultSet->GetRowCount(count);
    if (count == 0) {
        LOGI("DataShareHelper, query success, but no value, key=%{public}s", key.c_str());
        resultSet->Close();
        return DataShareObserverErrorCode::SUCCESS;
    }
    if (resultSet->GoToFirstRow()) {
        resultSet->Close();
        return DataShareObserverErrorCode::ERR_QUERY_GO_FIRST_ROW_FAILED;
    }
    int32_t columnIndex = 0;
    resultSet->GetColumnIndex(SETTING_COLUMN_VALUE, columnIndex);
    int32_t ret = resultSet->GetString(columnIndex, value);
    if (ret) {
        resultSet->Close();
        return DataShareObserverErrorCode::ERR_QUERY_GET_STRING_FAILED;
    }
    resultSet->Close();
    return DataShareObserverErrorCode::SUCCESS;
}

DataShareObserverCallBack DataShareObserverHelper::CreateSmartEdgeStateCallback()
{
    return [containerWeak = container_, observerHelperWeak = WeakClaim(this)](std::string& value, int32_t userId,
        bool isPostToUITask) {
        auto helper = observerHelperWeak.Upgrade();
        CHECK_NULL_VOID(helper);
        std::string newestRawValue;
        if (auto ret = helper->GetValueByUserId(SETTINGS_DATA_SMART_EDGE_KEY, newestRawValue, userId); ret) {
            LOGE("DataShareHelper, GetValueByUserId failed, ret: %{public}d", ret);
            return;
        }
        auto jsonObject = JsonUtil::ParseJsonString(newestRawValue);
        std::string newestValue;
        if (jsonObject && jsonObject->Contains(SETTINGS_DATA_SMART_EDGE_VALUE)) {
            newestValue = std::to_string(jsonObject->GetInt(SETTINGS_DATA_SMART_EDGE_VALUE, 0));
        }
        LOGI("DataShareHelper, OnChange value: %{public}s", newestValue.c_str());
        CHECK_NULL_VOID(newestValue != value);
        value = newestValue;

        bool isInSmartEdgeState = newestValue.empty() ? false : (std::stoi(newestValue) != 0);
        if (isPostToUITask) {
            auto container = containerWeak.Upgrade();
            CHECK_NULL_VOID(container);
            auto taskExecutor = container->GetTaskExecutor();
            CHECK_NULL_VOID(taskExecutor);
            taskExecutor->PostTask(
                [isInSmartEdgeState, observerHelperWeak] {
                    LOGI("DataShareHelper, Settings changed: %{public}d", isInSmartEdgeState);
                    auto helper = observerHelperWeak.Upgrade();
                    CHECK_NULL_VOID(helper);
                    helper->SetSmartEdgeStateInfo(isInSmartEdgeState);
                }, TaskExecutor::TaskType::UI, "SettingsDataObserverCallback");
        } else {
            LOGI("DataShareHelper, Settings change: %{public}d", isInSmartEdgeState);
            helper->SetSmartEdgeStateInfo(isInSmartEdgeState);
        }
    };
}

int32_t DataShareObserverHelper::RegisterDataShareSmartEdgeStateObserver()
{
    bool isWatchOrWearable = SystemProperties::GetDeviceType() == DeviceType::WATCH ||
                        SystemProperties::GetDeviceType() == DeviceType::WEARABLE;
    CHECK_NULL_RETURN(!isWatchOrWearable, DataShareObserverErrorCode::SUCCESS);

    auto callback = CreateSmartEdgeStateCallback();
    return RegisterObserver(SETTINGS_DATA_SMART_EDGE_KEY, std::move(callback));
}

int32_t DataShareObserverHelper::UnregisterDataShareSmartEdgeStateObserver()
{
    bool isWatchOrWearable = SystemProperties::GetDeviceType() == DeviceType::WATCH ||
                        SystemProperties::GetDeviceType() == DeviceType::WEARABLE;
    CHECK_NULL_RETURN(!isWatchOrWearable, DataShareObserverErrorCode::SUCCESS);
    return UnregisterObserver(SETTINGS_DATA_SMART_EDGE_KEY);
}

int32_t DataShareObserverHelper::UnregisterDataShareObservers()
{
    return UnregisterDataShareSmartEdgeStateObserver();
}

bool DataShareObserverHelper::IsInSmartEdgeState()
{
    return isSmartEdgeState_;
}

void DataShareObserverHelper::SetSmartEdgeStateInfo(bool isSmartEdgeState)
{
    isSmartEdgeState_ = isSmartEdgeState;
}

} // namespace OHOS::Ace
