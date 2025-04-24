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
#include <cstdlib>
#include <vector>

#include "base/error/error_code.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/custom_frame_node/custom_frame_node.h"
#include "core/components_ng/pattern/custom/custom_measure_layout_node.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG {
enum class ExpandMode : uint32_t {
    NOT_EXPAND = 0,
    EXPAND,
    LAZY_EXPAND,
};

enum EventQueryType {
    ON_CLICK = 0,
};

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
    return (parent == nullptr || parent->GetTag() == V2::PAGE_ETS_TAG || parent->GetTag() == V2::STAGE_ETS_TAG)
               ? nullptr : AceType::DynamicCast<FrameNode>(parent);
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

ArkUINodeHandle GetChild(ArkUINodeHandle node, ArkUI_Int32 index, ArkUI_Uint32 expandMode)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, nullptr);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, nullptr);
    CHECK_NULL_RETURN(index >= 0, nullptr);
    auto expandModeResult = static_cast<ExpandMode>(expandMode);
    if (expandModeResult == ExpandMode::EXPAND) {
        frameNode->GetAllChildrenWithBuild(false);
    }
    FrameNode* child = nullptr;
    if (expandModeResult == ExpandMode::EXPAND || expandModeResult == ExpandMode::NOT_EXPAND) {
        child = frameNode->GetFrameNodeChildByIndex(index, false, expandModeResult == ExpandMode::EXPAND);
    } else if (expandModeResult == ExpandMode::LAZY_EXPAND) {
        child = frameNode->GetFrameNodeChildByIndexWithoutBuild(index);
        if (child == nullptr) {
            return GetChild(node, index, static_cast<ArkUI_Uint32>(ExpandMode::EXPAND));
        }
    }
    return reinterpret_cast<ArkUINodeHandle>(child);
}

ArkUI_Int32 GetFirstChildIndexWithoutExpand(ArkUINodeHandle node, ArkUI_Uint32* index)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, ERROR_CODE_PARAM_INVALID);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    auto child = frameNode->GetFrameNodeChildByIndex(0, false, false);
    CHECK_NULL_RETURN(child, ERROR_CODE_PARAM_INVALID);
    auto* childNode = reinterpret_cast<FrameNode*>(child);
    auto childRef = Referenced::Claim<FrameNode>(childNode);
    *index = frameNode->GetFrameNodeIndex(childRef, true);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 GetLastChildIndexWithoutExpand(ArkUINodeHandle node, ArkUI_Uint32* index)
{
    auto* currentNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(currentNode, ERROR_CODE_PARAM_INVALID);
    auto* frameNode = AceType::DynamicCast<FrameNode>(currentNode);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    size_t size = static_cast<size_t>(frameNode->GetTotalChildCountWithoutExpanded());
    CHECK_NULL_RETURN(size > 0, ERROR_CODE_PARAM_INVALID);
    auto child = frameNode->GetFrameNodeChildByIndex(size - 1, false, false);
    CHECK_NULL_RETURN(child, ERROR_CODE_PARAM_INVALID);
    auto* childNode = reinterpret_cast<FrameNode*>(child);
    auto childRef = Referenced::Claim<FrameNode>(childNode);
    *index = frameNode->GetFrameNodeIndex(childRef, true);
    return ERROR_CODE_NO_ERROR;
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
    CHECK_NULL_RETURN(parent, nullptr);
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
    while (isVisible && parentNode) {
        if (AceType::InstanceOf<FrameNode>(*parentNode)) {
            isVisible = isVisible && AceType::DynamicCast<FrameNode>(parentNode)->IsVisible();
        } else if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_FIFTEEN)) {
            break;
        }
        
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

    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetFrameNodeByKey(ArkUI_CharPtr key)
{
    auto node = NG::Inspector::GetFrameNodeByKey(key, true);
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(node));
}

ArkUINodeHandle GetAttachedFrameNodeById(ArkUI_CharPtr key)
{
    auto pipeline = NG::PipelineContext::GetCurrentContextSafely();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("GetAttachedNodeHandleById doesn't run on UI thread");
    }
    auto node = ElementRegister::GetInstance()->GetAttachedFrameNodeById(key);
    CHECK_NULL_RETURN(node, nullptr);
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

