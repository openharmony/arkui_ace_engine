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
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkVal = value ? Converter::GetOpt(*value) : std::nullopt;
    auto convVal = arkVal.has_value() ? Converter::OptConvert<int32_t>(arkVal.value()) : std::nullopt;
    Validator::ValidateNonNegative(convVal);
    SelectModelStatic::SetSelected(frameNode, convVal);
}
void ValueImpl(Ark_NativePointer node,
               const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<std::string>(*value);
    SelectModelStatic::SetValue(frameNode, optValue);
}
void FontImpl(Ark_NativePointer node,
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
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionBgColorImpl(Ark_NativePointer node,
                               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void SelectedOptionFontImpl(Ark_NativePointer node,
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
void SelectedOptionFontColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetSelectedOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionBgColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionBgColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OptionFontImpl(Ark_NativePointer node,
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
void OptionFontColorImpl(Ark_NativePointer node,
                         const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetOptionFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSelectImpl(Ark_NativePointer node,
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
void SpaceImpl(Ark_NativePointer node,
               const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SelectModelStatic::SetSpace(frameNode, convValue);
}
void ArrowPositionImpl(Ark_NativePointer node,
                       const Opt_ArrowPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetArrowPosition(frameNode, Converter::OptConvert<ArrowPosition>(*value));
}
void OptionWidthImpl(Ark_NativePointer node,
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
void OptionHeightImpl(Ark_NativePointer node,
                      const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidatePositive(convValue);
    SelectModelStatic::SetOptionHeight(frameNode, convValue);
}
void MenuBackgroundColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelStatic::SetMenuBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void MenuBackgroundBlurStyleImpl(Ark_NativePointer node,
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
void ControlSizeImpl(Ark_NativePointer node,
                     const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SelectModelNG::SetControlSize(frameNode, Converter::OptConvert<ControlSize>(*value));
}
void MenuItemContentModifier0Impl(Ark_NativePointer node,
                                  const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetMenuItemContentModifier0(frameNode, convValue);
}
void MenuItemContentModifier1Impl(Ark_NativePointer node,
                                  const Opt_ContentModifier* value)
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
    SelectModelStatic::SetDivider(frameNode, divider);
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
void OptionTextModifierImpl(Ark_NativePointer node,
                            const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetOptionTextModifier(frameNode, convValue);
}
void SelectedOptionTextModifierImpl(Ark_NativePointer node,
                                    const Opt_TextModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetSelectedOptionTextModifier(frameNode, convValue);
}
void DividerStyleImpl(Ark_NativePointer node,
                      const Opt_DividerStyleOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetDividerStyle(frameNode, convValue);
}
void AvoidanceImpl(Ark_NativePointer node,
                   const Opt_AvoidanceMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetAvoidance(frameNode, convValue);
}
void MenuOutlineImpl(Ark_NativePointer node,
                     const Opt_MenuOutlineOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //SelectModelNG::SetMenuOutline(frameNode, convValue);
}
void MenuAlignImpl(Ark_NativePointer node,
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
        SelectAttributeModifier::SelectedImpl,
        SelectAttributeModifier::SelectedImpl,
        SelectAttributeModifier::ValueImpl,
        SelectAttributeModifier::ValueImpl,
        SelectAttributeModifier::FontImpl,
        SelectAttributeModifier::FontImpl,
        SelectAttributeModifier::FontColorImpl,
        SelectAttributeModifier::FontColorImpl,
        SelectAttributeModifier::SelectedOptionBgColorImpl,
        SelectAttributeModifier::SelectedOptionBgColorImpl,
        SelectAttributeModifier::SelectedOptionFontImpl,
        SelectAttributeModifier::SelectedOptionFontImpl,
        SelectAttributeModifier::SelectedOptionFontColorImpl,
        SelectAttributeModifier::SelectedOptionFontColorImpl,
        SelectAttributeModifier::OptionBgColorImpl,
        SelectAttributeModifier::OptionBgColorImpl,
        SelectAttributeModifier::OptionFontImpl,
        SelectAttributeModifier::OptionFontImpl,
        SelectAttributeModifier::OptionFontColorImpl,
        SelectAttributeModifier::OptionFontColorImpl,
        nullptr,
        SelectAttributeModifier::OnSelectImpl,
        SelectAttributeModifier::SpaceImpl,
        SelectAttributeModifier::SpaceImpl,
        SelectAttributeModifier::ArrowPositionImpl,
        SelectAttributeModifier::ArrowPositionImpl,
        SelectAttributeModifier::OptionWidthImpl,
        SelectAttributeModifier::OptionWidthImpl,
        SelectAttributeModifier::OptionHeightImpl,
        SelectAttributeModifier::OptionHeightImpl,
        SelectAttributeModifier::MenuBackgroundColorImpl,
        SelectAttributeModifier::MenuBackgroundColorImpl,
        SelectAttributeModifier::MenuBackgroundBlurStyleImpl,
        SelectAttributeModifier::MenuBackgroundBlurStyleImpl,
        SelectAttributeModifier::ControlSizeImpl,
        SelectAttributeModifier::ControlSizeImpl,
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
        SelectAttributeModifier::MenuAlignImpl,
        SelectAttributeModifier::MenuAlignImpl,
        SelectAttributeModifier::_onChangeEvent_selectedImpl,
        SelectAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISelectModifierImpl;
}

}
