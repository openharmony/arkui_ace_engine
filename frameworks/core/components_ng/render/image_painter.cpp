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

namespace OHOS::Ace::NG {

namespace {

void ApplyContain(
    const SizeF& imageSize, const SizeF& dstSize, const Alignment& alignment, RectF& srcRect, RectF& dstRect)
{
    if (imageSize.IsNonPositive()) {
        return;
    }
    if (imageSize.CalcRatio() > dstSize.CalcRatio()) {
        dstRect.SetSize(imageSize * (dstSize.Width() / imageSize.Width()));
    } else {
        dstRect.SetSize(imageSize * (dstSize.Height() / imageSize.Height()));
    }
    dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), alignment));
}

void ApplyCover(
    const SizeF& imageSize, const SizeF& dstSize, const Alignment& alignment, RectF& srcRect, RectF& dstRect)
{
    if (imageSize.CalcRatio() > dstSize.CalcRatio()) {
        srcRect.SetSize(dstSize * (imageSize.Height() / dstSize.Height()));
    } else {
        srcRect.SetSize(dstSize * (imageSize.Width() / dstSize.Width()));
    }
    srcRect.SetOffset(Alignment::GetAlignPosition(imageSize, srcRect.GetSize(), alignment));
}

void ApplyFitWidth(
    const SizeF& imageSize, const SizeF& dstSize, const Alignment& alignment, RectF& srcRect, RectF& dstRect)
{
    if (imageSize.CalcRatio() > dstSize.CalcRatio()) {
        dstRect.SetSize(imageSize * (dstSize.Width() / imageSize.Width()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), alignment));
    } else {
        srcRect.SetSize(dstSize * (imageSize.Width() / dstSize.Width()));
        srcRect.SetOffset(Alignment::GetAlignPosition(imageSize, srcRect.GetSize(), alignment));
    }
}

void ApplyFitHeight(
    const SizeF& imageSize, const SizeF& dstSize, const Alignment& alignment, RectF& srcRect, RectF& dstRect)
{
    if (imageSize.CalcRatio() > dstSize.CalcRatio()) {
        srcRect.SetSize(dstSize * (imageSize.Height() / dstSize.Height()));
        srcRect.SetOffset(Alignment::GetAlignPosition(imageSize, srcRect.GetSize(), alignment));
    } else {
        dstRect.SetSize(imageSize * (dstSize.Height() / imageSize.Height()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), alignment));
    }
}

void ApplyNone(const SizeF& imageSize, const SizeF& dstSize, const Alignment& alignment, RectF& srcRect, RectF& dstRect)
{
    SizeF srcSize = SizeF(std::min(dstSize.Width(), imageSize.Width()), std::min(dstSize.Height(), imageSize.Height()));
    dstRect.SetRect(Alignment::GetAlignPosition(dstSize, srcSize, alignment), srcSize);
    srcRect.SetRect(Alignment::GetAlignPosition(imageSize, srcSize, alignment), srcSize);
}

void ApplyImageFit(const SizeF& imageSize, const SizeF& dstSize, ImageFit imageFit, const Alignment& alignment,
    RectF& srcRect, RectF& dstRect)
{
    switch (imageFit) {
        case ImageFit::FILL:
            break;
        case ImageFit::NONE:
            ApplyNone(imageSize, dstSize, alignment, srcRect, dstRect);
            break;
        case ImageFit::COVER:
            ApplyCover(imageSize, dstSize, alignment, srcRect, dstRect);
            break;
        case ImageFit::FITWIDTH:
            ApplyFitWidth(imageSize, dstSize, alignment, srcRect, dstRect);
            break;
        case ImageFit::FITHEIGHT:
            ApplyFitHeight(imageSize, dstSize, alignment, srcRect, dstRect);
            break;
        case ImageFit::SCALEDOWN:
            if (imageSize < dstSize) {
                ApplyNone(imageSize, dstSize, alignment, srcRect, dstRect);
            } else {
                ApplyContain(imageSize, dstSize, alignment, srcRect, dstRect);
            }
            break;
        case ImageFit::CONTAIN:
        default:
            ApplyContain(imageSize, dstSize, alignment, srcRect, dstRect);
            break;
    }
}

} // namespace

void ImagePainter::DrawImage(const RefPtr<Canvas>& canvas, const OffsetF& offset) const
{
    CHECK_NULL_VOID(image_);
    RectF srcRect = RectF(OffsetF(), imageSize_);
    RectF dstRect = RectF(OffsetF(), dstSize_);
    ApplyImageFit(imageSize_, dstSize_, imageFit_, alignment_, srcRect, dstRect);
    dstRect = dstRect + offset;
    auto paint = Paint::Create();
    paint->SetFilterQuality(FilterQuality::NONE);
    canvas->DrawImage(image_, srcRect, dstRect, paint);
}

} // namespace OHOS::Ace::NG