ArkUI_Int32 SetDrawCompleteEvent(ArkUINodeHandle node, void* userData, void* onDraw)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    auto onDrawCallBack = [userData, onDraw]() {
        using FuncType = void (*)(void*);
        FuncType func = reinterpret_cast<FuncType>(onDraw);
        if (!func) {
            return;
        }
        func(userData);
    };
    ViewAbstract::SetDrawCompleteEvent(frameNode, std::move(onDrawCallBack));
    return 0;
}

ArkUI_Int32 ResetDrawCompleteEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    ViewAbstract::SetDrawCompleteEvent(frameNode, nullptr);
    return 0;
}

ArkUI_Int32 SetLayoutEvent(ArkUINodeHandle node, void* userData, void* onLayout)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    auto onLayoutCallBack = [userData, onLayout]() {
        using FuncType = void (*)(void*);
        FuncType func = reinterpret_cast<FuncType>(onLayout);
        if (!func) {
            return;
        }
        func(userData);
    };
    ViewAbstract::SetLayoutEvent(frameNode, std::move(onLayoutCallBack));
    return 0;
}

ArkUI_Int32 ResetLayoutEvent(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, -1);
    ViewAbstract::SetLayoutEvent(frameNode, nullptr);
    return 0;
}

ArkUI_Int32 SetCrossLanguageOptions(ArkUINodeHandle node, bool attributeSetting)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, ERROR_CODE_PARAM_INVALID);
    static const std::vector<const char*> nodeTypeArray = {
        OHOS::Ace::V2::SCROLL_ETS_TAG,
    };
    auto pos = std::find(nodeTypeArray.begin(), nodeTypeArray.end(), currentNode->GetTag());
    if (pos == nodeTypeArray.end()) {
        return ERROR_CODE_PARAM_INVALID;
    }
    currentNode->SetIsCrossLanguageAttributeSetting(attributeSetting);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Bool GetCrossLanguageOptions(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    return currentNode->isCrossLanguageAttributeSetting();
}

ArkUI_Bool CheckIfCanCrossLanguageAttributeSetting(ArkUINodeHandle node)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(currentNode, false);
    return currentNode -> IsCNode() ? currentNode->isCrossLanguageAttributeSetting() : false;
}

EventBindingInfo GetInteractionEventBindingInfo(ArkUINodeHandle node, int eventType)
{
    auto* currentNode = reinterpret_cast<UINode*>(node);
    EventBindingInfo bindingInfo {};
    CHECK_NULL_RETURN(currentNode, bindingInfo);
    if (eventType != EventQueryType::ON_CLICK) {
        return bindingInfo;
    }
    auto info = currentNode->GetInteractionEventBindingInfo();
    bindingInfo.baseEventRegistered = info.baseEventRegistered;
    bindingInfo.nodeEventRegistered = info.nodeEventRegistered;
    bindingInfo.nativeEventRegistered= info.nativeEventRegistered;
    bindingInfo.builtInEventRegistered= info.builtInEventRegistered;
    return bindingInfo;
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
    if (!frameNode->IsCNode() || !frameNode->GetCapiCustomProperty(key, capiCustomProperty)) {
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

void SetCustomPropertyModiferByKey(ArkUINodeHandle node, void* callback, void* getCallback,
    void* getCustomPropertyMap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::function<bool()>* func = reinterpret_cast<std::function<bool()>*>(callback);
    std::function<std::string(const std::string&)>* getFunc =
        reinterpret_cast<std::function<std::string(const std::string&)>*>(getCallback);
    std::function<std::string()>* getMapFunc =
        reinterpret_cast<std::function<std::string()>*>(getCustomPropertyMap);
    frameNode->SetJSCustomProperty(*func, *getFunc, std::move(*getMapFunc));
}

void AddCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key, ArkUI_CharPtr value)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto pipeline = uiNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("AddCustomProperty doesn't run on UI thread");
        return;
    }
    ViewAbstract::AddCustomProperty(uiNode, key, value);
}

void RemoveCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_VOID(uiNode);
    auto pipeline = uiNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("RemoveCustomProperty doesn't run on UI thread");
        return;
    }
    ViewAbstract::RemoveCustomProperty(uiNode, key);
}

ArkUINodeHandle GetCurrentPageRootNode(ArkUINodeHandle node)
{
    auto uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, nullptr);
    auto rootNode = uiNode->GetCurrentPageRootNode();
    return reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(rootNode));
}

