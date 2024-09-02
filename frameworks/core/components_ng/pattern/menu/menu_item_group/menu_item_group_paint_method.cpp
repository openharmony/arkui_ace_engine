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

#include "core/components/select/select_theme.h"
#include "core/components_ng/render/drawing.h"

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
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            GroupDividerInfo info = group->PreparePaintData(pipeline, props, paintWrapper);
            bool needHeaderDivider = props->GetNeedHeaderDivider().value_or(true);
            bool needFooterDivider = props->GetNeedFooterDivider().value_or(true);
            if (needHeaderPadding & needHeaderDivider) {
                group->PaintDivider(canvas, paintWrapper, info);
            }
            bool needFooterPadding = props->GetNeedFooterPadding().value_or(false);
            if (needFooterPadding && needFooterDivider) {
                auto groupSize = paintWrapper->GetGeometryNode()->GetFrameSize();
                info.topMargin = groupSize.Height() - info.strokeWidth;
                group->PaintDivider(canvas, paintWrapper, info);
            }
        }
    };
}

GroupDividerInfo MenuItemGroupPaintMethod::PreparePaintData(
    RefPtr<PipelineBase>& pipeline, RefPtr<MenuItemGroupPaintProperty>& props, PaintWrapper* paintWrapper)
{
    auto selectTheme = pipeline->GetTheme<SelectTheme>();
    auto horInterval = Dimension(0.0f, DimensionUnit::PX);
    auto strokeWidth = Dimension(1.0f, DimensionUnit::PX);
    Color dividerColor = Color::TRANSPARENT;
    GroupDividerInfo info;
    if (selectTheme) {
        float horIntervalF = static_cast<float>(selectTheme->GetMenuIconPadding().ConvertToPx()) -
            static_cast<float>(selectTheme->GetOutPadding().ConvertToPx());
        horInterval = Dimension(horIntervalF, DimensionUnit::PX);
        strokeWidth = selectTheme->GetDefaultDividerWidth();
        dividerColor =  selectTheme->GetLineColor();
    }
    auto groupSize = paintWrapper->GetGeometryNode()->GetFrameSize();
    info.width = groupSize.Width();
    if (props->GetStrokeWidth()->Unit() != DimensionUnit::INVALID) {
        info.strokeWidth = props->GetStrokeWidth().value_or(strokeWidth).ConvertToPxWithSize(groupSize.Height());
    } else {
        info.strokeWidth = strokeWidth.ConvertToPx();
    }
    if (props->GetStartMargin()->Unit() != DimensionUnit::INVALID) {
        info.startMargin = props->GetStartMargin().value_or(horInterval).ConvertToPxWithSize(groupSize.Width());
    } else {
        info.startMargin = horInterval.ConvertToPx();
    }
    if (props->GetEndMargin()->Unit() != DimensionUnit::INVALID) {
        info.endMargin = props->GetEndMargin().value_or(horInterval).ConvertToPxWithSize(groupSize.Width());
    } else {
        info.endMargin = horInterval.ConvertToPx();
    }
    info.color = props->GetDividerColor().value_or(dividerColor);
    if (info.color.GetValue() == Color::FOREGROUND.GetValue()) {
        info.color = dividerColor;
    }
    return info;
}

void MenuItemGroupPaintMethod::PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper, GroupDividerInfo info)
{
    RSPath path;
    // draw divider above content, length = content width
    path.AddRect(info.startMargin, info.topMargin, info.width - info.endMargin, info.topMargin + info.strokeWidth);
    RSBrush brush;
    brush.SetColor(static_cast<int>(info.color.GetValue()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG
