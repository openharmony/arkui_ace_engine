/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/pattern/time_picker/bridge/timepicker_util.h"

#include <string>

#include "interfaces/inner_api/ace_kit/include/ui/base/geometry/dimension.h"
#include "interfaces/inner_api/ace_kit/include/ui/gestures/gesture_event.h"

#include "bridge/arkts_frontend/koala_projects/arkoala-arkts/framework/native/src/generated/arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/timepicker_column_pattern.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"
#include "core/interfaces/arkoala/arkoala_api.h"
namespace OHOS::Ace::NG::TimePickerUtil {
namespace {
#define MODIFIER_COUNTS 1
const std::string COLON = ":";
const Dimension& FONT_SIZE_LIMIT = 0.0_vp;
const bool IS_USER_SET_FONT_SIZE = false;
} // namespace
std::string GetShowTimePickerText(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, "");
    auto parentNode = frameNode->GetParentFrameNode();
    CHECK_NULL_RETURN(parentNode, "");
    auto timeNode = AceType::DynamicCast<FrameNode>(parentNode->GetChildAtIndex(1));
    CHECK_NULL_RETURN(timeNode, "");
    auto timePickerRowPattern = timeNode->GetPattern<NG::TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, "");
    auto allChildNode = timePickerRowPattern->GetAllChildNode();
    auto hourColumn = allChildNode["hour"].Upgrade();
    CHECK_NULL_RETURN(hourColumn, "");
    auto hourPickerColumnPattern = hourColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(hourPickerColumnPattern, "");
    auto minuteColumn = allChildNode["minute"].Upgrade();
    CHECK_NULL_RETURN(minuteColumn, "");
    auto minutePickerColumnPattern = minuteColumn->GetPattern<TimePickerColumnPattern>();
    CHECK_NULL_RETURN(minutePickerColumnPattern, "");

    std::string result;
    auto options = timePickerRowPattern->GetOptions();
    if (options.find(hourColumn) != options.end()) {
        std::string hour = options[hourColumn][hourPickerColumnPattern->GetCurrentIndex()];
        result += hour;
    }
    if (options.find(minuteColumn) != options.end()) {
        std::string minute = options[minuteColumn][minutePickerColumnPattern->GetCurrentIndex()];
        result += COLON + minute;
    }
    if (timePickerRowPattern->GetHasSecond()) {
        auto secondColumn = allChildNode["second"].Upgrade();
        CHECK_NULL_RETURN(secondColumn, "");
        auto secondPickerColumnPattern = secondColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(secondPickerColumnPattern, "");
        if (options.find(secondColumn) != options.end()) {
            std::string second = options[secondColumn][secondPickerColumnPattern->GetCurrentIndex()];
            result += COLON + second;
        }
    }
    if (!timePickerRowPattern->GetHour24()) {
        auto amPmColumn = allChildNode["amPm"].Upgrade();
        CHECK_NULL_RETURN(amPmColumn, "");
        auto amPmPickerColumnPattern = amPmColumn->GetPattern<TimePickerColumnPattern>();
        CHECK_NULL_RETURN(amPmPickerColumnPattern, "");
        auto optionIndex = amPmPickerColumnPattern->GetCurrentIndex();
        if (optionIndex >= 0) {
            result = timePickerRowPattern->GetOptionValue(amPmColumn, optionIndex).append(" ") + result;
        }
    }
    return result;
}

std::optional<PickerTime> GetTimepickerCurrentTime(const RefPtr<FrameNode>& frameNode)
{
    std::optional<PickerTime> pickerTime;
    CHECK_NULL_RETURN(frameNode, pickerTime);
    auto pattern = frameNode->GetPattern<TimePickerRowPattern>();
    if (pattern) {
        pickerTime = pattern->GetCurrentTime();
    }
    return pickerTime;
}

bool SetTimepickerFocusDisable(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetFocusDisable();
    return true;
}

bool SetTimepickerFocusEnable(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetFocusEnable();
    return true;
}

