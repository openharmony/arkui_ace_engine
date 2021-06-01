/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <gtest/gtest.h>

#include "core/gestures/click_recognizer.h"
#include "core/gestures/drag_recognizer.h"
#include "core/gestures/gesture_referee.h"
#include "core/gestures/long_press_recognizer.h"
#include "core/gestures/raw_recognizer.h"
#include "core/gestures/velocity_tracker.h"
#include "core/pipeline/pipeline_context.h"

using namespace testing::ext;

namespace OHOS::Ace {
namespace {

constexpr double LOCATION_X = 200.0;
constexpr double LOCATION_Y = 400.0;
constexpr double LOCATION_STATIC = 0.0;
constexpr int32_t TIME_MILLISECOND = 1000;
constexpr int32_t TIME_COUNTS = 500;

constexpr double MAX_THRESHOLD = 20.0;

const std::string TOUCH_DOWN_TYPE = "onTouchDown";
const std::string TOUCH_UP_TYPE = "onTouchUp";
const std::string TOUCH_MOVE_TYPE = "onTouchMove";
const std::string TOUCH_CANCEL_TYPE = "onTouchCancel";

} // namespace

class TouchEventResult {
public:
    explicit TouchEventResult(const std::string& type) : touchEventInfo_(type) {};
    ~TouchEventResult() = default;

    const TouchEventInfo& GetTouchEventInfo() const
    {
        return touchEventInfo_;
    }

    void SetTouchEventInfo(const TouchEventInfo& touchEventInfo)
    {
        touchEventInfo_ = touchEventInfo;
    }

private:
    TouchEventInfo touchEventInfo_;
};

class LongPressEventResult {
public:
    explicit LongPressEventResult() : longPressInfo_(0) {};
    ~LongPressEventResult() = default;

    void SetLongPress(bool longPress)
    {
        longPress_ = longPress;
    }

    bool GetLongPress() const
    {
        return longPress_;
    }

    void SetLongPressInfo(const LongPressInfo& longPressInfo)
    {
        longPressInfo_ = longPressInfo;
    }

    const LongPressInfo& GetLongPressInfo()
    {
        return longPressInfo_;
    }

private:
    bool longPress_ = false;
    LongPressInfo longPressInfo_;
};

class ClickEventResult {
public:
    explicit ClickEventResult() : clickInfo_(0) {};
    ~ClickEventResult() = default;

    const ClickInfo& GetClickInfo() const
    {
        return clickInfo_;
    }

    void SetClickInfo(const ClickInfo& clickInfo)
    {
        clickInfo_ = clickInfo;
    }

private:
    ClickInfo clickInfo_;
};

class GestureRefereeResult {
public:
    GestureRefereeResult() : gestureName_("") {};
    ~GestureRefereeResult() = default;

    void SetGestureName(const std::string& gestureName)
    {
        gestureName_ = gestureName;
    }

    const std::string& GetGestureName() const
    {
        return gestureName_;
    }

private:
    std::string gestureName_;
};

class DragEventResult {
public:
    DragEventResult() : dragStartInfo_(0), dragUpdateInfo_(0), dragEndInfo_(0) {};
    ~DragEventResult() = default;

    void SetDragStart(const DragStartInfo& info)
    {
        dragStartInfo_ = info;
    }

    void SetDragUpdate(const DragUpdateInfo& info)
    {
        dragUpdateInfo_ = info;
    }

    void SetDragEnd(const DragEndInfo& info)
    {
        dragEndInfo_ = info;
    }

    const DragStartInfo& GetDragStart() const
    {
        return dragStartInfo_;
    }

    const DragUpdateInfo& GetDragUpdate() const
    {
        return dragUpdateInfo_;
    }

    const DragEndInfo& GetDragEnd() const
    {
        return dragEndInfo_;
    }

    void SetDragCancel(bool dragCancel)
    {
        dragCancel_ = dragCancel;
    }

