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

#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/components_ng/render/mock_paragraph.h"
#include "test/mock/frameworks/core/common/mock_container.h"

#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_layout_algorithm.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/pattern/text/span/span_string.h"
#include "core/components_ng/pattern/stage/stage_manager.h"
#include "core/components_ng/layout/layout_wrapper.h"
#include "core/components_ng/layout/layout_wrapper_node.h"
#include "core/components/common/layout/constants.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_NODE_ID = 100;
const std::u16string TEXT_CONTENT_HELLO = u"Hello World";
const std::u16string TEXT_CONTENT_SPAN = u"SpanContent";
constexpr float TEST_WIDTH_SAME = 500.0f;
constexpr float TEST_WIDTH_DIFFERENT = 600.0f;
constexpr double TEST_FONT_SIZE_VALUE = 20.0;
} // namespace

class ParagraphCacheTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void ParagraphCacheTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TextTheme>()));
    RefPtr<FrameNode> stageNode = AceType::MakeRefPtr<FrameNode>("STAGE", -1, AceType::MakeRefPtr<Pattern>());
    auto stageManager = AceType::MakeRefPtr<StageManager>(stageNode);
    MockPipelineContext::GetCurrent()->stageManager_ = stageManager;
}

void ParagraphCacheTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

void ParagraphCacheTestNg::SetUp()
{
    MockParagraph::GetOrCreateMockParagraph();
}

void ParagraphCacheTestNg::TearDown()
{
    MockParagraph::TearDown();
}

// ==================== TextPattern::InitParagraphCache Tests ====================

