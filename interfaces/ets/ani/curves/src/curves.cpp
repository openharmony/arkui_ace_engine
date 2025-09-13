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
    std::function<ani_double(ani_env*, ani_object, ani_double)> interpolate;
    std::string curveString;
    int32_t pageId;
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

}

OHOS::Ace::RefPtr<OHOS::Ace::Framework::JsAcePage> GetStagingPage(int32_t instanceId)
{
    auto engine = OHOS::Ace::EngineHelper::GetEngine(instanceId);
    auto jsiEngine = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::Framework::JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        return nullptr;
    }
    return engineInstance->GetStagingPage();
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
        if (ANI_OK == env->Object_CallMethodByName_Double(response, "doubleValue", nullptr, &resultResponse)) {
            double value = static_cast<double>(resultResponse);
            responseValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedDampingFraction = true;
    env->Reference_IsUndefined(dampingFraction, &isUndefinedDampingFraction);
    if (!isUndefinedDampingFraction) {
        ani_double resultDampingFraction;
        if (ANI_OK == env->Object_CallMethodByName_Double(dampingFraction, "doubleValue",
            nullptr, &resultDampingFraction)) {
            double value = static_cast<double>(resultDampingFraction);
            dampingFractionValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedOverlapDuration = true;
    env->Reference_IsUndefined(overlapDuration, &isUndefinedOverlapDuration);
    if (!isUndefinedOverlapDuration) {
        ani_double resultOverlapDuration;
        if (ANI_OK == env->Object_CallMethodByName_Double(overlapDuration, "doubleValue",
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

static ani_double Interpolate([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_double fraction)
{
    auto curveObject = unwrapp(env, object);
    if (!curveObject) {
        return 0.0;
    }
    auto curveString = curveObject->curveString;
    float time = static_cast<float>(fraction);
    time = std::clamp(time, 0.0f, 1.0f);
    auto animationCurve = OHOS::Ace::Framework::CreateCurve(curveString, false);
    if (!animationCurve) {
        return 0.0;
    }
    ani_double curveValue = static_cast<ani_double>(animationCurve->Move(time));
    return curveValue;
}

static ani_string CubicBezier([[maybe_unused]] ani_env *env,
    ani_double x1, ani_double y1, ani_double x2, ani_double y2)
{
    auto curvesStr = GetCubicBezierCurveString(x1, y1, x2, y2);
    ani_string ret;
    env->String_NewUTF8(curvesStr.c_str(), curvesStr.size(), &ret);
    return ret;
}

static ani_object CubicBezierCurve([[maybe_unused]] ani_env *env,
    ani_double x1, ani_double y1, ani_double x2, ani_double y2)
{
    static const char *className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    CurvesObj* cubicBezierCurve = new CurvesObj();
    cubicBezierCurve->interpolate = Interpolate;
    std::string curveString = GetCubicBezierCurveString(x1, y1, x2, y2);

    cubicBezierCurve->curveString = curveString;
    std::string curveStr = curveString;
    ani_string curveAniStr;
    env->String_NewUTF8(curveStr.c_str(), curveStr.size(), &curveAniStr);

    ani_object curve_object;

    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(cubicBezierCurve))) {
        delete cubicBezierCurve;
        cubicBezierCurve = nullptr;
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return curve_object;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    cubicBezierCurve->pageId = pageId;

    ani_object curveNew_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curveNew_object, reinterpret_cast<ani_object>(cubicBezierCurve))) {
        delete cubicBezierCurve;
        cubicBezierCurve = nullptr;
        return nullptr;
    }

    return curveNew_object;
}

static ani_object SpringCurve([[maybe_unused]] ani_env* env,
    ani_double velocity, ani_double mass, ani_double stiffness, ani_double damping)
{
    static const char* className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }

    CurvesObj* springCurve = new CurvesObj();
    springCurve->interpolate = Interpolate;
    if (OHOS::Ace::LessOrEqual(mass, 0)) {
        mass = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(stiffness, 0)) {
        stiffness = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(damping, 0)) {
        damping = 1.0;
    }
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::SpringCurve>(velocity, mass, stiffness, damping);
    std::string curveString = curve->ToString();

    springCurve->curveString = curveString;
    ani_string curveAniStr {};
    env->String_NewUTF8(curveString.c_str(), curveString.size(), &curveAniStr);

    ani_object obj;

    if (ANI_OK != env->Object_New(cls, ctor, &obj, reinterpret_cast<ani_object>(springCurve))) {
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return obj;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    springCurve->pageId = pageId;

    ani_object objNew;
    if (ANI_OK != env->Object_New(cls, ctor, &objNew, reinterpret_cast<ani_object>(springCurve))) {
        return nullptr;
    }

    return objNew;
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
        if (ANI_OK == env->Object_CallMethodByName_Double(response, "doubleValue", nullptr, &resultResponse)) {
            double value = static_cast<double>(resultResponse);
            responseValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedDampingFraction = true;
    env->Reference_IsUndefined(dampingFraction, &isUndefinedDampingFraction);
    if (!isUndefinedDampingFraction) {
        ani_double resultDampingFraction;
        if (ANI_OK == env->Object_CallMethodByName_Double(dampingFraction, "doubleValue",
            nullptr, &resultDampingFraction)) {
            double value = static_cast<double>(resultDampingFraction);
            dampingFractionValue = static_cast<float>(value);
        }
    }
    ani_boolean isUndefinedOverlapDuration = true;
    env->Reference_IsUndefined(overlapDuration, &isUndefinedOverlapDuration);
    if (!isUndefinedOverlapDuration) {
        ani_double resultOverlapDuration;
        if (ANI_OK == env->Object_CallMethodByName_Double(overlapDuration, "doubleValue",
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

static ani_object SpringResponsiveMotion([[maybe_unused]] ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    CurvesObj* springResponsiveMotion = new CurvesObj();
    springResponsiveMotion->interpolate = Interpolate;
    static const char *className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        return nullptr;
    }
    std::string curveString = GetSpringResponsiveMotionCurveString(env, response, dampingFraction, overlapDuration);
    springResponsiveMotion->curveString = curveString;
    std::string curveStr = curveString;
    ani_string curveAniStr;
    env->String_NewUTF8(curveStr.c_str(), curveStr.size(), &curveAniStr);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(springResponsiveMotion))) {
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return curve_object;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    springResponsiveMotion->pageId = pageId;

    ani_object curveNew_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curveNew_object, reinterpret_cast<ani_object>(springResponsiveMotion))) {
        return nullptr;
    }
    return curveNew_object;
}

static ani_object SpringMotion([[maybe_unused]] ani_env *env,
    ani_object response, ani_object dampingFraction, ani_object overlapDuration)
{
    CurvesObj* springMotion = new CurvesObj();
    springMotion->interpolate = Interpolate;
    static const char *className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        delete springMotion;
        springMotion = nullptr;
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        delete springMotion;
        springMotion = nullptr;
        return nullptr;
    }
    std::string curveString = GetSpringMotionCurveString(env, response, dampingFraction, overlapDuration);
    springMotion->curveString = curveString;
    std::string curveStr = curveString;
    ani_string curveAniStr;
    env->String_NewUTF8(curveStr.c_str(), curveStr.size(), &curveAniStr);

    ani_object curve_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curve_object, reinterpret_cast<ani_object>(springMotion))) {
        delete springMotion;
        springMotion = nullptr;
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return curve_object;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    springMotion->pageId = pageId;

    ani_object curveNew_object;
    if (ANI_OK != env->Object_New(cls, ctor, &curveNew_object, reinterpret_cast<ani_object>(springMotion))) {
        delete springMotion;
        springMotion = nullptr;
        return nullptr;
    }
    return curveNew_object;
}

static ani_object InitCurve([[maybe_unused]] ani_env* env, ani_enum_item enumItem)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(enumItem, &isUndefined);
    ani_int curveType;
    if (isUndefined) {
        curveType = Curve::Linear;
    } else {
        if (ANI_OK != env->EnumItem_GetValue_Int(enumItem, &curveType)) {
            std::cerr << "Enum_GetEnumItemByIndex curveType FAILD" << std::endl;
        }
    }
    std::string curveString = GetCurvesInitInternalMap(curveType);

    static const char* className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        std::cerr << "get ctor Failed'" << className << "'" << std::endl;
        return nullptr;
    }
    CurvesObj* curvesInitInternal = new CurvesObj();
    curvesInitInternal->interpolate = Interpolate;
    curvesInitInternal->curveString = curveString;
    ani_string curveAniStr {};
    env->String_NewUTF8(curveString.c_str(), curveString.size(), &curveAniStr);

    ani_object obj;

    if (ANI_OK != env->Object_New(cls, ctor, &obj, reinterpret_cast<ani_object>(curvesInitInternal))) {
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return obj;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    curvesInitInternal->pageId = pageId;

    ani_object newObj;
    if (ANI_OK != env->Object_New(cls, ctor, &newObj, reinterpret_cast<ani_object>(curvesInitInternal))) {
        return nullptr;
    }
    return newObj;
}

static ani_object InterpolatingSpring([[maybe_unused]] ani_env* env,
    ani_double velocity, ani_double mass, ani_double stiffness, ani_double damping)
{
    static const char* className = "L@ohos/curves/curves/Curves;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        std::cerr << "Not found '" << className << "'" << std::endl;
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        std::cerr << "get ctor Failed'" << className << "'" << std::endl;
        return nullptr;
    }

    CurvesObj* interpolatingCurve = new CurvesObj();
    interpolatingCurve->interpolate = Interpolate;
    if (OHOS::Ace::LessOrEqual(mass, 0)) {
        mass = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(stiffness, 0)) {
        stiffness = 1.0;
    }
    if (OHOS::Ace::LessOrEqual(damping, 0)) {
        damping = 1.0;
    }
    auto curve = OHOS::Ace::AceType::MakeRefPtr<OHOS::Ace::InterpolatingSpring>(velocity, mass, stiffness, damping);
    std::string curveString = curve->ToString();

    interpolatingCurve->curveString = curveString;
    ani_string curveAniStr {};
    env->String_NewUTF8(curveString.c_str(), curveString.size(), &curveAniStr);

    ani_object obj;

    if (ANI_OK != env->Object_New(cls, ctor, &obj, reinterpret_cast<ani_object>(interpolatingCurve))) {
        std::cerr << "New curve object Fail" << std::endl;
        delete interpolatingCurve;
        interpolatingCurve = nullptr;
        return nullptr;
    }

    if (OHOS::Ace::Container::IsCurrentUseNewPipeline()) {
        return obj;
    }
    auto page = GetStagingPage(OHOS::Ace::Container::CurrentId());
    int32_t pageId = -1;
    if (page) {
        pageId = page->GetPageId();
    }
    interpolatingCurve->pageId = pageId;

    ani_object objNew;
    if (ANI_OK != env->Object_New(cls, ctor, &objNew, reinterpret_cast<ani_object>(interpolatingCurve))) {
        std::cerr << "New curve object Fail" << std::endl;
        delete interpolatingCurve;
        interpolatingCurve = nullptr;
        return nullptr;
    }

    return objNew;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/curves/curves;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {"cubicBezier", nullptr, reinterpret_cast<void *>(CubicBezier)},
        ani_native_function {"cubicBezierCurve", nullptr, reinterpret_cast<void *>(CubicBezierCurve)},
        ani_native_function {"springMotion", nullptr, reinterpret_cast<void *>(SpringMotion)},
        ani_native_function {"initCurve", nullptr, reinterpret_cast<void*>(InitCurve)},
        ani_native_function {"interpolatingSpring", nullptr, reinterpret_cast<void*>(InterpolatingSpring)},
        ani_native_function {"springCurve", nullptr, reinterpret_cast<void*>(SpringCurve)},
        ani_native_function {"responsiveSpringMotion", nullptr, reinterpret_cast<void*>(SpringResponsiveMotion)}
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    static const char *classNameCurves = "L@ohos/curves/curves/Curves;";
    ani_class clsCurves;
    if (ANI_OK != env->FindClass(classNameCurves, &clsCurves)) {
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