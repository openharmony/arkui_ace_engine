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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/generated/interface/node_api.h"
#include "core/interfaces/native/implementation/search_controller_accessor_peer.h"
#include "core/components/common/properties/text_style_parser.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::NG {
namespace {
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
                   const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontColor = Converter::OptConvert<Color>(*value);
    SearchModelStatic::SetTextColor(frameNode, fontColor);
}
void SearchIconImpl(Ark_NativePointer node,
                    const Ark_Union_IconOptions_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto iconObjOpt = Converter::OptConvert<UnionIconOptionsObject>(*value);
    if (iconObjOpt) {
        auto arkIconOpt = std::get_if<Ark_IconOptions>(&iconObjOpt.value());
        if (arkIconOpt != nullptr) {
            auto options = Converter::OptConvert<NG::IconOptions>(*arkIconOpt);
            SearchModelStatic::SetSearchImageIcon(frameNode, options);
        } else {
            LOGE("ARKOALA SearchAttributeModifier.SearchIcon -> handling CustomObject not implemented.");
        }
    }
}
void CancelButtonImpl(Ark_NativePointer node,
                      const Ark_Union_CancelButtonOptions_CancelButtonSymbolOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
    }
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto indentValue = Converter::OptConvert<Dimension>(*value);
    SearchModelStatic::SetTextIndent(frameNode, indentValue);
}
void OnEditChangeImpl(Ark_NativePointer node,
                      const Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onEditChange = [arkCallback = CallbackHelper(*value)](bool value) {
        arkCallback.Invoke(value);
    };
    SearchModelNG::SetOnEditChange(frameNode, std::move(onEditChange));
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto placeHolderColor = Converter::OptConvert<Color>(*value);
    SearchModelStatic::SetSelectedBackgroundColor(frameNode, placeHolderColor);
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto caretStyle = Converter::Convert<Converter::CaretStyle>(*value);
    SearchModelStatic::SetCaretColor(frameNode, caretStyle.color);
    resetNegative(caretStyle.width);
    resetPercent(caretStyle.width);
    SearchModelStatic::SetCaretWidth(frameNode, caretStyle.width);
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const Ark_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
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
                      Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetSearchEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(value));
}
void OnSubmit0Impl(Ark_NativePointer node,
                   const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSubmit = [arkCallback = CallbackHelper(*value)](const std::u16string& value,
        NG::TextFieldCommonEvent&
    ) {
        Converter::ConvContext ctx;
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto arkStringValue = Converter::ArkValue<Ark_String>(u8Value, &ctx);
        arkCallback.Invoke(arkStringValue);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnSubmit1Impl(Ark_NativePointer node,
                   const SearchSubmitCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto weakNode = AceType::WeakClaim(frameNode);
    auto onSubmit = [arkCallback = CallbackHelper(*value), node = weakNode](
            const std::u16string& value, NG::TextFieldCommonEvent& info) {
        PipelineContext::SetCallBackNode(node);
        Converter::ConvContext ctx;
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto arkStringValue = Converter::ArkValue<Ark_String>(u8Value, &ctx);
        const auto event = Converter::ArkSubmitEventSync(info);
        auto eventArkValue = Converter::ArkValue<Opt_SubmitEvent, Ark_SubmitEvent>(event.ArkValue());
        arkCallback.InvokeSync(arkStringValue, eventArkValue);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnChangeImpl(Ark_NativePointer node,
                  const EditableTextOnChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](const ChangeValueInfo& changeValueInfo) {
        Converter::ConvContext ctx;
        const std::string u8Text = UtfUtils::Str16DebugToStr8(changeValueInfo.value);
        PreviewText prevText = changeValueInfo.previewText;
        auto textArkString = Converter::ArkValue<Ark_String>(u8Text, &ctx);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(prevText, &ctx);
        arkCallback.Invoke(textArkString, textArkPrevText);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               const OnTextSelectionChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onTextSelectionChange = [arkCallback = CallbackHelper(*value)](
        int32_t selectionStart, int32_t selectionEnd
    ) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        arkCallback.Invoke(arkSelectionStart, arkSelectionEnd);
    };
    SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         const OnContentScrollCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onContentScroll = [arkCallback = CallbackHelper(*value)](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Number>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Number>(totalOffsetY);
        arkCallback.Invoke(arkTotalOffsetX, arkTotalOffsetY);
    };
    SearchModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void OnCopyImpl(Ark_NativePointer node,
                const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCopy = [arkCallback = CallbackHelper(*value)](const std::u16string& value) {
        Converter::ConvContext ctx;
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value, &ctx);
        arkCallback.Invoke(textArkString);
    };
    SearchModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               const Callback_String_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onCut = [arkCallback = CallbackHelper(*value)](const std::u16string& value) {
        Converter::ConvContext ctx;
        const std::string u8Value = UtfUtils::Str16DebugToStr8(value);
        auto textArkString = Converter::ArkValue<Ark_String>(u8Value, &ctx);
        arkCallback.Invoke(textArkString);
    };
    SearchModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 const OnPasteCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPaste = [arkCallback = CallbackHelper(*value)](const std::u16string& content,
        NG::TextCommonEvent& event) -> void {
        Converter::ConvContext ctx;
        const std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        auto arkContent = Converter::ArkValue<Ark_String>(u8Content, &ctx);
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
                    Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(value));
}
void MaxLengthImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto maxLength = Converter::Convert<int>(*value);
    if (GreatOrEqual(maxLength, 0)) {
        SearchModelNG::SetMaxLength(frameNode, maxLength);
    } else {
        SearchModelNG::ResetMaxLength(frameNode);
    }
}
void TextAlignImpl(Ark_NativePointer node,
                   Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(value));
}
void EnableKeyboardOnFocusImpl(Ark_NativePointer node,
                               Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::RequestKeyboardOnFocus(frameNode, Converter::Convert<bool>(value));
}
void SelectionMenuHiddenImpl(Ark_NativePointer node,
                             Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHidden = Converter::Convert<bool>(value);
    SearchModelNG::SetSelectionMenuHidden(frameNode, isHidden);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelStatic::SetAdaptMinFontSize(frameNode, optValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelStatic::SetAdaptMaxFontSize(frameNode, optValue);
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_TextDecorationOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::TextDecorationOptions>(*value);
    SearchModelStatic::SetTextDecoration(frameNode, options.textDecoration);
    SearchModelStatic::SetTextDecorationColor(frameNode, options.color);
    SearchModelStatic::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    resetNegative(spacing);
    resetPercent(spacing);
    SearchModelStatic::SetLetterSpacing(frameNode, spacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Ark_Union_Number_String_Resource* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    SearchModelStatic::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              Ark_SearchType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelStatic::SetType(frameNode, Converter::OptConvert<TextInputType>(value));
}
void FontFeatureImpl(Ark_NativePointer node,
                     const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontFeatureSettings = Converter::Convert<std::string>(*value);
    SearchModelNG::SetFontFeature(frameNode, ParseFontFeatureSettings(fontFeatureSettings));
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
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
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
            .insertValue = Converter::ArkValue<Ark_String>(u8InsertValue)
        };
        arkCallback.Invoke(insertValue);
    };
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
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
    SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
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
            .deleteValue = Converter::ArkValue<Ark_String>(u8DeleteValue)
        };
        arkCallback.Invoke(deleteValue);
    };
    SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         Ark_EditMenuOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LOGE("ARKOALA SearchAttributeModifier.EditMenuOptionsImpl -> Method is not implemented.");
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, Converter::Convert<bool>(value));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnableHapticFeedback(frameNode, Converter::Convert<bool>(value));
}
void SearchButtonImpl(Ark_NativePointer node,
                      const Ark_String* value,
                      const Opt_SearchButtonOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto buttonText = Converter::Convert<std::string>(*value);
        SearchModelNG::SetSearchButton(frameNode, buttonText);
    }
    CHECK_NULL_VOID(option);
    auto buttonOptions = Converter::OptConvert<SearchButtonOptions>(*option);
    if (buttonOptions) {
        SearchModelStatic::SetSearchButtonFontColor(frameNode, buttonOptions->color);
        resetNegative(buttonOptions->width);
        resetPercent(buttonOptions->width);
        SearchModelStatic::SetSearchButtonFontSize(frameNode, buttonOptions->width);
    }
}
void InputFilterImpl(Ark_NativePointer node,
                     const Ark_ResourceStr* value,
                     const Opt_Callback_String_Void* error)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(error);
    auto valueString = Converter::OptConvert<std::string>(*value);
    auto errorEvent = [frameNode](const std::u16string& val) {
        std::string u8Val = UtfUtils::Str16DebugToStr8(val);
        auto errortArkString = Converter::ArkValue<Ark_String>(u8Val);
    };
    SearchModelNG::SetInputFilter(frameNode, valueString.value_or(""), errorEvent);
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
    auto customNodeBuilder = [callback = CallbackHelper(*value), node]() {
        auto builderNode = callback.BuildSync(node);
        NG::ViewStackProcessor::GetInstance()->Push(builderNode);
    };
    bool supportAvoidance = convOptions.has_value() ? convOptions->supportAvoidance : false;
    SearchModelStatic::SetCustomKeyboard(frameNode, std::move(customNodeBuilder), supportAvoidance);
}
void _onChangeEvent_valueImpl(Ark_NativePointer node,
                              const Callback_String_Void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(callback);
    auto onEvent = [arkCallback = CallbackHelper(*callback)](const std::u16string& content) {
        Converter::ConvContext ctx;
        std::string u8Content = UtfUtils::Str16DebugToStr8(content);
        auto arkContent = Converter::ArkValue<Ark_String>(u8Content, &ctx);
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
        SearchAttributeModifier::SearchButtonImpl,
        SearchAttributeModifier::InputFilterImpl,
        SearchAttributeModifier::CustomKeyboardImpl,
        SearchAttributeModifier::_onChangeEvent_valueImpl,
    };
    return &ArkUISearchModifierImpl;
}

}
