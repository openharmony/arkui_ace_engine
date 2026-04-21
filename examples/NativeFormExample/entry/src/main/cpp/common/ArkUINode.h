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

#ifndef MYAPPLICATION_ARKUINODE_H
#define MYAPPLICATION_ARKUINODE_H

#include "ArkUIBaseNode.h"
#include "NativeModule.h"
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <arkui/native_animate.h>

namespace NativeModule {

class ArkUINode : public ArkUIBaseNode {
public:
    explicit ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle) {}

    ~ArkUINode() override {}

    // 通用属性调用封装
    void SetWidth(float width, bool isPercent)
    {
        if (isPercent) {
            SetPercentWidth(width);
            return;
        }
        ArkUI_NumberValue value[] = {{.f32 = width}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_WIDTH, &item);
    }
    void SetPercentWidth(float percent)
    {
        ArkUI_NumberValue value[] = {{.f32 = percent}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_WIDTH_PERCENT, &item);
    }
    void SetHeight(float height, bool isPercent)
    {
        if (isPercent) {
            SetPercentHeight(height);
            return;
        }
        ArkUI_NumberValue value[] = {{.f32 = height}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_HEIGHT, &item);
    }
    void SetPercentHeight(float percent)
    {
        ArkUI_NumberValue value[] = {{.f32 = percent}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_HEIGHT_PERCENT, &item);
    }
    void SetBackgroundColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_BACKGROUND_COLOR, &item);
    }
    void SetPadding(float padding, bool isPercent = false)
    {
        ArkUI_NumberValue value[] = {{.f32 = padding}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, isPercent ? NODE_PADDING_PERCENT : NODE_PADDING, &item);
    }
    void SetMargin(float margin, bool isPercent = false)
    {
        ArkUI_NumberValue value[] = {{.f32 = margin}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, isPercent ? NODE_MARGIN_PERCENT : NODE_MARGIN, &item);
    }
    void SetVisibility(int visibility)
    {
        ArkUI_NumberValue value[] = {{.i32 = visibility}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_VISIBILITY, &item);
    }
    
    // 处理通用事件。
    void RegisterOnClick(const std::function<void()> &onClick) {
        assert(handle_);
        onClick_ = onClick;
        // 注册点击事件。
        nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK, 0, nullptr);
    }

    void RegisterOnTouch(const std::function<void(int32_t type, float x, float y)> &onTouch) {
        assert(handle_);
        onTouch_ = onTouch;
        // 注册触碰事件。
        nativeModule_->registerNodeEvent(handle_, NODE_TOUCH_EVENT, 0, nullptr);
    }

    void RegisterOnDisappear(const std::function<void()> &onDisappear) {
        assert(handle_);
        onDisappear_ = onDisappear;
        // 注册卸载事件。
        nativeModule_->registerNodeEvent(handle_, NODE_EVENT_ON_DISAPPEAR, 0, nullptr);
    }

    void RegisterOnAppear(const std::function<void()> &onAppear) {
        assert(handle_);
        onAppear_ = onAppear;
        // 注册挂载事件。
        nativeModule_->registerNodeEvent(handle_, NODE_EVENT_ON_APPEAR, 0, nullptr);
    }

protected:
    // 组件树操作的实现类对接。
    void OnAddChild(const std::shared_ptr<ArkUIBaseNode> &child) override
    {
        nativeModule_->addChild(handle_, child->GetHandle());
    }
    void OnRemoveChild(const std::shared_ptr<ArkUIBaseNode> &child) override
    {
        nativeModule_->removeChild(handle_, child->GetHandle());
    }
    void OnInsertChild(const std::shared_ptr<ArkUIBaseNode> &child, int32_t index) override
    {
        nativeModule_->insertChildAt(handle_, child->GetHandle(), index);
    }
    // 事件监听器函数指针。
    static void NodeEventReceiver(ArkUI_NodeEvent *event) {
        // 获取事件发生的UI组件对象。
        auto nodeHandle = OH_ArkUI_NodeEvent_GetNodeHandle(event);
        // 获取保持在UI组件对象中的自定义数据，返回封装类指针。
        auto *node = reinterpret_cast<ArkUINode *>(
            NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->getUserData(nodeHandle));
        // 基于封装类实例对象处理事件。
        node->ProcessNodeEvent(event);
    }
    void ProcessNodeEvent(ArkUI_NodeEvent *event) {
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (eventType) {
        case NODE_ON_CLICK: {
            if (onClick_) {
                onClick_();
            }
            break;
        }
        case NODE_TOUCH_EVENT: {
            if (onTouch_) {
                auto *uiInputEvent = OH_ArkUI_NodeEvent_GetInputEvent(event);
                float x = OH_ArkUI_PointerEvent_GetX(uiInputEvent);
                float y = OH_ArkUI_PointerEvent_GetY(uiInputEvent);
                auto type = OH_ArkUI_UIInputEvent_GetAction(uiInputEvent);
                onTouch_(type, x, y);
            }
        }
        case NODE_EVENT_ON_DISAPPEAR: {
            if (onDisappear_) {
                onDisappear_();
            }
            break;
        }
        case NODE_EVENT_ON_APPEAR: {
            if (onAppear_) {
                onAppear_();
            }
            break;
        }
        default: {
            // 组件特有事件交给子类处理
            OnNodeEvent(event);
        }
        }
    }

    virtual void OnNodeEvent(ArkUI_NodeEvent *event) {}
    
private:
    std::function<void()> onClick_;
    std::function<void()> onDisappear_;
    std::function<void()> onAppear_;
    std::function<void(int32_t type, float x, float y)> onTouch_;
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUINODE_H