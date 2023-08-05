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

namespace OHOS::Ace::NG {
void ImagePainter::DrawImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const {}

void ImagePainter::DrawSVGImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& svgContainerSize) const {}

void ImagePainter::DrawStaticImage(RSCanvas& canvas, const OffsetF& offset, const SizeF& contentSize) const {}

void ImagePainter::FlipHorizontal(RSCanvas& canvas, const SizeF& contentSize) {}

void ImagePainter::DrawImageWithRepeat(RSCanvas& canvas, const RectF& contentRect) const {}

void ImagePainter::ApplyImageFit(
    ImageFit imageFit, const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{}

OffsetF ImagePainter::CalculateBgImagePosition(const SizeF& boxPaintSize_, const SizeF& imageRenderSize_,
    const std::optional<BackgroundImagePosition>& bgImgPositionOpt)
{
    return { 0.0f, 0.0f };
}

SizeF ImagePainter::CalculateBgImageSize(
    const SizeF& boxPaintSize_, const SizeF& srcSize, const std::optional<BackgroundImageSize>& bgImageSizeOpt)
{
    return { 0.0f, 0.0f };
}
} // namespace OHOS::Ace::NG
