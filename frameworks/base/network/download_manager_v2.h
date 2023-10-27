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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_V2_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_V2_H

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <string>
#include <vector>

#include "base/image/image_source.h"
#include "base/thread/task_executor.h"

namespace OHOS::Ace {

struct DownloadCallback {
    std::function<void(const std::vector<uint8_t>&)> successCallback;
    std::function<void(std::string)> failCallback;
    std::function<void(std::string)> cancelCallback;
};
struct DownloadCondition {
    std::condition_variable cv;
    std::vector<uint8_t> dataOut;
    std::mutex downloadMutex;
    std::string errorMsg;
    bool downloadSuccess = false;
};

class DownloadManagerV2 {
public:
    DownloadManagerV2() = default;
    ~DownloadManagerV2() = default;
    static bool DownloadAsync(DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId);
    static bool DownloadSync(DownloadCallback&& downloadCallback, const std::string& url);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_NETWORK_DOWNLOAD_MANAGER_V2_H
