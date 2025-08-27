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

#include "core/interfaces/native/implementation/text_area_controller_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG::GeneratedModifier {
constexpr float SCALE_LIMIT = 1.f;

namespace TextAreaModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextFieldModelStatic::CreateTextAreaNode(id, u"", u"");
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextAreaModifier
namespace TextAreaInterfaceModifier {
void SetTextAreaOptionsImpl(Ark_NativePointer node,
                            const Opt_TextAreaOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<std::u16string> placeholder;
    std::optional<std::u16string> text;
    TextAreaControllerPeer* peerPtr = nullptr;
    auto textAreaOptions = Converter::OptConvert<Ark_TextAreaOptions>(*value);
    if (textAreaOptions.has_value()) {
        placeholder = Converter::OptConvert<std::u16string>(textAreaOptions.value().placeholder);
        text = Converter::OptConvert<std::u16string>(textAreaOptions.value().text);
        auto controller = Converter::OptConvert<Ark_TextAreaController>(textAreaOptions.value().controller);
        if (controller.has_value()) {
            peerPtr = controller.value();
        }
    }

    auto controller = TextFieldModelStatic::GetController(frameNode, placeholder, text);
    if (peerPtr) {
        peerPtr->SetController(controller);
    }
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, Converter::OptConvert<Font>(*value));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(*value));
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(*value));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetCaretColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextFieldModelStatic::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(*value);
    TextFieldModelStatic::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    TextFieldModelStatic::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextFieldModelStatic::SetFontFamily(frameNode, families);
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Opt_TextOverflow* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextOverflow>(*value);
    TextFieldModelStatic::SetTextOverflow(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    TextFieldModelStatic::SetTextIndent(frameNode, convValue);
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto caretStyle = Converter::OptConvert<Converter::CaretStyle>(*value).value_or(Converter::CaretStyle{});
    TextFieldModelStatic::SetCaretColor(frameNode, caretStyle.color);
    Validator::ValidateNonNegative(caretStyle.width);
    Validator::ValidateNonPercent(caretStyle.width);
    CaretStyle caretStyleNative;
    caretStyleNative.caretWidth = caretStyle.width;
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyleNative);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Opt_Callback_EnterKeyType_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSubmit = [arkCallback = CallbackHelper(*optValue)](int32_t enterKey, NG::TextFieldCommonEvent& event) {
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(enterKey));
        arkCallback.Invoke(enterKeyType);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnSubmit1Impl(Ark_NativePointer node,
                   const Opt_TextAreaSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onSubmit = [arkCallback = CallbackHelper(*optValue), node = weakNode](
		    const int32_t& keyType, NG::TextFieldCommonEvent& info) {
        PipelineContext::SetCallBackNode(node);
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(keyType));
        const auto event = Converter::ArkSubmitEventSync(info);
        auto eventArkValue = Converter::ArkValue<Opt_SubmitEvent, Ark_SubmitEvent>(event.ArkValue());
        arkCallback.InvokeSync(enterKeyType, eventArkValue);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const ChangeValueInfo& info) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(info.value, &ctx);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(info.previewText, &ctx);
        auto options = Converter::ArkValue<Opt_TextChangeOptions>();
        options.tag = INTEROP_TAG_OBJECT;
        options.value.rangeBefore = Converter::ArkValue<Ark_TextRange>(info.rangeBefore);
        options.value.rangeAfter = Converter::ArkValue<Ark_TextRange>(info.rangeAfter);
        options.value.oldContent = Converter::ArkValue<Ark_String>(info.oldContent, &ctx);
        options.value.oldPreviewText = Converter::ArkValue<Ark_PreviewText>(info.oldPreviewText, &ctx);
        arkCallback.InvokeSync(textArkString, textArkPrevText, options);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
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
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*optValue)](int32_t selectionStart, int32_t selectionEnd) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        arkCallback.Invoke(arkSelectionStart, arkSelectionEnd);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onContentScroll = [arkCallback = CallbackHelper(*optValue)](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Number>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Number>(totalOffsetY);
        arkCallback.Invoke(arkTotalOffsetX, arkTotalOffsetY);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onEditEvent = [arkCallback = CallbackHelper(*optValue)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
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
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onCut = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_Callback_String_PasteEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onPaste = [arkCallback = CallbackHelper(*optValue)](const std::u16string& content,
        NG::TextCommonEvent& event) -> void {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkValue<Ark_String>(content, &ctx);
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_PasteEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_Callback_Void>(keeper.ArkValue())
        };
        arkCallback.Invoke(arkContent, arkEvent);
    };
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}

