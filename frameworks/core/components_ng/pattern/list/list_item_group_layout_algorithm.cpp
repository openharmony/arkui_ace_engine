/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/log/event_report.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"

#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t GRID_COUNTS_12 = 12;

uint32_t GetMaxGridCounts(int32_t currentColumns)
{
    auto maxGridCounts = GRID_COUNTS_8;
    switch (currentColumns) {
        case GRID_COUNTS_4:
            maxGridCounts = GRID_COUNTS_4;
            break;
        case GRID_COUNTS_8:
            maxGridCounts = GRID_COUNTS_6;
            break;
        case GRID_COUNTS_12:
            maxGridCounts = GRID_COUNTS_8;
            break;
        default:
            break;
    }
    return maxGridCounts;
}
} // namespace

void ListItemGroupLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto totalChildCount = layoutWrapper->GetTotalChildCount();
    totalItemCount_ = totalChildCount - itemStartIndex_ - footerCount_;
    footerIndex_ = (footerCount_ > 0) ? (totalChildCount - footerCount_) : -1;
    CHECK_NULL_VOID(listLayoutProperty_);
    auto layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    axis_ = listLayoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    layoutDirection_ = listLayoutProperty_->GetNonAutoLayoutDirection();
    isStackFromEnd_ = listLayoutProperty_->GetStackFromEnd().value_or(false);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    paddingBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    paddingAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));
    auto listItemGroupLayoutProperty =
        AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(listItemGroupLayoutProperty);
    auto layoutPolicy = listItemGroupLayoutProperty->GetLayoutPolicyProperty();
    auto isCrossWrap =
        layoutPolicy.has_value() && ((axis_ == Axis::VERTICAL && layoutPolicy.value().IsWidthWrap()) ||
                                        (axis_ == Axis::HORIZONTAL && layoutPolicy.value().IsHeightWrap()));
    auto isCrossFix =
        layoutPolicy.has_value() && ((axis_ == Axis::VERTICAL && layoutPolicy.value().IsWidthFix()) ||
                                        (axis_ == Axis::HORIZONTAL && layoutPolicy.value().IsHeightFix()));

    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis_);
    auto space = layoutProperty->GetSpace().value_or(Dimension(0));

    auto layoutConstraint = layoutProperty->GetLayoutConstraint().value();
    CalculateLanes(listLayoutProperty_, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
    childLayoutConstraint_ = layoutProperty->CreateChildConstraint();
    isCardStyle_ = IsCardStyleForListItemGroup(layoutWrapper);
    if (isCardStyle_) {
        UpdateListItemGroupMaxWidth(contentConstraint.parentIdealSize, layoutProperty, contentIdealSize);
        listLayoutProperty_->UpdateListItemAlign(V2::ListItemAlign::CENTER);
    }
    UpdateListItemConstraint(contentIdealSize, childLayoutConstraint_);
    referencePos_ = UpdateReferencePos(layoutProperty, forwardLayout_, referencePos_);
    totalMainSize_ = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
    if (Negative(spaceWidth_) || GreatOrEqual(spaceWidth_, endPos_ - startPos_)) {
        spaceWidth_ = 0.0f;
    }
    if (layoutProperty->GetDivider().has_value()) {
        auto divider = layoutProperty->GetDivider().value();
        std::optional<float> dividerSpace = divider.strokeWidth.ConvertToPx();
        if (GreatOrEqual(dividerSpace.value(), endPos_ - startPos_)) {
            dividerSpace.reset();
        }
        if (dividerSpace.has_value()) {
            spaceWidth_ = std::max(spaceWidth_, dividerSpace.value());
        }
    }
    if (IsRoundingMode(layoutWrapper)) {
        spaceWidth_ = Round(spaceWidth_);
    }
    MeasureHeaderFooter(layoutWrapper);
    totalMainSize_ = std::max(totalMainSize_, headerMainSize_ + footerMainSize_);
    if (isStackFromEnd_) {
        std::swap(headerMainSize_, footerMainSize_);
    }
    if (childrenSize_) {
        posMap_->UpdateGroupPosMap(totalItemCount_, GetLanes(), spaceWidth_, childrenSize_,
            headerMainSize_, footerMainSize_);
        totalMainSize_ = posMap_->GetTotalHeight();
    }

    if (isLayouted_) {
        ReverseItemPosition(cachedItemPosition_, prevTotalItemCount_, prevTotalMainSize_);
        ReverseItemPosition(itemPosition_, prevTotalItemCount_, prevTotalMainSize_);
        ReverseLayoutedItemInfo(prevTotalItemCount_, prevTotalMainSize_);
    }

    if (cacheParam_) {
        MeasureCacheItem(layoutWrapper);
    } else {
        MeasureListItem(layoutWrapper, childLayoutConstraint_);
        UpdateCachedItemPosition(listLayoutProperty_->GetCachedCountWithDefault() * lanes_);
    }

    if (childrenSize_) {
        AdjustByPosMap();
    } else {
        AdjustItemPosition();
        UpdateLayoutedItemInfo();
    }

    ReverseLayoutedItemInfo(totalItemCount_, totalMainSize_);
    auto crossSize = contentIdealSize.CrossSize(axis_);
    if ((crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) || isCrossFix) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(layoutWrapper, axis_), axis_);
    } else if (isCrossWrap) {
        contentIdealSize.SetCrossSize(
            std::min(GetChildMaxCrossSize(layoutWrapper, axis_), crossSize.value_or(0.0f)), axis_);
    }
    contentIdealSize.SetMainSize(totalMainSize_, axis_);
    AddPaddingToSize(padding, contentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());
    layoutWrapper->SetCacheCount(listLayoutProperty_->GetCachedCountWithDefault() * lanes_);
    isLayouted_ = false;
}

void ListItemGroupLayoutAlgorithm::UpdateCachedItemPosition(int32_t cacheCount)
{
    if (!itemPosition_.empty()) {
        auto iter = cachedItemPosition_.begin();
        while (iter != cachedItemPosition_.end()) {
            if ((iter->first >= GetStartIndex() && iter->first <= GetEndIndex()) ||
                iter->first < (GetStartIndex() - cacheCount) || iter->first > (GetEndIndex() + cacheCount)) {
                iter = cachedItemPosition_.erase(iter);
            } else {
                iter++;
            }
        }
    }
}

void ListItemGroupLayoutAlgorithm::UpdateListItemGroupMaxWidth(
    const OptionalSizeF& parentIdealSize, RefPtr<LayoutProperty> layoutProperty, OptionalSizeF& contentIdealSize)
{
    RefPtr<GridColumnInfo> columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::LIST_CARD);
    CHECK_NULL_VOID(columnInfo);
    auto columnParent = columnInfo->GetParent();
    CHECK_NULL_VOID(columnParent);
    columnParent->BuildColumnWidth();
    auto maxGridWidth = static_cast<float>(columnInfo->GetWidth(GetMaxGridCounts(columnParent->GetColumns())));
    float paddingWidth = layoutProperty->CreatePaddingAndBorder().Width();
    auto parentWidth = parentIdealSize.CrossSize(axis_).value() + paddingWidth;
    auto maxWidth = std::min(parentWidth, maxGridWidth);
    if (LessNotEqual(maxGridWidth, paddingWidth)) {
        TAG_LOGI(AceLogTag::ACE_LIST,
            "ListItemGroup reset to parentWidth since grid_col width:%{public}f, border:%{public}f",
            maxGridWidth, paddingWidth);
        maxWidth = parentWidth;
    }
    contentIdealSize.SetCrossSize(maxWidth - paddingWidth, axis_);
}

void ListItemGroupLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis_);
    CHECK_NULL_VOID(listLayoutProperty_);
    itemAlign_ = listLayoutProperty_->GetListItemAlign().value_or(V2::ListItemAlign::START);
    bool show = listLayoutProperty_->GetShowCachedItemsValue(false);
    layoutProperty->UpdateListLanes(listLayoutProperty_->GetLanes(),
        listLayoutProperty_->GetLaneMinLength(), listLayoutProperty_->GetLaneMaxLength());

    if (cacheParam_) {
        LayoutCacheItem(layoutWrapper, paddingOffset, crossSize, show);
        CheckUpdateGroupAndItemPos(layoutWrapper, paddingOffset, crossSize);
    } else {
        LayoutListItem(layoutWrapper, paddingOffset, crossSize);
        ResetLayoutItem(layoutWrapper);
    }
    ReverseItemPosition(cachedItemPosition_, totalItemCount_, totalMainSize_);
    ReverseItemPosition(itemPosition_, totalItemCount_, totalMainSize_);
    if (isStackFromEnd_) {
        std::swap(headerMainSize_, footerMainSize_);
    }
    SetActiveChildRange(layoutWrapper, listLayoutProperty_->GetCachedCountWithDefault(), show);
    if (headerIndex_ >= 0 || footerIndex_ >= 0) {
        if (layoutDirection_ == TextDirection::RTL && axis_ == Axis::HORIZONTAL) {
            LayoutHeaderFooterRTL(layoutWrapper, paddingOffset, crossSize);
        } else {
            LayoutHeaderFooterLTR(layoutWrapper, paddingOffset, crossSize);
        }
    }
    isLayouted_ = true;
}

void ListItemGroupLayoutAlgorithm::CheckUpdateGroupAndItemPos(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    if (childrenSize_ || (NearZero(adjustReferenceDelta_) && NearZero(adjustTotalSize_))) {
        return;
    }
    auto offset = layoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    if (axis_ == Axis::VERTICAL) {
        offset = isStackFromEnd_ ? offset - OffsetF(0.0f, adjustTotalSize_ + adjustReferenceDelta_) :
                                   offset + OffsetF(0.0f, adjustReferenceDelta_);
    } else {
        if (layoutDirection_ == TextDirection::RTL) {
            offset = isStackFromEnd_ ? offset + OffsetF(adjustReferenceDelta_, 0.0f) :
                                       offset - OffsetF(adjustTotalSize_ + adjustReferenceDelta_, 0.0f);
        } else {
            offset = isStackFromEnd_ ?  offset - OffsetF(adjustTotalSize_ + adjustReferenceDelta_, 0.0f) :
                                        offset + OffsetF(adjustReferenceDelta_, 0.0f);
        }
    }
    layoutWrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    LayoutListItem(layoutWrapper, paddingOffset, crossSize);
}

void ListItemGroupLayoutAlgorithm::SyncGeometry(RefPtr<LayoutWrapper>& wrapper)
{
    CHECK_NULL_VOID(wrapper);
    auto host = wrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    host->ForceSyncGeometryNode();
    host->ResetLayoutAlgorithm();
}

bool ListItemGroupLayoutAlgorithm::CheckNeedMeasure(const RefPtr<LayoutWrapper>& layoutWrapper) const
{
    if (layoutWrapper->CheckNeedForceMeasureAndLayout()) {
        return true;
    }
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, true);
    auto constraint = geometryNode->GetParentLayoutConstraint();
    CHECK_NULL_RETURN(constraint, true);
    return constraint.value() != childLayoutConstraint_;
}

void ListItemGroupLayoutAlgorithm::MeasureHeaderFooter(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    auto headerFooterLayoutConstraint = layoutProperty->CreateChildConstraint();
    headerFooterLayoutConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);
    RefPtr<LayoutWrapper> headerWrapper = headerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(headerIndex_) : nullptr;
    RefPtr<LayoutWrapper> footerWrapper = footerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(footerIndex_) : nullptr;
    if (headerWrapper) {
        headerWrapper->Measure(headerFooterLayoutConstraint);
        headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    if (footerWrapper) {
        footerWrapper->Measure(headerFooterLayoutConstraint);
        footerMainSize_ = GetMainAxisSize(footerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
}

void ListItemGroupLayoutAlgorithm::SetActiveChildRange(LayoutWrapper* layoutWrapper, int32_t cacheCount, bool show)
{
    if (measureInNextFrame_) {
        return;
    }
    if (!itemPosition_.empty()) {
        auto start = itemStartIndex_ + itemPosition_.begin()->first;
        auto end = itemStartIndex_ + itemPosition_.rbegin()->first;
        int32_t cachedCountForward = cachedItemPosition_.empty() ? 0 :
            std::max(itemStartIndex_ + cachedItemPosition_.rbegin()->first - end, 0);
        int32_t cachedCountBackward = cachedItemPosition_.empty() ? 0 :
            std::max(start - itemStartIndex_ - cachedItemPosition_.begin()->first, 0);
        layoutWrapper->SetActiveChildRange(start, end, cachedCountBackward, cachedCountForward, show);
        return;
    } else if (show && !cachedItemPosition_.empty()) {
        int32_t start = cachedItemPosition_.begin()->first;
        int32_t end = cachedItemPosition_.rbegin()->first;
        int32_t count = end - start + 1;
        if (start == 0) {
            layoutWrapper->SetActiveChildRange(-1, itemStartIndex_ - 1, 0, count, show);
        } else if (end == totalItemCount_ - 1) {
            int32_t endLimit = end + itemStartIndex_ + 1;
            layoutWrapper->SetActiveChildRange(endLimit, endLimit, count, 0, show);
        }
        return;
    }
    auto listPadding = listLayoutProperty_->CreatePaddingAndBorder().Offset();
    auto offset = layoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    if (LessNotEqual(GetMainAxisOffset(offset, axis_), GetMainAxisOffset(listPadding, axis_))) {
        int32_t index = totalItemCount_ + itemStartIndex_;
        layoutWrapper->SetActiveChildRange(index, index, cacheCount * lanes_, 0);
    } else {
        layoutWrapper->SetActiveChildRange(-1, itemStartIndex_ - 1, 0, cacheCount * lanes_);
    }
}

void ListItemGroupLayoutAlgorithm::UpdateListItemConstraint(const OptionalSizeF& selfIdealSize,
    LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    contentConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);
    auto crossSizeOptional = selfIdealSize.CrossSize(axis_);
    if (crossSizeOptional.has_value()) {
        float crossSize = crossSizeOptional.value();
        if (lanes_ > 1) {
            crossSize = (crossSize + laneGutter_) / lanes_ - laneGutter_;
            crossSize = crossSize <= 0 ? 1 : crossSize;
        }
        if (maxLaneLength_.has_value() && maxLaneLength_.value() < crossSize) {
            crossSize = maxLaneLength_.value();
        }
        contentConstraint.percentReference.SetCrossSize(crossSize, axis_);
        contentConstraint.parentIdealSize.SetCrossSize(crossSize, axis_);
        contentConstraint.maxSize.SetCrossSize(crossSize, axis_);
        if (minLaneLength_.has_value()) {
            contentConstraint.minSize.SetCrossSize(minLaneLength_.value(), axis_);
        }
    }
}

float ListItemGroupLayoutAlgorithm::GetChildMaxCrossSize(LayoutWrapper* layoutWrapper, Axis axis)
{
    float maxCrossSize = 0.0f;
    for (const auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first, false);
        if (!wrapper) {
            continue;
        }
        auto getGeometryNode = wrapper->GetGeometryNode();
        if (!getGeometryNode) {
            continue;
        }
        maxCrossSize = std::max(maxCrossSize, getGeometryNode->GetMarginFrameSize().CrossSize(axis));
    }
    for (const auto& pos : cachedItemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first, false);
        if (!wrapper) {
            continue;
        }
        auto getGeometryNode = wrapper->GetGeometryNode();
        if (!getGeometryNode) {
            continue;
        }
        maxCrossSize = std::max(maxCrossSize, getGeometryNode->GetMarginFrameSize().CrossSize(axis));
    }
    return maxCrossSize;
}

