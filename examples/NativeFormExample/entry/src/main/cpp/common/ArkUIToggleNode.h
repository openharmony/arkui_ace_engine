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

#ifndef MYAPPLICATION_ARKUITOGGLENODE_H
#define MYAPPLICATION_ARKUITOGGLENODE_H

#include "ArkUINode.h"

#include <string>

namespace NativeModule {
class ArkUIToggleNode : public ArkUINode {
public:
    ArkUIToggleNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_TOGGLE)) {}
    // 属性接口封装。
    void SetIsOn(bool isOn)
    {
        ArkUI_NumberValue value[] = {{.i32 = isOn}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_TOGGLE_VALUE, &item);
    }
    void SetSelectedColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_TOGGLE_SELECTED_COLOR, &item);
    }
    void SetUnSelectedColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_TOGGLE_UNSELECTED_COLOR, &item);
    }
    void SetSwitchPointColor(uint32_t color)
    {
        ArkUI_NumberValue value[] = {{.u32 = color}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_TOGGLE_SWITCH_POINT_COLOR, &item);
    }
    
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUITOGGLENODE_H