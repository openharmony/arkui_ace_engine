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

#ifndef SCROLLABLE_COMPONENT_COMMON_ARKUINODEADAPTER_H
#define SCROLLABLE_COMPONENT_COMMON_ARKUINODEADAPTER_H

#include <cstdint>
#include <functional>
#include <stack>

#include <arkui/native_interface.h>
#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "ArkUIUtils.h"

/**
 * 通用 NodeAdapter 封装
 */
struct NodeAdapterCallbacks {
    std::function<int32_t()> getTotalCount;
    std::function<uint64_t(int32_t)> getStableId;
    std::function<ArkUI_NodeHandle(ArkUI_NativeNodeAPI_1 *, int32_t)> onCreate;
    std::function<void(ArkUI_NativeNodeAPI_1 *, ArkUI_NodeHandle, int32_t)> onBind;
    std::function<void(ArkUI_NativeNodeAPI_1 *, ArkUI_NodeHandle)> onRecycle;
};

class ArkUINodeAdapter {
public:
    using Callbacks = NodeAdapterCallbacks;

    ArkUINodeAdapter() : placeholderNodeType_(K_INVALID_NODE_TYPE)
    {
        InitializeApiAndAdapter();
    }

    explicit ArkUINodeAdapter(int32_t placeholderNodeType) : placeholderNodeType_(placeholderNodeType)
    {
        InitializeApiAndAdapter();
    }

    ~ArkUINodeAdapter()
    {
        ClearNodeCache();
        OH_ArkUI_NodeAdapter_UnregisterEventReceiver(adapterHandle_);
        OH_ArkUI_NodeAdapter_Dispose(adapterHandle_);
        adapterHandle_ = nullptr;
    }

    ArkUI_NodeAdapterHandle GetAdapter() const
    {
        return adapterHandle_;
    }

    void SetPlaceholderType(int32_t placeholderNodeType)
    {
        placeholderNodeType_ = placeholderNodeType;
    }

    void EnsurePlaceholderTypeOr(int32_t fallbackNodeType)
    {
        if (placeholderNodeType_ < 0) {
            placeholderNodeType_ = fallbackNodeType;
        }
    }

    void SetCallbacks(const NodeAdapterCallbacks &callbacks)
    {
        callbacks_ = callbacks;
        SynchronizeItemCount(GetTotalItemCount());
    }

    // ========================================
    // 数据变动通知接口
    // ========================================
    void ReloadAllItems()
    {
        OH_ArkUI_NodeAdapter_ReloadAllItems(adapterHandle_);
    }

    void InsertRange(int32_t index, int32_t count)
    {
        if (count <= 0) {
            return;
        }
        int32_t validIndex = ClampIndexToRange(index, GetTotalItemCount());
        OH_ArkUI_NodeAdapter_InsertItem(adapterHandle_, validIndex, count);
        SynchronizeItemCount(GetTotalItemCount());
    }

    void RemoveRange(int32_t index, int32_t count)
    {
        if (count <= 0) {
            return;
        }
        if (!IsValidIndex(index, GetTotalItemCount())) {
            return;
        }
        OH_ArkUI_NodeAdapter_RemoveItem(adapterHandle_, index, count);
        SynchronizeItemCount(GetTotalItemCount());
    }

protected:
    // ========================================
    // 事件分发处理
    // ========================================
    static void OnStaticEvent(ArkUI_NodeAdapterEvent *event)
    {
        auto *self = reinterpret_cast<ArkUINodeAdapter *>(OH_ArkUI_NodeAdapterEvent_GetUserData(event));
        if (IsNotNull(self)) {
            self->OnEvent(event);
        }
    }

    void OnEvent(ArkUI_NodeAdapterEvent *event)
    {
        const int32_t eventType = OH_ArkUI_NodeAdapterEvent_GetType(event);
        switch (eventType) {
            case NODE_ADAPTER_EVENT_ON_GET_NODE_ID: {
                HandleGetNodeId(event);
                break;
            }
            case NODE_ADAPTER_EVENT_ON_ADD_NODE_TO_ADAPTER: {
                HandleAddNodeToAdapter(event);
                break;
            }
            case NODE_ADAPTER_EVENT_ON_REMOVE_NODE_FROM_ADAPTER: {
                HandleRemoveNodeFromAdapter(event);
                break;
            }
            default: {
                break;
            }
        }
    }

private:
    // ========================================
    // 私有常量和工具方法
    // ========================================
    static constexpr int32_t K_INVALID_NODE_TYPE = -1;
    static constexpr ArkUI_NodeType K_DEFAULT_PLACEHOLDER_TYPE = ARKUI_NODE_LIST_ITEM;

