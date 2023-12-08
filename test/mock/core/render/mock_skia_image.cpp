/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#endif

namespace OHOS::Ace::NG {

RefPtr<CanvasImage> CanvasImage::Create(void* rawImage)
{
    return nullptr;
}

#ifndef USE_ROSEN_DRAWING
RefPtr<CanvasImage> SkiaImage::Clone()
#else
RefPtr<CanvasImage> DrawingImage::Clone()
#endif
{
    return Claim(this);
}

#ifndef USE_ROSEN_DRAWING
RefPtr<PixelMap> SkiaImage::GetPixelMap() const
#else
RefPtr<PixelMap> DrawingImage::GetPixelMap() const
#endif
{
    return nullptr;
}

#ifndef USE_ROSEN_DRAWING
void SkiaImage::Cache(const std::string& key) {}
#else
void DrawingImage::Cache(const std::string& key) {}
#endif

#ifndef USE_ROSEN_DRAWING
RefPtr<CanvasImage> SkiaImage::QueryFromCache(const std::string& key)
#else
RefPtr<CanvasImage> DrawingImage::QueryFromCache(const std::string& key)
#endif
{
    return nullptr;
}

#ifndef USE_ROSEN_DRAWING
void SkiaImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
#else
void DrawingImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
#endif
{}

#ifndef USE_ROSEN_DRAWING
int32_t SkiaImage::GetWidth() const
#else
int32_t DrawingImage::GetWidth() const
#endif
{
    return {};
}

#ifndef USE_ROSEN_DRAWING
int32_t SkiaImage::GetHeight() const
#else
int32_t DrawingImage::GetHeight() const
#endif
{
    return {};
}

} // namespace OHOS::Ace::NG
