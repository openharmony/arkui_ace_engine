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

#include "core/components_ng/render/border_image_painter.h"

namespace {
constexpr double EXTRA_OFFSET = 1.0;
} // namespace

namespace OHOS::Ace::NG {
BorderImagePainter::BorderImagePainter(BorderImageProperty bdImageProps,
    const std::unique_ptr<BorderWidthProperty>& widthProp, const SizeF& paintSize, const RSImage& image,
    const DisplayScaleInfo& dipscaleInfo)
    : hasWidthProp_(widthProp != nullptr), borderImageProperty_(std::move(bdImageProps)), paintSize_(paintSize),
      image_(image)
{
    dipScale_ = dipscaleInfo.vpScale;
    lpxScale_ = dipscaleInfo.lpxScale;
    if (hasWidthProp_) {
        widthProp_ = *widthProp;
    }
    imageWidth_ = image_.GetWidth();
    imageHeight_ = image_.GetHeight();
    InitPainter();
}

void BorderImagePainter::InitPainter()
{
    CHECK_NULL_VOID(borderImageProperty_.GetBorderImage());
    InitBorderImageSlice();
    InitBorderImageWidth();
    InitBorderImageOutset();
    imageCenterWidth_ = std::ceil(imageWidth_ - leftSlice_ - rightSlice_);
    imageCenterHeight_ = std::ceil(imageHeight_ - topSlice_ - bottomSlice_);
    borderCenterWidth_ = std::ceil(paintSize_.Width() - leftWidth_ - rightWidth_ + leftOutset_ + rightOutset_);
    borderCenterHeight_ = std::ceil(paintSize_.Height() - topWidth_ - bottomWidth_ + topOutset_ + bottomOutset_);
    srcRectLeft_ = RSRect(0, topSlice_, leftSlice_, topSlice_ + imageCenterHeight_);
    srcRectTop_ = RSRect(leftSlice_, 0, leftSlice_ + imageCenterWidth_, topSlice_);
    srcRectRight_ = RSRect(imageWidth_ - rightSlice_, topSlice_, imageWidth_, topSlice_ + imageCenterHeight_);
    srcRectBottom_ = RSRect(leftSlice_, imageHeight_ - bottomSlice_, leftSlice_ + imageCenterWidth_, imageHeight_);
}

void BorderImagePainter::InitBorderImageSlice()
{
    auto borderImage = borderImageProperty_.GetBorderImageValue();
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);
    if (!borderImageProperty_.GetHasBorderImageSlice()) {
        leftSlice_ = imageWidth_;
        topSlice_ = imageHeight_;
        rightSlice_ = imageWidth_;
        bottomSlice_ = imageHeight_;
        paintCornersOnly_ = true;
        return;
    }

    if (GreatNotEqual(imageLeft.GetBorderImageSlice().Value(), 0.0)) {
        imageLeft.GetBorderImageSlice().NormalizeToPx(dipScale_, 0.0, lpxScale_, imageWidth_, leftSlice_);
    }
    if (GreatNotEqual(imageRight.GetBorderImageSlice().Value(), 0.0)) {
        imageRight.GetBorderImageSlice().NormalizeToPx(dipScale_, 0.0, lpxScale_, imageWidth_, rightSlice_);
    }
    if (GreatNotEqual(imageTop.GetBorderImageSlice().Value(), 0.0)) {
        imageTop.GetBorderImageSlice().NormalizeToPx(dipScale_, 0.0, lpxScale_, imageHeight_, topSlice_);
    }
    if (GreatNotEqual(imageBottom.GetBorderImageSlice().Value(), 0.0)) {
        imageBottom.GetBorderImageSlice().NormalizeToPx(dipScale_, 0.0, lpxScale_, imageHeight_, bottomSlice_);
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

void BorderImagePainter::InitBorderImageWidth()
{
    if (!borderImageProperty_.GetHasBorderImageWidth() && !hasWidthProp_) {
        return;
    }
    auto borderImage = borderImageProperty_.GetBorderImageValue();
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);

    if (GreatNotEqual(imageLeft.GetBorderImageWidth().Value(), 0.0)) {
        imageLeft.GetBorderImageWidth().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), leftWidth_);
    } else if (hasWidthProp_) {
        widthProp_.leftDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), leftWidth_);
    }
    if (GreatNotEqual(imageRight.GetBorderImageWidth().Value(), 0.0)) {
        imageRight.GetBorderImageWidth().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), rightWidth_);
    } else if (hasWidthProp_) {
        widthProp_.rightDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), rightWidth_);
    }
    if (GreatNotEqual(imageTop.GetBorderImageWidth().Value(), 0.0)) {
        imageTop.GetBorderImageWidth().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), topWidth_);
    } else if (hasWidthProp_) {
        widthProp_.topDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), topWidth_);
    }
    if (GreatNotEqual(imageBottom.GetBorderImageWidth().Value(), 0.0)) {
        imageBottom.GetBorderImageWidth().NormalizeToPx(
            dipScale_, 0.0, lpxScale_, paintSize_.Height(), bottomWidth_);
    } else if (hasWidthProp_) {
        widthProp_.bottomDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), bottomWidth_);
    }

    ParseNegativeNumberToZeroOrCeil(leftWidth_);
    ParseNegativeNumberToZeroOrCeil(rightWidth_);
    ParseNegativeNumberToZeroOrCeil(topWidth_);
    ParseNegativeNumberToZeroOrCeil(bottomWidth_);
}

RectF BorderImagePainter::GetDrawRect(const OffsetF& offset)
{
    const float offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    const float offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    const float offsetTopY = std::ceil(offset.GetY() - topOutset_);
    const float offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    // desRectLeftTop:
    // [offsetLeftX, offsetTopY, offsetLeftX + leftWidth_ + EXTRA_OFFSET, offsetTopY + topWidth_ + EXTRA_OFFSET]
    // desRectRightBottom:
    // [offsetRightX - rightWidth_ - EXTRA_OFFSET, offsetBottomY - bottomWidth_ - EXTRA_OFFSET, offsetRightX,
    // offsetBottomY]
    float rbX = offsetRightX - rightWidth_ - EXTRA_OFFSET + offsetRightX;
    float rbY = offsetBottomY - bottomWidth_ - EXTRA_OFFSET + offsetBottomY;

    return { offsetLeftX, offsetTopY, rbX - offsetLeftX, rbY - offsetTopY };
}

void BorderImagePainter::InitBorderImageOutset()
{
    if (!borderImageProperty_.GetHasBorderImageOutset() && !hasWidthProp_) {
        return;
    }
    auto borderImage = borderImageProperty_.GetBorderImageValue();
    BorderImageEdge imageLeft = borderImage->GetBorderImageEdge(BorderImageDirection::LEFT);
    BorderImageEdge imageTop = borderImage->GetBorderImageEdge(BorderImageDirection::TOP);
    BorderImageEdge imageRight = borderImage->GetBorderImageEdge(BorderImageDirection::RIGHT);
    BorderImageEdge imageBottom = borderImage->GetBorderImageEdge(BorderImageDirection::BOTTOM);

    if (GreatNotEqual(imageLeft.GetBorderImageOutset().Value(), 0.0)) {
        imageLeft.GetBorderImageOutset().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), leftOutset_);
    } else if (hasWidthProp_) {
        widthProp_.leftDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), leftOutset_);
    }
    if (GreatNotEqual(imageRight.GetBorderImageOutset().Value(), 0.0)) {
        imageRight.GetBorderImageOutset().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), rightOutset_);
    } else if (hasWidthProp_) {
        widthProp_.rightDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Width(), rightOutset_);
    }
    if (GreatNotEqual(imageTop.GetBorderImageOutset().Value(), 0.0)) {
        imageTop.GetBorderImageOutset().NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), topOutset_);
    } else if (hasWidthProp_) {
        widthProp_.topDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), topOutset_);
    }
    if (GreatNotEqual(imageBottom.GetBorderImageOutset().Value(), 0.0)) {
        imageBottom.GetBorderImageOutset().NormalizeToPx(
            dipScale_, 0.0, lpxScale_, paintSize_.Height(), bottomOutset_);
    } else if (hasWidthProp_) {
        widthProp_.bottomDimen->NormalizeToPx(dipScale_, 0.0, lpxScale_, paintSize_.Height(), bottomOutset_);
    }

    ParseNegativeNumberToZeroOrCeil(leftOutset_);
    ParseNegativeNumberToZeroOrCeil(rightOutset_);
    ParseNegativeNumberToZeroOrCeil(topOutset_);
    ParseNegativeNumberToZeroOrCeil(bottomOutset_);
}

void BorderImagePainter::PaintBorderImage(const OffsetF& offset, RSCanvas& canvas) const
{
    CHECK_NULL_VOID(borderImageProperty_.GetBorderImage());
    OffsetF ceiledOffset(std::ceil(offset.GetX()), std::ceil(offset.GetY()));
    RSPen pen;
    pen.SetAntiAlias(true);
    canvas.AttachPen(pen);
    canvas.Save();
    PaintBorderImageCorners(ceiledOffset, canvas);
    if (paintCornersOnly_) {
        return;
    }
    switch (borderImageProperty_.GetBorderImageValue()->GetRepeatMode()) {
        case BorderImageRepeat::STRETCH:
            PaintBorderImageStretch(ceiledOffset, canvas);
            break;
        case BorderImageRepeat::SPACE:
            PaintBorderImageSpace(ceiledOffset, canvas);
            break;
        case BorderImageRepeat::ROUND:
            PaintBorderImageRound(ceiledOffset, canvas);
            break;
        case BorderImageRepeat::REPEAT:
            PaintBorderImageRepeat(ceiledOffset, canvas);
            break;
        default:
            LOGE("Unsupported Border Image repeat mode");
    }
    if (borderImageProperty_.GetBorderImageValue()->GetNeedFillCenter()) {
        FillBorderImageCenter(ceiledOffset, canvas);
    }
    canvas.Restore();
    canvas.DetachPen();
}

void BorderImagePainter::FillBorderImageCenter(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
    double destLeftOffset = offset.GetX() - leftOutset_ + leftWidth_ - EXTRA_OFFSET;
    double destTopOffset = offset.GetY() - topOutset_ + topWidth_ - EXTRA_OFFSET;
    RSRect srcRectCenter =
        RSRect(leftSlice_, topSlice_, leftSlice_ + imageCenterWidth_, topSlice_ + imageCenterHeight_);
    RSRect desRectCenter = RSRect(destLeftOffset, destTopOffset, destLeftOffset + borderCenterWidth_ + EXTRA_OFFSET * 2,
        destTopOffset + borderCenterHeight_ + EXTRA_OFFSET * 2);
    canvas.DrawImageRect(image_, srcRectCenter, desRectCenter, options);
}

void BorderImagePainter::PaintBorderImageCorners(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
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

    // Draw the four corners of the picture to the four corners of the border
    // left top
    RSRect desRectLeftTop =
        RSRect(offsetLeftX, offsetTopY, offsetLeftX + leftWidth_ + EXTRA_OFFSET, offsetTopY + topWidth_ + EXTRA_OFFSET);
    canvas.DrawImageRect(image_, srcRectLeftTop, desRectLeftTop, options);

    // right top
    RSRect desRectRightTop = RSRect(
        offsetRightX - rightWidth_ - EXTRA_OFFSET, offsetTopY, offsetRightX, offsetTopY + topWidth_ + EXTRA_OFFSET);
    canvas.DrawImageRect(image_, srcRectRightTop, desRectRightTop, options);

    // left bottom
    RSRect desRectLeftBottom = RSRect(offsetLeftX, offsetBottomY - bottomWidth_ - EXTRA_OFFSET,
        offsetLeftX + leftWidth_ + EXTRA_OFFSET, offsetBottomY);
    canvas.DrawImageRect(image_, srcRectLeftBottom, desRectLeftBottom, options);

    // right bottom
    RSRect desRectRightBottom = RSRect(offsetRightX - rightWidth_ - EXTRA_OFFSET,
        offsetBottomY - bottomWidth_ - EXTRA_OFFSET, offsetRightX, offsetBottomY);
    canvas.DrawImageRect(image_, srcRectRightBottom, desRectRightBottom, options);
}

void BorderImagePainter::PaintBorderImageStretch(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    RSRect desRectLeft = RSRect(
        offsetLeftX, offsetTopY + topWidth_, offsetLeftX + leftWidth_, offsetTopY + topWidth_ + borderCenterHeight_);
    canvas.DrawImageRect(image_, srcRectLeft_, desRectLeft, options);

    RSRect desRectRight = RSRect(
        offsetRightX - rightWidth_, offsetTopY + topWidth_, offsetRightX, offsetTopY + topWidth_ + borderCenterHeight_);
    canvas.DrawImageRect(image_, srcRectRight_, desRectRight, options);

    RSRect desRectTop = RSRect(offsetLeftX + leftWidth_, offsetTopY,
        offsetLeftX + paintSize_.Width() - rightWidth_ + leftOutset_ + rightOutset_, offsetTopY + topWidth_);
    canvas.DrawImageRect(image_, srcRectTop_, desRectTop, options);

    RSRect desRectBottom = RSRect(offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_,
        offsetLeftX + paintSize_.Width() - rightWidth_ + leftOutset_ + rightOutset_, offsetBottomY);
    canvas.DrawImageRect(image_, srcRectBottom_, desRectBottom, options);
}

