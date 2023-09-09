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
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"

#ifdef ENABLE_ROSEN_BACKEND
#include "render_service_client/core/ui/rs_node.h"
#include "render_service_client/core/ui/rs_surface_node.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#endif

namespace OHOS::Ace::NG {
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
    LOGW("pixelMap_ is nullptr, return width 0.");
    return 0;
}

int32_t PixelMapImage::GetHeight() const
{
    auto pixmap = GetPixelMap();
    if (pixmap) {
        return pixmap->GetHeight();
    }
    LOGW("rsCanvas is nullptr, return height 0.");
    return 0;
}

void PixelMapImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& /* srcRect */, const RSRect& /* dstRect */, const BorderRadiusArray& radiusXY)
{
    auto pixmap = GetPixelMap();
    CHECK_NULL_VOID(pixmap);

#ifdef ENABLE_ROSEN_BACKEND
#ifndef USE_ROSEN_DRAWING
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_VOID(recordingCanvas);
    SkPaint paint;
    auto config = GetPaintConfig();
#ifndef NEW_SKIA
    ImagePainterUtils::AddFilter(paint, config);
#else
    SkSamplingOptions options;
    ImagePainterUtils::AddFilter(paint, options, config);
#endif
    auto radii = ImagePainterUtils::ToSkRadius(radiusXY);
    recordingCanvas->ClipAdaptiveRRect(radii.get());
    recordingCanvas->scale(config.scaleX_, config.scaleY_);

    Rosen::RsImageInfo rsImageInfo(
        static_cast<int>(config.imageFit_), static_cast<int>(config.imageRepeat_), radii.get(), 1.0, 0, 0, 0);

#ifndef NEW_SKIA
    recordingCanvas->DrawPixelMapWithParm(pixmap->GetPixelMapSharedPtr(), rsImageInfo, paint);
#else
    recordingCanvas->DrawPixelMapWithParm(pixmap->GetPixelMapSharedPtr(), rsImageInfo, options, paint);
#endif
#else
    RSBrush brush;
    auto config = GetPaintConfig();
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    auto recordingCanvas = static_cast<RSRecordingCanvas&>(canvas);
    std::vector<RSPoint> radius;
    for (int ii = 0; ii < 4; ii++) {
        RSPoint point(radiusXY[ii].GetX(), radiusXY[ii].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    CHECK_NULL_VOID(pixmap->GetPixelMapSharedPtr());
    RSPoint pointRadius[4] = {};
    for (int i = 0; i < 4; i++) {
        pointRadius[i] = radius[i];
    }
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo =
        {static_cast<int32_t>(config.imageFit_), static_cast<int32_t>(config.imageRepeat_),
         {pointRadius[0], pointRadius[1], pointRadius[2], pointRadius[3]}, 1.0, 0, 0, 0};
    RSSamplingOptions smapling;
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawPixelMap(pixmap->GetPixelMapSharedPtr(), rsImageInfo, smapling);
    recordingCanvas.DetachBrush();
#endif
#endif
}

void PixelMapImage::DrawRect(RSCanvas& canvas, const RSRect& dstRect)
{
#ifndef USE_ROSEN_DRAWING
#ifdef ENABLE_ROSEN_BACKEND
#ifdef NEW_SKIA
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
    auto skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_VOID(recordingCanvas);
    SkPaint paint;
    SkSamplingOptions option;
    SkRect dst { dstRect.GetLeft(), dstRect.GetTop(), dstRect.GetRight(), dstRect.GetBottom() };

    auto pixelMap = pixelMap_->GetPixelMapSharedPtr();
    recordingCanvas->DrawPixelMapRect(pixelMap, dst, option, &paint);
#endif
#else
    LOGE("Drawing is not supported");
#endif
#else
    // TODO Drawing
    LOGE("Drawing is not supported");
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
    LOGD("pixelMap cache found %{public}s", key.c_str());
    return MakeRefPtr<PixelMapImage>(data->GetPixmap());
}
} // namespace OHOS::Ace::NG
