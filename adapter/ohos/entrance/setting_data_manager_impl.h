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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SETTING_DATA_MANAGER_IMPL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SETTING_DATA_MANAGER_IMPL_H

#include "datashare_helper.h"
#include "errors.h"
#include "setting_data_observer.h"

#include "core/common/setting_data_manager.h"

namespace OHOS::Ace {

class SettingDataManagerImpl : public SettingDataManager {
public:
    SettingDataManagerImpl() = default;
    ~SettingDataManagerImpl() override = default;
    int32_t Initialize() override;

    bool IsInitialized() const override;

    int32_t GetCurrentUserId() override;

    int32_t RegisterObserver(
        const std::string& key, const DataUpdateFunc& updateFunc, int32_t userId = INVALID_USER_ID) override;

    int32_t UnregisterObserver(const std::string& key, int32_t userId = INVALID_USER_ID) override;

    int32_t GetStringValue(
        const std::string& key, std::string& value, int32_t userId = INVALID_USER_ID) const override;

    int32_t GetInt32ValueStrictly(
        const std::string& key, int32_t& value, int32_t userId = INVALID_USER_ID) const override;

private:
    int32_t RegisterObserverInner(const sptr<SettingDataObserver>& observer) const;

    int32_t UnregisterObserverInner(const sptr<SettingDataObserver>& observer) const;

    void CreateDataShareHelperAndUri(int32_t userId, const std::string& key, std::string& uri,
        std::shared_ptr<DataShare::DataShareHelper>& helper) const;

    std::shared_ptr<DataShare::DataShareHelper> CreateDataShareHelper() const;

    std::shared_ptr<DataShare::DataShareHelper> CreateUserDbDataShareHelper(int32_t userId) const;

    static bool ReleaseDataShareHelper(const std::shared_ptr<DataShare::DataShareHelper>& helper);

    static inline std::string GenerateObserverName(const std::string& key, int32_t userId);

    static sptr<SettingDataObserver> CreateObserver(
        const std::string& key, const DataUpdateFunc& updateFunc, int32_t userId = INVALID_USER_ID);

    static std::string AssembleUri(const std::string& key);

    static std::string AssembleUserDbUri(int32_t userId, const std::string& key);

    std::mutex initializeMutex_;
    bool isInitialized_ = false;
    sptr<IRemoteObject> remoteObject_;

    std::mutex observersMutex_;
    std::map<std::string, sptr<SettingDataObserver>> observers_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_SETTING_DATA_MANAGER_IMPL_H
