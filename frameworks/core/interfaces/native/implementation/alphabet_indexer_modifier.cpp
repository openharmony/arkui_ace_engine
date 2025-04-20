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
namespace AlphabetIndexerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // AlphabetIndexerModifier
namespace AlphabetIndexerInterfaceModifier {
void SetAlphabetIndexerOptionsImpl(Ark_NativePointer node,
                                   const Ark_AlphabetIndexerOptions* options)
{
}
} // AlphabetIndexerInterfaceModifier
namespace AlphabetIndexerAttributeModifier {
void OnSelectedImpl(Ark_NativePointer node,
                    const Opt_Callback_Number_Void* value)
{
}
void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
}
void SelectedColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
}
void PopupColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
}
void PopupBackgroundImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
}
void PopupSelectedColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
}
void PopupUnselectedColorImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
}
void PopupItemBackgroundColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
}
void UsingPopupImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void SelectedFontImpl(Ark_NativePointer node,
                      const Opt_Font* value)
{
}
void PopupFontImpl(Ark_NativePointer node,
                   const Opt_Font* value)
{
}
void PopupItemFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
{
}
void ItemSizeImpl(Ark_NativePointer node,
                  const Opt_Union_String_Number* value)
{
}
void FontImpl(Ark_NativePointer node,
              const Opt_Font* value)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_OnAlphabetIndexerSelectCallback* value)
{
}
void OnRequestPopupDataImpl(Ark_NativePointer node,
                            const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
{
}
void OnPopupSelectImpl(Ark_NativePointer node,
                       const Opt_OnAlphabetIndexerPopupSelectCallback* value)
{
}
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void PopupPositionImpl(Ark_NativePointer node,
                       const Opt_Position* value)
{
}
void AutoCollapseImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void PopupItemBorderRadiusImpl(Ark_NativePointer node,
                               const Opt_Number* value)
{
}
void ItemBorderRadiusImpl(Ark_NativePointer node,
                          const Opt_Number* value)
{
}
void PopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                  const Opt_BlurStyle* value)
{
}
void PopupTitleBackgroundImpl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
}
void AlignStyleImpl(Ark_NativePointer node,
                    const Opt_IndexerAlign* value,
                    const Opt_Length* offset)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Number_Void* callback)
{
}
} // AlphabetIndexerAttributeModifier
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
        AlphabetIndexerModifier::ConstructImpl,
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
        AlphabetIndexerAttributeModifier::AlignStyleImpl,
        AlphabetIndexerAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIAlphabetIndexerModifierImpl;
}

}
