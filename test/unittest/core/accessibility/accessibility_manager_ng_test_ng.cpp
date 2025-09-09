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

#include <iostream>
#include <chrono>
#include "gtest/gtest.h"

#define private public
#define protected public
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/node_container/node_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/core/accessibility/accessibility_constants.h"
#include "frameworks/core/accessibility/accessibility_manager_ng.h"
#include "frameworks/core/components_ng/event/touch_event.h"
#include "frameworks/core/components_ng/pattern/pattern.h"
#include "frameworks/core/components_ng/pattern/text/text_pattern.h"
#include "frameworks/core/event/mouse_event.h"
#include "frameworks/core/event/pointer_event.h"

#include "accessibility_session_adapter_test.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr float TILT_X_VALUE = 400.0f;
    constexpr float TILT_Y_VALUE = 400.0f;
    const std::vector<TouchPoint> POINTERS = { { .tiltX = TILT_X_VALUE, .tiltY = TILT_Y_VALUE } };
    const float POINT_X = 1.0f;
    const float POINT_Y = 1.0f;
    const int32_t SOURCETYPE = 1;
    const int32_t SOURCETYPETWO = 2;
    const int32_t EVENTTYPE = 1;
    const int64_t TIMEMS_INTERVAL_HOVER = 50;
    const int64_t TIMEMS_DIFFERENT_HOVER_SOURCE = 200;
    const int64_t TIMEMS = 500;
    const int64_t LARGETIMEMS = 1500;
    const int32_t NUMTWO = 2;
    constexpr int32_t INVALID_NODE_ID = -1;
    constexpr float TEST_FRAME_NODE_WIDTH = 10.0f;
    constexpr float TEST_FRAME_NODE_HEIGHT = 10.0f;

class MockRenderContextTest : public RenderContext {
public:
    RectF GetPaintRectWithoutTransform() override
    {
        return *retf;
    }
    std::shared_ptr<RectF> retf;
};

bool InitTwoFrameNode(RefPtr<FrameNode>& frameNode1, RefPtr<FrameNode>& frameNode2)
{
    frameNode1 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
    ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(frameNode1, false);
    frameNode2 = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    CHECK_NULL_RETURN(frameNode2, false);
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    CHECK_NULL_RETURN(renderContext, false);
    auto rect = std::make_shared<RectF>(0.0, 0.0, TEST_FRAME_NODE_WIDTH, TEST_FRAME_NODE_HEIGHT);
    renderContext->retf = rect;
    frameNode1->renderContext_ = renderContext;
    frameNode2->renderContext_ = renderContext;
    frameNode1->AddChild(frameNode2);
    return true;
}

    
} // namespace

constexpr int ZERO_ANGLE = 0;
constexpr int QUARTER_ANGLE = 90;
constexpr int HALF_ANGLE = 180;
constexpr int THREE_QUARTER_ANGLE = 270;
constexpr int FULL_ANGLE = 360;

class MockFrameNode : public FrameNode {
public:
    VectorF GetTransformScale()
    {
        VectorF testScale {1.2f, 1.2f};
        return testScale;
    }
};

class AccessibilityManagerNgTestNg : public testing::Test {
public:
    static void SetUpTestCase() {};
    static void TearDownTestCase() {};
};

