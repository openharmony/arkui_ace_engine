/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2023-2024. All rights reserved.
 */

#include "core/components_ng/pattern/cached_image/cached_image_layout_algorithm.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

const int ROUND_UP_SIZE = 2;

// returns maximum size of image component
// if maxSize is infinite, match screen size and retain aspectRatio
SizeF GetMaxSize(const SizeF& maxSize, float aspectRatio)
{
    if (NearZero(aspectRatio)) {
        return { 0.0, 0.0 };
    }
    // infinite size not allowed
    bool isInfWidth = GreaterOrEqualToInfinity(maxSize.Width());
    bool isInfHeight = GreaterOrEqualToInfinity(maxSize.Height());
    if (isInfWidth && isInfHeight) {
        auto width = PipelineContext::GetCurrentRootWidth();
        return { width, width / aspectRatio };
    }
    if (isInfWidth) {
        return { maxSize.Height() * aspectRatio, maxSize.Height() };
    }
    if (isInfHeight) {
        return { maxSize.Width(), maxSize.Width() / aspectRatio };
    }
    return maxSize;
}

std::optional<SizeF> CachedImageLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // case 1: image component is set with valid size, return contentConstraint.selfIdealSize as component size
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    // case 2: image component is not set with size, use image source size to determine component size
    // if image data not ready, can not decide content size, return std::nullopt
    if (!imageSize_.IsPositive()) {
        LOGE("imageSize_ is not Positive");
        return std::nullopt;
    }
    // if image data is valid, use image source
    auto rawImageSize = imageSize_;
    SizeF size(rawImageSize);
    do {
        auto aspectRatio = static_cast<float>(Size::CalcRatio(rawImageSize));
        if (NearZero(aspectRatio)) {
            LOGE("image aspectRatio is 0");
            return std::nullopt;
        }
        // case 2.1: image component is not set with size, use image source size as image component size
        // if isFitOriginalSize is true, use image source size as image component size
        // if isFitOriginalSize is false, use the parent component LayoutConstraint size as image component size
        const auto& props = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
        bool isFitOriginalSize = props->GetFitOriginalSize().value_or(false);
        if (contentConstraint.selfIdealSize.IsNull()) {
            if (!isFitOriginalSize) {
                size.SetSizeT(GetMaxSize(contentConstraint.maxSize, aspectRatio));
            }
            break;
        }
        // case 2.2 image component is set with width or height, and
        // image data is ready, use image source size to determine image component size
        // keep the principle of making the component aspect ratio and the image source aspect ratio the same.
        // the fitOriginSize is only useful in case 2.1.
        auto sizeSet = contentConstraint.selfIdealSize.ConvertToSizeT();
        size.SetSizeT(sizeSet);
        uint8_t sizeSetStatus = static_cast<uint8_t>(Negative(sizeSet.Width())) << 1
            | static_cast<uint8_t>(Negative(sizeSet.Height()));
        switch (sizeSetStatus) {
            case 0b01: // width is positive and height is negative
                size.SetHeight(sizeSet.Width() / aspectRatio);
                break;
            case 0b10: // width is negative and height is positive
                size.SetWidth(sizeSet.Height() * aspectRatio);
                break;
            case 0b11: // both width and height are negative
            default:
                break;
        }
    } while (false);
    return contentConstraint.Constrain(size);
}

void CachedImageLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    // if layout size has not decided yet, resize target can not be calculated
    if (layoutWrapper->GetGeometryNode()->GetContent() == nullptr) {
        return;
    }
    const auto& props = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(props);
    const auto& dstSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    bool isAutoResize = props->GetAutoResize().value_or(true);
    ImageFit imageFit = props->GetImageFit().value_or(ImageFit::COVER);
    const std::optional<SizeF>& sourceSize = props->GetSourceSize();
    CallbackTargetSizeIfNeed(dstSize, isAutoResize, imageFit, sourceSize);
}

void CachedImageLayoutAlgorithm::CallbackTargetSizeIfNeed(
    const SizeF& dstSize, bool isAutoResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{
    bool isSizeChanged = isAutoResize != isAutoResize_ || imageFit != imageFit_ || sourceSize != GetSourceSize();

    // When function is called with a changed dstSize, assume the image will be resized frequently.
    // Only Remake when the size level changes.
    if (isSizeChanging(dstSize)) {
        isSizeChanged = isSizeChanged || (RoundUp(dstSize.Width()) != sizeLevel_);
    } else if (dstSize_ == SizeF()) {
        isSizeChanged = isSizeChanged || dstSize.IsPositive();
    }
    if (isSizeChanged) {
        if (isSizeChanging(dstSize)) {
            sizeLevel_ = RoundUp(dstSize.Width());
        }
        dstSize_ = dstSize;
        imageFit_ = imageFit;
        isAutoResize_ = isAutoResize;
        if (sourceSize.has_value()) {
            sourceSizePtr_ = std::make_unique<SizeF>(sourceSize.value());
        }
    }
    CallbackTargetSize();
}

void CachedImageLayoutAlgorithm::CallbackTargetSize()
{
    SizeF targetSize;
    auto imageSize = imageSize_;
    // calculate the srcRect based on original image size
    ImagePainter::ApplyImageFit(imageFit_, imageSize, dstSize_, srcRect_, dstRect_);

    if (isAutoResize_) {
        targetSize = CalculateTargetSize(srcRect_.GetSize(), dstRect_.GetSize(), imageSize);
        // calculate real srcRect used for paint based on resized image size
        ImagePainter::ApplyImageFit(imageFit_, targetSize, dstSize_, srcRect_, dstRect_);
    }

    // applyScale targetSize if size level is mapped
    if (targetSize.IsPositive() && sizeLevel_ > targetSize.Width()) {
        targetSize.ApplyScale(sizeLevel_ / targetSize.Width());
    }
    if (this->layoutDoneCallback_ != nullptr) {
        this->layoutDoneCallback_(targetSize);
    } else {
        LOGD("target SizeReady Callback is null");
    }
}

void CachedImageLayoutAlgorithm::RegisterLayoutCallback(const LayoutDoneFunc& callback)
{
    this->layoutDoneCallback_ = callback;
}

int32_t CachedImageLayoutAlgorithm::RoundUp(int32_t value)
{
    auto res = imageSize_.Width();
    CHECK_NULL_RETURN(value > 0 && res > 0, -1);
    while (res / ROUND_UP_SIZE >= value) {
        res /= ROUND_UP_SIZE;
    }
    return res;
}

std::optional<SizeF> CachedImageLayoutAlgorithm::GetSourceSize() const
{
    CHECK_NULL_RETURN(sourceSizePtr_, std::nullopt);
    if (sourceSizePtr_->Width() <= 0.0 || sourceSizePtr_->Height() <= 0.0) {
        LOGW("Property SourceSize is at least One invalid! Use the Image Size to calculate resize target");
        return std::nullopt;
    }
    return { *sourceSizePtr_ };
}

SizeF CachedImageLayoutAlgorithm::CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize,
    const SizeF& rawImageSize)
{
    if (!srcSize.IsPositive()) {
        return rawImageSize;
    }

    SizeF targetSize = rawImageSize;
    auto context = PipelineContext::GetCurrentContext();
    auto viewScale = context ? context->GetViewScale() : 1.0;
    double widthScale = dstSize.Width() / srcSize.Width() * viewScale;
    double heightScale = dstSize.Height() / srcSize.Height() * viewScale;
    if (widthScale < 1.0 && heightScale < 1.0) {
        targetSize = SizeF(targetSize.Width() * widthScale, targetSize.Height() * heightScale);
    }
    return targetSize;
}

} // namespace OHOS::Ace::NG