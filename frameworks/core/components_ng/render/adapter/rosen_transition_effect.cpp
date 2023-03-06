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

void AsymmetricTransitionEffect::SetTransitionInEffect(const RefPtr<RosenTransitionEffect>& transitionIn)
{
    transitionIn_ = transitionIn;
}

void AsymmetricTransitionEffect::SetTransitionOutEffect(const RefPtr<RosenTransitionEffect>& transitionOut)
{
    transitionOut_ = transitionOut;
}

void AsymmetricTransitionEffect::OnAttach(RefPtr<RosenRenderContext> context, bool activeTransition)
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

void AsymmetricTransitionEffect::OnDetach(RefPtr<RosenRenderContext> context)
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

void RosenTransitionEffect::ApplyAnimationOption(const std::function<void()>& func, bool withAnimation)
{
    // no animation option or animation disabled, just call func directly
    if (withAnimation || animationOption == nullptr) {
        func();
        return;
    }
    // kick off animation with animation option
    AnimationUtils::Animate(
        *animationOption, [func]() { func(); }, animationOption->GetOnFinishEvent());
}

void AsymmetricTransitionEffect::OnAppear()
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

void AsymmetricTransitionEffect::OnDisappear(bool activeTransition)
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

void AsymmetricTransitionEffect::UpdateFrameSize(const SizeF& size)
{
    RosenTransitionEffect::UpdateFrameSize(size);
    if (transitionIn_) {
        transitionIn_->UpdateFrameSize(size);
    }
    if (transitionOut_) {
        transitionOut_->UpdateFrameSize(size);
    }
}

void SlideTransitionEffect::UpdateFrameSize(const SizeF& size)
{
    DynamicCast<TranslateTransitionEffect>(transitionIn_)->SetActiveValue({ -size.Width(), 0.0f });
    DynamicCast<TranslateTransitionEffect>(transitionOut_)->SetActiveValue({ size.Width(), 0.0f });
}
} // namespace OHOS::Ace::NG