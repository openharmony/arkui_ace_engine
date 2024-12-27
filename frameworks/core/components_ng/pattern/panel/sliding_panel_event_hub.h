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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H

#include <memory>

#include "base/memory/ace_type.h"
#include "core/common/recorder/event_recorder.h"
#include "core/components/panel/sliding_events.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const BaseEventInfo*)>;
using HeightChangeEvent = std::function<void(const float)>;

class SlidingPanelEventHub : public EventHub {
    DECLARE_ACE_TYPE(SlidingPanelEventHub, EventHub)

public:
    SlidingPanelEventHub() = default;
    ~SlidingPanelEventHub() override = default;

    void SetOnSizeChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void SetOnHeightChange(HeightChangeEvent&& heightChangeEvent)
    {
        heightChangeEvent_ = std::move(heightChangeEvent);
    }

    void FireSizeChangeEvent(PanelMode mode, float width, float height) const
    {
        if (modeChangeEvent_) {
            auto modeChangEvent = std::make_shared<SlidingPanelSizeChangeEvent>(mode, width, height);
            modeChangeEvent_(modeChangEvent.get());
        }
        if (changeEvent_) {
            auto changEvent = std::make_shared<SlidingPanelSizeChangeEvent>(mode, width, height);
            changeEvent_(changEvent.get());
        }
        if (!Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            return;
        }
        Recorder::EventParamsBuilder builder;
        auto host = GetFrameNode();
        if (host) {
            builder.SetId(host->GetInspectorIdValue(""))
                .SetType(host->GetHostTag())
                .SetHost(host)
                .SetDescription(host->GetAutoEventParamValue(""));
        }
        std::string modeDesc;
        if (mode == PanelMode::MINI) {
            modeDesc = "Mini";
        } else if (mode == PanelMode::HALF) {
            modeDesc = "Half";
        } else if (mode == PanelMode::FULL) {
            modeDesc = "Full";
        } else if (mode == PanelMode::AUTO) {
            modeDesc = "Auto";
        } else if (mode == PanelMode::CUSTOM) {
            modeDesc = "Custom";
        } else {
            modeDesc = "";
        }
        builder.SetText(modeDesc);
        Recorder::EventRecorder::Get().OnChange(std::move(builder));
    }

    void FireHeightChangeEvent(float currentOffset) const
    {
        if (heightChangeEvent_) {
            heightChangeEvent_(currentOffset);
        }
    }

    void SetModeChangeEvent(ChangeEvent&& modeChangeEvent)
    {
        modeChangeEvent_ = std::move(modeChangeEvent);
    }

private:
    ChangeEvent changeEvent_;
    HeightChangeEvent heightChangeEvent_;
    ChangeEvent modeChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(SlidingPanelEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PANEL_SLIDING_PANEL_EVENT_HUB_H
