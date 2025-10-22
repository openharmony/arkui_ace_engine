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

// 提供按钮组件的封装类。

#ifndef SCROLLABLE_COMPONENT_ARKUIBUTTONNODE_H
#define SCROLLABLE_COMPONENT_ARKUIBUTTONNODE_H

#include <memory>
#include <string>
#include "ArkUINode.h"

class ArkUIButtonNode : public BaseNode {
public:
    ArkUIButtonNode()
        : BaseNode(CreateButtonHandle())
    {
    }

    static std::shared_ptr<ArkUIButtonNode> Create()
    {
        return std::make_shared<ArkUIButtonNode>();
    }

    void SetLabel(const std::string& label)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUIButtonNode::SetLabel")) {
            return;
        }
        ArkUI_AttributeItem item { nullptr, 0, label.c_str() };
        nodeApi_->setAttribute(nodeHandle_, NODE_BUTTON_LABEL, &item);
    }

private:
    static ArkUI_NodeHandle CreateButtonHandle()
    {
        auto api = NodeApiInstance::GetInstance()->GetNativeNodeAPI();
        return api ? api->createNode(ARKUI_NODE_BUTTON) : nullptr;
    }
};

#endif // SCROLLABLE_COMPONENT_ARKUIBUTTONNODE_H