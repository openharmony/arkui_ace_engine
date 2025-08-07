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
#include "core/components_ng/base/frame_node.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "rich_editor_controller_peer_impl.h"
#include "rich_editor_styled_string_controller_peer_impl.h"

namespace OHOS::Ace::NG::Converter {
namespace {
using Union_Span_Result = Ark_Union_RichEditorTextSpanResult_RichEditorImageSpanResult;

void SetImageSpanResult(Union_Span_Result& dst, const ResultObject& src, Converter::ConvContext *ctx)
{
    Ark_RichEditorImageSpanResult imageSpanResult;
    imageSpanResult.spanPosition.spanIndex = Converter::ArkValue<Ark_Number>(src.spanPosition.spanIndex);
    imageSpanResult.spanPosition.spanRange.value0 = Converter::ArkValue<Ark_Number>(src.spanPosition.spanRange[0]);
    imageSpanResult.spanPosition.spanRange.value1 = Converter::ArkValue<Ark_Number>(src.spanPosition.spanRange[1]);

    Ark_PixelMap arkPixelMap = new PixelMapPeer();
    arkPixelMap->pixelMap = src.valuePixelMap;
    imageSpanResult.valuePixelMap = Converter::ArkValue<Opt_PixelMap>(arkPixelMap);

    if (src.valueResource) {
        imageSpanResult.valueResourceStr =
            Converter::ArkUnion<Opt_ResourceStr, Ark_Resource>(*src.valueResource, ctx);
    }
    imageSpanResult.imageStyle = Converter::ArkValue<Ark_RichEditorImageSpanStyleResult>(src.imageStyle);
    imageSpanResult.offsetInSpan.value0 = Converter::ArkValue<Ark_Number>(src.offsetInSpan[0]);
    imageSpanResult.offsetInSpan.value1 = Converter::ArkValue<Ark_Number>(src.offsetInSpan[1]);

    dst = Converter::ArkUnion<Union_Span_Result, Ark_RichEditorImageSpanResult>(imageSpanResult);
}

void SetTextSpanResult(Union_Span_Result& dst, const ResultObject& src, Converter::ConvContext *ctx)
{
    Ark_RichEditorTextSpanResult textSpanResult;

    // Set span position
    textSpanResult.spanPosition.spanIndex = Converter::ArkValue<Ark_Number>(src.spanPosition.spanIndex);
    textSpanResult.spanPosition.spanRange.value0 = Converter::ArkValue<Ark_Number>(src.spanPosition.spanRange[0]);
    textSpanResult.spanPosition.spanRange.value1 = Converter::ArkValue<Ark_Number>(src.spanPosition.spanRange[1]);

    // Set text value
    textSpanResult.value = Converter::ArkValue<Ark_String>(src.valueString, ctx);

    // Set text style
    textSpanResult.textStyle.fontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(
        src.textStyle.fontColor, ctx);
    textSpanResult.textStyle.fontSize = Converter::ArkValue<Ark_Number>(src.textStyle.fontSize);
    textSpanResult.textStyle.fontStyle = Converter::ArkValue<Ark_FontStyle>(
        static_cast<OHOS::Ace::FontStyle>(src.textStyle.fontStyle));
    textSpanResult.textStyle.fontWeight = Converter::ArkValue<Ark_Number>(src.textStyle.fontWeight);
    textSpanResult.textStyle.fontFamily = Converter::ArkValue<Ark_String>(src.textStyle.fontFamily, ctx);

    // Set decoration
    textSpanResult.textStyle.decoration.type = Converter::ArkValue<Ark_TextDecorationType>(
        static_cast<OHOS::Ace::TextDecoration>(src.textStyle.decorationType));
    textSpanResult.textStyle.decoration.color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(
        src.textStyle.decorationColor, ctx);
    textSpanResult.textStyle.decoration.style.value = Converter::ArkValue<Ark_TextDecorationStyle>(
        static_cast<OHOS::Ace::TextDecorationStyle>(src.textStyle.decorationStyle));

    // Set other text properties
    textSpanResult.textStyle.letterSpacing = Converter::ArkValue<Opt_Number>(src.textStyle.letterSpacing);
    textSpanResult.textStyle.lineHeight = Converter::ArkValue<Opt_Number>(src.textStyle.lineHeight);
    textSpanResult.textStyle.fontFeature.value = Converter::ArkValue<Ark_String>(src.textStyle.fontFeature, ctx);

    // Set preview text if available
    textSpanResult.previewText = Converter::ArkValue<Opt_String>(src.previewText, ctx);

    // Set offset in span
    textSpanResult.offsetInSpan.value0 = Converter::ArkValue<Ark_Number>(src.offsetInSpan[0]);
    textSpanResult.offsetInSpan.value1 = Converter::ArkValue<Ark_Number>(src.offsetInSpan[1]);

    // Set symbol span style
    textSpanResult.symbolSpanStyle.value = Converter::ArkValue<Ark_RichEditorSymbolSpanStyle>(
        src.symbolSpanStyle, ctx);

    // Set resource if available
    if (src.valueResource) {
        textSpanResult.valueResource.value = Converter::ArkValue<Ark_Resource>(*src.valueResource, ctx);
    }

    dst = Converter::ArkUnion<Union_Span_Result, Ark_RichEditorTextSpanResult>(textSpanResult);
}
} // namespace

void AssignArkValue(Ark_RichEditorSelection& dst, const BaseEventInfo& src, Converter::ConvContext *ctx)
{
    if (src.GetType() == "SelectionInfo") {
        auto selectionInfo = static_cast<const SelectionInfo*>(&src);
        if (!selectionInfo) {
            return;
        }
        auto selection = selectionInfo->GetSelection();
        // Setting selection
        dst.selection.value0 = Converter::ArkValue<Ark_Number>(selection.selection[0]);
        dst.selection.value1 = Converter::ArkValue<Ark_Number>(selection.selection[1]);
        // Setting span results
        std::list<ResultObject>& resultObjects = selection.resultObjects;
        if (resultObjects.empty()) {
            dst.spans.length = 0;
            dst.spans.array = nullptr;
            return;
        }
        dst.spans.length = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(resultObjects.size()));
        dst.spans.array = new Union_Span_Result[resultObjects.size()];
        size_t idx = 0;
        for (auto& resultObject : resultObjects) {
            Union_Span_Result* to = dst.spans.array + idx;
            if (resultObject.type == SelectSpanType::TYPEIMAGE) {
                SetImageSpanResult(*to, resultObject, ctx);
            } else if (resultObject.type == SelectSpanType::TYPESPAN) {
                SetTextSpanResult(*to, resultObject, ctx);
            }
            idx++;
        }
    }
}

