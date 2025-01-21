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

#ifndef OHOS_ACE_FRAMEWORK_CJ_CURVES_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CURVES_FFI_H

#include "ffi_remote_data.h"

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "core/animation/curve.h"

namespace OHOS::Ace {

class ICurveImpl : public OHOS::FFI::FFIData {
    DECL_TYPE(ICurveImpl, OHOS::FFI::FFIData);

public:
    ICurveImpl() = default;
    ICurveImpl(RefPtr<Curve> curve) : curve_(std::move(curve)) {}
    ~ICurveImpl() override = default;

    RefPtr<Curve> GetCurve() const
    {
        return curve_;
    }

private:
    RefPtr<Curve> curve_;
};

} // namespace OHOS::Ace

extern "C" {
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateStepsCurve(int32_t count, bool end);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateCubicBezierCurve(float x1, float y1, float x2, float y2);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateSpringCurve(
    float velocity, float mass, float stiffness, float damping);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateInterpolatingSpring(
    float velocity, float mass, float stiffness, float damping);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateSpringMotion(
    float response, float dampingFraction, float overlapDuration);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateResponsiveSpringMotion(
    float response, float dampingFraction, float overlapDuration);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesCreateCustomCurve(float (*callback)(float fraction));
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesInitCurve(char* aniTimFunc);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCurvesInterpolate(int64_t id, float fraction);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_CURVES_FFI_H
