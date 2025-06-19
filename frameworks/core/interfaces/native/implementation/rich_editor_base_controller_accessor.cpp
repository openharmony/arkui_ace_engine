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
        ret.updateFontFamily->push_back(fontFamilyStr.value());
    }
    ret.updateTextDecoration = Converter::OptConvert<TextDecoration>(src.decoration.value.type);
    ret.updateTextDecorationColor = Converter::OptConvert<Color>(src.decoration.value.color);
    ret.updateTextDecorationStyle = Converter::OptConvert<TextDecorationStyle>(src.decoration.value.style);
    ret.updateTextShadows = Converter::OptConvert<std::vector<Shadow>>(src.textShadow);

    if (auto heightOpt = Converter::OptConvert<Dimension>(src.lineHeight); heightOpt) {
        ret.updateLineHeight = heightOpt.value();
    }
    if (auto letterSpacingOpt = Converter::OptConvert<Dimension>(src.letterSpacing); letterSpacingOpt) {
        ret.updateLetterSpacing = letterSpacingOpt.value();
    }
    return ret;
}

void AssignArkValue(Ark_DecorationStyleInterface& dst, const UpdateSpanStyle& src,
    Converter::ConvContext *ctx)
{
    auto color = src.updateTextDecorationColor.value_or(Color::BLACK);
    auto strColor = Converter::ArkValue<Ark_String>(color.ToString(), ctx);
    dst.color = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(strColor);
    auto style = src.updateTextDecorationStyle.value_or(static_cast<TextDecorationStyle>(-1));
    dst.style = Converter::ArkValue<Opt_TextDecorationStyle>(src.updateTextDecorationStyle);
    dst.type = Converter::ArkValue<Ark_TextDecorationType>(src.updateTextDecoration.value_or(TextDecoration::NONE));
}

void AssignArkValue(Ark_RichEditorTextStyle& dst, const UpdateSpanStyle& src, Converter::ConvContext *ctx)
{
    auto color = src.updateTextColor.value_or(Color::BLACK);
    auto strColor = Converter::ArkValue<Ark_String>(color.ToString(), ctx);
    dst.fontColor = Converter::ArkUnion<Opt_ResourceColor, Ark_String>(strColor);
    dst.fontSize = Converter::ArkUnion<Opt_Union_Length_Number,
        Ark_Length>(src.updateFontSize.value_or(CalcDimension()));
    dst.fontStyle = Converter::ArkValue<Opt_FontStyle>(src.updateItalicFontStyle);
    auto arkFontWeight = Converter::ArkValue<Ark_FontWeight>(src.updateFontWeight.value_or(FontWeight::NORMAL));
    dst.fontWeight = Converter::ArkUnion<Opt_Union_Number_FontWeight_String,
        Ark_FontWeight>(arkFontWeight);
    Ark_String fontFamilies = {};
    if (src.updateFontFamily && !src.updateFontFamily->empty()) {
        auto families = src.updateFontFamily.value();
        fontFamilies = Converter::ArkValue<Ark_String>(families[0], ctx);
    }
    dst.fontFamily = Converter::ArkUnion<Opt_ResourceStr, Ark_String>(fontFamilies);
    dst.decoration = Converter::ArkValue<Opt_DecorationStyleInterface>(src, ctx);
    auto shadowVec = src.updateTextShadows.value_or(std::vector<Shadow>());
    auto array = Converter::ArkValue<Array_ShadowOptions>(shadowVec, ctx);
    dst.textShadow = Converter::ArkUnion<Opt_Union_ShadowOptions_Array_ShadowOptions, Array_ShadowOptions>(array);
    auto str = Converter::ArkValue<Ark_String>(src.updateLetterSpacing.value_or(CalcDimension()).ToString(), ctx);
    dst.letterSpacing = Converter::ArkUnion<Opt_Union_Number_String, Ark_String>(str);
    str = Converter::ArkValue<Ark_String>(src.updateLineHeight.value_or(CalcDimension()).ToString(), ctx);
    dst.lineHeight = Converter::ArkUnion<Opt_Union_Number_String_Resource, Ark_String>(str);
    dst.fontFeature = Converter::ArkValue<Opt_String>(src.updateFontFeature);
}

void AssignArkValue(Ark_PreviewText& dst, const PreviewTextInfo& src, Converter::ConvContext *ctx)
{
    dst.offset = ArkValue<Ark_Number>(src.offset.value_or(0.0f));
    // dst.value = ArkValue<Ark_String>(src.value.value_or(std::string()), ctx);
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
Ark_RichEditorBaseController CtorImpl()
{
    return new RichEditorBaseControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetCaretOffsetImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Number>(0));
    auto result = peer->GetCaretOffset();
    return Converter::ArkValue<Ark_Number>(result);
}
Ark_Boolean SetCaretOffsetImpl(Ark_RichEditorBaseController peer,
                               const Ark_Number* offset)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(offset, false);
    int32_t caretOffset = Converter::Convert<int32_t>(*offset);
    bool result = peer->SetCaretOffset(caretOffset);
    return Converter::ArkValue<Ark_Boolean>(result);
}
void CloseSelectionMenuImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseSelectionMenu();
}
Ark_RichEditorTextStyle GetTypingStyleImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto style = peer->GetTypingStyle();
    if (style) {
        return Converter::ArkValue<Ark_RichEditorTextStyle>(style.value(), Converter::FC);
    }
    return {};
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
                      const Ark_Number* selectionStart,
                      const Ark_Number* selectionEnd,
                      const Opt_SelectionOptions* options)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(selectionStart);
    CHECK_NULL_VOID(selectionEnd);
    CHECK_NULL_VOID(options);
    int32_t start = Converter::Convert<int32_t>(*selectionStart);
    int32_t end = Converter::Convert<int32_t>(*selectionEnd);
    auto optOptions = Converter::OptConvert<SelectionOptions>(*options);
    peer->SetSelection(start, end, optOptions, start < end);
}
Ark_Boolean IsEditingImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, false);
    bool result = peer->IsEditing();
    return Converter::ArkValue<Ark_Boolean>(result);
}
void StopEditingImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_VOID(peer);
    peer->StopEditing();
}
Ark_LayoutManager GetLayoutManagerImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer && GetLayoutManagerAccessor(), {});
    auto layoutManagerPeer = GetLayoutManagerAccessor()->ctor();
    CHECK_NULL_RETURN(layoutManagerPeer, {});
    layoutManagerPeer->handler = peer->GetLayoutInfoInterface();
    return layoutManagerPeer;
}
Ark_PreviewText GetPreviewTextImpl(Ark_RichEditorBaseController peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto result = peer->GetPreviewText();
    return Converter::ArkValue<Ark_PreviewText>(result, Converter::FC);
}
} // RichEditorBaseControllerAccessor
const GENERATED_ArkUIRichEditorBaseControllerAccessor* GetRichEditorBaseControllerAccessor()
{
    static const GENERATED_ArkUIRichEditorBaseControllerAccessor RichEditorBaseControllerAccessorImpl {
        RichEditorBaseControllerAccessor::DestroyPeerImpl,
        RichEditorBaseControllerAccessor::CtorImpl,
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
    };
    return &RichEditorBaseControllerAccessorImpl;
}

struct RichEditorBaseControllerPeer {
    virtual ~RichEditorBaseControllerPeer() = default;
};
}
