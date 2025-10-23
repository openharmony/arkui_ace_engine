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

#include "components/image/Image.h"

#include <cstdint>

namespace ArkUICApiDemo {

int32_t ImageComponent::SetImageSrc(const std::string& content)
{
    ArkUI_AttributeItem item = { nullptr, 0, content.c_str() };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_SRC, &item);
}
int32_t ImageComponent::SetImageSrc(ArkUI_DrawableDescriptor* descriptors)
{
    ArkUI_AttributeItem item = { .object = descriptors };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_SRC, &item);
}
int32_t ImageComponent::SetObjectFit(const int32_t objectFit)
{
    ArkUI_NumberValue value[] = { { .i32 = objectFit } };
    ArkUI_AttributeItem item = { value, 1 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_OBJECT_FIT, &item);
}
int32_t ImageComponent::SetResizable(const float left, const float top, const float right, const float bottom)
{
    ArkUI_NumberValue value[] = { { .f32 = left }, { .f32 = top }, { .f32 = right }, { .f32 = bottom } };
    ArkUI_AttributeItem item = { value, 4 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_RESIZABLE, &item);
}
int32_t ImageComponent::SetImageDraggable(bool isDraggable)
{
    ArkUI_NumberValue value[] = { { .i32 = isDraggable } };
    ArkUI_AttributeItem item = { value, 1 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_DRAGGABLE, &item);
}
int32_t ImageComponent::SetImageRenderMode(int32_t renderMode)
{
    ArkUI_NumberValue value[] = { { .i32 = renderMode } };
    ArkUI_AttributeItem item = { value, 1 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_RENDER_MODE, &item);
}
int32_t ImageComponent::SetImageFitOriginalSize(int32_t fitOriginalSize)
{
    ArkUI_NumberValue value[] = { { .i32 = fitOriginalSize } };
    ArkUI_AttributeItem item = { value, 1 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_FIT_ORIGINAL_SIZE, &item);
}
int32_t ImageComponent::SetImageFillColor(uint32_t color)
{
    ArkUI_NumberValue value[] = { { .u32 = color } };
    ArkUI_AttributeItem item = { value, 1 };
    return _nodeAPI->setAttribute(_component, NODE_IMAGE_FILL_COLOR, &item);
}
int32_t ImageComponent::SetGeometryTransition(int32_t type, const std::string& id)
{
    ArkUI_NumberValue value[] = { { .i32 = type } };
    ArkUI_AttributeItem item = { value, 1, id.c_str() };
    return _nodeAPI->setAttribute(_component, NODE_GEOMETRY_TRANSITION, &item);
}
} // namespace ArkUICApiDemo
