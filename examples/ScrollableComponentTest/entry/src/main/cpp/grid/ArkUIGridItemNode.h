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

#ifndef ARKUI_GRID_ITEM_NODE_H
#define ARKUI_GRID_ITEM_NODE_H
#include "../common/ArkUINode.h"

using OnItemSelect = std::function<void(bool)>;

class ArkUIGridItemNode : public BaseNode {
public:
    ArkUIGridItemNode() : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_GRID_ITEM))
    {
        if (!IsNotNull(nodeApi_) || !IsNotNull(GetHandle())) {
            return;
        }
        nodeApi_->addNodeEventReceiver(GetHandle(), StaticEventReceiver);
    }

    ~ArkUIGridItemNode() override
    {
        if (!IsNotNull(nodeApi_)) {
            return;
        }
        UnRegisterSpecificEvents();
    }

    // 测试NODE_GRID_ITEM_SELECTABLE属性，设置GridItem是否可选中
    void SetGridItemSelectable(bool selectable)
    {
        ArkUI_NumberValue value { .i32 = selectable ? 1 : 0 };
        ArkUI_AttributeItem item { &value, 1 };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_ITEM_SELECTABLE, &item);
    }

    // 测试NODE_GRID_ITEM_SELECTED属性，设置GridItem的选中状态
    void SetGridItemSelected(bool selected)
    {
        ArkUI_NumberValue value { .i32 = selected ? 1 : 0 };
        ArkUI_AttributeItem item { &value, 1 };
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_ITEM_SELECTED, &item);
    }

    // 设置GridItem的边框宽度
    int32_t SetBorderWidth(float borderWidth)
    {
        ArkUI_NumberValue value[] = { { .f32 = borderWidth }, { .f32 = borderWidth }, { .f32 = borderWidth },
            { .f32 = borderWidth } };
        ArkUI_AttributeItem item = { value, 4 };
        return nodeApi_->setAttribute(GetHandle(), NODE_BORDER_WIDTH, &item);
    }

    // 设置GridItem四个方向的边框颜色
    int32_t SetBorderColor(uint32_t top, uint32_t right, uint32_t bottom, uint32_t left)
    {
        ArkUI_NumberValue value[] = { { .u32 = top }, { .u32 = right }, { .u32 = bottom }, { .u32 = left } };
        ArkUI_AttributeItem item = { value, 4 };
        return nodeApi_->setAttribute(GetHandle(), NODE_BORDER_COLOR, &item);
    }

    // 测试NODE_GRID_ITEM_ON_SELECT事件，注册GridItem选择事件的回调函数
    void RegisterOnItemSelect(OnItemSelect onItemSelect)
    {
        onItemSelect_ = onItemSelect;
        if (!isGridItemOnSelectEventRegistered_) {
            nodeApi_->registerNodeEvent(GetHandle(), NODE_GRID_ITEM_ON_SELECT, 0, this);
            isGridItemOnSelectEventRegistered_ = true;
        }
    }

protected:
    void OnNodeEvent(ArkUI_NodeEvent* event) override
    {
        BaseNode::OnNodeEvent(event);

        HandleGridItemEvent(event);
    }

    // 处理GridItem事件的分发函数
    void HandleGridItemEvent(ArkUI_NodeEvent* event)
    {
        int32_t eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (eventType) {
            case NODE_GRID_ITEM_ON_SELECT:
                HandleOnItemSelectEvent(event);
                break;
            default:
                break;
        }
    }

    //处理具体选择事件
    void HandleOnItemSelectEvent(ArkUI_NodeEvent* event)
    {
        {
            if (onItemSelect_) {
                ArkUI_NodeComponentEvent* result = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event);
                bool selected = result->data[0].i32;
                onItemSelect_(selected);
            }
        }
    }

private:
    bool isGridItemOnSelectEventRegistered_ = false;
    OnItemSelect onItemSelect_;
    void UnRegisterSpecificEvents()
    {
        if (isGridItemOnSelectEventRegistered_) {
            nodeApi_->unregisterNodeEvent(GetHandle(), NODE_GRID_ITEM_ON_SELECT);
        }
    }
};

#endif // ARKUI_GRID_ITEM_NODE_H
