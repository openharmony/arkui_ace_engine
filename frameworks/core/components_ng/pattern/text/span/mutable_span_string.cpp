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

#include <algorithm>
#include <iterator>
#include <vector>

#include "base/memory/referenced.h"
#include "base/utils/string_utils.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace {

const std::vector<SpanType> specailTypes = { SpanType::Image, SpanType::CustomSpan };

void MutableSpanString::SplitSpansByNewLine()
{
    for (auto it = spans_.begin(); it != spans_.end();) {
        it = SplitSpansAndForward(it);
    }
}

void MutableSpanString::RemoveSpans(int32_t start, int32_t length)
{
    if (!CheckRange(start, length)) {
        return;
    }
    std::list<SpanType> typeList;
    auto iter = typeList.begin();
    for (auto& it : spansMap_) {
        auto spanKey = it.first;
        if (spanKey != SpanType::CustomSpan && spanKey != SpanType::Image) {
            iter = typeList.insert(iter, spanKey);
        }
    }
    for (const auto& spanKey : typeList) {
        if (spanKey != SpanType::CustomSpan && spanKey != SpanType::Image) {
            RemoveSpan(start, length, spanKey);
        }
    }
    RemoveSpecialSpans(start, length);
}

void MutableSpanString::RemoveSpecialSpans(int32_t start, int32_t length)
{
    if (!CheckRange(start, length)) {
        return;
    }
    int32_t end = start + length;
    std::list<RefPtr<SpanBase>> spanBaseList;
    auto iter = spanBaseList.begin();
    for (const auto& type : specailTypes) {
        auto spans = spansMap_[type];
        for (const auto& span : spans) {
            auto spanIndex = span->GetStartIndex();
            if (start <= spanIndex && spanIndex < end) {
                iter = spanBaseList.insert(iter, span);
            }
        }
    }
    spanBaseList.sort(
        [](const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b) { return a->GetStartIndex() < b->GetStartIndex(); });
    for (const auto& span : spanBaseList) {
        auto index = span->GetStartIndex();
        RemoveSpan(index, index + 1, span->GetSpanType());
    }
}

void MutableSpanString::ReplaceSpan(int32_t start, int32_t length, const RefPtr<SpanBase>& span)
{
    if (!CheckRange(start, length)) {
        return;
    }
    RemoveSpans(start, length);
    AddSpan(span->GetSubSpan(start, start + length));
}

void MutableSpanString::ApplyReplaceStringToSpans(
    int32_t start, int32_t length, const std::string& other, SpanStringOperation op)
{
    int32_t end = start + length;
    for (auto it = spans_.begin(); it != spans_.end();) {
        auto intersection = (*it)->GetIntersectionInterval({ start, end });
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
            it++;
            continue;
        }
        if (spanItemStart == intersection->first && spanItemEnd == intersection->second) {
            it = spans_.erase(it);
            continue;
        }
        if (spanItemStart < intersection->first && intersection->second < spanItemEnd &&
            op == SpanStringOperation::REMOVE) {
            auto newSpan = (*it)->GetSameStyleSpanItem();
            (*it)->interval = { spanItemStart, start };
            (*it)->content = StringUtils::ToString(wContent.substr(0, start - spanItemStart));
            newSpan->interval = { end, spanItemEnd };
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
                (*it)->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart) +
                                                       wOther + GetWideStringSubstr(wContent, end - spanItemStart));
                (*it)->interval.second = std::max(end, spanItemEnd);
            }
        } else {
            (*it)->content = StringUtils::ToString(GetWideStringSubstr(wContent, end - spanItemStart));
            (*it)->interval.first = end;
        }
        it++;
    }
}

void MutableSpanString::ApplyReplaceStringToSpanBase(
    int32_t start, int32_t length, const std::string& other, SpanStringOperation op)
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
            if (spanStart < intersection->first && intersection->second < spanEnd &&
                op == SpanStringOperation::REMOVE) {
                auto newSpan = (*it)->GetSubSpan(end, spanEnd);
                (*it)->UpdateEndIndex(start);
                ++it;
                spans.insert(it, newSpan);
                continue;
            }
            auto newEnd = (op != SpanStringOperation::REMOVE) ? std::max(intersection->second, spanEnd) : start;
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
    SplitSpansByNewLine();
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

