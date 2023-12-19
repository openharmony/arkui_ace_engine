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

#include "core/components_ng/pattern/option/option_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction OptionPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto option = weak.Upgrade();
        if (option) {
            // don't paint divider when pressed or hovered
            option->PaintDivider(canvas, paintWrapper);
        }
    };
}

void OptionPaintMethod::PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto props = DynamicCast<OptionPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(props);

    bool needDivider = props->GetNeedDivider().value_or(true);
    bool press = props->GetPress().value_or(false);
    bool hover = props->GetHover().value_or(false);
    if (!needDivider || press || hover) {
        return;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto optionSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto horInterval = static_cast<float>(selectTheme->GetMenuIconPadding().ConvertToPx()) -
                       static_cast<float>(selectTheme->GetOutPadding().ConvertToPx());
    auto hasIcon = props->GetHasIcon().value_or(false);
    float iconHorInterval = 0.0f;
    if (hasIcon) {
        iconHorInterval = static_cast<float>(selectTheme->GetIconSideLength().ConvertToPx()) +
                          static_cast<float>(selectTheme->GetIconContentPadding().ConvertToPx());
    }
    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(horInterval + iconHorInterval, 0, optionSize.Width() - horInterval,
        static_cast<float>(selectTheme->GetDefaultDividerWidth().ConvertToPx()));

    RSBrush brush;
    auto dividerColor = selectTheme->GetLineColor();
    brush.SetColor(dividerColor.GetValue());
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG