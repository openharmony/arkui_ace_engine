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

#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animation.h"
#include "core/animation/animator.h"
#include "core/animation/curve.h"
#include "core/animation/spring_motion.h"
namespace OHOS::Ace::Ani {
constexpr size_t INTERPOLATING_SPRING_PARAMS_SIZE = 4;
constexpr char INTERPOLATING_SPRING[] = "interpolating-spring";

struct AnimatorOption {
    int32_t duration = 0;
    int32_t delay = 0;
    int32_t iterations = 0;
    double begin = 0.0;
    double end = 0.0;
    std::string easing = "ease";
    std::string fill = "none";
    std::string direction = "normal";

    std::string ToString() const
    {
        return "AnimatorOption:[" + std::to_string(duration) + "," + std::to_string(delay) + "," +
               std::to_string(iterations) + "," + std::to_string(begin) + "," + std::to_string(end) + "," + easing +
               "," + fill + "," + direction + "]";
    }
};

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

class AnimatorResult final {
public:
    AnimatorResult() = default;
    AnimatorResult(RefPtr<Animator> &animator, std::shared_ptr<AnimatorOption> &option)
        : animator_(animator), option_(option)
    {
        ApplyOption();
    }
    ~AnimatorResult() = default;

    RefPtr<Animator> GetAnimator() const
    {
        return animator_;
    }

    std::shared_ptr<AnimatorOption> GetAnimatorOption() const
    {
        return option_;
    }

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

    const RefPtr<Motion> &GetMotion() const
    {
        return motion_;
    }

    void SetMotion(const RefPtr<Motion> &motion)
    {
        motion_ = motion;
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
    RefPtr<Animator> animator_;
    RefPtr<Motion> motion_;
    std::shared_ptr<AnimatorOption> option_;
    ani_ref onframe_ = nullptr;
    ani_ref onfinish_ = nullptr;
    ani_ref oncancel_ = nullptr;
    ani_ref onrepeat_ = nullptr;
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

static AnimatorResult *GetAnimatorResult(ani_env *env, ani_object obj)
{
    ani_long animatorResultForAni;
    if (ANI_OK != env->Object_GetFieldByName_Long(obj, "animatorResult", &animatorResultForAni)) {
        return nullptr;
    }
    return reinterpret_cast<AnimatorResult *>(animatorResultForAni);
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

static void ParseAnimatorOption(ani_env *env, ani_object obj, std::shared_ptr<AnimatorOption> option)
{
    ani_double durationAni;
    ani_double iterationsAni;
    ani_double delayAni;
    ani_ref easingAni;
    ani_ref fillAni;
    ani_ref directionAni;
    ani_double beginAni;
    ani_double endAni;

    env->Object_GetPropertyByName_Double(obj, "duration", &durationAni);
    env->Object_GetPropertyByName_Double(obj, "iterations", &iterationsAni);
    env->Object_GetPropertyByName_Double(obj, "delay", &delayAni);
    env->Object_GetPropertyByName_Double(obj, "begin", &beginAni);
    env->Object_GetPropertyByName_Double(obj, "end", &endAni);
    env->Object_GetPropertyByName_Ref(obj, "easing", &easingAni);
    env->Object_GetPropertyByName_Ref(obj, "fill", &fillAni);
    env->Object_GetPropertyByName_Ref(obj, "direction", &directionAni);
    std::string easing = "ease";
    std::string fill = "none";
    std::string direction = "normal";
    easing = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(easingAni));
    fill = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(fillAni));
    direction = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(directionAni));

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

static RefPtr<Motion> ParseOptionToMotion(const std::shared_ptr<AnimatorOption> &option)
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
    static const char *className = "Lstd/core/Double;";
    ani_class persion_cls;
    if (ANI_OK != env->FindClass(className, &persion_cls)) {
        return nullptr;
    }
    ani_method personInfoCtor;
    if (ANI_OK != env->Class_FindMethod(persion_cls, "<ctor>", "D:V", &personInfoCtor)) {
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
                               weakOption = std::weak_ptr<AnimatorOption>(animatorResult->GetAnimatorOption())](
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

void ParseExpectedFrameRateRange(ani_env *env, ani_object objOption,
    FrameRateRange& frameRateRange)
{
    static const char *className = "L@ohos/arkui/component/Common/ExpectedFrameRateRange;";
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
    ani_object animator_obj = {};
    static const char *className = "L@ohos/animator/AnimatorResultInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find class fail");
        return animator_obj;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] find method fail");
        return animator_obj;
    }

    // create animatot and construct animatorResult
    auto option = std::make_shared<AnimatorOption>();
    ParseAnimatorOption(env, aniOption, option);
    TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] option is %{public}s", option->ToString().c_str());
    auto animator = CREATE_ANIMATOR("ohos.animator");
    animator->AttachSchedulerOnContainer();
    auto animatorResult = new AnimatorResult(animator, option);

    // bind end with front object
    if (ANI_OK != env->Object_New(cls, ctor, &animator_obj, reinterpret_cast<ani_long>(animatorResult))) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] create animatorResult fail");
        return animator_obj;
    }

    return animator_obj;
}

static void ANIReset(ani_env *env, [[maybe_unused]] ani_object object, [[maybe_unused]] ani_object options)
{
    AnimatorResult *animatorResult = nullptr;
    animatorResult = GetAnimatorResult(env, object);
    if (!animatorResult) {
        return;
    }
    auto option = std::make_shared<AnimatorOption>();
    ParseAnimatorOption(env, options, option);
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        return;
    }
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

ani_status BindAnimator(ani_env *env)
{
    static const char *className = "L@ohos/animator/Animator;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] Bind Animator fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"create",
            "L@ohos/animator/AnimatorOptions;:L@ohos/animator/AnimatorResult;",
            reinterpret_cast<void *>(ANICreate)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] Bind Animator method fail");
        return ANI_ERROR;
    };
    return ANI_OK;
}

ani_status BindAnimatorResult(ani_env *env)
{
    static const char *className = "L@ohos/animator/AnimatorResultInner;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind animator result fail");
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function{"play", ":V", reinterpret_cast<void *>(JSPlay)},
        ani_native_function{"reverse", ":V", reinterpret_cast<void *>(JSReverse)},
        ani_native_function{"cancel", ":V", reinterpret_cast<void *>(JSCancel)},
        ani_native_function{"pause", ":V", reinterpret_cast<void *>(JSPause)},
        ani_native_function{"finish", ":V", reinterpret_cast<void *>(JSFinish)},
        ani_native_function{"setOnFinish", nullptr, reinterpret_cast<void *>(SetOnfinish)},
        ani_native_function{"setOnCancel", nullptr, reinterpret_cast<void *>(SetOncancel)},
        ani_native_function{"setOnRepeat", nullptr, reinterpret_cast<void *>(SetOnrepeat)},
        ani_native_function{"setOnFrame", nullptr, reinterpret_cast<void *>(SetOnframe)},
        ani_native_function{"update", "L@ohos/animator/AnimatorOptions;:V", reinterpret_cast<void *>(ANIUpdate)},
        ani_native_function{"reset", "L@ohos/animator/AnimatorOptions;:V", reinterpret_cast<void *>(ANIReset)},
        ani_native_function{"setExpectedFrameRateRange", nullptr,
            reinterpret_cast<void *>(JSSetExpectedFrameRateRange)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(cls, methods.data(), methods.size())) {
        TAG_LOGI(AceLogTag::ACE_ANIMATION, "[ANI] bind native method fail");
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

    *result = ANI_VERSION_1;
    return ANI_OK;
}
