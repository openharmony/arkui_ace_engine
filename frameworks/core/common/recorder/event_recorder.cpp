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

#include "core/common/container.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/node_data_cache.h"

namespace OHOS::Ace::Recorder {
constexpr char IGNORE_WINDOW_NAME[] = "$HA_FLOAT_WINDOW$";

bool IsCacheAvaliable()
{
    return EventRecorder::Get().IsComponentRecordEnable() && !NodeDataCache::Get().IsShareNodeEmpty();
}

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
    if (!id.empty()) {
        params_->emplace(KEY_ID, id);
    }
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetType(const std::string& type)
{
    params_->emplace(KEY_TYPE, type);
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetDescription(const std::string& desc)
{
    if (!desc.empty()) {
        params_->emplace(KEY_DESCRIPTION, desc);
    }
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetNavDst(const std::string& dstName)
{
    if (!dstName.empty()) {
        params_->emplace(KEY_NAV_DST, dstName);
    }
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetPageUrl(const std::string& pageUrl)
{
    if (!pageUrl.empty()) {
        params_->emplace(KEY_PAGE, pageUrl);
    }
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetText(const std::string& value)
{
    if (!value.empty()) {
        params_->emplace(KEY_TEXT, value);
    }
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
    if (!key.empty() && !value.empty()) {
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

void EventRecorder::UpdateEventSwitch(const EventSwitch& eventSwitch)
{
    eventSwitch_ = eventSwitch;
}

bool EventRecorder::IsPageRecordEnable() const
{
    return pageEnable_ && eventSwitch_.pageEnable;
}

bool EventRecorder::IsPageParamRecordEnable() const
{
    return pageParamEnable_ && eventSwitch_.pageParamEnable;
}

bool EventRecorder::IsExposureRecordEnable() const
{
    return exposureEnable_ && eventSwitch_.exposureEnable;
}

bool EventRecorder::IsComponentRecordEnable() const
{
    return componentEnable_ && eventSwitch_.componentEnable;
}

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

void EventRecorder::SetFocusContainerInfo(const std::string& windowName, int32_t id)
{
    isFocusContainerChanged_ = focusContainerId_ != id;
    if (windowName == IGNORE_WINDOW_NAME) {
        return;
    }
    focusContainerId_ = id;
}

int32_t EventRecorder::GetContainerId()
{
    if (containerId_ == -1) {
        return -1;
    }
    return focusContainerId_;
}

const std::string& EventRecorder::GetPageUrl()
{
    if (pageUrl_.empty() || isFocusContainerChanged_) {
        pageUrl_ = GetCurrentPageUrl();
    }
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
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_SHOW), std::move(builder.build()));
}

void EventRecorder::OnPageHide(const std::string& pageUrl, const int64_t duration)
{
    Recorder::EventParamsBuilder builder;
    builder.SetType(std::to_string(PageEventType::ROUTER_PAGE))
        .SetText(pageUrl)
        .SetExtra(KEY_DURATION, std::to_string(duration));
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
    builder.SetPageUrl(GetPageUrl());
    builder.SetNavDst(navDstName_);
    auto params = builder.build();
    taskExecutor_->PostTask(
        [taskExecutor = taskExecutor_, params]() {
            EventController::Get().NotifyEvent(
                EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(EventType::CLICK), std::move(params));
        },
        TaskExecutor::TaskType::UI, "ArkUINotifyClickEvent");
}

void EventRecorder::OnChange(EventParamsBuilder&& builder)
{
    builder.SetPageUrl(GetPageUrl());
    builder.SetNavDst(navDstName_);
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(EventType::CHANGE), std::move(params));
}

void EventRecorder::OnEvent(EventParamsBuilder&& builder)
{
    builder.SetPageUrl(GetPageUrl());
    builder.SetNavDst(navDstName_);
    auto eventType = builder.GetEventType();
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(eventType), std::move(params));
}

void EventRecorder::OnNavDstShow(EventParamsBuilder&& builder)
{
    navDstName_ = builder.GetText();
    navShowTime_ = GetCurrentTimestamp();
    builder.SetPageUrl(GetPageUrl());
    builder.SetType(std::to_string(PageEventType::NAV_PAGE));
    auto params = builder.build();
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
    builder.SetPageUrl(GetPageUrl());
    builder.SetType(std::to_string(PageEventType::NAV_PAGE));
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_HIDE), std::move(params));
}

void EventRecorder::OnExposure(EventParamsBuilder&& builder)
{
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_EXPOSURE, static_cast<int32_t>(EventType::EXPOSURE), std::move(params));
}
} // namespace OHOS::Ace::Recorder
