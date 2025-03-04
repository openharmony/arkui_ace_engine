/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#include "gtest/gtest.h"

#define protected public
#define private public

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {
std::vector<std::string> FONT_FAMILIES {"test"};

constexpr uint8_t NUM1 = 1;
constexpr uint8_t NUM55 = 55;
constexpr uint8_t NUM155 = 155;
constexpr uint8_t NUM255 = 255;
constexpr double FONT_SIZE = 10.0;
constexpr double FONT_SIZE_5 = 5.0;
constexpr double FONT_SIZE_0 = 0.0;

const Color TEST_COLOR = Color::FromARGB(1, 55, 155, 255);
const Color TEXT_COLOR_RED = Color::RED;

const NG::RectF TEST_RECT = {10.0f, 10.0f, 20.0f, 20.0f};
const NG::PointF TEST_POINT = {10.0f, 20.0f};

const FontWeight FONT_WEIGHT {0};
const FontStyle FONT_STYLE {0};

const Dimension WORD_SPACING_PX {1.0, DimensionUnit::PX};
const Dimension WORD_SPACING_PERCENT {10.0, DimensionUnit::PERCENT};
const Dimension LINE_HIGHT_PX {5.0, DimensionUnit::PX};
const Dimension LINE_HIGHT_PERCENT {10.0, DimensionUnit::PERCENT};
const Dimension LETTER_SPACING {2.0, DimensionUnit::PX};
const Dimension FONT_SIZE_FP {14.0, DimensionUnit::FP};
const Dimension FONT_SIZE_PX_0 {0.0, DimensionUnit::PX};
const Dimension FONT_SIZE_PX_5 {5.0, DimensionUnit::PX};
}

class DrawingPropConvertorTestNg : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        NG::MockPipelineContext::SetUp();
    }
    static void TearDownTestSuite()
    {
        NG::MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: DrawingPropConvertorTestNg001
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg001, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSColor.
     * @tc.expected: retRSColor value is the same as TEST_COLOR.
     */
    RSColor retRSColor = ToRSColor(TEST_COLOR);
    EXPECT_EQ(retRSColor.GetAlphaF(), NUM1);
    EXPECT_EQ(retRSColor.GetRed(), NUM55);
    EXPECT_EQ(retRSColor.GetGreen(), NUM155);
    EXPECT_EQ(retRSColor.GetBlue(), NUM255);
}

/**
 * @tc.name: DrawingPropConvertorTestNg002
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg002, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSColor.
     * @tc.expected: retRSColor.GetRed() is equal to 255.
     */
    RSColor retRSColor = ToRSColor(LinearColor::RED);

    EXPECT_EQ(retRSColor.GetAlphaF(), 1);
    EXPECT_EQ(retRSColor.GetRed(), 255);
    EXPECT_EQ(retRSColor.GetGreen(), 0);
    EXPECT_EQ(retRSColor.GetBlue(), 0);
}

/**
 * @tc.name: DrawingPropConvertorTestNg003
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg003, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSRect.
     * @tc.expected: return expected values.
     */
    RSRect retRect = ToRSRect(TEST_RECT);
    EXPECT_EQ(retRect.GetLeft(), 10);
    EXPECT_EQ(retRect.GetTop(), 10);
    EXPECT_EQ(retRect.GetRight(), 30);
    EXPECT_EQ(retRect.GetBottom(), 30);
}

/**
 * @tc.name: DrawingPropConvertorTestNg004
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg004, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSPoint.
     * @tc.expected: retPoint value is the same as TEST_POINT.
     */
    RSPoint retPoint = ToRSPoint(TEST_POINT);
    EXPECT_EQ(retPoint.GetX(), 10);
    EXPECT_EQ(retPoint.GetY(), 20);
}

