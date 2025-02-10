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

#include "bridge/cj_frontend/interfaces/cj_ffi/curves/cj_curves_ffi.h"

#include <string>

#include "cj_lambda.h"

#include "bridge/common/utils/utils.h"
#include "core/animation/cubic_curve.h"
#include "core/animation/spring_curve.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::FFI;

namespace {
constexpr int32_t INT_ERROR = 100001;
}

extern "C" {
int64_t FfiOHOSAceFrameworkCurvesCreateStepsCurve(int32_t count, bool end)
{
    auto position = end ? StepsCurvePosition::END : StepsCurvePosition::START;
    if (count < 1) {
        count = 1;
    }
    auto stepsCurve = AceType::MakeRefPtr<StepsCurve>(count, position);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(stepsCurve));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateCubicBezierCurve(float x1, float y1, float x2, float y2)
{
    x1 = std::clamp(x1, 0.0f, 1.0f);
    x2 = std::clamp(x2, 0.0f, 1.0f);
    auto cubicBezierCurve = AceType::MakeRefPtr<CubicCurve>(x1, y1, x2, y2);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(cubicBezierCurve));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateSpringCurve(float velocity, float mass, float stiffness, float damping)
{
    if (LessOrEqual(mass, 0.0)) {
        mass = 1.0;
    }
    if (LessOrEqual(stiffness, 0.0)) {
        stiffness = 1.0;
    }
    if (LessOrEqual(damping, 0.0)) {
        damping = 1.0;
    }
    auto springCurve = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(springCurve));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateInterpolatingSpring(float velocity, float mass, float stiffness, float damping)
{
    if (LessOrEqual(mass, 0.0)) {
        mass = 1.0;
    }
    if (LessOrEqual(stiffness, 0.0)) {
        stiffness = 1.0;
    }
    if (LessOrEqual(damping, 0.0)) {
        damping = 1.0;
    }
    auto interpolatingSpring = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(interpolatingSpring));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateSpringMotion(float response, float dampingFraction, float overlapDuration)
{
    if (LessOrEqual(response, 0.0)) {
        response = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_RESPONSE;
    }
    if (LessOrEqual(dampingFraction, 0.0)) {
        dampingFraction = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_DAMPING_RATIO;
    }
    if (LessOrEqual(overlapDuration, 0.0)) {
        overlapDuration = ResponsiveSpringMotion::DEFAULT_SPRING_MOTION_BLEND_DURATION;
    }
    auto responsiveSpringMotion =
        AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingFraction, overlapDuration);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(responsiveSpringMotion));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration)
{
    if (LessOrEqual(response, 0.0)) {
        response = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_RESPONSE;
    }
    if (LessOrEqual(dampingFraction, 0.0)) {
        dampingFraction = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_DAMPING_RATIO;
    }
    if (LessOrEqual(overlapDuration, 0.0)) {
        overlapDuration = ResponsiveSpringMotion::DEFAULT_RESPONSIVE_SPRING_MOTION_BLEND_DURATION;
    }
    auto responsiveMotion = AceType::MakeRefPtr<ResponsiveSpringMotion>(response, dampingFraction, overlapDuration);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(responsiveMotion));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesCreateCustomCurve(float (*callback)(float fraction))
{
    auto customCurve = AceType::MakeRefPtr<CustomCurve>(CJLambda::Create(callback));
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(customCurve));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesInitCurve(char* aniTimFunc)
{
    auto curve = CreateCurve(aniTimFunc);
    auto iCurve = FFIData::Create<ICurveImpl>(std::move(curve));
    if (iCurve == nullptr) {
        return INT_ERROR;
    }
    int64_t id = iCurve->GetID();
    return id;
}
int64_t FfiOHOSAceFrameworkCurvesInterpolate(int64_t id, float fraction)
{
    auto iCurve = FFIData::GetData<ICurveImpl>(id);
    if (!iCurve) {
        return INT_ERROR;
    }
    if (LessOrEqual(fraction, 0.0)) {
        fraction = 0.0;
    }
    if (GreatOrEqual(fraction, 1.0)) {
        fraction = 1.0;
    }
    return iCurve->GetCurve()->MoveInternal(fraction);
}
}
