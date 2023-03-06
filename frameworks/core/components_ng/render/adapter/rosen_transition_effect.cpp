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

#include "core/components_ng/render/adapter/rosen_transition_effect.h"

#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
void RosenTransitionEffect::OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition)
{
    CHECK_NULL_VOID(context);
    if (chainedEffect_) {
        chainedEffect_->OnAttach(context, activeTransition);
    }
}

void RosenTransitionEffect::OnDetach(RefPtr<RosenRenderContext> context)
{
    CHECK_NULL_VOID(context);
    if (chainedEffect_) {
        chainedEffect_->OnDetach(context);
    }
}

void RosenTransitionEffect::UpdateFrameSize(const SizeF& size)
{
    if (chainedEffect_) {
        chainedEffect_->UpdateFrameSize(size);
    }
}

void RosenTransitionEffect::OnAppear()
{
    if (chainedEffect_) {
        chainedEffect_->Appear();
    }
}

void RosenTransitionEffect::OnDisappear(bool activeTransition)
{
    if (chainedEffect_) {
        chainedEffect_->Disappear(activeTransition);
    }
}

void RosenTransitionEffect::Disappear(bool activeTransition)
{
    ApplyAnimationOption([this, activeTransition]() { OnDisappear(activeTransition); }, activeTransition);
}

void RosenTransitionEffect::Appear()
{
    ApplyAnimationOption([this]() { OnAppear(); });
}

void RosenTransitionEffect::CombineWith(const RefPtr<RosenTransitionEffect>& effect)
{
    chainedEffect_ = effect;
}

void RosenTransitionEffect::SetAnimationOption(const std::shared_ptr<AnimationOption>& option)
{
    animationOption = option;
}

void RosenTransitionEffect::ApplyAnimationOption(const std::function<void()>& func, bool withAnimation)
{
    // no animation option or animation disabled, just call func directly
    if (withAnimation == false || animationOption == nullptr) {
        func();
        return;
    }
    // kick off animation with animation option
    AnimationUtils::Animate(
        *animationOption, [func]() { func(); }, animationOption->GetOnFinishEvent());
}