/**
 * @tc.name: DrawingPropConvertorTestNg005
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg005, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSCapStyle and set input lineCap is ROUND.
     * @tc.expected: the return retCapStyle is the same as RSPen::CapStyle::ROUND_CAP.
     */
    auto testLineCap = static_cast<LineCap>(0);

    RSPen::CapStyle retCapStyle = ToRSCapStyle(testLineCap);
    EXPECT_EQ(retCapStyle, RSPen::CapStyle::FLAT_CAP);

    /**
     * @tc.steps2: call ToRSCapStyle and set input lineCap is SQUARE.
     * @tc.expected: the return retCapStyle is the same as RSPen::CapStyle::SQUARE_CAP.
     */
    testLineCap = static_cast<LineCap>(1);

    retCapStyle = ToRSCapStyle(testLineCap);
    EXPECT_EQ(retCapStyle, RSPen::CapStyle::ROUND_CAP);

    /**
     * @tc.steps3: call ToRSCapStyle and set input lineCap is BUTT.
     * @tc.expected: the return retCapStyle is the same as RSPen::CapStyle::FLAT_CAP.
     */
    testLineCap = static_cast<LineCap>(2);

    retCapStyle = ToRSCapStyle(testLineCap);
    EXPECT_EQ(retCapStyle, RSPen::CapStyle::SQUARE_CAP);
}

/**
 * @tc.name: DrawingPropConvertorTestNg006
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg006, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSTextDirection and set input TextDirection is LTR.
     * @tc.expected: the return retPoint is the same as RSTextDirection::LTR.
     */
    auto testTextDirection = static_cast<TextDirection>(0);

    RSTextDirection retTextDirection = ToRSTextDirection(testTextDirection);
    EXPECT_EQ(retTextDirection, RSTextDirection::LTR);

    /**
     * @tc.steps2: call ToRSTextDirection and set input TextDirection is RTL.
     * @tc.expected: the return retPoint is the same as RSTextDirection::RTL.
     */
    testTextDirection = static_cast<TextDirection>(1);

    retTextDirection = ToRSTextDirection(testTextDirection);
    EXPECT_EQ(retTextDirection, RSTextDirection::RTL);

    /**
     * @tc.steps3: call ToRSTextDirection and set input TextDirection is INHERIT.
     * @tc.expected: the return retPoint is the same as RSTextDirection::RTL.
     */
    testTextDirection = static_cast<TextDirection>(2);

    retTextDirection = ToRSTextDirection(testTextDirection);
    EXPECT_EQ(retTextDirection, RSTextDirection::LTR);
}

/**
 * @tc.name: DrawingPropConvertorTestNg007
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg007, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSTextAlign and set input align is LEFT.
     * @tc.expected: the return retTextAlign is the same as RSTextAlign::LEFT.
     */
    auto testTextAlign = static_cast<TextAlign>(4);

    RSTextAlign retTextAlign = ToRSTextAlign(testTextAlign);
    EXPECT_EQ(retTextAlign, RSTextAlign::LEFT);
}

/**
 * @tc.name: DrawingPropConvertorTestNg008
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg008, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSFontWeight and set different input values.
     * @tc.expected: the return retFontWeight is expected.
     */
    for (int32_t index = 0; index <= 15; index++) {
        auto testFontWeight = static_cast<FontWeight>(index);
        RSFontWeight retFontWeight = ToRSFontWeight(testFontWeight);
        switch (testFontWeight) {
            case FontWeight::W100:
            case FontWeight::LIGHTER:
                EXPECT_EQ(retFontWeight, RSFontWeight::W100);
                break;
            case FontWeight::W200:
                EXPECT_EQ(retFontWeight, RSFontWeight::W200);
                break;
            case FontWeight::W300:
                EXPECT_EQ(retFontWeight, RSFontWeight::W300);
                break;
            case FontWeight::W400:
            case FontWeight::NORMAL:
            case FontWeight::REGULAR:
                EXPECT_EQ(retFontWeight, RSFontWeight::W400);
                break;
            case FontWeight::W500:
            case FontWeight::MEDIUM:
                EXPECT_EQ(retFontWeight, RSFontWeight::W500);
                break;
            case FontWeight::W600:
                EXPECT_EQ(retFontWeight, RSFontWeight::W600);
                break;
            case FontWeight::W700:
            case FontWeight::BOLD:
                EXPECT_EQ(retFontWeight, RSFontWeight::W700);
                break;
            case FontWeight::W800:
                EXPECT_EQ(retFontWeight, RSFontWeight::W800);
                break;
            case FontWeight::W900:
            case FontWeight::BOLDER:
                EXPECT_EQ(retFontWeight, RSFontWeight::W900);
                break;
            default:
                EXPECT_EQ(retFontWeight, RSFontWeight::W400);
                break;
        }
    }
}

