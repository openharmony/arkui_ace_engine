/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/stepper/stepper_pattern.h"

#include <algorithm>

#include "base/i18n/localization.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {

void StepperPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_VOID(swiperNode);
    index_ = swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->GetIndex().value_or(0);

    auto swiperEventHub = swiperNode->GetEventHub<SwiperEventHub>();
    CHECK_NULL_VOID(swiperEventHub);
    auto stepperLayoutProperty = hostNode->GetLayoutProperty();
    auto layoutPolicy = stepperLayoutProperty->GetLayoutPolicyProperty();
    if (layoutPolicy.has_value()) {
        swiperNode->GetLayoutProperty()->UpdateLayoutPolicyProperty(
            layoutPolicy.value().widthLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH), true);
        swiperNode->GetLayoutProperty()->UpdateLayoutPolicyProperty(
            layoutPolicy.value().heightLayoutPolicy_.value_or(LayoutCalPolicy::NO_MATCH), false);
    }
    maxIndex_ = TotalCount();
    if (index_ > maxIndex_) {
        index_ = 0;
        hostNode->GetLayoutProperty<StepperLayoutProperty>()->UpdateIndex(index_);
        swiperNode->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(index_);
        swiperNode->MarkModifyDone();
        swiperNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    InitSwiperChangeEvent(swiperEventHub);
    UpdateOrCreateLeftButtonNode(index_);
    UpdateOrCreateRightButtonNode(index_);
    InitButtonClickEvent();
    SetAccessibilityAction();
}

void StepperPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_PARENT);
    host->GetRenderContext()->UpdateClipEdge(true);
}

void StepperPattern::InitSwiperChangeEvent(const RefPtr<SwiperEventHub>& swiperEventHub)
{
    ChangeEvent changeEvent = [weak = WeakClaim(this)](int32_t index) {
        auto stepperPattern = weak.Upgrade();
        CHECK_NULL_VOID(stepperPattern->TotalCount() > -1);
        stepperPattern->UpdateIndexWithoutMeasure(index);
        stepperPattern->UpdateOrCreateLeftButtonNode(index);
        stepperPattern->UpdateOrCreateRightButtonNode(index);
        stepperPattern->InitButtonClickEvent();
    };
    if (swiperChangeEvent_) {
        (*swiperChangeEvent_).swap(changeEvent);
    } else {
        swiperChangeEvent_ = std::make_shared<ChangeEvent>(std::move(changeEvent));
        swiperEventHub->AddOnChangeEvent(swiperChangeEvent_);
    }
}

void StepperPattern::UpdateIndexWithoutMeasure(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    stepperLayoutProperty->UpdateIndexWithoutMeasure(index);

    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_VOID(swiperNode);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    CHECK_NULL_VOID(swiperLayoutProperty);
    swiperLayoutProperty->UpdateIndexWithoutMeasure(index);
}

void StepperPattern::UpdateOrCreateLeftButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    isRightToLeft_ = stepperLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (index <= 0) {
        hostNode->RemoveLeftButtonNode();
    } else if (!hostNode->HasLeftButtonNode()) {
        CreateLeftButtonNode();
        UpdateLeftButtonNode(index);
    } else {
        UpdateLeftButtonNode(index);
    }
    index_ = index;
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void StepperPattern::CreateLeftButtonNode()
{
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    // Create buttonNode
    auto buttonId = hostNode->GetLeftButtonId();
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    buttonPattern->setComponentButtonType(ComponentButtonType::STEPPER);
    buttonPattern->SetFocusBorderColor(stepperTheme->GetFocusColor());
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, buttonId, buttonPattern);
    auto focusHub = buttonNode->GetOrCreateFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusDependence(FocusDependence::SELF);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
    buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(stepperTheme->GetRadius()));
    buttonNode->MountToParent(hostNode);
    buttonNode->MarkModifyDone();

    // Create rowNode
    auto rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rowLayoutProperty = rowNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowLayoutProperty);
    rowLayoutProperty->UpdateSpace(stepperTheme->GetControlPadding());
    rowLayoutProperty->UpdateMargin(
        { CalcLength(stepperTheme->GetControlPadding()), CalcLength(stepperTheme->GetControlPadding()) });
    rowLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    rowNode->MountToParent(buttonNode);
    rowNode->MarkModifyDone();

    // Create imageNode
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetArrowWidth()), CalcLength(stepperTheme->GetArrowHeight())));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    if (isRightToLeft_) {
        rowNode->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_NEXT_ARROW);
    } else {
        rowNode->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::LTR);
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_BACK_ARROW);
    }
    leftImage_ = imageNode;
    imageSourceInfo.SetFillColor(stepperTheme->GetArrowColor());
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    SizeF sourceSize(static_cast<float>(stepperTheme->GetArrowWidth().ConvertToPx()),
        static_cast<float>(stepperTheme->GetArrowHeight().ConvertToPx()));
    imageLayoutProperty->UpdateSourceSize(sourceSize);
    imageNode->MountToParent(rowNode);
    imageNode->MarkModifyDone();

    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    textLayoutProperty->UpdateTextColor(stepperTheme->GetTextStyle().GetTextColor());
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateAdaptMinFontSize(stepperTheme->GetMinFontSize());
    textLayoutProperty->UpdateAdaptMaxFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    textLayoutProperty->UpdateMaxLines(stepperTheme->GetTextMaxLines());
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->GetFocusHub()->SetFocusable(true);
    textNode->MountToParent(rowNode);
    textNode->MarkModifyDone();
}

void StepperPattern::UpdateLeftButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto buttonNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId()));
    auto rowNode = buttonNode->GetChildAtIndex(0);
    auto textNode = DynamicCast<FrameNode>(rowNode->GetChildAtIndex(1));

    auto swiperNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId()));
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index)));
    CHECK_NULL_VOID(stepperItemNode);
    auto stepperItemLayoutProperty = stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>();
    auto theme = GetTheme();
    auto buttonBackText = theme ? theme->GetStepperBack() : "";
    auto leftLabel = stepperItemLayoutProperty->GetLeftLabel().value_or(buttonBackText);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(leftLabel);

    textNode->MarkModifyDone();
    textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void StepperPattern::UpdateOrCreateRightButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    CreateRightButtonNode(index);
    index_ = index;
    hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void StepperPattern::CreateRightButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto swiperNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId()));
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index)));
    CHECK_NULL_VOID(stepperItemNode);
    auto theme = GetTheme();
    CHECK_NULL_VOID(theme);
    auto labelStatus =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus().value_or("normal");
    if (labelStatus == "normal") {
        if (index == maxIndex_) {
            CreateArrowlessRightButtonNode(index, false, theme->GetStepperStart());
        } else {
            CreateArrowRightButtonNode(index, false);
        }
    } else if (labelStatus == "disabled") {
        if (index == maxIndex_) {
            CreateArrowlessRightButtonNode(index, true, theme->GetStepperStart());
        } else {
            CreateArrowRightButtonNode(index, true);
        }
    } else if (labelStatus == "waiting") {
        CreateWaitingRightButtonNode();
    } else if (labelStatus == "skip") {
        CreateArrowlessRightButtonNode(index, false, theme->GetStepperSkip());
    }
}

