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

#include "core/image/image_cache.h"

#include <dirent.h>
#include <fstream>
#include <sys/stat.h>

namespace OHOS::Ace {

std::mutex ImageCache::cacheFilePathMutex_;
std::string ImageCache::cacheFilePath_;

std::atomic<size_t> ImageCache::cacheFileLimit_ = 100 * 1024 * 1024; // the capacity is 100MB

std::atomic<float> ImageCache::clearCacheFileRatio_ = 0.5f; // default clear ratio is 0.5

bool ImageCache::hasSetCacheFileInfo_ = false;

std::mutex ImageCache::cacheFileSizeMutex_;
int32_t ImageCache::cacheFileSize_ = 0;

std::mutex ImageCache::cacheFileInfoMutex_;
std::list<FileInfo> ImageCache::cacheFileInfo_;

void ImageCache::CacheImage(const std::string& key, const std::shared_ptr<CachedImage>& image)
{
    if (key.empty()) {
        return;
    }
    std::scoped_lock lock(imageCacheMutex_, cacheListMutex_);
    auto iter = imageCache_.find(key);
    if (iter == imageCache_.end()) {
        if (imageCache_.size() == capacity_) {
            imageCache_.erase(cacheList_.back().imageKey);
            cacheList_.pop_back();
        }
        cacheList_.emplace_front(key, image);
        imageCache_.emplace(key, cacheList_.begin());
    } else {
        iter->second->imagePtr = image;
        cacheList_.splice(cacheList_.begin(), cacheList_, iter->second);
        iter->second = cacheList_.begin();
    }
}

std::shared_ptr<CachedImage> ImageCache::GetCacheImage(const std::string& key)
{
    std::scoped_lock lock(imageCacheMutex_, cacheListMutex_);
    auto iter = imageCache_.find(key);
    if (iter != imageCache_.end()) {
        cacheList_.splice(cacheList_.begin(), cacheList_, iter->second);
        iter->second = cacheList_.begin();
        return iter->second->imagePtr;
    } else {
        return nullptr;
    }
}

void ImageCache::WriteCacheFile(const std::string& url, std::vector<uint8_t>& byteData)
{
    std::vector<std::string> removeVector;
    std::string cacheNetworkFilePath = GetNetworkImageCacheFilePath(url);
    {
        std::scoped_lock lock(cacheFileSizeMutex_, cacheFileInfoMutex_);
        cacheFileSize_ += byteData.size();
        cacheFileInfo_.emplace_back(cacheNetworkFilePath, byteData.size(), time(nullptr));
        // check if cache files too big.
        if (cacheFileSize_ > static_cast<int32_t>(cacheFileLimit_)) {
            int32_t removeCount = cacheFileInfo_.size() * clearCacheFileRatio_;
            int32_t removeSize = 0;
            auto iter = cacheFileInfo_.begin();
            int32_t count = 0;
            while (count < removeCount) {
                removeSize += iter->fileSize;
                removeVector.push_back(iter->filePath);
                iter++;
                count++;
            }
            cacheFileInfo_.erase(cacheFileInfo_.begin(), iter);
            cacheFileSize_ -= removeSize;
        }
    }
    ClearCacheFile(removeVector);

#ifdef WINDOWS_PLATFORM
    std::ofstream outFile(cacheNetworkFilePath, std::ios::binary);
#else
    std::ofstream outFile(cacheNetworkFilePath, std::fstream::out);
#endif
    outFile.write(reinterpret_cast<const char*>(byteData.data()), byteData.size());
}

void ImageCache::ClearCacheFile(const std::vector<std::string>& removeFiles)
{
    LOGD("begin to clear %{public}zu files: ", removeFiles.size());
    for (auto iter : removeFiles) {
        if (remove(iter.c_str()) != 0) {
            LOGW("remove file %{private}s failed.", iter.c_str());
            continue;
        }
    }
}

void ImageCache::SetCacheFileInfo()
{
    std::scoped_lock lock(cacheFileSizeMutex_, cacheFileInfoMutex_);
    // Set cache file information only once.
    if (hasSetCacheFileInfo_) {
        return;
    }
    std::string cacheFilePath = GetImageCacheFilePath();
    std::unique_ptr<DIR, decltype(&closedir)> dir(opendir(cacheFilePath.c_str()), closedir);
    if (dir == nullptr) {
        LOGW("cache file path wrong! maybe it is not set.");
        return;
    }
    int32_t cacheFileSize = 0;
    dirent* filePtr = readdir(dir.get());
    while (filePtr != nullptr) {
        // skip . or ..
        if (filePtr->d_name[0] != '.') {
            std::string filePath = cacheFilePath + "/" + std::string(filePtr->d_name);
            struct stat fileStatus;
            if (stat(filePath.c_str(), &fileStatus) == -1) {
                filePtr = readdir(dir.get());
                continue;
            }
            cacheFileInfo_.emplace_back(filePath, fileStatus.st_size, fileStatus.st_atime);
            cacheFileSize += static_cast<int32_t>(fileStatus.st_size);
        }
        filePtr = readdir(dir.get());
    }
    cacheFileInfo_.sort();
    cacheFileSize_ = cacheFileSize;
    hasSetCacheFileInfo_ = true;
}

} // namespace OHOS::Ace
