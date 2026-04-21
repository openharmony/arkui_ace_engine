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

#ifndef ARKUI_GRID_NODE_H
#define ARKUI_GRID_NODE_H
#include <cstdint>

#include "ArkUIGridItemNode.h"
#include "ArkUINodeExpandAdapter.h"
#include "manager.h"
#include "../common/ArkUINode.h"

using OnItemDragStart = std::function<void(float, float, int32_t)>;
using OnItemDragEnter = std::function<void(float, float)>;
using OnItemDragMove = std::function<void(float, float, int32_t, int32_t)>;
using OnItemDragLeave = std::function<void(float, float, int32_t)>;
using OnItemDrop = std::function<void(float, float, int32_t, int32_t, bool)>;

constexpr uint32_t COLOR_LIGHT_BLUE = 0xFF00FFFF;
constexpr uint32_t PARAM_0 = 0;
constexpr uint32_t PARAM_1 = 1;
constexpr uint32_t PARAM_2 = 2;
constexpr uint32_t PARAM_3 = 3;

class ArkUIGridNode : public BaseNode {
public:
    ArkUIGridNode()
        : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_GRID)),
          nodeApi_(NodeApiInstance::GetInstance()->GetNativeNodeAPI())
    {
        if (!IsNotNull(nodeApi_) || !IsNotNull(GetHandle())) {
            return;
        }
        nodeApi_->addNodeEventReceiver(GetHandle(), StaticEventReceiver);
    }

    ~ArkUIGridNode() override
    {
        if (!IsNotNull(nodeApi_)) {
            return;
        }
        UnRegisterSpecificEvents();
        ResetGridAdapter();
    }

    // ========================================
    // 适配器设置-测试懒加载数据源绑定功能
    // ========================================
    void SetLazyAdapter(const std::shared_ptr<ItemAdapter<ArkUIGridItemNode>>& adapter)
    {
        if (!IsNotNull(adapter)) {
            return;
        }
        ArkUI_AttributeItem item { nullptr, 0, nullptr, adapter->GetAdapter() };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_NODE_ADAPTER, &item);
        nodeAdapter_ = adapter;
    }

    std::shared_ptr<ItemAdapter<ArkUIGridItemNode>> GetLazyAdapter()
    {
        return nodeAdapter_;
    }

    // ========================================
    // 属性设置 - 测试网格布局的基础属性
    // ========================================
    void SetGridColumnsGap(float gap)
    {
        ArkUI_NumberValue value { .f32 = gap };
        ArkUI_AttributeItem item = { &value, 1 };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_COLUMN_GAP, &item);
    }

    void SetGridRowsGap(float gap)
    {
        ArkUI_NumberValue value { .f32 = gap };
        ArkUI_AttributeItem item = { &value, 1 };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_ROW_GAP, &item);
    }

    // 测试NODE_GRID_DRAG_ANIMATION属性，设置Grid是否支持拖拽动画
    int32_t SetGridSupportDragAnimation(bool support)
    {
        ArkUI_NumberValue value { .i32 = support ? 1 : 0 };
        ArkUI_AttributeItem item { &value, 1 };
        return nodeApi_->setAttribute(GetHandle(), NODE_GRID_DRAG_ANIMATION, &item);
    }

    // 测试NODE_GRID_EDIT_MODE属性，设置Grid是否启用编辑模式
    int32_t SetGridEditMode(bool enable)
    {
        ArkUI_NumberValue value { .i32 = enable ? 1 : 0 };
        ArkUI_AttributeItem item { &value, 1 };
        return nodeApi_->setAttribute(GetHandle(), NODE_GRID_EDIT_MODE, &item);
    }

    int32_t SetGridColumnsTemplate(const std::string& str)
    {
        ArkUI_AttributeItem item = { .string = str.c_str() };
        return nodeApi_->setAttribute(GetHandle(), NODE_GRID_COLUMN_TEMPLATE, &item);
    }

    int32_t SetBorderWidth(float borderWidth)
    {
        ArkUI_NumberValue value[] = { { .f32 = borderWidth }, { .f32 = borderWidth }, { .f32 = borderWidth },
            { .f32 = borderWidth } };
        ArkUI_AttributeItem item = { value, 4 };
        return nodeApi_->setAttribute(GetHandle(), NODE_BORDER_WIDTH, &item);
    }

    int32_t SetGridMultiSelectable(bool enable)
    {
        ArkUI_NumberValue value { .i32 = enable ? 1 : 0 };
        ArkUI_AttributeItem item { &value, 1 };
        return nodeApi_->setAttribute(GetHandle(), NODE_GRID_MULTI_SELECTABLE, &item);
    }

    int32_t ResetGridMultiSelectable()
    {
        return nodeApi_->resetAttribute(GetHandle(), NODE_GRID_MULTI_SELECTABLE);
    }

    int32_t GetGridMultiSelectable()
    {
        int32_t value = -1;
        auto getValue = nodeApi_->getAttribute(GetHandle(), NODE_GRID_MULTI_SELECTABLE);
        if (getValue) {
            value = getValue->value->i32;
        }
        return value;
    }

    void SetSelectedStates(std::shared_ptr<ArkUIGridItemNode>& gridItem)
    {
        if (!gridItem) {
            return;
        }
        int32_t selectedState = ArkUI_UIState::UI_STATE_SELECTED;
        std::weak_ptr<ArkUIGridItemNode> weakComponent = gridItem;
        // 定义静态回调函数
        static auto selectedStateCallback = [](int32_t currentStates, void* userData) {
            auto compPtr = static_cast<ArkUIGridItemNode*>(userData);
            if (!compPtr) {
                return;
            }

            if (currentStates & ArkUI_UIState::UI_STATE_SELECTED) {
                compPtr->SetBorderWidth(5);
                compPtr->SetBorderColor(COLOR_LIGHT_BLUE, COLOR_LIGHT_BLUE, COLOR_LIGHT_BLUE, COLOR_LIGHT_BLUE);
            } else {
                compPtr->SetBorderWidth(0);
            }
        };

        ArkUI_ErrorCode result = OH_ArkUI_AddSupportedUIStates(gridItem->GetHandle(), selectedState,
            selectedStateCallback, // 使用函数指针
            false,                 // 传递组件指针作为用户数据
            gridItem.get());
        if (result != 0) {
            OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, "GridDragEventMaker",
                "SetSelectedStates fail, errorCode:%{public}d", result);
        }
    }

    // ========================================
    // 设置属性
    // ========================================
    void SetGridLayoutOptions(ArkUI_GridLayoutOptions* layoutOptions)
    {
        if (layoutOptions == nullptr) {
            return;
        }

        ArkUI_AttributeItem item = { .object = layoutOptions };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_LAYOUT_OPTIONS, &item);
    }

    // ========================================
    // 事件注册接口
    // ========================================
    void RegisterOnItemDragStart(OnItemDragStart onItemDragStart)
    {
        onItemDragStart_ = onItemDragStart;
        if (!isOnItemDragStartEventRegistered_) {
            // 测试NODE_GRID_ON_ITEM_DRAG_START事件，注册拖拽GridItem开始事件
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_START, 0, this);
            isOnItemDragStartEventRegistered_ = true;
        }
    }

    // 测试NODE_GRID_ON_ITEM_DRAG_MOVE事件，注册拖拽GridItem移动事件的回调函数
    void RegisterOnItemDragMove(OnItemDragMove onItemDragMove)
    {
        onItemDragMove_ = onItemDragMove;
        if (!isOnItemDragMoveEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_MOVE, 0, this);
            isOnItemDragMoveEventRegistered_ = true;
        }
    }

    // 测试NODE_GRID_ON_ITEM_DRAG_ENTER事件，注册拖拽GridItem进入Grid事件的回调函数
    void RegisterOnItemDragEnter(OnItemDragEnter onItemDragEnter)
    {
        onItemDragEnter_ = onItemDragEnter;
        if (!isOnItemDragEnterEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_ENTER, 0, this);
            isOnItemDragEnterEventRegistered_ = true;
        }
    }

    // 测试NODE_GRID_ON_ITEM_DRAG_LEAVE事件，注册拖拽GridItem离开Grid事件的回调函数
    void RegisterOnItemDragLeave(OnItemDragLeave onItemDragLeave)
    {
        onItemDragLeave_ = onItemDragLeave;
        if (!isOnItemDragLeaveEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_LEAVE, 0, this);
            isOnItemDragLeaveEventRegistered_ = true;
        }
    }

    // 测试NODE_GRID_ON_ITEM_DROP事件，注册放置GridItem事件的回调函数
    void RegisterOnItemDrop(OnItemDrop onItemDrop)
    {
        onItemDrop_ = onItemDrop;
        if (!isOnItemDropEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DROP, 0, this);
            isOnItemDropEventRegistered_ = true;
        }
    }

