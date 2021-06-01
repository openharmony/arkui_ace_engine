/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components/image/flutter_render_image.h"

#include "flutter/common/task_runners.h"
#include "third_party/skia/include/core/SkClipOp.h"
#include "third_party/skia/include/core/SkGraphics.h"

#include "core/common/frontend.h"
#include "core/components/align/render_align.h"
#include "core/components/common/properties/radius.h"
#include "core/components/image/image_component.h"
#include "core/image/flutter_image_cache.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {

union SkColorEx {
    struct {
        SkColor color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};

RefPtr<RenderNode> RenderImage::Create()
{
    return AceType::MakeRefPtr<FlutterRenderImage>();
}

FlutterRenderImage::FlutterRenderImage()
{
    auto currentDartState = flutter::UIDartState::Current();
    if (!currentDartState) {
        return;
    }
    unrefQueue_ = currentDartState->GetSkiaUnrefQueue();
    ioManager_ = currentDartState->GetIOManager();
}

void FlutterRenderImage::Update(const RefPtr<Component>& component)
{
    RenderImage::Update(component);
    UpdateImageProvider();
}

void FlutterRenderImage::UpdateImageProvider()
{
    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("pipeline context is null!");
        return;
    }
    auto sharedImageManager = context->GetSharedImageManager();
    // curImageSrc represents the picture currently shown and imageSrc represents next picture to be shown
    bool imageSourceChange = (imageSrc_ != curImageSrc_ && !curImageSrc_.empty()) ||
                             (resourceId_ != InternalResource::ResourceId::NO_ID && curResourceId_ != resourceId_);
    bool needAltImage = (imageLoadingStatus_ != ImageLoadingStatus::LOAD_SUCCESS);
    if (imageSourceChange) {
        imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
        rawImageSize_ = Size();
    } else if (!curImageSrc_.empty()) {
        rawImageSize_ = formerRawImageSize_;
    }
    // when imageSrc empty and resourceId is changed to a valid ID, render internal image!
    // if the imageSrc is not empty, render the src image preferential.
    bool validInternalSourceSet =
        imageSrc_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID && curResourceId_ != resourceId_;
    bool validOuterSourceSet = !imageSrc_.empty() && (curImageSrc_ != imageSrc_);
    isSVG_ = IsSVG(imageSrc_, resourceId_);
    bool selfOnly = false;
    if (validInternalSourceSet) {
        imageProvider_ = AceType::MakeRefPtr<InternalImageProvider>(resourceId_);
    } else if (validOuterSourceSet) {
        imageProvider_ = ImageProvider::Create(imageSrc_, sharedImageManager);
        isNetworkSrc_ = (ImageProvider::ResolveURI(imageSrc_) == SrcType::NETWORK);
        imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
        UpdateRenderAltImage(needAltImage && isNetworkSrc_);
    } else if (isSVG_) {
        // this case is meant for SVG image needing to update color when there is no change of SVG source
        selfOnly = true;
    } else {
        return;
    }
    MarkNeedLayout(selfOnly);
    if (!imageProvider_) {
        OnLoadFail(imageProvider_);
        LOGE("Create imageProvider fail! imageSrc is %{private}s", imageSrc_.c_str());
        return;
    }
    if (isSVG_) {
        LoadSVGImage(imageProvider_, selfOnly);
        return;
    }
    imageProvider_->AddListener(AceType::WeakClaim(this));
    rawImageSizeUpdated_ = false;
    if (sharedImageManager && sharedImageManager->IsResourceToReload(ImageProvider::RemovePathHead(imageSrc_))) {
        // This case means that the imageSrc to load is a memory image and its data is not ready.
        // If run [GetImageSize] here, there will be an unexpected [OnLoadFail] callback from [ImageProvider].
        // When the data is ready, which is when [SharedImageManager] done [AddImageData], [GetImageSize] will be run.
        return;
    }
    auto frontend = context->GetFrontend();
    if (!frontend) {
        LOGE("frontend is null!");
        return;
    }
    bool syncMode = context->IsBuildingFirstPage() && frontend->GetType() == FrontendType::JS_CARD;
    auto assetManager = context->GetAssetManager();
    imageProvider_->GetImageSize(syncMode, assetManager, imageSrc_);
}

