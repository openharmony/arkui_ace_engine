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
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_info_sw.h"

#include <algorithm>
#include <cstdint>

#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
void WaterFlowLayoutInfoSW::Sync(float mainSize, float mainGap)
{
    for (const auto& lane : lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        startIndex_ = std::min(startIndex_, lane.items_.front().idx);
        endIndex_ = std::max(endIndex_, lane.items_.back().idx);
    }
    delta_ = 0.0f;
    lastMainSize_ = mainSize;
    mainGap_ = mainGap;

    itemStart_ = startIndex_ == 0 && NonNegative(DistanceToTop(0, mainGap_));
    itemEnd_ = endIndex_ == childrenCount_ - 1;
    offsetEnd_ = itemEnd_ && NonNegative(DistanceToBottom(endIndex_, mainSize, mainGap));
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
    if (lanes_.empty()) {
        return 0.0f;
    }
    return lanes_[0].startPos;
}

bool WaterFlowLayoutInfoSW::OutOfBounds() const
{
    if (lanes_.empty()) {
        return false;
    }
    // checking first lane is enough because re-align automatically happens when reaching start
    if (itemStart_ && Positive(lanes_[0].startPos)) {
        return true;
    }
    if (itemEnd_) {
        return std::all_of(lanes_.begin(), lanes_.end(),
            [mainSize = lastMainSize_](const Lane& lane) { return LessNotEqual(lane.endPos, mainSize); });
    }
    return false;
}

OverScrollOffset WaterFlowLayoutInfoSW::GetOverScrolledDelta(float delta) const
{
    OverScrollOffset res {};
    if (lanes_.empty()) {
        return res;
    }

    if (startIndex_ == 0) {
        float disToTop = -StartPos();
        if (!itemStart_) {
            res.start = std::max(0.0f, delta - disToTop);
        } else if (Positive(delta)) {
            res.start = delta;
        } else {
            res.start = std::max(delta, disToTop);
        }
    }

    if (endIndex_ < childrenCount_ - 1) {
        return res;
    }
    float disToBot = EndPos() - lastMainSize_;
    if (!itemEnd_) {
        res.end = std::min(0.0f, disToBot + delta);
    } else if (Negative(delta)) {
        res.end = delta;
    } else {
        res.end = std::min(delta, -disToBot);
    }
    return res;
}

float WaterFlowLayoutInfoSW::CalcOverScroll(float mainSize, float delta) const
{
    if (lanes_.empty()) {
        return 0.0f;
    }
    float res = 0.0f;
    if (itemStart_) {
        res = lanes_[0].startPos + delta;
    }
    if (itemEnd_) {
        res = mainSize - (EndPos() + delta);
    }
    return res;
}

inline float WaterFlowLayoutInfoSW::EndPos() const
{
    return std::max_element(lanes_.begin(), lanes_.end(), [](const Lane& left, const Lane& right) {
        return LessNotEqual(left.endPos, right.endPos);
    })->endPos;
}
inline float WaterFlowLayoutInfoSW::StartPos() const
{
    return std::min_element(lanes_.begin(), lanes_.end(), [](const Lane& left, const Lane& right) {
        return LessNotEqual(left.startPos, right.startPos);
    })->startPos;
}

bool WaterFlowLayoutInfoSW::ReachStart(float prevPos, bool firstLayout) const
{
    if (firstLayout || !itemStart_ || lanes_.empty()) {
        return false;
    }
    return Negative(prevPos);
}

bool WaterFlowLayoutInfoSW::ReachEnd(float prevPos) const
{
    if (!itemEnd_ || lanes_.empty()) {
        return false;
    }
    float prevEndPos = EndPos() - offset() + prevPos;
    return GreatNotEqual(prevEndPos, lastMainSize_);
}

float WaterFlowLayoutInfoSW::GetContentHeight() const
{
    if (lanes_.empty()) {
        return 0.0f;
    }
    return EndPos() - StartPos();
}

int32_t WaterFlowLayoutInfoSW::GetMainCount() const
{
    if (lanes_.empty()) {
        return 0;
    }
    return static_cast<int32_t>(std::max_element(lanes_.begin(), lanes_.end(), [](const Lane& left, const Lane& right) {
        return left.items_.size() < right.items_.size();
    })->items_.size());
}

float WaterFlowLayoutInfoSW::CalcTargetPosition(int32_t idx, int32_t /* crossIdx */) const
{
    if (!idxToLane_.count(idx)) {
        return Infinity<float>();
    }
    const auto& lane = lanes_[idxToLane_.at(idx)];
    float pos = 0.0f; // main-axis position of the item's top edge relative to viewport top. Positive if below viewport
    float itemSize = 0.0f;
    if (idx <= endIndex_) {
        pos = DistanceToTop(idx, mainGap_);
        auto it = std::find_if(
            lane.items_.begin(), lane.items_.end(), [idx](const ItemInfo& item) { return item.idx == idx; });
        if (it == lane.items_.end()) {
            std::abort();
        }
        itemSize = it->mainSize;
    } else {
        pos = -DistanceToBottom(idx, lastMainSize_, mainGap_) - lastMainSize_;
        if (lane.items_.back().idx != idx) {
            std::abort();
        }
        itemSize = lane.items_.back().mainSize;
    }
    switch (align_) {
        case ScrollAlign::START:
            return pos;
        case ScrollAlign::END:
            return pos - lastMainSize_ + itemSize;
        case ScrollAlign::AUTO:
            if (Negative(pos)) {
                return pos;
            } else if (GreatNotEqual(pos + itemSize, lastMainSize_)) {
                return pos - lastMainSize_ + itemSize;
            }
            return 0.0f; // already in viewport, no movement needed
        case ScrollAlign::CENTER:
            return pos - (lastMainSize_ - itemSize) / 2;
        default:
            return 0.0f;
    }
}

void WaterFlowLayoutInfoSW::Reset()
{
    jumpIndex_ = startIndex_;
    delta_ = DistanceToTop(startIndex_, mainGap_);
    lanes_.clear();
    idxToLane_.clear();
}
} // namespace OHOS::Ace::NG
