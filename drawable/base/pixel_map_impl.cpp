/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <memory>
#include <unordered_map>

#include "pixel_map.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
namespace {
PixelFormat PixelFormatConverter(Media::PixelFormat pixelFormat)
{
    static const std::unordered_map<Media::PixelFormat, PixelFormat> pixelFormatMap = {
        { Media::PixelFormat::RGB_565, PixelFormat::RGB_565 },
        { Media::PixelFormat::RGBA_8888, PixelFormat::RGBA_8888 },
        { Media::PixelFormat::RGBA_1010102, PixelFormat::RGBA_1010102 },
        { Media::PixelFormat::BGRA_8888, PixelFormat::BGRA_8888 },
        { Media::PixelFormat::ALPHA_8, PixelFormat::ALPHA_8 },
        { Media::PixelFormat::RGBA_F16, PixelFormat::RGBA_F16 },
        { Media::PixelFormat::UNKNOWN, PixelFormat::UNKNOWN },
        { Media::PixelFormat::ARGB_8888, PixelFormat::ARGB_8888 },
        { Media::PixelFormat::RGB_888, PixelFormat::RGB_888 },
        { Media::PixelFormat::NV21, PixelFormat::NV21 },
        { Media::PixelFormat::NV12, PixelFormat::NV12 },
        { Media::PixelFormat::CMYK, PixelFormat::CMYK },
    };

    auto it = pixelFormatMap.find(pixelFormat);
    if (it != pixelFormatMap.end()) {
        return it->second;
    }

    return PixelFormat::UNKNOWN;
}
} // namespace

std::shared_ptr<PixelMap> PixelMap::Create(const std::shared_ptr<Media::PixelMap>& pixmap)
{
    return std::make_shared<PixelMap>(pixmap);
}

int32_t PixelMap::GetWidth() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetWidth();
}

int32_t PixelMap::GetHeight() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetHeight();
}

const uint8_t* PixelMap::GetPixels() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_->GetPixels();
}

PixelFormat PixelMap::GetPixelFormat() const
{
    CHECK_NULL_RETURN(pixmap_, PixelFormat::UNKNOWN);
    return PixelFormatConverter(pixmap_->GetPixelFormat());
}

AlphaType PixelMap::GetAlphaType() const
{
    CHECK_NULL_RETURN(pixmap_, AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN);
    return AlphaTypeConverter(pixmap_->GetAlphaType());
}

int32_t PixelMap::GetRowStride() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowStride();
}

int32_t PixelMap::GetRowBytes() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowBytes();
}

int32_t PixelMap::GetByteCount() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetByteCount();
}

AllocatorType PixelMap::GetAllocatorType() const
{
    CHECK_NULL_RETURN(pixmap_, AllocatorType::DEFAULT);
    return AllocatorTypeConverter(pixmap_->GetAllocatorType());
}

bool PixelMap::IsHdr() const
{
    CHECK_NULL_RETURN(pixmap_, false);
    return pixmap_->IsHdr();
}

void* PixelMap::GetPixelManager() const
{
    Media::InitializationOptions opts;
    CHECK_NULL_RETURN(pixmap_, nullptr);
    auto newPixelMap = Media::PixelMap::Create(*pixmap_, opts);
    return reinterpret_cast<void*>(new Media::PixelMapManager(newPixelMap.release()));
}

void* PixelMap::GetRawPixelMapPtr() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_.get();
}

std::shared_ptr<Media::PixelMap> PixelMap::GetPixelMapSharedPtr()
{
    return pixmap_;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
