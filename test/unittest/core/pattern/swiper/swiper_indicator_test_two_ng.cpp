/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "swiper_test_ng.h"

#include "core/components_ng/pattern/swiper_indicator/dot_indicator/dot_indicator_paint_property.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/pipeline/base/constants.h"

namespace OHOS::Ace::NG {
namespace {
// padding:12 space:8 size:8
Offset FIRST_POINT = Offset(16.f, 16.f);
Offset SECOND_POINT = Offset(40.f, 16.f);
Offset FOURTH_POINT = Offset(72.f, 16.f);
} // namespace

class SwiperIndicatorTestTwoNg : public SwiperTestNg {
public:
    void MouseClickIndicator(SourceType sourceType, Offset hoverPoint);
    void TouchClickIndicator(SourceType sourceType, Offset touchPoint);
    void LongPressIndicator(Offset startPoint, Offset endPoint);
};

void SwiperIndicatorTestTwoNg::MouseClickIndicator(SourceType sourceType, Offset hoverPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    HoverInfo hoverInfo;
    hoverInfo.SetSourceDevice(sourceType);
    indicatorPattern->hoverEvent_->GetOnHoverFunc()(true, hoverInfo);

    MouseInfo mouseInfo;
    mouseInfo.SetSourceDevice(sourceType);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(hoverPoint);
    indicatorPattern->mouseEvent_->GetOnMouseEventFunc()(mouseInfo);

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(sourceType);
    indicatorPattern->isRepeatClicked_ = false;
    indicatorPattern->HandleClick(gestureEvent);
    FlushUITasks();
}

void SwiperIndicatorTestTwoNg::TouchClickIndicator(SourceType sourceType, Offset touchPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, touchPoint));
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, touchPoint));

    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(sourceType);
    gestureEvent.SetLocalLocation(touchPoint);
    indicatorPattern->HandleClick(gestureEvent);
    FlushUITasks();
}

void SwiperIndicatorTestTwoNg::LongPressIndicator(Offset startPoint, Offset endPoint)
{
    auto indicatorPattern = indicatorNode_->GetPattern<SwiperIndicatorPattern>();
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::DOWN, startPoint));
    GestureEvent gestureEvent;
    gestureEvent.SetLocalLocation(startPoint);
    indicatorPattern->HandleLongPress(gestureEvent);

    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::MOVE, endPoint));
    indicatorPattern->HandleTouchEvent(CreateTouchEventInfo(TouchType::UP, endPoint));
    FlushUITasks();
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: Test SwiperIndicator HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, HandleLongPress003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Touch and move right
     * @tc.expected: Swipe to item(index:1)
     */
    LongPressIndicator(FIRST_POINT, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 1);

    /**
     * @tc.steps: step1. Touch and move left
     * @tc.expected: Swipe to item(index:0)
     */
    LongPressIndicator(FOURTH_POINT, SECOND_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step1. Touch and move left, when RealTotalCount equals displayCount
     * @tc.expected: Swipe to item(index:0)
     */
    layoutProperty_->UpdateDisplayCount(4);
    LongPressIndicator(FIRST_POINT, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
    /**
     * @tc.steps: step1. Touch and move left, when RealTotalCount smaller displayCount
     * @tc.expected: Swipe to item(index:0)
     */
    layoutProperty_->UpdateDisplayCount(8);
    LongPressIndicator(FIRST_POINT, FOURTH_POINT);
    EXPECT_EQ(pattern_->GetCurrentIndex(), 0);
}

/**
 * @tc.name: CheckPointLocation001
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckPointLocation001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: CheckPointLocation002
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckPointLocation002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation003
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckPointLocation003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(2.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation004
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckPointLocation004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(2.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckPointLocation005
 * @tc.desc: CheckPointLocation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckPointLocation005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto result = indicatorPattern->CheckPointLocation(center, point);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CalculateCycle001
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    float angle = 90.0f;
    float startAngle = 0.0f;
    indicatorPattern->isUpdateCycle_ = true;
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_FALSE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle002
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    float angle = 0.0f;
    float startAngle = 90.0f;
    indicatorPattern->isUpdateCycle_ = true;
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_TRUE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle003
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    float angle = 0.0f;
    float startAngle = 90.0f;
    indicatorPattern->isUpdateCycle_ = false;
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_FALSE(indicatorPattern->CheckPointLocation(center, point));
    EXPECT_FALSE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle004
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(0.0), float(1.0));
    const PointT<float> point = PointT(float(1.0), float(0.0));
    float angle = 0.0f;
    float startAngle = 90.0f;
    indicatorPattern->isUpdateCycle_ = false;
    indicatorPattern->direction_ = SwiperDirection::LEFT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_TRUE(indicatorPattern->CheckPointLocation(center, point));
    EXPECT_TRUE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle005
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    float angle = 0.0f;
    float startAngle = 90.0f;
    indicatorPattern->isUpdateCycle_ = true;
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_FALSE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle006
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(0.0), float(1.0));
    float angle = 90.0f;
    float startAngle = 0.0f;
    indicatorPattern->isUpdateCycle_ = true;
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_TRUE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle007
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(1.0), float(0.0));
    const PointT<float> point = PointT(float(10.0), float(1.0));
    float angle = 90.0f;
    float startAngle = 0.0f;
    indicatorPattern->isUpdateCycle_ = false;
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_FALSE(indicatorPattern->CheckPointLocation(center, point));
    EXPECT_FALSE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: CalculateCycle008
 * @tc.desc: CalculateCycle
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateCycle008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateCycle.
     */
    const PointT<float> center = PointT(float(10.0), float(10.0));
    const PointT<float> point = PointT(float(1.0), float(0.0));
    float angle = 90.0f;
    float startAngle = 0.0f;
    indicatorPattern->isUpdateCycle_ = false;
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    indicatorPattern->CalculateCycle(angle, startAngle, center, point);
    EXPECT_TRUE(indicatorPattern->CheckPointLocation(center, point));
    EXPECT_TRUE(indicatorPattern->isUpdateCycle_);
}

/**
 * @tc.name: GetAngleWithPoint001
 * @tc.desc: GetAngleWithPoint
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, GetAngleWithPoint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushUITasks();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);

    /**
     * @tc.steps: step2. call GetAngleWithPoint.
     */
    PointF center(5.0f, 10.0f);
    PointF point(0.0f, 10.000001f);
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto angle = indicatorPattern->GetAngleWithPoint(center, point);
    EXPECT_EQ(angle, 90);
}

/**
 * @tc.name: GetAngleWithPoint002
 * @tc.desc: GetAngleWithPoint
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, GetAngleWithPoint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateArcSwiper();
    model.SetDirection(Axis::HORIZONTAL);
    CreateSwiperItems();
    CreateSwiperDone();
    FlushUITasks();
    auto indicatorPattern = indicatorNode_->GetPattern<ArcSwiperIndicatorPattern>();
    ASSERT_NE(indicatorPattern, nullptr);
    auto nodePaintMethod = indicatorPattern->CreateNodePaintMethod();
    ASSERT_NE(nodePaintMethod, nullptr);

    /**
     * @tc.steps: step2. call GetAngleWithPoint.
     */
    PointF center(0.0f, 10.0f);
    PointF point(5.0f, 10.000001f);
    indicatorPattern->direction_ = SwiperDirection::RIGHT;
    auto angle = indicatorPattern->GetAngleWithPoint(center, point);
    EXPECT_EQ(angle, -90);
}

/**
 * @tc.name: CalculateAngleOffset001
 * @tc.desc: CalculateAngleOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateAngleOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateAngleOffset.
     */
    float centerX = 1.0f;
    float centerY = 2.0f;
    float radius = 1.0f;
    double angle = -10.0f;
    OffsetF Offset = { 0.0, 0.0 };
    auto result = indicatorPattern->CalculateAngleOffset(centerX, centerY, radius, angle);
    EXPECT_EQ(result, Offset);
}

/**
 * @tc.name: CalculateAngleOffset002
 * @tc.desc: CalculateAngleOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateAngleOffset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateAngleOffset.
     */
    float centerX = 1.0f;
    float centerY = 2.0f;
    float radius = 1.0f;
    double angle = 180.0f;
    OffsetF Offset = { 0.0, 0.0 };
    auto result = indicatorPattern->CalculateAngleOffset(centerX, centerY, radius, angle);
    EXPECT_NE(result, Offset);
}

/**
 * @tc.name: CalculateAngleOffset003
 * @tc.desc: CalculateAngleOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CalculateAngleOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CalculateAngleOffset.
     */
    float centerX = 1.0f;
    float centerY = 2.0f;
    float radius = 1.0f;
    double angle = 45.0f;
    OffsetF Offset = { 0.0, 0.0 };
    auto result = indicatorPattern->CalculateAngleOffset(centerX, centerY, radius, angle);
    EXPECT_NE(result, Offset);
}

/**
 * @tc.name: GetInnerFocusPaintRect001
 * @tc.desc: GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, GetInnerFocusPaintRect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call GetInnerFocusPaintRect.
     */
    RoundRect paintRect;
    indicatorPattern->GetInnerFocusPaintRect(paintRect);
    auto rect = paintRect.GetRect();

    EXPECT_NE(rect.GetX(), 10);
}

/**
 * @tc.name: HandleMouseClick004
 * @tc.desc: HandleMouseClick
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, HandleMouseClick004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call HandleMouseClick.
     */
    indicatorPattern->isRepeatClicked_ = false;
    GestureEvent gestureEvent;
    gestureEvent.SetSourceDevice(SourceType::MOUSE);
    indicatorPattern->HandleMouseClick(gestureEvent);
    EXPECT_FALSE(indicatorPattern->isRepeatClicked_);
}

/**
 * @tc.name: HandleMouseEvent001
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, HandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(Offset(200.0, 30.0));
    mouseInfo.SetSourceDevice(SourceType::TOUCH);
    indicatorPattern->isClicked_ = true;
    indicatorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(indicatorPattern->isClicked_);
}

/**
 * @tc.name: HandleMouseEvent002
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, HandleMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(200.0, 30.0));
    mouseInfo.SetSourceDevice(SourceType::MOUSE);
    indicatorPattern->isClicked_ = true;
    indicatorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(indicatorPattern->isClicked_);
}

/**
 * @tc.name: HandleMouseEvent003
 * @tc.desc: HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, HandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call HandleMouseEvent.
     */
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::RELEASE);
    mouseInfo.SetLocalLocation(Offset(200.0, 30.0));
    mouseInfo.SetSourceDevice(SourceType::MOUSE);
    indicatorPattern->isClicked_ = true;
    indicatorPattern->HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(indicatorPattern->isClicked_);
}

/**
 * @tc.name: CheckDragAndUpdate001
 * @tc.desc: CheckDragAndUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckDragAndUpdate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_ = 10;
    indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_ = OverlongType::NONE;
    indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_ = 20;
    indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    pattern_->isTouchDownOnOverlong_ = true;
    pattern_->isDragging_ = true;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_LEFT;
    int32_t animationStartIndex = 10;
    int32_t animationEndIndex = 0;
    indicatorPattern->CheckDragAndUpdate(pattern_, animationStartIndex, animationEndIndex);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_,
        indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_);
    EXPECT_NE(indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_,
        indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_);
}

/**
 * @tc.name: CheckDragAndUpdate002
 * @tc.desc: CheckDragAndUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckDragAndUpdate002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_ = 10;
    indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_ = OverlongType::NONE;
    indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_ = 20;
    indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    pattern_->isTouchDownOnOverlong_ = true;
    pattern_->isDragging_ = true;
    pattern_->turnPageRate_ = 0.2f;
    int32_t animationStartIndex = 0;
    int32_t animationEndIndex = 3;
    indicatorPattern->CheckDragAndUpdate(pattern_, animationStartIndex, animationEndIndex);
    EXPECT_EQ(indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_,
        indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_);
    EXPECT_EQ(indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_,
        indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_);
}

/**
 * @tc.name: CheckDragAndUpdate003
 * @tc.desc: CheckDragAndUpdate
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, CheckDragAndUpdate003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set parameters.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDirection(Axis::VERTICAL);
    CreateSwiperItems();
    CreateSwiperDone();
    auto indicatorNode = GetChildFrameNode(frameNode_, 4);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();

    /**
     * @tc.steps: step2. call CheckPointLocation.
     */
    indicatorPattern->overlongDotIndicatorModifier_ = AceType::MakeRefPtr<OverlengthDotIndicatorModifier>();
    indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_ = 10;
    indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_ = OverlongType::NONE;
    indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_ = 20;
    indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_ = OverlongType::LEFT_FADEOUT_RIGHT_NORMAL;
    indicatorPattern->gestureState_ = GestureState::GESTURE_STATE_FOLLOW_RIGHT;
    pattern_->isTouchDownOnOverlong_ = true;
    pattern_->touchBottomType_ = TouchBottomTypeLoop::TOUCH_BOTTOM_TYPE_LOOP_NONE;
    pattern_->isDragging_ = true;
    pattern_->turnPageRate_ = 2.5f;
    int32_t animationStartIndex = 10;
    int32_t animationEndIndex = -1;
    indicatorPattern->CheckDragAndUpdate(pattern_, animationStartIndex, animationEndIndex);
    EXPECT_EQ(indicatorPattern->overlongDotIndicatorModifier_->currentSelectedIndex_,
        indicatorPattern->overlongDotIndicatorModifier_->targetSelectedIndex_);
    EXPECT_EQ(indicatorPattern->overlongDotIndicatorModifier_->currentOverlongType_,
        indicatorPattern->overlongDotIndicatorModifier_->targetOverlongType_);
}

/**
 * @tc.name: SetSwiperNode001
 * @tc.desc: Test SwiperIndicator SetSwiperNode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperIndicatorTestTwoNg, SetSwiperNode001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetIndicatorType(SwiperIndicatorType::DOT);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_NE(indicatorNode_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto mockIndicatorNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });
    EXPECT_NE(mockIndicatorNode, nullptr);
    auto indicatorPattern = mockIndicatorNode->GetPattern<IndicatorPattern>();
    auto controller = indicatorPattern->GetIndicatorController();
    controller->SetSwiperNode(frameNode_);
    EXPECT_EQ(indicatorNode_->GetPattern<IndicatorPattern>(), nullptr);
}
} // namespace OHOS::Ace::NG
