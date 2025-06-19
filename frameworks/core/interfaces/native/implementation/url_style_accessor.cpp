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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "url_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace UrlStyleAccessor {
void DestroyPeerImpl(Ark_UrlStyle peer)
{
    delete peer;
}
Ark_UrlStyle CtorImpl(const Ark_String* url)
{
    std::string urlAddress;
    if (url) {
        urlAddress = Converter::Convert<std::string>(*url);
    }
    auto span = AceType::MakeRefPtr<OHOS::Ace::UrlSpan>(urlAddress);
    return new UrlStylePeer{ .span = span };
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetUrlImpl(Ark_UrlStyle peer)
{
    CHECK_NULL_RETURN(peer && peer->span, {});
    return Converter::ArkValue<Ark_String>(peer->span->GetUrlSpanAddress(), Converter::FC);
}
} // UrlStyleAccessor
const GENERATED_ArkUIUrlStyleAccessor* GetUrlStyleAccessor()
{
    static const GENERATED_ArkUIUrlStyleAccessor UrlStyleAccessorImpl {
        UrlStyleAccessor::DestroyPeerImpl,
        UrlStyleAccessor::CtorImpl,
        UrlStyleAccessor::GetFinalizerImpl,
        UrlStyleAccessor::GetUrlImpl,
    };
    return &UrlStyleAccessorImpl;
}
}
