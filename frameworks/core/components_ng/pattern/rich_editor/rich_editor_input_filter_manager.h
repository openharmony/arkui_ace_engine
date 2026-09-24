/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_INPUT_FILTER_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_INPUT_FILTER_MANAGER_H

#include <functional>
#include <string>
#include <vector>

#include "core/common/ime/text_input_filter.h"
#include "core/components/common/properties/text_enums.h"
#include "core/components_ng/pattern/text/span/mutable_span_string.h"

namespace OHOS::Ace::NG {

/**
 * @brief Manages regex input filtering for RichEditor.
 * Stores the filter pattern and encapsulates all filter logic that
 * has no direct dependency on RichEditorPattern.
 */
class RichEditorInputFilterManager {
public:
    RichEditorInputFilterManager() = default;
    ~RichEditorInputFilterManager() = default;

    void SetFilter(const std::u16string& filter)
    {
        filter_ = filter;
    }

    /**
     * @brief Check if the filter is anchored (^ or $).
     * Anchored regex requires full-content re-validation after insertion
     * because individual matches may not hold after content combination.
     * Character-level regex (e.g. [0-9]) does not need full-content check.
     */
    bool IsAnchoredFilter() const
    {
        if (filter_.empty()) {
            return false;
        }
        return filter_.front() == u'^' || filter_.back() == u'$';
    }

    /**
     * @brief Filter plain text in-place using the stored regex.
     * @param text Text to filter (modified in-place).
     * @param onError Callback invoked with rejected characters.
     */
    void FilterText(std::u16string& text, const std::function<bool(const std::u16string&)>& onError) const
    {
        CHECK_NULL_VOID(!filter_.empty());
        CHECK_NULL_VOID(onError);
        TextInputFilter::FilterWithEvent(filter_, text, onError);
    }

    /**
     * @brief Check whether non-character content (U+FFFC) passes the filter.
     * @param onError Callback invoked if U+FFFC is rejected.
     * @return true if allowed, false if rejected.
     */
    bool IsNonCharAllowed(const std::function<bool(const std::u16string&)>& onError) const
    {
        CHECK_NULL_RETURN(!filter_.empty(), true);
        CHECK_NULL_RETURN(onError, true);
        std::u16string testChar = u"\uFFFC";
        bool filtered = TextInputFilter::FilterWithEvent(filter_, testChar, onError);
        return !filtered;
    }

    /**
     * @brief Filter content within a MutableSpanString in-place.
     * Non-text spans (image/symbol/placeholder/custom) are represented as
     * U+FFFC during regex matching. Rejected ranges are removed from the SpanString.
     * @param spanString The MutableSpanString to filter.
     * @param originalContent Pre-extracted u16string content of spanString.
     * @param onError Callback invoked with rejected characters.
     */
    void FilterSpanString(const RefPtr<MutableSpanString>& spanString, const std::u16string& originalContent,
        const std::function<bool(const std::u16string&)>& onError) const
    {
        CHECK_NULL_VOID(!filter_.empty());
        CHECK_NULL_VOID(spanString);
        CHECK_NULL_VOID(!originalContent.empty());
        auto specialSpans = CollectSpecialSpans(spanString);
        std::u16string filterText;
        std::vector<int32_t> posMap;
        std::vector<int32_t> origLen;
        BuildFilterText(originalContent, specialSpans, filterText, posMap, origLen);
        std::u16string beforeFilter = filterText;
        CHECK_NULL_VOID(onError);
        bool filtered = TextInputFilter::FilterWithEvent(filter_, filterText, onError);
        CHECK_NULL_VOID(filtered);
        RemoveRejectedRanges(spanString, beforeFilter, filterText, posMap, origLen);
    }

private:
    std::u16string filter_;

    /**
     * @brief Collect position/length of all non-text spans in the SpanString.
     * Non-text spans: IMAGE, CustomSpan, SYMBOL, PLACEHOLDER (i.e. != NORMAL).
     */
    static std::vector<std::pair<int32_t, int32_t>> CollectSpecialSpans(
        const RefPtr<MutableSpanString>& spanString)
    {
        std::vector<std::pair<int32_t, int32_t>> specialSpans;
        auto spanItems = spanString->GetSpanItems();
        for (const auto& item : spanItems) {
            if (item->spanItemType != SpanItemType::NORMAL) {
                specialSpans.emplace_back(item->interval.first,
                    item->interval.second - item->interval.first);
            }
        }
        return specialSpans;
    }

    /**
     * @brief Build a flat u16string for regex matching.
     * Non-text spans are collapsed to a single U+FFFC character.
     * posMap maps each position in filterText back to the original content.
     * origLen records the original length of each position (1 for chars, spanLen for special spans).
     */
    static void BuildFilterText(const std::u16string& originalContent,
        const std::vector<std::pair<int32_t, int32_t>>& specialSpans,
        std::u16string& filterText, std::vector<int32_t>& posMap, std::vector<int32_t>& origLen)
    {
        size_t spanIdx = 0;
        for (size_t i = 0; i < originalContent.length();) {
            if (spanIdx < specialSpans.size() && specialSpans[spanIdx].first == static_cast<int32_t>(i)) {
                int32_t spanLen = specialSpans[spanIdx].second;
                if (spanLen <= 0) {
                    ++spanIdx;
                    continue;
                }
                filterText += u'\uFFFC';
                posMap.push_back(static_cast<int32_t>(i));
                origLen.push_back(spanLen);
                i += static_cast<size_t>(spanLen);
                ++spanIdx;
            } else {
                filterText += originalContent[i];
                posMap.push_back(static_cast<int32_t>(i));
                origLen.push_back(1);
                ++i;
            }
        }
    }

    /**
     * @brief Remove rejected character ranges from the MutableSpanString.
     * Uses reverse diff between beforeFilter and afterFilter to find rejected
     * positions, maps them back via posMap/origLen, merges adjacent ranges,
     * and removes them in reverse order to preserve index validity.
     */
    static void RemoveRejectedRanges(const RefPtr<MutableSpanString>& spanString,
        const std::u16string& beforeFilter, const std::u16string& afterFilter,
        const std::vector<int32_t>& posMap, const std::vector<int32_t>& origLen)
    {
        std::vector<std::pair<int32_t, int32_t>> rejected;
        int32_t beforePos = static_cast<int32_t>(beforeFilter.length()) - 1;
        int32_t afterPos = static_cast<int32_t>(afterFilter.length()) - 1;
        while (afterPos >= 0 && beforePos >= 0) {
            if (beforeFilter[beforePos] == afterFilter[afterPos]) {
                --afterPos;
                --beforePos;
            } else {
                rejected.emplace_back(posMap[beforePos], origLen[beforePos]);
                --beforePos;
            }
        }
        while (beforePos >= 0) {
            rejected.emplace_back(posMap[beforePos], origLen[beforePos]);
            --beforePos;
        }
        std::reverse(rejected.begin(), rejected.end());
        std::vector<std::pair<int32_t, int32_t>> removeRanges;
        for (const auto& [pos, len] : rejected) {
            if (!removeRanges.empty() && removeRanges.back().first + removeRanges.back().second == pos) {
                removeRanges.back().second += len;
            } else {
                removeRanges.emplace_back(pos, len);
            }
        }
        for (int32_t i = static_cast<int32_t>(removeRanges.size()) - 1; i >= 0; --i) {
            spanString->RemoveString(removeRanges[i].first, removeRanges[i].second);
        }
    }
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RICH_EDITOR_INPUT_FILTER_MANAGER_H
