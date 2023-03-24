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
#include "core/components_ng/render/adapter/rosen_transition_effect_impl.h"
#include "core/components_ng/render/animation_utils.h"

namespace OHOS::Ace::NG {
void RosenTransitionEffect::Attach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    OnAttach(context, activeTransition);
    if (chainedEffect_) {
        chainedEffect_->Attach(context, activeTransition);
    }
}

void RosenTransitionEffect::Detach(const RefPtr<RosenRenderContext>& context)
{
    OnDetach(context);
    if (chainedEffect_) {
        chainedEffect_->Detach(context);
    }
}

void RosenTransitionEffect::UpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    OnUpdateTransitionContext(context, selfRect, viewSize);
    if (chainedEffect_) {
        chainedEffect_->UpdateTransitionContext(context, selfRect, viewSize);
    }
}

void RosenTransitionEffect::Disappear(bool activeTransition)
{
    ApplyAnimationOption(
        [this, activeTransition]() {
            OnDisappear(activeTransition);
            if (chainedEffect_) {
                chainedEffect_->Disappear(activeTransition);
            }
        },
        activeTransition);
}

void RosenTransitionEffect::Appear()
{
    ApplyAnimationOption([this]() {
        OnAppear();
        if (chainedEffect_) {
            chainedEffect_->Appear();
        }
    });
}

void RosenTransitionEffect::CombineWith(const RefPtr<RosenTransitionEffect>& effect)
{
    chainedEffect_ = effect;
}

void RosenTransitionEffect::SetAnimationOption(const std::shared_ptr<AnimationOption>& option)
{
    animationOption_ = option;
}

void RosenTransitionEffect::ApplyAnimationOption(const std::function<void()>& func, bool withAnimation)
{
    // no animation option or animation disabled, just call func directly
    if (withAnimation == false || animationOption_ == nullptr) {
        func();
        return;
    }
    // update animation option and reuse the finish callback (the callback in animationOption will be ignored)
    AnimationUtils::AnimateWithCurrentCallback(*animationOption_, [&func]() { func(); });
}

