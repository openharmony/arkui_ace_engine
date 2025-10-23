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
 
#include "components/radio/Radio.h"

#include <cstdint>

namespace ArkUICApiDemo {
constexpr size_t ALLOW_SIZE_3 = 3;
void RadioComponent::SetChecked(const bool& isChecked)
{
    ArkUI_NumberValue value[] = { { .i32 = static_cast<int32_t>(isChecked) } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_RADIO_CHECKED, &item);
}
void RadioComponent::SetGroup(const std::string& group)
{
    ArkUI_AttributeItem item = { .string = group.c_str() };
    _nodeAPI->setAttribute(_component, NODE_RADIO_GROUP, &item);
}
void RadioComponent::SetStyled(const uint32_t* colorArray, size_t size)
{
    if (size == ALLOW_SIZE_3) {
        ArkUI_NumberValue radioStyle_value[] = { { .u32 = colorArray[0] }, { .u32 = colorArray[1] },
            { .u32 = colorArray[2] } };
        ArkUI_AttributeItem radioStyle_value_item = { radioStyle_value, ALLOW_SIZE_3 };
        _nodeAPI->setAttribute(_component, NODE_RADIO_STYLE, &radioStyle_value_item);
    }
}
void RadioComponent::SetValue(const std::string& value)
{
    ArkUI_AttributeItem item = { .string = value.c_str() };
    _nodeAPI->setAttribute(_component, NODE_RADIO_VALUE, &item);
}
} // namespace ArkUICApiDemo
