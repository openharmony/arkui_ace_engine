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

#include "core/components_ng/pattern/stepper/stepper_layout_algorithm.h"

#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float SUIT_AGE_LEVEL_ONE = 1.75f;
constexpr float SUIT_AGE_LEVEL_TWO = 2.0f;
constexpr float SUIT_AGE_LEVEL_THRER = 3.2f;
constexpr Dimension PADDING = 4.0_vp;
constexpr float HEIGHT_HALF_RATIO = 0.5f;
constexpr float HEIGHT_DOUBLE_RATIO = 2.0f;
} // namespace

void StepperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);

    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    MinusPaddingToSize(padding, idealSize);

    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline->GetFontScale() == SUIT_AGE_LEVEL_ONE || pipeline->GetFontScale() == SUIT_AGE_LEVEL_TWO ||
        pipeline->GetFontScale() == SUIT_AGE_LEVEL_THRER) {
        MeasureLeftButton(layoutWrapper, childLayoutConstraint);
        MeasureRightButton(layoutWrapper, childLayoutConstraint);
        auto rightButtonHeight = CaluateButtonHeight(layoutWrapper, true);
        auto leftButtonHeight = CaluateButtonHeight(layoutWrapper, false);
        MeasureSwiper(layoutWrapper, childLayoutConstraint, rightButtonHeight, leftButtonHeight);
    } else {
        MeasureSwiper(layoutWrapper, childLayoutConstraint, 0, 0);
        MeasureLeftButton(layoutWrapper, childLayoutConstraint);
        MeasureRightButton(layoutWrapper, childLayoutConstraint);
    }
}

