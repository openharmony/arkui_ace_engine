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
#include "core/components_ng/pattern/rich_editor/rich_editor_event_hub.h"
#include "base/utils/utf_helper.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {

void RichEditorEventHub::SetOnReady(std::function<void()>&& func)
{
    onReady_ = std::move(func);
}

void RichEditorEventHub::FireOnReady()
{
    if (!onReady_) {
        return;
    }
    auto callback = onReady_;
    callback();
    auto host = GetFrameNode();
    CHECK_NULL_VOID(host);
    auto* context = host->GetContext();
    CHECK_NULL_VOID(context);
    context->AddAfterRenderTask([host]() { host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE); });
}

void RichEditorEventHub::SetAboutToIMEInput(std::function<bool(const RichEditorInsertValue&)>&& func)
{
    aboutToIMEInput_ = std::move(func);
}

bool RichEditorEventHub::FireAboutToIMEInput(const RichEditorInsertValue& info)
{
    if (!aboutToIMEInput_) {
        return true;
    }
    auto callback = aboutToIMEInput_;
    return callback(info);
}

void RichEditorEventHub::SetOnIMEInputComplete(std::function<void(const RichEditorAbstractSpanResult&)>&& func)
{
    onIMEInputComplete_ = std::move(func);
}

void RichEditorEventHub::FireOnIMEInputComplete(const RichEditorAbstractSpanResult& info)
{
    if (!onIMEInputComplete_) {
        return;
    }
    auto callback = onIMEInputComplete_;
    callback(info);
}

void RichEditorEventHub::SetOnDidIMEInput(std::function<void(const TextRange&)>&& func)
{
    onDidIMEInput_ = std::move(func);
}

void RichEditorEventHub::FireOnDidIMEInput(const TextRange& range)
{
    if (!onDidIMEInput_) {
        return;
    }
    auto callback = onDidIMEInput_;
    callback(range);
}

void RichEditorEventHub::SetAboutToDelete(std::function<bool(const RichEditorDeleteValue&)>&& func)
{
    aboutToDelete_ = std::move(func);
}

bool RichEditorEventHub::FireAboutToDelete(const RichEditorDeleteValue& info)
{
    if (!aboutToDelete_) {
        return true;
    }
    auto callback = aboutToDelete_;
    return callback(info);
}

void RichEditorEventHub::SetOnDeleteComplete(std::function<void()>&& func)
{
    onDeleteComplete_ = std::move(func);
}
void RichEditorEventHub::FireOnDeleteComplete()
{
    if (!onDeleteComplete_) {
        return;
    }
    auto callback = onDeleteComplete_;
    callback();
#ifndef CROSS_PLATFORM
    UiSessionManager::GetInstance()->ReportComponentChangeEvent("event", "RichEditor.onDeleteComplete",
        ComponentEventType::COMPONENT_EVENT_TEXT_INPUT);
#endif
}

std::string RichEditorEventHub::GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType type)
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, extraInfo);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(host, extraInfo);

    auto json = JsonUtil::Create(true);
    if (type == DragEventType::DROP && timestamp_ != 0 && pattern->GetTimestamp() == timestamp_) {
        json->Put("isInComponent", true);
        timestamp_ = 0;
    }
    if (!extraInfo.empty()) {
        json->Put("extraInfo", extraInfo.c_str());
    }
    return json->ToString();
}

void RichEditorEventHub::SetOnEditingChange(std::function<void(const bool&)>&& func)
{
    onEditingChange_ = std::move(func);
}
 
void RichEditorEventHub::FireOnEditingChange(bool isEditing)
{
    if (!onEditingChange_) {
        return;
    }
    auto callback = onEditingChange_;
    callback(isEditing);
}

void RichEditorEventHub::SetOnWillChange(std::function<bool(const RichEditorChangeValue&)>&& func)
{
    onWillChange_ = std::move(func);
}

bool RichEditorEventHub::FireOnWillChange(const RichEditorChangeValue& info)
{
    if (!onWillChange_) {
        return true;
    }
    auto callback = onWillChange_;
    return callback(info);
}

bool RichEditorEventHub::HasOnWillChange() const
{
    return static_cast<bool>(onWillChange_);
}

void RichEditorEventHub::SetOnDidChange(std::function<void(const RichEditorChangeValue&)>&& func)
{
    onDidChange_ = std::move(func);
}

void RichEditorEventHub::FireOnDidChange(const RichEditorChangeValue& changeValue)
{
    if (!onDidChange_) {
        return;
    }
    auto callback = onDidChange_;
    callback(changeValue);
}

bool RichEditorEventHub::HasOnDidChange() const
{
    auto host = GetFrameNode();
    CHECK_NULL_RETURN(host, false);
    auto pattern = host->GetPattern<RichEditorPattern>();
    CHECK_NULL_RETURN(pattern, false);
    pattern->SetContentChange(true);
    return static_cast<bool>(onDidChange_);
}

void RichEditorEventHub::SetOnCut(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onCut_ = std::move(func);
}

