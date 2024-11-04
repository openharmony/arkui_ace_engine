/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_CACHE_H

#include <algorithm>
#include <list>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/lru/count_limit_lru.h"

namespace OHOS::Ace {

struct CachedImage;
class ImageObject;

namespace NG {
class ImageObject;
class ImageData;
} // namespace NG

class ACE_EXPORT ImageCache : public AceType {
    DECLARE_ACE_TYPE(ImageCache, AceType);

public:
    static RefPtr<ImageCache> Create();
    ImageCache() = default;
    ~ImageCache() override = default;

    void CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image);
    std::shared_ptr<CachedImage> GetCacheImage(const std::string& key);

    void CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& imageData);
    RefPtr<NG::ImageData> GetCacheImageData(const std::string& key);

    RefPtr<NG::ImageObject> GetCacheImgObjNG(const std::string& key);
    void CacheImgObjNG(const std::string& key, const RefPtr<NG::ImageObject>& imgObj);

    void CacheImgObj(const std::string& key, const RefPtr<ImageObject>& imgObj);
    RefPtr<ImageObject> GetCacheImgObj(const std::string& key);
    /**
    @brief Clears the cached image object associated with the specified key.
    This interface is for internal use only. Exercise caution when calling it.
    @param key The unique identifier for the cached image object.
    */
    void ClearCacheImgObj(const std::string& key);

    void SetCapacity(size_t capacity)
    {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "User Set Capacity : %{public}d", static_cast<int32_t>(capacity));
        capacity_ = capacity;
    }

    void SetDataCacheLimit(size_t sizeLimit)
    {
        TAG_LOGI(AceLogTag::ACE_IMAGE, "User Set data size cache limit : %{public}d", static_cast<int32_t>(sizeLimit));
        dataSizeLimit_ = sizeLimit;
    }

    size_t GetCapacity() const
    {
        return capacity_;
    }

    size_t GetCachedImageCount() const
    {
        std::lock_guard<std::mutex> lock(imageCacheMutex_);
        return cacheList_.size();
    }

    void Clear();
    static void Purge();

    void ClearCacheImage(const std::string& key);
    void DumpCacheInfo();

private:
    bool ProcessImageDataCacheInner(size_t dataSize, std::vector<CacheNode<RefPtr<NG::ImageData>>>& needErase);

    std::atomic<size_t> capacity_ = 0; // by default memory cache can store 0 images.
    mutable std::mutex imageCacheMutex_;
    std::list<CacheNode<std::shared_ptr<CachedImage>>> cacheList_;
    std::unordered_map<std::string, std::list<CacheNode<std::shared_ptr<CachedImage>>>::iterator> imageCache_;

    std::timed_mutex dataCacheMutex_;
    std::list<CacheNode<RefPtr<NG::ImageData>>> dataCacheList_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<NG::ImageData>>>::iterator> imageDataCache_;

    std::atomic<size_t> dataSizeLimit_ = 0; // by default, image data before decoded cache is 0 MB.;
    std::atomic<size_t> curDataSize_ = 0;

    std::mutex imgObjMutex_;
    std::atomic<size_t> imgObjCapacity_ = 2000; // imgObj is cached after clear image data.

    std::list<CacheNode<RefPtr<NG::ImageObject>>> cacheImgObjListNG_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<NG::ImageObject>>>::iterator> imgObjCacheNG_;
    std::list<CacheNode<RefPtr<ImageObject>>> cacheImgObjList_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<ImageObject>>>::iterator> imgObjCache_;

    ACE_DISALLOW_COPY_AND_MOVE(ImageCache);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_CACHE_H
