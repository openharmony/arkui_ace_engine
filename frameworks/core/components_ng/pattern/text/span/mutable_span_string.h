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

class ACE_EXPORT MutableSpanString : public SpanString {
    DECLARE_ACE_TYPE(MutableSpanString, SpanString);

public:
    explicit MutableSpanString(const std::string& text) : SpanString(text) {}
    MutableSpanString(const std::string& text, std::vector<RefPtr<SpanBase>>& spans)
        : SpanString(text, spans) {}
    void ReplaceString(int32_t start, int32_t length, const std::string& other);
    void InsertString(int32_t start, const std::string& other);
    void RemoveString(int32_t start, int32_t length);
    void ReplaceSpan(int32_t start, int32_t length, const RefPtr<SpanBase>& span);
    void RemoveSpan(int32_t start, int32_t length, SpanType key);
    void RemoveSpans(int32_t start, int32_t length);
    void ClearAllSpans();
    void ReplaceSpanString(int32_t start, int32_t length, const RefPtr<SpanString>& spanString);
    void InsertSpanString(int32_t start, const RefPtr<SpanString>& spanString);
    void AppendSpanString(const RefPtr<SpanString>& spanString);

private:
    void KeepSpansOrder();
    void ApplyReplaceStringToSpans(int32_t start, int32_t length, const std::string& other, SpanStringOperation op);
    void ApplyReplaceStringToSpanBase(int32_t start, int32_t length, const std::string& other, SpanStringOperation op);
    static RefPtr<SpanBase> GetDefaultSpan(SpanType type);
    static std::wstring GetWideStringSubstr(const std::wstring& content, int32_t start);
    static std::wstring GetWideStringSubstr(const std::wstring& content, int32_t start, int32_t length);
    bool InsertUseFrontStyle(int32_t start);
    void UpdateSpansAndSpanMapWithOffsetAfterInsert(int32_t start, int32_t offset, bool useFrontStyle);
    void UpdateSpansWithOffset(int32_t start, int32_t offset);
    void UpdateSpanMapWithOffset(int32_t start, int32_t offset);
    void UpdateSpanBaseWithOffset(RefPtr<SpanBase>& span, int32_t start, int32_t offset);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_TEXT_SPAN_MUTABLE_SPAN_STRING_H
