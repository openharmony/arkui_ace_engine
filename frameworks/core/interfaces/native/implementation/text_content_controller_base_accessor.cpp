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

#include "core/interfaces/native/implementation/text_content_controller_base_peer.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextContentControllerBaseAccessor {
void DestroyPeerImpl(TextContentControllerBasePeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
TextContentControllerBasePeer* CtorImpl()
{
    return new TextContentControllerBasePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_NativePointer GetCaretOffsetImpl(TextContentControllerBasePeer* peer)
{
    // fix a return value
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetCaretPosition();
    return 0;
}
Ark_NativePointer GetTextContentRectImpl(TextContentControllerBasePeer* peer)
{
    // fix a return value
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    peer->handler->GetTextContentRect();
    return 0;
}
Ark_Int32 GetTextContentLineCountImpl(TextContentControllerBasePeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, 0);
    return Converter::ArkValue<Ark_Int32>(peer->handler->GetTextContentLinesNum());
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

}
