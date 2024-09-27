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

#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/adapter/rosen_transition_effect_impl.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SLIDE_SWITCH_FRAME_PERCENT = 0.333f;
constexpr float SLIDE_SWITCH_SCALE = 0.85f;
const auto SLIDE_SWITCH_DEFAULT_CURVE = AceType::MakeRefPtr<CubicCurve>(0.24f, 0.0f, 0.50f, 1.0f);
constexpr int32_t SLIDE_SWITCH_DEFAULT_DURATION = 600;
const auto SLIDE_SWITCH_DEFAULT_OPTION =
    std::make_shared<AnimationOption>(SLIDE_SWITCH_DEFAULT_CURVE, SLIDE_SWITCH_DEFAULT_DURATION);
const std::vector<std::pair<float, Rosen::Vector2f>> SLIDE_SWITCH_KEYFRAMES = {
    { SLIDE_SWITCH_FRAME_PERCENT, Rosen::Vector2f { SLIDE_SWITCH_SCALE, SLIDE_SWITCH_SCALE } },
};
} // namespace

void RosenTransitionEffect::Attach(const RefPtr<RosenRenderContext>& context, bool activeTransition)
{
    OnAttach(context, activeTransition);
    if (chainedEffect_) {
        chainedEffect_->Attach(context, activeTransition);
    }
}

void RosenTransitionEffect::Detach(RosenRenderContext* context)
{
    OnDetach(context);
    if (chainedEffect_) {
        chainedEffect_->Detach(context);
    }
}

// Updates the transition context
void RosenTransitionEffect::UpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    OnUpdateTransitionContext(context, selfRect, viewSize);
    if (chainedEffect_) {
        chainedEffect_->UpdateTransitionContext(context, selfRect, viewSize);
    }
}

// Disappears with animation option if activeTransition is true
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

// Appears with animation option
void RosenTransitionEffect::Appear()
{
    ApplyAnimationOption([this]() {
        OnAppear();
        if (chainedEffect_) {
            chainedEffect_->Appear();
        }
    });
}

// Combines with another effect
void RosenTransitionEffect::CombineWith(const RefPtr<RosenTransitionEffect>& effect)
{
    chainedEffect_ = effect;
}

void RosenTransitionEffect::SetAnimationOption(const std::shared_ptr<AnimationOption>& option)
{
    animationOption_ = option;
}

// Applies the animation option if needed
void RosenTransitionEffect::ApplyAnimationOption(const std::function<void()>& func, bool withAnimation)
{
    // If there is no animation option or animation is disabled, just call func directly
    if (withAnimation == false || animationOption_ == nullptr) {
        func();
        return;
    }
    // Update animation option and reuse the finish callback (the callback in animationOption will be ignored)
    AnimationUtils::AnimateWithCurrentCallback(*animationOption_, [&func]() { func(); });
}

