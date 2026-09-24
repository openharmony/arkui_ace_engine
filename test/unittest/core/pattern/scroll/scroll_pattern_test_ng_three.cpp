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

#include "gtest/gtest.h"
#include "scroll_test_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_theme.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
namespace OHOS::Ace::NG {
// using namespace testing;
// using namespace testing::ext;

class ScrollPatternThreeTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: CalcPredictNextSnapOffset001
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 4.0f }
     */
    scrollPattern->snapOffsets_ = { 2.0f, 4.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 2 and snapDirection to BACKWARD
     * @tc.expected: The value of the result returned by the function is 3
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(2.0f, SnapDirection::BACKWARD);
    EXPECT_EQ(result.value(), 3.0f);
}

/**
 * @tc.name: CalcPredictNextSnapOffset002
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 4.0f }
     */
    scrollPattern->snapOffsets_ = { 2.0f, 4.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 6 and snapDirection to FORWARD
     * @tc.expected: The value of the result returned by the function is 1
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(6.0f, SnapDirection::FORWARD);
    EXPECT_EQ(result.value(), 1.0f);
}

/**
 * @tc.name: CalcPredictNextSnapOffset003
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to 5
     * and set snapOffsets_ to { -2.0f, -3.0f, -4.0f }
     */
    scrollPattern->snapOffsets_ = { -2.0f, -3.0f, -4.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = 5.0f;

    /**
     * @tc.steps: step3. Set delta to 1 and snapDirection to FORWARD
     * @tc.expected: The value of the result returned by the function is 1
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(1.0f, SnapDirection::FORWARD);
    EXPECT_EQ(result.value(), 1.0f);
}

/**
 * @tc.name: CalcPredictNextSnapOffset004
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f }
     */
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 6 and snapDirection to BACKWARD
     * @tc.expected: The value of the result returned by the function is 3
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(6.0f, SnapDirection::BACKWARD);
    EXPECT_EQ(result.value(), 3.0f);
}

/**
 * @tc.name: CalcPredictNextSnapOffset005
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 4.0f, 3.0f, 2.0f }
     */
    scrollPattern->snapOffsets_ = { 4.0f, 3.0f, 2.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 4 and snapDirection to FORWARD
     * @tc.expected: The value of the result returned by the function is 5
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(4.0f, SnapDirection::FORWARD);
    EXPECT_EQ(result.value(), 5.0f);
}

