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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TimePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TimePickerModifier
namespace TimePickerInterfaceModifier {
void SetTimePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TimePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //TimePickerModelNG::SetSetTimePickerOptions(frameNode, convValue);
}
} // TimePickerInterfaceModifier
namespace TimePickerAttributeModifier {
void UseMilitaryTime0Impl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TimePickerModelNG::SetUseMilitaryTime0(frameNode, convValue);
}
void UseMilitaryTime1Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetUseMilitaryTime1(frameNode, convValue);
}
void Loop0Impl(Ark_NativePointer node,
               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TimePickerModelNG::SetLoop0(frameNode, convValue);
}
void Loop1Impl(Ark_NativePointer node,
               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetLoop1(frameNode, convValue);
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetDisappearTextStyle0(frameNode, convValue);
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetDisappearTextStyle1(frameNode, convValue);
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetTextStyle0(frameNode, convValue);
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetTextStyle1(frameNode, convValue);
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetSelectedTextStyle0(frameNode, convValue);
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetSelectedTextStyle1(frameNode, convValue);
}
void DateTimeOptions0Impl(Ark_NativePointer node,
                          const Ark_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetDateTimeOptions0(frameNode, convValue);
}
void DateTimeOptions1Impl(Ark_NativePointer node,
                          const Opt_DateTimeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetDateTimeOptions1(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnTimePickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetOnChange1(frameNode, convValue);
}
void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                             const Callback_TimePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TimePickerModelNG::SetOnEnterSelectedArea(frameNode, convValue);
}
void EnableHapticFeedback0Impl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TimePickerModelNG::SetEnableHapticFeedback0(frameNode, convValue);
}
void EnableHapticFeedback1Impl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetEnableHapticFeedback1(frameNode, convValue);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TimePickerModelNG::SetDigitalCrownSensitivity(frameNode, convValue);
}
void EnableCascadeImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TimePickerModelNG::SetEnableCascade(frameNode, convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //TimePickerModelNG::Set_onChangeEvent_selected(frameNode, convValue);
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
