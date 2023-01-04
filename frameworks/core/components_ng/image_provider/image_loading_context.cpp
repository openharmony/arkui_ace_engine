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

#include "core/components_ng/image_provider/image_loading_context.h"

#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/components_ng/image_provider/pixel_map_image_object.h"
#include "core/components_ng/render/image_painter.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

ImageLoadingContext::ImageLoadingContext(
    const ImageSourceInfo& sourceInfo, const LoadNotifier& loadNotifier, bool syncLoad)
    : sourceInfo_(sourceInfo), loadNotifier_(loadNotifier),
      loadCallbacks_(GenerateDataReadyCallback(), GenerateLoadSuccessCallback(), GenerateLoadFailCallback()),
      syncLoad_(syncLoad)
{
    stateManager_ = MakeRefPtr<ImageStateManager>();
    RegisterStateChangeCallbacks();
}

SizeF ImageLoadingContext::CalculateResizeTarget(const SizeF& srcSize, const SizeF& dstSize, const SizeF& rawImageSize)
{
    SizeF resizeTarget = rawImageSize;
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
            resizeTarget = SizeF(resizeTarget.Width() * widthScale, resizeTarget.Height() * heightScale);
        }
    } while (false);
    return resizeTarget;
}

void ImageLoadingContext::RegisterStateChangeCallbacks()
{
    // these tasks are called when loading state changes
    stateManager_->SetOnUnloadedCallback(CreateOnUnloadedTask());
    stateManager_->SetOnDataLoadingCallback(CreateOnDataLoadingTask());
    stateManager_->SetOnDataReadyCallback(CreateOnDataReadyTask());
    stateManager_->SetOnCanvasImageMakingCallback(CreateOnMakeCanvasImageTask());
    stateManager_->SetOnLoadSuccessCallback(CreateOnLoadSuccessTask());
    stateManager_->SetOnLoadFailCallback(CreateOnLoadFailTask());
}

EnterStateTask ImageLoadingContext::CreateOnUnloadedTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto imageLoadingContext = weakCtx.Upgrade();
        CHECK_NULL_VOID(imageLoadingContext);
        LOGI("Enter State: Unloaded");
        imageLoadingContext->RestoreLoadingParams();
    };
    return task;
}

void ImageLoadingContext::RestoreLoadingParams()
{
    LOGI("ImageLoadingContext: restore loading params");
    if (imageObj_) {
        imageObj_->ClearData();
        imageObj_->ClearCanvasImage();
    }
    imageObj_ = nullptr;
    srcRect_ = RectF();
    dstRect_ = RectF();
    dstSize_ = SizeF();
    sourceInfo_.Reset();
}

EnterStateTask ImageLoadingContext::CreateOnDataLoadingTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto loadingCtx = weakCtx.Upgrade();
        CHECK_NULL_VOID(loadingCtx);
        if (loadingCtx->syncLoad_) {
            SyncImageProvider::CreateImageObject(
                loadingCtx->sourceInfo_, loadingCtx->loadCallbacks_, loadingCtx->svgFillColorOpt_);
        } else {
            ImageProvider::CreateImageObject(
                loadingCtx->sourceInfo_, loadingCtx->loadCallbacks_, loadingCtx->svgFillColorOpt_);
        }
    };
    return task;
}

EnterStateTask ImageLoadingContext::CreateOnDataReadyTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto imageLoadingContext = weakCtx.Upgrade();
        CHECK_NULL_VOID(imageLoadingContext);
        if (imageLoadingContext->loadNotifier_.dataReadyNotifyTask_) {
            imageLoadingContext->loadNotifier_.dataReadyNotifyTask_(imageLoadingContext->GetSourceInfo());
        }
    };
    return task;
}

EnterStateTask ImageLoadingContext::CreateOnMakeCanvasImageTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        if (!ctx->imageObj_) {
            // there must be something wrong with state manager if [imageObj_] is null here.
            LOGE("image object is null during canvas image making task, sourceInfo: %{public}s",
                ctx->GetSourceInfo().ToString().c_str());
            return;
        }

        // only update params when it actually do [MakeCanvasImage]
        if (ctx->updateParamsCallback_) {
            ctx->updateParamsCallback_();
            ctx->updateParamsCallback_ = nullptr;
        }

        // step1: do first [ApplyImageFit] to calculate the srcRect based on original image size
        ImagePainter::ApplyImageFit(ctx->imageFit_, ctx->GetImageSize(),
            ctx->dstSize_, ctx->srcRect_, ctx->dstRect_);

        // step2: calculate resize target
        auto resizeTarget = ctx->GetImageSize();
        bool isPixelMapResource = (SrcType::DATA_ABILITY_DECODED == ctx->GetSourceInfo().GetSrcType());
        if (ctx->needResize_ && !isPixelMapResource) {
            resizeTarget = ImageLoadingContext::CalculateResizeTarget(ctx->srcRect_.GetSize(),
                ctx->dstRect_.GetSize(),
                ctx->GetSourceSize().value_or(ctx->GetImageSize()));
        }

        // step3: do second [ApplyImageFit] to calculate real srcRect used for paint based on resized image size
        ImagePainter::ApplyImageFit(ctx->imageFit_, resizeTarget, ctx->dstSize_,
            ctx->srcRect_, ctx->dstRect_);

        // step4: [MakeCanvasImage] according to [resizeTarget]
        ctx->imageObj_->MakeCanvasImage(ctx->loadCallbacks_, resizeTarget,
            ctx->GetSourceSize().has_value(), ctx->syncLoad_);
    };
    return task;
}

EnterStateTask ImageLoadingContext::CreateOnLoadSuccessTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        if (ctx->loadNotifier_.loadSuccessNotifyTask_) {
            ctx->loadNotifier_.loadSuccessNotifyTask_(ctx->GetSourceInfo());
            ctx->CacheImageObject();
        }
        ctx->needAlt_ = false;
    };
    return task;
}

EnterStateTask ImageLoadingContext::CreateOnLoadFailTask()
{
    auto task = [weakCtx = WeakClaim(this)]() {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        if (ctx->loadNotifier_.loadFailNotifyTask_) {
            ctx->loadNotifier_.loadFailNotifyTask_(ctx->GetSourceInfo());
        }
    };
    return task;
}

DataReadyCallback ImageLoadingContext::GenerateDataReadyCallback()
{
    auto task = [weakCtx = WeakClaim(this)](const ImageSourceInfo& sourceInfo, const RefPtr<ImageObject>& imageObj) {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnDataReady(sourceInfo, imageObj);
    };
    return task;
}

void ImageLoadingContext::OnDataReady(const ImageSourceInfo& sourceInfo, const RefPtr<ImageObject>& imageObj)
{
    if (sourceInfo_ != sourceInfo) {
        LOGI("DataReady callback with sourceInfo: %{private}s does not match current: %{private}s",
            sourceInfo.ToString().c_str(), sourceInfo_.ToString().c_str());
        return;
    }
    imageObj_ = imageObj;
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA_SUCCESS);
}

LoadSuccessCallback ImageLoadingContext::GenerateLoadSuccessCallback()
{
    auto task = [weakCtx = WeakClaim(this)](const ImageSourceInfo& sourceInfo) {
        auto ctx = weakCtx.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->OnLoadSuccess(sourceInfo);
    };
    return task;
}

void ImageLoadingContext::OnLoadSuccess(const ImageSourceInfo& sourceInfo)
{
    if (sourceInfo_ != sourceInfo) {
        LOGI("LoadSuccess callback with sourceInfo: %{private}s does not match current: %{private}s",
            sourceInfo.ToString().c_str(), sourceInfo_.ToString().c_str());
        return;
    }
    stateManager_->HandleCommand(ImageLoadingCommand::MAKE_CANVAS_IMAGE_SUCCESS);
}

LoadFailCallback ImageLoadingContext::GenerateLoadFailCallback()
{
    auto task = [weakCtx = WeakClaim(this)](const ImageSourceInfo& sourceInfo, const std::string& errorMsg,
                    const ImageLoadingCommand& command) {
        auto loadingCtx = weakCtx.Upgrade();
        CHECK_NULL_VOID(loadingCtx);
        loadingCtx->OnLoadFail(sourceInfo, errorMsg, command);
    };
    return task;
}

void ImageLoadingContext::OnLoadFail(
    const ImageSourceInfo& sourceInfo, const std::string& errorMsg, const ImageLoadingCommand& command)
{
    if (sourceInfo_ != sourceInfo) {
        LOGI("LoadFail callback with sourceInfo: %{private}s does not match current: %{private}s",
            sourceInfo.ToString().c_str(), sourceInfo_.ToString().c_str());
        return;
    }
    LOGI("Image LoadFail, source = %{private}s, reason: %{public}s", sourceInfo.ToString().c_str(), errorMsg.c_str());
    stateManager_->HandleCommand(command);
}

const RectF& ImageLoadingContext::GetDstRect() const
{
    return dstRect_;
}

const RectF& ImageLoadingContext::GetSrcRect() const
{
    return srcRect_;
}

bool ImageLoadingContext::HasCanvasImage() const
{
    return imageObj_ && imageObj_->HasCanvasImage();
}

RefPtr<CanvasImage> ImageLoadingContext::MoveCanvasImage()
{
    return imageObj_->MoveCanvasImage();
}

void ImageLoadingContext::LoadImageData()
{
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA);
}

void ImageLoadingContext::MakeCanvasImageIfNeed(const RefPtr<ImageLoadingContext>& loadingCtx, const SizeF& dstSize,
    bool incomingNeedResize, ImageFit incomingImageFit, const std::optional<SizeF>& sourceSize)
{
    CHECK_NULL_VOID(loadingCtx);
    bool needMakeCanvasImage = incomingNeedResize != loadingCtx->GetNeedResize() ||
                               dstSize != loadingCtx->GetDstSize() || incomingImageFit != loadingCtx->GetImageFit() ||
                               sourceSize != loadingCtx->GetSourceSize();
    // do [MakeCanvasImage] only when:
    // 1. [autoResize] changes
    // 2. component size (aka [dstSize] here) changes.
    // 3. [ImageFit] changes
    // 4. [sourceSize] changes
    if (needMakeCanvasImage) {
        loadingCtx->MakeCanvasImage(dstSize, incomingNeedResize, incomingImageFit, sourceSize);
    }
}

void ImageLoadingContext::MakeCanvasImage(
    const SizeF& dstSize, bool needResize, ImageFit imageFit, const std::optional<SizeF>& sourceSize)
{
    // Because calling of this interface does not guarantee the execution of [MakeCanvasImage], so in order to avoid
    // updating params before they are not actually used, capture the params in a function. This function will only run
    // when it actually do [MakeCanvasImage], i.e. doing the update in [OnMakeCanvasImageTask]
    updateParamsCallback_ = [wp = WeakClaim(this), dstSize, needResize, imageFit, sourceSize]() {
        auto ctx = wp.Upgrade();
        CHECK_NULL_VOID(ctx);
        ctx->dstSize_ = dstSize;
        ctx->imageFit_ = imageFit;
        ctx->needResize_ = needResize;
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
    return sourceInfo_;
}

void ImageLoadingContext::SetNeedResize(bool needResize)
{
    needResize_ = needResize;
}

const SizeF& ImageLoadingContext::GetDstSize() const
{
    return dstSize_;
}

bool ImageLoadingContext::GetNeedResize() const
{
    return needResize_;
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
    return needAlt_;
}

const std::optional<Color>& ImageLoadingContext::GetSvgFillColor() const
{
    return svgFillColorOpt_;
}

void ImageLoadingContext::SetSvgFillColor(const std::optional<Color>& svgFillColorOpt)
{
    if (sourceInfo_.IsSvg() && svgFillColorOpt) {
        svgFillColorOpt_ = svgFillColorOpt;
    }
}

void ImageLoadingContext::ResetLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::RESET_STATE);
}

void ImageLoadingContext::ResumeLoading()
{
    stateManager_->HandleCommand(ImageLoadingCommand::LOAD_DATA);
}

void ImageLoadingContext::CacheImageObject()
{
    auto pipelineCtx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineCtx);
    auto cache = pipelineCtx->GetImageCache();
    CHECK_NULL_VOID(cache);
    if (cache && imageObj_->GetFrameCount() == 1 && imageObj_->IsSupportCache()) {
        cache->CacheImgObjNG(imageObj_->GetSourceInfo().ToString(), imageObj_);
    }
}

} // namespace OHOS::Ace::NG
