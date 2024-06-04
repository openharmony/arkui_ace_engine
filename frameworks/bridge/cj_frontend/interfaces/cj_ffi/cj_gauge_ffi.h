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

#ifndef OHOS_ACE_FRAMEWORK_CJ_GAUGE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_GAUGE_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorUInt32Ptr = void*;
using VectorFloat32Ptr = void*;
using VecLinearGradientHandle = void*;
using VectorColorStops = void*;

extern "C" {
struct ColorStop {
    uint32_t color;
    double offset;
};
CJ_EXPORT VectorColorStops FFICJCreateVectorColorStop(int64_t size);
CJ_EXPORT void FFICJVectorColorStopSetElement(VectorColorStops vec, int64_t index, ColorStop colorStop);
CJ_EXPORT void FFICJVectorColorStopDelete(VectorColorStops vec);
CJ_EXPORT VecLinearGradientHandle FFICJCreateVectorGaugeLinearGradient(int64_t size);
CJ_EXPORT void FFICJVectorGaugeLinearGradientSetElement(
    VecLinearGradientHandle vec, int64_t index, VectorColorStops vectorColorStops);
CJ_EXPORT void FFICJVectorGaugeLinearGradientDelete(VecLinearGradientHandle vec);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeCreate(double gaugeValue, double gaugeMin, double gaugeMax);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetValue(double value);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetStartAngle(double startAngle);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetEndAngle(double endAngle);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetColors(VectorUInt32Ptr colors, VectorFloat32Ptr weights);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetColorsV2(VectorUInt32Ptr colors, VectorFloat32Ptr weights);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetLinearGradientColors(
    VecLinearGradientHandle linearGradients, VectorUInt32Ptr weight);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetStrokeWidth(double strokeWidth, int32_t strokeUnit);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetShadowOptions(double radius, double offsetX, double offsetY);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetIndicator(const char* icon, double size);
CJ_EXPORT void FfiOHOSAceFrameworkGaugeSetDescription(void (*builder)());
}
#endif
