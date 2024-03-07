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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_IMPL_H

#include "modifier/rs_property.h"
#include "modifier/rs_property_modifier.h"

#include "core/components_ng/render/adapter/rosen_transition_effect.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
// Identity transition effect, do nothing and execute immediately.
class RosenIdentityTransitionEffect final : public RosenTransitionEffect {
public:
    RosenIdentityTransitionEffect();
    ~RosenIdentityTransitionEffect() override = default;

    // Identity transition effect ignores external animation option.
    void SetAnimationOption(const std::shared_ptr<AnimationOption>& option) override {}
    bool HasDisappearTransition() const override
    {
        return false;
    }

private:
    DECLARE_ACE_TYPE(RosenIdentityTransitionEffect, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenIdentityTransitionEffect);
};

// Template class for single property transition effect, applying identity and active value to target property/modifier.
template<typename Modifier, typename PropertyType>
class PropertyTransitionEffectTemplate : public RosenTransitionEffect {
public:
    PropertyTransitionEffectTemplate() : RosenTransitionEffect() {}
    PropertyTransitionEffectTemplate(PropertyType identityProperty, PropertyType activeValue)
        : RosenTransitionEffect(), identityValue_(identityProperty), activeValue_(activeValue)
    {}
    ~PropertyTransitionEffectTemplate() override = default;

    void SetIdentityValue(PropertyType identityValue);
    void SetActiveValue(PropertyType activeValue);

    void SetKeyframes(const std::vector<std::pair<float, PropertyType>>& keyframes)
    {
        keyframes_ = keyframes;
    }

protected:
    void OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition) override;
    void OnDetach(RosenRenderContext* context) override;
    void OnAppear() override
    {
        isActive_ = false;
        if (keyframes_.empty()) {
            property_->Set(identityValue_);
            return;
        }
        for (auto it = keyframes_.begin(); it != keyframes_.end(); ++it) {
            AnimationUtils::AddKeyFrame(it->first, [this, &it]() { property_->Set(it->second); });
        }
        AnimationUtils::AddKeyFrame(1.0f, [this]() { property_->Set(identityValue_); });
    }
    void OnDisappear(bool activeTransition) override
    {
        if (!activeTransition) {
            return;
        }
        isActive_ = true;
        if (keyframes_.empty()) {
            property_->Set(activeValue_);
            return;
        }
        // PLANNING: maybe we need to reverse the keyframes in disappearing animation.
        for (auto it = keyframes_.begin(); it != keyframes_.end(); ++it) {
            AnimationUtils::AddKeyFrame(it->first, [this, &it]() { property_->Set(it->second); });
        }
        AnimationUtils::AddKeyFrame(1.0f, [this]() { property_->Set(activeValue_); });
    }

private:
    std::shared_ptr<Modifier> modifier_;
    std::shared_ptr<Rosen::RSAnimatableProperty<PropertyType>> property_;
    PropertyType identityValue_ {};
    PropertyType activeValue_ {};
    std::vector<std::pair<float, PropertyType>> keyframes_;
    bool isActive_ = false;

    DECLARE_ACE_TYPE(PropertyTransitionEffectTemplate, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(PropertyTransitionEffectTemplate);
};

using RosenOpacityTransitionEffect = PropertyTransitionEffectTemplate<Rosen::RSAlphaModifier, float>;
template<>
RosenOpacityTransitionEffect::PropertyTransitionEffectTemplate();

// Set pivot during transition effect.
class RosenPivotTransitionEffect final : public RosenTransitionEffect {
public:
    RosenPivotTransitionEffect() = default;
    RosenPivotTransitionEffect(const Dimension& centerX, const Dimension& centerY,
        const Dimension& centerZ = Dimension(0.0));
    ~RosenPivotTransitionEffect() override = default;

    void SetPivot(const Dimension& centerX, const Dimension& centerY, const Dimension& centerZ = Dimension(0.0,
        DimensionUnit::VP));

private:
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override;

