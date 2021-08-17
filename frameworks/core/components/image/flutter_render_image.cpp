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
#include "third_party/skia/include/core/SkColorFilter.h"

#include "core/common/frontend.h"
#include "core/components/align/render_align.h"
#include "core/components/common/properties/radius.h"
#include "core/components/image/image_component.h"
#include "core/image/flutter_image_cache.h"
#include "core/pipeline/base/constants.h"
#include "core/pipeline/base/flutter_render_context.h"

namespace OHOS::Ace {
namespace {
// The [GRAY_COLOR_MATRIX] is of dimension [4 x 5], which transforms a RGB source color (R, G, B, A) to the
// destination color (R', G', B', A').
//
// A classic color image to grayscale conversion formula is [Gray = R * 0.3 + G * 0.59 + B * 0.11].
// Hence we get the following conversion:
//
// | M11 M12 M13 M14 M15 |   | R |   | R' |
// | M21 M22 M23 M24 M25 |   | G |   | G' |
// | M31 M32 M33 M34 M35 | x | B | = | B' |
// | M41 M42 M43 M44 M45 |   | A |   | A' |
//                           | 1 |
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0,    0,  // red
                                      0.30f, 0.59f, 0.11f, 0,    0,  // green
                                      0.30f, 0.59f, 0.11f, 0,    0,  // blue
                                      0,     0,     0,     1.0f, 0}; // alpha transparency
}

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
    isSVG_ = IsSVG(imageSrc_, resourceId_);
    if (proceedPreviousLoading_ && !forceReload_ && !isSVG_) {
        LOGI("Proceed previous loading, imageSrc is %{private}s, image loading status: %{private}d",
            imageSrc_.c_str(), imageLoadingStatus_);
        return;
    }
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
    if (imageSourceChange || forceReload_) {
        imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
        rawImageSize_ = Size();
    } else if (!curImageSrc_.empty()) {
        rawImageSize_ = formerRawImageSize_;
    }
    // when imageSrc empty and resourceId is changed to a valid ID, render internal image!
    // if the imageSrc is not empty, render the src image preferential.
    bool validInternalSourceSet = imageSrc_.empty() && resourceId_ != InternalResource::ResourceId::NO_ID &&
        ((curResourceId_ != resourceId_) || forceReload_);
    bool validOuterSourceSet = !imageSrc_.empty() && ((curImageSrc_ != imageSrc_) || forceReload_);
    bool selfOnly = false;
    if (validInternalSourceSet) {
        imageProvider_ = MakeRefPtr<ImageProvider>(resourceId_);
    } else if (validOuterSourceSet) {
        imageProvider_ = MakeRefPtr<ImageProvider>(imageSrc_, sharedImageManager);
        isNetworkSrc_ = (ImageLoader::ResolveURI(imageSrc_) == SrcType::NETWORK);
        imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
        UpdateRenderAltImage(needAltImage && isNetworkSrc_);
    } else if (isSVG_) {
        // this case is meant for SVG image needing to update color when there is no change of SVG source
        selfOnly = true;
    } else {
        return;
    }
    MarkNeedLayout(selfOnly);
    if (imageProvider_->Invalid()) {
        OnLoadFail(imageProvider_);
        LOGE("Create imageProvider fail! imageSrc is %{private}s", imageSrc_.c_str());
        return;
    }
    if (isSVG_) {
        if (useSkiaSvg_) {
            LoadSVGImage(imageProvider_, selfOnly);
        } else {
            LoadSVGImageCustom(imageProvider_, selfOnly);
        }
        return;
    }
    imageProvider_->AddListener(AceType::WeakClaim(this));
    rawImageSizeUpdated_ = false;
    if (sharedImageManager && sharedImageManager->IsResourceToReload(ImageLoader::RemovePathHead(imageSrc_))) {
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
    imageProvider_->GetImageSize(syncMode, context, imageSrc_);
}

void FlutterRenderImage::Paint(RenderContext& context, const Offset& offset)
{
    if (isSVG_ && !useSkiaSvg_) {
        DrawSVGImageCustom(context, offset);
        return;
    }
    if (renderAltImage_) {
        renderAltImage_->RenderWithContext(context, offset);
    }
    if (imageProvider_) {
        FetchImageData();
    }
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
    // draw alt color only when it fails to load image
    if (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL) {
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
        return;
    }
    if (!image_) {
        LOGI("Paint image is not ready, imageSrc is %{private}s, image size updated : %{private}d",
            imageSrc_.c_str(), rawImageSizeUpdated_);
        imageDataNotReady_ = true;
        return;
    }
    // It can be guaranteed that the [SkImage] object (image_->image()) is not null.
#ifdef USE_SYSTEM_SKIA
    paint.paint()->setColor4f(paint.paint()->getColor4f(), image_->image()->colorSpace());
#else
    paint.paint()->setColor(paint.paint()->getColor4f(), image_->image()->colorSpace());
#endif
    ApplyColorFilter(paint);
    ApplyInterpolation(paint);
    CanvasDrawImageRect(paint, paint_data, offset, canvas);
}

