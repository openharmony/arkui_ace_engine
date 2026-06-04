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

#include "gtest/gtest.h"

#include "core/components_ng/pattern/text/text_free_scroll_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {

namespace {
constexpr float TEST_VELOCITY = 300.0f;
constexpr float TEST_DELTA = 10.0f;
constexpr float TEST_OFFSET = 100.0f;
constexpr float TEST_NEAR_ZERO_VELOCITY = 200.0f;
constexpr float TEST_FINAL_POSITION = 150.0f;
constexpr float TEST_CURRENT_POSITION = 100.0f;
constexpr float TEST_FRICTION = 0.6f;
constexpr int32_t TEST_FINGER_COUNT = 2;
} // namespace

class MockScrollablePattern : public ScrollablePattern {
public:
    MockScrollablePattern() = default;
    ~MockScrollablePattern() override = default;

    bool UpdateCurrentOffset(float delta, int32_t source) override
    {
        return true;
    }

    bool IsAtTop() const override
    {
        return false;
    }

    bool IsAtBottom(bool considerRepeat = false) const override
    {
        return false;
    }

    void UpdateScrollBarOffset() override {}
};

class TextFreeScrollControllerTest : public testing::Test {
public:
    static void SetUpTestSuite()
    {
        MockContainer::SetUp();
        MockPipelineContext::SetUp();
    }

    static void TearDownTestSuite()
    {
        MockPipelineContext::TearDown();
        MockContainer::TearDown();
    }

    void SetUp() override
    {
        frameNode_ = FrameNode::CreateFrameNode("test", -1, AceType::MakeRefPtr<Pattern>());
        scrollablePattern_ = AceType::MakeRefPtr<MockScrollablePattern>();
        scrollablePattern_->SetAxis(Axis::VERTICAL);
        scrollablePattern_->SetFriction(TEST_FRICTION);
        scrollablePattern_->frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode_));
    }

    void TearDown() override
    {
        frameNode_ = nullptr;
        scrollablePattern_ = nullptr;
    }

protected:
    RefPtr<FrameNode> frameNode_;
    RefPtr<ScrollablePattern> scrollablePattern_;
};

