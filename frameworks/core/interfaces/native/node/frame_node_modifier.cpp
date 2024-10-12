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

#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
ArkUI_Bool IsModifiable(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    auto* frameNode = AceType::DynamicCast<UINode>(currentNode);
    CHECK_NULL_RETURN(frameNode, false);
    return frameNode->GetTag() == "CustomFrameNode";
}

ArkUINodeHandle CreateFrameNode()
{
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto node = NG::CustomFrameNode::GetOrCreateCustomFrameNode(nodeId);
    node->SetExclusiveEventForChild(true);
    node->SetIsArkTsFrameNode(true);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

void InvalidateInFrameNode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(AceType::InstanceOf<CustomFrameNode>(frameNode));
    auto pattern = frameNode->GetPattern<CustomFrameNodePattern>();
    CHECK_NULL_VOID(pattern);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    pattern->Invalidate();
    renderContext->RequestNextFrame();
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
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto* childNode = reinterpret_cast<UINode*>(child);
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

ArkUI_Uint32 GetChildrenCount(ArkUINodeHandle node, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, 0);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, 0);
    if (isExpanded) {
        frameNode->GetAllChildrenWithBuild(false);
    }
    return isExpanded ? frameNode->GetAllChildrenWithBuild(false).size()
                      : frameNode->GetTotalChildCountWithoutExpanded();
}

ArkUINodeHandle GetChild(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(index >= 0, nullptr);
    if (isExpanded) {
        frameNode->GetAllChildrenWithBuild(false);
    }
    auto child = frameNode->GetFrameNodeChildByIndex(index, false, isExpanded);
    return reinterpret_cast<ArkUINodeHandle>(child);
}

ArkUINodeHandle GetFirst(ArkUINodeHandle node, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    if (isExpanded) {
        frameNode->GetAllChildrenWithBuild(false);
    }
    auto child = frameNode->GetFrameNodeChildByIndex(0, false, isExpanded);
    return reinterpret_cast<ArkUINodeHandle>(child);
}

ArkUINodeHandle GetNextSibling(ArkUINodeHandle node, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto parent = GetParentNode(currentNode);
    CHECK_NULL_RETURN(parent, nullptr);
    auto index = -1;
    if (isExpanded) {
        parent->GetAllChildrenWithBuild(false);
        index = parent->GetChildTrueIndex(Referenced::Claim<FrameNode>(currentNode));
    } else {
        index = parent->GetFrameNodeIndex(Referenced::Claim<FrameNode>(currentNode), false);
    }
    CHECK_NULL_RETURN(index > -1, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index + 1, false, isExpanded);
    return reinterpret_cast<ArkUINodeHandle>(sibling);
}

ArkUINodeHandle GetPreviousSibling(ArkUINodeHandle node, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto parent = GetParentNode(currentNode);
    auto index = -1;
    if (isExpanded) {
        parent->GetAllChildrenWithBuild(false);
        index = parent->GetChildTrueIndex(Referenced::Claim<FrameNode>(currentNode));
    } else {
        index = parent->GetFrameNodeIndex(Referenced::Claim<FrameNode>(currentNode), false);
    }
    CHECK_NULL_RETURN(index > 0, nullptr);
    auto sibling = parent->GetFrameNodeChildByIndex(index - 1, false, isExpanded);
    return reinterpret_cast<ArkUINodeHandle>(sibling);
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

void GetPositionToParent(ArkUINodeHandle node, ArkUI_Float32 (*parentOffset)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto currFrameRect = currentNode->GetRectWithRender();
    auto offset = currFrameRect.GetOffset();
    if (useVp) {
        (*parentOffset)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*parentOffset)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*parentOffset)[0] = offset.GetX();
        (*parentOffset)[1] = offset.GetY();
    }
}

void GetPositionToScreen(ArkUINodeHandle node, ArkUI_Float32 (*screenPosition)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto offset = currentNode->GetPositionToScreen();
    if (useVp) {
        (*screenPosition)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*screenPosition)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*screenPosition)[0] = offset.GetX();
        (*screenPosition)[1] = offset.GetY();
    }
}

void GetPositionToWindow(ArkUINodeHandle node, ArkUI_Float32 (*windowOffset)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto offset = currentNode->GetOffsetRelativeToWindow();
    if (useVp) {
        (*windowOffset)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*windowOffset)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*windowOffset)[0] = offset.GetX();
        (*windowOffset)[1] = offset.GetY();
    }
}

void GetPositionToParentWithTransform(ArkUINodeHandle node, ArkUI_Float32 (*parentPosition)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto offset = currentNode->GetPositionToParentWithTransform();
    if (useVp) {
        (*parentPosition)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*parentPosition)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*parentPosition)[0] = offset.GetX();
        (*parentPosition)[1] = offset.GetY();
    }
}

void GetPositionToScreenWithTransform(ArkUINodeHandle node, ArkUI_Float32 (*screenPosition)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto offset = currentNode->GetPositionToScreenWithTransform();
    if (useVp) {
        (*screenPosition)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*screenPosition)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*screenPosition)[0] = offset.GetX();
        (*screenPosition)[1] = offset.GetY();
    }
}

void GetPositionToWindowWithTransform(ArkUINodeHandle node, ArkUI_Float32 (*windowPosition)[2], ArkUI_Bool useVp)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto offset = currentNode->GetPositionToWindowWithTransform();
    if (useVp) {
        (*windowPosition)[0] = PipelineBase::Px2VpWithCurrentDensity(offset.GetX());
        (*windowPosition)[1] = PipelineBase::Px2VpWithCurrentDensity(offset.GetY());
    } else {
        (*windowPosition)[0] = offset.GetX();
        (*windowPosition)[1] = offset.GetY();
    }
}

ArkUI_Float32* GetMeasuredSize(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto offset = currentNode->GetGeometryNode()->GetFrameSize();
    ArkUI_Float32* ret = new ArkUI_Float32[2];
    ret[0] = offset.Width();
    ret[1] = offset.Height();
    return ret;
}

ArkUI_Float32* GetLayoutPosition(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto offset = currentNode->GetGeometryNode()->GetMarginFrameOffset();
    ArkUI_Float32* ret = new ArkUI_Float32[2];
    ret[0] = offset.GetX();
    ret[1] = offset.GetY();
    return ret;
}

ArkUI_CharPtr GetInspectorId(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, "");
    auto inspectorIdProp = currentNode->GetInspectorId();
    if (inspectorIdProp.has_value()) {
        static std::string inspectorId;
        inspectorId = inspectorIdProp.value();
        return inspectorId.c_str();
    }

    return "";
}

ArkUI_CharPtr GetNodeType(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, "");
    static std::string nodeType;
    nodeType = currentNode->GetTag();
    return nodeType.c_str();
}

ArkUI_Bool IsVisible(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    auto isVisible = currentNode->IsVisible();
    auto parentNode = currentNode->GetParent();
    while (isVisible && parentNode && AceType::InstanceOf<FrameNode>(*parentNode)) {
        isVisible = isVisible && AceType::DynamicCast<FrameNode>(parentNode)->IsVisible();
        parentNode = parentNode->GetParent();
    }
    return isVisible;
}

ArkUI_Bool IsAttached(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    return currentNode->IsOnMainTree();
}

ArkUI_CharPtr GetInspectorInfo(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, "{}");
    static std::string inspectorInfo;
    inspectorInfo = NG::Inspector::GetInspectorOfNode(OHOS::Ace::AceType::Claim<FrameNode>(currentNode));
    return inspectorInfo.c_str();
}

