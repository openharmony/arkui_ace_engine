/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TABS_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TABS_EVENT_H

#include "core/event/ace_events.h"

namespace OHOS::Ace {

class ACE_EXPORT TabContentChangeEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TabContentChangeEvent, BaseEventInfo);

public:
    explicit TabContentChangeEvent(int32_t index) : BaseEventInfo("TabContentChangeEvent"), index_(index) {}

    ~TabContentChangeEvent() override = default;

    int32_t GetIndex() const
    {
        return index_;
    }

private:
    int32_t index_ = 0;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_TAB_BAR_TABS_EVENT_H
