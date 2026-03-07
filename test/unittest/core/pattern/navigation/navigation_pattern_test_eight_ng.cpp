/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_WINDOW_WIDTH = 100;
constexpr int32_t TEST_WINDOW_HEIGHT = 100;
} // namespace

class NavigationPatternTestEightNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

RefPtr<NavigationBarTheme> NavigationPatternTestEightNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestEightNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();

    navigationBarTheme_ = AceType::MakeRefPtr<NavigationBarTheme>();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly([](ThemeType type) -> RefPtr<Theme> {
        if (type == NavigationBarTheme::TypeId()) {
            return navigationBarTheme_;
        } else {
            return nullptr;
        }
    });
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
}

void NavigationPatternTestEightNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestEightNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: OnWindowSizeChanged001
 * @tc.desc: Branch: if (runningTransitionCount_ > 0) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnWindowSizeChanged001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->windowSizeChangedDuringTransition_ = false;
    pattern->runningTransitionCount_ = 1;
    pattern->OnWindowSizeChanged(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT, WindowSizeChangeReason::UNDEFINED);
    EXPECT_TRUE(pattern->windowSizeChangedDuringTransition_);
}

/**
 * @tc.name: OnWindowSizeChanged002
 * @tc.desc: Branch: if (runningTransitionCount_ > 0) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnWindowSizeChanged002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->windowSizeChangedDuringTransition_ = false;
    pattern->runningTransitionCount_ = 0;
    pattern->OnWindowSizeChanged(TEST_WINDOW_WIDTH, TEST_WINDOW_HEIGHT, WindowSizeChangeReason::UNDEFINED);
    EXPECT_FALSE(pattern->windowSizeChangedDuringTransition_);
}

/**
 * @tc.name: onHover
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, onHover, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    navNode->GetGeometryNode()->SetFrameSize(SizeF(1000.0, 1000.0));
    pattern->userSetNavBarWidthFlag_ = false;
    pattern->userSetNavBarRangeFlag_ = true;
    pattern->isInDividerDrag_ = false;

    /*
     *   test 500 < 1000 * 0.8
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(500, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(0.8, DimensionUnit::PERCENT));
    pattern->isDividerDraggable_ = false;
    pattern->OnHover(true);
    EXPECT_TRUE(pattern->isDividerDraggable_);

    /*
     *   test 1000 * 0.5 > 400
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(0.5, DimensionUnit::PERCENT));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(400, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_FALSE(pattern->isDividerDraggable_);

    /*
     *  test 500px > 400px
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(500, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(400, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_FALSE(pattern->isDividerDraggable_);

    /*
     *  test 400px > 500px
     */
    layoutProperty->UpdateMinNavBarWidth(Dimension(400, DimensionUnit::PX));
    layoutProperty->UpdateMaxNavBarWidth(Dimension(500, DimensionUnit::PX));
    pattern->OnHover(true);
    EXPECT_TRUE(pattern->isDividerDraggable_);
}

