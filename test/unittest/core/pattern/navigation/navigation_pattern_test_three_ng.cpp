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
constexpr float BLUR_OPACITY = 0.1f;
const std::string NAVIGATION_ID1 = "Navigation1";
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
const std::string PAGE03 = "Page03";
} // namespace

class NavigationPatternTestThreeNg : public testing::Test {
public:
    static RefPtr<DialogTheme> dialogTheme_;
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    static RefPtr<FrameNode> CreateDialogNode();
};

namespace {
RefPtr<Theme> GetTheme(ThemeType type)
{
    if (type == DialogTheme::TypeId()) {
        return NavigationPatternTestThreeNg::dialogTheme_;
    } else if (type == NavigationBarTheme::TypeId()) {
        return NavigationPatternTestThreeNg::navigationBarTheme_;
    } else {
        return nullptr;
    }
}
} // namespace

RefPtr<DialogTheme> NavigationPatternTestThreeNg::dialogTheme_ = nullptr;
RefPtr<NavigationBarTheme> NavigationPatternTestThreeNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestThreeNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    dialogTheme_ = AceType::MakeRefPtr<DialogTheme>();
    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        return GetTheme(type);
    });
    EXPECT_CALL(*themeManager, GetTheme(_, _))
        .WillRepeatedly([](ThemeType type, int32_t themeScopeId) -> RefPtr<Theme> { return GetTheme(type); });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestThreeNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

