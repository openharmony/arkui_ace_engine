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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H

#include "gtest/gtest.h"

#define private public
#define protected public

#include "core/components_ng/pattern/rich_editor/rich_editor_content_pattern.h"
#include "core/components_ng/pattern/rich_editor/rich_editor_pattern.h"
#include "test/unittest/core/pattern/test_ng.h"

namespace OHOS::Ace::NG {
namespace {
const std::string TEST_STR = "test";
const std::u16string INIT_VALUE_1 = u"hello1";
const std::u16string INIT_VALUE_2 = u"hello2";
const std::u16string INIT_VALUE_3 = u"hello world! hello world! hello world!";
const std::u16string TEST_INSERT_VALUE = u"s";
const std::u16string TEST_INSERT_LINE_SEP = u"\n";
const std::u16string EXCEPT_VALUE = u"h\n";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Dimension FONT_SIZE_VALUE_2 = Dimension(40, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const Ace::FontWeight FONT_WEIGHT_VALUE = Ace::FontWeight::W100;
const Ace::FontWeight FONT_WEIGHT_BOLD = Ace::FontWeight::BOLD;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const float TEXT_DECORATION_THICKNESS_SCALE = 5.0f;
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
const Dimension LINE_HEIGHT_VALUE = Dimension(20.1, DimensionUnit::PX);
const Shadow TEXT_SHADOW1 = Shadow(0, 0, Offset(), Color::RED);
const Shadow TEXT_SHADOW2 = Shadow(0, 0, Offset(), Color::WHITE);
const std::vector<Shadow> SHADOWS { TEXT_SHADOW1, TEXT_SHADOW2 };
const std::string IMAGE_VALUE = "image1";
const std::string BUNDLE_NAME = "bundleName";
const std::string MODULE_NAME = "moduleName";
const std::u16string PREVIEW_TEXT_VALUE1 = u"nihao";
const std::u16string PREVIEW_TEXT_VALUE2 = u"nihaodajia";
const std::u16string PREVIEW_TEXT_VALUE3 = u"dajia";
const std::string ROOT_TAG = "root";
const CalcLength CALC_LENGTH_CALC { 10.0, DimensionUnit::CALC };
const CalcLength ERROR_CALC_LENGTH_CALC { -10.0, DimensionUnit::CALC };
const Dimension CALC_TEST { 10.0, DimensionUnit::CALC };
const Dimension ERROR_CALC_TEST { -10.0, DimensionUnit::CALC };
const Offset MOUSE_GLOBAL_LOCATION = { 100, 200 };
constexpr int32_t WORD_LIMIT_LEN = 6;
constexpr int32_t WORD_LIMIT_RETURN = 2;
constexpr int32_t BEYOND_LIMIT_RETURN = 4;
constexpr int32_t DEFAULT_RETURN_VALUE = -1;
constexpr int32_t THIRD_PARAM = 2;
const float CONTAINER_WIDTH = 300.0f;
const float CONTAINER_HEIGHT = 300.0f;
const float BUILDER_WIDTH = 150.0f;
const float BUILDER_HEIGHT = 75.0f;
const SizeF BUILDER_SIZE(BUILDER_WIDTH, BUILDER_HEIGHT);
const uint32_t SYMBOL_ID = 1;
const std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE = {{ "subs", 1 }};
const std::list<std::pair<std::string, int32_t>> TEXT_FONTFEATURE_2 = {{ "subs", 0 }};
const std::vector<Color> SYMBOL_COLOR_LIST_1 = { Color::FromRGB(255, 100, 100) };
const std::vector<Color> SYMBOL_COLOR_LIST_2 = { Color::FromRGB(255, 100, 100), Color::FromRGB(255, 255, 100) };
const uint32_t RENDER_STRATEGY_SINGLE = 0;
const uint32_t RENDER_STRATEGY_MULTI_COLOR = 1;
const uint32_t EFFECT_STRATEGY_NONE = 0;
const uint32_t EFFECT_STRATEGY_SCALE = 1;
const SizeF CONTAINER_SIZE(720.0f, 1136.0f);
constexpr float DEFAILT_OPACITY = 0.2f;
constexpr Color SYSTEM_CARET_COLOR = Color(0xff007dff);
constexpr Color SYSTEM_SELECT_BACKGROUND_COLOR = Color(0x33007dff);
constexpr float CONTEXT_WIDTH_VALUE = 300.0f;
constexpr float CONTEXT_HEIGHT_VALUE = 150.0f;
const Color DEFAULT_TEXT_COLOR_VALUE = Color::FromARGB(229, 0, 0, 0);
const TextStyle TEXT_STYLE_1(10.0);
const TextStyle TEXT_STYLE_2(20.0);
const TextStyle TEXT_STYLE_3(30.0);
const TextSpanOptions TEXT_SPAN_OPTIONS_1 = { .value = INIT_VALUE_1, .style = TEXT_STYLE_1 };
const ImageSpanAttribute IMAGE_SPAN_ATTRIBUTE_1 = {
    .size = ImageSpanSize{ .width = 200.0_px, .height = 100.0_px },
    .verticalAlign = VerticalAlign::CENTER,
    .objectFit = ImageFit::COVER,
    .marginProp = std::nullopt,
    .borderRadius = std::nullopt,
    .paddingProp = std::nullopt
};
const ImageSpanOptions IMAGE_SPAN_OPTIONS_1 = {
    .offset = std::nullopt,
    .image = "app.media.icon",
    .bundleName = std::nullopt,
    .moduleName = std::nullopt,
    .imagePixelMap = std::nullopt,
    .imageAttribute = IMAGE_SPAN_ATTRIBUTE_1
};
const SymbolSpanOptions SYMBOL_SPAN_OPTIONS_1 = {
    .offset = std::nullopt,
    .symbolId = 1,
    .style = TEXT_STYLE_1,
    .resourceObject = nullptr
};
} // namespace

struct TestCursorItem {
    int32_t index;
    CaretMetricsF caretMetricsFDown;
    CaretMetricsF caretMetricsFUp;
};

struct TestParagraphRect {
    int32_t start;
    int32_t end;
    std::vector<RectF> rects;
};

struct TestParagraphItem {
    int32_t start;
    int32_t end;
    int32_t height;
    ParagraphStyle paragraphStyle;
    std::map<int32_t, Offset> indexOffsetMap;
    std::vector<TestCursorItem> testCursorItems;
    std::vector<TestParagraphRect> testParagraphRects;
};

class RichEditorCommonTestNg : public TestNG {
public:
    void AddSpan(const std::u16string& content);
    void AddSpan(const std::string& content);
    void AddImageSpan();
    void AddParagraph(TestParagraphItem testParagraphItem);
    void ClearParagraph();
    void ClearSpan();
    RefPtr<FrameNode> richEditorNode_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_COMMON_TEST_NG_H