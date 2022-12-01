/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_EVENT_HUB_H

#include <stdint.h>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

class PageEventHub : public EventHub {
    DECLARE_ACE_TYPE(PageEventHub, EventHub)

public:
    PageEventHub() = default;
    ~PageEventHub() override = default;

    void AddRadioToGroup(const std::string& group, int32_t radioId);
    void RemoveRadioFromGroup(const std::string& group, int32_t radioId);
    bool HasRadioId(const std::string& group, int32_t radioId);
    void UpdateRadioGroupValue(const std::string& group, int32_t radioId);

    void AddCheckBoxToGroup(const std::string& group, int32_t checkBoxId);
    void AddCheckBoxGroupToGroup(const std::string& group, int32_t checkBoxId);
    void RemoveCheckBoxFromGroup(const std::string& group, int32_t checkBoxId);

    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> GetCheckBoxGroupMap();

private:
    std::unordered_map<std::string, std::list<int32_t>> radioGroupNotify_;

    std::unordered_map<std::string, std::list<int32_t>> checkBoxGroupNotify_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STAGE_PAGE_EVENT_HUB_H