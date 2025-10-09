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

#include "core/common/multi_thread_build_manager.h"
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
}
} // SpanModifier
namespace SpanInterfaceModifier {
void SetSpanOptionsImpl(Ark_NativePointer node,
                        const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto text = Converter::OptConvert<std::u16string>(*value);
    SpanModelStatic::InitSpan(frameNode, text);
}
} // SpanInterfaceModifier
namespace SpanAttributeModifier {
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        SpanModelNG::ResetFont(frameNode);
        return;
    }
    auto fontSizeValue = Converter::OptConvert<Dimension>(optValue->size);
    Validator::ValidateNonNegative(fontSizeValue);
    Validator::ValidateNonPercent(fontSizeValue);
    SpanModelStatic::SetFontSize(frameNode, fontSizeValue);
    auto fontWeightValue = Converter::OptConvert<FontWeight>(optValue->weight);
    SpanModelStatic::SetFontWeight(frameNode, fontWeightValue);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(optValue->family); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    SpanModelStatic::SetFontFamily(frameNode, families);
    auto fontStyleValue = Converter::OptConvert<Ace::FontStyle>(optValue->style);
    SpanModelStatic::SetItalicFontStyle(frameNode, fontStyleValue);
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    SpanModelStatic::SetTextColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    SpanModelStatic::SetFontSize(frameNode, convValue);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontStyle>(value);
    SpanModelStatic::SetItalicFontStyle(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<FontWeight>(value);
    SpanModelStatic::SetFontWeight(frameNode, convValue);
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
    SpanModelStatic::SetFontFamily(frameNode, families);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto decoration = optValue ? Converter::OptConvert<TextDecoration>(optValue->type) : std::nullopt;
    SpanModelStatic::SetTextDecoration(frameNode, decoration);
    auto color = optValue ? Converter::OptConvert<Color>(optValue->color) : std::nullopt;
    SpanModelStatic::SetTextDecorationColor(frameNode, color);
    auto style = optValue ? Converter::OptConvert<TextDecorationStyle>(optValue->style) : std::nullopt;
    SpanModelStatic::SetTextDecorationStyle(frameNode, style);
}
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonPercent(convValue);
    SpanModelStatic::SetLetterSpacing(frameNode, convValue);
}
void SetTextCaseImpl(Ark_NativePointer node,
                     const Opt_TextCase* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextCase>(value);
    SpanModelStatic::SetTextCase(frameNode, convValue);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(convValue);
    SpanModelStatic::SetLineHeight(frameNode, convValue);
}
void SetTextShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    SpanModelStatic::SetTextShadow(frameNode, shadowList);
}
} // SpanAttributeModifier
const GENERATED_ArkUISpanModifier* GetSpanModifier()
{
    static const GENERATED_ArkUISpanModifier ArkUISpanModifierImpl {
        SpanModifier::ConstructImpl,
        SpanInterfaceModifier::SetSpanOptionsImpl,
        SpanAttributeModifier::SetFontImpl,
        SpanAttributeModifier::SetFontColorImpl,
        SpanAttributeModifier::SetFontSizeImpl,
        SpanAttributeModifier::SetFontStyleImpl,
        SpanAttributeModifier::SetFontWeightImpl,
        SpanAttributeModifier::SetFontFamilyImpl,
        SpanAttributeModifier::SetDecorationImpl,
        SpanAttributeModifier::SetLetterSpacingImpl,
        SpanAttributeModifier::SetTextCaseImpl,
        SpanAttributeModifier::SetLineHeightImpl,
        SpanAttributeModifier::SetTextShadowImpl,
    };
    return &ArkUISpanModifierImpl;
}

}
