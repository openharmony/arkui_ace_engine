/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "core/components/image/rosen_render_image.h"

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkClipOp.h"
#include "include/core/SkColorFilter.h"
#include "include/core/SkRect.h"
#include "include/core/SkShader.h"
#else
#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#endif

#include "base/thread/background_task_executor.h"
#include "core/components/text_overlay/text_overlay_component.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/render/adapter/drawing_image.h"
#endif
#include "core/image/image_object.h"
#include "core/pipeline/base/rosen_render_context.h"

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
const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency

#ifdef USE_ROSEN_DRAWING
constexpr float FLOAT_HALF = 0.5f;
#endif
} // namespace

#ifndef USE_ROSEN_DRAWING
union SkColorEx {
    struct {
        SkColor color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};
#else
union DrawingColorEx {
    struct {
        RSColorQuad color : 32;
        bool valid : 1;
        uint32_t reserved : 31; // reserved
    };
    uint64_t value = 0;
};
#endif

RosenRenderImage::RosenRenderImage()
{
    InitializeCallbacks();
}

RosenRenderImage::~RosenRenderImage()
{
    CancelBackgroundTasks();
}

void RosenRenderImage::InitializeCallbacks()
{
    imageObjSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                   ImageSourceInfo info, const RefPtr<ImageObject>& imageObj) {
        auto renderImage = weak.Upgrade();
        if (!renderImage) {
            return;
        }
        if (renderImage->sourceInfo_ == info) {
            renderImage->ImageObjReady(imageObj);
            return;
        }
        LOGW("imageObjSuccessCallback: image source info verify fail. sourceInfo: %{private}s, "
             "callback source info: %{private}s",
            renderImage->sourceInfo_.ToString().c_str(), info.ToString().c_str());
    };

    failedCallback_ = [weak = AceType::WeakClaim(this)](ImageSourceInfo info, const std::string& errorMsg) {
        auto renderImage = weak.Upgrade();
        if (!renderImage) {
            return;
        }
        if (info != renderImage->sourceInfo_) {
            return;
        }
        auto context = renderImage->GetContext().Upgrade();
        if (!context) {
            return;
        }
        auto isDeclarative = context->GetIsDeclarative();
        if (!isDeclarative && !renderImage->syncMode_ && renderImage->RetryLoading()) {
            LOGI("retry loading. sourceInfo: %{private}s", renderImage->sourceInfo_.ToString().c_str());
            return;
        }
        renderImage->ImageObjFailed(errorMsg);
    };
    uploadSuccessCallback_ = [weak = AceType::WeakClaim(this)](
                                 ImageSourceInfo sourceInfo, const RefPtr<NG::CanvasImage>& image) {
        auto renderImage = weak.Upgrade();
        if (!renderImage) {
            return;
        }
        if (renderImage->sourceInfo_ == sourceInfo) {
            renderImage->ImageDataPaintSuccess(image);
            return;
        }
        LOGW("paintDataSuccessCallback: image source info verify fail. sourceInfo: %{private}s, callback source info: "
             "%{private}s",
            renderImage->sourceInfo_.ToString().c_str(), sourceInfo.ToString().c_str());
    };

    onPostBackgroundTask_ = [weak = AceType::WeakClaim(this)](CancelableTask task) {
        auto renderImage = weak.Upgrade();
        if (renderImage) {
            renderImage->SetFetchImageObjBackgroundTask(task);
        }
    };
}

void RosenRenderImage::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    if (!Container::Current()) {
        return;
    }
    CHECK_NULL_VOID(imageObj);
    imageObj_ = imageObj;
    auto imageSize = imageObj_->GetImageSize();
    bool canStartUploadImageObj = !autoResize_ && (imageObj_->GetFrameCount() == 1);
    if (canStartUploadImageObj) {
        previousResizeTarget_ = imageSize;
        resizeTarget_ = imageSize;
        imageLoadingStatus_ = ImageLoadingStatus::LOADING;
        resizeScale_ = Size(1.0, 1.0);
    }
    if (!imageObj_->IsSvg()) {
        if (sourceInfo_.IsSourceDimensionValid()) {
            rawImageSize_ = sourceInfo_.GetSourceSize();
            forceResize_ = true;
        } else {
            rawImageSize_ = imageSize;
            forceResize_ = false;
        }
        imageSizeForEvent_ = imageSize;
        rawImageSizeUpdated_ = true;
        if (!background_) {
            currentDstRect_ = dstRect_;
        } else if (imageUpdateFunc_) {
            imageUpdateFunc_();
        }
    } else {
        image_ = nullptr;
        if (useSkiaSvg_) {
            skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj_)->GetSkiaDom();
        } else {
            CacheSvgImageObject();
            SyncCreateSvgNodes(false);
        }
        imageSizeForEvent_ = Measure();
        UpdateLoadSuccessState();
    }
    // If image component size is finally decided, only need to layout itself.
    bool layoutSizeNotChanged = (previousLayoutSize_ == GetLayoutSize());
    bool selfOnly = (imageComponentSize_.IsValid() && !imageComponentSize_.IsInfinite() && layoutSizeNotChanged) ||
                    imageObj_->IsSvg();
    MarkNeedLayout(selfOnly);
}

void RosenRenderImage::ImageObjFailed(const std::string& errorMsg)
{
    currentDstRectList_.clear();
    imageSizeForEvent_ = Size();
    image_ = nullptr;
    imageObj_ = nullptr;
    curSourceInfo_ = sourceInfo_;
    skiaDom_ = nullptr;
    svgDom_ = nullptr;
    proceedPreviousLoading_ = false;
    imageLoadingStatus_ = ImageLoadingStatus::LOAD_FAIL;
    retryCnt_ = 0;
    FireLoadEvent(imageSizeForEvent_, errorMsg);
    MarkNeedLayout();
}

void RosenRenderImage::ImageDataPaintSuccess(const RefPtr<NG::CanvasImage>& image)
{
    static constexpr double precision = 0.5;
    int32_t dstWidth = static_cast<int32_t>(previousResizeTarget_.Width() + precision);
    int32_t dstHeight = static_cast<int32_t>(previousResizeTarget_.Height() + precision);
    bool isTargetSource = ((dstWidth == image->GetWidth()) && (dstHeight == image->GetHeight()));
    CHECK_NULL_VOID(imageObj_);
    if (!isTargetSource && (imageObj_->GetFrameCount() <= 1) && !background_) {
        return;
    }
    UpdateLoadSuccessState();
    image_ = image;
    skiaDom_ = nullptr;
    svgDom_ = nullptr;
    if (imageDataNotReady_) {
        imageDataNotReady_ = false;
    }
    if (background_) {
        currentDstRectList_ = rectList_;
        if (imageUpdateFunc_) {
            imageUpdateFunc_();
        }
    }

    if (GetHidden() && imageObj_->GetFrameCount() > 1) {
        imageObj_->Pause();
    }
    if (imageObj_->GetFrameCount() == 1 && imageObj_->GetSourceInfo().GetSrcType() != SrcType::MEMORY) {
        imageObj_->ClearData();
    }
    CacheImageObject();
    contentChanged_ = true;
}

void RosenRenderImage::CacheImageObject()
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto imageCache = context->GetImageCache();
    if (imageCache && imageObj_->GetFrameCount() == 1) {
        imageCache->CacheImgObj(imageObj_->GetSourceInfo().ToString(), imageObj_);
    }
}

void RosenRenderImage::UpdatePixmap(const RefPtr<PixelMap>& pixmap)
{
    imageObj_ = MakeRefPtr<PixelMapImageObject>(pixmap);
    image_ = nullptr;
    rawImageSize_ = imageObj_->GetImageSize();
    rawImageSizeUpdated_ = true;
    MarkNeedLayout();
}

void RosenRenderImage::Update(const RefPtr<Component>& component)
{
    RenderImage::Update(component);
    // curImageSrc represents the picture currently shown and imageSrc represents next picture to be shown
    imageLoadingStatus_ = (sourceInfo_ != curSourceInfo_) ? ImageLoadingStatus::UPDATING : imageLoadingStatus_;
    UpdateRenderAltImage(component);
    if (proceedPreviousLoading_ && imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS) {
        return;
    }

    if (sourceInfo_ != curSourceInfo_ && curSourceInfo_.IsValid()) {
        rawImageSize_ = Size();
    } else if (curSourceInfo_.IsValid()) {
        rawImageSize_ = formerRawImageSize_;
    }

    if (sourceInfo_.IsSvg()) {
        auto imageObject = QueryCacheSvgImageObject();
        if (imageObject != nullptr) {
            imageObj_ = imageObject;
            SyncCreateSvgNodes(true);
            return;
        }
    }

    FetchImageObject();
}

std::function<void()> RosenRenderImage::GenerateThumbnailLoadTask()
{
    return [sourceInfo = sourceInfo_, pipelineContext = GetContext(), weak = AceType::WeakClaim(this),
               id = Container::CurrentId()]() {
#ifdef OHOS_PLATFORM
        ContainerScope scope(id);
        auto context = pipelineContext.Upgrade();
        if (!context) {
            return;
        }
        auto dataProvider = context->GetDataProviderManager();
        if (!dataProvider) {
            return;
        }
        void* pixmapMediaUniquePtr = dataProvider->GetDataProviderThumbnailResFromUri(sourceInfo.GetSrc());
        auto pixmapOhos = PixelMap::CreatePixelMapFromDataAbility(pixmapMediaUniquePtr);
        auto taskExecutor = context->GetTaskExecutor();
        if (!taskExecutor) {
            return;
        }
        if (!pixmapOhos) {
            taskExecutor->PostTask(
                [weak, sourceInfo] {
                    auto renderImage = weak.Upgrade();
                    if (!renderImage) {
                        return;
                    }
                    renderImage->failedCallback_(sourceInfo,
                        "Fail to get thumbnail data of dataability or datashare, please check the validation of src.");
                },
                TaskExecutor::TaskType::UI, "ArkUIImageThumbnailLoadFailed");
            return;
        }
        taskExecutor->PostTask(
            [weak, pixmapOhos, sourceInfo] {
                auto renderImage = weak.Upgrade();
                if (!renderImage) {
                    return;
                }
                renderImage->UpdatePixmap(pixmapOhos);
            },
            TaskExecutor::TaskType::UI, "ArkUIImageThumbnailLoad");
#endif
    };
}

void RosenRenderImage::FetchImageObject()
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto frontend = context->GetFrontend();
    if (!frontend) {
        return;
    }
    if (!sourceInfo_.IsValid()) {
        if (context->GetIsDeclarative()) {
            ImageObjFailed("Invalid image source, input of src may be null, please check.");
        }
        return;
    }
    rawImageSizeUpdated_ = false;
    SrcType srcType = sourceInfo_.GetSrcType();
    switch (srcType) {
        case SrcType::DATA_ABILITY_DECODED: {
            BackgroundTaskExecutor::GetInstance().PostTask(GenerateThumbnailLoadTask());
            break;
        }
        case SrcType::PIXMAP: {
            UpdatePixmap(sourceInfo_.GetPixmap());
            break;
        }
        case SrcType::MEMORY: {
            UpdateSharedMemoryImage(context);
            break;
        }
        default: {
            // prevent painting old pixMap while new image is loading
            if (curSourceInfo_.GetSrcType() == SrcType::PIXMAP) {
                imageObj_ = nullptr;
            }
            bool syncMode = (context->IsBuildingFirstPage() && frontend->GetType() == FrontendType::JS_CARD &&
                                sourceInfo_.GetSrcType() != SrcType::NETWORK) ||
                            syncMode_;
            ImageProvider::FetchImageObject(sourceInfo_, imageObjSuccessCallback_, uploadSuccessCallback_,
                failedCallback_, GetContext(), syncMode, useSkiaSvg_, autoResize_, onPostBackgroundTask_);
            break;
        }
    }
}

void RosenRenderImage::UpdateSharedMemoryImage(const RefPtr<PipelineContext>& context)
{
    auto sharedImageManager = context->GetOrCreateSharedImageManager();
    if (!sharedImageManager) {
        return;
    }
    auto nameOfSharedImage = ImageLoader::RemovePathHead(sourceInfo_.GetSrc());
    sharedImageManager->RegisterLoader(nameOfSharedImage, AceType::WeakClaim(this));
    // This case means that the image to load is a memory image.
    // Add [this] to [providerMapToReload_] so that it will be notified to start loading image.
    // When the data is ready, [SharedImageManager] will call [UpdateData] in [AddImageData].
    sharedImageManager->FindImageInSharedImageMap(nameOfSharedImage, AceType::WeakClaim(this));
}

void RosenRenderImage::PerformLayoutPixmap()
{
    ProcessPixmapForPaint();
    MarkNeedRender();
}
void RosenRenderImage::ProcessPixmapForPaint()
{
    auto pixmap = AceType::DynamicCast<PixelMapImageObject>(imageObj_)->GetPixmap();
    if (!pixmap) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    // Step1: Create SkPixmap
    auto imageInfo = MakeSkImageInfoFromPixelMap(pixmap);
    SkPixmap imagePixmap(imageInfo, reinterpret_cast<const void*>(pixmap->GetPixels()), pixmap->GetRowBytes());

    // Step2: Create SkImage and draw it, using gpu or cpu
    sk_sp<SkImage> skImage =
        SkImage::MakeFromRaster(imagePixmap, &PixelMap::ReleaseProc, PixelMap::GetReleaseContext(pixmap));
    image_ = NG::CanvasImage::Create(&skImage);
    if (!VerifySkImageDataFromPixmap(pixmap)) {
#else
    // Step1: Create RSBitmap
    auto rsBitmapFormat = MakeRSBitmapFormatInfoFromPixelMap(pixmap);
    auto rsBitmap = std::make_shared<RSBitmap>();
    rsBitmap->Build(pixmap->GetWidth(), pixmap->GetHeight(), rsBitmapFormat);
    rsBitmap->SetPixels(const_cast<void*>(reinterpret_cast<const void*>(pixmap->GetPixels())));

    // Step2: Create RSImage and draw it, using gpu or cpu
    auto rsImage = std::make_shared<RSImage>();
    rsImage->BuildFromBitmap(*rsBitmap);
    image_ = NG::CanvasImage::Create(&rsImage);
    if (!VerifyRSImageDataFromPixmap(pixmap)) {
#endif
        imageLoadingStatus_ = ImageLoadingStatus::LOAD_FAIL;
        FireLoadEvent(Size(), "Image data from PixelMap is invalid, please check PixelMap data.");
        image_ = nullptr;
        imageObj_->ClearData();
        return;
    }
    // pixelMap render finished
    curSourceInfo_ = sourceInfo_;
    imageLoadingStatus_ = ImageLoadingStatus::LOAD_SUCCESS;
    FireLoadEvent(rawImageSize_);
    RemoveChild(renderAltImage_);
    renderAltImage_ = nullptr;
}

void RosenRenderImage::PerformLayoutSvgImage()
{
    if (svgRenderTree_.root) {
        ACE_SVG_SCOPED_TRACE("RosenRenderImage::PerformLayoutSvgImage");
        SvgRadius svgRadius = { topLeftRadius_, topRightRadius_, bottomLeftRadius_, bottomRightRadius_ };
        svgRenderTree_.containerSize = GetLayoutSize();
        SvgDom svgDom(context_);
        svgDom.SetSvgRenderTree(svgRenderTree_);
        svgDom.UpdateLayout(imageFit_, svgRadius, !directPaint_);
    }
}

void RosenRenderImage::LayoutImageObject()
{
    if (imageObj_) {
        imageObj_->PerformLayoutImageObject(AceType::Claim(this));
    }
}

void RosenRenderImage::SyncCreateSvgNodes(bool isReady)
{
    auto currentSvgDom = AceType::DynamicCast<SvgImageObject>(imageObj_)->GetSvgDom();
    if (currentSvgDom == nullptr) {
        return;
    }
    svgDom_ = currentSvgDom;

    if (!currentSvgDom->HasAnimate() && !currentSvgDom->HasClipPath()) {
        directPaint_ = true;
    }
    if (directPaint_ == true && isReady) {
        // svg imageObject from map buffer, use as directly
        return;
    }
    CreateSvgNodes();
}

void RosenRenderImage::CreateSvgNodes()
{
    if (!svgDom_) {
        return;
    }
    ACE_SVG_SCOPED_TRACE("RosenRenderImage::CreateSvgNodes");
    svgDom_->SetFinishEvent(svgAnimatorFinishEvent_);
    svgDom_->SetContainerSize(GetLayoutSize());
    SvgRadius svgRadius = { topLeftRadius_, topRightRadius_, bottomLeftRadius_, bottomRightRadius_ };
    auto svgRenderTree = svgDom_->CreateRenderTree(imageFit_, svgRadius, !directPaint_);
    if (svgRenderTree.root == nullptr) {
        svgDom_ = nullptr;
        return;
    }
    if (!directPaint_) {
        RebuildSvgRenderTree(svgRenderTree, svgDom_);
    }
}

void RosenRenderImage::RebuildSvgRenderTree(const SvgRenderTree& svgRenderTree, const RefPtr<SvgDom>& svgDom)
{
    svgRenderTree_ = svgRenderTree;
    ClearChildren();
    AddChild(svgRenderTree_.root);
    MarkNeedRender();
}

void RosenRenderImage::CacheSvgImageObject()
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
    auto imageCache = context->GetImageCache();
    if (imageCache) {
        imageCache->CacheImgObj(sourceInfo_.GetKey(), imageObj_);
    }
}

