/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_H

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>

namespace OHOS::Ace {
struct DownloadCallback {
    std::function<void(const std::string&&, bool, int32_t)> successCallback;
    std::function<void(std::string, bool, int32_t)> failCallback;
    std::function<void(std::string, bool, int32_t)> cancelCallback;
    std::function<void(uint32_t, uint32_t, bool, int32_t)> onProgressCallback;
};

struct DownloadCondition {
    std::condition_variable cv;
    std::string dataOut;
    std::mutex downloadMutex;
    std::string errorMsg;
    std::optional<bool> downloadSuccess;
};

struct DownloadResult {
    std::string dataOut;
    std::string errorMsg;
    std::optional<bool> downloadSuccess;
};

class DownloadManager {
public:
    static DownloadManager* GetInstance();

    virtual ~DownloadManager() = default;

    virtual bool Download(const std::string& url, std::vector<uint8_t>& dataOut);
    virtual bool Download(const std::string& url, const std::shared_ptr<DownloadResult>& result);
    virtual bool DownloadAsync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId);
    virtual bool DownloadSync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId);
    virtual bool RemoveDownloadTask(const std::string& url, int32_t nodeId, bool isCancel = true);
    virtual bool RemoveDownloadTaskWithPreload(const std::string& url, int32_t nodeId, bool isCancel = true);

    // use preload module to download the url
    virtual bool DownloadAsyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId);
    virtual bool DownloadSyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId);
    virtual bool IsContains(const std::string& url);

private:
    static std::unique_ptr<DownloadManager> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_H