void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(*value));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, convValue);
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLength = Converter::OptConvert<int>(*value);
    Validator::ValidateNonNegative(maxLength);
    if (maxLength) {
        TextFieldModelNG::SetMaxLength(frameNode, *maxLength);
    } else {
        TextFieldModelNG::ResetMaxLength(frameNode);
    }
}
void StyleImpl(Ark_NativePointer node,
               const Opt_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<InputStyle>(*value);
    TextFieldModelStatic::SetInputStyle(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(*value);
    TextFieldModelStatic::SetBarState(frameNode, convValue);
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> optValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        optValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelStatic::SetAdaptMinFontSize(frameNode, optValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> optValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        optValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelStatic::SetAdaptMaxFontSize(frameNode, optValue);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidatePositive(convValue);
    Validator::ValidateLessOrEqual(convValue, SCALE_LIMIT);
    TextFieldModelStatic::SetMinFontScale(frameNode, convValue);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidatePositive(convValue);
    Validator::ValidateGreatOrEqual(convValue, SCALE_LIMIT);
    TextFieldModelStatic::SetMaxFontScale(frameNode, convValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(*value);
    TextFieldModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLines = Converter::OptConvert<uint32_t>(*value);
    TextFieldModelStatic::SetNormalMaxViewLines(frameNode, maxLines);
    TextFieldModelStatic::SetMaxViewLines(frameNode, maxLines);
}
void WordBreakImpl(Ark_NativePointer node,
                   const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(*value);
    TextFieldModelStatic::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(*value);
    TextFieldModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvert<Converter::TextDecorationOptions>(*value)
        .value_or(Converter::TextDecorationOptions{});
    TextFieldModelStatic::SetTextDecoration(frameNode, options.textDecoration);
    TextFieldModelStatic::SetTextDecorationColor(frameNode, options.color);
    TextFieldModelStatic::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> spacing = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        spacing = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(spacing);
    Validator::ValidateNonPercent(spacing);
    TextFieldModelStatic::SetLetterSpacing(frameNode, spacing);
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lineSpacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(lineSpacing);
    TextFieldModelStatic::SetLineSpacing(frameNode, lineSpacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> optValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        optValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(optValue);
    TextFieldModelStatic::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              const Opt_TextAreaType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetType(frameNode, Converter::OptConvert<TextInputType>(*value));
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelStatic::SetEnableAutoFill(frameNode, convValue);
}
void ContentTypeImpl(Ark_NativePointer node,
                     const Opt_ContentType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetContentType(frameNode, Converter::OptConvert<TextContentType>(*value));
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
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
}
void OnWillInsertImpl(Ark_NativePointer node,
                      const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillInsert = [callback = CallbackHelper(*optValue)](const InsertValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue, &ctx)
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(insertValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}
void OnDidInsertImpl(Ark_NativePointer node,
                     const Opt_Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDidInsert = [arkCallback = CallbackHelper(*optValue)](const InsertValueInfo& value) {
        Converter::ConvContext ctx;
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue, &ctx)
        };
        arkCallback.Invoke(insertValue);
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}
void OnWillDeleteImpl(Ark_NativePointer node,
                      const Opt_Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onWillDelete = [callback = CallbackHelper(*optValue)](const DeleteValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue, &ctx)
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(deleteValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}
void OnDidDeleteImpl(Ark_NativePointer node,
                     const Opt_Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onDidDelete = [arkCallback = CallbackHelper(*optValue)](const DeleteValueInfo& value) {
        Converter::ConvContext ctx;
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue, &ctx)
        };
        arkCallback.Invoke(deleteValue);
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
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
    TextFieldModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback),
        std::move(onMenuItemClick));
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelStatic::SetEnablePreviewText(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                const Opt_AutoCapitalizationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    // TextAreaModelNG::SetAutoCapitalizationMode(frameNode, convValue);
}
void HalfLeadingImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetHalfLeading(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void EllipsisModeImpl(Ark_NativePointer node,
                      const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<EllipsisMode>(*value) : std::nullopt;
    TextFieldModelStatic::SetEllipsisMode(frameNode, convValue);
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetStopBackPress(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void OnWillChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        return;
    }
    auto onWillChange = [callback = CallbackHelper(*optValue)](const ChangeValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_TextChangeOptions textChangeOptions = {
            .rangeBefore = Converter::ArkValue<Ark_TextRange>(value.rangeBefore),
            .rangeAfter = Converter::ArkValue<Ark_TextRange>(value.rangeAfter),
            .oldContent = Converter::ArkValue<Ark_String>(value.oldContent, &ctx),
            .oldPreviewText = Converter::ArkValue<Ark_PreviewText>(value.oldPreviewText, &ctx),
        };
        Ark_EditableTextChangeValue changeValue = {
            .content = Converter::ArkValue<Ark_String>(value.value, &ctx),
            .previewText = {
                .tag = INTEROP_TAG_OBJECT,
                .value = Converter::ArkValue<Ark_PreviewText>(value.previewText),
            },
            .options = {
                .tag = INTEROP_TAG_OBJECT,
                .value = textChangeOptions
            }
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(changeValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillChangeEvent(frameNode, std::move(onWillChange));
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<KeyboardAppearance>(*value) : std::nullopt;
    TextFieldModelStatic::SetKeyboardAppearance(frameNode, convValue);
}
void InputFilterImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value,
                     const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueString = Converter::OptConvert<std::string>(*value);
    std::function<void(const std::u16string&)> onErrorEvent = nullptr;
    if (error) {
        auto arkOnError = Converter::OptConvert<Callback_String_Void>(*error);
        if (arkOnError) {
            onErrorEvent = [arkCallback = CallbackHelper(arkOnError.value())](const std::u16string& val) {
                Converter::ConvContext ctx;
                arkCallback.Invoke(Converter::ArkValue<Ark_String>(val, &ctx));
            };
        }
    }
    TextFieldModelNG::SetInputFilter(frameNode, valueString.value_or(""), std::move(onErrorEvent));
}
void ShowCounterImpl(Ark_NativePointer node,
                     const Opt_Boolean* value,
                     const Opt_InputCounterOptions* options)
{
   auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto showCounter = Converter::OptConvert<bool>(*value);
    if (!showCounter) {
        // TODO: Reset value
        return;
    }
    auto optionsOpt = Converter::OptConvert<Ark_InputCounterOptions>(*options);
    const int32_t MAX_VALID_VALUE = 100;
    const int32_t MIN_VALID_VALUE = 1;
    std::optional<bool> highlightBorderOpt;
    std::optional<int> thresholdPercentageOpt;
    if (optionsOpt.has_value()) {
        highlightBorderOpt = Converter::OptConvert<bool>(optionsOpt.value().highlightBorder);
        thresholdPercentageOpt = Converter::OptConvert<int32_t>(optionsOpt.value().thresholdPercentage);
        if (thresholdPercentageOpt.has_value() &&
            (thresholdPercentageOpt.value() < MIN_VALID_VALUE || thresholdPercentageOpt.value() > MAX_VALID_VALUE)) {
            showCounter = false;
            thresholdPercentageOpt = std::nullopt;
        }
    }
    TextFieldModelStatic::SetShowCounterBorder(frameNode, highlightBorderOpt);
    TextFieldModelStatic::SetCounterType(frameNode, thresholdPercentageOpt);
    TextFieldModelNG::SetShowCounter(frameNode, *showCounter);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto keyboardOptions = options ? Converter::OptConvert<Ark_KeyboardOptions>(*options) : std::nullopt;
    bool supportAvoidance = keyboardOptions &&
        Converter::OptConvert<bool>(keyboardOptions.value().supportAvoidance).value_or(false);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto customKeyboard = AceType::DynamicCast<FrameNode>(uiNode);
        TextFieldModelNG::SetCustomKeyboard(
            frameNode, AceType::RawPtr(customKeyboard), supportAvoidance);
        }, node);
}
void _onChangeEvent_textImpl(Ark_NativePointer node,
                             const Callback_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(content, &ctx);
        arkCallback.Invoke(arkContent);
    };
    TextFieldModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // TextAreaAttributeModifier

const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
        TextAreaModifier::ConstructImpl,
        TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
        TextAreaAttributeModifier::PlaceholderColorImpl,
        TextAreaAttributeModifier::PlaceholderFontImpl,
        TextAreaAttributeModifier::EnterKeyTypeImpl,
        TextAreaAttributeModifier::TextAlignImpl,
        TextAreaAttributeModifier::CaretColorImpl,
        TextAreaAttributeModifier::FontColorImpl,
        TextAreaAttributeModifier::FontSizeImpl,
        TextAreaAttributeModifier::FontStyleImpl,
        TextAreaAttributeModifier::FontWeightImpl,
        TextAreaAttributeModifier::FontFamilyImpl,
        TextAreaAttributeModifier::TextOverflowImpl,
        TextAreaAttributeModifier::TextIndentImpl,
        TextAreaAttributeModifier::CaretStyleImpl,
        TextAreaAttributeModifier::SelectedBackgroundColorImpl,
        TextAreaAttributeModifier::OnSubmit0Impl,
        TextAreaAttributeModifier::OnSubmit1Impl,
        TextAreaAttributeModifier::OnChangeImpl,
        TextAreaAttributeModifier::OnTextSelectionChangeImpl,
        TextAreaAttributeModifier::OnContentScrollImpl,
        TextAreaAttributeModifier::OnEditChangeImpl,
        TextAreaAttributeModifier::OnCopyImpl,
        TextAreaAttributeModifier::OnCutImpl,
        TextAreaAttributeModifier::OnPasteImpl,
        TextAreaAttributeModifier::CopyOptionImpl,
        TextAreaAttributeModifier::EnableKeyboardOnFocusImpl,
        TextAreaAttributeModifier::MaxLengthImpl,
        TextAreaAttributeModifier::StyleImpl,
        TextAreaAttributeModifier::BarStateImpl,
        TextAreaAttributeModifier::SelectionMenuHiddenImpl,
        TextAreaAttributeModifier::MinFontSizeImpl,
        TextAreaAttributeModifier::MaxFontSizeImpl,
        TextAreaAttributeModifier::MinFontScaleImpl,
        TextAreaAttributeModifier::MaxFontScaleImpl,
        TextAreaAttributeModifier::HeightAdaptivePolicyImpl,
        TextAreaAttributeModifier::MaxLinesImpl,
        TextAreaAttributeModifier::WordBreakImpl,
        TextAreaAttributeModifier::LineBreakStrategyImpl,
        TextAreaAttributeModifier::DecorationImpl,
        TextAreaAttributeModifier::LetterSpacingImpl,
        TextAreaAttributeModifier::LineSpacingImpl,
        TextAreaAttributeModifier::LineHeightImpl,
        TextAreaAttributeModifier::TypeImpl,
        TextAreaAttributeModifier::EnableAutoFillImpl,
        TextAreaAttributeModifier::ContentTypeImpl,
        TextAreaAttributeModifier::FontFeatureImpl,
        TextAreaAttributeModifier::OnWillInsertImpl,
        TextAreaAttributeModifier::OnDidInsertImpl,
        TextAreaAttributeModifier::OnWillDeleteImpl,
        TextAreaAttributeModifier::OnDidDeleteImpl,
        TextAreaAttributeModifier::EditMenuOptionsImpl,
        TextAreaAttributeModifier::EnablePreviewTextImpl,
        TextAreaAttributeModifier::EnableHapticFeedbackImpl,
        TextAreaAttributeModifier::AutoCapitalizationModeImpl,
        TextAreaAttributeModifier::HalfLeadingImpl,
        TextAreaAttributeModifier::EllipsisModeImpl,
        TextAreaAttributeModifier::StopBackPressImpl,
        TextAreaAttributeModifier::OnWillChangeImpl,
        TextAreaAttributeModifier::KeyboardAppearanceImpl,
        TextAreaAttributeModifier::InputFilterImpl,
        TextAreaAttributeModifier::ShowCounterImpl,
        TextAreaAttributeModifier::CustomKeyboardImpl,
        TextAreaAttributeModifier::_onChangeEvent_textImpl,
    };
    return &ArkUITextAreaModifierImpl;
}

}
