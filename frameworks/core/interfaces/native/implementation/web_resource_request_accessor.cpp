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
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceRequestAccessor {
void DestroyPeerImpl(Ark_WebResourceRequest peer)
{
    delete peer;
}
Ark_WebResourceRequest CtorImpl()
{
    return new WebResourceRequestPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_Header GetRequestHeaderImpl(Ark_WebResourceRequest peer)
{
    std::vector<Converter::Header> result;
    CHECK_NULL_RETURN(peer && peer->webRequest, Converter::ArkValue<Array_Header>(result, Converter::FC));
    auto headers = peer->webRequest->GetHeaders();
    for (const auto& pair : headers) {
        Converter::Header header {
            .headerKey = pair.first,
            .headerValue = pair.second
        };
        result.push_back(header);
    }
    return Converter::ArkValue<Array_Header>(result, Converter::FC);
}
Ark_String GetRequestUrlImpl(Ark_WebResourceRequest peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->webRequest, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->webRequest->GetUrl();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_Boolean IsRequestGestureImpl(Ark_WebResourceRequest peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->HasGesture());
}
Ark_Boolean IsMainFrameImpl(Ark_WebResourceRequest peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->IsMainFrame());
}
Ark_Boolean IsRedirectImpl(Ark_WebResourceRequest peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->IsRedirect());
}
Ark_String GetRequestMethodImpl(Ark_WebResourceRequest peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->webRequest, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->webRequest->GetMethod();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
} // WebResourceRequestAccessor
const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor()
{
    static const GENERATED_ArkUIWebResourceRequestAccessor WebResourceRequestAccessorImpl {
        WebResourceRequestAccessor::DestroyPeerImpl,
        WebResourceRequestAccessor::CtorImpl,
        WebResourceRequestAccessor::GetFinalizerImpl,
        WebResourceRequestAccessor::GetRequestHeaderImpl,
        WebResourceRequestAccessor::GetRequestUrlImpl,
        WebResourceRequestAccessor::IsRequestGestureImpl,
        WebResourceRequestAccessor::IsMainFrameImpl,
        WebResourceRequestAccessor::IsRedirectImpl,
        WebResourceRequestAccessor::GetRequestMethodImpl,
    };
    return &WebResourceRequestAccessorImpl;
}

}
