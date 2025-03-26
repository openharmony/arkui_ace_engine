/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_PAINT_METHOD_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_PICKER_PAINT_METHOD_UTILS_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/pattern/picker/datepicker_row_layout_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
constexpr int32_t CONST_AVERAGE = 2;
constexpr int32_t BACKGROUND_HIGH = 12;
constexpr uint32_t SELECTED_ROW_BACKGROUND_COLOR = 0x33FFFFFF;
constexpr double  CONST_HALF_VALUE = 2.0;
constexpr int32_t CONST_DELTA_STEP = 1;
constexpr int32_t CONST_LINE_DIFF = 1;

class PickerPaintMethodCircleUtils {
public:
    PickerPaintMethodCircleUtils() {}

    virtual ~PickerPaintMethodCircleUtils() {}

    template<class T>
    CanvasDrawFunction GetContentDrawFunctionL(PaintWrapper* paintWrapper, const RefPtr<PipelineBase>& pipeline)
    {
        CHECK_NULL_RETURN(paintWrapper, nullptr);
        CHECK_NULL_RETURN(pipeline, nullptr);
        auto theme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_RETURN(theme, nullptr);
        auto dividerSpacing = pipeline->NormalizeToPx(theme->GetDividerSpacing());
        const auto& geometryNode = paintWrapper->GetGeometryNode();
        CHECK_NULL_RETURN(geometryNode, nullptr);
        auto frameRect = geometryNode->GetFrameRect();
        auto renderContext = paintWrapper->GetRenderContext();
        CHECK_NULL_RETURN(renderContext, nullptr);
        auto pickerNode = renderContext->GetHost();
        CHECK_NULL_RETURN(pickerNode, nullptr);
        auto layoutProperty = pickerNode->GetLayoutProperty<T>();
        CHECK_NULL_RETURN(layoutProperty, nullptr);

        Color paintcolor(SELECTED_ROW_BACKGROUND_COLOR);
        if (theme->GetOptionDecoration(false)) {
            paintcolor = theme->GetOptionDecoration(false)->GetBackgroundColor();
        }

        return [layoutProperty, frameRect, dividerSpacing, paintcolor](RSCanvas& canvas) {
            PaddingPropertyF padding = layoutProperty->CreatePaddingAndBorder();
            RectF contentRect = { padding.left.value_or(0), padding.top.value_or(0),
                frameRect.Width() - padding.Width(), frameRect.Height() - padding.Height() };
            if (GreatOrEqual(contentRect.Height(), dividerSpacing)) {
                double upperLine = (contentRect.Height() - dividerSpacing) / CONST_HALF_VALUE + contentRect.GetY();
                double downLine = (contentRect.Height() + dividerSpacing) / CONST_HALF_VALUE + contentRect.GetY();
                DrawCapsule(upperLine, downLine, contentRect.Width(), BACKGROUND_HIGH, paintcolor, canvas);
            }
        };
    }

protected:
    static void checkRepeat(std::vector<int32_t>& vec, int32_t _x, int32_t _y, int32_t up)
    {
        if (vec[_y - up] < _x) {
            vec[_y - up] = _x;
        }
    }

    static void DrawCapsule(int32_t up, int32_t down, int32_t width, int32_t margins, const Color &paintcolor,
        RSCanvas& canvas)
    {
        int32_t radius = (down - up) / CONST_AVERAGE;
        int32_t leftXc = margins + radius;
        int32_t rightXc = width - radius - margins;
        int32_t yC = up + radius;

        int32_t x = 0;
        int32_t y = radius;
        int32_t delta = CONST_AVERAGE - CONST_AVERAGE * radius;
        const double penWidth = 1.0;

        RSPen pen;
        pen.SetColor(paintcolor.GetValue());
        pen.SetWidth(penWidth);
        canvas.AttachPen(pen);

        // draw the capsule algorithm
        std::vector<int32_t> xOffset(down - up + CONST_LINE_DIFF);
        std::fill(xOffset.begin(), xOffset.end(), 0);
        while (x <= y) {
            checkRepeat(xOffset, x, yC + y, up);
            checkRepeat(xOffset, x, yC - y, up);
            checkRepeat(xOffset, y, yC + x, up);
            checkRepeat(xOffset, y, yC - x, up);

            if (delta > 0) {
                delta += CONST_AVERAGE * (x - y) + CONST_DELTA_STEP;
                y--;
            } else {
                delta += CONST_AVERAGE * x + CONST_DELTA_STEP;
            }
            x++;
        }
        for (int y = up; y <= down; y++) {
            canvas.DrawLine(RSPoint(leftXc - xOffset[y - up], y), RSPoint(rightXc + xOffset[y - up], y));
        }
        canvas.DetachPen();
    }
};
}
#endif
