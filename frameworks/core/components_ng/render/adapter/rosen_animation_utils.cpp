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
#include "core/components_ng/animation/callback_thread_wrapper.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "render_service_client/core/ui/rs_ui_director.h"

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
    timingProtocol.SetInterfaceName(option.GetAnimationInterfaceString());
    auto rateRange = option.GetFrameRateRange();
    if (rateRange) {
        timingProtocol.SetFrameRateRange({ rateRange->min_, rateRange->max_, rateRange->preferred_, 0,
            static_cast<Rosen::ComponentScene>(rateRange->componentScene_) });
    }
    return timingProtocol;
}
std::function<void()> GetWrappedCallback(
    const std::function<void()>& callback, bool once, const RefPtr<PipelineBase>& pipeline)
{
    CHECK_NULL_RETURN(callback, nullptr);
    auto instanceId = pipeline ? pipeline->GetInstanceId() : Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(instanceId);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_RETURN(taskExecutor, callback);
    NG::CallbackThreadWrapper callbackWrapper { taskExecutor, callback, once };
    auto wrappedCallback = [callbackWrapper, instanceId]() mutable {
        ContainerScope scope(instanceId);
        auto taskExecutor = Container::CurrentTaskExecutor();
        if (!taskExecutor) {
            TAG_LOGW(AceLogTag::ACE_ANIMATION, "taskExecutor is nullptr");
            return;
        }
        if (taskExecutor->WillRunOnCurrentThread(TaskExecutor::TaskType::UI)) {
            callbackWrapper();
            return;
        }
        taskExecutor->PostTask([callbackWrapper] () mutable { callbackWrapper(); }, TaskExecutor::TaskType::UI,
            "ArkUIAnimationGetWrappedCallback", PriorityType::HIGH);
    };
    return wrappedCallback;
}

std::shared_ptr<Rosen::RSUIContext> GetRSUIContext(const RefPtr<PipelineBase>& context)
{
    return AnimationUtils::GetCurrentRSUIContext(context);
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

void AnimationUtils::SetNavGroupNodeTransAnimationCallback()
{
    auto pipelineContext = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto navigationManger = pipelineContext->GetNavigationManager();
    CHECK_NULL_VOID(navigationManger);
    navigationManger->SetNodeAddAnimation(true);
}

void AnimationUtils::OpenImplicitAnimation(const AnimationOption& option, const RefPtr<Curve>& curve,
    const std::function<void()>& finishCallback, const RefPtr<PipelineBase>& context)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback, true, context);
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::OpenImplicitAnimation(rsUIContext, timingProtocol,
        NativeCurveHelper::ToNativeCurve(curve), wrappedOnFinish);
}

bool AnimationUtils::CloseImplicitAnimation(const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    auto animations = Rosen::RSNode::CloseImplicitAnimation(rsUIContext);
    auto pipeline = context ? context : PipelineBase::GetCurrentContext();
    SetNavGroupNodeTransAnimationCallback();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
    return !animations.empty();
}

bool AnimationUtils::CloseImplicitCancelAnimation(const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    return Rosen::RSNode::CloseImplicitCancelAnimation(rsUIContext);
}

CancelAnimationStatus AnimationUtils::CloseImplicitCancelAnimationReturnStatus(const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    auto status = Rosen::RSNode::CloseImplicitCancelAnimationReturnStatus(rsUIContext);
    return static_cast<CancelAnimationStatus>(status);
}

bool AnimationUtils::IsImplicitAnimationOpen(const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    return Rosen::RSNode::IsImplicitAnimationOpen(rsUIContext);
}

void AnimationUtils::Animate(const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback, true, context);
    auto wrappedOnRepeat = GetWrappedCallback(repeatCallback, false, context);
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::Animate(rsUIContext, timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback,
        wrappedOnFinish, wrappedOnRepeat);
    auto pipeline = context ? context : PipelineBase::GetCurrentContext();
    SetNavGroupNodeTransAnimationCallback();
    if (pipeline && !pipeline->GetOnShow()) {
        pipeline->FlushMessages();
    }
}

void AnimationUtils::AnimateWithCurrentOptions(const PropertyCallback& callback, const FinishCallback& finishCallback,
    bool timingSensitive, const RefPtr<PipelineBase>& context)
{
    auto wrappedOnFinish = GetWrappedCallback(finishCallback, true, context);
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::AnimateWithCurrentOptions(rsUIContext, callback, wrappedOnFinish, timingSensitive);
}

void AnimationUtils::AnimateWithCurrentCallback(const AnimationOption& option, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::AnimateWithCurrentCallback(rsUIContext,
        timingProtocol, NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const RefPtr<Curve>& curve, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::AddKeyFrame(rsUIContext, fraction, NativeCurveHelper::ToNativeCurve(curve), callback);
}

void AnimationUtils::AddKeyFrame(float fraction, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::AddKeyFrame(rsUIContext, fraction, callback);
}

void AnimationUtils::AddDurationKeyFrame(int duration, const RefPtr<Curve>& curve, const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::AddDurationKeyFrame(rsUIContext, duration, NativeCurveHelper::ToNativeCurve(curve), callback);
}

std::shared_ptr<AnimationUtils::Animation> AnimationUtils::StartAnimation(
    const AnimationOption& option, const PropertyCallback& callback,
    const FinishCallback& finishCallback, const RepeatCallback& repeatCallback, const RefPtr<PipelineBase>& context)
{
    std::shared_ptr<AnimationUtils::Animation> animation = std::make_shared<AnimationUtils::Animation>();
    CHECK_NULL_RETURN(animation, nullptr);
    const auto& timingProtocol = OptionToTimingProtocol(option);
    auto wrappedOnFinish = GetWrappedCallback(finishCallback, true, context);
    auto wrappedOnRepeat = GetWrappedCallback(repeatCallback, false, context);
    auto rsUIContext = GetRSUIContext(context);
    animation->animations_ = Rosen::RSNode::Animate(rsUIContext, timingProtocol,
        NativeCurveHelper::ToNativeCurve(option.GetCurve()), callback, wrappedOnFinish, wrappedOnRepeat);
    auto pipeline = context ? context : PipelineBase::GetCurrentContext();
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

void AnimationUtils::ReverseAnimation(const std::shared_ptr<AnimationUtils::Animation>& animation)
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
        ani->Reverse();
    }
}

void AnimationUtils::ExecuteWithoutAnimation(const PropertyCallback& callback,
    const RefPtr<PipelineBase>& context)
{
    auto rsUIContext = GetRSUIContext(context);
    Rosen::RSNode::ExecuteWithoutAnimation(callback, rsUIContext);
}

std::shared_ptr<AnimationUtils::InteractiveAnimation> AnimationUtils::CreateInteractiveAnimation(
    const InteractiveAnimationCallback& addCallback, const FinishCallback& callback)
{
    std::shared_ptr<AnimationUtils::InteractiveAnimation> interactiveAnimation =
        std::make_shared<AnimationUtils::InteractiveAnimation>();
    CHECK_NULL_RETURN(interactiveAnimation, nullptr);
    auto wrappedOnFinish = GetWrappedCallback(callback, true, nullptr);
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

std::shared_ptr<Rosen::RSUIContext> AnimationUtils::GetCurrentRSUIContext(RefPtr<PipelineBase> context)
{
    if (!context) {
        context = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(context, nullptr);
    }
    auto window = context->GetWindow();
    CHECK_NULL_RETURN(window, nullptr);
    auto rsUIDirector = window->GetRSUIDirector();
    CHECK_NULL_RETURN(rsUIDirector, nullptr);
    return rsUIDirector->GetRSUIContext();
}
} // namespace OHOS::Ace