    bool GetDragCancel() const
    {
        return dragCancel_;
    }

private:
    DragStartInfo dragStartInfo_;
    DragUpdateInfo dragUpdateInfo_;
    DragEndInfo dragEndInfo_;
    bool dragCancel_ = false;
};

class GesturesTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void GesturesTest::SetUpTestCase() {}

void GesturesTest::TearDownTestCase() {}

void GesturesTest::SetUp() {}

void GesturesTest::TearDown() {}

/**
 * @tc.name: RawRecognizer001
 * @tc.desc: Verify the raw recognizer recognizes corresponding touch down event.
 * @tc.type: FUNC
 * @tc.require: AR000DAPU9
 * @tc.author: yanshuifeng
 */
HWTEST_F(GesturesTest, RawRecognizer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create raw recognizer and set touch down event callback.
     */
    TouchEventResult onTouchDown(TOUCH_DOWN_TYPE);
    auto rawRecognizer = AceType::MakeRefPtr<RawRecognizer>();
    rawRecognizer->SetOnTouchDown([&onTouchDown](const TouchEventInfo& info) { onTouchDown.SetTouchEventInfo(info); });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. receive touch down callback and touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    rawRecognizer->HandleEvent(point);
    ASSERT_FALSE(onTouchDown.GetTouchEventInfo().GetTouches().empty());
    ASSERT_TRUE(onTouchDown.GetTouchEventInfo().GetChangedTouches().empty());

    /**
     * @tc.steps: step3. check the touch location info.
     * @tc.expected: step3. the touch location info is right.
     */
    auto& locationInfo = onTouchDown.GetTouchEventInfo().GetTouches().front();
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetX(), LOCATION_X);
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetY(), LOCATION_Y);
}

/**
 * @tc.name: RawRecognizer002
 * @tc.desc: Verify the raw recognizer recognizes corresponding touch up event.
 * @tc.type: FUNC
 * @tc.require: AR000DAPU9
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, RawRecognizer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create raw recognizer and set touch up event callback.
     */
    TouchEventResult onTouchUp(TOUCH_UP_TYPE);
    auto rawRecognizer = AceType::MakeRefPtr<RawRecognizer>();
    rawRecognizer->SetOnTouchUp([&onTouchUp](const TouchEventInfo& info) { onTouchUp.SetTouchEventInfo(info); });

    /**
     * @tc.steps: step2. send touch up event.
     * @tc.expected: step2. receive touch up callback and touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::UP, .time = std::chrono::high_resolution_clock::now()
    };
    rawRecognizer->HandleEvent(point);
    ASSERT_FALSE(onTouchUp.GetTouchEventInfo().GetTouches().empty());
    ASSERT_TRUE(onTouchUp.GetTouchEventInfo().GetChangedTouches().empty());

    /**
     * @tc.steps: step3. check the touch location info.
     * @tc.expected: step3. the touch location info is right.
     */
    auto& locationInfo = onTouchUp.GetTouchEventInfo().GetTouches().front();
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetX(), LOCATION_X);
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetY(), LOCATION_Y);
}

/**
 * @tc.name: RawRecognizer003
 * @tc.desc: Verify the raw recognizer recognizes corresponding touch cancel event.
 * @tc.type: FUNC
 * @tc.require: AR000DAPU9
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, RawRecognizer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create raw recognizer and set touch cancel event callback.
     */
    TouchEventResult onTouchCancel(TOUCH_CANCEL_TYPE);
    auto rawRecognizer = AceType::MakeRefPtr<RawRecognizer>();
    rawRecognizer->SetOnTouchCancel(
        [&onTouchCancel](const TouchEventInfo& info) { onTouchCancel.SetTouchEventInfo(info); });

    /**
     * @tc.steps: step2. send touch cancel event.
     * @tc.expected: step2. receive touch cancel callback and touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::CANCEL, .time = std::chrono::high_resolution_clock::now()
    };
    rawRecognizer->HandleEvent(point);
    ASSERT_FALSE(onTouchCancel.GetTouchEventInfo().GetTouches().empty());
    ASSERT_TRUE(onTouchCancel.GetTouchEventInfo().GetChangedTouches().empty());

    /**
     * @tc.steps: step3. check the touch location info.
     * @tc.expected: step3. the touch location info is right.
     */
    auto& locationInfo = onTouchCancel.GetTouchEventInfo().GetTouches().front();
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetX(), LOCATION_X);
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetY(), LOCATION_Y);
}

/**
 * @tc.name: RawRecognizer004
 * @tc.desc: Verify the raw recognizer recognizes corresponding touch move event.
 * @tc.type: FUNC
 * @tc.require: AR000DAPU9
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, RawRecognizer004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create raw recognizer and set touch move event callback.
     */
    TouchEventResult onTouchMove(TOUCH_MOVE_TYPE);
    auto rawRecognizer = AceType::MakeRefPtr<RawRecognizer>();
    rawRecognizer->SetOnTouchMove([&onTouchMove](const TouchEventInfo& info) { onTouchMove.SetTouchEventInfo(info); });

    /**
     * @tc.steps: step2. send touch move event.
     * @tc.expected: step2. receive touch move callback and touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };
    rawRecognizer->HandleEvent(point);
    ASSERT_FALSE(onTouchMove.GetTouchEventInfo().GetTouches().empty());
    ASSERT_TRUE(onTouchMove.GetTouchEventInfo().GetChangedTouches().empty());

    /**
     * @tc.steps: step3. check the touch location info.
     * @tc.expected: step3. the touch location info is right.
     */
    auto& locationInfo = onTouchMove.GetTouchEventInfo().GetTouches().front();
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetX(), LOCATION_X);
    ASSERT_EQ(locationInfo.GetGlobalLocation().GetY(), LOCATION_Y);
}

/**
 * @tc.name: VelocityTracker001
 * @tc.desc: Verify the velocity vracker recognizes velocity vracker.
 * @tc.type: FUNC
 * @tc.require: AR000DAPUA
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, VelocityTracker001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create velocity vracker.
     */
    VelocityTracker onVelocityTracker(Axis::VERTICAL);

    /**
     * @tc.steps: step2. send start point.
     * @tc.expected: step2. receive first point to calculate the velocity.
     */
    TouchPoint pointFirst {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };
    onVelocityTracker.UpdateTouchPoint(pointFirst);
    ASSERT_EQ(onVelocityTracker.GetMainAxisPos(), LOCATION_Y);
    ASSERT_EQ(onVelocityTracker.GetMainAxisDeltaPos(), LOCATION_STATIC);

    /**
     * @tc.steps: step3. send end point.
     * @tc.expected: step3. receive first point to calculate the velocity.
     */
    usleep(TIME_MILLISECOND);
    TouchPoint pointSecond {
        .x = LOCATION_X, .y = 2 * LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };

    onVelocityTracker.UpdateTouchPoint(pointSecond);
    ASSERT_EQ(onVelocityTracker.GetMainAxisPos(), 2 * LOCATION_Y);
    ASSERT_EQ(onVelocityTracker.GetMainAxisDeltaPos(), LOCATION_Y);

    // nanoseconds duration to seconds.
    const std::chrono::duration<double> duration = pointSecond.time - pointFirst.time;
    if (!NearZero(duration.count())) {
        Velocity velocity((pointSecond.GetOffset() - pointFirst.GetOffset()) / duration.count());
        ASSERT_EQ(onVelocityTracker.GetMainAxisVelocity(), velocity.GetVelocityY());
    }
}

/**
 * @tc.name: VelocityTracker002
 * @tc.desc: Verify the velocity tracker recognizes horizontal velocity.
 * @tc.type: FUNC
 * @tc.require: AR000DAPUA
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, VelocityTracker002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create horizontal velocity tracker.
     */
    VelocityTracker onVelocityTracker(Axis::HORIZONTAL);

    /**
     * @tc.steps: step2. send start point.
     * @tc.expected: step2. receive first point to calculate the velocity.
     */
    TouchPoint pointFirst {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };
    onVelocityTracker.UpdateTouchPoint(pointFirst);
    ASSERT_EQ(onVelocityTracker.GetMainAxisPos(), LOCATION_X);
    ASSERT_EQ(onVelocityTracker.GetMainAxisDeltaPos(), LOCATION_STATIC);

    /**
     * @tc.steps: step3. send end point.
     * @tc.expected: step3. receive first point to calculate the velocity.
     */
    usleep(TIME_MILLISECOND);
    TouchPoint pointSecond {
        .x = 2 * LOCATION_X, .y = LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };

    onVelocityTracker.UpdateTouchPoint(pointSecond);
    ASSERT_EQ(onVelocityTracker.GetMainAxisPos(), 2 * LOCATION_X);
    ASSERT_EQ(onVelocityTracker.GetMainAxisDeltaPos(), LOCATION_X);

    // nanoseconds duration to seconds.
    const std::chrono::duration<double> duration = pointSecond.time - pointFirst.time;
    if (!NearZero(duration.count())) {
        Velocity velocity((pointSecond.GetOffset() - pointFirst.GetOffset()) / duration.count());
        ASSERT_EQ(onVelocityTracker.GetMainAxisVelocity(), velocity.GetVelocityX());
    }
}

