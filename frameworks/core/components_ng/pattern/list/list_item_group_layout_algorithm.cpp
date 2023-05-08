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
#include "core/components_ng/pattern/list/list_item_group_layout_property.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/pattern/list/list_item_pattern.h"
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ListItemGroupLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    CHECK_NULL_VOID(listLayoutProperty_);
    auto layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(frameNode->GetLayoutProperty());
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
    UpdateListItemConstraint(contentIdealSize, itemLayoutConstraint);
    auto headerFooterLayoutConstraint = layoutProperty->CreateChildConstraint();
    headerFooterLayoutConstraint.maxSize.SetMainSize(Infinity<float>(), axis_);
    spaceWidth_ = ConvertToPx(space, layoutConstraint.scaleProperty, mainPercentRefer).value_or(0);
    if (layoutProperty->GetDivider().has_value()) {
        auto divider = layoutProperty->GetDivider().value();
        std::optional<float> dividerSpace =
            ConvertToPx(divider.strokeWidth, layoutConstraint.scaleProperty, mainPercentRefer);
        if (dividerSpace.has_value()) {
            spaceWidth_ = std::max(spaceWidth_, dividerSpace.value());
        }
    }
    UpdateReferencePos(layoutProperty);
    totalItemCount_ = frameNode->TotalChildCount() - itemStartIndex_;

    totalMainSize_ = frameNode->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    if (headerIndex_ >= 0) {
        auto header = frameNode->GetFrameNodeByIndex(headerIndex_);
        header->Measure(headerFooterLayoutConstraint);
        headerMainSize_ = GetMainAxisSize(header->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    if (footerIndex_ >= 0) {
        auto footer = frameNode->GetFrameNodeByIndex(footerIndex_);
        footer->Measure(headerFooterLayoutConstraint);
        footerMainSize_ = GetMainAxisSize(footer->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    totalMainSize_ = std::max(totalMainSize_, headerMainSize_ + footerMainSize_);
    MeasureListItem(frameNode, itemLayoutConstraint);
    if (!itemPosition_.empty()) {
        if (GetEndIndex() == totalItemCount_ - 1) {
            totalMainSize_ = GetEndPosition() + footerMainSize_;
        } else {
            totalMainSize_ = std::max(totalMainSize_, GetEndPosition() + footerMainSize_);
        }
    }

    auto crossSize = contentIdealSize.CrossSize(axis_);
    if (crossSize.has_value() && GreaterOrEqualToInfinity(crossSize.value())) {
        contentIdealSize.SetCrossSize(GetChildMaxCrossSize(frameNode, axis_), axis_);
    }
    contentIdealSize.SetMainSize(totalMainSize_, axis_);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentIdealSize);
    frameNode->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());
    // frameNode->SetCacheCount(listLayoutProperty_->GetCachedCountValue(1) * lanes_);
}

void ListItemGroupLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    const auto& layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto size = frameNode->GetGeometryNode()->GetFrameSize();
    auto padding = frameNode->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0.0f);
    auto top = padding.top.value_or(0.0f);
    auto paddingOffset = OffsetF(left, top);
    float crossSize = GetCrossAxisSize(size, axis_);
    CHECK_NULL_VOID(listLayoutProperty_);
    itemAlign_ = listLayoutProperty_->GetListItemAlign().value_or(V2::ListItemAlign::START);

    if (headerIndex_ >= 0 || footerIndex_ >= 0) {
        LayoutHeaderFooter(frameNode, paddingOffset, crossSize);
    }
    // layout items.
    LayoutListItem(frameNode, paddingOffset, crossSize);
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
            crossSize /= lanes_;
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

