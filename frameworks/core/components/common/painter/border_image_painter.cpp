/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components/common/painter/border_image_painter.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkImage.h"
#endif

namespace OHOS::Ace {

#ifndef USE_ROSEN_DRAWING
BorderImagePainter::BorderImagePainter(
    const Size& paintSize, const RefPtr<Decoration>& decoration, const sk_sp<SkImage>& image, double dipscale)
    : paintSize_(paintSize), decoration_(decoration), image_(image), dipscale_(dipscale)
{}
#else
BorderImagePainter::BorderImagePainter(
    const Size& paintSize, const RefPtr<Decoration>& decoration, const std::shared_ptr<RSImage>& image, double dipscale)
    : paintSize_(paintSize), decoration_(decoration), image_(image), dipscale_(dipscale)
{}
#endif

namespace {
constexpr double EXTRA_OFFSET = 1.0;
} // namespace

void BorderImagePainter::InitPainter()
{
#ifndef USE_ROSEN_DRAWING
    imageWidth_ = std::ceil(image_->width());
    imageHeight_ = std::ceil(image_->height());
#else
    imageWidth_ = std::ceil(image_->GetWidth());
    imageHeight_ = std::ceil(image_->GetHeight());
#endif
    auto border = decoration_->GetBorder();
    auto borderImage = decoration_->GetBorderImage();
    InitBorderImageSlice(borderImage);
    InitBorderImageWidth(border, borderImage);
    InitBorderImageOutset(border, borderImage);
    imageCenterWidth_ = std::ceil(imageWidth_ - leftSlice_ - rightSlice_);
    imageCenterHeight_ = std::ceil(imageHeight_ - topSlice_ - bottomSlice_);
    borderCenterWidth_ = std::ceil(paintSize_.Width() - leftWidth_ - rightWidth_ + leftOutset_ + rightOutset_);
    borderCenterHeight_ = std::ceil(paintSize_.Height() - topWidth_ - bottomWidth_ + topOutset_ + bottomOutset_);
#ifndef USE_ROSEN_DRAWING
    srcRectLeft_ = SkRect::MakeXYWH(0, topSlice_, leftSlice_, imageCenterHeight_);
    srcRectTop_ = SkRect::MakeXYWH(leftSlice_, 0, imageCenterWidth_, topSlice_);
    srcRectRight_ = SkRect::MakeXYWH(imageWidth_ - rightSlice_, topSlice_, rightSlice_, imageCenterHeight_);
    srcRectBottom_ = SkRect::MakeXYWH(leftSlice_, imageHeight_ - bottomSlice_, imageCenterWidth_, bottomSlice_);
#else
    srcRectLeft_ = RSRect(0, topSlice_, leftSlice_, imageCenterHeight_ + topSlice_);
    srcRectTop_ = RSRect(leftSlice_, 0, imageCenterWidth_ + leftSlice_, topSlice_);
    srcRectRight_ = RSRect(imageWidth_ - rightSlice_, topSlice_, imageWidth_, imageCenterHeight_ + topSlice_);
    srcRectBottom_ = RSRect(leftSlice_, imageHeight_ - bottomSlice_, imageCenterWidth_ + leftSlice_, imageHeight_);
#endif
}

void BorderImagePainter::UpdateExtraOffsetToPaintSize(const Offset& extraOffset)
{
    paintSize_ += Size(extraOffset.GetX() * 2, extraOffset.GetY() * 2);
    paintSize_.SetWidth(std::ceil(paintSize_.Width()));
    paintSize_.SetHeight(std::ceil(paintSize_.Height()));
}

void BorderImagePainter::InitBorderImageWidth(Border& border, RefPtr<BorderImage>& borderImage)
{
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);

    if (!decoration_->GetHasBorderImageWidth()) {
        border.Left().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), leftWidth_);
        border.Right().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), rightWidth_);
        border.Top().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), topWidth_);
        border.Bottom().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), bottomWidth_);
        return;
    }

    if (GreatNotEqual(imageLeft.GetBorderImageWidth().Value(), 0.0)) {
        imageLeft.GetBorderImageWidth().NormalizeToPx(
            dipscale_, 0, 0, border.Left().GetWidthInPx(dipscale_), leftWidth_);
    } else {
        border.Left().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), leftWidth_);
    }
    if (GreatNotEqual(imageRight.GetBorderImageWidth().Value(), 0.0)) {
        imageRight.GetBorderImageWidth().NormalizeToPx(
            dipscale_, 0, 0, border.Right().GetWidthInPx(dipscale_), rightWidth_);
    } else {
        border.Right().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), rightWidth_);
    }
    if (GreatNotEqual(imageTop.GetBorderImageWidth().Value(), 0.0)) {
        imageTop.GetBorderImageWidth().NormalizeToPx(dipscale_, 0, 0, border.Top().GetWidthInPx(dipscale_), topWidth_);
    } else {
        border.Top().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), topWidth_);
    }
    if (GreatNotEqual(imageBottom.GetBorderImageWidth().Value(), 0.0)) {
        imageBottom.GetBorderImageWidth().NormalizeToPx(
            dipscale_, 0, 0, border.Bottom().GetWidthInPx(dipscale_), bottomWidth_);
    } else {
        border.Bottom().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), bottomWidth_);
    }
    ParseNegativeNumberToZeroOrCeil(leftWidth_);
    ParseNegativeNumberToZeroOrCeil(rightWidth_);
    ParseNegativeNumberToZeroOrCeil(topWidth_);
    ParseNegativeNumberToZeroOrCeil(bottomWidth_);
}

