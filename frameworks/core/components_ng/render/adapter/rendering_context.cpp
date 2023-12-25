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

#include "image_painter_utils.h"

#include "base/image/pixel_map.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
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
#ifndef NG_BUILD
    return AceType::MakeRefPtr<PixelMapImage>(pixelMap);
#else
    return nullptr;
#endif
}

int32_t PixelMapImage::GetWidth() const
{
    if (pixelMap_) {
        return pixelMap_->GetWidth();
    }
    LOGW("pixelMap_ is nullptr, return width 0.");
    return 0;
}

int32_t PixelMapImage::GetHeight() const
{
    if (pixelMap_) {
        return pixelMap_->GetHeight();
    }
    LOGW("rsCanvas is nullptr, return height 0.");
    return 0;
}

#ifdef ENABLE_ROSEN_BACKEND
#ifndef USE_ROSEN_DRAWING
void PixelMapImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& /* srcRect */, const RSRect& /* dstRect */, const BorderRadiusArray& radiusXY)
{
    if (!pixelMap_) {
        return;
    }

    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    if (rsCanvas == nullptr) {
        LOGE("rsCanvas is nullptr.");
        return;
    }
    auto skCanvas = rsCanvas->ExportSkCanvas();
    if (skCanvas == nullptr) {
        LOGE("skCanvas is nullptr.");
        return;
    }
    auto recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    if (recordingCanvas == nullptr) {
        LOGE("recordingCanvas is nullptr.");
        return;
    }
    SkPaint paint;
    auto config = GetPaintConfig();

    SkSamplingOptions options;
    ImagePainterUtils::AddFilter(paint, options, config);
    auto radii = ImagePainterUtils::ToSkRadius(radiusXY);
    recordingCanvas->ClipAdaptiveRRect(radii.get());
    recordingCanvas->scale(config.scaleX_, config.scaleY_);

    Rosen::RsImageInfo rsImageInfo((int)(config.imageFit_), (int)(config.imageRepeat_), radii.get(), 1.0, 0, 0, 0);

    recordingCanvas->DrawPixelMapWithParm(pixelMap_->GetPixelMapSharedPtr(), rsImageInfo, paint);
}
#else
void PixelMapImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& /* srcRect */, const RSRect& /* dstRect */, const BorderRadiusArray& radiusXY)
{
    if (!pixelMap_) {
        return;
    }

    auto& recordingCanvas = static_cast<Rosen::ExtendRecordingCanvas&>(canvas);
    RSBrush brush;
    auto config = GetPaintConfig();
    RSSamplingOptions options;
    ImagePainterUtils::AddFilter(brush, options, config);
    std::vector<RSPoint> radius;
    static const int pointCount = 4;
    for (int i = 0; i < pointCount; i++) {
        RSPoint point(radiusXY[i].GetX(), radiusXY[i].GetY());
        radius.emplace_back(point);
    }
    recordingCanvas.ClipAdaptiveRoundRect(radius);
    recordingCanvas.Scale(config.scaleX_, config.scaleY_);

    CHECK_NULL_VOID_NOLOG(pixelMap_->GetPixelMapSharedPtr());
    auto radii = ImagePainterUtils::ToRSRadius(radiusXY);
    Rosen::Drawing::AdaptiveImageInfo rsImageInfo = { static_cast<int32_t>(config.imageFit_),
        static_cast<int32_t>(config.imageRepeat_), radii, 1.0, 0, 0, 0 };
    recordingCanvas.AttachBrush(brush);
    recordingCanvas.DrawPixelMapWithParm(pixelMap->GetPixelMapSharedPtr(), rsImageInfo, options);
    recordingCanvas.DetachBrush();
}
#endif
#endif
} // namespace OHOS::Ace::NG