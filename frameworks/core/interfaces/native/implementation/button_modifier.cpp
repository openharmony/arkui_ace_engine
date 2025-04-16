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

#include "bridge/common/utils/utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/button/button_model_ng.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"


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

template<>
ButtonParameters Convert(const Ark_LabelStyle& src)
{
    ButtonParameters parameters;
    parameters.textOverflow = Converter::OptConvert<TextOverflow>(src.overflow);
    auto maxLines = Converter::OptConvert<int32_t>(src.maxLines);
    if (maxLines) {
        maxLines = std::max(maxLines.value(), 1);
    }
    parameters.maxLines = maxLines;
    parameters.heightAdaptivePolicy = Converter::OptConvert<TextHeightAdaptivePolicy>(src.heightAdaptivePolicy);
    auto minFontSize = Converter::OptConvert<Dimension>(src.minFontSize);
    Validator::ValidateNonNegative(minFontSize);
    Validator::ValidateNonPercent(minFontSize);
    parameters.minFontSize = minFontSize;
    auto maxFontSize = Converter::OptConvert<Dimension>(src.maxFontSize);
    Validator::ValidateNonNegative(maxFontSize);
    Validator::ValidateNonPercent(maxFontSize);
    parameters.maxFontSize = maxFontSize;
    auto labelFont = Converter::OptConvert<Font>(src.font);
    if (labelFont) {
        parameters.fontSize = labelFont->fontSize;
        parameters.fontStyle = labelFont->fontStyle;
        parameters.fontWeight = labelFont->fontWeight;
        if (labelFont->fontFamilies.size() > 0) {
            parameters.fontFamily = labelFont->fontFamilies;
        }
    }
    return parameters;
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ButtonModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ButtonModifier
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
        auto typeInt = EnumToInt(buttonOptions.type);
        ButtonModelNG::SetType(frameNode, typeInt);
    }
    if (buttonOptions.stateEffect) {
        ButtonModelNG::SetStateEffect(frameNode, buttonOptions.stateEffect.value());
    }
    if (buttonOptions.role) {
        ButtonModelNG::SetRole(frameNode, buttonOptions.role);
    }
    if (buttonOptions.controlSize) {
        ButtonModelNG::SetControlSize(frameNode, buttonOptions.controlSize);
    }
    if (buttonOptions.buttonStyle) {
        ButtonModelNG::SetButtonStyle(frameNode, buttonOptions.buttonStyle);
    }
}
void SetButtonOptions2Impl(Ark_NativePointer node,
                           const Ark_ResourceStr* label,
                           const Opt_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(label);
    if (options != nullptr) {
        if (auto buttonOptions = Converter::OptConvert<Ark_ButtonOptions>(*options); buttonOptions) {
            SetButtonOptions1Impl(node, &buttonOptions.value());
        }
    }
    auto labelString = Converter::OptConvert<std::string>(*label);
    ButtonModelNG::SetLabel(frameNode, labelString.value_or("").c_str());
}
} // ButtonInterfaceModifier
namespace ButtonAttributeModifier {
void TypeImpl(Ark_NativePointer node,
              Ark_ButtonType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto typeInt = EnumToInt(Converter::OptConvert<ButtonType>(value));
    ButtonModelNG::SetType(frameNode, typeInt);
}
void StateEffectImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetStateEffect(frameNode, Converter::Convert<bool>(value));
}
void ButtonStyleImpl(Ark_NativePointer node,
                     Ark_ButtonStyleMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetButtonStyle(frameNode, Converter::OptConvert<ButtonStyleMode>(value));
}
void ControlSizeImpl(Ark_NativePointer node,
                     Ark_ControlSize value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetControlSize(frameNode, Converter::OptConvert<ControlSize>(value));
}
void RoleImpl(Ark_NativePointer node,
              Ark_ButtonRole value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetRole(frameNode, Converter::OptConvert<ButtonRole>(value));
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ButtonModelNG::SetFontColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidatePositive(fontSize);
    Validator::ValidateNonPercent(fontSize);
    ButtonModelNG::SetFontSize(frameNode, fontSize);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    ButtonModelNG::SetFontWeight(frameNode, Converter::OptConvert<Ace::FontWeight>(*value));
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelNG::SetFontStyle(frameNode, Converter::OptConvert<Ace::FontStyle>(value));
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    ButtonModelNG::SetFontFamily(frameNode, families);
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    LOGE("ARKOALA ButtonAttribute::ContentModifierImpl -> Method is not "
            "implemented.");
}
void LabelStyleImpl(Ark_NativePointer node,
                    const Ark_LabelStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto parameters = Converter::OptConvert<ButtonParameters>(*value);
    ButtonModelNG::SetLabelStyle(frameNode, parameters);
}
} // ButtonAttributeModifier
const GENERATED_ArkUIButtonModifier* GetButtonModifier()
{
    static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
        ButtonModifier::ConstructImpl,
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
