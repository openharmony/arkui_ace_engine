/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LIGHT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LIGHT_H

#include "base/geometry/animatable_float.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "base/memory/ace_type.h"
#include "core/pipeline/pipeline_context.h"
#include "model_position.h"

namespace OHOS::Ace::NG {
enum ModelLightType {
    INVALID_LIGHT = 0,
    DIRECTIONAL_LIGHT = 1,
    POINT_LIGHT = 2,
    SPOT_LIGHT = 3
};

class ModelLight : public virtual AceType {
    DECLARE_ACE_TYPE(ModelLight, AceType)
public:
    ModelLight(ModelLightType type, const Vec3& color, const AnimatableFloat& intensity,
        bool shadow, const ModelPosition& position, const Quaternion& rotation)
        : type_(type), shadow_(shadow), color_(color), intensity_(intensity),
        position_(position), rotation_(rotation) {};
    ~ModelLight() override = default;

    using RenderNodeAnimationCallback = std::function<void()>;
    void SetContextAndCallback(
        const WeakPtr<PipelineBase>& context,
        RenderNodeAnimationCallback&& callback)
    {
        intensity_.SetContextAndCallback(context, std::forward<RenderNodeAnimationCallback>(callback));
        color_.SetContextAndCallbacks(context, std::forward<RenderNodeAnimationCallback>(callback));
        position_.SetContextAndCallbacks(context, std::forward<RenderNodeAnimationCallback>(callback));
    }

    void SetLightType(ModelLightType type)
    {
        type_ = type;
    }

    void SetColor(const OHOS::Ace::Vec3& color)
    {
        color_ = color;
    }

    void SetIntensity(const OHOS::Ace::AnimatableFloat& intensity)
    {
        intensity_ = intensity;
    }

    void SetLightShadow(bool shadow)
    {
        shadow_ = shadow;
    }

    void SetPosition(const ModelPosition& position)
    {
        position_.SetPosition(position.GetPosition());
        position_.SetDistance(position.GetDistance());
        position_.SetIsAngular(position.GetIsAngular());
    }

    void SetRotation(const Quaternion& rotation)
    {
        rotation_ = rotation;
    }

    ModelLightType GetLightType() const
    {
        return type_;
    }

    const Vec3& GetLightColor() const
    {
        return color_;
    }

    const AnimatableFloat& GetLightIntensity() const
    {
        return intensity_;
    }

    bool GetLightShadow() const
    {
        return shadow_;
    }

    const ModelPosition& GetPosition() const
    {
        return position_;
    }

    const Quaternion& GetRotation() const
    {
        return rotation_;
    }

    void Print() {}

private:
    ModelLightType type_ = ModelLightType::DIRECTIONAL_LIGHT;
    bool shadow_ = false;
    Vec3 color_ { 1.0f, 1.0f, 1.0f };
    AnimatableFloat intensity_ { 10.0f };
    ModelPosition position_;
    Quaternion rotation_;
};
} // OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_LIGHT_H