void StepperPattern::CreateArrowRightButtonNode(int32_t index, bool isDisabled)
{
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    // get rightLabel
    auto swiperNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId()));
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index)));
    CHECK_NULL_VOID(stepperItemNode);
    auto buttonNextText = stepperTheme->GetStepperNext();
    auto rightLabel =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetRightLabel().value_or(buttonNextText);
    // Create or get buttonNode
    if (isLoadingButton_) {
        hostNode->RemoveRightButtonNode();
        isLoadingButton_ = false;
    }
    auto hasRightButton = hostNode->HasRightButtonNode();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    if (hasRightButton) {
        buttonNode->Clean(true);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } else {
        auto buttonPattern = buttonNode->GetPattern<ButtonPattern>();
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->setComponentButtonType(ComponentButtonType::STEPPER);
        buttonPattern->SetFocusBorderColor(stepperTheme->GetFocusColor());
        buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(buttonLayoutProperty);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(stepperTheme->GetRadius()));
        buttonNode->MountToParent(hostNode);
    }
    isDisabled ? buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(false)
               : buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(true);
    if (!isDisabled) {
        auto focusHub = buttonNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusDependence(FocusDependence::SELF);
    }
    buttonNode->MarkModifyDone();

    // Create rowNode
    auto rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    auto rowLayoutProperty = rowNode->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(rowLayoutProperty);
    rowLayoutProperty->UpdateSpace(stepperTheme->GetControlPadding());
    rowLayoutProperty->UpdateMargin(
        { CalcLength(stepperTheme->GetControlPadding()), CalcLength(stepperTheme->GetControlPadding()) });
    rowNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    rowNode->MountToParent(buttonNode);
    rowNode->MarkModifyDone();

    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    textLayoutProperty->UpdateContent(rightLabel);
    auto textColor = stepperTheme->GetTextStyle().GetTextColor();
    if (isDisabled) {
        textColor = textColor.BlendOpacity(stepperTheme->GetDisabledAlpha());
    }
    textLayoutProperty->UpdateTextColor(textColor);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateAdaptMinFontSize(stepperTheme->GetMinFontSize());
    textLayoutProperty->UpdateAdaptMaxFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    textLayoutProperty->UpdateMaxLines(stepperTheme->GetTextMaxLines());
    textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    textNode->GetFocusHub()->SetFocusable(true);
    textNode->MountToParent(rowNode);
    textNode->MarkModifyDone();

    // Create imageNode
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto imageLayoutProperty = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(imageLayoutProperty);
    imageLayoutProperty->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetArrowWidth()), CalcLength(stepperTheme->GetArrowHeight())));
    imageLayoutProperty->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    if (isRightToLeft_) {
        rowNode->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_BACK_ARROW);
    } else {
        rowNode->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::LTR);
        imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_NEXT_ARROW);
    }
    rightImage_ = imageNode;
    auto imageColor = stepperTheme->GetArrowColor();
    if (isDisabled) {
        imageColor = imageColor.BlendOpacity(stepperTheme->GetDisabledAlpha());
    }
    imageSourceInfo.SetFillColor(imageColor);
    imageLayoutProperty->UpdateImageSourceInfo(imageSourceInfo);
    SizeF sourceSize(static_cast<float>(stepperTheme->GetArrowWidth().ConvertToPx()),
        static_cast<float>(stepperTheme->GetArrowHeight().ConvertToPx()));
    imageLayoutProperty->UpdateSourceSize(sourceSize);
    imageNode->MountToParent(rowNode);
    imageNode->MarkModifyDone();
}

void StepperPattern::CreateArrowlessRightButtonNode(int32_t index, bool isDisabled, const std::string& defaultContent)
{
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    // get rightLabel
    auto swiperNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId()));
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index)));
    auto rightLabel =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetRightLabel().value_or(defaultContent);
    // Create or get buttonNode
    if (isLoadingButton_) {
        hostNode->RemoveRightButtonNode();
        isLoadingButton_ = false;
    }
    auto hasRightButton = hostNode->HasRightButtonNode();
    auto buttonNode = FrameNode::GetOrCreateFrameNode(
        V2::BUTTON_ETS_TAG, hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    if (hasRightButton) {
        buttonNode->Clean(true);
        buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    } else {
        auto buttonPattern = buttonNode->GetPattern<ButtonPattern>();
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->setComponentButtonType(ComponentButtonType::STEPPER);
        buttonPattern->SetFocusBorderColor(stepperTheme->GetFocusColor());
        buttonNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
        auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
        CHECK_NULL_VOID(buttonLayoutProperty);
        buttonLayoutProperty->UpdateType(ButtonType::NORMAL);
        buttonLayoutProperty->UpdateMeasureType(MeasureType::MATCH_CONTENT);
        buttonLayoutProperty->UpdateBorderRadius(BorderRadiusProperty(stepperTheme->GetRadius()));
        buttonNode->MountToParent(hostNode);
    }
    isDisabled ? buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(false)
               : buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(true);
    if (!isDisabled) {
        auto focusHub = buttonNode->GetOrCreateFocusHub();
        CHECK_NULL_VOID(focusHub);
        focusHub->SetFocusDependence(FocusDependence::SELF);
    }
    buttonNode->MarkModifyDone();

    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    textLayoutProperty->UpdateContent(rightLabel);
    textLayoutProperty->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateAdaptMinFontSize(stepperTheme->GetMinFontSize());
    textLayoutProperty->UpdateAdaptMaxFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textLayoutProperty->UpdateMaxLines(stepperTheme->GetTextMaxLines());
    textLayoutProperty->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    auto textColor = stepperTheme->GetTextStyle().GetTextColor();
    if (isDisabled) {
        textColor = textColor.BlendOpacity(stepperTheme->GetDisabledAlpha());
    }
    textLayoutProperty->UpdateTextColor(textColor);
    textLayoutProperty->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    textLayoutProperty->UpdateMargin(
        { CalcLength(stepperTheme->GetControlPadding()), CalcLength(stepperTheme->GetControlPadding()) });
    textNode->GetFocusHub()->SetFocusable(true);
    textNode->MountToParent(buttonNode);
    textNode->MarkModifyDone();
}

