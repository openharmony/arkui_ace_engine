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

#include "test/mock/core/render/mock_canvas_image.h"

#include "base/geometry/ng/size_t.h"
#include "core/components_ng/image_provider/image_loading_context.h"
#include "core/components_ng/pattern/image/image_dfx.h"

namespace OHOS::Ace::NG {
ImageLoadingContext::ImageLoadingContext(
    const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad, const ImageDfxConfig& imageDfxConfig)
    : src_(src), notifiers_(loadNotifier), syncLoad_(syncLoad), imageDfxConfig_(imageDfxConfig)
{}

ImageLoadingContext::~ImageLoadingContext() = default;

SizeF ImageLoadingContext::CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize)
{
    SizeF resizeTarget = rawImageSize;
    return resizeTarget;
}

void ImageLoadingContext::OnUnloaded() {}

void ImageLoadingContext::OnDataLoading() {}

void ImageLoadingContext::OnDataReady() {}

void ImageLoadingContext::OnMakeCanvasImage() {}

void ImageLoadingContext::OnLoadSuccess() {}

void ImageLoadingContext::OnLoadFail() {}

void ImageLoadingContext::DataReadyCallback(const RefPtr<ImageObject>& imageObj) {}

void ImageLoadingContext::SetOnProgressCallback(
    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& onProgress) {}

void ImageLoadingContext::SuccessCallback(const RefPtr<CanvasImage>& image)
{
    canvasImage_ = image;
    OnLoadSuccess();

    if (notifiers_.onDataReady_) {
        notifiers_.onDataReady_(src_);
    }
    if (notifiers_.onLoadSuccess_) {
        notifiers_.onLoadSuccess_(src_);
    }
}

void ImageLoadingContext::FailCallback(const std::string& errorMsg)
{
    if (notifiers_.onLoadFail_) {
        notifiers_.onLoadFail_(src_, errorMsg);
    }
}

const RectF& ImageLoadingContext::GetDstRect() const
{
    return dstRect_;
}

const RectF& ImageLoadingContext::GetSrcRect() const
{
    return srcRect_;
}

RefPtr<CanvasImage> ImageLoadingContext::MoveCanvasImage()
{
    return MakeRefPtr<MockCanvasImage>();
}

void ImageLoadingContext::CallbackAfterMeasureIfNeed() {}

void ImageLoadingContext::LoadImageData() {}

bool ImageLoadingContext::MakeCanvasImageIfNeed(const SizeF& dstSize, bool incomingNeedResize,
    ImageFit incomingImageFit, const std::optional<SizeF>& sourceSize, bool hasValidSlice)
{
    dstSize_ = dstSize;
    imageFit_ = incomingImageFit;
    autoResize_ = incomingNeedResize;
    return true;
}

void ImageLoadingContext::MakeCanvasImage(
    const SizeF& dstSize, bool needResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{}

SizeF ImageLoadingContext::GetImageSize() const
{
    return SizeF(GetSourceInfo().GetSourceSize().Width(), GetSourceInfo().GetSourceSize().Height());
}

SizeF ImageLoadingContext::GetOriginImageSize() const
{
    return SizeF(GetSourceInfo().GetSourceSize().Width(), GetSourceInfo().GetSourceSize().Height());
}

ImageFit ImageLoadingContext::GetImageFit() const
{
    return imageFit_;
}

void ImageLoadingContext::SetImageFit(ImageFit imageFit)
{
    imageFit_ = imageFit;
}

const ImageSourceInfo& ImageLoadingContext::GetSourceInfo() const
{
    return src_;
}

void ImageLoadingContext::SetAutoResize(bool needResize)
{
    autoResize_ = needResize;
}

const SizeF& ImageLoadingContext::GetDstSize() const
{
    return dstSize_;
}

bool ImageLoadingContext::GetAutoResize() const
{
    return autoResize_;
}

void ImageLoadingContext::SetSourceSize(const std::optional<SizeF>& sourceSize) {}

std::optional<SizeF> ImageLoadingContext::GetSourceSize() const
{
    return std::optional<SizeF>();
}

bool ImageLoadingContext::NeedAlt() const
{
    return true;
}

void ImageLoadingContext::ResetLoading() {}
void ImageLoadingContext::ResumeLoading() {}
void ImageLoadingContext::DownloadImage() {}
void ImageLoadingContext::ResizableCalcDstSize() {}

const std::string ImageLoadingContext::GetCurrentLoadingState()
{
    return "UNLOADED";
}

int32_t ImageLoadingContext::GetFrameCount() const
{
    return 1;
}

bool ImageLoadingContext::Downloadable()
{
    return true;
}

void ImageLoadingContext::PerformDownload() {}

void ImageLoadingContext::DownloadImageSuccess(const std::string& imageData) {}

void ImageLoadingContext::DownloadImageFailed(const std::string& errorMessage) {}

RefPtr<ImageData> ImageLoadingContext::QueryDataFromCache(const ImageSourceInfo& src, bool& dataHit)
{
    return nullptr;
}
} // namespace OHOS::Ace::NG