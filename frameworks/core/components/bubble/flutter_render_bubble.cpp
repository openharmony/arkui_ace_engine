/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components/bubble/flutter_render_bubble.h"

#include "include/core/SkMaskFilter.h"
#include "include/effects/Sk1DPathEffect.h"
#include "include/effects/SkDashPathEffect.h"
#include "include/effects/SkGradientShader.h"

#include "core/components/common/painter/flutter_decoration_painter.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/shadow_config.h"
#include "core/pipeline/base/flutter_render_context.h"
#include "core/pipeline/base/scoped_canvas_state.h"

#define SkPathkCCWDirection SkPathDirection::kCCW

namespace OHOS::Ace {

SkCanvas* FlutterRenderBubble::GetSkCanvas(RenderContext& context)
{
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("canvas fetch failed");
        return nullptr;
    }
    return canvas->canvas();
}

SkRRect FlutterRenderBubble::MakeRRect()
{
    SkRect rect = SkRect::MakeXYWH(childOffset_.GetX(), childOffset_.GetY(), childSize_.Width(), childSize_.Height());
    SkRRect rrect = SkRRect::MakeEmpty();
    SkVector rectRadii[4] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    rectRadii[SkRRect::kUpperLeft_Corner] =
        SkPoint::Make(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()));
    rectRadii[SkRRect::kUpperRight_Corner] =
        SkPoint::Make(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()));
    rectRadii[SkRRect::kLowerRight_Corner] = SkPoint::Make(
        NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()));
    rectRadii[SkRRect::kLowerLeft_Corner] = SkPoint::Make(
        NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()));
    rrect.setRectRadii(rect, rectRadii);
    return rrect;
}

void FlutterRenderBubble::Paint(RenderContext& context, const Offset& offset)
{
    if (!isShow_) {
        return;
    }
    PaintMask(context);
    PaintBubble(context);
    RenderNode::Paint(context, offset);
    PaintBorder(context);
    if (onVisibilityChange_ && !hasEventFired_) {
        std::string param = std::string("\"visibilitychange\",{\"visibility\":").append("true}");
        onVisibilityChange_(param);
        hasEventFired_ = true;
    }
}

void FlutterRenderBubble::PaintMask(RenderContext& context)
{
    SkCanvas* skCanvas = GetSkCanvas(context);
    if (skCanvas == nullptr) {
        return;
    }
    SkPaint paint;
    paint.setColor(maskColor_.GetValue());
    skCanvas->drawRect(SkRect::MakeXYWH(0.0, 0.0, GetLayoutSize().Width(), GetLayoutSize().Height()), paint);
}

void FlutterRenderBubble::PaintBubble(RenderContext& context)
{
    SkCanvas* skCanvas = GetSkCanvas(context);
    SkPaint paint;
    paint.setAntiAlias(true);
    paint.setColor(backgroundColor_.GetValue());
    if (!useCustom_) {
        PaintNonCustomPopup(skCanvas, paint);
        return;
    }
    if (enableArrow_ && showCustomArrow_) {
        PaintBubbleWithArrow(skCanvas, paint);
    } else {
        PaintDefaultBubble(skCanvas, paint);
    }
}

void FlutterRenderBubble::PaintNonCustomPopup(SkCanvas* skCanvas, const SkPaint& paint)
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        switch (arrowPlacement_) {
            case Placement::TOP:
                showTopArrow_ ? PaintTopBubble(skCanvas, paint) : PaintDefaultBubble(skCanvas, paint);
                break;
            case Placement::BOTTOM:
                showBottomArrow_ ? PaintBottomBubble(skCanvas, paint) : PaintDefaultBubble(skCanvas, paint);
                break;
            default:
                break;
        }
        return;
    }
    switch (arrowPlacement_) {
        case Placement::TOP:
            showTopArrow_ ? PaintTopBubbleInJs(skCanvas, paint) : PaintDefaultBubble(skCanvas, paint);
            break;
        case Placement::BOTTOM:
            showBottomArrow_ ? PaintBottomBubbleInJs(skCanvas, paint) : PaintDefaultBubble(skCanvas, paint);
            break;
        default:
            break;
    }
}

