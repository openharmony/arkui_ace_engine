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

#include <variant>

#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_model_static.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/paste_event_peer.h"
#include "core/interfaces/native/implementation/search_controller_accessor_peer.h"
#include "core/interfaces/native/implementation/symbol_glyph_modifier_peer.h"
#include "core/components/common/properties/text_style_parser.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SCALE_LIMIT = 1.f;

struct SearchButtonOptions {
    std::optional< OHOS::Ace::Dimension> width;
    std::optional<Color> color;
    std::optional<bool> autoDisable;
};

std::optional<std::string> ProcessBindableValue(FrameNode* frameNode, const Opt_Union_String_Bindable& value)
{
    std::optional<std::string> result;
    Converter::VisitUnion(value,
        [&result](const Ark_String& src) {
            result = Converter::OptConvert<std::string>(src);
        },
        [&result, frameNode](const Ark_Bindable_String& src) {
            result = Converter::OptConvert<std::string>(src.value);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange)](const std::u16string& content) {
                Converter::ConvContext ctx;
                auto arkContent = Converter::ArkValue<Ark_String>(content, &ctx);
                arkCallback.InvokeSync(arkContent);
            };
            SearchModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace

namespace Converter {
template<>
NG::IconOptions Convert(const Ark_IconOptions& src)
{
    NG::IconOptions options;
    auto iconColor = Converter::OptConvert<Color>(src.color);
    auto iconSize = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(src.size);
    auto iconSrc = Converter::OptConvert<Ark_Resource_Simple>(src.src);
    if (iconSrc) {
        options.UpdateSrc(iconSrc->content, iconSrc->moduleName, iconSrc->bundleName);
    }
    if (iconColor) {
        options.UpdateColor(iconColor.value());
    }
    Validator::ValidateNonNegative(iconSize);
    Validator::ValidateNonPercent(iconSize);
    if (iconSize) {
        options.UpdateSize(iconSize.value());
    }
    return options;
}
template<>
SearchButtonOptions Convert(const Ark_SearchButtonOptions& src)
{
    SearchButtonOptions buttonOptions;
    buttonOptions.color = OptConvert<Color> (src.fontColor);
    buttonOptions.width = Converter::OptConvertFromArkNumStrRes<Opt_Length, Ark_Number>(src.fontSize);
    buttonOptions.autoDisable = OptConvert<bool> (src.autoDisable);
    return buttonOptions;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SearchModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SearchModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // SearchModifier
namespace SearchInterfaceModifier {
void SetSearchOptionsImpl(Ark_NativePointer node,
                          const Opt_SearchOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto searchOptions = Converter::GetOptPtr(options);
    if (searchOptions) {
        auto value = ProcessBindableValue(frameNode, searchOptions->value);
        SearchModelNG::SetTextValue(frameNode, value);

        auto placeholder = Converter::OptConvert<std::string>(searchOptions->placeholder);
        SearchModelNG::SetPlaceholder(frameNode, placeholder);

        auto icon = Converter::OptConvert<std::string>(searchOptions->icon);
        SearchModelNG::SetIcon(frameNode, icon);

        auto controller = Converter::GetOpt(searchOptions->controller);
        CHECK_NULL_VOID(controller);
        auto peerImplPtr = *controller;
        CHECK_NULL_VOID(peerImplPtr);

        // pass the internal controller to external management
        auto internalSearchController = SearchModelNG::GetSearchController(frameNode);
        peerImplPtr->SetController(internalSearchController);
    }
}
} // SearchInterfaceModifier
namespace SearchAttributeModifier {
void SetFontColorImpl(Ark_NativePointer node,
                      const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontColor = Converter::OptConvertPtr<Color>(value);
    SearchModelStatic::SetTextColor(frameNode, fontColor);
}
void SetSearchIconImpl(Ark_NativePointer node,
                       const Opt_Union_IconOptions_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_IconOptions& src) {
            auto options = Converter::OptConvert<NG::IconOptions>(src);
            SearchModelStatic::SetSearchImageIcon(frameNode, options);
        },
        [frameNode](const Ark_SymbolGlyphModifier& src) {
            SearchModelStatic::SetSearchSymbolIcon(frameNode, src->symbolApply);
            PeerUtils::DestroyPeer(src);
        },
        [frameNode]() {
            SearchModelStatic::SetSearchDefaultIcon(frameNode);
        });
}
void SetCancelButtonImpl(Ark_NativePointer node,
                         const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    Converter::VisitUnionPtr(value,
        [frameNode](const Ark_CancelButtonOptions& src) {
            auto cancelButtonStyle = Converter::OptConvert<CancelButtonStyle>(src.style);
            auto iconOptions = Converter::OptConvert<NG::IconOptions>(src.icon);
            SearchModelStatic::SetCancelImageIcon(frameNode, iconOptions);
            SearchModelStatic::SetCancelButtonStyle(frameNode, cancelButtonStyle);
        },
        [frameNode](const Ark_CancelButtonSymbolOptions& src) {
            auto cancelButtonStyle = Converter::OptConvert<CancelButtonStyle>(src.style);
            SearchModelStatic::SetCancelButtonStyle(frameNode, cancelButtonStyle);
            auto symbolModifier = Converter::OptConvert<Ark_SymbolGlyphModifier>(src.icon);
            if (symbolModifier && *symbolModifier) {
                SearchModelStatic::SetCancelSymbolIcon(frameNode, (*symbolModifier)->symbolApply);
                PeerUtils::DestroyPeer(*symbolModifier);
            }
        },
        [frameNode]() {
            SearchModelStatic::SetCancelDefaultIcon(frameNode);
        });
}
void SetTextIndentImpl(Ark_NativePointer node,
                       const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Dimension> indentValue = std::nullopt;
    if (value->tag != INTEROP_TAG_UNDEFINED) {
        indentValue = Converter::OptConvertFromArkNumStrRes<Ark_Dimension, Ark_Number>(value->value);
    }
    SearchModelStatic::SetTextIndent(frameNode, indentValue);
}
void SetOnEditChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnEditChange(frameNode, nullptr);
        return;
    }
    auto onEditChange = [arkCallback = CallbackHelper(*optValue)](bool value) {
        arkCallback.InvokeSync(value);
    };
    SearchModelNG::SetOnEditChange(frameNode, std::move(onEditChange));
}
void SetSelectedBackgroundColorImpl(Ark_NativePointer node,
                                    const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto placeHolderColor = Converter::OptConvertPtr<Color>(value);
    SearchModelStatic::SetSelectedBackgroundColor(frameNode, placeHolderColor);
}
void SetCaretStyleImpl(Ark_NativePointer node,
                       const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto caretStyle = Converter::OptConvertPtr<Converter::CaretStyle>(value).value_or(Converter::CaretStyle{});
    SearchModelStatic::SetCaretColor(frameNode, caretStyle.color);
    Validator::ValidateNonNegative(caretStyle.width);
    Validator::ValidateNonPercent(caretStyle.width);
    SearchModelStatic::SetCaretWidth(frameNode, caretStyle.width);
}
void SetPlaceholderColorImpl(Ark_NativePointer node,
                             const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto placeHolderColor = Converter::OptConvertPtr<Color>(value);
    SearchModelStatic::SetPlaceholderColor(frameNode, placeHolderColor);
}
void SetPlaceholderFontImpl(Ark_NativePointer node,
                            const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontValue = Converter::OptConvertPtr<Font>(value);
    SearchModelStatic::SetPlaceholderFont(frameNode, fontValue);
}
void SetTextFontImpl(Ark_NativePointer node,
                     const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontValue = Converter::OptConvertPtr<Font>(value);
    SearchModelStatic::SetTextFont(frameNode, fontValue);
}
void SetEnterKeyTypeImpl(Ark_NativePointer node,
                         const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetSearchEnterKeyType(frameNode, Converter::OptConvertPtr<TextInputAction>(value));
}
void SetOnSubmitImpl(Ark_NativePointer node, const Opt_SearchSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnSubmit(frameNode, nullptr);
        return;
    }
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onSubmit = [arkCallback = CallbackHelper(*optValue), node = weakNode](
		    const std::u16string& value, NG::TextFieldCommonEvent& info) {
        PipelineContext::SetCallBackNode(node);
        Converter::ConvContext ctx;
        auto arkStringValue = Converter::ArkValue<Ark_String>(value, &ctx);
        const auto event = Converter::ArkSubmitEventSync(info);
        auto eventArkValue = Converter::ArkValue<Opt_SubmitEvent, Ark_SubmitEvent>(event.ArkValue());
        arkCallback.InvokeSync(arkStringValue, eventArkValue);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](const ChangeValueInfo& info) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(info.value, &ctx);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(info.previewText, &ctx);
        auto options = Converter::ArkValue<Opt_TextChangeOptions>(info, &ctx);
        arkCallback.InvokeSync(textArkString, textArkPrevText, options);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onChange));
}
void SetOnTextSelectionChangeImpl(Ark_NativePointer node,
                                  const Opt_OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnTextSelectionChange(frameNode, nullptr);
        return;
    }
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*optValue)](
        int32_t selectionStart, int32_t selectionEnd
    ) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Int32>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Int32>(selectionEnd);
        arkCallback.InvokeSync(arkSelectionStart, arkSelectionEnd);
    };
    SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void SetOnContentScrollImpl(Ark_NativePointer node,
                            const Opt_OnContentScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnContentScroll(frameNode, nullptr);
        return;
    }
    auto onContentScroll = [arkCallback = CallbackHelper(*optValue)](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Float64>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Float64>(totalOffsetY);
        arkCallback.InvokeSync(arkTotalOffsetX, arkTotalOffsetY);
    };
    SearchModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void SetOnCopyImpl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnCopy(frameNode, nullptr);
        return;
    }
    auto onCopy = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.InvokeSync(textArkString);
    };
    SearchModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void SetOnCutImpl(Ark_NativePointer node,
                  const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnCut(frameNode, nullptr);
        return;
    }
    auto onCut = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value) {
        Converter::ConvContext ctx;
        auto textArkString = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.InvokeSync(textArkString);
    };
    SearchModelNG::SetOnCut(frameNode, std::move(onCut));
}
void SetOnPasteImpl(Ark_NativePointer node,
                    const Opt_OnPasteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnPasteWithEvent(frameNode, nullptr);
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
    SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}
