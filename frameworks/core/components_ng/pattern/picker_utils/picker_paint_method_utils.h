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
constexpr int32_t SELECTED_ROW_BACKGROUND_COLOR = 0xffa9a9a9;

class PickerPaintMethodUtils {
public:
    PickerPaintMethodUtils()
    {
    }
    virtual ~PickerPaintMethodUtils()
    {
    }
protected:
    template<class T>
    CanvasDrawFunction GetContentDrawFunctionL(PaintWrapper* paintWrapper, const RefPtr<PipelineBase>& pipeline)
    {
        auto theme = pipeline->GetTheme<PickerTheme>();
        if (!theme->IsCircleDial()) {
            return nullptr;
        }

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
            if (contentRect.Height() >= dividerSpacing) {
                double upperLine = (contentRect.Height() - dividerSpacing) / 2.0 + contentRect.GetY();
                double downLine = (contentRect.Height() + dividerSpacing) / 2.0 + contentRect.GetY();
                DrawCircle(upperLine, downLine, contentRect.Width(), BACKGROUND_HIGH, paintcolor, canvas);
            }
        };
    }

    static void DrawCircle(int32_t up, int32_t down, int32_t width, int32_t margins, const Color &paintcolor,
        RSCanvas& canvas)
    {
        int32_t radius = (down -up) / CONST_AVERAGE;
        int32_t leftXc  = margins + radius;
        int32_t rightXc = width - radius - margins;
        int32_t yC = up + radius;

        int32_t x = 0;
        int32_t y = radius;
        int32_t delta = CONST_AVERAGE - CONST_AVERAGE * radius;

        RSPen pen;
        pen.SetColor(paintcolor.GetValue());
        pen.SetWidth(1.0);
        canvas.AttachPen(pen);
        while (x <= y) {
            canvas.DrawLine(RSPoint(leftXc - x, yC + y), RSPoint(rightXc + x, yC + y));
            canvas.DrawLine(RSPoint(leftXc - x, yC - y), RSPoint(rightXc + x, yC - y));
            canvas.DrawLine(RSPoint(leftXc - y, yC + x), RSPoint(rightXc + y, yC + x));
            canvas.DrawLine(RSPoint(leftXc - y, yC - x), RSPoint(rightXc + y, yC - x));

            if (delta > 0) {
                delta += CONST_AVERAGE * (x - y) + 1;
                y--;
            } else {
                delta += CONST_AVERAGE * x + 1;
            }
            x++;
        }

        canvas.DetachPen();
    }
};

}
#endif
