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

#include "http_client.h"
#include "http_proxy.h"
#include "net_conn_client.h"

#include "base/log/ace_trace.h"
#include "base/log/log.h"
#include "base/network/download_manager_v2.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace {

constexpr int32_t MAXIMUM_WAITING_PERIOD = 10;
using NetStackRequest = NetStack::HttpClient::HttpClientRequest;
using NetStackResponse = NetStack::HttpClient::HttpClientResponse;
using NetStackError = NetStack::HttpClient::HttpClientError;

bool DownloadManagerV2::DownloadAsync(DownloadCallback&& downloadCallback, const std::string& url, int32_t instanceId)
{
    NetStackRequest httpReq;
    httpReq.SetURL(url);
    auto& session = NetStack::HttpClient::HttpSession::GetInstance();
    auto task = session.CreateTask(httpReq);
    task->OnSuccess([callback = std::move(downloadCallback.successCallback), instanceId](
                        const NetStackRequest& request, const NetStackResponse& response) {
        ContainerScope scope(instanceId);
        std::string result = response.GetResult();
        std::vector<uint8_t> dataOut;
        for (auto iter = result.begin(); iter != result.end(); iter++) {
            dataOut.emplace_back(static_cast<uint8_t>(*iter));
        }
        dataOut.shrink_to_fit();
        LOGI("Async http task of url %{private}s success, data size %{public}zu", request.GetURL().c_str(),
            dataOut.size());
        NG::ImageUtils::PostToUI([data = std::move(dataOut), successCallback = std::move(callback)]() {
            if (successCallback) {
                successCallback(data);
            }
        });
    });
    task->OnCancel([callback = std::move(downloadCallback.cancelCallback), instanceId](
                       const NetStackRequest& request, const NetStackResponse& response) {
        ContainerScope scope(instanceId);
        LOGI("Async Http task of url %{private}s cancelled by netStack", request.GetURL().c_str());
        std::string errorMsg;
        errorMsg.append("Http task of url ");
        errorMsg.append(request.GetURL());
        errorMsg.append(" cancelled by netStack");
        NG::ImageUtils::PostToUI([failCallback = std::move(callback), errorMsg]() {
            if (failCallback) {
                failCallback(errorMsg);
            }
        });
    });
    task->OnFail([callback = std::move(downloadCallback.failCallback), instanceId](
                     const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
        ContainerScope scope(instanceId);
        LOGI("Async http task of url %{private}s failed, response code %{public}d, msg from netStack: %{public}s",
            request.GetURL().c_str(), response.GetResponseCode(), error.GetErrorMessage().c_str());
        std::string errorMsg;
        errorMsg.append("Http task of url ");
        errorMsg.append(request.GetURL());
        errorMsg.append(" failed, response code ");
        auto responseCode = response.GetResponseCode();
        errorMsg.append(std::to_string(responseCode));
        errorMsg.append(", msg from netStack: ");
        errorMsg.append(error.GetErrorMessage());
        NG::ImageUtils::PostToUI([failCallback = std::move(callback), errorMsg]() {
            if (failCallback) {
                failCallback(errorMsg);
            }
        });
    });
    auto result = task->Start();
    LOGI("Task of netstack with src %{private}s %{public}s", url.c_str(),
        result ? " started on another thread successfully"
               : " failed to start on another thread, please check netStack log");
    return result;
}

bool DownloadManagerV2::DownloadSync(DownloadCallback&& downloadCallback, const std::string& url)
{
    LOGI("DownloadSync task of %{private}s start", url.c_str());
    ACE_SCOPED_TRACE("DownloadSync of %s", url.c_str());
    NetStackRequest httpReq;
    httpReq.SetURL(url);
    auto& session = NetStack::HttpClient::HttpSession::GetInstance();
    auto task = session.CreateTask(httpReq);
    DownloadCondition downloadCondition;
    task->OnSuccess([&downloadCondition](const NetStackRequest& request, const NetStackResponse& response) {
        LOGI("Sync Http task of url %{private}s success", request.GetURL().c_str());
        {
            std::unique_lock<std::mutex> taskLock(downloadCondition.downloadMutex);
            downloadCondition.downloadSuccess = true;
            std::string result = response.GetResult();
            for (auto iter = result.begin(); iter != result.end(); iter++) {
                downloadCondition.dataOut.emplace_back(static_cast<uint8_t>(*iter));
            }
            downloadCondition.dataOut.shrink_to_fit();
        }
        downloadCondition.cv.notify_all();
    });
    task->OnCancel([&downloadCondition](const NetStackRequest& request, const NetStackResponse& response) {
        LOGI("Sync Http task of url %{private}s cancelled", request.GetURL().c_str());
        {
            std::unique_lock<std::mutex> taskLock(downloadCondition.downloadMutex);
            downloadCondition.errorMsg.append("Http task of url ");
            downloadCondition.errorMsg.append(request.GetURL());
            downloadCondition.errorMsg.append(" cancelled by netStack");
        }
        downloadCondition.cv.notify_all();
    });
    task->OnFail([&downloadCondition](
                     const NetStackRequest& request, const NetStackResponse& response, const NetStackError& error) {
        LOGI("Sync Http task of url %{private}s failed, response code %{public}d, msg from netStack: %{public}s",
            request.GetURL().c_str(), response.GetResponseCode(), error.GetErrorMessage().c_str());
        {
            std::unique_lock<std::mutex> taskLock(downloadCondition.downloadMutex);
            downloadCondition.errorMsg.append("Http task of url ");
            downloadCondition.errorMsg.append(request.GetURL());
            downloadCondition.errorMsg.append(" failed, response code ");
            auto responseCode = response.GetResponseCode();
            downloadCondition.errorMsg.append(std::to_string(responseCode));
            downloadCondition.errorMsg.append(", msg from netStack: ");
            downloadCondition.errorMsg.append(error.GetErrorMessage());
        }
        downloadCondition.cv.notify_all();
    });
    auto result = task->Start();
    if (!result) {
        LOGI("Sync Task of netstack with url %{private}s failed to start on another thread, please check netStack log",
            url.c_str());
        return result;
    }
    std::unique_lock<std::mutex> downloadlock(downloadCondition.downloadMutex);
    // condition_variable is waiting for any of the success, cancel or failed to respond in sync mode
    downloadCondition.cv.wait_for(downloadlock, std::chrono::seconds(MAXIMUM_WAITING_PERIOD));
    downloadlock.unlock();
    if (downloadCondition.downloadSuccess) {
        downloadCallback.successCallback(downloadCondition.dataOut);
    } else {
        downloadCallback.failCallback(downloadCondition.errorMsg);
    }
    return true;
}

} // namespace OHOS::Ace
