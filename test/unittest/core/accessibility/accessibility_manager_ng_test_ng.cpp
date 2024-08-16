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
} // namespace

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
    EXPECT_EQ(mouseEvent.action, MouseAction::PULL_UP);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    accessibilityManagerNg.hoverState_.idle = false;
    mouseEvent.sourceType = SourceType::MOUSE;
    mouseEvent.action = MouseAction::MOVE;
    
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    accessibilityManagerNg.hoverState_.idle = true;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    TimeStamp time;
    accessibilityManagerNg.hoverState_.time = time;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(false);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, mouseEvent);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(nullptr, mouseEvent);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.source, SourceType::MOUSE);
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
    EXPECT_EQ(touchEvent.type, TouchType::HOVER_EXIT);
    touchEvent.type = TouchType::UNKNOWN;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.sourceType = SourceType::TOUCH;
    touchEvent.SetPointers(POINTERS);
    touchEvent.pointers.push_back(pointOne);
    touchEvent.pointers.push_back(pointTwo);
    touchEvent.type = TouchType::HOVER_ENTER;
    accessibilityManagerNg.hoverState_.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    touchEvent.SetPointers(POINTERS);
    touchEvent.pointers.push_back(pointOne);
    touchEvent.pointers.push_back(pointTwo);
    accessibilityManagerNg.hoverState_.source = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.sourceType = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);

    touchEvent.type = TouchType::UNKNOWN;
    touchEvent.x = 100;
    touchEvent.y = 100;
    accessibilityManagerNg.hoverState_.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    accessibilityManagerNg.hoverState_.idle = true;
    touchEvent.sourceType = SourceType::TOUCH;
    accessibilityManagerNg.hoverState_.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(touchEvent.type, TouchType::UNKNOWN);
    
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
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, SOURCETYPE, EVENTTYPE, TIMEMS);

    accessibilityManagerNg.hoverState_.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.idle, false);
    WeakPtr<FrameNode> nodesHovering1;
    WeakPtr<FrameNode> nodesHovering2;
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(nodesHovering1);
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(nodesHovering2);
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(frameNode);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_NE(accessibilityManagerNg.hoverState_.nodesHovering.size(), 0);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, -1, EVENTTYPE, TIMEMS);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 99, EVENTTYPE, TIMEMS);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.idle, false);

    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    accessibilityManagerNg.hoverState_.idle = false;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    accessibilityManagerNg.hoverState_.idle = true;
    accessibilityManagerNg.hoverState_.source = SourceType::NONE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, LARGETIMEMS);
    accessibilityManagerNg.hoverState_.idle = true;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 0, EVENTTYPE, TIMEMS);

    int32_t eventTypeEnter = static_cast<int32_t>(AccessibilityHoverEventType::ENTER);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, 0, eventTypeEnter, TIMEMS);
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y, SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(AceApplicationInfo::GetInstance().IsAccessibilityEnabled(), true);
    accessibilityManagerNg.hoverState_.idle = true;
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
    PointerEvent pointerEvent;

    TimeStamp time;
    
    accessibilityManagerNg.HoverTestDebug(frameNode, hoverPoint, summary, detail);
    auto result = accessibilityManagerNg.DeliverAccessibilityHoverEvent(frameNode, hoverPoint);
    EXPECT_EQ(result, false);
    accessibilityManagerNg.IgnoreCurrentHoveringNode(frameNode);

    auto eventHub = frameNode->GetEventHub<EventHub>();
    eventHub->SetEnabled(false);
    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    eventHub->SetEnabled(true);
    accessibilityManagerNg.NotifyHoverEventToNodeSession(frameNode, frameNode,
        hoverPoint, SourceType::MOUSE, AccessibilityHoverEventType::ENTER, time);
    PointF pointNode(hoverPoint);
    result = accessibilityManagerNg.ConvertPointFromAncestorToNode(frameNode, frameNode, hoverPoint, pointNode);
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

    // for lastNodesHovering
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);
    accessibilityManagerNg.hoverState_.idle = true;
    WeakPtr<FrameNode> nodesHovering1;
    WeakPtr<FrameNode> nodesHovering2;
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(nodesHovering1);
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(nodesHovering2);
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(frameNode);

    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, POINT_X, POINT_Y,
        SOURCETYPETWO, EVENTTYPE, TIMEMS);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.nodesHovering.size(), 0);

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

    // pointers.size
    TouchEvent touchEvent;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    accessibilityManagerNg.hoverState_.idle = true;
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

    accessibilityManagerNg.hoverState_.source = SourceType::TOUCH;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.idle, true);

    accessibilityManagerNg.hoverState_.source = SourceType::MOUSE;
    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.idle, false);
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

    accessibilityManagerNg.hoverState_.idle = false;
    accessibilityManagerNg.hoverState_.nodesHovering.push_back(frameNode);

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

    EXPECT_NE(accessibilityManagerNg.hoverState_.nodesHovering.size(), 0);
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

    // hoverState source different and time is in MIN_SOURCE_CHANGE_GAP_MS
    TouchEvent touchEvent;
    AceApplicationInfo::GetInstance().SetAccessibilityEnabled(true);

    accessibilityManagerNg.hoverState_.idle = false;
    touchEvent.type = TouchType::HOVER_ENTER;

    touchEvent.SetPointers(POINTERS);

    touchEvent.sourceType = SourceType::TOUCH;
    accessibilityManagerNg.hoverState_.source = SourceType::MOUSE;
    TimeStamp time((std::chrono::milliseconds(TIMEMS_DIFFERENT_HOVER_SOURCE)));
    touchEvent.time = time;

    accessibilityManagerNg.HandleAccessibilityHoverEvent(frameNode, touchEvent);
    EXPECT_EQ(accessibilityManagerNg.hoverState_.idle, false);
}
} // namespace OHOS::Ace::NG