bool MutableSpanString::InsertUseFrontStyle(int32_t start)
{
    if (start == GetLength()) {
        return true;
    }
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& span : spans) {
            if (span->GetStartIndex() <= start - 1 && span->GetEndIndex() > start - 1) {
                return true;
            }
        }
    }
    return false;
}

void MutableSpanString::InsertString(int32_t start, const std::string& other)
{
    auto len = GetLength();
    if (other.length() == 0 || start > len) {
        return;
    }
    auto isAround = IsInsertAroundSpecialNode(start);
    if (isAround != AroundSpecialNode::NONE) {
        InsertStringAroundSpecialNode(start, other, isAround);
        NotifySpanWatcher();
        return;
    }
    bool useFrontStyle = InsertUseFrontStyle(start);
    auto wOther = StringUtils::ToWstring(other);
    auto text = GetWideString();
    text = GetWideStringSubstr(text, 0, start) + wOther + GetWideStringSubstr(text, start);
    SetString(StringUtils::ToString(text));
    auto otherLength = wOther.length();
    if (len == 0) {
        spans_.clear();
        auto spanItem = MakeRefPtr<NG::SpanItem>();
        spanItem->content = other;
        spanItem->interval = { 0, otherLength };
        spans_.emplace_back(spanItem);
        NotifySpanWatcher();
        return;
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
            span->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart) + wOther +
                                                  GetWideStringSubstr(wContent, start - spanItemStart));
            break;
        }
        if (start >= spanItemStart && start < spanItemEnd) {
            span->content = StringUtils::ToString(GetWideStringSubstr(wContent, 0, start - spanItemStart) + wOther +
                                                  GetWideStringSubstr(wContent, start - spanItemStart));
            break;
        }
    }
    UpdateSpansAndSpanMapWithOffsetAfterInsert(start, otherLength, useFrontStyle);
    SplitSpansByNewLine();
    KeepSpansOrder();
    NotifySpanWatcher();
}

void MutableSpanString::RemoveString(int32_t start, int32_t length)
{
    ReplaceString(start, length, "");
    NotifySpanWatcher();
}

void MutableSpanString::RemoveSpecialpanText()
{
    std::list<int32_t> indexList;
    auto iter = indexList.begin();
    for (const auto& type : specailTypes) {
        auto spans = spansMap_[type];
        for (const auto& span : spans) {
            iter = indexList.insert(iter, span->GetStartIndex());
        }
    }
    indexList.sort([](const int32_t& a, const int32_t& b) { return a < b; });
    int32_t count = 0;
    for (const auto& index : indexList) {
        auto wStr = GetWideString();
        wStr.erase(index - count, 1);
        text_ = StringUtils::ToString(wStr);
        ++count;
    }
}

void MutableSpanString::ClearAllSpans()
{
    RemoveSpecialpanText();
    spansMap_.clear();
    spans_.clear();
    spans_.emplace_back(GetDefaultSpanItem(text_));
    SplitSpansByNewLine();
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
    if (length != 0) {
        RemoveString(start, length);
    }
    InsertSpanString(start, spanString);
}

