/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components/common/properties/animatable_color.h"

#include "core/event/ace_event_helper.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

AnimatableColor::AnimatableColor() = default;
AnimatableColor::AnimatableColor(uint32_t value, const AnimationOption& option) : Color(value)
{
    animationOption_ = option;
}

AnimatableColor::AnimatableColor(const Color& color, const AnimationOption& option) : Color(color.GetValue())
{
    animationOption_ = option;
}

AnimatableColor::~AnimatableColor() = default;

void AnimatableColor::SetContextAndCallback(
    const WeakPtr<PipelineContext>& context, const RenderNodeAnimationCallback& callback)
{
    context_ = context;
    animationCallback_ = callback;
}

AnimatableColor& AnimatableColor::operator=(const AnimatableColor& newColor)
{
    SetAnimationOption(newColor.GetAnimationOption());
    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext || !animationCallback_) {
        SetValue(newColor.GetValue());
        return *this;
    }
    AnimationOption explicitAnim = pipelineContext->GetExplicitAnimationOption();
    if (explicitAnim.IsValid()) {
        SetAnimationOption(explicitAnim);
        AnimateTo(newColor.GetValue());
    } else if (animationOption_.IsValid()) {
        AnimateTo(newColor.GetValue());
    } else {
        ResetController();
        SetValue(newColor.GetValue());
    }
    isFirstAssign_ = false;
    return *this;
}

void AnimatableColor::AnimateTo(uint32_t endValue)
{
    if (isFirstAssign_) {
        isFirstAssign_ = false;
        SetValue(endValue);
        return;
    }
    if (GetValue() == endValue) {
        return;
    }
    ResetController();
    if (!animationController_) {
        animationController_ = CREATE_ANIMATOR(context_);
    }

    RefPtr<CurveAnimation<Color>> colorAnimation =
        AceType::MakeRefPtr<CurveAnimation<Color>>(Color(GetValue()), Color(endValue), animationOption_.GetCurve());
    colorAnimation->AddListener(std::bind(&AnimatableColor::OnAnimationCallback, this, std::placeholders::_1));

    animationController_->AddInterpolator(colorAnimation);
    auto onFinishEvent = animationOption_.GetOnFinishEvent();
    if (onFinishEvent) {
        animationController_->AddStopListener([onFinishEvent, weakContext = context_] {
            auto context = weakContext.Upgrade();
            if (context) {
                context->PostAsyncEvent(onFinishEvent, "ArkUIAnimatableColorFinishEvent");
            } else {
                LOGE("the context is null");
            }
        });
    }
    animationController_->SetDuration(animationOption_.GetDuration());
    animationController_->SetStartDelay(animationOption_.GetDelay());
    animationController_->SetIteration(animationOption_.GetIteration());
    animationController_->SetTempo(animationOption_.GetTempo());
    animationController_->SetAnimationDirection(animationOption_.GetAnimationDirection());
    animationController_->SetFillMode(FillMode::FORWARDS);
    animationController_->SetAllowRunningAsynchronously(animationOption_.GetAllowRunningAsynchronously());
    animationController_->Play();
}

void AnimatableColor::ResetController()
{
    if (animationController_) {
        if (!animationController_->IsStopped()) {
            animationController_->Stop();
        }
        animationController_->ClearInterpolators();
        animationController_->ClearAllListeners();
        animationController_.Reset();
    }
}

void AnimatableColor::OnAnimationCallback(const Color& color)
{
    SetValue(color.GetValue());
    if (animationCallback_) {
        animationCallback_();
    }
}

} // namespace OHOS::Ace
