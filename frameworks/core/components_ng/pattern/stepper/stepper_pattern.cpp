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

#include "core/components_ng/pattern/stepper/stepper_pattern.h"

#include <algorithm>

#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "core/components/stepper/stepper_theme.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/loading_progress/loading_progress_pattern.h"
#include "core/components_ng/pattern/stepper/stepper_item_layout_property.h"
#include "core/components_ng/pattern/stepper/stepper_node.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t PRESS_ANIMATION_DURATION = 100;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;

constexpr float BUTTON_ON_HOVER_BEZIER_CURVE_X0 = 0.2f;
constexpr float BUTTON_ON_HOVER_BEZIER_CURVE_Y0 = 0.0f;
constexpr float BUTTON_ON_HOVER_BEZIER_CURVE_X1 = 0.2f;
constexpr float BUTTON_ON_HOVER_BEZIER_CURVE_Y1 = 1.0f;

constexpr float BUTTON_ON_PRESS_BEZIER_CURVE_X0 = 0.33f;
constexpr float BUTTON_ON_PRESS_BEZIER_CURVE_Y0 = 0.0f;
constexpr float BUTTON_ON_PRESS_BEZIER_CURVE_X1 = 0.67f;
constexpr float BUTTON_ON_PRESS_BEZIER_CURVE_Y1 = 1.0f;
} // namespace

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
        CHECK_NULL_VOID_NOLOG(stepperPattern->TotalCount() > -1);
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
    CHECK_NULL_VOID(buttonNode);
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(stepperTheme->GetMouseHoverColor().ChangeOpacity(0));
    buttonNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    auto buttonRadius = stepperTheme->GetRadius();
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateBorderRadius(BorderRadiusProperty(buttonRadius));
    buttonNode->MountToParent(hostNode);
    buttonNode->MarkModifyDone();
    InitButtonOnHoverEvent(buttonNode, true);
    InitButtonTouchEvent(buttonNode);
    // Create rowNode
    auto rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    rowNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateSpace(stepperTheme->GetControlPadding());
    rowNode->GetLayoutProperty()->UpdateMargin(
        { CalcLength(stepperTheme->GetControlPadding()), CalcLength(stepperTheme->GetControlPadding()) });
    rowNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    rowNode->MountToParent(buttonNode);
    rowNode->MarkModifyDone();
    // Create imageNode
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetArrowWidth()), CalcLength(stepperTheme->GetArrowHeight())));
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_BACK_ARROW);
    imageSourceInfo.SetFillColor(stepperTheme->GetArrowColor().BlendOpacity(stepperTheme->GetDefaultAlpha()));
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(imageSourceInfo);
    SizeF sourceSize(static_cast<float>(stepperTheme->GetArrowWidth().ConvertToPx()),
        static_cast<float>(stepperTheme->GetArrowHeight().ConvertToPx()));
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateSourceSize(sourceSize);
    imageNode->MountToParent(rowNode);
    imageNode->MarkModifyDone();
    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    auto textColor = stepperTheme->GetTextStyle().GetTextColor().BlendOpacity(stepperTheme->GetDefaultAlpha());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextColor(textColor);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateAdaptMinFontSize(stepperTheme->GetMinFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateAdaptMaxFontSize(
        stepperTheme->GetTextStyle().GetFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateMaxLines(stepperTheme->GetTextMaxLines());
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
    auto buttonBackText = Localization::GetInstance()->GetEntryLetters("stepper.back");
    auto leftLabel = stepperItemLayoutProperty->GetLeftLabel().value_or(buttonBackText);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(leftLabel);

    textNode->MarkModifyDone();
    buttonNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void StepperPattern::UpdateOrCreateRightButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    if (!hostNode->HasRightButtonNode()) {
        CreateRightButtonNode(index);
    } else {
        UpdateRightButtonNode(index);
    }
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
    auto labelStatus =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetLabelStatus().value_or("normal");
    if (labelStatus == "normal") {
        isRightLabelDisable_ = false;
        if (index == maxIndex_) {
            CreateArrowlessRightButtonNode(index, Localization::GetInstance()->GetEntryLetters("stepper.start"));
        } else {
            CreateArrowRightButtonNode(index, false);
        }
    } else if (labelStatus == "disabled") {
        isRightLabelDisable_ = true;
        CreateArrowRightButtonNode(index, true);
    } else if (labelStatus == "waiting") {
        isRightLabelDisable_ = false;
        CreateWaitingRightButtonNode();
    } else if (labelStatus == "skip") {
        isRightLabelDisable_ = false;
        CreateArrowlessRightButtonNode(index, Localization::GetInstance()->GetEntryLetters("stepper.skip"));
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
    auto buttonNextText = Localization::GetInstance()->GetEntryLetters("stepper.next");
    auto rightLabel =
        stepperItemNode->GetLayoutProperty<StepperItemLayoutProperty>()->GetRightLabel().value_or(buttonNextText);
    // Create buttonNode
    auto buttonId = hostNode->GetRightButtonId();
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    buttonPattern->setComponentButtonType(ComponentButtonType::STEPPER);
    buttonPattern->SetFocusBorderColor(stepperTheme->GetFocusColor());
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, buttonId, buttonPattern);
    CHECK_NULL_VOID(buttonNode);
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    Color buttonBackgroundColor =
        rightIsHover_ ? stepperTheme->GetMouseHoverColor() : stepperTheme->GetMouseHoverColor().ChangeOpacity(0);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(buttonBackgroundColor);
    buttonNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    auto buttonRadius = stepperTheme->GetRadius();
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateBorderRadius(BorderRadiusProperty(buttonRadius));
    isRightLabelDisable_ ? buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(false)
                         : buttonNode->GetEventHub<ButtonEventHub>()->SetEnabled(true);
    buttonNode->MountToParent(hostNode);
    buttonNode->MarkModifyDone();
    InitButtonOnHoverEvent(buttonNode, false);
    InitButtonTouchEvent(buttonNode);
    // Create rowNode
    auto rowNode = FrameNode::GetOrCreateFrameNode(V2::ROW_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });
    rowNode->GetLayoutProperty<LinearLayoutProperty>()->UpdateSpace(stepperTheme->GetControlPadding());
    rowNode->GetLayoutProperty()->UpdateMargin(
        { CalcLength(stepperTheme->GetControlPadding()), CalcLength(stepperTheme->GetControlPadding()) });
    rowNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    rowNode->MountToParent(buttonNode);
    rowNode->MarkModifyDone();
    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(rightLabel);
    auto textColor = stepperTheme->GetTextStyle().GetTextColor();
    textColor = isDisabled ? textColor.BlendOpacity(stepperTheme->GetDisabledAlpha())
                           : textColor.BlendOpacity(stepperTheme->GetDefaultAlpha());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextColor(textColor);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateAdaptMinFontSize(stepperTheme->GetMinFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateAdaptMaxFontSize(
        stepperTheme->GetTextStyle().GetFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateMaxLines(stepperTheme->GetTextMaxLines());
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->GetFocusHub()->SetFocusable(true);
    textNode->MountToParent(rowNode);
    textNode->MarkModifyDone();
    // Create imageNode
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    imageNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetArrowWidth()), CalcLength(stepperTheme->GetArrowHeight())));
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageFit(ImageFit::FILL);
    ImageSourceInfo imageSourceInfo;
    imageSourceInfo.SetResourceId(InternalResource::ResourceId::STEPPER_NEXT_ARROW);
    auto imageColor = stepperTheme->GetArrowColor();
    imageColor = isDisabled ? imageColor.BlendOpacity(stepperTheme->GetDisabledAlpha())
                            : imageColor.BlendOpacity(stepperTheme->GetDefaultAlpha());
    imageSourceInfo.SetFillColor(imageColor);
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateImageSourceInfo(imageSourceInfo);
    SizeF sourceSize(static_cast<float>(stepperTheme->GetArrowWidth().ConvertToPx()),
        static_cast<float>(stepperTheme->GetArrowHeight().ConvertToPx()));
    imageNode->GetLayoutProperty<ImageLayoutProperty>()->UpdateSourceSize(sourceSize);
    imageNode->MountToParent(rowNode);
    imageNode->MarkModifyDone();
}

