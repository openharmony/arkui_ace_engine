/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "core/components_ng/pattern/text/span/span_group_hash_calculator.h"
#include "core/components_ng/pattern/text/paragraph_util.h"
#include "core/components_ng/pattern/text/span_node.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const std::u16string TEXT_HELLO = u"Hello";
const std::u16string TEXT_WORLD = u"World";
const std::u16string TEXT_HELLO_NEWLINE = u"Hello\n";
const std::u16string TEXT_WORLD_NEWLINE = u"World\n";
const std::u16string TEXT_EMPTY = u"";
constexpr int32_t INTERVAL_START_ZERO = 0;
constexpr int32_t INTERVAL_END_FIVE = 5;
constexpr uint32_t TEST_MAX_LINES_LIMITED = 2;
constexpr double TEST_FONT_SIZE_VALUE = 20.0;
} // namespace

RefPtr<SpanItem> CreateSpanItem(const std::u16string& content,
    int32_t intervalStart = INTERVAL_START_ZERO, int32_t intervalEnd = INTERVAL_END_FIVE)
{
    auto span = AceType::MakeRefPtr<SpanItem>();
    span->content = content;
    span->interval = { intervalStart, intervalEnd };
    span->spanItemType = SpanItemType::NORMAL;
    return span;
}

RefPtr<SpanItem> CreateSpanItemWithFontSize(const std::u16string& content, double fontSize)
{
    auto span = CreateSpanItem(content);
    span->fontStyle = std::make_unique<FontStyle>();
    span->fontStyle->UpdateFontSize(Dimension(fontSize, DimensionUnit::PX));
    return span;
}

RefPtr<SpanItem> CreateSpanItemWithFontSize(const std::u16string& content, const Dimension& fontSize)
{
    auto span = CreateSpanItem(content);
    span->fontStyle = std::make_unique<FontStyle>();
    span->fontStyle->UpdateFontSize(fontSize);
    return span;
}

RefPtr<SpanItem> CreateSpanItemWithMaxLines(const std::u16string& content, uint32_t maxLines)
{
    auto span = CreateSpanItem(content);
    span->textLineStyle = std::make_unique<TextLineStyle>();
    span->textLineStyle->UpdateMaxLines(maxLines);
    return span;
}

RefPtr<SpanItem> CreateSpanItemWithBackgroundStyle(const std::u16string& content, const TextBackgroundStyle& style)
{
    auto span = CreateSpanItem(content);
    span->SetBackgroundStyle(style);
    return span;
}

// ==================== SpanGroupHashCalculator Tests ====================

class SpanGroupHashCalculatorTestNg : public testing::Test {
public:
    void SetUp() override
    {
        MockPipelineContext::SetUp();
        auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
        MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
        EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    }

    void TearDown() override
    {
        MockPipelineContext::TearDown();
    }
};

