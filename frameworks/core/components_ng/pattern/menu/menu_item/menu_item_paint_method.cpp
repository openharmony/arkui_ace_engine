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

#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_method.h"

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_paint_property.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction MenuItemPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto menuItem = weak.Upgrade();
        if (menuItem) {
            CHECK_NULL_VOID(paintWrapper);
            auto props = DynamicCast<MenuItemPaintProperty>(paintWrapper->GetPaintProperty());
            CHECK_NULL_VOID(props);
            if (!props->GetDividerColor().has_value()) {
                return;
            }
            bool needDivider = props->GetNeedDivider().value_or(true);
            bool press = props->GetPress().value_or(false);
            bool hover = props->GetHover().value_or(false);
            if (!needDivider || press || hover) {
                return;
            }
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto selectTheme = pipeline->GetTheme<SelectTheme>();
            auto horInterval = Dimension(0.0f, DimensionUnit::PX);
            auto strokeWidth = Dimension(1.0f, DimensionUnit::PX);
            Color dividerColor = Color::TRANSPARENT;
            ItemDividerInfo info;
            if (selectTheme) {
                strokeWidth = selectTheme->GetDefaultDividerWidth();
                dividerColor =  selectTheme->GetLineColor();
            }
            auto itemSize = paintWrapper->GetGeometryNode()->GetFrameSize();
            info.width = itemSize.Width();
            info.strokeWidth = props->GetStrokeWidth().value_or(strokeWidth).ConvertToPxWithSize(itemSize.Height());
            info.startMargin = props->GetStartMargin().value_or(horInterval).ConvertToPxWithSize(itemSize.Width());
            info.endMargin = props->GetEndMargin().value_or(horInterval).ConvertToPxWithSize(itemSize.Width());
            info.color = props->GetDividerColor().value_or(dividerColor);
            menuItem->PaintDivider(canvas, paintWrapper, info);
        }
    };
}

void MenuItemPaintMethod::PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper, ItemDividerInfo info)
{
    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(info.startMargin, info.topMargin, info.width - info.endMargin,
        info.topMargin + info.strokeWidth);
    RSBrush brush;
    brush.SetColor(static_cast<int>(info.color.GetValue()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG
