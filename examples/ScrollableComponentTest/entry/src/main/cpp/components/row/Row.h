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

#ifndef ARKUI_CAPI_DEMO_ROW_COMPONENT_H
#define ARKUI_CAPI_DEMO_ROW_COMPONENT_H

#include "components/component.h"
namespace ArkUICApiDemo {
class RowComponent : public Component {
public:
    RowComponent() : Component(ARKUI_NODE_ROW) {}
    RowComponent(ArkUI_NodeHandle handle) : Component(handle) {}

    void SetAlignItems(int32_t verticalAlign)
    {
        ArkUI_NumberValue value[] = { { .i32 = verticalAlign } };
        ArkUI_AttributeItem item = { value, 1 };
        _nodeAPI->setAttribute(_component, NODE_ROW_ALIGN_ITEMS, &item);
    }
    void SetJustifyContent(int32_t flexAlign)
    {
        ArkUI_NumberValue value[] = { { .i32 = flexAlign } };
        ArkUI_AttributeItem item = { value, 1 };
        _nodeAPI->setAttribute(_component, NODE_ROW_JUSTIFY_CONTENT, &item);
    }
};
} // namespace ArkUICApiDemo

#endif // ARKUI_CAPI_DEMO_ROW_COMPONENT_H
