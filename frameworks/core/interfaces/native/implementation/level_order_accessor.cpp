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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/implementation/level_order_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LevelOrderAccessor {
void DestroyPeerImpl(Ark_LevelOrder peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->levelOrder);
    delete peer->levelOrder;
    peer->levelOrder = nullptr;
    PeerUtils::DestroyPeer(peer);
}
Ark_LevelOrder ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<LevelOrderPeer>();
    CHECK_NULL_RETURN(peer, nullptr);
    peer->levelOrder = new (std::nothrow) NG::LevelOrder();
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LevelOrder ClampImpl(const Ark_Number* order)
{
    auto peer = PeerUtils::CreatePeer<LevelOrderPeer>();
    CHECK_NULL_RETURN(peer, nullptr);
    peer->levelOrder = new (std::nothrow) NG::LevelOrder();
    if (!peer->levelOrder) {
        PeerUtils::DestroyPeer(peer);
        return nullptr;
    }
    peer->levelOrder->SetOrder(Converter::Convert<double>(*order));
    return peer;
}
Ark_Number GetOrderImpl(Ark_LevelOrder peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->levelOrder, {});
    auto value = Converter::ArkValue<Ark_Number>(peer->levelOrder->GetOrder());
    return value;
}
} // LevelOrderAccessor
const GENERATED_ArkUILevelOrderAccessor* GetLevelOrderAccessor()
{
    static const GENERATED_ArkUILevelOrderAccessor LevelOrderAccessorImpl {
        LevelOrderAccessor::DestroyPeerImpl,
        LevelOrderAccessor::ConstructImpl,
        LevelOrderAccessor::GetFinalizerImpl,
        LevelOrderAccessor::ClampImpl,
        LevelOrderAccessor::GetOrderImpl,
    };
    return &LevelOrderAccessorImpl;
}
}
