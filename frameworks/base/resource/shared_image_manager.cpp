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

#include "base/log/log.h"

namespace OHOS::Ace {
namespace {

constexpr uint32_t DELAY_TIME_FOR_IMAGE_DATA_CLEAN = 30000;
constexpr char MEMORY_IMAGE_HEAD[] = "memory://";

} // namespace

std::function<void()> SharedImageManager::GenerateClearImageDataCallback(const std::string& name)
{
    auto clearImageDataCallback = [wp = AceType::WeakClaim(this), picName = name]() {
        auto sharedImageManager = wp.Upgrade();
        if (!sharedImageManager) {
            LOGW("sharedImageManager upgrade fail, picName: %{private}s", picName.c_str());
            return;
        }
        {
            std::lock_guard<std::mutex> lockImageMap(sharedImageManager->sharedImageMapMutex_);
            sharedImageManager->sharedImageMap_.erase(picName);
        }
        {
            std::lock_guard<std::mutex> lockCancelableCallbackMap_(sharedImageManager->cancelableCallbackMapMutex_);
            sharedImageManager->cancelableCallbackMap_.erase(picName);
        }
    };
    return clearImageDataCallback;
}

void SharedImageManager::PostDelayedTaskToClearImageData(const std::string& name)
{
    if (!taskExecutor_) {
        LOGE("taskExecutor is null!");
        return;
    }
    std::lock_guard<std::mutex> lockCancelableCallbackMap_(cancelableCallbackMapMutex_);
    auto& cancelableCallback = cancelableCallbackMap_[name];
    cancelableCallback.Reset(GenerateClearImageDataCallback(name));
    taskExecutor_->PostDelayedTask(cancelableCallback, TaskExecutor::TaskType::IO, DELAY_TIME_FOR_IMAGE_DATA_CLEAN);
}

void SharedImageManager::AddSharedImage(const std::string& name, SharedImage&& sharedImage)
{
    {
        std::set<RefPtr<ImageProviderLoader>> providerSet = std::set<RefPtr<ImageProviderLoader>>();
        // step1: lock provider map to search for record of current picture name
        std::scoped_lock lock(providerMapMutex_, sharedImageMapMutex_);
        auto providersToNotify = providerMapToReload_.find(name);
        if (providersToNotify != providerMapToReload_.end()) {
            for (const auto& providerWp : providersToNotify->second) {
                auto provider = providerWp.Upgrade();
                if (!provider) {
                    LOGE("provider of %{private}s is null", name.c_str());
                    continue;
                }
                providerSet.emplace(provider);
            }
            providerMapToReload_.erase(providersToNotify);
        }
        // step2: lock image map to add shared image and notify [LazyMemoryImageProvider]s to update data and reload
        // update image data when the name can be found in map
        auto result = sharedImageMap_.try_emplace(name, std::move(sharedImage));
        if (!result.second) {
            result.first->second = std::move(sharedImage);
        }
        for (const auto& provider : providerSet) {
            provider->UpdateData(std::string(MEMORY_IMAGE_HEAD).append(name), result.first->second);
        }
        LOGI("done add image data for %{private}s, length of data is %{private}zu", name.c_str(),
            result.first->second.size());
    }
    PostDelayedTaskToClearImageData(name);
}

void SharedImageManager::AddPictureNamesToReloadMap(std::string&& name)
{
    // add names of memory image to be read from shared memory
    std::lock_guard<std::mutex> lock(providerMapMutex_);
    providerMapToReload_.try_emplace(name, std::set<WeakPtr<ImageProviderLoader>>());
}

bool SharedImageManager::AddProviderToReloadMap(
    const std::string& name, const WeakPtr<ImageProviderLoader>& loaderWp)
{
    std::lock_guard<std::mutex> lock(providerMapMutex_);
    auto providerMapIter = providerMapToReload_.find(name);
    if (providerMapIter != providerMapToReload_.end()) {
        providerMapIter->second.emplace(loaderWp);
        return true;
    }
    return false;
}

bool SharedImageManager::FindImageInSharedImageMap(
    const std::string& name, const WeakPtr<ImageProviderLoader>& providerWp)
{
    auto loader = providerWp.Upgrade();
    if (!loader) {
        LOGE("provider of %{private}s is null", name.c_str());
        return false;
    }
    std::lock_guard<std::mutex> lockImageMap(sharedImageMapMutex_);
    auto iter = sharedImageMap_.find(name);
    if (iter == sharedImageMap_.end()) {
        LOGE("image data of %{private}s does not found in SharedImageMap", name.c_str());
        return false;
    }
    loader->UpdateData(std::string(MEMORY_IMAGE_HEAD).append(name), iter->second);
    return true;
}

} // namespace OHOS::Ace
