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
#ifndef FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H
#define FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H

#include <mutex>
#include <vector>

#include "ui/base/referenced.h"

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/generated/interface/arkoala_api_generated.h"
#include "core/interfaces/native/implementation/render_node_peer_impl.h"

struct FrameNodePeer {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> node;

    OHOS::Ace::WeakPtr<OHOS::Ace::NG::FrameNode> weakNode;
    int32_t nodeId_ = -1;
    inline static std::map<int32_t, std::shared_ptr<FrameNodePeer>> peerMap_;
    inline static std::mutex peerMapMutex_;

    static FrameNodePeer* Create(Ark_UIContext uiContext)
    {
        return new FrameNodePeer;
    }

    static FrameNodePeer* Create(const OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode>& src)
    {
        std::lock_guard<std::mutex> lock(peerMapMutex_);
        auto it = peerMap_.find(src->GetId());
        if (it != peerMap_.end()) {
            return (it->second).get();
        }
        auto frameNode = std::make_shared<FrameNodePeer>();
        if (src->IsArkTsFrameNode()) {
            frameNode->node = src;
        } else {
            frameNode->weakNode = OHOS::Ace::WeakPtr(src);
        }
        peerMap_.emplace(src->GetId(), frameNode);
        frameNode->nodeId_ = src->GetId();
        return frameNode.get();
    }

    static FrameNodePeer* Create(OHOS::Ace::NG::FrameNode* src)
    {
        return Create(OHOS::Ace::AceType::Claim<OHOS::Ace::NG::FrameNode>(src));
    }

    static void Destroy(FrameNodePeer* peer)
    {
        if (peer) {
            std::lock_guard<std::mutex> lock(peerMapMutex_);
            peerMap_.erase(peer->nodeId_);
        }
    }

    static OHOS::Ace::RefPtr<OHOS::Ace::NG::FrameNode> GetFrameNodeByPeer(FrameNodePeer* peer)
    {
        if (peer == nullptr) {
            return nullptr;
        }
        if (peer->node) {
            return peer->node;
        } else if (peer->weakNode.Upgrade()) {
            return peer->weakNode.Upgrade();
        } else {
            return nullptr;
        }
    }

    RenderNodePeer* GetRenderNodePeer()
    {
        return OHOS::Ace::NG::PeerUtils::CreatePeer<RenderNodePeer>(GetFrameNodeByPeer(this));
    }
};
#endif // FOUNDATION_ARKUI_ACE_ENGINE_FRAMEWORKS_CORE_INTERFACES_NATIVE_IMPL_FRAME_NODE_PEER_IMPL_H
