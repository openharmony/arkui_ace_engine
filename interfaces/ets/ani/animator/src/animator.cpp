/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ani.h>
#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "interop_js/hybridgref_ani.h"
#include "interop_js/hybridgref_napi.h"
#include "napi/kits/animator/animator_option.h"

#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animator.h"
#include "core/animation/animation.h"
#include "core/animation/curve.h"
#include "core/animation/spring_motion.h"

namespace OHOS::Ace::Ani {
constexpr size_t INTERPOLATING_SPRING_PARAMS_SIZE = 4;
constexpr char INTERPOLATING_SPRING[] = "interpolating-spring";
constexpr int32_t ANIMATOR_DEFALUT_DURATION = 1000;
const std::string ANIMATOR_DEFALUT_EASING = "ease";
constexpr int32_t ANIMATOR_DEFALUT_DELAY = 0;
const std::string ANIMATOR_FILLMODE_NONE = "none";
const std::string ANIMATOR_FILLMODE_BACKWARDS = "backwards";
const std::string ANIMATOR_FILLMODE_BOTH = "both";
const std::string ANIMATOR_FILLMODE_FORWARDS = "forwards";
const std::string ANIMATOR_DIRECTION_ALTERNATE = "alternate";
const std::string ANIMATOR_DIRECTION_REVERSE = "reverse";
const std::string ANIMATOR_DIRECTION_ALTERNATE_REVERSE = "alternate-reverse";
const std::string ANIMATOR_DIRECTION_NORMAL = "normal";
constexpr int32_t ANIMATOR_DEFALUT_ITERATIONS = 1;

constexpr int32_t ANIMATION_DIRETION_NORMAL_NUM = 0;
constexpr int32_t ANIMATION_DIRETION_REVERSE_NUM = 1;
constexpr int32_t ANIMATION_DIRETION_ALTERNATE_NUM = 2;
constexpr int32_t ANIMATION_DIRETION_ALTERNATE_REVERSE_NUM = 3;
static AnimationDirection StringToAnimationDirection(const std::string &direction)
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

static FillMode StringToFillMode(const std::string &fillMode)
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

static bool IsInstanceOfCls(ani_env *env, [[maybe_unused]] ani_object object, const char* className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_boolean isInstance;
    if (env->Object_InstanceOf(object, cls, &isInstance)) {
        return false;
    }
    return (bool)isInstance;
}

static std::string FillModeToString(const FillMode& fillMode)
{
    switch (fillMode) {
        case FillMode::NONE:
            return ANIMATOR_FILLMODE_NONE;
        case FillMode::BACKWARDS:
            return ANIMATOR_FILLMODE_BACKWARDS;
        case FillMode::BOTH:
            return ANIMATOR_FILLMODE_BOTH;
        case FillMode::FORWARDS:
            [[fallthrough]];
        default:
            return ANIMATOR_FILLMODE_FORWARDS;
    }
}

static std::string AnimationDirectionToString(const AnimationDirection& direction)
{
    switch (direction) {
        case AnimationDirection::ALTERNATE:
            return ANIMATOR_DIRECTION_ALTERNATE;
        case AnimationDirection::REVERSE:
            return ANIMATOR_DIRECTION_REVERSE;
        case AnimationDirection::ALTERNATE_REVERSE:
            return ANIMATOR_DIRECTION_ALTERNATE_REVERSE;
        case AnimationDirection::NORMAL:
            [[fallthrough]];
        default:
            return ANIMATOR_DIRECTION_NORMAL;
    }
}

class AnimatorResult final: public Napi::AnimatorResultBase {
public:
    AnimatorResult() = default;
    AnimatorResult(RefPtr<Animator> &animator, std::shared_ptr<Napi::AnimatorOption> &option)
        : Napi::AnimatorResultBase(animator, option)
    {
        ApplyOption();
    }
    ~AnimatorResult() override = default;

    ani_ref GetOnframeRef() const
    {
        return onframe_;
    }

    void SetOnframeRef(const ani_ref &onframe)
    {
        onframe_ = onframe;
    }

    ani_ref GetOnfinishRef() const
    {
        return onfinish_;
    }