ArkUI_Int32 GetNodeTag(ArkUINodeHandle node)
{
    auto uiNode = reinterpret_cast<UINode*>(node);
    CHECK_NULL_RETURN(uiNode, 0);
    return uiNode->IsCNode();
}

void GetActiveChildrenInfo(ArkUINodeHandle handle, ArkUINodeHandle** items, ArkUI_Int32* size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(handle);
    CHECK_NULL_VOID(frameNode);
    auto childList = frameNode->GetActiveChildren();
    *size = childList.size();
    *items = new ArkUINodeHandle[*size];
    int32_t i = 0;
    for (auto& child : childList) {
        (*items)[i++] = reinterpret_cast<ArkUINodeHandle>(OHOS::Ace::AceType::RawPtr(child));
    }
}

void GetCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key, char** value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string capiCustomProperty;
    if (frameNode->IsCNode()) {
        frameNode->GetCapiCustomProperty(key, capiCustomProperty);
    } else {
        frameNode->GetJSCustomProperty(key, capiCustomProperty);
    }
    auto size = capiCustomProperty.size();
    *value = new char[size + 1];
    capiCustomProperty.copy(*value, size);
    (*value)[size] = '\0';
}

void AddExtraCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key, void* extraData)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("AddExtraCustomProperty doesn't run on UI thread");
        return;
    }
    frameNode->AddExtraCustomProperty(key, extraData);
}

void* GetExtraCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("GetExtraCustomProperty doesn't run on UI thread");
        return nullptr;
    }
    return frameNode->GetExtraCustomProperty(key);
}

void RemoveExtraCustomProperty(ArkUINodeHandle node, ArkUI_CharPtr key)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("RemoveExtraCustomProperty doesn't run on UI thread");
        return;
    }
    frameNode->RemoveExtraCustomProperty(key);
}

void GetCustomPropertyByKey(ArkUINodeHandle node, ArkUI_CharPtr key, char** value, ArkUI_Uint32* size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("GetCustomPropertyByKey doesn't run on UI thread");
        return;
    }
    std::string customProperty;
    if (!frameNode->GetCustomPropertyByKey(key, customProperty)) {
        return;
    }
    *size = customProperty.size();
    *value = new char[*size + 1];
    customProperty.copy(*value, *size);
    (*value)[*size] = '\0';
}

void AddNodeDestroyCallback(ArkUINodeHandle node, ArkUI_CharPtr callbackKey, void (*onDestroy)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("AddNodeDestroyCallback doesn't run on UI thread");
        return;
    }
    auto onDestroyCallback = [node, onDestroy]() {
        onDestroy(node);
    };
    frameNode->AddNodeDestroyCallback(std::string(callbackKey), std::move(onDestroyCallback));
}

void RemoveNodeDestroyCallback(ArkUINodeHandle node, ArkUI_CharPtr callbackKey)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGW("RemoveNodeDestroyCallback doesn't run on UI thread");
        return;
    }
    frameNode->RemoveNodeDestroyCallback(std::string(callbackKey));
}

ArkUI_Int32 RequestFocus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, ARKUI_ERROR_CODE_FOCUS_NON_EXISTENT);
    return static_cast<ArkUI_Int32>(ViewAbstract::RequestFocus(frameNode));
}

void ClearFocus(ArkUI_Int32 instanceId)
{
    ViewAbstract::ClearFocus(instanceId);
}

void FocusActivate(ArkUI_Int32 instanceId, bool isActive, bool isAutoInactive)
{
    ViewAbstract::FocusActivate(instanceId, isActive, isAutoInactive);
}

void SetAutoFocusTransfer(ArkUI_Int32 instanceId, bool isAutoFocusTransfer)
{
    ViewAbstract::SetAutoFocusTransfer(instanceId, isAutoFocusTransfer);
}

