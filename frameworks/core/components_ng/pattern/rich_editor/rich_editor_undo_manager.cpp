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
namespace {
    constexpr uint32_t RECORD_MAX_LENGTH = 20;
    constexpr int32_t IMAGE_SPAN_LENGTH = 1;
    constexpr int32_t SYMBOL_SPAN_LENGTH = 2;
    constexpr auto IMAGE_CONTENT = u" ";
} // namespace

// =============================================================================
// OPTIONS LIST BUILDER IMPLEMENTATION
// =============================================================================
OptionsList OptionsListBuilder::CreateOptionsListByRange(TextRange range)
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

SpanOptions OptionsListBuilder::CreateSpanOptionsBySpanObject(const ResultObject& object)
{
    auto type = object.type;
    if (type == SelectSpanType::TYPEIMAGE && object.valueString == IMAGE_CONTENT && object.valuePixelMap == nullptr) {
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

TextSpanOptions OptionsListBuilder::CreateTextSpanOptions(const ResultObject& object)
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

TextSpanOptions OptionsListBuilder::CreateTextSpanOptions(const RefPtr<SpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto options = pattern->GetTextSpanOptions(item);
    options.offset = item->rangeStart;
    return options;
}

ImageSpanOptions OptionsListBuilder::CreateImageSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateImageSpanOptions(AceType::DynamicCast<ImageSpanItem>(spanItem));
}

ImageSpanOptions OptionsListBuilder::CreateImageSpanOptions(const RefPtr<ImageSpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto options = item->options;
    options.offset = item->rangeStart;
    return options;
}

SymbolSpanOptions OptionsListBuilder::CreateSymbolSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateSymbolSpanOptions(spanItem);
}

SymbolSpanOptions OptionsListBuilder::CreateSymbolSpanOptions(const RefPtr<SpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto options = pattern->GetSymbolSpanOptions(item);
    options.paraStyle = pattern->GetParagraphStyle(item);
    options.offset = item->rangeStart;
    return options;
}

BuilderSpanOptions OptionsListBuilder::CreateBuilderSpanOptions(const ResultObject& object)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, {});
    auto spanItem = pattern->GetSpanItemByIndex(object.spanPosition.spanIndex);
    return CreateBuilderSpanOptions(AceType::DynamicCast<PlaceholderSpanItem>(spanItem));
}

BuilderSpanOptions OptionsListBuilder::CreateBuilderSpanOptions(const RefPtr<PlaceholderSpanItem>& item)
{
    CHECK_NULL_RETURN(item, {});
    BuilderSpanOptions options;
    options.customNode = item->GetCustomNode();
    options.offset = item->rangeStart;
    return options;
}

// =============================================================================
// RICH EDITOR UNDO MANAGER IMPLEMENTATION
// =============================================================================
std::unique_ptr<RichEditorUndoManager> RichEditorUndoManager::Create(
    bool isSpanStringMode, const WeakPtr<RichEditorPattern>& pattern)
{
    CHECK_NULL_RETURN(!isSpanStringMode, std::make_unique<StyledStringUndoManager>(pattern));
    auto richEditorPattern = pattern.Upgrade();
    bool isStyledUndoSupported = richEditorPattern && richEditorPattern->isStyledUndoSupported_;
    CHECK_NULL_RETURN(isStyledUndoSupported, std::make_unique<StringUndoManager>(pattern));
    return std::make_unique<SpansUndoManager>(pattern);
}

void RichEditorUndoManager::UndoByRecords()
{
    CHECK_NULL_VOID(!undoRecords_.empty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsUndoManagerEnabled());
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
    pattern->IsSupportStyledUndo() ? ProcessStyledUndo(record) : ProcessStringUndo(record);
    RecordUndoOperation(record);
    IF_TRUE(!record.isOnlyStyleChange, AfterChangeByRecord(record, true));
}

