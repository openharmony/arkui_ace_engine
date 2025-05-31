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

#include <optional>
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/property/calc_length.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/view_model_bridge.h"

namespace OHOS::Ace::NG {
enum class ExpandMode : uint32_t {
    NOT_EXPAND = 0,
    EXPAND,
    LAZY_EXPAND,
};
}
std::map<int32_t, FrameNodePeer> FrameNodePeer::peerMap_;
namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
Opt_Number GetOptNumberFromDimension(const std::optional<Dimension>& dimension)
{
    return dimension.has_value() ? Converter::ArkValue<Opt_Number>(dimension->Value())
                                 : Converter::ArkValue<Opt_Number>(std::nullopt);
}
Opt_LengthUnit GetOptLengthUnitFromDimension(const std::optional<Dimension>& dimension)
{
    return dimension.has_value() ? Converter::ArkValue<Opt_LengthUnit>(dimension->Unit())
                                 : Converter::ArkValue<Opt_LengthUnit>(std::nullopt);
}
Opt_Number GetOptNumberFromCalcLength(const std::optional<CalcLength>& calcLength)
{
    return calcLength.has_value() ? GetOptNumberFromDimension(calcLength->GetDimension())
                                  : Converter::ArkValue<Opt_Number>(std::nullopt);
}
Opt_LengthUnit GetOptLengthUnitFromCalcLength(const std::optional<CalcLength>& calcLength)
{
    return calcLength.has_value() ? GetOptLengthUnitFromDimension(calcLength->GetDimension())
                                  : Converter::ArkValue<Opt_LengthUnit>(std::nullopt);
}
} // namespace
namespace FrameNodeAccessor {
void DestroyPeerImpl(Ark_FrameNode peer)
{
    FrameNodePeer::Destroy(peer);
}
Ark_FrameNode CtorImpl(Ark_UIContext uiContext)
{
    auto peer = FrameNodePeer::Create(uiContext);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    peer->node = NG::CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
    peer->node->SetExclusiveEventForChild(true);
    peer->node->SetIsArkTsFrameNode(true);
    FrameNodePeer::peerMap_.emplace(nodeId, *peer);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, false);
    auto isModifiable = peerNode->GetTag() == "CustomFrameNode";
    return Converter::ArkValue<Ark_Boolean>(isModifiable);
}
void AppendChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto childPeerNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_VOID(childPeerNode);
    auto childNode = AceType::DynamicCast<UINode>(childPeerNode);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr && childNode->GetParent() != currentUINodeRef) {
        return;
    }
    currentUINodeRef->AddChild(childNode);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(Ark_FrameNode peer,
                          Ark_FrameNode child,
                          Ark_FrameNode sibling)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto childPeerNode = FrameNodePeer::GetFrameNodeByPeer(child);
    CHECK_NULL_VOID(child);
    auto childNode = AceType::DynamicCast<UINode>(childPeerNode);
    if (childNode->GetParent() != nullptr) {
        return;
    }
    auto index = -1;
    if (sibling) {
        auto siblingPeerNode = FrameNodePeer::GetFrameNodeByPeer(sibling);
        auto siblingNode = AceType::DynamicCast<UINode>(siblingPeerNode);
        index = currentUINodeRef->GetChildIndex(siblingNode);
    }

    currentUINodeRef->AddChild(childNode, index + 1);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode node)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto nodePeer = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_VOID(nodePeer);
    auto childNode = AceType::DynamicCast<UINode>(nodePeer);
    CHECK_NULL_VOID(childNode);

    currentUINodeRef->RemoveChild(childNode);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void ClearChildrenImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);
    currentUINodeRef->Clean();
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
FrameNode* GetChildNode(RefPtr<FrameNode> nodeRef, int32_t index, int32_t expandMode)
{
    auto expandModeResult = static_cast<ExpandMode>(expandMode);
    if (expandModeResult == ExpandMode::EXPAND) {
        nodeRef->GetAllChildrenWithBuild(false);
    }
    if (expandModeResult == ExpandMode::EXPAND || expandModeResult == ExpandMode::NOT_EXPAND) {
        return nodeRef->GetFrameNodeChildByIndex(index, false, expandModeResult == ExpandMode::EXPAND);
    } else {
        auto child = nodeRef->GetFrameNodeChildByIndexWithoutBuild(index);
        if (child == nullptr) {
            return GetChildNode(nodeRef, index, 1);
        } else {
            return child;
        }
    }
}
Ark_FrameNode GetChildImpl(Ark_FrameNode peer,
                           const Ark_Number* index,
                           const Ark_Number* expandMode)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    CHECK_NULL_RETURN(index, nullptr);
    auto indexInt = Converter::Convert<int32_t>(*index);
    CHECK_NULL_RETURN(indexInt > -1, nullptr);
    auto expandModeInt = Converter::Convert<int32_t>(*expandMode);
    auto child = GetChildNode(peerNode, indexInt, expandModeInt);
    CHECK_NULL_RETURN(child, nullptr);
    return FrameNodePeer::Create(child);
}
Ark_FrameNode GetFirstChildImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    peerNode->GetAllChildrenWithBuild(false);
    auto child = peerNode->GetFrameNodeChildByIndex(0, false, true);
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
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    auto parent = GetParentNode(peerNode);
    CHECK_NULL_RETURN(parent, nullptr);
    parent->GetAllChildrenWithBuild(false);
    auto index = parent->GetChildTrueIndex(peerNode);
    CHECK_NULL_RETURN(index > -1, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, true);
    CHECK_NULL_RETURN(sibling, nullptr);
    return FrameNodePeer::Create(sibling);
}
Ark_FrameNode GetPreviousSiblingImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    auto parent = GetParentNode(peerNode);
    CHECK_NULL_RETURN(parent, nullptr);
    parent->GetAllChildrenWithBuild(false);
    auto index = parent->GetChildTrueIndex(peerNode);
    CHECK_NULL_RETURN(index > 0, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, true);
    CHECK_NULL_RETURN(sibling, nullptr);
    return FrameNodePeer::Create(sibling);
}
Ark_FrameNode GetParentImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    auto parent = GetParentNode(peerNode);
    CHECK_NULL_RETURN(parent, nullptr);
    return FrameNodePeer::Create(parent);
}
Ark_Int32 GetChildrenCountImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, 0);
    return peerNode->GetAllChildrenWithBuild(false).size();
}
void DisposeImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);
    LOGW("FrameNodeAccessor::DisposeImpl - behavior can be wrong. No specification to this API.");
    auto parent = GetParentNode(peerNode);
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(currentUINodeRef);
}
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(1);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, errValue);
    auto opacity = ViewAbstract::GetOpacity(Referenced::RawPtr(peerNode));
    return Converter::ArkValue<Ark_Number>(opacity);
}
Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode,  Converter::ArkValue<Ark_Position>(OffsetF()));
    auto offset = peerNode->GetPositionToWindowWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_FrameNode GetFrameNodeByKeyImpl(const Ark_String* name)
{
    auto valueName = Converter::Convert<std::string>(*name);
    auto node = NG::Inspector::GetFrameNodeByKey(valueName, true);
    CHECK_NULL_RETURN(node, nullptr);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(node));
}
Ark_Number GetIdByFrameNodeImpl(Ark_FrameNode peer, Ark_FrameNode node)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    auto nodePeerNode = FrameNodePeer::GetFrameNodeByPeer(node);
    CHECK_NULL_RETURN(nodePeerNode, errValue);
    auto currentNode = AceType::DynamicCast<UINode>(nodePeerNode);
    CHECK_NULL_RETURN(currentNode, errValue);
    auto nodeId = currentNode->GetId();
    return Converter::ArkValue<Ark_Number>(nodeId);
}
void MoveToImpl(Ark_FrameNode peer, Ark_FrameNode targetParent, const Ark_Number* index)
{
    auto indexInt = Converter::Convert<int32_t>(*index);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto moveNode = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(moveNode);
    auto targetParentPeerNode = FrameNodePeer::GetFrameNodeByPeer(targetParent);
    CHECK_NULL_VOID(targetParentPeerNode);
    auto toNode = AceType::DynamicCast<UINode>(targetParentPeerNode);
    CHECK_NULL_VOID(toNode);
    static const std::vector<const char*> nodeTypeArray = {
        OHOS::Ace::V2::STACK_ETS_TAG,
        OHOS::Ace::V2::XCOMPONENT_ETS_TAG,
        OHOS::Ace::V2::EMBEDDED_COMPONENT_ETS_TAG,
    };
    auto pos = std::find(nodeTypeArray.begin(), nodeTypeArray.end(), moveNode->GetTag());
    if (pos == nodeTypeArray.end()) {
        return;
    }
    auto oldParent = moveNode->GetParent();
    moveNode->setIsMoving(true);
    if (oldParent) {
        oldParent->RemoveChild(moveNode);
        oldParent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    int32_t childCount = toNode->TotalChildCount();
    if (indexInt >= childCount || indexInt < 0) {
        toNode->AddChild(moveNode);
    } else {
        auto indexChild = toNode->GetChildAtIndex(indexInt);
        toNode->AddChildBefore(moveNode, indexChild);
    }
    toNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    moveNode->setIsMoving(false);
}
Ark_Number GetFirstChildIndexWithoutExpandImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, errValue);
    auto child = peerNode->GetFrameNodeChildByIndex(0, false, false);
    CHECK_NULL_RETURN(child, errValue);
    auto* childNode = reinterpret_cast<FrameNode*>(child);
    auto childRef = Referenced::Claim<FrameNode>(childNode);
    auto index = peer->node->GetFrameNodeIndex(childRef, true);
    return Converter::ArkValue<Ark_Number>(index);
}
Ark_Number GetLastChildIndexWithoutExpandImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, errValue);
    size_t size = static_cast<size_t>(peerNode->GetTotalChildCountWithoutExpanded());
    CHECK_NULL_RETURN(size > 0, errValue);
    auto child = peerNode->GetFrameNodeChildByIndex(size - 1, false, false);
    CHECK_NULL_RETURN(child, errValue);
    auto* childNode = reinterpret_cast<FrameNode*>(child);
    auto childRef = Referenced::Claim<FrameNode>(childNode);
    auto index = peerNode->GetFrameNodeIndex(childRef, true);
    return Converter::ArkValue<Ark_Number>(index);
}
Ark_FrameNode GetAttachedFrameNodeByIdImpl(const Ark_String* id)
{
    auto valueId = Converter::Convert<std::string>(*id);
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("GetAttachedNodeHandleById doesn't run on UI thread");
    }
    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(valueId);
    CHECK_NULL_RETURN(node, nullptr);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(node));
}
Ark_FrameNode GetFrameNodeByIdImpl(const Ark_Number* id)
{
    auto idInt = Converter::Convert<int32_t>(*id);
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(idInt);
    CHECK_NULL_RETURN(node, nullptr);
    auto nodeRef = AceType::DynamicCast<NG::FrameNode>(node);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(nodeRef));
}
Ark_FrameNode GetFrameNodeByUniqueIdImpl(const Ark_Number* id)
{
    auto idInt = Converter::Convert<int32_t>(*id);
    auto node = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(idInt));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() == "root" || node->GetTag() == "stage" || node->GetTag() == "page") {
        return nullptr;
    }

    if (!AceType::InstanceOf<NG::FrameNode>(node) || AceType::InstanceOf<NG::CustomMeasureLayoutNode>(node)) {
        auto parent = node->GetParent();
        if (parent && parent->GetTag() == V2::RECYCLE_VIEW_ETS_TAG) {
            parent = parent->GetParent();
        }
        if (parent && parent->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            node = parent;
        } else {
            node = node->GetFrameChildByIndexWithoutExpanded(0);
        }
    }
    CHECK_NULL_RETURN(node, nullptr);
    auto nodeRef = AceType::DynamicCast<NG::FrameNode>(node);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(nodeRef));
}
void ReuseImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    currentUINodeRef->OnReuse();
}
void RecycleImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    currentUINodeRef->OnRecycle();
}
Ark_RenderNode GetRenderNodeImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer && peer->node, nullptr);
    return peer->GetRenderNodePeer();
}
Ark_NativePointer GetFrameNodePtrImpl(Ark_FrameNode node)
{
    auto nodeRf = FrameNodePeer::GetFrameNodeByPeer(node);
    return AceType::RawPtr(nodeRf);
}
static GENERATED_Ark_NodeType ParseNodeType(std::string& type)
{
    static const std::unordered_map<std::string, GENERATED_Ark_NodeType> typeMap = { { "List", GENERATED_ARKUI_LIST } };
    GENERATED_Ark_NodeType nodeType = GENERATED_ARKUI_CUSTOM_NODE;
    auto iter = typeMap.find(type);
    if (iter != typeMap.end()) {
        nodeType = iter->second;
    }
    return nodeType;
}
Ark_FrameNode CreateTypedFrameNodeImpl(const Ark_String* type)
{
    auto valueType = Converter::Convert<std::string>(*type);
    int32_t nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    GENERATED_Ark_NodeType nodeType = ParseNodeType(valueType);
    if (nodeType == GENERATED_ARKUI_CUSTOM_NODE) {
        return nullptr;
    }
    auto node =  OHOS::Ace::NG::GeneratedBridge::CreateNode(nodeType, nodeId, 0);
    CHECK_NULL_RETURN(node, nullptr);
    auto newNode = AceType::Claim(reinterpret_cast<FrameNode*>(node));
    newNode->SetIsArkTsFrameNode(true);
    newNode->DecRefCount();
    return FrameNodePeer::Create(newNode);
}
Ark_String GetNodeTypeImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_String>("");
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, errValue);
    static std::string nodeType = peerNode->GetTag();
    return Converter::ArkValue<Ark_String>(nodeType);
}
Ark_Position GetPositionToParentImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToParentImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto currFrameRect = frameNode->GetRectWithRender();
    auto offset = currFrameRect.GetOffset();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Position GetPositionToScreenImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToScreenImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToScreen();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Position GetPositionToWindowImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToWindowImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetOffsetRelativeToWindow();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Position GetPositionToParentWithTransformImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToParentWithTransformImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToParentWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Position GetPositionToScreenWithTransformImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToScreenWithTransformImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToScreenWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Position GetPositionToWindowWithTransform1Impl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetPositionToWindowWithTransform1Impl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetPositionToWindowWithTransform();
    offset.SetX(PipelineBase::Px2VpWithCurrentDensity(offset.GetX()));
    offset.SetY(PipelineBase::Px2VpWithCurrentDensity(offset.GetY()));
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_Size GetMeasuredSizeImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetMeasuredSizeImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto size = frameNode->GetGeometryNode()->GetFrameSize();
    return Converter::ArkValue<Ark_Size>(size);
}
Ark_Position GetLayoutPositionImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetLayoutPositionImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto offset = frameNode->GetGeometryNode()->GetMarginFrameOffset();
    return Converter::ArkValue<Ark_Position>(offset);
}
Ark_EdgesLengthMetrics GetUserConfigBorderWidthImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigBorderWidthImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto borderWidth = ViewAbstract::GetLayoutBorderWidth(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromDimension(borderWidth.topDimen),
        .topUnit = GetOptLengthUnitFromDimension(borderWidth.topDimen),
        .left = GetOptNumberFromDimension(borderWidth.leftDimen),
        .leftUnit = GetOptLengthUnitFromDimension(borderWidth.leftDimen),
        .bottom = GetOptNumberFromDimension(borderWidth.bottomDimen),
        .bottomUnit = GetOptLengthUnitFromDimension(borderWidth.bottomDimen),
        .right = GetOptNumberFromDimension(borderWidth.rightDimen),
        .rightUnit = GetOptLengthUnitFromDimension(borderWidth.rightDimen),
    };
    return retValue;
}
Ark_EdgesLengthMetrics GetUserConfigPaddingImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigPaddingImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto padding = ViewAbstract::GetPadding(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromCalcLength(padding.top),
        .topUnit = GetOptLengthUnitFromCalcLength(padding.top),
        .left = GetOptNumberFromCalcLength(padding.left),
        .leftUnit = GetOptLengthUnitFromCalcLength(padding.left),
        .bottom = GetOptNumberFromCalcLength(padding.bottom),
        .bottomUnit = GetOptLengthUnitFromCalcLength(padding.bottom),
        .right = GetOptNumberFromCalcLength(padding.right),
        .rightUnit = GetOptLengthUnitFromCalcLength(padding.right),
    };
    return retValue;
}
Ark_EdgesLengthMetrics GetUserConfigMarginImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigMarginImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto margin = ViewAbstract::GetMargin(AceType::RawPtr(frameNode));
    Ark_EdgesLengthMetrics retValue = {
        .top = GetOptNumberFromCalcLength(margin.top),
        .topUnit = GetOptLengthUnitFromCalcLength(margin.top),
        .left = GetOptNumberFromCalcLength(margin.left),
        .leftUnit = GetOptLengthUnitFromCalcLength(margin.left),
        .bottom = GetOptNumberFromCalcLength(margin.bottom),
        .bottomUnit = GetOptLengthUnitFromCalcLength(margin.bottom),
        .right = GetOptNumberFromCalcLength(margin.right),
        .rightUnit = GetOptLengthUnitFromCalcLength(margin.right),
    };
    return retValue;
}
Ark_SizeLengthMetrics GetUserConfigSizeImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetUserConfigSizeImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto size = ViewAbstract::GetConfigSize(AceType::RawPtr(frameNode));
    if (!size.has_value()) {
        return {};
    }
    Ark_SizeLengthMetrics retValue = {
        .width = GetOptNumberFromCalcLength(size->Width()),
        .widthUnit = GetOptLengthUnitFromCalcLength(size->Width()),
        .height = GetOptNumberFromCalcLength(size->Height()),
        .heightUnit = GetOptLengthUnitFromCalcLength(size->Height())
    };
    return retValue;
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
        FrameNodeAccessor::GetIdByFrameNodeImpl,
        FrameNodeAccessor::MoveToImpl,
        FrameNodeAccessor::GetFirstChildIndexWithoutExpandImpl,
        FrameNodeAccessor::GetLastChildIndexWithoutExpandImpl,
        FrameNodeAccessor::GetAttachedFrameNodeByIdImpl,
        FrameNodeAccessor::GetFrameNodeByIdImpl,
        FrameNodeAccessor::GetFrameNodeByUniqueIdImpl,
        FrameNodeAccessor::ReuseImpl,
        FrameNodeAccessor::RecycleImpl,
        FrameNodeAccessor::GetRenderNodeImpl,
        FrameNodeAccessor::GetFrameNodePtrImpl,
        FrameNodeAccessor::CreateTypedFrameNodeImpl,
        FrameNodeAccessor::GetNodeTypeImpl,
        FrameNodeAccessor::GetPositionToParentImpl,
        FrameNodeAccessor::GetPositionToScreenImpl,
        FrameNodeAccessor::GetPositionToWindowImpl,
        FrameNodeAccessor::GetPositionToParentWithTransformImpl,
        FrameNodeAccessor::GetPositionToScreenWithTransformImpl,
        FrameNodeAccessor::GetPositionToWindowWithTransform1Impl,
        FrameNodeAccessor::GetMeasuredSizeImpl,
        FrameNodeAccessor::GetLayoutPositionImpl,
        FrameNodeAccessor::GetUserConfigBorderWidthImpl,
        FrameNodeAccessor::GetUserConfigPaddingImpl,
        FrameNodeAccessor::GetUserConfigMarginImpl,
        FrameNodeAccessor::GetUserConfigSizeImpl,
    };
    return &FrameNodeAccessorImpl;
}

}