void StepperLayoutAlgorithm::MeasureSwiper(LayoutWrapper* layoutWrapper, LayoutConstraintF swiperLayoutConstraint,
    float rightButtonHeight, float leftButtonHeight)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetSwiperId());
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(swiperWrapper);
    auto swiperWidth = swiperLayoutConstraint.parentIdealSize.Width().value_or(0.0);
    auto swiperHeight = swiperLayoutConstraint.parentIdealSize.Height().value_or(0.0) -
                        static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    auto stepperHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    auto swiperCaluateHeight = stepperHeight -
                               (rightButtonHeight > leftButtonHeight ? rightButtonHeight : leftButtonHeight) -
                               (PADDING.ConvertToPx() * HEIGHT_DOUBLE_RATIO);
    if (swiperCaluateHeight < swiperHeight) {
        swiperHeight = swiperCaluateHeight;
    }
    auto swiperLayoutProperty = AceType::DynamicCast<SwiperLayoutProperty>(swiperWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(swiperWidth), CalcLength(swiperHeight)));
    swiperLayoutConstraint.maxSize.SetHeight(swiperHeight);
    swiperLayoutConstraint.selfIdealSize.SetHeight(swiperHeight);
    swiperLayoutConstraint.selfIdealSize.SetWidth(swiperWidth);
    swiperWrapper->Measure(swiperLayoutConstraint);
}
void StepperLayoutAlgorithm::MeasureLeftButton(LayoutWrapper* layoutWrapper, LayoutConstraintF buttonLayoutConstraint)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(hostNode->HasLeftButtonNode());
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto padding =
        static_cast<float>((stepperTheme->GetDefaultPaddingStart() + stepperTheme->GetControlPadding()).ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidth = (buttonLayoutConstraint.parentIdealSize.Width().value() / 2) - padding - margin;
    auto buttonHeight = static_cast<float>(
        stepperTheme->GetArrowHeight().ConvertToPx() + 2 * stepperTheme->GetControlMargin().ConvertToPx());
    auto index = hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    buttonLayoutConstraint.minSize = { 0, buttonHeight };
    if (pipeline->GetFontScale() == SUIT_AGE_LEVEL_ONE || pipeline->GetFontScale() == SUIT_AGE_LEVEL_TWO ||
        pipeline->GetFontScale() == SUIT_AGE_LEVEL_THRER) {
        auto stepperHeight = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
        buttonLayoutConstraint.maxSize = { buttonWidth, stepperHeight };
        auto ButtonRow = leftButtonWrapper->GetChildByIndex(0);
        CHECK_NULL_VOID(ButtonRow);
        auto ButtonText = ButtonRow->GetChildByIndex(1);
        CHECK_NULL_VOID(ButtonText);
        auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(ButtonText->GetLayoutProperty());
        CHECK_NULL_VOID(textLayoutProperty);
        textLayoutProperty->UpdateMaxFontScale(SUIT_AGE_LEVEL_TWO);
        MeasureText(leftButtonWrapper, buttonLayoutConstraint, true);
        float TextHeight = ButtonText->GetGeometryNode()->GetFrameSize().Height();
        buttonLayoutConstraint.selfIdealSize =
            OptionalSizeF(std::nullopt, TextHeight + PADDING.ConvertToPx() * HEIGHT_DOUBLE_RATIO);
    } else {
        buttonLayoutConstraint.maxSize = { buttonWidth, buttonHeight };
        buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, buttonHeight);
    }
    leftButtonWrapper->Measure(buttonLayoutConstraint);
    MeasureText(leftButtonWrapper, buttonLayoutConstraint, true);
}
void StepperLayoutAlgorithm::MeasureRightButton(LayoutWrapper* layoutWrapper, LayoutConstraintF buttonLayoutConstraint)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(hostNode->HasRightButtonNode());

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto padding =
        static_cast<float>((stepperTheme->GetDefaultPaddingEnd() + stepperTheme->GetControlPadding()).ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidth = (buttonLayoutConstraint.parentIdealSize.Width().value() / 2) - padding - margin;
    auto buttonHeight = static_cast<float>(
        stepperTheme->GetArrowHeight().ConvertToPx() + 2 * stepperTheme->GetControlMargin().ConvertToPx());
    auto index = hostNode->GetChildIndexById(hostNode->GetRightButtonId());
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    buttonLayoutConstraint.minSize = { 0, buttonHeight };
    if (pipeline->GetFontScale() == SUIT_AGE_LEVEL_ONE || pipeline->GetFontScale() == SUIT_AGE_LEVEL_TWO ||
        pipeline->GetFontScale() == SUIT_AGE_LEVEL_THRER) {
        auto stepperHeight = hostNode->GetGeometryNode()->GetFrameSize().Height();
        buttonLayoutConstraint.maxSize = { buttonWidth, stepperHeight };
        auto ButtonRow = rightButtonWrapper->GetChildByIndex(0);
        CHECK_NULL_VOID(ButtonRow);
        auto ButtonText = ButtonRow->GetChildByIndex(0);
        if (!ButtonText) {
            auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(ButtonRow->GetLayoutProperty());
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateMaxFontScale(SUIT_AGE_LEVEL_TWO);
            PaddingProperty textPadding;
            textPadding.top = CalcLength(PADDING.ConvertToPx(), DimensionUnit::PX);
            textPadding.bottom = CalcLength(PADDING.ConvertToPx(), DimensionUnit::PX);
            rightButtonWrapper->GetLayoutProperty()->UpdatePadding(textPadding);
            buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, std::nullopt);
        } else {
            auto textLayoutProperty = AceType::DynamicCast<TextLayoutProperty>(ButtonText->GetLayoutProperty());
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateMaxFontScale(SUIT_AGE_LEVEL_TWO);
            MeasureText(rightButtonWrapper, buttonLayoutConstraint, false);
            float TextHeight = ButtonText->GetGeometryNode()->GetFrameSize().Height();
            buttonLayoutConstraint.selfIdealSize =
                OptionalSizeF(std::nullopt, TextHeight + PADDING.ConvertToPx() * HEIGHT_DOUBLE_RATIO);
        }
    } else {
        buttonLayoutConstraint.maxSize = { buttonWidth, buttonHeight };
        buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, buttonHeight);
    }
    rightButtonWrapper->Measure(buttonLayoutConstraint);
    MeasureText(rightButtonWrapper, buttonLayoutConstraint, false);
}

