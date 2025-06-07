/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "test/unittest/core/gestures/gestures_common_test_ng.h"
#include "core/components_ng/base/observer_handler.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
class MockNGGestureRecognizer : public NGGestureRecognizer {
public:
    MOCK_METHOD(void, ResetStatusOnFinish, (bool isBlocked), ());
    void BatchAdjudicate(const RefPtr<NGGestureRecognizer>& recognizer, GestureDisposal disposal) {}
    void OnBeginGestureReferee(int32_t touchId, bool needUpdateChild = false) {}
    void HandleTouchDownEvent(const TouchEvent& event) {}
    void HandleTouchUpEvent(const TouchEvent& event) {}
    void HandleTouchMoveEvent(const TouchEvent& event) {}
    void HandleTouchCancelEvent(const TouchEvent& event) {}
    void HandleTouchDownEvent(const AxisEvent& event) {}
    void HandleTouchUpEvent(const AxisEvent& event) {}
    void HandleTouchMoveEvent(const AxisEvent& event) {}
    void HandleTouchCancelEvent(const AxisEvent& event) {}
    void OnResetStatus() {}
    void OnSucceedCancel() {}
    void OnAccepted() {}
    void OnRejected() {}
    bool CheckTouchId(int32_t touchId)
    {
        return false;
    }
    std::map<int32_t, TouchEvent> GetTouchPoints()
    {
        std::map<int32_t, TouchEvent> emptyTouchPoints;
        return emptyTouchPoints;
    }
};
class GestureRecognizerTestNg : public GesturesCommonTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void GestureRecognizerTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
}

void GestureRecognizerTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: TriggerGestureJudgeCallbackTest001
 * @tc.desc: Test Recognizer function: TriggerGestureJudgeCallbackTest001
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, TriggerGestureJudgeCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    RefPtr<PinchRecognizer> pinchRecognizerPtr = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
        PINCH_GESTURE_DISTANCE);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);

    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();

    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.expected: step2. result equals CONTINUE.
     */
    clickRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    clickRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    auto result = clickRecognizerPtr->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
    longPressRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    longPressRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    result = longPressRecognizerPtr->TriggerGestureJudgeCallback();
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    result = panRecognizerPtr->TriggerGestureJudgeCallback();
    pinchRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    pinchRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    result = pinchRecognizerPtr->TriggerGestureJudgeCallback();
    rotationRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    rotationRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    result = rotationRecognizerPtr->TriggerGestureJudgeCallback();
    swipeRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    swipeRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    result = swipeRecognizerPtr->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
    /**
     * @tc.steps: step3. targetComponent_ is not null, call TriggerGestureJudgeCallback function and compare result.
     * @tc.expected: step3. result equals PREVENT.
     */
    clickRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(clickRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    longPressRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(longPressRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    panRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(panRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    pinchRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(pinchRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    rotationRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(rotationRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);

    swipeRecognizerPtr->targetComponent_ = targetComponent;
    EXPECT_EQ(swipeRecognizerPtr->TriggerGestureJudgeCallback(), GestureJudgeResult::REJECT);
}

/**
 * @tc.name: TransformTest001
 * @tc.desc: Test Transform in Default Condition
 */
HWTEST_F(GestureRecognizerTestNg, TransformTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode.
     */
    RefPtr<FrameNode> FRAME_NODE_0 = FrameNode::CreateFrameNode("0", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_1 = FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_2 = FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE_2->SetParent(WeakPtr<FrameNode>(FRAME_NODE_1));
    FRAME_NODE_1->SetParent(WeakPtr<FrameNode>(FRAME_NODE_0));

    /**
     * @tc.steps: step2. mock local matrix.
     */
    FRAME_NODE_0->localMat_ = Matrix4::CreateIdentity();
    FRAME_NODE_1->localMat_ = Matrix4::CreateIdentity();
    FRAME_NODE_2->localMat_ = Matrix4::CreateIdentity();

    /**
     * @tc.steps: step2. call callback function.
     */
    PointF f1(1.0, 1.0);
    NGGestureRecognizer::Transform(f1, WeakPtr<FrameNode>(FRAME_NODE_2));
    PointF f2(1.000000, 1.000000);
    EXPECT_EQ(f1, f2);
}

/**
 * @tc.name: TransformTest002
 * @tc.desc: Test Transform with Matrix
 */
HWTEST_F(GestureRecognizerTestNg, TransformTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode.
     */
    RefPtr<FrameNode> FRAME_NODE_0 = FrameNode::CreateFrameNode("0", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_1 = FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_2 = FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE_2->SetParent(WeakPtr<FrameNode>(FRAME_NODE_1));
    FRAME_NODE_1->SetParent(WeakPtr<FrameNode>(FRAME_NODE_0));

    /**
     * @tc.steps: step2. mock local matrix.
     */
    FRAME_NODE_0->localMat_ = Matrix4::CreateIdentity();
    FRAME_NODE_1->localMat_ = Matrix4::Invert(
            Matrix4::CreateTranslate(100, 200, 0) * Matrix4::CreateRotate(90, 0, 0, 1) *
            Matrix4::CreateScale(0.6, 0.8, 1));
    FRAME_NODE_2->localMat_ = Matrix4::Invert(
            Matrix4::CreateTranslate(400, 300, 0) * Matrix4::CreateRotate(30, 0, 0, 1) *
            Matrix4::CreateScale(0.5, 0.5, 1));

    /**
     * @tc.steps: step3. call callback function.
     */
    PointF f1(1.0, 1.0);
    NGGestureRecognizer::Transform(f1, WeakPtr<FrameNode>(FRAME_NODE_2));
    PointF f2(-1443.533813, 426.392731);
    EXPECT_EQ(f1, f2);
}

/**
 * @tc.name: TransformTest003
 * @tc.desc: Test Transform with Matrix in Reverse Order
 */
HWTEST_F(GestureRecognizerTestNg, TransformTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create FrameNode.
     */
    RefPtr<FrameNode> FRAME_NODE_0 = FrameNode::CreateFrameNode("0", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_1 = FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> FRAME_NODE_2 = FrameNode::CreateFrameNode("2", 2, AceType::MakeRefPtr<Pattern>());
    FRAME_NODE_2->SetParent(WeakPtr<FrameNode>(FRAME_NODE_1));
    FRAME_NODE_1->SetParent(WeakPtr<FrameNode>(FRAME_NODE_0));

    /**
     * @tc.steps: step2. mock local matrix.
     */
    FRAME_NODE_0->localMat_ = Matrix4::CreateIdentity();
    FRAME_NODE_2->localMat_ = Matrix4::Invert(
            Matrix4::CreateTranslate(100, 200, 0) * Matrix4::CreateRotate(90, 0, 0, 1) *
            Matrix4::CreateScale(0.6, 0.8, 1));
    FRAME_NODE_1->localMat_ = Matrix4::Invert(
            Matrix4::CreateTranslate(400, 300, 0) * Matrix4::CreateRotate(30, 0, 0, 1) *
            Matrix4::CreateScale(0.5, 0.5, 1));

    /**
     * @tc.steps: step3. call callback function.
     */
    PointF f1(1.0, 1.0);
    NGGestureRecognizer::Transform(f1, WeakPtr<FrameNode>(FRAME_NODE_2));
    PointF f2(-531.471924, 1362.610352);
    EXPECT_EQ(f1, f2);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest001
 * @tc.desc: Test PanPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */

    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    PanDirection panDirection;
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    panRecognizerPtr->targetComponent_ = targetComponent;
    panRecognizerPtr->targetComponent_->node_ = frameNode;
    TouchEvent touchEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    panRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizerPtr->direction_.type = PanDirection::ALL;
    panRecognizerPtr->isFlushTouchEventsEnd_ = true;
    panRecognizerPtr->averageDistance_ = Offset(0, -1);
    panRecognizerPtr->distance_ = 0;
    panRecognizerPtr->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizerPtr->currentFingers_ = 1;
    panRecognizerPtr->fingers_ = 1;

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: gestureInfo_ is nullptr touchEvent
     * @tc.expected: step2. result equals REJECT.
     */
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case2: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = true touchEvent
     * @tc.expected: step2. result equals REJECT.
     */
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    guestureEventHub->dragEventActuator_ = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(guestureEventHub)), panDirection, 1, 50.0f);
    guestureEventHub->dragEventActuator_->isDragUserReject_ = true;
    panRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_EQ(panRecognizerPtr->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case3: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = false touchEvent
     * @tc.expected: step2. isDragUserReject_ = true.
     */
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    guestureEventHub->dragEventActuator_->isDragUserReject_ = false;
    panRecognizerPtr->HandleTouchMoveEvent(touchEvent);
    EXPECT_TRUE(guestureEventHub->dragEventActuator_->isDragUserReject_);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest002
 * @tc.desc: Test PanPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create and set Recognizer、TargetComponent.
     */
    RefPtr<PanGestureOption> panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(panGestureOption);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    auto guestureEventHub = frameNode->GetOrCreateGestureEventHub();
    PanDirection panDirection;
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    panRecognizerPtr->targetComponent_ = targetComponent;
    panRecognizerPtr->targetComponent_->node_ = frameNode;
    TouchEvent touchEvent;
    touchEvent.tiltX.emplace(1.0f);
    touchEvent.tiltY.emplace(1.0f);
    AxisEvent axisEvent;
    panRecognizerPtr->touchPoints_[touchEvent.id] = touchEvent;
    panRecognizerPtr->direction_.type = PanDirection::ALL;
    panRecognizerPtr->isFlushTouchEventsEnd_ = true;
    panRecognizerPtr->averageDistance_ = Offset(0, -1);
    panRecognizerPtr->distance_ = 0;
    panRecognizerPtr->distanceMap_[SourceTool::UNKNOWN] = Dimension(0, DimensionUnit::PX);
    panRecognizerPtr->currentFingers_ = 1;
    panRecognizerPtr->fingers_ = 1;

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case1: gestureInfo_ is nullptr axisEvent
     * @tc.expected: step2. result equals REJECT.
     */
    panRecognizerPtr->inputEventType_ = InputEventType::AXIS;
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->disposal_, GestureDisposal::NONE);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case2: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = true axisEvent
     * @tc.expected: step2. result equals REJECT.
     */
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    guestureEventHub->dragEventActuator_ = AceType::MakeRefPtr<DragEventActuator>(
        AceType::WeakClaim(AceType::RawPtr(guestureEventHub)), panDirection, 1, 50.0f);
    guestureEventHub->dragEventActuator_->isDragUserReject_ = true;
    panRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_EQ(panRecognizerPtr->disposal_, GestureDisposal::REJECT);

    /**
     * @tc.steps: step2. call HandleOverdueDeadline function and compare result.
     * @tc.steps: case3: gestureInfo_ is not nullptr, gestureInfo_->type_ = DRAG
     *                   isDragUserReject_ = false axisEvent
     * @tc.expected: step2. isDragUserReject_ = true.
     */
    panRecognizerPtr->refereeState_ = RefereeState::DETECTING;
    guestureEventHub->dragEventActuator_->isDragUserReject_ = false;
    panRecognizerPtr->HandleTouchMoveEvent(axisEvent);
    EXPECT_TRUE(guestureEventHub->dragEventActuator_->isDragUserReject_);
}

class MockLongPressRecognizer : public LongPressRecognizer {
public:
    MockLongPressRecognizer() : LongPressRecognizer(DURATION, FINGER_NUMBER) {}
    MOCK_METHOD(void, HandleTouchUpEvent, (const TouchEvent&), (override));
    MOCK_METHOD(void, HandleTouchCancelEvent, (const TouchEvent&), (override));
};

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest003
 * @tc.desc: Test PanPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest003, TestSize.Level1)
{
    auto recognizerTest = AceType::MakeRefPtr<LongPressRecognizer>(PINCH_GESTURE_DISTANCE, FINGER_NUMBER);
    recognizerTest->fingersId_.insert(1);
    recognizerTest->fingersId_.insert(2);
    recognizerTest->fingersId_.insert(3);
    recognizerTest->fingersId_.insert(4);
    recognizerTest->fingersId_.insert(5);
    recognizerTest->fingersId_.insert(6);
    TouchEvent point;
    point.type = TouchType::MOVE;
    recognizerTest->HandleBridgeModeEvent(point);
    point.type = TouchType::DOWN;
    recognizerTest->HandleBridgeModeEvent(point);
    point.sourceType = SourceType::MOUSE;
    point.id = 4;
    recognizerTest->HandleBridgeModeEvent(point);

    point.type = TouchType::UP;
    point.id = 2;
    auto longPressRecoginzer = AceType::MakeRefPtr<MockLongPressRecognizer>();
    longPressRecoginzer->fingersId_.clear();
    longPressRecoginzer->fingersId_.insert(1);
    longPressRecoginzer->fingersId_.insert(2);
    longPressRecoginzer->fingersId_.insert(3);
    longPressRecoginzer->fingersId_.insert(4);
    EXPECT_CALL(*longPressRecoginzer, HandleTouchUpEvent(_)).WillRepeatedly(Return());
    longPressRecoginzer->HandleBridgeModeEvent(point);
    EXPECT_EQ(point.id, 2);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest004
 * @tc.desc: Test PanPressRecognizer function: HandleBridgeModeEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest004, TestSize.Level1)
{
    auto longPressRecoginzer = AceType::MakeRefPtr<MockLongPressRecognizer>();
    TouchEvent point;
    point.type = TouchType::UP;
    point.id = 8;
    longPressRecoginzer->fingersId_.clear();
    longPressRecoginzer->fingersId_.insert(1);
    longPressRecoginzer->fingersId_.insert(2);
    longPressRecoginzer->fingersId_.insert(3);
    longPressRecoginzer->fingersId_.insert(4);
    EXPECT_CALL(*longPressRecoginzer, HandleTouchUpEvent(_)).WillRepeatedly(Return());
    longPressRecoginzer->HandleBridgeModeEvent(point);

    point.type = TouchType::CANCEL;
    longPressRecoginzer->fingersId_.clear();
    longPressRecoginzer->fingersId_.insert(1);
    longPressRecoginzer->fingersId_.insert(2);
    longPressRecoginzer->fingersId_.insert(3);
    longPressRecoginzer->fingersId_.insert(4);
    point.id = 2;
    EXPECT_CALL(*longPressRecoginzer, HandleTouchCancelEvent(_)).WillRepeatedly(Return());
    longPressRecoginzer->HandleBridgeModeEvent(point);

    point.type = TouchType::CANCEL;
    longPressRecoginzer->fingersId_.clear();
    longPressRecoginzer->fingersId_.insert(1);
    longPressRecoginzer->fingersId_.insert(2);
    longPressRecoginzer->fingersId_.insert(3);
    longPressRecoginzer->fingersId_.insert(4);
    point.id = 5;
    EXPECT_CALL(*longPressRecoginzer, HandleTouchCancelEvent(_)).WillRepeatedly(Return());
    longPressRecoginzer->HandleBridgeModeEvent(point);
    point.type = TouchType::PULL_UP;
    auto recognizerTest = AceType::MakeRefPtr<LongPressRecognizer>(DURATION, FINGER_NUMBER);
    recognizerTest->HandleBridgeModeEvent(point);
    EXPECT_EQ(point.id, 5);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest005
 * @tc.desc: Test PanPressRecognizer function: OnRejectBridgeObj
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest005, TestSize.Level1)
{
    auto recognizerTest = AceType::MakeRefPtr<LongPressRecognizer>(DURATION, FINGER_NUMBER);
    recognizerTest->OnRejectBridgeObj();

    WeakPtr<NGGestureRecognizer> bridgeObj = AceType::MakeRefPtr<MockNGGestureRecognizer>();
    recognizerTest->bridgeObjList_.push_back(bridgeObj);
    recognizerTest->OnRejectBridgeObj();
    EXPECT_NE(recognizerTest->Dump(), nullptr);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest006
 * @tc.desc: Test PanPressRecognizer function: HandleBridgeModeEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest006, TestSize.Level1)
{
    AxisEvent event;
    auto longPressRecoginzer = AceType::MakeRefPtr<MockLongPressRecognizer>();
    event.action = AxisAction::NONE;
    longPressRecoginzer->HandleBridgeModeEvent(event);
    event.action = AxisAction::BEGIN;
    longPressRecoginzer->HandleBridgeModeEvent(event);
    event.action = AxisAction::UPDATE;
    longPressRecoginzer->HandleBridgeModeEvent(event);
    event.action = AxisAction::END;
    longPressRecoginzer->HandleBridgeModeEvent(event);
    EXPECT_EQ(event.action, AxisAction::END);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest007
 * @tc.desc: Test Dump
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest007, TestSize.Level1)
{
    auto recognizerTest = AceType::MakeRefPtr<LongPressRecognizer>(DURATION, FINGER_NUMBER);
    EXPECT_NE(recognizerTest->Dump(), nullptr);
}

/**
 * @tc.name: PanPressRecognizerHandleTouchMoveEventTest008
 * @tc.desc: Test PanPressRecognizer function: HandleTouchMoveEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, PanPressRecognizerHandleTouchMoveEventTest008, TestSize.Level1)
{
    auto recognizerTest = AceType::MakeRefPtr<LongPressRecognizer>(DURATION, FINGER_NUMBER);
    RefPtr<NGGestureRecognizer> targetPtr1 = nullptr;
    RefPtr<NGGestureRecognizer> targetPtr2 = nullptr;
    std::list<RefPtr<NGGestureRecognizer>> responseLinkResult;
    responseLinkResult.push_back(targetPtr1);
    responseLinkResult.push_back(targetPtr2);
    recognizerTest->SetResponseLinkRecognizers(responseLinkResult);
    EXPECT_NE(recognizerTest->Dump(), nullptr);
}

/**
 * @tc.name: GestureRecognizerHandleEvent001
 * @tc.desc: Test GestureRecognizer function: AboutToAddCurrentFingers AboutToMinusCurrentFingers
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, GestureRecognizerHandleEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create ExclusiveRecognizer.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    TouchEvent touchEvent;
    bool result = false;

    /**
     * @tc.steps: step3. set currentFinger = 0, add touchEvent to gestureRecognizer.
     * @tc.steps: case1: touchPoints is in recognizer region.
     * @tc.expected: step3. func success, clickRecognizer currentFingers add.
     */
    clickRecognizerPtr->currentFingers_ = 0;
    result = clickRecognizerPtr->AboutToAddCurrentFingers(touchEvent);
    EXPECT_EQ(result, true);
    EXPECT_EQ(clickRecognizerPtr->currentFingers_, 1);

    /**
     * @tc.steps: step3. set currentFinger = 1, delete touchEvent to gestureRecognizer.
     * @tc.steps: case2: fingersId not find touchEvent id.
     * @tc.expected: step3. func fail.
     */
    clickRecognizerPtr->currentFingers_ = 1;
    result = clickRecognizerPtr->AboutToMinusCurrentFingers(0);
    EXPECT_EQ(result, false);
    EXPECT_EQ(clickRecognizerPtr->currentFingers_, 1);

    /**
     * @tc.steps: step3. set currentFinger = 1, delete touchEvent to gestureRecognizer.
     * @tc.steps: case3: fingersId find touchEvent id.
     * @tc.expected: step3. func success, currentFingers delete.
     */
    clickRecognizerPtr->currentFingers_ = 1;
    clickRecognizerPtr->fingersId_.insert(0);
    result = clickRecognizerPtr->AboutToMinusCurrentFingers(0);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: HandlePanGestureAccept_001
 * @tc.desc: Test GestureRecognizer function: HandlePanGestureAccept
 * @tc.type: FUNC
 */

HWTEST_F(GestureRecognizerTestNg, HandlePanGestureAccept_001, TestSize.Level1)
{
    PanDirection direction;
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(SINGLE_FINGER_NUMBER, direction, 0);
    ASSERT_NE(panRecognizerPtr, nullptr);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    panRecognizerPtr->SetOnActionStart(start);
    panRecognizerPtr->SetOnActionEnd(end);
    panRecognizerPtr->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionStart_, GestureCallbackType::START);
    EXPECT_EQ(panRecognizerPtr->currentCallbackState_, CurrentCallbackState::START);
}

 /**
  * @tc.name: HandlePanGestureAccept_002
  * @tc.desc: Test GestureRecognizer function: HandlePanGestureAccept
  * @tc.type: FUNC
  */

HWTEST_F(GestureRecognizerTestNg, HandlePanGestureAccept_002, TestSize.Level1)
{
    PanDirection direction;
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(SINGLE_FINGER_NUMBER, direction, 0);
    ASSERT_NE(panRecognizerPtr, nullptr);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    panRecognizerPtr->SetOnActionStart(start);
    panRecognizerPtr->SetOnActionEnd(end);
    panRecognizerPtr->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionEnd_, GestureCallbackType::END);
    EXPECT_EQ(panRecognizerPtr->currentCallbackState_, CurrentCallbackState::END);
}

/**
 * @tc.name: TagGestureJudgeCallbackTest001
 * @tc.desc: Test function: CreateTapGestureLocationEvent
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, TagGestureJudgeCallbackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Recognizer、TargetComponent.
     */
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);

    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();

    auto gestureJudgeFunc = [](const RefPtr<GestureInfo>& gestureInfo, const std::shared_ptr<BaseGestureEvent>& info) {
        gestureInfo->SetType(GestureTypeName::TAP_GESTURE);
        return GestureJudgeResult::REJECT;};
    targetComponent->SetOnGestureJudgeBegin(gestureJudgeFunc);
    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.expected: step2. result equals CONTINUE.
     */
    clickRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    clickRecognizerPtr->gestureInfo_->type_ = GestureTypeName::TAP_GESTURE;
    auto result = clickRecognizerPtr->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::CONTINUE);
}

