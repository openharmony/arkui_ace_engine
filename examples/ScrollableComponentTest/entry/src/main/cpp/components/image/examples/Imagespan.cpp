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

#include "components/image/Imagespan.h"

namespace ArkUICApiDemo {

int32_t ImageSpanComponent::SetImageSpanSrc(const std::string& content)
{
    ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_SPAN_SRC, &item);
}
int32_t ImageSpanComponent::SetImageSpanSrc(ArkUI_DrawableDescriptor* descriptors)
{
    ArkUI_AttributeItem item = { .object = descriptors };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_SPAN_SRC, &item);
}
int32_t ImageSpanComponent::SetImageSpanAlt(const std::string& alt)
{
    ArkUI_AttributeItem item = { nullptr, 0, alt.c_str() };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_SPAN_ALT, &item);
}
} // namespace ArkUICApiDemo