void RichEditorUndoManager::RedoByRecords()
{
    CHECK_NULL_VOID(!redoRecords_.empty());
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsUndoManagerEnabled());
    CHECK_NULL_VOID(!pattern->IsPreviewTextInputting());
    auto record = redoRecords_.back();
    redoRecords_.pop_back();
    bool isPreventChange = !record.isOnlyStyleChange && !BeforeChangeByRecord(record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RedoByRecords [%{public}s] isPreventChange=%{public}d",
        record.ToString().c_str(), isPreventChange);
    CHECK_NULL_VOID(!isPreventChange);
    pattern->IsSupportStyledUndo() ? ProcessStyledRedo(record) : ProcessStringRedo(record);
    RecordOperation(record, true);
    IF_TRUE(!record.isOnlyStyleChange, AfterChangeByRecord(record));
}

void RichEditorUndoManager::AfterChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    CHECK_NULL_VOID(eventHub->HasOnDidChange());
    RichEditorChangeValue changeValue(isUndo ? TextChangeReason::UNDO : TextChangeReason::REDO);
    auto rangeBefore = isUndo ? record.rangeAfter : record.rangeBefore;
    changeValue.SetRangeBefore(rangeBefore);
    auto rangeAfter = isUndo ? record.rangeBefore : record.rangeAfter;
    changeValue.SetRangeAfter(rangeAfter);
    eventHub->FireOnDidChange(changeValue);
    pattern->ReportAfterContentChangeEvent();
}

void RichEditorUndoManager::RecordSelectionBefore()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsUndoManagerEnabled());
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
    CHECK_NULL_VOID(IsUndoManagerEnabled());
    selectionBefore_ = selection;
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "RecordSelectionBefore:%{public}s", selectionBefore_.ToString().c_str());
}

void RichEditorUndoManager::UpdateRecordBeforeChange(
    int32_t start, int32_t length, UndoRedoRecord& record, bool isOnlyStyleChange)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(IsUndoManagerEnabled());
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

void RichEditorUndoManager::RecordAddSpanOperation(const RefPtr<SpanItem>& item, SpanOptionsType type)
{
    CHECK_NULL_VOID(item);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && IsUndoManagerEnabled());
    auto start = item->rangeStart;
    UndoRedoRecord record;
    UpdateRecordBeforeChange(start, 0, record);
    int32_t length = static_cast<int32_t>(item->content.length());
    SpanOptions options;
    switch (type) {
        case SpanOptionsType::TEXT: {
            options = builder_->CreateTextSpanOptions(item);
            break;
        }
        case SpanOptionsType::IMAGE: {
            options = builder_->CreateImageSpanOptions(AceType::DynamicCast<ImageSpanItem>(item));
            break;
        }
        case SpanOptionsType::SYMBOL: {
            options = builder_->CreateSymbolSpanOptions(item);
            break;
        }
        case SpanOptionsType::BUILDER: {
            options = builder_->CreateBuilderSpanOptions(AceType::DynamicCast<PlaceholderSpanItem>(item));
            break;
        }
        default:
            break;
    }
    record.SetOperationAfter(TextRange{ start, start + length }, OptionsList{ options });
    RecordOperation(record);
}

