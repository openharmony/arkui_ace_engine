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

namespace OHOS::Ace::NG {
void WaterFlowLayoutInfoSW::Sync(int32_t itemCnt, float mainSize, const std::vector<float>& mainGap)
{
    if (lanes_.empty()) {
        return;
    }
    startIndex_ = StartIndex();
    endIndex_ = EndIndex();
    if (startIndex_ > endIndex_) {
        return;
    }
    if (!idxToLane_.count(startIndex_) || lanes_[GetSegment(startIndex_)].size() <= idxToLane_.at(startIndex_)) {
        return;
    }
    storedOffset_ = lanes_[GetSegment(startIndex_)][idxToLane_.at(startIndex_)].startPos;

    delta_ = 0.0f;
    lastMainSize_ = mainSize;
    mainGap_ = mainGap;
    startPos_ = StartPos();
    endPos_ = EndPos();

    itemStart_ = startIndex_ == 0 && NonNegative(startPos_ - TopMargin());
    itemEnd_ = endIndex_ == itemCnt - 1;
    if (footerIndex_ == 0) {
        itemEnd_ &= LessOrEqual(endPos_, mainSize);
    }
    offsetEnd_ = itemEnd_ && LessOrEqual(endPos_ + footerHeight_ + BotMargin(), mainSize);
    maxHeight_ = std::max(endPos_ - startPos_ + footerHeight_, maxHeight_);

    if (!itemEnd_) {
        footerHeight_ = 0.0f;
    }

    newStartIndex_ = EMPTY_NEW_START_INDEX;

    synced_ = true;
}

float WaterFlowLayoutInfoSW::CalibrateOffset()
{
    if (startIndex_ == 0) {
        // can calibrate totalOffset when at top
        const float prev = totalOffset_;
        totalOffset_ = startPos_ - TopMargin();
        return totalOffset_ - prev;
    }
    return 0.0f;
}

float WaterFlowLayoutInfoSW::DistanceToTop(int32_t itemIdx, float mainGap) const
{
    if (!ItemInView(itemIdx)) {
        return 0.0f;
    }
    const auto& lane = lanes_[GetSegment(itemIdx)][idxToLane_.at(itemIdx)];
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
    const auto& lane = lanes_[GetSegment(itemIdx)][idxToLane_.at(itemIdx)];
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
    if (lanes_.empty()) {
        return false;
    }
    // checking first lane is enough because re-align automatically happens when reaching start
    if (itemStart_ && Positive(lanes_[0][0].startPos - TopMargin())) {
        return true;
    }
    if (!itemStart_ && offsetEnd_) {
        return std::all_of(lanes_.back().begin(), lanes_.back().end(), [this](const Lane& lane) {
            return LessNotEqual(lane.endPos + footerHeight_ + BotMargin(), lastMainSize_);
        });
    }
    return false;
}

OverScrollOffset WaterFlowLayoutInfoSW::GetOverScrolledDelta(float delta) const
{
    OverScrollOffset res {};
    if (lanes_.empty()) {
        return res;
    }
    delta += delta_;
    if (startIndex_ == 0) {
        float disToTop = -StartPosWithMargin();
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
    float disToBot = EndPosWithMargin() + footerHeight_ - std::min(lastMainSize_, maxHeight_);
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
    if (lanes_.empty()) {
        return 0.0f;
    }
    float res = 0.0f;
    if (itemStart_) {
        res = StartPosWithMargin() + delta;
    }
    if (offsetEnd_) {
        res = mainSize - (EndPosWithMargin() + footerHeight_ + delta);
    }
    return res;
}

namespace {
using Lane = WaterFlowLayoutInfoSW::Lane;
inline bool SectionEmpty(const std::vector<WaterFlowLayoutInfoSW::Lane>& section)
{
    return section.empty() ||
           std::all_of(section.begin(), section.end(), [](const auto& lane) { return lane.items_.empty(); });
}
inline float SectionEndPos(const std::vector<WaterFlowLayoutInfoSW::Lane>& section)
{
    return std::max_element(section.begin(), section.end(), [](const Lane& left, const Lane& right) {
        return LessNotEqual(left.endPos, right.endPos);
    })->endPos;
}

inline float SectionStartPos(const std::vector<WaterFlowLayoutInfoSW::Lane>& section)
{
    return std::min_element(section.begin(), section.end(), [](const Lane& left, const Lane& right) {
        return LessNotEqual(left.startPos, right.startPos);
    })->startPos;
}
} // namespace

float WaterFlowLayoutInfoSW::EndPos() const
{
    if (synced_) {
        return endPos_;
    }
    for (auto it = lanes_.rbegin(); it != lanes_.rend(); ++it) {
        if (SectionEmpty(*it)) {
            continue;
        }
        return SectionEndPos(*it);
    }
    return 0.0f;
}

float WaterFlowLayoutInfoSW::StartPos() const
{
    if (synced_) {
        return startPos_;
    }
    for (const auto& section : lanes_) {
        if (SectionEmpty(section)) {
            continue;
        }
        return SectionStartPos(section);
    }
    return 0.0f;
}

bool WaterFlowLayoutInfoSW::ReachStart(float prevPos, bool firstLayout) const
{
    if (!itemStart_ || lanes_.empty()) {
        return false;
    }
    const bool backFromOverScroll = Positive(prevPos) && NonPositive(totalOffset_);
    return firstLayout || Negative(prevPos) || backFromOverScroll;
}

bool WaterFlowLayoutInfoSW::ReachEnd(float prevPos, bool firstLayout) const
{
    if (!offsetEnd_ || lanes_.empty()) {
        return false;
    }
    const float prevEndPos = EndPos() - (totalOffset_ - prevPos) + footerHeight_;
    const bool backFromOverScroll =
        LessNotEqual(prevEndPos, lastMainSize_) && GreatOrEqual(EndPos() + footerHeight_, lastMainSize_);
    return firstLayout || GreatNotEqual(prevEndPos, lastMainSize_) || backFromOverScroll;
}

float WaterFlowLayoutInfoSW::GetContentHeight() const
{
    // only height in view are remembered
    return maxHeight_;
}

int32_t WaterFlowLayoutInfoSW::GetMainCount() const
{
    if (lanes_.empty()) {
        return 0;
    }
    for (const auto& section : lanes_) {
        if (SectionEmpty(section)) {
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
    const auto& lane = lanes_[GetSegment(idx)][idxToLane_.at(idx)];
    float pos = 0.0f; // main-axis position of the item's top edge relative to viewport top. Positive if below viewport
    float itemSize = 0.0f;
    if (idx < endIndex_) {
        pos = DistanceToTop(idx, mainGap_[GetSegment(idx)]);
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

void WaterFlowLayoutInfoSW::PrepareJump()
{
    if (startIndex_ > endIndex_) {
        return;
    }
    align_ = ScrollAlign::START;
    jumpIndex_ = startIndex_;
    delta_ = storedOffset_;
}

void WaterFlowLayoutInfoSW::Reset()
{
    PrepareJump();
    for (auto& section : lanes_) {
        for (auto& lane : section) {
            lane.items_.clear();
        }
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
    for (auto it = lanes_.rbegin(); it != lanes_.rend(); ++it) {
        bool flag = false;
        for (const auto& lane : *it) {
            if (lane.items_.empty()) {
                continue;
            }
            flag = true;
            maxIdx = std::max(maxIdx, lane.items_.back().idx);
        }
        if (flag) {
            break;
        }
    }
    return maxIdx;
}

int32_t WaterFlowLayoutInfoSW::StartIndex() const
{
    if (synced_) {
        return startIndex_;
    }
    auto minIdx = Infinity<int32_t>();
    for (const auto& section : lanes_) {
        bool flag = false;
        for (const auto& lane : section) {
            if (lane.items_.empty()) {
                continue;
            }
            flag = true;
            minIdx = std::min(minIdx, lane.items_.front().idx);
        }
        if (flag) {
            break;
        }
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

void WaterFlowLayoutInfoSW::ResetWithLaneOffset(std::optional<float> laneBasePos)
{
    for (auto& section : lanes_) {
        std::for_each(section.begin(), section.end(), [&laneBasePos](auto& lane) {
            lane.items_.clear();
            if (laneBasePos) {
                lane.startPos = *laneBasePos;
                lane.endPos = *laneBasePos;
            } else {
                lane.endPos = lane.startPos;
            }
        });
    }
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
    if (lanes_.empty() || std::all_of(lanes_.begin(), lanes_.end(), [](const auto& lanes) { return lanes.empty(); })) {
        return false;
    }
    int32_t startIdx = StartIndex();
    int32_t endIdx = EndIndex();
    using std::abs, std::min;
    return min(abs(idx - endIdx), abs(idx - startIdx)) < endIdx - startIdx + 1;
}

void WaterFlowLayoutInfoSW::ClearDataFrom(int32_t idx, const std::vector<float>& mainGap)
{
    for (auto it = idxToLane_.begin(); it != idxToLane_.end();) {
        if (it->first >= idx) {
            it = idxToLane_.erase(it); // Erase and get the iterator to the next element
        } else {
            ++it;
        }
    }
    for (int32_t i = GetSegment(idx); i < static_cast<int32_t>(lanes_.size()); ++i) {
        for (auto& lane : lanes_[i]) {
            while (!lane.items_.empty() && lane.items_.back().idx >= idx) {
                lane.endPos -= lane.items_.back().mainSize + mainGap[i];
                lane.items_.pop_back();
            }
            lane.endPos = std::max(lane.endPos, lane.startPos);
        }
    }
}

float WaterFlowLayoutInfoSW::TopFinalPos() const
{
    return -(StartPosWithMargin() + delta_);
};

float WaterFlowLayoutInfoSW::BottomFinalPos(float viewHeight) const
{
    return -(EndPosWithMargin() + delta_ + footerHeight_) + std::min(maxHeight_, viewHeight);
};

bool WaterFlowLayoutInfoSW::IsMisaligned() const
{
    if (lanes_.empty()) {
        return false;
    }

    const int32_t startIdx = StartIndex();
    int32_t startSeg = GetSegment(startIdx);
    if (startSeg < 0) {
        return false;
    }
    if (startSeg == 0) {
        if (startIdx > 0) {
            ++startSeg;
        }
    } else if (startIdx != segmentTails_[startSeg - 1] + 1) {
        ++startSeg;
    }

    const int32_t endSeg = GetSegment(EndIndex());
    for (int32_t i = startSeg; i <= endSeg; ++i) {
        if (SectionEmpty(lanes_[i])) {
            continue;
        }
        const float startPos = SectionStartPos(lanes_[i]);
        if (std::any_of(lanes_[i].begin(), lanes_[i].end(),
                [&startPos](const auto& lane) { return !NearEqual(lane.startPos, startPos); })) {
            return true;
        }
        const int32_t sectionStart = (i == 0) ? 0 : segmentTails_[i - 1] + 1;
        if (sectionStart != lanes_[i][0].items_.front().idx) {
            return true;
        }
    }
    return false;
}

void WaterFlowLayoutInfoSW::InitSegments(const std::vector<WaterFlowSections::Section>& sections, int32_t start)
{
    synced_ = false;
    const size_t n = sections.size();
    if (n == 0) {
        return;
    }

    InitSegmentTails(sections);

    InitLanes(sections, start);

    margins_.clear(); // to be initialized during layout
}

void WaterFlowLayoutInfoSW::PrepareSectionPos(int32_t idx, bool fillBack)
{
    int32_t prevSeg = GetSegment(fillBack ? idx - 1 : idx + 1);
    int32_t curSeg = GetSegment(idx);
    if (prevSeg == curSeg) {
        return;
    }
    if (SectionEmpty(lanes_[prevSeg])) {
        // previous section is invalid
        return;
    }
    // prepare sections below
    if (prevSeg < curSeg) {
        for (int32_t i = prevSeg + 1; i <= curSeg; ++i) {
            float pos = SectionEndPos(lanes_[i - 1]);
            pos += axis_ == Axis::VERTICAL ? margins_[i - 1].bottom.value_or(0.0f) + margins_[i].top.value_or(0.0f)
                                           : margins_[i - 1].right.value_or(0.0f) + margins_[i].left.value_or(0.0f);
            std::for_each(lanes_[i].begin(), lanes_[i].end(), [pos](Lane& lane) {
                lane.startPos = lane.endPos = pos;
                lane.items_.clear();
            });
        }
        return;
    }
    // prepare sections above
    for (int32_t i = prevSeg - 1; i >= curSeg; --i) {
        float pos = SectionStartPos(lanes_[i + 1]);
        pos -= axis_ == Axis::VERTICAL ? margins_[i + 1].top.value_or(0.0f) + margins_[i].bottom.value_or(0.0f)
                                       : margins_[i + 1].left.value_or(0.0f) + margins_[i].right.value_or(0.0f);
        float diff = SectionEndPos(lanes_[i]) - pos;
        if (NearZero(diff)) {
            continue;
        }
        // use subtraction to keep the end positions staggered
        std::for_each(lanes_[i].begin(), lanes_[i].end(), [diff](Lane& lane) {
            lane.endPos -= diff;
            lane.startPos = lane.endPos;
            lane.items_.clear();
        });
    }
}

void WaterFlowLayoutInfoSW::InitSegmentTails(const std::vector<WaterFlowSections::Section>& sections)
{
    const size_t n = sections.size();
    segmentCache_.clear();
    segmentTails_ = { sections[0].itemsCount - 1 };
    for (size_t i = 1; i < n; ++i) {
        segmentTails_.push_back(segmentTails_[i - 1] + sections[i].itemsCount);
    }
}

void WaterFlowLayoutInfoSW::InitLanes(const std::vector<WaterFlowSections::Section>& sections, const int32_t start)
{
    const size_t n = sections.size();

    const int32_t lastValidIdx = start > 0 ? segmentTails_[start - 1] : -1;
    if (lastValidIdx < endIndex_) {
        PrepareJump();
    }

    lanes_.resize(n);
    for (size_t i = static_cast<size_t>(start); i < n; ++i) {
        lanes_[i] = std::vector<Lane>(sections[i].crossCount.value_or(1));
    }

    for (auto it = idxToLane_.begin(); it != idxToLane_.end();) {
        if (it->first > lastValidIdx) {
            it = idxToLane_.erase(it);
        } else {
            ++it;
        }
    }
}

void WaterFlowLayoutInfoSW::InitSegmentsForKeepPositionMode(const std::vector<WaterFlowSections::Section>& sections,
    const std::vector<WaterFlowSections::Section>& prevSections, int32_t start)
{
    synced_ = false;
    const size_t n = sections.size();
    if (n == 0) {
        ClearData();
        return;
    }

    WaterFlowSections::Section prevSection;
    auto prevSegIdx = GetSegment(startIndex_);
    if (prevSections.size() > static_cast<size_t>(prevSegIdx)) {
        prevSection = prevSections[prevSegIdx];
    }

    InitSegmentTails(sections);

    if (AdjustLanes(sections, prevSection, start, prevSegIdx)) {
        margins_.clear();
        return;
    }

    InitLanes(sections, start);

    margins_.clear(); // to be initialized during layout
}

bool WaterFlowLayoutInfoSW::AdjustLanes(const std::vector<WaterFlowSections::Section>& sections,
    const WaterFlowSections::Section& prevSection, int32_t start, int32_t prevSegIdx)
{
    if (newStartIndex_ < 0) {
        return false;
    }
    const size_t n = sections.size();
    const size_t curSegIdx = static_cast<size_t>(GetSegment(newStartIndex_));
    const auto& curSection = sections[curSegIdx];
    if (curSection.OnlyCountDiff(prevSection)) {
        // move old lanes_[prevSegIdx,...] to Lanes_[curSegIdx,...]
        if (n <= lanes_.size()) {
            // means curSegIdx <= prevSegIdx
            for (size_t i = 0; i < curSegIdx; ++i) {
                lanes_[i] = std::vector<Lane>(sections[i].crossCount.value_or(1));
            }
            for (size_t i = curSegIdx; i < n; ++i) {
                lanes_[i] = lanes_[prevSegIdx++];
            }
            lanes_.resize(n);
        } else {
            // 分组增加了，means curSegIdx > prevSegIdx
            size_t oriSize = lanes_.size() - 1;
            lanes_.resize(n);
            for (size_t i = n - 1; i >= curSegIdx; i--) {
                lanes_[i] = lanes_[oriSize--];
            }
            for (size_t i = 0; i < curSegIdx; ++i) {
                lanes_[i] = std::vector<Lane>(sections[i].crossCount.value_or(1));
            }
        }
        margins_.clear();
        return true;
    } else {
        newStartIndex_ = INVALID_NEW_START_INDEX;
    }
    return false;
}

bool WaterFlowLayoutInfoSW::PrepareNewStartIndex()
{
    if (newStartIndex_ == EMPTY_NEW_START_INDEX) {
        newStartIndex_ = StartIndex();
    }
    if (newStartIndex_ == Infinity<int32_t>()) {
        newStartIndex_ = INVALID_NEW_START_INDEX;
    }
    if (newStartIndex_ == INVALID_NEW_START_INDEX) {
        return false;
    }
    return true;
}

void WaterFlowLayoutInfoSW::NotifyDataChange(int32_t index, int32_t count)
{
    if (!PrepareNewStartIndex()) {
        return;
    }
    // 更新的index是否在newStartIndex_上方、是否会影响newStartIndex_
    if ((count == 0 && newStartIndex_ <= index) || (count > 0 && newStartIndex_ < index) ||
        (count < 0 && newStartIndex_ <= index - count - 1)) {
        newStartIndex_ = INVALID_NEW_START_INDEX;
        return;
    }
    newStartIndex_ += count;
}

void WaterFlowLayoutInfoSW::UpdateLanesIndex(int32_t updateIdx)
{
    idxToLane_.clear();
    const int32_t diff = newStartIndex_ - startIndex_;
    for (auto& section : lanes_) {
        for (size_t i = 0; i < section.size(); i++) {
            for (auto& item : section[i].items_) {
                item.idx += diff;
                idxToLane_[item.idx] = i;
            }
        }
    }
    startIndex_ = StartIndex();
    endIndex_ = EndIndex();
}

void WaterFlowLayoutInfoSW::BeginCacheUpdate()
{
    savedLanes_ = std::make_unique<decltype(lanes_)>(lanes_);
    synced_ = false;
}

void WaterFlowLayoutInfoSW::EndCacheUpdate()
{
    synced_ = true;
    if (savedLanes_) {
        lanes_ = std::move(*savedLanes_);
        savedLanes_.reset();
    }
}

void WaterFlowLayoutInfoSW::ClearData()
{
    segmentCache_.clear();
    segmentTails_.clear();
    lanes_.clear();
    idxToLane_.clear();
    margins_.clear();
    maxHeight_ = 0.0f;
    synced_ = false;
    startIndex_ = 0;
    endIndex_ = -1;
}
} // namespace OHOS::Ace::NG
