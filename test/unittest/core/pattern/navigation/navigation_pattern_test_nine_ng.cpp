/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/navigation/navigation_manager.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const std::string PAGE01 = "Page01";
const std::string PAGE02 = "Page02";
const std::string PAGE03 = "Page03";
constexpr char FORCESPLIT_DRAG_MASKNODE_TAG[] = "ForceSplitDragMask";

constexpr int32_t FORCESPLIT_DRAG_DIVIDER_ZINDEX_TEST = 4;
constexpr int32_t FORCESPLIT_DRAGBAR_ZINDEX_TEST = 5;
constexpr int32_t FORCESPLIT_DRAGBAR_ITEM_ZINDEX_TEST = 6;
constexpr int32_t SECOND_ZINDEX_VALUE_TEST = 2;
constexpr int32_t ZINDEX_DEFAULT_VALUE_TEST = 0;
constexpr int32_t DRAGBAR_NORMAL_ZINDEX = 1;
constexpr float TEST_SPLIT_RATIO_HALF = 0.5f;
constexpr float TEST_FRAME_WIDTH = 1000.0f;
constexpr float TEST_DIVIDER_WIDTH_PX = 1.0f;
constexpr float TEST_PRIMARY_PARTITION_WIDTH = 500.0f;
constexpr float TEST_SECONDARY_PARTITION_WIDTH = 500.0f;
constexpr float TEST_X_OFFSET_LTR = 100.0f;
constexpr float TEST_X_OFFSET_RTL = -100.0f;

void CreateDividerNodeForTest(const RefPtr<NavigationGroupNode>& navNode)
{
    CHECK_NULL_VOID(navNode);
    auto dividerNode = FrameNode::GetOrCreateFrameNode(V2::DIVIDER_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    CHECK_NULL_VOID(dividerNode);
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<DividerLayoutProperty>();
    CHECK_NULL_VOID(dividerLayoutProperty);
    dividerLayoutProperty->UpdateVertical(true);
    navNode->SetDividerNode(dividerNode);
}

void CreateDragBarNodeForTest(const RefPtr<NavigationGroupNode>& navNode)
{
    CHECK_NULL_VOID(navNode);
    auto dragBarNode = FrameNode::GetOrCreateFrameNode("DragBar", ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavigationDragBarPattern>(); });
    CHECK_NULL_VOID(dragBarNode);
    auto dragBarItemNode = FrameNode::GetOrCreateFrameNode("DragBarItem",
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<Pattern>(); });
    CHECK_NULL_VOID(dragBarItemNode);
    dragBarItemNode->MountToParent(dragBarNode);
    dragBarNode->MountToParent(navNode);
    navNode->SetDragBarNode(dragBarNode);
}

void CreateForceSplitMaskNodesForTest(const RefPtr<NavigationGroupNode>& navNode)
{
    CHECK_NULL_VOID(navNode);
    auto leftMask = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_VOID(leftMask);
    leftMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    navNode->leftMaskNode_ = leftMask;
    auto rightMask = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    CHECK_NULL_VOID(rightMask);
    rightMask->GetLayoutProperty()->UpdateVisibility(VisibleType::GONE);
    navNode->rightMaskNode_ = rightMask;
}

class ScopeIsRightToLeft {
public:
    explicit ScopeIsRightToLeft(bool isRightToLeft)
    {
        backupIsRightToLeft_ = AceApplicationInfo::GetInstance().IsRightToLeft();
        AceApplicationInfo::GetInstance().isRightToLeft_ = isRightToLeft;
    }
    ~ScopeIsRightToLeft()
    {
        AceApplicationInfo::GetInstance().isRightToLeft_ = backupIsRightToLeft_;
    }

private:
    bool backupIsRightToLeft_;
};

class ScopeColorMode {
public:
    explicit ScopeColorMode(ColorMode mode)
    {
        backupColorMode_ = MockContainer::Current()->GetColorMode();
        MockContainer::Current()->SetColorMode(mode);
    }
    ~ScopeColorMode()
    {
        MockContainer::Current()->SetColorMode(backupColorMode_);
    }

private:
    ColorMode backupColorMode_;
};

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
    manager->isForceSplitEnable_ = false;
    manager->mode_ = ForceSplitMode::NOT_SPLIT;

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

void MountDestinationToNavContent(const NavigationTestContext& context,
    const RefPtr<NavDestinationGroupNode>& destination)
{
    CHECK_NULL_VOID(context.navNode);
    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    CHECK_NULL_VOID(navContentNode);
    navContentNode->AddChild(destination);
}

} // namespace

class NavigationPatternTestNineNg : public testing::Test {
public:
    static RefPtr<NavigationBarTheme> navigationBarTheme_;
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();

    void SetUp() override;
};

RefPtr<NavigationBarTheme> NavigationPatternTestNineNg::navigationBarTheme_ = nullptr;

void NavigationPatternTestNineNg::SetUpTestSuite()
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

void NavigationPatternTestNineNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestNineNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

void NavigationPatternTestNineNg::SetUp()
{
    auto pipeline = MockPipelineContext::GetCurrent();
    if (pipeline) {
        auto mgr = AceType::MakeRefPtr<ForceSplitManager>();
        mgr->SetPipelineContext(WeakPtr(pipeline));
        pipeline->forceSplitMgr_ = mgr;
    }
}

