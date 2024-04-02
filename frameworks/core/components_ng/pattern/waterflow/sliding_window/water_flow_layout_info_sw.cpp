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

float WaterFlowLayoutInfoSW::DistanceToTop(size_t item, float mainGap) const
{
    if (!idxToLane_.count(item)) {
        return 0.0f;
    }
    const auto& lane = lanes_[idxToLane_[item]];
    float dist = lane.startPos;
    for (const auto& item : lane.items_) {
        if (item.idx == item) {
            break;
        }
        dist += item.mainSize + mainGap;
    }
    return dist;
}

float WaterFlowLayoutInfoSW::DistanceToBottom(size_t item, float mainSize, float mainGap) const
{
    if (!idxToLane_.count(item)) {
        return 0.0f;
    }
    const auto& lane = lanes_[idxToLane_[item]];
    float dist = mainSize - lane.endPos;
    for (const auto& item : lane.items_) {
        if (item.idx == item) {
            break;
        }
        dist += item.mainSize + mainGap;
    }
    return dist;
}
} // namespace OHOS::Ace::NG
