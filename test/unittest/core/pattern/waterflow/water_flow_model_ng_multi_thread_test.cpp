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

#include "water_flow_test_ng.h"

namespace OHOS::Ace::NG {

class WaterFlowMultiThreadTest : public WaterFlowTestNg {};

/**
 * @tc.name: SetScrollToIndexMultiThread001
 * @tc.desc: Test SetScrollToIndexMultiThread with non-waterflow node (null pattern)
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create a non-waterflow FrameNode marked as free.
     * @tc.expected: Task is not posted because GetPattern<WaterFlowPattern> returns nullptr.
     */
    auto nonWaterFlowNode = FrameNode::CreateFrameNode("NonWaterFlow", 999, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(nonWaterFlowNode, nullptr);
    nonWaterFlowNode->isFree_ = true;
    WaterFlowModelNG::SetScrollToIndexMultiThread(AceType::RawPtr(nonWaterFlowNode), 0, 0, 0, std::nullopt);
    EXPECT_TRUE(nonWaterFlowNode->afterAttachMainTreeTasks_.empty());
}

/**
 * @tc.name: SetScrollToIndexMultiThread002
 * @tc.desc: Test SetScrollToIndexMultiThread posts task on free node and executes correctly
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread002, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. Mark node as free and call SetScrollToIndexMultiThread.
     * @tc.expected: Task is added to afterAttachMainTreeTasks_.
     */
    frameNode_->isFree_ = true;
    WaterFlowModelNG::SetScrollToIndexMultiThread(
        AceType::RawPtr(frameNode_), 5, 0, static_cast<int32_t>(ScrollAlign::START), std::nullopt);
    EXPECT_FALSE(frameNode_->afterAttachMainTreeTasks_.empty());

    /**
     * @tc.steps: step2. Execute the pending tasks.
     * @tc.expected: ScrollToIndex is called, jumpIndex_ set to 5.
     */
    frameNode_->ExecuteAfterAttachMainTreeTasks();
    EXPECT_EQ(pattern_->layoutInfo_->jumpIndex_, 5);
}

/**
 * @tc.name: SetScrollToIndexMultiThread003
 * @tc.desc: Test SetScrollToIndexMultiThread with extraOffset parameter
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread003, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. Call with extraOffset = 10.0f and alignment = CENTER.
     * @tc.expected: After task execution, extraOffset_ and align are set correctly.
     */
    frameNode_->isFree_ = true;
    WaterFlowModelNG::SetScrollToIndexMultiThread(
        AceType::RawPtr(frameNode_), 3, 0, static_cast<int32_t>(ScrollAlign::CENTER), 10.0f);
    frameNode_->ExecuteAfterAttachMainTreeTasks();
    EXPECT_EQ(pattern_->layoutInfo_->jumpIndex_, 3);
    EXPECT_TRUE(pattern_->layoutInfo_->extraOffset_.has_value());
    EXPECT_FLOAT_EQ(pattern_->layoutInfo_->extraOffset_.value(), -10.0f);
}

/**
 * @tc.name: SetScrollToIndexMultiThread004
 * @tc.desc: Test SetScrollToIndexMultiThread with smooth animation to an item not yet laid out
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread004, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems(100);  // Create more items so index 50 is not laid out
    CreateDone();

    /**
     * @tc.steps: step1. Call with animation = 1 (smooth) and an index not yet laid out.
     * @tc.expected: After task execution, targetIndex_ is set because item is not visible.
     *              ScrollToTargetIndex returns false when GetCrossIndex returns -1 (item not laid out),
     *              so targetIndex_ is set for later processing.
     */
    frameNode_->isFree_ = true;
    WaterFlowModelNG::SetScrollToIndexMultiThread(
        AceType::RawPtr(frameNode_), 50, 1, static_cast<int32_t>(ScrollAlign::END), std::nullopt);
    frameNode_->ExecuteAfterAttachMainTreeTasks();
    EXPECT_EQ(pattern_->targetIndex_, 50);
}

/**
 * @tc.name: SetScrollToIndexMultiThread005
 * @tc.desc: Test SetScrollToIndexMultiThread task does not execute when pattern is destroyed
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread005, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. Post task, then reset pattern weak reference by replacing pattern.
     * @tc.expected: Task executes without crash when weak.Upgrade() returns nullptr.
     */
    frameNode_->isFree_ = true;
    // Save layoutInfo_ pointer and initial jumpIndex_ before releasing pattern reference
    auto savedLayoutInfo = pattern_->layoutInfo_;
    auto savedJumpIndex = savedLayoutInfo->jumpIndex_;
    WaterFlowModelNG::SetScrollToIndexMultiThread(
        AceType::RawPtr(frameNode_), 5, 0, static_cast<int32_t>(ScrollAlign::START), std::nullopt);

    // Release BOTH the test class member and frameNode's pattern to fully invalidate weak reference
    pattern_ = nullptr;
    frameNode_->pattern_ = AceType::MakeRefPtr<Pattern>();
    frameNode_->ExecuteAfterAttachMainTreeTasks();
    // jumpIndex_ should remain unchanged since pattern weak reference is invalid
    EXPECT_EQ(savedLayoutInfo->jumpIndex_, savedJumpIndex);
}

/**
 * @tc.name: SetScrollToIndexMultiThread006
 * @tc.desc: Test task not posted when node is not free
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowMultiThreadTest, SetScrollToIndexMultiThread006, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

    /**
     * @tc.steps: step1. Call without marking node as free.
     * @tc.expected: Task is not posted (node is not free).
     */
    EXPECT_FALSE(frameNode_->IsFree());
    WaterFlowModelNG::SetScrollToIndexMultiThread(
        AceType::RawPtr(frameNode_), 5, 0, static_cast<int32_t>(ScrollAlign::START), std::nullopt);
    EXPECT_TRUE(frameNode_->afterAttachMainTreeTasks_.empty());
}
} // namespace OHOS::Ace::NG
