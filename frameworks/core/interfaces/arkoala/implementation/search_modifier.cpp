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

#include <variant>

#include "core/components_ng/pattern/search/search_model_ng.h"
#include "core/components_ng/pattern/search/search_node.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/arkoala/utility/ace_engine_types.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
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

using UnionButtonOptions = std::variant<Ark_CancelButtonOptions, Ark_CancelButtonSymbolOptions>;
using UnionStringResource = std::variant<Ark_String, Ark_Resource>;
using UnionIconOptionsObject = std::variant<Ark_IconOptions, Ark_CustomObject>;
} // namespace

namespace Converter {
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
        auto srcArkStr = std::get_if<Ark_String>(&iconSrc.value());
        if (srcArkStr != nullptr) {
            auto srcStr = Converter::Convert<std::string>(*srcArkStr);
            if (!srcStr.empty()) {
                options.UpdateSrc(srcStr, "", "");
            }
        } else {
            LOGE("ARKOALA SearchAttributeModifier.IconResource not implemented.");
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
namespace SearchInterfaceModifier {
void SetSearchOptionsImpl(Ark_NativePointer node,
                          const Opt_Type_SearchInterface_setSearchOptions_Arg0* options)
{
    LOGE("ARKOALA SearchAttributeModifier.SetSearchOptionsImpl -> Method is not implemented.");
}
} // SearchInterfaceModifier
namespace SearchAttributeModifier {
void SearchButtonImpl(Ark_NativePointer node,
                      const Ark_String* value,
                      const Opt_SearchButtonOptions* option)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto buttonText = Converter::Convert<std::string>(*value);
        SearchModelNG::SetSearchButton(frameNode, buttonText);
    }
    CHECK_NULL_VOID(option);
    auto buttonOptions = Converter::OptConvert<SearchButtonOptions>(*option);
    if (buttonOptions) {
        SearchModelNG::SetSearchButtonFontColor(frameNode, buttonOptions->color);
        resetNegative(buttonOptions->width);
        resetPercent(buttonOptions->width);
        SearchModelNG::SetSearchButtonFontSize(frameNode, buttonOptions->width);
    }
}
void FontColorImpl(Ark_NativePointer node,
                   const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontColor = Converter::OptConvert<Color>(*value);
    SearchModelNG::SetTextColor(frameNode, fontColor);
}
void SearchIconImpl(Ark_NativePointer node,
                    const Type_SearchAttribute_searchIcon_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto iconObjOpt = Converter::OptConvert<UnionIconOptionsObject>(*value);
    if (iconObjOpt) {
        auto arkIconOpt = std::get_if<Ark_IconOptions>(&iconObjOpt.value());
        if (arkIconOpt != nullptr) {
            auto options = Converter::Convert<IconOptions>(*arkIconOpt);
            SearchModelNG::SetSearchImageIcon(frameNode, options);
        } else {
            LOGE("ARKOALA SearchAttributeModifier.SearchIcon -> handling CustomObject not implemented.");
        }
    }
}
void CancelButtonImpl(Ark_NativePointer node,
                      const Type_SearchAttribute_cancelButton_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto cancelOptions = Converter::OptConvert<UnionButtonOptions>(*value);
    if (cancelOptions) {
        auto options = std::get_if<Ark_CancelButtonOptions>(&cancelOptions.value());
        if (options != nullptr) {
            auto cancelButtonStyle = Converter::OptConvert<CancelButtonStyle>(options->style);
            auto iconOptions = Converter::OptConvert<NG::IconOptions>(options->icon);
            SearchModelNG::SetCancelImageIcon(frameNode, iconOptions);
            SearchModelNG::SetCancelButtonStyle(frameNode, cancelButtonStyle);
        } else {
            LOGE("ARKOALA SearchAttributeModifier.CancelButton -> handling OptCustomObject not implemented.");
        }
    }
}
void TextIndentImpl(Ark_NativePointer node,
                    const Ark_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto indentValue = Converter::OptConvert<Dimension>(*value);
    SearchModelNG::SetTextIndent(frameNode, indentValue);
}
void InputFilterImpl(Ark_NativePointer node,
                     const ResourceStr* value,
                     const Opt_Callback* error)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    CHECK_NULL_VOID(error);
    auto valueString = Converter::OptConvert<std::string>(*value);
    auto errorEvent = [frameNode](const std::string& val) {
        auto errortArkString = Converter::ArkValue<Ark_String>(val);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->inputFilter(frameNode->GetId(), errortArkString);
    };
    SearchModelNG::SetInputFilter(frameNode, valueString.value_or(""), errorEvent);
}
void OnEditChangeImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEditEvent = [frameNode](const bool value) {
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onEditChange(frameNode->GetId(), value);
    };
    SearchModelNG::SetOnEditChange(frameNode, std::move(onEditEvent));
}
void SelectedBackgroundColorImpl(Ark_NativePointer node,
                                 const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto placeHolderColor = Converter::OptConvert<Color>(*value);
    SearchModelNG::SetSelectedBackgroundColor(frameNode, placeHolderColor);
}
void CaretStyleImpl(Ark_NativePointer node,
                    const Ark_CaretStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto caretStyle = Converter::Convert<Converter::CaretStyle>(*value);
    SearchModelNG::SetCaretColor(frameNode, caretStyle.color);
    resetNegative(caretStyle.width);
    resetPercent(caretStyle.width);
    SearchModelNG::SetCaretWidth(frameNode, caretStyle.width);
}
void PlaceholderColorImpl(Ark_NativePointer node,
                          const ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto placeHolderColor = Converter::OptConvert<Color>(*value);
    SearchModelNG::SetPlaceholderColor(frameNode, placeHolderColor);
}
void PlaceholderFontImpl(Ark_NativePointer node,
                         const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontValue = Converter::OptConvert<Font>(*value);
    SearchModelNG::SetPlaceholderFont(frameNode, fontValue);
}
void TextFontImpl(Ark_NativePointer node,
                  const Opt_Font* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto fontValue = Converter::OptConvert<Font>(*value);
    SearchModelNG::SetTextFont(frameNode, fontValue);
}
void EnterKeyTypeImpl(Ark_NativePointer node,
                      enum Ark_EnterKeyType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetSearchEnterKeyType(frameNode, Converter::OptConvert<TextInputAction>(value));
}
void OnSubmitImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSubmit = [frameNode](const std::string& value) {
        auto arkStringValue = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onSubmit(frameNode->GetId(), arkStringValue);
    };
    SearchModelNG::SetOnSubmit(frameNode, std::move(onSubmit));
}
void OnChangeImpl(Ark_NativePointer node,
                  Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onChange = [frameNode](const std::string& text, PreviewText& prevText) {
        auto textArkString = Converter::ArkValue<Ark_String>(text);
        auto textArkPrevText = Converter::ArkValue<Opt_PreviewText>(prevText);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onChange(frameNode->GetId(),
            textArkString, textArkPrevText);
    };
    SearchModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnTextSelectionChangeImpl(Ark_NativePointer node,
                               Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onTextSelectionChange = [frameNode](int32_t selectionStart, int32_t selectionEnd) {
        auto arkSelectionStart = Converter::ArkValue<Ark_Number>(selectionStart);
        auto arkSelectionEnd = Converter::ArkValue<Ark_Number>(selectionEnd);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onTextSelectionChange(frameNode->GetId(),
            arkSelectionStart, arkSelectionEnd);
    };
    SearchModelNG::SetOnTextSelectionChange(frameNode, std::move(onTextSelectionChange));
}
void OnContentScrollImpl(Ark_NativePointer node,
                         Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onContentScroll = [frameNode](float totalOffsetX, float totalOffsetY) {
        auto arkTotalOffsetX = Converter::ArkValue<Ark_Number>(totalOffsetX);
        auto arkTotalOffsetY = Converter::ArkValue<Ark_Number>(totalOffsetY);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onContentScroll(frameNode->GetId(),
            arkTotalOffsetX,
            arkTotalOffsetY);
    };
    SearchModelNG::SetOnContentScroll(frameNode, std::move(onContentScroll));
}
void OnCopyImpl(Ark_NativePointer node,
                Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCopy = [frameNode](const std::string& value) {
        auto textArkString = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onCopy(frameNode->GetId(), textArkString);
    };
    SearchModelNG::SetOnCopy(frameNode, std::move(onCopy));
}
void OnCutImpl(Ark_NativePointer node,
               Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onCut = [frameNode](const std::string& value) {
        auto textArkString = Converter::ArkValue<Ark_String>(value);
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onCut(frameNode->GetId(), textArkString);
    };
    SearchModelNG::SetOnCut(frameNode, std::move(onCut));
}
void OnPasteImpl(Ark_NativePointer node,
                 Ark_Function callback)
{
    LOGE("ARKOALA SearchAttributeModifier.OnPasteImpl -> Method is not implemented.");
}
void CopyOptionImpl(Ark_NativePointer node,
                    enum Ark_CopyOptions value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetCopyOption(frameNode, Converter::OptConvert<CopyOptions>(value));
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
                   enum Ark_TextAlign value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetTextAlign(frameNode, Converter::OptConvert<TextAlign>(value));
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
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto isHidden = Converter::Convert<bool>(value);
    SearchModelNG::SetSelectionMenuHidden(frameNode, isHidden);
}
void MinFontSizeImpl(Ark_NativePointer node,
                     const Type_SearchAttribute_minFontSize_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelNG::SetAdaptMinFontSize(frameNode, optValue);
}
void MaxFontSizeImpl(Ark_NativePointer node,
                     const Type_SearchAttribute_maxFontSize_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    resetPercent(optValue);
    SearchModelNG::SetAdaptMaxFontSize(frameNode, optValue);
}
void CustomKeyboardImpl(Ark_NativePointer node,
                        const CustomBuilder* value,
                        const Opt_KeyboardOptions* options)
{
    LOGE("ARKOALA SearchAttributeModifier.CustomKeyboardImpl -> Method is not implemented.");
}
void DecorationImpl(Ark_NativePointer node,
                    const Ark_TextDecorationOptions* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto options = Converter::Convert<Converter::TextDecorationOptions>(*value);
    SearchModelNG::SetTextDecoration(frameNode, options.textDecoration);
    SearchModelNG::SetTextDecorationColor(frameNode, options.color);
    SearchModelNG::SetTextDecorationStyle(frameNode, options.textDecorationStyle);
}
void LetterSpacingImpl(Ark_NativePointer node,
                       const Type_SearchAttribute_letterSpacing_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto spacing = Converter::OptConvert<Dimension>(*value);
    resetNegative(spacing);
    resetPercent(spacing);
    SearchModelNG::SetLetterSpacing(frameNode, spacing);
}
void LineHeightImpl(Ark_NativePointer node,
                    const Type_SearchAttribute_lineHeight_Arg0* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    resetNegative(optValue);
    SearchModelNG::SetLineHeight(frameNode, optValue);
}
void TypeImpl(Ark_NativePointer node,
              enum Ark_SearchType value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetType(frameNode, Converter::OptConvert<TextInputType>(value));
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
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillInsert = [frameNode](const InsertValueInfo& value) -> bool {
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue)
        };
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onWillInsert(frameNode->GetId(), insertValue);
        LOGE("ARKOALA SearchAttributeModifier.OnWillInsert -> Method work incorrect.");
        return true;
    };
    SearchModelNG::SetOnWillInsertValueEvent(frameNode, std::move(onWillInsert));
}
void OnDidInsertImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidInsert = [frameNode](const InsertValueInfo& value) {
        Ark_InsertValue insertValue = {
            .insertOffset = Converter::ArkValue<Ark_Number>(value.insertOffset),
            .insertValue = Converter::ArkValue<Ark_String>(value.insertValue)
        };
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onWillInsert(frameNode->GetId(), insertValue);
    };
    SearchModelNG::SetOnDidInsertValueEvent(frameNode, std::move(onDidInsert));
}
void OnWillDeleteImpl(Ark_NativePointer node,
                      Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onWillDelete = [frameNode](const DeleteValueInfo& value) -> bool {
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue)
        };
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onWillDelete(frameNode->GetId(), deleteValue);
        LOGE("ARKOALA SearchAttributeModifier.OnWillDelete -> Method work incorrect.");
        return true;
    };
    SearchModelNG::SetOnWillDeleteEvent(frameNode, std::move(onWillDelete));
}
void OnDidDeleteImpl(Ark_NativePointer node,
                     Ark_Function callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDidDelete = [frameNode](const DeleteValueInfo& value) {
        Ark_DeleteValue deleteValue = {
            .deleteOffset = Converter::ArkValue<Ark_Number>(value.deleteOffset),
            .direction = Converter::ArkValue<Ark_TextDeleteDirection>(value.direction),
            .deleteValue = Converter::ArkValue<Ark_String>(value.deleteValue)
        };
        GetFullAPI()->getEventsAPI()->getSearchEventsReceiver()->onDidDelete(frameNode->GetId(), deleteValue);
    };
    SearchModelNG::SetOnDidDeleteEvent(frameNode, std::move(onDidDelete));
}
void EditMenuOptionsImpl(Ark_NativePointer node,
                         const Ark_Materialized* editMenu)
{
    LOGE("ARKOALA SearchAttributeModifier.EditMenuOptionsImpl -> Method is not implemented.");
}
void EnablePreviewTextImpl(Ark_NativePointer node,
                           Ark_Boolean enable)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    SearchModelNG::SetEnablePreviewText(frameNode, Converter::Convert<bool>(enable));
}
void EnableHapticFeedbackImpl(Ark_NativePointer node,
                              Ark_Boolean isEnabled)
{
}
} // SearchAttributeModifier
const GENERATED_ArkUISearchModifier* GetSearchModifier()
{
    static const GENERATED_ArkUISearchModifier ArkUISearchModifierImpl {
        SearchInterfaceModifier::SetSearchOptionsImpl,
        SearchAttributeModifier::SearchButtonImpl,
        SearchAttributeModifier::FontColorImpl,
        SearchAttributeModifier::SearchIconImpl,
        SearchAttributeModifier::CancelButtonImpl,
        SearchAttributeModifier::TextIndentImpl,
        SearchAttributeModifier::InputFilterImpl,
        SearchAttributeModifier::OnEditChangeImpl,
        SearchAttributeModifier::SelectedBackgroundColorImpl,
        SearchAttributeModifier::CaretStyleImpl,
        SearchAttributeModifier::PlaceholderColorImpl,
        SearchAttributeModifier::PlaceholderFontImpl,
        SearchAttributeModifier::TextFontImpl,
        SearchAttributeModifier::EnterKeyTypeImpl,
        SearchAttributeModifier::OnSubmitImpl,
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
        SearchAttributeModifier::CustomKeyboardImpl,
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
    };
    return &ArkUISearchModifierImpl;
}

}
