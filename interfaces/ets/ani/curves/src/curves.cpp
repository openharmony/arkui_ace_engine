/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <ani.h>
#include <array>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <future>
#include <thread>
#include <map>
#include <string>

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/base/log/log_wrapper.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/core/common/container.h"
#include "frameworks/core/animation/curve.h"
#include "frameworks/core/animation/spring_curve.h"
#include "test/mock/interfaces/mock_ace_forward_compatibility.cpp"
namespace {
struct CurvesObj {
    OHOS::Ace::RefPtr<OHOS::Ace::Curve> curve;
};

typedef enum Curve {
    Linear = 0,
    Ease = 1,
    EaseIn = 2,
    EaseOut = 3,
    EaseInOut = 4,
    FastOutSlowIn = 5,
    LinearOutSlowIn = 6,
    FastOutLinearIn = 7,
    ExtremeDeceleration = 8,
    Sharp = 9,
    Rhythm = 10,
    Smooth = 11,
    Friction = 12,
} Curve;

const char* ICURVE_CLASS_NAME = "@ohos.curves.curves.ICurveImpl";
}

std::string GetCubicBezierCurveString(ani_double x1, ani_double y1, ani_double x2, ani_double y2)
{
    float x1Value = 0.0f;
    float y1Value = 0.0f;
    float x2Value = 0.0f;
    float y2Value = 0.0f;
    if (!std::isnan(x1)) {
        x1Value = static_cast<float>(x1);
    }
    if (!std::isnan(y1)) {
        y1Value = static_cast<float>(y1);
    }
    if (!std::isnan(x2)) {
        x2Value = static_cast<float>(x2);
    }
    if (!std::isnan(y2)) {
        y2Value = static_cast<float>(y2);
    }
    x1Value = std::clamp(x1Value, 0.0f, 1.0f);
    x2Value = std::clamp(x2Value, 0.0f, 1.0f);

    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::CubicCurve>(x1Value, y1Value, x2Value, y2Value);
    return curve->ToString();
}

std::string GetSpringMotionCurveString(ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    float responseValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
    float dampingFractionValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
    float overlapDurationValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
    
    ani_boolean isUndefinedResponse = true;
    env->Reference_IsUndefined(response, &isUndefinedResponse);
    if (!isUndefinedResponse) {
        ani_double resultResponse;
        if (ANI_OK == env->Object_CallMethodByName_Double(response, "unboxed", nullptr, &resultResponse)) {
            double value = static_cast<double>(resultResponse);
            responseValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedDampingFraction = true;
    env->Reference_IsUndefined(dampingFraction, &isUndefinedDampingFraction);
    if (!isUndefinedDampingFraction) {
        ani_double resultDampingFraction;
        if (ANI_OK == env->Object_CallMethodByName_Double(dampingFraction, "unboxed",
            nullptr, &resultDampingFraction)) {
            double value = static_cast<double>(resultDampingFraction);
            dampingFractionValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedOverlapDuration = true;
    env->Reference_IsUndefined(overlapDuration, &isUndefinedOverlapDuration);
    if (!isUndefinedOverlapDuration) {
        ani_double resultOverlapDuration;
        if (ANI_OK == env->Object_CallMethodByName_Double(overlapDuration, "unboxed",
            nullptr, &resultOverlapDuration)) {
            double value = static_cast<double>(resultOverlapDuration);
            overlapDurationValue = static_cast<float>(value);
        }
    }
    if (OHOS::Ace::LessOrEqual(responseValue, 0)) {
        responseValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
    }
    if (OHOS::Ace::LessNotEqual(dampingFractionValue, 0)) {
        dampingFractionValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
    }
    if (OHOS::Ace::LessNotEqual(overlapDurationValue, 0)) {
        overlapDurationValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
    }
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::ResponsiveSpringMotion>(
        responseValue, dampingFractionValue, overlapDurationValue);
    return curve->ToString();
}

std::string GetCurvesInitInternalMap(int curveType)
{
    static std::map<int, std::string> curveMap = {
        { static_cast<int>(Curve::Linear), "linear" },
        { static_cast<int>(Curve::Ease), "ease" },
        { static_cast<int>(Curve::EaseIn), "ease-in" },
        { static_cast<int>(Curve::EaseOut), "ease-out" },
        { static_cast<int>(Curve::EaseInOut), "ease-in-out" },
        { static_cast<int>(Curve::FastOutSlowIn), "fast-out-slow-in" },
        { static_cast<int>(Curve::LinearOutSlowIn), "linear-out-slow-in" },
        { static_cast<int>(Curve::FastOutLinearIn), "fast-out-linear-in" },
        { static_cast<int>(Curve::ExtremeDeceleration), "extreme-deceleration" },
        { static_cast<int>(Curve::Sharp), "sharp" },
        { static_cast<int>(Curve::Rhythm), "rhythm" },
        { static_cast<int>(Curve::Smooth), "smooth" },
        { static_cast<int>(Curve::Friction), "friction" },
    };

    auto curveString = OHOS::Ace::Framework::CreateCurve(curveMap[curveType]);
    return curveString->ToString();
}

static CurvesObj* unwrapp(ani_env *env, ani_object object)
{
    ani_long curvesObj;
    if (ANI_OK != env->Object_GetFieldByName_Long(object, "nativeContext", &curvesObj)) {
        return nullptr;
    }
    return reinterpret_cast<CurvesObj*>(curvesObj);
}

static ani_double Interpolate(ani_env* env, ani_object object, ani_double fraction)
{
    auto curveObject = unwrapp(env, object);
    auto curveInterpolate = curveObject->curve;
    float time = std::clamp(static_cast<float>(fraction), 0.0f, 1.0f);
    ani_double curveValue = static_cast<ani_double>(curveInterpolate->Move(time));
    return curveValue;
}

static ani_object CubicBezierCurve(ani_env *env,
    ani_double x1, ani_double y1, ani_double x2, ani_double y2)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    CurvesObj* cubicBezierCurve = new CurvesObj();
    std::string curveString = GetCubicBezierCurveString(x1, y1, x2, y2);
    cubicBezierCurve->curve = OHOS::Ace::Framework::CreateCurve(curveString);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(cubicBezierCurve))) {
        return nullptr;
    }
    return curve_object;
}

static ani_object SpringCurve(ani_env* env,
    ani_double velocity, ani_double mass, ani_double stiffness, ani_double damping)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    if (OHOS::Ace::LessOrEqual(mass, 0)) {
        mass = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(stiffness, 0)) {
        stiffness = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(damping, 0)) {
        damping = 1.0;
    }

    CurvesObj* springCurve = new CurvesObj();
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::SpringCurve>(velocity, mass, stiffness, damping);
    std::string curveString = curve->ToString();
    springCurve->curve = OHOS::Ace::Framework::CreateCurve(curveString);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(springCurve))) {
        return nullptr;
    }
    return curve_object;
}

