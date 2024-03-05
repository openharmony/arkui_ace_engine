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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/common/recorder/event_recorder.h"
#include "core/common/recorder/node_data_cache.h"
#include "core/components/checkable/checkable_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {

using GroupChangeEvent = std::function<void(const BaseEventInfo* info)>;

class CheckBoxGroupEventHub : public EventHub {
    DECLARE_ACE_TYPE(CheckBoxGroupEventHub, EventHub)

public:
    CheckBoxGroupEventHub() = default;
    ~CheckBoxGroupEventHub() override = default;

    void SetOnChange(GroupChangeEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(const BaseEventInfo* info) const
    {
        if (selectAllChangeEvent_) {
            selectAllChangeEvent_(info);
        }
        if (changeEvent_) {
            changeEvent_(info);
        }
        auto groupRet = TypeInfoHelper::DynamicCast<CheckboxGroupResult>(info);
        if (!groupRet) {
            return;
        }
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            auto host = GetFrameNode();
            if (host) {
                auto id = host->GetInspectorIdValue("");
                builder.SetId(id).SetType(host->GetHostTag()).SetDescription(host->GetAutoEventParamValue(""));
                if (!id.empty()) {
                    Recorder::NodeDataCache::Get().PutMultiple(host, id, groupname_, groupRet->GetNameList());
                }
            }
            builder.SetTextArray(groupRet->GetNameList()).SetText(groupname_);
            Recorder::EventRecorder::Get().OnChange(std::move(builder));
        }
    }

    const std::string& GetGroupName()
    {
        return groupname_;
    }

    void SetGroupName(const std::string& groupname)
    {
        groupname_ = groupname;
    }

    void SetChangeEvent(GroupChangeEvent&& changeEvent)
    {
        selectAllChangeEvent_ = std::move(changeEvent);
    }

    bool HasChangeEvent()
    {
        return selectAllChangeEvent_ != nullptr;
    }

private:
    GroupChangeEvent changeEvent_;
    std::string groupname_;
    GroupChangeEvent selectAllChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_EVENT_HUB_H
