
/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_VALUE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_VALUE_H

#include "core/components_ng/pattern/rich_editor/rich_editor_abstract_span_result.h"
#include "core/common/ime/text_range.h"

namespace OHOS::Ace::NG {

class ACE_FORCE_EXPORT RichEditorInsertValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorInsertValue, BaseEventInfo);
public:
    RichEditorInsertValue() : BaseEventInfo("RichEditorInsertValue") {}
    ~RichEditorInsertValue() override = default;
    void SetInsertOffset(int32_t insertOffset)
    {
        insertOffset_ = insertOffset;
    }

    int32_t GetInsertOffset() const
    {
        return insertOffset_;
    }

    void SetInsertValue(const std::u16string& insertValue)
    {
        insertValue_ = insertValue;
    }

    void SetPreviewText(const std::u16string& previewText)
    {
        previewText_ = previewText;
    }

    const std::u16string& GetInsertValue() const
    {
        return insertValue_;
    }

    const std::u16string& GetPreviewText() const
    {
        return previewText_;
    }

private:
    int32_t insertOffset_ = 0;
    std::u16string insertValue_;
    std::u16string previewText_;
};

enum class RichEditorDeleteDirection { BACKWARD = 0, FORWARD };

class ACE_FORCE_EXPORT RichEditorDeleteValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorDeleteValue, BaseEventInfo);
public:
    RichEditorDeleteValue() : BaseEventInfo("RichEditorDeleteValue") {}
    ~RichEditorDeleteValue() = default;
    void SetOffset(int32_t offset)
    {
        offset_ = offset;
    }

    int32_t GetOffset() const
    {
        return offset_;
    }

    void SetRichEditorDeleteDirection(RichEditorDeleteDirection direction)
    {
        direction_ = direction;
    }

    RichEditorDeleteDirection GetRichEditorDeleteDirection() const
    {
        return direction_;
    }

    void SetLength(int32_t length)
    {
        length_ = length;
    }

    int32_t GetLength() const
    {
        return length_;
    }

    void SetRichEditorDeleteSpans(const RichEditorAbstractSpanResult& deleteSpan)
    {
        richEditorDeleteSpans_.emplace_back(deleteSpan);
    }

    void ResetRichEditorDeleteSpans()
    {
        richEditorDeleteSpans_.clear();
    }

    const std::list<RichEditorAbstractSpanResult>& GetRichEditorDeleteSpans() const
    {
        return richEditorDeleteSpans_;
    }

private:
    int32_t offset_ = 0;
    RichEditorDeleteDirection direction_ = RichEditorDeleteDirection::BACKWARD;
    int32_t length_ = 0;
    std::list<RichEditorAbstractSpanResult> richEditorDeleteSpans_;
};

class ACE_FORCE_EXPORT RichEditorChangeValue : public BaseEventInfo {
    DECLARE_ACE_TYPE(RichEditorChangeValue, BaseEventInfo);
#ifndef ACE_UNITTEST
private:
#else
public:
#endif
    RichEditorChangeValue() : BaseEventInfo("RichEditorChangeValue") {}
public:
    RichEditorChangeValue(TextChangeReason reason) : RichEditorChangeValue()
    {
        changeReason_ = reason;
    }
    ~RichEditorChangeValue() = default;

    void SetRichEditorOriginalSpans(const RichEditorAbstractSpanResult& span)
    {
        originalSpans_.emplace_back(span);
    }

    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorOriginalSpans() const
    {
        return originalSpans_;
    }

    void SetRichEditorReplacedSpans(const RichEditorAbstractSpanResult& span)
    {
        replacedSpans_.emplace_back(span);
    }

    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedSpans() const
    {
        return replacedSpans_;
    }

    void SetRichEditorReplacedImageSpans(const RichEditorAbstractSpanResult& span)
    {
        replacedImageSpans_.emplace_back(span);
    }

    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedImageSpans() const
    {
        return replacedImageSpans_;
    }

    void SetRichEditorReplacedSymbolSpans(const RichEditorAbstractSpanResult& span)
    {
        replacedSymbolSpans_.emplace_back(span);
    }

    const std::vector<RichEditorAbstractSpanResult>& GetRichEditorReplacedSymbolSpans() const
    {
        return replacedSymbolSpans_;
    }

    void SetRangeBefore(const TextRange& rangeBefore)
    {
        rangeBefore_ = rangeBefore;
    }

    TextRange GetRangeBefore() const
    {
        return rangeBefore_;
    }

    void SetRangeAfter(const TextRange& rangeAfter)
    {
        rangeAfter_ = rangeAfter;
    }

    TextRange GetRangeAfter() const
    {
        return rangeAfter_;
    }

    TextChangeReason GetChangeReason() const
    {
        return changeReason_;
    }
    void reset();

private:
    std::vector<RichEditorAbstractSpanResult> originalSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedImageSpans_;
    std::vector<RichEditorAbstractSpanResult> replacedSymbolSpans_;
    TextRange rangeBefore_;
    TextRange rangeAfter_;
    TextChangeReason changeReason_ = TextChangeReason::UNKNOWN;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_VALUE_H