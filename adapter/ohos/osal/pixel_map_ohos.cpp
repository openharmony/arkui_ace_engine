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

#include "drawable_descriptor.h"
#include "media_errors.h"
#include "pixel_map_manager.h"

#include "core/image/image_file_cache.h"

namespace OHOS::Ace {

PixelFormat PixelMapOhos::PixelFormatConverter(Media::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case Media::PixelFormat::RGB_565:
            return PixelFormat::RGB_565;
        case Media::PixelFormat::RGBA_8888:
            return PixelFormat::RGBA_8888;
        case Media::PixelFormat::RGBA_1010102:
            return PixelFormat::RGBA_1010102;
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

Media::PixelFormat PixelMapOhos::ConvertToMediaPixelFormat(Ace::PixelFormat pixelFormat)
{
    switch (pixelFormat) {
        case PixelFormat::RGB_565:
            return Media::PixelFormat::RGB_565;
        case PixelFormat::RGBA_8888:
            return Media::PixelFormat::RGBA_8888;
        case PixelFormat::RGBA_1010102:
            return Media::PixelFormat::RGBA_1010102;
        case PixelFormat::BGRA_8888:
            return Media::PixelFormat::BGRA_8888;
        case PixelFormat::ALPHA_8:
            return Media::PixelFormat::ALPHA_8;
        case PixelFormat::RGBA_F16:
            return Media::PixelFormat::RGBA_F16;
        case PixelFormat::UNKNOWN:
            return Media::PixelFormat::UNKNOWN;
        case PixelFormat::ARGB_8888:
            return Media::PixelFormat::ARGB_8888;
        case PixelFormat::RGB_888:
            return Media::PixelFormat::RGB_888;
        case PixelFormat::NV21:
            return Media::PixelFormat::NV21;
        case PixelFormat::NV12:
            return Media::PixelFormat::NV12;
        case PixelFormat::CMYK:
            return Media::PixelFormat::CMYK;
        default:
            return Media::PixelFormat::UNKNOWN;
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

Media::AlphaType PixelMapOhos::ConvertToMediaAlphaType(Ace::AlphaType alphaType)
{
    switch (alphaType) {
        case AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN:
            return Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
        case AlphaType::IMAGE_ALPHA_TYPE_OPAQUE:
            return Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
        case AlphaType::IMAGE_ALPHA_TYPE_PREMUL:
            return Media::AlphaType::IMAGE_ALPHA_TYPE_PREMUL;
        case AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL:
            return Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
        default:
            return Media::AlphaType::IMAGE_ALPHA_TYPE_UNKNOWN;
    }
}

AllocatorType PixelMapOhos::AllocatorTypeConverter(Media::AllocatorType allocatorType)
{
    switch (allocatorType) {
        case Media::AllocatorType::DEFAULT:
            return AllocatorType::DEFAULT;
        case Media::AllocatorType::HEAP_ALLOC:
            return AllocatorType::HEAP_ALLOC;
        case Media::AllocatorType::SHARE_MEM_ALLOC:
            return AllocatorType::SHARE_MEM_ALLOC;
        case Media::AllocatorType::CUSTOM_ALLOC:
            return AllocatorType::CUSTOM_ALLOC;
        case Media::AllocatorType::DMA_ALLOC:
            return AllocatorType::DMA_ALLOC;
        default:
            return AllocatorType::DEFAULT;
    }
}

Media::ScaleMode PixelMapOhos::ConvertToMediaScaleMode(Ace::ScaleMode scaleMode)
{
    switch (scaleMode) {
        case ScaleMode::CENTER_CROP:
            return Media::ScaleMode::CENTER_CROP;
        case ScaleMode::FIT_TARGET_SIZE:
            return Media::ScaleMode::FIT_TARGET_SIZE;
        default:
            return Media::ScaleMode::FIT_TARGET_SIZE;
    }
}

RefPtr<PixelMap> PixelMap::Create(std::unique_ptr<Media::PixelMap>&& pixmap)
{
    return AceType::MakeRefPtr<PixelMapOhos>(std::move(pixmap));
}

RefPtr<PixelMap> PixelMap::Create(const InitializationOptions& opts)
{
    Media::InitializationOptions options;
    opts.size.Width();
    options.size.width = opts.size.Width();
    options.size.height = opts.size.Height();
    options.srcPixelFormat = PixelMapOhos::ConvertToMediaPixelFormat(opts.srcPixelFormat);
    options.pixelFormat = PixelMapOhos::ConvertToMediaPixelFormat(opts.pixelFormat);
    options.editable = opts.editable;
    options.alphaType = PixelMapOhos::ConvertToMediaAlphaType(opts.alphaType);
    options.scaleMode = PixelMapOhos::ConvertToMediaScaleMode(opts.scaleMode);
    options.srcRowStride = opts.srcRowStride;
    options.useSourceIfMatch = opts.useSourceIfMatch;
    options.useDMA = opts.useDMA;
    std::unique_ptr<Media::PixelMap> pixmap = Media::PixelMap::Create(options);
    return AceType::MakeRefPtr<PixelMapOhos>(std::move(pixmap));
}

RefPtr<PixelMap> PixelMap::Create(const std::shared_ptr<Media::PixelMap>& pixmap)
{
    return AceType::MakeRefPtr<PixelMapOhos>(pixmap);
}

RefPtr<PixelMap> PixelMap::CreatePixelMap(void* rawPtr)
{
    auto* pixmapPtr = reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(rawPtr);
    if (pixmapPtr == nullptr || *pixmapPtr == nullptr) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "invalid pixmap");
        return nullptr;
    }
    return AceType::MakeRefPtr<PixelMapOhos>(*pixmapPtr);
}

RefPtr<PixelMap> PixelMap::CopyPixelMap(const RefPtr<PixelMap>& pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    OHOS::Media::InitializationOptions opts;
    auto mediaPixelMap = pixelMap->GetPixelMapSharedPtr();
    std::unique_ptr<Media::PixelMap> uniquePixelMap = Media::PixelMap::Create(*mediaPixelMap, opts);
    CHECK_NULL_RETURN(uniquePixelMap, nullptr);
    Media::PixelMap* pixelMapRelease = uniquePixelMap.release();
    CHECK_NULL_RETURN(pixelMapRelease, nullptr);
    std::shared_ptr<Media::PixelMap> newPixelMap(pixelMapRelease);
    CHECK_NULL_RETURN(newPixelMap, nullptr);
    return AceType::MakeRefPtr<PixelMapOhos>(newPixelMap);
}

RefPtr<PixelMap> PixelMap::DecodeTlv(std::vector<uint8_t>& buff)
{
    Media::PixelMap* pixelMapRelease = OHOS::Media::PixelMap::DecodeTlv(buff);
    CHECK_NULL_RETURN(pixelMapRelease, nullptr);
    std::shared_ptr<Media::PixelMap> newPixelMap(pixelMapRelease);
    CHECK_NULL_RETURN(newPixelMap, nullptr);
    return AceType::MakeRefPtr<PixelMapOhos>(newPixelMap);
}

bool PixelMapOhos::EncodeTlv(std::vector<uint8_t>& buff)
{
    CHECK_NULL_RETURN(pixmap_, false);
    return pixmap_->EncodeTlv(buff);
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

int32_t PixelMapOhos::GetRowStride() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowStride();
}

int32_t PixelMapOhos::GetRowBytes() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetRowBytes();
}

int32_t PixelMapOhos::GetByteCount() const
{
    CHECK_NULL_RETURN(pixmap_, 0);
    return pixmap_->GetByteCount();
}

AllocatorType PixelMapOhos::GetAllocatorType() const
{
    CHECK_NULL_RETURN(pixmap_, AllocatorType::DEFAULT);
    return AllocatorTypeConverter(pixmap_->GetAllocatorType());
}

bool PixelMapOhos::IsHdr() const
{
    CHECK_NULL_RETURN(pixmap_, false);
    return pixmap_->IsHdr();
}

void* PixelMapOhos::GetPixelManager() const
{
    Media::InitializationOptions opts;
    CHECK_NULL_RETURN(pixmap_, nullptr);
    auto newPixelMap = Media::PixelMap::Create(*pixmap_, opts);
    return reinterpret_cast<void*>(new Media::PixelMapManager(newPixelMap.release()));
}

void* PixelMapOhos::GetRawPixelMapPtr() const
{
    CHECK_NULL_RETURN(pixmap_, nullptr);
    return pixmap_.get();
}

void PixelMapOhos::Scale(float xAxis, float yAxis)
{
    CHECK_NULL_VOID(pixmap_);
    pixmap_->scale(xAxis, yAxis);
}

void PixelMapOhos::Scale(float xAxis, float yAxis, const AceAntiAliasingOption& option)
{
    CHECK_NULL_VOID(pixmap_);
    switch (option) {
        case AceAntiAliasingOption::NONE:
            pixmap_->scale(xAxis, yAxis, Media::AntiAliasingOption::NONE);
            break;
        case AceAntiAliasingOption::LOW:
            pixmap_->scale(xAxis, yAxis, Media::AntiAliasingOption::LOW);
            break;
        case AceAntiAliasingOption::MEDIUM:
            pixmap_->scale(xAxis, yAxis, Media::AntiAliasingOption::MEDIUM);
            break;
        case AceAntiAliasingOption::HIGH:
            pixmap_->scale(xAxis, yAxis, Media::AntiAliasingOption::HIGH);
            break;
        default:
            pixmap_->scale(xAxis, yAxis, Media::AntiAliasingOption::NONE);
            break;
    }
}

std::string PixelMapOhos::GetId()
{
    // using pixmap addr
    CHECK_NULL_RETURN(pixmap_, "nullptr");
    std::stringstream strm;
    strm << pixmap_.get();
    return strm.str();
}

uint32_t PixelMapOhos::GetUniqueId()
{
    CHECK_NULL_RETURN(pixmap_, -1);
    return pixmap_->GetUniqueId();
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

bool PixelMapOhos::GetPixelsVec(std::vector<uint8_t>& data) const
{
    CHECK_NULL_RETURN(pixmap_, false);
    data.resize(pixmap_->GetByteCount());
    uint8_t* dst = data.data();
    uint32_t errCode = pixmap_->ReadPixels(pixmap_->GetByteCount(), dst);
    if (errCode) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "GetPixelsVec error, errCode=%{public}d", errCode);
        return false;
    }
    return true;
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

void PixelMapOhos::SavePixelMapToFile(const std::string& dst) const
{
    int32_t w = pixmap_->GetWidth();
    int32_t h = pixmap_->GetHeight();
    int32_t totalSize = static_cast<int32_t>(pixmap_->GetCapacity());
    auto rowStride = pixmap_->GetRowStride();
    uint64_t nowTime = static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count());
    std::string filename = std::to_string(nowTime) + "_w" + std::to_string(w) + "_h" + std::to_string(h) +
                           "_rowStride" + std::to_string(rowStride) + "_byteCount" + std::to_string(totalSize) + dst +
                           ".dat";
    auto path = ImageFileCache::GetInstance().ConstructCacheFilePath(filename);
    std::ofstream outFile(path, std::fstream::out);
    if (!outFile.is_open()) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "write error, path=%{public}s", path.c_str());
    }
    outFile.write(reinterpret_cast<const char*>(pixmap_->GetPixels()), totalSize);
    TAG_LOGI(AceLogTag::ACE_IMAGE, "write success, path=%{public}s", path.c_str());
}