/**
 * @tc.name: DrawingPropConvertorTestNg009
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg009, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSWordBreakType and set input testWordBreak is NORMAL.
     * @tc.expected: the return retWordBreakType is the same as RSWordBreakType::WordBreakTypeNormal.
     */
    auto testWordBreak = static_cast<WordBreak>(0);

    RSWordBreakType retWordBreakType = ToRSWordBreakType(testWordBreak);
    EXPECT_EQ(retWordBreakType, RSWordBreakType::WordBreakTypeNormal);
}

/**
 * @tc.name: DrawingPropConvertorTestNg010
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg010, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSTextDecoration and set different input values.
     * @tc.expected: the return retTextDecoration is expected.
     */
    for (int32_t index = 0; index <= 4; index++) {
        auto testTextDecoration = static_cast<TextDecoration>(index);
        RSTextDecoration retTextDecoration = ToRSTextDecoration(testTextDecoration);
        switch (testTextDecoration) {
            case TextDecoration::OVERLINE:
                EXPECT_EQ(retTextDecoration, RSTextDecoration::OVERLINE);
                break;
            case TextDecoration::LINE_THROUGH:
                EXPECT_EQ(retTextDecoration, RSTextDecoration::LINE_THROUGH);
                break;
            case TextDecoration::UNDERLINE:
                EXPECT_EQ(retTextDecoration, RSTextDecoration::UNDERLINE);
                break;
            default:
                EXPECT_EQ(retTextDecoration, RSTextDecoration::NONE);
                break;
            }
    }
}

/**
 * @tc.name: DrawingPropConvertorTestNg011
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg011, TestSize.Level1)
{
    /**
     * @tc.steps1: create textStyle object.
     */
    TextStyle textStyle(FONT_FAMILIES, FONT_SIZE, FONT_WEIGHT, FONT_STYLE, TEXT_COLOR_RED);
    RefPtr<PipelineBase> context;

    /**
     * @tc.steps2: call ToRSTextStyle.
     * @tc.expected: retTextStyle.ellipsis_ is default value.
     */
    RSTextStyle retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_NE(retTextStyle.ellipsis, StringUtils::Str8ToStr16(StringUtils::ELLIPSIS));
    /**
     * @tc.steps3: call ToRSTextStyle and set input textStyle.textOverflow_ is TextOverflow::ELLIPSIS.
     * @tc.expected: the return retTextStyle is expected.
     */
    textStyle.textOverflow_ = TextOverflow::ELLIPSIS;
    textStyle.wordSpacing_ = WORD_SPACING_PX;
    retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_EQ(retTextStyle.ellipsis, StringUtils::Str8ToStr16(StringUtils::ELLIPSIS));
    EXPECT_EQ(retTextStyle.fontSize, FONT_SIZE);
    EXPECT_EQ(retTextStyle.wordSpacing, WORD_SPACING_PX.value_);
    EXPECT_FALSE(retTextStyle.heightOnly);

    /**
     * @tc.steps4: call ToRSTextStyle and set input textStyle.lineHeight_ is not equal to textStyle.fontSize_.
     * @tc.expected: retTextStyle.heightScale is expected value.
     */
    textStyle.lineHeight_ = LINE_HIGHT_PX;
    retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_EQ(retTextStyle.heightScale, LINE_HIGHT_PX.value_ / FONT_SIZE);

    /**
     * @tc.steps5: call ToRSTextStyle and set input textStyle.wordSpacing_ is WORD_SPACING_PERCENT.
     * @tc.expected: retTextStyle.heightScale is equal to LINE_HIGHT_PERCENT.value_.
     */
    textStyle.wordSpacing_ = WORD_SPACING_PERCENT;
    textStyle.lineHeight_ = LINE_HIGHT_PERCENT;
    retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_EQ(retTextStyle.wordSpacing, WORD_SPACING_PERCENT.value_ * FONT_SIZE);
    EXPECT_EQ(retTextStyle.heightScale, LINE_HIGHT_PERCENT.value_);
    EXPECT_TRUE(retTextStyle.heightOnly);
}

