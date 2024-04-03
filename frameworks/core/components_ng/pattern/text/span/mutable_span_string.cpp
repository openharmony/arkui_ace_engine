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

#include "core/components_ng/pattern/text/span/mutable_span_string.h"

#include <iterator>

#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"

namespace OHOS::Ace {
std::wstring MutableSpanString::GetWideStringSubstr(const std::wstring& content, int32_t start, int32_t length)
{
    if (start >= content.length()) {
        return StringUtils::ToWstring("");
    }
    return content.substr(start, length);
}

std::wstring MutableSpanString::GetWideStringSubstr(const std::wstring& content, int32_t start)
{
    if (start >= content.length()) {
        return StringUtils::ToWstring("");
    }
    return content.substr(start);
}

void MutableSpanString::RemoveSpan(int32_t start, int32_t length, SpanType key)
{
    if (!CheckRange(start, length)) {
        return;
    }
    auto it = spansMap_.find(key);
    if (it == spansMap_.end()) {
        return;
    }
    auto spans = spansMap_[key];
    auto end = start + length;

    auto defaultSpan = MutableSpanString::GetDefaultSpan(key);
    defaultSpan->UpdateStartIndex(start);
    defaultSpan->UpdateEndIndex(end);
    ApplyToSpans(defaultSpan, { start, end }, SpanOperation::REMOVE);
    SplitInterval(spans, { start, end });
    SortSpans(spans);
    MergeIntervals(spans);
    if (spans.empty()) {
        spansMap_.erase(key);
    } else {
        spansMap_[key] = spans;
    }
}

void MutableSpanString::RemoveSpans(int32_t start, int32_t length)
{
    if (!CheckRange(start, length)) {
        return;
    }
    for (const auto& item : spansMap_) {
        RemoveSpan(start, length, item.first);
    }
}

void MutableSpanString::ReplaceSpan(int32_t start, int32_t length, const RefPtr<SpanBase>& span)
{
    if (!CheckRange(start, length)) {
        return;
    }
    RemoveSpans(start, length);
    AddSpan(span->GetSubSpan(start, start+length));
}

void MutableSpanString::UpdateSpansWithOffset(int32_t start, int32_t offset)
{
    for (auto& span : spans_) {
        if (span->interval.second > start && span->interval.first != start) {
            span->interval.second += offset;
        }
        if (span->interval.first > start) {
            span->interval.first += offset;
        }
    }
}

void MutableSpanString::UpdateSpanMapWithOffset(int32_t start, int32_t offset)
{
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& it : spans) {
            UpdateSpanBaseWithOffset(it, start, offset);
        }
        spansMap_[iter.first] = spans;
    }
}

void MutableSpanString::UpdateSpanBaseWithOffset(RefPtr<SpanBase>& span, int32_t start,
    int32_t offset)
{
    if (span->GetEndIndex() > start && span->GetStartIndex() != start) {
        span->UpdateEndIndex(span->GetEndIndex() + offset);
    }
    if (span->GetStartIndex() > start) {
        span->UpdateStartIndex(span->GetStartIndex() + offset);
    }
}

void MutableSpanString::ApplyReplaceStringToSpans(int32_t start, int32_t length,
    const std::string& other, SpanStringOperation op)
{
    int32_t end = start + length;
    for (auto it = spans_.begin(); it != spans_.end();) {
        auto intersection = (*it)->GetIntersectionInterval({start, end});
        auto spanItemStart = (*it)->interval.first;
        auto spanItemEnd = (*it)->interval.second;
        if (!intersection) {
            ++it;
            continue;
        }
        auto wContent = StringUtils::ToWstring((*it)->content);
        auto wOther = StringUtils::ToWstring(other);
        if (spanItemStart == start && op == SpanStringOperation::REPLACE) {
            (*it)->content = StringUtils::ToString(wOther + GetWideStringSubstr(wContent, length));
            (*it)->interval.second = StringUtils::ToWstring((*it)->content).length() + spanItemStart;
            ++it;
            continue;
        }
        if (spanItemStart == intersection->first && spanItemEnd == intersection->second) {
            it = spans_.erase(it);
            continue;
        }
        if (spanItemStart < intersection->first && intersection->second < spanItemEnd
            && op == SpanStringOperation::REMOVE) {
            auto newSpan = (*it)->GetSameStyleSpanItem();
            (*it)->interval = {spanItemStart, start};
            (*it)->content = StringUtils::ToString(wContent.substr(0, start - spanItemStart));
            newSpan->interval = {end, spanItemEnd};
            newSpan->content = StringUtils::ToString(wContent.substr(end - spanItemStart, spanItemEnd - end));
            ++it;
            spans_.insert(it, newSpan);
            continue;
        }
        if (intersection->first > spanItemStart) {
            if (op == SpanStringOperation::REMOVE) {
                (*it)->content = StringUtils::ToString(wContent.substr(0, start - spanItemStart));
                (*it)->interval.second = start;
            } else {
                (*it)->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart)
                    + wOther + GetWideStringSubstr(wContent, end - spanItemStart));
                (*it)->interval.second = std::max(end, spanItemEnd);
            }
        } else {
            (*it)->content = StringUtils::ToString(GetWideStringSubstr(wContent, end - spanItemStart));
            (*it)->interval.first = end;
        }
        ++it;
    }
}

