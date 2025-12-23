/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_agent_event_reporter.h"

#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/pattern/web/web_pattern.h"

namespace OHOS::Ace::NG {

WebAgentEventReporter::WebAgentEventReporter(const WeakPtr<Pattern>& pattern)
{
    pattern_ = pattern;
}

void WebAgentEventReporter::AddEvent(const std::string& jsonString)
{
    auto jsonValue = JsonUtil::ParseJsonString(jsonString);
    if (!jsonValue || !jsonValue->IsObject()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddEvent parse json failed");
        return;
    }
    auto eventType = jsonValue->GetString(EVENT_IDENTIFIER);
    TAG_LOGD(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddEvent |%{public}s|", eventType.c_str());
    auto type = ParseEventType(eventType);
    switch (type) {
        case WebEventType::Tap:
            AddTapEvent(jsonValue);
            break;
        case WebEventType::LongPress:
            AddLongPressEvent(jsonValue);
            break;
        case WebEventType::ScrollStart:
        case WebEventType::ScrollEnd:
            AddScrollEvent(jsonValue);
            break;
        case WebEventType::PinchEnd:
            AddPinchEvent(jsonValue);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddEvent unknown event type: |%{public}s|",
                eventType.c_str());
            break;
    }
}

void WebAgentEventReporter::AddTapEvent(const std::unique_ptr<JsonValue>& tapEventJson)
{
    auto jsonValue = InspectorJsonUtil::Create();
    jsonValue->Put(REPORT_EVENT_IDENTIFIER, "Tap");
    jsonValue->Put("id", tapEventJson->GetInt("id"));
    RectF pointRect;
    auto pointJson = tapEventJson->GetValue("point");
    if (pointJson && pointJson->IsArray() && pointJson->GetArraySize() == 2) {
        pointRect.SetLeft(pointJson->GetArrayItem(0)->GetDouble());
        pointRect.SetTop(pointJson->GetArrayItem(1)->GetDouble());
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddTapEvent invalid point json");
        return;
    }
    pointRect = ConvertToWindow(pointRect);
    auto pointArray = InspectorJsonUtil::CreateArray();
    pointArray->Put(pointRect.Left());
    pointArray->Put(pointRect.Top());
    jsonValue->Put("point", pointArray);
    jsonValue->Put("count", tapEventJson->GetInt("count"));
    ReportEventImediately(jsonValue);
}

void WebAgentEventReporter::AddLongPressEvent(const std::unique_ptr<JsonValue>& longPressEventJson)
{
    auto jsonValue = InspectorJsonUtil::Create();
    jsonValue->Put(REPORT_EVENT_IDENTIFIER, "LongPress");
    jsonValue->Put("id", longPressEventJson->GetInt("id"));
    RectF pointRect;
    auto pointJson = longPressEventJson->GetValue("point");
    if (pointJson && pointJson->IsArray() && pointJson->GetArraySize() == 2) {
        pointRect.SetLeft(pointJson->GetArrayItem(0)->GetDouble());
        pointRect.SetTop(pointJson->GetArrayItem(1)->GetDouble());
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddLongPressEvent invalid point json");
        return;
    }
    pointRect = ConvertToWindow(pointRect);
    auto pointArray = InspectorJsonUtil::CreateArray();
    pointArray->Put(pointRect.Left());
    pointArray->Put(pointRect.Top());
    jsonValue->Put("point", pointArray);

    int64_t duration = LONG_PRESS_TIMEOUT_MS;
    if (auto pattern = DynamicCast<WebPattern>(pattern_.Upgrade())) {
        duration = GetCurrentTimestamp() - pattern->lastTouchDownTime_;
        duration = std::min(duration, static_cast<int64_t>(std::numeric_limits<int32_t>::max()));
    }
    jsonValue->Put("actualDuration", static_cast<int32_t>(duration));

    ReportEventImediately(jsonValue);
}

void WebAgentEventReporter::AddPinchEvent(const std::unique_ptr<JsonValue>& pinchEventJson)
{
    auto jsonValue = InspectorJsonUtil::Create();
    jsonValue->Put(REPORT_EVENT_IDENTIFIER, pinchEventJson->GetString(EVENT_IDENTIFIER).c_str());
    jsonValue->Put("id", pinchEventJson->GetInt("id"));
    double scale = pinchEventJson->GetDouble("scale");
    jsonValue->Put("scale", scale);
    ReportEventImediately(jsonValue);
}

WebAgentEventReporter::WebEventType WebAgentEventReporter::ParseEventType(const std::string& str)
{
    if (str == "Tap")
        return WebEventType::Tap;
    if (str == "LongPress")
        return WebEventType::LongPress;
    if (str == "ScrollStart")
        return WebEventType::ScrollStart;
    if (str == "ScrollEnd")
        return WebEventType::ScrollEnd;
    if (str == "PinchEnd")
        return WebEventType::PinchEnd;
    return WebEventType::Unknown;
}

RectF WebAgentEventReporter::ConvertToWindow(const RectF& rect, bool addComponentOffset)
{
    auto pattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, rect);
    auto host = pattern->GetHost();
    CHECK_NULL_RETURN(host, rect);
    double dsf = pattern->density_;
    double comX = addComponentOffset ? host->GetTransformRelativeOffset().GetX() : 0.0;
    double comY = addComponentOffset ? host->GetTransformRelativeOffset().GetY() : 0.0;
    return RectF(rect.Left() * dsf + comX, rect.Top() * dsf + comY, rect.Width() * dsf, rect.Height() * dsf);
}

