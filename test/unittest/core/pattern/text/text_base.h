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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H

#include <list>

#include "gtest/gtest.h"
#include "test/unittest/core/pattern/test_ng.h"

#include "core/common/ai/data_detector_adapter.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
using namespace testing;
using namespace testing::ext;

const InspectorFilter filter;
constexpr float RK356_WIDTH = 720.0f;
constexpr float RK356_HEIGHT = 1136.0f;
constexpr float RK356_LOW_WIDTH = 50.0f;
constexpr float RK356_LOW_HEIGHT = 20.0f;
constexpr float TEXT_WIDTH = 100.0f;
constexpr float TEXT_HEIGHT = 75.0f;
constexpr float LARGE_WIDTH = 1000000.0f;
constexpr float DIMENSION = 10.0f;
constexpr float CONTEXT_WIDTH_VALUE = 10.0f;
constexpr float CONTEXT_LARGE_WIDTH_VALUE = 10000.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 10.0f;
constexpr float BASE_LINE_OFFSET_VALUE = 1.0;
constexpr float BASE_LINE_OFFSET = 20.f;
constexpr float TEXT_FONT_SCALE = 2.5f;
constexpr float TEXT_FONT_WEIGHT = 6.0f;
constexpr double RECT_X_VALUE = 1.0;
constexpr double RECT_SECOND_X_VALUE = 2.0;
constexpr double RECT_Y_VALUE = 1.0;
constexpr double RECT_WIDTH_VALUE = 5.0;
constexpr double RECT_HEIGHT_VALUE = 10.0;
constexpr double BLURRADIUS_VALUE = 0.0;
constexpr double SPREADRADIUS_VALUE = 0.0;
constexpr double ADAPT_OFFSETY_VALUE = 5.0;
constexpr double ADAPT_OFFSETX_VALUE = 5.0;
constexpr double FONT_SIZE = 25.0;
const std::string TEXT_CONTENT = "text";
const std::u16string TEXT_U16CONTENT = u"text";
constexpr int32_t TEXT_ERROR = -1;
constexpr int32_t TEXT_SIZE_INT = 10;
constexpr int32_t MAX_LINES = 500;
constexpr int32_t CURSOR_COLOR = 0;
constexpr int32_t SELECTED_COLOR = 0;
constexpr Dimension BASELINE_OFFSET_VALUE = Dimension(20, DimensionUnit::PX);
constexpr Dimension ADAPT_MIN_FONT_SIZE_VALUE = Dimension(50, DimensionUnit::PX);
constexpr Dimension ADAPT_OVER_MIN_FONT_SIZE_VALUE = Dimension(100, DimensionUnit::PX);
constexpr Dimension ADAPT_ZERO_FONT_SIZE_VALUE = Dimension(0, DimensionUnit::PX);
constexpr Dimension ADAPT_MAX_FONT_SIZE_VALUE_S = Dimension(80, DimensionUnit::PX);
constexpr Dimension ADAPT_FONT_SIZE_STEP_VALUE = Dimension(10, DimensionUnit::PX);
const std::string CREATE_VALUE = "Hello World";
const std::u16string CREATE_VALUE_W = u"Hello World";
const SizeF CONTAINER_SIZE(RK356_WIDTH, RK356_HEIGHT);
const SizeF CONTAINER_LOW_SIZE(RK356_LOW_WIDTH, RK356_LOW_HEIGHT);
const SizeF TEXT_SIZE(TEXT_WIDTH, TEXT_HEIGHT);
const SizeF LARGE_CONTAINER_SIZE(LARGE_WIDTH, TEXT_HEIGHT);
constexpr Dimension ADAPT_LINE_HEIGHT_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension ADAPT_FONT_SIZE_VALUE = Dimension(30, DimensionUnit::PX);
constexpr Dimension ADAPT_BASE_LINE_OFFSET_VALUE = Dimension(10, DimensionUnit::PX);
constexpr Dimension ADAPT_LINE_SPACING_VALUE = Dimension(10, DimensionUnit::PX);
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const SizeT<float> LARGE_SIZE = SizeT<float>(10000.0f, 1000.0f);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextAlign TEXT_ALIGN_VALUE = Ace::TextAlign::CENTER;
const Ace::TextOverflow TEXT_OVERFLOW_VALUE = Ace::TextOverflow::CLIP;
const uint32_t MAX_LINES_VALUE = 10;
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension ADAPT_MAX_FONT_SIZE_VALUE = Dimension(200, DimensionUnit::PX);
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension TEXT_INDENT = Dimension(5, DimensionUnit::PX);
const Dimension ADAPT_UPDATE_FONTSIZE_VALUE = Dimension(50, DimensionUnit::PX);
const Dimension LINE_SPACING_VALUE = Dimension(20, DimensionUnit::PX);
const Dimension LINE_SPACING_VALUE_1 = Dimension(30, DimensionUnit::PX);
const std::string ROOT_TAG("root");
constexpr int32_t NODE_ID = 143;
const Color FOREGROUND_COLOR_VALUE = Color::FOREGROUND;
const RectF CONTENT_RECT(3.0, 3.0, TEXT_WIDTH, TEXT_HEIGHT);
constexpr int32_t ROOT_NODE_ID = 113;
const std::string EMPTY_TEXT = "";
const CopyOptions copyOption = CopyOptions::None;
constexpr int32_t UNKNOWN_REASON = 1;
constexpr float TEXT_RECT_SIZE_ZEOR = 0.0f;
constexpr float TEXT_RECT_WIDTH = 10.0f;
constexpr float TEXT_RECT_TOP_ONE = 10.0f;
constexpr float TEXT_RECT_TOP_TWO = 20.0f;
constexpr float TEXT_CONTENT_SIZE = 50.0f;
constexpr float TEXT_CONTENT_OFFSET = 2.25f;
const std::string TEXT_DEFAULT_VALUE =
    "{\"style\":\"FontStyle.Normal\",\"size\":\"16.00fp\",\"weight\":"
    "\"FontWeight.Normal\",\"variableFontWeight\":\"0\",\"enableVariableFontWeight\":\"false\",\"family\":"
    "\"HarmonyOS Sans\"}";
