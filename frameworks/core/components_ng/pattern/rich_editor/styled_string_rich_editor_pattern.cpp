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
#include "core/components_ng/pattern/rich_editor/styled_string_rich_editor_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_undo_manager.h"

namespace OHOS::Ace::NG {

StyledStringRichEditorPattern::StyledStringRichEditorPattern() : RichEditorPattern()
{
    styledString_ = MakeRefPtr<MutableSpanString>(u"");
    styledString_->SetSpanWatcher(WeakClaim(this));
    undoManager_ = std::make_unique<StyledStringUndoManager>(WeakClaim(this));
}

void StyledStringRichEditorPattern::BeforeCreateLayoutWrapper()
{
    ACE_SCOPED_TRACE("RichEditorBeforeCreateLayoutWrapper");
    IF_PRESENT(contentMod_, ContentChange());
}

void StyledStringRichEditorPattern::InsertStyledStringByPaste(const RefPtr<SpanString>& spanString)
{
    CHECK_NULL_VOID(spanString && styledString_);
    int32_t changeStart = caretPosition_;
    int32_t changeLength = 0;
    if (textSelector_.IsValid()) {
        changeStart = textSelector_.GetTextStart();
        changeLength = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(changeStart, changeLength, spanString, record);
    CHECK_NULL_VOID(BeforeStyledStringChange(record));
    undoManager_->RecordOperation(record);
    auto subSpanString = spanString;
    int32_t startLength = maxLength_.value_or(INT_MAX) + changeLength - GetTextContentLength();
    if (spanString->GetLength() >= startLength) {
        auto range = TextEmojiProcessor::CalSubU16stringRange(
            startLength, spanString->GetLength() - startLength, spanString->GetU16string(), true, true);
        auto subLength = range.endIndex - range.startIndex;
        subSpanString = subSpanString->GetSubSpanString(0, spanString->GetLength() - subLength);
    }
 
    if (changeLength > 0 && subSpanString->GetLength() > 0) {
        DeleteForwardInStyledString(changeLength, false);
    }
    ResetSelection();
    styledString_->InsertSpanString(changeStart, subSpanString);
    SetCaretPosition(caretPosition_ + subSpanString->GetLength());
    AfterStyledStringChange(changeStart, changeLength, subSpanString->GetU16string());
}

void StyledStringRichEditorPattern::HandleOnDragInsertStyledString(const RefPtr<SpanString>& spanString, bool isCopy)
{
    CHECK_NULL_VOID(spanString);
    int currentCaretPosition = caretPosition_;
    auto strLength = spanString->GetLength();
    insertValueLength_ = strLength;
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(currentCaretPosition, 0, spanString, record);
    if (isDragSponsor_ && !isCopy) {
        bool isInsertForward = currentCaretPosition < dragRange_.first;
        bool isInsertBackward = currentCaretPosition > dragRange_.second;
        CHECK_NULL_VOID(isInsertForward || isInsertBackward);
        CHECK_NULL_VOID(BeforeStyledStringChange(record));
        undoManager_->RecordOperation(record);
        styledString_->InsertSpanString(currentCaretPosition, spanString);
        AfterStyledStringChange(record);
        if (isInsertForward) {
            SetCaretPosition(currentCaretPosition + strLength);
            dragRange_.first += strLength;
            dragRange_.second += strLength;
        }
        DeleteValueInStyledString(dragRange_.first, strLength, true, false);
    } else {
        CHECK_NULL_VOID(BeforeStyledStringChange(record));
        undoManager_->RecordOperation(record);
        styledString_->InsertSpanString(currentCaretPosition, spanString);
        SetCaretPosition(currentCaretPosition + strLength);
        AfterStyledStringChange(record);
    }
    StartTwinkling();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void StyledStringRichEditorPattern::SetStyledString(const RefPtr<SpanString>& value)
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetStyledString, len=%{public}d", value->GetLength());
    SEC_TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "SetStyledString, str=%{public}s", value->GetString().c_str());
    if (GetTextContentLength() > maxLength_.value_or(INT_MAX)) {
        TAG_LOGD(AceLogTag::ACE_RICH_TEXT, "SetStyledString: Reach the maxLength. maxLength=%{public}d",
            maxLength_.value_or(INT_MAX));
        return;
    }
    CHECK_NULL_VOID(value && styledString_);
    auto subValue = value;
    if (value->GetLength() != styledString_->GetLength() && value->GetLength() > maxLength_.value_or(INT_MAX)) {
        auto subLength = CalculateTruncationLength(value->GetU16string(), maxLength_.value_or(INT_MAX));
        if (subLength == 0) {
            IF_TRUE(IsPreviewTextInputting() && !previewTextRecord_.previewTextExiting, NotifyExitTextPreview(true));
            return;
        }
        subValue = value->GetSubSpanString(0, subLength);
    }
    IF_TRUE(IsPreviewTextInputting() && !previewTextRecord_.previewTextExiting, NotifyExitTextPreview(true));
    auto length = styledString_->GetLength();
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(0, length, subValue, record);
    CloseSelectOverlay();
    ResetSelection();
    styledString_->RemoveCustomSpan();
    styledString_->ReplaceSpanString(0, length, subValue);
    SetCaretPosition(styledString_->GetLength());
    SetNeedMoveCaretToContentRect();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    styledString_->AddCustomSpan();
    styledString_->SetFramNode(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    ForceTriggerAvoidOnCaretChange();
    undoManager_->RecordOperation(record);
}

void StyledStringRichEditorPattern::UpdateSpanItems(const std::list<RefPtr<NG::SpanItem>>& spanItems)
{
    SetSpanItemChildren(spanItems);
    ProcessStyledString();
}

void StyledStringRichEditorPattern::ProcessStyledString()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::u16string textCache = textForDisplay_;
    textForDisplay_.clear();
    dataDetectorAdapter_->textForAI_.clear();
    host->Clean();
    RemoveEmptySpanItems();
    hasUrlSpan_ = false;
    for (const auto& span : spans_) {
        if (!span) {
            continue;
        }
        auto imageSpan = DynamicCast<ImageSpanItem>(span);
        if (imageSpan) {
            MountImageNode(imageSpan);
            dataDetectorAdapter_->textForAI_ += u'\n';
        } else {
            dataDetectorAdapter_->textForAI_ += span->content;
        }
        textForDisplay_ += span->content;
        auto [spanStart, spanEnd] = span->interval;
        span->rangeStart = spanStart;
        span->position = spanEnd;
 
        if (span->urlOnRelease) {
            hasUrlSpan_ = true;
        }
    }
    if (textForDisplay_ != textCache) {
        dataDetectorAdapter_->aiDetectInitialized_ = false;
    }
    if (CanStartAITask() && !dataDetectorAdapter_->aiDetectInitialized_) {
        dataDetectorAdapter_->StartAITask();
    }
}

void StyledStringRichEditorPattern::MountImageNode(const RefPtr<ImageSpanItem>& imageItem)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(imageItem);
    auto options = imageItem->options;
    auto imageNode = ImageSpanNode::GetOrCreateSpanNode(V2::IMAGE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<ImagePattern>(); });
    auto pattern = imageNode->GetPattern<ImagePattern>();
    CHECK_NULL_VOID(pattern);
    if (options.imagePixelMap.has_value()) {
        pattern->SetSyncLoad(true);
    } else if (options.imageAttribute.has_value()) {
        pattern->SetSyncLoad(options.imageAttribute.value().syncLoad);
    }
    auto index = host->GetChildren().size();
    imageNodes.push_back(imageNode);
    imageNode->MountToParent(host, index);
    HandleImageDrag(imageNode);
    SetImageLayoutProperty(imageNode, options);
    imageNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    imageNode->MarkModifyDone();
    imageItem->nodeId_ = imageNode->GetId();
    imageNode->SetImageItem(imageItem);
}

