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
#include "core/interfaces/native/implementation/client_authentication_handler_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ClientAuthenticationHandlerAccessor {
ClientAuthenticationHandlerPeer* CtorImpl()
{
    return new ClientAuthenticationHandlerPeer();
}
static void DestroyPeer(ClientAuthenticationHandlerPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeer);
}
void Confirm0Impl(ClientAuthenticationHandlerPeer* peer,
                  const Ark_String* priKeyFile,
                  const Ark_String* certChainFile)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(priKeyFile);
    CHECK_NULL_VOID(certChainFile);
    std::string priKeyFileStr = Converter::Convert<std::string>(*priKeyFile);
    std::string certChainFileStr = Converter::Convert<std::string>(*certChainFile);
    peer->handler->HandleConfirm(priKeyFileStr, certChainFileStr);
}
void Confirm1Impl(ClientAuthenticationHandlerPeer* peer,
                  const Ark_String* authUri)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(authUri);
    std::string priKeyFileStr = Converter::Convert<std::string>(*authUri);
    std::string certChainFileStr;
    peer->handler->HandleConfirm(priKeyFileStr, certChainFileStr);
}
void CancelImpl(ClientAuthenticationHandlerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->HandleCancel();
}
void IgnoreImpl(ClientAuthenticationHandlerPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->HandleIgnore();
}
} // ClientAuthenticationHandlerAccessor
const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor()
{
    static const GENERATED_ArkUIClientAuthenticationHandlerAccessor ClientAuthenticationHandlerAccessorImpl {
        ClientAuthenticationHandlerAccessor::CtorImpl,
        ClientAuthenticationHandlerAccessor::GetFinalizerImpl,
        ClientAuthenticationHandlerAccessor::Confirm0Impl,
        ClientAuthenticationHandlerAccessor::Confirm1Impl,
        ClientAuthenticationHandlerAccessor::CancelImpl,
        ClientAuthenticationHandlerAccessor::IgnoreImpl,
    };
    return &ClientAuthenticationHandlerAccessorImpl;
}

}
