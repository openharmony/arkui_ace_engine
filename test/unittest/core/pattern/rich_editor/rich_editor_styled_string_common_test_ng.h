/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_COMMON_TEST_NG_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_COMMON_TEST_NG_H

#include "test/unittest/core/pattern/rich_editor/rich_editor_common_test_ng.h"

namespace OHOS::Ace::NG {

namespace {
const std::u16string INIT_STRING_1 = u"初始属性字符串";
const std::u16string INIT_U16STRING_1 = u"初始属性字符串";
const std::u16string INIT_STRING_2 = u"Hellow World";
const std::u16string INIT_STRING_3 = u"123456";
const std::u16string INSERT_STRING_1 = u"插入";
const std::u16string INSERT_STRING_2 = u"Insert";
const std::u16string INSERT_STRING_3 = u"插入测试字符串";
const std::string TEST_IMAGE_SOURCE = "src/image.png";
const int32_t TEST_MAX_LINE = 10;
const Dimension TEST_BASELINE_OFFSET = Dimension(5, DimensionUnit::PX);
const Dimension TEST_TEXT_INDENT = Dimension(20, DimensionUnit::PX);
const CalcLength TEST_MARGIN_CALC { 10.0, DimensionUnit::CALC };
const CalcLength TEST_PADDING_CALC { 5.0, DimensionUnit::CALC };
const ImageSpanSize TEST_IMAGE_SIZE = { .width = 50.0_vp, .height = 50.0_vp };
const BorderRadiusProperty TEST_BORDER_RADIUS = { 4.0_vp, 4.0_vp, 4.0_vp, 4.0_vp };
const LeadingMarginSize TEST_LEADING_MARGIN_SIZE = { Dimension(5.0), Dimension(10.0) };
const LeadingMargin TEST_LEADING_MARGIN = { .size = TEST_LEADING_MARGIN_SIZE };
const Font TEST_FONT = { FONT_WEIGHT_BOLD, FONT_SIZE_VALUE, ITALIC_FONT_STYLE_VALUE, FONT_FAMILY_VALUE,
    OHOS::Ace::Color::RED, FONT_FAMILY_VALUE};
const SpanParagraphStyle TEST_PARAGRAPH_STYLE = { TextAlign::END, TEST_MAX_LINE, WordBreak::BREAK_ALL,
    TextOverflow::ELLIPSIS, TEST_LEADING_MARGIN, TEST_TEXT_INDENT};
StyledStringChangeValue onStyledStringWillChangeValue;
StyledStringChangeValue onStyledStringDidChangeValue;
} // namespace

class RichEditorStyledStringCommonTestNg : public RichEditorCommonTestNg {
public:
    void SetUp() override;
    void TearDown() override;
    static void TearDownTestSuite();
    RefPtr<MutableSpanString> CreateTextStyledString(const std::u16string& content);
    RefPtr<MutableSpanString> CreateImageStyledString();
    RefPtr<MutableSpanString> CreateCustomSpanStyledString();
    void SetTypingStyle();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_RICH_EDITOR_RICH_EDITOR_STYLED_STRING_COMMON_TEST_NG_H