void RichEditorEventHub::FireOnCut(NG::TextCommonEvent& value)
{
    if (!onCut_) {
        return;
    }
    auto callback = onCut_;
    callback(value);
}

void RichEditorEventHub::SetOnCopy(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onCopy_ = std::move(func);
}

void RichEditorEventHub::FireOnCopy(NG::TextCommonEvent& value)
{
    if (!onCopy_) {
        return;
    }
    auto callback = onCopy_;
    callback(value);
}

void RichEditorEventHub::SetOnShare(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onShare_ = std::move(func);
}

void RichEditorEventHub::FireOnShare(NG::TextCommonEvent& value)
{
    if (!onShare_) {
        return;
    }
    auto callback = onShare_;
    callback(value);
}

void RichEditorEventHub::SetOnStyledStringWillChange(std::function<bool(const StyledStringChangeValue&)>&& func)
{
    onStyledStringWillChange_ = std::move(func);
}

bool RichEditorEventHub::FireOnStyledStringWillChange(const StyledStringChangeValue& info)
{
    if (!onStyledStringWillChange_) {
        return true;
    }
    auto callback = onStyledStringWillChange_;
    return callback(info);
}

bool RichEditorEventHub::HasOnStyledStringWillChange() const
{
    return static_cast<bool>(onStyledStringWillChange_);
}

void RichEditorEventHub::SetOnStyledStringDidChange(std::function<void(const StyledStringChangeValue&)>&& func)
{
    onStyledStringDidChange_ = std::move(func);
}

void RichEditorEventHub::FireOnStyledStringDidChange(const StyledStringChangeValue& info)
{
    if (!onStyledStringDidChange_) {
        return;
    }
    auto callback = onStyledStringDidChange_;
    callback(info);
}

bool RichEditorEventHub::HasOnStyledStringDidChange() const
{
    return static_cast<bool>(onStyledStringDidChange_);
}

void TextInsertValueInfo::SetSpanIndex(int32_t spanIndex)
{
    spanIndex_ = spanIndex;
}

int32_t TextInsertValueInfo::GetSpanIndex() const
{
    return spanIndex_;
}

void TextInsertValueInfo::SetOffsetInSpan(int32_t offsetInSpan)
{
    offsetInSpan_ = offsetInSpan;
}

int32_t TextInsertValueInfo::GetOffsetInSpan() const
{
    return offsetInSpan_;
}

std::string TextInsertValueInfo::ToString() const
{
    return "spanIndex_: " + std::to_string(spanIndex_) + ", offsetInSpan_" + std::to_string(offsetInSpan_);
}

void RichEditorEventHub::SetOnSelect(std::function<void(const BaseEventInfo*)>&& func)
{
    onSelect_ = std::move(func);
}

void RichEditorEventHub::FireOnSelect(BaseEventInfo* value)
{
    if (!onSelect_) {
        return;
    }
    auto callback = onSelect_;
    callback(value);
}

void RichEditorEventHub::SetOnSelectionChange(std::function<void(const BaseEventInfo*)>&& func)
{
    OnSelectionChange_ = std::move(func);
}

void RichEditorEventHub::FireOnSelectionChange(BaseEventInfo* value)
{
    if (!OnSelectionChange_) {
        return;
    }
    auto callback = OnSelectionChange_;
    callback(value);
}

void RichEditorEventHub::SetTimestamp(long long timestamp)
{
    timestamp_ = timestamp;
}

void RichEditorEventHub::SetOnPaste(std::function<void(NG::TextCommonEvent&)>&& func)
{
    onPaste_ = std::move(func);
}

void RichEditorEventHub::FireOnPaste(NG::TextCommonEvent& value)
{
    if (!onPaste_) {
        return;
    }
    auto callback = onPaste_;
    callback(value);
}

void RichEditorEventHub::SetOnSubmit(std::function<void(int32_t, NG::TextFieldCommonEvent&)>&& func)
{
    onSubmit_ = std::move(func);
}

void RichEditorEventHub::FireOnSubmit(int32_t value, NG::TextFieldCommonEvent& event)
{
    if (!onSubmit_) {
        return;
    }
    auto callback = onSubmit_;
    callback(value, event);
}

void RichEditorEventHub::SetOnWillAttachIME(IMEAttachCallback&& func)
{
    onWillAttachIME_ = std::move(func);
}

void RichEditorEventHub::FireOnWillAttachIME(IMEClient& info)
{
    if (!onWillAttachIME_) {
        return;
    }
    auto callback = onWillAttachIME_;
    callback(info);
}

RefPtr<GestureEventHub> RichEditorEventHub::CreateGestureEventHub()
{
    return MakeRefPtr<RichEditorGestureEventHub>(WeakClaim(this));
}

void RichEditorChangeValue::reset()
{
    originalSpans_.clear();
    replacedSpans_.clear();
    replacedImageSpans_.clear();
    replacedSymbolSpans_.clear();
    rangeBefore_ = TextRange();
    rangeAfter_ = TextRange();
    changeReason_ = TextChangeReason::UNKNOWN;
}
} // namespace OHOS::Ace::NG