RefPtr<PixelMap> PixelMapOhos::GetCropPixelMap(const Rect& srcRect)
{
    Media::InitializationOptions options;
    options.size.width = static_cast<int32_t>(srcRect.Width());
    options.size.height = static_cast<int32_t>(srcRect.Height());
    options.pixelFormat = Media::PixelFormat::RGBA_8888;
    options.alphaType = Media::AlphaType::IMAGE_ALPHA_TYPE_OPAQUE;
    options.scaleMode = Media::ScaleMode::FIT_TARGET_SIZE;

    Media::Rect rect { static_cast<int32_t>(srcRect.Left()), static_cast<int32_t>(srcRect.Top()),
        static_cast<int32_t>(srcRect.Width()), static_cast<int32_t>(srcRect.Height()) };
    auto resPixelmap = OHOS::Media::PixelMap::Create(*pixmap_, rect, options);
    return AceType::MakeRefPtr<PixelMapOhos>(std::move(resPixelmap));
}

uint32_t PixelMapOhos::WritePixels(const WritePixelsOptions& opts)
{
    CHECK_NULL_RETURN(pixmap_, Media::ERR_IMAGE_WRITE_PIXELMAP_FAILED);
    Media::Rect rect { static_cast<int32_t>(opts.region.Left()), static_cast<int32_t>(opts.region.Top()),
        static_cast<int32_t>(opts.region.Width()), static_cast<int32_t>(opts.region.Height()) };
    Media::RWPixelsOptions options;
    options.pixels = opts.source;
    options.bufferSize = opts.bufferSize;
    options.offset = opts.offset;
    options.stride = opts.stride;
    options.region = rect;
    options.pixelFormat = PixelMapOhos::ConvertToMediaPixelFormat(opts.srcPixelFormat);
    return pixmap_->WritePixels(options);
}

uint32_t PixelMapOhos::GetInnerColorGamut() const
{
#ifdef IMAGE_COLORSPACE_FLAG
    if (!pixmap_) {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "pixmap_ is nullptr");
        return ColorManager::ColorSpaceName::NONE;
    }
#else
    return pixmap_->InnerGetGrColorSpace().GetColorSpaceName()；
#endif
    return 0;
}

void PixelMapOhos::SetMemoryName(std::string pixelMapName) const
{
    CHECK_NULL_VOID(pixmap_);
    LOGD("PixelMapOhos::SetMemoryName, %{public}s", pixelMapName.c_str());
    pixmap_->SetMemoryName(pixelMapName);
}
} // namespace OHOS::Ace
