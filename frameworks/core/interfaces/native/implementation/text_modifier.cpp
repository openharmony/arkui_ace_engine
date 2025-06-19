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

#include "core/interfaces/native/implementation/text_controller_peer_impl.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::Converter {
namespace WeightNum {
int32_t W100 = 100;
int32_t W200 = 200;
int32_t W300 = 300;
int32_t W400 = 400;
int32_t W500 = 500;
int32_t W600 = 600;
int32_t W700 = 700;
int32_t W800 = 800;
int32_t W900 = 900;
} // namespace WeightNum

struct FontSettingOptions {
    std::optional<bool> enableVariableFontWeight;
};

struct TextOptions {
    TextControllerPeer* peer;
};

template<>
inline FontSettingOptions Convert(const Ark_FontSettingOptions& src)
{
    FontSettingOptions options;
    options.enableVariableFontWeight = Converter::OptConvert<bool>(src.enableVariableFontWeight);
    return options;
}

template<>
void AssignCast(std::optional<TextSelectableMode>& dst, const Ark_TextSelectableMode& src)
{
    switch (src) {
        case ARK_TEXT_SELECTABLE_MODE_SELECTABLE_UNFOCUSABLE: dst = TextSelectableMode::SELECTABLE_UNFOCUSABLE; break;
        case ARK_TEXT_SELECTABLE_MODE_SELECTABLE_FOCUSABLE: dst = TextSelectableMode::SELECTABLE_FOCUSABLE; break;
        case ARK_TEXT_SELECTABLE_MODE_UNSELECTABLE: dst = TextSelectableMode::UNSELECTABLE; break;
        default: LOGE("Unexpected enum value in Ark_TextSelectableMode: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextSpanType>& dst, const Ark_TextSpanType& src)
{
    switch (src) {
        case ARK_TEXT_SPAN_TYPE_TEXT: dst = TextSpanType::TEXT; break;
        case ARK_TEXT_SPAN_TYPE_IMAGE: dst = TextSpanType::IMAGE; break;
        case ARK_TEXT_SPAN_TYPE_MIXED: dst = TextSpanType::MIXED; break;
        default: LOGE("Unexpected enum value in Ark_TextSpanType: %{public}d", src);
    }
}

template<>
void AssignCast(std::optional<TextResponseType>& dst, const Ark_TextResponseType& src)
{
    switch (src) {
        case ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK: dst = TextResponseType::RIGHT_CLICK; break;
        case ARK_TEXT_RESPONSE_TYPE_LONG_PRESS: dst = TextResponseType::LONG_PRESS; break;
        case ARK_TEXT_RESPONSE_TYPE_SELECT: dst = TextResponseType::SELECTED_BY_MOUSE; break;
        default: LOGE("Unexpected enum value in Ark_TextResponseType: %{public}d", src);
    }
}
template<>
TextOptions Convert(const Ark_TextOptions& src)
{
    TextOptions options;
    options.peer = src.controller;
    return options;
}

std::optional<int32_t> FontWeightToInt(const FontWeight& src)
{
    std::optional<int32_t> dst;
    switch (src) {
        case FontWeight::W100: dst = WeightNum::W100; break;
        case FontWeight::W200: dst = WeightNum::W200; break;
        case FontWeight::W300: dst = WeightNum::W300; break;
        case FontWeight::W400: dst = WeightNum::W400; break;
        case FontWeight::W500: dst = WeightNum::W500; break;
        case FontWeight::W600: dst = WeightNum::W600; break;
        case FontWeight::W700: dst = WeightNum::W700; break;
        case FontWeight::W800: dst = WeightNum::W800; break;
        case FontWeight::W900: dst = WeightNum::W900; break;
        default: dst = std::nullopt; break;
    }
    return dst;
}

template<>
TextSpanType Convert(const Ark_TextSpanType& src)
{
    TextSpanType textSpanType;
    switch (src) {
        case ARK_TEXT_SPAN_TYPE_TEXT: textSpanType = TextSpanType::TEXT; break;
        case ARK_TEXT_SPAN_TYPE_IMAGE: textSpanType = TextSpanType::IMAGE; break;
        case ARK_TEXT_SPAN_TYPE_MIXED: textSpanType = TextSpanType::MIXED; break;
        default: LOGE("Unexpected enum value in Ark_TextSpanType: %{public}d", src); break;
    }
    return textSpanType;
}

template<>
TextResponseType Convert(const Ark_TextResponseType& src)
{
    TextResponseType responseType;
    switch (src) {
        case ARK_TEXT_RESPONSE_TYPE_RIGHT_CLICK: responseType = TextResponseType::RIGHT_CLICK; break;
        case ARK_TEXT_RESPONSE_TYPE_LONG_PRESS: responseType = TextResponseType::LONG_PRESS; break;
        case ARK_TEXT_RESPONSE_TYPE_SELECT: responseType = TextResponseType::SELECTED_BY_MOUSE; break;
        default: LOGE("Unexpected enum value in Ark_TextResponseType: %{public}d", src); break;
    }
    return responseType;
}

template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_Number& src)
{
    auto intVal = src.tag == Ark_Tag::INTEROP_TAG_INT32 ? src.i32 : static_cast<int32_t>(src.f32);
    if (intVal >= WeightNum::W100 && intVal <= WeightNum::W900) {
        dst = intVal;
    }
}

template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_String& src)
{
    auto intVal = Converter::Convert<int32_t>(src);
    if (intVal >= WeightNum::W100 && intVal <= WeightNum::W900) {
        dst = intVal;
    }
}

template<>
void AssignCast(std::optional<int32_t>& dst, const Ark_FontWeight& src)
{
    if (src >= ARK_FONT_WEIGHT_LIGHTER && src <= ARK_FONT_WEIGHT_BOLDER) {
        dst = static_cast<int32_t>(src);
    }
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextModelNG::CreateFrameNode(id, u"");
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextModifier
namespace TextInterfaceModifier {
void SetTextOptionsImpl(Ark_NativePointer node,
                        const Opt_Union_String_Resource* content,
                        const Opt_TextOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);

    if (content) {
        auto text = Converter::OptConvert<std::string>(*content);
        if (text) {
            std::u16string u16Text = UtfUtils::Str8DebugToStr16(text.value());
            TextModelNG::InitText(frameNode, u16Text);
        }
    }

    if (value) {
        // obtain internal controller
        auto internalController = TextModelNG::InitTextController(frameNode);

        // pass internal controller to peer
        auto textOptions = Converter::OptConvert<Converter::TextOptions>(*value);
        if (textOptions && textOptions->peer) {
            textOptions->peer->controller = AceType::DynamicCast<TextController>(internalController);
        }
    }
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
static void FontImplInternal(Ark_NativePointer node,
                             const Ark_Font* value,
                             std::optional<bool> enableVariableFontWeight = std::nullopt)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    Font font = Converter::Convert<Font>(*value);
    font.enableVariableFontWeight = enableVariableFontWeight;
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
    std::optional<bool> enableVariableFontWeight;
    if (options) {
        if (auto settings = Converter::OptConvert<Converter::FontSettingOptions>(*options); settings) {
            enableVariableFontWeight = settings->enableVariableFontWeight;
        }
    }
    FontImplInternal(node, fontValue, enableVariableFontWeight);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto color = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetTextColor(frameNode, color);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);

    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetFontSize(frameNode, fontSize);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetAdaptMinFontSize(frameNode, fontSize);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetAdaptMaxFontSize(frameNode, fontSize);
}

void MinFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto minFontScale = Converter::OptConvert<float>(*value);
    Validator::ValidatePositive(minFontScale);
    const auto maxValue = 1.f;
    Validator::ValidateLessOrEqual(minFontScale, maxValue);
    TextModelStatic::SetMinFontScale(frameNode, minFontScale);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Ark_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxFontScale = Converter::OptConvert<float>(*value);
    const auto minValue = 1.f;
    Validator::ValidateGreatOrEqual(maxFontScale, minValue);
    TextModelStatic::SetMaxFontScale(frameNode, maxFontScale);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontStyle = Converter::OptConvert<Ace::FontStyle>(value);
    TextModelStatic::SetItalicFontStyle(frameNode, fontStyle);
}
void FontWeight0Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto weight = Converter::OptConvert<FontWeight>(*value);
    auto variableWeight = Converter::OptConvert<int32_t>(*value);
    TextModelStatic::SetFontWeight(frameNode, weight);
    TextModelStatic::SetVariableFontWeight(frameNode, variableWeight);
}
void FontWeight1Impl(Ark_NativePointer node,
                     const Ark_Union_Number_FontWeight_String* weight,
                     const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    FontWeight0Impl(node, weight);

    std::optional<bool> enableVariableFontWeight;
    if (options) {
        auto settings = Converter::OptConvert<Converter::FontSettingOptions>(*options);
        if (settings) {
            enableVariableFontWeight = settings->enableVariableFontWeight;
        }
    }
    TextModelStatic::SetEnableVariableFontWeight(frameNode, enableVariableFontWeight);
}
void LineSpacingImpl(Ark_NativePointer node,
                     Ark_LengthMetrics value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineSpacing = Converter::OptConvert<Dimension>(value);
    Validator::ValidateNonNegative(lineSpacing);
    TextModelStatic::SetLineSpacing(frameNode, lineSpacing);
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textAlign = Converter::OptConvert<TextAlign>(value);
    TextModelStatic::SetTextAlign(frameNode, textAlign);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineHeight = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(lineHeight);
    TextModelStatic::SetLineHeight(frameNode, lineHeight);
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Ark_TextOverflowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<TextOverflow>(value->overflow);
    TextModelStatic::SetTextOverflow(frameNode, convValue);
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
    Validator::ValidateNonEmpty(families);
    TextModelStatic::SetFontFamily(frameNode, families);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxLines = Converter::Convert<int32_t>(*value);
    std::optional<uint32_t> convValue;
    if (maxLines >= 0) {
        convValue = static_cast<uint32_t>(maxLines);
    }
    TextModelStatic::SetMaxLines(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto decoration = Converter::OptConvert<TextDecoration>(value->type);
    TextModelStatic::SetTextDecoration(frameNode, decoration);

    auto color = Converter::OptConvert<Color>(value->color);
    TextModelStatic::SetTextDecorationColor(frameNode, color);

    auto style = Converter::OptConvert<TextDecorationStyle>(value->style);
    TextModelStatic::SetTextDecorationStyle(frameNode, style);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonPercent(spacing);
    TextModelStatic::SetLetterSpacing(frameNode, spacing);
}
void TextCaseImpl(Ark_NativePointer node,
                  Ark_TextCase value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textCase = Converter::OptConvert<TextCase>(value);
    TextModelStatic::SetTextCase(frameNode, textCase);
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Ark_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto offset = Converter::OptConvert<Dimension>(*value);
    TextModelStatic::SetBaselineOffset(frameNode, offset);
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(value);
    TextModelStatic::SetCopyOption(frameNode, convValue);
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
    TextModelStatic::SetTextShadow(frameNode, shadowList);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(value);
    TextModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto indent = Converter::OptConvert<Dimension>(*value);
    TextModelStatic::SetTextIndent(frameNode, indent);
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_WordBreak value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(value);
    TextModelStatic::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_LineBreakStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(value);
    TextModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [arkCallback = CallbackHelper(*value)](const std::u16string& param) {
        std::string u8Param = UtfUtils::Str16DebugToStr8(param);
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(u8Param));
    };

    TextModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetCaretColor(frameNode, convValue);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetSelectedBackgroundColor(frameNode, convValue);
}
void EllipsisModeImpl(Ark_NativePointer node,
                      Ark_EllipsisMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<EllipsisMode>(value);
    TextModelStatic::SetEllipsisMode(frameNode, convValue);
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextModelNG::SetTextDetectEnable(frameNode, convValue);
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Ark_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<TextDetectConfig>(*value);
    TextModelNG::SetTextDetectConfig(frameNode, convValue);
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSelectionChange = [arkCallback = CallbackHelper(*value)](int32_t start, int32_t end) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
    };

    TextModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string fontFeatureSettings = Converter::Convert<std::string>(*value);
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(fontFeatureSettings));
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPrivacySensitive(frameNode, Converter::Convert<bool>(value));
}
void TextSelectableImpl(Ark_NativePointer node,
                        Ark_TextSelectableMode value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextSelectableMode>(value);
    TextModelStatic::SetTextSelectableMode(frameNode, convValue);
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         Ark_EditMenuOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
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
                           const CustomNodeBuilder* content,
                           Ark_TextResponseType responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto optSpanType = Converter::OptConvert<TextSpanType>(spanType);
    auto convResponseType = Converter::Convert<TextResponseType>(responseType);
    auto convBuildFunc = [callback = CallbackHelper(*content), node]() {
        auto builderNode = callback.BuildSync(node);
        NG::ViewStackProcessor::GetInstance()->Push(builderNode);
    };
    auto convMenuParam = Converter::OptConvert<SelectMenuParam>(*options);
    if (convMenuParam.has_value() && optSpanType.has_value()) {
        TextModelStatic::BindSelectionMenu(
            frameNode, optSpanType.value(), convResponseType, convBuildFunc, convMenuParam.value());
    }
}
} // TextAttributeModifier
const GENERATED_ArkUITextModifier* GetTextModifier()
{
    static const GENERATED_ArkUITextModifier ArkUITextModifierImpl {
        TextModifier::ConstructImpl,
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
        TextAttributeModifier::CaretColorImpl,
        TextAttributeModifier::SelectedBackgroundColorImpl,
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

}
