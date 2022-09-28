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

#include "core/components_ng/pattern/marquee/marquee_layout_algorithm.h"

#include "base/geometry/ng/offset_t.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MarqueeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();

    // measure child.
    LayoutConstraintF textLayoutConstraint;
    textLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(Infinity<float>(), maxSize.Height()));
    textLayoutConstraint.UpdateMinSizeWithCheck(minSize);
    for (auto&& child : layoutWrapper->GetAllChildrenWithBuild()) {
        child->Measure(textLayoutConstraint);
    }

    // measure self.
    OptionalSizeF frameSize;
    do {
        // Use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
            if (frameSize.IsValid()) {
                frameSize.Constrain(minSize, maxSize);
                break;
            }
        } else {
            // use the max child size.
            auto childFrame = SizeF(-1, -1);
            for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
                auto childSize = child->GetGeometryNode()->GetFrameSize();
                childFrame = childFrame > childSize ? childFrame : childSize;
            }
            childFrame.Constrain(minSize, maxSize);
            AddPaddingToSize(padding, childFrame);
            frameSize.UpdateIllegalSizeWithCheck(childFrame);
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);

    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    if (isNeedMarquee_) {
        PerformLayout(layoutWrapper);
    } else {
        BoxLayoutAlgorithm::Layout(layoutWrapper);
    }
}

// Called to perform layout render node and child.
void MarqueeLayoutAlgorithm::PerformLayout(LayoutWrapper* layoutWrapper) const
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update child position.
    auto childPosition = OffsetF(childOffset_, 0.0);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        auto translate =
            Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetFrameSize(), align) + paddingOffset;
        child->GetGeometryNode()->SetFrameOffset(translate + childPosition);
    }
}
} // namespace OHOS::Ace::NG
