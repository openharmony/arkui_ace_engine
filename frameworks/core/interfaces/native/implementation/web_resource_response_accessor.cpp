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
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace {
constexpr int32_t BAD_REQUEST = 400;
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceResponseAccessor {
void DestroyPeerImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
WebResourceResponsePeer* CtorImpl()
{
    return new WebResourceResponsePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetResponseDataImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetData();
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetResponseDataImpl - return value need to be supported");
}
Ark_NativePointer GetResponseDataExImpl(WebResourceResponsePeer* peer)
{
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetResponseDataExImpl - return value need to be supported");
    return 0;
}
void GetResponseEncodingImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetEncoding();
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetResponseEncodingImpl - return value need to be supported");
}
void GetResponseMimeTypeImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetMimeType();
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetResponseMimeTypeImpl - return value need to be supported");
}
void GetReasonMessageImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetReason();
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetReasonMessageImpl - return value need to be supported");
}
void GetResponseHeaderImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->GetHeaders();
    // value need to be returned
    LOGE("WebResourceResponseAccessor::GetResponseHeaderImpl - return value need to be supported");
}
Ark_Int32 GetResponseCodeImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, BAD_REQUEST);
    return static_cast<Ark_Int32>(peer->handler->GetStatusCode());
}
void SetResponseDataImpl(WebResourceResponsePeer* peer,
                         const Ark_Union_String_Number_Resource_Buffer* data)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(data);
    Converter::VisitUnion(*data,
        [peer, data](const Ark_String& responseData) {
            std::string str = Converter::Convert<std::string>(responseData);
            peer->handler->SetData(str);
        },
        [peer, data](const Ark_Number& responseData) {
            int32_t fd = Converter::Convert<int32_t>(responseData);
            peer->handler->SetFileHandle(fd);
        },
        [peer, data](const Ark_Resource& responseData) {
            std::optional<std::string> resourceUrl = Converter::OptConvert<std::string>(responseData);
            std::string url;
            if (resourceUrl) {
                auto np = resourceUrl.value().find_first_of("/");
                url = (np == std::string::npos) ? resourceUrl.value() : resourceUrl.value().erase(np, 1);
            }
            peer->handler->SetResourceUrl(url);
        },
        [peer, data](const Ark_Buffer& responseData) {
            LOGE("WebResourceResponseAccessor::SetResponseDataImpl - Ark_ArrayBuffer is not fully implemented");
        },
        []() {}
    );
}
void SetResponseEncodingImpl(WebResourceResponsePeer* peer,
                             const Ark_String* encoding)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(encoding);
    std::string str = Converter::Convert<std::string>(*encoding);
    peer->handler->SetEncoding(str);
}
void SetResponseMimeTypeImpl(WebResourceResponsePeer* peer,
                             const Ark_String* mimeType)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(mimeType);
    std::string str = Converter::Convert<std::string>(*mimeType);
    peer->handler->SetMimeType(str);
}
void SetReasonMessageImpl(WebResourceResponsePeer* peer,
                          const Ark_String* reason)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(reason);
    std::string str = Converter::Convert<std::string>(*reason);
    peer->handler->SetReason(str);
}
void SetResponseHeaderImpl(WebResourceResponsePeer* peer,
                           const Array_Header* header)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(header);
    auto headersOpt = Converter::OptConvert<std::vector<Converter::Header>>(*header);
    if (headersOpt) {
        for (auto header : headersOpt.value()) {
            peer->handler->SetHeadersVal(header.headerKey, header.headerValue);
        }
    }
}
void SetResponseCodeImpl(WebResourceResponsePeer* peer,
                         const Ark_Number* code)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(code);
    int32_t statusCode = Converter::Convert<int32_t>(*code);
    peer->handler->SetStatusCode(statusCode);
}
void SetResponseIsReadyImpl(WebResourceResponsePeer* peer,
                            Ark_Boolean IsReady)
{
    CHECK_NULL_VOID(peer && peer->handler);
    bool isReady = Converter::Convert<bool>(IsReady);
    peer->handler->SetResponseStatus(isReady);
}
Ark_Boolean GetResponseIsReadyImpl(WebResourceResponsePeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, false);
    return Converter::ArkValue<Ark_Boolean>(peer->handler->GetResponseStatus());
}
} // WebResourceResponseAccessor
const GENERATED_ArkUIWebResourceResponseAccessor* GetWebResourceResponseAccessor()
{
    static const GENERATED_ArkUIWebResourceResponseAccessor WebResourceResponseAccessorImpl {
        WebResourceResponseAccessor::DestroyPeerImpl,
        WebResourceResponseAccessor::CtorImpl,
        WebResourceResponseAccessor::GetFinalizerImpl,
        WebResourceResponseAccessor::GetResponseDataImpl,
        WebResourceResponseAccessor::GetResponseDataExImpl,
        WebResourceResponseAccessor::GetResponseEncodingImpl,
        WebResourceResponseAccessor::GetResponseMimeTypeImpl,
        WebResourceResponseAccessor::GetReasonMessageImpl,
        WebResourceResponseAccessor::GetResponseHeaderImpl,
        WebResourceResponseAccessor::GetResponseCodeImpl,
        WebResourceResponseAccessor::SetResponseDataImpl,
        WebResourceResponseAccessor::SetResponseEncodingImpl,
        WebResourceResponseAccessor::SetResponseMimeTypeImpl,
        WebResourceResponseAccessor::SetReasonMessageImpl,
        WebResourceResponseAccessor::SetResponseHeaderImpl,
        WebResourceResponseAccessor::SetResponseCodeImpl,
        WebResourceResponseAccessor::SetResponseIsReadyImpl,
        WebResourceResponseAccessor::GetResponseIsReadyImpl,
    };
    return &WebResourceResponseAccessorImpl;
}

}