void FlutterRenderImage::Paint(RenderContext& context, const Offset& offset)
{
    if (renderAltImage_) {
        renderAltImage_->RenderWithContext(context, offset);
    }
    FetchImageData();
    auto canvas = ScopedCanvas::Create(context);
    if (!canvas) {
        LOGE("Paint canvas is null");
        return;
    }

    if (!NearZero(rotate_)) {
        Offset center =
            offset + Offset(GetLayoutSize().Width() * SK_ScalarHalf, GetLayoutSize().Height() * SK_ScalarHalf);
        SkCanvas* skCanvas = canvas.GetSkCanvas();
        if (skCanvas) {
            skCanvas->rotate(rotate_, center.GetX(), center.GetY());
        }
    }

    flutter::Paint paint;
    flutter::PaintData paint_data;
    if (opacity_ != UINT8_MAX) {
        paint.paint()->setAlpha(opacity_);
    }
    bool loadFail = (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL);
    bool networkSrcLoading = (isNetworkSrc_ && (imageLoadingStatus_ == ImageLoadingStatus::LOADING));
    // when the [networkSrcLoading] comes from network image resizing, do not need to draw alt color or alt image
    if (loadFail || (networkSrcLoading && !resizeCallLoadImage_)) {
        if (renderAltImage_) {
            return;
        }
        paint.paint()->setColor(ALT_COLOR_GREY);
        canvas->drawRect(offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
            GetLayoutSize().Height() + offset.GetY(), paint, paint_data);
        return;
    }
    if (isSVG_) {
        DrawSVGImage(offset, canvas);
    } else {
        if (!image_) {
            LOGI("Paint image is not ready, imageSrc is %{private}s", imageSrc_.c_str());
            imageDataNotReady_ = true;
            return;
        }
#ifdef USE_SYSTEM_SKIA
        paint.paint()->setColorFilter(SkColorFilter::MakeModeFilter(
            SkColorSetARGB(color_.GetAlpha(), color_.GetRed(), color_.GetGreen(), color_.GetBlue()),
            SkBlendMode::kPlus));
#else
        paint.paint()->setColorFilter(SkColorFilters::Blend(
            SkColorSetARGB(color_.GetAlpha(), color_.GetRed(), color_.GetGreen(), color_.GetBlue()),
            SkBlendMode::kPlus));
#endif
        paint.paint()->setFilterQuality(SkFilterQuality::kLow_SkFilterQuality);
        CanvasDrawImageRect(paint, paint_data, offset, canvas);
    }
}

void FlutterRenderImage::CanvasDrawImageRect(
    const flutter::Paint& paint, const flutter::PaintData& paint_data, const Offset& offset, const ScopedCanvas& canvas)
{
    if (GetBackgroundImageFlag()) {
        PaintBgImage(paint, paint_data, offset, canvas);
        return;
    }
    // Radius only takes effect when image does not need to repeat.
    // HORIZONTAL_REPEAT is customized for rating component, hence exclude it as well.
    auto paintRectList = ((imageLoadingStatus_ == ImageLoadingStatus::LOADING) && !resizeCallLoadImage_)
                             ? currentDstRectList_
                             : rectList_;
    if (imageRepeat_ == ImageRepeat::NOREPEAT) {
        ACE_DCHECK(paintRectList.size() == 1);
        auto realDstRect = paintRectList.front() + offset;
        SetClipRadius();
        flutter::RRect rrect;
        rrect.sk_rrect.setRectRadii(
            SkRect::MakeXYWH(realDstRect.Left(), realDstRect.Top(), realDstRect.Width(), realDstRect.Height()), radii_);
        canvas->clipRRect(rrect, true);
    } else {
        canvas->clipRect(offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
            GetLayoutSize().Height() + offset.GetY(), SkClipOp::kIntersect, true);
    }
    double reverseFactor = 1.0;
    Offset drawOffset = offset;
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        auto realDstRect = paintRectList.front() + offset;
        canvas.FlipHorizontal(realDstRect.Left(), realDstRect.Width());
        reverseFactor = -1.0;
        drawOffset += Offset(paintRectList.front().GetOffset().GetX() * 2.0, 0.0);
    }
    for (const auto& rect : paintRectList) {
        auto realDstRect = Rect(Offset(rect.Left() * reverseFactor, rect.Top()) + drawOffset, rect.GetSize());
        bool isLoading = ((imageLoadingStatus_ == ImageLoadingStatus::LOADING) ||
                          (imageLoadingStatus_ == ImageLoadingStatus::UPDATING));
        Rect scaledSrcRect = isLoading ? currentSrcRect_ : srcRect_;
        if (frameCount_ <= 1) {
            Size sourceSize = (image_ ? Size(image_->width(), image_->height()) : Size());
            // calculate srcRect that matches the real image source size
            // note that gif doesn't do resize, so gif does not need to recalculate
            scaledSrcRect = RecalculateSrcRect(sourceSize);
        }
        LOGD("srcRect params: %{public}s", scaledSrcRect.ToString().c_str());
        if (frameCount_ <= 1) {
            scaledSrcRect.ApplyScaleAndRound(currentResizeScale_);
        }
        canvas->drawImageRect(image_.get(), scaledSrcRect.Left(), scaledSrcRect.Top(), scaledSrcRect.Right(),
            scaledSrcRect.Bottom(), realDstRect.Left(), realDstRect.Top(), realDstRect.Right(), realDstRect.Bottom(),
            paint, paint_data);
        LOGD("dstRect params: %{public}s", realDstRect.ToString().c_str());
    }
}

