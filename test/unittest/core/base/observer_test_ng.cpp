/*
 * Copyright (c) 2023 iSoftStone Information Technology (Group) Co.,Ltd.
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

#define protected public
#define private public

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/interfaces/native/implementation/gesture_trigger_info_peer.h"
#include "test/mock/frameworks/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float DEFAULT_DENSITY = 3.5f;
const float DEFAULT_NODE_OFFSET = 200.5f;
const int32_t DEFAULT_PARENT_NODE_ID = 1;
const int32_t DEFAULT_NODE_ID = 2;

bool g_panGestureHandleFuncCalled = false;
bool g_willClickHandleFuncCalled = false;
bool g_didClickHandleFuncCalled = false;
} // namespace
class ObserverTestNg : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
};

void ObserverTestNg::SetUpTestCase()
{
    MockContainer::SetUp();
}

void ObserverTestNg::TearDownTestCase()
{
    MockContainer::TearDown();
}


/**
 * @tc.name: ObserverTestNg001
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg001, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pattern = contentNode->GetPattern<NavDestinationPattern>();
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(AceType::WeakClaim(Referenced::RawPtr(pattern)),
                                                                 NavDestinationState::ON_SHOWN);
    ASSERT_EQ(UIObserverHandler::GetInstance().navigationHandleFunc_, nullptr);
    auto pattern1 = navigation->GetPattern<NavigationPattern>();
    pattern1->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    UIObserverHandler::GetInstance().NotifyNavigationStateChange(AceType::WeakClaim(Referenced::RawPtr(pattern1)),
                                                                 NavDestinationState::ON_SHOWN);
    ASSERT_EQ(UIObserverHandler::GetInstance().navigationHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg002
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg002, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);

    auto pattern = contentNode->GetPattern<NavDestinationPattern>();
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));

    auto info = UIObserverHandler::GetInstance().GetNavigationState(nullptr);
    ASSERT_EQ(info, nullptr);

    info = UIObserverHandler::GetInstance().GetNavigationState(navigation);
    ASSERT_EQ(info, nullptr);

    ASSERT_EQ(pattern->GetNavigationNode(), navigation);

    info = UIObserverHandler::GetInstance().GetNavigationState(contentNode);
    ASSERT_NE(info, nullptr);
    ASSERT_EQ(info->name, "test_name");
    ASSERT_EQ(info->navigationId, "");
    ASSERT_EQ(info->state, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: ObserverTestNg003
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg003, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 12, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(AceType::WeakClaim(Referenced::RawPtr(pattern)),
                                                                 ScrollEventType::SCROLL_START);
    ASSERT_EQ(UIObserverHandler::GetInstance().scrollEventHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg004
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg004, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 12, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
    double offset = 0.0f;
    pattern->UpdateCurrentOffset(offset, SCROLL_FROM_AXIS);

    auto info = UIObserverHandler::GetInstance().GetScrollEventState(frameNode);
    ASSERT_EQ(info->id, frameNode->GetInspectorId().value_or(""));
    ASSERT_EQ(info->uniqueId, frameNode->GetId());
    ASSERT_EQ(info->scrollEvent, ScrollEventType::SCROLL_START);
    ASSERT_EQ(info->offset, offset);
    ASSERT_EQ(info->axis, pattern->GetAxis());
}

/**
 * @tc.name: ObserverTestNg005
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg005, TestSize.Level1)
{
    auto targetDensity = DEFAULT_DENSITY;
    UIObserverHandler::GetInstance().NotifyDensityChange(targetDensity);
    
    UIObserverHandler::GetInstance().densityHandleFunc_ = [](AbilityContextInfo& context, double density) -> void {
        EXPECT_EQ(density, DEFAULT_DENSITY);
    };
    UIObserverHandler::GetInstance().densityHandleFuncForAni_ =
        [](AbilityContextInfo& context, double density) -> void { EXPECT_EQ(density, DEFAULT_DENSITY); };
    UIObserverHandler::GetInstance().NotifyDensityChange(targetDensity);
}

/**
 * @tc.name: ObserverTestNg006
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg006, TestSize.Level1)
{
    std::optional<NavDestinationInfo> from;
    std::optional<NavDestinationInfo> to;
    NavigationOperation operation = NavigationOperation::PUSH;
    UIObserverHandler::NavDestinationSwitchHandleFunc handleFunc = [](const AbilityContextInfo&,
                                                                       NavDestinationSwitchInfo& info) -> void {
        EXPECT_EQ(info.operation, NavigationOperation::PUSH);
    };
    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ = handleFunc;
    UIObserverHandler::GetInstance().NotifyNavDestinationSwitch(std::move(from), std::move(to), operation);
}

/**
 * @tc.name: ObserverTestNg007
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg007, TestSize.Level1)
{
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);
    RefPtr<FrameNode> frameNode = nullptr;

    UIObserverHandler::GetInstance().NotifyWillClick(gestureEventInfo, clickInfo, frameNode);
    ASSERT_EQ(UIObserverHandler::GetInstance().willClickHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg008
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg008, TestSize.Level1)
{
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);
    RefPtr<FrameNode> frameNode = nullptr;

    UIObserverHandler::GetInstance().NotifyDidClick(gestureEventInfo, clickInfo, frameNode);
    ASSERT_EQ(UIObserverHandler::GetInstance().didClickHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg009
 * @tc.desc: Test the func of GetHandleNavDestinationSwitchFunc
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg009, TestSize.Level1)
{
    std::optional<NavDestinationInfo> from;
    std::optional<NavDestinationInfo> to;
    UIObserverHandler::NavDestinationSwitchHandleFunc handleFunc = [](const AbilityContextInfo&,
                                                                       NavDestinationSwitchInfo&) -> void {};
    UIObserverHandler::GetInstance().navDestinationSwitchHandleFunc_ = handleFunc;
    UIObserverHandler::NavDestinationSwitchHandleFunc func =
        UIObserverHandler::GetInstance().GetHandleNavDestinationSwitchFunc();
    ASSERT_NE(handleFunc, nullptr);
    ASSERT_NE(func, nullptr);
}

/**
 * @tc.name: ObserverTestNg010
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg010, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);

    auto pattern = contentNode->GetPattern<NavDestinationPattern>();
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));

    auto info = UIObserverHandler::GetInstance().GetNavigationOuterState(nullptr);
    ASSERT_EQ(info, nullptr);

    info = UIObserverHandler::GetInstance().GetNavigationOuterState(navigation);
    ASSERT_EQ(info, nullptr);

    ASSERT_EQ(pattern->GetNavigationNode(), navigation);

    info = UIObserverHandler::GetInstance().GetNavigationOuterState(contentNode);
    ASSERT_EQ(info, nullptr);
}

/**
 * @tc.name: ObserverTestNg011
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg011, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);

    auto pattern = contentNode->GetPattern<NavDestinationPattern>();
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));

    auto info = UIObserverHandler::GetInstance().GetNavigationInnerState(nullptr);
    ASSERT_EQ(info, nullptr);

    info = UIObserverHandler::GetInstance().GetNavigationInnerState(navigation);
    ASSERT_EQ(info, nullptr);
}

/**
 * @tc.name: ObserverTestNg012
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg012, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<NavigationContentPattern>(); });
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);
    navDestination->SetParent(navigationContentNode);
    auto pattern = navDestination->GetPattern<NavDestinationPattern>();
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));

    auto info = UIObserverHandler::GetInstance().GetNavigationOuterState(nullptr);
    ASSERT_EQ(info, nullptr);

    info = UIObserverHandler::GetInstance().GetNavigationOuterState(navigation);
    ASSERT_EQ(info, nullptr);

    ASSERT_EQ(pattern->GetNavigationNode(), navigation);

    info = UIObserverHandler::GetInstance().GetNavigationOuterState(navDestination);
    ASSERT_NE(info, nullptr);
    ASSERT_EQ(info->name, "test_name");
    ASSERT_EQ(info->navigationId, "");
    ASSERT_EQ(info->state, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: ObserverTestNg013
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg013, TestSize.Level1)
{
    GestureEvent gestureEventInfo;
    RefPtr<FrameNode> frameNode = nullptr;
    const RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::AFTER, CurrentCallbackState::START };
    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(gestureEventInfo, current, frameNode, panGestureInfo);
    ASSERT_EQ(UIObserverHandler::GetInstance().panGestureHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg014
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg014, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, DEFAULT_NODE_ID, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto pattern = frameNode->GetPattern<ScrollablePattern>();

    /**
     * @tc.steps2: call the function NotifyScrollEventStateChange.
     * @tc.expected: The value of eventType is changed from SCROLL_START to SCROLL_STOP.
     */
    UIObserverHandler::GetInstance().NotifyScrollEventStateChange(AceType::WeakClaim(Referenced::RawPtr(pattern)),
                                                                ScrollEventType::SCROLL_STOP);
    /**
     * @tc.steps3: The function is called and the value of scrollEventHandleFunc_ is nullptr.
     */
    ASSERT_EQ(UIObserverHandler::GetInstance().scrollEventHandleFunc_, nullptr);
}

