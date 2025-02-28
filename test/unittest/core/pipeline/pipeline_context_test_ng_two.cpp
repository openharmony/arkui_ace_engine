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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
// Add the following two macro definitions to test the private and protected method.
#define private public
#define protected public

#include "core/accessibility/accessibility_manager_ng.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/event/axis_event.h"
#include "core/event/mouse_event.h"

using namespace testing;
using namespace testing::ext;
 
namespace OHOS::Ace {
namespace NG {

/**
 * @tc.name: PipelineContextTestNg130
 * @tc.desc: Test the function FlushMouseEventVoluntarily.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg130, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: Create MouseEvent, then initialize pipeline.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    MouseEvent event;
    event.x = 12.345f;
    event.y = 12.345f;
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(event);
    context_->lastMouseEvent_->action = MouseAction::WINDOW_LEAVE;
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    context_->viewScale_ = DEFAULT_DOUBLE2;

    /**
     * @tc.steps2: Call the function FlushMouseEventVoluntarily.
     * @tc.expected: Test isNeedFlushMouseEvent_ is Changed to REJECT.
     */
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);
    context_->isNeedFlushMouseEvent_ = MockFlushEventType::REJECT;
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg131
 * @tc.desc: Test the function FlushUITaskWithSingleDirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg131, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    EXPECT_NE(frameNode_1, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<LayoutProperty>();
    frameNode_1->SetLayoutProperty(layoutProperty);

    /**
     * @tc.steps2: Call the function FlushUITaskWithSingleDirtyNode.
     * @tc.expected: Test the reaction of the function at different Rect.
     */
    context_->FlushUITaskWithSingleDirtyNode(frameNode_1);
    NG::RectF testRect = { 10.0f, 10.0f, 10.0f, 10.0f };
    layoutProperty->SetLayoutRect(testRect);
    context_->FlushUITaskWithSingleDirtyNode(frameNode_1);
    EXPECT_NE(frameNode_1->GetLayoutProperty(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg132
 * @tc.desc: Test the function FlushUITaskWithSingleDirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg132, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, SafeAreaManager, TextFieldManagerNG.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    context_->safeAreaManager_ = safeAreaManager;
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    context_->SetTextFieldManager(textFieldManager);

    /**
     * @tc.steps2: Call the function DoKeyboardAvoidFunc.
     * @tc.expected: Test the stability of this function.
     */
    context_->DoKeyboardAvoidFunc(400.0f, 0.0, 400.0f, false);
    EXPECT_NE(context_->textFieldManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg133
 * @tc.desc: Test the function SetIsFocusActive.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg133, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, properties.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    SystemProperties::focusCanBeActive_.store(true);
    context_->isFocusActive_= true;

    /**
     * @tc.steps2: Call the function SetIsFocusActive.
     * @tc.expected: Test the stability of this function.
     */
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API);
    EXPECT_FALSE(context_->isFocusActive_);
}

/**
 * @tc.name: PipelineContextTestNg134
 * @tc.desc: Test the function SetHostParentOffsetToWindow.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg134, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, offfset.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    Offset offfset(1.0, 1.0);

    /**
     * @tc.steps2: Call the function SetHostParentOffsetToWindow.
     * @tc.expected: Test the stability of this function.
     */
    context_->SetHostParentOffsetToWindow(Offset(offfset.GetX(), offfset.GetY()));
    EXPECT_EQ(context_->lastHostParentOffsetToWindow_, offfset);
}

/**
 * @tc.name: PipelineContextTestNg135
 * @tc.desc: Test the function GetResponseRegion.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg135, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, frame node.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetRootSize(1.0f, 800, 1600);
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    EXPECT_NE(frameNode_1, nullptr);

    /**
     * @tc.steps2: Call the function GetResponseRegion.
     * @tc.expected: Test the stability of this function.
     */
    std::string result = context_->GetResponseRegion(frameNode_1);
    EXPECT_TRUE(result.empty());
}

/**
 * @tc.name: PipelineContextTestNg136
 * @tc.desc: Test the function SetWindowContainerColor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg136, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    /**
     * @tc.steps2: Call the function SetWindowContainerColor.
     * @tc.expected: Test if this function is available.
     */
    context_->SetWindowContainerColor(Color::BLUE, Color::BLACK);
    EXPECT_NE(context_->rootNode_, nullptr);
    auto containerNode = AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front());
    EXPECT_NE(containerNode, nullptr);
    auto containerPattern = containerNode->GetPattern<ContainerModalPattern>();
    EXPECT_NE(containerPattern, nullptr);
    EXPECT_EQ(containerPattern->activeColor_, Color::BLUE);

    /**
     * @tc.steps3: Call the function GetContainerControlButtonVisible.
     * @tc.expected: Test if this function is available.
     */
    bool isControlButtonVisible = context_->GetContainerControlButtonVisible();
    EXPECT_FALSE(isControlButtonVisible);

    /**
     * @tc.steps4: Call the function GetContainerCustomTitleVisible.
     * @tc.expected: Test if this function is available.
     */
    bool isCustomTitleVisible = context_->GetContainerCustomTitleVisible();
    EXPECT_FALSE(isCustomTitleVisible);

    /**
     * @tc.steps4: Call the function GetContainerFloatingTitleVisible.
     * @tc.expected: Test if this function is available.
     */
    bool isFloatingTitleVisible = context_->GetContainerFloatingTitleVisible();
    EXPECT_FALSE(isFloatingTitleVisible);
}

