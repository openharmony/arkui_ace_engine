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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceResponseAccessor {
void DestroyPeerImpl(WebResourceResponsePeer* peer)
{
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
}
Ark_NativePointer GetResponseDataExImpl(WebResourceResponsePeer* peer)
{
    return 0;
}
void GetResponseEncodingImpl(WebResourceResponsePeer* peer)
{
}
void GetResponseMimeTypeImpl(WebResourceResponsePeer* peer)
{
}
void GetReasonMessageImpl(WebResourceResponsePeer* peer)
{
}
void GetResponseHeaderImpl(WebResourceResponsePeer* peer)
{
}
Ark_Int32 GetResponseCodeImpl(WebResourceResponsePeer* peer)
{
    return 0;
}
void SetResponseDataImpl(WebResourceResponsePeer* peer,
                         const Ark_Union_String_Number_Resource_Buffer* data)
{
}
void SetResponseEncodingImpl(WebResourceResponsePeer* peer,
                             const Ark_String* encoding)
{
}
void SetResponseMimeTypeImpl(WebResourceResponsePeer* peer,
                             const Ark_String* mimeType)
{
}
void SetReasonMessageImpl(WebResourceResponsePeer* peer,
                          const Ark_String* reason)
{
}
void SetResponseHeaderImpl(WebResourceResponsePeer* peer,
                           const Array_Header* header)
{
}
void SetResponseCodeImpl(WebResourceResponsePeer* peer,
                         const Ark_Number* code)
{
}
void SetResponseIsReadyImpl(WebResourceResponsePeer* peer,
                            Ark_Boolean IsReady)
{
}
Ark_Boolean GetResponseIsReadyImpl(WebResourceResponsePeer* peer)
{
    return 0;
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
