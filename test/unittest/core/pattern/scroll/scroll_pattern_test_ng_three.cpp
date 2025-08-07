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
} // namespace OHOS::Ace::NG