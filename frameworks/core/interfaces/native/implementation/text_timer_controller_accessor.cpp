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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/implementation/text_timer_controller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextTimerControllerAccessor {
void DestroyPeerImpl(Ark_TextTimerController peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_TextTimerController CtorImpl()
{
    return new TextTimerControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(Ark_TextTimerController peer)
{
    auto peerImpl = reinterpret_cast<TextTimerControllerPeer*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    peerImpl->GetController()->Start();
}
void PauseImpl(Ark_TextTimerController peer)
{
    auto peerImpl = reinterpret_cast<TextTimerControllerPeer*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    peerImpl->GetController()->Pause();
}
void ResetImpl(Ark_TextTimerController peer)
{
    auto peerImpl = reinterpret_cast<TextTimerControllerPeer*>(peer);
    CHECK_NULL_VOID(peerImpl && peerImpl->GetController());
    peerImpl->GetController()->Reset();
}
} // TextTimerControllerAccessor
const GENERATED_ArkUITextTimerControllerAccessor* GetTextTimerControllerAccessor()
{
    static const GENERATED_ArkUITextTimerControllerAccessor TextTimerControllerAccessorImpl {
        TextTimerControllerAccessor::DestroyPeerImpl,
        TextTimerControllerAccessor::CtorImpl,
        TextTimerControllerAccessor::GetFinalizerImpl,
        TextTimerControllerAccessor::StartImpl,
        TextTimerControllerAccessor::PauseImpl,
        TextTimerControllerAccessor::ResetImpl,
    };
    return &TextTimerControllerAccessorImpl;
}

}
