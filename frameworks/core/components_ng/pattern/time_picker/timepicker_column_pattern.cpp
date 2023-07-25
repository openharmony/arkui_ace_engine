/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"

#include <cstdint>
#include <iterator>
#include <list>

#include "base/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO timepicker style modification
constexpr Dimension PADDING_WEIGHT = 10.0_vp;
const Dimension FONT_SIZE = Dimension(2.0);
const int32_t CHILD_SIZE = 3;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_HOUR24_HEIGHT_NUMBER = 9.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
const int32_t ANIMATION_ZERO_TO_OUTER = 200; // 200ms for animation that from zero to outer.
const int32_t ANIMATION_OUTER_TO_ZERO = 150; // 150ms for animation that from outer to zero.
const Dimension FOCUS_SIZE = Dimension(1.0);
const int32_t MIDDLE_CHILD_INDEX = 2;
const float MOVE_DISTANCE = 5.0f;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr int32_t PRESS_ANIMATION_DURATION = 100;
} // namespace

void TimePickerColumnPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    tossAnimationController_->SetPipelineContext(context);
    tossAnimationController_->SetColumn(AceType::WeakClaim(this));
    jumpInterval_ = pickerTheme->GetJumpInterval().ConvertToPx();
    CreateAnimation();
    InitPanEvent(gestureHub);
}

void TimePickerColumnPattern::OnModifyDone()
{
    auto host = GetHost();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    pressColor_ = theme->GetPressColor();
    hoverColor_ = theme->GetHoverColor();
    InitOnKeyEvent(focusHub);
    InitMouseAndPressEvent();
    SetAccessibilityAction();
}

void TimePickerColumnPattern::InitMouseAndPressEvent()
{
    if (mouseEvent_ || touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<FrameNode> middleChild = nullptr;
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    middleChild = DynamicCast<FrameNode>(host->GetChildAtIndex(childSize / MIDDLE_CHILD_INDEX));
    CHECK_NULL_VOID(middleChild);
    auto eventHub = middleChild->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
    auto gesture = middleChild->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->OnTouchDown();
            pattern->SetLocalDownDistance(info.GetTouches().front().GetLocalLocation().GetDistance());
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            pattern->OnTouchUp();
            pattern->SetLocalDownDistance(0.0f);
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::MOVE) {
            if (std::abs(info.GetTouches().front().GetLocalLocation().GetDistance() - pattern->GetLocalDownDistance()) >
                MOVE_DISTANCE) {
                pattern->OnTouchUp();
            }
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    gesture->AddTouchEvent(touchListener_);
}

void TimePickerColumnPattern::HandleMouseEvent(bool isHover)
{
    if (isHover) {
        hoverd_ = true;
        PlayHoverAnimation(hoverColor_);
    } else {
        hoverd_ = false;
        PlayHoverAnimation(Color::TRANSPARENT);
    }
}

void TimePickerColumnPattern::OnTouchDown()
{
    PlayPressAnimation(pressColor_);
}

void TimePickerColumnPattern::OnTouchUp()
{
    if (hoverd_) {
        PlayPressAnimation(hoverColor_);
    } else {
        PlayPressAnimation(Color::TRANSPARENT);
    }
}

void TimePickerColumnPattern::SetButtonBackgroundColor(const Color& pressColor)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto stack = host->GetParent();
    CHECK_NULL_VOID(stack);
    auto buttonNode = DynamicCast<FrameNode>(stack->GetFirstChild());
    auto renderContext = buttonNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(pressColor);
    buttonNode->MarkModifyDone();
    buttonNode->MarkDirtyNode();
}

void TimePickerColumnPattern::PlayPressAnimation(const Color& pressColor)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(PRESS_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), pressColor]() {
        auto picker = weak.Upgrade();
        if (picker) {
            picker->SetButtonBackgroundColor(pressColor);
        }
    });
}

void TimePickerColumnPattern::PlayHoverAnimation(const Color& color)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), color]() {
        auto picker = weak.Upgrade();
        if (picker) {
            picker->SetButtonBackgroundColor(color);
        }
    });
}

bool TimePickerColumnPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    CHECK_NULL_RETURN_NOLOG(config.frameSizeChange, false);
    CHECK_NULL_RETURN(dirty, false);
    return true;
}

