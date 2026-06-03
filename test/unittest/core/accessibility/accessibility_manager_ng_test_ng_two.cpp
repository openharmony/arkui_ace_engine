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

#include <chrono>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"

#include "core/components/common/properties/border_image.h"
#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/accessibility/accessibility_constants.h"
#include "frameworks/core/accessibility/accessibility_manager.h"
#include "frameworks/core/accessibility/accessibility_manager_ng.h"
#include "frameworks/core/components_ng/event/touch_event.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/event/mouse_event.h"
#include "frameworks/core/event/pointer_event.h"

#include "accessibility_session_adapter_test.h"
#include "ui/properties/ui_material.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t INVALID_NODE_ID_VALUE = -1;
constexpr float POINT_X_COORD = 10.0f;
constexpr float POINT_Y_COORD = 20.0f;
constexpr int64_t TIME_MS_BASE = 100;
constexpr float RECT_TEST_WIDTH = 10.0f;
constexpr float RECT_TEST_HEIGHT = 10.0f;

class MockRenderContextForTdd : public RenderContext {
public:
    RectF GetPaintRectWithoutTransform() override
    {
        return *rect_;
    }
    std::shared_ptr<RectF> rect_;
};
} // namespace

class AccessibilityManagerNgTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: IsEventTypeChangeDirectHandleHover001
 * @tc.desc: Test IsEventTypeChangeDirectHandleHover returns false for non-direct transitions
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, IsEventTypeChangeDirectHandleHover001, TestSize.Level1)
{
    AccessibilityManagerNG manager;

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::MOVE, AccessibilityHoverEventType::MOVE));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::MOVE, AccessibilityHoverEventType::ENTER));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::ENTER, AccessibilityHoverEventType::ENTER));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::EXIT, AccessibilityHoverEventType::EXIT));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::ENTER, AccessibilityHoverEventType::EXIT));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::MOVE, AccessibilityHoverEventType::CANCEL));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::CANCEL, AccessibilityHoverEventType::MOVE));

    EXPECT_FALSE(manager.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::CANCEL, AccessibilityHoverEventType::CANCEL));
}