void MutableSpanString::UpdateSpanAndSpanMapAfterInsertSpanString(int32_t start, int32_t offset)
{
    for (auto& span : spans_) {
        if (span->interval.first >= start) {
            span->interval.first += offset;
        }
        if (span->interval.second > start) {
            span->interval.second += offset;
        }
    }
    for (auto& iter : spansMap_) {
        if (spansMap_.find(iter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[iter.first];
        for (auto& span : spans) {
            if (span->GetStartIndex() >= start) {
                span->UpdateStartIndex(span->GetStartIndex() + offset);
            }
            if (span->GetEndIndex() > start) {
                span->UpdateEndIndex(span->GetEndIndex() + offset);
            }
        }
        spansMap_[iter.first] = spans;
    }
}

void MutableSpanString::ApplyInsertSpanStringToSpans(int32_t start, const RefPtr<SpanString>& spanString)
{
    auto offset = spanString->GetLength();
    for (auto it = spans_.begin(); it != spans_.end(); ++it) {
        auto spanItemStart = (*it)->interval.first;
        auto spanItemEnd = (*it)->interval.second;
        if (spanItemEnd < start || spanItemStart > start) {
            continue;
        }
        if (spanItemEnd != start) {
            auto newSpanItem = (*it)->GetSameStyleSpanItem();
            newSpanItem->interval.first = start + offset;
            newSpanItem->interval.second = spanItemEnd;
            auto wStr = StringUtils::ToWstring((*it)->content);
            newSpanItem->content = StringUtils::ToString(GetWideStringSubstr(wStr, start));
            (*it)->interval.second = start;
            (*it)->content = StringUtils::ToString(GetWideStringSubstr(wStr, 0, start - spanItemStart));
            ++it;
            it = spans_.insert(it, newSpanItem);
        } else {
            ++it;
        }
        auto otherSpans = spanString->GetSpanItems();
        for (auto rit = otherSpans.rbegin(); rit != otherSpans.rend(); ++rit) {
            auto newSpanItem = (*rit)->GetSameStyleSpanItem();
            newSpanItem->interval.first = (*rit)->interval.first + start;
            newSpanItem->interval.second = (*rit)->interval.second + start;
            newSpanItem->content = (*rit)->content;
            it = spans_.insert(it, newSpanItem);
        }
        break;
    }
}

void MutableSpanString::ApplyInsertSpanStringToSpanBase(int32_t start, const RefPtr<SpanString>& spanString)
{
    auto offset = spanString->GetLength();
    auto otherSpansMap = spanString->GetSpansMap();
    for (auto& iter : otherSpansMap) {
        auto spans = spansMap_[iter.first];
        for (auto it = spans.begin(); it != spans.end(); ++it) {
            auto spanItemStart = (*it)->GetStartIndex();
            auto spanItemEnd = (*it)->GetEndIndex();
            if (spanItemEnd < start || spanItemStart > start) {
                continue;
            }
            if (spanItemEnd != start) {
                auto newSpanItem = (*it)->GetSubSpan(start + offset, spanItemEnd);
                (*it)->UpdateEndIndex(start);
                ++it;
                spans.insert(it, newSpanItem);
            }
            break;
        }
        auto otherSpans = otherSpansMap[iter.first];
        for (auto& spanBase : otherSpans) {
            auto newSpanItem = spanBase->GetSubSpan(spanBase->GetStartIndex() + start, spanBase->GetEndIndex() + start);
            spans.emplace_back(newSpanItem);
        }
        spansMap_[iter.first] = spans;
    }
}

void MutableSpanString::InsertSpanString(int32_t start, const RefPtr<SpanString>& spanString)
{
    auto len = GetLength();
    if (start > len || spanString->GetLength() == 0) {
        return;
    }
    auto offset = spanString->GetLength();
    auto wContent = GetWideString();
    SetString(StringUtils::ToString(
        GetWideStringSubstr(wContent, 0, start) + spanString->GetWideString() + GetWideStringSubstr(wContent, start)));
    UpdateSpanAndSpanMapAfterInsertSpanString(start, offset);
    if (start == 0 || start == len) {
        auto it = start == 0 ? spans_.begin() : spans_.end();
        auto otherSpans = spanString->GetSpanItems();
        for (auto rit = otherSpans.rbegin(); rit != otherSpans.rend(); ++rit) {
            auto newSpanItem = (*rit)->GetSameStyleSpanItem();
            newSpanItem->interval.first = (*rit)->interval.first + start;
            newSpanItem->interval.second = (*rit)->interval.second + start;
            newSpanItem->content = (*rit)->content;
            it = spans_.insert(it, newSpanItem);
        }
    } else {
        ApplyInsertSpanStringToSpans(start, spanString);
    }
    ApplyInsertSpanStringToSpanBase(start, spanString);
    KeepSpansOrder();
}

void MutableSpanString::AppendSpanString(const RefPtr<SpanString>& spanString)
{
    InsertSpanString(GetLength(), spanString);
}

AroundSpecialNode MutableSpanString::IsInsertAroundSpecialNode(int32_t start)
{
    AroundSpecialNode res = AroundSpecialNode::NONE;
    if (spansMap_.find(SpanType::Image) == spansMap_.end() && spansMap_.find(SpanType::CustomSpan) == spansMap_.end()) {
        return res;
    }

    for (const auto& type : specailTypes) {
        auto specialSpans = spansMap_[type];
        for (const auto& span : specialSpans) {
            if (span->GetEndIndex() == start) {
                res = (res == AroundSpecialNode::NONE || res == AroundSpecialNode::AFTER) ? AroundSpecialNode::AFTER
                                                                                          : AroundSpecialNode::BETWEEN;
            }
            if (span->GetStartIndex() == start) {
                res = (res == AroundSpecialNode::NONE || res == AroundSpecialNode::BEFORE) ? AroundSpecialNode::BEFORE
                                                                                           : AroundSpecialNode::BETWEEN;
            }
        }
    }
    return res;
}

void MutableSpanString::InsertStringAroundSpecialNode(
    int32_t start, const std::string& str, AroundSpecialNode aroundMode)
{
    auto iter = spans_.begin();
    auto step = GetStepsByPosition(start);
    RefPtr<NG::SpanItem> spanItem = MakeRefPtr<NG::SpanItem>();
    std::advance(iter, step);
    if (aroundMode == AroundSpecialNode::BEFORE && step >= 1) {
        auto iter2 = spans_.begin();
        std::advance(iter2, step - 1);
        spanItem = (*iter2)->GetSameStyleSpanItem();
    } else if (aroundMode == AroundSpecialNode::AFTER && iter != spans_.end()) {
        spanItem = (*iter)->GetSameStyleSpanItem();
    }
    int32_t length = StringUtils::ToWstring(str).length();
    spanItem->content = str;
    spanItem->interval.first = start;
    spanItem->interval.second = start + length;
    auto beforeStr = GetWideStringSubstr(GetWideString(), 0, start);
    auto centerStr = StringUtils::ToWstring(str);
    auto afterStr = GetWideStringSubstr(GetWideString(), start);
    SetString(StringUtils::ToString(beforeStr + centerStr + afterStr));
    iter = spans_.insert(iter, spanItem);
    ++iter;
    for (; iter != spans_.end(); ++iter) {
        (*iter)->interval.first += length;
        (*iter)->interval.second += length;
    }

    SplitSpansByNewLine();

    for (auto& mapIter : spansMap_) {
        if (spansMap_.find(mapIter.first) == spansMap_.end()) {
            continue;
        }
        auto spans = spansMap_[mapIter.first];
        for (auto& span : spans) {
            if (span->GetStartIndex() > start ||
                (span->GetStartIndex() == start && aroundMode != AroundSpecialNode::AFTER)) {
                span->UpdateStartIndex(span->GetStartIndex() + length);
                span->UpdateEndIndex(span->GetEndIndex() + length);
            }
        }
        spansMap_[mapIter.first] = spans;
    }
}

bool MutableSpanString::IsSpeicalNode(int32_t location, SpanType speicalType)
{
    if (spansMap_.find(speicalType) == spansMap_.end()) {
        return false;
    }
    auto speicalList = spansMap_[speicalType];
    for (const auto& speicalNode : speicalList) {
        if (speicalNode->GetStartIndex() == location) {
            return true;
        }

        if (speicalNode->GetStartIndex() > location) {
            return false;
        }
    }
    return false;
}

void MutableSpanString::SetSpanWatcher(const WeakPtr<SpanWatcher>& watcher)
{
    watcher_ = watcher;
}

void MutableSpanString::NotifySpanWatcher()
{
    if (spans_.empty()) {
        spans_.emplace_back(GetDefaultSpanItem(""));
    }
    auto watcher = watcher_.Upgrade();
    if (watcher) {
        watcher->UpdateSpanItems(spans_);
    }
}
} // namespace OHOS::Ace