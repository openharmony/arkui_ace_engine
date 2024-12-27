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
#include <cstdlib>
#include <iterator>
#include <list>

#include "core/components_ng/pattern/time_picker/timepicker_haptic_factory.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {
namespace {
// timepicker style modification
constexpr Dimension PADDING_WEIGHT = 10.0_vp;
const Dimension FONT_SIZE = Dimension(2.0);
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const int32_t CHILDREN_SIZE = 3;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_HOUR24_HEIGHT_NUMBER = 9.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
const Dimension FOCUS_SIZE = Dimension(1.0);
const int32_t MIDDLE_CHILD_INDEX = 2;
const float MOVE_DISTANCE = 5.0f;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr int32_t PRESS_ANIMATION_DURATION = 100;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr float FONTWEIGHT = 0.5f;
constexpr float FONT_SIZE_PERCENT = 1.0f;
constexpr char MEASURE_SIZE_STRING[] = "TEST";
constexpr int32_t HOT_ZONE_HEIGHT_CANDIDATE = 2;
constexpr int32_t HOT_ZONE_HEIGHT_DISAPPEAR = 4;
constexpr char PICKER_DRAG_SCENE[] = "picker_drag_scene";
} // namespace

void TimePickerColumnPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
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
    InitHapticController(host);
    RegisterWindowStateChangedCallback();
}

void TimePickerColumnPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    UnregisterWindowStateChangedCallback();
}

void TimePickerColumnPattern::OnModifyDone()
{
    auto host = GetHost();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    pressColor_ = theme->GetPressColor();
    hoverColor_ = theme->GetHoverColor();
    auto showCount = GetShowCount();
    InitOnKeyEvent(focusHub);
    InitMouseAndPressEvent();
    SetAccessibilityAction();
    if (optionProperties_.empty()) {
        auto midIndex = showCount / 2;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        dividerSpacing_ = pipeline->NormalizeToPx(theme->GetDividerSpacing());
        gradientHeight_ = static_cast<float>(pipeline->NormalizeToPx(theme->GetGradientHeight()));
        MeasureContext measureContext;
        measureContext.textContent = MEASURE_SIZE_STRING;
        uint32_t childIndex = 0;
        TimePickerOptionProperty prop;
        while (childIndex < showCount) {
            if (childIndex == midIndex) { // selected
                auto selectedOptionSize = theme->GetOptionStyle(true, false).GetFontSize();
                measureContext.fontSize = selectedOptionSize;
            } else if ((childIndex == (midIndex + 1)) || (childIndex == (midIndex - 1))) {
                auto focusOptionSize = theme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
                measureContext.fontSize = focusOptionSize;
            } else {
                auto normalOptionSize = theme->GetOptionStyle(false, false).GetFontSize();
                measureContext.fontSize = normalOptionSize;
            }
            if (childIndex == midIndex) {
                prop.height = dividerSpacing_;
            } else {
                prop.height = gradientHeight_;
            }
            Size size = MeasureUtil::MeasureTextSize(measureContext);
            prop.fontheight = size.Height();
            optionProperties_.emplace_back(prop);
            childIndex++;
        }
        SetOptionShiftDistance();
    }
    InitHapticController(host);
}

void TimePickerColumnPattern::InitHapticController(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    if (timePickerRowPattern->GetIsEnableHaptic()) {
        isEnableHaptic_ = true;
        if (!hapticController_) {
            auto context = parentNode->GetContext();
            CHECK_NULL_VOID(context);
            context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->hapticController_ = TimepickerAudioHapticFactory::GetInstance();
            });
        }
    } else {
        isEnableHaptic_ = false;
        if (hapticController_) {
            hapticController_->Stop();
        }
    }
}

void TimePickerColumnPattern::RegisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
}

void TimePickerColumnPattern::UnregisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(host->GetId());
}

void TimePickerColumnPattern::OnWindowHide()
{
    isShow_ = false;
    if (hapticController_) {
        hapticController_->Stop();
    }
}

void TimePickerColumnPattern::OnWindowShow()
{
    isShow_ = true;
}

void TimePickerColumnPattern::ParseTouchListener()
{
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->OnTouchDown();
            pattern->SetLocalDownDistance(info.GetTouches().front().GetLocalLocation().GetDistance());
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
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
}