RefPtr<ImageObject> RosenRenderImage::QueryCacheSvgImageObject()
{
    auto context = GetContext().Upgrade();
    if (!context) {
        return nullptr;
    }
    auto imageCache = context->GetImageCache();
    if (imageCache == nullptr) {
        return nullptr;
    }
    return imageCache->GetCacheImgObj(sourceInfo_.GetKey());
}

void RosenRenderImage::Paint(RenderContext& context, const Offset& offset)
{
    if (contentChanged_) {
        auto rsNode = static_cast<RosenRenderContext*>(&context)->GetRSNode();
        if (rsNode) {
            rsNode->MarkContentChanged(true);
        }
        contentChanged_ = false;
    }
    if (imageObj_ && imageObj_->IsSvg() && !useSkiaSvg_ && !directPaint_) {
        DrawSVGImageCustom(context, offset);
        return;
    }
    bool sourceDataEmpty = !image_ && !svgDom_ && !skiaDom_;
    if (renderAltImage_ && sourceDataEmpty) {
        renderAltImage_->SetDirectPaint(directPaint_);
        renderAltImage_->RenderWithContext(context, offset);
    }
    if (sourceInfo_.GetSrcType() != SrcType::PIXMAP) {
        UpLoadImageDataForPaint();
    }
    auto canvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (!canvas) {
        return;
    }

#ifndef USE_ROSEN_DRAWING
    SkAutoCanvasRestore acr(canvas, true);
    if (!NearZero(rotate_)) {
        Offset center =
            offset + Offset(GetLayoutSize().Width() * SK_ScalarHalf, GetLayoutSize().Height() * SK_ScalarHalf);
        if (canvas) {
            canvas->rotate(rotate_, center.GetX(), center.GetY());
        }
    }
#else
    RSAutoCanvasRestore acr(*canvas, true);
    if (!NearZero(rotate_)) {
        Offset center = offset + Offset(GetLayoutSize().Width() * FLOAT_HALF, GetLayoutSize().Height() * FLOAT_HALF);
        if (canvas) {
            canvas->Rotate(rotate_, center.GetX(), center.GetY());
        }
    }
#endif

#ifndef USE_ROSEN_DRAWING
    SkPaint paint;
#else
    RSBrush brush;
#endif
    Rect paintRect =
        ((imageLoadingStatus_ == ImageLoadingStatus::LOADING) && !resizeCallLoadImage_) ? currentDstRect_ : dstRect_;
    ApplyBorderRadius(offset, paintRect, canvas);
    if (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL) {
        if (renderAltImage_) {
            return;
        }
        auto pipelineContext = GetContext().Upgrade();
        if (pipelineContext && pipelineContext->GetIsDeclarative()) {
            // for declarative front end, do not draw anything for developers who use image component, we just inform
            // them via load fail event and the developers then decide how to react when image loads fail.
            return;
        }
        // to ensure forward compatibility, draw alt color only when it fails to load image
#ifndef USE_ROSEN_DRAWING
        paint.setColor(ALT_COLOR_GREY);
#ifdef OHOS_PLATFORM
        auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas);
        if (GetBackgroundImageFlag()) {
            recordingCanvas->drawRect({ offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
                                          GetLayoutSize().Height() + offset.GetY() },
                paint);
        } else {
            recordingCanvas->DrawAdaptiveRRect(0, paint);
        }
#else
        canvas->drawRect({ offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
                             GetLayoutSize().Height() + offset.GetY() },
            paint);
#endif
#else
        brush.SetColor(ALT_COLOR_GREY);
#ifdef OHOS_PLATFORM
        auto recordingCanvas = static_cast<RSRecordingCanvas*>(canvas);
        recordingCanvas->AttachBrush(brush);
        if (GetBackgroundImageFlag()) {
            recordingCanvas->DrawRect({ offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
                GetLayoutSize().Height() + offset.GetY() });
        }
        recordingCanvas->DetachBrush();
#else
        canvas->AttachBrush(brush);
        canvas->DrawRect({ offset.GetX(), offset.GetY(), GetLayoutSize().Width() + offset.GetX(),
            GetLayoutSize().Height() + offset.GetY() });
        canvas->DetachBrush();
#endif
#endif
        return;
    }
    if (sourceInfo_.IsSvg()) {
        if (svgDom_) {
#ifndef USE_ROSEN_DRAWING
            canvas->translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));
#else
            canvas->Translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));
#endif
            svgDom_->PaintDirectly(context, offset, imageFit_, GetLayoutSize());
            return;
        }
        DrawSVGImage(offset, canvas);
        return;
    }
#ifndef USE_ROSEN_DRAWING
    ApplyColorFilter(paint);
    ApplyInterpolation(paint);
    sk_sp<SkColorSpace> colorSpace = SkColorSpace::MakeSRGB();
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (skImage && skImage->GetImage()) {
        colorSpace = skImage->GetImage()->refColorSpace();
    }

    paint.setColor(paint.getColor4f(), colorSpace.get());

#else
    ApplyColorFilter(brush);
    ApplyInterpolation(brush);
    auto colorSpace = RSColorSpace::CreateSRGB();
    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (rsImage && rsImage->GetImage()) {
        colorSpace = RSRecordingColorSpace::CreateRefImage(*rsImage->GetImage());
    }
    brush.SetColor(brush.GetColor4f(), colorSpace);
#endif
    if (GetBackgroundImageFlag()) {
        PaintBgImage(static_cast<RosenRenderContext*>(&context)->GetRSNode());
        return;
    }
