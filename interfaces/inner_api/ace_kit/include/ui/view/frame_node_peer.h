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
#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_PEER_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_PEER_H

#include <mutex>
#include <vector>

#include "ui/base/referenced.h"
#include "ui/view/frame_node.h"

namespace OHOS::Ace::Kit {
struct FrameNodePeer {
    RefPtr<FrameNode> node;

    WeakPtr<FrameNode> weakNode;
    int32_t nodeId_ = -1;
    inline static std::map<int32_t, std::shared_ptr<FrameNodePeer>> peerMap_;
    inline static std::mutex peerMapMutex_;

    static RefPtr<FrameNode> GetFrameNodeByPeer(FrameNodePeer* peer)
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
};
} // namespace OHOS::Ace::Kit
#endif // #ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_VIEW_FRAME_NODE_PEER_H
