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

#include "base/resource/shared_image_manager.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t DELAY_TIME_FOR_IMAGE_DATA_CLEAN = 30000;
constexpr char MEMORY_IMAGE_HEAD[] = "memory://";

constexpr size_t MAX_SIZE_FOR_TOTAL_IMAGE = 10000000;

} // namespace

std::function<void()> SharedImageManager::GenerateClearImageDataCallback(const std::string& name, size_t dataSize)
{
    auto clearImageDataCallback = [wp = AceType::WeakClaim(this), picName = name, dataSize]() {
        auto sharedImageManager = wp.Upgrade();
        if (!sharedImageManager) {
            return;
        }
        {
            std::lock_guard<std::mutex> lockImageMap(sharedImageManager->sharedImageMapMutex_);
            sharedImageManager->sharedImageMap_.erase(picName);
        }
        {
            std::lock_guard<std::mutex> lockCancelableCallbackMap_(sharedImageManager->cancelableCallbackMapMutex_);
            std::lock_guard<std::mutex> lockImageMap(sharedImageManager->sharedImageMapMutex_);
            LOGW("clear image cache name: %{public}s", picName.c_str());
            sharedImageManager->sharedImageTotalSize_ -= dataSize;
            sharedImageManager->cancelableCallbackMap_.erase(picName);
        }
    };
    return clearImageDataCallback;
}

void SharedImageManager::PostDelayedTaskToClearImageData(const std::string& name, size_t dataSize)
{
    auto taskExecutor = taskExecutor_.Upgrade();
    CHECK_NULL_VOID(taskExecutor);
    std::lock_guard<std::mutex> lockCancelableCallbackMap_(cancelableCallbackMapMutex_);
    auto& cancelableCallback = cancelableCallbackMap_[name];
    cancelableCallback.Reset(GenerateClearImageDataCallback(name, dataSize));
    auto bkTask = [wp = taskExecutor_, cancelableCallback]() {
        auto taskExecutor = wp.Upgrade();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            cancelableCallback, TaskExecutor::TaskType::BACKGROUND, "ArkUIImageClearSharedImageData");
    };
    taskExecutor->PostDelayedTask(
        bkTask, TaskExecutor::TaskType::UI, DELAY_TIME_FOR_IMAGE_DATA_CLEAN, "ArkUIImageClearSharedImageData");
}

void SharedImageManager::AddSharedImage(const std::string& name, SharedImage&& sharedImage)
{
        std::set<WeakPtr<ImageProviderLoader>> providerWpSet = std::set<WeakPtr<ImageProviderLoader>>();
        // step1: lock provider map to search for record of current picture name
        std::scoped_lock lock(providerMapMutex_, sharedImageMapMutex_);
        auto providersToNotify = providerMapToReload_.find(name);
        if (providersToNotify != providerMapToReload_.end()) {
            for (const auto& providerWp : providersToNotify->second) {
                auto provider = providerWp.Upgrade();
                if (!provider) {
                    continue;
                }
                providerWpSet.emplace(provider);
            }
            providerMapToReload_.erase(providersToNotify);
        }
        // step2: lock image map to add shared image and notify [LazyMemoryImageProvider]s to update data and reload
        // update image data when the name can be found in map
        bool isClear = UpdateImageMap(name, sharedImage);
        auto taskExecutor = taskExecutor_.Upgrade();
        CHECK_NULL_VOID(taskExecutor);
        taskExecutor->PostTask(
            [isClear, providerWpSet, name, wp = AceType::WeakClaim(this)]() {
                auto sharedImageManager = wp.Upgrade();
                CHECK_NULL_VOID(sharedImageManager);
                size_t dataSize = 0;
                {
                    std::lock_guard<std::mutex> lockImageMap(sharedImageManager->sharedImageMapMutex_);
                    auto sharedImageMap = sharedImageManager->GetSharedImageMap();
                    auto imageDataIter = sharedImageMap.find(name);
                    if (imageDataIter == sharedImageMap.end()) {
                        LOGW("fail to find data of %{public}s in sharedImageMap, stop UpdateData", name.c_str());
                        return;
                    }
                    dataSize = imageDataIter->second.size();
                    for (const auto& providerWp : providerWpSet) {
                        auto provider = providerWp.Upgrade();
                        if (!provider) {
                            continue;
                        }
                        provider->UpdateData(std::string(MEMORY_IMAGE_HEAD).append(name), imageDataIter->second);
                    }
                }
                if (isClear) {
                    sharedImageManager->PostDelayedTaskToClearImageData(name, dataSize);
                }
            },
            TaskExecutor::TaskType::UI, "ArkUIImageAddSharedImageData");
}

