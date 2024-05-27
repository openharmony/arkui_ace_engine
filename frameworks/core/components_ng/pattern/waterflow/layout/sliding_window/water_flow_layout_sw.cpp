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
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_layout_sw.h"

#include <algorithm>
#include <cfloat>
#include <queue>

#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void WaterFlowLayoutSW::Measure(LayoutWrapper* wrapper)
{
    info_->BeginUpdate();
    wrapper_ = wrapper;
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper->GetLayoutProperty());
    info_->axis_ = axis_ = props->GetAxis();

    auto [size, matchChildren] = WaterFlowLayoutUtils::PreMeasureSelf(wrapper_, axis_);
    Init(size);
    if (info_->segmentTails_.empty() || info_->segmentTails_.back() != itemCnt_ - 1) {
        return;
    }

    if (info_->jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(info_->jumpIndex_, info_->align_);
    } else if (info_->targetIndex_) {
        MeasureToTarget(*info_->targetIndex_);
    } else {
        MeasureOnOffset(info_->delta_);
    }
    if (matchChildren) {
        PostMeasureSelf(size.CrossSize(axis_));
    }

    info_->Sync(itemCnt_, mainLen_, mainGap_);
    wrapper->SetCacheCount(props->GetCachedCountValue(1));
}

void WaterFlowLayoutSW::Layout(LayoutWrapper* wrapper)
{
    if (info_->sections_.empty()) {
        return;
    }
    if (info_->segmentTails_.empty() || info_->segmentTails_.back() != itemCnt_ - 1) {
        return;
    }

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper->GetLayoutProperty());
    auto padding = props->CreatePaddingAndBorder();
    OffsetF paddingOffset { padding.top.value_or(0.0f), padding.top.value_or(0.0f) };

    bool reverse = props->IsReverse();
    bool rtl = props->GetNonAutoLayoutDirection() == TextDirection::RTL && axis_ == Axis::VERTICAL;
    float selfCrossLen = wrapper->GetGeometryNode()->GetContentSize().CrossSize(axis_);

    for (size_t idx = 0; idx < info_->sections_.size(); ++idx) {
        LayoutSection(idx, paddingOffset, selfCrossLen, reverse, rtl);
    }

    auto cachedCount = props->GetCachedCountValue(1);
    wrapper->SetActiveChildRange(nodeIdx(info_->startIndex_), nodeIdx(info_->endIndex_), cachedCount, cachedCount);
    PreBuildItems(wrapper_, info_,
        WaterFlowLayoutUtils::CreateChildConstraint({ itemCrossSize_[0], mainLen_, axis_ }, props, nullptr),
        cachedCount);

    if (info_->itemEnd_) {
        LayoutFooter(paddingOffset, reverse);
    }
}

void WaterFlowLayoutSW::Init(const SizeF& frameSize)
{
    sections_ = wrapper_->GetHostNode()->GetPattern<WaterFlowPattern>()->GetSections();
    if (sections_) {
        SectionInit(frameSize);
    } else {
        SingleInit(frameSize);
    }
    CheckReset();
    InitLanes();
}

void WaterFlowLayoutSW::SingleInit(const SizeF& frameSize)
{
    // omit footer from children count
    itemCnt_ = wrapper_->GetTotalChildCount() - info_->footerIndex_ - 1;
    info_->segmentTails_ = { itemCnt_ - 1 };
    info_->margins_.resize(1);

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    crossGap_ = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    mainLen_ = frameSize.MainSize(axis_);
    float crossSize = frameSize.CrossSize(axis_);
    std::pair<std::vector<double>, double> cross;
    auto rowsTemplate = props->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = props->GetColumnsTemplate().value_or("1fr");
    if (axis_ == Axis::VERTICAL) {
        cross = ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGap_, itemCnt_);
    } else {
        cross = ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGap_, itemCnt_);
    }
    if (cross.first.empty()) {
        cross.first = { crossSize };
    }
    crossGap_ = cross.second;

    itemCrossSize_.resize(1);
    for (const auto& len : cross.first) {
        itemCrossSize_[0].push_back(static_cast<float>(len));
    }
    if (itemCrossSize_.empty()) {
        itemCrossSize_[0].push_back(crossSize);
    }
}

