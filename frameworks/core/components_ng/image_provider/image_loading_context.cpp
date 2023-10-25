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

#include "core/components_ng/image_provider/image_loading_context.h"

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/image_provider/image_state_manager.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/render/image_painter.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ImageLoadingContext::ImageLoadingContext(const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad)
    : src_(src), notifiers_(std::move(loadNotifier)), syncLoad_(syncLoad)
{
    stateManager_ = MakeRefPtr<ImageStateManager>(WeakClaim(this));
    // pixmap src is ready to draw
    if (src_.GetSrcType() == SrcType::PIXMAP) {
        syncLoad_ = true;
    }
}

ImageLoadingContext::~ImageLoadingContext()
{
    // cancel background task
    if (!syncLoad_) {
        auto state = stateManager_->GetCurrentState();
        if (state == ImageLoadingState::DATA_LOADING) {
            // cancel CreateImgObj task
            ImageProvider::CancelTask(src_.GetKey(), WeakClaim(this));
        } else if (state == ImageLoadingState::MAKE_CANVAS_IMAGE) {
            // cancel MakeCanvasImage task
            if (InstanceOf<StaticImageObject>(imageObj_)) {
                ImageProvider::CancelTask(canvasKey_, WeakClaim(this));
            }
        }
    }
}

SizeF ImageLoadingContext::CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize)
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

void ImageLoadingContext::OnUnloaded()
{
    LOGD("ImageLoadingContext: OnUnloaded, reset params");
    imageObj_ = nullptr;
    canvasImage_ = nullptr;
    srcRect_ = RectF();
    dstRect_ = RectF();
    dstSize_ = SizeF();
}

void ImageLoadingContext::OnLoadSuccess()
{
    if (DynamicCast<StaticImageObject>(imageObj_)) {
        imageObj_->ClearData();
    }
    if (notifiers_.onLoadSuccess_) {
        notifiers_.onLoadSuccess_(src_);
    }
}

void ImageLoadingContext::OnLoadFail()
{
    if (notifiers_.onLoadFail_) {
        notifiers_.onLoadFail_(src_, errorMsg_);
    }
}

void ImageLoadingContext::OnDataReady()
{
    if (notifiers_.onDataReady_) {
        notifiers_.onDataReady_(src_);
    }
}

void ImageLoadingContext::OnDataLoading()
{
    if (auto obj = ImageProvider::QueryImageObjectFromCache(src_); obj) {
        DataReadyCallback(obj);
        return;
    }
    if (src_.GetSrcType() == SrcType::NETWORK && SystemProperties::GetDownloadByNetworkEnabled()) {
        DownloadImage();
        return;
    }
    ImageProvider::CreateImageObject(src_, WeakClaim(this), syncLoad_);
}

void ImageLoadingContext::DownloadImage()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    DownloadCallback downloadCallback;
    downloadCallback.successCallback = [weak = AceType::WeakClaim(this)](const std::vector<uint8_t>& imageData) {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto data = ImageData::MakeFromDataWithCopy(imageData.data(), imageData.size());
        RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(ctx->GetSourceInfo(), data);
        ctx->DataReadyCallback(imageObj);
    };
    downloadCallback.failCallback = [weak = AceType::WeakClaim(this)](std::string errorMsg) {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->FailCallback(errorMsg);
    };
    downloadCallback.cancelCallback = downloadCallback.failCallback;
    NetworkImageLoader::DownloadImage(std::move(downloadCallback), src_.GetSrc(), syncLoad_);
}

void ImageLoadingContext::OnMakeCanvasImage()
{
    CHECK_NULL_VOID(imageObj_);

    // only update params when entered MakeCanvasImage state successfully
    if (updateParamsCallback_) {
        updateParamsCallback_();
        updateParamsCallback_ = nullptr;
    }
    auto userDefinedSize = GetSourceSize();
    SizeF targetSize;
    if (userDefinedSize) {
        ImagePainter::ApplyImageFit(imageFit_, *userDefinedSize, dstSize_, srcRect_, dstRect_);
        targetSize = *userDefinedSize;
    } else {
        auto imageSize = GetImageSize();
        // calculate the srcRect based on original image size
        ImagePainter::ApplyImageFit(imageFit_, imageSize, dstSize_, srcRect_, dstRect_);

        bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == GetSourceInfo().GetSrcType());
        if (autoResize_ && !isPixelMapResource) {
            targetSize = CalculateTargetSize(srcRect_.GetSize(), dstRect_.GetSize(), imageSize);
            // calculate real srcRect used for paint based on resized image size
            ImagePainter::ApplyImageFit(imageFit_, targetSize, dstSize_, srcRect_, dstRect_);
        }

        // upscale targetSize if size level is mapped
        if (targetSize.IsPositive() && sizeLevel_ > targetSize.Width()) {
            targetSize.ApplyScale(sizeLevel_ / targetSize.Width());
        }
    }

    LOGD("start MakeCanvasImage: %{public}s, size = %{public}s", imageObj_->GetSourceInfo().ToString().c_str(),
        targetSize.ToString().c_str());
    // step4: [MakeCanvasImage] according to [targetSize]
    canvasKey_ = ImageUtils::GenerateImageKey(src_, targetSize);
    imageObj_->MakeCanvasImage(Claim(this), targetSize, userDefinedSize.has_value(), syncLoad_);
}

void ImageLoadingContext::DataReadyCallback(const RefPtr<ImageObject>& imageObj)
{
    CHECK_NULL_VOID(imageObj);
    imageObj_ = imageObj->Clone();
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA_SUCCESS);
}

void ImageLoadingContext::SuccessCallback(const RefPtr<CanvasImage>& canvasImage)
{
    canvasImage_ = canvasImage;
    stateManager_->HandleCommand(ImageLoadingCommand::MAKE_CANVAS_IMAGE_SUCCESS);
}

void ImageLoadingContext::FailCallback(const std::string& errorMsg)
{
    errorMsg_ = errorMsg;
    LOGW("Image LoadFail, source = %{private}s, reason: %{public}s", src_.ToString().c_str(), errorMsg.c_str());
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
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
    return std::move(canvasImage_);
}

void ImageLoadingContext::LoadImageData()
{
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA);
}

int32_t ImageLoadingContext::RoundUp(int32_t value)
{
    CHECK_NULL_RETURN(imageObj_, -1);
    auto res = imageObj_->GetImageSize().Width();
    CHECK_NULL_RETURN(value > 0 && res > 0, -1);
    while (res / 2 >= value) {
        res /= 2;
    }
    return res;
}

bool ImageLoadingContext::MakeCanvasImageIfNeed(
    const SizeF& dstSize, bool autoResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{
    bool res = autoResize != autoResize_ || imageFit != imageFit_ || sourceSize != GetSourceSize();

    /* When function is called with a changed dstSize, assume the image will be resized frequently. To minimize
     * MakeCanvasImage operations, map dstSize to size levels in log_2. Only Remake when the size level changes.
     */
    if (SizeChanging(dstSize)) {
        res |= RoundUp(dstSize.Width()) != sizeLevel_;
    } else if (dstSize_ == SizeF()) {
        res |= dstSize.IsPositive();
    }

    if (res) {
        MakeCanvasImage(dstSize, autoResize, imageFit, sourceSize);
    }
    return res;
}

void ImageLoadingContext::MakeCanvasImage(
    const SizeF& dstSize, bool autoResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{
    // Because calling of this interface does not guarantee the execution of [MakeCanvasImage], so in order to avoid
    // updating params before they are not actually used, capture the params in a function. This function will only run
    // when it actually do [MakeCanvasImage], i.e. doing the update in [OnMakeCanvasImageTask]
    updateParamsCallback_ = [wp = WeakClaim(this), dstSize, autoResize, imageFit, sourceSize]() {
        auto ctx = wp.Upgrade();
        CHECK_NULL_VOID(ctx);
        if (ctx->SizeChanging(dstSize)) {
            ctx->sizeLevel_ = ctx->RoundUp(dstSize.Width());
        }
        ctx->dstSize_ = dstSize;
        ctx->imageFit_ = imageFit;
        ctx->autoResize_ = autoResize;
        ctx->SetSourceSize(sourceSize);
    };
    // send command to [StateManager] and waiting the callback from it to determine next step
    stateManager_->HandleCommand(ImageLoadingCommand::MAKE_CANVAS_IMAGE);
}

SizeF ImageLoadingContext::GetImageSize() const
{
    return imageObj_ ? imageObj_->GetImageSize() : SizeF(-1.0, -1.0);
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

void ImageLoadingContext::SetAutoResize(bool autoResize)
{
    autoResize_ = autoResize;
}

const SizeF& ImageLoadingContext::GetDstSize() const
{
    return dstSize_;
}

bool ImageLoadingContext::GetAutoResize() const
{
    return autoResize_;
}

void ImageLoadingContext::SetSourceSize(const std::optional<SizeF>& sourceSize)
{
    if (sourceSize.has_value()) {
        sourceSizePtr_ = std::make_unique<SizeF>(sourceSize.value());
    }
}

std::optional<SizeF> ImageLoadingContext::GetSourceSize() const
{
    CHECK_NULL_RETURN(sourceSizePtr_, std::nullopt);
    if (sourceSizePtr_->Width() <= 0.0 || sourceSizePtr_->Height() <= 0.0) {
        LOGW("Property SourceSize is at least One invalid! Use the Image Size to calculate resize target");
        return std::nullopt;
    }
    return { *sourceSizePtr_ };
}

bool ImageLoadingContext::NeedAlt() const
{
    auto state = stateManager_->GetCurrentState();
    return state != ImageLoadingState::LOAD_SUCCESS;
}

void ImageLoadingContext::ResetLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::RESET_STATE);
}

void ImageLoadingContext::ResumeLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA);
}

const std::string ImageLoadingContext::GetCurrentLoadingState()
{
    ImageLoadingState state = ImageLoadingState::UNLOADED;
    if (stateManager_) {
        state = stateManager_->GetCurrentState();
    }
    switch (state) {
        case ImageLoadingState::DATA_LOADING:
            return "DATA_LOADING";
        case ImageLoadingState::DATA_READY:
            return "DATA_READY";
        case ImageLoadingState::MAKE_CANVAS_IMAGE:
            return "MAKE_CANVAS_IMAGE";
        case ImageLoadingState::LOAD_SUCCESS:
            return "LOAD_SUCCESS";
        case ImageLoadingState::LOAD_FAIL:
            return "LOAD_FAIL";

        default:
            return "UNLOADED";
    }
}

} // namespace OHOS::Ace::NG
