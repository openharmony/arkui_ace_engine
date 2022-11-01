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

#include <optional>

#include "core/components/stepper/stepper_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void StepperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto stepperTheme = themeManager->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    const auto idealSize =
        CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreatOrEqual(idealSize.Width(), Infinity<float>()) || GreatOrEqual(idealSize.Height(), Infinity<float>())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    // Measure button
    float maxButtonHeight = 0.0f;
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    if (leftButtonWrapper) {
        auto buttonLayoutConstraint = CreateButtonLayoutConstraint(childLayoutConstraint, true);
        if (!layoutLeftButton_) {
            buttonLayoutConstraint.minSize = { 0, 0 };
            buttonLayoutConstraint.maxSize = { 0, 0 };
            buttonLayoutConstraint.selfIdealSize = { 0, 0 };
        }
        leftButtonWrapper->Measure(buttonLayoutConstraint);
        maxButtonHeight = maxButtonHeight > leftButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Height()
                              ? maxButtonHeight
                              : leftButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    if (rightButtonWrapper) {
        auto buttonLayoutConstraint = CreateButtonLayoutConstraint(childLayoutConstraint, false);
        rightButtonWrapper->Measure(buttonLayoutConstraint);
        maxButtonHeight = maxButtonHeight > rightButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Height()
                              ? maxButtonHeight
                              : rightButtonWrapper->GetGeometryNode()->GetMarginFrameSize().Height();
    }

    // Measure swiper.
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    if (swiperWrapper) {
        auto swiperLayoutConstraint = childLayoutConstraint;
        auto controlMargin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
        swiperLayoutConstraint.maxSize.SetHeight(
            childLayoutConstraint.maxSize.Height() - maxButtonHeight - controlMargin - controlMargin);
        swiperLayoutConstraint.parentIdealSize.SetHeight(
            childLayoutConstraint.parentIdealSize.Height().value() - maxButtonHeight - controlMargin - controlMargin);
        swiperLayoutConstraint.selfIdealSize.SetHeight(
            childLayoutConstraint.maxSize.Height() - maxButtonHeight - controlMargin - controlMargin);
        swiperLayoutConstraint.selfIdealSize.SetWidth(childLayoutConstraint.maxSize.Width());
        swiperWrapper->Measure(swiperLayoutConstraint);
    }
}
void StepperLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    auto stepperTheme = themeManager->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    CHECK_NULL_VOID(layoutWrapper);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    if (!frameSize.IsPositive()) {
        LOGW("Frame size is not positive.");
        return;
    }
    auto swiperWrapper = layoutWrapper->GetOrCreateChildByIndex(0);
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(1);
    CHECK_NULL_VOID(leftButtonWrapper);
    auto leftButtonTextWrapper = leftButtonWrapper->GetOrCreateChildByIndex(0);
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(2);
    CHECK_NULL_VOID(rightButtonWrapper);
    auto rightButtonTextWrapper = rightButtonWrapper->GetOrCreateChildByIndex(0);
    if (!swiperWrapper || !leftButtonWrapper || !rightButtonWrapper) {
        return;
    }
    // Set swiper offset
    OffsetF swiperOffset = { 0.0f, 0.0f };
    swiperWrapper->GetGeometryNode()->SetMarginFrameOffset(swiperOffset);

    // git swiper frame Size
    auto swiperGeometryNode = swiperWrapper->GetGeometryNode();
    CHECK_NULL_VOID(swiperGeometryNode);
    auto swiperFrameSize = swiperGeometryNode->GetMarginFrameSize();

    auto buttonHeightOffset =
        swiperFrameSize.Height() + static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    // Set left button offset
    auto leftButtonWidthOffset = static_cast<float>(
        stepperTheme->GetDefaultPaddingStart().ConvertToPx() + stepperTheme->GetControlMargin().ConvertToPx());
    OffsetF leftButtonOffset = { leftButtonWidthOffset, buttonHeightOffset };
    leftButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(leftButtonOffset);

    // Set right button offset
    auto rightButtonGeometryNode = rightButtonWrapper->GetGeometryNode();
    CHECK_NULL_VOID(rightButtonGeometryNode);
    auto rightButtonFrameSize = rightButtonGeometryNode->GetMarginFrameSize();
    auto rightButtonWidthOffset =
        frameSize.Width() - rightButtonFrameSize.Width() -
        static_cast<float>((stepperTheme->GetDefaultPaddingEnd() + stepperTheme->GetControlMargin()).ConvertToPx());
    OffsetF rightButtonOffset = { rightButtonWidthOffset, buttonHeightOffset };
    rightButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(rightButtonOffset);
}

LayoutConstraintF StepperLayoutAlgorithm::CreateButtonLayoutConstraint(
    const LayoutConstraintF& childLayoutConstraint, bool isLeft)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, LayoutConstraintF());
    auto themeManager = pipeline->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, LayoutConstraintF());
    auto stepperTheme = themeManager->GetTheme<StepperTheme>();
    CHECK_NULL_RETURN(stepperTheme, LayoutConstraintF());
    auto buttonLayoutConstraint = childLayoutConstraint;
    // Two buttons each half, and remove the white space.
    auto padding = isLeft ? stepperTheme->GetDefaultPaddingStart() : stepperTheme->GetDefaultPaddingEnd();
    auto buttonWidth = (childLayoutConstraint.parentIdealSize.Width().value() / 2) -
                       static_cast<float>(padding.ConvertToPx() + 2 * stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonHeight = static_cast<float>(
        stepperTheme->GetControlHeight().ConvertToPx() - 2 * stepperTheme->GetControlMargin().ConvertToPx());

    buttonLayoutConstraint.minSize = { 0, buttonHeight };
    buttonLayoutConstraint.maxSize = { buttonWidth, buttonHeight };
    buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, buttonHeight);
    return buttonLayoutConstraint;
}

} // namespace OHOS::Ace::NG