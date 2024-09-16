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

#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "core/interfaces/native/node/node_api.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/arkoala/utility/converter.h"

namespace OHOS::Ace::NG {
struct ButtonOptions {
    std::optional<ButtonType> type;
    std::optional<ButtonRole> role;
    std::optional<bool> stateEffect;
    std::optional<ControlSize> controlSize;
    std::optional<ButtonStyleMode> buttonStyle;
};
} // OHOS::Ace::NG

namespace OHOS::Ace::NG::Converter {
template<>
ButtonOptions Convert(const Ark_ButtonOptions& src)
{
    ButtonOptions options;
    options.type = OptConvert<ButtonType>(src.type);
    options.role = OptConvert<ButtonRole>(src.role);
    options.stateEffect = OptConvert<bool>(src.stateEffect);
    options.controlSize = OptConvert<ControlSize>(src.controlSize);
    options.buttonStyle = OptConvert<ButtonStyleMode>(src.buttonStyle);
    return options;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ButtonInterfaceModifier {
void SetButtonOptions0Impl(Ark_NativePointer node)
{
    // safe it empty for save default values
}
void SetButtonOptions1Impl(Ark_NativePointer node,
                           const Ark_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto buttonOptions = Converter::Convert<ButtonOptions>(*options);
    if (buttonOptions.type) {
        ButtonModelNG::SetType(frameNode, static_cast<int>(buttonOptions.type.value()));
    }
    if (buttonOptions.stateEffect) {
        ButtonModelNG::SetStateEffect(frameNode, buttonOptions.stateEffect.value());
    }
    ButtonModelNG::SetRole(frameNode, buttonOptions.role);
    ButtonModelNG::SetControlSize(frameNode, buttonOptions.controlSize);
    ButtonModelNG::SetButtonStyle(frameNode, buttonOptions.buttonStyle);
}
void SetButtonOptions2Impl(Ark_NativePointer node,
                           const ResourceStr* label,
                           const Opt_ButtonOptions* options)
{
    if (options->tag == ARK_TAG_UNDEFINED) {
        SetButtonOptions0Impl(node);
    } else {
        SetButtonOptions1Impl(node, &options->value);
    }
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetLabel(frameNode, Converter::ConvertOrDefault(*label, ""));
}
} // ButtonInterfaceModifier
namespace ButtonAttributeModifier {
constexpr int32_t DEFAULT_FONT_SIZE = 12;
constexpr int32_t DEFAULT_MAX_LINES = 100;

void TypeImpl(Ark_NativePointer node,
              Ark_ButtonType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetType(frameNode, (ArkUI_Int32)Converter::ConvertOrDefault(value, ButtonType::CAPSULE));
}
void StateEffectImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, Converter::ConvertOrDefault(value, true));
}
void ButtonStyleImpl(Ark_NativePointer node,
                     Ark_ButtonStyleMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetButtonStyle(frameNode, Converter::ConvertOrDefault(value, ButtonStyleMode::EMPHASIZE));
}
void ControlSizeImpl(Ark_NativePointer node,
                     Ark_ControlSize value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetControlSize(frameNode, Converter::ConvertOrDefault(value, ControlSize::NORMAL));
}
void RoleImpl(Ark_NativePointer node,
              Ark_ButtonRole value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetRole(frameNode, Converter::ConvertOrDefault(value, ButtonRole::NORMAL));
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontColor(frameNode, Converter::ConvertOrDefault(*value, Color()));
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontSize(frameNode, CalcDimension(value->value, (DimensionUnit)value->unit));
}
void FontWeightImpl(Ark_NativePointer node,
                    const Type_ButtonAttribute_fontWeight_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontWeight(frameNode, Converter::ConvertOrDefault(*value, FontWeight::NORMAL));
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, (Ace::FontStyle)value);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Type_ButtonAttribute_fontFamily_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontFamily(frameNode,
                                 Framework::ConvertStrToFontFamilies(Converter::ConvertOrDefault(*value, "")));
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* modifier)
{
    LOGE("ARKOALA ButtonAttribute::ContentModifierImpl -> Method is not "
            "implemented.");
}
void LabelStyleImpl(Ark_NativePointer node,
                    const Ark_LabelStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonParameters parameters;
    parameters.textOverflow = Converter::ConvertOrDefault(value->overflow, TextOverflow::ELLIPSIS);
    parameters.maxLines = Converter::ConvertOrDefault(value->maxLines, DEFAULT_MAX_LINES);
    parameters.heightAdaptivePolicy = Converter::ConvertOrDefault(
        value->heightAdaptivePolicy, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    parameters.minFontSize = Converter::ConvertOrDefault(value->minFontSize, Dimension());
    parameters.maxFontSize = Converter::ConvertOrDefault(value->maxFontSize, Dimension());

    parameters.fontSize = Dimension(DEFAULT_FONT_SIZE, DimensionUnit::VP);
    parameters.fontStyle = Ace::FontStyle::NORMAL;
    parameters.fontWeight = FontWeight::NORMAL;
    parameters.fontFamily = std::vector<std::string>();
    Converter::WithOptional(value->font, [&](const Ark_Font &font) {
        parameters.fontSize = Converter::ConvertOrDefault(font.size, parameters.fontSize.value());
        parameters.fontStyle = Converter::ConvertOrDefault(font.style, parameters.fontStyle.value());
        parameters.fontWeight = Converter::ConvertOrDefault(font.weight, parameters.fontWeight.value());
        parameters.fontFamily = Converter::ConvertOrDefault(font.family, parameters.fontFamily.value());
    });
    ButtonModelNG::SetLabelStyle(frameNode, parameters);
}
} // ButtonAttributeModifier

const GENERATED_ArkUIButtonModifier* GetButtonModifier()
{
    static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
        ButtonInterfaceModifier::SetButtonOptions0Impl,
        ButtonInterfaceModifier::SetButtonOptions1Impl,
        ButtonInterfaceModifier::SetButtonOptions2Impl,
        ButtonAttributeModifier::TypeImpl,
        ButtonAttributeModifier::StateEffectImpl,
        ButtonAttributeModifier::ButtonStyleImpl,
        ButtonAttributeModifier::ControlSizeImpl,
        ButtonAttributeModifier::RoleImpl,
        ButtonAttributeModifier::FontColorImpl,
        ButtonAttributeModifier::FontSizeImpl,
        ButtonAttributeModifier::FontWeightImpl,
        ButtonAttributeModifier::FontStyleImpl,
        ButtonAttributeModifier::FontFamilyImpl,
        ButtonAttributeModifier::ContentModifierImpl,
        ButtonAttributeModifier::LabelStyleImpl,
    };
    return &ArkUIButtonModifierImpl;
}
}
