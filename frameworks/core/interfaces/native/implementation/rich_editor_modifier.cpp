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

#include "core/components_ng/pattern/rich_editor/rich_editor_model_ng.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_model_static.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components/common/properties/text_style_parser.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/copy_event_peer.h"
#include "core/interfaces/native/implementation/cut_event_peer.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "rich_editor_controller_peer_impl.h"
#include "rich_editor_styled_string_controller_peer_impl.h"
#include "core/interfaces/native/utility/validators.h"

namespace OHOS::Ace::NG::Converter {
namespace {
using Union_Span_Result = Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;
} // namespace

void AssignArkValue(Ark_RichEditorSelection& dst, const BaseEventInfo& src, Converter::ConvContext *ctx)
{
    CHECK_NULL_VOID(src.GetType() == "SelectionInfo");
    auto selectionInfo = static_cast<const SelectionInfo*>(&src);
    CHECK_NULL_VOID(selectionInfo);
    dst = Converter::ArkValue<Ark_RichEditorSelection>(*selectionInfo, ctx);
}

void AssignArkValue(Ark_RichEditorInsertValue& dst, const RichEditorInsertValue& src, ConvContext *ctx)
{
    dst.insertOffset = Converter::ArkValue<Ark_Int32>(src.GetInsertOffset());
    dst.insertValue = Converter::ArkValue<Ark_String>(src.GetInsertValue(), ctx);
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText(), ctx);
}

void AssignArkValue(Ark_RichEditorSpanPosition& dst, const RichEditorAbstractSpanResult& src)
{
    dst.spanIndex = Converter::ArkValue<Ark_Int32>(src.GetSpanIndex());
    dst.spanRange.value0 = Converter::ArkValue<Ark_Int32>(src.GetSpanRangeStart());
    dst.spanRange.value1 = Converter::ArkValue<Ark_Int32>(src.GetSpanRangeEnd());
}

void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.GetTextDecoration());
    dst.color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetColor(), ctx);
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.GetTextDecorationStyle());
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.fontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetFontColor(), ctx);
    dst.fontSize = Converter::ArkValue<Ark_Float64>(src.GetFontSize());
    dst.fontStyle = Converter::ArkValue<Ark_FontStyle>(src.GetFontStyle());
    dst.fontWeight = Converter::ArkValue<Ark_Int32>(src.GetFontWeight());
    dst.fontFamily = Converter::ArkValue<Ark_String>(src.GetFontFamily(), ctx);
    dst.decoration = Converter::ArkValue<Ark_DecorationStyleResult>(src);
    const auto& textStyle = src.GetTextStyle();
    const auto& textShadows = textStyle.textShadows;
    dst.textShadow = (textShadows.size() > 0) ? ArkValue<Opt_Array_ShadowOptions>(textShadows, ctx)
        : ArkValue<Opt_Array_ShadowOptions>(Ark_Empty(), ctx);
    dst.letterSpacing = Converter::ArkValue<Opt_Float64>(textStyle.letterSpacing);
    dst.lineHeight = Converter::ArkValue<Opt_Float64>(textStyle.lineHeight);
    const auto& fontFeatures = src.GetFontFeatures();
    dst.fontFeature = (fontFeatures.size() > 0)
        ? Converter::ArkValue<Opt_String>(UnParseFontFeatureSetting(fontFeatures), ctx)
        : Converter::ArkValue<Opt_String>(Ark_Empty(), ctx);
    dst.textBackgroundStyle = ArkValue<Opt_TextBackgroundStyle>(textStyle.textBackgroundStyle, ctx);
}

void AssignArkValue(Ark_RichEditorUrlStyle& dst, const std::u16string& src, ConvContext *ctx)
{
    Ark_ResourceStr arkResourceStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(src, ctx);
    dst.url = Converter::ArkValue<Opt_ResourceStr>(arkResourceStr);
}

