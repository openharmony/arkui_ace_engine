/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/waterflow/sliding_window/water_flow_layout_info_sw.h"

#include <algorithm>
#include <cstdint>

namespace OHOS::Ace::NG {
void WaterFlowLayoutInfoSW::SyncRange()
{
    for (const auto& lane : lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        startIndex_ = std::min(startIndex_, lane.items_.front().idx);
        endIndex_ = std::max(endIndex_, lane.items_.back().idx);
    }
}

float WaterFlowLayoutInfoSW::DistanceToTop(int32_t itemIdx, float mainGap) const
{
    if (!idxToLane_.count(itemIdx)) {
        return 0.0f;
    }
    const auto& lane = lanes_[idxToLane_.at(itemIdx)];
    float dist = lane.startPos;
    for (const auto& item : lane.items_) {
        if (item.idx == itemIdx) {
            break;
        }
        dist += item.mainSize + mainGap;
    }
    return dist;
}

float WaterFlowLayoutInfoSW::DistanceToBottom(int32_t itemIdx, float mainSize, float mainGap) const
{
    if (!idxToLane_.count(itemIdx)) {
        return 0.0f;
    }
    const auto& lane = lanes_[idxToLane_.at(itemIdx)];
    float dist = mainSize - lane.endPos;
    for (const auto& item : lane.items_) {
        if (item.idx == itemIdx) {
            break;
        }
        dist += item.mainSize + mainGap;
    }
    return dist;
}
float WaterFlowLayoutInfoSW::offset() const
{
    return lanes_[0].startPos;
}
} // namespace OHOS::Ace::NG
