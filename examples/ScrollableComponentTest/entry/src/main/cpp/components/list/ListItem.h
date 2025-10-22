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

#ifndef SCROLLABLE_COMPONENT_ARKUILISTITEM_H
#define SCROLLABLE_COMPONENT_ARKUILISTITEM_H

#include <memory>
#include "common/ArkUINode.h"

class ListItem : public BaseNode {
public:
    ListItem()
        : BaseNode(CreateHandle())
    {
    }

    ~ListItem() override
    {
        if (swipeAction_) {
            OH_ArkUI_ListItemSwipeActionOption_Dispose(swipeAction_);
            swipeAction_ = nullptr;
        }
        if (swipeItem_) {
            OH_ArkUI_ListItemSwipeActionItem_Dispose(swipeItem_);
            swipeItem_ = nullptr;
        }
        swipeContent_.reset();
    }

    // 适配：使用 BaseNode 指针，内部用 nodeApi_ 设置属性
    void SetSwiperAction(const std::shared_ptr<BaseNode>& node)
    {
        swipeContent_ = node;

        if (!swipeItem_) {
            swipeItem_ = OH_ArkUI_ListItemSwipeActionItem_Create();
        }
        OH_ArkUI_ListItemSwipeActionItem_SetContent(swipeItem_, node ? node->GetHandle() : nullptr);

        if (!swipeAction_) {
            swipeAction_ = OH_ArkUI_ListItemSwipeActionOption_Create();
        }
        OH_ArkUI_ListItemSwipeActionOption_SetEnd(swipeAction_, swipeItem_);

        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUIListItemNode::SetSwiperAction")) {
            return;
        }
        ArkUI_AttributeItem item{};
        item.object = swipeAction_;
        nodeApi_->setAttribute(nodeHandle_, NODE_LIST_ITEM_SWIPE_ACTION, &item);
    }

    std::shared_ptr<BaseNode> GetSwipeContent() const
    {
        return swipeContent_;
    }

private:
    static ArkUI_NodeHandle CreateHandle()
    {
        auto api = NodeApiInstance::GetInstance()->GetNativeNodeAPI();
        return api ? api->createNode(ARKUI_NODE_LIST_ITEM) : nullptr;
    }

    ArkUI_ListItemSwipeActionOption* swipeAction_ = nullptr;
    ArkUI_ListItemSwipeActionItem*   swipeItem_   = nullptr;
    std::shared_ptr<BaseNode>        swipeContent_;
};

#endif // SCROLLABLE_COMPONENT_ARKUILISTITEM_H
