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
#include "base/utils/utf_helper.h"
#include "core/common/ime/text_range.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace {
enum class TextDeleteDirection { BACKWARD = 0, FORWARD = 1 };

struct InsertValueInfo {
    int32_t insertOffset = 0;
    std::u16string insertValue;
};

struct DeleteValueInfo {
    int32_t deleteOffset = 0;
    TextDeleteDirection direction = TextDeleteDirection::BACKWARD;
    std::u16string deleteValue;
};

struct PreviewText {
    int32_t offset;
    std::u16string value;

    bool operator==(const PreviewText& other) const
    {
        return this->offset == other.offset && this->value == other.value;
    }

    bool operator!=(const PreviewText& other) const
    {
        return this->offset != other.offset || this->value != other.value;
    }
};
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class TextFieldCommonEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TextFieldCommonEvent, BaseEventInfo)
public:
    TextFieldCommonEvent() : BaseEventInfo("TextFieldCommonEvent") {}
    ~TextFieldCommonEvent() override = default;

    bool IsKeepEditable() const
    {
        return keepEditable_;
    }
    void SetKeepEditable(bool keepEditable)
    {
        keepEditable_ = keepEditable;
    }
    std::u16string GetText() const
    {
        return text_;
    }
    void SetText(std::u16string text)
    {
        text_ = text;
    }
private:
    bool keepEditable_ = false;
    std::u16string text_;
};

class TextFieldEventHub : public EventHub {
    DECLARE_ACE_TYPE(TextFieldEventHub, EventHub)

public:
    TextFieldEventHub() = default;
    ~TextFieldEventHub() override = default;

    void SetOnInputFilterError(const std::function<void(const std::u16string&)>& onInputFilterError)
    {
        onInputFilterError_ = onInputFilterError;
    }

    void FireOnInputFilterError(const std::u16string& value) const
    {
        if (onInputFilterError_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On filter error %{private}s", UtfUtils::Str16ToStr8(value).c_str());
            onInputFilterError_(value);
        }
    }

    void SetOnEditChanged(std::function<void(bool)>&& func)
    {
        onEditChanged_ = std::move(func);
    }

    void SetOnSecurityStateChange(std::function<void(bool)>&& func)
    {
        onSecurityStateChanged_ = std::move(func);
    }

    void FireOnSecurityStateChanged(bool value)
    {
        if (onSecurityStateChanged_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "FireOnSecurityStateChanged %{public}d", value);
            onSecurityStateChanged_(value);
        }
    }

    void FireOnEditChanged(bool value)
    {
        if (onEditChanged_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On edit change %{private}d", value);
            onEditChanged_(value);
        }
    }

    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
    {
        onSubmit_ = std::move(func);
    }

    void FireOnSubmit(int32_t value, NG::TextFieldCommonEvent& event)
    {
        if (onSubmit_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On submit %{private}d", value);
            onSubmit_(value, event);
        }
    }

    void SetOnChange(std::function<void(const std::u16string&, PreviewText&)>&& func)
    {
        onChange_ = std::move(func);
    }

    const std::function<void(const std::u16string&, PreviewText&)>& GetOnChange() const
    {
        return onChange_;
    }

    void FireOnChange(const std::u16string& value, PreviewText& previewText)
    {
        if (lastValue_.has_value() && lastValue_.value() == value && lastPreviewText_ == previewText) {
            return;
        }
        if (onValueChangeEvent_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On change event");
            onValueChangeEvent_(value);
        }
        if (onChange_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On change previewText index %{private}d", previewText.offset);
            // Not all in one, in order to fix the cppcrash bug
            auto onChange = onChange_;
            onChange(value, previewText);
        }
        lastValue_ = value;
        lastPreviewText_ = previewText;
    }

    void SetOnContentSizeChange(std::function<void(float, float)>&& func)
    {
        onContentSizeChange_ = std::move(func);
    }

    const std::function<void(float, float)>& GetOnContentSizeChange() const
    {
        return onContentSizeChange_;
    }

    void FireOnContentSizeChange(float width, float height)
    {
        if (onContentSizeChange_) {
            onContentSizeChange_(width, height);
        }
    }

    void SetOnSelectionChange(std::function<void(int32_t, int32_t)>&& func)
    {
        onSelectionChange_ = std::move(func);
    }

    void FireOnSelectionChange(int32_t selectionStart, int32_t selectionEnd)
    {
        if (onSelectionChange_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On selection change start %{private}d, end %{private}d",
                selectionStart, selectionEnd);
            onSelectionChange_(selectionStart, selectionEnd);
        }
    }

    void SetOnCopy(std::function<void(const std::u16string&)>&& func)
    {
        onCopy_ = std::move(func);
    }

    void FireOnCopy(const std::u16string& value)
    {
        if (onCopy_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On copy %{private}s", UtfUtils::Str16ToStr8(value).c_str());
            onCopy_(value);
        }
    }

    void SetOnCut(std::function<void(const std::u16string&)>&& func)
    {
        onCut_ = std::move(func);
    }

    void FireOnCut(const std::u16string& value)
    {
        if (onCut_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On cut %{private}s", UtfUtils::Str16ToStr8(value).c_str());
            onCut_(value);
        }
    }

    void SetOnPaste(std::function<void(const std::u16string&)>&& func)
    {
        onPaste_ = std::move(func);
    }

    void FireOnPaste(const std::u16string& value)
    {
        if (onPaste_) {
            TAG_LOGI(AceLogTag::ACE_TEXT_FIELD, "On paste %{private}s", UtfUtils::Str16ToStr8(value).c_str());
            onPaste_(value);
        }
    }

    void SetOnPasteWithEvent(std::function<void(const std::u16string&, NG::TextCommonEvent&)>&& func)
    {
        onPasteWithEvent_ = std::move(func);
    }

    void FireOnPasteWithEvent(const std::u16string& value, NG::TextCommonEvent& event)
    {
        if (onPasteWithEvent_) {
            onPasteWithEvent_(value, event);
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

    void SetOnChangeEvent(std::function<void(const std::u16string&)>&& func)
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

    void SetOnWillInsertValueEvent(std::function<bool(const InsertValueInfo&)>&& func)
    {
        onWillInsertValueEvent_ = std::move(func);
    }

    bool FireOnWillInsertValueEvent(const InsertValueInfo& info)
    {
        if (onWillInsertValueEvent_) {
            return onWillInsertValueEvent_(info);
        }
        return true;
    }

    void SetOnDidInsertValueEvent(std::function<void(const InsertValueInfo&)>&& func)
    {
        onDidInsertValueEvent_ = std::move(func);
    }

    void FireOnDidInsertValueEvent(const InsertValueInfo& info)
    {
        if (onDidInsertValueEvent_) {
            onDidInsertValueEvent_(info);
        }
    }

    void SetOnWillDeleteEvent(std::function<bool(const DeleteValueInfo&)>&& func)
    {
        onWillDeleteEvent_ = std::move(func);
    }

    bool FireOnWillDeleteEvent(const DeleteValueInfo& info)
    {
        if (onWillDeleteEvent_) {
            return onWillDeleteEvent_(info);
        }
        return true;
    }

    void SetOnDidDeleteEvent(std::function<void(const DeleteValueInfo&)>&& func)
    {
        onDidDeleteEvent_ = std::move(func);
    }

    void FireOnDidDeleteValueEvent(const DeleteValueInfo& info)
    {
        if (onDidDeleteEvent_) {
            onDidDeleteEvent_(info);
        }
    }

private:
    std::optional<std::u16string> lastValue_;
    PreviewText lastPreviewText_ {};

    OnScrollEvent onScrollEvent_;
    OnScrollBeginEvent onScrollBeginEvent_;
    OnScrollFrameBeginEvent onScrollFrameBeginEvent_;
    OnScrollStartEvent onScrollStartEvent_;
    OnScrollStopEvent onScrollStopEvent_;
    OnScrollIndexEvent onScrollIndexEvent_;
    std::function<void(float, float)> onScrollChangeEvent_;

    std::function<void(const std::u16string&)> onInputFilterError_;
    std::function<void(bool)> onEditChanged_;
    std::function<void(bool)> onSecurityStateChanged_;
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> onSubmit_;
    std::function<void(const std::u16string&, PreviewText&)> onChange_;
    std::function<void(float, float)> onContentSizeChange_;
    std::function<void(int32_t, int32_t)> onSelectionChange_;

    std::function<void(const std::u16string&)> onCopy_;
    std::function<void(const std::u16string&)> onCut_;
    std::function<void(const std::u16string&)> onPaste_;
    std::function<void(const std::u16string&, NG::TextCommonEvent&)> onPasteWithEvent_;
    std::function<void(const std::u16string&)> onValueChangeEvent_;

    std::function<bool(const InsertValueInfo&)> onWillInsertValueEvent_;
    std::function<void(const InsertValueInfo&)> onDidInsertValueEvent_;
    std::function<bool(const DeleteValueInfo&)> onWillDeleteEvent_;
    std::function<void(const DeleteValueInfo&)> onDidDeleteEvent_;
    ACE_DISALLOW_COPY_AND_MOVE(TextFieldEventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_FIELD_TEXT_FIELD_EVENT_HUB_H
