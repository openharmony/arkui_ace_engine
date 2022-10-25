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

#include "core/components_ng/pattern/list/list_item_group_layout_property.h"

namespace OHOS::Ace::NG {

void ListItemGroupLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = AceType::DynamicCast<ListItemGroupLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto contentConstraint = layoutProperty->GetContentLayoutConstraint().value();
    auto contentIdealSize = CreateIdealSize(
        contentConstraint, axis_, layoutProperty->GetMeasureType(MeasureType::MATCH_PARENT_CROSS_AXIS));

    axis_ = layoutProperty->GetListDirection().value_or(Axis::VERTICAL);
    lanes_ = layoutProperty->GetLanes().value_or(1);
    auto mainPercentRefer = GetMainAxisSize(contentConstraint.percentReference, axis_);
    auto space = layoutProperty->GetSpace().value_or(Dimension(0));

    auto layoutConstraint = layoutProperty->GetLayoutConstraint().value();
    auto itemLayoutConstraint = layoutProperty->GetLayoutConstraint().value();
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

    if (headerIndex_ >= 0) {
        auto headerWrapper = layoutWrapper->GetOrCreateChildByIndex(headerIndex_);
        headerWrapper->Measure(layoutConstraint);
        headerMainSize_ = GetMainAxisSize(headerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    float totalMainSize = MeasureListItem(layoutWrapper, itemLayoutConstraint, headerMainSize_);
    if (footerIndex_ >= 0) {
        auto footerWrapper = layoutWrapper->GetOrCreateChildByIndex(footerIndex_);
        footerWrapper->Measure(layoutConstraint);
        totalMainSize += GetMainAxisSize(footerWrapper->GetGeometryNode()->GetMarginFrameSize(), axis_);
    }
    if (axis_ == Axis::HORIZONTAL) {
        contentIdealSize.SetWidth(totalMainSize);
    } else {
        contentIdealSize.SetHeight(totalMainSize);
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

    if (headerIndex_ >= 0) {
        LayoutIndex(layoutWrapper, paddingOffset, headerIndex_, crossSize, 0.0f);
    }

    // layout items.
    LayoutListItem(layoutWrapper, paddingOffset, crossSize);

    if (footerIndex_ >= 0) {
        float endPos = itemPosition_.empty() ? headerMainSize_ : itemPosition_.rbegin()->second.second;
        LayoutIndex(layoutWrapper, paddingOffset, footerIndex_, crossSize, endPos);
    }
}

void ListItemGroupLayoutAlgorithm::UpdateListItemConstraint(const OptionalSizeF& selfIdealSize,
    LayoutConstraintF& contentConstraint)
{
    contentConstraint.parentIdealSize = selfIdealSize;
    if (axis_ == Axis::VERTICAL) {
        contentConstraint.maxSize.SetHeight(Infinity<float>());
        auto width = selfIdealSize.Width();
        if (width.has_value()) {
            float crossSize = width.value() / lanes_;
            contentConstraint.percentReference.SetWidth(crossSize);
            contentConstraint.parentIdealSize.SetWidth(crossSize);
            contentConstraint.maxSize.SetWidth(crossSize);
        }
        return;
    }
    contentConstraint.maxSize.SetWidth(Infinity<float>());
    auto height = selfIdealSize.Height();
    if (height.has_value()) {
        float crossSize = height.value() / lanes_;
        contentConstraint.percentReference.SetHeight(crossSize);
        contentConstraint.parentIdealSize.SetHeight(crossSize);
        contentConstraint.maxSize.SetHeight(crossSize);
    }
}

int32_t ListItemGroupLayoutAlgorithm::MeasureALine(LayoutWrapper* layoutWrapper, const LayoutConstraintF& layoutConstraint,
    int32_t currentIndex, float& mainLen)
{
    int32_t cnt = 0;
    for (int32_t i = 0; i < lanes_; i++) {
        auto wrapper = GetListItem(layoutWrapper, currentIndex + i);
        if (!wrapper) {
            LOGI("the start %{public}d index wrapper is null", currentIndex + 1);
            return cnt;
        }
        cnt++;
        {
            ACE_SCOPED_TRACE("ListLayoutAlgorithm::MeasureListItem");
            wrapper->Measure(layoutConstraint);
        }
        mainLen = std::max(mainLen, GetMainAxisSize(wrapper->GetGeometryNode()->GetMarginFrameSize(), axis_));
    }
    return cnt;
}

float ListItemGroupLayoutAlgorithm::MeasureListItem(LayoutWrapper* layoutWrapper,
    const LayoutConstraintF& layoutConstraint, float startPos)
{
    itemPosition_.clear();
    float totalMainSize = startPos;
    auto totalItemCount = layoutWrapper->GetTotalChildCount();
    int32_t currentIndex = 0;
    while (currentIndex < totalItemCount) {
        float mainLength = 0.0f;
        int32_t cnt = MeasureALine(layoutWrapper, layoutConstraint, currentIndex, mainLength);
        if (cnt == 0) {
            break;
        }
        float endPos = totalMainSize + mainLength;
        for (int32_t i = 0; i < cnt; i++) {
            itemPosition_[currentIndex + i] = { totalMainSize, endPos};
        }
        totalMainSize = endPos + spaceWidth_;
        currentIndex += cnt;
    }
    if (currentIndex > 0) {
        totalMainSize -= spaceWidth_;
    }
    return totalMainSize;
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

void ListItemGroupLayoutAlgorithm::LayoutIndex(LayoutWrapper* layoutWrapper, const OffsetF& paddingOffset,
    int32_t index, float crossSize, float startPos)
{
    auto wrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    if (wrapper) {
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
} // namespace OHOS::Ace::NG