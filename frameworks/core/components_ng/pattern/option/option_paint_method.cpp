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
#include "core/components_ng/pattern/shape/rect_paint_property.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

const Dimension ROUND_RADIUS_PHONE = 12.0_vp;
constexpr double DEFAULT_STROKE_WIDTH = 1.0f;
constexpr uint32_t DIVIDER_COLOR = 0x0C0DDDDD;

} // namespace

CanvasDrawFunction OptionPaintMethod::GetOverlayDrawFunction(PaintWrapper* paintWrapper)
{
    return [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto option = weak.Upgrade();
        if (option) {
            LOGI("start painting");
            option->PaintBackground(canvas, paintWrapper);
            option->PaintDivider(canvas, paintWrapper);
        }
    };
}

void OptionPaintMethod::PaintBackground(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto props = DynamicCast<OptionPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(props);

    // get background color
    Color bgColor;
    bool hover = props->GetHover().value_or(false);
    if (hover) {
        bgColor = props->GetSelectedBackgroundColor().value_or(Color::WHITE);
    } else {
        bgColor = props->GetBackgroundColor().value_or(Color::WHITE);
    }
    RSBrush brush;
    brush.SetARGB(bgColor.GetRed(), bgColor.GetGreen(), bgColor.GetBlue(), bgColor.GetAlpha());
    canvas.AttachBrush(brush);

    // initialize rRect radius
    float radius = ROUND_RADIUS_PHONE.ConvertToPx();

    auto size = paintWrapper->GetGeometryNode()->GetFrameSize();
    auto offset = paintWrapper->GetContentOffset();
    LOGI("paintWrapper offset = %{public}f, %{public}f, size = %{public}f, %{public}f", offset.GetX(), offset.GetY(),
        size.Width(), size.Height());
    // draw background rRect
    RSRoundRect rSRoundRect(
        RSRRect(offset.GetX(), offset.GetY(), size.Width() + offset.GetX(), size.Height() + offset.GetY()), radius,
        radius);
    canvas.DrawRoundRect(rSRoundRect);
    // MIGHT NEED: paint.setColor(GetEventEffectColor().GetValue());
    // MIGHT NEED: canvas->drawPath(path, paint);
}

void OptionPaintMethod::PaintDivider(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto props = DynamicCast<OptionPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(props);

    OffsetF dividerOffset = props->GetDividerOffset().value_or(OffsetF());
    float dividerLength = props->GetDividerLength().value_or(0);

    // use DividerPainter
    LOGI("DRAWING OptionDivider offset: X=%{public}f, Y=%{public}f, length: %{public}f", dividerOffset.GetX(),
        dividerOffset.GetY(), dividerLength);
    DividerPainter dividerPainter(DEFAULT_STROKE_WIDTH, dividerLength, false, Color(DIVIDER_COLOR), LineCap::SQUARE);
    dividerPainter.DrawLine(canvas, dividerOffset);
}
} // namespace OHOS::Ace::NG