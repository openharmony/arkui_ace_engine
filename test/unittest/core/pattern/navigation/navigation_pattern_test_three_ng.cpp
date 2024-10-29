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

#include <optional>

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/mousestyle/mouse_style.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
} // namespace

class NavigationPatternTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
};

void NavigationPatternTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationPatternTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

/**
 * @tc.name: InitDragBarEvent001
 * @tc.desc: Increase the coverage of NavigationPattern::InitDragBarEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, InitDragBarEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", 201,
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode("Divider", 301,
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigationNode->SetDividerNode(dividerNode);

    EXPECT_NE(navigationPattern->GetDragBarNode(), nullptr);
    EXPECT_NE(navigationPattern->GetDividerNode(), nullptr);
    EXPECT_EQ(navigationPattern->hoverEvent_, nullptr);
    EXPECT_EQ(navigationPattern->panEvent_, nullptr);
    navigationPattern->InitDragBarEvent();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: InitDragBarEvent002
 * @tc.desc: Increase the coverage of NavigationPattern::InitDragBarEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, InitDragBarEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", 201,
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode("Divider", 301,
        []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigationNode->SetDividerNode(dividerNode);
    auto hoverCallback = [](const MouseInfo& info) {};
    navigationPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>(std::move(hoverCallback));
    auto panActionStart = [](const GestureEvent& event) {};
    navigationPattern->panEvent_ = AceType::MakeRefPtr<PanEvent>(std::move(panActionStart), nullptr, nullptr, nullptr);

    EXPECT_NE(navigationPattern->GetDragBarNode(), nullptr);
    EXPECT_NE(navigationPattern->GetDividerNode(), nullptr);
    EXPECT_NE(navigationPattern->hoverEvent_, nullptr);
    EXPECT_NE(navigationPattern->panEvent_, nullptr);
    navigationPattern->InitDragBarEvent();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ClearDragBarEvent001
 * @tc.desc: Increase the coverage of NavigationPattern::ClearDragBarEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ClearDragBarEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", 201,
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);

    EXPECT_NE(navigationPattern->GetDragBarNode(), nullptr);
    EXPECT_EQ(navigationPattern->touchEvent_, nullptr);
    EXPECT_EQ(navigationPattern->dragBarPanEvent_, nullptr);
    navigationPattern->ClearDragBarEvent();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ClearDragBarEvent002
 * @tc.desc: Increase the coverage of NavigationPattern::ClearDragBarEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ClearDragBarEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", 201,
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto touchTask = [](TouchEventInfo& info) {};
    navigationPattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    auto actionStartTask = [](const GestureEvent& info) {};
    navigationPattern->dragBarPanEvent_ = AceType::MakeRefPtr<PanEvent>(
        std::move(actionStartTask), nullptr, nullptr, nullptr);

    EXPECT_NE(navigationPattern->GetDragBarNode(), nullptr);
    EXPECT_NE(navigationPattern->touchEvent_, nullptr);
    EXPECT_NE(navigationPattern->dragBarPanEvent_, nullptr);
    navigationPattern->ClearDragBarEvent();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: JudgeFoldStateChangeAndUpdateState001
 * @tc.desc: Increase the coverage of NavigationPattern::JudgeFoldStateChangeAndUpdateState function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, JudgeFoldStateChangeAndUpdateState001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    EXPECT_EQ(container->GetCurrentFoldStatus(), navigationPattern->currentFoldStatus_);
    navigationPattern->JudgeFoldStateChangeAndUpdateState();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: JudgeFoldStateChangeAndUpdateState002
 * @tc.desc: Increase the coverage of NavigationPattern::JudgeFoldStateChangeAndUpdateState function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, JudgeFoldStateChangeAndUpdateState002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationPattern->currentFoldStatus_ = FoldStatus::HALF_FOLD;

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    EXPECT_NE(container->GetCurrentFoldStatus(), navigationPattern->currentFoldStatus_);
    navigationPattern->JudgeFoldStateChangeAndUpdateState();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation001
 * @tc.desc: Increase the coverage of NavigationPattern::ReplaceAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", 201,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = nullptr;

    EXPECT_EQ(preTopNavDestinationNode, nullptr);
    EXPECT_EQ(newTopNavDestinationNode, nullptr);
    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation002
 * @tc.desc: Increase the coverage of NavigationPattern::ReplaceAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", 201,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;

    EXPECT_NE(preTopNavDestinationNode, nullptr);
    EXPECT_EQ(newTopNavDestinationNode, nullptr);
    EXPECT_NE(navigationPattern->navigationMode_, NavigationMode::STACK);
    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation003
 * @tc.desc: Increase the coverage of NavigationPattern::ReplaceAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", 201,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::STACK;

    EXPECT_NE(preTopNavDestinationNode, nullptr);
    EXPECT_EQ(newTopNavDestinationNode, nullptr);
    EXPECT_EQ(navigationPattern->navigationMode_, NavigationMode::STACK);
    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation004
 * @tc.desc: Increase the coverage of NavigationPattern::ReplaceAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", 201,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 302, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    EXPECT_NE(preTopNavDestinationNode, nullptr);
    EXPECT_NE(newTopNavDestinationNode, nullptr);
    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange001
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = -1;

    EXPECT_NE(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_EQ(navigationNode->GetLastStandardIndex(), -1);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange002
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationNode->preLastStandardIndex_ = -1;
    navigationNode->lastStandardIndex_ = 0;

    EXPECT_EQ(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_NE(navigationNode->GetLastStandardIndex(), -1);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange003
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationNode->preLastStandardIndex_ = -1;
    navigationNode->lastStandardIndex_ = -1;

    EXPECT_EQ(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_EQ(navigationNode->GetLastStandardIndex(), -1);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange004
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd nullptr
    navigationStack->navPathListBeforePoped_.emplace_back(std::make_pair("Page01", nullptr));
    // Make newStd nullptr
    navigationStack->navPathList_.emplace_back(std::make_pair("Page02", nullptr));
    auto& preNavPathList = navigationStack->GetAllNavDestinationNodesPrev();

    EXPECT_NE(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_NE(navigationNode->GetLastStandardIndex(), -1);
    auto preStd = NavigationGroupNode::GetNavDestinationNode(
        preNavPathList[navigationNode->preLastStandardIndex_].second.Upgrade());
    EXPECT_EQ(preStd, nullptr);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange005
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange005, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd not nullptr
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathListBeforePoped_.emplace_back(
        std::make_pair("Page01", WeakPtr<UINode>(navDestination01Node)));
    // Make newStd nullptr
    navigationStack->navPathList_.emplace_back(std::make_pair("Page02", nullptr));
    auto& preNavPathList = navigationStack->GetAllNavDestinationNodesPrev();
    auto& navPathList = navigationStack->GetAllNavDestinationNodes();

    EXPECT_NE(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_NE(navigationNode->GetLastStandardIndex(), -1);
    auto preStd = NavigationGroupNode::GetNavDestinationNode(
        preNavPathList[navigationNode->preLastStandardIndex_].second.Upgrade());
    EXPECT_NE(preStd, nullptr);
    auto newStd = NavigationGroupNode::GetNavDestinationNode(
        navPathList[navigationNode->lastStandardIndex_].second);
    EXPECT_EQ(newStd, nullptr);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange006
 * @tc.desc: Increase the coverage of NavigationPattern::IsLastStdChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange006, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd not nullptr
    auto navDestination1Node = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathListBeforePoped_.emplace_back(
        std::make_pair("Page01", WeakPtr<UINode>(navDestination1Node)));
    // Make newStd not nullptr
    auto navDestination2Node = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair("Page02", navDestination2Node));
    auto& preNavPathList = navigationStack->GetAllNavDestinationNodesPrev();
    auto& navPathList = navigationStack->GetAllNavDestinationNodes();

    EXPECT_NE(navigationNode->GetPreLastStandardIndex(), -1);
    EXPECT_NE(navigationNode->GetLastStandardIndex(), -1);
    auto preStd = NavigationGroupNode::GetNavDestinationNode(
        preNavPathList[navigationNode->preLastStandardIndex_].second.Upgrade());
    EXPECT_NE(preStd, nullptr);
    auto newStd = NavigationGroupNode::GetNavDestinationNode(
        navPathList[navigationNode->lastStandardIndex_].second);
    EXPECT_NE(newStd, nullptr);
    navigationPattern->IsLastStdChange();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Increase the coverage of NavigationPattern::HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::UNKNOWN;
    eventInfo.touches_.emplace_back(locationInfo);

    EXPECT_NE(eventInfo.touches_.front().GetTouchType(), TouchType::DOWN);
    EXPECT_NE(eventInfo.touches_.front().GetTouchType(), TouchType::UP);
    EXPECT_NE(eventInfo.touches_.front().GetTouchType(), TouchType::CANCEL);
    navigationPattern->HandleTouchEvent(eventInfo);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: Increase the coverage of NavigationPattern::HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::DOWN;
    eventInfo.touches_.emplace_back(locationInfo);

    EXPECT_EQ(eventInfo.touches_.front().GetTouchType(), TouchType::DOWN);
    navigationPattern->HandleTouchEvent(eventInfo);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: Increase the coverage of NavigationPattern::HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::UP;
    eventInfo.touches_.emplace_back(locationInfo);

    EXPECT_EQ(eventInfo.touches_.front().GetTouchType(), TouchType::UP);
    navigationPattern->HandleTouchEvent(eventInfo);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: Increase the coverage of NavigationPattern::HandleTouchEvent function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::CANCEL;
    eventInfo.touches_.emplace_back(locationInfo);

    EXPECT_EQ(eventInfo.touches_.front().GetTouchType(), TouchType::CANCEL);
    navigationPattern->HandleTouchEvent(eventInfo);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG