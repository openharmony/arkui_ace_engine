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
namespace DatePickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // DatePickerModifier
namespace DatePickerInterfaceModifier {
void SetDatePickerOptionsImpl(Ark_NativePointer node,
                              const Opt_DatePickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //DatePickerModelNG::SetSetDatePickerOptions(frameNode, convValue);
}
} // DatePickerInterfaceModifier
namespace DatePickerAttributeModifier {
void Lunar0Impl(Ark_NativePointer node,
                Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //DatePickerModelNG::SetLunar0(frameNode, convValue);
}
void Lunar1Impl(Ark_NativePointer node,
                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetLunar1(frameNode, convValue);
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DatePickerModelNG::SetDisappearTextStyle0(frameNode, convValue);
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetDisappearTextStyle1(frameNode, convValue);
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DatePickerModelNG::SetTextStyle0(frameNode, convValue);
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetTextStyle1(frameNode, convValue);
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DatePickerModelNG::SetSelectedTextStyle0(frameNode, convValue);
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetSelectedTextStyle1(frameNode, convValue);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_DatePickerResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DatePickerModelNG::SetOnChange(frameNode, convValue);
}
void OnDateChange0Impl(Ark_NativePointer node,
                       const Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //DatePickerModelNG::SetOnDateChange0(frameNode, convValue);
}
void OnDateChange1Impl(Ark_NativePointer node,
                       const Opt_Callback_Date_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetOnDateChange1(frameNode, convValue);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //DatePickerModelNG::SetDigitalCrownSensitivity(frameNode, convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Date_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //DatePickerModelNG::Set_onChangeEvent_selected(frameNode, convValue);
}
} // DatePickerAttributeModifier
const GENERATED_ArkUIDatePickerModifier* GetDatePickerModifier()
{
    static const GENERATED_ArkUIDatePickerModifier ArkUIDatePickerModifierImpl {
        DatePickerModifier::ConstructImpl,
        DatePickerInterfaceModifier::SetDatePickerOptionsImpl,
        DatePickerAttributeModifier::Lunar0Impl,
        DatePickerAttributeModifier::Lunar1Impl,
        DatePickerAttributeModifier::DisappearTextStyle0Impl,
        DatePickerAttributeModifier::DisappearTextStyle1Impl,
        DatePickerAttributeModifier::TextStyle0Impl,
        DatePickerAttributeModifier::TextStyle1Impl,
        DatePickerAttributeModifier::SelectedTextStyle0Impl,
        DatePickerAttributeModifier::SelectedTextStyle1Impl,
        DatePickerAttributeModifier::OnChangeImpl,
        DatePickerAttributeModifier::OnDateChange0Impl,
        DatePickerAttributeModifier::OnDateChange1Impl,
        DatePickerAttributeModifier::DigitalCrownSensitivityImpl,
        DatePickerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIDatePickerModifierImpl;
}

}
