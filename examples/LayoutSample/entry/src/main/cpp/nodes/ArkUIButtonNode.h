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

#ifndef LAYOUTSAMPLE_ARKUIBUTTONNODE_H
#define LAYOUTSAMPLE_ARKUIBUTTONNODE_H
#include "ArkUINode.h"

namespace NativeModule {

class ArkUIButtonNode : public ArkUINode {
public:
    using ClickCallback = std::function<void()>;

    ArkUIButtonNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_BUTTON))
    {
        // 注册自定义事件监听器
        nativeModule_->addNodeEventReceiver(handle_, OnClickEvent);
        // 声明自定义事件并转递自身作为自定义数据
        nativeModule_->registerNodeEvent(handle_, NODE_ON_CLICK_EVENT, 0, this);
    }

    ~ArkUIButtonNode() override {}
    
    void SetOnClick(ClickCallback cb) { onClick_ = std::move(cb); }
    
    void SetTextContent(const std::string &content)
    {
        assert(handle_);
        ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
        nativeModule_->setAttribute(handle_, NODE_BUTTON_LABEL, &item);
    }
    
    void SetButtonType(int32_t type)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .i32 = type }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_BUTTON_LABEL, &item);
    }
private:
    static void OnClickEvent(ArkUI_NodeEvent *event)
    {
        // 获取组件实例对象，调用相关实例方法
        auto buttonNode = reinterpret_cast<ArkUIButtonNode *>(OH_ArkUI_NodeEvent_GetUserData(event));
        auto type = OH_ArkUI_NodeEvent_GetEventType(event);
        switch (type) {
            case NODE_ON_CLICK_EVENT:
                if (buttonNode->onClick_)
                    buttonNode->onClick_();
                break;
            default:
                break;
        }
    }
    ClickCallback onClick_; // 点击回调函数
};

} // namespace NativeModule
#endif //LAYOUTSAMPLE_ARKUIBUTTONNODE_H
