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

#include "core/common/event_info_manager.h"

#include "core/components_ng/event/touch_event.h"
#include "core/event/axis_event.h"
#include "core/event/mouse_event.h"

namespace OHOS::Ace {

int32_t EventInfoManager::AddAxisInfo(const std::shared_ptr<AxisInfo>& info)
{
    int32_t id = axisNextId_++;
    info->SetEventId(id);
    axisMap_.emplace(id, info);
    return id;
}
int32_t EventInfoManager::RemoveAxisInfo(int32_t eventId)
{
    return static_cast<int32_t>(axisMap_.erase(eventId));
}

int32_t EventInfoManager::AddMouseInfo(const std::shared_ptr<MouseInfo>& info)
{
    int32_t id = mouseNextId_++;
    info->SetEventId(id);
    mouseMap_.emplace(id, info);
    return id;
}
int32_t EventInfoManager::RemoveMouseInfo(int32_t eventId)
{
    return static_cast<int32_t>(mouseMap_.erase(eventId));
}

int32_t EventInfoManager::AddTouchEventInfo(const std::shared_ptr<TouchEventInfo>& info)
{
    int32_t id = touchNextId_++;
    info->SetEventId(id);
    touchMap_.emplace(id, info);
    return id;
}
int32_t EventInfoManager::RemoveTouchEventInfo(int32_t eventId)
{
    return static_cast<int32_t>(touchMap_.erase(eventId));
}

} // namespace OHOS::Ace