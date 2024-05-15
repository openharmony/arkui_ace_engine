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

#include <cstdint>

#include "native_type.h"
#include "node_model.h"

#include "base/utils/utils.h"
#include "core/interfaces/arkoala/arkoala_api.h"

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
    item->onEnterActionArea = callback;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnAction(ArkUI_ListItemSwipeActionItem* item, void (*callback)())
{
    CHECK_NULL_VOID(item);
    item->onAction = callback;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnExitActionArea(ArkUI_ListItemSwipeActionItem* item, void (*callback)())
{
    CHECK_NULL_VOID(item);
    item->onExitActionArea = callback;
}

void OH_ArkUI_ListItemSwipeActionItem_SetOnStateChange(
    ArkUI_ListItemSwipeActionItem* item, void (*callback)(ArkUI_ListItemSwipeActionState swipeActionState))
{
    CHECK_NULL_VOID(item);
    auto onStateChange = reinterpret_cast<void (*)(ArkUI_Int32)>(callback);
    item->onStateChange = onStateChange;
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
    auto onOffsetChange = reinterpret_cast<void (*)(ArkUI_Int32)>(callback);
    option->onOffsetChange = onOffsetChange;
}

#ifdef __cplusplus
};
#endif
