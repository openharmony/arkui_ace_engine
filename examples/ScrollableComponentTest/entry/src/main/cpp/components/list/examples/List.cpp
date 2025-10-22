/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cstdint>

#include "components/list/List1.h"

namespace ArkUICApiDemo {

void ListItemSwipeActionOption::SetStart(ArkUI_ListItemSwipeActionItem* item)
{
    OH_ArkUI_ListItemSwipeActionOption_SetStart(_option, item);
}

void ListItemSwipeActionOption::SetEnd(ArkUI_ListItemSwipeActionItem* item)
{
    OH_ArkUI_ListItemSwipeActionOption_SetEnd(_option, item);
}

void ListItemSwipeActionOption::SetEdgeEffect(ArkUI_ListItemSwipeEdgeEffect edgeEffect)
{
    OH_ArkUI_ListItemSwipeActionOption_SetEdgeEffect(_option, edgeEffect);
}

int32_t ListItemSwipeActionOption::GetEdgeEffect()
{
    return OH_ArkUI_ListItemSwipeActionOption_GetEdgeEffect(_option);
}

void ListItemSwipeActionOption::SetOnOffsetChange(OnOffsetChangeCallback callback)
{
    OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChange(_option, callback);
}

void ListItemSwipeActionOption::SetOnOffsetChangWithUserData(
    OnOffsetChangeWithUserDataCallback callback, void* userData)
{
    OH_ArkUI_ListItemSwipeActionOption_SetOnOffsetChangeWithUserData(_option, userData, callback);
}

int32_t ListChildrenMainSizeOption::SetDefaultMainSize(float defaultMainSize)
{
    return OH_ArkUI_ListChildrenMainSizeOption_SetDefaultMainSize(_option, defaultMainSize);
}

float ListChildrenMainSizeOption::GetDefaultMainSize()
{
    return OH_ArkUI_ListChildrenMainSizeOption_GetDefaultMainSize(_option);
}

void ListChildrenMainSizeOption::Resize(int32_t totalSize)
{
    OH_ArkUI_ListChildrenMainSizeOption_Resize(_option, totalSize);
}

int32_t ListChildrenMainSizeOption::Delete(int32_t start, int32_t deleteCount)
{
    return SpliceInline(start, deleteCount, 0);
}

int32_t ListChildrenMainSizeOption::Update(int32_t start, int32_t updateCount, std::vector<float> childrenSize)
{
    if (updateCount != childrenSize.size()) {
        return -1;
    }
    int32_t ret = 0;
    for (int index = 0; index < childrenSize.size(); index++) {
        ret = UpdateSize(start + index, childrenSize[index]);
    }

    return ret;
}

int32_t ListChildrenMainSizeOption::Add(int32_t start, int32_t addCount, std::vector<float> childrenSize)
{
    if (addCount != childrenSize.size()) {
        return -1;
    }
    auto ret = SpliceInline(start, 0, addCount);
    for (int index = 0; index < childrenSize.size(); index++) {
        ret = UpdateSize(start + index, childrenSize[index]);
    }

    return ret;
}

int32_t ListChildrenMainSizeOption::SpliceInline(int32_t index, int32_t deleteCount, int32_t addCount)
{
    return OH_ArkUI_ListChildrenMainSizeOption_Splice(_option, index, deleteCount, addCount);
}

int32_t ListChildrenMainSizeOption::UpdateSize(int32_t index, float mainSize)
{
    return OH_ArkUI_ListChildrenMainSizeOption_UpdateSize(_option, index, mainSize);
}

float ListChildrenMainSizeOption::GetMainSize(int32_t index)
{
    return OH_ArkUI_ListChildrenMainSizeOption_GetMainSize(_option, index);
}

void ListItemComponent::SetListItemSwiperAction(ListItemSwipeActionOption* option)
{
    ArkUI_AttributeItem item = { nullptr, 0, nullptr, option->GetOption() };
    _nodeAPI->setAttribute(_component, NODE_LIST_ITEM_SWIPE_ACTION, &item);
}

void ListComponent::SetNestedScroll(int32_t forward, int32_t backward)
{
    ArkUI_NumberValue value[] = { { .i32 = forward }, { .i32 = backward } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_NESTED_SCROLL, &item);
}

void ListComponent::SetListDirection(int32_t direction)
{
    ArkUI_NumberValue value[] = { { .i32 = direction } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_DIRECTION, &item);
}

void ListComponent::SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams)
{
    auto value = new ArkUI_NumberValue[2 + static_cast<int32_t>(optionalParams.size())];
    value[0] = { .f32 = hOffset };
    value[1] = { .f32 = vOffset };
    for (int32_t i = 0; i < optionalParams.size(); i++) {
        value[2 + i] = { .i32 = optionalParams[i] };
    }
    ArkUI_AttributeItem item = { value, 2 + static_cast<int32_t>(optionalParams.size()) };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_OFFSET, &item);
}

void ListComponent::SetScrollEdge(int32_t type)
{
    ArkUI_NumberValue value[] = { { .i32 = type } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE, &item);
}

void ListComponent::SetScrollEdgeEffect(int32_t edgeEffect, bool alwaysEnabled)
{
    ArkUI_NumberValue value[] = { { .i32 = edgeEffect }, { .i32 = alwaysEnabled } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_EDGE_EFFECT, &item);
}

void ListComponent::SetScrollPage(int32_t next)
{
    ArkUI_NumberValue value[] = { { .i32 = next } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void ListComponent::SetScrollPage(int32_t next, int32_t animation)
{
    ArkUI_NumberValue value[] = { { .i32 = next }, { .i32 = animation } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_PAGE, &item);
}
void ListComponent::SetScrollBy(float hDistance, float vDistance)
{
    ArkUI_NumberValue value[] = { { .f32 = hDistance }, { .f32 = vDistance } };
    ArkUI_AttributeItem item = { value, 2 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BY, &item);
}

void ListComponent::SetListSticky(int32_t stickyStyle)
{
    ArkUI_NumberValue value[] = { { .i32 = stickyStyle } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_STICKY, &item);
}

void ListComponent::SetListSpace(float space)
{
    ArkUI_NumberValue value[] = { { .f32 = space } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_SPACE, &item);
}

void ListComponent::ResetListSpace()
{
    _nodeAPI->resetAttribute(_component, NODE_LIST_SPACE);
}

void ListComponent::SetListCachedCount(int32_t count)
{
    ArkUI_NumberValue value[] = { { .i32 = count } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_CACHED_COUNT, &item);
}

void ListComponent::SetListScrollToIndex(const std::vector<int32_t>& data)
{
    auto value = new ArkUI_NumberValue[static_cast<int32_t>(data.size())];
    for (int32_t i = 0; i < data.size(); i++) {
        value[i] = { .i32 = data[i] };
    }
    ArkUI_AttributeItem item = { value, static_cast<int32_t>(data.size()) };
    _nodeAPI->setAttribute(_component, NODE_LIST_SCROLL_TO_INDEX, &item);
}

void ListComponent::SetListAlignListItem(int32_t align)
{
    ArkUI_NumberValue value[] = { { .i32 = align } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_ALIGN_LIST_ITEM, &item);
}

void ListComponent::SetListChildrenMainSize(ListChildrenMainSizeOption* mainSize)
{
    ArkUI_AttributeItem item = { .object = mainSize->GetOption() };
    _nodeAPI->setAttribute(_component, NODE_LIST_CHILDREN_MAIN_SIZE, &item);
    _childrenMainSize.reset(mainSize);
}

void ListComponent::SetListInitialIndex(int32_t index)
{
    ArkUI_NumberValue value[] = { { .i32 = index } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_LIST_INITIAL_INDEX, &item);
}

void ListComponent::SetListDivider(uint32_t color, float width, float distanceStart, float distanceEnd)
{
    ArkUI_NumberValue value[] = { { .u32 = color }, { .f32 = width }, { .f32 = distanceStart },
        { .f32 = distanceEnd } };
    ArkUI_AttributeItem item = { value, 4 };
    _nodeAPI->setAttribute(_component, NODE_LIST_DIVIDER, &item);
}

void ListComponent::SetScrollBarWidth(float width)
{
    ArkUI_NumberValue value[] = { { .f32 = width } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_WIDTH, &item);
}

void ListComponent::SetScrollBarColor(uint32_t color)
{
    ArkUI_NumberValue value[] = { { .u32 = color } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_COLOR, &item);
}

void ListComponent::SetScrollBar(int32_t barState)
{
    ArkUI_NumberValue value[] = { { .i32 = barState } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
}

void ListItemGroupComponent::SetListItemGroupHeader(Component* node)
{
    ArkUI_AttributeItem item = { nullptr, 0, nullptr, node->GetComponent() };
    _nodeAPI->setAttribute(_component, NODE_LIST_ITEM_GROUP_SET_HEADER, &item);
}

void ListItemGroupComponent::SetListItemGroupFooter(Component* node)
{
    ArkUI_AttributeItem item = { nullptr, 0, nullptr, node->GetComponent() };
    _nodeAPI->setAttribute(_component, NODE_LIST_ITEM_GROUP_SET_FOOTER, &item);
}

void ListItemGroupComponent::SetListItemGroupDivider(
    uint32_t color, float width, float distanceStart, float distanceEnd)
{
    ArkUI_NumberValue value[] = { { .u32 = color }, { .f32 = width }, { .f32 = distanceStart },
        { .f32 = distanceEnd } };
    ArkUI_AttributeItem item = { value, 4 };
    _nodeAPI->setAttribute(_component, NODE_LIST_ITEM_GROUP_SET_DIVIDER, &item);
}

void ListItemGroupComponent::SetListItemGroupChildrenMainSize(ListChildrenMainSizeOption* mainSize)
{
    ArkUI_AttributeItem item = { .object = mainSize->GetOption() };
    _nodeAPI->setAttribute(_component, NODE_LIST_ITEM_GROUP_CHILDREN_MAIN_SIZE, &item);
    _childrenMainSize.reset(mainSize);
}

void ListItemGroupAdapter::OnNewItemAttached(ArkUI_NodeAdapterEvent* event)
{
    auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
    ArkUI_NodeHandle handle = nullptr;
    int32_t start = index > 0 ? _groupList[index - 1] : 0;
    int32_t end = _groupList[index];
    if (end - start != 1) {
        handle = UpdateNewItemByGroup(start, end);
    } else {
        handle = UpdateNewItem(start, end);
    }
    // 设置需要展示的元素。
    OH_ArkUI_NodeAdapterEvent_SetItem(event, handle);
}

void ListItemGroupAdapter::OnItemDetached(ArkUI_NodeAdapterEvent* event)
{
    auto item = OH_ArkUI_NodeAdapterEvent_GetRemovedNode(event);
    if (_removedNodeCallback) {
        _removedNodeCallback(std::make_shared<Component>(item));
    }
    // 放置到缓存池中进行回收复用。
    if (Component(item).GetChildren().size() == 1) {
        _cachedListItems.emplace(_listItems[item]);
    } else {
        _cachedItems.emplace(_items[item]);
    }
}

ArkUI_NodeHandle ListItemGroupAdapter::UpdateNewItemByGroup(int32_t start, int32_t end)
{
    ArkUI_NodeHandle handle = nullptr;
    if (!_cachedItems.empty()) {
        // 使用并更新回收复用的缓存。
        auto recycledItem = _cachedItems.top();
        recycledItem->RemoveAll();
        for (int32_t i = start; i < end; i++) {
            recycledItem->AddChild(_data[i]);
        }
        handle = recycledItem->GetComponent();
        // 释放缓存池的引用。
        _cachedItems.pop();
    } else {
        // 创建新的元素。
        auto groupItem = std::make_shared<ListItemGroupComponent>();
        groupItem->RemoveAll();
        for (int32_t i = start; i < end; i++) {
            groupItem->AddChild(_data[i]);
        }
        groupItem->SetBorderWidth(1);
        handle = groupItem->GetComponent();
        // 保持文本列表项的引用。
        _items.emplace(handle, groupItem);
    }
    return handle;
}

ArkUI_NodeHandle ListItemGroupAdapter::UpdateNewItem(int32_t start, int32_t end)
{
    ArkUI_NodeHandle handle = nullptr;
    if (!_cachedListItems.empty()) {
        // 使用并更新回收复用的缓存。
        auto recycledItem = _cachedListItems.top();
        recycledItem->RemoveAll();
        for (int32_t i = start; i < end; i++) {
            recycledItem->AddChild(_data[i]);
        }
        handle = recycledItem->GetComponent();
        // 释放缓存池的引用。
        _cachedListItems.pop();
    } else {
        // 创建新的元素。
        auto listItem = std::make_shared<ListItemComponent>();
        listItem->RemoveAll();
        for (int32_t i = start; i < end; i++) {
            listItem->AddChild(_data[i]);
        }
        handle = listItem->GetComponent();
        // 保持文本列表项的引用。
        _listItems.emplace(handle, listItem);
    }
    return handle;
}
} // namespace ArkUICApiDemo