/**
 * @tc.name: ObserverTestNg015
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg015, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto navContentParent = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_CONTENT_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navContentParent->AddChild(navDestinationChild);
    navigation->AddChild(navContentParent);

    /**
     * @tc.steps2: call the function GetNavigationInnerState.
     * @tc.expected: The value of V2::NAVDESTINATION_VIEW_ETS_TAG && V2::NAVIGATION_CONTENT_ETS_TAG
     */
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);

    auto pattern = navDestinationChild->GetPattern<NavDestinationPattern>();
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));
    auto info = UIObserverHandler::GetInstance().GetNavigationInnerState(nullptr);
    ASSERT_EQ(info, nullptr);

    /**
     * @tc.steps3: Call the function GetNavigationInnerState again.
     * @tc.expected: The function is called and the value of info is not nullptr.
     */
    info = UIObserverHandler::GetInstance().GetNavigationInnerState(navigation);
    ASSERT_NE(info, nullptr);
    EXPECT_EQ(info->name, "test_name");
}

/**
 * @tc.name: ObserverTestNg016
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg016, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto parentFrame = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 100, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto parentPattern = parentFrame->GetPattern<ScrollablePattern>();
    parentPattern->UpdateCurrentOffset(DEFAULT_NODE_ID, SCROLL_FROM_AXIS);
    auto childFrame = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_COMPONENT_TAG, 101, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    childFrame->SetParent(parentFrame);
    
    /**
     * @tc.steps2: call the function GetScrollEventState.
     * @tc.expected: The function is called and the value of info is not nullptr.
     */
    auto info = UIObserverHandler::GetInstance().GetScrollEventState(childFrame);
    ASSERT_NE(info, nullptr);
    ASSERT_EQ(info->uniqueId, 100);
    ASSERT_NE(info->offset, DEFAULT_NODE_OFFSET);
}

/**
 * @tc.name: ObserverTestNg017
 * @tc.desc: Test the operation of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg017, TestSize.Level1)
{
    /**
     * @tc.steps1: initialize parameters.
     */
    auto parentFrame = FrameNode::GetOrCreateFrameNode(
        V2::PAGE_ETS_TAG, DEFAULT_PARENT_NODE_ID, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto parentPattern = parentFrame->GetPattern<ScrollablePattern>();
    parentPattern->UpdateCurrentOffset(DEFAULT_NODE_OFFSET, SCROLL_FROM_AXIS);
    
    /**
     * @tc.steps2: call the function GetOrCreateFrameNode.
     * @tc.expected: The value of current->GetTag() is PAGE_ETS_TAG
     */
    auto childFrame = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, DEFAULT_NODE_ID, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    childFrame->SetParent(parentFrame);

    /**
     * @tc.steps3: call the function GetOrCreateFrameNode again.
     * @tc.expected: The value of current->GetTag() is SCROLL_ETS_TAG
     */
    auto info = UIObserverHandler::GetInstance().GetRouterPageState(childFrame);
    ASSERT_EQ(info, nullptr);
}

/**
 * @tc.name: ObserverTestNg018
 * @tc.desc: Test the scroll direction of components
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg018, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, DEFAULT_NODE_ID, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    auto pattern = frameNode->GetPattern<ScrollablePattern>();
 
    pattern->SetAxis(Axis::VERTICAL);
    auto info = UIObserverHandler::GetInstance().GetScrollEventState(frameNode);
    ASSERT_EQ(info->axis, Axis::VERTICAL);
 
    pattern->SetAxis(Axis::HORIZONTAL);
    info = UIObserverHandler::GetInstance().GetScrollEventState(frameNode);
    ASSERT_EQ(info->axis, Axis::HORIZONTAL);
 
    pattern->SetAxis(Axis::NONE);
    info = UIObserverHandler::GetInstance().GetScrollEventState(frameNode);
    ASSERT_EQ(info->axis, Axis::NONE);
}

/**
 * @tc.name: ObserverTestNg019
 * @tc.desc: Test the TextChangeEventInfo of Observer
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg019, TestSize.Level1)
{
    int32_t uniqueId = 1;
    TextChangeEventInfo info("test1", uniqueId, "HelloWorld");
    UIObserverHandler::TextChangeEventHandleFunc handleFunc = [](const TextChangeEventInfo& info) -> void {
        EXPECT_EQ(info.id, "test1");
        EXPECT_EQ(info.uniqueId, 1);
        EXPECT_EQ(info.content, "HelloWorld");
    };
    UIObserverHandler::GetInstance().NotifyTextChangeEvent(info);
    UIObserverHandler::GetInstance().SetHandleTextChangeEventFunc(std::move(handleFunc));
}

/**
 * @tc.name: ObserverTestNg020
 * @tc.desc: Test the NotifyWinSizeLayoutBreakpointChangeFunc
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg020, TestSize.Level1)
{
    int32_t instanceId = 1;
    static bool callbackTriggered = false;
    callbackTriggered = false;
    WindowSizeBreakpoint breakpoint { WidthBreakpoint::WIDTH_XS, HeightBreakpoint::HEIGHT_SM };
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_FALSE(callbackTriggered);
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) {
            callbackTriggered = true;
        });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_TRUE(callbackTriggered);
}

/**
 * @tc.name: ObserverTestNg021
 * @tc.desc: Test the NotifyWinSizeLayoutBreakpointChangeFunc with ANI version callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg021, TestSize.Level1)
{
    int32_t instanceId = 2;
    static bool aniCallbackTriggered = false;
    aniCallbackTriggered = false;
    WindowSizeBreakpoint breakpoint { WidthBreakpoint::WIDTH_LG, HeightBreakpoint::HEIGHT_MD };
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_FALSE(aniCallbackTriggered);
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFuncAni(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) {
            EXPECT_EQ(instanceId, 2);
            EXPECT_EQ(breakpoint.widthBreakpoint, WidthBreakpoint::WIDTH_LG);
            EXPECT_EQ(breakpoint.heightBreakpoint, HeightBreakpoint::HEIGHT_MD);
            aniCallbackTriggered = true;
        });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_TRUE(aniCallbackTriggered);
}

/**
 * @tc.name: ObserverTestNg022
 * @tc.desc: Test both regular and ANI version callbacks work together
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg022, TestSize.Level1)
{
    int32_t instanceId = 3;
    static bool regularCallbackTriggered = false;
    static bool aniCallbackTriggered22 = false;
    regularCallbackTriggered = false;
    aniCallbackTriggered22 = false;
    WindowSizeBreakpoint breakpoint { WidthBreakpoint::WIDTH_SM, HeightBreakpoint::HEIGHT_LG };
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) {
            EXPECT_EQ(instanceId, 3);
            regularCallbackTriggered = true;
        });
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFuncAni(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) {
            EXPECT_EQ(instanceId, 3);
            aniCallbackTriggered22 = true;
        });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_TRUE(regularCallbackTriggered);
    EXPECT_TRUE(aniCallbackTriggered22);
}
/**
 * @tc.name: ObserverTestNg023
 * @tc.desc: Test callback replacement functionality
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg023, TestSize.Level1)
{
    int32_t instanceId = 3;
    static int firstCallbackCount = 0;
    static int secondCallbackCount = 0;
    firstCallbackCount = 0;
    secondCallbackCount = 0;
    WindowSizeBreakpoint breakpoint { WidthBreakpoint::WIDTH_MD, HeightBreakpoint::HEIGHT_MD };
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) { firstCallbackCount++; });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_EQ(firstCallbackCount, 1);
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) { secondCallbackCount++; });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_EQ(firstCallbackCount, 1);
    EXPECT_EQ(secondCallbackCount, 1);
}
/**
 * @tc.name: ObserverTestNg024
 * @tc.desc: Test setting callback to nullptr (clear callback)
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg024, TestSize.Level1)
{
    int32_t instanceId = 3;
    static bool callbackCalled = false;
    callbackCalled = false;
    WindowSizeBreakpoint breakpoint { WidthBreakpoint::WIDTH_SM, HeightBreakpoint::HEIGHT_SM };
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(
        [](int32_t instanceId, const WindowSizeBreakpoint& breakpoint) { callbackCalled = true; });
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_TRUE(callbackCalled);
    callbackCalled = false;
    UIObserverHandler::GetInstance().SetWinSizeLayoutBreakpointChangeFunc(nullptr);
    UIObserverHandler::GetInstance().NotifyWinSizeLayoutBreakpointChangeFunc(instanceId, breakpoint);
    EXPECT_FALSE(callbackCalled);
}

/**
 * @tc.name: ObserverTestNg025
 * @tc.desc: Test GlobalGestureListenerStorage::CombineKey generates correct combined key
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg025, TestSize.Level1)
{
    /**
     * @tc.steps1: Test CombineKey with TAP gesture type and WILL_START phase
     * @tc.expected: Combined key should be (TAP << 32 | WILL_START)
     */
    uint64_t key1 = GlobalGestureListenerStorage::CombineKey(
        GestureListenerType::TAP, GestureActionPhase::WILL_START);
    uint64_t expectedKey1 = (static_cast<uint64_t>(GestureListenerType::TAP) << 32) |
                             static_cast<uint64_t>(GestureActionPhase::WILL_START);
    EXPECT_EQ(key1, expectedKey1);

    /**
     * @tc.steps2: Test CombineKey with PAN gesture type and WILL_END phase
     * @tc.expected: Combined key should be (PAN << 32 | WILL_END)
     */
    uint64_t key2 = GlobalGestureListenerStorage::CombineKey(
        GestureListenerType::PAN, GestureActionPhase::WILL_END);
    uint64_t expectedKey2 = (static_cast<uint64_t>(GestureListenerType::PAN) << 32) |
                             static_cast<uint64_t>(GestureActionPhase::WILL_END);
    EXPECT_EQ(key2, expectedKey2);

    /**
     * @tc.steps3: Test CombineKey with LONG_PRESS gesture type and UNKNOWN phase
     * @tc.expected: Combined key should be (LONG_PRESS << 32 | UNKNOWN)
     */
    uint64_t key3 = GlobalGestureListenerStorage::CombineKey(
        GestureListenerType::LONG_PRESS, GestureActionPhase::UNKNOWN);
    uint64_t expectedKey3 = (static_cast<uint64_t>(GestureListenerType::LONG_PRESS) << 32) |
                             static_cast<uint64_t>(GestureActionPhase::UNKNOWN);
    EXPECT_EQ(key3, expectedKey3);
}

/**
 * @tc.name: ObserverTestNg026
 * @tc.desc: Test AddGlobalGestureListenerCallback and TriggerGlobalGestureListener
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg026, TestSize.Level1)
{
    /**
     * @tc.steps1: Create test trigger info and callback
     */
    GestureTriggerInfo testInfo;
    testInfo.currentPhase = static_cast<int32_t>(GestureActionPhase::WILL_START);

    static bool callbackTriggered = false;
    callbackTriggered = false;

    GlobalGestureListenerCallback callback = [&testInfo](const GestureTriggerInfo& info) {
        callbackTriggered = true;
        EXPECT_EQ(info.currentPhase, testInfo.currentPhase);
    };

    /**
     * @tc.steps2: Add global gesture listener callback for TAP gesture
     * @tc.expected: Callback should be successfully added
     */
    int32_t resourceId = 1001;
    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::TAP,
        GestureActionPhase::WILL_START,
        resourceId,
        std::move(callback));

    /**
     * @tc.steps3: Trigger global gesture listener
     * @tc.expected: Callback should be triggered
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::TAP,
        GestureActionPhase::WILL_START,
        testInfo);
    EXPECT_TRUE(callbackTriggered);

    /**
     * @tc.steps4: Clean up - remove the listener
     */
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::TAP, resourceId);
}

/**
 * @tc.name: ObserverTestNg027
 * @tc.desc: Test RemoveGlobalGestureListenerCallback removes by resourceId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg027, TestSize.Level1)
{
    /**
     * @tc.steps1: Add callback for PAN gesture
     */
    static bool callbackTriggered = false;
    callbackTriggered = false;

    GlobalGestureListenerCallback callback1 = [](const GestureTriggerInfo&) {
        callbackTriggered = true;
    };

    int32_t resourceId1 = 2001;

    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::PAN, GestureActionPhase::WILL_END, resourceId1, std::move(callback1));

    /**
     * @tc.steps2: Trigger listener before removal
     * @tc.expected: Callback should be triggered
     */
    GestureTriggerInfo testInfo;
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PAN, GestureActionPhase::WILL_END, testInfo);
    EXPECT_TRUE(callbackTriggered);

    /**
     * @tc.steps3: Remove callback by resourceId
     */
    callbackTriggered = false;

    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::PAN, resourceId1);

    /**
     * @tc.steps4: Trigger listener after removal
     * @tc.expected: No callback should be triggered
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PAN, GestureActionPhase::WILL_END, testInfo);
    EXPECT_FALSE(callbackTriggered);
}

/**
 * @tc.name: ObserverTestNg027b
 * @tc.desc: Test AddGlobalGestureListenerCallback overwrites old callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg027b, TestSize.Level1)
{
    /**
     * @tc.steps1: Add first callback for PINCH gesture
     */
    static int callbackCount = 0;
    callbackCount = 0;

    GlobalGestureListenerCallback callback1 = [](const GestureTriggerInfo&) {
        callbackCount = 1;
    };
    GlobalGestureListenerCallback callback2 = [](const GestureTriggerInfo&) {
        callbackCount = 2;
    };

    int32_t resourceId1 = 2010;
    int32_t resourceId2 = 2011;

    // Add first callback
    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, resourceId1, std::move(callback1));

    /**
     * @tc.steps2: Trigger first callback
     * @tc.expected: callbackCount should be 1
     */
    GestureTriggerInfo testInfo;
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, testInfo);
    EXPECT_EQ(callbackCount, 1);

    /**
     * @tc.steps3: Add second callback (should overwrite first)
     */
    callbackCount = 0;
    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, resourceId2, std::move(callback2));

    /**
     * @tc.steps4: Trigger second callback
     * @tc.expected: callbackCount should be 2 (not 1)
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, testInfo);
    EXPECT_EQ(callbackCount, 2);

    /**
     * @tc.steps5: Clean up
     */
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START);
}

