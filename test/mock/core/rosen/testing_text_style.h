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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_STYLE_H

#include <string>
#include <vector>

#include "testing_color.h"
#include "testing_pen.h"
#include "testing_point.h"

namespace OHOS::Ace::Testing {
enum class TestingFontWeight {
    W100, // thin
    W200,
    W300,
    W400,
    W500,
    W600,
    W700,
    W800,
    W900,
};

enum class TestingTextDecoration {
    NONE = 0x0,
    UNDERLINE = 0x1,
    OVERLINE = 0x2,
    LINE_THROUGH = 0x4,
};

enum class TestingTextDecorationStyle {
    SOLID,
    DOUBLE,
    DOTTED,
    DASHED,
    WAVY,
};

enum class TestingFontStyle {
    NORMAL,
    ITALIC,
};

enum class TestingTextBaseline {
    ALPHABETIC,
    IDEOGRAPHIC,
};

class TestingTextShadow {
public:
    TestingTextShadow() = default;
    virtual ~TestingTextShadow() = default;

    virtual bool hasShadow() const
    {
        return false;
    }

    TestingColor color;
    TestingPoint offset;
    double blurRadius = 0.0;
};

class TestingFontFeatures {
public:
    TestingFontFeatures() = default;
    virtual ~TestingFontFeatures() = default;
};

class TestingTextStyle {
public:
    TestingTextStyle() = default;
    ~TestingTextStyle() = default;

    virtual bool equals(const TestingTextStyle& /* rhs */) const
    {
        return false;
    }

    double decorationThicknessMultiplier = 1.0;
    double fontSize = 14.0;
    double letterSpacing = 0.0;
    double wordSpacing = 0.0;
    double heightScale = 1.0;
    bool heightOnly = false;
    bool hasBackground = false;
    bool hasForeground = false;
    std::u16string ellipsis;
    std::string locale;
    std::vector<std::string> fontFamilies;
    TestingColor color;
    TestingTextDecoration decoration = TestingTextDecoration::NONE;
    TestingColor decorationColor;
    TestingPen background;
    TestingPen foreground;
    TestingTextDecorationStyle decorationStyle = TestingTextDecorationStyle::SOLID;
    TestingFontWeight fontWeight = TestingFontWeight::W400;
    TestingFontStyle fontStyle = TestingFontStyle::NORMAL;
    TestingTextBaseline baseline = TestingTextBaseline::ALPHABETIC;
    std::vector<TestingTextShadow> textShadows;
    TestingFontFeatures fontFeatures;
};
} // namespace OHOS::Ace::Testing
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MOCK_ROSEN_TEST_TESTING_TEXT_STYLE_H
