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
void AssignCast(std::optional<MarqueeUpdatePolicy>& dst, const Ark_MarqueeUpdatePolicy& src)
{
    switch (src) {
        case ARK_MARQUEE_UPDATE_POLICY_DEFAULT: dst = MarqueeUpdatePolicy::DEFAULT; break;
        case ARK_MARQUEE_UPDATE_POLICY_PRESERVE_POSITION: dst = MarqueeUpdatePolicy::PRESERVE_POSITION; break;
        default: LOGE("Unexpected enum value in Ark_MarqueeUpdatePolicy: %{public}d", src);
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

    auto optUpdatePolicy = OptConvert<MarqueeUpdatePolicy>(src.marqueeUpdatePolicy);
    if (optUpdatePolicy) {
        options.UpdateTextMarqueeUpdatePolicy(optUpdatePolicy.value());
    }

    auto optSpacing = OptConvert<CalcDimension>(src.spacing);
    if (optSpacing && !optSpacing.value().IsNegative()) {
        options.UpdateTextMarqueeSpacing(optSpacing.value());
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
} /* namespace OHOS::Ace::NG::Converter */

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

    auto text = Converter::OptConvertPtr<std::u16string>(content);
    if (text) {
        TextModelNG::InitText(frameNode, text.value());
    }

    // obtain internal controller
    auto internalController = TextModelNG::InitTextController(frameNode);

    // pass internal controller to peer
    auto textOptions = Converter::OptConvertPtr<Converter::TextOptions>(value);
    CHECK_NULL_VOID(textOptions);
    auto textController = textOptions->peer;
    CHECK_NULL_VOID(textController);
    textController->controller = AceType::DynamicCast<TextController>(internalController);
    auto styledStringCache = textController->GetStyledStringCache();
    if (styledStringCache) {
        textController->controller->SetStyledString(styledStringCache);
        textController->SetStyledStringCache(nullptr);
    }
}
} // TextInterfaceModifier
namespace TextAttributeModifier {
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto color = Converter::OptConvertPtr<Color>(value);
    TextModelStatic::SetTextColor(frameNode, color);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_F64_String_Resource* value)
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
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
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
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
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
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto minFontScale = Converter::OptConvertPtr<float>(value);
    TextModelStatic::SetMinFontScale(frameNode, minFontScale);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxFontScale = Converter::OptConvertPtr<float>(value);
    TextModelStatic::SetMaxFontScale(frameNode, maxFontScale);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontStyle = Converter::OptConvertPtr<Ace::FontStyle>(value);
    TextModelStatic::SetItalicFontStyle(frameNode, fontStyle);
}
void SetLineSpacingImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lineSpacing = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(lineSpacing);
    TextModelStatic::SetLineSpacing(frameNode, lineSpacing);
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textAlign = Converter::OptConvertPtr<TextAlign>(value);
    TextModelStatic::SetTextAlign(frameNode, textAlign);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_F64_String_Resource* value)
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
void SetTextOverflowImpl(Ark_NativePointer node,
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
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_Union_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvertPtr<Converter::FontFamilies>(value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    Validator::ValidateNonEmpty(families);
    TextModelStatic::SetFontFamily(frameNode, families);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<uint32_t>(value);
    TextModelStatic::SetMaxLines(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
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
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto spacing = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonPercent(spacing);
    TextModelStatic::SetLetterSpacing(frameNode, spacing);
}
void SetTextCaseImpl(Ark_NativePointer node,
                     const Opt_TextCase* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto textCase = Converter::OptConvertPtr<TextCase>(value);
    TextModelStatic::SetTextCase(frameNode, textCase);
}
void SetBaselineOffsetImpl(Ark_NativePointer node,
                           const Opt_Union_F64_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto offset = Converter::OptConvertPtr<Dimension>(value);
    TextModelStatic::SetBaselineOffset(frameNode, offset);
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CopyOptions>(value);
    TextModelStatic::SetCopyOption(frameNode, convValue);
}
void SetDraggableImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_VOID(pipeline);
        auto draggable = pipeline->GetDraggable<TextTheme>();
        frameNode->SetDraggable(draggable);
        auto gestureHub = frameNode->GetOrCreateGestureEventHub();
        CHECK_NULL_VOID(gestureHub);
        gestureHub->SetTextDraggable(true);
        return;
    }
    ViewAbstract::SetDraggable(frameNode, *convValue);
}
void SetTextShadowImpl(Ark_NativePointer node,
                       const Opt_Union_ShadowOptions_Array_ShadowOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto shadowList = Converter::OptConvert<std::vector<Shadow>>(*value);
    TextModelStatic::SetTextShadow(frameNode, shadowList);
}
void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                 const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextHeightAdaptivePolicy>(value);
    TextModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> indent = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        indent = Converter::OptConvertFromArkNumStrRes<Ark_Length, Ark_Number>(value->value, DimensionUnit::FP);
    }
    TextModelStatic::SetTextIndent(frameNode, indent);
}
void SetWordBreakImpl(Ark_NativePointer node,
                      const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<WordBreak>(value);
    TextModelStatic::SetWordBreak(frameNode, convValue);
}
void SetLineBreakStrategyImpl(Ark_NativePointer node,
                              const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<LineBreakStrategy>(value);
    TextModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextModelNG::ResetOnCopy(frameNode);
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& param) {
        Converter::ConvContext ctx;
        arkCallback.InvokeSync(Converter::ArkValue<Ark_String>(param, &ctx));
    };

    TextModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextModelStatic::SetCaretColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextModelStatic::SetSelectedBackgroundColor(frameNode, convValue);
}
void SetEllipsisModeImpl(Ark_NativePointer node,
                         const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<EllipsisMode>(value);
    TextModelStatic::SetEllipsisMode(frameNode, convValue);
}
void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextModelNG::SetTextDetectEnable(frameNode, convValue.value_or(false));
}
void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextDetectConfig>(value);
    if (!convValue) {
        TextModelNG::ResetTextDetectConfig(frameNode);
        return;
    }
    TextModelNG::SetTextDetectConfig(frameNode, *convValue);
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextModelNG::ResetOnTextSelectionChange(frameNode);
        return;
    }
    auto onSelectionChange = [arkCallback = CallbackHelper(*optValue)](int32_t start, int32_t end) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(start), Converter::ArkValue<Ark_Int32>(end));
    };

    TextModelNG::SetOnTextSelectionChange(frameNode, std::move(onSelectionChange));
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    if (!convValue) {
        TextModelNG::ResetFontFeature(frameNode);
        return;
    }
    TextModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
}
void SetMarqueeOptionsImpl(Ark_NativePointer node,
                           const Opt_TextMarqueeOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextMarqueeOptions>(value);
    TextModelNG::SetMarqueeOptions(frameNode, convValue.value_or(TextMarqueeOptions()));
}
void SetOnMarqueeStateChangeImpl(Ark_NativePointer node,
                                 const Opt_Callback_MarqueeState_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextModelNG::ResetOnMarqueeStateChange(frameNode);
        return;
    }
    auto modelCallback = [callbackHelper = CallbackHelper(*optValue)](int32_t marqueeState) {
        auto arkMarqueeState = Converter::ArkValue<Ark_MarqueeState>(marqueeState);
        callbackHelper.InvokeSync(arkMarqueeState);
    };
    TextModelNG::SetOnMarqueeStateChange(frameNode, std::move(modelCallback));
}
void SetPrivacySensitiveImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstractModelStatic::SetPrivacySensitive(frameNode, Converter::OptConvertPtr<bool>(value));
}
void SetTextSelectableImpl(Ark_NativePointer node,
                           const Opt_TextSelectableMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextSelectableMode>(value);
    TextModelStatic::SetTextSelectableMode(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        TextModelStatic::ResetSelectionMenuOptions(frameNode);
        return;
    }
    std::function<std::vector<NG::MenuOptionsParam>(const std::vector<NG::MenuItemParam>&)> onCreateMenuCallback =
        nullptr;
    std::function<bool(NG::MenuItemParam)> onMenuItemClick = nullptr;
    auto createMenuCallbackArk = Converter::GetOpt(optValue->onCreateMenu);
    if (createMenuCallbackArk.has_value()) {
        auto createMenuCallback = createMenuCallbackArk.value();
        onCreateMenuCallback =
            [arkCreateMenu = CallbackHelper(createMenuCallback)](
                const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    }
    auto clickCallbackArk = Converter::GetOpt(optValue->onMenuItemClick);
    if (clickCallbackArk.has_value()) {
        auto clickCallback = clickCallbackArk.value();
        onMenuItemClick = [arkMenuItemClick = CallbackHelper(clickCallback)](
                              NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range { .start = menuOptionsParam.start, .end = menuOptionsParam.end };
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult =
                arkMenuItemClick.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
        TextModelStatic::SetSelectionMenuOptions(
            frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
    }
}
void SetHalfLeadingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextModelStatic::SetHalfLeading(frameNode, Converter::OptConvertPtr<bool>(value));
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void SetCompressLeadingPunctuationImpl(Ark_NativePointer node,
                                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<bool>(*value) : std::nullopt;
    TextModelStatic::SetCompressLeadingPunctuation(frameNode, convValue);
}
void SetIncludeFontPaddingImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextModelStatic::SetIncludeFontPadding(frameNode, convValue);
}
void SetFallbackLineSpacingImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextModelStatic::SetFallbackLineSpacing(frameNode, convValue);
}
void SetFontImpl(Ark_NativePointer node,
                 const Opt_Font* fontValue,
                 const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<bool> enableVariableFontWeight;
    if (auto settings = Converter::OptConvertPtr<Converter::FontSettingOptions>(options); settings) {
        enableVariableFontWeight = settings->enableVariableFontWeight;
    }
    auto convValue = Converter::OptConvertPtr<Font>(fontValue);
    if (convValue.has_value()) {
        convValue->enableVariableFontWeight = enableVariableFontWeight;
    }
    Converter::FontWeightInt defaultWeight = {};
    std::optional<Converter::FontWeightInt> weight = defaultWeight;
    if (fontValue->tag != INTEROP_TAG_UNDEFINED) {
        weight = Converter::OptConvert<Converter::FontWeightInt>(fontValue->value.weight).value_or(defaultWeight);
    }
    TextModelStatic::SetVariableFontWeight(frameNode, weight->variable);
    TextModelStatic::SetFont(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* weight,
                       const Opt_FontSettingOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::FontWeightInt defaultWeight = {};
    auto convWeight = Converter::OptConvertPtr<Converter::FontWeightInt>(weight).value_or(defaultWeight);
    TextModelStatic::SetFontWeight(frameNode, convWeight.fixed);
    TextModelStatic::SetVariableFontWeight(frameNode, convWeight.variable);

    std::optional<bool> enableVariableFontWeight;
    auto settings = Converter::OptConvertPtr<Converter::FontSettingOptions>(options);
    if (settings) {
        enableVariableFontWeight = settings->enableVariableFontWeight;
    }
    TextModelStatic::SetEnableVariableFontWeight(frameNode, enableVariableFontWeight);
}
void SetSelectionImpl(Ark_NativePointer node,
                      const Opt_Int32* selectionStart,
                      const Opt_Int32* selectionEnd)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto startIndex = Converter::OptConvertPtr<int>(selectionStart);
    if (!startIndex) {
        startIndex = -1;
    }
    auto endIndex = Converter::OptConvertPtr<int>(selectionEnd);
    if (!endIndex) {
        endIndex = -1;
    }
    TextModelNG::SetTextSelection(frameNode, *startIndex, *endIndex);
}
void SetBindSelectionMenuImpl(Ark_NativePointer node,
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
    auto optSpanType = Converter::OptConvertPtr<TextSpanType>(spanType);
    if (optSpanType) {
        isValidTextSpanType = true;
    } else {
        optSpanType = NG::TextSpanType::TEXT;
    }
    // Builder
    auto optContent = Converter::GetOptPtr(content);
    CHECK_NULL_VOID(optContent);
    // TextResponseType
    auto convResponseType = Converter::OptConvertPtr<TextResponseType>(responseType);
    if (!convResponseType) {
        convResponseType = NG::TextResponseType::LONG_PRESS;
    }
    // SelectionMenuOptions
    auto convMenuParam = Converter::OptConvertPtr<SelectMenuParam>(options);
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
        TextAttributeModifier::SetFontColorImpl,
        TextAttributeModifier::SetFontSizeImpl,
        TextAttributeModifier::SetMinFontSizeImpl,
        TextAttributeModifier::SetMaxFontSizeImpl,
        TextAttributeModifier::SetMinFontScaleImpl,
        TextAttributeModifier::SetMaxFontScaleImpl,
        TextAttributeModifier::SetFontStyleImpl,
        TextAttributeModifier::SetLineSpacingImpl,
        TextAttributeModifier::SetTextAlignImpl,
        TextAttributeModifier::SetLineHeightImpl,
        TextAttributeModifier::SetTextOverflowImpl,
        TextAttributeModifier::SetFontFamilyImpl,
        TextAttributeModifier::SetMaxLinesImpl,
        TextAttributeModifier::SetDecorationImpl,
        TextAttributeModifier::SetLetterSpacingImpl,
        TextAttributeModifier::SetTextCaseImpl,
        TextAttributeModifier::SetBaselineOffsetImpl,
        TextAttributeModifier::SetCopyOptionImpl,
        TextAttributeModifier::SetDraggableImpl,
        TextAttributeModifier::SetTextShadowImpl,
        TextAttributeModifier::SetHeightAdaptivePolicyImpl,
        TextAttributeModifier::SetTextIndentImpl,
        TextAttributeModifier::SetWordBreakImpl,
        TextAttributeModifier::SetLineBreakStrategyImpl,
        TextAttributeModifier::SetOnCopyImpl,
        TextAttributeModifier::SetCaretColorImpl,
        TextAttributeModifier::SetSelectedBackgroundColorImpl,
        TextAttributeModifier::SetEllipsisModeImpl,
        TextAttributeModifier::SetEnableDataDetectorImpl,
        TextAttributeModifier::SetDataDetectorConfigImpl,
        TextAttributeModifier::SetOnTextSelectionChangeImpl,
        TextAttributeModifier::SetFontFeatureImpl,
        TextAttributeModifier::SetMarqueeOptionsImpl,
        TextAttributeModifier::SetOnMarqueeStateChangeImpl,
        TextAttributeModifier::SetPrivacySensitiveImpl,
        TextAttributeModifier::SetTextSelectableImpl,
        TextAttributeModifier::SetEditMenuOptionsImpl,
        TextAttributeModifier::SetHalfLeadingImpl,
        TextAttributeModifier::SetEnableHapticFeedbackImpl,
        TextAttributeModifier::SetCompressLeadingPunctuationImpl,
        TextAttributeModifier::SetIncludeFontPaddingImpl,
        TextAttributeModifier::SetFallbackLineSpacingImpl,
        TextAttributeModifier::SetFontImpl,
        TextAttributeModifier::SetFontWeightImpl,
        TextAttributeModifier::SetSelectionImpl,
        TextAttributeModifier::SetBindSelectionMenuImpl,
    };
    return &ArkUITextModifierImpl;
}

}
