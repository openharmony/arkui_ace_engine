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

#include "frameworks/base/image/image_source.h"
namespace OHOS::Ace {
RefPtr<ImageSource> ImageSource::Create(int32_t /* fd */)
{
    return nullptr;
}

RefPtr<ImageSource> ImageSource::Create(const uint8_t* data, uint32_t size, uint32_t& errorCode)
{
    return nullptr;
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
    return {};
}

uint32_t ImageSourcePreview::GetFrameCount()
{
    return 0;
}

std::string ImageSourcePreview::GetEncodedFormat()
{
    return "";
}
} // namespace OHOS::Ace