Rect FlutterRenderImage::RecalculateSrcRect(const Size& realImageSize)
{
    if (!currentResizeScale_.IsValid() || scale_ <= 0.0) {
        return Rect();
    }
    auto realSrcSize = Size(
        realImageSize.Width() / currentResizeScale_.Width(), realImageSize.Height() / currentResizeScale_.Height());
    Rect realSrcRect(Offset(), realSrcSize * (1.0 / scale_));
    Rect realDstRect(Offset(), GetLayoutSize());
    ApplyImageFit(realSrcRect, realDstRect);
    realSrcRect.ApplyScale(scale_);
    return realSrcRect;
}

void FlutterRenderImage::PaintBgImage(const flutter::Paint& paint, const flutter::PaintData& paint_data,
    const Offset& offset, const ScopedCanvas& canvas) const
{
    if (!GetBackgroundImageFlag()) {
        return;
    }
    if (currentDstRectList_.empty()) {
        LOGE("[BOX][IMAGE][Dep:%{public}d] PaintImage failed, the rect list is Null.", GetDepth());
        return;
    }

    for (auto rect : currentDstRectList_) {
        auto realDstRect = rect + offset + boxMarginOffset_;
        canvas->drawImageRect(image_.get(), 0.0, 0.0, image_->width(), image_->height(), realDstRect.Left(),
            realDstRect.Top(), realDstRect.Right(), realDstRect.Bottom(), paint, paint_data);
    }
}

void FlutterRenderImage::FetchImageData()
{
    bool sourceChange =
        (!imageSrc_.empty() && curImageSrc_ != imageSrc_) || (imageSrc_.empty() && curResourceId_ != resourceId_);
    bool newSourceCallLoadImage = (sourceChange && rawImageSize_.IsValid() && srcRect_.IsValid() &&
                                   (rawImageSizeUpdated_ && imageLoadingStatus_ != ImageLoadingStatus::LOADING) &&
                                   imageLoadingStatus_ != ImageLoadingStatus::LOAD_FAIL);
    if (imageLoadingStatus_ != ImageLoadingStatus::LOADING) {
        resizeCallLoadImage_ =
            !sourceChange && NeedResize() && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS);
    }
    if (newSourceCallLoadImage || resizeCallLoadImage_ || (needReload_ && rawImageSizeUpdated_)) {
        imageLoadingStatus_ = ImageLoadingStatus::LOADING;
        if (imageProvider_) {
            previousResizeTarget_ = resizeTarget_;
            auto piplineContext = GetContext().Upgrade();
            if (!piplineContext) {
                return;
            }
            imageProvider_->LoadImage(piplineContext, imageSrc_, resizeTarget_);
            if (needReload_) {
                needReload_ = false;
            }
        }
    }
}

void FlutterRenderImage::SetClipRadius()
{
    SetSkRadii(topLeftRadius_, radii_[SkRRect::kUpperLeft_Corner]);
    SetSkRadii(topRightRadius_, radii_[SkRRect::kUpperRight_Corner]);
    SetSkRadii(bottomLeftRadius_, radii_[SkRRect::kLowerLeft_Corner]);
    SetSkRadii(bottomRightRadius_, radii_[SkRRect::kLowerRight_Corner]);
}

void FlutterRenderImage::SetSkRadii(const Radius& radius, SkVector& radii)
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    double dipScale = context->GetDipScale();
    radii.set(SkDoubleToScalar(std::max(radius.GetX().ConvertToPx(dipScale), 0.0)),
        SkDoubleToScalar(std::max(radius.GetY().ConvertToPx(dipScale), 0.0)));
}

Size FlutterRenderImage::Measure()
{
    if (isSVG_) {
        return imageComponentSize_;
    }
    switch (imageLoadingStatus_) {
        case ImageLoadingStatus::LOAD_SUCCESS:
        case ImageLoadingStatus::LOADING:
        case ImageLoadingStatus::UNLOADED:
        case ImageLoadingStatus::LOAD_FAIL:
            return rawImageSize_;
        case ImageLoadingStatus::UPDATING:
            if (rawImageSizeUpdated_) {
                return rawImageSize_;
            }
            return formerRawImageSize_;
        default:
            return Size();
    }
}

void FlutterRenderImage::UploadToGPUForRender(
    const sk_sp<SkImage>& image,
    const std::function<void(flutter::SkiaGPUObject<SkImage>)>& callback)
{
    // If want to dump draw command, should use CPU image.
    callback({ image, unrefQueue_ });
}

void FlutterRenderImage::OnLoadSuccess(
    const sk_sp<SkImage>& image,
    const RefPtr<ImageProvider>& imageProvider,
    const std::string& key)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto imageCache = context->GetImageCache();
    auto taskExecutor = context->GetTaskExecutor();
    auto callback = [renderImage = Claim(this), key, imageCache, imageProvider, taskExecutor](
        flutter::SkiaGPUObject<SkImage> image) {
        auto canvasImage = flutter::CanvasImage::Create();
        canvasImage->set_image(std::move(image));
        if (imageCache) {
            imageCache->CacheImage(key, std::make_shared<CachedImage>(canvasImage));
        }
        ImageProvider::RemoveLoadingImage(key);
        renderImage->OnLoadGPUImageSuccess(canvasImage, imageProvider);
        // Trigger purge cpu bitmap resource, after image upload to gpu.
        taskExecutor->PostTask([]() { SkGraphics::PurgeResourceCache(); }, TaskExecutor::TaskType::IO);
    };
    UploadToGPUForRender(image, callback);
}

