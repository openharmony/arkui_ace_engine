/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/image/image_cache.h"
#include "core/image/image_file_cache.h"

namespace OHOS::Ace {
std::string g_cacheFilePath = "this is test cache file path.";
ImageFileCache::ImageFileCache() = default;
ImageFileCache::~ImageFileCache() = default;
void ImageFileCache::DumpCacheInfo() {}
void ImageFileCache::EraseCacheFile(const std::string &url) {}
std::string ImageFileCache::GetImageCacheFilePath(const std::string& url)
{
    return g_cacheFilePath;
}
std::string ImageFileCache::GetCacheFilePath(const std::string& url)
{
    return g_cacheFilePath;
}
void ImageFileCache::WriteCacheFile(const std::string& url, const void* data, size_t size, const std::string& suffix) {}
void ImageFileCache::SetImageCacheFilePath(const std::string& cacheFilePath)
{
    g_cacheFilePath = cacheFilePath;
}
} // namespace OHOS::Ace
