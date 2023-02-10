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
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ImageLoadingContext::ImageLoadingContext(const ImageSourceInfo& src, LoadNotifier&& loadNotifier, bool syncLoad)
    : src_(src), notifiers_(std::move(loadNotifier)), syncLoad_(syncLoad)
{
    stateManager_ = MakeRefPtr<ImageStateManager>(WeakClaim(this));
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
            if (DynamicCast<StaticImageObject>(imageObj_)) {
                ImageProvider::CancelTask(canvasKey_, WeakClaim(this));
            }
        }
    }
}

SizeF ImageLoadingContext::CalculateTargetSize(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize)
{
    SizeF targetSize = rawImageSize;
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, rawImageSize);
    auto viewScale = context->GetViewScale();
    do {
        if (!srcSize.IsPositive()) {
            break;
        }
        double widthScale = dstSize.Width() / srcSize.Width() * viewScale;
        double heightScale = dstSize.Height() / srcSize.Height() * viewScale;
        if (widthScale < 1.0 && heightScale < 1.0) {
            targetSize = SizeF(targetSize.Width() * widthScale, targetSize.Height() * heightScale);
        }
    } while (false);
    return targetSize;
}

void ImageLoadingContext::OnUnloaded()
{
    LOGI("ImageLoadingContext: OnUnloaded, reset params");
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
    if (notifiers_.loadSuccessNotifyTask_) {
        notifiers_.loadSuccessNotifyTask_(src_);
    }
}

void ImageLoadingContext::OnLoadFail()
{
    if (notifiers_.loadFailNotifyTask_) {
        notifiers_.loadFailNotifyTask_(src_);
    }
}

void ImageLoadingContext::OnDataReady()
{
    if (notifiers_.dataReadyNotifyTask_) {
        notifiers_.dataReadyNotifyTask_(src_);
    }
}

void ImageLoadingContext::OnDataLoading()
{
    if (auto obj = ImageProvider::QueryImageObjectFromCache(src_); obj) {
        DataReadyCallback(obj);
        return;
    }
    ImageProvider::CreateImageObject(src_, WeakClaim(this), syncLoad_);
}

void ImageLoadingContext::OnMakeCanvasImage()
{
    CHECK_NULL_VOID(imageObj_);

    // only update params when entered MakeCanvasImage state successfully
    if (updateParamsCallback_) {
        updateParamsCallback_();
        updateParamsCallback_ = nullptr;
    }

    // step1: do first [ApplyImageFit] to calculate the srcRect based on original image size
    ImagePainter::ApplyImageFit(imageFit_, GetImageSize(), dstSize_, srcRect_, dstRect_);

    // step2: calculate resize target
    auto resizeTarget = GetImageSize();
    bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == GetSourceInfo().GetSrcType());
    if (autoResize_ && !isPixelMapResource) {
        resizeTarget = ImageLoadingContext::CalculateTargetSize(
            srcRect_.GetSize(), dstRect_.GetSize(), GetSourceSize().value_or(GetImageSize()));
    }

    // step3: do second [ApplyImageFit] to calculate real srcRect used for paint based on resized image size
    ImagePainter::ApplyImageFit(imageFit_, resizeTarget, dstSize_, srcRect_, dstRect_);

    if (auto image = ImageProvider::QueryCanvasImageFromCache(src_, resizeTarget); image) {
        SuccessCallback(image);
        return;
    }
    LOGI("CanvasImage cache miss, start MakeCanvasImage: %{public}s", imageObj_->GetSourceInfo().ToString().c_str());
    // step4: [MakeCanvasImage] according to [resizeTarget]
    canvasKey_ = ImageUtils::GenerateImageKey(src_, resizeTarget);
    imageObj_->MakeCanvasImage(Claim(this), resizeTarget, GetSourceSize().has_value(), syncLoad_);
}

void ImageLoadingContext::DataReadyCallback(const RefPtr<ImageObject>& imageObj)
{
    CHECK_NULL_VOID(imageObj);
    imageObj_ = imageObj->Clone();
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA_SUCCESS);
}

void ImageLoadingContext::SuccessCallback(const RefPtr<CanvasImage>& canvasImage)
{
    canvasImage_ = canvasImage->Clone();
    stateManager_->HandleCommand(ImageLoadingCommand::MAKE_CANVAS_IMAGE_SUCCESS);
}

void ImageLoadingContext::FailCallback(const std::string& errorMsg)
{
    LOGI("Image LoadFail, source = %{private}s, reason: %{public}s", src_.ToString().c_str(), errorMsg.c_str());
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

void ImageLoadingContext::MakeCanvasImageIfNeed(
    const SizeF& dstSize, bool incomingNeedResize, ImageFit incomingImageFit, const std::optional<SizeF>& sourceSize)
{
    bool needMakeCanvasImage = incomingNeedResize != GetAutoResize() || dstSize != GetDstSize() ||
                               incomingImageFit != GetImageFit() || sourceSize != GetSourceSize();
    // do [MakeCanvasImage] only when:
    // 1. [autoResize] changes
    // 2. component size (aka [dstSize] here) changes.
    // 3. [ImageFit] changes
    // 4. [sourceSize] changes
    if (needMakeCanvasImage) {
        MakeCanvasImage(dstSize, incomingNeedResize, incomingImageFit, sourceSize);
    }
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
    if (sourceSizePtr_ == nullptr) {
        return std::nullopt;
    }
    if (sourceSizePtr_->Width() <= 0.0 || sourceSizePtr_->Height() <= 0.0) {
        LOGW("Property SourceSize is at least One invalid! Use the Image Size to calculate resize target");
        return std::nullopt;
    }
    return std::optional<SizeF>(*sourceSizePtr_);
}

bool ImageLoadingContext::NeedAlt() const
{
    auto state = stateManager_->GetCurrentState();
    return state != ImageLoadingState::LOAD_SUCCESS;
}

const std::optional<Color>& ImageLoadingContext::GetSvgFillColor() const
{
    return src_.GetFillColor();
}

void ImageLoadingContext::ResetLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::RESET_STATE);
}

void ImageLoadingContext::ResumeLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA);
}

} // namespace OHOS::Ace::NG
