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
#include  "core/interfaces/native/implementation/layout_policy_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutPolicyAccessor {
namespace {
Ark_LayoutPolicy CreateOwnedPolicyPeer(OHOS::Ace::LayoutCalPolicy layoutPolicy)
{
    return PeerUtils::CreatePeer<LayoutPolicyPeer>(layoutPolicy);
}

Ark_LayoutPolicy GetMatchParentPeer()
{
    static Ark_LayoutPolicy matchParentPeer =
        PeerUtils::CreatePeer<LayoutPolicyPeer>(OHOS::Ace::LayoutCalPolicy::MATCH_PARENT, false);
    return matchParentPeer;
}

Ark_LayoutPolicy GetWrapContentPeer()
{
    static Ark_LayoutPolicy wrapContentPeer =
        PeerUtils::CreatePeer<LayoutPolicyPeer>(OHOS::Ace::LayoutCalPolicy::WRAP_CONTENT, false);
    return wrapContentPeer;
}

Ark_LayoutPolicy GetFixAtIdealSizePeer()
{
    static Ark_LayoutPolicy fixAtIdealSizePeer =
        PeerUtils::CreatePeer<LayoutPolicyPeer>(OHOS::Ace::LayoutCalPolicy::FIX_AT_IDEAL_SIZE, false);
    return fixAtIdealSizePeer;
}

Ark_LayoutPolicy GetCachedPolicyPeer(OHOS::Ace::LayoutCalPolicy layoutPolicy)
{
    // Lazily initialize only the requested predefined policy peer, then reuse
    // that process-lifetime object on subsequent getter calls.
    switch (layoutPolicy) {
        case OHOS::Ace::LayoutCalPolicy::MATCH_PARENT:
            return GetMatchParentPeer();
        case OHOS::Ace::LayoutCalPolicy::WRAP_CONTENT:
            return GetWrapContentPeer();
        case OHOS::Ace::LayoutCalPolicy::FIX_AT_IDEAL_SIZE:
            return GetFixAtIdealSizePeer();
        default:
            return nullptr;
    }
}
} // namespace

void DestroyPeerImpl(Ark_LayoutPolicy peer)
{
    // Cached peers are reused across calls, so only owned instances created by
    // construct() should go through the normal destroy path.
    if (peer && !peer->isOwned) {
        return;
    }
    PeerUtils::DestroyPeer(peer);
}
Ark_LayoutPolicy ConstructImpl()
{
    // Construct an independent default object so callers can own and release it
    // without affecting the cached predefined policy peers.
    return CreateOwnedPolicyPeer(OHOS::Ace::LayoutCalPolicy::NO_MATCH);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_LayoutPolicy GetMatchParentImpl()
{
    return GetCachedPolicyPeer(OHOS::Ace::LayoutCalPolicy::MATCH_PARENT);
}
Ark_LayoutPolicy GetWrapContentImpl()
{
    return GetCachedPolicyPeer(OHOS::Ace::LayoutCalPolicy::WRAP_CONTENT);
}
Ark_LayoutPolicy GetFixAtIdealSizeImpl()
{
    return GetCachedPolicyPeer(OHOS::Ace::LayoutCalPolicy::FIX_AT_IDEAL_SIZE);
}
} // LayoutPolicyAccessor
const GENERATED_ArkUILayoutPolicyAccessor* GetLayoutPolicyAccessor()
{
    static const GENERATED_ArkUILayoutPolicyAccessor LayoutPolicyAccessorImpl {
        LayoutPolicyAccessor::DestroyPeerImpl,
        LayoutPolicyAccessor::ConstructImpl,
        LayoutPolicyAccessor::GetFinalizerImpl,
        LayoutPolicyAccessor::GetMatchParentImpl,
        LayoutPolicyAccessor::GetWrapContentImpl,
        LayoutPolicyAccessor::GetFixAtIdealSizeImpl,
    };
    return &LayoutPolicyAccessorImpl;
}
}
