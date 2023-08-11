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
namespace {
constexpr double MULTIPLE = 2.0;
}
void MarqueeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& minSize = layoutConstraint->minSize;
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto measureType = layoutWrapper->GetLayoutProperty()->GetMeasureType();
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    // measure child.
    LayoutConstraintF textLayoutConstraint;
    textLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(Infinity<float>(), maxSize.Height()));
    child->Measure(textLayoutConstraint);
    // measure self.
    OptionalSizeF frameSize;
    do {
        // Use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            break;
        }
        frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
        frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->percentReference);
        if (measureType == MeasureType::MATCH_PARENT) {
            if (frameSize.IsValid()) {
                frameSize.Constrain(minSize, maxSize);
                break;
            }
        } else {
            // use the child size.
            auto childFrame = child->GetGeometryNode()->GetMarginFrameSize();
            childFrame.Constrain(SizeF(Infinity<float>(), minSize.Height()), maxSize);
            AddPaddingToSize(padding, childFrame);
            frameSize.Constrain(SizeF { 0.0f, 0.0f }, SizeF { Infinity<float>(), childFrame.Height() });
            break;
        }
        frameSize.UpdateIllegalSizeWithCheck(SizeF { 0.0f, 0.0f });
    } while (false);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto size = layoutWrapper->GetGeometryNode()->GetFrameSize();
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, size);
    auto left = padding.left.value_or(0);
    auto top = padding.top.value_or(0);
    auto paddingOffset = OffsetF(left, top);
    auto align = Alignment::CENTER_LEFT;
    if (layoutWrapper->GetLayoutProperty()->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    // Update child position.
    auto textNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(textNode);
    auto textGeoNode = textNode->GetGeometryNode();
    CHECK_NULL_VOID(textGeoNode);
    for (const auto& child : layoutWrapper->GetAllChildrenWithBuild()) {
        OffsetF translate;
        translate.SetX((1.0 + align.GetHorizontal()) *
                       (size.Width() - child->GetGeometryNode()->GetMarginFrameSize().Width()) / MULTIPLE);
        translate.SetY((1.0 + align.GetVertical()) *
                       (size.Height() - child->GetGeometryNode()->GetMarginFrameSize().Height()) / MULTIPLE);
        child->GetGeometryNode()->SetMarginFrameOffset(translate + paddingOffset);
        child->Layout();
    }
}
} // namespace OHOS::Ace::NG