void AssignArkValue(Ark_RichEditorRange& dst, const BaseEventInfo& src)
{
    if (src.GetType() == "SelectionInfo") {
        auto selectionInfo = static_cast<const SelectionInfo*>(&src);
        if (selectionInfo) {
            auto selection = selectionInfo->GetSelection();
            dst.start = Converter::ArkValue<Opt_Number>(selection.selection[0]);
            dst.end = Converter::ArkValue<Opt_Number>(selection.selection[1]);
        }
    } else if (src.GetType() == "SelectionRangeInfo") {
        auto selectionRangeInfo = static_cast<const SelectionRangeInfo*>(&src);
        if (selectionRangeInfo) {
            dst.start = Converter::ArkValue<Opt_Number>(selectionRangeInfo->start_);
            dst.end = Converter::ArkValue<Opt_Number>(selectionRangeInfo->end_);
        }
    }
}

void AssignArkValue(Ark_RichEditorInsertValue& dst, const RichEditorInsertValue& src, ConvContext *ctx)
{
    dst.insertOffset = Converter::ArkValue<Ark_Number>(src.GetInsertOffset());
    dst.insertValue = Converter::ArkValue<Ark_String>(src.GetInsertValue(), ctx);
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText(), ctx);
}

void AssignArkValue(Ark_RichEditorSpanPosition& dst, const RichEditorAbstractSpanResult& src)
{
    dst.spanIndex = Converter::ArkValue<Ark_Number>(src.GetSpanIndex());
    dst.spanRange.value0 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeStart());
    dst.spanRange.value1 = Converter::ArkValue<Ark_Number>(src.GetSpanRangeEnd());
}

