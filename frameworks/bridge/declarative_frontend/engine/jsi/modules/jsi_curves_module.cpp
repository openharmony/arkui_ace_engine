/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/engine/jsi/modules/jsi_curves_module.h"

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "frameworks/bridge/js_frontend/engine/common/js_constants.h"
#include "frameworks/core/animation/curve.h"
#include "frameworks/core/common/container.h"

namespace OHOS::Ace::Framework {

shared_ptr<JsValue> CurvesInterpolate(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    auto jsCurveString = thisObj->GetProperty(runtime, "__curveString");
    auto curveString = jsCurveString->ToString(runtime);
    auto curveObjFunc = thisObj->GetProperty(runtime, "__curveCustomFunc");
    if (argv.size() == 0) {
        return runtime->NewNull();
    }
    double time = argv[0]->ToDouble(runtime);
    time = std::clamp(time, 0.0, 1.0);
    auto animationCurve = CreateCurve(curveString, false);
    if (curveObjFunc->IsFunction(runtime)) {
        std::function<float(float)> customCallBack = [func = std::move(curveObjFunc),
                    id = Container::CurrentId(), runtime] (float time)->float {
                    ContainerScope scope(id);
                    std::vector<shared_ptr<JsValue>> argv = { runtime->NewNumber(time) };
                    auto result = func->Call(runtime, runtime->GetGlobal(), argv, 1);
                    return result->IsNumber(runtime) ? static_cast<float>(result->ToDouble(runtime)) : 1.0f;
                };
        animationCurve = CreateCurve(customCallBack);
    }
    if (!animationCurve) {
        LOGW("created animationCurve is null, curveString:%{public}s", curveString.c_str());
        return runtime->NewNull();
    }
    double curveValue = animationCurve->Move(time);
    return runtime->NewNumber(curveValue);
}

shared_ptr<JsValue> CurvesInitInternal(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    auto curveObj = runtime->NewObject();
    curveObj->SetProperty(runtime, CURVE_INTERPOLATE, runtime->NewFunction(CurvesInterpolate));
    if (argc != 1 && argc != 0) {
        LOGE("CurvesInit args count is invalid");
        return runtime->NewNull();
    }
    RefPtr<Curve> curve;
    std::string curveString;
    if (argc == 1) {
        curveString = argv[0]->ToString(runtime);
    } else {
        curveString = "linear";
    }
    curve = CreateCurve(curveString);
    curveObj->SetProperty(runtime, "__curveString", runtime->NewString(curveString));
    if (Container::IsCurrentUseNewPipeline()) {
        return curveObj;
    }

    auto page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    int32_t pageId = -1;
    if (page == nullptr) {
        LOGW("page is nullptr");
    } else {
        pageId = page->GetPageId();
    }
    curveObj->SetProperty(runtime, "__pageId", runtime->NewInt32(pageId));
    return curveObj;
}

shared_ptr<JsValue> CurvesInit(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return CurvesInitInternal(runtime, thisObj, argv, argc);
}

shared_ptr<JsValue> InitCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    return CurvesInitInternal(runtime, thisObj, argv, argc);
}

bool CreateSpringCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc != 4) {
        LOGE("Spring curve: the number of parameters is illegal");
        return false;
    }
    double velocity = argv[0]->ToDouble(runtime);
    double mass = argv[1]->ToDouble(runtime);
    double stiffness = argv[2]->ToDouble(runtime);
    double damping = argv[3]->ToDouble(runtime);
    if (LessNotEqual(mass, 0)) {
        LOGW("Spring curve: mass is illegal, value:%{public}f, use default", mass);
        mass = 1.0;
    }
    if (LessNotEqual(stiffness, 0)) {
        LOGW("Spring curve: stiffness is illegal, value:%{public}f, use default", stiffness);
        stiffness = 1.0;
    }
    if (LessNotEqual(damping, 0)) {
        LOGW("Spring curve: damping is illegal, value:%{public}f, use default", damping);
        damping = 1.0;
    }
    curve = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
    return true;
}

bool CreateInterpolatingSpring(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc != 4) {
        LOGE("interpolating Spring: the number of parameters is illegal");
        return false;
    }
    float velocity = static_cast<float>(argv[0]->ToDouble(runtime));
    float mass = static_cast<float>(argv[1]->ToDouble(runtime));
    float stiffness = static_cast<float>(argv[2]->ToDouble(runtime));
    float damping = static_cast<float>(argv[3]->ToDouble(runtime));
    if (LessNotEqual(mass, 0)) {
        LOGW("interpolating Spring: mass is illegal, value:%{public}f, use default", mass);
        mass = 1.0;
    }
    if (LessNotEqual(stiffness, 0)) {
        LOGW("interpolating Spring: stiffness is illegal, value:%{public}f, use default", stiffness);
        stiffness = 1.0;
    }
    if (LessNotEqual(damping, 0)) {
        LOGW("interpolating Spring: damping is illegal, value:%{public}f, use default", damping);
        damping = 1.0;
    }
    curve = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
    return true;
}