void StyledStringRichEditorPattern::HandleStyledStringInsertion(RefPtr<SpanString> insertStyledString,
    const UndoRedoRecord& record, std::u16string& subValue, bool needReplaceInTextPreview, bool shouldCommitInput)
{
    auto changeStart = record.rangeBefore.start;
    auto changeLength = record.rangeBefore.GetLength();
    if (changeLength > 0 && (subValue.length() > 0 || !shouldCommitInput)) {
        auto start = needReplaceInTextPreview ? previewTextRecord_.replacedRange.start : caretPosition_;
        auto isUpdateCaret = !needReplaceInTextPreview;
        DeleteValueInStyledString(start, changeLength, false, isUpdateCaret);
    }
    bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
    if (textSelector_.IsValid()) {
        ResetSelection();
    }
    CloseSelectOverlay();
    if (insertStyledString) {
        styledString_->InsertSpanString(changeStart, insertStyledString);
    } else {
        styledString_->InsertString(changeStart, subValue);
    }
    SetCaretPosition(changeStart + static_cast<int32_t>(subValue.length()), !needReplaceInTextPreview);
    IF_TRUE((!caretVisible_ || isSingleHandleMoving) && HasFocus(), StartTwinkling());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}
 
void StyledStringRichEditorPattern::InsertValueInStyledString(
    const std::u16string& insertValue, bool shouldCommitInput)
{
    CHECK_NULL_VOID(styledString_);
    IF_TRUE(shouldCommitInput && previewTextRecord_.IsValid(), FinishTextPreviewInner());
    int32_t changeStart = caretPosition_;
    int32_t changeLength = 0;
    if (textSelector_.IsValid()) {
        changeStart = textSelector_.GetTextStart();
        changeLength = textSelector_.GetTextEnd() - changeStart;
        IF_TRUE(!shouldCommitInput, undoManager_->RecordPreviewInputtingStart(changeStart, changeLength));
    }
    auto subValue = insertValue;
    if (!ProcessTextTruncationOperation(subValue, shouldCommitInput)) {
        return;
    }
    auto needReplaceInTextPreview = (previewTextRecord_.needReplacePreviewText || previewTextRecord_.needReplaceText)
        && previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start > 0;
    if (needReplaceInTextPreview) {
        changeStart= previewTextRecord_.replacedRange.start;
        changeLength = previewTextRecord_.replacedRange.end - previewTextRecord_.replacedRange.start;
    }
    UndoRedoRecord record;
    bool isPreventChange = false;
    RefPtr<SpanString> insertStyledString = nullptr;
    if (typingStyle_.has_value() && typingTextStyle_.has_value()) {
        insertStyledString = CreateStyledStringByTextStyle(subValue, typingStyle_.value(), typingTextStyle_.value());
        undoManager_->ApplyOperationToRecord(changeStart, changeLength, insertStyledString, record);
        isPreventChange = !BeforeStyledStringChange(record);
    } else {
        undoManager_->ApplyOperationToRecord(changeStart, changeLength, subValue, record);
        isPreventChange = !BeforeStyledStringChange(record);
    }
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "InsertValueInSS isPreventChange=%{public}d, needReplacePreviewText=%{public}d",
        isPreventChange, previewTextRecord_.needReplacePreviewText);
    if (isPreventChange && !previewTextRecord_.needReplacePreviewText) {
        IF_TRUE(shouldCommitInput, undoManager_->ClearPreviewInputRecord());
        return;
    }
    HandleStyledStringInsertion(insertStyledString, record, subValue, needReplaceInTextPreview, shouldCommitInput);
    IF_TRUE(shouldCommitInput, undoManager_->RecordInsertOperation(record));
    AfterStyledStringChange(record);
}
 
