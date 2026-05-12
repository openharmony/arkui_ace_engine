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
constexpr char WINDOWID[] = "windowId";
}
std::once_flag ResschedEventListener::createFlag_;
sptr<ResschedEventListener> ResschedEventListener::instance_ = nullptr;

sptr<ResschedEventListener> ResschedEventListener::GetInstance()
{
    std::call_once(createFlag_, [](){
        instance_ = sptr<ResschedEventListener>::MakeSptr();
    });
    return instance_;
}

void ResschedEventListener::OnReceiveEvent(uint32_t eventType, uint32_t eventValue,
    std::unordered_map<std::string, std::string> extInfo)
{
    if (eventType == ResourceSchedule::ResType::EventType::EVENT_COMPONENT_PREMAKE) {
        OnComponentPreMake(extInfo);
    }
}

void ResschedEventListener::OnComponentPreMake(std::unordered_map<std::string, std::string> extInfo)
{
    auto it = extInfo.find(WINDOWID);
    CHECK_EQUAL_VOID(it, extInfo.end());
    int32_t windowId = StringUtils::StringToInt(it->second, -2);
    CHECK_EQUAL_VOID(windowId, -2);
    auto iter = containerMap_.find(windowId);
    CHECK_EQUAL_VOID(iter, containerMap_.end());
    auto instanceId = iter->second;
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
        },
        TaskExecutor::TaskType::UI, "ArkUINotifyComponentPreMake");
}

void ResschedEventListener::AddContainerId(int32_t windowId, int32_t instanceId)
{
    std::lock_guard<std::mutex> lock(mutex_);
    containerMap_.emplace(windowId, instanceId);
}
}