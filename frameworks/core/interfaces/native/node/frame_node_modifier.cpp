/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/frame_node_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector.h"

namespace OHOS::Ace::NG {
ArkUI_Bool IsModifiable(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    auto* frameNode = AceType::DynamicCast<UINode>(currentNode);
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetTag() == "CustomFrameNode";
}

RefPtr<FrameNode> GetParentNode(UINode* node)
{
    auto uiNode = AceType::Claim<UINode>(node);
    auto parent = uiNode->GetParent();
    while (parent != nullptr && !AceType::InstanceOf<FrameNode>(parent)) {
        parent = parent->GetParent();
    }
    return (parent == nullptr || parent->GetTag() == "page" || parent->GetTag() == "stage")
               ? nullptr
               : AceType::DynamicCast<FrameNode>(parent);
}

ArkUI_Bool AppendChildInFrameNode(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, true);
    auto* childNode = reinterpret_cast<UINode*>(child);
    auto childRef = Referenced::Claim<UINode>(childNode);
    CHECK_NULL_RETURN(childRef, true);
    if (childRef->GetParent() != nullptr && childRef->GetParent() != currentNode) {
        return false;
    }
    currentNode->AddChild(childRef);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    return true;
}

ArkUI_Bool InsertChildAfterInFrameNode(ArkUINodeHandle node, ArkUINodeHandle child, ArkUINodeHandle sibling)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, true);
    auto* childNode = reinterpret_cast<UINode*>(child);
    CHECK_NULL_RETURN(childNode, true);
    if (childNode->GetParent() != nullptr && childNode->GetParent() != currentNode) {
        return false;
    }
    auto index = -1;
    auto* siblingNode = reinterpret_cast<UINode*>(sibling);
    index = currentNode->GetChildIndex(Referenced::Claim<UINode>(siblingNode));
    currentNode->AddChild(Referenced::Claim<UINode>(childNode), index + 1);
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
    return true;
}

void RemoveChildInFrameNode(ArkUINodeHandle node, ArkUINodeHandle child)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto* childNode = reinterpret_cast<FrameNode*>(child);
    currentNode->RemoveChild(Referenced::Claim<UINode>(childNode));
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

void ClearChildrenInFrameNode(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    currentNode->Clean();
    currentNode->MarkNeedFrameFlushDirty(NG::PROPERTY_UPDATE_MEASURE);
}

ArkUI_Uint32 GetChildrenCount(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, 0);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, 0);
    return frameNode->GetAllChildrenWithBuild(false).size();
}

ArkUINodeHandle GetChild(ArkUINodeHandle node, ArkUI_Int32 index)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->GetAllChildrenWithBuild(false);
    auto child = frameNode->GetChildByIndex(index);
    auto childNode = AceType::DynamicCast<FrameNode>(child);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(childNode));
}

ArkUINodeHandle GetFirst(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->GetAllChildrenWithBuild(false);
    auto child = frameNode->GetChildByIndex(0);
    auto childNode = AceType::DynamicCast<FrameNode>(child);
    CHECK_NULL_RETURN(childNode, nullptr);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(childNode));
}

ArkUINodeHandle GetNextSibling(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto parent = GetParentNode(currentNode);
    CHECK_NULL_RETURN(parent, nullptr);
    parent->GetAllChildrenWithBuild(false);
    auto index = parent->GetChildTrueIndex(Referenced::Claim<FrameNode>(currentNode));
    auto sibling = parent->GetChildByIndex(index + 1);
    auto childNode = AceType::DynamicCast<FrameNode>(sibling);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(childNode));
}

ArkUINodeHandle GetPreviousSibling(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto parent = GetParentNode(currentNode);
    CHECK_NULL_RETURN(parent, nullptr);
    parent->GetAllChildrenWithBuild(false);
    auto index = parent->GetChildTrueIndex(Referenced::Claim<FrameNode>(currentNode));
    auto sibling = parent->GetChildByIndex(index - 1);
    auto childNode = AceType::DynamicCast<FrameNode>(sibling);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(childNode));
}

ArkUINodeHandle GetParent(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto parent = GetParentNode(currentNode);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(parent));
}

ArkUI_Int32 GetIdByNodePtr(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, -1);
    auto nodeId = currentNode->GetId();
    return nodeId;
}

ArkUI_Float32* GetPositionToParent(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto currFrameRect = currentNode->GetRectWithRender();
    auto offset = currFrameRect.GetOffset();
    ArkUI_Float32* ret = new ArkUI_Float32[2];
    ret[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    ret[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return ret;
}

ArkUI_Float32* GetPositionToWindow(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto offset = currentNode->GetOffsetRelativeToWindow();
    ArkUI_Float32* ret = new ArkUI_Float32[2];
    ret[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
    ret[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    return ret;
}

ArkUINodeHandle GetFrameNodeById(ArkUI_Int32 nodeId)
{
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetFrameNodeByKey(ArkUI_CharPtr key)
{
    auto node = NG::Inspector::GetFrameNodeByKey(key);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

void PropertyUpdate(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    if (uiNode) {
        uiNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    }
}

ArkUINodeHandle GetLast(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto size = frameNode->GetAllChildrenWithBuild(false).size();
    auto child = frameNode->GetChildByIndex(size - 1);
    auto childNode = AceType::DynamicCast<FrameNode>(child);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(childNode));
}

namespace NodeModifier {
const ArkUIFrameNodeModifier* GetFrameNodeModifier()
{
    static const ArkUIFrameNodeModifier modifier = { IsModifiable, AppendChildInFrameNode, InsertChildAfterInFrameNode,
        RemoveChildInFrameNode, ClearChildrenInFrameNode, GetChildrenCount, GetChild, GetFirst, GetNextSibling,
        GetPreviousSibling, GetParent, GetIdByNodePtr, GetPositionToParent, GetPositionToWindow,
        GetFrameNodeById, GetFrameNodeByKey, PropertyUpdate, GetLast };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