#ifndef USE_ROSEN_DRAWING
    CanvasDrawImageRect(paint, offset, canvas, paintRect);
#else
    CanvasDrawImageRect(brush, offset, canvas, paintRect);
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::ApplyBorderRadius(const Offset& offset, const Rect& paintRect, SkCanvas* canvas)
#else
void RosenRenderImage::ApplyBorderRadius(const Offset& offset, const Rect& paintRect, RSCanvas* canvas)
#endif
{
    if (GetBackgroundImageFlag()) {
        return;
    }
    SetClipRadius();

#ifdef OHOS_PLATFORM
#ifndef USE_ROSEN_DRAWING
    auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas);
    recordingCanvas->ClipAdaptiveRRect(radii_);
#else
    auto recordingCanvas = static_cast<RSRecordingCanvas*>(canvas);
    recordingCanvas->ClipAdaptiveRoundRect(radii_);
#endif
#else
    // There are three situations in which we apply border radius to the whole image component:
    // 1. when the image source is a SVG;
    // 2. when image loads fail;
    // 3. when there is a repeat to do;
    bool clipLayoutSize = sourceInfo_.IsSvg() || (imageRepeat_ != ImageRepeat::NO_REPEAT) ||
                          (imageLoadingStatus_ == ImageLoadingStatus::LOAD_FAIL);
    Rect clipRect = clipLayoutSize ? Rect(offset, GetLayoutSize()) : paintRect + offset;

#ifndef USE_ROSEN_DRAWING
    SkRRect rrect;
    rrect.setRectRadii(SkRect::MakeXYWH(clipRect.Left() - imageRenderPosition_.GetX(),
                           clipRect.Top() - imageRenderPosition_.GetY(), clipRect.Width(), clipRect.Height()),
        radii_);
    canvas->clipRRect(rrect, true);
#else
    RSRoundRect rrect(
        RSRect(clipRect.Left() - imageRenderPosition_.GetX(), clipRect.Top() - imageRenderPosition_.GetY(),
            clipRect.Width() + clipRect.Left() - imageRenderPosition_.GetX(),
            clipRect.Height() + clipRect.Top() - imageRenderPosition_.GetY()),
        radii_);
    canvas->ClipRoundRect(rrect, RSClipOp::INTERSECT, true);