void TimePickerColumnPattern::FlushCurrentOptions(bool isDown, bool isUpateTextContentOnly)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto stackNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto dataPickerLayoutProperty = host->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdatePadding(
        PaddingProperty { CalcLength(static_cast<float>(PADDING_WEIGHT.ConvertToPx()), DimensionUnit::PX) });
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto showOptionCount = GetShowCount();
    uint32_t totalOptionCount = timePickerRowPattern->GetOptionCount(host);
    auto timePickerLayoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(timePickerLayoutProperty);
    uint32_t currentIndex = host->GetPattern<TimePickerColumnPattern>()->GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showOptionCount) {
        return;
    }
    if (!isUpateTextContentOnly) {
        animationProperties_.clear();
    }
    for (uint32_t index = 0; index < showOptionCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (!isUpateTextContentOnly) {
            ChangeTextStyle(index, showOptionCount, textLayoutProperty, timePickerLayoutProperty);
            ChangeAmPmTextStyle(index, showOptionCount, textLayoutProperty, timePickerLayoutProperty);
            AddAnimationTextProperties(index, textLayoutProperty);
        }
        iter++;
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(selectedIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent("");
        } else {
            auto optionValue = timePickerRowPattern->GetOptionsValue(host, optionIndex);
            textLayoutProperty->UpdateContent(optionValue);
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
    }
    if (isUpateTextContentOnly) {
        FlushAnimationTextProperties(isDown);
    }
}

