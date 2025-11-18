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

#ifndef MYAPPLICATION_ARKUIFLEXNODE_H
#define MYAPPLICATION_ARKUIFLEXNODE_H

#include "ArkUINode.h"

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

} // namespace NativeModule

#endif