/**
 * @tc.name: CalcPredictNextSnapOffset006
 * @tc.desc: Test ScrollPattern CalcPredictNextSnapOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictNextSnapOffset006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);

    /**
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 4.0f, 3.0f, 2.0f }
     */
    scrollPattern->snapOffsets_ = { 4.0f, 3.0f, 2.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 4 and snapDirection to BACKWARD
     * @tc.expected: The value of the result returned by the function is 3
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(4.0f, SnapDirection::BACKWARD);
    EXPECT_EQ(result.value(), 3.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations_001
 * @tc.desc: Test ScrollPattern CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CaleSnapOffsetsByPaginations_001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;

    /**
     * @tc.steps: step2. Set viewPort_, viewPortExtent_ and snapPaginations_
     * set scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f, 5.0f }
     */
    scrollPattern->viewPort_ = SizeF(2.0f, 4.0f);
    scrollPattern->viewPortExtent_ = SizeF(4.0f, 8.0f);
    scrollPattern->scrollableDistance_ = -2.0f;
    scrollPattern->snapPaginations_ = { Dimension(2.0) };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };

    /**
     * @tc.steps: step3. Set scrollSnapDirection to START
     * @tc.expected: The value of the element at the end of the snapOffsets_ has 5 to 2
     */
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::START);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations_002
 * @tc.desc: Test ScrollPattern CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CaleSnapOffsetsByPaginations_002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;

    /**
     * @tc.steps: step2. Set viewPort_, viewPortExtent_ and snapPaginations_
     * set scrollableDistance_ to 4
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f, 5.0f }
     */
    scrollPattern->viewPort_ = SizeF(2.0f, 4.0f);
    scrollPattern->viewPortExtent_ = SizeF(4.0f, 8.0f);
    scrollPattern->scrollableDistance_ = 4.0f;
    scrollPattern->snapPaginations_ = { Dimension(2.0) };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };

    /**
     * @tc.steps: step3. Set scrollSnapDirection to CENTER
     * @tc.expected: The value of the element at the end of the snapOffsets_ has 5 to -4
     * The value of the penultimate element of the snapOffsets_ has 4 to -3
     */
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::CENTER);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), -4.0f);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin() + 1), -3.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations_003
 * @tc.desc: Test ScrollPattern CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CaleSnapOffsetsByPaginations_003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;

    /**
     * @tc.steps: step2. Set viewPort_, viewPortExtent_ and snapPaginations_
     * set scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f, 5.0f }
     */
    scrollPattern->viewPort_ = SizeF(2.0f, 4.0f);
    scrollPattern->viewPortExtent_ = SizeF(4.0f, 8.0f);
    scrollPattern->scrollableDistance_ = -2.0f;
    scrollPattern->snapPaginations_ = { Dimension(2.0) };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };

    /**
     * @tc.steps: step3. Set scrollSnapDirection to END
     * @tc.expected: The value of the element at the end of the snapOffsets_ has 5 to 2
     */
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::END);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: CaleSnapOffsetsByPaginations_004
 * @tc.desc: Test ScrollPattern CaleSnapOffsetsByPaginations
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CaleSnapOffsetsByPaginations_004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    frameNode->layoutProperty_ = layoutProperty;

    /**
     * @tc.steps: step2. Set viewPort_, viewPortExtent_ and snapPaginations_
     * set scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f, 5.0f }
     */
    scrollPattern->viewPort_ = SizeF(2.0f, 4.0f);
    scrollPattern->viewPortExtent_ = SizeF(4.0f, 8.0f);
    scrollPattern->scrollableDistance_ = -2.0f;
    scrollPattern->snapPaginations_ = { Dimension(2.0) };
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f, 5.0f };

    /**
     * @tc.steps: step3. Set scrollSnapDirection to NONE
     * @tc.expected: The value of the element at the end of the snapOffsets_ has 5 to 2
     */
    scrollPattern->CaleSnapOffsetsByPaginations(ScrollSnapAlign::NONE);
    EXPECT_EQ(*(scrollPattern->snapOffsets_.rbegin()), 2.0f);
}

/**
 * @tc.name: FireObserverOnDidScroll
 * @tc.desc: Test set and reset zoomScale
 * @tc.type: FUNC
 */
TEST_F(ScrollPatternThreeTestNg, FireObserverOnDidScroll)
{
    /**
     * @tc.step: step1. Create Scroll, set scroller observer with onDidScrollEvent
     */
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    auto controller = AceType::MakeRefPtr<ScrollableController>();
    ScrollerObserver observer;
    bool isCallback = false;
    observer.onDidScrollEvent = [&isCallback](Dimension, ScrollSource, bool, bool) { isCallback = true; };
    controller->SetObserver(observer);
    pattern_->SetPositionController(controller);
    /**
     * @tc.steps: step2. ScrollTo ITEM_MAIN_SIZE
     * @tc.expected: Trigger onDidScrollEvent
     */
    ScrollTo(ITEM_MAIN_SIZE);
    EXPECT_TRUE(isCallback);
}

