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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/search_controller_accessor_peer.h"
#include "core/components/common/properties/text_style_parser.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SCALE_LIMIT = 1.f;

void resetNegative(std::optional<OHOS::Ace::Dimension> &dim)
{
    if (dim && dim->IsNegative()) {
        dim.value().Reset();
    }
}

void resetPercent(std::optional<OHOS::Ace::Dimension> &dim)
{
    if (dim && dim->Unit() == OHOS::Ace::DimensionUnit::PERCENT) {
        dim.reset();
    }
}
struct SearchButtonOptions {
    std::optional< OHOS::Ace::Dimension> width;
    std::optional<Color> color;
    std::optional<bool> autoDisable;
};

struct SearchOptions {
    std::optional<std::string> value;
    std::optional<std::string> placeholder;
    std::optional<std::string> icon;
    std::optional<Ark_SearchController> controller;
};

using UnionButtonOptions = std::variant<Ark_CancelButtonOptions, Ark_CancelButtonSymbolOptions>;
using UnionStringResource = std::variant<Ark_String, Ark_Resource>;
using UnionIconOptionsObject = std::variant<Ark_IconOptions, Ark_SymbolGlyphModifier>;
} // namespace

namespace Converter {
template<>
SearchOptions Convert(const Ark_SearchOptions& src)
{
    SearchOptions options;
    options.value = Converter::OptConvert<std::string>(src.value);
    options.placeholder= Converter::OptConvert<std::string>(src.placeholder);
    options.icon = Converter::OptConvert<std::string>(src.icon);
    options.controller = Converter::OptConvert<Ark_SearchController>(src.controller);
    return options;
}

template<typename T>
void AssignTo(Ark_IconOptions& dst, const Opt_IconOptions& src)
{
    dst = src.value;
}
template<>
NG::IconOptions Convert(const Ark_IconOptions& src)
{
    NG::IconOptions options;
    auto iconColor = Converter::OptConvert<Color>(src.color);
    auto iconSize = Converter::OptConvert<Dimension>(src.size);
    auto iconSrc = Converter::OptConvert<UnionStringResource>(src.src);
    if (iconSrc) {
        if (auto srcArkStr = std::get_if<Ark_String>(&iconSrc.value());
            srcArkStr != nullptr) {
            auto srcStr = Converter::Convert<std::string>(*srcArkStr);
            if (!srcStr.empty()) {
                options.UpdateSrc(srcStr, "", "");
            }
        } else if (auto srcArkStr = std::get_if<Ark_Resource>(&iconSrc.value());
            srcArkStr != nullptr) {
            auto srcStr = Converter::OptConvert<std::string>(*srcArkStr);
            auto moduleName = Converter::Convert<std::string>(srcArkStr->moduleName);
            auto bundleName = Converter::Convert<std::string>(srcArkStr->bundleName);
            if (!srcStr->empty()) {
                options.UpdateSrc(*srcStr, moduleName, bundleName);
            }
        }
    }
    if (iconColor) {
        options.UpdateColor(iconColor.value());
    }
    resetNegative(iconSize);
    resetPercent(iconSize);
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
    buttonOptions.width = OptConvert<Dimension> (src.fontSize);
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
    auto searchOptions = options ? Converter::OptConvert<SearchOptions>(*options) : std::nullopt;
    if (searchOptions) {
        SearchModelNG::SetTextValue(frameNode, searchOptions->value);
        SearchModelNG::SetPlaceholder(frameNode, searchOptions->placeholder);
        SearchModelNG::SetIcon(frameNode, searchOptions->icon);
        auto internalSearchController = SearchModelNG::GetSearchController(frameNode);
        CHECK_NULL_VOID(searchOptions->controller);
        auto peerImplPtr = reinterpret_cast<SearchControllerPeer *>(
            searchOptions->controller.value());
        CHECK_NULL_VOID(peerImplPtr);

        // pass the internal controller to external management
        peerImplPtr->SetController(internalSearchController);
    }
}
} // SearchInterfaceModifier
namespace SearchAttributeModifier {
void FontColorImpl(Ark_NativePointer node,
                   const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontColor = Converter::OptConvert<Color>(*value);
    SearchModelStatic::SetTextColor(frameNode, fontColor);
}
void SearchIconImpl(Ark_NativePointer node,
                    const Opt_Union_IconOptions_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto iconObjOpt = Converter::OptConvert<UnionIconOptionsObject>(*value);
    if (iconObjOpt) {
        auto arkIconOpt = std::get_if<Ark_IconOptions>(&iconObjOpt.value());
        if (arkIconOpt != nullptr) {
            auto options = Converter::OptConvert<NG::IconOptions>(*arkIconOpt);
            SearchModelStatic::SetSearchImageIcon(frameNode, options);
        } else {
            LOGE("ARKOALA SearchAttributeModifier.SearchIcon -> handling CustomObject not implemented.");
        }
    } else {
        SearchModelStatic::SetSearchDefaultIcon(frameNode);
    }
}
void CancelButtonImpl(Ark_NativePointer node,
                      const Opt_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto cancelOptions = Converter::OptConvert<UnionButtonOptions>(*value);
    if (cancelOptions) {
        auto options = std::get_if<Ark_CancelButtonOptions>(&cancelOptions.value());
        if (options != nullptr) {
            auto cancelButtonStyle = Converter::OptConvert<CancelButtonStyle>(options->style);
            auto iconOptions = Converter::OptConvert<NG::IconOptions>(options->icon);
            SearchModelStatic::SetCancelImageIcon(frameNode, iconOptions);
            SearchModelStatic::SetCancelButtonStyle(frameNode, cancelButtonStyle);
        } else {
            LOGE("ARKOALA SearchAttributeModifier.CancelButton -> handling OptCustomObject not implemented.");
        }
    } else {
        SearchModelStatic::SetCancelDefaultIcon(frameNode);
    }
}
void TextIndentImpl(Ark_NativePointer node,
                    const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto indentValue = Converter::OptConvert<Dimension>(*value);
    SearchModelStatic::SetTextIndent(frameNode, indentValue);
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
    auto onEditChange = [arkCallback = CallbackHelper(*optValue)](bool value) {
        arkCallback.Invoke(value);
    };
    SearchModelNG::SetOnEditChange(frameNode, std::move(onEditChange));
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto placeHolderColor = Converter::OptConvert<Color>(*value);
    SearchModelStatic::SetSelectedBackgroundColor(frameNode, placeHolderColor);
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Opt_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto caretStyle = Converter::OptConvert<Converter::CaretStyle>(*value).value_or(Converter::CaretStyle{});
    SearchModelStatic::SetCaretColor(frameNode, caretStyle.color);
    resetNegative(caretStyle.width);
    resetPercent(caretStyle.width);
    SearchModelStatic::SetCaretWidth(frameNode, caretStyle.width);
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto placeHolderColor = Converter::OptConvert<Color>(*value);
    SearchModelStatic::SetPlaceholderColor(frameNode, placeHolderColor);
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontValue = Converter::OptConvert<Font>(*value);
    SearchModelStatic::SetPlaceholderFont(frameNode, fontValue);
}
void TextFontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontValue = Converter::OptConvert<Font>(*value);
    SearchModelStatic::SetTextFont(frameNode, fontValue);
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      const Opt_EnterKeyType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetSearchEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(*value));
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Opt_Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onSubmit = [arkCallback = CallbackHelper(*optValue)](const std::u16string& value,
        NG::TextFieldCommonEvent&
    ) {
        Converter::ConvContext ctx;
        auto arkStringValue = Converter::ArkValue<Ark_String>(value, &ctx);
        arkCallback.Invoke(arkStringValue);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnSubmit1Impl(Ark_NativePointer node,
                   const Opt_SearchSubmitCallback* value)
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
void OnChangeImpl(Ark_NativePointer node,
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
        auto options = Converter::ArkValue<Opt_TextChangeOptions>();
        options.tag = INTEROP_TAG_OBJECT;
        options.value.rangeBefore = Converter::ArkValue<Ark_TextRange>(info.rangeBefore);
        options.value.rangeAfter = Converter::ArkValue<Ark_TextRange>(info.rangeAfter);
        options.value.oldContent = Converter::ArkValue<Ark_String>(info.oldContent, &ctx);
        options.value.oldPreviewText = Converter::ArkValue<Ark_PreviewText>(info.oldPreviewText, &ctx);
        arkCallback.InvokeSync(textArkString, textArkPrevText, options);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const Opt_OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        // TODO: Reset value
        return;
    }
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*optValue)](
        int32_t selectionStart, int32_t selectionEnd
    ) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        arkCallback.Invoke(arkSelectionStart, arkSelectionEnd);
    };
    SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const Opt_OnContentScrollCallback* value)
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
    SearchModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
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
    SearchModelNG::SetOnCopy(frameNode, std::move(onCopy));
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
    SearchModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const Opt_OnPasteCallback* value)
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
    SearchModelNG::SetOnPasteWithEvent(frameNode, std::move(onPaste));
}
void CopyOptionImpl(Ark_NativePointer node,
                    const Opt_CopyOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(*value));
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto maxLength = Converter::OptConvert<int>(*value);
    Validator::ValidateNonNegative(maxLength);
    if (maxLength) {
        SearchModelNG::SetMaxLength(frameNode, *maxLength);
    } else {
        SearchModelNG::ResetMaxLength(frameNode);
    }
}
void TextAlignImpl(Ark_NativePointer node,
                   const Opt_TextAlign* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(*value));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    SearchModelStatic::RequestKeyboardOnFocus(frameNode, convValue);
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    SearchModelStatic::SetSelectionMenuHidden(frameNode, convValue);
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
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelStatic::SetAdaptMinFontSize(frameNode, optValue);
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
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelStatic::SetAdaptMaxFontSize(frameNode, optValue);
}
void MinFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateLessOrEqual(convValue, SCALE_LIMIT);
    SearchModelStatic::SetMinFontScale(frameNode, convValue);
}
void MaxFontScaleImpl(Ark_NativePointer node,
                      const Opt_Union_Number_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<float>(*value);
    Validator::ValidateNonNegative(convValue);
    Validator::ValidateGreatOrEqual(convValue, SCALE_LIMIT);
    SearchModelStatic::SetMaxFontScale(frameNode, convValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Opt_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Converter::TextDecorationOptions> options =
        Converter::OptConvert<Converter::TextDecorationOptions>(*value).value_or(Converter::TextDecorationOptions());
    SearchModelStatic::SetTextDecoration(frameNode, options->textDecoration);
    SearchModelStatic::SetTextDecorationColor(frameNode, options->color);
    SearchModelStatic::SetTextDecorationStyle(frameNode, options->textDecorationStyle);
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
    resetNegative(spacing);
    resetPercent(spacing);
    SearchModelStatic::SetLetterSpacing(frameNode, spacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Opt_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    SearchModelStatic::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              const Opt_SearchType* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetType(frameNode, Converter::OptConvert<TextInputType>(*value));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto fontFeatureSettings = Converter::OptConvert<std::string>(*value);
    if (!fontFeatureSettings) {
        return;
    }
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(*fontFeatureSettings));
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
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
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
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
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
    SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
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
    SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
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
    SearchModelStatic::SetSelectionMenuOptions(frameNode, std::move(onCreateMenuCallback), std::move(onMenuItemClick));
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    SearchModelStatic::SetEnablePreviewText(frameNode, convValue);
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    SearchModelStatic::SetEnableHapticFeedback(frameNode, convValue);
}
void AutoCapitalizationModeImpl(Ark_NativePointer node,
                                const Opt_AutoCapitalizationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void HalfLeadingImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetHalfLeading(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
}
void StopBackPressImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetStopBackPress(frameNode, value ? Converter::OptConvert<bool>(*value) : std::nullopt);
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
    SearchModelNG::SetOnWillChangeEvent(frameNode, std::move(onWillChange));
}
void KeyboardAppearanceImpl(Ark_NativePointer node,
                            const Opt_KeyboardAppearance* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = value ? Converter::OptConvert<KeyboardAppearance>(*value) : std::nullopt;
    SearchModelStatic::SetKeyboardAppearance(frameNode, convValue);
}
void SearchButtonImpl(Ark_NativePointer node,
                      const Opt_String* value,
                      const Opt_SearchButtonOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<std::string> convValue = Converter::OptConvert<std::string>(*value).value_or("");
    SearchModelNG::SetSearchButton(frameNode, *convValue);
    std::optional<SearchButtonOptions> buttonOptions =
        Converter::OptConvert<SearchButtonOptions>(*option).value_or(SearchButtonOptions());
    SearchModelStatic::SetSearchButtonFontColor(frameNode, buttonOptions->color);
    resetNegative(buttonOptions->width);
    resetPercent(buttonOptions->width);
    SearchModelStatic::SetSearchButtonFontSize(frameNode, buttonOptions->width);
    SearchModelStatic::SetSearchButtonAutoDisable(frameNode, buttonOptions->autoDisable);
}
void InputFilterImpl(Ark_NativePointer node,
                     const Opt_ResourceStr* value,
                     const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto valueString = Converter::OptConvert<std::string>(*value);
    std::optional<Callback_String_Void> arkErrorEvent = error ? Converter::GetOpt(*error) : std::nullopt;
    std::function<void(const std::u16string&)> errorEvent = nullptr;
    if (arkErrorEvent) {
        errorEvent = [callback = CallbackHelper(*arkErrorEvent)](const std::u16string& val) {
            auto errortArkString = Converter::ArkValue<Ark_String>(val, Converter::FC);
            callback.Invoke(errortArkString);
        };
    }
    SearchModelNG::SetInputFilter(frameNode, valueString.value_or(""), errorEvent);
}
void CustomKeyboardImpl(Ark_NativePointer node,
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
    KeyboardOptions keyboardOptions = {.supportAvoidance = false};
    auto convOptions = options ? Converter::OptConvert<KeyboardOptions>(*options) : keyboardOptions;
    bool supportAvoidance = convOptions.has_value() ? convOptions->supportAvoidance : false;
    CallbackHelper(*optValue).BuildAsync([frameNode, supportAvoidance](const RefPtr<UINode>& uiNode) {
        auto customNodeBuilder = [uiNode]() {
            NG::ViewStackProcessor::GetInstance()->Push(uiNode);
        };
        SearchModelStatic::SetCustomKeyboard(frameNode, std::move(customNodeBuilder), supportAvoidance);
        }, node);
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        auto arkContent = Converter::ArkValue<Ark_String>(content, &ctx);
        arkCallback.Invoke(arkContent);
    };
    SearchModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
}
} // SearchAttributeModifier
const GENERATED_ArkUISearchModifier* GetSearchModifier()
{
    static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
        SearchModifier::ConstructImpl,
        SearchInterfaceModifier::SetSearchOptionsImpl,
        SearchAttributeModifier::FontColorImpl,
        SearchAttributeModifier::SearchIconImpl,
        SearchAttributeModifier::CancelButtonImpl,
        SearchAttributeModifier::TextIndentImpl,
        SearchAttributeModifier::OnEditChangeImpl,
        SearchAttributeModifier::SelectedBackgroundColorImpl,
        SearchAttributeModifier::CaretStyleImpl,
        SearchAttributeModifier::PlaceholderColorImpl,
        SearchAttributeModifier::PlaceholderFontImpl,
        SearchAttributeModifier::TextFontImpl,
        SearchAttributeModifier::EnterKeyTypeImpl,
        SearchAttributeModifier::OnSubmit0Impl,
        SearchAttributeModifier::OnSubmit1Impl,
        SearchAttributeModifier::OnChangeImpl,
        SearchAttributeModifier::OnTextSelectionChangeImpl,
        SearchAttributeModifier::OnContentScrollImpl,
        SearchAttributeModifier::OnCopyImpl,
        SearchAttributeModifier::OnCutImpl,
        SearchAttributeModifier::OnPasteImpl,
        SearchAttributeModifier::CopyOptionImpl,
        SearchAttributeModifier::MaxLengthImpl,
        SearchAttributeModifier::TextAlignImpl,
        SearchAttributeModifier::EnableKeyboardOnFocusImpl,
        SearchAttributeModifier::SelectionMenuHiddenImpl,
        SearchAttributeModifier::MinFontSizeImpl,
        SearchAttributeModifier::MaxFontSizeImpl,
        SearchAttributeModifier::MinFontScaleImpl,
        SearchAttributeModifier::MaxFontScaleImpl,
        SearchAttributeModifier::DecorationImpl,
        SearchAttributeModifier::LetterSpacingImpl,
        SearchAttributeModifier::LineHeightImpl,
        SearchAttributeModifier::TypeImpl,
        SearchAttributeModifier::FontFeatureImpl,
        SearchAttributeModifier::OnWillInsertImpl,
        SearchAttributeModifier::OnDidInsertImpl,
        SearchAttributeModifier::OnWillDeleteImpl,
        SearchAttributeModifier::OnDidDeleteImpl,
        SearchAttributeModifier::EditMenuOptionsImpl,
        SearchAttributeModifier::EnablePreviewTextImpl,
        SearchAttributeModifier::EnableHapticFeedbackImpl,
        SearchAttributeModifier::AutoCapitalizationModeImpl,
        SearchAttributeModifier::HalfLeadingImpl,
        SearchAttributeModifier::StopBackPressImpl,
        SearchAttributeModifier::OnWillChangeImpl,
        SearchAttributeModifier::KeyboardAppearanceImpl,
        SearchAttributeModifier::SearchButtonImpl,
        SearchAttributeModifier::InputFilterImpl,
        SearchAttributeModifier::CustomKeyboardImpl,
        SearchAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISearchModifierImpl;
}

}
