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

#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_method.h"

#include "base/geometry/ng/offset_t.h"
#include "base/utils/utils.h"
#include "core/components/divider/divider_theme.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
#include "core/components_ng/pattern/option/option_theme.h"
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction MenuItemGroupPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto group = weak.Upgrade();
        if (group) {
            CHECK_NULL_VOID(paintWrapper);
            auto props = DynamicCast<MenuItemGroupPaintProperty>(paintWrapper->GetPaintProperty());
            CHECK_NULL_VOID(props);
            bool needHeaderPadding = props->GetNeedHeaderPadding().value_or(false);
            if (needHeaderPadding) {
                group->PaintDivider(canvas, paintWrapper, true);
            }
            bool needFooterPadding = props->GetNeedFooterPadding().value_or(false);
            if (needFooterPadding) {
                group->PaintDivider(canvas, paintWrapper, false);
            }
        }
    };
}

void MenuItemGroupPaintMethod::PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper, bool isHeader)
{
    auto groupSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    float horInterval = DIVIDER_PADDING.ConvertToPx();
    float verInterval = VERTICAL_INTERVAL_PHONE.ConvertToPx();
    if (!isHeader) {
        verInterval = groupSize.Height() - verInterval;
    }
    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(horInterval, verInterval, groupSize.Width() - horInterval, verInterval + DEFAULT_STROKE_WIDTH);

    RSBrush brush;
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<DividerTheme>();
    CHECK_NULL_VOID(theme);
    auto dividerColor = theme->GetColor();
    brush.SetColor(dividerColor.GetValue());
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
}
} // namespace OHOS::Ace::NG