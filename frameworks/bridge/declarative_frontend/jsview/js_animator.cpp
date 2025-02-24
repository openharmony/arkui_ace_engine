/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_animator.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"


#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_animator_function.h"
#include "bridge/declarative_frontend/jsview/models/animator_model_impl.h"
#include "core/components_ng/pattern/animator/animator_model.h"
#include "core/components_ng/pattern/animator/animator_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<AnimatorModel> AnimatorModel::instance_ = nullptr;
std::mutex AnimatorModel::mutex_;

AnimatorModel* AnimatorModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new Framework::AnimatorModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new Framework::AnimatorModelNG());
            } else {
                instance_.reset(new Framework::AnimatorModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

constexpr int32_t FRICTION_MOTION_LENGTH = 3;
constexpr int32_t SPRING_MOTION_LENGTH = 4;
constexpr int32_t SCROLL_MOTION_LENGTH = 5;

void AddFrameListener(const RefPtr<AnimatorInfo>& animatorInfo, const RefPtr<KeyframeAnimation<double>>& animation)
{
    if (!animatorInfo || !animation) {
        return;
    }
    auto frameEvent = animatorInfo->GetFrameEvent();
    if (frameEvent) {
        animation->AddListener(
            [frameEvent, weakInfo = WeakPtr<AnimatorInfo>(animatorInfo)](const float& progress) {
                auto animatorInfo = weakInfo.Upgrade();
                CHECK_NULL_VOID(animatorInfo);
                ACE_SCOPED_TRACE("animator component onframe. duration:%d, curve:%s", animatorInfo->GetDuration(),
                    animatorInfo->GetCurve() ? animatorInfo->GetCurve()->ToString().c_str() : "");
                frameEvent(progress);
            });
    }
}

void HandleAnimatorInfo(const RefPtr<AnimatorInfo>& animatorInfo, const RefPtr<Animator>& animator)
{
    if (!animatorInfo || !animator) {
        return;
    }
    int32_t duration = animatorInfo->GetDuration();
    int32_t delay = animatorInfo->GetDelay();
    FillMode fillMode = animatorInfo->GetFillMode();
    int32_t iteration = animatorInfo->GetIteration();
    AnimationDirection playMode = animatorInfo->GetPlayMode();
    animator->SetDuration(duration);
    animator->SetStartDelay(delay);
    animator->SetFillMode(fillMode);
    animator->SetIteration(iteration);
    animator->SetAnimationDirection(playMode);
}

bool CreateAnimation(
    const RefPtr<AnimatorInfo>& animatorInfo, const RefPtr<Animator>& animator, AnimationStatus operation)
{
    if (!animatorInfo || !animator) {
        return false;
    }
    auto motion = animatorInfo->GetAnimatorMotion();
    if (motion) {
        auto frameEvent = animatorInfo->GetFrameEvent();
        if (frameEvent) {
            motion->AddListener([frameEvent](const float& progress) { frameEvent(progress); });
        }
        animator->ClearPauseListeners();
        animator->ClearRepeatListeners();
        animator->ClearIdleListeners();
        if (operation == AnimationStatus::RUNNING && animator->GetStatus() != Animator::Status::RUNNING) {
            animator->PlayMotion(motion);
        } else if (operation == AnimationStatus::STOPPED) {
            animator->Finish();
        }
        return false;
    } else {
        animator->ClearInterpolators();
        auto keyframeBegin = AceType::MakeRefPtr<Keyframe<double>>(0.0, 0.0);
        auto keyframeEnd = AceType::MakeRefPtr<Keyframe<double>>(1.0, 1.0);
        auto keyframeAnimation = AceType::MakeRefPtr<KeyframeAnimation<double>>();
        auto curve = animatorInfo->GetCurve();
        if (curve) {
            keyframeAnimation->SetCurve(curve);
        }
        keyframeAnimation->AddKeyframe(keyframeBegin);
        keyframeAnimation->AddKeyframe(keyframeEnd);
        AddFrameListener(animatorInfo, keyframeAnimation);
        animator->AddInterpolator(keyframeAnimation);
        return true;
    }
}

std::function<void()> GetEventCallback(const JSCallbackInfo& info, const std::string& name)
{
    if (!info[0]->IsFunction()) {
        return nullptr;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    return [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), name]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT(name);
        func->Execute();
        UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", name);
    };
}

} // namespace

std::string JSAnimator::animatorId_;

