/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "render_service_client/core/animation/rs_interactive_implict_animator.h"

#include "core/animation/native_curve_helper.h"
#include "core/common/container.h"

namespace OHOS::Ace {

namespace {
Rosen::FinishCallbackType ToAnimationFinishCallbackType(const FinishCallbackType finishCallbackType)
{
    if (finishCallbackType == FinishCallbackType::LOGICALLY) {
        return Rosen::FinishCallbackType::LOGICALLY;
    } else if (finishCallbackType == FinishCallbackType::REMOVED) {
        return Rosen::FinishCallbackType::TIME_SENSITIVE;
    } else {
        return Rosen::FinishCallbackType::TIME_SENSITIVE;
    }
}
Rosen::RSAnimationTimingProtocol OptionToTimingProtocol(const AnimationOption& option)
{
    Rosen::RSAnimationTimingProtocol timingProtocol;
    timingProtocol.SetDuration(option.GetDuration());
    timingProtocol.SetStartDelay(option.GetDelay());
    timingProtocol.SetSpeed(option.GetTempo());
    timingProtocol.SetRepeatCount(option.GetIteration());
    timingProtocol.SetDirection(option.GetAnimationDirection() == AnimationDirection::NORMAL ||
                                option.GetAnimationDirection() == AnimationDirection::ALTERNATE);
    timingProtocol.SetAutoReverse(option.GetAnimationDirection() == AnimationDirection::ALTERNATE ||
                                  option.GetAnimationDirection() == AnimationDirection::ALTERNATE_REVERSE);
    timingProtocol.SetFillMode(static_cast<Rosen::FillMode>(option.GetFillMode()));
    timingProtocol.SetFinishCallbackType(ToAnimationFinishCallbackType(option.GetFinishCallbackType()));
    auto rateRange = option.GetFrameRateRange();
    if (rateRange) {
        timingProtocol.SetFrameRateRange({ rateRange->min_, rateRange->max_, rateRange->preferred_, 0,
            static_cast<Rosen::ComponentScene>(rateRange->componentScene_) });
    }
    return timingProtocol;
}
std::function<void()> GetWrappedCallback(const std::function<void()>& callback)
{
    if (!callback) {
        return nullptr;
    }
    auto wrappedOnFinish = [onFinish = callback, instanceId = Container::CurrentIdSafelyWithCheck()]() {
        ContainerScope scope(instanceId);
        auto taskExecutor = Container::CurrentTaskExecutor();
        if (!taskExecutor) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "taskExecutor is nullptr");
            return;
        }
        if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            onFinish();
            return;
        }
        taskExecutor->PostTask([onFinish]() { onFinish(); }, TaskExecutor::TaskType::UI,
            "ArkUIAnimationGetWrappedCallback", PriorityType::HIGH);
    };
    return wrappedOnFinish;
}
} // namespace

class AnimationUtils::Animation {
private:
    std::vector<std::shared_ptr<OHOS::Rosen::RSAnimation>> animations_;

    friend AnimationUtils;
};

class AnimationUtils::InteractiveAnimation {
private:
    std::shared_ptr<Rosen::RSInteractiveImplictAnimator> interactiveAnimation_;
    friend AnimationUtils;
};

void AnimationUtils::OpenImplicitAnimation(
    const AnimationOption& option, const RefPtr<Curve>& curve, const std::function<void()>& finishCallback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback);
    Rosen::RSNode::OpenImplicitAnimation(timingProtocol, NativeCurveHelper::ToNativeCurve(curve), wrappedOnFinish);
}

bool AnimationUtils::CloseImplicitAnimation()
{
    auto animations = Rosen::RSNode::CloseImplicitAnimation();
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
    return !animations.empty();
}

bool AnimationUtils::CloseImplicitCancelAnimation()
{
    return Rosen::RSNode::CloseImplicitCancelAnimation();
}

bool AnimationUtils::IsImplicitAnimationOpen()
{
    return Rosen::RSNode::IsImplicitAnimationOpen();
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback);
    auto wrappedOnRepeat = GetWrappedCallback(repeatCallback);
    Rosen::RSNode::Animate(timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback,
        wrappedOnFinish, wrappedOnRepeat);
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
}

void AnimationUtils::AnimateWithCurrentOptions(
    const PropertyCallback& callback, const FinishCallback& finishCallback, bool timingSensitive)
{
    auto wrappedOnFinish = GetWrappedCallback(finishCallback);
    Rosen::RSNode::AnimateWithCurrentOptions(callback, wrappedOnFinish, timingSensitive);
}

