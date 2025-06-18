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
#include "core/components_ng/pattern/picker_utils/toss_animation_controller.h"
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
constexpr char MEASURE_SIZE_STRING[] = "TEST";
constexpr float FONTWEIGHT = 0.5f;
constexpr int32_t BUFFER_NODE_NUMBER = 2;
constexpr uint32_t NEXT_COLOUM_DIFF = 1;
} // namespace

void DatePickerColumnPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
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
        PickerOptionProperty prop;
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

void DatePickerColumnPattern::InitHapticController(const RefPtr<FrameNode>& host)
{
    if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    
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

void DatePickerColumnPattern::UpdateTextAreaPadding(
    const RefPtr<PickerTheme>& pickerTheme, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (useButtonFocusArea_) {
        auto padding = pickerTheme->GetSelectorItemSpace();
        PaddingProperty defaultPadding = { CalcLength(padding), CalcLength(padding), CalcLength(0.0_vp),
            CalcLength(0.0_vp), CalcLength(0.0_vp), CalcLength(0.0_vp) };
        textLayoutProperty->UpdatePadding(defaultPadding);
    }
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
    bool isDown, bool isUpateTextContentOnly, bool isUpdateAnimationProperties, bool isTossPlaying)
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
    dataPickerLayoutProperty->UpdatePadding(PaddingProperty { .left = CalcLength(PADDING_WEIGHT, DimensionUnit::PX),
        .right = CalcLength(),
        .top = CalcLength(),
        .bottom = CalcLength(),
        .start = CalcLength(),
        .end = CalcLength() });
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
    bool isLoop_ = dataPickerRowLayoutProperty->GetCanLoopValue(true);
    auto actualOptionCount = showOptionCount < child.size() ? showOptionCount : child.size();
    for (uint32_t index = 0; index < actualOptionCount; index++) {
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
        if ((NotLoopOptions() || !isLoop_) && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent(u"");
            if (!isTossPlaying) {
                textNode->MarkModifyDone();
                textNode->MarkDirtyNode();
            }
            continue;
        }
        auto date = datePickerPattern->GetAllOptions(host)[optionIndex];
        auto optionValue = DatePickerPattern::GetFormatString(date);
        textLayoutProperty->UpdateContent(optionValue);
        textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        if (!isTossPlaying) {
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode();
        }
    }
    if (isUpateTextContentOnly && isUpdateAnimationProperties) {
        FlushAnimationTextProperties(isDown);
    }
}

void DatePickerColumnPattern::UpdatePickerTextProperties(uint32_t index, uint32_t showOptionCount,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<DataPickerRowLayoutProperty>& dataPickerRowLayoutProperty)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
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
    const RefPtr<PickerLayoutProperty>& pickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    PickerColumnPattern::UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, pickerLayoutProperty);
}

void DatePickerColumnPattern::UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<PickerLayoutProperty>& pickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    PickerColumnPattern::UpdateCandidateTextProperties(pickerTheme, textLayoutProperty, pickerLayoutProperty);
}

void DatePickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<PickerLayoutProperty>& pickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    PickerColumnPattern::UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, pickerLayoutProperty);
}

void DatePickerColumnPattern::SetDividerHeight(uint32_t showOptionCount)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    gradientHeight_ = static_cast<float>(pickerTheme->GetGradientHeight().Value() * TEXT_HEIGHT_NUMBER);
    dividerHeight_ = static_cast<float>(
        gradientHeight_ + pickerTheme->GetDividerSpacing().Value() + pickerTheme->GetGradientHeight().Value());
    dividerSpacingWidth_ = static_cast<float>(pickerTheme->GetDividerSpacing().Value() * TEXT_WEIGHT_NUMBER);
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

void DatePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    int32_t dragDelta = offsetY - yLast_;
    yLast_ = offsetY;
    PickerScrollDirection dir = dragDelta > 0.0 ? PickerScrollDirection::DOWN : PickerScrollDirection::UP;
    if (!CanMove(LessNotEqual(static_cast<double>(dragDelta), 0.0))) {
        auto currentIndex = GetCurrentIndex();
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto options = GetOptions();
        auto it = options.find(host);
        CHECK_NULL_VOID(it != options.end());
        auto totalCount = options[host].size();
        if ((currentIndex == 0 && dir == PickerScrollDirection::DOWN && GreatOrEqual(yOffset_, 0.0)) ||
            (currentIndex == totalCount - 1 && dir == PickerScrollDirection::UP && LessOrEqual(yOffset_, 0.0))) {
            return;
        }
    }
    if (hapticController_ && isShow_) {
        if (isEnableHaptic_ && !stopHaptic_ && !isHapticPlayOnce_) {
            hapticController_->HandleDelta(dragDelta);
        }
    }
    offsetCurSet_ = 0.0;
    auto midIndex = GetShowCount() / 2;
    auto shiftDistance = (dir == PickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                            : optionProperties_[midIndex].nextDistance;
    // the abs of drag delta is less than jump interval.
    dragDelta = dragDelta + yOffset_;
    bool isJump = GreatOrEqual(static_cast<double>(std::abs(dragDelta)), std::abs(shiftDistance));
    if (isJump) {
        InnerHandleScroll(LessNotEqual(dragDelta, 0.0), true, false);
        dragDelta %= (static_cast<int32_t>(shiftDistance) != 0 ? static_cast<int32_t>(shiftDistance) : 1);
        if (!NearZero(static_cast<double>(dragDelta)) && !CanMove(LessNotEqual(static_cast<double>(dragDelta), 0.0))) {
            dragDelta = 0;
            if (hapticController_) {
                hapticController_->Stop();
            }
        }
    }

    // update selected option
    ScrollOption(dragDelta);
    offsetCurSet_ = dragDelta;
    yOffset_ = dragDelta;
}

bool DatePickerColumnPattern::CanMove(bool isDown) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    bool canLoop = GetCanLoopFromLayoutProperty();
    // When CanLoop is true and NotLoopOptions is false(which means LoopOptions are satisfied), CanMove returns true;
    // otherwise, validate the index legality.
    if (canLoop && !NotLoopOptions()) {
        return true;
    }
    int totalOptionCount = static_cast<int>(GetOptionCount());

    auto datePickerColumnPattern = host->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(datePickerColumnPattern, false);
    int currentIndex = static_cast<int>(datePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

void DatePickerColumnPattern::UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme)
{
    UpdateAnimationColor(pickerTheme);

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
    auto dataPickerRowLayoutProperty = parentNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(dataPickerRowLayoutProperty);

    auto&& child = host->GetChildren();
    auto iter = child.begin();
    CHECK_NULL_VOID(iter != child.end());
    std::advance(iter, GetShowCount() / PICKER_SELECT_AVERAGE);
    CHECK_NULL_VOID(iter != child.end());
    auto textNode = DynamicCast<FrameNode>(*iter);
    CHECK_NULL_VOID(textNode);
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, dataPickerRowLayoutProperty);
    textNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    host->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
}

void DatePickerColumnPattern::UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    Color color;

    if (pickerTheme->IsCircleDial() && !isUserSetSelectColor_) {
        if (selectedMarkPaint_) {
            color = pickerTheme->GetOptionStyle(true, true).GetTextColor();
        } else {
            color = pickerTheme->GetOptionStyle(false, false).GetTextColor();
        }
    } else {
        color = layoutProperty->GetSelectedColor().value_or(
            pickerTheme->GetOptionStyle(true, false).GetTextColor());
    }

    uint32_t middleIndex = GetShowCount() / PICKER_SELECT_AVERAGE;
    if (middleIndex - NEXT_COLOUM_DIFF >= 0 && animationProperties_.size() > middleIndex) {
        animationProperties_[middleIndex - NEXT_COLOUM_DIFF].downColor = color;
        animationProperties_[middleIndex + NEXT_COLOUM_DIFF].upColor = color;
        animationProperties_[middleIndex].currentColor = color;
    }
}

uint32_t DatePickerColumnPattern::GetOptionCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto options = GetOptions();
    auto totalOptionCount = options[host].size();
    CHECK_NULL_RETURN(totalOptionCount, 0);
    return static_cast<uint32_t>(totalOptionCount);
}

bool DatePickerColumnPattern::GetOptionItemCount(uint32_t& itemCounts)
{
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, false);
    itemCounts = theme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    return true;
}

bool DatePickerColumnPattern::IsLanscape(uint32_t itemCount)
{
    return (itemCount == OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER);
}

bool DatePickerColumnPattern::GetCanLoopFromLayoutProperty() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(blendNode, false);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, false);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, false);
    auto dataPickerRowLayoutProperty = parentNode->GetLayoutProperty<DataPickerRowLayoutProperty>();
    return dataPickerRowLayoutProperty->GetCanLoopValue(true);
}

bool DatePickerColumnPattern::IsTossNeedToStop()
{
    return !GetCanLoopFromLayoutProperty();
}

std::string DatePickerColumnPattern::GetCurrentOption() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, "");
    auto pattern = frameNode->GetPattern<DatePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto index = pattern->GetCurrentIndex();
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        if (it->second.size() <= index) {
            return "";
        }
        auto date = it->second.at(index);
        return DatePickerPattern::GetFormatString(date);
    }
    return "";
}
} // namespace OHOS::Ace::NG
