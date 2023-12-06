/*
 * Copyright (C) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_CONVERTER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_CONVERTER_H

#ifndef USE_ROSEN_DRAWING
#include "include/core/SkBitmap.h"
#include "include/core/SkImageInfo.h"
#else
#include "image/bitmap.h"
#endif
#include "include/core/SkSamplingOptions.h"
#ifndef PREVIEW
#include "pixel_map.h"
#include "image_source.h"
#else
#include "image_source_preview.h"
#endif

namespace OHOS::Ace::Napi {
class ImageConverter {
public:
    std::unique_ptr<Media::ImageSource> CreateImageSource(const char* item, uint32_t& errorCode);
#ifndef USE_ROSEN_DRAWING
    static SkColorType PixelFormatToSkColorType(Media::PixelFormat pixelFormat);
    static SkAlphaType AlphaTypeToSkAlphaType(Media::AlphaType alphaType);
    static std::shared_ptr<SkBitmap> PixelMapToBitmap(
        const std::shared_ptr<Media::PixelMap>& pixelMap);
    static std::shared_ptr<Media::PixelMap> BitmapToPixelMap(
        const std::shared_ptr<SkBitmap>& bitMap, Media::InitializationOptions& opts);
#else
    static Rosen::Drawing::ColorType PixelFormatToColorType(Media::PixelFormat pixelFormat);
    static Rosen::Drawing::AlphaType AlphaTypeToAlphaType(Media::AlphaType alphaType);
    static std::shared_ptr<Rosen::Drawing::Bitmap> PixelMapToBitmap(
        const std::shared_ptr<Media::PixelMap>& pixelMap);
    static std::shared_ptr<Media::PixelMap> BitmapToPixelMap(
        const std::shared_ptr<Rosen::Drawing::Bitmap>& bitMap, Media::InitializationOptions& opts);
#endif
};
} // namespace OHOS::Ace::Napi
#endif // #define FOUNDATION_ACE_INTERFACE_INNERKITS_IMAGE_CONVERTER_H

