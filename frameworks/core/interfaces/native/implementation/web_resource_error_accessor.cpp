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
#include "core/interfaces/native/implementation/web_resource_error_peer_impl.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceErrorAccessor {
void DestroyPeerImpl(Ark_WebResourceError peer)
{
    delete peer;
}
Ark_WebResourceError CtorImpl()
{
    return new WebResourceErrorPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetErrorInfoImpl(Ark_WebResourceError peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetInfo();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_Number GetErrorCodeImpl(Ark_WebResourceError peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer && peer->handler, errValue);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetCode());
}
} // WebResourceErrorAccessor
const GENERATED_ArkUIWebResourceErrorAccessor* GetWebResourceErrorAccessor()
{
    static const GENERATED_ArkUIWebResourceErrorAccessor WebResourceErrorAccessorImpl {
        WebResourceErrorAccessor::DestroyPeerImpl,
        WebResourceErrorAccessor::CtorImpl,
        WebResourceErrorAccessor::GetFinalizerImpl,
        WebResourceErrorAccessor::GetErrorInfoImpl,
        WebResourceErrorAccessor::GetErrorCodeImpl,
    };
    return &WebResourceErrorAccessorImpl;
}

}
