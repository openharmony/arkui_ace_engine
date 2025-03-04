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
namespace WebResourceResponseAccessor {
void DestroyPeerImpl(Ark_WebResourceResponse peer)
{
}
Ark_WebResourceResponse CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetResponseDataImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Opt_Union_String_Number_Buffer_Resource GetResponseDataExImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Ark_String GetResponseEncodingImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Ark_String GetResponseMimeTypeImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Ark_String GetReasonMessageImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Array_Header GetResponseHeaderImpl(Ark_WebResourceResponse peer)
{
    return {};
}
Ark_Number GetResponseCodeImpl(Ark_WebResourceResponse peer)
{
    return {};
}
void SetResponseDataImpl(Ark_WebResourceResponse peer,
                         const Ark_Union_String_Number_Resource_Buffer* data)
{
}
void SetResponseEncodingImpl(Ark_WebResourceResponse peer,
                             const Ark_String* encoding)
{
}
void SetResponseMimeTypeImpl(Ark_WebResourceResponse peer,
                             const Ark_String* mimeType)
{
}
void SetReasonMessageImpl(Ark_WebResourceResponse peer,
                          const Ark_String* reason)
{
}
void SetResponseHeaderImpl(Ark_WebResourceResponse peer,
                           const Array_Header* header)
{
}
void SetResponseCodeImpl(Ark_WebResourceResponse peer,
                         const Ark_Number* code)
{
}
void SetResponseIsReadyImpl(Ark_WebResourceResponse peer,
                            Ark_Boolean IsReady)
{
}
Ark_Boolean GetResponseIsReadyImpl(Ark_WebResourceResponse peer)
{
    return {};
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