/**
 * @tc.name: GetDefaultFrictionTest001
 * @tc.desc: Test ScrollPattern GetDefaultFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetDefaultFrictionTest001, TestSize.Level1)
{
    MockContainer::SetUp();
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);

    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), API11_FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), API12_FRICTION);
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    auto context = PipelineBase::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto scrollableTheme = context->GetTheme<ScrollableTheme>();
    ASSERT_NE(scrollableTheme, nullptr);
    auto friction = scrollableTheme->GetFriction();
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), friction);
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: GetDefaultFrictionTest002
 * @tc.desc: Test ScrollPattern GetDefaultFriction
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetDefaultFrictionTest002, TestSize.Level1)
{
    MockContainer::SetUp();
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);

    int32_t backupApiVersion = MockContainer::Current()->GetApiTargetVersion();
    MockContainer::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(nullptr));
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), API12_FRICTION);

    auto originalPipeline = NG::MockPipelineContext::pipeline_;
    NG::MockPipelineContext::pipeline_ = nullptr;
    EXPECT_EQ(scrollPattern->GetDefaultFriction(), API12_FRICTION);
    NG::MockPipelineContext::pipeline_ = originalPipeline;
    MockContainer::Current()->SetApiTargetVersion(backupApiVersion);
    MockContainer::TearDown();
}

/**
 * @tc.name: GetOverScrollOffset_PositiveStart
 * @tc.desc: Test GetOverScrollOffset with Positive offset at start
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_PositiveStart, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    ScrollBy(0, -contentOffset * 0.5);
    EXPECT_EQ(pattern_->currentOffset_, -contentOffset * 0.5);

    auto result = pattern_->GetOverScrollOffset(contentOffset);
    EXPECT_DOUBLE_EQ(result.start, contentOffset * 0.5);
    EXPECT_DOUBLE_EQ(result.end, 0.0);

    result = pattern_->GetOverScrollOffset(-contentOffset);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, 0.0);
}

/**
 * @tc.name: GetOverScrollOffset_NegativeStart
 * @tc.desc: Test GetOverScrollOffset with Negative offset at start
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_NegativeStart, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    pattern_->currentOffset_ -= contentOffset * 0.5;

    // startPos <= 0 && newStartPos > 0
    auto result = pattern_->GetOverScrollOffset(contentOffset);
    EXPECT_DOUBLE_EQ(result.start, contentOffset * 0.5);
    EXPECT_DOUBLE_EQ(result.end, 0.0);

    // startPos <= 0 && newStartPos <= 0
    result = pattern_->GetOverScrollOffset(-contentOffset);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, 0.0);
}

/**
 * @tc.name: GetOverScrollOffset_PositiveEnd
 * @tc.desc: Test GetOverScrollOffset with Positive offset at end
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_PositiveEnd, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    pattern_->currentOffset_ -= 10;

    // endPos < endRefences && newEndPos < endRefences
    auto result = pattern_->GetOverScrollOffset(-10.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, -10.0);

    // endPos < endRefences && newEndPos >= endRefences
    result = pattern_->GetOverScrollOffset(20.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, 10.0);
}

/**
 * @tc.name: GetOverScrollOffset_NegativeEnd
 * @tc.desc: Test GetOverScrollOffset with Negative offset at end
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_NegativeEnd, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    pattern_->currentOffset_ += 10;

    // endPos >= endRefences && newEndPos < endRefences
    auto result = pattern_->GetOverScrollOffset(-15.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, -5.0);

    // endPos >= endRefences && newEndPos >= endRefences
    result = pattern_->GetOverScrollOffset(10.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, 0.0);
}

/**
 * @tc.name: GetOverScrollOffset_ZeroScrollableDistance
 * @tc.desc: Test GetOverScrollOffset with 0 scrollableDistance
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_ZeroScrollableDistance, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    pattern_->scrollableDistance_ = 0.0f;
    pattern_->currentOffset_ = -10.0;

    auto result = pattern_->GetOverScrollOffset(-5.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, -5.0);
}

/**
 * @tc.name: GetContentStartOffsetTest
 * @tc.desc: test ScrollPattern::GetContentStartOffsetTest
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetContentStartOffsetTest, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->GetContentStartOffset(), contentOffset);
}

/**
 * @tc.name: GetContentStartOffsetWithInvalidValueTest
 * @tc.desc: test ScrollPattern::GetContentStartOffsetTest with invalid value
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetContentStartOffsetWithInvalidValueTest, TestSize.Level1)
{
    CreateScroll();
    float contentOffset = HEIGHT / 2;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset);
    CreateContent();
    CreateScrollDone();

    EXPECT_FLOAT_EQ(pattern_->GetContentStartOffset(), 0.0f);
}

/**
 * @tc.name: ResetPositionTest
 * @tc.desc: test ScrollPattern::ResetPosition
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, ResetPositionTest, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    EXPECT_EQ(pattern_->lastOffset_, 0.0);

    ScrollBy(0, -50);
    EXPECT_EQ(pattern_->currentOffset_, -50.0);
    EXPECT_EQ(pattern_->lastOffset_, 0.0);

    ScrollBy(0, -50);
    EXPECT_EQ(pattern_->currentOffset_, -100.0);
    EXPECT_EQ(pattern_->lastOffset_, -50.0);

    pattern_->ResetPosition();
    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    EXPECT_EQ(pattern_->lastOffset_, 0.0);
}

/**
 * @tc.name: CheckScrollableWithContentOffset
 * @tc.desc: test ScrollPattern::CheckScrollable with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CheckScrollableWithContentOffset, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET + 1);
    CreateScrollDone();

    EXPECT_EQ(pattern_->scrollableDistance_, 1);
    // scrollableDistance_ + contentStartOffset_ > mainSize
    pattern_->CheckScrollable();
    EXPECT_TRUE(pattern_->GetScrollEnabled());
}

/**
 * @tc.name: IsAtBottomWithContentOffset
 * @tc.desc: test ScrollPattern::CheckScrollable with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, IsAtBottomWithContentOffset, TestSize.Level1)
{
    CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET + 1);
    CreateScrollDone();

    EXPECT_EQ(pattern_->scrollableDistance_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    EXPECT_FALSE(pattern_->IsAtBottom());

    pattern_->currentOffset_ -= 1;
    EXPECT_TRUE(pattern_->IsAtBottom());
}

/**
 * @tc.name: EdgeEffectCallbackwithContentOffset
 * @tc.desc: test ScrollPattern::CheckScrollable with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, EdgeEffectCallbackwithContentOffset, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent(HEIGHT - CONTENT_START_OFFSET - CONTENT_END_OFFSET + 1);
    CreateScrollDone();

    EXPECT_EQ(pattern_->scrollableDistance_, 1);
    EXPECT_EQ(pattern_->currentOffset_, 0.0);
    auto edgeEffect = pattern_->GetScrollEdgeEffect();
    ASSERT_NE(edgeEffect, nullptr);

    EXPECT_EQ(edgeEffect->leadingCallback_(), -1.0);
    EXPECT_EQ(edgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(edgeEffect->initLeadingCallback_(), -1.0);
    EXPECT_EQ(edgeEffect->initTrailingCallback_(), 0.0);

    pattern_->scrollableDistance_ -= 2;
    EXPECT_EQ(edgeEffect->leadingCallback_(), 0.0);
    EXPECT_EQ(edgeEffect->trailingCallback_(), 0.0);
    EXPECT_EQ(edgeEffect->initLeadingCallback_(), 0.0);
    EXPECT_EQ(edgeEffect->initTrailingCallback_(), 0.0);
}

/**
 * @tc.name: ScrollEdgeWithContentOffset
 * @tc.desc: Test ScrollEdge with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, ScrollEdgeWithContentOffset, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent();
    CreateScrollDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), CONTENT_MAIN_SIZE - HEIGHT + CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->currentOffset_, -CONTENT_MAIN_SIZE + HEIGHT - CONTENT_END_OFFSET - CONTENT_START_OFFSET);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, false);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->currentOffset_, 0);
}

/**
 * @tc.name: ScrollEdgeAnimationWithContentOffset
 * @tc.desc: Test ScrollEdge with animation and contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, ScrollEdgeAnimationWithContentOffset, TestSize.Level1)
{
    MockAnimationManager::GetInstance().SetTicks(TICK);
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    CreateContent();
    CreateScrollDone();

    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, true);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), CONTENT_MAIN_SIZE - HEIGHT + CONTENT_END_OFFSET);
    EXPECT_EQ(pattern_->currentOffset_, -CONTENT_MAIN_SIZE + HEIGHT - CONTENT_END_OFFSET - CONTENT_START_OFFSET);

    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, true);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);
    EXPECT_EQ(pattern_->currentOffset_, 0);
}

/**
 * @tc.name: SnapWithContentOffset
 * @tc.desc: Test Snap with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, SnapWithContentOffset, TestSize.Level1)
{
    Dimension intervalSize(50.0);
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, true);
    std::vector<float> offsets = {};
    for (int i = 0; i <= 13; ++i) {
        offsets.emplace_back(-i * 50);
    }

    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->snapOffsets_, offsets);
}

/**
 * @tc.name: SnapWithContentOffset
 * @tc.desc: Test Snap with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, SnapWithContentOffsetUpdate, TestSize.Level1)
{
    Dimension intervalSize(130.0);
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, true);

    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    EXPECT_EQ(pattern_->currentOffset_, 0);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_START_OFFSET);

    layoutProperty_->UpdateContentStartOffset(0);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 0);
    EXPECT_EQ(pattern_->GetTotalOffset(), 0);

    layoutProperty_->UpdateContentStartOffset(CONTENT_END_OFFSET);
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, 0);
    EXPECT_EQ(pattern_->GetTotalOffset(), -CONTENT_END_OFFSET);
}

/**
 * @tc.name: SetEnableScrollWithMouse001
 * @tc.desc: Test SetEnableScrollWithMouse
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, SetEnableScrollWithMouse001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    pattern_->SetIsAllowMouse(true);
    CreateScrollDone();
    EXPECT_TRUE(pattern_->GetIsAllowMouse());
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    EXPECT_TRUE(scrollable->panRecognizerNG_->isAllowMouse_);
}

/**
 * @tc.name: GetScrollSnap001
 * @tc.desc: Test Snap with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, GetScrollSnap001, TestSize.Level1)
{
    Dimension intervalSize(50.0);
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, true);

    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    ScrollSnapOptions snapOptions = model.GetScrollSnap(frameNode.GetRawPtr());

    EXPECT_TRUE(pattern_->IsSnapToInterval());
    EXPECT_EQ(snapOptions.snapAlign, 1);
    EXPECT_EQ(snapOptions.enableSnapToStart, 1);
    EXPECT_EQ(snapOptions.enableSnapToEnd, 1);
    EXPECT_EQ(snapOptions.paginationParams[0].ToString(), intervalSize.ToString());
}

/**
* @tc.name: GetScrollSnap002
* @tc.desc: Test Snap with contentOffset
* @tc.type: FUNC
*/
HWTEST_F(ScrollPatternThreeTestNg, GetScrollSnap002, TestSize.Level1)
{
    Dimension intervalSize(0);
    std::vector<Dimension> snapPaginations = { Dimension(100.0), Dimension(200.0) };
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, true);

    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();

    auto frameNode = pattern_->GetHost();
    ASSERT_NE(frameNode, nullptr);
    ScrollSnapOptions snapOptions = model.GetScrollSnap(frameNode.GetRawPtr());

    EXPECT_FALSE(pattern_->IsSnapToInterval());
    EXPECT_EQ(snapOptions.snapAlign, 1);
    EXPECT_EQ(snapOptions.enableSnapToStart, 1);
    EXPECT_EQ(snapOptions.enableSnapToEnd, 1);
    EXPECT_EQ(snapOptions.paginationParams[0].ToString(), snapPaginations[0].ToString());
    EXPECT_EQ(snapOptions.paginationParams[1].ToString(), snapPaginations[1].ToString());
}

