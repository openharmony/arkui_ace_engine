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
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

CanvasDrawFunction OptionPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto option = weak.Upgrade();
        if (option) {
            // don't paint divider when hovered
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
    bool hover = props->GetHover().value_or(false);
    if (!needDivider || hover) {
        return;
    }

    auto optionSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto horInterval = HORIZONTAL_INTERVAL_PHONE.ConvertToPx();

    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(horInterval, 0, optionSize.Width() - horInterval, DEFAULT_STROKE_WIDTH);
    LOGD("drawing option divider with length %{public}f", optionSize.Width() - 2 * horInterval);

    RSBrush brush;
    brush.SetColor(DIVIDER_COLOR);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
}
} // namespace OHOS::Ace::NG