bool CreateCubicCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc != 4) {
        LOGE("Cubic curve: the number of parameters is illegal");
        return false;
    }
    double x0 = argv[0]->ToDouble(runtime);
    double y0 = argv[1]->ToDouble(runtime);
    double x1 = argv[2]->ToDouble(runtime);
    double y1 = argv[3]->ToDouble(runtime);
    x0 = std::clamp(x0, 0.0, 1.0);
    x1 = std::clamp(x0, 0.0, 1.0);

    curve = AceType::MakeRefPtr<CubicCurve>(x0, y0, x1, y1);
    return true;
}

bool CreateStepsCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc != 1 && argc != 2) {
        LOGE("Steps curve: the number of parameters is illegal");
        return false;
    }
    int32_t stepSize = 1;
    if (argv[0]->IsNumber(runtime)) {
        stepSize = argv[0]->ToInt32(runtime);
        if (stepSize < 1) {
            LOGW("Steps curve: the value of the stepSize is illegal, use default value");
            stepSize = 1;
        }
    }
    if (argc == 2) {
        bool isEnd = argv[1]->ToBoolean(runtime);
        if (isEnd) {
            curve = AceType::MakeRefPtr<StepsCurve>(stepSize, StepsCurvePosition::END);
        } else {
            curve = AceType::MakeRefPtr<StepsCurve>(stepSize, StepsCurvePosition::START);
        }
    } else {
        curve = AceType::MakeRefPtr<StepsCurve>(stepSize);
    }
    return true;
}

bool CreateSpringMotionCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc > 3) {
        LOGW("SpringMotionCurve: the number of parameters is illegal");
        return false;
    }
    float response = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
    float dampingRatio = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
    float blendDuration = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
    if (argc > 0) {
        response = static_cast<float>(argv[0]->ToDouble(runtime));
        if (LessNotEqual(response, 0)) {
            response = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
            LOGW("SpringMotion: response is illegal, use default value:%{public}f", response);
        }
    }
    if (argc > 1) {
        dampingRatio = static_cast<float>(argv[1]->ToDouble(runtime));
        if (LessNotEqual(dampingRatio, 0)) {
            dampingRatio = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
            LOGW("SpringMotion: dampingRatio is illegal, use default value:%{public}f", dampingRatio);
        }
    }
    if (argc > 2) {
        blendDuration = static_cast<float>(argv[2]->ToDouble(runtime));
        if (LessNotEqual(blendDuration, 0)) {
            blendDuration = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
            LOGW("SpringMotion: blendDuration is illegal, use default value:%{public}f", blendDuration);
        }
    }
    curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
    return true;
}

bool CreateResponsiveSpringMotionCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, RefPtr<Curve>& curve)
{
    if (argc > 3) {
        LOGW("ResponsiveSpringMotionCurve: the number of parameters is illegal");
        return false;
    }
    float response = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
    float dampingRatio = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
    float blendDuration = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
    if (argc > 0) {
        response = static_cast<float>(argv[0]->ToDouble(runtime));
        if (LessNotEqual(response, 0)) {
            response = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
            LOGW("ResponsiveSpringMotion: response is illegal, use default value:%{public}f", response);
        }
    }
    if (argc > 1) {
        dampingRatio = static_cast<float>(argv[1]->ToDouble(runtime));
        if (LessNotEqual(dampingRatio, 0)) {
            dampingRatio = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
            LOGW("ResponsiveSpringMotion: dampingRatio is illegal, use default value:%{public}f", dampingRatio);
        }
    }
    if (argc > 2) {
        blendDuration = static_cast<float>(argv[2]->ToDouble(runtime));
        if (LessNotEqual(blendDuration, 0)) {
            blendDuration = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
            LOGW("ResponsiveSpringMotion: blendDuration is illegal, use default value:%{public}f", blendDuration);
        }
    }
    curve = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingRatio, blendDuration);
    return true;
}

