/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/rich_editor/paragraph_manager.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MIN_RECT_TOP = -0.4f;
constexpr float MIN_RECT_PRECISION = -0.5f;
} // namespace

float ParagraphManager::GetHeight() const
{
    float res = 0.0f;
    for (auto&& info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        res += paragraph->GetHeight();
    }
    return res;
}

float ParagraphManager::GetMaxIntrinsicWidth() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        res = std::max(res, paragraph->GetMaxIntrinsicWidth());
    }
    return res;
}
bool ParagraphManager::DidExceedMaxLines() const
{
    bool res = false;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, false);
        res |= paragraph->DidExceedMaxLines();
    }
    return res;
}
float ParagraphManager::GetLongestLine() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        res = std::max(res, paragraph->GetLongestLine());
    }
    return res;
}
float ParagraphManager::GetMaxWidth() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        res = std::max(res, paragraph->GetMaxWidth());
    }
    return res;
}
float ParagraphManager::GetTextWidth() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        res = std::max(res, paragraph->GetTextWidth());
    }
    return res;
}

float ParagraphManager::GetTextWidthIncludeIndent() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        auto width = paragraph->GetTextWidth();
        res = std::max(res, width);
    }
    return res;
}

float ParagraphManager::GetLongestLineWithIndent() const
{
    float res = 0.0f;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0.0f);
        auto width = paragraph->GetLongestLineWithIndent();
        res = std::max(res, width);
    }
    return res;
}

size_t ParagraphManager::GetLineCount() const
{
    size_t count = 0;
    for (auto &&info : paragraphs_) {
        auto paragraph = info.paragraph;
        CHECK_NULL_RETURN(paragraph, 0);
        count += paragraph->GetLineCount();
    }
    return count;
}

int32_t ParagraphManager::GetIndex(Offset offset, bool clamp) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), 0);
    if (clamp && LessNotEqual(offset.GetY(), 0.0)) {
        return 0;
    }
    int idx = 0;
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it, ++idx) {
        auto&& info = *it;
        if (LessOrEqual(offset.GetY(), info.paragraph->GetHeight()) ||
            (!clamp && idx == static_cast<int>(paragraphs_.size()) - 1)) {
            return info.paragraph->GetGlyphIndexByCoordinate(offset) + info.start;
        }
        // get offset relative to each paragraph
        offset.SetY(offset.GetY() - info.paragraph->GetHeight());
    }
    return paragraphs_.back().end;
}

PositionWithAffinity ParagraphManager::GetGlyphPositionAtCoordinate(Offset offset)
{
    TAG_LOGI(AceLogTag::ACE_TEXT,
        "Get Glyph Position, coordinate = [%{public}.2f %{public}.2f]", offset.GetX(), offset.GetY());
    PositionWithAffinity finalResult(0, TextAffinity::UPSTREAM);
    CHECK_NULL_RETURN(!paragraphs_.empty(), finalResult);
    if (LessNotEqual(offset.GetY(), 0.0)) {
        return finalResult;
    }
    int idx = 0;
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it, ++idx) {
        auto& info = *it;
        if (LessOrEqual(offset.GetY(), info.paragraph->GetHeight()) ||
            (idx == static_cast<int>(paragraphs_.size()) - 1)) {
            auto result = info.paragraph->GetGlyphPositionAtCoordinate(offset);
            finalResult.position_ = result.position_ + static_cast<size_t>(info.start);
            TAG_LOGI(AceLogTag::ACE_TEXT,
                "Current paragraph, originPos = %{public}zu, finalPos =%{public}zu and affinity = %{public}d",
                result.position_, finalResult.position_, result.affinity_);
            finalResult.affinity_ = static_cast<TextAffinity>(result.affinity_);
            return finalResult;
        }
        // get offset relative to each paragraph
        offset.SetY(offset.GetY() - info.paragraph->GetHeight());
    }
    auto info = paragraphs_.back();
    auto result = info.paragraph->GetGlyphPositionAtCoordinate(offset);
    finalResult.position_ = static_cast<size_t>(info.end);
    finalResult.affinity_ = static_cast<TextAffinity>(result.affinity_);
    TAG_LOGI(AceLogTag::ACE_TEXT,
        "Current paragraph, final position = %{public}zu and affinity = %{public}d", finalResult.position_,
        finalResult.affinity_);
    return finalResult;
}

