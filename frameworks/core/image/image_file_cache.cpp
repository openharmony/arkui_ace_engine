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
#include "core/image/image_file_cache.h"

#include <dirent.h>
#include <fstream>
#include <sys/stat.h>

#include "core/image/image_loader.h"
#include "core/image/image_source_info.h"
namespace OHOS::Ace {
ImageFileCache::ImageFileCache() = default;
ImageFileCache::~ImageFileCache() = default;

void ImageFileCache::SetImageCacheFilePath(const std::string& cacheFilePath)
{
    std::unique_lock<std::shared_mutex> lock(cacheFilePathMutex_);
    if (cacheFilePath_.empty()) {
        cacheFilePath_ = cacheFilePath;
    }
}

std::string ImageFileCache::GetImageCacheFilePath()
{
    std::shared_lock<std::shared_mutex> lock(cacheFilePathMutex_);
    return cacheFilePath_;
}

std::string ImageFileCache::GetImageCacheFilePath(const std::string& url)
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

void ImageFileCache::SetCacheFileLimit(size_t cacheFileLimit)
{
    LOGI("Set file cache limit size : %{public}d", static_cast<int32_t>(cacheFileLimit));
    fileLimit_ = cacheFileLimit;
}

void ImageFileCache::SetClearCacheFileRatio(float clearRatio)
{
    // clearRatio must in (0, 1].
    if (clearRatio < 0) {
        clearRatio = 0.1f;
    } else if (clearRatio > 1) {
        clearRatio = 1.0f;
    }
    clearCacheFileRatio_ = clearRatio;
}

RefPtr<NG::ImageData> ImageFileCache::GetDataFromCacheFile(const std::string& filePath)
{
    std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
    if (!GetFromCacheFileInner(filePath)) {
        LOGD("file not cached, return nullptr");
        return nullptr;
    }
    auto cacheFileLoader = AceType::MakeRefPtr<FileImageLoader>();
#ifndef USE_ROSEN_DRAWING
    auto data = cacheFileLoader->LoadImageData(ImageSourceInfo(std::string("file:/").append(filePath)));
    return NG::ImageData::MakeFromDataWrapper(&data);
#else
    auto rsData = cacheFileLoader->LoadImageData(ImageSourceInfo(std::string("file:/").append(filePath)));
    return rsData ? AceType::MakeRefPtr<NG::DrawingImageData>(rsData) : nullptr;
#endif
}

void ImageFileCache::WriteCacheFile(
    const std::string& url, const void* const data, size_t size, const std::string& suffix)
{
    if (size > fileLimit_) {
        LOGW("file size is %{public}d, greater than limit %{public}d, cannot cache", static_cast<int32_t>(size),
            static_cast<int32_t>(fileLimit_));
        return;
    }
    std::vector<std::string> removeVector;
    std::string cacheNetworkFilePath = GetImageCacheFilePath(url) + suffix;

    std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
    // 1. first check if file has been cached.
    if (GetFromCacheFileInner(cacheNetworkFilePath)) {
        LOGI("file has been wrote %{private}s", cacheNetworkFilePath.c_str());
        return;
    }

    // 2. if not in dist, write file into disk.
#ifdef WINDOWS_PLATFORM
    std::ofstream outFile(cacheNetworkFilePath, std::ios::binary);
#else
    std::ofstream outFile(cacheNetworkFilePath, std::fstream::out);
#endif
    if (!outFile.is_open()) {
        LOGW("open cache file failed, cannot write.");
        return;
    }
    outFile.write(reinterpret_cast<const char*>(data), size);
    LOGI("write image cache: %{public}s %{private}s", url.c_str(), cacheNetworkFilePath.c_str());

    cacheFileSize_ += size;
    cacheFileInfo_.emplace_back(cacheNetworkFilePath, size, time(nullptr));
    // check if cache files too big.
    if (cacheFileSize_ > static_cast<int32_t>(fileLimit_)) {
        auto removeCount = static_cast<int32_t>(cacheFileInfo_.size() * clearCacheFileRatio_);
        int32_t removeSize = 0;
        auto iter = cacheFileInfo_.begin();
        int32_t count = 0;
        while (count < removeCount) {
            removeSize += static_cast<int32_t>(iter->fileSize);
            removeVector.push_back(iter->filePath);
            ++iter;
            ++count;
        }
        cacheFileInfo_.erase(cacheFileInfo_.begin(), iter);
        cacheFileSize_ -= static_cast<int32_t>(removeSize);
    }
    // 3. clear files removed from cache list.
    ClearCacheFile(removeVector);
}

void ImageFileCache::ClearCacheFile(const std::vector<std::string>& removeFiles)
{
    LOGD("begin to clear %{public}zu files: ", removeFiles.size());
    for (auto&& iter : removeFiles) {
        if (remove(iter.c_str()) != 0) {
            LOGW("remove file %{private}s failed.", iter.c_str());
            continue;
        }
    }
}

bool ImageFileCache::GetFromCacheFile(const std::string& filePath)
{
    std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
    return GetFromCacheFileInner(filePath);
}

bool ImageFileCache::GetFromCacheFileInner(const std::string& filePath)
{
    auto iter = std::find_if(cacheFileInfo_.begin(), cacheFileInfo_.end(),
        [&filePath](const FileInfo& fileInfo) { return fileInfo.filePath == filePath; });
    if (iter == cacheFileInfo_.end()) {
        return false;
    }
    iter->accessTime = time(nullptr);
    cacheFileInfo_.splice(cacheFileInfo_.end(), cacheFileInfo_, iter);
    return true;
}

void ImageFileCache::SetCacheFileInfo()
{
    std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
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
    int64_t cacheFileSize = 0;
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
            cacheFileSize += static_cast<int64_t>(fileStatus.st_size);
        }
        filePtr = readdir(dir.get());
    }
    cacheFileInfo_.sort();
    cacheFileSize_ = cacheFileSize;
    hasSetCacheFileInfo_ = true;
}
} // namespace OHOS::Ace
