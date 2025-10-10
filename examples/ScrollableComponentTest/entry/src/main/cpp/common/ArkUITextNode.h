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

// 实现文本组件的封装类。

#ifndef SCROLLABLE_COMPONENT_ARKUITEXTNODE_H
#define SCROLLABLE_COMPONENT_ARKUITEXTNODE_H

#include <memory>
#include <string>
#include "ArkUINode.h"

class ArkUITextNode : public BaseNode {
public:
    ArkUITextNode()
        : BaseNode(CreateTextHandle())
    {}

    static std::shared_ptr<ArkUITextNode> Create()
    {
        return std::make_shared<ArkUITextNode>();
    }

    // 文本属性 C API 封装
    void SetFontSize(float fontSize)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUITextNode::SetFontSize")) return;
        ArkUI_NumberValue value[] = { {.f32 = fontSize} };
        ArkUI_AttributeItem item { value, 1, nullptr };
        nodeApi_->setAttribute(nodeHandle_, NODE_FONT_SIZE, &item);
    }

    void SetFontColor(uint32_t color)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUITextNode::SetFontColor")) return;
        ArkUI_NumberValue value[] = { {.u32 = color} };
        ArkUI_AttributeItem item { value, 1, nullptr };
        nodeApi_->setAttribute(nodeHandle_, NODE_FONT_COLOR, &item);
    }

    void SetTextContent(const std::string& content)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUITextNode::SetTextContent")) return;
        ArkUI_AttributeItem item { nullptr, 0, content.c_str() };
        nodeApi_->setAttribute(nodeHandle_, NODE_TEXT_CONTENT, &item);
    }

    void SetTextAlign(ArkUI_TextAlignment align)
    {
        if (!ValidateApiAndNode(nodeApi_, nodeHandle_, "ArkUITextNode::SetTextAlign")) return;
        ArkUI_NumberValue value[] = { {.i32 = static_cast<int32_t>(align)} };
        ArkUI_AttributeItem item { value, 1, nullptr };
        nodeApi_->setAttribute(nodeHandle_, NODE_TEXT_ALIGN, &item);
    }

private:
    static ArkUI_NodeHandle CreateTextHandle()
    {
        auto api = NodeApiInstance::GetInstance()->GetNativeNodeAPI();
        return api ? api->createNode(ARKUI_NODE_TEXT) : nullptr;
    }
};

#endif // SCROLLABLE_COMPONENT_ARKUITEXTNODE_H