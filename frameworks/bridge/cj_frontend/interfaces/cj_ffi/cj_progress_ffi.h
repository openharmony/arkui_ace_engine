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

#ifndef OHOS_ACE_FRAMEWORK_CJ_PROGRESS_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_PROGRESS_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"

extern "C" {
struct Length {
    double value;
    int32_t unitType;
};

struct ColorStop {
    uint32_t color;
    Length offset;
};

struct RingStyle {
    double value;
    int32_t unitType;
    bool shadow;
    int32_t status;
    bool enableSmoothEffect;
    bool enableScanEffect;
};

struct ScaleRingStyle {
    double strokeWidthValue;
    int32_t strokeWidthUnit;
    int32_t scaleCount;
    double scaleWidthValue;
    int32_t scaleWidthUnit;
    bool enableSmoothEffect;
};

struct LinearStyle {
    double widthValue;
    int32_t widthUnitType;
    double radiusValue;
    int32_t radiusUnitType;
    bool enableSmoothEffect;
    bool enableScanEffect;
};

struct CapsuleStyle {
    float borderColor;
    double borderWidthValue;
    int32_t borderWidthUnit;
    const char* content;
    float fontColor;
    bool showDefaultPercentage;
    bool enableSmoothEffect;
    bool enableScanEffect;
    double fontSizeValue;
    int32_t fontSizeUnit;
    int32_t fontWeight;
    int32_t fontStyle;
};

CJ_EXPORT void FfiOHOSAceFrameworkProgressCreate(double value, double total, int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetValue(double value);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetBackgroundColor(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetStyle(
    double strokeWidth, int32_t strokeWidthUnit, int32_t scaleCount, double scaleWidth, int32_t scaleWidthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetLinearStyle(LinearStyle linearStyle);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetCapsuleStyle(CapsuleStyle capsuleStyle, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetScaleRingStyle(ScaleRingStyle scaleRingStyle);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetRingStyle(RingStyle ringStyle);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetEclipseStyle(bool enableSmoothEffect);
CJ_EXPORT void FfiOHOSAceFrameworkProgressSetGradientColor(
    std::vector<uint32_t> color, std::vector<double> number, std::vector<int32_t> unitType);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PROGRESS_FFI_H