RefPtr<SpanString> StyledStringRichEditorPattern::CreateStyledStringByTextStyle(
    const std::u16string& insertValue, const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle)
{
    auto styledString = AceType::MakeRefPtr<SpanString>(insertValue);
    auto length = styledString->GetLength();
    std::vector<RefPtr<SpanBase>> spans;
    spans.push_back(CreateFontSpanByTextStyle(updateSpanStyle, textStyle, length));
    spans.push_back(CreateDecorationSpanByTextStyle(updateSpanStyle, textStyle, length));
    if (updateSpanStyle.updateTextShadows.has_value()) {
        spans.push_back(AceType::MakeRefPtr<TextShadowSpan>(textStyle.GetTextShadows(), 0, length));
    }
    if (updateSpanStyle.updateLineHeight.has_value()) {
        spans.push_back(AceType::MakeRefPtr<LineHeightSpan>(textStyle.GetLineHeight(), 0, length));
    }
    if (updateSpanStyle.updateHalfLeading.has_value()) {
        spans.push_back(AceType::MakeRefPtr<HalfLeadingSpan>(textStyle.GetHalfLeading(), 0, length));
    }
    if (updateSpanStyle.updateLetterSpacing.has_value()) {
        spans.push_back(AceType::MakeRefPtr<LetterSpacingSpan>(textStyle.GetLetterSpacing(), 0, length));
    }
    if (updateSpanStyle.updateTextBackgroundStyle.has_value()) {
        spans.push_back(AceType::MakeRefPtr<BackgroundColorSpan>(textStyle.GetTextBackgroundStyle(), 0, length));
    }
    styledString->BindWithSpans(spans);
    return styledString;
}
 
