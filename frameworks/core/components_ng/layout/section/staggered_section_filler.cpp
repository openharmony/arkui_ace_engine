/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "staggered_section_filler.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void SectionEndFiller::PrepareEndPosQueue(const std::vector<Lane>& lanes, float mainGap, float viewportBound)
{
    for (size_t i = 0; i < lanes.size(); ++i) {
        const float nextPos = lanes[i].endPos + (lanes[i].items_.empty() ? 0.0f : mainGap);
        if (LessNotEqual(nextPos, viewportBound)) {
            q_.push({ nextPos, i });
        }
    }
}
void SectionStartFiller::PrepareStartPosQueue(const std::vector<Lane>& lanes, float mainGap, float viewportBound)
{
    for (size_t i = 0; i < lanes.size(); ++i) {
        const float nextPos = lanes[i].startPos - (lanes[i].items_.empty() ? 0.0f : mainGap);
        if (GreatNotEqual(nextPos, viewportBound)) {
            q_.push({ nextPos, i });
        }
    }
}

bool SectionEndFiller::Fill(const RefPtr<Measurer>& measurer, FrameNode* node, int32_t index, float viewportBound)
{
    if (q_.empty()) {
        return false;
    }
    auto [_, laneIdx] = q_.top();
    q_.pop();
    const float itemLen = measurer->Measure(node, index, section_.lanes[laneIdx].crossLen);
    auto& lane = section_.lanes[laneIdx];
    lane.endPos += section_.mainGap + itemLen;
    if (lane.items_.empty()) {
        lane.endPos -= section_.mainGap;
    }
    lane.items_.push_back({ index, itemLen });
    section_.idxToLane[index] = laneIdx;
    float nextPos = lane.endPos + section_.mainGap;
    if (LessNotEqual(nextPos, viewportBound)) {
        q_.push({ nextPos, laneIdx });
    }
    return true;
}

bool SectionStartFiller::Fill(const RefPtr<Measurer>& measurer, FrameNode* node, int32_t index, float viewportBound)
{
    if (q_.empty()) {
        return false;
    }
    auto [_, laneIdx] = q_.top();
    q_.pop();
    const float itemLen = measurer->Measure(node, index, section_.lanes[laneIdx].crossLen);

    auto& lane = section_.lanes[laneIdx];
    lane.startPos -= section_.mainGap + itemLen;
    if (lane.items_.empty()) {
        lane.startPos += section_.mainGap;
    }
    lane.items_.push_front({ index, itemLen });
    section_.idxToLane[index] = laneIdx;
    float nextPos = lane.startPos - section_.mainGap;
    if (Positive(nextPos)) {
        q_.push({ nextPos, laneIdx });
    }

    return true;
}
} // namespace OHOS::Ace::NG
