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
#include "frameworks/bridge/pa_backend/backend_delegate_impl.h"

#include <atomic>
#include <string>

#include "ability.h"
#include "ability_info.h"
#include "base/log/ace_trace.h"
#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "core/common/ace_application_info.h"
#include "core/common/platform_bridge.h"
#include "core/components/dialog/dialog_component.h"
#include "core/components/toast/toast_component.h"
#include "frameworks/bridge/common/manifest/manifest_parser.h"
#include "frameworks/bridge/common/utils/utils.h"

namespace OHOS::Ace::Framework {
namespace {
const char PA_MANIFEST_JSON[] = "manifest.json";
} // namespace

BackendDelegateImpl::BackendDelegateImpl(const BackendDelegateImplBuilder &builder)
    : loadJs_(builder.loadCallback), dispatcherCallback_(builder.transferCallback),
      asyncEvent_(builder.asyncEventCallback), syncEvent_(builder.syncEventCallback),
      destroyApplication_(builder.destroyApplicationCallback),
      manifestParser_(AceType::MakeRefPtr<ManifestParser>()),
      ability_(builder.ability),
      type_(builder.type),
      taskExecutor_(builder.taskExecutor)
{}

void BackendDelegateImpl::ParseManifest()
{
    std::call_once(onceFlag_, [this]() {
        std::string jsonContent;
        if (!GetAssetContent(PA_MANIFEST_JSON, jsonContent)) {
            LOGE("RunPa parse manifest.json failed");
            EventReport::SendFormException(FormExcepType::RUN_PAGE_ERR);
            return;
        }
        manifestParser_->Parse(jsonContent);
    });
}

void BackendDelegateImpl::RunPa(const std::string &url, const std::string &params)
{
    ACE_SCOPED_TRACE("BackendDelegateImpl::RunService");
    LOGD("dDelegateImpl RunService url=%{private}s", url.c_str());
    ParseManifest();
    // if mutli pa in one hap should parse manifest get right url
    LoadPa(url, params);
}

void BackendDelegateImpl::SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) const
{
    LOGD("BackendDelegateImpl SetJsMessageDispatcher");
    taskExecutor_->PostTask([dispatcherCallback = dispatcherCallback_, dispatcher] { dispatcherCallback(dispatcher); },
        TaskExecutor::TaskType::JS);
}

void BackendDelegateImpl::PostJsTask(std::function<void()>&& task)
{
    taskExecutor_->PostTask(task, TaskExecutor::TaskType::JS);
}

bool BackendDelegateImpl::GetAssetContent(const std::string& url, std::string& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

bool BackendDelegateImpl::GetAssetContent(const std::string& url, std::vector<uint8_t>& content)
{
    return GetAssetContentImpl(assetManager_, url, content);
}

void BackendDelegateImpl::LoadPa(const std::string& url, const std::string& params)
{
    LOGD("BackendDelegateImpl LoadPa: %{private}s.", url.c_str());

    std::unique_lock<std::mutex> lock(LoadPaMutex_);
    if (isStagingPageExist_) {
        if (condition_.wait_for(lock, std::chrono::seconds(1)) == std::cv_status::timeout) {
            LOGE("BackendDelegateImpl, load page failed, waiting for current page loading finish.");
            return;
        }
    }

    isStagingPageExist_ = true;
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), url] {
            auto delegate = weak.Upgrade();
            if (!delegate) {
                return;
            }
            delegate->loadJs_(url);
        },
        TaskExecutor::TaskType::JS);
}

void BackendDelegateImpl::SetAssetManager(const RefPtr<AssetManager>& assetManager)
{
    assetManager_ = assetManager;
}

SingleTaskExecutor BackendDelegateImpl::GetAnimationJsTask()
{
    return SingleTaskExecutor::Make(taskExecutor_, TaskExecutor::TaskType::JS);
}

void BackendDelegateImpl::AddTaskObserver(std::function<void()> &&task)
{
    taskExecutor_->AddTaskObserver(std::move(task));
}

void BackendDelegateImpl::RemoveTaskObserver()
{
    taskExecutor_->RemoveTaskObserver();
}

void BackendDelegateImpl::FireAsyncEvent(
    const std::string &eventId, const std::string &param, const std::string &jsonArgs)
{
    LOGD("FireAsyncEvent eventId: %{public}s", eventId.c_str());
    std::string args = param;
    args.append(",null").append(",null"); // callback and dom changes
    if (!jsonArgs.empty()) {
        args.append(",").append(jsonArgs); // method args
    }
    taskExecutor_->PostTask(
        [weak = AceType::WeakClaim(this), eventId, args = std::move(args)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->asyncEvent_(eventId, args);
            }
        },
        TaskExecutor::TaskType::JS);
}

bool BackendDelegateImpl::FireSyncEvent(
    const std::string &eventId, const std::string &param, const std::string &jsonArgs)
{
    std::string resultStr;
    FireSyncEvent(eventId, param, jsonArgs, resultStr);
    return (resultStr == "true");
}

void BackendDelegateImpl::FireSyncEvent(
    const std::string &eventId, const std::string &param, const std::string &jsonArgs, std::string &result)
{
    int32_t callbackId = callbackCnt_++;
    std::string args = param;
    args.append("{\"_callbackId\":\"").append(std::to_string(callbackId)).append("\"}").append(",null");
    if (!jsonArgs.empty()) {
        args.append(",").append(jsonArgs); // method args
    }
    taskExecutor_->PostSyncTask(
        [weak = AceType::WeakClaim(this), eventId, args = std::move(args)] {
            auto delegate = weak.Upgrade();
            if (delegate) {
                delegate->syncEvent_(eventId, args);
            }
        },
        TaskExecutor::TaskType::JS);

    result = jsCallBackResult_[callbackId];
    LOGD("FireSyncEvent eventId: %{public}s, callbackId: %{public}d", eventId.c_str(), callbackId);
    jsCallBackResult_.erase(callbackId);
}

void BackendDelegateImpl::OnApplicationDestroy(const std::string &packageName)
{
    taskExecutor_->PostSyncTask(
        [destroyApplication = destroyApplication_, packageName] { destroyApplication(packageName); },
        TaskExecutor::TaskType::JS);
}
} // namespace OHOS::Ace::Framework
