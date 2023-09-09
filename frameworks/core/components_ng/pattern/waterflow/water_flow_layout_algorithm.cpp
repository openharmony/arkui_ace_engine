/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_layout_algorithm.h"

#include "base/geometry/axis.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/grid/grid_utils.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
const std::string UNIT_AUTO = "auto";
std::string PreParseArgs(const std::string& args)
{
    if (args.empty() || args.find(UNIT_AUTO) == std::string::npos) {
        return args;
    }
    std::string rowsArgs;
    std::vector<std::string> strs;
    StringUtils::StringSplitter(args, ' ', strs);
    std::string current;
    size_t rowArgSize = strs.size();
    for (size_t i = 0; i < rowArgSize; ++i) {
        current = strs[i];
        // "auto" means 1fr in waterflow
        if (strs[i] == std::string(UNIT_AUTO)) {
            current = "1fr";
        }
        rowsArgs += ' ' + current;
    }
    return rowsArgs;
}
} // namespace

float WaterFlowLayoutAlgorithm::ComputeCrossPosition(int32_t crossIndex) const
{
    float position = 0.0f;
    for (int32_t index = 0; index < crossIndex; ++index) {
        if (index >= 0 && index < static_cast<int32_t>(itemsCrossSize_.size())) {
            position += itemsCrossSize_.at(index);
        }
    }
    position += crossIndex * crossGap_;
    return position;
}

void WaterFlowLayoutAlgorithm::InitialItemsCrossSize(
    const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const SizeF& frameSize, int32_t childrenCount)
{
    itemsCrossSize_.clear();
    auto rowsTemplate = layoutProperty->GetRowsTemplate().value_or("1fr");
    auto columnsTemplate = layoutProperty->GetColumnsTemplate().value_or("1fr");
    axis_ = layoutProperty->GetAxis();
    auto scale = layoutProperty->GetLayoutConstraint()->scaleProperty;
    auto rowsGap = ConvertToPx(layoutProperty->GetRowsGap().value_or(0.0_vp), scale, frameSize.Height()).value_or(0);
    auto columnsGap =
        ConvertToPx(layoutProperty->GetColumnsGap().value_or(0.0_vp), scale, frameSize.Width()).value_or(0);
    mainGap_ = axis_ == Axis::HORIZONTAL ? columnsGap : rowsGap;
    crossGap_ = axis_ == Axis::VERTICAL ? columnsGap : rowsGap;

    auto crossSize = frameSize.CrossSize(axis_);
    std::vector<double> crossLens;
    std::pair<std::vector<double>, bool> cross;
    if (axis_ == Axis::VERTICAL) {
        cross = ParseTemplateArgs(PreParseArgs(columnsTemplate), crossSize, crossGap_, childrenCount);
    } else {
        cross = ParseTemplateArgs(PreParseArgs(rowsTemplate), crossSize, crossGap_, childrenCount);
    }
    crossLens = cross.first;
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    if (cross.second) {
        crossGap_ = 0;
    }

    // cross count changed by auto-fill and cross size change
    if (!layoutInfo_.waterFlowItems_.empty() && crossLens.size() != layoutInfo_.waterFlowItems_.size()) {
        layoutInfo_.Reset();
        LOGI("cross count changed");
    }

    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_.try_emplace(index, len);
        itemsCrossPosition_.try_emplace(index, ComputeCrossPosition(index));
        layoutInfo_.waterFlowItems_.try_emplace(index, std::map<int32_t, std::pair<float, float>>());
        ++index;
    }
}

void WaterFlowLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);

    Axis axis = layoutProperty->GetAxis();
    auto idealSize =
        CreateIdealSize(layoutProperty->GetLayoutConstraint().value(), axis, layoutProperty->GetMeasureType(), true);
    auto matchChildren = GreatOrEqual(GetMainAxisSize(idealSize, axis), Infinity<float>());
    if (!matchChildren) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);

    if (layoutWrapper->GetHostNode()->GetChildrenUpdated() != -1) {
        layoutInfo_.Reset(layoutWrapper->GetHostNode()->GetChildrenUpdated());
        layoutWrapper->GetHostNode()->ChildrenUpdatedFrom(-1);
    }

    layoutInfo_.childrenCount_ = layoutWrapper->GetTotalChildCount();

    InitialItemsCrossSize(layoutProperty, idealSize, layoutWrapper->GetTotalChildCount());
    mainSize_ = GetMainAxisSize(idealSize, axis);
    if (layoutInfo_.jumpIndex_ >= 0 && layoutInfo_.jumpIndex_ < layoutWrapper->GetTotalChildCount()) {
        auto crossIndex = layoutInfo_.GetCrossIndex(layoutInfo_.jumpIndex_);
        if (crossIndex == -1) {
            // jump to out of cache
        } else {
            auto item = layoutInfo_.waterFlowItems_[crossIndex][layoutInfo_.jumpIndex_];
            // first line
            if (layoutInfo_.currentOffset_ + item.first < 0 &&
                layoutInfo_.currentOffset_ + item.first + item.second > 0) {
                layoutInfo_.currentOffset_ = -item.first;
            } else if (layoutInfo_.currentOffset_ + item.first < mainSize_ &&
                       layoutInfo_.currentOffset_ + item.first + item.second > mainSize_) {
                // last line
                layoutInfo_.currentOffset_ = mainSize_ - (item.first + item.second);
            } else if (layoutInfo_.currentOffset_ + item.first + item.second < 0 ||
                       layoutInfo_.currentOffset_ + item.first > mainSize_) {
                // out of viewport
                layoutInfo_.currentOffset_ = -item.first;
            }
            LOGI("scroll to index:%{public}d", layoutInfo_.jumpIndex_);
            layoutInfo_.jumpIndex_ = -1;
        }
    } else {
        layoutInfo_.jumpIndex_ = -1;
    }

    FillViewport(mainSize_, layoutWrapper);
    if (matchChildren) {
        mainSize_ = layoutInfo_.GetMaxMainHeight() + footerMainSize_;
        idealSize.SetMainSize(mainSize_, axis_);
        AddPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
    layoutInfo_.lastMainSize_ = mainSize_;
}

void WaterFlowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    layoutWrapper->RemoveAllChildInRenderTree();

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto childFrameOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    for (const auto& mainPositions : layoutInfo_.waterFlowItems_) {
        for (const auto& item : mainPositions.second) {
            if (item.first < layoutInfo_.startIndex_ || item.first > layoutInfo_.endIndex_) {
                continue;
            }

            auto currentOffset = childFrameOffset;
            auto crossOffset = itemsCrossPosition_.at(mainPositions.first);
            auto mainOffset = item.second.first + layoutInfo_.currentOffset_;
            if (layoutProperty->IsReverse()) {
                mainOffset = mainSize_ - item.second.second - mainOffset;
            }
            if (axis_ == Axis::VERTICAL) {
                currentOffset += OffsetF(crossOffset, mainOffset);
            } else {
                currentOffset += OffsetF(mainOffset, crossOffset);
            }
            auto wrapper = layoutWrapper->GetOrCreateChildByIndex(GetChildIndexWithFooter(item.first));
            if (!wrapper) {
                LOGE("Layout item wrapper of index: %{public}d is null, please check.", item.first);
                continue;
            }
            wrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
            wrapper->Layout();
        }
    }
    if (layoutInfo_.itemEnd_ && layoutInfo_.footerIndex_ >= 0) {
        auto footer = layoutWrapper->GetOrCreateChildByIndex(layoutInfo_.footerIndex_);
        auto footerOffset = childFrameOffset;
        auto mainOffset = layoutInfo_.GetMaxMainHeight() + layoutInfo_.currentOffset_;
        if (layoutProperty->IsReverse()) {
            mainOffset = mainSize_ - footerMainSize_ - mainOffset;
        }
        footerOffset += (axis_ == Axis::VERTICAL) ? OffsetF(0, mainOffset) : OffsetF(mainOffset, 0);
        footer->GetGeometryNode()->SetMarginFrameOffset(footerOffset);
        footer->Layout();
    }
}

