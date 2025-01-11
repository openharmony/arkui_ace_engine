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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_offscreen_canvas_ffi.h"

#include <cstdint>
#include <string>

#include "cj_lambda.h"
#include "ffi_remote_data.h"

#include "base/geometry/matrix4.h"
#include "bridge/cj_frontend/cppview/canvas_image_data.h"
#include "bridge/cj_frontend/cppview/canvas_pattern.h"
#include "bridge/cj_frontend/cppview/offscreen_rendering_context.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_model.h"

using namespace OHOS;
using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
enum class CanvasImageType { COORDINATES_ONLY = 0, COORDINATES_AND_SIZE, COORDINATES_AND_SIZE_WITH_SOURCE };
const std::vector<LineCapStyle> LINE_CAP_STYLE_LIST = { LineCapStyle::BUTT, LineCapStyle::ROUND, LineCapStyle::SQUARE };
const std::vector<LineJoinStyle> LINE_JOIN_STYLE_LIST = { LineJoinStyle::MITER, LineJoinStyle::ROUND,
    LineJoinStyle::BEVEL };
const std::vector<FontStyle> FONT_STYLE_LIST = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGN_LIST = { TextAlign::LEFT, TextAlign::RIGHT, TextAlign::CENTER,
    TextAlign::JUSTIFY, TextAlign::START, TextAlign::END };
const std::vector<TextBaseline> TEXT_BASELINE_LIST = { TextBaseline::ALPHABETIC, TextBaseline::IDEOGRAPHIC,
    TextBaseline::TOP, TextBaseline::BOTTOM, TextBaseline::MIDDLE, TextBaseline::HANGING };
const std::vector<CompositeOperation> COMPOSITE_OPERATION_LIST = { CompositeOperation::SOURCE_OVER,
    CompositeOperation::SOURCE_ATOP, CompositeOperation::SOURCE_IN, CompositeOperation::SOURCE_OUT,
    CompositeOperation::DESTINATION_OVER, CompositeOperation::DESTINATION_ATOP, CompositeOperation::DESTINATION_IN,
    CompositeOperation::DESTINATION_OUT, CompositeOperation::LIGHTER, CompositeOperation::COPY,
    CompositeOperation::XOR };
const std::vector<CanvasImageType> CANVAS_IMAGE_TYPE_LIST = { CanvasImageType::COORDINATES_ONLY,
    CanvasImageType::COORDINATES_AND_SIZE, CanvasImageType::COORDINATES_AND_SIZE_WITH_SOURCE };

Rect GetRectParam(double x, double y, double width, double height)
{
    Rect rect = Rect(x, y, width, height);
    return rect;
}

BezierCurveParam GetBezierCurveParam(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y)
{
    BezierCurveParam param;
    param.cp1x = cp1x;
    param.cp1y = cp1y;
    param.cp2x = cp2x;
    param.cp2y = cp2y;
    param.x = x;
    param.y = y;
    return param;
}

QuadraticCurveParam GetQuadraticCurveParam(double cpx, double cpy, double x, double y)
{
    QuadraticCurveParam param;
    param.cpx = cpx;
    param.cpy = cpy;
    param.x = x;
    param.y = y;
    return param;
}

ArcParam GetArcParam(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise)
{
    ArcParam param;
    param.x = x;
    param.y = y;
    param.radius = radius;
    param.startAngle = startAngle;
    param.endAngle = endAngle;
    param.anticlockwise = anticlockwise;
    return param;
}

ArcToParam GetArcToParam(double x1, double y1, double x2, double y2, double radius)
{
    ArcToParam param;
    param.x1 = x1;
    param.y1 = y1;
    param.x2 = x2;
    param.y2 = y2;
    param.radius = radius;
    return param;
}

EllipseParam GetEllipseParam(double x, double y, double radiusX, double radiusY, double rotation, double startAngle,
    double endAngle, bool anticlockwise)
{
    EllipseParam param;
    param.x = x;
    param.y = y;
    param.radiusX = radiusX;
    param.radiusY = radiusY;
    param.rotation = rotation;
    param.startAngle = startAngle;
    param.endAngle = endAngle;
    param.anticlockwise = anticlockwise;
    return param;
}

TransformParam GetTransformParam(
    double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY)
{
    TransformParam param;
    param.scaleX = scaleX;
    param.scaleY = scaleY;
    param.skewX = skewX;
    param.skewY = skewY;
    param.translateX = translateX;
    param.translateY = translateY;
    return param;
}
} // namespace

