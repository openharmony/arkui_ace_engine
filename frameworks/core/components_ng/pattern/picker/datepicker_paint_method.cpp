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

#include "core/components_ng/pattern/picker/datepicker_paint_method.h"

#include "third_party/skia/include/effects/SkGradientShader.h"

#include "base/geometry/rect.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DIVIDER_LINE_WIDTH = 1.0f;
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
} // namespace

CanvasDrawFunction DatePickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto dividerColor = theme->GetDividerColor();

    auto dividerSpacing = pipeline->NormalizeToPx(theme->GetDividerSpacing());
    auto geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameRect();
    return [weak = WeakClaim(this), dividerLineWidth = DIVIDER_LINE_WIDTH, frameRect, dividerSpacing, dividerColor,
               enabled = enabled_](RSCanvas& canvas) {
        DividerPainter dividerPainter(dividerLineWidth, frameRect.Width(), false, dividerColor, LineCap::SQUARE);
        double upperLine = (frameRect.Height() - dividerSpacing) / 2.0;
        double downLine = (frameRect.Height() + dividerSpacing) / 2.0;

        OffsetF offset = OffsetF(0.0f, upperLine);
        dividerPainter.DrawLine(canvas, offset);
        OffsetF offsetY = OffsetF(0.0f, downLine);
        dividerPainter.DrawLine(canvas, offsetY);
        auto picker = weak.Upgrade();
        CHECK_NULL_VOID_NOLOG(picker);
        if (enabled) {
            picker->PaintGradient(canvas, frameRect);
        } else {
            picker->PaintDisable(canvas, frameRect.Width(), frameRect.Height());
        }
    };
}

void DatePickerPaintMethod::PaintGradient(RSCanvas& canvas, const RectF& frameRect)
{
    SkCanvas* skCanvas = canvas.GetImpl<Rosen::Drawing::SkiaCanvas>()->ExportSkCanvas();
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    double gradientHeight = pipeline->NormalizeToPx(theme->GetGradientHeight());
    if (NearZero(gradientHeight)) {
        return;
    }

    auto height = static_cast<float>((frameRect.Height() - theme->GetDividerSpacing().ConvertToPx()) / 2);
    // Paint gradient rect over the picker content.
    SkPaint paint;
    SkPoint beginPoint = SkPoint::Make(SkDoubleToScalar(0.0f), SkDoubleToScalar(0.0f));
    SkPoint endPoint = SkPoint::Make(SkDoubleToScalar(0.0f), SkDoubleToScalar(frameRect.Height()));
    SkPoint points[2] = { beginPoint, endPoint };
    auto backDecoration = theme->GetPopupDecoration(false);
    Color endColor = backDecoration ? backDecoration->GetBackgroundColor() : Color::WHITE;

    Color middleColor = endColor.ChangeAlpha(0);
    SkColor colors[] = { endColor.GetValue(), middleColor.GetValue(), middleColor.GetValue(), endColor.GetValue() };
    const float stopPositions[] = { 0.0f, height / frameRect.Bottom(),
        (frameRect.Bottom() - height) / frameRect.Bottom(), 1.0f };
#ifdef USE_SYSTEM_SKIA
    paint.setShader(
        SkGradientShader::MakeLinear(points, colors, stopPositions, std::size(colors), SkShader::kClamp_TileMode));
#else
    paint.setShader(SkGradientShader::MakeLinear(points, colors, stopPositions, std::size(colors), SkTileMode::kClamp));
#endif
    skCanvas->drawRect({ 0.0f, 0.0f, frameRect.Right(), frameRect.Bottom() }, paint);
}

void DatePickerPaintMethod::PaintDisable(RSCanvas& canvas, double X, double Y)
{
    double centerY = Y;
    double centerX = X;
    RSRect rRect(0, 0, centerX, centerY);
    RSPath path;
    path.AddRoundRect(rRect, 0, 0, RSPathDirection::CW_DIRECTION);
    RSPen pen;
    RSBrush brush;
    brush.SetColor(float(DISABLED_ALPHA) / ENABLED_ALPHA);
    pen.SetColor(float(DISABLED_ALPHA) / ENABLED_ALPHA);
    canvas.AttachBrush(brush);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
}

} // namespace OHOS::Ace::NG