/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef MYAPPLICATION_ARKUINODEADAPTER_H
#define MYAPPLICATION_ARKUINODEADAPTER_H
#include <arkui/native_interface.h>
#include <functional>
#include <list>
#include <stack>
#include <string>
#include <vector>

#include "ArkUIGridNode.h"


template<typename SubComponent>
class ItemAdapter {
public:
    explicit ItemAdapter(std::vector<std::shared_ptr<BaseNode>>& dataSource);
    virtual ~ItemAdapter();
    ArkUI_NodeAdapterHandle GetAdapter() const
    {
        return adapter_;
    }
    void InsertItem(int32_t index, const std::shared_ptr<BaseNode>& value);
    void MoveItem(int32_t oldIndex, int32_t newIndex);

private:
    static void OnStaticAdapterEvent(ArkUI_NodeAdapterEvent* event);
    void OnAdapterEvent(ArkUI_NodeAdapterEvent* event);
    void OnNewItemIdCreated(ArkUI_NodeAdapterEvent* event);
    void OnNewItemAttached(ArkUI_NodeAdapterEvent* event);
    void OnItemDetached(ArkUI_NodeAdapterEvent* event);

    std::vector<std::shared_ptr<BaseNode>> data_;
    ArkUI_NativeNodeAPI_1* nodeAPI_ = nullptr;
    ArkUI_NodeAdapterHandle adapter_ = nullptr;
    std::unordered_map<ArkUI_NodeHandle, std::shared_ptr<SubComponent>> items_;
    std::stack<std::shared_ptr<SubComponent>> cachedItems_;
    std::function<void(ArkUI_NodeAdapterEvent*)> eventCallBack_;
    std::function<void(std::shared_ptr<BaseNode>)> removedNodeCallback_;
};

template<typename SubComponent>
ItemAdapter<SubComponent>::ItemAdapter(std::vector<std::shared_ptr<BaseNode>>& dataSource)
    : adapter_(OH_ArkUI_NodeAdapter_Create())
{
    OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeAPI_);
    std::swap(data_, dataSource);
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(adapter_, data_.size());
    OH_ArkUI_NodeAdapter_RegisterEventReceiver(adapter_, this, OnStaticAdapterEvent);
}

template<typename SubComponent>
ItemAdapter<SubComponent>::~ItemAdapter()
{
    while (!cachedItems_.empty()) {
        cachedItems_.pop();
    }
    items_.clear();
    OH_ArkUI_NodeAdapter_UnregisterEventReceiver(adapter_);
    OH_ArkUI_NodeAdapter_Dispose(adapter_);
}

// 插入项目方法实现
template<typename SubComponent>
void ItemAdapter<SubComponent>::InsertItem(int32_t index, const std::shared_ptr<BaseNode>& value)
{
    data_.insert(data_.begin() + index, value);
    OH_ArkUI_NodeAdapter_InsertItem(adapter_, index, 1);
    OH_ArkUI_NodeAdapter_SetTotalNodeCount(adapter_, data_.size());
}

// 静态事件回调实现
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnStaticAdapterEvent(ArkUI_NodeAdapterEvent* event)
{
    auto itemAdapter = reinterpret_cast<ItemAdapter*>(OH_ArkUI_NodeAdapterEvent_GetUserData(event));
    itemAdapter->OnAdapterEvent(event);
}

// 实例事件处理函数
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnAdapterEvent(ArkUI_NodeAdapterEvent* event)
{
    auto type = OH_ArkUI_NodeAdapterEvent_GetType(event);
    switch (type) {
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
    if (eventCallBack_)
        eventCallBack_(event);
}

// 新项目ID创建事件处理
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnNewItemIdCreated(ArkUI_NodeAdapterEvent* event)
{
    auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
    static std::hash<std::string> hashId = std::hash<std::string>();
    auto id = hashId(std::to_string(index));
    OH_ArkUI_NodeAdapterEvent_SetNodeId(event, id);
}

// 新项目附加事件处理
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnNewItemAttached(ArkUI_NodeAdapterEvent* event)
{
    auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
    ArkUI_NodeHandle handle = nullptr;
    auto showNode = data_[index];
    if (!cachedItems_.empty()) {
        auto recycledItem = cachedItems_.top();
        recycledItem->RemoveAll();
        recycledItem->AddChild(showNode);
        handle = recycledItem->GetHandle();
        cachedItems_.pop();
    } else {
        auto flowItem = std::make_shared<SubComponent>();
        flowItem->RemoveAll();
        flowItem->AddChild(showNode);
        handle = flowItem->GetHandle();
        items_.emplace(handle, flowItem);
    }
    OH_ArkUI_NodeAdapterEvent_SetItem(event, handle);
}

// 项目分离事件处理
template<typename SubComponent>
void ItemAdapter<SubComponent>::OnItemDetached(ArkUI_NodeAdapterEvent* event)
{
    auto item = OH_ArkUI_NodeAdapterEvent_GetRemovedNode(event);
    if (removedNodeCallback_) {
        removedNodeCallback_(std::make_shared<BaseNode>(item));
    }
    cachedItems_.emplace(items_[item]);
}

// 移动项目方法实现
template<typename SubComponent>
void ItemAdapter<SubComponent>::MoveItem(int32_t oldIndex, int32_t newIndex)
{
    auto temp = data_[oldIndex];
    data_.insert(data_.begin() + newIndex, temp);
    data_.erase(data_.begin() + oldIndex);
    // 移到位置如果未发生可视区域内元素的可见性变化，则不回调事件，反之根据新增和删除场景回调对应的事件。
    OH_ArkUI_NodeAdapter_MoveItem(adapter_, oldIndex, newIndex);
}

#endif // MYAPPLICATION_ARKUINODEADAPTER_H
