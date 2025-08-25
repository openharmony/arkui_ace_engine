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

#include "gtest/gtest.h"
#include "test/mock/core/render/mock_paragraph.h"
#include "test/mock/core/render/mock_texteffect.h"
#include "text_base.h"

#include "core/components/common/properties/text_style_parser.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float DEFAULT_CONTENT_WIDTH = 800.0f;
constexpr float DEFAULT_TEXT_HEIGHT = 50.0f;
constexpr float DEFAULT_BLANK_LINE_WIDTH = 3.0f;
} // namespace

class TextTestSixNg : public TextBases {
public:
};

/**
 * @tc.name: UseSelfStyle001
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, UseSelfStyle001, TestSize.Level1)
{
    auto fontStyle = std::make_unique<FontStyle>();
    TextStyle textStyle;

    fontStyle->UpdateFontSize(Dimension(10.0, DimensionUnit::PX));
    fontStyle->UpdateTextColor(Color::WHITE);
    Shadow textShadow;
    textShadow.SetBlurRadius(BLURRADIUS_VALUE);
    textShadow.SetColor(TEXT_COLOR_VALUE);
    textShadow.SetSpreadRadius(SPREADRADIUS_VALUE);
    textShadow.SetOffsetX(ADAPT_OFFSETX_VALUE);
    textShadow.SetOffsetY(ADAPT_OFFSETY_VALUE);
    fontStyle->UpdateTextShadow({ textShadow });
    fontStyle->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);
    fontStyle->UpdateSuperscript(SuperscriptStyle::SUBSCRIPT);
    fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    fontStyle->UpdateFontFamily(fontFamilies);
    fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    fontStyle->UpdateTextDecoration({TextDecoration::OVERLINE});
    fontStyle->UpdateTextDecorationColor(Color::WHITE);
    fontStyle->UpdateTextDecorationStyle(TextDecorationStyle::SOLID);
    fontStyle->UpdateTextCase(TextCase::LOWERCASE);
    fontStyle->UpdateAdaptMinFontSize(12.0_fp);
    fontStyle->UpdateAdaptMaxFontSize(10.0_fp);
    fontStyle->UpdateLetterSpacing(Dimension(10.0, DimensionUnit::PX));
    std::vector<Color> colorList;
    colorList.emplace_back(Color::WHITE);
    colorList.emplace_back(Color::BLACK);
    fontStyle->UpdateSymbolColorList(colorList);
    fontStyle->UpdateSymbolRenderingStrategy(2);
    fontStyle->UpdateSymbolEffectStrategy(0);
    fontStyle->UpdateSymbolEffectOptions(SymbolEffectOptions(SymbolEffectType::BOUNCE));
    fontStyle->UpdateMinFontScale(1.0);
    fontStyle->UpdateMaxFontScale(2.0);

    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), false);
    UseSelfStyle(fontStyle, nullptr, textStyle, true);
    EXPECT_EQ(textStyle.GetSymbolEffectOptions().has_value(), true);
}

/**
 * @tc.name: UseSelfStyle002
 * @tc.desc: test text_styles.cpp UseSelfStyle function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, UseSelfStyle002, TestSize.Level1)
{
    auto textLineStyle = std::make_unique<TextLineStyle>();
    TextStyle textStyle;

    textLineStyle->UpdateLineHeight(Dimension(10.0, DimensionUnit::PX));
    textLineStyle->UpdateLineSpacing(Dimension(1.0, DimensionUnit::PX));
    textLineStyle->UpdateTextBaseline(TextBaseline::MIDDLE);
    textLineStyle->UpdateBaselineOffset(Dimension(20.0, DimensionUnit::PX));
    textLineStyle->UpdateTextOverflow(TextOverflow::DEFAULT);
    textLineStyle->UpdateTextAlign(TextAlign::LEFT);
    textLineStyle->UpdateMaxLines(1024);
    textLineStyle->UpdateTextIndent(Dimension(40, DimensionUnit::PX));
    textLineStyle->UpdateWordBreak(WordBreak::NORMAL);
    textLineStyle->UpdateEllipsisMode(EllipsisMode::HEAD);

    UseSelfStyle(nullptr, textLineStyle, textStyle);
    EXPECT_EQ(textStyle.GetLineSpacing(), Dimension(1.0, DimensionUnit::PX));
}

/**
 * @tc.name: GetLineBreakStrategyInJson001
 * @tc.desc: test text_styles.cpp GetLineBreakStrategyInJson function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, GetLineBreakStrategyInJson001, TestSize.Level1)
{
    std::optional<Ace::LineBreakStrategy> value = Ace::LineBreakStrategy::HIGH_QUALITY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "HIGH_QUALITY");
    value = Ace::LineBreakStrategy::BALANCED;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "BALANCED");
    value = Ace::LineBreakStrategy::GREEDY;
    EXPECT_EQ(GetLineBreakStrategyInJson(value), "GREEDY");
}

/**
 * @tc.name: TextBaseTestNG001
 * @tc.desc: test text_base.cpp UpdateSelectedBlankLineRect function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, TextBaseTestNG001, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 0.0f, 0.0f);
    TextAlign textAlign = TextAlign::START;
    bool result = false;

    rect.SetWidth(1.0f);
    textAlign = TextAlign::START;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, false);

    rect.SetWidth(1.0f);
    textAlign = TextAlign::END;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, false);

    rect.SetWidth(1.0f);
    textAlign = TextAlign::CENTER;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, false);

    rect.SetWidth(1.0f);
    textAlign = TextAlign::JUSTIFY;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: TextBaseTestNG002
 * @tc.desc: test text_base.cpp UpdateSelectedBlankLineRect function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, TextBaseTestNG002, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 0.0f, 0.0f);
    TextAlign textAlign = TextAlign::START;
    bool result = false;

    rect.SetWidth(0.0f);
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, true);
    EXPECT_NE(rect.Width(), 0.0f);

    rect.SetWidth(0.0f);
    textAlign = TextAlign::END;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, true);
    EXPECT_NE(rect.Width(), 0.0f);

    rect.SetWidth(0.0f);
    textAlign = TextAlign::CENTER;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, true);
    EXPECT_NE(rect.Width(), 0.0f);

    rect.SetWidth(0.0f);
    textAlign = TextAlign::JUSTIFY;
    result = TextBase::UpdateSelectedBlankLineRect(rect, DEFAULT_BLANK_LINE_WIDTH, textAlign, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result, true);
    EXPECT_NE(rect.Width(), 0.0f);
}

/**
 * @tc.name: TextBaseTestNG003
 * @tc.desc: test text_base.cpp CheckTextAlignByDirection function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, TextBaseTestNG003, TestSize.Level1)
{
    TextAlign textAlign = TextAlign::START;
    TextDirection direction = TextDirection::AUTO;
    TextAlign result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::START);

    textAlign = TextAlign::END;
    direction = TextDirection::AUTO;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::END);

    textAlign = TextAlign::CENTER;
    direction = TextDirection::AUTO;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::CENTER);

    textAlign = TextAlign::JUSTIFY;
    direction = TextDirection::AUTO;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::JUSTIFY);

    textAlign = TextAlign::START;
    direction = TextDirection::LTR;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::START);

    textAlign = TextAlign::END;
    direction = TextDirection::LTR;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::END);

    textAlign = TextAlign::CENTER;
    direction = TextDirection::LTR;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::CENTER);

    textAlign = TextAlign::JUSTIFY;
    direction = TextDirection::LTR;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::JUSTIFY);
}

/**
 * @tc.name: TextBaseTestNG004
 * @tc.desc: test text_base.cpp CheckTextAlignByDirection function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, TextBaseTestNG004, TestSize.Level1)
{
    TextAlign textAlign = TextAlign::START;
    TextDirection direction = TextDirection::INHERIT;
    TextAlign result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::START);

    textAlign = TextAlign::END;
    direction = TextDirection::INHERIT;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::END);

    textAlign = TextAlign::CENTER;
    direction = TextDirection::INHERIT;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::CENTER);

    textAlign = TextAlign::JUSTIFY;
    direction = TextDirection::INHERIT;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::JUSTIFY);

    textAlign = TextAlign::START;
    direction = TextDirection::RTL;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::END);

    textAlign = TextAlign::END;
    direction = TextDirection::RTL;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::START);

    textAlign = TextAlign::CENTER;
    direction = TextDirection::RTL;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::CENTER);

    textAlign = TextAlign::JUSTIFY;
    direction = TextDirection::RTL;
    result = TextBase::CheckTextAlignByDirection(textAlign, direction);
    EXPECT_EQ(result, TextAlign::JUSTIFY);
}

/**
 * @tc.name: TextPaintMethodTestNG001
 * @tc.desc: test text_paint_method.cpp CalculateSelectedRect function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, TextPaintMethodTestNG001, TestSize.Level1)
{
    std::vector<std::pair<std::vector<RectF>, ParagraphStyle>> paragraphsRects;
    auto result = TextPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_TRUE(result.empty());

    std::vector<RectF> rects;
    ParagraphStyle paragraphStyle;
    std::pair<std::vector<RectF>, ParagraphStyle> paragraphRects;

    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = TextPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_TRUE(result.empty());

    rects.clear();
    paragraphsRects.clear();
    rects.emplace_back(RectF(0.0f, 0.0f, 0.0f, DEFAULT_TEXT_HEIGHT));
    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = TextPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result.size(), rects.size());

    rects.clear();
    paragraphsRects.clear();
    rects.emplace_back(RectF(0.0f, 0.0f, 0.0f, DEFAULT_TEXT_HEIGHT));
    rects.emplace_back(RectF(0.0f, DEFAULT_TEXT_HEIGHT, 0.0f, DEFAULT_TEXT_HEIGHT));
    rects.emplace_back(RectF(0.0f, DEFAULT_TEXT_HEIGHT + DEFAULT_TEXT_HEIGHT, 0.0f, DEFAULT_TEXT_HEIGHT));
    paragraphRects.first = rects;
    paragraphRects.second = paragraphStyle;
    paragraphsRects.emplace_back(paragraphRects);
    result = TextPaintMethod::CalculateSelectedRect(paragraphsRects, DEFAULT_CONTENT_WIDTH);
    EXPECT_EQ(result.size(), rects.size());
}

/**
 * @tc.name: ParagraphManagerTestNG001
 * @tc.desc: test paragraph_manager.cpp IsRectOutByHandler function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, ParagraphManagerTestNG001, TestSize.Level1)
{
    ParagraphManager::SelectData selectData;
    RectF rect;
    float y = 0.0f;
    selectData.y = DEFAULT_TEXT_HEIGHT;
    selectData.secondResult = true;
    selectData.secondMetrics =
        CaretMetricsF(OffsetF(0.0f, DEFAULT_TEXT_HEIGHT + DEFAULT_TEXT_HEIGHT), DEFAULT_TEXT_HEIGHT);

    rect = RectF(0.0f, y, DEFAULT_BLANK_LINE_WIDTH, DEFAULT_TEXT_HEIGHT);
    auto result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_FALSE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, DEFAULT_BLANK_LINE_WIDTH, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_FALSE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, DEFAULT_BLANK_LINE_WIDTH, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_FALSE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, DEFAULT_BLANK_LINE_WIDTH, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_FALSE(result);

    y = 0.0f;
    rect = RectF(0.0f, y, 0.0f, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_FALSE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, 0.0f, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_TRUE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, 0.0f, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_TRUE(result);

    y += DEFAULT_TEXT_HEIGHT;
    rect = RectF(0.0f, y, 0.0f, DEFAULT_TEXT_HEIGHT);
    result = ParagraphManager::IsRectOutByHandler(rect, selectData);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ResetTextEffectBeforeLayoutTest001
 * @tc.desc: Test ResetTextEffectBeforeLayout when textEffectStrategy is NONE
 */