RefPtr<FontSpan> StyledStringRichEditorPattern::CreateFontSpanByTextStyle(
    const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
{
    Font font;
    if (updateSpanStyle.updateFontWeight.has_value()) {
        font.fontWeight = textStyle.GetFontWeight();
    }
    if (updateSpanStyle.updateFontSize.has_value()) {
        font.fontSize = textStyle.GetFontSize();
    }
    if (updateSpanStyle.updateItalicFontStyle.has_value()) {
        font.fontStyle = textStyle.GetFontStyle();
    }
    if (updateSpanStyle.updateFontFamily.has_value()) {
        font.fontFamilies = textStyle.GetFontFamilies();
    }
    if (updateSpanStyle.updateTextColor.has_value()) {
        font.fontColor = textStyle.GetTextColor();
    }
    return AceType::MakeRefPtr<FontSpan>(font, 0, length);
}
 
RefPtr<DecorationSpan> StyledStringRichEditorPattern::CreateDecorationSpanByTextStyle(
    const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length)
{
    TextDecoration type = TextDecoration::NONE;
    std::optional<Color> colorOption;
    std::optional<TextDecorationStyle> styleOption;
    if (updateSpanStyle.updateTextDecoration.has_value()) {
        type = textStyle.GetTextDecoration();
    }
    if (updateSpanStyle.updateTextDecorationColor.has_value()) {
        colorOption = textStyle.GetTextDecorationColor();
    }
    if (updateSpanStyle.updateTextDecorationStyle.has_value()) {
        styleOption = textStyle.GetTextDecorationStyle();
    }
    return AceType::MakeRefPtr<DecorationSpan>(type, colorOption, styleOption, 0, length);
}
 
void StyledStringRichEditorPattern::DeleteBackwardInStyledString(int32_t length)
{
    DeleteValueInStyledString(caretPosition_ - length, length);
}
 
void StyledStringRichEditorPattern::DeleteForwardInStyledString(int32_t length, bool isIME)
{
    DeleteValueInStyledString(caretPosition_, length, isIME);
}
 
void StyledStringRichEditorPattern::DeleteValueInStyledString(int32_t start, int32_t length, bool isIME,
    bool isUpdateCaret)
{
    CHECK_NULL_VOID(styledString_);
    if (!textSelector_.SelectNothing()) {
        start = textSelector_.GetTextStart();
        length = textSelector_.GetTextEnd() - textSelector_.GetTextStart();
    }
    auto range = TextEmojiProcessor::CalSubU16stringRange(start, length, styledString_->GetU16string(), true, true);
    start = range.startIndex;
    length = range.endIndex - range.startIndex;
    UndoRedoRecord record;
    undoManager_->ApplyOperationToRecord(start, length, u"", record);
    bool isPreventChange = isIME && !BeforeStyledStringChange(record);
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT,
        "deleteInSS, start=%{public}d, length=%{public}d, isPreventChange=%{public}d, "
        "isPreviewTextInputting=%{public}d",
        start, length, isPreventChange, IsPreviewTextInputting());
    CHECK_NULL_VOID(!isPreventChange || IsPreviewTextInputting());
    IF_TRUE(isIME && !IsPreviewTextInputting(), undoManager_->RecordOperation(record));
    bool isSingleHandleMoving = selectOverlay_->IsSingleHandleMoving();
    if (textSelector_.IsValid()) {
        CloseSelectOverlay();
        ResetSelection();
    }
    styledString_->RemoveString(start, length);
    if (isUpdateCaret) {
        SetCaretPosition(start, !isModifyingContent_);
    }
    if ((!caretVisible_ || isSingleHandleMoving) && HasFocus()) {
        StartTwinkling();
        if (!isEditing_ && isIME) {
            TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "previewLongPress_ is true, before RequestKeyboard");
            RequestKeyboard(false, true, true);
            HandleOnEditChanged(true);
            previewLongPress_ = false;
        }
    }
    if (isIME) {
        AfterStyledStringChange(record);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}
 
