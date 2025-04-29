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
#include "core/interfaces/native/implementation/js_geolocation_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace JsGeolocationAccessor {
void DestroyPeerImpl(Ark_JsGeolocation peer)
{
    CHECK_NULL_VOID(peer);
    peer->webGeolocation = nullptr;
    delete peer;
}
Ark_JsGeolocation CtorImpl()
{
    return new JsGeolocationPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void InvokeImpl(Ark_JsGeolocation peer,
                const Ark_String* origin,
                Ark_Boolean allow,
                Ark_Boolean retain)
{
    CHECK_NULL_VOID(peer && peer->webGeolocation);
    CHECK_NULL_VOID(origin);
    peer->webGeolocation->Invoke(
        Converter::Convert<std::string>(*origin),
        Converter::Convert<bool>(allow),
        Converter::Convert<bool>(retain)
    );
}
} // JsGeolocationAccessor
const GENERATED_ArkUIJsGeolocationAccessor* GetJsGeolocationAccessor()
{
    static const GENERATED_ArkUIJsGeolocationAccessor JsGeolocationAccessorImpl {
        JsGeolocationAccessor::DestroyPeerImpl,
        JsGeolocationAccessor::CtorImpl,
        JsGeolocationAccessor::GetFinalizerImpl,
        JsGeolocationAccessor::InvokeImpl,
    };
    return &JsGeolocationAccessorImpl;
}

struct JsGeolocationPeer {
    virtual ~JsGeolocationPeer() = default;
};
}
