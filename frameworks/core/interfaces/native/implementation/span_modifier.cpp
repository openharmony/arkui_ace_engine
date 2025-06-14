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
#include "core/components_ng/pattern/text/span_model_static.h"
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
    return nullptr;
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
              const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSizeValue = Converter::OptConvert<Dimension>(value->size);
    Validator::ValidateNonNegative(fontSizeValue);
    Validator::ValidateNonPercent(fontSizeValue);
    SpanModelStatic::SetFontSize(frameNode, fontSizeValue);
    auto fontWeightValue = Converter::OptConvert<FontWeight>(value->weight);
    SpanModelStatic::SetFontWeight(frameNode, fontWeightValue);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(value->family); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    SpanModelStatic::SetFontFamily(frameNode, families);
    auto fontStyleValue = Converter::OptConvert<Ace::FontStyle>(value->style);
    SpanModelStatic::SetItalicFontStyle(frameNode, fontStyleValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    SpanModelStatic::SetTextColor(frameNode, convValue);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SpanModelStatic::SetFontSize(frameNode, convValue);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(value);
    SpanModelStatic::SetItalicFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    SpanModelStatic::SetFontWeight(frameNode, convValue);
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
    SpanModelStatic::SetFontFamily(frameNode, families);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto decoration = Converter::OptConvert<TextDecoration>(value->type);
    SpanModelStatic::SetTextDecoration(frameNode, decoration);
    auto color = Converter::OptConvert<Color>(value->color);
    SpanModelStatic::SetTextDecorationColor(frameNode, color);
    auto style = Converter::OptConvert<TextDecorationStyle>(value->style);
    SpanModelStatic::SetTextDecorationStyle(frameNode, style);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonPercent(convValue);
    SpanModelStatic::SetLetterSpacing(frameNode, convValue);
}
void TextCaseImpl(Ark_NativePointer node,
                  Ark_TextCase value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextCase>(value);
    SpanModelStatic::SetTextCase(frameNode, convValue);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    SpanModelStatic::SetLineHeight(frameNode, convValue);
}
void TextShadowImpl(Ark_NativePointer node,
                    const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    SpanModelStatic::SetTextShadow(frameNode, shadowList);
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
