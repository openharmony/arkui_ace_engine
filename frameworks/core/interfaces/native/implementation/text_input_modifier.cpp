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
#include "core/interfaces/native/implementation/text_input_controller_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MIN_THRESHOLD_PERCENTAGE = 1;
constexpr int32_t MAX_THRESHOLD_PERCENTAGE = 100;

struct InputCounterOptions {
    std::optional<int> thresholdPercentage;
    std::optional<bool> highlightBorder;
};
} // namespace

namespace Converter {
template<>
InputCounterOptions Convert(const Ark_InputCounterOptions& src)
{
    InputCounterOptions options;
    options.thresholdPercentage = Converter::OptConvert<int>(src.thresholdPercentage);
    options.highlightBorder = Converter::OptConvert<bool>(src.highlightBorder);
    return options;
}

template<>
PasswordIcon Convert(const Ark_PasswordIcon& src)
{
    PasswordIcon result {};
    Converter::VisitUnion(
        src.onIconSrc, [&result](const Ark_String& src) { result.showResult = Converter::Convert<std::string>(src); },
        [&result](const Ark_Resource& src) {
            result.showBundleName = Converter::Convert<std::string>(src.bundleName);
            result.showModuleName = Converter::Convert<std::string>(src.moduleName);
            auto resStr = Converter::OptConvert<std::string>(src);
            result.showResult = (resStr.has_value()) ? resStr.value() : "";
        },
        []() {});
    Converter::VisitUnion(
        src.offIconSrc, [&result](const Ark_String& src) { result.hideResult = Converter::Convert<std::string>(src); },
        [&result](const Ark_Resource& src) {
            result.hideBundleName = Converter::Convert<std::string>(src.bundleName);
            result.hideModuleName = Converter::Convert<std::string>(src.moduleName);
            auto resStr = Converter::OptConvert<std::string>(src);
            result.hideResult = (resStr.has_value()) ? resStr.value() : "";
        },
        []() {});
    return result;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextInputModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = TextFieldModelNG::CreateFrameNode(id, u"", u"", false);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // TextInputModifier
namespace TextInputInterfaceModifier {
void SetTextInputOptionsImpl(Ark_NativePointer node,
                             const Opt_TextInputOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<std::string> placeholder;
    std::optional<std::string> text;
    TextInputControllerPeer* peerPtr = nullptr;
    auto textInputOptions = Converter::OptConvert<Ark_TextInputOptions>(*value);
    if (textInputOptions) {
        placeholder = Converter::OptConvert<std::string>(textInputOptions.value().placeholder);
        text = Converter::OptConvert<std::string>(textInputOptions.value().text);
        auto controller = Converter::OptConvert<Ark_TextInputController>(textInputOptions.value().controller);
        if (controller.has_value()) {
            peerPtr = controller.value();
        }
    }
    auto controller = TextFieldModelNG::GetController(frameNode, placeholder, text);
    if (peerPtr) {
        peerPtr->SetController(controller);
    }
}
} // TextInputInterfaceModifier
namespace TextInputAttributeModifier {
void TypeImpl(Ark_NativePointer node,
              Ark_InputType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextInputType>(value); //for enums
    TextFieldModelNG::SetType(frameNode, convValue);
}
void ContentTypeImpl(Ark_NativePointer node,
                     Ark_ContentType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextContentType>(value); // for enums
    TextFieldModelNG::SetContentType(frameNode, convValue);
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextFieldModelNG::SetPlaceholderColor(frameNode, convValue);
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
    auto convValue = Converter::OptConvert<Dimension>(*value);
    TextFieldModelNG::SetTextIndent(frameNode, convValue);
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<Font>(*value) : std::nullopt;
    TextFieldModelNG::SetPlaceholderFont(frameNode, convValue);
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextInputAction>(value); // for enums
    TextFieldModelNG::SetEnterKeyType(frameNode, convValue);
}
void CaretColorImpl(Ark_NativePointer node,
                    const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextFieldModelNG::SetCaretColor(frameNode, convValue);
}
void OnEditChangedImpl(Ark_NativePointer node,
                       const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEditChanged = [arkCallback = CallbackHelper(*value)](const bool& boolValue) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(boolValue));
    };
    TextFieldModelNG::SetOnEditChanged(frameNode, onEditChanged);
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEditChange = [arkCallback = CallbackHelper(*value)](const bool& boolValue) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(boolValue));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, onEditChange);
}
void OnSubmitImpl(Ark_NativePointer node,
                  const OnSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSubmit = [arkCallback = CallbackHelper(*value)](
                        const int32_t& value, NG::TextFieldCommonEvent& info) {
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(value));
        const auto event = Converter::ArkSubmitEventSync(info);
        arkCallback.InvokeSync(enterKeyType, event.ArkValue());
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
        const std::string u8Value = UtfUtils::Str16DebugToStr8(changeValueInfo.value);
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(u8Value),
            Converter::ArkValue<Opt_PreviewText>(changeValueInfo.previewText));
    };
    TextFieldModelNG::SetOnChange(frameNode, onChange);
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*value)](const int32_t& start, const int32_t& end) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(start), Converter::ArkValue<Ark_Number>(end));
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, onTextSelectionChange);
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const OnContentScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onContentScroll = [arkCallback = CallbackHelper(*value)](const float& offsetX, const float& offsetY) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(offsetX), Converter::ArkValue<Ark_Number>(offsetY));
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, onContentScroll);
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<int>(*value);
    TextFieldModelNG::SetMaxLength(frameNode, convValue);
}
void FontColorImpl(Ark_NativePointer node,
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Color>(*value);
    TextFieldModelNG::SetTextColor(frameNode, convValue);
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
    auto convValue = Converter::OptConvert<Ace::FontStyle>(value); // for enums
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
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [arkCallback = CallbackHelper(*value)](const std::u16string& copyStr) {
        const std::string u8CopyStr = UtfUtils::Str16DebugToStr8(copyStr);
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(u8CopyStr));
    };
    TextFieldModelNG::SetOnCopy(frameNode, onCopy);
}
void OnCutImpl(Ark_NativePointer node,
               const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCut = [arkCallback = CallbackHelper(*value)](const std::u16string& cutStr) {
        const std::string u8CutStr = UtfUtils::Str16DebugToStr8(cutStr);
        arkCallback.Invoke(Converter::ArkValue<Ark_String>(u8CutStr));
    };
    TextFieldModelNG::SetOnCut(frameNode, onCut);
}
void OnPasteImpl(Ark_NativePointer node,
                 const OnPasteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPaste = [arkCallback = CallbackHelper(*value)](const std::u16string& content) {
        const std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        auto arkContent = Converter::ArkValue<Ark_String>(u8Content);
        Ark_PasteEvent arkEvent;
        arkEvent.preventDefault = {};
        arkCallback.Invoke(arkContent, arkEvent);
    };
    TextFieldModelNG::SetOnPaste(frameNode, std::move(onPaste));
}
void CopyOptionImpl(Ark_NativePointer node,
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<CopyOptions>(value); // for enums
    TextFieldModelNG::SetCopyOption(frameNode, convValue);
}
void ShowPasswordIconImpl(Ark_NativePointer node,
                          Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetShowPasswordIcon(frameNode, convValue);
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextAlign>(value); // for enums
    TextFieldModelNG::SetTextAlign(frameNode, convValue);
}
void StyleImpl(Ark_NativePointer node,
               const Ark_Union_TextInputStyle_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<InputStyle>(*value);
    TextFieldModelNG::SetInputStyle(frameNode, convValue);
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
void CaretPositionImpl(Ark_NativePointer node,
                       const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<int>(*value);
    Validator::ValidateNonNegative(convValue);
    TextFieldModelNG::SetCaretPosition(frameNode, convValue);
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::RequestKeyboardOnFocus(frameNode, convValue);
}
void PasswordIconImpl(Ark_NativePointer node,
                      const Ark_PasswordIcon* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<PasswordIcon>(*value);
    TextFieldModelNG::SetPasswordIcon(frameNode, convValue);
}
void ShowErrorImpl(Ark_NativePointer node,
                   const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> convTextValue = Converter::OptConvert<std::string>(*value);
    std::optional<std::u16string> u16ConvTextValue = std::nullopt;
    auto convBoolValue = convTextValue.has_value() && !convTextValue->empty();
    if (convTextValue.has_value()) {
        u16ConvTextValue = UtfUtils::Str8DebugToStr16(convTextValue.value());
    }
    TextFieldModelNG::SetShowError(frameNode, u16ConvTextValue, convBoolValue);
}
void ShowUnitImpl(Ark_NativePointer node,
                  const CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto builder = [callback = CallbackHelper(*value), node]() -> RefPtr<UINode> {
        return callback.BuildSync(node);
    };
    TextFieldModelNG::SetShowUnit(frameNode, std::move(builder));
}
void ShowUnderlineImpl(Ark_NativePointer node,
                       Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetShowUnderline(frameNode, convValue);
}
void UnderlineColorImpl(Ark_NativePointer node,
                        const Opt_Union_ResourceColor_UnderlineColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<Color> resColor;
    std::optional<UserUnderlineColor> userColor;
    Converter::VisitUnion(
        *value,
        [&resColor](const Ark_ResourceColor& src) { resColor = Converter::OptConvert<Color>(src); },
        [&userColor](const Ark_UnderlineColor& src) { userColor = Converter::OptConvert<UserUnderlineColor>(src); },
        [](const Ark_Undefined& src) {},
        []() {});

    if (resColor.has_value()) {
        auto colorValue = resColor.value();
        userColor = UserUnderlineColor();
        userColor->disable = colorValue;
        userColor->error = colorValue;
        userColor->normal = colorValue;
        userColor->typing = colorValue;
    }
    TextFieldModelNG::SetUserUnderlineColor(frameNode, userColor);
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetSelectionMenuHidden(frameNode, convValue);
}
void BarStateImpl(Ark_NativePointer node,
                  Ark_BarState value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<DisplayMode>(value); // for enums
    TextFieldModelNG::SetBarState(frameNode, convValue);
}
void MaxLinesImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<int>(*value);
    TextFieldModelNG::SetMaxLines(frameNode, convValue);
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
void CancelButton0Impl(Ark_NativePointer node,
                       const Ark_CancelButtonOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto cleanButtonStyle = Converter::OptConvert<CleanNodeStyle>(value->style);
    auto optIconOptions = Converter::OptConvert<Ark_IconOptions>(value->icon);
    TextFieldModelNG::SetCleanNodeStyle(frameNode, cleanButtonStyle);
    if (optIconOptions) {
        TextFieldModelNG::SetCancelIconColor(frameNode, Converter::OptConvert<Color>(optIconOptions->color));
        auto iconSize = Converter::OptConvert<CalcDimension>(optIconOptions->size);
        Validator::ValidateNonNegative(iconSize);
        Validator::ValidateNonPercent(iconSize);
        TextFieldModelNG::SetCancelIconSize(frameNode, iconSize);
        TextFieldModelNG::SetCanacelIconSrc(frameNode, Converter::OptConvert<std::string>(optIconOptions->src));
    }
}
void CancelButton1Impl(Ark_NativePointer node,
                       const Ark_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto cleanButtonStyle = Converter::OptConvert<CleanNodeStyle>(value->style);
    auto symbol = Converter::OptConvert<Ark_SymbolGlyphModifier>(value->icon);
    TextFieldModelNG::SetCleanNodeStyle(frameNode, cleanButtonStyle);
    if (symbol) {
        TextFieldModelNG::SetCancelSymbolIcon(frameNode, nullptr);
        LOGE("TextInputModifier::CancelButton1Impl need to know what data is in value->icon");
    }
}
void SelectAllImpl(Ark_NativePointer node,
                   Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetSelectAllValue(frameNode, convValue);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    TextFieldModelNG::SetAdaptMinFontSize(frameNode, convValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    TextFieldModelNG::SetAdaptMaxFontSize(frameNode, convValue);
}
void HeightAdaptivePolicyImpl(Ark_NativePointer node,
                              Ark_TextHeightAdaptivePolicy value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextHeightAdaptivePolicy>(value);
    TextFieldModelNG::SetHeightAdaptivePolicy(frameNode, convValue);
}
void EnableAutoFillImpl(Ark_NativePointer node,
                        Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetEnableAutoFill(frameNode, convValue);
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
    Validator::ValidateNonPercent(spacing);
    TextFieldModelNG::SetLetterSpacing(frameNode, spacing);
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
void PasswordRulesImpl(Ark_NativePointer node,
                       const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<std::string>(*value);
    TextFieldModelNG::SetPasswordRules(frameNode, convValue);
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
void ShowPasswordImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(value);
    TextFieldModelNG::SetShowPassword(frameNode, convValue);
}
void OnSecurityStateChangeImpl(Ark_NativePointer node,
                               const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSecurityStateChange = [arkCallback = CallbackHelper(*value)](const bool& boolValue) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(boolValue));
    };
    TextFieldModelNG::SetOnSecurityStateChange(frameNode, onSecurityStateChange);
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
    auto onDidInsert = [arkCallback = CallbackHelper(*value)](const InsertValueInfo& insertValueInfo) {
        std::string u8InsertValue = UtfUtils::Str16DebugToStr8(insertValueInfo.insertValue);
        arkCallback.Invoke(Ark_InsertValue {
                .insertOffset = Converter::ArkValue<Ark_Number>(insertValueInfo.insertOffset),
                .insertValue = Converter::ArkValue<Ark_String>(u8InsertValue)
        });
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, onDidInsert);
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
    auto onDidDelete = [arkCallback = CallbackHelper(*value)](const DeleteValueInfo& deleteValueInfo) {
        Converter::ConvContext ctx;
        std::string u8DeleteValue = UtfUtils::Str16DebugToStr8(deleteValueInfo.deleteValue);
        arkCallback.Invoke(Ark_DeleteValue {
                .deleteOffset = Converter::ArkValue<Ark_Number>(deleteValueInfo.deleteOffset),
                .direction = Converter::ArkValue<Ark_TextDeleteDirection>(deleteValueInfo.direction),
                .deleteValue = Converter::ArkValue<Ark_String>(u8DeleteValue, &ctx)
        });
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, onDidDelete);
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         Ark_EditMenuOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //TextInputModelNG::SetEditMenuOptions(frameNode, convValue);
    LOGE("TextInputInterfaceModifier::EditMenuOptionsImpl not implemented");
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::Convert<bool>(value);
    TextFieldModelNG::SetEnablePreviewText(frameNode, convValue);
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
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomNodeBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    KeyboardOptions keyboardOptions = {.supportAvoidance = false};
    auto convOptions = options ? Converter::OptConvert<KeyboardOptions>(*options) : keyboardOptions;
    auto customNode = CallbackHelper(*value).BuildSync(node);
    auto customFrameNode = AceType::DynamicCast<FrameNode>(customNode).GetRawPtr();
    bool supportAvoidance = convOptions.has_value() ? convOptions->supportAvoidance : false;
    TextFieldModelNG::SetCustomKeyboard(frameNode, customFrameNode, supportAvoidance);
}
void ShowCounterImpl(Ark_NativePointer node,
                     Ark_Boolean value,
                     const Opt_InputCounterOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto counterOptions = Converter::OptConvert<InputCounterOptions>(*options);
    auto isShowCounter = Converter::Convert<bool>(value);
    if (counterOptions && counterOptions->thresholdPercentage.has_value()) {
        int32_t thresholdValue = counterOptions->thresholdPercentage.value();
        if (thresholdValue < MIN_THRESHOLD_PERCENTAGE || thresholdValue > MAX_THRESHOLD_PERCENTAGE) {
            counterOptions->thresholdPercentage = std::nullopt;
            isShowCounter = false;
        }
    }
    TextFieldModelNG::SetShowCounter(frameNode, isShowCounter);
    TextFieldModelNG::SetCounterType(frameNode, counterOptions->thresholdPercentage);
    TextFieldModelNG::SetShowCounterBorder(frameNode, counterOptions->highlightBorder);
}
void _onChangeEvent_textImpl(Ark_NativePointer node,
                             const Callback_ResourceStr_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        const std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(u8Content, &ctx);
        arkCallback.Invoke(arkContent);
    };
    TextFieldModelNG::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // TextInputAttributeModifier
const GENERATED_ArkUITextInputModifier* GetTextInputModifier()
{
    static const GENERATED_ArkUITextInputModifier ArkUITextInputModifierImpl {
        TextInputModifier::ConstructImpl,
        TextInputInterfaceModifier::SetTextInputOptionsImpl,
        TextInputAttributeModifier::TypeImpl,
        TextInputAttributeModifier::ContentTypeImpl,
        TextInputAttributeModifier::PlaceholderColorImpl,
        TextInputAttributeModifier::TextOverflowImpl,
        TextInputAttributeModifier::TextIndentImpl,
        TextInputAttributeModifier::PlaceholderFontImpl,
        TextInputAttributeModifier::EnterKeyTypeImpl,
        TextInputAttributeModifier::CaretColorImpl,
        TextInputAttributeModifier::OnEditChangedImpl,
        TextInputAttributeModifier::OnEditChangeImpl,
        TextInputAttributeModifier::OnSubmitImpl,
        TextInputAttributeModifier::OnChangeImpl,
        TextInputAttributeModifier::OnTextSelectionChangeImpl,
        TextInputAttributeModifier::OnContentScrollImpl,
        TextInputAttributeModifier::MaxLengthImpl,
        TextInputAttributeModifier::FontColorImpl,
        TextInputAttributeModifier::FontSizeImpl,
        TextInputAttributeModifier::FontStyleImpl,
        TextInputAttributeModifier::FontWeightImpl,
        TextInputAttributeModifier::FontFamilyImpl,
        TextInputAttributeModifier::OnCopyImpl,
        TextInputAttributeModifier::OnCutImpl,
        TextInputAttributeModifier::OnPasteImpl,
        TextInputAttributeModifier::CopyOptionImpl,
        TextInputAttributeModifier::ShowPasswordIconImpl,
        TextInputAttributeModifier::TextAlignImpl,
        TextInputAttributeModifier::StyleImpl,
        TextInputAttributeModifier::CaretStyleImpl,
        TextInputAttributeModifier::SelectedBackgroundColorImpl,
        TextInputAttributeModifier::CaretPositionImpl,
        TextInputAttributeModifier::EnableKeyboardOnFocusImpl,
        TextInputAttributeModifier::PasswordIconImpl,
        TextInputAttributeModifier::ShowErrorImpl,
        TextInputAttributeModifier::ShowUnitImpl,
        TextInputAttributeModifier::ShowUnderlineImpl,
        TextInputAttributeModifier::UnderlineColorImpl,
        TextInputAttributeModifier::SelectionMenuHiddenImpl,
        TextInputAttributeModifier::BarStateImpl,
        TextInputAttributeModifier::MaxLinesImpl,
        TextInputAttributeModifier::WordBreakImpl,
        TextInputAttributeModifier::LineBreakStrategyImpl,
        TextInputAttributeModifier::CancelButton0Impl,
        TextInputAttributeModifier::CancelButton1Impl,
        TextInputAttributeModifier::SelectAllImpl,
        TextInputAttributeModifier::MinFontSizeImpl,
        TextInputAttributeModifier::MaxFontSizeImpl,
        TextInputAttributeModifier::HeightAdaptivePolicyImpl,
        TextInputAttributeModifier::EnableAutoFillImpl,
        TextInputAttributeModifier::DecorationImpl,
        TextInputAttributeModifier::LetterSpacingImpl,
        TextInputAttributeModifier::LineHeightImpl,
        TextInputAttributeModifier::PasswordRulesImpl,
        TextInputAttributeModifier::FontFeatureImpl,
        TextInputAttributeModifier::ShowPasswordImpl,
        TextInputAttributeModifier::OnSecurityStateChangeImpl,
        TextInputAttributeModifier::OnWillInsertImpl,
        TextInputAttributeModifier::OnDidInsertImpl,
        TextInputAttributeModifier::OnWillDeleteImpl,
        TextInputAttributeModifier::OnDidDeleteImpl,
        TextInputAttributeModifier::EditMenuOptionsImpl,
        TextInputAttributeModifier::EnablePreviewTextImpl,
        TextInputAttributeModifier::EnableHapticFeedbackImpl,
        TextInputAttributeModifier::InputFilterImpl,
        TextInputAttributeModifier::CustomKeyboardImpl,
        TextInputAttributeModifier::ShowCounterImpl,
        TextInputAttributeModifier::_onChangeEvent_textImpl,
    };
    return &ArkUITextInputModifierImpl;
}

}
