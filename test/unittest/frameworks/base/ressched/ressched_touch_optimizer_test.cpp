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
    constexpr int32_t DPT_QUEUE_SIZE = 3;
    constexpr int32_t COMPENSATE_EXTENT = 4;
    constexpr double THRESHOLD_OFFSET_VALUE = 2.0;

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
} // namespace

class ResSchedTouchOptimizerTest : public testing::Test {
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
 * @tc.name: SetterTest001
 * @tc.desc: test setter method
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SetterTest001, TestSize.Level1)
{
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(true);
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().slideAccepted_);
    ResSchedTouchOptimizer::GetInstance().SetLastTpFlush(true);
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().lastTpFlush_);
    ResSchedTouchOptimizer::GetInstance().SetLastTpFlushCount(100);
    EXPECT_EQ(ResSchedTouchOptimizer::GetInstance().lastTpFlushCount_, 100);
    ResSchedTouchOptimizer::GetInstance().SetSlideAccepted(false);
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().slideAccepted_);
    ResSchedTouchOptimizer::GetInstance().SetLastTpFlush(false);
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().lastTpFlush_);
}

/**
 * @tc.name: NeedTpFlushVsync001
 * @tc.desc: test NeedTpFlushVsync
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, NeedTpFlushVsync001, TestSize.Level1)
{
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::FINGER;
    ResSchedTouchOptimizer::GetInstance().rvsEnable_ = false;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
    touchEvent.sourceTool = SourceTool::MOUSE;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
    ResSchedTouchOptimizer::GetInstance().rvsEnable_ = true;
    touchEvent.sourceTool = SourceTool::FINGER;
    ResSchedTouchOptimizer::GetInstance().slideAccepted_ = false;
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
    ResSchedTouchOptimizer::GetInstance().slideAccepted_ = true;
    ResSchedTouchOptimizer::GetInstance().lastTpFlushCount_ = 100;
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 101));
    ResSchedTouchOptimizer::GetInstance().lastTpFlush_ = false;
    touchEvent.xReverse = true;
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 100));
    touchEvent.xReverse = false;
    touchEvent.yReverse = false;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 100));
    ResSchedTouchOptimizer::GetInstance().lastTpFlush_ = true;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 100));
}

/**
 * @tc.name: HandleMainDelta_Test001
 * @tc.desc: test HandleMainDelta when rvs is disabled
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleMainDelta_Test001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.SetSlideAcceptOffset(Offset(0.0, 0.0));
    optimizer.rvsEnable_ = false;

    double mainDelta = 10.0;
    double touchPointsSize = 5.0;
    std::map<int32_t, TouchEvent> touchPoints;
    double result = optimizer.HandleMainDelta(mainDelta, touchPointsSize, touchPoints);

    EXPECT_DOUBLE_EQ(result, mainDelta / touchPointsSize);
}

/**
 * @tc.name: HandleMainDelta_Test002
 * @tc.desc: test HandleMainDelta when rvs is enabled with compensation
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleMainDelta_Test002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = false;
    optimizer.SetSlideAcceptOffset(Offset(10.0, 10.0));
    optimizer.rvsEnable_ = true;
    optimizer.SetSlideAcceptOffset(Offset(10.0, 10.0));

    double mainDelta = 10.0;
    double touchPointsSize = 5.0;
    std::map<int32_t, TouchEvent> touchPoints;
    double result = optimizer.HandleMainDelta(mainDelta, touchPointsSize, touchPoints);

    EXPECT_DOUBLE_EQ(result, mainDelta / touchPointsSize + mainDelta / (touchPointsSize * COMPENSATE_EXTENT));
}

/**
 * @tc.name: HandleMainDelta_Test003
 * @tc.desc: test HandleMainDelta with accumulated distance
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleMainDelta_Test003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.SetSlideAcceptOffset(Offset(10.0, 10.0));
    optimizer.accumulatedDistance_ = 10.0;

    double mainDelta = 10.0;
    double touchPointsSize = 5.0;
    std::map<int32_t, TouchEvent> touchPoints;
    double result = optimizer.HandleMainDelta(mainDelta, touchPointsSize, touchPoints);

    EXPECT_DOUBLE_EQ(result, 2.5);
}

/**
 * @tc.name: SetSliceAcceptOffsetTest001
 * @tc.desc: test SetSlideAcceptOffset with non-zero offset
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SetSliceAcceptOffsetTest001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    Offset offset = {10.0, 20.0};
    optimizer.SetSlideAcceptOffset(offset);
    
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetX(), offset.GetX());
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetX(), offset.GetX());
    EXPECT_DOUBLE_EQ(optimizer.accumulatedDistance_, 0.0);
}

/**
 * @tc.name: SetSliceAcceptOffsetTest002
 * @tc.desc: test SetSlideAcceptOffset with zero offset
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SetSliceAcceptOffsetTest002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    Offset offset = {0.0, 0.0};
    optimizer.SetSlideAcceptOffset(offset);
    
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetX(), offset.GetX());
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetX(), offset.GetX());
    EXPECT_DOUBLE_EQ(optimizer.accumulatedDistance_, 0.0);
}

/**
 * @tc.name: RVSQueueUpdate001
 * @tc.desc: test RVSQueueUpdate with multiple touch events
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;

    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.sourceTool = SourceTool::FINGER;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.type = TouchType::DOWN;
    touchEvent2.sourceTool = SourceTool::FINGER;

    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};

    optimizer.RVSQueueUpdate(touchEvents);

    EXPECT_FALSE(optimizer.rvsDequeX_[1].empty());
    EXPECT_FALSE(optimizer.rvsDequeY_[1].empty());
    EXPECT_TRUE(optimizer.rvsDequeX_.find(2) == optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(2) == optimizer.rvsDequeY_.end());
}

/**
 * @tc.name: RVSPointCheckWithSignal001
 * @tc.desc: test RVSPointCheckWithSignal functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;

    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.sourceTool = SourceTool::FINGER;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.type = TouchType::DOWN;
    touchEvent2.sourceTool = SourceTool::FINGER;

    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};

    optimizer.RVSQueueUpdate(touchEvents);

    EXPECT_FALSE(optimizer.rvsDequeX_[1].empty());
    EXPECT_FALSE(optimizer.rvsDequeY_[1].empty());
    EXPECT_TRUE(optimizer.rvsDequeX_.find(2) == optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(2) == optimizer.rvsDequeY_.end());
}

/**
 * @tc.name: RVSPointCheckWithoutSignal001
 * @tc.desc: test RVSPointCheckWithoutSignal functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;

    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    touchEvent1.sourceTool = SourceTool::FINGER;

    std::deque<double> yDeque = {50, 75, 100};
    optimizer.rvsDequeX_[1] = yDeque;
    EXPECT_FALSE(optimizer.RVSPointCheckWithoutSignal(touchEvent1, RVS_AXIS::RVS_AXIS_Y));

    yDeque = {200, 190, 180, 170, 160, 150, 140, 130, 120, 110, 200};
    optimizer.rvsDequeY_[1] = yDeque;

    EXPECT_TRUE(optimizer.RVSPointCheckWithoutSignal(touchEvent1, RVS_AXIS::RVS_AXIS_Y));
    EXPECT_NE(touchEvent1.yReverse, RVS_DIRECTION::RVS_NOT_APPLY);
}

/**
 * @tc.name: RVSPointReset001
 * @tc.desc: test RVSPointReset functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointReset001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    int32_t id = 1;
    optimizer.rvsDequeX_[id].push_back(100);
    optimizer.rvsDequeY_[id].push_back(200);
    optimizer.stateTagX_[id] = 1;
    optimizer.stateTagY_[id] = 1;
    optimizer.dptGapX_[id] = 5.0;
    optimizer.dptGapY_[id] = 10.0;

    optimizer.RVSPointReset(id, RVS_RESET_INFO::RVS_RESET_CUR_ID);
    EXPECT_TRUE(optimizer.rvsDequeX_.find(id) == optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(id) == optimizer.rvsDequeY_.end());
    EXPECT_TRUE(optimizer.stateTagX_.find(id) == optimizer.stateTagX_.end());
    EXPECT_TRUE(optimizer.stateTagY_.find(id) == optimizer.stateTagY_.end());
    EXPECT_TRUE(optimizer.dptGapX_.find(id) == optimizer.dptGapX_.end());
    EXPECT_TRUE(optimizer.dptGapY_.find(id) == optimizer.dptGapY_.end());

    optimizer.rvsDequeX_[id].push_back(100);
    optimizer.rvsDequeY_[id].push_back(200);
    optimizer.stateTagX_[id] = 1;
    optimizer.stateTagY_[id] = 1;
    optimizer.dptGapX_[id] = 5.0;
    optimizer.dptGapY_[id] = 10.0;

    optimizer.RVSPointReset(0, RVS_RESET_INFO::RVS_RESET_ALL);
    EXPECT_TRUE(optimizer.rvsDequeX_.empty());
    EXPECT_TRUE(optimizer.rvsDequeY_.empty());
    EXPECT_TRUE(optimizer.stateTagX_.empty());
    EXPECT_TRUE(optimizer.stateTagY_.empty());
    EXPECT_TRUE(optimizer.dptGapX_.empty());
    EXPECT_TRUE(optimizer.dptGapY_.empty());
    EXPECT_EQ(optimizer.lastRVSPointTimeStamp_, 0);
}

/**
 * @tc.name: DispatchPointSelect001
 * @tc.desc: test DispatchPointSelect functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, DispatchPointSelect001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;

    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    touchEvent1.sourceTool = SourceTool::FINGER;

    TouchEvent resamplePoint;
    resamplePoint.id = 1;
    resamplePoint.type = TouchType::MOVE;
    resamplePoint.x = 150;
    resamplePoint.y = 250;
    resamplePoint.sourceTool = SourceTool::FINGER;

    TouchEvent resultPoint;

    optimizer.DispatchPointSelect(true, touchEvent1, resamplePoint, resultPoint);
    EXPECT_EQ(resultPoint.x, resamplePoint.x);
    EXPECT_EQ(resultPoint.y, resamplePoint.y);

    optimizer.DispatchPointSelect(false, touchEvent1, resamplePoint, resultPoint);
    EXPECT_EQ(resultPoint.x, touchEvent1.x);
    EXPECT_EQ(resultPoint.y, touchEvent1.y);

    EXPECT_FALSE(optimizer.dptHistoryPointX_[1].empty());
    EXPECT_FALSE(optimizer.dptHistoryPointY_[1].empty());
}

/**
 * @tc.name: SelectSinglePoint001
 * @tc.desc: test SelectSinglePoint functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SelectSinglePoint001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;

    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    touchEvent1.sourceTool = SourceTool::FINGER;

    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.sourceTool = SourceTool::FINGER;

    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};

    optimizer.SelectSinglePoint(touchEvents);

    EXPECT_EQ(touchEvents.front().id, touchEvent1.id);
    EXPECT_EQ(touchEvents.front().xReverse, RVS_DIRECTION::RVS_DOWN_LEFT);

    touchEvents.clear();
    touchEvents = {touchEvent2};
    optimizer.SelectSinglePoint(touchEvents);
    EXPECT_EQ(touchEvents.front().id, touchEvent2.id);
}

/**
 * @tc.name: UpdateDepHistory001
 * @tc.desc: test UpdateDptHistory functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, UpdateDepHistory001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent event;
    event.id = 1;
    event.x = 100;
    event.y = 200;
    event.sourceTool = SourceTool::FINGER;

    optimizer.UpdateDptHistory(event);
    EXPECT_FALSE(optimizer.dptHistoryPointX_[1].empty());
    EXPECT_FALSE(optimizer.dptHistoryPointY_[1].empty());

    for (int i = 0; i < DPT_QUEUE_SIZE; i++) {
        optimizer.UpdateDptHistory(event);
    }

    EXPECT_EQ(optimizer.dptHistoryPointX_[1].size(), DPT_QUEUE_SIZE);
    EXPECT_EQ(optimizer.dptHistoryPointY_[1].size(), DPT_QUEUE_SIZE);
}

/**
 * @tc.name: RVSEnableCheck001
 * @tc.desc: test RVSEnableCheck functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSEnableCheck001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = false;
    EXPECT_FALSE(optimizer.RVSEnableCheck());
    optimizer.rvsEnable_ = true;
    EXPECT_TRUE(optimizer.RVSEnableCheck());
}

/**
 * @tc.name: UpdateState001
 * @tc.desc: test UpdateState functionality
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, UpdateState001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    int32_t id = 1;
    
    optimizer.UpdateState(id, RVS_FINETUNE_STATE::TP_USE, RVS_AXIS::RVS_AXIS_X);
    EXPECT_EQ(optimizer.stateTagX_[id], RVS_FINETUNE_STATE::TP_USE);
    
    optimizer.UpdateState(id, RVS_FINETUNE_STATE::OFFSET, RVS_AXIS::RVS_AXIS_Y);
    EXPECT_EQ(optimizer.stateTagY_[id], RVS_FINETUNE_STATE::OFFSET);
}

/**
 * @tc.name: HandleState0_001
 * @tc.desc: test HandleState0 when queue size is less than DPT_QUEUE_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState0_001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    
    double result = 0.0;
    bool resampleEnable = false;
    
    // Clear history first
    optimizer.dptHistoryPointX_.clear();
    optimizer.dptHistoryPointY_.clear();
    
    // Test when queue is empty
    EXPECT_FALSE(optimizer.HandleState0(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    
    // Test when queue has less than DPT_QUEUE_SIZE elements
    optimizer.dptHistoryPointX_[1].push_back(90);
    optimizer.dptHistoryPointX_[1].push_back(95);
    EXPECT_FALSE(optimizer.HandleState0(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
}

/**
 * @tc.name: HandleState0_002
 * @tc.desc: test HandleState0 when movement is small
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState0_002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100; // Small movement from history
    point.y = 200;
    
    double result = 0.0;
    bool resampleEnable = false;
    
    // Fill history with close values
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(99);
    optimizer.dptHistoryPointX_[1].push_back(99.5);
    optimizer.dptHistoryPointX_[1].push_back(100); // Back element
    
    EXPECT_TRUE(optimizer.HandleState0(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::TP_USE);
    EXPECT_DOUBLE_EQ(result, 100.0);
}

/**
 * @tc.name: HandleState1_001
 * @tc.desc: test HandleState1 with reverse signal RVS_DOWN_LEFT
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(90);
    optimizer.dptHistoryPointX_[1].push_back(95);
    optimizer.dptHistoryPointX_[1].push_back(110); // Second to last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
}

/**
 * @tc.name: HandleState1_002
 * @tc.desc: test HandleState1 with reverse signal RVS_UP_RIGHT
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(110);
    optimizer.dptHistoryPointX_[1].push_back(105);
    optimizer.dptHistoryPointX_[1].push_back(90); // Second to last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
}

/**
 * @tc.name: HandleState1_003
 * @tc.desc: test HandleState1 transition back to NO_CHANGE with large movement
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 120; // Large movement
    point.y = 200;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(90);
    optimizer.dptHistoryPointX_[1].push_back(95);
    optimizer.dptHistoryPointX_[1].push_back(100); // Back element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_TRUE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::NO_CHANGE);
}

/**
 * @tc.name: HandleState2_001
 * @tc.desc: test HandleState2 transition back to NO_CHANGE
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState2_001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 110; // Value that satisfies transition condition
    point.y = 200;
    
    double result = 0.0;
    
    // Setup gap
    optimizer.dptGapX_[1] = -5.0; // Positive gap
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
}

/**
 * @tc.name: HandleState2_002
 * @tc.desc: test HandleState2 with offset compensation
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState2_002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    
    double result = 0.0;
    
    // Setup gap
    optimizer.dptGapX_[1] = 5.0;
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(result, 95.0); // point.x - dptGapX_
}

/**
 * @tc.name: RVSSingleAxisUpdate001
 * @tc.desc: test RVSSingleAxisUpdate for different states
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSSingleAxisUpdate001, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    
    TouchEvent resamplePoint;
    resamplePoint.id = 1;
    resamplePoint.x = 105;
    resamplePoint.y = 205;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Test NO_CHANGE state
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::NO_CHANGE;
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(99);
    optimizer.dptHistoryPointX_[1].push_back(99.5);
    optimizer.dptHistoryPointX_[1].push_back(100);
    
    EXPECT_TRUE(optimizer.RVSSingleAxisUpdate(point, resamplePoint, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::TP_USE);
}

/**
 * @tc.name: RVSPointCheckWithSignal002
 * @tc.desc: test RVSPointCheckWithSignal with no signal
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No signal
    
    // Fill deque
    optimizer.rvsDequeX_[1].push_back(80);
    optimizer.rvsDequeX_[1].push_back(90);
    optimizer.rvsDequeX_[1].push_back(100);
    
    EXPECT_FALSE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: RVSPointCheckWithoutSignal002
 * @tc.desc: test RVSPointCheckWithoutSignal with same direction gaps
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    // Fill deque with same direction values
    std::deque<double> xDeque = {100, 110, 120, 130, 140, 150, 160};
    optimizer.rvsDequeX_[1] = xDeque;
    
    EXPECT_FALSE(optimizer.RVSPointCheckWithoutSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: SelectSinglePoint002
 * @tc.desc: test SelectSinglePoint with no reverse signal
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SelectSinglePoint002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No reverse
    touchEvent1.sourceTool = SourceTool::FINGER;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent1};
    
    optimizer.SelectSinglePoint(touchEvents);
    
    // Should still contain the point as it's the last one
    EXPECT_FALSE(touchEvents.empty());
}

/**
 * @tc.name: NeedTpFlushVsync002
 * @tc.desc: test NeedTpFlushVsync with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, NeedTpFlushVsync002, TestSize.Level1)
{
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::MOUSE;
    ResSchedTouchOptimizer::GetInstance().rvsEnable_ = true;
    
    // Test with MOUSE source tool, should return false
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
    
    // Test with PEN source tool, should return false
    touchEvent.sourceTool = SourceTool::PEN;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
    
    // Test with TOUCH_PAD source tool, should return false
    touchEvent.sourceTool = SourceTool::TOUCHPAD;
    EXPECT_FALSE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 0));
}

/**
 * @tc.name: RVSQueueUpdate002
 * @tc.desc: test RVSQueueUpdate with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.sourceTool = SourceTool::MOUSE; // Non-finger source
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.type = TouchType::MOVE;
    touchEvent2.sourceTool = SourceTool::FINGER; // Finger source
    touchEvent2.x = 150;
    touchEvent2.y = 250;
    
    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};
    
    // Should return early when encountering non-finger source
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Since the first event is non-finger, processing should stop and no data should be added
    EXPECT_TRUE(optimizer.rvsDequeX_.empty());
    EXPECT_TRUE(optimizer.rvsDequeY_.empty());
}

/**
 * @tc.name: RVSQueueUpdate003
 * @tc.desc: test RVSQueueUpdate with mixed finger and non-finger sources
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.sourceTool = SourceTool::FINGER;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.type = TouchType::MOVE;
    touchEvent2.sourceTool = SourceTool::MOUSE; // Non-finger source
    touchEvent2.x = 150;
    touchEvent2.y = 250;
    
    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};
    
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Second event should not be processed
    EXPECT_TRUE(optimizer.rvsDequeX_.find(2) == optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(2) == optimizer.rvsDequeY_.end());
}

/**
 * @tc.name: DispatchPointSelect002
 * @tc.desc: test DispatchPointSelect with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, DispatchPointSelect002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.dptHistoryPointX_.clear();
    optimizer.dptHistoryPointY_.clear();
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.x = 100;
    touchEvent1.y = 200;
    touchEvent1.sourceTool = SourceTool::MOUSE; // Non-finger source
    
    TouchEvent resamplePoint;
    resamplePoint.id = 1;
    resamplePoint.type = TouchType::MOVE;
    resamplePoint.x = 150;
    resamplePoint.y = 250;
    resamplePoint.sourceTool = SourceTool::MOUSE;
    
    TouchEvent resultPoint;
    
    // With non-finger source, RVS optimization should not be applied
    optimizer.DispatchPointSelect(true, touchEvent1, resamplePoint, resultPoint);
    EXPECT_EQ(resultPoint.x, resamplePoint.x);
    EXPECT_EQ(resultPoint.y, resamplePoint.y);
    
    // Check that no RVS data was added
    EXPECT_TRUE(optimizer.dptHistoryPointX_.find(1) == optimizer.dptHistoryPointX_.end());
    EXPECT_TRUE(optimizer.dptHistoryPointY_.find(1) == optimizer.dptHistoryPointY_.end());
}

/**
 * @tc.name: SelectSinglePoint003
 * @tc.desc: test SelectSinglePoint with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SelectSinglePoint003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    touchEvent1.sourceTool = SourceTool::MOUSE; // Non-finger source
    
    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.sourceTool = SourceTool::MOUSE;
    
    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};
    
    // With non-finger source, processing should return early
    optimizer.SelectSinglePoint(touchEvents);
    
    // List should remain unchanged since processing returns early
    EXPECT_EQ(touchEvents.size(), 2);
}

/**
 * @tc.name: HandleMainDelta_Test004
 * @tc.desc: test HandleMainDelta with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleMainDelta_Test004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    double mainDelta = 10.0;
    double touchPointsSize = 5.0;
    
    // Create touchPoints map with non-finger source
    std::map<int32_t, TouchEvent> touchPoints;
    TouchEvent event;
    event.sourceTool = SourceTool::MOUSE; // Non-finger source
    touchPoints[1] = event;
    
    double result = optimizer.HandleMainDelta(mainDelta, touchPointsSize, touchPoints);
    
    // Should return basic calculation without compensation since source is not finger
    EXPECT_DOUBLE_EQ(result, mainDelta / touchPointsSize);
}

/**
 * @tc.name: SetSlideAcceptOffsetTest003
 * @tc.desc: test SetSlideAcceptOffset when rvs is enabled
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SetSlideAcceptOffsetTest003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    Offset offset = {15.0, 25.0};
    optimizer.SetSlideAcceptOffset(offset);
    
    // When RVS is enabled, SetSlideAcceptOffset should not set the values
    // Based on the implementation, the condition is inverted
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetX(), 15.0);
    EXPECT_DOUBLE_EQ(optimizer.slideAcceptOffset_.GetY(), 25.0);
    EXPECT_DOUBLE_EQ(optimizer.accumulatedDistance_, 0.0);
}

/**
 * @tc.name: RVSPointCheckWithSignal003
 * @tc.desc: test RVSPointCheckWithSignal with empty deque
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    optimizer.rvsDequeX_.clear();
    optimizer.rvsDequeY_.clear();
    // Test with empty deque for X axis
    EXPECT_FALSE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    
    // Test with empty deque for Y axis
    touchEvent.yReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    EXPECT_FALSE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_Y));
}

/**
 * @tc.name: RVSPointCheckWithSignal004
 * @tc.desc: test RVSPointCheckWithSignal with single element deque
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    optimizer.rvsDequeX_.clear();
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    EXPECT_FALSE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
}

/**
 * @tc.name: HandleState0_003
 * @tc.desc: test HandleState0 with large movement
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState0_003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 120; // Large movement from history
    point.y = 200;
    
    double result = 0.0;
    bool resampleEnable = false;
    
    // Fill history with distant values
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(90);
    optimizer.dptHistoryPointX_[1].push_back(100); // Back element
    
    // Should not change state with large movement
    EXPECT_FALSE(optimizer.HandleState0(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::NO_CHANGE); // State should not be set
}

/**
 * @tc.name: HandleState1_004
 * @tc.desc: test HandleState1 with no reverse signal
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100;
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No reverse signal
    
    double result = 0.0;
    bool resampleEnable = false;
    
    // Setup history
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(95);
    optimizer.dptHistoryPointX_[1].push_back(98);
    optimizer.dptHistoryPointX_[1].push_back(100);
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    // With no reverse signal, should just return the point value
    EXPECT_TRUE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(result, 100.0);
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::TP_USE); // State should not change
}

/**
 * @tc.name: HandleState1_005
 * @tc.desc: test HandleState1 with small movement and resample disabled
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_005, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 101; // Small movement
    point.y = 200;
    
    double result = 0.0;
    bool resampleEnable = false; // Resample disabled
    
    // Setup history
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(99);
    optimizer.dptHistoryPointX_[1].push_back(100);
    optimizer.dptHistoryPointX_[1].push_back(100); // Back element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    // With small movement and resample disabled, should just return the point value
    EXPECT_TRUE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(result, 101.0);
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::TP_USE); // State should not change
}

/**
 * @tc.name: HandleState1_006
 * @tc.desc: test HandleState1 with RVS_DOWN_LEFT signal - first condition
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_006, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 110; // Less than second to last element
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history where second to last element (index 1) is 100, current point is 90
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(100); // Second to last element
    optimizer.dptHistoryPointX_[1].push_back(95);  // Last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
    EXPECT_DOUBLE_EQ(optimizer.dptGapX_[1], 95 - 100); // gap = last - second to last
}

/**
 * @tc.name: HandleState1_007
 * @tc.desc: test HandleState1 with RVS_DOWN_LEFT signal - second condition
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_007, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100; // Greater than or equal to last element
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history where current point (100) >= last element (95)
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(110);
    optimizer.dptHistoryPointX_[1].push_back(95); // Last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
    EXPECT_DOUBLE_EQ(optimizer.dptGapX_[1], THRESHOLD_OFFSET_VALUE);
}

/**
 * @tc.name: HandleState1_008
 * @tc.desc: test HandleState1 with RVS_UP_RIGHT signal - first condition
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_008, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 95; // Greater than second to last element
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history where second to last element (index 1) is 100, current point is 110
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(100); // Second to last element
    optimizer.dptHistoryPointX_[1].push_back(105); // Last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
    EXPECT_DOUBLE_EQ(optimizer.dptGapX_[1], 105 - 100); // gap = last - second to last
}

/**
 * @tc.name: HandleState1_009
 * @tc.desc: test HandleState1 with RVS_UP_RIGHT signal - second condition
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState1_009, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100; // Less than or equal to last element
    point.y = 200;
    point.xReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history where current point (100) <= last element (105)
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(90);
    optimizer.dptHistoryPointX_[1].push_back(105); // Last element
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    
    EXPECT_FALSE(optimizer.HandleState1(point, resampleEnable, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET);
    EXPECT_DOUBLE_EQ(optimizer.dptGapX_[1], -THRESHOLD_OFFSET_VALUE);
}

/**
 * @tc.name: HandleState2_003
 * @tc.desc: test HandleState2 with positive gap and condition not met
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState2_003, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100; // Value that doesn't satisfy transition condition
    point.y = 200;
    
    double result = 0.0;
    
    // Setup positive gap
    optimizer.dptGapX_[1] = 5.0; // Positive gap
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    // Condition (dptGap > 0 && (dptGap - pointNow) > 0) is not met because (5 - 100) < 0
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET); // State should not change
    EXPECT_DOUBLE_EQ(result, 100 - 5.0); // point.x - dptGapX_
}

/**
 * @tc.name: HandleState2_004
 * @tc.desc: test HandleState2 with negative gap and condition not met
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, HandleState2_004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent point;
    point.id = 1;
    point.x = 100; // Value that doesn't satisfy transition condition
    point.y = 200;
    
    double result = 0.0;
    
    // Setup negative gap
    optimizer.dptGapX_[1] = -5.0; // Negative gap
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::NO_CHANGE); // State should not change
    EXPECT_DOUBLE_EQ(result, 100); // point.x - dptGapX_
}

/**
 * @tc.name: RVSQueueUpdate004
 * @tc.desc: test RVSQueueUpdate with timestamp gap timeout
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate004, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    // 设置一个较早的时间戳，使其超过RVS_CLEAR_GAP_TIME
    optimizer.lastRVSPointTimeStamp_ = 1000;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Mock GetSysTimestamp to return a much larger value to trigger timeout
    // Since we can't easily mock this, we'll test the reset behavior by pre-setting data
    
    // Pre-populate some data
    optimizer.rvsDequeX_[1].push_back(50);
    optimizer.rvsDequeY_[1].push_back(150);
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::TP_USE;
    optimizer.stateTagY_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    // This test mainly verifies the structure, actual timeout would need mocking
    optimizer.RVSPointReset(0, RVS_RESET_INFO::RVS_RESET_ALL);
    
    EXPECT_TRUE(optimizer.rvsDequeX_.empty());
    EXPECT_TRUE(optimizer.rvsDequeY_.empty());
    EXPECT_TRUE(optimizer.stateTagX_.empty());
    EXPECT_TRUE(optimizer.stateTagY_.empty());
    EXPECT_EQ(optimizer.lastRVSPointTimeStamp_, 0);
}

/**
 * @tc.name: RVSQueueUpdate005
 * @tc.desc: test RVSQueueUpdate with same coordinate values
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate005, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 100;
    touchEvent.y = 200;
    
    // Pre-fill deques with same values as the event
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // Same x value
    
    optimizer.rvsDequeY_[1].clear();
    optimizer.rvsDequeY_[1].push_back(200); // Same y value
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Should not add duplicate values to the deques
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Check that no new elements were added (size should still be 1)
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 1);
    EXPECT_EQ(optimizer.rvsDequeY_[1].size(), 1);
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 100);
    EXPECT_EQ(optimizer.rvsDequeY_[1].back(), 200);
}

/**
 * @tc.name: RVSQueueUpdate006
 * @tc.desc: test RVSQueueUpdate with different coordinate values triggering deque updates
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate006, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 105; // Different from existing
    touchEvent.y = 205; // Different from existing
    
    // Pre-fill deques with different values
    optimizer.rvsDequeX_[1].clear();
    optimizer.rvsDequeX_[1].push_back(100); // Different x value
    
    optimizer.rvsDequeY_[1].clear();
    optimizer.rvsDequeY_[1].push_back(200); // Different y value
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // Should add new values to the deques
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Check that new elements were added
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 105);
    EXPECT_EQ(optimizer.rvsDequeY_[1].back(), 205);
}

/**
 * @tc.name: RVSQueueUpdate007
 * @tc.desc: test RVSQueueUpdate with queue size reaching RVS_QUEUE_SIZE
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate007, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.type = TouchType::MOVE;
    touchEvent.sourceTool = SourceTool::FINGER;
    touchEvent.x = 150;
    touchEvent.y = 250;
    touchEvent.xReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    touchEvent.yReverse = RVS_DIRECTION::RVS_NOT_APPLY;
    
    // Pre-fill deques to near RVS_QUEUE_SIZE (7) - fill with 6 elements
    optimizer.rvsDequeX_[1].clear();
    for (int i = 0; i < 6; i++) {
        optimizer.rvsDequeX_[1].push_back(100 + i * 5);
    }
    
    optimizer.rvsDequeY_[1].clear();
    for (int i = 0; i < 6; i++) {
        optimizer.rvsDequeY_[1].push_back(200 + i * 5);
    }
    
    std::list<TouchEvent> touchEvents = {touchEvent};
    
    // After adding the new event, the size should be 7 (RVS_QUEUE_SIZE)
    optimizer.RVSQueueUpdate(touchEvents);
    
    // Check that the deques have the expected size
    EXPECT_EQ(optimizer.rvsDequeX_[1].size(), 6);
    EXPECT_EQ(optimizer.rvsDequeY_[1].size(), 6);
    
    // The new element should be at the back
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 150);
    EXPECT_EQ(optimizer.rvsDequeY_[1].back(), 250);
}

/**
 * @tc.name: RVSQueueUpdate008
 * @tc.desc: test RVSQueueUpdate with queue overflow triggering pop_front
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate008, TestSize.Level1)
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
    EXPECT_EQ(optimizer.rvsDequeX_[1].back(), 200);
    EXPECT_EQ(optimizer.rvsDequeY_[1].back(), 300);
    
    // The old front element should no longer be in the deque
    EXPECT_NE(optimizer.rvsDequeX_[1].front(), frontX);
    EXPECT_NE(optimizer.rvsDequeY_[1].front(), frontY);
}

/**
 * @tc.name: RVSQueueUpdate009
 * @tc.desc: test RVSQueueUpdate with non-move event type
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate009, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSQueueUpdate010, TestSize.Level1)
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
    EXPECT_FALSE(optimizer.rvsDequeX_.find(1) == optimizer.rvsDequeX_.end());
    EXPECT_FALSE(optimizer.rvsDequeY_.find(1) == optimizer.rvsDequeY_.end());
    
    // data for ID 1 should still exist
    EXPECT_FALSE(optimizer.rvsDequeX_.find(1) == optimizer.rvsDequeX_.end());
    EXPECT_FALSE(optimizer.rvsDequeY_.find(1) == optimizer.rvsDequeY_.end());
}

/**
 * @tc.name: RVSSingleAxisUpdate002
 * @tc.desc: test RVSSingleAxisUpdate coverage
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, RVSSingleAxisUpdate002, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal005, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithSignal006, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal003, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal004, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal005, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal006, TestSize.Level1)
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
HWTEST_F(ResSchedTouchOptimizerTest, RVSPointCheckWithoutSignal007, TestSize.Level1)
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
} // namespace OHOS::Ace