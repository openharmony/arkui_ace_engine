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
namespace SelectModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // SelectModifier
namespace SelectInterfaceModifier {
void SetSelectOptionsImpl(Ark_NativePointer node,
                          const Array_SelectOption* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //SelectModelNG::SetSetSelectOptions(frameNode, convValue);
}
} // SelectInterfaceModifier
namespace SelectAttributeModifier {
void Selected0Impl(Ark_NativePointer node,
                   const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelected0(frameNode, convValue);
}
void Selected1Impl(Ark_NativePointer node,
                   const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelected1(frameNode, convValue);
}
void Value0Impl(Ark_NativePointer node,
                const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetValue0(frameNode, convValue);
}
void Value1Impl(Ark_NativePointer node,
                const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetValue1(frameNode, convValue);
}
void Font0Impl(Ark_NativePointer node,
               const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetFont0(frameNode, convValue);
}
void Font1Impl(Ark_NativePointer node,
               const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetFont1(frameNode, convValue);
}
void FontColor0Impl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetFontColor0(frameNode, convValue);
}
void FontColor1Impl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetFontColor1(frameNode, convValue);
}
void SelectedOptionBgColor0Impl(Ark_NativePointer node,
                                const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionBgColor0(frameNode, convValue);
}
void SelectedOptionBgColor1Impl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelectedOptionBgColor1(frameNode, convValue);
}
void SelectedOptionFont0Impl(Ark_NativePointer node,
                             const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionFont0(frameNode, convValue);
}
void SelectedOptionFont1Impl(Ark_NativePointer node,
                             const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelectedOptionFont1(frameNode, convValue);
}
void SelectedOptionFontColor0Impl(Ark_NativePointer node,
                                  const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionFontColor0(frameNode, convValue);
}
void SelectedOptionFontColor1Impl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelectedOptionFontColor1(frameNode, convValue);
}
void OptionBgColor0Impl(Ark_NativePointer node,
                        const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionBgColor0(frameNode, convValue);
}
void OptionBgColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionBgColor1(frameNode, convValue);
}
void OptionFont0Impl(Ark_NativePointer node,
                     const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionFont0(frameNode, convValue);
}
void OptionFont1Impl(Ark_NativePointer node,
                     const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionFont1(frameNode, convValue);
}
void OptionFontColor0Impl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionFontColor0(frameNode, convValue);
}
void OptionFontColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionFontColor1(frameNode, convValue);
}
void OnSelect0Impl(Ark_NativePointer node,
                   const Callback_Number_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOnSelect0(frameNode, convValue);
}
void OnSelect1Impl(Ark_NativePointer node,
                   const Opt_OnSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOnSelect1(frameNode, convValue);
}
void Space0Impl(Ark_NativePointer node,
                const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSpace0(frameNode, convValue);
}
void Space1Impl(Ark_NativePointer node,
                const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSpace1(frameNode, convValue);
}
void ArrowPosition0Impl(Ark_NativePointer node,
                        Ark_ArrowPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetArrowPosition0(frameNode, convValue);
}
void ArrowPosition1Impl(Ark_NativePointer node,
                        const Opt_ArrowPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetArrowPosition1(frameNode, convValue);
}
void OptionWidth0Impl(Ark_NativePointer node,
                      const Ark_Union_Dimension_OptionWidthMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionWidth0(frameNode, convValue);
}
void OptionWidth1Impl(Ark_NativePointer node,
                      const Opt_Union_Dimension_OptionWidthMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionWidth1(frameNode, convValue);
}
void OptionHeight0Impl(Ark_NativePointer node,
                       const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionHeight0(frameNode, convValue);
}
void OptionHeight1Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionHeight1(frameNode, convValue);
}
void MenuBackgroundColor0Impl(Ark_NativePointer node,
                              const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetMenuBackgroundColor0(frameNode, convValue);
}
void MenuBackgroundColor1Impl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetMenuBackgroundColor1(frameNode, convValue);
}
void MenuBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                  Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetMenuBackgroundBlurStyle0(frameNode, convValue);
}
void MenuBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                  const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetMenuBackgroundBlurStyle1(frameNode, convValue);
}
void ControlSize0Impl(Ark_NativePointer node,
                      Ark_ControlSize value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetControlSize0(frameNode, convValue);
}
void ControlSize1Impl(Ark_NativePointer node,
                      const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetControlSize1(frameNode, convValue);
}
void MenuItemContentModifier0Impl(Ark_NativePointer node,
                                  const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetMenuItemContentModifier0(frameNode, convValue);
}
void MenuItemContentModifier1Impl(Ark_NativePointer node,
                                  const Opt_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetMenuItemContentModifier1(frameNode, convValue);
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetDivider(frameNode, convValue);
}
void TextModifierImpl(Ark_NativePointer node,
                      const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetTextModifier(frameNode, convValue);
}
void ArrowModifierImpl(Ark_NativePointer node,
                       const Opt_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetArrowModifier(frameNode, convValue);
}
void OptionTextModifierImpl(Ark_NativePointer node,
                            const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionTextModifier(frameNode, convValue);
}
void SelectedOptionTextModifierImpl(Ark_NativePointer node,
                                    const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelectedOptionTextModifier(frameNode, convValue);
}
void MenuAlign0Impl(Ark_NativePointer node,
                    Ark_MenuAlignType alignType,
                    const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(alignType);
    //auto convValue = Converter::OptConvert<type>(alignType); // for enums
    //SelectModelNG::SetMenuAlign0(frameNode, convValue);
}
void MenuAlign1Impl(Ark_NativePointer node,
                    const Opt_MenuAlignType* alignType,
                    const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(alignType);
    //auto convValue = Converter::OptConvert<type>(alignType); // for enums
    //SelectModelNG::SetMenuAlign1(frameNode, convValue);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Union_Number_Resource_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //SelectModelNG::Set_onChangeEvent_selected(frameNode, convValue);
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    //auto convValue = Converter::OptConvert<type_name>(*callback);
    //SelectModelNG::Set_onChangeEvent_value(frameNode, convValue);
}
} // SelectAttributeModifier
const GENERATED_ArkUISelectModifier* GetSelectModifier()
{
    static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
        SelectModifier::ConstructImpl,
        SelectInterfaceModifier::SetSelectOptionsImpl,
        SelectAttributeModifier::Selected0Impl,
        SelectAttributeModifier::Selected1Impl,
        SelectAttributeModifier::Value0Impl,
        SelectAttributeModifier::Value1Impl,
        SelectAttributeModifier::Font0Impl,
        SelectAttributeModifier::Font1Impl,
        SelectAttributeModifier::FontColor0Impl,
        SelectAttributeModifier::FontColor1Impl,
        SelectAttributeModifier::SelectedOptionBgColor0Impl,
        SelectAttributeModifier::SelectedOptionBgColor1Impl,
        SelectAttributeModifier::SelectedOptionFont0Impl,
        SelectAttributeModifier::SelectedOptionFont1Impl,
        SelectAttributeModifier::SelectedOptionFontColor0Impl,
        SelectAttributeModifier::SelectedOptionFontColor1Impl,
        SelectAttributeModifier::OptionBgColor0Impl,
        SelectAttributeModifier::OptionBgColor1Impl,
        SelectAttributeModifier::OptionFont0Impl,
        SelectAttributeModifier::OptionFont1Impl,
        SelectAttributeModifier::OptionFontColor0Impl,
        SelectAttributeModifier::OptionFontColor1Impl,
        SelectAttributeModifier::OnSelect0Impl,
        SelectAttributeModifier::OnSelect1Impl,
        SelectAttributeModifier::Space0Impl,
        SelectAttributeModifier::Space1Impl,
        SelectAttributeModifier::ArrowPosition0Impl,
        SelectAttributeModifier::ArrowPosition1Impl,
        SelectAttributeModifier::OptionWidth0Impl,
        SelectAttributeModifier::OptionWidth1Impl,
        SelectAttributeModifier::OptionHeight0Impl,
        SelectAttributeModifier::OptionHeight1Impl,
        SelectAttributeModifier::MenuBackgroundColor0Impl,
        SelectAttributeModifier::MenuBackgroundColor1Impl,
        SelectAttributeModifier::MenuBackgroundBlurStyle0Impl,
        SelectAttributeModifier::MenuBackgroundBlurStyle1Impl,
        SelectAttributeModifier::ControlSize0Impl,
        SelectAttributeModifier::ControlSize1Impl,
        SelectAttributeModifier::MenuItemContentModifier0Impl,
        SelectAttributeModifier::MenuItemContentModifier1Impl,
        SelectAttributeModifier::DividerImpl,
        SelectAttributeModifier::TextModifierImpl,
        SelectAttributeModifier::ArrowModifierImpl,
        SelectAttributeModifier::OptionTextModifierImpl,
        SelectAttributeModifier::SelectedOptionTextModifierImpl,
        SelectAttributeModifier::MenuAlign0Impl,
        SelectAttributeModifier::MenuAlign1Impl,
        SelectAttributeModifier::_onChangeEvent_selectedImpl,
        SelectAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
