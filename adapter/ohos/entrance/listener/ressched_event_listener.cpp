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
#include "core/components_ng/pattern/stage/page_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace {
namespace {
constexpr char KEY_WINDOW_ID[] = "windowId";
constexpr char KEY_PAGE_NAME[] = "pageName";
constexpr char KEY_PATH[] = "path";
constexpr char KEY_INDEX[] = "index";
constexpr char KEY_COMPONENT_TYPE[] = "componentType";
constexpr int32_t DEFAULT_WINDOW_ID = -1;
constexpr int32_t DEFAULT_CONTAINER_ID = -1;
constexpr int32_t MAX_PATH_LENGTH = 1024;

bool CheckPath(std::unordered_map<std::string, std::string>& extInfo)
{
    auto iter = extInfo.find(KEY_PATH);
    CHECK_EQUAL_RETURN(iter, extInfo.end(), false);
    auto pathStr = iter->second;
    return !pathStr.empty() && pathStr.size() <= MAX_PATH_LENGTH;
}

bool CheckWindowId(std::unordered_map<std::string, std::string>& extInfo, int32_t& windowId)
{
    auto iter = extInfo.find(KEY_WINDOW_ID);
    CHECK_EQUAL_RETURN(iter, extInfo.end(), false);
    auto windowIdStr = iter->second;
    CHECK_EQUAL_RETURN(StringUtils::IsNumber(windowIdStr), false, false);
    windowId = StringUtils::StringToInt(windowIdStr, DEFAULT_WINDOW_ID);
    CHECK_EQUAL_RETURN(windowId, DEFAULT_WINDOW_ID, false);
    return true;
}

bool CheckNumber(std::unordered_map<std::string, std::string>& extInfo, const char* parameterKey)
{
    auto iter = extInfo.find(parameterKey);
    CHECK_EQUAL_RETURN(iter, extInfo.end(), false);
    return StringUtils::IsNumber(iter->second);
}

bool CheckPageName(std::unordered_map<std::string, std::string>& extInfo, std::string& pageName)
{
    auto iter = extInfo.find(KEY_PAGE_NAME);
    CHECK_EQUAL_RETURN(iter, extInfo.end(), false);
    pageName = iter->second;
    return !pageName.empty();
}

bool CheckParameterValid(std::unordered_map<std::string, std::string>& extInfo,
    int32_t& windowId, std::string& pageName)
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
    if (!CheckPageName(extInfo, pageName)) {
        LOGE("CheckParameterValid parameter pageName is invalid");
        return false;
    }
    if (!CheckWindowId(extInfo, windowId)) {
        LOGE("CheckParameterValid parameter windowId is invalid");
        return false;
    }
    return true;
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
    std::string pageName;
    int32_t windowId = -1;
    if (!CheckParameterValid(extInfo, windowId, pageName)) {
        return;
    }

    int32_t instanceId = GetContainerId(windowId);
    if (instanceId == DEFAULT_CONTAINER_ID) {
        LOGE("OnComponentPreMake windowId not registered, windowId:%{public}d", windowId);
        return;
    }
    auto context = NG::PipelineContext::GetContextByContainerId(instanceId);
    if (context == nullptr) {
        LOGE("OnComponentPreMake windowId is incorrect, context is nullptr");
        return;
    }
    auto pageInfo = context->GetLastPageInfo();
    CHECK_NULL_VOID(pageInfo);
    auto url = pageInfo->GetPageUrl();
    auto currentPageName = context->GetNavDestinationPageName(pageInfo);
    // In extInfo, pagename is set to url or navDestination pagename.
    if (pageName != url && pageName != currentPageName) {
        LOGE("OnComponentPreMake page name does not match, pageName:%{public}s, url:%{public}s,"
            "currentPageName:%{public}s", pageName.c_str(), url.c_str(), currentPageName.c_str());
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