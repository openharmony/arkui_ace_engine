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

#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::Recorder {
EventParamsBuilder::EventParamsBuilder() {}

EventParamsBuilder& EventParamsBuilder::SetEventType(EventType eventType)
{
    (void)eventType;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetId(const std::string& id)
{
    (void)id;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetType(const std::string& type)
{
    (void)type;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetDescription(const std::string& desc)
{
    (void)desc;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetText(const std::string& value)
{
    (void)value;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetTextArray(const std::vector<std::string>& value)
{
    (void)value;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetHost(const RefPtr<NG::FrameNode>& node)
{
    (void)node;
    return *this;
}

EventParamsBuilder& EventParamsBuilder::SetExtra(const std::string& key, const std::string& value)
{
    (void)key;
    (void)value;
    return *this;
}

bool EventRecorder::IsComponentRecordEnable() const
{
    return false;
}

bool EventRecorder::IsRecordEnable(EventCategory category) const
{
    (void)category;
    return false;
}

void EventRecorder::OnEvent(EventParamsBuilder&& builder)
{
    (void)builder;
}

void EventRecorder::OnClick(EventParamsBuilder&& builder) {}
} // namespace OHOS::Ace::Recorder