/**
 * @tc.name: PipelineContextTestNg137
 * @tc.desc: Test the function OnMouseMoveEventForAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg137, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, mouse event, frame node, event manager.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    MouseEvent mouseEvent1;
    mouseEvent1.x = 100.0f;
    mouseEvent1.y = 200.0f;
    mouseEvent1.action = MouseAction::MOVE;
    mouseEvent1.button = MouseButton::NONE_BUTTON;
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    EXPECT_NE(frameNode_1, nullptr);

    /**
     * @tc.steps2: Call the function SetEventManager.
     * @tc.expected: Test if this function is available.
     */
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    /**
     * @tc.steps3: Call the function OnMouseMoveEventForAxisEvent.
     * @tc.expected: Test if this function is available.
     */
    context_->OnMouseMoveEventForAxisEvent(mouseEvent1, frameNode_1);
    EXPECT_NE(context_->eventManager_, nullptr);
    AxisEvent axisEvent;

    /**
     * @tc.steps4: Call the function DispatchAxisEventToDragDropManager.
     * @tc.expected: Test if this function is available.
     */
    axisEvent.action = AxisAction::BEGIN;
    axisEvent.isRotationEvent = false;
    SerializedGesture etsSerializedGesture;
    ASSERT_NE(context_->dragDropManager_, nullptr);
    context_->DispatchAxisEventToDragDropManager(axisEvent, frameNode_1, etsSerializedGesture);

    /**
     * @tc.steps5: Call the function DispatchAxisEventToDragDropManager.
     * @tc.expected: Test the stability of this function.
     */
    context_->dragDropManager_ = nullptr;
    context_->isBeforeDragHandleAxis_ = true;
    axisEvent.action = AxisAction::END;
    context_->DispatchAxisEventToDragDropManager(axisEvent, frameNode_1, etsSerializedGesture);
    EXPECT_FALSE(context_->isBeforeDragHandleAxis_);
}

/**
 * @tc.name: PipelineContextTestNg138
 * @tc.desc: Test the function UpdateLastMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg138, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, mouse event.
     */
    ASSERT_NE(context_, nullptr);
    MouseEvent mouseEvent;
    mouseEvent.x = 0.1f;
    mouseEvent.y = 0.1f;
    mouseEvent.button = MouseButton::NONE_BUTTON;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.touchEventId = 101;

    /**
     * @tc.steps2: Call the function UpdateLastMoveEvent.
     * @tc.expected: Test if this function is available.
     */
    context_->UpdateLastMoveEvent(mouseEvent);
    ASSERT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->x, 0.1f);
    EXPECT_EQ(context_->lastMouseEvent_->y, 0.1f);
    EXPECT_EQ(context_->lastMouseEvent_->button, MouseButton::NONE_BUTTON);
    EXPECT_EQ(context_->lastMouseEvent_->action, MouseAction::MOVE);
    EXPECT_EQ(context_->lastMouseEvent_->sourceType, SourceType::MOUSE);
    EXPECT_EQ(context_->lastMouseEvent_->touchEventId, 101);
}

/**
 * @tc.name: PipelineContextTestNg139
 * @tc.desc: Test the function OnMouseMoveEventForAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg139, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, touch event.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    TouchEvent touchEvent;
    touchEvent.sourceTool = SourceTool::PEN;
    touchEvent.type = TouchType::DOWN;
    touchEvent.force = 0.1f;

    /**
     * @tc.steps2: Call the function HandlePenHoverOut.
     * @tc.expected: Test if this function is available.
     */
    context_->HandlePenHoverOut(touchEvent);

    /**
     * @tc.steps3: Call the function OnPenHoverEvent.
     * @tc.expected: Test if this function is available.
     */
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    EXPECT_NE(frameNode_1, nullptr);
    context_->OnPenHoverEvent(touchEvent, frameNode_1);

    /**
     * @tc.steps4: Call the function OnAccessibilityHoverEvent.
     * @tc.expected: Test if this function is available.
     */
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->OnAccessibilityHoverEvent(touchEvent, frameNode_1);

    /**
     * @tc.steps5: Call the function CompensateTouchMoveEvent.
     * @tc.expected: Test if this function is available.
     */
    touchEvent.type = TouchType::UP;
    context_->CompensateTouchMoveEvent(touchEvent);
    context_->touchEvents_.push_back(touchEvent);
    context_->CompensateTouchMoveEventFromUnhandledEvents(touchEvent);
    ASSERT_NE(context_->eventManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg140
 * @tc.desc: Test the function OnMouseMoveEventForAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg140, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function SetIsFocusActive.
     * @tc.expected: Test the stability of this function with different parameters passed in.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API, false);
    EXPECT_FALSE(context_->autoFocusInactive_);
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API, true);
    EXPECT_TRUE(context_->autoFocusInactive_);
    auto result_1 = context_->SetIsFocusActive(false, FocusActiveReason::POINTER_EVENT, false);
    EXPECT_FALSE(result_1);

    /**
     * @tc.steps2: Call the function OnCaretPositionChangeOrKeyboardHeightChange.
     * @tc.expected: Test the stability of this function.
     */
    auto safeAreaManager = AceType::MakeRefPtr<SafeAreaManager>();
    context_->safeAreaManager_ = safeAreaManager;
    auto textFieldManager = AceType::MakeRefPtr<TextFieldManagerNG>();
    textFieldManager->SetHeight(20);
    textFieldManager->SetUsingCustomKeyboardAvoid(false);
    context_->SetTextFieldManager(textFieldManager);
    context_->OnCaretPositionChangeOrKeyboardHeightChange(400.0f, 0.1f, 0.1f, nullptr, true);
    ASSERT_NE(context_->textFieldManager_, nullptr);
}

} // namespace NG
} // namespace OHOS::Ace