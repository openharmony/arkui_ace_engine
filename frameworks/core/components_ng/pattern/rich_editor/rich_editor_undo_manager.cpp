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
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    CHECK_NULL_VOID(!pattern->IsPreviewTextInputting());
    auto record = undoRecords_.back();
    auto sizeBefore = undoRecords_.size();
    auto recordIndex = sizeBefore - 1;
    undoRecords_.pop_back();
    StartCountingRecord();
    bool isPreventChange = !BeforeChangeByRecord(record, true);
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
    ExecuteUndo(record);
    RecordUndoOperation(record);
    AfterChangeByRecord(record, true);
}

void RichEditorUndoManager::RedoByRecords()
{
    CHECK_NULL_VOID(!redoRecords_.empty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    CHECK_NULL_VOID(!pattern->IsPreviewTextInputting());
    auto record = redoRecords_.back();
    redoRecords_.pop_back();
    CHECK_NULL_VOID(BeforeChangeByRecord(record));
    ExecuteRedo(record);
    RecordOperation(record, true);
    AfterChangeByRecord(record);
}

void RichEditorUndoManager::RecordSelectionBefore()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    auto caretPosition = pattern->caretPosition_;
    auto& textSelector = pattern->textSelector_;
    selectionBefore_ = textSelector.SelectNothing() ? TextRange{ caretPosition, caretPosition }
        : TextRange{ textSelector.GetStart(), textSelector.GetEnd() };
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RecordSelectionBefore:%{public}s", selectionBefore_.ToString().c_str());
}

void RichEditorUndoManager::UpdateRecordBeforeChange(
    int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    record.isOnlyStyleChange = isOnlyStyleChange;
    auto rangeBefore = TextRange{ start, start + length };
    auto caretAffinityBefore = pattern->caretAffinityPolicy_;
    if (selectionBefore_.IsValid()) {
        SetOperationBefore(rangeBefore, selectionBefore_, caretAffinityBefore, record);
        ClearSelectionBefore();
        return;
    }
    auto caretPosition = pattern->caretPosition_;
    auto& textSelector = pattern->textSelector_;
    auto selection = textSelector.SelectNothing() ? TextRange{ caretPosition, caretPosition }
        : TextRange{ textSelector.GetStart(), textSelector.GetEnd() };
    SetOperationBefore(rangeBefore, selection, caretAffinityBefore, record);
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
    ClearPreviewInputRecord();
    CHECK_NULL_VOID(length > 0);
    UpdateRecordBeforeChange(start, length, previewInputRecord_);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "PreviewInputtingStart [%{public}s]", previewInputRecord_.ToString().c_str());
}

bool RichEditorUndoManager::RecordPreviewInputtingEnd(const UndoRedoRecord& record)
{
    CHECK_NULL_RETURN(IsPreviewInputStartWithSelection(), false);
    previewInputRecord_.CopyOperationAfter(record);
    CHECK_NULL_RETURN(previewInputRecord_.IsValid(), false);
    RecordOperation(previewInputRecord_);
    ClearPreviewInputRecord();
    return true;
}

void RichEditorUndoManager::RecordInsertOperation(const UndoRedoRecord& record)
{
    // Record insert operation by initial state from preview input start
    CHECK_NULL_VOID(!RecordPreviewInputtingEnd(record));
    RecordOperation(record);
    ClearPreviewInputRecord();
}

bool StyledStringUndoManager::IsStyledUndoRedoSupported()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsStyledStringModeEnabled();
}

bool StyledStringUndoManager::BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->BeforeStyledStringChange(record, isUndo);
}

void StyledStringUndoManager::AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->AfterStyledStringChange(record, isUndo);
}

void StyledStringUndoManager::ExecuteUndo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->HandleUndoInStyledString(record);
}

void StyledStringUndoManager::ExecuteRedo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->HandleRedoInStyledString(record);
}

void StyledStringUndoManager::ApplyOperationToRecord(
    int32_t start, int32_t length, const std::u16string& string, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto styledString = pattern->CreateStyledStringByStyleBefore(start, string);
    ApplyOperationToRecord(start, length, styledString, record);
}

void StyledStringUndoManager::ApplyOperationToRecord(
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

void StyledStringUndoManager::SetOperationBefore(
    TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto styledStringBefore = pattern->GetStyledString()->GetSubSpanString(range.start, range.GetLength());
    record.SetOperationBefore(range, styledStringBefore, selection, caretAffinity);
}

void StyledStringUndoManager::UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto styledString = pattern->GetStyledString()->GetSubSpanString(start, length);
    CHECK_NULL_VOID(styledString);
    auto rangeAfter = TextRange{ start, start + length };
    record.SetOperationAfter(rangeAfter, styledString);
}
}