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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARAGRAPH_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_PARAGRAPH_MANAGER_H
#include <list>
#include <optional>

#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "core/components/common/properties/text_layout_info.h"
#include "core/components_ng/render/paragraph.h"
namespace OHOS::Ace::NG {
class ParagraphManager : public virtual AceType {
    DECLARE_ACE_TYPE(ParagraphManager, AceType);

public:
    struct ParagraphInfo {
        RefPtr<Paragraph> paragraph;
        ParagraphStyle paragraphStyle;
        int32_t start = 0;
        int32_t end = 0;
        float topPos = 0.0f;
        float bottomPos = 0.0f;

        std::string ToString() const;
    };
    struct TextBox {
        TextDirection direction_;
        RectF rect_;
        TextBox() = default;
        TextBox(RectF rect, TextDirection direction) : direction_(direction), rect_(rect) {}
    };

    ParagraphManager() = default;
    std::optional<double> minParagraphFontSize = std::nullopt;

    int32_t GetIndex(Offset offset, bool clamp = false) const;
    PositionWithAffinity GetGlyphPositionAtCoordinate(Offset offset);
    float GetHeight() const;

    const std::vector<ParagraphInfo>& GetParagraphs() const
    {
        return paragraphs_;
    }
    void Reset();

    virtual std::vector<RectF> GetRects(int32_t start, int32_t end,
        RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE) const;
    ParagraphManager::ParagraphInfo GetParagraphInfo(int32_t position) const;
    std::vector<std::pair<std::vector<RectF>, TextDirection>> GetParagraphsRects(
        int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE) const;
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> GetTextBoxesForSelect(
        int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE) const;
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> GetRichEditorBoxesForSelect(
        int32_t start, int32_t end, RectHeightPolicy rectHeightPolicy = RectHeightPolicy::COVER_LINE) const;
    std::vector<RectF> GetPlaceholderRects() const;
    OffsetF ComputeCursorOffset(int32_t index, float& selectLineHeight, bool downStreamFirst = false,
            bool needLineHighest = true) const;
    OffsetF ComputeCursorInfoByClick(int32_t index, float& selectLineHeight, const OffsetF& lastTouchOffset) const;
    bool IsSelectLineHeadAndUseLeadingMargin(int32_t start) const;

    void AddParagraph(ParagraphInfo&& info)
    {
        paragraphs_.emplace_back(std::move(info));
    }

    void SetParagraphs(const std::vector<ParagraphInfo>& paragraphs)
    {
        paragraphs_ = paragraphs;
    }

    // add for text
    int32_t GetGlyphIndexByCoordinate(Offset offset, bool isSelectionPos = false) const;
    bool GetWordBoundary(int32_t offset, int32_t& start, int32_t& end) const;
    bool CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity) const;
    float GetMaxIntrinsicWidth() const;
    bool DidExceedMaxLines() const;
    float GetLongestLine() const;
    float GetMaxWidth() const;
    float GetTextWidth() const;
    float GetTextWidthIncludeIndent() const;
    float GetLongestLineWithIndent() const;
    size_t GetLineCount() const;
    LineMetrics GetLineMetricsByRectF(RectF rect, int32_t paragraphIndex) const;
    void GetPaintRegion(RectF& boundsRect, float x, float y) const;
    std::vector<TextBox> GetRectsForRange(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle);
    std::pair<size_t, size_t> GetEllipsisTextRange();
    TextLineMetrics GetLineMetrics(size_t lineNumber);
    bool IsIndexAtParagraphEnd(int32_t index);

protected:
    std::vector<ParagraphInfo> paragraphs_;

private:
    struct SelectData {
        float y = 0.0f;
        bool secondResult = false;
        CaretMetricsF secondMetrics;
        int32_t relativeStart = 0;
        int32_t relativeEnd = 0;
        float paragraphSpacing = 0.0f;
    };
    static void MakeBlankLineRectsInParagraph(std::vector<RectF>& result, const ParagraphInfo& info,
        const SelectData& selectData);
    static void MakeBlankRectsInRichEditor(std::vector<RectF>& result, const ParagraphInfo& info,
        const SelectData& selectData);
    static void RemoveBlankLineRectByHandler(std::vector<RectF>& rects, const SelectData& selectData);
    static bool IsRectOutByHandler(const RectF& rect, const SelectData& selectData);
    static void AddParagraphSpacingBlankRect(
        std::vector<RectF>& rects, const RectF& lastRect, const SelectData& selectData);
    static void AppendParagraphSpacingBlankRect(std::vector<RectF>& rects, const SelectData& selectData);
};
} // namespace OHOS::Ace::NG
#endif
