/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <cstddef>

#include "gtest/gtest.h"

#define private public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/event/mouse_event.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr uint32_t INPUT_EVENTS_SIZE = 1;
constexpr uint32_t INPUT_EVENTS_SIZE_2 = 2;
constexpr uint32_t INPUT_EVENTS_SIZE_0 = 0;
constexpr uint32_t MOUSE_RESULT_SIZE = 10;
constexpr uint32_t AXIS_RESULT_SIZE = 1;
const HoverEffectType HOVER_EFFECT_TYPE = HoverEffectType::BOARD;
constexpr float WIDTH = 400.0f;
constexpr float HEIGHT = 400.0f;
const OffsetF COORDINATE_OFFSET(WIDTH, HEIGHT);
constexpr bool HOVER_VALUE = true;
const std::string RESULT_SUCCESS_ONE = "sucess1";
const std::string RESULT_SUCCESS_TWO = "sucess2";
bool accessibilityHover = false;
} // namespace

class InputEventHubTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void SetUp() override;
    void TearDown() override;
};

void InputEventHubTestNg::SetUpTestSuite()
{
    GTEST_LOG_(INFO) << "InputEventHubTestNg SetUpTestCase";
}

void InputEventHubTestNg::TearDownTestSuite()
{
    GTEST_LOG_(INFO) << "InputEventHubTestNg TearDownTestCase";
}

void InputEventHubTestNg::SetUp()
{
    MockPipelineContext::SetUp();
}

void InputEventHubTestNg::TearDown()
{
    MockPipelineContext::TearDown();
}
/**
 * @tc.name: InputEventHubCreateTest001
 * @tc.desc: Create InputEventHub
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubCreateTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
}

/**
 * @tc.name: InputEventHubMouseEventTest002
 * @tc.desc: Create InputEventHub and set, add and remove mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubMouseEventTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    EXPECT_TRUE(
        inputEventHub->GetFrameNode() != nullptr && inputEventHub->GetFrameNode()->GetTag() == V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step2. Create mouse event and set it to inputEventHub.
     * @tc.expected: mouseEventActuator_ will be initialized.
     */
    const OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    OnMouseEventFunc onMouse1 = onMouse;
    inputEventHub->SetMouseEvent(std::move(onMouse1));
    EXPECT_NE(inputEventHub->mouseEventActuator_, nullptr);

    /**
     * @tc.steps: step3. Make mouseEventActuator_ as nullptr, and create input event and add it to inputEventHub.
     * @tc.expected: mouseEventActuator_ will be initialized and the list of inputEvents size is 1.
     */
    inputEventHub->mouseEventActuator_ = nullptr;
    OnMouseEventFunc onMouse2 = onMouse;
    auto inputEvent = AceType::MakeRefPtr<InputEvent>(std::move(onMouse2));
    inputEventHub->AddOnMouseEvent(inputEvent);
    EXPECT_EQ(inputEventHub->mouseEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE);

    /**
     * @tc.steps: step4. Remove OnMouseEvent.
     * @tc.expected: inputEvent will be remove from the list of inputEvents and the size will be 0. If
     * mouseEventActuator_ is nullptr, the function will return directly.
     */
    inputEventHub->RemoveOnMouseEvent(inputEvent);
    EXPECT_EQ(inputEventHub->mouseEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_0);
    inputEventHub->mouseEventActuator_ = nullptr;
    inputEventHub->RemoveOnMouseEvent(inputEvent);
}

