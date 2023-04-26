/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/image/image_modifier.h"

namespace OHOS::Ace::NG {
ImageModifier::ImageModifier()
{
    imageFit_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f);
    AttachProperty(imageFit_);
}

void ImageModifier::onDraw(DrawingContext& context)
{
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    if (isFirst_) {
        DrawImageWithoutAnimation(context);
        isFirst_ = false;
    } else {
        auto&& config = canvas->GetPaintConfig();
        if (config.isSvg_) {
            DrawImageWithoutAnimation(context);
        } else {
            DrawImageWithAnimation(context);
        }
    }
}

void ImageModifier::SetImageFit(ImageFit imagefit)
{
    if (imagefit != endImageFit_) {
        startImageFit_ = endImageFit_;
        endImageFit_ = imagefit;
    } else {
        imageFit_->Set(static_cast<float>(startImageFit_));
    }
    imageFit_->Set(static_cast<float>(imagefit));
}

void ImageModifier::UpdateImageData(WeakPtr<CanvasImage>& canvasImage, OffsetF offset, SizeF contentSize)
{
    canvasImage_ = canvasImage;
    offset_ = offset;
    contentSize_ = contentSize;
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    auto&& config = canvas->GetPaintConfig();
    // update srcRect
    startSrcRect_ = endSrcRect_;
    endSrcRect_ = config.srcRect_;
    // update dstRect
    startDstRect_ = endDstRect_;
    endDstRect_ = config.dstRect_;
}

void ImageModifier::DrawImageWithAnimation(DrawingContext& context)
{
    RSCanvas rsCanvas = context.canvas;
    float difference = static_cast<float>(endImageFit_) - static_cast<float>(startImageFit_);
    float ratio = 1.0f;
    if (!NearZero(difference)) {
        // ratio goes from 0 to 1
        ratio = abs((imageFit_->Get() - static_cast<float>(startImageFit_)) / difference);
    }
    UpdatePaintConfig(ratio);
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    constexpr double epsilon = 0.00001f;
    if (NearEqual(ANIMATION_END, ratio, epsilon)) {
        canvas->SetIsDrawAnimate(false);
    } else {
        canvas->SetIsDrawAnimate(true);
    }
    ImagePainter imagePainter(canvas);
    imagePainter.DrawImage(rsCanvas, offset_, contentSize_);
}

void ImageModifier::DrawImageWithoutAnimation(DrawingContext& context)
{
    RSCanvas rsCanvas = context.canvas;
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    ImagePainter imagePainter(canvas);
    imagePainter.DrawImage(rsCanvas, offset_, contentSize_);
}

void ImageModifier::UpdatePaintConfig(float ratio)
{
    // use ratio to calculate new dstRect and srcRect
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    auto&& config = canvas->GetPaintConfig();
    // calculate new dstRect
    auto x = startDstRect_.GetX() + (endDstRect_.GetX() - startDstRect_.GetX()) * ratio;
    auto y = startDstRect_.GetY() + (endDstRect_.GetY() - startDstRect_.GetY()) * ratio;
    auto width = contentSize_.Width() - TWICE * x;
    auto height = contentSize_.Height() - TWICE * y;
    config.dstRect_.SetRect(x, y, width, height);
    // calculate new srcRect
    float startImageWidth = TWICE * startSrcRect_.GetX() + startSrcRect_.Width();
    float startImageHeight = TWICE * startSrcRect_.GetY() + startSrcRect_.Height();
    float endImageWidth = TWICE * endSrcRect_.GetX() + endSrcRect_.Width();
    float endImageHeight = TWICE * endSrcRect_.GetY() + endSrcRect_.Height();
    x = endSrcRect_.GetX() * ratio +
        (startSrcRect_.GetX() / (startImageWidth / endImageWidth)) * (ANIMATION_END - ratio);
    y = endSrcRect_.GetY() * ratio +
        (startSrcRect_.GetY() / (startImageHeight / endImageHeight)) * (ANIMATION_END - ratio);
    // calculate new width & height
    width = endImageWidth - TWICE * x;
    height = endImageHeight - TWICE * y;
    config.srcRect_.SetRect(x, y, width, height);
}
} // namespace OHOS::Ace::NG