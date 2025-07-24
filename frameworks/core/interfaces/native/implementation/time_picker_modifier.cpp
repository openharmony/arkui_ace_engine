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
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/components_ng/pattern/time_picker/timepicker_event_hub.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"

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

    auto showSeconds = false;
    auto pickerFormat = options ?
        Converter::OptConvert<TimePickerFormat>(options->value.format) :
        std::nullopt;
    if (pickerFormat.has_value() && pickerFormat.value() == TimePickerFormat::HOUR_MINUTE_SECOND) {
        showSeconds = true;
    }
    TimePickerModelNG::SetHasSecond(frameNode, showSeconds);

    auto selected = options ?
        Converter::OptConvert<PickerTime>(options->value.selected) :
        std::nullopt;
    if (selected.has_value()) {
        TimePickerModelNG::SetSelectedTime(frameNode, selected.value());
    }

    auto start = options ?
        Converter::OptConvert<PickerTime>(options->value.start) :
        std::nullopt;
    if (start.has_value()) {
        TimePickerModelNG::SetStartTime(frameNode, start.value());
    }

    auto end = options ?
        Converter::OptConvert<PickerTime>(options->value.end) :
        std::nullopt;
    if (end.has_value()) {
        TimePickerModelNG::SetEndTime(frameNode, end.value());
    }
}
} // TimePickerInterfaceModifier
namespace TimePickerAttributeModifier {
void UseMilitaryTime0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetHour24(frameNode, *convValue);
}
void UseMilitaryTime1Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void Loop0Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetWheelModeEnabled(frameNode, *convValue);
}
void Loop1Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, *convValue);
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, *convValue);
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto pickerStyle = Converter::OptConvert<PickerTextStyle>(*value);
    auto context = frameNode->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    auto convValue = Converter::OptConvert<PickerTextStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, *convValue);
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DateTimeOptions0Impl(Ark_NativePointer node,
                          const Opt_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto dateTimeOptions = Converter::OptConvert<DateTimeType>(*value);
    // TODO: Reset value
    if (dateTimeOptions) {
        TimePickerModelNG::SetDateTimeOptions(frameNode, dateTimeOptions->hourType,
            dateTimeOptions->minuteType, dateTimeOptions->secondType);
    }
}
void DateTimeOptions1Impl(Ark_NativePointer node,
                          const Opt_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DateTimeType dateTimeOptions = Converter::OptConvert<DateTimeType>(*value).value_or(
        DateTimeType {ZeroPrefixType::AUTO, ZeroPrefixType::AUTO, ZeroPrefixType::AUTO});
    TimePickerModelNG::SetDateTimeOptions(frameNode, dateTimeOptions.hourType,
        dateTimeOptions.minuteType, dateTimeOptions.secondType);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Opt_Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        auto resultStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_TimePickerResult>(resultStr);
        arkCallback.Invoke(result);
    };
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnTimePickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                             const Opt_Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEnterSelectedArea = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        auto resultStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_TimePickerResult>(resultStr);
        arkCallback.Invoke(result);
    };
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnEnterSelectedArea(std::move(onEnterSelectedArea));
}
void EnableHapticFeedback0Impl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, *convValue);
}
void EnableHapticFeedback1Impl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = EnumToInt(value ? Converter::OptConvert<CrownSensitivity>(*value) : std::nullopt);
    TimePickerModelNG::SetDigitalCrownSensitivity(frameNode, convValue);
}
void EnableCascadeImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    TimePickerModelNG::SetEnableCascade(frameNode, *convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        auto selectedStr = eventInfo->GetSelectedStr();
        auto result = Converter::ArkValue<Ark_Date>(selectedStr);
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(result);
    };
    TimePickerModelNG::SetChangeEvent(frameNode, std::move(onEvent));
}
} // TimePickerAttributeModifier
const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
{
    static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
        TimePickerModifier::ConstructImpl,
        TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
        TimePickerAttributeModifier::UseMilitaryTime0Impl,
        TimePickerAttributeModifier::UseMilitaryTime1Impl,
        TimePickerAttributeModifier::Loop0Impl,
        TimePickerAttributeModifier::Loop1Impl,
        TimePickerAttributeModifier::DisappearTextStyle0Impl,
        TimePickerAttributeModifier::DisappearTextStyle1Impl,
        TimePickerAttributeModifier::TextStyle0Impl,
        TimePickerAttributeModifier::TextStyle1Impl,
        TimePickerAttributeModifier::SelectedTextStyle0Impl,
        TimePickerAttributeModifier::SelectedTextStyle1Impl,
        TimePickerAttributeModifier::DateTimeOptions0Impl,
        TimePickerAttributeModifier::DateTimeOptions1Impl,
        TimePickerAttributeModifier::OnChange0Impl,
        TimePickerAttributeModifier::OnChange1Impl,
        TimePickerAttributeModifier::OnEnterSelectedAreaImpl,
        TimePickerAttributeModifier::EnableHapticFeedback0Impl,
        TimePickerAttributeModifier::EnableHapticFeedback1Impl,
        TimePickerAttributeModifier::DigitalCrownSensitivityImpl,
        TimePickerAttributeModifier::EnableCascadeImpl,
        TimePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUITimePickerModifierImpl;
}

}
