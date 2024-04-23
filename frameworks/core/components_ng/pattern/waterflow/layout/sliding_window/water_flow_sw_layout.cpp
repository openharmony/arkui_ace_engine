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
#include "core/components_ng/pattern/waterflow/layout/sliding_window/water_flow_sw_layout.h"

#include <algorithm>
#include <cfloat>
#include <queue>

#include "base/utils/utils.h"
#include "core/components/scroll/scroll_controller_base.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info_base.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void WaterFlowSWLayout::Measure(LayoutWrapper* wrapper)
{
    wrapper_ = wrapper;
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper->GetLayoutProperty());
    axis_ = axis_ = props->GetAxis();

    auto [idealSize, matchChildren] = WaterFlowLayoutUtils::PreMeasureSelf(wrapper_, axis_);
    Init(idealSize);
    CheckReset();

    if (info_->jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(info_->jumpIndex_, info_->align_);
        if (!NearZero(info_->delta_)) {
            overScroll_ = false;
            MeasureOnOffset(info_->delta_);
        }
    } else if (info_->targetIndex_) {
        MeasureToTarget(*info_->targetIndex_);
    } else {
        MeasureOnOffset(info_->delta_);
    }
    // if (matchChildren) {
    //     PostMeasureSelf();
    // }

    info_->Sync(mainSize_, mainGap_);
    wrapper->SetCacheCount(props->GetCachedCountValue(1));
}

void WaterFlowSWLayout::Layout(LayoutWrapper* wrapper)
{
    if (info_->lanes_.empty()) {
        return;
    }

    float crossPos = 0.0f;
    for (size_t i = 0; i < info_->lanes_.size(); ++i) {
        auto& lane = info_->lanes_[i];
        float mainPos = lane.startPos;
        for (auto& item : lane.items_) {
            auto child = wrapper->GetOrCreateChildByIndex(item.idx);
            if (!child) {
                continue;
            }
            auto childNode = child->GetGeometryNode();
            childNode->SetMarginFrameOffset(
                info_->axis_ == Axis::VERTICAL ? OffsetF { crossPos, mainPos } : OffsetF { mainPos, crossPos });
            if (child->CheckNeedForceMeasureAndLayout()) {
                child->Layout();
            } else {
                child->GetHostNode()->ForceSyncGeometryNode();
            }
            mainPos += childNode->GetMarginFrameSize().MainSize(info_->axis_) + mainGap_;
        }
        crossPos += itemCrossSize_[i] + crossGap_;
    }
    wrapper->SetActiveChildRange(info_->startIndex_, info_->endIndex_);
    for (int32_t i = info_->startIndex_; i <= info_->endIndex_; ++i) {
        if (!info_->idxToLane_.count(i)) {
            wrapper->RemoveChildInRenderTree(i);
        }
    }
}

void WaterFlowSWLayout::Init(const SizeF& frameSize)
{
    info_->footerIndex_ = 0;
    info_->childrenCount_ = wrapper_->GetTotalChildCount();

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    crossGap_ = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    mainSize_ = frameSize.MainSize(axis_);
    float crossSize = frameSize.CrossSize(axis_);
    std::pair<std::vector<double>, bool> cross;
    auto rowsTemplate = props->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = props->GetColumnsTemplate().value_or("1fr");
    if (axis_ == Axis::VERTICAL) {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGap_, info_->childrenCount_);
    } else {
        cross = ParseTemplateArgs(
            WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGap_, info_->childrenCount_);
    }
    if (cross.second) {
        crossGap_ = 0.0f;
    }

    if (info_->lanes_.empty()) {
        info_->lanes_.resize(cross.first.size());
    }
    for (const auto& len : cross.first) {
        itemCrossSize_.push_back(static_cast<float>(len));
    }
    if (itemCrossSize_.empty()) {
        itemCrossSize_.push_back(crossSize);
    }
}

void WaterFlowSWLayout::CheckReset()
{
    int32_t updateIdx = wrapper_->GetHostNode()->GetChildrenUpdated();
    if (updateIdx != -1) {
        if (updateIdx <= info_->endIndex_ && updateIdx >= info_->startIndex_) {
            info_->jumpIndex_ = info_->startIndex_;
        }
        wrapper_->GetHostNode()->ChildrenUpdatedFrom(-1);
    }
}

void WaterFlowSWLayout::MeasureOnOffset(float delta)
{
    ApplyDelta(delta);
    for (const auto& lane : info_->lanes_) {
        std::cout << "after APPLY delta lane = " << lane.ToString() << std::endl;
    }
    if (!overScroll_) {
        AdjustOverScroll();
    }
}