/**
 * @tc.name: ProcessHideNavBarChangeInForceSplit001
 * @tc.desc: Branch: if (!IsForceSplitSupported(context) || !forceSplitSuccess_) =>
 *           IsForceSplitSupported = false, forceSplitSuccess_ = true/false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, ProcessHideNavBarChangeInForceSplit001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.pattern, nullptr);

    context.pattern->navBarVisibilityChange_ = true;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->ProcessHideNavBarChangeInForceSplit();
    EXPECT_FALSE(context.pattern->IsForceSplitSupported(MockPipelineContext::GetCurrent()));

    context.pattern->forceSplitSuccess_ = false;
    context.pattern->ProcessHideNavBarChangeInForceSplit();
    EXPECT_FALSE(context.pattern->forceSplitSuccess_);
}

/**
 * @tc.name: ProcessHideNavBarChangeInForceSplit002
 * @tc.desc: Branch: if (!IsForceSplitSupported(context) || !forceSplitSuccess_) =>
 *           IsForceSplitSupported = true, forceSplitSuccess_ = true/false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, ProcessHideNavBarChangeInForceSplit002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.pattern, nullptr);

    context.pattern->navBarVisibilityChange_ = true;
    context.pattern->forceSplitSuccess_ = false;
    context.pattern->ProcessHideNavBarChangeInForceSplit();
    EXPECT_FALSE(context.pattern->forceSplitSuccess_);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->ProcessHideNavBarChangeInForceSplit();
    EXPECT_TRUE(context.pattern->forceSplitSuccess_);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination001
 * @tc.desc: Branch: if (!manager->IsForceSplitSupported(false) || !forceSplitSuccess_) =>
 *           IsForceSplitSupported = false, forceSplitSuccess_ = false/true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(false);
    ASSERT_NE(context.pattern, nullptr);

    context.pattern->forceSplitSuccess_ = false;
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);

    context.pattern->forceSplitSuccess_ = true;
    result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination002
 * @tc.desc: Branch: if (!manager->IsForceSplitSupported(false) || !forceSplitSuccess_) =>
 *           IsForceSplitSupported = true, forceSplitSuccess_ = false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.pattern, nullptr);

    context.pattern->forceSplitSuccess_ = false;
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination003
 * @tc.desc: Branch: forceSplitHomeDest && topDest && forceSplitHomeDest != topDest =>
 *           all conditions true, returns forceSplitHomeDest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    auto detailDest = CreateNavDestinationNode("Detail", 1);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE02, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, homeDest);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination004
 * @tc.desc: Branch: forceSplitHomeDest && topDest && forceSplitHomeDest != topDest =>
 *           forceSplitHomeDest = null, topDest = valid
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto detailDest = CreateNavDestinationNode("Detail", 1);

    AddDestinationToStack(context, PAGE02, detailDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(nullptr);
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination005
 * @tc.desc: Branch: forceSplitHomeDest && topDest && forceSplitHomeDest != topDest =>
 *           forceSplitHomeDest = null, topDest = null
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination005, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(nullptr);
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination006
 * @tc.desc: Branch: forceSplitHomeDest && topDest && forceSplitHomeDest != topDest =>
 *           forceSplitHomeDest = valid, topDest = null
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination006, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    MountDestinationToNavContent(context, homeDest);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: GetNonTopForceSplitHomeDestination007
 * @tc.desc: Branch: forceSplitHomeDest && topDest && forceSplitHomeDest != topDest =>
 *           forceSplitHomeDest == topDest (same node)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetNonTopForceSplitHomeDestination007, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);

    AddDestinationToStack(context, PAGE01, homeDest);
    MountDestinationToNavContent(context, homeDest);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    auto result = context.pattern->GetNonTopForceSplitHomeDestination();
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle001
 * @tc.desc: Branch: lifecycle = ON_SHOW (isShow = true)
 *           Fire lifecycle for shownPages if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnShow = false;
    homeDestHub->SetOnShown([&homeOnShow](int32_t) {
        homeOnShow = true;
    });
    auto detailDest = CreateNavDestinationNode("Detail", 1);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnShow = false;
    detailDestHub->SetOnShown([&detailOnShow](int32_t) {
        detailOnShow = true;
    });
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnShow = false;
    relatedDestHub->SetOnShown([&relatedOnShow](int32_t) {
        relatedOnShow = true;
    });

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 1;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(false);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(false);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(false);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_SHOW, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnShow);
    EXPECT_TRUE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnShow);
    EXPECT_TRUE(detailPattern->GetIsOnShow());
    EXPECT_FALSE(relatedOnShow);
    EXPECT_FALSE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle002
 * @tc.desc: Branch: lifecycle = ON_SHOW (isShow = true)
 *           Fire lifecycle for shownPages and relatedPage if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnShow = false;
    homeDestHub->SetOnShown([&homeOnShow](int32_t) {
        homeOnShow = true;
    });
    auto detailDest = CreateNavDestinationNode("Detail", 1, NavDestinationMode::DIALOG);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnShow = false;
    detailDestHub->SetOnShown([&detailOnShow](int32_t) {
        detailOnShow = true;
    });
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnShow = false;
    relatedDestHub->SetOnShown([&relatedOnShow](int32_t) {
        relatedOnShow = true;
    });

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(false);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(false);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(false);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_SHOW, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnShow);
    EXPECT_TRUE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnShow);
    EXPECT_TRUE(detailPattern->GetIsOnShow());
    EXPECT_TRUE(relatedOnShow);
    EXPECT_TRUE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle003
 * @tc.desc: Branch: lifecycle = ON_WILL_SHOW (isShow = true)
 *           Fire lifecycle for shownPages if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnWillShow = false;
    std::function<void()> homeWillShowCallback = [&homeOnWillShow]() {
        homeOnWillShow = true;
    };
    homeDestHub->SetOnWillShow(homeWillShowCallback);
    auto detailDest = CreateNavDestinationNode("Detail", 1);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnWillShow = false;
    std::function<void()> detailWillShowCallback = [&detailOnWillShow]() {
        detailOnWillShow = true;
    };
    detailDestHub->SetOnWillShow(detailWillShowCallback);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnWillShow = false;
    std::function<void()> relatedWillShowCallback = [&relatedOnWillShow]() {
        relatedOnWillShow = true;
    };
    relatedDestHub->SetOnWillShow(relatedWillShowCallback);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 1;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(false);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(false);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(false);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_WILL_SHOW, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnWillShow);
    EXPECT_FALSE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnWillShow);
    EXPECT_FALSE(detailPattern->GetIsOnShow());
    EXPECT_FALSE(relatedOnWillShow);
    EXPECT_FALSE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle004
 * @tc.desc: Branch: lifecycle = ON_WILL_SHOW (isShow = true)
 *           Fire lifecycle for shownPages and relatedPage if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnWillShow = false;
    std::function<void()> homeWillShowCallback = [&homeOnWillShow]() {
        homeOnWillShow = true;
    };
    homeDestHub->SetOnWillShow(homeWillShowCallback);
    auto detailDest = CreateNavDestinationNode("Detail", 1, NavDestinationMode::DIALOG);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnWillShow = false;
    std::function<void()> detailWillShowCallback = [&detailOnWillShow]() {
        detailOnWillShow = true;
    };
    detailDestHub->SetOnWillShow(detailWillShowCallback);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnWillShow = false;
    std::function<void()> relatedWillShowCallback = [&relatedOnWillShow]() {
        relatedOnWillShow = true;
    };
    relatedDestHub->SetOnWillShow(relatedWillShowCallback);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(false);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(false);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(false);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_WILL_SHOW, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnWillShow);
    EXPECT_FALSE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnWillShow);
    EXPECT_FALSE(detailPattern->GetIsOnShow());
    EXPECT_TRUE(relatedOnWillShow);
    EXPECT_FALSE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle005
 * @tc.desc: Branch: lifecycle = ON_HIDE (isShow = false)
 *           Fire lifecycle in reverse order for shownPages if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle005, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnHide = false;
    homeDestHub->SetOnHidden([&homeOnHide](int32_t) {
        homeOnHide = true;
    });
    auto detailDest = CreateNavDestinationNode("Detail", 1);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnHide = false;
    detailDestHub->SetOnHidden([&detailOnHide](int32_t) {
        detailOnHide = true;
    });
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnHide = false;
    relatedDestHub->SetOnHidden([&relatedOnHide](int32_t) {
        relatedOnHide = true;
    });

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 1;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(true);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(true);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(true);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_HIDE, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnHide);
    EXPECT_FALSE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnHide);
    EXPECT_FALSE(detailPattern->GetIsOnShow());
    EXPECT_FALSE(relatedOnHide);
    EXPECT_TRUE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle006
 * @tc.desc: Branch: lifecycle = ON_HIDE (isShow = false)
 *           Fire lifecycle in reverse order for shownPages, then relatedPage if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle006, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnHide = false;
    homeDestHub->SetOnHidden([&homeOnHide](int32_t) {
        homeOnHide = true;
    });
    auto detailDest = CreateNavDestinationNode("Detail", 1, NavDestinationMode::DIALOG);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnHide = false;
    detailDestHub->SetOnHidden([&detailOnHide](int32_t) {
        detailOnHide = true;
    });
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnHide = false;
    relatedDestHub->SetOnHidden([&relatedOnHide](int32_t) {
        relatedOnHide = true;
    });

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(true);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(true);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(true);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_HIDE, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnHide);
    EXPECT_FALSE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnHide);
    EXPECT_FALSE(detailPattern->GetIsOnShow());
    EXPECT_TRUE(relatedOnHide);
    EXPECT_FALSE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle007
 * @tc.desc: Branch: lifecycle = ON_WILL_HIDE (isShow = false)
 *           Fire lifecycle in reverse order for shownPages if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle007, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnWillHide = false;
    std::function<void()> homeWillHideCallback = [&homeOnWillHide]() {
        homeOnWillHide = true;
    };
    homeDestHub->SetOnWillHide(homeWillHideCallback);
    auto detailDest = CreateNavDestinationNode("Detail", 1);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnWillHide = false;
    std::function<void()> detailWillHideCallback = [&detailOnWillHide]() {
        detailOnWillHide = true;
    };
    detailDestHub->SetOnWillHide(detailWillHideCallback);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnWillHide = false;
    std::function<void()> relatedWillHideCallback = [&relatedOnWillHide]() {
        relatedOnWillHide = true;
    };
    relatedDestHub->SetOnWillHide(relatedWillHideCallback);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 1;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(true);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(true);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(true);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_WILL_HIDE, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnWillHide);
    EXPECT_TRUE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnWillHide);
    EXPECT_TRUE(detailPattern->GetIsOnShow());
    EXPECT_FALSE(relatedOnWillHide);
    EXPECT_TRUE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: FireForceSplitVisibleNodesLifecycle008
 * @tc.desc: Branch: lifecycle = ON_WILL_HIDE (isShow = false)
 *           Fire lifecycle in reverse order for shownPages, then relatedPage if visible
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, FireForceSplitVisibleNodesLifecycle008, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    ASSERT_NE(homeDest, nullptr);
    auto homeDestHub = homeDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(homeDestHub, nullptr);
    auto homeOnWillHide = false;
    std::function<void()> homeWillHideCallback = [&homeOnWillHide]() {
        homeOnWillHide = true;
    };
    homeDestHub->SetOnWillHide(homeWillHideCallback);
    auto detailDest = CreateNavDestinationNode("Detail", 1, NavDestinationMode::DIALOG);
    ASSERT_NE(detailDest, nullptr);
    auto detailDestHub = detailDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(detailDestHub, nullptr);
    auto detailOnWillHide = false;
    std::function<void()> detailWillHideCallback = [&detailOnWillHide]() {
        detailOnWillHide = true;
    };
    detailDestHub->SetOnWillHide(detailWillHideCallback);
    auto relatedDest = CreateNavDestinationNode("Related", 2);
    ASSERT_NE(relatedDest, nullptr);
    auto relatedDestHub = relatedDest->GetEventHub<NavDestinationEventHub>();
    ASSERT_NE(relatedDestHub, nullptr);
    auto relatedOnWillHide = false;
    std::function<void()> relatedWillHideCallback = [&relatedOnWillHide]() {
        relatedOnWillHide = true;
    };
    relatedDestHub->SetOnWillHide(relatedWillHideCallback);

    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE03, detailDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    context.navNode->SetRelatedPageDestNode(relatedDest);
    context.navNode->lastStandardIndex_ = 0;
    context.pattern->forceSplitSuccess_ = true;
    context.pattern->primaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(homeDest)
    };
    context.pattern->secondaryNodes_ = {
        WeakPtr<NavDestinationGroupNode>(detailDest)
    };

    auto homePattern = homeDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(homePattern, nullptr);
    homePattern->SetIsOnShow(true);
    auto detailPattern = detailDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(detailPattern, nullptr);
    detailPattern->SetIsOnShow(true);
    auto relatedPattern = relatedDest->GetPattern<NavDestinationPattern>();
    ASSERT_NE(relatedPattern, nullptr);
    relatedPattern->SetIsOnShow(true);
    context.pattern->FireForceSplitVisibleNodesLifecycle(
        NavDestinationLifecycle::ON_WILL_HIDE, NavDestVisibilityChangeReason::TRANSITION);
    EXPECT_TRUE(homeOnWillHide);
    EXPECT_TRUE(homePattern->GetIsOnShow());
    EXPECT_TRUE(detailOnWillHide);
    EXPECT_TRUE(detailPattern->GetIsOnShow());
    EXPECT_TRUE(relatedOnWillHide);
    EXPECT_TRUE(relatedPattern->GetIsOnShow());
}

/**
 * @tc.name: RebuildSplitDisplayNodes001
 * @tc.desc: Branch: if (idx <= homePageIndex) => true
 *                   if (idx == homePageIndex) { => false
 *                   } else if (columnType == ForceSplitPageColumnType::NONE) { => true/false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, RebuildSplitDisplayNodes001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(context.navNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto primaryContentNode = FrameNode::CreateFrameNode(V2::PRIMARY_CONTENT_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(primaryContentNode, nullptr);

    auto preNode1 = CreateNavDestinationNode("PreNode1", 0);
    ASSERT_NE(preNode1, nullptr);
    preNode1->SetColumnType(ForceSplitPageColumnType::NONE);
    auto preNode2 = CreateNavDestinationNode("PreNode2", 1);
    ASSERT_NE(preNode2, nullptr);
    preNode2->SetColumnType(ForceSplitPageColumnType::SECONDARY);
    auto homeDest = CreateNavDestinationNode("Home", 2);
    auto detailDest = CreateNavDestinationNode("Detail", 3);

    AddDestinationToStack(context, "PreNode1", preNode1);
    AddDestinationToStack(context, "PreNode2", preNode2);
    AddDestinationToStack(context, "Home", homeDest);
    AddDestinationToStack(context, "Detail", detailDest);
    MountDestinationToNavContent(context, preNode1);
    MountDestinationToNavContent(context, preNode2);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    NavigationPattern::SplitDisplaySyncScenario scenario;
    context.pattern->RebuildSplitDisplayNodes(navBar, navContentNode, primaryContentNode, scenario);
    ASSERT_EQ(context.pattern->primaryNodes_.size(), 3U);
    EXPECT_EQ(context.pattern->primaryNodes_[0].Upgrade(), preNode1);
    EXPECT_EQ(context.pattern->primaryNodes_[1].Upgrade(), preNode2);
    EXPECT_EQ(context.pattern->primaryNodes_[2].Upgrade(), homeDest);
    EXPECT_EQ(preNode1->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
    EXPECT_EQ(preNode2->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
    EXPECT_EQ(homeDest->GetColumnType(), ForceSplitPageColumnType::PRIMARY);
}

/**
 * @tc.name: RebuildSplitDisplayNodes002
 * @tc.desc: Branch: if (scenario.isSecondaryPushToPrimaryScene && destNode == scenario.preTopDest) { => true
 *                   if (primaryNodes_.empty()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, RebuildSplitDisplayNodes002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(context.navNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto primaryContentNode = FrameNode::CreateFrameNode(V2::PRIMARY_CONTENT_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(primaryContentNode, nullptr);

    auto detailDest1 = CreateNavDestinationNode("Detail1", 1);
    auto detailDest2 = CreateNavDestinationNode("Detail2", 2);

    AddDestinationToStack(context, "Detail1", detailDest1);
    AddDestinationToStack(context, "Detail2", detailDest2);
    MountDestinationToNavContent(context, detailDest1);
    MountDestinationToNavContent(context, detailDest2);

    context.pattern->forceSplitHomeDest_ = nullptr;
    context.pattern->navBarIsHome_ = true;
    NavigationPattern::SplitDisplaySyncScenario scenario;
    scenario.isSecondaryPushToPrimaryScene = true;
    scenario.preTopDest = detailDest1;
    context.pattern->RebuildSplitDisplayNodes(navBar, navContentNode, primaryContentNode, scenario);
    ASSERT_EQ(context.pattern->primaryNodes_.size(), 1U);
    EXPECT_EQ(context.pattern->primaryNodes_[0].Upgrade(), detailDest1);
    EXPECT_EQ(detailDest1->GetColumnType(), ForceSplitPageColumnType::PRIMARY);
    ASSERT_EQ(context.pattern->splitPushExitNode_.Upgrade(), navBar);
}

/**
 * @tc.name: RebuildSplitDisplayNodes003
 * @tc.desc: Branch: if (destNode == scenario.curTopDest) { => true
 *                   if (destNode->IsShowInPrimaryPartition()) { => true
 *                   if (columnType == ForceSplitPageColumnType::NONE) { => true
 *                   if (columnType == ForceSplitPageColumnType::PRIMARY) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, RebuildSplitDisplayNodes003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(context.navNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto primaryContentNode = FrameNode::CreateFrameNode(V2::PRIMARY_CONTENT_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(primaryContentNode, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 1);
    auto detailDest1 = CreateNavDestinationNode("Detail1", 2);
    auto detailDest2 = CreateNavDestinationNode("Detail2", 3);
    ASSERT_NE(detailDest2, nullptr);
    detailDest2->SetColumnType(ForceSplitPageColumnType::NONE);
    auto detailDest3 = CreateNavDestinationNode("Detail3", 4);
    ASSERT_NE(detailDest3, nullptr);
    detailDest3->SetColumnType(ForceSplitPageColumnType::NONE);
    detailDest3->SetIsShowInPrimaryPartition(true);

    AddDestinationToStack(context, "Home", homeDest);
    AddDestinationToStack(context, "Detail1", detailDest1);
    AddDestinationToStack(context, "Detail2", detailDest2);
    AddDestinationToStack(context, "Detail3", detailDest3);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, detailDest1);
    MountDestinationToNavContent(context, detailDest2);
    MountDestinationToNavContent(context, detailDest3);

    context.pattern->forceSplitHomeDest_ = WeakPtr(homeDest);
    NavigationPattern::SplitDisplaySyncScenario scenario;
    scenario.curTopDest = detailDest3;
    context.pattern->RebuildSplitDisplayNodes(navBar, navContentNode, primaryContentNode, scenario);
    EXPECT_FALSE(detailDest3->IsShowInPrimaryPartition());
    EXPECT_EQ(detailDest3->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
}

/**
 * @tc.name: RebuildSplitDisplayNodes004
 * @tc.desc: Branch: if (!isSecondaryPushToPrimaryScene_ && scenario.isPrimaryPopToSecondaryScene) { => true
 *                   if (primaryNodes_.empty()) { => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, RebuildSplitDisplayNodes004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(context.navNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto primaryContentNode = FrameNode::CreateFrameNode(V2::PRIMARY_CONTENT_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(primaryContentNode, nullptr);

    auto detailDest1 = CreateNavDestinationNode("Detail1", 1);

    AddDestinationToStack(context, "Detail1", detailDest1);
    MountDestinationToNavContent(context, detailDest1);

    context.pattern->forceSplitHomeDest_ = nullptr;
    context.pattern->navBarIsHome_ = true;
    NavigationPattern::SplitDisplaySyncScenario scenario;
    scenario.isSecondaryPushToPrimaryScene = false;
    scenario.isPrimaryPopToSecondaryScene = true;
    scenario.preTopDest = detailDest1;
    context.pattern->RebuildSplitDisplayNodes(navBar, navContentNode, primaryContentNode, scenario);
    ASSERT_TRUE(context.pattern->primaryNodes_.empty());
    ASSERT_EQ(context.pattern->splitPopEnterNode_.Upgrade(), navBar);
}

/**
 * @tc.name: RebuildSplitDisplayNodes005
 * @tc.desc: Branch: if (!isSecondaryPushToPrimaryScene_ && scenario.isPrimaryPopToSecondaryScene) { => true
 *                   if (primaryNodes_.empty()) { => false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, RebuildSplitDisplayNodes005, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    ASSERT_NE(context.stack, nullptr);

    auto navContentNode = AceType::DynamicCast<FrameNode>(context.navNode->GetContentNode());
    ASSERT_NE(navContentNode, nullptr);
    auto navBar = AceType::DynamicCast<NavBarNode>(context.navNode->GetNavBarNode());
    ASSERT_NE(navBar, nullptr);
    auto primaryContentNode = FrameNode::CreateFrameNode(V2::PRIMARY_CONTENT_NODE_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    ASSERT_NE(primaryContentNode, nullptr);

    auto detailDest1 = CreateNavDestinationNode("Detail1", 1);
    ASSERT_NE(detailDest1, nullptr);
    detailDest1->SetColumnType(ForceSplitPageColumnType::PRIMARY);
    detailDest1->SetIsShowInPrimaryPartition(true);
    auto detailDest2 = CreateNavDestinationNode("Detail2", 2);
    ASSERT_NE(detailDest2, nullptr);
    detailDest2->SetColumnType(ForceSplitPageColumnType::PRIMARY);
    detailDest2->SetIsShowInPrimaryPartition(true);
    auto detailDest3 = CreateNavDestinationNode("Detail3", 3);

    AddDestinationToStack(context, "Detail1", detailDest1);
    AddDestinationToStack(context, "Detail2", detailDest2);
    MountDestinationToNavContent(context, detailDest1);
    MountDestinationToNavContent(context, detailDest2);
    MountDestinationToNavContent(context, detailDest3);

    context.pattern->forceSplitHomeDest_ = nullptr;
    context.pattern->navBarIsHome_ = true;
    NavigationPattern::SplitDisplaySyncScenario scenario;
    scenario.isSecondaryPushToPrimaryScene = false;
    scenario.isPrimaryPopToSecondaryScene = true;
    scenario.preTopDest = detailDest3;
    scenario.curTopDest = detailDest2;
    context.pattern->RebuildSplitDisplayNodes(navBar, navContentNode, primaryContentNode, scenario);
    ASSERT_EQ(context.pattern->primaryNodes_.size(), 1U);
    EXPECT_EQ(context.pattern->primaryNodes_[0].Upgrade(), detailDest1);
    ASSERT_EQ(context.pattern->splitPopEnterNode_.Upgrade(), detailDest1);
}

/**
 * @tc.name: AdjustNodeForSplitDisplayReconfigure001
 * @tc.desc: Branch: hasHomePage && idx == topNodeIndex && idx != homePageIndex => true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, AdjustNodeForSplitDisplayReconfigure001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto homeDest = CreateNavDestinationNode("Home", 0);
    auto topDest = CreateNavDestinationNode("TopPrimary", 1);
    ASSERT_NE(homeDest, nullptr);
    ASSERT_NE(topDest, nullptr);

    topDest->SetColumnType(ForceSplitPageColumnType::PRIMARY);
    AddDestinationToStack(context, PAGE01, homeDest);
    AddDestinationToStack(context, PAGE02, topDest);
    MountDestinationToNavContent(context, homeDest);
    MountDestinationToNavContent(context, topDest);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->navBarIsHome_ = false;
    context.pattern->forceSplitHomeDest_ = WeakPtr<NavDestinationGroupNode>(homeDest);

    EXPECT_EQ(topDest->GetColumnType(), ForceSplitPageColumnType::PRIMARY);

    context.pattern->AdjustNodeForSplitDisplayReconfigure();

    EXPECT_EQ(topDest->GetColumnType(), ForceSplitPageColumnType::SECONDARY);
    ASSERT_EQ(context.pattern->primaryNodes_.size(), 1U);
    ASSERT_EQ(context.pattern->secondaryNodes_.size(), 1U);
}

/**
 * @tc.name: HandleForceSplitDragUpdate001
 * @tc.desc: Branch: forceSplitMgr->IsForceSplitDragging() => false
 *           HandleForceSplitDragUpdate returns early when not dragging
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(false);
    manager->SetTemporarySplitRatio(0.55f);

    context.pattern->HandleForceSplitDragUpdate(100.0f);

    auto result = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), 0.55f);
}

/**
 * @tc.name: HandleForceSplitDragUpdate002
 * @tc.desc: Branch: geometryNode->GetFrameSize().Width() == 0 => early return
 *           HandleForceSplitDragUpdate returns early when frame width is zero
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    manager->temporarySplitRatio_ = std::nullopt;

    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(0.0f, 100.0f));

    context.pattern->HandleForceSplitDragUpdate(100.0f);

    auto result = manager->GetTemporarySplitRatio();
    EXPECT_FALSE(result.has_value());
}

/**
 * @tc.name: HandleForceSplitDragUpdate003
 * @tc.desc: Branch: valid conditions => calculates new ratio with clamp
 *           HandleForceSplitDragUpdate updates temporary ratio correctly
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    manager->splitRatio_ = 0.5f;

    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(1000.0f, 100.0f));

    constexpr float xOffset = 100.0f;
    constexpr float expectedRatio = 0.5f - xOffset / 1000.0f;
    context.pattern->HandleForceSplitDragUpdate(xOffset);

    auto result = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), expectedRatio);
}

/**
 * @tc.name: HandleForceSplitDragUpdate004
 * @tc.desc: Branch: xOffset causes ratio below MIN_SPLIT_DRAG_RATIO => clamp to minimum
 *           HandleForceSplitDragUpdate clamps ratio to MIN_SPLIT_DRAG_RATIO
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    manager->splitRatio_ = 0.5f;

    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    constexpr float xOffset = 50.0f;
    constexpr float minSplitDragRatio = 1.0f / 7;
    context.pattern->HandleForceSplitDragUpdate(xOffset);

    auto result = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), minSplitDragRatio);
}

/**
 * @tc.name: HandleForceSplitDragUpdate005
 * @tc.desc: Branch: negative xOffset causes ratio above MAX_SPLIT_DRAG_RATIO => clamp to maximum
 *           HandleForceSplitDragUpdate clamps ratio to MAX_SPLIT_DRAG_RATIO
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate005, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    manager->splitRatio_ = 0.5f;

    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(100.0f, 100.0f));

    constexpr float xOffset = -50.0f;
    constexpr float maxSplitDragRatio = 6.0f / 7;
    context.pattern->HandleForceSplitDragUpdate(xOffset);

    auto result = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(result.has_value());
    EXPECT_FLOAT_EQ(result.value(), maxSplitDragRatio);
}

/**
 * @tc.name: HandleForceSplitDragEnd001
 * @tc.desc: Branch: forceSplitMgr->IsForceSplitDragging() => false
 *           HandleForceSplitDragEnd returns early when not dragging
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragEnd001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    constexpr float testRatio = 0.5f;
    manager->SetTemporarySplitRatio(testRatio);
    manager->SetIsForceSplitDragging(false);

    context.pattern->HandleForceSplitDragEnd();
    auto ratio = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(ratio.has_value());
    EXPECT_FLOAT_EQ(ratio.value(), testRatio);
}

/**
 * @tc.name: HandleForceSplitDragEnd002
 * @tc.desc: Branch: tempRatio has no value => uses splitRatio
 *           HandleForceSplitDragEnd uses splitRatio when temporary ratio is not set
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragEnd002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    manager->ClearTemporarySplitRatio();
    manager->splitRatio_ = 0.5f;

    context.pattern->HandleForceSplitDragEnd();

    EXPECT_FALSE(manager->IsForceSplitDragging());
}

/**
 * @tc.name: HandleForceSplitDragEnd003
 * @tc.desc: Branch: tempRatio equals finalRatio (snap point) => snap directly
 *           HandleForceSplitDragEnd snaps directly when ratio is already at snap point
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragEnd003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    constexpr float snapRatio = 0.5f;
    manager->SetTemporarySplitRatio(snapRatio);

    context.pattern->HandleForceSplitDragEnd();

    EXPECT_FALSE(manager->IsForceSplitDragging());
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), snapRatio);
}

/**
 * @tc.name: GetOrCreateMaskNode001
 * @tc.desc: Branch: isLeft=true, leftMaskNode_ exists => returns cached leftMaskNode_
 *           GetOrCreateMaskNode returns cached mask node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetOrCreateMaskNode001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    auto existingMask = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    context.navNode->leftMaskNode_ = existingMask;

    auto result = context.navNode->GetOrCreateMaskNode(true);
    EXPECT_EQ(result, existingMask);
}

/**
 * @tc.name: GetOrCreateMaskNode002
 * @tc.desc: Branch: isLeft=false, rightMaskNode_ exists => returns cached rightMaskNode_
 *           GetOrCreateMaskNode returns cached right mask node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetOrCreateMaskNode002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    auto existingMask = FrameNode::CreateFrameNode(V2::STACK_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<StackPattern>());
    context.navNode->rightMaskNode_ = existingMask;

    auto result = context.navNode->GetOrCreateMaskNode(false);
    EXPECT_EQ(result, existingMask);
}

/**
 * @tc.name: GetOrCreateMaskNode003
 * @tc.desc: Branch: isLeft=true, leftMaskNode_ is null => creates new mask node
 *           GetOrCreateMaskNode creates and caches new left mask node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetOrCreateMaskNode003, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    context.navNode->leftMaskNode_ = nullptr;

    auto result = context.navNode->GetOrCreateMaskNode(true);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), FORCESPLIT_DRAG_MASKNODE_TAG);
    EXPECT_EQ(context.navNode->leftMaskNode_, result);
}

/**
 * @tc.name: GetOrCreateMaskNode004
 * @tc.desc: Branch: isLeft=false, rightMaskNode_ is null => creates new mask node
 *           GetOrCreateMaskNode creates and caches new right mask node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, GetOrCreateMaskNode004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    context.navNode->rightMaskNode_ = nullptr;

    auto result = context.navNode->GetOrCreateMaskNode(false);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->GetTag(), FORCESPLIT_DRAG_MASKNODE_TAG);
    EXPECT_EQ(context.navNode->rightMaskNode_, result);
}

/**
 * @tc.name: UpdateMaskNodeVisibility001
 * @tc.desc: Branch: isLeft=true, VisibleType::VISIBLE => updates visibility
 *           UpdateMaskNodeVisibility updates left mask visibility correctly
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateMaskNodeVisibility001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    context.navNode->UpdateMaskNodeVisibility(true, VisibleType::VISIBLE);
    auto maskNode = context.navNode->GetOrCreateMaskNode(true);
    ASSERT_NE(maskNode, nullptr);
    auto property = maskNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    auto visibility = property->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::VISIBLE);
}

/**
 * @tc.name: UpdateMaskNodeVisibility002
 * @tc.desc: Branch: isLeft=false, VisibleType::GONE => updates visibility
 *           UpdateMaskNodeVisibility updates right mask visibility correctly
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateMaskNodeVisibility002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);

    context.navNode->UpdateMaskNodeVisibility(false, VisibleType::GONE);
    auto maskNode = context.navNode->GetOrCreateMaskNode(false);
    ASSERT_NE(maskNode, nullptr);
    auto property = maskNode->GetLayoutProperty();
    ASSERT_NE(property, nullptr);
    auto visibility = property->GetVisibilityValue(VisibleType::VISIBLE);
    EXPECT_EQ(visibility, VisibleType::GONE);
}

/**
 * @tc.name: PageTransitionReport001
 * @tc.desc: Branch: context == nullptr
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, PageTransitionReport001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext();
    ASSERT_NE(context.pattern, nullptr);
    RefPtr<MockPipelineContext> pipeline_bak = MockPipelineContext::pipeline_;
    MockPipelineContext::pipeline_ = nullptr;

    context.pattern->PageTransitionReport("fromPage", "toPage", "fromCompoent", "toComponent");
    EXPECT_NE(context.pattern, nullptr);
    MockPipelineContext::pipeline_ = pipeline_bak;
}

/**
 * @tc.name: UpdateForceSplitDragZIndex001
 * @tc.desc: Test UpdateForceSplitDragZIndex with isDragging true/false
 *           isDragging=true: sets ZIndex (divider=4, dragBar=5, item=6)
 *           isDragging=false: resets ZIndex (divider=0, dragBar=1, item=2)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateForceSplitDragZIndex001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    CreateDragBarNodeForTest(context.navNode);

    // Branch: isDragging=true
    context.pattern->UpdateForceSplitDragZIndex(true);
    auto divider = context.pattern->GetDividerNode();
    auto dragBar = context.pattern->GetDragBarNode();
    ASSERT_NE(divider, nullptr);
    ASSERT_NE(dragBar, nullptr);
    EXPECT_EQ(divider->GetRenderContext()->GetZIndex(), FORCESPLIT_DRAG_DIVIDER_ZINDEX_TEST);
    EXPECT_EQ(dragBar->GetRenderContext()->GetZIndex(), FORCESPLIT_DRAGBAR_ZINDEX_TEST);
    auto dragBarItem = AceType::DynamicCast<FrameNode>(dragBar->GetChildren().front());
    ASSERT_NE(dragBarItem, nullptr);
    EXPECT_EQ(dragBarItem->GetRenderContext()->GetZIndex(), FORCESPLIT_DRAGBAR_ITEM_ZINDEX_TEST);

    // Branch: isDragging=false
    context.pattern->UpdateForceSplitDragZIndex(false);
    EXPECT_EQ(divider->GetRenderContext()->GetZIndex().value_or(ZINDEX_DEFAULT_VALUE), ZINDEX_DEFAULT_VALUE_TEST);
    EXPECT_EQ(dragBar->GetRenderContext()->GetZIndex(), DRAGBAR_NORMAL_ZINDEX);
    EXPECT_EQ(dragBarItem->GetRenderContext()->GetZIndex(), SECOND_ZINDEX_VALUE_TEST);
}

/**
 * @tc.name: UpdateForceSplitDividerColor001
 * @tc.desc: Test UpdateForceSplitDividerColor early return conditions
 *           GetIsTargetForceSplitNav=false: returns false
 *           IsForceSplitEnable=false: returns false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateForceSplitDividerColor001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    auto divider = context.pattern->GetDividerNode();
    ASSERT_NE(divider, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    // Branch: GetIsTargetForceSplitNav=false
    context.pattern->SetIsTargetForceSplitNav(false);
    EXPECT_FALSE(context.pattern->UpdateForceSplitDividerColor(divider));

    // Branch: IsForceSplitEnable=false
    manager->isForceSplitEnable_ = false;
    context.pattern->SetIsTargetForceSplitNav(true);
    EXPECT_FALSE(context.pattern->UpdateForceSplitDividerColor(divider));
}

/**
 * @tc.name: UpdateForceSplitDividerColor002
 * @tc.desc: Test UpdateForceSplitDividerColor with LIGHT/DARK modes and has_value branches
 *           LIGHT/DARK mode with color: sets color, returns true
 *           LIGHT mode without color: returns false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateForceSplitDividerColor002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    auto divider = context.pattern->GetDividerNode();
    ASSERT_NE(divider, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitEnable_ = true;
    context.pattern->SetIsTargetForceSplitNav(true);

    // Branch: LIGHT mode with color
    manager->SetSplitDividerColor(Color::RED, std::nullopt);
    ScopeColorMode colorMode1(ColorMode::LIGHT);
    EXPECT_TRUE(context.pattern->UpdateForceSplitDividerColor(divider));
    EXPECT_EQ(divider->GetRenderContext()->GetBackgroundColor().value(), Color::RED);

    // Branch: DARK mode with color
    manager->SetSplitDividerColor(std::nullopt, Color::BLUE);
    ScopeColorMode colorMode2(ColorMode::DARK);
    EXPECT_TRUE(context.pattern->UpdateForceSplitDividerColor(divider));
    EXPECT_EQ(divider->GetRenderContext()->GetBackgroundColor().value(), Color::BLUE);

    // Branch: LIGHT mode without color
    manager->SetSplitDividerColor(std::nullopt, Color::BLUE);
    ScopeColorMode colorMode3(ColorMode::LIGHT);
    EXPECT_FALSE(context.pattern->UpdateForceSplitDividerColor(divider));
}

/**
 * @tc.name: OnForceSplitIsDraggableChange001
 * @tc.desc: Test OnForceSplitIsDraggableChange when conditions not met
 *           isDraggable=false: clears drag bar
 *           IsForceSplitSuccess=false: clears drag bar
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, OnForceSplitIsDraggableChange001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDragBarNodeForTest(context.navNode);
    auto dragBarNode = context.navNode->GetDragBarNode();
    ASSERT_NE(dragBarNode, nullptr);

    // Branch: isDraggable=false
    context.pattern->OnForceSplitIsDraggableChange(false);
    EXPECT_EQ(context.navNode->GetChildIndexById(dragBarNode), -1);

    // Branch: IsForceSplitSuccess=false
    CreateDragBarNodeForTest(context.navNode);
    dragBarNode = context.navNode->GetDragBarNode();
    ASSERT_NE(dragBarNode, nullptr);
    context.pattern->forceSplitSuccess_ = false;
    context.pattern->OnForceSplitIsDraggableChange(true);
    EXPECT_EQ(context.navNode->GetChildIndexById(dragBarNode), -1);
}

/**
 * @tc.name: OnForceSplitIsDraggableChange002
 * @tc.desc: Test OnForceSplitIsDraggableChange when conditions met
 *           dragBar=null: creates new
 *           dragBar exists: reuse
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, OnForceSplitIsDraggableChange002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    context.pattern->forceSplitSuccess_ = true;

    // Branch: dragBar=null => creates new
    context.navNode->SetDragBarNode(nullptr);
    context.pattern->OnForceSplitIsDraggableChange(true);
    ASSERT_NE(context.navNode->GetDragBarNode(), nullptr);

    // Branch: dragBar exists => reuse
    auto existingDragBar = context.navNode->GetDragBarNode();
    context.pattern->OnForceSplitIsDraggableChange(true);
    EXPECT_EQ(context.navNode->GetDragBarNode(), existingDragBar);
}

/**
 * @tc.name: HandleForceSplitDragUpdate006
 * @tc.desc: Test HandleForceSplitDragUpdate in LTR/RTL modes
 *           LTR: newRatio -= xOffset / frameWidth
 *           RTL: newRatio += xOffset / frameWidth
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragUpdate006, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, 100.0f));
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->splitRatio_ = TEST_SPLIT_RATIO_HALF;
    manager->SetIsForceSplitDragging(true);

    // Branch: LTR mode
    ScopeIsRightToLeft isRightToLeft1(false);
    context.pattern->HandleForceSplitDragUpdate(TEST_X_OFFSET_LTR);
    auto tempRatio = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(tempRatio.has_value());
    EXPECT_FLOAT_EQ(tempRatio.value(), TEST_SPLIT_RATIO_HALF - TEST_X_OFFSET_LTR / TEST_FRAME_WIDTH);

    // Branch: RTL mode
    manager->splitRatio_ = TEST_SPLIT_RATIO_HALF;
    ScopeIsRightToLeft isRightToLeft2(true);
    context.pattern->HandleForceSplitDragUpdate(TEST_X_OFFSET_RTL);
    tempRatio = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(tempRatio.has_value());
    EXPECT_FLOAT_EQ(tempRatio.value(), TEST_SPLIT_RATIO_HALF + TEST_X_OFFSET_RTL / TEST_FRAME_WIDTH);
}

/**
 * @tc.name: HandleForceSplitDragStart001
 * @tc.desc: Test HandleForceSplitDragStart early return
 *           IsSplitDraggable=false: not start
 *           IsForceSplitDragging=true: not start again
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragStart001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->isForceSplitDragging_ = false;

    // Branch: if(!IsForceSplitSuccess()) { => true
    context.pattern->forceSplitSuccess_ = false;
    context.pattern->HandleForceSplitDragStart();
    EXPECT_FALSE(manager->IsForceSplitDragging());

    context.pattern->forceSplitSuccess_ = true;
    // Branch: IsSplitDraggable=false
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->wideSplitIsDraggable_ = false;
    context.pattern->HandleForceSplitDragStart();
    EXPECT_FALSE(manager->IsForceSplitDragging());

    // Branch: IsForceSplitDragging=true
    manager->wideSplitIsDraggable_ = true;
    manager->SetIsForceSplitDragging(true);
    context.pattern->HandleForceSplitDragStart();
    EXPECT_TRUE(manager->IsForceSplitDragging());
}

/**
 * @tc.name: HandleForceSplitDragStart002
 * @tc.desc: Test HandleForceSplitDragStart success
 *           Starts drag and initializes partition widths
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragStart002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    CreateDragBarNodeForTest(context.navNode);
    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, 100.0f));
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->mode_ = ForceSplitMode::WIDE_SPLIT;
    manager->wideSplitIsDraggable_ = true;
    manager->splitRatio_ = TEST_SPLIT_RATIO_HALF;
    manager->SetIsForceSplitDragging(false);

    context.pattern->forceSplitSuccess_ = true;
    context.pattern->HandleForceSplitDragStart();
    EXPECT_TRUE(manager->IsForceSplitDragging());
    EXPECT_FLOAT_EQ(context.pattern->primaryPartitionWidth_,
        (TEST_FRAME_WIDTH - TEST_DIVIDER_WIDTH_PX) * (1.0f - TEST_SPLIT_RATIO_HALF));
}

/**
 * @tc.name: OnForceSplitDragStart001
 * @tc.desc: Test OnForceSplitDragStart initialization
 *           Sets ZIndex and partition widths
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, OnForceSplitDragStart001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    CreateDragBarNodeForTest(context.navNode);
    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, 100.0f));
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->splitRatio_ = TEST_SPLIT_RATIO_HALF;

    context.pattern->OnForceSplitDragStart();
    auto divider = context.pattern->GetDividerNode();
    auto dragBar = context.pattern->GetDragBarNode();
    ASSERT_NE(divider, nullptr);
    ASSERT_NE(dragBar, nullptr);
    auto dividerContext = divider->GetRenderContext();
    ASSERT_NE(dividerContext, nullptr);
    auto dragBarContext = dragBar->GetRenderContext();
    ASSERT_NE(dragBarContext, nullptr);
    EXPECT_EQ(dividerContext->GetZIndex().value_or(ZINDEX_DEFAULT_VALUE), FORCESPLIT_DRAG_DIVIDER_ZINDEX_TEST);
    EXPECT_EQ(dragBarContext->GetZIndex().value_or(ZINDEX_DEFAULT_VALUE), FORCESPLIT_DRAGBAR_ZINDEX_TEST);
    EXPECT_FLOAT_EQ(context.pattern->forceSplitDividerWidth_, TEST_DIVIDER_WIDTH_PX);
}

/**
 * @tc.name: OnForceSplitDragEnd001
 * @tc.desc: Test OnForceSplitDragEnd cleanup
 *           Resets ZIndex to normal
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, OnForceSplitDragEnd001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    CreateDragBarNodeForTest(context.navNode);
    CreateForceSplitMaskNodesForTest(context.navNode);

    context.pattern->OnForceSplitDragEnd();
    auto divider = context.pattern->GetDividerNode();
    auto dragBar = context.pattern->GetDragBarNode();
    ASSERT_NE(divider, nullptr);
    ASSERT_NE(dragBar, nullptr);
    auto dividerContext = divider->GetRenderContext();
    ASSERT_NE(dividerContext, nullptr);
    auto dragBarContext = dragBar->GetRenderContext();
    ASSERT_NE(dragBarContext, nullptr);
    EXPECT_EQ(dividerContext->GetZIndex().value_or(ZINDEX_DEFAULT_VALUE), ZINDEX_DEFAULT_VALUE_TEST);
    EXPECT_EQ(dragBarContext->GetZIndex().value_or(ZINDEX_DEFAULT_VALUE), DRAGBAR_NORMAL_ZINDEX);
}

/**
 * @tc.name: HandleForceSplitDragEnd004
 * @tc.desc: Test HandleForceSplitDragEnd with isDragCanceled and tempRatio branches
 *           isDragCanceled=true: uses splitRatio
 *           isDragCanceled=false + tempRatio: uses tempRatio
 *           isDragCanceled=false + no tempRatio: uses splitRatio
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragEnd004, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    constexpr float tempRatio = 0.7f;
    constexpr float splitRatio = 0.5f;
    manager->splitRatio_ = splitRatio;

    // Branch: isDragCanceled=true
    manager->SetIsForceSplitDragging(true);
    manager->SetTemporarySplitRatio(tempRatio);
    context.pattern->HandleForceSplitDragEnd(true);
    EXPECT_FALSE(manager->IsForceSplitDragging());
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), splitRatio);

    // Branch: isDragCanceled=false + tempRatio has value
    manager->SetIsForceSplitDragging(true);
    manager->SetTemporarySplitRatio(splitRatio);
    context.pattern->HandleForceSplitDragEnd(false);
    EXPECT_FALSE(manager->IsForceSplitDragging());
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), splitRatio);

    // Branch: isDragCanceled=false + tempRatio has no value
    manager->SetIsForceSplitDragging(true);
    manager->ClearTemporarySplitRatio();
    manager->splitRatio_ = splitRatio;
    context.pattern->HandleForceSplitDragEnd(false);
    EXPECT_FALSE(manager->IsForceSplitDragging());
}

/**
 * @tc.name: HandleForceSplitDragEnd005
 * @tc.desc: Test HandleForceSplitDragEnd plays animation when needed
 *           isDragCanceled=false + tempRatio != snap point: plays animation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, HandleForceSplitDragEnd005, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    manager->SetIsForceSplitDragging(true);
    constexpr float tempRatio = 0.6f;
    manager->SetTemporarySplitRatio(tempRatio);

    context.pattern->HandleForceSplitDragEnd(false);
    EXPECT_NE(context.pattern->forceSplitSnapAnimation_, nullptr);
}

/**
 * @tc.name: AbortForceSplitDragging001
 * @tc.desc: Test AbortForceSplitDragging with different conditions
 *           IsRouterForceSplit=true: returns early
 *           Has animation: stops animation
 *           No animation: calls HandleTouchUp + HandleForceSplitDragEnd(true)
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, AbortForceSplitDragging001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    CreateDividerNodeForTest(context.navNode);
    CreateDragBarNodeForTest(context.navNode);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);
    constexpr float tempRatio = 0.7f;
    constexpr float splitRatio = 0.5f;
    manager->splitRatio_ = splitRatio;

    // Branch: if (!GetIsTargetForceSplitNav()) { => true
    manager->SetIsForceSplitDragging(true);
    context.pattern->SetIsTargetForceSplitNav(false);
    context.pattern->AbortForceSplitDragging();
    EXPECT_TRUE(manager->IsForceSplitDragging());

    context.pattern->SetIsTargetForceSplitNav(true);
    // Branch: IsRouterForceSplit=true
    manager->SetIsRouter(true);
    manager->SetIsForceSplitDragging(true);
    context.pattern->AbortForceSplitDragging();
    EXPECT_TRUE(manager->IsForceSplitDragging());

    // Branch: Has animation
    manager->SetIsRouter(false);
    manager->SetIsForceSplitDragging(true);
    AnimationOption option;
    option.SetCurve(AceType::MakeRefPtr<InterpolatingSpring>(0.0f, 1.0f, 228.0f, 30.0f));
    context.pattern->forceSplitSnapAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    context.pattern->AbortForceSplitDragging();
    EXPECT_EQ(context.pattern->forceSplitSnapAnimation_, nullptr);

    // Branch: No animation
    manager->SetIsForceSplitDragging(true);
    manager->SetTemporarySplitRatio(tempRatio);
    context.pattern->forceSplitSnapAnimation_.reset();
    context.pattern->AbortForceSplitDragging();
    EXPECT_FALSE(manager->IsForceSplitDragging());
    EXPECT_FLOAT_EQ(manager->GetSplitRatio(), splitRatio);
}

/**
 * @tc.name: UpdateForceSplitScaleAndTranslateByRatio001
 * @tc.desc: Test UpdateForceSplitScaleAndTranslateByRatio invalid width
 *           frameWidth<=0: returns early
 *           primaryPartitionWidth<=0: returns early
 *           secondaryPartitionWidth<=0: returns early
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateForceSplitScaleAndTranslateByRatio001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);

    // Branch: frameWidth<=0
    geometryNode->SetFrameSize(SizeF(0.0f, 100.0f));
    context.pattern->UpdateForceSplitScaleAndTranslateByRatio(TEST_SPLIT_RATIO_HALF);

    // Branch: primaryPartitionWidth<=0
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, 100.0f));
    context.pattern->primaryPartitionWidth_ = 0.0f;
    context.pattern->UpdateForceSplitScaleAndTranslateByRatio(TEST_SPLIT_RATIO_HALF);

    // Branch: secondaryPartitionWidth<=0
    context.pattern->primaryPartitionWidth_ = TEST_PRIMARY_PARTITION_WIDTH;
    context.pattern->secondaryPartitionWidth_ = 0.0f;
    context.pattern->UpdateForceSplitScaleAndTranslateByRatio(TEST_SPLIT_RATIO_HALF);
}

/**
 * @tc.name: UpdateForceSplitScaleAndTranslateByRatio002
 * @tc.desc: Test UpdateForceSplitScaleAndTranslateByRatio in LTR/RTL
 *           LTR: calculates correct transforms
 *           RTL: calculates correct transforms
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, UpdateForceSplitScaleAndTranslateByRatio002, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto navBarNode = FrameNode::CreateFrameNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavBarPattern>());
    ASSERT_NE(navBarNode, nullptr);
    context.navNode->navBarNode_ = navBarNode;
    auto geometryNode = context.navNode->GetGeometryNode();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetFrameSize(SizeF(TEST_FRAME_WIDTH, 100.0f));
    context.pattern->primaryPartitionWidth_ = TEST_PRIMARY_PARTITION_WIDTH;
    context.pattern->secondaryPartitionWidth_ = TEST_SECONDARY_PARTITION_WIDTH;

    // Branch: LTR mode
    ScopeIsRightToLeft isRightToLeft1(false);
    context.pattern->UpdateForceSplitScaleAndTranslateByRatio(TEST_SPLIT_RATIO_HALF);
    auto scale = navBarNode->GetRenderContext()->GetTransformScale();
    ASSERT_TRUE(scale.has_value());
    EXPECT_NEAR(scale.value().x, 1.0f, 0.01f);

    // Branch: RTL mode
    ScopeIsRightToLeft isRightToLeft2(true);
    context.pattern->UpdateForceSplitScaleAndTranslateByRatio(TEST_SPLIT_RATIO_HALF);
    scale = navBarNode->GetRenderContext()->GetTransformScale();
    ASSERT_TRUE(scale.has_value());
    EXPECT_NEAR(scale.value().x, 1.0f, 0.01f);
}

/**
 * @tc.name: OnForceSplitSnapAnimationEnd001
 * @tc.desc: Test OnForceSplitSnapAnimationEnd sets temporary ratio
 *           Updates ratio and marks dirty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, OnForceSplitSnapAnimationEnd001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);
    auto manager = MockPipelineContext::GetCurrent()->GetForceSplitManager();
    ASSERT_NE(manager, nullptr);

    context.pattern->OnForceSplitSnapAnimationEnd(TEST_SPLIT_RATIO_HALF);
    auto tempRatio = manager->GetTemporarySplitRatio();
    ASSERT_TRUE(tempRatio.has_value());
    EXPECT_FLOAT_EQ(tempRatio.value(), TEST_SPLIT_RATIO_HALF);
}

/**
 * @tc.name: ClearForceSplitDragBarEvent001
 * @tc.desc: Test ClearForceSplitDragBarEvent clears events and removes node
 *           No events: removes node
 *           Has events: clears and removes node
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNineNg, ClearForceSplitDragBarEvent001, TestSize.Level1)
{
    auto context = CreateNavigationTestContext(true);
    ASSERT_NE(context.navNode, nullptr);
    ASSERT_NE(context.pattern, nullptr);

    // Branch: no events, just remove node
    CreateDragBarNodeForTest(context.navNode);
    auto dragBarNode = AceType::DynamicCast<FrameNode>(context.navNode->GetDragBarNode());
    ASSERT_NE(dragBarNode, nullptr);
    EXPECT_NE(context.navNode->GetChildIndexById(dragBarNode->GetId()), -1);
    context.pattern->touchEvent_ = nullptr;
    context.pattern->forceSplitDragEvent_ = nullptr;
    context.pattern->ClearForceSplitDragBarEvent();
    EXPECT_EQ(context.navNode->GetChildIndexById(dragBarNode->GetId()), -1);

    // Branch: has events, clears and removes
    CreateDragBarNodeForTest(context.navNode);
    dragBarNode = AceType::DynamicCast<FrameNode>(context.navNode->GetDragBarNode());
    ASSERT_NE(dragBarNode, nullptr);
    auto gestureHub = dragBarNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>([](const TouchEventInfo&) {});
    auto panEvent = AceType::MakeRefPtr<PanEvent>([](const GestureEvent&) {}, [](const GestureEvent&) {},
        [](const GestureEvent&) {}, []() {});
    context.pattern->touchEvent_ = touchEvent;
    context.pattern->forceSplitDragEvent_ = panEvent;
    gestureHub->AddTouchEvent(touchEvent);
    gestureHub->AddPanEvent(panEvent, { .type = PanDirection::HORIZONTAL }, 1,
        { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() } });
    context.pattern->ClearForceSplitDragBarEvent();
    EXPECT_EQ(context.pattern->touchEvent_, nullptr);
    EXPECT_EQ(context.pattern->forceSplitDragEvent_, nullptr);
    EXPECT_EQ(context.navNode->GetChildIndexById(dragBarNode->GetId()), -1);
}
} // namespace OHOS::Ace::NG
