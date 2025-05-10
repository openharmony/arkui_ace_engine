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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STYLED_STRING_RICH_EDITOR_RICH_EDITOR_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STYLED_STRING_RICH_EDITOR_RICH_EDITOR_PATTERN_H

#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"

namespace {
constexpr int32_t PLACEHOLDER_LENGTH = 6;
} // namespace
class RichEditorUndoManager;
namespace OHOS::Ace::NG {

class StyledStringRichEditorPattern : public RichEditorPattern {
    DECLARE_ACE_TYPE(StyledStringRichEditorPattern, RichEditorPattern);

public:
    StyledStringRichEditorPattern();
    ~StyledStringRichEditorPattern() override {}

    void BeforeCreateLayoutWrapper() override;
    void InsertValueInStyledString(const std::u16string& insertValue, bool shouldCommitInput = false);
    void InsertStyledStringByPaste(const RefPtr<SpanString>& spanString);

    void InsertValueInner(const std::u16string& insertValue, OperationType operationType,
        bool shouldCommitInput) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "InsertValueInner_SS");
        InsertValueInStyledString(insertValue, shouldCommitInput);
    }

    void HandleOnDragDropTextOperation(const std::u16string& insertValue, bool isDeleteSelect, bool isCopy) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "HandleOnDragDropTextOperation_SS");
        InsertValueInStyledString(insertValue, true);
    }

    void InsertValueByPaste(const std::u16string& insertValue) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "InsertValueByPaste_SS");
        InsertValueInStyledString(insertValue, true);
    }

    void AddSpansByPaste(const RefPtr<SpanString>& spanString) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddSpansByPaste_SS");
        InsertStyledStringByPaste(spanString);
    }

    int32_t AddImageSpan(const ImageSpanOptions& options, bool isPaste, int32_t index, bool updateCaret) override
    {
        TAG_LOGI(AceLogTag::ACE_RICH_TEXT, "AddImageSpan_SS");
        auto spanString = MakeRefPtr<SpanString>(options);
        InsertStyledStringByPaste(spanString);
        return 0;
    }

    void UpdateSelectStyledStringStyle(int32_t start, int32_t end, KeyCode code);
    void ReplacePlaceholderWithCustomSpan(const RefPtr<SpanItem>& spanItem, size_t& index, size_t& textIndex) override;
    void DeleteValueInStyledString(int32_t start, int32_t length, bool isIME = true, bool isUpdateCaret = true);
    void DeleteBackwardInStyledString(int32_t length);
    void DeleteForwardInStyledString(int32_t length, bool isIME = true);
    void DeleteBackwardInner(int32_t length) override
    {
        DeleteBackwardInStyledString(length);
    }

    void DeleteForwardInner(int32_t length) override
    {
        DeleteForwardInStyledString(length);
    }

    void DeleteToMaxLength(std::optional<int32_t> length) override
    {
        int32_t textContentLength = GetTextContentLength();
        if (length.value_or(INT_MAX) >= textContentLength) {
            return;
        }
        DeleteValueInStyledString(length.value_or(INT_MAX), textContentLength - length.value_or(INT_MAX));
    }

    int32_t GetTextContentLength() override
    {
        CHECK_NULL_RETURN(styledString_, 0);
        return styledString_->GetLength();
    }

    void HandleOnDragInsertStyledString(const RefPtr<SpanString>& spanString, bool isCopy = false);
    void HandleDragFromStyledString(const RefPtr<SpanString>& spanString, bool isCopy) override
    {
        HandleOnDragInsertStyledString(spanString, isCopy);
    }

    // Used for text replacement, without notifying developer caret change
    void DeleteByRange(OperationRecord* const record, int32_t start, int32_t end) override
    {
        auto length = end - start;
        CHECK_NULL_VOID(length > 0);
        lastCaretPosition_ = caretPosition_;
        caretPosition_ = std::clamp(start, 0, GetTextContentLength());
        DeleteValueInStyledString(start, length, true, false);
    }

    void HandleOnUndoAction() override;
    void HandleOnRedoAction() override;
    void HandleOnCopyStyledString();
    void OnCopyOperation(bool isUsingExternalKeyboard) override
    {
        HandleOnCopyStyledString();
    }

    void UpdateSelectSpanStyle(int32_t start, int32_t end, KeyCode code) override;
    bool IsCustomSpanInCaretPos(int32_t position, bool downStreamFirst) override;
    void SetStyledString(const RefPtr<SpanString>& value) override;
    void DeleteRangeInner(int32_t start, int32_t length) override
    {
        DeleteValueInStyledString(start, length, true, false);
    }

    void UpdateSpanItems(const std::list<RefPtr<NG::SpanItem>>& spanItems) override;

    void ProcessStyledString();
    void MountImageNode(const RefPtr<ImageSpanItem>& imageItem);
    void HandleStyledStringInsertion(RefPtr<SpanString> insertStyledString, const UndoRedoRecord& record,
        std::u16string& subValue, bool needReplaceInTextPreview, bool shouldCommitInput);
    RefPtr<SpanString> CreateStyledStringByTextStyle(
        const std::u16string& insertValue, const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle);
    RefPtr<FontSpan> CreateFontSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length);
    RefPtr<DecorationSpan> CreateDecorationSpanByTextStyle(
        const struct UpdateSpanStyle& updateSpanStyle, const TextStyle& textStyle, int32_t length);
    RefPtr<SpanString> CreateStyledStringByStyleBefore(int32_t start, const std::u16string& string);
    bool BeforeStyledStringChange(const UndoRedoRecord& record, bool isUndo = false);
    bool BeforeStyledStringChange(int32_t start, int32_t length, const std::u16string& string);
    bool BeforeStyledStringChange(int32_t start, int32_t length, const RefPtr<SpanString>& styledString);
    void AfterStyledStringChange(int32_t start, int32_t length, const std::u16string& string);
    void AfterStyledStringChange(const UndoRedoRecord& record, bool isUndo = false);
    void HandleUndoInStyledString(const UndoRedoRecord& record);
    void HandleRedoInStyledString(const UndoRedoRecord& record);
    void ApplyRecordInStyledString(const UndoRedoRecord& record);
    bool CheckStyledStringRangeValid(int32_t start, int32_t length);
    template<typename T>
    void UpdateSpansStyleInRange(int32_t start, int32_t end, const RefPtr<SpanBase>& baseSpan,
        std::function<RefPtr<T>(const RefPtr<T>&)>&& updateSpanFunc);
    void UpdateStyledStringFontStyle(int32_t start, int32_t end, const Font& font);
    void UpdateStyledStringDecorationType(int32_t start, int32_t end, const TextDecoration& type);
    void ClearOperationRecords() override;

private:
    friend class RichEditorUndoManager;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STYLED_STRING_RICH_EDITOR_RICH_EDITOR_PATTERN_H