// Converts ChainedTransitionEffect to RosenTransitionEffect
RefPtr<RosenTransitionEffect> RosenTransitionEffect::ConvertToRosenTransitionEffect(
    const RefPtr<NG::ChainedTransitionEffect>& effect)
{
    RefPtr<RosenTransitionEffect> res;
    RefPtr<RosenTransitionEffect> tailRSEffect;
    RefPtr<ChainedTransitionEffect> currentEffect = effect;
    while (currentEffect) {
        RefPtr<RosenTransitionEffect> currentRSEffect;
        switch (currentEffect->GetType()) {
            case ChainedTransitionEffectType::IDENTITY: {
                currentRSEffect = AceType::MakeRefPtr<RosenIdentityTransitionEffect>();
                break;
            }
            case ChainedTransitionEffectType::OPACITY: {
                auto opacityEffect = AceType::DynamicCast<ChainedOpacityEffect>(currentEffect);
                auto opacity = opacityEffect->GetEffect();
                currentRSEffect = AceType::MakeRefPtr<RosenOpacityTransitionEffect>(1.0f, opacity);
                break;
            }
            case ChainedTransitionEffectType::MOVE: {
                auto moveEffect = AceType::DynamicCast<ChainedMoveEffect>(currentEffect);
                const auto& edge = moveEffect->GetEffect();
                currentRSEffect = AceType::MakeRefPtr<RosenMoveTransitionEffect>(edge);
                break;
            }
            case ChainedTransitionEffectType::ROTATE: {
                auto rotateEffect = AceType::DynamicCast<ChainedRotateEffect>(currentEffect);
                const auto& rotateOption = rotateEffect->GetEffect();
                currentRSEffect = AceType::MakeRefPtr<RosenRotation3DTransitionEffect>(rotateOption);
                break;
            }
            case ChainedTransitionEffectType::SCALE: {
                auto scaleEffect = AceType::DynamicCast<ChainedScaleEffect>(currentEffect);
                const auto& scaleOption = scaleEffect->GetEffect();
                // Scale z is not considered
                currentRSEffect = AceType::MakeRefPtr<RosenScaleTransitionEffect>(scaleOption);
                break;
            }
            case ChainedTransitionEffectType::TRANSLATE: {
                auto translateEffect = AceType::DynamicCast<ChainedTranslateEffect>(currentEffect);
                const auto& translateOption = translateEffect->GetEffect();
                currentRSEffect = AceType::MakeRefPtr<RosenTranslateTransitionEffect>(translateOption);
                break;
            }
            case ChainedTransitionEffectType::ASYMMETRIC: {
                auto asymmetricEffect = AceType::DynamicCast<ChainedAsymmetricEffect>(currentEffect);
                auto rsAppearTransition = ConvertToRosenTransitionEffect(asymmetricEffect->GetAppearEffect());
                auto rsDisappearTransition = ConvertToRosenTransitionEffect(asymmetricEffect->GetDisappearEffect());
                currentRSEffect =
                    AceType::MakeRefPtr<RosenAsymmetricTransitionEffect>(rsAppearTransition, rsDisappearTransition);
                break;
            }
            case ChainedTransitionEffectType::SLIDE_SWITCH: {
                currentRSEffect = AceType::MakeRefPtr<RosenSlideSwitchTransitionEffect>();
                break;
            }
            default: {
                return res;
            }
        }
        currentRSEffect->SetAnimationOption(currentEffect->GetAnimationOption());
        if (tailRSEffect) {
            tailRSEffect->CombineWith(currentRSEffect);
        } else {
            res = currentRSEffect;
        }
        tailRSEffect = currentRSEffect;
        currentEffect = currentEffect->GetNext();
    }
    return res;
}

// Update RosenTransitionEffect in place, return false if structure is not matched
bool RosenTransitionEffect::UpdateRosenTransitionEffect(
    const RefPtr<RosenTransitionEffect>& rosenEffect, const RefPtr<ChainedTransitionEffect>& chainedEffect)
{
    if (!chainedEffect && !rosenEffect) {
        return true;
    }
    auto nowEffect = chainedEffect;
    auto nowRSEffect = rosenEffect;
    while (nowEffect) {
        CHECK_NULL_RETURN(nowRSEffect, false);
        switch (nowEffect->GetType()) {
            case ChainedTransitionEffectType::IDENTITY: {
                if (!AceType::InstanceOf<RosenIdentityTransitionEffect>(nowRSEffect)) {
                    return false;
                }
                break;
            }
            case ChainedTransitionEffectType::OPACITY: {
                auto rosenOpacityEffect = AceType::DynamicCast<RosenOpacityTransitionEffect>(nowRSEffect);
                if (!rosenOpacityEffect) {
                    return false;
                }
                auto opacityEffect = AceType::DynamicCast<ChainedOpacityEffect>(nowEffect);
                rosenOpacityEffect->SetActiveValue(opacityEffect->GetEffect());
                break;
            }
            case ChainedTransitionEffectType::MOVE: {
                auto rosenMoveEffect = AceType::DynamicCast<RosenMoveTransitionEffect>(nowRSEffect);
                if (!rosenMoveEffect) {
                    return false;
                }
                auto moveEffect = AceType::DynamicCast<ChainedMoveEffect>(nowEffect);
                rosenMoveEffect->SetMoveEffect(moveEffect->GetEffect());
                break;
            }
            case ChainedTransitionEffectType::ROTATE: {
                auto rosenRotateEffect = AceType::DynamicCast<RosenRotation3DTransitionEffect>(nowRSEffect);
                if (!rosenRotateEffect) {
                    return false;
                }
                auto rotateEffect = AceType::DynamicCast<ChainedRotateEffect>(nowEffect);
                rosenRotateEffect->SetRotateEffect(rotateEffect->GetEffect());
                break;
            }
            case ChainedTransitionEffectType::SCALE: {
                auto rosenScaleEffect = AceType::DynamicCast<RosenScaleTransitionEffect>(nowRSEffect);
                if (!rosenScaleEffect) {
                    return false;
                }
                auto scaleEffect = AceType::DynamicCast<ChainedScaleEffect>(nowEffect);
                rosenScaleEffect->SetScaleEffect(scaleEffect->GetEffect());
                break;
            }
            case ChainedTransitionEffectType::TRANSLATE: {
                auto rosenTranslateEffect = AceType::DynamicCast<RosenTranslateTransitionEffect>(nowRSEffect);
                if (!rosenTranslateEffect) {
                    return false;
                }
                auto translateEffect = AceType::DynamicCast<ChainedTranslateEffect>(nowEffect);
                rosenTranslateEffect->SetTranslateEffect(translateEffect->GetEffect());
                break;
            }
            case ChainedTransitionEffectType::ASYMMETRIC: {
                auto rosenAsymmetricEffect = AceType::DynamicCast<RosenAsymmetricTransitionEffect>(nowRSEffect);
                if (!rosenAsymmetricEffect) {
                    return false;
                }
                auto asymmetricEffect = AceType::DynamicCast<ChainedAsymmetricEffect>(nowEffect);
                if (!UpdateRosenTransitionEffect(
                    rosenAsymmetricEffect->GetTransitionInEffect(), asymmetricEffect->GetAppearEffect())) {
                    return false;
                }
                if (!UpdateRosenTransitionEffect(
                    rosenAsymmetricEffect->GetTransitionOutEffect(), asymmetricEffect->GetDisappearEffect())) {
                    return false;
                }
                break;
            }
            case ChainedTransitionEffectType::SLIDE_SWITCH: {
                if (!AceType::InstanceOf<RosenSlideSwitchTransitionEffect>(nowRSEffect)) {
                    return false;
                }
                break;
            }
            default: {
                return false;
            }
        }
        nowRSEffect->SetAnimationOption(nowEffect->GetAnimationOption());
        nowRSEffect = nowRSEffect->chainedEffect_;
        nowEffect = nowEffect->GetNext();
    }
    // All effects are updated correctly
    return nowRSEffect == nullptr;
}