/**
 * @tc.name: VelocityTracker003
 * @tc.desc: Verify the velocity tracker recognizes free velocity.
 * @tc.type: FUNC
 * @tc.require: AR000DAPUA
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, VelocityTracker003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create free velocity tracker.
     */
    VelocityTracker velTracker(Axis::FREE);

    /**
     * @tc.steps: step2. send start point.
     * @tc.expected: step2. receive first point to calculate the velocity.
     */
    TouchPoint pointFirst {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::MOVE, .time = std::chrono::high_resolution_clock::now()
    };
    velTracker.UpdateTouchPoint(pointFirst);
    ASSERT_EQ(velTracker.GetMainAxisPos(), pointFirst.GetOffset().GetDistance());
    ASSERT_EQ(velTracker.GetMainAxisDeltaPos(), LOCATION_STATIC);

    /**
     * @tc.steps: step3. send end point.
     * @tc.expected: step3. receive first point to calculate the velocity.
     */
    usleep(TIME_MILLISECOND);
    TouchPoint pointSecond { .x = 2 * LOCATION_X,
        .y = 2 * LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };

    velTracker.UpdateTouchPoint(pointSecond);
    ASSERT_EQ(velTracker.GetMainAxisPos(), pointSecond.GetOffset().GetDistance());
    ASSERT_EQ(velTracker.GetMainAxisDeltaPos(), (pointSecond.GetOffset() - pointFirst.GetOffset()).GetDistance());

    // nanoseconds duration to seconds.
    const std::chrono::duration<double> duration = pointSecond.time - pointFirst.time;
    if (!NearZero(duration.count())) {
        Velocity velocity((pointSecond.GetOffset() - pointFirst.GetOffset()) / duration.count());
        ASSERT_EQ(velTracker.GetMainAxisVelocity(), velocity.GetVelocityValue());
    }
}

/**
 * @tc.name: LongPressRecognizer001
 * @tc.desc: Verify the long press recognizer recognizes corresponding long press event.
 * @tc.type: FUNC
 * @tc.require: AR000DB0UK
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, LongPressRecognizer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create long press recognizer and set long press event callback.
     */
    LongPressEventResult onLongPress;
    WeakPtr<PipelineContext> context;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(context);
    longPressRecognizer->SetOnLongPress([&onLongPress](const LongPressInfo& info) {
        onLongPress.SetLongPress(true);
        onLongPress.SetLongPressInfo(info);
    });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step3. end touch up event. check the touch location info.
     * @tc.expected: step3. receive touch long press callback and the touch location info is right.
     */
    point.type = TouchType::UP;
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());
}

/**
 * @tc.name: LongPressRecognizer002
 * @tc.desc: Verify the long press recognizer recognizes corresponding long press event.
 * @tc.type: FUNC
 * @tc.require: AR000DB0UK
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, LongPressRecognizer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create long press recognizer and set long press event callback.
     */
    LongPressEventResult onLongPress;
    WeakPtr<PipelineContext> context;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(context);
    longPressRecognizer->SetOnLongPress([&onLongPress](const LongPressInfo& info) {
        onLongPress.SetLongPress(true);
        onLongPress.SetLongPressInfo(info);
    });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step3. end touch move event. move range less than max threshold.check the touch location info.
     * @tc.expected: step3. check the long press statusis right.
     */
    point.type = TouchType::MOVE;
    point.x += (MAX_THRESHOLD - 1);

    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step4. end touch move event. check the touch location info.
     * @tc.expected: step4. receive touch long press callback and check the long press status is right.
     */
    point.type = TouchType::UP;
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());
}

/**
 * @tc.name: LongPressRecognizer003
 * @tc.desc: Verify the long press recognizer recognizes corresponding long press event.
 * @tc.type: FUNC
 * @tc.require: AR000DB0UK
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, LongPressRecognizer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create long press recognizer and set long press event callback.
     */
    LongPressEventResult onLongPress;
    WeakPtr<PipelineContext> context;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(context);

    longPressRecognizer->SetOnLongPress([&onLongPress](const LongPressInfo& info) {
        onLongPress.SetLongPress(true);
        onLongPress.SetLongPressInfo(info);
    });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step3. end touch move event.move range more than max threshold. check the touch location info.
     * @tc.expected: step3. check the long press statusis right.
     */
    point.type = TouchType::MOVE;
    point.x += (MAX_THRESHOLD + 1);

    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step4. end touch move event. check the touch location info.
     * @tc.expected: step4. receive touch long press callback and check the long press status is right.
     */
    point.type = TouchType::UP;

    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());
}

