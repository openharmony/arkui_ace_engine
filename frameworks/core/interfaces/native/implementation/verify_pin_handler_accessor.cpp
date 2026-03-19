/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/verify_pin_handler_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace VerifyPinHandlerAccessor {
void DestroyPeerImpl(Ark_VerifyPinHandler peer)
{
    delete peer;
}
Ark_VerifyPinHandler ConstructImpl()
{
    return new VerifyPinHandlerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ConfirmImpl(Ark_VerifyPinHandler peer,
                 Ark_PinVerifyResult result)
{
    CHECK_NULL_VOID(peer);
    int32_t pinVerifyResult = static_cast<int32_t>(result);
    peer->verifyPinHandler->HandleConfirm(pinVerifyResult);
}
} // VerifyPinHandlerAccessor
const GENERATED_ArkUIVerifyPinHandlerAccessor* GetVerifyPinHandlerAccessor()
{
    static const GENERATED_ArkUIVerifyPinHandlerAccessor VerifyPinHandlerAccessorImpl {
        VerifyPinHandlerAccessor::DestroyPeerImpl,
        VerifyPinHandlerAccessor::ConstructImpl,
        VerifyPinHandlerAccessor::GetFinalizerImpl,
        VerifyPinHandlerAccessor::ConfirmImpl,
    };
    return &VerifyPinHandlerAccessorImpl;
}

}
