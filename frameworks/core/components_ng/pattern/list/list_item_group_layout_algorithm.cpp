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

#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"

#include "base/utils/utils.h"
#include "core/components/common/layout/grid_system_manager.h"
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint32_t GRID_COUNTS_4 = 4;
constexpr uint32_t GRID_COUNTS_6 = 6;
constexpr uint32_t GRID_COUNTS_8 = 8;
constexpr uint32_t GRID_COUNTS_12 = 12;

uint32_t GetMaxGridCounts(const RefPtr<GridColumnInfo>& columnInfo)
{
    CHECK_NULL_RETURN(columnInfo, GRID_COUNTS_8);
    auto currentColumns = columnInfo->GetParent()->GetColumns();
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
    CHECK_NULL_VOID(listLayoutProperty_);
    auto layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    axis_ = listLayoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis_);
    auto space = layoutProperty->GetSpace().value_or(Dimension(0));

    auto layoutConstraint = layoutProperty->GetLayoutConstraint().value();
    CalculateLanes(listLayoutProperty_, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
    auto itemLayoutConstraint = layoutProperty->CreateChildConstraint();
    isCardStyle_ = IsCardStyleForListItemGroup(layoutWrapper);
    if (isCardStyle_) {
        auto maxWidth = GetListItemGroupMaxWidth(contentConstraint.parentIdealSize, layoutProperty) -
                        layoutProperty->CreatePaddingAndBorder().Width();
        contentIdealSize.SetCrossSize(maxWidth, axis_);
    }
    UpdateListItemConstraint(contentIdealSize, itemLayoutConstraint);
    auto headerFooterLayoutConstraint = layoutProperty->CreateChildConstraint();
    headerFooterLayoutConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);
    spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
    if (layoutProperty->GetDivider().has_value()) {
        auto divider = layoutProperty->GetDivider().value();
        std::optional<float> dividerSpace = divider.strokeWidth.ConvertToPx();
        if (dividerSpace.has_value()) {
            spaceWidth_ = std::max(spaceWidth_, dividerSpace.value());
        }
    }
    UpdateReferencePos(layoutProperty);
    totalItemCount_ = layoutWrapper->GetTotalChildCount() - itemStartIndex_;

    totalMainSize_ = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    if (headerIndex_ >= 0) {
        auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        headerWrapper->Measure(headerFooterLayoutConstraint);
        headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    if (footerIndex_ >= 0) {
        auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        footerWrapper->Measure(headerFooterLayoutConstraint);
        footerMainSize_ = GetMainAxisSize(footerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    totalMainSize_ = std::max(totalMainSize_, headerMainSize_ + footerMainSize_);
    MeasureListItem(layoutWrapper, itemLayoutConstraint);
    if (!itemPosition_.empty()) {
        if (GetEndIndex() == totalItemCount_ - 1) {
            totalMainSize_ = GetEndPosition() + footerMainSize_;
        } else {
            totalMainSize_ = std::max(totalMainSize_, GetEndPosition() + footerMainSize_);
        }
    }

    auto crossSize = contentIdealSize.CrossSize(axis_);
    if (crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(layoutWrapper, axis_), axis_);
    }
    contentIdealSize.SetMainSize(totalMainSize_, axis_);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());
    layoutWrapper->SetCacheCount(listLayoutProperty_->GetCachedCountValue(1) * lanes_);
}

float ListItemGroupLayoutAlgorithm::GetListItemGroupMaxWidth(
    const OptionalSizeF& parentIdealSize, RefPtr<LayoutProperty> layoutProperty)
{
    RefPtr<GridColumnInfo> columnInfo;
    columnInfo = GridSystemManager::GetInstance().GetInfoByType(GridColumnType::LIST_CARD);
    columnInfo->GetParent()->BuildColumnWidth();
    auto maxGridWidth = static_cast<float>(columnInfo->GetWidth(GetMaxGridCounts(columnInfo)));
    auto parentWidth = parentIdealSize.CrossSize(axis_).value() + layoutProperty->CreatePaddingAndBorder().Width();
    auto maxWidth = std::min(parentWidth, maxGridWidth);
    return maxWidth;
}

void ListItemGroupLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    const auto& layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis_);
    CHECK_NULL_VOID(listLayoutProperty_);
    itemAlign_ = listLayoutProperty_->GetListItemAlign().value_or(V2::ListItemAlign::START);

    if (headerIndex_ >= 0 || footerIndex_ >= 0) {
        LayoutHeaderFooter(layoutWrapper, paddingOffset, crossSize);
    }
    // layout items.
    LayoutListItem(layoutWrapper, paddingOffset, crossSize);
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
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(pos.first, false);
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

void ListItemGroupLayoutAlgorithm::UpdateReferencePos(RefPtr<LayoutProperty> layoutProperty)
{
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    const auto& margin = layoutProperty->CreateMargin();
    auto offsetBeforeContent_ = axis_ == Axis::HORIZONTAL ? padding.left.value_or(0) : padding.top.value_or(0);
    auto offsetAfterContent_ = axis_ == Axis::HORIZONTAL ? padding.right.value_or(0) : padding.bottom.value_or(0);
    offsetBeforeContent_ += axis_ == Axis::HORIZONTAL ? margin.left.value_or(0) : margin.top.value_or(0);
    offsetAfterContent_ += axis_ == Axis::HORIZONTAL ? margin.right.value_or(0) : margin.bottom.value_or(0);
    forwardLayout_ ? referencePos_ += offsetBeforeContent_ : referencePos_ -= offsetAfterContent_;
}

bool ListItemGroupLayoutAlgorithm::NeedMeasureItem() const
{
    if (forwardLayout_ && headerIndex_ >= 0) {
        if (GreatNotEqual(headerMainSize_, endPos_ - referencePos_)) {
            return false;
        }
    }
    if (forwardLayout_ && footerIndex_ >= 0) {
        if (LessNotEqual(totalMainSize_ - footerMainSize_, startPos_ - referencePos_)) {
            return false;
        }
    }
    if (!forwardLayout_ && headerIndex_ >= 0) {
        if (GreatNotEqual(headerMainSize_, endPos_ - (referencePos_ - totalMainSize_))) {
            return false;
        }
    }
    if (!forwardLayout_ && footerIndex_ >= 0) {
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

void ListItemGroupLayoutAlgorithm::MeasureListItem(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    if (totalItemCount_ <= 0) {
        totalMainSize_ = headerMainSize_ + footerMainSize_;
        layoutWrapper->RemoveAllChildInRenderTree();
        itemPosition_.clear();
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
        layoutWrapper->RemoveAllChildInRenderTree();
        LayoutListItemAll(layoutWrapper, layoutConstraint, startPos);
        return;
    }
    if (targetIndex_) {
        startPos_ = -Infinity<float>();
        endPos_ = Infinity<float>();
    }
    if (jumpIndex_.has_value()) {
        if (jumpIndex_.value() == LAST_ITEM) {
            jumpIndex_ = totalItemCount_ - 1;
        }
        auto jumpIndex = jumpIndex_.value();
        if (jumpIndex < 0 || jumpIndex >= totalItemCount_) {
            jumpIndex = 0;
        }
        if (forwardLayout_) {
            startIndex = jumpIndex;
        } else {
            endIndex = jumpIndex;
        }
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
        jumpIndex_.reset();
    } else if (!itemPosition_.empty()) {
        if (itemPosition_.begin()->first > 0) {
            startPos = itemPosition_.begin()->second.first;
        }
        endPos = itemPosition_.rbegin()->second.second;
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
    } else if (!NeedMeasureItem()) {
        layoutWrapper->RemoveAllChildInRenderTree();
        itemPosition_.clear();
        return;
    }
    LOGD("referencePos_ is %{public}f, startPos_: %{public}f, endPos_: %{public}f, forward:%{public}d",
        referencePos_, startPos_, endPos_, forwardLayout_);
    if (forwardLayout_) {
        startIndex = GetLanesFloor(startIndex);
        LOGD("startIndex:%{public}d, startPos:%{public}f", startIndex, startPos);
        MeasureForward(layoutWrapper, layoutConstraint, startIndex, startPos);
    } else {
        LOGD("endIndex:%{public}d, endPos:%{public}f", endIndex, endPos);
        MeasureBackward(layoutWrapper, layoutConstraint, endIndex, endPos);
    }
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex + 1 <= totalItemCount_; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex + 1);
        if (!wrapper) {
            break;
        }
        cnt++;
        ++currentIndex;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
    }
    if (cnt > 0) {
        endPos = startPos + mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            itemPosition_[currentIndex - i] = { startPos, endPos };
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
            break;
        }
        --currentIndex;
        cnt++;
        {
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
            itemPosition_[currentIndex + i] = { startPos, endPos };
        }
    }
    return cnt;
}

