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

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {

static void ApplyContain(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
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

static void ApplyCover(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(dstSize * (rawPicSize.Height() / dstSize.Height()));
    } else {
        srcRect.SetSize(dstSize * (rawPicSize.Width() / dstSize.Width()));
    }
    srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
}

static void ApplyFitWidth(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        dstRect.SetSize(rawPicSize * (dstSize.Width() / rawPicSize.Width()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), Alignment::CENTER));
    } else {
        srcRect.SetSize(dstSize * (rawPicSize.Width() / dstSize.Width()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
    }
}

static void ApplyFitHeight(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    if (Size::CalcRatio(srcRect) > Size::CalcRatio(dstRect)) {
        srcRect.SetSize(dstSize * (rawPicSize.Height() / dstSize.Height()));
        srcRect.SetOffset(Alignment::GetAlignPosition(rawPicSize, srcRect.GetSize(), Alignment::CENTER));
    } else {
        dstRect.SetSize(rawPicSize * (dstSize.Height() / rawPicSize.Height()));
        dstRect.SetOffset(Alignment::GetAlignPosition(dstSize, dstRect.GetSize(), Alignment::CENTER));
    }
}

static void ApplyNone(const SizeF& rawPicSize, const SizeF& dstSize, RectF& srcRect, RectF& dstRect)
{
    SizeF srcSize(std::min(dstSize.Width(), rawPicSize.Width()), std::min(dstSize.Height(), rawPicSize.Height()));
    dstRect.SetRect(Alignment::GetAlignPosition(dstSize, srcSize, Alignment::CENTER), srcSize);
    srcRect.SetRect(Alignment::GetAlignPosition(rawPicSize, srcSize, Alignment::CENTER), srcSize);
}

}

void ImagePainter::DrawImage(
    const RefPtr<Canvas>& canvas, const OffsetF& offset, const ImagePaintConfig& ImagePaintConfig) const
{
    CHECK_NULL_VOID(canvasImage_);
    auto paint = Paint::Create();
    paint->SetFilterQuality(FilterQuality::NONE); // TODO: add interpolation, etc
    canvas->DrawImage(canvasImage_, ImagePaintConfig.srcRect_, ImagePaintConfig.dstRect_, paint);
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
            ApplyContain(rawPicSize, dstSize, srcRect, dstRect);
            break;
        default:
            ApplyContain(rawPicSize, dstSize, srcRect, dstRect);
            break;
    }
    srcRect.ApplyScale(viewScale);
}

} // namespace OHOS::Ace::NG
