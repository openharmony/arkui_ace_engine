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

#include "base/utils/string_utils.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/text/span/span_objects.h"

namespace OHOS::Ace {
void SpanString::ApplyToSpans(const RefPtr<SpanBase>& span, std::pair<int32_t, int32_t> interval)
{
    for (auto it = spans_.begin(); it != spans_.end(); ++it) {
        auto intersection = (*it)->GetIntersectionInterval(interval);
        if (!intersection) {
            continue;
        }
        auto oldStart = (*it)->interval.first;
        auto oldEnd = (*it)->interval.second;
        if (oldStart == intersection->first && intersection->second == oldEnd) {
            span->ApplyToSpanItem(*it);
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
            span->ApplyToSpanItem(newSpan);

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
            span->ApplyToSpanItem(*it);
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
            span->ApplyToSpanItem(newSpan);
            it = spans_.insert(std::next(it), newSpan);
        }
    }
    NotifySpanWatcher();
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

void SpanString::AddSpan(const RefPtr<SpanBase>& span)
{
    if (!span) {
        return;
    }
    if (!CheckRange(span->GetStartIndex(), span->GetLength())) {
        return;
    }
    auto spans = spansMap_[span->GetSpanType()];
    auto start = span->GetStartIndex();
    auto end = span->GetEndIndex();
    if (spansMap_.find(span->GetSpanType()) == spansMap_.end()) {
        spansMap_[span->GetSpanType()].emplace_back(span);
        ApplyToSpans(span, { start, end });
        return;
    }
    ApplyToSpans(span, { start, end });
    SplitInterval(spans, { start, end });
    spans.emplace_back(span);
    SortSpans(spans);
    MergeIntervals(spans);
    spansMap_[span->GetSpanType()] = spans;
}
} // namespace OHOS::Ace