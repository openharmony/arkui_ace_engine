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

#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"

#include <cstdint>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
// TODO datepicker style modification
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const Dimension FONT_SIZE = Dimension(2.0);
const int32_t ANIMATION_ZERO_TO_OUTER = 200; // 200ms for animation that from zero to outer.
const int32_t ANIMATION_OUTER_TO_ZERO = 150; // 150ms for animation that from outer to zero.
} // namespace

void TextPickerPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);
    textPickerLayoutProperty->UpdateMainAxisAlign(FlexAlign::CENTER);
    textPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

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
    host->GetRenderContext()->SetClipToFrame(true);
}

bool TextPickerPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    if (!config.frameSizeChange) {
        return false;
    }
    CHECK_NULL_RETURN(dirty, false);
    return true;
}

void TextPickerPattern::OnModifyDone()
{
    OnColumnsBuilding();
    FlushCurrentOptions();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID_NOLOG(focusHub);
    InitOnKeyEvent(focusHub);
}

void TextPickerPattern::OnColumnsBuilding()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto frameNode = DynamicCast<FrameNode>(host);
    auto children = frameNode->GetChildren();
    auto textPickerPattern = frameNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    textPickerPattern->ClearOption();
    for (const auto& item : range_) {
        textPickerPattern->AppendOption(item);
    }
    selectedIndex_ = range_.empty() ? 0 : GetSelected() % range_.size();
    SetCurrentIndex(selectedIndex_);
}

uint32_t TextPickerPattern::GetShowOptionCount() const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, 0);
    auto showCount = pickerTheme->GetShowOptionCount();
    if (SystemProperties::GetDeviceType() == DeviceType::PHONE &&
        SystemProperties::GetDeviceOrientation() == DeviceOrientation::LANDSCAPE) {
        showCount = OPTION_COUNT_PHONE_LANDSCAPE;
    }
    return showCount;
}

void TextPickerPattern::FlushCurrentOptions()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    uint32_t showCount = GetShowOptionCount();
    auto textPickerPattern = host->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);

    uint32_t totalOptionCount = GetOptionCount();
    uint32_t currentIndex = GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showCount / 2; // the center option is selected.

    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto middleIndex = showCount / 2;
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    for (uint32_t index = 0; index < showCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;
        auto optionValue = textPickerPattern->GetOption(optionIndex);

        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);

        if (index < middleIndex) {
            if (index == 0) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
            textLayoutProperty->UpdateMaxLines(1);
        }
        if (index == middleIndex) {
            textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, false).GetTextColor());
            textLayoutProperty->UpdateMaxLines(1);
            textLayoutProperty->UpdateAlignment(Alignment::CENTER);
            textLayoutProperty->UpdateFontSize(selectedOptionSize);
        }
        if (index > middleIndex) {
            if (index == showCount - 1) {
                textLayoutProperty->UpdateFontSize(normalOptionSize);
            } else {
                textLayoutProperty->UpdateFontSize(focusOptionSize);
            }
            textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
            textLayoutProperty->UpdateMaxLines(1);
        }
        
        iter++;
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(selectedIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent("");
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            textNode->MarkModifyDone();
            continue;
        }
        textLayoutProperty->UpdateContent(optionValue);
        textNode->GetRenderContext()->SetClipToFrame(true);
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        textNode->MarkModifyDone();
    }
    selectedIndex_ = currentIndex;
    if (isIndexChanged_) {
        auto textPickerEventHub = GetEventHub<TextPickerEventHub>();
        CHECK_NULL_VOID(textPickerEventHub);
        auto currentValue = textPickerPattern->GetOption(currentIndex);
        textPickerEventHub->FireChangeEvent(currentValue, currentIndex);
        textPickerEventHub->FireDialogChangeEvent(GetSelectedObject(true, 1));
    }
}

void TextPickerPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (panEvent_) {
        return;
    }
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

void TextPickerPattern::HandleDragStart(const GestureEvent& event)
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

