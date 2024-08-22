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

#include "core/components/badge/rosen_render_badge.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkRRect.h"
#endif

#include "core/pipeline/base/rosen_render_context.h"

namespace OHOS::Ace {
namespace {

constexpr Dimension CIRCLE_BADGE_SIZE = 6.0_vp;
constexpr Dimension NUMERICAL_BADGE_CIRCLE_SIZE = 16.0_vp;
constexpr Dimension NUMERICAL_BADGE_PADDING = 6.0_vp;

} // namespace

void RosenRenderBadge::Paint(RenderContext& context, const Offset& offset)
{
    auto badgeChild = GetChildren().front();
    if (!badgeChild) {
        return;
    }
    context.PaintChild(badgeChild, offset + badgeChildInitialOffset_);
    if (showMessage_) {
        DrawBadge(context, offset);
        if (LessOrEqual(textSize_.Height(), badgeHeight_)) {
            PaintText(offset + textInitialOffset_, context);
        }
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderBadge::DrawCircleBadge(SkCanvas* canvas, const Offset& offset)
{
    if (!badge_) {
        return;
    }

    SkPaint paint;
    paint.setColor(badge_->GetBadgeColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setAntiAlias(true);
    SkRRect rRect;
    auto circleSize = badge_->GetBadgeCircleSize();
    badgeCircleDiameter_ = badge_->IsBadgeCircleSizeDefined() ? (circleSize.IsValid() ? NormalizeToPx(circleSize) : 0)
                                                              : NormalizeToPx(CIRCLE_BADGE_SIZE);
    badgeCircleRadius_ = badgeCircleDiameter_ / 2;
    double boundaryStartX = 0.0;
    double boundaryStartY = 0.0;
    rRect.setRectXY(
        SkRect::MakeIWH(badgeCircleDiameter_, badgeCircleDiameter_), badgeCircleRadius_, badgeCircleRadius_);
    if (!badge_->IsPositionXy()) {
        auto badgePosition = badge_->GetBadgePosition();
        if (badgePosition == BadgePosition::RIGHT_TOP) {
            rRect.offset(offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY());
            boundaryStartX = offset.GetX() + width_ - badgeCircleDiameter_;
            boundaryStartY = offset.GetY();
        } else if (badgePosition == BadgePosition::RIGHT) {
            rRect.offset(
                offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY() + height_ / 2 - badgeCircleRadius_);
            boundaryStartX = offset.GetX() + width_ - badgeCircleDiameter_;
            boundaryStartY = offset.GetY() + height_ / 2 - badgeCircleRadius_;
        } else {
            rRect.offset(offset.GetX(), offset.GetY() + height_ / 2 - badgeCircleRadius_);
            boundaryStartX = offset.GetX();
            boundaryStartY = offset.GetY() + height_ / 2 - badgeCircleRadius_;
        }
    } else {
        auto badgePositionX = badge_->GetBadgePositionX();
        auto badgePositionY = badge_->GetBadgePositionY();
        boundaryStartX = offset.GetX() + badgePositionX.ConvertToPx();
        boundaryStartY = offset.GetY() + badgePositionY.ConvertToPx();
        rRect.offset(boundaryStartX, boundaryStartY);
    }
    canvas->drawRRect(rRect, paint);
    RenderBadgeBoundary(canvas, boundaryStartX, boundaryStartY, badgeCircleDiameter_, badgeCircleDiameter_);
}
#else
void RosenRenderBadge::DrawCircleBadge(RSCanvas* canvas, const Offset& offset)
{
    if (!badge_) {
        return;
    }

    RSBrush brush;
    brush.SetColor(badge_->GetBadgeColor().GetValue());
    brush.SetAntiAlias(true);

    auto circleSize = badge_->GetBadgeCircleSize();
    badgeCircleDiameter_ = badge_->IsBadgeCircleSizeDefined() ?
        (circleSize.IsValid() ? NormalizeToPx(circleSize) : 0) : NormalizeToPx(CIRCLE_BADGE_SIZE);
    badgeCircleRadius_ = badgeCircleDiameter_ / 2;
    double boundaryStartX = 0.0;
    double boundaryStartY = 0.0;
    RSRoundRect rRect(
        RSRect(0, 0,
            static_cast<RSScalar>(badgeCircleDiameter_),
            static_cast<RSScalar>(badgeCircleDiameter_)),
        badgeCircleRadius_, badgeCircleRadius_);
    if (!badge_->IsPositionXy()) {
        auto badgePosition = badge_->GetBadgePosition();
        if (badgePosition == BadgePosition::RIGHT_TOP) {
            rRect.Offset(offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY());
            boundaryStartX = offset.GetX() + width_ - badgeCircleDiameter_;
            boundaryStartY = offset.GetY();
        } else if (badgePosition == BadgePosition::RIGHT) {
            rRect.Offset(
                offset.GetX() + width_ - badgeCircleDiameter_, offset.GetY() + height_ / 2 - badgeCircleRadius_);
            boundaryStartX = offset.GetX() + width_ - badgeCircleDiameter_;
            boundaryStartY = offset.GetY() + height_ / 2 - badgeCircleRadius_;
        } else {
            rRect.Offset(offset.GetX(), offset.GetY() + height_ / 2 - badgeCircleRadius_);
            boundaryStartX = offset.GetX();
            boundaryStartY = offset.GetY() + height_ / 2 - badgeCircleRadius_;
        }
    } else {
        auto badgePositionX = badge_->GetBadgePositionX();
        auto badgePositionY = badge_->GetBadgePositionY();
        boundaryStartX = offset.GetX() + badgePositionX.ConvertToPx();
        boundaryStartY = offset.GetY() + badgePositionY.ConvertToPx();
        rRect.Offset(boundaryStartX, boundaryStartY);
    }
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rRect);
    canvas->DetachBrush();
    RenderBadgeBoundary(canvas, boundaryStartX, boundaryStartY, badgeCircleDiameter_, badgeCircleDiameter_);
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderBadge::DrawNumericalBadge(SkCanvas* canvas, const Offset& offset)
{
    if (!badge_) {
        return;
    }

    SkPaint paint;
    paint.setColor(badge_->GetBadgeColor().GetValue());
    paint.setStyle(SkPaint::Style::kFill_Style);
    paint.setAntiAlias(true);
    SkRRect rRect;
    textSize_ = CalculateTextSize(textData_, textStyle_, badgeRenderText_);
    auto circleSize = badge_->GetBadgeCircleSize();
    badgeCircleDiameter_ = badge_->IsBadgeCircleSizeDefined() ? (circleSize.IsValid() ? NormalizeToPx(circleSize) : 0)
                                                              : NormalizeToPx(NUMERICAL_BADGE_CIRCLE_SIZE);
    badgeHeight_ = badgeCircleDiameter_;
    auto messageCount = badge_->GetMessageCount();
    auto countLimit = badge_->GetMaxCount();
    if (!textData_.empty() || messageCount > 0) {
        if ((textData_.size() <= 1 && textData_.size() > 0) ||
            ((messageCount < 10 && messageCount <= countLimit) && textData_.empty())) {
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
            badgeWidth_ = badgeCircleDiameter_;
        } else if (textData_.size() > 1 || messageCount > countLimit) {
            badgeWidth_ = textSize_.Width() + NormalizeToPx(NUMERICAL_BADGE_PADDING) * 2;
            badgeWidth_ = badgeCircleDiameter_ > badgeWidth_ ? badgeCircleDiameter_ : badgeWidth_;
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
        }
    }
    rRect.setRectXY(SkRect::MakeIWH(badgeWidth_, badgeHeight_), badgeCircleRadius_, badgeCircleRadius_);
    double boundaryStartX = 0.0;
    double boundaryStartY = 0.0;
    SetBoundaryForNumericalBadge(boundaryStartX, boundaryStartY, rRect, offset);
    canvas->drawRRect(rRect, paint);
    RenderBadgeBoundary(canvas, boundaryStartX, boundaryStartY, badgeWidth_, badgeHeight_);
}
#else
void RosenRenderBadge::DrawNumericalBadge(RSCanvas* canvas, const Offset& offset)
{
    if (!badge_) {
        return;
    }

    RSBrush brush;
    brush.SetColor(badge_->GetBadgeColor().GetValue());
    brush.SetAntiAlias(true);
    textSize_ = CalculateTextSize(textData_, textStyle_, badgeRenderText_);
    auto circleSize = badge_->GetBadgeCircleSize();
    badgeCircleDiameter_ = badge_->IsBadgeCircleSizeDefined() ? (circleSize.IsValid() ? NormalizeToPx(circleSize) : 0)
                                                              : NormalizeToPx(NUMERICAL_BADGE_CIRCLE_SIZE);
    badgeHeight_ = badgeCircleDiameter_;
    auto messageCount = badge_->GetMessageCount();
    auto countLimit = badge_->GetMaxCount();
    if (!textData_.empty() || messageCount > 0) {
        if ((textData_.size() <= 1 && textData_.size() > 0) ||
            ((messageCount < 10 && messageCount <= countLimit) && textData_.empty())) {
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
            badgeWidth_ = badgeCircleDiameter_;
        } else if (textData_.size() > 1 || messageCount > countLimit) {
            badgeWidth_ = textSize_.Width() + NormalizeToPx(NUMERICAL_BADGE_PADDING) * 2;
            badgeWidth_ = badgeCircleDiameter_ > badgeWidth_ ? badgeCircleDiameter_ : badgeWidth_;
            badgeCircleRadius_ = badgeCircleDiameter_ / 2;
        }
    }
    RSRoundRect rRect(RSRect(0, 0, static_cast<RSScalar>(badgeWidth_),
                                        static_cast<RSScalar>(badgeHeight_)),
        badgeCircleRadius_, badgeCircleRadius_);
    double boundaryStartX = 0.0;
    double boundaryStartY = 0.0;
    SetBoundaryForNumericalBadge(boundaryStartX, boundaryStartY, rRect, offset);
    canvas->AttachBrush(brush);
    canvas->DrawRoundRect(rRect);
    canvas->DetachBrush();
    RenderBadgeBoundary(canvas, boundaryStartX, boundaryStartY, badgeWidth_, badgeHeight_);
}
#endif

void RosenRenderBadge::DrawBadge(RenderContext& context, const Offset& offset)
{
    if (!badge_) {
        return;
    }

    auto canvas = static_cast<RosenRenderContext&>(context).GetCanvas();
    if (canvas == nullptr) {
        LOGE("Paint canvas is null");
        return;
    }
    if (!textData_.empty() || badge_->GetMessageCount() > 0) {
        DrawNumericalBadge(canvas, offset);
    } else {
        DrawCircleBadge(canvas, offset);
    }
}

void RosenRenderBadge::PaintText(const Offset& textOffset, RenderContext& context) const
{
    auto textPos = Alignment::GetAlignPosition(Size(badgeWidth_, badgeHeight_), textSize_, Alignment::CENTER);
    if (!badgeRenderText_) {
        return;
    }
    badgeRenderText_->Paint(context, textOffset + textPos);
}

Size RosenRenderBadge::CalculateTextSize(
    const std::string& text, const TextStyle& textStyle, RefPtr<RenderText>& renderText)
{
    if (!renderText) {
        LOGW("the render text is nullptr");
        return Size();
    }
    renderText->SetTextData(text);
    renderText->SetTextStyle(textStyle);
    renderText->PerformLayout();
    return renderText->GetLayoutSize();
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderBadge::RenderBadgeBoundary(SkCanvas* canvas, double startX, double startY, double width, double height)
#else
void RosenRenderBadge::RenderBadgeBoundary(
    RSCanvas* canvas, double startX, double startY, double width, double height)
#endif
{
    if (SystemProperties::GetDebugBoundaryEnabled()) {
        if (canvas == nullptr) {
            LOGE("Paint canvas is null.");
            return;
        }
        Offset boundaryOffset(startX, startY);
        Size layoutSize;
        layoutSize.SetWidth(width);
        layoutSize.SetHeight(height);
        DebugBoundaryPainter::PaintDebugBoundary(canvas, boundaryOffset, layoutSize);
        DebugBoundaryPainter::PaintDebugCorner(canvas, boundaryOffset, layoutSize);
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderBadge::SetBoundaryForNumericalBadge(
    double& boundaryStartX, double& boundaryStartY, SkRRect& rRect, const Offset& offset)
#else
void RosenRenderBadge::SetBoundaryForNumericalBadge(
    double& boundaryStartX, double& boundaryStartY, RSRoundRect& rRect, const Offset& offset)
#endif
{
    if (!badge_->IsPositionXy()) {
        auto badgePosition = badge_->GetBadgePosition();
        if (badgePosition == BadgePosition::RIGHT_TOP) {
            textInitialOffset_ = Offset(
                width_ - badgeCircleDiameter_ + NormalizeToPx(2.0_vp), 0 - NormalizeToPx(2.0_vp));
#ifndef USE_ROSEN_DRAWING
            rRect.offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
#else
            rRect.Offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
#endif
            boundaryStartX = offset.GetX() + textInitialOffset_.GetX();
            boundaryStartY = offset.GetY() + textInitialOffset_.GetY();
        } else if (badgePosition == BadgePosition::RIGHT) {
            textInitialOffset_ = Offset(width_ - badgeCircleDiameter_, height_ / 2 - badgeCircleRadius_);
#ifndef USE_ROSEN_DRAWING
            rRect.offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
#else
            rRect.Offset(offset.GetX() + textInitialOffset_.GetX(), offset.GetY() + textInitialOffset_.GetY());
#endif
            boundaryStartX = offset.GetX() + textInitialOffset_.GetX();
            boundaryStartY = offset.GetY() + textInitialOffset_.GetY();
        } else {
            textInitialOffset_ = Offset(0, height_ / 2 - badgeCircleRadius_);
#ifndef USE_ROSEN_DRAWING
            rRect.offset(offset.GetX(), offset.GetY() + textInitialOffset_.GetY());
#else
            rRect.Offset(offset.GetX(), offset.GetY() + textInitialOffset_.GetY());
#endif
            boundaryStartX = offset.GetX();
            boundaryStartY = offset.GetY() + textInitialOffset_.GetY();
        }
    } else {
        auto badgePositionX = badge_->GetBadgePositionX();
        auto badgePositionY = badge_->GetBadgePositionY();
        boundaryStartX = offset.GetX() + badgePositionX.ConvertToPx();
        boundaryStartY = offset.GetY() + badgePositionY.ConvertToPx();
#ifndef USE_ROSEN_DRAWING
        rRect.offset(boundaryStartX, boundaryStartY);
#else
        rRect.Offset(boundaryStartX, boundaryStartY);
#endif
    }
}

} // namespace OHOS::Ace
