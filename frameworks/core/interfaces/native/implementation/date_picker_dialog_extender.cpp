/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "frameworks/core/interfaces/native/implementation/date_picker_dialog_extender.h"

#include <functional>
#include <utility>

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_date_picker_dialog.h"
#endif

namespace OHOS::Ace::NG {
namespace Converter {
template<>
CheckboxSettingData Convert(const Ark_LunarSwitchStyle& src)
{
    CheckboxSettingData dst;
    dst.selectedColor = OptConvert<Color>(src.selectedColor);
    dst.unselectedColor = OptConvert<Color>(src.unselectedColor);
    dst.strokeColor = OptConvert<Color>(src.strokeColor);
    return dst;
}
} // namespace Converter

namespace DatePickerDialogExtender {
std::optional<PickerDate> ProcessBindableDateSelected(const Opt_Union_Date_Bindable_Date& value)
{
    std::optional<PickerDate> result;
    Converter::VisitUnion(
        value,
        [&result](const Ark_Date& src) { result = Converter::OptConvert<PickerDate>(src); },
        [&result](const Ark_Bindable_Date& src) {
            result = Converter::OptConvert<PickerDate>(src.value);
            // Implement callback functionality
        },
        [] {});
    return result;
}
std::optional<PickerTime> ProcessBindableTimeSelected(const Opt_Union_Date_Bindable_Date& value)
{
    std::optional<PickerTime> result;
    Converter::VisitUnion(
        value,
        [&result](const Ark_Date& src) { result = Converter::OptConvert<PickerTime>(src); },
        [&result](const Ark_Bindable_Date& src) {
            result = Converter::OptConvert<PickerTime>(src.value);
            // Implement callback functionality
        },
        [] {});
    return result;
}

bool ParseDates(const Ark_DatePickerDialogOptions& options, PickerDialogInfo& dialogInfo)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, false);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, false);
    // parse start and end date
    auto parseStartDate = pickerTheme->GetDefaultStartDate();
    auto parseEndDate = pickerTheme->GetDefaultEndDate();
    auto start = Converter::OptConvert<PickerDate>(options.start);
    if (start) {
        parseStartDate = start.value();
    }
    auto end = Converter::OptConvert<PickerDate>(options.end);
    if (end) {
        parseEndDate = end.value();
    }
    if (parseStartDate.ToDays() > parseEndDate.ToDays()) {
        parseStartDate = pickerTheme->GetDefaultStartDate();
        parseEndDate = pickerTheme->GetDefaultEndDate();
    }
    dialogInfo.parseStartDate = parseStartDate;
    dialogInfo.parseEndDate = parseEndDate;
    // parse selected date and time
    auto selectedDate = ProcessBindableDateSelected(options.selected);
    auto selectedTime = ProcessBindableTimeSelected(options.selected);
    if (selectedDate) {
        dialogInfo.isSelectedDate = true;
        dialogInfo.parseSelectedDate = selectedDate.value();
        if (selectedTime) {
            dialogInfo.pickerTime = selectedTime.value();
        }
    }
    return true;
}

PickerDialogInfo BuildDatePickerDialogInfo(const Ark_DatePickerDialogOptions& options)
{
    PickerDialogInfo dialogInfo;
    auto datesParsed = ParseDates(options, dialogInfo);
    if (!datesParsed) {
        return dialogInfo;
    }

    auto alignment = Converter::OptConvert<DialogAlignment>(options.alignment);
    if (alignment) {
        dialogInfo.alignment = alignment.value();
    }
    auto offset = Converter::OptConvert<DimensionOffset>(options.offset);
    if (offset) {
        dialogInfo.offset = offset.value();
    }
    auto blurStyle = Converter::OptConvert<BlurStyle>(options.backgroundBlurStyle);
    if (blurStyle.has_value()) {
        dialogInfo.backgroundBlurStyle = static_cast<int32_t>(blurStyle.value());
    }
    dialogInfo.blurStyleOption = Converter::OptConvert<BlurStyleOption>(options.backgroundBlurStyleOptions);
    dialogInfo.effectOption = Converter::OptConvert<EffectOption>(options.backgroundEffect);
    dialogInfo.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogInfo.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogInfo.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    auto enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode);
    if (enableHoverMode.has_value()) {
        dialogInfo.enableHoverMode = enableHoverMode.value();
    }
    dialogInfo.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    return dialogInfo;
}

void ParseDateInfo(const Ark_DatePickerDialogOptions& options, DatePickerSettingData& settingData)
{
    auto start = Converter::OptConvert<PickerDate>(options.start);
    if (start) {
        settingData.datePickerProperty["start"] = *start;
    }
    auto end = Converter::OptConvert<PickerDate>(options.end);
    if (end) {
        settingData.datePickerProperty["end"] = *end;
    }
    auto selectedDate = ProcessBindableDateSelected(options.selected);
    auto selectedTime = ProcessBindableTimeSelected(options.selected);
    if (selectedDate) {
        settingData.datePickerProperty["selected"] = *selectedDate;
        if (selectedTime) {
            settingData.timePickerProperty["selected"] = *selectedTime;
        }
    }
}

