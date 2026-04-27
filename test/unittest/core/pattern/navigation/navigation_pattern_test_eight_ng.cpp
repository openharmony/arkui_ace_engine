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
#include <unordered_map>
#include <unordered_set>

#include "gtest/gtest.h"
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#define protected public
#define private public
#include "core/common/multi_thread_build_manager.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/manager/force_split/force_split_manager.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_drag_bar_pattern.h"
#include "core/common/page_viewport_config.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
#include "core/components_ng/pattern/stage/page_node.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/frameworks/base/thread/mock_task_executor.h"
#include "test/mock/frameworks/core/common/mock_container.h"
#include "test/mock/frameworks/core/common/mock_theme_manager.h"
#include "test/mock/frameworks/core/pipeline/mock_pipeline_context.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_WINDOW_WIDTH = 100;
constexpr int32_t TEST_WINDOW_HEIGHT = 100;
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
const std::string PAGE03 = "Page03";

class TestNavigationStack : public MockNavigationStack {
public:
    bool createHomeResult_ = false;
    RefPtr<UINode> homeNode_;
    bool createRelatedResult_ = false;
    RefPtr<UINode> relatedNode_;

    bool CreateHomeDestination(const WeakPtr<UINode>& customNode, RefPtr<UINode>& node) override
    {
        node = homeNode_;
        return createHomeResult_;
    }

    bool CreateRelatedDestination(
        const std::string& name, const WeakPtr<UINode>& customNode, RefPtr<UINode>& node) override
    {
        node = relatedNode_;
        return createRelatedResult_;
    }
};

class MockPageViewportConfigForTest : public PageViewportConfig {
    DECLARE_ACE_TYPE(MockPageViewportConfigForTest, PageViewportConfig);
public:
    explicit MockPageViewportConfigForTest(DisplayOrientation orientation) : orientation_(orientation) {}
    ~MockPageViewportConfigForTest() override = default;

    RefPtr<PageViewportConfig> Clone() const override
    {
        return AceType::MakeRefPtr<MockPageViewportConfigForTest>(orientation_);
    }

    DisplayOrientation GetOrientation() const override
    {
        return orientation_;
    }

private:
    DisplayOrientation orientation_ = DisplayOrientation::PORTRAIT;
};

struct NavigationTestContext {
    RefPtr<NavigationGroupNode> navNode;
    RefPtr<NavigationPattern> pattern;
    RefPtr<TestNavigationStack> stack;
};

RefPtr<NavDestinationGroupNode> CreateNavDestinationNode(const std::string& name, int32_t index,
    NavDestinationMode mode = NavDestinationMode::STANDARD,
    NavDestinationType type = NavDestinationType::DETAIL)
{
    auto node = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto pattern = node->GetPattern<NavDestinationPattern>();
    if (pattern) {
        pattern->SetName(name);
    }
    node->index_ = index;
    node->SetNavDestinationMode(mode);
    node->SetNavDestinationType(type);
    return node;
}

NavigationTestContext CreateNavigationTestContext(bool forceSplitSupported = false)
{
    auto pipeline = MockPipelineContext::GetCurrent();
    CHECK_NULL_RETURN(pipeline, {});
    auto manager = pipeline->GetForceSplitManager();
    CHECK_NULL_RETURN(manager, {});
    manager->SetIsRouter(false);
    manager->SetForceSplitSupported(forceSplitSupported);
    manager->SetBehaviorMode(ForceSplitBehaviorMode::NAVIGATION);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {});
    manager->SetTransPages(std::unordered_set<std::string> {});
    manager->SetForceSplitEnable(false, ForceSplitMode::NOT_SPLIT);

    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto rawNavNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    RefPtr<NavigationGroupNode> navNode = rawNavNode ? AceType::Claim(rawNavNode) : nullptr;
    auto pattern = navNode ? navNode->GetPattern<NavigationPattern>() : nullptr;
    auto stack = AceType::MakeRefPtr<TestNavigationStack>();
    if (pattern) {
        pattern->SetNavigationStack(stack);
    }
    return { navNode, pattern, stack };
}

void AddDestinationToStack(const NavigationTestContext& context, const std::string& name,
    const RefPtr<NavDestinationGroupNode>& destination)
{
    CHECK_NULL_VOID(context.stack);
    context.stack->Add(name, destination);
}

void MountDestinationToNavContent(const NavigationTestContext& context, const RefPtr<NavDestinationGroupNode>& destination)
{
    CHECK_NULL_VOID(context.navNode);
    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    CHECK_NULL_VOID(navContentNode);
    navContentNode->AddChild(destination);
}

