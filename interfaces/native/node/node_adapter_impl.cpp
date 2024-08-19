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


#include "node/node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_NodeAdapterHandle OH_ArkUI_NodeAdapter_Create(void)
{
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, nullptr);
    auto* nodeAdapter = fullImpl->getNodeAdapterAPI()->create();
    return reinterpret_cast<ArkUI_NodeAdapterHandle>(nodeAdapter);
}

void OH_ArkUI_NodeAdapter_Dispose(ArkUI_NodeAdapterHandle handle)
{
    CHECK_NULL_VOID(handle);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(fullImpl);
    fullImpl->getNodeAdapterAPI()->dispose(reinterpret_cast<ArkUINodeAdapterHandle>(handle));
}

int32_t OH_ArkUI_NodeAdapter_SetTotalNodeCount(ArkUI_NodeAdapterHandle handle, uint32_t size)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->setTotalNodeCount(reinterpret_cast<ArkUINodeAdapterHandle>(handle), size);
}

uint32_t OH_ArkUI_NodeAdapter_GetTotalNodeCount(ArkUI_NodeAdapterHandle handle)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->getTotalNodeCount(reinterpret_cast<ArkUINodeAdapterHandle>(handle));
}

typedef void (*InnerArkUINodeAdapterEvent)(ArkUINodeAdapterEvent* event);
int32_t OH_ArkUI_NodeAdapter_RegisterEventReceiver(
    ArkUI_NodeAdapterHandle handle, void* userData, void (*receiver)(ArkUI_NodeAdapterEvent* event))
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->registerEventReceiver(reinterpret_cast<ArkUINodeAdapterHandle>(handle),
        userData, reinterpret_cast<InnerArkUINodeAdapterEvent>(receiver));
}

void OH_ArkUI_NodeAdapter_UnregisterEventReceiver(ArkUI_NodeAdapterHandle handle)
{
    CHECK_NULL_VOID(handle);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_VOID(fullImpl);
    fullImpl->getNodeAdapterAPI()->unregisterEventReceiver(reinterpret_cast<ArkUINodeAdapterHandle>(handle));
}

int32_t OH_ArkUI_NodeAdapter_ReloadAllItems(ArkUI_NodeAdapterHandle handle)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->notifyItemReloaded(reinterpret_cast<ArkUINodeAdapterHandle>(handle));
}

int32_t OH_ArkUI_NodeAdapter_ReloadItem(
    ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->notifyItemChanged(
        reinterpret_cast<ArkUINodeAdapterHandle>(handle), startPosition, itemCount);
}

int32_t OH_ArkUI_NodeAdapter_RemoveItem(
    ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->notifyItemRemoved(
        reinterpret_cast<ArkUINodeAdapterHandle>(handle), startPosition, itemCount);
}

int32_t OH_ArkUI_NodeAdapter_InsertItem(
    ArkUI_NodeAdapterHandle handle, uint32_t startPosition, uint32_t itemCount)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->notifyItemInserted(
        reinterpret_cast<ArkUINodeAdapterHandle>(handle), startPosition, itemCount);
}

int32_t OH_ArkUI_NodeAdapter_MoveItem(ArkUI_NodeAdapterHandle handle, uint32_t from, uint32_t to)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    return fullImpl->getNodeAdapterAPI()->notifyItemMoved(reinterpret_cast<ArkUINodeAdapterHandle>(handle), from, to);
}

int32_t OH_ArkUI_NodeAdapter_GetAllItems(ArkUI_NodeAdapterHandle handle, ArkUI_NodeHandle** items, uint32_t* size)
{
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);
    ArkUINodeHandle* innerNodes = nullptr;
    uint32_t totalSize = 0;
    auto error = fullImpl->getNodeAdapterAPI()->getAllItem(
        reinterpret_cast<ArkUINodeAdapterHandle>(handle), &innerNodes, &totalSize);
    if (error != 0) {
        return error;
    }
    *size = totalSize;
    if (*size == 0) {
        return OHOS::Ace::ERROR_CODE_NO_ERROR;
    }
    *items = new ArkUI_NodeHandle[*size] {};
    for (uint32_t i = 0; i < *size; i++) {
        (*items[i]) = reinterpret_cast<ArkUI_NodeHandle>(fullImpl->getExtendedAPI()->getAttachNodePtr(innerNodes[i]));
    }
    delete[] innerNodes;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

void* OH_ArkUI_NodeAdapterEvent_GetUserData(ArkUI_NodeAdapterEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    return reinterpret_cast<void*>(innerEvent->extraParam);
}

ArkUI_NodeAdapterEventType OH_ArkUI_NodeAdapterEvent_GetType(ArkUI_NodeAdapterEvent* event)
{
    CHECK_NULL_RETURN(event, ArkUI_NodeAdapterEventType(-1));
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    return static_cast<ArkUI_NodeAdapterEventType>(innerEvent->type);
}

ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetRemovedNode(ArkUI_NodeAdapterEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, nullptr);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    return reinterpret_cast<ArkUI_NodeHandle>(fullImpl->getExtendedAPI()->getAttachNodePtr(innerEvent->handle));
}

ArkUI_NodeHandle OH_ArkUI_NodeAdapterEvent_GetHostNode(ArkUI_NodeAdapterEvent* event)
{
    CHECK_NULL_RETURN(event, nullptr);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, nullptr);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    return reinterpret_cast<ArkUI_NodeHandle>(fullImpl->getExtendedAPI()->getAttachNodePtr(innerEvent->handle));
}

uint32_t OH_ArkUI_NodeAdapterEvent_GetItemIndex(ArkUI_NodeAdapterEvent* event)
{
    CHECK_NULL_RETURN(event, 0);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    return innerEvent->index;
}

int32_t OH_ArkUI_NodeAdapterEvent_SetItem(ArkUI_NodeAdapterEvent* event, ArkUI_NodeHandle handle)
{
    CHECK_NULL_RETURN(event, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(handle, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    innerEvent->handle = handle->uiNodeHandle;
    innerEvent->nodeSet = true;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

int32_t OH_ArkUI_NodeAdapterEvent_SetNodeId(ArkUI_NodeAdapterEvent* event, int32_t id)
{
    CHECK_NULL_RETURN(event, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    auto* innerEvent = reinterpret_cast<ArkUINodeAdapterEvent*>(event);
    innerEvent->id = id;
    innerEvent->idSet = true;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ContextHandle OH_ArkUI_GetContextByNode(ArkUI_NodeHandle node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, nullptr);
    auto basicAPI = fullImpl->getBasicAPI();
    CHECK_NULL_RETURN(basicAPI, nullptr);
    int32_t instanceId = basicAPI->getContextByNode(node->uiNodeHandle);
    if (instanceId < 0) {
        return nullptr;
    }
    return new ArkUI_Context({ .id = instanceId });
}

#ifdef __cplusplus
};
#endif
