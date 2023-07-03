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

#include "base/geometry/rect.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/picker/datepicker_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DIVIDER_LINE_WIDTH = 1.0f;
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
} // namespace

CanvasDrawFunction DatePickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    auto dividerColor = theme->GetDividerColor();

    auto dividerSpacing = pipeline->NormalizeToPx(theme->GetDividerSpacing());
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameRect();
    return [weak = WeakClaim(this), dividerLineWidth = DIVIDER_LINE_WIDTH, frameRect, dividerSpacing, dividerColor,
               enabled = enabled_, pattern = pattern_](RSCanvas& canvas) {
        DividerPainter dividerPainter(dividerLineWidth, frameRect.Width(), false, dividerColor, LineCap::SQUARE);
        auto datePickerPattern = DynamicCast<DatePickerPattern>(pattern.Upgrade());
        CHECK_NULL_VOID_NOLOG(datePickerPattern);
        auto height = dividerSpacing;
        if (datePickerPattern->GetResizeFlag()) {
            height = datePickerPattern->GetResizePickerItemHeight();
        }
        double upperLine = (frameRect.Height() - height) / 2.0;
        double downLine = (frameRect.Height() + height) / 2.0;

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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();
    auto gradientHeight = static_cast<float>(pipeline->NormalizeToPx(theme->GetGradientHeight()));
    if (NearZero(gradientHeight)) {
        return;
    }

    // Paint gradient rect over the picker content.
    RSBrush topBrush;
    RSRect rect(0.0f, frameRect.Right(), 0.0f, frameRect.Bottom());
    RSPoint topStartPoint;
    topStartPoint.SetX(0.0f);
    topStartPoint.SetY(0.0f);
    RSPoint topEndPoint;
    topEndPoint.SetX(0.0f);
    topEndPoint.SetY(frameRect.Height());
    Color endColor = backgroundColor_;
    Color middleColor = endColor.ChangeAlpha(0);
    std::vector<float> topPos { 0.0f, gradientHeight / frameRect.Bottom(),
        (frameRect.Bottom() - gradientHeight) / frameRect.Bottom(), 1.0f };
    std::vector<RSColorQuad> topColors { endColor.GetValue(), middleColor.GetValue(), middleColor.GetValue(),
        endColor.GetValue() };
    topBrush.SetShaderEffect(
        RSShaderEffect::CreateLinearGradient(topStartPoint, topEndPoint, topColors, topPos, RSTileMode::CLAMP));
    canvas.DetachPen().AttachBrush(topBrush);
    canvas.DrawRect(rect);
    canvas.DetachBrush();
    canvas.Restore();
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