/**
 * @tc.name: ConvertPointFromAncestorToNode001
 * @tc.desc: Test ConvertPointFromAncestorToNode when ancestor equals node
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ConvertPointFromAncestorToNode001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    PointF pointAncestor(POINT_X_COORD, POINT_Y_COORD);
    PointF pointNode;

    auto ret = manager.ConvertPointFromAncestorToNode(frameNode, frameNode, pointAncestor, pointNode);
    EXPECT_TRUE(ret);
    EXPECT_FLOAT_EQ(pointNode.GetX(), POINT_X_COORD);
    EXPECT_FLOAT_EQ(pointNode.GetY(), POINT_Y_COORD);
}

/**
 * @tc.name: ConvertPointFromAncestorToNode002
 * @tc.desc: Test ConvertPointFromAncestorToNode with null ancestor returns false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ConvertPointFromAncestorToNode002, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    PointF pointAncestor(POINT_X_COORD, POINT_Y_COORD);
    PointF pointNode;

    auto ret = manager.ConvertPointFromAncestorToNode(nullptr, frameNode, pointAncestor, pointNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ConvertPointFromAncestorToNode003
 * @tc.desc: Test ConvertPointFromAncestorToNode with null endNode returns false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ConvertPointFromAncestorToNode003, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    PointF pointAncestor(POINT_X_COORD, POINT_Y_COORD);
    PointF pointNode;

    auto ret = manager.ConvertPointFromAncestorToNode(frameNode, nullptr, pointAncestor, pointNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ConvertPointFromAncestorToNode004
 * @tc.desc: Test ConvertPointFromAncestorToNode with node not descendant of ancestor returns false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ConvertPointFromAncestorToNode004, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto ancestor = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(ancestor, nullptr);
    auto unrelated = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(unrelated, nullptr);

    PointF pointAncestor(POINT_X_COORD, POINT_Y_COORD);
    PointF pointNode;

    auto ret = manager.ConvertPointFromAncestorToNode(ancestor, unrelated, pointAncestor, pointNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: ConvertPointFromAncestorToNode005
 * @tc.desc: Test ConvertPointFromAncestorToNode with parent-child relationship
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ConvertPointFromAncestorToNode005, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto parent = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(parent, nullptr);
    auto child = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(child, nullptr);

    auto renderContext = AceType::MakeRefPtr<MockRenderContextForTdd>();
    ASSERT_NE(renderContext, nullptr);
    auto rect = std::make_shared<RectF>(0.0f, 0.0f, RECT_TEST_WIDTH, RECT_TEST_HEIGHT);
    renderContext->rect_ = rect;
    child->renderContext_ = renderContext;

    child->SetParent(parent);

    PointF pointAncestor(POINT_X_COORD, POINT_Y_COORD);
    PointF pointNode;

    auto ret = manager.ConvertPointFromAncestorToNode(parent, child, pointAncestor, pointNode);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AccessibilityHoverStateManager002
 * @tc.desc: Test AccessibilityHoverStateManager with multiple different node IDs
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityHoverStateManager002, TestSize.Level1)
{
    AccessibilityHoverStateManager stateManager;

    auto node1 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(node1, nullptr);
    auto node2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(node2, nullptr);

    auto& state1 = stateManager.GetHoverState(node1->GetAccessibilityId());
    auto& state2 = stateManager.GetHoverState(node2->GetAccessibilityId());

    EXPECT_EQ(stateManager.hoverStateMap_.size(), 2);

    state1.idle = false;
    state1.source = SourceType::TOUCH;
    EXPECT_FALSE(state1.idle);
    EXPECT_TRUE(state2.idle);
    EXPECT_EQ(state2.source, SourceType::NONE);

    stateManager.ResetHoverState(state1);
    EXPECT_TRUE(state1.idle);
    EXPECT_TRUE(state2.idle);
}

/**
 * @tc.name: AccessibilityHoverStateManager003
 * @tc.desc: Test ResetHoverState clears nodesTransparent
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityHoverStateManager003, TestSize.Level1)
{
    AccessibilityHoverStateManager stateManager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto& hoverState = stateManager.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.idle = false;
    hoverState.nodesHovering.push_back(frameNode);
    hoverState.nodeTransparent.push_back(frameNode);

    ASSERT_FALSE(hoverState.idle);
    ASSERT_FALSE(hoverState.nodesHovering.empty());
    ASSERT_FALSE(hoverState.nodeTransparent.empty());

    stateManager.ResetHoverState(hoverState);

    EXPECT_TRUE(hoverState.idle);
    EXPECT_TRUE(hoverState.nodesHovering.empty());
    EXPECT_TRUE(hoverState.nodeTransparent.empty());
}

/**
 * @tc.name: HandleAccessibilityHoverEvent001
 * @tc.desc: Test TouchType HOVER_CANCEL triggers CANCEL and resets state
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.idle = false;
    hoverState.source = SourceType::TOUCH;
    hoverState.eventType = AccessibilityHoverEventType::MOVE;
    hoverState.nodesHovering.push_back(frameNode);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::HOVER_CANCEL;
    touchEvent.sourceType = SourceType::TOUCH;

    manager.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    EXPECT_TRUE(hoverState.idle);
    EXPECT_TRUE(hoverState.nodesHovering.empty());
}

/**
 * @tc.name: HandleAccessibilityHoverEvent002
 * @tc.desc: Test MouseAction PRESS/RELEASE returns early without updating state
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent002, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;

    mouseEvent.action = MouseAction::PRESS;
    manager.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);

    mouseEvent.action = MouseAction::RELEASE;
    manager.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);

    mouseEvent.action = MouseAction::MOVE;
    manager.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::MOUSE);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent003
 * @tc.desc: Test all HandleAccessibilityHoverEvent overloads with null root return early
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent003, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    manager.HandleAccessibilityHoverEvent(nullptr, mouseEvent);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::HOVER_MOVE;
    touchEvent.sourceType = SourceType::TOUCH;
    manager.HandleAccessibilityHoverEvent(nullptr, touchEvent);

    manager.HandleAccessibilityHoverEvent(nullptr, POINT_X_COORD, POINT_Y_COORD,
        static_cast<int32_t>(SourceType::TOUCH),
        static_cast<int32_t>(AccessibilityHoverEventType::ENTER),
        TIME_MS_BASE);

    SUCCEED();
}

/**
 * @tc.name: HandleAccessibilityHoverEvent004
 * @tc.desc: Test all overloads return early when accessibility is disabled
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent004, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    manager.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::HOVER_MOVE;
    touchEvent.sourceType = SourceType::TOUCH;
    manager.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);

    manager.HandleAccessibilityHoverEvent(frameNode, POINT_X_COORD, POINT_Y_COORD,
        static_cast<int32_t>(SourceType::TOUCH),
        static_cast<int32_t>(AccessibilityHoverEventType::MOVE), TIME_MS_BASE);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent005
 * @tc.desc: Test HandleAccessibilityHoverEvent with event type out of valid range returns early
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent005, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    manager.HandleAccessibilityHoverEvent(frameNode, POINT_X_COORD, POINT_Y_COORD,
        static_cast<int32_t>(SourceType::TOUCH), INVALID_NODE_ID_VALUE, TIME_MS_BASE);
    EXPECT_EQ(hoverState.source, SourceType::NONE);

    manager.HandleAccessibilityHoverEvent(frameNode, POINT_X_COORD, POINT_Y_COORD,
        static_cast<int32_t>(SourceType::TOUCH),
        static_cast<int32_t>(AccessibilityHoverEventType::Count), TIME_MS_BASE);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: HoverTestDebug001
 * @tc.desc: Test HoverTestDebug produces non-empty output
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HoverTestDebug001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    NG::PointF hoverPoint(POINT_X_COORD, POINT_Y_COORD);
    std::string summary;
    std::string detail;

    manager.HoverTestDebug(frameNode, hoverPoint, summary, detail);

    EXPECT_FALSE(summary.empty());
}

/**
 * @tc.name: IgnoreCurrentHoveringNode001
 * @tc.desc: Test IgnoreCurrentHoveringNode returns false when node has no session adapter
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, IgnoreCurrentHoveringNode001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto ret = manager.IgnoreCurrentHoveringNode(frameNode);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent006
 * @tc.desc: Test MouseEvent with non-MOUSE source type returns early
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent006, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    MouseEvent mouseEvent;
    mouseEvent.sourceType = SourceType::NONE;
    mouseEvent.action = MouseAction::MOVE;

    manager.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent007
 * @tc.desc: Test TouchEvent with MOUSE source type returns early
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent007, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    TouchEvent touchEvent;
    touchEvent.type = TouchType::HOVER_MOVE;
    touchEvent.sourceType = SourceType::MOUSE;

    manager.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent008
 * @tc.desc: Test TouchEvent with UNKNOWN touch type returns early without processing
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent008, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    TouchEvent touchEvent;
    touchEvent.type = TouchType::UNKNOWN;
    touchEvent.sourceType = SourceType::TOUCH;

    manager.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: HandleAccessibilityHoverEvent009
 * @tc.desc: Test TouchEvent with DOWN touch type returns early
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEvent009, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    hoverState.source = SourceType::NONE;

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    touchEvent.sourceType = SourceType::TOUCH;

    manager.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.source, SourceType::NONE);
}

/**
 * @tc.name: NotifyHoverEventToNodeSession001
 * @tc.desc: Test NotifyHoverEventToNodeSession with disabled event hub returns false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, NotifyHoverEventToNodeSession001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabled(false);

    NG::PointF hoverPoint(POINT_X_COORD, POINT_Y_COORD);
    TimeStamp time;

    auto ret = manager.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::TOUCH, AccessibilityHoverEventType::ENTER, time);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: HandleAccessibilityHoverTransparentCallback001
 * @tc.desc: Test HandleAccessibilityHoverTransparentCallback with INVALID lastHoveringId returns false
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverTransparentCallback001, TestSize.Level1)
{
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AccessibilityHoverState hoverState;
    PointF point(POINT_X_COORD, POINT_Y_COORD);
    AccessibilityManagerNG::HandleTransparentCallbackParam param = {0, INVALID_NODE_ID_VALUE, point};

    TouchEvent touchEvent;

    auto ret = manager.HandleAccessibilityHoverTransparentCallback(
        false, frameNode, param, touchEvent, hoverState);
    EXPECT_FALSE(ret);
}
} // namespace OHOS::Ace::NG
