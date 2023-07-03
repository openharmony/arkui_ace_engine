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
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"

namespace OHOS::Ace::NG {
using ChangeAndSubmitEvent = std::function<void(const std::string)>;
class SearchEventHub : public EventHub {
    DECLARE_ACE_TYPE(SearchEventHub, EventHub)

public:
    SearchEventHub() = default;

    ~SearchEventHub() override = default;

    void SetOnSubmit(ChangeAndSubmitEvent&& submitEvent)
    {
        submitEvent_ = std::move(submitEvent);
    }

    void SetOnChange(ChangeAndSubmitEvent&& changeEvent)
    {
        changeEvent_ = std::move(changeEvent);
    }

    void UpdateSubmitEvent(const std::string& value) const
    {
        if (submitEvent_) {
            submitEvent_(value);
        }
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

    void SetOnChangeEvent(ChangeAndSubmitEvent&& onChangeEvent)
    {
        onValueChangeEvent_ = std::move(onChangeEvent);
    }

    void SetOnSelectionChange(std::function<void(int32_t, int32_t)>&& func)
    {
        onSelectionChange_ = std::move(func);
    }

    void FireOnSelectionChange(int32_t selectionStart, int32_t selectionEnd)
    {
        if (onSelectionChange_) {
            LOGI("On selection change start %{private}d, end %{private}d", selectionStart, selectionEnd);
            onSelectionChange_(selectionStart, selectionEnd);
        }
    }

    void SetOnScrollChangeEvent(std::function<void(float, float)>&& func)
    {
        onScrollChangeEvent_ = std::move(func);
    }

    void FireOnScrollChangeEvent(float offsetX, float offsetY)
    {
        if (onScrollChangeEvent_) {
            onScrollChangeEvent_(offsetX, offsetY);
        }
    }

private:
    ChangeAndSubmitEvent submitEvent_;
    ChangeAndSubmitEvent changeEvent_;
    ChangeAndSubmitEvent onValueChangeEvent_;

    std::function<void(const std::string&)> onCopy_;
    std::function<void(const std::string&)> onCut_;
    std::function<void(const std::string&)> onPaste_;
    std::function<void(int32_t, int32_t)> onSelectionChange_;
    std::function<void(float, float)> onScrollChangeEvent_;

    ACE_DISALLOW_COPY_AND_MOVE(SearchEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_SEARCH_SEARCH_EVENT_HUB_H
