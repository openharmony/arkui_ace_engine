/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FrameNodeAccessor {
void DestroyPeerImpl(FrameNodePeer* peer)
{
    peer->node = nullptr;
    delete peer;
}
Ark_NativePointer CtorImpl(const Ark_UIContext* uiContext)
{
    auto peer = new FrameNodePeer(uiContext);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    peer->node = NG::CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
    peer->node->SetExclusiveEventForChild(true);
    peer->node->SetIsArkTsFrameNode(true);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->node, false);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_RETURN(currentUINodeRef, false);
    auto isModifiable = currentUINodeRef->GetTag() == "CustomFrameNode";
    return Converter::ArkValue<Ark_Boolean>(isModifiable);
}
void AppendChildImpl(FrameNodePeer* peer,
                     const Ark_FrameNode* node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(node->ptr);
    auto childNode = reinterpret_cast<UINode*>(node->ptr);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr && childNode->GetParent() != currentUINodeRef) {
        return;
    }
    currentUINodeRef->AddChild(Referenced::Claim<UINode>(childNode));
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(FrameNodePeer* peer,
                          const Ark_FrameNode* child,
                          const Ark_FrameNode* sibling)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(child);
    CHECK_NULL_VOID(child->ptr);
    auto childNode = reinterpret_cast<UINode*>(child->ptr);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr && childNode->GetParent() != currentUINodeRef) {
        return;
    }

    CHECK_NULL_VOID(sibling);
    CHECK_NULL_VOID(sibling->ptr);
    auto siblingNode = reinterpret_cast<UINode*>(sibling->ptr);
    auto index = currentUINodeRef->GetChildIndex(Referenced::Claim<UINode>(siblingNode));
    currentUINodeRef->AddChild(Referenced::Claim<UINode>(childNode), index + 1);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(FrameNodePeer* peer,
                     const Ark_FrameNode* node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(node);
    CHECK_NULL_VOID(node->ptr);
    auto childNode = reinterpret_cast<UINode*>(node->ptr);
    CHECK_NULL_VOID(childNode);

    currentUINodeRef->RemoveChild(Referenced::Claim<UINode>(childNode));
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void ClearChildrenImpl(FrameNodePeer* peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);
    currentUINodeRef->Clean();
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_NativePointer GetChildImpl(FrameNodePeer* peer,
                               const Ark_Number* index)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    CHECK_NULL_RETURN(index, nullptr);
    auto indexInt = Converter::Convert<int32_t>(*index);
    CHECK_NULL_RETURN(indexInt > 0, nullptr);
    LOGW("FrameNodeAccessor::GetChildImpl work only for case: IsExpanded is false");
    return peer->node->GetFrameNodeChildByIndex(indexInt, false, false);
}
Ark_NativePointer GetFirstChildImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto child = peer->node->GetFirstChild();
    CHECK_NULL_RETURN(child, nullptr);
    return AceType::DynamicCast<FrameNode>(child.GetRawPtr());
}

RefPtr<FrameNode> GetParentNode(RefPtr<FrameNode> nodeRef)
{
    auto parent = nodeRef->GetParent();
    while (parent != nullptr && !AceType::InstanceOf<FrameNode>(parent)) {
        parent = parent->GetParent();
    }
    return (parent == nullptr || parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::STAGE_ETS_TAG)
               ? nullptr : AceType::DynamicCast<FrameNode>(parent);
}

Ark_NativePointer GetNextSiblingImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, nullptr);
    LOGW("FrameNodeAccessor::GetNextSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index > -1, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, false);
    return sibling;
}
Ark_NativePointer GetPreviousSiblingImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, nullptr);
    LOGW("FrameNodeAccessor::GetPreviousSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index > 0, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, false);
    return sibling;
}
Ark_NativePointer GetParentImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    return parent.GetRawPtr();
}
Ark_Int32 GetChildrenCountImpl(FrameNodePeer* peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->node, 0);
    LOGW("FrameNodeAccessor::GetChildrenCountImpl work only for case: IsExpanded is false");
    return peer->node->GetTotalChildCountWithoutExpanded();
}
void DisposeImpl(FrameNodePeer* peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    LOGW("FrameNodeAccessor::DisposeImpl - behavior can be wrong. No specification to this API.");
    if (peer->node->IsOnMainTree()) {
        peer->node->DetachFromMainTree();
    } else {
        peer->node->DetachContext();
    }
}
} // FrameNodeAccessor
const GENERATED_ArkUIFrameNodeAccessor* GetFrameNodeAccessor()
{
    static const GENERATED_ArkUIFrameNodeAccessor FrameNodeAccessorImpl {
        FrameNodeAccessor::DestroyPeerImpl,
        FrameNodeAccessor::CtorImpl,
        FrameNodeAccessor::GetFinalizerImpl,
        FrameNodeAccessor::IsModifiableImpl,
        FrameNodeAccessor::AppendChildImpl,
        FrameNodeAccessor::InsertChildAfterImpl,
        FrameNodeAccessor::RemoveChildImpl,
        FrameNodeAccessor::ClearChildrenImpl,
        FrameNodeAccessor::GetChildImpl,
        FrameNodeAccessor::GetFirstChildImpl,
        FrameNodeAccessor::GetNextSiblingImpl,
        FrameNodeAccessor::GetPreviousSiblingImpl,
        FrameNodeAccessor::GetParentImpl,
        FrameNodeAccessor::GetChildrenCountImpl,
        FrameNodeAccessor::DisposeImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