// Identity animation option, with duration 0 and delay 0.
static const auto identityOption = std::make_shared<AnimationOption>();
RosenIdentityTransitionEffect::RosenIdentityTransitionEffect() : RosenTransitionEffect()
{
    // Identity transition effect comes with default identity animation option.
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
    // record the current status
    isActive_ = activeTransition;
    if (modifier_ != nullptr) {
        property_->Set(activeTransition ? activeValue_ : identityValue_);
        return;
    }

    // create the property corresponding to current status
    property_ =
        std::make_shared<Rosen::RSAnimatableProperty<PropertyType>>(activeTransition ? activeValue_ : identityValue_);
    // create the modifier and attach it to the context
    modifier_ = std::make_shared<Modifier>(property_);
    context->AddModifier(modifier_);
}

template<typename Modifier, typename PropertyType>
void PropertyTransitionEffectTemplate<Modifier, PropertyType>::OnDetach(RosenRenderContext* context)
{
    // remove the modifier
    context->RemoveModifier(modifier_);
    property_.reset();
    modifier_.reset();
}

void RosenPivotTransitionEffect::SetPivot(const Dimension& centerX, const Dimension& centerY, const Dimension& centerZ)
{
    centerX_ = centerX;
    centerY_ = centerY;
    centerZ_ = centerZ;
}

RosenPivotTransitionEffect::RosenPivotTransitionEffect(
    const Dimension& centerX, const Dimension& centerY, const Dimension& centerZ)
    : centerX_(centerX), centerY_(centerY), centerZ_(centerZ)
{}

void RosenPivotTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    // calculate and set the pivot
    float xPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerX_, selfRect.Width());
    float yPivot = RosenRenderContext::ConvertDimensionToScaleBySize(centerY_, selfRect.Height());
    float zPivot = static_cast<float>(centerZ_.ConvertToPx());
    context->SetPivot(xPivot, yPivot, zPivot);
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

void RosenAsymmetricTransitionEffect::OnDetach(RosenRenderContext* context)
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

bool RosenAsymmetricTransitionEffect::HasDisappearTransition() const
{
    return transitionOut_ && transitionOut_->HasDisappearTransition();
}

