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
    auto imageSpanResult = Converter::ArkValue<Ark_RichEditorImageSpanResult>(src, ctx);
    dst = Converter::ArkUnion<Union_Span_Result, Ark_RichEditorImageSpanResult>(imageSpanResult);
}

void SetTextSpanResult(Union_Span_Result& dst, const ResultObject& src, Converter::ConvContext *ctx)
{
    auto textSpanResult = Converter::ArkValue<Ark_RichEditorTextSpanResult>(src, ctx);
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
        dst.spans.length = resultObjects.size();
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
        } else {
            dst.start = Converter::ArkValue<Opt_Number>(Ark_Empty());
            dst.end = Converter::ArkValue<Opt_Number>(Ark_Empty());
        }
    } else if (src.GetType() == "SelectionRangeInfo") {
        auto selectionRangeInfo = static_cast<const SelectionRangeInfo*>(&src);
        if (selectionRangeInfo) {
            dst.start = Converter::ArkValue<Opt_Number>(selectionRangeInfo->start_);
            dst.end = Converter::ArkValue<Opt_Number>(selectionRangeInfo->end_);
        } else {
            dst.start = Converter::ArkValue<Opt_Number>(Ark_Empty());
            dst.end = Converter::ArkValue<Opt_Number>(Ark_Empty());
        }
    } else {
        dst.start = Converter::ArkValue<Opt_Number>(Ark_Empty());
        dst.end = Converter::ArkValue<Opt_Number>(Ark_Empty());
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

void AssignArkValue(Ark_DecorationStyleResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.GetTextDecoration());
    dst.color = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetColor(), ctx);
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.GetTextDecorationStyle());
}

void AssignArkValue(Ark_RichEditorTextStyleResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.fontColor = Converter::ArkUnion<Ark_ResourceColor, Ark_String>(src.GetFontColor(), ctx);
    dst.fontSize = Converter::ArkValue<Ark_Number>(src.GetFontSize());
    dst.fontStyle = Converter::ArkValue<Ark_FontStyle>(src.GetFontStyle());
    dst.fontWeight = Converter::ArkValue<Ark_Number>(src.GetFontWeight());
    dst.fontFamily = Converter::ArkValue<Ark_String>(src.GetFontFamily(), ctx);
    dst.decoration = Converter::ArkValue<Ark_DecorationStyleResult>(src);
    dst.letterSpacing = Converter::ArkValue<Opt_Number>(src.GetLetterspacing());
    dst.lineHeight = Converter::ArkValue<Opt_Number>(src.GetLineHeight());

    if (src.GetFontFeatures().size() > 0) {
        dst.fontFeature = Converter::ArkValue<Opt_String>(src.GetFontFeatures(), ctx);
    } else {
        dst.fontFeature = Converter::ArkValue<Opt_String>(Ark_Empty(), ctx);
    }

    if (src.GetTextStyle().textShadows.size() > 0) {
        dst.textShadow = Converter::ArkValue<Opt_Array_ShadowOptions>(src.GetTextStyle().textShadows, ctx);
    } else {
        dst.textShadow = Converter::ArkValue<Opt_Array_ShadowOptions>(Ark_Empty(), ctx);
    }

    dst.halfLeading = Converter::ArkValue<Opt_Boolean>(src.GetHalfLeading());
    dst.textBackgroundStyle = Converter::ArkValue<Opt_TextBackgroundStyle>(src.GetTextStyle().textBackgroundStyle, ctx);
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
    LOGW("RichEditor modifier :: urlStyle conversion is not implemented yet.");
    dst.urlStyle = ArkValue<Opt_RichEditorUrlStyle>(
        ArkValue<Ark_RichEditorUrlStyle>(src.GetUrlAddress(), ctx), ctx); // urlAddress?

    LeadingMargin leadingMargin {
        .size = LeadingMarginSize(
            StringUtils::StringToDimension(src.GetTextStyle().leadingMarginSize[0]),
            StringUtils::StringToDimension(src.GetTextStyle().leadingMarginSize[1])),
        .pixmap = nullptr, // not implemented yet, GetValuePixelMap()?
    };

    Ark_RichEditorParagraphStyle paragraphStyle {
        .textAlign = Converter::ArkValue<Opt_TextAlign>(static_cast<TextAlign>(src.GetTextStyle().textAlign)),
        .leadingMargin =
            Converter::ArkUnion<Opt_Union_Dimension_LeadingMarginPlaceholder, Ark_LeadingMarginPlaceholder>(
                leadingMargin),
        .wordBreak = Converter::ArkValue<Opt_WordBreak>(static_cast<WordBreak>(src.GetTextStyle().wordBreak)),
        .lineBreakStrategy =Converter::ArkValue<Opt_LineBreakStrategy>(
            static_cast<LineBreakStrategy>(src.GetTextStyle().lineBreakStrategy)),
        .paragraphSpacing = Converter::ArkValue<Opt_Number>(src.GetTextStyle().paragraphSpacing)
    };
    dst.paragraphStyle = Converter::ArkValue<Opt_RichEditorParagraphStyle>(paragraphStyle);
}

