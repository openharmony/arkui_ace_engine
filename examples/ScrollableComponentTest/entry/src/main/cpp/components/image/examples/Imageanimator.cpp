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

#include "components/image/Imageanimator.h"

namespace ArkUICApiDemo {
void ImageAnimatorComponent::SetState(int32_t state)
{
    ArkUI_NumberValue value[] = { { .i32 = state } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_STATE, &item);
}

void ImageAnimatorComponent::SetIteration(int32_t iteration)
{
    ArkUI_NumberValue value[] = { { .i32 = iteration } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_ITERATION, &item);
}

void ImageAnimatorComponent::SetImage(std::vector<ArkUI_ImageAnimatorFrameInfo*>& vector)
{
    ArkUI_AttributeItem item = { .size = static_cast<int32_t>(vector.size()), .object = _cast<void*>(vector.data()) };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_IMAGES, &item);
}

void ImageAnimatorComponent::SetFixedSize(int32_t fixedSize)
{
    ArkUI_NumberValue value[] = { { .i32 = fixedSize } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_FIXED_SIZE, &item);
}

void ImageAnimatorComponent::SetReverse(int32_t reverse)
{
    ArkUI_NumberValue value[] = { { .i32 = reverse } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_REVERSE, &item);
}

void ImageAnimatorComponent::SetFillMode(int32_t mode)
{
    ArkUI_NumberValue value[] = { { .i32 = mode } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_FILL_MODE, &item);
}

void ImageAnimatorComponent::SetDuration(int32_t duration)
{
    ArkUI_NumberValue value[] = { { .i32 = duration } };
    ArkUI_AttributeItem item = { value, 1 };
    _nodeAPI->setAttribute(_component, NODE_IMAGE_ANIMATOR_DURATION, &item);
}
} // namespace ArkUICApiDemo
