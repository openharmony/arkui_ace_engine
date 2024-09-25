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
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/utility/validators.h"

namespace OHOS::Ace::NG {
namespace Converter {
template<>
void AssignCast(std::optional<ArrowPosition>& dst, const Ark_ArrowPosition& src)
{
    switch (src) {
        case ARK_ARROW_POSITION_END: dst = ArrowPosition::END; break;
        case ARK_ARROW_POSITION_START: dst = ArrowPosition::START; break;
        default: LOGE("Unexpected enum value in Ark_ArrowPosition: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<MenuAlignType>& dst, const Ark_MenuAlignType& src)
{
    switch (src) {
        case ARK_MENU_ALIGN_TYPE_START: dst = MenuAlignType::START; break;
        case ARK_MENU_ALIGN_TYPE_CENTER: dst = MenuAlignType::CENTER; break;
        case ARK_MENU_ALIGN_TYPE_END: dst = MenuAlignType::END; break;
        default: LOGE("Unexpected enum value in Ark_MenuAlignType: %{public}d", src);
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG

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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<int32_t>(*value);
    if (optValue && optValue.value() < -1) {
        optValue.reset();
    }
    SelectModelNG::SetSelected(frameNode, optValue);
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionBgColorImpl(Ark_NativePointer node,
                               const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetSelectedOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionFontImpl(Ark_NativePointer node,
                            const Ark_Font* value)
{
}
void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetSelectedOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionBgColorImpl(Ark_NativePointer node,
                       const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionFontImpl(Ark_NativePointer node,
                    const Ark_Font* value)
{
}
void OptionFontColorImpl(Ark_NativePointer node,
                         const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSelect = [frameNode](int32_t index, const std::string& value) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkValue = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getSelectEventsReceiver()->onSelect(frameNode->GetId(), arkIndex, arkValue);
    };
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
}
void SpaceImpl(Ark_NativePointer node,
               const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    Validator::ValidateNonPercent(valueOpt);
    SelectModelNG::SetSpace(frameNode, valueOpt);
}
void ArrowPositionImpl(Ark_NativePointer node,
                       enum Ark_ArrowPosition value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetArrowPosition(frameNode, Converter::OptConvert<ArrowPosition>(value));
}
void MenuAlignImpl(Ark_NativePointer node,
                   enum Ark_MenuAlignType alignType,
                   const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(offset);
    auto menuAlignType = Converter::OptConvert<MenuAlignType>(alignType);
    auto dimensionOffset = Converter::OptConvert<DimensionOffset>(*offset);
    MenuAlign menuAlign;
    if (menuAlignType) {
        menuAlign.alignType = menuAlignType.value();
    }
    if (dimensionOffset) {
        menuAlign.offset = dimensionOffset.value();
    }
    SelectModelNG::SetMenuAlign(frameNode, menuAlign);
}
void OptionWidthImpl(Ark_NativePointer node,
                     const Type_SelectAttribute_optionWidth_Arg0* value)
{
}
void OptionHeightImpl(Ark_NativePointer node,
                      const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(optValue);
    SelectModelNG::SetOptionHeight(frameNode, optValue);
}
void MenuBackgroundColorImpl(Ark_NativePointer node,
                             const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    SelectModelNG::SetMenuBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
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
