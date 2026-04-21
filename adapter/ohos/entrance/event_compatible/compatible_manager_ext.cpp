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

#include "adapter/ohos/entrance/event_compatible/compatible_manager_ext.h"

#include "bundle_constants.h"
#include "cJSON.h"
#include "iservice_registry.h"
#include "rdb_errno.h"
#include "system_ability_definition.h"

#include "base/log/log_wrapper.h"

#ifdef OS_ACCOUNT_EXISTS
#include "os_account_manager.h"
#endif

namespace OHOS::Ace::NG {

constexpr const char* SETTING_URI_PROXY =
    "datashare:///com.ohos.settingsdata/entry/settingsdata/SETTINGSDATA?Proxy=true";
constexpr const char* SETTINGS_USER_DATA_URI =
    "datashare:///com.ohos.settingsdata/entry/settingsdata/USER_SETTINGSDATA_";
constexpr const char* SETTINGS_DATA_EXT_URI = "datashare:///com.ohos.settingsdata.DataAbility";
constexpr const char* SETTINGS_DATA_KEY_URI = "&key=";
constexpr const char* SETTINGS_DATA_COLUMN_KEYWORD = "KEYWORD";
constexpr const char* SETTINGS_DATA_COLUMN_VALUE = "VALUE";
constexpr const char* COMPATIBLE_APP_STRATEGY = "WHITELIST_MOUSETRANSFORM_STRATEGY";
constexpr const char* COMPATIBLE_SETTING_STRATEGY = "COMPATIBLE_SETTING_STRATEGY";
constexpr const char* COMPATIBLE_APP_STRATEGY_INPUT_MODE = "inputMode";
const int32_t COMPATIBLE_MODE_DISABLE = 8;
constexpr const char* COMPATIBLE_APP_STRATEGY_MOUSE_TRANSFORM = "mouseTransform";
constexpr const char* COMPATIBLE_APP_STRATEGY_MODE = "mode";

int32_t CompatibleManagerExt::GetCompatibleinputMode(const std::string& bundleName)
{
    std::lock_guard<std::mutex> lock(compatibleInfoMapMutex_);
    if (!isSettingsDataLoaded_) {
        std::string jsonStr = GetSettingsDataStringValue();
        if (!ParseJsonToMap(jsonStr, compatibleInfoMap_)) {
            TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "parse json fail");
            return 0;
        }
        isSettingsDataLoaded_ = true;
    }
    std::string settingJsonStr = GetSettingsModeStringValue();
    if (ParseSettingJsonToMap(settingJsonStr, compatibleSettingInfoMap_)) {
        int32_t mode = 1;
        auto iter = compatibleSettingInfoMap_.find(bundleName);
        if (iter != compatibleSettingInfoMap_.end()) {
            mode = iter->second;
        }
        if (mode == COMPATIBLE_MODE_DISABLE) {
            TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "compatible set disable bundleName: %{public}s", bundleName.c_str());
            return 0;
        }
    }
    int32_t inputMode = 0;
    auto iter = compatibleInfoMap_.find(bundleName);
    if (iter != compatibleInfoMap_.end()) {
        inputMode = iter->second.inputMode;
    }
    TAG_LOGD(
        AceLogTag::ACE_XCOMPONENT, "end bundleName: %{public}s, inputMode: %{public}d", bundleName.c_str(), inputMode);
    return inputMode;
}

CompatibleInfo CompatibleManagerExt::GetCompatibleMouseTransform(const std::string& bundleName)
{
    if (!isSettingsDataLoaded_) {
        std::lock_guard<std::mutex> lock(compatibleInfoMapMutex_);
        if (!isSettingsDataLoaded_) {
            std::string jsonStr = GetSettingsDataStringValue();
            if (!ParseJsonToMap(jsonStr, compatibleInfoMap_)) {
                TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "parse json fail");
                return CompatibleInfo(false);
            }
            isSettingsDataLoaded_ = true;
        }
    }
    CompatibleInfo result;
    auto iter = compatibleInfoMap_.find(bundleName);
    if (iter != compatibleInfoMap_.end()) {
        result = iter->second;
    }
    return result;
}

