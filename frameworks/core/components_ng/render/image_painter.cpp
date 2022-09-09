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

#include "core/components_ng/render/image_painter.h"

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
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0,    0,  // red
                                      0.30f, 0.59f, 0.11f, 0,    0,  // green
                                      0.30f, 0.59f, 0.11f, 0,    0,  // blue
                                      0,     0,     0,     1.0f, 0}; // alpha transparency
} // namespace

void ImagePainter::DrawImage(RSCanvas& canvas, const OffsetF& offset, const ImagePaintConfig& imagePaintConfig) const
{
    CHECK_NULL_VOID(canvasImage_);
    RSBrush brush;
    RSFilter filter;
    filter.SetFilterQuality(RSFilter::FilterQuality(imagePaintConfig.imageInterpolation_));
    if (ImageRenderMode::TEMPLATE == imagePaintConfig.renderMode_) {
        RSColorMatrix grayMatrix;
        grayMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSColorFilter::CreateMatrixColorFilter(grayMatrix));
    }
    canvas.Save();
    canvas.Translate(offset.GetX(), offset.GetY());
    brush.SetFilter(filter);
    canvas.AttachBrush(brush);
    canvasImage_->DrawToRSCanvas(canvas, ToRSRect(imagePaintConfig.srcRect_), ToRSRect(imagePaintConfig.dstRect_));
    canvas.Restore();
}

void ImagePainter::DrawImageWithRepeat(
    RSCanvas& canvas, const ImagePaintConfig& imagePaintConfig, const RectF& contentRect) const
{
    if (imagePaintConfig.imageRepeat_ == ImageRepeat::NOREPEAT) {
        return;
    }
    auto offset = contentRect.GetOffset();
    float contentWidth = contentRect.Width();
    float contentHeight = contentRect.Height();
    float singleImageWidth = imagePaintConfig.dstRect_.Width();
    float singleImageHeight = imagePaintConfig.dstRect_.Height();
    bool imageRepeatX =
        imagePaintConfig.imageRepeat_ == ImageRepeat::REPEAT || imagePaintConfig.imageRepeat_ == ImageRepeat::REPEATX;
    bool imageRepeatY =
        imagePaintConfig.imageRepeat_ == ImageRepeat::REPEAT || imagePaintConfig.imageRepeat_ == ImageRepeat::REPEATY;
    std::vector<uint32_t> dirRepeatNum = {
        static_cast<uint32_t>(ceil(imagePaintConfig.dstRect_.GetY() / singleImageHeight)),
        static_cast<uint32_t>((ceil((contentHeight - imagePaintConfig.dstRect_.GetY()) / singleImageHeight))) - 1,
        static_cast<uint32_t>(ceil(imagePaintConfig.dstRect_.GetX() / singleImageWidth)),
        imageRepeatX ? static_cast<uint32_t>(ceil((contentWidth - imagePaintConfig.dstRect_.GetX()) / singleImageWidth))
                     : 1 };

    canvas.Save();
    auto clipRect = RSRect(offset.GetX(), offset.GetY(),
        static_cast<float>(offset.GetX() + contentWidth),
        static_cast<float>(offset.GetY() + contentHeight));
    canvas.ClipRect(clipRect, OHOS::Rosen::Drawing::ClipOp::INTERSECT);
    uint32_t up = 0;
    uint32_t down = 1;
    uint32_t left = 2;
    uint32_t right = 3;
    auto DrawRepeatYTask = [this, &canvas, &imagePaintConfig, &dirRepeatNum, &singleImageHeight, &imageRepeatY](
                               OffsetF offsetTempY, uint32_t dir) {
        float downNum = (dir == 0) ? -1 : 1;
        for (size_t j = 0; j < dirRepeatNum[dir] && imageRepeatY; j++) {
            offsetTempY.SetY(static_cast<float>(offsetTempY.GetY() + singleImageHeight * downNum));
            DrawImage(canvas, offsetTempY, imagePaintConfig);
        }
    };
    auto offsetTempX = offset;
    // right
    for (size_t i = 0; i < dirRepeatNum[right]; i++) {
        DrawImage(canvas, offsetTempX, imagePaintConfig);
        DrawRepeatYTask(offsetTempX, up);
        DrawRepeatYTask(offsetTempX, down);
        offsetTempX.SetX(static_cast<float>(offsetTempX.GetX() + singleImageWidth));
    }
    // left
    offsetTempX = offset;
    for (size_t i = 0; i < dirRepeatNum[left] && imageRepeatX; i++) {
        offsetTempX.SetX(static_cast<float>(offsetTempX.GetX() - singleImageWidth));
        DrawImage(canvas, offsetTempX, imagePaintConfig);
        DrawRepeatYTask(offsetTempX, up);
        DrawRepeatYTask(offsetTempX, down);
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
        case ImageFit::SCALEDOWN:
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

} // namespace OHOS::Ace::NG
