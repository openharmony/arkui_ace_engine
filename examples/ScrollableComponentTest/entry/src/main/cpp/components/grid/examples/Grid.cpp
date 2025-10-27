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

#include "components/grid/Grid1.h"

namespace ArkUICApiDemo {
void GridComponent::SetGridColumnsTemplate(const std::string& str)
{
    ArkUI_AttributeItem item = { .string = str.c_str() };
    _nodeAPI->setAttribute(_component, NODE_GRID_COLUMN_TEMPLATE, &item);
}
void GridComponent::SetGridRowsTemplate(const std::string& str)
{
    ArkUI_AttributeItem item = { .string = str.c_str() };
    _nodeAPI->setAttribute(_component, NODE_GRID_ROW_TEMPLATE, &item);
}
void GridComponent::SetGridColumnsGap(float val)
{
    ArkUI_NumberValue value[] = { { .f32 = val } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_GRID_COLUMN_GAP, &item);
}
void GridComponent::SetGridRowsGap(float val)
{
    ArkUI_NumberValue value[] = { { .f32 = val } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_GRID_ROW_GAP, &item);
}
void GridComponent::SetGridCachedCount(int32_t cachedCount)
{
    ArkUI_NumberValue value[] = { { .i32 = cachedCount } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_GRID_CACHED_COUNT, &item);
}
void GridComponent::SetScrollTo(float hOffset, float vOffset, const std::vector<int32_t>& optionalParams)
{
    auto value = new ArkUI_NumberValue[2 + static_cast<int32_t>(optionalParams.size())];
    value[0] = { .f32 = hOffset };
    value[1] = { .f32 = vOffset };
    for (int32_t i = 0; i < optionalParams.size(); i++) {
        value[2 + i] = { .i32 = optionalParams[i] };
    }
    ArkUI_AttributeItem item = { value, 2 + static_cast<int32_t>(optionalParams.size()) };
    _nodeAPI->setAttribute(_component, NODE_SCROLL_OFFSET, &item);
}
} // namespace ArkUICApiDemo