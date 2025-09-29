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
#include "base/log/dump_log.h"
#include "adapter/ohos/osal/thp_extra_manager_impl.h"
#include "core/accessibility/accessibility_manager_ng.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/event/axis_event.h"
#include "core/event/mouse_event.h"
#include "test/mock/core/common/mock_window.h"

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
    auto focusManager = context_->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    focusManager->isFocusActive_ = false;

    /**
     * @tc.steps2: Call the function SetIsFocusActive.
     * @tc.expected: Test the stability of this function.
     */
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API);
    EXPECT_FALSE(context_->GetIsFocusActive());
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
    auto focusManager = context_->GetOrCreateFocusManager();
    ASSERT_NE(focusManager, nullptr);
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API, false);
    EXPECT_FALSE(focusManager->autoFocusInactive_);
    context_->SetIsFocusActive(false, FocusActiveReason::USE_API, true);
    EXPECT_TRUE(focusManager->autoFocusInactive_);
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

/**
 * @tc.name: PipelineContextTestNg141
 * @tc.desc: Test the function FlushPendingDeleteCustomNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg141, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<CustomNode> customNode =
        CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "test");

    /**
     * @tc.steps2: add pending delete customNode and call FlushPendingDeleteCustomNode function.
     * @tc.expected: pendingDeleteCustomNode_.size() is 0.
     */
    context_->AddPendingDeleteCustomNode(customNode);
    context_->FlushPendingDeleteCustomNode();
    EXPECT_EQ(context_->pendingDeleteCustomNode_.size(), 0);

    /**
     * @tc.steps3: executeFireOnAppear is true and call FlushPendingDeleteCustomNode function.
     * @tc.expected: pendingDeleteCustomNode_.size() is 0.
     */
    customNode->executeFireOnAppear_ = true;
    context_->AddPendingDeleteCustomNode(customNode);
    context_->FlushPendingDeleteCustomNode();
    EXPECT_EQ(context_->pendingDeleteCustomNode_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg142
 * @tc.desc: Test the function FlushFreezeNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg142, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushFreezeNode function.
     * @tc.expected: dirtyFreezeNode_.size() is 0.
     */
    ASSERT_NE(context_, nullptr);
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_1));
    context_->AddDirtyFreezeNode(frameNode);
    context_->FlushFreezeNode();
    EXPECT_EQ(context_->dirtyFreezeNode_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg143
 * @tc.desc: Test the function FlushDragEvents.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg143, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    DragPointerEvent pointerEvent;
    auto frameNode_1 = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    context_->dragEvents_[frameNode_1].emplace_back(pointerEvent);

    /**
     * @tc.steps2: dragDropManager is not null and call FlushDragEvents function.
     * @tc.expected: dragEvents_.size() is 0.
     */
    auto dragDropManager = AceType::MakeRefPtr<DragDropManager>();
    dragDropManager->SetDragFwkShow(false);
    context_->dragDropManager_ = dragDropManager;
    context_->FlushDragEvents();
    EXPECT_EQ(context_->dragEvents_.size(), 0);

    /**
     * @tc.steps3: dragDropManager is null and call FlushDragEvents function.
     * @tc.expected: dragEvents_.size() is 0.
     */
    context_->dragDropManager_ = nullptr;
    context_->FlushDragEvents();
    EXPECT_EQ(context_->dragEvents_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg144
 * @tc.desc: Test the function FlushDragEvents.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg144, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<DragDropManager> manager = AceType::MakeRefPtr<DragDropManager>();
    std::string extraInfo = "test";
    RefPtr<FrameNode> node = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    std::list<DragPointerEvent> pointerEventList;
    DragPointerEvent pointerEvent;
    TimeStamp time = std::chrono::high_resolution_clock::now();

    /**
     * @tc.steps2: call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 0.
     */
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 0);

    /**
     * @tc.steps3: pointerEvent.action is PULL_MOVE and call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 0.
     */
    pointerEvent.action = PointerAction::PULL_MOVE;
    pointerEventList.push_back(pointerEvent);
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 0);

    /**
     * @tc.steps4: pointerEvent.time is not default and call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 1.
     */
    pointerEvent.pointerId = 1;
    pointerEvent.time = time;
    pointerEventList.push_back(pointerEvent);
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->dragEvents_.size(), 0);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 1);

    /**
     * @tc.steps5: pointerEvent.x is 100 and call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 2.
     */
    pointerEvent.pointerId = 2;
    pointerEvent.x = 100.0f;
    pointerEventList.push_back(pointerEvent);
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->dragEvents_.size(), 0);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 2);

    /**
     * @tc.steps6: pointerEvent.y is 100 and call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 3.
     */
    pointerEvent.pointerId = 3;
    pointerEvent.x = 100.0f;
    pointerEvent.y = 100.0f;
    pointerEventList.push_back(pointerEvent);
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 3);

    /**
     * @tc.steps7: focusWindowId is 10 and call FlushDragEvents function.
     * @tc.expected: historyPointsEventById_.size() is 3.
     */
    context_->SetFocusWindowId(0);
    context_->FlushDragEvents(manager, extraInfo, node, pointerEventList);
    EXPECT_EQ(context_->historyPointsEventById_.size(), 3);
}

/**
 * @tc.name: PipelineContextTestNg145
 * @tc.desc: Test the function FlushMouseEventVoluntarily.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg145, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    context_->lastMouseEvent_ = nullptr;
    context_->SetupRootElement();
    EXPECT_NE(context_->rootNode_, nullptr);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());

    /**
     * @tc.steps2: call FlushMouseEventVoluntarily function.
     * @tc.expected: eventManager is not null.
     */
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);

    /**
     * @tc.steps3: lastMouseEvent_->action is NONE and call FlushMouseEventVoluntarily function.
     * @tc.expected: eventManager is not null.
     */
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>();
    context_->lastMouseEvent_->action = MouseAction::NONE;
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);

    /**
     * @tc.steps4: isNeedFlushMouseEvent_ is REJECT and call FlushMouseEventVoluntarily function.
     * @tc.expected: eventManager is not null.
     */
    context_->isNeedFlushMouseEvent_ = MockFlushEventType::REJECT;
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);

    /**
     * @tc.steps5: isNeedFlushMouseEvent_ is NONE and call FlushMouseEventVoluntarily function.
     * @tc.expected: eventManager is not null.
     */
    context_->isNeedFlushMouseEvent_ = MockFlushEventType::NONE;
    context_->FlushMouseEventVoluntarily();
    EXPECT_NE(context_->eventManager_, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg146
 * @tc.desc: Test the function FlushRequestFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg146, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    auto node = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    focusHub->focusable_ = false;
    node->focusHub_ = focusHub;
    context_->dirtyRequestFocusNode_ = node;

    /**
     * @tc.steps2: call FlushRequestFocus function.
     * @tc.expected: dirtyRequestFocusNode_.Upgrade() is null.
     */
    context_->FlushRequestFocus();
    EXPECT_EQ(context_->dirtyRequestFocusNode_.Upgrade(), nullptr);

    /**
     * @tc.steps3: focusHub->currentFocus_ is true and call FlushRequestFocus function.
     * @tc.expected: dirtyRequestFocusNode_.Upgrade() is null.
     */
    focusHub->currentFocus_ = true;
    context_->dirtyRequestFocusNode_ = node;
    context_->FlushRequestFocus();
    EXPECT_EQ(context_->dirtyRequestFocusNode_.Upgrade(), nullptr);

    /**
     * @tc.steps4: node->focusHub_ is null and call FlushRequestFocus function.
     * @tc.expected: dirtyRequestFocusNode_.Upgrade() is null.
     */
    node->focusHub_ = nullptr;
    context_->dirtyRequestFocusNode_ = node;
    context_->FlushRequestFocus();
    EXPECT_EQ(context_->dirtyRequestFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg147
 * @tc.desc: Test the function FlushFocusView.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg147, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushFocusView function.
     * @tc.expected: lastFocusView is invalid.
     */
    ASSERT_NE(context_, nullptr);
    auto pagePattern = AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>());
    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, -1, pagePattern);
    auto pageFocusHub = pageNode->GetOrCreateFocusHub();
    auto pageFocusView = AceType::WeakClaim<PagePattern>(AceType::RawPtr<PagePattern>(pagePattern));
    context_->GetOrCreateFocusManager()->lastFocusView_ = pageFocusView;
    context_->FlushFocusView();
    EXPECT_FALSE(context_->GetFocusManager()->lastFocusView_.Invalid());
}

/**
 * @tc.name: PipelineContextTestNg148
 * @tc.desc: Test the function FlushFocusScroll.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg148, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    auto node = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    RefPtr<EventHub> eventHub = AceType::MakeRefPtr<EventHub>();
    eventHub->AttachHost(node);
    auto focusHub = AceType::MakeRefPtr<FocusHub>(AceType::WeakClaim(AceType::RawPtr(eventHub)));
    context_->focusManager_->SetLastFocusStateNode(focusHub);

    /**
     * @tc.steps2: isNeedTriggerScroll_ is default and call FlushRequestFocus function.
     * @tc.expected: isNeedTriggerScroll_ is false.
     */
    context_->FlushFocusScroll();
    EXPECT_FALSE(context_->focusManager_->GetNeedTriggerScroll());

    /**
     * @tc.steps3: call FlushRequestFocus function.
     * @tc.expected: isNeedTriggerScroll_ is false.
     */
    context_->FlushFocusScroll();
    EXPECT_FALSE(context_->focusManager_->GetNeedTriggerScroll());
}

/**
 * @tc.name: PipelineContextTestNg149
 * @tc.desc: Test the function FlushPipelineImmediately.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg149, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushPipelineImmediately function.
     * @tc.expected: isRebuildFinished_ is true.
     */
    ASSERT_NE(context_, nullptr);
    context_->taskScheduler_->SetIsLayouting(true);
    context_->FlushPipelineImmediately();
    EXPECT_TRUE(context_->isRebuildFinished_);
}

/**
 * @tc.name: PipelineContextTestNg150
 * @tc.desc: Test DumpFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg150, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function DumpFocus.
     * @tc.expected: Test the result of calling the function when the parameter is set to true.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    ASSERT_NE(context_->rootNode_, nullptr);
    bool hasJson = true;
    context_->DumpFocus(hasJson);
    EXPECT_NE(context_->rootNode_->GetFocusHub(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg151
 * @tc.desc: Test DumpData.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg151, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function DumpData.
     * @tc.expected: Test that there is no "-" in the elements of the parameter params.
     */
    ASSERT_NE(context_, nullptr);
    std::vector<std::string> params;
    params.push_back("test");
    frameNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
    frameNode_ = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    bool hasJson = true;
    context_->DumpData(frameNode_, params, hasJson);
    EXPECT_TRUE(params[0].find("-") == std::string::npos);

    /**
     * @tc.steps2: Call the function DumpData.
     * @tc.expected: Test that there is a "-" in the elements of the parameter params.
     */
    params.clear();
    params.push_back("test-test");
    context_->DumpData(frameNode_, params, hasJson);
    EXPECT_FALSE(params[0].find("-") == std::string::npos);
}

/**
 * @tc.name: PipelineContextTestNg152
 * @tc.desc: Test OnDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg152, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function OnDumpInfo.
     * @tc.expected: Test that the member window_ is empty.
     */
    ASSERT_NE(context_, nullptr);
    std::vector<std::string> params;
    params.push_back("test");
    params.push_back("1");
    context_->window_ = nullptr;
    auto ret = context_->OnDumpInfo(params);
    EXPECT_TRUE(ret);
    auto window = std::make_shared<MockWindow>();
    context_->window_ = window;
    EXPECT_CALL(*window, RequestFrame()).Times(AnyNumber());
}

/**
 * @tc.name: PipelineContextTestNg153
 * @tc.desc: Test OnDumpRecorderStart.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg153, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function OnDumpRecorderStart.
     * @tc.expected: Test the second element of the parameter params is greater than 0.
     */
    ASSERT_NE(context_, nullptr);
    std::vector<std::string> params;
    params.push_back("test");
    params.push_back("1");
    context_->OnDumpRecorderStart(params);
    EXPECT_EQ(params.size(), 2);

    /**
     * @tc.steps2: Call the function OnDumpRecorderStart.
     * @tc.expected: Test the second element of the parameter params is equal to 0.
     */
    params.clear();
    params.push_back("test");
    params.push_back("0");
    context_->OnDumpRecorderStart(params);
    EXPECT_GT(params.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg154
 * @tc.desc: Test FlushMouseEventForHover.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg154, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function FlushMouseEventForHover.
     * @tc.expected: Test the stability of the function under various member conditions.
     */
    ASSERT_NE(context_, nullptr);
    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(mouseEvent);
    context_->lastMouseEvent_->pointerEvent = nullptr;
    context_->lastSourceType_ = SourceType::NONE;
    context_->lastMouseEvent_->isMockWindowTransFlag = true;
    context_->SetIsTransFlag(true);
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->action = MouseAction::WINDOW_ENTER;
    context_->lastMouseEvent_->isMockWindowTransFlag = false;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::MAXIMIZE;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->action = MouseAction::WINDOW_LEAVE;
    context_->FlushMouseEventForHover();

    context_->lastMouseEvent_->action = MouseAction::MOVE;
    context_->lastMouseEvent_->isMockWindowTransFlag = false;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::RECOVER;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->isMockWindowTransFlag = false;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::DRAG;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->isMockWindowTransFlag = false;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::MOVE;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->isMockWindowTransFlag = true;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::MAXIMIZE;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->isMockWindowTransFlag = true;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::DRAG;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);

    context_->lastMouseEvent_->isMockWindowTransFlag = true;
    context_->windowSizeChangeReason_ = WindowSizeChangeReason::MOVE;
    context_->FlushMouseEventForHover();
    EXPECT_FALSE(context_->lastMouseEvent_->pointerEvent);
}

/**
 * @tc.name: PipelineContextTestNg155
 * @tc.desc: Test FlushMouseEventInVsync.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg155, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function FlushMouseEventInVsync.
     * @tc.expected: Test the member mouseEvents_ is empty.
     */
    ASSERT_NE(context_, nullptr);
    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(mouseEvent);
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);
    int32_t frameNodeId = 1;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(TEST_TAG, frameNodeId, AceType::MakeRefPtr<Pattern>());
    std::list<MouseEvent> mouseEvents;
    mouseEvents.push_back(mouseEvent);
    context_->mouseEvents_[frameNode] = mouseEvents;

    /**
     * @tc.steps2: Call the function FlushMouseEventInVsync.
     * @tc.expected: Test the stability of the function under various member conditions.
     */
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(mouseEvent);
    context_->mouseEvents_.clear();
    context_->lastMouseEvent_->mockFlushEvent = false;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->mouseEvents_.clear();
    context_->lastMouseEvent_->mockFlushEvent = true;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->mouseEvents_[frameNode] = mouseEvents;
    context_->lastMouseEvent_->mockFlushEvent = true;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->isTransFlag_ = false;
    context_->lastMouseEvent_->mockFlushEvent = false;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->isTransFlag_ = false;
    context_->lastMouseEvent_->mockFlushEvent = true;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->isTransFlag_ = false;
    context_->mouseEvents_.clear();
    context_->lastMouseEvent_->mockFlushEvent = false;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->isTransFlag_ = false;
    context_->mouseEvents_.clear();
    context_->lastMouseEvent_->mockFlushEvent = true;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);

    context_->lastMouseEvent_ = nullptr;
    context_->FlushMouseEventInVsync();
    EXPECT_EQ(context_->isNeedFlushMouseEvent_, MockFlushEventType::NONE);
}

/**
 * @tc.name: PipelineContextTestNg156
 * @tc.desc: Test SetDisplayWindowRectInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg156, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function SetDisplayWindowRectInfo.
     * @tc.expected: Test setting the member displayWindowRectInfo_ under various conditions.
     */
    ASSERT_NE(context_, nullptr);
    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    Rect displayWindowRectInfo(100.0, 100.0, 0.0, 0.0);
    context_->displayWindowRectInfo_.SetRect(50.0, 50.0, 0.0, 0.0);
    context_->lastMouseEvent_ = std::make_unique<MouseEvent>(mouseEvent);
    context_->lastMouseEvent_->x = 10;
    context_->lastMouseEvent_->y = 10;
    context_->SetDisplayWindowRectInfo(displayWindowRectInfo);
    EXPECT_NE(context_->lastMouseEvent_->x, 10);

    context_->displayWindowRectInfo_.SetRect(100.0, 50.0, 0.0, 0.0);
    context_->SetDisplayWindowRectInfo(displayWindowRectInfo);
    EXPECT_NE(context_->lastMouseEvent_->x, 10);

    context_->displayWindowRectInfo_.SetRect(50.0, 100.0, 0.0, 0.0);
    context_->lastMouseEvent_ = nullptr;
    context_->SetDisplayWindowRectInfo(displayWindowRectInfo);
    EXPECT_FALSE(context_->lastMouseEvent_);

    context_->displayWindowRectInfo_.SetRect(100.0, 100.0, 0.0, 0.0);
    context_->SetDisplayWindowRectInfo(displayWindowRectInfo);
    EXPECT_FALSE(context_->lastMouseEvent_);
}