int32_t ParagraphManager::GetGlyphIndexByCoordinate(Offset offset, bool isSelectionPos) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), 0);
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it) {
        auto &&info = *it;
        if (LessOrEqual(offset.GetY(), info.paragraph->GetHeight())) {
            return info.paragraph->GetGlyphIndexByCoordinate(offset, isSelectionPos) + info.start;
        }
        // get offset relative to each paragraph
        offset.SetY(offset.GetY() - info.paragraph->GetHeight());
    }
    return paragraphs_.back().end;
}

bool ParagraphManager::GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), false);
    auto offsetIndex = offset;
    auto startIndex = 0;
    auto endIndex = 0;
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it) {
        auto &&info = *it;
        if (LessNotEqual(offset, info.end)) {
            auto flag = info.paragraph->GetWordBoundary(offsetIndex, start, end);
            start += startIndex;
            end += endIndex;
            return flag;
        }
        // get offset relative to each paragraph
        offsetIndex = offset - info.end;
        startIndex = info.end;
        endIndex = info.end;
    }
    return false;
}

bool ParagraphManager::CalcCaretMetricsByPosition(
    int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), false);
    auto offsetIndex = extent;
    auto offsetY = 0.0f;
    auto result = false;
    for (auto it = paragraphs_.begin(); it != paragraphs_.end(); ++it) {
        auto &&info = *it;
        if (textAffinity == TextAffinity::UPSTREAM || std::next(it) == paragraphs_.end()) {
            if (LessOrEqual(extent, info.end)) {
                result = info.paragraph->CalcCaretMetricsByPosition(offsetIndex, caretCaretMetric, textAffinity);
                break;
            }
        } else {
            if (LessNotEqual(extent, info.end)) {
                result = info.paragraph->CalcCaretMetricsByPosition(offsetIndex, caretCaretMetric, textAffinity);
                break;
            }
        }
        // get offset relative to each paragraph
        offsetIndex = extent - info.end;
        offsetY += info.paragraph->GetHeight();
    }
    caretCaretMetric.offset += OffsetF(0.0f, offsetY);
    return result;
}

LineMetrics ParagraphManager::GetLineMetricsByRectF(RectF rect, int32_t paragraphIndex) const
{
    auto index = 0;
    float height = 0;
    auto iter = paragraphs_.begin();
    while (index < paragraphIndex) {
        auto paragraphInfo = *iter;
        height += paragraphInfo.paragraph->GetHeight();
        iter++;
        index++;
    }
    auto paragraphInfo = *iter;
    rect.SetTop(rect.GetY() - height);
    auto lineMetrics = paragraphInfo.paragraph->GetLineMetricsByRectF(rect);
    lineMetrics.y += height;
    return lineMetrics;
}

TextLineMetrics ParagraphManager::GetLineMetrics(size_t lineNumber)
{
    if (GetLineCount() == 0 || lineNumber > GetLineCount() - 1) {
        TAG_LOGE(AceLogTag::ACE_TEXT,
            "GetLineMetrics failed, lineNumber is greater than max lines:%{public}zu", lineNumber);
        return TextLineMetrics();
    }
    size_t endIndex = 0;
    double paragraphsHeight = 0.0;
    size_t lineNumberParam = lineNumber;
    for (auto &&info : paragraphs_) {
        auto lineCount = info.paragraph->GetLineCount();
        if (lineCount > 0 && lineNumber > lineCount - 1) {
            lineNumber -= lineCount;
            paragraphsHeight += info.paragraph->GetHeight();
            auto lastLineMetrics = info.paragraph->GetLineMetrics(lineCount - 1);
            endIndex += lastLineMetrics.endIndex + 1;
            continue;
        }
        auto lineMetrics = info.paragraph->GetLineMetrics(lineNumber);
        lineMetrics.startIndex += endIndex;
        lineMetrics.endIndex += endIndex;
        lineMetrics.lineNumber = lineNumberParam;
        lineMetrics.y += paragraphsHeight;
        lineMetrics.baseline += paragraphsHeight;
        return lineMetrics;
    }
    return TextLineMetrics();
}