void RichEditorUndoManager::ProcessStyledUndo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && pattern->IsSupportStyledUndo());
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    IF_PRESENT(pattern->magnifierController_, RemoveMagnifierFrameNode());
    pattern->ResetTouchAndMoveCaretState(false);
    auto undoRecord = record;
    undoRecord.Reverse();
    ApplyRecord(undoRecord, true);
    if (record.selectionBefore.GetLength() == 0) {
        IF_TRUE(pattern->isEditing_, pattern->StartTwinkling());
    } else {
        pattern->HandleSelectionChange(undoRecord.selectionBefore.start, undoRecord.selectionBefore.end);
        pattern->FireOnSelect(pattern->textSelector_.GetTextStart(), pattern->textSelector_.GetTextEnd());
    }
    pattern->SetCaretPosition(undoRecord.selectionBefore.end);
    pattern->caretAffinityPolicy_ = undoRecord.caretAffinityBefore;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorUndoManager::ProcessStyledRedo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern && pattern->IsSupportStyledUndo());
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    ApplyRecord(record, false);
    pattern->SetCaretPosition(record.rangeAfter.end);
    IF_TRUE(pattern->isEditing_, pattern->StartTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorUndoManager::ProcessStringUndo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto undoRecord = record;
    undoRecord.Reverse();
    ApplyRecord(undoRecord, true);
    pattern->SetCaretPosition(undoRecord.selectionBefore.end);
    pattern->caretAffinityPolicy_ = undoRecord.caretAffinityBefore;
    IF_TRUE(pattern->isEditing_, pattern->StartTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

void RichEditorUndoManager::ProcessStringRedo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    ApplyRecord(record, false);
    pattern->SetCaretPosition(record.rangeAfter.end);
    IF_TRUE(pattern->isEditing_, pattern->StartTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}

RichEditorAbstractSpanResult RichEditorUndoManager::GetResultByImageSpanOptions(const ImageSpanOptions& options,
    int32_t spanIndex)
{
    RichEditorAbstractSpanResult retInfo;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, retInfo);
    auto spanRangeStart = options.offset.value_or(pattern->GetTextContentLength());
    pattern->UpdateSpanResultRange(retInfo, spanIndex, { spanRangeStart, spanRangeStart + IMAGE_SPAN_LENGTH });
    pattern->UpdateImageSpanResultByOptions(retInfo, options);
    return retInfo;
}

RichEditorAbstractSpanResult RichEditorUndoManager::GetResultByTextSpanOptions(const TextSpanOptions& options,
    int32_t spanIndex)
{
    RichEditorAbstractSpanResult retInfo;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, retInfo);
    auto spanRangeStart = options.offset.value_or(pattern->GetTextContentLength());
    pattern->UpdateSpanResultRange(retInfo, spanIndex, { spanRangeStart, spanRangeStart + options.value.length() });
    pattern->UpdateTextSpanResultByOptions(retInfo, options);
    return retInfo;
}

RichEditorAbstractSpanResult RichEditorUndoManager::GetResultBySymbolSpanOptions(const SymbolSpanOptions& options,
    int32_t spanIndex)
{
    RichEditorAbstractSpanResult retInfo;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, retInfo);
    auto spanRangeStart = options.offset.value_or(pattern->GetTextContentLength());
    pattern->UpdateSpanResultRange(retInfo, spanIndex, { spanRangeStart, spanRangeStart + SYMBOL_SPAN_LENGTH });
    pattern->UpdateSymbolSpanResultByOptions(retInfo, options);
    return retInfo;
}

RichEditorAbstractSpanResult RichEditorUndoManager::GetResultByBuilderSpanOptions(const BuilderSpanOptions& options,
    int32_t spanIndex)
{
    RichEditorAbstractSpanResult retInfo;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, retInfo);
    retInfo.SetSpanType(SpanResultType::IMAGE);
    auto spanRangeStart = options.offset.value_or(pattern->GetTextContentLength());
    pattern->UpdateSpanResultRange(retInfo, spanIndex, { spanRangeStart, spanRangeStart + IMAGE_SPAN_LENGTH });
    return retInfo;
}

// =============================================================================
// STYLED STRING UNDO MANAGER IMPLEMENTATION
// =============================================================================
bool StyledStringUndoManager::IsUndoManagerEnabled()
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

void StyledStringUndoManager::ApplyRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    CHECK_NULL_VOID(pattern->IsStyledStringModeEnabled());
    auto start = record.rangeBefore.start;
    auto length = record.rangeBefore.GetLength();
    auto styledString = record.styledStringAfter;
    auto startBefore = record.rangeAfter.start;
    auto lengthBefore = record.rangeAfter.GetLength();
    auto curStyledString = pattern->GetStyledString();
    pattern->CloseSelectOverlay();
    pattern->ResetSelection();
    if (record.isOnlyStyleChange) {
        std::vector<RefPtr<SpanBase>> updateSpans;
        for (const auto& spanType : record.updateSpanTypes) {
            curStyledString->RemoveSpan(start, length, spanType);
            auto spansBefore = styledString->GetSpans(0, lengthBefore, spanType);
            for (auto& span : spansBefore) {
                CHECK_NULL_CONTINUE(span);
                auto spanStart = span->GetStartIndex() + startBefore;
                auto spanEnd = span->GetEndIndex() + startBefore;
                updateSpans.push_back(span->GetSubSpan(spanStart, spanEnd));
            }
        }
        pattern->paragraphCache_.Clear();
        curStyledString->BindWithSpans(updateSpans);
        curStyledString->NotifySpanWatcher();
    } else {
        curStyledString->ReplaceSpanString(start, length, styledString);
    }
}

