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
void RosenTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    CHECK_NULL_VOID(context);
    if (chainedEffect_) {
        chainedEffect_->OnAttach(context, activeTransition);
    }
}

void RosenTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    CHECK_NULL_VOID(context);
    if (chainedEffect_) {
        chainedEffect_->OnDetach(context);
    }
}

void RosenTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
    if (chainedEffect_) {
        chainedEffect_->UpdateSelfAndViewSize(selfRect, viewSize);
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
    AnimationUtils::AnimateWithCurrentCallback(*animationOption_, [func]() { func(); });
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
                nowRSEffect = AceType::MakeRefPtr<RosenRotationTransitionEffect>(rotateOption);
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

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectImpl<Modifier, PropertyType>::OnAttach(
    const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    CHECK_NULL_VOID(context);
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

    RosenTransitionEffect::OnAttach(context, activeTransition);
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectImpl<Modifier, PropertyType>::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    CHECK_NULL_VOID(context);
    // remove the modifier
    context->RemoveModifier(modifier_);
    property_.reset();
    modifier_.reset();

    RosenTransitionEffect::OnDetach(context);
}

RosenRotationTransitionEffect::RosenRotationTransitionEffect(const RotateOptions& rotate)
    : rotateX_(0.0f, 0.0f), rotateY_(0.0f, 0.0f), rotateZ_(0.0f, 0.0f)
{
    SetActiveValue(rotate);
}

void RosenRotationTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    renderContext_ = context;
    rotateX_.OnAttach(context, activeTransition);
    rotateY_.OnAttach(context, activeTransition);
    rotateZ_.OnAttach(context, activeTransition);
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenRotationTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    rotateX_.OnDetach(context);
    rotateY_.OnDetach(context);
    rotateZ_.OnDetach(context);
    RosenTransitionEffect::OnDetach(context);
}

void RosenRotationTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
    RosenTransitionEffect::UpdateSelfAndViewSize(selfRect, viewSize);
    auto context = renderContext_.Upgrade();
    CHECK_NULL_VOID(context);
    float xPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerX_, selfRect.Width());
    float yPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerY_, selfRect.Height());
    context->SetPivot(xPivot, yPivot);
}

void RosenRotationTransitionEffect::SetActiveValue(const RotateOptions& activeValue)
{
    float norm =
        static_cast<float>(std::sqrt(std::pow(activeValue.xDirection, 2) + std::pow(activeValue.yDirection, 2) +
                                     std::pow(activeValue.zDirection, 2)));
    if (NearZero(norm)) {
        norm = 1.0f;
    }
    // for rosen backend, the rotation angles in the x and y directions should be set to opposite angles
    rotateX_.SetActiveValue(-activeValue.angle * activeValue.xDirection / norm);
    rotateY_.SetActiveValue(-activeValue.angle * activeValue.yDirection / norm);
    rotateZ_.SetActiveValue(activeValue.angle * activeValue.zDirection / norm);
    centerX_ = activeValue.centerX;
    centerY_ = activeValue.centerY;
}

void RosenRotationTransitionEffect::OnAppear()
{
    RosenTransitionEffect::OnAppear();
    // rotateX, rotateY, rotateZ has no animation param, call OnAppear directly
    rotateX_.OnAppear();
    rotateY_.OnAppear();
    rotateZ_.OnAppear();
}

void RosenRotationTransitionEffect::OnDisappear(bool activeTransition)
{
    RosenTransitionEffect::OnDisappear(activeTransition);
    // rotateX, rotateY, rotateZ has no animation param, call OnDisappear directly
    rotateX_.OnDisappear(activeTransition);
    rotateY_.OnDisappear(activeTransition);
    rotateZ_.OnDisappear(activeTransition);
}

void RosenScaleTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    renderContext_ = context;
    scale_.OnAttach(context, activeTransition);
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenScaleTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    scale_.OnDetach(context);
    RosenTransitionEffect::OnDetach(context);
}

void RosenScaleTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
    RosenTransitionEffect::UpdateSelfAndViewSize(selfRect, viewSize);
    auto context = renderContext_.Upgrade();
    CHECK_NULL_VOID(context);
    float xPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerX_, selfRect.Width());
    float yPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerY_, selfRect.Height());
    context->SetPivot(xPivot, yPivot);
}