void TimePickerColumnPattern::UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(timePickerLayoutProperty->GetDisappearColor().value_or(
        pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (timePickerLayoutProperty->HasDisappearFontSize()) {
        textLayoutProperty->UpdateFontSize(timePickerLayoutProperty->GetDisappearFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(normalOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(false, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(timePickerLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(timePickerLayoutProperty->GetDisappearFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(timePickerLayoutProperty->GetDisappearFontStyle().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TimePickerColumnPattern::UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    textLayoutProperty->UpdateTextColor(timePickerLayoutProperty->GetColor().value_or(
        pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (timePickerLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(timePickerLayoutProperty->GetFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(focusOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize() - FOCUS_SIZE);
    }
    textLayoutProperty->UpdateFontWeight(timePickerLayoutProperty->GetWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(timePickerLayoutProperty->GetFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(timePickerLayoutProperty->GetFontStyle().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TimePickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(timePickerLayoutProperty->GetSelectedColor().value_or(
        pickerTheme->GetOptionStyle(true, false).GetTextColor()));
    if (timePickerLayoutProperty->HasSelectedFontSize()) {
        textLayoutProperty->UpdateFontSize(timePickerLayoutProperty->GetSelectedFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(selectedOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(timePickerLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(timePickerLayoutProperty->GetSelectedFontFamily().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(timePickerLayoutProperty->GetSelectedFontStyle().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontStyle()));
}

void TimePickerColumnPattern::ChangeAmPmTextStyle(
    uint32_t index, uint32_t showOptionCount, const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    if (showOptionCount != CHILD_SIZE) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    if (index == selectedIndex) {
        UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    }
    if ((index == 0) || (index == showOptionCount - 1)) {
        UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        if (index == 0) {
            textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
        } else {
            textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
        }
    }
    textLayoutProperty->UpdateMaxLines(1);
}

void TimePickerColumnPattern::ChangeTextStyle(
    uint32_t index, uint32_t showOptionCount, const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    if (showOptionCount == CHILD_SIZE) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    if (index != selectedIndex) {
        if ((index == 0) || (index == showOptionCount - 1)) {
            UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        } else {
            UpdateCandidateTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        }
        if (index < selectedIndex) {
            textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
        } else {
            textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
        }
    }
    if (index == selectedIndex) {
        UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    }
    textLayoutProperty->UpdateMaxLines(1);
}

void TimePickerColumnPattern::AddAnimationTextProperties(uint32_t currentIndex,
    const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    TextProperties properties;
    if (textLayoutProperty->HasFontSize()) {
        properties.fontSize = Dimension(textLayoutProperty->GetFontSize().value().ConvertToPx());
    }
    if (textLayoutProperty->HasTextColor()) {
        properties.currentColor = textLayoutProperty->GetTextColor().value();
    }
    if (currentIndex > 0) {
        properties.upFontSize = animationProperties_[currentIndex - 1].fontSize;
        animationProperties_[currentIndex - 1].downFontSize = properties.fontSize;

        properties.upColor = animationProperties_[currentIndex - 1].currentColor;
        animationProperties_[currentIndex - 1].downColor = properties.currentColor;
    }
    animationProperties_.emplace_back(properties);
}

void TimePickerColumnPattern::FlushAnimationTextProperties(bool isDown)
{
    if (!animationProperties_.size()) {
        return;
    }
    if (isDown) {
        for (size_t i = 0; i < animationProperties_.size(); i++) {
            if (i > 0) {
                animationProperties_[i - 1].upFontSize = animationProperties_[i].upFontSize;
                animationProperties_[i - 1].fontSize = animationProperties_[i].fontSize;
                animationProperties_[i - 1].downFontSize = animationProperties_[i].downFontSize;

                animationProperties_[i - 1].upColor = animationProperties_[i].upColor;
                animationProperties_[i - 1].currentColor = animationProperties_[i].currentColor;
                animationProperties_[i - 1].downColor = animationProperties_[i].downColor;
            }
            if (i == (animationProperties_.size() - 1)) {
                animationProperties_[i].upFontSize = animationProperties_[i].fontSize;
                animationProperties_[i].fontSize = animationProperties_[i].fontSize * 0.5;
                animationProperties_[i].downFontSize = Dimension();

                animationProperties_[i].upColor = animationProperties_[i].currentColor;
                auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
                animationProperties_[i].currentColor =
                    colorEvaluator->Evaluate(Color(), animationProperties_[i].currentColor, 0.5);
                animationProperties_[i].downColor = Color();
            }
        }
    } else {
        for (size_t i = animationProperties_.size() - 1;; i--) {
            if (i == 0) {
                animationProperties_[i].upFontSize = Dimension();
                animationProperties_[i].downFontSize = animationProperties_[i].fontSize;
                animationProperties_[i].fontSize = animationProperties_[i].fontSize * 0.5;

                animationProperties_[i].upColor = Color();
                animationProperties_[i].downColor = animationProperties_[i].currentColor;
                auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
                animationProperties_[i].currentColor =
                    colorEvaluator->Evaluate(Color(), animationProperties_[i].currentColor, 0.5);
                break;
            } else {
                animationProperties_[i].upFontSize = animationProperties_[i - 1].upFontSize;
                animationProperties_[i].fontSize = animationProperties_[i - 1].fontSize;
                animationProperties_[i].downFontSize = animationProperties_[i - 1].downFontSize;

                animationProperties_[i].upColor = animationProperties_[i - 1].upColor;
                animationProperties_[i].currentColor = animationProperties_[i - 1].currentColor;
                animationProperties_[i].downColor = animationProperties_[i - 1].downColor;
            }
        }
    }
}

void TimePickerColumnPattern::TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    uint32_t index, uint32_t showCount, bool isDown, double scale)
{
    if (index >= animationProperties_.size()) {
        LOGE("Animation Properties vactor is break.");
        return;
    }
    if ((!index && isDown) || ((index == (showCount - 1)) && !isDown)) {
        return;
    }
    Dimension startFontSize = animationProperties_[index].fontSize;
    Color startColor = animationProperties_[index].currentColor;
    Dimension endFontSize;
    Color endColor;
    if (!isDown) {
        endFontSize = animationProperties_[index].downFontSize;
        endColor = animationProperties_[index].downColor;
    } else {
        endFontSize = animationProperties_[index].upFontSize;
        endColor = animationProperties_[index].upColor;
    }
    Dimension updateSize = LinearFontSize(startFontSize, endFontSize, scale);
    textLayoutProperty->UpdateFontSize(updateSize);
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    Color updateColor = colorEvaluator->Evaluate(startColor, endColor, scale);
    textLayoutProperty->UpdateTextColor(updateColor);
}

void TimePickerColumnPattern::UpdateTextPropertiesLinear(bool isDown, double scale)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    uint32_t showCount = GetShowCount();
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        RefPtr<TextLayoutProperty> textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        TextPropertiesLinearAnimation(textLayoutProperty, index, showCount, isDown, scale);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
}

Dimension TimePickerColumnPattern::LinearFontSize(const Dimension& startFontSize,
    const Dimension& endFontSize, double percent)
{
    return startFontSize + (endFontSize - startFontSize) * percent;
}

void TimePickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID_NOLOG(!panEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        LOGI("Pan event start");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragStart(event);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragMove(event);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            return;
        }
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGI("Pan event cancel");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(pattern);
        pattern->HandleDragEnd();
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void TimePickerColumnPattern::HandleDragStart(const GestureEvent& event)
{
    CHECK_NULL_VOID_NOLOG(GetHost());
    CHECK_NULL_VOID_NOLOG(GetToss());
    auto toss = GetToss();
    yOffset_ = event.GetGlobalPoint().GetY();
    toss->SetStart(yOffset_);
    yLast_ = yOffset_;
    pressed_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_START);
}

void TimePickerColumnPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetInputEventType() == InputEventType::AXIS) {
        InnerHandleScroll(LessNotEqual(event.GetDelta().GetY(), 0.0));
        return;
    }
    CHECK_NULL_VOID_NOLOG(pressed_);
    CHECK_NULL_VOID_NOLOG(GetHost());
    CHECK_NULL_VOID_NOLOG(GetToss());
    auto toss = GetToss();
    double offsetY = event.GetGlobalPoint().GetY();
    if (NearEqual(offsetY, yLast_, 1.0)) { // if changing less than 1.0, no need to handle
        return;
    }
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
}

void TimePickerColumnPattern::HandleDragEnd()
{
    pressed_ = false;
    CHECK_NULL_VOID_NOLOG(GetHost());
    CHECK_NULL_VOID_NOLOG(GetToss());
    auto toss = GetToss();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (!NotLoopOptions() && toss->Play()) {
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
        return;
    }
    yOffset_ = 0.0;
    yLast_ = 0.0;
    if (!animationCreated_) {
        ScrollOption(0.0);
        return;
    }
    auto curve = CreateAnimation(scrollDelta_, 0.0);
    fromController_->ClearInterpolators();
    fromController_->AddInterpolator(curve);
    fromController_->Play();
    frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
}
void TimePickerColumnPattern::CreateAnimation()
{
    CHECK_NULL_VOID_NOLOG(!animationCreated_);
    toController_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
    toController_->SetDuration(ANIMATION_ZERO_TO_OUTER);
    auto weak = AceType::WeakClaim(this);
    toController_->AddStopListener([weak]() {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->HandleCurveStopped();
    });
    fromBottomCurve_ = CreateAnimation(jumpInterval_, 0.0);
    fromTopCurve_ = CreateAnimation(0.0 - jumpInterval_, 0.0);
    fromController_ = CREATE_ANIMATOR(PipelineContext::GetCurrentContext());
    fromController_->SetDuration(ANIMATION_OUTER_TO_ZERO);
    animationCreated_ = true;
}

RefPtr<CurveAnimation<double>> TimePickerColumnPattern::CreateAnimation(double from, double to)
{
    auto weak = AceType::WeakClaim(this);
    auto curve = AceType::MakeRefPtr<CurveAnimation<double>>(from, to, Curves::FRICTION);
    curve->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->ScrollOption(value);
    }));
    return curve;
}

void TimePickerColumnPattern::HandleCurveStopped()
{
    CHECK_NULL_VOID_NOLOG(animationCreated_);
    if (NearZero(scrollDelta_)) {
        return;
    }
    ScrollOption(0.0 - scrollDelta_);
    InnerHandleScroll(GreatNotEqual(scrollDelta_, 0.0));
    fromController_->ClearInterpolators();
    if (LessNotEqual(scrollDelta_, 0.0)) {
        fromController_->AddInterpolator(fromTopCurve_);
    } else {
        fromController_->AddInterpolator(fromBottomCurve_);
    }
    fromController_->Play();
}

void TimePickerColumnPattern::ScrollOption(double delta, bool isJump)
{
    UpdateScrollDelta(delta);
    double oldDelta = scrollDelta_;
    scrollDelta_ = delta;

    if ((isJump_ && LessOrEqual(delta * oldDelta, 0.0)) || NearZero(delta) || (isJump_ && isJump)) {
        isJump_ = false;
        FlushCurrentOptions();
        return;
    }
    if (isJump) {
        isJump_ = true;
    }
    if (NearZero(jumpInterval_)) {
        return;
    }
    double scale = 0.0;
    if (!isJump_) {
        scale = fabs(delta) / (jumpInterval_ * 2);
        UpdateTextPropertiesLinear(LessNotEqual(delta, 0.0), scale);
    } else {
        scale = ((2 * jumpInterval_) - fabs(delta))  / (jumpInterval_ * 2);
        UpdateTextPropertiesLinear(!LessNotEqual(delta, 0.0), scale);
    }
}

void TimePickerColumnPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TimePickerColumnPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void TimePickerColumnPattern::TossStoped()
{
    yOffset_ = 0.0;
    yLast_ = 0.0;
    ScrollOption(0.0);
}

void TimePickerColumnPattern::SetDividerHeight(uint32_t showOptionCount)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = PipelineContext::GetCurrentContext();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto childSize = host->GetChildren().size();
    if (childSize != CHILD_SIZE) {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() * TEXT_HEIGHT_NUMBER);
    } else {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() - TEXT_HOUR24_HEIGHT_NUMBER);
    }
    dividerHeight_ = static_cast<float>(
        gradientHeight_ + pickerTheme->GetDividerSpacing().Value() + pickerTheme->GetGradientHeight().Value());
    dividerSpacingWidth_ = static_cast<float>(pickerTheme->GetDividerSpacing().Value() * TEXT_WEIGHT_NUMBER);
}

bool TimePickerColumnPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowCount();
    auto options = GetOptions();
    uint32_t totalOptionCount = options[host];
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool TimePickerColumnPattern::InnerHandleScroll(bool isDown, bool isUpatePropertiesOnly)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    auto totalOptionCount = options[host];

    CHECK_NULL_RETURN(host, false);
    CHECK_NULL_RETURN(totalOptionCount, false);

    uint32_t currentIndex = GetCurrentIndex();
    if (isDown) {
        currentIndex = (totalOptionCount + currentIndex + 1) % totalOptionCount; // index add one
    } else {
        currentIndex = (totalOptionCount + currentIndex - 1) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    FlushCurrentOptions(isDown, isUpatePropertiesOnly);
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);
    return true;
}

void TimePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    yLast_ = offsetY;
    double dragDelta = yLast_ - yOffset_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }

    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    jumpInterval_ = pickerTheme->GetJumpInterval().ConvertToPx();
    // the abs of drag delta is less than jump interval.
    if (LessNotEqual(0.0 - jumpInterval_, dragDelta) && LessNotEqual(dragDelta, jumpInterval_)) {
        ScrollOption(dragDelta);
        return;
    }
    InnerHandleScroll(LessNotEqual(dragDelta, 0.0), true);
    double jumpDelta = (LessNotEqual(dragDelta, 0.0) ? jumpInterval_ : 0.0 - jumpInterval_);
    ScrollOption(jumpDelta, true);
    yOffset_ = offsetY - jumpDelta;
}

bool TimePickerColumnPattern::CanMove(bool isDown) const
{
    CHECK_NULL_RETURN_NOLOG(NotLoopOptions(), true);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    int totalOptionCount = static_cast<int>(options[host]);
    auto timePickerColumnPattern = host->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(timePickerColumnPattern, false);
    int currentIndex = static_cast<int>(timePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

void TimePickerColumnPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool TimePickerColumnPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool TimePickerColumnPattern::HandleDirectionKey(KeyCode code)
{
    if (code == KeyCode::KEY_DPAD_UP) {
        // Need to update: current selection
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        // Need to update: current selection
        return true;
    }
    return false;
}

void TimePickerColumnPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->CanMove(true)) {
            return;
        }
        CHECK_NULL_VOID(pattern->animationCreated_);
        pattern->InnerHandleScroll(true);
        CHECK_NULL_VOID(pattern->fromController_);
        pattern->fromController_->ClearInterpolators();
        pattern->fromController_->AddInterpolator(pattern->fromTopCurve_);
        pattern->fromController_->Play();
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->CanMove(false)) {
            return;
        }
        CHECK_NULL_VOID(pattern->animationCreated_);
        pattern->InnerHandleScroll(false);
        CHECK_NULL_VOID(pattern->fromController_);
        pattern->fromController_->ClearInterpolators();
        pattern->fromController_->AddInterpolator(pattern->fromBottomCurve_);
        pattern->fromController_->Play();
        auto frameNode = pattern->GetHost();
        CHECK_NULL_VOID(frameNode);
        frameNode->OnAccessibilityEvent(AccessibilityEventType::SCROLL_END);
    });
}
} // namespace OHOS::Ace::NG
