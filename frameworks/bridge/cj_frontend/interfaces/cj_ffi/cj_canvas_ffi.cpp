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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_canvas_ffi.h"

#include <cstdint>
#include <string>
#include <vector>

#include "cj_lambda.h"
#include "ffi_remote_data.h"

#include "base/geometry/matrix4.h"
#include "bridge/cj_frontend/cppview/canvas_image_data.h"
#include "bridge/cj_frontend/cppview/canvas_pattern.h"
#include "bridge/cj_frontend/cppview/offscreen_canvas.h"
#include "bridge/cj_frontend/cppview/render_image.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/pattern/canvas/canvas_model.h"

using namespace OHOS;
using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
constexpr int32_t PIXEL_SIZE = 4;
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
void FfiOHOSAceFrameworkCanvasCreate(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }

    auto pattern = CanvasModel::GetInstance()->Create();
    context->SetCanvasPattern(pattern);
    context->SetAntiAlias();
}

void FfiOHOSAceFrameworkCanvasOnReady(void (*callback)())
{
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto readyEvent = [lambda = CJLambda::Create(callback), node = targetNode] {
        PipelineContext::SetCallBackNode(node);
        lambda();
    };
    CanvasModel::GetInstance()->SetOnReady(std::move(readyEvent));
}

int64_t FfiOHOSAceFrameworkRenderingContextCtor(bool antialias)
{
    auto context = FFIData::Create<NativeCanvasRenderer>(antialias);
    if (context == nullptr) {
        return FFI_ERROR_CODE;
    }
    return context->GetID();
}

int64_t FfiOHOSAceFrameworkRenderingContextCtorWithUnit(bool antialias, int32_t unit)
{
    auto context = FFIData::Create<NativeCanvasRenderer>(antialias);
    context->SetUnit(static_cast<CanvasUnit>(unit));
    if (context == nullptr) {
        return FFI_ERROR_CODE;
    }
    return context->GetID();
}