std::shared_ptr<DataShare::DataShareHelper> CompatibleManagerExt::CreateDataShareHelper()
{
    auto sam = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (sam == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "GetSystemAbilityManager return nullptr");
        return nullptr;
    }
    auto remoteObj = sam->GetSystemAbility(BUNDLE_MGR_SERVICE_SYS_ABILITY_ID);
    if (remoteObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "GetSystemAbility return nullptr");
        return nullptr;
    }
    auto helper = DataShare::DataShareHelper::Creator(remoteObj, SETTING_URI_PROXY, SETTINGS_DATA_EXT_URI);
    if (helper == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper is nullptr");
        return nullptr;
    }
    return helper;
}

bool CompatibleManagerExt::ReleaseDataShareHelper(std::shared_ptr<DataShare::DataShareHelper>& helper)
{
    if (helper == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper is null");
        return false;
    }
    if (!helper->Release()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "release helper fail");
        return false;
    }
    helper = nullptr;
    return true;
}

std::string CompatibleManagerExt::GetSettingsDataStringValue()
{
    auto helper = CreateDataShareHelper();
    if (helper == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper nullptr");
        return "";
    }
    std::vector<std::string> columns = { SETTINGS_DATA_COLUMN_VALUE };
    DataShare::DataSharePredicates predicates;
    predicates.EqualTo(SETTINGS_DATA_COLUMN_KEYWORD, COMPATIBLE_APP_STRATEGY);
    std::string uriString = SETTING_URI_PROXY;
    Uri uri(uriString + SETTINGS_DATA_KEY_URI + COMPATIBLE_APP_STRATEGY);
    auto resultSet = helper->Query(uri, predicates, columns);
    ReleaseDataShareHelper(helper);
    if (resultSet == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper->Query return nullptr");
        return "";
    }
    int32_t count;
    resultSet->GetRowCount(count);
    if (count == 0) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "not found value, count=%{public}d", count);
        resultSet->Close();
        return "";
    }
    const int32_t index = 0;
    resultSet->GoToRow(index);
    std::string value;
    int32_t ret = resultSet->GetString(index, value);
    if (ret != NativeRdb::E_OK) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "resultSet->GetString return not ok, ret=%{public}d", ret);
        resultSet->Close();
        return "";
    }
    resultSet->Close();
    return value;
}

void ParseCompatibleInfo(cJSON* childNode, CompatibleInfo& info)
{
    cJSON* inputMode = cJSON_GetObjectItem(childNode, COMPATIBLE_APP_STRATEGY_INPUT_MODE);
    cJSON* mode = cJSON_GetObjectItem(childNode, COMPATIBLE_APP_STRATEGY_MODE);
    cJSON* mouseTransform = cJSON_GetObjectItem(childNode, COMPATIBLE_APP_STRATEGY_MOUSE_TRANSFORM);

    if (inputMode == nullptr || !cJSON_IsNumber(inputMode)) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "inputMode is invalid.");
    } else {
        info.inputMode = inputMode->valueint;
    }

    if (mode == nullptr || !cJSON_IsNumber(mode)) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "mode is invalid.");
    } else {
        info.mode = mode->valueint;
    }

    if (mouseTransform == nullptr || !cJSON_IsBool(mouseTransform)) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "mouseTransform is invalid.");
    } else {
        info.mouseTransform = cJSON_IsTrue(mouseTransform) != 0;
    }
}