bool SetTimepickerRowPatternStopHaptic(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->ColumnPatternStopHaptic();
    return true;
}

bool SetTimeNode(const RefPtr<FrameNode>& timeNode, const DatePickerSettingData& settingData)
{
    CHECK_NULL_RETURN(timeNode, false);
    auto timePickerEventHub = timeNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_RETURN(timePickerEventHub, false);
    auto timePickerRowPattern = timeNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    timePickerRowPattern->SetTextProperties(settingData.properties);
    timePickerRowPattern->SetShowLunarSwitch(settingData.lunarswitch);
    auto timePickerLayout = timeNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(timePickerLayout, false);
    timePickerLayout->UpdateLoop(settingData.canLoop);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        ZeroPrefixType hourOptions = settingData.dateTimeOptions.hourType;
        ZeroPrefixType minuteOptions = settingData.dateTimeOptions.minuteType;
        if ((timePickerRowPattern->GetPrefixHour() != hourOptions) ||
            (timePickerRowPattern->GetPrefixMinute() != minuteOptions)) {
            timePickerRowPattern->SetDateTimeOptionUpdate(true);
        }
        timePickerRowPattern->SetPrefixHour(hourOptions);
        timePickerRowPattern->SetPrefixMinute(minuteOptions);
        timePickerLayout->UpdatePrefixHour(static_cast<int32_t>(hourOptions));
        timePickerLayout->UpdatePrefixMinute(static_cast<int32_t>(minuteOptions));
    }
    return true;
}

bool SetOnChangeForDatePicker(const RefPtr<FrameNode>& frameNode, TimeChangeEventForDatePicker&& changeEvent)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto timePickerEventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_RETURN(timePickerEventHub, false);
    timePickerEventHub->SetOnChangeForDatePicker(std::move(changeEvent));
    return true;
}

bool UpdateVisibility(const RefPtr<FrameNode>& frameNode, const VisibleType& value)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto timePickerLayout = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(timePickerLayout, false);
    timePickerLayout->UpdateVisibility(value);
    return true;
}

bool CreateTimeNode(ElementIdType nodeId, TimePickerNodeInfo& info, bool isEnableHapticFeedback)
{
    auto timePickerNode = FrameNode::GetOrCreateFrameNode(
        TIME_PICKER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerRowPattern>(); });
    CHECK_NULL_RETURN(timePickerNode, false);
    auto timePickerRowPattern = timePickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    uint32_t showCount = pickerTheme->GetShowOptionCount() + TimePickerUtil::BUFFER_NODE_NUMBER;
    timePickerRowPattern->SetShowCount(showCount);
    timePickerRowPattern->SetIsShowInDialog(true);
    timePickerRowPattern->SetIsShowInDatePickerDialog(true);
    timePickerRowPattern->SetIsEnableHaptic(isEnableHapticFeedback);
    info.hasHourNode = timePickerRowPattern->HasHourNode();
    info.hasMinuteNode = timePickerRowPattern->HasMinuteNode();
    info.hourId = timePickerRowPattern->GetHourId();
    info.minuteId = timePickerRowPattern->GetMinuteId();
    info.showCount = showCount;
    info.timePickerNode = std::move(timePickerNode);
    return true;
}

bool SetColumn(const RefPtr<FrameNode>& frameNode, const RefPtr<FrameNode>& columnNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    timePickerRowPattern->SetColumn(columnNode);
    return true;
}

bool SetSelectedTime(const RefPtr<FrameNode>& frameNode, const PickerTime& value)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    timePickerRowPattern->SetSelectedTime(value);
    return true;
}

bool SetHour24(const RefPtr<FrameNode>& frameNode, bool value)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto timePickerRowPattern = frameNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerRowPattern, false);
    timePickerRowPattern->SetHour24(value);
    return true;
}

void CreateTimePickerColumnPattern(ElementIdType nodeId, RefPtr<FrameNode>& columnNode)
{
    columnNode = FrameNode::GetOrCreateFrameNode(
        COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TimePickerColumnPattern>(); });
}

