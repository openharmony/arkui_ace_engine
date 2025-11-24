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
#include "core/components/common/properties/text_style_parser.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/converter2.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "rich_editor_base_controller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<> TextStyle Convert(const Ark_RichEditorTextStyle& src);
template<> OHOS::Ace::FontStyle Convert(const Ark_FontStyle& src);
template<> Array_ShadowOptions Convert(const Ark_ShadowOptions& src)
{
    Array_ShadowOptions ret;
    ret.array = const_cast<Ark_ShadowOptions*>(&src);
    ret.length = 1;
    return ret;
}
template<>
std::vector<Shadow> Convert(const Ark_Union_ShadowOptions_Array_ShadowOptions& src)
{
    std::vector<Shadow> ret;
    auto value = Converter::OptConvert<Array_ShadowOptions>(src);
    for (int idx = 0; value && idx < value->length; idx++) {
        if (auto shadow = Converter::OptConvert<Shadow>(value->array[idx]); shadow) {
            ret.push_back(shadow.value());
        }
    }
    return ret;
}
template<>
UpdateSpanStyle Convert(const Ark_RichEditorTextStyle& src)
{
    UpdateSpanStyle ret;
    ret.updateTextColor = Converter::OptConvert<Color>(src.fontColor);
    if (auto sizeOpt = Converter::OptConvert<Dimension>(src.fontSize); sizeOpt) {
        ret.updateFontSize = sizeOpt.value();
    }
    ret.updateItalicFontStyle = Converter::OptConvert<OHOS::Ace::FontStyle>(src.fontStyle);
    ret.updateFontWeight = Converter::OptConvert<FontWeight>(src.fontWeight);
    auto fontFamilyStr = Converter::OptConvert<std::string>(src.fontFamily);
    if (fontFamilyStr && fontFamilyStr->length() > 0) {
        ret.updateFontFamily = { fontFamilyStr.value() };
    }
    if (auto decorationValue = Converter::GetOpt(src.decoration)) {
        ret.isInitDecoration = true;
        ret.updateTextDecoration = Converter::OptConvert<TextDecoration>(decorationValue->type);
        ret.updateTextDecorationColor = Converter::OptConvert<Color>(decorationValue->color);
        ret.updateTextDecorationStyle = Converter::OptConvert<TextDecorationStyle>(decorationValue->style);
    }
    ret.updateTextShadows = Converter::OptConvert<std::vector<Shadow>>(src.textShadow);

    if (auto heightOpt = Converter::OptConvert<Dimension>(src.lineHeight); heightOpt) {
        ret.updateLineHeight = heightOpt.value();
    }
    if (auto letterSpacingOpt = Converter::OptConvert<Dimension>(src.letterSpacing); letterSpacingOpt) {
        ret.updateLetterSpacing = letterSpacingOpt.value();
    }
    if (auto halfLeadingOpt = Converter::OptConvert<bool>(src.halfLeading)) {
        ret.updateHalfLeading = halfLeadingOpt.value();
    }
    if (auto fontFeatureSettingsOpt = Converter::OptConvert<std::string>(src.fontFeature)) {
        ret.updateFontFeature = ParseFontFeatureSettings(fontFeatureSettingsOpt.value());
    }
    if (auto textBackgroundStyleOpt = Converter::OptConvert<TextBackgroundStyle>(src.textBackgroundStyle)) {
        ret.updateTextBackgroundStyle = textBackgroundStyleOpt.value();
    }
    return ret;
}

void AssignArkValue(Ark_DecorationStyleInterface& dst, const UpdateSpanStyle& src,
    Converter::ConvContext *ctx)
{
    dst.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(src.updateTextDecorationColor, ctx);
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.updateTextDecorationStyle);
    dst.type = Converter::ArkValue<Opt_TextDecorationType>(src.updateTextDecoration);
}

