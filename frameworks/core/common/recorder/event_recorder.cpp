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

#include <cstdint>
#include <optional>
#include <vector>

#include "core/common/container.h"
#include "core/common/recorder/event_controller.h"
#include "core/common/recorder/event_definition.h"
#include "core/common/recorder/node_data_cache.h"
#include "ui/base/utils/utils.h"

namespace OHOS::Ace::Recorder {
namespace {
constexpr char IGNORE_WINDOW_NAME[] = "$HA_FLOAT_WINDOW$";

void FillExtraTextIfNeed(EventType eventType, EventParamsBuilder& builder, const RefPtr<NG::FrameNode>& host)
{
    if (eventType != EventType::CLICK || !builder.GetValue(KEY_TEXT).empty()) {
        return;
    }
    if (!EventRecorder::Get().IsRecordEnable(Recorder::EventCategory::CATEGORY_PARENT_TEXT)) {
        return;
    }
    if (!host->GetChildren().empty()) {
        return;
    }
    auto parent = host->GetParentFrameNode();
    CHECK_NULL_VOID(parent);
    auto property = parent->GetAccessibilityProperty<NG::AccessibilityProperty>();
    CHECK_NULL_VOID(property);
    builder.SetExtra(KEY_EXTRA_TEXT, property->GetGroupText(true));
}
} // namespace

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

EventParamsBuilder& EventParamsBuilder::SetEventCategory(EventCategory category)
{
    category_ = category;
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

EventParamsBuilder& EventParamsBuilder::SetHost(const RefPtr<NG::FrameNode>& node)
{
    if (!node) {
        return *this;
    }
    if (EventRecorder::Get().IsRecordEnable(EventCategory::CATEGORY_RECT)) {
        auto rect = node->GetTransformRectRelativeToWindow().ToBounds();
        params_->emplace(Recorder::KEY_NODE_RECT, std::move(rect));
    }
    params_->emplace(KEY_ACE_ID, std::to_string(node->GetId()));
    params_->emplace("accessilityId", std::to_string(node->GetAccessibilityId()));
    SetPageUrl(GetPageUrlByNode(node));
    FillExtraTextIfNeed(eventType_, *this, node);
    auto parent = node->GetParent();
    if (parent) {
        auto index = parent->GetFrameNodeIndex(node);
        params_->emplace("nodeIndex", std::to_string(index));
    }
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
    auto current = Container::Current();
    if (current) {
        params_->emplace(KEY_MOUDLE_NAME, current->GetModuleName());
    }
    params_->emplace(KEY_ABILITY_NAME, AceApplicationInfo::GetInstance().GetAbilityName());
    return params_;
}

EventType EventParamsBuilder::GetEventType() const
{
    return eventType_;
}

EventCategory EventParamsBuilder::GetEventCategory() const
{
    return category_;
}

std::string EventParamsBuilder::GetValue(const std::string& key) const
{
    auto iter = params_->find(key);
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

EventRecorder::EventRecorder()
{
    eventSwitch_.resize(static_cast<int32_t>(EventCategory::CATEGORY_END), false);
    eventSwitch_[static_cast<int32_t>(EventCategory::CATEGORY_PAGE)] = true;
    globalSwitch_.resize(static_cast<int32_t>(EventCategory::CATEGORY_END), true);
}

void EventRecorder::UpdateEventSwitch(const std::vector<bool>& eventSwitch)
{
    std::unique_lock<std::shared_mutex> lock(switchLock_);
    eventSwitch_ = eventSwitch;
}

void EventRecorder::UpdateGlobalEventSwitch(const std::vector<bool>& eventSwitch)
{
    std::unique_lock<std::shared_mutex> lock(switchLock_);
    globalSwitch_ = eventSwitch;
}

void EventRecorder::UpdateWebIdentifier(const std::unordered_map<std::string, std::string>& identifierMap)
{
    std::unique_lock<std::shared_mutex> lock(switchLock_);
    webIdentifierMap_ = identifierMap;
}

bool EventRecorder::IsPageRecordEnable() const
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_PAGE);
    return globalSwitch_[index] && eventSwitch_[index];
}

bool EventRecorder::IsPageParamRecordEnable() const
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_PAGE_PARAM);
    return globalSwitch_[index] && eventSwitch_[index];
}

bool EventRecorder::IsExposureRecordEnable() const
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_EXPOSURE);
    return globalSwitch_[index] && eventSwitch_[index];
}

bool EventRecorder::IsComponentRecordEnable() const
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    int32_t index = static_cast<int32_t>(EventCategory::CATEGORY_COMPONENT);
    return globalSwitch_[index] && eventSwitch_[index];
}

bool EventRecorder::IsRecordEnable(EventCategory category) const
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    int32_t index = static_cast<int32_t>(category);
    return globalSwitch_[index] && eventSwitch_[index];
}

void EventRecorder::SetContainerInfo(const std::string& windowName, int32_t id, bool foreground)
{
    if (windowName == IGNORE_WINDOW_NAME) {
        return;
    }
    if (foreground) {
        containerId_ = id;
    }
}

void EventRecorder::SetFocusContainerInfo(const std::string& windowName, int32_t id)
{
    if (windowName == IGNORE_WINDOW_NAME) {
        return;
    }
    focusContainerId_ = id;
}

int32_t EventRecorder::GetContainerId(bool isFoucs)
{
    if (isFoucs) {
        return focusContainerId_;
    } else {
        return containerId_;
    }
}

