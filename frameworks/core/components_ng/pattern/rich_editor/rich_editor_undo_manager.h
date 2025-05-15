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
enum class SpanOptionsType { TEXT = 0, IMAGE, SYMBOL, BUILDER };

struct UndoRedoRecord {
    TextRange rangeBefore;
    TextRange rangeAfter;
    RefPtr<SpanString> styledStringBefore;
    RefPtr<SpanString> styledStringAfter;
    std::optional<OptionsList> optionsListBefore;
    std::optional<OptionsList> optionsListAfter;
    TextRange selectionBefore;
    CaretAffinityPolicy caretAffinityBefore = CaretAffinityPolicy::DEFAULT;
    bool isOnlyStyleChange = false;
    std::unordered_set<SpanType> updateSpanTypes;

    void SetOperationBefore(TextRange range, const RefPtr<SpanString>& styledString, TextRange selection,
        CaretAffinityPolicy caretAffinity)
    {
        rangeBefore = range;
        styledStringBefore = styledString;
        selectionBefore = selection;
        caretAffinityBefore = caretAffinity;
    }

    void SetOperationBefore(TextRange range, const OptionsList& optionsList, TextRange selection,
        CaretAffinityPolicy caretAffinity)
    {
        rangeBefore = range;
        optionsListBefore = optionsList;
        selectionBefore = selection;
        caretAffinityBefore = caretAffinity;
    }

    void SetOperationAfter(TextRange range, const RefPtr<SpanString>& styledString)
    {
        rangeAfter = range;
        styledStringAfter = styledString;
    }

    void SetOperationAfter(TextRange range, const OptionsList& optionsList)
    {
        rangeAfter = range;
        optionsListAfter = optionsList;
    }

    void CopyOperationAfter(const UndoRedoRecord& record)
    {
        rangeAfter = record.rangeAfter;
        styledStringAfter = record.styledStringAfter;
        optionsListAfter = record.optionsListAfter;
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
        optionsListBefore = std::nullopt;
        optionsListAfter = std::nullopt;
        selectionBefore.Reset();
        caretAffinityBefore = CaretAffinityPolicy::DEFAULT;
        isOnlyStyleChange = false;
        updateSpanTypes.clear();
    }

    void Reverse()
    {
        std::swap(rangeBefore, rangeAfter);
        std::swap(styledStringBefore, styledStringAfter);
        std::swap(optionsListBefore, optionsListAfter);
    }

    bool IsBeforeStateValid() const
    {
        return rangeBefore.IsValid() && (styledStringBefore || optionsListBefore);
    }
    
    bool IsAfterStateValid() const
    {
        return rangeAfter.IsValid() && (styledStringAfter || optionsListAfter);
    }
    
    bool IsValid() const
    {
        return IsBeforeStateValid() && IsAfterStateValid();
    }

    bool IsEmpty() const
    {
        return rangeBefore.GetLength() == 0 && rangeAfter.GetLength() == 0;
    }

    std::string ToString() const
    {
        auto jsonValue = JsonUtil::Create(true);
        JSON_STRING_PUT_STRINGABLE(jsonValue, rangeBefore);
        JSON_STRING_PUT_STRINGABLE(jsonValue, rangeAfter);
        JSON_STRING_PUT_STRINGABLE(jsonValue, selectionBefore);
        JSON_STRING_PUT_INT(jsonValue, caretAffinityBefore);
        JSON_STRING_PUT_BOOL(jsonValue, isOnlyStyleChange);
        return jsonValue->ToString();
    }
};

class RichEditorUndoManager {
public:
    RichEditorUndoManager(const WeakPtr<RichEditorPattern>& pattern): pattern_(pattern) {}
    virtual ~RichEditorUndoManager() = default;
    virtual bool IsStyledUndoRedoSupported() = 0;
    virtual bool BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) = 0;
    virtual void AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) = 0;
    virtual void ApplyOperationToRecord(int32_t start, int32_t length, const std::u16string& string,
        UndoRedoRecord& record) {}
    virtual void ApplyOperationToRecord(int32_t start, int32_t length, const RefPtr<SpanString>& styledString,
        UndoRedoRecord& record) {}
    virtual void RecordAddSpanOperation(const RefPtr<SpanItem>& item, SpanOptionsType type) {}
    virtual void SetOperationBefore(TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity,
        UndoRedoRecord& record) = 0;
    virtual void UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record) = 0;

    static std::unique_ptr<RichEditorUndoManager> Create(bool isSpanStringMode,
        const WeakPtr<RichEditorPattern>& pattern);
    void UndoByRecords();
    void RedoByRecords();
    void RecordSelectionBefore();
    void RecordSelectionBefore(TextRange selection);
    void UpdateRecordBeforeChange(
        int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange = false);
    void RecordOperation(const UndoRedoRecord& record, bool isFromRedo = false);
    void RecordPreviewInputtingStart(int32_t start, int32_t length);
    bool RecordPreviewInputtingEnd(const UndoRedoRecord& record);
    void RecordInsertOperation(const UndoRedoRecord& record);
    void RecordOperationAfterChange(int32_t start, int32_t length, UndoRedoRecord& record);
    void ClearSelectionBefore()
    {
        selectionBefore_.Reset();
    }

    void ClearPreviewInputRecord()
    {
        if (IsPreviewInputStartWithSelection()) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "ClearPreviewInputRecord");
        }
        previewInputRecord_.Reset();
    }

    void ClearUndoRedoRecords()
    {
        undoRecords_.clear();
        redoRecords_.clear();
        ClearPreviewInputRecord();
        ClearSelectionBefore();
    }

protected:
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
    // used to record selection or caret position at the start of a multi-step operation
    TextRange selectionBefore_;
    size_t recordCount_ = 0;
    bool isCountingRecord_ = false;
};

class StyledStringUndoManager : public RichEditorUndoManager {
public:
    StyledStringUndoManager(const WeakPtr<RichEditorPattern>& pattern): RichEditorUndoManager(pattern) {}
    bool IsStyledUndoRedoSupported() override;
    bool BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) override;
    void AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) override;
    void ApplyOperationToRecord(int32_t start, int32_t length, const std::u16string& string,
        UndoRedoRecord& record) override;
    void ApplyOperationToRecord(int32_t start, int32_t length, const RefPtr<SpanString>& styledString,
        UndoRedoRecord& record) override;
    void SetOperationBefore(TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity,
        UndoRedoRecord& record) override;
    void UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record) override;
};

class SpansUndoManager : public RichEditorUndoManager {
public:
    SpansUndoManager(const WeakPtr<RichEditorPattern>& pattern): RichEditorUndoManager(pattern) {}
    bool IsStyledUndoRedoSupported() override;
    bool BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) override;
    void AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo = false) override;
    void RecordAddSpanOperation(const RefPtr<SpanItem>& item, SpanOptionsType type) override;
    void SetOperationBefore(TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity,
        UndoRedoRecord& record) override;
    void UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record) override;
private:
    OptionsList CreateOptionsListByRange(TextRange range);
    SpanOptions CreateSpanOptionsBySpanObject(const ResultObject& object);
    TextSpanOptions CreateTextSpanOptions(const ResultObject& object);
    TextSpanOptions CreateTextSpanOptions(const RefPtr<SpanItem>& item);
    ImageSpanOptions CreateImageSpanOptions(const ResultObject& object);
    ImageSpanOptions CreateImageSpanOptions(const RefPtr<ImageSpanItem>& item);
    SymbolSpanOptions CreateSymbolSpanOptions(const ResultObject& object);
    SymbolSpanOptions CreateSymbolSpanOptions(const RefPtr<SpanItem>& item);
    BuilderSpanOptions CreateBuilderSpanOptions(const ResultObject& object);
    BuilderSpanOptions CreateBuilderSpanOptions(const RefPtr<PlaceholderSpanItem>& item);
};
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_UNDO_MANAGER_H