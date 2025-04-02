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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextContentControllerBaseAccessor {
void DestroyPeerImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_VOID(peer);
    peer->controller_ = nullptr;
    delete peer;
}
Ark_TextContentControllerBase CtorImpl()
{
    return new TextContentControllerBasePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_CaretOffset GetCaretOffsetImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_RETURN(peer && peer->controller_, {});
    auto offset = peer->controller_->GetCaretPosition();
    return Converter::ArkValue<Ark_CaretOffset>(offset);
}
Ark_RectResult GetTextContentRectImpl(Ark_TextContentControllerBase peer)
{
    CHECK_NULL_RETURN(peer && peer->controller_, {});
    auto rect = peer->controller_->GetTextContentRect();
    return Converter::ArkValue<Ark_RectResult>(rect);
}
Ark_Number GetTextContentLineCountImpl(Ark_TextContentControllerBase peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->controller_, errValue);
    return Converter::ArkValue<Ark_Number>(peer->controller_->GetTextContentLinesNum());
}
} // TextContentControllerBaseAccessor
const GENERATED_ArkUITextContentControllerBaseAccessor* GetTextContentControllerBaseAccessor()
{
    static const GENERATED_ArkUITextContentControllerBaseAccessor TextContentControllerBaseAccessorImpl {
        TextContentControllerBaseAccessor::DestroyPeerImpl,
        TextContentControllerBaseAccessor::CtorImpl,
        TextContentControllerBaseAccessor::GetFinalizerImpl,
        TextContentControllerBaseAccessor::GetCaretOffsetImpl,
        TextContentControllerBaseAccessor::GetTextContentRectImpl,
        TextContentControllerBaseAccessor::GetTextContentLineCountImpl,
    };
    return &TextContentControllerBaseAccessorImpl;
}

struct TextContentControllerBasePeer {
    virtual ~TextContentControllerBasePeer() = default;
};
}