bool ParagraphManager::IsIndexAtParagraphEnd(int32_t index)
{
    for (const auto& info : paragraphs_) {
        if (info.end == index) {
            return true;
        }
    }
    return false;
}

void ParagraphManager::GetPaintRegion(RectF& boundsRect, float x, float y) const
{
    if (paragraphs_.empty()) {
        return;
    }
    for (const auto& info : paragraphs_) {
        CHECK_NULL_VOID(info.paragraph);
        auto rect = info.paragraph->GetPaintRegion(x, y);
        boundsRect = boundsRect.CombineRectT(rect);
        y += info.paragraph->GetHeight();
    }
}

std::vector<ParagraphManager::TextBox> ParagraphManager::GetRectsForRange(
    int32_t start, int32_t end, RectHeightStyle heightStyle, RectWidthStyle widthStyle)
{
    std::vector<TextBox> resultTextBoxes;
    float y = 0.0f;
    for (const auto& info : paragraphs_) {
        if (info.start >= end) {
            break;
        }
        int32_t relativeStart = std::max(static_cast<int32_t>(0), start - info.start);
        int32_t relativeEnd = std::min(info.end - info.start, end - info.start);
        if (relativeStart >= relativeEnd) {
            y += info.paragraph->GetHeight();
            continue;
        }
        std::vector<RectF> tempRects;
        std::vector<TextDirection> tempTextDirections;
        info.paragraph->TxtGetRectsForRange(
            relativeStart, relativeEnd, heightStyle, widthStyle, tempRects, tempTextDirections);
        for (size_t i = 0; i < tempRects.size(); ++i) {
            tempRects[i].SetTop(tempRects[i].Top() + y);
            resultTextBoxes.emplace_back(TextBox(tempRects[i], tempTextDirections[i]));
        }
        y += info.paragraph->GetHeight();
    }
    return resultTextBoxes;
}

std::pair<size_t, size_t> ParagraphManager::GetEllipsisTextRange()
{
    std::pair<size_t, size_t> range = {std::numeric_limits<size_t>::max(), 0};
    for (auto&& info : paragraphs_) {
        const auto& ellipsisTextRange = info.paragraph->GetEllipsisTextRange();
        range.first = std::min(range.first, ellipsisTextRange.first);
        range.second = std::max(range.second, ellipsisTextRange.second);
    }
    return range;
}

std::vector<RectF> ParagraphManager::GetRects(int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy) const
{
    std::vector<RectF> res;
    float y = 0.0f;
    for (auto&& info : paragraphs_) {
        std::vector<RectF> rects;
        if (info.start > end) {
            break;
        }
        if (info.end > start) {
            auto relativeStart = (start < info.start) ? 0 : start - info.start;
            if (rectHeightPolicy == RectHeightPolicy::COVER_TEXT) {
                info.paragraph->GetTightRectsForRange(relativeStart, end - info.start, rects);
            } else {
                info.paragraph->GetRectsForRange(relativeStart, end - info.start, rects);
            }

            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + y);
            }
            res.insert(res.end(), rects.begin(), rects.end());
        }
        y += info.paragraph->GetHeight();
    }
    return res;
}

