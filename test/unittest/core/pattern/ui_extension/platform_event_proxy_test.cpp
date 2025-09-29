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

#include "gtest/gtest.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "adapter/ohos/osal/want_wrap_ohos.h"
#include "core/components_ng/pattern/ui_extension/isolated_component/isolated_pattern.h"
#include "core/components_ng/pattern/ui_extension/platform_event_proxy.h"
#include "core/components_ng/pattern/ui_extension/platform_pattern.h"
#include "frameworks/core/event/pointer_event.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    const std::string ISOLATED_COMPONENT_ETS_TAG = "IsolatedComponent";
    const std::string EVENT_PROXT_EMPTY = "[]";
    const std::string EVENT_PROXT_CLICK = "[Click]";
    const std::string EVENT_PROXT_LONG_PRESS = "[LongPress]";
    const std::string EVENT_PROXT_PAN_GESTURE_UP_STR = "[Up]";
    const std::string EVENT_PROXT_PAN_GESTURE_LEFT_STR = "[Left]";
    const std::string EVENT_PROXT_PAN_GESTURE_VERTICAL = "[Up, Down]";
    const std::string EVENT_PROXT_PAN_GESTURE_HORIZONTAL = "[Left, Right]";
    const std::string EVENT_PROXT_PAN_GESTURE_ALL = "[Left, Up]";
} // namespace

class PlatformEventProxyTestNg : public testing::Test {
public:
    void SetUp() override;
    void TearDown() override;

    bool CheckClickEvent(const RefPtr<FrameNode> &host);
    bool CheckClickEvent(const RefPtr<PlatformEventProxy> &eventProxy);
    bool CheckLongPressEvent(const RefPtr<FrameNode> &host);
    bool CheckLongPressEvent(const RefPtr<PlatformEventProxy> &eventProxy);
    bool CheckPanGestureEvent(const RefPtr<FrameNode> &host);
    bool CheckPanGestureEvent(const RefPtr<PlatformEventProxy> &eventProxy, uint32_t panDirection);
    bool CheckPanGestureVerticalEvent(const RefPtr<PlatformEventProxy> &eventProxy);
    bool CheckPanGestureHorizontalEvent(const RefPtr<PlatformEventProxy> &eventProxy);
};

void PlatformEventProxyTestNg::SetUp() {}

void PlatformEventProxyTestNg::TearDown() {}

bool PlatformEventProxyTestNg::CheckClickEvent(
    const RefPtr<FrameNode> &host)
{
    CHECK_NULL_RETURN(host, true);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, true);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, true);
    return !gestureHub->IsClickEventsEmpty();
}

bool PlatformEventProxyTestNg::CheckClickEvent(
    const RefPtr<PlatformEventProxy> &eventProxy)
{
    CHECK_NULL_RETURN(eventProxy, true);
    return eventProxy->HasEventProxy(
        static_cast<int32_t>(EventProxyFlag::EVENT_CLICK));
}

bool PlatformEventProxyTestNg::CheckLongPressEvent(
    const RefPtr<FrameNode> &host)
{
    CHECK_NULL_RETURN(host, true);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, true);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, true);
    return gestureHub->IsLongClickable();
}

bool PlatformEventProxyTestNg::CheckLongPressEvent(
    const RefPtr<PlatformEventProxy> &eventProxy)
{
    CHECK_NULL_RETURN(eventProxy, true);
    return eventProxy->HasEventProxy(
        static_cast<int32_t>(EventProxyFlag::EVENT_LONG_PRESS));
}

bool PlatformEventProxyTestNg::CheckPanGestureEvent(
    const RefPtr<FrameNode> &host)
{
    CHECK_NULL_RETURN(host, true);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(hub, true);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_RETURN(gestureHub, true);
    return !gestureHub->IsPanEventEmpty();
}