/**
 * @tc.name: LongPressGestureJudgeTest001
 * @tc.desc: Test function: Create LongpresRecognizer TriggerGestureJudgeCallback.
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, LongPressGestureJudgeTest001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create GestureEventHub, Recognizer, TargetComponent.
    */
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    ASSERT_NE(longPressRecognizerPtr, nullptr);
    longPressRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    ASSERT_NE(longPressRecognizerPtr->gestureInfo_, nullptr);
    longPressRecognizerPtr->gestureInfo_->type_ = GestureTypeName::PAN_GESTURE;
    auto gestureJudgeNativeFunc = [](const RefPtr<GestureInfo>& gestureInfo,
        const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::CONTINUE;};
    auto gestureJudgeNativeFuncForMenu = [](const RefPtr<GestureInfo>& gestureInfo,
        const std::shared_ptr<BaseGestureEvent>& info) {
        return GestureJudgeResult::REJECT;};
    auto frameNode = FrameNode::CreateFrameNode("myButton", 100, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    auto gestureHub = frameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    gestureHub->SetOnGestureJudgeNativeBegin(gestureJudgeNativeFunc);
    gestureHub->SetOnGestureJudgeNativeBeginForMenu(gestureJudgeNativeFuncForMenu);
    RefPtr<NG::TargetComponent> targetComponent = AceType::MakeRefPtr<TargetComponent>();
    ASSERT_NE(targetComponent, nullptr);
    auto callbackNative = gestureHub->GetOnGestureJudgeNativeBeginCallback();
    targetComponent->SetOnGestureJudgeNativeBegin(std::move(callbackNative));

    /**
     * @tc.steps: step2. call TriggerGestureJudgeCallback function and compare result.
     * @tc.expected: step2. result equals REJECT.
     */
    longPressRecognizerPtr->SetTargetComponent(targetComponent);
    auto result = longPressRecognizerPtr->TriggerGestureJudgeCallback();
    EXPECT_EQ(result, GestureJudgeResult::REJECT);
}

/**
 * @tc.name: HandleGestureAcceptTest001
 * @tc.desc: Test function: HandleGestureAccept for PanRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    PanDirection direction;
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(SINGLE_FINGER_NUMBER, direction, 0);
    ASSERT_NE(panRecognizerPtr, nullptr);
    panRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    panRecognizerPtr->SetOnActionStart(start);
    panRecognizerPtr->SetOnAction(action);
    panRecognizerPtr->SetOnActionEnd(end);
    panRecognizerPtr->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionStart_, GestureCallbackType::START);
    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onAction_, GestureCallbackType::ACTION);
    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_END);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionEnd_, GestureCallbackType::END);
    auto endCallbackError = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallbackError);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionEnd_, GestureCallbackType::UPDATE);
}

/**
 * @tc.name: HandleGestureAcceptTest002
 * @tc.desc: Test function: HandleGestureAccept for ClickRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<ClickRecognizer> clickRecognizerPtr = AceType::MakeRefPtr<ClickRecognizer>(FINGER_NUMBER, COUNT);
    ASSERT_NE(clickRecognizerPtr, nullptr);
    clickRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    clickRecognizerPtr->SetOnActionStart(start);
    clickRecognizerPtr->SetOnAction(action);
    clickRecognizerPtr->SetOnActionEnd(end);
    clickRecognizerPtr->SetRecognizerType(GestureTypeName::TAP_GESTURE);

    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::TAP);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    clickRecognizerPtr->SendCallbackMsg(clickRecognizerPtr->onActionStart_, GestureCallbackType::START);

    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::TAP);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    clickRecognizerPtr->SendCallbackMsg(clickRecognizerPtr->onAction_, GestureCallbackType::ACTION);

    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::TAP);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    clickRecognizerPtr->SendCallbackMsg(clickRecognizerPtr->onActionEnd_, GestureCallbackType::END);
    clickRecognizerPtr->SetRecognizerType(GestureTypeName::CLICK);
    clickRecognizerPtr->SendCallbackMsg(clickRecognizerPtr->onActionEnd_, GestureCallbackType::END);
}

/**
 * @tc.name: HandleGestureAcceptTest003
 * @tc.desc: Test function: HandleGestureAccept for LongPressRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<LongPressRecognizer> longPressRecognizerPtr = AceType::MakeRefPtr<LongPressRecognizer>(LONG_PRESS_DURATION,
        FINGER_NUMBER, false);
    ASSERT_NE(longPressRecognizerPtr, nullptr);
    longPressRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    longPressRecognizerPtr->SetOnActionStart(start);
    longPressRecognizerPtr->SetOnAction(action);
    longPressRecognizerPtr->SetOnActionEnd(end);
    longPressRecognizerPtr->SetRecognizerType(GestureTypeName::LONG_PRESS_GESTURE);

    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::LONG_PRESS);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    longPressRecognizerPtr->SendCallbackMsg(longPressRecognizerPtr->onActionStart_, false, GestureCallbackType::START);

    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::LONG_PRESS);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    longPressRecognizerPtr->SendCallbackMsg(longPressRecognizerPtr->onAction_, false, GestureCallbackType::ACTION);

    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_END);
        EXPECT_EQ(gestureListenerType, GestureListenerType::LONG_PRESS);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    longPressRecognizerPtr->SendCallbackMsg(longPressRecognizerPtr->onActionEnd_, false, GestureCallbackType::END);
}

/**
 * @tc.name: HandleGestureAcceptTest004
 * @tc.desc: Test function: HandleGestureAccept for PinchRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest004, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<PinchRecognizer> pinchRecognizerPtr = AceType::MakeRefPtr<PinchRecognizer>(SINGLE_FINGER_NUMBER,
        PINCH_GESTURE_DISTANCE);
    ASSERT_NE(pinchRecognizerPtr, nullptr);
    pinchRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    pinchRecognizerPtr->SetOnActionStart(start);
    pinchRecognizerPtr->SetOnAction(action);
    pinchRecognizerPtr->SetOnActionEnd(end);
    pinchRecognizerPtr->SetRecognizerType(GestureTypeName::PINCH_GESTURE);

    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PINCH);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    pinchRecognizerPtr->SendCallbackMsg(pinchRecognizerPtr->onActionStart_, GestureCallbackType::START);

    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PINCH);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    pinchRecognizerPtr->SendCallbackMsg(pinchRecognizerPtr->onAction_, GestureCallbackType::ACTION);

    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_END);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PINCH);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    pinchRecognizerPtr->SendCallbackMsg(pinchRecognizerPtr->onActionEnd_, GestureCallbackType::END);
}

/**
 * @tc.name: HandleGestureAcceptTest005
 * @tc.desc: Test function: HandleGestureAccept for RotationRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest005, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<RotationRecognizer> rotationRecognizerPtr =
        AceType::MakeRefPtr<RotationRecognizer>(SINGLE_FINGER_NUMBER, ROTATION_GESTURE_ANGLE);
    ASSERT_NE(rotationRecognizerPtr, nullptr);
    rotationRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    rotationRecognizerPtr->SetOnActionStart(start);
    rotationRecognizerPtr->SetOnAction(action);
    rotationRecognizerPtr->SetOnActionEnd(end);
    rotationRecognizerPtr->SetRecognizerType(GestureTypeName::ROTATION_GESTURE);

    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::ROTATION);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    rotationRecognizerPtr->SendCallbackMsg(rotationRecognizerPtr->onActionStart_, GestureCallbackType::START);

    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::ROTATION);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    rotationRecognizerPtr->SendCallbackMsg(rotationRecognizerPtr->onAction_, GestureCallbackType::ACTION);

    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_END);
        EXPECT_EQ(gestureListenerType, GestureListenerType::ROTATION);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    rotationRecognizerPtr->SendCallbackMsg(rotationRecognizerPtr->onActionEnd_, GestureCallbackType::END);
}

/**
 * @tc.name: HandleGestureAcceptTest006
 * @tc.desc: Test function: HandleGestureAccept for SwipeRecognizer
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest006, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    SwipeDirection swipeDirection;
    RefPtr<SwipeRecognizer> swipeRecognizerPtr =
        AceType::MakeRefPtr<SwipeRecognizer>(SINGLE_FINGER_NUMBER, swipeDirection, SWIPE_SPEED);
    ASSERT_NE(swipeRecognizerPtr, nullptr);
    swipeRecognizerPtr->AttachFrameNode(frameNode);
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    swipeRecognizerPtr->SetOnActionStart(start);
    swipeRecognizerPtr->SetOnAction(action);
    swipeRecognizerPtr->SetOnActionEnd(end);
    swipeRecognizerPtr->SetRecognizerType(GestureTypeName::SWIPE_GESTURE);

    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::SWIPE);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    swipeRecognizerPtr->SendCallbackMsg(swipeRecognizerPtr->onActionStart_, GestureCallbackType::START);

    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::SWIPE);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    swipeRecognizerPtr->SendCallbackMsg(swipeRecognizerPtr->onAction_, GestureCallbackType::ACTION);

    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::SWIPE);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    swipeRecognizerPtr->SendCallbackMsg(swipeRecognizerPtr->onActionEnd_, GestureCallbackType::END);
}

/**
 * @tc.name: HandleGestureAcceptTest007
 * @tc.desc: Test function: HandleGestureAccept for PanRecognizer drag
 * @tc.type: FUNC
 */