/**
 * @tc.name: CalcPredictSnapOffsetWithContentOffset
 * @tc.desc: Test Snap with contentOffset
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetWithContentOffset, TestSize.Level1)
{
    Dimension intervalSize(100.0);
    std::vector<Dimension> snapPaginations = {};
    std::pair<bool, bool> enableSnapToSide = std::make_pair(true, true);

    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetContentStartOffset(CONTENT_START_OFFSET);
    ScrollableModelNG::SetContentEndOffset(CONTENT_END_OFFSET);
    model.SetScrollSnap(ScrollSnapAlign::START, intervalSize, snapPaginations, enableSnapToSide);
    CreateContent();
    CreateScrollDone();
    auto offset = pattern_->CalcPredictSnapOffset(0, 0, 0, SnapDirection::NONE);
    EXPECT_EQ(offset, 0);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision001
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition is slightly above tail within 0.1f precision
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision001, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 1, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    scrollPattern->scrollableDistance_ = 600.0f;
    scrollPattern->currentOffset_ = -600.0f;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -200.0f, -300.0f, -400.0f, -500.0f, -600.0f };

    float delta = 0.05f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), delta, 0.01f);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision002
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition exactly equals tail
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision002, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 2, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    scrollPattern->scrollableDistance_ = 600.0f;
    scrollPattern->currentOffset_ = -600.0f;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -200.0f, -300.0f, -400.0f, -500.0f, -600.0f };

    float delta = 0.0f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), 0.0f, 0.01f);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision003
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition is above tail by more than 0.1f
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision003, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 3, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    scrollPattern->scrollableDistance_ = 600.0f;
    scrollPattern->currentOffset_ = -600.0f;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -200.0f, -300.0f, -400.0f, -500.0f, -600.0f };

    float delta = 0.2f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), 0.0f, 0.01f);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision004
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition is near tail boundary with 0.09f precision
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision004, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 4, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    scrollPattern->scrollableDistance_ = 600.0f;
    scrollPattern->currentOffset_ = -600.0f;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -200.0f, -300.0f, -400.0f, -500.0f, -600.0f };

    float delta = 0.09f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), delta, 0.01f);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision005
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition is slightly above tail with large scrollableDistance
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision005, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 5, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    float scrollableDistance = 10000.0f;
    scrollPattern->scrollableDistance_ = scrollableDistance;
    scrollPattern->currentOffset_ = -scrollableDistance;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -5000.0f, -scrollableDistance };

    float delta = 0.06f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), delta, 0.01f);
}

/**
 * @tc.name: CalcPredictSnapOffsetTailPrecision006
 * @tc.desc: Test CalcPredictSnapOffset when finalPosition at head boundary
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, CalcPredictSnapOffsetTailPrecision006, TestSize.Level1)
{
    auto scrollPattern = AceType::MakeRefPtr<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    auto frameNode = FrameNode::CreateFrameNode(V2::SCROLL_ETS_TAG, 6, scrollPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<ScrollLayoutProperty>();
    layoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    frameNode->layoutProperty_ = layoutProperty;

    scrollPattern->scrollableDistance_ = 600.0f;
    scrollPattern->currentOffset_ = 0.0f;
    scrollPattern->snapOffsets_ = { 0.0f, -100.0f, -200.0f, -300.0f, -400.0f, -500.0f, -600.0f };

    float delta = 0.05f;
    auto result = scrollPattern->CalcPredictSnapOffset(delta, 0.f, 0.f, SnapDirection::NONE);
    EXPECT_TRUE(result.has_value());
    EXPECT_NEAR(result.value(), delta, 0.01f);
}

/**
 * @tc.name: ScrollDirectionNoneResetPositionDuringAnimation001
 * @tc.desc: During a running AnimateTo animation, changing scrollable to ScrollDirection.None triggers
 *           SetAxis + ResetPosition, resetting currentOffset_ to 0 (back-to-top at data level).
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, ScrollDirectionNoneResetPositionDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. scroll to a middle position
     */
    ScrollBy(0, -300.0);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, -300.0f);

    /**
     * @tc.steps: step2. start an AnimateTo animation towards position 100 (currentOffset -> -100)
     */
    AnimateTo(Dimension(100.0f), 1, nullptr, false);
    EXPECT_TRUE(pattern_->AnimateRunning());

    /**
     * @tc.steps: step3. advance the animation by one tick
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();

    /**
     * @tc.steps: step4. change scrollable direction to None during the running animation
     * @tc.expected: SetAxis(NONE) triggers ResetPosition, currentOffset_ and lastOffset_ reset to 0
     */
    ScrollModelNG::SetAxis(AceType::RawPtr(frameNode_), Axis::NONE);
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, 0.0f);
    EXPECT_FLOAT_EQ(pattern_->lastOffset_, 0.0f);
    EXPECT_EQ(pattern_->GetAxis(), Axis::NONE);
}