std::vector<std::pair<std::vector<RectF>, TextDirection>> ParagraphManager::GetParagraphsRects(
    int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy) const
{
    std::vector<std::pair<std::vector<RectF>, TextDirection>> paragraphsRects;
    float y = 0.0f;
    for (auto&& info : paragraphs_) {
        if (info.start > end) {
            break;
        }
        if (info.end > start) {
            std::vector<RectF> rects;
            auto relativeStart = (start < info.start) ? 0 : start - info.start;
            if (rectHeightPolicy == RectHeightPolicy::COVER_TEXT) {
                info.paragraph->GetTightRectsForRange(relativeStart, end - info.start, rects);
            } else {
                info.paragraph->GetRectsForRange(relativeStart, end - info.start, rects);
            }
            std::pair<std::vector<RectF>, TextDirection> paragraphRects;
            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + y);
            }
            paragraphRects.first = rects;
            paragraphRects.second = info.paragraphStyle.direction;
            paragraphsRects.emplace_back(paragraphRects);
        }
        y += info.paragraph->GetHeight();
    }
    return paragraphsRects;
}

std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> ParagraphManager::GetTextBoxesForSelect(
    int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy) const
{
    SelectData selectData;
    selectData.secondResult = CalcCaretMetricsByPosition(end, selectData.secondMetrics, TextAffinity::UPSTREAM);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> paragraphsRects;
    selectData.y = 0.0f;
    for (auto&& info : paragraphs_) {
        if (info.start > end) {
            break;
        }
        CHECK_NULL_BREAK(info.paragraph);
        if (info.end > start) {
            std::vector<RectF> rects;
            selectData.relativeStart = std::max(0, start - info.start);
            selectData.relativeEnd = end - info.start;
            if (rectHeightPolicy == RectHeightPolicy::COVER_TEXT) {
                info.paragraph->GetTightRectsForRange(selectData.relativeStart, selectData.relativeEnd, rects);
            } else {
                info.paragraph->GetRectsForRange(selectData.relativeStart, selectData.relativeEnd, rects);
            }
            MakeBlankLineRectsInParagraph(rects, info, selectData);
            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + selectData.y);
            }
            paragraphsRects.emplace_back(std::make_pair(rects, info.paragraphStyle));
        }
        selectData.y += info.paragraph->GetHeight();
    }
    if (!paragraphsRects.empty()) {
        selectData.y = 0.0f;
        RemoveBlankLineRectByHandler(paragraphsRects.back().first, selectData);
    }
    return paragraphsRects;
}

void ParagraphManager::MakeBlankLineRectsInParagraph(std::vector<RectF>& result, const ParagraphInfo& info,
    const SelectData& selectData)
{
    const int32_t realEnd = info.end - info.start;
    const bool isLastParagraph = (selectData.relativeEnd == 0) || (selectData.relativeEnd < realEnd);
    if (isLastParagraph && !result.empty() && IsRectOutByHandler(result.back(), selectData)) {
        result.pop_back();
        return;
    }
    CHECK_NULL_VOID(info.paragraph);
    float height = info.paragraph->GetHeight();
    const float lastBottom = result.empty() ? MIN_RECT_TOP : result.back().Bottom();
    int32_t loopStart = std::min(realEnd, selectData.relativeEnd);
    int32_t loopEnd = std::max(0, selectData.relativeStart);
    std::vector<RectF> rects;
    for (int32_t index = loopStart; index >= loopEnd; index--) {
        if (GreatOrEqualCustomPrecision(lastBottom, height, MIN_RECT_PRECISION)) {
            break;
        }
        CaretMetricsF caretMetrics;
        bool res = info.paragraph->CalcCaretMetricsByPosition(index, caretMetrics, TextAffinity::UPSTREAM);
        CHECK_NULL_BREAK(res)
        RectF rect(caretMetrics.offset.GetX(), caretMetrics.offset.GetY(), 0.0f, caretMetrics.height);
        if (GreatNotEqual(rect.Bottom(), height) || (isLastParagraph && IsRectOutByHandler(rect, selectData))) {
            continue;
        }
        if (LessNotEqual(rect.Top(), lastBottom)) {
            break;
        }
        height = rect.Top();
        rects.emplace_back(rect);
    }
    std::reverse(rects.begin(), rects.end());
    result.insert(result.end(), rects.begin(), rects.end());
}

