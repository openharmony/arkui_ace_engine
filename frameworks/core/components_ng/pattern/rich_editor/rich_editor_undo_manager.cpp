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

std::unique_ptr<RichEditorUndoManager> RichEditorUndoManager::Create(
    bool isSpanStringMode, const WeakPtr<RichEditorPattern>& pattern)
{
    if (isSpanStringMode) {
        return std::make_unique<StyledStringUndoManager>(pattern);
    }
    return std::make_unique<SpansUndoManager>(pattern);
}

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
    bool isPreventChange = !record.isOnlyStyleChange && !BeforeChangeByRecord(record, true);
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
    pattern->ProcessStyledUndo(record);
    RecordUndoOperation(record);
    IF_TRUE(!record.isOnlyStyleChange, AfterChangeByRecord(record, true));
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
    bool isPreventChange = !record.isOnlyStyleChange && !BeforeChangeByRecord(record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RedoByRecords [%{public}s] isPreventChange=%{public}d",
        record.ToString().c_str(), isPreventChange);
    CHECK_NULL_VOID(!isPreventChange);
    pattern->ProcessStyledRedo(record);
    RecordOperation(record, true);
    IF_TRUE(!record.isOnlyStyleChange, AfterChangeByRecord(record));
}

void RichEditorUndoManager::RecordSelectionBefore()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    auto caretPosition = pattern->caretPosition_;
    auto& textSelector = pattern->textSelector_;
    auto selection = textSelector.SelectNothing() ? TextRange{ caretPosition, caretPosition }
        : TextRange{ textSelector.GetStart(), textSelector.GetEnd() };
    RecordSelectionBefore(selection);
}

void RichEditorUndoManager::RecordSelectionBefore(TextRange selection)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    selectionBefore_ = selection;
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RecordSelectionBefore:%{public}s", selectionBefore_.ToString().c_str());
}

void RichEditorUndoManager::UpdateRecordBeforeChange(
    int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsStyledUndoRedoSupported());
    record.isOnlyStyleChange = isOnlyStyleChange;
    auto end = std::min(start + length, pattern->GetTextContentLength());
    auto rangeBefore = TextRange{ start, end };
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
    CHECK_NULL_VOID(record.IsValid() && !record.IsEmpty());
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
    CHECK_NULL_VOID(record.IsValid() && !record.IsEmpty());
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

void RichEditorUndoManager::RecordOperationAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    UpdateRecordAfterChange(start, length, record);
    RecordOperation(record);
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
    auto end = std::min(start + length, pattern->GetTextContentLength());
    auto rangeAfter = TextRange{ start, end };
    record.SetOperationAfter(rangeAfter, styledString);
}

bool SpansUndoManager::IsStyledUndoRedoSupported()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSupportStyledUndo();
}

bool SpansUndoManager::BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_RETURN(!record.isOnlyStyleChange, true);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->BeforeSpansChange(record, isUndo);
}

void SpansUndoManager::RemoveBuilderSpanOptions(const RefPtr<NG::UINode> customNode)
{
    CHECK_NULL_VOID(customNode);
    RemoveBuilderSpanOptions(undoRecords_, customNode);
    RemoveBuilderSpanOptions(redoRecords_, customNode);
}

void SpansUndoManager::RemoveBuilderSpanOptions(std::deque<UndoRedoRecord>& records,
    const RefPtr<NG::UINode> customNode)
{
    CHECK_NULL_VOID(customNode);
    for (auto& record : records) {
        CHECK_NULL_CONTINUE(record.IsRestoreBuilderSpan());
        IF_TRUE(record.optionsListBefore.has_value(),
            RemoveBuilderSpanOptions(record.optionsListBefore.value(), customNode));
        IF_TRUE(record.optionsListAfter.has_value(),
            RemoveBuilderSpanOptions(record.optionsListAfter.value(), customNode));
    }
}

void SpansUndoManager::RemoveBuilderSpanOptions(OptionsList& optionsList, const RefPtr<NG::UINode> customNode)
{
    CHECK_NULL_VOID(customNode);
    for (auto& option : optionsList) {
        if (const auto* builderOpt = std::get_if<BuilderSpanOptions>(&option)) {
            bool needRemove = builderOpt->customNode && builderOpt->customNode == customNode;
            IF_TRUE(needRemove, (option = TextSpanOptions{ .offset = builderOpt->offset, .value = u" " }));
        }
    }
}

void SpansUndoManager::AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->AfterSpansChange(record, isUndo);
}

