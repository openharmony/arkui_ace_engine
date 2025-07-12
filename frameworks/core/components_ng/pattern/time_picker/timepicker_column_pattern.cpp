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

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
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
const int32_t CHILDREN_SIZE = 3;
const float TEXT_HEIGHT_NUMBER = 3.0f;
const float TEXT_HOUR24_HEIGHT_NUMBER = 9.0f;
const float TEXT_WEIGHT_NUMBER = 6.0f;
constexpr float FONTWEIGHT = 0.5f;
constexpr char MEASURE_SIZE_STRING[] = "TEST";
#ifdef SUPPORT_DIGITAL_CROWN
constexpr char PICKER_DRAG_SCENE[] = "picker_drag_scene";
#endif
const int32_t HALF_NUMBER = 2;
const uint32_t NEXT_COLOUM_DIFF = 1;
const std::string AMPM = "amPm";
} // namespace

void TimePickerColumnPattern::OnModifyDone()
{
    auto host = GetHost();
    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(theme);
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

bool TimePickerColumnPattern::IsStartEndTimeDefined()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(blendNode, false);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, false);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, false);
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    return timePickerRowPattern->IsStartEndTimeDefined();
}

bool TimePickerColumnPattern::IsTossNeedToStop()
{
    return IsStartEndTimeDefined();
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

void TimePickerColumnPattern::ChangeAmPmTextStyle(uint32_t index, uint32_t showOptionCount,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TimePickerLayoutProperty>& timePickerLayoutProperty)
{
    if (showOptionCount != CHILDREN_SIZE) {
        return;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
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
    auto pickerTheme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
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
    if (selectedColumnId_ == AMPM) {
        GetAnimationColor(index, showCount, updateColor);
    }

    textLayoutProperty->UpdateTextColor(updateColor);
    if (scale < FONTWEIGHT) {
        textLayoutProperty->UpdateFontWeight(animationProperties_[index].fontWeight);
    }
}

void TimePickerColumnPattern::HandleEnterSelectedArea(
    double scrollDelta, float shiftDistance, PickerScrollDirection dir)
{
    auto shiftThreshold = shiftDistance / HALF_NUMBER;
    uint32_t currentEnterIndex = GetCurrentIndex();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto options = GetOptions();
    auto totalOptionCount = options[host];
    if (totalOptionCount == 0) {
        return;
    }
    if (dir == PickerScrollDirection::UP) {
        currentEnterIndex = (totalOptionCount + currentEnterIndex + 1) % totalOptionCount;
    } else {
        auto totalCountAndIndex = totalOptionCount + currentEnterIndex;
        currentEnterIndex = (totalCountAndIndex ? totalCountAndIndex - 1 : 0) % totalOptionCount;
    }
    bool isDragReverse = false;
    if (GreatNotEqual(std::abs(enterDelta_), std::abs(scrollDelta))) {
        isDragReverse = true;
    }
    enterDelta_ = (NearEqual(scrollDelta, shiftDistance)) ? 0.0 : scrollDelta;
    if (GreatOrEqual(std::abs(scrollDelta), std::abs(shiftThreshold)) && GetEnterIndex() != currentEnterIndex) {
        SetEnterIndex(currentEnterIndex);
        HandleEnterSelectedAreaEventCallback(true);
    }
    if (isDragReverse && LessOrEqual(std::abs(scrollDelta), std::abs(shiftThreshold)) &&
        GetEnterIndex() != GetCurrentIndex()) {
        SetEnterIndex(GetCurrentIndex());
        HandleEnterSelectedAreaEventCallback(true);
    }
}

void TimePickerColumnPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
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

uint32_t TimePickerColumnPattern::GetOptionCount() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto options = GetOptions();
    auto totalOptionCount = options[host];
    CHECK_NULL_RETURN(totalOptionCount, 0);
    return static_cast<uint32_t>(totalOptionCount);
}

void TimePickerColumnPattern::FlushCurrentOptions(
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
    auto dataPickerLayoutProperty = host->GetLayoutProperty<LinearLayoutProperty>();
    CHECK_NULL_VOID(dataPickerLayoutProperty);
    dataPickerLayoutProperty->UpdatePadding(
        PaddingProperty { .left = CalcLength(static_cast<float>(PADDING_WEIGHT.ConvertToPx()), DimensionUnit::PX),
            .right = CalcLength(),
            .top = CalcLength(),
            .bottom = CalcLength(),
            .start = CalcLength(),
            .end = CalcLength() });
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
        if (!isTossPlaying) {
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode();
        }
    }
}

void TimePickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    CHECK_EQUAL_VOID(isTossReadyToStop_, true);
    int32_t dragDelta = static_cast<int32_t>(std::trunc(offsetY - yLast_));
    yLast_ = offsetY;
    PickerScrollDirection dir = dragDelta > 0 ? PickerScrollDirection::DOWN : PickerScrollDirection::UP;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto options = GetOptions();
    auto it = options.find(host);
    CHECK_NULL_VOID(it != options.end());
    auto totalCount = it->second;
    if (!CanMove(LessNotEqual(static_cast<double>(dragDelta), 0.0))) {
        auto currentIndex = GetCurrentIndex();
        if ((currentIndex == 0 && dir == PickerScrollDirection::DOWN && GreatOrEqual(yOffset_, 0.0)) ||
            (currentIndex == totalCount - 1 && dir == PickerScrollDirection::UP && LessOrEqual(yOffset_, 0.0))) {
            auto toss = GetToss();
            CHECK_NULL_VOID(toss);
            toss->StopTossAnimation();
            return;
        }
    }
    if (hapticController_ && isShow_ && isEnableHaptic_ && !stopHaptic_ && !isHapticPlayOnce_) {
        hapticController_->HandleDelta(static_cast<double>(dragDelta));
    }
    offsetCurSet_ = 0.0;
    auto midIndex = GetShowCount() / 2;
    auto shiftDistance = std::abs((dir == PickerScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                                     : optionProperties_[midIndex].nextDistance);
    // the abs of drag delta is less than jump interval.
    dragDelta += static_cast<int32_t>(std::trunc(yOffset_));
    bool isJump = GreatOrEqual(static_cast<double>(std::abs(dragDelta)), shiftDistance);
    if (isJump) {
        HandleEnterSelectedArea(static_cast<double>(dragDelta), shiftDistance, dir);
        InnerHandleScroll(LessNotEqual(static_cast<double>(dragDelta), 0.0), true);
        dragDelta %= (static_cast<int32_t>(shiftDistance) != 0 ? static_cast<int32_t>(shiftDistance) : 1);
        if (!NearZero(static_cast<double>(dragDelta)) && !CanMove(LessNotEqual(static_cast<double>(dragDelta), 0.0))) {
            dragDelta = 0;
            auto toss = GetToss();
            CHECK_NULL_VOID(toss);
            isTossReadyToStop_ = true;
            toss->StopTossAnimation();
            if (hapticController_) {
                hapticController_->Stop();
            }
        }
    }
    ScrollOption(static_cast<double>(dragDelta), isJump);
    offsetCurSet_ = static_cast<double>(dragDelta);
    yOffset_ = static_cast<double>(dragDelta);
    isTossReadyToStop_ = false;
}

bool TimePickerColumnPattern::CanMove(bool isDown) const
{
    if (wheelModeEnabled_) {
        CHECK_NULL_RETURN(NotLoopOptions(), true);
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    int totalOptionCount = static_cast<int>(GetOptionCount());
    auto timePickerColumnPattern = host->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(timePickerColumnPattern, false);
    int currentIndex = static_cast<int>(timePickerColumnPattern->GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

bool TimePickerColumnPattern::GetCanLoopFromLayoutProperty() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(blendNode, false);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, false);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, false);
    auto layoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetLoopValue(true);
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

void TimePickerColumnPattern::UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme)
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
    auto timePickerLayoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(timePickerLayoutProperty);

    auto&& child = host->GetChildren();
    auto iter = child.begin();
    CHECK_NULL_VOID(iter != child.end());
    std::advance(iter, GetShowCount() / PICKER_SELECT_AVERAGE);
    CHECK_NULL_VOID(iter != child.end());
    auto textNode = DynamicCast<FrameNode>(*iter);
    CHECK_NULL_VOID(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, timePickerLayoutProperty);

    textNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    host->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
}

void TimePickerColumnPattern::GetAnimationColor(uint32_t index, uint32_t showCount, Color& color, bool selectedMark)
{
    CHECK_EQUAL_VOID(index == showCount / PICKER_SELECT_AVERAGE, false);
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (pickerTheme->IsCircleDial() && !isUserSetSelectColor_) {
        if (!selectedMarkPaint_) {
            color = pickerTheme->GetOptionStyle(false, false).GetTextColor();
        } else if (selectedMark) {
            color = pickerTheme->GetOptionStyle(true, false).GetTextColor();
        }
    } else if (selectedMark) {
        color = layoutProperty->GetSelectedColor().value_or(pickerTheme->GetOptionStyle(true, false).GetTextColor());
    }
}

void TimePickerColumnPattern::UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme)
{
    Color color;
    uint32_t showCount = GetShowCount();
    uint32_t middleIndex = showCount / PICKER_SELECT_AVERAGE;
    GetAnimationColor(middleIndex, showCount, color, true);
    if (middleIndex - NEXT_COLOUM_DIFF >= 0 && animationProperties_.size() > middleIndex) {
        animationProperties_[middleIndex - NEXT_COLOUM_DIFF].downColor = color;
        animationProperties_[middleIndex + NEXT_COLOUM_DIFF].upColor = color;
        animationProperties_[middleIndex].currentColor = color;
    }
}

#ifdef SUPPORT_DIGITAL_CROWN
void TimePickerColumnPattern::HandleCrownMoveEvent(const CrownEvent& event)
{
    SetMainVelocity(event.angularVelocity);
    animationBreak_ = false;
    isCrownEventEnded_ = false;
    auto toss = GetToss();
    CHECK_NULL_VOID(toss);
    CHECK_NULL_VOID(circleUtils_);
    auto offsetY = circleUtils_->GetCrownRotatePx(event, GetDigitalCrownSensitivity());
    offsetY += yLast_;
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.angularVelocity, SceneStatus::RUNNING);
}
#endif

std::string TimePickerColumnPattern::GetCurrentOption() const
{
    auto frameNode = GetHost();
    CHECK_NULL_RETURN(frameNode, "");
    auto blendNode = DynamicCast<FrameNode>(frameNode->GetParent());
    CHECK_NULL_RETURN(blendNode, "");
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, "");
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, "");
    auto timePickerRowPattern = parentNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, "");
    auto pattern = frameNode->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(pattern, "");
    auto index = pattern->GetCurrentIndex();
    auto options = pattern->GetOptions();
    auto it = options.find(frameNode);
    if (it != options.end()) {
        if (it->second < index) {
            return "";
        }
        return timePickerRowPattern->GetOptionsValue(frameNode, index);
    }
    return "";
}
} // namespace OHOS::Ace::NG
