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

#include "image_converter.h"
#ifndef PREVIEW
#include "platform/image_native/image_type.h"
#include "image_utils.h"
#endif

namespace OHOS::Ace::Napi {
SkColorType ImageConverter::PixelFormatToSkColorType(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::BGRA_8888:
            return SkColorType::kBGRA_8888_SkColorType;
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
            return SkColorType::kUnknown_SkColorType;
    }
}

SkAlphaType ImageConverter::AlphaTypeToSkAlphaType(Media::AlphaType alphaType)
{
    switch (alphaType) {
        case Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return SkAlphaType::kOpaque_SkAlphaType;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return SkAlphaType::kPremul_SkAlphaType;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return SkAlphaType::kUnpremul_SkAlphaType;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
        default:
            return SkAlphaType::kUnknown_SkAlphaType;
    }
}

std::shared_ptr<SkBitmap> ImageConverter::PixelMapToBitmap(
    const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    auto data = pixelMap->GetPixels();
    SkBitmap bitmap;
    SkColorType colorType = ImageConverter::PixelFormatToSkColorType(pixelMap->GetPixelFormat());
    SkAlphaType alphaType = ImageConverter::AlphaTypeToSkAlphaType(pixelMap->GetAlphaType());
    auto imageInfo = SkImageInfo::Make(pixelMap->GetWidth(), pixelMap->GetHeight(), colorType, alphaType);
    bitmap.setInfo(imageInfo);
    bitmap.setPixels(const_cast<uint8_t*>(data));
    return std::make_shared<SkBitmap>(bitmap);
}

std::shared_ptr<Media::PixelMap> ImageConverter::BitmapToPixelMap(
    const std::shared_ptr<SkBitmap>& bitMap, Media::InitializationOptions& opts)
{
    auto data = bitMap->getPixels();
    opts.size.width = static_cast<int32_t>(bitMap->width());
    opts.size.height = static_cast<int32_t>(bitMap->height());
    auto pixelMap = Media::PixelMap::Create(reinterpret_cast<uint32_t*>(data),
        opts.size.width * opts.size.height, opts);
    return pixelMap;
}
} // namespace OHOS::Ace::Napi
