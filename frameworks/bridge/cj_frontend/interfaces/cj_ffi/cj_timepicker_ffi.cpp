/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_timepicker_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "bridge/common/utils/utils.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/picker/datepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
constexpr char TIMEPICKER_OPTIONS_NUMERIC_VAL[] = "numeric";
constexpr char TIMEPICKER_OPTIONS_TWO_DIGIT_VAL[] = "2-digit";

FFiTimePickerResult TimePickerChangeEventToFfi(const DatePickerChangeEvent& eventInfo)
{
    FFiTimePickerResult result;
    auto infoStr = eventInfo.GetSelectedStr();
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(eventInfo.GetSelectedStr());
    if (!argsPtr) {
        LOGW("selectedStr is not exist.");
        return result;
    }
    const auto hour = argsPtr->GetValue("hour")->GetInt();
    const auto minute = argsPtr->GetValue("minute")->GetInt();
    const auto second = argsPtr->GetValue("second")->GetInt();

    result.hour = hour;
    result.minute = minute;
    result.second = second;

    return result;
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

std::vector<ButtonInfo> ParseButtonStyles(const NativeTimePickerDialogOptions& options)
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

FfiTime GetFfiTime(const std::string& date)
{
    auto json = JsonUtil::ParseJsonString(date);
    if (!json || json->IsNull()) {
        return FfiTime();
    }

    FfiTime dateTime {};
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

std::map<std::string, NG::DialogEvent> ChangeDialogEvent(const NativeTimePickerDialogOptions& options)
{
    std::map<std::string, NG::DialogEvent> dialogEvent;
    if (options.onChange.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto changeId = [func = CJLambda::Create(options.onChange.value), node = targetNode](const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
        dialogEvent["changeId"] = changeId;
    }
    if (options.onAccept.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto acceptId = [func = CJLambda::Create(options.onAccept.value), node = targetNode](const std::string& info) {
            PipelineContext::SetCallBackNode(node);
            auto date = GetFfiTime(info);
            func(date);
        };
        dialogEvent["acceptId"] = acceptId;
    }
    return dialogEvent;
}

std::map<std::string, NG::DialogGestureEvent> DialogCancelEvent(const NativeTimePickerDialogOptions& options)
{
    std::map<std::string, NG::DialogGestureEvent> dialogCancelEvent;
    if (options.onCancel.hasValue) {
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto cancelId = [func = CJLambda::Create(options.onCancel.value), node = targetNode](
                            const GestureEvent& /*info*/) {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogCancelEvent["cancelId"] = cancelId;
    }
    return dialogCancelEvent;
}

void AppearDialogEvent(
    const NativeTimePickerDialogOptions& options, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidAppear.hasValue) {
        auto didAppearId = [func = CJLambda::Create(options.onDidAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["didAppearId"] = didAppearId;
    }

    if (options.onWillAppear.hasValue) {
        auto willAppearId = [func = CJLambda::Create(options.onWillAppear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["willAppearId"] = willAppearId;
    }
}

void DisappearDialogEvent(
    const NativeTimePickerDialogOptions& options, std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent)
{
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    if (options.onDidDisappear.hasValue) {
        auto didDisappearId = [func = CJLambda::Create(options.onDidDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["didDisappearId"] = didDisappearId;
    }

    if (options.onWillDisappear.hasValue) {
        auto willDisappearId = [func = CJLambda::Create(options.onWillDisappear.value), node = targetNode]() {
            PipelineContext::SetCallBackNode(node);
            func();
        };
        dialogLifeCycleEvent["willDisappearId"] = willDisappearId;
    }
}

std::map<std::string, NG::DialogCancelEvent> LifeCycleDialogEvent(const NativeTimePickerDialogOptions& options)
{
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    AppearDialogEvent(options, dialogLifeCycleEvent);
    DisappearDialogEvent(options, dialogLifeCycleEvent);
    return dialogLifeCycleEvent;
}

PickerDate ParseDate(const FfiTime& date)
{
    auto pickerDate = PickerDate();
    pickerDate.SetYear(date.year);
    pickerDate.SetMonth(date.month);
    pickerDate.SetDay(date.day);
    return pickerDate;
}

PickerTime ParseTime(const FfiTime& date)
{
    auto pickerTime = PickerTime();
    pickerTime.SetHour(date.hour);
    pickerTime.SetMinute(date.min);
    pickerTime.SetSecond(date.sec);
    return pickerTime;
}

void ParseTimePickerOptions(const NativeTimePickerDialogOptions& options, NG::TimePickerSettingData& settingData)
{
    // Parse format
    bool showSecond = false;
    auto displayedFormat = static_cast<TimePickerFormat>(options.format);
    if (displayedFormat == TimePickerFormat::HOUR_MINUTE_SECOND) {
        showSecond = true;
    }
    settingData.showSecond = showSecond;
    // Parse useMilitaryTime
    settingData.isUseMilitaryTime = options.useMilitaryTime;
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

void ParseTextStyle(NativePickerTextStyle value, NG::PickerTextStyle& textStyle, const std::string& pos)
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

// Parse selectedTextStyle, textStyle, disappearTextStyle
void ParseTextProperties(const NativeTimePickerDialogOptions& options, NG::PickerTextProperties& result)
{
    auto disappearProperty = options.disappearTextStyle;
    auto normalProperty = options.textStyle;
    auto selectedProperty = options.selectedTextStyle;
    ParseTextStyle(disappearProperty, result.disappearTextStyle_, "disappearTextStyle");
    ParseTextStyle(normalProperty, result.normalTextStyle_, "textStyle");
    ParseTextStyle(selectedProperty, result.selectedTextStyle_, "selectedTextStyle");
}

void ParseTimePickerDialogOptions(const NativeTimePickerDialogOptions& options, DialogProperties& dialogProps)
{
    // Parse alignment
    dialogProps.alignment = static_cast<DialogAlignment>(options.alignment);
    // Parse offset
    auto offset = options.offset;
    CalcDimension dx = CalcDimension(offset.dx.value, DimensionUnit(offset.dx.unitType));
    CalcDimension dy = CalcDimension(offset.dy.value, DimensionUnit(offset.dy.unitType));
    dialogProps.offset = DimensionOffset(dx, dy);
    // Parse maskRect
    NativeRectangle nativeRectangle = options.maskRect;
    Dimension xDimen = Dimension(nativeRectangle.x, static_cast<DimensionUnit>(nativeRectangle.xUnit));
    Dimension yDimen = Dimension(nativeRectangle.y, static_cast<DimensionUnit>(nativeRectangle.yUnit));
    Dimension widthDimen = Dimension(nativeRectangle.width, static_cast<DimensionUnit>(nativeRectangle.widthUnit));
    Dimension heightDimen = Dimension(nativeRectangle.height, static_cast<DimensionUnit>(nativeRectangle.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    dialogProps.maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);
    // Parse backgroundBlurStyle
    auto blurStyle = options.backgroundBlurStyle;
    if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
        blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
        dialogProps.backgroundBlurStyle = blurStyle;
    }
    // Parse backgroundColor
    dialogProps.backgroundColor = Color(options.backgroundColor);
    // Parse shadow
    if (options.shadow.hasValue) {
        dialogProps.shadow = ParseNativeShadowOptions(options.shadow.value);
    }
}

// Parse dateTimeOptions
void ParseDateTimeOptions(const NativeTimePickerDialogOptions& options, DateTimeType& dateTimeOptions)
{
    auto convertToZeroPrefixType = [](const char* type) -> ZeroPrefixType {
        if (type == nullptr) {
            return ZeroPrefixType::AUTO;
        }
        if (strcmp(type, TIMEPICKER_OPTIONS_TWO_DIGIT_VAL) == 0) {
            return ZeroPrefixType::SHOW;
        }
        if (strcmp(type, TIMEPICKER_OPTIONS_NUMERIC_VAL) == 0) {
            return ZeroPrefixType::HIDE;
        }
        return ZeroPrefixType::AUTO;
    };

    if (options.dateTimeOptions.hasValue) {
        ZeroPrefixType hourPrefixType = convertToZeroPrefixType(options.dateTimeOptions.hour);
        ZeroPrefixType minutePrefixType = convertToZeroPrefixType(options.dateTimeOptions.min);
        dateTimeOptions.hourType = hourPrefixType;
        dateTimeOptions.minuteType = minutePrefixType;
        dateTimeOptions.secondType = ZeroPrefixType::AUTO;
    }
}

void TimePickerDialogShow(const NativeTimePickerDialogOptions& options,
    const std::map<std::string, NG::DialogEvent>& dialogEvent,
    const std::map<std::string, NG::DialogGestureEvent>& dialogCancelEvent,
    const std::map<std::string, NG::DialogCancelEvent>& dialogLifeCycleEvent,
    const std::vector<ButtonInfo>& buttonInfos)
{
    auto container = Container::Current();
    if (!container) {
        return;
    }
    auto pipelineContext = AccessibilityManager::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    if (!pipelineContext) {
        return;
    }
    auto executor = pipelineContext->GetTaskExecutor();
    if (!executor) {
        return;
    }
    auto theme = GetTheme<DialogTheme>();
    CHECK_NULL_VOID(theme);
    NG::TimePickerSettingData settingData;
    DialogProperties properties;
    // Parse selected
    std::map<std::string, PickerTime> timePickerProperty;
    PickerDate dialogTitleDate = ParseDate(options.selected);
    if (dialogTitleDate.GetYear() != 0) {
        settingData.dialogTitleDate = dialogTitleDate;
        timePickerProperty["selected"] = ParseTime(options.selected);
    }
    ParseTimePickerOptions(options, settingData);
    ParseTextProperties(options, settingData.properties);
    properties.customStyle = false;
    properties.offset = DimensionOffset(Offset(0, -theme->GetMarginBottom().ConvertToPx()));
    ParseTimePickerDialogOptions(options, properties);
    ParseDateTimeOptions(options, settingData.dateTimeOptions);
    auto context = AccessibilityManager::DynamicCast<NG::PipelineContext>(pipelineContext);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    executor->PostTask(
        [properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowTimeDialog(properties, settingData, timePickerProperty, dialogEvent, dialogCancelEvent,
                dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowTimePicker");
}
} // namespace

extern "C" {
void FfiOHOSAceFrameworkTimePickerSetDefaultAttributes(void)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;
    auto selectedStyle = theme->GetOptionStyle(true, false);
    textStyle.textColor = selectedStyle.GetTextColor();
    textStyle.fontSize = selectedStyle.GetFontSize();
    textStyle.fontWeight = selectedStyle.GetFontWeight();
    TimePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);

    auto disappearStyle = theme->GetDisappearOptionStyle();
    textStyle.textColor = disappearStyle.GetTextColor();
    textStyle.fontSize = disappearStyle.GetFontSize();
    textStyle.fontWeight = disappearStyle.GetFontWeight();
    TimePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);

    auto normalStyle = theme->GetOptionStyle(false, false);
    textStyle.textColor = normalStyle.GetTextColor();
    textStyle.fontSize = normalStyle.GetFontSize();
    textStyle.fontWeight = normalStyle.GetFontWeight();
    TimePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTimePickerCreate(FfiTime selected, int32_t format)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);

    PickerTime selectedTime(selected.hour, selected.min, selected.sec);

    bool showSecond = (format == static_cast<int32_t>(TimePickerFormat::HOUR_MINUTE_SECOND));

    TimePickerModel::GetInstance()->CreateTimePicker(theme, showSecond);
    TimePickerModel::GetInstance()->SetSelectedTime(selectedTime);
    FfiOHOSAceFrameworkTimePickerSetDefaultAttributes();
}

void FfiOHOSAceFrameworkTimePickerSetUseMilitaryTime(bool value)
{
    TimePickerModel::GetInstance()->SetHour24(value);
}

void FfiOHOSAceFrameworkTimePickerSetDisappearTextStyle(NativePickerTextStyle value)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(value.color);
    CalcDimension fontSize = CalcDimension(value.size, DimensionUnit(value.unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = value.weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = value.family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(value.style);

    TimePickerModel::GetInstance()->SetDisappearTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTimePickerSetTextStyle(NativePickerTextStyle value)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(value.color);
    CalcDimension fontSize = CalcDimension(value.size, DimensionUnit(value.unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = value.weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = value.family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(value.style);

    TimePickerModel::GetInstance()->SetNormalTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTimePickerSetSelectedTextStyle(NativePickerTextStyle value)
{
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    NG::PickerTextStyle textStyle;

    textStyle.textColor = Color(value.color);
    CalcDimension fontSize = CalcDimension(value.size, DimensionUnit(value.unit));
    textStyle.fontSize = fontSize;

    std::string weightVal = value.weight;
    textStyle.fontWeight = ConvertStrToFontWeight(weightVal);

    std::string familyVal = value.family;
    textStyle.fontFamily = ConvertStrToFontFamilies(familyVal);
    textStyle.fontStyle = static_cast<FontStyle>(value.style);

    TimePickerModel::GetInstance()->SetSelectedTextStyle(theme, textStyle);
}

void FfiOHOSAceFrameworkTimePickerSetLoop(bool value)
{
    TimePickerModel::GetInstance()->SetWheelModeEnabled(value);
}

void FfiOHOSAceFrameworkTimePickerSetEnableHapticFeedback(bool enable)
{
    TimePickerModel::GetInstance()->SetIsEnableHapticFeedback(enable);
}

void FfiOHOSAceFrameworkTimePickerDateTimeOptions(const char* hourType, const char* minuteType, const char* secondType)
{
    auto convertToZeroPrefixType = [](const char* type) -> ZeroPrefixType {
        if (type == nullptr) {
            return ZeroPrefixType::AUTO;
        }
        if (strcmp(type, TIMEPICKER_OPTIONS_TWO_DIGIT_VAL) == 0) {
            return ZeroPrefixType::SHOW;
        }
        if (strcmp(type, TIMEPICKER_OPTIONS_NUMERIC_VAL) == 0) {
            return ZeroPrefixType::HIDE;
        }
        return ZeroPrefixType::AUTO;
    };

    ZeroPrefixType hourPrefixType = convertToZeroPrefixType(hourType);
    ZeroPrefixType minutePrefixType = convertToZeroPrefixType(minuteType);
    ZeroPrefixType secondPrefixType = convertToZeroPrefixType(secondType);

    TimePickerModel::GetInstance()->SetDateTimeOptions(hourPrefixType, minutePrefixType, secondPrefixType);
}

void FfiOHOSAceFrameworkTimePickerSetOnChange(void (*callback)(int64_t hour, int64_t minute, int64_t second))
{
    auto onChange = [lambda = CJLambda::Create(callback)](const BaseEventInfo* index) -> void {
        auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(index);
        const auto infoResult = TimePickerChangeEventToFfi(*eventInfo);
        lambda(infoResult.hour, infoResult.minute, infoResult.second);
    };
    auto* getInstance = NG::ViewStackProcessor::GetInstance();

    CHECK_NULL_VOID(getInstance);
    auto getMainFrameNode = getInstance->GetMainFrameNode();
    CHECK_NULL_VOID(getMainFrameNode);

    TimePickerModel::GetInstance()->SetOnChange(std::move(onChange));
}

void FfiOHOSAceFrameworkTimePickerDialogShow(NativeTimePickerDialogOptions options)
{
    auto buttonInfos = ParseButtonStyles(options);
    auto dialogEvent = ChangeDialogEvent(options);
    auto dialogCancelEvent = DialogCancelEvent(options);
    auto dialogLifeCycleEvent = LifeCycleDialogEvent(options);
    TimePickerDialogShow(options, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
}
}
