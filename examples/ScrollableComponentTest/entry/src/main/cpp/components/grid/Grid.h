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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_GRID_H
#define SCROLLABLE_COMPONENT_COMPONENTS_GRID_H

#include <memory>

#include <arkui/native_node.h>

#include "common/ArkUIUtils.h"
#include "common/ArkUIScrollEvents.h"
#include "common/ArkUINode.h"
#include "common/ArkUINodeAdapter.h"

class Grid : public BaseNode {
public:
    static ArkUI_NodeHandle CreateScrollableGrid();

    Grid()
        : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_GRID)),
          nodeApi_(NodeApiInstance::GetInstance()->GetNativeNodeAPI())
    {
        if (!IsNotNull(nodeApi_) || !IsNotNull(GetHandle())) {
            return;
        }

        nodeApi_->addNodeEventReceiver(GetHandle(), StaticEventReceiver);
        scrollEventGuard_.Bind(nodeApi_, GetHandle(), this, SCROLL_EVT_ALL);
    }

    ~Grid() override
    {
        scrollEventGuard_.Release();
        nodeAdapter_.reset();
    }

    // ========================================
    // 尺寸设置接口
    // ========================================
    void SetGridSize(float width, float height)
    {
        SetSize(width, height);
    }

    void SetGridSizePercent(float widthPercent, float heightPercent)
    {
        SetSizePercent(widthPercent, heightPercent);
    }

    // ========================================
    // 模板和间距设置
    // ========================================
    void SetRowsTemplate(const char *rowsTemplate)
    {
        SetAttributeString(nodeApi_, GetHandle(), NODE_GRID_ROW_TEMPLATE, rowsTemplate);
    }

    void SetColumnsTemplate(const char *columnsTemplate)
    {
        SetAttributeString(nodeApi_, GetHandle(), NODE_GRID_COLUMN_TEMPLATE, columnsTemplate);
    }

    void SetColumnsGap(float gap)
    {
        SetAttributeFloat32(nodeApi_, GetHandle(), NODE_GRID_COLUMN_GAP, gap);
    }

    void SetRowsGap(float gap)
    {
        SetAttributeFloat32(nodeApi_, GetHandle(), NODE_GRID_ROW_GAP, gap);
    }

    // ========================================
    // 行为和性能设置
    // ========================================
    void SetCachedCount(uint32_t count)
    {
        SetAttributeUInt32(nodeApi_, GetHandle(), NODE_GRID_CACHED_COUNT, count);
    }

    void SetFocusWrapMode(ArkUI_FocusWrapMode mode)
    {
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_GRID_FOCUS_WRAP_MODE, static_cast<int32_t>(mode));
    }

    void SetSyncLoad(bool enabled)
    {
        SetAttributeInt32(nodeApi_, GetHandle(), NODE_GRID_SYNC_LOAD, enabled ? 1 : 0);
    }

    void SetDefaultScrollStyle()
    {
        ::SetDefaultScrollStyle(nodeApi_, GetHandle());
    }

    // ========================================
    // 适配器设置
    // ========================================
    void SetLazyAdapter(const std::shared_ptr<ArkUINodeAdapter> &adapter)
    {
        if (!IsNotNull(adapter)) {
            return;
        }
        ArkUI_AttributeItem item{nullptr, 0, nullptr, adapter->GetAdapter()};
        nodeApi_->setAttribute(GetHandle(), NODE_GRID_NODE_ADAPTER, &item);
        nodeAdapter_ = adapter;
    }

protected:
    void OnNodeEvent(ArkUI_NodeEvent *event) override
    {
        BaseNode::OnNodeEvent(event);
    }

private:
    ArkUI_NativeNodeAPI_1 *nodeApi_ = nullptr;
    std::shared_ptr<ArkUINodeAdapter> nodeAdapter_;
    ScrollEventGuard scrollEventGuard_;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_GRID_H