void JSAnimator::JSBind(BindingTarget globalObj)
{
    JSClass<JSAnimator>::Declare("Animator");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSAnimator>::StaticMethod("create", &JSAnimator::Create, opt);
    JSClass<JSAnimator>::StaticMethod("state", &JSAnimator::SetState, opt);
    JSClass<JSAnimator>::StaticMethod("duration", &JSAnimator::SetDuration, opt);
    JSClass<JSAnimator>::StaticMethod("curve", &JSAnimator::SetCurve, opt);
    JSClass<JSAnimator>::StaticMethod("delay", &JSAnimator::SetDelay, opt);
    JSClass<JSAnimator>::StaticMethod("fillMode", &JSAnimator::SetFillMode, opt);
    JSClass<JSAnimator>::StaticMethod("iterations", &JSAnimator::SetIteration, opt);
    JSClass<JSAnimator>::StaticMethod("playMode", &JSAnimator::SetPlayMode, opt);
    JSClass<JSAnimator>::StaticMethod("motion", &JSAnimator::SetMotion, opt);
    JSClass<JSAnimator>::StaticMethod("pop", &JSAnimator::Pop, opt);

    JSClass<JSAnimator>::StaticMethod("onStart", &JSAnimator::OnStart, opt);
    JSClass<JSAnimator>::StaticMethod("onPause", &JSAnimator::OnPause, opt);
    JSClass<JSAnimator>::StaticMethod("onRepeat", &JSAnimator::OnRepeat, opt);
    JSClass<JSAnimator>::StaticMethod("onCancel", &JSAnimator::OnCancel, opt);
    JSClass<JSAnimator>::StaticMethod("onFinish", &JSAnimator::OnFinish, opt);
    JSClass<JSAnimator>::StaticMethod("onFrame", &JSAnimator::OnFrame, opt);

    JSClass<JSAnimator>::Bind<>(globalObj);

    JSClass<JSSpringProp>::Declare("SpringProp");
    JSClass<JSSpringProp>::Bind(globalObj, JSSpringProp::ConstructorCallback, JSSpringProp::DestructorCallback);

    JSClass<JSMotion>::Declare("SpringMotion");
    JSClass<JSMotion>::Bind(globalObj, JSMotion::ConstructorCallback, JSMotion::DestructorCallback);

    JSClass<JSMotion>::Declare("FrictionMotion");
    JSClass<JSMotion>::Bind(globalObj, JSMotion::ConstructorCallback, JSMotion::DestructorCallback);

    JSClass<JSMotion>::Declare("ScrollMotion");
    JSClass<JSMotion>::Bind(globalObj, JSMotion::ConstructorCallback, JSMotion::DestructorCallback);
}

void JSAnimator::Create(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() != 1) {
        return;
    }

    if (!info[0]->IsString()) {
        return;
    }
    animatorId_ = info[0]->ToString();
    AnimatorModel::GetInstance()->Create(animatorId_);
}

void JSAnimator::Pop() {}

void JSAnimator::SetState(int32_t state)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        TAG_LOGW(AceLogTag::ACE_ANIMATION, "animator component setState failed, id:%{public}s, state:%{public}d",
            animatorId_.c_str(), state);
        return;
    }
    auto animator = animatorInfo->GetAnimator();
    CHECK_NULL_VOID(animator);
    auto operation = static_cast<AnimationStatus>(state);
    HandleAnimatorInfo(animatorInfo, animator);
    if (!CreateAnimation(animatorInfo, animator, operation)) {
        return;
    }
    switch (operation) {
        case AnimationStatus::RUNNING:
            TAG_LOGI(AceLogTag::ACE_ANIMATION, "animator component play, id:%{public}s", animatorId_.c_str());
            animator->Play();
            break;
        case AnimationStatus::PAUSED:
            TAG_LOGI(AceLogTag::ACE_ANIMATION, "animator component pause, id:%{public}s", animatorId_.c_str());
            animator->Pause();
            break;
        case AnimationStatus::STOPPED:
            TAG_LOGI(AceLogTag::ACE_ANIMATION, "animator component stop, id:%{public}s", animatorId_.c_str());
            animator->Finish();
            break;
        case AnimationStatus::INITIAL:
            animator->Cancel();
            break;
        default:
            break;
    }
}

void JSAnimator::SetDuration(int32_t duration)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetDuration(duration);
}

void JSAnimator::SetCurve(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() != 1) {
        return;
    }

    if (!info[0]->IsString()) {
        return;
    }
    auto value = info[0]->ToString();
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    auto curve = CreateCurve(value);
    animatorInfo->SetCurve(curve);
}

void JSAnimator::SetDelay(int32_t delay)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetDelay(delay);
}

void JSAnimator::SetFillMode(int32_t fillMode)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetFillMode(static_cast<FillMode>(fillMode));
}

void JSAnimator::SetIteration(int32_t iteration)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetIteration(iteration);
}

void JSAnimator::SetPlayMode(int32_t playMode)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetPlayMode(static_cast<AnimationDirection>(playMode));
}

void JSAnimator::SetMotion(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() != 1 || !info[0]->IsObject()) {
        return;
    }
    JSMotion* rawMotion = JSRef<JSObject>::Cast(info[0])->Unwrap<JSMotion>();
    if (!rawMotion) {
        return;
    }

    RefPtr<Motion> motion = rawMotion->GetMotion();
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetAnimatorMotion(motion);
}

void JSAnimator::OnStart(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto callback = GetEventCallback(info, "Animator.onStart");
    AnimatorModel::GetInstance()->AddEventListener(std::move(callback), EventOperation::START, animatorId_);
}

void JSAnimator::OnPause(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto callback = GetEventCallback(info, "Animator.onPause");
    AnimatorModel::GetInstance()->AddEventListener(std::move(callback), EventOperation::PAUSE, animatorId_);
}

