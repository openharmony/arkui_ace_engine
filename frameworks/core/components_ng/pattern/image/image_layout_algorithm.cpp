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

#include "core/components_ng/pattern/image/image_layout_algorithm.h"

#ifdef FLUTTER_2_5
#include "ace_shell/shell/common/window_manager.h"
#endif
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
// returns maximum size of image component
// if maxSize is infinite, match screen size and retain aspectRatio
SizeF GetMaxSize(const SizeF& maxSize, float aspectRatio)
{
    if (NearZero(aspectRatio)) {
        return SizeF(0.0, 0.0);
    }
    // infinite size not allowed
    bool infWidth = GreaterOrEqualToInfinity(maxSize.Width());
    bool infHeight = GreaterOrEqualToInfinity(maxSize.Height());
    if (infWidth && infHeight) {
        auto width = PipelineContext::GetCurrentRootWidth();
        return SizeF(width, width / aspectRatio);
    }
    if (infWidth) {
        return SizeF(maxSize.Height() * aspectRatio, maxSize.Height());
    }
    if (infHeight) {
        return SizeF(maxSize.Width(), maxSize.Width() / aspectRatio);
    }
    return maxSize;
}
} // namespace

std::optional<SizeF> ImageLayoutAlgorithm::MeasureContent(
    const LayoutConstraintF& contentConstraint, LayoutWrapper* layoutWrapper)
{
    // case 1: image component is set with valid size, return contentConstraint.selfIdealSize as component size
    if (contentConstraint.selfIdealSize.IsValid()) {
        return contentConstraint.selfIdealSize.ConvertToSizeT();
    }
    // case 2: image component is not set with size, use image source size to determine component size
    // if image data and altImage are both not ready, can not decide content size,
    // return std::nullopt and wait for next layout task triggered by [OnImageDataReady]
    if ((!loadingCtx_ || !loadingCtx_->GetImageSize().IsPositive()) &&
        (!altLoadingCtx_ || !altLoadingCtx_->GetImageSize().IsPositive())) {
        return std::nullopt;
    }
    // if image data is valid, use image source, or use altImage data
    auto imageLoadingContext = loadingCtx_ ? loadingCtx_ : altLoadingCtx_;
    auto rawImageSize = imageLoadingContext->GetImageSize();
    SizeF size(rawImageSize);
    do {
        auto aspectRatio = static_cast<float>(Size::CalcRatio(rawImageSize));
        if (NearZero(aspectRatio)) {
            LOGW("image aspectRatio is 0");
            return std::nullopt;
        }
        // case 2.1: image component is not set with size, use image source size as image component size
        //          if fitOriginalSize is true, use image source size as image component size
        //          if fitOriginalSize is false, use the parent component LayoutConstraint size as image component size
        const auto& props = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
        bool fitOriginalSize = props->GetFitOriginalSize().value_or(false);
        if (contentConstraint.selfIdealSize.IsNull()) {
            if (!fitOriginalSize) {
                size.SetSizeT(GetMaxSize(contentConstraint.maxSize, aspectRatio));
            }
            break;
        }
        // case 2.2 image component is set with width or height, and
        //          image data is ready, use image source size to determine image component size
        //          keep the principle of making the component aspect ratio and the image source aspect ratio the same.
        //          the fitOriginSize is only useful in case 2.1.
        auto sizeSet = contentConstraint.selfIdealSize.ConvertToSizeT();
        size.SetSizeT(sizeSet);
        uint8_t sizeSetStatus = Negative(sizeSet.Width()) << 1 | Negative(sizeSet.Height());
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

void ImageLayoutAlgorithm::Layout(LayoutWrapper* layoutWrapper)
{
    BoxLayoutAlgorithm::Layout(layoutWrapper);
    // if layout size has not decided yet, resize target can not be calculated
    if (!layoutWrapper->GetGeometryNode()->GetContent()) {
        return;
    }
    const auto& imageLayoutProperty = DynamicCast<ImageLayoutProperty>(layoutWrapper->GetLayoutProperty());
    CHECK_NULL_VOID(imageLayoutProperty);
    const auto& dstSize = layoutWrapper->GetGeometryNode()->GetContentSize();
    bool autoResize = imageLayoutProperty->GetAutoResize().value_or(true);
    ImageFit imageFit = imageLayoutProperty->GetImageFit().value_or(ImageFit::COVER);
    const std::optional<SizeF>& sourceSize = imageLayoutProperty->GetSourceSize();
    if (loadingCtx_) {
        loadingCtx_->MakeCanvasImageIfNeed(dstSize, autoResize, imageFit, sourceSize);
    }
    if (altLoadingCtx_) {
        altLoadingCtx_->MakeCanvasImageIfNeed(dstSize, true, imageFit, sourceSize);
    }

    // update RS frame to content rect, no need to offset in PaintMethod
    auto host = layoutWrapper->GetHostNode();
    CHECK_NULL_VOID(host);
    auto contentRect = layoutWrapper->GetGeometryNode()->GetContentRect();
    host->GetRenderContext()->SetOverrideContentRect(contentRect);
}

} // namespace OHOS::Ace::NG