void TimePickerColumnPattern::ParseMouseEvent()
{
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
}

void TimePickerColumnPattern::InitMouseAndPressEvent()
{
    if (mouseEvent_ || touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(columnEventHub);
    RefPtr<TouchEventImpl> touchListener = CreateItemTouchEventListener();
    CHECK_NULL_VOID(touchListener);
    auto columnGesture = columnEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(columnGesture);
    columnGesture->AddTouchEvent(touchListener);
    RefPtr<FrameNode> middleChild = nullptr;
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    auto midSize = childSize / 2;
    middleChild = DynamicCast<FrameNode>(host->GetChildAtIndex(midSize));
    CHECK_NULL_VOID(middleChild);
    auto eventHub = middleChild->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ParseMouseEvent();
    inputHub->AddOnHoverEvent(mouseEvent_);
    auto gesture = middleChild->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    ParseTouchListener();
    gesture->AddTouchEvent(touchListener_);
    for (int32_t i = 0; i < childSize; i++) {
        RefPtr<FrameNode> childNode = DynamicCast<FrameNode>(host->GetChildAtIndex(i));
        CHECK_NULL_VOID(childNode);
        RefPtr<TimePickerEventParam> param = MakeRefPtr<TimePickerEventParam>();
        param->instance_ = childNode;
        param->itemIndex_ = i;
        param->itemTotalCounts_ = childSize;

        auto eventHub = childNode->GetEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        if (i != midSize) {
            RefPtr<ClickEvent> clickListener = CreateItemClickEventListener(param);
            CHECK_NULL_VOID(clickListener);
            auto gesture = eventHub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gesture);
            gesture->AddClickEvent(clickListener);
        }
    }
}

RefPtr<TouchEventImpl> TimePickerColumnPattern::CreateItemTouchEventListener()
{
    auto toss = GetToss();
    CHECK_NULL_RETURN(toss, nullptr);
    auto touchCallback = [weak = WeakClaim(this), toss](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto isToss = pattern->GetTossStatus();
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (isToss == true) {
                pattern->touchBreak_ = true;
                pattern->animationBreak_ = true;
                pattern->clickBreak_ = true;
                auto TossEndPosition = toss->GetTossEndPosition();
                pattern->SetYLast(TossEndPosition);
                toss->StopTossAnimation();
            } else {
                pattern->animationBreak_ = false;
                pattern->clickBreak_ = false;
            }
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            pattern->touchBreak_ = false;
            if (pattern->animationBreak_ == true) {
                pattern->PlayRestAnimation();
                pattern->yOffset_ = 0.0;
            }
        }
    };
    auto listener = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    return listener;
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
    auto blendNode = host->GetParent();
    CHECK_NULL_VOID(blendNode);
    auto stack = blendNode->GetParent();
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
    bool isChange =
        config.frameSizeChange || config.frameOffsetChange || config.contentSizeChange || config.contentOffsetChange;

    CHECK_NULL_RETURN(isChange, false);
    CHECK_NULL_RETURN(dirty, false);
    auto geometryNode = dirty->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, false);
    auto offset = geometryNode->GetFrameOffset();
    auto size = geometryNode->GetFrameSize();
    if (!NearEqual(offset, offset_) || !NearEqual(size, size_)) {
        offset_ = offset;
        size_ = size;
        AddHotZoneRectToText();
    }
    return true;
}

void TimePickerColumnPattern::InitTextFontFamily()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto pipeline = parentNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto timePickerLayoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(timePickerLayoutProperty);
    hasUserDefinedDisappearFontFamily_ = timePickerRowPattern->GetHasUserDefinedDisappearFontFamily();
    hasUserDefinedNormalFontFamily_ = timePickerRowPattern->GetHasUserDefinedNormalFontFamily();
    hasUserDefinedSelectedFontFamily_ = timePickerRowPattern->GetHasUserDefinedSelectedFontFamily();
    auto fontManager = pipeline->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (!(fontManager->GetAppCustomFont().empty())) {
        hasAppCustomFont_ = true;
    }
    auto appCustomFontFamily = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    if (hasAppCustomFont_ && !hasUserDefinedDisappearFontFamily_) {
        timePickerLayoutProperty->UpdateDisappearFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedNormalFontFamily_) {
        timePickerLayoutProperty->UpdateFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedSelectedFontFamily_) {
        timePickerLayoutProperty->UpdateSelectedFontFamily(appCustomFontFamily);
    }
}