void AssignArkValue(Ark_RichEditorImageSpanResult& dst, const RichEditorAbstractSpanResult& src, ConvContext *ctx)
{
    dst.spanPosition = Converter::ArkValue<Ark_RichEditorSpanPosition>(src);

    if (src.GetValuePixelMap()) {
        Ark_PixelMap arkPixelMap = new PixelMapPeer();
        arkPixelMap->pixelMap = src.GetValuePixelMap();
        dst.valuePixelMap = Converter::ArkValue<Opt_PixelMap>(arkPixelMap);
    } else {
        dst.valuePixelMap = Converter::ArkValue<Opt_PixelMap>(Ark_Empty());
    }

    if (!src.GetValueResourceStr().empty()) {
        dst.valueResourceStr = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(src.GetValueResourceStr(), ctx);
    } else {
        dst.valueResourceStr = Converter::ArkValue<Opt_ResourceStr>(Ark_Empty(), ctx);
    }

    Opt_Union_Dimension_Margin margin {};
    if (src.GetMargin().length()) {
        margin = ArkUnion<Opt_Union_Dimension_Margin, Ark_Length>(src.GetMargin());
    } else {
        margin = ArkUnion<Opt_Union_Dimension_Margin>(Ark_Empty());
    }

    Opt_Union_Dimension_BorderRadiuses borderRadius {};
    if (src.GetBorderRadius().length()) {
        borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses, Ark_Length>(src.GetBorderRadius());
    } else {
        borderRadius = ArkUnion<Opt_Union_Dimension_BorderRadiuses>(Ark_Empty());
    }

    Ark_RichEditorLayoutStyle layoutStyle {
        .margin = margin,
        .borderRadius = borderRadius
    };
    dst.imageStyle.layoutStyle = Converter::ArkValue<Opt_RichEditorLayoutStyle>(layoutStyle);
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

void AssignArkValue(Ark_RichEditorUrlStyle& dst, const std::u16string& src, ConvContext *ctx)
{
    if (src.length()) {
        auto str = Converter::ArkValue<Ark_String>(src, ctx);
        auto resStr = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(str, ctx);
        dst.url = Converter::ArkValue<Opt_ResourceStr>(resStr, ctx);
    } else {
        dst.url = Converter::ArkValue<Opt_ResourceStr>(Ark_Empty(), ctx);
    }
}
} // OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // RichEditorModifier
namespace RichEditorInterfaceModifier {
void SetRichEditorOptions0Impl(Ark_NativePointer node,
                               const Ark_RichEditorOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RichEditorModelNG::SetSetRichEditorOptions0(frameNode, convValue);
}
void SetRichEditorOptions1Impl(Ark_NativePointer node,
                               const Ark_RichEditorStyledStringOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    //auto convValue = Converter::OptConvert<type_name>(*options);
    //RichEditorModelNG::SetSetRichEditorOptions1(frameNode, convValue);
}
} // RichEditorInterfaceModifier
namespace RichEditorAttributeModifier {
void SetOnReadyImpl(Ark_NativePointer node,
                    const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnReady(frameNode, convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_RichEditorSelection_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSelect(frameNode, convValue);
}
void SetOnSelectionChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_RichEditorRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSelectionChange(frameNode, convValue);
}
void SetAboutToIMEInputImpl(Ark_NativePointer node,
                            const Opt_Callback_RichEditorInsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetAboutToIMEInput(frameNode, convValue);
}
void SetOnIMEInputCompleteImpl(Ark_NativePointer node,
                               const Opt_Callback_RichEditorTextSpanResult_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnIMEInputComplete(frameNode, convValue);
}
void SetOnDidIMEInputImpl(Ark_NativePointer node,
                          const Opt_Callback_TextRange_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDidIMEInput(frameNode, convValue);
}
void SetAboutToDeleteImpl(Ark_NativePointer node,
                          const Opt_Callback_RichEditorDeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetAboutToDelete(frameNode, convValue);
}
void SetOnDeleteCompleteImpl(Ark_NativePointer node,
                             const Opt_VoidCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDeleteComplete(frameNode, convValue);
}
void SetCopyOptionsImpl(Ark_NativePointer node,
                        const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetCopyOptions(frameNode, convValue);
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_PasteEventCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnPaste(frameNode, convValue);
}
void SetEnableDataDetectorImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableDataDetector(frameNode, convValue);
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnablePreviewText(frameNode, convValue);
}
void SetDataDetectorConfigImpl(Ark_NativePointer node,
                               const Opt_TextDataDetectorConfig* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetDataDetectorConfig(frameNode, convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetCaretColor(frameNode, convValue);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetSelectedBackgroundColor(frameNode, convValue);
}
void SetOnEditingChangeImpl(Ark_NativePointer node,
                            const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnEditingChange(frameNode, convValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnterKeyType(frameNode, convValue);
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_SubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnSubmit(frameNode, convValue);
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_RichEditorChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnWillChange(frameNode, convValue);
}
void SetOnDidChangeImpl(Ark_NativePointer node,
                        const Opt_OnDidChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnDidChange(frameNode, convValue);
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_CutEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnCut(frameNode, convValue);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_CopyEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetOnCopy(frameNode, convValue);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
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
    RichEditorModelNG::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableKeyboardOnFocus(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetEnableHapticFeedback(frameNode, convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetBarState(frameNode, convValue);
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetMaxLength(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetMaxLines(frameNode, convValue);
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetKeyboardAppearance(frameNode, convValue);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //RichEditorModelNG::SetSetStopBackPress(frameNode, convValue);
}
void SetBindSelectionMenuImpl(Ark_NativePointer node,
                              const Opt_RichEditorSpanType* spanType,
                              const Opt_CustomNodeBuilder* content,
                              const Opt_Union_ResponseType_RichEditorResponseType* responseType,
                              const Opt_SelectionMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(spanType);
    //auto convValue = Converter::OptConvert<type>(spanType); // for enums
    //RichEditorModelNG::SetSetBindSelectionMenu(frameNode, convValue);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetSetCustomKeyboard(frameNode, convValue);
}
void SetPlaceholderImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_PlaceholderStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //RichEditorModelNG::SetSetPlaceholder(frameNode, convValue);
}
} // RichEditorAttributeModifier
const GENERATED_ArkUIRichEditorModifier* GetRichEditorModifier()
{
    static const GENERATED_ArkUIRichEditorModifier ArkUIRichEditorModifierImpl {
        RichEditorModifier::ConstructImpl,
        RichEditorInterfaceModifier::SetRichEditorOptions0Impl,
        RichEditorInterfaceModifier::SetRichEditorOptions1Impl,
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
