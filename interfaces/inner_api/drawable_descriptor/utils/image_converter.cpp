/*
 * Copyright (C) 2023-2025 Huawei Device Co., Ltd.
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

#include "utils/image_converter.h"

#ifndef PREVIEW
#include "image_utils.h"
#include "platform/image_native/image_type.h"
#endif
#include "securec.h"

#include "base/log.h"

namespace OHOS::Ace::Napi {
Rosen::Drawing::ColorType ImageConverter::PixelFormatToColorType(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::BGRA_8888:
            return Rosen::Drawing::ColorType::COLORTYPE_BGRA_8888;
        case Media::PixelFormat::ARGB_8888:
        case Media::PixelFormat::ALPHA_8:
        case Media::PixelFormat::RGBA_8888:
        case Media::PixelFormat::RGB_565:
        case Media::PixelFormat::RGB_888:
        case Media::PixelFormat::RGBA_F16:
        case Media::PixelFormat::NV21:
        case Media::PixelFormat::NV12:
        case Media::PixelFormat::CMYK:
        case Media::PixelFormat::UNKNOWN:
        default:
            return Rosen::Drawing::ColorType::COLORTYPE_UNKNOWN;
    }
}

Rosen::Drawing::AlphaType ImageConverter::AlphaTypeToAlphaType(Media::AlphaType alphaType)
{
    switch (alphaType) {
        case Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return Rosen::Drawing::AlphaType::ALPHATYPE_OPAQUE;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_PREMUL;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNPREMUL;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
        default:
            return Rosen::Drawing::AlphaType::ALPHATYPE_UNKNOWN;
    }
}

std::shared_ptr<Rosen::Drawing::Bitmap> ImageConverter::PixelMapToBitmap(
    const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    if (!pixelMap) {
        return nullptr;
    }
    auto data = pixelMap->GetPixels();
    Rosen::Drawing::Bitmap bitmap;
    Rosen::Drawing::ColorType colorType = ImageConverter::PixelFormatToColorType(pixelMap->GetPixelFormat());
    Rosen::Drawing::AlphaType alphaType = ImageConverter::AlphaTypeToAlphaType(pixelMap->GetAlphaType());
    Rosen::Drawing::ImageInfo imageInfo(pixelMap->GetWidth(), pixelMap->GetHeight(), colorType, alphaType);
    bitmap.Build(imageInfo);
    bitmap.SetPixels(const_cast<uint8_t*>(data));
    return std::make_shared<Rosen::Drawing::Bitmap>(bitmap);
}

std::shared_ptr<Media::PixelMap> ImageConverter::BitmapToPixelMap(
    const std::shared_ptr<Rosen::Drawing::Bitmap>& bitMap, Media::InitializationOptions& opts)
{
    auto data = bitMap->GetPixels();
    opts.size.width = static_cast<int32_t>(bitMap->GetWidth());
    opts.size.height = static_cast<int32_t>(bitMap->GetHeight());
    opts.editable = false;
    auto pixelMap = Media::PixelMap::Create(opts);
    if (!pixelMap) {
        HILOGE("PixelMap is null, bitMap's Size = (%{public}d, %{public}d)", bitMap->GetWidth(), bitMap->GetHeight());
        return pixelMap;
    }
    auto dstAddr = pixelMap->GetWritablePixels();
    if (memcpy_s(dstAddr, pixelMap->GetByteCount(), data, pixelMap->GetByteCount()) != 0) {
        HILOGE("PixelMap write fail");
        return nullptr;
    }
    return pixelMap;
}
} // namespace OHOS::Ace::Napi
