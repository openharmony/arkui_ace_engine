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

#include "base/network/download_manager.h"

namespace OHOS::Ace {
class MockDownloadManager final : public DownloadManager {
public:
    MockDownloadManager() = default;
    ~MockDownloadManager() = default;

    bool Download(const std::string& /* url */, std::vector<uint8_t>& /* dataOut */) override
    {
        return false;
    }

    bool Download(const std::string& /* url */, const std::shared_ptr<DownloadResult>& /* result */) override
    {
        return false;
    }

    bool DownloadAsync(DownloadCallback&& /* downloadCallback */, const std::string& /* url */,
        int32_t /* instanceId */, int32_t /* nodeId */) override
    {
        return false;
    }
    bool DownloadSync(DownloadCallback&& /* downloadCallback */, const std::string& /* url */, int32_t /* instanceId */,
        int32_t /* nodeId */) override
    {
        return false;
    }
    bool RemoveDownloadTask(const std::string& /* url */, int32_t /*nodeId*/) override
    {
        return false;
    }
    bool DownloadAsyncWithPreload(DownloadCallback&& /* downloadCallback */, const std::string& /* url */,
        int32_t /* instanceId */, int32_t /* nodeId */) override
    {
        return false;
    }
    bool DownloadSyncWithPreload(DownloadCallback&& /* downloadCallback */, const std::string& /* url */,
        int32_t /* instanceId */, int32_t /* nodeId */) override
    {
        return false;
    }
};

DownloadManager* DownloadManager::GetInstance()
{
    static MockDownloadManager manager;
    return &manager;
}
} // namespace OHOS::Ace