    Dimension centerX_ { 0.5_pct };
    Dimension centerY_ { 0.5_pct };
    Dimension centerZ_ { 0.0_vp };
    DECLARE_ACE_TYPE(RosenPivotTransitionEffect, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenPivotTransitionEffect);
};

// Asymmetric transition effect, support in and out chaining with different transition effects.
class RosenAsymmetricTransitionEffect : public RosenTransitionEffect {
public:
    RosenAsymmetricTransitionEffect() : RosenTransitionEffect() {}
    RosenAsymmetricTransitionEffect(
        const RefPtr<RosenTransitionEffect>& transitionIn, const RefPtr<RosenTransitionEffect>& transitionOut);
    ~RosenAsymmetricTransitionEffect() override = default;

    void SetTransitionInEffect(const RefPtr<RosenTransitionEffect>& transitionIn);
    void SetTransitionOutEffect(const RefPtr<RosenTransitionEffect>& transitionOut);
    RefPtr<RosenTransitionEffect> GetTransitionInEffect()
    {
        return transitionIn_;
    }
    RefPtr<RosenTransitionEffect> GetTransitionOutEffect()
    {
        return transitionOut_;
    }
    bool HasDisappearTransition() const override;

protected:
    void OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition) override;
    void OnDetach(RosenRenderContext* context) override;
    void OnAppear() override;
    void OnDisappear(bool activeTransition) override;
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override;

    RefPtr<RosenTransitionEffect> transitionIn_;
    RefPtr<RosenTransitionEffect> transitionOut_;

private:
    DECLARE_ACE_TYPE(RosenAsymmetricTransitionEffect, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenAsymmetricTransitionEffect);
};

using InternalTranslateEffect = PropertyTransitionEffectTemplate<Rosen::RSTranslateModifier, Rosen::Vector2f>;
template<>
InternalTranslateEffect::PropertyTransitionEffectTemplate();

// Move in and out to (same) screen edge.
class RosenMoveTransitionEffect final : public InternalTranslateEffect {
public:
    explicit RosenMoveTransitionEffect(TransitionEdge transitionEdge) : edge_(transitionEdge) {}
    ~RosenMoveTransitionEffect() override = default;

    void SetMoveEffect(TransitionEdge edge);

private:
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override;
    TransitionEdge edge_;
    DECLARE_ACE_TYPE(RosenMoveTransitionEffect, InternalTranslateEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenMoveTransitionEffect);
};

// Move in and out to different screen edge.
class RosenAsyncMoveTransitionEffect final : public RosenAsymmetricTransitionEffect {
public:
    RosenAsyncMoveTransitionEffect(TransitionEdge inEdge, TransitionEdge outEdge);
    ~RosenAsyncMoveTransitionEffect() override = default;

private:
    DECLARE_ACE_TYPE(RosenAsyncMoveTransitionEffect, RosenAsymmetricTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenAsyncMoveTransitionEffect);
};

// Move in and out to different direction, by node size.
class RosenSlideTransitionEffect final : public RosenAsymmetricTransitionEffect {
public:
    RosenSlideTransitionEffect();
    RosenSlideTransitionEffect(TransitionEdge inEdge, TransitionEdge outEdge);
    ~RosenSlideTransitionEffect() override = default;

private:
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override;
    static Rosen::Vector2f GetTranslateValue(TransitionEdge edge, const RectF& rect);
    TransitionEdge inEdge_;
    TransitionEdge outEdge_;
    DECLARE_ACE_TYPE(RosenSlideTransitionEffect, RosenAsymmetricTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenSlideTransitionEffect);
};

// Helper class for compositing transition effects.
template<typename... effects>
class RosenCompositeTransitionEffect : public RosenTransitionEffect {
public:
    RosenCompositeTransitionEffect() = default;
    ~RosenCompositeTransitionEffect() override = default;

protected:
    std::tuple<effects...> effects_;

