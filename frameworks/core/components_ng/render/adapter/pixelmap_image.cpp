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

#include "core/components_ng/render/adapter/pixelmap_image.h"

#include "image_painter_utils.h"

#include "base/image/pixel_map.h"
#include "base/utils/utils.h"
#include "core/components_ng/image_provider/image_data.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"
#ifdef USE_ROSEN_DRAWING
#include "render_service_base/include/pipeline/rs_recording_canvas.h"
#endif
#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

namespace OHOS::Ace::NG {
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

bool ConvertSlice(const ImagePaintConfig& config, RectF& result, float rawImageWidth, float rawImageHeight)
{
    const auto& slice = config.resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    result.SetLeft(ConvertToPx(slice.left, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f));
    result.SetTop(ConvertToPx(slice.top, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f));
    auto rightSliceValue = ConvertToPx(slice.right, ScaleProperty::CreateScaleProperty(), rawImageWidth).value_or(0.0f);
    auto bottomSliceValue =
        ConvertToPx(slice.bottom, ScaleProperty::CreateScaleProperty(), rawImageHeight).value_or(0.0f);
    // illegal case if left position if larger than right, then rect has negative width
    if (GreatNotEqual(rawImageWidth - rightSliceValue - result.GetX(), 0.0f)) {
        result.SetWidth(rawImageWidth - rightSliceValue - result.GetX());
    } else {
        return false;
    }
    // same illegal case for height
    if (GreatNotEqual(rawImageHeight - bottomSliceValue - result.GetY(), 0.0f)) {
        result.SetHeight(rawImageHeight - bottomSliceValue - result.GetY());
    } else {
        return false;
    }
    return true;
}

#ifndef USE_ROSEN_DRAWING
void UpdateSKFilter(const ImagePaintConfig& config, SKPaint& paint)
{
    if (config.colorFilter_) {
        paint.setColorFilter(SkColorFilters::Matrix(config.colorFilter_->data()));
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        paint.setColorFilter(SkColorFilters::Matrix(GRAY_COLOR_MATRIX));
    }
}
#else
void UpdateRSFilter(const ImagePaintConfig& config, RSFilter& filter)
{
    if (config.colorFilter_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(config.colorFilter_->data());
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    } else if (ImageRenderMode::TEMPLATE == config.renderMode_) {
        RSColorMatrix colorMatrix;
        colorMatrix.SetArray(GRAY_COLOR_MATRIX);
        filter.SetColorFilter(RSRecordingColorFilter::CreateMatrixColorFilter(colorMatrix));
    }
}
#endif
} // namespace

RefPtr<CanvasImage> CanvasImage::Create(const RefPtr<PixelMap>& pixelMap)
{
    return AceType::MakeRefPtr<PixelMapImage>(pixelMap);
}

RefPtr<CanvasImage> PixelMapImage::Clone()
{
    return MakeRefPtr<PixelMapImage>(pixelMap_);
}

int32_t PixelMapImage::GetWidth() const
{
    auto pixmap = GetPixelMap();
    if (pixmap) {
        return pixmap->GetWidth();
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "pixelMap_ is nullptr, return width 0.");
    return 0;
}

int32_t PixelMapImage::GetHeight() const
{
    auto pixmap = GetPixelMap();
    if (pixmap) {
        return pixmap->GetHeight();
    }
    TAG_LOGW(AceLogTag::ACE_IMAGE, "rsCanvas is nullptr, return height 0.");
    return 0;
}

