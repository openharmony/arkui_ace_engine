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

#include <functional>
#include <utility>

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/picker/picker_model.h"
#include "core/components_ng/pattern/picker/picker_type_define.h"
#include "core/components_ng/pattern/time_picker/timepicker_model.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "frameworks/core/interfaces/native/implementation/time_picker_dialog_extender.h"

namespace OHOS::Ace::NG {
namespace TimePickerDialogExtender {
std::optional<PickerTime> ProcessBindableTimeSelected(const Opt_Union_Date_Bindable& value)
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
std::optional<PickerDate> ProcessBindableDateSelected(const Opt_Union_Date_Bindable& value)
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
PickerDialogInfo BuildTimePickerDialogInfo(const Ark_TimePickerDialogOptions& options)
{
    PickerDialogInfo dialogInfo;

    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, dialogInfo);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto parseStartTime = pickerTheme->GetDefaultStartTime();
    auto parseEndTime = pickerTheme->GetDefaultEndTime();
    // start & end time
    auto start = Converter::OptConvert<PickerTime>(options.start);
    if (start) {
        parseStartTime = start.value();
    }
    auto end = Converter::OptConvert<PickerTime>(options.end);
    if (end) {
        parseEndTime = end.value();
    }
    dialogInfo.parseStartTime = parseStartTime;
    dialogInfo.parseEndTime = parseEndTime;
    // select time
    auto selectedTime = ProcessBindableTimeSelected(options.selected);
    if (selectedTime) {
        dialogInfo.isSelectedTime = true;
        dialogInfo.pickerTime = selectedTime.value();
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
    auto enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode);
    if (enableHoverMode) {
        dialogInfo.enableHoverMode = enableHoverMode.value();
    }
    auto hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    if (hoverModeArea) {
        dialogInfo.hoverModeArea = hoverModeArea.value();
    }
    dialogInfo.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    return dialogInfo;
}

TimePickerSettingData BuildTimePickerSettingData(const Ark_TimePickerDialogOptions& options)
{
    TimePickerSettingData settingData;
    auto useMilitaryTime = Converter::OptConvert<bool>(options.useMilitaryTime);
    if (useMilitaryTime) {
        settingData.isUseMilitaryTime = useMilitaryTime.value();
    }
    auto selectedDate = ProcessBindableDateSelected(options.selected);
    if (selectedDate) {
        settingData.dialogTitleDate = selectedDate.value();
    }
    auto disappearTextStyle = Converter::OptConvert<PickerTextStyle>(options.disappearTextStyle);
    if (disappearTextStyle) {
        settingData.properties.disappearTextStyle_ = disappearTextStyle.value();
    }
    auto textStyle = Converter::OptConvert<PickerTextStyle>(options.textStyle);
    if (textStyle) {
        settingData.properties.normalTextStyle_ = textStyle.value();
    }
    auto selectedTextStyle = Converter::OptConvert<PickerTextStyle>(options.selectedTextStyle);
    if (selectedTextStyle) {
        settingData.properties.selectedTextStyle_ = selectedTextStyle.value();
    }
    auto dateTimeOptions = Converter::OptConvert<DateTimeType>(options.dateTimeOptions);
    if (dateTimeOptions) {
        settingData.dateTimeOptions.hourType = dateTimeOptions->hourType;
        settingData.dateTimeOptions.minuteType = dateTimeOptions->minuteType;
        settingData.dateTimeOptions.secondType = dateTimeOptions->secondType;
    }
    settingData.isEnableHapticFeedback = true;
    auto enableHapticFeedback = Converter::OptConvert<bool>(options.enableHapticFeedback);
    if (enableHapticFeedback) {
        settingData.isEnableHapticFeedback = enableHapticFeedback.value();
    }
    auto format = Converter::OptConvert<TimePickerFormat>(options.format);
    bool showSecond = format.has_value() && format.value() == TimePickerFormat::HOUR_MINUTE_SECOND;
    settingData.showSecond = showSecond;
    auto enableCascade = Converter::OptConvert<bool>(options.enableCascade);
    if (enableCascade) {
        settingData.isEnableCascade = enableCascade.value();
    }
    return settingData;
}

TimePickerDialogEvent BuildTimePickerDialogEvents(const Ark_TimePickerDialogOptions& options)
{
    TimePickerDialogEvent dialogEvent;
    auto didAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogEvent.onDidAppear = onDidAppear;
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogEvent.onDidDisappear = onDidDisappear;
    }
    auto willAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void { arkCallback.Invoke(); };
        dialogEvent.onWillAppear = onWillAppear;
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogEvent.onWillDisappear = onWillDisappear;
    }
    return dialogEvent;
}
std::vector<ButtonInfo> BuildButtonInfos(const Ark_TimePickerDialogOptions& options)
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

void Show(const Ark_TimePickerDialogOptions* options)
{
    CHECK_NULL_VOID(options);
    PickerDialogInfo dialogInfo = BuildTimePickerDialogInfo(*options);
    TimePickerSettingData settingData = BuildTimePickerSettingData(*options);
    dialogInfo.isUseMilitaryTime = settingData.isUseMilitaryTime;
    // onCancel
    std::function<void()> cancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<Callback_Void>(options->onCancel);
    if (cancelCallbackOpt) {
        cancelEvent = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void { arkCallback.Invoke(); };
    }
    // onAccept
    std::function<void(const std::string&)> acceptEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(options->onAccept);
    if (acceptCallbackOpt) {
        acceptEvent = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // onChange
    std::function<void(const std::string&)> changeEvent;
    auto changeCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(options->onChange);
    if (changeCallbackOpt) {
        changeEvent = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // onEnterSelectedAreaEvent
    std::function<void(const std::string&)> enterSelectedAreaEvent;
    auto enterSelectedAreaCallbackOpt =
        Converter::OptConvert<Callback_TimePickerResult_Void>(options->onEnterSelectedArea);
    if (enterSelectedAreaCallbackOpt) {
        enterSelectedAreaEvent = [arkCallback = CallbackHelper(*enterSelectedAreaCallbackOpt)](
                                     const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // window lifecycle callback event
    TimePickerDialogEvent timePickerDialogEvent = BuildTimePickerDialogEvents(*options);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(*options);
    TimePickerDialogModel::GetInstance()->SetTimePickerDialogShow(dialogInfo, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(enterSelectedAreaEvent), timePickerDialogEvent,
        buttonInfos);
}
} // namespace TimePickerDialogExtender
} // namespace OHOS::Ace::NG