void JSAnimator::OnRepeat(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto callback = GetEventCallback(info, "Animator.onRepeat");
    AnimatorModel::GetInstance()->AddEventListener(std::move(callback), EventOperation::REPEAT, animatorId_);
}

void JSAnimator::OnCancel(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto callback = GetEventCallback(info, "Animator.onCancel");
    AnimatorModel::GetInstance()->AddEventListener(std::move(callback), EventOperation::CANCEL, animatorId_);
}

void JSAnimator::OnFinish(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    auto callback = GetEventCallback(info, "Animator.onFinish");
    AnimatorModel::GetInstance()->AddEventListener(std::move(callback), EventOperation::FINISH, animatorId_);
}

void JSAnimator::OnFrame(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsAnimatorFunction> function = AceType::MakeRefPtr<JsAnimatorFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto OnFrameEvent = [execCtx = info.GetExecutionContext(), func = std::move(function)](const float& progress) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Animator.onFrame");
        func->Execute(progress);
    };
    auto animatorInfo = AnimatorModel::GetInstance()->GetAnimatorInfo(animatorId_);
    if (!animatorInfo) {
        return;
    }
    animatorInfo->SetFrameEvent(OnFrameEvent);
}

void JSSpringProp::ConstructorCallback(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    if (info.Length() != 3 || !info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        return;
    }
    auto obj = AceType::MakeRefPtr<JSSpringProp>();
    double mass = info[0]->ToNumber<double>();
    double stiffness = info[1]->ToNumber<double>();
    double damping = info[2]->ToNumber<double>();
    auto springProp = AceType::MakeRefPtr<SpringProperty>(mass, stiffness, damping);
    obj->SetSpringProp(springProp);
    obj->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(obj));
}

void JSSpringProp::DestructorCallback(JSSpringProp* obj)
{
    if (obj != nullptr) {
        obj->DecRefCount();
    }
}

void JSMotion::ConstructorCallback(const JSCallbackInfo& info)
{
    ContainerScope scope(Container::CurrentIdSafely());
    int32_t len = info.Length();
    if (len != FRICTION_MOTION_LENGTH && len != SPRING_MOTION_LENGTH && len != SCROLL_MOTION_LENGTH) {
        return;
    }
    auto obj = AceType::MakeRefPtr<JSMotion>();
    if (len == FRICTION_MOTION_LENGTH) {
        HandleFrictionMotion(info, obj);
    } else if (len == SPRING_MOTION_LENGTH) {
        HandleSpringMotion(info, obj);
    } else {
        HandleScrollMotion(info, obj);
    }
    obj->IncRefCount();
    info.SetReturnValue(AceType::RawPtr(obj));
}

void JSMotion::HandleFrictionMotion(const JSCallbackInfo& info, RefPtr<JSMotion>& obj)
{
    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber()) {
        return;
    }
    double friction = info[0]->ToNumber<double>();
    double position = info[1]->ToNumber<double>();
    double velocity = info[2]->ToNumber<double>();
    RefPtr<FrictionMotion> frictionMotion = AceType::MakeRefPtr<FrictionMotion>(friction, position, velocity);
    obj->SetMotion(frictionMotion);
}

void JSMotion::HandleSpringMotion(const JSCallbackInfo& info, RefPtr<JSMotion>& obj)
{
    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() || !info[3]->IsObject()) {
        return;
    }
    double start = info[0]->ToNumber<double>();
    double end = info[1]->ToNumber<double>();
    double velocity = info[2]->ToNumber<double>();
    JSSpringProp* prop = JSRef<JSObject>::Cast(info[3])->Unwrap<JSSpringProp>();
    if (!prop) {
        return;
    }
    RefPtr<SpringProperty> springProperty = prop->GetSpringProp();
    auto springMotion = AceType::MakeRefPtr<SpringMotion>(start, end, velocity, springProperty);
    obj->SetMotion(springMotion);
}

void JSMotion::HandleScrollMotion(const JSCallbackInfo& info, RefPtr<JSMotion>& obj)
{
    if (!info[0]->IsNumber() || !info[1]->IsNumber() || !info[2]->IsNumber() || !info[3]->IsNumber() ||
        !info[4]->IsObject()) {
        return;
    }
    double position = info[0]->ToNumber<double>();
    double velocity = info[1]->ToNumber<double>();
    double min = info[2]->ToNumber<double>();
    double max = info[3]->ToNumber<double>();
    JSSpringProp* prop = JSRef<JSObject>::Cast(info[4])->Unwrap<JSSpringProp>();
    if (!prop) {
        return;
    }
    RefPtr<SpringProperty> springProperty = prop->GetSpringProp();
    RefPtr<ScrollMotion> scrollMotion = AceType::MakeRefPtr<ScrollMotion>(
        position, velocity, ExtentPair(min, min), ExtentPair(max, max), springProperty);
    obj->SetMotion(scrollMotion);
}

void JSMotion::DestructorCallback(JSMotion* obj)
{
    if (obj != nullptr) {
        obj->DecRefCount();
    }
}

} // namespace OHOS::Ace::Framework
