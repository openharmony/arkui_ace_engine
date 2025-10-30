/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License")
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

#ifndef CAPI0805_2_ARKUICUSTOMCOLUMN_H
#define CAPI0805_2_ARKUICUSTOMCOLUMN_H

#include "ArkUINode.h"

namespace NativeModule {

class ArkUICustomColumnNode : public ArkUINode {
public:
    ArkUICustomColumnNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_CUSTOM))
    {
        // 注册自定义事件监听器
        nativeModule_->addNodeCustomEventReceiver(handle_, OnStaticCustomEvent);
        // 声明自定义事件并转递自身作为自定义数据
        nativeModule_->registerNodeCustomEvent(handle_, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE, 0, this);
        nativeModule_->registerNodeCustomEvent(handle_, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT, 0, this);
    }
    
    ~ArkUICustomColumnNode() override
    {
        // 反注册自定义事件监听器
        nativeModule_->removeNodeCustomEventReceiver(handle_, OnStaticCustomEvent);
        // 取消声明自定义事件
        nativeModule_->unregisterNodeCustomEvent(handle_, ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE);
        nativeModule_->unregisterNodeCustomEvent(handle_, ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT);
    }
    
    void SetPaddingCustom(int32_t padding)
    {
        padding_ = padding;
        nativeModule_->markDirty(handle_, NODE_NEED_MEASURE);
    }
    
    void SetOffsetCustom(int32_t offsetX, int32_t offsetY)
    {
        offset_.x = offsetX;
        offset_.y = offsetY;
        nativeModule_->markDirty(handle_, NODE_NEED_LAYOUT);
    }
    
    void SetRegisterLayoutCallback()
    {
        OH_ArkUI_RegisterLayoutCallbackOnNodeHandle(handle_, this, OnLayoutCompleted);
        OH_LOG_INFO(LOG_APP, "SetRegisterLayoutCallback");
    }
    
    void SetUnregisterLayoutCallback()
    {
        OH_ArkUI_UnregisterLayoutCallbackOnNodeHandle(handle_);
        OH_LOG_INFO(LOG_APP, "SetUnregisterLayoutCallback");
    }

private:
    
    static void OnStaticCustomEvent(ArkUI_NodeCustomEvent *event)
    {
        // 获取组件实例对象，调用相关实例方法
        auto customNode = reinterpret_cast<ArkUICustomColumnNode *>(OH_ArkUI_NodeCustomEvent_GetUserData(event));
        auto type = OH_ArkUI_NodeCustomEvent_GetEventType(event);
        switch (type) {
            case ARKUI_NODE_CUSTOM_EVENT_ON_MEASURE:
                customNode->OnMeasure(event);
                break;
            case ARKUI_NODE_CUSTOM_EVENT_ON_LAYOUT:
                customNode->OnLayout(event);
                break;
            default:
                break;
        }
    }
    
    void OnMeasure(ArkUI_NodeCustomEvent *event)
    {
        OH_LOG_INFO(LogType::LOG_APP, "OnMeasure");
        auto layoutConstrain = OH_ArkUI_NodeCustomEvent_GetLayoutConstraintInMeasure(event);

        // 创建子节点布局限制，复用父组件布局中的百分比参考值
        auto childLayoutConstrain = OH_ArkUI_LayoutConstraint_Copy(layoutConstrain);
        OH_ArkUI_LayoutConstraint_SetMaxHeight(childLayoutConstrain, MAX_SIZE);
        OH_ArkUI_LayoutConstraint_SetMaxWidth(childLayoutConstrain, MAX_SIZE);
        OH_ArkUI_LayoutConstraint_SetMinHeight(childLayoutConstrain, 0);
        OH_ArkUI_LayoutConstraint_SetMinWidth(childLayoutConstrain, 0);

        // 测算子节点获取子节点最大值
        auto totalSize = nativeModule_->getTotalChildCount(handle_);
        int32_t maxWidth = 0;
        int32_t maxHeight = 0;
        for (uint32_t i = 0; i < totalSize; i++) {
            auto child = nativeModule_->getChildAt(handle_, i);
            // 调用测算接口测算Native组件
            nativeModule_->measureNode(child, childLayoutConstrain);
            auto size = nativeModule_->getMeasuredSize(child);
            if (size.width > maxWidth) {
                maxWidth = size.width;
            }
            if (size.height > maxHeight) {
                maxHeight = size.height;
            }
        }
        nativeModule_->setMeasuredSize(handle_, maxWidth + DOUBLE * padding_, maxHeight + DOUBLE * padding_);
    }
    
    void OnLayout(ArkUI_NodeCustomEvent *event)
    {
        OH_LOG_INFO(LogType::LOG_APP, "OnLayout");
        // 获取父组件期望位置并设置
        auto position = OH_ArkUI_NodeCustomEvent_GetPositionInLayout(event);
        nativeModule_->setLayoutPosition(handle_, position.x + offset_.x, position.y + offset_.y);
        //  获取子组件总数和自身大小
        auto totalSize = nativeModule_->getTotalChildCount(handle_);
        auto selfSize = nativeModule_->getMeasuredSize(handle_);
        float currentX = 0.0f;
        float currentY = 0.0f;
        float maxHeightInColumn = 0.0f;

        for (uint32_t i = 0; i < totalSize; i++) {
            auto child = nativeModule_->getChildAt(handle_, i);
            auto childSize = nativeModule_->getMeasuredSize(child);
            // 如果当前子组件超出容器高度，换列
            if (currentY + childSize.height > selfSize.height && currentY != 0) {
                currentX += maxHeightInColumn;
                currentY = 0;
                maxHeightInColumn = 0;
            }
            nativeModule_->layoutNode(child, currentX, currentY);
            currentY += childSize.height;
            if (childSize.width > maxHeightInColumn) {
                maxHeightInColumn = childSize.width;
            }
        }
    }
    
    static void OnLayoutCompleted(void *userData) { OH_LOG_INFO(LogType::LOG_APP, "OnLayoutCompleted"); }
    int32_t padding_ = 100;           // 内边距
    ArkUI_IntOffset offset_ = { 0, 0 }; // 偏移量
    static constexpr int DOUBLE = 2;
    static constexpr int MAX_SIZE = 2;
};

} // namespace NativeModule

#endif // CAPI0805_2_ARKUICUSTOMCOLUMN_H