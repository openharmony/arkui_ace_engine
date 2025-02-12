/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_datepicker_ffi.h"


#include "cj_lambda.h"
#include "bridge/common/utils/utils.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components/picker/picker_data.h"
#include "core/components/picker/picker_date_component.h"
#include "core/components/picker/picker_theme.h"
#include "core/components/picker/picker_time_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/ace_event_helper.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
std::unique_ptr<DatePickerDialogModel> DatePickerDialogModel::datePickerDialogInstance_ = nullptr;
std::unique_ptr<TimePickerModel> TimePickerModel::timePickerInstance_ = nullptr;

DatePickerDialogModel* DatePickerDialogModel::GetInstance()
{
    std::call_once(onceFlag_, []() { datePickerDialogInstance_.reset(new NG::DatePickerDialogModelNG()); });

    return datePickerDialogInstance_.get();
}

TimePickerModel* TimePickerModel::GetInstance()
{
    std::call_once(onceFlag_, []() { timePickerInstance_.reset(new NG::TimePickerModelNG()); });

    return timePickerInstance_.get();
}
} // namespace OHOS::Ace

namespace {
const int MAX_YEAR = 2100;
const int MIN_YEAR = 1900;
const DimensionOffset DATEPICKER_OFFSET_DEFAULT_TOP = DimensionOffset(0.0_vp, 40.0_vp);
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::string TIMEPICKER_OPTIONS_NUMERIC_VAL = "numeric";
const std::string TIMEPICKER_OPTIONS_TWO_DIGIT_VAL = "2-digit";

PickerDate ParseDate(FfiTime data)
{
    auto pickerDate = PickerDate();
    pickerDate.SetYear(data.year);
    pickerDate.SetMonth(data.month);
    pickerDate.SetDay(data.day);

    return pickerDate;
}

PickerTime ParseTime(FfiTime data)
{
    auto pickerTime = PickerTime();
    pickerTime.SetHour(data.hour);
    pickerTime.SetMinute(data.min);
    pickerTime.SetSecond(data.sec);

    return pickerTime;
}

FFiDatePickerResult DatePickerChangeEventToFfi(const DatePickerChangeEvent& eventInfo)
{
    FFiDatePickerResult result;
    auto infoStr = eventInfo.GetSelectedStr();
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo.GetSelectedStr());
    if (!argsPtr) {
        LOGW("selectedStr is not exist.");
        return result;
    }
    const auto year = argsPtr->GetValue("year")->GetInt();
    const auto month = argsPtr->GetValue("month")->GetInt() + 1; // 0-11 means 1 to 12 months
    const auto day = argsPtr->GetValue("day")->GetInt();

    result.year = year;
    result.month = month;
    result.day = day;

    return result;
}

void IsUserDefinedFontFamily(const std::string& pos)
{
    if (pos == "disappearTextStyle") {
        DatePickerModel::GetInstance()->HasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyle") {
        DatePickerModel::GetInstance()->HasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyle") {
        DatePickerModel::GetInstance()->HasUserDefinedSelectedFontFamily(true);
    } else if (pos == "disappearTextStyleTime") {
        TimePickerModel::GetInstance()->HasUserDefinedDisappearFontFamily(true);
    } else if (pos == "textStyleTime") {
        TimePickerModel::GetInstance()->HasUserDefinedNormalFontFamily(true);
    } else if (pos == "selectedTextStyleTime") {
        TimePickerModel::GetInstance()->HasUserDefinedSelectedFontFamily(true);
    }
}

void ParseDateTimeOptions(const NativeDateDialogOptions& options, DateTimeType& dateTimeOptions)
{
    dateTimeOptions.hourType = ZeroPrefixType::AUTO;
    dateTimeOptions.minuteType = ZeroPrefixType::AUTO;
    dateTimeOptions.secondType = ZeroPrefixType::AUTO;

    std::string hour = std::string(options.dateTimeOptions.hour);
    if (std::string() == TIMEPICKER_OPTIONS_TWO_DIGIT_VAL) {
        dateTimeOptions.hourType = ZeroPrefixType::SHOW;
    } else if (hour == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
        dateTimeOptions.hourType = ZeroPrefixType::HIDE;
    }
    std::string minute = std::string(options.dateTimeOptions.min);
    if (minute == TIMEPICKER_OPTIONS_NUMERIC_VAL) {
        dateTimeOptions.minuteType = ZeroPrefixType::HIDE;
    }
}

void ParseTextStyle(const NativePickerTextStyle& value, NG::PickerTextStyle& textStyle, const std::string& pos)
{
    textStyle.textColor = Color(value.color);

    if (static_cast<DimensionUnit>(value.unit) == DimensionUnit::PERCENT) {
        textStyle.fontSize = Dimension(-1);
    } else {
        textStyle.fontSize = CalcDimension(value.size, static_cast<DimensionUnit>(value.unit));
    }

    textStyle.fontWeight = ConvertStrToFontWeight(value.weight);
    textStyle.fontFamily = ConvertStrToFontFamilies(std::string(value.family));
    IsUserDefinedFontFamily(pos);
    if (value.style < 0 || value.style > 1) {
        return;
    }
    textStyle.fontStyle = static_cast<FontStyle>(value.style);
}

void ParseTextProperties(const NativeDateDialogOptions& options, NG::PickerTextProperties& result)
{
    if (options.disappearTextStyle.hasValue) {
        ParseTextStyle(options.disappearTextStyle, result.disappearTextStyle_, "disappearTextStyle");
    }

    if (options.textStyle.hasValue) {
        ParseTextStyle(options.textStyle, result.normalTextStyle_, "textStyle");
    }

    if (options.selectedTextSytle.hasValue) {
        ParseTextStyle(options.selectedTextSytle, result.selectedTextStyle_, "selectedTextStyle");
    }
}

void UpdateDatePickerSettingData(const NativeDateDialogOptions& options, NG::DatePickerSettingData& settingData)
{
    settingData.isLunar = options.lunar;
    settingData.lunarswitch = options.lunarSwitch;
    settingData.showTime = options.showTime;
    settingData.useMilitary = options.useMilitaryTime;

    auto datePickerMode = DatePickerMode::DATE;
    settingData.mode = datePickerMode;

    if (options.dateTimeOptions.hasValue) {
        ParseDateTimeOptions(options, settingData.dateTimeOptions);
    }

    ParseTextProperties(options, settingData.properties);
}

void UpdatePickerDialogTimeInfo(const NativeDateDialogOptions& options, PickerDialogInfo& pickerDialog)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    auto startDate = options.start;
    if (startDate.hasValue) {
        pickerDialog.isStartDate = true;
    }

    auto endDate = options.end;
    if (endDate.hasValue) {
        pickerDialog.isEndDate = true;
    }

    auto selectedDate = options.selected;
    if (selectedDate.hasValue) {
        pickerDialog.isSelectedDate = true;
    }

    auto parseStartDate = ParseDate(startDate.value);
    auto parseEndDate = ParseDate(endDate.value);
    if (parseStartDate.GetYear() <= 0) {
        parseStartDate = theme->GetDefaultStartDate();
    }
    if (parseEndDate.GetYear() <= 0) {
        parseEndDate = theme->GetDefaultEndDate();
    }

    auto startDays = parseStartDate.ToDays();
    auto endDays = parseEndDate.ToDays();
    if (startDays > endDays) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
    }
    pickerDialog.parseStartDate = parseStartDate;
    pickerDialog.parseEndDate = parseEndDate;
    pickerDialog.parseSelectedDate = ParseDate(selectedDate.value);
    pickerDialog.pickerTime = ParseTime(selectedDate.value);
}

