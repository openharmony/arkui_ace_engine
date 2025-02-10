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

#include "core/components_ng/pattern/time_picker/timepicker_paint_method.h"

#include "core/components/common/properties/color.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/pattern/time_picker/timepicker_layout_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/time_picker/timepicker_row_pattern.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DIVIDER_LINE_WIDTH = 1.0f;
} // namespace

CanvasDrawFunction TimePickerPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    if (theme->IsCircleDial()) {
        if (!circleUtils_) {
            circleUtils_ = new PickerPaintMethodCircleUtils();
            CHECK_NULL_RETURN(circleUtils_, nullptr);
        }
        CanvasDrawFunction drawFun =
            circleUtils_->GetContentDrawFunctionL<TimePickerLayoutProperty>(paintWrapper, pipeline);
        CHECK_NULL_RETURN(drawFun, nullptr);
        return [weak = WeakClaim(this), drawFun](RSCanvas& canvas) {
            auto picker = weak.Upgrade();
            CHECK_NULL_VOID(picker);
            drawFun(canvas);
        };
    }

    return nullptr;
}

CanvasDrawFunction TimePickerPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto theme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(theme, nullptr);
    CHECK_EQUAL_RETURN(theme->IsCircleDial(), true, nullptr);
    auto dividerColor = theme->GetDividerColor();
    const auto& geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, nullptr);
    auto frameRect = geometryNode->GetFrameRect();

    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto pickerNode = renderContext->GetHost();
    CHECK_NULL_RETURN(pickerNode, nullptr);
    auto layoutProperty = pickerNode->GetLayoutProperty<TimePickerLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, nullptr);

    auto dividerSpacing = pipeline->NormalizeToPx(theme->GetDividerSpacing());
    auto timePickerPattern = pickerNode->GetPattern<TimePickerRowPattern>();
    CHECK_NULL_RETURN(timePickerPattern, nullptr);
    auto fontScale = timePickerPattern->GetPaintDividerSpacing();
    dividerSpacing = dividerSpacing * fontScale;
    return [weak = WeakClaim(this), dividerLineWidth = DIVIDER_LINE_WIDTH, layoutProperty, frameRect, dividerSpacing,
               dividerColor](RSCanvas& canvas) {
        auto picker = weak.Upgrade();
        CHECK_NULL_VOID(picker);

        PaddingPropertyF padding = layoutProperty->CreatePaddingAndBorder();
        RectF contentRect = { padding.left.value_or(0), padding.top.value_or(0), frameRect.Width() - padding.Width(),
            frameRect.Height() - padding.Height() };
        if (contentRect.Height() >= dividerSpacing) {
            DividerPainter dividerPainter(dividerLineWidth, contentRect.Width(), false, dividerColor, LineCap::SQUARE);
            double upperLine = (contentRect.Height() - dividerSpacing) / 2.0 + contentRect.GetY();
            double downLine = (contentRect.Height() + dividerSpacing) / 2.0 + contentRect.GetY();

            OffsetF offset = OffsetF(contentRect.GetX(), upperLine);
            dividerPainter.DrawLine(canvas, offset);
            OffsetF offsetY = OffsetF(contentRect.GetX(), downLine);
            dividerPainter.DrawLine(canvas, offsetY);
        }
    };
}

} // namespace OHOS::Ace::NG