/**
 * @tc.name: LongPressRecognizer004
 * @tc.desc: Verify the long press recognizer recognizes corresponding touch long press.
 * @tc.type: FUNC
 * @tc.require: AR000DB0UK
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, LongPressRecognizer004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create long press recognizer and set long press event callback.
     */
    LongPressEventResult onLongPress;
    WeakPtr<PipelineContext> context;
    auto longPressRecognizer = AceType::MakeRefPtr<LongPressRecognizer>(context);

    longPressRecognizer->SetOnLongPress([&onLongPress](const LongPressInfo& info) {
        onLongPress.SetLongPress(true);
        onLongPress.SetLongPressInfo(info);
    });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. touch point result is right.
     */
    TouchPoint point {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());

    /**
     * @tc.steps: step3. time wait longger than the max times(500ms).
     * @tc.expected: step3. check the long press statusis right.
     */
    usleep((TIME_COUNTS + 1) * TIME_MILLISECOND);

    /**
     * @tc.steps: step4. end touch up event. check the touch location info.
     * @tc.expected: step4. receive touch long press callback and check the long press status is right.
     */
    point.type = TouchType::UP;
    longPressRecognizer->HandleEvent(point);
    ASSERT_FALSE(onLongPress.GetLongPress());
}

/**
 * @tc.name: ClickRecognizer001
 * @tc.desc: Verify the click recognizer recognizes corresponding touch down event and up event.
 * @tc.type: FUNC
 * @tc.require: AR000DAIGG
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, ClickRecognizer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizer and set touch click event callback.
     */
    ClickEventResult onClick;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetOnClick([&onClick](const ClickInfo& info) { onClick.SetClickInfo(info); });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. receive touch down callback and touch point result is right.
     */
    TouchPoint point { .id = 2,
        .x = LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    clickRecognizer->HandleEvent(point);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());

    /**
     * @tc.steps: step3. check the touch up event.
     * @tc.expected: step3. the touch location info is right.
     */
    point.type = TouchType::UP;
    clickRecognizer->HandleEvent(point);
    ASSERT_FALSE(onClick.GetClickInfo().GetGlobalLocation().IsZero());
    ASSERT_EQ(onClick.GetClickInfo().GetGlobalLocation(), point.GetOffset());
    ASSERT_EQ(onClick.GetClickInfo().GetFingerId(), point.id);
}

/**
 * @tc.name: ClickRecognizer002
 * @tc.desc: Verify the click recognizer recognizes corresponding touch down event and move and up  event. move not far
 * than MAX_THRESHOLD
 * @tc.type: FUNC
 * @tc.require: AR000DAIGG
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, ClickRecognizer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizer and set touch click event callback.
     */
    ClickEventResult onClick;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetOnClick([&onClick](const ClickInfo& info) { onClick.SetClickInfo(info); });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. receive touch down callback and touch point result is
     * right.
     */
    TouchPoint pointStart {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    clickRecognizer->HandleEvent(pointStart);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());

    /**
     * @tc.steps: step3. send the touch move event. move not far than max threshold
     * @tc.expected: step3. the touch location info is right.
     */
    TouchPoint pointEnd { .x = LOCATION_X + MAX_THRESHOLD,
        .y = LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };
    clickRecognizer->HandleEvent(pointEnd);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());

    /**
     * @tc.steps: step4. send the touch up event.
     * @tc.expected: step4. the touch location info is right.
     */
    pointEnd.type = TouchType::UP;
    clickRecognizer->HandleEvent(pointEnd);
    ASSERT_FALSE(onClick.GetClickInfo().GetGlobalLocation().IsZero());
    ASSERT_EQ(onClick.GetClickInfo().GetGlobalLocation(), pointStart.GetOffset());
}

