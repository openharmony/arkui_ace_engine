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
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //AlphabetIndexerModelNG::SetSetAlphabetIndexerOptions(frameNode, convValue);
}
} // AlphabetIndexerInterfaceModifier
namespace AlphabetIndexerAttributeModifier {
void SetColorImpl(Ark_NativePointer node,
                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetColor(frameNode, convValue);
}
void SetSelectedColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetSelectedColor(frameNode, convValue);
}
void SetPopupColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetPopupBackgroundImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupBackground(frameNode, convValue);
}
void SetPopupSelectedColorImpl(Ark_NativePointer node,
                               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupSelectedColor(frameNode, convValue);
}
void SetPopupUnselectedColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupUnselectedColor(frameNode, convValue);
}
void SetPopupItemBackgroundColorImpl(Ark_NativePointer node,
                                     const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupItemBackgroundColor(frameNode, convValue);
}
void SetUsingPopupImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetUsingPopup(frameNode, convValue);
}
void SetSelectedFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetSelectedFont(frameNode, convValue);
}
void SetPopupFontImpl(Ark_NativePointer node,
                      const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupFont(frameNode, convValue);
}
void SetPopupItemFontImpl(Ark_NativePointer node,
                          const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupItemFont(frameNode, convValue);
}
void SetItemSizeImpl(Ark_NativePointer node,
                     const Opt_Union_String_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetItemSize(frameNode, convValue);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetFont(frameNode, convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_OnAlphabetIndexerSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetOnSelect(frameNode, convValue);
}
void SetOnRequestPopupDataImpl(Ark_NativePointer node,
                               const Opt_OnAlphabetIndexerRequestPopupDataCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetOnRequestPopupData(frameNode, convValue);
}
void SetOnPopupSelectImpl(Ark_NativePointer node,
                          const Opt_OnAlphabetIndexerPopupSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetOnPopupSelect(frameNode, convValue);
}
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetSelected(frameNode, convValue);
}
void SetPopupPositionImpl(Ark_NativePointer node,
                          const Opt_Position* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupPosition(frameNode, convValue);
}
void SetAutoCollapseImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetAutoCollapse(frameNode, convValue);
}
void SetPopupItemBorderRadiusImpl(Ark_NativePointer node,
                                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupItemBorderRadius(frameNode, convValue);
}
void SetItemBorderRadiusImpl(Ark_NativePointer node,
                             const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetItemBorderRadius(frameNode, convValue);
}
void SetPopupBackgroundBlurStyleImpl(Ark_NativePointer node,
                                     const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupBackgroundBlurStyle(frameNode, convValue);
}
void SetPopupTitleBackgroundImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetPopupTitleBackground(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //AlphabetIndexerModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetAlignStyleImpl(Ark_NativePointer node,
                       const Opt_IndexerAlign* value,
                       const Opt_Length* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //AlphabetIndexerModelNG::SetSetAlignStyle(frameNode, convValue);
}
} // AlphabetIndexerAttributeModifier
const GENERATED_ArkUIAlphabetIndexerModifier* GetAlphabetIndexerModifier()
{
    static const GENERATED_ArkUIAlphabetIndexerModifier ArkUIAlphabetIndexerModifierImpl {
        AlphabetIndexerModifier::ConstructImpl,
        AlphabetIndexerInterfaceModifier::SetAlphabetIndexerOptionsImpl,
        AlphabetIndexerAttributeModifier::SetColorImpl,
        AlphabetIndexerAttributeModifier::SetSelectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupColorImpl,
        AlphabetIndexerAttributeModifier::SetSelectedBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupBackgroundImpl,
        AlphabetIndexerAttributeModifier::SetPopupSelectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupUnselectedColorImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemBackgroundColorImpl,
        AlphabetIndexerAttributeModifier::SetUsingPopupImpl,
        AlphabetIndexerAttributeModifier::SetSelectedFontImpl,
        AlphabetIndexerAttributeModifier::SetPopupFontImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemFontImpl,
        AlphabetIndexerAttributeModifier::SetItemSizeImpl,
        AlphabetIndexerAttributeModifier::SetFontImpl,
        AlphabetIndexerAttributeModifier::SetOnSelectImpl,
        AlphabetIndexerAttributeModifier::SetOnRequestPopupDataImpl,
        AlphabetIndexerAttributeModifier::SetOnPopupSelectImpl,
        AlphabetIndexerAttributeModifier::SetSelectedImpl,
        AlphabetIndexerAttributeModifier::SetPopupPositionImpl,
        AlphabetIndexerAttributeModifier::SetAutoCollapseImpl,
        AlphabetIndexerAttributeModifier::SetPopupItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::SetItemBorderRadiusImpl,
        AlphabetIndexerAttributeModifier::SetPopupBackgroundBlurStyleImpl,
        AlphabetIndexerAttributeModifier::SetPopupTitleBackgroundImpl,
        AlphabetIndexerAttributeModifier::SetEnableHapticFeedbackImpl,
        AlphabetIndexerAttributeModifier::SetAlignStyleImpl,
    };
    return &ArkUIAlphabetIndexerModifierImpl;
}

}
