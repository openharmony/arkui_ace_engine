/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/level_order_peer.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LevelOrderExtenderAccessor {
void DestroyPeerImpl(Ark_LevelOrderExtender peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->levelOrder);
    delete peer->levelOrder;
    peer->levelOrder = nullptr;
    PeerUtils::DestroyPeer(peer);
}
Ark_LevelOrderExtender ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<LevelOrderExtenderPeer>();
    peer->levelOrder = new (std::nothrow) NG::LevelOrder();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LevelOrderExtender ClampImpl(const Ark_Number* order)
{
    auto peer = PeerUtils::CreatePeer<LevelOrderExtenderPeer>();
    CHECK_NULL_RETURN(peer, nullptr);
    peer->levelOrder = new (std::nothrow) NG::LevelOrder();
    CHECK_NULL_RETURN(peer->levelOrder, nullptr);
    peer->levelOrder->SetOrder(Converter::Convert<double>(*order));
    return peer;
}
Ark_Number GetOrderImpl(Ark_LevelOrderExtender peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->levelOrder, {});
    auto value = Converter::ArkValue<Ark_Number>(peer->levelOrder->GetOrder());
    return value;
}
} // LevelOrderExtenderAccessor
const GENERATED_ArkUILevelOrderExtenderAccessor* GetLevelOrderExtenderAccessor()
{
    static const GENERATED_ArkUILevelOrderExtenderAccessor LevelOrderExtenderAccessorImpl {
        LevelOrderExtenderAccessor::DestroyPeerImpl,
        LevelOrderExtenderAccessor::ConstructImpl,
        LevelOrderExtenderAccessor::GetFinalizerImpl,
        LevelOrderExtenderAccessor::ClampImpl,
        LevelOrderExtenderAccessor::GetOrderImpl,
    };
    return &LevelOrderExtenderAccessorImpl;
}

}
