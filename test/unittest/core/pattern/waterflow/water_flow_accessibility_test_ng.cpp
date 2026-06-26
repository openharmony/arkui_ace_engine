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

#include "core/animation/velocity_motion.h"

namespace OHOS::Ace::NG {
class WaterFlowAccessibilityTestNg : public WaterFlowTestNg {};

/**
 * @tc.name: WaterFlowA11ySourceUserSwipe001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="user" for swipe gesture
 *           (SCROLL_FROM_UPDATE) in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceUserSwipe001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Perform drag action (SCROLL_FROM_UPDATE) to trigger user scroll.
     * @tc.expected: SCROLL_END event with scrollSource="user" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    DragAction(frameNode_, Offset(0, HEIGHT / 2), -ITEM_MAIN_SIZE, 0);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "user");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceApiFling001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for Fling in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceApiFling001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger Fling to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    Fling(1000.0);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceApiAnimateTo001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for smooth AnimateTo in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceApiAnimateTo001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger smooth AnimateTo to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 1000.0f, nullptr, true);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceApiScrollToIndex001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for smooth
 *           ScrollToIndex in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceApiScrollToIndex001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger smooth ScrollToIndex to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    ScrollToIndex(5, true, ScrollAlign::CENTER);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceApiScrollToEdge001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for smooth
 *           ScrollToEdge in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceApiScrollToEdge001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger smooth ScrollToEdge to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, SCROLL_FIXED_VELOCITY);
    EXPECT_TRUE(pattern_->fixedVelocityMotion_);
    EXPECT_EQ(pattern_->fixedVelocityMotion_->GetCurrentVelocity(), -SCROLL_FIXED_VELOCITY);
    int32_t offsetTime = OFFSET_TIME;
    for (int i = 0; i < TIME_CHANGED_COUNTS; i++) {
        pattern_->fixedVelocityMotion_->OnTimestampChanged(offsetTime, 0.0f, false);
        offsetTime = offsetTime + OFFSET_TIME;
        FlushUITasks(frameNode_);
    }
    EXPECT_TRUE(pattern_->IsAtBottom());
    // WaterFlow's OnDirtyLayoutWrapperSwap gates TriggerPostLayoutEvents behind !measureInNextFrame_,
    // which may be true during manual OnTimestampChanged driving. Force animation completion so that
    // OnAnimateStop sets scrollStop_=true, then flush layout to trigger OnScrollStop->SCROLL_END.
    pattern_->OnAnimateStop();
    FlushUITasks(frameNode_);
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceApiScrollPage001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="api" for smooth
 *           ScrollPage in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceApiScrollPage001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger smooth ScrollPage to scroll with animation.
     * @tc.expected: SCROLL_END event with scrollSource="api" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    ScrollPage(false, true);
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "api");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceAccessibilityForward001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="accessibility" for
 *           ActActionScrollForward in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceAccessibilityForward001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger ActActionScrollForward.
     * @tc.expected: SCROLL_END event with scrollSource="accessibility" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    accessibilityProperty_->ActActionScrollForward();
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "accessibility");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}

/**
 * @tc.name: WaterFlowA11ySourceAccessibilityBackward001
 * @tc.desc: Verify SCROLL_END extraEventInfo["scrollSource"]=="accessibility" for
 *           ActActionScrollBackward in WaterFlow.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowAccessibilityTestNg, WaterFlowA11ySourceAccessibilityBackward001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    CreateWaterFlow();
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    auto pipeline = MockPipelineContext::GetCurrent();

    /**
     * @tc.steps: step1. Trigger ActActionScrollBackward.
     * @tc.expected: SCROLL_END event with scrollSource="accessibility" is fired.
     */
    auto captured = CaptureSendAccessibilityEventInfo(pipeline);
    accessibilityProperty_->ActActionScrollBackward();
    TickToFinish();
    EXPECT_EQ(captured->type, AccessibilityEventType::SCROLL_END);
    EXPECT_EQ(captured->extraEventInfo["scrollSource"], "accessibility");
    EXPECT_TRUE(pattern_->GetAccessibilityScrollSource().empty());
}
} // namespace OHOS::Ace::NG