void UpdatePickerDialogPositionInfo(const NativeDateDialogOptions& options, PickerDialogInfo& pickerDialog)
{
    // parse alignment
    auto alignment = options.alignment;
    if (alignment >= 0 && alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        pickerDialog.alignment = DIALOG_ALIGNMENT[alignment];
    }
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        if (alignment == static_cast<int32_t>(DialogAlignment::TOP) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_START) ||
            alignment == static_cast<int32_t>(DialogAlignment::TOP_END)) {
            pickerDialog.offset = DATEPICKER_OFFSET_DEFAULT_TOP;
        }
    }
    // parse offset
    Dimension dxValue(options.offset.value.dx.value, static_cast<DimensionUnit>(options.offset.value.dx.unitType));
    CalcDimension dx = CalcDimension(dxValue.ConvertToVp(), DimensionUnit::VP);
    Dimension dyValue(options.offset.value.dy.value, static_cast<DimensionUnit>(options.offset.value.dy.unitType));
    CalcDimension dy = CalcDimension(dyValue.ConvertToVp(), DimensionUnit::VP);
    pickerDialog.offset = DimensionOffset(dx, dy);
}

void ParseMaskRect(const NativeOptionRect& maskRect, DimensionRect& result)
{
    result.SetOffset(DimensionOffset(CalcDimension(0, DimensionUnit::VP), CalcDimension(0, DimensionUnit::VP)));
    result.SetSize(DimensionSize(CalcDimension(1, DimensionUnit::PERCENT), CalcDimension(1, DimensionUnit::PERCENT)));
    if (!maskRect.hasValue) {
        return;
    }

    NativeRectangle nativeRectangle = maskRect.value;

    CalcDimension xDimen = CalcDimension(nativeRectangle.x, static_cast<DimensionUnit>(nativeRectangle.xUnit));
    CalcDimension yDimen = CalcDimension(nativeRectangle.y, static_cast<DimensionUnit>(nativeRectangle.yUnit));
    auto offset = result.GetOffset();
    offset.SetX(xDimen);
    offset.SetY(yDimen);
    result.SetOffset(offset);
    CalcDimension widthDimen =
        CalcDimension(nativeRectangle.width, static_cast<DimensionUnit>(nativeRectangle.widthUnit));
    if (widthDimen.Unit() == DimensionUnit::PERCENT && widthDimen.Value() < 0) {
        return;
    }
    result.SetWidth(widthDimen);
    CalcDimension heightDimen =
        CalcDimension(nativeRectangle.height, static_cast<DimensionUnit>(nativeRectangle.heightUnit));
    if (heightDimen.Unit() == DimensionUnit::PERCENT && heightDimen.Value() < 0) {
        return;
    }
    result.SetHeight(heightDimen);
    return;
}

Shadow ParseNativeShadowOptions(NativeShadowOptions shadowOptions)
{
    Shadow shadow;
    if (LessNotEqual(shadowOptions.radius, 0.0)) {
        shadowOptions.radius = 0.0;
    }
    shadow.SetBlurRadius(shadowOptions.radius);
    Color shadowColor = Color(shadowOptions.color);
    shadow.SetColor(shadowColor);
    shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
    shadow.SetIsFilled(shadowOptions.fill);
    shadow.SetOffsetX(shadowOptions.offsetX);
    shadow.SetOffsetY(shadowOptions.offsetY);
    return shadow;
}

void UpdatePickerDialogInfo(const NativeDateDialogOptions& options, PickerDialogInfo& pickerDialog)
{
    UpdatePickerDialogTimeInfo(options, pickerDialog);
    UpdatePickerDialogPositionInfo(options, pickerDialog);
    // Parse maskRect
    DimensionRect maskRect;
    ParseMaskRect(options.maskRect, maskRect);
    pickerDialog.maskRect = maskRect;
    pickerDialog.backgroundColor = Color(options.backgroundColor);
    if (options.backgroundBlurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        options.backgroundBlurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        pickerDialog.backgroundBlurStyle = options.backgroundBlurStyle;
    }
    // Parse shadow
    if (options.shadow.hasValue) {
        pickerDialog.shadow = ParseNativeShadowOptions(options.shadow.value);
    }
}