Ark_RichEditorTextStyle CreateEmptyArkTextStyle()
{
    Ark_RichEditorTextStyle dst;
    dst.fontColor = Converter::ArkUnion<Opt_ResourceColor>(Ark_Empty());
    dst.fontSize = Converter::ArkUnion<Opt_Union_String_F64_Resource>(Ark_Empty());
    dst.fontStyle = Converter::ArkValue<Opt_FontStyle>(Ark_Empty());
    dst.fontWeight = Converter::ArkUnion<Opt_Union_I32_FontWeight_String>(Ark_Empty());
    dst.fontFamily = Converter::ArkUnion<Opt_ResourceStr>(Ark_Empty());
    dst.decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(Ark_Empty());
    dst.textShadow = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions>(Ark_Empty());
    dst.letterSpacing = Converter::ArkUnion<Opt_Union_F64_String>(Ark_Empty());
    dst.lineHeight = Converter::ArkUnion<Opt_Union_F64_String_Resource>(Ark_Empty());
    dst.fontFeature = Converter::ArkValue<Opt_String>(Ark_Empty());
    dst.halfLeading = Converter::ArkValue<Opt_Boolean>(Ark_Empty());
    dst.textBackgroundStyle = ArkValue<Opt_TextBackgroundStyle>(Ark_Empty());
    return dst;
}

void AssignArkValue(Ark_RichEditorTextStyle& dst, const UpdateSpanStyle& src, Converter::ConvContext *ctx)
{
    dst = CreateEmptyArkTextStyle();
    dst.fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(src.updateTextColor, ctx);
    dst.fontSize = Converter::ArkUnion<Opt_Union_String_F64_Resource, Ark_String>(src.updateFontSize, ctx);
    dst.fontStyle = Converter::ArkValue<Opt_FontStyle>(src.updateItalicFontStyle);
    dst.fontWeight = Converter::ArkUnion<Opt_Union_I32_FontWeight_String, Ark_FontWeight>(src.updateFontWeight);
    if (src.updateFontFamily.has_value() && !src.updateFontFamily->empty()) {
        std::string family = V2::ConvertFontFamily(src.updateFontFamily.value());
        dst.fontFamily = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(family, ctx);
    }
    if (src.isInitDecoration) {
        dst.decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(src, ctx);
    }
    dst.textShadow = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Array_ShadowOptions>(
        src.updateTextShadows, ctx);
    dst.letterSpacing = Converter::ArkUnion<Opt_Union_F64_String, Ark_String>(src.updateLetterSpacing, ctx);
    dst.lineHeight = Converter::ArkUnion<Opt_Union_F64_String_Resource, Ark_String>(src.updateLineHeight, ctx);
    if (src.updateFontFeature.has_value()) {
        dst.fontFeature =
            Converter::ArkValue<Opt_String>(UnParseFontFeatureSetting(src.updateFontFeature.value()), ctx);
    }
    dst.halfLeading = Converter::ArkValue<Opt_Boolean>(src.updateHalfLeading);
    dst.textBackgroundStyle = ArkValue<Opt_TextBackgroundStyle>(src.updateTextBackgroundStyle, ctx);
}