ArkUI_Int32 GetWindowInfoByNode(ArkUINodeHandle node, char** name)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (!frameNode->IsOnMainTree()) {
        return OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE;
    }
    auto context = frameNode->GetAttachedContext();
    CHECK_NULL_RETURN(context, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE);
    if (!context->CheckThreadSafe()) {
        LOGF_ABORT("GetWindowInfoByNode doesn't run on UI thread");
    }
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_NODE_NOT_ON_MAIN_TREE);
    std::string windowName = window->GetWindowName();
    size_t nameSize = windowName.size();
    *name = new char[nameSize + 1];
    windowName.copy(*name, nameSize);
    (*name)[nameSize] = '\0';
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 MoveNodeTo(ArkUINodeHandle node, ArkUINodeHandle target_parent, ArkUI_Int32 index)
{
    auto* moveNode = reinterpret_cast<UINode*>(node);
    auto* toNode = reinterpret_cast<UINode*>(target_parent);
    CHECK_NULL_RETURN(moveNode, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(toNode, ERROR_CODE_PARAM_INVALID);
    static const std::vector<const char*> nodeTypeArray = {
        OHOS::Ace::V2::STACK_ETS_TAG,
        OHOS::Ace::V2::XCOMPONENT_ETS_TAG,
        OHOS::Ace::V2::EMBEDDED_COMPONENT_ETS_TAG,
    };
    auto pos = std::find(nodeTypeArray.begin(), nodeTypeArray.end(), moveNode->GetTag());
    if (pos == nodeTypeArray.end()) {
        return ERROR_CODE_PARAM_INVALID;
    }
    auto pipeline = moveNode->GetContextRefPtr();
    if (pipeline && !pipeline->CheckThreadSafe()) {
        LOGF_ABORT("MoveNodeTo doesn't run on UI thread");
    }
    auto oldParent = moveNode->GetParent();
    moveNode->setIsMoving(true);
    auto moveNodeRef = AceType::Claim(moveNode);
    if (oldParent) {
        oldParent->RemoveChild(moveNodeRef);
        oldParent->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
    int32_t childCount = toNode->TotalChildCount();
    if (index >= childCount || index < 0) {
        toNode->AddChild(moveNodeRef);
    } else {
        auto indexChild = toNode->GetChildAtIndex(index);
        toNode->AddChildBefore(moveNodeRef, indexChild);
    }
    toNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    moveNode->setIsMoving(false);
    return ERROR_CODE_NO_ERROR;
}

void SetKeyProcessingMode(ArkUI_Int32 instanceId, ArkUI_Int32 mode)
{
    auto container = Container::GetContainer(instanceId);
    CHECK_NULL_VOID(container);
    auto delegate = EngineHelper::GetDelegateByContainer(container);
    CHECK_NULL_VOID(delegate);
    delegate->SetKeyProcessingMode(mode);
}

namespace NodeModifier {
const ArkUIFrameNodeModifier* GetFrameNodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIFrameNodeModifier modifier = {
        .isModifiable = IsModifiable,
        .createFrameNode = CreateFrameNode,
        .invalidate = InvalidateInFrameNode,
        .appendChild = AppendChildInFrameNode,
        .insertChildAfter = InsertChildAfterInFrameNode,
        .removeChild = RemoveChildInFrameNode,
        .clearChildren = ClearChildrenInFrameNode,
        .getChildrenCount = GetChildrenCount,
        .getChild = GetChild,
        .getFirstChildIndexWithoutExpand = GetFirstChildIndexWithoutExpand,
        .getLastChildIndexWithoutExpand = GetLastChildIndexWithoutExpand,
        .getFirst = GetFirst,
        .getNextSibling = GetNextSibling,
        .getPreviousSibling = GetPreviousSibling,
        .getParent = GetParent,
        .getIdByNodePtr = GetIdByNodePtr,
        .getPositionToParent = GetPositionToParent,
        .getPositionToScreen = GetPositionToScreen,
        .getPositionToWindow = GetPositionToWindow,
        .getPositionToParentWithTransform = GetPositionToParentWithTransform,
        .getPositionToScreenWithTransform = GetPositionToScreenWithTransform,
        .getPositionToWindowWithTransform = GetPositionToWindowWithTransform,
        .getMeasuredSize = GetMeasuredSize,
        .getLayoutPosition = GetLayoutPosition,
        .getInspectorId = GetInspectorId,
        .getNodeType = GetNodeType,
        .isVisible = IsVisible,
        .isAttached = IsAttached,
        .getInspectorInfo = GetInspectorInfo,
        .getFrameNodeById = GetFrameNodeById,
        .getFrameNodeByUniqueId = GetFrameNodeByUniqueId,
        .getFrameNodeByKey = GetFrameNodeByKey,
        .getAttachedFrameNodeById = GetAttachedFrameNodeById,
        .propertyUpdate = PropertyUpdate,
        .getLast = GetLast,
        .getFirstUINode = GetFirstUINode,
        .getLayoutSize = GetLayoutSize,
        .getLayoutPositionWithoutMargin = GetLayoutPositionWithoutMargin,
        .setSystemColorModeChangeEvent = SetSystemColorModeChangeEvent,
        .resetSystemColorModeChangeEvent = ResetSystemColorModeChangeEvent,
        .setSystemFontStyleChangeEvent = SetSystemFontStyleChangeEvent,
        .resetSystemFontStyleChangeEvent = ResetSystemFontStyleChangeEvent,
        .getCustomPropertyCapiByKey = GetCustomPropertyCapiByKey,
        .setCustomPropertyModiferByKey = SetCustomPropertyModiferByKey,
        .addCustomProperty = AddCustomProperty,
        .removeCustomProperty = RemoveCustomProperty,
        .freeCustomPropertyCharPtr = FreeCustomPropertyCharPtr,
        .getCurrentPageRootNode = GetCurrentPageRootNode,
        .getNodeTag = GetNodeTag,
        .getActiveChildrenInfo = GetActiveChildrenInfo,
        .getCustomProperty = GetCustomProperty,
        .addExtraCustomProperty = AddExtraCustomProperty,
        .getExtraCustomProperty = GetExtraCustomProperty,
        .removeExtraCustomProperty = RemoveExtraCustomProperty,
        .getCustomPropertyByKey = GetCustomPropertyByKey,
        .addNodeDestroyCallback = AddNodeDestroyCallback,
        .removeNodeDestroyCallback = RemoveNodeDestroyCallback,
        .getWindowInfoByNode = GetWindowInfoByNode,
        .setDrawCompleteEvent = SetDrawCompleteEvent,
        .resetDrawCompleteEvent = ResetDrawCompleteEvent,
        .setLayoutEvent = SetLayoutEvent,
        .resetLayoutEvent = ResetLayoutEvent,
        .requestFocus = RequestFocus,
        .clearFocus = ClearFocus,
        .focusActivate = FocusActivate,
        .setAutoFocusTransfer = SetAutoFocusTransfer,
        .moveNodeTo = MoveNodeTo,
        .setCrossLanguageOptions = SetCrossLanguageOptions,
        .getCrossLanguageOptions = GetCrossLanguageOptions,
        .checkIfCanCrossLanguageAttributeSetting = CheckIfCanCrossLanguageAttributeSetting,
        .setKeyProcessingMode = SetKeyProcessingMode,
        .getInteractionEventBindingInfo = GetInteractionEventBindingInfo,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIFrameNodeModifier* GetCJUIFrameNodeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIFrameNodeModifier modifier = {
        .isModifiable = IsModifiable,
        .createFrameNode = CreateFrameNode,
        .invalidate = InvalidateInFrameNode,
        .appendChild = AppendChildInFrameNode,
        .insertChildAfter = InsertChildAfterInFrameNode,
        .removeChild = RemoveChildInFrameNode,
        .clearChildren = ClearChildrenInFrameNode,
        .getChildrenCount = GetChildrenCount,
        .getChild = GetChild,
        .getFirst = GetFirst,
        .getNextSibling = GetNextSibling,
        .getPreviousSibling = GetPreviousSibling,
        .getParent = GetParent,
        .getIdByNodePtr = GetIdByNodePtr,
        .propertyUpdate = PropertyUpdate,
        .getLast = GetLast,
        .getPositionToParent = GetPositionToParent,
        .getPositionToScreen = GetPositionToScreen,
        .getPositionToWindow = GetPositionToWindow,
        .getPositionToParentWithTransform = GetPositionToParentWithTransform,
        .getPositionToScreenWithTransform = GetPositionToScreenWithTransform,
        .getPositionToWindowWithTransform = GetPositionToWindowWithTransform,
        .getMeasuredSize = GetMeasuredSize,
        .getLayoutPosition = GetLayoutPosition,
        .getInspectorId = GetInspectorId,
        .getNodeType = GetNodeType,
        .isVisible = IsVisible,
        .isAttached = IsAttached,
        .getInspectorInfo = GetInspectorInfo,
        .getFrameNodeById = GetFrameNodeById,
        .getFrameNodeByUniqueId = GetFrameNodeByUniqueId,
        .getFrameNodeByKey = GetFrameNodeByKey,
        .getFirstUINode = GetFirstUINode,
        .getLayoutSize = GetLayoutSize,
        .getLayoutPositionWithoutMargin = GetLayoutPositionWithoutMargin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