// =============================================================================
// SPANS UNDO MANAGER IMPLEMENTATION
// =============================================================================
bool SpansUndoManager::IsUndoManagerEnabled()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return pattern->IsSupportStyledUndo();
}

bool SpansUndoManager::BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_RETURN(!record.isOnlyStyleChange, true);
    return BeforeSpansChange(record, isUndo);
}

bool SpansUndoManager::BeforeSpansChange(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    RichEditorChangeValue changeValue(isUndo ? TextChangeReason::UNDO : TextChangeReason::REDO);
    auto rangeBefore = isUndo ? record.rangeAfter : record.rangeBefore;
    changeValue.SetRangeBefore(rangeBefore);
    auto rangeAfter = isUndo ? record.rangeBefore : record.rangeAfter;
    changeValue.SetRangeAfter(rangeAfter);
    auto optionsList = isUndo ? record.optionsListBefore : record.optionsListAfter;
    TextInsertValueInfo info;
    pattern->CalcInsertValueObj(info, rangeBefore.start, true);
    int32_t spanIndex = info.GetSpanIndex();
    OptionsListHandler handler(
        [&](const ImageSpanOptions& opts) {
            auto retInfo = GetResultByImageSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedImageSpans(retInfo);
        },
        [&](const TextSpanOptions& opts) {
            auto retInfo = GetResultByTextSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedSpans(retInfo);
        },
        [&](const SymbolSpanOptions& opts) {
            auto retInfo = GetResultBySymbolSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedSymbolSpans(retInfo);
        },
        [&](const BuilderSpanOptions& opts) {
            auto textOptions = TextSpanOptions{ .offset = opts.offset, .value = u" " };
            auto retInfo = GetResultByTextSpanOptions(textOptions, spanIndex);
            changeValue.SetRichEditorReplacedSpans(retInfo);
        },
        [&]() {
            spanIndex++;
        }
    );
    handler(optionsList.value_or(OptionsList{}));
    return eventHub->FireOnWillChange(changeValue);
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
            IF_TRUE(needRemove, (option = TextSpanOptions{ .offset = builderOpt->offset, .value = IMAGE_CONTENT }));
        }
    }
}

void SpansUndoManager::SetOperationBefore(
    TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity, UndoRedoRecord& record)
{
    CHECK_NULL_VOID(IsUndoManagerEnabled());
    record.SetOperationBefore(range, builder_->CreateOptionsListByRange(range), selection, caretAffinity);
}

void SpansUndoManager::UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(IsUndoManagerEnabled());
    auto end = std::min(start + length, pattern->GetTextContentLength());
    auto rangeAfter = TextRange{ start, end };
    record.SetOperationAfter(rangeAfter, builder_->CreateOptionsListByRange(rangeAfter));
}

void SpansUndoManager::ApplyRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->CloseSelectOverlay();
    pattern->ResetSelection();
    pattern->StopTwinkling();
    pattern->DeleteForward(record.rangeBefore.start, record.rangeBefore.GetLength());
    ApplyOptions(record.optionsListAfter.value_or(OptionsList{}), record.IsRestoreBuilderSpan(), isUndo);
}

