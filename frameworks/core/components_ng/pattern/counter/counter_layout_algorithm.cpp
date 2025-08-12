/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/counter/counter_layout_algorithm.h"

#include "core/components/counter/counter_theme.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/measure_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SUB_BUTTON = 0;
constexpr int32_t CONTENT = 1;
constexpr int32_t ADD_BUTTON = 2;
constexpr int32_t SUB_TEXT = 0;
constexpr int32_t ADD_TEXT = 0;
} // namespace
static bool checkLayoutPolicy(const std::optional<NG::LayoutPolicyProperty> layoutPolicy)
{
    if (layoutPolicy.has_value()) {
        return layoutPolicy->widthLayoutPolicy_ != LayoutCalPolicy::NO_MATCH ||
               layoutPolicy->heightLayoutPolicy_ != LayoutCalPolicy::NO_MATCH;
    }
    return false;
}

void CounterLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    // counter measure
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto layoutPolicy = layoutProperty->GetLayoutPolicyProperty();
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    auto frameWidthMax = ((constraint->selfIdealSize.Width().has_value())
                              ? std::min(constraint->selfIdealSize.Width().value(), constraint->maxSize.Width())
                              : std::min(constraint->percentReference.Width(), constraint->maxSize.Width()));
    frameSize.SetWidth(std::max(frameWidthMax, constraint->minSize.Width()));
    auto frameHeightMax = ((constraint->selfIdealSize.Height().has_value())
                               ? std::min(constraint->selfIdealSize.Height().value(), constraint->maxSize.Height())
                               : std::min(constraint->percentReference.Height(), constraint->maxSize.Height()));
    frameSize.SetHeight(std::max(frameHeightMax, constraint->minSize.Height()));
    bool checkSizeFlag = false;
    if (layoutPolicy.has_value()) {
        if (layoutPolicy->IsWidthMatch()) {
            frameSize.SetWidth(constraint->parentIdealSize.Width().value());
            checkSizeFlag = true;
        }
        if (layoutPolicy->IsHeightMatch()) {
            frameSize.SetHeight(constraint->parentIdealSize.Height().value());
            checkSizeFlag = true;
        }
    }
    SizeF selfContentSize(frameSize.Width(), frameSize.Height());
    const auto& padding = layoutProperty->CreatePaddingWithoutBorder();
    MinusPaddingToSize(padding, selfContentSize);
    if (checkSizeFlag || !checkLayoutPolicy(layoutPolicy)) {
        geometryNode->SetFrameSize(frameSize);
        geometryNode->SetContentSize(selfContentSize);
    }

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto frameNode = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(frameNode);
    auto counterTheme = pipeline->GetTheme<CounterTheme>(frameNode->GetThemeScopeId());
    CHECK_NULL_VOID(counterTheme);
    auto buttonWidth = counterTheme->GetControlWidth().ConvertToPx();
    auto layoutConstraint = layoutProperty->CreateChildConstraint();

    // content measure
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    CHECK_NULL_VOID(contentWrapper);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto contentLayoutProperty = contentWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(contentLayoutProperty);
    CalcSize contentSize;
    if (checkLayoutPolicy(layoutPolicy)) {
        if (layoutPolicy->IsWidthFix()) {
            layoutConstraint.maxSize.SetWidth(std::numeric_limits<float>::max());
            contentLayoutProperty->ClearUserDefinedIdealSize(true, false);
        } else if (layoutPolicy->IsWidthWrap()) {
            layoutConstraint.maxSize.SetWidth(constraint->parentIdealSize.Width().value() - 2 * buttonWidth);
            contentLayoutProperty->ClearUserDefinedIdealSize(true, false);
        } else if (layoutPolicy->IsWidthMatch()) {
            layoutConstraint.maxSize.SetWidth(constraint->parentIdealSize.Width().value() - 2 * buttonWidth);
            contentSize.SetWidth(CalcLength(selfContentSize.Width() - 2 * buttonWidth));
            contentLayoutProperty->UpdateUserDefinedIdealSize(contentSize);
        } else {
            contentSize.SetWidth(CalcLength(selfContentSize.Width() - 2 * buttonWidth));
        }
        if (layoutPolicy->IsHeightFix()) {
            layoutConstraint.maxSize.SetHeight(std::numeric_limits<float>::max());
            contentLayoutProperty->ClearUserDefinedIdealSize(false, true);
        } else if (layoutPolicy->IsHeightWrap()) {
            layoutConstraint.maxSize.SetHeight(constraint->parentIdealSize.Height().value());
            contentLayoutProperty->ClearUserDefinedIdealSize(false, true);
        } else if (layoutPolicy->IsHeightMatch()) {
            layoutConstraint.maxSize.SetHeight(constraint->parentIdealSize.Height().value());
            contentSize.SetHeight(CalcLength(selfContentSize.Height()));
            contentLayoutProperty->UpdateUserDefinedIdealSize(contentSize);
        } else {
            contentSize.SetHeight(CalcLength(selfContentSize.Height()));
        }
        checkSizeFlag = true;
    } else {
        contentSize.SetWidth(CalcLength(selfContentSize.Width() - 2 * buttonWidth));
        contentSize.SetHeight(CalcLength(selfContentSize.Height()));
        contentLayoutProperty->UpdateUserDefinedIdealSize(contentSize);
    }
    contentWrapper->Measure(layoutConstraint);
    auto contentSizeRes = contentWrapper->GetGeometryNode()->GetFrameSize();
    selfContentSize.SetWidth(contentSizeRes.Width() + 2 * buttonWidth);
    selfContentSize.SetHeight(contentSizeRes.Height());
    if (checkSizeFlag) {
        geometryNode->SetFrameSize(selfContentSize);
        geometryNode->SetContentSize(selfContentSize);
    }

    // sub button measure
    auto counterRenderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(counterRenderContext);
    Color textColor = counterRenderContext->GetForegroundColor().has_value()
                          ? counterRenderContext->GetForegroundColorValue()
                          : counterTheme->GetContentTextStyle().GetTextColor();

    auto subButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(SUB_BUTTON);
    CHECK_NULL_VOID(subButtonWrapper);
    auto subButtonGeometryNode = subButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(subButtonGeometryNode);
    auto subButtonLayoutProperty = subButtonWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(subButtonLayoutProperty);
    auto leftButtonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(subButtonLayoutProperty);
    CHECK_NULL_VOID(leftButtonLayoutProperty);
    BorderRadiusProperty leftButtonBorder { counterTheme->GetBorderRadius().radiusTopLeft.value(), 0.0_vp, 0.0_vp,
        counterTheme->GetBorderRadius().radiusBottomLeft.value() };
    BorderRadiusProperty rightButtonBorder { 0.0_vp, counterTheme->GetBorderRadius().radiusTopRight.value(),
        counterTheme->GetBorderRadius().radiusBottomRight.value(), 0.0_vp };
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL) {
        leftButtonLayoutProperty->UpdateBorderRadius(rightButtonBorder);
    } else {
        leftButtonLayoutProperty->UpdateBorderRadius(leftButtonBorder);
    }
    CalcSize subButtonSize;
    subButtonSize.SetWidth(CalcLength(buttonWidth));
    subButtonSize.SetHeight(CalcLength(selfContentSize.Height()));
    subButtonLayoutProperty->UpdateUserDefinedIdealSize(subButtonSize);
    auto subButtonTextWrapper = subButtonWrapper->GetOrCreateChildByIndex(SUB_TEXT);
    CHECK_NULL_VOID(subButtonTextWrapper);
    auto subButtonTextLayoutProperty = subButtonTextWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(subButtonTextLayoutProperty);
    subButtonTextLayoutProperty->UpdateUserDefinedIdealSize(subButtonSize);
    subButtonWrapper->Measure(layoutConstraint);

    auto subButtonHostNode = subButtonWrapper->GetHostNode();
    CHECK_NULL_VOID(subButtonHostNode);
    auto subButtonRenderContext = subButtonHostNode->GetRenderContext();
    CHECK_NULL_VOID(subButtonRenderContext);
    subButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto subTextNode = AceType::DynamicCast<FrameNode>(subButtonHostNode->GetChildren().front());
    UpdateTextColor(subTextNode, textColor);

    // add button measure
    auto addButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(ADD_BUTTON);
    CHECK_NULL_VOID(addButtonWrapper);
    auto addButtonGeometryNode = addButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(addButtonGeometryNode);
    auto addButtonLayoutProperty = addButtonWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(addButtonLayoutProperty);
    auto rightButtonLayoutProperty = AceType::DynamicCast<ButtonLayoutProperty>(addButtonLayoutProperty);
    CHECK_NULL_VOID(rightButtonLayoutProperty);
    if (layoutDirection == TextDirection::RTL) {
        rightButtonLayoutProperty->UpdateBorderRadius(leftButtonBorder);
    } else {
        rightButtonLayoutProperty->UpdateBorderRadius(rightButtonBorder);
    }
    CalcSize addButtonSize;
    addButtonSize.SetWidth(CalcLength(buttonWidth));
    addButtonSize.SetHeight(CalcLength(selfContentSize.Height()));
    auto addButtonTextWrapper = addButtonWrapper->GetOrCreateChildByIndex(ADD_TEXT);
    CHECK_NULL_VOID(addButtonTextWrapper);
    auto addButtonTextLayoutProperty = addButtonTextWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(addButtonTextLayoutProperty);
    addButtonTextLayoutProperty->UpdateUserDefinedIdealSize(addButtonSize);
    addButtonLayoutProperty->UpdateUserDefinedIdealSize(addButtonSize);
    addButtonWrapper->Measure(layoutConstraint);

    auto addButtonHostNode = addButtonWrapper->GetHostNode();
    CHECK_NULL_VOID(addButtonHostNode);
    auto addButtonRenderContext = addButtonHostNode->GetRenderContext();
    CHECK_NULL_VOID(addButtonRenderContext);
    addButtonRenderContext->UpdateBackgroundColor(Color::TRANSPARENT);
    auto addTextNode = AceType::DynamicCast<FrameNode>(addButtonHostNode->GetChildren().front());
    UpdateTextColor(addTextNode, textColor);
}