std::string GetSpringResponsiveMotionCurveString(ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    float responseValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
    float dampingFractionValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
    float overlapDurationValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
    
    ani_boolean isUndefinedResponse = true;
    env->Reference_IsUndefined(response, &isUndefinedResponse);
    if (!isUndefinedResponse) {
        ani_double resultResponse;
        if (ANI_OK == env->Object_CallMethodByName_Double(response, "unboxed", nullptr, &resultResponse)) {
            double value = static_cast<double>(resultResponse);
            responseValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedDampingFraction = true;
    env->Reference_IsUndefined(dampingFraction, &isUndefinedDampingFraction);
    if (!isUndefinedDampingFraction) {
        ani_double resultDampingFraction;
        if (ANI_OK == env->Object_CallMethodByName_Double(dampingFraction, "unboxed",
            nullptr, &resultDampingFraction)) {
            double value = static_cast<double>(resultDampingFraction);
            dampingFractionValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedOverlapDuration = true;
    env->Reference_IsUndefined(overlapDuration, &isUndefinedOverlapDuration);
    if (!isUndefinedOverlapDuration) {
        ani_double resultOverlapDuration;
        if (ANI_OK == env->Object_CallMethodByName_Double(overlapDuration, "unboxed",
            nullptr, &resultOverlapDuration)) {
            double value = static_cast<double>(resultOverlapDuration);
            overlapDurationValue = static_cast<float>(value);
        }
    }
    if (OHOS::Ace::LessOrEqual(responseValue, 0)) {
        responseValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
    }
    if (OHOS::Ace::LessNotEqual(dampingFractionValue, 0)) {
        dampingFractionValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
    }
    if (OHOS::Ace::LessNotEqual(overlapDurationValue, 0)) {
        overlapDurationValue = OHOS::Ace::ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
    }
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::ResponsiveSpringMotion>(
        responseValue, dampingFractionValue, overlapDurationValue);
    return curve->ToString();
}

static ani_object SpringResponsiveMotion(ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    CurvesObj* springResponsiveMotion = new CurvesObj();
    std::string curveString = GetSpringResponsiveMotionCurveString(env, response, dampingFraction, overlapDuration);
    springResponsiveMotion->curve = OHOS::Ace::Framework::CreateCurve(curveString);
    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(springResponsiveMotion))) {
        return nullptr;
    }

    return curve_object;
}

static ani_object SpringMotion(ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    CurvesObj* springMotion = new CurvesObj();
    std::string curveString = GetSpringMotionCurveString(env, response, dampingFraction, overlapDuration);
    springMotion->curve = OHOS::Ace::Framework::CreateCurve(curveString);
    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(springMotion))) {
        return nullptr;
    }
    return curve_object;
}

