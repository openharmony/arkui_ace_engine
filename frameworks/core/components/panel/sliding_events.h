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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PANEL_SLIDING_EVENTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PANEL_SLIDING_EVENTS_H

#include "core/components/common/layout/constants.h"

#include "core/event/ace_events.h"

namespace OHOS::Ace {

class ACE_EXPORT SlidingPanelSizeChangeEvent : public BaseEventInfo, public EventToJSONStringAdapter {
    DECLARE_RELATIONSHIP_OF_CLASSES(SlidingPanelSizeChangeEvent, BaseEventInfo, EventToJSONStringAdapter);

public:
    SlidingPanelSizeChangeEvent(PanelMode mode, double width, double height)
        : BaseEventInfo("SlidingPanelSizeChangeEvent"), mode_(mode), width_(width), height_(height)
    {}

    ~SlidingPanelSizeChangeEvent() = default;

    double GetWidth() const
    {
        return width_;
    }

    double GetHeight() const
    {
        return height_;
    }

    PanelMode GetMode() const
    {
        return mode_;
    }

    std::string ToJSONString() const override;

private:
    PanelMode mode_ = PanelMode::HALF;
    double width_ = 0.0;
    double height_ = 0.0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PANEL_SLIDING_EVENTS_H