/**
 * @tc.name: StopAnimateAtNonTerminalPosition001
 * @tc.desc: StopAnimate called during a running animation stops at the current intermediate (non-terminal)
 *           position, neither the start (0) nor the final target.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, StopAnimateAtNonTerminalPosition001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. start an AnimateTo animation towards a far position (500 => currentOffset -> -500)
     */
    AnimateTo(Dimension(500.0f), 1, nullptr, false);
    EXPECT_TRUE(pattern_->AnimateRunning());

    /**
     * @tc.steps: step2. advance one tick so the animation reaches an intermediate offset
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->AnimateRunning());
    float midOffset = pattern_->currentOffset_;

    /**
     * @tc.steps: step3. call StopAnimate to interrupt the running animation
     * @tc.expected: animation stops, currentOffset_ stays at the intermediate value (not 0, not -500)
     */
    StopAnimate();
    FlushUITasks();
    EXPECT_FALSE(pattern_->AnimateRunning());
    EXPECT_FLOAT_EQ(pattern_->currentOffset_, midOffset);
    EXPECT_NE(pattern_->currentOffset_, 0.0f);
    EXPECT_NE(pattern_->currentOffset_, -500.0f);
}

/**
 * @tc.name: AxisSwitchDuringAnimation001
 * @tc.desc: During a running AnimateTo animation, switching axis (Vertical<->Horizontal) invalidates the
 *           old-axis finalPosition_ and causes a visible jump, since the target was computed on the old axis.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, AxisSwitchDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    MockAnimationManager::GetInstance().SetTicks(TICK);
    CreateContent();
    CreateScrollDone();

    /**
     * @tc.steps: step1. start an AnimateTo animation towards position 300 on the vertical axis
     */
    AnimateTo(Dimension(300.0f), 1, nullptr, false);
    EXPECT_TRUE(pattern_->AnimateRunning());
    EXPECT_FLOAT_EQ(pattern_->finalPosition_, 300.0f);

    /**
     * @tc.steps: step2. advance one tick to move partway
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->AnimateRunning());
    float beforeSwitch = pattern_->currentOffset_;

    /**
     * @tc.steps: step3. switch axis to Horizontal during the running animation
     * @tc.expected: finalPosition_ was computed on the vertical axis; after switching axis the animation
     *               target is no longer valid for the new axis, currentOffset_ diverges from the old target
     */
    ScrollModelNG::SetAxis(AceType::RawPtr(frameNode_), Axis::HORIZONTAL);
    FlushUITasks();

    /**
     * @tc.steps: step4. tick to finish; the final position no longer matches the original vertical target 300
     */
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->AnimateRunning());
    EXPECT_EQ(pattern_->GetAxis(), Axis::HORIZONTAL);
    EXPECT_NE(pattern_->GetTotalOffset(), 300.0f);
    // currentOffset diverged from a clean vertical-only animation
    EXPECT_NE(pattern_->currentOffset_, beforeSwitch);
}

