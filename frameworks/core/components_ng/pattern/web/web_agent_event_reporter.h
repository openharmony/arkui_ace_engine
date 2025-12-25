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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_AGENT_EVENT_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_AGENT_EVENT_REPORT_H

#include <functional>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace {
class InspectorJsonValue;
}

namespace OHOS::Ace::NG {
class Pattern;

class WebAgentEventReporter : public AceType {
    DECLARE_ACE_TYPE(WebAgentEventReporter, AceType);

public:
    explicit WebAgentEventReporter(const WeakPtr<Pattern>& pattern);

    void AddEvent(const std::string& jsonString);

    virtual void ReportEventImediately(const std::shared_ptr<InspectorJsonValue>& eventJson);

    virtual void AddTapEvent(const std::unique_ptr<JsonValue>& tapEventJson);

    virtual void AddLongPressEvent(const std::unique_ptr<JsonValue>& longPressEventJson);

    virtual void AddPinchEvent(const std::unique_ptr<JsonValue>& pinchEventJson);

    virtual void AddScrollEvent(const std::unique_ptr<JsonValue>& scrollEventJson);

    void AIPostTask(const std::function<void()>& task, TaskExecutor::TaskType taskType, const std::string& name,
        uint32_t delay = 0);

    enum class WebEventType { Unknown, Tap, LongPress, ScrollStart, ScrollEnd, PinchEnd };

    WebEventType ParseEventType(const std::string& str);

    constexpr static char EVENT_IDENTIFIER[] = "EventType";

    constexpr static char REPORT_EVENT_IDENTIFIER[] = "WebEventType";

    constexpr static int32_t LONG_PRESS_TIMEOUT_MS = 550;

private:
    WeakPtr<Pattern> pattern_;

protected:
    virtual RectF ConvertToWindow(const RectF& rect, bool addComponentOffset = true);

    // ===== scroll event process start =====
    struct ScrollEventInfo {
        std::string eventType;
        int32_t id = 0;
        RectF scrollRect;
        int retry = 0;

        std::shared_ptr<InspectorJsonValue> GetInspectorJsonValue() const;
    };
    std::queue<ScrollEventInfo> scrollQueue_;
    std::unordered_map<int32_t, ScrollEventInfo> startRecords_;
    bool processingScroll_ = false;

    static constexpr int32_t DELAYED_SCROLL_EVENT_PROCESS_MS = 16;
    static constexpr int32_t MAX_SCROLL_EVENT_UPDATE_RETRY = 2;

    virtual void ProcessScrollQueue();

    void ContinueScrollProcessing();

    virtual bool UpdateScrollEventInfoFromTree(ScrollEventInfo& info);
    enum class ScrollEndEventAction { RETRY, DROP, PROCEED };
    // Handle updated end event and return an action for the caller to take.
    virtual ScrollEndEventAction HandleUpdatedScrollEndEvent(ScrollEventInfo& info);
    // Report the scroll event and advance the queue (does not schedule further processing).
    void ReportAndAdvanceScrollQueue(const ScrollEventInfo& info, bool isScrollStart);
    // ===== scroll event process end =====
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_WEB_AGENT_EVENT_REPORT_H