void StepperLayoutAlgorithm::MeasureText(
    const RefPtr<LayoutWrapper>& layoutWrapper, const LayoutConstraintF& buttonLayoutConstraint, bool isLeft)
{
    CHECK_NULL_VOID(layoutWrapper->GetHostTag() == std::string(V2::BUTTON_ETS_TAG));
    auto rowWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    CHECK_NULL_VOID(rowWrapper->GetHostTag() == std::string(V2::ROW_ETS_TAG));
    auto textWrapper = rowWrapper->GetOrCreateChildByIndex(isLeft ? 1 : 0);
    CHECK_NULL_VOID(textWrapper->GetHostTag() == std::string(V2::TEXT_ETS_TAG));

    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);

    LayoutConstraintF textLayoutConstraint = buttonLayoutConstraint;
    auto controlPadding = static_cast<float>(stepperTheme->GetControlPadding().ConvertToPx());
    auto arrowWidth = static_cast<float>(stepperTheme->GetArrowWidth().ConvertToPx());
    auto textMaxWidth =
        buttonLayoutConstraint.maxSize.Width() - controlPadding - controlPadding - arrowWidth - controlPadding;
    textLayoutConstraint.minSize = { 0, 0 };
    textLayoutConstraint.maxSize.SetWidth(textMaxWidth);
    textLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, std::nullopt);
    textWrapper->Measure(textLayoutConstraint);
}

void StepperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    if (!frameSize.IsPositive()) {
        return;
    }
    LayoutSwiper(layoutWrapper);
    if (pipeline->GetFontScale() == SUIT_AGE_LEVEL_ONE || pipeline->GetFontScale() == SUIT_AGE_LEVEL_TWO ||
        pipeline->GetFontScale() == SUIT_AGE_LEVEL_THRER) {
        auto layoutProperty = layoutWrapper->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        auto constraint = layoutProperty->GetLayoutConstraint();
        auto idealSize = CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
        if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
            LOGW("Size is infinity.");
            geometryNode->SetFrameSize(SizeF());
            return;
        }
        geometryNode->SetFrameSize(idealSize);

        const auto& padding = layoutProperty->CreatePaddingAndBorder();
        MinusPaddingToSize(padding, idealSize);

        auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
        childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);
        auto rightButtonHeight = CaluateButtonHeight(layoutWrapper, true);
        auto leftButtonHeight = CaluateButtonHeight(layoutWrapper, false);
        SuitAgeLayoutButton(layoutWrapper, rightButtonHeight, leftButtonHeight, true);
        SuitAgeLayoutButton(layoutWrapper, rightButtonHeight, leftButtonHeight, false);
    } else {
        LayoutLeftButton(layoutWrapper);
        LayoutRightButton(layoutWrapper);
    }
}

void StepperLayoutAlgorithm::SuitAgeLayoutButton(
    LayoutWrapper* layoutWrapper, float rightButtonHeight, float leftButtonHeight, bool isRight)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    if (!isRight) {
        CHECK_NULL_VOID(hostNode->HasLeftButtonNode());
    }
    auto buttonIndex = isRight ? hostNode->GetChildIndexById(hostNode->GetRightButtonId())
                               : hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto ButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(buttonIndex);
    CHECK_NULL_VOID(ButtonWrapper);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto frameSizeWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto ButtonWidth = ButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    auto padding = static_cast<float>(stepperTheme->GetDefaultPaddingEnd().ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidthOffset = isRight ? (frameSizeWidth - ButtonWidth - padding - margin) : (padding + margin);
    auto buttonHeightOffset = layoutWrapper->GetGeometryNode()->GetFrameSize().Height();
    auto maxButtonHeight = rightButtonHeight > leftButtonHeight ? rightButtonHeight : leftButtonHeight;
    auto ButtonHeight = isRight ? rightButtonHeight : leftButtonHeight;
    buttonHeightOffset -=
        maxButtonHeight * HEIGHT_HALF_RATIO + PADDING.ConvertToPx() + ButtonHeight * HEIGHT_HALF_RATIO;
    OffsetF buttonOffset = { buttonWidthOffset, buttonHeightOffset };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& stepperPadding = layoutProperty->CreatePaddingAndBorder();
    if (isRight) {
        buttonOffset -= OffsetF(stepperPadding.right.value_or(0.0), stepperPadding.bottom.value_or(0.0));
    } else {
        buttonOffset += OffsetF(stepperPadding.left.value_or(0.0), -stepperPadding.bottom.value_or(0.0));
    }
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    auto isRightToLeft = stepperLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRightToLeft) {
        auto frameWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
        auto offsetX = frameWidth - ButtonWrapper->GetGeometryNode()->GetFrameSize().Width() - buttonOffset.GetX();
        buttonOffset.SetX(offsetX);
    }
    ButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(buttonOffset);
    ButtonWrapper->Layout();
}

