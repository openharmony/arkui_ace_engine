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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_FILE_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_FILE_CACHE_H
#include <list>
#include <mutex>
#include <shared_mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "base/utils/singleton.h"
#include "core/components_ng/image_provider/image_data.h"

namespace OHOS::Ace {
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

class ImageFileCache : public Singleton<ImageFileCache> {
    DECLARE_SINGLETON(ImageFileCache);
    ACE_DISALLOW_MOVE(ImageFileCache);
public:
    void SetImageCacheFilePath(const std::string& cacheFilePath);
    std::string GetImageCacheFilePath();
    std::string GetImageCacheFilePath(const std::string& url);

    void SetCacheFileLimit(size_t cacheFileLimit);
    void SetClearCacheFileRatio(float clearRatio);

    bool GetFromCacheFile(const std::string& filePath);

    RefPtr<NG::ImageData> GetDataFromCacheFile(const std::string& filePath);

    void SetCacheFileInfo();
    void WriteCacheFile(
        const std::string& url, const void* data, size_t size, const std::string& suffix = std::string());
    void ClearCacheFile(const std::vector<std::string>& removeFiles);
private:
    bool GetFromCacheFileInner(const std::string& filePath);

    std::shared_mutex cacheFilePathMutex_;
    std::string cacheFilePath_;

    std::atomic<size_t> fileLimit_ = 100 * 1024 * 1024; // the capacity is 100MB

    std::atomic<float> clearCacheFileRatio_ = 0.5f; // default clear ratio is 0.5

    std::mutex cacheFileSizeMutex_;
    int64_t cacheFileSize_ = 0;

    std::mutex cacheFileInfoMutex_;
    std::list<FileInfo> cacheFileInfo_;
    bool hasSetCacheFileInfo_ = false;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_IMAGE_FILE_CACHE_H