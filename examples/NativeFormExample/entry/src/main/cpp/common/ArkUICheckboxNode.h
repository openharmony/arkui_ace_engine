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

#ifndef MYAPPLICATION_ARKUICHECKBOXNODE_H
#define MYAPPLICATION_ARKUICHECKBOXNODE_H

#include "ArkUINode.h"

#include <cstdint>
#include <string>

namespace NativeModule {
class ArkUICheckboxNode : public ArkUINode {
public:
    ArkUICheckboxNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_CHECKBOX)) {}
    // 属性接口封装。
    void SetIsSelect(bool isSelect)
    {
        ArkUI_NumberValue value[] = {{.i32 = isSelect ? 1 : 0}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_SELECT, &item);
    }
    void SetSelectColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_SELECT_COLOR, &item);
    }
    void SetUnSelectColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_UNSELECT_COLOR, &item);
    }
    void SetCheckboxMark(uint32_t color, float size = -1.0f, float strokeWidth = 2.0f)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}, {.f32 = size}, {.f32 = strokeWidth}};
        ArkUI_AttributeItem item = {value, size >= 0 ? 3 : 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_MARK, &item);
    }
    void SetCheckboxShape(ArkUI_CheckboxShape shape)
    {
        ArkUI_NumberValue value[] = {{.i32 = shape}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_SHAPE, &item);
    }
    void SetCheckboxName(const std::string &name)
    {
        ArkUI_AttributeItem item = {nullptr, 0, name.c_str()};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_NAME, &item);
    }
    void SetCheckboxGroup(const std::string &group)
    {
        ArkUI_AttributeItem item = {nullptr, 0, group.c_str()};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP, &item);
    }
};

class ArkUICheckboxGroupNode : public ArkUINode {
public:
    ArkUICheckboxGroupNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_CHECKBOX_GROUP)) {}
    // 属性接口封装。
    void SetCheckboxGroupName(const std::string &name)
    {
        ArkUI_AttributeItem item = {nullptr, 0, name.c_str()};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_NAME, &item);
    }
    void SetIsSelectAll(bool isSelectAll)
    {
        ArkUI_NumberValue value[] = {{.i32 = isSelectAll ? 1 : 0}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_SELECT_ALL, &item);
    }
    void SetSelectColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_SELECTED_COLOR, &item);
    }
    void SetUnSelectColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_UNSELECTED_COLOR, &item);
    }
    void SetCheckboxGroupMark(uint32_t color, float size = -1.0f, float strokeWidth = 2.0f)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}, {.f32 = size}, {.f32 = strokeWidth}};
        ArkUI_AttributeItem item = {value, size >= 0 ? 3 : 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_MARK, &item);
    }
    void SetCheckboxGroupShape(ArkUI_CheckboxShape shape)
    {
        ArkUI_NumberValue value[] = {{.i32 = shape}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_CHECKBOX_GROUP_SHAPE, &item);
    }
    
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUICHECKBOXNODE_H