/**
 * @tc.name: InputEventHubHoverEventTest003
 * @tc.desc: Create InputEventHub and invoke hover related functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubHoverEventTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Set hover animation.
     * @tc.expected: mouseEventActuator_ will be initialized and get the hoverEffect which will be assigned the correct
     * value.
     */
    inputEventHub->SetHoverEffect(HOVER_EFFECT_TYPE);
    EXPECT_NE(inputEventHub->hoverEffectActuator_, nullptr);
    EXPECT_EQ(inputEventHub->GetHoverEffect(), HOVER_EFFECT_TYPE);

    /**
     * @tc.steps: step3. Set HoverEvent.
     * @tc.expected: hoverEventActuator_ will be initialized.
     */
    OnHoverFunc onHover = [](bool, HoverInfo) {};
    inputEventHub->SetHoverEvent(std::move(onHover));
    EXPECT_NE(inputEventHub->hoverEventActuator_, nullptr);

    /**
     * @tc.steps: step4. Add OnHoverEvent.
     * @tc.expected: hoverEventActuator_ will be initialized and and the list of inputEvents size is 1.
     */
    inputEventHub->hoverEventActuator_ = nullptr;
    OnMouseEventFunc onHover2 = [](MouseInfo& info) {};
    auto onHoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHover2));
    inputEventHub->AddOnHoverEvent(onHoverEvent);
    EXPECT_NE(inputEventHub->hoverEventActuator_, nullptr);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE);

    /**
     * @tc.steps: step5. Remove OnHoverEvent.
     * @tc.expected: onHoverEvent will be remove from the list of inputEvents and the size will be 0. If
     * hoverEventActuator_ is nullptr, the function will return directly.
     */
    inputEventHub->RemoveOnHoverEvent(onHoverEvent);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_0);
    inputEventHub->hoverEventActuator_ = nullptr;
    inputEventHub->RemoveOnHoverEvent(onHoverEvent);
}

/**
 * @tc.name: InputEventHubAxisEventTest004
 * @tc.desc: Create InputEventHub and invoke Axis related functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubAxisEventTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Add OnAxisEvent.
     * @tc.expected: axisEventActuator_ will be initialized, and the list of inputEvents and the size will be 1.
     */
    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->AddOnAxisEvent(onAxisEvent);
    EXPECT_NE(inputEventHub->axisEventActuator_, nullptr);
    EXPECT_EQ(inputEventHub->axisEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE);

    /**
     * @tc.steps: step3. Remove OnAxisEvent.
     * @tc.expected: onAxisEvent will be remove from the list of inputEvents and the size will be 0. If
     * axisEventActuator_ is nullptr, the function will return directly.
     */
    inputEventHub->RemoveOnAxisEvent(onAxisEvent);
    EXPECT_EQ(inputEventHub->axisEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_0);
    inputEventHub->axisEventActuator_ = nullptr;
    inputEventHub->RemoveOnAxisEvent(onAxisEvent);
}

