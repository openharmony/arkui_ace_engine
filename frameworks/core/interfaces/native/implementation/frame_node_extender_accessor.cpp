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
#include "core/components_ng/property/measure_property.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"
#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/view_model_bridge.h"
#include "core/interfaces/native/implementation/ui_common_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
enum class ExpandMode : uint32_t {
    NOT_EXPAND = 0,
    EXPAND,
    LAZY_EXPAND,
};
// same as inner defines in property.h
typedef enum {
    ARKUI_DIRTY_FLAG_MEASURE = 0b1,
    ARKUI_DIRTY_FLAG_LAYOUT = 0b10,
    /** mark the node need to do attribute diff to drive update. */
    ARKUI_DIRTY_FLAG_ATTRIBUTE_DIFF = 0b100,
    ARKUI_DIRTY_FLAG_MEASURE_SELF = 0b1000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT = 0b10000,
    ARKUI_DIRTY_FLAG_MEASURE_BY_CHILD_REQUEST = 0b100000,
    ARKUI_DIRTY_FLAG_RENDER = 0b1000000,
    ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_CHILD = 0b1000000000,
} ArkUIDirtyFlag;
} // namespace OHOS::Ace::NG
std::map<int32_t, std::shared_ptr<FrameNodePeer>> FrameNodePeer::peerMap_;
std::mutex FrameNodePeer::peerMapMutex_;

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FrameNodeExtenderAccessor {
void DestroyPeerImpl(Ark_FrameNode peer)
{
    FrameNodePeer::Destroy(peer);
}
Ark_NativePointer ConstructorFrameNodeImpl()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NG::CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
    node->SetExclusiveEventForChild(true);
    node->SetIsArkTsFrameNode(true);
    auto peer = FrameNodePeer::Create(node);
    return peer;
}
Ark_NativePointer GetDestroyImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsModifiableImpl(Ark_NativePointer peer)
{
    auto frameNodePeer = reinterpret_cast<FrameNodePeer*>(peer);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    CHECK_NULL_RETURN(peerNode, false);
    auto isModifiable = peerNode->GetTag() == "CustomFrameNode";
    return Converter::ArkValue<Ark_Boolean>(isModifiable);
}
void AppendChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode child)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto childPeerNode = FrameNodePeer::GetFrameNodeByPeer(child);
    CHECK_NULL_VOID(childPeerNode);
    auto childNode = AceType::DynamicCast<UINode>(childPeerNode);
    CHECK_NULL_VOID(childNode);
    if (childNode->GetParent() != nullptr && childNode->GetParent() != currentUINodeRef) {
        return;
    }
    currentUINodeRef->AddChild(childNode);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void InsertChildAfterImpl(Ark_NativePointer peer,
                          Ark_NativePointer child,
                          Ark_NativePointer sibling)
{
    auto peerNodePeer = reinterpret_cast<FrameNodePeer*>(peer);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peerNodePeer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto childPeerNodePeer = reinterpret_cast<FrameNodePeer*>(child);
    auto childPeerNode = FrameNodePeer::GetFrameNodeByPeer(childPeerNodePeer);
    CHECK_NULL_VOID(childPeerNode);
    auto childNode = AceType::DynamicCast<UINode>(childPeerNode);
    if (childNode->GetParent() != nullptr) {
        return;
    }
    auto index = -1;
    if (sibling) {
        auto siblingPeer = reinterpret_cast<FrameNodePeer*>(sibling);
        auto siblingPeerNode = FrameNodePeer::GetFrameNodeByPeer(siblingPeer);
        auto siblingNode = AceType::DynamicCast<UINode>(siblingPeerNode);
        index = currentUINodeRef->GetChildIndex(siblingNode);
    }

    currentUINodeRef->AddChild(childNode, index + 1);
    currentUINodeRef->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}
void RemoveChildImpl(Ark_FrameNode peer,
                     Ark_FrameNode child)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto currentUINodeRef = AceType::DynamicCast<UINode>(peerNode);
    CHECK_NULL_VOID(currentUINodeRef);

    auto nodePeer = FrameNodePeer::GetFrameNodeByPeer(child);
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

