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
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSelected(frameNode, convValue);
}
void SetValueImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceStr_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetValue(frameNode, convValue);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetFont(frameNode, convValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetFontColor(frameNode, convValue);
}
void SetSelectedOptionBgColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSelectedOptionBgColor(frameNode, convValue);
}
void SetSelectedOptionFontImpl(Ark_NativePointer node,
                               const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSelectedOptionFont(frameNode, convValue);
}
void SetSelectedOptionFontColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSelectedOptionFontColor(frameNode, convValue);
}
void SetOptionBgColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionBgColor(frameNode, convValue);
}
void SetOptionFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionFont(frameNode, convValue);
}
void SetOptionFontColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionFontColor(frameNode, convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_OnSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOnSelect(frameNode, convValue);
}
void SetSpaceImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSpace(frameNode, convValue);
}
void SetArrowPositionImpl(Ark_NativePointer node,
                          const Opt_ArrowPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetArrowPosition(frameNode, convValue);
}
void SetOptionWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Dimension_OptionWidthMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionWidth(frameNode, convValue);
}
void SetOptionHeightImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionHeight(frameNode, convValue);
}
void SetMenuBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetMenuBackgroundColor(frameNode, convValue);
}
void SetMenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                    const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetMenuBackgroundBlurStyle(frameNode, convValue);
}
void SetControlSizeImpl(Ark_NativePointer node,
                        const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetControlSize(frameNode, convValue);
}
void SetMenuItemContentModifierImpl(Ark_NativePointer node,
                                    const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetMenuItemContentModifier(frameNode, convValue);
}
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetDivider(frameNode, convValue);
}
void SetTextModifierImpl(Ark_NativePointer node,
                         const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetTextModifier(frameNode, convValue);
}
void SetArrowModifierImpl(Ark_NativePointer node,
                          const Opt_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetArrowModifier(frameNode, convValue);
}
void SetOptionTextModifierImpl(Ark_NativePointer node,
                               const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetOptionTextModifier(frameNode, convValue);
}
void SetSelectedOptionTextModifierImpl(Ark_NativePointer node,
                                       const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetSelectedOptionTextModifier(frameNode, convValue);
}
void SetDividerStyleImpl(Ark_NativePointer node,
                         const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetDividerStyle(frameNode, convValue);
}
void SetAvoidanceImpl(Ark_NativePointer node,
                      const Opt_AvoidanceMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetAvoidance(frameNode, convValue);
}
void SetMenuOutlineImpl(Ark_NativePointer node,
                        const Opt_MenuOutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSetMenuOutline(frameNode, convValue);
}
void SetMenuAlignImpl(Ark_NativePointer node,
                      const Opt_MenuAlignType* alignType,
                      const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(alignType);
    //auto convValue = Converter::OptConvert<type>(alignType); // for enums
    //SelectModelNG::SetSetMenuAlign(frameNode, convValue);
}
} // SelectAttributeModifier
const GENERATED_ArkUISelectModifier* GetSelectModifier()
{
    static const GENERATED_ArkUISelectModifier ArkUISelectModifierImpl {
        SelectModifier::ConstructImpl,
        SelectInterfaceModifier::SetSelectOptionsImpl,
        SelectAttributeModifier::SetSelectedImpl,
        SelectAttributeModifier::SetValueImpl,
        SelectAttributeModifier::SetFontImpl,
        SelectAttributeModifier::SetFontColorImpl,
        SelectAttributeModifier::SetSelectedOptionBgColorImpl,
        SelectAttributeModifier::SetSelectedOptionFontImpl,
        SelectAttributeModifier::SetSelectedOptionFontColorImpl,
        SelectAttributeModifier::SetOptionBgColorImpl,
        SelectAttributeModifier::SetOptionFontImpl,
        SelectAttributeModifier::SetOptionFontColorImpl,
        SelectAttributeModifier::SetOnSelectImpl,
        SelectAttributeModifier::SetSpaceImpl,
        SelectAttributeModifier::SetArrowPositionImpl,
        SelectAttributeModifier::SetOptionWidthImpl,
        SelectAttributeModifier::SetOptionHeightImpl,
        SelectAttributeModifier::SetMenuBackgroundColorImpl,
        SelectAttributeModifier::SetMenuBackgroundBlurStyleImpl,
        SelectAttributeModifier::SetControlSizeImpl,
        SelectAttributeModifier::SetMenuItemContentModifierImpl,
        SelectAttributeModifier::SetDividerImpl,
        SelectAttributeModifier::SetTextModifierImpl,
        SelectAttributeModifier::SetArrowModifierImpl,
        SelectAttributeModifier::SetOptionTextModifierImpl,
        SelectAttributeModifier::SetSelectedOptionTextModifierImpl,
        SelectAttributeModifier::SetDividerStyleImpl,
        SelectAttributeModifier::SetAvoidanceImpl,
        SelectAttributeModifier::SetMenuOutlineImpl,
        SelectAttributeModifier::SetMenuAlignImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