void MutableSpanString::ApplyReplaceStringToSpanBase(int32_t start, int32_t length,
    const std::string& other, SpanStringOperation op)
{
    int32_t end = start + length;
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            spansMap_[iter.first] = {};
        }
        auto spans = spansMap_[iter.first];
        for (auto it = spans.begin(); it != spans.end();) {
            auto spanStart = (*it)->GetStartIndex();
            auto spanEnd = (*it)->GetEndIndex();
            auto intersection = (*it)->GetIntersectionInterval({ start, end });
            if (!intersection) {
                ++it;
                continue;
            }
            if (spanStart == start && op == SpanStringOperation::REPLACE) {
                ++it;
                continue;
            }
            if (intersection->first == spanStart && intersection->second == spanEnd) {
                it = spans.erase(it);
                continue;
            }
            if (spanStart < intersection->first && intersection->second < spanEnd
                && op == SpanStringOperation::REMOVE) {
                auto newSpan = (*it)->GetSubSpan(end, spanEnd);
                (*it)->UpdateEndIndex(start);
                ++it;
                spans.insert(it, newSpan);
                continue;
            }
            auto newEnd = (op != SpanStringOperation::REMOVE)?
                std::max(intersection->second, spanEnd): start;
            if (intersection->first > spanStart) {
                (*it)->UpdateEndIndex(newEnd);
            } else {
                (*it)->UpdateStartIndex(intersection->second);
            }
            ++it;
        }
        spansMap_[iter.first] = spans;
    }
}

void MutableSpanString::ReplaceString(int32_t start, int32_t length, const std::string& other)
{
    if (!CheckRange(start, length)) {
        return;
    }
    SpanStringOperation op = SpanStringOperation::REPLACE;
    auto wOther = StringUtils::ToWstring(other);
    auto otherLength = wOther.length();
    if (otherLength == 0) {
        op = SpanStringOperation::REMOVE;
    }
    int32_t end = start + length;
    auto text = GetWideString();
    SetString(StringUtils::ToString(text.substr(0, start) + wOther + text.substr(end)));
    ApplyReplaceStringToSpans(start, length, other, op);
    ApplyReplaceStringToSpanBase(start, length, other, op);
    UpdateSpansWithOffset(start, otherLength - length);
    UpdateSpanMapWithOffset(start, otherLength - length);
    NotifySpanWatcher();
    KeepSpansOrder();
}

void MutableSpanString::UpdateSpansAndSpanMapWithOffsetAfterInsert(int32_t start, int32_t offset, bool useFrontStyle)
{
    for (auto& span : spans_) {
        if (span->interval.first > start || (span->interval.first == start && useFrontStyle)) {
            span->interval.first += offset;
        }
        if (span->interval.second > start || (span->interval.second == start && useFrontStyle)) {
            span->interval.second += offset;
        }
    }
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& span : spans) {
            if (span->GetStartIndex() > start || (span->GetStartIndex() == start && useFrontStyle)) {
                span->UpdateStartIndex(span->GetStartIndex() + offset);
            }
            if (span->GetEndIndex() > start || (span->GetEndIndex() == start && useFrontStyle)) {
                span->UpdateEndIndex(span->GetEndIndex() + offset);
            }
        }
        spansMap_[iter.first] = spans;
    }
}