    void SetOnfinishRef(const ani_ref &onfinish)
    {
        onfinish_ = onfinish;
    }

    ani_ref GetOncancelRef() const
    {
        return oncancel_;
    }

    void SetOncancelRef(const ani_ref &oncancel)
    {
        oncancel_ = oncancel;
    }

    ani_ref GetOnrepeatRef() const
    {
        return onrepeat_;
    }

    void SetOnrepeatRef(const ani_ref &onrepeat)
    {
        onrepeat_ = onrepeat;
    }

    void ApplyOption()
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

private:
    ani_ref onframe_ = nullptr;
    ani_ref onfinish_ = nullptr;
    ani_ref oncancel_ = nullptr;
    ani_ref onrepeat_ = nullptr;
};

class JsSimpleAnimatorOption {
public:
    JsSimpleAnimatorOption() = default;
    ~JsSimpleAnimatorOption() = default;
    double GetBegin() const
    {
        return begin_;
    }

    void SetBegin(const double& begin)
    {
        begin_ = begin;
    }

    double GetEnd() const
    {
        return end_;
    }

    void SetEnd(const double& end)
    {
        end_ = end;
    }

    void SetDuration(const std::optional<int32_t>& duration)
    {
        duration_ = duration;
    }

    std::optional<int32_t> GetDuration() const
    {
        return duration_;
    }

    void SetEasing(const std::optional<std::string>& easing)
    {
        easing_ = easing;
    }

    std::optional<std::string> GetEasing() const
    {
        return easing_;
    }

    void SetDelay(const std::optional<int32_t>& delay)
    {
        delay_ = delay;
    }

    std::optional<int32_t> GetDelay() const
    {
        return delay_;
    }

    void SetFill(const std::optional<FillMode>& fill)
    {
        fill_ = fill;
    }

    std::optional<FillMode> GetFill() const
    {
        return fill_;
    }

    void SetDirection(const std::optional<AnimationDirection>& direction)
    {
        direction_ = direction;
    }

    std::optional<AnimationDirection> GetDirection() const
    {
        return direction_;
    }

    void SetIterations(const std::optional<int32_t>& iterations)
    {
        iterations_ = iterations;
    }

    std::optional<int32_t> GetIterations() const
    {
        return iterations_;
    }

private:
    double begin_ = 0.0;
    double end_ = 1.0;
    std::optional<int32_t> duration_;
    std::optional<int32_t> delay_;
    std::optional<int32_t> iterations_;
    std::optional<std::string> easing_;
    std::optional<FillMode> fill_;
    std::optional<AnimationDirection> direction_;
};

std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1);
    char *utf8_buffer = buffer.data();

    // String_GetUTF8 Supportted by https://gitee.com/openharmony/arkcompiler_runtime_core/pulls/3416
    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8_buffer, strSize + 1, &bytes_written);
    utf8_buffer[bytes_written] = '\0';
    std::string content = std::string(utf8_buffer);
    return content;
}

static AnimatorResult* GetAnimatorResult(ani_env *env, ani_object obj)
{
    ani_long animatorResultForAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "animatorResult", &animatorResultForAni)) {
        return nullptr;
    }
    return reinterpret_cast<AnimatorResult*>(animatorResultForAni);
}

static JsSimpleAnimatorOption *GetJsSimpleAnimatorOption(ani_env *env, ani_object obj)
{
    ani_long JsSimpleAnimatorOptionForAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "SimpleAnimatorOptionsResult", &JsSimpleAnimatorOptionForAni)) {
        return nullptr;
    }
    return reinterpret_cast<JsSimpleAnimatorOption *>(JsSimpleAnimatorOptionForAni);
}

// ani
static void JSReverse(ani_env *env, ani_object obj)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    // GetMotion
    if (animatorResult->GetMotion()) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    if (!animator->HasScheduler()) {
        // AttachSchedulerOnContainer
        auto result = animator->AttachSchedulerOnContainer();
        if (!result) {
            return;
        }
    }
    animator->Reverse();
}

// ani
static void JSCancel(ani_env *env, ani_object obj)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->Cancel();
}

// ani
static void JSPause(ani_env *env, ani_object obj)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->Pause();
}

