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
namespace SelectModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
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
void SelectedImpl(Ark_NativePointer node,
                  const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelected(frameNode, convValue);
}
void ValueImpl(Ark_NativePointer node,
               const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetValue(frameNode, convValue);
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetFont(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetFontColor(frameNode, convValue);
}
void SelectedOptionBgColorImpl(Ark_NativePointer node,
                               const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionBgColor(frameNode, convValue);
}
void SelectedOptionFontImpl(Ark_NativePointer node,
                            const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionFont(frameNode, convValue);
}
void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSelectedOptionFontColor(frameNode, convValue);
}
void OptionBgColorImpl(Ark_NativePointer node,
                       const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionBgColor(frameNode, convValue);
}
void OptionFontImpl(Ark_NativePointer node,
                    const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionFont(frameNode, convValue);
}
void OptionFontColorImpl(Ark_NativePointer node,
                         const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionFontColor(frameNode, convValue);
}
void OnSelectImpl(Ark_NativePointer node,
                  const Callback_Number_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOnSelect(frameNode, convValue);
}
void SpaceImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetSpace(frameNode, convValue);
}
void ArrowPositionImpl(Ark_NativePointer node,
                       Ark_ArrowPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetArrowPosition(frameNode, convValue);
}
void OptionWidthImpl(Ark_NativePointer node,
                     const Ark_Union_Dimension_OptionWidthMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionWidth(frameNode, convValue);
}
void OptionHeightImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetOptionHeight(frameNode, convValue);
}
void MenuBackgroundColorImpl(Ark_NativePointer node,
                             const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetMenuBackgroundColor(frameNode, convValue);
}
void MenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                 Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetMenuBackgroundBlurStyle(frameNode, convValue);
}
void ControlSizeImpl(Ark_NativePointer node,
                     Ark_ControlSize value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //SelectModelNG::SetControlSize(frameNode, convValue);
}
void MenuItemContentModifierImpl(Ark_NativePointer node,
                                 const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetMenuItemContentModifier(frameNode, convValue);
}
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_Opt_DividerOptions_Null* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //SelectModelNG::SetDivider(frameNode, convValue);
}
void MenuAlignImpl(Ark_NativePointer node,
                   Ark_MenuAlignType alignType,
                   const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(alignType);
    //auto convValue = Converter::OptConvert<type>(alignType); // for enums
    //SelectModelNG::SetMenuAlign(frameNode, convValue);
}
} // SelectAttributeModifier
const GENERATED_ArkUISelectModifier* GetSelectModifier()
{
    static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
        SelectModifier::ConstructImpl,
        SelectInterfaceModifier::SetSelectOptionsImpl,
        SelectAttributeModifier::SelectedImpl,
        SelectAttributeModifier::ValueImpl,
        SelectAttributeModifier::FontImpl,
        SelectAttributeModifier::FontColorImpl,
        SelectAttributeModifier::SelectedOptionBgColorImpl,
        SelectAttributeModifier::SelectedOptionFontImpl,
        SelectAttributeModifier::SelectedOptionFontColorImpl,
        SelectAttributeModifier::OptionBgColorImpl,
        SelectAttributeModifier::OptionFontImpl,
        SelectAttributeModifier::OptionFontColorImpl,
        SelectAttributeModifier::OnSelectImpl,
        SelectAttributeModifier::SpaceImpl,
        SelectAttributeModifier::ArrowPositionImpl,
        SelectAttributeModifier::OptionWidthImpl,
        SelectAttributeModifier::OptionHeightImpl,
        SelectAttributeModifier::MenuBackgroundColorImpl,
        SelectAttributeModifier::MenuBackgroundBlurStyleImpl,
        SelectAttributeModifier::ControlSizeImpl,
        SelectAttributeModifier::MenuItemContentModifierImpl,
        SelectAttributeModifier::DividerImpl,
        SelectAttributeModifier::MenuAlignImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