void WaterFlowSWLayout::ApplyDelta(float delta)
{
    std::cout << "offset = " << delta << std::endl;
    info_->totalOffset_ += delta;
    for (auto& lane : info_->lanes_) {
        lane.startPos += delta;
        lane.endPos += delta;
    }

    // clear out items outside viewport after position change
    if (Positive(delta)) {
        // positive offset is scrolling upwards
        FillFront(0.0f, info_->MinIdxInLanes() - 1, 0);
        ClearBack(mainSize_);
    } else {
        FillBack(mainSize_, info_->MaxIdxInLanes() + 1, info_->childrenCount_ - 1);
        ClearFront();
    }
}

void WaterFlowSWLayout::MeasureToTarget(int32_t targetIdx)
{
    std::cout << "measure to target " << targetIdx << " start = " << info_->startIndex_ << " end " << info_->endIndex_
              << std::endl;
    if (targetIdx < info_->startIndex_) {
        FillFront(-FLT_MAX, info_->startIndex_ - 1, targetIdx);
    } else if (targetIdx > info_->endIndex_) {
        FillBack(FLT_MAX, info_->endIndex_ + 1, targetIdx);
    }
}

// [lane start/end position, lane index]
using lanePos = std::pair<float, size_t>;

void WaterFlowSWLayout::FillBack(float viewportBound, int32_t idx, int32_t maxChildIdx)
{
    maxChildIdx = std::min(maxChildIdx, info_->childrenCount_ - 1);
    std::priority_queue<lanePos, std::vector<lanePos>, std::greater<>> q;
    for (size_t i = 0; i < info_->lanes_.size(); ++i) {
        std::cout << "Lane " << i << " = " << info_->lanes_[i].ToString() << std::endl;
        float endPos = info_->lanes_[i].endPos;
        if (LessNotEqual(endPos + mainGap_, viewportBound)) {
            q.push({ endPos, i });
        }
    }

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!q.empty() && idx <= maxChildIdx) {
        auto [endPos, laneIdx] = q.top();
        q.pop();
        float mainLen = MeasureChild(props, idx, laneIdx);
        endPos += mainLen + mainGap_;

        auto& lane = info_->lanes_[laneIdx];
        lane.endPos = endPos;
        info_->idxToLane_[idx] = laneIdx;
        lane.items_.push_back({ idx++, mainLen });
        if (LessNotEqual(endPos, viewportBound)) {
            q.push({ endPos, laneIdx });
        }
    }
}

namespace {
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
} // namespace

void WaterFlowSWLayout::FillFront(float viewportBound, int32_t idx, int32_t minChildIdx)
{
    minChildIdx = std::max(minChildIdx, 0);
    std::priority_queue<lanePos, std::vector<lanePos>, MaxHeapCmp> q;
    for (size_t i = 0; i < info_->lanes_.size(); ++i) {
        float startPos = info_->lanes_[i].startPos;
        if (GreatNotEqual(startPos - mainGap_, viewportBound)) {
            q.push({ startPos, i });
        }
    }

    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    while (!q.empty() && idx >= minChildIdx) {
        auto [startPos, laneIdx] = q.top();
        q.pop();
        float mainLen = MeasureChild(props, idx, laneIdx);
        startPos -= mainGap_ + mainLen;

        auto& lane = info_->lanes_[laneIdx];
        info_->idxToLane_[idx] = laneIdx;
        lane.startPos = startPos;
        lane.items_.push_front({ idx--, mainLen });
        if (GreatNotEqual(startPos - mainGap_, viewportBound)) {
            q.push({ startPos, laneIdx });
        }
    }
}

void WaterFlowSWLayout::ClearBack(float bound)
{
    for (auto& lane : info_->lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        float lastItemStartPos = lane.endPos - lane.items_.back().mainSize;
        while (GreatOrEqual(lastItemStartPos, bound)) {
            info_->idxToLane_.erase(lane.items_.back().idx);
            lane.items_.pop_back();
            lane.endPos = lastItemStartPos - mainGap_;
            if (lane.items_.empty()) {
                break;
            }
            lastItemStartPos -= mainGap_ + lane.items_.back().mainSize;
        }
    }
}

void WaterFlowSWLayout::ClearFront()
{
    for (auto& lane : info_->lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        float firstItemEndPos = lane.startPos + lane.items_.front().mainSize;
        while (NonPositive(firstItemEndPos)) {
            info_->idxToLane_.erase(lane.items_.front().idx);
            lane.items_.pop_front();
            lane.startPos = firstItemEndPos + mainGap_;
            if (lane.items_.empty()) {
                break;
            }
            firstItemEndPos += mainGap_ + lane.items_.front().mainSize;
        }
    }
}

