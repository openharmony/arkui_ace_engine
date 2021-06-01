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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_TRANSFORM_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_TRANSFORM_COMPONENT_H

#include "base/geometry/dimension_offset.h"
#include "base/geometry/matrix4.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/transform/render_transform.h"
#include "core/pipeline/base/component_group.h"
#include "core/pipeline/base/sole_child_component.h"

namespace OHOS::Ace {

inline constexpr int32_t INDEX_TWO = 2;
inline constexpr int32_t INDEX_THREE = 3;
inline constexpr float PERSPECTIVE = 0.0005f;
inline constexpr Dimension HALF_PERCENT = 0.5_pct;

class ACE_EXPORT TransformComponent : public SoleChildComponent {
    DECLARE_ACE_TYPE(TransformComponent, SoleChildComponent)

public:
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;
    void Translate(const Dimension& x, const Dimension& y);
    void TranslateX(const Dimension& x);
    void TranslateY(const Dimension& y);

    void Scale(float value);
    void Scale(float x, float y);
    void ScaleX(float x);
    void ScaleY(float y);

    void RotateX(float angle);
    void RotateY(float angle);
    void RotateZ(float angle);

    const DimensionOffset& GetOriginDimension() const
    {
        return originDimension_;
    }

    void SetOriginDimension(const DimensionOffset& origin)
    {
        originDimension_ = origin;
    }

    const std::vector<std::pair<TransformType, Dimension>>& GetTransformEffects() const
    {
        return transformEffects_;
    }

    const Matrix4& GetTransform() const
    {
        return transform_;
    }

    void SetTransform(const Matrix4& transform)
    {
        transform_ = transform;
    }

    void ResetTransform()
    {
        transform_ = Matrix4::CreateIdentity();
        transformEffects_.clear();
    }

    void SetClickSpringEffectType(ClickSpringEffectType type)
    {
        clickSpringEffectType_ = type;
    }

    ClickSpringEffectType GetClickSpringEffectType() const
    {
        return clickSpringEffectType_;
    }

    void SetTransitionEffect(TransitionEffect transitionEffect)
    {
        transitionEffect_ = transitionEffect;
    }

    TransitionEffect GetTransitionEffect() const
    {
        return transitionEffect_;
    }

    void SetShadow(const Shadow& shadow)
    {
        shadow_ = shadow;
    }

    const Shadow& GetShadow() const
    {
        return shadow_;
    }

private:
    Matrix4 transform_;
    std::vector<std::pair<TransformType, Dimension>> transformEffects_;
    DimensionOffset originDimension_ = DimensionOffset(HALF_PERCENT, HALF_PERCENT);
    ClickSpringEffectType clickSpringEffectType_ = ClickSpringEffectType::NONE;
    TransitionEffect transitionEffect_ = TransitionEffect::NONE;
    Shadow shadow_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TRANSFORM_TRANSFORM_COMPONENT_H
