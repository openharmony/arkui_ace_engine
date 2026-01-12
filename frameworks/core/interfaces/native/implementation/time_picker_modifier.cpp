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
#include "core/components_ng/pattern/picker/picker_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_static.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<PickerTime> ProcessBindableSelected(FrameNode* frameNode, const Opt_Union_Date_Bindable& value)
{
    std::optional<PickerTime> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Date& src) {
            result = Converter::OptConvert<PickerTime>(src);
        },
        [&result, frameNode](const Ark_Bindable_Date& src) {
            result = Converter::OptConvert<PickerTime>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const BaseEventInfo* event) {
                CHECK_NULL_VOID(event);
                const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
                CHECK_NULL_VOID(eventInfo);
                auto selectedStr = eventInfo->GetSelectedStr();
                auto result = Converter::ArkValue<Ark_Date>(selectedStr);
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(result);
            };
            TimePickerModelStatic::SetChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TimePickerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TimePickerModifier
namespace TimePickerInterfaceModifier {
void SetTimePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TimePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    auto optOptions = Converter::GetOptPtr(options);
    CHECK_NULL_VOID(optOptions);

    auto showSeconds = false;
    auto pickerFormat = Converter::OptConvert<TimePickerFormat>(optOptions->format);
    if (pickerFormat.has_value() && pickerFormat.value() == TimePickerFormat::HOUR_MINUTE_SECOND) {
        showSeconds = true;
    }
    TimePickerModelStatic::SetHasSecond(frameNode, showSeconds);

    auto selected = ProcessBindableSelected(frameNode, optOptions->selected);
    if (selected.has_value()) {
        TimePickerModelNG::SetSelectedTime(frameNode, selected.value());
    }

    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto startTime = theme->GetDefaultStartTime();
    auto endTime = theme->GetDefaultEndTime();
    auto start = Converter::OptConvert<PickerTime>(optOptions->start);
    if (start.has_value()) {
        startTime = start.value();
    }
    auto end = Converter::OptConvert<PickerTime>(optOptions->end);
    if (end.has_value()) {
        endTime = end.value();
    }
    if (startTime.ToMinutes() > endTime.ToMinutes()) {
        startTime = theme->GetDefaultStartTime();
        endTime = theme->GetDefaultEndTime();
    }
    TimePickerModelNG::SetStartTime(frameNode, startTime);
    TimePickerModelNG::SetEndTime(frameNode, endTime);
}
} // TimePickerInterfaceModifier
namespace TimePickerAttributeModifier {
void SetUseMilitaryTimeImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TimePickerModelStatic::SetUseMilitaryTime(frameNode, convValue);
}
void SetLoopImpl(Ark_NativePointer node,
                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TimePickerModelStatic::SetLoop(frameNode, convValue);
}
void SetDisappearTextStyleImpl(Ark_NativePointer node,
                               const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    PickerTextStyle defaultStyle;
    if (!convValue) {
        convValue = defaultStyle;
    }
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, *convValue);
}
void SetTextStyleImpl(Ark_NativePointer node,
                      const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    PickerTextStyle defaultStyle;
    if (!convValue) {
        convValue = defaultStyle;
    }
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, *convValue);
}
void SetSelectedTextStyleImpl(Ark_NativePointer node,
                              const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pickerStyle = Converter::OptConvertPtr<PickerTextStyle>(value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvertPtr<PickerTextStyle>(value);
    PickerTextStyle defaultStyle;
    if (!convValue) {
        convValue = defaultStyle;
    }
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, *convValue);
}
void SetDateTimeOptionsImpl(Ark_NativePointer node,
                            const Opt_intl_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dateTimeOptions = Converter::OptConvertPtr<DateTimeType>(value);
    if (dateTimeOptions) {
        TimePickerModelNG::SetDateTimeOptions(frameNode, dateTimeOptions->hourType,
            dateTimeOptions->minuteType, dateTimeOptions->secondType);
        return;
    }
    TimePickerModelStatic::ResetDateTimeOptions(frameNode);
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_OnTimePickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TimePickerModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        auto resultStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_TimePickerResult>(resultStr);
        arkCallback.Invoke(result);
    };
    TimePickerModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void SetOnEnterSelectedAreaImpl(Ark_NativePointer node,
                                const Opt_Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TimePickerModelStatic::SetOnEnterSelectedArea(frameNode, nullptr);
        return;
    }
    auto onEnterSelectedArea = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        auto resultStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_TimePickerResult>(resultStr);
        arkCallback.Invoke(result);
    };
    TimePickerModelStatic::SetOnEnterSelectedArea(frameNode, std::move(onEnterSelectedArea));
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value).value_or(true);
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, convValue);
}
void SetDigitalCrownSensitivityImpl(Ark_NativePointer node,
                                    const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = EnumToInt(Converter::OptConvertPtr<CrownSensitivity>(value));
    TimePickerModelStatic::SetDigitalCrownSensitivity(frameNode, convValue);
}
void SetEnableCascadeImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TimePickerModelStatic::SetEnableCascade(frameNode, convValue);
}
} // TimePickerAttributeModifier
const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
{
    static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
        TimePickerModifier::ConstructImpl,
        TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
        TimePickerAttributeModifier::SetUseMilitaryTimeImpl,
        TimePickerAttributeModifier::SetLoopImpl,
        TimePickerAttributeModifier::SetDisappearTextStyleImpl,
        TimePickerAttributeModifier::SetTextStyleImpl,
        TimePickerAttributeModifier::SetSelectedTextStyleImpl,
        TimePickerAttributeModifier::SetDateTimeOptionsImpl,
        TimePickerAttributeModifier::SetOnChangeImpl,
        TimePickerAttributeModifier::SetOnEnterSelectedAreaImpl,
        TimePickerAttributeModifier::SetEnableHapticFeedbackImpl,
        TimePickerAttributeModifier::SetDigitalCrownSensitivityImpl,
        TimePickerAttributeModifier::SetEnableCascadeImpl,
    };
    return &ArkUITimePickerModifierImpl;
}

}