bool SharedImageManager::UpdateImageMap(const std::string& name, const SharedImage& sharedImage)
{
    bool isClear = false;
    auto iter = sharedImageMap_.find(name);
    if (iter != sharedImageMap_.end()) {
        sharedImageTotalSize_ -= iter->second.size();
        sharedImageTotalSize_ += sharedImage.size();
        iter->second = sharedImage;
    } else {
        sharedImageTotalSize_ += sharedImage.size();
        sharedImageMap_.emplace(name, sharedImage);
        if (static_cast<int>(sharedImageMap_.size()) > sharedImageCacheThreshold_) {
            LOGW("will clear %{public}s cache, sharedImageMap_ size %{public}d max cache: %{public}d",
                name.c_str(), static_cast<int>(sharedImageMap_.size()), sharedImageCacheThreshold_);
            isClear = true;
        }
    }
    if (sharedImageTotalSize_ > MAX_SIZE_FOR_TOTAL_IMAGE) {
        LOGW("will clear %{public}s cache, sharedImageTotalSize_ size %{public}d",
            name.c_str(), static_cast<int32_t>(sharedImageTotalSize_));
        isClear = true;
    }
    return isClear;
}

void SharedImageManager::AddPictureNamesToReloadMap(std::string&& name)
{
    // add names of memory image to be read from shared memory
    std::lock_guard<std::mutex> lock(providerMapMutex_);
    providerMapToReload_.try_emplace(name, std::set<WeakPtr<ImageProviderLoader>>());
}

bool SharedImageManager::FindImageInSharedImageMap(
    const std::string& name, const WeakPtr<ImageProviderLoader>& providerWp)
{
    LOGD("find image %{public}s in SharedImageMap", name.c_str());
    auto loader = providerWp.Upgrade();
    if (!loader) {
        LOGW("image %{public}s loader nullptr", name.c_str());
        return false;
    }
    std::lock_guard<std::mutex> lockImageMap(sharedImageMapMutex_);
    auto iter = sharedImageMap_.find(name);
    if (iter == sharedImageMap_.end()) {
        LOGW("image data of %{private}s does not found in SharedImageMap", name.c_str());
        return false;
    }
    loader->UpdateData(std::string(MEMORY_IMAGE_HEAD).append(name), iter->second);
    return true;
}

bool SharedImageManager::RegisterLoader(const std::string& name, const WeakPtr<ImageProviderLoader>& providerWp)
{
    std::lock_guard<std::mutex> lockProviderMap(providerMapMutex_);
    bool resourceInMap = (providerMapToReload_.find(name) != providerMapToReload_.end());
    providerMapToReload_[name].emplace(providerWp);
    return resourceInMap;
}

bool SharedImageManager::Remove(const std::string& name)
{
    std::lock_guard<std::mutex> lockImageMap(sharedImageMapMutex_);
    auto iter = sharedImageMap_.find(name);
    if (iter == sharedImageMap_.end()) {
        LOGW("Remove failed: image data of %{private}s does not found in SharedImageMap", name.c_str());
        return false;
    }
    sharedImageTotalSize_ -= iter->second.size();
    LOGW("clear image cache name: %{public}s", name.c_str());
    int res = static_cast<int>(sharedImageMap_.erase(name));
    return (res != 0);
}
} // namespace OHOS::Ace
