/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/gauge/gauge_paint_method.h"

#include <algorithm>
#include <cmath>

#include "core/common/container.h"
#include "core/components/progress/progress_theme.h"
#include "core/components_ng/pattern/gauge/gauge_paint_property.h"
#include "core/components_ng/pattern/gauge/gauge_theme.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/render/paint_wrapper.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction GaugePaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto gauge = weak.Upgrade();
        if (gauge) {
            gauge->Paint(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void GaugePaintMethod::Paint(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<GaugePaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto offset = paintWrapper->GetContentOffset();
    auto contentSize = paintWrapper->GetContentSize();
    RenderRingInfo data;
    data.radius = std::min(contentSize.Width(), contentSize.Height()) / 2.0f;
    data.center = Offset(contentSize.Width() / 2.0f + offset.GetX(), contentSize.Height() / 2.0f + offset.GetY());
    float startAngle = DEFAULT_START_DEGREE;
    float endAngle = DEFAULT_END_DEGREE;
    if (paintProperty->GetStartAngle().has_value() && !std::isnan(paintProperty->GetStartAngle().value())) {
        startAngle = paintProperty->GetStartAngle().value();
    }
    if (paintProperty->GetEndAngle().has_value() && !std::isnan(paintProperty->GetEndAngle().value())) {
        endAngle = paintProperty->GetEndAngle().value();
    }
    float startDegree = startAngle;
    float sweepDegree = endAngle - startAngle;
    if (sweepDegree > 360.0f || sweepDegree < 0.0f) {
        sweepDegree = sweepDegree - floor(sweepDegree / 360.0f) * 360.0f;
    }
    if (NearZero(sweepDegree)) {
        sweepDegree = 360.0f;
    }
    auto theme = pipelineContext->GetTheme<ProgressTheme>();
    data.thickness = theme->GetTrackThickness().ConvertToPx();
    if (paintProperty->GetStrokeWidth().has_value() && paintProperty->GetStrokeWidth()->Value() > 0) {
        data.thickness =
            std::min(static_cast<float>(paintProperty->GetStrokeWidth()->ConvertToPx()), contentSize.Width() / 2);
    }
    std::vector<float> weights;
    if (paintProperty->GetValues().has_value()) {
        weights = paintProperty->GetValuesValue();
    } else {
        weights.push_back(1);
    }
    std::vector<Color> colors;
    if (paintProperty->GetColors().has_value()) {
        colors = paintProperty->GetColorsValue();
    } else {
        colors.push_back(Color::BLACK);
    }
    float min = paintProperty->GetMinValue();
    float max = paintProperty->GetMaxValue();
    float value = paintProperty->GetValueValue();

    if (colors.size() == 0 || colors.size() != weights.size()) {
        LOGE("color size is 0 or is not equal to weight size");
        return;
    }
    float totalWeight = 0.0f;
    for (const auto& weight : weights) {
        totalWeight += weight;
    }
    if (NearEqual(totalWeight, 0.0)) {
        LOGE("total weight is 0.0");
        return;
    }
    float currentStart = 0.0f;
    float highLightStart = 0.0f;
    size_t highLightIndex = 0;
    float ratio = 0.0f;
    if (max < min) {
        min = 0.0f;
        max = 100.0f;
    }
    if (value < min || value > max) {
        value = min;
    }
    if (min < max && value >= min && value <= max) {
        ratio = (value - min) / (max - min);
    }
    for (int32_t index = static_cast<int32_t>(colors.size()) - 1; index >= 0; --index) {
        data.color = colors[index];
        data.color.ChangeAlpha(UNSELECT_ALPHA);
        currentStart += weights[index];
        if (ShouldHighLight(totalWeight - currentStart, weights[index], ratio * totalWeight)) {
            highLightIndex = static_cast<size_t>(index);
            highLightStart = totalWeight - currentStart;
        }
        data.startDegree = startDegree + (1 - currentStart / totalWeight) * sweepDegree;
        data.sweepDegree = (weights[index] / totalWeight) * sweepDegree;
        DrawGauge(canvas, data);
    }
    // draw highlight part
    data.color = colors[highLightIndex];
    data.startDegree = startDegree + (highLightStart / totalWeight) * sweepDegree;
    data.sweepDegree = (weights[highLightIndex] / totalWeight) * sweepDegree;
    DrawGauge(canvas, data);
    data.startDegree = startDegree;
    data.sweepDegree = sweepDegree * ratio;
    DrawIndicator(canvas, data);
}

void GaugePaintMethod::DrawGauge(RSCanvas& canvas, RenderRingInfo data) const
{
    float thickness = data.thickness;
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(data.color.GetValue());
    pen.SetWidth(thickness);
    pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);

    canvas.AttachPen(pen);
    RSPath path;
    RSRect rRect(data.center.GetX() - data.radius + thickness / 2.0f,
        data.center.GetY() - data.radius + thickness / 2.0f, data.center.GetX() + data.radius - thickness / 2.0f,
        data.center.GetY() + data.radius - thickness / 2.0f);
    path.AddArc(rRect, data.startDegree - 90.0f, data.sweepDegree);
    canvas.DrawPath(path);
    canvas.DetachPen();
}

void GaugePaintMethod::DrawIndicator(RSCanvas& canvas, RenderRingInfo data) const
{
    RSPath path;
    float pathStartVertexX = data.center.GetX();
    float pathStartVertexY = data.center.GetY() - data.radius + (data.thickness / 2);
    path.MoveTo(pathStartVertexX, pathStartVertexY);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX - EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE + HEIGHT_OFFSET);
    path.LineTo(pathStartVertexX + EDGE, pathStartVertexY + EDGE);
    path.LineTo(pathStartVertexX, pathStartVertexY);

    canvas.Save();
    canvas.Rotate(data.startDegree + data.sweepDegree, data.center.GetX(), data.center.GetY());
    RSBrush paint;
    paint.SetColor(Color::WHITE.GetValue());
    canvas.AttachBrush(paint);
    canvas.DrawPath(path);
    canvas.DetachBrush();

    RSPen pen;
    pen.SetColor(Color::BLACK.GetValue());
    pen.SetWidth(INDICATOR_STROKE_WIDTH);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
    canvas.DetachPen();
    canvas.Restore();
}

bool GaugePaintMethod::ShouldHighLight(const float start, const float interval, const float percent) const
{
    if (LessOrEqual(percent, start + interval) && GreatOrEqual(percent, start)) {
        return true;
    }
    return false;
}

} // namespace OHOS::Ace::NG
