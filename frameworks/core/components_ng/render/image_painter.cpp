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

#include "core/components_ng/render/image_painter.h"

#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/svg_canvas_image.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {

void ApplyContain(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (rawPicSize.IsNonPositive()) {
        return;
    }
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        dstRect.SetSize(rawPicSize * (dstSize.Width() / rawPicSize.Width()));
    } else {
        dstRect.SetSize(rawPicSize * (dstSize.Height() / rawPicSize.Height()));
    }
    dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), Alignment::CENTER));
}

void ApplyCover(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(dstSize * (rawPicSize.Height() / dstSize.Height()));
    } else {
        srcRect.SetSize(dstSize * (rawPicSize.Width() / dstSize.Width()));
    }
    srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
}

void ApplyFitWidth(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        dstRect.SetSize(rawPicSize * (dstSize.Width() / rawPicSize.Width()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), Alignment::CENTER));
    } else {
        srcRect.SetSize(dstSize * (rawPicSize.Width() / dstSize.Width()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
    }
}

void ApplyFitHeight(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(dstSize * (rawPicSize.Height() / dstSize.Height()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
    } else {
        dstRect.SetSize(rawPicSize * (dstSize.Height() / rawPicSize.Height()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), Alignment::CENTER));
    }
}

void ApplyNone(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    SizeF srcSize(std::min(dstSize.Width(), rawPicSize.Width()), std::min(dstSize.Height(), rawPicSize.Height()));
    dstRect.SetRect(Alignment::GetAlignPosition(dstSize, srcSize, Alignment::CENTER), srcSize);
    srcRect.SetRect(Alignment::GetAlignPosition(rawPicSize, srcSize, Alignment::CENTER), srcSize);
}

// The [GRAY_COLOR_MATRIX] is of dimension [4 x 5], which transforms a RGB source color (R, G, B, A) to the
// destination color (R', G', B', A').
//
// A classic color image to grayscale conversion formula is [Gray = R * 0.3 + G * 0.59 + B * 0.11].
// Hence we get the following conversion:
//
// | M11 M12 M13 M14 M15 |   | R |   | R' |
// | M21 M22 M23 M24 M25 |   | G |   | G' |
// | M31 M32 M33 M34 M35 | x | B | = | B' |
// | M41 M42 M43 M44 M45 |   | A |   | A' |
//                           | 1 |
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency
} // namespace

void ImagePainter::DrawImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const
{
    CHECK_NULL_VOID(canvasImage_);
    const auto config = canvasImage_->GetPaintConfig();
    if (config.isSvg_) {
        DrawSVGImage(canvas, offset, contentSize);
    } else if (config.imageRepeat_ == ImageRepeat::NO_REPEAT) {
        DrawStaticImage(canvas, offset);
    } else {
        RectF rect(offset.GetX(), offset.GetY(), contentSize.Width(), contentSize.Height());
        DrawImageWithRepeat(canvas, rect);
    }
}

void ImagePainter::DrawSVGImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& svgContainerSize) const
{
    CHECK_NULL_VOID(canvasImage_);
    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());
    const auto config = canvasImage_->GetPaintConfig();
    if (config.needFlipCanvasHorizontally_) {
        ImagePainter::FlipHorizontal(canvas, offset.GetX(), config.dstRect_.Width());
    }

    RectF srcRect;
    srcRect.SetSize(svgContainerSize);
    canvasImage_->DrawToRSCanvas(canvas, ToRSRect(srcRect), ToRSRect(config.dstRect_), BorderRadiusArray());
    canvas.Restore();
}

void ImagePainter::DrawStaticImage(RSCanvas& canvas, const OffsetF& offset) const
{
    CHECK_NULL_VOID(canvasImage_);
    RSBrush brush;
    RSFilter filter;
    const auto config = canvasImage_->GetPaintConfig();
    filter.SetFilterQuality(RSFilter::FilterQuality(config.imageInterpolation_));
    // note that [colorFilter] has higher priority to [renderMode], because the [ImageRenderMode::TEMPLATE] is actually
    // a special value of colorFilter
    if (ImageRenderMode::TEMPLATE == config.renderMode_ || config.colorFilter_) {
        RSColorMatrix colorFilterMatrix;
        if (config.colorFilter_) {
            colorFilterMatrix.SetArray(config.colorFilter_->data());
        } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
            colorFilterMatrix.SetArray(GRAY_COLOR_MATRIX);
        }
        filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(colorFilterMatrix));
    }
    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());

    if (config.needFlipCanvasHorizontally_) {
        ImagePainter::FlipHorizontal(canvas, offset.GetX(), config.dstRect_.Width());
    }

    brush.SetFilter(filter);
    canvas.AttachBrush(brush);
    // include recordingCanvas's ClipAdaptiveRRect operation.
    canvasImage_->DrawToRSCanvas(canvas, ToRSRect(config.srcRect_), ToRSRect(config.dstRect_),
        config.borderRadiusXY_ ? *config.borderRadiusXY_ : BorderRadiusArray());
    canvas.Restore();
}

void ImagePainter::FlipHorizontal(RSCanvas& canvas, double horizontalOffset, double drawRectWidth)
{
    double horizontalMoveDelta = -1.0 * (horizontalOffset + drawRectWidth / 2.0);
    canvas.Translate(-1.0 * horizontalMoveDelta, 0.0);
    canvas.Scale(-1.0, 1.0);
    canvas.Translate(horizontalMoveDelta, 0.0);
}

void ImagePainter::DrawImageWithRepeat(RSCanvas& canvas, const RectF& contentRect) const
{
    auto config = canvasImage_->GetPaintConfig();
    if (config.imageRepeat_ == ImageRepeat::NO_REPEAT) {
        return;
    }
    auto offset = contentRect.GetOffset();
    float contentWidth = contentRect.Width();
    float contentHeight = contentRect.Height();
    float singleImageWidth = config.dstRect_.Width();
    float singleImageHeight = config.dstRect_.Height();
    if (NearZero(singleImageWidth) || NearZero(singleImageHeight)) {
        return;
    }

    bool imageRepeatX = config.imageRepeat_ == ImageRepeat::REPEAT || config.imageRepeat_ == ImageRepeat::REPEAT_X;
    bool imageRepeatY = config.imageRepeat_ == ImageRepeat::REPEAT || config.imageRepeat_ == ImageRepeat::REPEAT_Y;
    std::vector<uint32_t> dirRepeatNum = { static_cast<uint32_t>(ceil(config.dstRect_.GetY() / singleImageHeight)),
        static_cast<uint32_t>((ceil((contentHeight - config.dstRect_.GetY()) / singleImageHeight))) - 1,
        static_cast<uint32_t>(ceil(config.dstRect_.GetX() / singleImageWidth)),
        imageRepeatX ? static_cast<uint32_t>(ceil((contentWidth - config.dstRect_.GetX()) / singleImageWidth)) : 1 };

    canvas.Save();
    auto clipRect = RSRect(offset.GetX(), offset.GetY(), static_cast<float>(offset.GetX() + contentWidth),
        static_cast<float>(offset.GetY() + contentHeight));
    canvas.ClipRect(clipRect, OHOS::Rosen::Drawing::ClipOp::INTERSECT);
    uint32_t up = 0;
    uint32_t down = 1;
    uint32_t left = 2;
    uint32_t right = 3;
    auto drawRepeatYTask = [this, &canvas, &config, &dirRepeatNum, &singleImageHeight, &imageRepeatY](
                               OffsetF offsetTempY, uint32_t dir) {
        float downNum = (dir == 0) ? -1 : 1;
        for (size_t j = 0; j < dirRepeatNum[dir] && imageRepeatY; j++) {
            offsetTempY.SetY(static_cast<float>(offsetTempY.GetY() + singleImageHeight * downNum));
            DrawStaticImage(canvas, offsetTempY);
        }
    };
    auto offsetTempX = offset;
    // right
    for (size_t i = 0; i < dirRepeatNum[right]; i++) {
        DrawStaticImage(canvas, offsetTempX);
        drawRepeatYTask(offsetTempX, up);
        drawRepeatYTask(offsetTempX, down);
        offsetTempX.SetX(static_cast<float>(offsetTempX.GetX() + singleImageWidth));
    }
    // left
    offsetTempX = offset;
    for (size_t i = 0; i < dirRepeatNum[left] && imageRepeatX; i++) {
        offsetTempX.SetX(static_cast<float>(offsetTempX.GetX() - singleImageWidth));
        DrawStaticImage(canvas, offsetTempX);
        drawRepeatYTask(offsetTempX, up);
        drawRepeatYTask(offsetTempX, down);
    }
    canvas.Restore();
    // TODO: repeat refactory
}

void ImagePainter::ApplyImageFit(
    ImageFit imageFit, const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    auto context = PipelineContext::GetCurrentContext();
    float viewScale = context ? context->GetViewScale() : 1.0;
    srcRect.SetOffset(OffsetF());
    srcRect.SetSize(rawPicSize);
    srcRect.ApplyScale(1.0 / viewScale);
    dstRect.SetOffset(OffsetF());
    dstRect.SetSize(dstSize);
    switch (imageFit) {
        case ImageFit::FILL:
            break;
        case ImageFit::NONE:
            ApplyNone(rawPicSize, dstSize, srcRect, dstRect);
            break;
        case ImageFit::COVER:
            ApplyCover(rawPicSize, dstSize, srcRect, dstRect);
            break;
        case ImageFit::FITWIDTH:
            ApplyFitWidth(rawPicSize, dstSize, srcRect, dstRect);
            break;
        case ImageFit::FITHEIGHT:
            ApplyFitHeight(rawPicSize, dstSize, srcRect, dstRect);
            break;
        case ImageFit::SCALE_DOWN:
            if (srcRect.GetSize() < dstRect.GetSize()) {
                ApplyNone(rawPicSize, dstSize, srcRect, dstRect);
            } else {
                ApplyContain(rawPicSize, dstSize, srcRect, dstRect);
            }
            break;
        case ImageFit::CONTAIN:
        default:
            ApplyContain(rawPicSize, dstSize, srcRect, dstRect);
            break;
    }
    srcRect.ApplyScale(viewScale);
}

OffsetF ImagePainter::CalculateBgImagePosition(const SizeF& boxPaintSize_, const SizeF& imageRenderSize_,
    const std::optional<BackgroundImagePosition>& bgImgPositionOpt)
{
    OffsetF offset(.0, .0);
    if (bgImgPositionOpt == std::nullopt) {
        return offset;
    }
    const auto& bgImgPosition = bgImgPositionOpt.value();
    if (bgImgPosition.GetSizeTypeX() == BackgroundImagePositionType::PX) {
        offset.SetX(bgImgPosition.GetSizeValueX());
    } else {
        offset.SetX(
            bgImgPosition.GetSizeValueX() * (boxPaintSize_.Width() - imageRenderSize_.Width()) / PERCENT_TRANSLATE);
    }

    if (bgImgPosition.GetSizeTypeY() == BackgroundImagePositionType::PX) {
        offset.SetY(bgImgPosition.GetSizeValueY());
    } else {
        offset.SetY(
            bgImgPosition.GetSizeValueY() * (boxPaintSize_.Height() - imageRenderSize_.Height()) / PERCENT_TRANSLATE);
    }
    return offset;
}

