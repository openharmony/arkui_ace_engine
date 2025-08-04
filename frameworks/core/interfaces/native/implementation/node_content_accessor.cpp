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

#include "arkoala_api_generated.h"
#include "node_content_peer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace NodeContentAccessor {
void DestroyPeerImpl(Ark_NodeContent peer)
{
    auto peerImpl = reinterpret_cast<NodeContentPeer*>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}
Ark_NodeContent ConstructImpl()
{
    auto NodeContent = AceType::MakeRefPtr<NG::NodeContent>();
    auto peer = NodeContentPeer::Create(NodeContent);
    return peer;
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void AddFrameNodeImpl(Ark_NodeContent peer,
                      Ark_FrameNode node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->content);
    CHECK_NULL_VOID(node);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_VOID(frameNode);
    auto nodeContent = AceType::DynamicCast<NG::NodeContent>(peer->content);
    CHECK_NULL_VOID(nodeContent);
    auto childNode = AceType::DynamicCast<UINode>(frameNode);
    CHECK_NULL_VOID(childNode);
    nodeContent->AddNode(AceType::RawPtr(childNode));
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
}
void RemoveFrameNodeImpl(Ark_NodeContent peer,
                         Ark_FrameNode node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->content);
    CHECK_NULL_VOID(node);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_VOID(frameNode);
    auto nodeContent = AceType::DynamicCast<NG::NodeContent>(peer->content);
    CHECK_NULL_VOID(nodeContent);
    auto childNode = AceType::DynamicCast<UINode>(frameNode);
    CHECK_NULL_VOID(childNode);
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    nodeContent->RemoveNode(AceType::RawPtr(childNode));
}
} // NodeContentAccessor
const GENERATED_ArkUINodeContentAccessor* GetNodeContentAccessor()
{
    static const GENERATED_ArkUINodeContentAccessor NodeContentAccessorImpl {
        NodeContentAccessor::DestroyPeerImpl,
        NodeContentAccessor::ConstructImpl,
        NodeContentAccessor::GetFinalizerImpl,
        NodeContentAccessor::AddFrameNodeImpl,
        NodeContentAccessor::RemoveFrameNodeImpl,
    };
    return &NodeContentAccessorImpl;
}

}
