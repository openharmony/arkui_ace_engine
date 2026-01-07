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

#include "image_source_preview.h"

#include "include/codec/SkEncodedImageFormat.h"
#include "include/core/SkStream.h"

#include "base/image/image_defines.h"
#include "base/image/image_source.h"

namespace OHOS::Ace {
namespace {
ImageRotateOrientation GetImageRotateOrientation(SkEncodedOrigin origin)
{
    switch (origin) {
        case SkEncodedOrigin::kTopRight_SkEncodedOrigin:
            return ImageRotateOrientation::UP_MIRRORED;
        case SkEncodedOrigin::kBottomRight_SkEncodedOrigin:
            // Rotated 180
            return ImageRotateOrientation::DOWN;
        case SkEncodedOrigin::kBottomLeft_SkEncodedOrigin:
            return ImageRotateOrientation::DOWN_MIRRORED;
        case SkEncodedOrigin::kLeftTop_SkEncodedOrigin:
            // Reflected across x-axis, Rotated 90 CCW
            return ImageRotateOrientation::LEFT_MIRRORED;
        case SkEncodedOrigin::kRightTop_SkEncodedOrigin:
            // Rotated 90 CW
            return ImageRotateOrientation::RIGHT;
        case SkEncodedOrigin::kRightBottom_SkEncodedOrigin:
            // Reflected across x-axis, Rotated 90 CW
            return ImageRotateOrientation::RIGHT_MIRRORED;
        case SkEncodedOrigin::kLeftBottom_SkEncodedOrigin:
            // Rotated 90 CCW
            return ImageRotateOrientation::LEFT;
        case SkEncodedOrigin::kTopLeft_SkEncodedOrigin:
            return ImageRotateOrientation::UP;
        default:
            return ImageRotateOrientation::UP;
    }
}
}
RefPtr<ImageSource> ImageSource::Create(int32_t /* fd */)
{
    return nullptr;
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size)
{
    return nullptr;
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size, uint32_t& errorCode)
{
    auto skData = SkData::MakeWithCopy(data, size);
    if (!skData) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "skData is null");
        errorCode = static_cast<uint32_t>(ImageInnerErrorCode::SK_DATA_CREATE_ERROR);
        return nullptr;
    }
    auto codec = SkCodec::MakeFromData(skData);
    if (!codec) {
        TAG_LOGW(AceLogTag::ACE_IMAGE, "codec is null");
        errorCode =  static_cast<uint32_t>(ImageInnerErrorCode::SK_CODEC_CREATE_ERROR);
        return nullptr;
    }
    return MakeRefPtr<ImageSourcePreview>(std::move(codec));
}

RefPtr<ImageSource> ImageSource::Create(const std::string& filePath)
{
    return nullptr;
}

bool ImageSource::IsAstc(const uint8_t* data, size_t size)
{
    return false;
}

ImageSource::Size ImageSource::GetASTCInfo(const uint8_t* data, size_t size)
{
    return { 0, 0 };
}

std::string ImageSourcePreview::GetProperty(const std::string& /* key */)
{
    return "";
}

RefPtr<PixelMap> ImageSourcePreview::CreatePixelMap(
    const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig)
{
    return nullptr;
}

RefPtr<PixelMap> ImageSourcePreview::CreatePixelMap(
    uint32_t index, const Size& size, uint32_t& errorCode, const PixelMapConfig& pixelMapConfig)
{
    return nullptr;
}

RefPtr<PixelMap> ImageSourcePreview::CreatePixelMap(const DecodeOptions& options)
{
    return nullptr;
}

RefPtr<PixelMap> ImageSourcePreview::CreatePixelMap()
{
    return nullptr;
}

ImageSource::Size ImageSourcePreview::GetImageSize()
{
    CHECK_NULL_RETURN(codec_, {});
    return { codec_->dimensions().fWidth, codec_->dimensions().fHeight };
}

uint32_t ImageSourcePreview::GetFrameCount()
{
    CHECK_NULL_RETURN(codec_, {});
    return codec_->getFrameCount();
}

std::string ImageSourcePreview::GetEncodedFormat()
{
    return "";
}

int32_t ImageSourcePreview::GetLoopCount()
{
    return -1;
}

std::vector<int32_t> ImageSourcePreview::GetDelayTime()
{
    return {};
}

bool ImageSourcePreview::IsHeifWithoutAlpha()
{
    return false;
}

ImageRotateOrientation ImageSourcePreview::GetImageOrientation()
{
    auto origin = codec_->getOrigin();
    return GetImageRotateOrientation(origin);
}
} // namespace OHOS::Ace