bool PlatformEventProxyTestNg::CheckPanGestureEvent(
    const RefPtr<PlatformEventProxy> &eventProxy, uint32_t panDirection)
{
    CHECK_NULL_RETURN(eventProxy, true);
    bool ret = true;
    switch (panDirection) {
        case PanDirection::VERTICAL:
            ret = eventProxy->HasEventProxy(
                static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP
                | EventProxyFlag::EVENT_PAN_GESTURE_DOWN));
            break;
        case PanDirection::HORIZONTAL:
            ret = eventProxy->HasEventProxy(
                static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT
                | EventProxyFlag::EVENT_PAN_GESTURE_RIGHT));
            break;
        case PanDirection::ALL:
            ret = eventProxy->HasEventProxy(
                static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP
                | EventProxyFlag::EVENT_PAN_GESTURE_DOWN
                | EventProxyFlag::EVENT_PAN_GESTURE_LEFT
                | EventProxyFlag::EVENT_PAN_GESTURE_RIGHT));
            break;
        default:
            ret = eventProxy->HasEventProxy(static_cast<int32_t>(panDirection));
    }

    return ret;
}

bool PlatformEventProxyTestNg::CheckPanGestureVerticalEvent(
    const RefPtr<PlatformEventProxy> &eventProxy)
{
    return CheckPanGestureEvent(eventProxy, PanDirection::VERTICAL);
}

bool PlatformEventProxyTestNg::CheckPanGestureHorizontalEvent(
    const RefPtr<PlatformEventProxy> &eventProxy)
{
    return CheckPanGestureEvent(eventProxy, PanDirection::HORIZONTAL);
}

/**
 * @tc.name: AddEventProxy001
 * @tc.desc: Test PlatformEventProxy SetClickEventProxy
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy001, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() {
            return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    ASSERT_EQ(CheckClickEvent(isolatedNode), false);
    ASSERT_EQ(CheckClickEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);

    /**
     * @tc.steps: step2. First add
     */
    EventProxyResultCode code = eventProxy->SetClickEventProxy(gestureHub, true);
    ASSERT_EQ(code, EventProxyResultCode::ADD_WHEN_ADDING);
    ASSERT_EQ(CheckClickEvent(isolatedNode), true);
    ASSERT_EQ(CheckClickEvent(eventProxy), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_CLICK);

    /**
     * @tc.steps: step3. Second add
     */
    code = eventProxy->SetClickEventProxy(gestureHub, true);
    ASSERT_EQ(code, EventProxyResultCode::EXIST_WHEN_ADDING);
    ASSERT_EQ(CheckClickEvent(isolatedNode), true);
    ASSERT_EQ(CheckClickEvent(eventProxy), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_CLICK);

    /**
     * @tc.steps: step4. First Delete
     */
    code = eventProxy->SetClickEventProxy(gestureHub, false);
    ASSERT_EQ(code, EventProxyResultCode::REMOVE_WHEN_DELETE);
    ASSERT_EQ(CheckClickEvent(isolatedNode), false);
    ASSERT_EQ(CheckClickEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);

    /**
     * @tc.steps: step5. Second Delete
     */
    code = eventProxy->SetClickEventProxy(gestureHub, false);
    ASSERT_EQ(code, EventProxyResultCode::NO_EXIST_WHEN_DELETE);
    ASSERT_EQ(CheckClickEvent(isolatedNode), false);
    ASSERT_EQ(CheckClickEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
#endif
}

/**
 * @tc.name: AddEventProxy002
 * @tc.desc: Test PlatformEventProxy SetLongPressEventProxy
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy002, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId,
        []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    ASSERT_EQ(CheckLongPressEvent(isolatedNode), false);
    ASSERT_EQ(CheckLongPressEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);

    /**
     * @tc.steps: step2. First add
     */
    EventProxyResultCode code = eventProxy->SetLongPressEventProxy(gestureHub, true);
    ASSERT_EQ(code, EventProxyResultCode::ADD_WHEN_ADDING);
    ASSERT_EQ(CheckLongPressEvent(isolatedNode), true);
    ASSERT_EQ(CheckLongPressEvent(eventProxy), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_LONG_PRESS);

    /**
     * @tc.steps: step3. Second add
     */
    code = eventProxy->SetLongPressEventProxy(gestureHub, true);
    ASSERT_EQ(code, EventProxyResultCode::EXIST_WHEN_ADDING);
    ASSERT_EQ(CheckLongPressEvent(isolatedNode), true);
    ASSERT_EQ(CheckLongPressEvent(eventProxy), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_LONG_PRESS);

    /**
     * @tc.steps: step4. First Delete
     */
    code = eventProxy->SetLongPressEventProxy(gestureHub, false);
    ASSERT_EQ(code, EventProxyResultCode::REMOVE_WHEN_DELETE);
    ASSERT_EQ(CheckLongPressEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);

    /**
     * @tc.steps: step4. Second Delete
     */
    code = eventProxy->SetLongPressEventProxy(gestureHub, false);
    ASSERT_EQ(code, EventProxyResultCode::NO_EXIST_WHEN_DELETE);
    ASSERT_EQ(CheckLongPressEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
#endif
}