protected:
    void OnNodeEvent(ArkUI_NodeEvent* event) override
    {
        BaseNode::OnNodeEvent(event);

        HandleGridEvent(event);
    }

    void HandleGridEvent(ArkUI_NodeEvent* event)
    {
        int32_t eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (eventType) {
            case NODE_GRID_ON_ITEM_DRAG_START:
                HandleOnDragStartEvent(event);
                break;
            case NODE_GRID_ON_ITEM_DRAG_MOVE:
                HandleOnDragMoveEvent(event);
                break;
            case NODE_GRID_ON_ITEM_DRAG_LEAVE:
                HandleOnDragLeaveEvent(event);
                break;
            case NODE_GRID_ON_ITEM_DRAG_ENTER:
                HandleOnDragEnterEvent(event);
                break;
            case NODE_GRID_ON_ITEM_DROP:
                HandleOnDropEvent(event);
                break;
            default:
                break;
        }
    }

    // 处理拖拽开始事件
    void HandleOnDragStartEvent(ArkUI_NodeEvent* event)
    {
        {
            ArkUI_NumberValue drag_value[] = { { .i32 = 1 } };
            auto ret = OH_ArkUI_NodeEvent_SetReturnNumberValue(event, drag_value, 1);
            if (ret != 0) {
                OH_LOG_Print(LOG_APP, LOG_ERROR, LOG_PRINT_DOMAIN, LOG_TAG,
                    "SetOnItemDragStart setReturnNumberValue ret: %{public}d", ret);
            }
            if (onItemDragStart_) {
                ArkUI_NumberValue value[PARAM_3];
                OH_ArkUI_NodeEvent_GetNumberValue(event, PARAM_0, value);
                OH_ArkUI_NodeEvent_GetNumberValue(event, PARAM_1, value);
                OH_ArkUI_NodeEvent_GetNumberValue(event, PARAM_2, value);
                auto x = value[PARAM_0].f32;
                auto y = value[PARAM_1].f32;
                auto index = value[PARAM_2].i32;
                onItemDragStart_(x, y, index);
            }
        }
    }

    // 处理拖拽移动事件
    void HandleOnDragMoveEvent(ArkUI_NodeEvent* event)
    {
        {
            if (onItemDragMove_) {
                ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
                float x = result->data[0].f32;
                float y = result->data[1].f32;
                int32_t itemIndex = result->data[2].i32;
                int32_t insertIndex = result->data[3].i32;
                onItemDragMove_(x, y, itemIndex, insertIndex);
            }
        }
    }

    // 处理拖拽离开事件
    void HandleOnDragLeaveEvent(ArkUI_NodeEvent* event)
    {
        {
            if (onItemDragLeave_) {
                ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
                float x = result->data[0].f32;
                float y = result->data[1].f32;
                int32_t itemIndex = result->data[2].i32;
                onItemDragLeave_(x, y, itemIndex);
            }
        }
    }

    // 处理拖拽进入事件
    void HandleOnDragEnterEvent(ArkUI_NodeEvent* event)
    {
        {
            if (onItemDragEnter_) {
                ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
                float x = result->data[0].f32;
                float y = result->data[1].f32;
                onItemDragEnter_(x, y);
            }
        }
    }

    // 处理放置事件
    void HandleOnDropEvent(ArkUI_NodeEvent* event)
    {
        {
            if (onItemDrop_) {
                ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
                float x = result->data[0].f32;
                float y = result->data[1].f32;
                int32_t itemIndex = result->data[2].i32;
                int32_t insertIndex = result->data[3].i32;
                bool isSuccess = result->data[4].i32;
                onItemDrop_(x, y, itemIndex, insertIndex, isSuccess);
            }
        }
    }
 
