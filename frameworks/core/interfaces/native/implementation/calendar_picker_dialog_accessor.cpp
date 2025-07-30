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
#include "core/components_ng/pattern/calendar_picker/calendar_dialog_view.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace CalendarPickerDialogAccessor {
void BuildDialogPropertiesCallbacks(const Ark_CalendarDialogOptions options, DialogProperties& dialogProps)
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
DialogProperties BuildDialogProperties(const Ark_CalendarDialogOptions options)
{
    DialogProperties dialogProps;
    dialogProps.alignment = DialogAlignment::CENTER;
    dialogProps.backgroundBlurStyle = static_cast<int32_t>(Converter::OptConvert<BlurStyle>(
        options.backgroundBlurStyle).value_or(BlurStyle::COMPONENT_REGULAR));
    dialogProps.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogProps.customStyle = false;
    // dialogProps.enableHoverMode =
    //     Converter::OptConvert<bool>(options.enableHoverMode).value_or(dialogProps.enableHoverMode);
    dialogProps.hoverModeArea = Converter::OptConvert<HoverModeAreaType>(options.hoverModeArea);
    BuildDialogPropertiesCallbacks(options, dialogProps);
    return dialogProps;
}
CalendarSettingData BuildSettingData(const Ark_CalendarDialogOptions options)
{
    CalendarSettingData settingData;
    auto selectedDateOpt = Converter::OptConvert<PickerDate>(options.selected);
    if (selectedDateOpt) {
        settingData.selectedDate = *selectedDateOpt;
    }
    settingData.dayRadius = Converter::OptConvert<Dimension>(options.hintRadius);
    return settingData;
}
std::vector<ButtonInfo> BuildButtonInfos(const Ark_CalendarDialogOptions options)
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
void ShowImpl(const Opt_CalendarDialogOptions* options)
{
    CHECK_NULL_VOID(options);
    auto arkOptionsOpt = Converter::OptConvert<Ark_CalendarDialogOptions>(*options);
    if (!arkOptionsOpt.has_value()) { return; }

    Ark_CalendarDialogOptions arkOptions = *arkOptionsOpt;
    DialogProperties dialogProps = BuildDialogProperties(arkOptions);
    CalendarSettingData settingData = BuildSettingData(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);

    std::map<std::string, DialogEvent> dialogEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onAccept);
    if (acceptCallbackOpt) {
        auto onAcceptFunc = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            Ark_Date date = Converter::ArkValue<Ark_Date>(info);
            arkCallback.Invoke(date);
        };
        dialogEvent["acceptId"] = onAcceptFunc;
    }
    auto changeCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onChange);
    if (changeCallbackOpt) {
        auto onChangeFunc = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            Ark_Date date = Converter::ArkValue<Ark_Date>(info);
            arkCallback.Invoke(date);
        };
        dialogEvent["changeId"] = onChangeFunc;
    }

    std::map<std::string, DialogGestureEvent> dialogCancelEvent;
    auto cancelCallbackOpt = Converter::OptConvert<VoidCallback>(arkOptions.onCancel);
    if (cancelCallbackOpt) {
        auto onCancelFunc = [arkCallback = CallbackHelper(*cancelCallbackOpt)](const GestureEvent& info) -> void {
            arkCallback.Invoke();
        };
        dialogCancelEvent["cancelId"] = onCancelFunc;
    }

    CalendarDialogView::Show(dialogProps, settingData, buttonInfos, dialogEvent, dialogCancelEvent);
}
} // CalendarPickerDialogAccessor
const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor()
{
    static const GENERATED_ArkUICalendarPickerDialogAccessor CalendarPickerDialogAccessorImpl {
        CalendarPickerDialogAccessor::ShowImpl,
    };
    return &CalendarPickerDialogAccessorImpl;
}

}
