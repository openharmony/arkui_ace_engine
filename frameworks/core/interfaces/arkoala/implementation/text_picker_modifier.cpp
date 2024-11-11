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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
void DefaultPickerItemHeightImpl(Ark_NativePointer node,
                                 const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDefaultPickerItemHeight(frameNode, convValue);
}
void CanLoopImpl(Ark_NativePointer node,
                 Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextPickerModelNG::SetCanLoop(frameNode, convValue);
}
void DisappearTextStyleImpl(Ark_NativePointer node,
                            const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDisappearTextStyle(frameNode, convValue);
}
void TextStyleImpl(Ark_NativePointer node,
                   const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetTextStyle(frameNode, convValue);
}
void SelectedTextStyleImpl(Ark_NativePointer node,
                           const Ark_PickerTextStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetSelectedTextStyle(frameNode, convValue);
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
void OnChangeImpl(Ark_NativePointer node,
                  const Type_TextPickerAttribute_onChange_callback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetOnChange(frameNode, convValue);
}
void SelectedIndexImpl(Ark_NativePointer node,
                       const Ark_Union_Number_Array_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetSelectedIndex(frameNode, convValue);
}
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_DividerOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetDivider(frameNode, convValue);
}
void GradientHeightImpl(Ark_NativePointer node,
                        const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextPickerModelNG::SetGradientHeight(frameNode, convValue);
}
} // TextPickerAttributeModifier
const GENERATED_ArkUITextPickerModifier* GetTextPickerModifier()
{
    static const GENERATED_ArkUITextPickerModifier ArkUITextPickerModifierImpl {
        TextPickerInterfaceModifier::SetTextPickerOptionsImpl,
        TextPickerAttributeModifier::DefaultPickerItemHeightImpl,
        TextPickerAttributeModifier::CanLoopImpl,
        TextPickerAttributeModifier::DisappearTextStyleImpl,
        TextPickerAttributeModifier::TextStyleImpl,
        TextPickerAttributeModifier::SelectedTextStyleImpl,
        TextPickerAttributeModifier::OnAcceptImpl,
        TextPickerAttributeModifier::OnCancelImpl,
        TextPickerAttributeModifier::OnChangeImpl,
        TextPickerAttributeModifier::SelectedIndexImpl,
        TextPickerAttributeModifier::DividerImpl,
        TextPickerAttributeModifier::GradientHeightImpl,
    };
    return &ArkUITextPickerModifierImpl;
}

}
