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


#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/canvas_renderer.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/utils.h"
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
    x = PipelineBase::Vp2PxWithCurrentDensity(x);
    y = PipelineBase::Vp2PxWithCurrentDensity(y);
    width = PipelineBase::Vp2PxWithCurrentDensity(width);
    height = PipelineBase::Vp2PxWithCurrentDensity(height);
    Rect rect = Rect(x, y, width, height);
    return rect;
}

BezierCurveParam GetBezierCurveParam(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y)
{
    BezierCurveParam param;
    param.cp1x = PipelineBase::Vp2PxWithCurrentDensity(cp1x);
    param.cp1y = PipelineBase::Vp2PxWithCurrentDensity(cp1y);
    param.cp2x = PipelineBase::Vp2PxWithCurrentDensity(cp2x);
    param.cp2y = PipelineBase::Vp2PxWithCurrentDensity(cp2y);
    param.x = PipelineBase::Vp2PxWithCurrentDensity(x);
    param.y = PipelineBase::Vp2PxWithCurrentDensity(y);
    return param;
}

QuadraticCurveParam GetQuadraticCurveParam(double cpx, double cpy, double x, double y)
{
    QuadraticCurveParam param;
    param.cpx = PipelineBase::Vp2PxWithCurrentDensity(cpx);
    param.cpy = PipelineBase::Vp2PxWithCurrentDensity(cpy);
    param.x = PipelineBase::Vp2PxWithCurrentDensity(x);
    param.y = PipelineBase::Vp2PxWithCurrentDensity(y);
    return param;
}

ArcParam GetArcParam(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise)
{
    ArcParam param;
    param.x = PipelineBase::Vp2PxWithCurrentDensity(x);
    param.y = PipelineBase::Vp2PxWithCurrentDensity(y);
    param.radius = PipelineBase::Vp2PxWithCurrentDensity(radius);
    param.startAngle = startAngle;
    param.endAngle = endAngle;
    param.anticlockwise = anticlockwise;
    return param;
}

ArcToParam GetArcToParam(double x1, double y1, double x2, double y2, double radius)
{
    ArcToParam param;
    param.x1 = PipelineBase::Vp2PxWithCurrentDensity(x1);
    param.y1 = PipelineBase::Vp2PxWithCurrentDensity(y1);
    param.x2 = PipelineBase::Vp2PxWithCurrentDensity(x2);
    param.y2 = PipelineBase::Vp2PxWithCurrentDensity(y2);
    param.radius = PipelineBase::Vp2PxWithCurrentDensity(radius);
    return param;
}

EllipseParam GetEllipseParam(double x, double y, double radiusX, double radiusY, double rotation, double startAngle,
    double endAngle, bool anticlockwise)
{
    EllipseParam param;
    param.x = PipelineBase::Vp2PxWithCurrentDensity(x);
    param.y = PipelineBase::Vp2PxWithCurrentDensity(y);
    param.radiusX = PipelineBase::Vp2PxWithCurrentDensity(radiusX);
    param.radiusY = PipelineBase::Vp2PxWithCurrentDensity(radiusY);
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
    param.translateX = PipelineBase::Vp2PxWithCurrentDensity(translateX);
    param.translateY = PipelineBase::Vp2PxWithCurrentDensity(translateY);
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

double FfiOHOSAceFrameworkRenderingContextGetWidth(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return -1;
    }
    return context->GetWidth();
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

void FfiOHOSAceFrameworkRenderingContextSetFilter(int64_t contextId, const char* value)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context == nullptr) {
        return;
    }
    std::string filter = value;
    context->SetFilter(filter);
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

