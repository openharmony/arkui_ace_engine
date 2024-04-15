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
#include "core/components_ng/pattern/waterflow/sliding_window/water_flow_sw_layout.h"

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

    float mainSize = idealSize.MainSize(axis_);
    if (info_->jumpIndex_ != EMPTY_JUMP_INDEX) {
        MeasureOnJump(info_->jumpIndex_, info_->align_, mainSize);
    } else if (info_->targetIndex_) {
        MeasureToTarget(*info_->targetIndex_);
    } else {
        ApplyOffset(mainSize, info_->delta_);
        if (!overScroll_) {
            AdjustOverScroll(mainSize);
        }
    }
    wrapper->SetCacheCount(props->GetCachedCountValue(1));
}

void WaterFlowSWLayout::Layout(LayoutWrapper* wrapper)
{
    wrapper->RemoveAllChildInRenderTree();
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
}

void WaterFlowSWLayout::Init(const SizeF& frameSize)
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap = ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = { axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap };
    crossGap_ = { axis_ == Axis::VERTICAL ? columnsGap : rowsGap };

    auto crossSize = frameSize.CrossSize(axis_);
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

    for (const auto& len : cross.first) {
        itemCrossSize_.push_back(static_cast<float>(len));
    }
    if (itemCrossSize_.empty()) {
        itemCrossSize_.push_back(crossSize);
    }
}

void WaterFlowSWLayout::ApplyOffset(float mainSize, float offset)
{
    for (auto& lane : info_->lanes_) {
        lane.startPos += offset;
        lane.endPos += offset;
    }

    // clear out items outside viewport after position change
    if (Positive(offset)) {
        // positive offset is scrolling upwards
        ClearBack(mainSize);
        FillFront(0.0f, 0);
    } else {
        ClearFront();
        FillBack(mainSize, info_->childrenCount_ - 1);
    }

    info_->SyncRange();
}

void WaterFlowSWLayout::MeasureToTarget(int32_t targetIdx)
{
    if (targetIdx < info_->startIndex_) {
        FillFront(-FLT_MAX, targetIdx);
    } else if (targetIdx > info_->endIndex_) {
        FillBack(FLT_MAX, targetIdx);
    }
}

using lanePos = std::pair<float, int32_t>;

void WaterFlowSWLayout::FillBack(float viewportBound, int32_t maxChildIdx)
{
    maxChildIdx = std::min(maxChildIdx, info_->childrenCount_ - 1);
    std::priority_queue<lanePos> q;
    for (size_t i = 0; i < info_->lanes_.size(); ++i) {
        float endPos = info_->lanes_[i].endPos;
        if (LessNotEqual(endPos + mainGap_, viewportBound)) {
            q.push({ endPos, i });
        }
    }

    int32_t idx = info_->endIndex_ + 1;

    while (!q.empty() && idx <= maxChildIdx) {
        auto [endPos, laneIdx] = q.top();
        q.pop();
        auto child = MeasureChild(idx);

        float size = child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
        endPos += mainGap_ + size;

        auto& lane = info_->lanes_[laneIdx];
        lane.endPos = endPos;
        info_->idxToLane_[idx] = laneIdx;
        lane.items_.push_back({ idx++, size });
        if (LessNotEqual(endPos, viewportBound)) {
            q.push({ endPos, laneIdx });
        }
    }
}

void WaterFlowSWLayout::FillFront(float viewportBound, int32_t minChildIdx)
{
    minChildIdx = std::max(minChildIdx, 0);
    std::priority_queue<lanePos, std::vector<lanePos>, std::greater<>> q;
    for (size_t i = 0; i < info_->lanes_.size(); ++i) {
        float startPos = info_->lanes_[i].startPos;
        if (GreatNotEqual(startPos - mainGap_, viewportBound)) {
            q.push({ startPos, i });
        }
    }

    int32_t idx = info_->startIndex_ - 1;

    while (!q.empty() && idx >= minChildIdx) {
        auto [startPos, laneIdx] = q.top();
        q.pop();
        auto child = MeasureChild(idx);

        float size = child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
        startPos -= mainGap_ + size;

        auto& lane = info_->lanes_[laneIdx];
        info_->idxToLane_[idx] = laneIdx;
        lane.startPos = startPos;
        lane.items_.push_front({ idx--, size });
        if (GreatNotEqual(startPos - mainGap_, viewportBound)) {
            q.push({ startPos, laneIdx });
        }
    }
}

