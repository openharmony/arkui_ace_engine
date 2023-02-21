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

#include "core/components_ng/render/adapter/skia_canvas_image.h"

#include "third_party/skia/include/core/SkColorFilter.h"

#include "base/image/pixel_map.h"
#include "core/components_ng/render/drawing.h"
#ifdef ENABLE_ROSEN_BACKEND
#include "pipeline/rs_recording_canvas.h"
#endif

namespace OHOS::Ace::NG {
namespace {
constexpr uint8_t RADIUS_POINTS_SIZE = 4;

const float GRAY_COLOR_MATRIX[20] = { 0.30f, 0.59f, 0.11f, 0, 0, // red
    0.30f, 0.59f, 0.11f, 0, 0,                                   // green
    0.30f, 0.59f, 0.11f, 0, 0,                                   // blue
    0, 0, 0, 1.0f, 0 };                                          // alpha transparency

SkPixmap CloneSkPixmap(SkPixmap& srcPixmap)
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
} // namespace

RefPtr<CanvasImage> CanvasImage::Create(void* rawImage)
{
#ifdef FLUTTER_2_5
    return AceType::MakeRefPtr<SkiaCanvasImage>();
#else
    auto* imageRef = reinterpret_cast<fml::RefPtr<flutter::CanvasImage>*>(rawImage);
    CHECK_NULL_RETURN(imageRef, nullptr);

    return AceType::MakeRefPtr<SkiaCanvasImage>(*imageRef);
#endif
}

SkImageInfo SkiaCanvasImage::MakeSkImageInfoFromPixelMap(const RefPtr<PixelMap>& pixmap)
{
    SkColorType colorType = PixelFormatToSkColorType(pixmap);
    SkAlphaType alphaType = AlphaTypeToSkAlphaType(pixmap);
    sk_sp<SkColorSpace> colorSpace = ColorSpaceToSkColorSpace(pixmap);
    return SkImageInfo::Make(pixmap->GetWidth(), pixmap->GetHeight(), colorType, alphaType, colorSpace);
}

sk_sp<SkColorSpace> SkiaCanvasImage::ColorSpaceToSkColorSpace(const RefPtr<PixelMap>& pixmap)
{
    return SkColorSpace::MakeSRGB(); // Media::PixelMap has not support wide gamut yet.
}

SkAlphaType SkiaCanvasImage::AlphaTypeToSkAlphaType(const RefPtr<PixelMap>& pixmap)
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

SkColorType SkiaCanvasImage::PixelFormatToSkColorType(const RefPtr<PixelMap>& pixmap)
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

void SkiaCanvasImage::ReplaceSkImage(flutter::SkiaGPUObject<SkImage> newSkGpuObjSkImage)
{
#ifndef FLUTTER_2_5
    image_->set_image(std::move(newSkGpuObjSkImage));
#endif
}

int32_t SkiaCanvasImage::GetWidth() const
{
#ifdef FLUTTER_2_5
    return 0;
#else
    return image_->image() ? image_->width() : image_->compressWidth();
#endif
}

int32_t SkiaCanvasImage::GetHeight() const
{
#ifdef FLUTTER_2_5
    return 0;
#else
    return image_->image() ? image_->height() : image_->compressHeight();
#endif
}

RefPtr<CanvasImage> SkiaCanvasImage::Clone()
{
    auto clone = MakeRefPtr<SkiaCanvasImage>(image_);
    clone->uniqueId_ = uniqueId_;
    return clone;
}

void SkiaCanvasImage::AddFilter(SkPaint& paint)
{
    auto config = GetPaintConfig();
    paint.setFilterQuality(SkFilterQuality(config.imageInterpolation_));
    if (ImageRenderMode::TEMPLATE == config.renderMode_ || config.colorFilter_) {
        RSColorMatrix colorFilterMatrix;
        if (config.colorFilter_) {
            paint.setColorFilter(SkColorFilters::Matrix(config.colorFilter_->data()));
        } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
            paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
        }
    }
}

RefPtr<PixelMap> SkiaCanvasImage::GetPixelMap()
{
    CHECK_NULL_RETURN(GetCanvasImage(), nullptr);
    auto rasterImage = GetCanvasImage()->makeRasterImage();
    SkPixmap srcPixmap;
    if (!rasterImage->peekPixels(&srcPixmap)) {
        return nullptr;
    }
    SkPixmap newSrcPixmap = CloneSkPixmap(srcPixmap);
    const auto* addr = newSrcPixmap.addr32();
    auto width = static_cast<int32_t>(newSrcPixmap.width());
    auto height = static_cast<int32_t>(newSrcPixmap.height());
    int32_t length = width * height;
    return PixelMap::ConvertSkImageToPixmap(addr, length, width, height);
}