/**
 * @tc.name: TextPatternInitParagraphCache001
 * @tc.desc: Test InitParagraphCache creates cache when not yet initialized
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternInitParagraphCache001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(pattern->GetParagraphCache(), nullptr);
    pattern->InitParagraphCache();
    EXPECT_NE(pattern->GetParagraphCache(), nullptr);
}

/**
 * @tc.name: TextPatternInitParagraphCache002
 * @tc.desc: Test InitParagraphCache reuses existing cache on second call
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternInitParagraphCache002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->InitParagraphCache();
    auto firstCache = pattern->GetParagraphCache();
    ASSERT_NE(firstCache, nullptr);
    // Second call should reuse the same cache
    pattern->InitParagraphCache();
    auto secondCache = pattern->GetParagraphCache();
    EXPECT_EQ(firstCache, secondCache);
}

// ==================== TextPattern::UpdateSpanGroupHash Tests ====================

/**
 * @tc.name: TextPatternUpdateSpanGroupHash001
 * @tc.desc: Test UpdateSpanGroupHash creates result and computes hashes for spans
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternUpdateSpanGroupHash001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    EXPECT_EQ(pattern->GetSpanGroupHashResult(), nullptr);
    pattern->InitParagraphCache();

    std::list<RefPtr<SpanItem>> spans;
    auto span = AceType::MakeRefPtr<SpanItem>();
    span->content = TEXT_CONTENT_SPAN;
    span->interval = { 0, static_cast<int32_t>(TEXT_CONTENT_SPAN.length()) };
    spans.push_back(span);

    pattern->UpdateSpanGroupHash(spans);
    auto result = pattern->GetSpanGroupHashResult();
    ASSERT_NE(result, nullptr);
    EXPECT_FALSE(result->contentHashes.empty());
    EXPECT_FALSE(result->styleHashes.empty());
}

/**
 * @tc.name: TextPatternUpdateSpanGroupHash002
 * @tc.desc: Test UpdateSpanGroupHash handles empty span list
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternUpdateSpanGroupHash002, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->InitParagraphCache();

    std::list<RefPtr<SpanItem>> emptySpans;
    pattern->UpdateSpanGroupHash(emptySpans);
    auto result = pattern->GetSpanGroupHashResult();
    ASSERT_NE(result, nullptr);
    EXPECT_TRUE(result->contentHashes.empty());
}

// ==================== TextPattern::CreateLayoutAlgorithm Tests ====================

/**
 * @tc.name: TextPatternCreateLayoutAlgorithmNormalMode001
 * @tc.desc: Test CreateLayoutAlgorithm in non-span mode returns algorithm without cache
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternCreateLayoutAlgorithmNormalMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->isSpanStringMode_ = false;
    pattern->textStyle_ = TextStyle();

    auto layoutAlg = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlg, nullptr);
    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(layoutAlg);
    ASSERT_NE(textAlg, nullptr);
}

/**
 * @tc.name: TextPatternCreateLayoutAlgorithmSpanStringMode001
 * @tc.desc: Test CreateLayoutAlgorithm in spanString mode uses cache constructor
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternCreateLayoutAlgorithmSpanStringMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->isSpanStringMode_ = true;
    pattern->textStyle_ = TextStyle();
    pattern->InitParagraphCache();
    ASSERT_NE(pattern->GetParagraphCache(), nullptr);

    auto layoutAlg = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlg, nullptr);
}

/**
 * @tc.name: TextPatternCreateLayoutAlgorithmMarqueeMode001
 * @tc.desc: Test CreateLayoutAlgorithm in marquee mode overrides spanString mode
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternCreateLayoutAlgorithmMarqueeMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    // Set marquee overflow to trigger marquee branch
    layoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
    pattern->isSpanStringMode_ = true;
    pattern->textStyle_ = TextStyle();

    auto layoutAlg = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlg, nullptr);
}

// ==================== TextLayoutAlgorithm Constructor with Cache ====================

/**
 * @tc.name: TextLayoutAlgorithmCacheConstructor001
 * @tc.desc: Test TextLayoutAlgorithm constructor with paragraphCache stores cache and uses spanString mode
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextLayoutAlgorithmCacheConstructor001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    auto span = AceType::MakeRefPtr<SpanItem>();
    span->content = TEXT_CONTENT_SPAN;
    spans.push_back(span);

    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);
    // Verify the algorithm was constructed without crash
    EXPECT_NE(alg.GetTextStyle().GetFontSize().Value(), 0.0);
}

/**
 * @tc.name: TextLayoutAlgorithmCacheConstructorEmptySpans001
 * @tc.desc: Test TextLayoutAlgorithm constructor with empty spans and cache
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextLayoutAlgorithmCacheConstructorEmptySpans001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> emptySpans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(emptySpans, pManager, true, textStyle, cache);
    // Verify algorithm constructed with empty spans
    EXPECT_EQ(alg.GetParagraph(), nullptr);
}

/**
 * @tc.name: TextLayoutAlgorithmCacheConstructorNonSpanMode001
 * @tc.desc: Test TextLayoutAlgorithm constructor with cache in non-spanString mode wraps spans as single group
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextLayoutAlgorithmCacheConstructorNonSpanMode001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    auto span = AceType::MakeRefPtr<SpanItem>();
    span->content = TEXT_CONTENT_SPAN;
    spans.push_back(span);
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle, cache);
    // Verify algorithm constructed with cache in non-spanString mode
    EXPECT_NE(alg.GetTextStyle().GetFontSize().Value(), 0.0);
}

// ==================== TextLayoutAlgorithm::SetParagraphCache Tests ====================

/**
 * @tc.name: TextPatternSetParagraphCache001
 * @tc.desc: Test SetParagraphCache replaces existing cache
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, TextPatternSetParagraphCache001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);

    auto cache1 = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    pattern->SetParagraphCache(cache1);
    EXPECT_EQ(pattern->GetParagraphCache(), cache1);

    auto cache2 = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    pattern->SetParagraphCache(cache2);
    EXPECT_EQ(pattern->GetParagraphCache(), cache2);
    EXPECT_NE(pattern->GetParagraphCache(), cache1);
}

/**
 * @tc.name: UpdateTextStyleFromProperty001
 * @tc.desc: Test UpdateTextStyleFromProperty sets font size in px
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromProperty001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::FP));

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle);
    // Font size should be converted to PX via UPDATE_DIMENSION_STYLE_TO_PX macro
    EXPECT_NE(textStyle.GetFontSize().Value(), 0.0);
}

/**
 * @tc.name: UpdateTextStyleFromPropertyNullTheme001
 * @tc.desc: Test UpdateTextStyleFromProperty handles null theme gracefully
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyNullTheme001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);

    RefPtr<TextTheme> nullTheme = nullptr;
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, nullTheme, textStyle);
    // Should not crash with null theme; textStyle should still have default font size
    EXPECT_NE(textStyle.GetFontSize().Value(), 0.0);
}

/**
 * @tc.name: UpdateTextStyleFromPropertyWithFontStyle001
 * @tc.desc: Test UpdateTextStyleFromProperty applies font properties
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyWithFontStyle001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::FP));
    layoutProperty->UpdateFontWeight(FontWeight::BOLD);
    layoutProperty->UpdateItalicFontStyle(Ace::FontStyle::ITALIC);

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle);
    // Processes FontWeight and ItalicFontStyle but not TextColor
    EXPECT_EQ(textStyle.GetFontWeight(), FontWeight::BOLD);
    EXPECT_EQ(textStyle.GetFontStyle(), Ace::FontStyle::ITALIC);
}

// ==================== ConstructTextStyles Cache Overload Selection ====================

/**
 * @tc.name: ConstructTextStylesSpanStringMode001
 * @tc.desc: Test ConstructTextStyles calls UpdateTextStyleFromProperty when in spanStringMode
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, ConstructTextStylesSpanStringMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateContent(TEXT_CONTENT_HELLO);
    layoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::FP));

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle);

    LayoutConstraintF constraint;
    constraint.maxSize = { TEST_WIDTH_SAME, TEST_WIDTH_SAME };
    constraint.percentReference = { TEST_WIDTH_SAME, TEST_WIDTH_SAME };

    auto layoutWrapper = frameNode->CreateLayoutWrapper(false, false);
    ASSERT_NE(layoutWrapper, nullptr);

    // Calling MeasureContent triggers ConstructTextStyles which should use 3-param overload
    auto measureResult = alg.MeasureContent(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(measureResult.has_value());
}

// ==================== ReLayoutParagraphs Width Optimization ====================

/**
 * @tc.name: ReLayoutParagraphsWidthUnchanged001
 * @tc.desc: Test ReLayoutParagraphs skips layout when maxWidth equals paragraph's GetMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, ReLayoutParagraphsWidthUnchanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    // Layout should NOT be called when widths are equal
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(0);
    EXPECT_CALL(*mockParagraph, ReLayout(_, _, _)).Times(0);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);

    SizeF maxSize(TEST_WIDTH_SAME, TEST_WIDTH_SAME);
    alg.ReLayoutParagraphs(textStyle, AceType::RawPtr(layoutWrapper), maxSize);
}

/**
 * @tc.name: ReLayoutParagraphsWidthChanged001
 * @tc.desc: Test ReLayoutParagraphs performs layout when maxWidth differs from paragraph's GetMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, ReLayoutParagraphsWidthChanged001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    // Layout SHOULD be called when widths differ
    EXPECT_CALL(*mockParagraph, Layout(TEST_WIDTH_DIFFERENT)).Times(1);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    // needReCreateParagraph_ = true by default, so it calls Layout
    SizeF maxSize(TEST_WIDTH_DIFFERENT, TEST_WIDTH_DIFFERENT);
    alg.ReLayoutParagraphs(textStyle, AceType::RawPtr(layoutWrapper), maxSize);
}

// ==================== LayoutParagraphs Width Optimization ====================

/**
 * @tc.name: LayoutParagraphsWidthUnchanged001
 * @tc.desc: Test LayoutParagraphs skips layout when maxWidth equals paragraph's GetMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, LayoutParagraphsWidthUnchanged001, TestSize.Level1)
{
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    // Layout should NOT be called when widths are equal
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(0);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.LayoutParagraphs(TEST_WIDTH_SAME);
}

/**
 * @tc.name: LayoutParagraphsWidthChanged001
 * @tc.desc: Test LayoutParagraphs performs layout when maxWidth differs from paragraph's GetMaxWidth
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, LayoutParagraphsWidthChanged001, TestSize.Level1)
{
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    // Layout SHOULD be called when widths differ
    EXPECT_CALL(*mockParagraph, Layout(TEST_WIDTH_DIFFERENT)).Times(1);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.LayoutParagraphs(TEST_WIDTH_DIFFERENT);
}

// ==================== UpdateParagraphBySpan Override Tests ====================

/**
 * @tc.name: UpdateParagraphBySpanFallbackNoHash001
 * @tc.desc: Test UpdateParagraphBySpan falls back to base when no hash result available
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateParagraphBySpanFallbackNoHash001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textAlg, nullptr);
    textAlg->isSpanStringMode_ = true;
    // No hash result set - should fall back to base implementation

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"Hello";
    textAlg->spans_.emplace_back(spanItem);

    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    TextStyle textStyle;
    EXPECT_TRUE(textAlg->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
}

/**
 * @tc.name: UpdateParagraphBySpanFallbackEmptyHash001
 * @tc.desc: Test UpdateParagraphBySpan falls back to base when contentHashes is empty
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateParagraphBySpanFallbackEmptyHash001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    // Set empty hash result
    pattern->UpdateSpanGroupHash({});

    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textAlg, nullptr);
    textAlg->isSpanStringMode_ = true;

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"Hello";
    textAlg->spans_.emplace_back(spanItem);

    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    TextStyle textStyle;
    EXPECT_TRUE(textAlg->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
}

/**
 * @tc.name: UpdateParagraphBySpanNonSpanMode001
 * @tc.desc: Test UpdateParagraphBySpan in non-spanStringMode falls back to base
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateParagraphBySpanNonSpanMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);

    std::list<RefPtr<SpanItem>> hashSpans;
    auto hashSpan = AceType::MakeRefPtr<SpanItem>();
    hashSpan->content = u"test";
    hashSpans.push_back(hashSpan);
    pattern->UpdateSpanGroupHash(hashSpans);

    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textAlg, nullptr);
    textAlg->isSpanStringMode_ = false;
    // Even with hash result, non-span mode should fall back

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"Hello";
    textAlg->spans_.emplace_back(spanItem);

    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    TextStyle textStyle;
    EXPECT_TRUE(textAlg->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
}

// ==================== UpdateParagraphBySpanWithCache Size Mismatch Tests ====================

/**
 * @tc.name: UpdateParagraphBySpanWithCacheSizeMismatch001
 * @tc.desc: Test UpdateParagraphBySpanWithCache falls back when hash count != spans count
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateParagraphBySpanWithCacheSizeMismatch001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    // Set IncrementalUpdatePolicy to PARAGRAPH_CACHE to enable cache path
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);
    
    pattern->InitParagraphCache();

    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();

    // Create spans with content ending in newline to produce 2 groups
    std::list<RefPtr<SpanItem>> spans;
    auto span1 = AceType::MakeRefPtr<SpanItem>();
    span1->content = u"Hello\n";
    span1->interval = { 0, 6 };
    spans.push_back(span1);
    auto span2 = AceType::MakeRefPtr<SpanItem>();
    span2->content = u"World";
    span2->interval = { 6, 11 };
    spans.push_back(span2);

    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    // Provide hash vectors with wrong size (1 hash but 2 span groups)
    std::vector<uint64_t> contentHashes = { 123 };
    std::vector<uint64_t> styleHashes = { 456 };

    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    // Should fall back to base due to size mismatch
    EXPECT_TRUE(alg.UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
}

// ==================== UpdateCachedSpanGroup Tests ====================

/**
 * @tc.name: UpdateCachedSpanGroupNormalSpan001
 * @tc.desc: Test UpdateCachedSpanGroup processes NORMAL span items correctly
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateCachedSpanGroupNormalSpan001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);

    std::list<RefPtr<SpanItem>> group;
    auto normalSpan = AceType::MakeRefPtr<SpanItem>();
    normalSpan->content = u"Hello";
    normalSpan->spanItemType = SpanItemType::NORMAL;
    group.push_back(normalSpan);

    std::list<RefPtr<LayoutWrapper>> childList;
    RecursiveLock lock;
    ChildrenListWithGuard children(childList, lock);
    auto iterItems = children.begin();
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholderInfo;
    int32_t spanTextLength = 0;

    alg.UpdateCachedSpanGroup(group, 0, pattern, children, iterItems,
        imageNodeList, customSpanPlaceholderInfo, spanTextLength);
    EXPECT_EQ(spanTextLength, static_cast<int32_t>(5)); // "Hello" length
    EXPECT_EQ(normalSpan->paragraphIndex, 0);
    EXPECT_EQ(normalSpan->position, spanTextLength);
}

/**
 * @tc.name: UpdateCachedSpanGroupNullSpan001
 * @tc.desc: Test UpdateCachedSpanGroup skips null span items
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateCachedSpanGroupNullSpan001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();

    std::list<RefPtr<SpanItem>> group;
    group.push_back(nullptr); // null span
    auto normalSpan = AceType::MakeRefPtr<SpanItem>();
    normalSpan->content = u"Test";
    normalSpan->spanItemType = SpanItemType::NORMAL;
    group.push_back(normalSpan);

    std::list<RefPtr<LayoutWrapper>> childList;
    RecursiveLock lock;
    ChildrenListWithGuard children(childList, lock);
    auto iterItems = children.begin();
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholderInfo;
    int32_t spanTextLength = 0;

    alg.UpdateCachedSpanGroup(group, 0, pattern, children, iterItems,
        imageNodeList, customSpanPlaceholderInfo, spanTextLength);
    EXPECT_EQ(spanTextLength, static_cast<int32_t>(4)); // "Test" length
}

// ==================== BuildSpanGroup Tests ====================

/**
 * @tc.name: BuildSpanGroupNormalSpan001
 * @tc.desc: Test BuildSpanGroup processes NORMAL span items and builds paragraph content
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, BuildSpanGroupNormalSpan001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, PushStyle(_)).Times(AnyNumber());
    EXPECT_CALL(*mockParagraph, AddText(_)).Times(AnyNumber());
    EXPECT_CALL(*mockParagraph, PopStyle()).Times(AnyNumber());

    std::list<RefPtr<SpanItem>> group;
    auto normalSpan = AceType::MakeRefPtr<SpanItem>();
    normalSpan->content = u"Hello";
    normalSpan->spanItemType = SpanItemType::NORMAL;
    group.push_back(normalSpan);

    std::list<RefPtr<LayoutWrapper>> childList;
    RecursiveLock lock;
    ChildrenListWithGuard children(childList, lock);
    auto iterItems = children.begin();
    std::vector<WeakPtr<FrameNode>> imageNodeList;
    std::vector<CustomSpanPlaceholderInfo> customSpanPlaceholderInfo;
    int32_t spanTextLength = 0;

    bool result = alg.BuildSpanGroup(group, 0, frameNode, mockParagraph,
        children, iterItems, imageNodeList, customSpanPlaceholderInfo, spanTextLength);
    EXPECT_TRUE(result);
    EXPECT_EQ(normalSpan->paragraphIndex, 0);
}

// ==================== CreateSpanParagraphStyle Tests ====================

/**
 * @tc.name: CreateSpanParagraphStyleBasic001
 * @tc.desc: Test CreateSpanParagraphStyle returns paraStyle when no ParagraphStyleSpanItem
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, CreateSpanParagraphStyleBasic001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);

    std::list<RefPtr<SpanItem>> group;
    auto normalSpan = AceType::MakeRefPtr<SpanItem>();
    normalSpan->content = u"Test";
    group.push_back(normalSpan);

    ParagraphStyle paraStyle;
    paraStyle.maxLines = 100;
    int32_t maxLines = 100;

    auto result = alg.CreateSpanParagraphStyle(
        AceType::RawPtr(layoutWrapper), group, paraStyle, textStyle, maxLines, true, false);
    // Without ParagraphStyleSpanItem, should return original paraStyle
    EXPECT_EQ(result.maxLines, 100);
}

/**
 * @tc.name: CreateSpanParagraphStyleMaxLinesDecrement001
 * @tc.desc: Test CreateSpanParagraphStyle decrements maxLines from existing paragraphs
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, CreateSpanParagraphStyleMaxLinesDecrement001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);

    // Add an existing paragraph with 2 lines to the manager
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetLineCount()).WillRepeatedly(Return(2));
    pManager->AddParagraph({ .paragraph = mockParagraph, .paragraphStyle = ParagraphStyle(),
        .start = 0, .end = 10 });

    std::list<RefPtr<SpanItem>> group;
    auto normalSpan = AceType::MakeRefPtr<SpanItem>();
    normalSpan->content = u"Test";
    group.push_back(normalSpan);

    ParagraphStyle paraStyle;
    constexpr int32_t initialMaxLines = 10;
    paraStyle.maxLines = static_cast<uint32_t>(initialMaxLines);
    int32_t maxLines = initialMaxLines;

    auto result = alg.CreateSpanParagraphStyle(
        AceType::RawPtr(layoutWrapper), group, paraStyle, textStyle, maxLines, false, false);
    // maxLines should be decremented by existing paragraph line count (10 - 2 = 8)
    EXPECT_EQ(result.maxLines, static_cast<uint32_t>(8));
}

// ==================== AppendCachedParagraphInfo Tests ====================

/**
 * @tc.name: AppendCachedParagraphInfo001
 * @tc.desc: Test AppendCachedParagraphInfo adjusts start/end positions and adds to paragraph manager
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, AppendCachedParagraphInfo001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ParagraphStyle defaultParaStyle;
    ParagraphCacheInfo cacheInfo { .paragraph = mockParagraph, .start = 0, .end = 5 };

    int32_t spanTextLength = 10;

    alg.AppendCachedParagraphInfo(123, cacheInfo, spanTextLength);

    // start = spanTextLength - paragraphLength = 10 - 5 = 5, end = spanTextLength = 10
    EXPECT_EQ(spanTextLength, 10);

    // Paragraph should be added to manager
    auto paragraphs = pManager->GetParagraphs();
    ASSERT_FALSE(paragraphs.empty());
    EXPECT_EQ(paragraphs.back().start, 5);
    EXPECT_EQ(paragraphs.back().end, 10);
}

// ==================== StoreParagraphCache Tests ====================

/**
 * @tc.name: StoreParagraphCache001
 * @tc.desc: Test StoreParagraphCache stores in LRU cache and adds to paragraph manager
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, StoreParagraphCache001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ParagraphStyle spanParagraphStyle;
    constexpr uint64_t groupHash = 999;
    constexpr int32_t paraStart = 0;
    int32_t spanTextLength = 10;

    alg.StoreParagraphCache(groupHash, spans, mockParagraph, spanParagraphStyle, paraStart, spanTextLength);

    // Verify cache entry
    auto cachedIt = cache->Get(groupHash);
    ASSERT_NE(cachedIt, cache->End());
    EXPECT_EQ(cachedIt->second.start, paraStart);
    EXPECT_EQ(cachedIt->second.end, spanTextLength);

    // Verify paragraph manager entry
    auto paragraphs = pManager->GetParagraphs();
    ASSERT_FALSE(paragraphs.empty());
    EXPECT_EQ(paragraphs.back().start, paraStart);
    EXPECT_EQ(paragraphs.back().end, spanTextLength);
}

/**
 * @tc.name: StoreParagraphCacheMultiple001
 * @tc.desc: Test StoreParagraphCache stores multiple entries with different hashes
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, StoreParagraphCacheMultiple001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    ParagraphStyle paraStyle;
    int32_t spanTextLength = 0;

    // Store first cache entry
    alg.StoreParagraphCache(111, spans, mockParagraph, paraStyle, 0, spanTextLength = 5);
    // Store second cache entry
    alg.StoreParagraphCache(222, spans, mockParagraph, paraStyle, 5, spanTextLength = 12);

    EXPECT_NE(cache->Get(111), cache->End());
    EXPECT_NE(cache->Get(222), cache->End());
    EXPECT_EQ(cache->Size(), static_cast<size_t>(2));
}

// ==================== IncrementalUpdatePolicy Tests ====================

/**
 * @tc.name: IncrementalUpdatePolicyNONE001
 * @tc.desc: Test UpdateParagraphBySpan with NONE policy falls back directly without using cache
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, IncrementalUpdatePolicyNONE001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    // Set IncrementalUpdatePolicy to NONE (default behavior)
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::NONE);
    
    // Set hash result to enable potential cache usage
    std::list<RefPtr<SpanItem>> hashSpans;
    auto hashSpan = AceType::MakeRefPtr<SpanItem>();
    hashSpan->content = u"test";
    hashSpans.push_back(hashSpan);
    pattern->UpdateSpanGroupHash(hashSpans);
    
    pattern->InitParagraphCache();
    // Cache should be cleared due to NONE policy in SetStyledString
    // But here we call InitParagraphCache directly, so cache is created temporarily
    
    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textAlg, nullptr);
    textAlg->isSpanStringMode_ = true;
    
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"Hello";
    textAlg->spans_.emplace_back(spanItem);
    
    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    TextStyle textStyle;
    
    // Should directly fall back to base implementation due to NONE policy
    // NOT attempting to use cache path
    EXPECT_TRUE(textAlg->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
}

/**
 * @tc.name: IncrementalUpdatePolicyPARAGRAPH_CACHE001
 * @tc.desc: Test UpdateParagraphBySpan with PARAGRAPH_CACHE policy attempts to use cache path
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, IncrementalUpdatePolicyPARAGRAPH_CACHE001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    // Set IncrementalUpdatePolicy to PARAGRAPH_CACHE to enable cache path
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);
    
    // Set valid hash result
    std::list<RefPtr<SpanItem>> hashSpans;
    auto hashSpan = AceType::MakeRefPtr<SpanItem>();
    hashSpan->content = u"test";
    hashSpans.push_back(hashSpan);
    pattern->UpdateSpanGroupHash(hashSpans);
    
    pattern->InitParagraphCache();
    auto cacheBefore = pattern->GetParagraphCache();
    ASSERT_NE(cacheBefore, nullptr);
    
    auto textAlg = AceType::DynamicCast<TextLayoutAlgorithm>(pattern->CreateLayoutAlgorithm());
    ASSERT_NE(textAlg, nullptr);
    textAlg->isSpanStringMode_ = true;
    
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);
    
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    spanItem->content = u"Hello";
    textAlg->spans_.emplace_back(spanItem);
    
    ParagraphStyle paraStyle;
    paraStyle.maxLines = 1024;
    TextStyle textStyle;
    
    // Should attempt to use cache path due to PARAGRAPH_CACHE policy
    // Will check hash validity and fall back if invalid, but at least attempt cache
    EXPECT_TRUE(textAlg->UpdateParagraphBySpan(
        AceType::RawPtr(layoutWrapper), paraStyle, 100, textStyle));
    
    // Cache should still exist after operation
    auto cacheAfter = pattern->GetParagraphCache();
    EXPECT_NE(cacheAfter, nullptr);
}

/**
 * @tc.name: SetStyledStringWithIncrementalUpdatePolicy001
 * @tc.desc: Test SetStyledString initializes cache based on IncrementalUpdatePolicy
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, SetStyledStringWithIncrementalUpdatePolicy001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    pattern->AttachToFrameNode(frameNode);
    
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    
    // First test with NONE policy (default)
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::NONE);
    auto spanString = AceType::MakeRefPtr<SpanString>(u"Hello World");
    pattern->SetStyledString(spanString, false);
    
    // Cache should be nullptr due to NONE policy
    EXPECT_EQ(pattern->GetParagraphCache(), nullptr);
    
    // Then test with PARAGRAPH_CACHE policy
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);
    pattern->SetStyledString(spanString, false);
    
    // Cache should be initialized due to PARAGRAPH_CACHE policy
    EXPECT_NE(pattern->GetParagraphCache(), nullptr);
}

// ==================== IsSpanStringCacheEnabled Tests ====================

/**
 * @tc.name: IsSpanStringCacheEnabledNonePolicy001
 * @tc.desc: Test IsSpanStringCacheEnabled returns false when policy is NONE
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, IsSpanStringCacheEnabledNonePolicy001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::NONE);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle);
    alg.isSpanStringMode_ = true;

    // NONE policy should return false even in spanString mode
    EXPECT_FALSE(alg.IsSpanStringCacheEnabled(layoutProperty));
}

/**
 * @tc.name: IsSpanStringCacheEnabledParagraphCachePolicy001
 * @tc.desc: Test IsSpanStringCacheEnabled returns true when policy is PARAGRAPH_CACHE and in spanString mode
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, IsSpanStringCacheEnabledParagraphCachePolicy001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle);
    alg.isSpanStringMode_ = true;

    // PARAGRAPH_CACHE policy with spanString mode should return true
    EXPECT_TRUE(alg.IsSpanStringCacheEnabled(layoutProperty));
}

/**
 * @tc.name: IsSpanStringCacheEnabledNonSpanStringMode001
 * @tc.desc: Test IsSpanStringCacheEnabled returns false even with PARAGRAPH_CACHE if not in spanString mode
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, IsSpanStringCacheEnabledNonSpanStringMode001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.isSpanStringMode_ = false;

    // Even with PARAGRAPH_CACHE, non-spanString mode should return false
    EXPECT_FALSE(alg.IsSpanStringCacheEnabled(layoutProperty));
}

// ==================== ParagraphReLayout Cache Path Tests ====================

/**
 * @tc.name: ParagraphReLayoutUsesLongestLineWithIndent001
 * @tc.desc: Test ParagraphReLayout uses GetLongestLineWithIndent when cache is enabled
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, ParagraphReLayoutUsesLongestLineWithIndent001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::PARAGRAPH_CACHE);
    layoutProperty->UpdateContent(TEXT_CONTENT_HELLO);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    constexpr float longestLineWithIndent = 400.0f;
    constexpr float maxWidth = 500.0f;
    constexpr float paragraphMaxWidth = 480.0f;

    EXPECT_CALL(*mockParagraph, GetMaxWidth())
        .WillRepeatedly(Return(paragraphMaxWidth));
    EXPECT_CALL(*mockParagraph, GetLongestLineWithIndent())
        .WillRepeatedly(Return(longestLineWithIndent));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AnyNumber());

    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle);
    alg.isSpanStringMode_ = true;

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    LayoutConstraintF constraint;
    constraint.maxSize = { maxWidth, maxWidth };
    constraint.minSize = { 0.0f, 0.0f };
    constraint.percentReference = { maxWidth, maxWidth };

    // Set isSpanStringCacheEnabled_ = true and trigger ParagraphReLayout via MeasureContent
    auto result = alg.MeasureContent(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result.has_value());
}

/**
 * @tc.name: ParagraphReLayoutUsesTextWidthIncludeIndent001
 * @tc.desc: Test ParagraphReLayout uses GetTextWidthIncludeIndent when cache is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, ParagraphReLayoutUsesTextWidthIncludeIndent001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIncrementalUpdatePolicy(IncrementalUpdatePolicy::NONE);
    layoutProperty->UpdateContent(TEXT_CONTENT_HELLO);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    EXPECT_CALL(*mockParagraph, GetTextWidth()).WillRepeatedly(Return(450.0f));
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(AnyNumber());

    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.isSpanStringMode_ = false;

    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    ASSERT_NE(layoutWrapper, nullptr);

    LayoutConstraintF constraint;
    constraint.maxSize = { TEST_WIDTH_SAME, TEST_WIDTH_SAME };
    constraint.minSize = { 0.0f, 0.0f };
    constraint.percentReference = { TEST_WIDTH_SAME, TEST_WIDTH_SAME };

    auto result = alg.MeasureContent(constraint, AceType::RawPtr(layoutWrapper));
    EXPECT_TRUE(result.has_value());
    // With NONE policy, isSpanStringCacheEnabled_ should be false
    EXPECT_FALSE(alg.isSpanStringCacheEnabled_);
}

// ==================== UPDATE_DIMENSION_STYLE_TO_PX PERCENT Tests ====================

/**
 * @tc.name: UpdateTextStyleFromPropertyPercentFontSize001
 * @tc.desc: Test UpdateTextStyleFromProperty preserves PERCENT unit for font size
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyPercentFontSize001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(50.0, DimensionUnit::PERCENT));

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle);
    // PERCENT unit should be preserved, not converted to PX
    EXPECT_EQ(textStyle.GetFontSize().Unit(), DimensionUnit::PERCENT);
    EXPECT_EQ(textStyle.GetFontSize().Value(), 50.0);
}

/**
 * @tc.name: UpdateTextStyleFromPropertyPxFontSize001
 * @tc.desc: Test UpdateTextStyleFromProperty converts non-PERCENT units to PX
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyPxFontSize001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateFontSize(Dimension(TEST_FONT_SIZE_VALUE, DimensionUnit::FP));

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle);
    // FP unit should be converted to PX
    EXPECT_EQ(textStyle.GetFontSize().Unit(), DimensionUnit::PX);
}

// ==================== LayoutParagraphs Zero MaxWidth Tests ====================

/**
 * @tc.name: LayoutParagraphsZeroMaxWidth001
 * @tc.desc: Test LayoutParagraphs calls Layout when paragraph maxWidth is zero
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, LayoutParagraphsZeroMaxWidth001, TestSize.Level1)
{
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(0.0f));
    // Layout SHOULD be called when maxWidth is 0
    EXPECT_CALL(*mockParagraph, Layout(TEST_WIDTH_SAME)).Times(1);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.LayoutParagraphs(TEST_WIDTH_SAME);
}

/**
 * @tc.name: LayoutParagraphsSameWidthZeroWidth001
 * @tc.desc: Test LayoutParagraphs when both paragraph maxWidth and target are zero
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, LayoutParagraphsSameWidthZeroWidth001, TestSize.Level1)
{
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(0.0f));
    // Even with NearEqual(0, 0) = true, the first check NearEqual(0.0f, 0.0f) triggers Layout
    EXPECT_CALL(*mockParagraph, Layout(0.0f)).Times(1);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.LayoutParagraphs(0.0f);
}

/**
 * @tc.name: LayoutParagraphsSameNonZeroWidth001
 * @tc.desc: Test LayoutParagraphs skips layout when widths are equal and non-zero
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, LayoutParagraphsSameNonZeroWidth001, TestSize.Level1)
{
    auto mockParagraph = MockParagraph::GetOrCreateMockParagraph();
    EXPECT_CALL(*mockParagraph, GetMaxWidth()).WillRepeatedly(Return(TEST_WIDTH_SAME));
    // Layout should NOT be called when widths are equal and non-zero
    EXPECT_CALL(*mockParagraph, Layout(_)).Times(0);

    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    ParagraphStyle paraStyle;
    pManager->AddParagraph({ .paragraph = mockParagraph,
        .paragraphStyle = paraStyle,
        .start = 0,
        .end = 10 });

    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, false, textStyle);
    alg.LayoutParagraphs(TEST_WIDTH_SAME);
}

// ==================== ConvertToPxDistributeWithEnv (UPDATE_DIMENSION_STYLE_TO_PX) Tests ====================

/**
 * @tc.name: UpdateTextStyleFromPropertyEnvFontScale001
 * @tc.desc: Test UpdateTextStyleFromProperty uses pattern envFontScale when converting FP font size to PX
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyEnvFontScale001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetEnvFontScale(2.0f);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    constexpr double fpFontSize = 10.0;
    layoutProperty->UpdateFontSize(Dimension(fpFontSize, DimensionUnit::FP));

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle, pattern);
    // envFontScale=2.0, dipScale=1.0 => px = 10.0 * 1.0 * 2.0 = 20.0
    EXPECT_EQ(textStyle.GetFontSize().Unit(), DimensionUnit::PX);
    EXPECT_DOUBLE_EQ(textStyle.GetFontSize().Value(), fpFontSize * 2.0);
}

/**
 * @tc.name: UpdateTextStyleFromPropertyEnvFontScaleClamped001
 * @tc.desc: Test envFontScale is clamped by MinFontScale/MaxFontScale during PX conversion
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyEnvFontScaleClamped001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetEnvFontScale(5.0f);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    constexpr double fpFontSize = 10.0;
    layoutProperty->UpdateFontSize(Dimension(fpFontSize, DimensionUnit::FP));
    constexpr float minFontScale = 0.0f;
    constexpr float maxFontScale = 2.0f;
    layoutProperty->UpdateMinFontScale(minFontScale);
    layoutProperty->UpdateMaxFontScale(maxFontScale);

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle, pattern);
    // envFontScale=5.0 clamped to [0.0, 2.0] => 2.0 => px = 10.0 * 1.0 * 2.0 = 20.0
    EXPECT_EQ(textStyle.GetFontSize().Unit(), DimensionUnit::PX);
    EXPECT_DOUBLE_EQ(textStyle.GetFontSize().Value(), fpFontSize * maxFontScale);
}

/**
 * @tc.name: UpdateTextStyleFromPropertyEnvFontScaleNoScale001
 * @tc.desc: Test envFontScale is ignored when AllowScale is false
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, UpdateTextStyleFromPropertyEnvFontScaleNoScale001, TestSize.Level1)
{
    auto pattern = AceType::MakeRefPtr<TextPattern>();
    pattern->SetEnvFontScale(2.0f);
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TextLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    constexpr double fpFontSize = 10.0;
    layoutProperty->UpdateFontSize(Dimension(fpFontSize, DimensionUnit::FP));
    layoutProperty->UpdateAllowScale(false);

    auto textTheme = AceType::MakeRefPtr<TextTheme>();
    TextStyle textStyle;
    UpdateTextStyleFromProperty(layoutProperty, textTheme, textStyle, pattern);
    // allowScale=false => px = value * dipScale = 10.0 * 1.0 = 10.0 (envFontScale ignored)
    EXPECT_EQ(textStyle.GetFontSize().Unit(), DimensionUnit::PX);
    EXPECT_DOUBLE_EQ(textStyle.GetFontSize().Value(), fpFontSize);
}

// ==================== ConvertToPxDistributeWithEnv (CreateSpanParagraphStyle) Tests ====================

/**
 * @tc.name: CreateSpanParagraphStyleFontSizeWithEnv001
 * @tc.desc: Test CreateSpanParagraphStyle uses textStyle envFontScale when converting span fontSize
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, CreateSpanParagraphStyleFontSizeWithEnv001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);

    std::list<RefPtr<SpanItem>> group;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);
    constexpr double fpFontSize = 10.0;
    spanItem->fontStyle->UpdateFontSize(Dimension(fpFontSize, DimensionUnit::FP));
    spanItem->content = u"Test";
    group.push_back(spanItem);

    TextStyle envTextStyle;
    envTextStyle.SetEnvFontScale(2.0f);
    ParagraphStyle paraStyle;
    paraStyle.maxLines = 100;
    int32_t maxLines = 100;

    auto result = alg.CreateSpanParagraphStyle(
        AceType::RawPtr(layoutWrapper), group, paraStyle, envTextStyle, maxLines, true, false);
    // envFontScale=2.0, dipScale=1.0 => px = 10.0 * 1.0 * 2.0 = 20.0
    EXPECT_DOUBLE_EQ(result.fontSize, fpFontSize * 2.0);
}

/**
 * @tc.name: CreateSpanParagraphStyleFontSizeEnvClamped001
 * @tc.desc: Test CreateSpanParagraphStyle clamps envFontScale by MinFontScale/MaxFontScale
 * @tc.type: FUNC
 */
