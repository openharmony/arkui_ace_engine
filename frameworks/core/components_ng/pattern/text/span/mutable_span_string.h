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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MUTABLE_SPAN_STRING_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MUTABLE_SPAN_STRING_H

#include <list>
#include <string>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/pattern/text/span/span_string.h"

namespace OHOS::Ace {
enum class AroundSpecialNode { AFTER = 0, BEFORE, BETWEEN, NONE };

class ACE_EXPORT MutableSpanString : public SpanString {
    DECLARE_ACE_TYPE(MutableSpanString, SpanString);

public:
    explicit MutableSpanString(const std::u16string& text) : SpanString(text) {}
    explicit MutableSpanString(const ImageSpanOptions& options) : SpanString(options) {}
    explicit MutableSpanString(RefPtr<CustomSpan>& span) : SpanString(span) {}
    void ReplaceString(int32_t start, int32_t length, const std::u16string& other);
    void InsertString(int32_t start, const std::u16string& other);
    void RemoveString(int32_t start, int32_t length);
    void ReplaceSpan(int32_t start, int32_t length, const RefPtr<SpanBase>& span);
    void RemoveSpans(int32_t start, int32_t length, bool removeSpecialSpan = true);
    void ClearAllSpans();
    void ReplaceSpanString(int32_t start, int32_t length, const RefPtr<SpanString>& spanString);
    void InsertSpanString(int32_t start, const RefPtr<SpanString>& spanString);
    void AppendSpanString(const RefPtr<SpanString>& spanString);
    bool IsSpeicalNode(int32_t location, SpanType speicalType);
    void SetSpanWatcher(const WeakPtr<SpanWatcher>& watcher);
    void NotifySpanWatcher();

private:
    WeakPtr<SpanWatcher> watcher_;
    void KeepSpansOrder();
    std::list<RefPtr<NG::SpanItem>>::iterator HandleSpanOperation(
        std::list<RefPtr<NG::SpanItem>>::iterator it, int32_t start, int32_t length,
        const std::u16string& other, SpanStringOperation op, const std::pair<int32_t, int32_t>& intersection);
    void ApplyReplaceStringToSpans(int32_t start, int32_t length, const std::u16string& other, SpanStringOperation op);
    void ApplyReplaceStringToSpanBase(int32_t start, int32_t length, const std::u16string& other,
        SpanStringOperation op);
    void ApplyInsertSpanStringToSpans(int32_t start, const RefPtr<SpanString>& spanString);
    void ApplyInsertSpanStringToSpanBase(int32_t start, const RefPtr<SpanString>& spanString);
    void SplitSpansByNewLine();
    bool InsertUseFrontStyle(int32_t start);
    void UpdateSpanAndSpanMapAfterInsertSpanString(int32_t start, int32_t offset);
    void UpdateSpansAndSpanMapWithOffsetAfterInsert(int32_t start, int32_t offset, bool useFrontStyle);
    AroundSpecialNode IsInsertAroundSpecialNode(int32_t start);
    void InsertStringAroundSpecialNode(int32_t start, const std::u16string& str, AroundSpecialNode aroundMode);
    void RemoveSpecialpanText();
    void RemoveSpecialSpans(int32_t start, int32_t length);
    void ProcessSpanBaseList(std::list<RefPtr<SpanBase>>& spans, int32_t start,
        int32_t end, const std::u16string& other, SpanStringOperation op, SpanType spanType);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MUTABLE_SPAN_STRING_H
