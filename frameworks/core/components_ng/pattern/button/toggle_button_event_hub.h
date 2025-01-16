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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_event_hub.h"

namespace OHOS::Ace::NG {

using ChangeEvent = std::function<void(const bool)>;

class ToggleButtonEventHub : public ButtonEventHub {
    DECLARE_ACE_TYPE(ToggleButtonEventHub, ButtonEventHub)

public:
    ToggleButtonEventHub() = default;
    ~ToggleButtonEventHub() override = default;

    void SetOnChange(ChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(bool select) const
    {
        if (onChangeEvent_) {
            onChangeEvent_(select);
        }
        if (changeEvent_) {
            changeEvent_(select);
        }
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            auto host = GetFrameNode();
            if (host) {
                auto id = host->GetInspectorIdValue("");
                builder.SetId(id)
                    .SetType(host->GetHostTag())
                    .SetDescription(host->GetAutoEventParamValue(""))
                    .SetHost(host);
                if (!id.empty()) {
                    Recorder::NodeDataCache::Get().PutBool(host, id, select);
                }
            }
            builder.SetChecked(select);
            Recorder::EventRecorder::Get().OnChange(std::move(builder));
        }
    }

    void SetOnChangeEvent(ChangeEvent&& onChangeEvent)
    {
        onChangeEvent_ = std::move(onChangeEvent);
    }

private:
    ChangeEvent changeEvent_;
    ChangeEvent onChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(ToggleButtonEventHub);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_BUTTON_TOGGLE_BUTTON_EVENT_HUB_H
