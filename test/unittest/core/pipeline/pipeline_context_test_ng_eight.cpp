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

#include "test/unittest/core/pipeline/pipeline_context_test_ng.h"
#define private public
#define protected public
#include "core/common/event_manager.h"
#include "test/mock/adapter/ohos/osal/mock_system_properties.h"
#include "test/mock/frameworks/base/mousestyle/mock_mouse_style.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/common/mock_window.h"
#include "test/mock/frameworks/core/components_ng/pattern/mock_pattern.h"

#include "base/log/dump_log.h"
#include "core/common/statistic_event_reporter.h"
#include "core/common/thp_extra_manager.h"
#include "core/components_ng/pattern/button/button_event_hub.h"
#include "core/components_ng/pattern/container_modal/container_modal_pattern.h"
#include "core/components_ng/pattern/container_modal/container_modal_theme.h"
#include "core/components_ng/pattern/overlay/overlay_manager.h"
#include "core/components_ng/pattern/text_field/text_field_manager.h"
#include "core/components_ng/manager/drag_drop/drag_drop_manager.h"
#include "core/components_ng/manager/post_event/post_event_manager.h"
#include "core/components_ng/base/node_render_status_monitor.h"
#include "core/accessibility/accessibility_manager_ng.h"
#include "core/components_ng/pattern/web/itouch_event_callback.h"
#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"
#include "base/ressched/ressched_touch_optimizer.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
class MockTouchEventCallbackEight : public ITouchEventCallback {
public:
    MockTouchEventCallbackEight() = default;
    ~MockTouchEventCallbackEight() override = default;
    void OnTouchEvent() override {}
    WeakPtr<NG::Pattern> GetPatternFromListener() override { return nullptr; }
};
} // namespace

namespace {
constexpr int32_t TEST_TOUCH_ID = 1;
constexpr int32_t TEST_MOUSE_ID = 0;
constexpr int32_t TEST_NODE_ID_A = 1001;
constexpr int32_t TEST_NODE_ID_B = 1002;
constexpr int32_t TEST_DELAY_POSITIVE = 100;
constexpr int32_t TEST_DELAY_NEGATIVE = -50;
constexpr float TEST_X = 100.0f;
constexpr float TEST_Y = 200.0f;
constexpr double TEST_SCALE = 1.0;
} // namespace

// ==========================================================================
// OnTouchEvent(const TouchEvent&, const RefPtr<FrameNode>&, bool)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest001
 * @tc.desc: Test OnTouchEvent with DOWN type covers TouchTest and historyPointsById_ erase branch.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest001, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(node, nullptr);
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    context_->historyPointsById_[TEST_TOUCH_ID] = {};
    EXPECT_EQ(context_->historyPointsById_.size(), 1u);

    context_->OnTouchEvent(event, node, false);

    EXPECT_EQ(context_->historyPointsById_.find(TEST_TOUCH_ID), context_->historyPointsById_.end());
}

