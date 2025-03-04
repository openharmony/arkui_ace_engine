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
namespace TextPickerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // TextPickerModifier
namespace TextPickerInterfaceModifier {
void SetTextPickerOptionsImpl(Ark_NativePointer node,
                              const Opt_TextPickerOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //TextPickerModelNG::SetSetTextPickerOptions(frameNode, convValue);
}
} // TextPickerInterfaceModifier
namespace TextPickerAttributeModifier {
void DefaultPickerItemHeight0Impl(Ark_NativePointer node,
                                  const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDefaultPickerItemHeight0(frameNode, convValue);
}
void DefaultPickerItemHeight1Impl(Ark_NativePointer node,
                                  const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetDefaultPickerItemHeight1(frameNode, convValue);
}
void CanLoop0Impl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextPickerModelNG::SetCanLoop0(frameNode, convValue);
}
void CanLoop1Impl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetCanLoop1(frameNode, convValue);
}
void DisappearTextStyle0Impl(Ark_NativePointer node,
                             const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDisappearTextStyle0(frameNode, convValue);
}
void DisappearTextStyle1Impl(Ark_NativePointer node,
                             const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetDisappearTextStyle1(frameNode, convValue);
}
void TextStyle0Impl(Ark_NativePointer node,
                    const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetTextStyle0(frameNode, convValue);
}
void TextStyle1Impl(Ark_NativePointer node,
                    const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetTextStyle1(frameNode, convValue);
}
void SelectedTextStyle0Impl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetSelectedTextStyle0(frameNode, convValue);
}
void SelectedTextStyle1Impl(Ark_NativePointer node,
                            const Opt_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSelectedTextStyle1(frameNode, convValue);
}
void DisableTextStyleAnimationImpl(Ark_NativePointer node,
                                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextPickerModelNG::SetDisableTextStyleAnimation(frameNode, convValue);
}
void DefaultTextStyleImpl(Ark_NativePointer node,
                          const Ark_TextPickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDefaultTextStyle(frameNode, convValue);
}
void OnAcceptImpl(Ark_NativePointer node,
                  const Callback_String_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnAccept(frameNode, convValue);
}
void OnCancelImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnCancel(frameNode, convValue);
}
void OnChange0Impl(Ark_NativePointer node,
                   const Type_TextPickerAttribute_onChange_callback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnChange0(frameNode, convValue);
}
void OnChange1Impl(Ark_NativePointer node,
                   const Opt_OnTextPickerChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetOnChange1(frameNode, convValue);
}
void OnScrollStop0Impl(Ark_NativePointer node,
                       const TextPickerScrollStopCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnScrollStop0(frameNode, convValue);
}
void OnScrollStop1Impl(Ark_NativePointer node,
                       const Opt_TextPickerScrollStopCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetOnScrollStop1(frameNode, convValue);
}
void OnEnterSelectedAreaImpl(Ark_NativePointer node,
                             const TextPickerEnterSelectedAreaCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnEnterSelectedArea(frameNode, convValue);
}
void SelectedIndex0Impl(Ark_NativePointer node,
                        const Ark_Union_Number_Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetSelectedIndex0(frameNode, convValue);
}
void SelectedIndex1Impl(Ark_NativePointer node,
                        const Opt_Union_Number_Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetSelectedIndex1(frameNode, convValue);
}
void Divider0Impl(Ark_NativePointer node,
                  const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetDivider0(frameNode, convValue);
}
void Divider1Impl(Ark_NativePointer node,
                  const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetDivider1(frameNode, convValue);
}
void GradientHeight0Impl(Ark_NativePointer node,
                         const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetGradientHeight0(frameNode, convValue);
}
void GradientHeight1Impl(Ark_NativePointer node,
                         const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetGradientHeight1(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //TextPickerModelNG::SetDigitalCrownSensitivity(frameNode, convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Union_Number_Array_Number_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //TextPickerModelNG::Set_onChangeEvent_selected(frameNode, convValue);
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Union_String_Array_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //TextPickerModelNG::Set_onChangeEvent_value(frameNode, convValue);
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerModifier::ConstructImpl,
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::DefaultPickerItemHeight0Impl,
        TextPickerAttributeModifier::DefaultPickerItemHeight1Impl,
        TextPickerAttributeModifier::CanLoop0Impl,
        TextPickerAttributeModifier::CanLoop1Impl,
        TextPickerAttributeModifier::DisappearTextStyle0Impl,
        TextPickerAttributeModifier::DisappearTextStyle1Impl,
        TextPickerAttributeModifier::TextStyle0Impl,
        TextPickerAttributeModifier::TextStyle1Impl,
        TextPickerAttributeModifier::SelectedTextStyle0Impl,
        TextPickerAttributeModifier::SelectedTextStyle1Impl,
        TextPickerAttributeModifier::DisableTextStyleAnimationImpl,
        TextPickerAttributeModifier::DefaultTextStyleImpl,
        TextPickerAttributeModifier::OnAcceptImpl,
        TextPickerAttributeModifier::OnCancelImpl,
        TextPickerAttributeModifier::OnChange0Impl,
        TextPickerAttributeModifier::OnChange1Impl,
        TextPickerAttributeModifier::OnScrollStop0Impl,
        TextPickerAttributeModifier::OnScrollStop1Impl,
        TextPickerAttributeModifier::OnEnterSelectedAreaImpl,
        TextPickerAttributeModifier::SelectedIndex0Impl,
        TextPickerAttributeModifier::SelectedIndex1Impl,
        TextPickerAttributeModifier::Divider0Impl,
        TextPickerAttributeModifier::Divider1Impl,
        TextPickerAttributeModifier::GradientHeight0Impl,
        TextPickerAttributeModifier::GradientHeight1Impl,
        TextPickerAttributeModifier::EnableHapticFeedbackImpl,
        TextPickerAttributeModifier::DigitalCrownSensitivityImpl,
        TextPickerAttributeModifier::_onChangeEvent_selectedImpl,
        TextPickerAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
