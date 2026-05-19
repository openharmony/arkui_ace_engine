/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "ressched_event_listener.h"
#include "res_sched_client.h"
#include "res_value.h"
#include "base/utils/string_utils.h"
#include "base/ressched/taihang_optimizer.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
constexpr char KEY_WINDOW_ID[] = "windowId";
constexpr int32_t DEFAULT_WINDOW_ID = -1;
constexpr int32_t DEFAULT_CONTAINER_ID = -1;
} // namespace

sptr<ResschedEventListener> ResschedEventListener::GetInstance()
{
    static sptr<ResschedEventListener> instance = sptr<ResschedEventListener>::MakeSptr();
    return instance;
}

void ResschedEventListener::OnReceiveEvent(uint32_t eventType, uint32_t eventValue,
    std::unordered_map<std::string, std::string> extInfo)
{
    LOGD("ResschedEventListener::OnReceiveEvent eventType: %{public}d", eventType);
    if (eventType == ResourceSchedule::ResType::EventType::EVENT_COMPONENT_PREMAKE) {
        OnComponentPreMake(extInfo);
    }
}

void ResschedEventListener::OnComponentPreMake(std::unordered_map<std::string, std::string> extInfo)
{
    auto it = extInfo.find(KEY_WINDOW_ID);
    CHECK_EQUAL_VOID(it, extInfo.end());
    int32_t windowId = StringUtils::StringToInt(it->second, DEFAULT_WINDOW_ID);
    CHECK_EQUAL_VOID(windowId, DEFAULT_WINDOW_ID);

    auto instanceId = GetContainerId(windowId);
    CHECK_EQUAL_VOID(instanceId, DEFAULT_CONTAINER_ID);

    auto context = NG::PipelineContext::GetContextByContainerId(instanceId);
    CHECK_NULL_VOID(context);

    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [instanceId, extInfo]() {
            auto pipeline = NG::PipelineContext::GetContextByContainerId(instanceId);
            CHECK_NULL_VOID(pipeline);
            CHECK_NULL_VOID(pipeline->GetTaihangOptimizer());
            pipeline->GetTaihangOptimizer()->ComponentPreMake(extInfo);
        }, TaskExecutor::TaskType::UI, "ArkUINotifyComponentPreMake");
}

void ResschedEventListener::RegisterToRSS(int32_t windowId, int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto beforeSize = containerMap_.size();
    containerMap_.emplace(windowId, instanceId);

    if (beforeSize == 0 && containerMap_.size() != 0) {
        ResourceSchedule::ResSchedClient::GetInstance().RegisterEventListener(
            ResschedEventListener::GetInstance(),
            ResourceSchedule::ResType::EventType::EVENT_COMPONENT_PREMAKE);
    }
}

void ResschedEventListener::UnRegisterFromRSS(int32_t windowId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto beforeSize = containerMap_.size();
    containerMap_.erase(windowId);

    if (beforeSize != 0 && containerMap_.size() == 0) {
        ResourceSchedule::ResSchedClient::GetInstance().UnRegisterEventListener(
            ResschedEventListener::GetInstance(),
            ResourceSchedule::ResType::EventType::EVENT_COMPONENT_PREMAKE);
    }
}

int32_t ResschedEventListener::GetContainerId(int32_t windowId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = containerMap_.find(windowId);
    CHECK_EQUAL_RETURN(iter, containerMap_.end(), DEFAULT_CONTAINER_ID);
    return iter->second;
}
} // namespace OHOS::Ace