void WaterFlowLayoutSW::CheckReset()
{
    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (updateIdx > -1) {
        if (updateIdx <= info_->startIndex_) {
            info_->Reset();
        } else {
            info_->ClearDataFrom(updateIdx, mainGap_);
        }
        wrapper_->GetHostNode()->ChildrenUpdatedFrom(-1);
        return;
    }

    if (wrapper_->GetLayoutProperty()->GetPropertyChangeFlag() & PROPERTY_UPDATE_BY_CHILD_REQUEST) {
        info_->Reset();
        return;
    }

    if (!wrapper_->IsConstraintNoChanged()) {
        info_->Reset();
        return;
    }
}

void WaterFlowLayoutSW::MeasureOnOffset(float delta)
{
    ApplyDelta(delta);
    AdjustOverScroll();
    // clear out items outside viewport after position change
    if (Positive(delta)) {
        ClearBack(mainLen_);
    } else {
        ClearFront();
    }
}

void WaterFlowLayoutSW::ApplyDelta(float delta)
{
    info_->totalOffset_ += delta;
    for (auto& section : info_->sections_) {
        for (auto& lane : section) {
            lane.startPos += delta;
            lane.endPos += delta;
        }
    }

    if (Positive(delta)) {
        // positive offset is scrolling upwards
        FillFront(0.0f, info_->StartIndex() - 1, 0);
    } else {
        FillBack(mainLen_, info_->EndIndex() + 1, itemCnt_ - 1);
    }
}

void WaterFlowLayoutSW::MeasureToTarget(int32_t targetIdx)
{
    if (itemCnt_ == 0) {
        return;
    }
    if (targetIdx < info_->startIndex_) {
        FillFront(-FLT_MAX, info_->startIndex_ - 1, targetIdx);
    } else if (targetIdx > info_->endIndex_) {
        FillBack(FLT_MAX, info_->endIndex_ + 1, targetIdx);
    }
}

namespace {
// [lane start/end position, lane index]
using lanePos = std::pair<float, size_t>;

// max heap but with smaller laneIdx at the top
struct MaxHeapCmp {
    bool operator()(const lanePos& left, const lanePos& right)
    {
        if (NearEqual(left.first, right.first)) {
            return left.second > right.second;
        }
        return LessNotEqual(left.first, right.first);
    }
};

using StartPosQ = std::priority_queue<lanePos, std::vector<lanePos>, MaxHeapCmp>;
using EndPosQ = std::priority_queue<lanePos, std::vector<lanePos>, std::greater<>>;

using Lanes = std::vector<WaterFlowLayoutInfoSW::Lane>;

void PrepareStartPosQueue(StartPosQ& q, Lanes& lanes, float mainGap, float viewportBound)
{
    for (size_t i = 0; i < lanes.size(); ++i) {
        float endPos = lanes[i].endPos + (lanes[i].items_.empty() ? 0.0f : mainGap);
        if (LessNotEqual(endPos, viewportBound)) {
            q.push({ endPos, i });
        }
    }
}

void PrepareEndPosQueue(EndPosQ& q, Lanes& lanes, float mainGap, float viewportBound)
{
    for (size_t i = 0; i < lanes.size(); ++i) {
        float endPos = lanes[i].endPos + (lanes[i].items_.empty() ? 0.0f : mainGap);
        if (LessNotEqual(endPos, viewportBound)) {
            q.push({ endPos, i });
        }
    }
}
} // namespace

void WaterFlowLayoutSW::FillBack(float viewportBound, int32_t idx, int32_t maxChildIdx)
{
    idx = std::max(idx, 0);
    maxChildIdx = std::min(maxChildIdx, itemCnt_ - 1);
    info_->PrepareSection(idx, true);
    while (!FillBackSection(viewportBound, idx, maxChildIdx)) {
        if (idx > maxChildIdx) {
            break;
        }
        info_->PrepareSection(idx, true);
    }
}

bool WaterFlowLayoutSW::FillBackSection(float viewportBound, int32_t& idx, int32_t maxChildIdx)
{
    int32_t section = info_->GetSegment(idx);
    maxChildIdx = std::min(maxChildIdx, info_->segmentTails_[section]);
    if (info_->idxToLane_.count(idx)) {
        RecoverBack(viewportBound, idx, maxChildIdx);
    }
    EndPosQ q;
    PrepareEndPosQueue(q, info_->sections_[info_->GetSegment(idx)], mainGap_, viewportBound);

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!q.empty() && idx <= maxChildIdx) {
        auto [_, laneIdx] = q.top();
        q.pop();
        info_->idxToLane_[idx] = laneIdx;
        float endPos = FillBackHelper(props, idx++, laneIdx);
        if (LessNotEqual(endPos, viewportBound)) {
            q.push({ endPos, laneIdx });
        }
    }
    return q.empty();
}