const std::string WITH_THEME_CALL_TEXT_DEFAULT_VALUE =
    "{\"style\":\"FontStyle.Normal\",\"size\":\"14.00px\",\"weight\":"
    "\"FontWeight.Normal\",\"variableFontWeight\":\"0\",\"enableVariableFontWeight\":\"false\",\"family\":"
    "\"HarmonyOS Sans\"}";
const std::string TEXT_EQUALS_VALUE =
    R"({"style":"FontStyle.Italic","size":"20.10px","weight":"FontWeight.Bold",)"
    R"("variableFontWeight":"0","enableVariableFontWeight":"false","family":"cursive"})";
const Ace::WordBreak TEXT_WORD_BREAK = Ace::WordBreak::BREAK_ALL;
const Ace::LineBreakStrategy TEXT_LINE_BREAK_STRATEGY = Ace::LineBreakStrategy::GREEDY;
const std::string TEXT_FOR_AI_SINGLE = "phone: 18888888888";
const std::string TEXT_FOR_AI = "phone: 12345678900,url: www.baidu.com";
const std::u16string U16TEXT_FOR_AI = u"phone: 12345678900,url: www.baidu.com";
const std::string SPAN_PHONE = "12345678900";
const std::u16string SPAN_PHONE_U16 = u"12345678900";
const std::string SPAN_URL = "www.baidu.com";
const std::string SPAN_HTTP_URL = "https://www.baidu.com";
const std::u16string SPAN_HTTP_URL_U16 = u"https://www.baidu.com";
const std::u16string SPAN_URL_U16 = u"www.baidu.com";
constexpr int32_t AI_SPAN_START = 7;
constexpr int32_t AI_SPAN_END = 18;
constexpr int32_t AI_SPAN_START_II = 24;
constexpr int32_t AI_SPAN_END_II = 37;
const std::string MULTIPLE_SPAN1 = "Span1";
const std::string MULTIPLE_SPAN2 = "Span2\n";
const std::string MULTIPLE_SPAN3 = "Span3\n";
const std::string MULTIPLE_SPAN4 = "Span4";
const std::u16string MULTIPLE_SPAN1_U16 = u"Span1";
const std::u16string MULTIPLE_SPAN2_U16 = u"Span2\n";
const std::u16string MULTIPLE_SPAN3_U16 = u"Span3\n";
const std::u16string MULTIPLE_SPAN4_U16 = u"Span4";
using OnClickCallback = std::function<void(const BaseEventInfo* info)>;
using DragDropBaseCallback = std::function<DragDropBaseInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
constexpr uint32_t CODE1 = 6;
constexpr uint32_t CODE2 = 10000;
constexpr uint32_t CODE3 = 111888;
const char TEXT_CONTENT1[] = "hi";
const char TEXT_CONTENT2[] = "hello1";

