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

#ifndef MYAPPLICATION_ARKUITEXTNODE_H
#define MYAPPLICATION_ARKUITEXTNODE_H

#include "ArkUINode.h"
#include <string>

namespace NativeModule {

class ArkUIFlexNode : public ArkUINode {
public:
    ArkUIFlexNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_FLEX)) {}
    
    ~ArkUIFlexNode() override {}
    
    void SetFlexStyle(int32_t direct, int32_t flex, int32_t align, int32_t itemAlign, int32_t flexAlign)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {
            { .i32 = direct }, { .i32 = flex }, { .i32 = align }, { .i32 = itemAlign }, { .i32 = flexAlign }};
        ArkUI_AttributeItem item = { .value = value, 5 };
        nativeModule_->setAttribute(handle_, NODE_FLEX_OPTION, &item);
    }
};

class ArkUITextNode : public ArkUINode {
public:
    using ClickCallback = std::function<void()>;
    
    ArkUITextNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_TEXT))
    {
        // 注册自定义事件监听器
        nativeModule_->addNodeEventReceiver(handle_, OnTextEvent);
        // 声明自定义事件并转递自身作为自定义数据
        nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK_EVENT, 0, this);
    }
    
    void SetRegisterRefreshEvent()
    {
        assert(handle_);
        nativeModule_->registerNodeEvent(handle_, NODE_REFRESH_ON_OFFSET_CHANGE, 0, this);
        OH_LOG_INFO(LOG_APP, "SetRegisterRefreshEvent");
    }
    
    void SetRegisterVisibleAreaChangeEvent()
    {
        assert(handle_);
        nativeModule_->registerNodeEvent(handle_, NODE_EVENT_ON_VISIBLE_AREA_CHANGE, 0, this);
    }
    
    void SetVisibleAreaChangeRatio(float ratio)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .f32 = ratio }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_VISIBLE_AREA_CHANGE_RATIO, &item);
    }
    
    void SetUnregisterRefreshEvent()
    {
        assert(handle_);
        nativeModule_->unregisterNodeEvent(handle_, NODE_REFRESH_ON_OFFSET_CHANGE);
    }
    
    void SetFontSize(float fontSize)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .f32 = fontSize }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_FONT_SIZE, &item);
    }
    
    void SetFontColor(uint32_t color)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .u32 = color }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_FONT_COLOR, &item);
    }
    
    void SetTextContent(const std::string &content)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
        nativeModule_->setAttribute(handle_, NODE_TEXT_CONTENT, &item);
    }
    
    void SetTextAlign(ArkUI_TextAlignment align)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .i32 = align }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_TEXT_ALIGN, &item);
    }
    
    void SetOnClick(ClickCallback cb) { onClick_ = std::move(cb); }
    
    void SetRefreshOffset(float offset)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .f32 = offset }};
        ArkUI_AttributeItem item = { value, 1 };
        std::string log = "SetRefreshOffset: " + std::to_string(offset);
        OH_LOG_INFO(LOG_APP, "%{public}s", log.c_str());
        nativeModule_->setAttribute(handle_, NODE_REFRESH_OFFSET, &item);
    }

private:
    static void OnTextEvent(ArkUI_NodeEvent *event)
    {
        // 获取组件实例对象，调用相关实例方法
        auto textNode = reinterpret_cast<ArkUITextNode *>(OH_ArkUI_NodeEvent_GetUserData(event));
        auto type = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (type) {
            case NODE_ON_CLICK_EVENT:
                if (textNode->onClick_)
                    textNode->onClick_();
                break;
            case NODE_REFRESH_ON_OFFSET_CHANGE:
                textNode->OnOffsetChange();
                break;
            case NODE_EVENT_ON_VISIBLE_AREA_CHANGE:
                textNode->OnVisibleAreaChange();
            default:
                break;
        }
    }
    
    void OnOffsetChange() { OH_LOG_INFO(LOG_APP, "OnOffsetChange"); }
    
    void OnVisibleAreaChange() { OH_LOG_INFO(LOG_APP, "OnVisibleAreaChange"); }

    ClickCallback onClick_; // 点击回调函数
};

} // namespace NativeModule

#endif // MYAPPLICATION_ARKUITEXTNODE_H