void FlutterRenderImage::ApplyColorFilter(flutter::Paint& paint)
{
#ifdef USE_SYSTEM_SKIA
    if (imageRenderMode_ == ImageRenderMode::TEMPLATE) {
        paint.paint()->setColorFilter(SkColorFilter::MakeMatrixFilterRowMajor255(GRAY_COLOR_MATRIX));
        return;
    }
    paint.paint()->setColorFilter(SkColorFilter::MakeModeFilter(
        SkColorSetARGB(color_.GetAlpha(), color_.GetRed(), color_.GetGreen(), color_.GetBlue()),
        SkBlendMode::kPlus));
#else
    if (imageRenderMode_ == ImageRenderMode::TEMPLATE) {
        paint.paint()->setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
        return;
    }
    paint.paint()->setColorFilter(SkColorFilters::Blend(
        SkColorSetARGB(color_.GetAlpha(), color_.GetRed(), color_.GetGreen(), color_.GetBlue()),
        SkBlendMode::kPlus));
#endif
}

void FlutterRenderImage::ApplyInterpolation(flutter::Paint& paint)
{
    auto skFilterQuality = SkFilterQuality::kNone_SkFilterQuality;
    switch (imageInterpolation_) {
        case ImageInterpolation::LOW:
            skFilterQuality = SkFilterQuality::kLow_SkFilterQuality;
            break;
        case ImageInterpolation::MEDIUM:
            skFilterQuality = SkFilterQuality::kMedium_SkFilterQuality;
            break;
        case ImageInterpolation::HIGH:
            skFilterQuality = SkFilterQuality::kHigh_SkFilterQuality;
            break;
        case ImageInterpolation::NONE:
        default:
            break;
    }
    paint.paint()->setFilterQuality(skFilterQuality);
}

