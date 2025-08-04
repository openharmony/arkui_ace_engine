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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/components/dialog/dialog_theme.h"
#include "core/components_ng/pattern/picker/datepicker_dialog_view.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DatePickerDialogAccessor {
void BuildDialogPropertiesCallbacks(const Ark_DatePickerDialogOptions options, DialogProperties& dialogProps)
{
    auto didAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidAppear = onDidAppear;
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidDisappear = onDidDisappear;
    }
    auto willAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillAppear = onWillAppear;
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillDisappear = onWillDisappear;
    }
}
DialogProperties BuildDialogProperties(const Ark_DatePickerDialogOptions options)
{
    DialogProperties dialogProps;
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, dialogProps);
    auto dialogTheme = pipeline->GetTheme<DialogTheme>();
    CHECK_NULL_RETURN(dialogTheme, dialogProps);

    dialogProps.alignment = dialogTheme->GetAlignment();
    if (dialogProps.alignment == DialogAlignment::BOTTOM) {
        dialogProps.offset = DimensionOffset(Offset(0, -dialogTheme->GetMarginBottom().ConvertToPx()));
    }
    dialogProps.customStyle = false;
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        options.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    dialogProps.enableHoverMode =
        Converter::OptConvert<bool>(options.enableHoverMode).value_or(dialogProps.enableHoverMode.value_or(false));
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    BuildDialogPropertiesCallbacks(options, dialogProps);
    return dialogProps;
}
DatePickerSettingData BuildSettingData(const Ark_DatePickerDialogOptions options)
{
    DatePickerSettingData settingData;
    settingData.isLunar = Converter::OptConvert<bool>(options.lunar).value_or(settingData.isLunar);
    settingData.lunarswitch = Converter::OptConvert<bool>(options.lunarSwitch).value_or(settingData.lunarswitch);
    auto checkboxSettingData = Converter::OptConvert<CheckboxSettingData>(options.lunarSwitchStyle);
    if (checkboxSettingData) {
        settingData.checkboxSettingData = *checkboxSettingData;
    }
    auto start = Converter::OptConvert<PickerDate>(options.start);
    if (start) {
        settingData.datePickerProperty["start"] = *start;
    }
    auto end = Converter::OptConvert<PickerDate>(options.end);
    if (end) {
        settingData.datePickerProperty["end"] = *end;
    }
    auto selectedDate = Converter::OptConvert<PickerDate>(options.selected);
    auto selectedTime = Converter::OptConvert<PickerTime>(options.selected);
    if (selectedDate) {
        settingData.datePickerProperty["selected"] = *selectedDate;
        if (selectedTime) {
            settingData.timePickerProperty["selected"] = *selectedTime;
        }
    }
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
    return settingData;
}
std::vector<ButtonInfo> BuildButtonInfos(const Ark_DatePickerDialogOptions options)
{
    std::vector<ButtonInfo> buttonInfos;
    auto acceptButtonInfo = Converter::OptConvert<ButtonInfo>(options.acceptButtonStyle);
    if (acceptButtonInfo.has_value()) {
        buttonInfos.push_back(acceptButtonInfo.value());
    }
    auto cancelButtonInfo = Converter::OptConvert<ButtonInfo>(options.cancelButtonStyle);
    if (cancelButtonInfo.has_value()) {
        buttonInfos.push_back(cancelButtonInfo.value());
    }
    return buttonInfos;
}
std::map<std::string, DialogEvent> CreateDialogEvent(const Ark_DatePickerDialogOptions options)
{
    std::map<std::string, DialogEvent> dialogEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_DatePickerResult_Void>(options.onAccept);
    if (acceptCallbackOpt) {
        auto onAcceptFunc = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_DatePickerResult>(info);
            arkCallback.Invoke(result);
        };
        dialogEvent["acceptId"] = onAcceptFunc;
    }
    auto changeCallbackOpt = Converter::OptConvert<Callback_DatePickerResult_Void>(options.onChange);
    if (changeCallbackOpt) {
        auto onChangeFunc = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_DatePickerResult>(info);
            arkCallback.Invoke(result);
        };
        dialogEvent["changeId"] = onChangeFunc;
    }
    auto dateAcceptCallbackOpt = Converter::OptConvert<Callback_Date_Void>(options.onDateAccept);
    if (dateAcceptCallbackOpt) {
        auto onDateAcceptFunc = [arkCallback = CallbackHelper(*dateAcceptCallbackOpt)](
                                    const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_Date>(info);
            arkCallback.Invoke(result);
        };
        dialogEvent["dateAcceptId"] = onDateAcceptFunc;
    }
    auto dateChangeCallbackOpt = Converter::OptConvert<Callback_Date_Void>(options.onDateChange);
    if (dateChangeCallbackOpt) {
        auto onDateChangeFunc = [arkCallback = CallbackHelper(*dateChangeCallbackOpt)](
                                    const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_Date>(info);
            arkCallback.Invoke(result);
        };
        dialogEvent["dateChangeId"] = onDateChangeFunc;
    }
    return dialogEvent;
}
void ShowImpl(const Opt_DatePickerDialogOptions* options)
{
#ifndef ARKUI_WEARABLE
    CHECK_NULL_VOID(options);
    auto arkOptionsOpt = Converter::OptConvert<Ark_DatePickerDialogOptions>(*options);
    if (!arkOptionsOpt.has_value()) { return; }

    Ark_DatePickerDialogOptions arkOptions = *arkOptionsOpt;
    DialogProperties dialogProps = BuildDialogProperties(arkOptions);
    DatePickerSettingData settingData = BuildSettingData(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);
    std::map<std::string, DialogEvent> dialogEvent = CreateDialogEvent(arkOptions);
    std::map<std::string, DialogGestureEvent> dialogCancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        auto onCancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)](const GestureEvent& info) -> void {
            arkCallback.Invoke();
        };
        dialogCancelEvent["cancelId"] = onCancelFunc;
    }
    DatePickerDialogView::Show(dialogProps, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
#endif
}
} // DatePickerDialogAccessor
const GENERATED_ArkUIDatePickerDialogAccessor* GetDatePickerDialogAccessor()
{
    static const GENERATED_ArkUIDatePickerDialogAccessor DatePickerDialogAccessorImpl {
        DatePickerDialogAccessor::ShowImpl,
    };
    return &DatePickerDialogAccessorImpl;
}

}
