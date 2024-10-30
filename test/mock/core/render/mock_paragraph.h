/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_MOCK_CORE_RENDER_MOCK_PARAGRAPH_H
#define FOUNDATION_ACE_TEST_MOCK_CORE_RENDER_MOCK_PARAGRAPH_H

#include "gmock/gmock.h"

#include "core/components_ng/render/paragraph.h"

namespace OHOS::Ace::NG {
class MockParagraph : public Paragraph {
    DECLARE_ACE_TYPE(MockParagraph, Paragraph);

public:
    MockParagraph() = default;
    ~MockParagraph() override = default;

    MOCK_METHOD0(IsValid, bool());
    MOCK_METHOD0(PopStyle, void());
    MOCK_METHOD0(Build, void());
    MOCK_METHOD0(Reset, void());
    MOCK_METHOD0(GetHeight, float());
    MOCK_METHOD0(GetTextWidth, float());
    MOCK_METHOD0(GetLineCount, size_t());
    MOCK_METHOD0(GetMaxIntrinsicWidth, float());
    MOCK_METHOD0(DidExceedMaxLines, bool());
    MOCK_METHOD0(GetLongestLine, float());
    MOCK_METHOD0(GetLongestLineWithIndent, float());
    MOCK_METHOD0(GetMaxWidth, float());
    MOCK_METHOD0(GetAlphabeticBaseline, float());
    MOCK_METHOD0(GetParagraphText, std::u16string());
    MOCK_METHOD0(GetEllipsisTextRange, std::pair<size_t, size_t>());
    MOCK_CONST_METHOD0(GetParagraphStyle, const ParagraphStyle&());
    MOCK_METHOD1(PushStyle, void(const TextStyle& style));
    MOCK_METHOD1(AddText, void(const std::u16string& text));
    MOCK_METHOD1(AddSymbol, void(const uint32_t& symbolId));
    MOCK_METHOD1(Layout, void(float width));
    MOCK_METHOD1(AddPlaceholder, int32_t(const PlaceholderRun& span));
    MOCK_METHOD1(GetRectsForPlaceholders, void(std::vector<RectF>& selectedRects));
    MOCK_METHOD1(SetIndents, void(const std::vector<float>& indents));
    MOCK_METHOD1(GetCharacterWidth, float(int32_t index));
    MOCK_METHOD1(SetParagraphSymbolAnimation, void(const RefPtr<FrameNode>& frameNode));
    MOCK_METHOD1(SetParagraphId, void(uint32_t id));
    MOCK_METHOD1(GetLineMetrics, TextLineMetrics(size_t lineNumber));
    MOCK_METHOD1(GetGlyphPositionAtCoordinate, PositionWithAffinity(const Offset& offset));
    MOCK_METHOD2(GetGlyphIndexByCoordinate, int32_t(const Offset& offset, bool isSelectionPos));
    MOCK_METHOD3(ComputeOffsetForCaretDownstream, bool(int32_t extent, CaretMetricsF& result,
        bool needLineHighest));
    MOCK_METHOD3(ComputeOffsetForCaretUpstream, bool(int32_t extent, CaretMetricsF& result,
        bool needLineHighest));
    MOCK_METHOD3(GetRectsForRange, void(int32_t start, int32_t end, std::vector<RectF>& selectedRects));
    MOCK_METHOD3(GetTightRectsForRange, void(int32_t start, int32_t end, std::vector<RectF>& selectedRects));
    MOCK_METHOD3(Paint, void(RSCanvas& canvas, float x, float y));
#ifndef USE_ROSEN_DRAWING
    MOCK_METHOD3(Paint, void(SkCanvas* skCanvas, float x, float y));
#endif
    MOCK_METHOD3(GetWordBoundary, bool(int32_t offset, int32_t& start, int32_t& end));
    MOCK_METHOD6(TxtGetRectsForRange, void(int32_t start, int32_t end,
        RectHeightStyle heightStyle, RectWidthStyle widthStyle,
        std::vector<RectF>& selectedRects, std::vector<TextDirection>& textDirections));
    bool CalcCaretMetricsByPosition(
        int32_t extent, CaretMetricsF& caretCaretMetric, TextAffinity textAffinity, bool needLineHighest) override
    {
        return false;
    }

    bool CalcCaretMetricsByPosition(int32_t extent, CaretMetricsF& caretCaretMetric, const OffsetF& lastTouchOffsetF,
        TextAffinity& textAffinity) override
    {
        return false;
    }

    LineMetrics GetLineMetricsByRectF(RectF& rect) override
    {
        LineMetrics lineMetrics;
        return lineMetrics;
    }

    RectF GetPaintRegion(float x, float y) override
    {
        RectF rect;
        return rect;
    }

    bool GetLineMetricsByCoordinate(const Offset& offset, LineMetrics& lineMetrics) override
    {
        return true;
    }

    void UpdateColor(size_t from, size_t to, const Color& color) override;

    static RefPtr<MockParagraph> GetOrCreateMockParagraph();
    static void TearDown();

    static RefPtr<MockParagraph> paragraph_;
    static bool enabled_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_MOCK_CORE_RENDER_MOCK_PARAGRAPH_H
