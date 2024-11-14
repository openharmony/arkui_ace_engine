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
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/implementation/text_clock_controller_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TextClockControllerAccessor {
static void DestroyPeer(TextClockControllerPeer *peer)
{
    if (peer) {
        peer->controller = nullptr;
        delete peer;
    }
}
TextClockControllerPeer* CtorImpl()
{
    return new TextClockControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeer);
}
void StartImpl(TextClockControllerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->Start();
}
void StopImpl(TextClockControllerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->controller);
    peer->controller->Stop();
}
} // TextClockControllerAccessor
const GENERATED_ArkUITextClockControllerAccessor* GetTextClockControllerAccessor()
{
    static const GENERATED_ArkUITextClockControllerAccessor TextClockControllerAccessorImpl {
        TextClockControllerAccessor::CtorImpl,
        TextClockControllerAccessor::GetFinalizerImpl,
        TextClockControllerAccessor::StartImpl,
        TextClockControllerAccessor::StopImpl,
    };
    return &TextClockControllerAccessorImpl;
}

}
