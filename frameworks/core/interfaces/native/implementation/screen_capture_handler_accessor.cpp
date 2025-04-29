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
#include "core/interfaces/native/implementation/screen_capture_handler_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScreenCaptureHandlerAccessor {
void DestroyPeerImpl(Ark_ScreenCaptureHandler peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_ScreenCaptureHandler CtorImpl()
{
    return new ScreenCaptureHandlerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetOriginImpl(Ark_ScreenCaptureHandler peer)
{
    std::string result = "";
    CHECK_NULL_RETURN(peer && peer->handler, Converter::ArkValue<Ark_String>(result, Converter::FC));
    result = peer->handler->GetOrigin();
    return Converter::ArkValue<Ark_String>(result, Converter::FC);
}
void GrantImpl(Ark_ScreenCaptureHandler peer,
               const Ark_ScreenCaptureConfig* config)
{
    CHECK_NULL_VOID(peer && peer->handler);
    CHECK_NULL_VOID(config);
    peer->handler->Grant();
}
void DenyImpl(Ark_ScreenCaptureHandler peer)
{
    CHECK_NULL_VOID(peer && peer->handler);
    peer->handler->Deny();
}
} // ScreenCaptureHandlerAccessor
const GENERATED_ArkUIScreenCaptureHandlerAccessor* GetScreenCaptureHandlerAccessor()
{
    static const GENERATED_ArkUIScreenCaptureHandlerAccessor ScreenCaptureHandlerAccessorImpl {
        ScreenCaptureHandlerAccessor::DestroyPeerImpl,
        ScreenCaptureHandlerAccessor::CtorImpl,
        ScreenCaptureHandlerAccessor::GetFinalizerImpl,
        ScreenCaptureHandlerAccessor::GetOriginImpl,
        ScreenCaptureHandlerAccessor::GrantImpl,
        ScreenCaptureHandlerAccessor::DenyImpl,
    };
    return &ScreenCaptureHandlerAccessorImpl;
}

struct ScreenCaptureHandlerPeer {
    virtual ~ScreenCaptureHandlerPeer() = default;
};
}
