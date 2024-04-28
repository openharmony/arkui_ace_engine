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

#include "core/components_ng/pattern/text/span/span_string.h"

#include <iterator>
#include <utility>

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace {
SpanString::SpanString(const std::string& text) : text_(text)
{
    auto spanItem = MakeRefPtr<NG::SpanItem>();
    spanItem->content = text;
    spanItem->interval = { 0, StringUtils::ToWstring(text).length() };
    spans_.emplace_back(spanItem);
}

SpanString::SpanString(const ImageSpanOptions& options) : text_(" ")
{
    auto spanItem = MakeRefPtr<NG::ImageSpanItem>();
    spanItem->options = options;
    spanItem->content = " ";
    spanItem->interval = { 0, 1 };
    spans_.emplace_back(spanItem);
    spansMap_[SpanType::Image].emplace_back(MakeRefPtr<ImageSpan>(options));
}

SpanString::SpanString(RefPtr<CustomSpan>& span) : text_(" ")
{
    auto spanItem = MakeRefPtr<NG::CustomSpanItem>();
    spanItem->content = " ";
    spanItem->interval = { 0, 1 };
    spanItem->onMeasure = span->GetOnMeasure();
    spanItem->onDraw = span->GetOnDraw();
    spans_.emplace_back(spanItem);
    spansMap_[SpanType::CustomSpan].emplace_back(span);
}

SpanString::~SpanString()
{
    spansMap_.clear();
    spans_.clear();
}

void SpanString::ApplyToSpans(
    const RefPtr<SpanBase>& span, std::pair<int32_t, int32_t> interval, SpanOperation operation)
{
    for (auto it = spans_.begin(); it != spans_.end(); ++it) {
        auto intersection = (*it)->GetIntersectionInterval(interval);
        if (!intersection) {
            continue;
        }
        auto oldStart = (*it)->interval.first;
        auto oldEnd = (*it)->interval.second;
        if (oldStart == intersection->first && intersection->second == oldEnd) {
            span->ApplyToSpanItem(*it, operation);
            continue;
        }

        auto wContent = StringUtils::ToWstring((*it)->content);
        auto newSpan = (*it)->GetSameStyleSpanItem();
        if (oldStart < intersection->first && intersection->second < oldEnd) {
            (*it)->interval = { oldStart, intersection->first };
            (*it)->content = StringUtils::ToString(wContent.substr(0, intersection->first - oldStart));

            newSpan->interval = { intersection->first, intersection->second };
            newSpan->content = StringUtils::ToString(
                wContent.substr(intersection->first - oldStart, intersection->second - intersection->first));
            span->ApplyToSpanItem(newSpan, operation);

            auto newSpan2 = (*it)->GetSameStyleSpanItem();
            newSpan2->interval = { intersection->second, oldEnd };
            newSpan2->content = StringUtils::ToString(wContent.substr(intersection->second - oldStart));
            it = spans_.insert(std::next(it), newSpan);
            it = spans_.insert(std::next(it), newSpan2);
            continue;
        }

        if (oldEnd > intersection->second) {
            (*it)->content = StringUtils::ToString(wContent.substr(0, intersection->second - oldStart));
            (*it)->interval = { oldStart, intersection->second };
            span->ApplyToSpanItem(*it, operation);
            newSpan->interval = { intersection->second, oldEnd };
            newSpan->content = StringUtils::ToString(wContent.substr(intersection->second - oldStart));
            it = spans_.insert(std::next(it), newSpan);
            continue;
        }

        if (intersection->first > oldStart) {
            (*it)->content = StringUtils::ToString(wContent.substr(0, intersection->first - oldStart));
            (*it)->interval = { oldStart, intersection->first };
            newSpan->interval = { intersection->first, oldEnd };
            newSpan->content = StringUtils::ToString(wContent.substr(intersection->first - oldStart));
            span->ApplyToSpanItem(newSpan, operation);
            it = spans_.insert(std::next(it), newSpan);
        }
    }
}

void SpanString::SplitInterval(std::list<RefPtr<SpanBase>>& spans, std::pair<int32_t, int32_t> interval)
{
    std::list<RefPtr<SpanBase>> newSpans;
    for (auto it = spans.begin(); it != spans.end();) {
        auto intersection = (*it)->GetIntersectionInterval(interval);
        if (!intersection) {
            ++it;
            continue;
        }
        auto oldStart = (*it)->GetStartIndex();
        auto oldEnd = (*it)->GetEndIndex();
        if (intersection->first == oldStart && intersection->second == oldEnd) {
            it = spans.erase(it);
            continue;
        }
        if (oldStart < intersection->first && intersection->second < oldEnd) {
            newSpans.emplace_back((*it)->GetSubSpan(oldStart, intersection->first));
            newSpans.emplace_back((*it)->GetSubSpan(intersection->second, oldEnd));
            it = spans.erase(it);
            continue;
        }
        if (oldEnd > intersection->second) {
            (*it)->UpdateStartIndex(intersection->second);
            ++it;
            continue;
        }
        if (intersection->first > oldStart) {
            (*it)->UpdateEndIndex(intersection->first);
            ++it;
        }
    }
    spans.merge(newSpans);
}

void SpanString::SortSpans(std::list<RefPtr<SpanBase>>& spans)
{
    spans.sort(
        [](const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b) { return a->GetStartIndex() < b->GetStartIndex(); });
}

bool SpanString::CanMerge(const RefPtr<SpanBase>& a, const RefPtr<SpanBase>& b)
{
    return a->GetEndIndex() >= b->GetStartIndex() && a->IsAttributesEqual(b);
}

void SpanString::MergeIntervals(std::list<RefPtr<SpanBase>>& spans)
{
    auto it = spans.begin();
    while (it != spans.end()) {
        auto spanType = (*it)->GetSpanType();
        if (spanType == SpanType::Image || spanType == SpanType::CustomSpan) {
            return;
        }
        auto current = it++;
        if (it != spans.end() && CanMerge(*current, *it)) {
            (*current)->UpdateStartIndex(std::min((*current)->GetStartIndex(), (*it)->GetStartIndex()));
            (*current)->UpdateEndIndex(std::max((*current)->GetEndIndex(), (*it)->GetEndIndex()));
            spans.erase(it++);
            if (it == spans.end()) {
                break;
            }
            it = current;
        }
    }
}

int32_t SpanString::GetStepsByPosition(int32_t pos)
{
    if (pos == 0) {
        return 0;
    }
    int32_t step = 0;
    for (auto iter = spans_.begin(); iter != spans_.end(); ++iter) {
        if ((*iter)->interval.first == pos) {
            return step;
        }
        if ((*iter)->interval.first < pos && pos < (*iter)->interval.second) {
            auto spanItem = (*iter)->GetSameStyleSpanItem();
            spanItem->interval.first = pos;
            spanItem->interval.second = (*iter)->interval.second;
            auto wStr = StringUtils::ToWstring(spanItem->content);
            auto start = (*iter)->interval.first;
            spanItem->content = StringUtils::ToString(wStr.substr(pos - start));
            spans_.insert(std::next(iter), spanItem);
            (*iter)->interval.second = pos;
            (*iter)->content = StringUtils::ToString(wStr.substr(0, pos - start));
            return step;
        }
        step++;
    }
    return step;
}

void SpanString::AddSpecialSpan(const RefPtr<SpanBase>& span, SpanType type)
{
    auto iter = spans_.begin();
    auto step = GetStepsByPosition(span->GetStartIndex());
    std::advance(iter, step);
    if (type == SpanType::Image) {
        auto imageSpan = DynamicCast<ImageSpan>(span);
        CHECK_NULL_VOID(imageSpan);
        auto spanItem = MakeRefPtr<NG::ImageSpanItem>();
        spanItem->content = " ";
        spanItem->interval.first = span->GetStartIndex();
        spanItem->interval.second = span->GetEndIndex();
        spanItem->SetImageSpanOptions(imageSpan->GetImageSpanOptions());
        iter = spans_.insert(iter, spanItem);
    } else if (type == SpanType::CustomSpan) {
        auto customSpan = AceType::DynamicCast<CustomSpan>(span);
        CHECK_NULL_VOID(customSpan);
        auto spanItem = MakeRefPtr<NG::CustomSpanItem>();
        spanItem->content = " ";
        spanItem->interval.first = span->GetStartIndex();
        spanItem->interval.second = span->GetEndIndex();
        spanItem->onDraw = customSpan->GetOnDraw();
        spanItem->onMeasure = customSpan->GetOnMeasure();
        iter = spans_.insert(iter, spanItem);
    }
    for (++iter; iter != spans_.end(); ++iter) {
        ++(*iter)->interval.first;
        ++(*iter)->interval.second;
    }

    if (spansMap_.find(type) == spansMap_.end()) {
        spansMap_[type].emplace_back(span);
    } else {
        auto specialList = spansMap_[type];
        int32_t step = 0;
        for (const auto& specialSpan : specialList) {
            if (specialSpan->GetStartIndex() >= span->GetStartIndex()) {
                break;
            }
            ++step;
        }
        auto iter = specialList.begin();
        std::advance(iter, step);
        iter = specialList.insert(iter, span);
        for (++iter; iter != specialList.end(); ++iter) {
            (*iter)->UpdateStartIndex((*iter)->GetStartIndex() + 1);
            (*iter)->UpdateEndIndex((*iter)->GetEndIndex() + 1);
        }
        spansMap_[type] = specialList;
    }
}

void SpanString::AddSpan(const RefPtr<SpanBase>& span)
{
    if (!span || !CheckRange(span)) {
        return;
    }
    if (span->GetSpanType() == SpanType::Image) {
        AddSpecialSpan(span, SpanType::Image);
        return;
    }
    if (span->GetSpanType() == SpanType::CustomSpan) {
        AddSpecialSpan(span, SpanType::CustomSpan);
        return;
    }
    auto start = span->GetStartIndex();
    auto end = span->GetEndIndex();
    if (spansMap_.find(span->GetSpanType()) == spansMap_.end()) {
        spansMap_[span->GetSpanType()].emplace_back(span);
        ApplyToSpans(span, { start, end }, SpanOperation::ADD);
        return;
    }
    RemoveSpan(start, span->GetLength(), span->GetSpanType());
    auto spans = spansMap_[span->GetSpanType()];
    ApplyToSpans(span, { start, end }, SpanOperation::ADD);
    SplitInterval(spans, { start, end });
    spans.emplace_back(span);
    SortSpans(spans);
    MergeIntervals(spans);
    spansMap_[span->GetSpanType()] = spans;
}

void SpanString::RemoveSpan(int32_t start, int32_t length, SpanType key)
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
    if (key == SpanType::Image) {
        RemoveSpecialSpan(start, end, key);
        return;
    }
    if (key == SpanType::CustomSpan) {
        RemoveSpecialSpan(start, end, key);
        return;
    }
    auto defaultSpan = GetDefaultSpan(key);
    CHECK_NULL_VOID(defaultSpan);
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

RefPtr<SpanBase> SpanString::GetDefaultSpan(SpanType type)
{
    switch (type) {
        case SpanType::Font:
            return MakeRefPtr<FontSpan>();
        case SpanType::TextShadow:
            return MakeRefPtr<TextShadowSpan>();
        case SpanType::Gesture:
            return MakeRefPtr<GestureSpan>();
        case SpanType::Decoration:
            return MakeRefPtr<DecorationSpan>();
        case SpanType::BaselineOffset:
            return MakeRefPtr<BaselineOffsetSpan>();
        case SpanType::LetterSpacing:
            return MakeRefPtr<LetterSpacingSpan>();
        default:
            return nullptr;
    }
}

bool SpanString::CheckRange(const RefPtr<SpanBase>& spanBase) const
{
    auto start = spanBase->GetStartIndex();
    auto length = spanBase->GetLength();
    if (length <= 0) {
        return false;
    }
    auto spanType = spanBase->GetSpanType();
    auto len = spanType == SpanType::Image || spanType == SpanType::CustomSpan ? GetLength() + 1 : GetLength();
    auto end = start + length;

    if (start > len || end > len) {
        return false;
    }

    if (start < 0) {
        return false;
    }

    return true;
}

bool SpanString::CheckRange(int32_t start, int32_t length, bool allowLengthZero) const
{
    if (length < 0 || (length == 0 && !allowLengthZero)) {
        return false;
    }

    auto len = GetLength();
    auto end = start + length;

    if (start > len || end > len) {
        return false;
    }

    if (start < 0) {
        return false;
    }

    return true;
}

RefPtr<NG::SpanItem> SpanString::GetDefaultSpanItem(const std::string& text)
{
    auto spanItem = MakeRefPtr<NG::SpanItem>();
    spanItem->content = text;
    spanItem->interval = { 0, StringUtils::ToWstring(text).length() };
    return spanItem;
}

void SpanString::SetString(const std::string& text)
{
    text_ = text;
}

const std::string& SpanString::GetString() const
{
    return text_;
}

std::wstring SpanString::GetWideString()
{
    return StringUtils::ToWstring(text_);
}

int32_t SpanString::GetLength() const
{
    return StringUtils::ToWstring(text_).length();
}

bool SpanString::IsEqualToSpanString(const RefPtr<SpanString>& other) const
{
    return *this == *other;
}

RefPtr<SpanString> SpanString::GetSubSpanString(int32_t start, int32_t length) const
{
    if (!CheckRange(start, length)) {
        RefPtr<SpanString> span = AceType::MakeRefPtr<SpanString>("");
        return span;
    }
    int32_t end = start + length;
    RefPtr<SpanString> span =
        AceType::MakeRefPtr<SpanString>(StringUtils::ToString(StringUtils::ToWstring(text_).substr(start, length)));
    std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>> subMap;
    for (const auto& map : spansMap_) {
        auto subList = GetSubSpanList(start, length, map.second);
        if (!subList.empty()) {
            subMap.insert({ map.first, subList });
        }
    }
    span->spansMap_ = subMap;

    std::list<RefPtr<NG::SpanItem>> subSpans_;
    for (const auto& spanItem : spans_) {
        int32_t spanStart = spanItem->interval.first;
        int32_t spanEnd = spanItem->interval.second;
        if ((start <= spanStart && spanStart < end) || (start <= spanEnd && spanEnd < end)) {
            auto oldStart = spanStart;
            auto oldEnd = spanEnd;
            spanStart = spanStart <= start ? 0 : spanStart - start;
            spanEnd = spanEnd < end ? spanEnd - start : end - start;
            auto newSpanItem = spanItem->GetSameStyleSpanItem();
            newSpanItem->interval = { spanStart, spanEnd };
            newSpanItem->content = StringUtils::ToString(
                StringUtils::ToWstring(spanItem->content)
                    .substr(std::max(start - oldStart, 0), std::min(spanEnd, oldEnd) - std::max(start, oldStart)));
            subSpans_.emplace_back(newSpanItem);
        }
    }
    span->spans_ = subSpans_;
    return span;
}

std::list<RefPtr<SpanBase>> SpanString::GetSubSpanList(
    int32_t start, int32_t length, const std::list<RefPtr<SpanBase>>& spans) const
{
    std::list<RefPtr<SpanBase>> res;
    int32_t end = start + length;
    for (auto& span : spans) {
        auto intersection = span->GetIntersectionInterval({ start, end });
        if (intersection) {
            int32_t spanStart = span->GetStartIndex();
            int32_t spanEnd = span->GetEndIndex();
            spanStart = spanStart <= start ? 0 : spanStart - start;
            spanEnd = spanEnd < end ? spanEnd - start : end - start;
            if (spanStart == spanEnd) {
                continue;
            }
            res.emplace_back(span->GetSubSpan(spanStart, spanEnd));
        }
    }
    return res;
}

const std::unordered_map<SpanType, std::list<RefPtr<SpanBase>>>& SpanString::GetSpansMap() const
{
    return spansMap_;
}

std::vector<RefPtr<SpanBase>> SpanString::GetSpans(int32_t start, int32_t length) const
{
    std::vector<RefPtr<SpanBase>> res;
    if (!CheckRange(start, length)) {
        return res;
    }

    for (const auto& map : spansMap_) {
        auto spans = GetSpans(start, length, map.first);
        res.insert(res.begin(), spans.begin(), spans.end());
    }
    return res;
}

std::vector<RefPtr<SpanBase>> SpanString::GetSpans(int32_t start, int32_t length, SpanType spanType) const
{
    std::vector<RefPtr<SpanBase>> res;
    if (!CheckRange(start, length)) {
        return res;
    }
    int32_t end = start + length;
    RefPtr<SpanBase> span;
    while ((span = GetSpan(start, length, spanType)) != nullptr) {
        res.emplace_back(span);
        start = span->GetEndIndex();
        length = end - start;
    }
    return res;
}

RefPtr<SpanBase> SpanString::GetSpan(int32_t start, int32_t length, SpanType spanType) const
{
    if (!CheckRange(start, length) || spansMap_.find(spanType) == spansMap_.end()) {
        return nullptr;
    }
    int32_t end = start + length;
    auto spanBaseList = spansMap_.find(spanType)->second;
    for (auto& spanBase : spanBaseList) {
        auto intersection = spanBase->GetIntersectionInterval({ start, end });
        if (intersection) {
            int32_t newStart = intersection->first;
            int32_t newEnd = intersection->second;
            if (newStart == newEnd) {
                continue;
            }
            return spanBase->GetSubSpan(newStart, newEnd);
        }
    }
    return nullptr;
}

bool SpanString::operator==(const SpanString& other) const
{
    if (text_ != other.text_) {
        return false;
    }
    auto size = spansMap_.size() - (spansMap_.find(SpanType::Gesture) == spansMap_.end() ? 0 : 1);
    auto sizeOther =
        other.spansMap_.size() - (other.spansMap_.find(SpanType::Gesture) == other.spansMap_.end() ? 0 : 1);
    if (size != sizeOther) {
        return false;
    }

    for (const auto& map : spansMap_) {
        if (map.first == SpanType::Gesture) {
            continue;
        }
        auto spansOtherMap = other.spansMap_.find(map.first);
        if (spansOtherMap == other.spansMap_.end()) {
            return false;
        }
        auto spans = map.second;
        auto spansOther = spansOtherMap->second;
        if (spans.size() != spansOther.size()) {
            return false;
        }
        for (auto spansItr = spans.begin(), spansOtherItr = spansOther.begin();
             spansItr != spans.end() && spansOtherItr != spansOther.end(); ++spansItr, ++spansOtherItr) {
            if (!(*spansItr)->IsAttributesEqual(*spansOtherItr) ||
                (*spansItr)->GetEndIndex() != (*spansOtherItr)->GetEndIndex() ||
                (*spansItr)->GetStartIndex() != (*spansOtherItr)->GetStartIndex()) {
                return false;
            }
        }
    }
    return true;
}

const std::list<RefPtr<NG::SpanItem>>& SpanString::GetSpanItems() const
{
    return spans_;
}

void SpanString::BindWithSpans(const std::vector<RefPtr<SpanBase>>& spans)
{
    for (auto& span : spans) {
        AddSpan(span);
    }
}

void SpanString::UpdateSpansWithOffset(int32_t start, int32_t offset)
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

void SpanString::UpdateSpanMapWithOffset(int32_t start, int32_t offset)
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

void SpanString::UpdateSpanBaseWithOffset(RefPtr<SpanBase>& span, int32_t start, int32_t offset)
{
    if (span->GetEndIndex() > start && span->GetStartIndex() != start) {
        span->UpdateEndIndex(span->GetEndIndex() + offset);
    }
    if (span->GetStartIndex() > start) {
        span->UpdateStartIndex(span->GetStartIndex() + offset);
    }
}

void SpanString::RemoveSpecialSpan(int32_t start, int32_t end, SpanType type)
{
    auto spans = spansMap_[type];
    int32_t count = 0;
    for (auto iter = spans.begin(); iter != spans.end();) {
        if ((*iter)->GetStartIndex() >= start && (*iter)->GetStartIndex() < end - count) {
            auto wStr = GetWideString();
            wStr.erase((*iter)->GetStartIndex(), 1);
            text_ = StringUtils::ToString(wStr);
            UpdateSpanMapWithOffset((*iter)->GetStartIndex(), -1);
            iter = spans.erase(iter);
            ++count;
            continue;
        }
        ++iter;
    }
    if (spans.empty()) {
        spansMap_.erase(type);
    } else {
        spansMap_[type] = spans;
    }
    count = 0;
    for (auto iter = spans_.begin(); iter != spans_.end();) {
        if ((*iter)->interval.first >= start && (*iter)->interval.first < end - count
            && ((type == SpanType::Image && (*iter)->spanItemType == NG::SpanItemType::IMAGE)
                || (type == SpanType::CustomSpan && (*iter)->spanItemType == NG::SpanItemType::CustomSpan))) {
            UpdateSpansWithOffset((*iter)->interval.first, -1);
            iter = spans_.erase(iter);
            ++count;
            continue;
        }
        ++iter;
    }
}
} // namespace OHOS::Ace