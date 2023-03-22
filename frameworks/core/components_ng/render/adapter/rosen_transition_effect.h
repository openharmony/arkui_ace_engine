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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H

#include "modifier/rs_property.h"
#include "modifier/rs_property_modifier.h"

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;

// Base class for transition effect, providing basic functions for transition effect.
class RosenTransitionEffect : public AceType {
    DECLARE_ACE_TYPE(RosenTransitionEffect, AceType);

public:
    RosenTransitionEffect() = default;
    ~RosenTransitionEffect() override = default;

    virtual void OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition);
    virtual void OnDetach(RefPtr<RosenRenderContext> context);
    virtual void UpdateFrameSize(const SizeF& size);

    void Appear();
    void Disappear(bool activeTransition = true);

    // Chain with another transition effect, the chained effect will be applied after this effect.
    void CombineWith(const RefPtr<RosenTransitionEffect>& effect);
    virtual void SetAnimationOption(const std::shared_ptr<AnimationOption>& option);

    static RefPtr<RosenTransitionEffect> ConvertToRosenTransitionEffect(const RefPtr<ChainedTransitionEffect>& effect);

protected:
    virtual void OnAppear();
    virtual void OnDisappear(bool activeTransition);

    void ApplyAnimationOption(const std::function<void()>& func, bool withAnimation = true);

private:
    RefPtr<RosenTransitionEffect> chainedEffect_ = nullptr;
    std::shared_ptr<AnimationOption> animationOption_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(RosenTransitionEffect);
};

// Template class for property transition effect, applying identity and active value to target property/modifier.
template<typename Modifier, typename PropertyType>
class PropertyTransitionEffectImpl final : public RosenTransitionEffect {
    DECLARE_ACE_TYPE(PropertyTransitionEffectImpl, RosenTransitionEffect);

public:
    explicit PropertyTransitionEffectImpl() : RosenTransitionEffect() {}
    explicit PropertyTransitionEffectImpl(PropertyType identityProperty, PropertyType activeValue)
        : RosenTransitionEffect(), identityValue_(identityProperty), activeValue_(activeValue)
    {}

    void OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition) override;
    void OnDetach(RefPtr<RosenRenderContext> context) override;

    void SetIdentityValue(PropertyType identityValue)
    {
        identityValue_ = identityValue;
        if (!isActive_) {
            Identity();
        }
    }

    void SetActiveValue(PropertyType activeValue)
    {
        activeValue_ = activeValue;
        if (isActive_) {
            Active();
        }
    }

protected:
    void OnAppear() override
    {
        RosenTransitionEffect::OnAppear();
        Identity();
    }
    void OnDisappear(bool activeTransition) override
    {
        RosenTransitionEffect::OnDisappear(activeTransition);
        if (activeTransition) {
            Active();
        }
    }

    void Identity()
    {
        property_->Set(identityValue_);
        isActive_ = false;
    }

    void Active()
    {
        property_->Set(activeValue_);
        isActive_ = true;
    }

private:
    std::shared_ptr<Modifier> modifier_;
    std::shared_ptr<Rosen::RSAnimatableProperty<PropertyType>> property_;
    PropertyType identityValue_ {};
    PropertyType activeValue_ {};
    bool isActive_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(PropertyTransitionEffectImpl);
};

using RosenOpacityTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSAlphaModifier, float>;
using RosenTranslateTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSTranslateModifier, Rosen::Vector2f>;
using RosenRotationTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSRotationModifier, float>;
using RosenRotationXTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSRotationXModifier, float>;
using RosenRotationYTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSRotationYModifier, float>;
using RosenScaleTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSScaleModifier, Rosen::Vector2f>;

// Asymmetric transition effect, support in and out chaining with different transition effect.
class RosenAsymmetricTransitionEffect : public RosenTransitionEffect {
    DECLARE_ACE_TYPE(RosenAsymmetricTransitionEffect, RosenTransitionEffect);

public:
    RosenAsymmetricTransitionEffect() : RosenTransitionEffect() {}
    RosenAsymmetricTransitionEffect(
        const RefPtr<RosenTransitionEffect>& transitionIn, const RefPtr<RosenTransitionEffect>& transitionOut)
        : RosenTransitionEffect(), transitionIn_(transitionIn), transitionOut_(transitionOut)
    {}

    void OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition) override;
    void OnDetach(RefPtr<RosenRenderContext> context) override;

    void SetTransitionInEffect(const RefPtr<RosenTransitionEffect>& transitionIn);
    void SetTransitionOutEffect(const RefPtr<RosenTransitionEffect>& transitionOut);

protected:
    void OnAppear() override;
    void OnDisappear(bool activeTransition) override;
    void UpdateFrameSize(const SizeF& size) override;

    RefPtr<RosenTransitionEffect> transitionIn_;
    RefPtr<RosenTransitionEffect> transitionOut_;
};

// Slide transition effect, slide in and out by frame size.
class RosenSlideTransitionEffect final : public RosenAsymmetricTransitionEffect {
    DECLARE_ACE_TYPE(RosenSlideTransitionEffect, RosenAsymmetricTransitionEffect);

public:
    RosenSlideTransitionEffect(TransitionEdge transitionInEdge, TransitionEdge transitionOutEdge)
        : RosenAsymmetricTransitionEffect(
              MakeRefPtr<RosenTranslateTransitionEffect>(), MakeRefPtr<RosenTranslateTransitionEffect>()),
          transitionInEdge_(transitionInEdge), transitionOutEdge_(transitionOutEdge)
    {}

    void UpdateFrameSize(const SizeF& size) override;

private:
    static Rosen::Vector2f GetTranslateValue(TransitionEdge edge, const SizeF& size);
    TransitionEdge transitionInEdge_;
    TransitionEdge transitionOutEdge_;
    ACE_DISALLOW_COPY_AND_MOVE(RosenSlideTransitionEffect);
};

// Identity transition effect, do noting and execute immediately.
class RosenIdentityTransition final : public RosenTransitionEffect {
    DECLARE_ACE_TYPE(RosenIdentityTransition, RosenTransitionEffect);
    ACE_DISALLOW_COPY_AND_MOVE(RosenIdentityTransition);

public:
    RosenIdentityTransition();
    void SetAnimationOption(const std::shared_ptr<AnimationOption>& option) override {}
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H