/**
 * @tc.name: test CheckNeedInitRangeCalculation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, CheckNeedInitRangeCalculation, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();

    pattern->navigationSize_ = SizeF(100, 100);
    auto temp = SizeF(100, 100);
    bool ret = pattern->CheckNeedInitRangeCalculation(temp);
    EXPECT_FALSE(ret);

    auto tepm2 = SizeF(200, 200);
    ret = pattern->CheckNeedInitRangeCalculation(tepm2);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateForceSplitHomeDestVisibility001
 * @tc.desc: Branch: if (forceSplitSuccess_) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateForceSplitHomeDestVisibility001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto property = dest->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    pattern->forceSplitHomeDest_ = WeakPtr(dest);
    pattern->forceSplitSuccess_ = true;
    pattern->UpdateForceSplitHomeDestVisibility();
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateForceSplitHomeDestVisibility002
 * @tc.desc: Branch: if (forceSplitSuccess_) { => false
 *                   if (homeDest->GetIndex() < lastStandardIndex) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateForceSplitHomeDestVisibility002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto property = dest->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    pattern->forceSplitHomeDest_ = WeakPtr(dest);
    pattern->forceSplitSuccess_ = false;
    dest->index_ = 0;
    navNode->lastStandardIndex_ = 1;
    pattern->UpdateForceSplitHomeDestVisibility();
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: UpdateForceSplitHomeDestVisibility003
 * @tc.desc: Branch: if (forceSplitSuccess_) { => false
 *                   if (homeDest->GetIndex() < lastStandardIndex) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateForceSplitHomeDestVisibility003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pattern = navNode->GetPattern<NavigationPattern>();

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);
    auto property = dest->GetLayoutProperty();
    ASSERT_NE(property, nullptr);

    pattern->forceSplitHomeDest_ = WeakPtr(dest);
    pattern->forceSplitSuccess_ = false;
    dest->index_ = 1;
    navNode->lastStandardIndex_ = 0;
    pattern->UpdateForceSplitHomeDestVisibility();
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    // Test with equal values
    dest->index_ = 1;
    navNode->lastStandardIndex_ = 1;
    pattern->UpdateForceSplitHomeDestVisibility();
    EXPECT_EQ(property->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: GetNavigationNodeTest001
 * @tc.desc: Test GetNavigationNode returns navigation frame node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavigationNodeTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navigationNode = pattern->GetNavigationNode();
    EXPECT_EQ(navigationNode, navNode);

    navNode = nullptr;
    navigationNode = nullptr;
    pattern = nullptr;
}

/**
 * @tc.name: GetNavBarNodeTest001
 * @tc.desc: Test GetNavBarNode returns nav bar node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavBarNodeTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navBarNode = pattern->GetNavBarNode();
    EXPECT_EQ(navBarNode, navNode->GetNavBarNode());
}

/**
 * @tc.name: GetNavBarNodeOrHomeDestinationTest001
 * @tc.desc: Test GetNavBarNodeOrHomeDestination returns nav bar or home destination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavBarNodeOrHomeDestinationTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navBarOrHomeDest = pattern->GetNavBarNodeOrHomeDestination();
    EXPECT_EQ(navBarOrHomeDest, navNode->GetNavBarOrHomeDestinationNode());
}

/**
 * @tc.name: GetContentNodeTest001
 * @tc.desc: Test GetContentNode returns content node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetContentNodeTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto contentNode = pattern->GetContentNode();
    EXPECT_EQ(contentNode, navNode->GetContentNode());
}

/**
 * @tc.name: GetDividerNodeTest001
 * @tc.desc: Test GetDividerNode returns divider node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetDividerNodeTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dividerNode = pattern->GetDividerNode();
    EXPECT_EQ(dividerNode, navNode->GetDividerNode());
}

/**
 * @tc.name: GetDragBarNodeTest001
 * @tc.desc: Test GetDragBarNode returns drag bar node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetDragBarNodeTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dragBarNode = pattern->GetDragBarNode();
    EXPECT_EQ(dragBarNode, navNode->GetDragBarNode());
}

/**
 * @tc.name: BeforeSyncGeometryPropertiesTest001
 * @tc.desc: Test BeforeSyncGeometryProperties calls AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, BeforeSyncGeometryPropertiesTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    DirtySwapConfig config;
    pattern->BeforeSyncGeometryProperties(config);
}

/**
 * @tc.name: AddDividerHotZoneRectTest001
 * @tc.desc: Test AddDividerHotZoneRect adds hot zone rect to divider
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, AddDividerHotZoneRectTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dividerNode = navNode->GetDividerNode();
    ASSERT_NE(dividerNode, nullptr);
    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);
    ASSERT_NE(dividerFrameNode, nullptr);
    auto geometryNode = dividerFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    pattern->AddDividerHotZoneRect();

    auto gestureHub = dividerFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto mouseRegion = gestureHub->GetMouseResponseRegion();
    EXPECT_FALSE(mouseRegion.empty());
    auto responseRegion = gestureHub->GetResponseRegion();
    EXPECT_FALSE(responseRegion.empty());
}

/**
 * @tc.name: AddDragBarHotZoneRectTest001
 * @tc.desc: Test AddDragBarHotZoneRect adds hot zone rect to drag bar
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, AddDragBarHotZoneRectTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern->enableDragBar_ = true;
    pattern->OnModifyDone();

    auto dragBarNode = navNode->GetDragBarNode();
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarFrameNode = AceType::DynamicCast<FrameNode>(dragBarNode);
    ASSERT_NE(dragBarFrameNode, nullptr);
    auto geometryNode = dragBarFrameNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    pattern->AddDragBarHotZoneRect();

    auto gestureHub = dragBarFrameNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto responseRegion = gestureHub->GetResponseRegion();
    EXPECT_FALSE(responseRegion.empty());
}

/**
 * @tc.name: NotifyDialogLifecycleTest001
 * @tc.desc: Test NotifyDialogLifecycle notifies dialog lifecycle events
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, NotifyDialogLifecycleTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dest = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(dest, nullptr);

    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test", dest);

    navNode->lastStandardIndex_ = 0;
    pattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_SHOW, true, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_EQ(stack->Size(), 1);

    pattern->NotifyDialogLifecycle(NavDestinationLifecycle::ON_HIDE, true, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_EQ(stack->Size(), 1);

    pattern->NotifyDialogLifecycle(
        NavDestinationLifecycle::ON_WILL_APPEAR, true, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_EQ(stack->Size(), 1);

    pattern->NotifyDialogLifecycle(
        NavDestinationLifecycle::ON_WILL_DISAPPEAR, true, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_EQ(stack->Size(), 1);
}

/**
 * @tc.name: DumpInfoTest001
 * @tc.desc: Test DumpInfo logs navigation stack size
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, DumpInfoTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto stack = pattern->GetNavigationStack();
    ASSERT_NE(stack, nullptr);
    stack->Add("test1", nullptr);
    EXPECT_EQ(stack->Size(), 1);

    pattern->DumpInfo();
    EXPECT_EQ(stack->Size(), 1);
}

/**
 * @tc.name: TriggerCustomAnimationTest001
 * @tc.desc: Test TriggerCustomization triggers custom transition animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, TriggerCustomAnimationTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(newTopNavDestination, nullptr);

    bool result = pattern->TriggerCustomAnimation(preTopNavDestination, newTopNavDestination, false);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnCustomAnimationFinishTest001
 * @tc.desc: Test OnCustomAnimationFinish handles custom animation finish
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnCustomAnimationFinishTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(newTopNavDestination, nullptr);

    pattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, false);
}

/**
 * @tc.name: ExecuteTransitionTest001
 * @tc.desc: Test ExecuteTransition executes navigation transition
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ExecuteTransitionTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto proxy = AceType::MakeRefPtr<NavigationTransitionProxy>();
    pattern->proxyList_.emplace_back(proxy);

    pattern->onTransition_ = [](RefPtr<NavDestinationContext> preInfo, RefPtr<NavDestinationContext> topInfo,
                                 NavigationOperation operation) -> NavigationTransition {
        NavigationTransition transition;
        transition.isValid = false;
        return transition;
    };

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(newTopNavDestination, nullptr);

    auto transition = pattern->ExecuteTransition(preTopNavDestination, newTopNavDestination, false);
    EXPECT_FALSE(transition.isValid);
}

/**
 * @tc.name: OnColorConfigurationUpdateTest001
 * @tc.desc: Test OnColorConfigurationUpdate updates color mode for nodes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnColorConfigurationUpdateTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dividerNode = FrameNode::CreateFrameNode(
        "divider", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    navNode->SetDividerNode(dividerNode);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern->enableDragBar_ = true;
    pattern->OnModifyDone();

    auto dragBarNode = navNode->GetDragBarNode();
    ASSERT_NE(dragBarNode, nullptr);
    auto dragBarFrameNode = AceType::DynamicCast<FrameNode>(dragBarNode);
    ASSERT_NE(dragBarFrameNode, nullptr);
    auto dragBarPattern = dragBarFrameNode->GetPattern<NavigationDragBarPattern>();
    ASSERT_NE(dragBarPattern, nullptr);

    pattern->OnColorConfigurationUpdate();

    auto renderContext = dragBarFrameNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_TRUE(renderContext->HasBackgroundColor());
}

/**
 * @tc.name: UpdateDividerBackgroundColorTest001
 * @tc.desc: Test UpdateDividerBackgroundColor updates divider background color
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateDividerBackgroundColorTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto dividerNode = FrameNode::CreateFrameNode(
        "divider", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<DividerPattern>());
    navNode->SetDividerNode(dividerNode);

    auto renderContext = dividerNode->GetRenderContext();
    ASSERT_NE(renderContext, nullptr);
    EXPECT_FALSE(renderContext->HasBackgroundColor());

    pattern->UpdateDividerBackgroundColor();

    EXPECT_TRUE(renderContext->HasBackgroundColor());
}

/**
 * @tc.name: UpdateToobarFocusColorTest001
 * @tc.desc: Test UpdateToobarFocusColor updates toobar focus color
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateToobarFocusColorTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    navNode->SetNavBarNode(navBarNode);

    auto navBarOrHomeDestNode = navNode->GetNavBarOrHomeDestinationNode();
    ASSERT_NE(navBarOrHomeDestNode, nullptr);

    pattern->UpdateToobarFocusColor();

    EXPECT_NE(navBarOrHomeDestNode, nullptr);
    EXPECT_TRUE(pattern != nullptr);
}

/**
 * @tc.name: OnThemeScopeUpdateTest001
 * @tc.desc: Test OnThemeScopeUpdate handles theme scope update
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnThemeScopeUpdateTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    navNode->SetNavBarNode(navBarNode);

    bool result = pattern->OnThemeScopeUpdate(1);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnThemeScopeUpdateTest002
 * @tc.desc: Test OnThemeScopeUpdate returns false for invalid theme scope
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnThemeScopeUpdateTest002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto navNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navNode, nullptr);
    auto pattern = navNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBarNode, nullptr);
    navNode->SetNavBarNode(navBarNode);

    bool result = pattern->OnThemeScopeUpdate(0);
    EXPECT_FALSE(result);
}

} // namespace OHOS::Ace::NG