/**
 * @tc.name: ObserverTestNg028
 * @tc.desc: Test RemoveGlobalGestureListenerCallback with isRemoveAll flag
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg028, TestSize.Level1)
{
    /**
     * @tc.steps1: Add callbacks for multiple phases of the same gesture type
     */
    static int willStartCount = 0;
    static int willEndCount = 0;

    GlobalGestureListenerCallback callback1 = [](const GestureTriggerInfo&) {
        willStartCount++;
    };
    GlobalGestureListenerCallback callback2 = [](const GestureTriggerInfo&) {
        willEndCount++;
    };

    int32_t resourceId1 = 3001;
    int32_t resourceId2 = 3002;

    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_START, resourceId1, std::move(callback1));
    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_END, resourceId2, std::move(callback2));

    /**
     * @tc.steps2: Trigger listeners before removal
     */
    GestureTriggerInfo testInfo;
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_START, testInfo);
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_END, testInfo);
    EXPECT_EQ(willStartCount, 1);
    EXPECT_EQ(willEndCount, 1);

    /**
     * @tc.steps3: Remove all callbacks for SWIPE gesture type
     */
    willStartCount = 0;
    willEndCount = 0;

    // Remove callbacks for both phases
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_START);
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_END);

    /**
     * @tc.steps4: Trigger listeners after removal
     * @tc.expected: No callbacks should be triggered
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_START, testInfo);
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::SWIPE, GestureActionPhase::WILL_END, testInfo);
    EXPECT_EQ(willStartCount, 0);
    EXPECT_EQ(willEndCount, 0);
}

/**
 * @tc.name: ObserverTestNg029
 * @tc.desc: Test callback overwriting - last callback wins
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg029, TestSize.Level1)
{
    /**
     * @tc.steps1: Add multiple callbacks for same gesture type and phase
     * Since each (gestureType, phase) combination only stores one callback,
     * the last added callback overwrites previous ones
     */
    static int callbackValue = 0;
    callbackValue = 0;

    int32_t resourceIds[] = {4001, 4002, 4003};

    for (int i = 0; i < 3; i++) {
        // Each callback sets callbackValue to (i + 1)
        int value = i + 1;
        GlobalGestureListenerCallback callback = [value](const GestureTriggerInfo&) {
            callbackValue = value;
        };
        UIObserverHandler::AddGlobalGestureListenerCallback(
            GestureListenerType::PINCH, GestureActionPhase::WILL_START, resourceIds[i], std::move(callback));
    }

    /**
     * @tc.steps2: Trigger listener
     * @tc.expected: Only the last callback (value=3) should have been stored
     */
    GestureTriggerInfo testInfo;
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, testInfo);
    EXPECT_EQ(callbackValue, 3);  // Last callback wins

    /**
     * @tc.steps3: Remove callback by phase
     */
    callbackValue = 0;
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START);

    /**
     * @tc.steps4: Trigger listener after removal
     * @tc.expected: No callback should be triggered
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::PINCH, GestureActionPhase::WILL_START, testInfo);
    EXPECT_EQ(callbackValue, 0);
}

/**
 * @tc.name: ObserverTestNg030
 * @tc.desc: Test GestureTriggerInfo structure
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg030, TestSize.Level1)
{
    /**
     * @tc.steps1: Create and populate GestureTriggerInfo
     */
    GestureTriggerInfo triggerInfo;

    GestureEvent gestureEvent;
    gestureEvent.SetOffsetX(100.0);
    gestureEvent.SetOffsetY(200.0);
    triggerInfo.event = gestureEvent;

    void* mockRecognizer = reinterpret_cast<void*>(0x12345678);
    triggerInfo.current = mockRecognizer;

    triggerInfo.currentPhase = static_cast<int32_t>(GestureActionPhase::WILL_END);

    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 5001, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    triggerInfo.node = frameNode;

    /**
     * @tc.steps2: Verify all fields are correctly set
     */
    EXPECT_EQ(triggerInfo.event.GetOffsetX(), 100.0);
    EXPECT_EQ(triggerInfo.event.GetOffsetY(), 200.0);
    EXPECT_EQ(triggerInfo.current, mockRecognizer);
    EXPECT_EQ(triggerInfo.currentPhase, static_cast<int32_t>(GestureActionPhase::WILL_END));
    EXPECT_EQ(triggerInfo.node, frameNode);

    /**
     * @tc.steps3: Test callback receives correct GestureTriggerInfo
     */
    static bool infoCorrect = false;
    infoCorrect = false;

    GlobalGestureListenerCallback callback = [&triggerInfo](const GestureTriggerInfo& info) {
        infoCorrect = (info.event.GetOffsetX() == triggerInfo.event.GetOffsetX() &&
                       info.event.GetOffsetY() == triggerInfo.event.GetOffsetY() &&
                       info.current == triggerInfo.current &&
                       info.currentPhase == triggerInfo.currentPhase &&
                       info.node == triggerInfo.node);
    };

    int32_t resourceId = 6001;
    UIObserverHandler::AddGlobalGestureListenerCallback(
        GestureListenerType::ROTATION, GestureActionPhase::WILL_END, resourceId, std::move(callback));

    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::ROTATION, GestureActionPhase::WILL_END, triggerInfo);
    EXPECT_TRUE(infoCorrect);

    /**
     * @tc.steps4: Clean up
     */
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::ROTATION, resourceId);
}

/**
 * @tc.name: ObserverTestNg031
 * @tc.desc: Test thread safety of global gesture listener operations
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, ObserverTestNg031, TestSize.Level1)
{
    /**
     * @tc.steps1: Add multiple callbacks rapidly
     */
    for (int i = 0; i < 10; i++) {
        GlobalGestureListenerCallback callback = [](const GestureTriggerInfo&) {};
        int32_t resourceId = 7000 + i;
        UIObserverHandler::AddGlobalGestureListenerCallback(
            GestureListenerType::TAP, GestureActionPhase::WILL_START, resourceId, std::move(callback));
    }

    /**
     * @tc.steps2: Trigger listener
     * @tc.expected: Should execute last callback without crashing
     */
    GestureTriggerInfo testInfo;
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::TAP, GestureActionPhase::WILL_START, testInfo);

    /**
     * @tc.steps3: Remove all callbacks
     */
    UIObserverHandler::RemoveGlobalGestureListenerCallback(
        GestureListenerType::TAP, GestureActionPhase::WILL_START);

    /**
     * @tc.steps4: Verify cleanup
     */
    UIObserverHandler::TriggerGlobalGestureListener(
        GestureListenerType::TAP, GestureActionPhase::WILL_START, testInfo);
}