static void LayoutItem(LayoutWrapper* layoutWrapper, int32_t leftButton, int32_t rightButton)
{
    // layout left button
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(leftButton);
    CHECK_NULL_VOID(leftButtonWrapper);
    auto leftButtonGeometryNode = leftButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(leftButtonGeometryNode);
    auto leftButtonSize = leftButtonGeometryNode->GetFrameSize();
    auto leftButtonFrameWidth = leftButtonSize.Width();
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingWithoutBorder();
    OffsetF leftButtonOffset(padding.left.value_or(0), padding.top.value_or(0));
    leftButtonGeometryNode->SetMarginFrameOffset(leftButtonOffset);
    leftButtonWrapper->Layout();

    // layout content
    auto contentWrapper = layoutWrapper->GetOrCreateChildByIndex(CONTENT);
    CHECK_NULL_VOID(contentWrapper);
    auto contentGeometryNode = contentWrapper->GetGeometryNode();
    CHECK_NULL_VOID(contentGeometryNode);
    auto contentSize = contentGeometryNode->GetFrameSize();
    auto contentFrameWidth = contentSize.Width();
    auto contentHorizontalOffset = leftButtonGeometryNode->GetFrameOffset().GetX() + leftButtonFrameWidth;
    auto contentVerticalOffset = leftButtonGeometryNode->GetFrameOffset().GetY();
    OffsetF contentOffset(contentHorizontalOffset, contentVerticalOffset);
    contentGeometryNode->SetMarginFrameOffset(contentOffset);
    contentWrapper->Layout();

    // layout right button
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(rightButton);
    CHECK_NULL_VOID(rightButtonWrapper);
    auto rightButtonGeometryNode = rightButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(rightButtonGeometryNode);
    auto rightButtonHorizontalOffset =
        leftButtonGeometryNode->GetFrameOffset().GetX() + leftButtonFrameWidth + contentFrameWidth;
    auto rightButtonVerticalOffset = leftButtonGeometryNode->GetFrameOffset().GetY();
    OffsetF rightButtonOffset(rightButtonHorizontalOffset, rightButtonVerticalOffset);
    rightButtonGeometryNode->SetMarginFrameOffset(rightButtonOffset);
    rightButtonWrapper->Layout();
}

void CounterLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto layoutDirection = layoutWrapper->GetLayoutProperty()->GetNonAutoLayoutDirection();
    if (layoutDirection == TextDirection::RTL) {
        LayoutItem(layoutWrapper, ADD_BUTTON, SUB_BUTTON);
    } else {
        LayoutItem(layoutWrapper, SUB_BUTTON, ADD_BUTTON);
    }
}

void CounterLayoutAlgorithm::UpdateTextColor(const RefPtr<FrameNode>& frameNode, const Color& value)
{
    CHECK_NULL_VOID(frameNode);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateTextColorByRender(value);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateForegroundColor(value);
    renderContext->ResetForegroundColorStrategy();
    renderContext->UpdateForegroundColorFlag(true);
    auto textPattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    textPattern->UpdateFontColor(value);
}
} // namespace OHOS::Ace::NG