void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.GetTextDecoration());
    dst.color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetColor());
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.GetTextDecorationStyle());
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src)
{
    dst.fontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetFontColor());
    dst.fontSize = Converter::ArkValue<Ark_Number>(src.GetFontSize());
    dst.fontStyle = Converter::ArkValue<Ark_FontStyle>(src.GetFontStyle());
    dst.fontWeight = Converter::ArkValue<Ark_Number>(src.GetFontWeight());
    dst.fontFamily = Converter::ArkValue<Ark_String>(src.GetFontFamily());
    dst.decoration = Converter::ArkValue<Ark_DecorationStyleResult>(src);
    LOGW("RichEditor modifier :: textShadow conversion is not implemented yet.");
    dst.letterSpacing = Converter::ArkValue<Opt_Number>(src.GetLetterspacing());
    dst.lineHeight = Converter::ArkValue<Opt_Number>(src.GetLineHeight());
    dst.fontFeature = Converter::ArkValue<Opt_String>(src.GetFontFeatures());
}

void AssignArkValue(Ark_RichEditorTextSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);
    dst.value = Converter::ArkValue<Ark_String>(src.GetValue(), ctx);
    dst.textStyle = Converter::ArkValue<Ark_RichEditorTextStyleResult>(src);
    dst.symbolSpanStyle = Converter::ArkValue<Opt_RichEditorSymbolSpanStyle>(src.GetSymbolSpanStyle(), ctx);
    if (src.GetValueResource()) {
        dst.valueResource = Converter::ArkValue<Opt_Resource>(*src.GetValueResource(), ctx);
    } else {
        dst.valueResource = Converter::ArkValue<Opt_Resource>();
    }
    dst.previewText = Converter::ArkValue<Opt_String>(src.GetPreviewText(), ctx);
    dst.offsetInSpan.value0 = Converter::ArkValue<Ark_Number>(src.GetSpanIndex());
    dst.offsetInSpan.value1 = Converter::ArkValue<Ark_Number>(src.OffsetInSpan());
}

void AssignArkValue(Ark_RichEditorImageSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);

    if (src.GetValuePixelMap()) {
        Ark_PixelMap arkPixelMap = new PixelMapPeer();
        arkPixelMap->pixelMap = src.GetValuePixelMap();
        dst.valuePixelMap = Converter::ArkValue<Opt_PixelMap>(arkPixelMap);
    }

    if (!src.GetValueResourceStr().empty()) {
        dst.valueResourceStr = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(src.GetValueResourceStr(), ctx);
    }

    dst.imageStyle.size.value0 = Converter::ArkValue<Ark_Number>(src.GetSizeWidth());
    dst.imageStyle.size.value1 = Converter::ArkValue<Ark_Number>(src.GetSizeHeight());
    dst.imageStyle.objectFit = Converter::ArkValue<Ark_ImageFit>(src.GetObjectFit());
    dst.imageStyle.verticalAlign = Converter::ArkValue<Ark_ImageSpanAlignment>(src.GetVerticalAlign());
    dst.offsetInSpan.value0 = Converter::ArkValue<Ark_Number>(src.GetSpanIndex());
    dst.offsetInSpan.value1 = Converter::ArkValue<Ark_Number>(src.OffsetInSpan());
}

void AssignArkValue(Ark_TextRange& dst, const TextRange& src)
{
    dst.start = Converter::ArkValue<Opt_Number>(src.start);
    dst.end = Converter::ArkValue<Opt_Number>(src.end);
}

void AssignArkValue(Ark_RichEditorDeleteValue& dst, const RichEditorDeleteValue& src)
{
    dst.offset = Converter::ArkValue<Ark_Number>(src.GetOffset());
    dst.direction = Converter::ArkValue<Ark_RichEditorDeleteDirection>(src.GetRichEditorDeleteDirection());
    dst.length = Converter::ArkValue<Ark_Number>(src.GetLength());
}

void AssignArkValue(Ark_RichEditorChangeValue& dst, const RichEditorChangeValue& src, Converter::ConvContext *ctx)
{
    auto rangeBefore = src.GetRangeBefore();
    dst.rangeBefore.start = Converter::ArkValue<Opt_Number>(rangeBefore.start);
    dst.rangeBefore.end = Converter::ArkValue<Opt_Number>(rangeBefore.end);
    dst.replacedSpans = Converter::ArkValue<Array_RichEditorTextSpanResult>(src.GetRichEditorReplacedSpans(), ctx);
    dst.replacedImageSpans = Converter::ArkValue<Array_RichEditorImageSpanResult>(
        src.GetRichEditorReplacedImageSpans(), ctx);
    dst.replacedSymbolSpans = Converter::ArkValue<Array_RichEditorTextSpanResult>(
        src.GetRichEditorReplacedSymbolSpans(), ctx);
}

