/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/node_list_item_modifier.h"

#include "interfaces/native/node/list_option.h"

#include "core/components_ng/pattern/list/list_item_model_ng.h"

namespace OHOS::Ace::NG {

void SetOptionBuilder(FrameNode* frameNode, ArkUIListItemSwipeActionItemHandle item, bool isStart)
{
    if (item) {
        CalcDimension length { item->actionAreaDistance, DimensionUnit::VP };
        auto onAction = [item]() {
            if (item->onAction) {
                using FuncType = void (*)(void*);
                FuncType func = reinterpret_cast<FuncType>(item->onAction);
                func(item->onActionUserData);
            }
        };
        auto onEnterActionArea = [item]() {
            if (item->onEnterActionArea) {
                using FuncType = void (*)(void*);
                FuncType func = reinterpret_cast<FuncType>(item->onEnterActionArea);
                func(item->onEnterActionAreaUserData);
            }
        };
        auto onExitActionArea = [item]() {
            if (item->onExitActionArea) {
                using FuncType = void (*)(void*);
                FuncType func = reinterpret_cast<FuncType>(item->onExitActionArea);
                func(item->onExitActionAreaUserData);
            }
        };
        auto onStateChange = [item](OHOS::Ace::SwipeActionState swipeActionState) {
            if (item->onStateChange) {
                using FuncType = float (*)(int32_t, void*);
                FuncType func = reinterpret_cast<FuncType>(item->onStateChange);
                func(static_cast<int32_t>(swipeActionState), item->onStateChangeUserData);
            }
        };
        ListItemModelNG::SetDeleteArea(frameNode, reinterpret_cast<FrameNode*>(item->node), onAction,
            onEnterActionArea, onExitActionArea, onStateChange, length, isStart);
    } else {
        CalcDimension length;
        ListItemModelNG::SetDeleteArea(frameNode, nullptr, nullptr, nullptr, nullptr, nullptr, length, isStart);
    }
}

void SetListItemSwiperAction(ArkUINodeHandle node, ArkUIListItemSwipeActionOptionHandle option)
{
    CHECK_NULL_VOID(option);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SetOptionBuilder(frameNode, option->start, true);
    SetOptionBuilder(frameNode, option->end, false);

    auto onOffsetChange = [option](int32_t offset) {
        if (option->onOffsetChange) {
            using FuncType = float (*)(float, void*);
            FuncType func = reinterpret_cast<FuncType>(option->onOffsetChange);
            func(static_cast<float>(offset), option->userData);
        }
    };
    auto edgeEffect = static_cast<V2::SwipeEdgeEffect>(option->edgeEffect);
    ListItemModelNG::SetSwiperAction(frameNode, nullptr, nullptr, onOffsetChange, edgeEffect);
}

void ResetListItemSwiperAction(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension length;
    ListItemModelNG::SetDeleteArea(frameNode, nullptr, nullptr, nullptr, nullptr, nullptr, length, true);
    ListItemModelNG::SetDeleteArea(frameNode, nullptr, nullptr, nullptr, nullptr, nullptr, length, false);
    ListItemModelNG::SetSwiperAction(frameNode, nullptr, nullptr, nullptr, V2::SwipeEdgeEffect::None);
}

void SetListItemSelected(ArkUINodeHandle node, ArkUI_Bool selected)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelected(frameNode, selected);
}

void ResetListItemSelected(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelected(frameNode, false);
}

void SetSelectable(ArkUINodeHandle node, ArkUI_Bool selectable)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelectable(frameNode, selectable);
}

void ResetSelectable(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelectable(frameNode, true);
}

void SetListItemOnSelectCallback(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSelectEvent = reinterpret_cast<std::function<void(bool)>*>(callback);
        ListItemModelNG::SetSelectCallback(frameNode, std::move(*onSelectEvent));
    } else {
        ListItemModelNG::SetSelectCallback(frameNode, nullptr);
    }
}

void ResetListItemOnSelectCallback(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelectCallback(frameNode, nullptr);
}

void SetListItemStyle(ArkUINodeHandle node, ArkUI_Uint32 style)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetStyle(frameNode, static_cast<V2::ListItemStyle>(style));
}

void ResetListItemStyle(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetStyle(frameNode, V2::ListItemStyle::NONE);
}

namespace NodeModifier {
const ArkUIListItemModifier* GetListItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIListItemModifier modifier = {
        .setListItemSelected = SetListItemSelected,
        .resetListItemSelected = ResetListItemSelected,
        .setSelectable = SetSelectable,
        .resetSelectable = ResetSelectable,
        .setListItemSwipeAction = SetListItemSwiperAction,
        .resetListItemSwipeAction = ResetListItemSwiperAction,
        .setListItemOnSelectCallback = SetListItemOnSelectCallback,
        .resetListItemOnSelectCallback = ResetListItemOnSelectCallback,
        .setListItemStyle = SetListItemStyle,
        .resetListItemStyle = ResetListItemStyle,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIListItemModifier* GetCJUIListItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIListItemModifier modifier = {
        .setListItemSelected = SetListItemSelected,
        .resetListItemSelected = ResetListItemSelected,
        .setSelectable = SetSelectable,
        .resetSelectable = ResetSelectable,
        .setListItemSwipeAction = SetListItemSwiperAction,
        .resetListItemSwipeAction = ResetListItemSwiperAction,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

void SetListItemOnSelect(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam](bool isSelected) {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_LIST_ITEM_SELECTED;
        event.componentAsyncEvent.data[0].i32 = static_cast<int32_t>(isSelected);
        SendArkUISyncEvent(&event);
    };
    ListItemModelNG::SetSelectCallback(frameNode, std::move(onEvent));
}

void ResetListItemOnSelect(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ListItemModelNG::SetSelectCallback(frameNode, nullptr);
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
