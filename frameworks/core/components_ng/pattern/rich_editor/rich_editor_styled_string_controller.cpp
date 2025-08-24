/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_styled_string_controller.h"

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
namespace OHOS::Ace::NG {
void RichEditorStyledStringController::SetStyledString(const RefPtr<SpanStringBase>& value)
{
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        auto spanString = AceType::DynamicCast<SpanString>(value);
        if (spanString) {
            richEditorPattern->SetStyledString(spanString);
        }
    }
}

RefPtr<SpanStringBase> RichEditorStyledStringController::GetStyledString()
{
    auto richEditorPattern = pattern_.Upgrade();
    auto mutableSpanString = AceType::MakeRefPtr<MutableSpanString>(u"");
    CHECK_NULL_RETURN(richEditorPattern, mutableSpanString);
    auto styledString = richEditorPattern->GetStyledString();
    CHECK_NULL_RETURN(styledString, mutableSpanString);
    auto length = styledString->GetLength();
    auto spanString = styledString->GetSubSpanString(0, length);
    mutableSpanString->AppendSpanString(spanString);
    return mutableSpanString;
}

SelectionRangeInfo RichEditorStyledStringController::GetSelection()
{
    SelectionRangeInfo value(0, 0);
    auto richEditorPattern = pattern_.Upgrade();
    if (richEditorPattern) {
        auto start = std::max(richEditorPattern->GetTextSelector().GetTextStart(), 0);
        auto end = std::max(richEditorPattern->GetTextSelector().GetTextEnd(), 0);
        if (start == end) {
            start = richEditorPattern->GetCaretPosition();
            end = richEditorPattern->GetCaretPosition();
        }
        value = SelectionRangeInfo(start, end);
    }
    return value;
}

void RichEditorStyledStringController::SetOnWillChange(std::function<bool(const StyledStringChangeValue&)> && func)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStyledStringWillChange(std::move(func));
}

void RichEditorStyledStringController::SetOnDidChange(std::function<void(const StyledStringChangeValue&)> && func)
{
    auto richEditorPattern = pattern_.Upgrade();
    CHECK_NULL_VOID(richEditorPattern);
    auto eventHub = richEditorPattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnStyledStringDidChange(std::move(func));
}
}