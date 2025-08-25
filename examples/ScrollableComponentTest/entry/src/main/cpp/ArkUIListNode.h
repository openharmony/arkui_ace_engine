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

// 提供列表组件的封装。

#ifndef SCROLLABLE_COMPONENT_ARKUILISTNODE_H
#define SCROLLABLE_COMPONENT_ARKUILISTNODE_H

#include "ArkUIListItemAdapter.h"
#include "ArkUINode.h"

namespace NativeModule {
class ArkUIListNode : public ArkUINode {
public:
    // 创建ArkUI的列表组件。
    ArkUIListNode() : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_LIST))
    {
    }

    ~ArkUIListNode() override {}
    // List组件的属性C API接口封装。
    void SetScrollBarState(bool isShow)
    {
        ArkUI_ScrollBarDisplayMode displayMode =
            isShow ? ARKUI_SCROLL_BAR_DISPLAY_MODE_ON : ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF;
        ArkUI_NumberValue value[] = {{.i32 = displayMode}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
    }
    void SetSticky(ArkUI_StickyStyle style)
    {
        ArkUI_NumberValue value[] = {{.i32 = style}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_LIST_STICKY, &item);
    }
    // 引入懒加载模块。
    void SetLazyAdapter(const std::shared_ptr<ArkUIListItemAdapter> &adapter)
    {
        ArkUI_AttributeItem item{nullptr, 0, nullptr, adapter->GetHandle()};
        nativeModule_->setAttribute(handle_, NODE_LIST_NODE_ADAPTER, &item);
        adapter_ = adapter;
    }
private:
    std::shared_ptr<ArkUIListItemAdapter> adapter_;
};
} // namespace NativeModule

#endif // SCROLLABLE_COMPONENT_ARKUILISTNODE_H