/**
 * @tc.name: accessibilityManagerNgTest001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest001, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode("framenode", 1, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    MouseEvent mouseEvent;
    mouseEvent.button = MouseButton::LEFT_BUTTON;
    mouseEvent.action = MouseAction::PRESS;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    mouseEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    mouseEvent.sourceType = SourceType::MOUSE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    mouseEvent.action = MouseAction::WINDOW_ENTER;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    mouseEvent.action = MouseAction::MOVE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    mouseEvent.action = MouseAction::WINDOW_LEAVE;
    
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    mouseEvent.action = MouseAction::PULL_UP;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    hoverState.idle = false;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    hoverState.idle = true;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    TimeStamp time;
    hoverState.time = time;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, mouseEvent);
    EXPECT_EQ(hoverState.source, SourceType::MOUSE);
}

/**
 * @tc.name: accessibilityManagerNgTest002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest002, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode("main", NUMTWO, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    TouchEvent touchEvent;
    touchEvent.type = TouchType::DOWN;
    TouchPoint pointOne;
    touchEvent.pointers.push_back(pointOne);
    TouchPoint pointTwo;
    touchEvent.pointers.push_back(pointTwo);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.type = TouchType::HOVER_ENTER;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.type = TouchType::HOVER_MOVE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.type = TouchType::HOVER_EXIT;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.type = TouchType::UNKNOWN;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.sourceType = SourceType::TOUCH;
    touchEvent.SetPointers(POINTERS);
    touchEvent.pointers.push_back(pointOne);
    touchEvent.pointers.push_back(pointTwo);
    touchEvent.type = TouchType::HOVER_ENTER;
    hoverState.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.SetPointers(POINTERS);
    touchEvent.pointers.push_back(pointOne);
    touchEvent.pointers.push_back(pointTwo);
    hoverState.source = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.type = TouchType::UNKNOWN;
    touchEvent.x = 100;
    touchEvent.y = 100;
    hoverState.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    hoverState.idle = true;
    touchEvent.sourceType = SourceType::TOUCH;
    hoverState.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    
    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, touchEvent);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: accessibilityManagerNgTest003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest003, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());

    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, SOURCETYPE, EVENTTYPE, TIMEMS);

    hoverState.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(hoverState.idle, false);
    WeakPtr<FrameNode> nodesHovering1;
    WeakPtr<FrameNode> nodesHovering2;
    hoverState.nodesHovering.push_back(nodesHovering1);
    hoverState.nodesHovering.push_back(nodesHovering2);
    hoverState.nodesHovering.push_back(frameNode);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_NE(hoverState.nodesHovering.size(), 0);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, -1, EVENTTYPE, TIMEMS);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 99, EVENTTYPE, TIMEMS);
    EXPECT_EQ(hoverState.idle, false);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    hoverState.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    hoverState.idle = true;
    hoverState.source = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, LARGETIMEMS);
    hoverState.idle = true;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 0, EVENTTYPE, TIMEMS);

    int32_t eventTypeEnter = static_cast<int32_t>(AccessibilityHoverEventType::ENTER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 0, eventTypeEnter, TIMEMS);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(AceApplicationInfo::GetInstance().IsAccessibilityEnabled(), true);
    hoverState.idle = true;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y, SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(AceApplicationInfo::GetInstance().IsAccessibilityEnabled(), true);
}

/**
 * @tc.name: accessibilityManagerNgTest004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest004, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    int32_t x = 100;
    int32_t y = 100;
    NG::PointF hoverPoint(x, y);
    std::string summary;
    std::string detail;
    DragPointerEvent pointerEvent;

    TimeStamp time;
    
    accessibilityManagerNg.HoverTestDebug(frameNode, hoverPoint, summary, detail);
    accessibilityManagerNg.IgnoreCurrentHoveringNode(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(false);
    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    eventHub->SetEnabled(true);
    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    PointF pointNode(hoverPoint);
    auto result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, frameNode, hoverPoint, pointNode);
    EXPECT_EQ(result, true);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, nullptr, hoverPoint, pointNode);
    EXPECT_EQ(result, false);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(nullptr, frameNode, hoverPoint, pointNode);
    EXPECT_EQ(result, false);
    auto endNode = FrameNode::CreateFrameNode("main", NUMTWO, AceType::MakeRefPtr<Pattern>(), true);
    ASSERT_NE(endNode, nullptr);
    endNode->UpdateRecycleElmtId(NUMTWO);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, endNode, hoverPoint, pointNode);
    EXPECT_EQ(result, false);

    endNode->SetParent(frameNode);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, endNode, hoverPoint, pointNode);
    EXPECT_EQ(result, true);

    auto endNodeMock = MockFrameNode::CreateFrameNode("main", NUMTWO, AceType::MakeRefPtr<Pattern>(), true);
    endNodeMock->SetParent(frameNode);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, endNodeMock, hoverPoint, pointNode);
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: accessibilityManagerNgTest005
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest005, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    // for lastNodesHovering
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    hoverState.idle = true;
    WeakPtr<FrameNode> nodesHovering1;
    WeakPtr<FrameNode> nodesHovering2;
    hoverState.nodesHovering.push_back(nodesHovering1);
    hoverState.nodesHovering.push_back(nodesHovering2);
    hoverState.nodesHovering.push_back(frameNode);

    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(hoverState.nodesHovering.size(), 0);

    // for first judge
    TouchEvent touchEvent;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);
    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, touchEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.sourceType = SourceType::MOUSE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, touchEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, touchEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.sourceType = SourceType::MOUSE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, touchEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: accessibilityManagerNgTest006
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest006, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    // pointers.size
    TouchEvent touchEvent;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    hoverState.idle = true;
    touchEvent.type = TouchType::HOVER_ENTER;

    touchEvent.pointers.clear();

    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.sourceType = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.SetPointers(POINTERS);
    TouchPoint pointOne;
    TouchPoint pointTwo;
    touchEvent.pointers.push_back(pointOne);
    touchEvent.pointers.push_back(pointTwo);
    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.sourceType = SourceType::TOUCH;

    hoverState.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.idle, true);

    hoverState.source = SourceType::MOUSE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.idle, false);
}

/**
 * @tc.name: accessibilityManagerNgTest007
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest007, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MockAccessibilityTestPattern>());

    int32_t x = 100;
    int32_t y = 100;
    NG::PointF hoverPoint(x, y);
    TimeStamp time;
    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);

    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, nullptr,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);

    EXPECT_NE(frameNode, nullptr);
}

/**
 * @tc.name: accessibilityManagerNgTest008
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest008, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    hoverState.idle = false;
    hoverState.nodesHovering.push_back(frameNode);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, -1, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, 99, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, -1, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, 99, TIMEMS_INTERVAL_HOVER);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, -1, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, 99, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, -1, TIMEMS_INTERVAL_HOVER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, POINT_X, POINT_Y,
        SOURCETYPETWO, 99, TIMEMS_INTERVAL_HOVER);

    EXPECT_NE(hoverState.nodesHovering.size(), 0);
}

/**
 * @tc.name: accessibilityManagerNgTest009
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest009, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto& hoverState = accessibilityManagerNg.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());

    // hoverState source different and time is in MIN_SOURCE_CHANGE_GAP_MS
    TouchEvent touchEvent;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    hoverState.idle = false;
    touchEvent.type = TouchType::HOVER_ENTER;

    touchEvent.SetPointers(POINTERS);

    touchEvent.sourceType = SourceType::TOUCH;
    hoverState.source = SourceType::MOUSE;
    TimeStamp time((std::chrono::milliseconds(TIMEMS_DIFFERENT_HOVER_SOURCE)));
    touchEvent.time = time;

    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(hoverState.idle, false);

    hoverState.eventType = AccessibilityHoverEventType::MOVE;
    auto ret = accessibilityManagerNg.IsEventTypeChangeDirectHandleHover(
        AccessibilityHoverEventType::EXIT,
        AccessibilityHoverEventType::MOVE);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AccessibilityManagerNgTest010
 * @tc.desc: NotifyHoverEventToNodeSession
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest010, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    int32_t x = 100;
    int32_t y = 100;
    NG::PointF hoverPoint(x, y);
    TimeStamp time;

    auto ret = accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    EXPECT_FALSE(ret);

    ret = accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, nullptr,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    EXPECT_FALSE(ret);

    auto testNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<MockAccessibilityTestPattern>());
    auto pattern = testNode->GetPattern();
    ASSERT_NE(pattern, nullptr);
    testNode->eventHub_ = pattern->CreateEventHub();
    auto eventHub = testNode->eventHub_;
    ASSERT_NE(eventHub, nullptr);
    eventHub->SetEnabledInternal(true);
    ret = accessibilityManagerNg.NotifyHoverEventToNodeSession(testNode, testNode,
        hoverPoint, SourceType::TOUCH, AccessibilityHoverEventType::ENTER, time);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: AccessibilityManagerNgTest011
 * @tc.desc: HandleAccessibilityHoverTransparentCallback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest011, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    AccessibilityHoverState hoverState;
    PointF point;
    AccessibilityManagerNG::HandleTransparentCallbackParam param = {0, 1, point};

    TouchEvent touchEvent;

    auto ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(true,
        frameNode,
        param,
        touchEvent,
        hoverState);
    EXPECT_FALSE(ret);

    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(false,
        frameNode,
        param,
        touchEvent,
        hoverState);
    EXPECT_FALSE(ret);

    param = {-1, -1, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(false,
        frameNode,
        param,
        touchEvent,
        hoverState);
    EXPECT_FALSE(ret);

    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(false,
        nullptr,
        param,
        touchEvent,
        hoverState);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: AccessibilityManagerNgTest012
 * @tc.desc: ExecuteChildNodeHoverTransparentCallback
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityManagerNgTest012, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    TouchEvent touchEvent;
    AccessibilityHoverState hoverState;
    PointF point;
    auto ret = accessibilityManagerNg.ExecuteChildNodeHoverTransparentCallback(nullptr, point, touchEvent, hoverState);
    EXPECT_FALSE(ret);

    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    ret = accessibilityManagerNg.ExecuteChildNodeHoverTransparentCallback(frameNode, point, touchEvent, hoverState);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: ExecuteChildNodeHoverTransparentCallback002
 * @tc.desc: first event type is hover enter
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, ExecuteChildNodeHoverTransparentCallback002, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    TouchEvent touchEvent;
    AccessibilityHoverState hoverState;
    PointF point{1, 1};
    bool ret;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto renderContext = AceType::MakeRefPtr<MockRenderContextTest>();
    ASSERT_NE(renderContext, nullptr);
    auto rect = std::make_shared<RectF>(0.0, 0.0, 10.0, 10.0);
    renderContext->retf = rect;
    frameNode->renderContext_ = renderContext;
 
    auto accessibilityProperty = frameNode->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    bool processFlag = false;
    TouchType resultType = TouchType::UNKNOWN;
    accessibilityProperty->SetAccessibilityTransparentCallback([&] (TouchEventInfo& eventInfo) {
        processFlag = true;
        auto touches = eventInfo.GetChangedTouches();
        if (touches.size() > 0) {
            auto changeTouch = touches.front();
            resultType = changeTouch.GetTouchType();
        }
    });

    // IsInSentTransparentNode false  and event.type != TouchType::HOVER_CANCEL
    touchEvent.type = TouchType::HOVER_MOVE;
    ret = accessibilityManagerNg.ExecuteChildNodeHoverTransparentCallback(frameNode, point, touchEvent, hoverState);
    EXPECT_TRUE(ret);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_ENTER);
    // IsInSentTransparentNode false  and event.type == TouchType::HOVER_CANCEL
    processFlag = false;
    hoverState.nodeTransparent.clear();
    touchEvent.type = TouchType::HOVER_CANCEL;
    ret = accessibilityManagerNg.ExecuteChildNodeHoverTransparentCallback(frameNode, point, touchEvent, hoverState);
    EXPECT_TRUE(ret);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_CANCEL);

    // IsInSentTransparentNode true  and event.type == TouchType::HOVER_MOVE
    processFlag = false;
    hoverState.nodeTransparent.clear();
    hoverState.nodeTransparent.emplace_back(frameNode);
    touchEvent.type = TouchType::HOVER_MOVE;
    ret = accessibilityManagerNg.ExecuteChildNodeHoverTransparentCallback(frameNode, point, touchEvent, hoverState);
    EXPECT_TRUE(ret);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_MOVE);
}

/**
 * @tc.name: HandleAccessibilityHoverTransparentCallback002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverTransparentCallback002, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    TouchEvent touchEvent;
    AccessibilityHoverState hoverState;
    PointF point{1, 1};
    bool processFlag = false;
    bool transformed = false;
    bool ret;
    TouchType resultType = TouchType::UNKNOWN;
    AccessibilityManagerNG::HandleTransparentCallbackParam param;
    RefPtr<FrameNode> frameNode1;
    RefPtr<FrameNode> frameNode2;
    auto initRet = InitTwoFrameNode(frameNode1, frameNode2);
    ASSERT_EQ(initRet, true);
    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    accessibilityProperty2->SetAccessibilityTransparentCallback([&] (TouchEventInfo& eventInfo) {
        processFlag = true;
        auto touches = eventInfo.GetChangedTouches();
        if (touches.size() > 0) {
            auto changeTouch = touches.front();
            resultType = changeTouch.GetTouchType();
        }
    });
    // 1. has nodeTransparent, transformed false,
    // currentHoveringId == INVALID_NODE_ID, lastHoveringId == INVALID_NODE_ID
    hoverState.nodeTransparent.emplace_back(frameNode2);
    touchEvent.type = TouchType::HOVER_MOVE;
    // 1.1 point in node
    param = {INVALID_NODE_ID, INVALID_NODE_ID, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
        transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, false);
    // 1.2 point not in node
    PointF point2(-1, -1);
    param = {INVALID_NODE_ID, INVALID_NODE_ID, point2};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
        transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_EXIT);
}
/**
 * @tc.name: HandleAccessibilityHoverTransparentCallback003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverTransparentCallback003, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    TouchEvent touchEvent;
    AccessibilityHoverState hoverState;
    PointF point{1, 1};
    bool processFlag = false;
    bool transformed = false;
    bool ret;
    TouchType resultType = TouchType::UNKNOWN;
    AccessibilityManagerNG::HandleTransparentCallbackParam param;
    RefPtr<FrameNode> frameNode1;
    RefPtr<FrameNode> frameNode2;
    auto initRet = InitTwoFrameNode(frameNode1, frameNode2);
    ASSERT_EQ(initRet, true);

    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    accessibilityProperty2->SetAccessibilityTransparentCallback([&] (TouchEventInfo& eventInfo) {
        processFlag = true;
        auto touches = eventInfo.GetChangedTouches();
        if (touches.size() > 0) {
            auto changeTouch = touches.front();
            resultType = changeTouch.GetTouchType();
        }
    });
    hoverState.nodeTransparent.emplace_back(frameNode2);
    touchEvent.type = TouchType::HOVER_MOVE;
    // 2.has nodeTransparent, transformed false,currentHoveringId != INVALID_NODE_ID, lastHoveringId == INVALID_NODE_ID
    // 2.1  currentHoveringId != transparentNode->GetAccessibilityId()
    processFlag = false;
    param = {frameNode1->GetAccessibilityId(), INVALID_NODE_ID, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
            transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_EXIT);
    // 2.2  currentHoveringId == transparentNode->GetAccessibilityId()
    hoverState.nodeTransparent.clear();
    hoverState.nodeTransparent.emplace_back(frameNode2);
    processFlag = false;
    param = {frameNode2->GetAccessibilityId(), INVALID_NODE_ID, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
            transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, false);
}

/**
 * @tc.name: HandleAccessibilityHoverTransparentCallback004
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverTransparentCallback004, TestSize.Level1)
{
    AccessibilityManagerNG accessibilityManagerNg{};
    TouchEvent touchEvent;
    AccessibilityHoverState hoverState;
    PointF point{1, 1};
    bool processFlag = false;
    TouchType resultType = TouchType::UNKNOWN;
    AccessibilityManagerNG::HandleTransparentCallbackParam param;
    RefPtr<FrameNode> frameNode1;
    RefPtr<FrameNode> frameNode2;
    auto initRet = InitTwoFrameNode(frameNode1, frameNode2);
    ASSERT_EQ(initRet, true);

    auto accessibilityProperty2 = frameNode2->GetAccessibilityProperty<NG::AccessibilityProperty>();
    ASSERT_NE(accessibilityProperty2, nullptr);
    accessibilityProperty2->SetAccessibilityTransparentCallback([&] (TouchEventInfo& eventInfo) {
        processFlag = true;
        auto touches = eventInfo.GetChangedTouches();
        if (touches.size() > 0) {
            auto changeTouch = touches.front();
            resultType = changeTouch.GetTouchType();
        }
    });
    hoverState.nodeTransparent.emplace_back(frameNode2);
    touchEvent.type = TouchType::HOVER_MOVE;
    bool transformed = true;
    // 3.transformed true , currentHoveringId != INVALID_NODE_ID, lastHoveringId == INVALID_NODE_ID
    // 3.1  currentHoveringId != transparentNode->GetAccessibilityId(), point in node
    processFlag = false;
    param = {frameNode1->GetAccessibilityId(), INVALID_NODE_ID, point};
    auto ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
        transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, true);
    EXPECT_EQ(resultType, TouchType::HOVER_EXIT);
    // 3.2  currentHoveringId == transparentNode->GetAccessibilityId(), point in node
    hoverState.nodeTransparent.clear();
    hoverState.nodeTransparent.emplace_back(frameNode2);
    processFlag = false;
    param = {frameNode2->GetAccessibilityId(), INVALID_NODE_ID, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
        transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, true);
    // 3.3  currentHoveringId == INVALID_NODE_ID, point in node
    hoverState.nodeTransparent.clear();
    hoverState.nodeTransparent.emplace_back(frameNode2);
    processFlag = false;
    param = {frameNode2->GetAccessibilityId(), INVALID_NODE_ID, point};
    ret = accessibilityManagerNg.HandleAccessibilityHoverTransparentCallback(
        transformed, frameNode1, param, touchEvent, hoverState);
    EXPECT_EQ(processFlag, true);
}

/**
* @tc.name: AccessibilityRectTest001
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest001, TestSize.Level1)
{
    AccessibilityRect rect1;
    EXPECT_EQ(rect1.GetX(), 0);
    EXPECT_EQ(rect1.GetY(), 0);
    EXPECT_EQ(rect1.GetWidth(), 0);
    EXPECT_EQ(rect1.GetHeight(), 0);

    AccessibilityRect rect2(10, 20, 100, 200);
    EXPECT_EQ(rect2.GetX(), 10);
    EXPECT_EQ(rect2.GetY(), 20);
    EXPECT_EQ(rect2.GetWidth(), 100);
    EXPECT_EQ(rect2.GetHeight(), 200);

    rect2.SetPosition(30, 40);
    EXPECT_EQ(rect2.GetX(), 30);
    EXPECT_EQ(rect2.GetY(), 40);

    rect2.SetSize(50, 60);
    EXPECT_EQ(rect2.GetWidth(), 50);
    EXPECT_EQ(rect2.GetHeight(), 60);
}

/**
* @tc.name: AccessibilityRectTest002
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest002, TestSize.Level1)
{
    // init x=0, y=0, width=100, height=200
    AccessibilityRect rect(0, 0, 100, 200);
    const float originalCenterX = 50;  // 0 + 100/2
    const float originalCenterY = 100; // 0 + 200/2

    // rotate 90
    rect.Rotate(QUARTER_ANGLE);
    EXPECT_EQ(rect.GetWidth(), 200);
    EXPECT_EQ(rect.GetHeight(), 100);
    EXPECT_EQ(rect.GetX(), originalCenterX - 200/2); // 50 - 100 = -50
    EXPECT_EQ(rect.GetY(), originalCenterY - 100/2); // 100 - 50 = 50

    // rotate 180
    rect.Rotate(HALF_ANGLE);
    EXPECT_EQ(rect.GetWidth(), 200);
    EXPECT_EQ(rect.GetHeight(), 100);
    EXPECT_EQ(rect.GetX(), -50);
    EXPECT_EQ(rect.GetY(), 50);

    // rotate 270
    rect.Rotate(THREE_QUARTER_ANGLE);
    EXPECT_EQ(rect.GetWidth(), 100);
    EXPECT_EQ(rect.GetHeight(), 200);
}

/**
* @tc.name: AccessibilityRectTest003
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest003, TestSize.Level1)
{
    // rotate center (100, 100)
    AccessibilityRect rect(0, 0, 100, 100);
    // rotate 90
    rect.Rotate(0, 0, QUARTER_ANGLE);
    EXPECT_EQ(rect.GetWidth(), 100);
    EXPECT_EQ(rect.GetHeight(), 100);
}

/**
* @tc.name: AccessibilityRectTest004
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest004, TestSize.Level1)
{
    AccessibilityRect rect(0, 0, 100, 200);

    // 450 ≡ 90
    rect.Rotate(450);
    EXPECT_EQ(rect.GetWidth(), 200);

    // 720 ≡ 0
    rect.Rotate(FULL_ANGLE * 2);
    EXPECT_EQ(rect.GetWidth(), 200);
}

/**
* @tc.name: AccessibilityRectTest005
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest005, TestSize.Level1)
{
    AccessibilityRect rect(10, 20, 30, 40);
    rect.Rotate(ZERO_ANGLE);
    EXPECT_EQ(rect.GetX(), 10);
    EXPECT_EQ(rect.GetY(), 20);
    EXPECT_EQ(rect.GetWidth(), 30);
    EXPECT_EQ(rect.GetHeight(), 40);

    rect.Rotate(FULL_ANGLE);
    EXPECT_EQ(rect.GetWidth(), 30);
}

/**
* @tc.name: AccessibilityRectTest006
* @tc.desc: AccessibilityRect
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityRectTest006, TestSize.Level1)
{
    AccessibilityRect rect(10, 20, 100, 200);
    RotateTransform transform(0, 50, 60, 30, 40);

    // 2x, 3y
    rect.ApplyTransformation(transform, 2.0f, 3.0f);

    // x = (10 - 30)*2 + 50 = (-20)*2 +50 = 10
    EXPECT_EQ(rect.GetX(), 10.0f);
    // y = (20 -40)*3 +60 = (-20)*3 +60 = 0
    EXPECT_EQ(rect.GetY(), 0);
    // width = 100*2 = 200
    EXPECT_EQ(rect.GetWidth(), 200);
    // height = 200*3 = 600
    EXPECT_EQ(rect.GetHeight(), 600);
}

/**
* @tc.name: IsHandlePipelineAccessibilityHoverEnter001
* @tc.desc: IsHandlePipelineAccessibilityHoverEnter
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, IsHandlePipelineAccessibilityHoverEnter001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->context_ = nullptr;

    AccessibilityManagerNG manager{};
    bool result = manager.IsHandlePipelineAccessibilityHoverEnter(frameNode);
    EXPECT_FALSE(result);
}

/**
* @tc.name: IsHandlePipelineAccessibilityHoverEnter002
* @tc.desc: IsHandlePipelineAccessibilityHoverEnter
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, IsHandlePipelineAccessibilityHoverEnter002, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    
    AccessibilityManagerNG manager;
    bool result = manager.IsHandlePipelineAccessibilityHoverEnter(frameNode);
    EXPECT_FALSE(result);
}

/**
* @tc.name: IsHandlePipelineAccessibilityHoverEnter003
* @tc.desc: IsHandlePipelineAccessibilityHoverEnter
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, IsHandlePipelineAccessibilityHoverEnter003, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    auto pipe = MockPipelineContext::GetCurrent();
    frameNode->context_ = AceType::RawPtr(pipe);
    AccessibilityManagerNG manager;
    bool result = manager.IsHandlePipelineAccessibilityHoverEnter(frameNode);
    EXPECT_FALSE(result);
}

/**
* @tc.name: AccessibilityHoverStateManager001
* @tc.desc: Test GetHoverState and ResetHoverState func
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, AccessibilityHoverStateManager001, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    AccessibilityHoverStateManager  manager;
    auto& hoverState = manager.GetHoverState(frameNode->GetAccessibilityId());
    EXPECT_EQ(manager.hoverStateMap_.size(), 1);

    hoverState.idle = false;
    auto& hoverStateNew = manager.GetHoverState(frameNode->GetAccessibilityId());
    EXPECT_EQ(manager.hoverStateMap_.size(), 1);
    EXPECT_FALSE(hoverStateNew.idle);

    manager.ResetHoverState(hoverStateNew);
    EXPECT_TRUE(hoverStateNew.idle);
}

/**
* @tc.name: HandlePipelineAccessibilityHoverEnter001
* @tc.desc: HandlePipelineAccessibilityHoverEnter
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, HandlePipelineAccessibilityHoverEnter001, TestSize.Level1) {
    AccessibilityManagerNG manager;
    auto frameNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    TouchEvent event;
    int32_t eventType;
    // Case 1: Test with AccessibilityHoverEventType::ENTER
    eventType = static_cast<int32_t>(AccessibilityHoverEventType::ENTER);
    manager.HandlePipelineAccessibilityHoverEnter(frameNode, event, eventType);

    // Case 2: Test with AccessibilityHoverEventType::MOVE
    eventType = static_cast<int32_t>(AccessibilityHoverEventType::MOVE);
    manager.HandlePipelineAccessibilityHoverEnter(frameNode, event, eventType);

    // Case 3: Test with AccessibilityHoverEventType::EXIT
    eventType = static_cast<int32_t>(AccessibilityHoverEventType::EXIT);
    manager.HandlePipelineAccessibilityHoverEnter(frameNode, event, eventType);

    // Case 4: Test with an invalid event type (default case)
    eventType = -1; // Invalid type
    manager.HandlePipelineAccessibilityHoverEnter(frameNode, event, eventType);
}

/**
* @tc.name: HandleAccessibilityHoverEventBySurfaceId
* @tc.desc: HandleAccessibilityHoverEventBySurfaceId001
* @tc.type: FUNC
*/
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEventBySurfaceId001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    auto pipe = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipe, nullptr);

    auto exportNode = FrameNode::CreateFrameNode(
        "exportNode",
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(exportNode, nullptr);
    exportNode->context_ = AceType::RawPtr(pipe);

    ElementRegister::GetInstance()->RegisterEmbedNode(1U, exportNode);

    auto rootElement = pipe->GetRootElement();
    ASSERT_NE(rootElement, nullptr);
    rootElement->AddChild(exportNode);

    AccessibilityManagerNG manager;
    std::stringstream ss;
    ss << 1U;
    PointF point(POINT_X, POINT_Y);
    TimeStamp time((std::chrono::milliseconds(TIMEMS_DIFFERENT_HOVER_SOURCE)));
    HandleHoverEventParam param {
        .point = point,
        .time = time,
        .sourceType = SourceType::MOUSE,
        .eventType = AccessibilityHoverEventType::ENTER
    };
    auto ret = manager.HandleAccessibilityHoverEventBySurfaceId(ss.str(), param);
    EXPECT_EQ(ret, HandleHoverRet::HOVER_FAIL);

    MockPipelineContext::TearDown();
}

/**
 * @tc.name: HandleAccessibilityHoverEventInner001
 * @tc.desc: HandleAccessibilityHoverEventInner
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEventInner001, TestSize.Level1)
{
    MockPipelineContext::SetUp();
    auto pipe = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipe, nullptr);

    auto frameNode = FrameNode::CreateFrameNode(
        "testNode",
        ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->context_ = AceType::RawPtr(pipe);

    AccessibilityManagerNG manager;
    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    TouchEvent touchEvent;
    PointF point(10.0f, 20.0f);
    TimeStamp baseTime((std::chrono::milliseconds(100)));

    hoverState.idle = true;
    HandleHoverEventParam param1 {
        .point = point,
        .time = baseTime,
        .sourceType = SourceType::MOUSE,
        .eventType = AccessibilityHoverEventType::ENTER
    };
    auto ret = manager.HandleAccessibilityHoverEventInner(frameNode, param1, touchEvent);
    EXPECT_TRUE(ret == HandleHoverRet::HOVER_FAIL);

    hoverState.idle = false;
    hoverState.time = baseTime;
    hoverState.eventType = AccessibilityHoverEventType::MOVE;
    HandleHoverEventParam param2 = param1;
    param2.eventType = AccessibilityHoverEventType::MOVE;
    param2.time = baseTime + std::chrono::milliseconds(5);
    ret = manager.HandleAccessibilityHoverEventInner(frameNode, param2, touchEvent);
    EXPECT_EQ(ret, HandleHoverRet::IN_TIME_LIMIT);

    hoverState.idle = false;
    hoverState.time = baseTime;
    hoverState.eventType = AccessibilityHoverEventType::MOVE;
    HandleHoverEventParam param3 = param1;
    param3.eventType = AccessibilityHoverEventType::EXIT;
    param3.time = baseTime + std::chrono::milliseconds(5);
    ret = manager.HandleAccessibilityHoverEventInner(frameNode, param3, touchEvent);
    EXPECT_TRUE(ret == HandleHoverRet::HOVER_FAIL);
    MockPipelineContext::TearDown();
}

/**
 * @tc.name: HandleAccessibilityHoverEventInner002
 * @tc.desc: HandleAccessibilityHoverEventInner
 * @tc.type: FUNC
 */
