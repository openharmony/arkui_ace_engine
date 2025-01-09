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

#include "core/components_ng/pattern/picker/datepicker_column_pattern.h"

#include <cstdint>
#include <cstdlib>
#include <iterator>
#include <list>
#include <stdint.h>

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/log/log.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_base_component.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/pattern/button/button_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_event_hub.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/components_ng/pattern/picker/toss_animation_controller.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/property/calc_length.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

namespace {

// Datepicker style modification
constexpr float PADDING_WEIGHT = 10.0f;
const Dimension FONT_SIZE = Dimension(2.0);
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
const int32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const Dimension FOCUS_SIZE = Dimension(1.0);
const float MOVE_DISTANCE = 5.0f;
constexpr int32_t HOVER_ANIMATION_DURATION = 250;
constexpr int32_t PRESS_ANIMATION_DURATION = 100;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr int32_t MIDDLE_CHILD_INDEX = 2;
constexpr char MEASURE_SIZE_STRING[] = "TEST";
constexpr float FONTWEIGHT = 0.5f;
constexpr float FONT_SIZE_PERCENT = 1.0f;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr int32_t HOT_ZONE_HEIGHT_CANDIDATE = 2;
constexpr int32_t HOT_ZONE_HEIGHT_DISAPPEAR = 4;
constexpr char PICKER_DRAG_SCENE[] = "picker_drag_scene";
} // namespace

void DatePickerColumnPattern::OnAttachToFrameNode()
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
    InitHapticController();
    RegisterWindowStateChangedCallback();
}

void DatePickerColumnPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    UnregisterWindowStateChangedCallback();
}

void DatePickerColumnPattern::OnModifyDone()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    pressColor_ = theme->GetPressColor();
    hoverColor_ = theme->GetHoverColor();
    useButtonFocusArea_ = theme->NeedButtonFocusAreaType();
    InitSelectorButtonProperties(theme);
    auto showCount = theme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
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
        DatePickerOptionProperty prop;
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
}

void DatePickerColumnPattern::InitHapticController()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto datePickerPattern = parentNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    if (datePickerPattern->GetEnableHapticFeedback()) {
        isEnableHaptic_ = true;
        if (!hapticController_) {
            auto context = parentNode->GetContext();
            CHECK_NULL_VOID(context);
            context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
            });
        }
    } else {
        isEnableHaptic_ = false;
        if (hapticController_) {
            hapticController_->Stop();
        }
    }
}

void DatePickerColumnPattern::RegisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
}

void DatePickerColumnPattern::UnregisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(host->GetId());
}

void DatePickerColumnPattern::OnWindowHide()
{
    isShow_ = false;
    if (hapticController_) {
        hapticController_->Stop();
    }
}

void DatePickerColumnPattern::OnWindowShow()
{
    isShow_ = true;
}

void DatePickerColumnPattern::ParseTouchListener()
{
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->SetLocalDownDistance(info.GetTouches().front().GetLocalLocation().GetDistance());
            pattern->OnTouchDown();
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

void DatePickerColumnPattern::ParseMouseEvent()
{
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(isHover);
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
}

void DatePickerColumnPattern::InitMouseAndPressEvent()
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
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    RefPtr<FrameNode> middleChild = nullptr;
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
        RefPtr<DatePickerEventParam> param = MakeRefPtr<DatePickerEventParam>();
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

RefPtr<TouchEventImpl> DatePickerColumnPattern::CreateItemTouchEventListener()
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

void DatePickerColumnPattern::HandleMouseEvent(bool isHover)
{
    if (isHover) {
        hoverd_ = true;
        PlayHoverAnimation(GetButtonHoverColor());
    } else {
        hoverd_ = false;
        PlayHoverAnimation(buttonBgColor_);
    }
}

void DatePickerColumnPattern::OnTouchDown()
{
    PlayPressAnimation(pressColor_);
}

void DatePickerColumnPattern::OnTouchUp()
{
    if (hoverd_) {
        PlayPressAnimation(GetButtonHoverColor());
    } else {
        PlayPressAnimation(Color::TRANSPARENT);
    }
}

void DatePickerColumnPattern::SetButtonBackgroundColor(const Color& pressColor)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blend = host->GetParent();
    CHECK_NULL_VOID(blend);
    auto stack = blend->GetParent();
    CHECK_NULL_VOID(stack);
    auto buttonNode = DynamicCast<FrameNode>(stack->GetFirstChild());
    auto renderContext = buttonNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(pressColor);
    buttonNode->MarkModifyDone();
    buttonNode->MarkDirtyNode();
}

