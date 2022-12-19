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

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components_ng/layout/box_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
void ListItemLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    layoutWrapper->RemoveAllChildInRenderTree();
    if (Positive(curOffset_) && startNodeIndex_ >= 0) {
        auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        if (!NearZero(startNodeSize_) && curOffset_ > startNodeSize_) {
            layoutConstraint.maxSize.SetCrossSize(curOffset_, axis_);
            layoutConstraint.minSize.SetCrossSize(curOffset_, axis_);
        }
        auto child = layoutWrapper->GetOrCreateChildByIndex(startNodeIndex_);
        CHECK_NULL_VOID(child);
        child->Measure(layoutConstraint);
        if (NearZero(startNodeSize_)) {
            startNodeSize_ = child->GetGeometryNode()->GetMarginFrameSize().CrossSize(axis_);
        }
    } else if (Negative(curOffset_) && endNodeIndex_ >= 0) {
        auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
        if (!NearZero(endNodeSize_) && -curOffset_ > endNodeSize_) {
            layoutConstraint.maxSize.SetCrossSize(-curOffset_, axis_);
            layoutConstraint.minSize.SetCrossSize(-curOffset_, axis_);
        }
        auto child = layoutWrapper->GetOrCreateChildByIndex(endNodeIndex_);
        CHECK_NULL_VOID(child);
        child->Measure(layoutConstraint);
        if (NearZero(endNodeSize_)) {
            endNodeSize_ = child->GetGeometryNode()->GetMarginFrameSize().CrossSize(axis_);
        }
    }
    std::list<RefPtr<LayoutWrapper>> childList;
    auto layoutConstraint = layoutWrapper->GetLayoutProperty()->CreateChildConstraint();
    auto child = layoutWrapper->GetOrCreateChildByIndex(childNodeIndex_);
    if (child) {
        child->Measure(layoutConstraint);
        childList.push_back(child);
    }
    PerformMeasureSelfWithChildList(layoutWrapper, childList);
}

void ListItemLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto paddingOffset = padding.Offset();
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }

    // Update child position.
    if (Positive(curOffset_) && startNodeIndex_ >= 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(startNodeIndex_);
        CHECK_NULL_VOID(child);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        float crossOffset = curOffset_ - childSize.CrossSize(axis_);
        float mainOffset = (size.MainSize(axis_) - childSize.MainSize(axis_)) / 2;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(crossOffset, mainOffset) : OffsetF(mainOffset, crossOffset);
        child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
        child->Layout();
    } else if (Negative(curOffset_) && endNodeIndex_ >= 0) {
        auto child = layoutWrapper->GetOrCreateChildByIndex(endNodeIndex_);
        CHECK_NULL_VOID(child);
        auto childSize = child->GetGeometryNode()->GetMarginFrameSize();
        float crossOffset = size.CrossSize(axis_) + curOffset_;
        float mainOffset = (size.MainSize(axis_) - childSize.MainSize(axis_)) / 2;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(crossOffset, mainOffset) : OffsetF(mainOffset, crossOffset);
        child->GetGeometryNode()->SetMarginFrameOffset(paddingOffset + offset);
        child->Layout();
    }
    auto child = layoutWrapper->GetOrCreateChildByIndex(childNodeIndex_);
    if (child) {
        auto translate =
            Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), align) + paddingOffset;
        OffsetF offset = axis_ == Axis::VERTICAL ? OffsetF(curOffset_, 0.0f) : OffsetF(0.0f, curOffset_);
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
} // namespace OHOS::Ace::NG