/**
 * @tc.name: GetNavigationOuterState001
 * @tc.desc: Test the GetNavigationOuterState function
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, GetNavigationOuterState001, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigation, nullptr);
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, 33, []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode, nullptr);
    navDestination->AddChild(stackNode);
    navigation->AddChild(navDestination);
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);
    auto pattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));
    navigation->SetUseHomeDestination(true);
    navigation->customHomeDestination_ = navDestination;

    auto info = UIObserverHandler::GetInstance().GetNavigationOuterState(stackNode);
    ASSERT_NE(info, nullptr);
    ASSERT_EQ(info->name, "test_name");
    ASSERT_EQ(info->navigationId, "");
    ASSERT_EQ(info->state, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: GetNavigationInnerState001
 * @tc.desc: Test the GetNavigationInnerState function
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, GetNavigationInnerState001, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->GetPattern<NavigationPattern>()->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigation, nullptr);
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(navDestination, nullptr);
    auto stackNode = FrameNode::GetOrCreateFrameNode(
        V2::STACK_ETS_TAG, 33, []() { return AceType::MakeRefPtr<StackPattern>(); });
    ASSERT_NE(stackNode, nullptr);
    stackNode->AddChild(navDestination);
    navigation->AddChild(navDestination);
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    ASSERT_NE(pathInfo, nullptr);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    ASSERT_NE(context, nullptr);
    context->SetNavPathInfo(pathInfo);
    auto pattern = navDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetNavDestinationContext(context);
    pattern->name_ = "test_name";
    pattern->isOnShow_ = true;
    pattern->navigationNode_ = AceType::WeakClaim(Referenced::RawPtr(navigation));
    navigation->SetUseHomeDestination(true);
    navigation->customHomeDestination_ = navDestination;

    auto info = UIObserverHandler::GetInstance().GetNavigationInnerState(stackNode);
    ASSERT_NE(info, nullptr);
    ASSERT_EQ(info->name, "test_name");
    ASSERT_EQ(info->navigationId, "");
    ASSERT_EQ(info->state, NavDestinationState::ON_SHOWN);
}

/**
 * @tc.name: NotifyPanGestureStateChange001
 * @tc.desc: Test NotifyPanGestureStateChange with BEFORE/START triggers TriggerBeforePanStart
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyPanGestureStateChange001, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1001, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::BEFORE, CurrentCallbackState::START };

    bool beforePanStartTriggered = false;
    beforePanStartTriggered = false;
    PanListenerCallback callback = [&beforePanStartTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        beforePanStartTriggered = true;
    };
    UIObserverHandler::AddBeforePanStartListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
        gestureEventInfo, current, frameNode, panGestureInfo);
    EXPECT_TRUE(beforePanStartTriggered);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: NotifyPanGestureStateChange002
 * @tc.desc: Test NotifyPanGestureStateChange with AFTER/START triggers TriggerAfterPanStart
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyPanGestureStateChange002, TestSize.Level1)
{
    UIObserverHandler::afterPanStartCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1002, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::AFTER, CurrentCallbackState::START };

    bool afterPanStartTriggered = false;
    afterPanStartTriggered = false;
    PanListenerCallback callback = [&afterPanStartTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        afterPanStartTriggered = true;
    };
    UIObserverHandler::AddAfterPanStartListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
        gestureEventInfo, current, frameNode, panGestureInfo);
    EXPECT_TRUE(afterPanStartTriggered);
    UIObserverHandler::afterPanStartCallbackMap_.clear();
}

/**
 * @tc.name: NotifyPanGestureStateChange003
 * @tc.desc: Test NotifyPanGestureStateChange with BEFORE/END triggers TriggerBeforePanEnd
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyPanGestureStateChange003, TestSize.Level1)
{
    UIObserverHandler::beforePanEndCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1003, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::BEFORE, CurrentCallbackState::END };

    bool beforePanEndTriggered = false;
    beforePanEndTriggered = false;
    PanListenerCallback callback = [&beforePanEndTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        beforePanEndTriggered = true;
    };
    UIObserverHandler::AddBeforePanEndListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
        gestureEventInfo, current, frameNode, panGestureInfo);
    EXPECT_TRUE(beforePanEndTriggered);
    UIObserverHandler::beforePanEndCallbackMap_.clear();
}

/**
 * @tc.name: NotifyPanGestureStateChange004
 * @tc.desc: Test NotifyPanGestureStateChange with AFTER/END triggers TriggerAfterPanEnd
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyPanGestureStateChange004, TestSize.Level1)
{
    UIObserverHandler::afterPanEndCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1004, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::AFTER, CurrentCallbackState::END };

    bool afterPanEndTriggered = false;
    afterPanEndTriggered = false;
    PanListenerCallback callback = [&afterPanEndTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        afterPanEndTriggered = true;
    };
    UIObserverHandler::AddAfterPanEndListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
        gestureEventInfo, current, frameNode, panGestureInfo);
    EXPECT_TRUE(afterPanEndTriggered);
    UIObserverHandler::afterPanEndCallbackMap_.clear();
}

/**
 * @tc.name: NotifyPanGestureStateChange005
 * @tc.desc: Test NotifyPanGestureStateChange with panGestureHandleFunc_ set
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyPanGestureStateChange005, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 1005, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    PanGestureInfo panGestureInfo = { PanGestureState::BEFORE, CurrentCallbackState::START };

    g_panGestureHandleFuncCalled = false;
    UIObserverHandler::GetInstance().panGestureHandleFunc_ =
        [](AbilityContextInfo&, const GestureEvent&, const RefPtr<PanRecognizer>&,
            const RefPtr<FrameNode>&, const PanGestureInfo&) { g_panGestureHandleFuncCalled = true; };

    UIObserverHandler::GetInstance().NotifyPanGestureStateChange(
        gestureEventInfo, current, frameNode, panGestureInfo);
    EXPECT_TRUE(g_panGestureHandleFuncCalled);
    UIObserverHandler::GetInstance().panGestureHandleFunc_ = nullptr;
    g_panGestureHandleFuncCalled = false;
}

/**
 * @tc.name: AddBeforePanStartListenerCallback001
 * @tc.desc: Test AddBeforePanStartListenerCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddBeforePanStartListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddBeforePanStartListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::beforePanStartCallbackMap_.empty());
}

/**
 * @tc.name: AddBeforePanStartListenerCallback002
 * @tc.desc: Test AddBeforePanStartListenerCallback creates new entry for new instanceId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddBeforePanStartListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 1, std::move(callback));
    EXPECT_EQ(UIObserverHandler::beforePanStartCallbackMap_.size(), 1u);
    EXPECT_EQ(UIObserverHandler::beforePanStartCallbackMap_[100].size(), 1u);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: AddBeforePanStartListenerCallback003
 * @tc.desc: Test AddBeforePanStartListenerCallback updates existing instanceId entry
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddBeforePanStartListenerCallback003, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback callback1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    PanListenerCallback callback2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 1, std::move(callback1));
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::beforePanStartCallbackMap_[100].size(), 2u);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: AddBeforePanEndListenerCallback001
 * @tc.desc: Test AddBeforePanEndListenerCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddBeforePanEndListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::beforePanEndCallbackMap_.clear();
    PanListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddBeforePanEndListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::beforePanEndCallbackMap_.empty());
}

/**
 * @tc.name: AddBeforePanEndListenerCallback002
 * @tc.desc: Test AddBeforePanEndListenerCallback creates new entry and updates existing
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddBeforePanEndListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::beforePanEndCallbackMap_.clear();
    PanListenerCallback callback1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanEndListenerCallback(200, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::beforePanEndCallbackMap_.size(), 1u);

    PanListenerCallback callback2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanEndListenerCallback(200, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::beforePanEndCallbackMap_[200].size(), 2u);
    UIObserverHandler::beforePanEndCallbackMap_.clear();
}

/**
 * @tc.name: AddAfterPanStartListenerCallback001
 * @tc.desc: Test AddAfterPanStartListenerCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddAfterPanStartListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::afterPanStartCallbackMap_.clear();
    PanListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddAfterPanStartListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::afterPanStartCallbackMap_.empty());
}

/**
 * @tc.name: AddAfterPanStartListenerCallback002
 * @tc.desc: Test AddAfterPanStartListenerCallback creates and updates entries
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddAfterPanStartListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::afterPanStartCallbackMap_.clear();
    PanListenerCallback callback1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanStartListenerCallback(300, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::afterPanStartCallbackMap_.size(), 1u);

    PanListenerCallback callback2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanStartListenerCallback(300, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::afterPanStartCallbackMap_[300].size(), 2u);
    UIObserverHandler::afterPanStartCallbackMap_.clear();
}

/**
 * @tc.name: AddAfterPanEndListenerCallback001
 * @tc.desc: Test AddAfterPanEndListenerCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddAfterPanEndListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::afterPanEndCallbackMap_.clear();
    PanListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddAfterPanEndListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::afterPanEndCallbackMap_.empty());
}

/**
 * @tc.name: AddAfterPanEndListenerCallback002
 * @tc.desc: Test AddAfterPanEndListenerCallback creates and updates entries
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddAfterPanEndListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::afterPanEndCallbackMap_.clear();
    PanListenerCallback callback1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanEndListenerCallback(400, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::afterPanEndCallbackMap_.size(), 1u);

    PanListenerCallback callback2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanEndListenerCallback(400, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::afterPanEndCallbackMap_[400].size(), 2u);
    UIObserverHandler::afterPanEndCallbackMap_.clear();
}

/**
 * @tc.name: RemoveBeforePanStartListenerCallback001
 * @tc.desc: Test RemoveBeforePanStartListenerCallback with empty map
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveBeforePanStartListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    UIObserverHandler::RemoveBeforePanStartListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::beforePanStartCallbackMap_.empty());
}

/**
 * @tc.name: RemoveBeforePanStartListenerCallback002
 * @tc.desc: Test RemoveBeforePanStartListenerCallback with isRemoveAll=true
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveBeforePanStartListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 1, std::move(callback));
    EXPECT_FALSE(UIObserverHandler::beforePanStartCallbackMap_.empty());

    UIObserverHandler::RemoveBeforePanStartListenerCallback(100, 1, true);
    EXPECT_TRUE(UIObserverHandler::beforePanStartCallbackMap_.empty());
}

/**
 * @tc.name: RemoveBeforePanStartListenerCallback003
 * @tc.desc: Test RemoveBeforePanStartListenerCallback with isRemoveAll=false, found instanceId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveBeforePanStartListenerCallback003, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback callback1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    PanListenerCallback callback2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 1, std::move(callback1));
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 2, std::move(callback2));

    UIObserverHandler::RemoveBeforePanStartListenerCallback(100, 1, false);
    EXPECT_EQ(UIObserverHandler::beforePanStartCallbackMap_[100].size(), 1u);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: RemoveBeforePanStartListenerCallback004
 * @tc.desc: Test RemoveBeforePanStartListenerCallback with isRemoveAll=false, not found instanceId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveBeforePanStartListenerCallback004, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanStartListenerCallback(100, 1, std::move(callback));

    UIObserverHandler::RemoveBeforePanStartListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::beforePanStartCallbackMap_.size(), 1u);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: RemoveBeforePanEndListenerCallback001
 * @tc.desc: Test RemoveBeforePanEndListenerCallback with empty map, isRemoveAll, and partial remove
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveBeforePanEndListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::beforePanEndCallbackMap_.clear();
    UIObserverHandler::RemoveBeforePanEndListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::beforePanEndCallbackMap_.empty());

    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanEndListenerCallback(200, 1, std::move(callback));
    UIObserverHandler::RemoveBeforePanEndListenerCallback(200, 1, true);
    EXPECT_TRUE(UIObserverHandler::beforePanEndCallbackMap_.empty());

    PanListenerCallback cb1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    PanListenerCallback cb2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddBeforePanEndListenerCallback(200, 1, std::move(cb1));
    UIObserverHandler::AddBeforePanEndListenerCallback(200, 2, std::move(cb2));
    UIObserverHandler::RemoveBeforePanEndListenerCallback(200, 1, false);
    EXPECT_EQ(UIObserverHandler::beforePanEndCallbackMap_[200].size(), 1u);
    UIObserverHandler::beforePanEndCallbackMap_.clear();
}

/**
 * @tc.name: RemoveAfterPanStartListenerCallback001
 * @tc.desc: Test RemoveAfterPanStartListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveAfterPanStartListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::afterPanStartCallbackMap_.clear();
    UIObserverHandler::RemoveAfterPanStartListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::afterPanStartCallbackMap_.empty());

    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanStartListenerCallback(300, 1, std::move(callback));
    UIObserverHandler::RemoveAfterPanStartListenerCallback(300, 1, true);
    EXPECT_TRUE(UIObserverHandler::afterPanStartCallbackMap_.empty());

    PanListenerCallback cb1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    PanListenerCallback cb2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanStartListenerCallback(300, 1, std::move(cb1));
    UIObserverHandler::AddAfterPanStartListenerCallback(300, 2, std::move(cb2));
    UIObserverHandler::RemoveAfterPanStartListenerCallback(300, 1, false);
    EXPECT_EQ(UIObserverHandler::afterPanStartCallbackMap_[300].size(), 1u);

    UIObserverHandler::RemoveAfterPanStartListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::afterPanStartCallbackMap_.size(), 1u);
    UIObserverHandler::afterPanStartCallbackMap_.clear();
}

/**
 * @tc.name: RemoveAfterPanEndListenerCallback001
 * @tc.desc: Test RemoveAfterPanEndListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveAfterPanEndListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::afterPanEndCallbackMap_.clear();
    UIObserverHandler::RemoveAfterPanEndListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::afterPanEndCallbackMap_.empty());

    PanListenerCallback callback = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanEndListenerCallback(400, 1, std::move(callback));
    UIObserverHandler::RemoveAfterPanEndListenerCallback(400, 1, true);
    EXPECT_TRUE(UIObserverHandler::afterPanEndCallbackMap_.empty());

    PanListenerCallback cb1 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    PanListenerCallback cb2 = [](const GestureEvent&, const RefPtr<PanRecognizer>&,
        const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddAfterPanEndListenerCallback(400, 1, std::move(cb1));
    UIObserverHandler::AddAfterPanEndListenerCallback(400, 2, std::move(cb2));
    UIObserverHandler::RemoveAfterPanEndListenerCallback(400, 1, false);
    EXPECT_EQ(UIObserverHandler::afterPanEndCallbackMap_[400].size(), 1u);

    UIObserverHandler::RemoveAfterPanEndListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::afterPanEndCallbackMap_.size(), 1u);
    UIObserverHandler::afterPanEndCallbackMap_.clear();
}

/**
 * @tc.name: TriggerBeforePanStart001
 * @tc.desc: Test TriggerBeforePanStart with empty map
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerBeforePanStart001, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2001, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    UIObserverHandler::GetInstance().TriggerBeforePanStart(gestureEventInfo, current, frameNode);
}

/**
 * @tc.name: TriggerBeforePanStart002
 * @tc.desc: Test TriggerBeforePanStart with matching currentId invokes callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerBeforePanStart002, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2002, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    int callbackCount = 0;
    callbackCount = 0;
    PanListenerCallback callback = [&callbackCount](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        callbackCount++;
    };
    UIObserverHandler::AddBeforePanStartListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().TriggerBeforePanStart(gestureEventInfo, current, frameNode);
    EXPECT_EQ(callbackCount, 1);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: TriggerBeforePanStart003
 * @tc.desc: Test TriggerBeforePanStart with non-matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerBeforePanStart003, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2003, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    bool callbackTriggered = false;
    callbackTriggered = false;
    PanListenerCallback callback = [&callbackTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddBeforePanStartListenerCallback(999, 1, std::move(callback));

    UIObserverHandler::GetInstance().TriggerBeforePanStart(gestureEventInfo, current, frameNode);
    EXPECT_FALSE(callbackTriggered);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: TriggerBeforePanEnd001
 * @tc.desc: Test TriggerBeforePanEnd with empty, matching, and non-matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerBeforePanEnd001, TestSize.Level1)
{
    UIObserverHandler::beforePanEndCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2010, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerBeforePanEnd(gestureEventInfo, current, frameNode);

    int callbackCount = 0;
    callbackCount = 0;
    PanListenerCallback callback = [&callbackCount](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        callbackCount++;
    };
    UIObserverHandler::AddBeforePanEndListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerBeforePanEnd(gestureEventInfo, current, frameNode);
    EXPECT_EQ(callbackCount, 1);
    UIObserverHandler::beforePanEndCallbackMap_.clear();
}

/**
 * @tc.name: TriggerAfterPanStart001
 * @tc.desc: Test TriggerAfterPanStart with empty and matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerAfterPanStart001, TestSize.Level1)
{
    UIObserverHandler::afterPanStartCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2020, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerAfterPanStart(gestureEventInfo, current, frameNode);

    bool callbackTriggered = false;
    callbackTriggered = false;
    PanListenerCallback callback = [&callbackTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddAfterPanStartListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerAfterPanStart(gestureEventInfo, current, frameNode);
    EXPECT_TRUE(callbackTriggered);
    UIObserverHandler::afterPanStartCallbackMap_.clear();
}

/**
 * @tc.name: TriggerAfterPanEnd001
 * @tc.desc: Test TriggerAfterPanEnd with empty and matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerAfterPanEnd001, TestSize.Level1)
{
    UIObserverHandler::afterPanEndCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2030, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerAfterPanEnd(gestureEventInfo, current, frameNode);

    bool callbackTriggered = false;
    callbackTriggered = false;
    PanListenerCallback callback = [&callbackTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddAfterPanEndListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerAfterPanEnd(gestureEventInfo, current, frameNode);
    EXPECT_TRUE(callbackTriggered);
    UIObserverHandler::afterPanEndCallbackMap_.clear();
}

/**
 * @tc.name: TriggerPanCallbackWithNull001
 * @tc.desc: Test Trigger functions skip null callbacks in map
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerPanCallbackWithNull001, TestSize.Level1)
{
    UIObserverHandler::beforePanStartCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    RefPtr<PanRecognizer> current = nullptr;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 2040, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    bool validCallbackTriggered = false;
    validCallbackTriggered = false;

    UIObserverHandler::beforePanStartCallbackMap_[0][1] = nullptr;
    PanListenerCallback validCallback = [&validCallbackTriggered](
        const GestureEvent&, const RefPtr<PanRecognizer>&, const RefPtr<FrameNode>&) {
        validCallbackTriggered = true;
    };
    UIObserverHandler::AddBeforePanStartListenerCallback(0, 2, std::move(validCallback));

    UIObserverHandler::GetInstance().TriggerBeforePanStart(gestureEventInfo, current, frameNode);
    EXPECT_TRUE(validCallbackTriggered);
    UIObserverHandler::beforePanStartCallbackMap_.clear();
}

/**
 * @tc.name: AddWillClickListenerCallback001
 * @tc.desc: Test AddWillClickListenerCallback with null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddWillClickListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    GestureListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddWillClickListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::willClickCallbackMap_.empty());
}

/**
 * @tc.name: AddWillClickListenerCallback002
 * @tc.desc: Test AddWillClickListenerCallback creates and updates entries
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddWillClickListenerCallback002, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    GestureListenerCallback callback1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillClickListenerCallback(500, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::willClickCallbackMap_.size(), 1u);

    GestureListenerCallback callback2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillClickListenerCallback(500, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::willClickCallbackMap_[500].size(), 2u);
    UIObserverHandler::willClickCallbackMap_.clear();
}

/**
 * @tc.name: AddDidClickListenerCallback001
 * @tc.desc: Test AddDidClickListenerCallback with null callback and normal callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddDidClickListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::didClickCallbackMap_.clear();
    GestureListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddDidClickListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::didClickCallbackMap_.empty());

    GestureListenerCallback callback1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidClickListenerCallback(600, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::didClickCallbackMap_.size(), 1u);

    GestureListenerCallback callback2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidClickListenerCallback(600, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::didClickCallbackMap_[600].size(), 2u);
    UIObserverHandler::didClickCallbackMap_.clear();
}

/**
 * @tc.name: AddWillTapListenerCallback001
 * @tc.desc: Test AddWillTapListenerCallback with null callback and normal callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddWillTapListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::willTapCallbackMap_.clear();
    GestureListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddWillTapListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::willTapCallbackMap_.empty());

    GestureListenerCallback callback1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillTapListenerCallback(700, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::willTapCallbackMap_.size(), 1u);

    GestureListenerCallback callback2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillTapListenerCallback(700, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::willTapCallbackMap_[700].size(), 2u);
    UIObserverHandler::willTapCallbackMap_.clear();
}

/**
 * @tc.name: AddDidTapListenerCallback001
 * @tc.desc: Test AddDidTapListenerCallback with null callback and normal callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, AddDidTapListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::didTapCallbackMap_.clear();
    GestureListenerCallback nullCallback = nullptr;
    UIObserverHandler::AddDidTapListenerCallback(0, 1, std::move(nullCallback));
    EXPECT_TRUE(UIObserverHandler::didTapCallbackMap_.empty());

    GestureListenerCallback callback1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidTapListenerCallback(800, 1, std::move(callback1));
    EXPECT_EQ(UIObserverHandler::didTapCallbackMap_.size(), 1u);

    GestureListenerCallback callback2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidTapListenerCallback(800, 2, std::move(callback2));
    EXPECT_EQ(UIObserverHandler::didTapCallbackMap_[800].size(), 2u);
    UIObserverHandler::didTapCallbackMap_.clear();
}

/**
 * @tc.name: RemoveWillClickListenerCallback001
 * @tc.desc: Test RemoveWillClickListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveWillClickListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    UIObserverHandler::RemoveWillClickListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::willClickCallbackMap_.empty());

    GestureListenerCallback callback = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillClickListenerCallback(500, 1, std::move(callback));
    UIObserverHandler::RemoveWillClickListenerCallback(500, 1, true);
    EXPECT_TRUE(UIObserverHandler::willClickCallbackMap_.empty());

    GestureListenerCallback cb1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    GestureListenerCallback cb2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillClickListenerCallback(500, 1, std::move(cb1));
    UIObserverHandler::AddWillClickListenerCallback(500, 2, std::move(cb2));
    UIObserverHandler::RemoveWillClickListenerCallback(500, 1, false);
    EXPECT_EQ(UIObserverHandler::willClickCallbackMap_[500].size(), 1u);

    UIObserverHandler::RemoveWillClickListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::willClickCallbackMap_.size(), 1u);
    UIObserverHandler::willClickCallbackMap_.clear();
}

/**
 * @tc.name: RemoveDidClickListenerCallback001
 * @tc.desc: Test RemoveDidClickListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveDidClickListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::didClickCallbackMap_.clear();
    UIObserverHandler::RemoveDidClickListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::didClickCallbackMap_.empty());

    GestureListenerCallback callback = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidClickListenerCallback(600, 1, std::move(callback));
    UIObserverHandler::RemoveDidClickListenerCallback(600, 1, true);
    EXPECT_TRUE(UIObserverHandler::didClickCallbackMap_.empty());

    GestureListenerCallback cb1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    GestureListenerCallback cb2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidClickListenerCallback(600, 1, std::move(cb1));
    UIObserverHandler::AddDidClickListenerCallback(600, 2, std::move(cb2));
    UIObserverHandler::RemoveDidClickListenerCallback(600, 1, false);
    EXPECT_EQ(UIObserverHandler::didClickCallbackMap_[600].size(), 1u);

    UIObserverHandler::RemoveDidClickListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::didClickCallbackMap_.size(), 1u);
    UIObserverHandler::didClickCallbackMap_.clear();
}

/**
 * @tc.name: RemoveWillTapListenerCallback001
 * @tc.desc: Test RemoveWillTapListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveWillTapListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::willTapCallbackMap_.clear();
    UIObserverHandler::RemoveWillTapListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::willTapCallbackMap_.empty());

    GestureListenerCallback callback = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillTapListenerCallback(700, 1, std::move(callback));
    UIObserverHandler::RemoveWillTapListenerCallback(700, 1, true);
    EXPECT_TRUE(UIObserverHandler::willTapCallbackMap_.empty());

    GestureListenerCallback cb1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    GestureListenerCallback cb2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddWillTapListenerCallback(700, 1, std::move(cb1));
    UIObserverHandler::AddWillTapListenerCallback(700, 2, std::move(cb2));
    UIObserverHandler::RemoveWillTapListenerCallback(700, 1, false);
    EXPECT_EQ(UIObserverHandler::willTapCallbackMap_[700].size(), 1u);

    UIObserverHandler::RemoveWillTapListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::willTapCallbackMap_.size(), 1u);
    UIObserverHandler::willTapCallbackMap_.clear();
}

/**
 * @tc.name: RemoveDidTapListenerCallback001
 * @tc.desc: Test RemoveDidTapListenerCallback with all branches
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, RemoveDidTapListenerCallback001, TestSize.Level1)
{
    UIObserverHandler::didTapCallbackMap_.clear();
    UIObserverHandler::RemoveDidTapListenerCallback(0, 1, false);
    EXPECT_TRUE(UIObserverHandler::didTapCallbackMap_.empty());

    GestureListenerCallback callback = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidTapListenerCallback(800, 1, std::move(callback));
    UIObserverHandler::RemoveDidTapListenerCallback(800, 1, true);
    EXPECT_TRUE(UIObserverHandler::didTapCallbackMap_.empty());

    GestureListenerCallback cb1 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    GestureListenerCallback cb2 = [](const GestureEvent&, const RefPtr<FrameNode>&) {};
    UIObserverHandler::AddDidTapListenerCallback(800, 1, std::move(cb1));
    UIObserverHandler::AddDidTapListenerCallback(800, 2, std::move(cb2));
    UIObserverHandler::RemoveDidTapListenerCallback(800, 1, false);
    EXPECT_EQ(UIObserverHandler::didTapCallbackMap_[800].size(), 1u);

    UIObserverHandler::RemoveDidTapListenerCallback(999, 1, false);
    EXPECT_EQ(UIObserverHandler::didTapCallbackMap_.size(), 1u);
    UIObserverHandler::didTapCallbackMap_.clear();
}

/**
 * @tc.name: TriggerWillClick001
 * @tc.desc: Test TriggerWillClick with empty map
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerWillClick001, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3001, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    UIObserverHandler::GetInstance().TriggerWillClick(gestureEventInfo, frameNode);
}

/**
 * @tc.name: TriggerWillClick002
 * @tc.desc: Test TriggerWillClick with matching currentId invokes callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerWillClick002, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3002, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    bool callbackTriggered = false;
    callbackTriggered = false;
    GestureListenerCallback callback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddWillClickListenerCallback(0, 1, std::move(callback));

    UIObserverHandler::GetInstance().TriggerWillClick(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);
    UIObserverHandler::willClickCallbackMap_.clear();
}

/**
 * @tc.name: TriggerWillClick003
 * @tc.desc: Test TriggerWillClick with non-matching currentId and null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerWillClick003, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3003, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    bool callbackTriggered = false;
    callbackTriggered = false;
    GestureListenerCallback callback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddWillClickListenerCallback(999, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerWillClick(gestureEventInfo, frameNode);
    EXPECT_FALSE(callbackTriggered);

    UIObserverHandler::willClickCallbackMap_[0][1] = nullptr;
    GestureListenerCallback validCallback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddWillClickListenerCallback(0, 2, std::move(validCallback));
    callbackTriggered = false;
    UIObserverHandler::GetInstance().TriggerWillClick(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);
    UIObserverHandler::willClickCallbackMap_.clear();
}

/**
 * @tc.name: TriggerDidClick001
 * @tc.desc: Test TriggerDidClick with empty, matching, and non-matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerDidClick001, TestSize.Level1)
{
    UIObserverHandler::didClickCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3010, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerDidClick(gestureEventInfo, frameNode);

    bool callbackTriggered = false;
    callbackTriggered = false;
    GestureListenerCallback callback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddDidClickListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerDidClick(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);

    UIObserverHandler::didClickCallbackMap_.clear();
    GestureListenerCallback cb2 = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddDidClickListenerCallback(999, 1, std::move(cb2));
    callbackTriggered = false;
    UIObserverHandler::GetInstance().TriggerDidClick(gestureEventInfo, frameNode);
    EXPECT_FALSE(callbackTriggered);
    UIObserverHandler::didClickCallbackMap_.clear();
}

/**
 * @tc.name: TriggerWillTap001
 * @tc.desc: Test TriggerWillTap with empty, matching, and null callback
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerWillTap001, TestSize.Level1)
{
    UIObserverHandler::willTapCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3020, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerWillTap(gestureEventInfo, frameNode);

    bool callbackTriggered = false;
    callbackTriggered = false;
    GestureListenerCallback callback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddWillTapListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerWillTap(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);

    UIObserverHandler::willTapCallbackMap_[0][1] = nullptr;
    GestureListenerCallback validCallback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddWillTapListenerCallback(0, 2, std::move(validCallback));
    callbackTriggered = false;
    UIObserverHandler::GetInstance().TriggerWillTap(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);
    UIObserverHandler::willTapCallbackMap_.clear();
}

/**
 * @tc.name: TriggerDidTap001
 * @tc.desc: Test TriggerDidTap with empty, matching, and non-matching currentId
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, TriggerDidTap001, TestSize.Level1)
{
    UIObserverHandler::didTapCallbackMap_.clear();
    GestureEvent gestureEventInfo;
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 3030, []() { return AceType::MakeRefPtr<ScrollPattern>(); });

    UIObserverHandler::GetInstance().TriggerDidTap(gestureEventInfo, frameNode);

    bool callbackTriggered = false;
    callbackTriggered = false;
    GestureListenerCallback callback = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddDidTapListenerCallback(0, 1, std::move(callback));
    UIObserverHandler::GetInstance().TriggerDidTap(gestureEventInfo, frameNode);
    EXPECT_TRUE(callbackTriggered);

    UIObserverHandler::didTapCallbackMap_.clear();
    GestureListenerCallback cb2 = [&callbackTriggered](const GestureEvent&, const RefPtr<FrameNode>&) {
        callbackTriggered = true;
    };
    UIObserverHandler::AddDidTapListenerCallback(999, 1, std::move(cb2));
    callbackTriggered = false;
    UIObserverHandler::GetInstance().TriggerDidTap(gestureEventInfo, frameNode);
    EXPECT_FALSE(callbackTriggered);
    UIObserverHandler::didTapCallbackMap_.clear();
}

/**
 * @tc.name: NotifyWillClickWithCallbacks001
 * @tc.desc: Test NotifyWillClick triggers willClick/didClick/willTap/didTap callbacks
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyWillClickWithCallbacks001, TestSize.Level1)
{
    UIObserverHandler::willClickCallbackMap_.clear();
    UIObserverHandler::willTapCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 4001, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);

    int willClickCount = 0;
    int willTapCount = 0;
    willClickCount = 0;
    willTapCount = 0;

    GestureListenerCallback willClickCb = [&willClickCount](const GestureEvent&, const RefPtr<FrameNode>&) {
        willClickCount++;
    };
    GestureListenerCallback willTapCb = [&willTapCount](const GestureEvent&, const RefPtr<FrameNode>&) {
        willTapCount++;
    };
    UIObserverHandler::AddWillClickListenerCallback(0, 1, std::move(willClickCb));
    UIObserverHandler::AddWillTapListenerCallback(0, 1, std::move(willTapCb));

    UIObserverHandler::GetInstance().NotifyWillClick(gestureEventInfo, clickInfo, frameNode);
    EXPECT_EQ(willClickCount, 1);
    EXPECT_EQ(willTapCount, 1);

    UIObserverHandler::willClickCallbackMap_.clear();
    UIObserverHandler::willTapCallbackMap_.clear();
}

/**
 * @tc.name: NotifyWillClickWithAniCallback001
 * @tc.desc: Test NotifyWillClick with willClickHandleFuncForAni set
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyWillClickWithAniCallback001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 4002, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);

    bool aniCallbackTriggered = false;
    aniCallbackTriggered = false;
    UIObserverHandler::GetInstance().willClickHandleFuncForAni_ = [&aniCallbackTriggered]() {
        aniCallbackTriggered = true;
    };

    UIObserverHandler::GetInstance().NotifyWillClick(gestureEventInfo, clickInfo, frameNode);
    EXPECT_TRUE(aniCallbackTriggered);
    UIObserverHandler::GetInstance().willClickHandleFuncForAni_ = nullptr;
}

/**
 * @tc.name: NotifyDidClickWithCallbacks001
 * @tc.desc: Test NotifyDidClick triggers didClick/didTap callbacks and didClickHandleFuncForAni
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyDidClickWithCallbacks001, TestSize.Level1)
{
    UIObserverHandler::didClickCallbackMap_.clear();
    UIObserverHandler::didTapCallbackMap_.clear();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 4003, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);

    int didClickCount = 0;
    int didTapCount = 0;
    bool aniCallbackTriggered = false;
    didClickCount = 0;
    didTapCount = 0;
    aniCallbackTriggered = false;

    GestureListenerCallback didClickCb = [&didClickCount](const GestureEvent&, const RefPtr<FrameNode>&) {
        didClickCount++;
    };
    GestureListenerCallback didTapCb = [&didTapCount](const GestureEvent&, const RefPtr<FrameNode>&) {
        didTapCount++;
    };
    UIObserverHandler::AddDidClickListenerCallback(0, 1, std::move(didClickCb));
    UIObserverHandler::AddDidTapListenerCallback(0, 1, std::move(didTapCb));
    UIObserverHandler::GetInstance().didClickHandleFuncForAni_ = [&aniCallbackTriggered]() {
        aniCallbackTriggered = true;
    };

    UIObserverHandler::GetInstance().NotifyDidClick(gestureEventInfo, clickInfo, frameNode);
    EXPECT_EQ(didClickCount, 1);
    EXPECT_EQ(didTapCount, 1);
    EXPECT_TRUE(aniCallbackTriggered);

    UIObserverHandler::didClickCallbackMap_.clear();
    UIObserverHandler::didTapCallbackMap_.clear();
    UIObserverHandler::GetInstance().didClickHandleFuncForAni_ = nullptr;
}

/**
 * @tc.name: NotifyWillClickWithHandleFunc001
 * @tc.desc: Test NotifyWillClick with willClickHandleFunc_ set
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyWillClickWithHandleFunc001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 4004, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);

    g_willClickHandleFuncCalled = false;
    UIObserverHandler::GetInstance().willClickHandleFunc_ =
        [](AbilityContextInfo&, const GestureEvent&, const ClickInfo&,
            const RefPtr<FrameNode>&) { g_willClickHandleFuncCalled = true; };

    UIObserverHandler::GetInstance().NotifyWillClick(gestureEventInfo, clickInfo, frameNode);
    EXPECT_TRUE(g_willClickHandleFuncCalled);
    UIObserverHandler::GetInstance().willClickHandleFunc_ = nullptr;
    g_willClickHandleFuncCalled = false;
}

/**
 * @tc.name: NotifyDidClickWithHandleFunc001
 * @tc.desc: Test NotifyDidClick with didClickHandleFunc_ set
 * @tc.type: FUNC
 */
HWTEST_F(ObserverTestNg, NotifyDidClickWithHandleFunc001, TestSize.Level1)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::SCROLL_ETS_TAG, 4005, []() { return AceType::MakeRefPtr<ScrollPattern>(); });
    GestureEvent gestureEventInfo;
    ClickInfo clickInfo = ClickInfo(0);

    g_didClickHandleFuncCalled = false;
    UIObserverHandler::GetInstance().didClickHandleFunc_ =
        [](AbilityContextInfo&, const GestureEvent&, const ClickInfo&,
            const RefPtr<FrameNode>&) { g_didClickHandleFuncCalled = true; };

    UIObserverHandler::GetInstance().NotifyDidClick(gestureEventInfo, clickInfo, frameNode);
    EXPECT_TRUE(g_didClickHandleFuncCalled);
    UIObserverHandler::GetInstance().didClickHandleFunc_ = nullptr;
    g_didClickHandleFuncCalled = false;
}
}