    void InitializeApiAndAdapter()
    {
        OH_ArkUI_GetModuleInterface(ARKUI_NATIVE_NODE, ArkUI_NativeNodeAPI_1, nodeApi_);
        adapterHandle_ = OH_ArkUI_NodeAdapter_Create();
        OH_ArkUI_NodeAdapter_RegisterEventReceiver(adapterHandle_, this, &ArkUINodeAdapter::OnStaticEvent);
        SynchronizeItemCount(GetTotalItemCount());
    }

    void ClearNodeCache()
    {
        while (!nodeCache_.empty()) {
            nodeCache_.pop();
        }
    }

    int32_t GetTotalItemCount() const
    {
        if (callbacks_.getTotalCount) {
            return callbacks_.getTotalCount();
        }
        return 0;
    }

    int32_t ClampIndexToRange(int32_t index, int32_t maxCount) const
    {
        if (index < 0) {
            return 0;
        }
        if (index > maxCount) {
            return maxCount;
        }
        return index;
    }

    void SynchronizeItemCount(int32_t count)
    {
        OH_ArkUI_NodeAdapter_SetTotalNodeCount(adapterHandle_, static_cast<uint32_t>(count));
    }

    ArkUI_NodeHandle PopFromCacheOrCreate(int32_t index)
    {
        if (!nodeCache_.empty()) {
            ArkUI_NodeHandle handle = nodeCache_.top();
            nodeCache_.pop();
            return handle;
        }
        if (callbacks_.onCreate) {
            return callbacks_.onCreate(nodeApi_, index);
        }
        const ArkUI_NodeType nodeType = (placeholderNodeType_ >= 0) ? static_cast<ArkUI_NodeType>(placeholderNodeType_)
                                                                    : K_DEFAULT_PLACEHOLDER_TYPE;
        return nodeApi_->createNode(nodeType);
    }

    // ========================================
    // 事件处理实现
    // ========================================
    void HandleGetNodeId(ArkUI_NodeAdapterEvent *event)
    {
        const int32_t index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
        uint64_t nodeId = static_cast<uint64_t>(index);

        if (IsValidIndex(index, GetTotalItemCount()) && callbacks_.getStableId) {
            nodeId = callbacks_.getStableId(index);
        }
        OH_ArkUI_NodeAdapterEvent_SetNodeId(event, nodeId);
    }

    void HandleAddNodeToAdapter(ArkUI_NodeAdapterEvent *event)
    {
        const int32_t index = OH_ArkUI_NodeAdapterEvent_GetItemIndex(event);
        ArkUI_NodeHandle item = PopFromCacheOrCreate(index);

        if (callbacks_.onBind && IsValidIndex(index, GetTotalItemCount())) {
            callbacks_.onBind(nodeApi_, item, index);
        }
        OH_ArkUI_NodeAdapterEvent_SetItem(event, item);
    }

    void HandleRemoveNodeFromAdapter(ArkUI_NodeAdapterEvent *event)
    {
        ArkUI_NodeHandle node = OH_ArkUI_NodeAdapterEvent_GetRemovedNode(event);
        if (!IsNotNull(node)) {
            return;
        }

        if (callbacks_.onRecycle) {
            callbacks_.onRecycle(nodeApi_, node);
        }
        nodeCache_.push(node);
    }

private:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
    ArkUI_NodeAdapterHandle adapterHandle_ = nullptr;
    NodeAdapterCallbacks callbacks_;
    std::stack<ArkUI_NodeHandle> nodeCache_;
    int32_t placeholderNodeType_ = K_INVALID_NODE_TYPE;
};

#endif // SCROLLABLE_COMPONENT_COMMON_ARKUINODEADAPTER_H