#endif
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::ApplyColorFilter(SkPaint& paint)
#else
void RosenRenderImage::ApplyColorFilter(RSBrush& brush)
#endif
{
#ifndef USE_ROSEN_DRAWING

    if (colorfilter_.size() == COLOR_FILTER_MATRIX_SIZE) {
        float colorfiltermatrix[COLOR_FILTER_MATRIX_SIZE] = { 0 };
        std::copy(colorfilter_.begin(), colorfilter_.end(), colorfiltermatrix);
        paint.setColorFilter(SkColorFilters::Matrix(colorfiltermatrix));
        return;
    }
    if (imageRenderMode_ == ImageRenderMode::TEMPLATE) {
        paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
        return;
    }
    if (!color_.has_value()) {
        return;
    }
    Color color = color_.value();
    paint.setColorFilter(SkColorFilters::Blend(
        SkColorSetARGB(color.GetAlpha(), color.GetRed(), color.GetGreen(), color.GetBlue()), SkBlendMode::kPlus));
#else
    if (colorfilter_.size() == COLOR_FILTER_MATRIX_SIZE) {
        RSScalar matrixArray[COLOR_FILTER_MATRIX_SIZE] = { 0 };
        std::copy(colorfilter_.begin(), colorfilter_.end(), matrixArray);
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(matrixArray);
        auto filter = brush.GetFilter();
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
        brush.SetFilter(filter);
        return;
    }
    if (imageRenderMode_ == ImageRenderMode::TEMPLATE) {
        auto filter = brush.GetFilter();
        RSColorMatrix m;
        m.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(m));
        brush.SetFilter(filter);
        return;
    }
    if (!color_.has_value()) {
        return;
    }
    Color color = color_.value();
    auto filter = brush.GetFilter();
    filter.SetColorFilter(RSRecordingColorFilter::CreateBlendModeColorFilter(
        RSColor::ColorQuadSetARGB(color.GetAlpha(), color.GetRed(), color.GetGreen(), color.GetBlue()),
        RSBlendMode::PLUS));
    brush.SetFilter(filter);
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::ApplyInterpolation(SkPaint& paint)
{
    options_ = SkSamplingOptions(SkFilterMode::kNearest, SkMipmapMode::kNone);
    switch (imageInterpolation_) {
        case ImageInterpolation::LOW:
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kNone);
            break;
        case ImageInterpolation::MEDIUM:
            options_ = SkSamplingOptions(SkFilterMode::kLinear, SkMipmapMode::kLinear);
            break;
        case ImageInterpolation::HIGH:
            options_ = SkSamplingOptions(SkCubicResampler { 1 / 3.0f, 1 / 3.0f });
            break;
        case ImageInterpolation::NONE:
        default:
            break;
    }
}
#else
void RosenRenderImage::ApplyInterpolation(RSBrush& brush)
{
    options_ = RSSamplingOptions();
    switch (imageInterpolation_) {
        case ImageInterpolation::LOW:
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::NONE);
            break;
        case ImageInterpolation::MEDIUM:
            options_ = RSSamplingOptions(RSFilterMode::LINEAR, RSMipmapMode::LINEAR);
            break;
        case ImageInterpolation::HIGH:
            options_ = RSSamplingOptions(RSCubicResampler::Mitchell());
            break;
        case ImageInterpolation::NONE:
        default:
            break;
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::CanvasDrawImageRect(
    SkPaint& paint, const Offset& offset, SkCanvas* canvas, const Rect& paintRect)
#else
void RosenRenderImage::CanvasDrawImageRect(
    RSBrush& brush, const Offset& offset, RSCanvas* canvas, const Rect& paintRect)
#endif
{
    if (GetBackgroundImageFlag()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (!skImage || (!skImage->GetImage() && !skImage->GetCompressData())) {
#else
    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (!rsImage || (!rsImage->GetImage() && !rsImage->GetCompressData())) {
#endif
        imageDataNotReady_ = true;
        return;
    }
    int fitNum = static_cast<int>(imageFit_);
    int repeatNum = static_cast<int>(imageRepeat_);
#ifndef USE_ROSEN_DRAWING
    auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas);
    if (GetAdaptiveFrameRectFlag()) {
        recordingCanvas->translate(imageRenderPosition_.GetX() * -1, imageRenderPosition_.GetY() * -1);
        Rosen::RsImageInfo rsImageInfo(
            fitNum, repeatNum, radii_, scale_, 0, skImage->GetCompressWidth(), skImage->GetCompressHeight());

        recordingCanvas->DrawImageWithParm(
            skImage->GetImage(), skImage->GetCompressData(), rsImageInfo, options_, paint);
        skImage->SetCompressData(nullptr, 0, 0);
        return;
#else
    auto recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas*>(canvas);
    if (GetAdaptiveFrameRectFlag()) {
        recordingCanvas->Translate(imageRenderPosition_.GetX() * -1, imageRenderPosition_.GetY() * -1);
        Rosen::Drawing::AdaptiveImageInfo rsImageInfo = { fitNum, repeatNum,
            { radii_[0], radii_[1], radii_[2], radii_[3] }, scale_, 0, rsImage->GetCompressWidth(),
            rsImage->GetCompressHeight() };
        recordingCanvas->AttachBrush(brush);
        recordingCanvas->DrawImageWithParm(rsImage->GetImage(), rsImage->GetCompressData(), rsImageInfo, options_);
        recordingCanvas->DetachBrush();
        rsImage->SetCompressData(nullptr, 0, 0);
        return;
#endif
    }
    bool isLoading =
        ((imageLoadingStatus_ == ImageLoadingStatus::LOADING) || (imageLoadingStatus_ == ImageLoadingStatus::UPDATING));
    Rect scaledSrcRect = isLoading ? currentSrcRect_ : srcRect_;

    if (sourceInfo_.IsValid() && imageObj_ && (imageObj_->GetFrameCount() == 1)) {
#ifndef USE_ROSEN_DRAWING
        Size sourceSize = (skImage ? Size(skImage->GetWidth(), skImage->GetHeight()) : Size());
#else
        Size sourceSize = (rsImage ? Size(rsImage->GetWidth(), rsImage->GetHeight()) : Size());
#endif
        // calculate srcRect that matches the real image source size
        // note that gif doesn't do resize, so gif does not need to recalculate
        scaledSrcRect = RecalculateSrcRect(sourceSize);
        scaledSrcRect.ApplyScaleAndRound(currentResizeScale_);
    }

    Rect realDstRect = paintRect + offset;

    if (imageRepeat_ != ImageRepeat::NO_REPEAT) {
#ifndef USE_ROSEN_DRAWING
        DrawImageOnCanvas(scaledSrcRect, realDstRect, paint, canvas);
#else
        DrawImageOnCanvas(scaledSrcRect, realDstRect, brush, canvas);
#endif
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto skSrcRect =
        SkRect::MakeXYWH(scaledSrcRect.Left(), scaledSrcRect.Top(), scaledSrcRect.Width(), scaledSrcRect.Height());
    auto skDstRect = SkRect::MakeXYWH(realDstRect.Left() - imageRenderPosition_.GetX(),
        realDstRect.Top() - imageRenderPosition_.GetY(), realDstRect.Width(), realDstRect.Height());

    canvas->drawImageRect(
        skImage->GetImage(), skSrcRect, skDstRect, options_, &paint, SkCanvas::kFast_SrcRectConstraint);
#else
    auto srcRect = RSRect(scaledSrcRect.Left(), scaledSrcRect.Top(), scaledSrcRect.Right(), scaledSrcRect.Bottom());
    auto dstRect =
        RSRect(realDstRect.Left() - imageRenderPosition_.GetX(), realDstRect.Top() - imageRenderPosition_.GetY(),
            realDstRect.Right() - imageRenderPosition_.GetX(), realDstRect.Bottom() - imageRenderPosition_.GetY());
    canvas->AttachBrush(brush);
    canvas->DrawImageRect(*rsImage->GetImage(), srcRect, dstRect, options_);
    canvas->DetachBrush();
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::DrawImageOnCanvas(
    const Rect& srcRect, const Rect& dstRect, const SkPaint& paint, SkCanvas* canvas) const
{
#ifdef OHOS_PLATFORM
    auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas);

    auto skSrcRect =
        SkRect::MakeXYWH(Round(srcRect.Left()), Round(srcRect.Top()), Round(srcRect.Width()), Round(srcRect.Height()));
    // only transform one time, set skDstRect.top and skDstRect.left to 0.
    auto skDstRect = SkRect::MakeXYWH(0, 0, dstRect.Width(), dstRect.Height());

    // initialize a transform matrix
    SkScalar scaleX = skDstRect.width() / skSrcRect.width();
    SkScalar scaleY = skDstRect.height() / skSrcRect.height();
    SkScalar transX = dstRect.Left() - imageRenderPosition_.GetX();
    SkScalar transY = dstRect.Top() - imageRenderPosition_.GetY();
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        // flip the image algin x direction.
        scaleX = -1 * scaleX;
        transX = skDstRect.left() + skDstRect.width();
    }
    SkScalar skewX = 0;
    SkScalar skewY = 0;
    SkScalar pers0 = 0;
    SkScalar pers1 = 0;
    SkScalar pers2 = 1;
    auto sampleMatrix = SkMatrix::MakeAll(scaleX, skewX, transX, skewY, scaleY, transY, pers0, pers1, pers2);

    recordingCanvas->save();
    recordingCanvas->concat(sampleMatrix);
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (skImage && skImage->GetImage()) {
        recordingCanvas->drawImageRect(
            skImage->GetImage(), skSrcRect, skDstRect, options_, &paint, SkCanvas::kFast_SrcRectConstraint);
    }
    recordingCanvas->restore();
#endif
}
#else
void RosenRenderImage::DrawImageOnCanvas(
    const Rect& srcRect, const Rect& dstRect, const RSBrush& brush, RSCanvas* canvas) const
{
#ifdef OHOS_PLATFORM
    auto recordingCanvas = static_cast<RSRecordingCanvas*>(canvas);
    auto drSrcRect =
        RSRect(Round(srcRect.Left()), Round(srcRect.Top()), Round(srcRect.Right()), Round(srcRect.Bottom()));
    // only transform one time, set skDstRect.top and skDstRect.left to 0.
    auto drDstRect = RSRect(0, 0, dstRect.Width(), dstRect.Height());

    // initialize a transform matrix
    RSScalar scaleX = drDstRect.GetWidth() / drSrcRect.GetWidth();
    RSScalar scaleY = drDstRect.GetHeight() / drSrcRect.GetHeight();
    RSScalar transX = dstRect.Left() - imageRenderPosition_.GetX();
    RSScalar transY = dstRect.Top() - imageRenderPosition_.GetY();
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        // flip the image algin x direction.
        scaleX = -1 * scaleX;
        transX = drDstRect.GetLeft() + drDstRect.GetWidth();
    }
    RSScalar skewX = 0;
    RSScalar skewY = 0;
    RSScalar pers0 = 0;
    RSScalar pers1 = 0;
    RSScalar pers2 = 1;
    RSMatrix sampleMatrix;
    sampleMatrix.SetMatrix(scaleX, skewX, transX, skewY, scaleY, transY, pers0, pers1, pers2);

    recordingCanvas->Save();
    recordingCanvas->ConcatMatrix(sampleMatrix);

    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (rsImage && rsImage->GetImage()) {
        recordingCanvas->AttachBrush(brush);
        recordingCanvas->DrawImageRect(
            *rsImage->GetImage(), drSrcRect, drDstRect, options_, RSSrcRectConstraint::FAST_SRC_RECT_CONSTRAINT);
        recordingCanvas->DetachBrush();
    }
    recordingCanvas->Restore();
#endif
}
#endif

#ifndef USE_ROSEN_DRAWING
bool RosenRenderImage::VerifySkImageDataFromPixmap(const RefPtr<PixelMap>& pixmap) const
{
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (!skImage || !skImage->GetImage()) {
        return false;
    }
    if ((skImage->GetWidth() <= 0 || skImage->GetHeight() <= 0)) {
        return false;
    }
    return true;
}
#else
bool RosenRenderImage::VerifyRSImageDataFromPixmap(const RefPtr<PixelMap>& pixmap) const
{
    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (!rsImage || !rsImage->GetImage()) {
        return false;
    }
    if ((rsImage->GetWidth() <= 0 || rsImage->GetHeight() <= 0)) {
        return false;
    }
    return true;
}
#endif

Rect RosenRenderImage::RecalculateSrcRect(const Size& realImageSize)
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

void RosenRenderImage::PaintBgImage(const std::shared_ptr<RSNode>& rsNode)
{
    if (!GetBackgroundImageFlag()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (currentDstRectList_.empty() || !skImage || !skImage->GetImage()) {
#else
    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (currentDstRectList_.empty() || !rsImage || !rsImage->GetImage()) {
#endif
        return;
    }

    if (!rsNode) {
        return;
    }
    auto rosenImage = std::make_shared<Rosen::RSImage>();
#ifndef USE_ROSEN_DRAWING
    rosenImage->SetImage(skImage->GetImage());
#else
    rosenImage->SetImage(rsImage->GetImage());
#endif
    rosenImage->SetImageRepeat(static_cast<int>(imageRepeat_));
    rsNode->SetBgImageWidth(imageRenderSize_.Width());
    rsNode->SetBgImageHeight(imageRenderSize_.Height());
    rsNode->SetBgImagePositionX(imageRenderPosition_.GetX());
    rsNode->SetBgImagePositionY(imageRenderPosition_.GetY());
    rsNode->SetBgImage(rosenImage);
}

bool RosenRenderImage::NeedUploadImageObjToGpu()
{
    bool sourceChange = sourceInfo_ != curSourceInfo_;
    bool newSourceCallLoadImage = (sourceChange && rawImageSize_.IsValid() && srcRect_.IsValid() &&
                                   (rawImageSizeUpdated_ && imageLoadingStatus_ != ImageLoadingStatus::LOADING) &&
                                   imageLoadingStatus_ != ImageLoadingStatus::LOAD_FAIL);
    if (imageLoadingStatus_ != ImageLoadingStatus::LOADING) {
        resizeCallLoadImage_ =
            !sourceChange && NeedResize() && (imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS);
    }
    return (newSourceCallLoadImage && (background_ || resizeTarget_.IsValid())) ||
           (resizeCallLoadImage_ && autoResize_);
}

void RosenRenderImage::UpLoadImageDataForPaint()
{
    if (NeedUploadImageObjToGpu()) {
        imageLoadingStatus_ = ImageLoadingStatus::LOADING;
        if (imageObj_) {
            previousResizeTarget_ = resizeTarget_;
            RosenRenderImage::UploadImageObjToGpuForRender(imageObj_, GetContext(), uploadSuccessCallback_,
                failedCallback_, resizeTarget_, forceResize_, syncMode_);
        }
    }
}

void RosenRenderImage::UploadImageObjToGpuForRender(const RefPtr<ImageObject>& imageObj,
    const WeakPtr<PipelineContext> context, UploadSuccessCallback uploadSuccessCallback, FailedCallback failedCallback,
    Size resizeTarget, bool forceResize, bool syncMode)
{
    if (!imageObj) {
        return;
    }
    imageObj->UploadToGpuForRender(context, uploadSuccessCallback, failedCallback, resizeTarget, forceResize, syncMode);
}

void RosenRenderImage::UpdateData(const std::string& uri, const std::vector<uint8_t>& memData)
{
    if (uri != sourceInfo_.GetSrc()) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto skData = SkData::MakeWithCopy(memData.data(), memData.size());
    if (!skData) {
#else
    auto rsData = std::make_shared<RSData>();
    rsData->BuildWithCopy(memData.data(), memData.size());
    if (!rsData) {
#endif
        return;
    }
    if (sourceInfo_.IsSvg()) {
#ifndef USE_ROSEN_DRAWING
        PaintSVGImage(skData, true);
#else
        PaintSVGImage(rsData, true);
#endif
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto codec = SkCodec::MakeFromData(skData);
#else
    auto skData = SkData::MakeWithoutCopy(rsData->GetData(), rsData->GetSize());
    auto codec = SkCodec::MakeFromData(skData);
#endif
    if (!codec) {
        return;
    }

    auto context = GetContext().Upgrade();
    if (!context) {
        return;
    }
#ifndef USE_ROSEN_DRAWING
    auto ImageObj = ImageObject::BuildImageObject(sourceInfo_, context, skData, useSkiaSvg_);
#else
    auto ImageObj = ImageObject::BuildImageObject(sourceInfo_, context, rsData, useSkiaSvg_);
#endif
    if (!ImageObj) {
        return;
    }
    ImageObjReady(ImageObj);
}

void RosenRenderImage::SetClipRadius()
{
#ifndef USE_ROSEN_DRAWING
    SetSkRadii(topLeftRadius_, radii_[SkRRect::kUpperLeft_Corner]);
    SetSkRadii(topRightRadius_, radii_[SkRRect::kUpperRight_Corner]);
    SetSkRadii(bottomLeftRadius_, radii_[SkRRect::kLowerLeft_Corner]);
    SetSkRadii(bottomRightRadius_, radii_[SkRRect::kLowerRight_Corner]);
#else
    SetRadii(topLeftRadius_, radii_[RSRoundRect::CornerPos::TOP_LEFT_POS]);
    SetRadii(topRightRadius_, radii_[RSRoundRect::CornerPos::TOP_RIGHT_POS]);
    SetRadii(bottomLeftRadius_, radii_[RSRoundRect::CornerPos::BOTTOM_LEFT_POS]);
    SetRadii(bottomRightRadius_, radii_[RSRoundRect::CornerPos::BOTTOM_RIGHT_POS]);
#endif
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::SetSkRadii(const Radius& radius, SkVector& radii)
#else
void RosenRenderImage::SetRadii(const Radius& radius, RSPoint& radii)
#endif
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    double dipScale = context->GetDipScale();
#ifndef USE_ROSEN_DRAWING
    radii.set(SkDoubleToScalar(std::max(radius.GetX().ConvertToPx(dipScale), 0.0)),
        SkDoubleToScalar(std::max(radius.GetY().ConvertToPx(dipScale), 0.0)));
#else
    radii = { static_cast<RSScalar>(std::max(radius.GetX().ConvertToPx(dipScale), 0.0)),
        static_cast<RSScalar>(std::max(radius.GetY().ConvertToPx(dipScale), 0.0)) };
#endif
}

Size RosenRenderImage::MeasureForPixmap()
{
    return rawImageSize_;
}

Size RosenRenderImage::MeasureForSvgImage()
{
    return imageComponentSize_;
}

Size RosenRenderImage::MeasureForNormalImage()
{
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

Size RosenRenderImage::Measure()
{
    if (imageObj_) {
        return imageObj_->MeasureForImage(AceType::Claim(this));
    }
    return Size();
}

void RosenRenderImage::OnHiddenChanged(bool hidden)
{
    if (hidden) {
        if (imageObj_ && imageObj_->GetFrameCount() > 1) {
            imageObj_->Pause();
        } else if (sourceInfo_.GetSrcType() != SrcType::MEMORY) {
            CancelBackgroundTasks();
        }
    } else {
        if (imageObj_ && imageObj_->GetFrameCount() > 1 && GetVisible()) {
            imageObj_->Resume();
        } else if (backgroundTaskCanceled_) {
            backgroundTaskCanceled_ = false;
            if (sourceInfo_.GetSrcType() == SrcType::MEMORY) {
            }
            imageLoadingStatus_ = ImageLoadingStatus::UNLOADED;
            FetchImageObject();
        }
    }
}

void RosenRenderImage::CancelBackgroundTasks()
{
    if (fetchImageObjTask_) {
        backgroundTaskCanceled_ = fetchImageObjTask_.Cancel(false);
    }
    if (imageObj_) {
        backgroundTaskCanceled_ = imageObj_->CancelBackgroundTasks();
    }
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::PaintSVGImage(const sk_sp<SkData>& skData, bool onlyLayoutSelf)
#else
void RosenRenderImage::PaintSVGImage(const std::shared_ptr<RSData>& drawingData, bool onlyLayoutSelf)
#endif
{
    imageLoadingStatus_ = ImageLoadingStatus::LOADING;
    auto successCallback = [svgImageWeak = AceType::WeakClaim(this), onlyLayoutSelf](const sk_sp<SkSVGDOM>& svgDom) {
        auto svgImage = svgImageWeak.Upgrade();
        if (!svgImage) {
            return;
        }
        svgImage->skiaDom_ = svgDom;
        svgImage->image_ = nullptr;
        svgImage->imageSizeForEvent_ = svgImage->Measure();
        svgImage->UpdateLoadSuccessState();
        svgImage->MarkNeedLayout(onlyLayoutSelf);
    };
    auto failedCallback = [svgImageWeak = AceType::WeakClaim(this)]() {
        auto svgImage = svgImageWeak.Upgrade();
        if (svgImage) {
            // if Upgrade fail, just callback with nullptr
            svgImage->ImageObjFailed("SVG data may be broken, please check the SVG file.");
        }
    };
#ifndef USE_ROSEN_DRAWING
    SkColorEx skColor;
    auto fillColor = sourceInfo_.GetFillColor();
    if (fillColor.has_value()) {
        skColor.color = fillColor.value().GetValue();
        skColor.valid = 1;
    }
    ImageProvider::GetSVGImageDOMAsyncFromData(
        skData, successCallback, failedCallback, GetContext(), skColor.value, onPostBackgroundTask_);
#else
    DrawingColorEx drawingColor;
    auto fillColor = sourceInfo_.GetFillColor();
    if (fillColor.has_value()) {
        drawingColor.color = fillColor.value().GetValue();
        drawingColor.valid = 1;
    }
    ImageProvider::GetSVGImageDOMAsyncFromData(
        drawingData, successCallback, failedCallback, GetContext(), drawingColor.value, onPostBackgroundTask_);
#endif
    MarkNeedLayout();
}

#ifndef USE_ROSEN_DRAWING
void RosenRenderImage::DrawSVGImage(const Offset& offset, SkCanvas* canvas)
#else
void RosenRenderImage::DrawSVGImage(const Offset& offset, RSCanvas* canvas)
#endif
{
    if (!skiaDom_) {
        return;
    }
    Size layoutSize = GetLayoutSize();
    Size imageSize(skiaDom_->containerSize().width(), skiaDom_->containerSize().height());
    if (layoutSize.IsInfinite() || !layoutSize.IsValid()) {
        if (imageSize.IsInfinite() || !imageSize.IsValid()) {
            return;
        }
        // when layout size is invalid, use svg's own size
        layoutSize = imageSize;
    }

#ifndef USE_ROSEN_DRAWING
    canvas->translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));

    auto width = static_cast<float>(layoutSize.Width());
    auto height = static_cast<float>(layoutSize.Height());
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        canvas->translate(width, 0);
        canvas->scale(-1, 1);
    }
    canvas->clipRect({ 0, 0, width, height }, SkClipOp::kIntersect, true);
    if (imageSize.IsValid() && !imageSize.IsInfinite()) {
        // scale svg to layout size
        float scale = std::min(width / imageSize.Width(), height / imageSize.Height());
        canvas->scale(scale, scale);
    } else {
        skiaDom_->setContainerSize({ width, height });
    }
    skiaDom_->render(canvas);
#else
    canvas->Translate(static_cast<float>(offset.GetX()), static_cast<float>(offset.GetY()));

    auto width = static_cast<float>(layoutSize.Width());
    auto height = static_cast<float>(layoutSize.Height());
    if (matchTextDirection_ && GetTextDirection() == TextDirection::RTL) {
        canvas->Translate(width, 0);
        canvas->Scale(-1, 1);
    }
    canvas->ClipRect(RSRect(0, 0, width, height), RSClipOp::INTERSECT, true);
    if (imageSize.IsValid() && !imageSize.IsInfinite()) {
        // scale svg to layout size
        float scale = std::min(width / imageSize.Width(), height / imageSize.Height());
        canvas->Scale(scale, scale);
    } else {
        skiaDom_->setContainerSize({ width, height });
    }
    canvas->DrawSVGDOM(skiaDom_);
#endif
}

void RosenRenderImage::DrawSVGImageCustom(RenderContext& context, const Offset& offset)
{
    if (svgRenderTree_.root) {
        PaintChild(svgRenderTree_.root, context, offset);
    }
}

void RosenRenderImage::UpdateLoadSuccessState()
{
    imageLoadingStatus_ = ImageLoadingStatus::LOAD_SUCCESS;
    if (!imageObj_) {
        return;
    }
    auto currentFrameCount = imageObj_->GetFrameCount();
    if ((!sourceInfo_.IsSvg() && currentFrameCount == 1) || (currentFrameCount > 1 && curSourceInfo_ != sourceInfo_)) {
        FireLoadEvent(imageSizeForEvent_);
    }
    // alt_image has empty imageAlt_, then mark the parent needs render
    if ((currentFrameCount > 1 && curSourceInfo_ != sourceInfo_) || imageAlt_.empty()) {
        auto parent = GetParent().Upgrade();
        if (parent) {
            parent->MarkNeedRender();
        }
    }
    if (currentFrameCount != frameCount_) {
        frameCount_ = currentFrameCount;
    }

    currentSrcRect_ = srcRect_;
    curSourceInfo_ = sourceInfo_;
    formerRawImageSize_ = rawImageSize_;
    forceResize_ = false;
    retryCnt_ = 0;
    currentResizeScale_ = resizeScale_;
    if (renderAltImage_) {
        RemoveChild(renderAltImage_);
        renderAltImage_ = nullptr;
        MarkNeedLayout();
        return;
    }
    proceedPreviousLoading_ = false;
    rawImageSizeUpdated_ = false;
    MarkNeedRender();
}

void RosenRenderImage::UpdateRenderAltImage(const RefPtr<Component>& component)
{
    const RefPtr<ImageComponent> image = AceType::DynamicCast<ImageComponent>(component);
    if (!image) {
        return;
    }
    bool imageAltValid = !imageAlt_.empty() && (imageAlt_ != IMAGE_ALT_BLANK);
    if (!imageAltValid || imageLoadingStatus_ == ImageLoadingStatus::LOAD_SUCCESS) {
        return;
    }
    // note that alt image component must be a copy
    RefPtr<ImageComponent> altImageComponent = ImageComponent::MakeFromOtherWithoutSourceAndEvent(image);
    altImageComponent->SetSrc(imageAlt_);
    altImageComponent->SetAlt("");
    if (renderAltImage_) {
        renderAltImage_->Update(altImageComponent);
        return;
    }
    renderAltImage_ = AceType::DynamicCast<RenderImage>(altImageComponent->CreateRenderNode());
    renderAltImage_->Attach(GetContext());
    renderAltImage_->Update(altImageComponent);
    AddChild(renderAltImage_);
}

bool RosenRenderImage::MaybeRelease()
{
    auto context = GetContext().Upgrade();
    if (context && context->GetRenderFactory() && context->GetRenderFactory()->GetRenderImageFactory()->Recycle(this)) {
        ClearRenderObject();
        return false;
    }
    return true;
}

void RosenRenderImage::ClearRenderObject()
{
    RenderImage::ClearRenderObject();
    CancelBackgroundTasks();
    curSourceInfo_.Reset();
    image_ = nullptr;
    formerRawImageSize_ = { 0.0, 0.0 };
    imageObj_ = nullptr;
    skiaDom_ = nullptr;
    svgDom_ = nullptr;
    svgRenderTree_.ClearRenderObject();
}

bool RosenRenderImage::IsSourceWideGamut() const
{
#ifndef USE_ROSEN_DRAWING
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (sourceInfo_.IsSvg() || !skImage || !skImage->GetImage()) {
        return false;
    }
    return ImageProvider::IsWideGamut(skImage->GetImage()->refColorSpace());
#else
    auto rsImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (sourceInfo_.IsSvg() || !rsImage || !rsImage->GetImage()) {
        return false;
    }
    return ImageProvider::IsWideGamut(RSColorSpace::CreateRefImage(*rsImage->GetImage()));
#endif
}

bool RosenRenderImage::RetryLoading()
{
    if (!sourceInfo_.IsValid()) {
        return false;
    }
    if (retryCnt_++ > 5) { // retry loading 5 times at most
        return false;
    }

    if (rawImageSizeUpdated_ && imageObj_) { // case when image size is ready, only have to do loading again
        imageObj_->UploadToGpuForRender(
            GetContext(), uploadSuccessCallback_, failedCallback_, resizeTarget_, forceResize_);
        return true;
    }
    // case when the fail event is triggered by GetImageSize, do GetImageSize again
    auto context = GetContext().Upgrade();
    if (!context) {
        return false;
    }
    auto frontend = context->GetFrontend();
    if (!frontend) {
        return false;
    }
    bool syncMode = context->IsBuildingFirstPage() && frontend->GetType() == FrontendType::JS_CARD &&
                    sourceInfo_.GetSrcType() != SrcType::NETWORK;
    ImageProvider::FetchImageObject(sourceInfo_, imageObjSuccessCallback_, uploadSuccessCallback_, failedCallback_,
        GetContext(), syncMode, useSkiaSvg_, autoResize_, onPostBackgroundTask_);
    return true;
}

#ifndef USE_ROSEN_DRAWING
SkImageInfo RosenRenderImage::MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    SkColorType ct = PixelFormatToSkColorType(pixmap);
    SkAlphaType at = AlphaTypeToSkAlphaType(pixmap);
    sk_sp<SkColorSpace> cs = ColorSpaceToSkColorSpace(pixmap);
    return SkImageInfo::Make(pixmap->GetWidth(), pixmap->GetHeight(), ct, at, cs);
}
#else
RSBitmapFormat RosenRenderImage::MakeRSBitmapFormatInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    return { PixelFormatToRSColorType(pixmap), AlphaTypeToRSAlphaType(pixmap) };
}
#endif

#ifndef USE_ROSEN_DRAWING
sk_sp<SkColorSpace> RosenRenderImage::ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return SkColorSpace::MakeSRGB(); // Media::PixelMap has not support wide gamut yet.
}
#endif

#ifndef USE_ROSEN_DRAWING
SkAlphaType RosenRenderImage::AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return SkAlphaType::kUnknown_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return SkAlphaType::kOpaque_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return SkAlphaType::kPremul_SkAlphaType;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return SkAlphaType::kUnpremul_SkAlphaType;
        default:
            return SkAlphaType::kUnknown_SkAlphaType;
    }
}
#else
Rosen::Drawing::AlphaType RosenRenderImage::AlphaTypeToRSAlphaType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetAlphaType()) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNKNOWN;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return Rosen::Drawing::AlphaType::ALPHATYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNPREMUL;
        default:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNKNOWN;
    }
}
#endif

#ifndef USE_ROSEN_DRAWING
SkColorType RosenRenderImage::PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return SkColorType::kRGB_565_SkColorType;
        case PixelFormat::RGBA_8888:
            return SkColorType::kRGBA_8888_SkColorType;
        case PixelFormat::BGRA_8888:
            return SkColorType::kBGRA_8888_SkColorType;
        case PixelFormat::ALPHA_8:
            return SkColorType::kAlpha_8_SkColorType;
        case PixelFormat::RGBA_F16:
            return SkColorType::kRGBA_F16_SkColorType;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return SkColorType::kUnknown_SkColorType;
    }
}
#else
Rosen::Drawing::ColorType RosenRenderImage::PixelFormatToRSColorType(const RefPtr<PixelMap>& pixmap)
{
    switch (pixmap->GetPixelFormat()) {
        case PixelFormat::RGB_565:
            return Rosen::Drawing::ColorType::COLORTYPE_RGB_565;
        case PixelFormat::RGBA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_RGBA_8888;
        case PixelFormat::BGRA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_BGRA_8888;
        case PixelFormat::ALPHA_8:
            return Rosen::Drawing::ColorType::COLORTYPE_ALPHA_8;
        case PixelFormat::RGBA_F16:
            return Rosen::Drawing::ColorType::COLORTYPE_RGBA_F16;
        case PixelFormat::UNKNOWN:
        case PixelFormat::ARGB_8888:
        case PixelFormat::RGB_888:
        case PixelFormat::NV21:
        case PixelFormat::NV12:
        case PixelFormat::CMYK:
        default:
            return RSColorType::COLORTYPE_UNKNOWN;
    }
}
#endif

