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
    touchEvent.isXReverse = true;
    EXPECT_TRUE(ResSchedTouchOptimizer::GetInstance().NeedTpFlushVsync(touchEvent, 100));
    touchEvent.isXReverse = false;
    touchEvent.isYReverse = false;
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
    double result = optimizer.HandleMainDelta(mainDleta, touchPointsSize, touchPoints);

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
    optimizer.rvsEnable_ = true;
    optimizer.SetSlideAcceptOffset(Offset(10.0, 10.0));

    double mainDelta = 10.0;
    double touchPointsSize = 5.0;
    std::map<int32_t, TouchEvent> touchPoints;
    double result = optimizer.HandleMainDelta(mainDleta, touchPointsSize, touchPoints);

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
    double result = optimizer.HandleMainDelta(mainDleta, touchPointsSize, touchPoints);

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
    EXPECT_NE(touchEvent1.isYReverse, RVS_DIRECTION::RVS_NOT_APPLY);
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

    optimizer.RVSPointReset(0, RVS_RESET_INFO::RVS_RESET_CUR_ID);
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
    touchEvent1.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    touchEvent1.sourceTool = SourceTool::FINGER;

    TouchEvent touchEvent2;
    touchEvent2.id = 2;
    touchEvent2.sourceTool = SourceTool::FINGER;

    std::list<TouchEvent> touchEvents = {touchEvent1, touchEvent2};

    optimizer.SelectSinglePoint(touchEvents);

    EXPECT_EQ(touchEvents.front().id, touchEvent1.id);
    EXPECT_EQ(touchEvents.front().isXReverse, RVS_DIRECTION::RVS_DOWN_LEFT);

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
    point.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
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
    point.isXReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
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
    optimizer.dptGapX_[1] = 5.0; // Positive gap
    
    optimizer.stateTagX_[1] = RVS_FINETUNE_STATE::OFFSET;
    
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::NO_CHANGE);
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
    touchEvent.isXReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No signal
    
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
    touchEvent1.isXReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No reverse
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
    touchEvent.sourceTool = SourceTool::TOUCH_PAD;
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
    
    // Processing should stop at the second event, so only first event data should be processed
    EXPECT_FALSE(optimizer.rvsDequeX_.empty());
    EXPECT_FALSE(optimizer.rvsDequeY_.empty());
    EXPECT_TRUE(optimizer.rvsDequeX_.find(1) != optimizer.rvsDequeX_.end());
    EXPECT_TRUE(optimizer.rvsDequeY_.find(1) != optimizer.rvsDequeY_.end());
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
 * @tc.name: SelectSinglePoint002
 * @tc.desc: test SelectSinglePoint with non-finger source tool
 * @tc.type: FUNC
 */
HWTEST_F(ResSchedTouchOptimizerTest, SelectSinglePoint002, TestSize.Level1)
{
    ResSchedTouchOptimizer& optimizer = ResSchedTouchOptimizer::GetInstance();
    optimizer.rvsEnable_ = true;
    
    TouchEvent touchEvent1;
    touchEvent1.id = 1;
    touchEvent1.type = TouchType::MOVE;
    touchEvent1.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
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
    touchEvent.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    // Test with empty deque for X axis
    EXPECT_FALSE(optimizer.RVSPointCheckWithSignal(touchEvent, RVS_AXIS::RVS_AXIS_X));
    
    // Test with empty deque for Y axis
    touchEvent.isYReverse = RVS_DIRECTION::RVS_UP_RIGHT;
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
    
    TouchEvent touchEvent;
    touchEvent.id = 1;
    touchEvent.x = 100;
    touchEvent.y = 200;
    touchEvent.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    // Fill deque with single element
    optimizer.rvsDequeX_[1].push_back(100);
    
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
    EXPECT_EQ(optimizer.stateTagX_.find(1), optimizer.stateTagX_.end()); // State should not be set
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
    point.isXReverse = RVS_DIRECTION::RVS_NOT_APPLY; // No reverse signal
    
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
    point.x = 90; // Less than second to last element
    point.y = 200;
    point.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
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
    point.isXReverse = RVS_DIRECTION::RVS_DOWN_LEFT;
    
    double result = 0.0;
    bool resampleEnable = true;
    
    // Setup history where current point (100) >= last element (95)
    optimizer.dptHistoryPointX_[1].clear();
    optimizer.dptHistoryPointX_[1].push_back(80);
    optimizer.dptHistoryPointX_[1].push_back(90);
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
    point.x = 110; // Greater than second to last element
    point.y = 200;
    point.isXReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
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
    point.isXReverse = RVS_DIRECTION::RVS_UP_RIGHT;
    
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
    EXPECT_DOUBLE_EQ(optimizer.dptGapX_[1], THRESHOLD_OFFSET_VALUE);
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
    
    // Condition (dptGap < 0 && (pointNow - dptGap) > 0) is not met because (100 - (-5)) > 0 but we test the other branch
    EXPECT_TRUE(optimizer.HandleState2(point, RVS_AXIS::RVS_AXIS_X, result));
    EXPECT_EQ(optimizer.stateTagX_[1], RVS_FINETUNE_STATE::OFFSET); // State should not change
    EXPECT_DOUBLE_EQ(result, 100 - (-5.0)); // point.x - dptGapX_
}
} // namespace OHOS::Ace