DatePickerSettingData BuildSettingData(const Ark_DatePickerDialogOptions& options)
{
    DatePickerSettingData settingData;
    settingData.isLunar = Converter::OptConvert<bool>(options.lunar).value_or(settingData.isLunar);
    settingData.lunarswitch = Converter::OptConvert<bool>(options.lunarSwitch).value_or(settingData.lunarswitch);
    auto checkboxSettingData = Converter::OptConvert<CheckboxSettingData>(options.lunarSwitchStyle);
    if (checkboxSettingData) {
        settingData.checkboxSettingData = *checkboxSettingData;
    }
    ParseDateInfo(options, settingData);
    settingData.showTime = Converter::OptConvert<bool>(options.showTime).value_or(settingData.showTime);
    settingData.useMilitary = Converter::OptConvert<bool>(options.useMilitaryTime).value_or(settingData.useMilitary);
    auto dateTimeOptions = Converter::OptConvert<DateTimeType>(options.dateTimeOptions);
    if (dateTimeOptions) {
        settingData.dateTimeOptions = *dateTimeOptions;
    }
    auto disappearTextStyle = Converter::OptConvert<PickerTextStyle>(options.disappearTextStyle);
    if (disappearTextStyle) {
        settingData.properties.disappearTextStyle_ = *disappearTextStyle;
    }
    auto textStyle = Converter::OptConvert<PickerTextStyle>(options.textStyle);
    if (textStyle) {
        settingData.properties.normalTextStyle_ = *textStyle;
    }
    auto selectedTextStyle = Converter::OptConvert<PickerTextStyle>(options.selectedTextStyle);
    if (selectedTextStyle) {
        settingData.properties.selectedTextStyle_ = *selectedTextStyle;
    }
    auto pickerMode = Converter::OptConvert<DatePickerMode>(options.mode);
    if (pickerMode) {
        settingData.mode = *pickerMode;
    }
    settingData.isEnableHapticFeedback = true;
    auto enableHapticFeedback = Converter::OptConvert<bool>(options.enableHapticFeedback);
    if (enableHapticFeedback) {
        settingData.isEnableHapticFeedback = enableHapticFeedback.value();
    }
    return settingData;
}

PickerDialogEvent BuildPickerDialogEvents(const Ark_DatePickerDialogOptions& options)
{
    PickerDialogEvent dialogEvent;
    auto didAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogEvent.onDidAppear = onDidAppear;
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogEvent.onDidDisappear = onDidDisappear;
    }
    auto willAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogEvent.onWillAppear = onWillAppear;
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogEvent.onWillDisappear = onWillDisappear;
    }
    return dialogEvent;
}

std::optional<Ark_Date> ProcessDateStr(const std::string info)
{
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(info);
    CHECK_NULL_RETURN(argsPtr, std::nullopt);
    const auto year = argsPtr->GetValue("year")->GetInt();
    const auto month = argsPtr->GetValue("month")->GetInt() + 1; // 0-11 means 1 to 12 months
    const auto day = argsPtr->GetValue("day")->GetInt();

    PickerDateTime dateTime;
    dateTime.SetDate(PickerDate(year, month, day));
    dateTime.SetTime(PickerTime::Current());
    auto result = Converter::ArkValue<Ark_Date>(dateTime.ToString(true));
    return result;
}

PickerDialogInteractiveEvent BuildSelectInteractiveEvents(const Ark_DatePickerDialogOptions& arkOptions)
{
    PickerDialogInteractiveEvent events;
    // onCancel
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        events.cancelEvent = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
    }
    // onDateAccept
    auto dateAcceptCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onDateAccept);
    if (dateAcceptCallbackOpt) {
        events.dateAcceptEvent = [arkCallback = CallbackHelper(*dateAcceptCallbackOpt)](
                                     const std::string& info) -> void {
            auto result = ProcessDateStr(info);
            if (result) {
                arkCallback.Invoke(result.value());
            }
        };
    }
    // onDateChange
    auto dateChangeCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onDateChange);
    if (dateChangeCallbackOpt) {
        events.dateChangeEvent = [arkCallback = CallbackHelper(*dateChangeCallbackOpt)](
                                     const std::string& info) -> void {
            auto result = ProcessDateStr(info);
            if (result) {
                arkCallback.Invoke(result.value());
            }
        };
    }
    return events;
}

std::vector<ButtonInfo> BuildButtonInfos(const Ark_DatePickerDialogOptions& options)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonInfo = Converter::OptConvert<ButtonInfo>(options.acceptButtonStyle);
    if (acceptButtonInfo.has_value()) {
        buttonInfos.emplace_back(acceptButtonInfo.value());
        buttonInfos[0].isAcceptButton = true;
    } else {
        ButtonInfo buttonInfo;
        buttonInfos.emplace_back(buttonInfo);
    }
    auto cancelButtonInfo = Converter::OptConvert<ButtonInfo>(options.cancelButtonStyle);
    if (cancelButtonInfo.has_value()) {
        buttonInfos.emplace_back(cancelButtonInfo.value());
    }
    return buttonInfos;
}

void Show(const Ark_DatePickerDialogOptions* options)
{
    CHECK_NULL_VOID(options);
    PickerDialogInfo dialogInfo = BuildDatePickerDialogInfo(*options);
    DatePickerSettingData settingData = BuildSettingData(*options);
    PickerDialogInteractiveEvent interEvents = BuildSelectInteractiveEvents(*options);
    DatePickerType pickType = DATE;
    PickerDialogEvent datePickerDialogEvent = BuildPickerDialogEvents(*options);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(*options);
#ifndef ARKUI_CAPI_UNITTEST
    DatePickerDialogModel::GetInstance()->SetDatePickerDialogShow(dialogInfo, settingData,
        std::move(interEvents.cancelEvent), std::move(interEvents.acceptEvent), std::move(interEvents.changeEvent),
        std::move(interEvents.dateAcceptEvent), std::move(interEvents.dateChangeEvent), pickType, datePickerDialogEvent,
        buttonInfos);
#else
    MockDatePickerDialog::Show(dialogInfo, settingData);
#endif
}
} // namespace DatePickerDialogExtender
} // namespace OHOS::Ace::NG
