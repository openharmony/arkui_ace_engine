/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item_group/menu_item_group_paint_property.h"
#include "core/components_ng/pattern/menu/menu_theme.h"
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
            CHECK_NULL_VOID_NOLOG(paintWrapper);
            auto props = DynamicCast<MenuItemGroupPaintProperty>(paintWrapper->GetPaintProperty());
            CHECK_NULL_VOID_NOLOG(props);
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
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    CHECK_NULL_VOID(selectTheme);
    auto horInterval = static_cast<float>(selectTheme->GetMenuIconPadding().ConvertToPx()) -
                       static_cast<float>(selectTheme->GetOutPadding().ConvertToPx());
    auto verInterval = static_cast<float>(selectTheme->GetDividerPaddingVertical().ConvertToPx());
    if (!isHeader) {
        verInterval =
            groupSize.Height() - verInterval - static_cast<float>(selectTheme->GetDefaultDividerWidth().ConvertToPx());
    }
    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(horInterval, verInterval, groupSize.Width() - horInterval,
        verInterval + static_cast<float>(selectTheme->GetDefaultDividerWidth().ConvertToPx()));

    RSBrush brush;
    auto dividerColor = selectTheme->GetLineColor();
    brush.SetColor(static_cast<int>(dividerColor.GetValue()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
}
} // namespace OHOS::Ace::NG