void DatePickerColumnPattern::PlayPressAnimation(const Color& pressColor)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(PRESS_ANIMATION_DURATION);
    option.SetCurve(Curves::SHARP);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), pressColor]() {
        auto picker = weak.Upgrade();
        CHECK_NULL_VOID(picker);
        picker->SetButtonBackgroundColor(pressColor);
    });
}

void DatePickerColumnPattern::PlayHoverAnimation(const Color& color)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetCurve(Curves::FRICTION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), color]() {
        auto picker = weak.Upgrade();
        CHECK_NULL_VOID(picker);
        picker->SetButtonBackgroundColor(color);
    });
}

void DatePickerColumnPattern::InitSelectorButtonProperties(const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    if (useButtonFocusArea_) {
        buttonDefaultBgColor_ = pickerTheme->GetSelectorItemNormalBgColor();
        buttonFocusBgColor_ = pickerTheme->GetSelectorItemFocusBgColor();
        buttonDefaultBorderColor_ = pickerTheme->GetSelectorItemBorderColor();
        buttonFocusBorderColor_ = pickerTheme->GetSelectorItemFocusBorderColor();
        selectorTextFocusColor_ = pickerTheme->GetOptionStyle(true, true).GetTextColor();
        pressColor_ = buttonDefaultBgColor_.BlendColor(pickerTheme->GetPressColor());
        hoverColor_ = buttonDefaultBgColor_.BlendColor(pickerTheme->GetHoverColor());

        buttonFocusBorderWidth_ = pickerTheme->GetSelectorItemFocusBorderWidth();
        buttonDefaultBorderWidth_ = pickerTheme->GetSelectorItemBorderWidth();
    }
}

const Color& DatePickerColumnPattern::GetButtonHoverColor() const
{
    return useButtonFocusArea_ && isFocusColumn_ ? buttonFocusBgColor_ : hoverColor_;
}

void DatePickerColumnPattern::UpdateColumnButtonFocusState(bool haveFocus, bool needMarkDirty)
{
    auto isInitUpdate = isFirstTimeUpdateButtonProps_ && !haveFocus;
    auto isFocusChanged = isFocusColumn_ != haveFocus;

    if (isFocusChanged || isInitUpdate) {
        isFocusColumn_ = haveFocus;
        UpdateSelectorButtonProps(isFocusColumn_, needMarkDirty);
    }
    if (isFocusChanged) {
        FlushCurrentOptions();
    }
    if (isInitUpdate) {
        isFirstTimeUpdateButtonProps_ = false;
    }
}

void DatePickerColumnPattern::UpdateSelectorButtonProps(bool haveFocus, bool needMarkDirty)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blend = host->GetParent();
    CHECK_NULL_VOID(blend);
    auto stack = blend->GetParent();
    CHECK_NULL_VOID(stack);
    auto buttonNode = DynamicCast<FrameNode>(stack->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    BorderWidthProperty borderWidth;
    BorderColorProperty borderColor;

    if (haveFocus) {
        buttonBgColor_ = buttonFocusBgColor_;
        borderWidth.SetBorderWidth(buttonFocusBorderWidth_);
        borderColor.SetColor(buttonFocusBorderColor_);
    } else {
        buttonBgColor_ = buttonDefaultBgColor_;
        borderWidth.SetBorderWidth(buttonDefaultBorderWidth_);
        borderColor.SetColor(buttonDefaultBorderColor_);
    }

    buttonLayoutProperty->UpdateBorderWidth(borderWidth);
    renderContext->UpdateBorderColor(borderColor);
    renderContext->UpdateBackgroundColor(buttonBgColor_);

    if (needMarkDirty) {
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode();
    }
}

void DatePickerColumnPattern::UpdateTextAreaPadding(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (useButtonFocusArea_) {
        auto padding = pickerTheme->GetSelectorItemSpace();
        PaddingProperty defaultPadding = { CalcLength(padding), CalcLength(padding),
            CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp) };
        textLayoutProperty->UpdatePadding(defaultPadding);
    }
}