/**
 * @tc.name: DrawingPropConvertorTestNg012
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg012, TestSize.Level1)
{
    /**
     * @tc.steps1: create textStyle object and set input context is not null.
     */
    TextStyle textStyle(FONT_FAMILIES, FONT_SIZE, FONT_WEIGHT, FONT_STYLE, TEXT_COLOR_RED);
    RefPtr<PipelineBase> pipelineContext = NG::MockPipelineContext::pipeline_;

    /**
     * @tc.steps2: call ToRSTextStyle and set values of textStyle.
     * @tc.expected: retTextSty is expected and retTextStyle.letterSpacing_ is equal to WORD_SPACING_PX.value_.
     */
    textStyle.letterSpacing_ = LETTER_SPACING;
    textStyle.wordSpacing_ = WORD_SPACING_PX;
    textStyle.lineHeight_ = LINE_HIGHT_PX;
    RSTextStyle retTextStyle = ToRSTextStyle(pipelineContext, textStyle);
    EXPECT_EQ(retTextStyle.fontSize, FONT_SIZE * pipelineContext->fontScale_);
    EXPECT_EQ(retTextStyle.letterSpacing, LETTER_SPACING.value_);
    EXPECT_EQ(retTextStyle.wordSpacing, WORD_SPACING_PX.value_);
    EXPECT_EQ(retTextStyle.heightScale, LINE_HIGHT_PX.value_ / FONT_SIZE);

    /**
     * @tc.steps3: call ToRSTextStyle and set textStyle.allowScale_ is false.
     * @tc.expected: retTextStyle.fontSize is equal to FONT_SIZE.
     */
    textStyle.allowScale_ = false;
    retTextStyle = ToRSTextStyle(pipelineContext, textStyle);
    EXPECT_EQ(retTextStyle.fontSize, FONT_SIZE);

    /**
     * @tc.steps4: call ToRSTextStyle and set textStyle.fontSize_ is FONT_SIZE_FP.
     * @tc.expected: retTextStyle.fontSize is equal to FONT_SIZE.
     */
    textStyle.fontSize_ = FONT_SIZE_FP;
    retTextStyle = ToRSTextStyle(pipelineContext, textStyle);
    EXPECT_EQ(retTextStyle.fontSize, FONT_SIZE_FP.value_);
}

/**
 * @tc.name: DrawingPropConvertorTestNg013
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg013, TestSize.Level1)
{
    /**
     * @tc.steps1: create textStyle object.
     */
    TextStyle textStyle(FONT_FAMILIES, FONT_SIZE_5, FONT_WEIGHT, FONT_STYLE, TEXT_COLOR_RED);
    RefPtr<PipelineBase> context;

    /**
     * @tc.steps2: call ToRSTextStyle and set input textStyle.lineHeight_ is LINE_HIGHT_PX.
     * @tc.expected: retTextStyle.height_ is equal to 1.0.
     */
    textStyle.lineHeight_ = LINE_HIGHT_PX;
    RSTextStyle retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_EQ(retTextStyle.heightScale, 1.0);

    /**
     * @tc.steps3: call ToRSTextStyle and set input textStyle.fontSize_ is FONT_SIZE_PX_0.
     * @tc.expected: retTextStyle.height_ is equal to 1.0.
     */
    textStyle.fontSize_ = FONT_SIZE_PX_0;
    retTextStyle = ToRSTextStyle(context, textStyle);
    EXPECT_EQ(retTextStyle.heightScale, 1.0);
}

