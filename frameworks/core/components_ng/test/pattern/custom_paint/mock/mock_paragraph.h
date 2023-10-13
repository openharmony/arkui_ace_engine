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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_PARAGRAPH_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_PARAGRAPH_H

#ifdef USE_GRAPHIC_TEXT_GINE
#include <cstddef>
#endif

#include "gmock/gmock.h"
#ifdef USE_GRAPHIC_TEXT_GINE
#include "rosen_text/typography.h"
#endif
#include "include/core/SkCanvas.h"
#include "txt/paragraph.h"

namespace OHOS::Ace::NG {

#ifndef USE_GRAPHIC_TEXT_GINE
class MockParagraph : public txt::Paragraph {
public:
    MOCK_METHOD0(GetMaxWidth, double());
    MOCK_METHOD0(GetHeight, double());
    MOCK_METHOD0(GetLongestLine, double());
#else
class MockParagraph : public Rosen::Typography {
public:
    MOCK_CONST_METHOD0(GetMaxWidth, double());
    MOCK_CONST_METHOD0(GetHeight, double());
    MOCK_CONST_METHOD0(GetActualWidth, double());
#endif
    MOCK_METHOD0(GetMinIntrinsicWidth, double());
    MOCK_METHOD0(GetMaxIntrinsicWidth, double());
    MOCK_METHOD0(GetAlphabeticBaseline, double());
    MOCK_METHOD0(GetIdeographicBaseline, double());
#ifndef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD0(DidExceedMaxLines, bool());
    MOCK_METHOD0(GetRectsForPlaceholders, std::vector<TextBox>());
#else
    MOCK_CONST_METHOD0(DidExceedMaxLines, bool());
    MOCK_METHOD0(GetTextRectsOfPlaceholders, std::vector<Rosen::TextRect>());
    MOCK_CONST_METHOD0(GetLineCount, int());
#endif
    MOCK_METHOD1(Layout, void(double width));
#ifndef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD1(GetWordBoundary, Range<size_t>(size_t offset));
#else
    MOCK_METHOD1(SetIndents, void(const std::vector<float>& indents));
    MOCK_METHOD1(GetWordBoundaryByIndex, Rosen::Boundary(size_t offset));
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD2(GetGlyphPositionAtCoordinate, PositionWithAffinity(double dx, double dy));
    MOCK_METHOD2(GetGlyphPositionAtCoordinateWithCluster, PositionWithAffinity(double dx, double dy));
#else
    MOCK_METHOD2(GetGlyphIndexByCoordinate, Rosen::IndexAndAffinity(double x, double y));
#endif
    MOCK_METHOD3(Paint, void(SkCanvas* canvas, double x, double y));

#ifdef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD3(Paint, void(Rosen::Drawing::Canvas* canvas, double x, double y));
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
    MOCK_METHOD4(GetRectsForRange, std::vector<TextBox>(size_t start, size_t end, RectHeightStyle rect_height_style,
                                       RectWidthStyle rect_width_style));
#else
    MOCK_METHOD4(GetTextRectsByBoundary,
        std::vector<Rosen::TextRect>(size_t start, size_t end, Rosen::TextRectHeightStyle rect_height_style,
            Rosen::TextRectWidthStyle rect_width_style));
#endif
    MOCK_METHOD0(GetLineMetrics, std::vector<txt::LineMetrics>&());
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_TEST_PATTERN_CUSTOM_PAINT_MOCK_PARAGRAPH_H