float ListItemGroupLayoutAlgorithm::GetChildMaxCrossSize(FrameNode* frameNode, Axis axis)
{
    float maxCrossSize = 0.0f;
    for (const auto& pos : itemPosition_) {
        auto child = frameNode->GetFrameNodeByIndex(pos.first, false);
        if (!child) {
            continue;
        }
        auto getGeometryNode = child->GetGeometryNode();
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

void ListItemGroupLayoutAlgorithm::MeasureListItem(
    FrameNode* frameNode, const LayoutConstraintF& layoutConstraint)
{
    if (totalItemCount_ <= 0) {
        totalMainSize_ = headerMainSize_ + footerMainSize_;
        frameNode->RemoveAllChildInRenderTree();
        itemPosition_.clear();
        return;
    }
    int32_t startIndex = 0;
    int32_t endIndex = totalItemCount_ - 1;
    float startPos = headerMainSize_;
    float endPos = totalMainSize_ - footerMainSize_;
    if (jumpIndex_.has_value()) {
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
        frameNode->RemoveAllChildInRenderTree();
        jumpIndex_.reset();
    } else if (!itemPosition_.empty()) {
        if (itemPosition_.begin()->first > 0) {
            startPos = itemPosition_.begin()->second.first;
        }
        endPos = itemPosition_.rbegin()->second.second;
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        itemPosition_.clear();
        frameNode->RemoveAllChildInRenderTree();
    } else if (!NeedMeasureItem()) {
        frameNode->RemoveAllChildInRenderTree();
        itemPosition_.clear();
        return;
    }
    LOGD("referencePos_ is %{public}f, startPos_: %{public}f, endPos_: %{public}f, forward:%{public}d",
        referencePos_, startPos_, endPos_, forwardLayout_);
    if (forwardLayout_) {
        LOGD("startIndex:%{public}d, startPos:%{public}f", startIndex, startPos);
        MeasureForward(frameNode, layoutConstraint, startIndex, startPos);
    } else {
        LOGD("endIndex:%{public}d, endPos:%{public}f", endIndex, endPos);
        MeasureBackward(frameNode, layoutConstraint, endIndex, endPos);
    }
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineForward(FrameNode* frameNode,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float startPos, float& endPos)
{
    float mainLen = 0.0f;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    if (lanesChanged_) {
        lanesChanged_ = false;
        currentIndex = GetLanesFloor(currentIndex + 1) - 1;
    }
    for (int32_t i = 0; i < lanes && currentIndex + 1 <= totalItemCount_; i++) {
        auto child = frameNode->GetFrameNodeByIndex(currentIndex + 1 + itemStartIndex_);
        if (!child) {
            break;
        }
        cnt++;
        ++currentIndex;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            child->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(child->GetGeometryNode()->GetMarginFrameSize(), axis_));
    }
    if (cnt > 0) {
        endPos = startPos + mainLen;
        for (int32_t i = 0; i < cnt; i++) {
            itemPosition_[currentIndex - i] = { startPos, endPos };
        }
    }
    return cnt;
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALineBackward(FrameNode* frameNode,
    const LayoutConstraintF& layoutConstraint, int32_t& currentIndex, float endPos, float& startPos)
{
    float mainLen = 0.0f;
    int32_t cnt = 0;
    int32_t lanes = lanes_ > 1 ? lanes_ : 1;
    for (int32_t i = 0; i < lanes && currentIndex - 1 >= 0; i++) {
        auto child = frameNode->GetFrameNodeByIndex(currentIndex - 1 + itemStartIndex_);
        if (!child) {
            break;
        }
        --currentIndex;
        cnt++;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem:%d", currentIndex);
            child->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(child->GetGeometryNode()->GetMarginFrameSize(), axis_));
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

void ListItemGroupLayoutAlgorithm::MeasureForward(FrameNode* frameNode,
    const LayoutConstraintF& layoutConstraint, int32_t startIndex, float startPos)
{
    float currentEndPos = startPos;
    float currentStartPos = 0.0f;
    int32_t currentIndex = startIndex - 1;
    while (LessOrEqual(currentEndPos, endPos_ - referencePos_)) {
        currentStartPos = currentEndPos;
        int32_t count = MeasureALineForward(frameNode, layoutConstraint, currentIndex,
            currentStartPos, currentEndPos);
        if (count == 0) {
            break;
        }
        if (currentIndex < (totalItemCount_ - 1)) {
            currentEndPos += spaceWidth_;
        }
        LOGD("LayoutForward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
    }

    currentStartPos = startPos - spaceWidth_;
    currentIndex = startIndex;
    while (currentIndex > 0  && GreatOrEqual(currentStartPos, startPos_ - referencePos_)) {
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(frameNode, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
    }
}

void ListItemGroupLayoutAlgorithm::MeasureBackward(FrameNode* frameNode,
    const LayoutConstraintF& layoutConstraint, int32_t endIndex, float endPos)
{
    float currentStartPos = endPos;
    float currentEndPos = 0.0f;
    auto currentIndex = endIndex + 1;
    while (GreatOrEqual(currentStartPos, startPos_ - (referencePos_ - totalMainSize_))) {
        currentEndPos = currentStartPos;
        int32_t count = MeasureALineBackward(frameNode, layoutConstraint, currentIndex,
            currentEndPos, currentStartPos);
        if (count == 0) {
            break;
        }
        if (currentIndex > 0) {
            currentStartPos = currentStartPos - spaceWidth_;
        }
        LOGD("LayoutBackward: %{public}d current start pos: %{public}f, current end pos: %{public}f", currentIndex,
            currentStartPos, currentEndPos);
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
    const RefPtr<FrameNode>& frameNode, float startPos, float endPos, float referencePos, bool forwardLayout)
{
    // Mark inactive in wrapper.
    if (forwardLayout) {
        for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
            if (GreatOrEqual(pos->second.second, startPos - referencePos)) {
                break;
            }
            LOGI("recycle item:%{public}d", pos->first);
            frameNode->RemoveChildInRenderTree(pos->first);
            itemPosition_.erase(pos++);
        }
        return;
    }
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessOrEqual(pos->second.first, endPos - (referencePos - totalMainSize_))) {
            break;
        }
        frameNode->RemoveChildInRenderTree(pos->first);
        removeIndexes.emplace_back(pos->first);
    }
    for (const auto& index : removeIndexes) {
        itemPosition_.erase(index);
    }
}

void ListItemGroupLayoutAlgorithm::LayoutListItem(FrameNode* frameNode,
    const OffsetF& paddingOffset, float crossSize)
{
    // layout items.
    for (auto& pos : itemPosition_) {
        auto child = frameNode->GetFrameNodeByIndex(pos.first + itemStartIndex_);
        if (!child) {
            LOGI("wrapper is out of boundary");
            continue;
        }

        auto offset = paddingOffset;
        int32_t laneIndex = pos.first % lanes_;
        float childCrossSize = GetCrossAxisSize(child->GetGeometryNode()->GetMarginFrameSize(), axis_);
        float laneCrossOffset = CalculateLaneCrossOffset(crossSize / lanes_, childCrossSize);
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(0, pos.second.first) + OffsetF(laneCrossOffset, 0) +
                OffsetF(crossSize / lanes_ * laneIndex, 0);
        } else {
            offset = offset + OffsetF(pos.second.first, 0) + OffsetF(laneCrossOffset, 0) +
                OffsetF(0, crossSize / lanes_ * laneIndex);
        }
        SetListItemIndex(frameNode, child, pos.first);
        child->GetGeometryNode()->SetMarginFrameOffset(offset);
        child->Layout();
    }
}

void ListItemGroupLayoutAlgorithm::LayoutHeaderFooter(FrameNode* frameNode,
    const OffsetF& paddingOffset, float crossSize)
{
    OffsetF selfOffset = frameNode->GetGeometryNode()->GetPaddingOffset();
    selfOffset = selfOffset - listLayoutProperty_->CreatePaddingAndBorder().Offset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_);
    float headerMainSize = 0.0f;
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    if (headerIndex_ >= 0) {
        auto child = frameNode->GetFrameNodeByIndex(headerIndex_);
        CHECK_NULL_VOID(child);
        headerMainSize = child->GetGeometryNode()->GetFrameSize().MainSize(axis_);
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
        LayoutIndex(child, paddingOffset, crossSize, headerPos);
    }

    if (footerIndex_ >= 0) {
        float endPos = totalMainSize_ - footerMainSize_;
        auto child = frameNode->GetFrameNodeByIndex(footerIndex_);
        CHECK_NULL_VOID(child);
        float const listMainSize = endPos_ - startPos_;
        if (Positive(listMainSize) && (sticky == V2::StickyStyle::BOTH || sticky == V2::StickyStyle::FOOTER)) {
            auto footerMainSize = child->GetGeometryNode()->GetFrameSize().MainSize(axis_);
            float stickyPos = listMainSize - mainPos - footerMainSize;
            if (stickyPos < headerMainSize) {
                stickyPos = headerMainSize;
            }
            if (stickyPos < endPos) {
                endPos = stickyPos;
            }
        }
        LayoutIndex(child, paddingOffset, crossSize, endPos);
    }
}

void ListItemGroupLayoutAlgorithm::LayoutIndex(const RefPtr<FrameNode>& frameNode, const OffsetF& paddingOffset,
    float crossSize, float startPos)
{
    CHECK_NULL_VOID_NOLOG(frameNode);
    auto offset = paddingOffset;
    float childCrossSize = GetCrossAxisSize(frameNode->GetGeometryNode()->GetMarginFrameSize(), axis_);
    float laneCrossOffset = CalculateLaneCrossOffset(crossSize, childCrossSize);
    if (axis_ == Axis::VERTICAL) {
        offset = offset + OffsetF(laneCrossOffset, startPos);
    } else {
        offset = offset + OffsetF(startPos, laneCrossOffset);
    }
    frameNode->GetGeometryNode()->SetMarginFrameOffset(offset);
    frameNode->Layout();
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
    }
    lanes = ListLanesLayoutAlgorithm::CalculateLanesParam(minLaneLength_, maxLaneLength_, lanes, crossSizeOptional);
    if (lanes_ != lanes) {
        lanes_ = lanes;
        lanesChanged_ = true;
    }
}

void ListItemGroupLayoutAlgorithm::SetListItemIndex(const FrameNode* group,
    const RefPtr<FrameNode>& item, int32_t indexInGroup)
{
    auto listItem = item->GetPattern<ListItemPattern>();
    CHECK_NULL_VOID_NOLOG(listItem);
    listItem->SetIndexInListItemGroup(indexInGroup);

    auto listItemGroup = group->GetPattern<ListItemGroupPattern>();
    CHECK_NULL_VOID_NOLOG(listItemGroup);
    listItem->SetIndexInList(listItemGroup->GetIndexInList());
}
} // namespace OHOS::Ace::NG