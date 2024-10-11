/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_algorithm.h"

#include "core/components_ng/pattern/waterflow/layout/water_flow_layout_utils.h"
#include "core/components_ng/property/templates_parser.h"

namespace OHOS::Ace::NG {
namespace {
const std::string UNIT_AUTO = "auto";
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
    itemsCrossPosition_.clear();
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
    std::pair<std::vector<double>, double> cross;
    if (axis_ == Axis::VERTICAL) {
        cross =
            ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(columnsTemplate), crossSize, crossGap_, childrenCount);
    } else {
        cross =
            ParseTemplateArgs(WaterFlowLayoutUtils::PreParseArgs(rowsTemplate), crossSize, crossGap_, childrenCount);
    }
    crossLens = cross.first;
    if (crossLens.empty()) {
        crossLens.push_back(crossSize);
    }
    crossGap_ = cross.second;

    // cross count changed by auto-fill and cross size change
    if (!layoutInfo_->items_[0].empty() && crossLens.size() != layoutInfo_->items_[0].size()) {
        layoutInfo_->Reset();
    }

    int32_t index = 0;
    for (const auto& len : crossLens) {
        itemsCrossSize_.try_emplace(index, len);
        itemsCrossPosition_.try_emplace(index, ComputeCrossPosition(index));
        layoutInfo_->items_[0].try_emplace(index, std::map<int32_t, std::pair<float, float>>());
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
    if (NearZero(GetCrossAxisSize(idealSize, axis))) {
        TAG_LOGI(AceLogTag::ACE_WATERFLOW, "cross size is 0, skip measure");
        skipMeasure_ = true;
        return;
    }
    auto matchChildren = GreaterOrEqualToInfinity(GetMainAxisSize(idealSize, axis));
    if (!matchChildren) {
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
    MinusPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);

    int32_t updateIdx = GetUpdateIdx(layoutWrapper, layoutInfo_->footerIndex_);
    if (updateIdx != -1) {
        layoutInfo_->Reset(updateIdx);
        layoutWrapper->GetHostNode()->ChildrenUpdatedFrom(-1);
    }

    layoutInfo_->childrenCount_ = layoutWrapper->GetTotalChildCount();

    InitialItemsCrossSize(layoutProperty, idealSize, layoutInfo_->childrenCount_);
    mainSize_ = GetMainAxisSize(idealSize, axis);
    if (layoutInfo_->jumpIndex_ >= 0 && layoutInfo_->jumpIndex_ < layoutInfo_->childrenCount_) {
        auto crossIndex = layoutInfo_->GetCrossIndex(layoutInfo_->jumpIndex_);
        if (crossIndex == -1) {
            // jump to out of cache
        } else {
            layoutInfo_->JumpTo(layoutInfo_->items_[0][crossIndex][layoutInfo_->jumpIndex_]);
        }
    } else {
        layoutInfo_->jumpIndex_ = EMPTY_JUMP_INDEX;
    }

    FillViewport(mainSize_, layoutWrapper);
    if (layoutInfo_->targetIndex_.has_value()) {
        MeasureToTarget(layoutWrapper, layoutInfo_->endIndex_, std::nullopt);
    }
    if (matchChildren) {
        mainSize_ = layoutInfo_->GetMaxMainHeight() + footerMainSize_;
        idealSize.SetMainSize(mainSize_, axis_);
        AddPaddingToSize(layoutProperty->CreatePaddingAndBorder(), idealSize);
        layoutWrapper->GetGeometryNode()->SetFrameSize(idealSize);
    }
    layoutInfo_->lastMainSize_ = mainSize_;

    layoutWrapper->SetCacheCount(layoutProperty->GetCachedCountValue(1));
}

bool WaterFlowLayoutAlgorithm::MeasureToTarget(
    LayoutWrapper* layoutWrapper, int32_t startFrom, std::optional<int64_t> cacheDeadline)
{
    if (layoutInfo_->targetIndex_.value() > layoutInfo_->childrenCount_) {
        layoutInfo_->targetIndex_.reset();
        return false;
    }
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    int32_t currentIndex = startFrom;
    auto position = GetItemPosition(currentIndex);
    if (layoutInfo_->targetIndex_.value() == LAST_ITEM) {
        layoutInfo_->targetIndex_ = layoutInfo_->childrenCount_ - 1;
    }
    while (layoutInfo_->targetIndex_.has_value() && (startFrom < layoutInfo_->targetIndex_.value())) {
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(
            GetChildIndexWithFooter(currentIndex), !cacheDeadline, cacheDeadline.has_value());
        if (!itemWrapper) {
            layoutInfo_->targetIndex_.reset();
            return false;
        }
        auto itemCrossSize = itemsCrossSize_.find(position.crossIndex);
        if (itemCrossSize == itemsCrossSize_.end()) {
            return false;
        }
        itemWrapper->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
            { itemCrossSize->second, mainSize_, axis_ }, layoutProperty, itemWrapper));
        if (cacheDeadline) {
            itemWrapper->Layout();
            itemWrapper->SetActive(false);
        }
        auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
        auto itemHeight = GetMainAxisSize(itemSize, axis_);
        auto item = layoutInfo_->items_[0][position.crossIndex].find(currentIndex);
        if (item == layoutInfo_->items_[0][position.crossIndex].end()) {
            layoutInfo_->items_[0][position.crossIndex][currentIndex] =
                std::make_pair(position.startMainPos, itemHeight);
        } else {
            if (item->second.second != itemHeight) {
                item->second.second = itemHeight;
                layoutInfo_->ClearCacheAfterIndex(currentIndex);
                TAG_LOGD(AceLogTag::ACE_WATERFLOW, "item size changed");
            }
        }
        if (layoutInfo_->targetIndex_.value() == currentIndex) {
            layoutInfo_->targetIndex_.reset();
        }
        currentIndex++;
        position = GetItemPosition(currentIndex);
        if (cacheDeadline && GetSysTimestamp() > *cacheDeadline) {
            break;
        }
    }
    return true;
}

void WaterFlowLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (skipMeasure_) {
        skipMeasure_ = false;
        return;
    }
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    const int32_t cachedCount = layoutProperty->GetCachedCountValue(1);

    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto childFrameOffset = OffsetF(padding.left.value_or(0.0f), padding.top.value_or(0.0f));
    layoutInfo_->UpdateStartIndex();
    auto firstIndex = layoutInfo_->endIndex_;
    auto crossSize = size.CrossSize(axis_);
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    const bool isRtl = layoutDirection == TextDirection::RTL && axis_ == Axis::VERTICAL;
    for (const auto& mainPositions : layoutInfo_->items_[0]) {
        for (const auto& item : mainPositions.second) {
            if (item.first < layoutInfo_->startIndex_ - cachedCount ||
                item.first > layoutInfo_->endIndex_ + cachedCount) {
                continue;
            }
            auto itemCrossPosition = itemsCrossPosition_.find(mainPositions.first);
            if (itemCrossPosition == itemsCrossPosition_.end()) {
                return;
            }
            auto currentOffset = childFrameOffset;
            auto crossOffset = itemCrossPosition->second;
            auto mainOffset = item.second.first + layoutInfo_->currentOffset_;
            if (isRtl) {
                crossOffset = crossSize - crossOffset - itemsCrossSize_.at(mainPositions.first);
            }
            if (layoutProperty->IsReverse()) {
                mainOffset = mainSize_ - item.second.second - mainOffset;
            }
            if (axis_ == Axis::VERTICAL) {
                currentOffset += OffsetF(crossOffset, mainOffset);
            } else {
                currentOffset += OffsetF(mainOffset, crossOffset);
            }
            const bool isCache = item.first < layoutInfo_->startIndex_ || item.first > layoutInfo_->endIndex_;
            auto wrapper = layoutWrapper->GetChildByIndex(GetChildIndexWithFooter(item.first), isCache);
            if (!wrapper) {
                continue;
            }
            wrapper->GetGeometryNode()->SetMarginFrameOffset(currentOffset);
            wrapper->Layout();
            // recode restore info
            if (item.first == layoutInfo_->startIndex_) {
                layoutInfo_->storedOffset_ = mainOffset;
            }

            if (!isCache && NonNegative(mainOffset + item.second.second)) {
                firstIndex = std::min(firstIndex, item.first);
            }
            auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
            if (frameNode) {
                frameNode->MarkAndCheckNewOpIncNode();
            }
        }
    }
    layoutInfo_->firstIndex_ = firstIndex;
    layoutWrapper->SetActiveChildRange(layoutInfo_->NodeIdx(layoutInfo_->FirstIdx()),
        layoutInfo_->NodeIdx(layoutInfo_->endIndex_), cachedCount, cachedCount,
        layoutProperty->GetShowCachedItemsValue(false));
    PreloadItems(layoutWrapper, layoutInfo_, cachedCount);

    LayoutFooter(layoutWrapper, childFrameOffset, layoutProperty->IsReverse());
}

