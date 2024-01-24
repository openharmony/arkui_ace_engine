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
#include "hilog/log.h"
#include "http_client.h"
#include "http_proxy.h"
#include "net_conn_client.h"

#include "base/network/download_manager.h"

#define ACE_FORCE_EXPORT __attribute__((visibility("default")))

#define ACE_CURL_EASY_SET_OPTION(handle, opt, data)            \
    do {                                                       \
        CURLcode result = curl_easy_setopt(handle, opt, data); \
        if (result != CURLE_OK) {                              \
            return false;                                      \
        }                                                      \
    } while (0)

namespace OHOS::Ace {
namespace {
constexpr int32_t MAXIMUM_WAITING_PERIOD = 2800;
constexpr OHOS::HiviewDFX::HiLogLabel ACE_DOWNLOAD_MANAGER = { LOG_CORE, 0xC0393A, "DownloadManager" };
#define LOGI(fmt, ...) \
    (void)OHOS::HiviewDFX::HiLog::Info(ACE_DOWNLOAD_MANAGER, "[%{public}d]" fmt, __LINE__, ##__VA_ARGS__)
#define LOGE(fmt, ...) \
    (void)OHOS::HiviewDFX::HiLog::Error(ACE_DOWNLOAD_MANAGER, "[%{public}d]" fmt, __LINE__, ##__VA_ARGS__)
} // namespace

// For sync download tasks, this period may cause image not able to be loaded.
// System detects appFreeze after 3s, which has higher priority
using NetStackRequest = NetStack::HttpClient::HttpClientRequest;
using NetStackResponse = NetStack::HttpClient::HttpClientResponse;
using NetStackError = NetStack::HttpClient::HttpClientError;

class ACE_FORCE_EXPORT DownloadManagerImpl : public DownloadManager {
public:
    DownloadManagerImpl() = default;
    ~DownloadManagerImpl()
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
#if !defined(PREVIEW)
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_CAINFO, "/etc/ssl/certs/cacert.pem");
#endif
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

#if defined(IOS_PLATFORM) || defined(ANDROID_PLATFORM) || defined(PREVIEW)
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_SSL_VERIFYPEER, 0L);
        ACE_CURL_EASY_SET_OPTION(handle.get(), CURLOPT_SSL_VERIFYHOST, 0L);
#endif

        CURLcode result = curl_easy_perform(handle.get());
        if (result != CURLE_OK) {
            LOGE("Failed to download, url: [%{private}s], [%{public}s]", url.c_str(), curl_easy_strerror(result));
            if (!errorStr.empty()) {
                LOGE("Failed to download reason: [%{public}s]", errorStr.c_str());
            }
            dataOut.clear();
            return false;
        }
        dataOut.shrink_to_fit();
        return true;
    }

    bool DownloadAsync(DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId) override
    {
        NetStackRequest httpReq;
        httpReq.SetURL(url);
        auto& session = NetStack::HttpClient::HttpSession::GetInstance();
        auto task = session.CreateTask(httpReq);
        task->OnSuccess([successCallback = std::move(downloadCallback.successCallback), instanceId](
                            const NetStackRequest& request, const NetStackResponse& response) {
            LOGI("Async http task of url [%{private}s] success", request.GetURL().c_str());
            successCallback(std::move(response.GetResult()), true, instanceId);
        });
        task->OnCancel([cancelCallback = std::move(downloadCallback.cancelCallback), instanceId](
                           const NetStackRequest& request, const NetStackResponse& response) {
            LOGI("Async Http task of url [%{private}s] cancelled by netStack", request.GetURL().c_str());
            std::string errorMsg;
            errorMsg.append("Http task of url ");
            errorMsg.append(request.GetURL());
            errorMsg.append(" cancelled by netStack");
            cancelCallback(errorMsg, true, instanceId);
        });
        task->OnFail([failCallback = std::move(downloadCallback.failCallback), instanceId](
                         const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
            LOGI("Async http task of url [%{private}s] failed, response code %{public}d, msg from netStack: "
                 "[%{public}s]",
                request.GetURL().c_str(), response.GetResponseCode(), error.GetErrorMessage().c_str());
            std::string errorMsg;
            errorMsg.append("Http task of url ");
            errorMsg.append(request.GetURL());
            errorMsg.append(" failed, response code ");
            auto responseCode = response.GetResponseCode();
            errorMsg.append(std::to_string(responseCode));
            errorMsg.append(", msg from netStack: ");
            errorMsg.append(error.GetErrorMessage());
            failCallback(errorMsg, true, instanceId);
        });
        auto result = task->Start();
        LOGI("Task of netstack with src [%{private}s] [%{public}s]", url.c_str(),
            result ? " started on another thread successfully"
                   : " failed to start on another thread, please check netStack log");
        return result;
    }