void SpansUndoManager::ApplyOptions(const OptionsList& optionsList, bool restoreBuilderSpan, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    int32_t optionsLength = 0;
    auto reason = isUndo ? TextChangeReason::UNDO : TextChangeReason::REDO;
    OptionsListHandler handler(
        [&](const ImageSpanOptions& opts) {
            ImageSpanOptions options = opts;
            options.optionSource = OptionSource::UNDO_REDO;
            pattern->AddImageSpan(options, reason, false, pattern->GetCaretIndex(), false);
            optionsLength++;
        },
        [&](const TextSpanOptions& opts) {
            TextSpanOptions options = opts;
            options.optionSource = OptionSource::UNDO_REDO;
            pattern->AddTextSpan(options, reason, false, pattern->GetCaretIndex());
            optionsLength += static_cast<int32_t>(options.value.length());
        },
        [&](const SymbolSpanOptions& opts) {
            SymbolSpanOptions options = opts;
            options.optionSource = OptionSource::UNDO_REDO;
            pattern->AddSymbolSpan(options, reason, false, pattern->GetCaretIndex());
            optionsLength += SYMBOL_SPAN_LENGTH;
        },
        [&](const BuilderSpanOptions& opts) {
            pattern->AddPlaceholderSpan(opts, restoreBuilderSpan, reason);
            optionsLength++;
        }
    );
    handler(optionsList);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "ApplyOptions length=%{public}d", optionsLength);
}

// =============================================================================
// STRING UNDO MANAGER IMPLEMENTATION
// =============================================================================
bool StringUndoManager::IsUndoManagerEnabled()
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    return !pattern->IsSupportStyledUndo();
}

bool StringUndoManager::BeforeChangeByRecord(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_RETURN(record.restoreBuilderSpan, BeforeStringChange(record, isUndo));
    return isUndo ? BeforeUndoDrag(record) : BeforeRedoDrag(record);
}

void StringUndoManager::SetOperationBefore(TextRange range, TextRange selection, CaretAffinityPolicy caretAffinity,
    UndoRedoRecord& record)
{
    CHECK_NULL_VOID(!record.isOnlyStyleChange && IsUndoManagerEnabled());
    record.SetOperationBefore(range, builder_->CreateOptionsListByRange(range), selection, caretAffinity);
}

void StringUndoManager::UpdateRecordAfterChange(int32_t start, int32_t length, UndoRedoRecord& record)
{
    CHECK_NULL_VOID(!record.isOnlyStyleChange && IsUndoManagerEnabled());
    auto pattern = pattern_.Upgrade();
    auto end = std::min(start + length, pattern->GetTextContentLength());
    auto rangeAfter = TextRange{ start, end };
    record.SetOperationAfter(rangeAfter, builder_->CreateOptionsListByRange(rangeAfter));
    ProcessDragDeleteRecord(record);
}

void StringUndoManager::ApplyRecord(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->CloseSelectOverlay();
    pattern->ResetSelection();
    pattern->StopTwinkling();
    if (record.restoreBuilderSpan) {
        isUndo ? ProcessDragUndo(record) : ProcessDragRedo(record);
        return;
    }
    if (record.rangeBefore.GetLength() > 0) {
        pattern->DeleteForward(record.rangeBefore.start, record.rangeBefore.GetLength());
        auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
        IF_PRESENT(eventHub, FireOnDeleteComplete());
    }
    pattern->caretPosition_ = record.rangeBefore.start;
    pattern->InsertValueOperation(record.GetStringAfter());
}

void StringUndoManager::ProcessDragUndo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto insertOffset = record.rangeBefore.start;
    OptionsListHandler handler(
        [&](const ImageSpanOptions&) {
            pattern->InsertValueOperation(u" ", nullptr, OperationType::UNDO);
            insertOffset++;
        },
        [&](const TextSpanOptions& opts) {
            pattern->InsertValueOperation(opts.value, nullptr, OperationType::UNDO);
            insertOffset += static_cast<int32_t>(opts.value.length());
        },
        [&](const SymbolSpanOptions&) { insertOffset += SYMBOL_SPAN_LENGTH; },
        [&](const BuilderSpanOptions&) { insertOffset++; }
    );
    handler(record.optionsListAfter.value_or(OptionsList{}));
}

