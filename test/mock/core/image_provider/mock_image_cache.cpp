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

#include "core/image/image_cache.h"
#include "core/image/image_file_cache.h"

namespace OHOS::Ace {
void ImageCache::CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image) {}

RefPtr<NG::ImageObject> ImageCache::GetCacheImgObjNG(const std::string& key)
{
    return nullptr;
}

void ImageCache::CacheImgObjNG(const std::string& key, const RefPtr<NG::ImageObject>& imgObj) {}

RefPtr<ImageCache> ImageCache::Create()
{
    return nullptr;
}

RefPtr<NG::ImageData> ImageCache::GetCacheImageData(const std::string& key)
{
    return nullptr;
}

void ImageCache::CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& imageData) {}

void ImageCache::Purge() {}

void ImageCache::ClearCacheImage(const std::string& key) {}
void ImageCache::ClearCacheImgObj(const std::string& key) {}
void ImageCache::Clear() {}
void ImageCache::DumpCacheInfo() {}
} // namespace OHOS::Ace