HWTEST_F(GestureRecognizerTestNg, HandleGestureAcceptTest007, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode("myButton", 0, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(frameNode, nullptr);
    PanDirection direction;
    RefPtr<PanRecognizer> panRecognizerPtr = AceType::MakeRefPtr<PanRecognizer>(SINGLE_FINGER_NUMBER, direction, 0);
    ASSERT_NE(panRecognizerPtr, nullptr);
    panRecognizerPtr->AttachFrameNode(frameNode);
    panRecognizerPtr->gestureInfo_ = AceType::MakeRefPtr<GestureInfo>();
    panRecognizerPtr->gestureInfo_->type_ = GestureTypeName::DRAG;
    GestureEvent info;
    auto start = [](GestureEvent& info) {};
    auto action = [](GestureEvent& info) {};
    auto end = [](GestureEvent& info) {};
    panRecognizerPtr->SetOnActionStart(start);
    panRecognizerPtr->SetOnAction(action);
    panRecognizerPtr->SetOnActionEnd(end);
    panRecognizerPtr->SetRecognizerType(GestureTypeName::PAN_GESTURE);
    auto startCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                             const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                             GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_START);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(startCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionStart_, GestureCallbackType::START);
    auto actionCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                              const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                              GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(actionCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onAction_, GestureCallbackType::ACTION);
    auto endCallback = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::WILL_END);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallback);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionEnd_, GestureCallbackType::END);
    auto endCallbackError = [](GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
                           const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode,
                           GestureActionPhase phase) {
        EXPECT_EQ(phase, GestureActionPhase::UNKNOWN);
        EXPECT_EQ(gestureListenerType, GestureListenerType::PAN);
    };
    UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(endCallbackError);
    panRecognizerPtr->SendCallbackMsg(panRecognizerPtr->onActionEnd_, GestureCallbackType::UPDATE);
}
} // namespace OHOS::Ace::NG