void SpansUndoManager::RecordAddSpanOperation(const RefPtr<SpanItem>& item, SpanOptionsType type)
{
    CHECK_NULL_VOID(item);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && pattern->IsSupportStyledUndo());
    auto start = item->rangeStart;
    UndoRedoRecord record;
    UpdateRecordBeforeChange(start, 0, record);
    int32_t length = static_cast<int32_t>(item->content.length());
    SpanOptions options;
    switch (type) {
        case SpanOptionsType::TEXT: {
            options = CreateTextSpanOptions(item);
            break;
        }
        case SpanOptionsType::IMAGE: {
            options = CreateImageSpanOptions(AceType::DynamicCast<ImageSpanItem>(item));
            break;
        }
        case SpanOptionsType::SYMBOL: {
            options = CreateSymbolSpanOptions(item);
            break;
        }
        case SpanOptionsType::BUILDER: {
            options = CreateBuilderSpanOptions(AceType::DynamicCast<PlaceholderSpanItem>(item));
            break;
        }
        default:
            break;
    }
    record.SetOperationAfter(TextRange{ start, start + length }, OptionsList{ options });
    RecordOperation(record);
}

void SpansUndoManager::SetOperationBefore(
    TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && pattern->IsSupportStyledUndo());
    record.SetOperationBefore(range, CreateOptionsListByRange(range), selection, caretAffinity);
}

void SpansUndoManager::UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && pattern->IsSupportStyledUndo());
    auto end = std::min(start + length, pattern->GetTextContentLength());
    auto rangeAfter = TextRange{ start, end };
    record.SetOperationAfter(rangeAfter, CreateOptionsListByRange(rangeAfter));
}

OptionsList SpansUndoManager::CreateOptionsListByRange(TextRange range)
{
    OptionsList optionsList;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, optionsList);
    CHECK_NULL_RETURN(range.GetLength() != 0, optionsList);
    auto spansInfo = pattern->GetSpansInfoByRange(range.start, range.end);
    auto& resultObjects = spansInfo.GetSelectionRef().resultObjects;
    for (const ResultObject& spanObject : resultObjects) {
        optionsList.push_back(CreateSpanOptionsBySpanObject(spanObject));
    }
    return optionsList;
}

SpanOptions SpansUndoManager::CreateSpanOptionsBySpanObject(const ResultObject& object)
{
    auto type = object.type;
    if (type == SelectSpanType::TYPEIMAGE && object.valueString == u" " && object.valuePixelMap == nullptr) {
        type = SelectSpanType::TYPEBUILDERSPAN;
    }
    switch (type) {
        case SelectSpanType::TYPESPAN:
            return CreateTextSpanOptions(object);
        case SelectSpanType::TYPEIMAGE:
            return CreateImageSpanOptions(object);
        case SelectSpanType::TYPESYMBOLSPAN:
            return CreateSymbolSpanOptions(object);
        case SelectSpanType::TYPEBUILDERSPAN:
            return CreateBuilderSpanOptions(object);
        default:
            break;
    }
    TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "CreateSpanOptions: Unhandled span type");
    return TextSpanOptions{};
}

TextSpanOptions SpansUndoManager::CreateTextSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    CHECK_NULL_RETURN(pattern, {});
    auto options = pattern->GetTextSpanOptions(spanItem);
    auto offsetInSpanStart = object.offsetInSpan[0];
    auto offsetInSpanEnd = object.offsetInSpan[1];
    auto spanStart = object.spanPosition.spanRange[0];
    options.offset = spanStart + offsetInSpanStart;
    options.value = object.valueString.substr(offsetInSpanStart, offsetInSpanEnd - offsetInSpanStart);
    return options;
}

TextSpanOptions SpansUndoManager::CreateTextSpanOptions(const RefPtr<SpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto options = pattern->GetTextSpanOptions(item);
    options.offset = item->rangeStart;
    return options;
}

ImageSpanOptions SpansUndoManager::CreateImageSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateImageSpanOptions(AceType::DynamicCast<ImageSpanItem>(spanItem));
}

ImageSpanOptions SpansUndoManager::CreateImageSpanOptions(const RefPtr<ImageSpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto options = item->options;
    options.offset = item->rangeStart;
    return options;
}

SymbolSpanOptions SpansUndoManager::CreateSymbolSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateSymbolSpanOptions(spanItem);
}

SymbolSpanOptions SpansUndoManager::CreateSymbolSpanOptions(const RefPtr<SpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto options = pattern->GetSymbolSpanOptions(item);
    options.paraStyle = pattern->GetParagraphStyle(item);
    options.offset = item->rangeStart;
    return options;
}

BuilderSpanOptions SpansUndoManager::CreateBuilderSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateBuilderSpanOptions(AceType::DynamicCast<PlaceholderSpanItem>(spanItem));
}

BuilderSpanOptions SpansUndoManager::CreateBuilderSpanOptions(const RefPtr<PlaceholderSpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    BuilderSpanOptions options;
    options.customNode = item->GetCustomNode();
    options.offset = item->rangeStart;
    return options;
}
}