// ===== scroll event process begin =====
void WebAgentEventReporter::AddScrollEvent(const std::unique_ptr<JsonValue>& scrollEventJson)
{
    ScrollEventInfo info;
    info.eventType = scrollEventJson->GetString(EVENT_IDENTIFIER);
    info.id = scrollEventJson->GetInt("id");
    double scrollLeft = 0.0;
    double scrollTop = 0.0;
    auto offsetJson = scrollEventJson->GetValue("offset");
    if (offsetJson && offsetJson->IsArray() && offsetJson->GetArraySize() == 2) {
        scrollLeft = offsetJson->GetArrayItem(0)->GetDouble();
        scrollTop = offsetJson->GetArrayItem(1)->GetDouble();
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::AddScrollEvent invalid offset json");
        return;
    }
    info.scrollRect = ConvertToWindow(RectF(scrollLeft, scrollTop, 0.0, 0.0), false);
    // no lock here, called in UI thread
    scrollQueue_.push(info);
    ProcessScrollQueue();
}

std::shared_ptr<InspectorJsonValue> WebAgentEventReporter::ScrollEventInfo::GetInspectorJsonValue() const
{
    auto jsonValue = InspectorJsonUtil::Create();
    jsonValue->Put(REPORT_EVENT_IDENTIFIER, eventType.c_str());
    jsonValue->Put("id", id);

    auto offsetArray = InspectorJsonUtil::CreateArray();
    offsetArray->Put(scrollRect.Left());
    offsetArray->Put(scrollRect.Top());

    jsonValue->Put("offset", offsetArray);
    return jsonValue;
}

bool WebAgentEventReporter::UpdateScrollEventInfoFromTree(ScrollEventInfo& info)
{
    auto pattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_RETURN(pattern, false);
    auto [id, rect] = pattern->GetScrollAreaInfoFromDocument(info.id);
    if (id > 0) {
        info.id = id;
        info.scrollRect = rect; // related to window
        return true;
    }
    TAG_LOGE(AceLogTag::ACE_WEB, "UpdateScrollEventInfoFromTree failed");
    return false;
}

void WebAgentEventReporter::ContinueScrollProcessing()
{
    processingScroll_ = false;
    ProcessScrollQueue();
}

