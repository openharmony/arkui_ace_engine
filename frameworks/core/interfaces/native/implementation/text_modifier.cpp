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
#include "core/components_ng/base/view_abstract_model_static.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/components_ng/pattern/text/text_model_static.h"
#include "base/log/log_wrapper.h"
#include "base/utils/macros.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::Converter {
struct FontSettingOptions {
    std::optional<bool> enableVariableFontWeight;
};

struct TextOptions {
    TextControllerPeer* peer;
};

template<>
void AssignCast(std::optional<MarqueeStartPolicy>& dst, const Ark_MarqueeStartPolicy& src)
{
    switch (src) {
        case ARK_MARQUEE_START_POLICY_DEFAULT: dst = MarqueeStartPolicy::DEFAULT; break;
        case ARK_MARQUEE_START_POLICY_ON_FOCUS: dst = MarqueeStartPolicy::ON_FOCUS; break;
        default: LOGE("Unexpected enum value in Ark_MarqueeStartPolicy: %{public}d", src);
    }
}

template<>
inline FontSettingOptions Convert(const Ark_FontSettingOptions& src)
{
    FontSettingOptions options;
    options.enableVariableFontWeight = Converter::OptConvert<bool>(src.enableVariableFontWeight);
    return options;
}

template<>
TextMarqueeOptions Convert(const Ark_TextMarqueeOptions& src)
{
    TextMarqueeOptions options;
    options.UpdateTextMarqueeStart(Convert<bool>(src.start));

    auto optLoop = OptConvert<Dimension>(src.loop);
    if (optLoop) {
        auto loop = static_cast<int32_t>(optLoop.value().Value());
        if (loop == std::numeric_limits<int32_t>::max() || loop <= 0) {
            loop = -1;
        }
        options.UpdateTextMarqueeLoop(loop);
    }

    auto optStep = OptConvert<Dimension>(src.step);
    if (optStep) {
        auto step = optStep.value().Value();
        if (GreatNotEqual(step, 0.0)) {
            options.UpdateTextMarqueeStep(Dimension(step, DimensionUnit::VP).ConvertToPx());
        }
    }

    auto optDelay = OptConvert<Dimension>(src.delay);
    if (optDelay) {
        auto delayValue = static_cast<int32_t>(optDelay.value().Value());
        if (delayValue < 0) {
            delayValue = 0;
        }
        options.UpdateTextMarqueeDelay(delayValue);
    }

    auto fromStart = OptConvert<bool>(src.fromStart);
    if (fromStart) {
        options.UpdateTextMarqueeDirection(
            fromStart.value() ? MarqueeDirection::DEFAULT : MarqueeDirection::DEFAULT_REVERSE);
    }

    auto optFadeout = OptConvert<bool>(src.fadeout);
    if (optFadeout) {
        options.UpdateTextMarqueeFadeout(optFadeout.value());
    }

    auto optStartPolicy = OptConvert<MarqueeStartPolicy>(src.marqueeStartPolicy);
    if (optStartPolicy) {
        options.UpdateTextMarqueeStartPolicy(optStartPolicy.value());
    }

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
TextOptions Convert(const Ark_TextOptions& src)
{
    TextOptions options;
    options.peer = src.controller;
    return options;
}

template<>
TextSpanType Convert(const Ark_TextSpanType& src)
{
    TextSpanType textSpanType;
    switch (src) {
        case ARK_TEXT_SPAN_TYPE_TEXT: textSpanType = TextSpanType::TEXT; break;
        case ARK_TEXT_SPAN_TYPE_IMAGE: textSpanType = TextSpanType::IMAGE; break;
        case ARK_TEXT_SPAN_TYPE_MIXED: textSpanType = TextSpanType::MIXED; break;
        case ARK_TEXT_SPAN_TYPE_DEFAULT: textSpanType = TextSpanType::NONE; break;
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
        case ARK_TEXT_RESPONSE_TYPE_DEFAULT: responseType = TextResponseType::NONE; break;
        default: LOGE("Unexpected enum value in Ark_TextResponseType: %{public}d", src); break;
    }
    return responseType;
}

void AssignArkValue(Ark_MarqueeState& dst, int32_t src)
{
    const int32_t START = 0;
    const int32_t BOUNCE = 1;
    const int32_t FINISH = 2;
    switch (src) {
        case START: dst = ARK_MARQUEE_STATE_START; break;
        case BOUNCE: dst = ARK_MARQUEE_STATE_BOUNCE; break;
        case FINISH: dst = ARK_MARQUEE_STATE_FINISH; break;
        default:
            dst = static_cast<Ark_MarqueeState>(-1);
            LOGE("Unexpected enum value in Ark_MarqueeState: %{public}d", src);
            break;
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
        auto text = Converter::OptConvert<std::u16string>(*content);
        if (text) {
            TextModelNG::InitText(frameNode, text.value());
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
                             const Opt_Font* value,
                             std::optional<bool> enableVariableFontWeight = std::nullopt)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Font>(*value);
    if (convValue.has_value()) {
        convValue->enableVariableFontWeight = enableVariableFontWeight;
    }
    Converter::FontWeightInt defaultWeight = {};
    std::optional<Converter::FontWeightInt> weight = defaultWeight;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        weight = Converter::OptConvert<Converter::FontWeightInt>(value->value.weight).value_or(defaultWeight);
    }
    TextModelStatic::SetVariableFontWeight(frameNode, weight->variable);
    TextModelStatic::SetFont(frameNode, convValue);
}

void Font0Impl(Ark_NativePointer node,
               const Opt_Font* value)
{
    FontImplInternal(node, value);
}
void Font1Impl(Ark_NativePointer node,
               const Opt_Font* fontValue,
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
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetTextColor(frameNode, color);
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        fontSize = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetFontSize(frameNode, fontSize);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        fontSize = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetAdaptMinFontSize(frameNode, fontSize);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> fontSize = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        fontSize = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextModelStatic::SetAdaptMaxFontSize(frameNode, fontSize);
}

void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minFontScale = Converter::OptConvert<float>(*value);
    Validator::ValidatePositive(minFontScale);
    const auto maxValue = 1.f;
    Validator::ValidateLessOrEqual(minFontScale, maxValue);
    TextModelStatic::SetMinFontScale(frameNode, minFontScale);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxFontScale = Converter::OptConvert<float>(*value);
    const auto minValue = 1.f;
    Validator::ValidateGreatOrEqual(maxFontScale, minValue);
    TextModelStatic::SetMaxFontScale(frameNode, maxFontScale);
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontStyle = Converter::OptConvert<Ace::FontStyle>(*value);
    TextModelStatic::SetItalicFontStyle(frameNode, fontStyle);
}
void FontWeight0Impl(Ark_NativePointer node,
                     const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::FontWeightInt defaultWeight = {};
    auto weight = Converter::OptConvert<Converter::FontWeightInt>(*value).value_or(defaultWeight);
    TextModelStatic::SetFontWeight(frameNode, weight.fixed);
    TextModelStatic::SetVariableFontWeight(frameNode, weight.variable);
}
void FontWeight1Impl(Ark_NativePointer node,
                     const Opt_Union_Number_FontWeight_String* weight,
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
                     const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lineSpacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(lineSpacing);
    TextModelStatic::SetLineSpacing(frameNode, lineSpacing);
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textAlign = Converter::OptConvert<TextAlign>(*value);
    TextModelStatic::SetTextAlign(frameNode, textAlign);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> lineHeight = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        lineHeight = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(lineHeight);
    TextModelStatic::SetLineHeight(frameNode, lineHeight);
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Opt_TextOverflowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<TextOverflow> convValue = std::nullopt;
    auto optValue = Converter::GetOptPtr(value);
    if (optValue.has_value()) {
        convValue = Converter::OptConvert<TextOverflow>(optValue->overflow);
    }
    TextModelStatic::SetTextOverflow(frameNode, convValue);
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
    Validator::ValidateNonEmpty(families);
    TextModelStatic::SetFontFamily(frameNode, families);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<uint32_t>(*value);
    TextModelStatic::SetMaxLines(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_DecorationStyleInterface* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<TextDecoration> decoration = std::nullopt;
    std::optional<Color> color = std::nullopt;
    std::optional<TextDecorationStyle> style = std::nullopt;
    auto optValue = Converter::GetOptPtr(value);
    if (optValue.has_value()) {
        decoration = Converter::OptConvert<TextDecoration>(optValue->type);
        color = Converter::OptConvert<Color>(optValue->color);
        style = Converter::OptConvert<TextDecorationStyle>(optValue->style);
    }
    TextModelStatic::SetTextDecoration(frameNode, decoration);
    TextModelStatic::SetTextDecorationColor(frameNode, color);
    TextModelStatic::SetTextDecorationStyle(frameNode, style);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonPercent(spacing);
    TextModelStatic::SetLetterSpacing(frameNode, spacing);
}
void TextCaseImpl(Ark_NativePointer node,
                  const Opt_TextCase* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textCase = Converter::OptConvert<TextCase>(*value);
    TextModelStatic::SetTextCase(frameNode, textCase);
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto offset = Converter::OptConvert<Dimension>(*value);
    TextModelStatic::SetBaselineOffset(frameNode, offset);
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(*value);
    TextModelStatic::SetCopyOption(frameNode, convValue);
}
void DraggableImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    ViewAbstract::SetDraggable(frameNode, convValue.value_or(false));
}
void TextShadowImpl(Ark_NativePointer node,
                    const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    TextModelStatic::SetTextShadow(frameNode, shadowList);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(*value);
    TextModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto indent = Converter::OptConvert<Dimension>(*value);
    TextModelStatic::SetTextIndent(frameNode, indent);
}
void WordBreakImpl(Ark_NativePointer node,
                   const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(*value);
    TextModelStatic::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(*value);
    TextModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& param) {
        Converter::ConvContext ctx;
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(param, &ctx));
    };

    TextModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetCaretColor(frameNode, convValue);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextModelStatic::SetSelectedBackgroundColor(frameNode, convValue);
}
void EllipsisModeImpl(Ark_NativePointer node,
                      const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<EllipsisMode>(*value);
    TextModelStatic::SetEllipsisMode(frameNode, convValue);
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextModelNG::SetTextDetectEnable(frameNode, convValue.value_or(false));
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextDetectConfig>(*value);
    if (!convValue) {
        return;
    }
    TextModelNG::SetTextDetectConfig(frameNode, *convValue);
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSelectionChange = [arkCallback = CallbackHelper(*optValue)](int32_t start, int32_t end) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
    };

    TextModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<std::string>(*value);
    if (!convValue) {
        return;
    }
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
}
void MarqueeOptionsImpl(Ark_NativePointer node,
                        const Opt_TextMarqueeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<TextMarqueeOptions>(*value) : std::nullopt;
    TextModelNG::SetMarqueeOptions(frameNode, convValue.value_or(TextMarqueeOptions()));
}
void OnMarqueeStateChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_MarqueeState_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)](int32_t marqueeState) {
        auto arkMarqueeState = Converter::ArkValue<Ark_MarqueeState>(marqueeState);
        callbackHelper.Invoke(arkMarqueeState);
    };
    TextModelNG::SetOnMarqueeStateChange(frameNode, std::move(modelCallback));
}
void PrivacySensitiveImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetPrivacySensitive(frameNode, Converter::OptConvert<bool>(*value));
}
void TextSelectableImpl(Ark_NativePointer node,
                        const Opt_TextSelectableMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextSelectableMode>(*value);
    TextModelStatic::SetTextSelectableMode(frameNode, convValue);
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCreateMenuCallback = [arkCreateMenu = CallbackHelper(optValue->onCreateMenu)](
        const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    auto onMenuItemClick = [arkMenuItemClick = CallbackHelper(optValue->onMenuItemClick)](
        NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range {.start = menuOptionsParam.start, .end = menuOptionsParam.end};
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult = arkMenuItemClick.InvokeWithObtainResult<
                Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
    TextModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void HalfLeadingImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextModelStatic::SetHalfLeading(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void SelectionImpl(Ark_NativePointer node,
                   const Opt_Number* selectionStart,
                   const Opt_Number* selectionEnd)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto startIndex = Converter::OptConvert<int>(*selectionStart);
    if (!startIndex) {
        startIndex = -1;
    }
    auto endIndex = Converter::OptConvert<int>(*selectionEnd);
    if (!endIndex) {
        endIndex = -1;
    }
    TextModelNG::SetTextSelection(frameNode, *startIndex, *endIndex);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           const Opt_TextSpanType* spanType,
                           const Opt_CustomNodeBuilder* content,
                           const Opt_TextResponseType* responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    // TextSpanType
    NG::TextSpanType textSpanType = NG::TextSpanType::TEXT;
    bool isValidTextSpanType = false;
    auto optSpanType = Converter::OptConvert<TextSpanType>(*spanType);
    if (optSpanType) {
        isValidTextSpanType = true;
    }
    // Builder
    auto optContent = Converter::GetOptPtr(content);
    CHECK_NULL_VOID(optContent);
    // TextResponseType
    auto convResponseType = Converter::OptConvert<TextResponseType>(*responseType);
    if (!convResponseType) {
        convResponseType = NG::TextResponseType::LONG_PRESS;
    }
    // SelectionMenuOptions
    auto convMenuParam = Converter::OptConvert<SelectMenuParam>(*options);
    if (convMenuParam) {
        convMenuParam->isValid = isValidTextSpanType;
    } else {
        convMenuParam = NG::SelectMenuParam();
    }

    CallbackHelper(*optContent).BuildAsync([frameNode, spanType = optSpanType.value(), convResponseType,
        menuParam = convMenuParam.value()](const RefPtr<UINode>& uiNode) mutable {
        auto builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        TextModelStatic::BindSelectionMenu(frameNode, spanType, *convResponseType, std::move(builder), menuParam);
        }, node);
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
        TextAttributeModifier::MarqueeOptionsImpl,
        TextAttributeModifier::OnMarqueeStateChangeImpl,
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