LayoutConstraintF WaterFlowLayoutAlgorithm::CreateChildConstraint(int32_t crossIndex,
    const RefPtr<WaterFlowLayoutProperty>& layoutProperty, const RefPtr<LayoutWrapper>& childLayoutWrapper)
{
    auto itemConstraint = layoutProperty->CreateChildConstraint();
    if (itemsCrossSize_.find(crossIndex) == itemsCrossSize_.end()) {
        LOGE("crossIndex:%{public}d", crossIndex);
        return itemConstraint;
    }
    auto itemMainSize = mainSize_;
    auto itemCrossSize = itemsCrossSize_.at(crossIndex);
    auto itemIdealSize =
        axis_ == Axis::VERTICAL ? SizeF(itemCrossSize, itemMainSize) : SizeF(itemMainSize, itemCrossSize);

    itemConstraint.maxSize = itemIdealSize;
    itemConstraint.percentReference = itemIdealSize;

    CHECK_NULL_RETURN(layoutProperty->HasItemLayoutConstraint(), itemConstraint);

    OptionalSizeF childMinSize;
    OptionalSizeF childMaxSize;
    auto itemMinSize = layoutProperty->GetItemMinSize();
    if (itemMinSize.has_value()) {
        childMinSize = ConvertToOptionalSize(
            itemMinSize.value(), layoutProperty->GetLayoutConstraint()->scaleProperty, itemIdealSize);
    }
    auto itemMaxSize = layoutProperty->GetItemMaxSize();
    if (itemMaxSize.has_value()) {
        childMaxSize = ConvertToOptionalSize(
            itemMaxSize.value(), layoutProperty->GetLayoutConstraint()->scaleProperty, itemIdealSize);
    }

    if (childMaxSize.AtLeastOneValid()) {
        itemConstraint.maxSize.UpdateSizeWhenSmaller(childMaxSize.ConvertToSizeT());
    }
    if (childMinSize.AtLeastOneValid()) {
        itemConstraint.minSize.UpdateSizeWhenLarger(childMinSize.ConvertToSizeT());
    }

    CHECK_NULL_RETURN(childLayoutWrapper, itemConstraint);
    auto childLayoutProperty = childLayoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(childLayoutProperty, itemConstraint);
    auto&& childCalcLayoutConstraint = childLayoutProperty->GetCalcLayoutConstraint();
    if (childCalcLayoutConstraint) {
        if (childCalcLayoutConstraint->maxSize.has_value()) {
            itemConstraint.UpdateMaxSizeWithCheck(ConvertToSize(childCalcLayoutConstraint->maxSize.value(),
                itemConstraint.scaleProperty, itemConstraint.percentReference));
        }
        if (childCalcLayoutConstraint->minSize.has_value()) {
            itemConstraint.UpdateMinSizeWithCheck(ConvertToSize(childCalcLayoutConstraint->minSize.value(),
                itemConstraint.scaleProperty, itemConstraint.percentReference));
        }
    }

    childLayoutProperty->UpdateCalcMaxSize(CalcSize(CalcLength(itemConstraint.maxSize.Width(), DimensionUnit::PX),
        CalcLength(itemConstraint.maxSize.Height(), DimensionUnit::PX)));
    childLayoutProperty->UpdateCalcMinSize(CalcSize(CalcLength(itemConstraint.minSize.Width(), DimensionUnit::PX),
        CalcLength(itemConstraint.minSize.Height(), DimensionUnit::PX)));

    return itemConstraint;
}

FlowItemPosition WaterFlowLayoutAlgorithm::GetItemPosition(int32_t index)
{
    auto crossIndex = layoutInfo_.GetCrossIndex(index);
    // already in layoutInfo
    if (crossIndex != -1) {
        return { crossIndex, layoutInfo_.GetStartMainPos(crossIndex, index) };
    }
    auto itemIndex = layoutInfo_.GetCrossIndexForNextItem();
    if (itemIndex.lastItemIndex < 0) {
        return { itemIndex.crossIndex, 0.0f };
    }
    auto mainHeight = layoutInfo_.GetMainHeight(itemIndex.crossIndex, itemIndex.lastItemIndex);
    return { itemIndex.crossIndex, mainHeight + mainGap_ };
}