void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);
    dst.value = Converter::ArkValue<Ark_String>(src.GetValue(), ctx);
    dst.textStyle = Converter::ArkValue<Ark_RichEditorTextStyleResult>(src, ctx);
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText(), ctx);
    dst.offsetInSpan.value0 = Converter::ArkValue<Ark_Int32>(src.OffsetInSpan());
    dst.offsetInSpan.value1 = Converter::ArkValue<Ark_Int32>(src.OffsetInSpan() + src.GetEraseLength());
    dst.symbolSpanStyle = ArkValue<Opt_RichEditorSymbolSpanStyle>(Ark_Empty());
    dst.valueResource = ArkValue<Opt_Resource>(Ark_Empty());
    dst.paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(src.GetTextStyle(), ctx);
    const auto& urlAddress = src.GetUrlAddress();
    dst.urlStyle = urlAddress.empty() ? Converter::ArkValue<Opt_RichEditorUrlStyle>(Ark_Empty())
        : Converter::ArkValue<Opt_RichEditorUrlStyle>(urlAddress, ctx);
    // style for symbol span
    CHECK_NULL_VOID(src.GetType() == SpanResultType::SYMBOL);
    dst.value = Converter::ArkValue<Ark_String>(src.GetValueString(), ctx);
    dst.symbolSpanStyle = ArkValue<Opt_RichEditorSymbolSpanStyle>(src.GetSymbolSpanStyle(), ctx);
    if (auto valueResource = src.GetValueResource()) {
        dst.valueResource = ArkValue<Opt_Resource>(*valueResource, ctx);
    }
}

void AssignArkValue(Ark_RichEditorImageSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);
    if (auto pixelMap = src.GetValuePixelMap()) {
        Ark_image_PixelMap arkPixelMap = new image_PixelMapPeer();
        arkPixelMap->pixelMap = pixelMap;
        dst.valuePixelMap = Converter::ArkValue<Opt_image_PixelMap>(arkPixelMap);
    } else {
        dst.valuePixelMap = Converter::ArkValue<Opt_image_PixelMap>(Ark_Empty());
    }
    auto valueResourceStr = src.GetValueResourceStr();
    dst.valueResourceStr = valueResourceStr.empty() ? Converter::ArkUnion<Opt_ResourceStr>(Ark_Empty())
        : Converter::ArkUnion<Opt_ResourceStr, Ark_String>(valueResourceStr, ctx);
    dst.imageStyle.size.value0 = Converter::ArkValue<Ark_Int32>(src.GetSizeWidth());
    dst.imageStyle.size.value1 = Converter::ArkValue<Ark_Int32>(src.GetSizeHeight());
    dst.imageStyle.objectFit = Converter::ArkValue<Ark_ImageFit>(src.GetObjectFit());
    auto verticalAlign = static_cast<int32_t>(src.GetVerticalAlign());
    bool isVerticalAlignVaild = verticalAlign >= static_cast<int32_t>(VerticalAlign::TOP)
        && verticalAlign <= static_cast<int32_t>(VerticalAlign::BASELINE);
    auto imageVerticalAlign = isVerticalAlignVaild ? src.GetVerticalAlign() : VerticalAlign::BOTTOM;
    dst.imageStyle.verticalAlign = Converter::ArkValue<Ark_ImageSpanAlignment>(imageVerticalAlign);
    ImageStyleResult imageStyleResult {
        .borderRadius = src.GetBorderRadius(),
        .margin = src.GetMargin()
    };
    dst.imageStyle.layoutStyle = ArkValue<Opt_RichEditorLayoutStyle>(imageStyleResult);
    dst.offsetInSpan.value0 = Converter::ArkValue<Ark_Int32>(src.OffsetInSpan());
    dst.offsetInSpan.value1 = Converter::ArkValue<Ark_Int32>(src.OffsetInSpan() + src.GetEraseLength());
}