/**
 * @tc.name: PipelineContextTestNg157
 * @tc.desc: Test ScopedLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg157, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function ScopedLayout.
     * @tc.expected: Test the constructor and destructor of ScopedLayout.
     */
    ASSERT_NE(context_, nullptr);
    PipelineContext* pipeline = new PipelineContext();
    ScopedLayout scopedLayout(pipeline);
    PipelineContext* pipeline2 = nullptr;
    ScopedLayout scopedLayout2(pipeline2);
    EXPECT_EQ(scopedLayout.pipeline_, pipeline);
}

/**
 * @tc.name: PipelineContextTestNg158
 * @tc.desc: Test FlushModifierAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg158, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function FlushModifierAnimation.
     * @tc.expected: Test the parameter is less than the member variable.
     */
    ASSERT_NE(context_, nullptr);
    uint64_t nanoTimestamp = 0;
    context_->animationTimeStamp_ = context_->AdjustVsyncTimeStamp(nanoTimestamp) + 1;
    EXPECT_TRUE(context_->FlushModifierAnimation(nanoTimestamp));
}

/**
 * @tc.name: PipelineContextTestNg159
 * @tc.desc: Test CatchInteractiveAnimations.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg159, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function CatchInteractiveAnimations.
     * @tc.expected: Test the isInteractive_ member of navigationMgr_ is true.
     */
    ASSERT_NE(context_, nullptr);
    auto animationCallback = []() -> void {
        return;
    };
    context_->navigationMgr_->isInteractive_ = true;
    EXPECT_FALSE(context_->CatchInteractiveAnimations(animationCallback));

    /**
     * @tc.steps2: Call the function CatchInteractiveAnimations.
     * @tc.expected: Test the isInteractive_ member of navigationMgr_ is false.
     */
    context_->navigationMgr_->isInteractive_ = false;
    EXPECT_FALSE(context_->CatchInteractiveAnimations(animationCallback));
}

/**
 * @tc.name: PipelineContextTestNg160
 * @tc.desc: Test NotifyResponseRegionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg160, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function NotifyResponseRegionChanged.
     * @tc.expected: Test the member thpExtraMgr_ is not nullptr.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    context_->thpExtraMgr_ = AceType::MakeRefPtr<NG::THPExtraManagerImpl>();
    context_->NotifyResponseRegionChanged(rootNode);
    EXPECT_TRUE(context_->thpExtraMgr_);

    /**
     * @tc.steps2: Call the function NotifyResponseRegionChanged.
     * @tc.expected: Test the member thpExtraMgr_ is nullptr.
     */
    context_->thpExtraMgr_.Reset();
    context_->NotifyResponseRegionChanged(rootNode);
    EXPECT_FALSE(context_->thpExtraMgr_);
}

/**
 * @tc.name: PipelineContextTestNgDisableNotifyResponseRegionChanged
 * @tc.desc: Test DisableNotifyResponseRegionChanged.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNgDisableNotifyResponseRegionChanged, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function NotifyResponseRegionChanged.
     * @tc.expected: Test the member thpExtraMgr_ is not nullptr.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    context_->thpExtraMgr_ = AceType::MakeRefPtr<NG::THPExtraManagerImpl>();
    context_->NotifyResponseRegionChanged(rootNode);
    EXPECT_TRUE(context_->thpExtraMgr_);

    /**
     * @tc.steps2: Call the function DisableNotifyResponseRegionChanged.
     * @tc.expected: Test the member thpExtraMgr_ is nullptr.
     */
    context_->thpExtraMgr_.Reset();
    context_->DisableNotifyResponseRegionChanged();
    EXPECT_FALSE(context_->thpExtraMgr_);
}

/**
 * @tc.name: PipelineContextTestNg161
 * @tc.desc: Test StartFoldStatusDelayTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg161, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function StartFoldStatusDelayTask.
     * @tc.expected: Test the member foldStatusDelayTask_ is not nullptr.
     */
    ASSERT_NE(context_, nullptr);
    FoldStatus foldStatus = FoldStatus::EXPAND;
    std::function<void()> callback = []() {};
    CancelableCallback<void()> foldStatusDelayTask(std::move(callback));
    context_->foldStatusDelayTask_ = foldStatusDelayTask;
    context_->StartFoldStatusDelayTask(foldStatus);
    EXPECT_TRUE(foldStatusDelayTask);
}

/**
 * @tc.name: PipelineContextTestNg162
 * @tc.desc: Test RemoveChangedFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg162, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function RemoveChangedFrameNode.
     * @tc.expected: Test the member changedNodes_ is not empty.
     */
    ASSERT_NE(context_, nullptr);
    int32_t nodeId = 1;
    RefPtr<FrameNode> rootNode1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> rootNode2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> rootNode3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    context_->changedNodes_.push_back(rootNode1);
    context_->changedNodes_.push_back(rootNode2);
    context_->changedNodes_.push_back(rootNode3);
    context_->RemoveChangedFrameNode(nodeId);
    EXPECT_FALSE(context_->changedNodes_.empty());
}

/**
 * @tc.name: PipelineContextTestNg163
 * @tc.desc: Test AddChangedFrameNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg163, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function AddChangedFrameNode.
     * @tc.expected: Test the member changeInfoListeners_ is not empty and setting the node in changedNodes_.
     */
    ASSERT_NE(context_, nullptr);
    context_->changedNodes_.clear();
    RefPtr<FrameNode> rootNode1 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> rootNode2 = AceType::MakeRefPtr<FrameNode>("test2", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> rootNode3 = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> weakNode1 = AceType::WeakClaim(AceType::RawPtr(rootNode3));
    context_->changeInfoListeners_.push_back(rootNode1);
    context_->changedNodes_.push_back(rootNode1);
    context_->changedNodes_.push_back(rootNode2);
    EXPECT_TRUE(context_->AddChangedFrameNode(weakNode1));
    EXPECT_TRUE(context_->AddChangedFrameNode(weakNode1));
}

/**
 * @tc.name: PipelineContextTestNg164
 * @tc.desc: Test FlushFrameCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg164, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function FlushFrameCallback.
     * @tc.expected: Test the member frameCallbackFuncs_ is not empty.
     */
    ASSERT_NE(context_, nullptr);
    uint64_t nanoTimestamp = 1;
    FrameCallbackFunc callback = [](uint64_t nanoTimestamp) {
        return;
    };
    context_->frameCallbackFuncs_.push_back(callback);
    context_->FlushFrameCallback(nanoTimestamp);
    EXPECT_TRUE(context_->frameCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextTestNg165
 * @tc.desc: Test FlushFrameCallbackFromCAPI.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg165, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function FlushFrameCallbackFromCAPI.
     * @tc.expected: Test the member frameCallbackFuncsFromCAPI_ is not empty.
     */
    ASSERT_NE(context_, nullptr);
    uint64_t nanoTimestamp = 1;
    uint32_t frameCount = 1;
    FrameCallbackFuncFromCAPI frameCallback = [](uint64_t nanoTimestamp, uint32_t frameCount) {
        return;
    };
    context_->frameCallbackFuncsFromCAPI_.push_back(frameCallback);
    context_->FlushFrameCallbackFromCAPI(nanoTimestamp, frameCount);
    EXPECT_TRUE(context_->frameCallbackFuncsFromCAPI_.empty());
}

/**
 * @tc.name: PipelineContextTestNg166
 * @tc.desc: Test IsContainerModalVisible.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg166, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function IsContainerModalVisible.
     * @tc.expected: Test the member windowModal_ is not equal to CONTAINER_MODAL.
     */
    ASSERT_NE(context_, nullptr);
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    EXPECT_FALSE(context_->IsContainerModalVisible());
}

/**
 * @tc.name: PipelineContextTestNg167
 * @tc.desc: Test StopWindowAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg167, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function StopWindowAnimation.
     * @tc.expected: Test the member taskScheduler_ is empty.
     */
    ASSERT_NE(context_, nullptr);
    context_->StopWindowAnimation();
    EXPECT_FALSE(context_->isWindowAnimation_);

    /**
     * @tc.steps2: Call the function StopWindowAnimation.
     * @tc.expected: Test the member taskScheduler_ is not empty.
     */
    using PredictTask = std::function<void(int64_t, bool)>;
    PredictTask task = [](uint64_t value, bool flag) {
        return;
    };
    context_->taskScheduler_->AddPredictTask(std::move(task));
    context_->StopWindowAnimation();
    EXPECT_FALSE(context_->isWindowAnimation_);
}

