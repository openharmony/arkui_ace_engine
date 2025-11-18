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

#ifndef MYAPPLICATION_ARKUIROWNODE_H
#define MYAPPLICATION_ARKUIROWNODE_H

#include "ArkUINode.h"

namespace NativeModule {

class ArkUIRowNode : public ArkUINode {
public:
    ArkUIRowNode() : ArkUINode((NativeModuleInstance::GetInstance()->GetNativeNodeAPI())->createNode(ARKUI_NODE_ROW)) {}
    
    ~ArkUIRowNode() override {}
    
    void setJustifyContent(int32_t align)
    {
        assert(handle_);
        ArkUI_NumberValue value[] = {{ .i32 = align }};
        ArkUI_AttributeItem item = { value, 1 };
        nativeModule_->setAttribute(handle_, NODE_ROW_JUSTIFY_CONTENT, &item);
    }
};

} // namespace NativeModule

#endif