RefPtr<SpanString> StyledStringRichEditorPattern::CreateStyledStringByStyleBefore(int32_t start,
    const std::u16string& string)
{
    auto styledString = AceType::MakeRefPtr<SpanString>(string);
    CHECK_NULL_RETURN(styledString_, styledString);
    auto stringLength = styledString->GetLength();
    CHECK_NULL_RETURN(stringLength != 0, styledString);
    auto lastStyles = styledString_->GetSpans(start - 1, 1);
    for (auto&& style : lastStyles) {
        CHECK_NULL_CONTINUE(style);
        auto spanType = style->GetSpanType();
        CHECK_NULL_CONTINUE(spanType != SpanType::Image && spanType != SpanType::CustomSpan);
        auto span = style->GetSubSpan(0, stringLength);
        styledString->AddSpan(span);
    }
    return styledString;
}
 
bool StyledStringRichEditorPattern::BeforeStyledStringChange(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_RETURN(!record.isOnlyStyleChange, true);
    auto changeStart = isUndo ? record.rangeAfter.start : record.rangeBefore.start;
    auto changeLength = isUndo ? record.rangeAfter.GetLength() : record.rangeBefore.GetLength();
    auto styledString = isUndo ? record.styledStringBefore : record.styledStringAfter;
    return BeforeStyledStringChange(changeStart, changeLength, styledString);
}
 
bool StyledStringRichEditorPattern::BeforeStyledStringChange(int32_t start, int32_t length,
    const std::u16string& string)
{
    auto eventHub = GetOrCreateEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    CHECK_NULL_RETURN(eventHub->HasOnStyledStringWillChange(), true);
    auto changeStart = std::clamp(start, 0, GetTextContentLength());
    auto styledString = CreateStyledStringByStyleBefore(changeStart, string);
    return BeforeStyledStringChange(changeStart, length, styledString);
}
 
bool StyledStringRichEditorPattern::BeforeStyledStringChange(int32_t start, int32_t length,
    const RefPtr<SpanString>& styledString)
{
    auto eventHub = GetOrCreateEventHub<RichEditorEventHub>();
    CHECK_NULL_RETURN(eventHub, true);
    CHECK_NULL_RETURN(eventHub->HasOnStyledStringWillChange(), true);
    auto replaceMentString = AceType::MakeRefPtr<MutableSpanString>(u"");
    replaceMentString->AppendSpanString(styledString);
    StyledStringChangeValue changeValue;
    auto changeStart = std::clamp(start, 0, GetTextContentLength());
    auto changeEnd = std::clamp(changeStart + length, 0, GetTextContentLength());
    changeValue.SetRangeBefore({ changeStart, changeEnd });
    changeValue.SetReplacementString(replaceMentString);
    if (!previewTextRecord_.newPreviewContent.empty()) {
        auto previewTextStyledString = AceType::MakeRefPtr<MutableSpanString>(previewTextRecord_.newPreviewContent);
        changeValue.SetPreviewText(previewTextStyledString);
    }
    return eventHub->FireOnStyledStringWillChange(changeValue);
}
 
void StyledStringRichEditorPattern::AfterStyledStringChange(int32_t start, int32_t length,
    const std::u16string& string)
{
    auto eventHub = GetOrCreateEventHub<RichEditorEventHub>();
    CHECK_NULL_VOID(eventHub);
    if (eventHub->HasOnStyledStringDidChange()) {
        StyledStringChangeValue changeValue;
        auto changeStart = std::clamp(start, 0, GetTextContentLength());
        auto changeEnd = changeStart + length;
        auto stringLength = static_cast<int32_t>(string.length());
        auto stringEnd = changeStart + stringLength;
        changeValue.SetRangeBefore({ changeStart, changeEnd });
        changeValue.SetRangeAfter({ changeStart, stringEnd });
        eventHub->FireOnStyledStringDidChange(changeValue);
    }
    ForceTriggerAvoidOnCaretChange();
}
 
void StyledStringRichEditorPattern::AfterStyledStringChange(const UndoRedoRecord& record, bool isUndo)
{
    CHECK_NULL_VOID(!record.isOnlyStyleChange);
    auto start = isUndo ? record.rangeAfter.start : record.rangeBefore.start;
    auto length = isUndo ? record.rangeAfter.GetLength() : record.rangeBefore.GetLength();
    auto styledString = isUndo ? record.styledStringBefore : record.styledStringAfter;
    CHECK_NULL_VOID(styledString);
    AfterStyledStringChange(start, length, styledString->GetU16string());
}
 
