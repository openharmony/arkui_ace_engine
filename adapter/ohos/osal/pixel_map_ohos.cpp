/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "pixel_map_ohos.h"

#include <sstream>

#include "drawable_descriptor.h"
#include "pixel_map_manager.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace OHOS::Ace {

PixelFormat PixelMapOhos::PixelFormatConverter(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::RGB_565:
            return PixelFormat::RGB_565;
        case Media::PixelFormat::RGBA_8888:
            return PixelFormat::RGBA_8888;
        case Media::PixelFormat::BGRA_8888:
            return PixelFormat::BGRA_8888;
        case Media::PixelFormat::ALPHA_8:
            return PixelFormat::ALPHA_8;
        case Media::PixelFormat::RGBA_F16:
            return PixelFormat::RGBA_F16;
        case Media::PixelFormat::UNKNOWN:
            return PixelFormat::UNKNOWN;
        case Media::PixelFormat::ARGB_8888:
            return PixelFormat::ARGB_8888;
        case Media::PixelFormat::RGB_888:
            return PixelFormat::RGB_888;
        case Media::PixelFormat::NV21:
            return PixelFormat::NV21;
        case Media::PixelFormat::NV12:
            return PixelFormat::NV12;
        case Media::PixelFormat::CMYK:
            return PixelFormat::CMYK;
        default:
            return PixelFormat::UNKNOWN;
    }
}

AlphaType PixelMapOhos::AlphaTypeConverter(Media::AlphaType alphaType)
{
    switch (alphaType) {
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
        case Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
        default:
            return AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
    }
}

RefPtr<PixelMap> PixelMap::Create(std::unique_ptr<Media::PixelMap>&& pixmap)
{
    return AceType::MakeRefPtr<PixelMapOhos>(std::move(pixmap));
}

RefPtr<PixelMap> PixelMap::CreatePixelMap(void* rawPtr)
{
    auto* pixmapPtr = reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(rawPtr);
    if (pixmapPtr == nullptr || *pixmapPtr == nullptr) {
        LOGW("pixmap pointer is nullptr when CreatePixelMap.");
        return nullptr;
    }
    return AceType::MakeRefPtr<PixelMapOhos>(*pixmapPtr);
}

RefPtr<PixelMap> PixelMap::GetFromDrawable(void* ptr)
{
    CHECK_NULL_RETURN(ptr, nullptr);
    auto* drawable = reinterpret_cast<Napi::DrawableDescriptor*>(ptr);
    return AceType::MakeRefPtr<PixelMapOhos>(drawable->GetPixelMap());
}

RefPtr<PixelMap> PixelMap::CreatePixelMapFromDataAbility(void* ptr)
{
    auto* pixmap = reinterpret_cast<Media::PixelMap*>(ptr);
    CHECK_NULL_RETURN(pixmap, nullptr);
    return AceType::MakeRefPtr<PixelMapOhos>(std::shared_ptr<Media::PixelMap>(pixmap));
}

int32_t PixelMapOhos::GetWidth() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetWidth();
}

int32_t PixelMapOhos::GetHeight() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetHeight();
}

const uint8_t* PixelMapOhos::GetPixels() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_->GetPixels();
}

PixelFormat PixelMapOhos::GetPixelFormat() const
{
    CHECK_NULL_RETURN(pixmap_, PixelFormat::UNKNOWN);
    return PixelFormatConverter(pixmap_->GetPixelFormat());
}

AlphaType PixelMapOhos::GetAlphaType() const
{
    CHECK_NULL_RETURN(pixmap_, AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN);
    return AlphaTypeConverter(pixmap_->GetAlphaType());
}

int32_t PixelMapOhos::GetRowBytes() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowBytes();
}

int32_t PixelMapOhos::GetByteCount() const
{
    CHECK_NULL_RETURN_NOLOG(pixmap_, 0);
    return pixmap_->GetByteCount();
}

void* PixelMapOhos::GetPixelManager() const
{
    Media::InitializationOptions opts;
    CHECK_NULL_RETURN_NOLOG(pixmap_, nullptr);
    auto newPixelMap = Media::PixelMap::Create(*pixmap_, opts);
    return reinterpret_cast<void*>(new Media::PixelMapManager(newPixelMap.release()));
}

void* PixelMapOhos::GetRawPixelMapPtr() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_.get();
}

std::string PixelMapOhos::GetId()
{
    // using pixmap addr
    CHECK_NULL_RETURN(pixmap_, "nullptr");
    std::stringstream strm;
    strm << pixmap_.get();
    return strm.str();
}

std::string PixelMapOhos::GetModifyId()
{
    return {};
}

std::shared_ptr<Media::PixelMap> PixelMapOhos::GetPixelMapSharedPtr()
{
    return pixmap_;
}

void* PixelMapOhos::GetWritablePixels() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_->GetWritablePixels();
}

RefPtr<PixelMap> PixelMap::ConvertSkImageToPixmap(
    const uint32_t* colors, uint32_t colorLength, int32_t width, int32_t height)
{
    Media::InitializationOptions opts;
    opts.size.width = width;
    opts.size.height = height;
    opts.editable = true;
    std::unique_ptr<Media::PixelMap> pixmap = Media::PixelMap::Create(colors, colorLength, opts);
    CHECK_NULL_RETURN(pixmap, nullptr);
    std::shared_ptr<Media::PixelMap> sharedPixelmap(pixmap.release());
    return AceType::MakeRefPtr<PixelMapOhos>(sharedPixelmap);
}

} // namespace OHOS::Ace
