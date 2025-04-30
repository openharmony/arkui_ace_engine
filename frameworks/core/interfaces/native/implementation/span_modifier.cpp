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
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto spanNode = SpanModelNG::CreateSpanNode(id, u"");
    CHECK_NULL_RETURN(spanNode, nullptr);
    spanNode->IncRefCount();
    return AceType::RawPtr(spanNode);
}
} // SpanModifier
namespace SpanInterfaceModifier {
void SetSpanOptionsImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto text = Converter::OptConvert<std::string>(*value);
    std::u16string u16Text = UtfUtils::Str8DebugToStr16(text.value_or(""));
    SpanModelNG::InitSpan(frameNode, u16Text);
}
} // SpanInterfaceModifier
namespace SpanAttributeModifier {
void FontImpl(Ark_NativePointer node,
              const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSizeValue;
    std::optional<FontWeight> fontWeightValue;
    std::optional<StringArray> families;
    std::optional<Ace::FontStyle> fontStyleValue;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        fontSizeValue = Converter::OptConvert<Dimension>((value->value).size);
        fontWeightValue = Converter::OptConvert<FontWeight>((value->value).weight);
        auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>((value->value).family);
        if (fontfamiliesOpt) {
            families = fontfamiliesOpt->families;
        }
        fontStyleValue = Converter::OptConvert<Ace::FontStyle>((value->value).style);
    }
    Validator::ValidateNonNegative(fontSizeValue);
    Validator::ValidateNonPercent(fontSizeValue);
    SpanModelNG::SetFontSize(frameNode, fontSizeValue);
    SpanModelNG::SetFontWeight(frameNode, fontWeightValue);

    SpanModelNG::SetFontFamily(frameNode, families);
    SpanModelNG::SetItalicFontStyle(frameNode, fontStyleValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    SpanModelNG::SetTextColor(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SpanModelNG::SetFontSize(frameNode, convValue);
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(*value);
    SpanModelNG::SetItalicFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    SpanModelNG::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    SpanModelNG::SetFontFamily(frameNode, families);
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    std::optional<TextDecoration> decoration;
    std::optional<Color> color;
    std::optional<TextDecorationStyle> style;
    
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        decoration = Converter::OptConvert<TextDecoration>((value->value).type);
        color = Converter::OptConvert<Color>((value->value).color);
        style = Converter::OptConvert<TextDecorationStyle>((value->value).style);
    }
    SpanModelNG::SetTextDecoration(frameNode, decoration);
    SpanModelNG::SetTextDecorationColor(frameNode, color);
    SpanModelNG::SetTextDecorationStyle(frameNode, style);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonPercent(convValue);
    SpanModelNG::SetLetterSpacing(frameNode, convValue);
}
void TextCaseImpl(Ark_NativePointer node,
                  const Opt_TextCase* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextCase>(*value);
    SpanModelNG::SetTextCase(frameNode, convValue);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SpanModelNG::SetLineHeight(frameNode, convValue);
}
void TextShadowImpl(Ark_NativePointer node,
                    const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    SpanModelNG::SetTextShadow(frameNode, shadowList);
}
} // SpanAttributeModifier
const GENERATED_ArkUISpanModifier* GetSpanModifier()
{
    static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
        SpanModifier::ConstructImpl,
        SpanInterfaceModifier::SetSpanOptionsImpl,
        SpanAttributeModifier::FontImpl,
        SpanAttributeModifier::FontColorImpl,
        SpanAttributeModifier::FontSizeImpl,
        SpanAttributeModifier::FontStyleImpl,
        SpanAttributeModifier::FontWeightImpl,
        SpanAttributeModifier::FontFamilyImpl,
        SpanAttributeModifier::DecorationImpl,
        SpanAttributeModifier::LetterSpacingImpl,
        SpanAttributeModifier::TextCaseImpl,
        SpanAttributeModifier::LineHeightImpl,
        SpanAttributeModifier::TextShadowImpl,
    };
    return &ArkUISpanModifierImpl;
}

}