extern "C" {
int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCtor(
    double width, double height, bool antialias, int32_t unit)
{
    auto context = FFIData::Create<CJOffscreenRenderingContext>(width, height, antialias, unit);
    if (context == nullptr) {
        return FFI_ERROR_CODE;
    }
    return context->GetID();
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyle(int64_t contextId, uint32_t colorValue)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetFillStyle(Color(colorValue));
    } else {
        LOGE("canvas fillStyle error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyleByGradient(int64_t contextId, int64_t gradientId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasGradient = FFIData::GetData<NativeCanvasGradient>(gradientId);
    if (nativeCanvasGradient == nullptr) {
        return;
    }
    context->SetFillStyle(nativeCanvasGradient);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFillStyleByCanvasPattern(int64_t contextId, int64_t patternId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasPattern = FFIData::GetData<NativeCanvasPattern>(patternId);
    if (nativeCanvasPattern == nullptr) {
        return;
    }
    context->SetFillStyle(nativeCanvasPattern);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineWidth(int64_t contextId, double lineWidth)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetLineWidth(lineWidth);
    } else {
        LOGE("canvas lineWidth error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyle(int64_t contextId, uint32_t color)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetStrokeStyle(Color(color));
    } else {
        LOGE("canvas strokeStyle error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyleByGradient(int64_t contextId, int64_t gradientId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasGradient = FFIData::GetData<NativeCanvasGradient>(gradientId);
    if (nativeCanvasGradient == nullptr) {
        return;
    }
    context->SetStrokeStyle(nativeCanvasGradient);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetStrokeStyleByPattern(int64_t contextId, int64_t patterntId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasPattern = FFIData::GetData<NativeCanvasPattern>(patterntId);
    if (nativeCanvasPattern == nullptr) {
        return;
    }
    context->SetStrokeStyle(nativeCanvasPattern);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineCap(int64_t contextId, int32_t lineCap)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(lineCap, LINE_CAP_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetLineCap(LINE_CAP_STYLE_LIST[lineCap]);
    } else {
        LOGE("canvas lineCap error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineJoin(int64_t contextId, int32_t lineJoin)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(lineJoin, LINE_JOIN_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetLineJoin(LINE_JOIN_STYLE_LIST[lineJoin]);
    } else {
        LOGE("canvas lineJoin error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetMiterLimit(int64_t contextId, double limit)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetMiterLimit(limit);
    } else {
        LOGE("canvas miterLimit error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFont(
    int64_t contextId, int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(style, FONT_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetFont(FONT_STYLE_LIST[style], weight, Dimension(size, static_cast<DimensionUnit>(sizeUnit)), family);
    } else {
        LOGE("canvas font error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTextAlign(int64_t contextId, int32_t align)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(align, TEXT_ALIGN_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetTextAlign(TEXT_ALIGN_LIST[align]);
    } else {
        LOGE("canvas textAlign error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTextBaseline(int64_t contextId, int32_t baseline)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(baseline, TEXT_BASELINE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetTextBaseline(TEXT_BASELINE_LIST[baseline]);
    } else {
        LOGE("canvas textBaseline error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetGlobalAlpha(int64_t contextId, double alpha)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetGlobalAlpha(alpha);
    } else {
        LOGE("canvas globalAlpha error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineDashOffset(int64_t contextId, double lineDashOffset)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetLineDashOffset(lineDashOffset);
    } else {
        LOGE("canvas lineDashOffset error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetGlobalCompositeOperation(int64_t contextId, int32_t type)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(type, COMPOSITE_OPERATION_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetGlobalCompositeOperation(COMPOSITE_OPERATION_LIST[type]);
    } else {
        LOGE("canvas globalCompositeOperation error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowBlur(int64_t contextId, double blur)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetShadowBlur(blur);
    } else {
        LOGE("canvas shadowBlur error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowColor(int64_t contextId, uint32_t color)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetShadowColor(Color(color));
    } else {
        LOGE("canvas shadowColor error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowOffsetX(int64_t contextId, double offsetX)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetShadowOffsetX(offsetX);
    } else {
        LOGE("canvas shadowOffsetX error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetShadowOffsetY(int64_t contextId, double offsetY)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetShadowOffsetY(offsetY);
    } else {
        LOGE("canvas shadowOffsetY error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetImageSmoothingEnabled(int64_t contextId, bool enabled)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetImageSmoothingEnabled(enabled);
    } else {
        LOGE("canvas imageSmoothingEnabled error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetImageSmoothingQuality(int64_t contextId, const char* quality)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetImageSmoothingQuality(quality);
    } else {
        LOGE("canvas imageSmoothingQuality error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetDirection(int64_t contextId, const char* direction)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetDirection(direction);
    } else {
        LOGE("canvas SetDirection error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetFilter(int64_t contextId, const char* filterStr)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetFilter(filterStr);
    } else {
        LOGE("canvas SetFilter error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillRect(
    int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->FillRect(rect);
    } else {
        LOGE("canvas fillRect error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeRect(
    int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->StrokeRect(rect);
    } else {
        LOGE("canvas strokeRect error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClearRect(
    int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->ClearRect(rect);
    } else {
        LOGE("canvas clearRect error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillText(int64_t contextId, double x, double y, const char* text)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->FillText(x, y, text);
    } else {
        LOGE("canvas fillText error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->FillText(x, y, text, maxWidth);
    } else {
        LOGE("canvas fillText error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeText(
    int64_t contextId, double x, double y, const char* text)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->StrokeText(x, y, text);
    } else {
        LOGE("canvas strokeText error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->StrokeText(x, y, text, maxWidth);
    } else {
        LOGE("canvas fillText error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

CTextMetrics FfiOHOSAceFrameworkOffscreenCanvasRenderingContextMeasureText(int64_t contextId, const char* text)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    CTextMetrics textMetrics;
    if (context != nullptr) {
        auto metrics = context->MeasureText(text);
        textMetrics.height = metrics.height;
        textMetrics.width = metrics.width;
    } else {
        LOGE("canvas measureText error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
    return textMetrics;
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStroke(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Stroke();
    } else {
        LOGE("canvas stroke error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextStrokeWithPath(int64_t contextId, int64_t pathId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas beginPath error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return;
    }
    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        LOGE("canvas beginPath error, Cannot get NativeCanvasPath by id: %{public}" PRId64, pathId);
        return;
    }
    context->Stroke(path2d);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextBeginPath(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->BeginPath();
    } else {
        LOGE("canvas beginPath error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextMoveTo(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->MoveTo(x, y);
    } else {
        LOGE("canvas moveTo error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextLineTo(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->LineTo(x, y);
    } else {
        LOGE("canvas lineTo error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClosePath(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->ClosePath();
    } else {
        LOGE("canvas closePath error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateCanvasPattern(
    int64_t contextId, int64_t bitMapId, const char* repSrc)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas setTransform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
    return context->CreatePattern(bitMapId, repSrc);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextBezierCurveTo(
    int64_t contextId, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto bezierCurveParam = GetBezierCurveParam(cp1x, cp1y, cp2x, cp2y, x, y);
        context->BezierCurveTo(bezierCurveParam);
    } else {
        LOGE("canvas bezierCurveTo error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextQuadraticCurveTo(
    int64_t contextId, double cpx, double cpy, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto quadraticCurveParam = GetQuadraticCurveParam(cpx, cpy, x, y);
        context->QuadraticCurveTo(quadraticCurveParam);
    } else {
        LOGE("canvas quadraticCurveTo error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextArc(
    int64_t contextId, double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto arcParam = GetArcParam(x, y, radius, startAngle, endAngle, anticlockwise);
        context->Arc(arcParam);
    } else {
        LOGE("canvas arc error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextArcTo(
    int64_t contextId, double x1, double y1, double x2, double y2, double radius)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto arcToParam = GetArcToParam(x1, y1, x2, y2, radius);
        context->ArcTo(arcToParam);
    } else {
        LOGE("canvas arcTo error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextEllipse(int64_t contextId, double x, double y, double radiusX,
    double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto arcParam = GetEllipseParam(x, y, radiusX, radiusY, rotation, startAngle, endAngle, anticlockwise);
        context->Ellipse(arcParam);
    } else {
        LOGE("canvas ellipse error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRect(
    int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->NormalRect(rect);
    } else {
        LOGE("canvas normalRect error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFill(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Fill();
    } else {
        LOGE("canvas fill error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillWithStr(int64_t contextId, const char* ruleStr)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Fill(ruleStr);
    } else {
        LOGE("canvas fill error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextFillWithPath(
    int64_t contextId, int64_t pathId, const char* ruleStr)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas fill error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return;
    }

    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        LOGE("canvas fill error, Cannot get NativeCanvasPath by id: %{public}" PRId64, pathId);
        return;
    }
    context->Fill(path2d, ruleStr);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClip(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Clip();
    } else {
        LOGE("canvas clip error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClipWithStr(int64_t contextId, const char* ruleStr)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Clip(ruleStr);
    } else {
        LOGE("canvas clip error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextClipWithPath(
    int64_t contextId, int64_t pathId, const char* ruleStr)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas clip error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return;
    }

    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        LOGE("canvas clip error, Cannot get NativeCanvasPath by id: %{public}" PRId64, pathId);
        return;
    }
    context->Clip(path2d, ruleStr);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextReset(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Reset();
    } else {
        LOGE("NativeCanvasRenderer Reset error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSavaLayer(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SaveLayer();
    } else {
        LOGE("NativeCanvasRenderer SaveLayer error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRestoreLayer(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->RestoreLayer();
    } else {
        LOGE("NativeCanvasRenderer RestoreLayer error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextResetTransform(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->ResetTransform();
    } else {
        LOGE("NativeCanvasRenderer ResetTransform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRotate(int64_t contextId, double angle)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Rotate(angle);
    } else {
        LOGE("canvas rotate error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextScale(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Scale(x, y);
    } else {
        LOGE("canvas scale error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransform(
    int64_t contextId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto transformParam = GetTransformParam(scaleX, scaleY, skewX, skewY, translateX, translateY);
        context->Transform(transformParam);
    } else {
        LOGE("canvas transform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTransform(
    int64_t contextId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto transformParam = GetTransformParam(scaleX, scaleY, skewX, skewY, translateX, translateY);
        context->SetTransform(transformParam);
    } else {
        LOGE("canvas setTransform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetTransformByMatrix(int64_t contextId, int64_t matrixId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        auto matrix2d = FFIData::GetData<NativeMatrix2d>(matrixId);
        if (matrix2d != nullptr) {
            context->SetTransformByMatrix(matrix2d);
        } else {
            LOGE("canvas setTransform error, Cannot get NativeMatrix2d by id: %{public}" PRId64, matrixId);
        }
    } else {
        LOGE("canvas setTransform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetTransform(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->GetTransform();
    } else {
        LOGE("NativeCanvasRenderer GetTransform error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTranslate(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Translate(x, y);
    } else {
        LOGE("canvas translate error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithImageBitMap(
    int64_t contextId, int64_t bitMapID, NativeImageInfo imageInfo)
{
    auto imageBitmap = FFIData::GetData<CJRenderImage>(bitMapID);
    if (imageBitmap == nullptr) {
        LOGE("canvas DrawImage error, Cannot get CJRenderImage by id: %{public}" PRId64, bitMapID);
        return;
    }
    if (!imageBitmap->GetSrc().empty()) {
        FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithSrc(
            contextId, imageBitmap->GetSrc().c_str(), imageInfo);
    } else {
        FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithPixelMap(
            contextId, imageBitmap->GetPixelMapId(), imageInfo);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithSrc(
    int64_t contextId, const char* src, NativeImageInfo imageInfo)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(imageInfo.flag, CANVAS_IMAGE_TYPE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        return;
    }
    CanvasImage image { .flag = imageInfo.flag,
        .sx = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sx),
        .sy = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sy),
        .sWidth = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sWidth),
        .sHeight = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sHeight),
        .dx = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dx),
        .dy = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dy),
        .dWidth = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dWidth),
        .dHeight = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dHeight),
        .src = src };
    context->DrawImage(image);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextDrawImageWithPixelMap(
    int64_t contextId, int64_t pixelMapId, NativeImageInfo imageInfo)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(imageInfo.flag, CANVAS_IMAGE_TYPE_LIST.size())) {
        LOGE("canvas imageInfo type error, invalid value for ImageInfoType");
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas drawImage error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return;
    }
    auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (instance == nullptr) {
        LOGE("canvas drawImage error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
        return;
    }
    auto pixMap = instance->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("canvas drawImage error, Cannot get pixMap in PixelMapProxy");
        return;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("canvas drawImage error, Cannot create PixelMapOhos by pixMap");
        return;
    }
    CanvasImage image { .flag = imageInfo.flag,
        .sx = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sx),
        .sy = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sy),
        .sWidth = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sWidth),
        .sHeight = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.sHeight),
        .dx = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dx),
        .dy = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dy),
        .dWidth = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dWidth),
        .dHeight = PipelineBase::Vp2PxWithCurrentDensity(imageInfo.dHeight) };
    context->DrawImage(pixMapOhos, image);
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateImageData(
    int64_t contextId, double height, double width)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CreateImageData(height, width);
    } else {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateImageDataWithImageData(
    int64_t contextId, int64_t imageDataId)
{
    auto imageData = FFIData::GetData<NativeImageData>(imageDataId);
    if (imageData == nullptr) {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get NativeImageData by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CreateImageData(imageData);
    } else {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetPixelMap(
    int64_t contextId, double left, double top, double width, double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("canvas drawImage error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }

    return context->GetPixelMap(left, top, width, height);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetPixelMap(int64_t contextId, int64_t pixelMapId)
{
    auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (instance == nullptr) {
        LOGE("canvas SetPixelMap error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
        return;
    }
    auto pixMap = instance->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("canvas SetPixelMap error, Cannot get pixMap in PixelMapProxy");
        return;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("canvas SetPixelMap error, Cannot create PixelMapOhos by pixMap");
        return;
    }
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer SetPixelMap error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return;
    }
    context->SetPixelMap(pixMapOhos);
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetImageData(
    int64_t contextId, const double left, const double top, const double width, const double height)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
    auto nativeImagedata = FFIData::Create<NativeImageData>();
    return context->GetNativeImageData(left, top, width, height);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextPutImageDataWithDirty(int64_t contextId, int64_t dataId,
    double dx, double dy, double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
    auto nativeImagedata = FFIData::GetData<NativeImageData>(dataId);
    if (nativeImagedata == nullptr) {
        LOGE("NativeCanvasRenderer PutImageData error, Cannot get NativeImageData by id: %{public}" PRId64, dataId);
    }
    context->PutImageData(nativeImagedata, dx, dy, dirtyX, dirtyY, dirtyWidth, dirtyHeight);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextPutImageData(
    int64_t contextId, int64_t dataId, double dx, double dy)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    }
    auto nativeImagedata = FFIData::GetData<NativeImageData>(dataId);
    if (nativeImagedata == nullptr) {
        LOGE("NativeCanvasRenderer PutImageData error, Cannot get NativeImageData by id: %{public}" PRId64, dataId);
    }
    context->PutImageData(nativeImagedata, dx, dy);
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSetLineDash(int64_t contextId, VectorDoublePtr lineDashArr)
{
    auto actualVec = reinterpret_cast<std::vector<double>*>(lineDashArr);
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->SetLineDash(*actualVec);
    } else {
        LOGE("canvas lineDash error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

VectorFloat64Ptr FfiOHOSAceFrameworkOffscreenCanvasRenderingContextGetLineDash(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetLineDash error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return nullptr;
    }
    return new std::vector<double>(context->GetLineDash());
}

const char* FfiOHOSAceFrameworkOffscreenCanvasRenderingContextToDataURL(
    int64_t contextId, const char* type, double quality)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    std::string dataUrl;
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetLineDash error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
    } else {
        dataUrl = context->ToDataURL(type, quality);
    }
    auto ret = strdup(dataUrl.c_str());
    return ret;
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextRestore(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Restore();
    } else {
        LOGE("canvas restore error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkOffscreenCanvasRenderingContextSave(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        context->Save();
    } else {
        LOGE("canvas save error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64, contextId);
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateLinearGradient(
    int64_t contextId, double x0, double y0, double x1, double y1)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CreateLinearGradient(x0, y0, x1, y1);
    } else {
        LOGE("canvas createLinearGradient error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateRadialGradient(
    int64_t contextId, double x0, double y0, double r0, double x1, double y1, double r1)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CreateRadialGradient(x0, y0, r0, x1, y1, r1);
    } else {
        LOGE("canvas createRadialGradient error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextCreateConicGradient(
    int64_t contextId, double startAngle, double x, double y)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CreateConicGradient(startAngle, x, y);
    } else {
        LOGE("canvas CreateConicGradient error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContextTransferToImageBitmap(int64_t contextId)
{
    auto context = FFIData::GetData<CJOffscreenRenderingContext>(contextId);
    if (context != nullptr) {
        return context->CJTransferToImageBitmap();
    } else {
        LOGE("canvas transferToImageBitmap error, Cannot get OffscreenRenderingContext by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}
}