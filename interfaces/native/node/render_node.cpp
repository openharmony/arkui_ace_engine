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

#include "render_node.h"

#include "node_model.h"

#include "base/error/error_code.h"
#include "base/hiviewdfx/histogram_wrapper.h"
#include "base/utils/utils.h"
#include "interfaces/native/native_error_message_macros.h"

#define METRIC_PREFIX_NATIVE_RENDER "NativeRender.RenderNodeUtils."

#ifdef __cplusplus
extern "C" {
#endif

std::map<int32_t, ArkUIRenderNodeHandle> g_renderNodeMap;
std::set<ArkUIRenderModifierHandle> g_modifierSet;
std::set<ArkUIPropertyHandle> g_propertySet;

int32_t OH_ArkUI_RenderNodeUtils_AddRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AddRenderNode", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        child, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render child node is null");
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE, __FUNCTION__, "Node is not a custom node");
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->addRenderNode(
        node->uiNodeHandle, child->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_RemoveRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "RemoveRenderNode", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        child, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render child node is null");
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE, __FUNCTION__, "Node is not a custom node");
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->removeRenderNode(
        node->uiNodeHandle, child->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren(ArkUI_NodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "ClearRenderNodeChildren", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node is null");
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE, __FUNCTION__, "Node is not a custom node");
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->clearRenderNodeChildren(
        node->uiNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_Invalidate(ArkUI_NodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "Invalidate", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    impl->getNodeModifiers()->getFrameNodeModifier()->invalidate(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_RenderNodeHandle OH_ArkUI_RenderNodeUtils_CreateNode()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateNode", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);

    int32_t nodeId = 0;
    auto* renderNode = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createNode(&nodeId);
    if (!renderNode) {
        return nullptr;
    }
    ArkUI_RenderNode* arkUIRenderNode = new ArkUI_RenderNode({ renderNode });
    g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId, renderNode));
    return arkUIRenderNode;
}

int32_t OH_ArkUI_RenderNodeUtils_DisposeNode(ArkUI_RenderNodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeNode", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto nodeId = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getId(node->renderNodeHandle);
    if (nodeId == 0) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto it = g_renderNodeMap.find(nodeId);
    if (it != g_renderNodeMap.end()) {
        g_renderNodeMap.erase(it);
    }
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->deleteInnerRenderNodeStruct(node->renderNodeHandle);
    // deleteInnerRenderNodeStruct does not set node->renderNodeHandle to nullptr
    node->renderNodeHandle = nullptr;

    delete node;
    node = nullptr;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RenderNodeUtils_AddChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AddChild", 1);
    if (!(node && child)) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node or child is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->addChild(
        node->renderNodeHandle, child->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_InsertChildAfter(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child, ArkUI_RenderNodeHandle sibling)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "InsertChildAfter", 1);
    if (!(node && child && sibling)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node, child, or sibling is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->insertChildAfter(
        node->renderNodeHandle, child->renderNodeHandle, sibling->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_RemoveChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "RemoveChild", 1);
    if (!(node && child)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node or child is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->removeChild(
        node->renderNodeHandle, child->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_ClearChildren(ArkUI_RenderNodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "ClearChildren", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->clearChildren(
        node->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetChild(ArkUI_RenderNodeHandle node, int32_t index, ArkUI_RenderNodeHandle* child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetChild", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (index < 0) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Child index is invalid");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChild(
        node->renderNodeHandle, index, &renderNode, &nodeId);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        // Find in map first, try return same handle.
        auto it = g_renderNodeMap.find(nodeId);
        if (it != g_renderNodeMap.end()) {
            // delete renderNode;
            renderNode = it->second;
        }
        // If don't exit, create a new handle.
        *child = new ArkUI_RenderNode({ renderNode });
        g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId, renderNode));
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetFirstChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* child)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetFirstChild", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFirstChild(
        node->renderNodeHandle, &renderNode, &nodeId);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        // Find in map first, try return same handle.
        auto it = g_renderNodeMap.find(nodeId);
        if (it != g_renderNodeMap.end()) {
            // delete renderNode;
            renderNode = it->second;
        }
        // If don't exit, create a new handle.
        *child = new ArkUI_RenderNode({ renderNode });
        g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId, renderNode));
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetNextSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetNextSibling", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getNextSibling(
        node->renderNodeHandle, &renderNode, &nodeId);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        // Find in map first, try return same handle.
        auto it = g_renderNodeMap.find(nodeId);
        if (it != g_renderNodeMap.end()) {
            // delete renderNode;
            renderNode = it->second;
        }
        // If don't exit, create a new handle.
        *sibling = new ArkUI_RenderNode({ renderNode });
        g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId, renderNode));
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetPreviousSibling(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle* sibling)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetPreviousSibling", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPreviousSibling(
        node->renderNodeHandle, &renderNode, &nodeId);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        // Find in map first, try return same handle.
        auto it = g_renderNodeMap.find(nodeId);
        if (it != g_renderNodeMap.end()) {
            // delete renderNode;
            renderNode = it->second;
        }
        // If don't exit, create a new handle.
        *sibling = new ArkUI_RenderNode({ renderNode });
        g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId, renderNode));
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetChildren(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle** children, int32_t* count)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetChildren", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle* renderNode;
    uint32_t* nodeId;
    int32_t nodeCount = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChildren(
        node->renderNodeHandle, &renderNode, &nodeId, &nodeCount);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    *count = nodeCount;
    if (nodeCount > 0 && result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        ArkUI_RenderNodeHandle* childrenList = new ArkUI_RenderNodeHandle[nodeCount];
        for (int32_t i = 0; i < nodeCount; i++) {
            childrenList[i] = new ArkUI_RenderNode({ renderNode[i] });
            g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(nodeId[i], renderNode[i]));
        }
        *children = childrenList;
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetChildrenCount(ArkUI_RenderNodeHandle node, int32_t* count)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetChildrenCount", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    int32_t childCount;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChildrenCount(
        node->renderNodeHandle, &childCount);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        *count = childCount;
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t color)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBackgroundColor", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBackgroundColor(
        node->renderNodeHandle, color);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t* color)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBackgroundColor", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBackgroundColor(
        node->renderNodeHandle, color);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetOpacity(ArkUI_RenderNodeHandle node, float opacity)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetOpacity", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (!OHOS::Ace::InRegion(0, 1, opacity)) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Opacity is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setOpacity(
        node->renderNodeHandle, opacity);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetOpacity(ArkUI_RenderNodeHandle node, float* opacity)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetOpacity", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getOpacity(
        node->renderNodeHandle, opacity);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetSize(ArkUI_RenderNodeHandle node, int32_t width, int32_t height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetSize", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (width < 0 || height < 0) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Size is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setSize(
        node->renderNodeHandle, width, height);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetSize(ArkUI_RenderNodeHandle node, int32_t* width, int32_t* height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetSize", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getSize(
        node->renderNodeHandle, width, height);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetPosition(ArkUI_RenderNodeHandle node, int32_t x, int32_t y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetPosition", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setPosition(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetPosition(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetPosition", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPosition(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetPivot(ArkUI_RenderNodeHandle node, float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetPivot", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setPivot(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetPivot(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetPivot", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPivot(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetScale(ArkUI_RenderNodeHandle node, float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetScale", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setScale(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetScale(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetScale", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getScale(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetTranslation(ArkUI_RenderNodeHandle node, float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetTranslation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setTranslation(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetTranslation(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetTranslation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getTranslation(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetRotation(ArkUI_RenderNodeHandle node, float x, float y, float z)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRotation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRotation(
        node->renderNodeHandle, x, y, z);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetRotation(ArkUI_RenderNodeHandle node, float* x, float* y, float* z)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetRotation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getRotation(
        node->renderNodeHandle, x, y, z);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetTransform(ArkUI_RenderNodeHandle node, float* matrix)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetTransform", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setTransform(
        node->renderNodeHandle, matrix);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowColor(ArkUI_RenderNodeHandle node, uint32_t color)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetShadowColor", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowColor(
        node->renderNodeHandle, color);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowColor(ArkUI_RenderNodeHandle node, uint32_t* color)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetShadowColor", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowColor(
        node->renderNodeHandle, color);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowOffset(ArkUI_RenderNodeHandle node, int32_t x, int32_t y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetShadowOffset", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowOffset(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowOffset(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetShadowOffset", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowOffset(
        node->renderNodeHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowAlpha(ArkUI_RenderNodeHandle node, float alpha)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetShadowAlpha", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (!OHOS::Ace::InRegion(0, 1, alpha)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Shadow alpha is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowAlpha(
        node->renderNodeHandle, alpha);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowAlpha(ArkUI_RenderNodeHandle node, float* alpha)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetShadowAlpha", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowAlpha(
        node->renderNodeHandle, alpha);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowElevation(ArkUI_RenderNodeHandle node, float elevation)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetShadowElevation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (elevation < 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Shadow elevation is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowElevation(
        node->renderNodeHandle, elevation);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowElevation(ArkUI_RenderNodeHandle node, float* radius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetShadowElevation", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowElevation(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowRadius(ArkUI_RenderNodeHandle node, float* radius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetShadowRadius", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowRadius(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowRadius(ArkUI_RenderNodeHandle node, float radius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetShadowRadius", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (radius < 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Shadow radius is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowRadius(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption* borderStyle)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBorderStyle", 1);
    if (node == nullptr || borderStyle == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Render node or border style option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderStyle(node->renderNodeHandle,
        borderStyle->leftStyle, borderStyle->topStyle, borderStyle->rightStyle, borderStyle->bottomStyle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption** borderStyle)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBorderStyle", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderStyle(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(&((*borderStyle)->leftStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->topStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->rightStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->leftStyle)));
    if (code != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption* borderWidth)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBorderWidth", 1);
    if (node == nullptr || borderWidth == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Render node or border width option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderWidth(node->renderNodeHandle,
        borderWidth->leftWidth, borderWidth->topWidth, borderWidth->rightWidth, borderWidth->bottomWidth);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidth** borderWidth)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBorderWidth", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderWidth(node->renderNodeHandle,
        reinterpret_cast<float*>(&((*borderWidth)->leftWidth)), reinterpret_cast<float*>(&((*borderWidth)->topWidth)),
        reinterpret_cast<float*>(&((*borderWidth)->rightWidth)),
        reinterpret_cast<float*>(&((*borderWidth)->leftWidth)));
    if (code != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }

    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColor* borderColor)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBorderColor", 1);
    if (node == nullptr || borderColor == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Render node or border color option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderColor(node->renderNodeHandle,
        borderColor->leftColor, borderColor->topColor, borderColor->rightColor, borderColor->bottomColor);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColor** borderColor)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBorderColor", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderColor(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(&((*borderColor)->leftColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->topColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->rightColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->leftColor)));
    if (code != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderRadius(ArkUI_RenderNodeHandle node,
    ArkUI_NodeBorderRadiusOption* borderRadius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBorderRadius", 1);
    if (node == nullptr || borderRadius == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Render node or border radius option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderRadius(node->renderNodeHandle,
        borderRadius->topLeftRadius, borderRadius->topRightRadius,
        borderRadius->bottomLeftRadius, borderRadius->bottomRightRadius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderRadius(ArkUI_RenderNodeHandle node,
    ArkUI_NodeBorderRadiusOption** borderRadius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBorderRadius", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderRadius(node->renderNodeHandle,
        reinterpret_cast<float*>(&((*borderRadius)->topLeftRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->topRightRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->bottomLeftRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->bottomRightRadius)));
    if (code != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup(ArkUI_RenderNodeHandle node, bool markNodeGroup)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetMarkNodeGroup", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setMarkNodeGroup(node->renderNodeHandle,
        static_cast<int32_t>(markNodeGroup));
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBounds(ArkUI_RenderNodeHandle node,
    int32_t x, int32_t y, int32_t width, int32_t height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBounds", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (width < 0 || height < 0) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "Bounds size is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBounds(node->renderNodeHandle,
        static_cast<uint32_t>(x), static_cast<uint32_t>(y),
        static_cast<uint32_t>(width), static_cast<uint32_t>(height));
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetBounds(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y, int32_t* width,
    int32_t* height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetBounds", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBounds(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(x), reinterpret_cast<uint32_t*>(y),
        reinterpret_cast<uint32_t*>(width), reinterpret_cast<uint32_t*>(height));
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetDrawRegion(ArkUI_RenderNodeHandle node, float x, float y, float w, float h)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetDrawRegion", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setDrawRegion(
        node->renderNodeHandle, x, y, w, h);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetClipToFrame(ArkUI_RenderNodeHandle node, int32_t clipToFrame)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetClipToFrame", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (!OHOS::Ace::InRegion(0, 1, clipToFrame)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "ClipToFrame is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setClipToFrame(
        node->renderNodeHandle, clipToFrame);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetClipToFrame(ArkUI_RenderNodeHandle node, int32_t* clipToFrame)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetClipToFrame", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getClipToFrame(
        node->renderNodeHandle, clipToFrame);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetClipToBounds(ArkUI_RenderNodeHandle node, int32_t clipToBounds)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetClipToBounds", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    if (!OHOS::Ace::InRegion(0, 1, clipToBounds)) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE, __FUNCTION__, "ClipToBounds is out of range");
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setClipToBounds(
        node->renderNodeHandle, clipToBounds);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetClipToBounds(ArkUI_RenderNodeHandle node, int32_t* clipToBounds)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetClipToBounds", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getClipToBounds(
        node->renderNodeHandle, clipToBounds);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachContentModifier(
    ArkUI_RenderNodeHandle node, ArkUI_RenderContentModifierHandle modifier)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachContentModifier", 1);
    if (node == nullptr || modifier == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node or content modifier is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachModifier(
        node->renderNodeHandle, modifier->RenderModifierHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

ArkUI_RenderContentModifierHandle OH_ArkUI_RenderNodeUtils_CreateContentModifier()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateContentModifier", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* modifierPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createModifier();
    if (!modifierPtr) {
        return nullptr;
    }
    ArkUI_RenderContentModifier* arkUIRenderModifier = new ArkUI_RenderContentModifier({ modifierPtr });
    g_modifierSet.insert(modifierPtr);
    return arkUIRenderModifier;
}

void OH_ArkUI_RenderNodeUtils_DisposeContentModifier(ArkUI_RenderContentModifierHandle modifier)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeContentModifier", 1);
    CHECK_NULL_VOID(modifier);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_modifierSet.erase(modifier->RenderModifierHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeModifier(modifier->RenderModifierHandle);
    delete modifier;
    modifier = nullptr;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachFloatProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatPropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachFloatProperty", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Content modifier or float property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachVector2Property(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2PropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachVector2Property", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Content modifier or vector2 property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachColorProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorPropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachColorProperty", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(
            OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Content modifier or color property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatAnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachFloatAnimatableProperty", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Content modifier or float animatable property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2AnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachVector2AnimatableProperty", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Content modifier or vector2 animatable property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorAnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "AttachColorAnimatableProperty", 1);
    if (modifier == nullptr || property == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID,
            __FUNCTION__, "Content modifier or color animatable property is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

ArkUI_FloatPropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatProperty(float value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateFloatProperty", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createFloatProperty(value);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_FloatProperty* rsProperty = new ArkUI_FloatProperty({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetFloatPropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Float property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setFloatProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float* value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetFloatPropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Float property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFloatProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(ArkUI_FloatPropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeFloatProperty", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

ArkUI_Vector2PropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2Property(float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateVector2Property", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createVector2Property(x, y);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_Vector2Property* rsProperty = new ArkUI_Vector2Property({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetVector2PropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Vector2 property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setVector2Property(
        property->rsPropertyHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float* x, float* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetVector2PropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Vector2 property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getVector2Property(
        property->rsPropertyHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeVector2Property(ArkUI_Vector2PropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeVector2Property", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

ArkUI_ColorPropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorProperty(uint32_t value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateColorProperty", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createColorProperty(value);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_ColorProperty* rsProperty = new ArkUI_ColorProperty({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetColorPropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Color property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setColorProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t* value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetColorPropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Color property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getColorProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeColorProperty(ArkUI_ColorPropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeColorProperty", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

ArkUI_FloatAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatAnimatableProperty(float value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateFloatAnimatableProperty", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createFloatAnimatableProperty(value);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_FloatAnimatableProperty* rsProperty = new ArkUI_FloatAnimatableProperty({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetFloatAnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Float animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setFloatAnimatableProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float* value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetFloatAnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Float animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFloatAnimatableProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(ArkUI_FloatAnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeFloatAnimatableProperty", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

ArkUI_Vector2AnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateVector2AnimatableProperty(float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateVector2AnimatableProperty", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createVector2AnimatableProperty(x, y);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_Vector2AnimatableProperty* rsProperty = new ArkUI_Vector2AnimatableProperty({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float x, float y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetVector2AnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Vector2 animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setVector2AnimatableProperty(
        property->rsPropertyHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float* x, float* y)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetVector2AnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Vector2 animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getVector2AnimatableProperty(
        property->rsPropertyHandle, x, y);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(ArkUI_Vector2AnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeVector2AnimatableProperty", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

ArkUI_ColorAnimatablePropertyHandle OH_ArkUI_RenderNodeUtils_CreateColorAnimatableProperty(uint32_t value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateColorAnimatableProperty", 1);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, nullptr);
    auto* propertyPtr = impl->getNodeModifiers()->getNDKRenderNodeModifier()->createColorAnimatableProperty(value);
    if (!propertyPtr) {
        return nullptr;
    }
    ArkUI_ColorAnimatableProperty* rsProperty = new ArkUI_ColorAnimatableProperty({ propertyPtr });
    g_propertySet.insert(propertyPtr);
    return rsProperty;
}

int32_t OH_ArkUI_RenderNodeUtils_SetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetColorAnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Color animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setColorAnimatableProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t* value)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetColorAnimatablePropertyValue", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        property, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Color animatable property is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getColorAnimatableProperty(
        property->rsPropertyHandle, value);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

void OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(ArkUI_ColorAnimatablePropertyHandle property)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeColorAnimatableProperty", 1);
    CHECK_NULL_VOID(property);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(impl);
    g_propertySet.erase(property->rsPropertyHandle);
    impl->getNodeModifiers()->getNDKRenderNodeModifier()->disposeProperty(property->rsPropertyHandle);
    delete property;
    property = nullptr;
}

int32_t OH_ArkUI_RenderNodeUtils_SetContentModifierOnDraw(ArkUI_RenderContentModifierHandle modifier, void* userData,
    void (*callback)(ArkUI_DrawContext* context, void* userData))
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetContentModifierOnDraw", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        modifier, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Content modifier is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setModifierOnDraw(
        modifier->RenderModifierHandle, userData, reinterpret_cast<void (*)(ArkUIDrawingContext*, void*)>(callback));
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

/** 结构体类型写最下面,结构体内容参考 render_node.h*/
ArkUI_RectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRectShapeOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRectShapeOption", 1);
    ArkUI_RectShape* option = new ArkUI_RectShape { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ArkUI_RectShapeOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeRectShapeOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(
    ArkUI_RectShapeOption* option, float rect, ArkUI_EdgeDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRectShapeOptionEdgeValue", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_EDGE_DIRECTION_ALL:
            option->left = rect;
            option->right = rect;
            option->top = rect;
            option->bottom = rect;
            break;
        case ARKUI_EDGE_DIRECTION_LEFT:
            option->left = rect;
            break;
        case ARKUI_EDGE_DIRECTION_RIGHT:
            option->right = rect;
            break;
        case ARKUI_EDGE_DIRECTION_TOP:
            option->top = rect;
            break;
        case ARKUI_EDGE_DIRECTION_BOTTOM:
            option->bottom = rect;
            break;
        default:
            return;
    }
}

void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionValue(
    ArkUI_RectShapeOption* option, float x, float y, float width, float height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRectShapeOptionValue", 1);
    CHECK_NULL_VOID(option);
    option->left = x;
    option->top = y;
    option->right = x + width;
    option->bottom = y + height;
}

ArkUI_NodeBorderStyleOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateNodeBorderStyleOption", 1);
    ArkUI_NodeBorderStyle* option = new ArkUI_NodeBorderStyle {
        .leftStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .rightStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .topStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .bottomStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(ArkUI_NodeBorderStyleOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeNodeBorderStyleOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_NodeBorderStyleOption_SetLeftBorderStyle(ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle style)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetLeftBorderStyle", 1);
    CHECK_NULL_VOID(option);
    option->leftStyle = style;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
    ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle style, ArkUI_EdgeDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetNodeBorderStyleOptionEdgeStyle", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_EDGE_DIRECTION_ALL:
            option->leftStyle = style;
            option->rightStyle = style;
            option->topStyle = style;
            option->bottomStyle = style;
            break;
        case ARKUI_EDGE_DIRECTION_LEFT:
            option->leftStyle = style;
            break;
        case ARKUI_EDGE_DIRECTION_RIGHT:
            option->rightStyle = style;
            break;
        case ARKUI_EDGE_DIRECTION_TOP:
            option->topStyle = style;
            break;
        case ARKUI_EDGE_DIRECTION_BOTTOM:
            option->bottomStyle = style;
            break;
        default:
            return;
    }
}

ArkUI_NodeBorderWidthOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderWidthOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateNodeBorderWidthOption", 1);
    ArkUI_NodeBorderWidth* option = new ArkUI_NodeBorderWidth { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(ArkUI_NodeBorderWidthOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeNodeBorderWidthOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(
    ArkUI_NodeBorderWidthOption* option, float width, ArkUI_EdgeDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetNodeBorderWidthOptionEdgeWidth", 1);
    CHECK_NULL_VOID(option);
    if (OHOS::Ace::LessNotEqual(width, 0.0)) {
        return;
    }
    switch (direction) {
        case ARKUI_EDGE_DIRECTION_ALL:
            option->leftWidth = width;
            option->rightWidth = width;
            option->topWidth = width;
            option->bottomWidth = width;
            break;
        case ARKUI_EDGE_DIRECTION_LEFT:
            option->leftWidth = width;
            break;
        case ARKUI_EDGE_DIRECTION_RIGHT:
            option->rightWidth = width;
            break;
        case ARKUI_EDGE_DIRECTION_TOP:
            option->topWidth = width;
            break;
        case ARKUI_EDGE_DIRECTION_BOTTOM:
            option->bottomWidth = width;
            break;
        default:
            return;
    }
}

ArkUI_NodeBorderColorOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderColorOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateNodeBorderColorOption", 1);
    ArkUI_NodeBorderColor* option = new ArkUI_NodeBorderColor { 0, 0, 0, 0 };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(ArkUI_NodeBorderColorOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeNodeBorderColorOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(
    ArkUI_NodeBorderColorOption* option, uint32_t color, ArkUI_EdgeDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetNodeBorderColorOptionEdgeColor", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_EDGE_DIRECTION_ALL:
            option->leftColor = color;
            option->rightColor = color;
            option->topColor = color;
            option->bottomColor = color;
            break;
        case ARKUI_EDGE_DIRECTION_LEFT:
            option->leftColor = color;
            break;
        case ARKUI_EDGE_DIRECTION_RIGHT:
            option->rightColor = color;
            break;
        case ARKUI_EDGE_DIRECTION_TOP:
            option->topColor = color;
            break;
        case ARKUI_EDGE_DIRECTION_BOTTOM:
            option->bottomColor = color;
            break;
        default:
            return;
    }
}

ArkUI_NodeBorderRadiusOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderRadiusOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateNodeBorderRadiusOption", 1);
    ArkUI_NodeBorderRadius* option = new ArkUI_NodeBorderRadius { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(ArkUI_NodeBorderRadiusOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeNodeBorderRadiusOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(
    ArkUI_NodeBorderRadiusOption* option, uint32_t cornerRadius, ArkUI_CornerDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetNodeBorderRadiusOptionCornerRadius", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_CORNER_DIRECTION_ALL:
            option->topLeftRadius = cornerRadius;
            option->topRightRadius = cornerRadius;
            option->bottomLeftRadius = cornerRadius;
            option->bottomRightRadius = cornerRadius;
            break;
        case ARKUI_CORNER_DIRECTION_TOP_LEFT:
            option->topLeftRadius = cornerRadius;
            break;
        case ARKUI_CORNER_DIRECTION_TOP_RIGHT:
            option->topRightRadius = cornerRadius;
            break;
        case ARKUI_CORNER_DIRECTION_BOTTOM_LEFT:
            option->bottomLeftRadius = cornerRadius;
            break;
        case ARKUI_CORNER_DIRECTION_BOTTOM_RIGHT:
            option->bottomRightRadius = cornerRadius;
            break;
        default:
            return;
    }
}

ArkUI_CircleShapeOption* OH_ArkUI_RenderNodeUtils_CreateCircleShapeOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateCircleShapeOption", 1);
    ArkUI_CircleShape* option = new ArkUI_CircleShape { 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(ArkUI_CircleShapeOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeCircleShapeOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(ArkUI_CircleShapeOption* option, float centerX)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetCircleShapeOptionCenterX", 1);
    CHECK_NULL_VOID(option);
    option->centerX = centerX;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(ArkUI_CircleShapeOption* option, float centerY)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetCircleShapeOptionCenterY", 1);
    CHECK_NULL_VOID(option);
    option->centerY = centerY;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(ArkUI_CircleShapeOption* option, float radius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetCircleShapeOptionRadius", 1);
    CHECK_NULL_VOID(option);
    option->radius = radius;
}

ArkUI_RoundRectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRoundRectShapeOption", 1);
    ArkUI_RoundRectShape* option =
        new ArkUI_RoundRectShape { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(ArkUI_RoundRectShapeOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeRoundRectShapeOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(
    ArkUI_RoundRectShapeOption* option, float value, ArkUI_EdgeDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRoundRectShapeOptionEdgeValue", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_EDGE_DIRECTION_ALL:
            option->left = value;
            option->right = value;
            option->top = value;
            option->bottom = value;
            break;
        case ARKUI_EDGE_DIRECTION_LEFT:
            option->left = value;
            break;
        case ARKUI_EDGE_DIRECTION_RIGHT:
            option->right = value;
            break;
        case ARKUI_EDGE_DIRECTION_TOP:
            option->top = value;
            break;
        case ARKUI_EDGE_DIRECTION_BOTTOM:
            option->bottom = value;
            break;
        default:
            return;
    }
}

void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionValue(
    ArkUI_RoundRectShapeOption* option, float x, float y, float width, float height)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRoundRectShapeOptionValue", 1);
    CHECK_NULL_VOID(option);
    option->left = x;
    option->top = y;
    option->right = x + width;
    option->bottom = y + height;
}

void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
    ArkUI_RoundRectShapeOption* option, float x, float y, ArkUI_CornerDirection direction)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRoundRectShapeOptionCornerXY", 1);
    CHECK_NULL_VOID(option);
    switch (direction) {
        case ARKUI_CORNER_DIRECTION_ALL:
            option->topLeftX = x;
            option->topLeftY = y;
            option->topRightX = x;
            option->topRightY = y;
            option->bottomLeftX = x;
            option->bottomLeftY = y;
            option->bottomRightX = x;
            option->bottomRightY = y;
            break;
        case ARKUI_CORNER_DIRECTION_TOP_LEFT:
            option->topLeftX = x;
            option->topLeftY = y;
            break;
        case ARKUI_CORNER_DIRECTION_TOP_RIGHT:
            option->topRightX = x;
            option->topRightY = y;
            break;
        case ARKUI_CORNER_DIRECTION_BOTTOM_LEFT:
            option->bottomLeftX = x;
            option->bottomLeftY = y;
            break;
        case ARKUI_CORNER_DIRECTION_BOTTOM_RIGHT:
            option->bottomRightX = x;
            option->bottomRightY = y;
            break;
        default:
            return;
    }
}

ArkUI_CommandPathOption* OH_ArkUI_RenderNodeUtils_CreateCommandPathOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateCommandPathOption", 1);
    ArkUI_CommandPath* option = new ArkUI_CommandPath { "" };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(ArkUI_CommandPathOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeCommandPathOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(ArkUI_CommandPathOption* option, char* commands)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetCommandPathOptionCommands", 1);
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(commands);
    option->commands = commands;
}

int32_t OH_ArkUI_RenderNodeUtils_SetMask(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeMaskOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetMask", 1);
    if (node == nullptr || option == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node or mask option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    auto type = option->type;
    ArkUIMaskFill fillColor;
    fillColor.fillColor = option->fillColor;
    fillColor.strokeColor = option->strokeColor;
    fillColor.strokeWidth = option->strokeWidth;
    if (type == RECT_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRectMask(
            node->renderNodeHandle, option->rect, fillColor);
    } else if (type == CIRCLE_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCircleMask(
            node->renderNodeHandle, option->circle, fillColor);
    } else if (type == ROUND_RECT_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRoundRectMask(
            node->renderNodeHandle, option->roundRect, fillColor);
    } else if (type == OVAL_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setOvalMask(
            node->renderNodeHandle, option->oval, fillColor);
    } else if (type == COMMANDS) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCommandPathMask(
            node->renderNodeHandle, option->commands, fillColor);
    }
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetClip(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeClipOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetClip", 1);
    if (node == nullptr || option == nullptr) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node or clip option is null");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR;
    auto type = option->type;
    if (type == RECT_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRectClip(
            node->renderNodeHandle, option->rect);
    } else if (type == CIRCLE_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCircleClip(
            node->renderNodeHandle, option->circle);
    } else if (type == ROUND_RECT_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRoundRectClip(
            node->renderNodeHandle, option->roundRect);
    } else if (type == OVAL_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setOvalClip(
            node->renderNodeHandle, option->oval);
    } else if (type == COMMANDS) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCommandPathClip(
            node->renderNodeHandle, option->commands);
    }
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(
    ArkUI_RectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeMaskOptionFromRectShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .rect = rectShape, .type = RECT_SHAPE };
    return option;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeMaskOptionFromRoundRectShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRoundRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    rectShape.topLeftX = shape->topLeftX;
    rectShape.topLeftY = shape->topLeftY;
    rectShape.topRightX = shape->topRightX;
    rectShape.topRightY = shape->topRightY;
    rectShape.bottomLeftX = shape->bottomLeftX;
    rectShape.bottomLeftY = shape->bottomLeftY;
    rectShape.bottomRightX = shape->bottomRightX;
    rectShape.bottomRightY = shape->bottomRightY;
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .roundRect = rectShape,
        .type = ROUND_RECT_SHAPE };
    return option;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeMaskOptionFromCircleShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUICircleShape rectShape;
    rectShape.centerX = shape->centerX;
    rectShape.centerY = shape->centerY;
    rectShape.radius = shape->radius;
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .circle = rectShape, .type = CIRCLE_SHAPE };
    return option;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromOvalShape(
    ArkUI_RectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeMaskOptionFromOvalShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .oval = rectShape, .type = OVAL_SHAPE };
    return option;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromCommandPath(
    ArkUI_CommandPathOption* path)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeMaskOptionFromCommandPath", 1);
    CHECK_NULL_RETURN(path, nullptr);
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .commands = path->commands,
        .type = COMMANDS };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(ArkUI_RenderNodeMaskOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeRenderNodeMaskOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(ArkUI_RenderNodeMaskOption* option, uint32_t fillColor)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRenderNodeMaskOptionFillColor", 1);
    CHECK_NULL_VOID(option);
    option->fillColor = fillColor;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(
    ArkUI_RenderNodeMaskOption* option, uint32_t strokeColor)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRenderNodeMaskOptionStrokeColor", 1);
    CHECK_NULL_VOID(option);
    option->strokeColor = strokeColor;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(ArkUI_RenderNodeMaskOption* option, float strokeWidth)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetRenderNodeMaskOptionStrokeWidth", 1);
    CHECK_NULL_VOID(option);
    option->strokeWidth = strokeWidth;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRectShape(
    ArkUI_RectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeClipOptionFromRectShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .rect = rectShape, .type = RECT_SHAPE };
    return option;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRoundRectShape(
    ArkUI_RoundRectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeClipOptionFromRoundRectShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRoundRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    rectShape.topLeftX = shape->topLeftX;
    rectShape.topLeftY = shape->topLeftY;
    rectShape.topRightX = shape->topRightX;
    rectShape.topRightY = shape->topRightY;
    rectShape.bottomLeftX = shape->bottomLeftX;
    rectShape.bottomLeftY = shape->bottomLeftY;
    rectShape.bottomRightX = shape->bottomRightX;
    rectShape.bottomRightY = shape->bottomRightY;
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .roundRect = rectShape,
        .type = ROUND_RECT_SHAPE };
    return option;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCircleShape(
    ArkUI_CircleShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeClipOptionFromCircleShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUICircleShape rectShape;
    rectShape.centerX = shape->centerX;
    rectShape.centerY = shape->centerY;
    rectShape.radius = shape->radius;
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .circle = rectShape, .type = CIRCLE_SHAPE };
    return option;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromOvalShape(
    ArkUI_RectShapeOption* shape)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeClipOptionFromOvalShape", 1);
    CHECK_NULL_RETURN(shape, nullptr);
    ArkUIRectShape rectShape;
    rectShape.left = shape->left;
    rectShape.right = shape->right;
    rectShape.top = shape->top;
    rectShape.bottom = shape->bottom;
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .oval = rectShape, .type = OVAL_SHAPE };
    return option;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromCommandPath(
    ArkUI_CommandPathOption* path)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateRenderNodeClipOptionFromCommandPath", 1);
    CHECK_NULL_RETURN(path, nullptr);
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .commands = path->commands,
        .type = COMMANDS };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(ArkUI_RenderNodeClipOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeRenderNodeClipOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

int32_t OH_ArkUI_RenderNodeUtils_GetRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle* renderNode)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "GetRenderNode", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        renderNode, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_RENDER_NOT_ADOPTED_NODE, __FUNCTION__, "Node is not an adopted node");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    ArkUIRenderNodeHandle renderNodeHandle;
    int renderNodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getRenderNode(
        node->uiNodeHandle, &renderNodeHandle, &renderNodeId);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        auto iter = g_renderNodeMap.find(renderNodeId);
        if (iter == g_renderNodeMap.end()) {
            g_renderNodeMap.insert(std::pair<int32_t, ArkUIRenderNodeHandle>(renderNodeId, renderNodeHandle));
        }
        *renderNode = new ArkUI_RenderNode({ renderNodeHandle });
    }
    return result;
}

ArkUI_RenderBlurStyleOption* OH_ArkUI_RenderNodeUtils_CreateBlurStyleOption()
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "CreateBlurStyleOption", 1);
    return new ArkUI_RenderBlurStyleOption { 0.0f };
}

void OH_ArkUI_RenderNodeUtils_DisposeBlurStyleOption(ArkUI_RenderBlurStyleOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "DisposeBlurStyleOption", 1);
    CHECK_NULL_VOID(option);
    delete option;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBlurStyleOptionRadius(ArkUI_RenderBlurStyleOption* option, float radius)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBlurStyleOptionRadius", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Blur option is null");
    if (radius < 0.0f) {
        SET_ERROR_MESSAGE(OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__,
            "Blur radius must be greater than or equal to 0.");
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->radius = radius;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetBackgroundBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Blur option is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    float radius = option->radius;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBackgroundBlurOption(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_ResetBackgroundBlurOption(ArkUI_RenderNodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "ResetBackgroundBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->resetBackgroundBlurOption(
        node->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetForegroundBlurOption(
    ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetForegroundBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Blur option is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    float radius = option->radius;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setForegroundBlurOption(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_ResetForegroundBlurOption(ArkUI_RenderNodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "ResetForegroundBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->resetForegroundBlurOption(
        node->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetContentBlurOption(ArkUI_RenderNodeHandle node, ArkUI_RenderBlurStyleOption* option)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "SetContentBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    CHECK_NULL_RETURN_WITH_MESSAGE(
        option, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Blur option is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    float radius = option->radius;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setContentBlurOption(
        node->renderNodeHandle, radius);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_ResetContentBlurOption(ArkUI_RenderNodeHandle node)
{
    ACE_ENGINE_HISTOGRAM_BOOLEAN(METRIC_PREFIX_NATIVE_RENDER "ResetContentBlurOption", 1);
    CHECK_NULL_RETURN_WITH_MESSAGE(
        node, OHOS::Ace::ERROR_CODE_PARAM_INVALID, __FUNCTION__, "Render node is null");
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN_WITH_MESSAGE(
        impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR, __FUNCTION__, "Native module not initialized");
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->resetContentBlurOption(
        node->renderNodeHandle);
    if (result != OHOS::Ace::ERROR_CODE_NO_ERROR) {
        SET_ERROR_FUNCTION_NAME(__FUNCTION__);
    }
    return result;
}

#ifdef __cplusplus
};
#endif