void WaterFlowSWLayout::ClearBack(float mainSize)
{
    for (auto& lane : info_->lanes_) {
        if (lane.items_.empty()) {
            continue;
        }
        float lastItemStartPos = lane.endPos - lane.items_.back().mainSize;
        while (GreatNotEqual(lastItemStartPos, mainSize)) {
            lane.items_.pop_back();
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
        while (Negative(firstItemEndPos)) {
            lane.items_.pop_front();
            if (lane.items_.empty()) {
                break;
            }
            firstItemEndPos += mainGap_ + lane.items_.front().mainSize;
        }
    }
}

ScrollAlign WaterFlowSWLayout::ParseAutoAlign(int32_t jumpIdx, float mainSize, bool inView)
{
    if (inView) {
        if (Negative(info_->DistanceToTop(jumpIdx, mainGap_))) {
            return ScrollAlign::START;
        }
        if (Negative(info_->DistanceToBottom(jumpIdx, mainSize, mainGap_))) {
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

void WaterFlowSWLayout::MeasureOnJump(int32_t jumpIdx, ScrollAlign align, float mainSize)
{
    if (jumpIdx == -1) {
        jumpIdx = info_->childrenCount_ - 1;
    }

    bool inView = jumpIdx >= info_->startIndex_ && jumpIdx <= info_->endIndex_;
    if (align == ScrollAlign::AUTO) {
        align = ParseAutoAlign(jumpIdx, mainSize, inView);
    }

    // if the item is within 1 full-viewport distance (approximately), we consider it close
    int32_t cntInView = info_->endIndex_ - info_->startIndex_ + 1;
    bool closeToView =
        jumpIdx > info_->endIndex_ ? jumpIdx - info_->endIndex_ < cntInView : info_->startIndex_ - jumpIdx < cntInView;
    if (closeToView) {
        MeasureToTarget(jumpIdx);
    }
    switch (align) {
        case ScrollAlign::START: {
            if (inView || closeToView) {
                ApplyOffset(mainSize, -info_->DistanceToTop(jumpIdx, mainGap_));
            } else {
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [](auto& it) {
                    it->items_.clear();
                    it->startPos = 0.0f;
                    it->endPos = 0.0f;
                });
                info_->idxToLane_.clear();
                info_->endIndex_ = jumpIdx - 1;
                FillBack(mainSize, info_->childrenCount_ - 1);
            }
            break;
        }
        case ScrollAlign::CENTER: {
            auto child = MeasureChild(jumpIdx);
            float itemH = child->GetGeometryNode()->GetMarginFrameSize().MainSize(info_->axis_);
            if (inView || closeToView) {
                ApplyOffset(mainSize, -info_->DistanceToTop(jumpIdx, mainGap_) + (mainSize - itemH) / 2.0f);
            } else {
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [mainSize, itemH](auto& it) {
                    it->items_.clear();
                    it->startPos = (mainSize - itemH) / 2.0f;
                    it->endPos = (mainSize + itemH) / 2.0f;
                });
                auto& lane = info_->lanes_[0];
                lane.items_.push_back({ jumpIdx, itemH });
                info_->startIndex_ = info_->endIndex_ = jumpIdx;

                FillFront(0.0f, 0);
                FillBack(mainSize, info_->childrenCount_ - 1);
            }
            break;
        }
        case ScrollAlign::END: {
            if (inView || closeToView) {
                ApplyOffset(mainSize, info_->DistanceToBottom(jumpIdx, mainSize, mainGap_));
            } else {
                std::for_each(info_->lanes_.begin(), info_->lanes_.end(), [mainSize](auto& it) {
                    it->items_.clear();
                    it->startPos = mainSize;
                    it->endPos = mainSize;
                });
                info_->idxToLane_.clear();
                info_->startIndex_ = jumpIdx + 1;
                FillFront(0.0f, 0);
            }
            break;
        }
        default:
            break;
    }
    info_->SyncRange();
    AdjustOverScroll(mainSize);
}

void WaterFlowSWLayout::AdjustOverScroll(float mainSize)
{
    if (info_->lanes_.empty()) {
        return;
    }
    auto minStart = std::min_element(info_->lanes_.begin(), info_->lanes_.end(),
        [](const auto& a, const auto& b) { return LessNotEqual(a.startPos, b.startPos); });
    auto maxEnd = std::max_element(info_->lanes_.begin(), info_->lanes_.end(),
        [](const auto& a, const auto& b) { return LessNotEqual(a.endPos, b.endPos); });

    if (Positive(minStart->startPos)) {
        ApplyOffset(mainSize, -minStart->startPos);
    } else if (LessNotEqual(maxEnd->endPos, mainSize)) {
        ApplyOffset(mainSize, mainSize - maxEnd->endPos);
    }
}
} // namespace OHOS::Ace::NG