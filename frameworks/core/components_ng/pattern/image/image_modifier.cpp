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
    flag_ = AceType::MakeRefPtr<PropertyBool>(false);
    AttachProperty(imageFit_);
    AttachProperty(flag_);
}

void ImageModifier::onDraw(DrawingContext& context)
{
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    if (isAltImage_) {
        DrawImageWithoutAnimation(context);
        return;
    }
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

void ImageModifier::UpdateImageData(const WeakPtr<CanvasImage>& canvasImage,
    const OffsetF& offset, const SizeF& contentSize)
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

void ImageModifier::Modify()
{
    flag_->Set(!flag_->Get());
}

void ImageModifier::SetIsAltImage(bool isAltImage)
{
    isAltImage_ = isAltImage;
}

float ImageModifier::GetValue(float value) const
{
    return std::max(value, 0.0f);
}

void ImageModifier::DrawImageWithAnimation(DrawingContext& context)
{
    float difference = static_cast<float>(endImageFit_) - static_cast<float>(startImageFit_);
    float ratio = 1.0f;
    if (!NearZero(difference)) {
        // ratio goes from 0 to 1
        ratio = abs((imageFit_->Get() - static_cast<float>(startImageFit_)) / difference);
    }
    UpdatePaintConfig(ratio);
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    canvas->SetIsDrawAnimate(!NearEqual(ANIMATION_END, ratio, EPSILON));
    ImagePainter imagePainter(canvas);
    imagePainter.DrawImage(context.canvas, offset_, contentSize_);
}

void ImageModifier::DrawImageWithoutAnimation(DrawingContext& context) const
{
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    ImagePainter imagePainter(canvas);
    imagePainter.DrawImage(context.canvas, offset_, contentSize_);
}

void ImageModifier::UpdatePaintConfig(float ratio)
{
    // use ratio to calculate new dstRect and srcRect
    auto canvas = canvasImage_.Upgrade();
    CHECK_NULL_VOID(canvas);
    auto&& config = canvas->GetPaintConfig();
    if (NearEqual(ANIMATION_END, ratio, EPSILON)) {
        config.dstRect_.SetRect(endDstRect_.GetOffset(), endDstRect_.GetSize());
        config.srcRect_.SetRect(endSrcRect_.GetOffset(), endSrcRect_.GetSize());
    } else {
        // calculate new dstRect
        auto x = startDstRect_.GetX() + (endDstRect_.GetX() - startDstRect_.GetX()) * ratio;
        auto y = startDstRect_.GetY() + (endDstRect_.GetY() - startDstRect_.GetY()) * ratio;
        auto width = contentSize_.Width() - TWICE * x;
        auto height = contentSize_.Height() - TWICE * y;
        config.dstRect_.SetRect(GetValue(x), GetValue(y), GetValue(width), GetValue(height));
        // calculate new srcRect
        auto startImageWidth = TWICE * startSrcRect_.GetX() + startSrcRect_.Width();
        auto startImageHeight = TWICE * startSrcRect_.GetY() + startSrcRect_.Height();
        auto endImageWidth = TWICE * endSrcRect_.GetX() + endSrcRect_.Width();
        auto endImageHeight = TWICE * endSrcRect_.GetY() + endSrcRect_.Height();

        x = endSrcRect_.GetX() * ratio +
            (startSrcRect_.GetX() / (startImageWidth / endImageWidth)) * (ANIMATION_END - ratio);
        y = endSrcRect_.GetY() * ratio +
            (startSrcRect_.GetY() / (startImageHeight / endImageHeight)) * (ANIMATION_END - ratio);
        // calculate new width & height
        width = endImageWidth - TWICE * x;
        height = endImageHeight - TWICE * y;
        config.srcRect_.SetRect(GetValue(x), GetValue(y), GetValue(width), GetValue(height));
    }
}
} // namespace OHOS::Ace::NG
