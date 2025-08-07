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
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

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
namespace SelectAttributeModifier {
    void Selected1Impl(Ark_NativePointer node, const Opt_Union_Number_Resource* value);
    void Font1Impl(Ark_NativePointer node, const Opt_Font* value);
    void SelectedOptionFont1Impl(Ark_NativePointer node, const Opt_Font* value);
    void OptionFont1Impl(Ark_NativePointer node, const Opt_Font* value);
    void Space1Impl(Ark_NativePointer node, const Opt_Length* value);
    void OptionWidth1Impl(Ark_NativePointer node,
        const Opt_Union_Dimension_OptionWidthMode* value);
    void OptionHeight1Impl(Ark_NativePointer node, const Opt_Length* value);
    void MenuBackgroundBlurStyle1Impl(Ark_NativePointer node, const Opt_BlurStyle* value);
    void MenuAlign1Impl(Ark_NativePointer node, const Opt_MenuAlignType* alignType, const Opt_Offset* offset);
}
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
                   const Opt_Union_Number_Resource* value)
{
    Selected1Impl(node, value);
}
void Selected1Impl(Ark_NativePointer node,
                   const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::GetOpt(*value) : std::nullopt;
    auto convVal = arkVal.has_value() ? Converter::OptConvert<int32_t>(arkVal.value()) : std::nullopt;
    Validator::ValidateNonNegative(convVal);
    SelectModelStatic::SetSelected(frameNode, convVal);
}
void Value0Impl(Ark_NativePointer node,
                const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<std::string>(*value);
    SelectModelStatic::SetValue(frameNode, optValue);
}
void Value1Impl(Ark_NativePointer node,
                const Opt_ResourceStr* value)
{
    Value0Impl(node, value);
}
void Font0Impl(Ark_NativePointer node,
               const Opt_Font* value)
{
    Font1Impl(node, value);
}
void Font1Impl(Ark_NativePointer node,
               const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::OptConvert<Font>(*value) : std::nullopt;
    if (arkVal.has_value()) {
        SelectModelStatic::SetFontSize(frameNode, arkVal->fontSize);
        SelectModelStatic::SetFontWeight(frameNode, arkVal->fontWeight);
        SelectModelNG::SetFontFamily(frameNode, arkVal->fontFamilies);
        SelectModelStatic::SetItalicFontStyle(frameNode, arkVal->fontStyle);
    } else {
        SelectModelStatic::SetFontSize(frameNode, std::nullopt);
        SelectModelStatic::SetFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetFontFamily(frameNode, {});
        SelectModelStatic::SetItalicFontStyle(frameNode, std::nullopt);
    }
}
void FontColor0Impl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontColor1Impl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    FontColor0Impl(node, value);
}
void SelectedOptionBgColor0Impl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionBgColor1Impl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
{
    SelectedOptionBgColor0Impl(node, value);
}
void SelectedOptionFont0Impl(Ark_NativePointer node,
                             const Opt_Font* value)
{
    SelectedOptionFont1Impl(node, value);
}
void SelectedOptionFont1Impl(Ark_NativePointer node,
                             const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::OptConvert<Font>(*value) : std::nullopt;
    if (arkVal.has_value()) {
        auto font = Converter::Convert<Font>(arkVal.value());
        SelectModelStatic::SetSelectedOptionFontSize(frameNode, arkVal->fontSize);
        SelectModelStatic::SetSelectedOptionFontWeight(frameNode, arkVal->fontWeight);
        SelectModelNG::SetSelectedOptionFontFamily(frameNode, arkVal->fontFamilies);
        SelectModelStatic::SetSelectedOptionItalicFontStyle(frameNode, arkVal->fontStyle);
    } else {
        SelectModelStatic::SetFontSize(frameNode, std::nullopt);
        SelectModelStatic::SetFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetFontFamily(frameNode, {});
        SelectModelStatic::SetItalicFontStyle(frameNode, std::nullopt);
    }
}
void SelectedOptionFontColor0Impl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionFontColor1Impl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    SelectedOptionFontColor0Impl(node, value);
}
void OptionBgColor0Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionBgColor1Impl(Ark_NativePointer node,
                        const Opt_ResourceColor* value)
{
    OptionBgColor0Impl(node, value);
}
void OptionFont0Impl(Ark_NativePointer node,
                     const Opt_Font* value)
{
    OptionFont1Impl(node, value);
}
void OptionFont1Impl(Ark_NativePointer node,
                     const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::OptConvert<Font>(*value) : std::nullopt;
    if (arkVal.has_value()) {
        SelectModelStatic::SetOptionFontSize(frameNode, arkVal->fontSize);
        SelectModelStatic::SetOptionFontWeight(frameNode, arkVal->fontWeight);
        SelectModelNG::SetOptionFontFamily(frameNode, arkVal->fontFamilies);
        SelectModelStatic::SetOptionItalicFontStyle(frameNode, arkVal->fontStyle);
    } else {
        SelectModelStatic::SetFontSize(frameNode, std::nullopt);
        SelectModelStatic::SetFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetFontFamily(frameNode, {});
        SelectModelStatic::SetItalicFontStyle(frameNode, std::nullopt);
    }
}
void OptionFontColor0Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionFontColor1Impl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    OptionFontColor0Impl(node, value);
}
void OnSelect0Impl(Ark_NativePointer node,
                   const Opt_Callback_Number_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectEvent onSelect = {};
    auto optValue = Converter::GetOptPtr(value);
    if (optValue) {
        onSelect = [arkCallback = CallbackHelper(*optValue)](int32_t index, const std::string& value) {
            auto arkIndex = Converter::ArkValue<Ark_Number>(index);
            auto arkValue = Converter::ArkValue<Ark_String>(value);
            arkCallback.Invoke(arkIndex, arkValue);
        };
    }
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
}
void OnSelect1Impl(Ark_NativePointer node,
                   const Opt_OnSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectEvent onSelect = {};
    auto optValue = Converter::GetOptPtr(value);
    if (optValue) {
        onSelect = [arkCallback = CallbackHelper(*optValue)](int32_t index, const std::string& value) {
            auto arkIndex = Converter::ArkValue<Ark_Number>(index);
            auto arkValue = Converter::ArkValue<Ark_String>(value);
            arkCallback.Invoke(arkIndex, arkValue);
        };
    }
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
}
void Space0Impl(Ark_NativePointer node,
                const Opt_Length* value)
{
    Space1Impl(node, value);
}
void Space1Impl(Ark_NativePointer node,
                const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SelectModelStatic::SetSpace(frameNode, convValue);
}
void ArrowPosition0Impl(Ark_NativePointer node,
                        const Opt_ArrowPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetArrowPosition(frameNode, Converter::OptConvert<ArrowPosition>(*value));
}
void ArrowPosition1Impl(Ark_NativePointer node,
                        const Opt_ArrowPosition* value)
{
    ArrowPosition0Impl(node, value);
}
void OptionWidth0Impl(Ark_NativePointer node,
                      const Opt_Union_Dimension_OptionWidthMode* value)
{
    OptionWidth1Impl(node, value);
}
void OptionWidth1Impl(Ark_NativePointer node,
                      const Opt_Union_Dimension_OptionWidthMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkUnion = value ? Converter::GetOpt(*value) : std::nullopt;
    if (!arkUnion.has_value()) {
        SelectModelNG::SetHasOptionWidth(frameNode, true);
        SelectModelStatic::SetOptionWidth(frameNode, std::nullopt);
        return;
    }
    Converter::VisitUnion(arkUnion.value(),
        [frameNode](const Ark_Length& value) {
            auto width = Converter::OptConvert<Dimension>(value);
            Validator::ValidateNonNegative(width);
            Validator::ValidateNonPercent(width);
            SelectModelNG::SetHasOptionWidth(frameNode, true);
            SelectModelStatic::SetOptionWidth(frameNode, width);
        },
        [frameNode](const Ark_OptionWidthMode& value) {
            auto fit = Converter::OptConvert<bool>(value);
            SelectModelNG::SetHasOptionWidth(frameNode, true);
            SelectModelStatic::SetOptionWidthFitTrigger(frameNode, fit.value_or(true));
        },
        []() {}
    );
}
void OptionHeight0Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    OptionHeight1Impl(node, value);
}
void OptionHeight1Impl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidatePositive(convValue);
    Validator::ValidateNonPercent(convValue);
    SelectModelStatic::SetOptionHeight(frameNode, convValue);
}
void MenuBackgroundColor0Impl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetMenuBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void MenuBackgroundColor1Impl(Ark_NativePointer node,
                              const Opt_ResourceColor* value)
{
    MenuBackgroundColor0Impl(node, value);
}
void MenuBackgroundBlurStyle0Impl(Ark_NativePointer node,
                                  const Opt_BlurStyle* value)
{
    MenuBackgroundBlurStyle1Impl(node, value);
}
void MenuBackgroundBlurStyle1Impl(Ark_NativePointer node,
                                  const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<BlurStyle>(*value) : std::nullopt;
    BlurStyleOption option = {};
    if (convValue) {
        option.blurStyle = convValue.value();
    }
    SelectModelNG::SetMenuBackgroundBlurStyle(frameNode, option);
}
void ControlSize0Impl(Ark_NativePointer node,
                      const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetControlSize(frameNode, Converter::OptConvert<ControlSize>(*value));
}
void ControlSize1Impl(Ark_NativePointer node,
                      const Opt_ControlSize* value)
{
    ControlSize0Impl(node, value);
}
void MenuItemContentModifier0Impl(Ark_NativePointer node,
                                  const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MenuItemContentModifier1Impl(Ark_NativePointer node,
                                  const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_DividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = SelectModelStatic::GetDefaultDivider(frameNode);
    if (value->tag == INTEROP_TAG_UNDEFINED) {
        SelectModelStatic::SetDivider(frameNode, divider);
        return;
    }
    auto dividerOptions = value->value;
    auto strokeWidthOpt = Converter::OptConvert<Dimension>(dividerOptions.strokeWidth);
    Validator::ValidateNonNegative(strokeWidthOpt);
    Validator::ValidateNonPercent(strokeWidthOpt);
    if (strokeWidthOpt.has_value()) {
        divider.strokeWidth = strokeWidthOpt.value();
    }
    auto colorOpt = Converter::OptConvert<Color>(dividerOptions.color);
    if (colorOpt.has_value()) {
        divider.color = colorOpt.value();
    }
    auto startMarginOpt = Converter::OptConvert<Dimension>(dividerOptions.startMargin);
    Validator::ValidateNonNegative(startMarginOpt);
    Validator::ValidateNonPercent(startMarginOpt);
    if (startMarginOpt.has_value()) {
        divider.startMargin = startMarginOpt.value();
    }
    auto endMarginOpt = Converter::OptConvert<Dimension>(dividerOptions.endMargin);
    Validator::ValidateNonNegative(endMarginOpt);
    Validator::ValidateNonPercent(endMarginOpt);
    if (endMarginOpt.has_value()) {
        divider.endMargin = endMarginOpt.value();
    }
    std::optional<SelectDivider> dividerOpt = divider;
    SelectModelStatic::SetDivider(frameNode, dividerOpt);
}
void TextModifierImpl(Ark_NativePointer node,
                      const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void ArrowModifierImpl(Ark_NativePointer node,
                       const Opt_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OptionTextModifierImpl(Ark_NativePointer node,
                            const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SelectedOptionTextModifierImpl(Ark_NativePointer node,
                                    const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void DividerStyleImpl(Ark_NativePointer node,
                      const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void AvoidanceImpl(Ark_NativePointer node,
                   const Opt_AvoidanceMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MenuOutlineImpl(Ark_NativePointer node,
                     const Opt_MenuOutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void MenuAlign0Impl(Ark_NativePointer node,
                    const Opt_MenuAlignType* alignType,
                    const Opt_Offset* offset)
{
    MenuAlign1Impl(node, alignType, offset);
}
void MenuAlign1Impl(Ark_NativePointer node,
                    const Opt_MenuAlignType* alignType,
                    const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optAlignType = alignType ? Converter::OptConvert<MenuAlignType>(*alignType) : std::nullopt;
    auto optOffset = offset ? Converter::OptConvert<DimensionOffset>(*offset) : std::nullopt;
    MenuAlign menuAlign = {};
    if (optAlignType) {
        menuAlign.alignType = optAlignType.value();
    }
    if (optOffset) {
        menuAlign.offset = optOffset.value();
    }
    SelectModelNG::SetMenuAlign(frameNode, menuAlign);
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Union_Number_Resource_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](int32_t index) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Opt_Union_Number_Resource, Ark_Number>(index));
    };
    SelectModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_Opt_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
    auto onEvent = [arkCallback = CallbackHelper(*callback), weakNode](const std::string& value) {
        PipelineContext::SetCallBackNode(weakNode);
        arkCallback.Invoke(Converter::ArkUnion<Opt_ResourceStr, Ark_String>(value));
    };
    SelectModelStatic::SetValueChangeEvent(frameNode, std::move(onEvent));
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
        SelectAttributeModifier::DividerStyleImpl,
        SelectAttributeModifier::AvoidanceImpl,
        SelectAttributeModifier::MenuOutlineImpl,
        SelectAttributeModifier::MenuAlign0Impl,
        SelectAttributeModifier::MenuAlign1Impl,
        SelectAttributeModifier::_onChangeEvent_selectedImpl,
        SelectAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
