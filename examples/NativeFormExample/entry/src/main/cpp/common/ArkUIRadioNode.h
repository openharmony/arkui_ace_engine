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

#ifndef MYAPPLICATION_ARKUIRADIONODE_H
#define MYAPPLICATION_ARKUIRADIONODE_H

#include "ArkUINode.h"

#include <cstdint>
#include <string>

namespace NativeModule {
class ArkUIRadioNode : public ArkUINode {
public:
    ArkUIRadioNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_RADIO)) {}
    // 属性接口封装。
    void SetIsOn(bool isOn)
    {
        ArkUI_NumberValue value[] = {{.i32 = isOn}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_RADIO_CHECKED, &item);
    }
    void SetRadioStyle(uint32_t selectedBgColor, uint32_t unSelectedBorderColor, uint32_t selectedIndicatorColor)
    {
        ArkUI_NumberValue value[] = {{.u32 = selectedBgColor}, {.u32 = unSelectedBorderColor}, {.u32 = selectedIndicatorColor}};
        ArkUI_AttributeItem item = {value, 3};
        nativeModule_->setAttribute(handle_, NODE_RADIO_STYLE, &item);
    }
    void SetRadioValue(const std::string &value)
    {
        ArkUI_AttributeItem item = {nullptr, 0, value.c_str()};
        nativeModule_->setAttribute(handle_, NODE_RADIO_VALUE, &item);
    }
    void SetRadioGroup(const std::string &group)
    {
        ArkUI_AttributeItem item = {nullptr, 0, group.c_str()};
        nativeModule_->setAttribute(handle_, NODE_RADIO_GROUP, &item);
    }
    
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUIRADIONODE_H