void ListItemGroupLayoutAlgorithm::MeasureForward(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    int32_t currentIndex = startIndex - 1;
    while (LessOrEqual(currentEndPos, endPos_ - referencePos_)) {
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(layoutWrapper, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        LOGD("LayoutForward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
        if (targetIndex_ && GreatOrEqual(startIndex, targetIndex_.value())) {
            startPos_ = prevStartPos_;
            endPos_ = prevEndPos_;
            targetIndex_.reset();
        }
    }

    currentStartPos = startPos - spaceWidth_;
    currentIndex = startIndex;
    while (currentIndex > 0  && GreatOrEqual(currentStartPos, startPos_ - referencePos_)) {
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
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(layoutWrapper, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        LOGD("LayoutBackward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
        if (targetIndex_ && LessOrEqual(endIndex, targetIndex_.value())) {
            startPos_ = prevStartPos_;
            endPos_ = prevEndPos_;
            targetIndex_.reset();
        }
    }

    if (itemPosition_.empty()) {
        return;
    }

    if (currentStartPos < headerMainSize_) {
        auto delta = headerMainSize_ - currentStartPos;
        for (auto& pos : itemPosition_) {
            pos.second.first += delta;
            pos.second.second += delta;
        }
        totalMainSize_ = std::max(totalMainSize_, GetEndPosition() + footerMainSize_);
    } else if (GetStartIndex() == 0 && currentStartPos > headerMainSize_) {
        auto delta = currentStartPos - headerMainSize_;
        for (auto& pos : itemPosition_) {
            pos.second.first -= delta;
            pos.second.second -= delta;
        }
        totalMainSize_ -= delta;
    }
}

void ListItemGroupLayoutAlgorithm::CheckRecycle(
    const RefPtr<LayoutWrapper>& layoutWrapper, float startPos, float endPos, float referencePos, bool forwardLayout)
{
    // Mark inactive in wrapper.
    if (forwardLayout) {
        for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
            if (GreatOrEqual(pos->second.second, startPos - referencePos)) {
                break;
            }
            LOGI("recycle item:%{public}d", pos->first);
            layoutWrapper->RemoveChildInRenderTree(pos->first);
            itemPosition_.erase(pos++);
        }
        return;
    }
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessOrEqual(pos->second.first, endPos - (referencePos - totalMainSize_))) {
            break;
        }
        layoutWrapper->RemoveChildInRenderTree(pos->first);
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
            LOGI("wrapper is out of boundary");
            continue;
        }

        auto offset = paddingOffset;
        int32_t laneIndex = pos.first % lanes_;
        float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
        childCrossSize_ = childCrossSize;
        float laneCrossOffset = CalculateLaneCrossOffset(crossSize / lanes_, childCrossSize);
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(0, pos.second.first) + OffsetF(laneCrossOffset, 0) +
                     OffsetF(childCrossSize * laneIndex + laneGutter_ * laneIndex, 0);
        } else {
            offset = offset + OffsetF(pos.second.first, 0) + OffsetF(0, laneCrossOffset) +
                     OffsetF(0, childCrossSize * laneIndex + laneGutter_ * laneIndex);
        }
        SetListItemIndex(layoutWrapper, wrapper, pos.first);
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        wrapper->Layout();
    }
}