HWTEST_F(TextTestSixNg, ResetTextEffectBeforeLayoutTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);

    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::NONE);

    bool result = pattern->ResetTextEffectBeforeLayout();
    EXPECT_TRUE(result);

    layoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);

    result = pattern->ResetTextEffectBeforeLayout(false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetOrCreateTextEffectTest001
 * @tc.desc: Test GetOrCreateTextEffect when need to reset text effect
 */
HWTEST_F(TextTestSixNg, GetOrCreateTextEffectTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    auto layoutProperty = pattern->GetLayoutProperty<TextLayoutProperty>();
    layoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);

    bool needUpdate = false;
    std::u16string content = u"123";
    auto result = pattern->GetOrCreateTextEffect(content, needUpdate);
    EXPECT_NE(result, nullptr);
    EXPECT_FALSE(needUpdate);

    content = u"124";
    result = pattern->GetOrCreateTextEffect(content, needUpdate);
    EXPECT_NE(result, nullptr);
    EXPECT_TRUE(needUpdate);

    layoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::NONE);

    result = pattern->GetOrCreateTextEffect(content, needUpdate);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: RegularMatchNumbersTest001
 * @tc.desc: Test RegularMatchNumbers with empty content
 */
HWTEST_F(TextTestSixNg, RegularMatchNumbersTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    std::u16string content = u"";
    bool result = pattern->RegularMatchNumbers(content);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: RegularMatchNumbersTest002
 * @tc.desc: Test RegularMatchNumbers with pure numbers
 */
HWTEST_F(TextTestSixNg, RegularMatchNumbersTest002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    std::u16string content = u"1234567890";
    bool result = pattern->RegularMatchNumbers(content);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CreateOrUpdateTextEffectTest001
 * @tc.desc: Test CreateOrUpdateTextEffect with non-number content
 */
HWTEST_F(TextTestSixNg, CreateOrUpdateTextEffectTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    auto layoutAlgorithm = AceType::MakeRefPtr<TextLayoutAlgorithm>();
    auto paragraph = MockParagraph::GetOrCreateMockParagraph();

    // Non-number content should not create text effect
    layoutAlgorithm->CreateOrUpdateTextEffect(nullptr, paragraph, pattern, u"abc");

    // Verify no text effect was created
    auto textEffect = pattern->GetTextEffect();
    EXPECT_EQ(textEffect, nullptr);
}

/**
 * @tc.name: RelayoutResetOrUpdateTextEffect001
 * @tc.desc: Test Update When Values Change
 */
HWTEST_F(TextTestSixNg, RelayoutResetOrUpdateTextEffect001, TestSize.Level1)
{
    auto textPattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, textPattern);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);

    // Set up textEffect_ with initial values.
    textPattern->textEffect_ = TextEffect::CreateTextEffect();
    auto textEffect = AceType::DynamicCast<MockTextEffect>(textPattern->textEffect_);
    ASSERT_NE(textEffect, nullptr);
    textEffect->direction_ = TextFlipDirection::DOWN;
    textEffect->enableBlur_ = false;

    // Call the function with new values (should return -1)
    textLayoutProperty->UpdateTextFlipDirection(TextFlipDirection::UP);
    textLayoutProperty->UpdateTextFlipEnableBlur(true);
    textLayoutProperty->UpdateTextEffectStrategy(TextEffectStrategy::FLIP);
    textPattern->RelayoutResetOrUpdateTextEffect();

    // Verify updates occurred (return value -1)
    EXPECT_EQ(textEffect->direction_, TextFlipDirection::UP);
    EXPECT_EQ(textEffect->enableBlur_, true);
}

/**
 * @tc.name: IsSelectableAndCopyTest001
 * @tc.desc: Test IsSelectableAndCopy when textEffect is not null
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, IsSelectableAndCopyTest001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode("Test", 1, pattern);
    auto textLayoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_NE(textLayoutProperty, nullptr);

    // 设置 SELECTABLE 模式和非 None copyOption
    textLayoutProperty->UpdateTextSelectableMode(TextSelectableMode::SELECTABLE_FOCUSABLE);
    pattern->copyOption_ = CopyOptions::Local;
    pattern->textEffect_ = TextEffect::CreateTextEffect(); // textEffect 不为空

    EXPECT_FALSE(pattern->IsSelectableAndCopy());
}
} // namespace OHOS::Ace::NG
