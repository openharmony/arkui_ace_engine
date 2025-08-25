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

// ArkUIListItemGroupNode.h

#ifndef SCROLLABLE_COMPONENT_ARKUILISTITEMGROUPNODE_H
#define SCROLLABLE_COMPONENT_ARKUILISTITEMGROUPNODE_H

#include "ArkUIListItemAdapter.h"
#include "ArkUINode.h"

namespace NativeModule {
class ArkUIListItemGroupNode : public ArkUINode {
public:
    ArkUIListItemGroupNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_LIST_ITEM_GROUP))
    {
    }

    void SetHeader(std::shared_ptr<ArkUINode> node)
    {
        if (node) {
            ArkUI_AttributeItem Item = {.object = node->GetHandle()};
            nativeModule_->setAttribute(handle_, NODE_LIST_ITEM_GROUP_SET_HEADER, &Item);
        } else {
            nativeModule_->resetAttribute(handle_, NODE_LIST_ITEM_GROUP_SET_HEADER);
        }
    }

    void SetFooter(std::shared_ptr<ArkUINode> node)
    {
        if (node) {
            ArkUI_AttributeItem Item = {.object = node->GetHandle()};
            nativeModule_->setAttribute(handle_, NODE_LIST_ITEM_GROUP_SET_FOOTER, &Item);
        } else {
            nativeModule_->resetAttribute(handle_, NODE_LIST_ITEM_GROUP_SET_FOOTER);
        }
    }

    std::shared_ptr<ArkUINode> GetHeader() const
    {
        return header_;
    }

    std::shared_ptr<ArkUINode> GetFooter() const
    {
        return footer_;
    }

    // 引入懒加载模块。
    void SetLazyAdapter(const std::shared_ptr<ArkUIListItemAdapter> &adapter)
    {
        ArkUI_AttributeItem item{nullptr, 0, nullptr, adapter->GetHandle()};
        nativeModule_->setAttribute(handle_, NODE_LIST_ITEM_GROUP_NODE_ADAPTER, &item);
        adapter_ = adapter;
    }

private:
    std::shared_ptr<ArkUINode> header_;
    std::shared_ptr<ArkUINode> footer_;
    std::shared_ptr<ArkUIListItemAdapter> adapter_;
};

} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_ARKUILISTITEMGROUPNODE_H
