/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

namespace OHOS::Ace::NG {
constexpr uint32_t RECORD_MAX_LENGTH = 20;

void RichEditorUndoManager::UndoByRecords()
{
    CHECK_NULL_VOID(!undoRecords_.empty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    CHECK_NULL_VOID(!pattern->IsPreviewTextInputting());
    auto record = undoRecords_.back();
    auto sizeBefore = undoRecords_.size();
    auto recordIndex = sizeBefore - 1;
    undoRecords_.pop_back();
    StartCountingRecord();
    bool isPreventChange = !pattern->BeforeStyledStringChange(record, true);
    auto recordCount = EndCountingRecord();
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "UndoByRecord [%{public}s] isPreventChange=%{public}d",
        record.ToString().c_str(), isPreventChange);
    if (isPreventChange) {
        // if prevevent change need put the record back
        CHECK_NULL_VOID(recordCount < RECORD_MAX_LENGTH);
        auto sizeAfter = sizeBefore + recordCount;
        size_t moveLength = (sizeAfter > RECORD_MAX_LENGTH) ? sizeAfter - RECORD_MAX_LENGTH : 0;
        IF_TRUE(moveLength <= recordIndex, RecordOperation(record, recordIndex - moveLength));
        return;
    }
    pattern->HandleUndoInStyledString(record);
    RecordUndoOperation(record);
    pattern->AfterStyledStringChange(record, true);
}

void RichEditorUndoManager::RedoByRecords()
{
    CHECK_NULL_VOID(!redoRecords_.empty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    CHECK_NULL_VOID(!pattern->IsPreviewTextInputting());
    auto record = redoRecords_.back();
    redoRecords_.pop_back();
    CHECK_NULL_VOID(pattern->BeforeStyledStringChange(record));
    pattern->HandleRedoInStyledString(record);
    RecordOperation(record, true);
    pattern->AfterStyledStringChange(record);
}

void RichEditorUndoManager::ApplyOperationToRecord(
    int32_t start, int32_t length, const std::u16string& string, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto styledString = pattern->CreateStyledStringByStyleBefore(start, string);
    ApplyOperationToRecord(start, length, styledString, record);
}

void RichEditorUndoManager::ApplyOperationToRecord(
    int32_t start, int32_t length, const RefPtr<SpanString>& styledString, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    UpdateRecordBeforeChange(start, length, record);
    CHECK_NULL_VOID(styledString);
    auto stringLength = styledString->GetLength();
    auto rangeAfter = TextRange{ start, start + stringLength };
    record.SetOperationAfter(rangeAfter, styledString);
}

void RichEditorUndoManager::UpdateRecordBeforeChange(
    int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto rangeBefore = TextRange{ start, start + length };
    auto styledStringBefore = pattern->styledString_->GetSubSpanString(start, length);
    auto caretPosition = pattern->caretPosition_;
    auto& textSelector = pattern->textSelector_;
    auto selection = textSelector.SelectNothing() ? TextRange{ caretPosition, caretPosition }
        : TextRange{ textSelector.GetStart(), textSelector.GetEnd() };
    record.SetOperationBefore(rangeBefore, styledStringBefore, selection);
    record.isOnlyStyleChange = isOnlyStyleChange;
}

void RichEditorUndoManager::UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto styledString = pattern->styledString_->GetSubSpanString(start, length);
    CHECK_NULL_VOID(styledString);
    auto rangeAfter = TextRange{ start, start + length };
    record.SetOperationAfter(rangeAfter, styledString);
}

void RichEditorUndoManager::RecordOperation(const UndoRedoRecord& record, size_t index)
{
    CHECK_NULL_VOID(record.IsValid());
    CHECK_NULL_VOID(index <= undoRecords_.size());
    undoRecords_.insert(undoRecords_.begin() + index, record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RecordOperation [%{public}s] in %{public}zu",
        record.ToString().c_str(), index);
    if (undoRecords_.size() >= RECORD_MAX_LENGTH) {
        undoRecords_.pop_front();
    }
}

void RichEditorUndoManager::RecordOperation(const UndoRedoRecord& record, bool isFromRedo)
{
    CHECK_NULL_VOID(record.IsValid());
    if (undoRecords_.size() >= RECORD_MAX_LENGTH) {
        undoRecords_.pop_front();
    }
    undoRecords_.push_back(record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RecordOperation [%{public}s]", record.ToString().c_str());
    CountRecord();
    IF_TRUE(!isFromRedo, redoRecords_.clear());
}

void RichEditorUndoManager::RecordUndoOperation(const UndoRedoRecord& record)
{
    CHECK_NULL_VOID(record.IsValid());
    if (redoRecords_.size() >= RECORD_MAX_LENGTH) {
        redoRecords_.erase(redoRecords_.begin());
    }
    redoRecords_.push_back(record);
}

// Records initial state when preview input start with selection
void RichEditorUndoManager::RecordPreviewInputtingStart(int32_t start, int32_t length)
{
    previewInputRecord_.Reset();
    UpdateRecordBeforeChange(start, length, previewInputRecord_);
}

bool RichEditorUndoManager::RecordPreviewInputtingEnd(const UndoRedoRecord& record)
{
    CHECK_NULL_RETURN(IsPreviewInputStartWithSelection(), false);
    auto start = record.rangeAfter.start;
    auto styledString = record.styledStringAfter;
    CHECK_NULL_RETURN(styledString, false);
    auto stringLength = styledString->GetLength();
    auto rangeAfter = TextRange{ start, start + stringLength };
    previewInputRecord_.SetOperationAfter(rangeAfter, styledString);
    CHECK_NULL_RETURN(previewInputRecord_.IsValid(), false);
    RecordOperation(previewInputRecord_);
    return true;
}

void RichEditorUndoManager::RecordInsertOperation(const UndoRedoRecord& record)
{
    // Record insert operation by initial state from preview input start
    CHECK_NULL_VOID(!RecordPreviewInputtingEnd(record));
    RecordOperation(record);
    previewInputRecord_.Reset();
}
}