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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/components_ng/pattern/text_clock/text_clock_model_ng.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/components/common/properties/text_style_parser.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextClockInterfaceModifier {
void SetTextClockOptionsImpl(Ark_NativePointer node,
                             const Opt_TextClockOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //TextClockModelNG::SetSetTextClockOptions(frameNode, convValue);
}
} // TextClockInterfaceModifier
namespace TextClockAttributeModifier {
void FormatImpl(Ark_NativePointer node,
                const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<std::string>(*value) : std::nullopt;
    TextClockModelNG::SetFormat(frameNode, convValue);
}
void OnDateChangeImpl(Ark_NativePointer node,
                      const Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextClockModelNG::SetOnDateChange(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Color>(*value) : std::nullopt;
    TextClockModelNG::SetFontColor(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = value ? Converter::OptConvert<Dimension>(*value) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    TextClockModelNG::SetFontSize(frameNode, convValue);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Ace::FontStyle>(value) : std::nullopt;
    TextClockModelNG::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Ace::FontWeight>(*value) : std::nullopt;
    TextClockModelNG::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    StringArray fontFamilyResult;
    if (auto families = Converter::OptConvert<std::string>(*value); families) {
        fontFamilyResult = Converter::Convert<StringArray>(families.value());
    }
    TextClockModelNG::SetFontFamily(frameNode, fontFamilyResult);
}
void TextShadowImpl(Ark_NativePointer node,
                    const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::vector<Shadow> shadowListResult;
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    if (shadowList.has_value()) {
        shadowListResult = shadowList.value();
    }
    TextClockModelNG::SetTextShadow(frameNode, shadowListResult);
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontFeatureSettings = Converter::Convert<std::string>(*value);
    TextClockModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(fontFeatureSettings));
}
void ContentModifierImpl(Ark_NativePointer node,
                         const Ark_CustomObject* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextClockModelNG::SetContentModifier(frameNode, convValue);
}
void DateTimeOptionsImpl(Ark_NativePointer node,
                         const Ark_Union_DateTimeOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextClockModelNG::SetDateTimeOptions(frameNode, convValue);
}
} // TextClockAttributeModifier
const GENERATED_ArkUITextClockModifier* GetTextClockModifier()
{
    static const GENERATED_ArkUITextClockModifier ArkUITextClockModifierImpl {
        TextClockInterfaceModifier::SetTextClockOptionsImpl,
        TextClockAttributeModifier::FormatImpl,
        TextClockAttributeModifier::OnDateChangeImpl,
        TextClockAttributeModifier::FontColorImpl,
        TextClockAttributeModifier::FontSizeImpl,
        TextClockAttributeModifier::FontStyleImpl,
        TextClockAttributeModifier::FontWeightImpl,
        TextClockAttributeModifier::FontFamilyImpl,
        TextClockAttributeModifier::TextShadowImpl,
        TextClockAttributeModifier::FontFeatureImpl,
        TextClockAttributeModifier::ContentModifierImpl,
        TextClockAttributeModifier::DateTimeOptionsImpl,
    };
    return &ArkUITextClockModifierImpl;
}

}