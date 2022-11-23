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

#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"

#include <cstdint>
#include <iterator>
#include <list>
#include <stdint.h>

#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {

// TODO datepicker style modification
constexpr float PADDING_WEIGHT = 10.0f;
const Dimension FONT_SIZE = Dimension(2.0);
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const int32_t DIVIDER_SIZE = 2;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
const int32_t ANIMATION_ZERO_TO_OUTER = 200;
const int32_t ANIMATION_OUTER_TO_ZERO = 150;

} // namespace

void DatePickerColumnPattern::OnAttachToFrameNode()
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

bool DatePickerColumnPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    return true;
}

void DatePickerColumnPattern::FlushCurrentOptions()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto parentNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(parentNode);

    auto dataPickerLayoutProperty = host->GetLayoutProperty<DataPickerLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdatePadding(PaddingProperty { CalcLength(PADDING_WEIGHT, DimensionUnit::PX) });
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

    auto datePickerPattern = parentNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto showOptionCount = datePickerPattern->GetShowCount();
    uint32_t totalOptionCount = datePickerPattern->GetOptionCount(host);
    uint32_t currentIndex = host->GetPattern<DatePickerColumnPattern>()->GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.

    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showOptionCount) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto middleIndex = showOptionCount / 2;
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    SetCurrentIndex(currentIndex);
    SetDividerHeight(showOptionCount);
    for (uint32_t index = 0; index < showOptionCount; index++) {
        currentChildIndex_ = index;
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        int diffIndex = static_cast<int>(index) - static_cast<int>(selectedIndex);
        int virtualIndex = static_cast<int>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int>(totalOptionCount);
        auto optionValue = datePickerPattern->GetAllOptions(host)[optionIndex];

        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (index < middleIndex) {
            if (index == 0) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetGradientHeight())));
            textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
        }
        if (index == middleIndex) {
            textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateFontSize(selectedOptionSize);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetDividerSpacing())));
            textLayoutProperty->UpdateAlignment(Alignment::CENTER);
        }
        if (index > middleIndex) {
            if (index == showOptionCount - 1) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateUserDefinedIdealSize(
                CalcSize(CalcLength(pickerTheme->GetDividerSpacing() * DIVIDER_SIZE),
                    CalcLength(pickerTheme->GetGradientHeight())));
            textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
        }
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent("");
            continue;
        }
        textLayoutProperty->UpdateContent(optionValue);
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        textNode->MarkModifyDone();
        iter++;
    }
}

void DatePickerColumnPattern::SetDividerHeight(uint32_t showOptionCount)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    if (showOptionCount != OPTION_COUNT_PHONE_LANDSCAPE) {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() * TEXT_HEIGHT_NUMBER);
    } else {
        gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value());
    }
    dividerHeight_ = static_cast<float>(
        gradientHeight_ + pickerTheme->GetDividerSpacing().Value() + pickerTheme->GetGradientHeight().Value());
    dividerSpacingWidth_ = static_cast<float>(pickerTheme->GetDividerSpacing().Value() * TEXT_WEIGHT_NUMBER);
}

bool DatePickerColumnPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowCount();
    auto options = GetOptions();
    uint32_t totalOptionCount = options[host].size();
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool DatePickerColumnPattern::InnerHandleScroll(bool isDown)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    auto totalOptionCount = options[host].size();

    if (!host || !totalOptionCount) {
        LOGE("options is empty.");
        return false;
    }

    uint32_t currentIndex = GetCurrentIndex();
    if (isDown) {
        currentIndex = (totalOptionCount + currentIndex + 1) % totalOptionCount; // index add one
    } else {
        currentIndex = (totalOptionCount + currentIndex - 1) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    FlushCurrentOptions();
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);
    return true;
}

void DatePickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        LOGI("Pan event start");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragStart(event);
        }
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragMove(event);
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        LOGI("Pan event end mainVelocity: %{public}lf", info.GetMainVelocity());
        auto pattern = weak.Upgrade();
        if (pattern) {
            if (info.GetInputEventType() == InputEventType::AXIS) {
                return;
            }
            pattern->HandleDragEnd();
        }
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        LOGI("Pan event cancel");
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleDragEnd();
        }
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

