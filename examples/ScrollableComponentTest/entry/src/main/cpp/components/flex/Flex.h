/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef ARKUI_CAPI_DEMO_FLEX_COMPONENT_H
#define ARKUI_CAPI_DEMO_FLEX_COMPONENT_H

#include <arkui/native_node.h>
#include "components/component.h"

namespace ArkUICApiDemo {
class FlexComponent : public Component {
public:
    FlexComponent() : Component(ARKUI_NODE_COLUMN) {}
    explicit FlexComponent(ArkUI_NodeHandle handle) : Component(handle) {}
    
    void SetOptions(int32_t *options)
    {
    ArkUI_NumberValue options_value[] = {
        {.i32 = options[0]}, {.i32 = options[1]}, {.i32 = options[2]}, {.i32 = options[3]}, {.i32 = options[4]}};
    ArkUI_AttributeItem options_item = {options_value, sizeof(options_value) / sizeof(ArkUI_NumberValue)};
    _nodeAPI->setAttribute(_component, NODE_FLEX_OPTION, &options_item);
    }
};
} // namespace ArkUICApiDemo

#endif // ARKUI_CAPI_DEMO_FLEX_COMPONENT_H
