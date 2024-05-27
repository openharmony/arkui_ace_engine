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
void WaterFlowLayoutInfoSW::Sync(int32_t itemCnt, float mainSize, float mainGap)
{
    if (sections_.empty()) {
        return;
    }
    startIndex_ = StartIndex();
    endIndex_ = EndIndex();
    if (startIndex_ > endIndex_) {
        return;
    }
    if (!idxToLane_.count(startIndex_) || sections_[GetSegment(startIndex_)].size() <= idxToLane_.at(startIndex_)) {
        return;
    }
    storedOffset_ = sections_[GetSegment(startIndex_)][idxToLane_.at(startIndex_)].startPos;

    delta_ = 0.0f;
    lastMainSize_ = mainSize;
    mainGap_ = mainGap;
    startPos_ = StartPos();
    endPos_ = EndPos();

    itemStart_ = startIndex_ == 0 && NonNegative(startPos_);
    itemEnd_ = endIndex_ == itemCnt - 1;
    if (footerIndex_ == 0) {
        itemEnd_ &= LessOrEqual(endPos_, mainSize);
    }
    offsetEnd_ = itemEnd_ && LessOrEqual(endPos_ + footerHeight_, mainSize);
    maxHeight_ = std::max(endPos_ - startPos_ + footerHeight_, maxHeight_);

    if (!itemEnd_) {
        footerHeight_ = 0.0f;
    }

    synced_ = true;
}

float WaterFlowLayoutInfoSW::DistanceToTop(int32_t itemIdx, float mainGap) const
{
    if (!ItemInView(itemIdx)) {
        return 0.0f;
    }
    const auto& lane = sections_[GetSegment(itemIdx)][idxToLane_.at(itemIdx)];
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
    if (!ItemInView(itemIdx)) {
        return 0.0f;
    }
    const auto& lane = sections_[GetSegment(itemIdx)][idxToLane_.at(itemIdx)];
    float dist = mainSize - lane.endPos;
    for (auto item = lane.items_.rbegin(); item != lane.items_.rend(); ++item) {
        if (item->idx == itemIdx) {
            break;
        }
        dist += item->mainSize + mainGap;
    }
    return dist;
}

bool WaterFlowLayoutInfoSW::OutOfBounds() const
{
    if (sections_.empty()) {
        return false;
    }
    // checking first lane is enough because re-align automatically happens when reaching start
    if (itemStart_ && Positive(sections_[0][0].startPos)) {
        return true;
    }
    if (offsetEnd_) {
        return std::all_of(sections_.back().begin(), sections_.back().end(),
            [this](const Lane& lane) { return LessNotEqual(lane.endPos + footerHeight_, lastMainSize_); });
    }
    return false;
}

