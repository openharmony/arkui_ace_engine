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

#include "core/image/image_cache.h"

#include "base/log/dump_log.h"
#include "core/components_ng/image_provider/image_object.h"
#include "core/image/image_object.h"

namespace OHOS::Ace {
namespace {
constexpr uint64_t MAX_WAITING_TIME = 1000; // 1000ms
}
RefPtr<ImageCache> ImageCache::Create()
{
    return MakeRefPtr<ImageCache>();
}

// TODO: Create a real ImageCache later
#ifdef FLUTTER_2_5
class MockImageCache : public ImageCache {
    void Clear() override {};
    RefPtr<NG::ImageData> GetDataFromCacheFile(const std::string& filePath) override
    {
        return nullptr;
    }
};

RefPtr<ImageCache> ImageCache::Create()
{
    return AceType::MakeRefPtr<MockImageCache>();
}

void ImageCache::Purge() {}
#endif

void ImageCache::CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image)
{
    if (key.empty() || capacity_ == 0) {
        return;
    }
    std::scoped_lock lock(imageCacheMutex_);
    CountLimitLRU::CacheWithCountLimitLRU<std::shared_ptr<CachedImage>>(key, image, cacheList_, imageCache_, capacity_);
}

std::shared_ptr<CachedImage> ImageCache::GetCacheImage(const std::string& key)
{
    std::scoped_lock lock(imageCacheMutex_);
    return CountLimitLRU::GetCacheObjWithCountLimitLRU<std::shared_ptr<CachedImage>>(key, cacheList_, imageCache_);
}

void ImageCache::CacheImgObjNG(const std::string& key, const RefPtr<NG::ImageObject>& imgObj)
{
    if (key.empty() || imgObjCapacity_ == 0) {
        return;
    }
    std::scoped_lock lock(imgObjMutex_);
    CountLimitLRU::CacheWithCountLimitLRU<RefPtr<NG::ImageObject>>(
        key, imgObj, cacheImgObjListNG_, imgObjCacheNG_, imgObjCapacity_);
}

RefPtr<NG::ImageObject> ImageCache::GetCacheImgObjNG(const std::string& key)
{
    std::scoped_lock lock(imgObjMutex_);
    return CountLimitLRU::GetCacheObjWithCountLimitLRU<RefPtr<NG::ImageObject>>(
        key, cacheImgObjListNG_, imgObjCacheNG_);
}

void ImageCache::CacheImgObj(const std::string& key, const RefPtr<ImageObject>& imgObj)
{
    if (key.empty() || imgObjCapacity_ == 0) {
        return;
    }
    std::scoped_lock lock(imgObjMutex_);
    CountLimitLRU::CacheWithCountLimitLRU<RefPtr<ImageObject>>(
        key, imgObj, cacheImgObjList_, imgObjCache_, imgObjCapacity_);
}

RefPtr<ImageObject> ImageCache::GetCacheImgObj(const std::string& key)
{
    std::scoped_lock lock(imgObjMutex_);
    return CountLimitLRU::GetCacheObjWithCountLimitLRU<RefPtr<ImageObject>>(key, cacheImgObjList_, imgObjCache_);
}

void ImageCache::CacheImageData(const std::string& key, const RefPtr<NG::ImageData>& imageData)
{
    if (key.empty() || !imageData || dataSizeLimit_ == 0) {
        return;
    }
    ACE_SCOPED_TRACE("CacheImageData key:%s", key.c_str());
    auto dataSize = imageData->GetSize();
    std::vector<CacheNode<RefPtr<NG::ImageData>>> needErase;

    // Try to acquire the dataCacheMutex_ lock within MAX_WAITING_TIME milliseconds to avoid long blocking.
    if (!dataCacheMutex_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME))) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "Failed to acquire mutex within %{public}" PRIu64 "milliseconds, proceeding without cache access.",
            MAX_WAITING_TIME);
        return;
    }
    // Adopt the already acquired lock
    std::scoped_lock lock(std::adopt_lock, dataCacheMutex_);
    auto iter = imageDataCache_.find(key);
    bool inCache = (iter != imageDataCache_.end());
    bool largerHalfSize = dataSize > (dataSizeLimit_ >> 1);
    size_t oldSize = !inCache ? 0 : iter->second->cacheObj->GetSize();
    if (largerHalfSize && inCache) {
        // if data is longer than half limit, do not cache it.
        // and if the key is in Cache, erase it.
        curDataSize_ -= oldSize;
        needErase.push_back(*(iter->second));
        dataCacheList_.erase(iter->second);
        imageDataCache_.erase(key);
        TAG_LOGW(AceLogTag::ACE_IMAGE, "data is %{public}d, bigger than half limit %{public}d, do not cache it",
            static_cast<int32_t>(dataSize), static_cast<int32_t>(dataSizeLimit_ >> 1));
    } else if (!largerHalfSize && !inCache && ProcessImageDataCacheInner(dataSize, needErase)) {
        dataCacheList_.emplace_front(key, imageData);
        imageDataCache_.emplace(key, dataCacheList_.begin());
    } else if (!largerHalfSize && inCache && oldSize >= dataSize) {
        // if the image is in the cache, and dataSize <= oldSize, we can replace the imageData in cache.
        curDataSize_ = curDataSize_ + dataSize - oldSize;
        iter->second->cacheObj = imageData;
        dataCacheList_.splice(dataCacheList_.begin(), dataCacheList_, iter->second);
        iter->second = dataCacheList_.begin();
    } else if (!largerHalfSize && inCache && oldSize < dataSize) {
        // if the image is in the cache, and dataSize > oldSize, we erase the old one, the try to cache the new image.
        curDataSize_ -= oldSize;
        needErase.push_back(*(iter->second));
        dataCacheList_.erase(iter->second);
        imageDataCache_.erase(key);
        if (ProcessImageDataCacheInner(dataSize, needErase)) {
            dataCacheList_.emplace_front(key, imageData);
            imageDataCache_.emplace(key, dataCacheList_.begin());
        }
    }
}

