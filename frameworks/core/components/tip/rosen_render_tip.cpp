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

#include "core/components/tip/rosen_render_tip.h"

#define SkPathkCCWDirection SkPathDirection::kCCW

namespace OHOS::Ace {
namespace {
constexpr double HALF = 0.5;
constexpr Dimension BEZIER_HORIZON_OFFSET_FIRST = 1.3_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_SECOND = 3.2_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_THIRD = 6.6_vp;
constexpr Dimension BEZIER_HORIZON_OFFSET_FOURTH = 16.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_FIRST = 0.1_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_SECOND = 3.0_vp;
constexpr Dimension BEZIER_VERTICAL_OFFSET_THIRD = 8.0_vp;

} // namespace

void RosenRenderTip::Paint(RenderContext& context, const Offset& offset)
{
    PaintTip(context, offset);
    auto child = GetFirstChild();
    if (!child) {
        return;
    }
    if (child->GetVisible()) {
        child->Paint(context, child->GetPosition() + offset);
    }
}

#ifndef USE_ROSEN_DRAWING
SkCanvas* RosenRenderTip::GetSkCanvas(RenderContext& context)
#else
RSCanvas* RosenRenderTip::GetCanvas(RenderContext& context)
#endif
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("canvas fetch failed");
        return nullptr;
    }
    return canvas;
}

void RosenRenderTip::PaintTip(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(bgColor_.GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    if (direction_ == Axis::VERTICAL) {
        PaintLeftTip(canvas, paint, offset);
    } else {
        PaintTopTip(canvas, paint, offset);
    }
#else
    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(bgColor_.GetValue());
    if (direction_ == Axis::VERTICAL) {
        PaintLeftTip(canvas, brush, offset);
    } else {
        PaintTopTip(canvas, brush, offset);
    }
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderTip::PaintTopTip(SkCanvas* skCanvas, SkPaint paint, const Offset& offset)
{
    if (!skCanvas) {
        return;
    }

    double bubbleSpacing = NormalizeToPx(TIP_SPACING);
    double childHeight = GetLayoutSize().Height() - bubbleSpacing;
    double childHalfWidth = childSize_.Width() * HALF;
    double arrowOffset = NormalizeToPx(arrowOffset_);
    auto globalArrowPosition = offset + Offset(childHalfWidth, GetLayoutSize().Height());

    path_.reset();
    path_.moveTo(globalArrowPosition.GetX() + arrowOffset, globalArrowPosition.GetY());
    path_.quadTo(globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        globalArrowPosition.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.lineTo(globalArrowPosition.GetX() + (childHalfWidth - NormalizeToPx(border_.BottomRightRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing);
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, globalArrowPosition.GetX() + childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.lineTo(globalArrowPosition.GetX() + childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopRightRadius().GetY())));
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        globalArrowPosition.GetX() + childHalfWidth - NormalizeToPx(border_.TopRightRadius().GetX()),
        globalArrowPosition.GetY() - bubbleSpacing - childHeight);
    path_.lineTo(globalArrowPosition.GetX() - (childHalfWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing - childHeight);
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, globalArrowPosition.GetX() - childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopLeftRadius().GetY())));
    path_.lineTo(globalArrowPosition.GetX() - childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        globalArrowPosition.GetX() - (childHalfWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing);
    path_.lineTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.quadTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        globalArrowPosition.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        globalArrowPosition.GetX() + arrowOffset, globalArrowPosition.GetY());
    path_.close();
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}
#else
void RosenRenderTip::PaintTopTip(RSCanvas* canvas, RSBrush brush, const Offset& offset)
{
    if (!canvas) {
        return;
    }

    double bubbleSpacing = NormalizeToPx(TIP_SPACING);
    double childHeight = GetLayoutSize().Height() - bubbleSpacing;
    double childHalfWidth = childSize_.Width() * HALF;
    double arrowOffset = NormalizeToPx(arrowOffset_);
    auto globalArrowPosition = offset + Offset(childHalfWidth, GetLayoutSize().Height());

    path_.Reset();
    path_.MoveTo(globalArrowPosition.GetX() + arrowOffset, globalArrowPosition.GetY());

    path_.QuadTo(globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        globalArrowPosition.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.QuadTo(globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        globalArrowPosition.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.LineTo(globalArrowPosition.GetX() + (childHalfWidth - NormalizeToPx(border_.BottomRightRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing);
    path_.ArcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, RSPathDirection::CCW_DIRECTION, globalArrowPosition.GetX() + childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.LineTo(globalArrowPosition.GetX() + childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopRightRadius().GetY())));
    path_.ArcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        RSPathDirection::CCW_DIRECTION,
        globalArrowPosition.GetX() + childHalfWidth - NormalizeToPx(border_.TopRightRadius().GetX()),
        globalArrowPosition.GetY() - bubbleSpacing - childHeight);
    path_.LineTo(globalArrowPosition.GetX() - (childHalfWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing - childHeight);
    path_.ArcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        RSPathDirection::CCW_DIRECTION, globalArrowPosition.GetX() - childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopLeftRadius().GetY())));
    path_.LineTo(globalArrowPosition.GetX() - childHalfWidth,
        globalArrowPosition.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.ArcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, RSPathDirection::CCW_DIRECTION,
        globalArrowPosition.GetX() - (childHalfWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        globalArrowPosition.GetY() - bubbleSpacing);
    path_.LineTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.QuadTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        globalArrowPosition.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.QuadTo(globalArrowPosition.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        globalArrowPosition.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        globalArrowPosition.GetX() + arrowOffset, globalArrowPosition.GetY());

    path_.Close();
    canvas->AttachBrush(brush);
    canvas->DrawPath(path_);
    canvas->DetachBrush();
    canvas->ClipPath(path_, RSClipOp::INTERSECT);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderTip::PaintLeftTip(SkCanvas* skCanvas, SkPaint paint, const Offset& offset)
{
    if (!skCanvas) {
        return;
    }

    double bubbleSpacing = NormalizeToPx(TIP_SPACING);
    double childWidth = GetLayoutSize().Width() - bubbleSpacing;
    double childHalfHeight = childSize_.Height() * HALF;
    double arrowOffset = NormalizeToPx(arrowOffset_);
    auto globalArrowPosition = offset + Offset(GetLayoutSize().Width(), childHalfHeight);

    path_.reset();
    path_.moveTo(globalArrowPosition.GetX(), globalArrowPosition.GetY() + arrowOffset);
    path_.quadTo(globalArrowPosition.GetX() + NormalizeToPx(0.1_vp),
        globalArrowPosition.GetY() - NormalizeToPx(1.3_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(3.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(3.2_vp) + arrowOffset);
    path_.quadTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(6.6_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(16.0_vp) + arrowOffset);
    path_.lineTo(globalArrowPosition.GetX() - bubbleSpacing,
        globalArrowPosition.GetY() - (childHalfHeight - NormalizeToPx(border_.TopRightRadius().GetY())));
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        globalArrowPosition.GetX() - bubbleSpacing - NormalizeToPx(border_.TopRightRadius().GetX()),
        globalArrowPosition.GetY() - childHalfHeight);
    path_.lineTo(
        globalArrowPosition.GetX() - bubbleSpacing - (childWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        globalArrowPosition.GetY() - childHalfHeight);
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, globalArrowPosition.GetX() - bubbleSpacing - childWidth,
        globalArrowPosition.GetY() - childHalfHeight + NormalizeToPx(border_.TopLeftRadius().GetY()));
    path_.lineTo(globalArrowPosition.GetX() - bubbleSpacing - childWidth,
        globalArrowPosition.GetY() + (childHalfHeight - NormalizeToPx(border_.BottomLeftRadius().GetY())));
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        globalArrowPosition.GetX() - bubbleSpacing - (childWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        globalArrowPosition.GetY() + childHalfHeight);
    path_.lineTo(globalArrowPosition.GetX() - bubbleSpacing - NormalizeToPx(border_.BottomRightRadius().GetX()),
        globalArrowPosition.GetY() + childHalfHeight);
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, globalArrowPosition.GetX() - bubbleSpacing,
        globalArrowPosition.GetY() + (childHalfHeight - NormalizeToPx(border_.BottomRightRadius().GetY())));
    path_.lineTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(16.0_vp) + arrowOffset);
    path_.quadTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(6.6_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(3.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(3.2_vp) + arrowOffset);
    path_.quadTo(globalArrowPosition.GetX() + NormalizeToPx(0.1_vp),
        globalArrowPosition.GetY() + NormalizeToPx(1.3_vp) + arrowOffset, globalArrowPosition.GetX(),
        globalArrowPosition.GetY() + arrowOffset);
    path_.close();
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}
#else
void RosenRenderTip::PaintLeftTip(RSCanvas* canvas, RSBrush brush, const Offset& offset)
{
    if (!canvas) {
        return;
    }

    double bubbleSpacing = NormalizeToPx(TIP_SPACING);
    double childWidth = GetLayoutSize().Width() - bubbleSpacing;
    double childHalfHeight = childSize_.Height() * HALF;
    double arrowOffset = NormalizeToPx(arrowOffset_);
    auto globalArrowPosition = offset + Offset(GetLayoutSize().Width(), childHalfHeight);

    path_.Reset();
    path_.MoveTo(globalArrowPosition.GetX(), globalArrowPosition.GetY() + arrowOffset);

    path_.QuadTo(globalArrowPosition.GetX() + NormalizeToPx(0.1_vp),
        globalArrowPosition.GetY() - NormalizeToPx(1.3_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(3.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(3.2_vp) + arrowOffset);
    path_.QuadTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(6.6_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() - NormalizeToPx(16.0_vp) + arrowOffset);
    path_.LineTo(globalArrowPosition.GetX() - bubbleSpacing,
        globalArrowPosition.GetY() - (childHalfHeight - NormalizeToPx(border_.TopRightRadius().GetY())));
    path_.ArcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        RSPathDirection::CCW_DIRECTION,
        globalArrowPosition.GetX() - bubbleSpacing - NormalizeToPx(border_.TopRightRadius().GetX()),
        globalArrowPosition.GetY() - childHalfHeight);
    path_.LineTo(
        globalArrowPosition.GetX() - bubbleSpacing - (childWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        globalArrowPosition.GetY() - childHalfHeight);
    path_.ArcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        RSPathDirection::CCW_DIRECTION, globalArrowPosition.GetX() - bubbleSpacing - childWidth,
        globalArrowPosition.GetY() - childHalfHeight + NormalizeToPx(border_.TopLeftRadius().GetY()));
    path_.LineTo(globalArrowPosition.GetX() - bubbleSpacing - childWidth,
        globalArrowPosition.GetY() + (childHalfHeight - NormalizeToPx(border_.BottomLeftRadius().GetY())));
    path_.ArcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, RSPathDirection::CCW_DIRECTION,
        globalArrowPosition.GetX() - bubbleSpacing - (childWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        globalArrowPosition.GetY() + childHalfHeight);
    path_.LineTo(globalArrowPosition.GetX() - bubbleSpacing - NormalizeToPx(border_.BottomRightRadius().GetX()),
        globalArrowPosition.GetY() + childHalfHeight);
    path_.ArcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, RSPathDirection::CCW_DIRECTION, globalArrowPosition.GetX() - bubbleSpacing,
        globalArrowPosition.GetY() + (childHalfHeight - NormalizeToPx(border_.BottomRightRadius().GetY())));
    path_.LineTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(16.0_vp) + arrowOffset);
    path_.QuadTo(globalArrowPosition.GetX() - NormalizeToPx(8.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(6.6_vp) + arrowOffset,
        globalArrowPosition.GetX() - NormalizeToPx(3.0_vp),
        globalArrowPosition.GetY() + NormalizeToPx(3.2_vp) + arrowOffset);
    path_.QuadTo(globalArrowPosition.GetX() + NormalizeToPx(0.1_vp),
        globalArrowPosition.GetY() + NormalizeToPx(1.3_vp) + arrowOffset, globalArrowPosition.GetX(),
        globalArrowPosition.GetY() + arrowOffset);
    path_.Close();
    canvas->AttachBrush(brush);
    canvas->DrawPath(path_);
    canvas->ClipPath(path_, RSClipOp::INTERSECT);
    canvas->DetachBrush();
}
#endif

} // namespace OHOS::Ace
