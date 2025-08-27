/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

// 用于文本列表懒加载功能代码。

#ifndef SCROLLABLE_COMPONENT_ARKUILISTITEMADAPTER_H
#define SCROLLABLE_COMPONENT_ARKUILISTITEMADAPTER_H

#include <arkui/native_node.h>
#include <hilog/log.h>
#include <stack>
#include <string>

#include "ArkUIListItemNode.h"
#include "ArkUITextNode.h"

namespace NativeModule {

class ArkUIListItemAdapter {
public:
    explicit ArkUIListItemAdapter(int32_t dataCount)
        : module_(NativeModuleInstance::GetInstance()->GetNativeNodeAPI()),
          handle_(OH_ArkUI_NodeAdapter_Create()) // 使用NodeAdapter创建函数。
    {
        // 初始化懒加载数据。
        for (int32_t i = 0; i < dataCount; i++) {
            data_.emplace_back(std::to_string(i));
        }
        // 设置懒加载数据。
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(handle_, data_.size());
        // 设置懒加载回调事件。
        OH_ArkUI_NodeAdapter_RegisterEventReceiver(handle_, this, OnStaticAdapterEvent);
    }

    ~ArkUIListItemAdapter()
    {
        // 释放创建的组件。
        while (!cachedItems_.empty()) {
            cachedItems_.pop();
        }
        items_.clear();
        // 释放Adapter相关资源。
        OH_ArkUI_NodeAdapter_UnregisterEventReceiver(handle_);
        OH_ArkUI_NodeAdapter_Dispose(handle_);
    }

    ArkUI_NodeAdapterHandle GetHandle() const
    {
        return handle_;
    }

    void RemoveItem(int32_t index)
    {
        // 删除第index个数据。
        data_.erase(data_.begin() + index);
        // 如果index会导致可视区域元素发生可见性变化，则会回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER事件删除元素，
        // 根据是否有新增元素回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件。
        OH_ArkUI_NodeAdapter_RemoveItem(handle_, index, 1);
        // 更新新的数量。
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(handle_, data_.size());
    }

    void InsertItem(int32_t index, const std::string &value)
    {
        data_.insert(data_.begin() + index, value);
        // 如果index会导致可视区域元素发生可见性变化，则会回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件，
        // 根据是否有删除元素回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER事件。
        OH_ArkUI_NodeAdapter_InsertItem(handle_, index, 1);
        // 更新新的数量。
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(handle_, data_.size());
    }

    void MoveItem(int32_t oldIndex, int32_t newIndex)
    {
        auto temp = data_[oldIndex];
        data_.insert(data_.begin() + newIndex, temp);
        data_.erase(data_.begin() + oldIndex);
        // 移到位置如果未发生可视区域内元素的可见性变化，则不回调事件，反之根据新增和删除场景回调对应的事件。
        OH_ArkUI_NodeAdapter_MoveItem(handle_, oldIndex, newIndex);
    }

    void ReloadItem(int32_t index, const std::string &value)
    {
        data_[index] = value;
        // 如果index位于可视区域内，先回调NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER删除老元素，
        // 再回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID和NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件。
        OH_ArkUI_NodeAdapter_ReloadItem(handle_, index, 1);
    }

    void ReloadAllItem()
    {
        std::reverse(data_.begin(), data_.end());
        // 全部重新加载场景下，会回调NODE_ADAPTER_EVENT_ON_GET_NODE_ID接口获取新的组件ID，
        // 根据新的组件ID进行对比，ID不发生变化的进行复用，
        // 针对新增ID的元素，调用NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER事件创建新的组件，
        // 然后判断老数据中遗留的未使用ID，调用NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER删除老元素。
        OH_ArkUI_NodeAdapter_ReloadAllItems(handle_);
    }

private:
    static void OnStaticAdapterEvent(ArkUI_NodeAdapterEvent *event)
    {
        // 获取实例对象，回调实例事件。
        auto itemAdapter = reinterpret_cast<ArkUIListItemAdapter *>(OH_ArkUI_NodeAdapterEvent_GetUserData(event));
        itemAdapter->OnAdapterEvent(event);
    }

