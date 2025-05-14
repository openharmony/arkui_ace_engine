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

#include "hilog/log.h"
#include "http_client.h"
#include "net_conn_client.h"
#include "request_preload.h"

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

#define PRINT_LOG(level, fmt, ...)                                                                               \
    HILOG_IMPL(LOG_CORE, LOG_##level, 0xD00393A, "DownloadManager", "[%{public}d]" fmt, __LINE__, ##__VA_ARGS__) \

#define LOGE(fmt, ...) PRINT_LOG(ERROR, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) PRINT_LOG(WARN, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) PRINT_LOG(INFO, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) PRINT_LOG(DEBUG, fmt, ##__VA_ARGS__)
} // namespace

// For sync download tasks, this period may cause image not able to be loaded.
// System detects appFreeze after 3s, which has higher priority
using NetStackRequest = NetStack::HttpClient::HttpClientRequest;
using NetStackResponse = NetStack::HttpClient::HttpClientResponse;
using NetStackError = NetStack::HttpClient::HttpClientError;
using NetStackTask = NetStack::HttpClient::HttpClientTask;
using NetStackTaskStatus = NetStack::HttpClient::TaskStatus;

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

    bool Download(const std::string& url, const std::shared_ptr<DownloadResult>& downloadResult) override
    {
        NetStackRequest httpReq;
        httpReq.SetHeader("Accept", "image/webp,*/*");
        httpReq.SetURL(url);
        auto& session = NetStack::HttpClient::HttpSession::GetInstance();
        auto task = session.CreateTask(httpReq);
        if (!task) {
            return false;
        }
        std::shared_ptr<DownloadCondition> downloadCondition = std::make_shared<DownloadCondition>();
        task->OnSuccess(
            [downloadCondition, downloadResult](const NetStackRequest& request, const NetStackResponse& response) {
                {
                    std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                    downloadResult->downloadSuccess = true;
                    downloadResult->dataOut = std::move(response.GetResult());
                }
                downloadCondition->cv.notify_all();
            });
        task->OnCancel(
            [downloadCondition, downloadResult](const NetStackRequest& request, const NetStackResponse& response) {
                {
                    std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                    downloadResult->errorMsg.append("Http task of url ");
                    downloadResult->errorMsg.append(request.GetURL());
                    downloadResult->errorMsg.append(" cancelled by netStack");
                    downloadResult->downloadSuccess = false;
                }
                downloadCondition->cv.notify_all();
            });
        task->OnFail([downloadCondition, downloadResult](
                         const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadResult->errorMsg.append("Http task of url ");
                downloadResult->errorMsg.append(request.GetURL());
                downloadResult->errorMsg.append(" failed, response code ");
                auto responseCode = response.GetResponseCode();
                downloadResult->errorMsg.append(std::to_string(responseCode));
                downloadResult->errorMsg.append(", msg from netStack: ");
                downloadResult->errorMsg.append(error.GetErrorMessage());
                downloadResult->downloadSuccess = false;
            }
            downloadCondition->cv.notify_all();
        });
        auto result = task->Start();
        return HandleDownloadResult(result, downloadCondition, downloadResult);
    }

    bool DownloadAsync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        NetStackRequest httpReq;
        httpReq.SetHeader("Accept", "image/webp,*/*");
        httpReq.SetURL(url);
        auto& session = NetStack::HttpClient::HttpSession::GetInstance();
        auto task = session.CreateTask(httpReq);
        if (!task) {
            return false;
        }
        task->OnSuccess(
            [this, successCallback = downloadCallback.successCallback, failCallback = downloadCallback.failCallback,
                instanceId, url, nodeId](const NetStackRequest& request, const NetStackResponse& response) {
                if (response.GetResponseCode() != NetStack::HttpClient::ResponseCode::OK) {
                    std::string errorMsg = "Http task of url " + request.GetURL() + " failed, response code " +
                                           std::to_string(response.GetResponseCode());
                    failCallback(errorMsg, { ImageErrorCode::GET_IMAGE_ASYNC_HTTP_FAILED, errorMsg }, true, instanceId);
                    RemoveDownloadTask(url, nodeId, false);
                    return;
                }
                LOGI("Async http task of url [%{private}s] success, the responseCode = %d", request.GetURL().c_str(),
                    response.GetResponseCode());
                successCallback(std::move(response.GetResult()), true, instanceId);
                RemoveDownloadTask(url, nodeId, false);
            });
        task->OnCancel([this, cancelCallback = downloadCallback.cancelCallback, instanceId, url, nodeId](
                           const NetStackRequest& request, const NetStackResponse& response) {
            LOGI("Async Http task of url [%{private}s] cancelled by netStack", request.GetURL().c_str());
            std::string errorMsg = "Http task of url " + request.GetURL() + " cancelled by netStack";
            cancelCallback(errorMsg, { ImageErrorCode::GET_IMAGE_ASYNC_HTTP_CANCELLED, errorMsg }, true, instanceId);
            RemoveDownloadTask(url, nodeId, false);
        });
        task->OnFail([this, failCallback = downloadCallback.failCallback, instanceId, url, nodeId](
                         const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
            LOGI("Async http task of url [%{private}s] failed, response code %{public}d, msg from netStack: "
                 "[%{public}s]",
                request.GetURL().c_str(), response.GetResponseCode(), error.GetErrorMessage().c_str());
            std::string errorMsg = "Http task of url " + request.GetURL() + " failed, response code " +
                                   std::to_string(response.GetResponseCode()) +
                                   ", msg from netStack: " + error.GetErrorMessage();
            failCallback(errorMsg, { ImageErrorCode::GET_IMAGE_ASYNC_HTTP_FAILED, errorMsg }, true, instanceId);
            RemoveDownloadTask(url, nodeId, false);
        });
        if (downloadCallback.onProgressCallback) {
            task->OnProgress([onProgressCallback = downloadCallback.onProgressCallback, instanceId](
                                 const NetStackRequest& request, u_long dlTotal, u_long dlNow, u_long ulTotal,
                                 u_long ulNow) { onProgressCallback(dlTotal, dlNow, true, instanceId); });
        }
        AddDownloadTask(url, task, nodeId);
        auto result = task->Start();
        LOGI("download src [%{private}s] [%{public}s]", url.c_str(),
            result ? " successfully" : " failed to download, please check netStack log");
        return result;
    }

    bool DownloadSync(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId, int32_t nodeId) override
    {
        LOGI("DownloadSync task of [%{private}s] start", url.c_str());
        NetStackRequest httpReq;
        httpReq.SetHeader("Accept", "image/webp,*/*");
        httpReq.SetURL(url);
        auto& session = NetStack::HttpClient::HttpSession::GetInstance();
        auto task = session.CreateTask(httpReq);
        std::shared_ptr<DownloadCondition> downloadCondition = std::make_shared<DownloadCondition>();
        if (!task) {
            return false;
        }
        task->OnSuccess(
            [this, downloadCondition, url, nodeId](const NetStackRequest& request, const NetStackResponse& response) {
                LOGI("Sync http task of url [%{private}s] success, the responseCode = %d", request.GetURL().c_str(),
                    response.GetResponseCode());
                {
                    std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                    downloadCondition->downloadSuccess = true;
                    downloadCondition->dataOut = std::move(response.GetResult());
                }
                downloadCondition->cv.notify_all();
                RemoveDownloadTask(url, nodeId, false);
            });
        task->OnCancel(
            [this, downloadCondition, url, nodeId](const NetStackRequest& request, const NetStackResponse& response) {
                LOGI("Sync Http task of url [%{private}s] cancelled", request.GetURL().c_str());
                {
                    std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                    downloadCondition->errorMsg.append("Http task of url ");
                    downloadCondition->errorMsg.append(request.GetURL());
                    downloadCondition->errorMsg.append(" cancelled by netStack");
                    downloadCondition->downloadSuccess = false;
                }
                downloadCondition->cv.notify_all();
                RemoveDownloadTask(url, nodeId, false);
            });
        task->OnFail(
            [downloadCondition, url](const NetStackRequest& request, const NetStackResponse& response,
                const NetStackError& error) { OnFail(downloadCondition, request, response, error); });
        if (downloadCallback.onProgressCallback) {
            task->OnProgress([onProgressCallback = downloadCallback.onProgressCallback, instanceId](
                                const NetStackRequest& request, u_long dlTotal, u_long dlNow, u_long ulTotal,
                                u_long ulNow) { onProgressCallback(dlTotal, dlNow, false, instanceId); });
        }
        AddDownloadTask(url, task, nodeId);
        auto result = task->Start();
        return HandleDownloadResult(result, std::move(downloadCallback), downloadCondition, instanceId, url);
    }

    bool DownloadAsyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId) override
    {
        auto innerCallback = std::make_unique<Request::PreloadCallback>();
        innerCallback->OnSuccess = [this, successCallback = downloadCallback.successCallback,
                                       failCallback = downloadCallback.failCallback, instanceId,
                                       url](const std::shared_ptr<Request::Data>&& data, const std::string& taskId) {
            LOGI("Async http task of url [%{private}s-%{public}s] success", url.c_str(), taskId.c_str());
            successCallback(std::move(std::string(data->bytes().data(), data->bytes().data() + data->bytes().length())),
                true, instanceId);
            RemoveDownloadTaskWithPreload(url, false);
        };
        innerCallback->OnCancel = [this, cancelCallback = downloadCallback.cancelCallback, instanceId, url]() {
            LOGI("Async Http task of url [%{private}s] cancelled", url.c_str());
            std::string errorMsg = "Http task of url " + url + " canceled";
            cancelCallback(errorMsg,
                { ImageErrorCode::GET_IMAGE_ASYNC_HTTP_CANCELLED, "async http task of uri cancelled." }, true,
                instanceId);
            RemoveDownloadTaskWithPreload(url, false);
        };
        innerCallback->OnFail = [this, failCallback = downloadCallback.failCallback, instanceId, url](
                                    const Request::PreloadError& error, const std::string& taskId) {
            LOGI("ASync http task of url [%{private}s-%{public}s] failed, reason [%{private}s]", url.c_str(),
                taskId.c_str(), error.GetMessage().c_str());
            std::string errorMsg = "Http task of url " + url + " failed, response code " +
                                   std::to_string(error.GetCode()) + ", msg from netStack: " + error.GetMessage();
            failCallback(errorMsg, { ImageErrorCode::GET_IMAGE_ASYNC_HTTP_FAILED, "async http task of uri failed." },
                true, instanceId);
            RemoveDownloadTaskWithPreload(url, false);
        };

        if (downloadCallback.onProgressCallback) {
            innerCallback->OnProgress = [onProgressCallback = downloadCallback.onProgressCallback, instanceId](
                                            uint64_t dlNow, uint64_t dlTotal) {
                onProgressCallback(dlTotal, dlNow, true, instanceId);
            };
        }
        auto handle = Request::Preload::GetInstance()->load(url, std::move(innerCallback));
        bool isSuccess = (handle != nullptr);
        if (isSuccess) {
            AddDownloadTaskForPreload(url, handle);
        }
        LOGI("Async http download src [%{private}s] [%{public}s]", url.c_str(),
            isSuccess ? " successfully" : " failed to download, please check netStack log");
        return isSuccess;
    }

    bool fetchCachedResult(const std::string& url, std::string& result) override
    {
        auto data = Request::Preload::GetInstance()->fetch(url);
        if (data.has_value()) {
            result = std::string(data->bytes().data(), data->bytes().data() + data->bytes().length());
            return true;
        }
        return false;
    }

    bool DownloadSyncWithPreload(
        DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId) override
    {
        auto innerCallback = std::make_unique<Request::PreloadCallback>();
        auto downloadCondition = std::make_shared<DownloadCondition>();
        innerCallback->OnSuccess = [this, downloadCondition, url](
                                       const std::shared_ptr<Request::Data>&& data, const std::string& taskId) {
            LOGI("Sync http task of url [%{private}s-%{public}s] success", url.c_str(), taskId.c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadCondition->downloadSuccess = true;
                downloadCondition->dataOut =
                    std::string(data->bytes().data(), data->bytes().data() + data->bytes().length());
            }
            downloadCondition->cv.notify_all();
            RemoveDownloadTaskWithPreload(url, false);
        };
        innerCallback->OnCancel = [this, downloadCondition, url]() {
            LOGI("Sync Http task of url [%{private}s] cancelled", url.c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                downloadCondition->errorMsg.append("Http task of url ");
                downloadCondition->errorMsg.append(url.c_str());
                downloadCondition->errorMsg.append(" cancelled by netStack");
                downloadCondition->errorInfo = { ImageErrorCode::GET_IMAGE_SYNC_HTTP_CANCELLED,
                    "sync http task of uri cancelled." };
                downloadCondition->downloadSuccess = false;
            }
            downloadCondition->cv.notify_all();
            RemoveDownloadTaskWithPreload(url, false);
        };
        innerCallback->OnFail = [this, downloadCondition, url](
                                    const Request::PreloadError& error, const std::string& taskId) {
            LOGI("Sync http task of url [%{private}s-%{public}s] failed, reason [%{private}s]", url.c_str(),
                taskId.c_str(), error.GetMessage().c_str());
            {
                std::unique_lock<std::mutex> taskLock(downloadCondition->downloadMutex);
                std::string errorMsg = "Http task of url " + url + " failed, response code " +
                                       std::to_string(error.GetCode()) + ", msg from netStack: " + error.GetMessage();
                downloadCondition->errorMsg = errorMsg;
                downloadCondition->errorInfo = { ImageErrorCode::GET_IMAGE_SYNC_HTTP_FAILED,
                    "sync http task of uri failed." };
                downloadCondition->downloadSuccess = false;
            }
            downloadCondition->cv.notify_all();
            RemoveDownloadTaskWithPreload(url, false);
        };

        if (downloadCallback.onProgressCallback) {
            innerCallback->OnProgress = [onProgressCallback = downloadCallback.onProgressCallback, instanceId](
                                            uint64_t dlNow, uint64_t dlTotal) {
                onProgressCallback(dlTotal, dlNow, true, instanceId);
            };
        }
        auto handle = Request::Preload::GetInstance()->load(url, std::move(innerCallback));
        bool isSuccess = (handle != nullptr);
        if (isSuccess) {
            AddDownloadTaskForPreload(url, handle);
        }
        return HandleDownloadResult(isSuccess, std::move(downloadCallback), downloadCondition, instanceId, url);
    }

    static void OnFail(std::shared_ptr<DownloadCondition> downloadCondition, const NetStackRequest& request,
        const NetStackResponse& response, const NetStackError& error)
    {
        LOGI("Sync Http task of url [%{private}s] failed, response code %{public}d, msg from netStack: [%{public}s]",
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
    }

    bool RemoveDownloadTask(const std::string& url, int32_t nodeId, bool isCancel = true) override
    {
        std::scoped_lock lock(httpTaskMutex_);
        auto urlKey = url + std::to_string(nodeId);
        auto iter = httpTaskMap_.find(urlKey);
        if (iter != httpTaskMap_.end()) {
            auto task = iter->second;
            if (task->GetStatus() == NetStackTaskStatus::RUNNING && isCancel) {
                LOGI("AceImage RemoveDownloadTask, url:%{private}s", url.c_str());
                task->Cancel();
            }
            httpTaskMap_.erase(iter);
            return true;
        }
        return false;
    }

    bool RemoveDownloadTaskWithPreload(const std::string& url, bool isCancel = true) override
    {
        std::scoped_lock lock(httpHandleMutexForPreload_);
        auto iter = httpHandleMapForPreload_.find(url);
        if (iter != httpHandleMapForPreload_.end()) {
            auto task = iter->second;
            if (task->GetState() == Request::PreloadState::RUNNING && isCancel) {
                LOGI("AceImage RemoveDownloadHandle, url:%{private}s", url.c_str());
                task->Cancel();
            }
            httpHandleMapForPreload_.erase(iter);
            return true;
        }
        return false;
    }

private:
    struct ProxyInfo {
        std::string host;
        int32_t port = 0;
        std::string exclusions;
    };
    std::mutex httpTaskMutex_;
    std::unordered_map<std::string, std::shared_ptr<NetStackTask>> httpTaskMap_;
    // use preload module to download the url
    std::mutex httpHandleMutexForPreload_;
    std::unordered_map<std::string, std::shared_ptr<Request::PreloadHandle>> httpHandleMapForPreload_;

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
            downloadCallback.failCallback(downloadCondition->errorMsg, downloadCondition->errorInfo, false, instanceId);
        }
        return true;
    }

    bool HandleDownloadResult(bool result, const std::shared_ptr<DownloadCondition>& downloadCondition,
        const std::shared_ptr<DownloadResult>& downloadResult)
    {
        if (!result) {
            return result;
        }
        {
            std::unique_lock<std::mutex> downloadLock(downloadCondition->downloadMutex);
            // condition_variable is waiting for any of the success, cancel or failed to respond in sync mode
            downloadCondition->cv.wait_for(
                downloadLock, std::chrono::milliseconds(MAXIMUM_WAITING_PERIOD), [downloadCondition, downloadResult] {
                    return downloadCondition ? downloadResult->downloadSuccess.has_value() : false;
                });
        }
        return true;
    }

    bool IsContains(const std::string& url) override
    {
        return Request::Preload::GetInstance()->Contains(url);
    }

    void AddDownloadTask(const std::string& url, const std::shared_ptr<NetStackTask>& task, int32_t nodeId)
    {
        std::scoped_lock lock(httpTaskMutex_);
        httpTaskMap_.emplace(url + std::to_string(nodeId), task);
    }

    // use preload module to download the url
    void AddDownloadTaskForPreload(
        const std::string& url, const std::shared_ptr<Request::PreloadHandle>& handle)
    {
        std::scoped_lock lock(httpHandleMutexForPreload_);
        httpHandleMapForPreload_.emplace(url, handle);
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
