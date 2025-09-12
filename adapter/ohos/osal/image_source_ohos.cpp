/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "image_source_ohos.h"

#include "media_errors.h"
#include "pixel_map_ohos.h"

namespace OHOS::Ace {
namespace {
void InitDecodeOptions(Media::DecodeOptions& options, const std::pair<int32_t, int32_t>& size,
    AIImageQuality imageQuality, bool isHdrDecoderNeed, PixelFormat photoDecodeFormat)
{
    options.preferDma = true;
    // only hdr image need to decoder in hdr mode
    if (isHdrDecoderNeed) {
        options.desiredDynamicRange = Media::DecodeDynamicRange::AUTO;
    }
    if (photoDecodeFormat == PixelFormat::NV21) {
        options.photoDesiredPixelFormat = Media::PixelFormat::NV21;
    } else if (photoDecodeFormat == PixelFormat::RGBA_8888) {
        options.photoDesiredPixelFormat = Media::PixelFormat::RGBA_8888;
    } else if (photoDecodeFormat == PixelFormat::RGBA_1010102) {
        options.photoDesiredPixelFormat = Media::PixelFormat::RGBA_1010102;
    } else if (photoDecodeFormat == PixelFormat::YCBCR_P010) {
        options.photoDesiredPixelFormat = Media::PixelFormat::YCBCR_P010;
    } else if (photoDecodeFormat == PixelFormat::YCRCB_P010) {
        options.photoDesiredPixelFormat = Media::PixelFormat::YCRCB_P010;
    }
    // Pass imageQuality to imageFramework
    options.resolutionQuality = static_cast<Media::ResolutionQuality>(imageQuality);
    if (size.first > 0 && size.second > 0) {
        options.desiredSize = { size.first, size.second };
    }
}
} // namespace

RefPtr<ImageSource> ImageSource::Create(int32_t fd)
{
    uint32_t errorCode;
    Media::SourceOptions options;
    auto src = Media::ImageSource::CreateImageSource(fd, options, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create image source failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return MakeRefPtr<ImageSourceOhos>(std::move(src));
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size)
{
    uint32_t errorCode = 0;
    Media::SourceOptions options;
    auto src = Media::ImageSource::CreateImageSource(data, size, options, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create image source failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return MakeRefPtr<ImageSourceOhos>(std::move(src));
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size, uint32_t& errorCode)
{
    Media::SourceOptions options;
    auto src = Media::ImageSource::CreateImageSource(data, size, options, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create image source failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return MakeRefPtr<ImageSourceOhos>(std::move(src));
}

RefPtr<ImageSource> ImageSource::Create(const std::string& filePath)
{
    Media::SourceOptions opts;
    uint32_t errorCode = 0;
    auto src = Media::ImageSource::CreateImageSource(filePath, opts, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create image source failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return MakeRefPtr<ImageSourceOhos>(std::move(src));
}

bool ImageSource::IsAstc(const uint8_t* data, size_t size)
{
    return Media::ImageSource::IsASTC(data, size);
}

ImageSource::Size ImageSource::GetASTCInfo(const uint8_t* data, size_t size)
{
    Media::ASTCInfo astcInfo;
    Media::ImageSource::GetASTCInfo(data, size, astcInfo);
    return { astcInfo.size.width, astcInfo.size.height };
}

std::string ImageSourceOhos::GetProperty(const std::string& key)
{
    std::string value;
    uint32_t res = imageSource_->GetImagePropertyString(0, key, value);
    if (res != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get ImageSource property %{public}s failed, errorCode = %{public}u",
            key.c_str(), res);
    }
    return value;
}

RefPtr<PixelMap> ImageSourceOhos::CreatePixelMap(
    const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig)
{
    return CreatePixelMap(0, size, errorCode, pixelMapConfig);
}

RefPtr<PixelMap> ImageSourceOhos::CreatePixelMap(
    uint32_t index, const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig)
{
    Media::DecodeOptions options;
    InitDecodeOptions(
        options, size, pixelMapConfig.imageQuality, pixelMapConfig.isHdrDecoderNeed, pixelMapConfig.photoDecodeFormat);
    auto pixmap = imageSource_->CreatePixelMapEx(index, options, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "create PixelMap from ImageSource failed, index = %{public}u, errorCode = %{public}u", index, errorCode);
        return nullptr;
    }
    return PixelMap::Create(std::move(pixmap));
}

RefPtr<PixelMap> ImageSourceOhos::CreatePixelMap()
{
    uint32_t errorCode;
    Media::DecodeOptions decodeOpts;
    auto pixelMap = imageSource_->CreatePixelMap(decodeOpts, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create PixelMap from ImageSource failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return PixelMap::Create(std::move(pixelMap));
}

ImageSource::Size ImageSourceOhos::GetImageSize()
{
    Media::ImageInfo info;
    auto errorCode = imageSource_->GetImageInfo(info);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get ImageSource info failed, errorCode = %{public}u", errorCode);
        return { 0, 0 };
    }
    return { info.size.width, info.size.height };
}

RefPtr<PixelMap> ImageSourceOhos::CreatePixelMap(const DecodeOptions& options)
{
    uint32_t errorCode;
    Media::DecodeOptions decodeOpts;
    decodeOpts.desiredPixelFormat = PixelMapOhos::ConvertToMediaPixelFormat(options.desiredFormat);
    auto pixelmap = imageSource_->CreatePixelMap(decodeOpts, errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "create pixelmap failed, errorCode = %{public}u", errorCode);
        return nullptr;
    }
    return PixelMap::Create(std::move(pixelmap));
}

uint32_t ImageSourceOhos::GetFrameCount()
{
    uint32_t errorCode;
    auto frameCount = imageSource_->GetFrameCount(errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get image frame count failed, errorCode = %{public}u", errorCode);
        return 0;
    }
    return frameCount;
}

int32_t ImageSourceOhos::GetLoopCount()
{
    uint32_t errorCode;
    auto loopCount = imageSource_->GetLoopCount(errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get image loop count failed, errorCode = %{public}u", errorCode);
        return 0;
    }
    return loopCount;
}
std::vector<int32_t> ImageSourceOhos::GetDelayTime()
{
    uint32_t errorCode;
    auto delayTime = imageSource_->GetDelayTime(errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get image delay time failed, errorCode = %{public}u", errorCode);
        return {};
    }
    return std::move(*delayTime.release());
}

std::string ImageSourceOhos::GetEncodedFormat()
{
    uint32_t errorCode;
    auto sourceInfo = imageSource_->GetSourceInfo(errorCode);
    if (errorCode != Media::SUCCESS) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "Get image source info failed, errorCode = %{public}u", errorCode);
        return "";
    }
    return sourceInfo.encodedFormat;
}
} // namespace OHOS::Ace