/**
 * @tc.name: PipelineContextTestNg168
 * @tc.desc: Test GetWindowPaintRectWithoutMeasureAndLayout.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg168, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function GetWindowPaintRectWithoutMeasureAndLayout.
     * @tc.expected: Test the member windowModal_ is not equal to CONTAINER_MODAL.
     */
    ASSERT_NE(context_, nullptr);
    RectInt rect;
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    context_->GetWindowPaintRectWithoutMeasureAndLayout(rect);
    EXPECT_TRUE(context_->rootNode_);

    /**
     * @tc.steps2: Call the function GetWindowPaintRectWithoutMeasureAndLayout.
     * @tc.expected: Test the member windowModal_ is equal to CONTAINER_MODAL.
     */
    context_->windowModal_ = WindowModal::CONTAINER_MODAL;
    context_->GetWindowPaintRectWithoutMeasureAndLayout(rect);
    EXPECT_TRUE(context_->rootNode_);
}

/**
 * @tc.name: PipelineContextTestNg169
 * @tc.desc: Test DoKeyboardAvoidAnimate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg169, TestSize.Level1)
{
    /**
     * @tc.steps1: Call the function DoKeyboardAvoidAnimate.
     * @tc.expected: Test the member isDoKeyboardAvoidAnimate_ is false.
     */
    ASSERT_NE(context_, nullptr);
    KeyboardAnimationConfig keyboardAnimationConfig;
    float keyboardHeight = 0.0;
    context_->isDoKeyboardAvoidAnimate_ = false;
    std::function<void()> func = []() {
        context_->isDoKeyboardAvoidAnimate_ = true;
        return;
    };
    context_->DoKeyboardAvoidAnimate(keyboardAnimationConfig, keyboardHeight, func);
    EXPECT_TRUE(context_->isDoKeyboardAvoidAnimate_);
}

/**
 * @tc.name: PipelineContextTestNg170
 * @tc.desc: Test the function OnDrawCompleted.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg170, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call OnDrawCompleted function.
     * @tc.expected: weakFrontend_.Upgrade() is null.
     */
    ASSERT_NE(context_, nullptr);
    context_->OnDrawCompleted(TEST_TAG);
    EXPECT_EQ(context_->weakFrontend_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg171
 * @tc.desc: Test the function StartWindowSizeChangeAnimate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg171, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call OnDrawCompleted function.
     * @tc.expected: designWidthScale_ is equal to DEFAULT_DOUBLE1.
     */
    ASSERT_NE(context_, nullptr);
    WindowSizeChangeReason type = WindowSizeChangeReason::FULL_TO_SPLIT;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, type);
    EXPECT_EQ(context_->designWidthScale_, DEFAULT_DOUBLE1);

    /**
     * @tc.steps2: type is MAXIMIZE_TO_SPLIT and call OnDrawCompleted function.
     * @tc.expected: designWidthScale_ is equal to DEFAULT_DOUBLE1.
     */
    type = WindowSizeChangeReason::MAXIMIZE_TO_SPLIT;
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, type);
    EXPECT_EQ(context_->designWidthScale_, DEFAULT_DOUBLE1);

    /**
     * @tc.steps3: type is ROTATION and call OnDrawCompleted function.
     * @tc.expected: designWidthScale_ is equal to DEFAULT_DOUBLE1.
     */
    type = WindowSizeChangeReason::ROTATION;
    context_->SetTextFieldManager(nullptr);
    context_->StartWindowSizeChangeAnimate(DEFAULT_INT3, DEFAULT_INT3, type);
    EXPECT_EQ(context_->designWidthScale_, DEFAULT_DOUBLE1);
}

/**
 * @tc.name: PipelineContextTestNg172
 * @tc.desc: Test the function UpdateSystemSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg172, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    SafeAreaInsets::Inset left { 0, 1 };
    SafeAreaInsets::Inset top { 0, 2 };
    SafeAreaInsets::Inset right { 0, 3 };
    SafeAreaInsets::Inset bottom { 0, 4 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);
    bool checkSceneBoardWindow = true;

    /**
     * @tc.steps2: call UpdateSystemSafeArea function.
     * @tc.expected: scbSystemSafeArea_ is equal to safeAreaInsets.
     */
    context_->UpdateSystemSafeArea(safeAreaInsets, checkSceneBoardWindow);
    EXPECT_EQ(context_->safeAreaManager_->scbSystemSafeArea_, safeAreaInsets);

    /**
     * @tc.steps3: call UpdateCutoutSafeArea function.
     * @tc.expected: scbCutoutSafeArea_ is not equal to safeAreaInsets.
     */
    context_->UpdateCutoutSafeArea(safeAreaInsets, checkSceneBoardWindow);
    EXPECT_NE(context_->safeAreaManager_->scbCutoutSafeArea_, safeAreaInsets);

    /**
     * @tc.steps4: call UpdateNavSafeArea function.
     * @tc.expected: scbNavSafeArea_ is equal to safeAreaInsets.
     */
    context_->UpdateNavSafeArea(safeAreaInsets, checkSceneBoardWindow);
    EXPECT_EQ(context_->safeAreaManager_->scbNavSafeArea_, safeAreaInsets);
}

/**
 * @tc.name: PipelineContextTestNg173
 * @tc.desc: Test the function UpdateCutoutSafeArea.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg173, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    SafeAreaInsets::Inset left { 0, 0 };
    SafeAreaInsets::Inset top { 0, 0 };
    SafeAreaInsets::Inset right { 0, 0 };
    SafeAreaInsets::Inset bottom { 0, 0 };
    SafeAreaInsets safeAreaInsets(left, top, right, bottom);

    /**
     * @tc.steps2: minPlatformVersion_ is 10 and call UpdateCutoutSafeArea function.
     * @tc.expected: cutoutSafeArea_ is equal to safeAreaInsets.
     */
    context_->SetMinPlatformVersion(10);
    context_->UpdateCutoutSafeArea(safeAreaInsets);
    EXPECT_EQ(context_->safeAreaManager_->cutoutSafeArea_, safeAreaInsets);

    /**
     * @tc.steps3: minPlatformVersion_ is 10 and call UpdateNavSafeArea function.
     * @tc.expected: navSafeArea_ is equal to safeAreaInsets.
     */
    context_->UpdateNavSafeArea(safeAreaInsets);
    EXPECT_EQ(context_->safeAreaManager_->navSafeArea_, safeAreaInsets);
}

/**
 * @tc.name: PipelineContextTestNg174
 * @tc.desc: Test the function SetEnableKeyBoardAvoidMode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg174, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call SetEnableKeyBoardAvoidMode function.
     * @tc.expected: keyboardSafeAreaEnabled_ is false.
     */
    ASSERT_NE(context_, nullptr);
    KeyBoardAvoidMode keyBoardAvoidMode = KeyBoardAvoidMode::OFFSET;
    context_->SetEnableKeyBoardAvoidMode(keyBoardAvoidMode);
    EXPECT_FALSE(context_->GetSafeAreaManager()->KeyboardSafeAreaEnabled());

    /**
     * @tc.steps2: call SetEnableKeyBoardAvoidMode function.
     * @tc.expected: isFullScreen_ is false.
     */
    context_->SetIsLayoutFullScreen(false);
    EXPECT_FALSE(context_->GetSafeAreaManager()->isFullScreen_);

    /**
     * @tc.steps3: call SetIsNeedAvoidWindow function.
     * @tc.expected: isNeedAvoidWindow_ is false.
     */
    context_->SetIsNeedAvoidWindow(false);
    EXPECT_FALSE(context_->GetSafeAreaManager()->isNeedAvoidWindow_);
}

/**
 * @tc.name: PipelineContextTestNg175
 * @tc.desc: Test the function DetachNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg175, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call DetachNode function.
     * @tc.expected: focusNode_ is not equal to frameNode_.
     */
    ASSERT_NE(context_, nullptr);
    context_->focusNode_ = frameNode_;
    frameNode_->SetPrivacySensitive(true);
    context_->DetachNode(frameNode_);
    EXPECT_NE(context_->focusNode_, frameNode_);
}

