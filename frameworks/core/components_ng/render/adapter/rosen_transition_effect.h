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

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/animation_option.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;

class RosenTransitionEffect : public AceType {
    DECLARE_ACE_TYPE(RosenTransitionEffect, AceType);

public:
    RosenTransitionEffect();
    ~RosenTransitionEffect() override = default;

    virtual void OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition);
    virtual void OnDetach(RefPtr<RosenRenderContext> context);
    virtual void UpdateFrameSize(const SizeF& size);

    void Appear();
    void Disappear(bool activeTransition = true);

    void CombineWith(const RefPtr<RosenTransitionEffect>& effect);
    void SetAnimationOption(const std::shared_ptr<AnimationOption>& option);

protected:
    virtual void OnAppear();
    virtual void OnDisappear(bool activeTransition);

    void ApplyAnimationOption(const std::function<void()>& func, bool withAnimation = true);

    RefPtr<RosenTransitionEffect> chainedEffect_ = nullptr;

private:
    std::shared_ptr<AnimationOption> animationOption = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(RosenTransitionEffect);
};

template<typename Modifier, typename PropertyType>
class PropertyTransitionEffectImpl final : public RosenTransitionEffect {
    DECLARE_ACE_TYPE(PropertyTransitionEffectImpl, RosenTransitionEffect);

public:
    explicit PropertyTransitionEffectImpl() : RosenTransitionEffect(), identityValue_({}), activeValue_({}) {}
    explicit PropertyTransitionEffectImpl(PropertyType identityProperty, PropertyType activeValue)
        : RosenTransitionEffect(), identityValue_(identityProperty), activeValue_(activeValue)
    {}

    void OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition) override
    {
        CHECK_NULL_VOID(context);
        if (modifier_ != nullptr) {
            LOGE("PropertyTransitionEffectImpl::OnAttach modifier_ is not null");
            return;
        }

        isActive_ = activeTransition;
        property_ = std::make_shared<Rosen::RSAnimatableProperty<PropertyType>>(
            activeTransition ? activeValue_ : identityValue_);
        modifier_ = std::make_shared<Modifier>(property_);
        context->AddModifier(modifier_);

        RosenTransitionEffect::OnAttach(context, activeTransition);
    }

    void OnDetach(RefPtr<RosenRenderContext> context) override
    {
        CHECK_NULL_VOID(context);
        context->RemoveModifier(modifier_);
        property_.reset();
        modifier_.reset();

        RosenTransitionEffect::OnDetach(context);
    }

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
        Active();
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
    PropertyType identityValue_;
    PropertyType activeValue_;
    bool isActive_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(PropertyTransitionEffectImpl);
};

using OpacityTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSAlphaModifier, Rosen::Vector2f>;
using TranslateTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSTranslateModifier, Rosen::Vector2f>;
using RotationTransitionEffect = PropertyTransitionEffectImpl<Rosen::RSRotationModifier, float>;

class AsymmetricTransitionEffect : public RosenTransitionEffect {
    DECLARE_ACE_TYPE(AsymmetricTransitionEffect, RosenTransitionEffect);

public:
    AsymmetricTransitionEffect() : RosenTransitionEffect() {}
    AsymmetricTransitionEffect(
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

class SlideTransitionEffect : public AsymmetricTransitionEffect {
    DECLARE_ACE_TYPE(SlideTransitionEffect, AsymmetricTransitionEffect);

public:
    SlideTransitionEffect()
        : AsymmetricTransitionEffect(MakeRefPtr<TranslateTransitionEffect>(), MakeRefPtr<TranslateTransitionEffect>())
    {}

    void UpdateFrameSize(const SizeF& size) override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_TRANSITION_EFFECT_H