void FfiOHOSAceFrameworkRenderingContextSetLineWidth(int64_t contextId, double lineWidth)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        lineWidth = PipelineBase::Vp2PxWithCurrentDensity(lineWidth);
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
        limit = PipelineBase::Vp2PxWithCurrentDensity(limit);
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
        lineDashOffset = PipelineBase::Vp2PxWithCurrentDensity(lineDashOffset);
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
        offsetX = PipelineBase::Vp2PxWithCurrentDensity(offsetX);
        context->SetShadowOffsetX(offsetX);
    } else {
        LOGE("canvas shadowOffsetX error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextSetShadowOffsetY(int64_t contextId, double offsetY)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        offsetY = PipelineBase::Vp2PxWithCurrentDensity(offsetY);
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
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        context->FillText(x, y, text);
    } else {
        LOGE("canvas fillText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextStrokeText(int64_t contextId, double x, double y, const char* text)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        context->StrokeText(x, y, text);
    } else {
        LOGE("canvas strokeText error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
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
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        context->MoveTo(x, y);
    } else {
        LOGE("canvas moveTo error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
}

void FfiOHOSAceFrameworkRenderingContextLineTo(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
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

void FfiOHOSAceFrameworkRenderingContextClip(int64_t contextId)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        context->Clip();
    } else {
        LOGE("canvas clip error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
    }
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

void FfiOHOSAceFrameworkRenderingContextTranslate(int64_t contextId, double x, double y)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
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
        x0 = PipelineBase::Vp2PxWithCurrentDensity(x0);
        y0 = PipelineBase::Vp2PxWithCurrentDensity(y0);
        x1 = PipelineBase::Vp2PxWithCurrentDensity(x1);
        y1 = PipelineBase::Vp2PxWithCurrentDensity(y1);
        return context->CreateLinearGradient(x0, y0, x1, y1);
    } else {
        LOGE("canvas createLinearGradient error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return 0;
    }
}

int64_t FfiOHOSAceFrameworkRenderingContextCreateRadialGradient(
    int64_t contextId, double x0, double y0, double r0, double x1, double y1, double r1)
{
    auto context = FFIData::GetData<NativeCanvasRenderer>(contextId);
    if (context != nullptr) {
        x0 = PipelineBase::Vp2PxWithCurrentDensity(x0);
        y0 = PipelineBase::Vp2PxWithCurrentDensity(y0);
        r0 = PipelineBase::Vp2PxWithCurrentDensity(r0);
        x1 = PipelineBase::Vp2PxWithCurrentDensity(x1);
        y1 = PipelineBase::Vp2PxWithCurrentDensity(y1);
        r1 = PipelineBase::Vp2PxWithCurrentDensity(r1);
        return context->CreateRadialGradient(x0, y0, r0, x1, y1, r1);
    } else {
        LOGE("canvas createRadialGradient error, Cannot get NativeCanvasRenderer by id: %{public}" PRId64, contextId);
        return 0;
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
        return 0;
    }

    left = PipelineBase::Vp2PxWithCurrentDensity(left);
    top = PipelineBase::Vp2PxWithCurrentDensity(top);
    width = PipelineBase::Vp2PxWithCurrentDensity(width);
    height = PipelineBase::Vp2PxWithCurrentDensity(height);
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

void FfiOHOSAceFrameworkCanvasPathSetTransform(int64_t selfId, TransformParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double translateX = PipelineBase::Vp2PxWithCurrentDensity(params.translateX);
        double translateY = PipelineBase::Vp2PxWithCurrentDensity(params.translateY);
        path2d->SetTransform(params.scaleX, params.skewX, params.skewY, params.scaleY, translateX, translateY);
    } else {
        LOGE("canvas path2D setTransform error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathMoveTo(int64_t selfId, double x, double y)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        path2d->MoveTo(x, y);
    } else {
        LOGE("canvas path2D moveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathLineTo(int64_t selfId, double x, double y)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        x = PipelineBase::Vp2PxWithCurrentDensity(x);
        y = PipelineBase::Vp2PxWithCurrentDensity(y);
        path2d->LineTo(x, y);
    } else {
        LOGE("canvas path2D lineTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathArc(int64_t selfId, ArcParams params, bool anticlockwise)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double x = PipelineBase::Vp2PxWithCurrentDensity(params.x);
        double y = PipelineBase::Vp2PxWithCurrentDensity(params.y);
        double radius = PipelineBase::Vp2PxWithCurrentDensity(params.radius);
        path2d->Arc(x, y, radius, params.startAngle, params.endAngle, anticlockwise);
    } else {
        LOGE("canvas path2D arc error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathArcTo(int64_t selfId, ArcToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double x1 = PipelineBase::Vp2PxWithCurrentDensity(params.x1);
        double y1 = PipelineBase::Vp2PxWithCurrentDensity(params.y1);
        double x2 = PipelineBase::Vp2PxWithCurrentDensity(params.x2);
        double y2 = PipelineBase::Vp2PxWithCurrentDensity(params.y2);
        double radius = PipelineBase::Vp2PxWithCurrentDensity(params.radius);
        path2d->ArcTo(x1, y1, x2, y2, radius);
    } else {
        LOGE("canvas path2D arcTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathQuadraticCurveTo(int64_t selfId, QuadraticCurveToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double cpx = PipelineBase::Vp2PxWithCurrentDensity(params.cpx);
        double cpy = PipelineBase::Vp2PxWithCurrentDensity(params.cpy);
        double x = PipelineBase::Vp2PxWithCurrentDensity(params.x);
        double y = PipelineBase::Vp2PxWithCurrentDensity(params.y);
        path2d->QuadraticCurveTo(cpx, cpy, x, y);
    } else {
        LOGE("canvas path2D quadraticCurveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathBezierCurveTo(int64_t selfId, BezierCurveToParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double cp1x = PipelineBase::Vp2PxWithCurrentDensity(params.cp1x);
        double cp1y = PipelineBase::Vp2PxWithCurrentDensity(params.cp1y);
        double cp2x = PipelineBase::Vp2PxWithCurrentDensity(params.cp2x);
        double cp2y = PipelineBase::Vp2PxWithCurrentDensity(params.cp2y);
        double x = PipelineBase::Vp2PxWithCurrentDensity(params.x);
        double y = PipelineBase::Vp2PxWithCurrentDensity(params.y);
        path2d->BezierCurveTo(cp1x, cp1y, cp2x, cp2y, x, y);
    } else {
        LOGE("canvas path2D bezierCurveTo error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathEllipse(int64_t selfId, EllipseParams params, bool anticlockwise)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double x = PipelineBase::Vp2PxWithCurrentDensity(params.x);
        double y = PipelineBase::Vp2PxWithCurrentDensity(params.y);
        double radiusX = PipelineBase::Vp2PxWithCurrentDensity(params.radiusX);
        double radiusY = PipelineBase::Vp2PxWithCurrentDensity(params.radiusY);
        path2d->Ellipse(x, y, radiusX, radiusY, params.rotation, params.startAngle, params.endAngle, anticlockwise);
    } else {
        LOGE("canvas path2D ellipse error, Cannot get NativeCanvasPath by id: %{public}" PRId64, selfId);
    }
}

void FfiOHOSAceFrameworkCanvasPathRect(int64_t selfId, RectParams params)
{
    auto path2d = FFIData::GetData<NativeCanvasPath>(selfId);
    if (path2d != nullptr) {
        double x = PipelineBase::Vp2PxWithCurrentDensity(params.x);
        double y = PipelineBase::Vp2PxWithCurrentDensity(params.y);
        double width = PipelineBase::Vp2PxWithCurrentDensity(params.width);
        double height = PipelineBase::Vp2PxWithCurrentDensity(params.height);
        path2d->Rect(x, y, width, height);
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
}
