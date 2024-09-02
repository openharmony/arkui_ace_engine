/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include <dlfcn.h>

#include "base/log/log_wrapper.h"
#include "base/network/download_manager.h"

namespace OHOS::Ace {
using CreateDownloadManagerFunc = DownloadManager* (*)();
std::unique_ptr<DownloadManager> DownloadManager::instance_ = nullptr;
std::mutex DownloadManager::mutex_;
constexpr char CREATE_DOWNLOAD_MANAGER_FUNC[] = "OHOS_ACE_CreateDownloadManager";
constexpr char ACE_NET_WORK_NAME[] = "libace_network.z.so";

DownloadManager* CreateDownloadManager()
{
    void* handle = dlopen(ACE_NET_WORK_NAME, RTLD_LAZY | RTLD_LOCAL);
    if (handle == nullptr) {
        TAG_LOGW(AceLogTag::ACE_DOWNLOAD_MANAGER, "load libace_network failed");
        return nullptr;
    }

    auto entry = reinterpret_cast<CreateDownloadManagerFunc>(dlsym(handle, CREATE_DOWNLOAD_MANAGER_FUNC));
    if (entry == nullptr) {
        dlclose(handle);
        return nullptr;
    }

    auto* manager = entry();
    return manager;
}

DownloadManager* DownloadManager::GetInstance()
{
    TAG_LOGI(AceLogTag::ACE_DOWNLOAD_MANAGER, "DownloadManager GetInstance");
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            auto* manager = CreateDownloadManager();
            instance_.reset(manager);
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace