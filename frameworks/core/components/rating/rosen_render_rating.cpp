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

#include "core/components/rating/rosen_render_rating.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkClipOp.h"
#include "include/core/SkMaskFilter.h"
#include "include/core/SkRRect.h"
#else
#include "core/components_ng/render/drawing.h"
#endif

#include "core/components/common/painter/rosen_universal_painter.h"
#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {

void RosenRenderRating::Paint(RenderContext& context, const Offset& offset)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    double offsetDeltaX = (GetLayoutSize().Width() - ratingSize_.Width()) / 2.0;
    double offsetDeltaY = (GetLayoutSize().Height() - ratingSize_.Height()) / 2.0;
    offsetDelta_ = offset + Offset(offsetDeltaX, offsetDeltaY);
    double imageVerticalOffset = ratingSize_.Width() * paddingVertical_.Value() / defaultHeight_.Value() / starNum_;
    Offset starOffset = GetStarOffset(imageVerticalOffset);
    auto pipeline = context_.Upgrade();
    if (!isIndicator_ && operationEvent_ == OperationEvent::RATING_KEY_EVENT && !NearZero(imageVerticalOffset) &&
        pipeline && pipeline->GetIsTabKeyPressed()) {
        Offset animationOffset = starOffset + Offset(offsetDeltaX, offsetDeltaY);
        PaintFocus(animationOffset + offset, singleWidth_ / 2 - imageVerticalOffset,
            Size(singleWidth_ - imageVerticalOffset * 2, singleWidth_ - imageVerticalOffset * 2), context);
        double focusRadius = singleWidth_ - imageVerticalOffset * 2;
        RequestFocusAnimation(animationOffset + GetGlobalOffset(), Size(focusRadius, focusRadius), focusRadius);
    }

    if ((IsTablet() || IsPhone()) && !isIndicator_ && operationEvent_ == OperationEvent::RATING_KEY_EVENT &&
        pipeline && pipeline->GetIsTabKeyPressed()) {
        Offset animationOffset = starOffset + Offset(offsetDeltaX, offsetDeltaY);
        PaintFocusForTABLET(
            animationOffset, focusBorderRadius_.Value(), Size(singleWidth_, ratingSize_.Height()), context);
        double focusRadius = singleWidth_;
        RequestFocusAnimation(animationOffset + GetGlobalOffset(), Size(focusRadius, focusRadius), focusRadius);
    }

    if ((IsPhone() || IsTablet()) && !isIndicator_) {
        PaintHoverRect(canvas);
    }
    Offset pressstarOffset = Offset(singleWidth_ * pressstarNum_ + imageVerticalOffset, imageVerticalOffset);
    if (!isIndicator_ && (IsTablet() || IsPhone()) && isPress_) {
        Offset animationOffset = pressstarOffset + Offset(offsetDeltaX, offsetDeltaY);
        PaintPress(animationOffset + offset, NormalizeToPx(PRESS_BORDER_RADIUS),
            Size(singleWidth_, ratingSize_.Height()), context);
    }
    if (IsPhone() && !isIndicator_ && operationEvent_ == OperationEvent::RATING_KEY_EVENT &&
        operationEvent_ != OperationEvent::RATING_MOUSE_EVENT) {
        // total width of focus border is twice the width of [focusBorderWidth_], border-width + padding-width
        RequestFocusAnimationForPhone();
    }
    PaintRatingBar(context, canvas);
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderRating::PaintHoverRect(SkCanvas* canvas)
#else
void RosenRenderRating::PaintHoverRect(RSCanvas* canvas)
#endif
{
    Size hoverSize = Size(singleWidth_, ratingSize_.Height());
    for (auto& item : hoverColorMap_) {
        if (item.second == Color::TRANSPARENT) {
            continue;
        }
        RosenUniversalPainter::DrawHoverBackground(canvas,
            Rect(Offset(item.first * singleWidth_, 0.0) + offsetDelta_, hoverSize), item.second.GetValue(),
            focusBorderRadius_.Value());
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderRating::PaintRatingBar(RenderContext& context, SkCanvas* canvas)
#else
void RosenRenderRating::PaintRatingBar(RenderContext& context, RSCanvas* canvas)
#endif
{
    double imageVerticalOffset = ratingSize_.Width() * paddingVertical_.Value() / defaultHeight_.Value() / starNum_;
    auto imageOffset = offsetDelta_ + Offset(0.0, imageVerticalOffset);
    if (paintForeground_) {
        // In RTL environment, foreground image may draw three stars and be clipped to display 2.5 stars eventually.
        // [foregroundDrawOffset] is the position to start drawing foreground image.
        // [foregroundClipOffset] is the position to start clipping foreground image zone.
        Offset foregroundDrawOffset = imageOffset;
        Offset foregroundClipOffset = imageOffset;
        Size foregroundSize = Size(foregroundImageWidth_, ratingSize_.Height());
        if (needReverse_) {
            foregroundDrawOffset += Offset((starNum_ - ceil(drawScore_)) * singleWidth_, 0.0);
            foregroundClipOffset += Offset(secondaryImageWidth_ + backgroundImageWidth_, 0.0);
        }

        auto foregroundProperties =
            ImageAreaProperties(ceil(drawScore_), foregroundSize, foregroundDrawOffset, foregroundClipOffset);
        PaintImageArea(context, renderForeground_, canvas, foregroundProperties);
    }

    if (paintSecondary_) {
        Offset secondaryClipOffset = imageOffset;
        Offset secondaryDrawOffset = imageOffset;
        if (needReverse_) {
            secondaryClipOffset += Offset((starNum_ - ceil(drawScore_)) * singleWidth_, 0.0);
            secondaryDrawOffset = secondaryClipOffset;
        } else {
            secondaryClipOffset += Offset(foregroundImageWidth_, 0.0);
            secondaryDrawOffset += Offset(floor(drawScore_) * singleWidth_, 0.0);
        }
        Size secondarySize = Size(secondaryImageWidth_, ratingSize_.Height());

        auto secondaryProperties = ImageAreaProperties(1, secondarySize, secondaryDrawOffset, secondaryClipOffset);
        PaintImageArea(context, renderSecondary_, canvas, secondaryProperties);
    }

    if (paintBackground_) {
        Offset backgroundDrawOffset =
            needReverse_ ? imageOffset : imageOffset + Offset(foregroundImageWidth_ + secondaryImageWidth_, 0.0);
        Offset backgroundClipOffset = backgroundDrawOffset;
        Size backgroundSize = Size(backgroundImageWidth_, ratingSize_.Height());

        auto backgroundProperties = ImageAreaProperties(
            starNum_ - floor(drawScore_), backgroundSize, backgroundDrawOffset, backgroundClipOffset);
        PaintImageArea(context, renderBackground_, canvas, backgroundProperties);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderRating::PaintImageArea(RenderContext& context, const RefPtr<RenderImage>& renderImage, SkCanvas* canvas,
    const ImageAreaProperties& properties)
{
    canvas->save();
    auto clipOffset = properties.clipOffset;
    auto drawOffset = properties.drawOffset;
    auto imageAreaSize = properties.imageAreaSize;
    canvas->clipRect({ clipOffset.GetX(), clipOffset.GetY(), clipOffset.GetX() + imageAreaSize.Width(),
                         clipOffset.GetY() + imageAreaSize.Height() },
        SkClipOp::kIntersect, true);
    for (int i = 0; i < properties.repeatNum; ++i) {
        renderImage->SetAdaptiveFrameRectFlag(false);
        renderImage->RenderWithContext(context, drawOffset + Offset(singleWidth_ * i, 0.0));
    }
    canvas->restore();
}
#else
void RosenRenderRating::PaintImageArea(RenderContext& context, const RefPtr<RenderImage>& renderImage,
    RSCanvas* canvas, const ImageAreaProperties& properties)
{
    canvas->Save();
    auto clipOffset = properties.clipOffset;
    auto drawOffset = properties.drawOffset;
    auto imageAreaSize = properties.imageAreaSize;
    canvas->ClipRect(
        RSRect{clipOffset.GetX(), clipOffset.GetY(), clipOffset.GetX() + imageAreaSize.Width(),
            clipOffset.GetY() + imageAreaSize.Height()},
        RSClipOp::INTERSECT, true);
    for (int i = 0; i < properties.repeatNum; ++i) {
        renderImage->SetAdaptiveFrameRectFlag(false);
        renderImage->RenderWithContext(context, drawOffset + Offset(singleWidth_ * i, 0.0));
    }
    canvas->Restore();
}
#endif

void RosenRenderRating::PaintFocus(
    const Offset& offset, double rRectRadius, const Size& boardSize, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    SkRRect rRect;
    paint.setColor(RATING_FOCUS_BOARD_COLOR);
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setMaskFilter(SkMaskFilter::MakeBlur(SkBlurStyle::kSolid_SkBlurStyle, 1.0));
    rRect.setRectXY(SkRect::MakeWH(boardSize.Width(), boardSize.Height()), rRectRadius, rRectRadius);
    rRect.offset(offset.GetX(), offset.GetY());
    canvas->drawRRect(rRect, paint);
#else
    RSBrush brush;
    brush.SetColor(RATING_FOCUS_BOARD_COLOR);
    RSFilter filter;
    filter.SetMaskFilter(RSMaskFilter::CreateBlurMaskFilter(RSBlurType::SOLID, 1.0));
    brush.SetFilter(filter);

    RSRoundRect rRect(
        RSRect(0, 0, boardSize.Width(), boardSize.Height()), rRectRadius, rRectRadius);
    rRect.Offset(offset.GetX(), offset.GetY());
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rRect);
    canvas->DetachBrush();
#endif
}

void RosenRenderRating::PaintFocusForTABLET(
    const Offset& offset, double rRectRadius, const Size& boardSize, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
    SkRRect rRect;
    paint.setColor(FOCUS_BORDER_COLOR);
    paint.setStyle(SkPaint::Style::kStroke_Style);
    paint.setStrokeWidth(NormalizeToPx(FOCUS_BORDER_PADDING));
    paint.setAntiAlias(true);
    rRect.setRectXY(SkRect::MakeWH(boardSize.Width(), boardSize.Height()), rRectRadius, rRectRadius);
    rRect.offset(offset.GetX(), offset.GetY());
    canvas->drawRRect(rRect, paint);
#else
    RSPen pen;
    pen.SetColor(FOCUS_BORDER_COLOR);
    pen.SetWidth(NormalizeToPx(FOCUS_BORDER_PADDING));
    pen.SetAntiAlias(true);
    RSRoundRect rRect(
        RSRect(0, 0, boardSize.Width(), boardSize.Height()), rRectRadius, rRectRadius);
    rRect.Offset(offset.GetX(), offset.GetY());
    canvas->AttachPen(pen);
    canvas->DrawRoundRect(rRect);
    canvas->DetachPen();
#endif
}

void RosenRenderRating::PaintPress(
    const Offset& offset, double rRectRadius, const Size& boardSize, RenderContext& context)
{
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }
    double dipScale = 1.0;
    auto pipelineContext = GetContext().Upgrade();
    if (pipelineContext) {
        dipScale = pipelineContext->GetDipScale();
    }
    RosenUniversalPainter::DrawRRectBackground(canvas, RRect::MakeRRect(Rect(offset.GetX(), offset.GetY(),
        boardSize.Width(), boardSize.Height()), Radius(rRectRadius)), PRESS_COLOR, dipScale);
}

} // namespace OHOS::Ace
