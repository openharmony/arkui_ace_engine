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

#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace WebResourceResponseModifier {
Ark_NativePointer CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void GetResponseDataImpl(WebResourceResponsePeer* peer)
{
}
void GetResponseDataExImpl(WebResourceResponsePeer* peer)
{
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
Ark_NativePointer GetResponseHeaderImpl(WebResourceResponsePeer* peer)
{
    return 0;
}
Ark_Int32 GetResponseCodeImpl(WebResourceResponsePeer* peer)
{
    return 0;
}
void SetResponseDataImpl(WebResourceResponsePeer* peer,
                         const Union_String_Number_Resource_ArrayBuffer* data)
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
} // WebResourceResponseModifier
const GENERATED_ArkUIWebResourceResponseAccessor* GetWebResourceResponseAccessor()
{
    static const GENERATED_ArkUIWebResourceResponseAccessor WebResourceResponseAccessorImpl {
        WebResourceResponseModifier::CtorImpl,
        WebResourceResponseModifier::GetFinalizerImpl,
        WebResourceResponseModifier::GetResponseDataImpl,
        WebResourceResponseModifier::GetResponseDataExImpl,
        WebResourceResponseModifier::GetResponseEncodingImpl,
        WebResourceResponseModifier::GetResponseMimeTypeImpl,
        WebResourceResponseModifier::GetReasonMessageImpl,
        WebResourceResponseModifier::GetResponseHeaderImpl,
        WebResourceResponseModifier::GetResponseCodeImpl,
        WebResourceResponseModifier::SetResponseDataImpl,
        WebResourceResponseModifier::SetResponseEncodingImpl,
        WebResourceResponseModifier::SetResponseMimeTypeImpl,
        WebResourceResponseModifier::SetReasonMessageImpl,
        WebResourceResponseModifier::SetResponseHeaderImpl,
        WebResourceResponseModifier::SetResponseCodeImpl,
        WebResourceResponseModifier::SetResponseIsReadyImpl,
        WebResourceResponseModifier::GetResponseIsReadyImpl,
    };
    return &WebResourceResponseAccessorImpl;
}

}