bool PixelMapImage::DrawImageNine(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    CHECK_NULL_RETURN(pixmap, false);
    const auto& config = GetPaintConfig();
    const auto& slice = GetPaintConfig().resizableSlice_;
    CHECK_NULL_RETURN(slice.Valid(), false);
    RectF centerRect;
    CHECK_NULL_RETURN(ConvertSlice(config, centerRect, pixmap->GetWidth(), pixmap->GetHeight()), false);
#ifdef ENABLE_ROSEN_BACKEND
#ifndef USE_ROSEN_DRAWING
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_RETURN(rsCanvas, false);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_RETURN(skCanvas, false);
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_RETURN(recordingCanvas, false);
    SkPaint paint;
    UpdateSKFilter(config, paint);

    auto radii = ImagePainterUtils::ToSkRadius(radiusXY);
    recordingCanvas->ClipAdaptiveRRect(radii.get());
    recordingCanvas->scale(config.scaleX_, config.scaleY_);
    SkIRect skCenterRect =
        SkIRect::MakeXYWH(centerRect.GetX(), centerRect.GetY(), centerRect.Width(), centerRect.Height());
    SkRect dst { dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom() };
    recordingCanvas->drawImageNine(pixmap->GetPixelMapSharedPtr(), skCenterRect, dst, paint);
    return true;
#endif
    RSBrush brush;
    auto filterMode = RSFilterMode::NEAREST;
    switch (config.imageInterpolation_) {
        case ImageInterpolation::LOW:
        case ImageInterpolation::MEDIUM:
            filterMode = RSFilterMode::LINEAR;
            break;
        case ImageInterpolation::HIGH:
        default:
            break;
    }

    auto filter = brush.GetFilter();
    UpdateRSFilter(config, filter);
    brush.SetFilter(filter);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radiusXY[ii].GetX(), radiusXY[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    RSRectI rsCenterRect(centerRect.GetX(), centerRect.GetY(), centerRect.GetX() + centerRect.Width(),
        centerRect.GetY() + centerRect.Height());
    std::shared_ptr<RSImage> rsImage = DrawingImage::MakeRSImageFromPixmap(pixmap);
    CHECK_NULL_RETURN(rsImage, false);
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawImageNine(rsImage.get(), rsCenterRect, dstRect, filterMode, &brush);
    recordingCanvas.DetachBrush();
    return true;
#endif
    return false;
}

void PixelMapImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    CHECK_NULL_VOID(pixmap);
    const auto& config = GetPaintConfig();

#ifdef ENABLE_ROSEN_BACKEND
#ifndef USE_ROSEN_DRAWING
    if (config.frameCount_ == 1 && config.resizableSlice_.Valid() &&
        DrawImageNine(canvas, srcRect, dstRect, radiusXY)) {
        return;
    }
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_VOID(recordingCanvas);
    SkPaint paint;

    SkSamplingOptions options;
    ImagePainterUtils::AddFilter(paint, options, config);
    auto radii = ImagePainterUtils::ToSkRadius(radiusXY);
    recordingCanvas->ClipAdaptiveRRect(radii.get());
    recordingCanvas->scale(config.scaleX_, config.scaleY_);

    Rosen::RsImageInfo rsImageInfo(
        static_cast<int>(config.imageFit_), static_cast<int>(config.imageRepeat_), radii.get(), 1.0, 0, 0, 0);
    recordingCanvas->DrawPixelMapWithParm(pixmap->GetPixelMapSharedPtr(), rsImageInfo, options, paint);
#else
    if (config.frameCount_ == 1 &&config.resizableSlice_.Valid() &&
        DrawImageNine(canvas, srcRect, dstRect, radiusXY)) {
        return;
    }
    RSBrush brush;
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radii[ii].GetX(), radii[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    CHECK_NULL_VOID(pixmap->GetPixelMapSharedPtr());
    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo = { static_cast<int32_t>(config.imageFit_),
        static_cast<int32_t>(config.imageRepeat_), { pointRadius[0], pointRadius[1], pointRadius[2], pointRadius[3] },
        1.0, 0, 0, 0 };
    recordingCanvas.AttachBrush(brush);
    if (SystemProperties::GetDebugPixelMapSaveEnabled()) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "pixmap, width=%{public}d * height=%{public}d", pixmap->GetWidth(),
            pixmap->GetHeight());
        pixmap->SavePixelMapToFile("_ToRS_");
    }
    recordingCanvas.DrawPixelMapWithParm(pixmap->GetPixelMapSharedPtr(), rsImageInfo, options);
    recordingCanvas.DetachBrush();
#endif
#endif
}

void PixelMapImage::DrawRect(RSCanvas& canvas, const RSRect& dstRect)
{
#ifndef USE_ROSEN_DRAWING
#ifdef ENABLE_ROSEN_BACKEND
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_VOID(recordingCanvas);
    SkPaint paint;
    SkSamplingOptions option;
    SkRect dst { dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom() };

    CHECK_NULL_VOID(pixelMap_);
    auto pixelMap = pixelMap_->GetPixelMapSharedPtr();
    recordingCanvas->DrawPixelMapRect(pixelMap, dst, option, &paint);
#endif
#else
#ifdef ENABLE_ROSEN_BACKEND
    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    RSBrush brush;
    RSSamplingOptions options;
    RSRect dst = RSRect(dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom());

    auto pixelMap = pixelMap_->GetPixelMapSharedPtr();
    RSRect src = RSRect(0, 0, pixelMap->GetWidth(), pixelMap->GetHeight());
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawPixelMapRect(pixelMap, src, dst, options);
    recordingCanvas.DetachBrush();
#endif
#endif
}

void PixelMapImage::Cache(const std::string& key)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto cache = pipeline->GetImageCache();
    CHECK_NULL_VOID(cache);
    cache->CacheImageData(key, MakeRefPtr<PixmapData>(GetPixelMap()));
}

RefPtr<CanvasImage> PixelMapImage::QueryFromCache(const std::string& key)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, nullptr);
    auto cache = pipeline->GetImageCache();
    CHECK_NULL_RETURN(cache, nullptr);
    auto data = DynamicCast<PixmapData>(cache->GetCacheImageData(key));
    CHECK_NULL_RETURN(data, nullptr);
    return MakeRefPtr<PixelMapImage>(data->GetPixmap());
}
} // namespace OHOS::Ace::NG