void RosenRenderImage::OnAppHide()
{
    isAppOnShow_ = false;
    if (imageObj_) {
        imageObj_->Pause();
    }
}

void RosenRenderImage::OnAppShow()
{
    isAppOnShow_ = true;
    if (imageObj_) {
        imageObj_->Resume();
    }
}

// pause image when not visible
void RosenRenderImage::OnVisibleChanged()
{
    if (imageObj_) {
        if (GetVisible()) {
            imageObj_->Resume();
        } else {
            imageObj_->Pause();
        }
    }
}

#ifndef USE_ROSEN_DRAWING
RefPtr<PixelMap> RosenRenderImage::GetPixmapFromSkImage()
{
    auto skImage = AceType::DynamicCast<NG::SkiaImage>(image_);
    if (!skImage || !skImage->GetImage()) {
        return nullptr;
    }
    auto image = skImage->GetImage();
    auto rasterizedImage = image->makeRasterImage();
    SkPixmap srcPixmap;
    if (!rasterizedImage->peekPixels(&srcPixmap)) {
        return nullptr;
    }
    SkPixmap newSrcPixmap = CloneSkPixmap(srcPixmap);
    auto addr = newSrcPixmap.addr32();
    int32_t width = static_cast<int32_t>(newSrcPixmap.width());
    int32_t height = static_cast<int32_t>(newSrcPixmap.height());
    auto length = width * height;
    return PixelMap::ConvertSkImageToPixmap(addr, length, width, height);
}