void RosenScaleTransitionEffect::SetActiveValue(const ScaleOptions& activeValue)
{
    scale_.SetActiveValue({ activeValue.xScale, activeValue.yScale });
    centerX_ = activeValue.centerX;
    centerY_ = activeValue.centerY;
}

void RosenScaleTransitionEffect::OnAppear()
{
    RosenTransitionEffect::OnAppear();
    scale_.OnAppear();
}

void RosenScaleTransitionEffect::OnDisappear(bool activeTransition)
{
    RosenTransitionEffect::OnDisappear(activeTransition);
    scale_.OnDisappear(activeTransition);
}

RosenTranslateTransitionEffect::RosenTranslateTransitionEffect(const TranslateOptions& option)
    : translate_({ 0.0f, 0.0f }, { 0.0f, 0.0f }), translateValue_(option)
{
    auto translateX = static_cast<float>(option.x.ConvertToPx());
    auto translateY = static_cast<float>(option.y.ConvertToPx());
    translate_.SetActiveValue({ translateX, translateY });
}

void RosenTranslateTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    translate_.OnAttach(context, activeTransition);
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenTranslateTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    translate_.OnDetach(context);
    RosenTransitionEffect::OnDetach(context);
}

void RosenTranslateTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
    if (translateValue_.x.Unit() != DimensionUnit::PERCENT && translateValue_.y.Unit() != DimensionUnit::PERCENT) {
        return;
    }
    float translateX = translateValue_.x.ConvertToPxWithSize(selfRect.Width());
    float translateY = translateValue_.y.ConvertToPxWithSize(selfRect.Height());
    translate_.SetActiveValue({ translateX, translateY });
}

void RosenTranslateTransitionEffect::SetActiveValue(const TranslateOptions& activeValue)
{
    translateValue_ = activeValue;
}

void RosenTranslateTransitionEffect::OnAppear()
{
    RosenTransitionEffect::OnAppear();
    translate_.OnAppear();
}

void RosenTranslateTransitionEffect::OnDisappear(bool activeTransition)
{
    RosenTransitionEffect::OnDisappear(activeTransition);
    translate_.OnDisappear(activeTransition);
}

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
    CHECK_NULL_VOID(context);
    // upon attach, we should only active the transitionIn_ branch if activeTransition is true.
    if (transitionIn_) {
        transitionIn_->OnAttach(context, activeTransition);
    }
    if (transitionOut_) {
        transitionOut_->OnAttach(context, false);
    }
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenAsymmetricTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
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

// update the frame rect of the transition node and size of view
void RosenAsymmetricTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
    RosenTransitionEffect::UpdateSelfAndViewSize(selfRect, viewSize);
    if (transitionIn_) {
        transitionIn_->UpdateSelfAndViewSize(selfRect, viewSize);
    }
    if (transitionOut_) {
        transitionOut_->UpdateSelfAndViewSize(selfRect, viewSize);
    }
}

void RosenMoveTransitionEffect::OnAttach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    translate_.OnAttach(context, activeTransition);
    RosenTransitionEffect::OnAttach(context, activeTransition);
}

void RosenMoveTransitionEffect::OnDetach(const RefPtr<RosenRenderContext>& context)
{
    translate_.OnDetach(context);
    RosenTransitionEffect::OnDetach(context);
}

void RosenMoveTransitionEffect::SetActiveValue(TransitionEdge activeValue)
{
    edge_ = activeValue;
}

void RosenMoveTransitionEffect::OnAppear()
{
    RosenTransitionEffect::OnAppear();
    translate_.OnAppear();
}

void RosenMoveTransitionEffect::OnDisappear(bool activeTransition)
{
    RosenTransitionEffect::OnDisappear(activeTransition);
    translate_.OnDisappear(activeTransition);
}

void RosenMoveTransitionEffect::UpdateSelfAndViewSize(const RectF& selfRect, const SizeF& viewSize)
{
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
    translate_.SetActiveValue(value);
    RosenTransitionEffect::UpdateSelfAndViewSize(selfRect, viewSize);
}

// Identity animation option, with duration 0 and delay 0.
static const auto identityOption = std::make_shared<AnimationOption>();
RosenIdentityTransitionEffect::RosenIdentityTransitionEffect() : RosenTransitionEffect()
{
    // Set animation option. And disable other options by overriding SetAnimationOption().
    RosenTransitionEffect::SetAnimationOption(identityOption);
}
} // namespace OHOS::Ace::NG
