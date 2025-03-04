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
namespace WebResourceRequestAccessor {
void DestroyPeerImpl(Ark_WebResourceRequest peer)
{
}
Ark_WebResourceRequest CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_Header GetRequestHeaderImpl(Ark_WebResourceRequest peer)
{
    return {};
}
Ark_String GetRequestUrlImpl(Ark_WebResourceRequest peer)
{
    return {};
}
Ark_Boolean IsRequestGestureImpl(Ark_WebResourceRequest peer)
{
    return {};
}
Ark_Boolean IsMainFrameImpl(Ark_WebResourceRequest peer)
{
    return {};
}
Ark_Boolean IsRedirectImpl(Ark_WebResourceRequest peer)
{
    return {};
}
Ark_String GetRequestMethodImpl(Ark_WebResourceRequest peer)
{
    return {};
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
