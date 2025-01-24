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

#include <optional>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "base/mousestyle/mouse_style.h"
#include "core/common/agingadapation/aging_adapation_dialog_util.h"
#include "core/components/dialog/dialog_properties.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_pattern.h"
#include "core/components_ng/pattern/dialog/dialog_view.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t RET_ZERO = 0;
constexpr int32_t RET_ONE = 1;
} // namespace

class NavigationPatternTestThreeNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateDialogNode();
};

void NavigationPatternTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == DialogTheme::TypeId()) {
            return AceType::MakeRefPtr<DialogTheme>();
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> NavigationPatternTestThreeNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG, 100, AceType::MakeRefPtr<Pattern>());
    DialogProperties dialogProperties {
        .title = "Title",
        .content = "Content",
        .width = 300,
        .height = 200,
    };
    return DialogView::CreateDialogNode(dialogProperties, contentNode);
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

/**
 * @tc.name: DialogAnimation001
 * @tc.desc: Increase the coverage of NavigationPattern::DialogAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DialogAnimation001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto preNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);
    EXPECT_FALSE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN));
    navigationPattern->DialogAnimation(preNavDestinationNode, newNavDestinationNode, true, true);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: DialogAnimation002
 * @tc.desc: Increase the coverage of NavigationPattern::DialogAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DialogAnimation002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto preNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    AceApplicationInfo::GetInstance().apiVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_FOURTEEN);
    EXPECT_TRUE(AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_THIRTEEN));
    navigationPattern->DialogAnimation(preNavDestinationNode, newNavDestinationNode, true, true);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery001
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeFromRecovery function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("Page01", navDestinationNode));
    int32_t lastStandardIndex = 0;

    EXPECT_NE(navPathList[lastStandardIndex].second, nullptr);
    navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery002
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeFromRecovery function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("Page01", nullptr));
    int32_t lastStandardIndex = 0;
    
    EXPECT_EQ(navPathList[lastStandardIndex].second, nullptr);
    EXPECT_FALSE(navigationStack->IsFromRecovery(lastStandardIndex));
    navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery003
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeFromRecovery function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("Page01", nullptr));
    int32_t lastStandardIndex = 0;
    MockNavPathInfo page01Info("Page01");
    page01Info.fromRecovery = true;
    navigationStack->mockPathArray_.emplace_back(page01Info);
    MockNavPathInfo page02Info("Page02");
    navigationStack->mockPathArray_.emplace_back(page02Info);
    
    EXPECT_EQ(navPathList[lastStandardIndex].second, nullptr);
    EXPECT_TRUE(navigationStack->IsFromRecovery(lastStandardIndex));
    int32_t ret = navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
    EXPECT_EQ(ret, RET_ONE);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery004
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeFromRecovery function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("Page01", nullptr));
    int32_t lastStandardIndex = 0;
    MockNavPathInfo page01Info("Page01");
    page01Info.fromRecovery = true;
    navigationStack->mockPathArray_.emplace_back(page01Info);
    MockNavPathInfo page02Info("Page02");
    navigationStack->mockPathArray_.emplace_back(page02Info);
    auto route = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(route);
    
    EXPECT_EQ(navPathList[lastStandardIndex].second, nullptr);
    EXPECT_TRUE(navigationStack->IsFromRecovery(lastStandardIndex));
    int32_t ret = navigationPattern->GenerateUINodeFromRecovery(lastStandardIndex, navPathList);
    EXPECT_EQ(ret, RET_ZERO);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex002
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeByIndex002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    RefPtr<UINode> node = navDestinationNode;
    navigationPattern->frameNode_ = nullptr;

    EXPECT_NE(node, nullptr);
    EXPECT_EQ(navigationPattern->GetHost(), nullptr);
    navigationPattern->GenerateUINodeByIndex(0, node);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex003
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeByIndex003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->GetEventHub<EventHub>();
    RefPtr<UINode> node = navDestinationNode;
    auto navDestinationPattern = navDestinationNode->pattern_;
    navDestinationNode->pattern_ = nullptr;

    EXPECT_NE(node, nullptr);
    EXPECT_NE(navigationPattern->GetHost(), nullptr);
    EXPECT_EQ(navDestinationNode->GetPattern(), nullptr);
    navigationPattern->GenerateUINodeByIndex(0, node);
    navDestinationNode->pattern_ = navDestinationPattern;
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeByIndex004
 * @tc.desc: Increase the coverage of NavigationPattern::GenerateUINodeByIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeByIndex004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    RefPtr<UINode> node = navDestinationNode;

    EXPECT_NE(node, nullptr);
    EXPECT_NE(navigationPattern->GetHost(), nullptr);
    EXPECT_NE(navDestinationNode->GetPattern(), nullptr);
    navigationPattern->GenerateUINodeByIndex(0, node);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray001
 * @tc.desc: Increase the coverage of NavigationPattern::GetNavdestinationJsonArray function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = nullptr;
    navigationStack->navPathList_.emplace_back(std::make_pair("Page01", navDestinationNode));
    
    EXPECT_EQ(navDestinationNode, nullptr);
    navigationPattern->GetNavdestinationJsonArray();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray002
 * @tc.desc: Increase the coverage of NavigationPattern::GetNavdestinationJsonArray function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair("Page01", navDestinationNode));
    navDestinationNode->recoverable_ = false;

    EXPECT_NE(navDestinationNode, nullptr);
    EXPECT_FALSE(navDestinationNode->CanRecovery());
    navigationPattern->GetNavdestinationJsonArray();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray003
 * @tc.desc: Increase the coverage of NavigationPattern::GetNavdestinationJsonArray function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationNode->GetEventHub<EventHub>();
    navigationStack->navPathList_.emplace_back(std::make_pair("Page01", navDestinationNode));
    auto navDestinationPattern = navDestinationNode->pattern_;
    navDestinationNode->pattern_ = nullptr;

    EXPECT_NE(navDestinationNode, nullptr);
    EXPECT_TRUE(navDestinationNode->CanRecovery());
    EXPECT_EQ(navDestinationNode->GetPattern<NavDestinationPattern>(), nullptr);
    navigationPattern->GetNavdestinationJsonArray();
    navDestinationNode->pattern_ = navDestinationPattern;
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray004
 * @tc.desc: Increase the coverage of NavigationPattern::GetNavdestinationJsonArray function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair("Page01", navDestinationNode));

    EXPECT_NE(navDestinationNode, nullptr);
    EXPECT_TRUE(navDestinationNode->CanRecovery());
    EXPECT_NE(navDestinationNode->GetPattern<NavDestinationPattern>(), nullptr);
    navigationPattern->GetNavdestinationJsonArray();
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetProxyById001
 * @tc.desc: Branch: if (proxy && proxy->GetProxyId() == id) = false
 *           Condition: proxy = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetProxyById001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->proxyList_.emplace_back(nullptr);

    auto ret = navigationPattern->GetProxyById(100);
    EXPECT_EQ(ret, nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetProxyById002
 * @tc.desc: Branch: if (proxy && proxy->GetProxyId() == id) = false
 *           Condition: proxy = true, proxy->GetProxyId() == id = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetProxyById002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    auto proxyId = proxy->GetProxyId();
    navigationPattern->proxyList_.emplace_back(proxy);

    auto ret = navigationPattern->GetProxyById(proxyId + 100);
    EXPECT_EQ(ret, nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetProxyById003
 * @tc.desc: Branch: if (proxy && proxy->GetProxyId() == id) = true
 *           Condition: proxy = true, proxy->GetProxyId() == id = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetProxyById003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    auto proxyId = proxy->GetProxyId();
    navigationPattern->proxyList_.emplace_back(proxy);

    auto ret = navigationPattern->GetProxyById(proxyId);
    ASSERT_NE(ret, nullptr);
    EXPECT_EQ(ret->GetProxyId(), proxyId);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckContentNeedMeasure001
 * @tc.desc: Branch: if (!IsAutoHeight) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, CheckContentNeedMeasure001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_ = nullptr;
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 201,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->SetContentNode(contentNode);
    contentNode->isFreeze_ = true;
    contentNode->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    navigationPattern->CheckContentNeedMeasure(navigationNode);
    EXPECT_EQ(contentNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_NORMAL);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: CheckContentNeedMeasure002
 * @tc.desc: Branch: if (!IsAutoHeight) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, CheckContentNeedMeasure002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    ASSERT_NE(navigationLayoutProperty->calcLayoutConstraint_, nullptr);
    navigationLayoutProperty->calcLayoutConstraint_->selfIdealSize =
        CalcSize(NG::CalcLength(100.0f), NG::CalcLength("auto"));
    auto contentNode = FrameNode::GetOrCreateFrameNode(V2::NAVDESTINATION_CONTENT_ETS_TAG, 201,
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    navigationNode->SetContentNode(contentNode);
    contentNode->isFreeze_ = true;
    contentNode->layoutProperty_->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    navigationPattern->CheckContentNeedMeasure(navigationNode);
    EXPECT_EQ(contentNode->layoutProperty_->propertyChangeFlag_, PROPERTY_UPDATE_MEASURE);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: CloseLongPressDialog001
 * @tc.desc: Branch: if (backButtonDialogNode) = true
 *           Branch: if (menuItemDialogNode) = true
 *           Branch: if (toolBarItemDialogNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, CloseLongPressDialog001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navBarNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = NavigationPatternTestThreeNg::CreateDialogNode();
    int32_t backButtonDialogNodeId = titleBarPattern->dialogNode_->GetId();
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    overlayManager->dialogMap_.emplace(backButtonDialogNodeId, titleBarPattern->dialogNode_);
    auto menuItemDialogNode = NavigationPatternTestThreeNg::CreateDialogNode();
    int32_t menuItemDialogNodeId = menuItemDialogNode->GetId();
    titleBarPattern->largeFontPopUpDialogNode_ = AceType::WeakClaim(AceType::RawPtr(menuItemDialogNode));
    overlayManager->dialogMap_.emplace(menuItemDialogNodeId, menuItemDialogNode);
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navBarNode->toolBarNode_ = toolBarNode;
    auto toolBarPattern = AceType::DynamicCast<NavToolbarPattern>(toolBarNode->GetPattern());
    ASSERT_NE(toolBarPattern, nullptr);
    toolBarPattern->dialogNode_ = NavigationPatternTestThreeNg::CreateDialogNode();
    int32_t toolBarItemDialogNodeId = toolBarPattern->dialogNode_->GetId();
    overlayManager->dialogMap_.emplace(toolBarItemDialogNodeId, toolBarPattern->dialogNode_);

    navigationPattern->CloseLongPressDialog();
    EXPECT_EQ(overlayManager->dialogMap_.find(backButtonDialogNodeId), overlayManager->dialogMap_.end());
    EXPECT_EQ(overlayManager->dialogMap_.find(menuItemDialogNodeId), overlayManager->dialogMap_.end());
    EXPECT_EQ(overlayManager->dialogMap_.find(toolBarItemDialogNodeId), overlayManager->dialogMap_.end());
    EXPECT_EQ(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_EQ(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    EXPECT_EQ(toolBarPattern->GetDialogNode(), nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: CloseLongPressDialog002
 * @tc.desc: Branch: if (backButtonDialogNode) = false
 *           Branch: if (menuItemDialogNode) = false
 *           Branch: if (toolBarItemDialogNode) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, CloseLongPressDialog002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navBarNode->titleBarNode_ = titleBarNode;
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);
    titleBarPattern->dialogNode_ = nullptr;
    titleBarPattern->largeFontPopUpDialogNode_ = nullptr;
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    navBarNode->toolBarNode_ = toolBarNode;
    auto toolBarPattern = AceType::DynamicCast<NavToolbarPattern>(toolBarNode->GetPattern());
    ASSERT_NE(toolBarPattern, nullptr);
    toolBarPattern->dialogNode_ = nullptr;

    navigationPattern->CloseLongPressDialog();
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    auto overlayManager = pipelineContext->GetOverlayManager();
    ASSERT_NE(overlayManager, nullptr);
    EXPECT_EQ(overlayManager->dialogMap_.size(), 0);
    EXPECT_EQ(titleBarPattern->GetBackButtonDialogNode(), nullptr);
    EXPECT_EQ(titleBarPattern->GetLargeFontPopUpDialogNode(), nullptr);
    EXPECT_EQ(toolBarPattern->GetDialogNode(), nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RemoveFromDumpManager001
 * @tc.desc: Branch: if (!node || !context) = false
 *           Condition: !node = false, !context = false
 *           Branch: if (mgr) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RemoveFromDumpManager001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto mgr = context->GetNavigationManager();
    auto callback = [](int depth) {};
    mgr->AddNavigationDumpCallback(navigationNode->GetId(), navigationNode->GetDepth(), callback);

    navigationPattern->RemoveFromDumpManager();
    EXPECT_EQ(mgr->dumpMap_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RemoveFromDumpManager002
 * @tc.desc: Branch: if (!node || !context) = true
 *           Condition: !node = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RemoveFromDumpManager002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto mgr = context->GetNavigationManager();
    auto callback = [](int depth) {};
    mgr->AddNavigationDumpCallback(navigationNode->GetId(), navigationNode->GetDepth(), callback);
    navigationPattern->frameNode_ = nullptr;

    navigationPattern->RemoveFromDumpManager();
    EXPECT_EQ(mgr->dumpMap_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RemoveFromDumpManager003
 * @tc.desc: Branch: if (!node || !context) = true
 *           Condition: !node = false, !context = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RemoveFromDumpManager003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto mgr = context->GetNavigationManager();
    auto callback = [](int depth) {};
    mgr->AddNavigationDumpCallback(navigationNode->GetId(), navigationNode->GetDepth(), callback);
    MockPipelineContext::pipeline_ = nullptr;

    navigationPattern->RemoveFromDumpManager();
    EXPECT_EQ(mgr->dumpMap_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RemoveFromDumpManager004
 * @tc.desc: Branch: if (!node || !context) = false
 *           Condition: !node = false, !context = false
 *           Branch: if (mgr) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RemoveFromDumpManager004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto mgr = context->GetNavigationManager();
    auto callback = [](int depth) {};
    mgr->AddNavigationDumpCallback(navigationNode->GetId(), navigationNode->GetDepth(), callback);
    context->navigationMgr_ = nullptr;

    navigationPattern->RemoveFromDumpManager();
    EXPECT_EQ(mgr->dumpMap_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG