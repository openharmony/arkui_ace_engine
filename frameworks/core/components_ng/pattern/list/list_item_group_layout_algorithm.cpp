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
#include "core/components_ng/pattern/list/list_lanes_layout_algorithm.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

void ListItemGroupLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(listLayoutProperty_);
    auto layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    axis_ = listLayoutProperty_->GetListDirection().value_or(Axis::VERTICAL);
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis_);
    auto space = layoutProperty->GetSpace().value_or(Dimension(0));

    auto layoutConstraint = layoutProperty->GetLayoutConstraint().value();
    CalculateLanes(listLayoutProperty_, layoutConstraint, contentIdealSize.CrossSize(axis_), axis_);
    auto itemLayoutConstraint = layoutProperty->CreateChildConstraint();
    UpdateListItemConstraint(contentIdealSize, itemLayoutConstraint);
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
    totalItemCount_ = layoutWrapper->GetTotalChildCount() - itemStartIndex_;

    totalMainSize_ = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    if (headerIndex_ >= 0) {
        auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        headerWrapper->Measure(layoutProperty->CreateChildConstraint());
        headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    if (footerIndex_ >= 0) {
        auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        footerWrapper->Measure(layoutProperty->CreateChildConstraint());
        footerMainSize_ = GetMainAxisSize(footerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    totalMainSize_ = std::max(totalMainSize_, headerMainSize_ + footerMainSize_);
    MeasureListItem(layoutWrapper, itemLayoutConstraint);
    if (GetEndIndex() == totalItemCount_ - 1) {
        totalMainSize_ = GetEndPosition() + footerMainSize_;
    } else {
        totalMainSize_ = std::max(totalMainSize_, GetEndPosition() + footerMainSize_);
    }

    if (axis_ == Axis::HORIZONTAL) {
        contentIdealSize.SetWidth(totalMainSize_);
    } else {
        contentIdealSize.SetHeight(totalMainSize_);
    }

    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    AddPaddingToSize(padding, contentIdealSize);
    layoutWrapper->GetGeometryNode()->SetFrameSize(contentIdealSize.ConvertToSizeT());
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

void ListItemGroupLayoutAlgorithm::MeasureListItem(
    LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint)
{
    int32_t startIndex = 0;
    int32_t endIndex = totalItemCount_ - 1;
    float startPos = headerMainSize_;
    float endPos = totalMainSize_ - footerMainSize_;
    if (!itemPosition_.empty()) {
        startPos = itemPosition_.begin()->second.first;
        endPos = itemPosition_.rbegin()->second.second;
        startIndex = std::min(GetStartIndex(), totalItemCount_ - 1);
        endIndex = std::min(GetEndIndex(), totalItemCount_ - 1);
        itemPosition_.clear();
        layoutWrapper->RemoveAllChildInRenderTree();
    } else {
        if (forwardLayout_ && footerIndex_ >= 0) {
            if (LessOrEqual(totalMainSize_ - footerMainSize_, startPos_ - referencePos_)) {
                return;
            }
        }
        if (!forwardLayout_ && headerIndex_ >= 0) {
            if (GreatOrEqual(headerMainSize_, endPos_ - (referencePos_ - totalMainSize_))) {
                return;
            }
        }
    }
    LOGD("referencePos_ is %{public}f, startPos_: %{public}f, endPos_: %{public}f, forward:%{public}d",
        referencePos_, startPos_, endPos_, forwardLayout_);
    if (forwardLayout_) {
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
    if (lanesChanged_) {
        lanesChanged_ = false;
        currentIndex = GetLanesFloor(currentIndex + 1) - 1;
    }
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
    }

    // Mark inactive in wrapper.
    for (auto pos = itemPosition_.begin(); pos != itemPosition_.end();) {
        if (GreatOrEqual(pos->second.second, startPos_ - referencePos_)) {
            break;
        }
        LOGI("recycle item:%{public}d", pos->first);
        layoutWrapper->RemoveChildInRenderTree(pos->first);
        itemPosition_.erase(pos++);
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

    // Mark inactive in wrapper.
    std::list<int32_t> removeIndexes;
    for (auto pos = itemPosition_.rbegin(); pos != itemPosition_.rend(); ++pos) {
        if (LessOrEqual(pos->second.first, endPos_ - (referencePos_ - totalMainSize_))) {
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
        float laneCrossOffset = CalculateLaneCrossOffset(crossSize / lanes_, childCrossSize);
        if (axis_ == Axis::VERTICAL) {
            offset = offset + OffsetF(0, pos.second.first) + OffsetF(laneCrossOffset, 0) +
                OffsetF(crossSize / lanes_ * laneIndex, 0);
        } else {
            offset = offset + OffsetF(pos.second.first, 0) + OffsetF(laneCrossOffset, 0) +
                OffsetF(0, crossSize / lanes_ * laneIndex);
        }
        wrapper->GetGeometryNode()->SetMarginFrameOffset(offset);
        wrapper->Layout();
    }
}

void ListItemGroupLayoutAlgorithm::LayoutHeaderFooter(LayoutWrapper* layoutWrapper,
    const OffsetF& paddingOffset, float crossSize)
{
    CHECK_NULL_VOID(listLayoutProperty_);
    OffsetF selfOffset = layoutWrapper->GetGeometryNode()->GetPaddingOffset();
    float mainPos = GetMainAxisOffset(selfOffset, axis_);
    float headerMainSize = 0.0f;
    V2::StickyStyle sticky = listLayoutProperty_->GetStickyStyle().value_or(V2::StickyStyle::NONE);
    itemAlign_ = listLayoutProperty_->GetListItemAlign().value_or(V2::ListItemAlign::START);
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
    CHECK_NULL_VOID(wrapper);
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
    }
    lanes = ListLanesLayoutAlgorithm::CalculateLanesParam(minLaneLength_, maxLaneLength_, lanes, crossSizeOptional);
    if (lanes_ != lanes) {
        lanes_ = lanes;
        lanesChanged_ = true;
    }
}
} // namespace OHOS::Ace::NG