const std::string& EventRecorder::GetPageUrl()
{
    auto pageUrl = GetPageUrlByContainerId(focusContainerId_);
    if (!pageUrl.empty()) {
        pageUrl_ = pageUrl;
    }
    return pageUrl_;
}

const std::string& EventRecorder::GetNavDstName() const
{
    return navDstName_;
}

void EventRecorder::FillWebJsCode(std::optional<WebJsItem>& scriptItems) const
{
    if (!IsRecordEnable(EventCategory::CATEGORY_WEB)) {
        return;
    }
    auto codeList = EventController::Get().GetWebJsCodeList();
    if (codeList.empty()) {
        return;
    }
    std::vector<std::string> scriptRules = { "*" };
    if (scriptItems.has_value()) {
        for (const auto& code : codeList) {
            scriptItems->emplace(std::make_pair(code, scriptRules));
        }
    } else {
        WebJsItem webJsItems;
        for (const auto& code : codeList) {
            webJsItems.emplace(std::make_pair(code, scriptRules));
        }
        scriptItems = std::make_optional<WebJsItem>(webJsItems);
    }
}

bool EventRecorder::IsMessageValid(const std::string& webCategory, const std::string& identifier)
{
    std::shared_lock<std::shared_mutex> lock(switchLock_);
    auto iter = webIdentifierMap_.find(webCategory);
    if (iter == webIdentifierMap_.end()) {
        return false;
    }
    return iter->second == identifier;
}

void EventRecorder::NotifyEventCacheEnd() {}

void EventRecorder::OnPageShow(const std::string& pageUrl, const std::string& param, const std::string& name)
{
    pageUrl_ = pageUrl;
    NodeDataCache::Get().OnPageShow(pageUrl);
    Recorder::EventParamsBuilder builder;
    builder.SetType(std::to_string(PageEventType::ROUTER_PAGE))
        .SetPageUrl(pageUrl)
        .SetExtra(KEY_NAME, name)
        .SetExtra(Recorder::KEY_PAGE_PARAM, param);
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_SHOW), std::move(builder.build()));
}

void EventRecorder::OnPageHide(const std::string& pageUrl, const int64_t duration, const std::string& name)
{
    Recorder::EventParamsBuilder builder;
    builder.SetType(std::to_string(PageEventType::ROUTER_PAGE))
        .SetPageUrl(pageUrl)
        .SetExtra(KEY_NAME, name)
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
    if (builder.GetValue(KEY_PAGE).empty()) {
        builder.SetPageUrl(GetPageUrl());
    }
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
    if (builder.GetValue(KEY_PAGE).empty()) {
        builder.SetPageUrl(GetPageUrl());
    }
    builder.SetNavDst(navDstName_);
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_COMPONENT, static_cast<int32_t>(EventType::CHANGE), std::move(params));
}

void EventRecorder::OnEvent(EventParamsBuilder&& builder)
{
    if (builder.GetValue(KEY_PAGE).empty()) {
        builder.SetPageUrl(GetPageUrl());
    }
    builder.SetNavDst(navDstName_);
    auto eventType = builder.GetEventType();
    auto params = builder.build();
    EventController::Get().NotifyEvent(builder.GetEventCategory(), static_cast<int32_t>(eventType), std::move(params));
}

void EventRecorder::OnNavDstShow(EventParamsBuilder&& builder)
{
    navDstName_ = builder.GetValue(KEY_NAV_DST);
    navShowTime_ = GetCurrentTimestamp();
    builder.SetPageUrl(GetPageUrl());
    builder.SetType(std::to_string(PageEventType::NAV_PAGE));
    auto params = builder.build();
    EventController::Get().NotifyEvent(
        EventCategory::CATEGORY_PAGE, static_cast<int32_t>(EventType::PAGE_SHOW), std::move(params));
}

void EventRecorder::OnNavDstHide(EventParamsBuilder&& builder)
{
    if (builder.GetValue(KEY_NAV_DST) == navDstName_) {
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

void EventRecorder::OnWebEvent(const RefPtr<NG::FrameNode>& node, const std::vector<std::string>& params)
{
    CHECK_NULL_VOID(node);
    if (params.empty()) {
        return;
    }
    if (params.size() == WEB_PARAM_SIZE) {
        if (!IsRecordEnable(EventCategory::CATEGORY_WEB)) {
            return;
        }
        if (!IsMessageValid(params[WEB_PARAM_INDEX_CATEGORY], params[WEB_PARAM_INDEX_IDENTIFIER])) {
            return;
        }
        EventParamsBuilder builder;
        builder.SetId(node->GetInspectorIdValue(""))
            .SetType(node->GetHostTag())
            .SetEventType(EventType::WEB_ACTION)
            .SetEventCategory(EventCategory::CATEGORY_WEB)
            .SetExtra(KEY_WEB_CATEGORY, params[WEB_PARAM_INDEX_CATEGORY])
            .SetText(params[WEB_PARAM_INDEX_CONTENT])
            .SetHost(node)
            .SetDescription(node->GetAutoEventParamValue(""));
        OnEvent(std::move(builder));
    }
}

void EventRecorder::OnAttachWeb(const RefPtr<NG::FrameNode>& node)
{
    CHECK_NULL_VOID(node);
    weakNodeCache_[node->GetId()] = Referenced::WeakClaim(Referenced::RawPtr(node));
}

void EventRecorder::OnDetachWeb(int32_t nodeId)
{
    weakNodeCache_.erase(nodeId);
}
} // namespace OHOS::Ace::Recorder