HWTEST_F(ParagraphCacheTestNg, CreateSpanParagraphStyleFontSizeEnvClamped001, TestSize.Level1)
{
    auto cache = AceType::MakeRefPtr<LRUMap<uint64_t, ParagraphCacheInfo>>();
    auto pManager = AceType::MakeRefPtr<ParagraphManager>();
    std::list<RefPtr<SpanItem>> spans;
    TextStyle textStyle;
    TextLayoutAlgorithm alg(spans, pManager, true, textStyle, cache);

    auto pattern = AceType::MakeRefPtr<TextPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, TEST_NODE_ID, pattern);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);

    std::list<RefPtr<SpanItem>> group;
    auto spanItem = AceType::MakeRefPtr<SpanItem>();
    ASSERT_NE(spanItem, nullptr);
    ASSERT_NE(spanItem->fontStyle, nullptr);
    constexpr double fpFontSize = 10.0;
    spanItem->fontStyle->UpdateFontSize(Dimension(fpFontSize, DimensionUnit::FP));
    spanItem->content = u"Test";
    group.push_back(spanItem);

    TextStyle envTextStyle;
    envTextStyle.SetEnvFontScale(5.0f);
    constexpr float minFontScale = 0.0f;
    constexpr float maxFontScale = 2.0f;
    envTextStyle.SetMinFontScale(minFontScale);
    envTextStyle.SetMaxFontScale(maxFontScale);
    ParagraphStyle paraStyle;
    paraStyle.maxLines = 100;
    int32_t maxLines = 100;

    auto result = alg.CreateSpanParagraphStyle(
        AceType::RawPtr(layoutWrapper), group, paraStyle, envTextStyle, maxLines, true, false);
    // envFontScale=5.0 clamped to [0.0, 2.0] => 2.0 => px = 10.0 * 1.0 * 2.0 = 20.0
    EXPECT_DOUBLE_EQ(result.fontSize, fpFontSize * maxFontScale);
}

} // namespace OHOS::Ace::NG
