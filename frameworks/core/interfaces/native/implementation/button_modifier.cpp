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
namespace ButtonModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ButtonModifier
namespace ButtonInterfaceModifier {
void SetButtonOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //ButtonModelNG::SetSetButtonOptions0(frameNode, convValue);
}
void SetButtonOptions1Impl(Ark_NativePointer node,
                           const Ark_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //ButtonModelNG::SetSetButtonOptions1(frameNode, convValue);
}
void SetButtonOptions2Impl(Ark_NativePointer node,
                           const Ark_ResourceStr* label,
                           const Opt_ButtonOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(label);
    //auto convValue = Converter::OptConvert<type>(label); // for enums
    //ButtonModelNG::SetSetButtonOptions2(frameNode, convValue);
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
    ButtonModelStatic::SetStateEffect(frameNode, *convValue);
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
                       const Opt_Union_Number_FontWeight_String* value)
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
void SetContentModifierImpl(Ark_NativePointer node,
                            const Opt_ContentModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ButtonModelNG::SetSetContentModifier(frameNode, convValue);
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
                         const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateLessOrEqual(convValue, SCALE_LIMIT);
    ButtonModelStatic::SetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_Number_Resource* value)
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
        ButtonInterfaceModifier::SetButtonOptions2Impl,
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
        ButtonAttributeModifier::SetContentModifierImpl,
        ButtonAttributeModifier::SetLabelStyleImpl,
        ButtonAttributeModifier::SetMinFontScaleImpl,
        ButtonAttributeModifier::SetMaxFontScaleImpl,
    };
    return &ArkUIButtonModifierImpl;
}

}
