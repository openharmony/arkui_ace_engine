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

#include "arkoala_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/pattern/select/select_model_ng.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SelectInterfaceModifier {
void SetSelectOptionsImpl(Ark_NativePointer node,
                          const Array_SelectOption* options)
{
}
} // SelectInterfaceModifier
namespace SelectAttributeModifier {
void SelectedImpl(Ark_NativePointer node,
                  const Type_SelectAttribute_selected_Arg0* value)
{
}
void ValueImpl(Ark_NativePointer node,
               const ResourceStr* value)
{
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
}
void SelectedOptionBgColorImpl(Ark_NativePointer node,
                               const ResourceColor* value)
{
}
void SelectedOptionFontImpl(Ark_NativePointer node,
                            const Ark_Font* value)
{
}
void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
}
void OptionBgColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
}
void OptionFontImpl(Ark_NativePointer node,
                    const Ark_Font* value)
{
}
void OptionFontColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void SpaceImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
}
void ArrowPositionImpl(Ark_NativePointer node,
                       enum Ark_ArrowPosition value)
{
}
void MenuAlignImpl(Ark_NativePointer node,
                   enum Ark_MenuAlignType alignType,
                   const Opt_Offset* offset)
{
}
void OptionWidthImpl(Ark_NativePointer node,
                     const Type_SelectAttribute_optionWidth_Arg0* value)
{
}
void OptionHeightImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
}
void MenuBackgroundColorImpl(Ark_NativePointer node,
                             const ResourceColor* value)
{
}
void MenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                 enum Ark_BlurStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto blurStyle = Converter::OptConvert<BlurStyle>(value);
    if (blurStyle) {
        BlurStyleOption option;
        option.blurStyle = blurStyle.value();
        SelectModelNG::SetMenuBackgroundBlurStyle(frameNode, option);
    }
}
void ControlSizeImpl(Ark_NativePointer node,
                     enum Ark_ControlSize value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetControlSize(frameNode, Converter::OptConvert<ControlSize>(value));
}
void MenuItemContentModifierImpl(Ark_NativePointer node,
                                 const Ark_CustomObject* modifier)
{
}
void DividerImpl(Ark_NativePointer node,
                 const Type_SelectAttribute_divider_Arg0* options)
{
}
} // SelectAttributeModifier
const GENERATED_ArkUISelectModifier* GetSelectModifier()
{
    static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
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
        SelectAttributeModifier::MenuAlignImpl,
        SelectAttributeModifier::OptionWidthImpl,
        SelectAttributeModifier::OptionHeightImpl,
        SelectAttributeModifier::MenuBackgroundColorImpl,
        SelectAttributeModifier::MenuBackgroundBlurStyleImpl,
        SelectAttributeModifier::ControlSizeImpl,
        SelectAttributeModifier::MenuItemContentModifierImpl,
        SelectAttributeModifier::DividerImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
