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

#include <variant>

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG {
using DimensionOrOptBool = std::variant<Dimension, std::optional<bool>>;

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

template<>
void AssignCast(std::optional<bool>& dst, const Ark_OptionWidthMode& src)
{
    switch (src) {
        case ARK_OPTION_WIDTH_MODE_FIT_CONTENT: dst = false; break;
        case ARK_OPTION_WIDTH_MODE_FIT_TRIGGER: dst = true; break;
        default: LOGE("Unexpected enum value in Ark_OptionWidthMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<DimensionOrOptBool>& dst, const Ark_OptionWidthMode& src)
{
    dst = Converter::OptConvert<bool>(src);
}

template<>
void AssignCast(std::optional<DimensionOrOptBool>& dst, const Ark_Length& src)
{
    dst = Converter::Convert<Dimension>(src);
}

template<>
SelectParam Convert(const Ark_SelectOption& src)
{
    SelectParam param;
    auto text = OptConvert<std::string>(src.value);
    if (text) {
        param.text = text.value();
    }
    auto icon = OptConvert<std::string>(src.icon);
    if (icon) {
        param.icon = icon.value();
    }
    return param;
}

template<>
SelectDivider Convert(const Ark_DividerOptions& src)
{
    auto dst = SelectDivider{}; // this struct is initialized by default
    auto strokeWidthOpt = OptConvert<Dimension>(src.strokeWidth);
    if (strokeWidthOpt.has_value()) {
        dst.strokeWidth = strokeWidthOpt.value();
    }
    auto colorOpt = OptConvert<Color>(src.color);
    if (colorOpt.has_value()) {
        dst.color = colorOpt.value();
    }
    auto startMarginOpt = OptConvert<Dimension>(src.startMargin);
    if (startMarginOpt.has_value()) {
        dst.startMargin = startMarginOpt.value();
    }
    auto endMarginOpt = OptConvert<Dimension>(src.endMargin);
    if (endMarginOpt.has_value()) {
        dst.endMargin = endMarginOpt.value();
    }
    return dst;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SelectModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SelectModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SelectModifier
namespace SelectInterfaceModifier {
void SetSelectOptionsImpl(Ark_NativePointer node,
                          const Array_SelectOption* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto params = Converter::Convert<std::vector<SelectParam>>(*options);
    SelectModelNG::InitSelect(frameNode, params);
}
} // SelectInterfaceModifier
namespace SelectAttributeModifier {
void Selected0Impl(Ark_NativePointer node,
                   const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<int32_t>(*value);
    if (optValue && optValue.value() < -1) {
        optValue.reset();
    }
    SelectModelNG::SetSelected(frameNode, optValue);
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
    auto optValue = Converter::OptConvert<std::string>(*value);
    SelectModelNG::SetValue(frameNode, optValue);
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
    auto font = Converter::OptConvert<Font>(*value);
    if (font) {
        SelectModelNG::SetFontSize(frameNode, font->fontSize);
        SelectModelNG::SetFontWeight(frameNode, font->fontWeight);
        SelectModelNG::SetFontFamily(frameNode, font->fontFamilies);
        SelectModelNG::SetItalicFontStyle(frameNode, font->fontStyle);
    } else {
        SelectModelNG::SetFontSize(frameNode, std::nullopt);
        SelectModelNG::SetFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetFontFamily(frameNode, {});
        SelectModelNG::SetItalicFontStyle(frameNode, std::nullopt);
    }
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
    SelectModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
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
    SelectModelNG::SetSelectedOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
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
    auto font = Converter::OptConvert<Font>(*value);
    if (font) {
        SelectModelNG::SetSelectedOptionFontSize(frameNode, font->fontSize);
        SelectModelNG::SetSelectedOptionFontWeight(frameNode, font->fontWeight);
        SelectModelNG::SetSelectedOptionFontFamily(frameNode, font->fontFamilies);
        SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, font->fontStyle);
    } else {
        SelectModelNG::SetSelectedOptionFontSize(frameNode, std::nullopt);
        SelectModelNG::SetSelectedOptionFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetSelectedOptionFontFamily(frameNode, {});
        SelectModelNG::SetSelectedOptionItalicFontStyle(frameNode, std::nullopt);
    }
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
    SelectModelNG::SetSelectedOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
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
    SelectModelNG::SetOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
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
    auto font = Converter::OptConvert<Font>(*value);
    if (font) {
        SelectModelNG::SetOptionFontSize(frameNode, font->fontSize);
        SelectModelNG::SetOptionFontWeight(frameNode, font->fontWeight);
        SelectModelNG::SetOptionFontFamily(frameNode, font->fontFamilies);
        SelectModelNG::SetOptionItalicFontStyle(frameNode, font->fontStyle);
    } else {
        SelectModelNG::SetOptionFontSize(frameNode, std::nullopt);
        SelectModelNG::SetOptionFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetOptionFontFamily(frameNode, {});
        SelectModelNG::SetOptionItalicFontStyle(frameNode, std::nullopt);
    }
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
    SelectModelNG::SetOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
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
    auto onSelect = [arkCallback = CallbackHelper(*value)](int32_t index, const std::string& value) {
        auto arkIndex = Converter::ArkValue<Ark_Number>(index);
        auto arkValue = Converter::ArkValue<Ark_String>(value);
        arkCallback.Invoke(arkIndex, arkValue);
    };
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
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
    auto valueOpt = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(valueOpt);
    Validator::ValidateNonPercent(valueOpt);
    SelectModelNG::SetSpace(frameNode, valueOpt);
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
    SelectModelNG::SetArrowPosition(frameNode, Converter::OptConvert<ArrowPosition>(value));
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
    auto converted = Converter::OptConvert<DimensionOrOptBool>(*value);
    if (!converted.has_value()) {
        LOGE("SelectAttributeModifier::OptionWidthImpl incorrect value");
    }
    if (auto widthPtr = std::get_if<Dimension>(&converted.value())) {
        std::optional<Dimension> width = *widthPtr;
        Validator::ValidateNonNegative(width);
        Validator::ValidateNonPercent(width);
        SelectModelNG::SetHasOptionWidth(frameNode, true);
        SelectModelNG::SetOptionWidth(frameNode, width);
    } else if (auto fitTriggerPtr = std::get_if<std::optional<bool>>(&converted.value())) {
        SelectModelNG::SetHasOptionWidth(frameNode, true);
        SelectModelNG::SetOptionWidthFitTrigger(frameNode, *fitTriggerPtr);
    } else {
        LOGE("SelectAttributeModifier::OptionWidthImpl incorrect value");
    }
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
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(optValue);
    SelectModelNG::SetOptionHeight(frameNode, optValue);
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
    SelectModelNG::SetMenuBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
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
    auto blurStyle = Converter::OptConvert<BlurStyle>(value);
    if (blurStyle) {
        BlurStyleOption option;
        option.blurStyle = blurStyle.value();
        SelectModelNG::SetMenuBackgroundBlurStyle(frameNode, option);
    }
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
    SelectModelNG::SetControlSize(frameNode, Converter::OptConvert<ControlSize>(value));
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
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<SelectDivider>(*value);
    SelectModelNG::SetDivider(frameNode, divider);
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
void MenuAlign0Impl(Ark_NativePointer node,
                    Ark_MenuAlignType alignType,
                    const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
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
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](int32_t index) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Ark_Union_Number_Resource, Ark_Number>(index));
    };
    SelectModelNG::SetSelectChangeEvent(frameNode, std::move(onEvent));
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Ark_ResourceStr, Ark_String>(value));
    };
    SelectModelNG::SetValueChangeEvent(frameNode, std::move(onEvent));
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
        SelectAttributeModifier::MenuAlign0Impl,
        SelectAttributeModifier::MenuAlign1Impl,
        SelectAttributeModifier::_onChangeEvent_selectedImpl,
        SelectAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