template<typename To>
std::vector<To> ArkDeleteValueConvert(const RichEditorDeleteValue& src, ConvContext *ctx)
{
    std::vector<To> values;
    for (const RichEditorAbstractSpanResult& spanResult : src.GetRichEditorDeleteSpans()) {
        auto spanType = spanResult.GetType();
        if (spanType == SpanResultType::TEXT) {
            auto textSpanResult = ArkValue<Ark_RichEditorTextSpanResult>(spanResult, ctx);
            auto unionValue = ArkUnion<To, Ark_RichEditorTextSpanResult>(textSpanResult);
            values.push_back(unionValue);
        } else if (spanType == SpanResultType::IMAGE) {
            auto imageSpanResult = ArkValue<Ark_RichEditorImageSpanResult>(spanResult, ctx);
            auto unionValue = ArkUnion<To, Ark_RichEditorImageSpanResult>(imageSpanResult);
            values.push_back(unionValue);
        } else if (spanType == SpanResultType::SYMBOL) {
            auto symbolSpanResult = ArkValue<Ark_RichEditorTextSpanResult>(spanResult, ctx);
            auto unionValue = ArkUnion<To, Ark_RichEditorTextSpanResult>(symbolSpanResult);
            values.push_back(unionValue);
        }
    }
    return values;
}

void AssignArkValue(Ark_RichEditorDeleteValue& dst, const RichEditorDeleteValue& src, Converter::ConvContext *ctx)
{
    dst.offset = Converter::ArkValue<Ark_Int32>(src.GetOffset());
    dst.direction = Converter::ArkValue<Ark_RichEditorDeleteDirection>(src.GetRichEditorDeleteDirection());
    dst.length = Converter::ArkValue<Ark_Int32>(src.GetLength());
    auto values = Converter::ArkDeleteValueConvert<Union_Span_Result>(src, ctx);
    dst.richEditorDeleteSpans = ArkValue<Array_Union_RichEditorTextSpanResult_RichEditorImageSpanResult>(values, ctx);
}

void AssignArkValue(Ark_RichEditorChangeValue& dst, const RichEditorChangeValue& src, Converter::ConvContext *ctx)
{
    auto rangeBefore = src.GetRangeBefore();
    dst.rangeBefore.start = Converter::ArkValue<Opt_Int32>(rangeBefore.start);
    dst.rangeBefore.end = Converter::ArkValue<Opt_Int32>(rangeBefore.end);
    dst.replacedSpans = Converter::ArkValue<Array_RichEditorTextSpanResult>(src.GetRichEditorReplacedSpans(), ctx);
    dst.replacedImageSpans = Converter::ArkValue<Array_RichEditorImageSpanResult>(
        src.GetRichEditorReplacedImageSpans(), ctx);
    dst.replacedSymbolSpans = Converter::ArkValue<Array_RichEditorTextSpanResult>(
        src.GetRichEditorReplacedSymbolSpans(), ctx);
}

PlaceholderOptions GetThemePlaceholderOptions()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, PlaceholderOptions{});
    auto textTheme = pipelineContext->GetTheme<TextTheme>();
    TextStyle textStyle = textTheme ? textTheme->GetTextStyle() : TextStyle();
    auto richEditorTheme = pipelineContext->GetTheme<OHOS::Ace::NG::RichEditorTheme>();
    return PlaceholderOptions {
        .value = std::nullopt,
        .fontWeight = textStyle.GetFontWeight(),
        .fontSize = textStyle.GetFontSize(),
        .fontColor = richEditorTheme ? richEditorTheme->GetPlaceholderColor() : Color(),
        .fontStyle = textStyle.GetFontStyle(),
        .fontFamilies = textStyle.GetFontFamilies()
    };
}