void StepperPattern::CreateWaitingRightButtonNode()
{
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    // Create loadingProgressNode
    hostNode->RemoveRightButtonNode();
    auto loadingProgressNode = FrameNode::GetOrCreateFrameNode(V2::LOADING_PROGRESS_ETS_TAG,
        hostNode->GetRightButtonId(), []() { return AceType::MakeRefPtr<LoadingProgressPattern>(); });
    loadingProgressNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetProgressDiameter()), CalcLength(stepperTheme->GetProgressDiameter())));
    loadingProgressNode->GetPaintProperty<LoadingProgressPaintProperty>()->UpdateColor(
        stepperTheme->GetProgressColor());
    loadingProgressNode->GetRenderContext()->UpdateForegroundColor(stepperTheme->GetProgressColor());
    loadingProgressNode->MountToParent(hostNode);
    loadingProgressNode->MarkModifyDone();
    isLoadingButton_ = true;
}

void StepperPattern::InitButtonClickEvent()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);

    if (hostNode->HasLeftButtonNode()) {
        auto leftButtonNode =
            DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId())));
        CHECK_NULL_VOID(leftButtonNode);
        auto leftGestureHub = leftButtonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(leftGestureHub);
        if (leftGestureHub->IsClickEventsEmpty()) {
            auto leftClickEvent = [weak = WeakClaim(this)](const GestureEvent& info) {
                auto stepperPattern = weak.Upgrade();
                CHECK_NULL_VOID(stepperPattern);
                stepperPattern->HandlingLeftButtonClickEvent();
            };
            leftGestureHub->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(leftClickEvent)));
        }
    }

    if (hostNode->HasRightButtonNode()) {
        auto rightButtonNode = DynamicCast<FrameNode>(
            hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId())));
        CHECK_NULL_VOID(rightButtonNode);
        auto rightGestureHub = rightButtonNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(rightGestureHub);
        if (rightGestureHub->IsClickEventsEmpty()) {
            auto rightClickEvent = [weak = WeakClaim(this)](const GestureEvent& info) {
                auto stepperPattern = weak.Upgrade();
                CHECK_NULL_VOID(stepperPattern);
                stepperPattern->HandlingRightButtonClickEvent();
            };
            rightGestureHub->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(rightClickEvent)));
        }
    }
}

void StepperPattern::HandlingLeftButtonClickEvent()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperHub = hostNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(stepperHub);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    auto swiperAnimationController = swiperNode->GetPattern<SwiperPattern>()->GetController();
    if (swiperAnimationController && !swiperAnimationController->IsStopped()) {
        return;
    }
    auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
    stepperHub->FireChangeEvent(index_, std::clamp<int32_t>(index_ - 1, 0, maxIndex_));
    stepperHub->FirePreviousEvent(index_, std::clamp<int32_t>(index_ - 1, 0, maxIndex_));
    swiperController->SwipeTo(std::clamp<int32_t>(index_ - 1, 0, maxIndex_));
}

