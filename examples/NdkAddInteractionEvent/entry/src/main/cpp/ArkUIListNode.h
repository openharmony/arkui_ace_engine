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

// [Start arkui_list_node]
// ArkUIListNode.h
// 列表封装类对象

#ifndef MYAPPLICATION_ARKUILISTNODE_H
#define MYAPPLICATION_ARKUILISTNODE_H

#include "ArkUINode.h"

namespace NativeModule {
class ArkUIListNode : public ArkUINode {
public:
    ArkUIListNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_LIST)) {}

    ~ArkUIListNode() override { nativeModule_->unregisterNodeEvent(handle_, NODE_LIST_ON_SCROLL_INDEX); }

    void SetScrollBarState(bool isShow)
    {
        if (!handle_) {
            return;
        }
        ArkUI_ScrollBarDisplayMode displayMode =
            isShow ? ARKUI_SCROLL_BAR_DISPLAY_MODE_ON : ARKUI_SCROLL_BAR_DISPLAY_MODE_OFF;
        ArkUI_NumberValue value[] = {{.i32 = displayMode}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_SCROLL_BAR_DISPLAY_MODE, &item);
    }

    // 注册列表相关事件。
    void RegisterOnScrollIndex(const std::function<void(int32_t index)> &onScrollIndex)
    {
        if (!handle_) {
            return;
        }
        onScrollIndex_ = onScrollIndex;
        nativeModule_->registerNodeEvent(handle_, NODE_LIST_ON_SCROLL_INDEX, 0, nullptr);
    }

protected:
   // 处理List相关事件。
    void OnNodeEvent(ArkUI_NodeEvent *event) override
    {
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (eventType) {
            case NODE_LIST_ON_SCROLL_INDEX: {
                auto index = OH_ArkUI_NodeEvent_GetNodeComponentEvent(event)->data[0];
                if (onScrollIndex_) {
                    onScrollIndex_(index.i32);
                }
            }
            default: {
            }
        }
    }

private:
    std::function<void(int32_t index)> onScrollIndex_;
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUILISTNODE_H
// [End arkui_list_node]