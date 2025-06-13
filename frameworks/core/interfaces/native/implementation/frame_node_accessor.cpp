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

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FrameNodeAccessor {
void DestroyPeerImpl(Ark_FrameNode peer)
{
    FrameNodePeer::Destroy(peer);
}
Ark_FrameNode CtorImpl(const Ark_UIContext* uiContext)
{
    auto peer = FrameNodePeer::Create(uiContext);
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
Ark_Boolean IsModifiableImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, false);
    CHECK_NULL_RETURN(peer->node, false);
    auto isModifiable = peer->node->GetTag() == "CustomFrameNode";
    return Converter::ArkValue<Ark_Boolean>(isModifiable);
}
void AppendChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(node);
    auto childNode = AceType::DynamicCast<UINode>(node->node);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr) {
        return;
    }
    currentUINodeRef->AddChild(childNode);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(Ark_FrameNode peer,
                          Ark_FrameNode child,
                          Ark_FrameNode sibling)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(child);
    auto childNode = AceType::DynamicCast<UINode>(child->node);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr) {
        return;
    }
    CHECK_NULL_VOID(sibling);
    auto siblingNode = AceType::DynamicCast<UINode>(sibling->node);
    auto index = currentUINodeRef->GetChildIndex(siblingNode);
    currentUINodeRef->AddChild(childNode, index + 1);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);

    CHECK_NULL_VOID(node);
    auto childNode = AceType::DynamicCast<UINode>(node->node);
    CHECK_NULL_VOID(childNode);

    currentUINodeRef->RemoveChild(childNode);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void ClearChildrenImpl(Ark_FrameNode peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);
    currentUINodeRef->Clean();
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
Ark_FrameNode GetChildImpl(Ark_FrameNode peer,
                           const Ark_Number* index)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    CHECK_NULL_RETURN(index, nullptr);
    auto indexInt = Converter::Convert<int32_t>(*index);
    CHECK_NULL_RETURN(indexInt > -1, nullptr);
    LOGW("FrameNodeAccessor::GetChildImpl work only for case: IsExpanded is false");
    return FrameNodePeer::Create(peer->node->GetFrameNodeChildByIndex(indexInt, false, false));
}
Ark_FrameNode GetFirstChildImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto child = peer->node->GetFirstChild();
    CHECK_NULL_RETURN(child, nullptr);
    return FrameNodePeer::Create(AceType::DynamicCast<FrameNode>(child));
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
Ark_FrameNode GetNextSiblingImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, nullptr);
    LOGW("FrameNodeAccessor::GetNextSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index > -1, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, false);
    return FrameNodePeer::Create(sibling);
}
Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_RETURN(parent, nullptr);
    LOGW("FrameNodeAccessor::GetPreviousSiblingImpl work only for case: IsExpanded is false");
    auto index = parent->GetFrameNodeIndex(peer->node, false);
    CHECK_NULL_RETURN(index > 0, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, false);
    return FrameNodePeer::Create(sibling);
}
Ark_FrameNode GetParentImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    CHECK_NULL_RETURN(peer->node, nullptr);
    auto parent = GetParentNode(peer->node);
    return FrameNodePeer::Create(parent);
}
Ark_Int32 GetChildrenCountImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, 0);
    CHECK_NULL_RETURN(peer->node, 0);
    LOGW("FrameNodeAccessor::GetChildrenCountImpl work only for case: IsExpanded is false");
    return peer->node->GetTotalChildCountWithoutExpanded();
}
void DisposeImpl(Ark_FrameNode peer)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->node);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peer->node);
    CHECK_NULL_VOID(currentUINodeRef);
    LOGW("FrameNodeAccessor::DisposeImpl - behavior can be wrong. No specification to this API.");
    auto parent = GetParentNode(peer->node);
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(currentUINodeRef);
}
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(1);
    CHECK_NULL_RETURN(peer && peer->node, errValue);
    auto opacity = ViewAbstract::GetOpacity(Referenced::RawPtr(peer->node));
    return Converter::ArkValue<Ark_Number>(opacity);
}
Ark_GraphicsPosition GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer && peer->node,  Converter::ArkValue<Ark_GraphicsPosition>(OffsetF()));
    auto offset = peer->node->GetPositionToWindowWithTransform();
    return Converter::ArkValue<Ark_GraphicsPosition>(offset);
}
Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
{
    auto valueName = Converter::Convert<std::string>(*name);
    auto node = NG::Inspector::GetFrameNodeByKey(valueName, true);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(node));
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
        FrameNodeAccessor::GetOpacityImpl,
        FrameNodeAccessor::GetPositionToWindowWithTransformImpl,
        FrameNodeAccessor::GetFrameNodeByKeyImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
