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

#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

struct CachedImage;
class ImageObject;

namespace NG {
class ImageObject;
} // namespace NG

template<typename T>
struct CacheNode {
    CacheNode(std::string key, const T& obj) : cacheKey(std::move(key)), cacheObj(obj) {}
    std::string cacheKey;
    T cacheObj;
};

struct CachedImageData : public AceType {
    DECLARE_ACE_TYPE(CachedImageData, AceType);

public:
    CachedImageData() = default;
    virtual ~CachedImageData() = default;
    virtual size_t GetSize() = 0;
    virtual const uint8_t* GetData() = 0;
};

struct CacheImageDataNode {
    CacheImageDataNode(const std::string& key, const RefPtr<CachedImageData>& imageData)
        : imageDataKey(key), imageDataPtr(imageData)
    {}
    std::string imageDataKey;
    RefPtr<CachedImageData> imageDataPtr;
};

struct FileInfo {
    FileInfo(std::string path, size_t size, time_t time) : filePath(std::move(path)), fileSize(size), accessTime(time)
    {}

    // file information will be sort by access time.
    bool operator<(const FileInfo& otherFile) const
    {
        return accessTime < otherFile.accessTime;
    }
    std::string filePath;
    size_t fileSize;
    time_t accessTime;
};

class ACE_EXPORT ImageCache : public AceType {
    DECLARE_ACE_TYPE(ImageCache, AceType);

public:
    static RefPtr<ImageCache> Create();
    ImageCache() = default;
    ~ImageCache() override = default;

    void CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image);
    std::shared_ptr<CachedImage> GetCacheImage(const std::string& key);

    void CacheImageData(const std::string& key, const RefPtr<CachedImageData>& imageData);
    RefPtr<CachedImageData> GetCacheImageData(const std::string& key);

    // cache interface for [NG::ImageObject]
    RefPtr<NG::ImageObject> GetCacheImgObjNG(const std::string& key);
    void CacheImgObjNG(const std::string& key, const RefPtr<NG::ImageObject>& imgObj);

    void CacheImgObj(const std::string& key, const RefPtr<ImageObject>& imgObj);
    RefPtr<ImageObject> GetCacheImgObj(const std::string& key);

    static void SetCacheFileInfo();
    static void WriteCacheFile(
        const std::string& url, const void* data, size_t size, const std::string& suffix = std::string());

    void SetCapacity(size_t capacity)
    {
        LOGI("Set Capacity : %{public}d", static_cast<int32_t>(capacity));
        capacity_ = capacity;
    }

    void SetDataCacheLimit(size_t sizeLimit)
    {
        LOGI("Set data size cache limit : %{public}d", static_cast<int32_t>(sizeLimit));
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

    static void SetImageCacheFilePath(const std::string& cacheFilePath)
    {
        std::unique_lock<std::shared_mutex> lock(cacheFilePathMutex_);
        if (cacheFilePath_.empty()) {
            cacheFilePath_ = cacheFilePath;
        }
    }

    static std::string GetImageCacheFilePath()
    {
        std::shared_lock<std::shared_mutex> lock(cacheFilePathMutex_);
        return cacheFilePath_;
    }

    static std::string GetImageCacheFilePath(const std::string& url)
    {
        std::shared_lock<std::shared_mutex> lock(cacheFilePathMutex_);
#if !defined(PREVIEW)
        return cacheFilePath_ + "/" + std::to_string(std::hash<std::string> {}(url));
#elif defined(MAC_PLATFORM) || defined(LINUX_PLATFORM)
        return "/tmp/" + std::to_string(std::hash<std::string> {}(url));
#elif defined(WINDOWS_PLATFORM)
        char* pathvar;
        pathvar = getenv("TEMP");
        if (!pathvar) {
            return std::string("C:\\Windows\\Temp") + "\\" + std::to_string(std::hash<std::string> {}(url));
        }
        return std::string(pathvar) + "\\" + std::to_string(std::hash<std::string> {}(url));
#endif
    }

    static void SetCacheFileLimit(size_t cacheFileLimit)
    {
        LOGI("Set file cache limit size : %{public}d", static_cast<int32_t>(cacheFileLimit));
        fileLimit_ = cacheFileLimit;
    }

    static void SetClearCacheFileRatio(float clearRatio)
    {
        // clearRatio must in (0, 1].
        if (clearRatio < 0) {
            clearRatio = 0.1f;
        } else if (clearRatio > 1) {
            clearRatio = 1.0f;
        }
        clearCacheFileRatio_ = clearRatio;
    }

    static bool GetFromCacheFile(const std::string& filePath);

    virtual void Clear() = 0;

    virtual RefPtr<CachedImageData> GetDataFromCacheFile(const std::string& filePath) = 0;

    static void Purge();

    void ClearCacheImage(const std::string& key);

protected:
    static void ClearCacheFile(const std::vector<std::string>& removeFiles);

    template<typename T>
    static void CacheWithCountLimitLRU(const std::string& key, const T& cacheObj, std::list<CacheNode<T>>& cacheList,
        std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache,
        const std::atomic<size_t>& capacity);

    template<typename T>
    static T GetCacheObjWithCountLimitLRU(const std::string& key, std::list<CacheNode<T>>& cacheList,
        std::unordered_map<std::string, typename std::list<CacheNode<T>>::iterator>& cache);

    static bool GetFromCacheFileInner(const std::string& filePath);

    bool ProcessImageDataCacheInner(size_t dataSize);

    std::atomic<size_t> capacity_ = 0; // by default memory cache can store 0 images.
    mutable std::mutex imageCacheMutex_;
    std::list<CacheNode<std::shared_ptr<CachedImage>>> cacheList_;
    std::unordered_map<std::string, std::list<CacheNode<std::shared_ptr<CachedImage>>>::iterator> imageCache_;

    std::mutex dataCacheMutex_;
    std::list<CacheImageDataNode> dataCacheList_;
    std::unordered_map<std::string, std::list<CacheImageDataNode>::iterator> imageDataCache_;

    std::atomic<size_t> dataSizeLimit_ = 0; // by default, image data before decoded cache is 0 MB.;
    std::atomic<size_t> curDataSize_ = 0;

    std::mutex imgObjCacheMutex_;
    std::list<CacheNode<RefPtr<ImageObject>>> cacheImgObjList_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<ImageObject>>>::iterator> imgObjCache_;
    std::atomic<size_t> imgObjCapacity_ = 2000; // imgObj is cached after clear image data.

    std::list<CacheNode<RefPtr<NG::ImageObject>>> cacheImgObjListNG_;
    std::unordered_map<std::string, std::list<CacheNode<RefPtr<NG::ImageObject>>>::iterator> imgObjCacheNG_;

    static std::shared_mutex cacheFilePathMutex_;
    static std::string cacheFilePath_;

    static std::atomic<size_t> fileLimit_;

    static std::atomic<float> clearCacheFileRatio_;

    static std::mutex cacheFileSizeMutex_;
    static int64_t cacheFileSize_;

    static std::mutex cacheFileInfoMutex_;
    static std::list<FileInfo> cacheFileInfo_;
    static bool hasSetCacheFileInfo_;
};

struct PixmapCachedData : public CachedImageData {
    DECLARE_ACE_TYPE(PixmapCachedData, CachedImageData);

public:
    explicit PixmapCachedData(const RefPtr<PixelMap>& data) : pixmap_(data) {}
    ~PixmapCachedData() override = default;

    size_t GetSize() override
    {
        return pixmap_ ? pixmap_->GetByteCount() : 0;
    }

    const uint8_t* GetData() override
    {
        return pixmap_ ? pixmap_->GetPixels() : nullptr;
    }

    const RefPtr<PixelMap> pixmap_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_CACHE_H
