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
#include "core/common/container_consts.h"
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

int32_t OH_ArkUI_NodeUtils_GetLayoutPositionInGlobalDisplay(ArkUI_NodeHandle node, ArkUI_IntOffset* offset)
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(offset, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getGlobalPositionOnDisplay(
        node->uiNodeHandle, &tempOffset, false);
    offset->x = tempOffset[0];
    offset->y = tempOffset[1];

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

int32_t OH_ArkUI_RegisterDrawCallbackOnNodeHandle(
    ArkUI_NodeHandle node, void* userData, void (*onDrawCompleted)(void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    if (impl == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getFrameNodeModifier()->setDrawCompleteEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onDrawCompleted));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}


int32_t OH_ArkUI_UnregisterDrawCallbackOnNodeHandle(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetDrawCompleteEvent(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RegisterLayoutCallbackOnNodeHandle(
    ArkUI_NodeHandle node, void* userData, void (*onLayoutCompleted)(void* userData))
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->setLayoutEvent(
        node->uiNodeHandle, userData, reinterpret_cast<void*>(onLayoutCompleted));

    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_UnregisterLayoutCallbackOnNodeHandle(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->resetLayoutEvent(node->uiNodeHandle);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
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
    if (node == nullptr || !OHOS::Ace::NodeModel::CheckIsCNode(node)) {
        return;
    }
    if (name == nullptr || value == nullptr) {
        LOGF_ABORT("AddCustomProperty input params name or value is nullptr");
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
        LOGF_ABORT("RemoveCustomProperty input params name is nullptr");
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
    
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
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
        for (int32_t i = 0; i < totalSize; i++) {
            ((*handle)->nodeList[i]) = OHOS::Ace::NodeModel::GetArkUINode(innerNodes[i]);
        }
    }
    delete[] innerNodes;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetParentInPageTree(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getParent(node->uiNodeHandle);
    return OHOS::Ace::NodeModel::GetArkUINode(attachNode);
}

ArkUI_NodeHandle OH_ArkUI_NodeUtils_GetCurrentPageRootNode(ArkUI_NodeHandle node)
{
    if (node == nullptr) {
        return nullptr;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    auto* attachNode = impl->getNodeModifiers()->getFrameNodeModifier()->getCurrentPageRootNode(node->uiNodeHandle);
    return OHOS::Ace::NodeModel::GetArkUINode(attachNode);
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

    return OHOS::Ace::NodeModel::GetNodeTypeByTag(node);
}

int32_t OH_ArkUI_NodeUtils_GetWindowInfo(ArkUI_NodeHandle node, ArkUI_HostWindowInfo** info)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(info, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    char* name = nullptr;
    int32_t error = impl->getNodeModifiers()->getFrameNodeModifier()->getWindowInfoByNode(node->uiNodeHandle, &name);
    *info = new ArkUI_HostWindowInfo({ .name = name });
    return error;
}

const char* OH_ArkUI_HostWindowInfo_GetName(ArkUI_HostWindowInfo* info)
{
    if (!info) {
        LOGF_ABORT("HostWindowInfo is nullptr");
    }
    return info->name;
}

void OH_ArkUI_HostWindowInfo_Destroy(ArkUI_HostWindowInfo* info)
{
    delete[] info->name;
    info->name = nullptr;
    delete info;
    info = nullptr;
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
    if (!handle) {
        LOGF_ABORT("CustomProperty is nullptr");
    }
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
    if (!handle) {
        LOGF_ABORT("ActiveChildrenInfo is nullptr");
    }
    if (index < handle->nodeCount && index >= 0) {
        return handle->nodeList[index];
    }
    return nullptr;
}

int32_t OH_ArkUI_ActiveChildrenInfo_GetCount(ArkUI_ActiveChildrenInfo* handle)
{
    if (!handle) {
        LOGF_ABORT("ActiveChildrenInfo is nullptr");
    }
    return handle->nodeCount;
}

int32_t OH_ArkUI_NodeUtils_GetAttachedNodeHandleById(const char* id, ArkUI_NodeHandle* node)
{
    CHECK_NULL_RETURN(id, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto nodePtr = impl->getNodeModifiers()->getFrameNodeModifier()->getAttachedFrameNodeById(id);
    CHECK_NULL_RETURN(nodePtr, ARKUI_ERROR_CODE_PARAM_INVALID);
    *node = OHOS::Ace::NodeModel::GetArkUINode(nodePtr);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetNodeHandleByUniqueId(const uint32_t uniqueId, ArkUI_NodeHandle* node)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto nodePtr = impl->getNodeModifiers()->getFrameNodeModifier()->getFrameNodeByUniqueId(uniqueId);
    *node = OHOS::Ace::NodeModel::GetArkUINode(nodePtr);
    CHECK_NULL_RETURN(*node, ARKUI_ERROR_CODE_PARAM_INVALID);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetNodeUniqueId(ArkUI_NodeHandle node, int32_t* uniqueId)
{
    if (node == nullptr) {
        *uniqueId = -1;
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    auto id = impl->getNodeModifiers()->getFrameNodeModifier()->getIdByNodePtr(node->uiNodeHandle);
    *uniqueId = id;
    if (*uniqueId < 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_MoveTo(ArkUI_NodeHandle node, ArkUI_NodeHandle target_parent, int32_t index)
{
    if (node == nullptr || target_parent == nullptr
        || !OHOS::Ace::NodeModel::CheckIsCNode(node) || !OHOS::Ace::NodeModel::CheckIsCNode(target_parent)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    int32_t errorCode = impl->getNodeModifiers()->getFrameNodeModifier()->moveNodeTo(node->uiNodeHandle,
        target_parent->uiNodeHandle, index);
    return errorCode;
}

int32_t OH_ArkUI_NodeUtils_SetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option)
{
    if (node == nullptr || option == nullptr || node->cNode == false) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto errorCode = impl->getNodeModifiers()->getFrameNodeModifier()->setCrossLanguageOptions(
        node->uiNodeHandle, option->attributeSetting);
    return errorCode;
}

int32_t OH_ArkUI_NodeUtils_GetCrossLanguageOption(ArkUI_NodeHandle node, ArkUI_CrossLanguageOption* option)
{
    if (node == nullptr || option == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    bool isCross = impl->getNodeModifiers()->getFrameNodeModifier()->getCrossLanguageOptions(node->uiNodeHandle);
    option->attributeSetting = isCross;
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_CrossLanguageOption* OH_ArkUI_CrossLanguageOption_Create(void)
{
    ArkUI_CrossLanguageOption* option = new ArkUI_CrossLanguageOption {
        .attributeSetting = false
    };
    return option;
}

void OH_ArkUI_CrossLanguageOption_Destroy(ArkUI_CrossLanguageOption* option)
{
    if (option == nullptr) {
        return;
    }
    delete option;
}

void OH_ArkUI_CrossLanguageOption_SetAttributeSettingStatus(ArkUI_CrossLanguageOption* option, bool enable)
{
    if (option == nullptr) {
        return;
    }
    option->attributeSetting = enable;
}

bool OH_ArkUI_CrossLanguageOption_GetAttributeSettingStatus(ArkUI_CrossLanguageOption* option)
{
    if (option == nullptr) {
        return false;
    }
    return option->attributeSetting;
}

int32_t OH_ArkUI_NativeModule_InvalidateAttributes(ArkUI_NodeHandle node)
{
    if (node == nullptr || !OHOS::Ace::NodeModel::CheckIsCNode(node)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    impl->getNodeModifiers()->getFrameNodeModifier()->applyAttributesFinish(node->uiNodeHandle);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetFirstChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index)
{
    if (node == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t errorCode = impl->getNodeModifiers()->getFrameNodeModifier()->getFirstChildIndexWithoutExpand(
        node->uiNodeHandle, index);
    return errorCode;
}

int32_t OH_ArkUI_NodeUtils_GetLastChildIndexWithoutExpand(ArkUI_NodeHandle node, uint32_t* index)
{
    if (node == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    int32_t errorCode = impl->getNodeModifiers()->getFrameNodeModifier()->getLastChildIndexWithoutExpand(
        node->uiNodeHandle, index);
    return errorCode;
}

int32_t OH_ArkUI_NodeUtils_GetChildWithExpandMode(ArkUI_NodeHandle node, int32_t position,
    ArkUI_NodeHandle* subnode, uint32_t expandMode)
{
    if (node == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_PARAM_INVALID);
    auto nodePtr = impl->getNodeModifiers()->getFrameNodeModifier()->getChild(
        node->uiNodeHandle, position, expandMode);
    CHECK_NULL_RETURN(nodePtr, ARKUI_ERROR_CODE_PARAM_INVALID);
    *subnode = OHOS::Ace::NodeModel::GetArkUINode(nodePtr);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeUtils_GetPositionToParent(ArkUI_NodeHandle node, ArkUI_IntOffset* globalOffset)
{
    if (node == nullptr) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    ArkUI_Float32 tempOffset[2];
    impl->getNodeModifiers()->getFrameNodeModifier()->getPositionToParent(node->uiNodeHandle, &tempOffset, false);
    globalOffset->x = tempOffset[0];
    globalOffset->y = tempOffset[1];
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_AddSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates,
    void (statesChangeHandler)(int32_t currentStates, void* userData), bool excludeInner, void* userData)
{
    if (node == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->addSupportedUIStates(node->uiNodeHandle, uiStates,
        reinterpret_cast<void*>(statesChangeHandler), excludeInner, userData);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

ArkUI_ErrorCode OH_ArkUI_RemoveSupportedUIStates(ArkUI_NodeHandle node, int32_t uiStates)
{
    if (node == nullptr) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    impl->getNodeModifiers()->getFrameNodeModifier()->removeSupportedUIStates(node->uiNodeHandle, uiStates);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_RunTaskInScope(ArkUI_ContextHandle uiContext, void* userData, void(*callback)(void* userData))
{
    CHECK_NULL_RETURN(uiContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    CHECK_NULL_RETURN(callback, ARKUI_ERROR_CODE_CALLBACK_INVALID);
    auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
    impl->getNodeModifiers()->getFrameNodeModifier()->runScopedTask(context->id, userData, callback);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_SetForceDarkConfig(
    ArkUI_ContextHandle uiContext, bool forceDark, ArkUI_NodeType nodeType, uint32_t (*colorInvertFunc)(uint32_t color))
{
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, OHOS::Ace::ERROR_CODE_CAPI_INIT_ERROR);
    int32_t instanceId = OHOS::Ace::INSTANCE_ID_UNDEFINED;
    if (uiContext) {
        auto* context = reinterpret_cast<ArkUI_Context*>(uiContext);
        instanceId = context->id;
    }
    int32_t errorCode = impl->getNodeModifiers()->getFrameNodeModifier()->setForceDarkConfig(
        instanceId, forceDark, OHOS::Ace::NodeModel::ConvertNodeTypeToTag(nodeType).c_str(), colorInvertFunc);
    return errorCode;
}

static std::set<uint32_t> NDKCommonEventList = {
    NODE_ON_CLICK_EVENT,
    NODE_TOUCH_EVENT,
    NODE_EVENT_ON_APPEAR,
    NODE_EVENT_ON_DISAPPEAR,
    NODE_ON_KEY_EVENT,
    NODE_ON_FOCUS,
    NODE_ON_BLUR,
    NODE_ON_HOVER,
    NODE_ON_MOUSE,
    NODE_ON_SIZE_CHANGE,
};

int32_t OH_ArkUI_NativeModule_RegisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType,
    void* userData, void (*callback)(ArkUI_NodeEvent* event))
{
    if (!node || !callback) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    // Check event type.
    if (NDKCommonEventList.find(eventType) == NDKCommonEventList.end()) {
        return ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE;
    }
    if (!OHOS::Ace::NodeModel::MakeCommonEventMap(node, eventType, userData, callback)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (eventType) {
        case NODE_ON_CLICK_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnClick(node->uiNodeHandle, node);
            break;
        case NODE_TOUCH_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnTouch(node->uiNodeHandle, node);
            break;
        case NODE_EVENT_ON_APPEAR:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnAppear(node->uiNodeHandle, node);
            break;
        case NODE_EVENT_ON_DISAPPEAR:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnDisappear(node->uiNodeHandle, node);
            break;
        case NODE_ON_KEY_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnKeyEvent(node->uiNodeHandle, node);
            break;
        case NODE_ON_FOCUS:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnFocus(node->uiNodeHandle, node);
            break;
        case NODE_ON_BLUR:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnBlur(node->uiNodeHandle, node);
            break;
        case NODE_ON_HOVER:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnHover(node->uiNodeHandle, node);
            break;
        case NODE_ON_MOUSE:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnMouse(node->uiNodeHandle, node);
            break;
        case NODE_ON_SIZE_CHANGE:
            impl->getNodeModifiers()->getCommonModifier()->setCommonOnSizeChange(node->uiNodeHandle, node);
            break;
        default:
            break;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NativeModule_UnregisterCommonEvent(ArkUI_NodeHandle node, ArkUI_NodeEventType eventType)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    // Check event type.
    if (NDKCommonEventList.find(eventType) == NDKCommonEventList.end()) {
        return ARKUI_ERROR_CODE_NODE_UNSUPPORTED_EVENT_TYPE;
    }
    if (!OHOS::Ace::NodeModel::ClearCommonEventMap(node, eventType)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    switch (eventType) {
        case NODE_ON_CLICK_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnClick(node->uiNodeHandle);
            break;
        case NODE_TOUCH_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnTouch(node->uiNodeHandle);
            break;
        case NODE_EVENT_ON_APPEAR:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnAppear(node->uiNodeHandle);
            break;
        case NODE_EVENT_ON_DISAPPEAR:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnDisappear(node->uiNodeHandle);
            break;
        case NODE_ON_KEY_EVENT:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnKeyEvent(node->uiNodeHandle);
            break;
        case NODE_ON_FOCUS:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnFocus(node->uiNodeHandle);
            break;
        case NODE_ON_BLUR:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnBlur(node->uiNodeHandle);
            break;
        case NODE_ON_HOVER:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnHover(node->uiNodeHandle);
            break;
        case NODE_ON_MOUSE:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnMouse(node->uiNodeHandle);
            break;
        case NODE_ON_SIZE_CHANGE:
            impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnSizeChange(node->uiNodeHandle);
            break;
        default:
            break;
    }
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NativeModule_RegisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node, float* ratios,
    int32_t size, float expectedUpdateInterval, void* userData, void (*callback)(ArkUI_NodeEvent* event))
{
    if (!node || !callback || !ratios || size <= 0) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    if (!OHOS::Ace::NodeModel::MakeCommonEventMap(node, NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT,
        userData, callback)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    ArkUI_Float32 radioList[size];
    for (int i = 0; i < size; ++i) {
        if (OHOS::Ace::LessNotEqual(ratios[i], 0.0f)
            || OHOS::Ace::GreatNotEqual(ratios[i], 1.0f)) {
            return ARKUI_ERROR_CODE_PARAM_INVALID;
        }
        radioList[i] = ratios[i];
    }
    impl->getNodeModifiers()->getCommonModifier()->setCommonOnVisibleAreaApproximateChangeEvent(
        node->uiNodeHandle, node, radioList, size, expectedUpdateInterval);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NativeModule_UnregisterCommonVisibleAreaApproximateChangeEvent(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, ARKUI_ERROR_CODE_PARAM_INVALID);
    const auto* impl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(impl, ARKUI_ERROR_CODE_CAPI_INIT_ERROR);
    if (!OHOS::Ace::NodeModel::ClearCommonEventMap(node, NODE_VISIBLE_AREA_APPROXIMATE_CHANGE_EVENT)) {
        return ARKUI_ERROR_CODE_PARAM_INVALID;
    }
    impl->getNodeModifiers()->getCommonModifier()->unregisterCommonOnVisibleAreaApproximateChangeEvent(
        node->uiNodeHandle);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

#ifdef __cplusplus
};
#endif
