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

#include "core/components/select/select_theme.h"
#include "core/components_ng/pattern/option/option_paint_property.h"
#include "core/components_ng/render/drawing.h"

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

void PaintCustomDivider(SizeF optionSize, float horInterval, float iconHorInterval,
    PaintWrapper* paintWrapper, RSPath& path)
{
    CHECK_NULL_VOID(paintWrapper);
    auto props = AceType::DynamicCast<OptionPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(props);
    auto dividerWidth = static_cast<float>(props->GetDividerValue().strokeWidth.ConvertToPx());
    auto startMargin = static_cast<float>(props->GetDividerValue().startMargin.ConvertToPx());
    auto endMargin = static_cast<float>(props->GetDividerValue().endMargin.ConvertToPx());
    if (startMargin < 0.0f || startMargin > optionSize.Width()) {
        startMargin = horInterval + iconHorInterval;
    }
    if (endMargin < 0.0f || endMargin > optionSize.Width()) {
        endMargin = horInterval;
    }
    if ((startMargin + endMargin) > optionSize.Width()) {
        startMargin = horInterval + iconHorInterval;
        endMargin = horInterval;
    }
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto optionNode = renderContext->GetHost();
    CHECK_NULL_VOID(optionNode);
    auto layoutProperty = optionNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto dividerRtl = static_cast<float>(props->GetDividerValue().isRtl);
    dividerRtl = (textDirection == TextDirection::RTL) ? true : false;
    if (dividerRtl) {
        auto rtlStartMargin = startMargin;
        startMargin = endMargin;
        endMargin = rtlStartMargin;
    }
    path.AddRect(startMargin, -dividerWidth, optionSize.Width() - endMargin, dividerWidth);
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
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto optionNode = renderContext->GetHost();
    CHECK_NULL_VOID(optionNode);
    auto layoutProperty = optionNode->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto textDirection = layoutProperty->GetNonAutoLayoutDirection();
    auto isRtl = (textDirection == TextDirection::RTL) ? true : false;
    if (hasIcon) {
        iconHorInterval = static_cast<float>(selectTheme->GetIconSideLength().ConvertToPx()) +
                          static_cast<float>(selectTheme->GetIconContentPadding().ConvertToPx());
    }
    RSPath path;
    // draw divider above content, length = content width
    if (props->HasDivider()) {
        PaintCustomDivider(optionSize, horInterval, iconHorInterval, paintWrapper, path);
    } else {
        auto startX = isRtl ? optionSize.Width() - (horInterval + iconHorInterval) : horInterval + iconHorInterval;
        auto rectWidth = isRtl ? horInterval : optionSize.Width() - horInterval;
        path.AddRect(startX, 0, rectWidth, static_cast<float>(selectTheme->GetDefaultDividerWidth().ConvertToPx()));
    }
    RSBrush brush;
    auto dividerColor = props->HasDivider() ? props->GetDividerValue().color : selectTheme->GetLineColor();
    brush.SetColor(dividerColor.GetValue());
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawPath(path);
    canvas.DetachBrush();
}
} // namespace OHOS::Ace::NG