/**
 * @tc.name: ClickRecognizer003
 * @tc.desc: Verify the click recognizer recognizes corresponding touch down event and move and up  event. move far than
 * MAX_THRESHOLD
 * @tc.type: FUNC
 * @tc.require: AR000DAIGG
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, ClickRecognizer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizer and set touch click event callback.
     */
    ClickEventResult onClick;
    auto clickRecognizer = AceType::MakeRefPtr<ClickRecognizer>();
    clickRecognizer->SetOnClick([&onClick](const ClickInfo& info) { onClick.SetClickInfo(info); });

    /**
     * @tc.steps: step2. send touch down event.
     * @tc.expected: step2. receive touch down callback and touch point result is right.
     */
    TouchPoint pointStart {
        .x = LOCATION_X, .y = LOCATION_Y, .type = TouchType::DOWN, .time = std::chrono::high_resolution_clock::now()
    };
    clickRecognizer->HandleEvent(pointStart);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());

    /**
     * @tc.steps: step3. send the touch move event. move far than max threshold
     * @tc.expected: step3. the touch location info is right.
     */
    TouchPoint pointEnd { .x = LOCATION_X + MAX_THRESHOLD + 0.1f,
        .y = LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };
    clickRecognizer->HandleEvent(pointEnd);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());

    /**
     * @tc.steps: step4. send the touch up event.
     * @tc.expected: step4. the touch location info is right.
     */
    pointEnd.type = TouchType::UP;
    clickRecognizer->HandleEvent(pointEnd);
    ASSERT_TRUE(onClick.GetClickInfo().GetGlobalLocation().IsZero());
}

/**
 * @tc.name: GestureReferee001
 * @tc.desc: Verify the gesture referee corresponding gesture recognizer's referee
 * @tc.type: FUNC
 * @tc.require: AR000DAIGF
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, GestureReferee001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture arbiter.
     */
    GestureRefereeResult refereeResult;
    auto clickRecognizerA = AceType::MakeRefPtr<ClickRecognizer>();
    auto clickRecognizerB = AceType::MakeRefPtr<ClickRecognizer>();
    auto clickRecognizerC = AceType::MakeRefPtr<ClickRecognizer>();

    clickRecognizerA->SetOnClick(
        [&refereeResult](const ClickInfo& info) { refereeResult.SetGestureName("clickRecognizerA"); });
    clickRecognizerB->SetOnClick(
        [&refereeResult](const ClickInfo& info) { refereeResult.SetGestureName("clickRecognizerB"); });
    clickRecognizerC->SetOnClick(
        [&refereeResult](const ClickInfo& info) { refereeResult.SetGestureName("clickRecognizerC"); });

    int32_t eventId = 2;
    GestureReferee::GetInstance().AddGestureRecognizer(eventId, clickRecognizerA);
    GestureReferee::GetInstance().AddGestureRecognizer(eventId, clickRecognizerB);
    GestureReferee::GetInstance().AddGestureRecognizer(eventId, clickRecognizerC);

    /**
     * @tc.steps: step2. send accept to gesture arbiter.
     * @tc.expected: step2. receive event callback and check result is right.
     */
    GestureReferee::GetInstance().Adjudicate(eventId, clickRecognizerC, GestureDisposal::ACCEPT);
    GestureReferee::GetInstance().Adjudicate(eventId, clickRecognizerB, GestureDisposal::ACCEPT);
    GestureReferee::GetInstance().Adjudicate(eventId, clickRecognizerA, GestureDisposal::ACCEPT);

    ASSERT_EQ(refereeResult.GetGestureName(), std::string("clickRecognizerC"));
}

/**
 * @tc.name: GestureReferee002
 * @tc.desc: Verify the gesture arbiter corresponding gesture recognizer's arbiter
 * @tc.type: FUNC
 * @tc.require: AR000DAIGF
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, GestureReferee002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture arbiter.
     */
    GestureRefereeResult refereeResult;
    auto clickRecognizerA = AceType::MakeRefPtr<ClickRecognizer>();

    clickRecognizerA->SetOnClick(
        [&refereeResult](const ClickInfo& info) { refereeResult.SetGestureName("clickRecognizerA"); });

    int32_t eventId = 0;
    GestureReferee::GetInstance().AddGestureRecognizer(++eventId, clickRecognizerA);

    /**
     * @tc.steps: step2. send accept to gesture arbiter.
     * @tc.expected: step2. receive event callback and check result is right.
     */
    GestureReferee::GetInstance().Adjudicate(eventId--, clickRecognizerA, GestureDisposal::REJECT);

    ASSERT_TRUE(refereeResult.GetGestureName().empty());
}

/**
 * @tc.name: DragRecognizer001
 * @tc.desc: verify the drag recognizer corresponding vertical drag event
 * @tc.type: FUNC
 * @tc.require: AR000DAIGH
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, DragRecognizer001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture referee.
     */
    DragEventResult onDrag;
    auto dragRecognizer = AceType::MakeRefPtr<DragRecognizer>(Axis::VERTICAL);

    dragRecognizer->SetOnDragStart([&onDrag](const DragStartInfo& info) { onDrag.SetDragStart(info); });
    dragRecognizer->SetOnDragUpdate([&onDrag](const DragUpdateInfo& info) { onDrag.SetDragUpdate(info); });
    dragRecognizer->SetOnDragEnd([&onDrag](const DragEndInfo& info) { onDrag.SetDragEnd(info); });

    /**
     * @tc.steps: step2. send down event and vertical move event.
     * @tc.expected: step2. receive event callback and result is right.
     */
    TouchPoint pointStart { .id = 2,
        .x = LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointStart);

    TouchPoint pointEnd { .id = 2,
        .x = LOCATION_X,
        .y = 2 * LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragStart().GetGlobalLocation(), pointStart.GetOffset());
    ASSERT_EQ(onDrag.GetDragStart().GetFingerId(), pointStart.id);
    ASSERT_EQ(onDrag.GetDragUpdate().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragUpdate().GetFingerId(), pointEnd.id);

    /**
     * @tc.steps: step3. send up event, check touch point result is right
     * @tc.expected: step3. touch point result is right.
     */
    pointEnd.type = TouchType::UP;
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragEnd().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragEnd().GetFingerId(), pointEnd.id);
}

/**
 * @tc.name: DragRecognizer002
 * @tc.desc: verify the drag recognizer corresponding horizontal drag event
 * @tc.type: FUNC
 * @tc.require: AR000DAIGH
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, DragRecognizer002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture referee.
     */
    DragEventResult onDrag;
    auto dragRecognizer = AceType::MakeRefPtr<DragRecognizer>(Axis::HORIZONTAL);

    dragRecognizer->SetOnDragStart([&onDrag](const DragStartInfo& info) { onDrag.SetDragStart(info); });
    dragRecognizer->SetOnDragUpdate([&onDrag](const DragUpdateInfo& info) { onDrag.SetDragUpdate(info); });
    dragRecognizer->SetOnDragEnd([&onDrag](const DragEndInfo& info) { onDrag.SetDragEnd(info); });

    /**
     * @tc.steps: step2. send down event and horizontal move event.
     * @tc.expected: step2. receive event callback and result is right.
     */
    TouchPoint pointStart { .id = 2,
        .x = LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointStart);

    TouchPoint pointEnd { .id = 2,
        .x = 2 * LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragStart().GetGlobalLocation(), pointStart.GetOffset());
    ASSERT_EQ(onDrag.GetDragStart().GetFingerId(), pointStart.id);
    ASSERT_EQ(onDrag.GetDragUpdate().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragUpdate().GetFingerId(), pointEnd.id);

    /**
     * @tc.steps: step3. send up event, check touch point result is right
     * @tc.expected: step3. touch point result is right.
     */
    pointEnd.type = TouchType::UP;
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragEnd().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragEnd().GetFingerId(), pointEnd.id);
}

/**
 * @tc.name: DragRecognizer003
 * @tc.desc: verify the drag recognizer corresponding free drag event
 * @tc.type: FUNC
 * @tc.require: AR000DAIGH
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, DragRecognizer003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture referee.
     */
    DragEventResult onDrag;
    auto dragRecognizer = AceType::MakeRefPtr<DragRecognizer>(Axis::FREE);

    dragRecognizer->SetOnDragStart([&onDrag](const DragStartInfo& info) { onDrag.SetDragStart(info); });
    dragRecognizer->SetOnDragUpdate([&onDrag](const DragUpdateInfo& info) { onDrag.SetDragUpdate(info); });
    dragRecognizer->SetOnDragEnd([&onDrag](const DragEndInfo& info) { onDrag.SetDragEnd(info); });

    /**
     * @tc.steps: step2. send down event and free move event.
     * @tc.expected: step2. receive event callback and result is right.
     */
    TouchPoint pointStart { .id = 2,
        .x = 2 * LOCATION_X,
        .y = 2 * LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointStart);

    TouchPoint pointEnd { .id = 2,
        .x = 2 * LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragStart().GetGlobalLocation(), pointStart.GetOffset());
    ASSERT_EQ(onDrag.GetDragStart().GetFingerId(), pointStart.id);
    ASSERT_EQ(onDrag.GetDragUpdate().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragUpdate().GetFingerId(), pointEnd.id);

    /**
     * @tc.steps: step3. send up event, check touch point result is right
     * @tc.expected: step3. touch point result is right.
     */
    pointEnd.type = TouchType::UP;
    dragRecognizer->HandleEvent(pointEnd);

    ASSERT_EQ(onDrag.GetDragEnd().GetGlobalLocation(), pointEnd.GetOffset());
    ASSERT_EQ(onDrag.GetDragEnd().GetFingerId(), pointEnd.id);
}