const Dimension ConvertFontSizeLimit(const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    if (isUserSetFont == false) {
        return fontSizeValue;
    }
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto fontScale = pipeline->GetFontScale();
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    if (pipeline->IsFollowSystem() && (!NearZero(maxAppFontScale))) {
        fontScale = std::min(fontScale, maxAppFontScale);
    }
    Dimension fontSizeValueResult = fontSizeValue;
    if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontScale, fontSizeLimit.ConvertToPx())) {
        if (!NearZero(fontScale)) {
            fontSizeValueResult = fontSizeLimit / fontScale;
        }
    }
    return fontSizeValueResult;
}

bool NeedAdaptForAging()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();
    auto follow = pipeline->IsFollowSystem();
    if (GreatOrEqual(pipeline->GetFontScale(), pickerTheme->GetMaxOneFontScale()) &&
        Dimension(pipeline->GetRootHeight()).ConvertToVp() > pickerTheme->GetDeviceHeightLimit() &&
        (follow && (GreatOrEqual(maxAppFontScale, pickerTheme->GetMaxOneFontScale())))) {
        return true;
    }
    return false;
}

const Dimension ConvertFontScaleValue(
    const Dimension& fontSizeValue, const Dimension& fontSizeLimit, bool isUserSetFont)
{
    auto pipeline = PipelineContext::GetCurrentContextPtrSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, fontSizeValue);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, fontSizeValue);
    float fontSizeScale = pipeline->GetFontScale();
    Dimension fontSizeValueResult = fontSizeValue;
    Dimension fontSizeValueResultVp(fontSizeLimit.Value(), DimensionUnit::VP);
    auto maxAppFontScale = pipeline->GetMaxAppFontScale();

    if (fontSizeValue.Unit() == DimensionUnit::VP) {
        return isUserSetFont ? std::min(fontSizeValueResultVp, fontSizeValue) : fontSizeValue;
    }
    if (pipeline->IsFollowSystem() && (!NearZero(maxAppFontScale))) {
        fontSizeScale = std::min(fontSizeScale, maxAppFontScale);
    }
    if (NeedAdaptForAging()) {
        if (isUserSetFont) {
            if (GreatOrEqualCustomPrecision(fontSizeValue.ConvertToPx() * fontSizeScale, fontSizeLimit.ConvertToPx()) &&
                (fontSizeScale != 0.0f)) {
                fontSizeValueResult = fontSizeLimit / fontSizeScale;
            } else {
                fontSizeValueResult = fontSizeValue;
            }
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxThirdFontScale())) {
                fontSizeScale = pickerTheme->GetMaxTwoFontScale() / pickerTheme->GetMaxThirdFontScale();
                fontSizeValueResult = fontSizeValue * fontSizeScale;
            }
        }
    } else {
        if (isUserSetFont) {
            fontSizeValueResult = ConvertFontSizeLimit(fontSizeValueResult, fontSizeLimit, isUserSetFont);
        } else {
            if (GreatOrEqualCustomPrecision(fontSizeScale, pickerTheme->GetMaxOneFontScale()) &&
                (!NearZero(fontSizeScale))) {
                fontSizeValueResult = fontSizeValueResult / fontSizeScale;
            }
        }
    }
    return fontSizeValueResult;
}