void BorderImagePainter::PaintBorderImageRound(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    auto roundHorizontalCount = static_cast<int32_t>(borderCenterWidth_ / imageCenterWidth_);
    auto roundVerticalCount = static_cast<int32_t>(borderCenterHeight_ / imageCenterHeight_);

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
        RSRect desRectTopRound =
            RSRect(roundStartHorizontal, offsetTopY, roundStartHorizontal + roundImageWidth, offsetTopY + topWidth_);
        canvas.DrawImageRect(image_, srcRectTop_, desRectTopRound, options);
        // bottom
        RSRect desRectBottomRound = RSRect(
            roundStartHorizontal, offsetBottomY - bottomWidth_, roundStartHorizontal + roundImageWidth, offsetBottomY);
        canvas.DrawImageRect(image_, srcRectBottom_, desRectBottomRound, options);
        roundStartHorizontal += roundImageWidth;
    }
    double roundStartVertical = offsetTopY + topWidth_;
    // draw shrinked border images on left and right edge
    for (int32_t i = 0; i < roundVerticalCount; i++) {
        // left
        RSRect desRectLeftRound =
            RSRect(offsetLeftX, roundStartVertical, offsetLeftX + leftWidth_, roundStartVertical + roundImageHeight);
        canvas.DrawImageRect(image_, srcRectLeft_, desRectLeftRound, options);
        // right
        RSRect desRectRightRound =
            RSRect(offsetRightX - rightWidth_, roundStartVertical, offsetRightX, roundStartVertical + roundImageHeight);
        canvas.DrawImageRect(image_, srcRectRight_, desRectRightRound, options);
        roundStartVertical += roundImageHeight;
    }
}

void BorderImagePainter::PaintBorderImageSpace(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    if (NearZero(imageCenterWidth_) || NearZero(imageCenterHeight_)) {
        LOGW("Image center width or height is zero.");
        return;
    }

    // calculate maximum count of image pieces can fit in border
    auto roundHorizontalCount = static_cast<int32_t>(borderCenterWidth_ / imageCenterWidth_);
    auto roundVerticalCount = static_cast<int32_t>(borderCenterHeight_ / imageCenterHeight_);
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
        // top
        RSRect desRectTopRound =
            RSRect(roundStartHorizontal, offsetTopY, roundStartHorizontal + imageCenterWidth_, offsetTopY + topWidth_);
        canvas.DrawImageRect(image_, srcRectTop_, desRectTopRound, options);
        // bottom
        RSRect desRectBottomRound = RSRect(roundStartHorizontal, offsetBottomY - bottomWidth_,
            roundStartHorizontal + imageCenterWidth_, offsetBottomY);
        canvas.DrawImageRect(image_, srcRectBottom_, desRectBottomRound, options);

        roundStartHorizontal += imageCenterWidth_ + blankHorizontalSize;
    }

    double roundStartVertical = offsetTopY + topWidth_ + blankVerticalSize;
    for (int32_t i = 0; i < roundVerticalCount; i++) {
        // left
        RSRect desRectLeftRound =
            RSRect(offsetLeftX, roundStartVertical, offsetLeftX + leftWidth_, roundStartVertical + imageCenterHeight_);
        canvas.DrawImageRect(image_, srcRectLeft_, desRectLeftRound, options);
        // right
        RSRect desRectRightRound = RSRect(
            offsetRightX - rightWidth_, roundStartVertical, offsetRightX, roundStartVertical + imageCenterHeight_);
        canvas.DrawImageRect(image_, srcRectRight_, desRectRightRound, options);
        roundStartVertical += imageCenterHeight_ + blankVerticalSize;
    }
}

