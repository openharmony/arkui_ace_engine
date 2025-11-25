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
    auto blurStyle = Converter::OptConvert<BlurStyle>(options.backgroundBlurStyle);
    if (blurStyle.has_value()) {
        dialogProps.backgroundBlurStyle = static_cast<int32_t>(blurStyle.value());
    }
    dialogProps.backgroundColor = Converter::OptConvert<Color>(options.backgroundColor);
    dialogProps.blurStyleOption = Converter::OptConvert<BlurStyleOption>(options.backgroundBlurStyleOptions);
    dialogProps.effectOption = Converter::OptConvert<EffectOption>(options.backgroundEffect);
    dialogProps.shadow = Converter::OptConvert<Shadow>(options.shadow);
    dialogProps.customStyle = false;
    dialogProps.enableHoverMode = Converter::OptConvert<bool>(options.enableHoverMode);
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
    auto startDate = Converter::OptConvert<PickerDate>(options.start).value_or(PickerDate());
    auto endDate = Converter::OptConvert<PickerDate>(options.end).value_or(PickerDate());
    if (endDate.GetYear() > 0 && startDate.ToDays() > endDate.ToDays()) {
        startDate = PickerDate();
        endDate = PickerDate();
    }
    settingData.startDate = startDate;
    settingData.endDate = endDate;
    settingData.disabledDateRange =
        Converter::Convert<std::vector<std::pair<PickerDate, PickerDate>>>(options.disabledDateRange.value);
    PickerDate::SortAndMergeDisabledDateRange(settingData.disabledDateRange);
    settingData.dayRadius = Converter::OptConvert<Dimension>(options.hintRadius);
    auto markToday = Converter::OptConvert<bool>(options.markToday);
    if (markToday.has_value()) {
        settingData.markToday = markToday.value();
    }
    return settingData;
}

std::map<std::string, NG::DialogCancelEvent> ParseDialogLifeCycleEvents(const Ark_CalendarDialogOptions& options)
{
    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent;
    auto didAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidAppear);
    if (didAppearCallbackOpt) {
        auto onDidAppear = [arkCallback = CallbackHelper(*didAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogLifeCycleEvent.emplace("didAppearId", onDidAppear);
    }
    auto didDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onDidDisappear);
    if (didDisappearCallbackOpt) {
        auto onDidDisappear = [arkCallback = CallbackHelper(*didDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogLifeCycleEvent.emplace("didDisappearId", onDidDisappear);
    }
    auto willAppearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillAppear);
    if (willAppearCallbackOpt) {
        auto onWillAppear = [arkCallback = CallbackHelper(*willAppearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogLifeCycleEvent.emplace("willAppearId", onWillAppear);
    }
    auto willDisappearCallbackOpt = Converter::OptConvert<VoidCallback>(options.onWillDisappear);
    if (willDisappearCallbackOpt) {
        auto onWillDisappear = [arkCallback = CallbackHelper(*willDisappearCallbackOpt)]() -> void {
            arkCallback.Invoke();
        };
        dialogLifeCycleEvent.emplace("willDisappearId", onWillDisappear);
    }
    return dialogLifeCycleEvent;
}

std::vector<ButtonInfo> BuildButtonInfos(const Ark_CalendarDialogOptions options)
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

std::optional<Ark_Date> ProcessDateStr(const std::string info)
{
    std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(info);
    CHECK_NULL_RETURN(argsPtr, std::nullopt);
    const auto year = argsPtr->GetValue("year")->GetInt();
    const auto month = argsPtr->GetValue("month")->GetInt();
    const auto day = argsPtr->GetValue("day")->GetInt();

    PickerDateTime dateTime;
    dateTime.SetDate(PickerDate(year, month, day));
    dateTime.SetTime(PickerTime::Current());
    auto result = Converter::ArkValue<Ark_Date>(dateTime.ToString(true));
    return result;
}

void DestroyPeerImpl(Ark_CalendarPickerDialog peer)
{
}
Ark_CalendarPickerDialog ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ShowImpl(const Opt_CalendarDialogOptions* options)
{
    auto arkOptionsOpt = Converter::OptConvertPtr<Ark_CalendarDialogOptions>(options);
    if (!arkOptionsOpt.has_value()) { return; }

    Ark_CalendarDialogOptions arkOptions = *arkOptionsOpt;
    DialogProperties dialogProps = BuildDialogProperties(arkOptions);
    CalendarSettingData settingData = BuildSettingData(arkOptions);
    std::vector<ButtonInfo> buttonInfos = BuildButtonInfos(arkOptions);

    std::map<std::string, DialogEvent> dialogEvent;
    auto acceptCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onAccept);
    if (acceptCallbackOpt) {
        auto onAcceptFunc = [arkCallback = CallbackHelper(*acceptCallbackOpt)](const std::string& info) -> void {
            auto result = ProcessDateStr(info);
            if (result) {
                arkCallback.Invoke(result.value());
            }
        };
        dialogEvent["acceptId"] = onAcceptFunc;
    }
    auto changeCallbackOpt = Converter::OptConvert<Callback_Date_Void>(arkOptions.onChange);
    if (changeCallbackOpt) {
        auto onChangeFunc = [arkCallback = CallbackHelper(*changeCallbackOpt)](const std::string& info) -> void {
            auto result = ProcessDateStr(info);
            if (result) {
                arkCallback.Invoke(result.value());
            }
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

    std::map<std::string, NG::DialogCancelEvent> dialogLifeCycleEvent = ParseDialogLifeCycleEvents(arkOptions);

    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope cope(currentId);
    auto container = Container::CurrentSafely();
    CHECK_NULL_VOID(container);
    auto context = AceType::DynamicCast<NG::PipelineContext>(container->GetPipelineContext());
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    CHECK_NULL_VOID(overlayManager);
    auto executor = context->GetTaskExecutor();
    CHECK_NULL_VOID(executor);
    executor->PostTask(
        [dialogProps, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos,
            weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            overlayManager->ShowCalendarDialog(
                dialogProps, settingData, dialogEvent, dialogCancelEvent, dialogLifeCycleEvent, buttonInfos);
        },
        TaskExecutor::TaskType::UI, "ArkUIDialogShowCalendarPicker",
        TaskExecutor::GetPriorityTypeWithCheck(PriorityType::VIP));
}
} // CalendarPickerDialogAccessor
const GENERATED_ArkUICalendarPickerDialogAccessor* GetCalendarPickerDialogAccessor()
{
    static const GENERATED_ArkUICalendarPickerDialogAccessor CalendarPickerDialogAccessorImpl {
        CalendarPickerDialogAccessor::DestroyPeerImpl,
        CalendarPickerDialogAccessor::ConstructImpl,
        CalendarPickerDialogAccessor::GetFinalizerImpl,
        CalendarPickerDialogAccessor::ShowImpl,
    };
    return &CalendarPickerDialogAccessorImpl;
}

}
