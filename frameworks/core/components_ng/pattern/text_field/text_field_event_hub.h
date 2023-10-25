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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_EVENT_HUB_H

#include <cstdint>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
class TextFieldEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextFieldEventHub, EventHub)

public:
    TextFieldEventHub() = default;
    ~TextFieldEventHub() override = default;

    void SetOnInputFilterError(const std::function<void(const std::string&)>& onInputFilterError)
    {
        onInputFilterError_ = onInputFilterError;
    }

    void FireOnInputFilterError(const std::string& value) const
    {
        if (onInputFilterError_) {
            LOGI("On filter error %{private}s", value.c_str());
            onInputFilterError_(value);
        }
    }

    void SetOnEditChanged(std::function<void(bool)>&& func)
    {
        onEditChanged_ = std::move(func);
    }

    void FireOnEditChanged(bool value)
    {
        if (onEditChanged_) {
            LOGI("On edit change %{private}d", value);
            onEditChanged_(value);
        }
    }

    void SetOnSubmit(std::function<void(int32_t)>&& func)
    {
        onSubmit_ = std::move(func);
    }

    void FireOnSubmit(int32_t value)
    {
        if (onSubmit_) {
            LOGI("On submit %{private}d", value);
            onSubmit_(value);
        }
    }

    void SetOnChange(std::function<void(const std::string&)>&& func)
    {
        onChange_ = std::move(func);
    }

    const std::function<void(const std::string&)>& GetOnChange() const
    {
        return onChange_;
    }

    void FireOnChange(const std::string& value)
    {
        if (lastValue_.has_value() && lastValue_.value() == value) {
            return;
        }
        if (onValueChangeEvent_) {
            LOGI("On change event %{private}s", value.c_str());
            onValueChangeEvent_(value);
        }
        if (onChange_) {
            LOGI("On change %{private}s", value.c_str());
            onChange_(value);
        }
        lastValue_ = value;
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

    void SetOnCopy(std::function<void(const std::string&)>&& func)
    {
        onCopy_ = std::move(func);
    }

    void FireOnCopy(const std::string& value)
    {
        if (onCopy_) {
            LOGI("On copy %{private}s", value.c_str());
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
            LOGI("On cut %{private}s", value.c_str());
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
            LOGI("On paste %{private}s", value.c_str());
            onPaste_(value);
        }
    }

    void SetOnScroll(OnScrollEvent&& onScroll)
    {
        onScrollEvent_ = std::move(onScroll);
    }

    const OnScrollEvent& GetOnScroll() const
    {
        return onScrollEvent_;
    }

    void SetOnScrollBegin(OnScrollBeginEvent&& onScrollBegin)
    {
        onScrollBeginEvent_ = std::move(onScrollBegin);
    }

    const OnScrollBeginEvent& GetOnScrollBegin() const
    {
        return onScrollBeginEvent_;
    }

    void SetOnScrollFrameBegin(OnScrollFrameBeginEvent&& onScrollFrameBegin)
    {
        onScrollFrameBeginEvent_ = std::move(onScrollFrameBegin);
    }

    const OnScrollFrameBeginEvent& GetOnScrollFrameBegin() const
    {
        return onScrollFrameBeginEvent_;
    }

    void SetOnScrollStart(OnScrollStartEvent&& onScrollStart)
    {
        onScrollStartEvent_ = std::move(onScrollStart);
    }

    const OnScrollStartEvent& GetOnScrollStart() const
    {
        return onScrollStartEvent_;
    }

    void SetOnScrollStop(OnScrollStopEvent&& onScrollStop)
    {
        onScrollStopEvent_ = std::move(onScrollStop);
    }

    const OnScrollStopEvent& GetOnScrollStop() const
    {
        return onScrollStopEvent_;
    }

    void SetOnScrollIndex(OnScrollIndexEvent&& onScrollIndex)
    {
        onScrollIndexEvent_ = std::move(onScrollIndex);
    }

    const OnScrollIndexEvent& GetOnScrollIndex() const
    {
        return onScrollIndexEvent_;
    }

    void SetOnChangeEvent(std::function<void(const std::string&)>&& func)
    {
        onValueChangeEvent_ = std::move(func);
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
    std::optional<std::string> lastValue_;

    OnScrollEvent onScrollEvent_;
    OnScrollBeginEvent onScrollBeginEvent_;
    OnScrollFrameBeginEvent onScrollFrameBeginEvent_;
    OnScrollStartEvent onScrollStartEvent_;
    OnScrollStopEvent onScrollStopEvent_;
    OnScrollIndexEvent onScrollIndexEvent_;
    std::function<void(float, float)> onScrollChangeEvent_;

    std::function<void(const std::string&)> onInputFilterError_;
    std::function<void(bool)> onEditChanged_;
    std::function<void(int32_t)> onSubmit_;
    std::function<void(const std::string&)> onChange_;
    std::function<void(int32_t, int32_t)> onSelectionChange_;

    std::function<void(const std::string&)> onCopy_;
    std::function<void(const std::string&)> onCut_;
    std::function<void(const std::string&)> onPaste_;
    std::function<void(const std::string&)> onValueChangeEvent_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_EVENT_HUB_H