// ani
static void JSFinish(ani_env *env, ani_object obj)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (animator == nullptr) {
        return;
    }
    animator->Finish();
}

// ani
static void JSPlay(ani_env *env, ani_object obj)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    if (!animator->HasScheduler()) {
        auto result = animator->AttachSchedulerOnContainer();
        if (!result) {
            return;
        }
    }
    if (animatorResult->GetMotion()) {
        animator->PlayMotion(animatorResult->GetMotion());
    } else {
        animator->Play();
    }
    animator->PrintVsyncInfoIfNeed();
}

static void ParseAnimatorOption(ani_env *env, ani_object obj, std::shared_ptr<Napi::AnimatorOption> option)
{
    ani_int durationAni;
    ani_int iterationsAni;
    ani_int delayAni;
    ani_ref easingAni;
    ani_ref fillAni;
    ani_ref directionAni;
    ani_double beginAni;
    ani_double endAni;
    if (IsInstanceOfCls(env, obj, "@ohos.animator.SimpleAnimatorOptions")) {
        auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, obj);
        CHECK_NULL_VOID(simpleAnimatorOption);
        option->begin = simpleAnimatorOption->GetBegin();
        option->end = simpleAnimatorOption->GetEnd();
        option->duration = simpleAnimatorOption->GetDuration().has_value() ?
            simpleAnimatorOption->GetDuration().value() : ANIMATOR_DEFALUT_DURATION;
        option->easing = simpleAnimatorOption->GetEasing().has_value() ?
            simpleAnimatorOption->GetEasing().value() : ANIMATOR_DEFALUT_EASING;
        option->delay = simpleAnimatorOption->GetDelay().has_value() ?
            simpleAnimatorOption->GetDelay().value() : ANIMATOR_DEFALUT_DELAY;
        option->fill = simpleAnimatorOption->GetFill().has_value() ?
            FillModeToString(simpleAnimatorOption->GetFill().value()) : ANIMATOR_FILLMODE_FORWARDS;
        option->direction = simpleAnimatorOption->GetDirection().has_value() ?
            AnimationDirectionToString(simpleAnimatorOption->GetDirection().value()) : ANIMATOR_DIRECTION_NORMAL;
        option->iterations = simpleAnimatorOption->GetIterations().has_value() ?
            simpleAnimatorOption->GetIterations().value() : ANIMATOR_DEFALUT_ITERATIONS;
        return;
    }
    env->Object_GetPropertyByName_Int(obj, "duration", &durationAni);
    env->Object_GetPropertyByName_Int(obj, "iterations", &iterationsAni);
    env->Object_GetPropertyByName_Int(obj, "delay", &delayAni);
    env->Object_GetPropertyByName_Double(obj, "begin", &beginAni);
    env->Object_GetPropertyByName_Double(obj, "end", &endAni);
    env->Object_GetPropertyByName_Ref(obj, "easing", &easingAni);
    env->Object_GetPropertyByName_Ref(obj, "fill", &fillAni);
    env->Object_GetPropertyByName_Ref(obj, "direction", &directionAni);
    std::string easing = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(easingAni));
    std::string fill = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(fillAni));
    std::string direction = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(directionAni));
    option->duration = durationAni > 0 ? durationAni : 0;
    option->iterations = iterationsAni >= -1 ? iterationsAni : 1;
    option->begin = beginAni;
    option->delay = delayAni;
    option->end = endAni;
    option->easing = easing;
    option->fill = fill;
    option->direction = direction;
}

static void SetOnfinish([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object callbackObj)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    ani_ref onfinishRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onfinishGlobalRef;
    env->GlobalReference_Create(onfinishRef, &onfinishGlobalRef);
    animatorResult->SetOnfinishRef(onfinishGlobalRef);
    animator->ClearStopListeners();
    animator->AddStopListener([env, onfinishGlobalRef, id = animator->GetId()] {
        auto fnObj = reinterpret_cast<ani_fn_object>(onfinishGlobalRef);
        ani_ref result;
        env->FunctionalObject_Call(fnObj, 0, NULL, &result);
    });
    return;
}