ScrollAlign WaterFlowSWLayout::ParseAutoAlign(int32_t jumpIdx, bool inView)
{
    if (inView) {
        if (Negative(info_->DistanceToTop(jumpIdx, mainGap_))) {
            return ScrollAlign::START;
        }
        if (Negative(info_->DistanceToBottom(jumpIdx, mainSize_, mainGap_))) {
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

void WaterFlowSWLayout::MeasureOnJump(int32_t jumpIdx, ScrollAlign align)
{
    if (jumpIdx == -1) {
        jumpIdx = info_->childrenCount_ - 1;
    }

    bool inView = jumpIdx >= info_->startIndex_ && jumpIdx <= info_->endIndex_;
    if (align == ScrollAlign::AUTO) {
        align = ParseAutoAlign(jumpIdx, inView);
    }

    // if the item is within 1 full-viewport distance (approximately), we consider it close
    int32_t cntInView = info_->endIndex_ - info_->startIndex_ + 1;
    std::cout << "start " << info_->startIndex_ << " end = " << info_->endIndex_ << std::endl;
    bool closeToView =
        jumpIdx > info_->endIndex_ ? jumpIdx - info_->endIndex_ < cntInView : info_->startIndex_ - jumpIdx < cntInView;
    if (closeToView) {
        MeasureToTarget(jumpIdx);
    }
    switch (align) {
        case ScrollAlign::START: {
            if (inView || closeToView) {
                ApplyDelta(-info_->DistanceToTop(jumpIdx, mainGap_));
            } else {
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [](auto& lane) {
                    lane.items_.clear();
                    lane.startPos = 0.0f;
                    lane.endPos = 0.0f;
                });
                info_->totalOffset_ = 0;
                info_->idxToLane_.clear();
                FillBack(mainSize_, jumpIdx, info_->childrenCount_ - 1);
            }
            break;
        }
        case ScrollAlign::CENTER: {
            auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
            if (inView || closeToView) {
                std::cout << "jumpIdx = " << jumpIdx << " map size = " << info_->idxToLane_.size()
                          << " children size = " << info_->childrenCount_ << std::endl;
                float itemH = MeasureChild(props, jumpIdx, info_->idxToLane_.at(jumpIdx));
                ApplyDelta(-info_->DistanceToTop(jumpIdx, mainGap_) + (mainSize_ - itemH) / 2.0f);
            } else {
                float itemH = MeasureChild(props, jumpIdx, 0);
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [mainSize = mainSize_, itemH](auto& lane) {
                    lane.items_.clear();
                    lane.startPos = (mainSize - itemH) / 2.0f;
                    lane.endPos = (mainSize + itemH) / 2.0f;
                });
                info_->idxToLane_ = { { jumpIdx, 0 } };
                auto& lane = info_->lanes_[0];
                lane.items_.push_back({ jumpIdx, itemH });
                info_->totalOffset_ = 0;

                FillFront(0.0f, jumpIdx - 1, 0);
                FillBack(mainSize_, jumpIdx + 1, info_->childrenCount_ - 1);
            }
            break;
        }
        case ScrollAlign::END: {
            if (inView || closeToView) {
                std::cout << "jumpIdx = " << jumpIdx
                          << "dis to bot = " << info_->DistanceToBottom(jumpIdx, mainSize_, mainGap_) << std::endl;
                ApplyDelta(info_->DistanceToBottom(jumpIdx, mainSize_, mainGap_));
            } else {
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [mainSize = mainSize_](auto& lane) {
                    lane.items_.clear();
                    lane.startPos = mainSize;
                    lane.endPos = mainSize;
                });
                info_->totalOffset_ = 0;
                info_->idxToLane_.clear();
                FillFront(0.0f, jumpIdx, 0);
            }
            break;
        }
        default:
            break;
    }
}

void WaterFlowSWLayout::AdjustOverScroll()
{
    if (info_->lanes_.empty()) {
        return;
    }
    float maxEnd = info_->EndPos();
    float minStart = info_->StartPos();

    if (Positive(minStart)) {
        ApplyDelta(-minStart);
    } else if (LessNotEqual(maxEnd, mainSize_)) {
        bool reachedTop = info_->MinIdxInLanes() == 0 && NearZero(info_->DistanceToTop(0, mainGap_));
        if (reachedTop) {
            // no room to adjust
            return;
        }
        ApplyDelta(mainSize_ - maxEnd);
    }
}

float WaterFlowSWLayout::MeasureChild(const RefPtr<WaterFlowLayoutProperty>& props, int32_t idx, size_t lane)
{
    auto child = wrapper_->GetOrCreateChildByIndex(idx);
    CHECK_NULL_RETURN(child, 0.0f);
    child->Measure(
        WaterFlowLayoutUtils::CreateChildConstraint({ itemCrossSize_[lane], mainSize_, axis_ }, props, child));
    return child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
}
} // namespace OHOS::Ace::NG
