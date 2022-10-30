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
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
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
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    auto lastChildFrame = child->GetGeometryNode()->GetMarginFrameSize();
    // measure child.
    LayoutConstraintF textLayoutConstraint;
    textLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(Infinity<float>(), maxSize.Height()));
    textLayoutConstraint.UpdateMinSizeWithCheck(minSize);
    child->Measure(textLayoutConstraint);

    // measure self.
    OptionalSizeF frameSize;
    SizeF childFrameSize;
    auto lastMarqueeFrame = layoutWrapper->GetGeometryNode()->GetFrameSize();
    do {
        // Use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            childFrameSize = lastChildFrame;
            break;
        }

        if (measureType == MeasureType::MATCH_PARENT) {
            frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
            if (frameSize.IsValid()) {
                frameSize.Constrain(minSize, maxSize);
                break;
            }
        } else {
            // use the child size.
            auto childFrame = child->GetGeometryNode()->GetMarginFrameSize();
            childFrameSize = childFrame;
            childFrame.Constrain(SizeF(Infinity<float>(), minSize.Height()), maxSize);
            AddPaddingToSize(padding, childFrame);
            frameSize.UpdateIllegalSizeWithCheck(childFrame);
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);
    
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
    if (lastChildFrame != childFrameSize || lastMarqueeFrame != frameSize.ConvertToSizeT()) {
        auto pattern = layoutWrapper->GetHostNode()->GetPattern<MarqueePattern>();
        childOffset_ = pattern->CheckAndAdjustPosition(layoutWrapper);
    }
}

// Called to perform layout render node and child.
void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
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
            Alignment::GetAlignPosition(size, child->GetGeometryNode()->GetMarginFrameSize(), align) + paddingOffset;
        child->GetGeometryNode()->SetMarginFrameOffset(translate + childPosition);
    }
}
} // namespace OHOS::Ace::NG
