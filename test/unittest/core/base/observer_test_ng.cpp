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
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_property.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
const float DEFAULT_DENSITY = 3.5f;
const float DEFAULT_NODE_OFFSET = 200.5f;
const int32_t DEFAULT_PARENT_NODE_ID = 1;
const int32_t DEFAULT_NODE_ID = 2;
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
}
