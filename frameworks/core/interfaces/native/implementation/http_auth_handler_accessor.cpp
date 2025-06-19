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
#include "core/interfaces/native/implementation/http_auth_handler_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace HttpAuthHandlerAccessor {
void DestroyPeerImpl(Ark_HttpAuthHandler peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_HttpAuthHandler CtorImpl()
{
    return new HttpAuthHandlerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean ConfirmImpl(Ark_HttpAuthHandler peer,
                        const Ark_String* userName,
                        const Ark_String* password)
{
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_Boolean>(false));
    CHECK_NULL_RETURN(userName, Converter::ArkValue<Ark_Boolean>(false));
    CHECK_NULL_RETURN(password, Converter::ArkValue<Ark_Boolean>(false));
    std::string name = Converter::Convert<std::string>(*userName);
    std::string pass = Converter::Convert<std::string>(*password);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->Confirm(name, pass));
}
void CancelImpl(Ark_HttpAuthHandler peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Cancel();
}
Ark_Boolean IsHttpAuthInfoSavedImpl(Ark_HttpAuthHandler peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_Boolean>(false));
    return Converter::ArkValue<Ark_Boolean>(peer->handler->IsHttpAuthInfoSaved());
}
} // HttpAuthHandlerAccessor
const GENERATED_ArkUIHttpAuthHandlerAccessor* GetHttpAuthHandlerAccessor()
{
    static const GENERATED_ArkUIHttpAuthHandlerAccessor HttpAuthHandlerAccessorImpl {
        HttpAuthHandlerAccessor::DestroyPeerImpl,
        HttpAuthHandlerAccessor::CtorImpl,
        HttpAuthHandlerAccessor::GetFinalizerImpl,
        HttpAuthHandlerAccessor::ConfirmImpl,
        HttpAuthHandlerAccessor::CancelImpl,
        HttpAuthHandlerAccessor::IsHttpAuthInfoSavedImpl,
    };
    return &HttpAuthHandlerAccessorImpl;
}

struct HttpAuthHandlerPeer {
    virtual ~HttpAuthHandlerPeer() = default;
};
}
