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

#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "core/components/common/properties/text_style.h"

namespace OHOS::Ace {

using FONT_FEATURES_LIST = std::list<std::pair<std::string, int32_t>>;
ACE_FORCE_EXPORT FONT_FEATURES_LIST ParseFontFeatureSettings(const std::string& fontFeatureSettings);

namespace NG {
namespace Converter {
struct FontSettingOptions {
    std::optional<bool> enableVariableFontWeight;
};

template<>
inline FontSettingOptions Convert(const Ark_FontSettingOptions& src)
{
    FontSettingOptions options;
    options.enableVariableFontWeight = Converter::OptConvert<bool>(src.enableVariableFontWeight);
    return options;
}
}

namespace GeneratedModifier {
namespace TextInterfaceModifier {
void SetTextOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* content,
                        const Opt_TextOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(content);

    auto text = Converter::OptConvert<std::string>(*content);
    if (text) {
        TextModelNG::InitText(frameNode, text.value());
    }

    if (value && value->tag != ARK_TAG_UNDEFINED) {
        LOGW("TextInterfaceModifier::SetTextOptionsImpl with options is not implemented");
    }
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
constexpr Dimension DEFAULT_FONT_SIZE;
constexpr FontWeight DEFAULT_FONT_WEIGHT = FontWeight::NORMAL;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;

static void FontImplInternal(Ark_NativePointer node,
                             const Ark_Font* value,
                             std::optional<bool> enableVariableFontWeight = std::nullopt)
{
    CHECK_NULL_VOID(value);

    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    Font font;
    font.fontSize = Converter::ConvertOrDefault(value->size, DEFAULT_FONT_SIZE);
    font.fontStyle = Converter::ConvertOrDefault(value->style, DEFAULT_FONT_STYLE);
    font.fontWeight = Converter::ConvertOrDefault(value->weight, DEFAULT_FONT_WEIGHT);
    font.enableVariableFontWeight = enableVariableFontWeight;

    auto families = Converter::OptConvert<StringArray>(value->family);
    if (families) {
        font.fontFamilies = std::move(families.value());
    }
    TextModelNG::SetFont(frameNode, font);
}

void Font0Impl(Ark_NativePointer node,
               const Ark_Font* value)
{
    FontImplInternal(node, value);
}
void Font1Impl(Ark_NativePointer node,
               const Ark_Font* fontValue,
               const Opt_FontSettingOptions* options)
{
    if (options) {
        if (auto settings = Converter::OptConvert<Converter::FontSettingOptions>(*options); settings) {
            FontImplInternal(node, fontValue, settings->enableVariableFontWeight);
        }
    } else {
        FontImplInternal(node, fontValue);
    }
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    if (color) {
        TextModelNG::SetTextColor(frameNode, color.value());
    }
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto fontSize = Converter::OptConvert<Dimension>(*value);
    if (fontSize) {
        TextModelNG::SetFontSize(frameNode, fontSize.value());
    } else {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        TextModelNG::SetFontSize(frameNode, theme->GetTextStyle().GetFontSize());
    }
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    if (fontSize) {
        TextModelNG::SetAdaptMinFontSize(frameNode, fontSize.value());
    }
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    if (fontSize) {
        TextModelNG::SetAdaptMaxFontSize(frameNode, fontSize.value());
    }
}

void MinFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto minFontScale = Converter::OptConvert<float>(*value);
    if (minFontScale) {
        TextModelNG::SetMinFontScale(frameNode, minFontScale.value());
    }
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxFontScale = Converter::OptConvert<float>(*value);
    if (maxFontScale) {
        TextModelNG::SetMaxFontScale(frameNode, maxFontScale.value());
    }
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetItalicFontStyle(frameNode, static_cast<Ace::FontStyle>(value));
}
void FontWeight0Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto weight = Converter::OptConvert<FontWeight>(*value);
    if (weight) {
        TextModelNG::SetFontWeight(frameNode, weight.value());
    }
}
void FontWeight1Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* weight,
                     const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FontWeight0Impl(node, weight);