void SetCopyOptionImpl(Ark_NativePointer node,
                       const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetCopyOption(frameNode, Converter::OptConvertPtr<CopyOptions>(value));
}
void SetMaxLengthImpl(Ark_NativePointer node,
                      const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLength = Converter::OptConvertPtr<int>(value);
    Validator::ValidateNonNegative(maxLength);
    if (maxLength) {
        SearchModelNG::SetMaxLength(frameNode, *maxLength);
    } else {
        SearchModelNG::ResetMaxLength(frameNode);
    }
}
void SetTextAlignImpl(Ark_NativePointer node,
                      const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetTextAlign(frameNode, Converter::OptConvertPtr<TextAlign>(value));
}
void SetEnableKeyboardOnFocusImpl(Ark_NativePointer node,
                                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    SearchModelStatic::RequestKeyboardOnFocus(frameNode, convValue);
}
void SetSelectionMenuHiddenImpl(Ark_NativePointer node,
                                const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    SearchModelStatic::SetSelectionMenuHidden(frameNode, convValue);
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
    SearchModelStatic::SetAdaptMinFontSize(frameNode, optValue);
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
    SearchModelStatic::SetAdaptMaxFontSize(frameNode, optValue);
}
void SetMinFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    SearchModelStatic::SetMinFontScale(frameNode, convValue);
}
void SetMaxFontScaleImpl(Ark_NativePointer node,
                         const Opt_Union_F64_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<float>(value);
    SearchModelStatic::SetMaxFontScale(frameNode, convValue);
}
void SetDecorationImpl(Ark_NativePointer node,
                       const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Converter::TextDecorationOptions> options =
        Converter::OptConvertPtr<Converter::TextDecorationOptions>(value).value_or(Converter::TextDecorationOptions());
    SearchModelStatic::SetTextDecoration(frameNode, options->textDecoration);
    SearchModelStatic::SetTextDecorationColor(frameNode, options->color);
    SearchModelStatic::SetTextDecorationStyle(frameNode, options->textDecorationStyle);
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
    SearchModelStatic::SetLetterSpacing(frameNode, spacing);
}
void SetLineHeightImpl(Ark_NativePointer node,
                       const Opt_Union_F64_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvertPtr<Dimension>(value);
    Validator::ValidateNonNegative(optValue);
    SearchModelStatic::SetLineHeight(frameNode, optValue);
}
void SetTypeImpl(Ark_NativePointer node,
                 const Opt_SearchType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetType(frameNode, Converter::OptConvertPtr<TextInputType>(value));
}
void SetFontFeatureImpl(Ark_NativePointer node,
                        const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontFeatureSettings = Converter::OptConvertPtr<std::string>(value);
    if (!fontFeatureSettings) {
        FONT_FEATURES_LIST fontFeatures;
        SearchModelNG::SetFontFeature(frameNode, fontFeatures);
        return;
    }
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(*fontFeatureSettings));
}
void SetOnWillInsertImpl(Ark_NativePointer node,
                         const Opt_Callback_InsertValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnWillInsertValueEvent(frameNode, nullptr);
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
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}
void SetOnDidInsertImpl(Ark_NativePointer node,
                        const Opt_Callback_InsertValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnDidInsertValueEvent(frameNode, nullptr);
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
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}
void SetOnWillDeleteImpl(Ark_NativePointer node,
                         const Opt_Callback_DeleteValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnWillDeleteEvent(frameNode, nullptr);
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
    SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}
