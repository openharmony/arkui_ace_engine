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

#ifndef OHOS_ACE_FRAMEWORK_CJ_RECT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_RECT_FFI_H

#include <cstdint>
#include <vector>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorDoubleHandle = void*;
using VectorInt32Handle = void*;

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkRectCreate(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRectInsCreate(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetRadiusWidth(double radiusWidth, int32_t radiusWidthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetRadiusHeight(double radiusHeight, int32_t radiusHeightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetRadius(double radius, int32_t radiusUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetRadiusArray(VectorDoubleHandle voidValue, VectorInt32Handle voidUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetRadiusTupleArray(VectorDoubleHandle voidWidthValue,
    VectorInt32Handle voidWidthUnit, VectorDoubleHandle voidHeightValue, VectorInt32Handle voidHeightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetInsRadiusWidth(int64_t shapeId, double radiusWidth, int32_t radiusWidthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetInsRadiusHeight(
    int64_t shapeId, double radiusHeight, int32_t radiusHeightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkRectSetInsRadius(int64_t shapeId, double radius, int32_t radiusUnit);
};
#endif
