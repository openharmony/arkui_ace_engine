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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H

#include <vector>

#include "testing_canvas.h"
#include "testing_typography_properties.h"

namespace OHOS::Ace::Testing {
enum class WordBreakType {
    WordBreakTypeNormal = 0,
    WordBreakTypeBreakAll,
    WordBreakTypeBreakWord,
    WordBreakTypeHyphenation,
};

enum class TextAlign {
    LEFT = 0,
    RIGHT,
    CENTER,
    JUSTIFY,
    START,
    END,
};

enum class EllipsisMode {
    HEAD,
    MIDDLE,
    TAIL,
};

class TestingTypography {
public:
    TestingTypography() = default;
    virtual ~TestingTypography() = default;

    virtual double GetHeight()
    {
        return 1.0;
    }

    virtual void Layout(double width) {}

    virtual double GetMaxIntrinsicWidth()
    {
        return 1.0;
    }

    virtual double GetMaxWidth()
    {
        return 1.0;
    }

#ifndef USE_GRAPHIC_TEXT_GINE
    virtual double GetLongestLine()
#else
    virtual double GetActualWidth()
#endif
    {
        return 1.0;
    }

    virtual double GetMinIntrinsicWidth()
    {
        return 1.0;
    }

    virtual size_t GetLineCount()
    {
        return 1;
    }

    virtual void Paint(TestingCanvas* canvas, double x, double y) {}

#ifndef USE_GRAPHIC_TEXT_GINE
    virtual std::vector<TestingTypographyProperties::TextBox> GetRectsForRange(size_t /* start */, size_t /* end */,
        TestingTypographyProperties::RectHeightStyle /* height */,
        TestingTypographyProperties::RectWidthStyle /* width */)
#else
    virtual std::vector<TestingTypographyProperties::TextRect> GetTextRectsByBoundary(size_t /* start */,
        size_t /* end */, TestingTypographyProperties::TextRectHeightStyle /* height */,
        TestingTypographyProperties::TextRectWidthStyle /* width */)
#endif
    {
        return {};
    }

#ifndef USE_GRAPHIC_TEXT_GINE
    virtual TestingTypographyProperties::PositionAndAffinity GetGlyphPositionAtCoordinateWithCluster(double x, double y)
    {
        TestingTypographyProperties::PositionAndAffinity res(1, TestingTypographyProperties::Affinity::UPSTREAM);
        return res;
    }
#else
    virtual TestingTypographyProperties::IndexAndAffinity GetGlyphIndexByCoordinate(double x, double y)
    {
        TestingTypographyProperties::IndexAndAffinity res(1, TestingTypographyProperties::Affinity::PREV);
        return res;
    }
#endif

#ifndef USE_GRAPHIC_TEXT_GINE
    virtual TestingTypographyProperties::PositionAndAffinity GetGlyphPositionAtCoordinate(double x, double y)
    {
        TestingTypographyProperties::PositionAndAffinity res(1, TestingTypographyProperties::Affinity::UPSTREAM);
        return res;
    }

    virtual TestingTypographyProperties::Range<size_t> GetWordBoundary(size_t offset)
    {
        TestingTypographyProperties::Range<size_t> range =
            TestingTypographyProperties::Range<size_t>(offset, offset + 1);
        return range;
    }
#else
    virtual TestingTypographyProperties::IndexAndAffinity GetGlyphPositionAtCoordinate(double x, double y)
    {
        TestingTypographyProperties::IndexAndAffinity res(1, TestingTypographyProperties::Affinity::PREV);
        return res;
    }

    virtual TestingTypographyProperties::Boundary<size_t> GetWordBoundaryByIndex(size_t offset)
    {
        TestingTypographyProperties::Boundary<size_t> range =
            TestingTypographyProperties::Boundary<size_t>(offset, offset + 1);
        return range;
    }
#endif
    double GetAlphabeticBaseline()
    {
        return 0.0;
    }
    double GetIdeographicBaseline()
    {
        return 0.0;
    }
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TYPOGRAPHY_H