/**
 * @tc.name: AddEventProxy003
 * @tc.desc: Test PlatformEventProxy SetPanGestureEventProxy Vertical
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy003, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() {
            return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. SetPanGestureEventProxy EventProxyFlag::EVENT_PAN_GESTURE_UP
     */
    EventProxyResultCode code = eventProxy->SetPanGestureEventProxy(gestureHub,
        eventProxy->GetPanDirection(EventProxyFlag::EVENT_PAN_GESTURE_UP));
    ASSERT_EQ(code, EventProxyResultCode::ADD_WHEN_ADDING);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_UP_STR);
    /**
     * @tc.steps: step3. SetPanGestureEventProxy EventProxyFlag::EVENT_NONE
     */
    code = eventProxy->SetPanGestureEventProxy(gestureHub,
        eventProxy->GetPanDirection(EventProxyFlag::EVENT_NONE));
    ASSERT_EQ(code, EventProxyResultCode::REMOVE_WHEN_DELETE);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), false);
    EXPECT_NE(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_UP_STR);
#endif
}

/**
 * @tc.name: AddEventProxy004
 * @tc.desc: Test PlatformEventProxy SetPanGestureEventProxy Horizontal
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy004, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() {
            return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. SetPanGestureEventProxy EventProxyFlag::EVENT_PAN_GESTURE_LEFT
     */
    EventProxyResultCode code = eventProxy->SetPanGestureEventProxy(gestureHub,
        eventProxy->GetPanDirection(EventProxyFlag::EVENT_PAN_GESTURE_LEFT));
    ASSERT_EQ(code, EventProxyResultCode::ADD_WHEN_ADDING);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), true);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_LEFT_STR);
    /**
     * @tc.steps: step3. SetPanGestureEventProxy EventProxyFlag::EVENT_NONE
     */
    code = eventProxy->SetPanGestureEventProxy(gestureHub,
        eventProxy->GetPanDirection(EventProxyFlag::EVENT_NONE));
    ASSERT_EQ(code, EventProxyResultCode::REMOVE_WHEN_DELETE);
    ASSERT_EQ(CheckPanGestureEvent(isolatedNode), false);
    EXPECT_NE(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_LEFT_STR);
#endif
}

/**
 * @tc.name: AddEventProxy005
 * @tc.desc: Test PlatformEventProxy GetPanDirection
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy005, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    /**
     * @tc.steps: step1. Test EventProxyFlag::EVENT_NONE
     */
    uint32_t panDirection = eventProxy->GetPanDirection(EventProxyFlag::EVENT_NONE);
    ASSERT_EQ(panDirection, PanDirection::NONE);
#endif
}

/**
 * @tc.name: AddEventProxy006
 * @tc.desc: Test PlatformEventProxy SetEventProxyFlag Normal Flag
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy006, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId,
        []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. Only left
     */
    eventProxy->SetEventProxyFlag(1);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), false);
    /**
     * @tc.steps: step3. Only right
     */
    eventProxy->SetEventProxyFlag(2);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), false);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), true);
    /**
     * @tc.steps: step4. left right
     */
    eventProxy->SetEventProxyFlag(3);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), true);
    /**
     * @tc.steps: step5. Only up
     */
    eventProxy->SetEventProxyFlag(4);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), false);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), false);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP)), true);
