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
const std::vector<int32_t> UIDisplaySyncManager::REFRESH_RATE_LIST = { 90, 120, 144 };

void UIDisplaySyncManager::DispatchFunc(int64_t nanoTimestamp)
{
    CheckSkipEnableProperty();
    displaySyncRange_->Reset();

    if (uiDisplaySyncMap_.empty()) {
        if (sourceVsyncRate_ > 0) {
            monitorVsyncRate_ = sourceVsyncRate_;
        }
        return;
    }

    IdToDisplaySyncMap backupedMap(uiDisplaySyncMap_);

    int32_t VSyncPeriod = GetVsyncPeriod();
    for (const auto& [Id, weakDisplaySync] : backupedMap) {
        auto displaySync = weakDisplaySync.Upgrade();
        if (displaySync) {
            displaySync->CheckRate(sourceVsyncRate_, refreshRateMode_);
            displaySync->UpdateData(nanoTimestamp, VSyncPeriod);
            if (IsAutoRefreshRateMode() ||
                (IsNonAutoRefreshRateMode() && IsSupportSkip())) {
                displaySync->JudgeWhetherSkip();
            }
            displaySync->OnFrame();

            auto rateRange = displaySync->GetDisplaySyncData()->rateRange_;
            if (rateRange->IsValid()) {
                displaySyncRange_->Merge(*rateRange);
                monitorVsyncRate_ = rateRange->preferred_;
            } else if (sourceVsyncRate_ > 0) {
                monitorVsyncRate_ = sourceVsyncRate_;
            }
            TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "UIDisplaySyncMapSize:%{public}d Id:%{public}d"
                " FrameRateRange: {%{public}d, %{public}d, %{public}d}",
                static_cast<int32_t>(uiDisplaySyncMap_.size()), static_cast<int32_t>(displaySync->GetId()),
                rateRange->min_, rateRange->max_, rateRange->preferred_);
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
        TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "DisplaySyncId[%{public}d] is existed.",
            static_cast<int32_t>(displaySync->GetId()));
        return false;
    }
    ACE_SCOPED_TRACE("AddDisplaySync Id:%d", static_cast<int32_t>(displaySync->GetId()));
    uiDisplaySyncMap_[displaySync->GetId()] = displaySync;
    TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "AddDisplaySync MapSize: %{public}d expected: %{public}d.",
        static_cast<int32_t>(uiDisplaySyncMap_.size()), displaySync->GetDisplaySyncData()->rateRange_->preferred_);
    displaySync->JudgeWhetherRequestFrame();
    return true;
}

bool UIDisplaySyncManager::RemoveDisplaySync(const RefPtr<UIDisplaySync>& displaySync)
{
    if (HasDisplaySync(displaySync)) {
        ACE_SCOPED_TRACE("RemoveDisplaySync Id:%d", static_cast<int32_t>(displaySync->GetId()));
        uiDisplaySyncMap_.erase(displaySync->GetId());
        TAG_LOGD(AceLogTag::ACE_DISPLAY_SYNC, "RemoveDisplaySync MapSize: %{public}d expected: %{public}d.",
            static_cast<int32_t>(uiDisplaySyncMap_.size()),
            displaySync->GetDisplaySyncData()->rateRange_->preferred_);
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
    if (vsyncPeriod <= 0) {
        return false;
    }

    if (vsyncPeriod_ == vsyncPeriod) {
        return false;
    }
    vsyncPeriod_ = vsyncPeriod;

    int32_t rate = static_cast<int32_t>(std::ceil(SECOND_IN_NANO / vsyncPeriod_));
    std::call_once(computeFactorsFlag_, [this]() { FindAllRefreshRateFactors(); });
    int32_t refreshRate = FindMatchedRefreshRate(rate);
    SetVsyncRate(refreshRate);

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

std::set<int32_t> UIDisplaySyncManager::FindRefreshRateFactors(int32_t refreshRate)
{
    std::set<int32_t> refreshRateFactors;
    for (int32_t i = 1; i * i <= refreshRate; ++i) {
        if (refreshRate % i == 0) {
            refreshRateFactors.insert(i);
            if (i != refreshRate / i) {
                refreshRateFactors.insert(refreshRate / i);
            }
        }
    }
    return refreshRateFactors;
}

int32_t UIDisplaySyncManager::FindMatchedRefreshRate(int32_t target)
{
    auto it = std::lower_bound(refreshRateFactors_.begin(), refreshRateFactors_.end(), target);
    if (it == refreshRateFactors_.begin()) {
        return *it;
    } else if (it == refreshRateFactors_.end()) {
        return *(it - 1);
    }
    return std::abs(*it - target) < std::abs(*(it - 1) - target) ? *it : *(it - 1);
}

void UIDisplaySyncManager::FindAllRefreshRateFactors()
{
    std::set<int32_t> allFactors;
    for (const auto& refreshRate : REFRESH_RATE_LIST) {
        std::set<int32_t> factors = FindRefreshRateFactors(refreshRate);
        allFactors.insert(factors.begin(), factors.end());
    }
    refreshRateFactors_.clear();
    std::copy(allFactors.begin(), allFactors.end(), std::back_inserter(refreshRateFactors_));
    return;
}

int32_t UIDisplaySyncManager::GetAnimatorRate()
{
    std::priority_queue<int32_t> emptyQue;
    std::swap(maxAnimatorRateHap_, emptyQue);

    if (uiDisplaySyncMap_.empty()) {
        return INVALID_ANIMATOR_EXPECTED_RATE;
    }

    bool existAnimatorNoExpectdRate = false;
    IdToDisplaySyncMap backupedMap(uiDisplaySyncMap_);
    for (const auto& [Id, weakDisplaySync] : backupedMap) {
        auto displaySync = weakDisplaySync.Upgrade();
        if (displaySync) {
            if (displaySync->GetAnimatorExpectedRate() == 0) {
                existAnimatorNoExpectdRate = true;
            }
            maxAnimatorRateHap_.push(displaySync->GetAnimatorExpectedRate());
        } else {
            uiDisplaySyncMap_.erase(Id);
        }
    }

    if (maxAnimatorRateHap_.empty()) {
        return INVALID_ANIMATOR_EXPECTED_RATE;
    }
    int32_t currMaxAnimatorExpectedRate = maxAnimatorRateHap_.top();
    if (currMaxAnimatorExpectedRate < 0) {
        return currMaxAnimatorExpectedRate;
    }
    // currMaxAnimatorExpectedRate int32_t  example: 0x003c0001
    // [0, 16) is existAnimatorNoExpectdRate = 1
    // [16, 32) is aceAnimatorExpectedFrameRate = 60
    currMaxAnimatorExpectedRate = (currMaxAnimatorExpectedRate << ACE_ANIMATOR_OFFSET) + existAnimatorNoExpectdRate;
    return currMaxAnimatorExpectedRate;
}

bool UIDisplaySyncManager::IsAnimatorStopped()
{
    if (GetAnimatorRate() == INVALID_ANIMATOR_EXPECTED_RATE) {
        return true;
    }
    return false;
}

int32_t UIDisplaySyncManager::GetMonitorVsyncRate() const
{
    return monitorVsyncRate_;
}

UIDisplaySyncManager::UIDisplaySyncManager() {}

UIDisplaySyncManager::~UIDisplaySyncManager() noexcept
{
    uiDisplaySyncMap_.clear();
}
} // namespace OHOS::Ace