/**
 * @tc.name: PipelineContextTestNg176
 * @tc.desc: Test the function MarkDirtyOverlay.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg176, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call MarkDirtyOverlay function.
     * @tc.expected: rootNode_->GetChildren().size() is 1.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<FrameNode> child = FrameNode::CreateFrameNode(V2::POPUP_ETS_TAG, 0, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_->children_.clear();
    context_->rootNode_->AddChild(child);
    context_->MarkDirtyOverlay();
    EXPECT_EQ(context_->rootNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: PipelineContextTestNg177
 * @tc.desc: Test the function FlushDirtyPropertyNodesWhenExist.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg177, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushDirtyPropertyNodesWhenExist function.
     * @tc.expected: dirtyPropertyNodes_.size() is 0.
     */
    ASSERT_NE(context_, nullptr);
    context_->FlushDirtyPropertyNodesWhenExist();
    EXPECT_EQ(context_->dirtyPropertyNodes_.size(), 0);

    /**
     * @tc.steps2: dirtyPropertyNodes_ is not null and call FlushDirtyPropertyNodesWhenExist function.
     * @tc.expected: dirtyPropertyNodes_.size() is 0.
     */
    context_->dirtyPropertyNodes_.emplace(frameNode_);
    context_->taskScheduler_->SetIsLayouting(false);
    context_->FlushDirtyPropertyNodesWhenExist();
    EXPECT_EQ(context_->dirtyPropertyNodes_.size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg178
 * @tc.desc: Test the function CalcAvoidOffset.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg178, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call CalcAvoidOffset function.
     * @tc.expected: result is 0.0f.
     */
    ASSERT_NE(context_, nullptr);
    float keyboardHeight = 0.0f;
    float positionY = 0.0f;
    float height = 0.0f;
    SizeF rootSize(100.0f, 100.0f);
    float result = context_->CalcAvoidOffset(keyboardHeight, positionY, height, rootSize);
    EXPECT_EQ(result, 0.0f);

    /**
     * @tc.steps2: positionY is 10.0f and call CalcAvoidOffset function.
     * @tc.expected: result is -20.0f.
     */
    positionY = 10.0f;
    height = 10.0f;
    keyboardHeight = 100.0f;
    result = context_->CalcAvoidOffset(keyboardHeight, positionY, height, rootSize);
    EXPECT_EQ(result, -20.0f);

    /**
     * @tc.steps3: positionY is 100.0f and call CalcAvoidOffset function.
     * @tc.expected: result is 0.0f.
     */
    positionY = 100.0f;
    height = 20.0f;
    keyboardHeight = -100.0f;
    result = context_->CalcAvoidOffset(keyboardHeight, positionY, height, rootSize);
    EXPECT_EQ(result, 0.0f);

    /**
     * @tc.steps4: positionY is 80.0f and call CalcAvoidOffset function.
     * @tc.expected: result is 0.0f.
     */
    positionY = 80.0f;
    height = -100.0f;
    result = context_->CalcAvoidOffset(keyboardHeight, positionY, height, rootSize);
    EXPECT_EQ(result, 0.0f);
}

/**
 * @tc.name: PipelineContextTestNg179
 * @tc.desc: Test the function FindNavigationNodeToHandleBack.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg179, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    auto node = NavigationGroupNode::GetOrCreateGroupNode(
        TEST_TAG, nodeId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    node->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto childNode1 = NavigationGroupNode::GetOrCreateGroupNode(
        TEST_TAG, 0, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto childNode2 = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 1, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    childNode1->isActive_ = true;
    childNode2->isActive_ = true;
    node->AddChild(childNode1);
    node->AddChild(childNode2);
    node->AddChild(nullptr);
    bool isEntry = false;

    /**
     * @tc.steps2: call CalcAvoidOffset function.
     * @tc.expected: result is null.
     */
    RefPtr<FrameNode> result = context_->FindNavigationNodeToHandleBack(node, isEntry);
    EXPECT_EQ(result, nullptr);

    /**
     * @tc.steps3: isEntry is true and call CalcAvoidOffset function.
     * @tc.expected: result is null.
     */
    isEntry = true;
    childNode1->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    childNode2->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    result = context_->FindNavigationNodeToHandleBack(node, isEntry);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: PipelineContextTestNg180
 * @tc.desc: Test the function OnDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg180, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call OnDumpInfo function.
     * @tc.expected: result is true.
     */
    ASSERT_NE(context_, nullptr);
    std::vector<std::string> params;
    params.push_back("test");
    params.push_back("dcDepth_");
    params.push_back("dcDepth_10");
    context_->SetIsDynamicRender(true);
    bool result = context_->OnDumpInfo(params);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: PipelineContextTestNg181
 * @tc.desc: Test the function HandleSpecialContainerNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg181, TestSize.Level1)
{
    /**
     * @tc.steps1: containerDeleteFlag_ is true and call HandleSpecialContainerNode function.
     * @tc.expected: positionZNodes_ is null.
     */
    ASSERT_NE(context_, nullptr);
    SystemProperties::containerDeleteFlag_ = true;
    context_->HandleSpecialContainerNode();
    EXPECT_EQ(context_->GetPositionZNodes().size(), 0);

    /**
     * @tc.steps2: initialize parameters and call HandleSpecialContainerNode function.
     * @tc.expected: element is false and positionZNodes_ is null.
     */
    RefPtr<FrameNode> parentNode = FrameNode::CreateFrameNode("parent", 0, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode1 = FrameNode::CreateFrameNode("test1", 1, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> frameNode2 = FrameNode::CreateFrameNode("test2", 2, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> overlayNode = FrameNode::CreateFrameNode("overlayNode", 3, AceType::MakeRefPtr<Pattern>());
    RefPtr<FrameNode> focusPaintNode = FrameNode::CreateFrameNode("overlayNode", 4, AceType::MakeRefPtr<Pattern>());
    auto element = ElementRegister::GetInstance()->AddReferenced(1, frameNode1);
    element = ElementRegister::GetInstance()->AddReferenced(2, frameNode2);
    EXPECT_FALSE(element);
    frameNode2->SetParent(parentNode);
    context_->AddPositionZNode(-1);
    context_->AddPositionZNode(1);
    context_->AddPositionZNode(2);
    context_->HandleSpecialContainerNode();
    EXPECT_EQ(context_->GetPositionZNodes().size(), 0);

    /**
     * @tc.steps3: overlayNode and focusPaintNode are not null, call HandleSpecialContainerNode function.
     * @tc.expected: element is false and positionZNodes_ is null.
     */
    context_->AddPositionZNode(2);
    parentNode->SetOverlayNode(overlayNode);
    parentNode->SetFocusPaintNode(focusPaintNode);
    parentNode->renderContext_ = nullptr;
    context_->HandleSpecialContainerNode();
    EXPECT_EQ(context_->GetPositionZNodes().size(), 0);

    /**
     * @tc.steps4: renderContext_ is null and call HandleSpecialContainerNode function.
     * @tc.expected: element is false and positionZNodes_ is null.
     */
    context_->AddPositionZNode(2);
    overlayNode->renderContext_ = nullptr;
    focusPaintNode->renderContext_ = nullptr;
    context_->HandleSpecialContainerNode();
    EXPECT_EQ(context_->GetPositionZNodes().size(), 0);
}

/**
 * @tc.name: PipelineContextTestNg182
 * @tc.desc: Test the function FlushMessages.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg182, TestSize.Level1)
{
    /**
     * @tc.steps1: isFreezeFlushMessage_ is true and call FlushMessages function.
     * @tc.expected: isFreezeFlushMessage_ is false.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetIsFreezeFlushMessage(true);
    context_->FlushMessages();
    EXPECT_FALSE(context_->IsFreezeFlushMessage());

    /**
     * @tc.steps2: navigationMgr_ is null and call FlushMessages function.
     * @tc.expected: isFreezeFlushMessage_ is false.
     */
    context_->navigationMgr_ = nullptr;
    context_->FlushMessages();
    EXPECT_FALSE(context_->IsFreezeFlushMessage());
}

/**
 * @tc.name: PipelineContextTestNg183
 * @tc.desc: Test the function FlushUITaskWithSingleDirtyNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg183, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushUITaskWithSingleDirtyNode function.
     * @tc.expected: singleDirtyNodesToFlush_.size() is 1.
     */
    RefPtr<FrameNode> node = FrameNode::CreateFrameNode("node", 0, AceType::MakeRefPtr<Pattern>());
    context_->taskScheduler_->SetIsLayouting(true);
    context_->FlushUITaskWithSingleDirtyNode(node);
    context_->FlushAfterLayoutCallbackInImplicitAnimationTask();
    EXPECT_EQ(context_->taskScheduler_->singleDirtyNodesToFlush_.size(), 1);
}

/**
 * @tc.name: PipelineContextTestNg184
 * @tc.desc: Test the function FlushFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg184, TestSize.Level1)
{
    /**
     * @tc.steps1: add dirty focus and call FlushFocus function.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    ASSERT_NE(context_, nullptr);
    context_->AddDirtyFocus(frameNode_);
    context_->FlushFocus();
    EXPECT_EQ(context_->dirtyFocusScope_.Upgrade(), nullptr);

    /**
     * @tc.steps2: set focus type to SCOPE and call FlushFocus function.
     * @tc.expected: The dirtyFocusNode_ is changed to nullptr.
     */
    auto eventHub = frameNode_->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto focusHub = eventHub->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    focusHub->SetFocusType(FocusType::SCOPE);
    context_->AddDirtyFocus(frameNode_);
    context_->FlushFocus();
    EXPECT_EQ(context_->dirtyFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg185
 * @tc.desc: Test the function FlushFocusWithNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg185, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushFocusWithNode function.
     * @tc.expected: singleDirtyNodesToFlush_.size() is 1.
     */
    ASSERT_NE(context_, nullptr);
    RefPtr<FrameNode> focusNode = FrameNode::CreateFrameNode("focusNode", 0, AceType::MakeRefPtr<Pattern>());
    bool isScope = true;
    context_->FlushFocusWithNode(focusNode, isScope);
    EXPECT_EQ(context_->dirtyFocusNode_.Upgrade(), nullptr);
}

/**
 * @tc.name: PipelineContextTestNg186
 * @tc.desc: Test the function FlushFrameRate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg186, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call FlushFrameRate function.
     * @tc.expected: lastAnimatorExpectedFrameRate_ is -1.
     */
    ASSERT_NE(context_, nullptr);
    context_->lastAnimatorExpectedFrameRate_ = 0;
    context_->FlushFrameRate();
    EXPECT_EQ(context_->lastAnimatorExpectedFrameRate_, -1);

    /**
     * @tc.steps2: isRateChanged_ is true and call FlushFrameRate function.
     * @tc.expected: isRateChanged_ is true is false and lastAnimatorExpectedFrameRate_ is -1.
     */
    context_->frameRateManager_->SetIsRateChanged(true);
    context_->FlushFrameRate();
    EXPECT_EQ(context_->lastAnimatorExpectedFrameRate_, -1);
    EXPECT_FALSE(context_->frameRateManager_->IsRateChanged());
}

/**
 * @tc.name: PipelineContextTestNg187
 * @tc.desc: Test the function StartWindowSizeChangeAnimate.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg187, TestSize.Level1)
{
    /**
     * @tc.steps1: type is FULL_TO_SPLIT and call StartWindowSizeChangeAnimate function.
     * @tc.expected: designWidthScale_ not change.
     */
    ASSERT_NE(context_, nullptr);
    int32_t width = 0;
    int32_t height = 0;
    WindowSizeChangeReason type = WindowSizeChangeReason::FULL_TO_SPLIT;
    context_->StartWindowSizeChangeAnimate(width, height, type);
    EXPECT_EQ(context_->designWidthScale_, 1);

    /**
     * @tc.steps2: type is MAXIMIZE_TO_SPLIT and call StartWindowSizeChangeAnimate function.
     * @tc.expected: designWidthScale_ not change.
     */
    type = WindowSizeChangeReason::MAXIMIZE_TO_SPLIT;
    context_->StartWindowSizeChangeAnimate(width, height, type);
    EXPECT_EQ(context_->designWidthScale_, 1);
}

/**
 * @tc.name: PipelineContextTestNg188
 * @tc.desc: Test the function PostKeyboardAvoidTask.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg188, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters and call PostKeyboardAvoidTask function.
     * @tc.expected: laterAvoid is false.
     */
    ASSERT_NE(context_, nullptr);
    auto manager = AceType::MakeRefPtr<TextFieldManagerNG>();
    manager->SetLaterAvoid(true);
    context_->textFieldManager_ = manager;
    context_->PostKeyboardAvoidTask();
    EXPECT_FALSE(manager->GetLaterAvoid());

    /**
     * @tc.steps2: usingCustomKeyboardAvoid_ is true and call PostKeyboardAvoidTask function.
     * @tc.expected: laterAvoid is true.
     */
    manager->SetLaterAvoid(true);
    manager->SetUsingCustomKeyboardAvoid(true);
    context_->textFieldManager_ = manager;
    context_->PostKeyboardAvoidTask();
    EXPECT_TRUE(manager->GetLaterAvoid());
}

/**
 * @tc.name: PipelineContextTestNg189
 * @tc.desc: Test CompensatePointerMoveEventFromUnhandledEvents.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg189, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    DragPointerEvent event;
    event.pointerEventId = 1;
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    DragPointerEvent PointerEvent1;
    PointerEvent1.pointerEventId = 2;
    DragPointerEvent PointerEvent2;
    PointerEvent2.pointerEventId = 3;
    std::list<DragPointerEvent> dragEvents;
    dragEvents.push_back(PointerEvent1);
    dragEvents.push_back(PointerEvent2);
    context_->dragEvents_[rootNode] = dragEvents;

    /**
     * @tc.steps2: Call the function CompensatePointerMoveEventFromUnhandledEvents.
     * @tc.expected: Test the member dragEvents_ is not empty and The result is false.
     */
    EXPECT_FALSE(context_->CompensatePointerMoveEventFromUnhandledEvents(event, rootNode));

    /**
     * @tc.steps3: Call the function CompensatePointerMoveEventFromUnhandledEvents.
     * @tc.expected: Test The parameter rootNode2 is not in dragEvents_ and The result is false.
     */
    RefPtr<FrameNode> rootNode2 = AceType::MakeRefPtr<FrameNode>("test1", 1, AceType::MakeRefPtr<Pattern>());
    EXPECT_FALSE(context_->CompensatePointerMoveEventFromUnhandledEvents(event, rootNode2));

    /**
     * @tc.steps4: Push the event into dragEvents_.
     * @tc.expected: The result is TRUE.
     */
    context_->dragEvents_[rootNode].push_back(event);
    EXPECT_TRUE(context_->CompensatePointerMoveEventFromUnhandledEvents(event, rootNode));
}

/**
 * @tc.name: PipelineContextTestNg190
 * @tc.desc: Test AddFrameCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg190, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.let delayMillis is equal to 0;
     */
    ASSERT_NE(context_, nullptr);
    int64_t delayMillis = 0;
    FrameCallbackFunc frameCallbackFunc2 = nullptr;
    IdleCallbackFunc idleCallbackFunc2 = nullptr;

    /**
     * @tc.steps2:
     * Test the parameters frameCallbackFunc and idleCallbackFunc are nullptr, and delayMillis is equal to 0.
     * @tc.expected: The member frameCallbackFuncs_ is empty
     */
    context_->AddFrameCallback(std::move(frameCallbackFunc2), std::move(idleCallbackFunc2), delayMillis);
    EXPECT_TRUE(context_->frameCallbackFuncs_.empty());
    FrameCallbackFunc frameCallbackFunc = [](uint64_t nanoTimestamp) {
        return;
    };
    IdleCallbackFunc idleCallbackFunc = [](uint64_t nanoTimestamp, uint32_t frameCount) {
        return;
    };

    /**
     * @tc.steps3:
     * Test the parameters frameCallbackFunc and idleCallbackFunc are not nullptr, and delayMillis is equal to 0.
     * @tc.expected: The member frameCallbackFuncs_ is not empty
     */
    context_->AddFrameCallback(std::move(frameCallbackFunc), std::move(idleCallbackFunc), delayMillis);
    EXPECT_FALSE(context_->frameCallbackFuncs_.empty());

    /**
     * @tc.steps4:
     * Test the parameters frameCallbackFunc and idleCallbackFunc are nullptr, and delayMillis is granter than 0.
     * @tc.expected: The member frameCallbackFuncs_ is empty
     */
    delayMillis = 1;
    context_->frameCallbackFuncs_.clear();
    context_->AddFrameCallback(std::move(frameCallbackFunc2), std::move(idleCallbackFunc2), delayMillis);
    EXPECT_TRUE(context_->frameCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextTestNg191
 * @tc.desc: Test AddCAPIFrameCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg191, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    FrameCallbackFuncFromCAPI frameCallbackFuncFromCAPI = [](uint64_t nanoTimestamp, uint32_t frameCount) {
        return;
    };

    /**
     * @tc.steps2:
     * Test the parameters frameCallbackFuncFromCAPI is not nullptr.
     * @tc.expected: The member frameCallbackFuncFromCAPI is not empty
     */
    context_->AddCAPIFrameCallback(std::move(frameCallbackFuncFromCAPI));
    EXPECT_FALSE(context_->frameCallbackFuncsFromCAPI_.empty());

    /**
     * @tc.steps3:
     * Test the parameters frameCallbackFuncFromCAPI is nullptr.
     * @tc.expected: The member frameCallbackFuncFromCAPI is empty
     */
    frameCallbackFuncFromCAPI = nullptr;
    context_->frameCallbackFuncsFromCAPI_.clear();
    context_->AddCAPIFrameCallback(std::move(frameCallbackFuncFromCAPI));
    EXPECT_TRUE(context_->frameCallbackFuncsFromCAPI_.empty());
}