void StepperPattern::HandlingRightButtonClickEvent()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperHub = hostNode->GetEventHub<StepperEventHub>();
    CHECK_NULL_VOID(stepperHub);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    auto swiperAnimationController = swiperNode->GetPattern<SwiperPattern>()->GetController();
    if (swiperAnimationController && !swiperAnimationController->IsStopped()) {
        return;
    }
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index_)));
    CHECK_NULL_VOID(stepperItemNode);
    auto labelStatus =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus().value_or("normal");
    if (labelStatus == "skip") {
        stepperHub->FireSkipEvent(index_);
    } else if (labelStatus == "normal") {
        if (index_ == maxIndex_) {
            stepperHub->FireFinishEvent(index_);
        } else {
            stepperHub->FireChangeEvent(index_, std::clamp<int32_t>(index_ + 1, 0, maxIndex_));
            stepperHub->FireNextEvent(index_, std::clamp<int32_t>(index_ + 1, 0, maxIndex_));
            auto swiperController = swiperNode->GetPattern<SwiperPattern>()->GetSwiperController();
            swiperController->SwipeTo(std::clamp<int32_t>(index_ + 1, 0, maxIndex_));
        }
    }
}

int32_t StepperPattern::TotalCount() const
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, 0);
    auto swiperNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId())));
    CHECK_NULL_RETURN(swiperNode, 0);
    return swiperNode->TotalChildCount() - 1;
}

void StepperPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlingRightButtonClickEvent();
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlingLeftButtonClickEvent();
    });
}

WeakPtr<FocusHub> StepperPattern::GetFocusNode(FocusStep step, const WeakPtr<FocusHub>& currentFocusNode)
{
    auto curFocusNode = currentFocusNode.Upgrade();
    CHECK_NULL_RETURN(curFocusNode, nullptr);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_RETURN(hostNode, nullptr);

    auto swiperNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetSwiperId()));
    CHECK_NULL_RETURN(swiperNode, nullptr);
    auto stepperItemNode = DynamicCast<FrameNode>(swiperNode->GetChildAtIndex(static_cast<int32_t>(index_)));
    CHECK_NULL_RETURN(stepperItemNode, nullptr);
    auto buttonFocusHub = stepperItemNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(buttonFocusHub, nullptr);

    auto stepperItemLayoutProperty = stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>();
    CHECK_NULL_RETURN(stepperItemLayoutProperty, nullptr);
    auto labelStatus = stepperItemLayoutProperty->GetLabelStatus().value_or("normal");

    if (hostNode->HasLeftButtonNode()) {
        auto leftButtonNode =
            DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId())));
        CHECK_NULL_RETURN(leftButtonNode, nullptr);
        leftFocusHub_ = leftButtonNode->GetOrCreateFocusHub();
    }

    auto rightButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId())));
    CHECK_NULL_RETURN(rightButtonNode, nullptr);
    auto rightFocusHub = rightButtonNode->GetOrCreateFocusHub();
    CHECK_NULL_RETURN(rightFocusHub, nullptr);

    if (labelStatus == "normal" || labelStatus == "skip") {
        if (step == FocusStep::UP || step == FocusStep::LEFT || step == FocusStep::SHIFT_TAB) {
            return curFocusNode == leftFocusHub_ ? buttonFocusHub : leftFocusHub_;
        }

        if (curFocusNode != leftFocusHub_ && curFocusNode != rightFocusHub) {
            return hostNode->HasLeftButtonNode() ? leftFocusHub_ : rightFocusHub;
        }

        if (curFocusNode == rightFocusHub && !hostNode->HasLeftButtonNode()) {
            return buttonFocusHub;
        }

        if (step == FocusStep::DOWN || step == FocusStep::RIGHT || step == FocusStep::TAB) {
            return curFocusNode == buttonFocusHub ? leftFocusHub_ : rightFocusHub;
        }
    } else if (labelStatus == "disabled" || labelStatus == "waiting") {
        return curFocusNode == leftFocusHub_ ? buttonFocusHub : leftFocusHub_;
    }
    return nullptr;
}