RefPtr<FrameNode> NavigationPatternTestThreeNg::CreateDialogNode()
{
    auto contentNode = FrameNode::CreateFrameNode(V2::BLANK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
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
 * @tc.desc: Branch: if (hoverEvent_) = true
 *           Branch: if (panEvent_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, InitDragBarEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigationNode->SetDividerNode(dividerNode);
    auto hoverCallback = [](const MouseInfo& info) {};
    navigationPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>(hoverCallback);
    auto dividerInputHub = dividerNode->GetOrCreateInputEventHub();
    ASSERT_NE(dividerInputHub, nullptr);
    dividerInputHub->AddOnHoverEvent(navigationPattern->hoverEvent_);
    auto panActionStart = [](const GestureEvent& event) {};
    navigationPattern->panEvent_ = AceType::MakeRefPtr<PanEvent>(panActionStart, nullptr, nullptr, nullptr);
    auto dividerGestureHub = dividerNode->GetOrCreateGestureEventHub();
    ASSERT_NE(dividerGestureHub, nullptr);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    dividerGestureHub->AddPanEvent(navigationPattern->panEvent_, panDirection, 1, 0.0_vp);

    navigationPattern->InitDragBarEvent();
    ASSERT_NE(dividerInputHub->hoverEventActuator_, nullptr);
    ASSERT_EQ(dividerInputHub->hoverEventActuator_->inputEvents_.size(), 0);
    ASSERT_NE(dividerGestureHub->panEventActuator_, nullptr);
    ASSERT_EQ(dividerGestureHub->panEventActuator_->panEvents_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: InitDragBarEvent002
 * @tc.desc: Branch: if (hoverEvent_) = false
 *           Branch: if (panEvent_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, InitDragBarEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigationNode->SetDividerNode(dividerNode);
    navigationPattern->panEvent_ = nullptr;
    navigationPattern->hoverEvent_ = nullptr;

    navigationPattern->InitDragBarEvent();
    auto dividerInputHub = dividerNode->GetOrCreateInputEventHub();
    ASSERT_NE(dividerInputHub, nullptr);
    EXPECT_EQ(dividerInputHub->hoverEventActuator_, nullptr);
    auto dividerGestureHub = dividerNode->GetOrCreateGestureEventHub();
    ASSERT_NE(dividerGestureHub, nullptr);
    EXPECT_EQ(dividerGestureHub->panEventActuator_, nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ClearDragBarEvent001
 * @tc.desc: Branch: if (touchEvent_) = true
 *           Branch: if (dragBarPanEvent_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ClearDragBarEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto touchTask = [](TouchEventInfo& info) {};
    navigationPattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    auto dragGestureHub = dragBarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(dragGestureHub, nullptr);
    dragGestureHub->AddTouchEvent(navigationPattern->touchEvent_);
    auto actionStartTask = [](const GestureEvent& info) {};
    navigationPattern->dragBarPanEvent_ = AceType::MakeRefPtr<PanEvent>(actionStartTask, nullptr, nullptr, nullptr);
    PanDirection panDirection;
    panDirection.type = PanDirection::ALL;
    dragGestureHub->AddPanEvent(navigationPattern->dragBarPanEvent_, panDirection, 1, 0.0_vp);

    navigationPattern->ClearDragBarEvent();
    ASSERT_NE(dragGestureHub->touchEventActuator_, nullptr);
    ASSERT_EQ(dragGestureHub->touchEventActuator_->touchEvents_.size(), 0);
    ASSERT_NE(dragGestureHub->panEventActuator_, nullptr);
    ASSERT_EQ(dragGestureHub->panEventActuator_->panEvents_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ClearDragBarEvent002
 * @tc.desc: Branch: if (touchEvent_) = false
 *           Branch: if (dragBarPanEvent_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ClearDragBarEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    navigationPattern->touchEvent_ = nullptr;
    navigationPattern->dragBarPanEvent_ = nullptr;

    navigationPattern->ClearDragBarEvent();
    auto dragGestureHub = dragBarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(dragGestureHub, nullptr);
    EXPECT_EQ(dragGestureHub->touchEventActuator_, nullptr);
    EXPECT_EQ(dragGestureHub->panEventActuator_, nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: JudgeFoldStateChangeAndUpdateState001
 * @tc.desc: Branch: if (foldStatus != currentFoldStatus_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, JudgeFoldStateChangeAndUpdateState001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->currentFoldStatus_ = FoldStatus::HALF_FOLD;

    bool ret = navigationPattern->JudgeFoldStateChangeAndUpdateState();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: JudgeFoldStateChangeAndUpdateState002
 * @tc.desc: Branch: if (foldStatus != currentFoldStatus_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, JudgeFoldStateChangeAndUpdateState002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    navigationPattern->currentFoldStatus_ = container->GetCurrentFoldStatus();

    bool ret = navigationPattern->JudgeFoldStateChangeAndUpdateState();
    EXPECT_FALSE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation001
 * @tc.desc: Branch: if (newTopNavDestination && preTopNavDestination) = true
 *           Condition: newTopNavDestination = true, preTopNavDestination = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto preTopNavDestinationEventHub = preTopNavDestinationNode->GetEventHub<EventHub>();
    ASSERT_NE(preTopNavDestinationEventHub, nullptr);
    preTopNavDestinationEventHub->SetEnabledInternal(false);

    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    EXPECT_TRUE(preTopNavDestinationEventHub->enabled_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation002
 * @tc.desc: Branch: if (newTopNavDestination && preTopNavDestination) = false
 *           Condition: newTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    auto preTopNavDestinationEventHub = preTopNavDestinationNode->GetEventHub<EventHub>();
    ASSERT_NE(preTopNavDestinationEventHub, nullptr);
    preTopNavDestinationEventHub->SetEnabledInternal(false);
    auto navBarEventHub = navBarNode->GetEventHub<EventHub>();
    ASSERT_NE(navBarEventHub, nullptr);
    navBarEventHub->SetEnabledInternal(false);

    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    EXPECT_FALSE(preTopNavDestinationEventHub->enabled_);
    EXPECT_FALSE(navBarEventHub->enabled_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation003
 * @tc.desc: Branch: if (newTopNavDestination && preTopNavDestination) = false
 *           Condition: newTopNavDestination = true, preTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = true, navigationMode_ == NavigationMode::STACK = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto navBarEventHub = navBarNode->GetEventHub<EventHub>();
    ASSERT_NE(navBarEventHub, nullptr);
    navBarEventHub->SetEnabledInternal(false);

    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    EXPECT_FALSE(navBarEventHub->enabled_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: ReplaceAnimation004
 * @tc.desc: Branch: if (newTopNavDestination && preTopNavDestination) = false
 *           Condition: newTopNavDestination = true, preTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = true
 *           Condition: newTopNavDestination = true, navigationMode_ == NavigationMode::STACK = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, ReplaceAnimation004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto navBarEventHub = navBarNode->GetEventHub<EventHub>();
    ASSERT_NE(navBarEventHub, nullptr);
    navBarEventHub->SetEnabledInternal(false);

    navigationPattern->ReplaceAnimation(preTopNavDestinationNode, newTopNavDestinationNode);
    EXPECT_TRUE(navBarEventHub->enabled_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange001
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = false
 *           Condition: preLastStdIndex == -1 = false
 *           Branch: if (preLastStdIndex != -1 && lastStdIndex != -1) = false
 *           Condition: preLastStdIndex != -1 = true, lastStdIndex != -1 = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = -1;

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange002
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = false
 *           Condition: preLastStdIndex == -1 = true, lastStdIndex == -1 = false
 *           Branch: if (preLastStdIndex != -1 && lastStdIndex != -1) = false
 *           Condition: preLastStdIndex != -1 = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = -1;
    navigationNode->lastStandardIndex_ = 0;

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange003
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = true
 *           Condition: preLastStdIndex == -1 = true, lastStdIndex == -1 = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    navigationNode->preLastStandardIndex_ = -1;
    navigationNode->lastStandardIndex_ = -1;

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_FALSE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange004
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = false
 *           Condition: preLastStdIndex == -1 = false
 *           Branch: if (preLastStdIndex != -1 && lastStdIndex != -1) = true
 *           Condition: preLastStdIndex != -1 = true, lastStdIndex != -1 = true
 *           Branch: if (preStd && newStd) = false
 *           Condition: preStd = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd false
    navigationStack->navPathListBeforePoped_.emplace_back(std::make_pair(PAGE01, nullptr));
    // Make newStd false
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE02, nullptr));

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange005
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = false
 *           Condition: preLastStdIndex == -1 = false
 *           Branch: if (preLastStdIndex != -1 && lastStdIndex != -1) = true
 *           Condition: preLastStdIndex != -1 = true, lastStdIndex != -1 = true
 *           Branch: if (preStd && newStd) = false
 *           Condition: preStd = true, newStd = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange005, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd true
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathListBeforePoped_.emplace_back(
        std::make_pair(PAGE01, WeakPtr<UINode>(navDestination01Node)));
    // Make newStd false
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE02, nullptr));

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: IsLastStdChange006
 * @tc.desc: Branch: if (preLastStdIndex == -1 && lastStdIndex == -1) = false
 *           Condition: preLastStdIndex == -1 = false
 *           Branch: if (preLastStdIndex != -1 && lastStdIndex != -1) = true
 *           Condition: preLastStdIndex != -1 = true, lastStdIndex != -1 = true
 *           Branch: if (preStd && newStd) = true
 *           Condition: preStd = true, newStd = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, IsLastStdChange006, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationNode->preLastStandardIndex_ = 0;
    navigationNode->lastStandardIndex_ = 0;
    // Make preStd true
    auto navDestination1Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathListBeforePoped_.emplace_back(
        std::make_pair(PAGE01, WeakPtr<UINode>(navDestination1Node)));
    // Make newStd true
    auto navDestination2Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE02, navDestination2Node));

    bool ret = navigationPattern->IsLastStdChange();
    EXPECT_TRUE(ret);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: isNodeVisible
 * @tc.desc: Test node visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, isNodeVisible, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation stack, and add navBar
    */
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
   
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode("NavBar", 201,
        []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;

    /**
     * @tc.steps: step2. set navigationMode stack
    */
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("A", navDestinationA);
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("B", navDestinationB);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    navigationNode->UpdateLastStandardIndex();
    
    auto navBarNode2 = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    EXPECT_NE(navBarNode2, nullptr);
    bool isInvisible = navBarNode2->IsNodeInvisible(navigationNode);
    ASSERT_EQ(isInvisible, true);
}

/**
 * @tc.name: HandleTouchEvent001
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = false
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::UNKNOWN;
    eventInfo.touches_.emplace_back(locationInfo);
    auto navigationBarTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    navigationBarTheme->dragBarDefaultColor_ = Color::WHITE;
    navigationBarTheme->dragBarActiveColor_ = Color::GRAY;
    navigationBarTheme_ = navigationBarTheme;
    auto dragBarRenderContext = dragBarNode->GetRenderContext();
    ASSERT_NE(dragBarRenderContext, nullptr);
    dragBarRenderContext->UpdateBackgroundColor(Color::BLUE);

    navigationPattern->HandleTouchEvent(eventInfo);
    EXPECT_NE(dragBarRenderContext->GetBackgroundColor(), navigationBarTheme->dragBarDefaultColor_);
    EXPECT_NE(dragBarRenderContext->GetBackgroundColor(), navigationBarTheme->dragBarActiveColor_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent002
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = true
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = false
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::DOWN;
    eventInfo.touches_.emplace_back(locationInfo);
    auto navigationBarTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    navigationBarTheme->dragBarDefaultColor_ = Color::WHITE;
    navigationBarTheme->dragBarActiveColor_ = Color::GRAY;
    navigationBarTheme_ = navigationBarTheme;
    auto dragBarRenderContext = dragBarNode->GetRenderContext();
    ASSERT_NE(dragBarRenderContext, nullptr);
    dragBarRenderContext->UpdateBackgroundColor(Color::BLUE);

    navigationPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarRenderContext->GetBackgroundColor(), navigationBarTheme->dragBarActiveColor_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent003
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = true
 *           Condition: touchType == TouchType::UP = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::UP;
    eventInfo.touches_.emplace_back(locationInfo);
    auto navigationBarTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    navigationBarTheme->dragBarDefaultColor_ = Color::WHITE;
    navigationBarTheme->dragBarActiveColor_ = Color::GRAY;
    navigationBarTheme_ = navigationBarTheme;
    auto dragBarRenderContext = dragBarNode->GetRenderContext();
    ASSERT_NE(dragBarRenderContext, nullptr);
    dragBarRenderContext->UpdateBackgroundColor(Color::BLUE);

    navigationPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarRenderContext->GetBackgroundColor(),
        navigationBarTheme->dragBarDefaultColor_.ChangeOpacity(BLUR_OPACITY));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: Branch: if (touchType == TouchType::DOWN) = false
 *           Branch: if (touchType == TouchType::UP || touchType == TouchType::CANCEL) = true
 *           Condition: touchType == TouchType::UP = false, touchType == TouchType::CANCEL = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, HandleTouchEvent004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto dragBarNode = FrameNode::GetOrCreateFrameNode(V2::DRAG_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    navigationNode->SetDragBarNode(dragBarNode);
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    TouchEventInfo eventInfo("Touch1");
    TouchLocationInfo locationInfo(0);
    locationInfo.touchType_ = TouchType::CANCEL;
    eventInfo.touches_.emplace_back(locationInfo);
    auto navigationBarTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    navigationBarTheme->dragBarDefaultColor_ = Color::WHITE;
    navigationBarTheme->dragBarActiveColor_ = Color::GRAY;
    navigationBarTheme_ = navigationBarTheme;
    auto dragBarRenderContext = dragBarNode->GetRenderContext();
    ASSERT_NE(dragBarRenderContext, nullptr);
    dragBarRenderContext->UpdateBackgroundColor(Color::BLUE);

    navigationPattern->HandleTouchEvent(eventInfo);
    EXPECT_EQ(dragBarRenderContext->GetBackgroundColor(),
        navigationBarTheme->dragBarDefaultColor_.ChangeOpacity(BLUR_OPACITY));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery001
 * @tc.desc: Branch: if (navPathList[index].second || !navigationStack_->IsFromRecovery(index)) = true
 *           Condition: navPathList[index].second = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->fromRecovery = false;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    int32_t removeSize = navigationPattern->GenerateUINodeFromRecovery(0, navPathList);
    EXPECT_EQ(removeSize, 0);
    EXPECT_FALSE(navigationStack->IsFromRecovery(0));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery002
 * @tc.desc: Branch: if (navPathList[index].second || !navigationStack_->IsFromRecovery(index)) = true
 *           Condition: navPathList[index].second = false, !navigationStack_->IsFromRecovery(index) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair(PAGE01, nullptr));
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->fromRecovery = false;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    int32_t removeSize = navigationPattern->GenerateUINodeFromRecovery(0, navPathList);
    EXPECT_EQ(removeSize, 0);
    EXPECT_FALSE(navigationStack->IsFromRecovery(0));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery003
 * @tc.desc: Branch: if (navPathList[index].second || !navigationStack_->IsFromRecovery(index)) = false
 *           Condition: navPathList[index].second = false, !navigationStack_->IsFromRecovery(index) = false
 *           Branch: if (!GenerateUINodeByIndex(index - removeSize, navPathList[index].second)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair(PAGE01, nullptr));
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->fromRecovery = true;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    int32_t removeSize = navigationPattern->GenerateUINodeFromRecovery(0, navPathList);
    EXPECT_EQ(removeSize, 1);
    EXPECT_TRUE(navigationStack->IsFromRecovery(0));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GenerateUINodeFromRecovery004
 * @tc.desc: Branch: if (navPathList[index].second || !navigationStack_->IsFromRecovery(index)) = false
 *           Condition: navPathList[index].second = false, !navigationStack_->IsFromRecovery(index) = false
 *           Branch: if (!GenerateUINodeByIndex(index - removeSize, navPathList[index].second)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GenerateUINodeFromRecovery004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair(PAGE01, nullptr));
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->fromRecovery = true;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    int32_t removeSize = navigationPattern->GenerateUINodeFromRecovery(0, navPathList);
    EXPECT_EQ(removeSize, 0);
    EXPECT_FALSE(navigationStack->IsFromRecovery(0));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray001
 * @tc.desc: Branch: if (!navdestinationNode) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = nullptr;
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));

    auto allNavdestinationInfo = navigationPattern->GetNavdestinationJsonArray();
    EXPECT_EQ(allNavdestinationInfo->GetArraySize(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray002
 * @tc.desc: Branch: if (!navdestinationNode) = false
 *           Branch: if (!navdestinationNode->CanRecovery()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    navDestinationNode->recoverable_ = false;

    auto allNavdestinationInfo = navigationPattern->GetNavdestinationJsonArray();
    EXPECT_EQ(allNavdestinationInfo->GetArraySize(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray003
 * @tc.desc: Branch: if (!navdestinationNode) = false
 *           Branch: if (!navdestinationNode->CanRecovery()) = false
 *           Branch: if (!navdestinationPattern) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    auto navDestinationPattern = navDestinationNode->pattern_;
    navDestinationNode->pattern_ = nullptr;

    auto allNavdestinationInfo = navigationPattern->GetNavdestinationJsonArray();
    EXPECT_EQ(allNavdestinationInfo->GetArraySize(), 0);
    navDestinationNode->pattern_ = navDestinationPattern;
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: GetNavdestinationJsonArray004
 * @tc.desc: Branch: if (!navdestinationNode) = false
 *           Branch: if (!navdestinationNode->CanRecovery()) = false
 *           Branch: if (!navdestinationPattern) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, GetNavdestinationJsonArray004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navdestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navdestinationPattern, nullptr);
    navdestinationPattern->name_ = PAGE01;
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));

    auto allNavdestinationInfo = navigationPattern->GetNavdestinationJsonArray();
    EXPECT_EQ(allNavdestinationInfo->GetArraySize(), 1);
    auto navdestinationInfo = allNavdestinationInfo->GetArrayItem(0);
    ASSERT_NE(navdestinationInfo, nullptr);
    EXPECT_EQ(navdestinationInfo->GetString("name"), PAGE01);
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
    mgr->AddNavigationDumpCallback(navigationNode, callback);

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
    mgr->AddNavigationDumpCallback(navigationNode, callback);
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
    mgr->AddNavigationDumpCallback(navigationNode, callback);
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
    mgr->AddNavigationDumpCallback(navigationNode, callback);
    context->navigationMgr_ = nullptr;

    navigationPattern->RemoveFromDumpManager();
    EXPECT_EQ(mgr->dumpMap_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RefreshFocusToDestination001
 * @tc.desc: Branch: if (!newTopNavPath.has_value()) = false
 *           Branch: if (!navBarFocus->IsCurrentFocus()) = false
 *           Branch: if (!GetIsFocusable(newTopNavDestination)) = false
 *           Branch: if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RefreshFocusToDestination001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // Make newTopNavPath.has_value return true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    navigationPattern->SetNavigationStack(navigationStack);
    // Make IsCurrentFocus return true
    auto navBarFocus = navBarNode->GetFocusHub();
    ASSERT_NE(navBarFocus, nullptr);
    navBarFocus->currentFocus_ = true;
    // Make GetIsFocusable return true
    auto navigationFocusHub = navigationNode->GetFocusHub();
    ASSERT_NE(navigationFocusHub, nullptr);
    navigationFocusHub->focusType_ = FocusType::NODE;
    navigationFocusHub->focusable_ = true;
    navigationFocusHub->parentFocusable_ = true;
    // Make LessThanAPIVersion return false
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_TWELVE);
    // Set SetIsViewRootScopeFocused testing parameters
    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
    ASSERT_NE(navDestinationFocusView, nullptr);
    navDestinationFocusView->isViewRootScopeFocused_ = true;
    // Set FocusViewShow testing parameters
    navDestinationFocusView->isViewHasFocused_ = true;

    navigationPattern->RefreshFocusToDestination();
    EXPECT_TRUE(navDestinationFocusView->isViewRootScopeFocused_);
    EXPECT_FALSE(navDestinationFocusView->isViewHasFocused_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RefreshFocusToDestination002
 * @tc.desc: Branch: if (!newTopNavPath.has_value()) = false
 *           Branch: if (!navBarFocus->IsCurrentFocus()) = false
 *           Branch: if (!GetIsFocusable(newTopNavDestination)) = false
 *           Branch: if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RefreshFocusToDestination002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // Make newTopNavPath.has_value return true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    navigationPattern->SetNavigationStack(navigationStack);
    // Make IsCurrentFocus return true
    auto navBarFocus = navBarNode->GetFocusHub();
    ASSERT_NE(navBarFocus, nullptr);
    navBarFocus->currentFocus_ = true;
    // Make GetIsFocusable return true
    auto navigationFocusHub = navigationNode->GetFocusHub();
    ASSERT_NE(navigationFocusHub, nullptr);
    navigationFocusHub->focusType_ = FocusType::NODE;
    navigationFocusHub->focusable_ = true;
    navigationFocusHub->parentFocusable_ = true;
    // Make LessThanAPIVersion return false
    auto pipelineContext = navigationNode->GetContext();
    ASSERT_NE(pipelineContext, nullptr);
    pipelineContext->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN);
    // Set SetIsViewRootScopeFocused testing parameters
    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
    ASSERT_NE(navDestinationFocusView, nullptr);
    navDestinationFocusView->isViewRootScopeFocused_ = true;
    // Set FocusViewShow testing parameters
    navDestinationFocusView->isViewHasFocused_ = true;

    navigationPattern->RefreshFocusToDestination();
    EXPECT_FALSE(navDestinationFocusView->isViewRootScopeFocused_);
    EXPECT_FALSE(navDestinationFocusView->isViewHasFocused_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RefreshFocusToDestination003
 * @tc.desc: Branch: if (!newTopNavPath.has_value()) = false
 *           Branch: if (!navBarFocus->IsCurrentFocus()) = false
 *           Branch: if (!GetIsFocusable(newTopNavDestination)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RefreshFocusToDestination003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // Make newTopNavPath.has_value return true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    navigationPattern->SetNavigationStack(navigationStack);
    // Make IsCurrentFocus return true
    auto navBarFocus = navBarNode->GetFocusHub();
    ASSERT_NE(navBarFocus, nullptr);
    navBarFocus->currentFocus_ = true;
    // Make GetIsFocusable return false
    auto navigationFocusHub = navigationNode->GetFocusHub();
    ASSERT_NE(navigationFocusHub, nullptr);
    navigationFocusHub->focusType_ = FocusType::NODE;
    navigationFocusHub->focusable_ = false;
    // Set FocusViewShow testing parameters
    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
    ASSERT_NE(navDestinationFocusView, nullptr);
    navDestinationFocusView->isViewHasFocused_ = true;

    navigationPattern->RefreshFocusToDestination();
    EXPECT_TRUE(navDestinationFocusView->isViewHasFocused_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RefreshFocusToDestination004
 * @tc.desc: Branch: if (!newTopNavPath.has_value()) = false
 *           Branch: if (!navBarFocus->IsCurrentFocus()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RefreshFocusToDestination004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // Make newTopNavPath.has_value return true
    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationStack->navPathList_.emplace_back(std::make_pair(PAGE01, navDestinationNode));
    navigationPattern->SetNavigationStack(navigationStack);
    // Make IsCurrentFocus return true
    auto navBarFocus = navBarNode->GetFocusHub();
    ASSERT_NE(navBarFocus, nullptr);
    navBarFocus->currentFocus_ = false;
    // Set FocusViewShow testing parameters
    auto navDestinationFocusView = navDestinationNode->GetPattern<FocusView>();
    ASSERT_NE(navDestinationFocusView, nullptr);
    navDestinationFocusView->isViewHasFocused_ = true;

    navigationPattern->RefreshFocusToDestination();
    EXPECT_TRUE(navDestinationFocusView->isViewHasFocused_);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: RefreshFocusToDestination005
 * @tc.desc: Branch: if (!newTopNavPath.has_value()) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, RefreshFocusToDestination005, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    // Make newTopNavPath.has_value return false
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);

    navigationPattern->RefreshFocusToDestination();
    auto topNavPath = navigationStack->GetTopNavPath();
    EXPECT_FALSE(topNavPath.has_value());
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: DumpInfo001
 * @tc.desc: Branch: if (!navigationStack_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DumpInfo001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    DumpLog::GetInstance().description_.clear();

    navigationPattern->DumpInfo();
    ASSERT_EQ(DumpLog::GetInstance().description_.size(), 1);
    EXPECT_EQ(DumpLog::GetInstance().description_[0], "size0\n");
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: DumpInfo002
 * @tc.desc: Branch: if (!navigationStack_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DumpInfo002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    DumpLog::GetInstance().description_.clear();

    navigationPattern->DumpInfo();
    EXPECT_EQ(DumpLog::GetInstance().description_.size(), 0);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: DumpInfo101
 * @tc.desc: Branch: if (!navigationStack_) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DumpInfo101, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    navigationPattern->DumpInfo(info);
    EXPECT_EQ(info->GetString("size"), "0");
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: DumpInfo102
 * @tc.desc: Branch: if (!navigationStack_) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, DumpInfo102, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    std::unique_ptr<JsonValue> info = JsonUtil::Create(true);
    navigationPattern->DumpInfo(info);
    EXPECT_EQ(info->GetString("size"), "");
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation001
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = true
 *           Condition: preTopNavDestination = true, newTopNavDestination = true
 *           Branch: if (isPopPage) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, true);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation002
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = true
 *           Condition: preTopNavDestination = true, newTopNavDestination = true
 *           Branch: if (isPopPage) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 0);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation003
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = true, newTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = false
 *           Branch: if (preTopNavDestination) = true
 *           Branch: if (navigationMode_ == NavigationMode::SPLIT) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation004
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = true, newTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = false
 *           Branch: if (preTopNavDestination) = true
 *           Branch: if (navigationMode_ == NavigationMode::SPLIT) = false
 *           Branch: if (navigationMode_ == NavigationMode::STACK) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 1);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation005
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = true, newTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = false
 *           Branch: if (preTopNavDestination) = true
 *           Branch: if (navigationMode_ == NavigationMode::SPLIT) = false
 *           Branch: if (navigationMode_ == NavigationMode::STACK) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation005, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::AUTO;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 0);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation006
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = false, newTopNavDestination = false
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = false
 *           Branch: if (preTopNavDestination) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation006, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = nullptr;
    navigationPattern->navigationMode_ = NavigationMode::AUTO;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 0);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation007
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = false, newTopNavDestination = true
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = false
 *           Condition: newTopNavDestination = true, navigationMode_ == NavigationMode::STACK = false
 *           Branch: if (preTopNavDestination) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation007, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationMode_ = NavigationMode::AUTO;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 0);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: FollowStdNavdestinationAnimation008
 * @tc.desc: Branch: if (preTopNavDestination && newTopNavDestination) = false
 *           Condition: preTopNavDestination = false, newTopNavDestination = true
 *           Branch: if (newTopNavDestination && navigationMode_ == NavigationMode::STACK) = true
 *           Condition: newTopNavDestination = true, navigationMode_ == NavigationMode::STACK = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, FollowStdNavdestinationAnimation008, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationNode->navBarNode_ = navBarNode;
    auto preTopNavDestinationNode = nullptr;
    auto newTopNavDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationNode->popAnimations_.clear();
    navigationNode->pushAnimations_.clear();

    navigationPattern->FollowStdNavdestinationAnimation(preTopNavDestinationNode, newTopNavDestinationNode, false);
    EXPECT_EQ(navigationNode->popAnimations_.size(), 0);
    EXPECT_EQ(navigationNode->pushAnimations_.size(), 1);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList001
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = true
 *           Branch: if (GetRecoveredDestinationMode(arrayIndex) == NavDestinationMode::STANDARD)) = false
 *           Branch: if (GetRecoveredDestinationMode(arrayIndex) == NavDestinationMode::STANDARD)) = true
 *           Branch: if (index == pathListSize - 1) = false
 *           Branch: if (index == pathListSize - 1) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList001, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->fromRecovery = true;
    page01Info->mode = static_cast<int32_t>(NavDestinationMode::DIALOG);
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);
    auto page02Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE02);
    page02Info->fromRecovery = true;
    navigationStack->MockPushPath(page02Info, true, LaunchMode::STANDARD);

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    ASSERT_EQ(navPathList.size(), 2);
    EXPECT_EQ(navPathList[0].first, PAGE01);
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_EQ(navPathList[1].first, PAGE02);
    auto navDestination02NodeInList = AceType::DynamicCast<NavDestinationGroupNode>(navPathList[1].second);
    ASSERT_NE(navDestination02NodeInList, nullptr);
    EXPECT_TRUE(navDestination02NodeInList->NeedAppearFromRecovery());
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList002
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = true
 *           Branch: if (!GenerateUINodeByIndex(arrayIndex, uiNode)) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList002, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->needBuildNewInstance = true;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList.size(), 0);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList003
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = true
 *           Branch: if (!GenerateUINodeByIndex(arrayIndex, uiNode)) = false
 *           Branch: if (index == pathListSize - 1) = false
 *           Branch: if (index == pathListSize - 1) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList003, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    auto page01Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE01);
    page01Info->needBuildNewInstance = true;
    navigationStack->MockPushPath(page01Info, true, LaunchMode::STANDARD);
    auto page02Info = AceType::MakeRefPtr<MockNavPathInfo>(PAGE02);
    page02Info->needBuildNewInstance = true;
    navigationStack->MockPushPath(page02Info, true, LaunchMode::STANDARD);

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    ASSERT_EQ(navPathList.size(), 2);
    EXPECT_EQ(navPathList[0].first, PAGE01);
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(navPathList[0].second), nullptr);
    EXPECT_FALSE(navigationStack->NeedBuildNewInstance(1));
    EXPECT_EQ(navPathList[1].first, PAGE02);
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(navPathList[1].second), nullptr);
    EXPECT_FALSE(navigationStack->NeedBuildNewInstance(1));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList004
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = false
 *           Branch: if (isPageForceSet) = true
 *           Branch: if (index == pathListSize - 1 && addByNavRouter_) = false
 *           Condition: index == pathListSize - 1 = false
 *           Condition: index == pathListSize - 1 = true, addByNavRouter_ = false
 *           Branch: else if (isCurForceSetList) = true
 *           Branch: if (uiNode) = true
 *           Branch: if (navDestinationGroupNode && navDestinationGroupNode->GetCanReused()) = false
 *           Condition: navDestinationGroupNode = true, navDestinationGroupNode->GetCanReused() = false
 *           Condition: navDestinationGroupNode = true, navDestinationGroupNode->GetCanReused() = true
 *           Branch: if (navDestinationGroupNode && navDestinationGroupNode->GetCanReused()) = true
 *           Branch: if (uiNode) = false
 *           Branch: if (isPageForceSet) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList004, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    auto navDestination01Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE01, navDestination01Node);
    navigationStack->mockPathArray_[0]->isForceSet = true;
    navigationStack->mockPathArray_[0]->SetNavDestinationId("-1");
    auto navDestination02Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE02, navDestination02Node);
    navDestination02Node->canReused_ = false;
    navigationStack->mockPathArray_[1]->isForceSet = true;
    navigationStack->mockPathArray_[1]->SetNavDestinationId("2");
    navigationStack->preNavPathList_.push_back(std::make_pair(PAGE02, navDestination02Node));
    auto navDestination02Pattern = navDestination02Node->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestination02Pattern, nullptr);
    navDestination02Pattern->navDestinationId_ = 2;
    auto navDestination03Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add(PAGE03, navDestination03Node);
    navigationStack->mockPathArray_[2]->isForceSet = true;
    navigationStack->mockPathArray_[2]->SetNavDestinationId("3");
    navigationStack->preNavPathList_.push_back(std::make_pair(PAGE03, navDestination03Node));
    auto navDestination03Pattern = navDestination03Node->GetPattern<NavDestinationPattern>();
    ASSERT_NE(navDestination03Pattern, nullptr);
    navDestination03Pattern->navDestinationId_ = 3;

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    ASSERT_EQ(navPathList.size(), 3);
    EXPECT_EQ(navPathList[0].first, PAGE01);
    EXPECT_EQ(navPathList[0].second, nullptr);
    EXPECT_EQ(navPathList[1].first, PAGE02);
    EXPECT_EQ(navPathList[1].second, nullptr);
    EXPECT_TRUE(navigationStack->GetIsForceSet(1));
    EXPECT_EQ(navPathList[2].first, PAGE03);
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(navPathList[2].second), nullptr);
    EXPECT_FALSE(navigationStack->GetIsForceSet(2));
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList005
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = false
 *           Branch: if (isPageForceSet) = false
 *           Branch: if (index == pathListSize - 1 && addByNavRouter_) = false
 *           Condition: index == pathListSize - 1 = false
 *           Branch: if (index == pathListSize - 1 && addByNavRouter_) = true
 *           Branch: if (uiNode) = false
 *           Branch: if (uiNode) = true
 *           Branch: if (navDestination) = false
 *           Branch: if (navDestination) = true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList005, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->addByNavRouter_ = true;
    auto text01Node = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    navigationStack->Add(PAGE01, nullptr);
    navigationStack->cacheNodes_.emplace_back(std::make_pair(PAGE01, text01Node));
    auto navDestination02Node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination02Node->SetInCurrentStack(false);
    navigationStack->Add(PAGE02, nullptr);
    navigationStack->cacheNodes_.emplace_back(std::make_pair(PAGE02, navDestination02Node));

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    ASSERT_EQ(navPathList.size(), 2);
    EXPECT_EQ(navPathList[0].first, PAGE01);
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(navPathList[0].second), nullptr);
    EXPECT_EQ(navPathList[1].first, PAGE02);
    auto navDestination02NodeInList = AceType::DynamicCast<NavDestinationGroupNode>(navPathList[1].second);
    EXPECT_NE(navDestination02NodeInList, nullptr);
    EXPECT_TRUE(navDestination02NodeInList->GetInCurrentStack());
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList006
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = false
 *           Branch: if (isPageForceSet) = false
 *           Branch: if (uiNode) = false
 *           Branch: if (uiNode) = false
 *           Branch: if (isPageForceSet) = false
 *           Branch: if (!GenerateUINodeByIndex(arrayIndex, uiNode)) = true
 *           Branch: if (navigationStack_->CheckIsReplacedDestination()) = true
 *           Branch: if (navigationStack_->CheckIsReplacedDestination()) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList006, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    navigationPattern->addByNavRouter_ = true;
    navigationStack->Add(PAGE01, nullptr);
    navigationStack->mockPathArray_[0]->isReplaced = true;
    navigationStack->Add(PAGE02, nullptr);

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    EXPECT_EQ(navPathList.size(), 0);
    EXPECT_FALSE(navigationStack->mockPathArray_[0]->isReplaced);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}

/**
 * @tc.name: UpdateNavPathList007
 * @tc.desc: Branch: if (navigationStack_->IsFromRecovery(arrayIndex)) = false
 *           Branch: if (navigationStack_->NeedBuildNewInstance(arrayIndex)) = false
 *           Branch: if (isPageForceSet) = false
 *           Branch: if (uiNode) = false
 *           Branch: if (uiNode) = false
 *           Branch: if (isPageForceSet) = false
 *           Branch: if (!GenerateUINodeByIndex(arrayIndex, uiNode)) = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestThreeNg, UpdateNavPathList007, TestSize.Level1)
{
    NavigationPatternTestThreeNg::SetUpTestSuite();
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(V2::NAVIGATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationPattern->SetNavigationStack(navigationStack);
    auto navigationRoute = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(navigationRoute);
    navigationPattern->addByNavRouter_ = true;
    navigationStack->Add(PAGE01, nullptr);
    navigationStack->mockPathArray_[0]->isReplaced = true;

    navigationPattern->UpdateNavPathList();
    auto navPathList = navigationStack->GetAllNavDestinationNodes();
    ASSERT_EQ(navPathList.size(), 1);
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(navPathList[0].second), nullptr);
    NavigationPatternTestThreeNg::TearDownTestSuite();
}
} // namespace OHOS::Ace::NG