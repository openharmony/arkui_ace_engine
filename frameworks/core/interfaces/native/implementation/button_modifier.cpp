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
#include "core/components_ng/pattern/button/button_model_static.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/validators.h"

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
ButtonParameters Convert(const Ark_ButtonLabelStyle& src)
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
constexpr float SCALE_LIMIT = 1.f;
namespace ButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ButtonModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // ButtonModifier
namespace ButtonInterfaceModifier {
void SetButtonOptions0Impl(Ark_NativePointer node,
                           const Ark_ResourceStr* label,
                           const Opt_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(label);
    auto arkButtonOptions = Converter::OptConvertPtr<Ark_ButtonOptions>(options);
    if (arkButtonOptions.has_value()) {
        auto buttonOptions = Converter::Convert<ButtonOptions>(*arkButtonOptions);
        ButtonModelStatic::SetType(frameNode, EnumToInt(buttonOptions.type));
        ButtonModelStatic::SetStateEffect(frameNode, buttonOptions.stateEffect);
        ButtonModelStatic::SetRole(frameNode, buttonOptions.role);
        ButtonModelStatic::SetControlSize(frameNode, buttonOptions.controlSize);
        ButtonModelStatic::SetButtonStyle(frameNode, buttonOptions.buttonStyle);
    }
    auto labelString = Converter::OptConvert<std::string>(*label);
    if (labelString) {
        ButtonModelStatic::SetLabel(frameNode, labelString->c_str());
    }
    ButtonModelStatic::SetCreateWithLabel(frameNode, true);
}
void SetButtonOptions1Impl(Ark_NativePointer node,
                           const Opt_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto arkButtonOptions = Converter::OptConvertPtr<Ark_ButtonOptions>(options);
    if (arkButtonOptions.has_value()) {
        auto buttonOptions = Converter::Convert<ButtonOptions>(*arkButtonOptions);
        ButtonModelStatic::SetType(frameNode, EnumToInt(buttonOptions.type));
        ButtonModelStatic::SetStateEffect(frameNode, buttonOptions.stateEffect);
        ButtonModelStatic::SetRole(frameNode, buttonOptions.role);
        ButtonModelStatic::SetControlSize(frameNode, buttonOptions.controlSize);
        ButtonModelStatic::SetButtonStyle(frameNode, buttonOptions.buttonStyle);
    }
    ButtonModelStatic::SetCreateWithLabel(frameNode, false);
}
} // ButtonInterfaceModifier
namespace ButtonAttributeModifier {
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_ButtonType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto typeInt = EnumToInt(Converter::OptConvertPtr<ButtonType>(value));
    ButtonModelStatic::SetType(frameNode, typeInt);
}
void SetStateEffectImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    ButtonModelStatic::SetStateEffect(frameNode, convValue);
}
void SetButtonStyleImpl(Ark_NativePointer node,
                        const Opt_ButtonStyleMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetButtonStyle(frameNode, Converter::OptConvertPtr<ButtonStyleMode>(value));
}
void SetControlSizeImpl(Ark_NativePointer node,
                        const Opt_ControlSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetControlSize(frameNode, Converter::OptConvertPtr<ControlSize>(value));
}
void SetRoleImpl(Ark_NativePointer node,
                 const Opt_ButtonRole* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetRole(frameNode, Converter::OptConvertPtr<ButtonRole>(value));
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetFontColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidatePositive(fontSize);
    Validator::ValidateNonPercent(fontSize);
    ButtonModelStatic::SetFontSize(frameNode, fontSize);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetFontWeight(frameNode, Converter::OptConvertPtr<Ace::FontWeight>(value));
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ButtonModelStatic::SetFontStyle(frameNode, Converter::OptConvertPtr<Ace::FontStyle>(value));
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvertPtr<Converter::FontFamilies>(value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    ButtonModelStatic::SetFontFamily(frameNode, families);
}
void SetLabelStyleImpl(Ark_NativePointer node,
                       const Opt_ButtonLabelStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto parameters = Converter::OptConvertPtr<ButtonParameters>(value);
    ButtonModelStatic::SetLabelStyle(frameNode, parameters);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateLessOrEqual(convValue, SCALE_LIMIT);
    ButtonModelStatic::SetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateGreatOrEqual(convValue, SCALE_LIMIT);
    ButtonModelStatic::SetMaxFontScale(frameNode, convValue);
}
} // ButtonAttributeModifier
const GENERATED_ArkUIButtonModifier* GetButtonModifier()
{
    static const GENERATED_ArkUIButtonModifier ArkUIButtonModifierImpl {
        ButtonModifier::ConstructImpl,
        ButtonInterfaceModifier::SetButtonOptions0Impl,
        ButtonInterfaceModifier::SetButtonOptions1Impl,
        ButtonAttributeModifier::SetTypeImpl,
        ButtonAttributeModifier::SetStateEffectImpl,
        ButtonAttributeModifier::SetButtonStyleImpl,
        ButtonAttributeModifier::SetControlSizeImpl,
        ButtonAttributeModifier::SetRoleImpl,
        ButtonAttributeModifier::SetFontColorImpl,
        ButtonAttributeModifier::SetFontSizeImpl,
        ButtonAttributeModifier::SetFontWeightImpl,
        ButtonAttributeModifier::SetFontStyleImpl,
        ButtonAttributeModifier::SetFontFamilyImpl,
        ButtonAttributeModifier::SetLabelStyleImpl,
        ButtonAttributeModifier::SetMinFontScaleImpl,
        ButtonAttributeModifier::SetMaxFontScaleImpl,
    };
    return &ArkUIButtonModifierImpl;
}

}