/**
 * @tc.name: DragRecognizer004
 * @tc.desc: verify the drag recognizer corresponding drag  cancel event
 * @tc.type: FUNC
 * @tc.require: AR000DAIGH
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, DragRecognizer004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture referee.
     */
    DragEventResult onDrag;
    auto dragRecognizer = AceType::MakeRefPtr<DragRecognizer>(Axis::HORIZONTAL);

    dragRecognizer->SetOnDragStart([&onDrag](const DragStartInfo& info) { onDrag.SetDragStart(info); });
    dragRecognizer->SetOnDragUpdate([&onDrag](const DragUpdateInfo& info) { onDrag.SetDragUpdate(info); });
    dragRecognizer->SetOnDragEnd([&onDrag](const DragEndInfo& info) { onDrag.SetDragEnd(info); });
    dragRecognizer->SetOnDragCancel([&onDrag]() { onDrag.SetDragCancel(true); });

    /**
     * @tc.steps: step2. send down event and move event.
     * @tc.expected: step2. receive event callback and check result is right.
     */
    TouchPoint pointStart { .id = 2,
        .x = 2 * LOCATION_X,
        .y = 2 * LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointStart);

    pointStart.type = TouchType::CANCEL;
    dragRecognizer->HandleEvent(pointStart);

    ASSERT_FALSE(onDrag.GetDragCancel());
    ASSERT_TRUE(onDrag.GetDragStart().GetGlobalLocation().IsZero());
    ASSERT_TRUE(onDrag.GetDragUpdate().GetGlobalLocation().IsZero());
    ASSERT_TRUE(onDrag.GetDragEnd().GetGlobalLocation().IsZero());
}

/**
 * @tc.name: DragRecognizer005
 * @tc.desc: verify the drag recognizer corresponding drag move and cancel event
 * @tc.type: FUNC
 * @tc.require: AR000DAIGH
 * @tc.author: huye
 */
HWTEST_F(GesturesTest, DragRecognizer005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create click recognizers and register to gesture referee.
     */
    DragEventResult onDrag;
    auto dragRecognizer = AceType::MakeRefPtr<DragRecognizer>(Axis::VERTICAL);

    dragRecognizer->SetOnDragStart([&onDrag](const DragStartInfo& info) { onDrag.SetDragStart(info); });
    dragRecognizer->SetOnDragUpdate([&onDrag](const DragUpdateInfo& info) { onDrag.SetDragUpdate(info); });
    dragRecognizer->SetOnDragEnd([&onDrag](const DragEndInfo& info) { onDrag.SetDragEnd(info); });
    dragRecognizer->SetOnDragCancel([&onDrag]() { onDrag.SetDragCancel(true); });

    /**
     * @tc.steps: step2. send down event and cancel event.
     * @tc.expected: step2. receive event callback and check result is right.
     */
    TouchPoint pointStart { .id = 2,
        .x = 2 * LOCATION_X,
        .y = 2 * LOCATION_Y,
        .type = TouchType::DOWN,
        .time = std::chrono::high_resolution_clock::now() };
    dragRecognizer->HandleEvent(pointStart);

    TouchPoint pointEnd { .id = 2,
        .x = 2 * LOCATION_X,
        .y = LOCATION_Y,
        .type = TouchType::MOVE,
        .time = std::chrono::high_resolution_clock::now() };

    dragRecognizer->HandleEvent(pointEnd);
    ASSERT_EQ(onDrag.GetDragStart().GetGlobalLocation().GetY(), pointStart.GetOffset().GetY());
    ASSERT_EQ(onDrag.GetDragStart().GetFingerId(), pointStart.id);
    ASSERT_EQ(onDrag.GetDragUpdate().GetGlobalLocation().GetY(), pointEnd.GetOffset().GetY());
    ASSERT_EQ(onDrag.GetDragUpdate().GetFingerId(), pointEnd.id);
    ASSERT_FALSE(onDrag.GetDragCancel());

    /**
     * @tc.steps: step3. send cancel event.
     * @tc.expected: step3. receive event callback and check result is right.
     */
    pointEnd.type = TouchType::CANCEL;
    dragRecognizer->HandleEvent(pointEnd);
    ASSERT_TRUE(onDrag.GetDragCancel());
}

} // namespace OHOS::Ace