float StepperLayoutAlgorithm::CaluateButtonHeight(LayoutWrapper* layoutWrapper, bool isRight)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_RETURN(hostNode, 0.0f);
    auto hasButtonNode = isRight ? hostNode->HasRightButtonNode() : hostNode->HasLeftButtonNode();
    if (!hasButtonNode) {
        return 0.0f;
    }
    auto buttonId = isRight ? hostNode->GetRightButtonId() : hostNode->GetLeftButtonId();
    auto ButtonIndex = hostNode->GetChildIndexById(buttonId);
    CHECK_NULL_RETURN(ButtonIndex, 0.0f);
    auto ButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(ButtonIndex);
    CHECK_NULL_RETURN(ButtonWrapper, 0.0f);
    auto ButtonHeight = ButtonWrapper->GetGeometryNode()->GetFrameSize().Height();
    return ButtonHeight;
}

void StepperLayoutAlgorithm::LayoutSwiper(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetSwiperId());
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    CHECK_NULL_VOID(swiperWrapper);
    OffsetF swiperOffset = { 0.0f, 0.0f };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& padding = layoutProperty->CreatePaddingAndBorder();
    swiperOffset += OffsetF(padding.left.value_or(0.0), padding.top.value_or(0.0));
    swiperWrapper->GetGeometryNode()->SetMarginFrameOffset(swiperOffset);
    swiperWrapper->Layout();
}

void StepperLayoutAlgorithm::LayoutLeftButton(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(hostNode->HasLeftButtonNode());
    auto index = hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto controlHeight = static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    auto buttonHeight = leftButtonWrapper->GetGeometryNode()->GetFrameSize().Height();
    auto buttonHeightOffset = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - controlHeight;
    buttonHeightOffset += (controlHeight - buttonHeight) / 2;
    auto padding = static_cast<float>(stepperTheme->GetDefaultPaddingStart().ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidthOffset = padding + margin;
    OffsetF buttonOffset = { buttonWidthOffset, buttonHeightOffset };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& stepperPadding = layoutProperty->CreatePaddingAndBorder();
    buttonOffset += OffsetF(stepperPadding.left.value_or(0.0), -stepperPadding.bottom.value_or(0.0));
    auto geometryNode = leftButtonWrapper->GetGeometryNode();
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    auto isRightToLeft = stepperLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRightToLeft) {
        auto frameWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
        auto offsetX = frameWidth - geometryNode->GetFrameSize().Width() - buttonOffset.GetX();
        buttonOffset.SetX(offsetX);
    }
    geometryNode->SetMarginFrameOffset(buttonOffset);
    leftButtonWrapper->Layout();
}

void StepperLayoutAlgorithm::LayoutRightButton(LayoutWrapper* layoutWrapper)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(layoutWrapper->GetHostNode());
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID(hostNode->HasRightButtonNode());
    auto index = hostNode->GetChildIndexById(hostNode->GetRightButtonId());
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto frameSizeWidth = layoutWrapper->GetGeometryNode()->GetFrameSize().Width();
    auto rightButtonWidth = rightButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Width();
    auto padding = static_cast<float>(stepperTheme->GetDefaultPaddingEnd().ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidthOffset = frameSizeWidth - rightButtonWidth - padding - margin;
    auto controlHeight = static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    auto buttonHeight = rightButtonWrapper->GetGeometryNode()->GetFrameSize().Height();
    auto buttonHeightOffset = layoutWrapper->GetGeometryNode()->GetFrameSize().Height() - controlHeight;
    buttonHeightOffset += (controlHeight - buttonHeight) / 2;
    OffsetF buttonOffset = { buttonWidthOffset, buttonHeightOffset };
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    const auto& stepperPadding = layoutProperty->CreatePaddingAndBorder();
    buttonOffset -= OffsetF(stepperPadding.right.value_or(0.0), stepperPadding.bottom.value_or(0.0));
 
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    auto isRightToLeft = stepperLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRightToLeft) {
        auto offsetX = frameSizeWidth - rightButtonWidth - buttonOffset.GetX();
        buttonOffset.SetX(offsetX);
    }
    rightButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(buttonOffset);
    rightButtonWrapper->Layout();
}

} // namespace OHOS::Ace::NG
