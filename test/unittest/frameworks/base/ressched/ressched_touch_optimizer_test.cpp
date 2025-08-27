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
} // namespace OHOS::Ace