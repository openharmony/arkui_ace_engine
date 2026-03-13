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

#ifndef MYAPPLICATION_ARKUIBUTTONNODE_H
#define MYAPPLICATION_ARKUIBUTTONNODE_H

#include "ArkUINode.h"

#include <string>

namespace NativeModule {
class ArkUIButtonNode : public ArkUINode {
public:
    ArkUIButtonNode()
        : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_BUTTON)) {}
    // 按钮属性接口封装。
    void SetButtonLabel(const std::string &label)
    {
        ArkUI_AttributeItem item = {nullptr, 0, label.c_str()};
        nativeModule_->setAttribute(handle_, NODE_BUTTON_LABEL, &item);
    }
    void SetButtonType(ArkUI_ButtonType type)
    {
        ArkUI_NumberValue value[] = {{.i32 = type}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_BUTTON_TYPE, &item);
    }
    void SetMinFontScale(float scale)
    {
        ArkUI_NumberValue value[] = {{.f32 = scale}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_BUTTON_MIN_FONT_SCALE, &item);
    }
    void SetMaxFontScale(float scale)
    {
        ArkUI_NumberValue value[] = {{.f32 = scale}};
        ArkUI_AttributeItem item = {value, 1};
        nativeModule_->setAttribute(handle_, NODE_BUTTON_MAX_FONT_SCALE, &item);
    }
    
    
};
} // namespace NativeModule

#endif // MYAPPLICATION_ARKUIBUTTONNODE_H