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

#include "core/components_ng/render/shape_painter.h"

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/paint_state.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
void ShapePainter::SetPan(RSPen& pen, const ShapePaintProperty& shapePaintProperty)
{
    if (shapePaintProperty.HasAntiAlias()) {
        pen.SetAntiAlias(shapePaintProperty.GetAntiAliasValue());
    } else {
        pen.SetAntiAlias(shapePaintProperty.ANTIALIAS_DEFAULT);
    }

    if (shapePaintProperty.HasStrokeLineCap()) {
        int lineCap = shapePaintProperty.GetStrokeLineCapValue();
        if (static_cast<int>(RSPen::CapStyle::FLAT_CAP) == lineCap) {
            pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
        } else if (static_cast<int>(shapePaintProperty.SQUARE_CAP) == lineCap) {
            pen.SetCapStyle(RSPen::CapStyle::SQUARE_CAP);
        } else {
            pen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
        }
    } else {
        pen.SetCapStyle(RSPen::CapStyle::FLAT_CAP);
    }

    if (shapePaintProperty.HasStrokeLineJoin()) {
        int lineJoin = shapePaintProperty.GetStrokeLineJoinValue();
        if (static_cast<int>(RSPen::JoinStyle::BEVEL_JOIN) == lineJoin) {
            pen.SetJoinStyle(RSPen::JoinStyle::BEVEL_JOIN);
        } else if (static_cast<int>(RSPen::JoinStyle::MITER_JOIN) == lineJoin) {
            pen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
        } else {
            pen.SetJoinStyle(RSPen::JoinStyle::ROUND_JOIN);
        }
    } else {
        pen.SetJoinStyle(RSPen::JoinStyle::MITER_JOIN);
    }

    if (shapePaintProperty.HasStrokeWidth()) {
        pen.SetWidth(static_cast<RSScalar>(shapePaintProperty.GetStrokeWidthValue().ConvertToPx()));
    } else {
        pen.SetWidth(static_cast<RSScalar>(shapePaintProperty.STOKE_WIDTH_DEFAULT.ConvertToPx()));
    }

    Color strokeColor = Color::BLACK;
    if (shapePaintProperty.HasStroke()) {
        strokeColor = shapePaintProperty.GetStrokeValue();
    }
    RSColor rSColor(strokeColor.GetRed(), strokeColor.GetGreen(), strokeColor.GetBlue(), strokeColor.GetAlpha());
    if (shapePaintProperty.HasStrokeOpacity()) {
        rSColor.SetAlphaF(static_cast<RSScalar>(shapePaintProperty.GetStrokeOpacityValue()));
    }
    pen.SetColor(rSColor);

    if (shapePaintProperty.HasStrokeDashArray()) {
        auto lineDashState = shapePaintProperty.GetStrokeDashArrayValue();
        RSScalar intervals[lineDashState.size()];
        for (size_t i = 0; i < lineDashState.size(); ++i) {
            intervals[i] = static_cast<RSScalar>(lineDashState[i].ConvertToPx());
        }
        RSScalar phase = 0.0f;
        if (shapePaintProperty.HasStrokeDashOffset()) {
            phase = static_cast<RSScalar>(shapePaintProperty.GetStrokeDashOffsetValue().ConvertToPx());
        }
        pen.SetPathEffect(RSPathEffect::CreateDashPathEffect(intervals, lineDashState.size(), phase));
    }

    if (shapePaintProperty.HasStrokeMiterLimit()) {
        pen.SetMiterLimit(static_cast<RSScalar>(shapePaintProperty.GetStrokeMiterLimitValue()));
    }
}

void ShapePainter::SetBrush(RSBrush& brush, const ShapePaintProperty& shapePaintProperty)
{
    Color fillColor = Color::BLACK;
    if (shapePaintProperty.HasFill()) {
        fillColor = shapePaintProperty.GetFillValue();
    }
    RSColor rSColor(fillColor.GetRed(), fillColor.GetGreen(), fillColor.GetBlue(), fillColor.GetAlpha());
    if (shapePaintProperty.HasFillOpacity()) {
        rSColor.SetAlphaF(static_cast<RSScalar>(shapePaintProperty.GetFillOpacityValue()));
    }
    brush.SetColor(rSColor);
}
} // namespace OHOS::Ace::NG