private:
    void UnRegisterSpecificEvents()
    {
        if (isOnItemDragStartEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_START);
        }
        if (isOnItemDragMoveEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_MOVE);
        }
        if (isOnItemDragEnterEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_ENTER);
        }
        if (isOnItemDragLeaveEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DRAG_LEAVE);
        }
        if (isOnItemDropEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ON_ITEM_DROP);
        }
    }

    void ResetGridAdapter()
    {
        if (IsNotNull(nodeAdapter_)) {
            nodeApi_->resetAttribute(GetHandle(), NODE_GRID_NODE_ADAPTER);
            nodeAdapter_.reset();
        }
    }

    static std::shared_ptr<ArkUIGridNode> BuildGrid();
    ArkUI_NativeNodeAPI_1* nodeApi_ = nullptr;
    std::shared_ptr<ItemAdapter<ArkUIGridItemNode>> nodeAdapter_;

    // 事件回调函数
    OnItemDragStart onItemDragStart_;
    OnItemDragEnter onItemDragEnter_;
    OnItemDragMove onItemDragMove_;
    OnItemDragLeave onItemDragLeave_;
    OnItemDrop onItemDrop_;

    // 事件注册状态
    bool isOnItemDragStartEventRegistered_;
    bool isOnItemDragEnterEventRegistered_;
    bool isOnItemDragMoveEventRegistered_;
    bool isOnItemDragLeaveEventRegistered_;
    bool isOnItemDropEventRegistered_;
};

#endif // ARKUI_GRID_NODE_H
 