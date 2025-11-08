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

#ifndef ARKUI_CAPI_DEMO_NODE_ADAPTER_H
#define ARKUI_CAPI_DEMO_NODE_ADAPTER_H

#include <arkui/native_interface.h>
#include <functional>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "components/column/Column.h"
namespace ArkUICApiDemo {
using AllItemCallBack = std::function<void(std::shared_ptr<Component>, uint32_t)>;

template<typename SubComponent>
class ItemAdapter {
public:
    explicit ItemAdapter(std::vector<std::shared_ptr<Component>>& dataSource);
    virtual ~ItemAdapter();
    ArkUI_NodeAdapterHandle GetAdapter() const
    {
        return _adapter;
    }
    void RemoveItem(int32_t index);
    void RemoveItems(int32_t startPosition, int32_t itemCount);
    void InsertItem(int32_t index, const std::shared_ptr<Component>& value);
    void InsertItems(int32_t index, std::vector<std::shared_ptr<Component>>& dataSource);
    void MoveItem(int32_t oldIndex, int32_t newIndex);
    void ReloadItem(int32_t index, const std::shared_ptr<Component>& value);
    void ReloadItems(int32_t startPosition, std::vector<std::shared_ptr<Component>>& dataSource);
    void ReloadAllItem();
    void SetAllItem(AllItemCallBack callback);
    void UnregisterEventReceiver();
    void SetNodeAdapterEvent(const std::function<void(ArkUI_NodeAdapterEvent*)>& callback);
    void RegisterRemovedNodeCallback(std::function<void(std::shared_ptr<Component>)> callback)
    {
        _removedNodeCallback = callback;
    }
    void SetTotalNodeCount(uint32_t count)
    {
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, count);
    }
    uint32_t GetTotalNodeCount()
    {
        return OH_ArkUI_NodeAdapter_GetTotalNodeCount(_adapter);
    }

protected:
    static void OnStaticAdapterEvent(ArkUI_NodeAdapterEvent* event);
    virtual void OnAdapterEvent(ArkUI_NodeAdapterEvent* event);
    // 分配ID给需要显示的Item，用于ReloadAllItems场景的元素diff。
    virtual void OnNewItemIdCreated(ArkUI_NodeAdapterEvent* event);
    // 需要新的Item显示在可见区域。
    virtual void OnNewItemAttached(ArkUI_NodeAdapterEvent* event);
    // Item从可见区域移除。
    virtual void OnItemDetached(ArkUI_NodeAdapterEvent* event);

    std::vector<std::shared_ptr<Component>> _data;
    ArkUI_NativeNodeAPI_1* _nodeAPI = nullptr;
    ArkUI_NodeAdapterHandle _adapter = nullptr;
    // 管理NodeAdapter生成的元素。
    std::unordered_map<ArkUI_NodeHandle, std::shared_ptr<SubComponent>> _items;
    // 管理回收复用组件池。
    std::stack<std::shared_ptr<SubComponent>> _cachedItems;
    std::function<void(ArkUI_NodeAdapterEvent*)> _eventCallBack;
    std::function<void(std::shared_ptr<Component>)> _removedNodeCallback;
};

template<typename SubComponent>
ItemAdapter<SubComponent>::ItemAdapter(std::vector<std::shared_ptr<Component>>& dataSource)
    : _adapter(OH_ArkUI_NodeAdapter_Create())
{
    // 使用NodeAdapter创建函数。
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, _nodeAPI);
    std::swap(_data, dataSource);
    // 设置懒加载数据。
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, _data.size());
    // 设置懒加载回调事件。
    OH_ArkUI_NodeAdapter_RegisterEventReceiver(_adapter, this, OnStaticAdapterEvent);
}

template<typename SubComponent>
ItemAdapter<SubComponent>::~ItemAdapter()
{
    // 释放创建的组件。
    while (!_cachedItems.empty()) {
        _cachedItems.pop();
    }
    _items.clear();
    // 释放Adapter相关资源。
    OH_ArkUI_NodeAdapter_UnregisterEventReceiver(_adapter);
    OH_ArkUI_NodeAdapter_Dispose(_adapter);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::RemoveItem(int32_t index)
{
    // 删除第index个数据。
    _data.erase(_data.begin() + index);
    // 如果index会导致可视区域元素发生可见性变化，则会回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER事件删除元素，
    // 根据是否有新增元素回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件。
    OH_ArkUI_NodeAdapter_RemoveItem(_adapter, index, 1);
    // 更新新的数量。
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, _data.size());
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::RemoveItems(int32_t startPosition, int32_t itemCount)
{
    auto end = _data.begin() + startPosition + itemCount;
    if (startPosition + itemCount > _data.size()) {
        end = _data.end();
    }
    _data.erase(_data.begin() + startPosition, end);
    OH_ArkUI_NodeAdapter_RemoveItem(_adapter, startPosition, itemCount);
    // 更新新的数量。
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, _data.size());
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::InsertItem(int32_t index, const std::shared_ptr<Component>& value)
{
    _data.insert(_data.begin() + index, value);
    // 如果index会导致可视区域元素发生可见性变化，则会回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件，
    // 根据是否有删除元素回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER事件。
    OH_ArkUI_NodeAdapter_InsertItem(_adapter, index, 1);
    // 更新新的数量。
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, _data.size());
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::InsertItems(int32_t index, std::vector<std::shared_ptr<Component>>& dataSource)
{
    _data.insert(_data.begin() + index, dataSource.begin(), dataSource.end());
    OH_ArkUI_NodeAdapter_InsertItem(_adapter, index, dataSource.size());
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(_adapter, _data.size());
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::MoveItem(int32_t oldIndex, int32_t newIndex)
{
    auto temp = _data[oldIndex];
    _data.insert(_data.begin() + newIndex, temp);
    _data.erase(_data.begin() + oldIndex);
    // 移到位置如果未发生可视区域内元素的可见性变化，则不回调事件，反之根据新增和删除场景回调对应的事件。
    OH_ArkUI_NodeAdapter_MoveItem(_adapter, oldIndex, newIndex);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::ReloadItem(int32_t index, const std::shared_ptr<Component>& value)
{
    _data[index] = value;
    // 如果index位于可视区域内，先回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER删除老元素，
    // 再回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件。
    OH_ArkUI_NodeAdapter_ReloadItem(_adapter, index, 1);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::ReloadItems(int32_t startPosition, std::vector<std::shared_ptr<Component>>& dataSource)
{
    if (startPosition + dataSource.size() > _data.size()) {
        // 防止nodeAdapter崩溃
        return;
    }
    for (int32_t i = 0; i < dataSource.size(); i++) {
        _data[startPosition + i] = dataSource[i];
    }
    // 如果index位于可视区域内，先回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER删除老元素，
    // 再回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件。
    OH_ArkUI_NodeAdapter_ReloadItem(_adapter, startPosition, dataSource.size());
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::SetAllItem(AllItemCallBack callback)
{
    ArkUI_NodeHandle* items = nullptr;
    uint32_t size = 0;
    OH_ArkUI_NodeAdapter_GetAllItems(_adapter, &items, &size);
    for (uint32_t i = 0; i < size; i++) {
        if (!items[i]) {
            continue;
        }
        auto temp = std::make_shared<SubComponent>(items[i]);
        if (callback) {
            callback(temp, i);
        }
    }
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::UnregisterEventReceiver()
{
    OH_ArkUI_NodeAdapter_UnregisterEventReceiver(_adapter);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::SetNodeAdapterEvent(const std::function<void(ArkUI_NodeAdapterEvent*)>& callback)
{
    _eventCallBack = callback;
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::ReloadAllItem()
{
    std::reverse(_data.begin(), _data.end());
    // 全部重新加载场景下，会回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID接口获取新的组件ID，
    // 根据新的组件ID进行对比，ID不发生变化的进行复用，
    // 针对新增ID的元素，调用NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件创建新的组件，
    // 然后判断老数据中遗留的未使用ID，调用NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER删除老元素。
    OH_ArkUI_NodeAdapter_ReloadAllItems(_adapter);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::OnStaticAdapterEvent(ArkUI_NodeAdapterEvent* event)
{
    // 获取实例对象，回调实例事件。
    auto itemAdapter = reinterpret_cast<ItemAdapter*>(OH_ArkUI_NodeAdapterEvent_GetUserData(event));
    itemAdapter->OnAdapterEvent(event);
}

template<typename SubComponent>
void ItemAdapter<SubComponent>::OnAdapterEvent(ArkUI_NodeAdapterEvent* event)
{
    auto type = OH_ArkUI_NodeAdapterEvent_GetType(event);
    switch (type) {
        case NODE_ADAPTER_EVENT_WILL_ATTACH_TO_NODE:
            break;
        case NODE_ADAPTER_EVENT_WILL_DETACH_FROM_NODE:
            break;
        case NODE_ADAPTER_EVENT_ON_GET_NODE_ID:
            OnNewItemIdCreated(event);
            break;
        case NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER:
            OnNewItemAttached(event);
            break;
        case NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER:
            OnItemDetached(event);
            break;
        default:
            break;
    }
    if (_eventCallBack) {
        _eventCallBack(event);
    }
}
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnNewItemIdCreated(ArkUI_NodeAdapterEvent* event)
{
    auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
    static std::hash<std::string> hashId = std::hash<std::string>();
    auto id = hashId(std::to_string(index));
    OH_ArkUI_NodeAdapterEvent_SetNodeId(event, id);
}

// 需要新的Item显示在可见区域。
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnNewItemAttached(ArkUI_NodeAdapterEvent* event)
{
    auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
    ArkUI_NodeHandle handle = nullptr;
    auto showNode = _data[index];
    if (!_cachedItems.empty()) {
        // 使用并更新回收复用的缓存。
        auto recycledItem = _cachedItems.top();
        recycledItem->RemoveAll();
        recycledItem->AddChild(showNode);
        handle = recycledItem->GetComponent();
        // 释放缓存池的引用。
        _cachedItems.pop();
    } else {
        // 创建新的元素。
        auto flowItem = std::make_shared<SubComponent>();
        flowItem->RemoveAll();
        flowItem->AddChild(showNode);
        handle = flowItem->GetComponent();
        // 保持文本列表项的引用。
        _items.emplace(handle, flowItem);
    }
    // 设置需要展示的元素。
    OH_ArkUI_NodeAdapterEvent_SetItem(event, handle);
}

// Item从可见区域移除。
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnItemDetached(ArkUI_NodeAdapterEvent* event)
{
    auto item = OH_ArkUI_NodeAdapterEvent_GetRemovedNode(event);
    if (_removedNodeCallback) {
        _removedNodeCallback(std::make_shared<Component>(item));
    }
    // 放置到缓存池中进行回收复用。
    _cachedItems.emplace(_items[item]);
}
} // namespace ArkUICApiDemo
#endif // ARKUI_CAPI_DEMO_NODE_ADAPTER_H
