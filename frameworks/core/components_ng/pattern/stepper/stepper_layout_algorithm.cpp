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
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

void StepperLayoutAlgorithm::Measure(FrameNode* frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto constraint = layoutProperty->GetLayoutConstraint();
    const auto idealSize =
        CreateIdealSize(constraint.value(), Axis::HORIZONTAL, layoutProperty->GetMeasureType(), true);
    if (GreaterOrEqualToInfinity(idealSize.Width()) || GreaterOrEqualToInfinity(idealSize.Height())) {
        LOGW("Size is infinity.");
        geometryNode->SetFrameSize(SizeF());
        return;
    }
    geometryNode->SetFrameSize(idealSize);
    auto childLayoutConstraint = layoutProperty->CreateChildConstraint();
    childLayoutConstraint.parentIdealSize = OptionalSizeF(idealSize);

    MeasureSwiper(frameNode, childLayoutConstraint);
    MeasureLeftButton(frameNode, childLayoutConstraint);
    MeasureRightButton(frameNode, childLayoutConstraint);
}

void StepperLayoutAlgorithm::MeasureSwiper(FrameNode* frameNode, LayoutConstraintF swiperLayoutConstraint)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetSwiperId());
    auto swiper = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_VOID(swiper);
    auto swiperHeight = swiperLayoutConstraint.parentIdealSize.Height().value() -
                        static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    swiperLayoutConstraint.maxSize.SetHeight(swiperHeight);
    swiperLayoutConstraint.selfIdealSize.SetHeight(swiperHeight);
    swiperLayoutConstraint.selfIdealSize.SetWidth(swiperLayoutConstraint.parentIdealSize.Width());
    swiper->Measure(swiperLayoutConstraint);
}
void StepperLayoutAlgorithm::MeasureLeftButton(FrameNode* frameNode, LayoutConstraintF buttonLayoutConstraint)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID_NOLOG(hostNode->HasLeftButtonNode());

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
    auto leftButton = frameNode->GetFrameNodeByIndex(index);
    leftButton->Measure(buttonLayoutConstraint);
    MeasureText(leftButton, buttonLayoutConstraint, true);
}
void StepperLayoutAlgorithm::MeasureRightButton(FrameNode* frameNode, LayoutConstraintF buttonLayoutConstraint)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID_NOLOG(hostNode->HasRightButtonNode());

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
    auto rightButton = frameNode->GetFrameNodeByIndex(index);
    rightButton->Measure(buttonLayoutConstraint);
    MeasureText(rightButton, buttonLayoutConstraint, false);
}

void StepperLayoutAlgorithm::MeasureText(
    const RefPtr<FrameNode>& frameNode, const LayoutConstraintF& buttonLayoutConstraint, bool isLeft)
{
    CHECK_NULL_VOID_NOLOG(frameNode->GetTag() == std::string(V2::BUTTON_ETS_TAG));
    auto row = frameNode->GetFrameNodeByIndex(0);
    CHECK_NULL_VOID_NOLOG(row->GetTag() == std::string(V2::ROW_ETS_TAG));
    auto text = row->GetFrameNodeByIndex(isLeft ? 1 : 0);
    CHECK_NULL_VOID(text->GetTag() == std::string(V2::TEXT_ETS_TAG));

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
    text->Measure(textLayoutConstraint);
}

void StepperLayoutAlgorithm::Layout(FrameNode* frameNode)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto frameSize = geometryNode->GetFrameSize();
    if (!frameSize.IsPositive()) {
        LOGW("Frame size is not positive.");
        return;
    }
    LayoutSwiper(frameNode);
    LayoutLeftButton(frameNode);
    LayoutRightButton(frameNode);
}

void StepperLayoutAlgorithm::LayoutSwiper(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    auto index = hostNode->GetChildIndexById(hostNode->GetSwiperId());
    auto swiper = frameNode->GetFrameNodeByIndex(index);
    CHECK_NULL_VOID(swiper);
    OffsetF swiperOffset = { 0.0f, 0.0f };
    swiper->GetGeometryNode()->SetMarginFrameOffset(swiperOffset);
    swiper->Layout();
}

void StepperLayoutAlgorithm::LayoutLeftButton(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID_NOLOG(hostNode->HasLeftButtonNode());
    auto index = hostNode->GetChildIndexById(hostNode->GetLeftButtonId());
    auto leftButton = frameNode->GetFrameNodeByIndex(index);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto controlHeight = static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    auto buttonHeight = leftButton->GetGeometryNode()->GetFrameSize().Height();
    auto buttonHeightOffset = leftButton->GetGeometryNode()->GetFrameSize().Height() - controlHeight;
    buttonHeightOffset += (controlHeight - buttonHeight) / 2;
    auto padding = static_cast<float>(stepperTheme->GetDefaultPaddingStart().ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidthOffset = padding + margin;
    OffsetF buttonOffset = { buttonWidthOffset, buttonHeightOffset };
    auto geometryNode = leftButton->GetGeometryNode();
    geometryNode->SetMarginFrameOffset(buttonOffset);
    leftButton->Layout();
}

void StepperLayoutAlgorithm::LayoutRightButton(FrameNode* frameNode)
{
    auto hostNode = AceType::DynamicCast<StepperNode>(frameNode);
    CHECK_NULL_VOID(hostNode);
    CHECK_NULL_VOID_NOLOG(hostNode->HasRightButtonNode());
    auto index = hostNode->GetChildIndexById(hostNode->GetRightButtonId());
    auto rightButton = frameNode->GetFrameNodeByIndex(index);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto stepperTheme = pipeline->GetTheme<StepperTheme>();
    CHECK_NULL_VOID(stepperTheme);
    auto frameSizeWidth = frameNode->GetGeometryNode()->GetFrameSize().Width();
    auto rightButtonWidth = rightButton->GetGeometryNode()->GetMarginFrameSize().Width();
    auto padding = static_cast<float>(stepperTheme->GetDefaultPaddingEnd().ConvertToPx());
    auto margin = static_cast<float>(stepperTheme->GetControlMargin().ConvertToPx());
    auto buttonWidthOffset = frameSizeWidth - rightButtonWidth - padding - margin;
    auto controlHeight = static_cast<float>(stepperTheme->GetControlHeight().ConvertToPx());
    auto buttonHeight = rightButton->GetGeometryNode()->GetFrameSize().Height();
    auto buttonHeightOffset = frameNode->GetGeometryNode()->GetFrameSize().Height() - controlHeight;
    buttonHeightOffset += (controlHeight - buttonHeight) / 2;
    OffsetF buttonOffset = { buttonWidthOffset, buttonHeightOffset };
    rightButton->GetGeometryNode()->SetMarginFrameOffset(buttonOffset);
    rightButton->Layout();
}

} // namespace OHOS::Ace::NG
