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

#include "cj_animator.h"
#include "bridge/common/utils/utils.h"
#include "cj_lambda.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;

const char INTERPOLATING_SPRING[] = "interpolatingSpring";
constexpr size_t INTERPOLATING_SPRING_PARAMS_SIZE = 4;

namespace OHOS::Ace {

AnimationDirection StringToAnimationDirection(const std::string& direction)
{
    if (direction.compare("alternate") == 0) {
        return AnimationDirection::ALTERNATE;
    } else if (direction.compare("reverse") == 0) {
        return AnimationDirection::REVERSE;
    } else if (direction.compare("alternate-reverse") == 0) {
        return AnimationDirection::ALTERNATE_REVERSE;
    } else {
        return AnimationDirection::NORMAL;
    }
}

FillMode StringToFillMode(const std::string& fillMode)
{
    if (fillMode.compare("forwards") == 0) {
        return FillMode::FORWARDS;
    } else if (fillMode.compare("backwards") == 0) {
        return FillMode::BACKWARDS;
    } else if (fillMode.compare("both") == 0) {
        return FillMode::BOTH;
    } else {
        return FillMode::NONE;
    }
}

RefPtr<Motion> ParseOptionToMotion(const std::shared_ptr<AnimatorOption>& option)
{
    const auto& curveStr = option->easing;
    if (curveStr.back() != ')') {
        return nullptr;
    }
    std::string::size_type leftEmbracePosition = curveStr.find_last_of('(');
    if (leftEmbracePosition == std::string::npos) {
        return nullptr;
    }
    auto aniTimFuncName = curveStr.substr(0, leftEmbracePosition);
    if (aniTimFuncName.compare(INTERPOLATING_SPRING)) {
        return nullptr;
    }
    auto params = curveStr.substr(leftEmbracePosition + 1, curveStr.length() - leftEmbracePosition - 2);
    std::vector<std::string> paramsVector;
    StringUtils::StringSplitter(params, ',', paramsVector);
    if (paramsVector.size() != INTERPOLATING_SPRING_PARAMS_SIZE) {
        return nullptr;
    }
    for (auto& param : paramsVector) {
        Framework::RemoveHeadTailSpace(param);
    }
    float velocity = StringUtils::StringToFloat(paramsVector[0]);
    float mass = StringUtils::StringToFloat(paramsVector[1]);
    float stiffness = StringUtils::StringToFloat(paramsVector[2]);
    float damping = StringUtils::StringToFloat(paramsVector[3]);
    // input velocity is normalized velocity, while the velocity of arkui's springMotion is absolute velocity.
    velocity = velocity * (option->end - option->begin);
    if (LessOrEqual(mass, 0)) {
        mass = 1.0f;
    }
    if (LessOrEqual(stiffness, 0)) {
        stiffness = 1.0f;
    }
    if (LessOrEqual(damping, 0)) {
        damping = 1.0f;
    }
    return AceType::MakeRefPtr<SpringMotion>(
        option->begin, option->end, velocity, AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping));
}

void AnimatorResultImpl::ApplyOption()
{
    CHECK_NULL_VOID(animator_);
    CHECK_NULL_VOID(option_);
    if (motion_) {
        // duration not works. Iteration can only be 1. Direction can only be normal.
        animator_->SetIteration(1);
        animator_->SetAnimationDirection(AnimationDirection::NORMAL);
    } else {
        animator_->SetDuration(option_->duration);
        animator_->SetIteration(option_->iterations);
        animator_->SetAnimationDirection(StringToAnimationDirection(option_->direction));
    }
    animator_->SetStartDelay(option_->delay);
    // FillMode not works for motion in animator implementation.
    animator_->SetFillMode(StringToFillMode(option_->fill));
}

void AnimatorResultImpl::SetOnframe(int64_t funcId)
{
    auto func = reinterpret_cast<void(*)(double)>(funcId);
    onframe_ = CJLambda::Create(func);
    animator_->ClearInterpolators();
    auto onFrameCallback = [&callback = onframe_,
                                weakOption = std::weak_ptr<AnimatorOption>(option_)]
                            (double value) {
        auto option = weakOption.lock();
        ACE_SCOPED_TRACE("ohos.animator onframe. duration:%d, curve:%s", option->duration, option->easing.c_str());
        callback(value);
    };
    RefPtr<Animation<double>> animation;
    RefPtr<Motion> motion = ParseOptionToMotion(option_);
    if (motion) {
        motion->AddListener(onFrameCallback);
        motion_ = motion;
    } else {
        auto curve = Framework::CreateCurve(option_->easing);
        animation = AceType::MakeRefPtr<CurveAnimation<double>>(option_->begin, option_->end, curve);
        animation->AddListener(onFrameCallback);
        animator_->AddInterpolator(animation);
        motion_ = nullptr;
    }
    if (!animator_->HasScheduler()) {
        animator_->AttachSchedulerOnContainer();
    }
    return;
}

void AnimatorResultImpl::SetOnfinish(int64_t funcId)
{
    auto func = reinterpret_cast<void(*)(void)>(funcId);
    onfinish_ = CJLambda::Create(func);
    animator_->ClearStopListeners();
    animator_->AddStopListener([&callback = onfinish_] {
        callback();
    });
    return;
}

void AnimatorResultImpl::SetOncancel(int64_t funcId)
{
    auto func = reinterpret_cast<void(*)(void)>(funcId);
    oncancel_ = CJLambda::Create(func);
    animator_->ClearIdleListeners();
    animator_->AddIdleListener([&callback = oncancel_] {
        callback();
    });
    return;
}

void AnimatorResultImpl::SetOnrepeat(int64_t funcId)
{
    auto func = reinterpret_cast<void(*)(void)>(funcId);
    onrepeat_ = CJLambda::Create(func);
    animator_->ClearRepeatListeners();
    animator_->AddRepeatListener([&callback = onrepeat_] {
        callback();
    });
    return;
}

void AnimatorResultImpl::Destroy()
{
    if (animator_) {
        if (!animator_->IsStopped()) {
            animator_->Stop();
            LOGI("Animator force stopping done, id:%{public}d", animator_->GetId());
        }
    }
}
}
