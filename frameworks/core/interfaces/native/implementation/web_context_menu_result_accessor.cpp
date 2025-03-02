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
#include "core/interfaces/native/implementation/web_context_menu_result_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebContextMenuResultAccessor {
void DestroyPeerImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_WebContextMenuResult CtorImpl()
{
    return new WebContextMenuResultPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CloseContextMenuImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Cancel();
}
void CopyImageImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->CopyImage();
}
void CopyImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Copy();
}
void PasteImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Paste();
}
void CutImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Cut();
}
void SelectAllImpl(Ark_WebContextMenuResult peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->SelectAll();
}
} // WebContextMenuResultAccessor
const GENERATED_ArkUIWebContextMenuResultAccessor* GetWebContextMenuResultAccessor()
{
    static const GENERATED_ArkUIWebContextMenuResultAccessor WebContextMenuResultAccessorImpl {
        WebContextMenuResultAccessor::DestroyPeerImpl,
        WebContextMenuResultAccessor::CtorImpl,
        WebContextMenuResultAccessor::GetFinalizerImpl,
        WebContextMenuResultAccessor::CloseContextMenuImpl,
        WebContextMenuResultAccessor::CopyImageImpl,
        WebContextMenuResultAccessor::CopyImpl,
        WebContextMenuResultAccessor::PasteImpl,
        WebContextMenuResultAccessor::CutImpl,
        WebContextMenuResultAccessor::SelectAllImpl,
    };
    return &WebContextMenuResultAccessorImpl;
}

struct WebContextMenuResultPeer {
    virtual ~WebContextMenuResultPeer() = default;
};
}
