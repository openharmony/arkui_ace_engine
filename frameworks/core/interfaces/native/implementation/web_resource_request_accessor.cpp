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
#include "core/interfaces/native/implementation/web_resource_request_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceRequestAccessor {
WebResourceRequestPeer* CtorImpl()
{
    return new WebResourceRequestPeer();
}
static void DestroyPeer(WebResourceRequestPeer *peer)
{
    CHECK_NULL_VOID(peer);
    peer->webRequest = nullptr;
    delete peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(DestroyPeer);
}
void GetRequestHeaderImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->webRequest);
    peer->webRequest->GetHeaders();
    // headers need to be returned
    LOGE("WebResourceRequestPeer::GetRequestHeaderImpl - return value need to be supported");
}
void GetRequestUrlImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->webRequest);
    peer->webRequest->GetUrl();
    // url need to be returned
    LOGE("WebResourceRequestPeer::GetRequestUrlImpl - return value need to be supported");
}
Ark_Boolean IsRequestGestureImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->HasGesture());
}
Ark_Boolean IsMainFrameImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->IsMainFrame());
}
Ark_Boolean IsRedirectImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->webRequest, false);
    return Converter::ArkValue<Ark_Boolean>(peer->webRequest->IsRedirect());
}
void GetRequestMethodImpl(WebResourceRequestPeer* peer)
{
    CHECK_NULL_VOID(peer && peer->webRequest);
    peer->webRequest->GetMethod();
    // method need to be returned
    LOGE("WebResourceRequestPeer::GetRequestMethodImpl - return value need to be supported");
}
} // WebResourceRequestAccessor
const GENERATED_ArkUIWebResourceRequestAccessor* GetWebResourceRequestAccessor()
{
    static const GENERATED_ArkUIWebResourceRequestAccessor WebResourceRequestAccessorImpl {
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
