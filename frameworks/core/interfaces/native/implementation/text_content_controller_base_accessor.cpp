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

#include "core/interfaces/native/implementation/text_content_controller_base_peer.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
template<> void AssignCast(std::optional<int32_t>& dst, const Ark_TextContentControllerOptions& src)
{
    dst = Converter::OptConvert<int32_t>(src.offset);
}

void AssignArkValue(Ark_CaretOffset& dst, const NG::OffsetF& src)
{
    dst.x = Converter::ArkValue<Ark_Int32>(src.GetX());
    dst.y = Converter::ArkValue<Ark_Int32>(src.GetY());
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextContentControllerBaseAccessor {
void DestroyPeerImpl(Ark_TextContentControllerBase peer)
{
    delete peer;
}
Ark_TextContentControllerBase ConstructImpl()
{
    return new TextContentControllerBasePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_CaretOffset GetCaretOffsetImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_RETURN(peer && peer->controller_, Converter::ArkValue<Opt_CaretOffset>(Ark_Empty()));
    auto offset = peer->controller_->GetCaretPosition();
    Opt_CaretOffset caretOffset = Converter::ArkValue<Opt_CaretOffset>(offset);
    caretOffset.value.index = Converter::ArkValue<Ark_Int32>(peer->controller_->GetCaretIndex());
    return caretOffset;
}
Opt_RectResult GetTextContentRectImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_RETURN(peer && peer->controller_, Converter::ArkValue<Opt_RectResult>(Ark_Empty()));
    auto rect = peer->controller_->GetTextContentRect();
    return Converter::ArkValue<Opt_RectResult>(rect);
}
Opt_Int32 GetTextContentLineCountImpl(Ark_TextContentControllerBase peer)
{
    const auto errValue = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    CHECK_NULL_RETURN(peer && peer->controller_, errValue);
    return Converter::ArkValue<Opt_Int32>(peer->controller_->GetTextContentLinesNum());
}
Opt_Int32 AddTextImpl(Ark_TextContentControllerBase peer,
                      const Ark_String* text,
                      const Opt_TextContentControllerOptions* textOperationOptions)
{
    const auto errValue = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    CHECK_NULL_RETURN(peer && peer->controller_ && text, errValue);
    auto textConv = Converter::Convert<std::u16string>(*text);
    auto optionsConv = Converter::OptConvertPtr<int32_t>(textOperationOptions);
    const auto defaultOffset = -1;
    auto retValue = peer->controller_->AddText(textConv, optionsConv.value_or(defaultOffset));
    return Converter::ArkValue<Opt_Int32>(retValue);
}
void DeleteTextImpl(Ark_TextContentControllerBase peer,
                    const Opt_TextRange* range)
{
    CHECK_NULL_VOID(peer && peer->controller_);
    auto rangeConv = Converter::OptConvertPtr<TextRange>(range);
    if (rangeConv.has_value()) {
        auto startIndex = rangeConv.value().start;
        auto endIndex = rangeConv.value().end;
        peer->controller_->DeleteText(
            startIndex < 0 ? 0 : startIndex, endIndex < 0 ? -1 : endIndex);
    } else {
        peer->controller_->DeleteText(-1, -1);
    }
}
Opt_TextRange GetSelectionImpl(Ark_TextContentControllerBase peer)
{
    const auto errValue = Converter::ArkValue<Opt_TextRange>(TextRange{});
    CHECK_NULL_RETURN(peer && peer->controller_, errValue);
    auto retValue = peer->controller_->GetSelection();
    return Converter::ArkValue<Opt_TextRange>(retValue);
}
void ClearPreviewTextImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_VOID(peer && peer->controller_);
    peer->controller_->ClearPreviewText();
}
Opt_String GetTextImpl(Ark_TextContentControllerBase peer,
                       const Opt_TextRange* range)
{
    std::u16string result = u"";
    CHECK_NULL_RETURN(peer && peer->controller_ && range, Converter::ArkValue<Opt_String>(Ark_Empty()));
    auto rangeConv = Converter::OptConvertPtr<TextRange>(range);
    std::u16string content = peer->controller_->GetText();
    int32_t startIndex = 0;
    int32_t endIndex = content.length();
    if (rangeConv) {
        startIndex = rangeConv->start;
        startIndex = startIndex < 0 ? 0 : startIndex;
        startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(content.length()));
        endIndex = rangeConv->end;
        endIndex = endIndex < 0 ? static_cast<int32_t>(content.length()) : endIndex;
        endIndex = std::clamp(endIndex, 0, static_cast<int32_t>(content.length()));
        if (startIndex > endIndex) {
            std::swap(startIndex, endIndex);
        }
    }
    result = content.substr(startIndex, endIndex - startIndex);
    return Converter::ArkValue<Opt_String>(result, Converter::FC);
}
} // TextContentControllerBaseAccessor
const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor()
{
    static const GENERATED_ArkUITextContentControllerBaseAccessor TextContentControllerBaseAccessorImpl {
        TextContentControllerBaseAccessor::DestroyPeerImpl,
        TextContentControllerBaseAccessor::ConstructImpl,
        TextContentControllerBaseAccessor::GetFinalizerImpl,
        TextContentControllerBaseAccessor::GetCaretOffsetImpl,
        TextContentControllerBaseAccessor::GetTextContentRectImpl,
        TextContentControllerBaseAccessor::GetTextContentLineCountImpl,
        TextContentControllerBaseAccessor::AddTextImpl,
        TextContentControllerBaseAccessor::DeleteTextImpl,
        TextContentControllerBaseAccessor::GetSelectionImpl,
        TextContentControllerBaseAccessor::ClearPreviewTextImpl,
        TextContentControllerBaseAccessor::GetTextImpl,
    };
    return &TextContentControllerBaseAccessorImpl;
}

}