void WaterFlowLayoutSW::FillFront(float viewportBound, int32_t idx, int32_t minChildIdx)
{
    idx = std::min(itemCnt_ - 1, idx);
    minChildIdx = std::max(minChildIdx, 0);
    info_->PrepareSection(idx, false);
    while (!FillBackSection(viewportBound, idx, minChildIdx)) {
        if (idx < minChildIdx) {
            break;
        }
        info_->PrepareSection(idx, false);
    }
}

bool WaterFlowLayoutSW::FillFrontSection(float viewportBound, int32_t& idx, int32_t minChildIdx)
{
    int32_t secIdx = info_->GetSegment(idx);
    minChildIdx = std::max(minChildIdx, secIdx > 0 ? info_->segmentTails_[secIdx - 1] + 1 : 0);
    if (info_->idxToLane_.count(idx)) {
        RecoverFront(viewportBound, idx, minChildIdx);
    }
    StartPosQ q;
    PrepareStartPosQueue(q, info_->sections_[secIdx], mainGap_, viewportBound);

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!q.empty() && idx >= minChildIdx) {
        auto [_, laneIdx] = q.top();
        q.pop();
        info_->idxToLane_[idx] = laneIdx;
        float startPos = FillFrontHelper(props, idx--, laneIdx);
        if (GreatNotEqual(startPos - mainGap_, viewportBound)) {
            q.push({ startPos, laneIdx });
        }
    }
    return q.empty();
}

float WaterFlowLayoutSW::FillBackHelper(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t laneIdx)
{
    float mainLen = MeasureChild(props, idx, laneIdx);
    auto& lane = info_->sections_[info_->GetSegment(idx)][laneIdx];
    lane.endPos += mainGap_ + mainLen;
    if (lane.items_.empty()) {
        lane.endPos -= mainGap_;
    }
    lane.items_.push_back({ idx, mainLen });
    return lane.endPos;
}

float WaterFlowLayoutSW::FillFrontHelper(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t laneIdx)
{
    float mainLen = MeasureChild(props, idx, laneIdx);
    auto& lane = info_->sections_[info_->GetSegment(idx)][laneIdx];
    lane.startPos -= mainGap_ + mainLen;
    if (lane.items_.empty()) {
        lane.startPos += mainGap_;
    }
    lane.items_.push_front({ idx, mainLen });
    return lane.startPos;
}

void WaterFlowLayoutSW::RecoverBack(float viewportBound, int32_t& idx, int32_t maxChildIdx)
{
    std::unordered_set<size_t> lanes;
    int32_t secIdx = info_->GetSegment(idx);
    for (size_t i = 0; i < info_->sections_[secIdx].size(); ++i) {
        float endPos =
            info_->sections_[secIdx][i].endPos + (info_->sections_[secIdx][i].items_.empty() ? 0.0f : mainGap_);
        if (LessNotEqual(endPos, viewportBound)) {
            lanes.insert(i);
        }
    }

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!lanes.empty() && idx <= maxChildIdx && info_->idxToLane_.count(idx)) {
        size_t laneIdx = info_->idxToLane_.at(idx);
        float endPos = FillBackHelper(props, idx++, laneIdx);
        if (GreatOrEqual(endPos + mainGap_, viewportBound)) {
            lanes.erase(laneIdx);
        }
    }
}

void WaterFlowLayoutSW::RecoverFront(float viewportBound, int32_t& idx, int32_t minChildIdx)
{
    std::unordered_set<size_t> lanes;
    int32_t secIdx = info_->GetSegment(idx);
    for (size_t i = 0; i < info_->sections_[secIdx].size(); ++i) {
        float startPos =
            info_->sections_[secIdx][i].startPos - (info_->sections_[secIdx][i].items_.empty() ? 0.0f : mainGap_);
        if (GreatNotEqual(startPos, viewportBound)) {
            lanes.insert(i);
        }
    }
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!lanes.empty() && idx >= minChildIdx && info_->idxToLane_.count(idx)) {
        size_t laneIdx = info_->idxToLane_.at(idx);
        float startPos = FillFrontHelper(props, idx--, laneIdx);
        if (LessOrEqual(startPos, viewportBound)) {
            lanes.erase(laneIdx);
        }
    }
}

