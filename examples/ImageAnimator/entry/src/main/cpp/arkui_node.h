/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
// ArkUINode.h
// 提供通用属性和事件的封装。

#ifndef MYAPPLICATION_ARKUINODE_H
#define MYAPPLICATION_ARKUINODE_H

#include <arkui/native_node.h>
#include <arkui/native_type.h>

#include "arkui_base_node.h"
#include "native_module.h"

namespace NativeModule {

class ArkUINode : public ArkUIBaseNode {
public:
    explicit ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle) {}

    ~ArkUINode() override {}

    // NDK相关通用属性调用封装
    void SetWidth(float width)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .f32 = width } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_WIDTH, &item);
    }
    void SetPercentWidth(float percent)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .f32 = percent } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_WIDTH_PERCENT, &item);
    }
    void SetHeight(float height)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .f32 = height } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_HEIGHT, &item);
    }
    void SetPercentHeight(float percent)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .f32 = percent } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_HEIGHT_PERCENT, &item);
    }
    void SetBackgroundColor(uint32_t color)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .u32 = color } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_BACKGROUND_COLOR, &item);
    }
    void SetBorderColor(uint32_t color)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .u32 = color } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_BORDER_COLOR, &item);
    }
    void SetBorderWidth(float width)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = { { .f32 = width } };
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_BORDER_WIDTH, &item);
    }

protected:
    // 组件树操作的实现类对接。
    void OnAddChild(const std::shared_ptr<ArkUIBaseNode>& child) override
    {
        nativeModule_->addChild(handle_, child->GetHandle());
    }
    void OnRemoveChild(const std::shared_ptr<ArkUIBaseNode>& child) override
    {
        nativeModule_->removeChild(handle_, child->GetHandle());
    }
    void OnInsertChild(const std::shared_ptr<ArkUIBaseNode>& child, int32_t index) override
    {
        nativeModule_->insertChildAt(handle_, child->GetHandle(), index);
    }
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUINODE_H