#endif
}


/**
 * @tc.name: AddEventProxy007
 * @tc.desc: Test PlatformEventProxy SetEventProxyFlag Normal Flag
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy007, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId,
        []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step1. left up
     */
    eventProxy->SetEventProxyFlag(5);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP)), true);
    /**
     * @tc.steps: step2. right up
     */
    eventProxy->SetEventProxyFlag(6);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP)), true);
    /**
     * @tc.steps: step3. left right and up
     */
    eventProxy->SetEventProxyFlag(7);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_RIGHT)), true);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP)), true);
    /**
     * @tc.steps: step4. down
     */
    eventProxy->SetEventProxyFlag(8);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP)), false);
    EXPECT_EQ(eventProxy->HasEventProxy(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_DOWN)), true);
#endif
}

/**
 * @tc.name: AddEventProxy008
 * @tc.desc: Test PlatformEventProxy Delete EventProxy
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy008, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId,
        []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. All
     */
    eventProxy->SetEventProxyFlag(15);
    EXPECT_EQ(eventProxy->HasEventProxy(15), true);

    /**
     * @tc.steps: step3. Delete LongPress
     */
    eventProxy->SetEventProxyFlag(5);
    EXPECT_EQ(eventProxy->HasEventProxy(5), true);

    /**
     * @tc.steps: step4. Delete All
     */
    eventProxy->SetEventProxyFlag(0);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
#endif
}

/**
 * @tc.name: AddEventProxy009
 * @tc.desc: Test PlatformEventProxy Exception Num
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy009, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId,
        []() { return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. 16
     */
    eventProxy->SetEventProxyFlag(16);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step4. 17
     */
    eventProxy->SetEventProxyFlag(17);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_LEFT_STR);
#endif
}

/**
 * @tc.name: AddEventProxy010
 * @tc.desc: Test PlatformEventProxy GetCurEventProxyToString
 * @tc.type: FUNC
 */
HWTEST_F(PlatformEventProxyTestNg, AddEventProxy010, TestSize.Level1)
{
#ifdef OHOS_STANDARD_SYSTEM
    /**
     * @tc.steps: step1. construct a IsolatedComponent Node
     */
    auto isolatedNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto isolatedNode = FrameNode::GetOrCreateFrameNode(
        ISOLATED_COMPONENT_ETS_TAG, isolatedNodeId, []() {
            return AceType::MakeRefPtr<IsolatedPattern>(); });
    CHECK_NULL_VOID(isolatedNode);
    RefPtr<PlatformEventProxy> eventProxy = AceType::MakeRefPtr<PlatformEventProxy>();
    CHECK_NULL_VOID(eventProxy);
    eventProxy->SetHostNode(isolatedNode);
    auto hub = isolatedNode->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    ASSERT_EQ(CheckClickEvent(isolatedNode), false);
    ASSERT_EQ(CheckClickEvent(eventProxy), false);
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_EMPTY);
    /**
     * @tc.steps: step2. Test click、longPress、PanGesture and so on
     */
    eventProxy->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_CLICK));
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_CLICK);

    eventProxy->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_LONG_PRESS));
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_LONG_PRESS);

    eventProxy->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_UP
        | EventProxyFlag::EVENT_PAN_GESTURE_DOWN));
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_VERTICAL);

    eventProxy->SetEventProxyFlag(static_cast<int32_t>(EventProxyFlag::EVENT_PAN_GESTURE_LEFT
        | EventProxyFlag::EVENT_PAN_GESTURE_RIGHT));
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_HORIZONTAL);

    eventProxy->SetEventProxyFlag(static_cast<int32_t>(
        EventProxyFlag::EVENT_PAN_GESTURE_UP | EventProxyFlag::EVENT_PAN_GESTURE_LEFT));
    EXPECT_EQ(eventProxy->GetCurEventProxyToString(), EVENT_PROXT_PAN_GESTURE_ALL);
#endif
}
} // namespace OHOS::Ace::NG