void MutableSpanString::InsertString(int32_t start, const std::string& other)
{
    if (other.length() == 0 || start > GetLength()) {
        return;
    }
    auto text = GetWideString();
    auto wOther = StringUtils::ToWstring(other);
    text = GetWideStringSubstr(text, 0, start) + wOther + GetWideStringSubstr(text, start);
    SetString(StringUtils::ToString(text));
    auto otherLength = wOther.length();
    bool useFrontStyle = false;
    for (auto& iter : spansMap_) {
        if (useFrontStyle || spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& span : spans) {
            if (span->GetStartIndex() <= start - 1 && span->GetEndIndex() > start - 1) {
                useFrontStyle = true;
                break;
            }
        }
    }
    for (auto& span : spans_) {
        auto spanItemStart = span->interval.first;
        auto spanItemEnd = span->interval.second;
        if (start == 0 && spanItemStart == 0) {
            span->content = other + span->content;
            break;
        }
        auto wContent = StringUtils::ToWstring(span->content);
        if (start - 1 >= spanItemStart && start - 1 < spanItemEnd && useFrontStyle) {
            span->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart)
                + wOther + GetWideStringSubstr(wContent, start - spanItemStart));
            break;
        }
        if (start >= spanItemStart && start < spanItemEnd) {
            span->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart)
                + wOther + GetWideStringSubstr(wContent, start - spanItemStart));
            break;
        }
    }
    UpdateSpansAndSpanMapWithOffsetAfterInsert(start, otherLength, useFrontStyle);
    NotifySpanWatcher();
    KeepSpansOrder();
}

void MutableSpanString::RemoveString(int32_t start, int32_t length)
{
    ReplaceString(start, length, "");
}

void MutableSpanString::ClearAllSpans()
{
    spansMap_.clear();
    spans_.clear();
    spans_.emplace_back(GetDefaultSpanItem(text_));
    NotifySpanWatcher();
}

void MutableSpanString::KeepSpansOrder()
{
    for (auto& it : spansMap_) {
        auto spans = spansMap_[it.first];
        SortSpans(spans);
        MergeIntervals(spans);
        spansMap_[it.first] = spans;
    }
}

void MutableSpanString::ReplaceSpanString(int32_t start, int32_t length, const RefPtr<SpanString>& spanString)
{
    if (length < 0 || start + length > GetLength()) {
        return;
    }
    if (length == 0) {
        InsertString(start, spanString->GetString());
    } else {
        ReplaceString(start, length, spanString->GetString());
    }
    RemoveSpans(start, spanString->GetLength());
    auto spanStringSpansMap = spanString->GetSpansMap();
    for (auto it = spanStringSpansMap.begin(); it != spanStringSpansMap.end(); ++it) {
        auto spans = spansMap_[it->first];
        auto spanStringSpans = spanStringSpansMap[it->first];
        for (auto& spanStringSpan : spanStringSpans) {
            auto span = spanStringSpan->GetSubSpan(spanStringSpan->GetStartIndex() + start,
                spanStringSpan->GetEndIndex() + start);
            ApplyToSpans(span, {spanStringSpan->GetStartIndex() + start,
                spanStringSpan->GetEndIndex() + start}, SpanOperation::ADD);
            spans.emplace_back(span);
        }
        spansMap_[it->first] = spans;
    }
    KeepSpansOrder();
}

void MutableSpanString::InsertSpanString(int32_t start, const RefPtr<SpanString>& spanString)
{
    ReplaceSpanString(start, 0, spanString);
}

void MutableSpanString::AppendSpanString(const RefPtr<SpanString>& spanString)
{
    ReplaceSpanString(GetLength(), 0, spanString);
}

RefPtr<SpanBase> MutableSpanString::GetDefaultSpan(SpanType type)
{
    switch (type) {
        case SpanType::Font:
            return MakeRefPtr<FontSpan>();
        case SpanType::Background:
        case SpanType::Decoration:
        case SpanType::Gesture:
            return nullptr;
    }
}
} // namespace OHOS::Ace