std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> ParagraphManager::GetRichEditorBoxesForSelect(
    int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy) const
{
    SelectData selectData;
    selectData.secondResult = CalcCaretMetricsByPosition(end, selectData.secondMetrics, TextAffinity::UPSTREAM);
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> paragraphsRects;
    selectData.y = 0.0f;
    for (auto&& info : paragraphs_) {
        if (info.start > end) {
            break;
        }
        CHECK_NULL_BREAK(info.paragraph);
        if (info.end > start) {
            std::vector<RectF> rects;
            selectData.relativeStart = std::max(0, start - info.start);
            selectData.relativeEnd = end - info.start;
            if (rectHeightPolicy == RectHeightPolicy::COVER_TEXT) {
                info.paragraph->GetTightRectsForRange(selectData.relativeStart, selectData.relativeEnd, rects);
            } else {
                info.paragraph->GetRectsForRange(selectData.relativeStart, selectData.relativeEnd, rects);
            }
            MakeBlankRectsInRichEditor(rects, info, selectData);
            for (auto&& rect : rects) {
                rect.SetTop(rect.Top() + selectData.y);
            }
            paragraphsRects.emplace_back(std::make_pair(rects, info.paragraphStyle));
        }
        selectData.y += info.paragraph->GetHeight();
    }
    if (!paragraphsRects.empty()) {
        selectData.y = 0.0f;
        RemoveBlankLineRectByHandler(paragraphsRects.back().first, selectData);
    }
    return paragraphsRects;
}

void ParagraphManager::MakeBlankRectsInRichEditor(std::vector<RectF>& result, const ParagraphInfo& info,
    const SelectData& selectData)
{
    const int32_t realEnd = info.end - info.start;
    const bool isLastParagraph = (selectData.relativeEnd == 0) || (selectData.relativeEnd < realEnd);
    if (isLastParagraph && !result.empty() && IsRectOutByHandler(result.back(), selectData)) {
        result.pop_back();
        return;
    }
    CHECK_NULL_VOID(info.paragraph);
    float height = info.paragraph->GetHeight();
    const float lastBottom = result.empty() ? MIN_RECT_TOP : result.back().Bottom();
    int32_t loopStart = std::min(realEnd, selectData.relativeEnd);
    int32_t loopEnd = std::max(0, selectData.relativeStart);
    std::vector<RectF> rects;
    for (int32_t index = loopStart; index >= loopEnd; index--) {
        if (GreatOrEqualCustomPrecision(lastBottom, height, MIN_RECT_PRECISION)) {
            break;
        }
        CaretMetricsF caretMetrics;
        bool res = info.paragraph->CalcCaretMetricsByPosition(index, caretMetrics, TextAffinity::UPSTREAM);
        CHECK_NULL_BREAK(res)
        RectF rect(caretMetrics.offset.GetX(), caretMetrics.offset.GetY(), 0.0f, caretMetrics.height);
        height  = rect.Top();
        rects.emplace_back(rect);
    }
    std::reverse(rects.begin(), rects.end());
    result.insert(result.end(), rects.begin(), rects.end());
}

void ParagraphManager::RemoveBlankLineRectByHandler(std::vector<RectF>& rects, const SelectData& selectData)
{
    while (!rects.empty()) {
        CHECK_EQUAL_VOID(IsRectOutByHandler(rects.back(), selectData), false);
        rects.pop_back();
    }
}

bool ParagraphManager::IsRectOutByHandler(const RectF& rect, const SelectData& selectData)
{
    CHECK_EQUAL_RETURN(NearZero(rect.Width()), false, false);
    CHECK_EQUAL_RETURN(selectData.secondResult, false, false);
    return GreatOrEqual(rect.Top() + selectData.y, selectData.secondMetrics.offset.GetY());
}

bool ParagraphManager::IsSelectLineHeadAndUseLeadingMargin(int32_t start) const
{
    for (auto iter = paragraphs_.begin(); iter != paragraphs_.end(); iter++) {
        auto curParagraph = *iter;
        if (curParagraph.paragraph && curParagraph.paragraph->GetParagraphStyle().leadingMargin &&
            curParagraph.start == start) {
            return true;
        }
        auto next = std::next(iter);
        if (next != paragraphs_.end()) {
            auto nextParagraph = *next;
            if (nextParagraph.paragraph && nextParagraph.paragraph->GetParagraphStyle().leadingMargin &&
                nextParagraph.start == start + 1) {
                return true;
            }
        }
    }
    return false;
}