static RefPtr<Motion> ParseOptionToMotion(const std::shared_ptr<Napi::AnimatorOption> &option)
{
    const auto &curveStr = option->easing;
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
    for (auto &param : paramsVector) {
        OHOS::Ace::Framework::RemoveHeadTailSpace(param);
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

static ani_object createDouble(ani_env *env, double value)
{
    static const char *className = "std.core.Double";
    ani_class persion_cls;
    if (ANI_OK != env->FindClass(className, &persion_cls)) {
        return nullptr;
    }
    ani_method personInfoCtor;
    if (ANI_OK != env->Class_FindMethod(persion_cls, "<ctor>", "d:", &personInfoCtor)) {
        return nullptr;
    }
    ani_object personInfoObj;
    if (ANI_OK != env->Object_New(persion_cls, personInfoCtor, &personInfoObj, ani_double(value))) {
        return nullptr;
    }
    return personInfoObj;
}

static void SetOnframe([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object callbackObj)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    animator->ClearInterpolators();
    ani_ref onframeRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onframeGlobalRef;
    env->GlobalReference_Create(onframeRef, &onframeGlobalRef);
    animatorResult->SetOnframeRef(onframeGlobalRef);
    auto onFrameCallback = [env,
                               onframeGlobalRef,
                               id = animator->GetId(),
                               weakOption = std::weak_ptr<Napi::AnimatorOption>(animatorResult->GetAnimatorOption())](
                               double value) {
        auto fnObj = reinterpret_cast<ani_fn_object>(onframeGlobalRef);
        auto option = weakOption.lock();
        auto args = createDouble(env, value);
        if (args == nullptr) {
            return;
        }
        ani_ref result;
        auto obj = reinterpret_cast<ani_ref>(args);
        std::vector<ani_ref> tmp = {reinterpret_cast<ani_ref>(obj)};
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
    };
    RefPtr<Animation<double>> animation;
    RefPtr<Motion> motion = ParseOptionToMotion(option);
    if (motion) {
        motion->AddListener(onFrameCallback);
        animatorResult->SetMotion(motion);
    } else {
        auto curve = OHOS::Ace::Framework::CreateCurve(option->easing);
        animation = AceType::MakeRefPtr<CurveAnimation<double>>(option->begin, option->end, curve);
        animation->AddListener(onFrameCallback);
        animator->AddInterpolator(animation);
        animatorResult->SetMotion(nullptr);
    }
    if (!animator->HasScheduler()) {
        animator->AttachSchedulerOnContainer();
    }
    return;
}

static void SetOncancel([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object callbackObj)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    ani_ref oncancelRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref oncancelGlobalRef;
    env->GlobalReference_Create(oncancelRef, &oncancelGlobalRef);
    animatorResult->SetOncancelRef(oncancelGlobalRef);
    animator->ClearIdleListeners();
    animator->AddIdleListener([env, oncancelGlobalRef] {
        auto fnObj = reinterpret_cast<ani_fn_object>(oncancelGlobalRef);
        ani_ref result;
        env->FunctionalObject_Call(fnObj, 0, NULL, &result);
    });
    return;
}

static void SetOnrepeat([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object callbackObj)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }

    ani_ref onrepeatRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onrepeatGlobalRef;
    env->GlobalReference_Create(onrepeatRef, &onrepeatGlobalRef);
    animatorResult->SetOnrepeatRef(onrepeatGlobalRef);
    animator->ClearRepeatListeners();
    animator->AddRepeatListener([env, onrepeatGlobalRef] {
        auto fnObj = reinterpret_cast<ani_fn_object>(onrepeatGlobalRef);
        ani_ref result;
        env->FunctionalObject_Call(fnObj, 0, NULL, &result);
    });
    return;
}

static ani_object AnimatorTransferStatic(ani_env *aniEnv, ani_object, ani_object input)
{
    ani_object animatorObj = {};
    static const char *className = "@ohos.animator.AnimatorResultInner";
    ani_class cls;
    if (aniEnv == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "[ANI] aniEnv is null");
        return animatorObj;
    }
    if (ANI_OK != aniEnv->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find class fail");
        return animatorObj;
    }

    ani_method ctor;
    if (ANI_OK != aniEnv->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find method fail");
        return animatorObj;
    }

    void *unwrapResult = nullptr;
    bool success = arkts_esvalue_unwrap(aniEnv, input, &unwrapResult);
    if (!success) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "[ANI] failed to unwrap");
        return nullptr;
    }
    if (unwrapResult == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "[ANI] null unwrapResult");
        return nullptr;
    }
    auto animatorResultPre = reinterpret_cast<OHOS::Ace::Napi::AnimatorResult*>(unwrapResult);
    if (animatorResultPre == nullptr) {
        TAG_LOGE(AceLogTag::ACE_ANIMATION, "[ANI] null animatorResult");
        return nullptr;
    }

    auto option = animatorResultPre->GetAnimatorOption();
    auto motion = animatorResultPre->GetMotion();
    auto animator = animatorResultPre->GetAnimator();
    auto animatorResult = new AnimatorResult();
    animatorResult->SetMotion(motion);
    animatorResult->SetAnimatorOption(option);
    animatorResult->SetAnimator(animator);
    aniEnv->Object_New(cls, ctor, &animatorObj, reinterpret_cast<ani_long>(animatorResult));
    return animatorObj;
}