    if (options) {
        auto settings = Converter::OptConvert<Converter::FontSettingOptions>(*options);
        if (settings && settings->enableVariableFontWeight) {
            TextModelNG::SetEnableVariableFontWeight(frameNode, settings->enableVariableFontWeight.value());
        }
    }
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Ark_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineSpacing = Converter::OptConvert<Dimension>(*value);
    if (lineSpacing) {
        TextModelNG::SetLineSpacing(frameNode, lineSpacing.value());
    }
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textAlign = Converter::OptConvert<TextAlign>(value);
    if (textAlign) {
        TextModelNG::SetTextAlign(frameNode, textAlign.value());
    }
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineHeight = Converter::OptConvert<Dimension>(*value);
    if (lineHeight) {
        TextModelNG::SetLineHeight(frameNode, lineHeight.value());
    }
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Ark_TextOverflowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextModelNG::SetTextOverflow(frameNode, static_cast<TextOverflow>(value->overflow));
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto families = Converter::OptConvert<StringArray>(*value);
    if (families) {
        TextModelNG::SetFontFamily(frameNode, families.value());
    }
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxLines = Converter::Convert<int>(*value);
    TextModelNG::SetMaxLines(frameNode, maxLines);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto decoration = Converter::OptConvert<TextDecoration>(value->type);
    if (decoration) {
        TextModelNG::SetTextDecoration(frameNode, decoration.value());
    }

    auto color = Converter::OptConvert<Color>(value->color);
    if (color) {
        TextModelNG::SetTextDecorationColor(frameNode, color.value());
    }

