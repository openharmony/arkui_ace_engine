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
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void MarqueeLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    const auto& layoutConstraint = layoutWrapper->GetLayoutProperty()->GetLayoutConstraint();
    const auto& maxSize = layoutConstraint->maxSize;
    const auto& padding = layoutWrapper->GetLayoutProperty()->CreatePaddingAndBorder();
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    LayoutConstraintF textLayoutConstraint;
    textLayoutConstraint.UpdateMaxSizeWithCheck(SizeF(Infinity<float>(), maxSize.Height()));
    // use marquee constrain size as text child max constrain size
    if (layoutConstraint->selfIdealSize.Height().has_value()) {
        textLayoutConstraint.selfIdealSize.SetHeight(layoutConstraint->selfIdealSize.Height().value());
    }
    // measure text, and add marquee padding to text child
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding.left.value());
    textPadding.right = CalcLength(padding.right.value());
    textPadding.top = CalcLength(padding.top.value());
    textPadding.bottom = CalcLength(padding.bottom.value());
    child->GetLayoutProperty()->UpdatePadding(textPadding);
    child->Measure(textLayoutConstraint);
    // measure marquee self, and update marquee padding to zero
    layoutWrapper->GetGeometryNode()->UpdatePaddingWithBorder({ 0.0, 0.0, 0.0, 0.0 });
    OptionalSizeF frameSize;
    do {
        // use idea size first if it is valid.
        frameSize.UpdateSizeWithCheck(layoutConstraint->selfIdealSize);
        if (frameSize.IsValid()) {
            break;
        }
        // don't set marquee's height, and use text child's height
        frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->parentIdealSize);
        frameSize.UpdateIllegalSizeWithCheck(layoutConstraint->percentReference);
        auto childFrame = child->GetGeometryNode()->GetMarginFrameSize();
        frameSize.Constrain(SizeF { 0.0f, 0.0f }, SizeF { maxSize.Width(), childFrame.Height() });
        break;
    } while (false);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    child->GetGeometryNode()->SetMarginFrameOffset({ 0.0f, 0.0f });
    child->Layout();
}
} // namespace OHOS::Ace::NG