void FfiOHOSAceFrameworkRenderingContextSetFillStyle(int64_t contextId, uint32_t colorValue)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetFillStyle(Color(colorValue));
    } else {
        LOGE("canvas fillStyle error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

double FfiOHOSAceFrameworkRenderingContextGetHight(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return -1;
    }
    return context->GetHeight();
}

void FfiOHOSAceFrameworkRenderingContextRestoreLayer(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    context->RestoreLayer();
}

void FfiOHOSAceFrameworkRenderingContextSaveLayer(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    context->SaveLayer();
}

void FfiOHOSAceFrameworkRenderingContextSetFillStyleByGradient(int64_t contextId, int64_t gradientId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasGradient = FFIData::GetData<NativeCanvasGradient>(gradientId);
    if (nativeCanvasGradient == nullptr) {
        return;
    }
    context->SetFillStyle(nativeCanvasGradient);
}

void FfiOHOSAceFrameworkRenderingContextSetFillStyleByCanvasPattern(int64_t contextId, int64_t patternId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasPattern = FFIData::GetData<NativeCanvasPattern>(patternId);
    if (nativeCanvasPattern == nullptr) {
        return;
    }
    context->SetFillStyle(nativeCanvasPattern);
}

void FfiOHOSAceFrameworkRenderingContextSetLineWidth(int64_t contextId, double lineWidth)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetLineWidth(lineWidth);
    } else {
        LOGE("canvas lineWidth error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetStrokeStyle(int64_t contextId, uint32_t color)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetStrokeStyle(Color(color));
    } else {
        LOGE("canvas strokeStyle error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetStrokeStyleByGradient(int64_t contextId, int64_t gradientId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasGradient = FFIData::GetData<NativeCanvasGradient>(gradientId);
    if (nativeCanvasGradient == nullptr) {
        return;
    }
    context->SetStrokeStyle(nativeCanvasGradient);
}

void FfiOHOSAceFrameworkRenderingContextSetStrokeStyleByPattern(int64_t contextId, int64_t patterntId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    auto nativeCanvasPattern = FFIData::GetData<NativeCanvasPattern>(patterntId);
    if (nativeCanvasPattern == nullptr) {
        return;
    }
    context->SetStrokeStyle(nativeCanvasPattern);
}

void FfiOHOSAceFrameworkRenderingContextSetLineCap(int64_t contextId, int32_t lineCap)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(lineCap, LINE_CAP_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetLineCap(LINE_CAP_STYLE_LIST[lineCap]);
    } else {
        LOGE("canvas lineCap error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetLineJoin(int64_t contextId, int32_t lineJoin)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(lineJoin, LINE_JOIN_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetLineJoin(LINE_JOIN_STYLE_LIST[lineJoin]);
    } else {
        LOGE("canvas lineJoin error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetMiterLimit(int64_t contextId, double limit)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetMiterLimit(limit);
    } else {
        LOGE("canvas miterLimit error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetFont(
    int64_t contextId, int32_t style, const char* weight, double size, int32_t sizeUnit, const char* family)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(style, FONT_STYLE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetFont(FONT_STYLE_LIST[style], weight, Dimension(size, static_cast<DimensionUnit>(sizeUnit)), family);
    } else {
        LOGE("canvas font error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetTextAlign(int64_t contextId, int32_t align)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(align, TEXT_ALIGN_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetTextAlign(TEXT_ALIGN_LIST[align]);
    } else {
        LOGE("canvas textAlign error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetTextBaseline(int64_t contextId, int32_t baseline)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(baseline, TEXT_BASELINE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetTextBaseline(TEXT_BASELINE_LIST[baseline]);
    } else {
        LOGE("canvas textBaseline error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetGlobalAlpha(int64_t contextId, double alpha)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetGlobalAlpha(alpha);
    } else {
        LOGE("canvas globalAlpha error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetLineDash(int64_t contextId, VectorDoublePtr lineDashArr)
{
    auto actualVec = reinterpret_cast<std::vector<double>*>(lineDashArr);
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetLineDash(*actualVec);
    } else {
        LOGE("canvas lineDash error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetLineDashOffset(int64_t contextId, double lineDashOffset)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetLineDashOffset(lineDashOffset);
    } else {
        LOGE("canvas lineDashOffset error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetGlobalCompositeOperation(int64_t contextId, int32_t type)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(type, COMPOSITE_OPERATION_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetGlobalCompositeOperation(COMPOSITE_OPERATION_LIST[type]);
    } else {
        LOGE("canvas globalCompositeOperation error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetShadowBlur(int64_t contextId, double blur)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetShadowBlur(blur);
    } else {
        LOGE("canvas shadowBlur error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetShadowColor(int64_t contextId, uint32_t color)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetShadowColor(Color(color));
    } else {
        LOGE("canvas shadowColor error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetShadowOffsetX(int64_t contextId, double offsetX)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetShadowOffsetX(offsetX);
    } else {
        LOGE("canvas shadowOffsetX error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetShadowOffsetY(int64_t contextId, double offsetY)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetShadowOffsetY(offsetY);
    } else {
        LOGE("canvas shadowOffsetY error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetImageSmoothingEnabled(int64_t contextId, bool enabled)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetImageSmoothingEnabled(enabled);
    } else {
        LOGE("canvas imageSmoothingEnabled error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetImageSmoothingQuality(int64_t contextId, const char* quality)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetImageSmoothingQuality(quality);
    } else {
        LOGE("canvas imageSmoothingQuality error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetDirection(int64_t contextId, const char* direction)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetDirection(direction);
    } else {
        LOGE("canvas SetDirection error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetFilter(int64_t contextId, const char* filterStr)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SetFilter(filterStr);
    } else {
        LOGE("canvas SetFilter error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFillRect(int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->FillRect(rect);
    } else {
        LOGE("canvas fillRect error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextStrokeRect(int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->StrokeRect(rect);
    } else {
        LOGE("canvas strokeRect error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextClearRect(int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->ClearRect(rect);
    } else {
        LOGE("canvas clearRect error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFillText(int64_t contextId, double x, double y, const char* text)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->FillText(x, y, text);
    } else {
        LOGE("canvas fillText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFillTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->FillText(x, y, text, maxWidth);
    } else {
        LOGE("canvas fillText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextStrokeText(int64_t contextId, double x, double y, const char* text)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->StrokeText(x, y, text);
    } else {
        LOGE("canvas strokeText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextStrokeTextWithMaxWidth(
    int64_t contextId, double x, double y, const char* text, double maxWidth)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->StrokeText(x, y, text, maxWidth);
    } else {
        LOGE("canvas fillText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

CTextMetrics FfiOHOSAceFrameworkRenderingContextMeasureText(int64_t contextId, const char* text)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    CTextMetrics textMetrics;
    if (context != nullptr) {
        auto metrics = context->MeasureText(text);
        textMetrics.height = metrics.height;
        textMetrics.width = metrics.width;
    } else {
        LOGE("canvas measureText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
    return textMetrics;
}

void FfiOHOSAceFrameworkRenderingContextStroke(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Stroke();
    } else {
        LOGE("canvas stroke error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextStrokeWithPath(int64_t contextId, int64_t pathId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        return;
    }
    context->Stroke(path2d);
}

void FfiOHOSAceFrameworkRenderingContextBeginPath(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->BeginPath();
    } else {
        LOGE("canvas beginPath error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextMoveTo(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->MoveTo(x, y);
    } else {
        LOGE("canvas moveTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextLineTo(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->LineTo(x, y);
    } else {
        LOGE("canvas lineTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextClosePath(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->ClosePath();
    } else {
        LOGE("canvas closePath error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextBezierCurveTo(
    int64_t contextId, double cp1x, double cp1y, double cp2x, double cp2y, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto bezierCurveParam = GetBezierCurveParam(cp1x, cp1y, cp2x, cp2y, x, y);
        context->BezierCurveTo(bezierCurveParam);
    } else {
        LOGE("canvas bezierCurveTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextQuadraticCurveTo(int64_t contextId, double cpx, double cpy, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto quadraticCurveParam = GetQuadraticCurveParam(cpx, cpy, x, y);
        context->QuadraticCurveTo(quadraticCurveParam);
    } else {
        LOGE("canvas quadraticCurveTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextArc(
    int64_t contextId, double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto arcParam = GetArcParam(x, y, radius, startAngle, endAngle, anticlockwise);
        context->Arc(arcParam);
    } else {
        LOGE("canvas arc error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextArcTo(
    int64_t contextId, double x1, double y1, double x2, double y2, double radius)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto arcToParam = GetArcToParam(x1, y1, x2, y2, radius);
        context->ArcTo(arcToParam);
    } else {
        LOGE("canvas arcTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextEllipse(int64_t contextId, double x, double y, double radiusX, double radiusY,
    double rotation, double startAngle, double endAngle, bool anticlockwise)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto arcParam = GetEllipseParam(x, y, radiusX, radiusY, rotation, startAngle, endAngle, anticlockwise);
        context->Ellipse(arcParam);
    } else {
        LOGE("canvas ellipse error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextRect(int64_t contextId, double x, double y, double width, double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto rect = GetRectParam(x, y, width, height);
        context->NormalRect(rect);
    } else {
        LOGE("canvas normalRect error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFill(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Fill();
    } else {
        LOGE("canvas fill error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFillWithStr(int64_t contextId, const char* ruleStr)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Fill(ruleStr);
    } else {
        LOGE("canvas fill error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextFillWithPath(int64_t contextId, int64_t pathId, const char* ruleStr)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("canvas fill error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return;
    }

    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        LOGE("canvas fill error, Cannot get NativeCanvasPath by id: %{public}" PRId64, pathId);
        return;
    }
    context->Fill(path2d, ruleStr);
}

void FfiOHOSAceFrameworkRenderingContextClip(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Clip();
    } else {
        LOGE("canvas clip error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextClipWithStr(int64_t contextId, const char* ruleStr)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Clip(ruleStr);
    } else {
        LOGE("canvas clip error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextClipWithPath(int64_t contextId, int64_t pathId, const char* ruleStr)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("canvas clip error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return;
    }

    auto path2d = FFIData::GetData<NativeCanvasPath>(pathId);
    if (path2d == nullptr) {
        LOGE("canvas clip error, Cannot get NativeCanvasPath by id: %{public}" PRId64, pathId);
        return;
    }
    context->Clip(path2d, ruleStr);
}

void FfiOHOSAceFrameworkRenderingContextRotate(int64_t contextId, double angle)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Rotate(angle);
    } else {
        LOGE("canvas rotate error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextScale(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Scale(x, y);
    } else {
        LOGE("canvas scale error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextTransform(
    int64_t contextId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto transformParam = GetTransformParam(scaleX, scaleY, skewX, skewY, translateX, translateY);
        context->Transform(transformParam);
    } else {
        LOGE("canvas transform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetTransform(
    int64_t contextId, double scaleX, double scaleY, double skewX, double skewY, double translateX, double translateY)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto transformParam = GetTransformParam(scaleX, scaleY, skewX, skewY, translateX, translateY);
        context->SetTransform(transformParam);
    } else {
        LOGE("canvas setTransform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetTransformByMatrix(int64_t contextId, int64_t matrixId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        auto matrix2d = FFIData::GetData<NativeMatrix2d>(matrixId);
        if (matrix2d != nullptr) {
            context->SetTransformByMatrix(matrix2d);
        } else {
            LOGE("canvas setTransform error, Cannot get NativeMatrix2d by id: %{public}" PRId64, matrixId);
        }
    } else {
        LOGE("canvas setTransform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateCanvasPattern(int64_t contextId, int64_t bitMapId, const char* repSrc)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("canvas setTransform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
    return context->CreatePattern(bitMapId, repSrc);
}

void FfiOHOSAceFrameworkRenderingContextTranslate(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Translate(x, y);
    } else {
        LOGE("canvas translate error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextRestore(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Restore();
    } else {
        LOGE("canvas restore error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSave(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Save();
    } else {
        LOGE("canvas save error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateLinearGradient(
    int64_t contextId, double x0, double y0, double x1, double y1)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->CreateLinearGradient(x0, y0, x1, y1);
    } else {
        LOGE("canvas createLinearGradient error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateRadialGradient(
    int64_t contextId, double x0, double y0, double r0, double x1, double y1, double r1)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->CreateRadialGradient(x0, y0, r0, x1, y1, r1);
    } else {
        LOGE("canvas createRadialGradient error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateConicGradient(int64_t contextId, double startAngle, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->CreateConicGradient(startAngle, x, y);
    } else {
        LOGE("canvas createRadialGradient error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
}

void FfiOHOSAceFrameworkRenderingContextDrawImageWithImageBitMap(
    int64_t contextId, int64_t bitMapID, NativeImageInfo imageInfo)
{
    auto imageBitmap = FFIData::GetData<CJRenderImage>(bitMapID);
    if (imageBitmap == nullptr) {
        LOGE("canvas DrawImage error, Cannot get CJRenderImage by id: %{public}" PRId64, bitMapID);
        return;
    }
    if (!imageBitmap->GetSrc().empty()) {
        FfiOHOSAceFrameworkRenderingContextDrawImage(contextId, imageBitmap->GetSrc().c_str(), imageInfo);
    } else {
        FfiOHOSAceFrameworkRenderingContextDrawImageWithPixelMap(contextId, imageBitmap->GetPixelMapId(), imageInfo);
    }
}

void FfiOHOSAceFrameworkRenderingContextDrawImage(int64_t contextId, const char* src, NativeImageInfo imageInfo)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(imageInfo.flag, CANVAS_IMAGE_TYPE_LIST.size())) {
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
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

void FfiOHOSAceFrameworkRenderingContextDrawImageWithPixelMap(
    int64_t contextId, int64_t pixelMapId, NativeImageInfo imageInfo)
{
    if (!OHOS::Ace::Framework::Utils::CheckParamsValid(imageInfo.flag, CANVAS_IMAGE_TYPE_LIST.size())) {
        LOGE("canvas imageInfo type error, invalid value for ImageInfoType");
        return;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("canvas drawImage error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
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

int64_t FfiOHOSAceFrameworkRenderingContextGetPixelMap(
    int64_t contextId, double left, double top, double width, double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("canvas drawImage error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }

    return context->GetPixelMap(left, top, width, height);
}

void FfiOHOSAceFrameworkCanvasGradientAddColorStop(int64_t contextId, double offset, uint32_t color)
{
    auto context = FFIData::GetData<NativeCanvasGradient>(contextId);
    if (context != nullptr) {
        context->AddColorStop(offset, Color(color));
    } else {
        LOGE("canvasGradient addColorStop error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

double FfiOHOSAceFrameworkRenderingContextGetWidth(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->GetWidth();
    } else {
        LOGE(
            "NativeCanvasRenderer GetHeight error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return FFI_ERROR_CODE;
    }
}

void FfiOHOSAceFrameworkRenderingContextReset(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Reset();
    } else {
        LOGE("NativeCanvasRenderer Reset error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSavaLayer(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->SaveLayer();
    } else {
        LOGE(
            "NativeCanvasRenderer SaveLayer error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextResetTransform(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->ResetTransform();
    } else {
        LOGE("NativeCanvasRenderer ResetTransform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextGetTransform(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->GetTransform();
    } else {
        LOGE("NativeCanvasRenderer GetTransform error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateImageData(int64_t contextId, double height, double width)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->CreateImageData(height, width);
    } else {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateImageDataWithImageData(int64_t contextId, int64_t imageDataId)
{
    auto imageData = FFIData::GetData<NativeImageData>(imageDataId);
    if (imageData == nullptr) {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get NativeImageData by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        return context->CreateImageData(imageData);
    } else {
        LOGE("NativeCanvasRenderer CreateImageData error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
}

void FfiOHOSAceFrameworkRenderingContextSetPixelMap(int64_t contextId, int64_t pixelMapId)
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
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer SetPixelMap error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return;
    }
    context->SetPixelMap(pixMapOhos);
}

int64_t FfiOHOSAceFrameworkRenderingContextGetImageData(
    int64_t contextId, const double left, const double top, const double width, const double height)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return FFI_ERROR_CODE;
    }
    auto nativeImagedata = FFIData::Create<NativeImageData>();
    return context->GetNativeImageData(left, top, width, height);
}

void FfiOHOSAceFrameworkRenderingContextPutImageDataWithDirty(int64_t contextId, int64_t dataId, double dx, double dy,
    double dirtyX, double dirtyY, double dirtyWidth, double dirtyHeight)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
    }
    auto nativeImagedata = FFIData::GetData<NativeImageData>(dataId);
    if (nativeImagedata == nullptr) {
        LOGE("NativeCanvasRenderer PutImageData error, Cannot get NativeImageData by id: %{public}" PRId64, dataId);
    }
    context->PutImageData(nativeImagedata, dx, dy, dirtyX, dirtyY, dirtyWidth, dirtyHeight);
}

void FfiOHOSAceFrameworkRenderingContextPutImageData(int64_t contextId, int64_t dataId, double dx, double dy)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetImageData error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
    }
    auto nativeImagedata = FFIData::GetData<NativeImageData>(dataId);
    if (nativeImagedata == nullptr) {
        LOGE("NativeCanvasRenderer PutImageData error, Cannot get NativeImageData by id: %{public}" PRId64, dataId);
    }
    context->PutImageData(nativeImagedata, dx, dy);
}

VectorFloat64Ptr FfiOHOSAceFrameworkRenderingContextGetLineDash(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetLineDash error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
        return nullptr;
    }
    return new std::vector<double>(context->GetLineDash());
}

const char* FfiOHOSAceFrameworkRenderingContextToDataURL(int64_t contextId, const char* type, double quality)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    std::string dataUrl;
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer GetLineDash error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64,
            contextId);
    } else {
        dataUrl = context->ToDataURL(type, quality);
    }
    auto ret = strdup(dataUrl.c_str());
    return ret;
}

void FfiOHOSAceFrameworkRenderingContextTransferFromImageBitmap(int64_t contextId, int64_t imageId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        LOGE("NativeCanvasRenderer TransferFromImageBitmap error, Cannot get NativeCanvasRenderer by id: "
             "%{public}" PRId64,
            contextId);
    }
    auto renderImage = FFIData::GetData<CJRenderImage>(imageId);
    if (renderImage == nullptr) {
        LOGE("imageBitMap invert error, Cannot get CJRenderImage by id: %{public}" PRId64, imageId);
    }
    context->TransferFromImageBitmap(renderImage);
}

// Canvas Path2d
int64_t FfiOHOSAceFrameworkCanvasPathCtor()
{
    auto path2d = FFIData::Create<NativeCanvasPath>();
    return path2d->GetID();
}

int64_t FfiOHOSAceFrameworkCanvasPathCtorWithPath(const char* path)
{
    auto path2d = FFIData::Create<NativeCanvasPath>(path);
    return path2d->GetID();
}

int64_t FfiOHOSAceFrameworkCanvasPathCtorWithUnit(int32_t unit)
{
    auto path2d = FFIData::Create<NativeCanvasPath>();
    path2d->SetUnit(static_cast<CanvasUnit>(unit));
    return path2d->GetID();
}

int64_t FfiOHOSAceFrameworkCanvasPathCtorWithPathAndUnit(const char* path, int32_t unit)
{
    auto path2d = FFIData::Create<NativeCanvasPath>(path);
    path2d->SetUnit(static_cast<CanvasUnit>(unit));
    return path2d->GetID();
}

void FfiOHOSAceFrameworkCanvasPathAddPath(int64_t selfId, int64_t pathId)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d == nullptr) {
        return;
    }
    auto addPath = FFIData::GetData<NativeCanvasPath>(pathId);
    if (addPath == nullptr) {
        return;
    }
    path2d->AddPath(addPath);
}

void FfiOHOSAceFrameworkCanvasPathAddPathWithMatrix(int64_t selfId, int64_t pathId, int64_t matrixId)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d == nullptr) {
        return;
    }
    auto addPath = FFIData::GetData<NativeCanvasPath>(pathId);
    if (addPath == nullptr) {
        return;
    }
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(matrixId);
    if (matrix2d == nullptr) {
        return;
    }
    path2d->AddPathWithMatrix(addPath, matrix2d);
}

void FfiOHOSAceFrameworkCanvasPathSetTransform(int64_t selfId, TransformParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->SetTransform(
            params.scaleX, params.skewX, params.skewY, params.scaleY, params.translateX, params.translateY);
    } else {
        LOGE("canvas path2D setTransform error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathMoveTo(int64_t selfId, double x, double y)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->MoveTo(x, y);
    } else {
        LOGE("canvas path2D moveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathLineTo(int64_t selfId, double x, double y)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->LineTo(x, y);
    } else {
        LOGE("canvas path2D lineTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathArc(int64_t selfId, ArcParams params, bool anticlockwise)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->Arc(params.x, params.y, params.radius, params.startAngle, params.endAngle, anticlockwise);
    } else {
        LOGE("canvas path2D arc error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathArcTo(int64_t selfId, ArcToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->ArcTo(params.x1, params.y1, params.x2, params.y2, params.radius);
    } else {
        LOGE("canvas path2D arcTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathQuadraticCurveTo(int64_t selfId, QuadraticCurveToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->QuadraticCurveTo(params.cpx, params.cpy, params.x, params.y);
    } else {
        LOGE("canvas path2D quadraticCurveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathBezierCurveTo(int64_t selfId, BezierCurveToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->BezierCurveTo(params.cp1x, params.cp1y, params.cp2x, params.cp2y, params.x, params.y);
    } else {
        LOGE("canvas path2D bezierCurveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathEllipse(int64_t selfId, EllipseParams params, bool anticlockwise)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->Ellipse(params.x, params.y, params.radiusX, params.radiusY, params.rotation, params.startAngle,
            params.endAngle, anticlockwise);
    } else {
        LOGE("canvas path2D ellipse error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathRect(int64_t selfId, RectParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->Rect(params.x, params.y, params.width, params.height);
    } else {
        LOGE("canvas path2D rect error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathClosePath(int64_t selfId)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        path2d->ClosePath();
    } else {
        LOGE("canvas path2D closePath error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

// Canvas Matrix2d
int64_t FfiOHOSAceFrameworkCanvasMatrixCtor(int32_t unit)
{
    auto matrix2d = FFIData::Create<NativeMatrix2d>(unit);
    return matrix2d->GetID();
}

double FfiOHOSAceFrameworkCanvasMatrixGetScaleX(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetScaleX();
}

double FfiOHOSAceFrameworkCanvasMatrixGetScaleY(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetScaleY();
}

double FfiOHOSAceFrameworkCanvasMatrixGetRotateX(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetRotateX();
}

double FfiOHOSAceFrameworkCanvasMatrixGetRotateY(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetRotateY();
}

double FfiOHOSAceFrameworkCanvasMatrixGetTranslateX(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetTranslateX();
}

double FfiOHOSAceFrameworkCanvasMatrixGetTranslateY(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return matrix2d->GetTranslateY();
}

void FfiOHOSAceFrameworkCanvasMatrixSetScaleX(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetScaleX(value);
}

void FfiOHOSAceFrameworkCanvasMatrixSetScaleY(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetScaleY(value);
}

void FfiOHOSAceFrameworkCanvasMatrixSetRotateX(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetRotateX(value);
}

void FfiOHOSAceFrameworkCanvasMatrixSetRotateY(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetRotateY(value);
}

void FfiOHOSAceFrameworkCanvasMatrixSetTranslateX(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetTranslateX(value);
}

void FfiOHOSAceFrameworkCanvasMatrixSetTranslateY(int64_t selfId, double value)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->SetTranslateY(value);
}

void FfiOHOSAceFrameworkCanvasMatrixIdentity(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->Identity();
}

void FfiOHOSAceFrameworkCanvasMatrixInvert(int64_t selfId)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->Invert();
}

void FfiOHOSAceFrameworkCanvasMatrixRotate(int64_t selfId, double degree, double rx, double ry)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->Rotate(degree, rx, ry);
}

void FfiOHOSAceFrameworkCanvasMatrixTranslate(int64_t selfId, double tx, double ty)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->Translate(tx, ty);
}

void FfiOHOSAceFrameworkCanvasMatrixScale(int64_t selfId, double sx, double sy)
{
    auto matrix2d = FFIData::GetData<NativeMatrix2d>(selfId);
    if (matrix2d == nullptr) {
        LOGE("canvas matrix2d identity error, Cannot get NativeCanvasMatrix2d by id: %{public}" PRId64, selfId);
    }
    matrix2d->Scale(sx, sy);
}

// Canvas ImageData
int64_t FfiOHOSAceFrameworkCanvasImageDataCtor(double width, double heigth, VectorUInt8Prt dataHandle, int32_t unit)
{
    auto imageData = FFIData::Create<NativeImageData>();

    int32_t finalWidth = 0;
    int32_t finalHeight = 0;
    imageData->SetUnit(static_cast<CanvasUnit>(unit));
    if (!imageData->GetImageDataSize(width, heigth, finalWidth, finalHeight)) {
        return FFI_ERROR_CODE;
    }
    int32_t result = finalWidth * finalHeight * PIXEL_SIZE;
    imageData->width_ = finalWidth;
    imageData->height_ = finalHeight;

    const auto& colorArray = *reinterpret_cast<std::vector<uint8_t>*>(dataHandle);
    if ((static_cast<CanvasUnit>(unit) == CanvasUnit::PX) && ((static_cast<int32_t>(colorArray.size())) != result)) {
        LOGE("Failed to construct 'ImageData': The input data length is not equal to (4 * widthPX * heightPX).");
        return FFI_ERROR_CODE;
    }
    imageData->data = colorArray;
    return imageData->GetID();
}

int64_t FfiOHOSAceFrameworkCanvasImageDataCtorWithNoData(double width, double heigth, int32_t unit)
{
    auto imageData = FFIData::Create<NativeImageData>();
    int32_t finalWidth = 0;
    int32_t finalHeight = 0;
    imageData->SetUnit(static_cast<CanvasUnit>(unit));
    if (!imageData->GetImageDataSize(width, heigth, finalWidth, finalHeight)) {
        return FFI_ERROR_CODE;
    }
    int32_t result = finalWidth * finalHeight * PIXEL_SIZE;
    imageData->width_ = finalWidth;
    imageData->height_ = finalHeight;

    std::vector<uint8_t> bufferArray;
    for (int32_t i = 0; i < result; i++) {
        bufferArray.emplace_back(0);
    }
    imageData->data = bufferArray;
    return imageData->GetID();
}

int32_t FfiOHOSAceFrameworkCanvasImageDataGetHeight(int64_t selfId)
{
    auto imageData = FFIData::GetData<NativeImageData>(selfId);
    if (imageData == nullptr) {
        LOGE("canvas image data invert error, Cannot get NativeImageData by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return imageData->GetHeight();
}

int32_t FfiOHOSAceFrameworkCanvasImageDataGetWidth(int64_t selfId)
{
    auto imageData = FFIData::GetData<NativeImageData>(selfId);
    if (imageData == nullptr) {
        LOGE("canvas image data invert error, Cannot get NativeImageData by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return imageData->GetWidth();
}

VectorUInt8Handle FfiOHOSAceFrameworkCanvasImageDataGetData(int64_t selfId)
{
    auto imageData = FFIData::GetData<NativeImageData>(selfId);
    if (imageData == nullptr) {
        LOGE("canvas image data invert error, Cannot get NativeImageData by id: %{public}" PRId64, selfId);
        return new std::vector<uint8_t>();
    }
    return new std::vector<uint8_t>(imageData->GetData());
}

// Canvas Pattern
int64_t FfiOHOSAceFrameworkCanvasPatternCtor()
{
    auto pattern = FFIData::Create<NativeCanvasPattern>();
    pattern->IncRefCount();
    return pattern->GetID();
}

void FfiOHOSAceFrameworkCanvasPatternSetTransform(int64_t selfId, int64_t matrixId)
{
    auto pattern = FFIData::GetData<NativeCanvasPattern>(selfId);
    if (pattern == nullptr) {
        LOGE("canvas pattern invert error, Cannot get NativeCanvasPattern by id: %{public}" PRId64, selfId);
        return;
    }
    pattern->SetTransform(matrixId);
}
// ImageBitmap
int64_t FfiOHOSAceFrameworkImageBitMapCtor(const char* src, int32_t unit)
{
    // ImageBitMap init by src
    auto renderImage = FFIData::Create<CJRenderImage>(unit);
    renderImage->InitCJRenderImage(src);
    return renderImage->GetID();
}

int64_t FfiOHOSAceFrameworkImageBitMapCtorWithPixelMap(int64_t pixelMapId, int32_t unit)
{
    // ImageBitMap init by PixelMap
    auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(pixelMapId);
    if (instance == nullptr) {
        LOGE("canvas drawImage error, Cannot get PixelMapProxy by id: %{public}" PRId64, pixelMapId);
        return FFI_ERROR_CODE;
    }
    auto pixMap = instance->GetRealPixelMap();
    if (pixMap == nullptr) {
        LOGE("canvas drawImage error, Cannot get pixMap in PixelMapProxy");
        return FFI_ERROR_CODE;
    }
    auto pixMapOhos = PixelMap::CreatePixelMap(&pixMap);
    if (pixMapOhos == nullptr) {
        LOGE("canvas drawImage error, Cannot create PixelMapOhos by pixMap");
        return FFI_ERROR_CODE;
    }

    auto renderImage = FFIData::Create<CJRenderImage>(unit);
    renderImage->SetPixelMapId(pixelMapId);
    renderImage->InitCJRenderImage(pixMapOhos);
    return renderImage->GetID();
}

double FfiOHOSAceFrameworkImageBitMapGetHeight(int64_t selfId)
{
    auto renderImage = FFIData::GetData<CJRenderImage>(selfId);
    if (renderImage == nullptr) {
        LOGE("imageBitMap invert error, Cannot get CJRenderImage by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return renderImage->GetHeight();
}

double FfiOHOSAceFrameworkImageBitMapGetWidth(int64_t selfId)
{
    auto renderImage = FFIData::GetData<CJRenderImage>(selfId);
    if (renderImage == nullptr) {
        LOGE("imageBitMap invert error, Cannot get CJRenderImage by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return renderImage->GetWidth();
}

// Offscreen Canvas
int64_t FfiOHOSAceFrameworkOffscreenCanvasCtor(double height, double width, int32_t unit)
{
    auto offscreenCanvas = FFIData::Create<NativeOffscreenCanvas>(height, width, unit);
    return offscreenCanvas->GetID();
}

void FfiOHOSAceFrameworkOffscreenCanvasSetHeight(int64_t selfId, double height)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(selfId);
    if (offscreenCanvas == nullptr) {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64, selfId);
    }
    offscreenCanvas->NativeSetHeihgt(height);
}

void FfiOHOSAceFrameworkOffscreenCanvasSetWidth(int64_t selfId, double width)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(selfId);
    if (offscreenCanvas == nullptr) {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64, selfId);
    }
    offscreenCanvas->NativeSetWidth(width);
}

double FfiOHOSAceFrameworkOffscreenCanvasGetHeight(int64_t selfId)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(selfId);
    if (offscreenCanvas == nullptr) {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return offscreenCanvas->NativeGetHeihgt();
}

double FfiOHOSAceFrameworkOffscreenCanvasGetWidth(int64_t selfId)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(selfId);
    if (offscreenCanvas == nullptr) {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64, selfId);
        return FFI_ERROR_CODE;
    }
    return offscreenCanvas->NativeGetWidth();
}

int64_t FfiOHOSAceFrameworkImageBitMapCtorByOffscreenCanvas(int64_t offscreenCanvasId)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(offscreenCanvasId);
    if (offscreenCanvas == nullptr) {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64,
            offscreenCanvasId);
        return FFI_ERROR_CODE;
    }
    return offscreenCanvas->TransferToImageBitmap();
}

int64_t FfiOHOSAceFrameworkOffscreenCanvasRenderingContext2DCtor(
    int64_t offscreenId, int32_t contextType, bool option, double width, double height)
{
    auto offscreenCanvas = FFIData::GetData<NativeOffscreenCanvas>(offscreenId);
    if (offscreenCanvas != nullptr) {
        if (offscreenCanvas->IsDetached()) {
            LOGE("OffscreenCanvas object is detached, id: %{public}" PRId64, offscreenId);
            return FFI_ERROR_CODE;
        }
        return offscreenCanvas->GetContext(contextType, option, width, height);
    } else {
        LOGE("offscreen canvas invert error, Cannot get NativeOffscreenCanvas by id: %{public}" PRId64, offscreenId);
    }
    return FFI_ERROR_CODE;
}
}