/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/rosen_scroll_fade_painter.h"

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

constexpr double WIDTH_TO_HEIGHT_FACTOR = 0.20096; // (3.0 / 4.0) * (2.0 - std::sqrt(3));
constexpr double QUARTER_CIRCLE = 90.0;            // 3.1415926 / 2.0;

} // namespace

#ifndef USE_ROSEN_DRAWING
void RosenScrollFadePainter::Paint(SkCanvas* canvas, const Size& size, const Offset& offset)
{
    if (canvas == nullptr || NearZero(opacity_) || size.IsEmpty()) {
        return;
    }

    double baseGlowScale = size.Width() > size.Height() ? size.Height() / size.Width() : 1.0;
    double radius = size.Width() * 3.0 / 2.0;
    double height = std::min(size.Height(), size.Width() * WIDTH_TO_HEIGHT_FACTOR);
    double scaleH = scaleFactor_ * baseGlowScale;
    const auto& clipRect = Rect(Offset::Zero(), Size(size.Width(), height));
    Offset center = Offset(size.Width() / 2.0, height - radius);

    SkPaint painter;
    painter.setColor(color_.GetValue());
    painter.setAlphaf(opacity_);
    painter.setBlendMode(SkBlendMode::kSrcOver);

    canvas->save();
    canvas->scale(1.0, scaleH);
    canvas->clipRect({ clipRect.Left(), clipRect.Top(), clipRect.Right(), clipRect.Bottom() }, SkClipOp::kIntersect);
    canvas->drawCircle(center.GetX(), center.GetY(), radius, painter);
    canvas->restore();
}
#else
void RosenScrollFadePainter::Paint(RSCanvas* canvas, const Size& size, const Offset& offset)
{
    if (canvas == nullptr || NearZero(opacity_) || size.IsEmpty()) {
        return;
    }

    double baseGlowScale = size.Width() > size.Height() ? size.Height() / size.Width() : 1.0;
    double radius = size.Width() * 3.0 / 2.0;
    double height = std::min(size.Height(), size.Width() * WIDTH_TO_HEIGHT_FACTOR);
    double scaleH = scaleFactor_ * baseGlowScale;
    const auto& clipRect = Rect(Offset::Zero(), Size(size.Width(), height));
    Offset center = Offset(size.Width() / 2.0, height - radius);

    RSBrush brush;
    brush.SetColor(color_.GetValue());
    brush.SetAlpha(opacity_);
    brush.SetBlendMode(RSBlendMode::SRC_OVER);

    canvas->Save();
    canvas->Scale(1.0, scaleH);
    canvas->ClipRect(RSRect(clipRect.Left(), clipRect.Top(), clipRect.Right(), clipRect.Bottom()),
        RSClipOp::INTERSECT);
    canvas->AttachBrush(brush);
    RSPoint point(center.GetX(), center.GetY());
    canvas->DrawCircle(point, radius);
    canvas->DetachBrush();
    canvas->Restore();
}
#endif

void RosenScrollFadePainter::PaintSide(RenderContext& context, const Size& size, const Offset& offset)
{
    const auto renderContext = static_cast<RosenRenderContext*>(&context);
    if (!renderContext) {
        return;
    }
    auto canvas = renderContext->GetCanvas();
    if (canvas == nullptr) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    switch (direction_) {
        case OverScrollDirection::UP:
            canvas->save();
            canvas->translate(offset.GetX(), offset.GetY());
            Paint(canvas, size, offset);
            canvas->restore();
            break;
        case OverScrollDirection::DOWN:
            canvas->save();
            canvas->translate(offset.GetX(), offset.GetY());
            canvas->translate(0.0, size.Height());
            canvas->scale(1.0, -1.0);
            Paint(canvas, size, offset);
            canvas->restore();
            break;
        case OverScrollDirection::LEFT:
            canvas->save();
            canvas->translate(offset.GetX(), offset.GetY());
            canvas->rotate(QUARTER_CIRCLE);
            canvas->scale(1.0, -1.0);
            Paint(canvas, Size(size.Height(), size.Width()), offset);
            canvas->restore();
            break;
        case OverScrollDirection::RIGHT:
            canvas->save();
            canvas->translate(offset.GetX(), offset.GetY());
            canvas->translate(size.Width(), 0.0);
            canvas->rotate(QUARTER_CIRCLE);
            Paint(canvas, Size(size.Height(), size.Width()), offset);
            canvas->restore();
            break;
        default:
            break;
    }
#else
    switch (direction_) {
        case OverScrollDirection::UP:
            canvas->Save();
            canvas->Translate(offset.GetX(), offset.GetY());
            Paint(canvas, size, offset);
            canvas->Restore();
            break;
        case OverScrollDirection::DOWN:
            canvas->Save();
            canvas->Translate(offset.GetX(), offset.GetY());
            canvas->Translate(0.0, size.Height());
            canvas->Scale(1.0, -1.0);
            Paint(canvas, size, offset);
            canvas->Restore();
            break;
        case OverScrollDirection::LEFT:
            canvas->Save();
            canvas->Translate(offset.GetX(), offset.GetY());
            canvas->Rotate(QUARTER_CIRCLE);
            canvas->Scale(1.0, -1.0);
            Paint(canvas, Size(size.Height(), size.Width()), offset);
            canvas->Restore();
            break;
        case OverScrollDirection::RIGHT:
            canvas->Save();
            canvas->Translate(offset.GetX(), offset.GetY());
            canvas->Translate(size.Width(), 0.0);
            canvas->Rotate(QUARTER_CIRCLE);
            Paint(canvas, Size(size.Height(), size.Width()), offset);
            canvas->Restore();
            break;
        default:
            break;
    }
#endif
}

} // namespace OHOS::Ace