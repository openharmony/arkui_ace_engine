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

#ifndef FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_DATA_SHARE_OBSERVER_HELPER_H
#define FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_DATA_SHARE_OBSERVER_HELPER_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "base/resource/data_ability_helper.h"
#include "data_ability_observer_stub.h"

namespace OHOS::AbilityRuntime { class Context; }
namespace OHOS::DataShare { class DataShareHelper; }
namespace OHOS { class Uri; }

namespace OHOS::Ace {
namespace Platform { class AceContainer; }

inline constexpr int32_t INVALID_USER_ID = -1;
using DataShareObserverCallBack = std::function<void(std::string&, int32_t, bool)>;

enum DataShareObserverErrorCode : int32_t {
    SUCCESS                         = 0,
    ERR_OBSERVER_HELPER_NULL        = -1,   // Observer Helper of DataProviderManagerStandard is nullptr
    ERR_HELPER_NULL                 = -2,   // DataShareHelper is nullptr
    ERR_INVALID_USER_ID             = -3,   // Invalid user ID
    ERR_OBSERVER_NOT_FOUND          = -4,   // Observer not found
    ERR_OBSERVER_ALLOC_FAILED       = -5,   // Failed to allocate observer
    ERR_QUERY_RESULTSET_NULL        = -6,   // Query result set is null
    ERR_QUERY_GO_FIRST_ROW_FAILED   = -7,   // Failed to go to first row
    ERR_QUERY_GET_STRING_FAILED     = -8,   // Failed to get string value
};

class DataShareObserverHelper : public DataAbilityHelper {
    DECLARE_ACE_TYPE(DataShareObserverHelper, DataAbilityHelper);

public:
    class SettingsDataObserver : public AAFwk::DataAbilityObserverStub {
    public:
        SettingsDataObserver(const std::string& key, int32_t userId, DataShareObserverCallBack&& callback);
        ~SettingsDataObserver() override = default;
        void OnChange() override;
        int32_t userId_ = -1;
        void OnChangeInner(bool isPostToUITask = true);
    private:
        std::string key_;
        std::string value_ = "";
        DataShareObserverCallBack callback_;
    };

    DataShareObserverHelper(const std::shared_ptr<OHOS::AbilityRuntime::Context>& runtimeContext,
        const WeakPtr<Platform::AceContainer>& container, bool useStageModel);
    ~DataShareObserverHelper() override = default;

    // DataAbilityHelper interface implementation (observer related)
    int32_t RegisterDataShareSmartEdgeStateObserver() override;
    int32_t UnregisterDataShareObservers() override;
    bool IsInSmartEdgeState() override;
    void SetSmartEdgeStateInfo(bool isSmartEdgeState) override;
    bool QuerySmartEdgeState() override;

    // DataAbilityHelper interface implementation (data access related - empty implementations)
    int32_t OpenFile(const std::string& uriStr, const std::string& mode) override { return -1; }
    void* QueryThumbnailResFromDataAbility(const std::string& uri) override { return nullptr; }

private:
    std::shared_ptr<DataShare::DataShareHelper> CreateDataShareHelper(int32_t userId);
    bool ReleaseDataShareHelper(std::shared_ptr<DataShare::DataShareHelper> helper);
    Uri MakeUri(const std::string &key, int32_t userId);
    int32_t GetActiveOsAccountId();
    int32_t RegisterObserver(const std::string& key, DataShareObserverCallBack&& func);
    int32_t UnregisterObserver(const std::string& key);
    int32_t GetValue(const std::string &key, std::string &value);
    int32_t GetValueByUserId(const std::string &key, std::string &value, int32_t userId);
    DataShareObserverCallBack CreateSmartEdgeStateCallback();
    int32_t UnregisterDataShareSmartEdgeStateObserver();
    std::weak_ptr<OHOS::AbilityRuntime::Context> runtimeContext_;
    WeakPtr<Platform::AceContainer> container_;
    bool useStageModel_ = false;
    std::unordered_map<std::string, sptr<SettingsDataObserver>> observerMap_;
    bool isSmartEdgeState_ = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ACE_ENGINE_ADAPTER_OHOS_ENTRANCE_DATA_SHARE_OBSERVER_HELPER_H