struct TestProperty {
    std::optional<Dimension> fontSizeValue = std::nullopt;
    std::optional<Color> textColorValue = std::nullopt;
    std::optional<Ace::FontStyle> italicFontStyleValue = std::nullopt;
    std::optional<Ace::FontWeight> fontWeightValue = std::nullopt;
    std::optional<std::vector<std::string>> fontFamilyValue = std::nullopt;
    std::optional<Ace::TextAlign> textAlignValue = std::nullopt;
    std::optional<Ace::TextOverflow> textOverflowValue = std::nullopt;
    std::optional<uint32_t> maxLinesValue = std::nullopt;
    std::optional<Dimension> lineHeightValue = std::nullopt;
    std::optional<Dimension> lineSpacingValue = std::nullopt;
    std::optional<bool> isOnlyBetweenLines = std::nullopt;
    std::optional<Ace::TextDecoration> textDecorationValue = std::nullopt;
    std::optional<Color> textDecorationColorValue = std::nullopt;
    std::optional<Dimension> baselineOffsetValue = std::nullopt;
    std::optional<Ace::TextCase> textCaseValue = std::nullopt;
    std::optional<Dimension> adaptMinFontSize = std::nullopt;
    std::optional<Dimension> adaptMaxFontSize = std::nullopt;
    std::optional<Dimension> letterSpacing = std::nullopt;
    std::optional<Dimension> textIndent = std::nullopt;
    std::optional<Ace::WordBreak> wordBreak = std::nullopt;
    std::optional<Ace::LineBreakStrategy> lineBreakStrategy = std::nullopt;
};

struct ImageSpanNodeProperty {
    std::optional<std::string> imageSrc = std::nullopt;
    std::optional<RefPtr<PixelMap>> pixelMap = std::nullopt;
    std::optional<MarginPropertyF> margin = std::nullopt;
    std::optional<ImageFit> imageFit = std::nullopt;
    std::optional<VerticalAlign> verticalAlign = std::nullopt;
};

// include span string and position
struct AISpanTestInfo {
    std::variant<std::string, std::u16string> content;
    vector<Ace::AISpan> aiSpans;
};

const AISpanTestInfo U16_TEXT_FOR_AI_INFO = { std::u16string(u"phone: 12345678900,url: www.baidu.com Hello World"),
                                              { {7, 18, "12345678900", TextDataDetectType::PHONE_NUMBER},
                                                {24, 37, "www.baidu.com", TextDataDetectType::URL} }
                                            };

const AISpanTestInfo U16_TEXT_FOR_AI_INFO_2 = { std::u16string(u"email: 1234@abc.com,date: 2025.09.12, "),
                                                { {7, 19, "12345678900", TextDataDetectType::EMAIL},
                                                  {26, 36, "www.baidu.com", TextDataDetectType::DATE_TIME} }
                                              };

class TextBases : public TestNG {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
    RefPtr<SpanNode> CreateSpanNodeWithSetDefaultProperty(const std::u16string& content);
    RefPtr<ImageSpanNode> CreateImageSpanNode(const ImageSpanNodeProperty& property);

protected:
    static void onClickFunc(const BaseEventInfo* info);
    static void onRemoteMessage();
    static void OnDragDropFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&);
    static DragDropBaseInfo OnDragStartFunction(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&);
    static void SuppressMockParagraph();
    static std::pair<RefPtr<FrameNode>, RefPtr<TextPattern>> Init();
    static void TestUpdateScenario(const RefPtr<TextPattern>& pattern);
    static void ConstructSpanItemList1(std::list<RefPtr<SpanItem>>& spans);
    static RefPtr<FrameNode> CreateTextParagraph(const std::u16string& createValue, const TestProperty& testProperty);
    static void SetContentModifier(TextContentModifier& textContentModifier);
    static void SetPaintMethodModifier(TextPaintMethod& textPaintMethod);
    static void UpdateTextLayoutProperty(RefPtr<TextLayoutProperty> textLayoutProperty);
};

class TextPatternTestNg : public TestNG {
    void SetUp() override;
    void TearDown() override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_TEXTFIELD_TEXTINPUT_TEST_NG_H