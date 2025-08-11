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
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerDialogAccessor {
PickerDialogInfo BuildTimePickerDialogInfo(const Ark_TimePickerDialogOptions& options)
{
    PickerDialogInfo dialogInfo;

    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, dialogInfo);

    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    auto parseStartTime = pickerTheme->GetDefaultStartTime();
    auto parseEndTime = pickerTheme->GetDefaultEndTime();
    // start & end time
    auto start =  Converter::OptConvert<PickerTime>(options.start);
    if (start) {
        parseStartTime = start.value();
    }
    auto end =  Converter::OptConvert<PickerTime>(options.end);
    if (end) {
        parseEndTime = end.value();
    }
    dialogInfo.parseStartTime = parseStartTime;
    dialogInfo.parseEndTime = parseEndTime;
    // select time
    auto selectedTime = Converter::OptConvert<PickerTime>(options.selected);
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
    dialogInfo.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        options.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
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

TimePickerSettingData BuildPickerSettingData(const Ark_TimePickerDialogOptions& options)
{
    TimePickerSettingData settingData;
    auto useMilitaryTime = Converter::OptConvert<bool>(options.useMilitaryTime);
    if (useMilitaryTime) {
        settingData.isUseMilitaryTime = useMilitaryTime.value();
    }
    auto selectedDate = Converter::OptConvert<PickerDate>(options.selected);
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
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
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
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
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
        buttonInfos.push_back(acceptButtonInfo.value());
    }
    auto cancelButtonInfo = Converter::OptConvert<ButtonInfo>(options.cancelButtonStyle);
    if (cancelButtonInfo.has_value()) {
        buttonInfos.push_back(cancelButtonInfo.value());
    }
    return buttonInfos;
}

void ShowImpl(const Opt_TimePickerDialogOptions* options)
{
    CHECK_NULL_VOID(options);
    auto arkOptionsOpt = Converter::OptConvert<Ark_TimePickerDialogOptions>(*options);
    if (!arkOptionsOpt.has_value()) { return; }

    Ark_TimePickerDialogOptions arkOptions = arkOptionsOpt.value();
    PickerDialogInfo dialogInfo = BuildTimePickerDialogInfo(arkOptions);
    TimePickerSettingData settingData = BuildPickerSettingData(arkOptions);
    dialogInfo.isUseMilitaryTime = settingData.isUseMilitaryTime;
    // onCancel
    std::function<void()> cancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<Callback_Void>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        cancelEvent = [arkCallback = CallbackHelper(*cancelCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
    }
    // onAccept
    std::function<void(const std::string &)> acceptEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(arkOptions.onAccept);
    if (acceptCallbackOpt) {
        acceptEvent = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // onChange
    std::function<void(const std::string &)> changeEvent;
    auto changeCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(arkOptions.onChange);
    if (changeCallbackOpt) {
        changeEvent = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // onEnterSelectedAreaEvent
    std::function<void(const std::string &)> enterSelectedAreaEvent;
    auto enterSelectedAreaCallbackOpt =
        Converter::OptConvert<Callback_TimePickerResult_Void>(arkOptions.onEnterSelectedArea);
    if (enterSelectedAreaCallbackOpt) {
        enterSelectedAreaEvent =
            [arkCallback = CallbackHelper(*enterSelectedAreaCallbackOpt)](const std::string& info) -> void {
            auto result = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(result);
        };
    }
    // window lifecycle callback event
    TimePickerDialogEvent timePickerDialogEvent = BuildTimePickerDialogEvents(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);
    TimePickerDialogModel::GetInstance()->SetTimePickerDialogShow(dialogInfo, settingData, std::move(cancelEvent),
        std::move(acceptEvent), std::move(changeEvent), std::move(enterSelectedAreaEvent),
        timePickerDialogEvent, buttonInfos);
}
} // TimePickerDialogAccessor

const GENERATED_ArkUITimePickerDialogAccessor* GetTimePickerDialogAccessor()
{
    static const GENERATED_ArkUITimePickerDialogAccessor TimePickerDialogAccessorImpl {
        TimePickerDialogAccessor::ShowImpl,
    };
    return &TimePickerDialogAccessorImpl;
}
}