void WaterFlowLayoutSW::ClearBack(float bound)
{
    int32_t startIdx = info_->StartIndex();
    for (int32_t i = info_->EndIndex(); i > startIdx; --i) {
        size_t laneIdx = info_->idxToLane_.at(i);
        auto& lane = info_->sections_[info_->GetSegment(i)][laneIdx];
        float itemStartPos = lane.endPos - lane.items_.back().mainSize;
        if (LessNotEqual(itemStartPos, bound)) {
            break;
        }
        lane.items_.pop_back();
        lane.endPos = itemStartPos - mainGap_;
        if (lane.items_.empty()) {
            lane.endPos += mainGap_;
        }
    }
}

void WaterFlowLayoutSW::ClearFront()
{
    int32_t endIdx = info_->EndIndex();
    for (int32_t i = info_->StartIndex(); i < endIdx; ++i) {
        size_t laneIdx = info_->idxToLane_.at(i);
        auto& lane = info_->sections_[info_->GetSegment(i)][laneIdx];
        float itemEndPos = lane.startPos + lane.items_.front().mainSize;
        if (Positive(itemEndPos)) {
            break;
        }
        lane.items_.pop_front();
        lane.startPos = itemEndPos + mainGap_;
        if (lane.items_.empty()) {
            lane.startPos -= mainGap_;
        }
    }
}

ScrollAlign WaterFlowLayoutSW::ParseAutoAlign(int32_t jumpIdx, bool inView)
{
    if (inView) {
        if (Negative(info_->DistanceToTop(jumpIdx, mainGap_))) {
            return ScrollAlign::START;
        }
        if (Negative(info_->DistanceToBottom(jumpIdx, mainLen_, mainGap_))) {
            return ScrollAlign::END;
        }
        // item is already fully in viewport
        return ScrollAlign::NONE;
    }
    if (jumpIdx < info_->startIndex_) {
        return ScrollAlign::START;
    }
    return ScrollAlign::END;
}

void WaterFlowLayoutSW::MeasureOnJump(int32_t jumpIdx, ScrollAlign align)
{
    if (jumpIdx == LAST_ITEM) {
        jumpIdx = itemCnt_ - 1;
    } else if (jumpIdx == itemCnt_ && info_->footerIndex_ == 0) {
        // jump to footer
        info_->delta_ = -Infinity<float>();
    }
    overScroll_ = false;

    bool inView = info_->ItemInView(jumpIdx);
    if (align == ScrollAlign::AUTO) {
        align = ParseAutoAlign(jumpIdx, inView);
    }

    // If item is close, we simply scroll to it instead of triggering a reset/jump, which would change the layout.
    bool closeToView = info_->ItemCloseToView(jumpIdx);
    if (closeToView) {
        MeasureToTarget(jumpIdx);
    }
    Jump(jumpIdx, align, inView || closeToView);
    if (!NearZero(info_->delta_)) {
        MeasureOnOffset(info_->delta_);
    } else {
        AdjustOverScroll();
        ClearFront();
        ClearBack(mainLen_);
    }
}

void WaterFlowLayoutSW::Jump(int32_t jumpIdx, ScrollAlign align, bool noSkip)
{
    switch (align) {
        case ScrollAlign::START: {
            if (noSkip) {
                ApplyDelta(-info_->DistanceToTop(jumpIdx, mainGap_));
            } else {
                info_->ResetBeforeJump(0.0f);
                FillBack(mainLen_, jumpIdx, itemCnt_ - 1);
            }
            break;
        }
        case ScrollAlign::CENTER: {
            auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
            if (noSkip) {
                float itemH = MeasureChild(props, jumpIdx, info_->idxToLane_.at(jumpIdx));
                ApplyDelta(-info_->DistanceToTop(jumpIdx, mainGap_) + (mainLen_ - itemH) / 2.0f);
            } else {
                info_->ResetBeforeJump(mainLen_ / 2.0f);
                info_->idxToLane_ = { { jumpIdx, 0 } };
                auto& lane = info_->sections_[info_->GetSegment(jumpIdx)][0];
                float itemH = MeasureChild(props, jumpIdx, 0);
                lane.startPos = (mainLen_ - itemH) / 2.0f;
                lane.endPos = (mainLen_ + itemH) / 2.0f;
                lane.items_.push_back({ jumpIdx, itemH });

                FillFront(0.0f, jumpIdx - 1, 0);
                FillBack(mainLen_, jumpIdx + 1, itemCnt_ - 1);
            }
            break;
        }
        case ScrollAlign::END: {
            if (noSkip) {
                ApplyDelta(info_->DistanceToBottom(jumpIdx, mainLen_, mainGap_));
            } else {
                info_->ResetBeforeJump(mainLen_);
                FillFront(0.0f, jumpIdx, 0);
            }
            break;
        }
        default:
            break;
    }
}

