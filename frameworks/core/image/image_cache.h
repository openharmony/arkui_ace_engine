/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
#include <unordered_map>
#include <vector>

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace {

struct CachedImage;

struct CacheNode {
    CacheNode(const std::string& key, const std::shared_ptr<CachedImage>& image)
        : imageKey(key), imagePtr(image)
    {}
    std::string imageKey;
    std::shared_ptr<CachedImage> imagePtr;
};

struct FileInfo {
    FileInfo(const std::string& path, size_t size, time_t time)
        : filePath(path), fileSize(size), accessTime(time)
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
    ~ImageCache() = default;
    void CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image);
    std::shared_ptr<CachedImage> GetCacheImage(const std::string& key);
    static void SetCacheFileInfo();
    static void WriteCacheFile(const std::string& url, std::vector<uint8_t>& byteData);

    void RemoveCachedImage(const std::string& key)
    {
        std::scoped_lock lock(imageCacheMutex_, cacheListMutex_);
        cacheList_.remove_if([&key](const CacheNode& cacheNode) { return cacheNode.imageKey == key; });
        imageCache_.erase(key);
    }

    void SetCapacity(size_t capacity)
    {
        capacity_ = capacity;
    }

    size_t GetCapacity() const
    {
        return capacity_;
    }

    size_t GetCachedImageCount() const
    {
        std::lock_guard<std::mutex> lock(cacheListMutex_);
        return cacheList_.size();
    }

    static void SetImageCacheFilePath(const std::string& cacheFilePath)
    {
        std::lock_guard<std::mutex> lock(cacheFilePathMutex_);
        if (cacheFilePath_.empty()) {
            cacheFilePath_ = cacheFilePath;
        }
    }

    static std::string GetImageCacheFilePath()
    {
        std::lock_guard<std::mutex> lock(cacheFilePathMutex_);
        return cacheFilePath_;
    }

    static std::string GetNetworkImageCacheFilePath(const std::string& url)
    {
        std::lock_guard<std::mutex> lock(cacheFilePathMutex_);
#if !defined(WINDOWS_PLATFORM) && !defined(MAC_PLATFORM)
        return cacheFilePath_ + "/" + std::to_string(std::hash<std::string> {}(url));
#elif defined(MAC_PLATFORM)
        return "/tmp/" + std::to_string(std::hash<std::string> {}(url));
#elif defined(WINDOWS_PLATFORM)
        char *pathvar;
        pathvar = getenv("TEMP");
        if (!pathvar) {
            return std::string("C:\\Windows\\Temp") + "\\" + std::to_string(std::hash<std::string> {}(url));
        }
        return std::string(pathvar) + "\\" + std::to_string(std::hash<std::string> {}(url));
#endif
    }

    static void SetCacheFileLimit(size_t cacheFileLimit)
    {
        cacheFileLimit_ = cacheFileLimit;
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

    static bool GetFromCacheFile(const std::string& filePath)
    {
        std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
        std::list<FileInfo>::iterator iter = std::find_if(cacheFileInfo_.begin(), cacheFileInfo_.end(),
            [&filePath](const FileInfo& fileInfo) { return fileInfo.filePath == filePath; });
        if (iter == cacheFileInfo_.end()) {
            return false;
        }
        iter->accessTime = time(nullptr);
        cacheFileInfo_.splice(cacheFileInfo_.end(), cacheFileInfo_, iter);
        return true;
    }

    virtual void Clear() = 0;

protected:
    static void ClearCacheFile(const std::vector<std::string>& removeFiles);

    mutable std::mutex cacheListMutex_;
    std::list<CacheNode> cacheList_;

    std::mutex imageCacheMutex_;
    std::unordered_map<std::string, std::list<CacheNode>::iterator> imageCache_;

    std::atomic<size_t> capacity_ = 80; // by default memory cache can store 80 images.

    static std::mutex cacheFilePathMutex_;
    static std::string cacheFilePath_;

    static std::atomic<size_t> cacheFileLimit_;

    static std::atomic<float> clearCacheFileRatio_;

    static std::mutex cacheFileSizeMutex_;
    static int32_t cacheFileSize_;

    static std::mutex cacheFileInfoMutex_;
    static std::list<FileInfo> cacheFileInfo_;
    static bool hasSetCacheFileInfo_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_CACHE_H
