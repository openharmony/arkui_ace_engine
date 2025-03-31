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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UNDO_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UNDO_MANAGER_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace OHOS::Ace::NG {
struct UndoRedoRecord {
    TextRange rangeBefore;
    TextRange rangeAfter;
    RefPtr<SpanString> styledStringBefore;
    RefPtr<SpanString> styledStringAfter;
    TextRange selectionBefore;
    bool isOnlyStyleChange = false;
    std::unordered_set<SpanType> updateSpanTypes;

    void SetOperationBefore(TextRange range, const RefPtr<SpanString>& styledString, TextRange selection)
    {
        rangeBefore = range;
        styledStringBefore = styledString;
        selectionBefore = selection;
    }

    void SetOperationAfter(TextRange range, const RefPtr<SpanString>& styledString)
    {
        rangeAfter = range;
        styledStringAfter = styledString;
    }

    void AddUpdateSpanType(SpanType type)
    {
        updateSpanTypes.insert(type);
    }

    void Reset()
    {
        rangeBefore.Reset();
        rangeAfter.Reset();
        styledStringBefore = nullptr;
        styledStringAfter = nullptr;
        selectionBefore.Reset();
        isOnlyStyleChange = false;
        updateSpanTypes.clear();
    }

    void Reverse()
    {
        std::swap(rangeBefore, rangeAfter);
        std::swap(styledStringBefore, styledStringAfter);
    }

    bool IsBeforeStateValid() const
    {
        return rangeBefore.IsValid() && styledStringBefore;
    }
    
    bool IsAfterStateValid() const
    {
        return rangeAfter.IsValid() && styledStringAfter;
    }
    
    bool IsValid() const
    {
        return IsBeforeStateValid() && IsAfterStateValid();
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_STRINGABLE(jsonValue, rangeBefore);
        JSON_STRING_PUT_STRINGABLE(jsonValue, rangeAfter);
        JSON_STRING_PUT_STRINGABLE(jsonValue, selectionBefore);
        JSON_STRING_PUT_BOOL(jsonValue, isOnlyStyleChange);
        return jsonValue->ToString();
    }
};

class RichEditorUndoManager {
public:
    RichEditorUndoManager(const WeakPtr<RichEditorPattern>& pattern): pattern_(pattern) {}
    void UndoByRecords();
    void RedoByRecords();
    void ApplyOperationToRecord(int32_t start, int32_t length, const std::u16string& string,
        UndoRedoRecord& record);
    void ApplyOperationToRecord(int32_t start, int32_t length, const RefPtr<SpanString>& styledString,
        UndoRedoRecord& record);
    void UpdateRecordBeforeChange(
        int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange = false);
    void UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record);
    void RecordOperation(const UndoRedoRecord& record, bool isFromRedo = false);
    void RecordPreviewInputtingStart(int32_t start, int32_t length);
    bool RecordPreviewInputtingEnd(const UndoRedoRecord& record);
    void RecordInsertOperation(const UndoRedoRecord& record);
    void ClearUndoRedoRecords()
    {
        undoRecords_.clear();
        redoRecords_.clear();
        previewInputRecord_.Reset();
    }

private:
    void RecordOperation(const UndoRedoRecord& record, size_t index);
    void RecordUndoOperation(const UndoRedoRecord& record);
    bool IsPreviewInputStartWithSelection()
    {
        return previewInputRecord_.IsBeforeStateValid();
    }

    void StartCountingRecord()
    {
        CHECK_NULL_VOID(!isCountingRecord_);
        recordCount_ = 0;
        isCountingRecord_ = true;
    }

    void CountRecord()
    {
        CHECK_NULL_VOID(isCountingRecord_);
        recordCount_ ++;
    }

    size_t EndCountingRecord()
    {
        CHECK_NULL_RETURN(isCountingRecord_, 0);
        isCountingRecord_ = false;
        return recordCount_;
    }

    WeakPtr<RichEditorPattern> pattern_;
    std::deque<UndoRedoRecord> undoRecords_;
    std::deque<UndoRedoRecord> redoRecords_;
    UndoRedoRecord previewInputRecord_;
    size_t recordCount_ = 0;
    bool isCountingRecord_ = false;
};
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UNDO_MANAGER_H