float ListItemGroupLayoutAlgorithm::UpdateReferencePos(
    RefPtr<LayoutProperty> layoutProperty, bool forwardLayout, float referencePos)
{
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    const auto& margin = layoutProperty->CreateMargin();
    auto offsetBeforeContent = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    auto offsetAfterContent = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    offsetBeforeContent += axis_ == Axis::HORIZONTAL ? margin.left.value_or(0) : margin.top.value_or(0);
    offsetAfterContent += axis_ == Axis::HORIZONTAL ? margin.right.value_or(0) : margin.bottom.value_or(0);
    forwardLayout ? referencePos += offsetBeforeContent : referencePos -= offsetAfterContent;
    return referencePos;
}

bool ListItemGroupLayoutAlgorithm::NeedMeasureItem(LayoutWrapper* layoutWrapper)
{
    auto contentMainSize = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    if (NearZero(contentMainSize)) {
        return true;
    }
    bool layoutedEntirely = layoutedItemInfo_ && layoutedItemInfo_.value().startIndex <= 0 &&
        layoutedItemInfo_.value().endIndex >= totalItemCount_ - 1;
    if (forwardLayout_) {
        if (childrenSize_ && needAdjustRefPos_) {
            referencePos_ -= (totalMainSize_ - posMap_->GetPrevTotalHeight());
            refPos_ -= (totalMainSize_ - posMap_->GetPrevTotalHeight());
        }
        if (GreatNotEqual(headerMainSize_, endPos_ - referencePos_)) {
            return false;
        }
        if (LessNotEqual(totalMainSize_ - footerMainSize_, startPos_ - referencePos_)) {
            auto listPadding = listLayoutProperty_->CreatePaddingAndBorder().Offset();
            auto offset = layoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
            bool belowList = GreatOrEqual(GetMainAxisOffset(offset, axis_), GetMainAxisOffset(listPadding, axis_));
            if (belowList && totalItemCount_ > 0 && !layoutedEntirely) {
                return true;
            }
            return false;
        }
    } else {
        if (childrenSize_ && needAdjustRefPos_) {
            referencePos_ += (totalMainSize_ - posMap_->GetPrevTotalHeight());
            refPos_ += (totalMainSize_ - posMap_->GetPrevTotalHeight());
        }
        if (GreatNotEqual(headerMainSize_, endPos_ - (referencePos_ - totalMainSize_))) {
            auto listPadding = GetMainAxisOffset(listLayoutProperty_->CreatePaddingAndBorder().Offset(), axis_);
            auto offset = GetMainAxisOffset(layoutWrapper->GetGeometryNode()->GetMarginFrameOffset(), axis_);
            auto groupBottom = offset + totalMainSize_;
            auto aboveList = LessOrEqual(groupBottom, listPadding);
            if (aboveList && totalItemCount_ > 0 && !layoutedEntirely) {
                return true;
            }
            return false;
        }
        if (LessNotEqual(totalMainSize_ - footerMainSize_, startPos_ - (referencePos_ - totalMainSize_))) {
            return false;
        }
    }
    return true;
}