void ConfigurePageLevelConfig(const RefPtr<NavigationPattern>& navigationPattern,
    const RefPtr<NavigationGroupNode>& navigationNode, const RefPtr<FrameNode>& pageNode, bool enabled)
{
    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion(static_cast<int32_t>(
        enabled ? PlatformVersion::VERSION_NINETEEN : PlatformVersion::VERSION_TWELVE));
    if (!enabled) {
        return;
    }

    ASSERT_NE(navigationPattern, nullptr);
    ASSERT_NE(navigationNode, nullptr);
    navigationPattern->isFullPageNavigation_ = true;
    navigationPattern->pageNode_ = pageNode;
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;

    auto mockContainer = MockContainer::Current();
    ASSERT_NE(mockContainer, nullptr);
    mockContainer->SetIsUIExtensionWindow(false);
    EXPECT_CALL(*mockContainer, IsMainWindow()).WillRepeatedly(Return(true));

    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    auto manager = context->GetWindowManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsPcOrPadFreeMultiWindowModeCallback([]() { return false; });
    manager->SetIsFullScreenWindowCallback([]() { return true; });
}

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

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg001
 * @tc.desc: Test GetNavDestinationJsViewName - null uiNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    RefPtr<UINode> uiNode = nullptr;
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(uiNode);
    EXPECT_TRUE(jsViewNames.empty());
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg002
 * @tc.desc: Test GetNavDestinationJsViewName - NavDestination node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(navDestination);
    EXPECT_TRUE(jsViewNames.empty());
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg003
 * @tc.desc: Test GetNavDestinationJsViewName - CustomNode with empty name
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto customNode = CustomNode::CreateCustomNode(100, "testKey");
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(customNode);
    EXPECT_TRUE(jsViewNames.empty());
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg004
 * @tc.desc: Test GetNavDestinationJsViewName - CustomNode with name
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto customNode = CustomNode::CreateCustomNode(100, "testKey");
    customNode->SetJSViewName("MyCustomView");
    
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(customNode);
    EXPECT_EQ(jsViewNames, "");
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg005
 * @tc.desc: Test GetNavDestinationJsViewName - nested CustomNode to NavDestination
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg005, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto customNode = CustomNode::CreateCustomNode(101, "testKey");
    customNode->SetJSViewName("MyCustomView");
    customNode->AddChild(navDestination);
    
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(customNode);
    EXPECT_EQ(jsViewNames, "MyCustomView");
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg006
 * @tc.desc: Test GetNavDestinationJsViewName - multiple CustomNodes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg006, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto customNode1 = CustomNode::CreateCustomNode(101, "testKey1");
    customNode1->SetJSViewName("CustomView1");
    auto customNode2 = CustomNode::CreateCustomNode(102, "testKey2");
    customNode2->SetJSViewName("CustomView2");
    customNode1->AddChild(customNode2);
    customNode2->AddChild(navDestination);
    
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(customNode1);
    EXPECT_EQ(jsViewNames, "CustomView1/CustomView2");
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg007
 * @tc.desc: Test GetNavDestinationJsViewName - CustomNode with empty name in chain
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg007, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto customNode1 = CustomNode::CreateCustomNode(101, "testKey1");
    customNode1->SetJSViewName("CustomView1");
    auto customNode2 = CustomNode::CreateCustomNode(102, "testKey2");
    customNode2->SetJSViewName("");
    customNode1->AddChild(customNode2);
    customNode2->AddChild(navDestination);
    
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(customNode1);
    EXPECT_EQ(jsViewNames, "CustomView1");
}

