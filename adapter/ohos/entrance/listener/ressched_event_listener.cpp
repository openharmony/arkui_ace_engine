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
constexpr char KEY_PAGE_NAME[] = "pageName";
constexpr char KEY_PATH[] = "path";
constexpr char KEY_INDEX[] = "index";
constexpr char KEY_COMPONENT_TYPE[] = "componentType";
constexpr int32_t DEFAULT_WINDOW_ID = 0;
constexpr int32_t DEFAULT_CONTAINER_ID = -1;
constexpr int32_t MAX_PATH_LENGTH = 1024;

bool CheckPath(std::unordered_map<std::string, std::string>& extInfo)
{
    CHECK_EQUAL_RETURN(extInfo.find(KEY_PATH), extInfo.end(), false);
    auto pathStr = extInfo.find(KEY_PATH)->second;
    return !pathStr.empty() && pathStr.size() < MAX_PATH_LENGTH;
}

bool CheckWindowId(std::unordered_map<std::string, std::string>& extInfo)
{
    CHECK_EQUAL_RETURN(extInfo.find(KEY_WINDOW_ID), extInfo.end(), false);
    auto windowIdStr = extInfo.find(KEY_WINDOW_ID)->second;
    CHECK_EQUAL_RETURN(StringUtils::IsNumber(windowIdStr), false, false);
    int32_t windowId = StringUtils::StringToInt(windowIdStr, DEFAULT_WINDOW_ID);
    CHECK_EQUAL_RETURN(windowId, DEFAULT_WINDOW_ID, false);
    return true;
}

bool CheckNumber(std::unordered_map<std::string, std::string>& extInfo, const char* parameterKey)
{
    CHECK_EQUAL_RETURN(extInfo.find(parameterKey), extInfo.end(), false);
    return StringUtils::IsNumber(extInfo.find(parameterKey)->second);
}

bool CheckParameterValid(std::unordered_map<std::string, std::string>& extInfo)
{
    if (!CheckNumber(extInfo, KEY_COMPONENT_TYPE)) {
        LOGE("CheckParameterValid parameter component type is invalid");
        return false;
    }
    if (!CheckNumber(extInfo, KEY_INDEX)) {
        LOGE("CheckParameterValid parameter index is invalid");
        return false;
    }
    if (!CheckPath(extInfo)) {
        LOGE("CheckParameterValid parameter path is invalid");
        return false;
    }
    if (extInfo.find(KEY_PAGE_NAME) == extInfo.end()) {
        LOGE("CheckParameterValid parameter pageName is invalid");
        return false;
    }
    if (!CheckWindowId(extInfo)) {
        LOGE("CheckParameterValid parameter windowId is invalid");
        return false;
    }
    return true;
}

bool CheckPageName(std::string& pageName, std::string& curPageName)
{
    std::vector<std::string> splits;
    StringUtils::StringSplitter(curPageName, ',', splits);
    for (auto split : splits) {
        if (pageName == split) {
            return true;
        }
    }
    return false;
}
} // namespace

sptr<ResschedEventListener> ResschedEventListener::GetInstance()
{
    static sptr<ResschedEventListener> instance = sptr<ResschedEventListener>::MakeSptr();
    return instance;
}

void ResschedEventListener::OnReceiveEvent(uint32_t eventType, uint32_t eventValue,
    std::unordered_map<std::string, std::string> extInfo)
{
    LOGD("OnReceiveEvent eventType: %{public}d", eventType);
    if (eventType == ResourceSchedule::ResType::EventType::EVENT_COMPONENT_PREMAKE) {
        OnComponentPreMake(extInfo);
    }
}

void ResschedEventListener::OnComponentPreMake(std::unordered_map<std::string, std::string>& extInfo)
{
    if (!CheckParameterValid(extInfo)) {
        return;
    }
    int32_t windowId = StringUtils::StringToInt(extInfo.find(KEY_WINDOW_ID)->second);
    int32_t instanceId = GetContainerId(windowId);
    if (instanceId == DEFAULT_CONTAINER_ID) {
        LOGE("OnComponentPreMake windowId not registered");
        return;
    }
    auto context = NG::PipelineContext::GetContextByContainerId(instanceId);
    if (context == nullptr) {
        LOGE("OnComponentPreMake windowId is incorrect, context is nullptr");
        return;
    }

    auto pageName = extInfo.find(KEY_PAGE_NAME)->second;
    auto curPageName = context->GetCurrentPageName();
    if (!CheckPageName(pageName, curPageName)) {
        LOGE("OnComponentPreMake page name does not match");
        return;
    }

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