void WaterFlowLayoutAlgorithm::LayoutFooter(LayoutWrapper* layoutWrapper, const OffsetF& childFrameOffset, bool reverse)
{
    if (layoutInfo_->footerIndex_ < 0) {
        return;
    }
    if (layoutInfo_->itemEnd_) {
        auto footer = layoutWrapper->GetOrCreateChildByIndex(layoutInfo_->footerIndex_);
        CHECK_NULL_VOID(footer);
        auto footerOffset = childFrameOffset;
        auto mainOffset = layoutInfo_->GetMaxMainHeight() + layoutInfo_->currentOffset_;
        if (reverse) {
            mainOffset = mainSize_ - footerMainSize_ - mainOffset;
        }
        footerOffset += (axis_ == Axis::VERTICAL) ? OffsetF(0, mainOffset) : OffsetF(mainOffset, 0);
        footer->GetGeometryNode()->SetMarginFrameOffset(footerOffset);
        footer->Layout();
    } else {
        auto footer = layoutWrapper->GetChildByIndex(layoutInfo_->footerIndex_);
        CHECK_NULL_VOID(footer);
        footer->SetActive(false);
    }
}

FlowItemPosition WaterFlowLayoutAlgorithm::GetItemPosition(int32_t index)
{
    auto crossIndex = layoutInfo_->GetCrossIndex(index);
    // already in layoutInfo
    if (crossIndex != -1) {
        return { crossIndex, layoutInfo_->GetStartMainPos(crossIndex, index) };
    }
    auto itemIndex = layoutInfo_->GetCrossIndexForNextItem(layoutInfo_->GetSegment(index));
    if (itemIndex.lastItemIndex < 0) {
        return { itemIndex.crossIndex, 0.0f };
    }
    auto mainHeight = layoutInfo_->GetMainHeight(itemIndex.crossIndex, itemIndex.lastItemIndex);
    return { itemIndex.crossIndex, mainHeight + mainGap_ };
}

void WaterFlowLayoutAlgorithm::FillViewport(float mainSize, LayoutWrapper* layoutWrapper)
{
    if (layoutInfo_->currentOffset_ >= 0) {
        if (!canOverScroll_) {
            layoutInfo_->currentOffset_ = 0;
        }
        layoutInfo_->itemStart_ = true;
    } else {
        layoutInfo_->itemStart_ = false;
    }

    layoutInfo_->UpdateStartIndex();
    auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
    auto currentIndex = layoutInfo_->startIndex_;
    auto position = GetItemPosition(currentIndex);
    bool fill = false;
    while (
        LessNotEqual(position.startMainPos + layoutInfo_->currentOffset_, mainSize) || layoutInfo_->jumpIndex_ >= 0) {
        auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(GetChildIndexWithFooter(currentIndex));
        if (!itemWrapper) {
            break;
        }
        auto itemCrossSize = itemsCrossSize_.find(position.crossIndex);
        if (itemCrossSize == itemsCrossSize_.end()) {
            break;
        }
        itemWrapper->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
            { itemCrossSize->second, mainSize_, axis_ }, layoutProperty, itemWrapper));
        auto itemSize = itemWrapper->GetGeometryNode()->GetMarginFrameSize();
        auto itemHeight = GetMainAxisSize(itemSize, axis_);
        auto item = layoutInfo_->items_[0][position.crossIndex].find(currentIndex);
        if (item == layoutInfo_->items_[0][position.crossIndex].end()) {
            layoutInfo_->items_[0][position.crossIndex][currentIndex] =
                std::make_pair(position.startMainPos, itemHeight);
        } else {
            if (item->second.second != itemHeight) {
                TAG_LOGI(AceLogTag::ACE_WATERFLOW,
                    "item size change. currentIdx:%{public}d,cacheHeight:%{public}f,itemHeight:%{public}f",
                    currentIndex, item->second.second, itemHeight);
                item->second.second = itemHeight;
                layoutInfo_->ClearCacheAfterIndex(currentIndex);
            }
        }
        if (layoutInfo_->jumpIndex_ == currentIndex) {
            layoutInfo_->currentOffset_ =
                layoutInfo_->JumpToTargetAlign(layoutInfo_->items_[0][position.crossIndex][currentIndex]);
            layoutInfo_->currentOffset_ += layoutInfo_->restoreOffset_;
            // restoreOffSet only be used once
            layoutInfo_->restoreOffset_ = 0.0f;
            layoutInfo_->align_ = ScrollAlign::START;
            layoutInfo_->jumpIndex_ = EMPTY_JUMP_INDEX;
            layoutInfo_->itemStart_ = false;
            if (layoutInfo_->extraOffset_.has_value()) {
                layoutInfo_->currentOffset_ += layoutInfo_->extraOffset_.value();
                layoutInfo_->extraOffset_.reset();
            }
        }
        position = GetItemPosition(++currentIndex);
        fill = true;
    }
    layoutInfo_->endIndex_ = !fill ? currentIndex : currentIndex - 1;

    layoutInfo_->itemEnd_ = GetChildIndexWithFooter(currentIndex) == layoutInfo_->childrenCount_;
    if (layoutInfo_->itemEnd_) {
        ModifyCurrentOffsetWhenReachEnd(mainSize, layoutWrapper);
    } else {
        layoutInfo_->offsetEnd_ = false;
    }
}

