/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/implementation/magnifier_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace MagnifierAccessor {
void DestroyPeerImpl(Ark_arkui_component_idlize_Magnifier peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_arkui_component_idlize_Magnifier ConstructImpl()
{
    auto peer = OHOS::Ace::NG::PeerUtils::CreatePeer<MagnifierPeer>();
    CHECK_NULL_RETURN(peer, {});
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void BindImpl(Ark_arkui_component_idlize_Magnifier peer,
              const Ark_String* id)
{
    CHECK_NULL_VOID(peer);
    auto idStr = Converter::Convert<std::string>(*id);
    peer->Bind(idStr);
}
void ShowImpl(Ark_arkui_component_idlize_Magnifier peer,
              Ark_Float64 x,
              Ark_Float64 y)
{
    CHECK_NULL_VOID(peer);
    auto optX = Converter::OptConvert<float>(x);
    auto optY = Converter::OptConvert<float>(y);
    peer->Show(optX, optY);
}
void UnbindImpl(Ark_arkui_component_idlize_Magnifier peer)
{
    CHECK_NULL_VOID(peer);
    peer->Unbind();
}
} // MagnifierAccessor
const GENERATED_ArkUIMagnifierAccessor* GetMagnifierAccessor()
{
    static const GENERATED_ArkUIMagnifierAccessor MagnifierAccessorImpl {
        MagnifierAccessor::DestroyPeerImpl,
        MagnifierAccessor::ConstructImpl,
        MagnifierAccessor::GetFinalizerImpl,
        MagnifierAccessor::BindImpl,
        MagnifierAccessor::ShowImpl,
        MagnifierAccessor::UnbindImpl,
    };
    return &MagnifierAccessorImpl;
}

}