/**
 * @tc.name: DrawingPropConvertorTestNg014
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps1: create textStyle object.
     */
    TextStyle testTextStyle(FONT_FAMILIES, FONT_SIZE_0, FONT_WEIGHT, FONT_STYLE, TEXT_COLOR_RED);
    RefPtr<PipelineBase> pipelineContext = NG::MockPipelineContext::pipeline_;

    /**
     * @tc.steps2: call ToRSTextStyle and set pipelineContext->minPlatformVersion_ is 6.
     * @tc.expected: retTextStyle.hasHeightOverride_ is false.
     */
    pipelineContext->minPlatformVersion_ = 6;
    RSTextStyle retTextStyle = ToRSTextStyle(pipelineContext, testTextStyle);
    EXPECT_FALSE(retTextStyle.heightOnly);

    /**
     * @tc.steps3: call ToRSTextStyle and set testTextStyle.fontSize_ is FONT_SIZE_PX_5.
     * @tc.expected: retTextStyle.hasHeightOverride_ is false.
     */
    testTextStyle.fontSize_ = FONT_SIZE_PX_5;
    testTextStyle.lineHeight_ = LINE_HIGHT_PX;
    retTextStyle = ToRSTextStyle(pipelineContext, testTextStyle);
    EXPECT_FALSE(retTextStyle.heightOnly);
}

/**
 * @tc.name: DrawingPropConvertorTestNg015
 * @tc.desc: Test function to ToRSTextAlign ToRSEllipsisMode
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSTextAlign ToRSEllipsisMode.
     * @tc.expected: the return result is the same as input align.
     */
    auto testTextAlign = static_cast<TextAlign>(7); // 7 is not a valid TextAlign.

    RSTextAlign retTextAlign = ToRSTextAlign(testTextAlign);
    EXPECT_EQ(retTextAlign, RSTextAlign::START);
    EXPECT_EQ(ToRSTextAlign(TextAlign::LEFT), RSTextAlign::LEFT);
    EXPECT_EQ(ToRSTextAlign(TextAlign::RIGHT), RSTextAlign::RIGHT);
    EXPECT_EQ(ToRSTextAlign(TextAlign::JUSTIFY), RSTextAlign::JUSTIFY);
    EXPECT_EQ(ToRSTextAlign(TextAlign::END), RSTextAlign::END);
    EXPECT_EQ(ToRSTextAlign(TextAlign::CENTER), RSTextAlign::CENTER);
    EXPECT_EQ(ToRSTextAlign(TextAlign::START), RSTextAlign::START);
    EXPECT_EQ(ToRSEllipsisMode(EllipsisMode::HEAD), RSEllipsisMode::HEAD);
}

/**
 * @tc.name: DrawingPropConvertorTestNg016
 * @tc.desc: Test function to ToRSTextDecorationStyle
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSTextDecorationStyle.
     * @tc.expected: the return result is the same as input align.
     */
    TextStyle textStyle;
    textStyle.SetTextDecorationStyle(TextDecorationStyle::DASHED);
    EXPECT_EQ(ToRSTextStyle(nullptr, textStyle).decorationStyle, RSTextDecorationStyle::DASHED);
    textStyle.SetTextDecorationStyle(TextDecorationStyle::DOTTED);
    EXPECT_EQ(ToRSTextStyle(nullptr, textStyle).decorationStyle, RSTextDecorationStyle::DOTTED);
    textStyle.SetTextDecorationStyle(TextDecorationStyle::DOUBLE);
    EXPECT_EQ(ToRSTextStyle(nullptr, textStyle).decorationStyle, RSTextDecorationStyle::DOUBLE);
    textStyle.SetTextDecorationStyle(TextDecorationStyle::WAVY);
    EXPECT_EQ(ToRSTextStyle(nullptr, textStyle).decorationStyle, RSTextDecorationStyle::WAVY);
    textStyle.SetTextDecorationStyle(TextDecorationStyle::INHERIT);
    EXPECT_EQ(ToRSTextStyle(nullptr, textStyle).decorationStyle, RSTextDecorationStyle::SOLID);
}

/**
 * @tc.name: DrawingPropConvertorTestNg017
 * @tc.desc: Test cast to DrawingPropConvertorTestNg
 * @tc.type: FUNC
 */
HWTEST_F(DrawingPropConvertorTestNg, DrawingPropConvertorTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: call ToRSWordBreakType and set input testWordBreak is HYPHENATION.
     * @tc.expected: the return retWordBreakType is the same as RSWordBreakType::WordBreakTypeHyphenation.
     */
    auto testWordBreak = static_cast<WordBreak>(3);

    RSWordBreakType retWordBreakType = ToRSWordBreakType(testWordBreak);
    EXPECT_EQ(retWordBreakType, RSWordBreakType::WordBreakTypeHyphenation);
}
} // namespace OHOS::Ace
