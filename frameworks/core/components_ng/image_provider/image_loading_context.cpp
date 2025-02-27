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
#include "core/components/common/layout/constants.h"
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/image_provider/static_image_object.h"
#include "core/components_ng/pattern/image/image_dfx.h"
#include "core/components_ng/render/image_painter.h"
#include "core/image/image_file_cache.h"
#include "core/image/image_loader.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

RefPtr<ImageData> ImageLoadingContext::QueryDataFromCache(const ImageSourceInfo& src, bool& dataHit)
{
    ACE_FUNCTION_TRACE();
    std::shared_ptr<RSData> rsData = nullptr;
    rsData = ImageLoader::QueryImageDataFromImageCache(src);
    if (rsData) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "%{private}s hit the memory Cache.", src.GetSrc().c_str());
        dataHit = true;
        return AceType::MakeRefPtr<NG::DrawingImageData>(rsData);
    }
    auto drawingData = ImageLoader::LoadDataFromCachedFile(src.GetSrc());
    if (drawingData) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "%{private}s hit the disk Cache, and the data size is %{public}d.",
            src.GetSrc().c_str(), static_cast<int32_t>(drawingData->GetSize()));
        auto data = std::make_shared<RSData>();
        data->BuildWithCopy(drawingData->GetData(), drawingData->GetSize());
        return AceType::MakeRefPtr<NG::DrawingImageData>(data);
    }
    return nullptr;
}

ImageLoadingContext::ImageLoadingContext(
    const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad, const ImageDfxConfig& imageDfxConfig)
    : src_(src), notifiers_(std::move(loadNotifier)), containerId_(Container::CurrentId()), syncLoad_(syncLoad),
      imageDfxConfig_(imageDfxConfig),
      usePreload_(Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_SIXTEEN))
{
    stateManager_ = MakeRefPtr<ImageStateManager>(WeakClaim(this));
    src_.SetImageDfxConfig(imageDfxConfig_);

    if (!AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE) &&
        src_.GetSrcType() == SrcType::PIXMAP) {
        syncLoad_ = true;
    }
}

