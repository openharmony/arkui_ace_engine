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

#ifndef ACCESSIBILITY_CAPI_FAKE_CUSTOMWIDGET_H
#define ACCESSIBILITY_CAPI_FAKE_CUSTOMWIDGET_H

#include "fake_node.h"
#include <vector>

namespace NativeXComponentSample {

/**
 * @brief 自定义容器节点
 *
 * 作为场景的根节点，管理子节点
 * 演示以下Native接口：
 * - SetAccessibilityGroup
 * - SetAccessibilityLevel
 * - SetChildNodeIds
 */
class FakeCustomWidget : public AccessibleObject {
public:
    explicit FakeCustomWidget(const std::string& name);
    ~FakeCustomWidget();

    const char* ObjectType() const override
    {
        return "FakeCustomWidget";
    }

    const char* Hint() const override
    {
        return "Container";
    }

    bool Focusable() const override
    {
        return false;  // 容器本身不可聚焦
    }

    // 添加子节点
    void AddChild(AccessibleObject* child)
    {
        if (child) {
            children_.push_back(child);
            childNodeIds_.push_back(child->GetElementId());
        }
    }

    // 获取所有子节点
    const std::vector<AccessibleObject*>& GetChildren() const
    {
        return children_;
    }

    // 获取子节点ID列表
    const std::vector<int64_t>& GetChildNodeIds() const
    {
        return childNodeIds_;
    }

    // 清理资源
    void Cleanup()
    {
        for (auto* child : children_) {
            delete child;
        }
        children_.clear();
        childNodeIds_.clear();
    }

private:
    std::vector<AccessibleObject*> children_;
    std::vector<int64_t> childNodeIds_;
};

} // namespace NativeXComponentSample

#endif // ACCESSIBILITY_CAPI_FAKE_CUSTOMWIDGET_H