Ark_NativePointer GetChildImpl(Ark_FrameNode peer,
                           const Ark_Number* index,
                           const Ark_Number* expandMode)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, nullptr);
    CHECK_NULL_RETURN(index, nullptr);
    auto indexInt = Converter::Convert<int32_t>(*index);
    if (indexInt < 0) {
        return nullptr;
    }
    auto expandModeInt = Converter::Convert<int32_t>(*expandMode);
    auto child = GetChildNode(peerNode, indexInt, expandModeInt);
    CHECK_NULL_RETURN(child, nullptr);
    return FrameNodePeer::Create(child);
}
Ark_NativePointer GetFirstChildImpl(Ark_FrameNode peer)
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

Ark_NativePointer GetNextSiblingImpl(Ark_FrameNode peer)
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
Ark_NativePointer GetPreviousSiblingImpl(Ark_FrameNode peer)
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
Ark_NativePointer GetParentImpl(Ark_FrameNode peer)
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
    auto parent = GetParentNode(peerNode);
    CHECK_NULL_VOID(parent);
    parent->RemoveChild(currentUINodeRef);
}
Ark_Vector2 GetPositionToWindowImpl(Ark_FrameNode peer)
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
    return Converter::ArkValue<Ark_Vector2>(offset);
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
Ark_Size GetMeasuredSizeImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetMeasuredSizeImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto size = geometryNode->GetFrameSize();
    return Converter::ArkValue<Ark_Size>(size);
}
Ark_Vector2 GetLayoutPositionImpl(Ark_FrameNode peer)
{
    if (!peer) {
        LOGW("This frameNode nullptr when GetLayoutPositionImpl!");
        return {};
    }
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto geometryNode = frameNode->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, {});
    auto offset = geometryNode->GetMarginFrameOffset();
    return Converter::ArkValue<Ark_Vector2>(offset);
}
Ark_String GetIdImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto inspectorId = frameNode->GetInspectorId().value_or("");
    return Converter::ArkValue<Ark_String>(inspectorId, Converter::FC);
}
Ark_Int32 GetUniqueIdImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, 0);
    return Converter::ArkValue<Ark_Int32>(frameNode->GetId());
}
Ark_String GetNodeTypeImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto nodeType = frameNode->GetTag();
    return Converter::ArkValue<Ark_String>(nodeType, Converter::FC);
}
Ark_Number GetOpacityImpl(Ark_FrameNode peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(1);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode, errValue);
    auto opacity = ViewAbstract::GetOpacity(Referenced::RawPtr(peerNode));
    return Converter::ArkValue<Ark_Number>(opacity);
}
Ark_Boolean IsVisibleImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    auto isVisible = frameNode->IsVisible();
    auto parentNode = frameNode->GetParent();
    while (isVisible && parentNode) {
        auto parentFrameNode = AceType::DynamicCast<FrameNode>(parentNode);
        if (parentFrameNode) {
            isVisible = isVisible && parentFrameNode->IsVisible();
        }
        parentNode = parentNode->GetParent();
    }
    return isVisible;
}
Ark_Boolean IsClipToFrameImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    return ViewAbstract::GetClip(Referenced::RawPtr(frameNode));
}
Ark_Boolean IsAttachedImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    auto isOnMainTree = frameNode->IsOnMainTree();
    return isOnMainTree;
}
Ark_String GetInspectorInfoImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, {});
    auto inspectorInfo = NG::Inspector::GetInspectorOfNode(frameNode);
    return Converter::ArkValue<Ark_String>(inspectorInfo, Converter::FC);
}
void InvalidateImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CustomFrameNodePattern>();
    CHECK_NULL_VOID(pattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
}
void DisposeTreeImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(frameNode);
    auto parent = frameNode->GetParent();
    if (parent && parent->GetTag() == "NodeContainer") {
        auto pattern = AceType::DynamicCast<NodeContainerPattern>(parent);
        CHECK_NULL_VOID(pattern);
        pattern->CleanChild();
    } else if (parent) {
        parent->RemoveChild(frameNode);
    }
}
Ark_Boolean SetCrossLanguageOptionsImpl(Ark_FrameNode peer, Ark_Boolean options)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    static const std::vector<const char*> nodeTypeArray = { OHOS::Ace::V2::SCROLL_ETS_TAG,
        OHOS::Ace::V2::SWIPER_ETS_TAG, OHOS::Ace::V2::LIST_ETS_TAG, OHOS::Ace::V2::LIST_ITEM_ETS_TAG,
        OHOS::Ace::V2::LIST_ITEM_GROUP_ETS_TAG, OHOS::Ace::V2::WATERFLOW_ETS_TAG, OHOS::Ace::V2::FLOW_ITEM_ETS_TAG,
        OHOS::Ace::V2::GRID_ETS_TAG, OHOS::Ace::V2::GRID_ITEM_ETS_TAG, OHOS::Ace::V2::TEXT_ETS_TAG,
        OHOS::Ace::V2::TEXTINPUT_ETS_TAG, OHOS::Ace::V2::TEXTAREA_ETS_TAG, OHOS::Ace::V2::COLUMN_ETS_TAG,
        OHOS::Ace::V2::ROW_ETS_TAG, OHOS::Ace::V2::STACK_ETS_TAG, OHOS::Ace::V2::FLEX_ETS_TAG,
        OHOS::Ace::V2::RELATIVE_CONTAINER_ETS_TAG, OHOS::Ace::V2::PROGRESS_ETS_TAG,
        OHOS::Ace::V2::LOADING_PROGRESS_ETS_TAG, OHOS::Ace::V2::IMAGE_ETS_TAG, OHOS::Ace::V2::BUTTON_ETS_TAG,
        OHOS::Ace::V2::CHECKBOX_ETS_TAG, OHOS::Ace::V2::RADIO_ETS_TAG, OHOS::Ace::V2::SLIDER_ETS_TAG,
        OHOS::Ace::V2::TOGGLE_ETS_TAG, OHOS::Ace::V2::XCOMPONENT_ETS_TAG };
    auto pos = std::find(nodeTypeArray.begin(), nodeTypeArray.end(), frameNode->GetTag());
    if (pos == nodeTypeArray.end()) {
        return false;
    }
    frameNode->SetIsCrossLanguageAttributeSetting(options);
    return true;
}
Ark_Boolean GetCrossLanguageOptionsImpl(Ark_FrameNode peer)
{
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->isCrossLanguageAttributeSetting();
}
void SetMeasuredSizeImpl(Ark_FrameNode peer,
                         const Ark_Size* size)
{
    CHECK_NULL_VOID(size);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    auto widthValue = Converter::Convert<int32_t>(size->width);
    auto heightValue = Converter::Convert<int32_t>(size->height);
    peerNode->GetGeometryNode()->SetFrameWidth(widthValue);
    peerNode->GetGeometryNode()->SetFrameHeight(heightValue);
}
void SetLayoutPositionImpl(Ark_FrameNode peer,
                           const Ark_Position* position)
{
    CHECK_NULL_VOID(position);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
}
void MeasureImpl(Ark_FrameNode peer,
                 const Ark_LayoutConstraint* constraint)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    CHECK_NULL_VOID(constraint);
    Ark_Size maxSize = constraint->maxSize;
    Ark_Size minSize = constraint->minSize;
    Ark_Size percentReference = constraint->percentReference;
    auto minWidth = Converter::Convert<float>(constraint->minSize.width);
    auto minHeight = Converter::Convert<float>(constraint->minSize.height);
    auto maxWidth = Converter::Convert<float>(constraint->maxSize.width);
    auto maxHeight = Converter::Convert<float>(constraint->maxSize.height);
    auto percentReferenceWidth = Converter::Convert<float>(constraint->percentReference.width);
    auto percentReferenceHeight = Converter::Convert<float>(constraint->percentReference.height);
    std::optional<LayoutConstraintF> constraintF = std::make_optional<LayoutConstraintF>();
    // minWidth
    constraintF->minSize.SetWidth(minWidth);
    // minHeight
    constraintF->minSize.SetHeight(minHeight);
    // maxWidth
    constraintF->maxSize.SetWidth(maxWidth);
    // maxHeight
    constraintF->maxSize.SetHeight(maxHeight);
    // minWidth == maxWidth
    if (minWidth == maxWidth) {
        constraintF->selfIdealSize.SetWidth(minWidth);
    }
    // minHeight == maxHeight
    if (minHeight == maxHeight) {
        constraintF->selfIdealSize.SetHeight(minHeight);
    }
    // percentReferenceWidth
    constraintF->percentReference.SetWidth(percentReferenceWidth);
    // percentReferenceHeight
    constraintF->percentReference.SetHeight(percentReferenceHeight);
    peerNode->SetActive(true);
    peerNode->Measure(constraintF);
}
void LayoutImpl(Ark_FrameNode peer,
                const Ark_Position* position)
{
    CHECK_NULL_VOID(position);
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    peerNode->Layout();
}
void SetNeedsLayoutImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_VOID(peerNode);
    peerNode->MarkDirtyNode(ARKUI_DIRTY_FLAG_MEASURE_SELF_AND_PARENT);
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
Ark_Position GetPositionToWindowWithTransformImpl(Ark_FrameNode peer)
{
    auto peerNode = FrameNodePeer::GetFrameNodeByPeer(peer);
    CHECK_NULL_RETURN(peerNode,  Converter::ArkValue<Ark_Position>(OffsetF()));
    auto offset = peerNode->GetPositionToWindowWithTransform();
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
Ark_NativePointer GetFrameNodeByKeyImpl(const Ark_String* name)
{
    auto valueName = Converter::Convert<std::string>(*name);
    auto node = NG::Inspector::GetFrameNodeByKey(valueName, true);
    CHECK_NULL_RETURN(node, nullptr);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(node));
}
Ark_Number GetIdByFrameNodeImpl(Ark_NativePointer node)
{
    auto nodePeer = reinterpret_cast<FrameNodePeer*>(node);
    const auto errValue = Converter::ArkValue<Ark_Number>(-1);
    auto currentNode = FrameNodePeer::GetFrameNodeByPeer(nodePeer);
    CHECK_NULL_RETURN(currentNode, errValue);
    auto nodeId = currentNode->GetId();
    return Converter::ArkValue<Ark_Number>(nodeId);
}
void MoveToImpl(Ark_FrameNode peer,
                Ark_FrameNode targetParent,
                const Ark_Number* index)
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
    auto index = peerNode->GetFrameNodeIndex(childRef, true);
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
Ark_NativePointer GetAttachedFrameNodeByIdImpl(const Ark_String* id)
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
Ark_NativePointer GetFrameNodeByIdImpl(const Ark_Number* id)
{
    auto idInt = Converter::Convert<int32_t>(*id);
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(idInt);
    CHECK_NULL_RETURN(node, nullptr);
    auto nodeRef = AceType::DynamicCast<NG::FrameNode>(node);
    return FrameNodePeer::Create(OHOS::Ace::AceType::RawPtr(nodeRef));
}
Ark_NativePointer GetFrameNodeByUniqueIdImpl(Ark_Int32 id)
{
    auto idInt = Converter::Convert<int32_t>(id);
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
Ark_NativePointer GetFrameNodePtrImpl(Ark_FrameNode node)
{
    auto nodeRf = FrameNodePeer::GetFrameNodeByPeer(node);
    return AceType::RawPtr(nodeRf);
}

static GENERATED_Ark_NodeType ParseNodeType(std::string& type)
{
    static const std::unordered_map<std::string, GENERATED_Ark_NodeType> typeMap = {
        { "List", GENERATED_ARKUI_LIST },
        { "ListItem", GENERATED_ARKUI_LIST_ITEM },
        { "ListItemGroup", GENERATED_ARKUI_LIST_ITEM_GROUP },
        { "Scroll", GENERATED_ARKUI_SCROLL },
        { "WaterFlow", GENERATED_ARKUI_WATER_FLOW },
        { "FlowItem", GENERATED_ARKUI_FLOW_ITEM },
        { "Grid", GENERATED_ARKUI_GRID },
        { "GridItem", GENERATED_ARKUI_GRID_ITEM },
        { "Column", GENERATED_ARKUI_COLUMN },
        { "Row", GENERATED_ARKUI_ROW },
        { "Stack", GENERATED_ARKUI_STACK },
        { "Flex", GENERATED_ARKUI_FLEX },
        { "RelativeContainer", GENERATED_ARKUI_RELATIVE_CONTAINER },
        { "GridRow", GENERATED_ARKUI_GRID_ROW },
        { "GridCol", GENERATED_ARKUI_GRID_COL },
        { "Divider", GENERATED_ARKUI_DIVIDER },
        { "Blank", GENERATED_ARKUI_BLANK },
        { "Search", GENERATED_ARKUI_SEARCH },
        { "Swiper", GENERATED_ARKUI_SWIPER },
        { "TextArea", GENERATED_ARKUI_TEXT_AREA },
        { "TextInput", GENERATED_ARKUI_TEXT_INPUT },
        { "Text", GENERATED_ARKUI_TEXT },
        { "Marquee", GENERATED_ARKUI_MARQUEE },
        { "SymbolGlyph", GENERATED_ARKUI_SYMBOL_GLYPH },
        { "XComponent", GENERATED_ARKUI_XCOMPONENT },
        { "QRCode", GENERATED_ARKUI_QRCODE },
        { "Badge", GENERATED_ARKUI_BADGE },
        { "Progress", GENERATED_ARKUI_PROGRESS },
        { "LoadingProgress", GENERATED_ARKUI_LOADING_PROGRESS },
        { "TextClock", GENERATED_ARKUI_TEXT_CLOCK },
        { "TextTimer", GENERATED_ARKUI_TEXT_TIMER },
        { "Image", GENERATED_ARKUI_IMAGE },
        { "Button", GENERATED_ARKUI_BUTTON },
        { "CheckboxGroup", GENERATED_ARKUI_CHECKBOX_GROUP },
        { "Checkbox", GENERATED_ARKUI_CHECKBOX },
        { "Radio", GENERATED_ARKUI_RADIO },
        { "Rating", GENERATED_ARKUI_RATING },
        { "Select", GENERATED_ARKUI_SELECT },
        { "Slider", GENERATED_ARKUI_SLIDER },
        { "Toggle", GENERATED_ARKUI_TOGGLE },
    };
    GENERATED_Ark_NodeType nodeType = GENERATED_ARKUI_CUSTOM_NODE;
    auto iter = typeMap.find(type);
    if (iter != typeMap.end()) {
        nodeType = iter->second;
    }
    return nodeType;
}

Ark_NativePointer CreateTypedFrameNodeImpl(const Ark_String* type)
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
    return static_cast<Ark_FrameNode>(FrameNodePeer::Create(newNode));
}
Ark_NativePointer CreateByRawPtrImpl(Ark_NativePointer rawPtr)
{
    auto frameNode = reinterpret_cast<FrameNode*>(rawPtr);
    auto peer = FrameNodePeer::Create(frameNode);
    return reinterpret_cast<Ark_NativePointer>(peer);
}
Ark_NativePointer UnWrapRawPtrImpl(Ark_NativePointer peerNode)
{
    auto frameNodePeer = reinterpret_cast<FrameNodePeer*>(peerNode);
    auto frameNode = FrameNodePeer::GetFrameNodeByPeer(frameNodePeer);
    auto frameNodeRaw = Referenced::RawPtr(frameNode);
    return reinterpret_cast<Ark_NativePointer>(frameNodeRaw);
}
Ark_UICommonEvent GetCommonEventImpl(Ark_FrameNode peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto ret = PeerUtils::CreatePeer<UICommonEventPeer>();
    ret->node = peer->node;
    return ret;
}
Ark_NativePointer GetRenderNodeImpl(Ark_NativePointer peer)
{
    auto nodePeer = reinterpret_cast<FrameNodePeer*>(peer);
    return nodePeer->GetRenderNodePeer();
}
} // FrameNodeExtenderAccessor
const GENERATED_ArkUIFrameNodeExtenderAccessor* GetFrameNodeExtenderAccessor()
{
    static const GENERATED_ArkUIFrameNodeExtenderAccessor FrameNodeExtenderAccessorImpl {
        FrameNodeExtenderAccessor::ConstructorFrameNodeImpl,
        FrameNodeExtenderAccessor::GetDestroyImpl,
        FrameNodeExtenderAccessor::DestroyPeerImpl,
        FrameNodeExtenderAccessor::IsModifiableImpl,
        FrameNodeExtenderAccessor::AppendChildImpl,
        FrameNodeExtenderAccessor::InsertChildAfterImpl,
        FrameNodeExtenderAccessor::RemoveChildImpl,
        FrameNodeExtenderAccessor::ClearChildrenImpl,
        FrameNodeExtenderAccessor::GetChildImpl,
        FrameNodeExtenderAccessor::GetFirstChildImpl,
        FrameNodeExtenderAccessor::GetNextSiblingImpl,
        FrameNodeExtenderAccessor::GetPreviousSiblingImpl,
        FrameNodeExtenderAccessor::GetParentImpl,
        FrameNodeExtenderAccessor::GetChildrenCountImpl,
        FrameNodeExtenderAccessor::DisposeImpl,
        FrameNodeExtenderAccessor::GetPositionToWindowImpl,
        FrameNodeExtenderAccessor::GetPositionToParentImpl,
        FrameNodeExtenderAccessor::GetMeasuredSizeImpl,
        FrameNodeExtenderAccessor::GetLayoutPositionImpl,
        FrameNodeExtenderAccessor::GetIdImpl,
        FrameNodeExtenderAccessor::GetUniqueIdImpl,
        FrameNodeExtenderAccessor::GetNodeTypeImpl,
        FrameNodeExtenderAccessor::GetOpacityImpl,
        FrameNodeExtenderAccessor::IsVisibleImpl,
        FrameNodeExtenderAccessor::IsClipToFrameImpl,
        FrameNodeExtenderAccessor::IsAttachedImpl,
        FrameNodeExtenderAccessor::GetInspectorInfoImpl,
        FrameNodeExtenderAccessor::InvalidateImpl,
        FrameNodeExtenderAccessor::DisposeTreeImpl,
        FrameNodeExtenderAccessor::SetCrossLanguageOptionsImpl,
        FrameNodeExtenderAccessor::GetCrossLanguageOptionsImpl,
        FrameNodeExtenderAccessor::SetMeasuredSizeImpl,
        FrameNodeExtenderAccessor::SetLayoutPositionImpl,
        FrameNodeExtenderAccessor::MeasureImpl,
        FrameNodeExtenderAccessor::LayoutImpl,
        FrameNodeExtenderAccessor::SetNeedsLayoutImpl,
        FrameNodeExtenderAccessor::GetPositionToScreenImpl,
        FrameNodeExtenderAccessor::GetPositionToWindowWithTransformImpl,
        FrameNodeExtenderAccessor::GetPositionToParentWithTransformImpl,
        FrameNodeExtenderAccessor::GetPositionToScreenWithTransformImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByKeyImpl,
        FrameNodeExtenderAccessor::GetIdByFrameNodeImpl,
        FrameNodeExtenderAccessor::MoveToImpl,
        FrameNodeExtenderAccessor::GetFirstChildIndexWithoutExpandImpl,
        FrameNodeExtenderAccessor::GetLastChildIndexWithoutExpandImpl,
        FrameNodeExtenderAccessor::GetAttachedFrameNodeByIdImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByIdImpl,
        FrameNodeExtenderAccessor::GetFrameNodeByUniqueIdImpl,
        FrameNodeExtenderAccessor::ReuseImpl,
        FrameNodeExtenderAccessor::RecycleImpl,
        FrameNodeExtenderAccessor::GetFrameNodePtrImpl,
        FrameNodeExtenderAccessor::CreateTypedFrameNodeImpl,
        FrameNodeExtenderAccessor::CreateByRawPtrImpl,
        FrameNodeExtenderAccessor::UnWrapRawPtrImpl,
        FrameNodeExtenderAccessor::GetCommonEventImpl,
        FrameNodeExtenderAccessor::GetRenderNodeImpl,
    };
    return &FrameNodeExtenderAccessorImpl;
}

}