/**
 * @tc.name: PipelineContextTestNg192
 * @tc.desc: Test TriggerIdleCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg192, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    IdleCallbackFunc callback = [](uint64_t nanoTimestamp, uint32_t frameCount) {
        return;
    };
    /**
     * @tc.steps2:
     * Test the parameters deadline is near to currentTime.
     * @tc.expected: The member idleCallbackFuncs_ is not empty
     */
    context_->idleCallbackFuncs_.push_back(callback);
    int64_t deadline = GetSysTimestamp();
    context_->TriggerIdleCallback(deadline);
    EXPECT_FALSE(context_->idleCallbackFuncs_.empty());

    /**
     * @tc.steps3:
     * Test current time is less than the minimum idle time.
     * @tc.expected: The member idleCallbackFuncs_ is not empty
     */
    context_->idleCallbackFuncs_.push_back(callback);
    deadline = GetSysTimestamp() + 10000;
    context_->TriggerIdleCallback(deadline);
    EXPECT_TRUE(context_->idleCallbackFuncs_.empty());
}

/**
 * @tc.name: PipelineContextTestNg193
 * @tc.desc: Test EnableContainerModalGesture.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg193, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    ASSERT_NE(context_, nullptr);
    bool isEnable = 0;
    RefPtr<UINode> node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_->children_.push_front(node);

    /**
     * @tc.steps2:
     * Call function EnableContainerModalGesture.
     * @tc.expected: children.front() is not nullptr
     */
    context_->EnableContainerModalGesture(isEnable);
    EXPECT_TRUE(AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front()));

    context_->rootNode_->children_.clear();
    node.Reset();
    context_->rootNode_->children_.push_front(node);

    /**
     * @tc.steps3:
     * Call function EnableContainerModalGesture.
     * @tc.expected: children.front() is nullptr
     */
    context_->EnableContainerModalGesture(isEnable);
    EXPECT_FALSE(AceType::DynamicCast<FrameNode>(context_->rootNode_->GetChildren().front()));

    context_->rootNode_->children_.clear();

    /**
     * @tc.steps4:
     * Call function EnableContainerModalGesture.
     * @tc.expected: children is empty
     */
    context_->EnableContainerModalGesture(isEnable);
    EXPECT_TRUE(context_->rootNode_->GetChildren().empty());
}

/**
 * @tc.name: PipelineContextTestNg194
 * @tc.desc: Test SetCursor.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg194, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.let delayMillis is less than 0;
     * @tc.expected: The isUserSetCursor_ is false
     */
    ASSERT_NE(context_, nullptr);
    int32_t cursorValue = -1;
    context_->SetCursor(cursorValue);
    EXPECT_FALSE(context_->eventManager_->GetMouseStyleManager()->userSetCursor_);

    /**
     * @tc.steps2: let delayMillis is greater than RUNNING;
     * @tc.expected: The isUserSetCursor_ is false
     */
    cursorValue = static_cast<int32_t>(MouseFormat::ALIAS);
    context_->SetCursor(cursorValue);
    EXPECT_FALSE(context_->eventManager_->GetMouseStyleManager()->userSetCursor_);

    /**
     * @tc.steps3: let delayMillis is greater than 0 and less than RUNNING;
     * @tc.expected: The isUserSetCursor_ is true
     */
    cursorValue = 10;
    context_->SetCursor(cursorValue);
    EXPECT_TRUE(context_->eventManager_->GetMouseStyleManager()->userSetCursor_);
}

/**
 * @tc.name: PipelineContextTestNg195
 * @tc.desc: Test FlushWindowActivateChangedCallback.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg195, TestSize.Level1)
{
    /**
     * @tc.steps1: Call function FlushWindowActivateChangedCallback;
     * @tc.expected: The onWindowActivateChangedCallbacks_ is empty
     */
    ASSERT_NE(context_, nullptr);
    bool isActivate = false;
    context_->onWindowActivateChangedCallbacks_.clear();
    context_->FlushWindowActivateChangedCallback(isActivate);
    EXPECT_TRUE(context_->onWindowActivateChangedCallbacks_.empty());

    /**
     * @tc.steps2: Call function FlushWindowActivateChangedCallback;
     * @tc.expected: The onWindowActivateChangedCallbacks_ is empty
     */
    context_->onWindowActivateChangedCallbacks_.insert(10);
    context_->FlushWindowActivateChangedCallback(isActivate);
    EXPECT_TRUE(context_->onWindowActivateChangedCallbacks_.empty());

    /**
     * @tc.steps3: Call function FlushWindowActivateChangedCallback;
     * @tc.expected: The onWindowActivateChangedCallbacks_ is not empty
     */
    context_->onWindowActivateChangedCallbacks_.insert(10);
    ElementIdType elmtId = 10;
    RefPtr<FrameNode> rootNode = AceType::MakeRefPtr<FrameNode>("test3", 3, AceType::MakeRefPtr<Pattern>());
    WeakPtr<FrameNode> referenced = AceType::WeakClaim(AceType::RawPtr(rootNode));
    ElementRegister::GetInstance()->AddReferenced(elmtId, referenced);
    context_->FlushWindowActivateChangedCallback(isActivate);
    EXPECT_TRUE(!context_->onWindowActivateChangedCallbacks_.empty());

    /**
     * @tc.steps4: Call function FlushWindowActivateChangedCallback;
     * @tc.expected: The onWindowActivateChangedCallbacks_ is not empty
     */
    isActivate = true;
    context_->FlushWindowActivateChangedCallback(isActivate);
    EXPECT_TRUE(!context_->onWindowActivateChangedCallbacks_.empty());
}

/**
 * @tc.name: PipelineContextTestNg196
 * @tc.desc: Test SetIsWindowSizeDragging.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg196, TestSize.Level1)
{
    /**
     * @tc.steps1: Call function SetIsWindowSizeDragging;
     * @tc.expected: The isWindowSizeDragging_ is true
     */
    ASSERT_NE(context_, nullptr);
    bool isDragging = true;
    context_->SetIsWindowSizeDragging(isDragging);
    EXPECT_TRUE(context_->isWindowSizeDragging_);

    /**
     * @tc.steps2: Call function SetIsWindowSizeDragging;
     * @tc.expected: The isWindowSizeDragging_ is false and onWindowSizeDragEndCallbacks_ is empty
     */
    isDragging = false;
    std::function<void()> callback = nullptr;
    context_->onWindowSizeDragEndCallbacks_.clear();
    context_->AddWindowSizeDragEndCallback(std::move(callback));
    context_->SetIsWindowSizeDragging(isDragging);
    EXPECT_FALSE(context_->isWindowSizeDragging_);

    /**
     * @tc.steps3: Call function SetIsWindowSizeDragging;
     * @tc.expected: The isWindowSizeDragging_ is false and onWindowSizeDragEndCallbacks_ is not empty
     */
    callback = []() {
        return;
    };
    context_->onWindowSizeDragEndCallbacks_.clear();
    context_->AddWindowSizeDragEndCallback(std::move(callback));
    isDragging = false;
    context_->SetIsWindowSizeDragging(isDragging);
    EXPECT_FALSE(context_->isWindowSizeDragging_);
}