void DatePickerColumnPattern::HandleDragStart(const GestureEvent& event)
{
    if (!GetHost() || !GetToss()) {
        return;
    }
    auto toss = GetToss();
    yOffset_ = event.GetGlobalPoint().GetY();
    toss->SetStart(yOffset_);
    yLast_ = yOffset_;
    pressed_ = true;
}

void DatePickerColumnPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetInputEventType() == InputEventType::AXIS) {
        InnerHandleScroll(LessNotEqual(event.GetDelta().GetY(), 0.0));
        return;
    }
    if (!pressed_) {
        LOGE("not pressed.");
        return;
    }
    if (!GetHost() || !GetToss()) {
        return;
    }
    auto toss = GetToss();
    double offsetY = event.GetGlobalPoint().GetY();
    if (NearEqual(offsetY, yLast_, 1.0)) { // if changing less than 1.0, no need to handle
        return;
    }
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
}

void DatePickerColumnPattern::HandleDragEnd()
{
    pressed_ = false;
    if (!GetHost() || !GetToss()) {
        return;
    }
    auto toss = GetToss();
    if (!NotLoopOptions() && toss->Play()) {
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
}
void DatePickerColumnPattern::CreateAnimation()
{
    if (animationCreated_) {
        return;
    }
    toController_ = AceType::MakeRefPtr<Animator>(PipelineContext::GetCurrentContext());
    toController_->SetDuration(ANIMATION_ZERO_TO_OUTER); // 200ms for animation that from zero to outer.
    auto weak = AceType::WeakClaim(this);
    toController_->AddStopListener([weak]() {
        auto column = weak.Upgrade();
        if (column) {
            column->HandleCurveStopped();
        } else {
            LOGE("render picker column is null.");
        }
    });
    fromBottomCurve_ = CreateAnimation(jumpInterval_, 0.0);
    fromTopCurve_ = CreateAnimation(0.0 - jumpInterval_, 0.0);
    fromController_ = AceType::MakeRefPtr<Animator>(PipelineContext::GetCurrentContext());
    fromController_->SetDuration(ANIMATION_OUTER_TO_ZERO); // 150ms for animation that from outer to zero.
    animationCreated_ = true;
}

RefPtr<CurveAnimation<double>> DatePickerColumnPattern::CreateAnimation(double from, double to)
{
    auto weak = AceType::WeakClaim(this);
    auto curve = AceType::MakeRefPtr<CurveAnimation<double>>(from, to, Curves::FRICTION);
    curve->AddListener(Animation<double>::ValueCallback([weak](double value) {
        auto column = weak.Upgrade();
        if (column) {
            column->ScrollOption(value);
        } else {
            LOGE("datepicker column is null.");
        }
    }));
    return curve;
}

void DatePickerColumnPattern::HandleCurveStopped()
{
    if (!animationCreated_) {
        LOGE("animation not created.");
        return;
    }
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

void DatePickerColumnPattern::ScrollOption(double delta)
{
    UpdateScrollDelta(delta);
    scrollDelta_ = delta;
}

void DatePickerColumnPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void DatePickerColumnPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void DatePickerColumnPattern::TossStoped()
{
    yOffset_ = 0.0;
    yLast_ = 0.0;
    ScrollOption(0.0);
}

void DatePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    yLast_ = offsetY;
    double dragDelta = yLast_ - yOffset_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    // the abs of drag delta is less than jump interval.
    if (LessNotEqual(0.0 - jumpInterval_, dragDelta) && LessNotEqual(dragDelta, jumpInterval_)) {
        ScrollOption(dragDelta);
        return;
    }
    InnerHandleScroll(LessNotEqual(dragDelta, 0.0));
    double jumpDelta = (LessNotEqual(dragDelta, 0.0) ? jumpInterval_ : 0.0 - jumpInterval_);
    ScrollOption(jumpDelta);
    yOffset_ = offsetY - jumpDelta;
}

bool DatePickerColumnPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    int totalOptionCount = static_cast<int>(options[host].size());

    auto datePickerColumnPattern = host->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(datePickerColumnPattern, false);
    int currentIndex = static_cast<int>(datePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}
} // namespace OHOS::Ace::NG