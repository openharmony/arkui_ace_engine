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
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

std::map<int32_t, ArkUIRenderNodeHandle> g_renderNodeMap;
std::set<ArkUIRenderModifierHandle> g_modifierSet;
std::set<ArkUIPropertyHandle> g_propertySet;

int32_t OH_ArkUI_RenderNodeUtils_AddRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(child, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->addRenderNode(
        node->uiNodeHandle, child->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_RemoveRenderNode(ArkUI_NodeHandle node, ArkUI_RenderNodeHandle child)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(child, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->removeRenderNode(
        node->uiNodeHandle, child->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_ClearRenderNodeChildren(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (node->type != ArkUI_NodeType::ARKUI_NODE_CUSTOM) {
        return OHOS::Ace::ERROR_CODE_NOT_CUSTOM_NODE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->clearRenderNodeChildren(node->uiNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_Invalidate(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    impl->getNodeModifiers()->getFrameNodeModifier()->invalidate(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_RenderNodeHandle OH_ArkUI_RenderNodeUtils_CreateNode()
{
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    auto nodeId = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getId(node->renderNodeHandle);
    if (nodeId == 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    auto it = g_renderNodeMap.find(nodeId);
    if (it != g_renderNodeMap.end()) {
        g_renderNodeMap.erase(it);
    }
    delete node;
    node = nullptr;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RenderNodeUtils_AddChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child)
{
    CHECK_NULL_RETURN(node && child, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->addChild(
        node->renderNodeHandle, child->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_InsertChildAfter(
    ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child, ArkUI_RenderNodeHandle sibling)
{
    CHECK_NULL_RETURN(node && child && sibling, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->insertChildAfter(
        node->renderNodeHandle, child->renderNodeHandle, sibling->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_RemoveChild(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeHandle child)
{
    CHECK_NULL_RETURN(node && child, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->removeChild(
        node->renderNodeHandle, child->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_ClearChildren(ArkUI_RenderNodeHandle node)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->clearChildren(node->renderNodeHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_GetChild(ArkUI_RenderNodeHandle node, int32_t index, ArkUI_RenderNodeHandle* child)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (index < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChild(
        node->renderNodeHandle, index, &renderNode, &nodeId);
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFirstChild(
        node->renderNodeHandle, &renderNode, &nodeId);
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getNextSibling(
        node->renderNodeHandle, &renderNode, &nodeId);
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    ArkUIRenderNodeHandle renderNode;
    int32_t nodeId = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPreviousSibling(
        node->renderNodeHandle, &renderNode, &nodeId);
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    ArkUIRenderNodeHandle* renderNode;
    uint32_t* nodeId;
    int32_t nodeCount = 0;
    auto result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChildren(
        node->renderNodeHandle, &renderNode, &nodeId, &nodeCount);
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
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    int32_t childCount;
    auto result =
        impl->getNodeModifiers()->getNDKRenderNodeModifier()->getChildrenCount(node->renderNodeHandle, &childCount);
    if (result == OHOS::Ace::ERROR_CODE_NO_ERROR) {
        *count = childCount;
    }
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t color)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBackgroundColor(node->renderNodeHandle, color);
}

int32_t OH_ArkUI_RenderNodeUtils_GetBackgroundColor(ArkUI_RenderNodeHandle node, uint32_t* color)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBackgroundColor(node->renderNodeHandle, color);
}

int32_t OH_ArkUI_RenderNodeUtils_SetOpacity(ArkUI_RenderNodeHandle node, float opacity)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!OHOS::Ace::InRegion(0, 1, opacity)) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setOpacity(node->renderNodeHandle, opacity);
}

int32_t OH_ArkUI_RenderNodeUtils_GetOpacity(ArkUI_RenderNodeHandle node, float* opacity)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getOpacity(node->renderNodeHandle, opacity);
}

int32_t OH_ArkUI_RenderNodeUtils_SetSize(ArkUI_RenderNodeHandle node, int32_t width, int32_t height)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (width < 0 || height < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setSize(node->renderNodeHandle, width, height);
}

int32_t OH_ArkUI_RenderNodeUtils_GetSize(ArkUI_RenderNodeHandle node, int32_t* width, int32_t* height)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getSize(node->renderNodeHandle, width, height);
}

int32_t OH_ArkUI_RenderNodeUtils_SetPosition(ArkUI_RenderNodeHandle node, int32_t x, int32_t y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setPosition(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetPosition(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPosition(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_SetPivot(ArkUI_RenderNodeHandle node, float x, float y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setPivot(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetPivot(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getPivot(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_SetScale(ArkUI_RenderNodeHandle node, float x, float y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setScale(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetScale(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getScale(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_SetTranslation(ArkUI_RenderNodeHandle node, float x, float y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setTranslation(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetTranslation(ArkUI_RenderNodeHandle node, float* x, float* y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getTranslation(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_SetRotation(ArkUI_RenderNodeHandle node, float x, float y, float z)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRotation(node->renderNodeHandle, x, y, z);
}

int32_t OH_ArkUI_RenderNodeUtils_GetRotation(ArkUI_RenderNodeHandle node, float* x, float* y, float* z)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getRotation(node->renderNodeHandle, x, y, z);
}

int32_t OH_ArkUI_RenderNodeUtils_SetTransform(ArkUI_RenderNodeHandle node, float* matrix)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setTransform(node->renderNodeHandle, matrix);
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowColor(ArkUI_RenderNodeHandle node, uint32_t color)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowColor(node->renderNodeHandle, color);
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowColor(ArkUI_RenderNodeHandle node, uint32_t* color)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowColor(node->renderNodeHandle, color);
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowOffset(ArkUI_RenderNodeHandle node, int32_t x, int32_t y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowOffset(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowOffset(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowOffset(node->renderNodeHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowAlpha(ArkUI_RenderNodeHandle node, float alpha)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!OHOS::Ace::InRegion(0, 1, alpha)) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowAlpha(node->renderNodeHandle, alpha);
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowAlpha(ArkUI_RenderNodeHandle node, float* alpha)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowAlpha(node->renderNodeHandle, alpha);
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowElevation(ArkUI_RenderNodeHandle node, float elevation)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (elevation < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowElevation(node->renderNodeHandle, elevation);
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowElevation(ArkUI_RenderNodeHandle node, float* radius)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowElevation(node->renderNodeHandle, radius);
}

int32_t OH_ArkUI_RenderNodeUtils_GetShadowRadius(ArkUI_RenderNodeHandle node, float* radius)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getShadowRadius(node->renderNodeHandle, radius);
}

int32_t OH_ArkUI_RenderNodeUtils_SetShadowRadius(ArkUI_RenderNodeHandle node, float radius)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (radius < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setShadowRadius(node->renderNodeHandle, radius);
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption* borderStyle)
{
    if (node == nullptr || borderStyle == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderStyle(node->renderNodeHandle,
        borderStyle->leftStyle, borderStyle->topStyle, borderStyle->rightStyle, borderStyle->bottomStyle);
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderStyle(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderStyleOption** borderStyle)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    int32_t code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderStyle(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(&((*borderStyle)->leftStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->topStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->rightStyle)),
        reinterpret_cast<uint32_t*>(&((*borderStyle)->leftStyle)));
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidthOption* borderWidth)
{
    if (node == nullptr || borderWidth == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderWidth(node->renderNodeHandle,
        borderWidth->leftWidth, borderWidth->topWidth, borderWidth->rightWidth, borderWidth->bottomWidth);
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderWidth(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderWidth** borderWidth)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    int32_t code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderWidth(node->renderNodeHandle,
        reinterpret_cast<float*>(&((*borderWidth)->leftWidth)), reinterpret_cast<float*>(&((*borderWidth)->topWidth)),
        reinterpret_cast<float*>(&((*borderWidth)->rightWidth)),
        reinterpret_cast<float*>(&((*borderWidth)->leftWidth)));
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColor* borderColor)
{
    if (node == nullptr || borderColor == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderColor(node->renderNodeHandle,
        borderColor->leftColor, borderColor->topColor, borderColor->rightColor, borderColor->bottomColor);
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderColor(ArkUI_RenderNodeHandle node, ArkUI_NodeBorderColor** borderColor)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    int32_t code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderColor(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(&((*borderColor)->leftColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->topColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->rightColor)),
        reinterpret_cast<uint32_t*>(&((*borderColor)->leftColor)));
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetBorderRadius(ArkUI_RenderNodeHandle node,
    ArkUI_NodeBorderRadiusOption* borderRadius)
{
    if (node == nullptr || borderRadius == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBorderRadius(node->renderNodeHandle,
        borderRadius->topLeftRadius, borderRadius->topRightRadius,
        borderRadius->bottomLeftRadius, borderRadius->bottomRightRadius);
}

int32_t OH_ArkUI_RenderNodeUtils_GetBorderRadius(ArkUI_RenderNodeHandle node,
    ArkUI_NodeBorderRadiusOption** borderRadius)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    int32_t code = impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBorderRadius(node->renderNodeHandle,
        reinterpret_cast<float*>(&((*borderRadius)->topLeftRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->topRightRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->bottomLeftRadius)),
        reinterpret_cast<float*>(&((*borderRadius)->bottomRightRadius)));
    return code;
}

int32_t OH_ArkUI_RenderNodeUtils_SetMarkNodeGroup(ArkUI_RenderNodeHandle node, bool markNodeGroup)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setMarkNodeGroup(node->renderNodeHandle,
        static_cast<int32_t>(markNodeGroup));
}

int32_t OH_ArkUI_RenderNodeUtils_SetBounds(ArkUI_RenderNodeHandle node,
    int32_t x, int32_t y, int32_t width, int32_t height)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (width < 0 || height < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setBounds(node->renderNodeHandle,
        static_cast<uint32_t>(x), static_cast<uint32_t>(y),
        static_cast<uint32_t>(width), static_cast<uint32_t>(height));
}

int32_t OH_ArkUI_RenderNodeUtils_GetBounds(ArkUI_RenderNodeHandle node, int32_t* x, int32_t* y, int32_t* width,
    int32_t* height)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getBounds(node->renderNodeHandle,
        reinterpret_cast<uint32_t*>(x), reinterpret_cast<uint32_t*>(y),
        reinterpret_cast<uint32_t*>(width), reinterpret_cast<uint32_t*>(height));
}

int32_t OH_ArkUI_RenderNodeUtils_SetDrawRegion(ArkUI_RenderNodeHandle node, float x, float y, float w, float h)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setDrawRegion(node->renderNodeHandle, x, y, w, h);
}

int32_t OH_ArkUI_RenderNodeUtils_SetClipToFrame(ArkUI_RenderNodeHandle node, int32_t clipToFrame)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!OHOS::Ace::InRegion(0, 1, clipToFrame)) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setClipToFrame(node->renderNodeHandle, clipToFrame);
}

int32_t OH_ArkUI_RenderNodeUtils_GetClipToFrame(ArkUI_RenderNodeHandle node, int32_t* clipToFrame)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getClipToFrame(node->renderNodeHandle, clipToFrame);
}

int32_t OH_ArkUI_RenderNodeUtils_SetClipToBounds(ArkUI_RenderNodeHandle node, int32_t clipToBounds)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    if (!OHOS::Ace::InRegion(0, 1, clipToBounds)) {
        return OHOS::Ace::ERROR_CODE_PARAM_OUT_OF_RANGE;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setClipToBounds(node->renderNodeHandle, clipToBounds);
}

int32_t OH_ArkUI_RenderNodeUtils_GetClipToBounds(ArkUI_RenderNodeHandle node, int32_t* clipToBounds)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getClipToBounds(node->renderNodeHandle, clipToBounds);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachContentModifier(
    ArkUI_RenderNodeHandle node, ArkUI_RenderContentModifierHandle modifier)
{
    if (node == nullptr || modifier == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachModifier(
        node->renderNodeHandle, modifier->RenderModifierHandle);
}

ArkUI_RenderContentModifierHandle OH_ArkUI_RenderNodeUtils_CreateContentModifier()
{
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
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachVector2Property(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2PropertyHandle property)
{
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachColorProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorPropertyHandle property)
{
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachFloatAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_FloatAnimatablePropertyHandle property)
{
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachVector2AnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_Vector2AnimatablePropertyHandle property)
{
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

int32_t OH_ArkUI_RenderNodeUtils_AttachColorAnimatableProperty(
    ArkUI_RenderContentModifierHandle modifier, ArkUI_ColorAnimatablePropertyHandle property)
{
    if (modifier == nullptr || property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->attachProperty(
        modifier->RenderModifierHandle, property->rsPropertyHandle);
}

ArkUI_FloatPropertyHandle OH_ArkUI_RenderNodeUtils_CreateFloatProperty(float value)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setFloatProperty(property->rsPropertyHandle, value);
}

int32_t OH_ArkUI_RenderNodeUtils_GetFloatPropertyValue(ArkUI_FloatPropertyHandle property, float* value)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFloatProperty(property->rsPropertyHandle, value);
}

void OH_ArkUI_RenderNodeUtils_DisposeFloatProperty(ArkUI_FloatPropertyHandle property)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setVector2Property(property->rsPropertyHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetVector2PropertyValue(ArkUI_Vector2PropertyHandle property, float* x, float* y)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getVector2Property(property->rsPropertyHandle, x, y);
}

void OH_ArkUI_RenderNodeUtils_DisposeVector2Property(ArkUI_Vector2PropertyHandle property)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setColorProperty(property->rsPropertyHandle, value);
}

int32_t OH_ArkUI_RenderNodeUtils_GetColorPropertyValue(ArkUI_ColorPropertyHandle property, uint32_t* value)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getColorProperty(property->rsPropertyHandle, value);
}

void OH_ArkUI_RenderNodeUtils_DisposeColorProperty(ArkUI_ColorPropertyHandle property)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setFloatAnimatableProperty(
        property->rsPropertyHandle, value);
}

int32_t OH_ArkUI_RenderNodeUtils_GetFloatAnimatablePropertyValue(
    ArkUI_FloatAnimatablePropertyHandle property, float* value)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getFloatAnimatableProperty(
        property->rsPropertyHandle, value);
}

void OH_ArkUI_RenderNodeUtils_DisposeFloatAnimatableProperty(ArkUI_FloatAnimatablePropertyHandle property)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setVector2AnimatableProperty(
        property->rsPropertyHandle, x, y);
}

int32_t OH_ArkUI_RenderNodeUtils_GetVector2AnimatablePropertyValue(
    ArkUI_Vector2AnimatablePropertyHandle property, float* x, float* y)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getVector2AnimatableProperty(
        property->rsPropertyHandle, x, y);
}

void OH_ArkUI_RenderNodeUtils_DisposeVector2AnimatableProperty(ArkUI_Vector2AnimatablePropertyHandle property)
{
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
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setColorAnimatableProperty(
        property->rsPropertyHandle, value);
}

int32_t OH_ArkUI_RenderNodeUtils_GetColorAnimatablePropertyValue(
    ArkUI_ColorAnimatablePropertyHandle property, uint32_t* value)
{
    if (property == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->getColorAnimatableProperty(
        property->rsPropertyHandle, value);
}

void OH_ArkUI_RenderNodeUtils_DisposeColorAnimatableProperty(ArkUI_ColorAnimatablePropertyHandle property)
{
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
    CHECK_NULL_RETURN(modifier, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    return impl->getNodeModifiers()->getNDKRenderNodeModifier()->setModifierOnDraw(
        modifier->RenderModifierHandle, userData, reinterpret_cast<void (*)(ArkUIDrawingContext*, void*)>(callback));
}

/** 结构体类型写最下面,结构体内容参考 render_node.h*/
ArkUI_RectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRectShapeOption()
{
    ArkUI_RectShape* option = new ArkUI_RectShape { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRectShapeOption(ArkUI_RectShapeOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRectShapeOptionEdgeValue(
    ArkUI_RectShapeOption* option, float top, float right, float bottom, float left)
{
    CHECK_NULL_VOID(option);
    option->left = left;
    option->right = right;
    option->top = top;
    option->bottom = bottom;
}

ArkUI_NodeBorderStyleOption* OH_ArkUI_RenderNodeUtils_CreateNodeBorderStyleOption()
{
    ArkUI_NodeBorderStyle* option = new ArkUI_NodeBorderStyle {
        .leftStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .rightStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .topStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID,
        .bottomStyle = ArkUI_BorderStyle::ARKUI_BORDER_STYLE_SOLID };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderStyleOption(ArkUI_NodeBorderStyleOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_NodeBorderStyleOption_SetLeftBorderStyle(ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle style)
{
    CHECK_NULL_VOID(option);
    option->leftStyle = style;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderStyleOptionEdgeStyle(
    ArkUI_NodeBorderStyleOption* option, ArkUI_BorderStyle style, ArkUI_EdgeDirection direction)
{
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
    ArkUI_NodeBorderWidth* option = new ArkUI_NodeBorderWidth { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderWidthOption(ArkUI_NodeBorderWidthOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderWidthOptionEdgeWidth(
    ArkUI_NodeBorderWidthOption* option, float width, ArkUI_EdgeDirection direction)
{
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
    ArkUI_NodeBorderColor* option = new ArkUI_NodeBorderColor { 0, 0, 0, 0 };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderColorOption(ArkUI_NodeBorderColorOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderColorOptionEdgeColor(
    ArkUI_NodeBorderColorOption* option, uint32_t color, ArkUI_EdgeDirection direction)
{
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
    ArkUI_NodeBorderRadius* option = new ArkUI_NodeBorderRadius { 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeNodeBorderRadiusOption(ArkUI_NodeBorderRadiusOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetNodeBorderRadiusOptionCornerRadius(
    ArkUI_NodeBorderRadiusOption* option, uint32_t cornerRadius, ArkUI_CornerDirection direction)
{
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
    ArkUI_CircleShape* option = new ArkUI_CircleShape { 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeCircleShapeOption(ArkUI_CircleShapeOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterX(ArkUI_CircleShapeOption* option, float centerX)
{
    CHECK_NULL_VOID(option);
    option->centerX = centerX;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionCenterY(ArkUI_CircleShapeOption* option, float centerY)
{
    CHECK_NULL_VOID(option);
    option->centerY = centerY;
}

void OH_ArkUI_RenderNodeUtils_SetCircleShapeOptionRadius(ArkUI_CircleShapeOption* option, float radius)
{
    CHECK_NULL_VOID(option);
    option->radius = radius;
}

ArkUI_RoundRectShapeOption* OH_ArkUI_RenderNodeUtils_CreateRoundRectShapeOption()
{
    ArkUI_RoundRectShape* option =
        new ArkUI_RoundRectShape { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRoundRectShapeOption(ArkUI_RoundRectShapeOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionEdgeValue(
    ArkUI_RoundRectShapeOption* option, float top, float right, float bottom, float left)
{
    CHECK_NULL_VOID(option);
    option->left = left;
    option->right = right;
    option->top = top;
    option->bottom = bottom;
}

void OH_ArkUI_RenderNodeUtils_SetRoundRectShapeOptionCornerXY(
    ArkUI_RoundRectShapeOption* option, float x, float y, ArkUI_CornerDirection direction)
{
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
    ArkUI_CommandPath* option = new ArkUI_CommandPath { "" };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeCommandPathOption(ArkUI_CommandPathOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetCommandPathOptionCommands(ArkUI_CommandPathOption* option, char* commands)
{
    CHECK_NULL_VOID(option);
    CHECK_NULL_VOID(commands);
    option->commands = commands;
}

int32_t OH_ArkUI_RenderNodeUtils_SetMask(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeMaskOption* option)
{
    if (node == nullptr || option == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
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
    return result;
}

int32_t OH_ArkUI_RenderNodeUtils_SetClip(ArkUI_RenderNodeHandle node, ArkUI_RenderNodeClipOption* option)
{
    if (node == nullptr || option == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    auto result = OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR;
    auto type = option->type;
    if (type == RECT_SHAPE) {
        result =
            impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRectClip(node->renderNodeHandle, option->rect);
    } else if (type == CIRCLE_SHAPE) {
        result =
            impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCircleClip(node->renderNodeHandle, option->circle);
    } else if (type == ROUND_RECT_SHAPE) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setRoundRectClip(
            node->renderNodeHandle, option->roundRect);
    } else if (type == OVAL_SHAPE) {
        result =
            impl->getNodeModifiers()->getNDKRenderNodeModifier()->setOvalClip(node->renderNodeHandle, option->oval);
    } else if (type == COMMANDS) {
        result = impl->getNodeModifiers()->getNDKRenderNodeModifier()->setCommandPathClip(
            node->renderNodeHandle, option->commands);
    }
    return result;
}

ArkUI_RenderNodeMaskOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeMaskOptionFromRectShape(
    ArkUI_RectShapeOption* shape)
{
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
    CHECK_NULL_RETURN(path, nullptr);
    ArkUI_RenderNodeMaskOption* option = new ArkUI_RenderNodeMaskOption { .commands = path->commands,
        .type = COMMANDS };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeMaskOption(ArkUI_RenderNodeMaskOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionFillColor(ArkUI_RenderNodeMaskOption* option, uint32_t fillColor)
{
    CHECK_NULL_VOID(option);
    option->fillColor = fillColor;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeColor(
    ArkUI_RenderNodeMaskOption* option, uint32_t strokeColor)
{
    CHECK_NULL_VOID(option);
    option->strokeColor = strokeColor;
}

void OH_ArkUI_RenderNodeUtils_SetRenderNodeMaskOptionStrokeWidth(ArkUI_RenderNodeMaskOption* option, float strokeWidth)
{
    CHECK_NULL_VOID(option);
    option->strokeWidth = strokeWidth;
}

ArkUI_RenderNodeClipOption* OH_ArkUI_RenderNodeUtils_CreateRenderNodeClipOptionFromRectShape(
    ArkUI_RectShapeOption* shape)
{
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
    CHECK_NULL_RETURN(path, nullptr);
    ArkUI_RenderNodeClipOption* option = new ArkUI_RenderNodeClipOption { .commands = path->commands,
        .type = COMMANDS };
    return option;
}

void OH_ArkUI_RenderNodeUtils_DisposeRenderNodeClipOption(ArkUI_RenderNodeClipOption* option)
{
    CHECK_NULL_VOID(option);
    delete option;
}

#ifdef __cplusplus
};
#endif