std::vector<RectF> ParagraphManager::GetPlaceholderRects() const
{
    std::vector<RectF> res;
    float y = 0.0f;
    for (auto&& info : paragraphs_) {
        std::vector<RectF> rects;
        info.paragraph->GetRectsForPlaceholders(rects);
        for (auto& rect : rects) {
            rect.SetTop(rect.Top() + y);
        }
        y += info.paragraph->GetHeight();

        res.insert(res.end(), rects.begin(), rects.end());
    }
    return res;
}

OffsetF ParagraphManager::ComputeCursorOffset(
    int32_t index, float& selectLineHeight, bool downStreamFirst, bool needLineHighest) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), {});
    auto it = paragraphs_.begin();
    float y = 0.0f;
    while (it != paragraphs_.end()) {
        if (index >= it->start && index < it->end) {
            break;
        }
        y += it->paragraph->GetHeight();
        ++it;
    }

    if (index == paragraphs_.back().end) {
        --it;
        y -= it->paragraph->GetHeight();
    }

    CHECK_NULL_RETURN(it != paragraphs_.end(), OffsetF(0.0f, y));

    int32_t relativeIndex = index - it->start;
    auto&& paragraph = it->paragraph;
    CaretMetricsF metrics;
    auto computeSuccess = false;
    if (downStreamFirst) {
        computeSuccess = paragraph->ComputeOffsetForCaretDownstream(relativeIndex, metrics, needLineHighest) ||
                         paragraph->ComputeOffsetForCaretUpstream(relativeIndex, metrics, needLineHighest);
    } else {
        computeSuccess = paragraph->ComputeOffsetForCaretUpstream(relativeIndex, metrics, needLineHighest) ||
                         paragraph->ComputeOffsetForCaretDownstream(relativeIndex, metrics, needLineHighest);
    }
    CHECK_NULL_RETURN(computeSuccess, OffsetF(0.0f, y));
    selectLineHeight = metrics.height;
    return { static_cast<float>(metrics.offset.GetX()), static_cast<float>(metrics.offset.GetY() + y) };
}

OffsetF ParagraphManager::ComputeCursorInfoByClick(
    int32_t index, float& selectLineHeight, const OffsetF& lastTouchOffset) const
{
    CHECK_NULL_RETURN(!paragraphs_.empty(), {});
    auto it = paragraphs_.begin();
    float y = 0.0f;
    while (it != paragraphs_.end()) {
        if (index >= it->start && index < it->end) {
            break;
        }
        y += it->paragraph->GetHeight();
        ++it;
    }

    if (index == paragraphs_.back().end) {
        --it;
        y -= it->paragraph->GetHeight();
    }

    CHECK_NULL_RETURN(it != paragraphs_.end(), OffsetF(0.0f, y));

    int32_t relativeIndex = index - it->start;
    auto&& paragraph = it->paragraph;

    CaretMetricsF caretCaretMetric;
    auto touchOffsetInCurrentParagraph = OffsetF(static_cast<float>(lastTouchOffset.GetX()),
        static_cast<float>(lastTouchOffset.GetY() - y));
    TextAffinity textAffinity;
    paragraph->CalcCaretMetricsByPosition(relativeIndex, caretCaretMetric, touchOffsetInCurrentParagraph, textAffinity);
    selectLineHeight = caretCaretMetric.height;
    return { static_cast<float>(caretCaretMetric.offset.GetX()),
        static_cast<float>(caretCaretMetric.offset.GetY() + y) };
}

void ParagraphManager::Reset()
{
    paragraphs_.clear();
}

std::string ParagraphManager::ParagraphInfo::ToString() const
{
    return "Paragraph start: " + std::to_string(start) + ", end: " + std::to_string(end);
}
} // namespace OHOS::Ace::NG