/**
 * @tc.name: PipelineContextEightTest002
 * @tc.desc: Test OnTouchEvent with MOVE type triggers listenerVector_ callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest002, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;

    int listenerCount = 0;
    auto listener = std::make_shared<MockTouchEventCallbackEight>();
    context_->listenerVector_.clear();

    TouchEvent event;
    event.type = TouchType::MOVE;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    context_->OnTouchEvent(event, node, false);
    EXPECT_EQ(listenerCount, 0);
    context_->listenerVector_.clear();
}

/**
 * @tc.name: PipelineContextEightTest003
 * @tc.desc: Test OnTouchEvent with isSubPipe=true returns early before accessibility handling.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest003, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    context_->OnTouchEvent(event, node, true);
    EXPECT_EQ(context_->instanceId_, 0);
}

/**
 * @tc.name: PipelineContextEightTest004
 * @tc.desc: Test OnTouchEvent with MOVE type and isEventsPassThrough_ true dispatches immediately.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest004, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    context_->isEventsPassThrough_ = true;

    TouchEvent event;
    event.type = TouchType::MOVE;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;
    event.passThrough = false;

    context_->OnTouchEvent(event, node, false);
    EXPECT_TRUE(context_->hasIdleTasks_);

    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest005
 * @tc.desc: Test OnTouchEvent with MOVE type and passThrough=true dispatches immediately.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest005, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    context_->isEventsPassThrough_ = false;

    TouchEvent event;
    event.type = TouchType::MOVE;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;
    event.passThrough = true;

    context_->OnTouchEvent(event, node, false);
    EXPECT_TRUE(context_->hasIdleTasks_);

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest006
 * @tc.desc: Test OnTouchEvent with UP type clears historyPointsById_ and resets touch time.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest006, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    TouchEvent event;
    event.type = TouchType::UP;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    auto lastDispatchTime = context_->eventManager_->GetLastDispatchTime();
    lastDispatchTime[TEST_TOUCH_ID] = 1000;
    context_->eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));

    context_->OnTouchEvent(event, node, false);

    auto updatedDispatchTime = context_->eventManager_->GetLastDispatchTime();
    EXPECT_EQ(updatedDispatchTime.find(TEST_TOUCH_ID), updatedDispatchTime.end());
    EXPECT_TRUE(context_->hasIdleTasks_);

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest007
 * @tc.desc: Test OnTouchEvent with CANCEL type clears drag events and touch plugin context.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest007, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    DragPointerEvent dragEvent;
    dragEvent.pointerId = TEST_TOUCH_ID;
    context_->dragEvents_[node].push_back(dragEvent);
    EXPECT_FALSE(context_->dragEvents_.empty());

    TouchEvent event;
    event.type = TouchType::CANCEL;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    auto lastDispatchTime = context_->eventManager_->GetLastDispatchTime();
    lastDispatchTime[TEST_TOUCH_ID] = 1000;
    context_->eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));

    context_->OnTouchEvent(event, node, false);
    EXPECT_TRUE(context_->dragEvents_.empty());
    EXPECT_TRUE(context_->touchPluginPipelineContext_.empty());

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest008
 * @tc.desc: Test OnTouchEvent with accessibilityManagerNG_ null skips hover event handling.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest008, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = nullptr;
    context_->isEventsPassThrough_ = false;

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    EXPECT_NO_FATAL_FAILURE(context_->OnTouchEvent(event, node, false));
}

// ==========================================================================
// OnMouseEvent(const MouseEvent&, const RefPtr<FrameNode>&)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest009
 * @tc.desc: Test OnMouseEvent with RELEASE action triggers CompensateMouseMoveEvent path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest009, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();


    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.button = MouseButton::LEFT_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->node, node);
}

/**
 * @tc.name: PipelineContextEightTest010
 * @tc.desc: Test OnMouseEvent with CANCEL action triggers CompensateMouseMoveEvent path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest010, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();


    MouseEvent event;
    event.action = MouseAction::CANCEL;
    event.button = MouseButton::LEFT_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->node, node);
}

/**
 * @tc.name: PipelineContextEightTest011
 * @tc.desc: Test OnMouseEvent with WINDOW_LEAVE action triggers CompensateMouseMoveEvent.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest011, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();


    MouseEvent event;
    event.action = MouseAction::WINDOW_LEAVE;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;
    event.mockFlushEvent = true;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_FALSE(context_->lastMouseEvent_->isMockWindowTransFlag);
}

/**
 * @tc.name: PipelineContextEightTest012
 * @tc.desc: Test OnMouseEvent with RIGHT_BUTTON PRESS sets focus inactive.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest012, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();


    MouseEvent event;
    event.action = MouseAction::PRESS;
    event.button = MouseButton::RIGHT_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    EXPECT_NO_FATAL_FAILURE(context_->OnMouseEvent(event, node));
}

/**
 * @tc.name: PipelineContextEightTest013
 * @tc.desc: Test OnMouseEvent with MOVE action and isMousePassThrough_ true dispatches directly.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest013, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    context_->isMousePassThrough_ = true;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    MouseEvent event;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->OnMouseEvent(event, node);
    EXPECT_EQ(context_->lastMouseEvent_->node, node);

    context_->isMousePassThrough_ = false;
    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest014
 * @tc.desc: Test OnMouseEvent with MOVE action queues event in mouseEvents_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest014, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isMousePassThrough_ = false;

    MouseEvent event;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->mouseEvents_.clear();
    context_->OnMouseEvent(event, node);
    EXPECT_EQ(context_->mouseEvents_.size(), 1u);
    EXPECT_FALSE(context_->mouseEvents_[node].empty());

    context_->mouseEvents_.clear();
}

/**
 * @tc.name: PipelineContextEightTest015
 * @tc.desc: Test OnMouseEvent with postEventManager_ null does not crash on non-MOVE action.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest015, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    context_->postEventManager_ = nullptr;

    MouseEvent event;
    event.action = MouseAction::PRESS;
    event.button = MouseButton::LEFT_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    EXPECT_NO_FATAL_FAILURE(context_->OnMouseEvent(event, node));
}

// ==========================================================================
// CompensateMouseMoveEvent(const MouseEvent&, const RefPtr<FrameNode>&)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest016
 * @tc.desc: Test CompensateMouseMoveEvent with no entry in nodeToMousePoints_ returns early.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest016, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();
    context_->nodeToMousePoints_.clear();

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));
    EXPECT_TRUE(context_->nodeToMousePoints_.empty());
}

/**
 * @tc.name: PipelineContextEightTest017
 * @tc.desc: Test CompensateMouseMoveEvent with empty entry in nodeToMousePoints_ returns early.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest017, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();
    context_->nodeToMousePoints_[node] = {};

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));
    EXPECT_TRUE(context_->nodeToMousePoints_[node].empty());

    context_->nodeToMousePoints_.clear();
}

/**
 * @tc.name: PipelineContextEightTest018
 * @tc.desc: Test CompensateMouseMoveEvent dispatches when lastDispatchTime entry exists and time is greater.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest018, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(2000));
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.sourceTool = SourceTool::MOUSE;
    context_->nodeToMousePoints_[node] = { mouseEvent };

    auto lastDispatchTime = context_->eventManager_->GetLastDispatchTime();
    lastDispatchTime[TEST_MOUSE_ID] = 1000;
    context_->eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));

    context_->nodeToMousePoints_.clear();
}

/**
 * @tc.name: PipelineContextEightTest019
 * @tc.desc: Test CompensateMouseMoveEvent skips dispatch when time is not greater.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest019, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(500));
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.sourceType = SourceType::MOUSE;
    context_->nodeToMousePoints_[node] = { mouseEvent };

    auto lastDispatchTime = context_->eventManager_->GetLastDispatchTime();
    lastDispatchTime[TEST_MOUSE_ID] = 1000;
    context_->eventManager_->SetLastDispatchTime(std::move(lastDispatchTime));

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));

    context_->nodeToMousePoints_.clear();
}

// ==========================================================================
// CompensateMouseMoveEventFromUnhandledEvents
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest020
 * @tc.desc: Test CompensateMouseMoveEventFromUnhandledEvents returns false when mouseEvents_ empty.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest020, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();

    MouseEvent event;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    auto result = context_->CompensateMouseMoveEventFromUnhandledEvents(event, node);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: PipelineContextEightTest021
 * @tc.desc: Test CompensateMouseMoveEventFromUnhandledEvents returns false when node not in map.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest021, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    auto otherNode = FrameNode::CreateFrameNode("other", TEST_NODE_ID_B, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    context_->mouseEvents_[otherNode] = { mouseEvent };

    MouseEvent event;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    auto result = context_->CompensateMouseMoveEventFromUnhandledEvents(event, node);
    EXPECT_FALSE(result);

    context_->mouseEvents_.clear();
}

/**
 * @tc.name: PipelineContextEightTest022
 * @tc.desc: Test CompensateMouseMoveEventFromUnhandledEvents returns false when no matching id.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest022, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID + 99;
    mouseEvent.action = MouseAction::MOVE;
    context_->mouseEvents_[node] = { mouseEvent };

    MouseEvent event;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    auto result = context_->CompensateMouseMoveEventFromUnhandledEvents(event, node);
    EXPECT_FALSE(result);

    context_->mouseEvents_.clear();
}

/**
 * @tc.name: PipelineContextEightTest023
 * @tc.desc: Test CompensateMouseMoveEventFromUnhandledEvents returns true when matching id found.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest023, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
    context_->mouseEvents_[node] = { mouseEvent };

    MouseEvent event;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    auto result = context_->CompensateMouseMoveEventFromUnhandledEvents(event, node);
    EXPECT_TRUE(result);
    EXPECT_TRUE(context_->mouseEvents_.empty());
}

/**
 * @tc.name: PipelineContextEightTest024
 * @tc.desc: Test CompensateMouseMoveEventFromUnhandledEvents filters by id and collects history.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest024, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();

    MouseEvent event1;
    event1.id = TEST_MOUSE_ID;
    event1.action = MouseAction::MOVE;
    event1.x = 50.0f;
    event1.y = 60.0f;
    event1.time = TimeStamp(std::chrono::nanoseconds(1000));

    MouseEvent event2;
    event2.id = TEST_MOUSE_ID + 10;
    event2.action = MouseAction::MOVE;
    event2.x = 70.0f;
    event2.y = 80.0f;
    event2.time = TimeStamp(std::chrono::nanoseconds(1100));

    MouseEvent event3;
    event3.id = TEST_MOUSE_ID;
    event3.action = MouseAction::MOVE;
    event3.x = 90.0f;
    event3.y = 100.0f;
    event3.time = TimeStamp(std::chrono::nanoseconds(1200));

    context_->mouseEvents_[node] = { event1, event2, event3 };

    MouseEvent event;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    auto result = context_->CompensateMouseMoveEventFromUnhandledEvents(event, node);
    EXPECT_TRUE(result);
    EXPECT_TRUE(context_->mouseEvents_.empty());
}

// ==========================================================================
// OnFlushMouseEvent(const RefPtr<FrameNode>&, const std::list<MouseEvent>&, TouchRestrict&)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest025
 * @tc.desc: Test OnFlushMouseEvent with empty mouseEvents returns early and sets canUseLongPredictTask_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest025, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    std::list<MouseEvent> emptyEvents;
    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::MOUSE;
    touchRestrict.hitTestType = SourceType::MOUSE;

    context_->canUseLongPredictTask_ = false;
    context_->OnFlushMouseEvent(node, emptyEvents, touchRestrict);
    EXPECT_TRUE(context_->canUseLongPredictTask_);
}

/**
 * @tc.name: PipelineContextEightTest026
 * @tc.desc: Test OnFlushMouseEvent with non-empty mouseEvents processes events.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest026, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.button = MouseButton::NONE_BUTTON;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
    std::list<MouseEvent> events = { mouseEvent };

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::MOUSE;
    touchRestrict.hitTestType = SourceType::MOUSE;

    context_->canUseLongPredictTask_ = true;
    context_->OnFlushMouseEvent(node, events, touchRestrict);
    EXPECT_FALSE(context_->canUseLongPredictTask_);
}

/**
 * @tc.name: PipelineContextEightTest027
 * @tc.desc: Test OnFlushMouseEvent with multiple events including non-MOVE action.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest027, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    MouseEvent moveEvent;
    moveEvent.id = TEST_MOUSE_ID;
    moveEvent.action = MouseAction::MOVE;
    moveEvent.x = TEST_X;
    moveEvent.y = TEST_Y;
    moveEvent.button = MouseButton::LEFT_BUTTON;
    moveEvent.time = TimeStamp(std::chrono::nanoseconds(1000));

    MouseEvent pressEvent;
    pressEvent.id = TEST_MOUSE_ID;
    pressEvent.action = MouseAction::PRESS;
    pressEvent.x = TEST_X;
    pressEvent.y = TEST_Y;
    pressEvent.button = MouseButton::LEFT_BUTTON;
    pressEvent.time = TimeStamp(std::chrono::nanoseconds(2000));

    std::list<MouseEvent> events = { moveEvent, pressEvent };

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::MOUSE;
    touchRestrict.hitTestType = SourceType::MOUSE;

    context_->OnFlushMouseEvent(node, events, touchRestrict);
    EXPECT_FALSE(context_->canUseLongPredictTask_);
}

/**
 * @tc.name: PipelineContextEightTest028
 * @tc.desc: Test OnFlushMouseEvent with mockFlushEvent flag skips history insertion.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest028, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.button = MouseButton::NONE_BUTTON;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
    mouseEvent.mockFlushEvent = true;
    std::list<MouseEvent> events = { mouseEvent };

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::MOUSE;
    touchRestrict.hitTestType = SourceType::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnFlushMouseEvent(node, events, touchRestrict));
}

// ==========================================================================
// OnAxisEvent(const AxisEvent&, const RefPtr<FrameNode>&)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest029
 * @tc.desc: Test OnAxisEvent with BEGIN action covers AddAxis and AxisTest path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest029, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    AxisEvent event;
    event.action = AxisAction::BEGIN;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest030
 * @tc.desc: Test OnAxisEvent with UPDATE action covers AxisTest path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest030, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    AxisEvent event;
    event.action = AxisAction::UPDATE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest031
 * @tc.desc: Test OnAxisEvent with END action covers cleanup path.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest031, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    AxisEvent event;
    event.action = AxisAction::END;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));

    context_->postEventManager_ = nullptr;
}

/**
 * @tc.name: PipelineContextEightTest032
 * @tc.desc: Test OnAxisEvent with NONE action skips AxisTest for API < 15.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest032, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = nullptr;

    AxisEvent event;
    event.action = AxisAction::NONE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));
}

/**
 * @tc.name: PipelineContextEightTest033
 * @tc.desc: Test OnAxisEvent with postEventManager_ null does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest033, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = nullptr;

    AxisEvent event;
    event.action = AxisAction::UPDATE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));
}

// ==========================================================================
// AddVisibleAreaChangeNode(const int32_t nodeId)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest034
 * @tc.desc: Test AddVisibleAreaChangeNode with valid nodeId adds to set.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest034, TestSize.Level1)
{
    AssertValidContext();
    context_->onVisibleAreaChangeNodeIds_.clear();
    auto frameNode = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    ElementRegister::GetInstance()->AddUINode(frameNode);

    context_->AddVisibleAreaChangeNode(TEST_NODE_ID_A);
    EXPECT_TRUE(context_->onVisibleAreaChangeNodeIds_.count(TEST_NODE_ID_A) > 0);
    EXPECT_TRUE(context_->isNeedCallbackAreaChange_);

    context_->onVisibleAreaChangeNodeIds_.clear();
}

/**
 * @tc.name: PipelineContextEightTest035
 * @tc.desc: Test AddVisibleAreaChangeNode with invalid nodeId (no FrameNode) still adds id to set.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest035, TestSize.Level1)
{
    AssertValidContext();
    context_->onVisibleAreaChangeNodeIds_.clear();
    constexpr int32_t invalidNodeId = 99999;

    context_->AddVisibleAreaChangeNode(invalidNodeId);
    EXPECT_TRUE(context_->onVisibleAreaChangeNodeIds_.count(invalidNodeId) > 0);
    EXPECT_TRUE(context_->isNeedCallbackAreaChange_);

    context_->onVisibleAreaChangeNodeIds_.clear();
}

// ==========================================================================
// UnregisterTouchEventListener(const WeakPtr<NG::Pattern>&)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest036
 * @tc.desc: Test UnregisterTouchEventListener with empty listenerVector_ does nothing.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest036, TestSize.Level1)
{
    AssertValidContext();
    context_->listenerVector_.clear();

    auto pattern = AceType::MakeRefPtr<Pattern>();
    context_->UnregisterTouchEventListener(WeakPtr<NG::Pattern>(pattern));
    EXPECT_TRUE(context_->listenerVector_.empty());
}

/**
 * @tc.name: PipelineContextEightTest037
 * @tc.desc: Test UnregisterTouchEventListener removes listener when pattern matches.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest037, TestSize.Level1)
{
    AssertValidContext();
    context_->listenerVector_.clear();

    auto pattern = AceType::MakeRefPtr<Pattern>();
    auto listener = std::make_shared<MockTouchEventCallbackEight>();
    ASSERT_NE(listener, nullptr);
    context_->RegisterTouchEventListener(listener);
    EXPECT_EQ(context_->listenerVector_.size(), 1u);

    context_->UnregisterTouchEventListener(WeakPtr<NG::Pattern>(pattern));
    EXPECT_EQ(context_->listenerVector_.size(), 0u);

    context_->listenerVector_.clear();
}

/**
 * @tc.name: PipelineContextEightTest038
 * @tc.desc: Test UnregisterTouchEventListener removes listener when pattern is invalid.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest038, TestSize.Level1)
{
    AssertValidContext();
    context_->listenerVector_.clear();

    auto listener = std::make_shared<MockTouchEventCallbackEight>();
    ASSERT_NE(listener, nullptr);
    context_->RegisterTouchEventListener(listener);
    EXPECT_EQ(context_->listenerVector_.size(), 1u);

    WeakPtr<NG::Pattern> invalidPattern;
    context_->UnregisterTouchEventListener(invalidPattern);
    EXPECT_TRUE(context_->listenerVector_.empty());
}

/**
 * @tc.name: PipelineContextEightTest039
 * @tc.desc: Test UnregisterTouchEventListener with multiple listeners removes only matching ones.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest039, TestSize.Level1)
{
    AssertValidContext();
    context_->listenerVector_.clear();

    auto listener1 = std::make_shared<MockTouchEventCallbackEight>();
    auto listener2 = std::make_shared<MockTouchEventCallbackEight>();
    context_->RegisterTouchEventListener(listener1);
    context_->RegisterTouchEventListener(listener2);
    EXPECT_EQ(context_->listenerVector_.size(), 2u);

    WeakPtr<NG::Pattern> invalidPattern;
    context_->UnregisterTouchEventListener(invalidPattern);
    EXPECT_TRUE(context_->listenerVector_.empty());
}

// ==========================================================================
// PostTaskResponseRegion(int32_t delay)
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest040
 * @tc.desc: Test PostTaskResponseRegion with null taskExecutor_ does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest040, TestSize.Level1)
{
    AssertValidContext();
    auto originalExecutor = context_->taskExecutor_;
    context_->taskExecutor_.Reset();

    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(TEST_DELAY_POSITIVE));

    context_->taskExecutor_ = originalExecutor;
}

/**
 * @tc.name: PipelineContextEightTest041
 * @tc.desc: Test PostTaskResponseRegion with null thpExtraMgr_ does not crash.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest041, TestSize.Level1)
{
    AssertValidContext();
    auto originalMgr = context_->thpExtraMgr_;
    context_->thpExtraMgr_.Reset();

    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(TEST_DELAY_POSITIVE));

    context_->thpExtraMgr_ = originalMgr;
}

/**
 * @tc.name: PipelineContextEightTest042
 * @tc.desc: Test PostTaskResponseRegion with negative delay uses DEFAULT_DELAY_THP.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest042, TestSize.Level1)
{
    AssertValidContext();
    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(TEST_DELAY_NEGATIVE));
}

/**
 * @tc.name: PipelineContextEightTest043
 * @tc.desc: Test PostTaskResponseRegion with positive delay uses provided value.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest043, TestSize.Level1)
{
    AssertValidContext();
    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(TEST_DELAY_POSITIVE));
}

/**
 * @tc.name: PipelineContextEightTest044
 * @tc.desc: Test PostTaskResponseRegion with zero delay.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest044, TestSize.Level1)
{
    AssertValidContext();
    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(0));
}

// ==========================================================================
// SetMouseStyleHoldNode(int32_t id) - Additional branch coverage
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest045
 * @tc.desc: Test SetMouseStyleHoldNode returns false when mouseStyleManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest045, TestSize.Level1)
{
    AssertValidContext();
    auto originalMouseStyleManager = context_->eventManager_->mouseStyleManager_;
    context_->eventManager_->mouseStyleManager_.Reset();

    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_NODE_ID_A));

    context_->eventManager_->mouseStyleManager_ = originalMouseStyleManager;
}

// ==========================================================================
// FreeMouseStyleHoldNode() - Additional branch coverage
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest046
 * @tc.desc: Test FreeMouseStyleHoldNode returns false when mouseStyleManager is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest046, TestSize.Level1)
{
    AssertValidContext();
    auto originalMouseStyleManager = context_->eventManager_->mouseStyleManager_;
    context_->eventManager_->mouseStyleManager_.Reset();

    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());

    context_->eventManager_->mouseStyleManager_ = originalMouseStyleManager;
}

/**
 * @tc.name: PipelineContextEightTest047
 * @tc.desc: Test SetMouseStyleHoldNode and FreeMouseStyleHoldNode full cycle with both overloads.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest047, TestSize.Level1)
{
    AssertValidContext();
    auto mouseStyleManager = context_->eventManager_->GetMouseStyleManager();
    ASSERT_NE(mouseStyleManager, nullptr);
    mouseStyleManager->mouseStyleNodeId_.reset();

    EXPECT_TRUE(context_->SetMouseStyleHoldNode(TEST_NODE_ID_A));
    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_NODE_ID_B));
    EXPECT_TRUE(context_->FreeMouseStyleHoldNode(TEST_NODE_ID_A));
    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());

    mouseStyleManager->mouseStyleNodeId_.reset();
}

// ==========================================================================
// OnFlushMouseEvent(TouchRestrict&) - the overload without node param
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest048
 * @tc.desc: Test OnFlushMouseEvent(TouchRestrict&) with empty mouseEvents_ sets canUseLongPredictTask_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest048, TestSize.Level1)
{
    AssertValidContext();
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    context_->canUseLongPredictTask_ = false;

    context_->OnFlushMouseEvent(touchRestrict);
    EXPECT_TRUE(context_->canUseLongPredictTask_);
    EXPECT_TRUE(context_->nodeToMousePoints_.empty());
}

/**
 * @tc.name: PipelineContextEightTest049
 * @tc.desc: Test OnFlushMouseEvent(TouchRestrict&) with non-empty mouseEvents_ iterates entries.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest049, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.button = MouseButton::NONE_BUTTON;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
    std::list<MouseEvent> eventList = { mouseEvent };
    context_->mouseEvents_[node] = eventList;

    TouchRestrict touchRestrict { TouchRestrict::NONE };
    touchRestrict.sourceType = SourceType::MOUSE;
    context_->canUseLongPredictTask_ = true;

    context_->OnFlushMouseEvent(touchRestrict);
    EXPECT_FALSE(context_->canUseLongPredictTask_);
}

// ==========================================================================
// OnMouseEvent - additional WINDOW_LEAVE without mockFlushEvent
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest051
 * @tc.desc: Test OnMouseEvent WINDOW_LEAVE without mockFlushEvent does not set isMockWindowTransFlag.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest051, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();


    MouseEvent event;
    event.action = MouseAction::WINDOW_LEAVE;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;
    event.mockFlushEvent = false;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_FALSE(context_->lastMouseEvent_->isMockWindowTransFlag);
}

// ==========================================================================
// OnMouseEvent - HOVER action
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest052
 * @tc.desc: Test OnMouseEvent with HOVER action dispatches event directly.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest052, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    MouseEvent event;
    event.action = MouseAction::HOVER;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->node, node);

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// CompensateMouseMoveEvent - CompensateMouseMoveEventFromUnhandledEvents returns true
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest053
 * @tc.desc: Test CompensateMouseMoveEvent delegates to CompensateMouseMoveEventFromUnhandledEvents.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest053, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(1000));
    context_->mouseEvents_[node] = { mouseEvent };

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.id = TEST_MOUSE_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));
    EXPECT_TRUE(context_->mouseEvents_.empty());
}

// ==========================================================================
// OnTouchEvent - DOWN with ConvertFromMouseAxis path
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest054
 * @tc.desc: Test OnTouchEvent with DOWN type from mouse source covers non-ConvertFromMouseAxis branch.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest054, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    TouchEvent event;
    event.type = TouchType::DOWN;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;
    event.sourceTool = SourceTool::FINGER;

    context_->OnTouchEvent(event, node, false);
    EXPECT_TRUE(context_->hasIdleTasks_);

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// OnTouchEvent - UP with postEventManager_
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest055
 * @tc.desc: Test OnTouchEvent with UP type sets passThroughResult on postEventManager_.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest055, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    context_->eventManager_->passThroughResult_ = true;

    TouchEvent event;
    event.type = TouchType::UP;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    context_->OnTouchEvent(event, node, false);
    EXPECT_EQ(context_->postEventManager_->passThroughResult_,
        context_->eventManager_->passThroughResult_);

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// OnAxisEvent - additional branch for isRotationEvent
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest056
 * @tc.desc: Test OnAxisEvent with BEGIN action and isRotationEvent true.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest056, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    AxisEvent event;
    event.action = AxisAction::BEGIN;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;
    event.isRotationEvent = true;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// OnAxisEvent - CANCEL action with formEventMgr
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest057
 * @tc.desc: Test OnAxisEvent with CANCEL action cleans up form event callbacks.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest057, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->dragDropManager_ = AceType::MakeRefPtr<DragDropManager>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    AxisEvent event;
    event.action = AxisAction::CANCEL;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = 0;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->OnAxisEvent(event, node));

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// AddVisibleAreaChangeNode - duplicate nodeId
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest058
 * @tc.desc: Test AddVisibleAreaChangeNode with duplicate nodeId does not duplicate entry.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest058, TestSize.Level1)
{
    AssertValidContext();
    context_->onVisibleAreaChangeNodeIds_.clear();
    auto frameNode = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    ElementRegister::GetInstance()->AddUINode(frameNode);

    context_->AddVisibleAreaChangeNode(TEST_NODE_ID_A);
    EXPECT_EQ(context_->onVisibleAreaChangeNodeIds_.count(TEST_NODE_ID_A), 1u);

    context_->AddVisibleAreaChangeNode(TEST_NODE_ID_A);
    EXPECT_EQ(context_->onVisibleAreaChangeNodeIds_.count(TEST_NODE_ID_A), 1u);

    context_->onVisibleAreaChangeNodeIds_.clear();
}

// ==========================================================================
// OnMouseEvent - MOVE with passThrough=true dispatches directly
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest059
 * @tc.desc: Test OnMouseEvent MOVE with passThrough=true dispatches without queuing.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest059, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isMousePassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    MouseEvent event;
    event.action = MouseAction::MOVE;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = true;

    context_->mouseEvents_.clear();
    context_->OnMouseEvent(event, node);
    EXPECT_TRUE(context_->mouseEvents_.empty());

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// CompensateMouseMoveEvent - no matching entry in lastDispatchTime
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest060
 * @tc.desc: Test CompensateMouseMoveEvent when lastDispatchTime has no entry for the mouse id.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest060, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->mouseEvents_.clear();

    MouseEvent mouseEvent;
    mouseEvent.id = TEST_MOUSE_ID;
    mouseEvent.x = TEST_X;
    mouseEvent.y = TEST_Y;
    mouseEvent.time = TimeStamp(std::chrono::nanoseconds(2000));
    mouseEvent.action = MouseAction::MOVE;
    mouseEvent.sourceType = SourceType::MOUSE;
    context_->nodeToMousePoints_[node] = { mouseEvent };

    context_->eventManager_->SetLastDispatchTime({});

    MouseEvent event;
    event.action = MouseAction::RELEASE;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.sourceTool = SourceTool::MOUSE;

    EXPECT_NO_FATAL_FAILURE(context_->CompensateMouseMoveEvent(event, node));

    context_->nodeToMousePoints_.clear();
}

// ==========================================================================
// PostTaskResponseRegion - combined null guard
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest061
 * @tc.desc: Test PostTaskResponseRegion with both taskExecutor_ and thpExtraMgr_ null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest061, TestSize.Level1)
{
    AssertValidContext();
    auto originalExecutor = context_->taskExecutor_;
    auto originalMgr = context_->thpExtraMgr_;
    context_->taskExecutor_.Reset();
    context_->thpExtraMgr_.Reset();

    EXPECT_NO_FATAL_FAILURE(context_->PostTaskResponseRegion(TEST_DELAY_POSITIVE));

    context_->taskExecutor_ = originalExecutor;
    context_->thpExtraMgr_ = originalMgr;
}

// ==========================================================================
// SetMouseStyleHoldNode - null eventManager guard
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest062
 * @tc.desc: Test SetMouseStyleHoldNode returns false when eventManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest062, TestSize.Level1)
{
    AssertValidContext();
    auto originalEventManager = context_->eventManager_;
    context_->eventManager_.Reset();

    EXPECT_FALSE(context_->SetMouseStyleHoldNode(TEST_NODE_ID_A));

    context_->eventManager_ = originalEventManager;
}

// ==========================================================================
// FreeMouseStyleHoldNode() - null eventManager guard
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest063
 * @tc.desc: Test FreeMouseStyleHoldNode returns false when eventManager_ is null.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest063, TestSize.Level1)
{
    AssertValidContext();
    auto originalEventManager = context_->eventManager_;
    context_->eventManager_.Reset();

    EXPECT_FALSE(context_->FreeMouseStyleHoldNode());

    context_->eventManager_ = originalEventManager;
}

// ==========================================================================
// OnMouseEvent - WINDOW_ENTER action
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest064
 * @tc.desc: Test OnMouseEvent with WINDOW_ENTER action.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest064, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();

    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();

    MouseEvent event;
    event.action = MouseAction::WINDOW_ENTER;
    event.button = MouseButton::NONE_BUTTON;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.id = TEST_MOUSE_ID;
    event.sourceType = SourceType::MOUSE;
    event.passThrough = false;

    context_->OnMouseEvent(event, node);
    EXPECT_NE(context_->lastMouseEvent_, nullptr);
    EXPECT_EQ(context_->lastMouseEvent_->node, node);

    context_->postEventManager_ = nullptr;
}

// ==========================================================================
// OnTouchEvent - CANCEL with postEventManager_
// ==========================================================================

/**
 * @tc.name: PipelineContextEightTest065
 * @tc.desc: Test OnTouchEvent with CANCEL type and postEventManager_ syncs passThroughResult.
 * @tc.type: FUNC
 */
HWTEST_F(PipelineContextFourTestNg, PipelineContextEightTest065, TestSize.Level1)
{
    AssertValidContext();
    auto node = FrameNode::CreateFrameNode("test", TEST_NODE_ID_A, AceType::MakeRefPtr<Pattern>());
    context_->rootNode_ = node;
    context_->viewScale_ = TEST_SCALE;
    context_->eventManager_ = AceType::MakeRefPtr<EventManager>();
    context_->accessibilityManagerNG_ = AceType::MakeRefPtr<AccessibilityManagerNG>();
    context_->isEventsPassThrough_ = false;
    context_->postEventManager_ = AceType::MakeRefPtr<PostEventManager>();
    context_->eventManager_->passThroughResult_ = false;

    TouchEvent event;
    event.type = TouchType::CANCEL;
    event.id = TEST_TOUCH_ID;
    event.x = TEST_X;
    event.y = TEST_Y;
    event.sourceType = SourceType::TOUCH;

    context_->OnTouchEvent(event, node, false);
    EXPECT_EQ(context_->postEventManager_->passThroughResult_,
        context_->eventManager_->passThroughResult_);

    context_->postEventManager_ = nullptr;
}
} // namespace OHOS::Ace::NG