/**
 * @tc.name: GetNavDestinationJsViewNameTestNg008
 * @tc.desc: Test GetNavDestinationJsViewName - non-CustomNode UINode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, GetNavDestinationJsViewNameTestNg008, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto stackNode = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG, 100, AceType::MakeRefPtr<StackPattern>());
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    stackNode->AddChild(navDestination);
    
    auto jsViewNames = NavigationPattern::GetNavDestinationJsViewName(stackNode);
    EXPECT_TRUE(jsViewNames.empty());
}

/**
 * @tc.name: CreateHomeAndRelatedDestinationTest001
 * @tc.desc: Test CreateHomeDestination and CreateRelatedDestination branch combinations
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, CreateHomeAndRelatedDestinationTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    RefPtr<UINode> customNode;
    RefPtr<NavDestinationGroupNode> homeDest;
    context.pattern->navigationStack_ = nullptr;
    EXPECT_FALSE(context.pattern->CreateHomeDestination(customNode, homeDest));

    context.pattern->SetNavigationStack(context.stack);
    context.stack->createHomeResult_ = false;
    EXPECT_FALSE(context.pattern->CreateHomeDestination(customNode, homeDest));

    context.stack->createHomeResult_ = true;
    context.stack->homeNode_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(context.pattern->CreateHomeDestination(customNode, homeDest));

    auto homeNode = CreateNavDestinationNode("Home", 0, NavDestinationMode::STANDARD, NavDestinationType::DETAIL);
    context.stack->homeNode_ = homeNode;
    EXPECT_TRUE(context.pattern->CreateHomeDestination(customNode, homeDest));
    ASSERT_NE(homeDest, nullptr);
    EXPECT_EQ(customNode, homeNode);
    EXPECT_TRUE(homeDest->isHomeDestination_);

    RefPtr<NavDestinationGroupNode> relatedDest;
    context.pattern->navigationStack_ = nullptr;
    EXPECT_FALSE(context.pattern->CreateRelatedDestination(PAGE01, customNode, relatedDest));

    context.pattern->SetNavigationStack(context.stack);
    context.pattern->parentNode_ = WeakPtr<UINode>();
    EXPECT_FALSE(context.pattern->CreateRelatedDestination(PAGE01, customNode, relatedDest));

    auto parentCustomNode = CustomNode::CreateCustomNode(ElementRegister::GetInstance()->MakeUniqueId(), "parent");
    context.pattern->parentNode_ = WeakPtr<UINode>(parentCustomNode);
    context.stack->createRelatedResult_ = false;
    EXPECT_FALSE(context.pattern->CreateRelatedDestination(PAGE01, customNode, relatedDest));

    context.stack->createRelatedResult_ = true;
    context.stack->relatedNode_ = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(context.pattern->CreateRelatedDestination(PAGE01, customNode, relatedDest));

    auto relatedNode = CreateNavDestinationNode("Related", 1, NavDestinationMode::STANDARD, NavDestinationType::DETAIL);
    context.stack->relatedNode_ = relatedNode;
    EXPECT_TRUE(context.pattern->CreateRelatedDestination(PAGE01, customNode, relatedDest));
    ASSERT_NE(relatedDest, nullptr);
    EXPECT_EQ(customNode, relatedNode);
    EXPECT_EQ(relatedDest->GetNavDestinationType(), NavDestinationType::RELATED);
}

/**
 * @tc.name: ForceSplitDisplayStateAndDiffTest001
 * @tc.desc: Test force split display state builders and lifecycle diff ordering
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ForceSplitDisplayStateAndDiffTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = context.navNode->GetContextRefPtr()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {
        { "DetailA", { "DetailB" } }
    });

    auto homeDest = CreateNavDestinationNode("Home", 0);
    auto dialogDest = CreateNavDestinationNode("Dialog", 1, NavDestinationMode::DIALOG);
    auto detailDest = CreateNavDestinationNode("DetailA", 2);
    auto hiddenDest = CreateNavDestinationNode("Hidden", 3);
    auto relatedDest = CreateNavDestinationNode("Related", 4);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE02, dialogDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, dialogDest);
    MountDestinationToNavContent(context, detailDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->hideNodes_.emplace_back(hiddenDest, true);
    context.navNode->lastStandardIndex_ = 2;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(homeDest), WeakPtr<NavDestinationGroupNode>(dialogDest) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(detailDest) };

    homeDest->GetPattern<NavDestinationPattern>()->SetIsOnShow(true);
    homeDest->GetPattern<NavDestinationPattern>()->SetIsActive(false);
    dialogDest->GetPattern<NavDestinationPattern>()->SetIsOnShow(false);
    dialogDest->GetPattern<NavDestinationPattern>()->SetIsActive(false);
    detailDest->GetPattern<NavDestinationPattern>()->SetIsOnShow(false);
    detailDest->GetPattern<NavDestinationPattern>()->SetIsActive(false);
    hiddenDest->GetPattern<NavDestinationPattern>()->SetIsOnShow(true);
    hiddenDest->GetPattern<NavDestinationPattern>()->SetIsActive(true);
    relatedDest->GetPattern<NavDestinationPattern>()->SetIsOnShow(true);
    relatedDest->GetPattern<NavDestinationPattern>()->SetIsActive(false);

    std::vector<RefPtr<NavDestinationGroupNode>> candidates;
    context.pattern->CollectForceSplitLifecycleCandidates(candidates, homeDest, detailDest);
    EXPECT_GE(candidates.size(), 3U);

    auto beforeState = context.pattern->CollectForceSplitDisplayStateFromLifecycleFlags(homeDest, detailDest);
    EXPECT_EQ(beforeState.shownPages.size(), 2U);
    EXPECT_EQ(beforeState.activePages.size(), 1U);
    EXPECT_TRUE(beforeState.relatedVisible);
    EXPECT_FALSE(beforeState.relatedActive);

    auto logicalState = context.pattern->BuildForceSplitDisplayStateFromLogicalStacks();
    ASSERT_EQ(logicalState.shownPages.size(), 3U);
    ASSERT_EQ(logicalState.activePages.size(), 2U);
    EXPECT_EQ(logicalState.shownPages[0], homeDest);
    EXPECT_EQ(logicalState.shownPages[1], dialogDest);
    EXPECT_EQ(logicalState.shownPages[2], detailDest);
    EXPECT_EQ(logicalState.activePages[0], dialogDest);
    EXPECT_EQ(logicalState.activePages[1], detailDest);
    EXPECT_TRUE(logicalState.relatedVisible);
    EXPECT_TRUE(logicalState.relatedActive);

    context.pattern->isSplitDisplay_ = false;
    auto stackModeState = context.pattern->BuildForceSplitDisplayStateForModeChange();
    ASSERT_EQ(stackModeState.shownPages.size(), 1U);
    EXPECT_EQ(stackModeState.shownPages[0], detailDest);
    context.pattern->isSplitDisplay_ = true;

    NavigationPattern::ForceSplitDisplayState manualBefore;
    manualBefore.shownPages = { detailDest, homeDest };
    manualBefore.activePages = { homeDest };
    manualBefore.relatedVisible = false;
    manualBefore.relatedActive = false;
    NavigationPattern::ForceSplitDisplayState manualAfter;
    manualAfter.shownPages = { homeDest, dialogDest, detailDest };
    manualAfter.activePages = { dialogDest, detailDest };
    manualAfter.relatedVisible = true;
    manualAfter.relatedActive = true;
    auto diff = context.pattern->BuildForceSplitLifecycleDiff(manualBefore, manualAfter);
    ASSERT_EQ(diff.willShowPages.size(), 1U);
    ASSERT_EQ(diff.activePages.size(), 2U);
    ASSERT_EQ(diff.inactivePages.size(), 1U);
    EXPECT_EQ(diff.willShowPages[0], dialogDest);
    EXPECT_EQ(diff.activePages[0], dialogDest);
    EXPECT_EQ(diff.activePages[1], detailDest);
    EXPECT_EQ(diff.inactivePages[0], homeDest);
    EXPECT_TRUE(diff.relatedWillShow);
    EXPECT_TRUE(diff.relatedActive);
}

/**
 * @tc.name: ForceSplitLifecycleFireTest001
 * @tc.desc: Test new force split lifecycle fire helpers update visible and active flags
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ForceSplitLifecycleFireTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = context.navNode->GetContextRefPtr()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {
        { "A", { "B" } }
    });

    auto nodeA = CreateNavDestinationNode("A", 0);
    auto nodeB = CreateNavDestinationNode("B", 1);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    AddDestinationToStack(context, PAGE01, nodeA);
    AddDestinationToStack(context, PAGE02, nodeB);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = -1;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(nodeA) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(nodeB) };

    auto patternA = nodeA->GetPattern<NavDestinationPattern>();
    auto patternB = nodeB->GetPattern<NavDestinationPattern>();
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(patternA, nullptr);
    ASSERT_NE(patternB, nullptr);
    ASSERT_NE(relatedPattern, nullptr);

    NavigationPattern::ForceSplitLifecycleDiff showDiff;
    showDiff.willShowPages = { nodeA };
    showDiff.shownPages = { nodeA };
    showDiff.activePages = { nodeA };
    showDiff.relatedWillShow = true;
    showDiff.relatedShow = true;
    showDiff.relatedActive = true;
    context.pattern->FireForceSplitWillShowLifecycle(showDiff);
    context.pattern->FireForceSplitShowLifecycle(
        showDiff, NavDestVisibilityChangeReason::TRANSITION, NavDestinationActiveReason::TRANSITION);
    EXPECT_TRUE(patternA->GetIsOnShow());
    EXPECT_TRUE(patternA->IsActive());
    EXPECT_TRUE(relatedPattern->GetIsOnShow());
    EXPECT_TRUE(relatedPattern->IsActive());

    NavigationPattern::ForceSplitLifecycleDiff hideDiff;
    hideDiff.willHidePages = { nodeA };
    hideDiff.hiddenPages = { nodeA };
    hideDiff.inactivePages = { nodeA };
    hideDiff.relatedWillHide = true;
    hideDiff.relatedHide = true;
    hideDiff.relatedInactive = true;
    context.pattern->FireForceSplitWillHideLifecycle(hideDiff);
    context.pattern->FireForceSplitHideLifecycle(
        hideDiff, NavDestVisibilityChangeReason::TRANSITION, NavDestinationActiveReason::TRANSITION);
    EXPECT_FALSE(patternA->GetIsOnShow());
    EXPECT_FALSE(patternA->IsActive());
    EXPECT_FALSE(relatedPattern->GetIsOnShow());
    EXPECT_FALSE(relatedPattern->IsActive());

    patternA->SetIsOnShow(false);
    patternB->SetIsOnShow(false);
    relatedPattern->SetIsOnShow(false);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_SHOW, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(patternA->GetIsOnShow());
    EXPECT_TRUE(patternB->GetIsOnShow());
    EXPECT_TRUE(relatedPattern->GetIsOnShow());

    patternA->SetIsOnShow(false);
    patternA->SetIsActive(false);
    patternB->SetIsOnShow(false);
    patternB->SetIsActive(false);
    relatedPattern->SetIsOnShow(false);
    relatedPattern->SetIsActive(false);
    context.pattern->FireForceSplitLifecycleForModeChange();
    EXPECT_TRUE(patternB->GetIsOnShow());
    EXPECT_TRUE(patternB->IsActive());
}

/**
 * @tc.name: HandleForceSplitTransitionWithoutAnimationTest001
 * @tc.desc: Test no-animation force split transition handles push and pop scenes
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, HandleForceSplitTransitionWithoutAnimationTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto preTop = CreateNavDestinationNode("PreTop", 0);
    auto newTop = CreateNavDestinationNode("NewTop", 1);
    auto pushExitNode = CreateNavDestinationNode("PushExit", -1);
    navContentNode->AddChild(preTop);
    navContentNode->AddChild(newTop);

    context.pattern->isSecondaryPushToPrimaryScene_ = true;
    context.pattern->splitPushExitNode_ =
        WeakPtr<NavDestinationNodeBase>(AceType::DynamicCast<NavDestinationNodeBase>(pushExitNode));
    EXPECT_TRUE(context.pattern->HandleForceSplitTransitionWithoutAnimation(context.navNode, preTop, newTop));
    EXPECT_FALSE(context.pattern->isSecondaryPushToPrimaryScene_);
    EXPECT_EQ(pushExitNode->GetTransitionType(), PageTransitionType::EXIT_PUSH);
    EXPECT_EQ(preTop->GetTransitionType(), PageTransitionType::MOVE_PUSH);
    EXPECT_EQ(newTop->GetTransitionType(), PageTransitionType::ENTER_PUSH);

    auto popEnterNode = CreateNavDestinationNode("PopEnter", -1);
    navContentNode->AddChild(preTop);
    context.pattern->isPrimaryPopToSecondaryScene_ = true;
    context.pattern->splitPopEnterNode_ =
        WeakPtr<NavDestinationNodeBase>(AceType::DynamicCast<NavDestinationNodeBase>(popEnterNode));
    EXPECT_TRUE(context.pattern->HandleForceSplitTransitionWithoutAnimation(context.navNode, preTop, newTop));
    EXPECT_FALSE(context.pattern->isPrimaryPopToSecondaryScene_);
    EXPECT_EQ(popEnterNode->GetTransitionType(), PageTransitionType::ENTER_POP);
    EXPECT_EQ(newTop->GetTransitionType(), PageTransitionType::ENTER_POP);
    EXPECT_EQ(preTop->GetTransitionType(), PageTransitionType::EXIT_POP);

    EXPECT_FALSE(context.pattern->HandleForceSplitTransitionWithoutAnimation(context.navNode, nullptr, nullptr));
}

/**
 * @tc.name: OnCustomAnimationFinishAndStartTransitionTest001
 * @tc.desc: Test OnCustomAnimationFinish and StartTransition key branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, OnCustomAnimationFinishAndStartTransitionTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = context.navNode->GetContextRefPtr()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {
        { "Pre", { "Cur" } }
    });

    auto preTop = CreateNavDestinationNode("Pre", 0);
    auto curTop = CreateNavDestinationNode("Cur", 1);
    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    navContentNode->AddChild(preTop);
    navContentNode->AddChild(curTop);
    AddDestinationToStack(context, PAGE01, preTop);
    AddDestinationToStack(context, PAGE02, curTop);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(preTop);
    context.pattern->prePrimaryNodes_ = { WeakPtr<NavDestinationGroupNode>(preTop) };
    context.pattern->primaryNodes_ = context.pattern->prePrimaryNodes_;
    context.pattern->StartTransition(preTop, curTop, true, false, true);
    EXPECT_TRUE(context.pattern->prePrimaryNodes_.empty());

    context.stack->UpdateReplaceValue(1);
    preTop->SetIsOnAnimation(true);
    curTop->SetIsOnAnimation(true);
    context.pattern->OnCustomAnimationFinish(preTop, curTop, false);
    EXPECT_FALSE(preTop->IsOnAnimation());
    EXPECT_FALSE(curTop->IsOnAnimation());
    EXPECT_EQ(context.stack->GetReplaceValue(), 0);

    preTop->SetTransitionType(PageTransitionType::EXIT_POP);
    curTop->SetTransitionType(PageTransitionType::ENTER_POP);
    navContentNode->AddChild(preTop);
    context.pattern->OnCustomAnimationFinish(preTop, curTop, true);
    EXPECT_EQ(preTop->GetParent(), nullptr);
}

/**
 * @tc.name: CollectActiveNodesAndMoveToPrimaryTest001
 * @tc.desc: Test CollectActiveNodes and IsTransitionShouldMovePageToPrimary branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, CollectActiveNodesAndMoveToPrimaryTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = context.navNode->GetContextRefPtr()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {
        { "From", { "To" } }
    });

    auto primaryTop = CreateNavDestinationNode("Home", 0);
    auto secondaryTop = CreateNavDestinationNode("To", 1);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    AddDestinationToStack(context, PAGE01, secondaryTop);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(primaryTop) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryTop) };

    std::vector<RefPtr<NavDestinationGroupNode>> activeNodes;
    context.pattern->CollectActiveNodes(activeNodes);
    ASSERT_EQ(activeNodes.size(), 2U);
    EXPECT_EQ(activeNodes[0], secondaryTop);
    EXPECT_EQ(activeNodes[1], primaryTop);

    auto fromDialog = CreateNavDestinationNode("From", 3, NavDestinationMode::DIALOG);
    auto toDialog = CreateNavDestinationNode("To", 4, NavDestinationMode::STANDARD);
    manager->SetBehaviorMode(ForceSplitBehaviorMode::DISPLACE);
    EXPECT_FALSE(context.pattern->IsTransitionShouldMovePageToPrimary(fromDialog, toDialog));

    auto fromDetail = CreateNavDestinationNode("From", 5);
    auto toDetail = CreateNavDestinationNode("To", 6);
    EXPECT_TRUE(context.pattern->IsTransitionShouldMovePageToPrimary(fromDetail, toDetail));
}

/**
 * @tc.name: SplitDisplayReconfigureAndSyncTest001
 * @tc.desc: Test split-display reconfigure and stack-sync helper branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, SplitDisplayReconfigureAndSyncTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = context.navNode->GetContextRefPtr()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetPagePairs(std::unordered_map<std::string, std::unordered_set<std::string>> {
        { "DetailA", { "DetailB" } }
    });

    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(context.navNode->GetNavBarNode());
    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetPrimaryContentNode());
    ASSERT_NE(navBarNode, nullptr);
    ASSERT_NE(navContentNode, nullptr);
    ASSERT_NE(primaryContentNode, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    auto detailA = CreateNavDestinationNode("DetailA", 1);
    auto detailB = CreateNavDestinationNode("DetailB", 2);
    auto relatedDest = CreateNavDestinationNode("Related", 3);
    detailA->SetNavDestinationType(NavDestinationType::DETAIL);
    detailB->SetNavDestinationType(NavDestinationType::DETAIL);
    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE02, detailA);
    AddDestinationToStack(context, PAGE03, detailB);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailA);
    MountDestinationToNavContent(context, detailB);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 2;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(homeDest);
    context.pattern->navBarIsHome_ = false;
    context.pattern->AdjustNodeForSplitDisplayReconfigure();
    ASSERT_EQ(context.pattern->primaryNodes_.size(), 1U);
    ASSERT_EQ(context.pattern->secondaryNodes_.size(), 2U);
    EXPECT_EQ(context.pattern->primaryNodes_[0].Upgrade(), homeDest);

    context.pattern->HandleSplitDisplaySyncWithoutHome(navContentNode);
    EXPECT_EQ(context.pattern->primaryNodes_.size(), 3U);
    EXPECT_TRUE(context.pattern->secondaryNodes_.empty());

    context.pattern->forceSplitSuccess_ = false;
    context.pattern->AdjustNodeForStackDisplayReconfigure();
    EXPECT_TRUE(context.pattern->primaryNodes_.empty());
    EXPECT_EQ(context.pattern->secondaryNodes_.size(), 3U);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(homeDest);
    context.pattern->prePrimaryNodes_ = { WeakPtr<NavDestinationGroupNode>(homeDest) };
    context.pattern->SetTouchedSecondaryColumnDestination(detailA);
    auto scenario = context.pattern->BuildSplitDisplaySyncScenario(
        std::make_optional(std::make_pair(PAGE02, AceType::DynamicCast<UINode>(detailA))),
        std::make_optional(std::make_pair(PAGE03, AceType::DynamicCast<UINode>(detailB))));
    EXPECT_TRUE(scenario.isSecondaryPushToPrimaryScene);

    context.pattern->RebuildSplitDisplayNodes(navBarNode, navContentNode, primaryContentNode, scenario);
    EXPECT_TRUE(context.pattern->isSecondaryPushToPrimaryScene_);
    EXPECT_EQ(context.pattern->splitPushMoveNode_.Upgrade(), detailA);
    EXPECT_EQ(context.pattern->splitPushEnterNode_.Upgrade(), detailB);

    context.pattern->AdjustNodeForStackSyncWhenSplitDisplay(
        std::make_optional(std::make_pair(PAGE02, AceType::DynamicCast<UINode>(detailA))),
        std::make_optional(std::make_pair(PAGE03, AceType::DynamicCast<UINode>(detailB))));
    EXPECT_FALSE(context.pattern->primaryNodes_.empty());

    context.pattern->forceSplitSuccess_ = false;
    context.pattern->AdjustNodeForStackSyncWhenStackDisplay();
    EXPECT_EQ(context.pattern->secondaryNodes_.size(), 3U);
}

/**
 * @tc.name: PageViewportAndSystemBarTest001
 * @tc.desc: Test UpdatePageViewportConfigIfNeeded and ShowOrRestoreSystemBarIfNeeded core branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, PageViewportAndSystemBarTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto pageNode = FrameNode::CreateFrameNode(V2::PAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    ConfigurePageLevelConfig(context.pattern, context.navNode, pageNode, true);

    auto preNode = CreateNavDestinationNode("PrePage", 0);
    auto curNode = CreateNavDestinationNode("CurPage", 1);
    preNode->SetOrientation(Orientation::VERTICAL);
    curNode->SetOrientation(Orientation::HORIZONTAL);
    context.pattern->preVisibleNodes_ = {
        WeakPtr<NavDestinationNodeBase>(AceType::DynamicCast<NavDestinationNodeBase>(preNode))
    };
    AddDestinationToStack(context, PAGE01, curNode);

    auto container = Container::Current();
    ASSERT_NE(container, nullptr);
    auto windowManager = context.navNode->GetContextRefPtr()->GetWindowManager();
    ASSERT_NE(windowManager, nullptr);
    windowManager->SetGetPageViewportConfigCallback(
        [](const PageViewportConfigParams& currentParams, RefPtr<PageViewportConfig>& currentConfig,
            const PageViewportConfigParams& targetParams, RefPtr<PageViewportConfig>& targetConfig) {
            currentConfig = AceType::MakeRefPtr<MockPageViewportConfigForTest>(DisplayOrientation::PORTRAIT);
            targetConfig = AceType::MakeRefPtr<MockPageViewportConfigForTest>(DisplayOrientation::LANDSCAPE);
            return true;
        });
    windowManager->SetWindowSetSystemBarEnabledCallback(
        [](SystemBarType type, std::optional<bool> enabled, std::optional<bool> animated) { return true; });

    context.pattern->UpdatePageViewportConfigIfNeeded(preNode, curNode);
    EXPECT_TRUE(context.pattern->enableLockOrientation_);
    EXPECT_NE(curNode->GetPageViewportConfig(), nullptr);

    curNode->statusBarConfig_ = std::make_optional(std::make_pair(true, true));
    curNode->navigationIndicatorConfig_ = std::make_optional(true);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->ShowOrRestoreSystemBarIfNeeded();
    EXPECT_NE(curNode->GetPageViewportConfig(), nullptr);
}

/**
 * @tc.name: ForceSplitAdjustConstraintTypeTest001
 * @tc.desc: Test UpdateAdjustConstraintTypeForForceSplitAnimation branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ForceSplitAdjustConstraintTypeTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.pattern, nullptr);

    auto moveNode = CreateNavDestinationNode("Move", 0);
    ASSERT_NE(moveNode, nullptr);
    auto moveNodeBase = AceType::DynamicCast<NavDestinationNodeBase>(moveNode);
    ASSERT_NE(moveNodeBase, nullptr);

    context.pattern->forceSplitSuccess_ = false;
    context.pattern->isSecondaryPushToPrimaryScene_ = true;
    context.pattern->splitPushMoveNode_ = WeakPtr<NavDestinationNodeBase>(moveNodeBase);
    context.pattern->UpdateAdjustConstraintTypeForForceSplitAnimation(true);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->UpdateAdjustConstraintTypeForForceSplitAnimation(false);

    context.pattern->UpdateAdjustConstraintTypeForForceSplitAnimation(true);

    context.pattern->isSecondaryPushToPrimaryScene_ = false;
    context.pattern->isPrimaryPopToSecondaryScene_ = true;
    context.pattern->splitPopMoveNode_ = WeakPtr<NavDestinationNodeBase>(moveNodeBase);
    context.pattern->UpdateAdjustConstraintTypeForForceSplitAnimation(true);
}

/**
 * @tc.name: UpdateSplitDisplayVisibilityTest001
 * @tc.desc: Test UpdateSplitDisplayVisibility structure visibility branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateSplitDisplayVisibilityTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto navBarNode = AceType::DynamicCast<NavDestinationNodeBase>(context.navNode->GetNavBarNode());
    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    auto primaryContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetPrimaryContentNode());
    ASSERT_NE(navBarNode, nullptr);
    ASSERT_NE(navContentNode, nullptr);
    ASSERT_NE(primaryContentNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    auto navContentProperty = navContentNode->GetLayoutProperty();
    auto primaryProperty = primaryContentNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    ASSERT_NE(navContentProperty, nullptr);
    ASSERT_NE(primaryProperty, nullptr);

    auto navProperty = context.navNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navProperty, nullptr);
    navProperty->UpdateHideNavBar(false);

    context.pattern->primaryNodes_.clear();
    context.pattern->secondaryNodes_.clear();
    context.pattern->UpdateSplitDisplayVisibility(context.navNode, navBarProperty, navContentProperty, primaryProperty);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(primaryProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    auto primaryStandard = CreateNavDestinationNode("PrimaryStandard", 0);
    auto secondaryDialog = CreateNavDestinationNode("SecondaryDialog", 1, NavDestinationMode::DIALOG);
    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(primaryStandard) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryDialog) };
    context.pattern->isSecondaryPushToPrimaryScene_ = false;
    context.pattern->UpdateSplitDisplayVisibility(context.navNode, navBarProperty, navContentProperty, primaryProperty);
    EXPECT_EQ(navContentProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(primaryProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    auto relatedDest = CreateNavDestinationNode("Related", 2);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.pattern->primaryNodes_.clear();
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryDialog) };
    context.pattern->UpdateSplitDisplayVisibility(context.navNode, navBarProperty, navContentProperty, primaryProperty);
    auto relatedProperty = relatedDest->GetLayoutProperty();
    ASSERT_NE(relatedProperty, nullptr);
    EXPECT_EQ(relatedProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    auto secondaryStandard = CreateNavDestinationNode("SecondaryStandard", 3);
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryDialog),
        WeakPtr<NavDestinationGroupNode>(secondaryStandard) };
    context.pattern->UpdateSplitDisplayVisibility(context.navNode, navBarProperty, navContentProperty, primaryProperty);
    EXPECT_EQ(relatedProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
}

/**
 * @tc.name: UpdateSplitDisplayDestinationVisibilityTest001
 * @tc.desc: Test UpdateSplitDisplayDestinationVisibility shown, hidden and deferred branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateSplitDisplayDestinationVisibilityTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto primaryStandard = CreateNavDestinationNode("PrimaryStandard", 0);
    auto primaryDialog = CreateNavDestinationNode("PrimaryDialog", 1, NavDestinationMode::DIALOG);
    auto secondaryStandard = CreateNavDestinationNode("SecondaryStandard", 2);
    auto secondaryDialog = CreateNavDestinationNode("SecondaryDialog", 3, NavDestinationMode::DIALOG);
    auto staleNode = CreateNavDestinationNode("Stale", 4);
    auto deferredNode = CreateNavDestinationNode("Deferred", 5);
    AddDestinationToStack(context, PAGE01, primaryStandard);
    AddDestinationToStack(context, PAGE02, primaryDialog);
    AddDestinationToStack(context, PAGE03, secondaryStandard);
    AddDestinationToStack(context, "Page04", secondaryDialog);
    AddDestinationToStack(context, "Page05", staleNode);
    AddDestinationToStack(context, "Page06", deferredNode);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(primaryStandard),
        WeakPtr<NavDestinationGroupNode>(primaryDialog) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryStandard),
        WeakPtr<NavDestinationGroupNode>(secondaryDialog) };

    auto staleProperty = staleNode->GetLayoutProperty();
    auto deferredProperty = deferredNode->GetLayoutProperty();
    ASSERT_NE(staleProperty, nullptr);
    ASSERT_NE(deferredProperty, nullptr);
    staleProperty->UpdateVisibility(VisibleType::VISIBLE);
    deferredProperty->UpdateVisibility(VisibleType::VISIBLE);

    context.pattern->UpdateSplitDisplayDestinationVisibility(context.navNode, deferredNode);
    EXPECT_EQ(primaryStandard->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(primaryDialog->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(secondaryStandard->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(secondaryDialog->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(staleProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(deferredProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);

    staleProperty->UpdateVisibility(VisibleType::VISIBLE);
    context.navNode->hideNodes_.emplace_back(staleNode, true);
    context.pattern->UpdateSplitDisplayDestinationVisibility(context.navNode, nullptr);
    EXPECT_EQ(staleProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateDestinationVisibilityForDisplayReconfigureTest001
 * @tc.desc: Test UpdateDestinationVisibilityForDisplayReconfigure split and stack target branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateDestinationVisibilityForDisplayReconfigureTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto primaryStandard = CreateNavDestinationNode("PrimaryStandard", 0);
    auto primaryDialog = CreateNavDestinationNode("PrimaryDialog", 1, NavDestinationMode::DIALOG);
    auto secondaryStandard = CreateNavDestinationNode("SecondaryStandard", 2);
    auto secondaryDialog = CreateNavDestinationNode("SecondaryDialog", 3, NavDestinationMode::DIALOG);
    auto staleNode = CreateNavDestinationNode("Stale", 4);
    AddDestinationToStack(context, PAGE01, primaryStandard);
    AddDestinationToStack(context, PAGE02, primaryDialog);
    AddDestinationToStack(context, PAGE03, secondaryStandard);
    AddDestinationToStack(context, "Page04", secondaryDialog);
    AddDestinationToStack(context, "Page05", staleNode);

    context.pattern->primaryNodes_ = { WeakPtr<NavDestinationGroupNode>(primaryStandard),
        WeakPtr<NavDestinationGroupNode>(primaryDialog) };
    context.pattern->secondaryNodes_ = { WeakPtr<NavDestinationGroupNode>(secondaryStandard),
        WeakPtr<NavDestinationGroupNode>(secondaryDialog) };

    auto primaryStandardProperty = primaryStandard->GetLayoutProperty();
    auto primaryDialogProperty = primaryDialog->GetLayoutProperty();
    auto staleProperty = staleNode->GetLayoutProperty();
    ASSERT_NE(primaryStandardProperty, nullptr);
    ASSERT_NE(primaryDialogProperty, nullptr);
    ASSERT_NE(staleProperty, nullptr);

    context.pattern->UpdateDestinationVisibilityForDisplayReconfigure(context.navNode, true);
    EXPECT_EQ(primaryStandardProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(primaryDialogProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(secondaryStandard->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(secondaryDialog->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(staleProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);

    primaryStandardProperty->UpdateVisibility(VisibleType::VISIBLE);
    primaryDialogProperty->UpdateVisibility(VisibleType::VISIBLE);
    staleProperty->UpdateVisibility(VisibleType::VISIBLE);
    context.navNode->hideNodes_.emplace_back(staleNode, true);
    context.pattern->UpdateDestinationVisibilityForDisplayReconfigure(context.navNode, false);
    EXPECT_EQ(primaryStandardProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(primaryDialogProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(secondaryStandard->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(secondaryDialog->GetLayoutProperty()->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(staleProperty->GetVisibilityValue(VisibleType::INVISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: ForceSplitLifecycleDiffOrderTest001
 * @tc.desc: Test helper ordering branches used by SortDestinationsByPhysicalOrder and SubtractDestinations
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ForceSplitLifecycleDiffOrderTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.pattern, nullptr);

    auto lowIndexNode = CreateNavDestinationNode("Low", 0);
    auto highIndexNode = CreateNavDestinationNode("High", 10);
    auto middleIndexNode = CreateNavDestinationNode("Middle", 5);

    NavigationPattern::ForceSplitDisplayState beforeState;
    beforeState.shownPages = { highIndexNode, lowIndexNode };
    beforeState.activePages = { middleIndexNode, highIndexNode };
    NavigationPattern::ForceSplitDisplayState afterState;
    afterState.shownPages = { middleIndexNode, lowIndexNode };
    afterState.activePages = { lowIndexNode };

    auto diff = context.pattern->BuildForceSplitLifecycleDiff(beforeState, afterState);
    ASSERT_EQ(diff.willShowPages.size(), 1U);
    ASSERT_EQ(diff.willHidePages.size(), 1U);
    ASSERT_EQ(diff.activePages.size(), 1U);
    ASSERT_EQ(diff.inactivePages.size(), 2U);
    EXPECT_EQ(diff.willShowPages[0], middleIndexNode);
    EXPECT_EQ(diff.willHidePages[0], highIndexNode);
    EXPECT_EQ(diff.activePages[0], lowIndexNode);
    EXPECT_EQ(diff.inactivePages[0], highIndexNode);
    EXPECT_EQ(diff.inactivePages[1], middleIndexNode);
}

/**
 * @tc.name: ProcessHideNavBarChangeInForceSplitTest001
 * @tc.desc: Test ProcessHideNavBarChangeInForceSplit early-return branches
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, ProcessHideNavBarChangeInForceSplitTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.pattern, nullptr);

    context.pattern->navBarVisibilityChange_ = false;
    context.pattern->ProcessHideNavBarChangeInForceSplit();

    context.pattern->navBarVisibilityChange_ = true;
    context.pattern->forceSplitSuccess_ = false;
    context.pattern->ProcessHideNavBarChangeInForceSplit();

    auto forceSplitContext = CreateNavigationTestContext(true);
    ASSERT_NE(forceSplitContext.pattern, nullptr);
    forceSplitContext.pattern->navBarVisibilityChange_ = true;
    forceSplitContext.pattern->forceSplitSuccess_ = false;
    forceSplitContext.pattern->ProcessHideNavBarChangeInForceSplit();
}

/**
 * @tc.name: UpdateColorModeForNodesTest001
 * @tc.desc: Test UpdateColorModeForNodes entry branch when config change perform is disabled
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestEightNg, UpdateColorModeForNodesTest001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.pattern, nullptr);

    auto destination = CreateNavDestinationNode("ColorMode", 0);
    AddDestinationToStack(context, PAGE01, destination);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->UpdateColorModeForNodes(std::make_optional(std::make_pair(PAGE01,
        AceType::DynamicCast<UINode>(destination))));
    context.pattern->UpdateColorModeForNodes(std::nullopt);
    SUCCEED();
}
} // namespace OHOS::Ace::NG
