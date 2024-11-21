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

#include "core/interfaces/arkoala/implementation/text_area_controller_peer.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG::GeneratedModifier {
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
            peerPtr = reinterpret_cast<TextAreaControllerPeer*>(controller.value().ptr);
        }
    }

    auto controller = TextFieldModelNG::GetController(frameNode, placeholder, text);
    if (peerPtr) {
        peerPtr->SetController(controller);
    }
}
} // TextAreaInterfaceModifier
namespace TextAreaAttributeModifier {
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetPlaceholderColor(frameNode, Converter::OptConvert<Color>(*value));
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Ark_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetPlaceholderFont(frameNode, Converter::OptConvert<Font>(*value));
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(value));
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(value));
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetCaretColor(frameNode, Converter::OptConvert<Color>(*value));
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetTextColor(frameNode, Converter::OptConvert<Color>(*value));
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
    TextFieldModelNG::SetFontSize(frameNode, fontSize);
}
void FontStyleImpl(Ark_NativePointer node,
                   Ark_FontStyle value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Ace::FontStyle>(value);
    TextFieldModelNG::SetFontStyle(frameNode, convValue);
}
void FontWeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<FontWeight>(*value);
    TextFieldModelNG::SetFontWeight(frameNode, convValue);
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
    TextFieldModelNG::SetFontFamily(frameNode, families);
}
void TextOverflowImpl(Ark_NativePointer node,
                      Ark_TextOverflow value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextOverflow>(value); // for enums
    TextFieldModelNG::SetTextOverflow(frameNode, convValue);
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetTextIndent(frameNode, Converter::OptConvert<Dimension>(*value));
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto caretStyle = Converter::Convert<Converter::CaretStyle>(*value);
    TextFieldModelNG::SetCaretColor(frameNode, caretStyle.color);
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
    TextFieldModelNG::SetSelectedBackgroundColor(frameNode, Converter::OptConvert<Color>(*value));
}
void OnSubmitImpl(Ark_NativePointer node,
                  const Callback_EnterKeyType_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSubmit = [frameNode](int32_t enterKey, NG::TextFieldCommonEvent& event) {
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(enterKey));
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onSubmit(frameNode->GetId(), enterKeyType);
    };
    TextFieldModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnChangeImpl(Ark_NativePointer node,
                  const EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [frameNode](const std::string& text, PreviewText& prevText) {
        auto textArkString = Converter::ArkValue<Ark_String>(text);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(prevText);
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()
            ->onChange(frameNode->GetId(), textArkString, textArkPrevText);
    };
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTextSelectionChange = [frameNode](int32_t selectionStart, int32_t selectionEnd) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onTextSelectionChange(
            frameNode->GetId(), arkSelectionStart, arkSelectionEnd);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onContentScroll = [frameNode](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Number>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Number>(totalOffsetY);
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onContentScroll(
            frameNode->GetId(), arkTotalOffsetX, arkTotalOffsetY);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEditEvent = [frameNode](const bool value) {
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onEditChange(frameNode->GetId(), value);
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [frameNode](const std::string& value) {
        auto textArkString = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onCopy(frameNode->GetId(), textArkString);
    };
    TextFieldModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCut = [frameNode](const std::string& value) {
        auto textArkString = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onCut(frameNode->GetId(), textArkString);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const Callback_String_PasteEvent_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
    LOGE("ARKOALA TextAreaAttributeModifier.OnPasteImpl -> Method is not fully implemented.");
}

void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(value));
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
    TextFieldModelNG::SetInputStyle(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(value); // for enums
    TextFieldModelNG::SetBarState(frameNode, convValue);
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
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, optValue);
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
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, optValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(value);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
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
    TextFieldModelNG::SetMaxViewLines(frameNode, maxLines);
}
void WordBreakImpl(Ark_NativePointer node,
                   Ark_WordBreak value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<WordBreak>(value); // for enums
    TextFieldModelNG::SetWordBreak(frameNode, convValue);
}
void LineBreakStrategyImpl(Ark_NativePointer node,
                           Ark_LineBreakStrategy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<LineBreakStrategy>(value); // for enums
    TextFieldModelNG::SetLineBreakStrategy(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::TextDecorationOptions>(*value);
    TextFieldModelNG::SetTextDecoration(frameNode, options.textDecoration);
    TextFieldModelNG::SetTextDecorationColor(frameNode, options.color);
    TextFieldModelNG::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
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
    TextFieldModelNG::SetLetterSpacing(frameNode, spacing);
}
void LineSpacingImpl(Ark_NativePointer node,
                     const Ark_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //TextAreaModelNG::SetLineSpacing(frameNode, convValue);
    LOGE("ARKOALA TextAreaAttributeModifier.LineSpacingImpl -> Method is not implemented.");
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(optValue);
    TextFieldModelNG::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              Ark_TextAreaType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelNG::SetType(frameNode, Converter::OptConvert<TextInputType>(value));
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
    TextFieldModelNG::SetContentType(frameNode, Converter::OptConvert<TextContentType>(value));
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
    auto onWillInsert = [frameNode](const InsertValueInfo& value) -> bool {
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue)
        };
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onWillInsert(frameNode->GetId(), insertValue);
        LOGE("ARKOALA TextAreaAttributeModifier.OnWillInsert -> Method work incorrect.");
        return true;
    };
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}
void OnDidInsertImpl(Ark_NativePointer node,
                     const Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onDidInsert = [frameNode](const InsertValueInfo& value) {
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue)
        };
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onDidInsert(frameNode->GetId(), insertValue);
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}
void OnWillDeleteImpl(Ark_NativePointer node,
                      const Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onWillDelete = [frameNode](const DeleteValueInfo& value) -> bool {
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue)
        };
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onWillDelete(frameNode->GetId(), deleteValue);
        LOGE("ARKOALA TextAreaAttributeModifier.OnWillDeleteImpl -> Method work incorrect.");
        return true;
    };
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}
void OnDidDeleteImpl(Ark_NativePointer node,
                     const Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onDidDelete = [frameNode](const DeleteValueInfo& value) {
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue)
        };
        GetFullAPI()->getEventsAPI()->getTextAreaEventsReceiver()->onDidDelete(frameNode->GetId(), deleteValue);
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
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
    //TextAreaModelNG::SetEnableHapticFeedback(frameNode, convValue);
    LOGE("ARKOALA TextAreaAttributeModifier.EnableHapticFeedbackImpl -> Method is not implemented.");
}
void InputFilterImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value,
                     const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueString = Converter::OptConvert<std::string>(*value);
    auto errorEvent = [frameNode](const std::string& val) {
        auto errorArkString = Converter::ArkValue<Ark_String>(val);
    };
    TextFieldModelNG::SetInputFilter(frameNode, valueString.value_or(""), errorEvent);
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
    TextFieldModelNG::SetShowCounterBorder(frameNode, highlightBorderOpt);
    TextFieldModelNG::SetCounterType(frameNode, thresholdPercentageOpt);
    TextFieldModelNG::SetShowCounter(frameNode, showCounter);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const Callback_Any* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextAreaModelNG::SetCustomKeyboard(frameNode, convValue);
    LOGE("ARKOALA TextAreaAttributeModifier.CustomKeyboardImpl -> Method is not implemented.");
}
} // TextAreaAttributeModifier

const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
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
        TextAreaAttributeModifier::OnSubmitImpl,
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
    };
    return &ArkUITextAreaModifierImpl;
}

}