void AssignArkValue(Ark_PreviewText& dst, const PreviewTextInfo& src, Converter::ConvContext *ctx)
{
    dst.offset = ArkValue<Ark_Int32>(src.offset.value_or(0.0f));
    dst.value = ArkValue<Ark_String>(src.value.value_or(std::u16string()), ctx);
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
namespace RichEditorBaseControllerAccessor {
void DestroyPeerImpl(Ark_RichEditorBaseController peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_RichEditorBaseController ConstructImpl()
{
    return new RichEditorBaseControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Int32 GetCaretOffsetImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Int32>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_Int32>(Ark_Empty()));
    auto result = peer->GetCaretOffset();
    return Converter::ArkValue<Opt_Int32>(result);
}
Opt_Boolean SetCaretOffsetImpl(Ark_RichEditorBaseController peer,
                               Ark_Int32 offset)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    bool result = peer->SetCaretOffset(offset);
    return Converter::ArkValue<Opt_Boolean>(result);
}
void CloseSelectionMenuImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseSelectionMenu();
}
Opt_RichEditorTextStyle GetTypingStyleImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_RichEditorTextStyle>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_RichEditorTextStyle>(Ark_Empty()));
    auto style = peer->GetTypingStyle();
    if (style) {
        return Converter::ArkValue<Opt_RichEditorTextStyle>(style.value(), Converter::FC);
    }
    return Converter::ArkValue<Opt_RichEditorTextStyle>(Converter::CreateEmptyArkTextStyle());
}
void SetTypingStyleImpl(Ark_RichEditorBaseController peer,
                        const Ark_RichEditorTextStyle* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(value);
    auto textStyle = Converter::OptConvert<TextStyle>(*value);
    auto typingStyle = Converter::OptConvert<UpdateSpanStyle>(*value);
    peer->SetTypingStyle(typingStyle, textStyle);
}
void SetSelectionImpl(Ark_RichEditorBaseController peer,
                      const Ark_Int32* selectionStart,
                      const Ark_Int32* selectionEnd,
                      const Opt_SelectionOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(selectionStart);
    CHECK_NULL_VOID(selectionEnd);
    int32_t start = Converter::Convert<int32_t>(*selectionStart);
    int32_t end = Converter::Convert<int32_t>(*selectionEnd);
    auto optOptions = Converter::OptConvertPtr<SelectionOptions>(options);
    peer->SetSelection(start, end, optOptions, start < end);
}
Opt_Boolean IsEditingImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_Boolean>(Ark_Empty()));
    bool result = peer->IsEditing();
    return Converter::ArkValue<Opt_Boolean>(result);
}
void StopEditingImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->StopEditing();
}
Opt_LayoutManager GetLayoutManagerImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer && GetLayoutManagerAccessor(), Converter::ArkValue<Opt_LayoutManager>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_LayoutManager>(Ark_Empty()));
    auto layoutManagerPeer = GetLayoutManagerAccessor()->construct();
    CHECK_NULL_RETURN(layoutManagerPeer, Converter::ArkValue<Opt_LayoutManager>(Ark_Empty()));
    layoutManagerPeer->handler = peer->GetLayoutInfoInterface();
    return Converter::ArkValue<Opt_LayoutManager>(layoutManagerPeer);
}
Opt_PreviewText GetPreviewTextImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_PreviewText>(Ark_Empty()));
    auto controller = (peer->GetTargetController()).Upgrade();
    CHECK_NULL_RETURN(controller, Converter::ArkValue<Opt_PreviewText>(Ark_Empty()));
    auto result = peer->GetPreviewText();
    return Converter::ArkValue<Opt_PreviewText>(result, Converter::FC);
}
Opt_RectResult GetCaretRectImpl(Ark_RichEditorBaseController peer)
{
    auto invalidValue = Converter::ArkValue<Opt_RectResult>(Ark_Empty());
    CHECK_NULL_RETURN(peer, invalidValue);
    auto caretRect = peer->GetCaretRect();
    CHECK_NULL_RETURN(caretRect, invalidValue);
    CHECK_EQUAL_RETURN(caretRect->IsValid(), false, invalidValue);
    return Converter::ArkValue<Opt_RectResult>(*caretRect);
}
} // RichEditorBaseControllerAccessor
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
        RichEditorBaseControllerAccessor::DestroyPeerImpl,
        RichEditorBaseControllerAccessor::ConstructImpl,
        RichEditorBaseControllerAccessor::GetFinalizerImpl,
        RichEditorBaseControllerAccessor::GetCaretOffsetImpl,
        RichEditorBaseControllerAccessor::SetCaretOffsetImpl,
        RichEditorBaseControllerAccessor::CloseSelectionMenuImpl,
        RichEditorBaseControllerAccessor::GetTypingStyleImpl,
        RichEditorBaseControllerAccessor::SetTypingStyleImpl,
        RichEditorBaseControllerAccessor::SetSelectionImpl,
        RichEditorBaseControllerAccessor::IsEditingImpl,
        RichEditorBaseControllerAccessor::StopEditingImpl,
        RichEditorBaseControllerAccessor::GetLayoutManagerImpl,
        RichEditorBaseControllerAccessor::GetPreviewTextImpl,
        RichEditorBaseControllerAccessor::GetCaretRectImpl,
    };
    return &RichEditorBaseControllerAccessorImpl;
}

}
