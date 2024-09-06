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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace AlphabetIndexerInterfaceModifier {
void SetAlphabetIndexerOptionsImpl(Ark_NativePointer node,
                                   const Ark_AlphabetIndexerOptions* options)
{
}
} // AlphabetIndexerInterfaceModifier
namespace AlphabetIndexerAttributeModifier {
void OnSelectedImpl(Ark_NativePointer node,
                    Ark_Function callback)
{
}
void ColorImpl(Ark_NativePointer node,
               const ResourceColor* value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
}
void PopupColorImpl(Ark_NativePointer node,
                    const ResourceColor* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
}
void PopupBackgroundImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
}
void PopupSelectedColorImpl(Ark_NativePointer node,
                            const ResourceColor* value)
{
}
void PopupUnselectedColorImpl(Ark_NativePointer node,
                              const ResourceColor* value)
{
}
void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                  const ResourceColor* value)
{
}
void UsingPopupImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
}
void SelectedFontImpl(Ark_NativePointer node,
                      const Ark_Font* value)
{
}
void PopupFontImpl(Ark_NativePointer node,
                   const Ark_Font* value)
{
}
void PopupItemFontImpl(Ark_NativePointer node,
                       const Ark_Font* value)
{
}
void ItemSizeImpl(Ark_NativePointer node,
                  const Type_AlphabetIndexerAttribute_itemSize_Arg0* value)
{
}
void FontImpl(Ark_NativePointer node,
              const Ark_Font* value)
{
}
void AlignStyleImpl(Ark_NativePointer node,
                    Ark_Int32 value,
                    const Opt_Length* offset)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
}
void OnRequestPopupDataImpl(Ark_NativePointer node,
                            Ark_Function callback)
{
}
void OnPopupSelectImpl(Ark_NativePointer node,
                       Ark_Function callback)
{
}
void SelectedImpl(Ark_NativePointer node,
                  const Ark_Number* index)
{
}
void PopupPositionImpl(Ark_NativePointer node,
                       const Ark_Position* value)
{
}
void AutoCollapseImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
}
void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                               const Ark_Number* value)
{
}
void ItemBorderRadiusImpl(Ark_NativePointer node,
                          const Ark_Number* value)
{
}
void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                  Ark_Int32 value)
{
}
void PopupTitleBackgroundImpl(Ark_NativePointer node,
                              const ResourceColor* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
}
} // AlphabetIndexerAttributeModifier
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
        AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
        AlphabetIndexerAttributeModifier::OnSelectedImpl,
        AlphabetIndexerAttributeModifier::ColorImpl,
        AlphabetIndexerAttributeModifier::SelectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupColorImpl,
        AlphabetIndexerAttributeModifier::SelectedBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::PopupBackgroundImpl,
        AlphabetIndexerAttributeModifier::PopupSelectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupUnselectedColorImpl,
        AlphabetIndexerAttributeModifier::PopupItemBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::UsingPopupImpl,
        AlphabetIndexerAttributeModifier::SelectedFontImpl,
        AlphabetIndexerAttributeModifier::PopupFontImpl,
        AlphabetIndexerAttributeModifier::PopupItemFontImpl,
        AlphabetIndexerAttributeModifier::ItemSizeImpl,
        AlphabetIndexerAttributeModifier::FontImpl,
        AlphabetIndexerAttributeModifier::AlignStyleImpl,
        AlphabetIndexerAttributeModifier::OnSelectImpl,
        AlphabetIndexerAttributeModifier::OnRequestPopupDataImpl,
        AlphabetIndexerAttributeModifier::OnPopupSelectImpl,
        AlphabetIndexerAttributeModifier::SelectedImpl,
        AlphabetIndexerAttributeModifier::PopupPositionImpl,
        AlphabetIndexerAttributeModifier::AutoCollapseImpl,
        AlphabetIndexerAttributeModifier::PopupItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::ItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::PopupBackgroundBlurStyleImpl,
        AlphabetIndexerAttributeModifier::PopupTitleBackgroundImpl,
        AlphabetIndexerAttributeModifier::EnableHapticFeedbackImpl,
    };
    return &ArkUIAlphabetIndexerModifierImpl;
}

}
