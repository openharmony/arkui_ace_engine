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
#include "core/interfaces/native/implementation/text_area_controller_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextAreaModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextFieldModelNG::CreateFrameNode(id, u"", u"", true);
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
    std::optional<std::string> placeholder;
    std::optional<std::string> text;
    TextAreaControllerPeer* peerPtr = nullptr;
    auto textAreaOptions = Converter::OptConvert<Ark_TextAreaOptions>(*value);
    if (textAreaOptions.has_value()) {
        placeholder = Converter::OptConvert<std::string>(textAreaOptions.value().placeholder);
        text = Converter::OptConvert<std::string>(textAreaOptions.value().text);
        auto controller = Converter::OptConvert<Ark_TextAreaController>(textAreaOptions.value().controller);
        if (controller.has_value()) {
            peerPtr = controller.value();
        }
    }
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetPlaceholderColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetPlaceholderFont(frameNode, Converter::OptConvert<Font>(*value));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(*value));
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(*value));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetCaretColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetTextColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontSizeImpl(Ark_NativePointer node,
                  const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextFieldModelNG::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(*value);
    TextFieldModelNG::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    TextFieldModelNG::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextFieldModelNG::SetFontFamily(frameNode, families);
}
void TextOverflowImpl(Ark_NativePointer node,
                      const Opt_TextOverflow* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextOverflow>(*value); // for enums
    TextFieldModelNG::SetTextOverflow(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetTextIndent(frameNode, Converter::OptConvert<Dimension>(*value));
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::CaretStyle caretStyle;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        caretStyle = Converter::Convert<Converter::CaretStyle>(value->value);
    }
    TextFieldModelNG::SetCaretColor(frameNode, caretStyle.color);
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
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Opt_Callback_EnterKeyType_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onSubmit = [arkCallback = CallbackHelper(value->value)](int32_t enterKey, NG::TextFieldCommonEvent& event) {
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
    CHECK_NULL_VOID(value);
    auto weakNode = AceType::WeakClaim(frameNode);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onSubmit = [arkCallback = CallbackHelper(value->value), node = weakNode](
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onChange = [arkCallback = CallbackHelper(value->value)](const ChangeValueInfo& changeValueInfo) {
        Converter::ConvContext ctx;
        const std::string u8Text = UtfUtils::Str16DebugToStr8(changeValueInfo.value);
        PreviewText prevText = changeValueInfo.previewText;
        auto textArkString = Converter::ArkValue<Ark_String>(u8Text, &ctx);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(prevText, &ctx);
        auto options = Converter::ArkValue<Opt_TextChangeOptions>();
        arkCallback.Invoke(textArkString, textArkPrevText, options);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onTextSelectionChange = [arkCallback = CallbackHelper(value->value)]
        (int32_t selectionStart, int32_t selectionEnd) {
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onContentScroll = [arkCallback = CallbackHelper(value->value)](float totalOffsetX, float totalOffsetY) {
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onEditEvent = [arkCallback = CallbackHelper(value->value)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
}
void OnCopyImpl(Ark_NativePointer node,
                const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onCopy = [arkCallback = CallbackHelper(value->value)](const std::u16string& value) {
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onCut = [arkCallback = CallbackHelper(value->value)](const std::u16string& value) {
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_Callback_String_PasteEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onPaste = [arkCallback = CallbackHelper(value->value)](const std::u16string& content,
        NG::TextCommonEvent& event) -> void {
        const std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkValue<Ark_String>(u8Content, &ctx);
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
    TextFieldModelNG::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(*value));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, convValue? convValue.value() : true);
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto maxLength = Converter::Convert<int>(value->value);
        if (GreatOrEqual(maxLength, 0)) {
            TextFieldModelNG::SetMaxLength(frameNode, maxLength);
            return;
        }
    }
    TextFieldModelNG::ResetMaxLength(frameNode);
}
void StyleImpl(Ark_NativePointer node,
               const Opt_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<InputStyle>(*value); // for enums
    TextFieldModelNG::SetInputStyle(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(*value); // for enums
    TextFieldModelNG::SetBarState(frameNode, convValue);
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto convValue = Converter::Convert<bool>(value->value);
        TextFieldModelNG::SetSelectionMenuHidden(frameNode, convValue);
    } else {
        TextFieldModelNG::SetSelectionMenuHidden(frameNode, false);
    }
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, optValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, optValue);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(*value);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<uint32_t> maxLines;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto maxLinesInt = Converter::Convert<int>(value->value);
        if (GreatOrEqual(maxLinesInt, 0)) {
            maxLines = static_cast<uint32_t>(maxLinesInt);
        }
    }
    TextFieldModelNG::SetMaxViewLines(frameNode, maxLines);
}
void WordBreakImpl(Ark_NativePointer node,
                   const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(*value); // for enums
    TextFieldModelNG::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(*value); // for enums
    TextFieldModelNG::SetLineBreakStrategy(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Converter::TextDecorationOptions options;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        options = Converter::Convert<Converter::TextDecorationOptions>(value->value);
    }
    TextFieldModelNG::SetTextDecoration(frameNode, options.textDecoration);
    TextFieldModelNG::SetTextDecorationColor(frameNode, options.color);
    TextFieldModelNG::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(spacing);
    Validator::ValidateNonPercent(spacing);
    TextFieldModelNG::SetLetterSpacing(frameNode, spacing);
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineSpacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(lineSpacing);
    TextFieldModelNG::SetLineSpacing(frameNode, lineSpacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    TextFieldModelNG::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              const Opt_TextAreaType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, Converter::OptConvert<TextInputType>(*value));
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto convValue = Converter::Convert<bool>(value->value);
        TextFieldModelNG::SetEnableAutoFill(frameNode, convValue);
    } else {
        TextFieldModelNG::SetEnableAutoFill(frameNode, true);
    }
}
void ContentTypeImpl(Ark_NativePointer node,
                     const Opt_ContentType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetContentType(frameNode, Converter::OptConvert<TextContentType>(*value));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string fontFeatureSettings = "";
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        fontFeatureSettings = Converter::Convert<std::string>(value->value);
    }
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(fontFeatureSettings));
}
void OnWillInsertImpl(Ark_NativePointer node,
                      const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onWillInsert = [callback = CallbackHelper(value->value)](const InsertValueInfo& value) -> bool {
        std::string u8InsertValue = UtfUtils::Str16DebugToStr8(value.insertValue);
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(u8InsertValue)
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onDidInsert = [arkCallback = CallbackHelper(value->value)](const InsertValueInfo& value) {
        Converter::ConvContext ctx;
        std::string u8InsertValue = UtfUtils::Str16DebugToStr8(value.insertValue);
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(u8InsertValue, &ctx)
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onWillDelete = [callback = CallbackHelper(value->value)](const DeleteValueInfo& value) -> bool {
        std::string u8DeleteValue = UtfUtils::Str16DebugToStr8(value.deleteValue);
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(u8DeleteValue)
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
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto onDidDelete = [arkCallback = CallbackHelper(value->value)](const DeleteValueInfo& value) {
        Converter::ConvContext ctx;
        std::string u8DeleteValue = UtfUtils::Str16DebugToStr8(value.deleteValue);
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(u8DeleteValue, &ctx)
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
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetEditMenuOptions(frameNode, convValue);
    LOGE("ARKOALA TextAreaAttributeModifier.EditMenuOptionsImpl -> Method is not implemented.");
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto convValue = Converter::Convert<bool>(value->value);
        TextFieldModelNG::SetEnablePreviewText(frameNode, convValue);
    } else {
        TextFieldModelNG::SetEnablePreviewText(frameNode, true);
    }
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        auto convValue = Converter::Convert<bool>(value->value);
        TextFieldModelNG::SetEnableHapticFeedback(frameNode, convValue);
    } else {
        TextFieldModelNG::SetEnableHapticFeedback(frameNode, true);
    }
}
void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                const Opt_AutoCapitalizationMode* value)
{
}
void HalfLeadingImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
}
void EllipsisModeImpl(Ark_NativePointer node,
                      const Opt_EllipsisMode* value)
{
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
}
void OnWillChangeImpl(Ark_NativePointer node,
                      const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
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
                const std::string u8Val = UtfUtils::Str16DebugToStr8(val);
                arkCallback.Invoke(Converter::ArkValue<Ark_String>(u8Val, &ctx));
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
    CHECK_NULL_VOID(options);
    CHECK_NULL_VOID(value);
    bool showCounter = false;
    if (value->tag != InteropTag::INTEROP_TAG_UNDEFINED) {
        showCounter = Converter::Convert<bool>(value->value);
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
    TextFieldModelNG::SetShowCounterBorder(frameNode, highlightBorderOpt);
    TextFieldModelNG::SetCounterType(frameNode, thresholdPercentageOpt);
    TextFieldModelNG::SetShowCounter(frameNode, showCounter);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Opt_CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    CHECK_NULL_VOID(value->tag != InteropTag::INTEROP_TAG_UNDEFINED);
    auto keyboardOptions = options ? Converter::OptConvert<Ark_KeyboardOptions>(*options) : std::nullopt;
    bool supportAvoidance = keyboardOptions &&
        Converter::OptConvert<bool>(keyboardOptions.value().supportAvoidance).value_or(false);
    auto uiNode = CallbackHelper(value->value).BuildSync(node);
    auto customKeyboard = AceType::DynamicCast<FrameNode>(uiNode);
    TextFieldModelNG::SetCustomKeyboard(
        frameNode, AceType::RawPtr(customKeyboard), supportAvoidance);
}
void _onChangeEvent_textImpl(Ark_NativePointer node,
                             const Callback_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        const std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(u8Content);
        arkCallback.Invoke(arkContent);
    };
    TextFieldModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
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
