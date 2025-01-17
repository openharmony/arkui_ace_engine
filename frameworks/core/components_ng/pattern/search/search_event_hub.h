/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_EVENT_HUB_H

#include "base/memory/ace_type.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/search/search_gesture_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::NG {
using ChangeAndSubmitEvent = std::function<void(const std::string)>;
class SearchEventHub : public EventHub {
    DECLARE_ACE_TYPE(SearchEventHub, EventHub)

public:
    SearchEventHub() = default;

    ~SearchEventHub() override = default;

    void SetOnSubmit(std::function<void(const std::string&, NG::TextFieldCommonEvent&)>&& func)
    {
        onSubmit_ = std::move(func);
    }

    void FireOnSubmit(const std::string& value, NG::TextFieldCommonEvent& event)
    {
        if (onSubmit_) {
            event.SetText(value);
            onSubmit_(value, event);
        }
        if (Recorder::EventRecorder::Get().IsComponentRecordEnable()) {
            Recorder::EventParamsBuilder builder;
            auto host = GetFrameNode();
            if (host) {
                auto id = host->GetInspectorIdValue("");
                builder.SetId(id).SetType(host->GetHostTag()).SetDescription(host->GetAutoEventParamValue(""));
            }
            builder.SetEventType(Recorder::EventType::SEARCH_SUBMIT).SetText(value);
            Recorder::EventRecorder::Get().OnEvent(std::move(builder));
        }
    }

    void SetOnChange(ChangeAndSubmitEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateChangeEvent(const std::string& value) const;

    void SetOnCopy(std::function<void(const std::string&)>&& func)
    {
        onCopy_ = std::move(func);
    }

    void FireOnCopy(const std::string& value)
    {
        if (onCopy_) {
            onCopy_(value);
        }
    }

    void SetOnCut(std::function<void(const std::string&)>&& func)
    {
        onCut_ = std::move(func);
    }

    void FireOnCut(const std::string& value)
    {
        if (onCut_) {
            onCut_(value);
        }
    }

    void SetOnPaste(std::function<void(const std::string&)>&& func)
    {
        onPaste_ = std::move(func);
    }

    void FireOnPaste(const std::string& value)
    {
        if (onPaste_) {
            onPaste_(value);
        }
    }

    void SetOnPasteWithEvent(std::function<void(const std::string&, NG::TextCommonEvent&)>&& func)
    {
        onPasteWithEvent_ = std::move(func);
    }

    void FireOnPasteWithEvent(const std::string& value, NG::TextCommonEvent& event)
    {
        if (onPasteWithEvent_) {
            onPasteWithEvent_(value, event);
        }
    }

    void SetOnChangeEvent(ChangeAndSubmitEvent&& onChangeEvent)
    {
        onValueChangeEvent_ = std::move(onChangeEvent);
    }

    RefPtr<GestureEventHub> CreateGestureEventHub() override
    {
        return MakeRefPtr<SearchGestureEventHub>(WeakClaim(this));
    }

private:
    ChangeAndSubmitEvent changeEvent_;
    ChangeAndSubmitEvent onValueChangeEvent_;

    std::function<void(const std::string&)> onCopy_;
    std::function<void(const std::string&)> onCut_;
    std::function<void(const std::string&)> onPaste_;
    std::function<void(const std::string&, NG::TextCommonEvent&)> onPasteWithEvent_;
    std::function<void(const std::string&, NG::TextFieldCommonEvent&)> onSubmit_;

    ACE_DISALLOW_COPY_AND_MOVE(SearchEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_EVENT_HUB_H
