/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "base/log/event_report.h"

#include <numeric>

namespace OHOS::Ace::NG {
void WaterFlowLayoutInfoSW::Sync(int32_t itemCnt, float mainSize, const std::vector<float>& mainGap)
{
    if (lanes_.empty()) {
        return;
    }
    startIndex_ = StartIndex();
    endIndex_ = EndIndex();
    if (startIndex_ > endIndex_) {
        SyncOnEmptyLanes(mainSize);
        return;
    }
    const auto* startLane = GetLane(startIndex_);
    CHECK_NULL_VOID(startLane);
    storedOffset_ = startLane->startPos;

    delta_ = 0.0f;
    lastMainSize_ = mainSize;
    mainGap_ = mainGap;
    startPos_ = StartPos();
    endPos_ = EndPos();

    prevItemStart_ = itemStart_;
    itemStart_ = startIndex_ == 0 && NonNegative(startPos_ - TopMargin());
    itemEnd_ = endIndex_ == itemCnt - 1;
    if (footerIndex_ == 0) {
        itemEnd_ &= LessOrEqualCustomPrecision(endPos_, mainSize + expandHeight_, 0.1f);
    }

    if (itemEnd_) {
        knowTotalHeight_ = true;
    } else {
        footerHeight_ = 0.0f;
    }

    const float contentEnd = endPos_ + footerHeight_ + BotMargin();
    offsetEnd_ = itemEnd_ && LessOrEqualCustomPrecision(contentEnd, mainSize, 0.1f);
    maxHeight_ = std::max(-totalOffset_ + contentEnd, maxHeight_);

    newStartIndex_ = EMPTY_NEW_START_INDEX;
    isPrevOffsetValid_ = true;

    synced_ = true;
}

bool WaterFlowLayoutInfoSW::IsAtTopWithDelta()
{
    return AtStartPos(startIndex_) && NonNegative(startPos_ + delta_ - TopMargin());
}

bool WaterFlowLayoutInfoSW::IsAtBottomWithDelta()
{
    return itemEnd_ && LessOrEqualCustomPrecision(endPos_ + delta_ + footerHeight_ + BotMargin(), lastMainSize_, 0.1f);
}

float WaterFlowLayoutInfoSW::CalibrateOffset()
{
    if (startIndex_ == 0) {
        // can calibrate totalOffset when at top
        const float prev = totalOffset_;
        totalOffset_ = startPos_ - TopMargin();
        if (!NearEqual(totalOffset_, prev)) {
            maxHeight_ = endPos_;
            knowTotalHeight_ = false;
        }
        return totalOffset_ - prev;
    }
    return 0.0f;
}

float WaterFlowLayoutInfoSW::DistanceToTop(int32_t itemIdx, float mainGap) const
{
    if (!ItemInView(itemIdx)) {
        return 0.0f;
    }
    const auto* lane = GetLane(itemIdx);
    CHECK_NULL_RETURN(lane, 0.0f);
    float dist = lane->startPos;
    for (const auto& item : lane->items_) {
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
    const auto* lane = GetLane(itemIdx);
    CHECK_NULL_RETURN(lane, 0.0f);
    float dist = mainSize - lane->endPos;
    for (auto item = lane->items_.rbegin(); item != lane->items_.rend(); ++item) {
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
    if (itemStart_ && !lanes_[0].empty() && Positive(lanes_[0][0].startPos - TopMargin() + delta_)) {
        return true;
    }
    if (!itemStart_ && offsetEnd_) {
        return std::all_of(lanes_.back().begin(), lanes_.back().end(), [this](const Lane& lane) {
            return LessNotEqual(lane.endPos + footerHeight_ + BotMargin() + delta_, lastMainSize_);
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
    if (AtStartPos(startIndex_)) {
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
    if (Positive(disToBot) && LessNotEqual(maxHeight_, lastMainSize_)) {
        res.end = std::min(0.0f, disToBot + delta);
        return res;
    }
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
    if (section.empty()) {
        return 0.0f;
    }
    return std::max_element(section.begin(), section.end(), [](const Lane& left, const Lane& right) {
        return LessNotEqual(left.endPos, right.endPos);
    })->endPos;
}

inline float SectionStartPos(const std::vector<WaterFlowLayoutInfoSW::Lane>& section)
{
    if (section.empty()) {
        return 0.0f;
    }
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
    if (StartIndex() > EndIndex()) {
        // when lanes_ is empty, the endPos of all section is same.
        return lanes_[0][0].endPos;
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
    if (StartIndex() > EndIndex()) {
        // when lanes_ is empty, the startPos of all section is same.
        return lanes_[0][0].startPos;
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
    return firstLayout || prevItemStart_ != itemStart_ || backFromOverScroll;
}

bool WaterFlowLayoutInfoSW::ReachEnd(float prevPos, bool firstLayout) const
{
    if (!offsetEnd_ || lanes_.empty()) {
        return false;
    }
    const float prevEndPos = EndPosWithMargin() - (totalOffset_ - prevPos) + footerHeight_;
    const bool backFromOverScroll =
        LessNotEqualCustomPrecision(prevEndPos, lastMainSize_, -0.1f) &&
        GreatOrEqualCustomPrecision(EndPosWithMargin() + footerHeight_, lastMainSize_, -0.1f);
    return firstLayout || GreatNotEqualCustomPrecision(prevEndPos, lastMainSize_, 0.1f) || backFromOverScroll;
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
    const auto* lane = GetLane(idx);
    CHECK_NULL_RETURN(lane, Infinity<float>());
    float pos = 0.0f; // main-axis position of the item's top edge relative to viewport top. Positive if below viewport
    float itemSize = 0.0f;
    if (idx < endIndex_) {
        pos = DistanceToTop(idx, mainGap_[GetSegment(idx)]);
        auto it = std::find_if(
            lane->items_.begin(), lane->items_.end(), [idx](const ItemInfo& item) { return item.idx == idx; });
        if (it == lane->items_.end()) {
            return Infinity<float>();
        }
        itemSize = it->mainSize;
    } else {
        if (lane->items_.empty()) {
            return Infinity<float>();
        }
        itemSize = lane->items_.back().mainSize;
        pos = lane->endPos - itemSize;
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
    if (startIndex_ > endIndex_ || jumpIndex_ != EMPTY_JUMP_INDEX) {
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
    idxToHeight_.clear();
    heightSum_ = 0.0f;
    maxHeight_ = 0.0f;
    knowTotalHeight_ = false;
    synced_ = false;
}

void WaterFlowLayoutInfoSW::ResetFooter()
{
    footerIndex_ = -1;
    footerHeight_ = 0.0f;
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
    if (!ItemInView(itemIndex)) {
        return -1;
    }
    auto it = idxToLane_.find(itemIndex);
    if (it == idxToLane_.end()) {
        return -1;
    }
    return static_cast<int32_t>(it->second);
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
    knowTotalHeight_ = false;
    idxToLane_.clear();
    idxToHeight_.clear();
    heightSum_ = 0.0f;
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

namespace {
/**
 * @brief erase elements in range [idx, end)
 */
template<typename T>
void EraseFrom(int32_t idx, std::unordered_map<int32_t, T>& hashTable)
{
    for (auto it = hashTable.begin(); it != hashTable.end();) {
        if (it->first >= idx) {
            it = hashTable.erase(it); // Erase and get the iterator to the next element
        } else {
            ++it;
        }
    }
}
} // namespace

void WaterFlowLayoutInfoSW::ClearDataFrom(int32_t idx, const std::vector<float>& mainGap)
{
    EraseFrom(idx, idxToLane_);
    EraseFrom(idx, idxToHeight_);
    heightSum_ = 0.0f;

    if (mainGap.size() < lanes_.size()) {
        TAG_LOGW(ACE_WATERFLOW,
            "internal data structure is corrupted. mainGap size = %{public}zu, lanes size = %{public}zu",
            mainGap.size(), lanes_.size());
        return;
    }
    int32_t segment = GetSegment(idx);
    for (int32_t i = segment; i < static_cast<int32_t>(lanes_.size()); ++i) {
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
        if (i >= static_cast<int32_t>(lanes_.size())) {
            break;
        }
        if (SectionEmpty(lanes_[i])) {
            continue;
        }
        const float startPos = SectionStartPos(lanes_[i]);
        if (std::any_of(lanes_[i].begin(), lanes_[i].end(),
            [&startPos](const auto& lane) { return !NearEqual(lane.startPos, startPos, 0.01); })) {
            return true;
        }
        if (lanes_[i].empty() || lanes_[i][0].items_.empty()) {
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
    if (n == 0) {
        segmentTails_.clear();
        return;
    }
    segmentTails_ = { sections[0].itemsCount - 1 };
    for (size_t i = 1; i < n; ++i) {
        segmentTails_.push_back(segmentTails_[i - 1] + sections[i].itemsCount);
    }
}

void WaterFlowLayoutInfoSW::InitLanes(const std::vector<WaterFlowSections::Section>& sections, int32_t start)
{
    const size_t n = sections.size();

    start = std::min(start, static_cast<int32_t>(n));
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
    if (curSegIdx >= n) {
        return false;
    }
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

void WaterFlowLayoutInfoSW::NotifySectionChange(int32_t index)
{
    if (startIndex_ == Infinity<int32_t>()) {
        newStartIndex_ = INVALID_NEW_START_INDEX;
        return;
    }
    if (index >= startIndex_) {
        newStartIndex_ = INVALID_NEW_START_INDEX;
    }
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
    idxToHeight_.clear();
    heightSum_ = 0.0f;
    margins_.clear();
    maxHeight_ = 0.0f;
    knowTotalHeight_ = false;
    synced_ = false;
    startIndex_ = 0;
    endIndex_ = -1;
}

float WaterFlowLayoutInfoSW::GetAverageItemHeight() const
{
    if (idxToHeight_.empty()) {
        return 0.0f;
    }
    if (NearZero(heightSum_)) {
        heightSum_ = std::accumulate(idxToHeight_.begin(), idxToHeight_.end(), 0.0f,
            [](float sum, const auto& pair) { return sum + pair.second; });
    }
    return heightSum_ / static_cast<float>(idxToHeight_.size());
}

float WaterFlowLayoutInfoSW::EstimateTotalHeight() const
{
    if (!synced_) {
        return 0.0f;
    }
    if (knowTotalHeight_ && repeatDifference_ == 0) {
        return maxHeight_;
    }
    float height = std::max(-totalOffset_, 0.0f) // to eliminate top overScroll
                   + (endPos_ - startPos_);
    if (itemEnd_ && repeatDifference_ == 0) {
        float bottomOverScroll = std::max(BottomFinalPos(lastMainSize_), 0.0f);
        return height - bottomOverScroll + BotMargin() + footerHeight_;
    }

    const float average = GetAverageItemHeight();
    for (uint32_t i = static_cast<uint32_t>(GetSegment(endIndex_ + 1)); i < lanes_.size(); ++i) {
        height += EstimateSectionHeight(i, average, endIndex_ + 1, INT_MAX);
    }
    float virtualTotalHeight = 0.f;
    if (EstimateVirtualTotalHeight(average, virtualTotalHeight)) {
        height += virtualTotalHeight;
        return height;
    } else {
        return std::max(height, maxHeight_);
    }
}

bool WaterFlowLayoutInfoSW::EstimateVirtualTotalHeight(float average, float& virtualTotalHeight) const
{
    CHECK_NULL_RETURN(repeatDifference_ > 0 && lanes_.size() <= mainGap_.size() && lanes_.size() >= 1, false);
    const size_t crossCnt = std::max((lanes_.rbegin())->size(), (size_t)1);
    virtualTotalHeight = (average + mainGap_[static_cast<int32_t>(lanes_.size() - 1)]) * repeatDifference_ /
                         static_cast<float>(crossCnt);
    return true;
}

void WaterFlowLayoutInfoSW::EstimateTotalOffset(int32_t prevStart, int32_t startIdx)
{
    const float average = GetAverageItemHeight();
    const int32_t section = GetSegment(startIdx);
    const float prevOffset = totalOffset_;
    totalOffset_ = StartPos();

    for (int32_t i = 0; i <= section; ++i) {
        totalOffset_ -= EstimateSectionHeight(i, average, INT_MIN, startIdx - 1);
    }

    // filter unreasonable estimates
    if (!isPrevOffsetValid_) {
        return;
    }

    if (prevStart <= startIdx) {
        totalOffset_ = std::min(totalOffset_, prevOffset - average);
    } else {
        totalOffset_ = std::max(totalOffset_, prevOffset + average);
    }
}

bool WaterFlowLayoutInfoSW::TryConvertLargeDeltaToJump(float viewport, int32_t itemCnt)
{
    using std::abs, std::round, std::clamp;
    const float offset = StartPos() + delta_;
    if (LessOrEqual(abs(delta_), viewport * 2.0f)) {
        return false;
    }
    const int32_t startIdx = StartIndex();
    const auto curSec = static_cast<uint32_t>(GetSegment(startIdx)); // change function return type to uint later
    if (curSec >= lanes_.size() || curSec >= mainGap_.size()) {
        return false;
    }

    const auto crossCnt = static_cast<float>(lanes_[curSec].size());
    const float average = GetAverageItemHeight() + mainGap_[curSec];
    if (NearZero(average)) {
        return false;
    }

    jumpIndex_ = startIdx - static_cast<int32_t>(round(offset * crossCnt / average));
    jumpIndex_ = clamp(jumpIndex_, 0, itemCnt - 1);
    align_ = ScrollAlign::START;
    delta_ = 0.0f;
    return true;
}

float WaterFlowLayoutInfoSW::EstimateSectionHeight(
    uint32_t section, float average, int32_t startBound, int32_t endBound) const
{
    if (segmentTails_.size() <= section || lanes_.size() <= section || mainGap_.size() <= section ||
        margins_.size() <= section) {
        return 0.0f;
    }
    startBound = std::max((section == 0) ? 0 : segmentTails_[section - 1] + 1, startBound);
    endBound = std::min(segmentTails_[section], endBound);
    const size_t crossCnt = std::max(lanes_[section].size(), (size_t)1); // prevent division by 0

    float height = 0.0f;
    for (int32_t i = startBound; i <= endBound; ++i) {
        height += GetCachedHeight(i).value_or(average) + mainGap_[section];
    }
    height /= static_cast<float>(crossCnt);
    height += average; // to compensate half-filled last row
    height += axis_ == Axis::VERTICAL ? margins_[section].Height() : margins_[section].Width();
    return height;
}

std::optional<float> WaterFlowLayoutInfoSW::GetCachedHeight(int32_t idx) const
{
    auto it = idxToHeight_.find(idx);
    if (it != idxToHeight_.end()) {
        return it->second;
    }
    return std::nullopt;
}

void WaterFlowLayoutInfoSW::SyncOnEmptyLanes(float mainSize)
{
    startPos_ = StartPos();
    endPos_ = EndPos();
    itemStart_ = NonNegative(startPos_ - TopMargin());
    itemEnd_ = true;
    offsetEnd_ = LessOrEqualCustomPrecision(endPos_ + footerHeight_ + BotMargin(), mainSize, 0.1f);
    maxHeight_ = footerHeight_;
    knowTotalHeight_ = true;
    newStartIndex_ = EMPTY_NEW_START_INDEX;
    delta_ = 0.0f;
    lastMainSize_ = mainSize;
    synced_ = true;
}

bool WaterFlowLayoutInfoSW::LaneOutOfRange(size_t laneIdx, int32_t section) const
{
    if (laneIdx >= lanes_[section].size()) {
        TAG_LOGW(ACE_WATERFLOW, "lane %{public}zu is out of bounds in section %{public}d", laneIdx, section);
        return true;
    }
    return false;
}

Lane* WaterFlowLayoutInfoSW::GetMutableLane(int32_t itemIdx)
{
    return const_cast<Lane*>(GetLane(itemIdx));
}

const Lane* WaterFlowLayoutInfoSW::GetLane(int32_t itemIdx) const
{
    if (!idxToLane_.count(itemIdx)) {
        TAG_LOGW(ACE_WATERFLOW, "Inconsistent data found on item %{public}d", itemIdx);
        std::string subErrorType = "Inconsistent data found on item " + std::to_string(itemIdx);
        EventReport::ReportScrollableErrorEvent("WaterFlow", ScrollableErrorType::INTERNAL_ERROR, subErrorType);
        return nullptr;
    }
    size_t laneIdx = idxToLane_.at(itemIdx);
    int32_t secIdx = GetSegment(itemIdx);
    if (LaneOutOfRange(laneIdx, secIdx)) {
        return nullptr;
    }
    auto&& lane = lanes_[secIdx][laneIdx];
    if (lane.items_.empty()) {
        TAG_LOGW(ACE_WATERFLOW, "Inconsistent data found on item %{public}d when accessing lane %{public}zu", itemIdx,
            laneIdx);
        std::string subErrorType = "Inconsistent data found on item " + std::to_string(itemIdx) +
                                   " when accessing lane " + std::to_string(laneIdx);
        EventReport::ReportScrollableErrorEvent("WaterFlow", ScrollableErrorType::INTERNAL_ERROR, subErrorType);
        return nullptr;
    }
    return &lane;
}

float WaterFlowLayoutInfoSW::GetDistanceToTop(int32_t itemIdx, int32_t laneIdx, float mainGap) const
{
    if (!ItemInView(itemIdx)) {
        int32_t seg = GetSegment(itemIdx);
        return lanes_[seg][laneIdx].endPos;
    }
    return DistanceToTop(itemIdx, mainGap);
}

float WaterFlowLayoutInfoSW::GetDistanceToBottom(int32_t itemIdx, int32_t laneIdx, float mainSize, float mainGap) const
{
    if (!ItemInView(itemIdx)) {
        int32_t seg = GetSegment(itemIdx);
        return lanes_[seg][laneIdx].startPos;
    }
    return DistanceToTop(itemIdx, mainGap) + GetCachedHeightInLanes(itemIdx);
}

float WaterFlowLayoutInfoSW::GetCachedHeightInLanes(int32_t idx) const
{
    const auto* lane = GetLane(idx);
    CHECK_NULL_RETURN(lane, 0.0f);
    for (const auto& item : lane->items_) {
        if (item.idx == idx) {
            return item.mainSize;
        }
    }
    return 0.0f;
}

void WaterFlowLayoutInfoSW::SetHeightInLanes(int32_t idx, float mainHeight)
{
    auto* lane = GetMutableLane(idx);
    CHECK_NULL_VOID(lane);
    for (auto& item : lane->items_) {
        if (item.idx == idx) {
            item.mainSize = mainHeight;
        }
    }
}

bool WaterFlowLayoutInfoSW::HaveRecordIdx(int32_t idx) const
{
    const auto* lane = GetLane(idx);
    CHECK_NULL_RETURN(lane, false);
    for (const auto& item : lane->items_) {
        if (item.idx == idx) {
            return true;
        }
    }
    return false;
}
} // namespace OHOS::Ace::NG