bool CompatibleManagerExt::ParseJsonToMap(
    const std::string& jsonStr, std::map<std::string, CompatibleInfo>& compatibleMap)
{
    if (jsonStr.empty()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "json str is empty.");
        return false;
    }

    cJSON* root = cJSON_Parse(jsonStr.c_str());
    if (root == nullptr || !cJSON_IsObject(root)) {
        cJSON_Delete(root);
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "root is not object.");
        return false;
    }
    cJSON* childNode;
    int32_t rootSize = cJSON_GetArraySize(root);
    for (int32_t i = 0; i < rootSize; i++) {
        childNode = cJSON_GetArrayItem(root, i);
        if (childNode == nullptr) {
            continue;
        }
        const char* key = childNode->string;
        if (key == nullptr) {
            continue;
        }
        CompatibleInfo info;
        ParseCompatibleInfo(childNode, info);
        compatibleMap[key] = info;
    }
    cJSON_Delete(root);
    return true;
}

std::string CompatibleManagerExt::GetSettingsModeStringValue()
{
    auto helper = CreateDataShareHelper();
    if (helper == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper nullptr");
        return "";
    }
    int32_t userId = GetCurrentActiveUserId();
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "get current user id is %{public}d.", userId);
    if (userId == AppExecFwk::Constants::INVALID_USERID) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "get user id failed");
        return "";
    }
    std::vector<std::string> columns = { SETTINGS_DATA_COLUMN_VALUE };
    DataShare::DataSharePredicates predicates;
    predicates.EqualTo(SETTINGS_DATA_COLUMN_KEYWORD, COMPATIBLE_SETTING_STRATEGY);
    std::string uriString = SETTINGS_USER_DATA_URI;
    Uri uri(uriString + std::to_string(userId) + "?Proxy=true" + SETTINGS_DATA_KEY_URI + COMPATIBLE_SETTING_STRATEGY);
    auto resultSet = helper->Query(uri, predicates, columns);
    ReleaseDataShareHelper(helper);
    if (resultSet == nullptr) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "helper->Query return nullptr");
        return "";
    }
    int32_t count;
    resultSet->GetRowCount(count);
    if (count == 0) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "not found value, count=%{public}d", count);
        resultSet->Close();
        return "";
    }
    const int32_t index = 0;
    resultSet->GoToRow(index);
    std::string value;
    int32_t ret = resultSet->GetString(index, value);
    if (ret != NativeRdb::E_OK) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "resultSet->GetString return not ok, ret=%{public}d", ret);
        resultSet->Close();
        return "";
    }
    resultSet->Close();
    return value;
}

bool CompatibleManagerExt::ParseSettingJsonToMap(
    const std::string& jsonStr, std::map<std::string, int32_t>& compatibleMap)
{
    if (jsonStr.empty()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "json str is empty.");
        return false;
    }
    TAG_LOGD(AceLogTag::ACE_XCOMPONENT, "jsonStr : %{public}s", jsonStr.c_str());
    cJSON* root = cJSON_Parse(jsonStr.c_str());
    if (root == nullptr || !cJSON_IsObject(root)) {
        cJSON_Delete(root);
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "root is not object.");
        return false;
    }
    compatibleMap.clear();
    cJSON* item = root->child;
    while (item != nullptr) {
        const char* key = item->string;
        const int value = item->valueint;
        compatibleMap[key] = value;
        item = item->next;
    }
    cJSON_Delete(root);
    return true;
}

int32_t CompatibleManagerExt::GetCurrentActiveUserId()
{
#ifdef OS_ACCOUNT_EXISTS
    std::vector<int32_t> activeIds;
    int ret = AccountSA::OsAccountManager::QueryActiveOsAccountIds(activeIds);
    if (ret != 0) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "QueryActiveOsAccountIds failed ret:%{public}d", ret);
        return AppExecFwk::Constants::INVALID_USERID;
    }
    if (activeIds.empty()) {
        TAG_LOGE(AceLogTag::ACE_XCOMPONENT, "QueryActiveOsAccountIds activeIds empty");
        return AppExecFwk::Constants::INVALID_USERID;
    }
    return activeIds[0];
#else
    TAG_LOGI(AceLogTag::ACE_XCOMPONENT, "ACCOUNT_ENABLE is false");
    return AppExecFwk::Constants::INVALID_USERID;
#endif
}
} // namespace OHOS::Ace::NG