void ParseExpectedFrameRateRange(ani_env *env, ani_object objOption,
    FrameRateRange& frameRateRange)
{
    static const char *className = "@ohos.arkui.component.Common.ExpectedFrameRateRange";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return;
    }

    ani_boolean isInstance;
    if (ANI_OK != env->Object_InstanceOf(objOption, cls, &isInstance)) {
        return;
    }

    int32_t minFPS = 0;
    int32_t maxFPS = 0;
    int32_t expectedFPS = 0;

    ani_double minAni;
    ani_double maxAni;
    ani_double expectedAni;
    env->Object_GetPropertyByName_Double(objOption, "min", &minAni);
    env->Object_GetPropertyByName_Double(objOption, "max", &maxAni);
    env->Object_GetPropertyByName_Double(objOption, "expected", &expectedAni);

    minFPS = static_cast<int32_t>(minAni);
    maxFPS = static_cast<int32_t>(maxAni);
    expectedFPS = static_cast<int32_t>(expectedAni);
    frameRateRange.Set(minFPS, maxFPS, expectedFPS);
}

// ani
static void JSSetExpectedFrameRateRange(ani_env *env, ani_object obj, ani_object objOption)
{
    auto animatorResult = GetAnimatorResult(env, obj);
    if (animatorResult == nullptr) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    if (!animator->HasScheduler()) {
        auto result = animator->AttachSchedulerOnContainer();
        if (!result) {
            return;
        }
    }
    FrameRateRange frameRateRange;
    ParseExpectedFrameRateRange(env, objOption, frameRateRange);
    animator->SetExpectedFrameRateRange(frameRateRange);
}

ani_object ANICreate(ani_env *env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object aniOption)
{
    ani_object animatorObj = {};
    static const char *className = "@ohos.animator.AnimatorResultInner";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find class fail");
        return animatorObj;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find method fail");
        return animatorObj;
    }

    // create animator and construct animatorResult
    auto option = std::make_shared<Napi::AnimatorOption>();
    ParseAnimatorOption(env, aniOption, option);
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] option is %{public}s", option->ToString().c_str());
    auto animator = CREATE_ANIMATOR("ohos.animator");
    animator->AttachSchedulerOnContainer();
    auto animatorResult = new AnimatorResult(animator, option);

    // bind end with front object
    if (ANI_OK != env->Object_New(cls, ctor, &animatorObj, reinterpret_cast<ani_long>(animatorResult))) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] create animatorResult fail");
        delete animatorResult;
        return animatorObj;
    }

    return animatorObj;
}

