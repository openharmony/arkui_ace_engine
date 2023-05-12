/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "base/json/json_util.h"
#include "base/utils/utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/test/json/component_factory.h"
#include "core/components/text/text_component.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {
namespace {

constexpr double FONT_SIZE = 10.0;
constexpr double FONT_SIZE_DEFAULT = 14.0;
constexpr int32_t FONT_WEIGHT = 1;
constexpr int32_t FONT_WEIGHT_DEFAULT = 10;
constexpr int32_t FONT_STYLE = 1;
constexpr int32_t FONT_STYLE_DEFAULT = 0;
constexpr int32_t TEXT_BASE_LINE_JSON = 1;
constexpr int32_t TEXT_BASE_LINE_DEFAULT = 0;
constexpr int32_t TEXT_DECORATION_JSON = 1;
constexpr int32_t TEXT_DECORATION_DEFAULT = 0;
constexpr Dimension WORD_SPACING = 10.0_px;
constexpr Dimension WORD_SPACING_DEFAULT = 0.0_px;
constexpr Dimension LETTER_SPACING = 10.0_px;
constexpr Dimension LETTER_SPACING_DEFAULT = 0.0_px;
constexpr double LINE_HEIGHT = 10.0;
constexpr double LINE_HEIGHT_DEFAULT = 0.0;
constexpr uint32_t TEXT_COLOR_VALUE = 255;
constexpr uint32_t TEXT_COLOR_ZERO = 0;
constexpr uint32_t TEXT_COLOR_ALPHA = 100;
constexpr uint32_t TEXT_COLOR_RED = 100;
constexpr uint32_t TEXT_COLOR_GREEN = 100;
constexpr uint32_t TEXT_COLOR_BLUE = 100;
constexpr double OFFSET_DX = 10.0;
constexpr double OFFSET_DY = 15.0;
constexpr double DIMENSION_ZERO = 0.0;
constexpr double SHADOW_BLUR_RADIUS = 10.0;
const std::vector<std::string> FONT_FAMILIES = { "normal", "sans-serif", "serif", "monospace" };
const std::vector<Dimension> PREFER_FONT_SIZES { Dimension(20), Dimension(10), Dimension(5) };
const std::unordered_map<std::string, int32_t> FONT_FEATURES {
    {"liga ", 0},
    {"clig ", 0},
    {"dlig ", 0},
    {"hlig ", 0},
    {"dlig ", 0}
};
const std::string JSON_TEXT_STR = "{                                    "
                                  "  \"className\": \"Text\",           "
                                  "  \"textStyle\":                     "
                                  "{                                    "
                                  "  \"className\": \"TextStyle\",      "
                                  "  \"fontSize\": 10.0,                "
                                  "  \"fontWeight\": 1,                 "
                                  "  \"fontStyle\": 1,                  "
                                  "  \"textBaseline\": 1,               "
                                  "  \"textDecoration\": 1,             "
                                  "  \"wordSpacing\": 10.0,             "
                                  "  \"letterSpacing\": 10.0,           "
                                  "  \"lineHeight\": 10.0,              "
                                  "  \"color\":                         "
                                  "{                                    "
                                  "  \"className\": \"Color\",          "
                                  "  \"value\": 255                     "
                                  "},                                   "
                                  "  \"shadow\":                        "
                                  "{                                    "
                                  "  \"className\": \"Shadow\",         "
                                  "  \"blurRadius\": 10.0,              "
                                  "  \"offset\":                        "
                                  "{                                    "
                                  "  \"className\": \"Offset\",         "
                                  "\"dx\": 10.0,                        "
                                  "\"dy\": 15.0                         "
                                  "},                                   "
                                  "  \"color\":                         "
                                  "{                                    "
                                  "  \"className\": \"Color\",          "
                                  "  \"alpha\": 100,                    "
                                  "  \"red\": 100,                      "
                                  "  \"green\": 100,                    "
                                  "  \"blue\": 100                      "
                                  "}                                    "
                                  "},                                   "
                                  "  \"lineHeight\": 10.0,              "
                                  "  \"fontFamilies\":                  "
                                  "[                                    "
                                  "  \"normal\",                        "
                                  "  \"sans-serif\",                    "
                                  "  \"serif\",                         "
                                  "  \"monospace\"                      "
                                  "]                                    "
                                  "}"
                                  "}";

} // namespace

class TextStyleCreatorTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp();
    void TearDown();

protected:
    RefPtr<TextComponent> CreateComponent(const std::string& textJson);
};

void TextStyleCreatorTest::SetUpTestCase() {}
void TextStyleCreatorTest::TearDownTestCase() {}
void TextStyleCreatorTest::SetUp() {}
void TextStyleCreatorTest::TearDown() {}

RefPtr<TextComponent> TextStyleCreatorTest::CreateComponent(const std::string& textJson)
{
    const auto dslBuf = reinterpret_cast<const uint8_t*>(textJson.c_str());
    size_t dslLen = textJson.length();
    RefPtr<Component> component = ComponentFactory::GetInstance().CreateComponentFromDsl(dslBuf, dslLen);
    if (!component) {
        return nullptr;
    }
    return AceType::DynamicCast<TextComponent>(component);
}

/**
 * @tc.name: TextStyleCreator001
 * @tc.desc: Test all the properties of text style.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create component based on json string.
     */
    RefPtr<TextComponent> text = CreateComponent(JSON_TEXT_STR);
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. All the properties are matched.
     */
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_TRUE(NearEqual(textStyle.GetFontSize().Value(), FONT_SIZE));
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontWeight()), FONT_WEIGHT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontStyle()), FONT_STYLE);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextBaseline()), TEXT_BASE_LINE_JSON);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextDecoration()), TEXT_DECORATION_JSON);
    EXPECT_EQ(textStyle.GetWordSpacing().Unit(), WORD_SPACING.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetWordSpacing().Value(), WORD_SPACING.Value()));
    EXPECT_EQ(textStyle.GetLetterSpacing().Unit(), LETTER_SPACING.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetLetterSpacing().Value(), LETTER_SPACING.Value()));
    EXPECT_TRUE(NearEqual(textStyle.GetLineHeight().Value(), LINE_HEIGHT));
    EXPECT_EQ(textStyle.GetTextColor().GetValue(), TEXT_COLOR_VALUE);

    const auto& textShadow = textStyle.GetTextShadows()[0];
    EXPECT_TRUE(NearEqual(textShadow.GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadow.GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadow.GetBlurRadius(), SHADOW_BLUR_RADIUS));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(textShadowColor.GetAlpha(), TEXT_COLOR_ALPHA);
    EXPECT_EQ(textShadowColor.GetRed(), TEXT_COLOR_RED);
    EXPECT_EQ(textShadowColor.GetGreen(), TEXT_COLOR_GREEN);
    EXPECT_EQ(textShadowColor.GetBlue(), TEXT_COLOR_BLUE);
    EXPECT_TRUE(textStyle.GetFontFamilies() == FONT_FAMILIES);
}

/**
 * @tc.name: TextStyleCreator002
 * @tc.desc: Test all the properties set by default value when value is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with all property.
     */
    const std::string jsonText = "{                                    "
                                 "  \"className\": \"Text\",           "
                                 "  \"textStyle\":                     "
                                 "{                                    "
                                 "  \"className\": \"TextStyle\",      "
                                 "  \"fontSize\": 10.0,                "
                                 "  \"fontWeight\": 10,                "
                                 "  \"fontStyle\": 10,                 "
                                 "  \"textBaseline\": 10,              "
                                 "  \"textDecoration\": 10,            "
                                 "  \"wordSpacing\": 10.0,             "
                                 "  \"letterSpacing\": 10.0,           "
                                 "  \"lineHeight\": 10.0,              "
                                 "  \"fontFamilies\":                  "
                                 "[                                    "
                                 "  \"normal\",                        "
                                 "  \"sans-serif\",                    "
                                 "  \"serif\",                         "
                                 "  \"monospace\"                      "
                                 "]                                    "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. All the properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_TRUE(NearEqual(textStyle.GetFontSize().Value(), FONT_SIZE));
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontWeight()), FONT_WEIGHT_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontStyle()), FONT_STYLE_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextBaseline()), TEXT_BASE_LINE_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextDecoration()), TEXT_DECORATION_DEFAULT);
    EXPECT_EQ(textStyle.GetWordSpacing().Unit(), WORD_SPACING.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetWordSpacing().Value(), WORD_SPACING.Value()));
    EXPECT_EQ(textStyle.GetLetterSpacing().Unit(), LETTER_SPACING.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetLetterSpacing().Value(), LETTER_SPACING.Value()));
    EXPECT_TRUE(NearEqual(textStyle.GetLineHeight().Value(), LINE_HEIGHT));
    EXPECT_TRUE(textStyle.GetFontFamilies() == FONT_FAMILIES);
}

/**
 * @tc.name: TextStyleCreator003
 * @tc.desc: Test all the properties when initialized by default value.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with all property.
     */
    const std::string jsonText = "{                                "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\"  "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. All the properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_TRUE(NearEqual(textStyle.GetFontSize().Value(), FONT_SIZE_DEFAULT));
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontWeight()), FONT_WEIGHT_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetFontStyle()), FONT_STYLE_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextBaseline()), TEXT_BASE_LINE_DEFAULT);
    EXPECT_EQ(static_cast<int32_t>(textStyle.GetTextDecoration()), TEXT_DECORATION_DEFAULT);
    EXPECT_EQ(textStyle.GetWordSpacing().Unit(), WORD_SPACING_DEFAULT.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetWordSpacing().Value(), WORD_SPACING_DEFAULT.Value()));
    EXPECT_EQ(textStyle.GetLetterSpacing().Unit(), LETTER_SPACING_DEFAULT.Unit());
    EXPECT_TRUE(NearEqual(textStyle.GetLetterSpacing().Value(), LETTER_SPACING_DEFAULT.Value()));
    EXPECT_TRUE(NearEqual(textStyle.GetLineHeight().Value(), LINE_HEIGHT_DEFAULT));
}

/**
 * @tc.name: TextStyleCreator004
 * @tc.desc: Test text shadow properties initialized by [offsetX, offsetY] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with all property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"10px 15px \""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow property matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 1UL);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
}

/**
 * @tc.name: TextStyleCreator005
 * @tc.desc: Test text shadow properties when initialized by [offsetX, offsetY, blurRadius] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with shadow property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"10px 15px 10px\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadows[0].GetBlurRadius(), SHADOW_BLUR_RADIUS));
}

/**
 * @tc.name: TextStyleCreator006
 * @tc.desc: Test text shadow properties initialized by [offsetX, offsetY, color] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with all property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"10px 15px #FF0000\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetRed()), TEXT_COLOR_VALUE);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetGreen()), TEXT_COLOR_ZERO);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetBlue()), TEXT_COLOR_ZERO);
}

/**
 * @tc.name: TextStyleCreator007
 * @tc.desc: Test text shadow properties initialized by [color, offsetX, offsetY] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with all property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"#FF0000 10px 15px\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetRed()), TEXT_COLOR_VALUE);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetGreen()), TEXT_COLOR_ZERO);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetBlue()), TEXT_COLOR_ZERO);
}

/**
 * @tc.name: TextStyleCreator008
 * @tc.desc: Test text shadow properties when initialized by [color, offsetX offsetY],
 * [offsetX, offsetY, blurs] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with text shadow property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"#FF0000 10px 15px,\
                                 10px 15px 10px\" "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 2);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadows[1].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[1].GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadows[1].GetBlurRadius(), SHADOW_BLUR_RADIUS));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetRed()), TEXT_COLOR_VALUE);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetGreen()), TEXT_COLOR_ZERO);
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetBlue()), TEXT_COLOR_ZERO);
}

/**
 * @tc.name: TextStyleCreator009
 * @tc.desc: Test text shadow properties when initialized by [color, offsetX offsetY, blurRadius],
 * [offsetX, offsetY, blurRadius, color] forms.
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with shadow property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"#FF0000 10px 15px 10px,\
                                 10px 15px 10px #00FF00\" "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 2);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadows[0].GetBlurRadius(), SHADOW_BLUR_RADIUS));
    EXPECT_TRUE(NearEqual(textShadows[1].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[1].GetOffset().GetY(), OFFSET_DY));
    EXPECT_TRUE(NearEqual(textShadows[1].GetBlurRadius(), SHADOW_BLUR_RADIUS));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetRed()), TEXT_COLOR_VALUE);
    auto textShadowColor2 = textStyle.GetTextShadows()[1].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor2.GetGreen()), TEXT_COLOR_VALUE);
}

/**
 * @tc.name: TextStyleCreator010
 * @tc.desc: Test text shadow properties initialized by special value 0
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with shadow property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textShadow\": \"#FF0000 10px 0 10px\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text shadow properties matched.
     * @tc.expected: step2. text shadow properties are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    const auto& textShadows = textStyle.GetTextShadows();
    EXPECT_EQ(textShadows.size(), 1);
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetX(), OFFSET_DX));
    EXPECT_TRUE(NearEqual(textShadows[0].GetOffset().GetY(), DIMENSION_ZERO));
    EXPECT_TRUE(NearEqual(textShadows[0].GetBlurRadius(), SHADOW_BLUR_RADIUS));
    const auto& textShadowColor = textStyle.GetTextShadows()[0].GetColor();
    EXPECT_EQ(static_cast<uint32_t>(textShadowColor.GetRed()), TEXT_COLOR_VALUE);
}

/**
 * @tc.name: TextStyleCreator011
 * @tc.desc: Test textStyle adaptHeight property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with adaptHeight property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"adaptHeight\": true    "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"adaptHeight\": false    "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check adaptHeight property matched.
     * @tc.expected: step2. text adaptHeight property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetAdaptHeight(), true);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetAdaptHeight(), false);
}

/**
 * @tc.name: TextStyleCreator012
 * @tc.desc: Test textStyle allowScale property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with allowScale property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"allowScale\": false         "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"allowScale\": true          "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check allowScale property matched.
     * @tc.expected: step2. text allowScale property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.IsAllowScale(), false);
    // default allowScale value
    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.IsAllowScale(), true);
}

/**
 * @tc.name: TextStyleCreator013
 * @tc.desc: Test textStyle textColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textcolor property.
     */
    // match for #FFFFFF or #FFFFFFFF.
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"#FF0000\"        "
                                 "}"
                                 "}";

    // special value
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"#FFFFFFFF\"      "
                                 "}"
                                 "}";

    // regexp [0-9A-Fa-f]{3,4},#abc->#aabbcc|maskAlpha
    const std::string jsonText3 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"#FF00\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textColor property matched.
     * @tc.expected: step2. textColor property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextColor(), Color::RED);

    // defalut textColor black
    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextColor(), Color::WHITE);

    // #F00 -> #FFFF0000
    RefPtr<TextComponent> text3 = CreateComponent(jsonText3);
    EXPECT_TRUE(text3 != nullptr);
    const auto& textStyle3 = text3->GetTextStyle();
    EXPECT_EQ(textStyle3.GetTextColor(), Color::RED);
}

/**
 * @tc.name: TextStyleCreator014
 * @tc.desc: Test textStyle textColor property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textcolor property.
     */
    const std::string jsonText4 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"green\""
                                 "}"
                                 "}";

    const std::string jsonText5 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"rgb(0,0,255)\""
                                 "}"
                                 "}";

    const std::string jsonText6 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"color\": \"rgba(0,0,255,255)\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textColor property matched.
     * @tc.expected: step2. textColor property are matched.
     */
    // special value
    RefPtr<TextComponent> text4 = CreateComponent(jsonText4);
    EXPECT_TRUE(text4 != nullptr);
    const auto& textStyle4 = text4->GetTextStyle();
    EXPECT_EQ(textStyle4.GetTextColor(), Color::GREEN);

    // (0,0,255)
    RefPtr<TextComponent> text5 = CreateComponent(jsonText5);
    EXPECT_TRUE(text5 != nullptr);
    const auto& textStyle5 = text5->GetTextStyle();
    EXPECT_EQ(textStyle5.GetTextColor(), Color::FromRGB(0, 0, 255));

    // regx(0,0,255. d+)
    RefPtr<TextComponent> text6 = CreateComponent(jsonText6);
    EXPECT_TRUE(text6 != nullptr);
    const auto& textStyle6 = text6->GetTextStyle();
    EXPECT_EQ(textStyle6.GetTextColor(), Color::FromRGBO(0, 0, 255, 255));
}

/**
 * @tc.name: TextStyleCreator015
 * @tc.desc: Test textStyle fontFamilies property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontFamilies property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontFamilies\": [\"normal\", \"sans-serif\", \"serif\", \"monospace\"] "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check fontFamilies properties matched.
     * @tc.expected: step2. fontFamilies property are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_EQ(textStyle.GetFontFamilies(), FONT_FAMILIES);
}

/**
 * @tc.name: TextStyleCreator016
 * @tc.desc: Test textStyle fontSize property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontSize property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontSize\": 10              "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check fontSize properties matched.
     * @tc.expected: step2. fontSize property are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_TRUE(NearEqual(textStyle.GetFontSize(), Dimension(10.0)));
}

/**
 * @tc.name: TextStyleCreator017
 * @tc.desc: Test textStyle fontStyle property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontStyle property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontStyle\": 1              "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontStyle\": 0              "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. fontStyle property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetFontStyle(), FontStyle::ITALIC);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetFontStyle(), FontStyle::NORMAL);
}

/**
 * @tc.name: TextStyleCreator019
 * @tc.desc: Test textStyle fontWeight property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontWeight property.
     */
    const std::string jsonText1 = "{                              "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontWeight\": 0           "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                              "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontWeight\": 9      "
                                 "}"
                                 "}";

    const std::string jsonText3 = "{                              "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontWeight\": 14   "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check fontWeight properties matched.
     * @tc.expected: step2. fontWeight property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetFontWeight(), FontWeight::W100);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetFontWeight(), FontWeight::BOLD);

    RefPtr<TextComponent> text3 = CreateComponent(jsonText3);
    EXPECT_TRUE(text3 != nullptr);
    const auto& textStyle3 = text3->GetTextStyle();
    EXPECT_EQ(textStyle3.GetFontWeight(), FontWeight::REGULAR);
}

/**
 * @tc.name: TextStyleCreator021
 * @tc.desc: Test textStyle letterSpacing property initialized by percent
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with letterSpacing property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"letterSpacing\": \"50%\"    "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"letterSpacing\": \"10px\"   "
                                 "}"
                                 "}";

    /**
     * @tc.steps: step2. Check letterspacing properties matched.
     * @tc.expected: step2. fontStyle property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetLetterSpacing(), Dimension(50.0, DimensionUnit::PERCENT));

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetLetterSpacing(), Dimension(10, DimensionUnit::PX));
}

/**
 * @tc.name: TextStyleCreator022
 * @tc.desc: Test textStyle letterSpacing property initialized by percent
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with letterSpacing property.
     */
    const std::string jsonText3 = "{                              "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"letterSpacing\": \"10vp\"   "
                                 "}"
                                 "}";

    const std::string jsonText4 = "{                              "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"letterSpacing\": \"10fp\"   "
                                 "}"
                                 "}";

    const std::string jsonText5 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"letterSpacing\": \"10lpx\"  "
                                 "}"
                                 "}";

    /**
     * @tc.steps: step2. Check letterspacing properties matched.
     * @tc.expected: step2. fontStyle property are matched.
     */
    RefPtr<TextComponent> text3 = CreateComponent(jsonText3);
    EXPECT_TRUE(text3 != nullptr);
    const auto& textStyle3 = text3->GetTextStyle();
    EXPECT_EQ(textStyle3.GetLetterSpacing(), Dimension(10, DimensionUnit::VP));

    RefPtr<TextComponent> text4 = CreateComponent(jsonText4);
    EXPECT_TRUE(text4 != nullptr);
    const auto& textStyle4 = text4->GetTextStyle();
    EXPECT_EQ(textStyle4.GetLetterSpacing(), Dimension(10, DimensionUnit::FP));

    RefPtr<TextComponent> text5 = CreateComponent(jsonText5);
    EXPECT_TRUE(text5 != nullptr);
    const auto& textStyle5 = text5->GetTextStyle();
    EXPECT_EQ(textStyle5.GetLetterSpacing(), Dimension(10, DimensionUnit::LPX));
}

/**
 * @tc.name: TextStyleCreator023
 * @tc.desc: Test textStyle lineHeight property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with lineHeight property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"lineHeight\": \"normal\"    "
                                 "}"
                                 "}";

    const std::string jsonText3 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"lineHeight\": \"10px\"      "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. letterSpacing property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetLineHeight(), Dimension(0));

    RefPtr<TextComponent> text3 = CreateComponent(jsonText3);
    EXPECT_TRUE(text3 != nullptr);
    const auto& textStyle3 = text3->GetTextStyle();
    EXPECT_EQ(textStyle3.GetLineHeight(), Dimension(10.0, DimensionUnit::PX));
}

/**
 * @tc.name: TextStyleCreator024
 * @tc.desc: Test textStyle lines property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with lines property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"maxLines\": 10"
                                 "}"
                                 "}";

    // abnormal value
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"maxLines\": 4294967296      "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check text MaxLines properties matched.
     * @tc.expected: step2. MaxLines property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetMaxLines(), 10);
    // abnormal value
    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetMaxLines(), UINT32_MAX);
}

/**
 * @tc.name: TextStyleCreator025
 * @tc.desc: Test textStyle maxFontSize & minFontSize property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with maxFontSize & minFontSize property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"adaptMaxFontSize\": \"100px\", "
                                 "  \"adaptMinFontSize\": \"10px \""
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"adaptMaxFontSize\": \"0px\", "
                                 "  \"adaptMinFontSize\": \"0px \""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check maxFontSize & minFontSize properties matched.
     * @tc.expected: step2. maxFontSize & minFontSize property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetAdaptMaxFontSize(), Dimension(100));
    EXPECT_EQ(textStyle1.GetAdaptMinFontSize(), Dimension(10));
    EXPECT_EQ(textStyle1.GetAdaptTextSize(), true);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetAdaptMaxFontSize(), Dimension(0));
    EXPECT_EQ(textStyle2.GetAdaptMinFontSize(), Dimension(0));
}

/**
 * @tc.name: TextStyleCreator026
 * @tc.desc: Test textStyle preferFontSizes property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with preferFontSizes property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"preferFontSizes\": \"10px, 5px, 20px\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check preferFontSizes properties matched.
     * @tc.expected: step2. preferFontSizes property are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_EQ(textStyle.GetPreferFontSizes(), PREFER_FONT_SIZES);
}

/**
 * @tc.name: TextStyleCreator027
 * @tc.desc: Test textStyle textAlign property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textAlign property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textAlign\": \"right\"      "
                                 "}"
                                 "}";

    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textAlign\": \"left\"      "
                                 "}"
                                 "}";

    const std::string jsonText3 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textAlign\": \"center\"      "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textAlign properties matched.
     * @tc.expected: step2. textAlign property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextAlign(), TextAlign::RIGHT);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextAlign(), TextAlign::LEFT);

    RefPtr<TextComponent> text3 = CreateComponent(jsonText3);
    EXPECT_TRUE(text3 != nullptr);
    const auto& textStyle3 = text3->GetTextStyle();
    EXPECT_EQ(textStyle3.GetTextAlign(), TextAlign::CENTER);
}

/**
 * @tc.name: TextStyleCreator028
 * @tc.desc: Test textStyle textAlign property initialized by normal
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator028, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textAlign property.
     */
    const std::string jsonText4 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textAlign\": \"start\"      "
                                 "}"
                                 "}";

    const std::string jsonText5 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textAlign\": \"end\"      "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textAlign properties matched.
     * @tc.expected: step2. textAlign property are matched.
     */
    RefPtr<TextComponent> text4 = CreateComponent(jsonText4);
    EXPECT_TRUE(text4 != nullptr);
    const auto& textStyle4 = text4->GetTextStyle();
    EXPECT_EQ(textStyle4.GetTextAlign(), TextAlign::START);

    RefPtr<TextComponent> text5 = CreateComponent(jsonText5);
    EXPECT_TRUE(text5 != nullptr);
    const auto& textStyle5 = text5->GetTextStyle();
    EXPECT_EQ(textStyle5.GetTextAlign(), TextAlign::END);
}


