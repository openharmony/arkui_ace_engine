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
#include "core/interfaces/native/implementation/text_clock_controller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextClockControllerAccessor {
void DestroyPeerImpl(Ark_TextClockController peer)
{
    if (peer) {
        peer->controller = nullptr;
        delete peer;
    }
}
Ark_TextClockController CtorImpl()
{
    return new TextClockControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StartImpl(Ark_TextClockController peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->Start();
}
void StopImpl(Ark_TextClockController peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->Stop();
}
} // TextClockControllerAccessor
const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor()
{
    static const GENERATED_ArkUITextClockControllerAccessor TextClockControllerAccessorImpl {
        TextClockControllerAccessor::DestroyPeerImpl,
        TextClockControllerAccessor::CtorImpl,
        TextClockControllerAccessor::GetFinalizerImpl,
        TextClockControllerAccessor::StartImpl,
        TextClockControllerAccessor::StopImpl,
    };
    return &TextClockControllerAccessorImpl;
}

struct TextClockControllerPeer {
    virtual ~TextClockControllerPeer() = default;
};
}