void WaterFlowLayoutAlgorithm::FillViewport(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (layoutInfo_.currentOffset_ >= 0) {
        layoutInfo_.currentOffset_ = 0;
        layoutInfo_.itemStart_ = true;
    } else {
        layoutInfo_.itemStart_ = false;
    }

    layoutInfo_.UpdateStartIndex();
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto currentIndex = layoutInfo_.startIndex_;
    auto position = GetItemPosition(currentIndex);
    while (LessNotEqual(position.startMainPos + layoutInfo_.currentOffset_, mainSize) || layoutInfo_.jumpIndex_ >= 0) {
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(GetChildIndexWithFooter(currentIndex));
        if (!itemWrapper) {
            break;
        }
        itemWrapper->Measure(CreateChildConstraint(position.crossIndex, layoutProperty, itemWrapper));
        auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
        auto itemHeight = GetMainAxisSize(itemSize, axis_);
        auto item = layoutInfo_.waterFlowItems_[position.crossIndex].find(currentIndex);
        if (item == layoutInfo_.waterFlowItems_[position.crossIndex].end()) {
            layoutInfo_.waterFlowItems_[position.crossIndex][currentIndex] =
                std::make_pair(position.startMainPos, itemHeight);
        } else {
            if (item->second.second != itemHeight) {
                item->second.second = itemHeight;
                layoutInfo_.ClearCacheAfterIndex(currentIndex);
                LOGI("item size changed");
            }
        }
        if (layoutInfo_.jumpIndex_ == currentIndex) {
            layoutInfo_.currentOffset_ = -(layoutInfo_.waterFlowItems_[position.crossIndex][currentIndex].first);
            layoutInfo_.jumpIndex_ = -1;
        }
        currentIndex++;
        position = GetItemPosition(currentIndex);
    }
    layoutInfo_.endIndex_ = currentIndex - 1;

    layoutInfo_.itemEnd_ = GetChildIndexWithFooter(currentIndex) == layoutWrapper->GetTotalChildCount();
    if (layoutInfo_.itemEnd_) {
        ModifyCurrentOffsetWhenReachEnd(mainSize, layoutWrapper);
    } else {
        layoutInfo_.offsetEnd_ = false;
    }
}

void WaterFlowLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper)
{
    auto maxItemHeight = layoutInfo_.GetMaxMainHeight();
    if (layoutInfo_.footerIndex_ >= 0) {
        footerMainSize_ = MeasuerFooter(layoutWrapper);
        maxItemHeight += footerMainSize_;
    }
    layoutInfo_.maxHeight_ = maxItemHeight;

    if (mainSize >= maxItemHeight) {
        layoutInfo_.currentOffset_ = 0;
        layoutInfo_.offsetEnd_ = true;
        layoutInfo_.itemStart_ = true;
        return;
    }

    if (layoutInfo_.currentOffset_ + maxItemHeight <= mainSize) {
        layoutInfo_.offsetEnd_ = true;
        layoutInfo_.currentOffset_ = mainSize - maxItemHeight;
        auto oldStart = layoutInfo_.startIndex_;
        layoutInfo_.UpdateStartIndex();
        // lazyforeach
        LOGD("oldStart:%{public}d, newStart:%{public}d", oldStart, layoutInfo_.startIndex_);
        for (auto i = oldStart; i >= layoutInfo_.startIndex_; i--) {
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(GetChildIndexWithFooter(i));
            auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
            itemWrapper->Measure(CreateChildConstraint(layoutInfo_.GetCrossIndex(i), layoutProperty, itemWrapper));
        }
    } else {
        layoutInfo_.offsetEnd_ = false;
    }
}

float WaterFlowLayoutAlgorithm::MeasuerFooter(LayoutWrapper* layoutWrapper)
{
    auto footer = layoutWrapper->GetOrCreateChildByIndex(layoutInfo_.footerIndex_);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    auto footerConstraint = layoutProperty->CreateChildConstraint();
    footer->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    footer->Measure(footerConstraint);
    auto itemSize = footer->GetGeometryNode()->GetMarginFrameSize();
    return GetMainAxisSize(itemSize, axis_);
}
} // namespace OHOS::Ace::NG