void ParseFontOfButtonStyle(const NativePickerDialogButtonStyle& buttonStyle, ButtonInfo& buttonInfo)
{
    if (buttonStyle.fontSize.hasValue) {
        CalcDimension fontSize =
            CalcDimension(buttonStyle.fontSize.value.value, DimensionUnit(buttonStyle.fontSize.value.unitType));
        if (fontSize.Unit() != DimensionUnit::PERCENT && GreatNotEqual(fontSize.Value(), 0.0)) {
            buttonInfo.fontSize = fontSize;
        }
    }
    if (buttonStyle.fontColor.hasValue) {
        buttonInfo.fontColor = Color(buttonStyle.fontColor.value);
    }
    if (buttonStyle.fontStyle.hasValue) {
        buttonInfo.fontWeight = ConvertStrToFontWeight(buttonStyle.fontWeight.value);
    }
    if (buttonStyle.fontStyle.hasValue) {
        auto style = buttonStyle.fontStyle.value;
        if (style >= 0 && style < static_cast<int32_t>(FontStyle::NONE)) {
            buttonInfo.fontStyle = static_cast<FontStyle>(style);
        }
    }
    if (buttonStyle.fontFamily.hasValue) {
        buttonInfo.fontFamily = ConvertStrToFontFamilies(buttonStyle.fontFamily.value);
    }
}

NG::BorderRadiusProperty ParseNativeBorderRadiuses(const NativeBorderRadiuses& nativeBorderRadiuses)
{
    NG::BorderRadiusProperty radius;
    CalcDimension topLeft(
        nativeBorderRadiuses.topLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topLeftUnit));
    CalcDimension topRight(
        nativeBorderRadiuses.topRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.topRightUnit));
    CalcDimension bottomLeft(
        nativeBorderRadiuses.bottomLeftRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomLeftUnit));
    CalcDimension bottomRight(
        nativeBorderRadiuses.bottomRightRadiuses, static_cast<DimensionUnit>(nativeBorderRadiuses.bottomRightUnit));
    radius.radiusTopLeft = topLeft;
    radius.radiusTopRight = topRight;
    radius.radiusBottomLeft = bottomLeft;
    radius.radiusBottomRight = bottomRight;
    radius.multiValued = true;
    return radius;
}

ButtonInfo ParseButtonStyle(const NativePickerDialogButtonStyle& buttonStyle)
{
    ButtonInfo buttonInfo;
    if (buttonStyle.type.hasValue) {
        int32_t buttonTypeIntValue = buttonStyle.type.value;
        if (buttonTypeIntValue == static_cast<int32_t>(ButtonType::CAPSULE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::CIRCLE) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ARC) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::NORMAL) ||
            buttonTypeIntValue == static_cast<int32_t>(ButtonType::ROUNDED_RECTANGLE)) {
            buttonInfo.type = static_cast<ButtonType>(buttonTypeIntValue);
        }
    }
    if (buttonStyle.style.hasValue) {
        int32_t styleModeIntValue = buttonStyle.style.value;
        if (styleModeIntValue >= static_cast<int32_t>(ButtonStyleMode::NORMAL) &&
            styleModeIntValue <= static_cast<int32_t>(ButtonStyleMode::TEXT)) {
            buttonInfo.buttonStyle = static_cast<ButtonStyleMode>(styleModeIntValue);
        }
    }
    if (buttonStyle.role.hasValue) {
        int32_t buttonRoleIntValue = buttonStyle.style.value;
        if (buttonRoleIntValue >= static_cast<int32_t>(ButtonRole::NORMAL) &&
            buttonRoleIntValue <= static_cast<int32_t>(ButtonRole::ERROR)) {
            buttonInfo.role = static_cast<ButtonRole>(buttonRoleIntValue);
        }
    }
    ParseFontOfButtonStyle(buttonStyle, buttonInfo);
    if (buttonStyle.backgroundColor.hasValue) {
        buttonInfo.backgroundColor = Color(buttonStyle.backgroundColor.value);
    }
    if (buttonStyle.borderRadius.hasValue) {
        buttonInfo.borderRadius = ParseNativeBorderRadiuses(buttonStyle.borderRadius.value);
    }
    if (buttonStyle.primary.hasValue) {
        buttonInfo.isPrimary = buttonStyle.primary.value;
    }
    return buttonInfo;
}