shared_ptr<JsValue> ParseCurves(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc, std::string& curveString)
{
    auto curveObj = runtime->NewObject();
    curveObj->SetProperty(runtime, CURVE_INTERPOLATE, runtime->NewFunction(CurvesInterpolate));
    RefPtr<Curve> curve;
    bool curveCreated;
    if (curveString == CURVES_SPRING || curveString == SPRING_CURVE) {
        curveCreated = CreateSpringCurve(runtime, thisObj, argv, argc, curve);
    } else if (curveString == INTERPOLATING_SPRING) {
        curveCreated = CreateInterpolatingSpring(runtime, thisObj, argv, argc, curve);
    } else if (curveString == CURVES_CUBIC_BEZIER || curveString == CUBIC_BEZIER_CURVE) {
        curveCreated = CreateCubicCurve(runtime, thisObj, argv, argc, curve);
    } else if (curveString == CURVES_STEPS || curveString == STEPS_CURVE) {
        curveCreated = CreateStepsCurve(runtime, thisObj, argv, argc, curve);
    } else if (curveString == SPRING_MOTION) {
        curveCreated = CreateSpringMotionCurve(runtime, thisObj, argv, argc, curve);
    } else if (curveString == RESPONSIVE_SPRING_MOTION) {
        curveCreated = CreateResponsiveSpringMotionCurve(runtime, thisObj, argv, argc, curve);
    } else if (curveString == CURVES_CUSTOM) {
        curve = AceType::MakeRefPtr<CustomCurve>(nullptr);
        curveCreated = true;
        if (argv[0]->IsFunction(runtime)) {
            curveObj->SetProperty(runtime, "__curveCustomFunc", argv[0]);
        } else {
            curveCreated = false;
            LOGW("customCruve argv is not function argv[0] = %{public}s", argv[0]->ToString(runtime).c_str());
        }
    } else {
        LOGE("curve params: %{public}s is illegal", curveString.c_str());
        return runtime->NewNull();
    }
    if (!curveCreated) {
        return runtime->NewNull();
    }
    auto customCurve = curve->ToString();
    curveObj->SetProperty(runtime, "__curveString", runtime->NewString(customCurve));
    if (Container::IsCurrentUseNewPipeline()) {
        return curveObj;
    }
    auto page = JsiDeclarativeEngineInstance::GetStagingPage(Container::CurrentId());
    int32_t pageId = -1;
    if (page == nullptr) {
        LOGW("page is nullptr");
    } else {
        pageId = page->GetPageId();
    }
    curveObj->SetProperty(runtime, "__pageId", runtime->NewInt32(pageId));
    return curveObj;
}

shared_ptr<JsValue> CurvesBezier(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(CURVES_CUBIC_BEZIER);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> BezierCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(CUBIC_BEZIER_CURVE);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> CurvesSpring(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(CURVES_SPRING);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> SpringCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(SPRING_CURVE);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> InterpolatingSpringCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(INTERPOLATING_SPRING);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> CurvesSteps(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(CURVES_STEPS);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> StepsCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(STEPS_CURVE);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}
shared_ptr<JsValue> CustomCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(CURVES_CUSTOM);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> SpringMotionCurve(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& thisObj,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(SPRING_MOTION);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

shared_ptr<JsValue> ResponsiveSpringMotionCurve(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    std::string curveString(RESPONSIVE_SPRING_MOTION);
    return ParseCurves(runtime, thisObj, argv, argc, curveString);
}

void InitCurvesModule(const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& moduleObj)
{
    moduleObj->SetProperty(runtime, CURVES_INIT, runtime->NewFunction(CurvesInit));
    moduleObj->SetProperty(runtime, INIT_CURVE, runtime->NewFunction(InitCurve));
    moduleObj->SetProperty(runtime, CURVES_CUBIC_BEZIER, runtime->NewFunction(CurvesBezier));
    moduleObj->SetProperty(runtime, CUBIC_BEZIER_CURVE, runtime->NewFunction(BezierCurve));
    moduleObj->SetProperty(runtime, CURVES_SPRING, runtime->NewFunction(CurvesSpring));
    moduleObj->SetProperty(runtime, SPRING_CURVE, runtime->NewFunction(SpringCurve));
    moduleObj->SetProperty(runtime, INTERPOLATING_SPRING, runtime->NewFunction(InterpolatingSpringCurve));
    moduleObj->SetProperty(runtime, CURVES_STEPS, runtime->NewFunction(CurvesSteps));
    moduleObj->SetProperty(runtime, STEPS_CURVE, runtime->NewFunction(StepsCurve));
    moduleObj->SetProperty(runtime, SPRING_MOTION, runtime->NewFunction(SpringMotionCurve));
    moduleObj->SetProperty(runtime, RESPONSIVE_SPRING_MOTION, runtime->NewFunction(ResponsiveSpringMotionCurve));
    moduleObj->SetProperty(runtime, CURVES_CUSTOM, runtime->NewFunction(CustomCurve));
    
}

} // namespace OHOS::Ace::Framework