void StringUndoManager::ProcessDragRedo(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto deleteStart = record.rangeBefore.start;
    OptionsListHandler handler(
        [&](const ImageSpanOptions&) { pattern->DeleteForward(deleteStart, IMAGE_SPAN_LENGTH); },
        [&](const TextSpanOptions& opts) {
            pattern->DeleteForward(deleteStart, static_cast<int32_t>(opts.value.length()));
        },
        [&](const SymbolSpanOptions&) { deleteStart += SYMBOL_SPAN_LENGTH; },
        [&](const BuilderSpanOptions&) { deleteStart++; }
    );
    handler(record.optionsListBefore.value_or(OptionsList{}));
}

void StringUndoManager::ProcessDragDeleteRecord(UndoRedoRecord& record)
{
    CHECK_NULL_VOID(record.IsValid() && record.restoreBuilderSpan);
    OptionsList optionsList;
    std::optional<TextSpanOptions> textSpanOptions;
    const auto handleTextOrImage = [&](const std::u16string& str, std::optional<int32_t> offset) {
        if (!textSpanOptions.has_value()) {
            textSpanOptions = TextSpanOptions{ .offset = offset, .value = str };
            return;
        }
        textSpanOptions->value += str;
    };
    const auto handleSymbolOrBuilder = [&](const auto& opts) {
        if (textSpanOptions.has_value()) {
            optionsList.push_back(textSpanOptions.value());
            textSpanOptions = std::nullopt;
        }
        optionsList.push_back(opts);
    };
    OptionsListHandler handler(
        [&](const ImageSpanOptions& opts) { handleTextOrImage(IMAGE_CONTENT, opts.offset); },
        [&](const TextSpanOptions& opts) { handleTextOrImage(opts.value, opts.offset); },
        [&](const SymbolSpanOptions& opts) { handleSymbolOrBuilder(opts); },
        [&](const BuilderSpanOptions& opts) { handleSymbolOrBuilder(opts); }
    );
    handler(record.optionsListBefore.value_or(OptionsList{}));
    IF_TRUE(textSpanOptions.has_value(), optionsList.push_back(textSpanOptions.value()));
    record.optionsListBefore = optionsList;
}

bool StringUndoManager::BeforeStringChange(const UndoRedoRecord& record, bool isUndo)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    auto rangeBefore = isUndo ? record.rangeAfter : record.rangeBefore;
    auto rangeAfter = isUndo ? record.rangeBefore : record.rangeAfter;
    auto deleteLength = rangeBefore.GetLength();
    if (eventHub->HasOnWillChange()) {
        auto insertStart = rangeAfter.start;
        auto deleteEnd = rangeBefore.end;
        RichEditorChangeValue changeValue(isUndo ? TextChangeReason::UNDO : TextChangeReason::REDO);
        pattern->GetDeletedSpan(changeValue, deleteEnd, deleteLength, RichEditorDeleteDirection::BACKWARD);
        auto replaceStr = isUndo ? record.GetStringBefore() : record.GetStringAfter();
        IF_TRUE(!replaceStr.empty(), pattern->GetReplacedSpan(changeValue, insertStart, replaceStr, insertStart,
            std::nullopt, std::nullopt));
        CHECK_NULL_RETURN(eventHub->FireOnWillChange(changeValue), false);
    }
    CHECK_NULL_RETURN(deleteLength > 0, true);
    RichEditorDeleteValue info;
    auto deleteStart = rangeBefore.start;
    info.SetOffset(deleteStart);
    info.SetRichEditorDeleteDirection(RichEditorDeleteDirection::BACKWARD);
    info.SetLength(deleteLength);
    pattern->CalcDeleteValueObj(deleteStart, deleteLength, info);
    return eventHub->FireAboutToDelete(info);
}