void StyledStringRichEditorPattern::HandleUndoInStyledString(const UndoRedoRecord& record)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    IF_PRESENT(magnifierController_, RemoveMagnifierFrameNode());
    ResetTouchAndMoveCaretState(false);
    auto undoRecord = record;
    undoRecord.Reverse();
    ApplyRecordInStyledString(undoRecord);
    if (record.selectionBefore.GetLength() == 0) {
        IF_TRUE(isEditing_, StartTwinkling());
    } else {
        HandleSelectionChange(undoRecord.selectionBefore.start, undoRecord.selectionBefore.end);
    }
    SetCaretPosition(undoRecord.selectionBefore.end);
    caretAffinityPolicy_ = undoRecord.caretAffinityBefore;
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}
 
void StyledStringRichEditorPattern::HandleRedoInStyledString(const UndoRedoRecord& record)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    ApplyRecordInStyledString(record);
    SetCaretPosition(record.rangeAfter.end);
    IF_TRUE(isEditing_, StartTwinkling());
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    host->MarkModifyDone();
}
 
void StyledStringRichEditorPattern::ApplyRecordInStyledString(const UndoRedoRecord& record)
{
    CHECK_NULL_VOID(styledString_);
    auto start = record.rangeBefore.start;
    auto length = record.rangeBefore.GetLength();
    auto styledString = record.styledStringAfter;
    auto startBefore = record.rangeAfter.start;
    auto lengthBefore = record.rangeAfter.GetLength();
    CloseSelectOverlay();
    ResetSelection();
    if (record.isOnlyStyleChange) {
        std::vector<RefPtr<SpanBase>> updateSpans;
        for (const auto& spanType : record.updateSpanTypes) {
            styledString_->RemoveSpan(start, length, spanType);
            auto spansBefore = styledString->GetSpans(0, lengthBefore, spanType);
            for (auto& span : spansBefore) {
                CHECK_NULL_CONTINUE(span);
                auto spanStart = span->GetStartIndex() + startBefore;
                auto spanEnd = span->GetEndIndex() + startBefore;
                updateSpans.push_back(span->GetSubSpan(spanStart, spanEnd));
            }
        }
        paragraphCache_.Clear();
        styledString_->BindWithSpans(updateSpans);
        styledString_->NotifySpanWatcher();
    } else {
        styledString_->ReplaceSpanString(start, length, styledString);
    }
}
 
bool StyledStringRichEditorPattern::IsCustomSpanInCaretPos(int32_t position, bool downStreamFirst)
{
    CHECK_NULL_RETURN((isSpanStringMode_ && styledString_), false);
    auto start = downStreamFirst ? position : position - 1;
    start = std::clamp(start, 0, GetTextContentLength());
    auto lastStyles = styledString_->GetSpans(start, 1);
    for (auto& style : lastStyles) {
        if (style && style->GetSpanType() == SpanType::CustomSpan) {
            return true;
        }
    }
    return false;
}
 
 
bool StyledStringRichEditorPattern::CheckStyledStringRangeValid(int32_t start, int32_t length)
{
    if (!styledString_ || !styledString_->CheckRange(start, length)) {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "range:[%{public}d-%{public}d] is invalid or styledString is null",
            start, start + length);
        return false;
    }
    return true;
}
 
