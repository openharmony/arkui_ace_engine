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

#include "core/components_ng/pattern/scroll/effect/scroll_fade_painter.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float WIDTH_TO_HEIGHT_FACTOR = 0.20096f; // (3.0 / 4.0) * (2.0 - std::sqrt(3));
constexpr float QUARTER_CIRCLE = 90.0f;            // 3.1415926 / 2.0;
} // namespace

void ScrollFadePainter::Paint(RSCanvas& canvas, const SizeF& size, const OffsetF& offset)
{
    if (NearZero(opacity_) || NearZero(size.Width()) || NearZero(size.Height())) {
        return;
    }

    float baseGlowScale = size.Width() > size.Height() ? size.Height() / size.Width() : 1.0;
    float radius = size.Width() * 3.0 / 2.0;
    float height = std::min(size.Height(), size.Width() * WIDTH_TO_HEIGHT_FACTOR);
    float scaleH = scaleFactor_ * baseGlowScale;
    const auto& clipRect = Rect(Offset::Zero(), Size(size.Width(), height));
    Offset center = Offset(size.Width() / 2.0, height - radius);

    RSBrush brush;
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(color_));
    brush.SetAlphaF(opacity_);

    canvas.Save();
    canvas.DetachPen();
    canvas.AttachBrush(brush);
    canvas.Scale(1.0, scaleH);
    canvas.ClipRect(
        { clipRect.Left(), clipRect.Top(), clipRect.Right(), clipRect.Bottom() }, RSClipOp::INTERSECT);
    canvas.DrawCircle(
        { center.GetX(), center.GetY() }, radius);
    canvas.DetachBrush();
    canvas.Restore();
}

void ScrollFadePainter::PaintSide(RSCanvas& canvas, const SizeF& size, const OffsetF& offset)
{
    switch (direction_) {
        case OverScrollDirection::UP:
            canvas.Save();
            canvas.Translate(offset.GetX(), offset.GetY());
            Paint(canvas, size, offset);
            canvas.Restore();
            break;
        case OverScrollDirection::DOWN:
            canvas.Save();
            canvas.Translate(offset.GetX(), offset.GetY());
            canvas.Translate(0.0, size.Height());
            canvas.Scale(1.0, -1.0);
            Paint(canvas, size, offset);
            canvas.Restore();
            break;
        case OverScrollDirection::LEFT:
            canvas.Save();
            canvas.Translate(offset.GetX(), offset.GetY());
            canvas.Rotate(QUARTER_CIRCLE);
            canvas.Scale(1.0, -1.0);
            Paint(canvas, SizeF(size.Height(), size.Width()), offset);
            canvas.Restore();
            break;
        case OverScrollDirection::RIGHT:
            canvas.Save();
            canvas.Translate(offset.GetX(), offset.GetY());
            canvas.Translate(size.Width(), 0.0);
            canvas.Rotate(QUARTER_CIRCLE);
            Paint(canvas, SizeF(size.Height(), size.Width()), offset);
            canvas.Restore();
            break;
        default:
            break;
    }
}
} // namespace OHOS::Ace::NG