void TimePickerColumnPattern::FlushCurrentOptions(bool isDown, bool isUpateTextContentOnly)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto dataPickerLayoutProperty = host->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdatePadding(PaddingProperty {
            .left = CalcLength(static_cast<float>(PADDING_WEIGHT.ConvertToPx()), DimensionUnit::PX),
            .bottom = CalcLength(),
            .top = CalcLength(),
            .start = CalcLength(),
            .end = CalcLength(),
            .right = CalcLength()});
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_VOID(timePickerRowPattern);
    auto showOptionCount = GetShowCount();
    uint32_t totalOptionCount = timePickerRowPattern->GetOptionCount(host);
    auto timePickerLayoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(timePickerLayoutProperty);
    uint32_t currentIndex = host->GetPattern<TimePickerColumnPattern>()->GetCurrentIndex();
    CHECK_EQUAL_VOID(totalOptionCount, 0);
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    auto child = host->GetChildren();
    auto iter = child.begin();
    InitTextFontFamily();

    if (!isUpateTextContentOnly) {
        animationProperties_.clear();
    }
    auto actualOptionCount = showOptionCount < child.size() ? showOptionCount : child.size();
    for (uint32_t index = 0; index < actualOptionCount; index++) {
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
        if ((NotLoopOptions() || !wheelModeEnabled_) && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent(u"");
        } else {
            auto optionValue = timePickerRowPattern->GetOptionsValue(host, optionIndex);
            textLayoutProperty->UpdateContent(optionValue);
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        }
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode();
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
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(false, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(timePickerLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    DisappearWeight_ = timePickerLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight());
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
    textLayoutProperty->UpdateTextColor(
        timePickerLayoutProperty->GetColor().value_or(pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (timePickerLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(timePickerLayoutProperty->GetFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(focusOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize() - FOCUS_SIZE);
    }
    textLayoutProperty->UpdateFontWeight(
        timePickerLayoutProperty->GetWeight().value_or(pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(timePickerLayoutProperty->GetFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(
        timePickerLayoutProperty->GetFontStyle().value_or(pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TimePickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(
        timePickerLayoutProperty->GetSelectedColor().value_or(pickerTheme->GetOptionStyle(true, false).GetTextColor()));
    if (timePickerLayoutProperty->HasSelectedFontSize()) {
        textLayoutProperty->UpdateFontSize(timePickerLayoutProperty->GetSelectedFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(selectedOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(timePickerLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight()));
    SelectedWeight_ = timePickerLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    textLayoutProperty->UpdateFontFamily(timePickerLayoutProperty->GetSelectedFontFamily().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(timePickerLayoutProperty->GetSelectedFontStyle().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontStyle()));
}

void TimePickerColumnPattern::ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    if (showOptionCount != CHILDREN_SIZE) {
        return;
    }
    auto pipeline = GetContext();
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

void TimePickerColumnPattern::ChangeTextStyle(uint32_t index, uint32_t showOptionCount,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    if (showOptionCount == CHILDREN_SIZE) {
        return;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    uint32_t val = selectedIndex > 0 ? selectedIndex - 1 : 0;
    if (index != selectedIndex) {
        if ((index == selectedIndex + 1) || (index == val)) {
            UpdateCandidateTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
        } else {
            UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);
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

void TimePickerColumnPattern::AddAnimationTextProperties(
    uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    TimeTextProperties properties;
    if (textLayoutProperty->HasFontSize()) {
        MeasureContext measureContext;
        measureContext.textContent = MEASURE_SIZE_STRING;
        measureContext.fontSize = textLayoutProperty->GetFontSize().value();
        auto size = MeasureUtil::MeasureTextSize(measureContext);
        if (!optionProperties_.empty()) {
            optionProperties_[currentIndex].fontheight = size.Height();
            if (optionProperties_[currentIndex].fontheight > optionProperties_[currentIndex].height) {
                optionProperties_[currentIndex].fontheight = optionProperties_[currentIndex].height;
            }
        }
        SetOptionShiftDistance();
        properties.fontSize = Dimension(textLayoutProperty->GetFontSize().value().ConvertToPx());
    }
    if (textLayoutProperty->HasFontWeight()) {
        properties.fontWeight = textLayoutProperty->GetFontWeight().value();
    }
    if (textLayoutProperty->HasTextColor()) {
        properties.currentColor = textLayoutProperty->GetTextColor().value();
    }
    if (currentIndex > 0) {
        properties.upFontSize = animationProperties_[currentIndex - 1].fontSize;
        animationProperties_[currentIndex - 1].downFontSize = properties.fontSize;

        properties.upColor = animationProperties_[currentIndex - 1].currentColor;
        animationProperties_[currentIndex - 1].downColor = properties.currentColor;

        properties.upFontWeight = animationProperties_[currentIndex - 1].fontWeight;
        animationProperties_[currentIndex - 1].downFontWeight = properties.fontWeight;
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

void TimePickerColumnPattern::TextPropertiesLinearAnimation(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index, uint32_t showCount, bool isDown, double scale)
{
    if (index >= animationProperties_.size()) {
        return;
    }
    Dimension startFontSize = animationProperties_[index].fontSize;
    Color startColor = animationProperties_[index].currentColor;
    if ((!index && isDown) || ((index == (showCount - 1)) && !isDown && scale)) {
        textLayoutProperty->UpdateFontSize(startFontSize);
        textLayoutProperty->UpdateTextColor(startColor);
        return;
    }
    Dimension endFontSize;
    Color endColor;
    if (!isDown) {
        endFontSize = animationProperties_[index].downFontSize;
        endColor = animationProperties_[index].downColor;

        if (scale >= FONTWEIGHT) {
            textLayoutProperty->UpdateFontWeight(animationProperties_[index].downFontWeight);
        }
    } else {
        endFontSize = animationProperties_[index].upFontSize;
        endColor = animationProperties_[index].upColor;

        if (scale >= FONTWEIGHT) {
            textLayoutProperty->UpdateFontWeight(animationProperties_[index].upFontWeight);
        }
    }
    Dimension updateSize = LinearFontSize(startFontSize, endFontSize, distancePercent_);
    textLayoutProperty->UpdateFontSize(updateSize);
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    Color updateColor = colorEvaluator->Evaluate(startColor, endColor, distancePercent_);
    textLayoutProperty->UpdateTextColor(updateColor);
    if (scale < FONTWEIGHT) {
        textLayoutProperty->UpdateFontWeight(animationProperties_[index].fontWeight);
    }
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
        iter++;
    }
}

Dimension TimePickerColumnPattern::LinearFontSize(
    const Dimension& startFontSize, const Dimension& endFontSize, double percent)
{
    if (percent > FONT_SIZE_PERCENT) {
        return startFontSize + (endFontSize - startFontSize);
    } else {
        return startFontSize + (endFontSize - startFontSize) * percent;
    }
}

void TimePickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!panEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (event.GetInputEventType() == InputEventType::AXIS && event.GetSourceTool() == SourceTool::MOUSE) {
            return;
        }
        pattern->HandleDragStart(event);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetMainVelocity(event.GetMainVelocity());
        pattern->HandleDragMove(event);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            return;
        }
        pattern->SetMainVelocity(info.GetMainVelocity());
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    CHECK_NULL_VOID(GetHost());
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY = event.GetGlobalPoint().GetY();
    toss->SetStart(offsetY);
    yLast_ = offsetY;
    pressed_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.GetMainVelocity(), SceneStatus::START);
    // AccessibilityEventType::SCROLL_START
}

void TimePickerColumnPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetInputEventType() == InputEventType::AXIS && event.GetSourceTool() == SourceTool::MOUSE) {
        InnerHandleScroll(LessNotEqual(event.GetDelta().GetY(), 0.0), true);
        return;
    }
    animationBreak_ = false;
    CHECK_NULL_VOID(pressed_);
    CHECK_NULL_VOID(GetHost());
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY =
        event.GetGlobalPoint().GetY() + (event.GetInputEventType() == InputEventType::AXIS ? event.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, 1.0)) { // if changing less than 1.0, no need to handle
        return;
    }
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.GetMainVelocity(), SceneStatus::RUNNING);
}

void TimePickerColumnPattern::HandleDragEnd()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    pressed_ = false;
    CHECK_NULL_VOID(GetHost());
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (!NotLoopOptions() && toss->Play()) {
        frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
        // AccessibilityEventType::SCROLL_END
        return;
    }
    yOffset_ = 0.0;
    yLast_ = 0.0;
    if (!animationCreated_) {
        ScrollOption(0.0);
        return;
    }

    TimePickerScrollDirection dir =
        scrollDelta_ > 0.0 ? TimePickerScrollDirection::DOWN : TimePickerScrollDirection::UP;
    int32_t middleIndex = static_cast<int32_t>(GetShowCount()) / MIDDLE_CHILD_INDEX;
    auto shiftDistance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                                : optionProperties_[middleIndex].nextDistance;
    auto shiftThreshold = shiftDistance / MIDDLE_CHILD_INDEX;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == TimePickerScrollDirection::UP ? -1 : 1);
    }
    CreateAnimation(scrollDelta_, 0.0);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
    // AccessibilityEventType::SCROLL_END
}

void TimePickerColumnPattern::CreateAnimation()
{
    CHECK_NULL_VOID(!animationCreated_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->ScrollOption(value);
    };
    scrollProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(scrollProperty_);

    auto aroundClickCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        if (value > 0) {
            column->UpdateColumnChildPosition(std::ceil(value));
        } else {
            column->UpdateColumnChildPosition(std::floor(value));
        }
    };
    aroundClickProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(aroundClickCallback));
    renderContext->AttachNodeAnimatableProperty(aroundClickProperty_);
    animationCreated_ = true;
}

void TimePickerColumnPattern::CreateAnimation(double from, double to)
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), to]() {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->scrollProperty_->Set(to);
    });
}