void ListItemGroupLayoutAlgorithm::LayoutHeaderFooter(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    OffsetF selfOffset = layoutWrapper->GetGeometryNode()->GetPaddingOffset();
    selfOffset = selfOffset - listLayoutProperty_->CreatePaddingAndBorder().Offset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_);
    float headerMainSize = 0.0f;
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    if (headerIndex_ >= 0) {
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        CHECK_NULL_VOID(wrapper);
        headerMainSize = wrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
        float headerPos = 0.0f;
        if (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::HEADER) {
            float endPos = itemPosition_.empty() ? headerMainSize : itemPosition_.rbegin()->second.second;
            float stickyPos = -mainPos;
            if (stickyPos + headerMainSize > endPos) {
                stickyPos = endPos - headerMainSize;
            }
            if (stickyPos > headerPos) {
                headerPos = stickyPos;
            }
        }
        LayoutIndex(wrapper, paddingOffset, crossSize, headerPos);
    }

    if (footerIndex_ >= 0) {
        float endPos = totalMainSize_ - footerMainSize_;
        auto wrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        CHECK_NULL_VOID(wrapper);
        float const listMainSize = endPos_ - startPos_;
        if (Positive(listMainSize) && (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::FOOTER)) {
            auto footerMainSize = wrapper->GetGeometryNode()->GetFrameSize().MainSize(axis_);
            float stickyPos = listMainSize - mainPos - footerMainSize;
            if (stickyPos < headerMainSize) {
                stickyPos = headerMainSize;
            }
            if (stickyPos < endPos) {
                endPos = stickyPos;
            }
        }
        LayoutIndex(wrapper, paddingOffset, crossSize, endPos);
    }
}

void ListItemGroupLayoutAlgorithm::LayoutIndex(const RefPtr<LayoutWrapper>& wrapper, const OffsetF& paddingOffset,
    float crossSize, float startPos)
{
    CHECK_NULL_VOID_NOLOG(wrapper);
    auto offset = paddingOffset;
    float childCrossSize = GetCrossAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float laneCrossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
    if (axis_ == Axis::VERTICAL) {
        offset = offset + OffsetF(laneCrossOffset, startPos);
    } else {
        offset = offset + OffsetF(startPos, laneCrossOffset);
    }
    wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
    wrapper->Layout();
}

float ListItemGroupLayoutAlgorithm::CalculateLaneCrossOffset(float crossSize, float childCrossSize)
{
    float delta = crossSize - childCrossSize;
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
            LOGW("Invalid ListItemAlign: %{public}d", itemAlign_);
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
            laneGutter_ = laneGutter.value();
        }
    }

    lanes_ = ListLanesLayoutAlgorithm::CalculateLanesParam(
        minLaneLength_, maxLaneLength_, lanes, crossSizeOptional, laneGutter_);
}

void ListItemGroupLayoutAlgorithm::SetListItemIndex(const LayoutWrapper* groupLayoutWrapper,
    const RefPtr<LayoutWrapper>& itemLayoutWrapper, int32_t indexInGroup)
{
    auto host = itemLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID_NOLOG(host);
    auto listItem = host->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID_NOLOG(listItem);
    listItem->SetIndexInListItemGroup(indexInGroup);

    host = groupLayoutWrapper->GetHostNode();
    CHECK_NULL_VOID_NOLOG(host);
    auto listItemGroup = host->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID_NOLOG(listItemGroup);
    listItem->SetIndexInList(listItemGroup->GetIndexInList());
}

bool ListItemGroupLayoutAlgorithm::IsCardStyleForListItemGroup(const LayoutWrapper* groupLayoutWrapper)
{
    auto host = groupLayoutWrapper->GetHostNode();
    CHECK_NULL_RETURN(host, false);
    auto listItemGroup = host->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_RETURN(listItemGroup, false);
    return listItemGroup->GetListItemGroupStyle() == V2::ListItemGroupStyle::CARD;
}
} // namespace OHOS::Ace::NG
