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

#include "core/components_ng/pattern/waterflow/water_flow_segmented_layout.h"

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
void WaterFlowSegmentedLayout::Measure(LayoutWrapper* wrapper)
{
    wrapper_ = wrapper;
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper->GetLayoutProperty());
    axis_ = props->GetAxis();
    auto [idealSize, matchChildren] = PreMeasureSelf();

    info_.childrenCount_ = wrapper_->GetTotalChildCount();

    Init(idealSize);
    mainSize_ = GetMainAxisSize(idealSize, axis_);

    // independent reset / jump procedure

    // independent offset (scrolling) procedure
    bool forward = info_.currentOffset_ - info_.prevOffset_ <= 0.0f;
    if (forward) {
        Fill();
    }

    info_.startIndex_ = info_.FastSolveStartIndex();
    info_.endIndex_ = info_.FastSolveEndIndex(mainSize_);

    info_.itemStart_ = GreatOrEqual(info_.currentOffset_, 0.0f);
    info_.itemEnd_ = info_.endIndex_ == info_.childrenCount_ - 1;
    info_.offsetEnd_ = info_.itemEnd_ && mainSize_ - info_.currentOffset_ >= info_.endPosArray_.back().first;

    if (matchChildren) {
        PostMeasureSelf(idealSize);
    }
    info_.lastMainSize_ = mainSize_;

    wrapper_->SetCacheCount(props->GetCachedCountValue(1));
}

void WaterFlowSegmentedLayout::Layout(LayoutWrapper* wrapper)
{
    wrapper_ = wrapper;

    wrapper_->RemoveAllChildInRenderTree();

    auto size = wrapper_->GetGeometryNode()->GetFrameSize();
    auto padding = wrapper_->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto initialOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    info_.UpdateStartIndex();
    int32_t firstSegment = info_.GetSegment(info_.startIndex_);
    int32_t lastSegment = info_.GetSegment(info_.endIndex_);
    for (int32_t seg = firstSegment; seg <= lastSegment; ++seg) {
        LayoutSegment(seg, initialOffset, props->IsReverse());
    }
}

void WaterFlowSegmentedLayout::Init(const SizeF& frameSize)
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());
    itemsCrossSize_.clear();
    auto rowsTemplate = props->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = props->GetColumnsTemplate().value_or("1fr");
    axis_ = props->GetAxis();
    auto scale = props->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(props->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(props->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap;
    crossGap_ = axis_ == Axis::VERTICAL ? columnsGap : rowsGap;

    // parse crossSize for different segments
    
//     auto crossSize = frameSize.CrossSize(axis_);
//     std::vector<double> crossLens;
//     std::pair<std::vector<double>, bool> cross;
//     if (axis_ == Axis::VERTICAL) {
//         cross = ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGap_, childrenCount);
//     } else {
//         cross = ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGap_, childrenCount);
//     }
//     crossLens = cross.first;
//     if (crossLens.empty()) {
//         crossLens.push_back(crossSize);
//     }
//     if (cross.second) {
//         crossGap_ = 0;
//     }

//     // cross count changed by auto-fill and cross size change
//     if (!info_.items_[0].empty() && crossLens.size() != info_.items_[0].size()) {
//         info_.Reset();
//     }

//     int32_t index = 0;
//     // for (const auto& len : crossLens) {
//     //     itemsCrossSize_.try_emplace(index, len);
//     //     itemsCrossPosition_.try_emplace(index, ComputeCrossPosition(index));
//     //     info_.items_[0].try_emplace(index, std::map<int32_t, std::pair<float, float>>());
//     //     ++index;
//     // }
}

void WaterFlowSegmentedLayout::Fill()
{
    auto props = DynamicCast<WaterFlowLayoutProperty>(wrapper_->GetLayoutProperty());

    int32_t idx = ++info_.endIndex_;
    int32_t segment = info_.GetSegment(idx);
    auto position = WaterFlowLayoutUtils::GetItemPosition(info_, idx, mainGap_);
    while (LessNotEqual(position.startMainPos + info_.currentOffset_, mainSize_)) {
        auto itemWrapper = wrapper_->GetOrCreateChildByIndex(idx);
        if (!itemWrapper) {
            break;
        }
        itemWrapper->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
            { itemsCrossSize_[segment][position.crossIndex], mainSize_, axis_ }, props, itemWrapper));

        auto itemHeight = GetMainAxisSize(itemWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        info_.items_[segment][position.crossIndex][idx] = { position.startMainPos, itemHeight };
        info_.AddItemToCache(idx, position.startMainPos, itemHeight);

        // prepare next item
        segment = info_.GetSegment(++idx);
        position = WaterFlowLayoutUtils::GetItemPosition(info_, idx, mainGap_);
    }
}

std::pair<SizeF, bool> WaterFlowSegmentedLayout::PreMeasureSelf()
{
    auto props = wrapper_->GetLayoutProperty();
    auto size = CreateIdealSize(props->GetLayoutConstraint().value(), axis_, props->GetMeasureType(), true);
    auto matchChildren = GreaterOrEqualToInfinity(GetMainAxisSize(size, axis_));
    if (!matchChildren) {
        wrapper_->GetGeometryNode()->SetFrameSize(size);
    }
    MinusPaddingToSize(props->CreatePaddingAndBorder(), size);
    wrapper_->GetGeometryNode()->SetContentSize(size);
    return { size, matchChildren };
}

void WaterFlowSegmentedLayout::PostMeasureSelf(SizeF size)
{
    mainSize_ = info_.GetMaxMainHeight();
    size.SetMainSize(mainSize_, axis_);
    auto props = wrapper_->GetLayoutProperty();
    AddPaddingToSize(props->CreatePaddingAndBorder(), size);
    wrapper_->GetGeometryNode()->SetFrameSize(size);
}

void WaterFlowSegmentedLayout::LayoutSegment(int32_t segment, const OffsetF& padding, bool isReverse)
{
    for (const auto& mainPositions : info_.items_[segment]) {
        for (const auto& item : mainPositions.second) {
            if (item.first < info_.startIndex_ || item.first > info_.endIndex_) {
                continue;
            }

            auto crossOffset = itemsCrossPosition_[segment][mainPositions.first];
            auto mainOffset = item.second.first + info_.currentOffset_;
            if (isReverse) {
                mainOffset = mainSize_ - item.second.second - mainOffset;
            }

            OffsetF offset =
                (axis_ == Axis::VERTICAL) ? OffsetF(crossOffset, mainOffset) : OffsetF(mainOffset, crossOffset);
            auto wrapper = wrapper_->GetOrCreateChildByIndex(item.first);
            wrapper->GetGeometryNode()->SetMarginFrameOffset(offset + padding);
            wrapper->Layout();

            // recode restore info
            if (item.first == info_.startIndex_) {
                info_.storedOffset_ = mainOffset;
            }
        }
    }
}
} // namespace OHOS::Ace::NG
