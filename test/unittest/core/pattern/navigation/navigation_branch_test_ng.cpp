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
#include "mock_navigation_route.h"
#include "mock_navigation_stack.h"

#include "base/memory/ace_type.h"
#include "core/components_ng/animation/geometry_transition.h"

#define protected public
#define private public
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
const std::string TEST_TAG = "test";
constexpr int32_t TEST_DATA = 10;
} // namespace

class NavigationBranchTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
};

void NavigationBranchTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationBranchTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationBranchTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

/**
 * @tc.name: NavigationPatternTest001
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
}

/**
 * @tc.name: NavigationPatternTest002
 * @tc.desc: Test NavigationPattern OnModifyDone.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);
    NavigationPattern navigationPattern;
    navigationPattern.navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern.navigationStack_, nullptr);
    navigationPattern.AttachToFrameNode(frameNode);
    navigationPattern.OnModifyDone();
    navigationPattern.DetachFromFrameNode(AceType::RawPtr(frameNode));
}

/**
 * @tc.name: NavigationPatternTest003
 * @tc.desc: Various situations of Test NavigationPattern OnDirtyLayoutWrapperSwap.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    std::vector<DirtySwapConfig> configValue;
    configValue.push_back(config);

    for (auto& iter : configValue) {
        EXPECT_EQ(pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, iter), false);
    }
}

/**
 * @tc.name: NavigationPatternTest004
 * @tc.desc: Test Two level nesting of layoutWrapper.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest004, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    bool result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);

    auto setNavigation = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(setNavigation);
    layoutWrapper->SetLayoutAlgorithm(layoutAlgorithmWrapper);
    result = pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(result, false);
}

/**
 * @tc.name: NavigationPatternTest005
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest005, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    navigationModel.SetCustomTitle(frameNode);
    RefPtr<UINode> uiNode = nullptr;
    navigationModel.SetCustomTitle(uiNode);

    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
}

/**
 * @tc.name: NavigationTestNg001
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationTestNg001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationGroupNode.GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto res = navigationGroupNode.GetFrameNode(TEST_TAG, nodeId);
    EXPECT_EQ(res, nullptr);
}

/**
 * @tc.name: NavigationTestNg002
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationTestNg002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationGroupNode.GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->isRoot_ = true;
    ASSERT_NE(json, nullptr);
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigationGroupNode.SetNavBarNode(navBarNode);
    auto narbar = AceType::DynamicCast<OHOS::Ace::NG::NavBarNode>(navigationGroupNode.GetNavBarNode());
    ASSERT_NE(narbar, nullptr);
}

/**
 * @tc.name: NavigationTestNg003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationTestNg003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    navigationGroupNode.pattern_ = pattern;
    ASSERT_NE(AceType::DynamicCast<NavigationPattern>(navigationGroupNode.GetPattern()), nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationGroupNode.GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigationGroupNode.SetNavBarNode(navBarNode);
    auto navBar = AceType::DynamicCast<OHOS::Ace::NG::NavBarNode>(navigationGroupNode.GetNavBarNode());
    navBar->SetNavBarContentNode(navBarNode);
    auto contentNode = navBar->GetNavBarContentNode();
    ASSERT_NE(navBar, nullptr);
    auto child = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG, TEST_DATA, []() { return AceType::MakeRefPtr<OHOS::Ace::NG::NavBarPattern>(); });
    ASSERT_NE(child, nullptr);
    navigationGroupNode.AddChildToGroup(child);
}

/**
 * @tc.name: NavigationModelTest001
 * @tc.desc: Test NavigationModel SetTitleMode.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationModelTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationModel.SetTitleMode(NavigationTitleMode::FREE);
    navigationModel.SetTitleMode(NavigationTitleMode::MINI);
    bool result = true;
    if (navBarLayoutProperty->GetTitleModeString() != "NavigationTitleMode.Mini") {
        result = false;
    }
    EXPECT_EQ(result, true);
}

/**
 * @tc.name: NavigationModelTest002
 * @tc.desc: Test NavigationModel SetHideTitleBar false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationModelTest002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    EXPECT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    EXPECT_NE(navBarLayoutProperty, nullptr);
    navigationModel.SetHideTitleBar(false);
    EXPECT_EQ(navBarLayoutProperty->GetHideTitleBar().value_or(false), false);
}

/**
 * @tc.name: NavigationPatternTest006
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest006, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = nullptr;
    pattern->FireNavigationInner(frameNode, true);
}

/**
 * @tc.name: NavigationPatternTest007
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest007, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", nullptr));
    pattern->navigationStack_->SetNavPathList(navPathList);
    pattern->FireNavigationInner(frameNode, true);
}

/**
 * @tc.name: NavigationPatternTest008
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest008, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is not nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    // set curDestination->IsActive() is false
    curDestination->isActive_ = false;
    // set navDestinationPattern->GetIsOnShow() is false
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    pattern->FireNavigationInner(frameNode, true);
}

/**
 * @tc.name: NavigationPatternTest009
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest009, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is not nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    // set curDestination->IsActive() is true
    curDestination->isActive_ = true;
    // set navDestinationPattern->GetIsOnShow() is true
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(true);
    pattern->FireNavigationInner(frameNode, true);
}

/**
 * @tc.name: NavigationPatternTest010
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest010, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = nullptr;
    pattern->FireNavigationInner(frameNode, false);
}

/**
 * @tc.name: NavigationPatternTest011
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest011, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", nullptr));
    pattern->navigationStack_->SetNavPathList(navPathList);
    pattern->FireNavigationInner(frameNode, false);
}

/**
 * @tc.name: NavigationPatternTest012
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest012, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is not nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    // set curDestination->IsActive() is false
    curDestination->isActive_ = false;
    // set navDestinationPattern->GetIsOnShow() is false
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    pattern->FireNavigationInner(frameNode, false);
}

/**
 * @tc.name: NavigationPatternTest013
 * @tc.desc: Test FireNavigationInner function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest013, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    // set curDestination is not nullptr
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set curDestination->GetLayoutProperty() is not nullptr
    auto curDestination = AceType::DynamicCast<NavDestinationGroupNode>(
        hostNode->GetNavDestinationNode(tempNode));
    curDestination->layoutProperty_ = AceType::MakeRefPtr<LayoutProperty>();
    // set curDestination->IsActive() is true
    curDestination->isActive_ = true;
    // set navDestinationPattern->GetIsOnShow() is true
    auto navDestinationPattern = curDestination->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(true);
    pattern->FireNavigationInner(frameNode, false);
}

/**
 * @tc.name: NavigationPatternTest014
 * @tc.desc: Test FireNavigationChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest014, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    // test FireNavigationChange function if isFirst is true
    pattern->FireNavigationChange(frameNode, true, true);
}

/**
 * @tc.name: NavigationPatternTest015
 * @tc.desc: Test FireNavigationChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest015, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    // test FireNavigationChange function if isFirst is false
    pattern->FireNavigationChange(frameNode, true, false);
}

/**
 * @tc.name: NavigationPatternTest016
 * @tc.desc: Test RefreshFocusToDestination function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest016, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    // add stack info
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    auto navDestination1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 124, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    pattern->navigationStack_->Add("navDestination1", navDestination1);
    pattern->OnModifyDone();
    pattern->RefreshFocusToDestination();
}

/**
 * @tc.name: NavigationPatternTest017
 * @tc.desc: Test RecoveryToLastStack function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest017, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    // set navPathList_
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", nullptr));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set recoveryList_
    pattern->navigationStack_->UpdateRecoveryList();
    pattern->OnModifyDone();
    pattern->RecoveryToLastStack();
}

/**
 * @tc.name: NavigationPatternTest018
 * @tc.desc: Test RecoveryToLastStack function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest018, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    // set navPathList_
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    // set recoveryList_
    pattern->navigationStack_->UpdateRecoveryList();
    pattern->OnModifyDone();
    pattern->RecoveryToLastStack();
}

/**
 * @tc.name: NavigationPatternTest019
 * @tc.desc: Test PerformanceEventReport function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest019, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    int32_t nodeCount = 1001;
    int32_t depth = 301;
    std::string navDestinationName = "navDestinationName";
    pattern->PerformanceEventReport(nodeCount, depth, navDestinationName);
}

/**
 * @tc.name: NavigationPatternTest020
 * @tc.desc: Test PerformanceEventReport function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest020, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    int32_t nodeCount = 1;
    int32_t depth = 3;
    std::string navDestinationName = "navDestinationName";
    pattern->PerformanceEventReport(nodeCount, depth, navDestinationName);
}

/**
 * @tc.name: NavigationPatternTest021
 * @tc.desc: Test OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest021, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    int32_t width = 10;
    int32_t height = 20;
    pattern->OnWindowSizeChanged(width, height, WindowSizeChangeReason::ROTATION);
}

/**
 * @tc.name: NavigationPatternTest022
 * @tc.desc: Test OnWindowSizeChanged function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest022, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    int32_t width = 10;
    int32_t height = 20;
    pattern->OnWindowSizeChanged(width, height, WindowSizeChangeReason::MAXIMIZE);
}

/**
 * @tc.name: NavigationPatternTest023
 * @tc.desc: Test NotifyPerfMonitorPageMsg function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest023, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    std::string pageName = "pageone";
    pattern->NotifyPerfMonitorPageMsg(pageName);
}

/**
 * @tc.name: NavigationPatternTest024
 * @tc.desc: Test AbortAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest024, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();

    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.314f, 0.95f);
    option.SetCurve(motion);
    std::shared_ptr<AnimationUtils::Animation> adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    hostNode->pushAnimations_.emplace_back(adaptAnimation_);
    pattern->AbortAnimation(hostNode);
}

/**
 * @tc.name: NavigationPatternTest025
 * @tc.desc: Test AbortAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest025, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();

    hostNode->pushAnimations_.emplace_back(nullptr);
    pattern->AbortAnimation(hostNode);
}

/**
 * @tc.name: NavigationPatternTest026
 * @tc.desc: Test AbortAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest026, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();

    AnimationOption option;
    auto motion = AceType::MakeRefPtr<ResponsiveSpringMotion>(0.314f, 0.95f);
    option.SetCurve(motion);
    std::shared_ptr<AnimationUtils::Animation> adaptAnimation_ = AnimationUtils::StartAnimation(option, [&]() {});
    hostNode->popAnimations_.emplace_back(adaptAnimation_);
    pattern->AbortAnimation(hostNode);
}

/**
 * @tc.name: NavigationPatternTest027
 * @tc.desc: Test AbortAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest027, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();

    hostNode->popAnimations_.emplace_back(nullptr);
    pattern->AbortAnimation(hostNode);
}

/**
 * @tc.name: NavigationPatternTest028
 * @tc.desc: Test ApplyTopNavPathSystemBarStyleOrRestore function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest028, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    navPathList.emplace_back(std::make_pair("pageOne", nullptr));
    pattern->navigationStack_->SetNavPathList(navPathList);
    pattern->OnModifyDone();

    RefPtr<WindowManager> windowManager = nullptr;
    auto topNavPath = pattern->navigationStack_->GetTopNavPath();
    EXPECT_EQ(pattern->ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath), false);
}

/**
 * @tc.name: NavigationPatternTest029
 * @tc.desc: Test ApplyTopNavPathSystemBarStyleOrRestore function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest029, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavPathList navPathList;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navPathList.emplace_back(std::make_pair("pageOne", tempNode));
    pattern->navigationStack_->SetNavPathList(navPathList);
    pattern->OnModifyDone();

    RefPtr<WindowManager> windowManager = nullptr;
    auto topNavPath = pattern->navigationStack_->GetTopNavPath();
    EXPECT_EQ(pattern->ApplyTopNavPathSystemBarStyleOrRestore(windowManager, topNavPath), true);
}

/**
 * @tc.name: NavigationPatternTest030
 * @tc.desc: Test UpdateSystemBarStyleOnPageVisibilityChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest030, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->UpdateSystemBarStyleOnPageVisibilityChange(true);
}

/**
 * @tc.name: NavigationPatternTest031
 * @tc.desc: Test UpdateSystemBarStyleOnPageVisibilityChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest031, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->isFullPageNavigation_ = true;
    pattern->UpdateSystemBarStyleOnPageVisibilityChange(true);
}

/**
 * @tc.name: NavigationPatternTest032
 * @tc.desc: Test UpdateSystemBarStyleOnPageVisibilityChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationBranchTestNg, NavigationPatternTest032, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    auto hostNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(hostNode, nullptr);

    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->isFullPageNavigation_ = true;
    pattern->UpdateSystemBarStyleOnPageVisibilityChange(false);
}
} // namespace OHOS::Ace::NG