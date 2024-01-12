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
#include "core/components_ng/manager/display_sync/ui_display_sync_manager.h"

namespace OHOS::Ace {
const std::vector<int32_t> UIDisplaySyncManager::REFRESH_RATE_LIST = { 30, 60, 72, 90, 120, 144 };

void UIDisplaySyncManager::DispatchFunc(uint64_t nanoTimestamp)
{
    CheckSkipEnableProperty();
    displaySyncRange_->Reset();

    if (uiDisplaySyncMap_.empty()) {
        return;
    }

    IdToDisplaySyncMap backupedMap(uiDisplaySyncMap_);

    int32_t VSyncPeriod = GetVsyncPeriod();
    for (const auto& [Id, weakDisplaySync] : backupedMap) {
        auto displaySync = weakDisplaySync.Upgrade();
        if (displaySync) {
            auto rateRange = displaySync->GetDisplaySyncData()->rateRange_;
            if (rateRange->IsValid()) {
                displaySyncRange_->Merge(*rateRange);
            }

            displaySync->CheckRate(sourceVsyncRate_, refreshRateMode_);
            displaySync->UpdateData(nanoTimestamp, VSyncPeriod);
            if (IsAutoRefreshRateMode() ||
                (IsNonAutoRefreshRateMode() && IsSupportSkip())) {
                displaySync->JudgeWhetherSkip();
            }
            displaySync->OnFrame();
        } else {
            uiDisplaySyncMap_.erase(Id);
        }
    }

    return;
}

bool UIDisplaySyncManager::HasDisplaySync(const RefPtr<UIDisplaySync>& displaySync)
{
    if (displaySync && uiDisplaySyncMap_.count(displaySync->GetId())) {
        return true;
    }
    return false;
}

bool UIDisplaySyncManager::AddDisplaySync(const RefPtr<UIDisplaySync>& displaySync)
{
    if (HasDisplaySync(displaySync)) {
        return false;
    }
    uiDisplaySyncMap_[displaySync->GetId()] = displaySync;
    return true;
}

bool UIDisplaySyncManager::RemoveDisplaySync(const RefPtr<UIDisplaySync>& displaySync)
{
    if (HasDisplaySync(displaySync)) {
        uiDisplaySyncMap_.erase(displaySync->GetId());
        return true;
    }
    return false;
}

bool UIDisplaySyncManager::SetVsyncRate(int32_t vsyncRate)
{
    if (vsyncRate < 0) {
        return false;
    }

    if (sourceVsyncRate_ == vsyncRate) {
        return false;
    }
    sourceVsyncRate_ = vsyncRate;
    return true;
}

int32_t UIDisplaySyncManager::GetVsyncRate() const
{
    return sourceVsyncRate_;
}

bool UIDisplaySyncManager::SetVsyncPeriod(int64_t vsyncPeriod)
{
    if (vsyncPeriod < 0) {
        return false;
    }

    if (vsyncPeriod_ == vsyncPeriod) {
        return false;
    }
    vsyncPeriod_ = vsyncPeriod;

    int32_t rate = static_cast<int32_t>(std::ceil(SECOND_IN_NANO / vsyncPeriod_));
    for (const auto& refreshRate : REFRESH_RATE_LIST) {
        if (std::abs(rate - refreshRate) <= ERROR_DELTA) {
            SetVsyncRate(refreshRate);
            return true;
        }
    }

    return true;
}

int64_t UIDisplaySyncManager::GetVsyncPeriod() const
{
    return vsyncPeriod_;
}

bool UIDisplaySyncManager::SetRefreshRateMode(int32_t refreshRateMode)
{
    if (refreshRateMode < -1) {
        return false;
    }

    if (refreshRateMode_ == refreshRateMode) {
        return false;
    }

    refreshRateMode_ = refreshRateMode;
    return true;
}

int32_t UIDisplaySyncManager::GetRefreshRateMode() const
{
    return refreshRateMode_;
}

int32_t UIDisplaySyncManager::GetDisplaySyncRate() const
{
    int32_t displaySyncRate = displaySyncRange_->preferred_;
    return displaySyncRate;
}

IdToDisplaySyncMap UIDisplaySyncManager::GetUIDisplaySyncMap() const
{
    return uiDisplaySyncMap_;
}

void UIDisplaySyncManager::CheckSkipEnableProperty()
{
    std::call_once(isEnablePropertyFlag_, [this] () {
        supportSkipEnabled_ = SystemProperties::GetDisplaySyncSkipEnabled();
    });
}

bool UIDisplaySyncManager::IsSupportSkip() const
{
    return supportSkipEnabled_;
}

bool UIDisplaySyncManager::IsAutoRefreshRateMode() const
{
    return refreshRateMode_ == static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

bool UIDisplaySyncManager::IsNonAutoRefreshRateMode() const
{
    return refreshRateMode_ != static_cast<int32_t>(RefreshRateMode::REFRESHRATE_MODE_AUTO);
}

UIDisplaySyncManager::UIDisplaySyncManager() {}

UIDisplaySyncManager::~UIDisplaySyncManager() noexcept
{
    uiDisplaySyncMap_.clear();
}
} // namespace OHOS::Ace