    void OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition) override
    {
        std::apply([&](auto&&... effect) { (effect.Attach(context, activeTransition), ...); }, effects_);
    }
    void OnDetach(RosenRenderContext* context) override
    {
        std::apply([&](auto&&... effect) { (effect.Detach(context), ...); }, effects_);
    }
    void OnAppear() override
    {
        std::apply([&](auto&&... effect) { (effect.Appear(), ...); }, effects_);
    }
    void OnDisappear(bool activeTransition) override
    {
        std::apply([&](auto&&... effect) { (effect.Disappear(activeTransition), ...); }, effects_);
    }
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override
    {
        std::apply(
            [&](auto&&... effect) { (effect.UpdateTransitionContext(context, selfRect, viewSize), ...); }, effects_);
    }

private:
    DECLARE_ACE_TYPE(RosenCompositeTransitionEffect, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenCompositeTransitionEffect);
};

using InternalTranslateZEffect = PropertyTransitionEffectTemplate<Rosen::RSTranslateZModifier, float>;
template<>
InternalTranslateZEffect::PropertyTransitionEffectTemplate();
// 3D Translate effect that accepts Dimension.
class RosenTranslateTransitionEffect final
    : public RosenCompositeTransitionEffect<InternalTranslateEffect, InternalTranslateZEffect> {
public:
    explicit RosenTranslateTransitionEffect(const TranslateOptions& option) : translateValue_(option) {}
    ~RosenTranslateTransitionEffect() override = default;

    void SetTranslateEffect(const TranslateOptions& option);

private:
    void OnUpdateTransitionContext(
        const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize) override;
    TranslateOptions translateValue_;
    DECLARE_ACE_TYPE(RosenTranslateTransitionEffect, RosenCompositeTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenTranslateTransitionEffect);
};

// 3D rotation composite effect with pivot.
using InternalRotationXEffect = PropertyTransitionEffectTemplate<Rosen::RSRotationXModifier, float>;
using InternalRotationYEffect = PropertyTransitionEffectTemplate<Rosen::RSRotationYModifier, float>;
using InternalRotationZEffect = PropertyTransitionEffectTemplate<Rosen::RSRotationModifier, float>;
template<>
InternalRotationXEffect::PropertyTransitionEffectTemplate();
template<>
InternalRotationYEffect::PropertyTransitionEffectTemplate();
template<>
InternalRotationZEffect::PropertyTransitionEffectTemplate();
class RosenRotation3DTransitionEffect final
    : public RosenCompositeTransitionEffect<InternalRotationXEffect, InternalRotationYEffect, InternalRotationZEffect,
          RosenPivotTransitionEffect> {
public:
    explicit RosenRotation3DTransitionEffect(const RotateOptions& options);
    ~RosenRotation3DTransitionEffect() override = default;

    void SetRotateEffect(const RotateOptions& options);

private:
    DECLARE_ACE_TYPE(RosenRotation3DTransitionEffect, RosenCompositeTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenRotation3DTransitionEffect);
};

using InternalScaleEffect = PropertyTransitionEffectTemplate<Rosen::RSScaleModifier, Rosen::Vector2f>;
template<>
InternalScaleEffect::PropertyTransitionEffectTemplate();
// 2D scale composite effect with pivot.
class RosenScaleTransitionEffect final
    : public RosenCompositeTransitionEffect<InternalScaleEffect, RosenPivotTransitionEffect> {
public:
    explicit RosenScaleTransitionEffect(const ScaleOptions& options);
    ~RosenScaleTransitionEffect() override = default;

    void SetScaleEffect(const ScaleOptions& options);

private:
    DECLARE_ACE_TYPE(RosenScaleTransitionEffect, RosenCompositeTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenScaleTransitionEffect);
};

class RosenSlideSwitchTransitionEffect final
    : public RosenCompositeTransitionEffect<RosenSlideTransitionEffect, InternalScaleEffect> {
public:
    RosenSlideSwitchTransitionEffect();
    ~RosenSlideSwitchTransitionEffect() override = default;
    void SetAnimationOption(const std::shared_ptr<AnimationOption>& option) override;

private:
    DECLARE_ACE_TYPE(RosenSlideSwitchTransitionEffect, RosenCompositeTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenSlideSwitchTransitionEffect);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_IMPL_H
