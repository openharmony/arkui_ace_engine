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

#include "core/components_ng/render/adapter/skia_canvas_image.h"

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

RefPtr<CanvasImage> CanvasImage::Create(void* rawImage)
{
#ifdef NG_BUILD
    return AceType::MakeRefPtr<SkiaCanvasImage>();
#else
    auto* imageRef = reinterpret_cast<fml::RefPtr<flutter::CanvasImage>*>(rawImage);
    CHECK_NULL_RETURN(imageRef, nullptr);

    return AceType::MakeRefPtr<SkiaCanvasImage>(*imageRef);
#endif
}

void SkiaCanvasImage::ReplaceSkImage(flutter::SkiaGPUObject<SkImage> newSkGpuObjSkImage)
{
#ifndef NG_BUILD
    image_->set_image(std::move(newSkGpuObjSkImage));
#endif
}

int32_t SkiaCanvasImage::GetWidth() const
{
#ifdef NG_BUILD
    return 0;
#else
    return image_->width();
#endif
}

int32_t SkiaCanvasImage::GetHeight() const
{
#ifdef NG_BUILD
    return 0;
#else
    return image_->height();
#endif
}

void SkiaCanvasImage::DrawToRSCanvas(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect)
{
    auto image = GetCanvasImage();
    RSImage rsImage(&image);
    RSSamplingOptions options;
    canvas.DrawImageRect(rsImage, srcRect, dstRect, options);
}

} // namespace OHOS::Ace::NG
