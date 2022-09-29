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

#include "core/components_ng/pattern/custom_paint/canvas_paint_method.h"

#include "drawing/engine_adapter/skia_adapter/skia_canvas.h"

#include "core/components_ng/render/drawing.h"
#include "core/image/flutter_image_cache.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t IMAGE_CACHE_COUNT = 50;
} // namespace

CanvasDrawFunction CanvasPaintMethod::GetForegroundDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintFunc = [weak = WeakClaim(this), paintWrapper](RSCanvas& canvas) {
        auto customPaint = weak.Upgrade();
        if (customPaint) {
            customPaint->PaintCustomPaint(canvas, paintWrapper);
        }
    };

    return paintFunc;
}

void CanvasPaintMethod::PaintCustomPaint(RSCanvas& canvas, PaintWrapper* paintWrapper)
{
    SkCanvas* skCanvas = canvas.GetImpl<Rosen::Drawing::SkiaCanvas>()->ExportSkCanvas();
    auto contentSize = paintWrapper->GetContentSize();
    if (lastLayoutSize_ != contentSize) {
        CreateBitmap(contentSize);
        lastLayoutSize_.SetSizeT(contentSize);
    }
    auto viewScale = context_->GetViewScale();
    skCanvas_->scale(viewScale, viewScale);

    for (const auto& task : tasks_) {
        task(*this, paintWrapper);
    }
    skCanvas_->scale(1.0 / viewScale, 1.0 / viewScale);
    tasks_.clear();

    skCanvas->save();
    skCanvas->scale(1.0 / viewScale, 1.0 / viewScale);

    skCanvas->drawBitmap(canvasCache_, 0.0f, 0.0f);

    skCanvas->restore();
}

void CanvasPaintMethod::CreateBitmap(SizeF contentSize)
{
    auto viewScale = context_->GetViewScale();
    auto imageInfo = SkImageInfo::Make(contentSize.Width() * viewScale, contentSize.Height() * viewScale,
        SkColorType::kRGBA_8888_SkColorType, SkAlphaType::kUnpremul_SkAlphaType);
    canvasCache_.reset();
    cacheBitmap_.reset();
    canvasCache_.allocPixels(imageInfo);
    cacheBitmap_.allocPixels(imageInfo);
    canvasCache_.eraseColor(SK_ColorTRANSPARENT);
    cacheBitmap_.eraseColor(SK_ColorTRANSPARENT);
    skCanvas_ = std::make_unique<SkCanvas>(canvasCache_);
    cacheCanvas_ = std::make_unique<SkCanvas>(cacheBitmap_);
}

void CanvasPaintMethod::ImageObjReady(const RefPtr<ImageObject>& imageObj)
{
    imageObj_ = imageObj;
    if (imageObj_->IsSvg()) {
        skiaDom_ = AceType::DynamicCast<SvgSkiaImageObject>(imageObj_)->GetSkiaDom();
        currentSource_ = loadingSource_;
        Ace::CanvasImage canvasImage = canvasImage_;
        TaskFunc func = [canvasImage](CustomPaintPaintMethod& paintMethod, PaintWrapper* paintWrapper) {
            paintMethod.DrawImage(paintWrapper, canvasImage, 0, 0);
        };
        tasks_.emplace_back(func);
        return;
    }
    LOGE("image is not svg");
}

void CanvasPaintMethod::ImageObjFailed()
{
    imageObj_ = nullptr;
    skiaDom_ = nullptr;
}

sk_sp<SkImage> CanvasPaintMethod::GetImage(const std::string& src)
{
    if (!imageCache_) {
        imageCache_ = ImageCache::Create();
        imageCache_->SetCapacity(IMAGE_CACHE_COUNT);
    }
    auto cacheImage = imageCache_->GetCacheImage(src);
    if (cacheImage && cacheImage->imagePtr) {
        return cacheImage->imagePtr->image();
    }

    CHECK_NULL_RETURN(context_, nullptr);

    auto image = ImageProvider::GetSkImage(src, context_);
    if (image) {
        auto rasterizedImage = image->makeRasterImage();
        auto canvasImage = flutter::CanvasImage::Create();
        canvasImage->set_image({ rasterizedImage, renderTaskHolder_->unrefQueue });
        imageCache_->CacheImage(src, std::make_shared<CachedImage>(canvasImage));
        return rasterizedImage;
    }

    return image;
}

std::unique_ptr<Ace::ImageData> CanvasPaintMethod::GetImageData(
    double left, double top, double width, double height)
{
    double viewScale = 1.0;
    CHECK_NULL_RETURN(context_, nullptr);
    viewScale = context_->GetViewScale();
    // copy the bitmap to tempCanvas
    auto imageInfo =
        SkImageInfo::Make(width, height, SkColorType::kBGRA_8888_SkColorType, SkAlphaType::kOpaque_SkAlphaType);
    SkBitmap tempCache;
    double scaledLeft = left * viewScale;
    double scaledTop = top * viewScale;
    double dirtyWidth = width >= 0 ? width : 0;
    double dirtyHeight = height >= 0 ? height : 0;
    tempCache.allocPixels(imageInfo);
    int32_t size = dirtyWidth * dirtyHeight;
    bool isGpuEnable = false;
    const uint8_t* pixels = nullptr;
    SkCanvas tempCanvas(tempCache);
    auto srcRect = SkRect::MakeXYWH(scaledLeft, scaledTop, width * viewScale, height * viewScale);
    auto dstRect = SkRect::MakeXYWH(0.0, 0.0, dirtyWidth, dirtyHeight);

    if (!isGpuEnable) {
        tempCanvas.drawBitmapRect(canvasCache_, srcRect, dstRect, nullptr);
    }
    pixels = tempCache.pixmap().addr8();
    if (pixels == nullptr) {
        return nullptr;
    }
    std::unique_ptr<Ace::ImageData> imageData = std::make_unique<Ace::ImageData>();
    imageData->dirtyWidth = dirtyWidth;
    imageData->dirtyHeight = dirtyHeight;
    // a pixel include 4 data(blue, green, red, alpha)
    for (int i = 0; i < size * 4; i += 4) {
        auto blue = pixels[i];
        auto green = pixels[i + 1];
        auto red = pixels[i + 2];
        auto alpha = pixels[i + 3];
        imageData->data.emplace_back(Color::FromARGB(alpha, red, green, blue));
    }
    return imageData;
}

void CanvasPaintMethod::TransferFromImageBitmap(const RefPtr<OffscreenCanvasPattern>& offscreenCanvas)
{
    std::unique_ptr<Ace::ImageData> imageData =
        offscreenCanvas->GetImageData(0, 0, offscreenCanvas->GetWidth(), offscreenCanvas->GetHeight());
    Ace::ImageData* imageDataPtr = imageData.get();
    if (imageData != nullptr) {
        PutImageData(nullptr, *imageDataPtr);
    }
}
} // namespace OHOS::Ace::NG