    void OnAdapterEvent(ArkUI_NodeAdapterEvent *event)
    {
        auto type = OH_ArkUI_NodeAdapterEvent_GetType(event);
        switch (type) {
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
    }

    // 分配ID给需要显示的Item，用于ReloadAllItems场景的元素diff。
    void OnNewItemIdCreated(ArkUI_NodeAdapterEvent *event)
    {
        auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
        static std::hash<std::string> hashId = std::hash<std::string>();
        auto id = hashId(data_[index]);
        OH_ArkUI_NodeAdapterEvent_SetNodeId(event, id);
    }

    // 需要新的Item显示在可见区域。
    void OnNewItemAttached(ArkUI_NodeAdapterEvent *event)
    {
        auto index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
        ArkUI_NodeHandle handle = nullptr;
        if (!cachedItems_.empty()) {
            // 使用并更新回收复用的缓存。
            auto recycledItem = cachedItems_.top();
            auto textItem = std::dynamic_pointer_cast<ArkUITextNode>(recycledItem->GetChildren().back());
            textItem->SetTextContent(data_[index]);
            handle = recycledItem->GetHandle();
            auto swipeContent = recycledItem->GetSwipeContent();
            swipeContent->RegisterOnClick([this, data = data_[index]](ArkUI_NodeEvent *event) {
                auto it = std::find(data_.begin(), data_.end(), data);
                if (it != data_.end()) {
                    auto index = std::distance(data_.begin(), it);
                    RemoveItem(index);
                }
            });
            // 释放缓存池的引用。
            cachedItems_.pop();
        } else {
            // 创建新的元素。
            auto listItem = std::make_shared<ArkUIListItemNode>();
            auto textNode = std::make_shared<ArkUITextNode>();
            textNode->SetTextContent(data_[index]);
            textNode->SetFontSize(16); /* 16: font size */
            textNode->SetPercentWidth(1);
            textNode->SetHeight(100); /* 100: height */
            textNode->SetBackgroundColor(0xFFfffacd);
            textNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
            listItem->AddChild(textNode);
            // 创建ListItem划出菜单。
            auto swipeNode = std::make_shared<ArkUITextNode>();
            swipeNode->SetTextContent("del");
            swipeNode->SetFontSize(16); /* 16: font size */
            swipeNode->SetFontColor(0xFFFFFFFF);
            swipeNode->SetWidth(100); /* 100: width */
            swipeNode->SetHeight(100); /* 100: height */
            swipeNode->SetBackgroundColor(0xFFFF0000);
            swipeNode->SetTextAlign(ARKUI_TEXT_ALIGNMENT_CENTER);
            swipeNode->RegisterOnClick([this, data = data_[index]](ArkUI_NodeEvent *event) {
                auto it = std::find(data_.begin(), data_.end(), data);
                if (it != data_.end()) {
                    auto index = std::distance(data_.begin(), it);
                    RemoveItem(index);
                }
            });
            listItem->SetSwiperAction(swipeNode);
            handle = listItem->GetHandle();
            // 保持文本列表项的引用。
            items_.emplace(handle, listItem);
        }
        // 设置需要展示的元素。
        OH_ArkUI_NodeAdapterEvent_SetItem(event, handle);
    }

    // Item从可见区域移除。
    void OnItemDetached(ArkUI_NodeAdapterEvent *event)
    {
        auto item = OH_ArkUI_NodeAdapterEvent_GetRemovedNode(event);
        // 放置到缓存池中进行回收复用。
        cachedItems_.emplace(items_[item]);
    }

    std::vector<std::string> data_;
    ArkUI_NativeNodeAPI_1 *module_ = nullptr;
    ArkUI_NodeAdapterHandle handle_ = nullptr;

    // 管理NodeAdapter生成的元素。
    std::unordered_map<ArkUI_NodeHandle, std::shared_ptr<ArkUIListItemNode>> items_;

    // 管理回收复用组件池。
    std::stack<std::shared_ptr<ArkUIListItemNode>> cachedItems_;
};

} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_ARKUILISTITEMADAPTER_H
