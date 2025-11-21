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
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/text_input_controller_peer.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter_union.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components/common/properties/text_style_parser.h"
#include "core/image/image_source_info.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t MIN_THRESHOLD_PERCENTAGE = 1;
constexpr int32_t MAX_THRESHOLD_PERCENTAGE = 100;
constexpr float SCALE_LIMIT = 1.f;
constexpr uint32_t ILLEGAL_VALUE = 0;

struct InputCounterOptions {
    std::optional<int> thresholdPercentage;
    std::optional<bool> highlightBorder;
};

std::optional<std::u16string> ProcessBindableText(FrameNode* frameNode,
    const Opt_Union_ResourceStr_Bindable_Bindable_Bindable& value)
{
    std::optional<std::u16string> result;
    Converter::VisitUnion(value,
        [&result](const Ark_ResourceStr& src) {
            result = Converter::OptConvert<std::u16string>(src);
        },
        [&result, frameNode](const Ark_Bindable_String& src) {
            result = Converter::OptConvert<std::u16string>(src.value);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange)](const std::u16string& content) {
                Converter::ConvContext ctx;
                auto arkContent = Converter::ArkValue<Ark_String>(content, &ctx);
                arkCallback.InvokeSync(arkContent);
            };
            TextFieldModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [&result, frameNode](const Ark_Bindable_Arkui_Component_Units_ResourceStr& src) {
            result = Converter::OptConvert<std::u16string>(src.value);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange)](const std::u16string& content) {
                Converter::ConvContext ctx;
                auto arkContent = Converter::ArkUnion<Ark_ResourceStr, Ark_String>(content, &ctx);
                arkCallback.InvokeSync(arkContent);
            };
            TextFieldModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [](const Ark_Bindable_Global_Resource_Resource& src) {
            // Invalid case, should be deleted from SDK
        },
        [] {});
    return result;
}
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
    auto frameNode = TextFieldModelStatic::CreateTextInputNode(id, u"", u"");
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
    std::optional<std::u16string> placeholder;
    std::optional<std::u16string> text;
    TextInputControllerPeer* peerPtr = nullptr;
    auto textInputOptions = Converter::GetOptPtr(value);
    if (textInputOptions) {
        placeholder = Converter::OptConvert<std::u16string>(textInputOptions->placeholder);
        text = ProcessBindableText(frameNode, textInputOptions->text);
        auto controller = Converter::GetOpt(textInputOptions->controller);
        if (controller.has_value()) {
            peerPtr = controller.value();
        }
    }
    auto controller = TextFieldModelStatic::GetController(frameNode, placeholder, text);
    if (peerPtr) {
        peerPtr->SetController(controller);
    }
}
} // TextInputInterfaceModifier
namespace TextInputAttributeModifier {
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_InputType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextInputType>(value);
    TextFieldModelStatic::SetType(frameNode, convValue);
}
void SetContentTypeImpl(Ark_NativePointer node,
                        const Opt_ContentType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextContentType>(value);
    TextFieldModelStatic::SetContentType(frameNode, convValue);
}
void SetPlaceholderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, convValue);
}
void SetTextOverflowImpl(Ark_NativePointer node,
                         const Opt_TextOverflow* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextOverflow>(value);
    TextFieldModelStatic::SetTextOverflow(frameNode, convValue);
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes<Ark_Dimension, Ark_Number>(value->value, DimensionUnit::FP);
    }
    TextFieldModelStatic::SetTextIndent(frameNode, convValue);
}
void SetPlaceholderFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Font>(value);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, convValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextInputAction>(value);
    TextFieldModelStatic::SetEnterKeyType(frameNode, convValue);
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextFieldModelStatic::SetCaretColor(frameNode, convValue);
}
void SetOnEditChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnEditChange(frameNode, nullptr);
        return;
    }
    auto onEditChange = [arkCallback = CallbackHelper(*optValue)](const bool& boolValue) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Boolean>(boolValue));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditChange));
}
void SetOnSubmitImpl(Ark_NativePointer node,
                     const Opt_OnSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnSubmit(frameNode, nullptr);
        return;
    }
    auto onSubmit = [arkCallback = CallbackHelper(*optValue)](
                        const int32_t& value, NG::TextFieldCommonEvent& info) {
        auto enterKeyType = Converter::ArkValue<Ark_EnterKeyType>(static_cast<TextInputAction>(value));
        const auto event = Converter::ArkSubmitEventSync(info);
        arkCallback.InvokeSync(enterKeyType, event.ArkValue());
    };
    TextFieldModelNG::SetOnSubmit(frameNode, onSubmit);
}
void SetOnChangeImpl(Ark_NativePointer node,
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
        auto options = Converter::ArkValue<Opt_TextChangeOptions>(info, &ctx);
        arkCallback.InvokeSync(textArkString, textArkPrevText, options);
    };
    TextFieldModelNG::SetOnChange(frameNode, onChange);
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnTextSelectionChange(frameNode, nullptr);
        return;
    }
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*optValue)](const int32_t& start, const int32_t& end) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(start), Converter::ArkValue<Ark_Int32>(end));
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, onTextSelectionChange);
}
void SetOnContentScrollImpl(Ark_NativePointer node,
                            const Opt_OnContentScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnContentScroll(frameNode, nullptr);
        return;
    }
    auto onContentScroll = [arkCallback = CallbackHelper(*optValue)](const float& offsetX, const float& offsetY) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Int32>(offsetX), Converter::ArkValue<Ark_Int32>(offsetY));
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, onContentScroll);
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLength = Converter::OptConvertPtr<int>(value);
    Validator::ValidateNonNegative(maxLength);
    if (maxLength) {
        TextFieldModelNG::SetMaxLength(frameNode, *maxLength);
    } else {
        TextFieldModelNG::ResetMaxLength(frameNode);
    }
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Color>(value);
    TextFieldModelStatic::SetTextColor(frameNode, convValue);
}
void SetFontSizeImpl(Ark_NativePointer node,
                     const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontSize = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(fontSize);
    Validator::ValidateNonPercent(fontSize);
    TextFieldModelStatic::SetFontSize(frameNode, fontSize);
}
void SetFontStyleImpl(Ark_NativePointer node,
                      const Opt_FontStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<Ace::FontStyle>(value);
    TextFieldModelStatic::SetFontStyle(frameNode, convValue);
}
void SetFontWeightImpl(Ark_NativePointer node,
                       const Opt_Union_I32_FontWeight_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<FontWeight>(value);
    TextFieldModelStatic::SetFontWeight(frameNode, convValue);
}
void SetFontFamilyImpl(Ark_NativePointer node,
                       const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<StringArray> families;
    if (auto fontfamiliesOpt = Converter::OptConvertPtr<Converter::FontFamilies>(value); fontfamiliesOpt) {
        families = fontfamiliesOpt->families;
    }
    TextFieldModelStatic::SetFontFamily(frameNode, families);
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnCopy(frameNode, nullptr);
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& copyStr) {
        Converter::ConvContext ctx;
        arkCallback.InvokeSync(Converter::ArkValue<Ark_String>(copyStr, &ctx));
    };
    TextFieldModelNG::SetOnCopy(frameNode, onCopy);
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnCut(frameNode, nullptr);
        return;
    }
    auto onCut = [arkCallback = CallbackHelper(*optValue)](const std::u16string& cutStr) {
        Converter::ConvContext ctx;
        arkCallback.InvokeSync(Converter::ArkValue<Ark_String>(cutStr, &ctx));
    };
    TextFieldModelNG::SetOnCut(frameNode, onCut);
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_OnPasteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnPasteWithEvent(frameNode, nullptr);
        return;
    }
    auto onPaste = [arkCallback = CallbackHelper(*optValue)](const std::u16string& content,
        NG::TextCommonEvent& event) -> void {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkValue<Ark_String>(content, &ctx);
        Ark_PasteEvent arkEvent = PasteEventPeer::Create();
        CHECK_NULL_VOID(arkEvent);
        auto preventDefault = [&event]() { event.SetPreventDefault(true); };
        arkEvent->SetPreventDefault(preventDefault);
        arkCallback.InvokeSync(arkContent, arkEvent);
    };
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<CopyOptions>(value);
    TextFieldModelStatic::SetCopyOption(frameNode, convValue);
}
void SetShowPasswordIconImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetShowPasswordIcon(frameNode, convValue);
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextAlign>(value);
    TextFieldModelStatic::SetTextAlign(frameNode, convValue);
}
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_Union_TextInputStyle_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<InputStyle>(value);
    TextFieldModelStatic::SetInputStyle(frameNode, convValue);
}
void SetCaretStyleImpl(Ark_NativePointer node,
                       const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto caretStyle = Converter::OptConvertPtr<Converter::CaretStyle>(value).value_or(Converter::CaretStyle{});
    TextFieldModelStatic::SetCaretColor(frameNode, caretStyle.color);
    Validator::ValidateNonNegative(caretStyle.width);
    Validator::ValidateNonPercent(caretStyle.width);
    TextFieldModelStatic::SetCaretWidth(frameNode, caretStyle.width);
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetSelectedBackgroundColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetCaretPositionImpl(Ark_NativePointer node,
                          const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int>(value);
    Validator::ValidateNonNegative(convValue);
    TextFieldModelStatic::SetCaretPosition(frameNode, convValue);
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, convValue);
}
void SetPasswordIconImpl(Ark_NativePointer node,
                         const Opt_PasswordIcon* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<PasswordIcon>(value);
    TextFieldModelStatic::SetPasswordIcon(frameNode, convValue);
}
void SetShowErrorImpl(Ark_NativePointer node,
                      const Opt_ResourceStr* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convTextValue = Converter::OptConvertPtr<std::u16string>(value);
    auto convBoolValue = convTextValue.has_value() && !convTextValue->empty();
    TextFieldModelStatic::SetShowError(frameNode, convTextValue, convBoolValue);
}
void SetShowUnitImpl(Ark_NativePointer node,
                     const Opt_CustomNodeBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelStatic::SetShowUnit(frameNode, nullptr);
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode](const RefPtr<UINode>& uiNode) {
        auto builder = [uiNode]() -> RefPtr<UINode> {
            return uiNode;
        };
        TextFieldModelStatic::SetShowUnit(frameNode, std::move(builder));
        }, node);
}
void SetShowUnderlineImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetShowUnderline(frameNode, convValue);
}
void SetUnderlineColorImpl(Ark_NativePointer node,
                           const Opt_Union_ResourceColor_UnderlineColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
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
    TextFieldModelStatic::SetUserUnderlineColor(frameNode, userColor);
}
void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<DisplayMode>(value);
    TextFieldModelStatic::SetBarState(frameNode, convValue);
}
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int>(value);
    TextFieldModelStatic::SetMaxViewLines(frameNode, convValue);
}
void SetWordBreakImpl(Ark_NativePointer node,
                      const Opt_WordBreak* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<WordBreak>(value);
    TextFieldModelStatic::SetWordBreak(frameNode, convValue);
}
void SetLineBreakStrategyImpl(Ark_NativePointer node,
                              const Opt_LineBreakStrategy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<LineBreakStrategy>(value);
    TextFieldModelStatic::SetLineBreakStrategy(frameNode, convValue);
}
void SetCancelButton0Impl(Ark_NativePointer node, const Opt_CancelButtonOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto cleanButtonStyle = optValue ? Converter::OptConvert<CleanNodeStyle>(optValue->style) : std::nullopt;
    auto optIconOptions = optValue ? Converter::OptConvert<Ark_IconOptions>(optValue->icon) : std::nullopt;
    TextFieldModelStatic::SetCleanNodeStyle(frameNode, cleanButtonStyle);
    TextFieldModelNG::SetIsShowCancelButton(frameNode, true);
    TextFieldModelNG::SetCancelButtonSymbol(frameNode, false);
    if (!optIconOptions) {
        TextFieldModelStatic::SetDefaultCancelIcon(frameNode);
        return;
    }
    // set icon size
    auto iconSize = Converter::OptConvert<CalcDimension>(optIconOptions->size);
    Validator::ValidateNonNegative(iconSize);
    Validator::ValidateNonPercent(iconSize);
    TextFieldModelStatic::SetCancelIconSize(frameNode, iconSize);
    // set icon src
    auto iconSrcOpt = Converter::OptConvert<Converter::Ark_Resource_Simple>(optIconOptions->src);
    if (!iconSrcOpt) {
        iconSrcOpt = Converter::Ark_Resource_Simple();
    }
    TextFieldModelStatic::SetCanacelIconSrc(frameNode, iconSrcOpt->content, iconSrcOpt->bundleName,
        iconSrcOpt->moduleName);
    // set icon color
    auto info = ImageSourceInfo(iconSrcOpt->content, iconSrcOpt->bundleName, iconSrcOpt->moduleName);
    if (info.IsSvg() && iconSrcOpt->content != "") {
        // svg need not default color, otherwise multi color svg will render fault
        return;
    }
    std::optional<Color> iconColor;
    if (Container::CurrentColorMode() != ColorMode::DARK) {
        iconColor = Converter::OptConvert<Color>(optIconOptions->color);
    }
    TextFieldModelStatic::SetCancelIconColor(frameNode, iconColor);
}
void SetCancelButton1Impl(Ark_NativePointer node, const Opt_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto cleanButtonStyle = optValue ? Converter::OptConvert<CleanNodeStyle>(optValue->style) : std::nullopt;
    auto symbolModifier = optValue ? Converter::OptConvert<Ark_SymbolGlyphModifier>(optValue->icon) : std::nullopt;
    TextFieldModelStatic::SetCleanNodeStyle(frameNode, cleanButtonStyle);
    TextFieldModelNG::SetIsShowCancelButton(frameNode, true);
    TextFieldModelNG::SetCancelButtonSymbol(frameNode, true);
    if (symbolModifier && *symbolModifier) {
        TextFieldModelNG::SetCancelSymbolIcon(frameNode, (*symbolModifier)->symbolApply);
        PeerUtils::DestroyPeer(*symbolModifier);
    }
}
void SetSelectAllImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetSelectAllValue(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    TextFieldModelStatic::SetAdaptMinFontSize(frameNode, convValue);
}
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> convValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        convValue = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateNonPercent(convValue);
    TextFieldModelStatic::SetAdaptMaxFontSize(frameNode, convValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    TextFieldModelStatic::SetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    TextFieldModelStatic::SetMaxFontScale(frameNode, convValue);
}
void SetHeightAdaptivePolicyImpl(Ark_NativePointer node,
                                 const Opt_TextHeightAdaptivePolicy* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<TextHeightAdaptivePolicy>(value);
    TextFieldModelStatic::SetHeightAdaptivePolicy(frameNode, convValue);
}
void SetEnableAutoFillImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetEnableAutoFill(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = Converter::OptConvertPtr<Converter::TextDecorationOptions>(value)
        .value_or(Converter::TextDecorationOptions{});
    TextFieldModelStatic::SetTextDecoration(frameNode, options.textDecoration);
    TextFieldModelStatic::SetTextDecorationColor(frameNode, options.color);
    TextFieldModelStatic::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void SetLetterSpacingImpl(Ark_NativePointer node,
                          const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> spacing = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        spacing = Converter::OptConvertFromArkNumStrRes(value->value);
    }
    Validator::ValidateNonPercent(spacing);
    TextFieldModelStatic::SetLetterSpacing(frameNode, spacing);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_F64_String_Resource* value)
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
void SetPasswordRulesImpl(Ark_NativePointer node,
                          const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    TextFieldModelStatic::SetPasswordRules(frameNode, convValue);
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    TextFieldModelStatic::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
}
void SetShowPasswordImpl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetShowPassword(frameNode, convValue);
}
void SetOnSecurityStateChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelStatic::SetOnSecurityStateChange(frameNode, nullptr);
        return;
    }
    auto onSecurityStateChange = [arkCallback = CallbackHelper(*optValue)](const bool& boolValue) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Boolean>(boolValue));
    };
    TextFieldModelStatic::SetOnSecurityStateChange(frameNode, onSecurityStateChange);
}
void SetOnWillInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
        return;
    }
    auto onWillInsert = [callback = CallbackHelper(*optValue)](const InsertValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Int32>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue, &ctx)
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(insertValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}
void SetOnDidInsertImpl(Ark_NativePointer node,
                        const Opt_Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
        return;
    }
    auto onDidInsert = [arkCallback = CallbackHelper(*optValue)](const InsertValueInfo& insertValueInfo) {
        Converter::ConvContext ctx;
        arkCallback.InvokeSync(Ark_InsertValue {
                .insertOffset = Converter::ArkValue<Ark_Int32>(insertValueInfo.insertOffset),
                .insertValue = Converter::ArkValue<Ark_String>(insertValueInfo.insertValue, &ctx)
        });
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, onDidInsert);
}
void SetOnWillDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
        return;
    }
    auto onWillDelete = [callback = CallbackHelper(*optValue)](const DeleteValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Int32>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue, &ctx)
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(deleteValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}
void SetOnDidDeleteImpl(Ark_NativePointer node,
                        const Opt_Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
        return;
    }
    auto onDidDelete = [arkCallback = CallbackHelper(*optValue)](const DeleteValueInfo& deleteValueInfo) {
        Converter::ConvContext ctx;
        arkCallback.InvokeSync(Ark_DeleteValue {
                .deleteOffset = Converter::ArkValue<Ark_Int32>(deleteValueInfo.deleteOffset),
                .direction = Converter::ArkValue<Ark_TextDeleteDirection>(deleteValueInfo.direction),
                .deleteValue = Converter::ArkValue<Ark_String>(deleteValueInfo.deleteValue, &ctx)
        });
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, onDidDelete);
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelStatic::SetSelectionMenuOptions(frameNode, nullptr, nullptr);
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
    }
    TextFieldModelStatic::SetSelectionMenuOptions(
        frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetEnablePreviewText(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void SetAutoCapitalizationModeImpl(Ark_NativePointer node,
                                   const Opt_AutoCapitalizationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void SetHalfLeadingImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetHalfLeading(frameNode, Converter::OptConvertPtr<bool>(value));
}
void SetEllipsisModeImpl(Ark_NativePointer node,
                         const Opt_EllipsisMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<EllipsisMode>(value);
    TextFieldModelStatic::SetEllipsisMode(frameNode, convValue);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetStopBackPress(frameNode, Converter::OptConvertPtr<bool>(value));
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnWillChangeEvent(frameNode, nullptr);
        return;
    }
    auto onWillChange = [callback = CallbackHelper(*optValue)](const ChangeValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_EditableTextChangeValue changeValue = {
            .content = Converter::ArkValue<Ark_String>(value.value, &ctx),
            .previewText = Converter::ArkValue<Opt_PreviewText>(value.previewText),
            .options = Converter::ArkValue<Opt_TextChangeOptions>(value, &ctx),
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(changeValue)
            .value_or(true);
    };
    TextFieldModelNG::SetOnWillChangeEvent(frameNode, std::move(onWillChange));
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<KeyboardAppearance>(value);
    TextFieldModelStatic::SetKeyboardAppearance(frameNode, convValue);
}
void SetInputFilterImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto valueString = Converter::OptConvertPtr<std::string>(value);
    std::function<void(const std::u16string&)> onErrorEvent = nullptr;
    auto arkOnError = Converter::GetOptPtr(error);
    if (arkOnError) {
        onErrorEvent = [arkCallback = CallbackHelper(arkOnError.value())](const std::u16string& val) {
            Converter::ConvContext ctx;
            arkCallback.InvokeSync(Converter::ArkValue<Ark_String>(val, &ctx));
        };
    }
    TextFieldModelNG::SetInputFilter(frameNode, valueString.value_or(""), std::move(onErrorEvent));
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convOptions = Converter::OptConvertPtr<KeyboardOptions>(options);
    bool supportAvoidance = convOptions.has_value() ? convOptions->supportAvoidance : false;
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetCustomKeyboard(frameNode, nullptr, false);
        return;
    }
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto customNodeBuilder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        TextFieldModelStatic::SetCustomKeyboard(frameNode, std::move(customNodeBuilder), supportAvoidance);
        }, node);
}
void SetShowCounterImpl(Ark_NativePointer node,
                        const Opt_Boolean* value,
                        const Opt_InputCounterOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto counterOptions = Converter::OptConvertPtr<InputCounterOptions>(options);
    auto isShowCounter = Converter::OptConvertPtr<bool>(value);
    if (!isShowCounter) {
        TextFieldModelStatic::SetShowCounter(frameNode, std::nullopt);
        TextFieldModelStatic::SetCounterType(frameNode, std::nullopt);
        TextFieldModelStatic::SetShowCounterBorder(frameNode, std::nullopt);
        return;
    }
    if (counterOptions && counterOptions->thresholdPercentage.has_value()) {
        int32_t thresholdValue = counterOptions->thresholdPercentage.value();
        if (thresholdValue < MIN_THRESHOLD_PERCENTAGE || thresholdValue > MAX_THRESHOLD_PERCENTAGE) {
            counterOptions->thresholdPercentage = ILLEGAL_VALUE;
            isShowCounter = false;
        }
    }
    TextFieldModelStatic::SetShowCounter(frameNode, isShowCounter);
    TextFieldModelStatic::SetCounterType(frameNode, counterOptions->thresholdPercentage);
    TextFieldModelStatic::SetShowCounterBorder(frameNode, counterOptions->highlightBorder);
}
} // TextInputAttributeModifier
const GENERATED_ArkUITextInputModifier* GetTextInputModifier()
{
    static const GENERATED_ArkUITextInputModifier ArkUITextInputModifierImpl {
        TextInputModifier::ConstructImpl,
        TextInputInterfaceModifier::SetTextInputOptionsImpl,
        TextInputAttributeModifier::SetTypeImpl,
        TextInputAttributeModifier::SetContentTypeImpl,
        TextInputAttributeModifier::SetPlaceholderColorImpl,
        TextInputAttributeModifier::SetTextOverflowImpl,
        TextInputAttributeModifier::SetTextIndentImpl,
        TextInputAttributeModifier::SetPlaceholderFontImpl,
        TextInputAttributeModifier::SetEnterKeyTypeImpl,
        TextInputAttributeModifier::SetCaretColorImpl,
        TextInputAttributeModifier::SetOnEditChangeImpl,
        TextInputAttributeModifier::SetOnSubmitImpl,
        TextInputAttributeModifier::SetOnChangeImpl,
        TextInputAttributeModifier::SetOnTextSelectionChangeImpl,
        TextInputAttributeModifier::SetOnContentScrollImpl,
        TextInputAttributeModifier::SetMaxLengthImpl,
        TextInputAttributeModifier::SetFontColorImpl,
        TextInputAttributeModifier::SetFontSizeImpl,
        TextInputAttributeModifier::SetFontStyleImpl,
        TextInputAttributeModifier::SetFontWeightImpl,
        TextInputAttributeModifier::SetFontFamilyImpl,
        TextInputAttributeModifier::SetOnCopyImpl,
        TextInputAttributeModifier::SetOnCutImpl,
        TextInputAttributeModifier::SetOnPasteImpl,
        TextInputAttributeModifier::SetCopyOptionImpl,
        TextInputAttributeModifier::SetShowPasswordIconImpl,
        TextInputAttributeModifier::SetTextAlignImpl,
        TextInputAttributeModifier::SetStyleImpl,
        TextInputAttributeModifier::SetCaretStyleImpl,
        TextInputAttributeModifier::SetSelectedBackgroundColorImpl,
        TextInputAttributeModifier::SetCaretPositionImpl,
        TextInputAttributeModifier::SetEnableKeyboardOnFocusImpl,
        TextInputAttributeModifier::SetPasswordIconImpl,
        TextInputAttributeModifier::SetShowErrorImpl,
        TextInputAttributeModifier::SetShowUnitImpl,
        TextInputAttributeModifier::SetShowUnderlineImpl,
        TextInputAttributeModifier::SetUnderlineColorImpl,
        TextInputAttributeModifier::SetSelectionMenuHiddenImpl,
        TextInputAttributeModifier::SetBarStateImpl,
        TextInputAttributeModifier::SetMaxLinesImpl,
        TextInputAttributeModifier::SetWordBreakImpl,
        TextInputAttributeModifier::SetLineBreakStrategyImpl,
        TextInputAttributeModifier::SetCancelButton0Impl,
        TextInputAttributeModifier::SetCancelButton1Impl,
        TextInputAttributeModifier::SetSelectAllImpl,
        TextInputAttributeModifier::SetMinFontSizeImpl,
        TextInputAttributeModifier::SetMaxFontSizeImpl,
        TextInputAttributeModifier::SetMinFontScaleImpl,
        TextInputAttributeModifier::SetMaxFontScaleImpl,
        TextInputAttributeModifier::SetHeightAdaptivePolicyImpl,
        TextInputAttributeModifier::SetEnableAutoFillImpl,
        TextInputAttributeModifier::SetDecorationImpl,
        TextInputAttributeModifier::SetLetterSpacingImpl,
        TextInputAttributeModifier::SetLineHeightImpl,
        TextInputAttributeModifier::SetPasswordRulesImpl,
        TextInputAttributeModifier::SetFontFeatureImpl,
        TextInputAttributeModifier::SetShowPasswordImpl,
        TextInputAttributeModifier::SetOnSecurityStateChangeImpl,
        TextInputAttributeModifier::SetOnWillInsertImpl,
        TextInputAttributeModifier::SetOnDidInsertImpl,
        TextInputAttributeModifier::SetOnWillDeleteImpl,
        TextInputAttributeModifier::SetOnDidDeleteImpl,
        TextInputAttributeModifier::SetEditMenuOptionsImpl,
        TextInputAttributeModifier::SetEnablePreviewTextImpl,
        TextInputAttributeModifier::SetEnableHapticFeedbackImpl,
        TextInputAttributeModifier::SetAutoCapitalizationModeImpl,
        TextInputAttributeModifier::SetHalfLeadingImpl,
        TextInputAttributeModifier::SetEllipsisModeImpl,
        TextInputAttributeModifier::SetStopBackPressImpl,
        TextInputAttributeModifier::SetOnWillChangeImpl,
        TextInputAttributeModifier::SetKeyboardAppearanceImpl,
        TextInputAttributeModifier::SetInputFilterImpl,
        TextInputAttributeModifier::SetCustomKeyboardImpl,
        TextInputAttributeModifier::SetShowCounterImpl,
    };
    return &ArkUITextInputModifierImpl;
}

}