void BorderImagePainter::InitBorderImageSlice(RefPtr<BorderImage>& borderImage)
{
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);

    if (!decoration_->GetHasBorderImageSlice()) {
        leftSlice_ = imageWidth_;
        topSlice_ = imageHeight_;
        rightSlice_ = imageWidth_;
        bottomSlice_ = imageHeight_;
        paintCornersOnly_ = true;
        return;
    }

    if (GreatNotEqual(imageLeft.GetBorderImageSlice().Value(), 0.0)) {
        imageLeft.GetBorderImageSlice().NormalizeToPx(dipscale_, 0, 0, imageWidth_, leftSlice_);
    }
    if (GreatNotEqual(imageRight.GetBorderImageSlice().Value(), 0.0)) {
        imageRight.GetBorderImageSlice().NormalizeToPx(dipscale_, 0, 0, imageWidth_, rightSlice_);
    }
    if (GreatNotEqual(imageTop.GetBorderImageSlice().Value(), 0.0)) {
        imageTop.GetBorderImageSlice().NormalizeToPx(dipscale_, 0, 0, imageHeight_, topSlice_);
    }
    if (GreatNotEqual(imageBottom.GetBorderImageSlice().Value(), 0.0)) {
        imageBottom.GetBorderImageSlice().NormalizeToPx(dipscale_, 0, 0, imageHeight_, bottomSlice_);
    }
    if (GreatNotEqual(leftSlice_, imageWidth_)) {
        leftSlice_ = imageWidth_;
    }
    if (GreatNotEqual(rightSlice_, imageWidth_)) {
        rightSlice_ = imageWidth_;
    }
    if (GreatNotEqual(topSlice_, imageHeight_)) {
        topSlice_ = imageHeight_;
    }
    if (GreatNotEqual(bottomSlice_, imageHeight_)) {
        bottomSlice_ = imageHeight_;
    }
    ParseNegativeNumberToZeroOrCeil(leftSlice_);
    ParseNegativeNumberToZeroOrCeil(rightSlice_);
    ParseNegativeNumberToZeroOrCeil(topSlice_);
    ParseNegativeNumberToZeroOrCeil(bottomSlice_);
}

