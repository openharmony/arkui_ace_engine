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

#include "list_option.h"


#include "node_model.h"

#include "base/error/error_code.h"
#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_ListItemSwipeActionItem* OH_ArkUI_ListItemSwipeActionItem_Create()
{
    ArkUI_ListItemSwipeActionItem* item =
        new ArkUI_ListItemSwipeActionItem { nullptr, 0.0f, nullptr, nullptr, nullptr, nullptr };
    return item;
}

void OH_ArkUI_ListItemSwipeActionItem_Dispose(ArkUI_ListItemSwipeActionItem* item)
{
    delete item;
}

void OH_ArkUI_ListItemSwipeActionItem_SetContent(ArkUI_ListItemSwipeActionItem* item, ArkUI_NodeHandle node)
{
    CHECK_NULL_VOID(item);
    item->node = node->uiNodeHandle;
}

void OH_ArkUI_ListItemSwipeActionItem_SetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item, float distance)
{
    CHECK_NULL_VOID(item);
    item->actionAreaDistance = distance;
}

float OH_ArkUI_ListItemSwipeActionItem_GetActionAreaDistance(ArkUI_ListItemSwipeActionItem* item)
{
    CHECK_NULL_RETURN(item, 0.0f);
    return item->actionAreaDistance;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)())
{
    CHECK_NULL_VOID(item);
    item->onEnterActionArea = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnEnterActionAreaWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_VOID(item);
    item->onEnterActionArea = reinterpret_cast<void*>(callback);
    item->onEnterActionAreaUserData = userData;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)())
{
    CHECK_NULL_VOID(item);
    item->onAction = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnActionWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_VOID(item);
    item->onAction = reinterpret_cast<void*>(callback);
    item->onActionUserData = userData;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)())
{
    CHECK_NULL_VOID(item);
    item->onExitActionArea = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionAreaWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_VOID(item);
    item->onExitActionArea = reinterpret_cast<void*>(callback);
    item->onExitActionAreaUserData = userData;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(
    ArkUI_ListItemSwipeActionItem* item, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState))
{
    CHECK_NULL_VOID(item);
    item->onStateChange = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChangeWithUserData(ArkUI_ListItemSwipeActionItem* item,
    void* userData, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState, void* userData))
{
    CHECK_NULL_VOID(item);
    item->onStateChange = reinterpret_cast<void*>(callback);
    item->onStateChangeUserData = userData;
}

ArkUI_ListItemSwipeActionOption* OH_ArkUI_ListItemSwipeActionOption_Create()
{
    ArkUI_ListItemSwipeActionOption* option = new ArkUI_ListItemSwipeActionOption { nullptr, nullptr, 0, nullptr };
    return option;
}

void OH_ArkUI_ListItemSwipeActionOption_Dispose(ArkUI_ListItemSwipeActionOption* option)
{
    delete option;
}

void OH_ArkUI_ListItemSwipeActionOption_SetStart(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item)
{
    CHECK_NULL_VOID(option);
    option->start = item;
}

void OH_ArkUI_ListItemSwipeActionOption_SetEnd(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeActionItem* item)
{
    CHECK_NULL_VOID(option);
    option->end = item;
}

void OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(
    ArkUI_ListItemSwipeActionOption* option, ArkUI_ListItemSwipeEdgeEffect edgeEffect)
{
    CHECK_NULL_VOID(option);
    option->edgeEffect = edgeEffect;
}

int32_t OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(ArkUI_ListItemSwipeActionOption* option)
{
    CHECK_NULL_RETURN(option, 0);
    return option->edgeEffect;
}

void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(
    ArkUI_ListItemSwipeActionOption* option, void (*callback)(float offset))
{
    CHECK_NULL_VOID(option);
    option->onOffsetChange = reinterpret_cast<void*>(callback);
}

void OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(ArkUI_ListItemSwipeActionOption* option,
    void* userData, void (*callback)(float offset, void* userData))
{
    CHECK_NULL_VOID(option);
    option->onOffsetChange = reinterpret_cast<void*>(callback);
    option->userData = userData;
}

int32_t OH_ArkUI_List_CloseAllSwipeActions(ArkUI_NodeHandle node, void* userData, void (*onFinish)(void* userData))
{
    CHECK_NULL_RETURN(node, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (node->type != ARKUI_NODE_LIST) {
        return OHOS::Ace::ERROR_CODE_NATIVE_IMPL_TYPE_NOT_SUPPORTED;
    }
    auto* fullImpl = OHOS::Ace::NodeModel::GetFullImpl();
    CHECK_NULL_RETURN(fullImpl, OHOS::Ace::ERROR_CODE_NATIVE_IMPL_LIBRARY_NOT_FOUND);

    fullImpl->getNodeModifiers()->getListModifier()->setListCloseAllSwipeActions(
        node->uiNodeHandle, userData, onFinish);
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

ArkUI_ListChildrenMainSize* OH_ArkUI_ListChildrenMainSizeOption_Create()
{
    ArkUI_ListChildrenMainSize* option = new ArkUI_ListChildrenMainSize { 0, { -1.0f } };
    return option;
}

void OH_ArkUI_ListChildrenMainSizeOption_Dispose(ArkUI_ListChildrenMainSize* option)
{
    delete option;
}

int32_t OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(
    ArkUI_ListChildrenMainSize* option, float defaultMainSize)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID;);
    if (defaultMainSize < 0) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->defaultMainSize = defaultMainSize;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

float OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(ArkUI_ListChildrenMainSize* option)
{
    CHECK_NULL_RETURN(option, -1);
    return option->defaultMainSize;
}

void OH_ArkUI_ListChildrenMainSizeOption_Resize(ArkUI_ListChildrenMainSize* option, int32_t totalSize)
{
    CHECK_NULL_VOID(option);
    if (totalSize <= 0) {
        return;
    }
    option->mainSize.resize(std::max(totalSize, 0), -1.0f);
}

int32_t OH_ArkUI_ListChildrenMainSizeOption_Splice(
    ArkUI_ListChildrenMainSize* option, int32_t index, int32_t deleteCount, int32_t addCount)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (index < 0 || deleteCount < 0 || addCount < 0 || static_cast<int32_t>(option->mainSize.size()) - 1 < index) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    while (deleteCount > 0) {
        if (static_cast<size_t>(index) < option->mainSize.size()) {
            option->mainSize.erase(option->mainSize.begin() + index);
        }
        deleteCount--;
    }
    while (addCount > 0) {
        option->mainSize.insert(option->mainSize.begin() + index, -1.0f);
        addCount--;
    }
    return 0;
}

int32_t OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(
    ArkUI_ListChildrenMainSize* option, int32_t index, float mainSize)
{
    CHECK_NULL_RETURN(option, OHOS::Ace::ERROR_CODE_PARAM_INVALID);
    if (index < 0 || mainSize < 0 || static_cast<int32_t>(option->mainSize.size()) - 1 < index) {
        return OHOS::Ace::ERROR_CODE_PARAM_INVALID;
    }
    option->mainSize[index] = mainSize;
    return OHOS::Ace::ERROR_CODE_NO_ERROR;
}

float OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(ArkUI_ListChildrenMainSize* option, int32_t index)
{
    CHECK_NULL_RETURN(option, -1);
    if (index < 0 || static_cast<int32_t>(option->mainSize.size()) - 1 < index) {
        return -1;
    }
    return option->mainSize[index];
}

#ifdef __cplusplus
};
#endif