ImageLoadingContext::~ImageLoadingContext()
{
    if (!syncLoad_) {
        auto state = stateManager_->GetCurrentState();
        if (state == ImageLoadingState::DATA_LOADING) {
            // cancel CreateImgObj task
            ImageProvider::CancelTask(src_.GetKey(), WeakClaim(this));
            if (Downloadable()) {
                usePreload_
                    ? DownloadManager::GetInstance()->RemoveDownloadTaskWithPreload(
                          src_.GetSrc(), imageDfxConfig_.nodeId_)
                    : DownloadManager::GetInstance()->RemoveDownloadTask(src_.GetSrc(), imageDfxConfig_.nodeId_);
            }
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
    ImageUtils::PostToUI(std::move(pendingMakeCanvasImageTask_), "ArkUIImageMakeCanvasImage");
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

void ImageLoadingContext::OnDataReadyOnCompleteCallBack()
{
    if (notifiers_.onDataReadyComplete_) {
        notifiers_.onDataReadyComplete_(src_);
    }
}

void ImageLoadingContext::SetOnProgressCallback(
    std::function<void(const uint32_t& dlNow, const uint32_t& dlTotal)>&& onProgress)
{
    onProgressCallback_ = onProgress;
}

void ImageLoadingContext::OnDataLoading()
{
    auto obj = ImageProvider::QueryImageObjectFromCache(src_);
    if (obj) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "%{private}s hit cache, not need create object", src_.GetSrc().c_str());
        DataReadyCallback(obj);
        return;
    }
    if (Downloadable()) {
        if (syncLoad_) {
            DownloadImage();
        } else {
            auto task = [weak = AceType::WeakClaim(this)]() {
                auto ctx = weak.Upgrade();
                CHECK_NULL_VOID(ctx);
                ctx->DownloadImage();
            };
            NG::ImageUtils::PostToBg(task, "ArkUIImageDownload");
        }
        return;
    }
    src_.SetImageDfxConfig(GetImageDfxConfig());
    ImageProvider::CreateImageObject(src_, WeakClaim(this), syncLoad_);
}

bool ImageLoadingContext::NotifyReadyIfCacheHit()
{
    bool dataHit = false;
    auto cachedImageData = QueryDataFromCache(src_, dataHit);
    CHECK_NULL_RETURN(cachedImageData, false);
    auto notifyDataReadyTask = [weak = AceType::WeakClaim(this), data = std::move(cachedImageData), dataHit] {
        auto ctx = weak.Upgrade();
        CHECK_NULL_VOID(ctx);
        auto src = ctx->GetSourceInfo();
        // if find data or file cache only, build and cache object, cache data if file cache hit
        RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(src, data);
        ImageProvider::CacheImageObject(imageObj);
        if (!dataHit) {
            ImageLoader::CacheImageData(ctx->GetSourceInfo().GetKey(), data);
        }
        ctx->DataReadyCallback(imageObj);
    };
    if (syncLoad_) {
        notifyDataReadyTask();
    } else {
        ImageUtils::PostToUI(std::move(notifyDataReadyTask), "ArkUIImageNotifyDataReady");
    }
    return true;
}

bool ImageLoadingContext::Downloadable()
{
    return src_.GetSrcType() == SrcType::NETWORK && SystemProperties::GetDownloadByNetworkEnabled();
}

void ImageLoadingContext::DownloadImage()
{
    // If the preload module is not used for downloading the image, check the cache.
    if (!usePreload_ && NotifyReadyIfCacheHit()) {
        TAG_LOGD(AceLogTag::ACE_IMAGE, "%{private}s hit the Cache, not need DownLoad.", src_.GetSrc().c_str());
        return;
    }
    PerformDownload();
}

void ImageLoadingContext::PerformDownload()
{
    ACE_SCOPED_TRACE("PerformDownload %s", imageDfxConfig_.ToStringWithSrc().c_str());
    DownloadCallback downloadCallback;
    downloadCallback.successCallback = [weak = AceType::WeakClaim(this)](
                                           const std::string&& imageData, bool async, int32_t instanceId) {
        ContainerScope scope(instanceId);
        auto callback = [weak = weak, data = std::move(imageData)]() {
            auto ctx = weak.Upgrade();
            CHECK_NULL_VOID(ctx);
            ctx->DownloadImageSuccess(data);
        };
        async ? NG::ImageUtils::PostToUI(callback, "ArkUIImageDownloadSuccess") : callback();
    };
    downloadCallback.failCallback = [weak = AceType::WeakClaim(this)](
                                        std::string errorMessage, bool async, int32_t instanceId) {
        ContainerScope scope(instanceId);
        auto callback = [weak = weak, errorMessage = errorMessage]() {
            auto ctx = weak.Upgrade();
            CHECK_NULL_VOID(ctx);
            ctx->DownloadImageFailed(errorMessage);
        };
        async ? NG::ImageUtils::PostToUI(callback, "ArkUIImageDownloadFailed") : callback();
    };
    downloadCallback.cancelCallback = downloadCallback.failCallback;
    if (onProgressCallback_) {
        downloadCallback.onProgressCallback = [weak = AceType::WeakClaim(this)](
                                                  uint32_t dlTotal, uint32_t dlNow, bool async, int32_t instanceId) {
            ContainerScope scope(instanceId);
            auto callback = [weak = weak, dlTotal = dlTotal, dlNow = dlNow]() {
                auto ctx = weak.Upgrade();
                CHECK_NULL_VOID(ctx);
                ctx->DownloadOnProgress(dlNow, dlTotal);
            };
            async ? NG::ImageUtils::PostToUI(callback, "ArkUIImageDownloadOnProcess") : callback();
        };
    }
    NetworkImageLoader::DownloadImage(std::move(downloadCallback), src_.GetSrc(), syncLoad_, imageDfxConfig_.nodeId_);
}

void ImageLoadingContext::CacheDownloadedImage()
{
    CHECK_NULL_VOID(Downloadable());
    ImageProvider::CacheImageObject(imageObj_);
    if (imageObj_->GetData()) {
        ImageLoader::CacheImageData(GetSourceInfo().GetKey(), imageObj_->GetData());
    }
    if (!downloadedUrlData_.empty()) {
        ImageLoader::WriteCacheToFile(GetSourceInfo().GetSrc(), downloadedUrlData_);
    }
}

void ImageLoadingContext::DownloadImageSuccess(const std::string& imageData)
{
    ACE_SCOPED_TRACE("DownloadImageSuccess %s, [%zu]", imageDfxConfig_.ToStringWithSrc().c_str(), imageData.size());
    if (!Positive(imageData.size())) {
        FailCallback("The length of imageData from netStack is not positive");
        return;
    }
    auto data = ImageData::MakeFromDataWithCopy(imageData.data(), imageData.size());
    // if downloading is necessary, cache object, data to file
    RefPtr<ImageObject> imageObj = ImageProvider::BuildImageObject(GetSourceInfo(), data);
    if (!imageObj) {
        FailCallback("After download successful, imageObject Create fail");
        return;
    }
    // Save the downloaded data only if the preload module is not used for downloading the URL.
    // The data will be written to the cache after successful decoding.
    if (!usePreload_) {
        downloadedUrlData_ = imageData;
    }
    DataReadyCallback(imageObj);
}

void ImageLoadingContext::DownloadImageFailed(const std::string& errorMessage)
{
    TAG_LOGI(AceLogTag::ACE_IMAGE, "Download image failed, the error message is %{private}s", errorMessage.c_str());
    FailCallback(errorMessage);
}

void ImageLoadingContext::DownloadOnProgress(const uint32_t& dlNow, const uint32_t& dlTotal)
{
    if (onProgressCallback_) {
        onProgressCallback_(dlNow, dlTotal);
    }
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

    // step4: [MakeCanvasImage] according to [targetSize]
    canvasKey_ = ImageUtils::GenerateImageKey(src_, targetSize);
    imageObj_->SetImageDfxConfig(imageDfxConfig_);
    imageObj_->MakeCanvasImage(WeakClaim(this), targetSize, userDefinedSize.has_value(), syncLoad_);
}

void ImageLoadingContext::ResizableCalcDstSize()
{
    auto userDefinedSize = GetSourceSize();
    if (userDefinedSize) {
        ImagePainter::ApplyImageFit(imageFit_, *userDefinedSize, dstSize_, srcRect_, dstRect_);
        return;
    }
    auto imageSize = GetImageSize();
    // calculate the srcRect based on original image size
    ImagePainter::ApplyImageFit(imageFit_, imageSize, dstSize_, srcRect_, dstRect_);

    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == GetSourceInfo().GetSrcType());
    if (autoResize_ && !isPixelMapResource) {
        SizeF targetSize = CalculateTargetSize(srcRect_.GetSize(), dstRect_.GetSize(), imageSize);
        // calculate real srcRect used for paint based on resized image size
        ImagePainter::ApplyImageFit(imageFit_, targetSize, dstSize_, srcRect_, dstRect_);
    }
}

void ImageLoadingContext::DataReadyCallback(const RefPtr<ImageObject>& imageObj)
{
    CHECK_NULL_VOID(imageObj);
    imageObj_ = imageObj->Clone();
    if (measureFinish_) {
        OnDataReadyOnCompleteCallBack();
    } else {
        needDataReadyCallBack_ = true;
    }
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA_SUCCESS);
}

void ImageLoadingContext::SuccessCallback(const RefPtr<CanvasImage>& canvasImage)
{
    canvasImage_ = canvasImage;
    if (!usePreload_) {
        CacheDownloadedImage();
    }
    stateManager_->HandleCommand(ImageLoadingCommand::MAKE_CANVAS_IMAGE_SUCCESS);
}

void ImageLoadingContext::FailCallback(const std::string& errorMsg)
{
    errorMsg_ = errorMsg;
    needErrorCallBack_ = true;
    TAG_LOGW(AceLogTag::ACE_IMAGE, "Image LoadFail, src = %{private}s, reason: %{public}s, %{public}s",
        src_.ToString().c_str(), errorMsg.c_str(), imageDfxConfig_.ToStringWithoutSrc().c_str());
    CHECK_NULL_VOID(measureFinish_);
    if (Downloadable()) {
        ImageFileCache::GetInstance().EraseCacheFile(GetSourceInfo().GetSrc());
    }
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
    needErrorCallBack_ = false;
}

void ImageLoadingContext::CallbackAfterMeasureIfNeed()
{
    if (needErrorCallBack_) {
        stateManager_->HandleCommand(ImageLoadingCommand::LOAD_FAIL);
        needErrorCallBack_ = false;
    }
    if (needDataReadyCallBack_) {
        OnDataReadyOnCompleteCallBack();
        needDataReadyCallBack_ = false;
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
    return std::move(canvasImage_);
}

RefPtr<ImageObject> ImageLoadingContext::MoveImageObject()
{
    return std::move(imageObj_);
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

bool ImageLoadingContext::MakeCanvasImageIfNeed(const SizeF& dstSize, bool autoResize, ImageFit imageFit,
    const std::optional<SizeF>& sourceSize, bool hasValidSlice)
{
    bool res = autoResize != autoResize_ || imageFit != imageFit_ || sourceSize != GetSourceSize() || firstLoadImage_;

    /* When function is called with a changed dstSize, assume the image will be resized frequently. To minimize
     * MakeCanvasImage operations, map dstSize to size levels in log_2. Only Remake when the size level changes.
     */
    if (SizeChanging(dstSize)) {
        res |= RoundUp(dstSize.Width()) != sizeLevel_;
    } else if (dstSize_ == SizeF()) {
        res |= dstSize.IsPositive();
    }
    if (!res && hasValidSlice) {
        dstSize_ = dstSize;
    }
    CHECK_NULL_RETURN(res, res);
    if (stateManager_->GetCurrentState() == ImageLoadingState::MAKE_CANVAS_IMAGE) {
        pendingMakeCanvasImageTask_ = [weak = AceType::WeakClaim(this), dstSize, autoResize, imageFit, sourceSize]() {
            auto ctx = weak.Upgrade();
            CHECK_NULL_VOID(ctx);
            CHECK_NULL_VOID(ctx->SizeChanging(dstSize));
            ctx->MakeCanvasImage(dstSize, autoResize, imageFit, sourceSize);
        };
    } else {
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
        if (ctx->SizeChanging(dstSize) || ctx->firstLoadImage_) {
            ctx->sizeLevel_ = ctx->RoundUp(dstSize.Width());
        }
        ctx->firstLoadImage_ = false;
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
    CHECK_NULL_RETURN(imageObj_, SizeF(-1.0, -1.0));
    auto imageSize = imageObj_->GetImageSize();
    auto orientation = imageObj_->GetOrientation();
    if (orientation == ImageRotateOrientation::LEFT || orientation == ImageRotateOrientation::RIGHT) {
        return { imageSize.Height(), imageSize.Width() };
    }
    return imageSize;
}

SizeF ImageLoadingContext::GetOriginImageSize() const
{
    return imageObj_ ? imageObj_->GetImageSize() : SizeF(-1, -1);
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
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "Property SourceSize is at least One invalid! Use the Image Size to calculate resize target");
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

int32_t ImageLoadingContext::GetFrameCount() const
{
    return imageObj_ ? imageObj_->GetFrameCount() : 0;
}

} // namespace OHOS::Ace::NG
