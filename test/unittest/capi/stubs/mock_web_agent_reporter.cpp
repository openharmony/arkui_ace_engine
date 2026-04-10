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

namespace OHOS::Ace::NG {
WebAgentEventReporter::WebAgentEventReporter(const WeakPtr<Pattern>& pattern)
{
}

void WebAgentEventReporter::SetAISessionOptions(uint32_t type, const AISessionCallback&& onCreateAISession,
    const AISessionCallback&& onExecuteAIAction, const AISessionCallback&& onDestroyAISession)
{
}

void WebAgentEventReporter::ReportEventImediately(const std::shared_ptr<InspectorJsonValue>& eventJson)
{
}

void WebAgentEventReporter::AddTapEvent(const std::unique_ptr<JsonValue>& tapEventJson)
{
}

void WebAgentEventReporter::AddLongPressEvent(const std::unique_ptr<JsonValue>& longPressEventJson)
{
}

void WebAgentEventReporter::AddPinchEvent(const std::unique_ptr<JsonValue>& pinchEventJson)
{
}

void WebAgentEventReporter::AddScrollEvent(const std::unique_ptr<JsonValue>& scrollEventJson)
{
}

RectF WebAgentEventReporter::ConvertToWindow(const RectF& rect, bool addComponentOffset)
{
    return {};
}

void WebAgentEventReporter::ProcessScrollQueue()
{
}

bool WebAgentEventReporter::UpdateScrollEventInfoFromTree(ScrollEventInfo& info)
{
    return false;
}

WebAgentEventReporter::ScrollEndEventAction WebAgentEventReporter::HandleUpdatedScrollEndEvent(ScrollEventInfo& info)
{
    return ScrollEndEventAction::DROP;
}
} // namespace OHOS::Ace::NG
