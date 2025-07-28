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
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_time_picker_dialog_view.h"
#else
#include "core/components_ng/pattern/time_picker/timepicker_dialog_view.h"
#endif
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerDialogAccessor {
void BuildDialogPropertiesCallbacks(const Ark_TimePickerDialogOptions options, DialogProperties& dialogProps)
{
    auto didAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidAppear = onDidAppear;
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onDidDisappear = onDidDisappear;
    }
    auto willAppearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillAppear = onWillAppear;
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<Callback_Void>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogProps.onWillDisappear = onWillDisappear;
    }
}
DialogProperties BuildDialogProperties(const Ark_TimePickerDialogOptions options)
{
    DialogProperties dialogProps;
    auto alignment = Converter::OptConvert<DialogAlignment>(options.alignment);
    if (alignment) {
        dialogProps.alignment = alignment.value();
    }
    auto offset = Converter::OptConvert<DimensionOffset>(options.offset);
    if (offset) {
        dialogProps.offset = offset.value();
    }
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        options.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    auto enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode);
    if (enableHoverMode) {
        dialogProps.enableHoverMode = enableHoverMode.value();
    }
    auto hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    if (hoverModeArea) {
        dialogProps.hoverModeArea = hoverModeArea.value();
    }
    dialogProps.maskRect = Converter::OptConvert<DimensionRect>(options.maskRect);
    BuildDialogPropertiesCallbacks(options, dialogProps);
    return dialogProps;
}
TimePickerSettingData BuildPickerSettingData(const Ark_TimePickerDialogOptions options)
{
    TimePickerSettingData settingData;
    auto format = Converter::OptConvert<TimePickerFormat>(options.format);
    bool showSecond = format.has_value() && format.value() == TimePickerFormat::HOUR_MINUTE_SECOND;
    settingData.showSecond = showSecond;
    auto useMilitaryTime = Converter::OptConvert<bool>(options.useMilitaryTime);
    if (useMilitaryTime) {
        settingData.isUseMilitaryTime = useMilitaryTime.value();
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
    return settingData;
}
std::vector<ButtonInfo> BuildButtonInfos(const Ark_TimePickerDialogOptions options)
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
    DialogProperties dialogProps = BuildDialogProperties(arkOptions);
    TimePickerSettingData settingData = BuildPickerSettingData(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);

    std::map<std::string, PickerTime> timePickerProp;
    auto time = Converter::OptConvert<PickerTime>(arkOptions.selected);
    if (time) {
        timePickerProp.insert({"selected", time.value()});
    }

    std::map<std::string, DialogEvent> dialogEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(arkOptions.onAccept);
    if (acceptCallbackOpt) {
        auto onAcceptFunc = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            auto timePickerRes = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(timePickerRes);
        };
        dialogEvent["acceptId"] = onAcceptFunc;
    }
    auto changeCallbackOpt = Converter::OptConvert<Callback_TimePickerResult_Void>(arkOptions.onChange);
    if (changeCallbackOpt) {
        auto onChangeFunc = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            auto timePickerRes = Converter::ArkValue<Ark_TimePickerResult>(info);
            arkCallback.Invoke(timePickerRes);
        };
        dialogEvent["changeId"] = onChangeFunc;
    }

    std::map<std::string, DialogGestureEvent> dialogCancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<Callback_Void>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        auto onCancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)](const GestureEvent& info) -> void {
            arkCallback.Invoke();
        };
        dialogCancelEvent["cancelId"] = onCancelFunc;
    }
#ifndef ARKUI_CAPI_UNITTEST
    TimePickerDialogView::Show(dialogProps, settingData, buttonInfos,
        timePickerProp, dialogEvent, dialogCancelEvent);
#else
    MockTimePickerDialogView::SetData(dialogProps, settingData, buttonInfos, timePickerProp);
    MockTimePickerDialogView::SetCallbacks(dialogEvent, dialogCancelEvent);
#endif
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