void SetTimeTextProperties(const RefPtr<FrameNode>& frameNode, const PickerTextProperties& properties,
    Dimension disappearTextStyleFont, Dimension normalTextStyleFont, Dimension selectedTextStyleFont)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto selectedStyle = pickerTheme->GetOptionStyle(true, false);
    auto disappearStyle = pickerTheme->GetDisappearOptionStyle();
    auto normalStyle = pickerTheme->GetOptionStyle(false, false);
    auto pickerProperty = frameNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_VOID(pickerProperty);
    if (properties.disappearTextStyle_.fontSize.has_value() && properties.disappearTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateDisappearFontSize(
            ConvertFontScaleValue(properties.disappearTextStyle_.fontSize.value(), disappearTextStyleFont, true));
    } else {
        pickerProperty->UpdateDisappearFontSize(
            ConvertFontScaleValue(disappearStyle.GetFontSize(), FONT_SIZE_LIMIT, IS_USER_SET_FONT_SIZE));
    }
    pickerProperty->UpdateDisappearColor(
        properties.disappearTextStyle_.textColor.value_or(disappearStyle.GetTextColor()));
    pickerProperty->UpdateDisappearWeight(
        properties.disappearTextStyle_.fontWeight.value_or(disappearStyle.GetFontWeight()));

    if (properties.normalTextStyle_.fontSize.has_value() && properties.normalTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateFontSize(
            ConvertFontScaleValue(properties.normalTextStyle_.fontSize.value(), normalTextStyleFont, true));
    } else {
        pickerProperty->UpdateFontSize(
            ConvertFontScaleValue(normalStyle.GetFontSize(), FONT_SIZE_LIMIT, IS_USER_SET_FONT_SIZE));
    }
    pickerProperty->UpdateColor(properties.normalTextStyle_.textColor.value_or(normalStyle.GetTextColor()));
    pickerProperty->UpdateWeight(properties.normalTextStyle_.fontWeight.value_or(normalStyle.GetFontWeight()));

    if (properties.selectedTextStyle_.fontSize.has_value() && properties.selectedTextStyle_.fontSize->IsValid()) {
        pickerProperty->UpdateSelectedFontSize(
            ConvertFontScaleValue(properties.selectedTextStyle_.fontSize.value(), selectedTextStyleFont, true));
    } else {
        pickerProperty->UpdateSelectedFontSize(
            ConvertFontScaleValue(selectedStyle.GetFontSize(), FONT_SIZE_LIMIT, IS_USER_SET_FONT_SIZE));
    }
    pickerProperty->UpdateSelectedColor(properties.selectedTextStyle_.textColor.value_or(selectedStyle.GetTextColor()));
    pickerProperty->UpdateSelectedWeight(
        properties.selectedTextStyle_.fontWeight.value_or(selectedStyle.GetFontWeight()));
}

#ifndef ARKUI_WEARABLE
void SetTimePickerDialogViewShow(TimePickerDialogInfo& info, std::map<std::string, PickerTime> timePickerProperty,
    std::map<std::string, NG::DialogEvent> dialogEvent, std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent)
{
    info.timePickerNode = TimePickerDialogView::Show(info.dialogProperties, info.settingData, info.buttonInfos,
        std::move(timePickerProperty), std::move(dialogEvent), std::move(dialogCancelEvent));
}
#endif

const TimepickerCustomModifier* GetTimePickerCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const TimepickerCustomModifier modifier = {
        .getShowTimePickerText = GetShowTimePickerText,
        .getTimepickerCurrentTime = GetTimepickerCurrentTime,
        .setTimepickerFocusDisable = SetTimepickerFocusDisable,
        .setTimepickerFocusEnable = SetTimepickerFocusEnable,
        .setTimepickerRowPatternStopHaptic = SetTimepickerRowPatternStopHaptic,
        .setTimeNode = SetTimeNode,
        .setOnChangeForDatePicker = SetOnChangeForDatePicker,
        .updateVisibility = UpdateVisibility,
        .createTimeNode = CreateTimeNode,
        .setColumn = SetColumn,
        .setSelectedTime = SetSelectedTime,
        .setHour24 = SetHour24,
        .createTimePickerColumnPattern = CreateTimePickerColumnPattern,
        .setTimeTextProperties = SetTimeTextProperties,
#ifndef ARKUI_WEARABLE
        .setTimePickerDialogViewShow = SetTimePickerDialogViewShow,
#else
        .setTimePickerDialogViewShow = nullptr,
#endif
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, MODIFIER_COUNTS, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG::TimePickerUtil