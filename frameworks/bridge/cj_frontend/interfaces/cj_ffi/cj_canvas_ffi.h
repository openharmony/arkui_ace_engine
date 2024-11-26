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

#ifndef OHOS_ACE_FRAMEWORK_FFI_CJ_TAB_H
#define OHOS_ACE_FRAMEWORK_FFI_CJ_TAB_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"

using VectorDoublePtr = void*;
using VectorUInt8Prt = void*;

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
CJ_EXPORT double FfiOHOSAceFrameworkRenderingContextGetHight(int64_t contextId);
CJ_EXPORT double FfiOHOSAceFrameworkRenderingContextGetWidth(int64_t contextId);

// Rendering Context Function
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextClearRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextFillText(int64_t selfId, double x, double y, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextStrokeText(int64_t selfId, double x, double y, const char* text);
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
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextDrawImage(
    int64_t contextId, const char* src, NativeImageInfo imageInfo);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextDrawImageWithPixelMap(
    int64_t contextId, int64_t pixelMapId, NativeImageInfo imageInfo);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextGetPixelMap(
    int64_t contextId, double fLeft, double fTop, double fWidth, double fHeight);
CJ_EXPORT int64_t FfiOHOSAceFrameworkRenderingContextTransferToImageBitmap(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkRenderingContextTransferFromImageBitmap(int64_t selfId, int64_t id);

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
CJ_EXPORT TransformParams FfiOHOSAceFrameworkCanvasMatrixIdentity(int64_t selfId, TransformParams transParams);
CJ_EXPORT TransformParams FfiOHOSAceFrameworkCanvasMatrixInvert(int64_t selfId, TransformParams transParams);
CJ_EXPORT TransformParams FfiOHOSAceFrameworkCanvasMatrixRotate(
    int64_t selfId, TransformParams transParams, double degree, double rx, double ry);
CJ_EXPORT TransformParams FfiOHOSAceFrameworkCanvasMatrixTranslate(
    int64_t selfId, TransformParams transParams, double tx, double ty);
CJ_EXPORT TransformParams FfiOHOSAceFrameworkCanvasMatrixScale(
    int64_t selfId, TransformParams transParams, double sx, double sy);
CJ_EXPORT void FfiOHOSAceFrameworkCanvasMatrixUpdate(int64_t selfId, TransformParams transParams);

// Canvas ImageData
CJ_EXPORT ImageDataParams FfiOHOSAceFrameworkCanvasImageDataCtor(
    double width, double heigth, VectorUInt8Prt dataHandle, int32_t unit);
CJ_EXPORT ImageDataParams FfiOHOSAceFrameworkCanvasImageDataCtorWithNoData(double width, double heigth, int32_t unit);

// Canvas Pattern
CJ_EXPORT int64_t FfiOHOSAceFrameworkCanvasPatternCtor();
CJ_EXPORT void FfiOHOSAceFrameworkCanvasPatternSetTransform(int64_t selfId, int64_t matrixId);

// Drawing Rendering Context
CJ_EXPORT int64_t FfiOHOSAceFrameworkDrawingRenderingContextCtor(int32_t unit);
CJ_EXPORT void FfiOHOSAceFrameworkDrawingRenderingContextInvalidate(int64_t selfId);
}
#endif