template<>
void AssignCast(std::optional<PlaceholderOptions>& dst, const Ark_PlaceholderStyle& src)
{
    PlaceholderOptions ret;
    ret.fontSize = Converter::OptConvert<Dimension>(src.font.value.size);
    ret.fontWeight = Converter::OptConvert<FontWeight>(src.font.value.weight);
    ret.fontColor = Converter::OptConvert<Color>(src.fontColor);
    ret.fontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(src.font.value.style);
    dst = ret;
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
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void OnReadyImpl(Ark_NativePointer node,
                 const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    RichEditorModelNG::SetOnReady(frameNode, std::move(onCallback));
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_Callback_RichEditorSelection_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        Converter::ConvContext ctx;
        auto selection = Converter::ArkValue<Ark_RichEditorSelection>(*event, &ctx);
        arkCallback.Invoke(selection);
    };
    RichEditorModelNG::SetOnSelect(frameNode, std::move(onCallback));
}
void OnSelectionChangeImpl(Ark_NativePointer node,
                           const Opt_Callback_RichEditorRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const BaseEventInfo* event) {
        CHECK_NULL_VOID(event);
        auto range = Converter::ArkValue<Ark_RichEditorRange>(*event);
        arkCallback.Invoke(range);
    };
    RichEditorModelNG::SetOnSelectionChange(frameNode, std::move(onCallback));
}
void AboutToIMEInputImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorInsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue),
        frameNode](const RichEditorInsertValue& param) -> bool {
        Converter::ConvContext ctx;
        Ark_RichEditorInsertValue data = Converter::ArkValue<Ark_RichEditorInsertValue>(param, &ctx);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetAboutToIMEInput(frameNode, std::move(onCallback));
}
void OnIMEInputCompleteImpl(Ark_NativePointer node,
                            const Opt_Callback_RichEditorTextSpanResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const RichEditorAbstractSpanResult& param) {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorTextSpanResult>(param, &ctx);
        arkCallback.Invoke(data);
    };
    RichEditorModelNG::SetOnIMEInputComplete(frameNode, std::move(onCallback));
}
void OnDidIMEInputImpl(Ark_NativePointer node,
                       const Opt_Callback_TextRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const TextRange& param) {
        auto data = Converter::ArkValue<Ark_TextRange>(param);
        arkCallback.Invoke(data);
    };
    RichEditorModelNG::SetOnDidIMEInput(frameNode, std::move(onCallback));
}
void AboutToDeleteImpl(Ark_NativePointer node,
                       const Opt_Callback_RichEditorDeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue), frameNode](const RichEditorDeleteValue& param) -> bool {
        auto data = Converter::ArkValue<Ark_RichEditorDeleteValue>(param);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelStatic::SetAboutToDelete(frameNode, std::move(onCallback));
}
void OnDeleteCompleteImpl(Ark_NativePointer node,
                          const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)]() {
        arkCallback.Invoke();
    };
    RichEditorModelNG::SetOnDeleteComplete(frameNode, std::move(onCallback));
}
void CopyOptionsImpl(Ark_NativePointer node,
                     const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvert<CopyOptions>(*value);
    if (options) {
        RichEditorModelNG::SetCopyOption(frameNode, options.value());
    }
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_PasteEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onPaste = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) -> void {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_PasteEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(Converter::ArkValue<Opt_PasteEvent>(arkEvent));
    };
    RichEditorModelStatic::SetOnPaste(frameNode, std::move(onPaste));
}
void EnableDataDetectorImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    RichEditorModelNG::SetTextDetectEnable(frameNode, *convValue);
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    RichEditorModelNG::SetSupportPreviewText(frameNode, *convValue);
}
void DataDetectorConfigImpl(Ark_NativePointer node,
                            const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextDetectConfig>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    RichEditorModelNG::SetTextDetectConfig(frameNode, *convValue);
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    RichEditorModelStatic::SetCaretColor(frameNode, convValue);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    RichEditorModelStatic::SetSelectedBackgroundColor(frameNode, convValue);
}
void OnEditingChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const bool& param) {
        Ark_Boolean flag = Converter::ArkValue<Ark_Boolean>(param);
        arkCallback.Invoke(flag);
    };
    RichEditorModelNG::SetOnEditingChange(frameNode, std::move(onCallback));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextInputAction>(*value);
    RichEditorModelStatic::SetEnterKeyType(frameNode, convValue);
}
void OnSubmitImpl(Ark_NativePointer node,
                  const Opt_SubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
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
void OnWillChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_RichEditorChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue),
        frameNode](const RichEditorChangeValue& param) -> bool {
        Converter::ConvContext ctx;
        auto data = Converter::ArkValue<Ark_RichEditorChangeValue>(param, &ctx);
        auto result = arkCallback.InvokeWithObtainResult<Ark_Boolean, Callback_Boolean_Void>(data);
        return Converter::Convert<bool>(result);
    };
    RichEditorModelNG::SetOnWillChange(frameNode, std::move(onCallback));
}
void OnDidChangeImpl(Ark_NativePointer node,
                     const Opt_OnDidChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCallback = [arkCallback = CallbackHelper(*optValue)](const RichEditorChangeValue& param) {
        TextRange inBefore = param.GetRangeBefore();
        TextRange inAfter = param.GetRangeAfter();
        Ark_TextRange rangeBefore = Converter::ArkValue<Ark_TextRange>(inBefore);
        Ark_TextRange rangeAfter = Converter::ArkValue<Ark_TextRange>(inAfter);
        arkCallback.Invoke(rangeBefore, rangeAfter);
    };
    RichEditorModelNG::SetOnDidChange(frameNode, std::move(onCallback));
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_CutEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCut = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_CutEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelStatic::SetOnCut(frameNode, std::move(onCut));
}
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_CopyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](NG::TextCommonEvent& event) {
        Converter::ConvContext ctx;
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_CopyEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(arkEvent);
    };
    RichEditorModelStatic::SetOnCopy(frameNode, std::move(onCopy));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Opt_EditMenuOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto optValue = Converter::GetOptPtr(value);
    // if (!optValue) {
    //     // TODO: Reset value
    //     return;
    // }
    // auto onCreateMenuCallback = [arkCreateMenu = CallbackHelper(optValue->onCreateMenu)](
    //     const std::vector<NG::MenuItemParam>& systemMenuItems) -> std::vector<NG::MenuOptionsParam> {
    //         auto menuItems = Converter::ArkValue<Array_TextMenuItem>(systemMenuItems, Converter::FC);
    //         auto result = arkCreateMenu.InvokeWithOptConvertResult<std::vector<NG::MenuOptionsParam>,
    //             Array_TextMenuItem, Callback_Array_TextMenuItem_Void>(menuItems);
    //         return result.value_or(std::vector<NG::MenuOptionsParam>());
    //     };
    // auto onMenuItemClick = [arkMenuItemClick = CallbackHelper(optValue->onMenuItemClick)](
    //     NG::MenuItemParam menuOptionsParam) -> bool {
    //         TextRange range {.start = menuOptionsParam.start, .end = menuOptionsParam.end};
    //         auto menuItem = Converter::ArkValue<Ark_TextMenuItem>(menuOptionsParam);
    //         auto arkRange = Converter::ArkValue<Ark_TextRange>(range);
    //         auto arkResult = arkMenuItemClick.InvokeWithObtainResult<
    //             Ark_Boolean, Callback_Boolean_Void>(menuItem, arkRange);
    //         return Converter::Convert<bool>(arkResult);
    //     };
    // RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    RichEditorModelNG::SetRequestKeyboardOnFocus(frameNode, *convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    RichEditorModelStatic::SetEnableHapticFeedback(frameNode, *convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // auto convValue = Converter::OptConvert<DisplayMode>(*value);
    // RichEditorModelNG::SetBarState(frameNode, convValue);
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<int32_t>(*value) : std::nullopt;
    auto validValue = convValue && convValue.value() >= 0 ? convValue : std::nullopt;
    RichEditorModelNG::SetMaxLength(frameNode, validValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<uint32_t>(*value) : std::nullopt;
    RichEditorModelNG::SetMaxLines(frameNode, convValue.value_or(UINT_MAX));
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void BindSelectionMenuImpl(Ark_NativePointer node,
                           const Opt_RichEditorSpanType* spanType,
                           const Opt_CustomNodeBuilder* content,
                           const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                           const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto aceSpanType = Converter::OptConvert<TextSpanType>(*spanType);
    auto aceResponseType = Converter::OptConvert<TextResponseType>(*responseType);
    auto response = aceResponseType.value_or(TextResponseType::NONE);
    auto span = aceSpanType.value_or(TextSpanType::NONE);
    auto convMenuParam = Converter::OptConvert<SelectMenuParam>(*options);
    // TODO: Reset value
    CHECK_NULL_VOID(convMenuParam);
    auto optContent = Converter::GetOptPtr(content);
    if (!optContent) {
        // TODO: Reset value
        return;
    }
    CallbackHelper(*optContent).BuildAsync([frameNode, span, response, convMenuParam = convMenuParam.value()](
        const RefPtr<UINode>& uiNode) mutable {
        std::function<void()> builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        RichEditorModelStatic::BindSelectionMenu(frameNode, span, response, builder, convMenuParam);
        }, node);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ark_KeyboardOptions>(*options);
    std::optional<bool> supportAvoidance;
    if (convValue) {
        supportAvoidance = Converter::OptConvert<bool>(convValue->supportAvoidance);
    }
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto builder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        RichEditorModelStatic::SetCustomKeyboard(frameNode, std::move(builder), supportAvoidance);
        }, node);
}
void PlaceholderImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value,
                     const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(style);
    PlaceholderOptions options;
    if (auto value = Converter::OptConvert<PlaceholderOptions>(*style); value) {
        options = *value;
    }
    options.value = Converter::OptConvert<std::u16string>(*value);
    RichEditorModelNG::SetPlaceholder(frameNode, options);
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
        RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
        RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
        RichEditorAttributeModifier::OnReadyImpl,
        RichEditorAttributeModifier::OnSelectImpl,
        RichEditorAttributeModifier::OnSelectionChangeImpl,
        RichEditorAttributeModifier::AboutToIMEInputImpl,
        RichEditorAttributeModifier::OnIMEInputCompleteImpl,
        RichEditorAttributeModifier::OnDidIMEInputImpl,
        RichEditorAttributeModifier::AboutToDeleteImpl,
        RichEditorAttributeModifier::OnDeleteCompleteImpl,
        RichEditorAttributeModifier::CopyOptionsImpl,
        RichEditorAttributeModifier::OnPasteImpl,
        RichEditorAttributeModifier::EnableDataDetectorImpl,
        RichEditorAttributeModifier::EnablePreviewTextImpl,
        RichEditorAttributeModifier::DataDetectorConfigImpl,
        RichEditorAttributeModifier::CaretColorImpl,
        RichEditorAttributeModifier::SelectedBackgroundColorImpl,
        RichEditorAttributeModifier::OnEditingChangeImpl,
        RichEditorAttributeModifier::EnterKeyTypeImpl,
        RichEditorAttributeModifier::OnSubmitImpl,
        RichEditorAttributeModifier::OnWillChangeImpl,
        RichEditorAttributeModifier::OnDidChangeImpl,
        RichEditorAttributeModifier::OnCutImpl,
        RichEditorAttributeModifier::OnCopyImpl,
        RichEditorAttributeModifier::EditMenuOptionsImpl,
        RichEditorAttributeModifier::EnableKeyboardOnFocusImpl,
        RichEditorAttributeModifier::EnableHapticFeedbackImpl,
        RichEditorAttributeModifier::BarStateImpl,
        RichEditorAttributeModifier::MaxLengthImpl,
        RichEditorAttributeModifier::MaxLinesImpl,
        RichEditorAttributeModifier::KeyboardAppearanceImpl,
        RichEditorAttributeModifier::StopBackPressImpl,
        RichEditorAttributeModifier::BindSelectionMenuImpl,
        RichEditorAttributeModifier::CustomKeyboardImpl,
        RichEditorAttributeModifier::PlaceholderImpl,
    };
    return &ArkUIRichEditorModifierImpl;
}

}
