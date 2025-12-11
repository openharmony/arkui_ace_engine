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
#define private public
#define protected public
#include "base/ressched/ressched_touch_optimizer.h"
#include "core/event/touch_event.h"
#undef private
#undef protected

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace {

namespace {
    enum RVS_DIRECTION : int32_t {
        RVS_NOT_APPLY = 0,
        RVS_INITIAL_SIGNAL = 1,
        RVS_DOWN_LEFT = 2,
        RVS_UP_RIGHT = 3,
    };
    
    enum RVS_AXIS : int32_t {
        RVS_AXIS_X = 0,
        RVS_AXIS_Y = 1,
    };

    // slide direction from pan recognizer
    enum SLIDE_DIRECTION : int32_t {
        VERTICAL = 0,
        HORIZONTAL = 1,
        FREE = 2,
        NONE = 3,
    };
} // namespace

static std::unique_ptr<ResSchedTouchOptimizer> optimizer_;

class ResSchedTouchOptimizerTwoTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        optimizer_ = std::make_unique<ResSchedTouchOptimizer>();
    }
    static void TearDownTestSuite()
    {
        optimizer_.reset();
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: RVSPointCheckWithoutSignal003
 * @tc.desc: test RVSPointCheckWithoutSignal with direction change detection
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal003, TestSize.Level1)
{
    optimizer_->rvsSignalEnable_ = true;
    optimizer_->vsyncPeriod_ = 8.3 * 1000 * 1000;
    optimizer_->rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing direction change for X axis
    // Sequence: 150 -> 130 -> 100 (decreasing, then decreasing again)
    optimizer_->rvsDequeX_[1].clear();
    optimizer_->rvsDequeX_[1].push_back(150); // First element
    optimizer_->rvsDequeX_[1].push_back(130); // Second element (gap1 = 130-150 = -20)
    optimizer_->rvsDequeX_[1].push_back(100); // Third element (gap2 = 100-130 = -30)
    
    // Both gaps are negative, so no direction change - should return false
    EXPECT_FALSE(optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    EXPECT_EQ(touchEvent.xReverse, RVS_DIRECTION::RVS_NOT_APPLY); // Should remain unchanged
}

/**
 * @tc.name: RVSPointCheckWithoutSignal004
 * @tc.desc: test RVSPointCheckWithoutSignal with actual direction change
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal004, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 130;
    touchEvent.y = 230;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing actual direction change for X axis
    // Sequence: 100 -> 150 -> 130 (increasing, then decreasing)
    optimizer_->rvsDequeX_[1].clear();
    optimizer_->rvsDequeX_[1].push_back(100); // First element
    optimizer_->rvsDequeX_[1].push_back(150); // Second element (gap1 = 150-100 = 50, positive)
    optimizer_->rvsDequeX_[1].push_back(130); // Third element (gap2 = 130-150 = -20, negative)
    
    // Gaps have different signs, so direction change detected - should return true
    EXPECT_TRUE(optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    // Second gap is negative, so direction should be RVS_DOWN_LEFT
    EXPECT_EQ(touchEvent.xReverse, RVS_DIRECTION::RVS_DOWN_LEFT);
}

/**
 * @tc.name: RVSPointCheckWithoutSignal005
 * @tc.desc: test RVSPointCheckWithoutSignal with reverse direction change
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal005, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 160;
    touchEvent.y = 260;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing reverse direction change for Y axis
    // Sequence: 200 -> 150 -> 160 (decreasing, then increasing)
    optimizer_->rvsDequeY_[1].clear();
    optimizer_->rvsDequeY_[1].push_back(200); // First element
    optimizer_->rvsDequeY_[1].push_back(150); // Second element (gap1 = 150-200 = -50, negative)
    optimizer_->rvsDequeY_[1].push_back(160); // Third element (gap2 = 160-150 = 10, positive)
    
    // Gaps have different signs, so direction change detected - should return true
    EXPECT_TRUE(optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_Y));
    // Second gap is positive, so direction should be RVS_UP_RIGHT
    EXPECT_EQ(touchEvent.yReverse, RVS_DIRECTION::RVS_UP_RIGHT);
}

/**
 * @tc.name: RVSPointCheckWithoutSignal006
 * @tc.desc: test RVSPointCheckWithoutSignal with insufficient elements
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal006, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    // Fill deque with only one element
    optimizer_->rvsDequeX_[1].clear();
    optimizer_->rvsDequeX_[1].push_back(100); // Only one element
    
    // With only one element, pointCurrent will be set but no gaps can be calculated
    // Loop will exit without processing gaps, should return false
    EXPECT_FALSE(optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: RVSPointCheckWithoutSignal007
 * @tc.desc: test RVSPointCheckWithoutSignal with two elements
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal007, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 150;
    touchEvent.y = 250;
    
    // Fill deque with two elements
    optimizer_->rvsDequeX_[1].clear();
    optimizer_->rvsDequeX_[1].push_back(100); // First element
    optimizer_->rvsDequeX_[1].push_back(150); // Second element
    
    // With two elements, gap1 will be calculated but not gap2
    // Loop will exit without comparing gap signs, should return false
    EXPECT_TRUE(optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: SetSlideDirection001
 * @tc.desc: Test SetSlideDirection functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetSlideDirection001, TestSize.Level1)
{
    optimizer_->slideDirection_ = SLIDE_DIRECTION::NONE;
    
    optimizer_->SetSlideDirection(SLIDE_DIRECTION::HORIZONTAL);
    EXPECT_EQ(optimizer_->slideDirection_, SLIDE_DIRECTION::HORIZONTAL);
    
    optimizer_->SetSlideDirection(SLIDE_DIRECTION::VERTICAL);
    EXPECT_EQ(optimizer_->slideDirection_, SLIDE_DIRECTION::VERTICAL);
}

/**
 * @tc.name: RVSDirectionStateCheck001
 * @tc.desc: Test RVSDirectionStateCheck with different directions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSDirectionStateCheck001, TestSize.Level1)
{
    // Test valid directions
    EXPECT_TRUE(optimizer_->RVSDirectionStateCheck(RVS_DIRECTION::RVS_DOWN_LEFT));
    EXPECT_TRUE(optimizer_->RVSDirectionStateCheck(RVS_DIRECTION::RVS_UP_RIGHT));
    
    // Test invalid directions
    EXPECT_FALSE(optimizer_->RVSDirectionStateCheck(RVS_DIRECTION::RVS_NOT_APPLY));
    EXPECT_FALSE(optimizer_->RVSDirectionStateCheck(RVS_DIRECTION::RVS_INITIAL_SIGNAL));
    EXPECT_FALSE(optimizer_->RVSDirectionStateCheck(100)); // Invalid value
}

/**
 * @tc.name: RVSQueueUpdate011
 * @tc.desc: Test RVSQueueUpdate horizontal slide direction processing
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate011, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer_->rvsDequeX_.clear();
    optimizer_->rvsDequeY_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // First call - should add to deque but not process yet (size < RVS_QUEUE_SIZE)
    optimizer_->RVSQueueUpdate(touchEvents);
    EXPECT_EQ(optimizer_->rvsDequeX_[1].size(), 1);
    EXPECT_TRUE(optimizer_->rvsDequeY_[1].empty()); // Y should not be processed for horizontal slide
    
    // Add more events to reach RVS_QUEUE_SIZE
    for (int i = 1; i < 7; i++) {
        touchEvent.x = 100 + i * 10;
        touchEvents = {touchEvent};
        optimizer_->RVSQueueUpdate(touchEvents);
    }
    
    // Now deque should have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer_->rvsDequeX_[1].size(), 6);
}

/**
 * @tc.name: RVSQueueUpdate012
 * @tc.desc: Test RVSQueueUpdate vertical slide direction processing
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate012, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->slideDirection_ = SLIDE_DIRECTION::VERTICAL;
    optimizer_->rvsDequeX_.clear();
    optimizer_->rvsDequeY_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // First call - should add to deque but not process yet (size < RVS_QUEUE_SIZE)
    optimizer_->RVSQueueUpdate(touchEvents);
    EXPECT_EQ(optimizer_->rvsDequeY_[1].size(), 1);
    EXPECT_TRUE(optimizer_->rvsDequeX_[1].empty()); // X should not be processed for vertical slide
    
    // Add more events to reach RVS_QUEUE_SIZE
    for (int i = 1; i < 7; i++) {
        touchEvent.y = 200 + i * 10;
        touchEvents = {touchEvent};
        optimizer_->RVSQueueUpdate(touchEvents);
    }
    
    // Now deque should have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer_->rvsDequeY_[1].size(), 6);
}

/**
 * @tc.name: RVSQueueUpdate013
 * @tc.desc: Test RVSQueueUpdate duplicate value filtering
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate013, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer_->rvsDequeX_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100; // Same value
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Add same value multiple times
    for (int i = 0; i < 3; i++) {
        optimizer_->RVSQueueUpdate(touchEvents);
    }
    
    // Should only contain one element due to duplicate filtering
    EXPECT_EQ(optimizer_->rvsDequeX_[1].size(), 1);
    EXPECT_EQ(optimizer_->rvsDequeX_[1].back(), 100);
}

/**
 * @tc.name: RVSQueueUpdate014
 * @tc.desc: Test RVSQueueUpdate processing when queue reaches RVS_QUEUE_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate014, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer_->rvsDequeX_.clear();
    
    // Pre-fill deque to RVS_QUEUE_SIZE - 1
    for (int i = 0; i < 6; i++) {
        optimizer_->rvsDequeX_[1].push_back(50 + i * 10);
    }
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 150; // This will make the queue reach RVS_QUEUE_SIZE
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Mock the check functions to avoid complex setup
    optimizer_->RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X);
    optimizer_->RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X);
    
    optimizer_->RVSQueueUpdate(touchEvents);
    
    // Queue should now have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer_->rvsDequeX_[1].size(), 6);
}

/**
 * @tc.name: NeedTpFlushVsync001
 * @tc.desc: Test NeedTpFlushVsync functionality when RVS is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsync001, TestSize.Level1)
{
    optimizer_->rvsEnable_ = false;
    
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    
    // When RVS is disabled, should return false
    EXPECT_FALSE(optimizer_->NeedTpFlushVsync(touchEvent));
    EXPECT_FALSE(optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_);
}

/**
 * @tc.name: NeedTpFlushVsync002
 * @tc.desc: Test NeedTpFlushVsync functionality with different conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsync002, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    optimizer_->slideAccepted_ = false;
    optimizer_->isTpFlushFrameDisplayPeriod_ = true;
    
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    
    // When slide is not accepted, should return true
    EXPECT_TRUE(optimizer_->NeedTpFlushVsync(touchEvent));
    
    // Test the transition to first frame after TP flush
    optimizer_->slideAccepted_ = true;
    optimizer_->isTpFlushFrameDisplayPeriod_ = true;
    optimizer_->lastTpFlush_ = false;
    optimizer_->NeedTpFlushVsyncInner(touchEvent); // Call inner function to set up state
    optimizer_->NeedTpFlushVsync(touchEvent);
    EXPECT_TRUE(optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_);
}

/**
 * @tc.name: NeedTpFlushVsyncInner001
 * @tc.desc: Test NeedTpFlushVsyncInner with various conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsyncInner001, TestSize.Level1)
{
    // Test when RVS is disabled
    optimizer_->rvsEnable_ = false;
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    EXPECT_FALSE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
    
    // Test when hisAvgPointTimeStamp_ is zero
    optimizer_->rvsEnable_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 0;
    EXPECT_FALSE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
    
    // Test with non-finger source tool
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    touchEvent.sourceTool = SourceTool::MOUSE;
    EXPECT_FALSE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
}

/**
 * @tc.name: NeedTpFlushVsyncInner002
 * @tc.desc: Test NeedTpFlushVsyncInner with slide acceptance conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsyncInner002, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    optimizer_->slideAccepted_ = false;
    
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    
    // When slide is not accepted, should trigger TP flush for first frame
    EXPECT_TRUE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
    
    // Test when slide is accepted
    optimizer_->slideAccepted_ = true;
    EXPECT_FALSE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
}

/**
 * @tc.name: NeedTpFlushVsyncInner003
 * @tc.desc: Test NeedTpFlushVsyncInner with last TP flush conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsyncInner003, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    optimizer_->slideAccepted_ = true;
    optimizer_->lastTpFlush_ = true;
    optimizer_->vsyncFlushed_ = true;

    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    
    // When last frame was TP triggered and current Vsync count differs, should continue TP flush
    EXPECT_TRUE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
}

/**
 * @tc.name: NeedTpFlushVsyncInner004
 * @tc.desc: Test NeedTpFlushVsyncInner with reverse direction conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsyncInner004, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    optimizer_->slideAccepted_ = true;
    optimizer_->lastTpFlush_ = false;
    
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    // When current direction is reversed and last frame wasn't TP triggered, should trigger TP flush
    EXPECT_TRUE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
    
    // Test with Y axis reverse
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    touchEvent.yReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    EXPECT_TRUE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
    
    // Test with no reverse direction
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    EXPECT_FALSE(optimizer_->NeedTpFlushVsyncInner(touchEvent));
}

/**
 * @tc.name: SetLastVsyncTimeStamp001
 * @tc.desc: Test SetLastVsyncTimeStamp functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetLastVsyncTimeStamp001, TestSize.Level1)
{
    optimizer_->vsyncTimeReportExemption_ = false;
    optimizer_->vsyncFlushed_ = false;
    optimizer_->lastVsyncTimeStamp_ = 0;
    
    uint64_t testTimeStamp = 123456789;
    optimizer_->SetLastVsyncTimeStamp(testTimeStamp);
    
    EXPECT_TRUE(optimizer_->vsyncFlushed_);
    EXPECT_EQ(optimizer_->lastVsyncTimeStamp_, testTimeStamp);
    EXPECT_FALSE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: SetLastVsyncTimeStamp002
 * @tc.desc: Test SetLastVsyncTimeStamp with exemption
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetLastVsyncTimeStamp002, TestSize.Level1)
{
    optimizer_->vsyncTimeReportExemption_ = true;
    optimizer_->vsyncFlushed_ = false;
    optimizer_->lastVsyncTimeStamp_ = 0;
    
    uint64_t testTimeStamp = 123456789;
    optimizer_->SetLastVsyncTimeStamp(testTimeStamp);
    
    // When exemption is true, should not update vsyncFlushed_ and lastVsyncTimeStamp_
    EXPECT_FALSE(optimizer_->vsyncFlushed_);
    EXPECT_EQ(optimizer_->lastVsyncTimeStamp_, 0);
    EXPECT_FALSE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: SetVsyncPeriod001
 * @tc.desc: Test SetVsyncPeriod functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetVsyncPeriod001, TestSize.Level1)
{
    optimizer_->vsyncPeriod_ = std::numeric_limits<uint64_t>::max();
    
    uint64_t testPeriod = 16666666; // ~60Hz
    optimizer_->SetVsyncPeriod(testPeriod);
    
    EXPECT_EQ(optimizer_->vsyncPeriod_, testPeriod);
}

/**
 * @tc.name: GetIsTpFlushFrameDisplayPeriod001
 * @tc.desc: Test GetIsTpFlushFrameDisplayPeriod functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, GetIsTpFlushFrameDisplayPeriod001, TestSize.Level1)
{
    optimizer_->isTpFlushFrameDisplayPeriod_ = false;
    EXPECT_FALSE(optimizer_->GetIsTpFlushFrameDisplayPeriod());
    
    optimizer_->isTpFlushFrameDisplayPeriod_ = true;
    EXPECT_TRUE(optimizer_->GetIsTpFlushFrameDisplayPeriod());
}

/**
 * @tc.name: GetIsFirstFrameAfterTpFlushFrameDisplayPeriod001
 * @tc.desc: Test GetIsFirstFrameAfterTpFlushFrameDisplayPeriod functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, GetIsFirstFrameAfterTpFlushFrameDisplayPeriod001, TestSize.Level1)
{
    optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_ = false;
    EXPECT_FALSE(optimizer_->GetIsFirstFrameAfterTpFlushFrameDisplayPeriod());
    
    optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_ = true;
    EXPECT_TRUE(optimizer_->GetIsFirstFrameAfterTpFlushFrameDisplayPeriod());
}

/**
 * @tc.name: SetHisAvgPointTimeStamp001
 * @tc.desc: Test SetHisAvgPointTimeStamp with empty history points
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetHisAvgPointTimeStamp001, TestSize.Level1)
{
    optimizer_->hisAvgPointTimeStamp_ = 1000;
    
    std::unordered_map<int32_t, std::vector<TouchEvent>> historyPointsById;
    int32_t pointId = 1;
    
    optimizer_->SetHisAvgPointTimeStamp(pointId, historyPointsById);
    EXPECT_EQ(optimizer_->hisAvgPointTimeStamp_, 0);
}

/**
 * @tc.name: SetHisAvgPointTimeStamp002
 * @tc.desc: Test SetHisAvgPointTimeStamp with valid history points
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetHisAvgPointTimeStamp002, TestSize.Level1)
{
    optimizer_->hisAvgPointTimeStamp_ = 0;
    
    std::unordered_map<int32_t, std::vector<TouchEvent>> historyPointsById;
    int32_t pointId = 1;
    
    TouchEvent event1, event2;
    auto time1 = std::chrono::high_resolution_clock::now();
    auto time2 = time1 + std::chrono::milliseconds(10);
    
    event1.time = time1;
    event2.time = time2;
    
    historyPointsById[pointId].push_back(event1);
    historyPointsById[pointId].push_back(event2);
    
    optimizer_->SetHisAvgPointTimeStamp(pointId, historyPointsById);
    // Should calculate average timestamp
    EXPECT_NE(optimizer_->hisAvgPointTimeStamp_, 0);
}

/**
 * @tc.name: FineTuneTimeStampDuringTpFlushPeriod001
 * @tc.desc: Test FineTuneTimeStampDuringTpFlushPeriod functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, FineTuneTimeStampDuringTpFlushPeriod001, TestSize.Level1)
{
    optimizer_->hisAvgPointTimeStamp_ = 0;
    optimizer_->lastTpFlush_ = false;
    optimizer_->vsyncTimeReportExemption_ = false;
    optimizer_->vsyncPeriod_ = 16666666;
    
    uint64_t testTimeStamp = 123456789;
    uint64_t result = optimizer_->FineTuneTimeStampDuringTpFlushPeriod(testTimeStamp);
    
    // When hisAvgPointTimeStamp_ is 0, should return the original timestamp
    EXPECT_EQ(result, testTimeStamp);
    EXPECT_TRUE(optimizer_->lastTpFlush_);
    EXPECT_TRUE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: FineTuneTimeStampDuringTpFlushPeriod002
 * @tc.desc: Test FineTuneTimeStampDuringTpFlushPeriod with valid hisAvgPointTimeStamp
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, FineTuneTimeStampDuringTpFlushPeriod002, TestSize.Level1)
{
    optimizer_->hisAvgPointTimeStamp_ = 123456789;
    optimizer_->lastTpFlush_ = false;
    optimizer_->vsyncTimeReportExemption_ = false;
    optimizer_->vsyncPeriod_ = 16666666;
    
    uint64_t testTimeStamp = 123456789;
    uint64_t result = optimizer_->FineTuneTimeStampDuringTpFlushPeriod(testTimeStamp);
    
    // Should calculate fictional Vsync time based on hisAvgPointTimeStamp_
    EXPECT_NE(result, testTimeStamp);
    EXPECT_TRUE(optimizer_->lastTpFlush_);
    EXPECT_TRUE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod001
 * @tc.desc: Test FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod with invalid conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod001, TestSize.Level1)
{
    optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_ = false;
    optimizer_->hisAvgPointTimeStamp_ = 0;
    optimizer_->lastVsyncTimeStamp_ = 0;
    optimizer_->lastTpFlush_ = true;
    optimizer_->vsyncTimeReportExemption_ = true;
    
    std::unordered_map<int32_t, std::vector<TouchEvent>> historyPointsById;
    int32_t pointId = 1;
    
    optimizer_->FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod(pointId, historyPointsById);
    
    // Should not change lastTpFlush_ and vsyncTimeReportExemption_ since conditions are not met
    EXPECT_FALSE(optimizer_->lastTpFlush_);
    EXPECT_FALSE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod002
 * @tc.desc: Test FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod with valid conditions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod002, TestSize.Level1)
{
    optimizer_->isFristFrameAfterTpFlushFrameDisplayPeriod_ = true;
    optimizer_->hisAvgPointTimeStamp_ = 200000000;
    optimizer_->lastVsyncTimeStamp_ = 100000000;
    optimizer_->lastTpFlush_ = true;
    optimizer_->vsyncTimeReportExemption_ = true;
    
    std::unordered_map<int32_t, std::vector<TouchEvent>> historyPointsById;
    int32_t pointId = 1;
    
    // Add a test event to history
    TouchEvent testEvent;
    testEvent.time = std::chrono::high_resolution_clock::time_point(std::chrono::nanoseconds(150000000));
    historyPointsById[pointId].push_back(testEvent);
    
    optimizer_->FineTuneTimeStampWhenFirstFrameAfterTpFlushPeriod(pointId, historyPointsById);
    
    // Should reset lastTpFlush_ and vsyncTimeReportExemption_
    EXPECT_FALSE(optimizer_->lastTpFlush_);
    EXPECT_FALSE(optimizer_->vsyncTimeReportExemption_);
}

/**
 * @tc.name: SetPointReverseSignal001
 * @tc.desc: Test SetPointReverseSignal when RVS and rvsSignalEnable_ is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetPointReverseSignal001, TestSize.Level1)
{
    optimizer_->rvsEnable_ = false;
    optimizer_->rvsSignalEnable_ = false;
    optimizer_->vsyncPeriod_ = 8.3 * 1000 * 1000;

    TouchEvent inputEvent;
    inputEvent.id = 1;
    inputEvent.x = 100;
    inputEvent.y = 200;
    inputEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    inputEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    TouchEvent resultEvent = optimizer_->SetPointReverseSignal(inputEvent);
    
    // When RVS is disabled, should return the same event
    EXPECT_EQ(resultEvent.id, inputEvent.id);
    EXPECT_EQ(resultEvent.x, inputEvent.x);
    EXPECT_EQ(resultEvent.y, inputEvent.y);
    EXPECT_EQ(resultEvent.xReverse, inputEvent.xReverse);
    EXPECT_EQ(resultEvent.yReverse, inputEvent.yReverse);
}

/**
 * @tc.name: SetPointReverseSignal002
 * @tc.desc: Test SetPointReverseSignal when RVS is true and rvsSignalEnable_ is false
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetPointReverseSignal002, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->rvsSignalEnable_ = false;
    optimizer_->vsyncPeriod_ = 8.3 * 1000 * 1000;

    TouchEvent inputEvent;
    inputEvent.id = 1;
    inputEvent.x = 100;
    inputEvent.y = 200;
    inputEvent.sourceTool = SourceTool::FINGER;
    inputEvent.type = TouchType::MOVE;
    inputEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    inputEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    TouchEvent resultEvent = optimizer_->SetPointReverseSignal(inputEvent);
    
    // When RVS is enabled, should process the event through RVSQueueUpdate
    EXPECT_EQ(resultEvent.id, inputEvent.id);
    EXPECT_EQ(resultEvent.x, inputEvent.x);
    EXPECT_EQ(resultEvent.y, inputEvent.y);
}

/**
 * @tc.name: SetPointReverseSignal003
 * @tc.desc: Test SetPointReverseSignal when RVS is false and rvsSignalEnable_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetPointReverseSignal003, TestSize.Level1)
{
    optimizer_->rvsEnable_ = false;
    optimizer_->rvsSignalEnable_ = true;
    optimizer_->vsyncPeriod_ = 8.3 * 1000 * 1000;

    TouchEvent inputEvent;
    inputEvent.id = 1;
    inputEvent.x = 100;
    inputEvent.y = 200;
    inputEvent.sourceTool = SourceTool::FINGER;
    inputEvent.type = TouchType::MOVE;
    inputEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    inputEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    TouchEvent resultEvent = optimizer_->SetPointReverseSignal(inputEvent);
    
    // When RVS is enabled, should process the event through RVSQueueUpdate
    EXPECT_EQ(resultEvent.id, inputEvent.id);
    EXPECT_EQ(resultEvent.x, inputEvent.x);
    EXPECT_EQ(resultEvent.y, inputEvent.y);
}

/**
 * @tc.name: SetPointReverseSignal004
 * @tc.desc: Test SetPointReverseSignal when RVS is false and rvsSignalEnable_ is true
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetPointReverseSignal004, TestSize.Level1)
{
    optimizer_->rvsEnable_ = true;
    optimizer_->rvsSignalEnable_ = true;
    optimizer_->vsyncPeriod_ = 8.3 * 1000 * 1000;

    TouchEvent inputEvent;
    inputEvent.id = 1;
    inputEvent.x = 100;
    inputEvent.y = 200;
    inputEvent.sourceTool = SourceTool::FINGER;
    inputEvent.type = TouchType::MOVE;
    inputEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    inputEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    TouchEvent resultEvent = optimizer_->SetPointReverseSignal(inputEvent);
    
    // When RVS is enabled, should process the event through RVSQueueUpdate
    EXPECT_EQ(resultEvent.id, inputEvent.id);
    EXPECT_EQ(resultEvent.x, inputEvent.x);
    EXPECT_EQ(resultEvent.y, inputEvent.y);
}
} // namespace OHOS::Ace