    auto style = Converter::OptConvert<TextDecorationStyle>(value->style);
    if (style) {
        TextModelNG::SetTextDecorationStyle(frameNode, style.value());
    }
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    if (spacing) {
        TextModelNG::SetLetterSpacing(frameNode, spacing.value());
    }
}
void TextCaseImpl(Ark_NativePointer node,
                  Ark_TextCase value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textCase = Converter::OptConvert<TextCase>(value);
    if (textCase) {
        TextModelNG::SetTextCase(frameNode, textCase.value());
    }
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto offset = Converter::OptConvert<Dimension>(*value);
    if (offset) {
        TextModelNG::SetBaselineOffset(frameNode, offset.value());
    }
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetCopyOption(frameNode, static_cast<CopyOptions>(value));
}
void DraggableImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetDraggable(value);
}
void TextShadowImpl(Ark_NativePointer node,
                    const Ark_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    if (shadowList) {
        TextModelNG::SetTextShadow(frameNode, shadowList.value());
    }
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHeightAdaptivePolicy(frameNode, static_cast<TextHeightAdaptivePolicy>(value));
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto indent = Converter::OptConvert<Dimension>(*value);
    if (indent) {
        TextModelNG::SetTextIndent(frameNode, indent.value());
    }
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_WordBreak value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetWordBreak(frameNode, static_cast<WordBreak>(value));
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_LineBreakStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetLineBreakStrategy(frameNode, static_cast<LineBreakStrategy>(value));
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [frameNode](const std::string& value) {
        auto stringValue = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getTextEventsReceiver()->onCopy(frameNode->GetId(), stringValue);
    };

    TextModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void EllipsisModeImpl(Ark_NativePointer node,
                      Ark_EllipsisMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEllipsisMode(frameNode, static_cast<EllipsisMode>(value));
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    //TextModelNG::SetEnableDataDetector(frameNode, convValue);
    LOGW("TextAttributeModifier::EnableDataDetectorImpl not implemented");
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetDataDetectorConfig(frameNode, convValue);
    LOGW("TextAttributeModifier::EnableDataDetectorImpl not implemented");
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSelectionChange = [frameNode](int32_t start, int32_t end) {
        auto selectionStart = Converter::ArkValue<Ark_Number>(start);
        auto selectionEnd = Converter::ArkValue<Ark_Number>(end);
        GetFullAPI()->getEventsAPI()->getTextEventsReceiver()->onTextSelectionChange(frameNode->GetId(),
            selectionStart, selectionEnd);
    };

    TextModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string strValue(value->chars);
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(strValue));
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    frameNode->SetPrivacySensitive(Converter::Convert<bool>(value));
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}
void TextSelectableImpl(Ark_NativePointer node,
                        Ark_TextSelectableMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetTextSelectableMode(frameNode, static_cast<TextSelectableMode>(value));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextModelNG::SetEditMenuOptions(frameNode, convValue);
    LOGW("TextAttributeModifier::EditMenuOptionsImpl not implemented");
}
void HalfLeadingImpl(Ark_NativePointer node,
                     Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetHalfLeading(frameNode, Converter::Convert<bool>(value));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextModelNG::SetEnableHapticFeedback(frameNode, Converter::Convert<bool>(value));
}
void SelectionImpl(Ark_NativePointer node,
                   const Ark_Number* selectionStart,
                   const Ark_Number* selectionEnd)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(selectionStart);
    CHECK_NULL_VOID(selectionEnd);
    auto startIndex = Converter::Convert<int>(*selectionStart);
    auto endIndex = Converter::Convert<int>(*selectionEnd);
    TextModelNG::SetTextSelection(frameNode, startIndex, endIndex);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           Ark_TextSpanType spanType,
                           const Callback_Any* content,
                           Ark_TextResponseType responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(spanType);
    //auto convValue = Converter::OptConvert<type>(spanType); // for enums
    //TextModelNG::SetBindSelectionMenu(frameNode, convValue);
}
} // TextAttributeModifier
const GENERATED_ArkUITextModifier* GetTextModifier()
{
    static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
        TextInterfaceModifier::SetTextOptionsImpl,
        TextAttributeModifier::Font0Impl,
        TextAttributeModifier::Font1Impl,
        TextAttributeModifier::FontColorImpl,
        TextAttributeModifier::FontSizeImpl,
        TextAttributeModifier::MinFontSizeImpl,
        TextAttributeModifier::MaxFontSizeImpl,
        TextAttributeModifier::MinFontScaleImpl,
        TextAttributeModifier::MaxFontScaleImpl,
        TextAttributeModifier::FontStyleImpl,
        TextAttributeModifier::FontWeight0Impl,
        TextAttributeModifier::FontWeight1Impl,
        TextAttributeModifier::LineSpacingImpl,
        TextAttributeModifier::TextAlignImpl,
        TextAttributeModifier::LineHeightImpl,
        TextAttributeModifier::TextOverflowImpl,
        TextAttributeModifier::FontFamilyImpl,
        TextAttributeModifier::MaxLinesImpl,
        TextAttributeModifier::DecorationImpl,
        TextAttributeModifier::LetterSpacingImpl,
        TextAttributeModifier::TextCaseImpl,
        TextAttributeModifier::BaselineOffsetImpl,
        TextAttributeModifier::CopyOptionImpl,
        TextAttributeModifier::DraggableImpl,
        TextAttributeModifier::TextShadowImpl,
        TextAttributeModifier::HeightAdaptivePolicyImpl,
        TextAttributeModifier::TextIndentImpl,
        TextAttributeModifier::WordBreakImpl,
        TextAttributeModifier::LineBreakStrategyImpl,
        TextAttributeModifier::OnCopyImpl,
        TextAttributeModifier::EllipsisModeImpl,
        TextAttributeModifier::EnableDataDetectorImpl,
        TextAttributeModifier::DataDetectorConfigImpl,
        TextAttributeModifier::OnTextSelectionChangeImpl,
        TextAttributeModifier::FontFeatureImpl,
        TextAttributeModifier::PrivacySensitiveImpl,
        TextAttributeModifier::TextSelectableImpl,
        TextAttributeModifier::EditMenuOptionsImpl,
        TextAttributeModifier::HalfLeadingImpl,
        TextAttributeModifier::EnableHapticFeedbackImpl,
        TextAttributeModifier::SelectionImpl,
        TextAttributeModifier::BindSelectionMenuImpl,
    };
    return &ArkUITextModifierImpl;
}

} // namespace GeneratedModifier
} // namespace NG
} // namespace OHOS::Ace
