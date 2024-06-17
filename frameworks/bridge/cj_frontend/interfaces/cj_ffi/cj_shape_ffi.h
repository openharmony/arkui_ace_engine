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

#ifndef OHOS_ACE_FRAMEWORK_CJ_SHAPE_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_SHAPE_FFI_H

#include <cstdint>
#include <vector>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorFloat64Ptr = void*;
using VectorInt32Ptr = void*;

extern "C" {
struct FFIAtCViewPort {
    int32_t unitX;
    int32_t unitY;
    int32_t unitWidth;
    int32_t unitHeight;
    double x;
    double y;
    double width;
    double height;
};

CJ_EXPORT void FfiOHOSAceFrameworkShapeCreate();
CJ_EXPORT void FfiOHOSAceFrameworkShapeCreateWithPixelMap(int64_t pixelMapId);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetViewPort(FFIAtCViewPort viewPort);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetFill(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetFillOpacity(double fillOpacity);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStroke(uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeDashArray(VectorFloat64Ptr vecValue, VectorInt32Ptr vecUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeDashOffset(double offset, int32_t offsetUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeLineCap(int32_t lineCap);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeLineJoin(int32_t lineJoin);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeMiterLimit(double miterLimit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeOpacity(double strokeOpacity);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetStrokeWidth(double strokeWidth, int32_t widthUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetAntiAlias(bool antiAlias);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetMesh(VectorFloat64Ptr vecValue, uint32_t column, uint32_t row);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetWidth(double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetHeight(double height, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetInsWidth(int64_t shapeId, double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetInsHeight(int64_t shapeId, double value, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetInsSize(
    int64_t shapeId, double width, int32_t widthUnit, double height, int32_t heightUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetInsOffset(int64_t shapeId, double x, int32_t xUnit, double y, int32_t yUnit);
CJ_EXPORT void FfiOHOSAceFrameworkShapeSetInsFill(int64_t shapeId, uint32_t color);
};
#endif