RefPtr<RosenTransitionEffect> RosenTransitionEffect::ConvertToRosenTransitionEffect(
    const RefPtr<NG::ChainedTransitionEffect>& effect)
{
    RefPtr<RosenTransitionEffect> res;
    RefPtr<RosenTransitionEffect> tailEffect;
    RefPtr<ChainedTransitionEffect> nowEffect = effect;
    while (nowEffect) {
        RefPtr<RosenTransitionEffect> nowRSEffect;
        switch (nowEffect->GetType()) {
            case ChainedTransitionEffectType::IDENTITY: {
                nowRSEffect = AceType::MakeRefPtr<RosenIdentityTransitionEffect>();
                break;
            }
            case ChainedTransitionEffectType::OPACITY: {
                auto opacityEffect = AceType::DynamicCast<ChainedOpacityEffect>(nowEffect);
                auto opacity = opacityEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenOpacityTransitionEffect>(1.0f, opacity);
                break;
            }
            case ChainedTransitionEffectType::MOVE: {
                auto moveEffect = AceType::DynamicCast<ChainedMoveEffect>(nowEffect);
                const auto& edge = moveEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenMoveTransitionEffect>(edge);
                break;
            }
            case ChainedTransitionEffectType::ROTATE: {
                auto rotateEffect = AceType::DynamicCast<ChainedRotateEffect>(nowEffect);
                const auto& rotateOption = rotateEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenRotation3DTransitionEffect>(rotateOption);
                break;
            }
            case ChainedTransitionEffectType::SCALE: {
                auto scaleEffect = AceType::DynamicCast<ChainedScaleEffect>(nowEffect);
                const auto& scaleOption = scaleEffect->GetEffect();
                // scale z is not considered
                nowRSEffect = AceType::MakeRefPtr<RosenScaleTransitionEffect>(scaleOption);
                break;
            }
            case ChainedTransitionEffectType::TRANSLATE: {
                auto translateEffect = AceType::DynamicCast<ChainedTranslateEffect>(nowEffect);
                const auto& translateOption = translateEffect->GetEffect();
                nowRSEffect = AceType::MakeRefPtr<RosenTranslateTransitionEffect>(translateOption);
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
                LOGW("not support effect type: %{public}d", static_cast<int>(nowEffect->GetType()));
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

// Identity animation option, with duration 0 and delay 0.
static const auto identityOption = std::make_shared<AnimationOption>();
RosenIdentityTransitionEffect::RosenIdentityTransitionEffect() : RosenTransitionEffect()
{
    // Set animation option. And disable other options by overriding SetAnimationOption().
    RosenTransitionEffect::SetAnimationOption(identityOption);
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectTemplate<Modifier, PropertyType>::SetIdentityValue(PropertyType identityValue)
{
    identityValue_ = identityValue;
    if (!isActive_) {
        property_->Set(identityValue_);
    }
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectTemplate<Modifier, PropertyType>::SetActiveValue(PropertyType activeValue)
{
    activeValue_ = activeValue;
    if (isActive_) {
        property_->Set(activeValue_);
    }
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectTemplate<Modifier, PropertyType>::OnAttach(
    const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    if (modifier_ != nullptr) {
        LOGE("PropertyTransitionEffectImpl::OnAttach modifier_ is not null");
        return;
    }

    // record the current status
    isActive_ = activeTransition;
    // create the property corresponding to current status
    property_ =
        std::make_shared<Rosen::RSAnimatableProperty<PropertyType>>(activeTransition ? activeValue_ : identityValue_);
    // create the modifier and attach it to the context
    modifier_ = std::make_shared<Modifier>(property_);
    context->AddModifier(modifier_);
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectTemplate<Modifier, PropertyType>::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    // remove the modifier
    context->RemoveModifier(modifier_);
    property_.reset();
    modifier_.reset();
}

void RosenPivotTransitionEffect::SetPivot(Dimension centerX, Dimension centerY)
{
    centerX_ = centerX;
    centerY_ = centerY;
}

RosenPivotTransitionEffect::RosenPivotTransitionEffect(const Dimension& centerX, const Dimension& centerY)
    : centerX_(centerX), centerY_(centerY)
{}

void RosenPivotTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    // calculate and set the pivot
    float xPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerX_, selfRect.Width());
    float yPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerY_, selfRect.Height());
    context->SetPivot(xPivot, yPivot);
}

RosenAsymmetricTransitionEffect::RosenAsymmetricTransitionEffect(
    const RefPtr<RosenTransitionEffect>& transitionIn, const RefPtr<RosenTransitionEffect>& transitionOut)
    : transitionIn_(transitionIn), transitionOut_(transitionOut)
{}

void RosenAsymmetricTransitionEffect::SetTransitionInEffect(const RefPtr<RosenTransitionEffect>& transitionIn)
{
    transitionIn_ = transitionIn;
}

void RosenAsymmetricTransitionEffect::SetTransitionOutEffect(const RefPtr<RosenTransitionEffect>& transitionOut)
{
    transitionOut_ = transitionOut;
}

void RosenAsymmetricTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    // upon attach, we should only trigger the transitionIn_ branch if activeTransition is true.
    if (transitionIn_) {
        transitionIn_->Attach(context, activeTransition);
    }
    if (transitionOut_) {
        transitionOut_->Attach(context, false);
    }
}

void RosenAsymmetricTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    if (transitionIn_) {
        transitionIn_->Detach(context);
    }
    if (transitionOut_) {
        transitionOut_->Detach(context);
    }
}

void RosenAsymmetricTransitionEffect::OnAppear()
{
    // upon node appear & reappear, we should trigger all transitions
    if (transitionIn_ != nullptr) {
        transitionIn_->Appear();
    }
    if (transitionOut_ != nullptr) {
        transitionOut_->Appear();
    }
}

void RosenAsymmetricTransitionEffect::OnDisappear(bool activeTransition)
{
    // upon node disappear, we should only trigger the transitionOut branch
    if (transitionIn_) {
        transitionIn_->Disappear(false);
    }
    if (transitionOut_) {
        transitionOut_->Disappear(activeTransition);
    }
}

void RosenAsymmetricTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    if (transitionIn_) {
        transitionIn_->UpdateTransitionContext(context, selfRect, viewSize);
    }
    if (transitionOut_) {
        transitionOut_->UpdateTransitionContext(context, selfRect, viewSize);
    }
}

void RosenTranslateTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    // translate dimension to pixel, and update active value
    float translateX = translateValue_.x.ConvertToPxWithSize(selfRect.Width());
    float translateY = translateValue_.y.ConvertToPxWithSize(selfRect.Height());
    SetActiveValue({ translateX, translateY });
}

void RosenMoveTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    // move node to the edge of the view
    Rosen::Vector2f value { 0.0f, 0.0f };
    switch (edge_) {
        case TransitionEdge::TOP: {
            value[1] = -selfRect.Bottom();
            break;
        }
        case TransitionEdge::BOTTOM: {
            value[1] = viewSize.Height() - selfRect.Top();
            break;
        }
        case TransitionEdge::START: {
            value[0] = -selfRect.Right();
            break;
        }
        case TransitionEdge::END: {
            value[0] = viewSize.Width() - selfRect.Left();
            break;
        }
        default: {
            LOGW("invalid Edge");
        }
    }
    SetActiveValue(value);
}

RosenAsyncMoveTransitionEffect ::RosenAsyncMoveTransitionEffect(TransitionEdge inEdge, TransitionEdge outEdge)
    : RosenAsymmetricTransitionEffect(
          MakeRefPtr<RosenMoveTransitionEffect>(inEdge), MakeRefPtr<RosenMoveTransitionEffect>(outEdge))
{}

RosenSlideTransitionEffect::RosenSlideTransitionEffect(TransitionEdge inEdge, TransitionEdge outEdge)
    : RosenAsymmetricTransitionEffect(MakeRefPtr<InternalTranslateEffect>(), MakeRefPtr<InternalTranslateEffect>()),
      inEdge_(inEdge), outEdge_(outEdge)
{}

void RosenSlideTransitionEffect ::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    DynamicCast<InternalTranslateEffect>(transitionIn_)->SetActiveValue(GetTranslateValue(inEdge_, selfRect));
    DynamicCast<InternalTranslateEffect>(transitionOut_)->SetActiveValue(GetTranslateValue(outEdge_, selfRect));
}

// convert the transition edge to the corresponding translate value
Rosen::Vector2f RosenSlideTransitionEffect::GetTranslateValue(TransitionEdge edge, const RectF& rect)
{
    switch (edge) {
        case TransitionEdge::START:
            return { -rect.Width(), 0.0f };
        case TransitionEdge::END:
            return { rect.Width(), 0.0f };
        case TransitionEdge::TOP:
            return { 0.0f, -rect.Height() };
        case TransitionEdge::BOTTOM:
            return { 0.0f, rect.Height() };
        default:
            return { 0.0f, 0.0f };
    }
}

RosenRotation3DTransitionEffect::RosenRotation3DTransitionEffect(const RotateOptions& options)
    : RosenCompositeTransitionEffect()
{
    auto norm = static_cast<float>(
        std::sqrt(std::pow(options.xDirection, 2) + std::pow(options.yDirection, 2) + std::pow(options.zDirection, 2)));
    if (NearZero(norm)) {
        norm = 1.0f;
    }
    // for rosen backend, the rotation angles in the x and y directions should be set to opposite angles
    std::get<InternalRotationXEffect>(effects_).SetActiveValue(-options.angle * options.xDirection / norm);
    std::get<InternalRotationYEffect>(effects_).SetActiveValue(-options.angle * options.yDirection / norm);
    std::get<InternalRotationZEffect>(effects_).SetActiveValue(options.angle * options.zDirection / norm);
    std::get<RosenPivotTransitionEffect>(effects_).SetPivot(options.centerX, options.centerY);
}

RosenScaleTransitionEffect::RosenScaleTransitionEffect(const ScaleOptions& options)
{
    std::get<InternalScaleEffect>(effects_).SetActiveValue({ options.xScale, options.yScale });
    std::get<RosenPivotTransitionEffect>(effects_).SetPivot(options.centerX, options.centerY);
}
} // namespace OHOS::Ace::NG