    bool DownloadSync(DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId) override
    {
        LOGI("DownloadSync task of [%{private}s] start", url.c_str());
        NetStackRequest httpReq;
        httpReq.SetURL(url);
        auto& session = NetStack::HttpClient::HttpSession::GetInstance();
        auto task = session.CreateTask(httpReq);
        std::shared_ptr<DownloadCondition> downloadCondition = std::make_shared<DownloadCondition>();
        task->OnSuccess([downloadCondition](const NetStackRequest& request, const NetStackResponse& response) {
            LOGI("Sync Http task of url [%{private}s] success", request.GetURL().c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadCondition->downloadSuccess = true;
                downloadCondition->dataOut = std::move(response.GetResult());
            }
            downloadCondition->cv.notify_all();
        });
        task->OnCancel([downloadCondition](const NetStackRequest& request, const NetStackResponse& response) {
            LOGI("Sync Http task of url [%{private}s] cancelled", request.GetURL().c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadCondition->errorMsg.append("Http task of url ");
                downloadCondition->errorMsg.append(request.GetURL());
                downloadCondition->errorMsg.append(" cancelled by netStack");
                downloadCondition->downloadSuccess = false;
            }
            downloadCondition->cv.notify_all();
        });
        task->OnFail([downloadCondition](
                         const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
            LOGI(
                "Sync Http task of url [%{private}s] failed, response code %{public}d, msg from netStack: [%{public}s]",
                request.GetURL().c_str(), response.GetResponseCode(), error.GetErrorMessage().c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadCondition->errorMsg.append("Http task of url ");
                downloadCondition->errorMsg.append(request.GetURL());
                downloadCondition->errorMsg.append(" failed, response code ");
                auto responseCode = response.GetResponseCode();
                downloadCondition->errorMsg.append(std::to_string(responseCode));
                downloadCondition->errorMsg.append(", msg from netStack: ");
                downloadCondition->errorMsg.append(error.GetErrorMessage());
                downloadCondition->downloadSuccess = false;
            }
            downloadCondition->cv.notify_all();
        });
        auto result = task->Start();
        return HandleDownloadResult(result, std::move(downloadCallback), downloadCondition, instanceId, url);
    }

private:
    struct ProxyInfo {
        std::string host;
        int32_t port = 0;
        std::string exclusions;
    };

    bool HandleDownloadResult(bool result, DownloadCallback&& downloadCallback,
        const std::shared_ptr<DownloadCondition>& downloadCondition, int32_t instanceId, const std::string& url)
    {
        if (!result) {
            return result;
        }
        {
            std::unique_lock<std::mutex> downloadLock(downloadCondition->downloadMutex);
            // condition_variable is waiting for any of the success, cancel or failed to respond in sync mode
            downloadCondition->cv.wait_for(
                downloadLock, std::chrono::milliseconds(MAXIMUM_WAITING_PERIOD), [downloadCondition] {
                    return downloadCondition ? downloadCondition->downloadSuccess.has_value() : false;
                });
        }
        if (!downloadCondition->downloadSuccess.has_value()) {
            LOGI("Sync Task of netstack with url [%{private}s] maximum waiting period exceed", url.c_str());
        }
        if (downloadCondition->downloadSuccess.value_or(false)) {
            downloadCallback.successCallback(std::move(downloadCondition->dataOut), false, instanceId);
        } else {
            downloadCallback.failCallback(downloadCondition->errorMsg, false, instanceId);
        }
        return true;
    }

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
        NetManagerStandard::HttpProxy httpProxy;
        NetManagerStandard::NetConnClient::GetInstance().GetDefaultHttpProxy(httpProxy);
        proxy.host = httpProxy.GetHost();
        proxy.port = httpProxy.GetPort();

        auto exclusionList = httpProxy.GetExclusionList();
        for (auto&& ex : exclusionList) {
            proxy.exclusions.append(ex);
            if (ex != exclusionList.back()) {
                proxy.exclusions.append(",");
            }
        }
        return true;
    }

    std::mutex mutex_;
    bool initialized_ = false;
    bool isCurl_ = false;
};

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateDownloadManager()
{
    return new DownloadManagerImpl();
}
} // namespace OHOS::Ace