/**
 * @tc.name: PipelineContextTestNg198
 * @tc.desc: Test UpdateFormLinkInfos.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg198, TestSize.Level1)
{
    /**
     * @tc.steps1: Call function UpdateFormLinkInfos;
     * @tc.expected: The formLinkInfoUpdateHandler_ is nullptr
     */
    ASSERT_NE(context_, nullptr);
    context_->UpdateFormLinkInfos();
    EXPECT_EQ(context_->formLinkInfoUpdateHandler_, nullptr);

    /**
     * @tc.steps2: Call function UpdateFormLinkInfos;
     * @tc.expected: The formLinkInfoMap_ is empty
     */
    std::string info = "test";
    context_->formLinkInfoMap_[1] = info;
    context_->UpdateFormLinkInfos();
    EXPECT_FALSE(context_->formLinkInfoMap_.empty());

    /**
     * @tc.steps3: Call function UpdateFormLinkInfos;
     * @tc.expected: The formLinkInfoUpdateHandler_ is not nullptr
     */
    std::function<void(const std::vector<std::string>&)>
        formLinkInfoUpdateHandler = [](const std::vector<std::string> hander) {
        return;
    };
    context_->SetFormLinkInfoUpdateHandler(std::move(formLinkInfoUpdateHandler));
    context_->UpdateFormLinkInfos();
    EXPECT_NE(context_->formLinkInfoUpdateHandler_, nullptr);

    /**
     * @tc.steps4: Call function UpdateFormLinkInfos;
     * @tc.expected: The formLinkInfoMap_ is not empty
     */
    context_->formLinkInfoMap_.clear();
    context_->UpdateFormLinkInfos();
    EXPECT_TRUE(context_->formLinkInfoMap_.empty());
}

/**
 * @tc.name: PipelineContextTestNg199
 * @tc.desc: Test ContainerModalUnFocus.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg199, TestSize.Level1)
{
    /**
     * @tc.steps1: Call function RequireSummary;
     * @tc.expected: The windowModal_ is not equal to CONTAINER_MODAL
     */
    ASSERT_NE(context_, nullptr);
    context_->windowModal_ = WindowModal::DIALOG_MODAL;
    context_->ContainerModalUnFocus();
    EXPECT_TRUE(context_->windowModal_ != WindowModal::CONTAINER_MODAL);
}

/**
 * @tc.name: PipelineContextTestNg200
 * @tc.desc: Test the function OnDumpInfo.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg200, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: All pointer is non-null.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    std::unique_ptr<std::ostream> ostream = std::make_unique<std::ostringstream>();
    ASSERT_NE(ostream, nullptr);
    DumpLog::GetInstance().SetDumpFile(std::move(ostream));
    /**
     * @tc.steps2: init a vector with some string params and
                call OnDumpInfo with every param array.
     * @tc.expected: The return value is same as the expectation.
     */
    auto testJson = R"({"cmd":"changeIndex","params":{"index":0}} 6)";
    auto testErrorJson = R"({"cmd":"changeIndex","params":{"index":2}} -1)";
    std::vector<std::vector<std::string>> params = { { "-injection", testJson }, { "-injection", testErrorJson } };
    int turn = 0;
    for (; turn < params.size(); turn++) {
        EXPECT_TRUE(context_->OnDumpInfo(params[turn]));
    }
}

/**
 * @tc.name: PipelineContextTestNg300
 * @tc.desc: Test the function NotifyColorModeChange.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg300, TestSize.Level1)
{
    /**
     * @tc.steps1: Call Function NotifyColorModeChange.
     * @tc.expected: rootNode_->isDarkMode_ is false.
     */
    ASSERT_NE(context_, nullptr);
    uint32_t colorMode = static_cast<uint32_t>(ColorMode::LIGHT);
    context_->rootNode_->isDarkMode_ = false;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_FALSE(context_->rootNode_->isDarkMode_);

    context_->stageManager_->stageNode_->renderContext_ = nullptr;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_FALSE(context_->stageManager_->stageNode_->HasPositionProp());

    context_->stageManager_->stageNode_ = nullptr;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_EQ(context_->stageManager_->GetStageNode(), nullptr);

    context_->stageManager_ = nullptr;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_EQ(context_->GetStageManager(), nullptr);

    context_->rootNode_ = nullptr;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_EQ(context_->GetRootElement(), nullptr);
    context_->rootNode_ = frameNode_;
}

/* @tc.name: PipelineContextTestNg301
 * @tc.desc: Test SetBackgroundColorModeUpdated.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg301, TestSize.Level1)
{
    /**
     * @tc.steps1: check context_.
     * @tc.expected: context_ is nullptr.
     */
    ASSERT_NE(context_, nullptr);

    /**
     * @tc.steps2: SetBackgroundColorModeUpdated true.
     * @tc.expected: backgroundColorModeUpdated_ is true.
     */
    context_->SetBackgroundColorModeUpdated(true);
    EXPECT_TRUE(context_->backgroundColorModeUpdated_);

    /**
     * @tc.steps3: SetBackgroundColorModeUpdated false.
     * @tc.expected: backgroundColorModeUpdated_ is false.
     */
    context_->SetBackgroundColorModeUpdated(false);
    EXPECT_FALSE(context_->backgroundColorModeUpdated_);
}

/**
 * @tc.name: PipelineContextTestNg303
 * @tc.desc: Test the function OnMouseMoveEventForAxisEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg303, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     * @tc.expected: initialize pipeline, touch event.
     */
    ASSERT_NE(context_, nullptr);
    context_->SetEventManager(AceType::MakeRefPtr<EventManager>());
    TouchEvent touchEventOne;
    touchEventOne.id = 0;
    touchEventOne.type = TouchType::MOVE;
    TouchEvent touchEventTwo;
    touchEventTwo.id = 1;
    touchEventTwo.type = TouchType::MOVE;

    /**
     * @tc.steps2: Call the function CompensateTouchMoveEventBeforeDown.
     * @tc.expected: Test if this function is available and the events is consumed.
     */
    context_->CompensateTouchMoveEventBeforeDown();
    context_->touchEvents_.push_back(touchEventOne);
    context_->touchEvents_.push_back(touchEventTwo);
    context_->CompensateTouchMoveEventBeforeDown();
    EXPECT_TRUE(context_->touchEvents_.empty());
}

/**
 * @tc.name: PipelineContextTestNg400
 * @tc.desc: Test the function RegisterAttachedNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg400, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    RefPtr<UINode> node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    context_->RegisterAttachedNode(AceType::RawPtr(node));
    auto& attachedNodeSet = context_->attachedNodeSet_;
    bool found = false;
    for (const auto& uiNode : attachedNodeSet) {
        auto illegalNode = uiNode.Upgrade();
        if (illegalNode && illegalNode == node) {
            found = true;
            break;
        }
    }
    EXPECT_TRUE(found);
}

/**
 * @tc.name: PipelineContextTestNg401
 * @tc.desc: Test the function RemoveAttachedNode.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg401, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    RefPtr<UINode> node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    context_->RegisterAttachedNode(AceType::RawPtr(node));

    auto& attachedNodeSet = context_->attachedNodeSet_;
    auto AttachedNum = attachedNodeSet.size();
    context_->RemoveAttachedNode(AceType::RawPtr(node));
    EXPECT_EQ(AttachedNum, attachedNodeSet.size() + 1);
}

/**
 * @tc.name: PipelineContextTestNg402
 * @tc.desc: Test the function detaching node.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg402, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();

    RefPtr<UINode> node = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    node->AttachContext(AceType::RawPtr(context_), false);
    EXPECT_TRUE(context_->attachedNodeSet_.count(AceType::WeakClaim(AceType::RawPtr(node))));
    node->DetachContext(false);
    EXPECT_FALSE(context_->attachedNodeSet_.count(AceType::WeakClaim(AceType::RawPtr(node))));
}

/**
 * @tc.name: PipelineContextTestNg300
 * @tc.desc: Test the function NotifyColorModeChange.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg403, TestSize.Level1)
{
    /**
     * @tc.steps1: Call Function NotifyColorModeChange.
     * @tc.expected: context_->instanceId_ == Container::CurrentIdSafely().
     */
    ASSERT_NE(context_, nullptr);
    uint32_t colorMode = static_cast<uint32_t>(ColorMode::LIGHT);
    context_->rootNode_->isDarkMode_ = false;
    context_->NotifyColorModeChange(colorMode);
    EXPECT_EQ(context_->instanceId_, Container::CurrentIdSafely());
}

/**
 * @tc.name: PipelineContextTestNg404
 * @tc.desc: Test the function NotifyColorModeChange.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextTestNg, PipelineContextTestNg404, TestSize.Level1)
{
    ASSERT_NE(context_, nullptr);
    context_->SetupRootElement();
    auto node = FrameNode::GetOrCreateFrameNode(TEST_TAG, frameNodeId_, nullptr);
    ASSERT_NE(node, nullptr);
    MouseEvent mouseEvent;
    mouseEvent.action = MouseAction::HOVER;
    context_->DispatchMouseToTouchEvent(mouseEvent, node);
    EXPECT_TRUE(context_->eventManager_->touchTestResults_.empty());
}
} // namespace NG
} // namespace OHOS::Ace
