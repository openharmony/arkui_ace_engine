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
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/text_field/text_field_model_ng.h"
#include "core/components_ng/pattern/text_field/text_field_model_static.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {
namespace {
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
} // namespace OHOS::Ace::NG

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
    std::optional<std::u16string> placeholder;
    std::optional<std::u16string> text;
    TextAreaControllerPeer* peerPtr = nullptr;
    auto textAreaOptions = Converter::GetOptPtr(value);
    if (textAreaOptions.has_value()) {
        placeholder = Converter::OptConvert<std::u16string>(textAreaOptions->placeholder);
        text = ProcessBindableText(frameNode, textAreaOptions->text);
        auto controller = Converter::GetOpt(textAreaOptions->controller);
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
void SetPlaceholderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetPlaceholderColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetPlaceholderFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetPlaceholderFont(frameNode, Converter::OptConvertPtr<Font>(value));
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetEnterKeyType(frameNode, Converter::OptConvertPtr<TextInputAction>(value));
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextAlign(frameNode, Converter::OptConvertPtr<TextAlign>(value));
}
void SetCaretColorImpl(Ark_NativePointer node,
                       const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetCaretColor(frameNode, Converter::OptConvertPtr<Color>(value));
}
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetTextColor(frameNode, Converter::OptConvertPtr<Color>(value));
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
void SetOnSubmitImpl(Ark_NativePointer node, const Opt_TextAreaSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnSubmit(frameNode, nullptr);
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
    TextFieldModelNG::SetOnChange(frameNode, std::move(onChange));
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        TextFieldModelNG::SetOnTextSelectionChange(frameNode, nullptr);
        return;
    }
    auto onEvent = [arkCallback = CallbackHelper(*optValue)](int32_t selectionStart, int32_t selectionEnd) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Int32>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Int32>(selectionEnd);
        arkCallback.InvokeSync(arkSelectionStart, arkSelectionEnd);
    };
    TextFieldModelNG::SetOnTextSelectionChange(frameNode, std::move(onEvent));
}
void SetOnContentScrollImpl(Ark_NativePointer node,
                            const Opt_Callback_F64_F64_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // Implement Reset value
        return;
    }
    auto onContentScroll = [arkCallback = CallbackHelper(*optValue)](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Float64>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Float64>(totalOffsetY);
        arkCallback.InvokeSync(arkTotalOffsetX, arkTotalOffsetY);
    };
    TextFieldModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
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
    auto onEditEvent = [arkCallback = CallbackHelper(*optValue)](const bool value) {
        arkCallback.InvokeSync(Converter::ArkValue<Ark_Boolean>(value));
    };
    TextFieldModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
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
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.InvokeSync(textArkString);
    };
    TextFieldModelNG::SetOnCopy(frameNode, std::move(onCopy));
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
    auto onCut = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.InvokeSync(textArkString);
    };
    TextFieldModelNG::SetOnCut(frameNode, std::move(onCut));
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_Callback_String_PasteEvent_Void* value)
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
        auto keeper = CallbackKeeper::Claim([&event]() {
            event.SetPreventDefault(true);
        });
        Ark_PasteEvent arkEvent = {
            .preventDefault = Converter::ArkValue<Opt_VoidCallback>(keeper.ArkValue())
        };
        arkCallback.InvokeSync(arkContent, arkEvent);
    };
    TextFieldModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetCopyOption(frameNode, Converter::OptConvertPtr<CopyOptions>(value));
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::RequestKeyboardOnFocus(frameNode, convValue);
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
void SetStyleImpl(Ark_NativePointer node,
                  const Opt_TextContentStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<InputStyle>(value);
    TextFieldModelStatic::SetInputStyle(frameNode, convValue);
}
void SetBarStateImpl(Ark_NativePointer node,
                     const Opt_BarState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<DisplayMode>(value);
    TextFieldModelStatic::SetBarState(frameNode, convValue);
}
void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetSelectionMenuHidden(frameNode, convValue);
}
void SetMinFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
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
void SetMaxFontSizeImpl(Ark_NativePointer node,
                        const Opt_Union_F64_String_Resource* value)
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
void SetMaxLinesImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLines = Converter::OptConvertPtr<uint32_t>(value);
    TextFieldModelStatic::SetNormalMaxViewLines(frameNode, maxLines);
    TextFieldModelStatic::SetMaxViewLines(frameNode, maxLines);
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
    Validator::ValidateNonNegative(spacing);
    Validator::ValidateNonPercent(spacing);
    TextFieldModelStatic::SetLetterSpacing(frameNode, spacing);
}
void SetLineSpacingImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto lineSpacing = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(lineSpacing);
    TextFieldModelStatic::SetLineSpacing(frameNode, lineSpacing);
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
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_TextAreaType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetType(frameNode, Converter::OptConvertPtr<TextInputType>(value));
}
void SetEnableAutoFillImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    TextFieldModelStatic::SetEnableAutoFill(frameNode, convValue);
}
void SetContentTypeImpl(Ark_NativePointer node,
                        const Opt_ContentType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    TextFieldModelStatic::SetContentType(frameNode, Converter::OptConvertPtr<TextContentType>(value));
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value);
    TextFieldModelStatic::SetFontFeature(frameNode, ParseFontFeatureSettings(*convValue));
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
    auto onDidInsert = [arkCallback = CallbackHelper(*optValue)](const InsertValueInfo& value) {
        Converter::ConvContext ctx;
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Int32>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue, &ctx)
        };
        arkCallback.InvokeSync(insertValue);
    };
    TextFieldModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
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
    auto onDidDelete = [arkCallback = CallbackHelper(*optValue)](const DeleteValueInfo& value) {
        Converter::ConvContext ctx;
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Int32>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue, &ctx)
        };
        arkCallback.InvokeSync(deleteValue);
    };
    TextFieldModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
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
    TextFieldModelStatic::SetHalfLeading(frameNode, value ? Converter::OptConvertPtr<bool>(value) : std::nullopt);
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
void SetShowCounterImpl(Ark_NativePointer node,
                        const Opt_Boolean* value,
                        const Opt_InputCounterOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto showCounter = Converter::OptConvertPtr<bool>(value);
    if (!showCounter) {
        TextFieldModelStatic::SetShowCounter(frameNode, std::nullopt);
        TextFieldModelStatic::SetCounterType(frameNode, std::nullopt);
        TextFieldModelStatic::SetShowCounterBorder(frameNode, std::nullopt);
        return;
    }
    auto optionsOpt = Converter::OptConvertPtr<Ark_InputCounterOptions>(options);
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
    TextFieldModelStatic::SetShowCounter(frameNode, showCounter);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto keyboardOptions = Converter::OptConvertPtr<Ark_KeyboardOptions>(options);
    bool supportAvoidance = keyboardOptions &&
        Converter::OptConvert<bool>(keyboardOptions.value().supportAvoidance).value_or(false);
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
} // TextAreaAttributeModifier