ArkUINodeHandle GetFrameNodeById(ArkUI_Int32 nodeId)
{
    auto node = OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(nodeId);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetFrameNodeByUniqueId(ArkUI_Int32 uniqueId)
{
    auto node = AceType::DynamicCast<NG::UINode>(OHOS::Ace::ElementRegister::GetInstance()->GetNodeById(uniqueId));
    CHECK_NULL_RETURN(node, nullptr);
    if (node->GetTag() == "root" || node->GetTag() == "stage" || node->GetTag() == "page") {
        return nullptr;
    }

    if (!AceType::InstanceOf<NG::FrameNode>(node)) {
        auto parent = node->GetParent();
        if (parent && parent->GetTag() == V2::COMMON_VIEW_ETS_TAG) {
            node = parent;
        } else {
            node = node->GetFrameChildByIndexWithoutExpanded(0);
        }
    }

    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetFrameNodeByKey(ArkUI_CharPtr key)
{
    auto node = NG::Inspector::GetFrameNodeByKey(key, true);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetAttachedFrameNodeById(ArkUI_CharPtr key)
{
    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(key);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

void PropertyUpdate(ArkUINodeHandle node)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    if (uiNode) {
        uiNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    }
}

ArkUINodeHandle GetLast(ArkUINodeHandle node, ArkUI_Bool isExpanded)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    size_t size = isExpanded ? frameNode->GetAllChildrenWithBuild(false).size()
                             : static_cast<size_t>(frameNode->GetTotalChildCountWithoutExpanded());
    CHECK_NULL_RETURN(size > 0, nullptr);
    auto child = frameNode->GetFrameNodeChildByIndex(size - 1, false, isExpanded);
    return reinterpret_cast<ArkUINodeHandle>(child);
}

ArkUINodeHandle GetFirstUINode(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto child = currentNode->GetFirstChild();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(child));
}

void GetLayoutSize(ArkUINodeHandle node, ArkUI_Int32* size)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(currentNode);
    auto renderContext = currentNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto rectSize = renderContext->GetPaintRectWithoutTransform().GetSize();
    size[0] = rectSize.Width();
    size[1] = rectSize.Height();
}

ArkUI_Float32* GetLayoutPositionWithoutMargin(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto rect = currentNode->GetPaintRectWithTransform();
    ArkUI_Float32* ret = new ArkUI_Float32[2];
    ret[0] = rect.GetX();
    ret[1] = rect.GetY();
    return ret;
}

ArkUI_Int32 SetSystemColorModeChangeEvent(ArkUINodeHandle node, void* userData, void* onColorModeChange)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto onColorChange = [userData, onColorModeChange](int32_t colorMode) {
        using FuncType = float (*)(int32_t, void*);
        FuncType func = reinterpret_cast<FuncType>(onColorModeChange);
        func(colorMode, userData);
    };
    ViewAbstract::SetSystemColorModeChangeEvent(frameNode, onColorChange);
    return 1;
}

void ResetSystemColorModeChangeEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSystemColorModeChangeEvent(frameNode, nullptr);
}

ArkUI_Int32 SetSystemFontStyleChangeEvent(ArkUINodeHandle node, void* userData, void* onFontStyleChange)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto onFontChange = [userData, onFontStyleChange](float fontSize, float fontWeight) {
        ArkUISystemFontStyleEvent fontStyle = new ArkUI_SystemFontStyleEvent();
        fontStyle->fontSize = fontSize;
        fontStyle->fontWeight = fontWeight;
        using FuncType = float (*)(ArkUISystemFontStyleEvent, void*);
        FuncType func = reinterpret_cast<FuncType>(onFontStyleChange);
        func(fontStyle, userData);
    };
    ViewAbstract::SetSystemFontChangeEvent(frameNode, onFontChange);
    return 1;
}

void ResetSystemFontStyleChangeEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetSystemFontChangeEvent(frameNode, nullptr);
}

