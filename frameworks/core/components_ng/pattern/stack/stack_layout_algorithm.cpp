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

#include "frameworks/core/components_ng/pattern/stack/stack_layout_algorithm.h"

#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {

StackLayoutAlgorithm::StackLayoutAlgorithm() = default;

void StackLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    PerformLayout(layoutWrapper);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}

// Called to perform layout render node and child.
void StackLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper)
{
    // update child position.
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    auto contentSize = frameSize;
    MinusPaddingToSize(padding, contentSize);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    auto layoutProperty = DynamicCast<StackLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        auto rawAlign = layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER);
        align = Alignment::GetAlignment(layoutDirection, rawAlign.GetAlignmentStr(TextDirection::AUTO));
    }
    // Update child position.
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto childNode = child->GetHostNode();
        auto host = layoutWrapper->GetHostNode();
        auto childAlign = align;
        auto childLayoutProperty = child->GetLayoutProperty();
        if (childLayoutProperty && childLayoutProperty->GetPositionProperty() &&
            childLayoutProperty->GetPositionProperty()->HasLayoutGravity()) {
            auto rawChildAlign =
                childLayoutProperty->GetPositionProperty()->GetLayoutGravity().value_or(Alignment::CENTER);
            childAlign = Alignment::GetAlignment(layoutDirection, rawChildAlign.GetAlignmentStr(TextDirection::AUTO));
        }
        if (host && childNode && childNode->GetLayoutProperty() &&
            childNode->GetLayoutProperty()->IsIgnoreOptsValid()) {
            IgnoreLayoutSafeAreaOpts& opts = *(childNode->GetLayoutProperty()->GetIgnoreLayoutSafeAreaOpts());
            auto sae = host->GetAccumulatedSafeAreaExpand(true, opts);
            auto adjustContentSize = contentSize + sae.Size();
            auto translate =
                CalculateStackAlignment(adjustContentSize, child->GetGeometryNode()->GetMarginFrameSize(), childAlign) +
                paddingOffset;
            translate -= sae.Offset();
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        } else {
            auto translate =
                CalculateStackAlignment(contentSize, child->GetGeometryNode()->GetMarginFrameSize(), childAlign) +
                paddingOffset;
            child->GetGeometryNode()->SetMarginFrameOffset(translate);
        }
    }
    // Update content position.
    const auto& content = layoutWrapper->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = CalculateStackAlignment(contentSize, content->GetRect().GetSize(), align) + paddingOffset;
        content->SetOffset(translate);
    }
}

NG::OffsetF StackLayoutAlgorithm::CalculateStackAlignment(
    const NG::SizeF& parentSize, const NG::SizeF& childSize, const Alignment& alignment)
{
    NG::OffsetF offset;
    offset.SetX((1.0 + alignment.GetHorizontal()) * (parentSize.Width() - childSize.Width()) / 2.0);
    offset.SetY((1.0 + alignment.GetVertical()) * (parentSize.Height() - childSize.Height()) / 2.0);
    return offset;
}
} // namespace OHOS::Ace::NG
