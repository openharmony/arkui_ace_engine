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
#include "mock_image_loader.h"

#include <chrono>

#include "core/image/image_loader.h"

namespace OHOS::Ace {
RefPtr<MockImageLoader> g_loader;

RefPtr<NG::ImageData> ImageLoader::GetImageData(
    const ImageSourceInfo& imageSourceInfo, ImageErrorInfo& errorInfo, const WeakPtr<PipelineBase>& context)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(100ms);
    if (imageSourceInfo.IsPixmap()) {
        return LoadDecodedImageData(imageSourceInfo, errorInfo, context);
    }
    this->LoadImageData(imageSourceInfo, errorInfo, context);
    return nullptr;
}

RefPtr<ImageLoader> ImageLoader::CreateImageLoader(const ImageSourceInfo& /*imageSourceInfo*/)
{
    return g_loader;
}

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    return uri.substr(0);
}

std::shared_ptr<RSData> ImageLoader::LoadDataFromCachedFile(const std::string& /* uri */)
{
    return nullptr;
}

std::shared_ptr<RSData> ImageLoader::QueryImageDataFromImageCache(const ImageSourceInfo& /*sourceInfo*/)
{
    return nullptr;
}

void ImageLoader::CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& imageData) {}

RefPtr<NG::ImageData> ImageLoader::LoadImageDataFromFileCache(const std::string& /*key*/, const std::string& /*suffix*/)
{
    return nullptr;
}

bool NetworkImageLoader::DownloadImage(DownloadCallback&& downloadCallback, const std::string& src, bool sync)
{
    return false;
}

void ImageLoader::WriteCacheToFile(const std::string& uri, const std::vector<uint8_t>& imageData) {}
void ImageLoader::WriteCacheToFile(const std::string& uri, const std::string& imageData) {}
} // namespace OHOS::Ace