void AnimationUtils::AnimateWithCurrentCallback(const AnimationOption& option, const PropertyCallback& callback)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    Rosen::RSNode::AnimateWithCurrentCallback(
        timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{
    Rosen::RSNode::AddKeyFrame(fraction, NativeCurveHelper::ToNativeCurve(curve), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback)
{
    Rosen::RSNode::AddKeyFrame(fraction, callback);
}

void AnimationUtils::AddDurationKeyFrame(int duration, const RefPtr<Curve>& curve, const PropertyCallback& callback)
{
    Rosen::RSNode::AddDurationKeyFrame(duration, NativeCurveHelper::ToNativeCurve(curve), callback);
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(const AnimationOption& option,
    const PropertyCallback& callback, const FinishCallback& finishCallback, const RepeatCallback& repeatCallback)
{
    std::shared_ptr<AnimationUtils::Animation> animation = std::make_shared<AnimationUtils::Animation>();
    CHECK_NULL_RETURN(animation, nullptr);
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback);
    auto wrappedOnRepeat = GetWrappedCallback(repeatCallback);
    animation->animations_ = Rosen::RSNode::Animate(timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()),
        callback, wrappedOnFinish, wrappedOnRepeat);
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
    if (!animation->animations_.empty()) {
        return animation;
    }
    return nullptr;
}

void AnimationUtils::StopAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    if (!animation->animations_.empty()) {
        for (auto& ani : animation->animations_) {
            ani->Finish();
        }
        animation->animations_.clear();
    }
}

void AnimationUtils::BlendBgColorAnimation(
    RefPtr<NG::RenderContext>& renderContext, const Color& endColor, int32_t duration, const RefPtr<Curve>& curve)
{
    AnimationOption option = AnimationOption();
    option.SetCurve(curve);
    option.SetDuration(duration);
    AnimationUtils::Animate(option, [context = renderContext, color = endColor]() { context->BlendBgColor(color); });
}

void AnimationUtils::PauseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    for (auto& ani : animation->animations_) {
        ani->Pause();
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
}

void AnimationUtils::ResumeAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
{
    CHECK_NULL_VOID(animation);
    if (animation->animations_.empty()) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    if (pipeline) {
        pipeline->RequestFrame();
    }
    for (auto& ani : animation->animations_) {
        ani->Resume();
    }
}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback)
{
    Rosen::RSNode::ExecuteWithoutAnimation(callback);
}

std::shared_ptr<AnimationUtils::InteractiveAnimation> AnimationUtils::CreateInteractiveAnimation(
    const InteractiveAnimationCallback& addCallback, const FinishCallback& callback)
{
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation =
        std::make_shared<AnimationUtils::InteractiveAnimation>();
    CHECK_NULL_RETURN(interactiveAnimation, nullptr);
    auto wrappedOnFinish = GetWrappedCallback(callback);
    Rosen::RSAnimationTimingProtocol timingProtocol;
    Rosen::RSAnimationTimingCurve curve;
    interactiveAnimation->interactiveAnimation_ =
        Rosen::RSInteractiveImplictAnimator::Create(timingProtocol, curve);
    CHECK_NULL_RETURN(interactiveAnimation->interactiveAnimation_, nullptr);
    if (addCallback) {
        interactiveAnimation->interactiveAnimation_->AddAnimation(addCallback);
    }
    interactiveAnimation->interactiveAnimation_->SetFinishCallBack(wrappedOnFinish);
    return interactiveAnimation;
}

int32_t AnimationUtils::StartInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    CHECK_NULL_RETURN(interactiveAnimation, -1);
    CHECK_NULL_RETURN(interactiveAnimation->interactiveAnimation_, -1);
    return interactiveAnimation->interactiveAnimation_->StartAnimation();
}

void AnimationUtils::ContinueInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->interactiveAnimation_);
    interactiveAnimation->interactiveAnimation_->ContinueAnimation();
}

void AnimationUtils::ReverseInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->interactiveAnimation_);
    interactiveAnimation->interactiveAnimation_->ReverseAnimation();
}

void AnimationUtils::UpdateInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation, float progress)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->interactiveAnimation_);
    interactiveAnimation->interactiveAnimation_->PauseAnimation();
    interactiveAnimation->interactiveAnimation_->SetFraction(progress);
}

void AnimationUtils::AddInteractiveAnimation(
    const std::shared_ptr<AnimationUtils::InteractiveAnimation>& interactiveAnimation,
    const std::function<void()>& callback)
{
    CHECK_NULL_VOID(interactiveAnimation);
    CHECK_NULL_VOID(interactiveAnimation->interactiveAnimation_);
    interactiveAnimation->interactiveAnimation_->AddAnimation(callback);
}
} // namespace OHOS::Ace