void BorderImagePainter::InitBorderImageOutset(Border& border, RefPtr<BorderImage>& borderImage)
{
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);
    if (!decoration_->GetHasBorderImageOutset()) {
        leftOutset_ = 0.0;
        topOutset_ = 0.0;
        rightOutset_ = 0.0;
        bottomOutset_ = 0.0;
        return;
    }
    if (GreatNotEqual(imageLeft.GetBorderImageOutset().Value(), 0.0)) {
        imageLeft.GetBorderImageOutset().NormalizeToPx(
            dipscale_, 0, 0, border.Left().GetWidthInPx(dipscale_), leftOutset_);
    } else {
        border.Left().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), leftOutset_);
    }

    if (GreatNotEqual(imageRight.GetBorderImageOutset().Value(), 0.0)) {
        imageRight.GetBorderImageOutset().NormalizeToPx(
            dipscale_, 0, 0, border.Right().GetWidthInPx(dipscale_), rightOutset_);
    } else {
        border.Right().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Width(), rightOutset_);
    }

    if (GreatNotEqual(imageTop.GetBorderImageOutset().Value(), 0.0)) {
        imageTop.GetBorderImageOutset().NormalizeToPx(
            dipscale_, 0, 0, border.Top().GetWidthInPx(dipscale_), topOutset_);
    } else {
        border.Top().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), topOutset_);
    }

    if (GreatNotEqual(imageBottom.GetBorderImageOutset().Value(), 0.0)) {
        imageBottom.GetBorderImageOutset().NormalizeToPx(
            dipscale_, 0, 0, border.Bottom().GetWidthInPx(dipscale_), bottomOutset_);
    } else {
        border.Bottom().GetWidth().NormalizeToPx(dipscale_, 0, 0, paintSize_.Height(), bottomOutset_);
    }
    ParseNegativeNumberToZeroOrCeil(leftOutset_);
    ParseNegativeNumberToZeroOrCeil(rightOutset_);
    ParseNegativeNumberToZeroOrCeil(topOutset_);
    ParseNegativeNumberToZeroOrCeil(bottomOutset_);
}

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImage(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    Offset ceiledOffset(std::ceil(offset.GetX()), std::ceil(offset.GetY()));
    PaintBorderImageCorners(ceiledOffset, canvas, paint);
    if (paintCornersOnly_) {
        return;
    }
    switch (decoration_->GetBorderImage()->GetRepeatMode()) {
        case BorderImageRepeat::STRETCH:
            PaintBorderImageStretch(ceiledOffset, canvas, paint);
            break;
        case BorderImageRepeat::SPACE:
            PaintBorderImageSpace(ceiledOffset, canvas, paint);
            break;
        case BorderImageRepeat::ROUND:
            PaintBorderImageRound(ceiledOffset, canvas, paint);
            break;
        case BorderImageRepeat::REPEAT:
            PaintBorderImageRepeat(ceiledOffset, canvas, paint);
            break;
        default:
            LOGE("Unsupported Border Image repeat mode");
    }
    if (decoration_->GetBorderImage()->GetNeedFillCenter()) {
        FillBorderImageCenter(ceiledOffset, canvas, paint);
    }
    paint.reset();
}
#else
void BorderImagePainter::PaintBorderImage(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    Offset ceiledOffset(std::ceil(offset.GetX()), std::ceil(offset.GetY()));
    PaintBorderImageCorners(ceiledOffset, canvas, brush);
    if (paintCornersOnly_) {
        return;
    }
    switch (decoration_->GetBorderImage()->GetRepeatMode()) {
        case BorderImageRepeat::STRETCH:
            PaintBorderImageStretch(ceiledOffset, canvas, brush);
            break;
        case BorderImageRepeat::SPACE:
            PaintBorderImageSpace(ceiledOffset, canvas, brush);
            break;
        case BorderImageRepeat::ROUND:
            PaintBorderImageRound(ceiledOffset, canvas, brush);
            break;
        case BorderImageRepeat::REPEAT:
            PaintBorderImageRepeat(ceiledOffset, canvas, brush);
            break;
        default:
            LOGE("Unsupported Border Image repeat mode");
    }
    if (decoration_->GetBorderImage()->GetNeedFillCenter()) {
        FillBorderImageCenter(ceiledOffset, canvas, brush);
    }
    brush.Reset();
}
#endif

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::FillBorderImageCenter(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    double destLeftOffset = offset.GetX() - leftOutset_ + leftWidth_ - EXTRA_OFFSET;
    double destTopOffset = offset.GetY() - topOutset_ + topWidth_ - EXTRA_OFFSET;
    SkRect srcRectCenter = SkRect::MakeXYWH(leftSlice_, topSlice_, imageCenterWidth_, imageCenterHeight_);
    SkRect desRectCenter = SkRect::MakeXYWH(
        destLeftOffset, destTopOffset, borderCenterWidth_ + EXTRA_OFFSET * 2, borderCenterHeight_ + EXTRA_OFFSET * 2);
    canvas->drawImageRect(
        image_, srcRectCenter, desRectCenter, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);
}
#else
void BorderImagePainter::FillBorderImageCenter(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    double destLeftOffset = offset.GetX() - leftOutset_ + leftWidth_ - EXTRA_OFFSET;
    double destTopOffset = offset.GetY() - topOutset_ + topWidth_ - EXTRA_OFFSET;
    RSRect srcRectCenter =
        RSRect(leftSlice_, topSlice_, imageCenterWidth_ + leftSlice_, imageCenterHeight_ + topSlice_);
    RSRect desRectCenter = RSRect(destLeftOffset, destTopOffset, borderCenterWidth_ + EXTRA_OFFSET * 2 + destLeftOffset,
        borderCenterHeight_ + EXTRA_OFFSET * 2 + destTopOffset);

    canvas->AttachBrush(brush);
    RSSamplingOptions samplingOpetions;
    canvas->DrawImageRect(*image_, srcRectCenter, desRectCenter, samplingOpetions);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImageCorners(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    // top left corner
    SkRect srcRectLeftTop = SkRect::MakeXYWH(0, 0, leftSlice_, topSlice_);
    // top right corner
    SkRect srcRectRightTop = SkRect::MakeXYWH(imageWidth_ - rightSlice_, 0, rightSlice_, topSlice_);
    // left bottom corner
    SkRect srcRectLeftBottom = SkRect::MakeXYWH(0, imageHeight_ - bottomSlice_, leftSlice_, bottomSlice_);
    // right bottom corner
    SkRect srcRectRightBottom =
        SkRect::MakeXYWH(imageWidth_ - rightSlice_, imageHeight_ - bottomSlice_, rightSlice_, bottomSlice_);

    // Draw the four corners of the picture to the four corners of the border
    // left top
    SkRect desRectLeftTop =
        SkRect::MakeXYWH(offsetLeftX, offsetTopY, leftWidth_ + EXTRA_OFFSET, topWidth_ + EXTRA_OFFSET);
    canvas->drawImageRect(
        image_, srcRectLeftTop, desRectLeftTop, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);
    // right top
    SkRect desRectRightTop = SkRect::MakeXYWH(
        offsetRightX - rightWidth_ - EXTRA_OFFSET, offsetTopY, rightWidth_ + EXTRA_OFFSET, topWidth_ + EXTRA_OFFSET);
    canvas->drawImageRect(
        image_, srcRectRightTop, desRectRightTop, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);
    // left bottom
    SkRect desRectLeftBottom = SkRect::MakeXYWH(offsetLeftX, offsetBottomY - bottomWidth_ - EXTRA_OFFSET,
        leftWidth_ + EXTRA_OFFSET, bottomWidth_ + EXTRA_OFFSET);
    canvas->drawImageRect(
        image_, srcRectLeftBottom, desRectLeftBottom, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);
    // right bottom
    SkRect desRectRightBottom = SkRect::MakeXYWH(offsetRightX - rightWidth_ - EXTRA_OFFSET,
        offsetBottomY - bottomWidth_ - EXTRA_OFFSET, rightWidth_ + EXTRA_OFFSET, bottomWidth_ + EXTRA_OFFSET);
    canvas->drawImageRect(image_, srcRectRightBottom, desRectRightBottom, SkSamplingOptions(), &paint,
        SkCanvas::kStrict_SrcRectConstraint);
}
#else
void BorderImagePainter::PaintBorderImageCorners(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    // top left corner
    RSRect srcRectLeftTop = RSRect(0, 0, leftSlice_, topSlice_);
    // top right corner
    RSRect srcRectRightTop = RSRect(imageWidth_ - rightSlice_, 0, imageWidth_, topSlice_);
    // left bottom corner
    RSRect srcRectLeftBottom = RSRect(0, imageHeight_ - bottomSlice_, leftSlice_, imageHeight_);
    // right bottom corner
    RSRect srcRectRightBottom =
        RSRect(imageWidth_ - rightSlice_, imageHeight_ - bottomSlice_, imageWidth_, imageHeight_);

    canvas->AttachBrush(brush);
    RSSamplingOptions samplingOpetions;

    // Draw the four corners of the picture to the four corners of the border
    // left top
    RSRect desRectLeftTop =
        RSRect(offsetLeftX, offsetTopY, leftWidth_ + EXTRA_OFFSET + offsetLeftX, topWidth_ + EXTRA_OFFSET + offsetTopY);
    canvas->DrawImageRect(*image_, srcRectLeftTop, desRectLeftTop, samplingOpetions);

    // right top
    RSRect desRectRightTop = RSRect(
        offsetRightX - rightWidth_ - EXTRA_OFFSET, offsetTopY, offsetRightX, topWidth_ + EXTRA_OFFSET + offsetTopY);
    canvas->DrawImageRect(*image_, srcRectRightTop, desRectRightTop, samplingOpetions);

    // left bottom
    RSRect desRectLeftBottom = RSRect(offsetLeftX, offsetBottomY - bottomWidth_ - EXTRA_OFFSET,
        leftWidth_ + EXTRA_OFFSET + offsetLeftX, offsetBottomY);
    canvas->DrawImageRect(*image_, srcRectLeftBottom, desRectLeftBottom, samplingOpetions);

    // right bottom
    RSRect desRectRightBottom = RSRect(offsetRightX - rightWidth_ - EXTRA_OFFSET,
        offsetBottomY - bottomWidth_ - EXTRA_OFFSET, offsetRightX, offsetBottomY);
    canvas->DrawImageRect(*image_, srcRectRightBottom, desRectRightBottom, samplingOpetions);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImageStretch(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    SkRect desRectLeft = SkRect::MakeXYWH(offsetLeftX, offsetTopY + topWidth_, leftWidth_, borderCenterHeight_);

    canvas->drawImageRect(
        image_, srcRectLeft_, desRectLeft, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

    SkRect desRectRight =
        SkRect::MakeXYWH(offsetRightX - rightWidth_, offsetTopY + topWidth_, rightWidth_, borderCenterHeight_);

    canvas->drawImageRect(
        image_, srcRectRight_, desRectRight, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

    SkRect desRectTop = SkRect::MakeXYWH(offsetLeftX + leftWidth_, offsetTopY,
        paintSize_.Width() - leftWidth_ - rightWidth_ + leftOutset_ + rightOutset_, topWidth_);

    canvas->drawImageRect(
        image_, srcRectTop_, desRectTop, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

    SkRect desRectBottom = SkRect::MakeXYWH(offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_,
        paintSize_.Width() - leftWidth_ - rightWidth_ + leftOutset_ + rightOutset_, bottomWidth_);

    canvas->drawImageRect(
        image_, srcRectBottom_, desRectBottom, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);
}
#else
void BorderImagePainter::PaintBorderImageStretch(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    canvas->AttachBrush(brush);
    RSSamplingOptions samplingOpetions;

    RSRect desRectLeft = RSRect(
        offsetLeftX, offsetTopY + topWidth_, leftWidth_ + offsetLeftX, borderCenterHeight_ + offsetTopY + topWidth_);
    canvas->DrawImageRect(*image_, srcRectLeft_, desRectLeft, samplingOpetions);

    RSRect desRectRight = RSRect(
        offsetRightX - rightWidth_, offsetTopY + topWidth_, offsetRightX, borderCenterHeight_ + offsetTopY + topWidth_);
    canvas->DrawImageRect(*image_, srcRectRight_, desRectRight, samplingOpetions);

    RSRect desRectTop = RSRect(offsetLeftX + leftWidth_, offsetTopY,
        paintSize_.Width() - rightWidth_ + leftOutset_ + rightOutset_ + offsetLeftX, topWidth_ + offsetTopY);
    canvas->DrawImageRect(*image_, srcRectTop_, desRectTop, samplingOpetions);

    RSRect desRectBottom = RSRect(offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_,
        paintSize_.Width() - rightWidth_ + leftOutset_ + rightOutset_ + offsetLeftX, offsetBottomY);
    canvas->DrawImageRect(*image_, srcRectBottom_, desRectBottom, samplingOpetions);
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImageRound(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    int32_t roundHorizontalCount = static_cast<int32_t>(borderCenterWidth_ / imageCenterWidth_);
    int32_t roundVerticalCount = static_cast<int32_t>(borderCenterHeight_ / imageCenterHeight_);

    // Surplus
    if (fmod(borderCenterWidth_, imageCenterWidth_) != 0) {
        roundHorizontalCount += 1;
    }

    if (fmod(borderCenterHeight_, imageCenterHeight_) != 0) {
        roundVerticalCount += 1;
    }

    double roundImageWidth = borderCenterWidth_ / roundHorizontalCount;
    double roundImageHeight = borderCenterHeight_ / roundVerticalCount;

    double roundStartHorizontal = offsetLeftX + leftWidth_;

    // draw shrinked border images on top and bottom edge
    for (int32_t i = 0; i < roundHorizontalCount; i++) {
        // top
        SkRect desRectTopRound = SkRect::MakeXYWH(roundStartHorizontal, offsetTopY, roundImageWidth, topWidth_);

        canvas->drawImageRect(
            image_, srcRectTop_, desRectTopRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        // bottom
        SkRect desRectBottomRound =
            SkRect::MakeXYWH(roundStartHorizontal, offsetBottomY - bottomWidth_, roundImageWidth, bottomWidth_);

        canvas->drawImageRect(image_, srcRectBottom_, desRectBottomRound, SkSamplingOptions(), &paint,
            SkCanvas::kStrict_SrcRectConstraint);

        roundStartHorizontal += roundImageWidth;
    }
    double roundStartVertical = offsetTopY + topWidth_;
    // draw shrinked border images on left and right edge
    for (int32_t i = 0; i < roundVerticalCount; i++) {
        // left
        SkRect desRectLeftRound = SkRect::MakeXYWH(offsetLeftX, roundStartVertical, leftWidth_, roundImageHeight);

        canvas->drawImageRect(
            image_, srcRectLeft_, desRectLeftRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        // right
        SkRect desRectRightRound =
            SkRect::MakeXYWH(offsetRightX - rightWidth_, roundStartVertical, rightWidth_, roundImageHeight);

        canvas->drawImageRect(
            image_, srcRectRight_, desRectRightRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        roundStartVertical += roundImageHeight;
    }
}
#else
void BorderImagePainter::PaintBorderImageRound(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    int32_t roundHorizontalCount = static_cast<int32_t>(borderCenterWidth_ / imageCenterWidth_);
    int32_t roundVerticalCount = static_cast<int32_t>(borderCenterHeight_ / imageCenterHeight_);

    // Surplus
    if (fmod(borderCenterWidth_, imageCenterWidth_) != 0) {
        roundHorizontalCount += 1;
    }

    if (fmod(borderCenterHeight_, imageCenterHeight_) != 0) {
        roundVerticalCount += 1;
    }

    double roundImageWidth = borderCenterWidth_ / roundHorizontalCount;
    double roundImageHeight = borderCenterHeight_ / roundVerticalCount;

    double roundStartHorizontal = offsetLeftX + leftWidth_;

    canvas->AttachBrush(brush);
    RSSamplingOptions samplingOpetions;

    // draw shrinked border images on top and bottom edge
    for (int32_t i = 0; i < roundHorizontalCount; i++) {
        // top
        RSRect desRectTopRound =
            RSRect(roundStartHorizontal, offsetTopY, roundImageWidth + roundStartHorizontal, topWidth_ + offsetTopY);
        canvas->DrawImageRect(*image_, srcRectTop_, desRectTopRound, samplingOpetions);
        // bottom
        RSRect desRectBottomRound = RSRect(
            roundStartHorizontal, offsetBottomY - bottomWidth_, roundImageWidth + roundStartHorizontal, offsetBottomY);
        canvas->DrawImageRect(*image_, srcRectBottom_, desRectBottomRound, samplingOpetions);
        roundStartHorizontal += roundImageWidth;
    }
    double roundStartVertical = offsetTopY + topWidth_;
    // draw shrinked border images on left and right edge
    for (int32_t i = 0; i < roundVerticalCount; i++) {
        // left
        RSRect desRectLeftRound =
            RSRect(offsetLeftX, roundStartVertical, leftWidth_ + offsetLeftX, roundImageHeight + roundStartVertical);
        canvas->DrawImageRect(*image_, srcRectLeft_, desRectLeftRound, samplingOpetions);
        // right
        RSRect desRectRightRound =
            RSRect(offsetRightX - rightWidth_, roundStartVertical, offsetRightX, roundImageHeight + roundStartVertical);
        canvas->DrawImageRect(*image_, srcRectRight_, desRectRightRound, samplingOpetions);
        roundStartVertical += roundImageHeight;
    }
    canvas->DetachBrush();
}
#endif

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImageSpace(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
#else
void BorderImagePainter::PaintBorderImageSpace(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
#endif
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    // calculate maximum count of image pieces can fit in border
    int32_t roundHorizontalCount = static_cast<int32_t>(borderCenterWidth_ / imageCenterWidth_);
    int32_t roundVerticalCount = static_cast<int32_t>(borderCenterHeight_ / imageCenterHeight_);
    if (roundHorizontalCount == 0.0) {
        LOGW("Border image center width exceeds horizontal border center length, left and right side will not paint");
    }
    if (roundVerticalCount == 0.0) {
        LOGW("Border image center height exceeds vertical border center length, top and bottom side will not paint");
    }
    // fmod(borderCenterWidth_, imageCenterWidth_) will return total blank length,
    // and there are roundHorizontalCount + 1 blanks
    double blankHorizontalSize = fmod(borderCenterWidth_, imageCenterWidth_) / (roundHorizontalCount + 1);
    double blankVerticalSize = fmod(borderCenterHeight_, imageCenterHeight_) / (roundVerticalCount + 1);

    double roundStartHorizontal = offsetLeftX + leftWidth_ + blankHorizontalSize;
    for (int32_t i = 0; i < roundHorizontalCount; i++) {
#ifndef USE_ROSEN_DRAWING
        // top
        SkRect desRectTopRound = SkRect::MakeXYWH(roundStartHorizontal, offsetTopY, imageCenterWidth_, topWidth_);

        canvas->drawImageRect(
            image_, srcRectTop_, desRectTopRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        // bottom
        SkRect desRectBottomRound =
            SkRect::MakeXYWH(roundStartHorizontal, offsetBottomY - bottomWidth_, imageCenterWidth_, bottomWidth_);

        canvas->drawImageRect(image_, srcRectBottom_, desRectBottomRound, SkSamplingOptions(), &paint,
            SkCanvas::kStrict_SrcRectConstraint);

#else
        canvas->AttachBrush(brush);
        // top
        RSRect desRectTopRound =
            RSRect(roundStartHorizontal, offsetTopY, imageCenterWidth_ + roundStartHorizontal, topWidth_ + offsetTopY);
        canvas->DrawImageRect(*image_, srcRectTop_, desRectTopRound, RSSamplingOptions());
        // bottom
        RSRect desRectBottomRound = RSRect(roundStartHorizontal, offsetBottomY - bottomWidth_,
            imageCenterWidth_ + roundStartHorizontal, offsetBottomY);
        canvas->DrawImageRect(*image_, srcRectBottom_, desRectBottomRound, RSSamplingOptions());
#endif
        roundStartHorizontal += imageCenterWidth_ + blankHorizontalSize;
    }

    double roundStartVertical = offsetTopY + topWidth_ + blankVerticalSize;
    for (int32_t i = 0; i < roundVerticalCount; i++) {
#ifndef USE_ROSEN_DRAWING
        // left
        SkRect desRectLeftRound = SkRect::MakeXYWH(offsetLeftX, roundStartVertical, leftWidth_, imageCenterHeight_);

        canvas->drawImageRect(
            image_, srcRectLeft_, desRectLeftRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        // right
        SkRect desRectRightRound =
            SkRect::MakeXYWH(offsetRightX - rightWidth_, roundStartVertical, rightWidth_, imageCenterHeight_);

        canvas->drawImageRect(
            image_, srcRectRight_, desRectRightRound, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

#else
        // left
        RSRect desRectLeftRound =
            RSRect(offsetLeftX, roundStartVertical, leftWidth_ + offsetLeftX, imageCenterHeight_ + roundStartVertical);
        canvas->DrawImageRect(*image_, srcRectLeft_, desRectLeftRound, RSSamplingOptions());
        // right
        RSRect desRectRightRound = RSRect(
            offsetRightX - rightWidth_, roundStartVertical, offsetRightX, imageCenterHeight_ + roundStartVertical);
        canvas->DrawImageRect(*image_, srcRectRight_, desRectRightRound, RSSamplingOptions());
#endif
        roundStartVertical += imageCenterHeight_ + blankVerticalSize;
    }
#ifdef USE_ROSEN_DRAWING
    canvas->DetachBrush();
#endif
}

#ifndef USE_ROSEN_DRAWING
void BorderImagePainter::PaintBorderImageRepeat(const Offset& offset, SkCanvas* canvas, SkPaint& paint)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    double widthFactor = 0.0;
    if (GreatNotEqual(imageCenterWidth_, 0.0)) {
        widthFactor = borderCenterWidth_ / imageCenterWidth_;
        if (GreatNotEqual(widthFactor, 0.0) && LessOrEqual(widthFactor, 1.0)) {
            double halfSurplusImageCenterWidth = (imageCenterWidth_ - borderCenterWidth_) / 2;
            SkRect srcRectTop =
                SkRect::MakeXYWH(halfSurplusImageCenterWidth + leftSlice_, 0, borderCenterWidth_, topSlice_);
            SkRect desRectTop = SkRect::MakeXYWH(offsetLeftX + leftWidth_, offsetTopY, borderCenterWidth_, topWidth_);

            canvas->drawImageRect(
                image_, srcRectTop, desRectTop, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectBottom = SkRect::MakeXYWH(halfSurplusImageCenterWidth + leftSlice_,
                imageHeight_ - bottomSlice_, borderCenterWidth_, bottomSlice_);
            SkRect desRectBottom = SkRect::MakeXYWH(offsetLeftX + leftWidth_,
                offset.GetY() + paintSize_.Height() - bottomWidth_ + bottomOutset_, borderCenterWidth_, bottomWidth_);

            canvas->drawImageRect(
                image_, srcRectBottom, desRectBottom, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        } else if (GreatNotEqual(widthFactor, 1.0)) {
            double halfSurplusHorizontalLength = 0;
            halfSurplusHorizontalLength = (borderCenterWidth_ - (int)(widthFactor)*imageCenterWidth_) / 2;
            SkRect srcRectTopLeft = SkRect::MakeXYWH(
                imageWidth_ - rightSlice_ - halfSurplusHorizontalLength, 0, halfSurplusHorizontalLength, topSlice_);
            SkRect desRectTopLeftEnd =
                SkRect::MakeXYWH(offsetLeftX + leftWidth_, offsetTopY, halfSurplusHorizontalLength, topWidth_);

            canvas->drawImageRect(image_, srcRectTopLeft, desRectTopLeftEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectTopRight = SkRect::MakeXYWH(leftSlice_, 0, halfSurplusHorizontalLength, topSlice_);
            SkRect desRectTopRightEnd =
                SkRect::MakeXYWH(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength,
                    offsetTopY, halfSurplusHorizontalLength, topWidth_);

            canvas->drawImageRect(image_, srcRectTopRight, desRectTopRightEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectBottomLeft = SkRect::MakeXYWH(imageWidth_ - rightSlice_ - halfSurplusHorizontalLength,
                imageHeight_ - bottomSlice_, halfSurplusHorizontalLength, bottomSlice_);
            SkRect desRectBottomLeftEnd = SkRect::MakeXYWH(
                offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_, halfSurplusHorizontalLength, bottomWidth_);

            canvas->drawImageRect(image_, srcRectBottomLeft, desRectBottomLeftEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectBottomRight =
                SkRect::MakeXYWH(leftSlice_, imageHeight_ - bottomSlice_, halfSurplusHorizontalLength, bottomSlice_);
            SkRect desRectBottomRightEnd =
                SkRect::MakeXYWH(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength,
                    offsetBottomY - bottomWidth_, halfSurplusHorizontalLength, bottomWidth_);

            canvas->drawImageRect(image_, srcRectBottomRight, desRectBottomRightEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            double repeatHorizontalStart = offsetLeftX + leftWidth_ + halfSurplusHorizontalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(widthFactor); i++) {
                // top
                SkRect desRectTopRepeat =
                    SkRect::MakeXYWH(repeatHorizontalStart, offsetTopY, imageCenterWidth_, topWidth_);

                canvas->drawImageRect(image_, srcRectTop_, desRectTopRepeat, SkSamplingOptions(), &paint,
                    SkCanvas::kStrict_SrcRectConstraint);

                // bottom
                SkRect desRectBottomRepeat = SkRect::MakeXYWH(
                    repeatHorizontalStart, offsetBottomY - bottomWidth_, imageCenterWidth_, bottomWidth_);

                canvas->drawImageRect(image_, srcRectBottom_, desRectBottomRepeat, SkSamplingOptions(), &paint,
                    SkCanvas::kStrict_SrcRectConstraint);

                repeatHorizontalStart += imageCenterWidth_;
            }
        }
    }

    double heightFactor = 0.0;
    double destTopOffsetY = offsetTopY + topWidth_;
    if (GreatNotEqual(imageCenterHeight_, 0.0)) {
        heightFactor = borderCenterHeight_ / imageCenterHeight_;
        if (GreatNotEqual(heightFactor, 0.0) && LessOrEqual(heightFactor, 1.0)) {
            double halfSurplusImageCenterHeight = (imageCenterHeight_ - borderCenterHeight_) / 2;
            SkRect srcRectLeft =
                SkRect::MakeXYWH(0, topSlice_ + halfSurplusImageCenterHeight, leftSlice_, borderCenterHeight_);
            SkRect desRectLeft = SkRect::MakeXYWH(offsetLeftX, destTopOffsetY, leftWidth_, borderCenterHeight_);

            canvas->drawImageRect(
                image_, srcRectLeft, desRectLeft, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectRight = SkRect::MakeXYWH(
                imageWidth_ - rightSlice_, topSlice_ + halfSurplusImageCenterHeight, rightSlice_, borderCenterHeight_);
            SkRect desRectRight = SkRect::MakeXYWH(offset.GetX() + paintSize_.Width() - rightWidth_ + rightOutset_,
                destTopOffsetY, rightWidth_, borderCenterHeight_);

            canvas->drawImageRect(
                image_, srcRectRight, desRectRight, SkSamplingOptions(), &paint, SkCanvas::kStrict_SrcRectConstraint);

        } else if (GreatNotEqual(heightFactor, 1.0)) {
            double halfSurplusVerticalLength = 0;
            halfSurplusVerticalLength = (borderCenterHeight_ - (int)(heightFactor)*imageCenterHeight_) / 2;
            SkRect srcRectLeftTop = SkRect::MakeXYWH(
                0, imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, leftSlice_, halfSurplusVerticalLength);
            SkRect desRectLeftTopStart =
                SkRect::MakeXYWH(offsetLeftX, destTopOffsetY, leftWidth_, halfSurplusVerticalLength);

            canvas->drawImageRect(image_, srcRectLeftTop, desRectLeftTopStart, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectRightTop = SkRect::MakeXYWH(imageWidth_ - rightSlice_,
                imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, rightSlice_, halfSurplusVerticalLength);
            SkRect desRectRightTopStart =
                SkRect::MakeXYWH(offsetRightX - rightWidth_, destTopOffsetY, rightWidth_, halfSurplusVerticalLength);

            canvas->drawImageRect(image_, srcRectRightTop, desRectRightTopStart, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectLeftBottom = SkRect::MakeXYWH(0, topSlice_, leftSlice_, halfSurplusVerticalLength);
            SkRect desRectLeftBottomEnd = SkRect::MakeXYWH(offsetLeftX,
                offsetBottomY - bottomWidth_ - halfSurplusVerticalLength, leftWidth_, halfSurplusVerticalLength);

            canvas->drawImageRect(image_, srcRectLeftBottom, desRectLeftBottomEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            SkRect srcRectRightBottom =
                SkRect::MakeXYWH(imageWidth_ - rightSlice_, topSlice_, rightSlice_, halfSurplusVerticalLength);
            SkRect desRectRightBottomEnd = SkRect::MakeXYWH(offsetRightX - rightWidth_,
                offsetBottomY - bottomWidth_ - halfSurplusVerticalLength, rightWidth_, halfSurplusVerticalLength);

            canvas->drawImageRect(image_, srcRectRightBottom, desRectRightBottomEnd, SkSamplingOptions(), &paint,
                SkCanvas::kStrict_SrcRectConstraint);

            double repeatVerticalStart = destTopOffsetY + halfSurplusVerticalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(heightFactor); i++) {
                // left
                SkRect desRectLeftRepeat =
                    SkRect::MakeXYWH(offsetLeftX, repeatVerticalStart, leftWidth_, imageCenterHeight_);
                canvas->drawImageRect(image_, srcRectLeft_, desRectLeftRepeat, SkSamplingOptions(), &paint,
                    SkCanvas::kStrict_SrcRectConstraint);

                // right
                SkRect desRectRightRepeat =
                    SkRect::MakeXYWH(offsetRightX - rightWidth_, repeatVerticalStart, rightWidth_, imageCenterHeight_);
                canvas->drawImageRect(image_, srcRectRight_, desRectRightRepeat, SkSamplingOptions(), &paint,
                    SkCanvas::kStrict_SrcRectConstraint);
                repeatVerticalStart += imageCenterHeight_;
            }
        }
    }
    paint.reset();
}
#else
void BorderImagePainter::PaintBorderImageRepeat(const Offset& offset, RSCanvas* canvas, RSBrush& brush)
{
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    canvas->AttachBrush(brush);
    RSSamplingOptions samplingOpetions;

    double widthFactor = 0.0;
    if (GreatNotEqual(imageCenterWidth_, 0.0)) {
        widthFactor = borderCenterWidth_ / imageCenterWidth_;
        if (GreatNotEqual(widthFactor, 0.0) && LessOrEqual(widthFactor, 1.0)) {
            double halfSurplusImageCenterWidth = (imageCenterWidth_ - borderCenterWidth_) / 2;
            RSRect srcRectTop = RSRect(halfSurplusImageCenterWidth + leftSlice_, 0,
                borderCenterWidth_ + halfSurplusImageCenterWidth + leftSlice_, topSlice_);
            RSRect desRectTop = RSRect(offsetLeftX + leftWidth_, offsetTopY,
                borderCenterWidth_ + offsetLeftX + leftWidth_, topWidth_ + offsetTopY);
            canvas->DrawImageRect(*image_, srcRectTop, desRectTop, samplingOpetions);

            RSRect srcRectBottom = RSRect(halfSurplusImageCenterWidth + leftSlice_, imageHeight_ - bottomSlice_,
                borderCenterWidth_ + halfSurplusImageCenterWidth + leftSlice_, imageHeight_);
            RSRect desRectBottom =
                RSRect(offsetLeftX + leftWidth_, offset.GetY() + paintSize_.Height() - bottomWidth_ + bottomOutset_,
                    borderCenterWidth_ + offsetLeftX + leftWidth_, offset.GetY() + paintSize_.Height() + bottomOutset_);
            canvas->DrawImageRect(*image_, srcRectBottom, desRectBottom, samplingOpetions);
        } else if (GreatNotEqual(widthFactor, 1.0)) {
            double halfSurplusHorizontalLength = 0;
            halfSurplusHorizontalLength = (borderCenterWidth_ - (int)(widthFactor)*imageCenterWidth_) / 2;
            RSRect srcRectTopLeft = RSRect(
                imageWidth_ - rightSlice_ - halfSurplusHorizontalLength, 0, imageWidth_ - rightSlice_, topSlice_);
            RSRect desRectTopLeftEnd = RSRect(offsetLeftX + leftWidth_, offsetTopY,
                halfSurplusHorizontalLength + offsetLeftX + leftWidth_, topWidth_ + offsetTopY);
            canvas->DrawImageRect(*image_, srcRectTopLeft, desRectTopLeftEnd, samplingOpetions);

            RSRect srcRectTopRight = RSRect(leftSlice_, 0, halfSurplusHorizontalLength + leftSlice_, topSlice_);
            RSRect desRectTopRightEnd =
                RSRect(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength, offsetTopY,
                    offsetLeftX + leftWidth_ + borderCenterWidth_, topWidth_ + offsetTopY);
            canvas->DrawImageRect(*image_, srcRectTopRight, desRectTopRightEnd, samplingOpetions);

            RSRect srcRectBottomLeft = RSRect(imageWidth_ - rightSlice_ - halfSurplusHorizontalLength,
                imageHeight_ - bottomSlice_, imageWidth_ - rightSlice_, imageHeight_);
            RSRect desRectBottomLeftEnd = RSRect(offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_,
                halfSurplusHorizontalLength + offsetLeftX + leftWidth_, offsetBottomY);
            canvas->DrawImageRect(*image_, srcRectBottomLeft, desRectBottomLeftEnd, samplingOpetions);

            RSRect srcRectBottomRight =
                RSRect(leftSlice_, imageHeight_ - bottomSlice_, halfSurplusHorizontalLength + leftSlice_, imageHeight_);
            RSRect desRectBottomRightEnd =
                RSRect(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength,
                    offsetBottomY - bottomWidth_, offsetLeftX + leftWidth_ + borderCenterWidth_, offsetBottomY);
            canvas->DrawImageRect(*image_, srcRectBottomRight, desRectBottomRightEnd, samplingOpetions);

            double repeatHorizontalStart = offsetLeftX + leftWidth_ + halfSurplusHorizontalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(widthFactor); i++) {
                // top
                RSRect desRectTopRepeat = RSRect(repeatHorizontalStart, offsetTopY,
                    imageCenterWidth_ + repeatHorizontalStart, topWidth_ + offsetTopY);
                canvas->DrawImageRect(*image_, srcRectTop_, desRectTopRepeat, samplingOpetions);

                // bottom
                RSRect desRectBottomRepeat = RSRect(repeatHorizontalStart, offsetBottomY - bottomWidth_,
                    imageCenterWidth_ + repeatHorizontalStart, offsetBottomY);
                canvas->DrawImageRect(*image_, srcRectBottom_, desRectBottomRepeat, samplingOpetions);

                repeatHorizontalStart += imageCenterWidth_;
            }
        }
    }

    double heightFactor = 0.0;
    double destTopOffsetY = offsetTopY + topWidth_;
    if (GreatNotEqual(imageCenterHeight_, 0.0)) {
        heightFactor = borderCenterHeight_ / imageCenterHeight_;
        if (GreatNotEqual(heightFactor, 0.0) && LessOrEqual(heightFactor, 1.0)) {
            double halfSurplusImageCenterHeight = (imageCenterHeight_ - borderCenterHeight_) / 2;
            RSRect srcRectLeft = RSRect(0, topSlice_ + halfSurplusImageCenterHeight, leftSlice_,
                borderCenterHeight_ + topSlice_ + halfSurplusImageCenterHeight);
            RSRect desRectLeft =
                RSRect(offsetLeftX, destTopOffsetY, leftWidth_ + offsetLeftX, borderCenterHeight_ + destTopOffsetY);
            canvas->DrawImageRect(*image_, srcRectLeft, desRectLeft, samplingOpetions);

            RSRect srcRectRight = RSRect(imageWidth_ - rightSlice_, topSlice_ + halfSurplusImageCenterHeight,
                imageWidth_, borderCenterHeight_ + topSlice_ + halfSurplusImageCenterHeight);
            RSRect desRectRight =
                RSRect(offset.GetX() + paintSize_.Width() - rightWidth_ + rightOutset_, destTopOffsetY,
                    offset.GetX() + paintSize_.Width() + rightOutset_, borderCenterHeight_ + destTopOffsetY);
            canvas->DrawImageRect(*image_, srcRectRight, desRectRight, samplingOpetions);
        } else if (GreatNotEqual(heightFactor, 1.0)) {
            double halfSurplusVerticalLength = 0;
            halfSurplusVerticalLength = (borderCenterHeight_ - (int)(heightFactor)*imageCenterHeight_) / 2;
            RSRect srcRectLeftTop = RSRect(
                0, imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, leftSlice_, imageHeight_ - bottomSlice_);
            RSRect desRectLeftTopStart = RSRect(
                offsetLeftX, destTopOffsetY, leftWidth_ + offsetLeftX, halfSurplusVerticalLength + destTopOffsetY);
            canvas->DrawImageRect(*image_, srcRectLeftTop, desRectLeftTopStart, samplingOpetions);

            RSRect srcRectRightTop = RSRect(imageWidth_ - rightSlice_,
                imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, imageWidth_, imageHeight_ - bottomSlice_);
            RSRect desRectRightTopStart = RSRect(
                offsetRightX - rightWidth_, destTopOffsetY, offsetRightX, halfSurplusVerticalLength + destTopOffsetY);
            canvas->DrawImageRect(*image_, srcRectRightTop, desRectRightTopStart, samplingOpetions);

            RSRect srcRectLeftBottom = RSRect(0, topSlice_, leftSlice_, halfSurplusVerticalLength + leftSlice_);
            RSRect desRectLeftBottomEnd = RSRect(offsetLeftX, offsetBottomY - bottomWidth_ - halfSurplusVerticalLength,
                leftWidth_ + offsetLeftX, offsetBottomY - bottomWidth_);
            canvas->DrawImageRect(*image_, srcRectLeftBottom, desRectLeftBottomEnd, samplingOpetions);

            RSRect srcRectRightBottom =
                RSRect(imageWidth_ - rightSlice_, topSlice_, imageWidth_, halfSurplusVerticalLength + topSlice_);
            RSRect desRectRightBottomEnd = RSRect(offsetRightX - rightWidth_,
                offsetBottomY - bottomWidth_ - halfSurplusVerticalLength, offsetRightX, offsetBottomY - bottomWidth_);
            canvas->DrawImageRect(*image_, srcRectRightBottom, desRectRightBottomEnd, samplingOpetions);

            double repeatVerticalStart = destTopOffsetY + halfSurplusVerticalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(heightFactor); i++) {
                // left
                RSRect desRectLeftRepeat = RSRect(offsetLeftX, repeatVerticalStart, leftWidth_ + offsetLeftX,
                    imageCenterHeight_ + repeatVerticalStart);
                canvas->DrawImageRect(*image_, srcRectLeft_, desRectLeftRepeat, samplingOpetions);

                // right
                RSRect desRectRightRepeat = RSRect(offsetRightX - rightWidth_, repeatVerticalStart, offsetRightX,
                    imageCenterHeight_ + repeatVerticalStart);
                canvas->DrawImageRect(*image_, srcRectRight_, desRectRightRepeat, samplingOpetions);

                repeatVerticalStart += imageCenterHeight_;
            }
        }
    }
    canvas->DetachBrush();
    brush.Reset();
}
#endif

void BorderImagePainter::ParseNegativeNumberToZeroOrCeil(double& value)
{
    if (LessNotEqual(value, 0.0)) {
        value = 0.0;
    }
    value = std::ceil(value);
}

} // namespace OHOS::Ace
