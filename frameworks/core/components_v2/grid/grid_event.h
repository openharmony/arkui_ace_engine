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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_GRID_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_GRID_EVENT_H

#include "core/event/ace_events.h"

namespace OHOS::Ace::V2 {

class GridEventInfo : public BaseEventInfo, public EventToJSONStringAdapter {
    DECLARE_RELATIONSHIP_OF_CLASSES(GridEventInfo, BaseEventInfo, EventToJSONStringAdapter);

public:
    explicit GridEventInfo(int32_t scrollIndex) : BaseEventInfo("grid"), scrollIndex_(scrollIndex) {}

    ~GridEventInfo() override = default;

    std::string ToJSONString() const override;

    int32_t GetScrollIndex() const
    {
        return scrollIndex_;
    }

private:
    int32_t scrollIndex_ = 0;
};

} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_GRID_EVENT_H