static ani_object InitCurve(ani_env* env, ani_enum_item enumItem)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(enumItem, &isUndefined);
    ani_int curveType = Curve::Linear;
    if (isUndefined) {
        curveType = Curve::Linear;
    } else {
        if (ANI_OK != env->EnumItem_GetValue_Int(enumItem, &curveType)) {
            LOGW("InitCurve input enum is invalid");
            curveType = Curve::Linear;
        }
    }
    std::string curveString = GetCurvesInitInternalMap(curveType);

    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        LOGW("InitCurve not found class");
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGW("InitCurve get ctor failed");
        return nullptr;
    }
    CurvesObj* curvesInitInternal = new CurvesObj();
    curvesInitInternal->curve = OHOS::Ace::Framework::CreateCurve(curveString);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(curvesInitInternal))) {
        return nullptr;
    }
    return curve_object;
}

static ani_object InterpolatingSpring(ani_env* env,
    ani_double velocity, ani_double mass, ani_double stiffness, ani_double damping)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        LOGW("InterpolatingSpring not found class");
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGW("InterpolatingSpring get ctor failed");
        return nullptr;
    }

    if (OHOS::Ace::LessOrEqual(mass, 0)) {
        mass = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(stiffness, 0)) {
        stiffness = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(damping, 0)) {
        damping = 1.0;
    }
    auto InterpolatingSpringCurve =
        OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::InterpolatingSpring>(velocity, mass, stiffness, damping);
    std::string curveString = InterpolatingSpringCurve->ToString();
    CurvesObj* interpolatingCurve = new CurvesObj();
    interpolatingCurve->curve = OHOS::Ace::Framework::CreateCurve(curveString);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(interpolatingCurve))) {
        return nullptr;
    }

    return curve_object;
}

static ani_object StepsCurve(ani_env* env, ani_int count, ani_boolean end)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        LOGW("StepsCurve not found class");
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGW("StepsCurve get ctor failed");
        return nullptr;
    }

    if (count <= 1) {
        count = 1;
    }
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::StepsCurve>(count);
    if (end) {
        curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::StepsCurve>(count, OHOS::Ace::StepsCurvePosition::END);
    } else {
        curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::StepsCurve>(count, OHOS::Ace::StepsCurvePosition::START);
    }

    std::string curveString = curve->ToString();
    CurvesObj* interpolatingCurve = new CurvesObj();
    interpolatingCurve->curve = OHOS::Ace::Framework::CreateCurve(curveString);

    ani_object curve_object;
    env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(interpolatingCurve));
    return curve_object;
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

static ani_object CustomCurve(ani_env* env, ani_object callbackObj)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &cls)) {
        LOGW("CustomCurve not found class");
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGW("CustomCurve get ctor failed");
        return nullptr;
    }

    ani_ref onframeRef = reinterpret_cast<ani_ref>(callbackObj);
    ani_ref onframeGlobalRef;
    env->GlobalReference_Create(onframeRef, &onframeGlobalRef);
    auto onFrameCallback = [env,
                            onframeGlobalRef](
                            double value) -> double {
        auto fnObj = reinterpret_cast<ani_fn_object>(onframeGlobalRef);
        auto args = createDouble(env, value);
        if (args == nullptr) {
            return 0.0f;
        }
        ani_ref result;
        auto obj = reinterpret_cast<ani_ref>(args);
        std::vector<ani_ref> tmp = {reinterpret_cast<ani_ref>(obj)};
        env->FunctionalObject_Call(fnObj, tmp.size(), tmp.data(), &result);
        auto aniObj = reinterpret_cast<ani_object>(result);
        ani_double valueAniDouble = 0.0;
        env->Object_CallMethodByName_Double(aniObj, "unboxed", ":d", &valueAniDouble);
        return static_cast<float>(valueAniDouble);
    };

    auto customCurve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::CustomCurve>(onFrameCallback);
    CurvesObj* interpolatingCurve = new CurvesObj();
    interpolatingCurve->curve = customCurve;

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(interpolatingCurve))) {
        return nullptr;
    }
    return curve_object;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("@ohos.curves.curves", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"cubicBezierCurve", nullptr, reinterpret_cast<void *>(CubicBezierCurve)},
        ani_native_function {"springMotion", nullptr, reinterpret_cast<void *>(SpringMotion)},
        ani_native_function {"initCurve", nullptr, reinterpret_cast<void*>(InitCurve)},
        ani_native_function {"interpolatingSpring", nullptr, reinterpret_cast<void*>(InterpolatingSpring)},
        ani_native_function {"springCurve", nullptr, reinterpret_cast<void*>(SpringCurve)},
        ani_native_function {"responsiveSpringMotion", nullptr, reinterpret_cast<void*>(SpringResponsiveMotion)},
        ani_native_function {"stepsCurve", nullptr, reinterpret_cast<void*>(StepsCurve)},
        ani_native_function {"customCurve", nullptr, reinterpret_cast<void*>(CustomCurve)}
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    ani_class clsCurves;
    if (ANI_OK != env->FindClass(ICURVE_CLASS_NAME, &clsCurves)) {
        return ANI_ERROR;
    }
    std::array methodsCurves = {
        ani_native_function {"interpolate", nullptr, reinterpret_cast<void *>(Interpolate)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(clsCurves, methodsCurves.data(), methodsCurves.size())) {
        return ANI_ERROR;
    };

    *result = ANI_VERSION_1;
    return ANI_OK;
}