ArkUI_Uint32 GetCustomPropertyCapiByKey(ArkUINodeHandle node, ArkUI_CharPtr key, char** value, ArkUI_Uint32* size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    std::string capiCustomProperty;
    if (!frameNode->GetCapiCustomProperty(key, capiCustomProperty)) {
        return 0;
    }
    *size = capiCustomProperty.size();
    *value = new char[*size + 1];
    capiCustomProperty.copy(*value, *size);
    (*value)[*size] = '\0';
    return 1;
}

void FreeCustomPropertyCharPtr(char* value, ArkUI_Uint32 size)
{
    CHECK_NULL_VOID(value);
    delete[] value;
    value = nullptr;
}

void SetCustomPropertyModiferByKey(ArkUINodeHandle node, void* callback, void* getCallback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<bool()>* func = reinterpret_cast<std::function<bool()>*>(callback);
    std::function<std::string(const std::string&)>* getFunc =
        reinterpret_cast<std::function<std::string(const std::string&)>*>(getCallback);
    frameNode->SetJSCustomProperty(*func, *getFunc);
}

void AddCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("AddCustomProperty doesn't run on UI thread");
        return;
    }
    ViewAbstract::AddCustomProperty(frameNode, key, value);
}

void RemoveCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("RemoveCustomProperty doesn't run on UI thread");
        return;
    }
    ViewAbstract::RemoveCustomProperty(frameNode, key);
}

namespace NodeModifier {
const ArkUIFrameNodeModifier* GetFrameNodeModifier()
{
    static const ArkUIFrameNodeModifier modifier = { IsModifiable, CreateFrameNode, InvalidateInFrameNode,
        AppendChildInFrameNode, InsertChildAfterInFrameNode, RemoveChildInFrameNode, ClearChildrenInFrameNode,
        GetChildrenCount, GetChild, GetFirst, GetNextSibling, GetPreviousSibling, GetParent, GetIdByNodePtr,
        GetPositionToParent, GetPositionToScreen, GetPositionToWindow, GetPositionToParentWithTransform,
        GetPositionToScreenWithTransform, GetPositionToWindowWithTransform, GetMeasuredSize, GetLayoutPosition,
        GetInspectorId, GetNodeType, IsVisible, IsAttached, GetInspectorInfo, GetFrameNodeById, GetFrameNodeByUniqueId,
        GetFrameNodeByKey, GetAttachedFrameNodeById, PropertyUpdate, GetLast, GetFirstUINode, GetLayoutSize,
        GetLayoutPositionWithoutMargin, SetSystemColorModeChangeEvent, ResetSystemColorModeChangeEvent,
        SetSystemFontStyleChangeEvent, ResetSystemFontStyleChangeEvent, GetCustomPropertyCapiByKey,
        SetCustomPropertyModiferByKey, AddCustomProperty, RemoveCustomProperty, FreeCustomPropertyCharPtr };
    return &modifier;
}

const CJUIFrameNodeModifier* GetCJUIFrameNodeModifier()
{
    static const CJUIFrameNodeModifier modifier = { IsModifiable, CreateFrameNode, InvalidateInFrameNode,
        AppendChildInFrameNode, InsertChildAfterInFrameNode, RemoveChildInFrameNode, ClearChildrenInFrameNode,
        GetChildrenCount, GetChild, GetFirst, GetNextSibling, GetPreviousSibling, GetParent, GetIdByNodePtr,
        PropertyUpdate, GetLast, GetPositionToParent, GetPositionToScreen, GetPositionToWindow,
        GetPositionToParentWithTransform, GetPositionToScreenWithTransform, GetPositionToWindowWithTransform,
        GetMeasuredSize, GetLayoutPosition, GetInspectorId, GetNodeType, IsVisible, IsAttached, GetInspectorInfo,
        GetFrameNodeById, GetFrameNodeByUniqueId, GetFrameNodeByKey, GetFirstUINode, GetLayoutSize,
        GetLayoutPositionWithoutMargin };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