bool StringUndoManager::BeforeUndoDrag(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    RichEditorChangeValue changeValue(TextChangeReason::UNDO);
    changeValue.SetRangeBefore(record.rangeAfter);
    changeValue.SetRangeAfter(record.rangeBefore);
    auto insertOffset = record.rangeBefore.start;
    const auto& optionsList = record.optionsListBefore.value_or(OptionsList{});
    auto spanIndex = CalcAdjustedInsertSpanIndex(insertOffset, optionsList);
    bool isFirst = true;
    OptionsListHandler handler(nullptr,
        [&](const TextSpanOptions& opts) {
            auto retInfo = GetAdjustedInsertSpanInfo(insertOffset, spanIndex, opts, isFirst);
            changeValue.SetRichEditorReplacedSpans(retInfo);
        },
        [&](const SymbolSpanOptions& opts) {
            auto retInfo = GetResultBySymbolSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedSymbolSpans(retInfo);
            insertOffset += SYMBOL_SPAN_LENGTH;
        },
        [&](const BuilderSpanOptions& opts) {
            auto retInfo = GetResultByBuilderSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedImageSpans(retInfo);
            insertOffset++;
        },
        [&]() {
            spanIndex++;
            isFirst = false;
        }
    );
    handler(optionsList);
    return eventHub->FireOnWillChange(changeValue);
}

bool StringUndoManager::BeforeRedoDrag(const UndoRedoRecord& record)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto eventHub = pattern->GetEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, false);
    CHECK_NULL_RETURN(eventHub->HasOnWillChange(), true);
    RichEditorChangeValue changeValue(TextChangeReason::REDO);
    changeValue.SetRangeBefore(record.rangeBefore);
    changeValue.SetRangeAfter(record.rangeAfter);
    TextInsertValueInfo info;
    pattern->CalcInsertValueObj(info, record.rangeBefore.start, true);
    int32_t spanIndex = info.GetSpanIndex();
    OptionsListHandler handler(nullptr, nullptr,
        [&](const SymbolSpanOptions& opts) {
            auto retInfo = GetResultBySymbolSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedSymbolSpans(retInfo);
        },
        [&](const BuilderSpanOptions& opts) {
            auto retInfo = GetResultByBuilderSpanOptions(opts, spanIndex);
            changeValue.SetRichEditorReplacedImageSpans(retInfo);
        },
        [&]() { spanIndex++; }
    );
    handler(record.optionsListAfter.value_or(OptionsList{}));
    return eventHub->FireOnWillChange(changeValue);
}

int32_t StringUndoManager::CalcAdjustedInsertSpanIndex(int32_t insertOffset, const OptionsList& optionsList)
{
    CHECK_NULL_RETURN(!optionsList.empty(), 0);
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, 0);
    const auto& firstOptions = optionsList.front();
    bool isCreate = !std::holds_alternative<TextSpanOptions>(firstOptions);
    TextInsertValueInfo info;
    pattern->CalcInsertValueObj(info, insertOffset, isCreate);
    int32_t spanIndex = info.GetSpanIndex();
    CHECK_NULL_RETURN(!isCreate, spanIndex);
    auto uiNode = pattern->GetChildByIndex(spanIndex);
    IF_TRUE((uiNode && uiNode->GetTag() != V2::SPAN_ETS_TAG), spanIndex++);
    return spanIndex;
}

RichEditorAbstractSpanResult StringUndoManager::GetAdjustedInsertSpanInfo(int32_t insertOffset, int32_t spanIndex,
    const TextSpanOptions& options, bool isFirst)
{
    RichEditorAbstractSpanResult retInfo;
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, retInfo);
    RichEditorChangeValue insertChangeValue(TextChangeReason::INPUT);
    pattern->GetReplacedSpan(insertChangeValue, insertOffset, options.value, insertOffset, std::nullopt, std::nullopt);
    auto& replaceSpans = insertChangeValue.GetRichEditorReplacedSpans();
    CHECK_NULL_RETURN(!replaceSpans.empty(), {});
    retInfo = replaceSpans.back();
    retInfo.SetSpanIndex(spanIndex);
    CHECK_NULL_RETURN(!isFirst && options.offset.has_value(), retInfo);
    auto spanStart = options.offset.value();
    auto spanLength = retInfo.GetSpanRangeEnd() - retInfo.GetSpanRangeStart();
    auto spanEnd = spanStart + spanLength;
    retInfo.SetSpanRangeStart(spanStart);
    retInfo.SetSpanRangeEnd(spanEnd);
    return retInfo;
}
}