void StepperPattern::CreateArrowlessRightButtonNode(int32_t index, const std::string& defaultContent)
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
    // Create buttonNode
    auto buttonId = hostNode->GetRightButtonId();
    auto buttonPattern = AceType::MakeRefPtr<NG::ButtonPattern>();
    CHECK_NULL_VOID(buttonPattern);
    buttonPattern->setComponentButtonType(ComponentButtonType::STEPPER);
    buttonPattern->SetFocusBorderColor(stepperTheme->GetFocusColor());
    auto buttonNode = FrameNode::CreateFrameNode(V2::BUTTON_ETS_TAG, buttonId, buttonPattern);
    CHECK_NULL_VOID(buttonNode);
    buttonNode->GetEventHub<ButtonEventHub>()->SetStateEffect(true);
    Color buttonBackgroundColor =
        rightIsHover_ ? stepperTheme->GetMouseHoverColor() : stepperTheme->GetMouseHoverColor().ChangeOpacity(0);
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateType(ButtonType::NORMAL);
    buttonNode->GetRenderContext()->UpdateBackgroundColor(buttonBackgroundColor);
    buttonNode->GetLayoutProperty()->UpdateMeasureType(MeasureType::MATCH_CONTENT);
    auto buttonRadius = stepperTheme->GetRadius();
    buttonNode->GetLayoutProperty<ButtonLayoutProperty>()->UpdateBorderRadius(BorderRadiusProperty(buttonRadius));
    buttonNode->MountToParent(hostNode);
    buttonNode->MarkModifyDone();
    InitButtonOnHoverEvent(buttonNode, false);
    InitButtonTouchEvent(buttonNode);
    // Create textNode
    auto textNode = FrameNode::GetOrCreateFrameNode(V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<TextPattern>(); });
    textNode->GetRenderContext()->UpdateBackgroundColor(Color::TRANSPARENT);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateContent(rightLabel);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontSize(stepperTheme->GetTextStyle().GetFontSize());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateFontWeight(stepperTheme->GetTextStyle().GetFontWeight());
    auto textColor = stepperTheme->GetTextStyle().GetTextColor().BlendOpacity(stepperTheme->GetDefaultAlpha());
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextColor(textColor);
    textNode->GetLayoutProperty<TextLayoutProperty>()->UpdateTextOverflow(TextOverflow::ELLIPSIS);
    textNode->GetLayoutProperty()->UpdateAlignment(Alignment::CENTER);
    textNode->GetLayoutProperty()->UpdateMargin(
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
    auto buttonId = hostNode->GetRightButtonId();
    auto loadingProgressNode = FrameNode::GetOrCreateFrameNode(
        V2::LOADING_PROGRESS_ETS_TAG, buttonId, []() { return AceType::MakeRefPtr<LoadingProgressPattern>(); });
    loadingProgressNode->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(stepperTheme->GetProgressDiameter()), CalcLength(stepperTheme->GetProgressDiameter())));
    loadingProgressNode->GetPaintProperty<LoadingProgressPaintProperty>()->UpdateColor(
        stepperTheme->GetProgressColor());
    loadingProgressNode->GetRenderContext()->UpdateForegroundColor(stepperTheme->GetProgressColor());
    loadingProgressNode->MountToParent(hostNode);
    loadingProgressNode->MarkModifyDone();
}

