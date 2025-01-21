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

#ifndef OHOS_ACE_FRAMEWORK_FFI_CJ_OFFSCREEN_CANVAS_H
#define OHOS_ACE_FRAMEWORK_FFI_CJ_OFFSCREEN_CANVAS_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_polygon_ffi.h"

using VectorDoublePtr = void*;
using VectorUInt8Prt = void*;
using VectorFloat64Ptr = void*;

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

// Offscreen Canvas Rendering Context Create
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCtor(
    double width, double height, bool antialias, int32_t unit);
// Rendering Context Attribute
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyle(int64_t selfId, uint32_t colorValue);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyleByGradient(
    int64_t selfId, int64_t gradientId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyleByCanvasPattern(
    int64_t contextId, int64_t patternId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineWidth(int64_t selfId, double lineWidth);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyle(int64_t selfId, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyleByGradient(
    int64_t selfId, int64_t gradientId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyleByPattern(
    int64_t contextId, int64_t patterntId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineCap(int64_t selfId, int32_t lineCap);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineJoin(int64_t selfId, int32_t lineJoin);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetMiterLimit(int64_t selfId, double limit);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFont(
    int64_t selfId, int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTextAlign(int64_t selfId, int32_t align);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTextBaseline(int64_t selfId, int32_t baseline);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetGlobalAlpha(int64_t selfId, double alpha);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineDash(
    int64_t selfId, VectorDoublePtr lineDashArr);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineDashOffset(
    int64_t selfId, double lineDashOffset);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetGlobalCompositeOperation(
    int64_t selfId, int32_t type);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowBlur(int64_t selfId, double blur);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowColor(int64_t selfId, uint32_t color);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowOffsetX(int64_t selfId, double offsetX);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowOffsetY(int64_t selfId, double offsetY);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetImageSmoothingEnabled(int64_t selfId, bool enabled);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetImageSmoothingQuality(
    int64_t selfId, const char* quality);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetDirection(int64_t contextId, const char* direction);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFilter(int64_t contextId, const char* filterStr);

// Rendering Context Function
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClearRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillText(
    int64_t selfId, double x, double y, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeText(
    int64_t selfId, double x, double y, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth);
CJ_EXPORT CTextMetrics FfiOHOSAceFrameworkOffscreenCanvasRenderingContextMeasureText(int64_t selfId, const char* text);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStroke(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeWithPath(int64_t selfId, int64_t pathId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextBeginPath(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextMoveTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextLineTo(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClosePath(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextBezierCurveTo(
    int64_t selfId, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextQuadraticCurveTo(
    int64_t selfId, double cpx, double cpy, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextArc(
    int64_t selfId, double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextArcTo(
    int64_t selfId, double x1, double y1, double x2, double y2, double radius);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextEllipse(int64_t selfId, double x, double y,
    double radiusX, double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRect(
    int64_t selfId, double x, double y, double width, double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFill(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillWithStr(int64_t contextId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillWithPath(
    int64_t contextId, int64_t pathId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClip(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClipWithStr(int64_t contextId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClipWithPath(
    int64_t contextId, int64_t pathId, const char* ruleStr);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRotate(int64_t selfId, double angle);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextScale(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransform(
    int64_t selfId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTransform(
    int64_t selfId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTransformByMatrix(
    int64_t contextId, int64_t matrixId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTranslate(int64_t selfId, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRestore(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSave(int64_t selfId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateLinearGradient(
    int64_t selfId, double x0, double y0, double x1, double y1);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateRadialGradient(
    int64_t selfId, double x0, double y0, double r0, double x1, double y1, double r1);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateConicGradient(
    int64_t contextId, double startAngle, double x, double y);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithSrc(
    int64_t contextId, const char* src, NativeImageInfo imageInfo);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithPixelMap(
    int64_t contextId, int64_t pixelMapId, NativeImageInfo imageInfo);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithImageBitMap(
    int64_t contextId, int64_t bitMapID, NativeImageInfo imageInfo);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetPixelMap(
    int64_t contextId, double fLeft, double fTop, double fWidth, double fHeight);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransferToImageBitmap(int64_t selfId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransferFromImageBitmap(int64_t selfId, int64_t id);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextReset(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSavaLayer(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRestoreLayer(int64_t contextId);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextResetTransform(int64_t contextId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetTransform(int64_t contextId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateImageDataWithImageData(
    int64_t contextId, int64_t imageDataId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateImageData(
    int64_t contextId, double height, double width);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetPixelMap(int64_t contextId, int64_t pixelMapId);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetImageData(
    int64_t contextId, const double left, const double top, const double width, const double height);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextPutImageDataWithDirty(int64_t contextId,
    int64_t dataId, double dx, double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight);
CJ_EXPORT void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextPutImageData(
    int64_t contextId, int64_t dataId, double dx, double dy);
CJ_EXPORT VectorFloat64Ptr FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetLineDash(int64_t contextId);
CJ_EXPORT const char* FfiOHOSAceFrameworkOffscreenCanvasRenderingContextToDataURL(
    int64_t contextId, const char* type, double quality);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateCanvasPattern(
    int64_t contextId, int64_t bitMapId, const char* repSrc);
CJ_EXPORT int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransferToImageBitmap(int64_t contextId);
}
#endif
