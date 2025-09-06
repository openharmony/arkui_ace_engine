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
uint32_t GetRateTypeOfScene(const std::string& scene)
{
    static const std::unordered_map<std::string, uint32_t> sceneRateTypeMap = {
        { "refresh_drag_scene", REFRESH_DRAG_FRAME_RATE_TYPE },
        { "swiper_drag_scene", SWIPER_DRAG_FRAME_RATE_TYPE },
        { "scrollable_drag_scene", SCROLLABLE_DRAG_FRAME_RATE_TYPE },
        { "scrollBar_drag_scene", SCROLLBAR_DRAG_FRAME_RATE_TYPE },
        { "split_drag_scene", SPLIT_DRAG_FRAME_RATE_TYPE },
        { "picker_drag_scene", PICKER_DRAG_FRAME_RATE_TYPE },
        { "scrollable_multi_task_scene", SCROLLABLE_MULTI_TASK_FRAME_RATE_TYPE },
    };
    auto iter = sceneRateTypeMap.find(scene);
    if (iter != sceneRateTypeMap.end()) {
        return iter->second;
    }
    return UNKNOWN_FRAME_RATE_TYPE;
}

bool FrameRateManager::IsRateChanged()
{
    return isRateChanged_;
}

void FrameRateManager::SetIsRateChanged(bool isChanged)
{
    isRateChanged_ = isChanged;
}

void FrameRateManager::AddNodeRate(int32_t nodeId, const std::string& scene, int32_t rate)
{
    auto [iter, success] = nodeRateMap_.try_emplace(nodeId, std::pair<std::string, int32_t>(scene, rate));
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
    if (auto iter = nodeRateMap_.find(nodeId); iter != nodeRateMap_.end() && iter->second.second != rate) {
        iter->second.second = rate;
        isRateChanged_ = true;
    }
}

void FrameRateManager::SetAnimateRate(int32_t rate, bool hasFirstFrameAnimation)
{
    if (animateRate_ != rate || hasFirstFrameAnimation_ != hasFirstFrameAnimation) {
        hasFirstFrameAnimation_ = hasFirstFrameAnimation;
        animateRate_ = rate;
        isRateChanged_ = true;
    }
}

void FrameRateManager::SetDisplaySyncRate(int32_t displaySyncRate, uint32_t displaySyncType)
{
    if (displaySyncRate_ != displaySyncRate || displaySyncType_ != displaySyncType) {
        displaySyncRate_ = displaySyncRate;
        displaySyncType_ = displaySyncType;
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
    int32_t rateType = UNKNOWN_FRAME_RATE_TYPE;
    for (const auto& [_, sceneRate] : nodeRateMap_) {
        const auto& [scene, rate] = sceneRate;
        if (rate <= 0) {
            continue;
        }
        expectedRate = std::max(expectedRate, rate);
        rateType |= GetRateTypeOfScene(scene);
    }

    expectedRate = std::max(expectedRate, displaySyncRate_);
    if (displaySyncRate_ > 0) {
        rateType |= displaySyncType_;
    }

    expectedRate = std::max(expectedRate, animateRate_);
    if (animateRate_ > 0) {
        rateType |= UI_ANIMATION_FRAME_RATE_TYPE;
    }
    if (hasFirstFrameAnimation_) {
        if (expectedRate == 0) {
            rateType |= UI_ANIMATION_FRAME_RATE_TYPE;
        }
        rateType |= ANIMATION_STATE_FIRST_FRAME;
    }
    return {expectedRate, rateType};
}
} // namespace OHOS::Ace::NG