void StepperPattern::UpdateRightButtonNode(int32_t index)
{
    auto hostNode = DynamicCast<StepperNode>(GetHost());
    CHECK_NULL_VOID(hostNode);
    hostNode->RemoveRightButtonNode();
    CreateRightButtonNode(index);
}

void StepperPattern::InitButtonOnHoverEvent(RefPtr<FrameNode> buttonNode, bool isLeft)
{
    CHECK_NULL_VOID(buttonNode);
    auto buttonInputHub = buttonNode->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(buttonInputHub);
    auto hoverCallback = [weak = WeakClaim(this), buttonNode, isLeft](bool isHovered) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ButtonOnHover(buttonNode, isHovered, isLeft);
    };
    buttonOnHoverListenr_ = MakeRefPtr<InputEvent>(std::move(hoverCallback));
    buttonInputHub->AddOnHoverEvent(buttonOnHoverListenr_);
}

void StepperPattern::ButtonOnHover(RefPtr<FrameNode> buttonNode, bool isHover, bool isLeft)
{
    if (isLeft) {
        if (leftIsHover_ == isHover) {
            return;
        }
        leftIsHover_ = isHover;
    } else {
        if (rightIsHover_ == isHover) {
            return;
        }
        rightIsHover_ = isHover;
    }
    if (isHover) {
        ButtonHoverInAnimation(buttonNode);
    } else {
        ButtonHoverOutAnimation(buttonNode);
    }
}

void StepperPattern::ButtonHoverInAnimation(RefPtr<FrameNode> buttonNode)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(BUTTON_ON_HOVER_BEZIER_CURVE_X0, BUTTON_ON_HOVER_BEZIER_CURVE_Y0,
        BUTTON_ON_HOVER_BEZIER_CURVE_X1, BUTTON_ON_HOVER_BEZIER_CURVE_Y1));
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    Color buttonBackgroundColor = stepperTheme->GetMouseHoverColor();
    AnimationUtils::Animate(option,
        [renderContext, buttonBackgroundColor]() { renderContext->UpdateBackgroundColor(buttonBackgroundColor); });
}
void StepperPattern::ButtonHoverOutAnimation(RefPtr<FrameNode> buttonNode)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(BUTTON_ON_HOVER_BEZIER_CURVE_X0, BUTTON_ON_HOVER_BEZIER_CURVE_Y0,
        BUTTON_ON_HOVER_BEZIER_CURVE_X1, BUTTON_ON_HOVER_BEZIER_CURVE_Y1));
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    Color buttonBackgroundColor = stepperTheme->GetMouseHoverColor().ChangeOpacity(0);
    AnimationUtils::Animate(option,
        [renderContext, buttonBackgroundColor]() { renderContext->UpdateBackgroundColor(buttonBackgroundColor); });
}

