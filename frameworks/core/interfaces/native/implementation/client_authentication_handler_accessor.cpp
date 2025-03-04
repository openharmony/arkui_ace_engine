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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ClientAuthenticationHandlerAccessor {
void DestroyPeerImpl(Ark_ClientAuthenticationHandler peer)
{
}
Ark_ClientAuthenticationHandler CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void Confirm0Impl(Ark_ClientAuthenticationHandler peer,
                  const Ark_String* priKeyFile,
                  const Ark_String* certChainFile)
{
}
void Confirm1Impl(Ark_ClientAuthenticationHandler peer,
                  const Ark_String* authUri)
{
}
void CancelImpl(Ark_ClientAuthenticationHandler peer)
{
}
void IgnoreImpl(Ark_ClientAuthenticationHandler peer)
{
}
} // ClientAuthenticationHandlerAccessor
const GENERATED_ArkUIClientAuthenticationHandlerAccessor* GetClientAuthenticationHandlerAccessor()
{
    static const GENERATED_ArkUIClientAuthenticationHandlerAccessor ClientAuthenticationHandlerAccessorImpl {
        ClientAuthenticationHandlerAccessor::DestroyPeerImpl,
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