void StepperPattern::OnColorConfigurationUpdate()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    auto textColor = stepperTheme->GetTextStyle().GetTextColor();
    auto leftButtonNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetLeftButtonId()));
    if (leftButtonNode) {
        auto leftButtonFrameNode = DynamicCast<FrameNode>(leftButtonNode);
        CHECK_NULL_VOID(leftButtonFrameNode);
        ButtonSkipColorConfigurationUpdate(leftButtonFrameNode);
        auto renderContext = leftButtonFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(stepperTheme->GetMouseHoverColor().ChangeOpacity(0));
        auto rowNode = leftButtonFrameNode->GetChildAtIndex(0);
        CHECK_NULL_VOID(rowNode);
        auto textFrameNode = DynamicCast<FrameNode>(rowNode->GetChildAtIndex(1));
        CHECK_NULL_VOID(textFrameNode);
        auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->UpdateTextColor(textColor);
    }
    auto rightButtonNode = hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId()));
    if (rightButtonNode) {
        auto rightButtonFrameNode = DynamicCast<FrameNode>(rightButtonNode);
        CHECK_NULL_VOID(rightButtonFrameNode);
        ButtonSkipColorConfigurationUpdate(rightButtonFrameNode);
        auto renderContext = rightButtonFrameNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackgroundColor(stepperTheme->GetMouseHoverColor().ChangeOpacity(0));
        auto firstChild = rightButtonFrameNode->GetFirstChild();
        CHECK_NULL_VOID(firstChild);
        if (firstChild->GetTag() == V2::ROW_ETS_TAG) {
            auto textFrameNode = DynamicCast<FrameNode>(firstChild->GetChildAtIndex(0));
            CHECK_NULL_VOID(textFrameNode);
            auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateTextColor(textColor);
        }
        if (firstChild->GetTag() == V2::TEXT_ETS_TAG) {
            auto textFrameNode = DynamicCast<FrameNode>(firstChild);
            CHECK_NULL_VOID(textFrameNode);
            auto layoutProperty = textFrameNode->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(layoutProperty);
            layoutProperty->UpdateTextColor(textColor);
        }
    }
}

void StepperPattern::ButtonSkipColorConfigurationUpdate(const RefPtr<FrameNode>& buttonNode)
{
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSkipColorConfigurationUpdate();
}

void StepperPattern::OnLanguageConfigurationUpdate()
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    auto stepperLayoutProperty = hostNode->GetLayoutProperty<StepperLayoutProperty>();
    CHECK_NULL_VOID(stepperLayoutProperty);
    auto isRightToLeft = stepperLayoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    if (isRightToLeft != isRightToLeft_) {
        auto hostNode = AceType::DynamicCast<StepperNode>(GetHost());
        CHECK_NULL_VOID(hostNode);
        hostNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        isRightToLeft_ = isRightToLeft;

        auto stepperTheme = GetTheme();
        CHECK_NULL_VOID(stepperTheme);
        if (leftImage_) {
            auto leftimageLayoutProperty = leftImage_->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(leftimageLayoutProperty);
            auto leftRow = DynamicCast<FrameNode>(leftImage_->GetParent());
            CHECK_NULL_VOID(leftRow);
            
            ImageSourceInfo leftimageSourceInfo;
            if (isRightToLeft_) {
                leftRow->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
                leftimageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_NEXT_ARROW);
            } else {
                leftRow->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::LTR);
                leftimageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_BACK_ARROW);
            }
            leftimageSourceInfo.SetFillColor(stepperTheme->GetArrowColor());
            leftimageLayoutProperty->UpdateImageSourceInfo(leftimageSourceInfo);
            leftImage_->MarkModifyDone();
        }
        if (rightImage_) {
            auto rightimageLayoutProperty = rightImage_->GetLayoutProperty<ImageLayoutProperty>();
            CHECK_NULL_VOID(rightimageLayoutProperty);
            auto rightRow = DynamicCast<FrameNode>(rightImage_->GetParent());
            CHECK_NULL_VOID(rightRow);
            ImageSourceInfo rightimageSourceInfo;
            if (isRightToLeft_) {
                rightRow->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::RTL);
                rightimageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_BACK_ARROW);
            } else {
                rightRow->GetLayoutProperty()->UpdateLayoutDirection(TextDirection::LTR);
                rightimageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_NEXT_ARROW);
            }
            rightimageSourceInfo.SetFillColor(stepperTheme->GetArrowColor());
            rightimageLayoutProperty->UpdateImageSourceInfo(rightimageSourceInfo);
            rightImage_->MarkModifyDone();
        }
    }
}
} // namespace OHOS::Ace::NG