void RosenTranslateTransitionEffect::OnUpdateTransitionContext(
    const RefPtr<RosenRenderContext>& context, const RectF& selfRect, const SizeF& viewSize)
{
    // translate dimension to pixel, and update active value
    float translateX = translateValue_.x.ConvertToPxWithSize(selfRect.Width());
    float translateY = translateValue_.y.ConvertToPxWithSize(selfRect.Height());
    float translateZ = translateValue_.z.ConvertToPx();
    std::get<InternalTranslateEffect>(effects_).SetActiveValue({ translateX, translateY });
    std::get<InternalTranslateZEffect>(effects_).SetActiveValue(translateZ);
}

void RosenTranslateTransitionEffect::SetTranslateEffect(const TranslateOptions& option)
{
    translateValue_ = option;
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
            if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
                value[0] = viewSize.Width() - selfRect.Left();
                break;
            }
            value[0] = -selfRect.Right();
            break;
        }
        case TransitionEdge::END: {
            if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
                value[0] = -selfRect.Right();
                break;
            }
            value[0] = viewSize.Width() - selfRect.Left();
            break;
        }
        default: {
            break;
        }
    }
    SetActiveValue(value);
}

void RosenMoveTransitionEffect::SetMoveEffect(TransitionEdge edge)
{
    edge_ = edge;
}

RosenAsyncMoveTransitionEffect ::RosenAsyncMoveTransitionEffect(TransitionEdge inEdge, TransitionEdge outEdge)
    : RosenAsymmetricTransitionEffect(
          MakeRefPtr<RosenMoveTransitionEffect>(inEdge), MakeRefPtr<RosenMoveTransitionEffect>(outEdge))
{}

RosenSlideTransitionEffect::RosenSlideTransitionEffect()
    : RosenSlideTransitionEffect(TransitionEdge::END, TransitionEdge::START)
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
    SetRotateEffect(options);
}

void RosenRotation3DTransitionEffect::SetRotateEffect(const RotateOptions& options)
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
    std::get<RosenPivotTransitionEffect>(effects_).SetPivot(options.centerX, options.centerY, options.centerZ);
}

RosenScaleTransitionEffect::RosenScaleTransitionEffect(const ScaleOptions& options)
{
    SetScaleEffect(options);
}

void RosenScaleTransitionEffect::SetScaleEffect(const ScaleOptions& options)
{
    std::get<InternalScaleEffect>(effects_).SetActiveValue({ options.xScale, options.yScale });
    std::get<RosenPivotTransitionEffect>(effects_).SetPivot(options.centerX, options.centerY);
}

template<>
RosenOpacityTransitionEffect::PropertyTransitionEffectTemplate() : identityValue_(1.0f), activeValue_(0.0f)
{}

template<>
InternalRotationXEffect::PropertyTransitionEffectTemplate() : identityValue_(0.0f), activeValue_(0.0f)
{}

template<>
InternalRotationYEffect::PropertyTransitionEffectTemplate() : identityValue_(0.0f), activeValue_(0.0f)
{}

template<>
InternalRotationZEffect::PropertyTransitionEffectTemplate() : identityValue_(0.0f), activeValue_(0.0f)
{}

template<>
InternalTranslateEffect::PropertyTransitionEffectTemplate() : identityValue_(0.0f, 0.0f), activeValue_(0.0f, 0.0f)
{}

template<>
InternalTranslateZEffect::PropertyTransitionEffectTemplate() : identityValue_(0.0f), activeValue_(0.0f)
{}

template<>
InternalScaleEffect::PropertyTransitionEffectTemplate() : identityValue_(1.0f, 1.0f), activeValue_(1.0f, 1.0f)
{}

RefPtr<RosenTransitionEffect> RosenTransitionEffect::CreateDefaultRosenTransitionEffect()
{
    return AceType::MakeRefPtr<RosenOpacityTransitionEffect>();
}

RosenSlideSwitchTransitionEffect::RosenSlideSwitchTransitionEffect()
{
    std::get<InternalScaleEffect>(effects_).SetKeyframes(SLIDE_SWITCH_KEYFRAMES);
    SetAnimationOption(SLIDE_SWITCH_DEFAULT_OPTION);
}

void RosenSlideSwitchTransitionEffect::SetAnimationOption(const std::shared_ptr<AnimationOption>& option)
{
    RosenTransitionEffect::SetAnimationOption(option ? option : SLIDE_SWITCH_DEFAULT_OPTION);
}
} // namespace OHOS::Ace::NG