const GENERATED_ArkUITextAreaModifier* GetTextAreaModifier()
{
    static const GENERATED_ArkUITextAreaModifier ArkUITextAreaModifierImpl {
        TextAreaModifier::ConstructImpl,
        TextAreaInterfaceModifier::SetTextAreaOptionsImpl,
        TextAreaAttributeModifier::SetPlaceholderColorImpl,
        TextAreaAttributeModifier::SetPlaceholderFontImpl,
        TextAreaAttributeModifier::SetEnterKeyTypeImpl,
        TextAreaAttributeModifier::SetTextAlignImpl,
        TextAreaAttributeModifier::SetCaretColorImpl,
        TextAreaAttributeModifier::SetFontColorImpl,
        TextAreaAttributeModifier::SetFontSizeImpl,
        TextAreaAttributeModifier::SetFontStyleImpl,
        TextAreaAttributeModifier::SetFontWeightImpl,
        TextAreaAttributeModifier::SetFontFamilyImpl,
        TextAreaAttributeModifier::SetTextOverflowImpl,
        TextAreaAttributeModifier::SetTextIndentImpl,
        TextAreaAttributeModifier::SetCaretStyleImpl,
        TextAreaAttributeModifier::SetSelectedBackgroundColorImpl,
        TextAreaAttributeModifier::SetOnSubmitImpl,
        TextAreaAttributeModifier::SetOnChangeImpl,
        TextAreaAttributeModifier::SetOnTextSelectionChangeImpl,
        TextAreaAttributeModifier::SetOnContentScrollImpl,
        TextAreaAttributeModifier::SetOnEditChangeImpl,
        TextAreaAttributeModifier::SetOnCopyImpl,
        TextAreaAttributeModifier::SetOnCutImpl,
        TextAreaAttributeModifier::SetOnPasteImpl,
        TextAreaAttributeModifier::SetCopyOptionImpl,
        TextAreaAttributeModifier::SetEnableKeyboardOnFocusImpl,
        TextAreaAttributeModifier::SetMaxLengthImpl,
        TextAreaAttributeModifier::SetStyleImpl,
        TextAreaAttributeModifier::SetBarStateImpl,
        TextAreaAttributeModifier::SetSelectionMenuHiddenImpl,
        TextAreaAttributeModifier::SetMinFontSizeImpl,
        TextAreaAttributeModifier::SetMaxFontSizeImpl,
        TextAreaAttributeModifier::SetMinFontScaleImpl,
        TextAreaAttributeModifier::SetMaxFontScaleImpl,
        TextAreaAttributeModifier::SetHeightAdaptivePolicyImpl,
        TextAreaAttributeModifier::SetMaxLinesImpl,
        TextAreaAttributeModifier::SetWordBreakImpl,
        TextAreaAttributeModifier::SetLineBreakStrategyImpl,
        TextAreaAttributeModifier::SetDecorationImpl,
        TextAreaAttributeModifier::SetLetterSpacingImpl,
        TextAreaAttributeModifier::SetLineSpacingImpl,
        TextAreaAttributeModifier::SetLineHeightImpl,
        TextAreaAttributeModifier::SetTypeImpl,
        TextAreaAttributeModifier::SetEnableAutoFillImpl,
        TextAreaAttributeModifier::SetContentTypeImpl,
        TextAreaAttributeModifier::SetFontFeatureImpl,
        TextAreaAttributeModifier::SetOnWillInsertImpl,
        TextAreaAttributeModifier::SetOnDidInsertImpl,
        TextAreaAttributeModifier::SetOnWillDeleteImpl,
        TextAreaAttributeModifier::SetOnDidDeleteImpl,
        TextAreaAttributeModifier::SetEditMenuOptionsImpl,
        TextAreaAttributeModifier::SetEnablePreviewTextImpl,
        TextAreaAttributeModifier::SetEnableHapticFeedbackImpl,
        TextAreaAttributeModifier::SetAutoCapitalizationModeImpl,
        TextAreaAttributeModifier::SetHalfLeadingImpl,
        TextAreaAttributeModifier::SetEllipsisModeImpl,
        TextAreaAttributeModifier::SetStopBackPressImpl,
        TextAreaAttributeModifier::SetOnWillChangeImpl,
        TextAreaAttributeModifier::SetKeyboardAppearanceImpl,
        TextAreaAttributeModifier::SetInputFilterImpl,
        TextAreaAttributeModifier::SetShowCounterImpl,
        TextAreaAttributeModifier::SetCustomKeyboardImpl,
    };
    return &ArkUITextAreaModifierImpl;
}

}
