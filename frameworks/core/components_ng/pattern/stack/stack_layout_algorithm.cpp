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

#include "core/common/ace_application_info.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"

namespace OHOS::Ace::NG {

StackLayoutAlgorithm::StackLayoutAlgorithm() = default;

void StackLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    PerformLayout(frameNode);
    for (auto&& child : frameNode->GetAllFrameNodeChildren()) {
        child->Layout();
    }
}

// Called to perform layout render node and child.
void StackLayoutAlgorithm::PerformLayout(FrameNode* frameNode)
{
    // update child position.
    auto size = frameNode->GetGeometryNode()->GetFrameSize();
    const auto& padding = frameNode->GetLayoutProperty()->CreatePaddingAndBorder();
    auto layoutDirection = frameNode->GetLayoutProperty()->GetLayoutDirection();
    if (layoutDirection == TextDirection::AUTO) {
        layoutDirection = AceApplicationInfo::GetInstance().IsRightToLeft() ? TextDirection::RTL : TextDirection::LTR;
    }
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    auto layoutProperty = DynamicCast<StackLayoutProperty>(frameNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->HasAlignmentContent()) {
        align = layoutProperty->GetAlignmentContent().value_or(Alignment::CENTER);
    }
    if (layoutProperty->HasAlignment()) {
        align = layoutProperty->GetAlignment().value_or(Alignment::CENTER);
    }
    // Update child position.
    for (const auto& child : frameNode->GetAllFrameNodeChildren()) {
        auto translate =
            CalculateStackAlignment(size, child->GetGeometryNode()->GetMarginFrameSize(), align) + paddingOffset;
        if (layoutDirection == TextDirection::RTL) {
            translate.SetX(size.Width() - translate.GetX() - child->GetGeometryNode()->GetMarginFrameSize().Width());
        }
        child->GetGeometryNode()->SetMarginFrameOffset(translate);
    }
    // Update content position.
    const auto& content = frameNode->GetGeometryNode()->GetContent();
    if (content) {
        auto translate = CalculateStackAlignment(size, content->GetRect().GetSize(), align) + paddingOffset;
        if (layoutDirection == TextDirection::RTL) {
            translate.SetX(size.Width() - translate.GetX() - content->GetRect().GetSize().Width());
        }
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
