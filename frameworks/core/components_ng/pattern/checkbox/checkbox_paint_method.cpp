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
#include "core/components_ng/pattern/checkbox/checkbox_paint_method.h"

#include <optional>

#include "foundation/graphic/graphic_2d/rosen/modules/2d_graphics/include/draw/path.h"

#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/rect.h"
#include "base/geometry/rrect.h"
#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/color.h"
#include "core/components/theme/theme_manager.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction CheckBoxPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    InitializeParam();
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto checkbox = weak.Upgrade();
        if (checkbox) {
            checkbox->PaintCheckBox(canvas, paintWrapper);
        }
    };
    return paintFunc;
}

void CheckBoxPaintMethod::InitializeParam()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkBoxTheme = pipeline->GetThemeManager()->GetTheme<CheckboxTheme>();
    borderWidth_ = checkBoxTheme->GetBorderWidth().ConvertToPx();
    borderRadius_ = checkBoxTheme->GetBorderRadius().ConvertToPx();
    checkStroke_ = checkBoxTheme->GetCheckStroke().ConvertToPx();
    activeColor_ = checkBoxTheme->GetActiveColor();
}

void CheckBoxPaintMethod::PaintCheckBox(RSCanvas& canvas, PaintWrapper* paintWrapper) const
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<CheckBoxPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto contentSize = paintWrapper->GetContentSize();
    bool isSelected = false;
    if (paintProperty->HasCheckBoxSelect()) {
        isSelected = paintProperty->GetCheckBoxSelectValue();
    }

    auto color = activeColor_;
    if (paintProperty->HasCheckBoxSelectedColor()) {
        color = paintProperty->GetCheckBoxSelectedColorValue();
    }
    auto offset = paintWrapper->GetContentOffset();

    RSPen pen = RSPen();
    RSBrush brush = RSBrush();

    OffsetF paintOffset = OffsetF(offset.GetX(), offset.GetY());
    pen.SetWidth(borderWidth_);
    pen.SetAntiAlias(true);
    float strokeOffset = borderWidth_ / 2;
    paintOffset += OffsetF(strokeOffset, strokeOffset);
    contentSize.SetWidth(contentSize.Width() - borderWidth_);
    contentSize.SetHeight(contentSize.Height() - borderWidth_);

    if (isSelected) {
        brush.SetColor(ToRSColor(color));
        brush.SetAntiAlias(true);
        DrawActiveBorder(canvas, paintOffset, brush, contentSize);
        pen.SetColor(ToRSColor(Color::WHITE));
        DrawCheck(canvas, paintOffset, pen, contentSize);
    } else {
        pen.SetColor(ToRSColor(Color::GRAY));
        brush.SetColor(ToRSColor(Color::WHITE));
        brush.SetAlpha(50);
        DrawUnselected(canvas, paintOffset, pen, brush, contentSize);
    }
}

void CheckBoxPaintMethod::DrawUnselected(
    RSCanvas& canvas, const OffsetF& origin, RSPen& pen, RSBrush& brush, SizeF& paintSize) const
{
    pen.SetColor(ToRSColor(Color::GRAY));
    float originX = origin.GetX();
    float originY = origin.GetY();
    auto rrect = RSRoundRect(
        { originX, originY, paintSize.Width() + originX, paintSize.Height() + originY }, borderRadius_, borderRadius_);
    canvas.AttachPen(pen);
    canvas.DrawRoundRect(rrect);
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(rrect);
}

void CheckBoxPaintMethod::DrawActiveBorder(
    RSCanvas& canvas, const OffsetF& paintOffset, RSBrush& brush, const SizeF& paintSize) const
{
    float originX = paintOffset.GetX();
    float originY = paintOffset.GetY();
    auto rrect = RSRoundRect(
        { originX, originY, paintSize.Width() + originX, paintSize.Height() + originY }, borderRadius_, borderRadius_);
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(rrect);
}

void CheckBoxPaintMethod::DrawCheck(RSCanvas& canvas, const OffsetF& origin, RSPen& pen, const SizeF& paintSize) const
{
    constexpr float CHECK_MARK_START_X_POSITION = 0.25f;
    constexpr float CHECK_MARK_START_Y_POSITION = 0.49f;
    constexpr float CHECK_MARK_MIDDLE_X_POSITION = 0.44f;
    constexpr float CHECK_MARK_MIDDLE_Y_POSITION = 0.68f;
    constexpr float CHECK_MARK_END_X_POSITION = 0.76f;
    constexpr float CHECK_MARK_END_Y_POSITION = 0.33f;

    RSPath path;
    RSPen shadowPen = RSPen(pen);
    float originX = origin.GetX();
    float originY = origin.GetY();
    const Offset start =
        Offset(paintSize.Width() * CHECK_MARK_START_X_POSITION, paintSize.Width() * CHECK_MARK_START_Y_POSITION);
    const Offset middle =
        Offset(paintSize.Width() * CHECK_MARK_MIDDLE_X_POSITION, paintSize.Width() * CHECK_MARK_MIDDLE_Y_POSITION);
    const Offset end =
        Offset(paintSize.Width() * CHECK_MARK_END_X_POSITION, paintSize.Width() * CHECK_MARK_END_Y_POSITION);

    path.MoveTo(originX + start.GetX(), originY + start.GetY());
    path.LineTo(originX + middle.GetX(), originY + middle.GetY());
    shadowPen.SetCapStyle(RSPen::CapStyle::ROUND_CAP);
    shadowPen.SetWidth(checkStroke_);
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);

    path.MoveTo(originX + middle.GetX(), originY + middle.GetY());
    path.LineTo(originX + end.GetX(), originY + end.GetY());
    canvas.AttachPen(shadowPen);
    canvas.DrawPath(path);
    canvas.AttachPen(pen);
    canvas.DrawPath(path);
}
} // namespace OHOS::Ace::NG