void FlutterRenderImage::OnLoadGPUImageSuccess(
    const fml::RefPtr<flutter::CanvasImage>& image, const RefPtr<ImageProvider>& imageProvider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [renderImage = Claim(this), image, imageProvider]() {
            if (!renderImage->imageProvider_) {
                LOGE("imageProvider is null!");
                return;
            }
            if (imageProvider != renderImage->imageProvider_) {
                LOGI(
                    "OnLoadSuccess called from invalid imageProvider, src: %{private}s",
                    renderImage->imageSrc_.c_str());
                renderImage->imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
                return;
            }
            static constexpr double precision = 0.5;
            int32_t dstWidth = static_cast<int32_t>(renderImage->previousResizeTarget_.Width() + precision);
            int32_t dstHeight = static_cast<int32_t>(renderImage->previousResizeTarget_.Height() + precision);
            bool isTargetSource = ((dstWidth == image->width()) && (dstHeight == image->height()));
            if (!isTargetSource && (renderImage->imageProvider_->GetTotalFrames() <= 1) && !renderImage->background_) {
                return;
            }
            renderImage->UpdateLoadSuccessState();
            renderImage->image_ = image;
            if (renderImage->imageDataNotReady_) {
                LOGI("Paint image is ready, imageSrc is %{private}s", renderImage->imageSrc_.c_str());
                renderImage->imageDataNotReady_ = false;
            }
            if (renderImage->background_) {
                renderImage->currentDstRectList_ = renderImage->rectList_;
                if (renderImage->imageUpdateFunc_) {
                    renderImage->imageUpdateFunc_();
                }
            }

            if (renderImage->GetHidden() && renderImage->frameCount_ > 1) {
                renderImage->animatedPlayer_->Pause();
            }
        },
        TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnAnimateImageSuccess(
    const RefPtr<ImageProvider>& provider,
    std::unique_ptr<SkCodec> codec)
{
    animatedPlayer_ = MakeRefPtr<AnimatedImagePlayer>(
        provider,
        GetContext(),
        ioManager_,
        unrefQueue_,
        std::move(codec));
}

void FlutterRenderImage::OnLoadFail(const RefPtr<ImageProvider>& imageProvider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [imageProvider, renderImage = Claim(this)]() {
            if (imageProvider != renderImage->imageProvider_) {
                LOGW("OnLoadFail called from invalid imageProvider, src: %{private}s", renderImage->imageSrc_.c_str());
                return;
            }
            renderImage->currentDstRectList_.clear();
            renderImage->curImageSrc_ = renderImage->imageSrc_;
            renderImage->curResourceId_ = renderImage->resourceId_;
            renderImage->imageLoadingStatus_ = ImageLoadingStatus::LOAD_FAIL;
            renderImage->FireLoadEvent(renderImage->Measure());
            renderImage->MarkNeedLayout();
            LOGW("Load image failed!, imageSrc is %{private}s", renderImage->imageSrc_.c_str());
        },
        TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnChangeProvider(const RefPtr<ImageProvider>& provider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    context->GetTaskExecutor()->PostTask(
        [renderImage = Claim(this), provider] {
             renderImage->imageProvider_ = provider;
        },
        TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnLoadImageSize(
    Size imageSize,
    const std::string& imageSrc,
    const RefPtr<ImageProvider>& imageProvider,
    bool syncMode)
{
    auto task = [renderImage = Claim(this), imageSize, imageSrc, imageProvider]() {
        if (imageSrc != renderImage->imageSrc_) {
            LOGW("imageSrc does not match. imageSrc from callback: %{private}s, imageSrc of now: %{private}s",
                imageSrc.c_str(), renderImage->imageSrc_.c_str());
            return;
        }
        if (imageProvider != renderImage->imageProvider_) {
            LOGW("OnLoadImageSize called from invalid imageProvider, src: %{private}s", renderImage->imageSrc_.c_str());
            return;
        }
        renderImage->rawImageSize_ = imageSize;
        renderImage->rawImageSizeUpdated_ = true;
        if (!renderImage->background_) {
            renderImage->currentDstRectList_ = renderImage->rectList_;
        } else if (renderImage->imageUpdateFunc_) {
            renderImage->imageUpdateFunc_();
        }
        // If image component size is finally decided, only need to layout itself.
        bool layoutSizeNotChanged = (renderImage->previousLayoutSize_ == renderImage->GetLayoutSize());
        bool selfOnly = renderImage->imageComponentSize_.IsValid() &&
                        !renderImage->imageComponentSize_.IsInfinite() &&
                        layoutSizeNotChanged;
        renderImage->MarkNeedLayout(selfOnly);
    };

    if (syncMode) {
        task();
    } else {
        auto context = GetContext().Upgrade();
        if (!context) {
            return;
        }
        context->GetTaskExecutor()->PostTask(task, TaskExecutor::TaskType::UI);
    }
}

void FlutterRenderImage::OnHiddenChanged(bool hidden)
{
    if (animatedPlayer_ && frameCount_ > 1) {
        if (hidden) {
            animatedPlayer_->Pause();
        } else {
            animatedPlayer_->Resume();
        }
    }
}

bool FlutterRenderImage::IsSVG(const std::string& src, InternalResource::ResourceId resourceId) const
{
    // 4 is the length of ".svg".
    return (src.size() > 4 && src.substr(src.size() - 4) == ".svg") ||
           (src.empty() && resourceId > InternalResource::ResourceId::SVG_START &&
               resourceId < InternalResource::ResourceId::SVG_END);
}

void FlutterRenderImage::LoadSVGImage(const RefPtr<ImageProvider>& imageProvider, bool onlyLayoutSelf)
{
    imageLoadingStatus_ = ImageLoadingStatus::LOADING;
    auto successCallback = [svgImage = Claim(this), onlyLayoutSelf](const sk_sp<SkSVGDOM>& svgDom) {
        if (svgDom) {
            svgImage->skiaDom_ = svgDom;
            svgImage->UpdateLoadSuccessState();
            svgImage->FireLoadEvent(svgImage->Measure());
            svgImage->MarkNeedLayout(onlyLayoutSelf);
        }
    };
    auto failedCallback = [svgImage = Claim(this), providerWp = WeakClaim(RawPtr(imageProvider_))]() {
        svgImage->OnLoadFail(providerWp.Upgrade()); // if Upgrade fail, just callback with nullptr
        svgImage->FireLoadEvent(svgImage->Measure());
        svgImage->MarkNeedLayout();
    };

    auto piplineContext = GetContext().Upgrade();
    if (!piplineContext) {
        LOGE("piplinecontext is null!");
        return;
    }
    auto taskExecutor = piplineContext->GetTaskExecutor();
    auto assetManager = piplineContext->GetAssetManager();
    if (isColorSet_) {
        SkColorEx skColor;
        skColor.color = color_.GetValue();
        skColor.valid = 1;
        imageProvider->GetSVGImageDOMAsync(
            imageSrc_, successCallback, failedCallback, taskExecutor, assetManager, skColor.value);
    } else {
        imageProvider->GetSVGImageDOMAsync(imageSrc_, successCallback, failedCallback, taskExecutor, assetManager);
    }
    MarkNeedLayout();
}

void FlutterRenderImage::DrawSVGImage(const Offset& offset, ScopedCanvas& canvas)
{
    if (!skiaDom_) {
        return;
    }
    canvas->translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));
    int32_t width = static_cast<int32_t>(imageComponentSize_.Width());
    int32_t height = static_cast<int32_t>(imageComponentSize_.Height());
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        canvas.FlipHorizontal(0.0, width);
    }
    skiaDom_->setContainerSize({ width, height });
    canvas->clipRect(0, 0, width, height, SkClipOp::kIntersect);
    skiaDom_->render(canvas.GetSkCanvas());
}

void FlutterRenderImage::UpdateLoadSuccessState()
{
    if (!imageProvider_) {
        LOGD("imageProvider is null!");
        return;
    }
    imageLoadingStatus_ =
        imageLoadingStatus_ == ImageLoadingStatus::LOADING ? ImageLoadingStatus::LOAD_SUCCESS : imageLoadingStatus_;
    auto currentFrameCount = imageProvider_->GetTotalFrames();
    if (!isSVG_ && currentFrameCount == 1) {
        FireLoadEvent(Measure());
    }
    if (currentFrameCount > 1 && imageSrc_ != curImageSrc_) {
        FireLoadEvent(Measure());
        auto parent = GetParent().Upgrade();
        if (parent) {
            parent->MarkNeedRender();
        }
    }
    if (currentFrameCount != frameCount_) {
        frameCount_ = currentFrameCount;
    }
    if (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS) {
        currentSrcRect_ = srcRect_;
        imageAlt_.clear();
        curImageSrc_ = imageSrc_;
        curResourceId_ = resourceId_;
        formerRawImageSize_ = rawImageSize_;
        currentResizeScale_ = resizeScale_;
        if (renderAltImage_) {
            renderAltImage_ = nullptr;
            MarkNeedLayout();
            return;
        }
        rawImageSizeUpdated_ = false;
        LOGD("Load image success!");
    }
    MarkNeedRender();
}

void FlutterRenderImage::UpdateRenderAltImage(bool needAltImage)
{
    if (!needAltImage) {
        renderAltImage_ = nullptr;
        return;
    }
    bool imageAltValid = !imageAlt_.empty() && (imageAlt_ != IMAGE_ALT_BLANK);
    if (needAltImage && imageAltValid) {
        RefPtr<ImageComponent> altImageComponent = AceType::MakeRefPtr<ImageComponent>(imageAlt_);
        renderAltImage_ = AceType::DynamicCast<RenderImage>(altImageComponent->CreateRenderNode());
        renderAltImage_->Attach(GetContext());
        renderAltImage_->Update(altImageComponent);
        AddChild(renderAltImage_);
    }
}

bool FlutterRenderImage::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory()->GetRenderImageFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void FlutterRenderImage::ClearRenderObject()
{
    RenderImage::ClearRenderObject();
    isNetworkSrc_ = false;
    isSVG_ = false;
    curImageSrc_ = "";
    curResourceId_ = InternalResource::ResourceId::NO_ID;
    image_ = nullptr;
    imageProvider_ = nullptr;
    layer_ = nullptr;
    formerRawImageSize_ = { 0.0, 0.0 };
}

} // namespace OHOS::Ace