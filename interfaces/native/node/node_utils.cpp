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


#include <cstdlib>
#include "node_model.h"
#include "node_extened.h"

#include "base/utils/utils.h"
#include "base/error/error_code.h"
#include "core/components_v2/inspector/inspector_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

int32_t OH_ArkUI_NodeUtils_GetLayoutSize(ArkUI_NodeHandle node, ArkUI_IntSize* size)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Int32* tempSize = new ArkUI_Int32[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getLayoutSize(node->uiNodeHandle, tempSize);
    size->width = tempSize[0];
    size->height = tempSize[1];
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPosition(ArkUI_NodeHandle node, ArkUI_IntOffset* localOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto value = impl->getNodeModifiers()->getFrameNodeModifier()->getLayoutPositionWithoutMargin(node->uiNodeHandle);
    localOffset->x = static_cast<int32_t>(value[0]);
    localOffset->y = static_cast<int32_t>(value[1]);

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToWindow(node->uiNodeHandle, &tempOffset, false);
    globalOffset->x = tempOffset[0];
    globalOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* screenOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToScreen(node->uiNodeHandle, &tempOffset, false);
    screenOffset->x = tempOffset[0];
    screenOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInWindow(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToWindowWithTransform(
        node->uiNodeHandle, &tempOffset, false);
    translateOffset->x = tempOffset[0];
    translateOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetPositionWithTranslateInScreen(ArkUI_NodeHandle node, ArkUI_IntOffset* translateOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToScreenWithTransform(
        node->uiNodeHandle, &tempOffset, false);
    translateOffset->x = tempOffset[0];
    translateOffset->y = tempOffset[1];

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RegisterSystemColorModeChangeEvent(
    ArkUI_NodeHandle node, void* userData, void (*onColorModeChange)(ArkUI_SystemColorMode colorMode, void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->setSystemColorModeChangeEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onColorModeChange));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_UnregisterSystemColorModeChangeEvent(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetSystemColorModeChangeEvent(node->uiNodeHandle);
}

int32_t OH_ArkUI_RegisterSystemFontStyleChangeEvent(
    ArkUI_NodeHandle node, void* userData, void (*onFontStyleChange)(ArkUI_SystemFontStyleEvent* event, void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->setSystemFontStyleChangeEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onFontStyleChange));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void OH_ArkUI_UnregisterSystemFontStyleChangeEvent(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetSystemFontStyleChangeEvent(node->uiNodeHandle);
}

float OH_ArkUI_SystemFontStyleEvent_GetFontSizeScale(const ArkUI_SystemFontStyleEvent* event)
{
    return event->fontSize;
}

float OH_ArkUI_SystemFontStyleEvent_GetFontWeightScale(const ArkUI_SystemFontStyleEvent* event)
{
    return event->fontWeight;
}

void OH_ArkUI_NodeUtils_AddCustomProperty(ArkUI_NodeHandle node, const char* name, const char* value)
{
    if (node == nullptr) {
        return;
    }
    if (name == nullptr || value == nullptr) {
        LOGF("AddCustomProperty input params name or value is nullptr");
        abort();
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->addCustomProperty(node->uiNodeHandle, name, value);
}

void OH_ArkUI_NodeUtils_RemoveCustomProperty(ArkUI_NodeHandle node, const char* name)
{
    if (node == nullptr) {
        return;
    }
    if (name == nullptr) {
        LOGF("RemoveCustomProperty input params name is nullptr");
        abort();
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->removeCustomProperty(node->uiNodeHandle, name);
}

int32_t OH_ArkUI_NodeUtils_GetCustomProperty(ArkUI_NodeHandle node, const char* name, ArkUI_CustomProperty** handle)
{
    if (node == nullptr || name == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    char* value = nullptr;
    impl->getNodeModifiers()->getFrameNodeModifier()->getCustomProperty(node->uiNodeHandle, name, &value);
    *handle  = new ArkUI_CustomProperty({ .value = value });
    
    return 0;
}

ArkUI_NodeHandle GetArkUINode(ArkUINodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    void* attachNode = impl->getExtendedAPI()->getAttachNodePtr(node);
    if (attachNode) {
        return reinterpret_cast<ArkUI_NodeHandle>(attachNode);
    }
    ArkUI_Node* arkUINode = new ArkUI_Node({ -1, node, false });
    impl->getExtendedAPI()->setAttachNodePtr((arkUINode)->uiNodeHandle, reinterpret_cast<void*>(arkUINode));
    return reinterpret_cast<ArkUI_NodeHandle>(arkUINode);
}

int32_t OH_ArkUI_NodeUtils_GetActiveChildrenInfo(ArkUI_NodeHandle head, ArkUI_ActiveChildrenInfo** handle)
{
    CHECK_NULL_RETURN(head, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    ArkUINodeHandle* innerNodes = nullptr;
    int32_t totalSize = 0;
    impl->getNodeModifiers()->getFrameNodeModifier()->getActiveChildrenInfo(
        head->uiNodeHandle, &innerNodes, &totalSize);
    *handle = new ArkUI_ActiveChildrenInfo({ .nodeList = nullptr, .nodeCount = totalSize });
    (*handle)->nodeCount = totalSize;
    if (totalSize > 0) {
        (*handle)->nodeList = new ArkUI_NodeHandle[totalSize] {};
        for (uint32_t i = 0; i < totalSize; i++) {
            ((*handle)->nodeList[i]) = GetArkUINode(innerNodes[i]);
        }
    }
    delete[] innerNodes;
    return 0;
}

ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetParentInPageTree(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getParent(node->uiNodeHandle);
    return GetArkUINode(attachNode);
}

ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetCurrentPageRootNode(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getCurrentPageRootNode(node->uiNodeHandle);
    return GetArkUINode(attachNode);
}

bool OH_ArkUI_NodeUtils_IsCreatedByNDK(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return 0;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    return impl->getNodeModifiers()->getFrameNodeModifier()->getNodeTag(node->uiNodeHandle);
}

int32_t OH_ArkUI_NodeUtils_GetNodeType(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return -1;
    }
    if (node->type != -1) {
        return node->type;
    }

    static const std::unordered_map<std::string, ArkUI_NodeType> nodeTypeMap = {
        { OHOS::Ace::V2::TEXT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT },
        { OHOS::Ace::V2::SPAN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SPAN },
        { OHOS::Ace::V2::IMAGE_SPAN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE_SPAN },
        { OHOS::Ace::V2::IMAGE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE },
        { OHOS::Ace::V2::TOGGLE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TOGGLE },
        { OHOS::Ace::V2::LOADING_PROGRESS_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LOADING_PROGRESS },
        { OHOS::Ace::V2::TEXTINPUT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_INPUT },
        { OHOS::Ace::V2::TEXTAREA_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_AREA },
        { OHOS::Ace::V2::BUTTON_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_BUTTON },
        { OHOS::Ace::V2::PROGRESS_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_PROGRESS },
        { OHOS::Ace::V2::CHECK_BOX_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CHECKBOX },
        { OHOS::Ace::V2::XCOMPONENT_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_XCOMPONENT },
        { OHOS::Ace::V2::DATE_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_DATE_PICKER },
        { OHOS::Ace::V2::TIME_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TIME_PICKER },
        { OHOS::Ace::V2::TEXT_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_TEXT_PICKER },
        { OHOS::Ace::V2::CALENDAR_PICKER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CALENDAR_PICKER },
        { OHOS::Ace::V2::SLIDER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SLIDER },
        { OHOS::Ace::V2::RADIO_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_RADIO },
        { OHOS::Ace::V2::IMAGE_ANIMATOR_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_IMAGE_ANIMATOR },
        { OHOS::Ace::V2::STACK_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_STACK },
        { OHOS::Ace::V2::SWIPER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SWIPER },
        { OHOS::Ace::V2::SCROLL_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_SCROLL },
        { OHOS::Ace::V2::LIST_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST },
        { OHOS::Ace::V2::LIST_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST_ITEM },
        { OHOS::Ace::V2::LIST_ITEM_GROUP_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_LIST_ITEM_GROUP },
        { OHOS::Ace::V2::COLUMN_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_COLUMN },
        { OHOS::Ace::V2::ROW_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_ROW },
        { OHOS::Ace::V2::FLEX_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_FLEX },
        { OHOS::Ace::V2::REFRESH_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_REFRESH },
        { OHOS::Ace::V2::WATERFLOW_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_WATER_FLOW },
        { OHOS::Ace::V2::FLOW_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_FLOW_ITEM },
        { OHOS::Ace::V2::RELATIVE_CONTAINER_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_RELATIVE_CONTAINER },
        { OHOS::Ace::V2::GRID_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_GRID },
        { OHOS::Ace::V2::GRID_ITEM_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_GRID_ITEM },
        { OHOS::Ace::V2::CUSTOM_SPAN_NODE_ETS_TAG, ArkUI_NodeType::ARKUI_NODE_CUSTOM_SPAN },
    };

    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto value = impl->getNodeModifiers()->getFrameNodeModifier()->getNodeType(node->uiNodeHandle);
    auto iter = nodeTypeMap.find(value);
    if (iter != nodeTypeMap.end()) {
        return iter->second;
    }
    return -1;
}

void OH_ArkUI_CustomProperty_Destroy(ArkUI_CustomProperty* handle)
{
    delete[] handle->value;
    handle->value = nullptr;
    delete handle;
    handle = nullptr;
}

const char* OH_ArkUI_CustomProperty_GetStringValue(ArkUI_CustomProperty* handle)
{
    CHECK_NULL_RETURN(handle, nullptr);
    return handle->value;
}

void OH_ArkUI_ActiveChildrenInfo_Destroy(ArkUI_ActiveChildrenInfo* handle)
{
    delete[] handle->nodeList;
    handle->nodeList = nullptr;
    delete handle;
    handle = nullptr;
}

ArkUI_NodeHandle OH_ArkUI_ActiveChildrenInfo_GetNodeByIndex(ArkUI_ActiveChildrenInfo* handle, int32_t index)
{
    CHECK_NULL_RETURN(handle, nullptr);
    if (index < handle->nodeCount && index >= 0) {
        return handle->nodeList[index];
    }
    return nullptr;
}

int32_t OH_ArkUI_ActiveChildrenInfo_GetCount(ArkUI_ActiveChildrenInfo* handle)
{
    CHECK_NULL_RETURN(handle, 0);
    return handle->nodeCount;
}

#ifdef __cplusplus
};
#endif
