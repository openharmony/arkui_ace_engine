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

#include <functional>
#include <optional>

#include "gtest/gtest.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string CREATE_VALUE = "Hello World";
const Dimension FONT_SIZE_VALUE = Dimension(20.1, DimensionUnit::PX);
const Color TEXT_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::FontStyle ITALIC_FONT_STYLE_VALUE = Ace::FontStyle::ITALIC;
const std::vector<std::string> FONT_FAMILY_VALUE = { "cursive" };
const Ace::TextDecoration TEXT_DECORATION_VALUE = Ace::TextDecoration::INHERIT;
const Color TEXT_DECORATION_COLOR_VALUE = Color::FromRGB(255, 100, 100);
const Ace::TextCase TEXT_CASE_VALUE = Ace::TextCase::LOWERCASE;
const Dimension LETTER_SPACING = Dimension(10, DimensionUnit::PX);
void onclickFunc(const BaseEventInfo* info) {};
} // namespace

class SpanPatternTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SpanPatternTestNg::SetUpTestCase() {}
void SpanPatternTestNg::TearDownTestCase() {}
void SpanPatternTestNg::SetUp() {}
void SpanPatternTestNg::TearDown() {}

/**
 * @tc.name: SpanFrameNodeCreator001
 * @tc.desc: Test all the properties of text.
 * @tc.type: FUNC
 */
HWTEST_F(SpanPatternTestNg, SpanFrameNodeCreator001, TestSize.Level1)
{
    SpanModelNG spanModelNG;
    spanModelNG.Create(CREATE_VALUE);
    auto spanNode = AceType::DynamicCast<SpanNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    spanModelNG.SetFontSize(FONT_SIZE_VALUE);
    spanModelNG.SetTextColor(TEXT_COLOR_VALUE);
    spanModelNG.SetItalicFontStyle(ITALIC_FONT_STYLE_VALUE);
    spanModelNG.SetFontFamily(FONT_FAMILY_VALUE);
    EXPECT_EQ(spanNode->GetFontSize(), FONT_SIZE_VALUE);
    EXPECT_EQ(spanNode->GetTextColor(), TEXT_COLOR_VALUE);
    EXPECT_EQ(spanNode->GetItalicFontStyle(), ITALIC_FONT_STYLE_VALUE);
    EXPECT_EQ(spanNode->GetFontFamily(), FONT_FAMILY_VALUE);

    spanModelNG.SetTextDecoration(TEXT_DECORATION_VALUE);
    spanModelNG.SetTextDecorationColor(TEXT_DECORATION_COLOR_VALUE);
    spanModelNG.SetTextCase(TEXT_CASE_VALUE);
    spanModelNG.SetLetterSpacing(LETTER_SPACING);
    EXPECT_EQ(spanNode->GetTextDecoration(), TEXT_DECORATION_VALUE);
    EXPECT_EQ(spanNode->GetTextDecorationColor(), TEXT_DECORATION_COLOR_VALUE);
    EXPECT_EQ(spanNode->GetTextCase(), TEXT_CASE_VALUE);
    EXPECT_EQ(spanNode->GetLetterSpacing(), LETTER_SPACING);

    spanModelNG.SetFontWeight(FontWeight::LIGHTER);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W100);
    spanModelNG.SetFontWeight(FontWeight::REGULAR);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W400);
    spanModelNG.SetFontWeight(FontWeight::NORMAL);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W400);
    spanModelNG.SetFontWeight(FontWeight::MEDIUM);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W500);
    spanModelNG.SetFontWeight(FontWeight::BOLD);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W700);
    spanModelNG.SetFontWeight(FontWeight::BOLDER);
    EXPECT_EQ(spanNode->GetFontWeight(), FontWeight::W900);
    spanModelNG.SetOnClick(onclickFunc);
}
} // namespace OHOS::Ace::NG
