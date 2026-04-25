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

#include "core/components_ng/render/circle_painter.h"

#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/shape_painter.h"
namespace OHOS::Ace::NG {
namespace {
std::shared_ptr<RSColorSpace> GetCircleStrokeColorSpace(const Color& color)
{
    if (color.GetColorSpace() == ColorSpace::BT2020) {
        return RSColorSpace::CreateRGB(RSCMSTransferFuncType::SRGB, RSCMSMatrixType::REC2020);
    }
    if (color.GetColorSpace() == ColorSpace::DISPLAY_P3) {
        return RSColorSpace::CreateRGB(RSCMSTransferFuncType::SRGB, RSCMSMatrixType::DCIP3);
    }
    return RSColorSpace::CreateSRGB();
}

bool NeedUseHdrStrokeColor(const Color& color)
{
    return color.GetHeadRoomColor().has_value() || color.GetColorSpace() == ColorSpace::BT2020 ||
           color.GetColorSpace() == ColorSpace::DISPLAY_P3;
}

RSColor4f GetCircleStrokeColor4f(const Color& color, double strokeOpacity)
{
    return { static_cast<RSScalar>(color.GetRed() / 255.0 * strokeOpacity),
        static_cast<RSScalar>(color.GetGreen() / 255.0 * strokeOpacity),
        static_cast<RSScalar>(color.GetBlue() / 255.0 * strokeOpacity),
        static_cast<RSScalar>(color.GetAlpha() / 255.0 * strokeOpacity) };
}

void UpdateCircleStrokeColorIfNeeded(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    Color strokeColor = Color::TRANSPARENT;
    if (shapePaintProperty.HasStroke()) {
        strokeColor = shapePaintProperty.GetStrokeValue();
    }
    if (!NeedUseHdrStrokeColor(strokeColor)) {
        return;
    }

    double strokeOpacity = 1.0;
    if (shapePaintProperty.HasStrokeOpacity()) {
        strokeOpacity = shapePaintProperty.GetStrokeOpacityValue();
    }

    if (strokeColor.GetHeadRoomColor().has_value()) {
        const auto hdr = strokeColor.GetHeadRoomColor().value();
        RSUIColor uiColor(hdr.red * strokeOpacity, hdr.green * strokeOpacity, hdr.blue * strokeOpacity,
            hdr.alpha * strokeOpacity, hdr.headRoom);
        pen.SetUIColor(uiColor, GetCircleStrokeColorSpace(strokeColor));
        return;
    }

    pen.SetColor(GetCircleStrokeColor4f(strokeColor, strokeOpacity), GetCircleStrokeColorSpace(strokeColor));
}

bool SetCirclePen(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    if (!ShapePainter::SetPen(pen, shapePaintProperty)) {
        return false;
    }
    UpdateCircleStrokeColorIfNeeded(pen, shapePaintProperty);
    return true;
}
} // namespace

void CirclePainter::DrawCircle(
    RSCanvas& canvas, float radius, const OffsetF& offset, const ShapePaintProperty& shapePaintProperty)
{
    RSPen pen;
    RSBrush brush;
    if (SetCirclePen(pen, shapePaintProperty)) {
        canvas.AttachPen(pen);
    }
    ShapePainter::SetBrush(brush, shapePaintProperty);
    canvas.AttachBrush(brush);
    PointF centerPoint = PointF(radius + offset.GetX(), radius + offset.GetY());
    canvas.DrawCircle(ToRSPoint(centerPoint), radius);
    canvas.DetachBrush();
    canvas.DetachPen();
}
} // namespace OHOS::Ace::NG