/**
 * @tc.name: TextStyleCreator029
 * @tc.desc: Test textStyle textDecoration/textDecorationColor property initialized by overline
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator029, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textDecoration/textDecorationColor  property.
     */
    const std::string jsonText = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textDecoration\": 2,        "
                                 "  \"textDecorationColor\": \"#FF0000\" "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textDecoration/textDecorationColor  properties matched.
     * @tc.expected: step2. textDecoration/textDecorationColor property are matched.
     */
    RefPtr<TextComponent> text = CreateComponent(jsonText);
    EXPECT_TRUE(text != nullptr);
    const auto& textStyle = text->GetTextStyle();
    EXPECT_EQ(textStyle.GetTextDecoration(), TextDecoration::OVERLINE);
    EXPECT_EQ(textStyle.GetTextDecorationColor(), Color::RED);
}

/**
 * @tc.name: TextStyleCreator030
 * @tc.desc: Test textStyle textIndent property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with shadow property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textIndent\": \"10px\"      "
                                 "}"
                                 "}";

    // abnormal textIndent
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textIndent\": \"xpx\"      "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. textDecoration/textDecorationColor property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextIndent(), Dimension(10));

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextIndent(), Dimension(0));
}

/**
 * @tc.name: TextStyleCreator031
 * @tc.desc: Test textStyle textOverflow property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator031, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textOverflow property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textOverflow\": \"ellipsis\""
                                 "}"
                                 "}";

    // abnormal textOverflow
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textOverflow\": \"abc\""
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textOverflow matched.
     * @tc.expected: step2. textDecoration/textDecorationColor property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextOverflow(), TextOverflow::ELLIPSIS);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextOverflow(), TextOverflow::CLIP);
}

/**
 * @tc.name: TextStyleCreator032
 * @tc.desc: Test textStyle textValign property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with textValign property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textValign\": \"bottom\"    "
                                 "}"
                                 "}";

    // abnormal textValign
    const std::string jsonText2 = "{                               "
                                "  \"className\": \"Text\",      "
                                "  \"textStyle\":                "
                                "{                               "
                                "  \"className\": \"TextStyle\", "
                                "  \"textValign\": \"abc\"    "
                                "}"
                                "}";
    /**
     * @tc.steps: step2. Check all the properties matched.
     * @tc.expected: step2. textDecoration/textDecorationColor property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextVerticalAlign(), VerticalAlign::BOTTOM);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextVerticalAlign(), VerticalAlign::NONE);
}

/**
 * @tc.name: TextStyleCreator033
 * @tc.desc: Test textStyle whiteSpace property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with whiteSpace property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"whiteSpace\": \"nowrap\"    "
                                 "}"
                                 "}";
    // abnormal whitespace
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"whiteSpace\": \"abc\"       "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check whiteSpace properties matched.
     * @tc.expected: step2. whiteSpace property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetWhiteSpace(), WhiteSpace::NOWRAP);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetWhiteSpace(), WhiteSpace::NORMAL);
}

/**
 * @tc.name: TextStyleCreator034
 * @tc.desc: Test textStyle wordBreak property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with wordBreak property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"wordBreak\": \"break-all\"  "
                                 "}"
                                 "}";

    // abnormal value
    const std::string jsonText2 = "{                               "
                                "  \"className\": \"Text\",      "
                                "  \"textStyle\":                "
                                "{                               "
                                "  \"className\": \"TextStyle\", "
                                "  \"wordBreak\": \"abc\"  "
                                "}"
                                "}";
    /**
     * @tc.steps: step2. Check wordBreak properties matched.
     * @tc.expected: step2. wordBreak property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetWordBreak(), WordBreak::BREAK_ALL);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetWordBreak(), WordBreak::BREAK_WORD);
}

/**
 * @tc.name: TextStyleCreator035
 * @tc.desc: Test textStyle wordSpacing property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator035, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with wordSpacing property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"wordSpacing\": \"10px\"     "
                                 "}"
                                 "}";
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"wordSpacing\": \"normal\"   "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check wordSpacing properties matched.
     * @tc.expected: step2. wordSpacing property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetWordSpacing(), Dimension(10));

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetWordSpacing(), Dimension(0));
}

/**
 * @tc.name: TextStyleCreator036
 * @tc.desc: Test textStyle fontSizeStep property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontSizeStep property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontSizeStep\": \"10px\"    "
                                 "}"
                                 "}";
    // abnomal fontSizeStep
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"fontSizeStep\": \"abc\"    "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check fontSizeStep properties matched.
     * @tc.expected: step2. fontSizeStep property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetAdaptFontSizeStep(), Dimension(10));

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetAdaptFontSizeStep(), Dimension(0));
}

/**
 * @tc.name: TextStyleCreator037
 * @tc.desc: Test textStyle textCase property
 * @tc.type: FUNC
 */
HWTEST_F(TextStyleCreatorTest, TextStyleCreator037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the json string with fontSizeStep property.
     */
    const std::string jsonText1 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textCase\": 1              "
                                 "}"
                                 "}";
    // abnomal textcase
    const std::string jsonText2 = "{                               "
                                 "  \"className\": \"Text\",      "
                                 "  \"textStyle\":                "
                                 "{                               "
                                 "  \"className\": \"TextStyle\", "
                                 "  \"textCase\": 4               "
                                 "}"
                                 "}";
    /**
     * @tc.steps: step2. Check textCase properties matched.
     * @tc.expected: step2. textCase property are matched.
     */
    RefPtr<TextComponent> text1 = CreateComponent(jsonText1);
    EXPECT_TRUE(text1 != nullptr);
    const auto& textStyle1 = text1->GetTextStyle();
    EXPECT_EQ(textStyle1.GetTextCase(), TextCase::LOWERCASE);

    RefPtr<TextComponent> text2 = CreateComponent(jsonText2);
    EXPECT_TRUE(text2 != nullptr);
    const auto& textStyle2 = text2->GetTextStyle();
    EXPECT_EQ(textStyle2.GetTextCase(), TextCase::NORMAL);
}
} // namespace OHOS::Ace
