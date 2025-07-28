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

#include "core/components_ng/pattern/list/list_item_layout_algorithm.h"

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/property/position_property.h"
#include "core/components_ng/property/measure_utils.h"
namespace OHOS::Ace::NG {

bool ListItemLayoutAlgorithm::IsRTLAndVertical(LayoutWrapper* layoutWrapper) const
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, false);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL && axis_ == Axis::VERTICAL) {
        return true;
    } else {
        return false;
    }
}

float ListItemLayoutAlgorithm::SetReverseValue(LayoutWrapper* layoutWrapper, float offset)
{
    if (IsRTLAndVertical(layoutWrapper)) {
        return -offset;
    } else {
        return offset;
    }
}

SizeF ListItemLayoutAlgorithm::GetContentSize(LayoutWrapper* layoutWrapper) const
{
    CHECK_NULL_RETURN(layoutWrapper, {});
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    return geometryNode->GetPaddingSize();
}

void ListItemLayoutAlgorithm::CheckAndUpdateCurOffset(LayoutWrapper* layoutWrapper)
{
    if (!canUpdateCurOffset_) {
        return;
    }
    float itemWidth = GetContentSize(layoutWrapper).CrossSize(axis_);
    if (NearEqual(itemWidth, childNodeSize_)) {
        return;
    }
    isCurOffsetUpdated_ = true;
    if (Positive(curOffset_) && startNodeIndex_ >= 0) {
        curOffset_ = itemWidth;
    } else if (Negative(curOffset_) && endNodeIndex_ >= 0) {
        curOffset_ = -itemWidth;
    }
}

void ListItemLayoutAlgorithm::MeasureItemChild(LayoutWrapper* layoutWrapper)
{
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    std::list<RefPtr<LayoutWrapper>> childList;
    auto layoutConstraint = layoutProperty->CreateChildConstraint();
    auto child = layoutWrapper->GetOrCreateChildByIndex(childNodeIndex_);
    if (child) {
        child->Measure(layoutConstraint);
        childList.push_back(child);
    }
    PerformMeasureSelfWithChildList(layoutWrapper, childList);
    CheckAndUpdateCurOffset(layoutWrapper);
}

void ListItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    layoutWrapper->RemoveAllChildInRenderTree();

    // step 1: measure item child node.
    MeasureItemChild(layoutWrapper);
    auto mainSize = layoutWrapper->GetGeometryNode()->GetPaddingSize().MainSize(axis_);
    if (NonPositive(mainSize)) {
        curOffset_ = 0.0f;
        return;
    }

    // step 2: measure swipeAction node.
    if (Positive(curOffset_) && startNodeIndex_ >= 0) {
        auto startLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        if (!NearZero(startNodeSize_) && curOffset_ > startNodeSize_) {
            startLayoutConstraint.maxSize.SetCrossSize(curOffset_, axis_);
            startLayoutConstraint.minSize.SetCrossSize(curOffset_, axis_);
        }
        startLayoutConstraint.maxSize.SetMainSize(mainSize, axis_);
        startLayoutConstraint.percentReference.SetMainSize(mainSize, axis_);
        auto startNode = layoutWrapper->GetOrCreateChildByIndex(startNodeIndex_);
        CHECK_NULL_VOID(startNode);
        startNode->Measure(startLayoutConstraint);
        if (NearZero(startNodeSize_) || curOffset_ < startNodeSize_) {
            startNodeSize_ = startNode->GetGeometryNode()->GetMarginFrameSize().CrossSize(axis_);
        }
        curOffset_ = NearZero(startNodeSize_) && !hasStartDeleteArea_ ? 0.0f : curOffset_;
    } else if (Negative(curOffset_) && endNodeIndex_ >= 0) {
        auto endLayoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        if (!NearZero(endNodeSize_) && -curOffset_ > endNodeSize_) {
            endLayoutConstraint.maxSize.SetCrossSize(-curOffset_, axis_);
            endLayoutConstraint.minSize.SetCrossSize(-curOffset_, axis_);
        }
        endLayoutConstraint.maxSize.SetMainSize(mainSize, axis_);
        endLayoutConstraint.percentReference.SetMainSize(mainSize, axis_);
        auto endNode = layoutWrapper->GetOrCreateChildByIndex(endNodeIndex_);
        CHECK_NULL_VOID(endNode);
        endNode->Measure(endLayoutConstraint);
        if (NearZero(endNodeSize_) || -curOffset_ < endNodeSize_) {
            endNodeSize_ = endNode->GetGeometryNode()->GetMarginFrameSize().CrossSize(axis_);
        }
        curOffset_ = NearZero(endNodeSize_) && !hasEndDeleteArea_ ? 0.0f : curOffset_;
    }
}

void ListItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto paddingOffset = padding.Offset();
    auto align = Alignment::CENTER;
    if (layoutProperty->GetPositionProperty()) {
        align = layoutProperty->GetPositionProperty()->GetAlignment().value_or(align);
    }

    SetSwipeActionNode(layoutWrapper, size, paddingOffset);
    auto child = layoutWrapper->GetOrCreateChildByIndex(childNodeIndex_);
    if (child) {
        auto translate =
            Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), align) + paddingOffset;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(SetReverseValue(layoutWrapper, curOffset_), 0.0f) :
            OffsetF(0.0f, curOffset_);
        child->GetGeometryNode()->SetMarginFrameOffset(translate + offset);
        child->Layout();
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = Alignment::GetAlignPosition(size, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

void ListItemLayoutAlgorithm::SetSwipeActionNode(
    LayoutWrapper* layoutWrapper, const SizeF& size, const OffsetF& paddingOffset)
{
    // Update child position.
    if (Positive(curOffset_) && startNodeIndex_ >= 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(startNodeIndex_);
        CHECK_NULL_VOID(child);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        float crossOffset = IsRTLAndVertical(layoutWrapper) ?
            (size.CrossSize(axis_) - curOffset_) : (curOffset_ - childSize.CrossSize(axis_));
        float mainOffset = (size.MainSize(axis_) - childSize.MainSize(axis_)) / 2;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(crossOffset, mainOffset) : OffsetF(mainOffset, crossOffset);
        child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
        child->Layout();
    } else if (Negative(curOffset_) && endNodeIndex_ >= 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(endNodeIndex_);
        CHECK_NULL_VOID(child);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        float crossOffset = IsRTLAndVertical(layoutWrapper) ?
            (-curOffset_ - childSize.CrossSize(axis_)) : (size.CrossSize(axis_) + curOffset_);
        float mainOffset = (size.MainSize(axis_) - childSize.MainSize(axis_)) / 2;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(crossOffset, mainOffset) : OffsetF(mainOffset, crossOffset);
        child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
        child->Layout();
    }
}
} // namespace OHOS::Ace::NG