void WaterFlowLayoutSW::AdjustOverScroll()
{
    if (info_->sections_.empty()) {
        return;
    }
    float maxEnd = info_->EndPos();
    float minStart = info_->StartPos();

    if (LessOrEqual(maxEnd, mainLen_) && info_->footerIndex_ == 0) {
        info_->footerHeight_ = WaterFlowLayoutUtils::MeasureFooter(wrapper_, axis_);
        maxEnd += info_->footerHeight_;
    }

    if (overScroll_) {
        return;
    }
    int32_t startIdx = info_->StartIndex();
    if (startIdx == 0 && Positive(minStart)) {
        ApplyDelta(-minStart);
    } else if (info_->EndIndex() == itemCnt_ - 1 && LessNotEqual(maxEnd, mainLen_)) {
        float delta = mainLen_ - maxEnd;
        if (startIdx == 0) {
            delta = std::min(-minStart, delta);
        }
        ApplyDelta(delta);
    }
}

float WaterFlowLayoutSW::MeasureChild(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t lane)
{
    auto child = wrapper_->GetOrCreateChildByIndex(nodeIdx(idx));
    CHECK_NULL_RETURN(child, 0.0f);
    child->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
        { itemCrossSize_[info_->GetSegment(idx)][lane], mainLen_, axis_ }, props, child));
    return child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
}

void WaterFlowLayoutSW::LayoutSection(
    size_t idx, const OffsetF& paddingOffset, float selfCrossLen, bool reverse, bool rtl)
{
    float crossPos = rtl ? selfCrossLen + mainGap_ : 0.0f;
    for (size_t i = 0; i < info_->sections_[idx].size(); ++i) {
        if (rtl) {
            crossPos -= itemCrossSize_[idx][i] + crossGap_;
        }
        auto& lane = info_->sections_[idx][i];
        float mainPos = lane.startPos;
        for (auto& item : lane.items_) {
            auto child = wrapper_->GetOrCreateChildByIndex(nodeIdx(item.idx));
            if (!child) {
                continue;
            }
            auto childNode = child->GetGeometryNode();
            auto offset =
                reverse ? OffsetF { crossPos, mainLen_ - item.mainSize - mainPos } : OffsetF { crossPos, mainPos };
            if (axis_ != Axis::VERTICAL) {
                offset = OffsetF { offset.GetY(), offset.GetX() };
            }
            childNode->SetMarginFrameOffset(offset + paddingOffset);

            if (child->CheckNeedForceMeasureAndLayout()) {
                child->Layout();
            } else {
                child->GetHostNode()->ForceSyncGeometryNode();
            }
            mainPos += item.mainSize + mainGap_;
        }
        if (!rtl) {
            crossPos += itemCrossSize_[idx][i] + crossGap_;
        }
    }
}

void WaterFlowLayoutSW::LayoutFooter(const OffsetF& paddingOffset, bool reverse)
{
    float mainPos = info_->EndPos();
    if (info_->footerIndex_ != 0 || GreatOrEqual(mainPos, mainLen_)) {
        return;
    }
    auto footer = wrapper_->GetOrCreateChildByIndex(0);
    if (reverse) {
        mainPos = mainLen_ - info_->footerHeight_ - mainPos;
    }
    footer->GetGeometryNode()->SetMarginFrameOffset(
        (axis_ == Axis::VERTICAL) ? OffsetF(0.0f, mainPos) + paddingOffset : OffsetF(mainPos, 0.0f) + paddingOffset);
    footer->Layout();
}

void WaterFlowLayoutSW::PostMeasureSelf(float selfCrossLen)
{
    mainLen_ = info_->GetContentHeight();
    SizeF selfSize = (axis_ == Axis::VERTICAL) ? SizeF(selfCrossLen, mainLen_) : SizeF(mainLen_, selfCrossLen);
    auto props = wrapper_->GetLayoutProperty();
    AddPaddingToSize(props->CreatePaddingAndBorder(), selfSize);
    wrapper_->GetGeometryNode()->SetFrameSize(selfSize);
}

inline int32_t WaterFlowLayoutSW::nodeIdx(int32_t idx) const
{
    return idx + info_->footerIndex_ + 1;
}
void WaterFlowLayoutSW::InitLanes()
{
    for (size_t i = 0; i < itemCrossSize_.size(); ++i) {
        if (info_->sections_[i].empty()) {
            info_->sections_[i].resize(itemCrossSize_[i].size());
        }
    }
}
} // namespace OHOS::Ace::NG
