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
#include "core/interfaces/native/implementation/web_resource_response_peer_impl.h"
#include "core/interfaces/native/utility/ace_engine_types.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace {
const Ark_Number BAD_REQUEST = OHOS::Ace::NG::Converter::ArkValue<Ark_Number>(400);
const int32_t RESPONSE_DATA_TYPE_STRING = 0;
const int32_t RESPONSE_DATA_TYPE_NUMBER = 1;
const int32_t RESPONSE_DATA_TYPE_RESOURCE = 2;
const int32_t RESPONSE_DATA_TYPE_BUFFER = 3;
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceResponseAccessor {
void DestroyPeerImpl(Ark_WebResourceResponse peer)
{
    delete peer;
}
Ark_WebResourceResponse CtorImpl()
{
    return new WebResourceResponsePeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetResponseDataImpl(Ark_WebResourceResponse peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result  = peer->handler->GetData();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Opt_Union_String_Number_Buffer_Resource GetResponseDataExImpl(Ark_WebResourceResponse peer)
{
    Opt_Union_String_Number_Buffer_Resource result {};
    CHECK_NULL_RETURN(peer && peer->handler, result);
    if (peer->responseDataType) {
        switch (peer->responseDataType.value()) {
            case RESPONSE_DATA_TYPE_STRING:
                return Converter::ArkUnion<Opt_Union_String_Number_Buffer_Resource, Ark_String>(
                    peer->handler->GetData(), Converter::FC);
            case RESPONSE_DATA_TYPE_NUMBER:
                return Converter::ArkUnion<Opt_Union_String_Number_Buffer_Resource, Ark_Number>(
                    peer->handler->GetFileHandle());
            case RESPONSE_DATA_TYPE_RESOURCE:
                if (peer->responseDataResEx) {
                    return Converter::ArkUnion<Opt_Union_String_Number_Buffer_Resource, Ark_Resource>(
                        peer->responseDataResEx.value());
                }
                break;
            case RESPONSE_DATA_TYPE_BUFFER:
                return Converter::ArkUnion<Opt_Union_String_Number_Buffer_Resource, Ark_Buffer>(
                    peer->handler->GetData(), Converter::FC);
            default:
                break;
        }
    }
    return result;
}
Ark_String GetResponseEncodingImpl(Ark_WebResourceResponse peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetEncoding();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_String GetResponseMimeTypeImpl(Ark_WebResourceResponse peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetMimeType();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Ark_String GetReasonMessageImpl(Ark_WebResourceResponse peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetReason();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
Array_Header GetResponseHeaderImpl(Ark_WebResourceResponse peer)
{
    std::vector<Converter::Header> result;
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Array_Header>(result, Converter::FC));
    auto headers = peer->handler->GetHeaders();
    for (const auto& pair : headers) {
        Converter::Header header {
            .headerKey = pair.first,
            .headerValue = pair.second
        };
        result.push_back(header);
    }
    return Converter::ArkValue<Array_Header>(result, Converter::FC);
}
Ark_Number GetResponseCodeImpl(Ark_WebResourceResponse peer)
{
    CHECK_NULL_RETURN(peer && peer->handler, BAD_REQUEST);
    return Converter::ArkValue<Ark_Number>(peer->handler->GetStatusCode());
}
void SetResponseDataImpl(Ark_WebResourceResponse peer,
                         const Ark_Union_String_Number_Resource_Buffer* data)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(data);
    Converter::VisitUnion(*data,
        [peer](const Ark_String& responseData) {
            std::string str = Converter::Convert<std::string>(responseData);
            peer->handler->SetData(str);
            peer->responseDataType = RESPONSE_DATA_TYPE_STRING;
        },
        [peer](const Ark_Number& responseData) {
            int32_t fd = Converter::Convert<int32_t>(responseData);
            peer->handler->SetFileHandle(fd);
            peer->responseDataType = RESPONSE_DATA_TYPE_NUMBER;
        },
        [peer](const Ark_Resource& responseData) {
            std::optional<std::string> resourceUrl = Converter::OptConvert<std::string>(responseData);
            std::string url;
            if (resourceUrl) {
                auto np = resourceUrl.value().find_first_of("/");
                url = (np == std::string::npos) ? resourceUrl.value() : resourceUrl.value().erase(np, 1);
            }
            peer->handler->SetResourceUrl(url);
            peer->responseDataType = RESPONSE_DATA_TYPE_RESOURCE;
            peer->responseDataResEx = responseData;
        },
        [peer](const Ark_Buffer& responseData) {
            int32_t bufferSize = static_cast<int32_t>(responseData.length);
            void* buffer = responseData.data;
            std::string str = Converter::Convert<std::string>(responseData);
            peer->handler->SetData(str);
            peer->handler->SetBuffer(static_cast<char*>(buffer), bufferSize);
            peer->responseDataType = RESPONSE_DATA_TYPE_BUFFER;
        },
        [peer]() {
            peer->responseDataType.reset();
        }
    );
}
void SetResponseEncodingImpl(Ark_WebResourceResponse peer,
                             const Ark_String* encoding)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(encoding);
    std::string str = Converter::Convert<std::string>(*encoding);
    peer->handler->SetEncoding(str);
}
void SetResponseMimeTypeImpl(Ark_WebResourceResponse peer,
                             const Ark_String* mimeType)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(mimeType);
    std::string str = Converter::Convert<std::string>(*mimeType);
    peer->handler->SetMimeType(str);
}
void SetReasonMessageImpl(Ark_WebResourceResponse peer,
                          const Ark_String* reason)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(reason);
    std::string str = Converter::Convert<std::string>(*reason);
    peer->handler->SetReason(str);
}
void SetResponseHeaderImpl(Ark_WebResourceResponse peer,
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
void SetResponseCodeImpl(Ark_WebResourceResponse peer,
                         const Ark_Number* code)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(code);
    int32_t statusCode = Converter::Convert<int32_t>(*code);
    peer->handler->SetStatusCode(statusCode);
}
void SetResponseIsReadyImpl(Ark_WebResourceResponse peer,
                            Ark_Boolean IsReady)
{
    CHECK_NULL_VOID(peer && peer->handler);
    bool isReady = Converter::Convert<bool>(IsReady);
    peer->handler->SetResponseStatus(isReady);
}
Ark_Boolean GetResponseIsReadyImpl(Ark_WebResourceResponse peer)
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
