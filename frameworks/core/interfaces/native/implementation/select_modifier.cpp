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
#include "core/components/common/properties/blur_style_option.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/select/select_model_ng.h"
#include "core/components_ng/pattern/select/select_model_static.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/implementation/text_modifier_peer.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"

namespace OHOS::Ace::NG {
constexpr uint32_t MENU_OUTLINE_COLOR = 0x19FFFFFF;
constexpr Dimension DEFAULT_OUTLINE_WIDTH = Dimension { -1 };
namespace Converter {
struct SelectDividerStyle {
    SelectDivider selectDivider;
    std::optional<DividerMode> dividerMode;
};

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
void AssignCast(std::optional<AvoidanceMode>& dst, const Ark_AvoidanceMode& src)
{
    switch (src) {
        case ARK_AVOIDANCE_MODE_COVER_TARGET:
            dst = AvoidanceMode::COVER_TARGET;
            break;
        case ARK_AVOIDANCE_MODE_AVOID_AROUND_TARGET:
            dst = AvoidanceMode::AVOID_AROUND_TARGET;
            break;
        default:
            LOGE("Unexpected enum value in Ark_AvoidanceMode: %{public}d", src);
    }
}

template<>
Avoidance Convert(const Ark_AvoidanceMode& src)
{
    Avoidance avoidance;
    auto mode = OptConvert<AvoidanceMode>(src);
    if (mode) {
        avoidance.mode = *mode;
    }
    return avoidance;
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
    auto symbolIcon = Converter::OptConvert<Ark_SymbolGlyphModifier>(src.symbolIcon);
    if (symbolIcon && *symbolIcon) {
        param.symbolIcon = (*symbolIcon)->symbolApply;
        PeerUtils::DestroyPeer(*symbolIcon);
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

template<>
SelectDividerStyle Convert(const Ark_DividerStyleOptions& src)
{
    SelectDivider dst;
    auto colorOpt = OptConvert<Color>(src.color);
    if (colorOpt.has_value()) {
        dst.color = *colorOpt;
    }
    auto strokeWidth = OptConvert<Dimension>(src.strokeWidth);
    Validator::ValidateNonNegative(strokeWidth);
    if (strokeWidth.has_value()) {
        dst.strokeWidth = strokeWidth.value();
    }
    auto startMargin = OptConvert<Dimension>(src.startMargin);
    Validator::ValidateNonNegative(startMargin);
    if (startMargin.has_value()) {
        dst.startMargin = startMargin.value();
    }
    auto endMargin = OptConvert<Dimension>(src.endMargin);
    Validator::ValidateNonNegative(endMargin);
    if (endMargin.has_value()) {
        dst.endMargin = endMargin.value();
    }
    return {
        .selectDivider = dst,
        .dividerMode = OptConvert<OHOS::Ace::DividerMode>(src.mode),
    };
}

void SetMenuOutlineWidthMultiValued(std::optional<Dimension>& dst, std::optional<Dimension>& dimensionOpt)
{
    CHECK_EQUAL_VOID(dimensionOpt.has_value(), false);
    Validator::ValidateNonNegative(dimensionOpt);
    Validator::ValidateNonPercent(dimensionOpt);
    dst = dimensionOpt;
}

template<>
MenuParam Convert(const Ark_MenuOutlineOptions& src)
{
    MenuParam dst;
    BorderWidthProperty outlineWidth;
    auto outlineWidthOpt = OptConvert<BorderWidthProperty>(src.width);
    if (outlineWidthOpt.has_value()) {
        auto outlineWidthValue = outlineWidthOpt.value();
        if (outlineWidthValue.multiValued) {
            SetMenuOutlineWidthMultiValued(outlineWidth.leftDimen, outlineWidthValue.leftDimen);
            SetMenuOutlineWidthMultiValued(outlineWidth.rightDimen, outlineWidthValue.rightDimen);
            SetMenuOutlineWidthMultiValued(outlineWidth.topDimen, outlineWidthValue.topDimen);
            SetMenuOutlineWidthMultiValued(outlineWidth.bottomDimen, outlineWidthValue.bottomDimen);
        } else {
            auto borderWidth = outlineWidthValue.topDimen.value_or(DEFAULT_OUTLINE_WIDTH);
            auto validBorderWidth = (borderWidth.IsNegative() || borderWidth.Unit() == DimensionUnit::PERCENT)
                                        ? DEFAULT_OUTLINE_WIDTH
                                        : borderWidth;
            outlineWidth.SetBorderWidth(validBorderWidth);
        }
    } else {
        outlineWidth.SetBorderWidth(DEFAULT_OUTLINE_WIDTH);
    }
    dst.outlineWidth = outlineWidth;

    BorderColorProperty outlineColor;
    auto outlineColorOpt = OptConvert<BorderColorProperty>(src.color);
    if (outlineColorOpt.has_value()) {
        outlineColor = outlineColorOpt.value();
        if (outlineColor.multiValued) {
            Color defaultColor = Color::TRANSPARENT;
            outlineColor.leftColor = outlineColor.leftColor.value_or(defaultColor);
            outlineColor.rightColor = outlineColor.rightColor.value_or(defaultColor);
            outlineColor.topColor = outlineColor.topColor.value_or(defaultColor);
            outlineColor.bottomColor = outlineColor.bottomColor.value_or(defaultColor);
        }
    } else {
        outlineColor.SetColor(Color(MENU_OUTLINE_COLOR));
    }
    dst.outlineColor = outlineColor;
    return dst;
}
} // namespace Converter
namespace {
std::optional<std::string> ProcessBindableValue(FrameNode* frameNode,
    const Opt_Union_ResourceStr_Bindable_Bindable* value)
{
    std::optional<std::string> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_ResourceStr& src) {
            result = Converter::OptConvert<std::string>(src);
        },
        [&result, frameNode](const Ark_Bindable_String& src) {
            result = Converter::OptConvert<std::string>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](const std::string& value) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_String>(value));
            };
            SelectModelStatic::SetValueChangeEvent(frameNode, std::move(onEvent));
        },
        [](const Ark_Bindable_Global_Resource_Resource& src) {
            // Invalid case, should be deleted from SDK
        },
        [] {});
    return result;
}
std::optional<int32_t> ProcessBindableSelected(FrameNode* frameNode,
    const Opt_Union_I32_Resource_Bindable_Bindable* value)
{
    std::optional<int32_t> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Int32& src) {
            result = Converter::OptConvert<int32_t>(src);
        },
        [&result](const Ark_Resource& src) {
            result = Converter::OptConvert<int32_t>(src);
        },
        [&result, frameNode](const Ark_Bindable_I32& src) {
            result = Converter::Convert<int32_t>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](int32_t index) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(index));
            };
            SelectModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
        },
        [](const Ark_Bindable_Global_Resource_Resource& src) {
            // Invalid case, should be deleted from SDK
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SelectAttributeModifier {
    void Selected1Impl(Ark_NativePointer node, const Opt_Union_I32_Resource* value);
    void Font1Impl(Ark_NativePointer node, const Opt_Font* value);
    void SelectedOptionFont1Impl(Ark_NativePointer node, const Opt_Font* value);
    void OptionFont1Impl(Ark_NativePointer node, const Opt_Font* value);
    void Space1Impl(Ark_NativePointer node, const Opt_Length* value);
    void OptionWidth1Impl(Ark_NativePointer node,
        const Opt_Union_Dimension_OptionWidthMode* value);
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
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_I32_Resource_Bindable_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convVal = ProcessBindableSelected(frameNode, value);
    if (convVal.has_value() && Negative(convVal.value())) {
        convVal = -1;
    }
    SelectModelStatic::SetSelected(frameNode, convVal);
}
void SetValueImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceStr_Bindable_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = ProcessBindableValue(frameNode, value);
    SelectModelStatic::SetValue(frameNode, optValue);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = Converter::OptConvertPtr<Font>(value);
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
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetSelectedOptionBgColorImpl(Ark_NativePointer node,
                                  const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionBgColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetSelectedOptionFontImpl(Ark_NativePointer node,
                               const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = Converter::OptConvertPtr<Font>(value);
    if (arkVal.has_value()) {
        auto font = Converter::Convert<Font>(arkVal.value());
        SelectModelStatic::SetSelectedOptionFontSize(frameNode, arkVal->fontSize);
        SelectModelStatic::SetSelectedOptionFontWeight(frameNode, arkVal->fontWeight);
        SelectModelNG::SetSelectedOptionFontFamily(frameNode, arkVal->fontFamilies);
        SelectModelStatic::SetSelectedOptionItalicFontStyle(frameNode, arkVal->fontStyle);
    } else {
        SelectModelStatic::SetSelectedOptionFontSize(frameNode, std::nullopt);
        SelectModelStatic::SetSelectedOptionFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetSelectedOptionFontFamily(frameNode, {});
        SelectModelStatic::SetSelectedOptionItalicFontStyle(frameNode, std::nullopt);
    }
}
void SetSelectedOptionFontColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetOptionBgColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionBgColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetOptionFontImpl(Ark_NativePointer node,
                       const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = Converter::OptConvertPtr<Font>(value);
    if (arkVal.has_value()) {
        SelectModelStatic::SetOptionFontSize(frameNode, arkVal->fontSize);
        SelectModelStatic::SetOptionFontWeight(frameNode, arkVal->fontWeight);
        SelectModelNG::SetOptionFontFamily(frameNode, arkVal->fontFamilies);
        SelectModelStatic::SetOptionItalicFontStyle(frameNode, arkVal->fontStyle);
    } else {
        SelectModelStatic::SetOptionFontSize(frameNode, std::nullopt);
        SelectModelStatic::SetOptionFontWeight(frameNode, std::nullopt);
        SelectModelNG::SetOptionFontFamily(frameNode, {});
        SelectModelStatic::SetOptionItalicFontStyle(frameNode, std::nullopt);
    }
}
void SetOptionFontColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_OnSelectCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectEvent onSelect = {};
    auto optValue = Converter::GetOptPtr(value);
    if (optValue) {
        onSelect = [arkCallback = CallbackHelper(*optValue)](int32_t index, const std::string& value) {
            auto arkIndex = Converter::ArkValue<Ark_Int32>(index);
            auto arkValue = Converter::ArkValue<Ark_String>(value);
            arkCallback.Invoke(arkIndex, arkValue);
        };
    }
    SelectModelNG::SetOnSelect(frameNode, std::move(onSelect));
}
void SetSpaceImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SelectModelStatic::SetSpace(frameNode, convValue);
}
void SetArrowPositionImpl(Ark_NativePointer node,
                          const Opt_ArrowPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetArrowPosition(frameNode, Converter::OptConvertPtr<ArrowPosition>(value));
}
void SetOptionWidthImpl(Ark_NativePointer node,
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
        [frameNode](const Ark_Dimension& value) {
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
void SetOptionHeightImpl(Ark_NativePointer node,
                         const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidatePositive(convValue);
    Validator::ValidateNonPercent(convValue);
    SelectModelStatic::SetOptionHeight(frameNode, convValue);
}
void SetMenuBackgroundColorImpl(Ark_NativePointer node,
                                const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetMenuBackgroundColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetMenuBackgroundBlurStyleImpl(Ark_NativePointer node,
                                    const Opt_BlurStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<BlurStyle>(value);
    BlurStyleOption option = {};
    if (convValue) {
        option.blurStyle = convValue.value();
    } else {
        option.blurStyle = BlurStyle::COMPONENT_ULTRA_THIN;
    }
    SelectModelNG::SetMenuBackgroundBlurStyle(frameNode, option);
}
void SetControlSizeImpl(Ark_NativePointer node,
                        const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetControlSize(frameNode, Converter::OptConvertPtr<ControlSize>(value));
}
void SetTextModifierImpl(Ark_NativePointer node,
                         const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == INTEROP_TAG_UNDEFINED || !value->value) {
        SelectModelStatic::SetTextModifierApply(frameNode, nullptr);
        return;
    }
    SelectModelStatic::SetTextModifierApply(frameNode, value->value->textApply);
}
void SetArrowModifierImpl(Ark_NativePointer node,
                          const Opt_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto symbolIcon = Converter::OptConvert<Ark_SymbolGlyphModifier>(*value);
    if (symbolIcon && *symbolIcon) {
        SelectModelStatic::SetArrowModifierApply(frameNode, (*symbolIcon)->symbolApply);
        PeerUtils::DestroyPeer(*symbolIcon);
        return;
    }
    SelectModelStatic::SetArrowModifierApply(frameNode, nullptr);
}
void SetOptionTextModifierImpl(Ark_NativePointer node,
                               const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == INTEROP_TAG_UNDEFINED || !value->value) {
        SelectModelStatic::SetOptionTextModifier(frameNode, nullptr);
        return;
    }
    SelectModelStatic::SetOptionTextModifier(frameNode, value->value->textApply);
}
void SetSelectedOptionTextModifierImpl(Ark_NativePointer node,
                                       const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag == INTEROP_TAG_UNDEFINED || !value->value) {
        SelectModelStatic::SetSelectedOptionTextModifier(frameNode, nullptr);
        return;
    }
    SelectModelStatic::SetSelectedOptionTextModifier(frameNode, value->value->textApply);
}
void SetDividerStyleImpl(Ark_NativePointer node,
                         const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto divider = Converter::OptConvertPtr<Converter::SelectDividerStyle>(value);
    if (divider) {
        SelectModelStatic::SetDividerStyle(frameNode, divider->selectDivider, divider->dividerMode);
    } else {
        SelectModelStatic::SetDivider(frameNode, std::nullopt);
    }
}
void SetAvoidanceImpl(Ark_NativePointer node,
                      const Opt_AvoidanceMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetAvoidance(frameNode, Converter::OptConvertPtr<Avoidance>(value));
}
void SetMenuOutlineImpl(Ark_NativePointer node,
                        const Opt_MenuOutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optConvert = Converter::OptConvertPtr<MenuParam>(value);
    if (!optConvert.has_value()) {
        optConvert = NG::MenuParam();
        SelectModelStatic::SetDefaultMenuParam(frameNode, optConvert.value());
    }
    optConvert->placement = Placement::BOTTOM_LEFT;
    SelectModelStatic::SetMenuOutline(frameNode, optConvert);
}
void SetShowInSubWindowImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optConvert = Converter::OptConvertPtr<bool>(value);
    SelectModelStatic::SetShowInSubWindow(frameNode, optConvert);
}
void SetShowDefaultSelectedIconImpl(Ark_NativePointer node, const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto optConvert = Converter::OptConvertPtr<bool>(value);
    SelectModelStatic::SetShowDefaultSelectedIcon(frameNode, optConvert);
}
void SetBackgroundColorImpl(Ark_NativePointer node,
                            const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetBackgroundColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetMenuAlignImpl(Ark_NativePointer node,
                      const Opt_MenuAlignType* alignType,
                      const Opt_Offset* offset)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optAlignType = Converter::OptConvertPtr<MenuAlignType>(alignType);
    auto optOffset = Converter::OptConvertPtr<DimensionOffset>(offset);
    MenuAlign menuAlign = {};
    if (optAlignType) {
        menuAlign.alignType = optAlignType.value();
    }
    if (optOffset) {
        menuAlign.offset = optOffset.value();
    }
    SelectModelNG::SetMenuAlign(frameNode, menuAlign);
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
        SelectAttributeModifier::SetTextModifierImpl,
        SelectAttributeModifier::SetArrowModifierImpl,
        SelectAttributeModifier::SetOptionTextModifierImpl,
        SelectAttributeModifier::SetSelectedOptionTextModifierImpl,
        SelectAttributeModifier::SetDividerStyleImpl,
        SelectAttributeModifier::SetAvoidanceImpl,
        SelectAttributeModifier::SetMenuOutlineImpl,
        SelectAttributeModifier::SetShowInSubWindowImpl,
        SelectAttributeModifier::SetShowDefaultSelectedIconImpl,
        SelectAttributeModifier::SetBackgroundColorImpl,
        SelectAttributeModifier::SetMenuAlignImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