void BorderImagePainter::PaintBorderImageRepeat(const OffsetF& offset, RSCanvas& canvas) const
{
    RSSamplingOptions options;
    double offsetLeftX = std::ceil(offset.GetX() - leftOutset_);
    double offsetRightX = std::ceil(offset.GetX() + paintSize_.Width() + rightOutset_);
    double offsetTopY = std::ceil(offset.GetY() - topOutset_);
    double offsetBottomY = std::ceil(offset.GetY() + paintSize_.Height() + bottomOutset_);

    double widthFactor = 0.0;
    if (GreatNotEqual(imageCenterWidth_, 0.0)) {
        widthFactor = borderCenterWidth_ / imageCenterWidth_;
        if (GreatNotEqual(widthFactor, 0.0) && LessOrEqual(widthFactor, 1.0)) {
            double halfSurplusImageCenterWidth = (imageCenterWidth_ - borderCenterWidth_) / 2;
            RSRect srcRectTop = RSRect(halfSurplusImageCenterWidth + leftSlice_, 0,
                halfSurplusImageCenterWidth + leftSlice_ + borderCenterWidth_, topSlice_);
            RSRect desRectTop = RSRect(offsetLeftX + leftWidth_, offsetTopY,
                offsetLeftX + leftWidth_ + borderCenterWidth_, offsetTopY + topWidth_);
            canvas.DrawImageRect(image_, srcRectTop, desRectTop, options);

            RSRect srcRectBottom = RSRect(halfSurplusImageCenterWidth + leftSlice_, imageHeight_ - bottomSlice_,
                halfSurplusImageCenterWidth + leftSlice_ + borderCenterWidth_, imageHeight_);
            RSRect desRectBottom =
                RSRect(offsetLeftX + leftWidth_, offset.GetY() + paintSize_.Height() - bottomWidth_ + bottomOutset_,
                    offsetLeftX + leftWidth_ + borderCenterWidth_, offset.GetY() + paintSize_.Height() + bottomOutset_);
            canvas.DrawImageRect(image_, srcRectBottom, desRectBottom, options);
        } else if (GreatNotEqual(widthFactor, 1.0)) {
            double halfSurplusHorizontalLength = 0;
            halfSurplusHorizontalLength = (borderCenterWidth_ - (int)(widthFactor)*imageCenterWidth_) / 2;
            RSRect srcRectTopLeft = RSRect(
                imageWidth_ - rightSlice_ - halfSurplusHorizontalLength, 0, imageWidth_ - rightSlice_, topSlice_);
            RSRect desRectTopLeftEnd = RSRect(offsetLeftX + leftWidth_, offsetTopY,
                offsetLeftX + leftWidth_ + halfSurplusHorizontalLength, offsetTopY + topWidth_);
            canvas.DrawImageRect(image_, srcRectTopLeft, desRectTopLeftEnd, options);

            RSRect srcRectTopRight = RSRect(leftSlice_, 0, leftSlice_ + halfSurplusHorizontalLength, topSlice_);
            RSRect desRectTopRightEnd =
                RSRect(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength, offsetTopY,
                    offsetLeftX + leftWidth_ + borderCenterWidth_, offsetTopY + topWidth_);
            canvas.DrawImageRect(image_, srcRectTopRight, desRectTopRightEnd, options);

            RSRect srcRectBottomLeft = RSRect(imageWidth_ - rightSlice_ - halfSurplusHorizontalLength,
                imageHeight_ - bottomSlice_, imageWidth_ - rightSlice_, imageHeight_);
            RSRect desRectBottomLeftEnd = RSRect(offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_,
                offsetLeftX + leftWidth_ + halfSurplusHorizontalLength, offsetBottomY);
            canvas.DrawImageRect(image_, srcRectBottomLeft, desRectBottomLeftEnd, options);

            RSRect srcRectBottomRight =
                RSRect(leftSlice_, imageHeight_ - bottomSlice_, leftSlice_ + halfSurplusHorizontalLength, imageHeight_);
            RSRect desRectBottomRightEnd =
                RSRect(offsetLeftX + leftWidth_ + borderCenterWidth_ - halfSurplusHorizontalLength,
                    offsetBottomY - bottomWidth_, offsetLeftX + leftWidth_ + borderCenterWidth_, offsetBottomY);
            canvas.DrawImageRect(image_, srcRectBottomRight, desRectBottomRightEnd, options);

            double repeatHorizontalStart = offsetLeftX + leftWidth_ + halfSurplusHorizontalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(widthFactor); i++) {
                // top
                RSRect desRectTopRepeat = RSRect(repeatHorizontalStart, offsetTopY,
                    repeatHorizontalStart + imageCenterWidth_, offsetTopY + topWidth_);
                canvas.DrawImageRect(image_, srcRectTop_, desRectTopRepeat, options);

                // bottom
                RSRect desRectBottomRepeat = RSRect(repeatHorizontalStart, offsetBottomY - bottomWidth_,
                    repeatHorizontalStart + imageCenterWidth_, offsetBottomY);
                canvas.DrawImageRect(image_, srcRectBottom_, desRectBottomRepeat, options);

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
                topSlice_ + halfSurplusImageCenterHeight + borderCenterHeight_);
            RSRect desRectLeft =
                RSRect(offsetLeftX, destTopOffsetY, offsetLeftX + leftWidth_, destTopOffsetY + borderCenterHeight_);
            canvas.DrawImageRect(image_, srcRectLeft, desRectLeft, options);

            RSRect srcRectRight = RSRect(imageWidth_ - rightSlice_, topSlice_ + halfSurplusImageCenterHeight,
                imageWidth_, topSlice_ + halfSurplusImageCenterHeight + borderCenterHeight_);
            RSRect desRectRight =
                RSRect(offset.GetX() + paintSize_.Width() - rightWidth_ + rightOutset_, destTopOffsetY,
                    offset.GetX() + paintSize_.Width() + rightOutset_, destTopOffsetY + borderCenterHeight_);
            canvas.DrawImageRect(image_, srcRectRight, desRectRight, options);
        } else if (GreatNotEqual(heightFactor, 1.0)) {
            double halfSurplusVerticalLength = 0;
            halfSurplusVerticalLength = (borderCenterHeight_ - (int)(heightFactor)*imageCenterHeight_) / 2;
            RSRect srcRectLeftTop = RSRect(
                0, imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, leftSlice_, imageHeight_ - bottomSlice_);
            RSRect desRectLeftTopStart = RSRect(
                offsetLeftX, destTopOffsetY, offsetLeftX + leftWidth_, destTopOffsetY + halfSurplusVerticalLength);
            canvas.DrawImageRect(image_, srcRectLeftTop, desRectLeftTopStart, options);

            RSRect srcRectRightTop = RSRect(imageWidth_ - rightSlice_,
                imageHeight_ - bottomSlice_ - halfSurplusVerticalLength, imageWidth_, imageHeight_ - bottomSlice_);
            RSRect desRectRightTopStart = RSRect(
                offsetRightX - rightWidth_, destTopOffsetY, offsetRightX, destTopOffsetY + halfSurplusVerticalLength);
            canvas.DrawImageRect(image_, srcRectRightTop, desRectRightTopStart, options);

            RSRect srcRectLeftBottom = RSRect(0, topSlice_, leftSlice_, topSlice_ + halfSurplusVerticalLength);
            RSRect desRectLeftBottomEnd = RSRect(offsetLeftX, offsetBottomY - bottomWidth_ - halfSurplusVerticalLength,
                offsetLeftX + leftWidth_, offsetBottomY - bottomWidth_);
            canvas.DrawImageRect(image_, srcRectLeftBottom, desRectLeftBottomEnd, options);

            RSRect srcRectRightBottom =
                RSRect(imageWidth_ - rightSlice_, topSlice_, imageWidth_, topSlice_ + halfSurplusVerticalLength);
            RSRect desRectRightBottomEnd = RSRect(offsetRightX - rightWidth_,
                offsetBottomY - bottomWidth_ - halfSurplusVerticalLength, offsetRightX, offsetBottomY - bottomWidth_);
            canvas.DrawImageRect(image_, srcRectRightBottom, desRectRightBottomEnd, options);

            double repeatVerticalStart = destTopOffsetY + halfSurplusVerticalLength;
            for (int32_t i = 0; i < static_cast<int32_t>(heightFactor); i++) {
                // left
                RSRect desRectLeftRepeat = RSRect(offsetLeftX, repeatVerticalStart, offsetLeftX + leftWidth_,
                    repeatVerticalStart + imageCenterHeight_);
                canvas.DrawImageRect(image_, srcRectLeft_, desRectLeftRepeat, options);

                // right
                RSRect desRectRightRepeat = RSRect(offsetRightX - rightWidth_, repeatVerticalStart, offsetRightX,
                    repeatVerticalStart + imageCenterHeight_);
                canvas.DrawImageRect(image_, srcRectRight_, desRectRightRepeat, options);

                repeatVerticalStart += imageCenterHeight_;
            }
        }
    }
}

void BorderImagePainter::ParseNegativeNumberToZeroOrCeil(double& value)
{
    if (LessNotEqual(value, 0.0)) {
        value = 0.0;
    }
    value = std::ceil(value);
}
} // namespace OHOS::Ace::NG