namespace {
float CalculateBgWidth(const SizeF& boxPaintSize_, const SizeF& srcSize, const BackgroundImageSize& bgImageSize)
{
    float width = 0.0f;
    float paintAspectRatio = boxPaintSize_.Width() / boxPaintSize_.Height();
    float srcAspectRatio = srcSize.Width() / srcSize.Height();
    auto bgImageSizeTypeX = bgImageSize.GetSizeTypeX();
    switch (bgImageSizeTypeX) {
        case BackgroundImageSizeType::COVER:
            width = paintAspectRatio >= srcAspectRatio ? boxPaintSize_.Width()
                                                       : srcSize.Width() * (boxPaintSize_.Height() / srcSize.Height());
            break;
        case BackgroundImageSizeType::CONTAIN:
            width = paintAspectRatio >= srcAspectRatio ? srcSize.Width() * (boxPaintSize_.Height() / srcSize.Height())
                                                       : boxPaintSize_.Width();
            break;
        case BackgroundImageSizeType::LENGTH:
            width = bgImageSize.GetSizeValueX();
            break;
        case BackgroundImageSizeType::PERCENT:
            width = boxPaintSize_.Width() * bgImageSize.GetSizeValueX() / PERCENT_TRANSLATE;
            break;
        default:
            break;
    }
    return width;
}

float CalculateBgHeight(const SizeF& boxPaintSize_, const SizeF& srcSize, const BackgroundImageSize& bgImageSize)
{
    float height = 0.0f;
    float paintAspectRatio = boxPaintSize_.Width() / boxPaintSize_.Height();
    float srcAspectRatio = srcSize.Width() / srcSize.Height();
    auto bgImageSizeTypeY = bgImageSize.GetSizeTypeY();
    switch (bgImageSizeTypeY) {
        case BackgroundImageSizeType::COVER:
            height = paintAspectRatio >= srcAspectRatio ? srcSize.Height() * (boxPaintSize_.Width() / srcSize.Width())
                                                        : boxPaintSize_.Height();
            break;
        case BackgroundImageSizeType::CONTAIN:
            height = paintAspectRatio >= srcAspectRatio ? boxPaintSize_.Height()
                                                        : srcSize.Height() * (boxPaintSize_.Width() / srcSize.Width());
            break;
        case BackgroundImageSizeType::LENGTH:
            height = bgImageSize.GetSizeValueY();
            break;
        case BackgroundImageSizeType::PERCENT:
            height = boxPaintSize_.Height() * bgImageSize.GetSizeValueY() / PERCENT_TRANSLATE;
            break;
        default:
            break;
    }
    return height;
}
} // namespace

SizeF ImagePainter::CalculateBgImageSize(
    const SizeF& boxPaintSize_, const SizeF& srcSize, const std::optional<BackgroundImageSize>& bgImageSizeOpt)
{
    SizeF sizeRet(srcSize.Width(), srcSize.Height());
    if (bgImageSizeOpt == std::nullopt || NearZero(srcSize.Width()) || NearZero(srcSize.Height()) ||
        NearZero(boxPaintSize_.Width()) || NearZero(boxPaintSize_.Height())) {
        return sizeRet;
    }
    auto bgImageSize = bgImageSizeOpt.value();
    float renderSizeX = CalculateBgWidth(boxPaintSize_, srcSize, bgImageSize);
    float renderSizeY = CalculateBgHeight(boxPaintSize_, srcSize, bgImageSize);

    if (bgImageSize.GetSizeTypeX() == BackgroundImageSizeType::AUTO &&
        bgImageSize.GetSizeTypeY() == BackgroundImageSizeType::AUTO) {
        renderSizeX = srcSize.Width();
        renderSizeY = srcSize.Height();
    } else if (bgImageSize.GetSizeTypeX() == BackgroundImageSizeType::AUTO) {
        renderSizeX = srcSize.Width() * (renderSizeY / srcSize.Height());
    } else if (bgImageSize.GetSizeTypeY() == BackgroundImageSizeType::AUTO) {
        renderSizeY = srcSize.Height() * (renderSizeX / srcSize.Width());
    }
    // fit image ratio if width or height is not set
    float srcRatio = srcSize.Width() / srcSize.Height();
    CHECK_NULL_RETURN(srcRatio > 0, sizeRet);
    if (renderSizeX <= 0) {
        renderSizeX = renderSizeY * srcRatio;
    } else if (renderSizeY <= 0) {
        renderSizeY = renderSizeX / srcRatio;
    }
    sizeRet.SetWidth(renderSizeX);
    sizeRet.SetHeight(renderSizeY);
    return sizeRet;
}

} // namespace OHOS::Ace::NG
