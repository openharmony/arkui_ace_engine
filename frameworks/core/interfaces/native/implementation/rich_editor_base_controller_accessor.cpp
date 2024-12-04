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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/rich_editor_styled_string_controller_peer_impl.h"
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
struct UpdateSpanStyle Convert(const Ark_RichEditorTextStyle& src)
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
}

struct RichEditorBaseControllerPeer : public OHOS::Ace::NG::GeneratedModifier::RichEditorBaseControllerPeerImpl {};

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RichEditorBaseControllerAccessor {
void DestroyPeerImpl(RichEditorBaseControllerPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
RichEditorBaseControllerPeer* CtorImpl()
{
    return new RichEditorBaseControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 GetCaretOffsetImpl(RichEditorBaseControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    auto result = peer->GetCaretOffset();
    return Converter::ArkValue<Ark_Int32>(result);
}
Ark_Boolean SetCaretOffsetImpl(RichEditorBaseControllerPeer* peer,
                               const Ark_Number* offset)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(offset, false);
    int32_t caretOffset = Converter::Convert<int32_t>(*offset);
    bool result = peer->SetCaretOffset(caretOffset);
    return Converter::ArkValue<Ark_Boolean>(result);
}
void CloseSelectionMenuImpl(RichEditorBaseControllerPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->CloseSelectionMenu();
}
Ark_NativePointer GetTypingStyleImpl(RichEditorBaseControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    LOGW("RichEditorBaseControllerAccessor:: GetTypingStyleImpl is not implemented");
    return nullptr;
}
void SetTypingStyleImpl(RichEditorBaseControllerPeer* peer,
                        const Ark_RichEditorTextStyle* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(value);
    auto textStyle = Converter::OptConvert<TextStyle>(*value);
    auto typingStyle = Converter::OptConvert<struct UpdateSpanStyle>(*value);
    peer->SetTypingStyle(typingStyle, textStyle);
}
void SetSelectionImpl(RichEditorBaseControllerPeer* peer,
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
Ark_Boolean IsEditingImpl(RichEditorBaseControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer, false);
    bool result = peer->IsEditing();
    return Converter::ArkValue<Ark_Boolean>(result);
}
void StopEditingImpl(RichEditorBaseControllerPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->StopEditing();
}
Ark_NativePointer GetLayoutManagerImpl(RichEditorBaseControllerPeer* peer)
{
    LOGW("RichEditorBaseControllerAccessor:: GetLayoutManagerImpl is not implemented");
    return 0;
}
Ark_NativePointer GetPreviewTextImpl(RichEditorBaseControllerPeer* peer)
{
    LOGW("RichEditorBaseControllerAccessor:: GetPreviewTextImpl is not implemented");
    return 0;
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

}