void StyledStringRichEditorPattern::UpdateSelectStyledStringStyle(int32_t start, int32_t end, KeyCode code)
{
    auto length = end - start;
    CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
    UndoRedoRecord record;
    undoManager_->UpdateRecordBeforeChange(start, length, record, true);
    Font updateFont;
    bool isFirstSpanStylePresent;
    switch (code) {
        case KeyCode::KEY_B: {
            auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
            isFirstSpanStylePresent = firstFontSpan && firstFontSpan->GetFont().fontWeight == FontWeight::BOLD;
            updateFont.fontWeight = isFirstSpanStylePresent ? FontWeight::NORMAL : FontWeight::BOLD;
            UpdateStyledStringFontStyle(start, end, updateFont);
            record.AddUpdateSpanType(SpanType::Font);
            break;
        }
        case KeyCode::KEY_I: {
            auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
            isFirstSpanStylePresent = firstFontSpan &&
                firstFontSpan->GetFont().fontStyle == OHOS::Ace::FontStyle::ITALIC;
            updateFont.fontStyle = isFirstSpanStylePresent ?
                OHOS::Ace::FontStyle::NORMAL : OHOS::Ace::FontStyle::ITALIC;
            UpdateStyledStringFontStyle(start, end, updateFont);
            record.AddUpdateSpanType(SpanType::Font);
            break;
        }
        case KeyCode::KEY_U: {
            auto firstDecorationSpan =
                DynamicCast<DecorationSpan>(styledString_->GetSpan(start, 1, SpanType::Decoration));
            isFirstSpanStylePresent =
                firstDecorationSpan && firstDecorationSpan->GetTextDecorationType() == TextDecoration::UNDERLINE;
            auto updateDecorationType = isFirstSpanStylePresent ? TextDecoration::NONE : TextDecoration::UNDERLINE;
            UpdateStyledStringDecorationType(start, end, updateDecorationType);
            record.AddUpdateSpanType(SpanType::Decoration);
            break;
        }
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported key code for UpdateSelectStyledStringStyle");
            return;
    }
    undoManager_->UpdateRecordAfterChange(start, length, record);
    undoManager_->RecordOperation(record);
}
 
template<typename T>
void StyledStringRichEditorPattern::UpdateSpansStyleInRange(int32_t start, int32_t end,
    const RefPtr<SpanBase>& baseSpan, std::function<RefPtr<T>(const RefPtr<T>&)>&& updateSpanFunc)
{
    auto length = end - start;
    CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
    CHECK_NULL_VOID(baseSpan);
    auto spanType = baseSpan->GetSpanType();
    std::vector<RefPtr<SpanBase>> updateSpans;
    updateSpans.push_back(baseSpan);
    auto originalSpans = styledString_->GetSpans(start, length, spanType);
    for (auto& originalSpan : originalSpans) {
        auto originalTypedSpan = DynamicCast<T>(originalSpan);
        CHECK_NULL_CONTINUE(originalTypedSpan)
        updateSpans.push_back(updateSpanFunc(originalTypedSpan));
    }
    paragraphCache_.Clear();
    styledString_->BindWithSpans(updateSpans);
    styledString_->NotifySpanWatcher();
}
 
void StyledStringRichEditorPattern::UpdateStyledStringFontStyle(int32_t start, int32_t end, const Font& font)
{
    auto fontSpan = AceType::MakeRefPtr<FontSpan>(font, start, end);
    auto updateFontSpanFunc = [&font](const RefPtr<FontSpan>& oriFontSpan) -> RefPtr<FontSpan> {
        CHECK_NULL_RETURN(oriFontSpan, nullptr);
        auto fontStyle = oriFontSpan->GetFont();
        if (font.fontStyle.has_value()) {
            fontStyle.fontStyle = font.fontStyle.value();
        }
        if (font.fontWeight.has_value()) {
            fontStyle.fontWeight = font.fontWeight.value();
        }
        return AceType::MakeRefPtr<FontSpan>(fontStyle, oriFontSpan->GetStartIndex(), oriFontSpan->GetEndIndex());
    };
    UpdateSpansStyleInRange<FontSpan>(start, end, fontSpan, updateFontSpanFunc);
}
 
void StyledStringRichEditorPattern::UpdateStyledStringDecorationType(int32_t start, int32_t end,
    const TextDecoration& type)
{
    std::optional<Color> colorOption;
    std::optional<TextDecorationStyle> styleOption;
    auto decorationSpan = AceType::MakeRefPtr<DecorationSpan>(type, colorOption, styleOption, start, end);
    auto updateDecorationSpanFunc = [&type](const RefPtr<DecorationSpan>& decorationSpan) -> RefPtr<DecorationSpan> {
        CHECK_NULL_RETURN(decorationSpan, nullptr);
        auto decorationColor = decorationSpan->GetColor();
        auto decorationStyle = decorationSpan->GetTextDecorationStyle();
        return AceType::MakeRefPtr<DecorationSpan>(type, decorationColor, decorationStyle,
            decorationSpan->GetStartIndex(), decorationSpan->GetEndIndex());
    };
    UpdateSpansStyleInRange<DecorationSpan>(start, end, decorationSpan, updateDecorationSpanFunc);
}
 
