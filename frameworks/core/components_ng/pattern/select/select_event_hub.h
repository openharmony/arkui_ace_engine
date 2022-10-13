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

#include "base/memory/ace_type.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"


#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SELECT_SELECT_EVENT_HUB_H

namespace OHOS::Ace::NG {

using SelectEvent = std::function<void(const int32_t, const std::string&)>;

class SelectEventHub : public EventHub {
    DECLARE_ACE_TYPE(SelectEventHub, EventHub)
public:
    SelectEventHub() = default;

    ~SelectEventHub() override = default;

    const std::vector<std::string>& GetValues()
    {
        return values_;
    }

    const std::vector<std::string>& GetIcons()
    {
        return icons_;
    }

    void SetValues(const std::vector<std::string>& values)
    {
        values_ = values;
    }

    void SetIcons(const std::vector<std::string>& icons)
    {
        icons_ = icons;
    }



private:
    std::vector<std::string> values_;
    std::vector<std::string> icons_;
    std::size_t selected_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(SelectEventHub);
};
} // namespace OHOS::Ace::NG
#endif
 