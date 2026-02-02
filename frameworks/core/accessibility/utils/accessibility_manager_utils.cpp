/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "frameworks/core/accessibility/utils/accessibility_manager_utils.h"
#include "base/log/log_wrapper.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::NG {

void AccessibilityEventBlockerInAction::AddBlockedEvent(int64_t actionId, AccessibilityEventType event)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "AddBlockedEvent fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.insert(static_cast<uint32_t>(event));
}

void AccessibilityEventBlockerInAction::SetBlockedEvents(int64_t actionId,
    const std::vector<AccessibilityEventType>& events)
{
    CHECK_EQUAL_VOID(actionId, -1);
    if (currentActionId_ == -1) {
        currentActionId_ = actionId;
    }
    if (currentActionId_ != actionId) {
        TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY,
            "SetBlockedEvents fail by currentActionId_ %{public}" PRId64
            " actionId: %{public}" PRId64, currentActionId_, actionId);
        return;
    }
    blockedEvents_.clear();
    blockedEvents_.reserve(events.size());
    
    for (const auto& event : events) {
        blockedEvents_.insert(static_cast<uint32_t>(event));
    }
}


bool AccessibilityEventBlockerInAction::ShouldBlock(int64_t actionId, AccessibilityEventType eventType) const
{
    CHECK_EQUAL_RETURN(actionId, -1, false);
    CHECK_NE_RETURN(actionId, currentActionId_, false);
    CHECK_NE_RETURN(blockedEvents_.find(static_cast<uint32_t>(eventType)), blockedEvents_.end(), true);
    return false;
}

void AccessibilityEventBlockerInAction::Reset()
{
    currentActionId_ = -1;
    blockedEvents_.clear();
}
} // namespace OHOS::Ace::NG