void StepperPattern::InitButtonTouchEvent(RefPtr<FrameNode> buttonNode)
{
    CHECK_NULL_VOID(buttonNode);
    auto buttonEventHub = buttonNode->GetEventHub<ButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->SetStateEffect(false);
    auto buttonGestureHub = buttonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(buttonGestureHub);
    auto touchCallback = [weak = WeakClaim(this), buttonNode](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ButtonOnTouch(buttonNode, info.GetTouches().front().GetTouchType());
    };
    buttonTouchListenr_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    buttonGestureHub->AddTouchEvent(buttonTouchListenr_);
}

void StepperPattern::ButtonOnTouch(RefPtr<FrameNode> buttonNode, TouchType touchType)
{
    if (touchType == TouchType::DOWN) {
        ButtonTouchDownAnimation(buttonNode);
    }
    if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        ButtonTouchUpAnimation(buttonNode);
    }
}

void StepperPattern::ButtonTouchDownAnimation(RefPtr<FrameNode> buttonNode)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(PRESS_ANIMATION_DURATION);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(BUTTON_ON_PRESS_BEZIER_CURVE_X0, BUTTON_ON_PRESS_BEZIER_CURVE_Y0,
        BUTTON_ON_PRESS_BEZIER_CURVE_X1, BUTTON_ON_PRESS_BEZIER_CURVE_Y1));
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    Color buttonBackgroundColor = stepperTheme->GetButtonPressedColor();
    AnimationUtils::Animate(option,
        [renderContext, buttonBackgroundColor]() { renderContext->UpdateBackgroundColor(buttonBackgroundColor); });
}

void StepperPattern::ButtonTouchUpAnimation(RefPtr<FrameNode> buttonNode)
{
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    AnimationOption option;
    option.SetDuration(PRESS_ANIMATION_DURATION);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(BUTTON_ON_PRESS_BEZIER_CURVE_X0, BUTTON_ON_PRESS_BEZIER_CURVE_Y0,
        BUTTON_ON_PRESS_BEZIER_CURVE_X1, BUTTON_ON_PRESS_BEZIER_CURVE_Y1));
    auto stepperTheme = GetTheme();
    CHECK_NULL_VOID(stepperTheme);
    Color buttonBackgroundColor =
        rightIsHover_ ? stepperTheme->GetMouseHoverColor() : stepperTheme->GetMouseHoverColor().ChangeOpacity(0);
    AnimationUtils::Animate(option,
        [renderContext, buttonBackgroundColor]() { renderContext->UpdateBackgroundColor(buttonBackgroundColor); });
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
                CHECK_NULL_VOID_NOLOG(stepperPattern);
                stepperPattern->HandlingLeftButtonClickEvent();
            };
            leftGestureHub->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(leftClickEvent)));
        }
    }

    auto rightButtonNode =
        DynamicCast<FrameNode>(hostNode->GetChildAtIndex(hostNode->GetChildIndexById(hostNode->GetRightButtonId())));
    CHECK_NULL_VOID(rightButtonNode);
    auto rightGestureHub = rightButtonNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(rightGestureHub);
    if (rightGestureHub->IsClickEventsEmpty()) {
        auto rightClickEvent = [weak = WeakClaim(this)](const GestureEvent& info) {
            auto stepperPattern = weak.Upgrade();
            CHECK_NULL_VOID_NOLOG(stepperPattern);
            stepperPattern->HandlingRightButtonClickEvent();
        };
        rightGestureHub->AddClickEvent(MakeRefPtr<ClickEvent>(std::move(rightClickEvent)));
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
        stepperHub->FireSkipEvent();
    } else if (labelStatus == "normal") {
        if (index_ == maxIndex_) {
            stepperHub->FireFinishEvent();
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

void StepperPattern::ButtonSkipColorConfigurationUpdate(RefPtr<FrameNode> buttonNode)
{
    auto pattern = buttonNode->GetPattern<ButtonPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSkipColorConfigurationUpdate();
}
} // namespace OHOS::Ace::NG