std::vector<ButtonInfo> ParseButtonStyles(const NativeDateDialogOptions& options)
{
    std::vector<ButtonInfo> buttonInfos;
    if (options.acceptButtonStyle.hasValue) {
        buttonInfos.emplace_back(ParseButtonStyle(options.acceptButtonStyle.value));
        buttonInfos[0].isAcceptButton = true;
    } else {
        buttonInfos.emplace_back(ButtonInfo());
    }
    if (options.cancelButtonStyle.hasValue) {
        buttonInfos.emplace_back(ParseButtonStyle(options.cancelButtonStyle.value));
    }
    return buttonInfos;
}

void DatePickerDialogAppearEvent(const NativeDateDialogOptions& options, PickerDialogEvent& pickerDialogEvent)
{
    std::function<void()> didAppearEvent;
    std::function<void()> willAppearEvent;

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidAppear.hasValue) {
        didAppearEvent = [func = CJLambda::Create(options.onDidAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
    }

    if (options.onWillAppear.hasValue) {
        willAppearEvent = [func = CJLambda::Create(options.onWillAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
    }
    pickerDialogEvent.onDidAppear = std::move(didAppearEvent);
    pickerDialogEvent.onWillAppear = std::move(willAppearEvent);
}

void DatePickerDialogDisappearEvent(const NativeDateDialogOptions& options, PickerDialogEvent& pickerDialogEvent)
{
    std::function<void()> didDisappearEvent;
    std::function<void()> willDisappearEvent;

    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidDisappear.hasValue) {
        didDisappearEvent = [func = CJLambda::Create(options.onDidDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
    }

    if (options.onWillDisappear.hasValue) {
        willDisappearEvent = [func = CJLambda::Create(options.onWillDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
    }

    pickerDialogEvent.onDidDisappear = std::move(didDisappearEvent);
    pickerDialogEvent.onWillDisappear = std::move(willDisappearEvent);
}

std::function<void()> GetCancelEvent(const NativeDateDialogOptions& options, const WeakPtr<NG::FrameNode>& frameNode)
{
    std::function<void()> cancelEvent;
    if (options.onCancel.hasValue) {
        cancelEvent = [func = CJLambda::Create(options.onCancel.value), node = frameNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
    }
    return cancelEvent;
}

FfiTime GetFfiTime(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return FfiTime();
    }

    FfiTime dateTime {};
    auto year = json->GetValue("year");
    if (year && year->IsNumber()) {
        dateTime.year = year->GetInt(); // local date start from 1900
    }
    auto month = json->GetValue("month");
    if (month && month->IsNumber()) {
        dateTime.month = month->GetInt() + 1;
    }
    auto day = json->GetValue("day");
    if (day && day->IsNumber()) {
        dateTime.day = day->GetInt();
    }
    auto hour = json->GetValue("hour");
    if (hour && hour->IsNumber()) {
        dateTime.hour = hour->GetInt();
    }
    auto min = json->GetValue("minute");
    if (min && min->IsNumber()) {
        dateTime.min = min->GetInt();
    }
    auto sec = json->GetValue("second");
    if (sec && sec->IsNumber()) {
        dateTime.sec = sec->GetInt();
    }
    return dateTime;
}

std::function<void(const std::string&)> GetDateChangeEvent(
    const NativeDateDialogOptions& options, const DatePickerType& pickerType, const WeakPtr<NG::FrameNode>& frameNode)
{
    std::function<void(const std::string&)> dateChangeEvent;
    if (options.onChange.hasValue) {
        dateChangeEvent = [type = pickerType, func = CJLambda::Create(options.onChange.value), node = frameNode](
                              const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
    }
    return dateChangeEvent;
}

std::function<void(const std::string&)> GetDateAcceptEvent(
    const NativeDateDialogOptions& options, const DatePickerType& pickerType, const WeakPtr<NG::FrameNode>& frameNode)
{
    std::function<void(const std::string&)> dateAcceptEvent;
    if (options.onAccept.hasValue) {
        dateAcceptEvent = [type = pickerType, func = CJLambda::Create(options.onAccept.value), node = frameNode](
                              const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
    }
    return dateAcceptEvent;
}
} // namespace

extern "C" {
void ConvertToNoramlDate(PickerDate& date)
{
    auto theme = GetTheme<PickerTheme>();
    if (date.GetYear() < MIN_YEAR) {
        date = theme->GetDefaultStartDate();
    }
    if (date.GetYear() > MAX_YEAR) {
        date = theme->GetDefaultEndDate();
    }
}

void FfiOHOSAceFrameworkDatePickerCreate(FfiTime startDate, FfiTime endDate, FfiTime selectedDate)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto parseStartDate = ParseDate(startDate);
    auto parseEndDate = ParseDate(endDate);
    auto parseSelectedDate = ParseDate(selectedDate);

    ConvertToNoramlDate(parseStartDate);
    ConvertToNoramlDate(parseEndDate);
    ConvertToNoramlDate(parseSelectedDate);

    auto startDays = parseStartDate.ToDays();
    auto endDays = parseEndDate.ToDays();
    auto selectedDays = parseSelectedDate.ToDays();
    if (startDays > endDays) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
        startDays = parseStartDate.ToDays();
        endDays = parseEndDate.ToDays();
    }
    if (selectedDays > endDays) {
        parseSelectedDate = parseEndDate;
    }
    if (selectedDays < startDays) {
        parseSelectedDate = parseStartDate;
    }

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(parseStartDate);
    DatePickerModel::GetInstance()->SetEndDate(parseEndDate);
    DatePickerModel::GetInstance()->SetSelectedDate(parseSelectedDate);
    FfiOHOSAceFrameworkDatePickerSetDefaultAttributes();
}

// create with changeEvent
void FfiOHOSAceFrameworkDatePickerCreateWithChangeEvent(
    FfiTime startDate, FfiTime endDate, FfiTime selectedDate, void (*callback)(FfiTime selectedDate))
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto parseStartDate = ParseDate(startDate);
    auto parseEndDate = ParseDate(endDate);
    auto parseSelectedDate = ParseDate(selectedDate);

    ConvertToNoramlDate(parseStartDate);
    ConvertToNoramlDate(parseEndDate);
    ConvertToNoramlDate(parseSelectedDate);

    auto startDays = parseStartDate.ToDays();
    auto endDays = parseEndDate.ToDays();
    auto selectedDays = parseSelectedDate.ToDays();
    if (startDays > endDays) {
        parseStartDate = theme->GetDefaultStartDate();
        parseEndDate = theme->GetDefaultEndDate();
        startDays = parseStartDate.ToDays();
        endDays = parseEndDate.ToDays();
    }
    if (selectedDays > endDays) {
        parseSelectedDate = parseEndDate;
    }
    if (selectedDays < startDays) {
        parseSelectedDate = parseStartDate;
    }

    DatePickerModel::GetInstance()->CreateDatePicker(theme);
    DatePickerModel::GetInstance()->SetStartDate(parseStartDate);
    DatePickerModel::GetInstance()->SetEndDate(parseEndDate);
    DatePickerModel::GetInstance()->SetSelectedDate(parseSelectedDate);

    auto changeEvent = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = DatePickerChangeEventToFfi(*eventInfo);
        lambda(FfiTime { infoResult.year, infoResult.month, infoResult.day });
    };
    DatePickerModel::GetInstance()->SetChangeEvent(std::move(changeEvent));

    FfiOHOSAceFrameworkDatePickerSetDefaultAttributes();
}

void FfiOHOSAceFrameworkDatePickerSetLunar(bool isLunar)
{
    DatePickerModel::GetInstance()->SetShowLunar(isLunar);
}

void FfiOHOSAceFrameworkDatePickerUseMilitaryTime(bool isUseMilitaryTime)
{
    DatePickerModel::GetInstance()->SetHour24(isUseMilitaryTime);
}

void FfiOHOSAceFrameworkDatePickerSetOnChange(void (*callback)(int64_t year, int64_t month, int64_t day))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = DatePickerChangeEventToFfi(*eventInfo);
        lambda(infoResult.year, infoResult.month, infoResult.day);
    };
    auto* getInstance = NG::ViewStackProcessor::GetInstance();

    CHECK_NULL_VOID(getInstance);
    auto getMainFrameNode = getInstance->GetMainFrameNode();
    CHECK_NULL_VOID(getMainFrameNode);

    DatePickerModel::GetInstance()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkDatePickerSetOnDateChange(void (*callback)(int64_t year, int64_t month, int64_t day))
{
    auto onDateChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = DatePickerChangeEventToFfi(*eventInfo);
        lambda(infoResult.year, infoResult.month, infoResult.day);
    };
    auto* getInstance = NG::ViewStackProcessor::GetInstance();

    CHECK_NULL_VOID(getInstance);
    auto getMainFrameNode = getInstance->GetMainFrameNode();
    CHECK_NULL_VOID(getMainFrameNode);

    DatePickerModel::GetInstance()->SetOnDateChange(std::move(onDateChange));
}

void FfiOHOSAceFrameworkDatePickerSetDefaultAttributes(void)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetBackgroundColor(uint32_t color)
{
    DatePickerModel::GetInstance()->SetBackgroundColor(Color(color));
}

void FfiOHOSAceFrameworkDatePickerSetDisappearTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetSelectedTextStyle(
    uint32_t color, double size, int32_t unit, const char* weight, const char* family, uint32_t style)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(color);
    CalcDimension fontSize = CalcDimension(size, DimensionUnit(unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(style);

    DatePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkDatePickerSetOpacity(double opacity)
{
    ViewAbstractModel::GetInstance()->SetOpacity(opacity);
    DatePickerModel::GetInstance()->HasUserDefinedOpacity();
}

void FfiOHOSAceFrameworkDatePickerDialogShow(NativeDateDialogOptions options)
{
    DatePickerType pickerType = DatePickerType::DATE;
    std::function<void()> cancelEvent;
    std::function<void(const std::string&)> acceptEvent;
    std::function<void(const std::string&)> changeEvent;
    std::function<void(const std::string&)> dateChangeEvent;
    std::function<void(const std::string&)> dateAcceptEvent;
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelEvent = GetCancelEvent(options, frameNode);
    dateChangeEvent = GetDateChangeEvent(options, pickerType, frameNode);
    dateAcceptEvent = GetDateAcceptEvent(options, pickerType, frameNode);
    NG::DatePickerSettingData settingData;
    UpdateDatePickerSettingData(options, settingData);
    PickerDialogInfo pickerDialog;
    UpdatePickerDialogInfo(options, pickerDialog);

    auto buttonInfos = ParseButtonStyles(options);
    PickerDialogEvent pickerDialogEvent { nullptr, nullptr, nullptr, nullptr };

    DatePickerDialogAppearEvent(options, pickerDialogEvent);
    DatePickerDialogDisappearEvent(options, pickerDialogEvent);
    DatePickerDialogModel::GetInstance()->SetDatePickerDialogShow(pickerDialog, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(dateAcceptEvent), std::move(dateChangeEvent),
        pickerType, pickerDialogEvent, buttonInfos);
}
}
