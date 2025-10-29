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
#include "core/components_ng/syntax/node_content_peer.h"

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {
constexpr int32_t ERROR_CODE_NO_ERROR = 0;
constexpr int32_t ERROR_CODE_NODE_IS_ADOPTED = 106206;
constexpr int32_t ERROR_CODE_PARAM_INVALID = 401;
} // namespace

namespace NodeContentExtenderAccessor {
void DestroyPeerImpl(Ark_NativePointer peer)
{
    auto peerImpl = reinterpret_cast<NodeContentPeer*>(peer);
    if (peerImpl) {
        delete peerImpl;
    }
}

Ark_NativePointer ConstructorNodeContentImpl()
{
    auto NodeContent = AceType::MakeRefPtr<NG::NodeContent>();
    auto peer = NodeContentPeer::Create(NodeContent);
    return peer;
}

Ark_NativePointer GetDestroyImpl()
{
    return reinterpret_cast<void*>(&DestroyPeerImpl);
}

Ark_Float64 AddFrameNodeImpl(Ark_NativePointer peer, Ark_NativePointer node)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    auto peerImpl = reinterpret_cast<NodeContentPeer*>(peer);
    CHECK_NULL_RETURN(peerImpl->content, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    CHECK_NULL_RETURN(node, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    auto frameNodePeer = reinterpret_cast<FrameNodePeer*>(node);
    CHECK_NULL_RETURN(frameNodePeer->node, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    if (frameNodePeer->node->IsAdopted()) {
        return Converter::ArkValue<Ark_Float64>(ERROR_CODE_NODE_IS_ADOPTED);
    }
    auto nodeContent = AceType::DynamicCast<NG::NodeContent>(peerImpl->content);
    CHECK_NULL_RETURN(nodeContent, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    auto childNode = AceType::DynamicCast<UINode>(frameNodePeer->node);
    CHECK_NULL_RETURN(childNode, Converter::ArkValue<Ark_Float64>(ERROR_CODE_PARAM_INVALID));
    nodeContent->AddNode(AceType::RawPtr(childNode));
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    return Converter::ArkValue<Ark_Float64>(ERROR_CODE_NO_ERROR);
}

Ark_Boolean RemoveFrameNodeImpl(Ark_NativePointer peer, Ark_NativePointer node)
{
    CHECK_NULL_RETURN(peer, false);
    auto peerImpl = reinterpret_cast<NodeContentPeer*>(peer);
    CHECK_NULL_RETURN(peerImpl->content, false);
    CHECK_NULL_RETURN(node, false);
    auto frameNodePeer = reinterpret_cast<FrameNodePeer*>(node);
    CHECK_NULL_RETURN(frameNodePeer->node, false);
    auto nodeContent = AceType::DynamicCast<NG::NodeContent>(peerImpl->content);
    CHECK_NULL_RETURN(nodeContent, false);
    auto childNode = AceType::DynamicCast<UINode>(frameNodePeer->node);
    CHECK_NULL_RETURN(childNode, false);
    childNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_PARENT);
    nodeContent->RemoveNode(AceType::RawPtr(childNode));
    return true;
}
} // namespace NodeContentExtenderAccessor
const GENERATED_ArkUINodeContentExtenderAccessor* GetNodeContentExtenderAccessor()
{
    static const GENERATED_ArkUINodeContentExtenderAccessor NodeContentExtenderAccessorImpl {
        NodeContentExtenderAccessor::ConstructorNodeContentImpl,
        NodeContentExtenderAccessor::GetDestroyImpl,
        NodeContentExtenderAccessor::AddFrameNodeImpl,
        NodeContentExtenderAccessor::RemoveFrameNodeImpl,
    };
    return &NodeContentExtenderAccessorImpl;
}

} // namespace OHOS::Ace::NG::GeneratedModifier