void TimePickerColumnPattern::ScrollOption(double delta, bool isJump)
{
    scrollDelta_ = delta;
    auto midIndex = GetShowCount() / 2;
    TimePickerScrollDirection dir = delta > 0.0 ? TimePickerScrollDirection::DOWN : TimePickerScrollDirection::UP;
    auto shiftDistance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                                : optionProperties_[midIndex].nextDistance;
    distancePercent_ = delta / shiftDistance;
    auto textLinearPercent = 0.0;
    textLinearPercent = (std::abs(delta)) / (optionProperties_[midIndex].height);
    UpdateTextPropertiesLinear(LessNotEqual(delta, 0.0), textLinearPercent);
    CalcAlgorithmOffset(dir, distancePercent_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void TimePickerColumnPattern::ResetAlgorithmOffset()
{
    algorithmOffset_.clear();
    uint32_t counts = GetShowCount();
    for (uint32_t i = 0; i < counts; i++) {
        algorithmOffset_.emplace_back(0.0f);
    }
}

void TimePickerColumnPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TimePickerColumnPattern::CalcAlgorithmOffset(TimePickerScrollDirection dir, double distancePercent)
{
    algorithmOffset_.clear();
    uint32_t counts = GetShowCount();
    for (uint32_t i = 0; i < counts; i++) {
        auto distance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[i].prevDistance
                                                               : optionProperties_[i].nextDistance;
        algorithmOffset_.emplace_back(static_cast<int32_t>(distance * distancePercent));
    }
}

float TimePickerColumnPattern::GetShiftDistance(uint32_t index, TimePickerScrollDirection dir)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    const uint32_t optionCounts = GetShowCount();
    uint32_t nextIndex = 0;
    float distance = 0.0f;
    float val = 0.0f;
    auto isDown = dir == TimePickerScrollDirection::DOWN;
    if (optionCounts == 0) {
        return distance;
    }
    if (isDown) {
        nextIndex = (optionCounts + index + 1) % optionCounts; // index add one
    } else {
        nextIndex = (optionCounts + index - 1) % optionCounts; // index reduce one
    }
    switch (static_cast<TimePickerOptionIndex>(index)) {
        case TimePickerOptionIndex::COLUMN_INDEX_0: // first
            distance = (dir == TimePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_1:
            distance = (dir == TimePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_2:
            if (dir == TimePickerScrollDirection::UP) {
                distance = -optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                          MIDDLE_CHILD_INDEX;
                distance = std::ceil(val);
            }
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_3:
            val = (optionProperties_[index].height - optionProperties_[nextIndex].fontheight) / MIDDLE_CHILD_INDEX +
                  optionProperties_[nextIndex].height;
            distance = (dir == TimePickerScrollDirection::DOWN) ? val : (0.0f - val);
            distance = std::floor(distance);
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_4:
            if (dir == TimePickerScrollDirection::DOWN) {
                distance = optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                          MIDDLE_CHILD_INDEX;
                distance = std::ceil(0.0f - val);
            }
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_5:
            distance = (dir == TimePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_6: // last
            distance = (dir == TimePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        default:
            break;
    }
    return distance;
}

float TimePickerColumnPattern::GetShiftDistanceForLandscape(uint32_t index, TimePickerScrollDirection dir)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    uint32_t optionCounts = GetShowCount();
    uint32_t nextIndex = 0;
    float distance = 0.0f;
    float val = 0.0f;
    auto isDown = dir == TimePickerScrollDirection::DOWN;
    if (optionCounts == 0) {
        return distance;
    }
    if (isDown) {
        nextIndex = (optionCounts + index + 1) % optionCounts; // index add one
    } else {
        nextIndex = (optionCounts + index - 1) % optionCounts; // index reduce one
    }
    switch (static_cast<TimePickerOptionIndex>(index)) {
        case TimePickerOptionIndex::COLUMN_INDEX_0: // first
            if (dir == TimePickerScrollDirection::UP) {
                distance = 0.0f - optionProperties_[index].height;
            } else {
                distance = optionProperties_[index].height +
                           (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                               MIDDLE_CHILD_INDEX;
            }
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_1:
            val = (optionProperties_[index].height - optionProperties_[nextIndex].fontheight) / MIDDLE_CHILD_INDEX +
                  optionProperties_[nextIndex].height;
            distance = (dir == TimePickerScrollDirection::DOWN) ? val : (0.0f - val);
            distance = std::floor(distance);
            break;
        case TimePickerOptionIndex::COLUMN_INDEX_2: // last
            if (dir == TimePickerScrollDirection::DOWN) {
                distance = optionProperties_[index].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                          MIDDLE_CHILD_INDEX;
                distance = 0.0f - val;
            }
            break;
        default:
            break;
    }
    return distance;
}

void TimePickerColumnPattern::SetOptionShiftDistance()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    uint32_t itemCounts = GetShowCount();
    bool isLanscape = itemCounts == OPTION_COUNT_PHONE_LANDSCAPE;
    for (uint32_t i = 0; i < itemCounts; i++) {
        TimePickerOptionProperty& prop = optionProperties_[i];
        if (isLanscape) {
            prop.prevDistance = GetShiftDistanceForLandscape(i, TimePickerScrollDirection::UP);
            prop.nextDistance = GetShiftDistanceForLandscape(i, TimePickerScrollDirection::DOWN);
        } else {
            prop.prevDistance = GetShiftDistance(i, TimePickerScrollDirection::UP);
            prop.nextDistance = GetShiftDistance(i, TimePickerScrollDirection::DOWN);
        }
    }
}

void TimePickerColumnPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void TimePickerColumnPattern::UpdateFinishToss(double offsetY)
{
    int32_t dragDelta = offsetY - yLast_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    auto midIndex = GetShowCount() / 2;
    TimePickerScrollDirection dir = dragDelta > 0.0 ? TimePickerScrollDirection::DOWN : TimePickerScrollDirection::UP;
    auto shiftDistance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                                : optionProperties_[midIndex].nextDistance;
    ScrollOption(shiftDistance);
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
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto childSize = host->GetChildren().size();
    if (childSize != CHILDREN_SIZE) {
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
        auto totalCountAndIndex = totalOptionCount + currentIndex;
        currentIndex = (totalCountAndIndex ? totalCountAndIndex - 1 : 0) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    if (hapticController_ && isEnableHaptic_) {
        hapticController_->PlayOnce();
    }
    FlushCurrentOptions(isDown, isUpatePropertiesOnly);
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
    return true;
}

void TimePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    int32_t dragDelta = offsetY - yLast_;
    if (hapticController_ && isShow_) {
        if (isEnableHaptic_) {
            hapticController_->HandleDelta(dragDelta);
        }
    }
    yLast_ = offsetY;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    offsetCurSet_ = 0.0;
    auto midIndex = GetShowCount() / 2;
    TimePickerScrollDirection dir = dragDelta > 0.0 ? TimePickerScrollDirection::DOWN : TimePickerScrollDirection::UP;
    auto shiftDistance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                                : optionProperties_[midIndex].nextDistance;
    // the abs of drag delta is less than jump interval.
    dragDelta = dragDelta + yOffset_;
    if (GreatOrEqual(std::abs(dragDelta), std::abs(shiftDistance))) {
        InnerHandleScroll(LessNotEqual(dragDelta, 0.0), true);
        dragDelta = dragDelta % static_cast<int>(std::abs(shiftDistance));
        if (!NearZero(dragDelta) && !CanMove(LessNotEqual(dragDelta, 0))) {
            dragDelta = 0.0;
            auto toss = GetToss();
            CHECK_NULL_VOID(toss);
            toss->StopTossAnimation();
            if (hapticController_) {
                hapticController_->Stop();
            }
        }
        ScrollOption(dragDelta, true);
        offsetCurSet_ = dragDelta;
        yOffset_ = dragDelta;
        return;
    }
    // update selected option
    ScrollOption(dragDelta);
    offsetCurSet_ = dragDelta;
    yOffset_ = dragDelta;
}

void TimePickerColumnPattern::ShiftOptionProp(RefPtr<FrameNode> curNode, RefPtr<FrameNode> shiftNode)
{
    RefPtr<TextPattern> curPattern = curNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(curPattern);
    RefPtr<TextLayoutProperty> curLayoutProperty = curPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(curLayoutProperty);

    RefPtr<TextPattern> shiftPattern = shiftNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(shiftPattern);
    RefPtr<TextLayoutProperty> shiftLayoutProperty = shiftPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(shiftLayoutProperty);
    curLayoutProperty->UpdateFontWeight(shiftLayoutProperty->GetFontWeight().value_or(FontWeight::W100));
}

bool TimePickerColumnPattern::CanMove(bool isDown) const
{
    if (wheelModeEnabled_) {
        CHECK_NULL_RETURN(NotLoopOptions(), true);
    }
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
        CHECK_NULL_RETURN(pattern, false);
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
        pattern->CreateAnimation(0.0 - pattern->jumpInterval_, 0.0);
        // AccessibilityEventType::SCROLL_END
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->CanMove(false)) {
            return;
        }
        CHECK_NULL_VOID(pattern->animationCreated_);
        pattern->InnerHandleScroll(false);
        pattern->CreateAnimation(pattern->jumpInterval_, 0.0);
        // AccessibilityEventType::SCROLL_END
    });
}

RefPtr<ClickEvent> TimePickerColumnPattern::CreateItemClickEventListener(RefPtr<TimePickerEventParam> param)
{
    auto clickEventHandler = [param, weak = WeakClaim(this)](const GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        pattern->OnAroundButtonClick(param);
    };
    auto listener = AceType::MakeRefPtr<NG::ClickEvent>(clickEventHandler);
    return listener;
}

void TimePickerColumnPattern::OnAroundButtonClick(RefPtr<TimePickerEventParam> param)
{
    if (clickBreak_) {
        return;
    }
    int32_t middleIndex = static_cast<int32_t>(GetShowCount()) / 2;
    int32_t step = param->itemIndex_ - middleIndex;
    if (step != 0) {
        if (animation_) {
            AnimationUtils::StopAnimation(animation_);
            yLast_ = 0.0;
            yOffset_ = 0.0;
        }
        auto distance =
            (step > 0 ? optionProperties_[middleIndex].prevDistance : optionProperties_[middleIndex].nextDistance) *
            std::abs(step);
        AnimationOption option;
        option.SetCurve(Curves::FAST_OUT_SLOW_IN);
        option.SetDuration(CLICK_ANIMATION_DURATION);
        aroundClickProperty_->Set(0.0);
        animation_ = AnimationUtils::StartAnimation(option, [weak = AceType::WeakClaim(this), step, distance]() {
            auto column = weak.Upgrade();
            CHECK_NULL_VOID(column);
            column->aroundClickProperty_->Set(step > 0 ? 0.0 - std::abs(distance) : std::abs(distance));
        });
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->RequestFrame();
    }
}
void TimePickerColumnPattern::TossAnimationStoped()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    yLast_ = 0.0;
}