void StyledStringRichEditorPattern::HandleOnCopyStyledString()
{
    RefPtr<PasteDataMix> pasteData = clipboard_->CreatePasteDataMix();
    auto subSpanString = styledString_->GetSubSpanString(textSelector_.GetTextStart(),
        textSelector_.GetTextEnd() - textSelector_.GetTextStart());
#ifdef PREVIEW
    clipboard_->SetData(subSpanString->GetString(), CopyOptions::Distributed);
#else
    std::vector<uint8_t> tlvData;
    subSpanString->EncodeTlv(tlvData);
    clipboard_->AddSpanStringRecord(pasteData, tlvData);
    clipboard_->AddTextRecord(pasteData, subSpanString->GetString());
    clipboard_->SetData(pasteData, copyOption_);
#endif
}
 
void StyledStringRichEditorPattern::ReplacePlaceholderWithCustomSpan(
    const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex)
{
    auto customSpanItem = DynamicCast<CustomSpanItem>(spanItem);
    auto customSpan = MakeRefPtr<CustomSpan>();
    if (customSpanItem->onMeasure.has_value()) {
        customSpan->SetOnMeasure(customSpanItem->onMeasure.value());
    }
    if (customSpanItem->onDraw.has_value()) {
        customSpan->SetOnDraw(customSpanItem->onDraw.value());
    }
    auto spanString = MakeRefPtr<MutableSpanString>(customSpan);
    InsertStyledStringByPaste(spanString);
    textIndex = index + PLACEHOLDER_LENGTH;
}
 
void StyledStringRichEditorPattern::UpdateSelectSpanStyle(int32_t start, int32_t end, KeyCode code)
{
    auto length = end - start;
    CHECK_NULL_VOID(CheckStyledStringRangeValid(start, length));
    UndoRedoRecord record;
    undoManager_->UpdateRecordBeforeChange(start, length, record, true);
    Font updateFont;
    bool isFirstSpanStylePresent;
    switch (code) {
        case KeyCode::KEY_B: {
            auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
            isFirstSpanStylePresent = firstFontSpan && firstFontSpan->GetFont().fontWeight == FontWeight::BOLD;
            updateFont.fontWeight = isFirstSpanStylePresent ? FontWeight::NORMAL : FontWeight::BOLD;
            UpdateStyledStringFontStyle(start, end, updateFont);
            record.AddUpdateSpanType(SpanType::Font);
            break;
        }
        case KeyCode::KEY_I: {
            auto firstFontSpan = DynamicCast<FontSpan>(styledString_->GetSpan(start, 1, SpanType::Font));
            isFirstSpanStylePresent = firstFontSpan &&
                firstFontSpan->GetFont().fontStyle == OHOS::Ace::FontStyle::ITALIC;
            updateFont.fontStyle = isFirstSpanStylePresent ?
                OHOS::Ace::FontStyle::NORMAL : OHOS::Ace::FontStyle::ITALIC;
            UpdateStyledStringFontStyle(start, end, updateFont);
            record.AddUpdateSpanType(SpanType::Font);
            break;
        }
        case KeyCode::KEY_U: {
            auto firstDecorationSpan =
                DynamicCast<DecorationSpan>(styledString_->GetSpan(start, 1, SpanType::Decoration));
            isFirstSpanStylePresent =
                firstDecorationSpan && firstDecorationSpan->GetTextDecorationType() == TextDecoration::UNDERLINE;
            auto updateDecorationType = isFirstSpanStylePresent ? TextDecoration::NONE : TextDecoration::UNDERLINE;
            UpdateStyledStringDecorationType(start, end, updateDecorationType);
            record.AddUpdateSpanType(SpanType::Decoration);
            break;
        }
        default:
            TAG_LOGW(AceLogTag::ACE_RICH_TEXT, "Unsupported key code for UpdateSelectStyledStringStyle");
            return;
    }
    undoManager_->UpdateRecordAfterChange(start, length, record);
    undoManager_->RecordOperation(record);
}
 
void StyledStringRichEditorPattern::HandleOnUndoAction()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnUndoAction_SS");
    undoManager_->UndoByRecords();
}
 
void StyledStringRichEditorPattern::HandleOnRedoAction()
{
    TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnRedoAction_SS");
    undoManager_->RedoByRecords();
}
 
void StyledStringRichEditorPattern::ClearOperationRecords()
{
    undoManager_->ClearUndoRedoRecords();
}
 
}