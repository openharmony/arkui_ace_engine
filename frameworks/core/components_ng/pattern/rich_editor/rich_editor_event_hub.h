/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H

#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/text/selection_info.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_gesture_event_hub.h"
#include "core/components_ng/pattern/text_field/text_field_event_hub.h"
#include "core/components_ng/pattern/text/styled_string_change_value.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_abstract_span_result.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_value.h"
#include "core/common/ime/text_range.h"

namespace OHOS::Ace {
class SpanStringBase;
}

namespace OHOS::Ace::NG {
class TextInsertValueInfo {
public:
    TextInsertValueInfo() = default;
    ~TextInsertValueInfo() = default;
    void SetSpanIndex(int32_t spanIndex);
    int32_t GetSpanIndex() const;
    void SetOffsetInSpan(int32_t offsetInSpan);
    int32_t GetOffsetInSpan() const;
    std::string ToString() const;

private:
    int32_t spanIndex_ = 0;
    int32_t offsetInSpan_ = 0;
};

class RichEditorEventHub : public EventHub {
    DECLARE_ACE_TYPE(RichEditorEventHub, EventHub);

public:
    RichEditorEventHub() = default;
    ~RichEditorEventHub() override = default;
    void SetOnReady(std::function<void()>&& func);
    void FireOnReady();
    void SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func);
    bool FireAboutToIMEInput(const RichEditorInsertValue& info);
    void SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func);
    void SetOnDidIMEInput(std::function<void(const TextRange&)>&& func);
    void FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info);
    void FireOnDidIMEInput(const TextRange& info);
    void SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func);
    bool FireAboutToDelete(const RichEditorDeleteValue& info);
    void SetOnDeleteComplete(std::function<void()>&& func);
    void FireOnDeleteComplete();
    std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType type) override;
    void SetOnEditingChange(std::function<void(const bool&)>&& func);
    void FireOnEditingChange(bool isEditing);
    void SetOnSelect(std::function<void(const BaseEventInfo*)>&& func);
    void FireOnSelect(BaseEventInfo* value);
    void SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func);
    void FireOnSelectionChange(BaseEventInfo* value);
    void SetTimestamp(long long timestamp);
    void SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func);
    void FireOnPaste(NG::TextCommonEvent& value);
    void SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func);
    void FireOnSubmit(int32_t value, NG::TextFieldCommonEvent& event);
    void SetOnWillAttachIME(IMEAttachCallback&& func);
    void FireOnWillAttachIME(IMEClient& info);
    RefPtr<GestureEventHub> CreateGestureEventHub() override;
    void SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func);
    bool FireOnWillChange(const RichEditorChangeValue& info);
    bool HasOnWillChange() const;
    void SetOnDidChange(std::function<void(const RichEditorChangeValue&)>&& func);
    void FireOnDidChange(const RichEditorChangeValue& info);
    bool HasOnDidChange() const;
    void SetOnScrollChangeEvent(std::function<void(float, float)>&& func);
    bool HasOnScrollChange() const;
    void FireOnScrollChangeEvent(float offsetX, float offsetY);
    void SetOnContentSizeChange(std::function<void(float, float)>&& func);
    bool HasOnContentSizeChange() const;
    void FireOnContentSizeChange(float width, float height);
    void SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func);
    void FireOnCut(NG::TextCommonEvent& value);
    void SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func);
    void FireOnCopy(NG::TextCommonEvent& value);
    void SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func);
    void FireOnShare(NG::TextCommonEvent& value);
    void SetOnStyledStringWillChange(std::function<bool(const StyledStringChangeValue&)>&& func);
    bool FireOnStyledStringWillChange(const StyledStringChangeValue& info);
    bool HasOnStyledStringWillChange() const;
    void SetOnStyledStringDidChange(std::function<void(const StyledStringChangeValue&)>&& func);
    void FireOnStyledStringDidChange(const StyledStringChangeValue& info);
    bool HasOnStyledStringDidChange() const;

private:
    long long timestamp_ = 0;
    std::function<void(NG::TextCommonEvent&)> onPaste_;
    std::function<void()> onReady_;
    std::function<void(const BaseEventInfo*)> onSelect_;
    std::function<void(const BaseEventInfo*)> OnSelectionChange_;
    std::function<bool(const RichEditorInsertValue&)> aboutToIMEInput_;
    std::function<void(const RichEditorAbstractSpanResult&)> onIMEInputComplete_;
    std::function<void(const TextRange&)> onDidIMEInput_;
    std::function<bool(const RichEditorDeleteValue&)> aboutToDelete_;
    std::function<void()> onDeleteComplete_;
    std::function<void(int32_t, NG::TextFieldCommonEvent&)> onSubmit_;
    std::function<void(const bool&)> onEditingChange_;
    std::function<bool(const RichEditorChangeValue&)> onWillChange_;
    std::function<void(const RichEditorChangeValue&)> onDidChange_;
    std::function<void(float, float)> onScrollChangeEvent_;
    std::function<void(float, float)> onContentSizeChangeEvent_;
    std::function<void(NG::TextCommonEvent&)> onCut_;
    std::function<void(NG::TextCommonEvent&)> onCopy_;
    std::function<void(NG::TextCommonEvent&)> onShare_;
    std::function<bool(const StyledStringChangeValue&)> onStyledStringWillChange_;
    std::function<void(const StyledStringChangeValue&)> onStyledStringDidChange_;
    IMEAttachCallback onWillAttachIME_;
    ACE_DISALLOW_COPY_AND_MOVE(RichEditorEventHub);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_RICH_EDITOR_EVENT_HUB_H
