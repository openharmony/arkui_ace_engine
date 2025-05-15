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

#ifndef OHOS_ACE_FRAMEWORK_CJ_CANVAS_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_CANVAS_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_collection_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_polygon_ffi.h"

using VectorDoublePtr = void*;
using VectorUInt8Prt = void*;
using VectorFloat64Ptr = void*;
using VectorUInt8Handle = void*;

extern "C" {
struct CTextMetrics {
    double width;
    double height;
};

struct NativeImageInfo {
    int32_t flag;
    double sx;
    double sy;
    double sWidth;
    double sHeight;
    double dx;
    double dy;
    double dWidth;
    double dHeight;
};

struct TransformParams {
    double scaleX;
    double skewX;
    double skewY;
    double scaleY;
    double translateX;
    double translateY;
};

struct ArcParams {
    double x;
    double y;
    double radius;
    double startAngle;
    double endAngle;
};

struct ArcToParams {
    double x1;
    double y1;
    double x2;
    double y2;
    double radius;
};

struct QuadraticCurveToParams {
    double cpx;
    double cpy;
    double x;
    double y;
};

struct BezierCurveToParams {
    double cp1x;
    double cp1y;
    double cp2x;
    double cp2y;
    double x;
    double y;
};

struct EllipseParams {
    double x;
    double y;
    double radiusX;
    double radiusY;
    double rotation;
    double startAngle;
    double endAngle;
};

struct RectParams {
    double x;
    double y;
    double width;
    double height;
};

struct ImageDataParams {
    int64_t id;
    int32_t width;
    int32_t height;
    int64_t result;
};

struct ImageBitMapParams {
    double height;
    double width;
    int64_t pixelMapId;
    int32_t unit;
    bool hasSrc;
    int64_t imageBitMapId;
};

struct DrawingRenderingContextParams {
    double width;
    double height;
};

CJ_EXPORT void FfiOHOSAceFrameworkCanvasCreate(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasOnReady(void (*callback)());

// Rendering Context Create
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCtor(bool antialias);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCtorWithUnit(bool antialias, int32_t unit);
// Rendering Context Attribute
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetFillStyle(int64_t selfId, uint32_t colorValue);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetFillStyleByGradient(int64_t selfId, int64_t gradientId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetFillStyleByCanvasPattern(int64_t contextId, int64_t patternId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetLineWidth(int64_t selfId, double lineWidth);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetStrokeStyle(int64_t selfId, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetStrokeStyleByGradient(int64_t selfId, int64_t gradientId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetStrokeStyleByPattern(int64_t contextId, int64_t patterntId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetLineCap(int64_t selfId, int32_t lineCap);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetLineJoin(int64_t selfId, int32_t lineJoin);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetMiterLimit(int64_t selfId, double limit);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetFont(
    int64_t selfId, int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetTextAlign(int64_t selfId, int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetTextBaseline(int64_t selfId, int32_t baseline);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetGlobalAlpha(int64_t selfId, double alpha);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetLineDash(int64_t selfId, VectorDoublePtr lineDashArr);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetLineDashOffset(int64_t selfId, double lineDashOffset);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetGlobalCompositeOperation(int64_t selfId, int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetShadowBlur(int64_t selfId, double blur);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetShadowColor(int64_t selfId, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetShadowOffsetX(int64_t selfId, double offsetX);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetShadowOffsetY(int64_t selfId, double offsetY);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetImageSmoothingEnabled(int64_t selfId, bool enabled);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetImageSmoothingQuality(int64_t selfId, const char* quality);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetDirection(int64_t contextId, const char* direction);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetFilter(int64_t contextId, const char* filterStr);
CJ_EXPORT double FfiOHOSAceFrameworkRenderingContextGetHight(int64_t contextId);
CJ_EXPORT double FfiOHOSAceFrameworkRenderingContextGetWidth(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSaveLayer(int64_t contextId);

// Rendering Context Function
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClearRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillText(int64_t selfId, double x, double y, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeText(int64_t selfId, double x, double y, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth);
CJ_EXPORT CTextMetrics FfiOHOSAceFrameworkRenderingContextMeasureText(int64_t selfId, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStroke(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeWithPath(int64_t selfId, int64_t pathId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextBeginPath(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextMoveTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextLineTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClosePath(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextBezierCurveTo(
    int64_t selfId, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextQuadraticCurveTo(
    int64_t selfId, double cpx, double cpy, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextArc(
    int64_t selfId, double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextArcTo(
    int64_t selfId, double x1, double y1, double x2, double y2, double radius);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextEllipse(int64_t selfId, double x, double y, double radiusX,
    double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextRect(int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFill(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillWithStr(int64_t contextId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillWithPath(int64_t contextId, int64_t pathId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClip(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClipWithStr(int64_t contextId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClipWithPath(int64_t contextId, int64_t pathId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextRotate(int64_t selfId, double angle);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextScale(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextTransform(
    int64_t selfId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetTransform(
    int64_t selfId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetTransformByMatrix(int64_t contextId, int64_t matrixId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextTranslate(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextRestore(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSave(int64_t selfId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateLinearGradient(
    int64_t selfId, double x0, double y0, double x1, double y1);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateRadialGradient(
    int64_t selfId, double x0, double y0, double r0, double x1, double y1, double r1);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateConicGradient(
    int64_t contextId, double startAngle, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextDrawImage(
    int64_t contextId, const char* src, NativeImageInfo imageInfo);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextDrawImageWithPixelMap(
    int64_t contextId, int64_t pixelMapId, NativeImageInfo imageInfo);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextDrawImageWithImageBitMap(
    int64_t contextId, int64_t bitMapID, NativeImageInfo imageInfo);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextGetPixelMap(
    int64_t contextId, double fLeft, double fTop, double fWidth, double fHeight);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextTransferToImageBitmap(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextTransferFromImageBitmap(int64_t selfId, int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextReset(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSavaLayer(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextRestoreLayer(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextResetTransform(int64_t contextId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextGetTransform(int64_t contextId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateImageDataWithImageData(
    int64_t contextId, int64_t imageDataId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateImageData(int64_t contextId, double height, double width);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextSetPixelMap(int64_t contextId, int64_t pixelMapId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextGetImageData(
    int64_t contextId, const double left, const double top, const double width, const double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextPutImageDataWithDirty(int64_t contextId, int64_t dataId, double dx,
    double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextPutImageData(int64_t contextId, int64_t dataId, double dx, double dy);
CJ_EXPORT VectorFloat64Ptr FfiOHOSAceFrameworkRenderingContextGetLineDash(int64_t contextId);
CJ_EXPORT const char* FfiOHOSAceFrameworkRenderingContextToDataURL(int64_t contextId, const char* type, double quality);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextCreateCanvasPattern(
    int64_t contextId, int64_t bitMapId, const char* repSrc);

// canvas_gradient
CJ_EXPORT void FfiOHOSAceFrameworkCanvasGradientAddColorStop(int64_t selfId, double offset, uint32_t color);

// Canvas Path2d
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPathCtor();
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPathCtorWithPath(const char* path);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPathCtorWithUnit(int32_t unit);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPathCtorWithPathAndUnit(const char* path, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathAddPath(int64_t selfId, int64_t pathId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathAddPathWithMatrix(int64_t selfId, int64_t pathId, int64_t matrixId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathSetTransform(int64_t selfId, TransformParams params);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathMoveTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathLineTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathArc(int64_t selfId, ArcParams params, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathArcTo(int64_t selfId, ArcToParams params);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathQuadraticCurveTo(int64_t selfId, QuadraticCurveToParams params);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathBezierCurveTo(int64_t selfId, BezierCurveToParams params);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathEllipse(int64_t selfId, EllipseParams params, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathRect(int64_t selfId, RectParams params);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPathClosePath(int64_t selfId);

// Canvas Matrix2d
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasMatrixCtor(int32_t unit);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetScaleX(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetScaleY(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetRotateX(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetRotateY(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetTranslateX(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkCanvasMatrixGetTranslateY(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetScaleX(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetScaleY(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetRotateX(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetRotateY(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetTranslateX(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixSetTranslateY(int64_t selfId, double value);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixIdentity(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixInvert(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixRotate(int64_t selfId, double degree, double rx, double ry);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixTranslate(int64_t selfId, double tx, double ty);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixScale(int64_t selfId, double sx, double sy);

// Canvas ImageData
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasImageDataCtor(
    double width, double heigth, VectorUInt8Prt dataHandle, int32_t unit);
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasImageDataCtorWithNoData(double width, double heigth, int32_t unit);
CJ_EXPORT int32_t FfiOHOSAceFrameworkCanvasImageDataGetHeight(int64_t selfId);
CJ_EXPORT int32_t FfiOHOSAceFrameworkCanvasImageDataGetWidth(int64_t selfId);
CJ_EXPORT VectorUInt8Handle FfiOHOSAceFrameworkCanvasImageDataGetData(int64_t selfId);

// Canvas Pattern
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPatternCtor();
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPatternSetTransform(int64_t selfId, int64_t matrixId);

// Drawing Rendering Context
CJ_EXPORT int64_t FfiOHOSAceFrameworkDrawingRenderingContextCtor(int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkDrawingRenderingContextInvalidate(int64_t selfId);

// ImageBitMap
CJ_EXPORT int64_t FfiOHOSAceFrameworkImageBitMapCtor(const char* src, int32_t unit);
CJ_EXPORT int64_t FfiOHOSAceFrameworkImageBitMapCtorWithPixelMap(int64_t pixelMapId, int32_t unit);
CJ_EXPORT double FfiOHOSAceFrameworkImageBitMapGetHeight(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkImageBitMapGetWidth(int64_t selfId);

// Offscreen Canvas
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasCtor(double height, double width, int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasSetHeight(int64_t selfId, double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasSetWidth(int64_t selfId, double width);
CJ_EXPORT double FfiOHOSAceFrameworkOffscreenCanvasGetHeight(int64_t selfId);
CJ_EXPORT double FfiOHOSAceFrameworkOffscreenCanvasGetWidth(int64_t selfId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkImageBitMapCtorByOffscreenCanvas(int64_t offscreenCanvasId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContext2DCtor(
    int64_t offscreenId, int32_t contextType, bool option, double width, double height);
}
#endif
