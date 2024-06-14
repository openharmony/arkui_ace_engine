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
#include "frame_rate_manager.h"

namespace OHOS::Ace::NG {
bool FrameRateManager::IsRateChanged()
{
    return isRateChanged_;
}

void FrameRateManager::SetIsRateChanged(bool isChanged)
{
    isRateChanged_ = isChanged;
}

void FrameRateManager::AddNodeRate(int32_t nodeId, int32_t rate)
{
    auto [iter, success] = nodeRateMap_.try_emplace(nodeId, rate);
    if (success) {
        isRateChanged_ = true;
    }
}

void FrameRateManager::RemoveNodeRate(int32_t nodeId)
{
    if (auto iter = nodeRateMap_.find(nodeId); iter != nodeRateMap_.end()) {
        nodeRateMap_.erase(iter);
        isRateChanged_ = true;
    }
}

void FrameRateManager::UpdateNodeRate(int32_t nodeId, int32_t rate)
{
    if (auto iter = nodeRateMap_.find(nodeId); iter != nodeRateMap_.end() && iter->second != rate) {
        iter->second = rate;
        isRateChanged_ = true;
    }
}

void FrameRateManager::SetAnimateRate(int32_t rate)
{
    if (animateRate_ != rate) {
        animateRate_ = rate;
        isRateChanged_ = true;
    }
}

void FrameRateManager::SetDisplaySyncRate(int32_t displaySyncRate)
{
    if (displaySyncRate_ != displaySyncRate) {
        displaySyncRate_ = displaySyncRate;
        isRateChanged_ = true;
    }
}

int32_t FrameRateManager::GetDisplaySyncRate() const
{
    return displaySyncRate_;
}

std::pair<int32_t, int32_t> FrameRateManager::GetExpectedRate()
{
    int32_t expectedRate = 0;
    int32_t rateType = 0;
    if (!nodeRateMap_.empty()) {
        auto maxIter = std::max_element(
            nodeRateMap_.begin(), nodeRateMap_.end(), [](auto a, auto b) { return a.second < b.second; });
        expectedRate = maxIter->second;
        rateType = ACE_COMPONENT_FRAME_RATE_TYPE;
    }
    if (displaySyncRate_ > expectedRate) {
        expectedRate = displaySyncRate_;
        rateType = DISPLAY_SYNC_FRAME_RATE_TYPE;
    }
    if (animateRate_ > expectedRate) {
        expectedRate = animateRate_;
        rateType = UI_ANIMATION_FRAME_RATE_TYPE;
    }
    return {expectedRate, rateType};
}
} // namespace OHOS::Ace::NG