void WaterFlowLayoutAlgorithm::ModifyCurrentOffsetWhenReachEnd(float mainSize, LayoutWrapper* layoutWrapper)
{
    auto maxItemHeight = layoutInfo_->GetMaxMainHeight();
    if (layoutInfo_->footerIndex_ >= 0) {
        footerMainStartPos_ = maxItemHeight;
        footerMainSize_ = WaterFlowLayoutUtils::MeasureFooter(layoutWrapper, axis_);
        maxItemHeight += footerMainSize_;
        if (layoutInfo_->jumpIndex_ != EMPTY_JUMP_INDEX) {
            if (layoutInfo_->extraOffset_.has_value() && Negative(layoutInfo_->extraOffset_.value())) {
                layoutInfo_->extraOffset_.reset();
            }
            layoutInfo_->itemStart_ = false;
            layoutInfo_->JumpTo({ footerMainStartPos_, footerMainSize_ });
        }
    }
    layoutInfo_->maxHeight_ = maxItemHeight;

    if (mainSize >= maxItemHeight) {
        if (!canOverScroll_) {
            layoutInfo_->currentOffset_ = 0;
        }
        layoutInfo_->itemStart_ = GreatOrEqual(layoutInfo_->currentOffset_, 0.0f);
        layoutInfo_->offsetEnd_ = LessOrEqual(layoutInfo_->currentOffset_, 0.0f);
        return;
    }

    if (LessOrEqual(layoutInfo_->currentOffset_ + maxItemHeight, mainSize)) {
        layoutInfo_->offsetEnd_ = true;
        if (!canOverScroll_) {
            layoutInfo_->currentOffset_ = mainSize - maxItemHeight;
        }

        auto oldStart = layoutInfo_->startIndex_;
        layoutInfo_->UpdateStartIndex();
        // lazyforeach
        for (auto i = oldStart; i >= layoutInfo_->startIndex_; i--) {
            auto itemWrapper = layoutWrapper->GetOrCreateChildByIndex(GetChildIndexWithFooter(i));
            CHECK_NULL_VOID(itemWrapper);
            auto layoutProperty = AceType::DynamicCast<WaterFlowLayoutProperty>(layoutWrapper->GetLayoutProperty());
            float crossSize = itemsCrossSize_.at(layoutInfo_->GetCrossIndex(i));
            itemWrapper->Measure(WaterFlowLayoutUtils::CreateChildConstraint(
                { crossSize, mainSize_, axis_ }, layoutProperty, itemWrapper));
        }
    } else {
        layoutInfo_->offsetEnd_ = false;
    }
}

bool WaterFlowLayoutAlgorithm::AppendCacheItem(LayoutWrapper* host, int32_t itemIdx, int64_t deadline)
{
    const int32_t lastItem = layoutInfo_->GetLastItem();
    if (itemIdx <= lastItem) {
        return host->GetOrCreateChildByIndex(itemIdx, false, true);
    }
    const auto sub = layoutInfo_->targetIndex_;
    layoutInfo_->targetIndex_ = itemIdx;
    const bool res = MeasureToTarget(host, lastItem, deadline);
    layoutInfo_->targetIndex_ = sub;
    return res;
}
} // namespace OHOS::Ace::NG