/**
 * @tc.name: InputEventHubProcessMouseTest005
 * @tc.desc: Create InputEventHub and invoke ProcessMouseTestHit functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubProcessMouseTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke ProcessMouseTestHit when eventHub is nullptr.
     * @tc.expected: ProcessMouseTestHit return false.
     */
    TouchTestResult mouseResult;
    auto inputEventHub2 = AceType::MakeRefPtr<InputEventHub>(nullptr);
    EXPECT_FALSE(inputEventHub2->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));

    /**
     * @tc.steps: step3. Initialize mouseEventActuator_ and mouseEventActuator_, their inputEvents_ is empty and
     * userCallback_ is nullptr and userJSFrameNodeCallback_ is nullptr too.
     * @tc.expected: OnCollectMouseEvent will return directly, and ProcessMouseTestHit return false.
     */
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    inputEventHub->hoverEffectActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));

    /**
     * @tc.steps: step4. Create mouse event and initialize userJSFrameNodeCallback_ .
     * @tc.expected: userJSFrameNodeCallback_ will be initialized and ProcessMouseTestHit return false.
     */
    const OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    OnMouseEventFunc onMouse1 = onMouse;
    inputEventHub->SetJSFrameNodeOnMouseEvent(std::move(onMouse1));
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));

    /**
     * @tc.steps: step5. Invoke ProcessMouseTestHit when hoverNode is nullptr and the hover effect is UNKNOWN or not.
     * @tc.expected: OnCollectMouseEvent will return directly, and ProcessMouseTestHit return false.
     */
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));
    inputEventHub->SetHoverEffect(HOVER_EFFECT_TYPE);
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));

    /**
     * @tc.steps: step6. Set MouseEvent and mouseEventActuator_ and userCallback_ will be initialized.
     */
    OnMouseEventFunc onMouse2 = onMouse;
    inputEventHub->SetMouseEvent(std::move(onMouse2));
    EXPECT_NE(inputEventHub->mouseEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step7. Set HoverEvent and hoverEventActuator_ and userCallback_ will be initialized.
     */
    const OnHoverFunc onHover = [](bool, HoverInfo) {};
    OnHoverFunc onHover1 = onHover;
    inputEventHub->SetHoverEvent(std::move(onHover1));
    EXPECT_NE(inputEventHub->hoverEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step8. Add OnMouseEvent and inputEvents_ will not be empty.
     */
    OnMouseEventFunc onMouse3 = onMouse;
    auto inputEvent = AceType::MakeRefPtr<InputEvent>(std::move(onMouse3));
    inputEventHub->AddOnMouseEvent(inputEvent);
    inputEventHub->AddOnMouseEvent(nullptr);
    EXPECT_EQ(inputEventHub->mouseEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_2);

    /**
     * @tc.steps: step9. Set HoverEvent and inputEvents_ will not be empty.
     */
    OnHoverFunc onHover2 = onHover;
    auto onHoverEvent = AceType::MakeRefPtr<InputEvent>(std::move(onHover2));
    inputEventHub->AddOnHoverEvent(onHoverEvent);
    inputEventHub->AddOnHoverEvent(nullptr);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_2);

    /**
     * @tc.steps: step10. Invoke ProcessMouseTestHit when inputEvents_ is not empty and userCallback_ has already been
     * initialized.
     * @tc.expected: ProcessMouseTestHit return false, mouse and hover result size has been increased one.
     */
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));
    EXPECT_EQ(inputEventHub->mouseEventActuator_->mouseEventTarget_->GetCoordinateOffset(),
        Offset(COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(inputEventHub->hoverEventActuator_->hoverEventTarget_->GetCoordinateOffset(),
        Offset(COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(inputEventHub->hoverEffectActuator_->hoverEffectTarget_->GetCoordinateOffset(),
        Offset(COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(mouseResult.size(), MOUSE_RESULT_SIZE);

    /**
     * @tc.steps: step11. Handle mouse and hover event when the events and userCallback is nullptr or not.
     */
    MouseEvent mouseEvent;
    mouseEvent.action = MouseAction::MOVE;
    EXPECT_FALSE(inputEventHub->hoverEventActuator_->hoverEventTarget_->HandleHoverEvent(HOVER_VALUE));
    inputEventHub->mouseEventActuator_->mouseEventTarget_->HandleMouseEvent(mouseEvent);
    inputEventHub->mouseEventActuator_->userCallback_ = nullptr;
    inputEventHub->hoverEventActuator_->userCallback_ = nullptr;
    EXPECT_FALSE(inputEventHub->hoverEventActuator_->hoverEventTarget_->HandleHoverEvent(HOVER_VALUE));
    inputEventHub->mouseEventActuator_->mouseEventTarget_->HandleMouseEvent(mouseEvent);
}

/**
 * @tc.name: InputEventHubProcessAxisTestHitTest006
 * @tc.desc: Create InputEventHub and invoke ProcessAxisTestHit functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubProcessAxisTestHitTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke ProcessAxisTestHit when eventHub is nullptr.
     * @tc.expected: ProcessMouseTestHit return false.
     */
    AxisTestResult onAxisResult;
    auto inputEventHub2 = AceType::MakeRefPtr<InputEventHub>(nullptr);
    EXPECT_FALSE(inputEventHub2->ProcessAxisTestHit(COORDINATE_OFFSET, onAxisResult));

    /**
     * @tc.steps: step3. Initialize axisEventActuator_ and its inputEvents_ is empty and userCallback_ is nullptr.
     * @tc.expected: OnCollectAxisEvent will return directly, and ProcessAxisTestHit return false.
     */
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    EXPECT_FALSE(inputEventHub2->ProcessAxisTestHit(COORDINATE_OFFSET, onAxisResult));

    /**
     * @tc.steps: step4. Initialize userCallback_.
     */
    OnMouseEventFunc onAxis = [](MouseInfo& info) {};
    auto onAxisEvent = AceType::MakeRefPtr<InputEvent>(std::move(onAxis));
    inputEventHub->axisEventActuator_->userCallback_ = onAxisEvent;

    /**
     * @tc.steps: step5. Add OnAxisEvent.
     * @tc.expected: axisEventActuator_ will be initialized, and the list of inputEvents and the size will be 1.
     */
    inputEventHub->AddOnAxisEvent(onAxisEvent);
    EXPECT_EQ(inputEventHub->axisEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE);

    /**
     * @tc.steps: step6. Invoke ProcessAxisTestHit when inputEvents_ is not empty and userCallback_ has already been
     * initialized.
     * @tc.expected: ProcessAxisTestHit return false, axis result size has been increased one.
     */
    EXPECT_FALSE(inputEventHub->ProcessAxisTestHit(COORDINATE_OFFSET, onAxisResult));
    EXPECT_EQ(inputEventHub->axisEventActuator_->axisEventTarget_->coordinateOffset_, COORDINATE_OFFSET);
    EXPECT_EQ(onAxisResult.size(), AXIS_RESULT_SIZE);
}

/**
 * @tc.name: InputEventHubBindContextMenuTest007
 * @tc.desc: Create InputEventHub and invoke BindContextMenu functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubBindContextMenuTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Invoke BindContextMenu when showMenu_ is nullptr or not.
     * @tc.expected: mouseEventActuator_ is not nullptr.
     */
    const OnMouseEventFunc onMouse = [](MouseInfo& info) {};
    OnMouseEventFunc onMouse1 = onMouse;
    OnMouseEventFunc onMouse2 = onMouse;
    inputEventHub->BindContextMenu(std::move(onMouse1));
    inputEventHub->BindContextMenu(std::move(onMouse2));
    EXPECT_NE(inputEventHub->mouseEventActuator_, nullptr);
}

/**
 * @tc.name: InputEventHubProcessMouseTest008
 * @tc.desc: Create InputEventHub and invoke ProcessMouseTestHit functions.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubProcessMouseTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    TouchTestResult mouseResult;

    /**
     * @tc.steps: step2. Set HoverEvent and hoverEventActuator_ and userCallback_ will be initialized.
     */
    const OnAccessibilityHoverFunc onHover = [](bool, AccessibilityHoverInfo) { accessibilityHover = true; };
    OnAccessibilityHoverFunc onHover1 = onHover;
    inputEventHub->SetAccessibilityHoverEvent(std::move(onHover1));
    EXPECT_NE(inputEventHub->accessibilityHoverEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step3. Invoke ProcessMouseTestHit when the userCallback_ has already been
     * initialized.
     * @tc.expected: ProcessMouseTestHit return false, mouse and hover result size has been increased one.
     */
    EXPECT_FALSE(inputEventHub->ProcessMouseTestHit(COORDINATE_OFFSET, mouseResult));
    EXPECT_EQ(inputEventHub->accessibilityHoverEventActuator_->accessibilityHoverEventTarget_->GetCoordinateOffset(),
        Offset(COORDINATE_OFFSET.GetX(), COORDINATE_OFFSET.GetY()));
    EXPECT_EQ(mouseResult.size(), INPUT_EVENTS_SIZE);

    /**
     * @tc.steps: step11. Handle mouse and hover event when the events and userCallback is nullptr or not.
     */
    TouchEvent event;
    inputEventHub->accessibilityHoverEventActuator_->accessibilityHoverEventTarget_->HandleAccessibilityHoverEvent(
        HOVER_VALUE, event);
    EXPECT_EQ(accessibilityHover, true);
}

/**
 * @tc.name: DisableMouseEvent001
 * @tc.desc: Test disable mouse event.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, DisableMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Initialize mouseEventActuator_, and set callback
     * @tc.expected: callback is right.
     */
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    std::string result;
    OnMouseEventFunc onMouse = [&result](MouseInfo& info) { result = RESULT_SUCCESS_ONE; };
    inputEventHub->SetMouseEvent(std::move(onMouse));
    EXPECT_NE(inputEventHub->mouseEventActuator_->userCallback_, nullptr);

    MouseInfo press;
    press.SetButton(MouseButton::LEFT_BUTTON);
    press.SetAction(MouseAction::PRESS);
    inputEventHub->mouseEventActuator_->userCallback_->onMouseCallback_(press);
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: callback is null.
     */
    inputEventHub->ClearUserOnMouse();
    EXPECT_EQ(inputEventHub->mouseEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step4. Set the callback again.
     * @tc.expected: callback is right.
     */
    OnMouseEventFunc onMouse2 = [&result](MouseInfo& info) { result = RESULT_SUCCESS_TWO; };
    inputEventHub->SetMouseEvent(std::move(onMouse2));
    EXPECT_NE(inputEventHub->mouseEventActuator_->userCallback_, nullptr);

    MouseInfo release;
    release.SetButton(MouseButton::LEFT_BUTTON);
    release.SetAction(MouseAction::RELEASE);
    inputEventHub->mouseEventActuator_->userCallback_->onMouseCallback_(release);
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: DisableAxisEvent001
 * @tc.desc: Test disable Axis event.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, DisableAxisEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Initialize axisEventActuator_, and set callback
     * @tc.expected: callback is right.
     */
    inputEventHub->axisEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    std::string result;
    OnAxisEventFunc onAxis = [&result](AxisInfo& info) { result = RESULT_SUCCESS_ONE; };
    inputEventHub->SetAxisEvent(std::move(onAxis));
    EXPECT_NE(inputEventHub->axisEventActuator_->userCallback_, nullptr);

    AxisInfo axis;
    inputEventHub->axisEventActuator_->userCallback_->onAxisCallback_(axis);
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: callback is null.
     */
    inputEventHub->ClearUserOnAxisEvent();
    EXPECT_EQ(inputEventHub->axisEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step4. Set the callback again.
     * @tc.expected: callback is right.
     */
    OnAxisEventFunc onAxis2 = [&result](AxisInfo& info) { result = RESULT_SUCCESS_TWO; };
    inputEventHub->SetAxisEvent(std::move(onAxis2));
    EXPECT_NE(inputEventHub->axisEventActuator_->userCallback_, nullptr);

    AxisInfo axis2;
    inputEventHub->axisEventActuator_->userCallback_->onAxisCallback_(axis2);
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: DisableHoverEvent001
 * @tc.desc: Test disable hover event.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, DisableHoverEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);

    /**
     * @tc.steps: step2. Initialize hoverEventActuator_, and set callback
     * @tc.expected: callback is right.
     */
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    std::string result;
    OnHoverFunc onHover = [&result](bool, HoverInfo) { result = RESULT_SUCCESS_ONE; };
    inputEventHub->SetHoverEvent(std::move(onHover));
    EXPECT_NE(inputEventHub->hoverEventActuator_->userCallback_, nullptr);

    HoverInfo hover;
    inputEventHub->hoverEventActuator_->userCallback_->onHoverEventCallback_(true, hover);
    EXPECT_EQ(result, RESULT_SUCCESS_ONE);

    /**
     * @tc.steps: step3. Clear the callback.
     * @tc.expected: callback is null.
     */
    inputEventHub->ClearUserOnHover();
    EXPECT_EQ(inputEventHub->hoverEventActuator_->userCallback_, nullptr);

    /**
     * @tc.steps: step4. Set the callback again.
     * @tc.expected: callback is right.
     */
    OnHoverFunc onHover2 = [&result](bool, HoverInfo) { result = RESULT_SUCCESS_TWO; };
    inputEventHub->SetHoverEvent(std::move(onHover2));
    EXPECT_NE(inputEventHub->hoverEventActuator_->userCallback_, nullptr);

    HoverInfo hover2;
    inputEventHub->hoverEventActuator_->userCallback_->onHoverEventCallback_(true, hover2);
    EXPECT_EQ(result, RESULT_SUCCESS_TWO);
}

/**
 * @tc.name: InputEventHubGetHoverEffectStr001
 * @tc.desc: Create InputEventHub and invoke GetHoverEffectStr function.
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, InputEventHubGetHoverEffectStr001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create InputEventHub.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);
    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    inputEventHub->hoverEffectType_ = HoverEffectType::AUTO;

    /**
     * @tc.steps: step2. Invoke BindContextMenu when showMenu_ is nullptr or not.
     * @tc.expected: mouseEventActuator_ is not nullptr.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            EXPECT_EQ(inputEventHub->GetHoverEffectStr(), i==0&&j==0?"HoverEffect.Auto":(i==0&&j==1?"HoverEffect.Scale":
                (i==1&&j==0?"HoverEffect.Highlight":"HoverEffect.None")));
            if (i == 1) {
                inputEventHub->hoverEffectType_ = HoverEffectType::NONE;
                continue;
            }
            inputEventHub->hoverEffectType_ = HoverEffectType::SCALE;
        }
        inputEventHub->hoverEffectType_ = HoverEffectType::BOARD;
    }
    inputEventHub->hoverEffectType_ = HoverEffectType::OPACITY;
    EXPECT_EQ(inputEventHub->GetHoverEffectStr(), "HoverEffect.Auto");
}

/**
 * @tc.name: RemoveAllTipsMouseEvents001
 * @tc.desc: test RemoveAllTipsMouseEvents
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, RemoveAllTipsMouseEvents001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    inputEventHub->RemoveAllTipsMouseEvents();
    inputEventHub->mouseEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    auto mouseTask1 = [](MouseInfo& info) {};
    auto mouseTask2 = [](MouseInfo& info) {};
    auto mouseEvent1 = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask1));
    auto mouseEvent2 = AceType::MakeRefPtr<InputEvent>(std::move(mouseTask2));
    mouseEvent1->SetIstips(true);
    mouseEvent1->SetTipsFollowCursor(true);
    mouseEvent2->SetIstips(true);
    mouseEvent2->SetTipsFollowCursor(true);
    inputEventHub->AddOnMouseEvent(mouseEvent1);
    inputEventHub->AddOnMouseEvent(mouseEvent2);
    ASSERT_NE(inputEventHub->mouseEventActuator_, nullptr);
    EXPECT_EQ(inputEventHub->mouseEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_2);
    inputEventHub->RemoveAllTipsMouseEvents();
    EXPECT_EQ(inputEventHub->mouseEventActuator_->inputEvents_.size(), 0);
}

/**
 * @tc.name: RemoveAllTipsHoverEvents001
 * @tc.desc: test RemoveAllTipsHoverEvents
 * @tc.type: FUNC
 */
HWTEST_F(InputEventHubTestNg, RemoveAllTipsHoverEvents001, TestSize.Level1)
{
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::TEXT_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    eventHub->AttachHost(frameNode);

    auto inputEventHub = AceType::MakeRefPtr<InputEventHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    EXPECT_NE(inputEventHub, nullptr);
    inputEventHub->RemoveAllTipsHoverEvents();
    inputEventHub->hoverEventActuator_ =
        AceType::MakeRefPtr<InputEventActuator>(AceType::WeakClaim(AceType::RawPtr(inputEventHub)));
    auto hoverTask1 = [](bool isHover) {};
    auto hoverTask2 = [](bool isHover) {};
    auto hoverEvent1 = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask1));
    auto hoverEvent2 = AceType::MakeRefPtr<InputEvent>(std::move(hoverTask2));
    hoverEvent1->SetIstips(true);
    hoverEvent2->SetIstips(true);
    inputEventHub->AddOnHoverEvent(hoverEvent1);
    inputEventHub->AddOnHoverEvent(hoverEvent2);
    ASSERT_NE(inputEventHub->hoverEventActuator_, nullptr);
    EXPECT_EQ(inputEventHub->hoverEventActuator_->inputEvents_.size(), INPUT_EVENTS_SIZE_2);
    inputEventHub->RemoveAllTipsHoverEvents();
    EXPECT_EQ(inputEventHub->hoverEventActuator_->inputEvents_.size(), 0);
}
} // namespace OHOS::Ace::NG
