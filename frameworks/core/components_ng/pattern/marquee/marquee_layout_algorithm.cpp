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
#include "base/utils/utils.h"
#include "core/components_ng/pattern/marquee/marquee_layout_property.h"
#include "core/components_ng/pattern/marquee/marquee_pattern.h"
#include "core/components_ng/pattern/text/text_base.h"

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
    auto heightLayoutPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    // use marquee constrain size as text child max constrain size
    if (layoutConstraint->selfIdealSize.Height().has_value()) {
        textLayoutConstraint.selfIdealSize.SetHeight(layoutConstraint->selfIdealSize.Height().value());
    } else if (heightLayoutPolicy == LayoutCalPolicy::MATCH_PARENT) {
        textLayoutConstraint.selfIdealSize.SetHeight(maxSize.Height());
    }
    // measure text, and add marquee padding to text child
    PaddingProperty textPadding;
    textPadding.left = CalcLength(padding.left.value());
    textPadding.right = CalcLength(padding.right.value());
    textPadding.top = CalcLength(padding.top.value());
    textPadding.bottom = CalcLength(padding.bottom.value());
    child->GetLayoutProperty()->UpdatePadding(textPadding);
    child->Measure(textLayoutConstraint);
    auto adaptiveSize = GetMeasureAdaptiveHeight(layoutWrapper, child);
    if (adaptiveSize.Height().has_value()) {
        textLayoutConstraint.selfIdealSize.SetHeight(adaptiveSize.Height().value());
        child->Measure(textLayoutConstraint);
    }
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
        MeasureWithLayoutPolicy(layoutWrapper, child, frameSize);
        break;
    } while (false);
    layoutWrapper->GetGeometryNode()->SetFrameSize(frameSize.ConvertToSizeT());
}

void MarqueeLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto frameSize = layoutWrapper->GetGeometryNode()->GetFrameSize();
    CHECK_NULL_VOID(!layoutWrapper->GetAllChildrenWithBuild().empty());
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

    auto textGeoNode = child->GetGeometryNode();
    CHECK_NULL_VOID(textGeoNode);
    auto minusLen = frameSize.Width() - textGeoNode->GetMarginFrameSize().Width();
    if (layoutProperty->GetPositionProperty() && GreatOrEqual(minusLen, 0.0f)) {
        align = layoutWrapper->GetLayoutProperty()->GetPositionProperty()->GetAlignment().value_or(align);
    }
    OffsetF translate;
    translate.SetX((1.0 + align.GetHorizontal()) * minusLen / MULTIPLE);
    translate.SetY(0.0f);
    textGeoNode->SetMarginFrameOffset(translate);
    child->Layout();
}

void MarqueeLayoutAlgorithm::MeasureWithLayoutPolicy(
    LayoutWrapper* layoutWrapper, const RefPtr<LayoutWrapper>& textLayoutWrapper, OptionalSizeF& frameSize)
{
    auto widthPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, true);
    auto heightPolicy = TextBase::GetLayoutCalPolicy(layoutWrapper, false);
    if (widthPolicy == LayoutCalPolicy::NO_MATCH && heightPolicy == LayoutCalPolicy::NO_MATCH) {
        return;
    }
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_VOID(layoutConstraint);
    auto childGeometryNode = textLayoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(childGeometryNode);
    auto childFrame = childGeometryNode->GetMarginFrameSize();
    MeasureCalculationContext context {
        .layoutConstraint = layoutConstraint.value(), .layoutProperty = layoutProperty, .optionalSize = OptionalSizeF()
    };
    HandleWidthConstraint(widthPolicy, childFrame.Width(), context);
    HandleHeightConstraint(heightPolicy, childFrame.Height(), context);
    auto optionalFrameSize = context.optionalSize;
    optionalFrameSize.Constrain(context.layoutConstraint.minSize, context.layoutConstraint.maxSize, true);
    if (optionalFrameSize.Width().has_value()) {
        frameSize.SetWidth(optionalFrameSize.Width().value());
    }
    if (optionalFrameSize.Height().has_value()) {
        frameSize.SetHeight(optionalFrameSize.Height().value());
    }
}