OverScrollOffset WaterFlowLayoutInfoSW::GetOverScrolledDelta(float delta) const
{
    OverScrollOffset res {};
    if (sections_.empty()) {
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

    if (!itemEnd_) {
        return res;
    }
    float disToBot = EndPos() + footerHeight_ - lastMainSize_;
    if (!offsetEnd_) {
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
    if (sections_.empty()) {
        return 0.0f;
    }
    float res = 0.0f;
    if (itemStart_) {
        res = StartPos() + delta;
    }
    if (offsetEnd_) {
        res = mainSize - (EndPos() + footerHeight_ + delta);
    }
    return res;
}

float WaterFlowLayoutInfoSW::EndPos() const
{
    if (synced_) {
        return endPos_;
    }
    for (auto it = sections_.rbegin(); it != sections_.rend(); ++it) {
        if (std::all_of(it->begin(), it->end(), [](const auto& lane) { return lane.items_.empty(); })) {
            continue;
        }
        return std::max_element(it->begin(), it->end(), [](const Lane& left, const Lane& right) {
            return LessNotEqual(left.endPos, right.endPos);
        })->endPos;
    }
    return 0.0f;
}

float WaterFlowLayoutInfoSW::StartPos() const
{
    if (synced_) {
        return startPos_;
    }
    for (const auto& section : sections_) {
        if (std::all_of(section.begin(), section.end(), [](const auto& lane) { return lane.items_.empty(); })) {
            continue;
        }
        return std::min_element(section.begin(), section.end(), [](const Lane& left, const Lane& right) {
            return LessNotEqual(left.startPos, right.startPos);
        })->startPos;
    }
    return 0.0f;
}

bool WaterFlowLayoutInfoSW::ReachStart(float prevPos, bool firstLayout) const
{
    if (!itemStart_ || sections_.empty()) {
        return false;
    }
    return firstLayout || Negative(prevPos);
}

bool WaterFlowLayoutInfoSW::ReachEnd(float prevPos) const
{
    if (!offsetEnd_ || sections_.empty()) {
        return false;
    }
    float prevEndPos = EndPos() - (totalOffset_ - prevPos);
    return GreatNotEqual(prevEndPos + footerHeight_, lastMainSize_);
}

float WaterFlowLayoutInfoSW::GetContentHeight() const
{
    // only height in view are remembered
    return maxHeight_;
}

int32_t WaterFlowLayoutInfoSW::GetMainCount() const
{
    if (sections_.empty()) {
        return 0;
    }
    for (const auto& section : sections_) {
        if (std::all_of(section.begin(), section.end(), [](const auto& lane) { return lane.items_.empty(); })) {
            continue;
        }
        return static_cast<int32_t>(
            std::max_element(section.begin(), section.end(), [](const Lane& left, const Lane& right) {
                return left.items_.size() < right.items_.size();
            })->items_.size());
    }
    return 0;
}

float WaterFlowLayoutInfoSW::CalcTargetPosition(int32_t idx, int32_t /* crossIdx */) const
{
    if (!ItemInView(idx)) {
        return Infinity<float>();
    }
    const auto& lane = sections_[GetSegment(idx)][idxToLane_.at(idx)];
    float pos = 0.0f; // main-axis position of the item's top edge relative to viewport top. Positive if below viewport
    float itemSize = 0.0f;
    if (idx < endIndex_) {
        pos = DistanceToTop(idx, mainGap_);
        auto it = std::find_if(
            lane.items_.begin(), lane.items_.end(), [idx](const ItemInfo& item) { return item.idx == idx; });
        itemSize = it->mainSize;
    } else {
        itemSize = lane.items_.back().mainSize;
        pos = lane.endPos - itemSize;
    }
    switch (align_) {
        case ScrollAlign::START:
            break;
        case ScrollAlign::END:
            pos = pos - lastMainSize_ + itemSize;
            break;
        case ScrollAlign::AUTO:
            if (Negative(pos)) {
                /* */
            } else if (GreatNotEqual(pos + itemSize, lastMainSize_)) {
                pos = pos - lastMainSize_ + itemSize;
            } else {
                pos = 0.0f; // already in viewport, no movement needed
            }
            break;
        case ScrollAlign::CENTER:
            pos = pos - (lastMainSize_ - itemSize) / 2.0f;
            break;
        default:
            pos = 0.0f;
            break;
    }
    // convert to absolute position
    return pos - totalOffset_;
}

void WaterFlowLayoutInfoSW::Reset()
{
    jumpIndex_ = startIndex_;
    align_ = ScrollAlign::START;
    delta_ = DistanceToTop(startIndex_, mainGap_);
    for (auto& section : sections_) {
        section.clear();
    }
    idxToLane_.clear();
    maxHeight_ = 0.0f;
    synced_ = false;
}

int32_t WaterFlowLayoutInfoSW::EndIndex() const
{
    if (synced_) {
        return endIndex_;
    }
    int32_t maxIdx = -1;
    for (auto it = sections_.rbegin(); it != sections_.rend(); ++it) {
        if (std::all_of(it->begin(), it->end(), [](const auto& lane) { return lane.item_.empty(); })) {
            continue;
        }
        for (const auto& lane : *it) {
            if (lane.items_.empty()) {
                continue;
            }
            maxIdx = std::max(maxIdx, lane.items_.back().idx);
        }
        break;
    }
    return maxIdx;
}

int32_t WaterFlowLayoutInfoSW::StartIndex() const
{
    if (synced_) {
        return startIndex_;
    }
    auto minIdx = Infinity<int32_t>();
    for (const auto& section : sections_) {
        if (std::all_of(section.begin(), section.end(), [](const auto& lane) { return lane.item_.empty(); })) {
            continue;
        }

        for (const auto& lane : section) {
            if (lane.items_.empty()) {
                continue;
            }
            minIdx = std::min(minIdx, lane.items_.front().idx);
        }
        break;
    }
    return minIdx;
}

int32_t WaterFlowLayoutInfoSW::GetCrossIndex(int32_t itemIndex) const
{
    if (ItemInView(itemIndex)) {
        return static_cast<int32_t>(idxToLane_.at(itemIndex));
    }
    return -1;
}

void WaterFlowLayoutInfoSW::ResetBeforeJump(float laneBasePos)
{
    for (auto& section : sections_) {
        std::for_each(section.begin(), section.end(), [&laneBasePos](auto& lane) {
            lane.items_.clear();
            lane.startPos = laneBasePos;
            lane.endPos = laneBasePos;
        });
    }
    totalOffset_ = 0.0f;
    maxHeight_ = 0.0f;
    idxToLane_.clear();
    synced_ = false;
}

std::string WaterFlowLayoutInfoSW::Lane::ToString() const
{
    std::string res = "{StartPos: " + std::to_string(startPos) + " EndPos: " + std::to_string(endPos) + " ";
    if (items_.empty()) {
        res += "empty";
    } else {
        res += "Items [";
        for (const auto& item : items_) {
            res += std::to_string(item.idx) + " ";
        }
        res += "] ";
    }
    res += "}";
    return res;
}

bool WaterFlowLayoutInfoSW::ItemCloseToView(int32_t idx) const
{
    if (sections_.empty() ||
        std::all_of(sections_.begin(), sections_.end(), [](const auto& lanes) { return lanes.empty(); })) {
        return false;
    }
    int32_t startIdx = StartIndex();
    int32_t endIdx = EndIndex();
    if (endIdx > startIdx) {
        return false;
    }
    using std::abs, std::min;
    return min(abs(idx - endIdx), abs(idx - startIdx)) < endIdx - startIdx + 1;
}

void WaterFlowLayoutInfoSW::ClearDataFrom(int32_t idx, float mainGap)
{
    for (auto it = idxToLane_.begin(); it != idxToLane_.end();) {
        if (it->first >= idx) {
            it = idxToLane_.erase(it); // Erase and get the iterator to the next element
        } else {
            ++it; // Move to the next element
        }
    }
    for (int32_t i = GetSegment(idx); i < sections_.size(); ++i) {
        for (auto& lane : sections_[i]) {
            while (!lane.items_.empty()) {
                if (lane.items_.back().idx >= idx) {
                    lane.endPos -= lane.items_.back().mainSize + mainGap;
                    lane.items_.pop_back();
                } else {
                    lane.endPos = std::max(lane.endPos, lane.startPos);
                    break;
                }
            }
        }
    }
}

float WaterFlowLayoutInfoSW::TopFinalPos() const
{
    return -(StartPos() + delta_);
};

float WaterFlowLayoutInfoSW::BottomFinalPos(float viewHeight) const
{
    return -(EndPos() + delta_ + footerHeight_) + std::min(maxHeight_, viewHeight);
};

bool WaterFlowLayoutInfoSW::IsMisaligned() const
{
    if (sections_.empty()) {
        return false;
    }
    if (StartIndex() > 0) {
        return false;
    }
    bool laneNotAligned = std::any_of(sections_[0].begin(), sections_[0].end(),
        [this](const auto& lane) { return !NearEqual(lane.startPos, StartPos()); });
    return laneNotAligned || sections_[0][0].items_.front().idx != 0;
}

void WaterFlowLayoutInfoSW::InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t /* start */)
{
    size_t n = sections.size();
    if (n == 0) {
        return;
    }
    segmentCache_.clear();
    segmentTails_ = { sections[0].itemsCount - 1 };
    for (size_t i = 1; i < n; ++i) {
        segmentTails_.push_back(segmentTails_[i - 1] + sections[i].itemsCount);
    }
}

void WaterFlowLayoutInfoSW::PrepareSection(int32_t idx, bool forward)
{
    int32_t prevSeg = GetSegment(forward ? idx - 1 : idx + 1);
    int32_t curSeg = GetSegment(idx);
    if (prevSeg == curSeg) {
        return;
    }
    if (prevSeg < curSeg) {
        for (int32_t i = prevSeg + 1; i <= idx; ++i) {
            float pos = std::max_element(
                sections_[i - 1].begin(), sections_[i - 1].end(), [](const Lane& left, const Lane& right) {
                    return LessNotEqual(left.endPos, right.endPos);
                })->endPos;
            pos += axis_ == Axis::VERTICAL ? margins_[i - 1].bottom.value_or(0.0f) + margins_[i].top.value_or(0.0f)
                                           : margins_[i - 1].right.value_or(0.0f) + margins_[i].left.value_or(0.0f);
            std::for_each(sections_[i].begin(), sections_[i].end(),
                [pos](auto& section) { section.startPos = section.endPos = pos; });
        }
    } else {
        for (int32_t i = prevSeg - 1; i >= idx; --i) {
            float pos = std::min_element(
                sections_[i + 1].begin(), sections_[i + 1].end(), [](const Lane& left, const Lane& right) {
                    return LessNotEqual(left.startPos, right.startPos);
                })->startPos;
            pos -= axis_ == Axis::VERTICAL ? margins_[i + 1].top.value_or(0.0f) + margins_[i].bottom.value_or(0.0f)
                                           : margins_[i + 1].left.value_or(0.0f) + margins_[i].right.value_or(0.0f);
            std::for_each(sections_[i].begin(), sections_[i].end(),
                [pos](auto& section) { section.startPos = section.endPos = pos; });
        }
    }
}
} // namespace OHOS::Ace::NG