static void ANIReset(ani_env *env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object options)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        return;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
    ParseAnimatorOption(env, options, option);
    animator->ClearInterpolators();
    animator->ResetIsReverse();
    animatorResult->ApplyOption();
    ani_ref onframeRef = animatorResult->GetOnframeRef();
    if (onframeRef) {
        auto onFrameCallback = [env, onframeRef, id = animator->GetId()](double value) {
            auto fnObj = reinterpret_cast<ani_fn_object>(onframeRef);
            auto args = createDouble(env, value);
            if (args == nullptr) {
                return;
            }
            ani_ref result;
            auto obj = reinterpret_cast<ani_ref>(args);
            std::vector<ani_ref> tmp = {reinterpret_cast<ani_ref>(obj)};
            env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
        };
        RefPtr<Animation<double>> animation;
        RefPtr<Motion> motion = ParseOptionToMotion(option);
        if (motion) {
            motion->AddListener(onFrameCallback);
            animatorResult->SetMotion(motion);
        } else {
            auto curve = Framework::CreateCurve(option->easing);
            animation = AceType::MakeRefPtr<CurveAnimation<double>>(option->begin, option->end, curve);
            animation->AddListener(onFrameCallback);
            animator->AddInterpolator(animation);
            animatorResult->SetMotion(nullptr);
        }
    }
    return;
}

static void ANIUpdate(ani_env *env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object options)
{
    ANIReset(env, object, options);
}

bool GetIsUndefinedObject(ani_env *env, ani_ref object_ref)
{
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(object_ref, &isUndefined)) {
        return false;
    }
    return (bool)isUndefined;
}

void ANICreateSimpleAnimatorOptionsWithParam(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_double start,  [[maybe_unused]] ani_double end)
{
    JsSimpleAnimatorOption* simpleAnimatorOption = new JsSimpleAnimatorOption();
    simpleAnimatorOption->SetBegin(static_cast<double>(start));
    simpleAnimatorOption->SetEnd(static_cast<double>(end));
    env->Object_SetPropertyByName_Long(
        object, "SimpleAnimatorOptionsResult", reinterpret_cast<ani_long>(simpleAnimatorOption));
}

ani_object ANISetSimpleAnimatorDuration(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_int duration)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    simpleAnimatorOption->SetDuration(static_cast<int32_t>(duration));
    return object;
}

ani_object ANISetSimpleAnimatorEasing(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_string easing)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    auto easingStr = ANIUtils_ANIStringToStdString(env, easing);
    simpleAnimatorOption->SetEasing(easingStr);
    return object;
}

ani_object ANISetSimpleAnimatorDelay(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_int delay)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    simpleAnimatorOption->SetDelay(static_cast<int32_t>(delay));
    return object;
}

ani_object ANISetSimpleAnimatorFill(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_object fillMode)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    ani_enum fillModerEnum;
    if (ANI_OK != env->FindEnum("arkui.component.enums.FillMode", &fillModerEnum)) {
        return object;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(fillMode), fillModerEnum, &isEnum)) {
        return object;
    }

    ani_int fillModeInt;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(fillMode), &fillModeInt)) {
        return object;
    }
    simpleAnimatorOption->SetFill(static_cast<FillMode>(fillModeInt));
    return object;
}

ani_object ANISetSimpleAnimatorDirection(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_object playMode)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    ani_enum PlayModeEnum;
    if (ANI_OK != env->FindEnum("arkui.component.enums.PlayMode", &PlayModeEnum)) {
        return object;
    }
    ani_boolean isEnum;
    if (ANI_OK != env->Object_InstanceOf(static_cast<ani_object>(playMode), PlayModeEnum, &isEnum)) {
        return object;
    }

    ani_int playModInt;
    if (ANI_OK != env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(playMode), &playModInt)) {
        return object;
    }
    switch (playModInt) {
        case ANIMATION_DIRETION_NORMAL_NUM:
            simpleAnimatorOption->SetDirection(AnimationDirection::NORMAL);
            break;
        case ANIMATION_DIRETION_REVERSE_NUM:
            simpleAnimatorOption->SetDirection(AnimationDirection::REVERSE);
            break;
        case ANIMATION_DIRETION_ALTERNATE_NUM:
            simpleAnimatorOption->SetDirection(AnimationDirection::ALTERNATE);
            break;
        case ANIMATION_DIRETION_ALTERNATE_REVERSE_NUM:
            simpleAnimatorOption->SetDirection(AnimationDirection::ALTERNATE_REVERSE);
            break;
        default:
            simpleAnimatorOption->SetDirection(AnimationDirection::NORMAL);
            break;
    }
    return object;
}

