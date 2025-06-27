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
#include "core/interfaces/native/utility/callback_helper.h"
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
namespace TextAreaModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextFieldModelNG::CreateTextAreaNode(id, u"", u"");
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextAreaModifier
namespace TextAreaInterfaceModifier {
void SetTextAreaOptionsImpl(Ark_NativePointer node,
                            const Opt_TextAreaOptions* value)
{
    // auto frameNode = reinterpret_cast<FrameNode *>(node);
    // CHECK_NULL_VOID(frameNode);
    // CHECK_NULL_VOID(value);
    // std::optional<std::string> placeholder;
    // std::optional<std::string> text;
    // TextAreaControllerPeer* peerPtr = nullptr;
    // auto textAreaOptions = Converter::OptConvert<Ark_TextAreaOptions>(*value);
    // if (textAreaOptions.has_value()) {
    //     placeholder = Converter::OptConvert<std::string>(textAreaOptions.value().placeholder);
    //     text = Converter::OptConvert<std::string>(textAreaOptions.value().text);
    //     auto controller = Converter::OptConvert<Ark_TextAreaController>(textAreaOptions.value().controller);
    //     if (controller.has_value()) {
    //         peerPtr = controller.value();
    //     }
    // }

    // auto controller = TextFieldModelStatic::GetController(frameNode, placeholder, text);
    // if (peerPtr) {
    //     peerPtr->SetController(controller);
    // }
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, Converter::OptConvert<Font>(*value));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(value));
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(value));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetCaretColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetTextColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontSizeImpl(Ark_NativePointer node,
                  const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontSize = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextFieldModelStatic::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(value);
    TextFieldModelStatic::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    TextFieldModelStatic::SetFontWeight(frameNode, convValue);
}
void FontFamilyImpl(Ark_NativePointer node,
                    const Ark_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvert<Converter::FontFamilies>(*value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextFieldModelStatic::SetFontFamily(frameNode, families);
}
void TextOverflowImpl(Ark_NativePointer node,
                      Ark_TextOverflow value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextOverflow>(value); // for enums
    TextFieldModelStatic::SetTextOverflow(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetTextIndent(frameNode, Converter::OptConvert<Dimension>(*value));
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto caretStyle = Converter::Convert<Converter::CaretStyle>(*value);
    TextFieldModelStatic::SetCaretColor(frameNode, caretStyle.color);
    Validator::ValidateNonNegative(caretStyle.width);
    Validator::ValidateNonPercent(caretStyle.width);
    CaretStyle caretStyleNative;
    caretStyleNative.caretWidth = caretStyle.width;
    TextFieldModelNG::SetCaretStyle(frameNode, caretStyleNative);
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelStatic::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Callback_EnterKeyType_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSubmit = [arkCallback = CallbackHelper(*value)](int32_t enterKey, NG::TextFieldCommonEvent& event) {
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(enterKey));
        arkCallback.Invoke(enterKeyType);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnSubmit1Impl(Ark_NativePointer node,
                   const TextAreaSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onSubmit = [arkCallback = CallbackHelper(*value), node = weakNode](
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
                  const EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const ChangeValueInfo& changeValueInfo) {
        const std::string u8Text = UtfUtils::Str16DebugToStr8(changeValueInfo.value);
        PreviewText prevText = changeValueInfo.previewText;
        auto textArkString = Converter::ArkValue<Ark_String>(u8Text);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(prevText);
        arkCallback.Invoke(textArkString, textArkPrevText);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*value)](int32_t selectionStart, int32_t selectionEnd) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        arkCallback.Invoke(arkSelectionStart, arkSelectionEnd);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onContentScroll = [arkCallback = CallbackHelper(*value)](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Number>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Number>(totalOffsetY);
        arkCallback.Invoke(arkTotalOffsetX, arkTotalOffsetY);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEditEvent = [arkCallback = CallbackHelper(*value)](const bool value) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(value));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [arkCallback = CallbackHelper(*value)](const std::u16string& value) {
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCut = [arkCallback = CallbackHelper(*value)](const std::u16string& value) {
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value);
        arkCallback.Invoke(textArkString);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const Callback_String_PasteEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPaste = [arkCallback = CallbackHelper(*value)](const std::u16string& content,
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
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(value));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, Converter::Convert<bool>(value));
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxLength = Converter::Convert<int>(*value);
    if (GreatOrEqual(maxLength, 0)) {
        TextFieldModelNG::SetMaxLength(frameNode, maxLength);
    } else {
        TextFieldModelNG::ResetMaxLength(frameNode);
    }
}
void StyleImpl(Ark_NativePointer node,
               Ark_TextContentStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<InputStyle>(value); // for enums
    TextFieldModelStatic::SetInputStyle(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(value); // for enums
    TextFieldModelStatic::SetBarState(frameNode, convValue);
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, Converter::Convert<bool>(value));
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelStatic::SetAdaptMinFontSize(frameNode, optValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    Validator::ValidateNonPercent(optValue);
    TextFieldModelStatic::SetAdaptMaxFontSize(frameNode, optValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(value);
    TextFieldModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxLinesInt = Converter::Convert<int>(*value);
    std::optional<uint32_t> maxLines;
    if (GreatOrEqual(maxLinesInt, 0)) {
        maxLines = static_cast<uint32_t>(maxLinesInt);
    }
    TextFieldModelStatic::SetMaxViewLines(frameNode, maxLines);
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_WordBreak value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(value); // for enums
    TextFieldModelStatic::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_LineBreakStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(value); // for enums
    TextFieldModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::TextDecorationOptions>(*value);
    TextFieldModelStatic::SetTextDecoration(frameNode, options.textDecoration);
    TextFieldModelStatic::SetTextDecorationColor(frameNode, options.color);
    TextFieldModelStatic::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(spacing);
    Validator::ValidateNonPercent(spacing);
    TextFieldModelStatic::SetLetterSpacing(frameNode, spacing);
}
void LineSpacingImpl(Ark_NativePointer node,
                     Ark_LengthMetrics value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto lineSpacing = Converter::OptConvert<Dimension>(value);
    Validator::ValidateNonNegative(lineSpacing);
    TextFieldModelStatic::SetLineSpacing(frameNode, lineSpacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    TextFieldModelStatic::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              Ark_TextAreaType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetType(frameNode, Converter::OptConvert<TextInputType>(value));
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnableAutoFill(frameNode, Converter::Convert<bool>(value));
}
void ContentTypeImpl(Ark_NativePointer node,
                     Ark_ContentType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetContentType(frameNode, Converter::OptConvert<TextContentType>(value));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::string fontFeatureSettings = Converter::Convert<std::string>(*value);
    TextFieldModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(fontFeatureSettings));
}
void OnWillInsertImpl(Ark_NativePointer node,
                      const Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillInsert = [callback = CallbackHelper(*value)](const InsertValueInfo& value) -> bool {
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
                     const Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onDidInsert = [arkCallback = CallbackHelper(*value)](const InsertValueInfo& value) {
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
                      const Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillDelete = [callback = CallbackHelper(*value)](const DeleteValueInfo& value) -> bool {
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
                     const Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onDidDelete = [arkCallback = CallbackHelper(*value)](const DeleteValueInfo& value) {
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
                         Ark_EditMenuOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetEditMenuOptions(frameNode, convValue);
    LOGE("ARKOALA TextAreaAttributeModifier.EditMenuOptionsImpl -> Method is not implemented.");
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnablePreviewText(frameNode, Converter::Convert<bool>(value));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetEnableHapticFeedback(frameNode, convValue);
}
void InputFilterImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value,
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
                     Ark_Boolean value,
                     const Opt_InputCounterOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto showCounter = Converter::Convert<bool>(value);
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
    TextFieldModelNG::SetShowCounter(frameNode, showCounter);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto keyboardOptions = options ? Converter::OptConvert<Ark_KeyboardOptions>(*options) : std::nullopt;
    bool supportAvoidance = keyboardOptions &&
        Converter::OptConvert<bool>(keyboardOptions.value().supportAvoidance).value_or(false);
    auto uiNode = CallbackHelper(*value).BuildSync(node);
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
        TextAreaAttributeModifier::InputFilterImpl,
        TextAreaAttributeModifier::ShowCounterImpl,
        TextAreaAttributeModifier::CustomKeyboardImpl,
        TextAreaAttributeModifier::_onChangeEvent_textImpl,
    };
    return &ArkUITextAreaModifierImpl;
}

}