/**
 * @tc.name: SpanGroupHashCalculateEmptySpans001
 * @tc.desc: Test Calculate returns empty result when input span list is empty
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateEmptySpans001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_TRUE(result.contentHashes.empty());
    EXPECT_TRUE(result.styleHashes.empty());
}

/**
 * @tc.name: SpanGroupHashCalculateSingleSpanNoNewline001
 * @tc.desc: Test Calculate produces one hash group for single span without newline
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateSingleSpanNoNewline001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(1));
    EXPECT_EQ(result.styleHashes.size(), static_cast<size_t>(1));
    EXPECT_NE(result.contentHashes[0], static_cast<uint64_t>(0));
}

/**
 * @tc.name: SpanGroupHashCalculateSingleSpanWithNewline001
 * @tc.desc: Test Calculate produces one group when single trailing newline has no following real span
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateSingleSpanWithNewline001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(1));
    EXPECT_EQ(result.styleHashes.size(), static_cast<size_t>(1));
    EXPECT_NE(result.contentHashes[0], static_cast<uint64_t>(0));
}

/**
 * @tc.name: SpanGroupHashCalculateMultipleSpansNoNewline001
 * @tc.desc: Test Calculate produces one group for multiple spans without newlines
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateMultipleSpansNoNewline001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO, 0, 5));
    spans.push_back(CreateSpanItem(TEXT_WORLD, 5, 10));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(1));
    EXPECT_EQ(result.styleHashes.size(), static_cast<size_t>(1));
}

/**
 * @tc.name: SpanGroupHashCalculateNewlineSplit001
 * @tc.desc: Test Calculate splits into separate groups when span ends with newline
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateNewlineSplit001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    spans.push_back(CreateSpanItem(TEXT_WORLD, 6, 11));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(2));
    EXPECT_EQ(result.styleHashes.size(), static_cast<size_t>(2));
}

/**
 * @tc.name: SpanGroupHashCalculateNullSpan001
 * @tc.desc: Test Calculate skips null spans without crashing
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateNullSpan001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(nullptr);
    spans.push_back(CreateSpanItem(TEXT_HELLO));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(1));
}

/**
 * @tc.name: SpanGroupHashCalculateConsistency001
 * @tc.desc: Test Calculate produces identical hashes for identical inputs
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateConsistency001, TestSize.Level1)
{
    // Use the same span object to ensure identical input (including nodeId_)
    auto sharedSpan = CreateSpanItem(TEXT_HELLO);
    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(sharedSpan);
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(sharedSpan);

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    EXPECT_EQ(result1.contentHashes.size(), result2.contentHashes.size());
    EXPECT_EQ(result1.contentHashes[0], result2.contentHashes[0]);
    EXPECT_EQ(result1.styleHashes[0], result2.styleHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateDifferentContent001
 * @tc.desc: Test Calculate produces different content hashes for different content
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateDifferentContent001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(CreateSpanItem(TEXT_HELLO));
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(CreateSpanItem(TEXT_WORLD));

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    EXPECT_NE(result1.contentHashes[0], result2.contentHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateStyleDifference001
 * @tc.desc: Test Calculate produces different style hashes for different font sizes
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateStyleDifference001, TestSize.Level1)
{
    auto span1 = CreateSpanItemWithFontSize(TEXT_HELLO, TEST_FONT_SIZE_VALUE);
    auto span2 = CreateSpanItemWithFontSize(TEXT_HELLO, TEST_FONT_SIZE_VALUE * 2);
    // Set same nodeId so content hash matches — only style should differ
    span2->nodeId_ = span1->nodeId_;

    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(span1);
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(span2);

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    // Content hashes should be the same (same content and interval)
    EXPECT_EQ(result1.contentHashes[0], result2.contentHashes[0]);
    // Style hashes should differ (different font size)
    EXPECT_NE(result1.styleHashes[0], result2.styleHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateEquivalentFontSizeUnits001
 * @tc.desc: Test Calculate keeps style hash stable when font sizes convert to the same px value
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateEquivalentFontSizeUnits001, TestSize.Level1)
{
    auto span1 = CreateSpanItemWithFontSize(TEXT_HELLO, Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::PX));
    auto span2 = CreateSpanItemWithFontSize(TEXT_HELLO, Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::VP));
    span2->nodeId_ = span1->nodeId_;

    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(span1);
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(span2);

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    EXPECT_EQ(result1.contentHashes[0], result2.contentHashes[0]);
    EXPECT_NE(result1.styleHashes[0], result2.styleHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateBackgroundStyleDifference001
 * @tc.desc: Test Calculate produces different style hashes for different background styles
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateBackgroundStyleDifference001, TestSize.Level1)
{
    TextBackgroundStyle style1;
    style1.backgroundColor = Color::RED;

    TextBackgroundStyle style2;
    style2.backgroundColor = Color::BLUE;

    auto span1 = CreateSpanItemWithBackgroundStyle(TEXT_HELLO, style1);
    auto span2 = CreateSpanItemWithBackgroundStyle(TEXT_HELLO, style2);
    span2->nodeId_ = span1->nodeId_;

    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(span1);
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(span2);

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    EXPECT_EQ(result1.contentHashes[0], result2.contentHashes[0]);
    EXPECT_NE(result1.styleHashes[0], result2.styleHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateBackgroundStyleGroupIdIgnored001
 * @tc.desc: Test Calculate keeps style hash stable when only background style groupId differs
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateBackgroundStyleGroupIdIgnored001, TestSize.Level1)
{
    TextBackgroundStyle style1;
    style1.backgroundColor = Color::RED;
    style1.groupId = 1;
    style1.needCompareGroupId = true;

    TextBackgroundStyle style2 = style1;
    style2.groupId = 2;
    style2.needCompareGroupId = false;

    auto span1 = CreateSpanItemWithBackgroundStyle(TEXT_HELLO, style1);
    auto span2 = CreateSpanItemWithBackgroundStyle(TEXT_HELLO, style2);
    span2->nodeId_ = span1->nodeId_;

    std::list<RefPtr<SpanItem>> spans1;
    spans1.push_back(span1);
    std::list<RefPtr<SpanItem>> spans2;
    spans2.push_back(span2);

    auto result1 = SpanGroupHashCalculator::Calculate(spans1);
    auto result2 = SpanGroupHashCalculator::Calculate(spans2);
    EXPECT_EQ(result1.contentHashes[0], result2.contentHashes[0]);
    EXPECT_EQ(result1.styleHashes[0], result2.styleHashes[0]);
}

/**
 * @tc.name: SpanGroupHashCalculateMultipleNewlines001
 * @tc.desc: Test Calculate produces correct number of groups for multiple newline spans
 * @tc.type: FUNC
 */
HWTEST_F(SpanGroupHashCalculatorTestNg, SpanGroupHashCalculateMultipleNewlines001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    spans.push_back(CreateSpanItem(TEXT_WORLD_NEWLINE, 6, 12));
    auto result = SpanGroupHashCalculator::Calculate(spans);
    EXPECT_EQ(result.contentHashes.size(), static_cast<size_t>(2));
    EXPECT_EQ(result.styleHashes.size(), static_cast<size_t>(2));
}