void TimePickerColumnPattern::PlayRestAnimation()
{
    TimePickerScrollDirection dir =
        scrollDelta_ > 0.0 ? TimePickerScrollDirection::DOWN : TimePickerScrollDirection::UP;
    int32_t middleIndex = static_cast<int32_t>(GetShowCount()) / 2;
    double shiftDistance = (dir == TimePickerScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                                  : optionProperties_[middleIndex].nextDistance;
    double shiftThreshold = shiftDistance / 2;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == TimePickerScrollDirection::UP ? -1 : 1);
    }

    CreateAnimation(scrollDelta_, 0.0);
}

DimensionRect TimePickerColumnPattern::CalculateHotZone(
    int32_t index, int32_t midSize, float middleChildHeight, float otherChildHeight)
{
    float hotZoneHeight = 0.0f;
    float hotZoneOffsetY = 0.0f;
    if (index == midSize) {
        hotZoneHeight = middleChildHeight;
    }
    if (size_.Height() <= middleChildHeight) {
        hotZoneHeight = index == midSize ? size_.Height() : 0;
    } else if (size_.Height() <= (middleChildHeight + HOT_ZONE_HEIGHT_CANDIDATE * otherChildHeight)) {
        if ((index == midSize + 1) || (index == midSize - 1)) {
            hotZoneHeight = (size_.Height() - middleChildHeight) / MIDDLE_CHILD_INDEX;
            hotZoneOffsetY = (index == midSize - 1) ? (otherChildHeight - hotZoneHeight) : 0;
        }
    } else if (size_.Height() <= (middleChildHeight + HOT_ZONE_HEIGHT_DISAPPEAR * otherChildHeight)) {
        if ((index == midSize + 1) || (index == midSize - 1)) {
            hotZoneHeight = otherChildHeight;
        } else if ((index == midSize + HOT_ZONE_HEIGHT_CANDIDATE) || (index == midSize - HOT_ZONE_HEIGHT_CANDIDATE)) {
            hotZoneHeight = (size_.Height() - middleChildHeight - HOT_ZONE_HEIGHT_CANDIDATE * otherChildHeight) /
                            MIDDLE_CHILD_INDEX;
            hotZoneOffsetY = (index == midSize - HOT_ZONE_HEIGHT_CANDIDATE) ? (otherChildHeight - hotZoneHeight) : 0;
        }
    } else {
        if ((index == midSize + 1) || (index == midSize - 1)) {
            hotZoneHeight = otherChildHeight;
        } else if ((index == midSize + HOT_ZONE_HEIGHT_CANDIDATE) || (index == midSize - HOT_ZONE_HEIGHT_CANDIDATE)) {
            hotZoneHeight = otherChildHeight;
        }
    }
    OffsetF hotZoneOffset;
    SizeF hotZoneSize;
    hotZoneOffset.SetX(0.0f);
    hotZoneOffset.SetY(hotZoneOffsetY);
    hotZoneSize.SetWidth(size_.Width());
    hotZoneSize.SetHeight(hotZoneHeight);
    DimensionRect hotZoneRegion;
    hotZoneRegion.SetSize(DimensionSize(Dimension(hotZoneSize.Width()), Dimension(hotZoneSize.Height())));
    hotZoneRegion.SetOffset(DimensionOffset(Dimension(hotZoneOffset.GetX()), Dimension(hotZoneOffset.GetY())));
    return hotZoneRegion;
}

void TimePickerColumnPattern::AddHotZoneRectToText()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    auto midSize = childSize / MIDDLE_CHILD_INDEX;
    auto middleChildHeight = optionProperties_[midSize].height;
    auto otherChildHeight = optionProperties_[midSize - 1].height;
    for (int32_t i = 0; i < childSize; i++) {
        RefPtr<FrameNode> childNode = DynamicCast<FrameNode>(host->GetChildAtIndex(i));
        CHECK_NULL_VOID(childNode);
        DimensionRect hotZoneRegion = CalculateHotZone(i, midSize, middleChildHeight, otherChildHeight);
        childNode->AddHotZoneRect(hotZoneRegion);
    }
}
} // namespace OHOS::Ace::NG
