/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "ArkUIBaseNode.h"
#include "NativeModule.h"
#include <arkui/native_node.h>
#include <arkui/native_type.h>

namespace NativeModule {

class ArkUINode : public ArkUIBaseNode {
public:
    explicit ArkUINode(ArkUI_NodeHandle handle) : ArkUIBaseNode(handle) {
        // 事件触发时需要通过函数获取对应的事件对象，这边通过设置节点自定义数据将封装类指针保持在组件上，方便后续事件分发。
            nativeModule_->setUserData(handle_, this);
            // 注册节点监听事件接收器。
            nativeModule_->addNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
    }

    ~ArkUINode() override 
    {
        if (onClick_) {
                nativeModule_->unregisterNodeEvent(handle_, NODE_ON_CLICK);
        }
        nativeModule_->removeNodeEventReceiver(handle_, ArkUINode::NodeEventReceiver);
    }
    
    void SetWidth(float width)
    {
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
    void SetHeight(float height)
    {
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
    void SetOnClick(std::function<void()> callback)
    {
        RegisterOnClick(callback);
    }
    void RegisterOnClick(const std::function<void()> &onClick)
    {
        onClick_ = onClick;
        nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK, 0, nullptr);
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
    
    // 事件监听器函数指针
    static void NodeEventReceiver(ArkUI_NodeEvent *event) 
    {
        // 获取事件发生的UI组件对象。
        auto nodeHandle = OH_ArkUI_NodeEvent_GetNodeHandle(event);
        // 获取保持在UI组件对象中的自定义数据，返回封装类指针。
        auto *node = reinterpret_cast<ArkUINode*>(
            NativeModuleInstance::GetInstance()->GetNativeNodeAPI()->getUserData(nodeHandle));
        // 基于封装类实例对象处理事件。
        node->ProcessNodeEvent(event);
    }
    
    void ProcessNodeEvent(ArkUI_NodeEvent *event) 
    {
        auto eventType = OH_ArkUI_NodeEvent_GetEventType(event);
        if (eventType == NODE_ON_CLICK && onClick_) {
            onClick_();
        }
    }
    
private:
    std::function<void()> onClick_;
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUINODE_H