void FlutterRenderImage::CanvasDrawImageRect(
    const flutter::Paint& paint, const flutter::PaintData& paint_data, const Offset& offset, const ScopedCanvas& canvas)
{
    if (GetBackgroundImageFlag()) {
        PaintBgImage(paint, paint_data, offset, canvas);
        return;
    }
    auto paintRectList = ((imageLoadingStatus_ == ImageLoadingStatus::LOADING) && !resizeCallLoadImage_)
                             ? currentDstRectList_
                             : rectList_;
    SetClipRadius();
    flutter::RRect rrect;
    if (imageRepeat_ == ImageRepeat::NOREPEAT) {
        ACE_DCHECK(paintRectList.size() == 1);
        auto realDstRect = paintRectList.front() + offset;
        rrect.sk_rrect.setRectRadii(
            SkRect::MakeXYWH(realDstRect.Left(), realDstRect.Top(), realDstRect.Width(), realDstRect.Height()), radii_);
    } else {
        rrect.sk_rrect.setRectRadii(
            SkRect::MakeXYWH(offset.GetX(), offset.GetY(), GetLayoutSize().Width(), GetLayoutSize().Height()), radii_);
    }
    canvas->clipRRect(rrect, true);
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
    if (newSourceCallLoadImage || resizeCallLoadImage_ || ((needReload_ || forceReload_) && rawImageSizeUpdated_)) {
        imageLoadingStatus_ = ImageLoadingStatus::LOADING;
        if (imageProvider_) {
            previousResizeTarget_ = resizeTarget_;
            imageProvider_->LoadImage(GetContext(), imageSrc_, resizeTarget_, forceResize_);
            if (needReload_) {
                needReload_ = false;
            }
            if (forceReload_) {
                forceReload_ = false;
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

void FlutterRenderImage::OnLoadSuccess(
    const fml::RefPtr<flutter::CanvasImage>& image, const RefPtr<ImageProvider>& imageProvider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto weakRender = AceType::WeakClaim(this);
    auto weakProvider = AceType::WeakClaim(AceType::RawPtr(imageProvider));
    context->GetTaskExecutor()->PostTask([weakRender, image, weakProvider]() {
        auto renderImage = weakRender.Upgrade();
        auto imageProvider = weakProvider.Upgrade();
        if (!renderImage || !imageProvider) {
            LOGE("renderImage or imageProvider is null!");
            return;
        }
        if (!renderImage->imageProvider_) {
            LOGE("imageProvider in renderImage is null!");
            return;
        }
        if (imageProvider != renderImage->imageProvider_) {
            LOGI("Invalid imageProvider, src: %{private}s", renderImage->imageSrc_.c_str());
            renderImage->imageLoadingStatus_ = ImageLoadingStatus::UPDATING;
            return;
        }
        static constexpr double precision = 0.5;
        int32_t dstWidth = static_cast<int32_t>(renderImage->previousResizeTarget_.Width() + precision);
        int32_t dstHeight = static_cast<int32_t>(renderImage->previousResizeTarget_.Height() + precision);
        bool isTargetSource = ((dstWidth == image->width()) && (dstHeight == image->height()));
        if (!isTargetSource && (renderImage->imageProvider_->GetTotalFrames() <= 1) && !renderImage->background_) {
            LOGW("The size of returned image is not as expected, rejecting it. imageSrc: %{private}s,"
                "expected: [%{private}d x %{private}d], get [%{private}d x %{private}d]",
                renderImage->imageSrc_.c_str(), dstWidth, dstHeight, image->width(), image->height());
            return;
        }
        renderImage->UpdateLoadSuccessState();
        renderImage->image_ = image;
        if (renderImage->useSkiaSvg_) {
            renderImage->skiaDom_ = nullptr;
        } else {
            renderImage->svgDom_ = nullptr;
        }
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
    }, TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnAnimateImageSuccess(
    const RefPtr<ImageProvider>& provider, std::unique_ptr<SkCodec> codec, bool forceResize)
{
    if (forceResize) {
        int32_t dstWidth = static_cast<int32_t>(resizeTarget_.Width() + 0.5);
        int32_t dstHeight = static_cast<int32_t>(resizeTarget_.Height() + 0.5);
        animatedPlayer_ = MakeRefPtr<AnimatedImagePlayer>(
            provider, GetContext(), ioManager_, unrefQueue_, std::move(codec), dstWidth, dstHeight);
        return;
    }
    animatedPlayer_ = MakeRefPtr<AnimatedImagePlayer>(
        provider, GetContext(), ioManager_, unrefQueue_, std::move(codec));
}

void FlutterRenderImage::OnLoadFail(const RefPtr<ImageProvider>& imageProvider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto weakProvider = AceType::WeakClaim(AceType::RawPtr(imageProvider));
    context->GetTaskExecutor()->PostTask([weakProvider, weakRender = AceType::WeakClaim(this)]() {
        auto renderImage = weakRender.Upgrade();
        auto imageProvider = weakProvider.Upgrade();
        if (!renderImage || !imageProvider) {
            LOGE("renderImage or imageProvider is null!");
            return;
        }
        if (!renderImage->imageProvider_) {
            LOGE("imageProvider in renderImage is null!");
            return;
        }
        if (imageProvider != renderImage->imageProvider_) {
            LOGW("OnLoadFail called from invalid imageProvider, src: %{private}s", renderImage->imageSrc_.c_str());
            return;
        }
        if (renderImage->RetryLoading()) {
            return;
        }
        renderImage->currentDstRectList_.clear();
        renderImage->imageSizeForEvent_ = Size();
        renderImage->renderAltImage_ = nullptr;
        renderImage->image_ = nullptr;
        renderImage->curImageSrc_ = renderImage->imageSrc_;
        renderImage->curResourceId_ = renderImage->resourceId_;
        renderImage->imageLoadingStatus_ = ImageLoadingStatus::LOAD_FAIL;
        renderImage->proceedPreviousLoading_ = false;
        renderImage->FireLoadEvent(renderImage->imageSizeForEvent_);
        renderImage->MarkNeedLayout();
        LOGW("Load image failed!, imageSrc is %{private}s", renderImage->imageSrc_.c_str());
    }, TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnChangeProvider(const RefPtr<ImageProvider>& provider)
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto weakProvider = AceType::WeakClaim(AceType::RawPtr(provider));
    context->GetTaskExecutor()->PostTask([weakRender = AceType::WeakClaim(this), weakProvider] {
        auto renderImage = weakRender.Upgrade();
        if (renderImage == nullptr) {
            LOGE("renderImage is null!");
            return;
        }
        renderImage->imageProvider_ = weakProvider.Upgrade();
    }, TaskExecutor::TaskType::UI);
}

void FlutterRenderImage::OnLoadImageSize(
    Size imageSize,
    const std::string& imageSrc,
    const RefPtr<ImageProvider>& imageProvider,
    bool syncMode)
{
    auto weakProvider = AceType::WeakClaim(AceType::RawPtr(imageProvider));
    auto task = [weakRender = AceType::WeakClaim(this), imageSize, imageSrc, weakProvider]() {
        auto renderImage = weakRender.Upgrade();
        auto imageProvider = weakProvider.Upgrade();
        if (renderImage == nullptr) {
            LOGE("renderImage is null!");
            return;
        }
        if (imageSrc != renderImage->imageSrc_) {
            LOGW("imageSrc does not match. imageSrc from callback: %{private}s, imageSrc of now: %{private}s",
                imageSrc.c_str(), renderImage->imageSrc_.c_str());
            return;
        }
        if (imageProvider != renderImage->imageProvider_) {
            LOGW("OnLoadImageSize called from invalid imageProvider, src: %{private}s", renderImage->imageSrc_.c_str());
            return;
        }
        if (renderImage->sourceWidth_.IsValid() && renderImage->sourceHeight_.IsValid()) {
            renderImage->rawImageSize_ = Size(renderImage->sourceWidth_.Value(), renderImage->sourceHeight_.Value());
            renderImage->forceResize_ = true;
        } else {
            renderImage->rawImageSize_ = imageSize;
            renderImage->forceResize_ = false;
        }
        renderImage->imageSizeForEvent_ = imageSize;
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
            svgImage->image_ = nullptr;
            svgImage->renderAltImage_ = nullptr;
            svgImage->UpdateLoadSuccessState();
            svgImage->FireLoadEvent(svgImage->Measure());
            svgImage->MarkNeedLayout(onlyLayoutSelf);
        }
    };
    auto failedCallback = [svgImage = Claim(this), providerWp = WeakClaim(RawPtr(imageProvider_))]() {
        svgImage->OnLoadFail(providerWp.Upgrade()); // if Upgrade fail, just callback with nullptr
        svgImage->FireLoadEvent(Size());
        svgImage->renderAltImage_ = nullptr;
        svgImage->image_ = nullptr;
        svgImage->skiaDom_ = nullptr;
        svgImage->MarkNeedLayout();
    };

    if (isColorSet_) {
        SkColorEx skColor;
        skColor.color = color_.GetValue();
        skColor.valid = 1;
        imageProvider->GetSVGImageDOMAsync(
            imageSrc_, successCallback, failedCallback, GetContext(), skColor.value);
    } else {
        imageProvider->GetSVGImageDOMAsync(imageSrc_, successCallback, failedCallback, GetContext());
    }
    MarkNeedLayout();
}

void FlutterRenderImage::LoadSVGImageCustom(const RefPtr<ImageProvider>& imageProvider, bool onlyLayoutSelf)
{
    imageLoadingStatus_ = ImageLoadingStatus::LOADING;
    auto successCallback = [svgImageWeak = AceType::WeakClaim(this), onlyLayoutSelf](const RefPtr<SvgDom>& svgDom) {
        auto svgImage = svgImageWeak.Upgrade();
        if (svgImage && svgDom) {
            svgImage->svgDom_ = svgDom;
            svgImage->AddSvgChild();
            svgImage->image_ = nullptr;
            svgImage->renderAltImage_ = nullptr;
            svgImage->UpdateLoadSuccessState();
            svgImage->FireLoadEvent(svgImage->Measure());
            svgImage->MarkNeedLayout(onlyLayoutSelf);
        }
    };
    auto failedCallback = [svgImageWeak = AceType::WeakClaim(this), providerWp = WeakClaim(RawPtr(imageProvider_))]() {
        auto svgImage = svgImageWeak.Upgrade();
        if (svgImage) {
            svgImage->OnLoadFail(providerWp.Upgrade()); // if Upgrade fail, just callback with nullptr
            svgImage->FireLoadEvent(Size());
            svgImage->renderAltImage_ = nullptr;
            svgImage->image_ = nullptr;
            svgImage->svgDom_ = nullptr;
            svgImage->MarkNeedLayout();
        }
    };

    if (isColorSet_) {
        imageProvider->GetSVGImageDOMAsyncCustom(
            imageSrc_, successCallback, failedCallback, GetContext(), std::make_optional(color_));
    } else {
        imageProvider->GetSVGImageDOMAsyncCustom(imageSrc_, successCallback, failedCallback,
            GetContext(), std::nullopt);
    }
    MarkNeedLayout();
}

void FlutterRenderImage::DrawSVGImage(const Offset& offset, ScopedCanvas& canvas)
{
    if (!skiaDom_) {
        return;
    }
    Size svgContainerSize = GetLayoutSize();
    if (svgContainerSize.IsInfinite() || !svgContainerSize.IsValid()) {
        // when layout size is invalid, try the container size of svg
        svgContainerSize = Size(skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
        if (svgContainerSize.IsInfinite() || !svgContainerSize.IsValid()) {
            LOGE("Invalid layout size: %{private}s, invalid svgContainerSize: %{private}s, stop draw svg. The max size"
                 " of layout param is %{private}s", GetLayoutSize().ToString().c_str(),
                 svgContainerSize.ToString().c_str(), GetLayoutParam().GetMaxSize().ToString().c_str());
            return;
        } else {
            LOGE("Invalid layout size: %{private}s, valid svgContainerSize: %{private}s, use svg container size to draw"
                 " svg. The max size of layout param is %{private}s", GetLayoutSize().ToString().c_str(),
                 svgContainerSize.ToString().c_str(), GetLayoutParam().GetMaxSize().ToString().c_str());
        }
    }
    canvas->translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));
    double width = svgContainerSize.Width();
    double height = svgContainerSize.Height();
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        canvas.FlipHorizontal(0.0, width);
    }
    skiaDom_->setContainerSize({ width, height });
    canvas->clipRect(0, 0, width, height, SkClipOp::kIntersect);
    skiaDom_->render(canvas.GetSkCanvas());
}


void FlutterRenderImage::DrawSVGImageCustom(RenderContext& context, const Offset& offset)
{
    if (svgDom_ && svgDom_->GetRootRenderNode()) {
        svgDom_->GetRootRenderNode()->RenderWithContext(context, offset);
    }
}

void FlutterRenderImage::AddSvgChild()
{
    if (!svgDom_) {
        return;
    }
    svgDom_->SetFinishEvent(svgAnimatorFinishEvent_);
    svgDom_->SetContainerSize(GetLayoutSize());
    svgDom_->CreateRenderNode();
    if (svgDom_->GetRootRenderNode()) {
        ClearChildren();
        AddChild(svgDom_->GetRootRenderNode());
    }
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
        FireLoadEvent(imageSizeForEvent_);
    }
    if (currentFrameCount > 1 && imageSrc_ != curImageSrc_) {
        FireLoadEvent(imageSizeForEvent_);
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
        forceResize_ = false;
        retryCnt_ = 0;
        currentResizeScale_ = resizeScale_;
        if (renderAltImage_) {
            renderAltImage_ = nullptr;
            MarkNeedLayout();
            return;
        }
        proceedPreviousLoading_ = false;
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

bool FlutterRenderImage::IsSourceWideGamut() const
{
    if (isSVG_ || !image_) {
        return false;
    }
    return ImageProvider::IsWideGamut(image_->image()->refColorSpace());
}

bool FlutterRenderImage::RetryLoading()
{
    if (retryCnt_++ > 5) { // retry loading 5 times at most
        LOGW("Retry time has reached 5, stop retry loading, please check fail reason. imageSrc: %{private}s",
            imageSrc_.c_str());
        return false;
    }
    if (!imageProvider_) {
        LOGE("image provider is null while retrying loading. imageSrc: %{private}s", imageSrc_.c_str());
        return false;
    }
    if (rawImageSizeUpdated_) { // case when image size is ready, only have to do loading again
        imageProvider_->LoadImage(GetContext(), imageSrc_, resizeTarget_);
        LOGW("Retry loading time: %{public}d, trigger by LoadImage fail, imageSrc: %{private}s", retryCnt_,
            imageSrc_.c_str());
        return true;
    }
    // case when the fail event is triggered by GetImageSize, do GetImageSize again
    auto context = GetContext().Upgrade();
    if (!context) {
        LOGE("pipeline context is null while trying to get image size again. imageSrc: %{private}s",
            imageSrc_.c_str());
        return false;
    }
    auto frontend = context->GetFrontend();
    if (!frontend) {
        LOGE("frontend is null while trying to get image size again. imageSrc: %{private}s", imageSrc_.c_str());
        return false;
    }
    bool syncMode = context->IsBuildingFirstPage() && frontend->GetType() == FrontendType::JS_CARD;
    imageProvider_->GetImageSize(syncMode, context, imageSrc_);
    LOGW("Retry loading time: %{public}d, triggered by GetImageSize fail, imageSrc: %{private}s", retryCnt_,
        imageSrc_.c_str());
    return true;
}

} // namespace OHOS::Ace