void MarqueeLayoutAlgorithm::HandleWidthConstraint(
    LayoutCalPolicy policy, float childDimensionSize, MeasureCalculationContext& context)
{
    CHECK_NULL_VOID(context.layoutProperty);
    if (context.layoutConstraint.selfIdealSize.Width().has_value()) {
        return;
    }
    switch (policy) {
        case LayoutCalPolicy::WRAP_CONTENT:
            context.optionalSize.SetWidth(childDimensionSize);
            break;
        case LayoutCalPolicy::FIX_AT_IDEAL_SIZE: {
            context.optionalSize.SetWidth(childDimensionSize);
            const auto& calcLayoutConstraint = context.layoutProperty->GetCalcLayoutConstraint();
            if (calcLayoutConstraint && !calcLayoutConstraint->maxSize->Width().has_value()) {
                context.layoutConstraint.maxSize.SetWidth(Infinity<float>());
            }
            break;
        }
        case LayoutCalPolicy::MATCH_PARENT:
            context.optionalSize.SetWidth(context.layoutConstraint.parentIdealSize.Width());
            break;
        default:
            break;
    }
}

void MarqueeLayoutAlgorithm::HandleHeightConstraint(
    LayoutCalPolicy policy, float childDimensionSize, MeasureCalculationContext& context)
{
    CHECK_NULL_VOID(context.layoutProperty);
    if (context.layoutConstraint.selfIdealSize.Height().has_value()) {
        return;
    }
    switch (policy) {
        case LayoutCalPolicy::WRAP_CONTENT:
            context.optionalSize.SetHeight(childDimensionSize);
            break;
        case LayoutCalPolicy::FIX_AT_IDEAL_SIZE: {
            context.optionalSize.SetHeight(childDimensionSize);
            const auto& calcLayoutConstraint = context.layoutProperty->GetCalcLayoutConstraint();
            if (calcLayoutConstraint && !calcLayoutConstraint->maxSize->Height().has_value()) {
                context.layoutConstraint.maxSize.SetHeight(Infinity<float>());
            }
            break;
        }
        case LayoutCalPolicy::MATCH_PARENT:
            context.optionalSize.SetHeight(context.layoutConstraint.parentIdealSize.Height());
            break;
        default:
            break;
    }
}

OptionalSizeF MarqueeLayoutAlgorithm::GetMeasureAdaptiveHeight(
    LayoutWrapper* marqueeLayoutWrapper, const RefPtr<LayoutWrapper>& textLayoutWrapper)
{
    OptionalSizeF frameSize;
    auto heightPolicy = TextBase::GetLayoutCalPolicy(marqueeLayoutWrapper, false);
    if (heightPolicy != LayoutCalPolicy::WRAP_CONTENT && heightPolicy != LayoutCalPolicy::FIX_AT_IDEAL_SIZE) {
        return frameSize;
    }
    auto layoutProperty = marqueeLayoutWrapper->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, frameSize);
    const auto& layoutConstraint = layoutProperty->GetLayoutConstraint();
    CHECK_NULL_RETURN(layoutConstraint, frameSize);
    if (layoutConstraint->selfIdealSize.Height().has_value()) {
        return frameSize;
    }
    const auto& calcLayoutConstraint = layoutProperty->GetCalcLayoutConstraint();
    CHECK_NULL_RETURN(calcLayoutConstraint, frameSize);
    auto childGeometryNode = textLayoutWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(childGeometryNode, frameSize);
    auto childFrame = childGeometryNode->GetMarginFrameSize();
    frameSize.SetHeight(childFrame.Height());
    auto maxSize = layoutConstraint->maxSize;
    if (heightPolicy == LayoutCalPolicy::FIX_AT_IDEAL_SIZE && !calcLayoutConstraint->maxSize->Height().has_value()) {
        maxSize.SetHeight(Infinity<float>());
    }
    frameSize.Constrain(layoutConstraint->minSize, maxSize, true);
    if (frameSize.Height().has_value() && frameSize.Height().value() != childFrame.Height()) {
        return frameSize;
    }
    frameSize.Reset();
    return frameSize;
}
} // namespace OHOS::Ace::NG