void SkiaCanvasImage::ClipRRect(RSCanvas& canvas, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    std::vector<RSPoint> radius(RADIUS_POINTS_SIZE);
    for (size_t i = 0; i < radius.size(); ++i) {
        radius[i] = RSPoint(radiusXY[i].GetX(), radiusXY[i].GetY());
    }
    RSRoundRect rRect(dstRect, radius);
    canvas.ClipRoundRect(rRect, RSClipOp::INTERSECT);
}

void SkiaCanvasImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto image = GetCanvasImage();
    CHECK_NULL_VOID(image || GetCompressData());
    RSImage rsImage(&image);
    RSSamplingOptions options;
#ifdef ENABLE_ROSEN_BACKEND
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    if (rsCanvas == nullptr) {
        canvas.DrawImageRect(rsImage, srcRect, dstRect, options);
        return;
    }
    auto skCanvas = rsCanvas->ExportSkCanvas();
    if (skCanvas == nullptr) {
        canvas.DrawImageRect(rsImage, srcRect, dstRect, options);
        return;
    }
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    if (recordingCanvas == nullptr) {
        canvas.DrawImageRect(rsImage, srcRect, dstRect, options);
        return;
    }
    SkPaint paint;
    AddFilter(paint);
    SkVector radii[RADIUS_POINTS_SIZE] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    if (radiusXY.size() == RADIUS_POINTS_SIZE) {
        radii[SkRRect::kUpperLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetY(), 0.0f)));
        radii[SkRRect::kUpperRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetY(), 0.0f)));
    }
    recordingCanvas->ClipAdaptiveRRect(radii);
    auto config = GetPaintConfig();
    if (config.imageFit_ == ImageFit::TOP_LEFT) {
        SkAutoCanvasRestore acr(recordingCanvas, true);
        auto skSrcRect = SkRect::MakeXYWH(srcRect.GetLeft(), srcRect.GetTop(), srcRect.GetWidth(), srcRect.GetHeight());
        auto skDstRect = SkRect::MakeXYWH(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetWidth(), dstRect.GetHeight());
        recordingCanvas->concat(SkMatrix::MakeRectToRect(skSrcRect, skDstRect, SkMatrix::kFill_ScaleToFit));
    }
    Rosen::RsImageInfo rsImageInfo((int)(config.imageFit_), (int)(config.imageRepeat_), radii, 1.0, GetUniqueID(),
        GetCompressWidth(), GetCompressHeight());
    auto data = GetCompressData();
    recordingCanvas->DrawImageWithParm(image, std::move(data), rsImageInfo, paint);
#else
    canvas.DrawImageRect(rsImage, srcRect, dstRect, options);
#endif
}

bool SkiaCanvasImage::DrawCompressedImage(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    CHECK_NULL_RETURN_NOLOG(GetCompressData(), false);

#ifdef ENABLE_ROSEN_BACKEND
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_RETURN(rsCanvas, false);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_RETURN(skCanvas, false);
    auto recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_RETURN(recordingCanvas, false);

    SkPaint paint;
    AddFilter(paint);
    SkVector radii[RADIUS_POINTS_SIZE] = { { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 }, { 0.0, 0.0 } };
    if (radiusXY.size() == RADIUS_POINTS_SIZE) {
        radii[SkRRect::kUpperLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperLeft_Corner].GetY(), 0.0f)));
        radii[SkRRect::kUpperRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kUpperRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerLeft_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerRight_Corner].GetY(), 0.0f)));
        radii[SkRRect::kLowerRight_Corner].set(
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetX(), 0.0f)),
            SkFloatToScalar(std::max(radiusXY[SkRRect::kLowerLeft_Corner].GetY(), 0.0f)));
    }
    recordingCanvas->ClipAdaptiveRRect(radii);
    auto config = GetPaintConfig();
    if (config.imageFit_ == ImageFit::TOP_LEFT) {
        SkAutoCanvasRestore acr(recordingCanvas, true);
        auto skSrcRect = SkRect::MakeXYWH(srcRect.GetLeft(), srcRect.GetTop(), srcRect.GetWidth(), srcRect.GetHeight());
        auto skDstRect = SkRect::MakeXYWH(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetWidth(), dstRect.GetHeight());
        recordingCanvas->concat(SkMatrix::MakeRectToRect(skSrcRect, skDstRect, SkMatrix::kFill_ScaleToFit));
    }

    Rosen::RsImageInfo rsImageInfo((int)(config.imageFit_), (int)(config.imageRepeat_), radii, 1.0, GetUniqueID(),
        GetCompressWidth(), GetCompressHeight());
    auto data = GetCompressData();
    recordingCanvas->DrawImageWithParm(nullptr, std::move(data), rsImageInfo, paint);
#endif
    return true;
}
} // namespace OHOS::Ace::NG