SkPixmap RosenRenderImage::CloneSkPixmap(SkPixmap& srcPixmap)
{
    SkImageInfo dstImageInfo = SkImageInfo::Make(srcPixmap.info().width(), srcPixmap.info().height(),
        SkColorType::kBGRA_8888_SkColorType, srcPixmap.alphaType());
    auto dstPixels = std::make_unique<uint8_t[]>(srcPixmap.computeByteSize());
    SkPixmap dstPixmap(dstImageInfo, dstPixels.release(), srcPixmap.rowBytes());

    SkBitmap dstBitmap;
    if (!dstBitmap.installPixels(dstPixmap)) {
        return dstPixmap;
    }
    if (!dstBitmap.writePixels(srcPixmap, 0, 0)) {
        return dstPixmap;
    }
    return dstPixmap;
}
#else
RefPtr<PixelMap> RosenRenderImage::GetPixmapFromDrawingImage()
{
    auto rosenImage = AceType::DynamicCast<NG::DrawingImage>(image_);
    if (!rosenImage || !rosenImage->GetImage()) {
        return nullptr;
    }
    auto rsImage = rosenImage->GetImage();
    RSBitmapFormat rsBitmapFormat = { RSColorType::COLORTYPE_BGRA_8888, rsImage->GetAlphaType() };
    RSBitmap rsBitmap;
    if (!rsBitmap.Build(rsImage->GetWidth(), rsImage->GetHeight(), rsBitmapFormat)) {
        LOGW("rsBitmap build fail.");
        return nullptr;
    }
    CHECK_NULL_RETURN(rsImage->ReadPixels(rsBitmap, 0, 0), nullptr);
    const auto* addr = static_cast<uint32_t*>(rsBitmap.GetPixels());
    auto width = static_cast<int32_t>(rsBitmap.GetWidth());
    auto height = static_cast<int32_t>(rsBitmap.GetHeight());
    int32_t length = width * height;
    return PixelMap::ConvertSkImageToPixmap(addr, length, width, height);
}
#endif
} // namespace OHOS::Ace