ani_object ANISetSimpleAnimatorIterations(ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_int iteration)
{
    auto simpleAnimatorOption = GetJsSimpleAnimatorOption(env, object);
    if (simpleAnimatorOption == nullptr) {
        return object;
    }
    simpleAnimatorOption->SetIterations(static_cast<int32_t>(iteration));
    return object;
}

ani_status BindAnimator(ani_env *env)
{
    static const char *className = "@ohos.animator.Animator";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] Bind Animator fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"create",
            nullptr,
            reinterpret_cast<void *>(ANICreate)},
    };

    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] Bind Animator static method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status BindAnimatorResult(ani_env *env)
{
    static const char *className = "@ohos.animator.AnimatorResultInner";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind animator result fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"play", ":", reinterpret_cast<void *>(JSPlay)},
        ani_native_function{"reverse", ":", reinterpret_cast<void *>(JSReverse)},
        ani_native_function{"cancel", ":", reinterpret_cast<void *>(JSCancel)},
        ani_native_function{"pause", ":", reinterpret_cast<void *>(JSPause)},
        ani_native_function{"finish", ":", reinterpret_cast<void *>(JSFinish)},
        ani_native_function{"setOnFinish", nullptr, reinterpret_cast<void *>(SetOnfinish)},
        ani_native_function{"setOnCancel", nullptr, reinterpret_cast<void *>(SetOncancel)},
        ani_native_function{"setOnRepeat", nullptr, reinterpret_cast<void *>(SetOnrepeat)},
        ani_native_function{"setOnFrame", nullptr, reinterpret_cast<void *>(SetOnframe)},
        ani_native_function{"update", "C{@ohos.animator.AnimatorOptions}:", reinterpret_cast<void *>(ANIUpdate)},
        ani_native_function{"reset", "X{C{@ohos.animator.AnimatorOptions}C{@ohos.animator.SimpleAnimatorOptions}}:",
            reinterpret_cast<void *>(ANIReset)},
        ani_native_function{"setExpectedFrameRateRange", nullptr,
            reinterpret_cast<void *>(JSSetExpectedFrameRateRange)},
    };

    std::array staticMethods = {
        ani_native_function{ "nativeTransferStatic", nullptr, reinterpret_cast<void*>(AnimatorTransferStatic)}
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind native method fail");
        return ANI_ERROR;
    };
    if (ANI_OK != env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind static native static method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status BindSimpleAnimatorOptions(ani_env *env)
{
    static const char *className = "@ohos.animator.SimpleAnimatorOptions";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind SimpleAnimatorOptions result fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {
            "<ctor>", "dd:", reinterpret_cast<void*>(ANICreateSimpleAnimatorOptionsWithParam) },
        ani_native_function {
            "duration", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorDuration) },
        ani_native_function {
            "easing", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorEasing) },
        ani_native_function {
            "delay", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorDelay) },
        ani_native_function {
            "fill", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorFill) },
        ani_native_function {
            "direction", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorDirection) },
        ani_native_function {
            "iterations", nullptr, reinterpret_cast<void*>(ANISetSimpleAnimatorIterations) },
        };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind SimpleAnimatorOptions native method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}
}  // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    // bind Animator class.
    ani_status retBindAnimator = OHOS::Ace::Ani::BindAnimator(env);
    if (retBindAnimator != ANI_OK) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_ANIMATION, "[ANI] BindAnimator fail");
        return retBindAnimator;
    }
    ani_status retBindResult = OHOS::Ace::Ani::BindAnimatorResult(env);
    if (retBindResult != ANI_OK) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_ANIMATION, "[ANI] BindAnimatorResult fail");
        return retBindResult;
    }
    ani_status retBindSimpleAnimatorOptions = OHOS::Ace::Ani::BindSimpleAnimatorOptions(env);
    if (retBindSimpleAnimatorOptions != ANI_OK) {
        TAG_LOGI(OHOS::Ace::AceLogTag::ACE_ANIMATION, "[ANI] retBindSimpleAnimatorOptions fail");
        return retBindAnimator;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