RefPtr<RosenTransitionEffect> RosenTransitionEffect::ConvertToRosenTransitionEffect(
    const RefPtr<NG::ChainedTransitionEffect>& effect)
{
    if (!effect) {
        return nullptr;
    }
    RefPtr<RosenTransitionEffect> res;
    RefPtr<RosenTransitionEffect> tailEffect;
    RefPtr<ChainedTransitionEffect> nowEffect = effect;
    while (nowEffect) {
        RefPtr<RosenTransitionEffect> nowRSEffect;
        switch (nowEffect->GetType()) {
            case ChainedTransitionEffectType::OPACITY: {
                auto opacityEffect = AceType::DynamicCast<ChainedOpacityEffect>(nowEffect);
                auto opacity = opacityEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenOpacityTransitionEffect>(1.0f, opacity);
                break;
            }
            case ChainedTransitionEffectType::ROTATE: {
                auto rotateEffect = AceType::DynamicCast<ChainedRotateEffect>(nowEffect);
                // only z rotate is effective, no pivot
                const auto& rotateOption = rotateEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenRotationTransitionEffect>(0.0f, rotateOption.angle);
                break;
            }
            case ChainedTransitionEffectType::SCALE: {
                auto scaleEffect = AceType::DynamicCast<ChainedScaleEffect>(nowEffect);
                const auto& scaleOption = scaleEffect->GetEffect();
                // scale z is not considered
                nowRSEffect = AceType::MakeRefPtr<RosenScaleTransitionEffect>(
                    Rosen::Vector2f(1.0f, 1.0f), Rosen::Vector2f(scaleOption.xScale, scaleOption.yScale));
                break;
            }
            case ChainedTransitionEffectType::TRANSLATE: {
                auto translateEffect = AceType::DynamicCast<ChainedTranslateEffect>(nowEffect);
                const auto& translateOption = translateEffect->GetEffect();
                // not support percent
                auto xTranslate = static_cast<float>(translateOption.x.ConvertToPx());
                auto yTranslate = static_cast<float>(translateOption.y.ConvertToPx());
                nowRSEffect = AceType::MakeRefPtr<RosenTranslateTransitionEffect>(
                    Rosen::Vector2f(0.0f, 0.0f), Rosen::Vector2f(xTranslate, yTranslate));
                break;
            }
            case ChainedTransitionEffectType::ASYMMETRIC: {
                auto asymmetricEffect = AceType::DynamicCast<ChainedAsymmetricEffect>(nowEffect);
                auto rsAppearTransition = ConvertToRosenTransitionEffect(asymmetricEffect->GetAppearEffect());
                auto rsDisappearTransition = ConvertToRosenTransitionEffect(asymmetricEffect->GetDisappearEffect());
                nowRSEffect =
                    AceType::MakeRefPtr<RosenAsymmetricTransitionEffect>(rsAppearTransition, rsDisappearTransition);
                break;
            }
            default: {
                LOGW("now support effect type: %{public}d", static_cast<int>(nowEffect->GetType()));
                return res;
            }
        }
        nowRSEffect->SetAnimationOption(nowEffect->GetAnimationOption());
        if (tailEffect) {
            tailEffect->CombineWith(nowRSEffect);
        } else {
            res = nowRSEffect;
        }
        tailEffect = nowRSEffect;
        nowEffect = nowEffect->GetNext();
    }
    return res;
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectImpl<Modifier, PropertyType>::OnAttach(
    RefPtr<RosenRenderContext> context, bool activeTransition)
{
    CHECK_NULL_VOID(context);
    if (modifier_ != nullptr) {
        LOGE("PropertyTransitionEffectImpl::OnAttach modifier_ is not null");
        return;
    }

    isActive_ = activeTransition;
    property_ =
        std::make_shared<Rosen::RSAnimatableProperty<PropertyType>>(activeTransition ? activeValue_ : identityValue_);
    modifier_ = std::make_shared<Modifier>(property_);
    context->AddModifier(modifier_);

    RosenTransitionEffect::OnAttach(context, activeTransition);
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectImpl<Modifier, PropertyType>::OnDetach(RefPtr<RosenRenderContext> context)
{
    CHECK_NULL_VOID(context);
    context->RemoveModifier(modifier_);
    property_.reset();
    modifier_.reset();

    RosenTransitionEffect::OnDetach(context);
}

void RosenAsymmetricTransitionEffect::SetTransitionInEffect(const RefPtr<RosenTransitionEffect>& transitionIn)
{
    transitionIn_ = transitionIn;
}

void RosenAsymmetricTransitionEffect::SetTransitionOutEffect(const RefPtr<RosenTransitionEffect>& transitionOut)
{
    transitionOut_ = transitionOut;
}

void RosenAsymmetricTransitionEffect::OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition)
{
    CHECK_NULL_VOID(context);
    // upon attach, we should only the active the transition in effect
    if (transitionIn_) {
        transitionIn_->OnAttach(context, activeTransition);
    }
    if (transitionOut_) {
        transitionOut_->OnAttach(context, false);
    }
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenAsymmetricTransitionEffect::OnDetach(RefPtr<RosenRenderContext> context)
{
    CHECK_NULL_VOID(context);
    if (transitionIn_) {
        transitionIn_->OnDetach(context);
    }
    if (transitionOut_) {
        transitionOut_->OnDetach(context);
    }
    RosenTransitionEffect::OnDetach(context);
}

void RosenAsymmetricTransitionEffect::OnAppear()
{
    RosenTransitionEffect::OnAppear();
    // upon node appear & reappear, active all transitions
    if (transitionIn_ != nullptr) {
        transitionIn_->Appear();
    }
    if (transitionOut_ != nullptr) {
        transitionOut_->Appear();
    }
}

void RosenAsymmetricTransitionEffect::OnDisappear(bool activeTransition)
{
    RosenTransitionEffect::OnDisappear(activeTransition);
    // upon node disappear, we should only active the transition out transition
    if (transitionIn_) {
        transitionIn_->Disappear(false);
    }
    if (transitionOut_) {
        transitionOut_->Disappear(activeTransition);
    }
}

void RosenAsymmetricTransitionEffect::UpdateFrameSize(const SizeF& size)
{
    RosenTransitionEffect::UpdateFrameSize(size);
    if (transitionIn_) {
        transitionIn_->UpdateFrameSize(size);
    }
    if (transitionOut_) {
        transitionOut_->UpdateFrameSize(size);
    }
}

Rosen::Vector2f RosenSlideTransitionEffect::GetTranslateValue(TransitionEdge edge, const SizeF& size)
{
    switch (edge) {
        case TransitionEdge::START:
            return { -size.Width(), 0.0f };
        case TransitionEdge::END:
            return { size.Width(), 0.0f };
        case TransitionEdge::TOP:
            return { 0.0f, -size.Height() };
        case TransitionEdge::BOTTOM:
            return { 0.0f, size.Height() };
        default:
            return { 0.0f, 0.0f };
    }
}

void RosenSlideTransitionEffect::UpdateFrameSize(const SizeF& size)
{
    DynamicCast<RosenTranslateTransitionEffect>(transitionIn_)
        ->SetActiveValue(GetTranslateValue(transitionInEdge_, size));
    DynamicCast<RosenTranslateTransitionEffect>(transitionOut_)
        ->SetActiveValue(GetTranslateValue(transitionOutEdge_, size));
}
} // namespace OHOS::Ace::NG