HWTEST_F(AccessibilityManagerNgTestNg, HandleAccessibilityHoverEventInner002, TestSize.Level1)
{
    // Step 1: Set up the mock pipeline context.
    MockPipelineContext::SetUp();
    auto pipe = MockPipelineContext::GetCurrent();
    ASSERT_NE(pipe, nullptr);
    // Step 2: Create a FrameNode and set its context.
    auto frameNode = FrameNode::CreateFrameNode("testNode", ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    frameNode->context_ = AceType::RawPtr(pipe);

    AccessibilityManagerNG manager;
    // Step 3: Get the hover state for the frame node.
    auto& hoverState = manager.hoverStateManager_.GetHoverState(frameNode->GetAccessibilityId());
    TouchEvent touchEvent;
    PointF point(10.0f, 20.0f);
    TimeStamp baseTime((std::chrono::milliseconds(100)));
    // Step 4: Prepare a hover event param with idle state.
    hoverState.idle = true;
    HandleHoverEventParam param1 {
        .point = point,
        .time = baseTime,
        .sourceType = SourceType::MOUSE,
        .eventType = AccessibilityHoverEventType::ENTER
    };
    // Step 5: Simulate previous event from TOUCH, current event from MOUSE, interval 2000ms.
    hoverState.idle = false;
    hoverState.source = SourceType::TOUCH;
    hoverState.time = baseTime;
    HandleHoverEventParam param5 = param1;
    param5.sourceType = SourceType::MOUSE;
    param5.eventType = AccessibilityHoverEventType::MOVE;
    param5.time = baseTime + std::chrono::milliseconds(2000);

    auto ret = manager.HandleAccessibilityHoverEventInner(frameNode, param5, touchEvent);
    EXPECT_TRUE(ret == HandleHoverRet::HOVER_FAIL);
    // Step 6: Previous event from MOUSE, current event ENTER, interval 50ms.
    hoverState.idle = false;
    hoverState.source = SourceType::MOUSE;
    hoverState.time = baseTime;
    HandleHoverEventParam param6 = param1;
    param6.eventType = AccessibilityHoverEventType::ENTER;
    param6.time = baseTime + std::chrono::milliseconds(50);
    ret = manager.HandleAccessibilityHoverEventInner(frameNode, param6, touchEvent);
    EXPECT_TRUE(ret == HandleHoverRet::HOVER_FAIL);
    // Step 7: Pass nullptr as frameNode, expect HOVER_FAIL.
    ret = manager.HandleAccessibilityHoverEventInner(nullptr, param1, touchEvent);
    EXPECT_EQ(ret, HandleHoverRet::HOVER_FAIL);
    // Step 8: Previous event from TOUCH, current event from MOUSE, interval 500ms.
    hoverState.idle = false;
    hoverState.source = SourceType::TOUCH;
    hoverState.time = baseTime;
    HandleHoverEventParam param4 = param1;
    param4.sourceType = SourceType::MOUSE;
    param4.eventType = AccessibilityHoverEventType::MOVE;
    param4.time = baseTime + std::chrono::milliseconds(500);
    ret = manager.HandleAccessibilityHoverEventInner(frameNode, param4, touchEvent);
    EXPECT_EQ(ret, HandleHoverRet::IN_TIME_LIMIT);
    MockPipelineContext::TearDown();
}
} // namespace OHOS::Ace::NG