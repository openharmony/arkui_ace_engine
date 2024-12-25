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
#include "core/interfaces/native/implementation/layout_manager_peer_impl.h"
#include "core/interfaces/native/implementation/styled_string_peer.h"
#include "core/interfaces/native/implementation/text_controller_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor();
namespace TextControllerAccessor {
void DestroyPeerImpl(TextControllerPeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->controller = nullptr;
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new TextControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void CloseSelectionMenuImpl(TextControllerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->CloseSelectionMenu();
}
void SetStyledStringImpl(TextControllerPeer* peer,
                         const Ark_StyledString* value)
{
    CHECK_NULL_VOID(peer && peer->controller);
    CHECK_NULL_VOID(value && value->ptr);
    auto styledStringPeer = reinterpret_cast<StyledStringPeer*>(value->ptr);
    peer->controller->SetStyledString(styledStringPeer->spanString);
}
Ark_NativePointer GetLayoutManagerImpl(TextControllerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->controller, nullptr);
    auto layoutManagerAccessor = GetLayoutManagerAccessor();
    CHECK_NULL_RETURN(layoutManagerAccessor, nullptr);
    auto layoutManagerPeer = reinterpret_cast<LayoutManagerPeer*>(GetLayoutManagerAccessor()->ctor());
    CHECK_NULL_RETURN(layoutManagerPeer, nullptr);
    layoutManagerPeer->handler = peer->controller->GetLayoutInfoInterface();
    return layoutManagerPeer;
}
} // TextControllerAccessor
const GENERATED_ArkUITextControllerAccessor* GetTextControllerAccessor()
{
    static const GENERATED_ArkUITextControllerAccessor TextControllerAccessorImpl {
        TextControllerAccessor::DestroyPeerImpl,
        TextControllerAccessor::CtorImpl,
        TextControllerAccessor::GetFinalizerImpl,
        TextControllerAccessor::CloseSelectionMenuImpl,
        TextControllerAccessor::SetStyledStringImpl,
        TextControllerAccessor::GetLayoutManagerImpl,
    };
    return &TextControllerAccessorImpl;
}

struct TextControllerPeer {
    virtual ~TextControllerPeer() = default;
};
}