void SetOnDidDeleteImpl(Ark_NativePointer node,
                        const Opt_Callback_DeleteValue_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnDidDeleteEvent(frameNode, nullptr);
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
    SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}
void SetEditMenuOptionsImpl(Ark_NativePointer node,
                            const Opt_EditMenuOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelStatic::SetSelectionMenuOptions(frameNode, nullptr, nullptr);
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
    SearchModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void SetEnablePreviewTextImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    SearchModelStatic::SetEnablePreviewText(frameNode, convValue);
}
void SetEnableHapticFeedbackImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    SearchModelStatic::SetEnableHapticFeedback(frameNode, convValue);
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
    SearchModelStatic::SetHalfLeading(frameNode, value ? Converter::OptConvertPtr<bool>(value) : std::nullopt);
}
void SetStopBackPressImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetStopBackPress(frameNode, value ? Converter::OptConvertPtr<bool>(value) : std::nullopt);
}
void SetOnWillChangeImpl(Ark_NativePointer node,
                         const Opt_Callback_EditableTextChangeValue_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelNG::SetOnWillChangeEvent(frameNode, nullptr);
        return;
    }
    auto onWillChange = [callback = CallbackHelper(*optValue)](const ChangeValueInfo& value) -> bool {
        Converter::ConvContext ctx;
        Ark_EditableTextChangeValue changeValue = {
            .content = Converter::ArkValue<Ark_String>(value.value, &ctx),
            .previewText = Converter::ArkValue<Opt_PreviewText>(value.previewText, &ctx),
            .options = Converter::ArkValue<Opt_TextChangeOptions>(value, &ctx),
        };
        return callback.InvokeWithOptConvertResult<bool, Ark_Boolean, Callback_Boolean_Void>(changeValue)
            .value_or(true);
    };
    SearchModelNG::SetOnWillChangeEvent(frameNode, std::move(onWillChange));
}
void SetKeyboardAppearanceImpl(Ark_NativePointer node,
                               const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<KeyboardAppearance>(value);
    SearchModelStatic::SetKeyboardAppearance(frameNode, convValue);
}
void SetSearchButtonImpl(Ark_NativePointer node,
                         const Opt_String* value,
                         const Opt_SearchButtonOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<std::string>(value).value_or("");
    SearchModelNG::SetSearchButton(frameNode, convValue);
    auto buttonOptions = Converter::OptConvertPtr<SearchButtonOptions>(option).value_or(SearchButtonOptions());
    SearchModelStatic::SetSearchButtonFontColor(frameNode, buttonOptions.color);
    Validator::ValidateNonNegative(buttonOptions.width);
    Validator::ValidateNonPercent(buttonOptions.width);
    SearchModelStatic::SetSearchButtonFontSize(frameNode, buttonOptions.width);
    SearchModelStatic::SetSearchButtonAutoDisable(frameNode, buttonOptions.autoDisable);
}
void SetInputFilterImpl(Ark_NativePointer node,
                        const Opt_ResourceStr* value,
                        const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueString = Converter::OptConvertPtr<std::string>(value);
    std::optional<Callback_String_Void> arkErrorEvent = error ? Converter::GetOpt(*error) : std::nullopt;
    std::function<void(const std::u16string&)> errorEvent = nullptr;
    if (arkErrorEvent) {
        errorEvent = [callback = CallbackHelper(*arkErrorEvent)](const std::u16string& val) {
            auto errortArkString = Converter::ArkValue<Ark_String>(val, Converter::FC);
            callback.InvokeSync(errortArkString);
        };
    }
    SearchModelNG::SetInputFilter(frameNode, valueString.value_or(""), errorEvent);
}
void SetCustomKeyboardImpl(Ark_NativePointer node,
                           const Opt_CustomNodeBuilder* value,
                           const Opt_KeyboardOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        SearchModelStatic::SetCustomKeyboard(frameNode, nullptr, false);
        return;
    }
    auto convOptions = Converter::OptConvertPtr<KeyboardOptions>(options);
    bool supportAvoidance = convOptions.has_value() ? convOptions->supportAvoidance : false;
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto customNodeBuilder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        SearchModelStatic::SetCustomKeyboard(frameNode, std::move(customNodeBuilder), supportAvoidance);
        }, node);
}
} // SearchAttributeModifier
const GENERATED_ArkUISearchModifier* GetSearchModifier()
{
    static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
        SearchModifier::ConstructImpl,
        SearchInterfaceModifier::SetSearchOptionsImpl,
        SearchAttributeModifier::SetFontColorImpl,
        SearchAttributeModifier::SetSearchIconImpl,
        SearchAttributeModifier::SetCancelButtonImpl,
        SearchAttributeModifier::SetTextIndentImpl,
        SearchAttributeModifier::SetOnEditChangeImpl,
        SearchAttributeModifier::SetSelectedBackgroundColorImpl,
        SearchAttributeModifier::SetCaretStyleImpl,
        SearchAttributeModifier::SetPlaceholderColorImpl,
        SearchAttributeModifier::SetPlaceholderFontImpl,
        SearchAttributeModifier::SetTextFontImpl,
        SearchAttributeModifier::SetEnterKeyTypeImpl,
        SearchAttributeModifier::SetOnSubmitImpl,
        SearchAttributeModifier::SetOnChangeImpl,
        SearchAttributeModifier::SetOnTextSelectionChangeImpl,
        SearchAttributeModifier::SetOnContentScrollImpl,
        SearchAttributeModifier::SetOnCopyImpl,
        SearchAttributeModifier::SetOnCutImpl,
        SearchAttributeModifier::SetOnPasteImpl,
        SearchAttributeModifier::SetCopyOptionImpl,
        SearchAttributeModifier::SetMaxLengthImpl,
        SearchAttributeModifier::SetTextAlignImpl,
        SearchAttributeModifier::SetEnableKeyboardOnFocusImpl,
        SearchAttributeModifier::SetSelectionMenuHiddenImpl,
        SearchAttributeModifier::SetMinFontSizeImpl,
        SearchAttributeModifier::SetMaxFontSizeImpl,
        SearchAttributeModifier::SetMinFontScaleImpl,
        SearchAttributeModifier::SetMaxFontScaleImpl,
        SearchAttributeModifier::SetDecorationImpl,
        SearchAttributeModifier::SetLetterSpacingImpl,
        SearchAttributeModifier::SetLineHeightImpl,
        SearchAttributeModifier::SetTypeImpl,
        SearchAttributeModifier::SetFontFeatureImpl,
        SearchAttributeModifier::SetOnWillInsertImpl,
        SearchAttributeModifier::SetOnDidInsertImpl,
        SearchAttributeModifier::SetOnWillDeleteImpl,
        SearchAttributeModifier::SetOnDidDeleteImpl,
        SearchAttributeModifier::SetEditMenuOptionsImpl,
        SearchAttributeModifier::SetEnablePreviewTextImpl,
        SearchAttributeModifier::SetEnableHapticFeedbackImpl,
        SearchAttributeModifier::SetAutoCapitalizationModeImpl,
        SearchAttributeModifier::SetHalfLeadingImpl,
        SearchAttributeModifier::SetStopBackPressImpl,
        SearchAttributeModifier::SetOnWillChangeImpl,
        SearchAttributeModifier::SetKeyboardAppearanceImpl,
        SearchAttributeModifier::SetSearchButtonImpl,
        SearchAttributeModifier::SetInputFilterImpl,
        SearchAttributeModifier::SetCustomKeyboardImpl,
    };
    return &ArkUISearchModifierImpl;
}

}