/**
 * @tc.name: TextFreeScrollController_UpdateCurrentOffset
 * @tc.desc: Test UpdateCurrentOffset method
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_UpdateCurrentOffset, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    OffsetF offset(TEST_OFFSET, TEST_OFFSET);
    controller->UpdateCurrentOffset(offset);
    EXPECT_EQ(controller->currentOffset_, offset);
}

/**
 * @tc.name: TextFreeScrollController_Fling
 * @tc.desc: Test Fling method with different velocities and directions
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_Fling, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    controller->UpdateCurrentOffset(OffsetF(TEST_CURRENT_POSITION, TEST_CURRENT_POSITION));
    
    // Branch 1: Near zero velocity - should remain IDLE
    controller->Fling(TEST_NEAR_ZERO_VELOCITY, true);
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    
    // Branch 2: Valid velocity vertical
    controller->Fling(TEST_VELOCITY, true);
    EXPECT_EQ(controller->verticalState_, State::FLING);
    
    // Branch 3: Valid velocity horizontal
    controller->horizontalState_ = State::IDLE;
    controller->Fling(TEST_VELOCITY, false);
    EXPECT_EQ(controller->horizontalState_, State::FLING);
}

/**
 * @tc.name: TextFreeScrollController_StopScrollAnimation
 * @tc.desc: Test StopScrollAnimation method in different states and directions
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_StopScrollAnimation, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: State is FLING - should change to IDLE
    controller->verticalState_ = State::FLING;
    controller->StopScrollAnimation(true);
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    
    // Branch 2: State is not FLING - should remain unchanged
    controller->verticalState_ = State::DRAG;
    controller->StopScrollAnimation(true);
    EXPECT_EQ(controller->verticalState_, State::DRAG);
    
    // Branch 3: Horizontal direction
    controller->horizontalState_ = State::FLING;
    controller->StopScrollAnimation(false);
    EXPECT_EQ(controller->horizontalState_, State::IDLE);
}

/**
 * @tc.name: TextFreeScrollController_StopAllScrollAnimation
 * @tc.desc: Test StopAllScrollAnimation method
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_StopAllScrollAnimation, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    controller->verticalState_ = State::FLING;
    controller->horizontalState_ = State::FLING;
    controller->StopAllScrollAnimation();
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    EXPECT_EQ(controller->horizontalState_, State::IDLE);
}

/**
 * @tc.name: TextFreeScrollController_HandlePanStart
 * @tc.desc: Test HandlePanStart method in vertical and horizontal directions
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandlePanStart, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    GestureEvent event;
    
    // Branch 1: Vertical direction
    controller->HandlePanStart(event, true);
    EXPECT_EQ(controller->verticalState_, State::DRAG);
    
    // Branch 2: Horizontal direction
    controller->HandlePanStart(event, false);
    EXPECT_EQ(controller->horizontalState_, State::DRAG);
}

/**
 * @tc.name: TextFreeScrollController_HandlePanUpdate
 * @tc.desc: Test HandlePanUpdate method with mouse wheel and multi-finger and and single-finger touch
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandlePanUpdate, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: Mouse wheel - should trigger WHEEL state
    GestureEvent wheelEvent;
    wheelEvent.SetInputEventType(InputEventType::AXIS);
    wheelEvent.SetDelta(Offset(TEST_DELTA, TEST_DELTA));
    controller->HandlePanUpdate(wheelEvent, true);
    EXPECT_EQ(controller->verticalState_, State::WHEEL);
    
    // Branch 2: Multi-finger touch - delta should be divided by finger count
    bool callbackCalled = false;
    controller->SetOnScrollCallback([&callbackCalled](float offset, int32_t source, bool isVertical) {
        callbackCalled = true;
        EXPECT_EQ(offset, TEST_DELTA / TEST_FINGER_COUNT);
    });
    
    GestureEvent multiFingerEvent;
    multiFingerEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    multiFingerEvent.SetDelta(Offset(TEST_DELTA, TEST_DELTA));
    std::list<FingerInfo> fingers;
    for (int32_t i = 0; i < TEST_FINGER_COUNT; ++i) {
        fingers.emplace_back();
    }
    multiFingerEvent.SetFingerList(fingers);
    controller->HandlePanUpdate(multiFingerEvent, true);
    EXPECT_TRUE(callbackCalled);
    
    // Branch 3: Single-finger touch - delta should remain unchanged
    callbackCalled = false;
    controller->SetOnScrollCallback([&callbackCalled](float offset, int32_t source, bool isVertical) {
        callbackCalled = true;
        EXPECT_EQ(offset, TEST_DELTA);
    });
    
    GestureEvent singleFingerEvent;
    singleFingerEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    singleFingerEvent.SetDelta(Offset(TEST_DELTA, TEST_DELTA));
    std::list<FingerInfo> singleFinger;
    singleFinger.emplace_back();
    singleFingerEvent.SetFingerList(singleFinger);
    controller->HandlePanUpdate(singleFingerEvent, true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: TextFreeScrollController_HandlePanEndOrCancel
 * @tc.desc: Test HandlePanEndOrCancel method with mouse wheel and touch
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandlePanEndOrCancel, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: Mouse wheel - should trigger scroll end callback
    bool callbackCalled = false;
    controller->SetOnScrollEndCallback([&callbackCalled](bool isVertical) {
        callbackCalled = true;
    });
    
    GestureEvent wheelEvent;
    wheelEvent.SetInputEventType(InputEventType::AXIS);
    controller->HandlePanEndOrCancel(wheelEvent, true);
    EXPECT_TRUE(callbackCalled);
    
    // Branch 2: Touch with zero velocity - should trigger scroll end callback
    callbackCalled = false;
    GestureEvent touchEvent;
    touchEvent.SetInputEventType(InputEventType::TOUCH_SCREEN);
    Velocity velocity;
    velocity.SetOffsetPerSecond(Offset(0.0, 0.0));
    touchEvent.SetVelocity(velocity);
    controller->HandlePanEndOrCancel(touchEvent, true);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: TextFreeScrollController_HandleTouchDown
 * @tc.desc: Test HandleTouchDown method when state is DRAG and not DRAG
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandleTouchDown, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: State is DRAG - should remain DRAG
    controller->verticalState_ = State::DRAG;
    controller->HandleTouchDown();
    EXPECT_EQ(controller->verticalState_, State::DRAG);
    
    // Branch 2: State is not DRAG - should stop all animations and become IDLE
    controller->verticalState_ = State::FLING;
    controller->horizontalState_ = State::FLING;
    controller->HandleTouchDown();
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    EXPECT_EQ(controller->horizontalState_, State::IDLE);
}

/**
 * @tc.name: TextFreeScrollController_HandleOffsetUpdate
 * @tc.desc: Test HandleOffsetUpdate method when state is FLING, WHEEL, and IDLE
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandleOffsetUpdate, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: State is FLING and near final position - should stop animation
    controller->verticalState_ = State::FLING;
    controller->flingFinalPos_ = TEST_FINAL_POSITION;
    controller->lastVsyncTime_ = 0;
    controller->lastPosition_ = TEST_CURRENT_POSITION;
    controller->HandleOffsetUpdate(TEST_FINAL_POSITION, true);
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    
    // Branch 2: State is WHEEL - should trigger scroll update callback
    bool callbackCalled = false;
    controller->SetOnScrollCallback([&callbackCalled](float offset, int32_t source, bool isVertical) {
        callbackCalled = true;
    });
    controller->verticalState_ = State::WHEEL;
    controller->UpdateCurrentOffset(OffsetF(TEST_CURRENT_POSITION, TEST_CURRENT_POSITION));
    controller->HandleOffsetUpdate(TEST_FINAL_POSITION, true);
    EXPECT_TRUE(callbackCalled);
    
    // Branch 3: State is IDLE - should not trigger scroll update callback
    callbackCalled = false;
    controller->verticalState_ = State::IDLE;
    controller->HandleOffsetUpdate(TEST_FINAL_POSITION, true);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: TextFreeScrollController_HandleAnimationEnd
 * @tc.desc: Test HandleAnimationEnd method in vertical and horizontal directions
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandleAnimationEnd, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    bool callbackCalled = false;
    controller->SetOnScrollEndCallback([&callbackCalled](bool isVertical) {
        callbackCalled = true;
    });
    
    // Branch 1: Vertical direction
    controller->verticalState_ = State::FLING;
    controller->HandleAnimationEnd(true);
    EXPECT_EQ(controller->verticalState_, State::IDLE);
    EXPECT_TRUE(callbackCalled);
    
    // Branch 2: Horizontal direction
    callbackCalled = false;
    controller->horizontalState_ = State::FLING;
    controller->HandleAnimationEnd(false);
    EXPECT_EQ(controller->horizontalState_, State::IDLE);
    EXPECT_TRUE(callbackCalled);
}

/**
 * @tc.name: TextFreeScrollController_TriggerMouseAnimation
 * @tc.desc: Test TriggerMouseAnimation method when wheelAnimator is null and exists
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_TriggerMouseAnimation, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    controller->UpdateCurrentOffset(OffsetF(TEST_CURRENT_POSITION, TEST_CURRENT_POSITION));
    
    // Branch 1: wheelAnimator is null - should create animator
    controller->wheelAnimator_ = nullptr;
    controller->TriggerMouseAnimation(TEST_DELTA, true);
    EXPECT_NE(controller->wheelAnimator_, nullptr);
    EXPECT_EQ(controller->verticalState_, State::WHEEL);
    
    // Branch 2: wheelAnimator exists - should reuse animator
    controller->TriggerMouseAnimation(TEST_DELTA, false);
    EXPECT_EQ(controller->horizontalState_, State::WHEEL);
}

 /**
 * @tc.name: TextFreeScrollController_HandleMouseAnimationFrame
 * @tc.desc: Test HandleMouseAnimationFrame method in vertical and horizontal directions
 * @tc.type: FUNC
 */
HWTEST_F(TextFreeScrollControllerTest, TextFreeScrollController_HandleMouseAnimationFrame, TestSize.Level1)
{
    auto controller = AceType::MakeRefPtr<TextFreeScrollController>(scrollablePattern_);
    
    // Branch 1: Vertical direction
    controller->mouseWheelScrollIsVertical_ = true;
    controller->HandleMouseAnimationFrame(TEST_FINAL_POSITION);
    // offsetY_ should be updated internally
    
    // Branch 2: Horizontal direction
    controller->mouseWheelScrollIsVertical_ = false;
    controller->HandleMouseAnimationFrame(TEST_FINAL_POSITION);
    // offsetX_ should be updated internally
}

} // namespace OHOS::Ace::NG
