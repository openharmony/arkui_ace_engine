/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<TimePickerFormat>& dst, const Ark_TimePickerFormat& src)
{
    switch (src) {
        case ARK_TIME_PICKER_FORMAT_HOUR_MINUTE: dst = TimePickerFormat::HOUR_MINUTE; break;
        case ARK_TIME_PICKER_FORMAT_HOUR_MINUTE_SECOND: dst = TimePickerFormat::HOUR_MINUTE_SECOND; break;
        default: LOGE("Unexpected enum value in Ark_TimePickerFormat: %{public}d", src);
    }
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
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

    LOGE("TimePickerInterfaceModifier::SetTimePickerOptionsImpl - Ark_CustomObject isn't supported");
}
} // TimePickerInterfaceModifier
namespace TimePickerAttributeModifier {
void UseMilitaryTimeImpl(Ark_NativePointer node,
                         Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetHour24(frameNode, Converter::Convert<bool>(value));
}
void LoopImpl(Ark_NativePointer node,
              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetWheelModeEnabled(frameNode, Converter::Convert<bool>(value));
}
void DisappearTextStyleImpl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TimePickerModelNG::SetDisappearTextStyle(frameNode, theme, pickerStyle);
}
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TimePickerModelNG::SetNormalTextStyle(frameNode, theme, pickerStyle);
}
void SelectedTextStyleImpl(Ark_NativePointer node,
                           const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto pickerStyle = Converter::Convert<PickerTextStyle>(*value);
    auto theme = GetTheme<PickerTheme>();
    CHECK_NULL_VOID(theme);
    TimePickerModelNG::SetSelectedTextStyle(frameNode, theme, pickerStyle);
}
void DateTimeOptionsImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetDateTimeOptions(frameNode, convValue);
    LOGE("TimePickerInterfaceModifier::DateTimeOptionsImpl - Ark_CustomObject isn't supported");
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [frameNode](const BaseEventInfo* event) {
        const auto* eventInfo = TypeInfoHelper::DynamicCast<DatePickerChangeEvent>(event);
        auto resultStr = eventInfo->GetSelectedStr();
        auto data = JsonUtil::ParseJsonString(resultStr);
        auto hour = data->GetValue("hour")->GetInt();
        auto minute = data->GetValue("minute")->GetInt();
        auto second = data->GetValue("second")->GetInt();
        Ark_TimePickerResult result = {
            .hour = Converter::ArkValue<Ark_Number>(hour),
            .minute = Converter::ArkValue<Ark_Number>(minute),
            .second = Converter::ArkValue<Ark_Number>(second)
        };
        GetFullAPI()->getEventsAPI()->getTimePickerEventsReceiver()->onChange(frameNode->GetId(), result);
    };
    auto eventHub = frameNode->GetEventHub<TimePickerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChange(std::move(onChange));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TimePickerModelNG::SetIsEnableHapticFeedback(frameNode, Converter::Convert<bool>(value));
}
} // TimePickerAttributeModifier
const GENERATED_ArkUITimePickerModifier* GetTimePickerModifier()
{
    static const GENERATED_ArkUITimePickerModifier ArkUITimePickerModifierImpl {
        TimePickerModifier::ConstructImpl,
        TimePickerInterfaceModifier::SetTimePickerOptionsImpl,
        TimePickerAttributeModifier::UseMilitaryTimeImpl,
        TimePickerAttributeModifier::LoopImpl,
        TimePickerAttributeModifier::DisappearTextStyleImpl,
        TimePickerAttributeModifier::TextStyleImpl,
        TimePickerAttributeModifier::SelectedTextStyleImpl,
        TimePickerAttributeModifier::DateTimeOptionsImpl,
        TimePickerAttributeModifier::OnChangeImpl,
        TimePickerAttributeModifier::EnableHapticFeedbackImpl,
    };
    return &ArkUITimePickerModifierImpl;
}

}
