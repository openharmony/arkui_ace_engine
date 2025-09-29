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

#ifndef SCROLLABLE_COMPONENT_COMPONENTS_LIST_LISTITEMGROUP_H
#define SCROLLABLE_COMPONENT_COMPONENTS_LIST_LISTITEMGROUP_H

#include <memory>
#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "common/ArkUINode.h"
#include "common/ArkUINodeAdapter.h"

/** 轻量封装：分组节点，仅提供示例所需 API */
class ListItemGroupNode : public BaseNode {
public:
    ListItemGroupNode()
        : BaseNode(NodeApiInstance::GetInstance()->GetNativeNodeAPI()->createNode(ARKUI_NODE_LIST_ITEM_GROUP)),
          api_(NodeApiInstance::GetInstance()->GetNativeNodeAPI())
    {
    }

    ~ListItemGroupNode() override
    {
        if (!api_) {
            return;
        }

        // 清空 adapter
        if (adapter_) {
            ArkUI_AttributeItem it{nullptr, 0, nullptr, nullptr};
            api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_NODE_ADAPTER, &it);
            adapter_.reset();
        }

        // 清空 header / footer —— 传 nullptr 给同一属性即可
        if (header_) {
            ArkUI_AttributeItem it{nullptr, 0, nullptr, nullptr};
            api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_SET_HEADER, &it);
            header_.reset();
        }
        if (footer_) {
            ArkUI_AttributeItem it{nullptr, 0, nullptr, nullptr};
            api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_SET_FOOTER, &it);
            footer_.reset();
        }
    }

    // 设置/清空 Header：传 nullptr 即清空
    void SetHeader(const std::shared_ptr<BaseNode> &header)
    {
        ArkUI_AttributeItem it{nullptr, 0, nullptr, header ? header->GetHandle() : nullptr};
        api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_SET_HEADER, &it);
        header_ = header;
    }

    // 设置/清空 Footer：传 nullptr 即清空
    void SetFooter(const std::shared_ptr<BaseNode> &footer)
    {
        ArkUI_AttributeItem it{nullptr, 0, nullptr, footer ? footer->GetHandle() : nullptr};
        api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_SET_FOOTER, &it);
        footer_ = footer;
    }

    void SetLazyAdapter(const std::shared_ptr<ArkUINodeAdapter> &adapter)
    {
        if (!adapter) {
            ArkUI_AttributeItem it{nullptr, 0, nullptr, nullptr};
            api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_NODE_ADAPTER, &it);
            adapter_.reset();
            return;
        }
        adapter->EnsurePlaceholderTypeOr(static_cast<int32_t>(ARKUI_NODE_LIST_ITEM));
        ArkUI_AttributeItem it{nullptr, 0, nullptr, adapter->GetAdapter()};
        api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_NODE_ADAPTER, &it);
        adapter_ = adapter;
    }

    // 可选：分组 divider
    void SetDivider(float widthPx)
    {
        ArkUI_NumberValue v{.f32 = widthPx};
        ArkUI_AttributeItem it{&v, 1};
        api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_SET_DIVIDER, &it);
    }

    // 可选：分组 children main size
    void SetChildrenMainSizeOption(ArkUI_ListChildrenMainSize *opt)
    {
        ArkUI_AttributeItem it{nullptr, 0, nullptr, opt};
        api_->setAttribute(GetHandle(), NODE_LIST_ITEM_GROUP_CHILDREN_MAIN_SIZE, &it);
    }

private:
    ArkUI_NativeNodeAPI_1 *api_ = nullptr;
    std::shared_ptr<ArkUINodeAdapter> adapter_;
    std::shared_ptr<BaseNode> header_;
    std::shared_ptr<BaseNode> footer_;
};

#endif // SCROLLABLE_COMPONENT_COMPONENTS_LIST_LISTITEMGROUP_H
