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

#include "components/text/Text.h"

namespace ArkUICApiDemo {

void TextComponent::SetFontSize(float fontSize)
{
    ArkUI_NumberValue value[] = { { .f32 = fontSize } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_FONT_SIZE, &item);
}
void TextComponent::SetFontColor(uint32_t color)
{
    ArkUI_NumberValue value[] = { { .u32 = color } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_FONT_COLOR, &item);
}
void TextComponent::SetTextContent(const std::string& content)
{
    ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
    _nodeAPI->setAttribute(_component, NODE_TEXT_CONTENT, &item);
}
void TextComponent::SetTextAlign(ArkUI_TextAlignment align)
{
    ArkUI_NumberValue value[] = { { .i32 = align } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_TEXT_ALIGN, &item);
}
} // namespace ArkUICApiDemo