void FlutterRenderBubble::PaintBubbleWithArrow(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    BuildCompletePath(path_);
    FlutterDecorationPainter::PaintShadow(path_, ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintTopBubbleInJs(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    double childHeight = childSize_.Height();
    double childHalfWidth = childSize_.Width() / 2.0;
    double bubbleSpacing = NormalizeToPx(BUBBLE_SPACING);
    double arrowOffset = std::clamp(NormalizeToPx(arrowOffset_),
        -(childHalfWidth - std::max(NormalizeToPx(padding_.Left()), NormalizeToPx(border_.TopLeftRadius().GetX())) -
            NormalizeToPx(BEZIER_WIDTH_HALF)),
        childHalfWidth - std::max(NormalizeToPx(padding_.Right()), NormalizeToPx(border_.TopRightRadius().GetY())) -
            NormalizeToPx(BEZIER_WIDTH_HALF));

    path_.reset();
    path_.moveTo(arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
    path_.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.lineTo(arrowPosition_.GetX() + (childHalfWidth - NormalizeToPx(border_.BottomRightRadius().GetX())),
        arrowPosition_.GetY() - bubbleSpacing);
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, arrowPosition_.GetX() + childHalfWidth,
        arrowPosition_.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.lineTo(arrowPosition_.GetX() + childHalfWidth,
        arrowPosition_.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopRightRadius().GetY())));
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        arrowPosition_.GetX() + childHalfWidth - NormalizeToPx(border_.TopRightRadius().GetX()),
        arrowPosition_.GetY() - bubbleSpacing - childHeight);
    path_.lineTo(arrowPosition_.GetX() - (childHalfWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        arrowPosition_.GetY() - bubbleSpacing - childHeight);
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, arrowPosition_.GetX() - childHalfWidth,
        arrowPosition_.GetY() - bubbleSpacing - (childHeight - NormalizeToPx(border_.TopLeftRadius().GetY())));
    path_.lineTo(arrowPosition_.GetX() - childHalfWidth,
        arrowPosition_.GetY() - bubbleSpacing - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        arrowPosition_.GetX() - (childHalfWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        arrowPosition_.GetY() - bubbleSpacing);
    path_.lineTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST), arrowPosition_.GetX() + arrowOffset,
        arrowPosition_.GetY());
    path_.close();
    FlutterDecorationPainter::PaintShadow(path_, ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintBottomBubbleInJs(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    double childHeight = childSize_.Height();
    double childHalfWidth = childSize_.Width() / 2.0;
    double bubbleSpacing = NormalizeToPx(BUBBLE_SPACING);
    double arrowOffset = std::clamp(NormalizeToPx(arrowOffset_),
        -(childHalfWidth - std::max(NormalizeToPx(padding_.Left()), NormalizeToPx(border_.BottomLeftRadius().GetX())) -
            NormalizeToPx(BEZIER_WIDTH_HALF)),
        childHalfWidth - std::max(NormalizeToPx(padding_.Right()), NormalizeToPx(border_.BottomRightRadius().GetY())) -
            NormalizeToPx(BEZIER_WIDTH_HALF));

    path_.reset();
    path_.moveTo(arrowPosition_.GetX() + arrowOffset, arrowPosition_.GetY());
    path_.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPosition_.GetX() + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.lineTo(arrowPosition_.GetX() + (childHalfWidth - NormalizeToPx(border_.TopRightRadius().GetX())),
        arrowPosition_.GetY() + bubbleSpacing);
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction, arrowPosition_.GetX() + childHalfWidth,
        arrowPosition_.GetY() + bubbleSpacing + NormalizeToPx(border_.TopRightRadius().GetY()));
    path_.lineTo(arrowPosition_.GetX() + childHalfWidth,
        arrowPosition_.GetY() + bubbleSpacing + childHeight - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction,
        arrowPosition_.GetX() + childHalfWidth - NormalizeToPx(border_.BottomRightRadius().GetX()),
        arrowPosition_.GetY() + bubbleSpacing + childHeight);
    path_.lineTo(arrowPosition_.GetX() - (childHalfWidth - NormalizeToPx(border_.BottomLeftRadius().GetX())),
        arrowPosition_.GetY() + bubbleSpacing + childHeight);
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction, arrowPosition_.GetX() - childHalfWidth,
        arrowPosition_.GetY() + bubbleSpacing + childHeight - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.lineTo(arrowPosition_.GetX() - childHalfWidth,
        arrowPosition_.GetY() + bubbleSpacing + NormalizeToPx(border_.TopLeftRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction,
        arrowPosition_.GetX() - (childHalfWidth - NormalizeToPx(border_.TopLeftRadius().GetX())),
        arrowPosition_.GetY() + bubbleSpacing);
    path_.lineTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPosition_.GetY() + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPosition_.GetX() - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPosition_.GetY() - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST), arrowPosition_.GetX() + arrowOffset,
        arrowPosition_.GetY());
    path_.close();
    FlutterDecorationPainter::PaintShadow(path_, ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintTopBubble(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    double childHeight = childSize_.Height();
    double childWidth = childSize_.Width();
    double childOffsetX = childOffset_.GetX();
    double childOffsetY = childOffset_.GetY();
    double arrowPositionX = arrowPosition_.GetX();
    double arrowPositionY = arrowPosition_.GetY();
    double arrowOffset = GetArrowOffset(Placement::TOP);
    path_.reset();
    path_.moveTo(arrowPositionX + arrowOffset, arrowPositionY);
    path_.quadTo(arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.lineTo(
        childOffsetX + childWidth - NormalizeToPx(border_.BottomRightRadius().GetX()), childOffsetY + childHeight);
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, childOffsetX + childWidth,
        childOffsetY + childHeight - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.lineTo(childOffsetX + childWidth, childOffsetY + NormalizeToPx(border_.TopRightRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        childOffsetX + childWidth - NormalizeToPx(border_.TopRightRadius().GetX()), childOffsetY);
    path_.lineTo(childOffsetX + NormalizeToPx(border_.TopLeftRadius().GetX()), childOffsetY);
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection, childOffsetX,
        childOffsetY + NormalizeToPx(border_.TopLeftRadius().GetY()));
    path_.lineTo(childOffsetX, childOffsetY + childHeight - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPathkCCWDirection,
        childOffsetX + NormalizeToPx(border_.BottomLeftRadius().GetX()), childOffsetY + childHeight);
    path_.lineTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.quadTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST), arrowPositionX + arrowOffset, arrowPositionY);
    path_.close();
    FlutterDecorationPainter::PaintShadow(path_, ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintBottomBubble(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    double childHeight = childSize_.Height();
    double childWidth = childSize_.Width();
    double childOffsetX = childOffset_.GetX();
    double childOffsetY = childOffset_.GetY();
    double arrowPositionX = arrowPosition_.GetX();
    double arrowPositionY = arrowPosition_.GetY();
    double arrowOffset = GetArrowOffset(Placement::BOTTOM);
    path_.reset();
    path_.moveTo(arrowPositionX + arrowOffset, arrowPositionY);
    path_.quadTo(arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST),
        arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPositionX + NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.lineTo(childOffsetX + childWidth - NormalizeToPx(border_.TopRightRadius().GetX()), childOffsetY);
    path_.arcTo(NormalizeToPx(border_.TopRightRadius().GetX()), NormalizeToPx(border_.TopRightRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction, childOffsetX + childWidth,
        childOffsetY + NormalizeToPx(border_.TopRightRadius().GetY()));
    path_.lineTo(
        childOffsetX + childWidth, childOffsetY + childHeight - NormalizeToPx(border_.BottomRightRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.BottomRightRadius().GetX()), NormalizeToPx(border_.BottomRightRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction,
        childOffsetX + childWidth - NormalizeToPx(border_.BottomRightRadius().GetX()), childOffsetY + childHeight);
    path_.lineTo(childOffsetX + NormalizeToPx(border_.BottomLeftRadius().GetX()), childOffsetY + childHeight);
    path_.arcTo(NormalizeToPx(border_.BottomLeftRadius().GetX()), NormalizeToPx(border_.BottomLeftRadius().GetY()),
        0.0f, SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction, childOffsetX,
        childOffsetY + childHeight - NormalizeToPx(border_.BottomLeftRadius().GetY()));
    path_.lineTo(childOffsetX, childOffsetY + NormalizeToPx(border_.TopLeftRadius().GetY()));
    path_.arcTo(NormalizeToPx(border_.TopLeftRadius().GetX()), NormalizeToPx(border_.TopLeftRadius().GetY()), 0.0f,
        SkPath::ArcSize::kSmall_ArcSize, SkPath::Direction::kCW_Direction,
        childOffsetX + NormalizeToPx(border_.TopLeftRadius().GetX()), childOffsetY);
    path_.lineTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_FOURTH) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD));
    path_.quadTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_THIRD) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_THIRD),
        arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_SECOND) + arrowOffset,
        arrowPositionY + NormalizeToPx(BEZIER_VERTICAL_OFFSET_SECOND));
    path_.quadTo(arrowPositionX - NormalizeToPx(BEZIER_HORIZON_OFFSET_FIRST) + arrowOffset,
        arrowPositionY - NormalizeToPx(BEZIER_VERTICAL_OFFSET_FIRST), arrowPositionX + arrowOffset, arrowPositionY);
    path_.close();
    FlutterDecorationPainter::PaintShadow(path_, ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawPath(path_, paint);
    skCanvas->clipPath(path_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintDefaultBubble(SkCanvas* skCanvas, const SkPaint& paint)
{
    if (skCanvas == nullptr) {
        return;
    }
    rrect_ = MakeRRect();
    FlutterDecorationPainter::PaintShadow(SkPath().addRRect(rrect_), ShadowConfig::DefaultShadowM, skCanvas);
    skCanvas->drawRRect(rrect_, paint);
    skCanvas->clipRRect(rrect_, SkClipOp::kIntersect);
}

void FlutterRenderBubble::PaintBorder(RenderContext& context)
{
    SkCanvas* skCanvas = GetSkCanvas(context);
    if (skCanvas == nullptr) {
        return;
    }
    BorderEdge edge = border_.Left();
    if (!border_.IsAllEqual()) {
        edge = border_.GetValidEdge();
        border_ = Border(edge);
    }
    if (!border_.HasValue()) {
        return;
    }
    double borderWidth = NormalizeToPx(edge.GetWidth());
    SkPaint paint;
    paint.setStrokeWidth(borderWidth);
    paint.setColor(edge.GetColor().GetValue());
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setAntiAlias(true);
    if (edge.GetBorderStyle() == BorderStyle::DOTTED) {
        SkPath dotPath;
        dotPath.addCircle(0.0f, 0.0f, SkDoubleToScalar(borderWidth / 2.0));
        paint.setPathEffect(
            SkPath1DPathEffect::Make(dotPath, borderWidth * 2.0, 0.0, SkPath1DPathEffect::kRotate_Style));
    } else if (edge.GetBorderStyle() == BorderStyle::DASHED) {
        const float intervals[] = { SkDoubleToScalar(borderWidth), SkDoubleToScalar(borderWidth) };
        paint.setPathEffect(SkDashPathEffect::Make(intervals, SK_ARRAY_COUNT(intervals), 0.0));
        skCanvas->drawPath(path_, paint);
    } else {
        paint.setPathEffect(nullptr);
    }

    skCanvas->save();
    skCanvas->translate(
        childOffset_.GetX() + childSize_.Width() / 2.0, childOffset_.GetY() + childSize_.Height() / 2.0);
    skCanvas->scale(1.0 - (borderWidth / childSize_.Width()), 1.0 - (borderWidth / childSize_.Height()));
    skCanvas->translate(
        -(childOffset_.GetX() + childSize_.Width() / 2.0), -(childOffset_.GetY() + childSize_.Height() / 2.0));
    if ((arrowPlacement_ == Placement::TOP || arrowPlacement_ == Placement::BOTTOM) && !path_.isEmpty()) {
        skCanvas->drawPath(path_, paint);
    } else {
        skCanvas->drawRRect(rrect_, paint);
    }
    skCanvas->restore();
}

} // namespace OHOS::Ace