// ==================== ParagraphUtil::ConstructParagraphSpanGroupForHash Tests ====================

class ConstructParagraphSpanGroupForHashTestNg : public testing::Test {
public:
    void SetUp() override {}
    void TearDown() override {}
};

/**
 * @tc.name: ConstructSpanGroupForHashEmptySpans001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash with empty input produces no groups
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashEmptySpans001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    EXPECT_TRUE(spanGroupVec.empty());
    EXPECT_FALSE(spanStringHasMaxLines);
}

/**
 * @tc.name: ConstructSpanGroupForHashSingleSpanNoNewline001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash creates single group for span without newline
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashSingleSpanNoNewline001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    ASSERT_EQ(spanGroupVec.size(), static_cast<size_t>(1));
    EXPECT_EQ(spanGroupVec[0].size(), static_cast<size_t>(1));
    EXPECT_EQ(spanGroupVec[0].front()->content, TEXT_HELLO);
}

/**
 * @tc.name: ConstructSpanGroupForHashNewlineSplit001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash splits at newline boundary
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashNewlineSplit001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    spans.push_back(CreateSpanItem(TEXT_WORLD, 6, 11));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    ASSERT_EQ(spanGroupVec.size(), static_cast<size_t>(2));
    EXPECT_EQ(spanGroupVec[0].front()->content, TEXT_HELLO_NEWLINE);
    EXPECT_TRUE(spanGroupVec[0].front()->needRemoveNewLine);
    EXPECT_EQ(spanGroupVec[1].front()->content, TEXT_WORLD);
    EXPECT_FALSE(spanGroupVec[1].front()->needRemoveNewLine);
}

/**
 * @tc.name: ConstructSpanGroupForHashTrailingNewline001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash keeps trailing newline in last real group
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashTrailingNewline001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    ASSERT_EQ(spanGroupVec.size(), static_cast<size_t>(1));
    ASSERT_FALSE(spanGroupVec[0].empty());
    EXPECT_FALSE(spanGroupVec[0].front()->needRemoveNewLine);
}

/**
 * @tc.name: ConstructSpanGroupForHashTrailingNewlineWithFollowingSpan001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash removes newline only when a following real span exists
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashTrailingNewlineWithFollowingSpan001,
    TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    spans.push_back(CreateSpanItem(TEXT_WORLD, 6, 11));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    ASSERT_EQ(spanGroupVec.size(), static_cast<size_t>(2));
    ASSERT_FALSE(spanGroupVec[0].empty());
    ASSERT_FALSE(spanGroupVec[1].empty());
    EXPECT_TRUE(spanGroupVec[0].front()->needRemoveNewLine);
    EXPECT_FALSE(spanGroupVec[1].front()->needRemoveNewLine);
}

/**
 * @tc.name: ConstructSpanGroupForHashNullSpan001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash skips null spans gracefully
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashNullSpan001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(nullptr);
    spans.push_back(CreateSpanItem(TEXT_HELLO));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    ASSERT_EQ(spanGroupVec.size(), static_cast<size_t>(1));
    EXPECT_EQ(spanGroupVec[0].size(), static_cast<size_t>(1));
}

/**
 * @tc.name: ConstructSpanGroupForHashMaxLinesDetection001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash detects maxLines in textLineStyle
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashMaxLinesDetection001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItemWithMaxLines(TEXT_HELLO, TEST_MAX_LINES_LIMITED));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    EXPECT_TRUE(spanStringHasMaxLines);
}

/**
 * @tc.name: ConstructSpanGroupForHashNoMaxLines001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash does not set flag when no maxLines
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashNoMaxLines001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    EXPECT_FALSE(spanStringHasMaxLines);
}

/**
 * @tc.name: ConstructSpanGroupForHashMultipleNewlines001
 * @tc.desc: Test ConstructParagraphSpanGroupForHash handles multiple newline spans correctly
 * @tc.type: FUNC
 */
HWTEST_F(ConstructParagraphSpanGroupForHashTestNg, ConstructSpanGroupForHashMultipleNewlines001, TestSize.Level1)
{
    std::list<RefPtr<SpanItem>> spans;
    spans.push_back(CreateSpanItem(TEXT_HELLO_NEWLINE, 0, 6));
    spans.push_back(CreateSpanItem(TEXT_WORLD_NEWLINE, 6, 12));
    std::vector<std::list<RefPtr<SpanItem>>> spanGroupVec;
    bool spanStringHasMaxLines = false;
    ParagraphUtil::ConstructParagraphSpanGroupForHash(spans, spanGroupVec, spanStringHasMaxLines);
    EXPECT_GE(spanGroupVec.size(), static_cast<size_t>(2));
    EXPECT_TRUE(spanGroupVec[0].front()->needRemoveNewLine);
    EXPECT_FALSE(spanGroupVec[1].front()->needRemoveNewLine);
}
} // namespace OHOS::Ace::NG
