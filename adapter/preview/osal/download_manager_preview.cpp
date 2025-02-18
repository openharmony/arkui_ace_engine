/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <string>
#include <vector>

#include "curl/curl.h"

#include "base/log/log.h"
#include "base/network/download_manager.h"
#include "base/utils/macros.h"

#define ACE_CURL_EASY_SET_OPTION(handle, opt, data)            \
    do {                                                       \
        CURLcode result = curl_easy_setopt(handle, opt, data); \
        if (result != CURLE_OK) {                              \
            return false;                                      \
        }                                                      \
    } while (0)

namespace OHOS::Ace {

std::unique_ptr<DownloadManager> DownloadManager::instance_ = nullptr;

class ACE_FORCE_EXPORT DownloadManagerPrview : public DownloadManager {
public:
    DownloadManagerPrview() = default;
    ~DownloadManagerPrview()
    {
        if (isCurl_) {
            curl_global_cleanup();
        }
    }

    bool Download(const std::string& url, std::vector<uint8_t>& dataOut) override
    {
        // when calling, it is necessary to set it to true and call curl clean up method
        // during download manager ohos object destruction
        isCurl_ = true;
        if (!Initialize()) {
            return false;
        }

        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> handle(curl_easy_init(), &curl_easy_cleanup);
        if (!handle) {
            return false;
        }

        dataOut.clear();
        std::string errorStr;
        errorStr.reserve(CURL_ERROR_SIZE);

        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_URL, url.c_str());
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_WRITEFUNCTION, OnWritingMemory);
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_WRITEDATA, &dataOut);
        // Some servers don't like requests that are made without a user-agent field, so we provide one
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_URL, url.c_str());
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_VERBOSE, 1L);
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_ERRORBUFFER, errorStr.data());

        ProxyInfo proxy;
        if (GetProxy(proxy)) {
            ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_PROXY, proxy.host.c_str());
            ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_PROXYPORT, proxy.port);
            if (!proxy.exclusions.empty()) {
                ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_NOPROXY, proxy.exclusions.c_str());
            }
            ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
            ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_HTTPPROXYTUNNEL, 1L);
        }

        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_SSL_VERIFYPEER, 0L);
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_SSL_VERIFYHOST, 0L);

        CURLcode result = curl_easy_perform(handle.get());
        if (result != CURLE_OK) {
            LOGE("Failed to download, url: %{private}s, %{public}s", url.c_str(), curl_easy_strerror(result));
            if (!errorStr.empty()) {
                LOGE("Failed to download reason: %{public}s", errorStr.c_str());
            }
            dataOut.clear();
            return false;
        }
        dataOut.shrink_to_fit();
        return true;
    }

    bool Download(const std::string& url, const std::shared_ptr<DownloadResult>& result) override
    {
        return false;
    }

    bool DownloadAsync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        return false;
    }

    bool DownloadSync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        return false;
    }

    bool DownloadAsyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        return false;
    }

    bool DownloadSyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        return false;
    }

    bool RemoveDownloadTask(const std::string& url, int32_t nodeId, bool isCancel = true) override
    {
        return false;
    }

    bool RemoveDownloadTaskWithPreload(const std::string& url, int32_t nodeId, bool isCancel = true) override
    {
        return false;
    }

    bool IsContains(const std::string& url) override
    {
        return false;
    }

private:
    struct ProxyInfo {
        std::string host;
        int32_t port = 0;
        std::string exclusions;
    };

    bool Initialize()
    {
        if (initialized_) {
            return true;
        }

        std::lock_guard<std::mutex> lock(mutex_);
        if (initialized_) {
            return true;
        }
        if (curl_global_init(CURL_GLOBAL_ALL) != CURLE_OK) {
            LOGE("Failed to initialize 'curl'");
            return false;
        }
        initialized_ = true;
        return true;
    }

    static size_t OnWritingMemory(void* data, size_t size, size_t memBytes, void* userData)
    {
        // size is always 1, for more details see https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
        auto& dataOut = *static_cast<std::vector<uint8_t>*>(userData);
        auto chunkData = static_cast<uint8_t*>(data);
        dataOut.insert(dataOut.end(), chunkData, chunkData + memBytes);
        return memBytes;
    }

    static bool GetProxy(ProxyInfo& proxy)
    {
        return false;
    }

    std::mutex mutex_;
    bool initialized_ = false;
    bool isCurl_ = false;
};

DownloadManager* DownloadManager::GetInstance()
{
    static std::once_flag onceFlag;
    std::call_once(onceFlag, []() {
        instance_.reset(new DownloadManagerPrview());
    });
    return instance_.get();
}
} // namespace OHOS::Ace
