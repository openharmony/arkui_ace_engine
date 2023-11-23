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
#include "core/common/recorder/event_recorder.h"

#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "base/utils/string_utils.h"
#include "base/utils/time_util.h"
#include "core/common/container.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/node_data_cache.h"

namespace OHOS::Ace::Recorder {
constexpr char IGNORE_WINDOW_NAME[] = "$HA_FLOAT_WINDOW$";

EventParamsBuilder::EventParamsBuilder()
{
    params_ = std::make_shared<std::unordered_map<std::string, std::string>>();
}

EventParamsBuilder& EventParamsBuilder::SetEventType(EventType eventType)
{
    eventType_ = eventType;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetId(const std::string& id)
{
    params_->emplace(KEY_ID, id);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetType(const std::string& type)
{
    params_->emplace(KEY_TYPE, type);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetNavDst(const std::string& dstName)
{
    params_->emplace(KEY_NAV_DST, dstName);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetPageUrl(const std::string& pageUrl)
{
    params_->emplace(KEY_PAGE, pageUrl);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetText(const std::string& value)
{
    params_->emplace(KEY_TEXT, value);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetChecked(bool value)
{
    std::string strVal = value ? "true" : "false";
    params_->emplace(KEY_CHECKED, strVal);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetIndex(int value)
{
    params_->emplace(KEY_INDEX, std::to_string(value));
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetTextArray(const std::vector<std::string>& value)
{
    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < value.size(); i++) {
        jsonArray->Put(std::to_string(i).c_str(), value.at(i).c_str());
    }
    params_->emplace(KEY_TEXT_ARRAY, jsonArray->ToString());
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetExtra(const std::string& key, const std::string& value)
{
    if (!key.empty()) {
        params_->emplace(key, value);
    }
    return *this;
}

std::shared_ptr<std::unordered_map<std::string, std::string>> EventParamsBuilder::build()
{
    return params_;
}

EventType EventParamsBuilder::GetEventType() const
{
    return eventType_;
}

std::string EventParamsBuilder::GetText() const
{
    auto iter = params_->find(KEY_TEXT);
    if (iter != params_->end()) {
        return iter->second;
    }
    return "";
}

std::string EventParamsBuilder::ToString() const
{
    std::stringstream ss;
    ss << "{";
    if (eventType_ != EventType::INVALID) {
        ss << "eventType:" << eventType_ << ", ";
    }
    for (auto&& it : *params_) {
        ss << it.first << ":" << it.second << ", ";
    }
    ss << "}";
    return ss.str();
}

std::string MapToString(const std::shared_ptr<std::unordered_map<std::string, std::string>>& input)
{
    if (!input) {
        return "";
    }
    std::stringstream ss;
    ss << "{";
    for (auto it = input->begin(); it != input->end(); it++) {
        ss << it->first << ":" << it->second << ", ";
    }
    ss << "}";
    return ss.str();
}

EventRecorder& EventRecorder::Get()
{
    static EventRecorder eventRecorder;
    return eventRecorder;
}

EventRecorder::EventRecorder() {}


void EventRecorder::SetContainerInfo(const std::string& windowName, int32_t id, bool foreground)
{
    if (windowName == IGNORE_WINDOW_NAME) {
        return;
    }
    if (foreground) {
        containerId_ = id;
        containerCount_++;
    } else {
        containerCount_--;
    }
    if (containerCount_ <= 0) {
        containerCount_ = 0;
        containerId_ = -1;
    }
}

int32_t EventRecorder::GetContainerId()
{
    return containerId_;
}

const std::string& EventRecorder::GetPageUrl() const
{
    return pageUrl_;
}

const std::string& EventRecorder::GetNavDstName() const
{
    return navDstName_;
}

void EventRecorder::OnPageShow(const std::string& pageUrl, const std::string& param)
{
    pageUrl_ = pageUrl;
    NodeDataCache::Get().OnPageShow(pageUrl);
    Recorder::EventParamsBuilder builder;
    builder.SetType(std::to_string(PageEventType::ROUTER_PAGE))
        .SetText(pageUrl)
        .SetExtra(Recorder::KEY_PAGE_PARAM, param);
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnPageShow record %{public}s", builder.ToString().c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_SHOW), std::move(builder.build()));
}

void EventRecorder::OnPageHide(const std::string& pageUrl, const int64_t duration)
{
    Recorder::EventParamsBuilder builder;
    builder.SetType(std::to_string(PageEventType::ROUTER_PAGE))
        .SetText(pageUrl)
        .SetExtra(KEY_DURATION, std::to_string(duration));
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnPageHide record %{public}s", builder.ToString().c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_HIDE), std::move(builder.build()));
}

void EventRecorder::OnClick(EventParamsBuilder&& builder)
{
    if (!taskExecutor_) {
        auto container = Container::Current();
        CHECK_NULL_VOID(container);
        taskExecutor_ = container->GetTaskExecutor();
    }
    CHECK_NULL_VOID(taskExecutor_);
    builder.SetPageUrl(pageUrl_);
    builder.SetNavDst(navDstName_);
    auto params = builder.build();
    taskExecutor_->PostTask(
        [taskExecutor = taskExecutor_, params]() {
            TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnClick record %{public}s", MapToString(params).c_str());
            EventController::Get().NotifyEvent(
                EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(EventType::CLICK), std::move(params));
        },
        TaskExecutor::TaskType::UI);
}

void EventRecorder::OnChange(EventParamsBuilder&& builder)
{
    builder.SetPageUrl(pageUrl_);
    builder.SetNavDst(navDstName_);
    auto params = builder.build();
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnChange record %{public}s", MapToString(params).c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(EventType::CHANGE), std::move(params));
}

void EventRecorder::OnEvent(EventParamsBuilder&& builder)
{
    builder.SetPageUrl(pageUrl_);
    builder.SetNavDst(navDstName_);
    auto eventType = builder.GetEventType();
    auto params = builder.build();
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnEvent record event %{public}d, %{public}s", static_cast<int32_t>(eventType),
        MapToString(params).c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(eventType), std::move(params));
}

void EventRecorder::OnNavDstShow(EventParamsBuilder&& builder)
{
    navDstName_ = builder.GetText();
    navShowTime_ = GetCurrentTimestamp();
    builder.SetPageUrl(pageUrl_);
    builder.SetType(std::to_string(PageEventType::NAV_PAGE));
    auto params = builder.build();
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnNavDestShow record %{public}s", MapToString(params).c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_SHOW), std::move(params));
}

void EventRecorder::OnNavDstHide(EventParamsBuilder&& builder)
{
    if (builder.GetText() == navDstName_) {
        navDstName_ = "";
        if (navShowTime_ > 0) {
            int64_t duration = GetCurrentTimestamp() - navShowTime_;
            builder.SetExtra(KEY_DURATION, std::to_string(duration));
            navShowTime_ = 0;
        }
    }
    builder.SetPageUrl(pageUrl_);
    builder.SetType(std::to_string(PageEventType::NAV_PAGE));
    auto params = builder.build();
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnNavDestHide record %{public}s", MapToString(params).c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_HIDE), std::move(params));
}

void EventRecorder::OnExposure(EventParamsBuilder&& builder)
{
    auto params = builder.build();
    TAG_LOGD(AceLogTag::ACE_UIEVENT, "OnExposure record %{public}s", MapToString(params).c_str());
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_EXPOSURE, static_cast<int32_t>(EventType::EXPOSURE), std::move(params));
}
} // namespace OHOS::Ace::Recorder