void TextPickerPattern::HandleDragMove(const GestureEvent& event)
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

void TextPickerPattern::HandleDragEnd()
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
void TextPickerPattern::CreateAnimation()
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
            LOGE("timepicker column is null.");
        }
    });
    fromBottomCurve_ = CreateAnimation(jumpInterval_, 0.0);
    fromTopCurve_ = CreateAnimation(0.0 - jumpInterval_, 0.0);
    fromController_ = AceType::MakeRefPtr<Animator>(PipelineContext::GetCurrentContext());
    fromController_->SetDuration(ANIMATION_OUTER_TO_ZERO);
    animationCreated_ = true;
}

RefPtr<CurveAnimation<double>> TextPickerPattern::CreateAnimation(double from, double to)
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

void TextPickerPattern::HandleCurveStopped()
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

void TextPickerPattern::ScrollOption(double delta)
{
    UpdateScrollDelta(delta);
    scrollDelta_ = delta;
}

void TextPickerPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextPickerPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void TextPickerPattern::TossStoped()
{
    yOffset_ = 0.0;
    yLast_ = 0.0;
    ScrollOption(0.0);
}

double TextPickerPattern::CalculateHeight()
{
    double height = 0.0;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, height);
    auto textPickerPattern = host->GetPattern<TextPickerPattern>();
    CHECK_NULL_RETURN(textPickerPattern, height);
    auto textPickerLayoutProperty = host->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_RETURN(textPickerLayoutProperty, height);
    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, height);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, height);
    if (textPickerLayoutProperty->HasDefaultPickerItemHeight()) {
        auto defaultPickerItemHeightValue = textPickerLayoutProperty->GetDefaultPickerItemHeightValue();
        if (context->NormalizeToPx(defaultPickerItemHeightValue) <= 0) {
            return height;
        }
        if (defaultPickerItemHeightValue.Unit() == DimensionUnit::PERCENT) {
            height = pickerTheme->GetGradientHeight().ConvertToPx() * defaultPickerItemHeightValue.ConvertToPx();
        } else {
            height = context->NormalizeToPx(defaultPickerItemHeightValue);
        }
    } else {
        height = pickerTheme->GetDividerSpacing().ConvertToPx();
    }
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return height;
}

std::string TextPickerPattern::GetSelectedObject(bool isColumnChange, int32_t status) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto value = GetOption(GetSelected());
    auto index = GetSelected();
    if (isColumnChange) {
        value = GetCurrentText();
        index = GetCurrentIndex();
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");

    if (context->GetIsDeclarative()) {
        return std::string("{\"value\":") + "\"" + value + "\"" + ",\"index\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    } else {
        return std::string("{\"newValue\":") + "\"" + value + "\"" + ",\"newSelected\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    }
}

void TextPickerPattern::UpdateColumnChildPosition(double offsetY)
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
    InnerHandleScroll(LessNotEqual(dragDelta, 0.0));
    double jumpDelta = (LessNotEqual(dragDelta, 0.0) ? jumpInterval_ : 0.0 - jumpInterval_);
    ScrollOption(jumpDelta);
    yOffset_ = offsetY - jumpDelta;
}

bool TextPickerPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    int totalOptionCount = static_cast<int>(GetOptionCount());
    int currentIndex = static_cast<int>(GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

bool TextPickerPattern::NotLoopOptions() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto showOptionCount = GetShowOptionCount();
    uint32_t totalOptionCount = GetOptionCount();
    return totalOptionCount <= showOptionCount / 2 + 1; // the critical value of loop condition.
}

bool TextPickerPattern::InnerHandleScroll(bool isDown)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto totalOptionCount = GetOptionCount();

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
    isIndexChanged_ = true;
    return true;
}

void TextPickerPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN_NOLOG(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));
}

bool TextPickerPattern::OnKeyEvent(const KeyEvent& event)
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

bool TextPickerPattern::HandleDirectionKey(KeyCode code)
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

} // namespace OHOS::Ace::NG