template<>
void AssignCast(std::optional<PlaceholderOptions>& dst, const Ark_PlaceholderStyle& src)
{
    dst = GetThemePlaceholderOptions();
    CHECK_NULL_VOID(dst.has_value());
    if (auto fontColor = Converter::OptConvert<Color>(src.fontColor)) {
        dst->fontColor = fontColor;
    }
    CHECK_NULL_VOID(src.font.tag != INTEROP_TAG_UNDEFINED);
    auto arkFont = src.font.value;
    if (auto fontSize = Converter::OptConvert<Dimension>(arkFont.size)) {
        dst->fontSize = fontSize;
    }
    if (auto fontWeight = Converter::OptConvert<FontWeight>(arkFont.weight)) {
        dst->fontWeight = fontWeight;
    }
    auto fontFamilyStr = Converter::OptConvert<std::string>(arkFont.family);
    if (fontFamilyStr && fontFamilyStr->length() > 0) {
        dst->fontFamilies = std::vector<std::string>{ fontFamilyStr.value() };
    }
    if (auto fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(arkFont.style)) {
        dst->fontStyle = fontStyle;
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = RichEditorModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // RichEditorModifier
namespace RichEditorInterfaceModifier {
void SetRichEditorOptions0Impl(Ark_NativePointer node,
                               const Ark_RichEditorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->controller);
    // obtain the internal RichEditorController
    RefPtr<RichEditorBaseControllerBase> controller = RichEditorModelStatic::GetRichEditorController(frameNode);
    CHECK_NULL_VOID(controller);

    // pass the internal controller to external management
    value->controller->AddTargetController(controller);
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    RichEditorModelStatic::SetStyledStringMode(frameNode, true);
    CHECK_NULL_VOID(options->controller);
    // obtain the internal Styled String RichEditorController
    RefPtr<RichEditorBaseControllerBase> controller =
        RichEditorModelStatic::GetRichEditorStyledStringController(frameNode);
    CHECK_NULL_VOID(controller);

    options->controller->AddTargetController(controller);
}
void SetRichEditorOptionsImpl(Ark_NativePointer node,
                              const Ark_Union_RichEditorOptions_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    options->selector == 0 ? SetRichEditorOptions0Impl(node, &(options->value0))
        : SetRichEditorOptions1Impl(node, &(options->value1));
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void SetOnReadyImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    CHECK_NULL_VOID(optValue);
    auto onCallback = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    RichEditorModelNG::SetOnReady(frameNode, std::move(onCallback));
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_RichEditorSelection_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnSelect(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        Converter::ConvContext ctx;
        auto selection = Converter::ArkValue<Ark_RichEditorSelection>(*event, &ctx);
        arkCallback.InvokeSync(selection);
    };
    RichEditorModelNG::SetOnSelect(frameNode, std::move(onCallback));
}
void SetOnSelectionChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_RichEditorRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnSelectionChange(frameNode, nullptr);
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto range = Converter::ArkValue<Ark_RichEditorRange>(*event);
        arkCallback.InvokeSync(range);
    };
    RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(onCallback));
}
void SetAboutToIMEInputImpl(Ark_NativePointer node,
                            const Opt_Callback_RichEditorInsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetAboutToIMEInput(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue),
        frameNode](const RichEditorInsertValue& param) -> bool {
        Converter::ConvContext ctx;
        Ark_RichEditorInsertValue data = Converter::ArkValue<Ark_RichEditorInsertValue>(param, &ctx);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(onCallback));
}
void SetOnIMEInputCompleteImpl(Ark_NativePointer node,
                               const Opt_Callback_RichEditorTextSpanResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnIMEInputComplete(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const RichEditorAbstractSpanResult& param) {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorTextSpanResult>(param, &ctx);
        arkCallback.InvokeSync(data);
    };
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(onCallback));
}
void SetOnDidIMEInputImpl(Ark_NativePointer node,
                          const Opt_Callback_TextRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnDidIMEInput(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const TextRange& param) {
        auto data = Converter::ArkValue<Ark_TextRange>(param);
        arkCallback.InvokeSync(data);
    };
    RichEditorModelNG::SetOnDidIMEInput(frameNode, std::move(onCallback));
}
void SetAboutToDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_RichEditorDeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelStatic::SetAboutToDelete(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue), frameNode](const RichEditorDeleteValue& param) -> bool {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorDeleteValue>(param, &ctx);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelStatic::SetAboutToDelete(frameNode, std::move(onCallback));
}
void SetOnDeleteCompleteImpl(Ark_NativePointer node,
                             const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnDeleteComplete(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.InvokeSync();
    };
    RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(onCallback));
}
void SetCopyOptionsImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvertPtr<CopyOptions>(value);
    if (options) {
        RichEditorModelNG::SetCopyOption(frameNode, options.value());
    } else {
        auto value = OHOS::Ace::CopyOptions::Local;
        RichEditorModelNG::SetCopyOption(frameNode, value);
    }
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_PasteEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnPaste(frameNode, nullptr);
        return;
    }
    auto onPaste = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) -> void {
        Ark_PasteEvent arkEvent = PasteEventPeer::Create();
        CHECK_NULL_VOID(arkEvent);
        auto preventDefault = [&event]() { event.SetPreventDefault(true); };
        arkEvent->SetPreventDefault(preventDefault);
        arkCallback.InvokeSync(Converter::ArkValue<Opt_PasteEvent>(arkEvent));
    };
    RichEditorModelStatic::SetOnPaste(frameNode, std::move(onPaste));
}
void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        RichEditorModelNG::SetTextDetectEnable(frameNode, false);
        return;
    }
    RichEditorModelNG::SetTextDetectEnable(frameNode, *convValue);
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        RichEditorModelNG::SetSupportPreviewText(frameNode, true);
        return;
    }
    RichEditorModelNG::SetSupportPreviewText(frameNode, *convValue);
}
void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextDetectConfig>(value);
    if (!convValue) {
        // Implement Reset value
        return;
    }
    RichEditorModelNG::SetTextDetectConfig(frameNode, *convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    RichEditorModelStatic::SetCaretColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto richEditorTheme = pipelineContext->GetTheme<RichEditorTheme>();
    CHECK_NULL_VOID(richEditorTheme);
    auto selectedBackgroundColor = richEditorTheme->GetSelectedBackgroundColor();
    if (!convValue) {
        RichEditorModelStatic::SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
        return;
    }
    RichEditorModelStatic::SetSelectedBackgroundColor(frameNode, convValue);
}
void SetOnEditingChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnEditingChange(frameNode, nullptr);
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const bool& param) {
        Ark_Boolean flag = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.InvokeSync(flag);
    };
    RichEditorModelNG::SetOnEditingChange(frameNode, std::move(onCallback));
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextInputAction>(value);
    RichEditorModelStatic::SetEnterKeyType(frameNode, convValue);
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_SubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnSubmit(frameNode, nullptr);
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](int32_t param1,
        NG::TextFieldCommonEvent& param2) {
        auto enterKey = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(param1));
        const auto event = Converter::ArkSubmitEventSync(param2);
        arkCallback.InvokeSync(enterKey, event.ArkValue());
    };
    RichEditorModelNG::SetOnSubmit(frameNode, std::move(onCallback));
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnWillChange(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue),
        frameNode](const RichEditorChangeValue& param) -> bool {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorChangeValue>(param, &ctx);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(onCallback));
}
void SetOnDidChangeImpl(Ark_NativePointer node,
                        const Opt_OnDidChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelNG::SetOnDidChange(frameNode, nullptr);
        return;
    }
    CHECK_NULL_VOID(!RichEditorModelStatic::IsStyledStringMode(frameNode));
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const RichEditorChangeValue& param) {
        TextRange inBefore = param.GetRangeBefore();
        TextRange inAfter = param.GetRangeAfter();
        Ark_TextRange rangeBefore = Converter::ArkValue<Ark_TextRange>(inBefore);
        Ark_TextRange rangeAfter = Converter::ArkValue<Ark_TextRange>(inAfter);
        arkCallback.InvokeSync(rangeBefore, rangeAfter);
    };
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(onCallback));
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_CutEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelStatic::SetOnCut(frameNode, nullptr);
        return;
    }
    auto onCut = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) {
        Ark_CutEvent arkEvent = CutEventPeer::Create();
        CHECK_NULL_VOID(arkEvent);
        auto preventDefault = [&event]() { event.SetPreventDefault(true); };
        arkEvent->SetPreventDefault(preventDefault);
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelStatic::SetOnCut(frameNode, std::move(onCut));
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_CopyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelStatic::SetOnCopy(frameNode, nullptr);
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) {
        Ark_CopyEvent arkEvent = CopyEventPeer::Create();
        CHECK_NULL_VOID(arkEvent);
        auto preventDefault = [&event]() { event.SetPreventDefault(true); };
        arkEvent->SetPreventDefault(preventDefault);
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelStatic::SetOnCopy(frameNode, std::move(onCopy));
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelStatic::SetSelectionMenuOptions(frameNode, nullptr, nullptr);
        return;
    }
    auto createMenuCallback = Converter::GetOpt(optValue->onCreateMenu);
    std::function<std::vector<NG::MenuOptionsParam>(const std::vector<NG::MenuItemParam>&)> onCreateMenuCallback =
        nullptr;
    if (createMenuCallback) {
        onCreateMenuCallback =
            [arkCreateMenu = CallbackHelper(*createMenuCallback)](
                const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
            auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
            auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
                Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
            return result.value_or(std::vector<NG::MenuOptionsParam>());
        };
    }
    auto menuItemClickCallback = Converter::GetOpt(optValue->onMenuItemClick);
    std::function<bool(NG::MenuItemParam)> onMenuItemClickCallback = nullptr;
    if (menuItemClickCallback) {
        onMenuItemClickCallback = [arkMenuItemClick = CallbackHelper(*menuItemClickCallback)](
                                      NG::MenuItemParam menuOptionsParam) -> bool {
            TextRange range { .start = menuOptionsParam.start, .end = menuOptionsParam.end };
            auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
            auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
            auto arkResult =
                arkMenuItemClick.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
            return Converter::Convert<bool>(arkResult);
        };
    }
    RichEditorModelStatic::SetSelectionMenuOptions(
        frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClickCallback));
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, true);
        return;
    }
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, *convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        RichEditorModelStatic::SetEnableHapticFeedback(frameNode, true);
        return;
    }
    RichEditorModelStatic::SetEnableHapticFeedback(frameNode, *convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<DisplayMode>(value);
    RichEditorModelNG::SetBarState(frameNode, convValue.value_or(DisplayMode::AUTO));
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    Validator::ValidateNonNegative(convValue);
    RichEditorModelStatic::SetMaxLength(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    auto isValid = convValue && (convValue.value() > 0);
    auto maxLineValue = isValid ? Converter::OptConvert<uint32_t>(*value).value_or(UINT_MAX) : UINT_MAX;
    RichEditorModelStatic::SetMaxLines(frameNode, maxLineValue);
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<KeyboardAppearance>(value);
    RichEditorModelNG::SetKeyboardAppearance(frameNode, convValue.value_or(KeyboardAppearance::NONE_IMMERSIVE));
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    RichEditorModelNG::SetStopBackPress(frameNode, convValue.value_or(true));
}
void SetBindSelectionMenuImpl(Ark_NativePointer node,
                              const Opt_RichEditorSpanType* spanType,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                              const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceSpanType = Converter::OptConvertPtr<TextSpanType>(spanType);
    auto aceResponseType = Converter::OptConvertPtr<TextResponseType>(responseType);
    auto response = aceResponseType.value_or(TextResponseType::LONG_PRESS);
    auto span = aceSpanType.value_or(TextSpanType::TEXT);
    auto convMenuParam = Converter::OptConvertPtr<SelectMenuParam>(options).value_or(SelectMenuParam{});
    auto optContent = Converter::GetOptPtr(content);
    if (!optContent) {
        std::function<void()> builder = {};
        RichEditorModelStatic::BindSelectionMenu(frameNode, span, response, builder, convMenuParam);
        return;
    }
    CallbackHelper(*optContent).BuildAsync([frameNode, span, response, convMenuParam](
        const RefPtr<UINode>& uiNode) mutable {
        std::function<void()> builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        RichEditorModelStatic::BindSelectionMenu(frameNode, span, response, builder, convMenuParam);
        }, node);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ark_KeyboardOptions>(options);
    std::optional<bool> supportAvoidance;
    if (convValue) {
        supportAvoidance = Converter::OptConvert<bool>(convValue->supportAvoidance);
    }
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        RichEditorModelStatic::SetCustomKeyboard(frameNode, nullptr, std::nullopt);
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        RichEditorModelStatic::SetCustomKeyboard(frameNode, std::move(builder), supportAvoidance);
        }, node);
}
void SetPlaceholderImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    PlaceholderOptions options;
    if (auto value = Converter::OptConvertPtr<PlaceholderOptions>(style); value) {
        options = *value;
    }
    options.value = Converter::OptConvertPtr<std::u16string>(value);
    RichEditorModelNG::SetPlaceholder(frameNode, options);
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
        RichEditorInterfaceModifier::SetRichEditorOptionsImpl,
        RichEditorAttributeModifier::SetOnReadyImpl,
        RichEditorAttributeModifier::SetOnSelectImpl,
        RichEditorAttributeModifier::SetOnSelectionChangeImpl,
        RichEditorAttributeModifier::SetAboutToIMEInputImpl,
        RichEditorAttributeModifier::SetOnIMEInputCompleteImpl,
        RichEditorAttributeModifier::SetOnDidIMEInputImpl,
        RichEditorAttributeModifier::SetAboutToDeleteImpl,
        RichEditorAttributeModifier::SetOnDeleteCompleteImpl,
        RichEditorAttributeModifier::SetCopyOptionsImpl,
        RichEditorAttributeModifier::SetOnPasteImpl,
        RichEditorAttributeModifier::SetEnableDataDetectorImpl,
        RichEditorAttributeModifier::SetEnablePreviewTextImpl,
        RichEditorAttributeModifier::SetDataDetectorConfigImpl,
        RichEditorAttributeModifier::SetCaretColorImpl,
        RichEditorAttributeModifier::SetSelectedBackgroundColorImpl,
        RichEditorAttributeModifier::SetOnEditingChangeImpl,
        RichEditorAttributeModifier::SetEnterKeyTypeImpl,
        RichEditorAttributeModifier::SetOnSubmitImpl,
        RichEditorAttributeModifier::SetOnWillChangeImpl,
        RichEditorAttributeModifier::SetOnDidChangeImpl,
        RichEditorAttributeModifier::SetOnCutImpl,
        RichEditorAttributeModifier::SetOnCopyImpl,
        RichEditorAttributeModifier::SetEditMenuOptionsImpl,
        RichEditorAttributeModifier::SetEnableKeyboardOnFocusImpl,
        RichEditorAttributeModifier::SetEnableHapticFeedbackImpl,
        RichEditorAttributeModifier::SetBarStateImpl,
        RichEditorAttributeModifier::SetMaxLengthImpl,
        RichEditorAttributeModifier::SetMaxLinesImpl,
        RichEditorAttributeModifier::SetKeyboardAppearanceImpl,
        RichEditorAttributeModifier::SetStopBackPressImpl,
        RichEditorAttributeModifier::SetBindSelectionMenuImpl,
        RichEditorAttributeModifier::SetCustomKeyboardImpl,
        RichEditorAttributeModifier::SetPlaceholderImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
