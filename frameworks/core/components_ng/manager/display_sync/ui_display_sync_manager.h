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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_MANAGER_H

#include <unordered_map>
#include <mutex>
#include <queue>

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "base/log/log.h"
#include "base/utils/base_id.h"
#include "base/log/ace_trace.h"
#include "base/utils/system_properties.h"
#include "ui_display_sync.h"

namespace OHOS::Ace {
using IdType = uint64_t;
using IdToDisplaySyncMap = std::unordered_map<IdType, WeakPtr<UIDisplaySync>>;

class ACE_FORCE_EXPORT UIDisplaySyncManager : public AceType {
    DECLARE_ACE_TYPE(UIDisplaySyncManager, AceType)
public:
    bool AddDisplaySync(const RefPtr<UIDisplaySync>& displaySync);
    bool RemoveDisplaySync(const RefPtr<UIDisplaySync>& displaySync);
    bool HasDisplaySync(const RefPtr<UIDisplaySync>& displaySync);

    void DispatchFunc(int64_t nanoTimestamp);

    bool SetVsyncRate(int32_t vsyncRate);
    int32_t GetVsyncRate() const;
    bool SetVsyncPeriod(int64_t vsyncPeriod);
    int64_t GetVsyncPeriod() const;
    bool SetRefreshRateMode(int32_t refreshRateMode);
    int32_t GetRefreshRateMode() const;
    int32_t GetDisplaySyncRate() const;
    IdToDisplaySyncMap GetUIDisplaySyncMap() const;
    void CheckSkipEnableProperty();
    bool IsSupportSkip() const;
    bool IsAutoRefreshRateMode() const;
    bool IsNonAutoRefreshRateMode() const;

    std::set<int32_t> FindRefreshRateFactors(int32_t refreshRate);
    int32_t FindMatchedRefreshRate(int32_t target);
    void FindAllRefreshRateFactors();

    int32_t GetAnimatorRate();
    bool IsAnimatorStopped();
    int32_t GetMonitorVsyncRate() const;

    UIDisplaySyncManager();
    ~UIDisplaySyncManager() noexcept override;

private:
    static const std::vector<int32_t> REFRESH_RATE_LIST;
    static constexpr int32_t ERROR_DELTA = 3;
    static constexpr float SECOND_IN_NANO = 1000000000.0f;
    
    int32_t sourceVsyncRate_ = 0;
    int64_t vsyncPeriod_ = 0;
    int32_t refreshRateMode_ = 0;
    int32_t monitorVsyncRate_ = 0;
    RefPtr<FrameRateRange> displaySyncRange_ = AceType::MakeRefPtr<FrameRateRange>();

    IdToDisplaySyncMap uiDisplaySyncMap_;
    std::once_flag isEnablePropertyFlag_;
    bool supportSkipEnabled_ = true;
    std::vector<int32_t> refreshRateFactors_;
    std::once_flag computeFactorsFlag_;
    std::priority_queue<int32_t> maxAnimatorRateHap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_UI_DISPLAY_SYNC_MANAGER_H
