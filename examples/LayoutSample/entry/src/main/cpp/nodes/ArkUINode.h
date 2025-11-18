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

#ifndef MYAPPLICATION_ARKUINODE_H
#define MYAPPLICATION_ARKUINODE_H

#include "NativeModule.h"
#include "nodes/ArkUIBaseNode.h"
#include <arkui/native_node.h>
#include <arkui/native_type.h>
#include <hilog/log.h>
#include <ostream>
#include <string>
#include <memory>
#include <functional>

#undef LOG_DOMAIN
#undef LOG_TAG
#define LOG_DOMAIN 0x3200 // 全局domain宏，标识业务领域
#define LOG_TAG "NativeModule"  // 全局tag宏，标识模块日志tag

namespace NativeModule {

class ArkUINode : public ArkUIBaseNode {
public:
    explicit ArkUINode(ArkUI_NodeHandle handle);
    
    ~ArkUINode() override;
    
    std::pair<std::string, ArkUI_IntSize> layoutConstraintExample(std::shared_ptr<ArkUIBaseNode> child);

    // 布局策略相关方法
    void SetWidthLayoutPolicy(int32_t policy);
    void SetHeightLayoutPolicy(int32_t policy);
    void SetConstraintSize(float minWidth, float maxWidth, float minHeight, float maxHeight);

    // 尺寸相关方法
    void SetWidth(float width);
    float GetWidth();
    void SetHeight(float height);
    void SetPercentWidth(float percent);
    void SetPercentHeight(float percent);
    void SetSize(float width, float height);
    void SetAspectRatio(float ratio);

    // 位置相关方法
    std::string GetLayoutPositionOH();
    std::string GetLayoutPosition();
    std::string GetLayoutPositionInScreen();
    std::string GetPositionWithTranslateInScreen();
    void GetPositionToParent();
    std::string GetLayoutPositionInWindow();
    std::string GetLayoutSize();
    void SetPosition(float x, float y);
    void SetOffset(float x, float y);

    // 位置边距相关方法
    void SetPositionEdges(void *positionEdge);
    std::string SetPositionEdgesExample(float top = -1, float left = -1, float bottom = -1, float right = -1);

    // 像素取整相关方法
    void SetPixelRound(void *pixelRound);
    std::string SetPixelRoundExample(ArkUI_PixelRoundCalcPolicy top, ArkUI_PixelRoundCalcPolicy start,
                                     ArkUI_PixelRoundCalcPolicy bottom, ArkUI_PixelRoundCalcPolicy end);

    // 显示和布局相关方法
    void SetDisplayPriority(uint32_t priority);
    void SetLayoutRect(int32_t positionX, int32_t positionY, int32_t width, int32_t height);
    void SetExpandSafeArea(uint32_t type, uint32_t edge);
    void SetDirection(int32_t direct);

    // 对齐相关方法
    void SetAlignSelf(int32_t align);
    void SetTextAlignment(int32_t align);
    void SetAlignment(int32_t align);
    void SetColumnJustifyContent(int32_t justifyContent);
    void SetColumnAlignItems(int32_t align);
    void SetRowAlignItems(int32_t align);
    void SetStackAlignContent(int32_t align);

    // 内边距相关方法
    void SetPadding(float top, float right, float bottom, float left);
    void SetPadding(float padding);
    void SetPercentPadding(float top, float right, float bottom, float left);
    void SetPercentPadding(float percentPadding);

    // 外边距相关方法
    void SetMargin(float top, float right, float bottom, float left);
    void SetMargin(float margin);
    void SetPercentMargin(float top, float right, float bottom, float left);
    void SetPercentMargin(float percentMargin);

    // 边框相关方法
    void SetBorderWidth(float top, float right, float bottom, float left);
    void SetBorderWidth(float borderWidth);
    void SetBorderRadius(float upperLeft, float upperRight, float lowerLeft, float lowerRight);
    void SetBorderRadius(float borderRadius);
    void SetBorderColor(uint32_t upperLeft, uint32_t upperRight, uint32_t lowerLeft, uint32_t lowerRight);
    void SetBorderColor(uint32_t borderColor);
    void SetBorderStyle(int32_t upperLeft, int32_t upperRight, int32_t lowerLeft, int32_t lowerRight);
    void SetBorderStyle(int32_t borderStyle);
    void SetBorderWidthPercent(float width);
    void SetBorderWidthPercent(float top, float right, float bottom, float left);
    void SetBorderRadiusPercent(float radius);
    void SetBorderRadiusPercent(float upperLeft, float upperRight, float lowerLeft, float lowerRight);

    // Flex布局相关方法
    void SetFlexShrink(float shrink);
    void SetFlexGrow(float grow);
    void SetFlexBasis(float basis);

    // 背景相关方法
    void SetBackgroundColor(uint32_t color);

    // 布局权重和滚动条
    void SetLayoutWeight(uint32_t layoutWeight);
    void SetScrollBar(int32_t displayMode);

    // 相对布局相关方法
    void SetAlignRules(void *alignRules);
    void SetBarrier(void *barrier);
    void SetChainMode(int32_t axi, int32_t style);

    // ID相关方法
    void SetId(const char *id);
    const char *GetId();

    // 事件注册方法
    void RegisterOnClick(std::function<void()> onClick)
    {
        onClick_ = std::move(onClick);
        nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK, 0, nullptr);
    }

    void RegisterOnTouch(std::function<void(int32_t type, float x, float y)> onTouch)
    {
        onTouch_ = std::move(onTouch);
        nativeModule_->registerNodeEvent(handle_, NODE_TOUCH_EVENT, 0, nullptr);
    }

    void RegisterOnAppear(std::function<void()> onAppear)
    {
        onAppear_ = std::move(onAppear);
        nativeModule_->registerNodeEvent(handle_, NODE_EVENT_ON_APPEAR, 0, nullptr);
    }

    void RegisterOnDisappear(std::function<void()> onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
        nativeModule_->registerNodeEvent(handle_, NODE_EVENT_ON_DISAPPEAR, 0, nullptr);
    }

protected:
    static void NodeEventReceiver(ArkUI_NodeEvent *event);
    
    void ProcessNodeEvent(ArkUI_NodeEvent *event);
    
    virtual void OnNodeEvent(ArkUI_NodeEvent *event) {}
    
    void OnAddChild(const std::shared_ptr<ArkUIBaseNode> &child) override;
    
    void OnRemoveChild(const std::shared_ptr<ArkUIBaseNode> &child) override;
    
    void OnInsertChild(const std::shared_ptr<ArkUIBaseNode> &child, int32_t index) override;

private:
    std::function<void()> onClick_;                               // 点击事件回调函数
    std::function<void()> onDisappear_;                           // 消失事件回调函数
    std::function<void()> onAppear_;                              // 出现事件回调函数
    std::function<void(int32_t type, float x, float y)> onTouch_; // 触摸事件回调函数
    
    // 添加常量定义
    static constexpr float defaultMinSize = 0.0f;
    static constexpr float defaultMaxSize = 50.0f;
    static constexpr float defaultPercentReference = 1.0f;
    static constexpr int32_t defaultLayoutPosition = 20;
    static constexpr float constraintCopyMaxWidth = 5.0f;
};

} // namespace NativeModule

#endif // MYAPPLICATION_ARKUINODE_H