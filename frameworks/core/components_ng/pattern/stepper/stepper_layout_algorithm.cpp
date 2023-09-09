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

#include "base/utils/utils.h"
#include "core/components/stepper/stepper_theme.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void StepperLayoutAlgorithm::Measure(LayoutWrapper* layoutWrapper)
{
    CHECK_NULL_VOID(layoutWrapper);
    auto layoutProperty = layoutWrapper->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = layoutWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    auto idealSize =
        CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
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

    MeasureSwiper(layoutWrapper, childLayoutConstraint);
    MeasureLeftButton(layoutWrapper, childLayoutConstraint);
    MeasureRightButton(layoutWrapper, childLayoutConstraint);
}

void StepperLayoutAlgorithm::MeasureSwiper(LayoutWrapper* layoutWrapper, LayoutConstraintF swiperLayoutConstraint)
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
    buttonLayoutConstraint.minSize = { 0, buttonHeight };
    buttonLayoutConstraint.maxSize = { buttonWidth, buttonHeight };
    buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, buttonHeight);

    auto index = hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto leftButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
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
    buttonLayoutConstraint.minSize = { 0, buttonHeight };
    buttonLayoutConstraint.maxSize = { buttonWidth, buttonHeight };
    buttonLayoutConstraint.selfIdealSize = OptionalSizeF(std::nullopt, buttonHeight);

    auto index = hostNode->GetChildIndexById(hostNode->GetRightButtonId());
    auto rightButtonWrapper = layoutWrapper->GetOrCreateChildByIndex(index);
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
        LOGW("Frame size is not positive.");
        return;
    }
    LayoutSwiper(layoutWrapper);
    LayoutLeftButton(layoutWrapper);
    LayoutRightButton(layoutWrapper);
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
    rightButtonWrapper->GetGeometryNode()->SetMarginFrameOffset(buttonOffset);
    rightButtonWrapper->Layout();
}

} // namespace OHOS::Ace::NG