// Handle an updated end scroll event. Returns true if processing should return early
// (either scheduled a retry or dropped the end event because no matching start record).
WebAgentEventReporter::ScrollEndEventAction WebAgentEventReporter::HandleUpdatedScrollEndEvent(ScrollEventInfo& info)
{
    auto it = startRecords_.find(info.id);
    if (it != startRecords_.end()) {
        bool same = NearEqual(it->second.scrollRect.Left(), info.scrollRect.Left()) &&
                    NearEqual(it->second.scrollRect.Top(), info.scrollRect.Top());
        if (same && info.retry < MAX_SCROLL_EVENT_UPDATE_RETRY) {
            ++info.retry;
            TAG_LOGI(AceLogTag::ACE_WEB,
                "WebAgentEventReporter::HandleUpdatedScrollEndEvent scroll offset not changed, retry: %{public}d",
                info.retry);
            AIPostTask(
                [weak = AceType::WeakClaim(this)]() {
                    auto reporter = weak.Upgrade();
                    CHECK_NULL_VOID(reporter);
                    reporter->ContinueScrollProcessing();
                },
                TaskExecutor::TaskType::UI, "ContinueScrollProcessing", DELAYED_SCROLL_EVENT_PROCESS_MS);
            return ScrollEndEventAction::RETRY; // scheduled retry, caller should return
        }
        return ScrollEndEventAction::PROCEED; // proceed to report
    } else {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::HandleUpdatedScrollEndEvent no match start record found");
        // drop this end event and let caller pop/continue
        return ScrollEndEventAction::DROP;
    }
}

// Report the scroll event and advance the queue
void WebAgentEventReporter::ReportAndAdvanceScrollQueue(const ScrollEventInfo& info, bool isScrollStart)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebAgentEventReporter::ReportAndAdvanceScrollQueue, isScrollStart: %{public}d",
        isScrollStart);
    if (isScrollStart) {
        startRecords_[info.id] = info;
    } else {
        startRecords_.erase(info.id);
    }
    auto jsonValue = info.GetInspectorJsonValue();
    scrollQueue_.pop();
    ReportEventImediately(jsonValue);
}

void WebAgentEventReporter::ProcessScrollQueue()
{
    if (processingScroll_) {
        TAG_LOGI(AceLogTag::ACE_WEB, "WebAgentEventReporter::ProcessScrollQueue already processing");
        return;
    }
    if (scrollQueue_.empty()) {
        TAG_LOGE(AceLogTag::ACE_WEB, "WebAgentEventReporter::ProcessScrollQueue empty");
        return;
    }

    processingScroll_ = true;
    // Process items iteratively to avoid recursion.
    while (!scrollQueue_.empty()) {
        ScrollEventInfo& info = scrollQueue_.front(); // copy so we can pop safely
        bool isScrollStart = (info.eventType == "ScrollStart");
        bool updated = UpdateScrollEventInfoFromTree(info);
        if (updated) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebAgentEventReporter::ProcessScrollQueue updated from tree");
            if (!isScrollStart) {
                auto action = HandleUpdatedScrollEndEvent(info);
                if (action == ScrollEndEventAction::RETRY) {
                    // retry scheduled; keep processingScroll_ true to match previous behavior
                    return;
                } else if (action == ScrollEndEventAction::DROP) {
                    // drop this event and continue with next
                    scrollQueue_.pop();
                    continue;
                }
                // else PROCEED -> fall through to report
            }
        }

        // report event immediately and continue loop
        ReportAndAdvanceScrollQueue(info, isScrollStart);
    }

    // processed all queued items
    processingScroll_ = false;
}
// ===== scroll event process end =====

void WebAgentEventReporter::ReportEventImediately(const std::shared_ptr<InspectorJsonValue>& eventJson)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebAgentEventReporter::ReportEventImediately");
    auto pattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    UiSessionManager::GetInstance()->ReportComponentChangeEvent(host->GetId(), "event", eventJson);
}

void WebAgentEventReporter::AIPostTask(
    const std::function<void()>& task, TaskExecutor::TaskType taskType, const std::string& name, uint32_t delay)
{
    TAG_LOGD(AceLogTag::ACE_WEB, "WebAgentEventReporter::AIPostTask start");
    auto pipeline = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    bool result = taskExecutor->PostDelayedTask(task, taskType, delay, name);
    TAG_LOGD(AceLogTag::ACE_WEB, "WebAgentEventReporter::AIPostTask end, result: %{public}d", result);
}

} // namespace OHOS::Ace::NG
