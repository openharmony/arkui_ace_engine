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

#include "text_base.h"
#include "test/mock/core/render/mock_canvas_image.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/common/mock_font_manager.h"
#include "core/components/hyperlink/hyperlink_theme.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

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
    fontStyle->UpdateFontWeight(Ace::FontWeight::W200);
    std::vector<std::string> fontFamilies;
    fontFamilies.emplace_back("Arial");
    fontFamilies.emplace_back("Calibri");
    fontStyle->UpdateFontFamily(fontFamilies);
    fontStyle->UpdateFontFeature(ParseFontFeatureSettings("\"ss01\" 0"));
    fontStyle->UpdateTextDecoration(TextDecoration::OVERLINE);
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
    UseSelfStyle(fontStyle, nullptr, textStyle);
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
 * @tc.name: CreateTextStyleUsingThemeWithText001
 * @tc.desc: test text_styles.cpp CreateTextStyleUsingThemeWithText function
 * @tc.type: FUNC
 */
HWTEST_F(TextTestSixNg, CreateTextStyleUsingThemeWithText001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, 0, AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);

    auto fontStyle = std::make_unique<FontStyle>();
    auto textLineStyle = std::make_unique<TextLineStyle>();
    RefPtr<TextTheme> textTheme;

    auto textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle, TextStyle());

    renderContext->UpdateForegroundColorStrategy(ForegroundColorStrategy::INVERT);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);

    renderContext->UpdateForegroundColor(Color::BLACK);
    textStyle = CreateTextStyleUsingThemeWithText(frameNode, fontStyle, textLineStyle, textTheme);
    EXPECT_EQ(textStyle.GetTextColor(), Color::FOREGROUND);
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
} // namespace OHOS::Ace::NG