void ListItemGroupLayoutAlgorithm::LayoutListItemAll(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, float startPos)
{
    int32_t currentIndex = -1;
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    while (currentIndex < totalItemCount_) {
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(layoutWrapper, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::ClearItemPosition()
{
    itemPosition_.clear();
    cachedItemPosition_.clear();
    layoutedItemInfo_.reset();
    forwardCachedIndex_ = -1;
    backwardCachedIndex_ = INT_MAX;
}

void ListItemGroupLayoutAlgorithm::CheckNeedAllLayout(const RefPtr<LayoutWrapper>& layoutWrapper, bool forwardLayout)
{
    if (itemPosition_.empty()) {
        needAllLayout_ = true;
        return;
    }
    int32_t totalItemCount = layoutWrapper->GetTotalChildCount() - itemStartIndex_ - footerCount_;
    if (!(forwardLayout && itemPosition_.rbegin()->first == totalItemCount - 1) &&
        !(!forwardLayout && itemPosition_.begin()->first == 0)) {
        needAllLayout_ = true;
    }
}

void ListItemGroupLayoutAlgorithm::MeasureListItem(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    if (totalItemCount_ <= 0) {
        if (LessNotEqual(totalMainSize_ - footerMainSize_, startPos_ - referencePos_)) {
            adjustReferenceDelta_ = totalMainSize_ - (headerMainSize_ + footerMainSize_);
        }
        totalMainSize_ = headerMainSize_ + footerMainSize_;
        itemPosition_.clear();
        cachedItemPosition_.clear();
        layoutedItemInfo_.reset();
        return;
    }
    int32_t startIndex = 0;
    int32_t endIndex = totalItemCount_ - 1;
    float startPos = headerMainSize_;
    float endPos = totalMainSize_ - footerMainSize_;
    prevStartPos_ = startPos_;
    prevEndPos_ = endPos_;
    if (needAllLayout_) {
        needAllLayout_ = false;
        itemPosition_.clear();
        cachedItemPosition_.clear();
        LayoutListItemAll(layoutWrapper, layoutConstraint, startPos);
        return;
    }
    if (targetIndex_) {
        startPos_ = -Infinity<float>();
        endPos_ = Infinity<float>();
        targetIndex_ = isStackFromEnd_ ? totalItemCount_ - targetIndex_.value() - 1 : targetIndex_.value();
    }
    if (jumpIndex_.has_value()) {
        if (jumpIndex_.value() == LAST_ITEM) {
            jumpIndex_ = totalItemCount_ - 1;
        }
        auto jumpIndex = isStackFromEnd_ ? totalItemCount_ - jumpIndex_.value() - 1 : jumpIndex_.value();
        if (jumpIndex < 0 || jumpIndex >= totalItemCount_) {
            jumpIndex = 0;
        }
        if (scrollAlign_ == ScrollAlign::CENTER || scrollAlign_ == ScrollAlign::START ||
            scrollAlign_ == ScrollAlign::AUTO) {
            startIndex = jumpIndex;
        } else if (scrollAlign_ == ScrollAlign::END) {
            endIndex = jumpIndex;
        } else if (forwardLayout_) {
            startIndex = jumpIndex;
        } else {
            endIndex = jumpIndex;
        }
        itemPosition_.clear();
        cachedItemPosition_.clear();
        jumpIndex_.reset();
        layoutedItemInfo_.reset();
    } else if (!itemPosition_.empty()) {
        if (itemPosition_.begin()->first > 0 || (forwardLayout_ && Negative(referencePos_))) {
            startPos = itemPosition_.begin()->second.startPos;
        }
        startIndex = GetStartIndex();
        if (startIndex >= totalItemCount_) {
            startIndex = totalItemCount_ - 1;
            if (itemPosition_.begin()->first > 0) {
                startPos = ((startPos - headerMainSize_) / GetLanesFloor(itemPosition_.begin()->first)) *
                               GetLanesFloor(startIndex) + headerMainSize_;
            }
        }
        if (!isNeedMeasureFormLastItem_) {
            endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
            endPos = itemPosition_.rbegin()->second.endPos;
        }
        if (forwardLayout_) {
            ModifyReferencePos(GetLanesFloor(startIndex), startPos);
        } else {
            ModifyReferencePos(GetLanesCeil(endIndex), endPos);
        }
        itemPosition_.clear();
    } else if (!NeedMeasureItem(layoutWrapper)) {
        itemPosition_.clear();
        return;
    }
    if (scrollAlign_ == ScrollAlign::CENTER) {
        startIndex = GetLanesFloor(startIndex);
        MeasureCenter(layoutWrapper, layoutConstraint, startIndex);
    } else if (scrollAlign_ == ScrollAlign::START) {
        startIndex = GetLanesFloor(startIndex);
        MeasureStart(layoutWrapper, layoutConstraint, startIndex);
    } else if (scrollAlign_ == ScrollAlign::END) {
        endIndex = GetLanesCeil(endIndex);
        MeasureEnd(layoutWrapper, layoutConstraint, endIndex);
    } else if (jumpIndex_.has_value() && scrollAlign_ == ScrollAlign::AUTO) {
        startIndex = GetLanesFloor(startIndex);
        MeasureAuto(layoutWrapper, layoutConstraint, startIndex);
    } else if (forwardLayout_) {
        startIndex = GetLanesFloor(startIndex);
        if (!CheckJumpForwardForBigOffset(startIndex, startPos)) {
            startPos = childrenSize_ ? posMap_->GetPos(startIndex) : startPos;
            MeasureForward(layoutWrapper, layoutConstraint, startIndex, startPos);
        }
    } else {
        endIndex = GetLanesCeil(endIndex);
        if (!CheckJumpBackwardForBigOffset(endIndex, endPos)) {
            endPos = childrenSize_ ? posMap_->GetPos(endIndex) + posMap_->GetRowHeight(endIndex) : endPos;
            MeasureBackward(layoutWrapper, layoutConstraint, endIndex, endPos);
        }
    }
}

std::pair<float, float> ListItemGroupLayoutAlgorithm::GetItemGroupPosition(int32_t index)
{
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    index = isStackFromEnd_ ? totalItemCount_ - index - 1 : index;
    if (scrollAlign_ == ScrollAlign::CENTER) {
        auto pos = itemPosition_.find(index);
        if (pos != itemPosition_.end()) {
            float refPos = (pos->second.endPos + pos->second.startPos) / 2 + paddingBeforeContent_; // 2:average
            float delta = (startPos_ + endPos_) / 2 - refPos;
            return { delta, totalMainSize_ + paddingBeforeContent_ + paddingAfterContent_ + delta };
        }
    } else if (scrollAlign_ == ScrollAlign::START) {
        auto pos = itemPosition_.find(index);
        if (pos != itemPosition_.end()) {
            float top = startPos_ + contentStartOffset_;
            if (sticky == V2::StickyStyle::HEADER || sticky == V2::StickyStyle::BOTH) {
                top += headerMainSize_;
            }
            float refPos = pos->second.startPos + paddingBeforeContent_;
            float delta = top - refPos;
            return { delta, totalMainSize_ + paddingBeforeContent_ + paddingAfterContent_ + delta };
        }
    } else if (scrollAlign_ == ScrollAlign::END) {
        auto pos = itemPosition_.find(index);
        if (pos != itemPosition_.end()) {
            float bottom = endPos_ - contentEndOffset_;
            if (sticky == V2::StickyStyle::FOOTER || sticky == V2::StickyStyle::BOTH) {
                bottom -= footerMainSize_;
            }
            float refPos = pos->second.endPos + paddingBeforeContent_;
            float delta = bottom - refPos;
            return { delta, totalMainSize_ + paddingBeforeContent_ + paddingAfterContent_ + delta };
        }
    }
    return { 0.0f, 0.0f };
}

float ListItemGroupLayoutAlgorithm::GetItemHeight(int32_t index)
{
    auto it = itemPosition_.find(index);
    if (it != itemPosition_.end()) {
        return it->second.endPos - it->second.startPos;
    }
    return 0.0f;
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineAuto(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t currentIndex)
{
    auto wrapper = GetListItem(layoutWrapper, currentIndex);
    if (!wrapper) {
        ReportGetChildError("MeasureALineAuto", currentIndex);
        return 0;
    }
    if (CheckNeedMeasure(wrapper)) {
        ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
        wrapper->Measure(layoutConstraint);
    }
    float mainLen = GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    int32_t id = wrapper->GetHostNode()->GetId();
    itemPosition_[currentIndex] = { id, 0.0f, mainLen };
    return 1;
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineCenter(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t currentIndex)
{
    float mainLen = 0;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex + cnt < totalItemCount_; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex + cnt);
        if (!wrapper) {
            ReportGetChildError("MeasureALineCenter", currentIndex + cnt);
            break;
        }
        if (CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex + cnt);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
        cnt++;
    }
    if (cnt > 0) {
        auto startPos = (startPos_ + endPos_ - mainLen) / 2; // 2:average
        auto endPos = startPos + mainLen; // 2:average
        for (int32_t i = 0; i < cnt; i++) {
            auto wrapper = GetListItem(layoutWrapper, currentIndex + i);
            int32_t id = wrapper->GetHostNode()->GetId();
            itemPosition_[currentIndex + i] = { id, startPos, endPos };
        }
    }
    return cnt;
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    if (currentIndex + 1 >= totalItemCount_) {
        return cnt;
    }
    for (int32_t i = 0; i < lanes && currentIndex + 1 <= totalItemCount_ - 1; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
        if (!wrapper) {
            ReportGetChildError("MeasureALineForward", currentIndex + 1);
            break;
        }
        cnt++;
        ++currentIndex;
        if (CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
    }
    if (cnt > 0) {
        endPos = startPos + mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            auto wrapper = GetListItem(layoutWrapper, currentIndex - i);
            int32_t id = wrapper->GetHostNode()->GetId();
            itemPosition_[currentIndex - i] = { id, startPos, endPos };
        }
    }
    return cnt;
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float endPos, float& startPos)
{
    float mainLen = 0.0f;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex - 1 >= 0; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex - 1);
        if (!wrapper) {
            ReportGetChildError("MeasureALineBackward", currentIndex - 1);
            break;
        }
        --currentIndex;
        cnt++;
        if (CheckNeedMeasure(wrapper)) {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
        if (currentIndex % lanes == 0) {
            break;
        }
    }
    if (cnt > 0) {
        startPos = endPos - mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            auto wrapper = GetListItem(layoutWrapper, currentIndex + i);
            int32_t id = wrapper->GetHostNode()->GetId();
            itemPosition_[currentIndex + i] = { id, startPos, endPos };
        }
    }
    return cnt;
}

void ListItemGroupLayoutAlgorithm::MeasureCenter(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex)
{
    MeasureALineCenter(layoutWrapper, layoutConstraint, startIndex);
    MeasureJumpToItemForward(layoutWrapper, layoutConstraint, GetEndIndex() + 1, GetEndPosition());
    MeasureJumpToItemBackward(layoutWrapper, layoutConstraint, GetStartIndex() - 1, GetStartPosition());

    totalMainSize_ = GetEndPosition() - GetStartPosition() + headerMainSize_ + footerMainSize_;
    float currentStartPos = headerMainSize_;
    int32_t i = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (auto& pos : itemPosition_) {
        float len = pos.second.endPos - pos.second.startPos;
        pos.second.startPos = currentStartPos;
        pos.second.endPos = currentStartPos + len;
        i++;
        if (i % lanes == 0) {
            currentStartPos = pos.second.endPos + spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureAuto(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex)
{
    if (MeasureALineAuto(layoutWrapper, layoutConstraint, startIndex) == 0) {
        return;
    }

    totalMainSize_ = GetEndPosition() - GetStartPosition() + headerMainSize_ + footerMainSize_;
}

void ListItemGroupLayoutAlgorithm::MeasureJumpToItemForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos)
{
    float currentStartPos = startPos;
    float currentEndPos = startPos;
    int32_t currentIndex = startIndex - 1;
    while (LessOrEqual(currentEndPos, endPos_)) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(layoutWrapper, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureJumpToItemBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos)
{
    float currentEndPos = endPos;
    float currentStartPos = endPos;
    int32_t currentIndex = endIndex + 1;
    while (GreatOrEqual(currentStartPos, startPos_)) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(layoutWrapper, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos -= spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureStart(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex)
{
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    float currentStartPos = startPos_ + contentStartOffset_;
    if (sticky == V2::StickyStyle::HEADER || sticky == V2::StickyStyle::BOTH) {
        currentStartPos += headerMainSize_;
    }

    MeasureJumpToItemForward(layoutWrapper, layoutConstraint, startIndex, currentStartPos);
    if (GreatNotEqual(currentStartPos, startPos_)) {
        MeasureJumpToItemBackward(layoutWrapper, layoutConstraint, startIndex - 1, currentStartPos);
    }

    totalMainSize_ = GetEndPosition() - GetStartPosition() + headerMainSize_ + footerMainSize_;
    currentStartPos = headerMainSize_;
    int32_t i = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (auto& pos : itemPosition_) {
        float len = pos.second.endPos - pos.second.startPos;
        pos.second.startPos = currentStartPos;
        pos.second.endPos = currentStartPos + len;
        i++;
        if (i % lanes == 0) {
            currentStartPos = pos.second.endPos + spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureEnd(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex)
{
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    float currentEndPos = endPos_ - contentEndOffset_;
    if (sticky == V2::StickyStyle::FOOTER || sticky == V2::StickyStyle::BOTH) {
        currentEndPos -= footerMainSize_;
    }

    MeasureJumpToItemBackward(layoutWrapper, layoutConstraint, endIndex, currentEndPos);
    if (LessNotEqual(currentEndPos, endPos_)) {
        MeasureJumpToItemForward(layoutWrapper, layoutConstraint, endIndex + 1, currentEndPos);
    }

    totalMainSize_ = GetEndPosition() - GetStartPosition() + headerMainSize_ + footerMainSize_;
    float currentStartPos = headerMainSize_;
    int32_t i = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (auto& pos : itemPosition_) {
        float len = pos.second.endPos - pos.second.startPos;
        pos.second.startPos = currentStartPos;
        pos.second.endPos = currentStartPos + len;
        i++;
        if (i % lanes == 0) {
            currentStartPos = pos.second.endPos + spaceWidth_;
        }
    }
}

bool ListItemGroupLayoutAlgorithm::CheckJumpForwardForBigOffset(int32_t& startIndex, float& startPos)
{
    if (!isNeedCheckOffset_ || childrenSize_) {
        return false;
    }
    float th = startPos_ - (endPos_ - startPos_) - referencePos_;
    if (GreatNotEqual(startPos, th)) {
        return false;
    }
    float averageHeight = groupItemAverageHeight_;
    if (layoutedItemInfo_.has_value()) {
        const auto& itemInfo = layoutedItemInfo_.value();
        auto totalHeight = (itemInfo.endPos - itemInfo.startPos + spaceWidth_);
        auto itemCount = itemInfo.endIndex - itemInfo.startIndex + 1;
        averageHeight = totalHeight / itemCount;
    }
    if (Positive(averageHeight)) {
        float distance = startPos_ - referencePos_ - startPos;
        int32_t jumpCount = distance / averageHeight;
        int32_t maxCount = totalItemCount_ - 1 - startIndex;
        if (jumpCount > maxCount) {
            float pos = startPos + maxCount * averageHeight;
            itemPosition_[totalItemCount_ - 1] = { -1, pos, pos + averageHeight - spaceWidth_ };
            return true;
        }
        startPos += jumpCount * averageHeight;
        startIndex += jumpCount;
    }
    return false;
}

bool ListItemGroupLayoutAlgorithm::CheckJumpBackwardForBigOffset(int32_t& endIndex, float& endPos)
{
    if (!isNeedCheckOffset_ || childrenSize_) {
        return false;
    }
    float th = endPos_ + (endPos_ - startPos_) - (referencePos_ - totalMainSize_);
    if (LessNotEqual(endPos, th)) {
        return false;
    }
    float averageHeight = groupItemAverageHeight_;
    if (layoutedItemInfo_.has_value()) {
        const auto& itemInfo = layoutedItemInfo_.value();
        auto totalHeight = (itemInfo.endPos - itemInfo.startPos + spaceWidth_);
        auto itemCount = itemInfo.endIndex - itemInfo.startIndex + 1;
        averageHeight = totalHeight / itemCount;
    }
    if (Positive(averageHeight)) {
        float distance = endPos - (endPos_ - (referencePos_ - totalMainSize_));
        int32_t jumpCount = distance / averageHeight;
        if (jumpCount > endIndex) {
            float pos = endPos - endIndex * averageHeight;
            itemPosition_[0] = { -1, pos - averageHeight + spaceWidth_, pos };
            return true;
        }
        endPos -= jumpCount * averageHeight;
        endIndex -= jumpCount;
    }
    return false;
}

void ListItemGroupLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    int32_t currentIndex = startIndex - 1;
    while (LessOrEqual(currentEndPos, endPos_ - referencePos_)) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(layoutWrapper, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        if (targetIndex_ && GreatOrEqual(startIndex, targetIndex_.value())) {
            startPos_ = prevStartPos_;
            endPos_ = prevEndPos_;
            targetIndex_.reset();
        }
    }

    currentStartPos = startPos - spaceWidth_;
    currentIndex = startIndex;
    float th = startPos_ - referencePos_;
    if (!prevMeasureBreak_) {
        th = std::max(th, headerMainSize_);
    }
    while (currentIndex > 0  && GreatNotEqual(currentStartPos, th)) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(layoutWrapper, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureBackward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    auto currentIndex = endIndex + 1;
    while (GreatOrEqual(currentStartPos, startPos_ - (referencePos_ - totalMainSize_))) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(layoutWrapper, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        if (targetIndex_ && LessOrEqual(endIndex, targetIndex_.value())) {
            startPos_ = prevStartPos_;
            endPos_ = prevEndPos_;
            targetIndex_.reset();
        }
    }
    currentIndex = endIndex;
    currentEndPos = endPos + spaceWidth_;
    while (childrenSize_ && LessOrEqual(currentEndPos, endPos_ - (referencePos_ - totalMainSize_))) {
        if (ReachResponseDeadline(layoutWrapper)) {
            measureInNextFrame_ = true;
            return;
        }
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(layoutWrapper, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::ModifyReferencePos(int32_t index, float pos)
{
    if (!childrenSize_ || !needAdjustRefPos_) {
        return;
    }
    if (forwardLayout_ && Negative(referencePos_)) {
        float offset = referencePos_ + pos;
        float newReferencePos = offset - posMap_->GetPos(index);
        refPos_ = refPos_ + newReferencePos - referencePos_;
        referencePos_ = newReferencePos;
    } else if (!forwardLayout_ && GreatNotEqual(referencePos_, prevContentMainSize_)) {
        float offset = referencePos_ - posMap_->GetPrevTotalHeight() + pos - prevContentMainSize_;
        float newReferencePos = offset + endPos_ - startPos_ + totalMainSize_ -
            (posMap_->GetPos(index) + posMap_->GetRowHeight(index));
        refPos_ = refPos_ + newReferencePos - referencePos_;
        referencePos_ = newReferencePos;
    }
}

void ListItemGroupLayoutAlgorithm::AdjustByPosMap()
{
    totalMainSize_ = posMap_->GetTotalHeight();
    if (itemPosition_.empty()) {
        return;
    }
    float startPos = itemPosition_.begin()->second.startPos;
    float offset = posMap_->GetGroupLayoutOffset(GetStartIndex(), startPos);
    for (auto& pos : itemPosition_) {
        pos.second.startPos += offset;
        pos.second.endPos += offset;
    }
}

void ListItemGroupLayoutAlgorithm::AdjustItemPosition()
{
    if (itemPosition_.empty()) {
        return;
    }
    float currentStartPos = GetStartPosition();
    if (currentStartPos < headerMainSize_) {
        auto delta = headerMainSize_ - currentStartPos;
        for (auto& pos : itemPosition_) {
            pos.second.startPos += delta;
            pos.second.endPos += delta;
        }
        for (auto& pos : cachedItemPosition_) {
            pos.second.startPos += delta;
            pos.second.endPos += delta;
        }
        totalMainSize_ = std::max(totalMainSize_ + delta, GetEndPosition() + footerMainSize_);
        adjustReferenceDelta_ = -delta;
    } else if (GetStartIndex() == 0 && currentStartPos > headerMainSize_) {
        auto delta = currentStartPos - headerMainSize_;
        for (auto& pos : itemPosition_) {
            pos.second.startPos -= delta;
            pos.second.endPos -= delta;
        }
        for (auto& pos : cachedItemPosition_) {
            pos.second.startPos -= delta;
            pos.second.endPos -= delta;
        }
        totalMainSize_ -= delta;
        adjustReferenceDelta_ = delta;
    }
    if (GetEndIndex() == totalItemCount_ - 1) {
        totalMainSize_ = GetEndPosition() + footerMainSize_;
    } else {
        float endPos = GetCacheEndIndex() > GetEndIndex() ? GetCacheEndPosition() : GetEndPosition();
        totalMainSize_ = std::max(totalMainSize_, endPos + footerMainSize_);
    }
}

void ListItemGroupLayoutAlgorithm::UpdateLayoutedItemInfo()
{
    if (itemPosition_.empty()) {
        return;
    }
    int32_t startIndex = INT_MAX;
    int32_t endIndex = -1;
    float startPos = FLT_MAX;
    float endPos = -1.0f;
    if (!itemPosition_.empty()) {
        startIndex = itemPosition_.begin()->first;
        endIndex = itemPosition_.rbegin()->first;
        startPos = itemPosition_.begin()->second.startPos;
        endPos = itemPosition_.rbegin()->second.endPos;
    }
    if (layoutedItemInfo_.has_value()) {
        auto& itemInfo = layoutedItemInfo_.value();
        auto prevStartIndex = itemInfo.startIndex;
        if (startIndex <= itemInfo.startIndex || LessNotEqual(startPos, itemInfo.startPos) ||
            startIndex > itemInfo.endIndex) {
            itemInfo.startIndex = startIndex;
            itemInfo.startPos = startPos;
        }
        if (endIndex >= itemInfo.endIndex || GreatNotEqual(endPos, itemInfo.endPos) ||
            itemInfo.endIndex > totalItemCount_ - 1 || endIndex < prevStartIndex) {
            itemInfo.endIndex = endIndex;
            itemInfo.endPos = endPos;
        }
    } else {
        layoutedItemInfo_ = { startIndex, startPos, endIndex, endPos };
    }
}

void ListItemGroupLayoutAlgorithm::CheckRecycle(
    const RefPtr<LayoutWrapper>& layoutWrapper, float startPos, float endPos, float referencePos, bool forwardLayout)
{
    referencePos = UpdateReferencePos(layoutWrapper->GetLayoutProperty(), forwardLayout, referencePos);
    // Mark inactive in wrapper.
    if (forwardLayout) {
        for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
            if (GreatOrEqual(pos->second.endPos, startPos - referencePos)) {
                break;
            }
            recycledItemPosition_.insert(*pos);
            cachedItemPosition_.insert(*pos);
            pos = itemPosition_.erase(pos);
        }
        return;
    }
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessOrEqual(pos->second.startPos, endPos - (referencePos - totalMainSize_))) {
            break;
        }
        recycledItemPosition_.insert(*pos);
        cachedItemPosition_.insert(*pos);
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ListItemGroupLayoutAlgorithm::LayoutListItem(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    // layout items.
    for (auto& pos : itemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        if (!wrapper) {
            ReportGetChildError("LayoutListItem", pos.first);
            continue;
        }

        auto offset = paddingOffset;
        int32_t laneIndex = pos.first % lanes_;
        float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        float laneCrossOffset = CalculateLaneCrossOffset((crossSize + GetLaneGutter()) / lanes_, childCrossSize);
        auto startPos = !isStackFromEnd_ ? pos.second.startPos : totalMainSize_ - pos.second.endPos;
        auto endPos = !isStackFromEnd_ ? pos.second.endPos : totalMainSize_ - pos.second.startPos;
        if (layoutDirection_ == TextDirection::RTL) {
            if (axis_ == Axis::VERTICAL) {
                auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
                auto tmpX = crossSize - laneCrossOffset -
                    ((crossSize + laneGutter_) / lanes_) * laneIndex - size.Width();
                offset = offset + OffsetF(tmpX, startPos);
            } else {
                auto tmpY = laneCrossOffset + ((crossSize + laneGutter_) / lanes_) * laneIndex;
                offset = offset + OffsetF(totalMainSize_ - endPos, tmpY);
            }
        } else {
            if (axis_ == Axis::VERTICAL) {
                offset =
                    offset + OffsetF(0, startPos) + OffsetF(laneCrossOffset, 0) +
                    OffsetF(((crossSize + laneGutter_) / lanes_) * laneIndex, 0);
            } else {
                offset =
                    offset + OffsetF(startPos, 0) + OffsetF(0, laneCrossOffset) +
                    OffsetF(0, ((crossSize + laneGutter_) / lanes_) * laneIndex);
            }
        }
        auto index = isStackFromEnd_ ? totalItemCount_ - pos.first - 1 : pos.first;
        SetListItemIndex(layoutWrapper, wrapper, index);
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        if (wrapper->CheckNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
        auto frameNode = AceType::DynamicCast<FrameNode>(wrapper);
        if (frameNode) {
            frameNode->MarkAndCheckNewOpIncNode(axis_);
        }
    }
}

void ListItemGroupLayoutAlgorithm::UpdateZIndex(const RefPtr<LayoutWrapper>& layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateZIndex(1);
}

void ListItemGroupLayoutAlgorithm::LayoutHeaderFooterRTL(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    OffsetF selfOffset = layoutWrapper->GetGeometryNode()->GetPaddingOffset();
    selfOffset = selfOffset - listLayoutProperty_->CreatePaddingAndBorder().Offset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_);
    float footerMainSize = 0.0f;
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    RefPtr<LayoutWrapper> headerWrapper = headerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(headerIndex_) : nullptr;
    RefPtr<LayoutWrapper> footerWrapper = footerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(footerIndex_) : nullptr;
    if (footerWrapper) {
        UpdateZIndex(footerWrapper);
        footerMainSize = footerWrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
        float footerPos = 0.0f;
        if (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::FOOTER) {
            contentStartOffset_ = std::max(contentStartOffset_, 0.0f);
            float stickyPos = contentStartOffset_ - mainPos;
            stickyPos = std::min(stickyPos, totalMainSize_ - footerMainSize_ - headerMainSize_);
            footerPos = std::max(footerPos, stickyPos);
            footerPos = std::min(footerPos, totalMainSize_ - footerMainSize_ - headerMainSize_);
        }
        LayoutIndex(footerWrapper, paddingOffset, crossSize, footerPos);
        endFooterPos_ = endFooterPos_ > mainPos ? mainPos : endFooterPos_;
    }

    if (headerWrapper) {
        float headPos = totalMainSize_ - headerMainSize_;
        UpdateZIndex(headerWrapper);
        float const listMainSize = endPos_ - startPos_;
        if (Positive(listMainSize) && (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::HEADER)) {
            auto headerMainSize = headerWrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
            float stickyPos = listMainSize - contentEndOffset_ - mainPos - headerMainSize;
            if (stickyPos < footerMainSize) {
                stickyPos = footerMainSize;
            }
            if (stickyPos < headPos) {
                headPos = stickyPos;
            }
        }
        LayoutIndex(headerWrapper, paddingOffset, crossSize, headPos);
        startHeaderPos_ = mainPos + totalMainSize_ - headerMainSize_ - listMainSize;
    }
}

void ListItemGroupLayoutAlgorithm::LayoutHeaderFooterLTR(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    OffsetF selfOffset = layoutWrapper->GetGeometryNode()->GetPaddingOffset();
    selfOffset = selfOffset - listLayoutProperty_->CreatePaddingAndBorder().Offset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_);
    float headerMainSize = 0.0f;
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    RefPtr<LayoutWrapper> headerWrapper = headerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(headerIndex_) : nullptr;
    RefPtr<LayoutWrapper> footerWrapper = footerIndex_ >= 0 ?
        layoutWrapper->GetOrCreateChildByIndex(footerIndex_) : nullptr;
    if (headerWrapper) {
        UpdateZIndex(headerWrapper);
        headerMainSize = headerWrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
        float headerPos = 0.0f;
        if (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::HEADER) {
            contentStartOffset_ = std::max(contentStartOffset_, 0.0f);
            float stickyPos = contentStartOffset_ - mainPos;
            stickyPos = std::min(stickyPos, totalMainSize_ - footerMainSize_ - headerMainSize_);
            headerPos = std::max(headerPos, stickyPos);
        }
        LayoutIndex(headerWrapper, paddingOffset, crossSize, headerPos);
        startHeaderPos_ = startHeaderPos_ > mainPos ? mainPos : startHeaderPos_;
    }

    if (footerWrapper) {
        float endPos = totalMainSize_ - footerMainSize_;
        UpdateZIndex(footerWrapper);
        float const listMainSize = endPos_ - startPos_;
        if (Positive(listMainSize) && (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::FOOTER)) {
            auto footerMainSize = footerWrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
            float stickyPos = listMainSize - contentEndOffset_ - mainPos - footerMainSize;
            if (stickyPos < headerMainSize) {
                stickyPos = headerMainSize;
            }
            if (stickyPos < endPos) {
                endPos = stickyPos;
            }
        }
        LayoutIndex(footerWrapper, paddingOffset, crossSize, endPos);
        endFooterPos_ = mainPos + totalMainSize_ - footerMainSize_ - listMainSize;
    }
}

void ListItemGroupLayoutAlgorithm::LayoutIndex(const RefPtr<LayoutWrapper>& wrapper, const OffsetF& paddingOffset,
    float crossSize, float startPos)
{
    CHECK_NULL_VOID(wrapper);
    auto offset = paddingOffset;
    float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float laneCrossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
    if (axis_ == Axis::VERTICAL) {
        if (layoutDirection_ == TextDirection::RTL) {
            auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
            offset = offset + OffsetF(crossSize - laneCrossOffset - size.Width(), startPos);
        } else {
            offset = offset + OffsetF(laneCrossOffset, startPos);
        }
    } else {
        offset = offset + OffsetF(startPos, laneCrossOffset);
    }
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}

float ListItemGroupLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    float delta = crossSize - GetLaneGutter() - childCrossSize;
    if (LessOrEqual(delta, 0.0f)) {
        return 0.0f;
    }
    switch (itemAlign_) {
        case OHOS::Ace::V2::ListItemAlign::START:
            return 0.0f;
        case OHOS::Ace::V2::ListItemAlign::CENTER:
            return delta / 2; /* 2:average */
        case OHOS::Ace::V2::ListItemAlign::END:
            return delta;
        default:
            return 0.0f;
    }
}

void ListItemGroupLayoutAlgorithm::CalculateLanes(const RefPtr<ListLayoutProperty>& layoutProperty,
    const LayoutConstraintF& layoutConstraint, std::optional<float> crossSizeOptional, Axis axis)
{
    int32_t lanes = layoutProperty->GetLanes().value_or(1);
    lanes = lanes > 1 ? lanes : 1;
    if (crossSizeOptional.has_value()) {
        if (layoutProperty->GetLaneMinLength().has_value()) {
            minLaneLength_ = ConvertToPx(layoutProperty->GetLaneMinLength().value(),
                layoutConstraint.scaleProperty, crossSizeOptional.value());
        }
        if (layoutProperty->GetLaneMaxLength().has_value()) {
            maxLaneLength_ = ConvertToPx(layoutProperty->GetLaneMaxLength().value(),
                layoutConstraint.scaleProperty, crossSizeOptional.value());
        }
        if (layoutProperty->GetLaneGutter().has_value()) {
            auto laneGutter = ConvertToPx(
                layoutProperty->GetLaneGutter().value(), layoutConstraint.scaleProperty, crossSizeOptional.value());
            laneGutter_ = laneGutter.value_or(0.0f);
        }
    }
    lanes_ = ListLanesLayoutAlgorithm::CalculateLanesParam(
        minLaneLength_, maxLaneLength_, lanes, crossSizeOptional, laneGutter_);
}

void ListItemGroupLayoutAlgorithm::SetListItemIndex(const LayoutWrapper* groupLayoutWrapper,
    const RefPtr<LayoutWrapper>& itemLayoutWrapper, int32_t indexInGroup)
{
    auto host = itemLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto listItem = host->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID(listItem);
    listItem->SetIndexInListItemGroup(indexInGroup);

    host = groupLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto listItemGroup = host->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID(listItemGroup);
    listItem->SetIndexInList(listItemGroup->GetIndexInList());
}

ListItemGroupLayoutInfo ListItemGroupLayoutAlgorithm::GetLayoutInfo() const
{
    ListItemGroupLayoutInfo info;
    info.headerSize = headerMainSize_;
    info.footerSize = footerMainSize_;
    info.spaceWidth = spaceWidth_;
    if (totalItemCount_ == 0 || childrenSize_) {
        info.atStart = true;
        info.atEnd = true;
        return info;
    }
    if (layoutedItemInfo_.has_value()) {
        const auto& itemInfo = layoutedItemInfo_.value();
        info.atStart = itemInfo.startIndex == 0;
        info.atEnd = itemInfo.endIndex >= totalItemCount_ - 1;
        auto totalHeight = (itemInfo.endPos - itemInfo.startPos + spaceWidth_);
        auto itemCount = itemInfo.endIndex - itemInfo.startIndex + 1;
        info.averageHeight = totalHeight / itemCount;
    }
    return info;
}

bool ListItemGroupLayoutAlgorithm::IsCardStyleForListItemGroup(const LayoutWrapper* groupLayoutWrapper)
{
    auto host = groupLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto listItemGroup = host->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroup, false);
    return listItemGroup->GetListItemGroupStyle() == V2::ListItemGroupStyle::CARD;
}

void ListItemGroupLayoutAlgorithm::MeasureCacheForward(LayoutWrapper* layoutWrapper, ListItemGroupCacheParam& param)
{
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    int32_t endIndex = itemPosition_.empty() ? -1 : GetEndIndex();
    if (endIndex >= totalItemCount_ - 1) {
        return;
    }
    int32_t limit = std::min(endIndex + param.cacheCountForward * lanes_, totalItemCount_ - 1);
    float startPos = itemPosition_.empty() ? headerMainSize_ : GetEndPosition();
    int32_t curIndex = GetLanesFloor(endIndex + 1);
    while (curIndex <= limit) {
        if (GetSysTimestamp() > param.deadline) {
            return;
        }
        float mainLen = 0.0f;
        int32_t cnt = 0;
        for (int32_t i = 0; i < lanes && curIndex + i < totalItemCount_; i++) {
            auto wrapper = GetListItem(layoutWrapper, curIndex + i, param.show, !param.show);
            if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(param.deadline)) {
                return;
            }
            cnt++;
            if (CheckNeedMeasure(wrapper)) {
                ACE_SCOPED_TRACE("ListItemGroupLayoutAlgorithm::MeasureCacheForward:%d", curIndex + i);
                wrapper->Measure(childLayoutConstraint_);
            }
            mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
        }
        for (int32_t i = 0; i < cnt; i++) {
            cachedItemPosition_[curIndex + i] = { -1, startPos, startPos + mainLen };
        }
        curIndex += cnt;
        startPos += mainLen + spaceWidth_;
        param.forwardCachedIndex = curIndex - 1;
    }
}

void ListItemGroupLayoutAlgorithm::MeasureCacheBackward(LayoutWrapper* layoutWrapper, ListItemGroupCacheParam& param)
{
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    int32_t startIndex = itemPosition_.empty() ? totalItemCount_ : GetStartIndex();
    if (startIndex <= 0) {
        return;
    }
    int32_t limit = std::max(startIndex - param.cacheCountBackward * lanes_, 0);
    if (limit % lanes_ != 0) {
        limit += (lanes_ - limit % lanes_);
    }
    float endPos = itemPosition_.empty() ? totalMainSize_ - footerMainSize_ : GetStartPosition();
    int32_t curIndex = GetLanesCeil(startIndex - 1);
    while (curIndex >= limit) {
        if (GetSysTimestamp() > param.deadline) {
            return;
        }
        float mainLen = 0.0f;
        int32_t cnt = 0;
        for (int32_t i = 0; i < lanes && curIndex - i >= 0; i++) {
            auto wrapper = GetListItem(layoutWrapper, curIndex - i, param.show, !param.show);
            if (!wrapper || !wrapper->GetHostNode() || !wrapper->GetHostNode()->RenderCustomChild(param.deadline)) {
                return;
            }
            cnt++;
            if (CheckNeedMeasure(wrapper)) {
                ACE_SCOPED_TRACE("ListItemGroupLayoutAlgorithm::MeasureCacheForward:%d", curIndex - i);
                wrapper->Measure(childLayoutConstraint_);
            }
            mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
            if (0 == (curIndex - i) % lanes) {
                break;
            }
        }
        for (int32_t i = 0; i < cnt; i++) {
            cachedItemPosition_[curIndex - i] = { -1, endPos - mainLen, endPos };
        }
        curIndex -= cnt;
        endPos -= (mainLen + spaceWidth_);
        param.backwardCachedIndex = curIndex + 1;
    }
}

void ListItemGroupLayoutAlgorithm::MeasureCacheItem(LayoutWrapper* layoutWrapper)
{
    ListItemGroupCacheParam& param = cacheParam_.value();
    if (param.forward) {
        MeasureCacheForward(layoutWrapper, param);
    }
    if (param.backward) {
        MeasureCacheBackward(layoutWrapper, param);
    }
    if (cachedItemPosition_.empty()) {
        return;
    }
    float originHeight = totalMainSize_;
    float currentStartPos = GetCacheStartPosition();
    if (currentStartPos < headerMainSize_) {
        auto delta = headerMainSize_ - currentStartPos;
        for (auto& pos : itemPosition_) {
            pos.second.startPos += delta;
            pos.second.endPos += delta;
        }
        for (auto& pos : cachedItemPosition_) {
            pos.second.startPos += delta;
            pos.second.endPos += delta;
        }
        totalMainSize_ = std::max(totalMainSize_ + delta,
            std::max(GetCacheEndPosition(), GetEndPosition()) + footerMainSize_);
        adjustReferenceDelta_ = -delta;
    } else if (GetCacheStartIndex() == 0 && currentStartPos > headerMainSize_) {
        auto delta = currentStartPos - headerMainSize_;
        for (auto& pos : itemPosition_) {
            pos.second.startPos -= delta;
            pos.second.endPos -= delta;
        }
        for (auto& pos : cachedItemPosition_) {
            pos.second.startPos -= delta;
            pos.second.endPos -= delta;
        }
        totalMainSize_ -= delta;
        adjustReferenceDelta_ = delta;
    }
    if (GetCacheEndIndex() == totalItemCount_ - 1) {
        totalMainSize_ = GetCacheEndPosition() + footerMainSize_;
    } else {
        float endPos = GetCacheEndIndex() > GetEndIndex() || itemPosition_.empty() ?
            GetCacheEndPosition() : GetEndPosition();
        totalMainSize_ = std::max(totalMainSize_, endPos + footerMainSize_);
    }
    adjustTotalSize_ = totalMainSize_ - originHeight;
}

void ListItemGroupLayoutAlgorithm::LayoutCacheItem(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize, bool show)
{
    for (auto& pos : cachedItemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first, show, !show);
        if (!wrapper) {
            continue;
        }
        auto offset = paddingOffset;
        int32_t laneIndex = pos.first % lanes_;
        float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        float laneCrossOffset = CalculateLaneCrossOffset((crossSize + GetLaneGutter()) / lanes_, childCrossSize);
        auto startPos = !isStackFromEnd_ ? pos.second.startPos : totalMainSize_ - pos.second.endPos;
        auto endPos = !isStackFromEnd_ ? pos.second.endPos : totalMainSize_ - pos.second.startPos;
        if (layoutDirection_ == TextDirection::RTL) {
            if (axis_ == Axis::VERTICAL) {
                auto size = wrapper->GetGeometryNode()->GetMarginFrameSize();
                auto tmpX = crossSize - laneCrossOffset -
                    ((crossSize + laneGutter_) / lanes_) * laneIndex - size.Width();
                offset = offset + OffsetF(tmpX, startPos);
            } else {
                auto tmpY = laneCrossOffset + ((crossSize + laneGutter_) / lanes_) * laneIndex;
                offset = offset + OffsetF(totalMainSize_ - endPos, tmpY);
            }
        } else {
            if (axis_ == Axis::VERTICAL) {
                offset =
                    offset + OffsetF(0, startPos) + OffsetF(laneCrossOffset, 0) +
                    OffsetF(((crossSize + laneGutter_) / lanes_) * laneIndex, 0);
            } else {
                offset =
                    offset + OffsetF(startPos, 0) + OffsetF(0, laneCrossOffset) +
                    OffsetF(0, ((crossSize + laneGutter_) / lanes_) * laneIndex);
            }
        }
        auto index = isStackFromEnd_ ? totalItemCount_ - pos.first - 1 : pos.first;
        SetListItemIndex(layoutWrapper, wrapper, index);
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        if (wrapper->CheckNeedForceMeasureAndLayout()) {
            wrapper->Layout();
        } else {
            SyncGeometry(wrapper);
        }
    }
}

void ListItemGroupLayoutAlgorithm::ReverseItemPosition(
    ListItemGroupLayoutAlgorithm::PositionMap& itemPosition, int32_t totalItemCount, float mainSize)
{
    if (!isStackFromEnd_ || itemPosition.empty()) {
        return;
    }
    ListItemGroupLayoutAlgorithm::PositionMap posMap;
    for (auto pos : itemPosition) {
        auto startPos = mainSize - pos.second.endPos;
        auto endPos = mainSize - pos.second.startPos;
        pos.second.startPos = startPos;
        pos.second.endPos = endPos;
        posMap[totalItemCount - pos.first - 1] = pos.second;
    }
    itemPosition = std::move(posMap);
}

void ListItemGroupLayoutAlgorithm::ReverseLayoutedItemInfo(int32_t totalItemCount, float mainSize)
{
    if (!isStackFromEnd_ || !layoutedItemInfo_.has_value()) {
        return;
    }
    auto& itemInfo = layoutedItemInfo_.value();
    auto startIndex = totalItemCount - itemInfo.endIndex - 1;
    auto startPos = mainSize - itemInfo.endPos;
    auto endIndex = totalItemCount - itemInfo.startIndex - 1;
    auto endPos = mainSize - itemInfo.startPos;
    layoutedItemInfo_ = { startIndex, startPos, endIndex, endPos };
}

void ListItemGroupLayoutAlgorithm::ReportGetChildError(const std::string& funcName, int32_t index) const
{
    if (index < 0 || index > totalItemCount_ - 1) {
        return;
    }
    std::string subErrorType = funcName + " get item: " + std::to_string(index) + " failed.";
    EventReport::ReportScrollableErrorEvent("ListItemGroup", ScrollableErrorType::GET_CHILD_FAILED, subErrorType);
}

bool ListItemGroupLayoutAlgorithm::IsRoundingMode(LayoutWrapper* layoutWrapper)
{
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto pipeline = host->GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    return pipeline->GetPixelRoundMode() == PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE;
}

void ListItemGroupLayoutAlgorithm::ResetLayoutItem(LayoutWrapper* layoutWrapper)
{
    for (auto& pos : recycledItemPosition_) {
        auto wrapper = GetListItem(layoutWrapper, pos.first);
        auto wrapperFrameNode = AceType::DynamicCast<FrameNode>(wrapper);
        if (wrapperFrameNode) {
            wrapperFrameNode->ClearSubtreeLayoutAlgorithm();
        }
    }
}
} // namespace OHOS::Ace::NG
