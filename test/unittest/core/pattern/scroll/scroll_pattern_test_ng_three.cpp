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
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
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
     * @tc.steps: step2. Set currentOffset_ to -1 and scrollableDistance_ to -2
     * and set snapOffsets_ to { 2.0f, 3.0f, 4.0f }
     */
    scrollPattern->snapOffsets_ = { 2.0f, 3.0f, 4.0f };
    scrollPattern->currentOffset_ = -1.0f;
    scrollPattern->scrollableDistance_ = -2.0f;

    /**
     * @tc.steps: step3. Set delta to 2 and snapDirection to FORWARD
     * @tc.expected: The value of the result returned by the function is 4
     */
    auto result = scrollPattern->CalcPredictNextSnapOffset(2.0f, SnapDirection::FORWARD);
    EXPECT_EQ(result.value(), 4.0f);
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
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_PositiveStart, TestSize.Level1) {
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0f);
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
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_NegativeStart, TestSize.Level1) {
    ScrollModelNG model = CreateScroll();
    float contentOffset = 20;
    ScrollableModelNG::SetContentStartOffset(contentOffset);
    ScrollableModelNG::SetContentEndOffset(contentOffset * 1.5);
    CreateContent();
    CreateScrollDone();

    EXPECT_EQ(pattern_->currentOffset_, 0.0f);
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
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_PositiveEnd, TestSize.Level1) {
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
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_NegativeEnd, TestSize.Level1) {
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
HWTEST_F(ScrollPatternThreeTestNg, GetOverScrollOffset_ZeroScrollableDistance, TestSize.Level1) {
    ScrollModelNG model = CreateScroll();
    CreateContent();
    CreateScrollDone();
    pattern_->scrollableDistance_ = 0.0f;
    pattern_->currentOffset_ = -10.0;
    
    auto result = pattern_->GetOverScrollOffset(-5.0);
    EXPECT_DOUBLE_EQ(result.start, 0.0);
    EXPECT_DOUBLE_EQ(result.end, -5.0);
}
} // namespace OHOS::Ace::NG