bool ImageCache::ProcessImageDataCacheInner(size_t dataSize, std::vector<CacheNode<RefPtr<NG::ImageData>>>& needErase)
{
    while (dataSize + curDataSize_ > dataSizeLimit_ && !dataCacheList_.empty()) {
        curDataSize_ -= dataCacheList_.back().cacheObj->GetSize();
        needErase.push_back(dataCacheList_.back());
        imageDataCache_.erase(dataCacheList_.back().cacheKey);
        dataCacheList_.pop_back();
    }
    if (dataSize + curDataSize_ > dataSizeLimit_) {
        return false;
    }
    curDataSize_ += dataSize;
    return true;
}

RefPtr<NG::ImageData> ImageCache::GetCacheImageData(const std::string& key)
{
    ACE_SCOPED_TRACE("GetCacheImageData key:%s", key.c_str());
    // Try to acquire the dataCacheMutex_ lock within MAX_WAITING_TIME milliseconds to avoid long blocking.
    if (!dataCacheMutex_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME))) {
        TAG_LOGW(AceLogTag::ACE_IMAGE,
            "Failed to acquire mutex within %{public}" PRIu64 "milliseconds, proceeding without cache access.",
            MAX_WAITING_TIME);
        return nullptr;
    }
    // Adopt the already acquired lock
    std::scoped_lock lock(std::adopt_lock, dataCacheMutex_);
    auto iter = imageDataCache_.find(key);
    if (iter != imageDataCache_.end()) {
        dataCacheList_.splice(dataCacheList_.begin(), dataCacheList_, iter->second);
        iter->second = dataCacheList_.begin();
        return iter->second->cacheObj;
    }
    return nullptr;
}

void ImageCache::ClearCacheImage(const std::string& key)
{
    ACE_SCOPED_TRACE("ClearCacheImage key:%s", key.c_str());
    {
        std::scoped_lock lock(imageCacheMutex_);
        auto iter = imageCache_.find(key);
        if (iter != imageCache_.end()) {
            cacheList_.erase(iter->second);
            imageCache_.erase(iter);
        }
    }

    {
        // Try to acquire the dataCacheMutex_ lock within MAX_WAITING_TIME milliseconds to avoid long blocking.
        if (!dataCacheMutex_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME))) {
            TAG_LOGW(AceLogTag::ACE_IMAGE,
                "Failed to acquire mutex within %{public}" PRIu64 "milliseconds, proceeding without cache access.",
                MAX_WAITING_TIME);
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, dataCacheMutex_);
        auto iter = imageDataCache_.find(key);
        if (iter != imageDataCache_.end()) {
            dataCacheList_.erase(iter->second);
            imageDataCache_.erase(iter);
        }
    }
}

void ImageCache::Clear()
{
    ACE_SCOPED_TRACE("ImageCache Clear");
    {
        std::scoped_lock lock(imageCacheMutex_);
        cacheList_.clear();
        imageCache_.clear();
    }
    {
        // Try to acquire the dataCacheMutex_ lock within MAX_WAITING_TIME milliseconds to avoid long blocking.
        if (!dataCacheMutex_.try_lock_for(std::chrono::milliseconds(MAX_WAITING_TIME))) {
            TAG_LOGW(AceLogTag::ACE_IMAGE,
                "Failed to acquire mutex within %{public}" PRIu64 "milliseconds, proceeding without cache access.",
                MAX_WAITING_TIME);
            return;
        }
        // Adopt the already acquired lock
        std::scoped_lock lock(std::adopt_lock, dataCacheMutex_);
        dataCacheList_.clear();
        imageDataCache_.clear();
    }
    {
        std::scoped_lock lock(imgObjMutex_);
        cacheImgObjListNG_.clear();
        imgObjCacheNG_.clear();
        cacheImgObjList_.clear();
        imgObjCache_.clear();
    }
}

void ImageCache::DumpCacheInfo()
{
    auto cacheSize = dataCacheList_.size();
    auto capacity = static_cast<int32_t>(capacity_);
    auto dataSizeLimit = static_cast<int32_t>(dataSizeLimit_);
    DumpLog::GetInstance().Print("------------ImageCacheInfo------------");
    DumpLog::GetInstance().Print("User set ImageRawDataCacheSize : " + std::to_string(dataSizeLimit) + "(B)" +
                                 ", ImageCacheCount :" + std::to_string(capacity) + "(number)");
    DumpLog::GetInstance().Print("Cache count: " + std::to_string(cacheSize));
    if (cacheSize == 0) {
        return;
    }
    auto totalCount = 0;
    for (const auto& item : dataCacheList_) {
        auto imageObj = item.cacheObj;
        auto key = item.cacheKey;
        std::string srcStr = "NA";
        for (const auto& cacheImageObj : cacheImgObjListNG_) {
            if (cacheImageObj.cacheKey == key) {
                srcStr = cacheImageObj.cacheObj->GetSourceInfo().ToString();
                break;
            }
        }
        totalCount += static_cast<int32_t>(imageObj->GetSize());
        DumpLog::GetInstance().Print("Cache Obj of key: " + key + ", src:" + srcStr + "," + imageObj->ToString());
    }
    DumpLog::GetInstance().Print("Cache total size: " + std::to_string(totalCount));
}
} // namespace OHOS::Ace