/**
 * @tc.name: EdgeEffectSpringToNoneDuringAnimation001
 * @tc.desc: During a running over-scroll animation (SPRING), switching edgeEffect to NONE removes the
 *           spring effect and clamps the offset back to the boundary (currentOffset_ <= 0).
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, EdgeEffectSpringToNoneDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetEdgeEffect(AceType::RawPtr(frameNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);
    CreateContent();
    CreateScrollDone();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    AnimateTo(Dimension(-100.0f), 1, nullptr, false, true);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    float overBefore = pattern_->currentOffset_;

    ScrollableModelNG::SetEdgeEffect(AceType::RawPtr(frameNode_), EdgeEffect::NONE, false, EffectEdge::ALL);
    FlushUITasks();

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->edgeEffect_, EdgeEffect::NONE);
    EXPECT_LE(pattern_->currentOffset_, overBefore);
}

/**
 * @tc.name: ContentStartOffsetChangeDuringAnimation001
 * @tc.desc: During a running AnimateTo, changing contentStartOffset recomputes the offset baseline
 *           (GetTotalOffset = -currentOffset - contentStartOffset), so the running offset diverges.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, ContentStartOffsetChangeDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    AnimateTo(Dimension(500.0f), 1, nullptr, false);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    float offsetBefore = pattern_->currentOffset_;

    ScrollableModelNG::SetContentStartOffset(AceType::RawPtr(frameNode_), 50.0f);
    FlushUITasks();

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_NE(pattern_->currentOffset_, offsetBefore);
}

/**
 * @tc.name: EffectEdgeChangeDuringAnimation001
 * @tc.desc: During a running over-scroll animation (SPRING, ALL), switching effectEdge to END disables
 *           over-scroll at the START end, so the offset is clamped at the top boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, EffectEdgeChangeDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    ScrollableModelNG::SetEdgeEffect(AceType::RawPtr(frameNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);
    CreateContent();
    CreateScrollDone();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    AnimateTo(Dimension(-100.0f), 1, nullptr, false, true);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();

    ScrollableModelNG::SetEdgeEffect(AceType::RawPtr(frameNode_), EdgeEffect::SPRING, true, EffectEdge::END);
    FlushUITasks();

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_LE(pattern_->currentOffset_, 0.0f);
}

/**
 * @tc.name: NestedScrollModeChangeDuringAnimation001
 * @tc.desc: During a running AnimateTo, changing nestedScroll mode does not interrupt the animation;
 *           the running state remains and the boundary dispatch chain uses the new mode.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollPatternThreeTestNg, NestedScrollModeChangeDuringAnimation001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    NestedScrollOptions opt;
    opt.forward = NestedScrollMode::SELF_ONLY;
    opt.backward = NestedScrollMode::SELF_ONLY;
    ScrollableModelNG::SetNestedScroll(AceType::RawPtr(frameNode_), opt);
    CreateContent();
    CreateScrollDone();
    MockAnimationManager::GetInstance().SetTicks(TICK);

    AnimateTo(Dimension(500.0f), 1, nullptr, false);
    EXPECT_TRUE(pattern_->AnimateRunning());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();

    NestedScrollOptions opt2;
    opt2.forward = NestedScrollMode::PARENT_FIRST;
    opt2.backward = NestedScrollMode::PARENT_FIRST;
    ScrollableModelNG::SetNestedScroll(AceType::RawPtr(frameNode_), opt2);
    FlushUITasks();

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->AnimateRunning());
}
} // namespace OHOS::Ace::NG
