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
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double MULTIPLE = 2.0;
} // namespace

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
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    auto child = layoutWrapper->GetAllChildrenWithBuild().front();
    // init align, and get user defined alignment
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);

    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<MarqueePattern>();
    CHECK_NULL_VOID(pattern);
    auto marqueeLayoutProperty = AceType::DynamicCast<MarqueeLayoutProperty>(layoutProperty);
    CHECK_NULL_VOID(marqueeLayoutProperty);
    auto content = marqueeLayoutProperty->GetSrc().value_or("");
    auto direction = layoutProperty->GetLayoutDirection();
    auto textDirection = pattern->GetTextDirection(content, direction);
    auto align = (textDirection == TextDirection::RTL ? Alignment::CENTER_RIGHT : Alignment::CENTER_LEFT);

    if (layoutProperty->GetPositionProperty()) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    OffsetF translate;
    translate.SetX((1.0 + align.GetHorizontal()) *
                   (frameSize.Width() - child->GetGeometryNode()->GetMarginFrameSize().Width()) / MULTIPLE);
    translate.SetY(0.0f);
    child->GetGeometryNode()->SetMarginFrameOffset(translate);
    child->Layout();
}
} // namespace OHOS::Ace::NG