bool DatePickerColumnPattern::OnDirtyLayoutWrapperSwap(
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

void DatePickerColumnPattern::InitTextFontFamily()
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
    auto datePickerPattern = parentNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto dataPickerRowLayoutProperty = parentNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    hasUserDefinedDisappearFontFamily_ = datePickerPattern->GetHasUserDefinedDisappearFontFamily();
    hasUserDefinedNormalFontFamily_ = datePickerPattern->GetHasUserDefinedNormalFontFamily();
    hasUserDefinedSelectedFontFamily_ = datePickerPattern->GetHasUserDefinedSelectedFontFamily();
    auto fontManager = pipeline->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (!(fontManager->GetAppCustomFont().empty())) {
        hasAppCustomFont_ = true;
    }
    auto appCustomFontFamily = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    if (hasAppCustomFont_ && !hasUserDefinedDisappearFontFamily_) {
        dataPickerRowLayoutProperty->UpdateDisappearFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedNormalFontFamily_) {
        dataPickerRowLayoutProperty->UpdateFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedSelectedFontFamily_) {
        dataPickerRowLayoutProperty->UpdateSelectedFontFamily(appCustomFontFamily);
    }
}

void DatePickerColumnPattern::FlushCurrentOptions(
    bool isDown, bool isUpateTextContentOnly, bool isUpdateAnimationProperties)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);

    auto dataPickerLayoutProperty = host->GetLayoutProperty<DataPickerLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdatePadding(PaddingProperty {
        .left = CalcLength(PADDING_WEIGHT, DimensionUnit::PX),
        .right = CalcLength(),
        .top = CalcLength(),
        .bottom = CalcLength(),
        .start = CalcLength(),
        .end = CalcLength()});
    dataPickerLayoutProperty->UpdateAlignSelf(FlexAlign::CENTER);

    InitTextFontFamily();

    auto datePickerPattern = parentNode->GetPattern<DatePickerPattern>();
    CHECK_NULL_VOID(datePickerPattern);
    auto dataPickerRowLayoutProperty = parentNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);
    auto showOptionCount = datePickerPattern->GetShowCount();
    uint32_t totalOptionCount = datePickerPattern->GetOptionCount(host);
    uint32_t currentIndex = host->GetPattern<DatePickerColumnPattern>()->GetCurrentIndex();
    CHECK_EQUAL_VOID(totalOptionCount, 0);
    currentIndex = currentIndex % totalOptionCount;
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.

    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showOptionCount) {
        return;
    }
    SetCurrentIndex(currentIndex);
    SetDividerHeight(showOptionCount);
    if (!isUpateTextContentOnly) {
        animationProperties_.clear();
    }
    for (uint32_t index = 0; index < showOptionCount; index++) {
        currentChildIndex_ = static_cast<int32_t>(index);
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - selectedIndex) % totalOptionCount;

        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (!isUpateTextContentOnly) {
            UpdatePickerTextProperties(index, showOptionCount, textLayoutProperty, dataPickerRowLayoutProperty);
        }
        iter++;
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(selectedIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent(u"");
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode();
            continue;
        }
        auto date = datePickerPattern->GetAllOptions(host)[optionIndex];
        auto optionValue = DatePickerPattern::GetFormatString(date);
        textLayoutProperty->UpdateContent(optionValue);
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
    if (isUpateTextContentOnly && isUpdateAnimationProperties) {
        FlushAnimationTextProperties(isDown);
    }
}

void DatePickerColumnPattern::UpdatePickerTextProperties(uint32_t index, uint32_t showOptionCount,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    uint32_t selectedIndex = showOptionCount / 2; // the center option is selected.
    uint32_t val = selectedIndex > 0 ? selectedIndex - 1 : 0;
    if (index == selectedIndex) {
        UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, dataPickerRowLayoutProperty);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    } else if ((index == selectedIndex + 1) || (index == val)) {
        UpdateCandidateTextProperties(pickerTheme, textLayoutProperty, dataPickerRowLayoutProperty);
    } else {
        UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, dataPickerRowLayoutProperty);
    }
    if (index < selectedIndex) {
        textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
    } else if (index > selectedIndex) {
        textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
    }
    textLayoutProperty->UpdateMaxLines(1);
    AddAnimationTextProperties(index, textLayoutProperty);
}

void DatePickerColumnPattern::UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(dataPickerRowLayoutProperty->GetDisappearColor().value_or(
        pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (dataPickerRowLayoutProperty->HasDisappearFontSize()) {
        textLayoutProperty->UpdateFontSize(dataPickerRowLayoutProperty->GetDisappearFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(normalOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(false, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(dataPickerRowLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(dataPickerRowLayoutProperty->GetDisappearFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(dataPickerRowLayoutProperty->GetDisappearFontStyle().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void DatePickerColumnPattern::UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    textLayoutProperty->UpdateTextColor(
        dataPickerRowLayoutProperty->GetColor().value_or(pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (dataPickerRowLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(dataPickerRowLayoutProperty->GetFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(focusOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize() - FOCUS_SIZE);
    }
    textLayoutProperty->UpdateFontWeight(
        dataPickerRowLayoutProperty->GetWeight().value_or(pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    CandidateWeight_ =
        dataPickerRowLayoutProperty->GetWeight().value_or(pickerTheme->GetOptionStyle(false, false).GetFontWeight());
    textLayoutProperty->UpdateFontFamily(dataPickerRowLayoutProperty->GetFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(
        dataPickerRowLayoutProperty->GetFontStyle().value_or(pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void DatePickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(dataPickerRowLayoutProperty->GetSelectedColor().value_or(
        pickerTheme->GetOptionStyle(true, false).GetTextColor()));
    if (dataPickerRowLayoutProperty->HasSelectedFontSize()) {
        textLayoutProperty->UpdateFontSize(dataPickerRowLayoutProperty->GetSelectedFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(selectedOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(dataPickerRowLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight()));
    SelectedWeight_ = dataPickerRowLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight());
    textLayoutProperty->UpdateFontFamily(dataPickerRowLayoutProperty->GetSelectedFontFamily().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(dataPickerRowLayoutProperty->GetSelectedFontStyle().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontStyle()));
}

void DatePickerColumnPattern::SetDividerHeight(uint32_t showOptionCount)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() * TEXT_HEIGHT_NUMBER);
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

void DatePickerColumnPattern::AddAnimationTextProperties(
    uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    DateTextProperties properties;
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
    if (textLayoutProperty->HasTextColor()) {
        properties.currentColor = textLayoutProperty->GetTextColor().value();
    }
    if (textLayoutProperty->HasFontWeight()) {
        properties.fontWeight = textLayoutProperty->GetFontWeight().value();
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

void DatePickerColumnPattern::FlushAnimationTextProperties(bool isDown)
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

void DatePickerColumnPattern::TextPropertiesLinearAnimation(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index, uint32_t showCount, bool isDown, double scale)
{
    if (index >= animationProperties_.size()) {
        return;
    }
    Dimension startFontSize = animationProperties_[index].fontSize;
    Color startColor = animationProperties_[index].currentColor;
    if ((!index && isDown) || ((index == (showCount - 1)) && !isDown)) {
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

void DatePickerColumnPattern::UpdateTextPropertiesLinear(bool isDown, double scale)
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

Dimension DatePickerColumnPattern::LinearFontSize(
    const Dimension& startFontSize, const Dimension& endFontSize, double percent)
{
    if (percent > FONT_SIZE_PERCENT) {
        return startFontSize + (endFontSize - startFontSize);
    } else {
        return startFontSize + (endFontSize - startFontSize) * percent;
    }
}

bool DatePickerColumnPattern::InnerHandleScroll(
    bool isDown, bool isUpatePropertiesOnly, bool isUpdateAnimationProperties)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto options = GetOptions();
    auto totalOptionCount = options[host].size();

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
    FlushCurrentOptions(isDown, isUpatePropertiesOnly, isUpdateAnimationProperties);
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
    return true;
}

void DatePickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
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

void DatePickerColumnPattern::HandleDragStart(const GestureEvent& event)
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

void DatePickerColumnPattern::HandleDragMove(const GestureEvent& event)
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

void DatePickerColumnPattern::HandleDragEnd()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    pressed_ = false;
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
    DatePickerScrollDirection dir =
        scrollDelta_ > 0.0 ? DatePickerScrollDirection::DOWN : DatePickerScrollDirection::UP;
    uint32_t middleIndex = GetShowCount() / 2;
    auto shiftDistance = (dir == DatePickerScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                                : optionProperties_[middleIndex].nextDistance;
    auto shiftThreshold = shiftDistance / 2;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == DatePickerScrollDirection::UP ? -1 : 1);
    }
    CreateAnimation(scrollDelta_, 0.0);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
    // AccessibilityEventType::SCROLL_END
}

void DatePickerColumnPattern::CreateAnimation()
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

void DatePickerColumnPattern::CreateAnimation(double from, double to)
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

void DatePickerColumnPattern::ScrollOption(double delta, bool isJump)
{
    scrollDelta_ = delta;
    auto midIndex = GetShowCount() / 2;
    DatePickerScrollDirection dir = delta > 0.0 ? DatePickerScrollDirection::DOWN : DatePickerScrollDirection::UP;
    auto shiftDistance = (dir == DatePickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
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

void DatePickerColumnPattern::ResetAlgorithmOffset()
{
    algorithmOffset_.clear();
    uint32_t counts = GetShowCount();
    for (uint32_t i = 0; i < counts; i++) {
        algorithmOffset_.emplace_back(0.0f);
    }
}

void DatePickerColumnPattern::CalcAlgorithmOffset(DatePickerScrollDirection dir, double distancePercent)
{
    algorithmOffset_.clear();
    uint32_t counts = GetShowCount();

    for (uint32_t i = 0; i < counts; i++) {
        auto distance = (dir == DatePickerScrollDirection::UP) ? optionProperties_[i].prevDistance
                                                               : optionProperties_[i].nextDistance;
        algorithmOffset_.emplace_back(static_cast<int32_t>(distance * distancePercent));
    }
}

void DatePickerColumnPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void DatePickerColumnPattern::UpdateFinishToss(double offsetY)
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

void DatePickerColumnPattern::TossStoped()
{
    yOffset_ = 0.0;
    yLast_ = 0.0;
    ScrollOption(0.0);
}

void DatePickerColumnPattern::TossAnimationStoped()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    yLast_ = 0.0;
}

int32_t DatePickerColumnPattern::CalcScrollIndex(
    int32_t totalOptionCount, int32_t currentIndex, bool canLoop, int32_t step)
{
    int32_t nextIndex = currentIndex;
    if (!canLoop) {
        // scroll down
        if (step > 0) {
            nextIndex = (currentIndex + step) > (totalOptionCount - 1) ? totalOptionCount - 1 : currentIndex + step;
            // scroll up
        } else if (step < 0) {
            nextIndex = currentIndex + step < 0 ? 0 : currentIndex + step;
        }
    } else {
        if (totalOptionCount != 0) {
            nextIndex = (totalOptionCount + currentIndex + step) % totalOptionCount;
        }
    }
    return nextIndex;
}

float DatePickerColumnPattern::GetShiftDistance(uint32_t index, DatePickerScrollDirection dir)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    uint32_t optionCounts = theme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    uint32_t nextIndex = 0;
    float distance = 0.0f;
    float val = 0.0f;
    auto isDown = dir == DatePickerScrollDirection::DOWN;
    if (optionCounts == 0) {
        return distance;
    }
    if (isDown) {
        nextIndex = (optionCounts + index + 1) % optionCounts; // index add one
    } else {
        nextIndex = (optionCounts + index - 1) % optionCounts; // index reduce one
    }
    switch (static_cast<DatePickerOptionIndex>(index)) {
        case DatePickerOptionIndex::COLUMN_INDEX_0: // first
            distance = (dir == DatePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_1:
            distance = (dir == DatePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_2:
            if (dir == DatePickerScrollDirection::UP) {
                distance = -optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                          MIDDLE_CHILD_INDEX;
                distance = std::ceil(val);
            }
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_3:
            val = (optionProperties_[index].height - optionProperties_[nextIndex].fontheight) / MIDDLE_CHILD_INDEX +
                  optionProperties_[nextIndex].height;
            distance = (dir == DatePickerScrollDirection::DOWN) ? val : (0.0f - val);
            distance = std::floor(distance);
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_4:
            if (dir == DatePickerScrollDirection::DOWN) {
                distance = optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                          MIDDLE_CHILD_INDEX;
                distance = std::ceil(0.0f - val);
            }
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_5:
            distance = (dir == DatePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_6: // last
            distance = (dir == DatePickerScrollDirection::DOWN) ? optionProperties_[index].height
                                                                : (0.0f - optionProperties_[index].height);
            break;
        default:
            break;
    }
    return distance;
}

float DatePickerColumnPattern::GetShiftDistanceForLandscape(uint32_t index, DatePickerScrollDirection dir)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 0.0f);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, 0.0f);
    uint32_t optionCounts = theme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    uint32_t nextIndex = 0;
    float distance = 0.0f;
    float val = 0.0f;
    auto isDown = dir == DatePickerScrollDirection::DOWN;
    if (optionCounts == 0) {
        return distance;
    }
    if (isDown) {
        nextIndex = (optionCounts + index + 1) % optionCounts; // index add one
    } else {
        nextIndex = (optionCounts + index - 1) % optionCounts; // index reduce one
    }

    switch (static_cast<DatePickerOptionIndex>(index)) {
        case DatePickerOptionIndex::COLUMN_INDEX_0: // first

            if (dir == DatePickerScrollDirection::UP) {
                distance = 0.0f - optionProperties_[index].height;
            } else {
                distance = optionProperties_[index].height +
                           (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) /
                               MIDDLE_CHILD_INDEX;
            }
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_1:
            val = (optionProperties_[index].height - optionProperties_[nextIndex].fontheight) / MIDDLE_CHILD_INDEX +
                  optionProperties_[nextIndex].height;
            distance = (dir == DatePickerScrollDirection::DOWN) ? val : (0.0f - val);
            distance = std::floor(distance);
            break;
        case DatePickerOptionIndex::COLUMN_INDEX_2: // last
            if (dir == DatePickerScrollDirection::DOWN) {
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

void DatePickerColumnPattern::SetOptionShiftDistance()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    uint32_t itemCounts = theme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    bool isLanscape = itemCounts == OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER;
    for (uint32_t i = 0; i < itemCounts; i++) {
        DatePickerOptionProperty& prop = optionProperties_[i];
        if (isLanscape) {
            prop.prevDistance = GetShiftDistanceForLandscape(i, DatePickerScrollDirection::UP);
            prop.nextDistance = GetShiftDistanceForLandscape(i, DatePickerScrollDirection::DOWN);
        } else {
            prop.prevDistance = GetShiftDistance(i, DatePickerScrollDirection::UP);
            prop.nextDistance = GetShiftDistance(i, DatePickerScrollDirection::DOWN);
        }
    }
}

void DatePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
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
    DatePickerScrollDirection dir = dragDelta > 0.0 ? DatePickerScrollDirection::DOWN : DatePickerScrollDirection::UP;
    auto shiftDistance = (dir == DatePickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                                : optionProperties_[midIndex].nextDistance;
    // the abs of drag delta is less than jump interval.
    dragDelta = dragDelta + yOffset_;
    if (GreatOrEqual(std::abs(dragDelta), std::abs(shiftDistance))) {
        InnerHandleScroll(LessNotEqual(dragDelta, 0.0), true, false);
        dragDelta = dragDelta % static_cast<int>(std::abs(shiftDistance));
    }
    // update selected option
    ScrollOption(dragDelta);
    offsetCurSet_ = dragDelta;
    yOffset_ = dragDelta;
}

void DatePickerColumnPattern::ShiftOptionProp(RefPtr<FrameNode> curNode, RefPtr<FrameNode> shiftNode)
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

bool DatePickerColumnPattern::CanMove(bool isDown) const
{
    CHECK_NULL_RETURN(NotLoopOptions(), true);
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

void DatePickerColumnPattern::SetAccessibilityAction()
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

RefPtr<ClickEvent> DatePickerColumnPattern::CreateItemClickEventListener(RefPtr<DatePickerEventParam> param)
{
    auto clickEventHandler = [param, weak = WeakClaim(this)](const GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        pattern->OnAroundButtonClick(param);
    };
    auto listener = AceType::MakeRefPtr<NG::ClickEvent>(clickEventHandler);
    return listener;
}

void DatePickerColumnPattern::OnAroundButtonClick(RefPtr<DatePickerEventParam> param)
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

void DatePickerColumnPattern::PlayRestAnimation()
{
    DatePickerScrollDirection dir =
        scrollDelta_ > 0.0 ? DatePickerScrollDirection::DOWN : DatePickerScrollDirection::UP;
    uint32_t middleIndex = GetShowCount() / 2;
    double shiftDistance = (dir == DatePickerScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                                  : optionProperties_[middleIndex].nextDistance;
    double shiftThreshold = shiftDistance / 2;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == DatePickerScrollDirection::UP ? -1 : 1);
    }

    CreateAnimation(scrollDelta_, 0.0);
}

DimensionRect DatePickerColumnPattern::CalculateHotZone(
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

void DatePickerColumnPattern::AddHotZoneRectToText()
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
