/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
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

#include "core/components/transform/transform_component.h"

#include "core/components/transform/transform_element.h"

namespace OHOS::Ace {

RefPtr<Element> TransformComponent::CreateElement()
{
    return AceType::MakeRefPtr<TransformElement>();
}

RefPtr<RenderNode> TransformComponent::CreateRenderNode()
{
    return RenderTransform::Create();
}

void TransformComponent::Translate(const Dimension& x, const Dimension& y)
{
    if (!NearEqual(x.Value(), 0.0)) {
        transformEffects_.emplace_back(TransformType::TRANSLATE_X, x);
    }
    if (!NearEqual(y.Value(), 0.0)) {
        transformEffects_.emplace_back(TransformType::TRANSLATE_Y, y);
    }
}

void TransformComponent::TranslateX(const Dimension& x)
{
    if (NearEqual(x.Value(), 0.0)) {
        return;
    }
    transformEffects_.emplace_back(TransformType::TRANSLATE_X, x);
}

void TransformComponent::TranslateY(const Dimension& y)
{
    if (NearEqual(y.Value(), 0.0)) {
        return;
    }
    transformEffects_.emplace_back(TransformType::TRANSLATE_Y, y);
}

void TransformComponent::Scale(float value)
{
    Scale(value, value);
}

void TransformComponent::Scale(float x, float y)
{
    if (!NearEqual(x, 1.0f)) {
        transformEffects_.emplace_back(TransformType::SCALE_X, Dimension(x));
    }
    if (!NearEqual(y, 1.0f)) {
        transformEffects_.emplace_back(TransformType::SCALE_Y, Dimension(y));
    }
}

void TransformComponent::ScaleX(float x)
{
    if (NearEqual(x, 1.0f)) {
        return;
    }
    transformEffects_.emplace_back(TransformType::SCALE_X, Dimension(x));
}

void TransformComponent::ScaleY(float y)
{
    if (NearEqual(y, 1.0f)) {
        return;
    }
    transformEffects_.emplace_back(TransformType::SCALE_Y, Dimension(y));
}

void TransformComponent::RotateX(float angle)
{
    if (NearZero(angle) || NearZero(fmod(angle, 360.0f))) {
        return;
    }
    // keep rotate direction same with quick app: angel --> -angle
    transformEffects_.emplace_back(TransformType::ROTATE_X, Dimension(-angle));
}

void TransformComponent::RotateY(float angle)
{
    if (NearZero(angle) || NearZero(fmod(angle, 360.0f))) {
        return;
    }
    // keep rotate direction same with quick app: angel --> -angle
    transformEffects_.emplace_back(TransformType::ROTATE_Y, Dimension(-angle));
}

void TransformComponent::RotateZ(float angle)
{
    if (NearZero(angle) || NearZero(fmod(angle, 360.0f))) {
        return;
    }
    transformEffects_.emplace_back(TransformType::ROTATE_Z, Dimension(angle));
}

} // namespace OHOS::Ace
