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

#ifndef OHOS_ACE_FRAMEWORK_CJ_DATA_PANEL_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_DATA_PANEL_FFI_H

#include <cstdint>
#include <vector>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorDoubleHandle = void*;
using VectorStringPtr = void*;
using VectorNativeLinearGradientHandle = void*;

extern "C" {
struct NativeLinearGradient {
    int32_t firstColor;
    double firstOffset;
    int32_t secondColor;
    double secondOffset;
};
CJ_EXPORT VectorNativeLinearGradientHandle FFICJCreateVectorNativeLinearGradient(int64_t size);
CJ_EXPORT void FFICJVectorNativeLinearGradientSetElement(
    VectorNativeLinearGradientHandle vec, int64_t index, NativeLinearGradient linearGradient);
CJ_EXPORT void FFICJVectorNativeLinearGradientDelete(VectorNativeLinearGradientHandle vec);


struct NativeDataPanelShadow {
    double radius;
    double offsetX;
    double offsetY;
    VectorStringPtr colors;
};

CJ_EXPORT void FfiOHOSAceFrameworkDataPanelCreate(VectorDoubleHandle values, double max, int32_t panelType);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetCloseEffect(bool isCloseEffect);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetValueColors(VectorStringPtr vecContent);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetTrackBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetStrokeWidth(double strokeWidth, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkDataPanelSetTrackShadow(NativeDataPanelShadow nativeDataPanelShadow);
};
#endif