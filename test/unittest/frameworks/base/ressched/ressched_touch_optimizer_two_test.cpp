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

    enum RVS_RESET_INFO : int32_t {
        RVS_RESET_ALL = 0,
        RVS_RESET_CUR_ID = 1,
    };
    
    enum RVS_AXIS : int32_t {
        RVS_AXIS_X = 0,
        RVS_AXIS_Y = 1,
    };

    enum RVS_FINETUNE_STATE : int32_t {
        NO_CHANGE = 0,
        TP_USE = 1,
        OFFSET = 2,
    };

    // slide direction from pan recognizer
    enum SLIDE_DIRECTION : int32_t {
        VERTICAL = 0,
        HORIZONTAL = 1,
        FREE = 2,
        NONE = 3,
    };
} // namespace

class ResSchedTouchOptimizerTwoTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
    }
    static void TearDownTestSuite()
    {
    }
    void SetUp() {};
    void TearDown() {};
};

/**
 * @tc.name: RVSQueueUpdate008
 * @tc.desc: test RVSQueueUpdate with queue overflow triggering pop_front
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate008, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 200;
    touchEvent.y = 300;
    touchEvent.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    touchEvent.yReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
    // Pre-fill deques with exactly RVS_QUEUE_SIZE elements
    optimizer.rvsDequeX_[1].clear();
    for (int i = 0; i < 7; i++) {
        optimizer.rvsDequeX_[1].push_back(100 + i * 5);
    }
    
    optimizer.rvsDequeY_[1].clear();
    for (int i = 0; i < 7; i++) {
        optimizer.rvsDequeY_[1].push_back(200 + i * 5);
    }
    
    // Save the front elements to check if they get popped
    double frontX = optimizer.rvsDequeX_[1].front();
    double frontY = optimizer.rvsDequeY_[1].front();
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // After adding the new event, the front element should be popped
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Check that the size is still RVS_QUEUE_SIZE (7)
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 7);
    EXPECT_EQ(optimizer.rvsDequeY_[1].size(), 7);
    
    // The new element should be at the back
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 130);
    EXPECT_EQ(optimizer.rvsDequeY_[1].back(), 300);
    
    // The old front element should no longer be in the deque
    EXPECT_EQ(optimizer.rvsDequeX_[1].front(), frontX);
    EXPECT_NE(optimizer.rvsDequeY_[1].front(), frontY);
}

/**
 * @tc.name: RVSQueueUpdate009
 * @tc.desc: test RVSQueueUpdate with non-move event type
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate009, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    // Pre-populate some data for id=1
    optimizer.rvsDequeX_[1].push_back(100);
    optimizer.rvsDequeY_[1].push_back(200);
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    optimizer.stateTagY_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::UP; // Non-MOVE type
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 150;
    touchEvent.y = 250;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Should reset data for id=1 since it's a non-MOVE event
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Check that data for id=1 has been cleared
    EXPECT_TRUE(optimizer.rvsDequeX_.find(1) == optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(1) == optimizer.rvsDequeY_.end());
    EXPECT_TRUE(optimizer.stateTagX_.find(1) == optimizer.stateTagX_.end());
    EXPECT_TRUE(optimizer.stateTagY_.find(1) == optimizer.stateTagY_.end());
}

/**
 * @tc.name: RVSQueueUpdate010
 * @tc.desc: test RVSQueueUpdate with mixed event types
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate010, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent moveEvent;
    moveEvent.id = 1;
    moveEvent.type = TouchType::MOVE;
    moveEvent.sourceTool = SourceTool::FINGER;
    moveEvent.x = 100;
    moveEvent.y = 200;
    
    TouchEvent upEvent;
    upEvent.id = 2;
    upEvent.type = TouchType::UP;
    upEvent.sourceTool = SourceTool::FINGER;
    upEvent.x = 150;
    upEvent.y = 250;
    
    std::list<TouchEvent> touchEvents = {moveEvent, upEvent};
    
    optimizer.RVSQueueUpdate(touchEvents);
    
    // MOVE event should be processed and data added
    EXPECT_TRUE(optimizer.rvsDequeX_.find(1) == optimizer.rvsDequeX_.end());
    EXPECT_FALSE(optimizer.rvsDequeY_.find(1) == optimizer.rvsDequeY_.end());
    
    // data for ID 1 should still exist
    EXPECT_TRUE(optimizer.rvsDequeX_.find(1) == optimizer.rvsDequeX_.end());
    EXPECT_FALSE(optimizer.rvsDequeY_.find(1) == optimizer.rvsDequeY_.end());
}

/**
 * @tc.name: RVSSingleAxisUpdate002
 * @tc.desc: test RVSSingleAxisUpdate coverage
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSSingleAxisUpdate002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent moveEvent;
    double result = 0.0;
    moveEvent.id = 1;
    moveEvent.type = TouchType::MOVE;
    moveEvent.sourceTool = SourceTool::FINGER;
    moveEvent.x = 100;
    moveEvent.y = 200;
    
    TouchEvent resampleEvent;
    resampleEvent.id = 1;
    resampleEvent.type = TouchType::MOVE;
    resampleEvent.sourceTool = SourceTool::FINGER;
    resampleEvent.x = 150;
    resampleEvent.y = 250;
    optimizer.stateTagY_[1] = RVS_FINETUNE_STATE::OFFSET;
    EXPECT_TRUE(optimizer.RVSSingleAxisUpdate(moveEvent, resampleEvent, false, RVS_AXIS::RVS_AXIS_Y, result));
}

/**
 * @tc.name: RVSPointCheckWithSignal005
 * @tc.desc: test RVSPointCheckWithSignal with multiple elements and gap calculation
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithSignal005, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 150;
    touchEvent.y = 250;
    touchEvent.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT; // Signal indicating reverse
    
    // Fill deque with multiple elements for X axis
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // First element
    optimizer.rvsDequeX_[1].push_back(120); // Second element
    optimizer.rvsDequeX_[1].push_back(130); // Third element
    optimizer.rvsDequeX_[1].push_back(150); // Current element (back)
    
    // Test X axis with multiple elements
    EXPECT_TRUE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    // Gap should be positive (150-130=20), so direction should be RVS_DOWN_LEFT
    EXPECT_EQ(touchEvent.xReverse, RVS_DIRECTION::RVS_DOWN_LEFT);
}

/**
 * @tc.name: RVSPointCheckWithSignal006
 * @tc.desc: test RVSPointCheckWithSignal with negative gap
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithSignal006, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 90;
    touchEvent.y = 190;
    touchEvent.yReverse = RVS_DIRECTION::RVS_UP_RIGHT; // Signal indicating reverse
    
    // Fill deque with multiple elements for Y axis
    optimizer.rvsDequeY_[1].clear();
    optimizer.rvsDequeY_[1].push_back(200); // First element
    optimizer.rvsDequeY_[1].push_back(190); // Second element
    optimizer.rvsDequeY_[1].push_back(180); // Third element
    optimizer.rvsDequeY_[1].push_back(90);  // Current element (back)
    
    // Test Y axis with multiple elements and negative gap
    EXPECT_TRUE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_Y));
    // Gap should be negative (90-180=-90), so direction should be RVS_UP_RIGHT
    EXPECT_EQ(touchEvent.yReverse, RVS_DIRECTION::RVS_UP_RIGHT);
}

/**
 * @tc.name: RVSPointCheckWithoutSignal003
 * @tc.desc: test RVSPointCheckWithoutSignal with direction change detection
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing direction change for X axis
    // Sequence: 150 -> 130 -> 100 (decreasing, then decreasing again)
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(150); // First element
    optimizer.rvsDequeX_[1].push_back(130); // Second element (gap1 = 130-150 = -20)
    optimizer.rvsDequeX_[1].push_back(100); // Third element (gap2 = 100-130 = -30)
    
    // Both gaps are negative, so no direction change - should return false
    EXPECT_FALSE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    EXPECT_EQ(touchEvent.xReverse, RVS_DIRECTION::RVS_NOT_APPLY); // Should remain unchanged
}

/**
 * @tc.name: RVSPointCheckWithoutSignal004
 * @tc.desc: test RVSPointCheckWithoutSignal with actual direction change
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 130;
    touchEvent.y = 230;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing actual direction change for X axis
    // Sequence: 100 -> 150 -> 130 (increasing, then decreasing)
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // First element
    optimizer.rvsDequeX_[1].push_back(150); // Second element (gap1 = 150-100 = 50, positive)
    optimizer.rvsDequeX_[1].push_back(130); // Third element (gap2 = 130-150 = -20, negative)
    
    // Gaps have different signs, so direction change detected - should return true
    EXPECT_TRUE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
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
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 160;
    touchEvent.y = 260;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No initial signal
    
    // Fill deque with elements showing reverse direction change for Y axis
    // Sequence: 200 -> 150 -> 160 (decreasing, then increasing)
    optimizer.rvsDequeY_[1].clear();
    optimizer.rvsDequeY_[1].push_back(200); // First element
    optimizer.rvsDequeY_[1].push_back(150); // Second element (gap1 = 150-200 = -50, negative)
    optimizer.rvsDequeY_[1].push_back(160); // Third element (gap2 = 160-150 = 10, positive)
    
    // Gaps have different signs, so direction change detected - should return true
    EXPECT_TRUE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_Y));
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
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    // Fill deque with only one element
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // Only one element
    
    // With only one element, pointCurrent will be set but no gaps can be calculated
    // Loop will exit without processing gaps, should return false
    EXPECT_FALSE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: RVSPointCheckWithoutSignal007
 * @tc.desc: test RVSPointCheckWithoutSignal with two elements
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSPointCheckWithoutSignal007, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 150;
    touchEvent.y = 250;
    
    // Fill deque with two elements
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // First element
    optimizer.rvsDequeX_[1].push_back(150); // Second element
    
    // With two elements, gap1 will be calculated but not gap2
    // Loop will exit without comparing gap signs, should return false
    EXPECT_TRUE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: SetSlideDirection001
 * @tc.desc: Test SetSlideDirection functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, SetSlideDirection001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.slideDirection_ = SLIDE_DIRECTION::NONE;
    
    optimizer.SetSlideDirection(SLIDE_DIRECTION::HORIZONTAL);
    EXPECT_EQ(optimizer.slideDirection_, SLIDE_DIRECTION::HORIZONTAL);
    
    optimizer.SetSlideDirection(SLIDE_DIRECTION::VERTICAL);
    EXPECT_EQ(optimizer.slideDirection_, SLIDE_DIRECTION::VERTICAL);
}

/**
 * @tc.name: NeedTpFlushVsync003
 * @tc.desc: Test NeedTpFlushVsync lastTpFlushCount_ reset branch
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, NeedTpFlushVsync003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.slideAccepted_ = true;
    optimizer.lastTpFlush_ = false;
    optimizer.lastTpFlushCount_ = 100;
    
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    // Test the branch where lastTpFlushCount_ != 0 && lastTpFlushCount_ == currentVsyncCount
    EXPECT_FALSE(optimizer.NeedTpFlushVsync(touchEvent, 100));
    EXPECT_EQ(optimizer.lastTpFlushCount_, 0); // Should be reset to 0
}

/**
 * @tc.name: RVSDirectionStateCheck001
 * @tc.desc: Test RVSDirectionStateCheck with different directions
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSDirectionStateCheck001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    
    // Test valid directions
    EXPECT_TRUE(optimizer.RVSDirectionStateCheck(RVS_DIRECTION::RVS_DOWN_LEFT));
    EXPECT_TRUE(optimizer.RVSDirectionStateCheck(RVS_DIRECTION::RVS_UP_RIGHT));
    
    // Test invalid directions
    EXPECT_FALSE(optimizer.RVSDirectionStateCheck(RVS_DIRECTION::RVS_NOT_APPLY));
    EXPECT_FALSE(optimizer.RVSDirectionStateCheck(RVS_DIRECTION::RVS_INITIAL_SIGNAL));
    EXPECT_FALSE(optimizer.RVSDirectionStateCheck(100)); // Invalid value
}

/**
 * @tc.name: RVSQueueUpdate011
 * @tc.desc: Test RVSQueueUpdate horizontal slide direction processing
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate011, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer.rvsDequeX_.clear();
    optimizer.rvsDequeY_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // First call - should add to deque but not process yet (size < RVS_QUEUE_SIZE)
    optimizer.RVSQueueUpdate(touchEvents);
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 1);
    EXPECT_TRUE(optimizer.rvsDequeY_[1].empty()); // Y should not be processed for horizontal slide
    
    // Add more events to reach RVS_QUEUE_SIZE
    for (int i = 1; i < 7; i++) {
        touchEvent.x = 100 + i * 10;
        touchEvents = {touchEvent};
        optimizer.RVSQueueUpdate(touchEvents);
    }
    
    // Now deque should have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 6);
}

/**
 * @tc.name: RVSQueueUpdate012
 * @tc.desc: Test RVSQueueUpdate vertical slide direction processing
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate012, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.slideDirection_ = SLIDE_DIRECTION::VERTICAL;
    optimizer.rvsDequeX_.clear();
    optimizer.rvsDequeY_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // First call - should add to deque but not process yet (size < RVS_QUEUE_SIZE)
    optimizer.RVSQueueUpdate(touchEvents);
    EXPECT_EQ(optimizer.rvsDequeY_[1].size(), 1);
    EXPECT_TRUE(optimizer.rvsDequeX_[1].empty()); // X should not be processed for vertical slide
    
    // Add more events to reach RVS_QUEUE_SIZE
    for (int i = 1; i < 7; i++) {
        touchEvent.y = 200 + i * 10;
        touchEvents = {touchEvent};
        optimizer.RVSQueueUpdate(touchEvents);
    }
    
    // Now deque should have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer.rvsDequeY_[1].size(), 6);
}

/**
 * @tc.name: RVSQueueUpdate013
 * @tc.desc: Test RVSQueueUpdate duplicate value filtering
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate013, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer.rvsDequeX_.clear();
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100; // Same value
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Add same value multiple times
    for (int i = 0; i < 3; i++) {
        optimizer.RVSQueueUpdate(touchEvents);
    }
    
    // Should only contain one element due to duplicate filtering
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 1);
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 100);
}

/**
 * @tc.name: RVSQueueUpdate014
 * @tc.desc: Test RVSQueueUpdate processing when queue reaches RVS_QUEUE_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTwoTest, RVSQueueUpdate014, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.slideDirection_ = SLIDE_DIRECTION::HORIZONTAL;
    optimizer.rvsDequeX_.clear();
    
    // Pre-fill deque to RVS_QUEUE_SIZE - 1
    for (int i = 0; i < 6; i++) {
        optimizer.rvsDequeX_[1].push_back(50 + i * 10);
    }
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 150; // This will make the queue reach RVS_QUEUE_SIZE
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Mock the check functions to avoid complex setup
    optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X);
    optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X);
    
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Queue should now have RVS_QUEUE_SIZE elements
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 6);
}
} // namespace OHOS::Ace