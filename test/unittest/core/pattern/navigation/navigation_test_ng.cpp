/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "base/json/json_util.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/animation/animator.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_content_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_stack.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr Dimension DEFAULT_NAVBAR_WIDTH = 240.0_vp;
constexpr int32_t TEST_DATA = 10;
constexpr int32_t STANDARD_INDEX = -1;
const std::string NAVIGATION_TITLE = "NavigationTestNg";
const std::string TEST_TAG = "test";
constexpr Dimension SPLIT_WIDTH = 520.0_vp;
constexpr Dimension STACK_WIDTH = 510.0_vp;
constexpr float HEIGHT = 1000.0f;
constexpr float FLOAT_260 = 260.0f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
constexpr Dimension DEFAULT_MIN_NAV_BAR_WIDTH_PER = Dimension(0.2, DimensionUnit::PERCENT);
constexpr Dimension DEFAULT_MAX_NAV_BAR_WIDTH_PER = Dimension(0.5, DimensionUnit::PERCENT);
constexpr Dimension DEFAULT_MIN_CONTENT_WIDTH_PER = Dimension(0.3, DimensionUnit::PERCENT);
constexpr Dimension TOOL_BAR_HEIGHT = 56.0_vp;
constexpr Dimension TOOL_BAR_ITEM_SAFE_INTERVAL = 8.0_vp;
constexpr Dimension TOOL_BAR_ITEM_VERTICAL_PADDING = 12.0_vp;
constexpr Dimension ICON_SIZE = 24.0_vp;
} // namespace

class NavigationTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
    static RefPtr<NavDestinationGroupNode> CreateDestination(const std::string name);
};

void NavigationTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
{
    layoutWrapper->SetActive();
    layoutWrapper->SetRootMeasureNode();
    LayoutConstraintF LayoutConstraint;
    LayoutConstraint.parentIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.percentReference = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.selfIdealSize = { width, DEFAULT_ROOT_HEIGHT };
    LayoutConstraint.maxSize = { width, DEFAULT_ROOT_HEIGHT };
    layoutWrapper->Measure(LayoutConstraint);
    layoutWrapper->Layout();
    layoutWrapper->MountToHostOnMainThread();
}

void NavigationTestNg::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
}

RefPtr<NavDestinationGroupNode> NavigationTestNg::CreateDestination(const std::string name)
{
    auto* stack = ViewStackProcessor::GetInstance();
    // navDestination node
    int32_t nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId);
    auto frameNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavDestinationPattern>(frameNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetName(name);
    auto context = AceType::MakeRefPtr<NavDestinationContext>();
    auto pathInfo = AceType::MakeRefPtr<NavPathInfo>();
    pathInfo->name_ = name;
    context->SetNavPathInfo(pathInfo);
    return frameNode;
}

struct TestProperty {
    std::optional<bool> isOn = std::nullopt;
    std::optional<Color> selectedColor = std::nullopt;
    std::optional<Color> backgroundColor = std::nullopt;
};

/**
 * @tc.name: NavigationPatternTest001
 * @tc.desc: Test REPLACE navigator.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest001, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationPatternTest002, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationPatternTest003, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationPatternTest004, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationPatternTest005, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationTestNg001, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationTestNg002, TestSize.Level1)
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
    ASSERT_NE(AceType::DynamicCast<OHOS::Ace::NG::NavBarNode>(navigationGroupNode.GetNavBarNode()), nullptr);
    navigationGroupNode.ToJsonValue(json, filter);
}

/**
 * @tc.name: NavigationTestNg003
 * @tc.desc:
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationTestNg003, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationModelTest001, TestSize.Level1)
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
HWTEST_F(NavigationTestNg, NavigationModelTest002, TestSize.Level1)
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
 * @tc.name: NavigationModelTest003
 * @tc.desc: Test NavigationModel SetHideToolBar false.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelTest003, TestSize.Level1)
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
    navigationModel.SetHideToolBar(false);
    EXPECT_EQ(navBarLayoutProperty->GetHideToolBar().value_or(false), false);
}

/**
 * @tc.name: NavigationModelTest004
 * @tc.desc: Test NavigationModel SetTitle & SetSubTitle.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelTest004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationView", true);
    navigationModel.SetSubtitle("subtitle");
    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_006
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_006, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    // init SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationPatternTest_007
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_007, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    // init SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPLIT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationPatternTest_008
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_008, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::AUTO);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    // init SetUsrNavigationMode:AUTO, expect navigationMode_:STACK after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationPatternTest_009
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_009, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::AUTO);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    geometryNode->SetContentSize(SizeF(static_cast<float>(STACK_WIDTH.ConvertToPx()), HEIGHT));
    geometryNode->SetContentOffset(OffsetF(0, 0));

    // init SetUsrNavigationMode:AUTO, expect navigationMode_:STACK after OnModifyDone
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->OnModifyDone();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationPatternTest_011
 * @tc.desc: Test Navigation OnHover
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create model, frameNode and pattern.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::AUTO);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnHover(true);
    pattern->OnHover(false);
    /**
     * @tc.steps: step2. check pattern
     * @tc.expected: pattern is not nullptr.
     */
    EXPECT_NE(pattern, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_012
 * @tc.desc: Test Navigation AddDividerHotZoneRect
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create model, frameNode.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<LayoutWrapperNode> layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    /**
     * @tc.steps: step2. create navbar frameNode.
     */
    auto navBar = FrameNode::CreateFrameNode(
        V2::NAVBAR_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<NavigationPattern>());
    ASSERT_NE(navBar, nullptr);
    navBar->MountToParent(frameNode);
    /**
     * @tc.steps: step3. create navigationPattern.
     */
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(frameNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    auto navLayoutAlgorithm = navigationPattern->CreateLayoutAlgorithm();
    ASSERT_NE(navLayoutAlgorithm, nullptr);
    layoutWrapper->SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(navLayoutAlgorithm));
    LayoutConstraintF LayoutConstraintVaildSize;
    LayoutConstraintVaildSize.selfIdealSize.SetSize(SizeF(1000000, 1000000));
    layoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(LayoutConstraintVaildSize);
    layoutWrapper->GetLayoutProperty()->UpdateContentConstraint();
    auto layoutAlgorithmWrapper = AceType::DynamicCast<LayoutAlgorithmWrapper>(layoutWrapper->GetLayoutAlgorithm());
    ASSERT_NE(layoutAlgorithmWrapper, nullptr);
    auto navigationLayoutAlgorithm =
        AceType::DynamicCast<NavigationLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    navigationPattern->AddDividerHotZoneRect();
    navigationPattern->realDividerWidth_ = 2.0f;
    navigationPattern->AddDividerHotZoneRect();
    /**
     * @tc.steps: step4. check navigationLayoutAlgorithm
     * @tc.expected: navigationLayoutAlgorithm is not nullptr.
     */
    EXPECT_NE(navigationLayoutAlgorithm, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_013
 * @tc.desc: Test Navigation HandleDrag
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create Navigation ,then get pattern.
     */
    auto pattern = AceType::MakeRefPtr<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    pattern->frameNode_ = frameNode;
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.width_ = 10.0;
    layoutConstraint.selfIdealSize.height_ = 10.0;
    layoutProperty->UpdateLayoutConstraint(layoutConstraint);
    pattern->HandleDragStart();
    pattern->HandleDragEnd();
    /**
     * @tc.steps: step2. check pattern->preNavBarWidth_.
     * @tc.expected: preNavBarWidth_ is correct.
     */
    EXPECT_EQ(pattern->preNavBarWidth_, static_cast<float>(DEFAULT_NAVBAR_WIDTH.ConvertToPx()));
    pattern->preNavBarWidth_ = 0;
    pattern->HandleDragUpdate(FLOAT_260);
    EXPECT_EQ(pattern->realNavBarWidth_, 0.0);
}

/**
 * @tc.name: NavigationPatternTest_014
 * @tc.desc: Test Navigation Measure
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create model, frameNode and pattern.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetTitle("navigationModel", false);
    navigationModel.SetNavigationStack();
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.width_ = 10.0;
    layoutConstraint.selfIdealSize.height_ = 10.0;
    navigationLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navigationLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(navigationLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. get geometryNode .
     * @tc.expected: layoutWrapper is not nullptr.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    navigationLayoutProperty->UpdateMinNavBarWidth(DEFAULT_MIN_NAV_BAR_WIDTH_PER);
    navigationLayoutProperty->UpdateMaxNavBarWidth(DEFAULT_MAX_NAV_BAR_WIDTH_PER);
    navigationLayoutProperty->UpdateMinContentWidth(DEFAULT_MIN_CONTENT_WIDTH_PER);
    navigationLayoutAlgorithm->Measure(AceType::RawPtr(layoutWrapper));
    EXPECT_NE(layoutWrapper, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_015
 * @tc.desc: Test NavigationPattern hoverEvent_.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create model, frameNode and pattern.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavigationPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    /**
     * @tc.steps: step2. get inputHub.
     * @tc.expected: hoverEvent_ is not nullptr.
     */
    auto hub = host->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto inputHub = hub->GetOrCreateInputEventHub();
    ASSERT_NE(inputHub, nullptr);
    pattern->InitDividerMouseEvent(inputHub);
    ASSERT_NE(pattern->hoverEvent_, nullptr);
    pattern->hoverEvent_->GetOnHoverEventFunc()(false);
    EXPECT_NE(pattern->hoverEvent_, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_016
 * @tc.desc: Test NavigationPattern dragEvent_.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create model, frameNode and pattern.
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = AceType::DynamicCast<NavigationPattern>(frameNode->GetPattern());
    ASSERT_NE(pattern, nullptr);
    auto host = pattern->GetHost();
    ASSERT_NE(host, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    LayoutConstraintF layoutConstraint;
    layoutConstraint.selfIdealSize.width_ = 10.0;
    layoutConstraint.selfIdealSize.height_ = 10.0;
    navigationLayoutProperty->UpdateLayoutConstraint(layoutConstraint);
    /**
     * @tc.steps: step2. get gestureHub.
     * @tc.expected: pattern is not nullptr.
     */
    auto hub = host->GetEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    pattern->InitDragEvent(gestureHub);
    ASSERT_NE(pattern->dragEvent_, nullptr);
    GestureEvent event;
    pattern->dragEvent_->GetActionStartEventFunc()(event);
    pattern->dragEvent_->GetActionUpdateEventFunc()(event);
    pattern->dragEvent_->GetActionEndEventFunc()(event);
    pattern->dragEvent_->GetActionCancelEventFunc()();
    EXPECT_NE(pattern->dragEvent_, nullptr);
}

/**
 * @tc.name: NavigationLayoutTest_001
 * @tc.desc: Test Navigation Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLayoutTest_001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();

    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationLayoutTest_002
 * @tc.desc: Test Navigation Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLayoutTest_002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();

    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationModelNGTest001
 * @tc.desc: Test Navigation Model
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNGTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();

    // ParseCommonTitle, Expect has Subtitle and Title or not
    navigationModel.ParseCommonTitle(true, true, "navigationModel", "navigationModel");
    navigationModel.ParseCommonTitle(false, false, "navigationModel", "navigationModel");
    navigationModel.SetTitle("", true);

    // SetTitleHeight:SPLIT_WIDTH
    navigationModel.SetTitleHeight(SPLIT_WIDTH);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(frameNode, nullptr);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
}

/**
 * @tc.name: NavigationModelNGTest002
 * @tc.desc: Test Navigation Model
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNGTest002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    RefPtr<PixelMap> pixMap = nullptr;
    NG::BarItem bar;
    std::vector<NG::BarItem> toolBarItems;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitleHeight(SPLIT_WIDTH);
    navigationModel.SetSubtitle("navigationModel");
    navigationModel.SetHideNavBar(true);
    navigationModel.SetBackButtonIcon("navigationModel", true, pixMap, "", "");
    navigationModel.SetHideBackButton(true);
    navigationModel.NeedSetItems();
    navigationModel.SetToolBarItems(std::move(toolBarItems));

    auto frameNode = AceType::Claim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto customNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    customNode->SetDepth(1);
    EXPECT_NE(navBarNode->GetPreToolBarNode(), nullptr);
    EXPECT_NE(static_cast<int32_t>(navBarNode->GetPreToolBarNode()->GetChildren().size()), 0);
    navBarNode->SetPreToolBarNode(customNode);
    navigationModel.SetToolBarItems(std::move(toolBarItems));
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    CHECK_NULL_VOID(titleBarNode);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    CHECK_NULL_VOID(titleBarLayoutProperty);
    EXPECT_EQ(titleBarLayoutProperty->GetTitleHeight(), SPLIT_WIDTH);
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    ASSERT_NE(navBarLayoutProperty, nullptr);
    EXPECT_TRUE(navBarLayoutProperty->GetHideBackButton());
}

/**
 * @tc.name: NavigationModelNGTest003
 * @tc.desc: Test Navigation Model
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNGTest003, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    RefPtr<PixelMap> pixMap = nullptr;
    bool isSelected = true;
    auto onChange = [&isSelected](bool select) { isSelected = select; };
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    RefPtr<AceType> customNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    ASSERT_NE(customNode, nullptr);
    navigationModel.SetCustomMenu(customNode);
    navigationModel.SetNavBarWidth(SPLIT_WIDTH);
    navigationModel.SetOnNavBarStateChange(std::move(onChange));
    navigationModel.SetNavigationMode(NavigationMode::AUTO);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetEventHub<EventHub>());
    ASSERT_NE(navigationEventHub, nullptr);
    navigationEventHub->SetOnNavBarStateChange(std::move(onChange));
    EXPECT_TRUE(isSelected);
}

/**
 * @tc.name: NavigationPatternTest_010
 * @tc.desc: Test NavigationPatternTest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest_010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation contentNode and navBarNode.
     * @tc.expected: check whether the properties is correct.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto pattern = navigation->GetPattern<NavigationPattern>();
    auto layoutProperty = pattern->GetLayoutProperty<NavigationLayoutProperty>();
    navigation->contentNode_ = contentNode;
    navigation->navBarNode_ = navBarNode;
    /**
     * @tc.steps: step2. set properties of layoutProperty, test OnModifyDone.
     * @tc.expected: check whether the properties is correct.
     */
    pattern->navigationMode_ = NavigationMode::AUTO;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
    pattern->navigationMode_ = NavigationMode::SPLIT;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
    pattern->navigationMode_ = NavigationMode::STACK;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
    pattern->navigationMode_ = NavigationMode::STACK;
    pattern->DoAnimation(NavigationMode::STACK);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    ASSERT_EQ(pattern->navigationStack_, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    /**
     * @tc.steps: step3. construct layoutWrapper and set properties of layoutProperty, test OnDirtyLayoutWrapperSwap.
     * @tc.expected: check whether the properties is correct.
     */
    auto geometryNode = navigation->geometryNode_;
    auto layout = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(AceType::WeakClaim(AceType::RawPtr(navigation)), geometryNode, layout);
    auto algorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    layoutAlgorithmWrapper->layoutAlgorithm_ = navigationLayoutAlgorithm;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.frameSizeChange = true;

    pattern->navigationMode_ = NavigationMode::SPLIT;
    layout->propVisibility_ = VisibleType::INVISIBLE;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(navigation->isModeChange_);

    layout->propVisibility_ = VisibleType::VISIBLE;
    layout->propHideNavBar_ = true;
    navigation->contentNode_ = contentNode;
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigation->contentNode_->children_.push_back(navDestination);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(navBarNode->GetLayoutProperty<NavBarLayoutProperty>()->propVisibility_, VisibleType::INVISIBLE);
}

/**
 * @tc.name: NavigationLayoutAlgorithm001
 * @tc.desc: Test NavigationPatternTest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLayoutAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation contentNode and navBarNode.
     * @tc.expected: check whether the properties is correct.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 44, []() { return AceType::MakeRefPtr<NavBarPattern>(); });

    navigation->navBarNode_ = navBarNode;
    auto geometryNode = navigation->geometryNode_;
    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(navigation), geometryNode, navigationLayoutProperty);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    /**
     * @tc.steps: step2. change properties of navigationLayoutProperty, test LayoutNavBar.
     * @tc.expected: check whether the properties is correct.
     */
    navigationLayoutProperty->propHideNavBar_ = true;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::SPLIT;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    auto navBarGeometryNode = navBarNode->geometryNode_;
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto navBarWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(navBarNode)), navBarGeometryNode, navBarLayoutProperty);
    layoutWrapper->childrenMap_[0] = navBarWrapper;
    layoutWrapper->currentChildCount_ = 1;

    navigationLayoutProperty->propHideNavBar_ = false;
    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::END;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));

    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::START;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::STACK;
    navigation->isModeChange_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navigation->isModeChange_);
    /**
     * @tc.steps: step3. set navigation->dividerNode_ change properties of navigationLayoutProperty,
     *                   test LayoutDivider.
     * @tc.expected: check whether the properties is correct.
     */
    auto dividerGeometryNode = dividerNode->geometryNode_;
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto dividerWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(dividerNode)), dividerGeometryNode, dividerLayoutProperty);
    layoutWrapper->childrenMap_[1] = dividerWrapper;
    layoutWrapper->currentChildCount_ = 2;
    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::END;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propNavBarPosition_.value(), NavBarPosition::END);
    /**
     * @tc.steps: step4. set navigation->contentNode_ change properties of navigationLayoutProperty,
     *                   test LayoutContent.
     * @tc.expected: check whether the properties is correct.
     */
    auto contentGeometryNode = contentNode->geometryNode_;
    auto contentLayoutProperty = contentNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto contentWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
        AceType::WeakClaim(AceType::RawPtr(contentNode)), contentGeometryNode, contentLayoutProperty);
    layoutWrapper->childrenMap_[2] = contentWrapper;
    layoutWrapper->currentChildCount_ = 3;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::STACK;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::STACK);

    navigationLayoutProperty->propNavigationMode_ = NavigationMode::SPLIT;
    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::END;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::SPLIT);
    ASSERT_EQ(navigationLayoutProperty->propNavBarPosition_.value(), NavBarPosition::END);
    /**
     * @tc.steps: step5. reset navigation->contentNode_ change properties of navigationLayoutProperty,
     *                   test Measure.
     * @tc.expected: check whether the properties is correct.
     */
    LayoutConstraintF constraint;
    constraint.selfIdealSize.height_ = 1000000.0f;
    constraint.selfIdealSize.width_ = 1000000.0f;
    constraint.maxSize.height_ = 1000000.0f;
    constraint.maxSize.width_ = 1000000.0f;
    navigationLayoutProperty->layoutConstraint_ = constraint;
    navigationLayoutProperty->contentConstraint_ = constraint;
    navigationLayoutProperty->propHideNavBar_ = true;

    Dimension dimension(20.0, DimensionUnit::PERCENT);
    navigationLayoutProperty->propNavBarWidth_ = dimension;

    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navigationLayoutProperty->propHideNavBar_.value());

    auto tempAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tempAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(layoutWrapper->layoutAlgorithm_, nullptr);
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::SPLIT);
    ASSERT_TRUE(navigationLayoutProperty->propHideNavBar_.value());

    navigation->contentNode_ =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 66, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationModelNG001
 * @tc.desc: Test NavigationPatternTest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG001, TestSize.Level1)
{
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        FrameNode::GetOrCreateFrameNode("dividerNode", 44, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;

    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::AUTO;

    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = 11;
    NavigationModelNG model;
    model.Create();
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::AUTO);

    navigation->navBarNode_ = nullptr;
    navBarNode = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG, 55, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 66, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto navBarContentNode = FrameNode::GetOrCreateFrameNode(
        "navBarContentNode", 77, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto toolBarNode = FrameNode::GetOrCreateFrameNode(
        "toolBarNode", 88, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });

    navBarNode->titleBarNode_ = titleBarNode;
    navBarNode->navBarContentNode_ = navBarContentNode;
    navBarNode->toolBarNode_ = toolBarNode;

    stack->reservedNodeId_ = 11;
    auto tempRegister = ElementRegister::GetInstance();
    tempRegister->nextUniqueElementId_ = 55;
    model.Create();
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::AUTO);
}

/**
 * @tc.name: NavigationModelNG005
 * @tc.desc: Test ToolbarLayoutAlgorithm::Measure
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create toolBarNode.
     */
    auto toolBarNode = NavToolbarNode::GetOrCreateToolbarNode(
        "toolBarNode", 1, []() { return AceType::MakeRefPtr<NavToolbarPattern>(); });
    ASSERT_NE(toolBarNode, nullptr);
    auto toolBarPattern = toolBarNode->GetPattern<NavToolbarPattern>();
    ASSERT_NE(toolBarPattern, nullptr);
    auto toolbarLayoutAlgorithm = AceType::MakeRefPtr<ToolbarLayoutAlgorithm>();
    ASSERT_NE(toolbarLayoutAlgorithm, nullptr);

    auto toolBarWrapper = toolBarNode->CreateLayoutWrapper();
    ASSERT_NE(toolBarWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(toolBarWrapper);
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_FALSE(toolBarNode->isNewToolbar_);

    auto toolbarContainerNode =
        FrameNode::CreateFrameNode("toolbarContainerNode", 2, AceType::MakeRefPtr<TextPattern>());
    auto toolbarContainerWrapper = toolbarContainerNode->CreateLayoutWrapper();
    toolBarNode->isNewToolbar_ = true;
    toolBarNode->toolbarContainerNode_ = toolbarContainerNode;
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_TRUE(toolBarNode->isNewToolbar_);
    /**
     * @tc.steps: step2. create child1, child2 etc.
     */
    auto child1 = FrameNode::CreateFrameNode("child1", 3, AceType::MakeRefPtr<ButtonPattern>());
    auto child2 = FrameNode::CreateFrameNode("child2", 4, AceType::MakeRefPtr<ButtonPattern>());
    auto child1Child = FrameNode::CreateFrameNode("child1Child", 5, AceType::MakeRefPtr<ButtonPattern>());
    auto child2Child = FrameNode::CreateFrameNode("child2Child", 6, AceType::MakeRefPtr<ButtonPattern>());
    auto child1Wrapper = child1->CreateLayoutWrapper();
    auto child2Wrapper = child2->CreateLayoutWrapper();
    auto child1ChildWrapper = child1Child->CreateLayoutWrapper();
    auto child2ChildWrapper = child2Child->CreateLayoutWrapper();
    toolbarContainerNode->children_.emplace_back(child1);
    toolbarContainerNode->children_.emplace_back(child2);
    auto temp = LayoutConstraintF();
    temp.selfIdealSize = OptionalSizeF(200.0f, 200.0f);
    temp.parentIdealSize = OptionalSizeF(200.0f, 200.0f);

    toolBarWrapper->GetLayoutProperty()->layoutConstraint_ = temp;
    toolBarWrapper->AppendChild(toolbarContainerWrapper);
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_TRUE(toolBarNode->isNewToolbar_);
    /**
     * @tc.steps: step3. change selfIdealSize.
     * @tc.expected: check whether the properties is correct.
     */
    temp.selfIdealSize = OptionalSizeF(0.0f, 200.0f);
    toolBarWrapper->GetLayoutProperty()->layoutConstraint_ = temp;
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_TRUE(toolBarNode->isNewToolbar_);

    temp.selfIdealSize = OptionalSizeF(200.0f, 0.0f);
    toolBarWrapper->GetLayoutProperty()->layoutConstraint_ = temp;
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_TRUE(toolBarNode->isNewToolbar_);

    child2ChildWrapper->GetGeometryNode()->frame_.rect_ = RectF(0, 0, 400.0f, 400.0f);
    toolbarContainerWrapper->AppendChild(child1Wrapper);
    toolbarContainerWrapper->AppendChild(child2Wrapper);
    child1Wrapper->AppendChild(child1ChildWrapper);
    child2Wrapper->AppendChild(child2ChildWrapper);
    temp.selfIdealSize = OptionalSizeF(200.0f, 200.0f);
    toolBarWrapper->GetLayoutProperty()->layoutConstraint_ = temp;
    toolbarLayoutAlgorithm->Measure(AceType::RawPtr(toolBarWrapper));
    ASSERT_TRUE(toolBarNode->isNewToolbar_);
}

/**
 * @tc.name: NavigationModelNG006
 * @tc.desc: Test NavigationPattern::CheckTopNavPathChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(
        ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    /**
     * @tc.steps: step2. construct failed arguments of navigationPattern->CheckTopNavPathChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    std::optional<std::pair<std::string, RefPtr<UINode>>> preTopNavPath = std::pair<std::string, RefPtr<UINode>>();
    std::optional<std::pair<std::string, RefPtr<UINode>>> newTopNavPath = std::pair<std::string, RefPtr<UINode>>();
    navigationPattern->CheckTopNavPathChange(preTopNavPath, preTopNavPath);

    preTopNavPath = std::pair<std::string, RefPtr<UINode>>();
    newTopNavPath = std::nullopt;
    auto context = PipelineContext::GetCurrentContext();
    auto stageManager = context->GetStageManager();
    auto pageNode =
        FrameNode::CreateFrameNode("1", 1, AceType::MakeRefPtr<PagePattern>(AceType::MakeRefPtr<PageInfo>()));
    stageManager->stageNode_->children_.emplace_back(pageNode);
    navigationPattern->CheckTopNavPathChange(preTopNavPath, newTopNavPath);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::AUTO);

    preTopNavPath = std::nullopt;
    newTopNavPath = std::pair<std::string, RefPtr<UINode>>();
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->CheckTopNavPathChange(preTopNavPath, newTopNavPath);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::STACK);
    /**
     * @tc.steps: step3. construct correct arguments of navigationPattern->CheckTopNavPathChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    preTopNavPath = std::pair<std::string, RefPtr<UINode>>("preTopNavDestination", preTopNavDestination);
    newTopNavPath = std::pair<std::string, RefPtr<UINode>>("newTopNavDestination", newTopNavDestination);
    navigationPattern->CheckTopNavPathChange(preTopNavPath, newTopNavPath);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::STACK);

    auto preNavDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(preNavDestinationPattern, nullptr);
    auto newNavDestinationPattern = newTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(newNavDestinationPattern, nullptr);
    preNavDestinationPattern->isOnShow_ = true;
    ASSERT_NE(preTopNavDestination->GetEventHub<NavDestinationEventHub>(), nullptr);

    navigationPattern->CheckTopNavPathChange(preTopNavPath, newTopNavPath);
    ASSERT_FALSE(preNavDestinationPattern->isOnShow_);
}

/**
 * @tc.name: NavigationToolbarTest001
 * @tc.desc: Test the old toolBar function with the new toolbar measure algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation theme to set toolbar specifications.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    navigationTheme->toolbarIconSize_ = ICON_SIZE;
    navigationTheme->menuIconSize_ = ICON_SIZE;

    /**
     * @tc.steps: step2. initialize navigation with old toolBar.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    bar.text = "text";
    bar.icon = "icon";
    bar.action = []() {};
    std::vector<NG::BarItem> toolBarItems;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolBarItems(std::move(toolBarItems));

    /**
     * @tc.steps: step3. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step4. measure and layout toolbar.
     * @tc.expected: layoutWrapper is not nullptr.
     */
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);

    /**
     * @tc.steps: step5. test whether the node of the toolbar is created after calling SetToolBarItems function.
     * @tc.expected: toolbar node and preToolbar node are not nullptr.
     */
    EXPECT_NE(navBarNode->GetToolBarNode(), nullptr);
    EXPECT_NE(navBarNode->GetPreToolBarNode(), nullptr);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest001
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize navigation with BarItem number less than five.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    bar.text = "text";
    bar.icon = "icon";
    bar.action = []() {};
    bar.status = NG::NavToolbarItemStatus::NORMAL;
    std::vector<NG::BarItem> toolBarItems;
    for (int i = 0; i < 4; i++) {
        toolBarItems.push_back(bar);
    }
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. test whether the node of the toolbar is created after calling the SetToolbarConfiguration
     * function.
     * @tc.expected: toolbar node and preToolbar node are not nullptr.
     */
    EXPECT_NE(navBarNode->GetToolBarNode(), nullptr);
    EXPECT_NE(navBarNode->GetPreToolBarNode(), nullptr);

    /**
     * @tc.steps: step4. test whether the container size is four.
     * @tc.expected: barItemSize is four.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    auto barItemSize = static_cast<int32_t>(containerNode->GetChildren().size());
    EXPECT_EQ(barItemSize, 4);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest002
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize navigation with BarItem in disable status.
     */
    NavigationModelNG navigationModel;
    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem disableBar;
    disableBar.text = "disableText";
    disableBar.icon = "disableIcon";
    disableBar.status = NG::NavToolbarItemStatus::DISABLED;
    toolBarItems.push_back(disableBar);

    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. test whether the node of the toolbar is created after calling the SetToolbarConfiguration
     * function.
     * @tc.expected: toolbar node and preToolbar node are not nullptr.
     */
    EXPECT_NE(navBarNode->GetToolBarNode(), nullptr);
    EXPECT_NE(navBarNode->GetPreToolBarNode(), nullptr);

    /**
     * @tc.steps: step4. obtain barItem node.
     * @tc.expected: barItem node is not nullptr.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    auto buttonNode = containerNode->GetChildren().front();
    EXPECT_NE(buttonNode, nullptr);
    auto barItemNode = AceType::DynamicCast<BarItemNode>(buttonNode->GetChildren().front());
    EXPECT_NE(barItemNode, nullptr);

    /**
     * @tc.steps: step5. barItem is disable.
     * @tc.expected: IsEnabled function return false.
     */
    auto itemEventHub = barItemNode->GetEventHub<BarItemEventHub>();
    EXPECT_NE(itemEventHub, nullptr);
    EXPECT_FALSE(itemEventHub->IsEnabled());
}

/**
 * @tc.name: NavigationToolbarConfigurationTest003
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize navigation with BarItem in active status.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    bar.text = "text";
    bar.icon = "icon";
    bar.action = []() {};
    bar.activeIcon = "activeIcon";
    bar.status = NG::NavToolbarItemStatus::ACTIVE;
    std::vector<NG::BarItem> toolBarItems;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. test whether the node of the toolbar is created after calling the SetToolbarConfiguration
     * function.
     * @tc.expected: toolbar node and preToolbar node are not nullptr.
     */
    EXPECT_NE(navBarNode->GetToolBarNode(), nullptr);
    EXPECT_NE(navBarNode->GetPreToolBarNode(), nullptr);

    /**
     * @tc.steps: step4. obtain barItem node.
     * @tc.expected: barItem node is not nullptr.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    auto buttonNode = containerNode->GetChildren().front();
    EXPECT_NE(buttonNode, nullptr);
    auto barItemNode = AceType::DynamicCast<BarItemNode>(buttonNode->GetChildren().front());
    EXPECT_NE(barItemNode, nullptr);

    /**
     * @tc.steps: step5. barItem is active.
     * @tc.expected: icon status is initial and barItem status is active.
     */
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    EXPECT_EQ(barItemPattern->GetToolbarItemStatus(), NavToolbarItemStatus::ACTIVE);
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::INITIAL);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest004
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize navigation with an empty toolbarItem array.
     */
    NavigationModelNG navigationModel;
    std::vector<NG::BarItem> toolBarItems;
    navigationModel.Create();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. create layoutWrapper and layout toolbar.
     * @tc.expected: layoutWrapper is not nullptr.
     */
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);

    /**
     * @tc.steps: step4. test whether the container size is zero.
     * @tc.expected:  barItemSize is zero.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    auto barItemSize = static_cast<int32_t>(containerNode->GetChildren().size());
    EXPECT_EQ(barItemSize, 0);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest005
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation theme to set toolbar specifications.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    navigationTheme->height_ = TOOL_BAR_HEIGHT;
    navigationTheme->toolbarItemSafeInterval_ = TOOL_BAR_ITEM_SAFE_INTERVAL;
    navigationTheme->toolbarItemHorizontalPadding_ = TOOL_BAR_ITEM_SAFE_INTERVAL;
    navigationTheme->toolbarItemVerticalPadding_ = TOOL_BAR_ITEM_VERTICAL_PADDING;

    /**
     * @tc.steps: step2. initialize navigation with BarItem number less than five to test.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    std::vector<NG::BarItem> toolBarItems;
    for (int i = 0; i < 4; i++) {
        toolBarItems.push_back(bar);
    }
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. create layoutWrapper and layout toolbar.
     * @tc.expected: layoutWrapper is not nullptr.
     */
    auto navigationLayoutProperty = frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);

    /**
     * @tc.steps: step4. test whether the container size is four.
     * @tc.expected:  barItemSize is four.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    EXPECT_EQ(static_cast<int32_t>(containerNode->GetChildren().size()), 4);

    /**
     * @tc.steps: step5. modify toolbar item parameters.
     */
    NG::BarItem newBar;
    std::vector<NG::BarItem> newToolBarItems;
    newToolBarItems.push_back(newBar);
    navigationModel.SetToolbarConfiguration(std::move(newToolBarItems));

    /**
     * @tc.steps: step6. test whether the container size is one after modify.
     * @tc.expected: barItemSize is one.
     */
    auto newToolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(newToolbarNode, nullptr);
    auto newTontainerNode = newToolbarNode->GetToolbarContainerNode();
    EXPECT_NE(newTontainerNode, nullptr);
    EXPECT_EQ(static_cast<int32_t>(newTontainerNode->GetChildren().size()), 1);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest006
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationToolbarConfigurationTest006, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    /**
     * @tc.steps: step1. initialize navigation with only one active BarItem.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    bar.text = "text";
    bar.icon = "icon";
    bar.action = []() {};
    bar.activeIcon = "activeIcon";
    bar.status = NG::NavToolbarItemStatus::ACTIVE;
    std::vector<NG::BarItem> toolBarItems;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    /**
     * @tc.steps: step2. obtain navigation nodes.
     * @tc.expected: nodes are not nullptr.
     */
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    EXPECT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    /**
     * @tc.steps: step3. create layoutWrapper and layout toolbar.
     * @tc.expected: layoutWrapper is not nullptr.
     */
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    RefPtr<NavigationLayoutProperty> navigationLayoutProperty =
        frameNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    SizeF value(static_cast<float>(SPLIT_WIDTH.ConvertToPx()), HEIGHT);
    navigationLayoutProperty->UpdateMarginSelfIdealSize(value);
    navigationLayoutProperty->UpdateContentConstraint();
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);

    /**
     * @tc.steps: step4. obtain barItem nodes.
     * @tc.expected: barItem node is not nullptr.
     */
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetToolBarNode());
    EXPECT_NE(toolbarNode, nullptr);
    auto containerNode = toolbarNode->GetToolbarContainerNode();
    EXPECT_NE(containerNode, nullptr);
    auto buttonNode = containerNode->GetChildren().front();
    EXPECT_NE(buttonNode, nullptr);
    auto barItemNode = AceType::DynamicCast<BarItemNode>(buttonNode->GetChildren().front());
    EXPECT_NE(barItemNode, nullptr);

    /**
     * @tc.steps: step5. barItem status can be change after UpdateBarItemActiveStatusResource.
     * @tc.expected: barItem status is changed.
     */
    auto barItemPattern = barItemNode->GetPattern<BarItemPattern>();
    barItemPattern->UpdateBarItemActiveStatusResource();
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::ACTIVE);
    barItemPattern->UpdateBarItemActiveStatusResource();
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::INITIAL);
}

/**
 * @tc.name: NavigationModelNG007
 * @tc.desc: Test NavigationPattern::CheckTopNavPathChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto narBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(narBarNode, nullptr);
    /**
     * @tc.steps: step2. construct correct arguments of navigationPattern->CheckTopNavPathChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 101, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 102, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_NE(titleBarNode, nullptr);
    narBarNode->titleBarNode_ = titleBarNode;
    preTopNavDestination->titleBarNode_ = titleBarNode;
    newTopNavDestination->titleBarNode_ = titleBarNode;
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->TransitionWithAnimation(nullptr, nullptr, false);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, nullptr, false);
    ASSERT_EQ(preTopNavDestination->transitionType_, PageTransitionType::EXIT_POP);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, false);
    ASSERT_EQ(newTopNavDestination->transitionType_, PageTransitionType::ENTER_PUSH);
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, true);
    ASSERT_EQ(preTopNavDestination->transitionType_, PageTransitionType::EXIT_POP);
}

/**
 * @tc.name: NavigationModelNG008
 * @tc.desc: Test NavigationPattern::OnNavBarStateChange
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    ASSERT_NE(AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode()), nullptr);

    /**
     * @tc.steps: step2. construct correct condition of navigationPattern->OnNavBarStateChange then call it.
     * @tc.expected: check whether the properties is correct.
     */
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = false;
    navigationPattern->OnNavBarStateChange(true);
    ASSERT_FALSE(navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_.value());

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = false;
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationStack_->Add("preTopNavDestination", preTopNavDestination);
    navigationPattern->OnNavBarStateChange(true);
    ASSERT_FALSE(navigationPattern->navigationStack_->Empty());

    navigationPattern->navBarVisibilityChange_ = false;
    navigationPattern->OnNavBarStateChange(false);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    navigationPattern->OnNavBarStateChange(false);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->OnNavBarStateChange(false);
    ASSERT_FALSE(navigationPattern->navBarVisibilityChange_);

    navigationPattern->navBarVisibilityChange_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->GetLayoutProperty<NavigationLayoutProperty>()->propHideNavBar_ = true;
    navigationPattern->OnNavBarStateChange(false);
    ASSERT_FALSE(navigationPattern->navBarVisibilityChange_);
}

/**
 * @tc.name: NavigationModelNG009
 * @tc.desc: Test NavigationPattern::OnDirtyLayoutWrapperSwap && UpdateTitleModeChangeEventHub
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    ASSERT_NE(AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode()), nullptr);
    /**
     * @tc.steps: step2. construct correct arguments of navigationPattern->OnDirtyLayoutWrapperSwap then call it.
     * @tc.expected: check whether the properties is correct.
     */
    auto dirty = navigation->CreateLayoutWrapper();
    DirtySwapConfig config;
    config.skipMeasure = false;

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 100, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationPattern->navigationStack_->Add("preTopNavDestination", preTopNavDestination);

    navigationPattern->OnDirtyLayoutWrapperSwap(dirty, config);
    /**
     * @tc.steps: step3. construct correct condition of navigationPattern->UpdateTitleModeChangeEventHub() then call it.
     * @tc.expected: check whether the properties is correct.
     */
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigation->navBarNode_);
    ASSERT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    ASSERT_NE(navBarProperty, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->titleBarNode_);
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto titleBarPattern = titleBarNode->GetPattern<TitleBarPattern>();
    ASSERT_NE(titleBarPattern, nullptr);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FULL;
    navigationPattern->UpdateTitleModeChangeEventHub(navigation);
    ASSERT_EQ(titleBarLayoutProperty->propTitleMode_.value(), NavigationTitleMode::FULL);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->titleMode_ = NavigationTitleMode::FULL;
    navigationPattern->titleMode_ = NavigationTitleMode::FREE;
    navigationPattern->UpdateTitleModeChangeEventHub(navigation);

    titleBarLayoutProperty->propTitleMode_ = NavigationTitleMode::FREE;
    titleBarPattern->titleMode_ = NavigationTitleMode::FULL;
    navigationPattern->titleMode_ = NavigationTitleMode::FULL;
    navigationPattern->UpdateTitleModeChangeEventHub(navigation);
    /**
     * @tc.steps: step3. construct correct condition of navigationPattern->UpdateContextRect() then call it.
     * @tc.expected: check whether the properties is correct.
     */
    navigationPattern->UpdateContextRect(preTopNavDestination, navigation);
    ASSERT_EQ(navBarProperty->propVisibility_.value(), VisibleType::VISIBLE);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigationPattern->UpdateContextRect(preTopNavDestination, navigation);
    ASSERT_EQ(navBarProperty->propVisibility_.value(), VisibleType::VISIBLE);
}

/**
 * @tc.name: NavigationModelNG0011
 * @tc.desc: Test NavigationModelNG::SetCustomToolBar && SetToolBarItems
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    auto customNode = FrameNode::CreateFrameNode("text", 113, AceType::MakeRefPtr<TextPattern>());
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    navBarNode->propPrevToolBarIsCustom_ = true;
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    customNode =
        FrameNode::CreateFrameNode("text", navBarNode->GetToolBarNode()->GetId(), AceType::MakeRefPtr<TextPattern>());
    model.SetCustomToolBar(customNode);
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::NONE);

    std::vector<NG::BarItem> toolBarItems;
    model.SetToolBarItems(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);

    navBarNode->preToolBarNode_ = nullptr;
    model.SetToolBarItems(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: NavigationModelNG0012
 * @tc.desc: Test NavigationModelNG::SetToolbarConfiguration
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigation->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    navBarNode->propPrevToolBarIsCustom_ = true;
    std::vector<NG::BarItem> toolBarItems;
    model.SetToolbarConfiguration(std::move(toolBarItems));
    ASSERT_EQ(navBarNode->GetToolBarNodeOperationValue(), ChildNodeOperation::REPLACE);
}

/**
 * @tc.name: NavigationModelNG0013
 * @tc.desc: Test NavigationContentLayoutAlgorithm::Measure
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 120, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto layoutWrapper = navigation->CreateLayoutWrapper();

    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 121, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationWrapper1 = navDestination->CreateLayoutWrapper();

    ASSERT_EQ(layoutWrapper->GetTotalChildCount(), 0);
    ASSERT_NE(layoutWrapper->GetLayoutProperty(), nullptr);
    ASSERT_NE(navDestinationWrapper1->GetLayoutAlgorithm(), nullptr);
    ASSERT_NE(navDestinationWrapper1->GetLayoutAlgorithm()->GetLayoutAlgorithm(), nullptr);

    auto temp1 = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    navDestinationWrapper1->layoutAlgorithm_->layoutAlgorithm_ = temp1;

    layoutWrapper->AppendChild(navDestinationWrapper1);

    NavigationContentLayoutAlgorithm algorithm;
    algorithm.Measure(AceType::RawPtr(layoutWrapper));

    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 121, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationWrapper2 = navDestination2->CreateLayoutWrapper();
    auto temp2 = AceType::MakeRefPtr<NavDestinationLayoutAlgorithm>();
    temp2->isShown_ = true;
    navDestinationWrapper2->layoutAlgorithm_->layoutAlgorithm_ = temp2;
    layoutWrapper->AppendChild(navDestinationWrapper2);
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(temp2->isShown_);
    temp1->isShown_ = true;
    algorithm.Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(temp1->isShown_);
}

/**
 * @tc.name: NavigationModelNG0014
 * @tc.desc: Test NavigationModelNG::SetBackButtonVisible  BackButtonAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestination", 123, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto backButtonNode2 = FrameNode::CreateFrameNode("backButtonNode", 126, AceType::MakeRefPtr<ButtonPattern>());
    ASSERT_NE(backButtonNode2->renderContext_, nullptr);
    navigation->BackButtonAnimation(backButtonNode2, false);
    navigation->BackButtonAnimation(backButtonNode2, true);
}

/**
 * @tc.name: NavigationModelNG0015
 * @tc.desc: Test NavigationModelNG::UpdateNavDestinationNodeWithoutMarkDirty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    /**
     * @tc.steps: step2. create navDestination.
     */
    auto navDestination1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 124, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 125, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 126, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 127, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination5 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 129, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination6 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 130, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination7 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 131, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto child8 = FrameNode::CreateFrameNode("NavDestination", 132, AceType::MakeRefPtr<ButtonPattern>());

    auto temp = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 133, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    /**
     * @tc.steps: step3. add element to navigationPattern->navigationStack_.
     */
    navigationPattern->navigationStack_->Add("navDestination1", navDestination1);
    navigationPattern->navigationStack_->Add("navDestination2", navDestination2);
    navigationPattern->navigationStack_->Add("navDestination3", navDestination3);

    auto pattern5 = navDestination5->GetPattern<NavDestinationPattern>();
    pattern5->customNode_ = AceType::RawPtr(navDestination5);

    pattern5->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 234, AceType::MakeRefPtr<ButtonPattern>()); });
    navDestination5->contentNode_ = FrameNode::CreateFrameNode("temp", 235, AceType::MakeRefPtr<ButtonPattern>());

    auto pattern6 = navDestination6->GetPattern<NavDestinationPattern>();
    pattern6->customNode_ = AceType::RawPtr(navDestination6);

    auto pattern7 = navDestination7->GetPattern<NavDestinationPattern>();
    pattern7->customNode_ = AceType::RawPtr(navDestination7);

    ASSERT_NE(navDestination7->GetPattern<NavDestinationPattern>()->GetCustomNode(), nullptr);
    /**
     * @tc.steps: step4. add element to navigationContentNode->children_.
     */
    navigationContentNode->children_.push_back(navDestination1);
    navigationContentNode->children_.push_back(navDestination4);
    navigationContentNode->children_.push_back(navDestination2);
    navigationContentNode->children_.push_back(navDestination5);
    navigationContentNode->children_.push_back(navDestination6);
    navigationContentNode->children_.push_back(navDestination7);
    navigationContentNode->children_.push_back(child8);

    navigation->UpdateNavDestinationNodeWithoutMarkDirty(temp);
}

/**
 * @tc.name: NavigationModelNG0016
 * @tc.desc: Test NavigationModelNG::GetNavDestinationNode
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;

    auto result = navigation->GetNavDestinationNode(navigationContentNode);
    ASSERT_EQ(result, nullptr);
}

/**
 * @tc.name: NavigationModelNG0017
 * @tc.desc: Test NavigationModelNG::CheckCanHandleBack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;

    auto child = FrameNode::CreateFrameNode("navigationContent", 345, AceType::MakeRefPtr<ButtonPattern>());
    navigationContentNode->children_.push_back(child);

    navigation->CheckCanHandleBack();
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::AUTO);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigation->CheckCanHandleBack();
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
    auto child2 = FrameNode::CreateFrameNode("navigationContent", 346, AceType::MakeRefPtr<ButtonPattern>());
    navigationContentNode->children_.push_back(child2);
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    navigation->CheckCanHandleBack();
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationModelNG0018
 * @tc.desc: Test NavigationModelNG::UpdateNavDestinationNodeWithoutMarkDirty
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto navigationContentNode =
        FrameNode::CreateFrameNode("navigationContent", 123, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = navigationContentNode;
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    /**
     * @tc.steps: step2. create navDestination.
     */
    auto navDestination1 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 154, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 155, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination3 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 156, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination4 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 157, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination5 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 159, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination6 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 160, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestination7 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 161, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto child8 = FrameNode::CreateFrameNode("NavDestination", 132, AceType::MakeRefPtr<ButtonPattern>());

    auto temp = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 163, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    auto pattern5 = navDestination5->GetPattern<NavDestinationPattern>();
    pattern5->customNode_ = AceType::RawPtr(navDestination5);

    pattern5->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 236, AceType::MakeRefPtr<ButtonPattern>()); });
    navDestination5->contentNode_ = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());

    auto pattern6 = navDestination6->GetPattern<NavDestinationPattern>();
    pattern6->customNode_ = AceType::RawPtr(navDestination6);

    auto pattern7 = navDestination7->GetPattern<NavDestinationPattern>();
    pattern7->customNode_ = AceType::RawPtr(temp);

    ASSERT_NE(navDestination7->GetPattern<NavDestinationPattern>()->GetCustomNode(), nullptr);
    /**
     * @tc.steps: step4. add element to navigationContentNode->children_.
     */
    navigationContentNode->children_.push_back(navDestination1);
    navigationContentNode->children_.push_back(navDestination4);
    navigationContentNode->children_.push_back(navDestination2);
    navigationContentNode->children_.push_back(navDestination5);
    navigationContentNode->children_.push_back(navDestination6);
    navigationContentNode->children_.push_back(navDestination7);
    navigationContentNode->children_.push_back(child8);

    navigation->UpdateNavDestinationNodeWithoutMarkDirty(temp);
}

/**
 * @tc.name: NavigationModelNG0019
 * @tc.desc: Test NavigationLayoutAlgorithm::IsAutoHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto property = AceType::MakeRefPtr<LayoutProperty>();
    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = CalcSize(std::nullopt, len);
    property->calcLayoutConstraint_ = std::move(calcLayoutConstraint);

    auto& test = property->GetCalcLayoutConstraint();
    ASSERT_NE(test, nullptr);
    ASSERT_TRUE(test->selfIdealSize.has_value());
    ASSERT_TRUE(test->selfIdealSize->Height().has_value());
    ASSERT_NE(test->selfIdealSize->Height().value().ToString().find("auto"), std::string::npos);

    NavigationLayoutAlgorithm algorithm;
    auto result = algorithm.IsAutoHeight(property);
    ASSERT_TRUE(result);

    len = CalcLength("");
    property->calcLayoutConstraint_->selfIdealSize = CalcSize(std::nullopt, len);
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_->selfIdealSize = CalcSize(std::nullopt, std::nullopt);
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_->selfIdealSize = std::nullopt;
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);

    property->calcLayoutConstraint_ = nullptr;
    result = algorithm.IsAutoHeight(property);
    ASSERT_FALSE(result);
}

/**
 * @tc.name: NavigationModelNG0020
 * @tc.desc: Test NavigationLayoutAlgorithm::SizeCalculationSplit
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto property = AceType::MakeRefPtr<NavigationLayoutProperty>();
    property->propHideNavBar_ = true;
    property->layoutConstraint_ = LayoutConstraintF();

    algorithm->SizeCalculationSplit(property, SizeF());
    property->propHideNavBar_ = false;
    algorithm->realNavBarWidth_ = -1.0f;
    algorithm->SizeCalculationSplit(property, SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: NavigationModelNG0021
 * @tc.desc: Test NavigationLayoutAlgorithm::CheckSizeInSplit
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto property = AceType::MakeRefPtr<NavigationLayoutProperty>();
    property->propHideNavBar_ = true;
    property->layoutConstraint_ = LayoutConstraintF();

    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->CheckSizeInSplit(0, 0, 0, 0);
    ASSERT_EQ(algorithm->realNavBarWidth_, 0.0f);

    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    algorithm->realNavBarWidth_ = 60;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetNavBarRangeFlag_);

    algorithm->userSetMinContentFlag_ = false;
    algorithm->userSetNavBarRangeFlag_ = false;
    algorithm->userSetNavBarWidthFlag_ = true;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetMinContentFlag_);

    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->realNavBarWidth_ = 0;
    algorithm->CheckSizeInSplit(50, 0, 0, 0);
    ASSERT_FALSE(algorithm->userSetNavBarWidthFlag_);

    algorithm->realNavBarWidth_ = 60;
    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->CheckSizeInSplit(100, 0, 0, 50);
    ASSERT_FALSE(algorithm->userSetNavBarWidthFlag_);

    algorithm->userSetMinContentFlag_ = true;
    algorithm->userSetNavBarRangeFlag_ = true;
    algorithm->realNavBarWidth_ = 40;
    algorithm->userSetNavBarWidthFlag_ = false;
    algorithm->CheckSizeInSplit(100, 0, 60, 50);
    ASSERT_TRUE(algorithm->userSetMinContentFlag_);
}

/**
 * @tc.name: NavigationModelNG0022
 * @tc.desc: Test NavigationLayoutAlgorithm::MeasureContentChild
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());
    navigation->contentNode_ = contentNode;
    navigation->children_.push_back(contentNode);

    auto layoutWrapper = navigation->CreateLayoutWrapper();
    auto navigationLayoutProperty = AceType::MakeRefPtr<NavigationLayoutProperty>();

    layoutWrapper->layoutProperty_ = navigationLayoutProperty;
    auto contentWrapper = contentNode->CreateLayoutWrapper();
    layoutWrapper->AppendChild(contentWrapper);
    contentNode->children_.push_back(FrameNode::CreateFrameNode("content", 456, AceType::MakeRefPtr<ButtonPattern>()));

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    algorithm->MeasureContentChild(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    ASSERT_FALSE(contentNode->children_.empty());

    std::unique_ptr<MeasureProperty> calcLayoutConstraint = std::make_unique<MeasureProperty>();
    std::optional<CalcLength> len = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = CalcSize(std::nullopt, len);
    navigationLayoutProperty->calcLayoutConstraint_ = std::move(calcLayoutConstraint);
    algorithm->MeasureContentChild(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    algorithm->MeasureNavBar(AceType::RawPtr(layoutWrapper), navigation, navigationLayoutProperty, SizeF());
    LayoutConstraintF constraint;
    constraint.selfIdealSize = OptionalSizeF(20, 20);
    navigationLayoutProperty->layoutConstraint_ = LayoutConstraintF();
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_FALSE(contentNode->children_.empty());
}

/**
 * @tc.name: NavigationModelNG0023
 * @tc.desc: Test NavigationLayoutAlgorithm::SetNavigationHeight
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());

    auto layoutWrapper = navigation->CreateLayoutWrapper();

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    SizeF size;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);

    navigationPattern->navigationStack_->Add("11", contentNode);
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::AUTO);

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::STACK);

    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    algorithm->SetNavigationHeight(AceType::RawPtr(layoutWrapper), size);
    ASSERT_EQ(navigationPattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationModelNG0025
 * @tc.desc: Test NavBarPattern::OnWindowSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG0025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation.
     */
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    auto contentNode = FrameNode::CreateFrameNode("content", 454, AceType::MakeRefPtr<ButtonPattern>());

    auto navBar =
        NavBarNode::GetOrCreateNavBarNode("navBar", 300, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    ASSERT_NE(navBar, nullptr);
    auto navBarPattern = navBar->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RESIZE);
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 301, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    ASSERT_EQ(titleBarNode->menu_, nullptr);
    navBar->titleBarNode_ = titleBarNode;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RESIZE);
    auto menu = FrameNode::CreateFrameNode("menu", 302, AceType::MakeRefPtr<ButtonPattern>());
    auto barItem = AceType::MakeRefPtr<BarItemNode>("barItem", 303);
    menu->children_.push_back(barItem);
    titleBarNode->menu_ = menu;
    barItem->isMoreItemNode_ = true;
    navBarPattern->isTitleMenuNodeShowing_ = false;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RECOVER);
    ASSERT_TRUE(barItem->isMoreItemNode_);
    barItem->isMoreItemNode_ = false;
    navBarPattern->isTitleMenuNodeShowing_ = true;
    navBarPattern->OnWindowSizeChanged(20, 20, WindowSizeChangeReason::RECOVER);
    ASSERT_FALSE(barItem->isMoreItemNode_);
}

HWTEST_F(NavigationTestNg, NavigationStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.add page A
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto stack = pattern->GetNavigationStack();
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    auto targetNode = navigationPattern->GetNavigationStack()->Get();
    ASSERT_EQ(frameNode, targetNode);

    /**
     * @tc.steps: step3. replace pageA
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Pop();
    stack->Add("C", replaceNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(replaceNode, stack->Get());
}

HWTEST_F(NavigationTestNg, NavigationStackTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.add page A
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto stack = pattern->GetNavigationStack();
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 1);

    /**
     * @tc.steps: step3. replace pageA
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 1);

    /**
     * @tc.steps: step4. push pageC
     */
    stack->Add("C", frameNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->Size(), 2);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.push A
     */
    stack->Add("C", frameNode);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step3.pop page B
     */
    stack->Remove();
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

HWTEST_F(NavigationTestNg, NavigationReplaceTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation, and set the navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    navigationModel.SetTitle("navigationModel", false);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto pattern = navigationNode->GetPattern<NavigationPattern>();
    auto stack = pattern->GetNavigationStack();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.add page A to stack
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Add("A", frameNode);
    stack->Add("A", frameNode);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    navigationPattern->SetNavigationMode(NavigationMode::STACK);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step2.replace page A in stack
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    stack->Remove();
    stack->Add("B", replaceNode);
    stack->UpdateReplaceValue(1);
    ASSERT_EQ(stack->GetReplaceValue(), 1);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);

    /**
     * @tc.steps: step3.pop page B
     */
    stack->Clear();
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    ASSERT_EQ(stack->GetReplaceValue(), 0);
}

/**
 * @tc.name: NavigationFocusTest001
 * @tc.desc: Test NavigationPattern::OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationFocusTest001, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
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

    /**
     * @tc.steps: step2. call OnDirtyLayoutWrapperSwap function while navDestination has no child or 2 children.
     * @tc.expected: check whether the defaultFocus property is correct.
     */
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(V2::NAVBAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navigationContentNode = AceType::DynamicCast<FrameNode>(frameNode->GetContentNode());
    ASSERT_NE(navigationContentNode, nullptr);
    navigationContentNode->children_.emplace_back(navDestination);
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(navigationContentNode->GetLastChild());
    ASSERT_NE(navDestinationNode, nullptr);
    auto titleBar = TitleBarNode::GetOrCreateTitleBarNode(V2::TITLE_BAR_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    navDestinationNode->titleBarNode_ = titleBar;
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navDestinationNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BUTTON_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->backButton_ = backButtonNode;
    navDestinationNode->children_.emplace_back(backButtonNode);
    navDestinationNode->children_.emplace_back(backButtonNode);
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_FALSE(backButtonNode->GetOrCreateFocusHub()->IsDefaultFocus());
}

/**
 * @tc.name: NavDestinationTest001
 * @tc.desc: Test Dialog page visibility
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavDestinationDialogTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);

    /**
     * @tc.steps: step2.push page A to navDestination
     * @tc.expected: navbar is visible,page is visible
     */
    auto navDestination = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestination->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("A", navDestination);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(pattern, nullptr);
    pattern->SetNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    auto destinationProperty = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestination->GetLayoutProperty());
    EXPECT_TRUE(destinationProperty != nullptr);
    destinationProperty->UpdateHideTitleBar(true);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationNode->GetNavBarNode());
    EXPECT_NE(navBarNode, nullptr);
    auto navBarProperty = navBarNode->GetLayoutProperty();
    EXPECT_EQ(navBarProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step2. push navdestination page B
     * @tc.expected: page A is visible, page B is visible
     */
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("B", navDestinationB);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    auto layoutPropertyB = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestinationB->GetLayoutProperty());
    EXPECT_NE(layoutPropertyB, nullptr);
    layoutPropertyB->UpdateHideTitleBar(true);
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    EXPECT_EQ(layoutPropertyB->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);

    /**
     * @tc.steps: step3. push standard page C
     * @tc.expected: page A is invisible, pageB is invisible, navBar is invisible, pageC is visible
     */
    auto navDestinationC = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() {
            return AceType::MakeRefPtr<NavDestinationPattern>();
        });
    auto layoutPropertyC = AceType::DynamicCast<NavDestinationLayoutProperty>(navDestinationC->GetLayoutProperty());
    EXPECT_NE(layoutPropertyC, nullptr);
    layoutPropertyC->UpdateHideTitleBar(true);
    navigationStack->Add("C", navDestinationC);
    pattern->OnModifyDone();
    pattern->MarkNeedSyncWithJsStack();
    pattern->SyncWithJsStackIfNeeded();
    navigationNode->hideNodes_.emplace_back(navDestination);
    PipelineContext::GetCurrentContext()->FlushBuildFinishCallbacks();
    EXPECT_EQ(layoutPropertyB->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(destinationProperty->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::INVISIBLE);
    EXPECT_EQ(layoutPropertyC->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: NavDestinationDialogTest002
 * @tc.desc: Test window lifecycle event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavDestinationDialogTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation stack
    */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    auto context = PipelineContext::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    auto taskExecutor = context->GetTaskExecutor();
    ASSERT_NE(taskExecutor, nullptr);

    /**
     * @tc.steps: step2. add pageA and pageB to navDestination
    */
    auto navDestinationA = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationA->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("A", navDestinationA);
    auto navDestinationB = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navDestinationB->SetNavDestinationMode(NavDestinationMode::DIALOG);
    navigationStack->Add("B", navDestinationB);
    navigationPattern->OnModifyDone();
    navigationPattern->MarkNeedSyncWithJsStack();
    navigationPattern->SyncWithJsStackIfNeeded();
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(navigationNode, geometryNode, navigationNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    navigationPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true, true);
    auto navDestinationPatternA = AceType::DynamicCast<NavDestinationPattern>(navDestinationA->GetPattern());
    EXPECT_NE(navDestinationPatternA, nullptr);
    auto navDestinationPatternB = AceType::DynamicCast<NavDestinationPattern>(navDestinationB->GetPattern());
    EXPECT_NE(navDestinationPatternB, nullptr);
    EXPECT_TRUE(navDestinationPatternB->GetIsOnShow());
    EXPECT_TRUE(navDestinationPatternA->GetIsOnShow());
}

/**
 * @tc.name: NavDestinationDialogTest003
 * @tc.desc: Test window lifecycle event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavDestinationDialogTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1.create navigation stack
    */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto navigationStack = AceType::MakeRefPtr<MockNavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step2. push standard page C
    */
    auto navDestinationC = NavDestinationGroupNode::GetOrCreateGroupNode(V2::NAVDESTINATION_VIEW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationStack->Add("C", navDestinationC);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(navigationNode, geometryNode, navigationNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);
    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    navigationPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    auto layoutPropertyC = navDestinationC->GetLayoutProperty();
    EXPECT_NE(layoutPropertyC, nullptr);
    EXPECT_EQ(layoutPropertyC->GetVisibilityValue(VisibleType::VISIBLE), VisibleType::VISIBLE);
}

/**
 * @tc.name: NavigationSetStackTest001
 * @tc.desc: Test setting of NavigationStack
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationSetStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();

    int numOfCreatorCall = 0;
    int numOfUpdaterCall = 0;
    RefPtr<MockNavigationStack> stack;
    auto stackCreator = [&numOfCreatorCall, &stack]() -> RefPtr<MockNavigationStack> {
        numOfCreatorCall++;
        stack = AceType::MakeRefPtr<MockNavigationStack>();
        return stack;
    };
    auto stackUpdater = [&numOfUpdaterCall, &navigationModel](RefPtr<NG::NavigationStack> stack) {
        numOfUpdaterCall++;
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };

    /**
     * @tc.steps: step1. set stack's creator and updater
     * @tc.expected: check number of function calls
     */
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    ASSERT_NE(stack, nullptr);
    ASSERT_NE(stack->GetOnStateChangedCallback(), nullptr);
    EXPECT_EQ(numOfCreatorCall, 1);
    EXPECT_EQ(numOfUpdaterCall, 3);
}

/**
 * @tc.name: NavigationNewStackTest001
 * @tc.desc: Test stack operation of Navigation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationNewStackTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2. get onStateChangedCallback
     * @tc.expected: check if callback has been setted.
     */
    RefPtr<NavigationGroupNode> navigationNode =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(navigationNode, nullptr);
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    ASSERT_NE(navigationPattern, nullptr);
    EXPECT_FALSE(navigationPattern->GetNavigationStackProvided());
    auto stack = navigationPattern->GetNavigationStack();
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
    ASSERT_NE(mockStack, nullptr);
    auto stateChangedCallback = mockStack->GetOnStateChangedCallback();
    ASSERT_NE(stateChangedCallback, nullptr);

    /**
     * @tc.steps: step2.add page A
     */
    RefPtr<FrameNode> frameNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    mockStack->Add("A", frameNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 1);

    /**
     * @tc.steps: step3. replace pageA
     */
    RefPtr<FrameNode> replaceNode = FrameNode::CreateFrameNode("temp", 245, AceType::MakeRefPtr<ButtonPattern>());
    mockStack->Remove();
    mockStack->Add("B", replaceNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 1);

    /**
     * @tc.steps: step4. push pageC
     */
    mockStack->Add("C", frameNode);
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    stateChangedCallback();
    ASSERT_TRUE(navigationPattern->NeedSyncWithJsStackMarked());
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
    ASSERT_FALSE(navigationPattern->NeedSyncWithJsStackMarked());
    ASSERT_EQ(mockStack->Size(), 2);
}

/**
 * @tc.name: NestedNavigationTest001
 * @tc.desc: Test case of nested Navigation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NestedNavigationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create NavigationStack, setup mock function
     */
    ScopedViewStackProcessor scopedViewStackProcessor;
    auto outerStack = AceType::MakeRefPtr<MockNavigationStack>();
    auto innerStack = AceType::MakeRefPtr<MockNavigationStack>();
    EXPECT_CALL(*outerStack, OnAttachToParent(_)).Times(0);
    EXPECT_CALL(*innerStack, OnAttachToParent(_)).Times(1);

    /**
     * @tc.steps: step1. create outer navigation and set stack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStackWithCreatorAndUpdater(
        [&outerStack]() -> RefPtr<MockNavigationStack> {
            return outerStack;
        }, [](RefPtr<NG::NavigationStack> stack) {
            auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
            ASSERT_NE(mockStack, nullptr);
        });
    auto groupNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(groupNode, nullptr);
    groupNode->AttachToMainTree(true);

    /**
     * @tc.steps: step2. create inner navigation and set stack
     */
    navigationModel.Create();
    navigationModel.SetNavigationStackWithCreatorAndUpdater(
        [&innerStack]() -> RefPtr<MockNavigationStack> {
            return innerStack;
        }, [](RefPtr<NG::NavigationStack> stack) {
            auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
            ASSERT_NE(mockStack, nullptr);
        });

    /**
     * @tc.steps: step3. attach navigation to main tree
     * @tc.expected: check number of NavigationStack's OnAttachToParent function calls
     */
    ViewStackProcessor::GetInstance()->Pop();
}

/*
 * @tc.name: NavigationInterceptionTest001
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<MockNavigationStack>(mockStack)]
        (const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(from, nullptr);
        ASSERT_NE(to, nullptr);
        auto info = to->GetNavPathInfo();
        ASSERT_NE(info, nullptr);
        ASSERT_EQ(info->GetName(), "A");
        ASSERT_EQ(operation, NavigationOperation::PUSH);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        ASSERT_NE(navigationStack, nullptr);
        navigationStack->Remove();
        RefPtr<FrameNode> frameNode = NavigationTestNg::CreateDestination("B");
        navigationStack->Add("B", frameNode);
        navigationStack->UpdateReplaceValue(true);
        navigationStack->UpdateAnimatedValue(true);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        EXPECT_EQ(from, nullptr);
        EXPECT_NE(to, nullptr);
        auto info = to->GetNavPathInfo();
        ASSERT_NE(info->GetName(), "B");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, false);
    });

    /**
     * @tc.steps: step3. sync navigation stack
     * @tc.expected: step3. trigger navigation interception before and after callback
     */
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest002
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2. push A to navigation stack
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<NavigationStack>(mockStack)](
        const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::POP);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        ASSERT_NE(navigationStack, nullptr);
        auto frameNode = NavigationTestNg::CreateDestination("B");
        ASSERT_NE(frameNode, nullptr);
        navigationStack->Add("B", frameNode);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        EXPECT_NE(from, nullptr);
        EXPECT_NE(to, nullptr);
        auto fromInfo = from->GetNavPathInfo();
        ASSERT_NE(fromInfo, nullptr);
        ASSERT_EQ(fromInfo->GetName(), "A");
        auto toInfo = to->GetNavPathInfo();
        ASSERT_NE(toInfo, nullptr);
        ASSERT_EQ(toInfo->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::PUSH);
        ASSERT_EQ(isAnimated, false);
    });

    /**
     * @tc.steps: step3. sync navigation stack
     * @tc.expected: step3. trigger navigation interception before and after callback
     */
    mockStack->Remove();
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest003
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2. push A to navigation stack
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    mockStack->UpdateReplaceValue(true);

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition
     */
    mockStack->SetInterceptionBeforeCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
    });

    mockStack->SetInterceptionAfterCallback([](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
    });

    /**
     * @tc.steps: step3. sync navigation stack.
     * @tc.expected: step3. trigger navigation before and after callback.
     */
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
}

/**
 * @tc.name: NavigationInterceptionTest004
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2.set navigation before and after interception during destination transition.
     *            Remove top Destination during interception before callback.
     * @tc.expected: trigger before interception and not trigger after interception.
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);
    mockStack->SetInterceptionBeforeCallback([stack = WeakPtr<NavigationStack>(mockStack)]
        (const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        ASSERT_EQ(to, nullptr);
        ASSERT_NE(from, nullptr);
        auto info = from->GetNavPathInfo();
        ASSERT_EQ(info->name_, "A");
        ASSERT_EQ(operation, NavigationOperation::REPLACE);
        ASSERT_EQ(isAnimated, true);
        auto navigationStack = stack.Upgrade();
        EXPECT_NE(navigationStack, nullptr);
        navigationStack->Remove();
    });

    uint32_t times = 0;
    mockStack->SetInterceptionAfterCallback([time = &times](const RefPtr<NavDestinationContext>& from,
        const RefPtr<NavDestinationContext>& to, NavigationOperation operation, bool isAnimated) {
        (*time)++;
    });

    /**
     * @tc.steps: step3. push destination A and sync navigation stack.
     * @tc.expected: step3. don't trigger interception after callback.times is 0.
     */
    auto frameNode = NavigationTestNg::CreateDestination("A");
    mockStack->Add("A", frameNode);
    navigationPattern->MarkNeedSyncWithJsStack();
    MockPipelineContext::GetCurrent()->GetNavigationManager()->FireNavigationUpdateCallback();
    EXPECT_EQ(times, 0);
}

/**
 * @tc.name: NavigationInterceptionTest005
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationInterceptionTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation, set NavigationStack
     */
    NavigationModelNG navigationModel;
    navigationModel.Create();
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    /**
     * @tc.steps: step2.set navigation mode change callback and set navigation width 700
     * @tc.expected: step2. trigger navigation mode callback and current mode is split
     */
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(
            ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto navigationPattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    EXPECT_NE(navigationPattern, nullptr);
    auto mockStack = AceType::DynamicCast<MockNavigationStack>(navigationPattern->GetNavigationStack());
    EXPECT_NE(mockStack, nullptr);

    mockStack->SetInterceptionModeCallback([](NavigationMode mode) {
        EXPECT_EQ(mode, NavigationMode::SPLIT);
    });
    auto layoutWrapper = navigationNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper, nullptr);
    const int32_t maxWidth = 700;
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper, maxWidth);

    /**
     * @tc.steps:step3. set navigation mode callback and set navigation width is 500
     * @tc.expected: step3.trigger current navigation mode is stack
     */
    mockStack->SetInterceptionModeCallback([](NavigationMode mode) {
        EXPECT_EQ(mode, NavigationMode::STACK);
    });
    const int32_t stackWidth = 500;
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper, stackWidth);
}

/*
 * @tc.name: NavigationPatternTest017
 * @tc.desc: Test DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest017, TestSize.Level1)
{
    NavigationPattern navigationPattern;
    navigationPattern.navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern.navigationStack_, nullptr);
    navigationPattern.DumpInfo();
}

/**
 * @tc.name: NavigationPatternTest018
 * @tc.desc: Test DumpInfo function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest018, TestSize.Level1)
{
    NavigationPattern navigationPattern;
    navigationPattern.navigationStack_ = nullptr;
    ASSERT_EQ(navigationPattern.navigationStack_, nullptr);
    navigationPattern.DumpInfo();
}

/**
 * @tc.name: NavigationPatternTest019
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest019, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isNavigationChanged = false;
    bool isFromStandard = true;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest020
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest020, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = false;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest021
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest021, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = true;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest022
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest022, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = false;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest023
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest023, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    cacheNodes.emplace_back(std::make_pair("pageOne", nullptr));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = false;
    bool isNavigationChanged = false;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest024
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest024, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = false;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = false;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest025
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest025, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = true;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest026
 * @tc.desc: Test NotifyDialogChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest026, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    EXPECT_NE(tempNode, nullptr);
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    EXPECT_NE(navDestinationPattern, nullptr);
    bool isOnShow = true;
    navDestinationPattern->SetIsOnShow(isOnShow);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    bool isFromStandard = true;
    bool isNavigationChanged = false;
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_HIDE, isNavigationChanged, isFromStandard);
}

/**
 * @tc.name: NavigationPatternTest027
 * @tc.desc: Test TriggerCustomAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest027, TestSize.Level1)
{
    NavigationPattern navigationPattern;
    bool isPopPage = true;
    EXPECT_EQ(navigationPattern.TriggerCustomAnimation(nullptr, nullptr, isPopPage), false);
}

/**
 * @tc.name: NavigationPatternTest028
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest028, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(nullptr, nullptr, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest029
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest029, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::NONE;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest030
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest030, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(preDestinationPattern, nullptr);
    preDestinationPattern->shallowBuilder_ = nullptr;
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest031
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest031, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto preDestinationPattern = preTopNavDestination->GetPattern<NavDestinationPattern>();
    ASSERT_NE(preDestinationPattern, nullptr);
    preDestinationPattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 234, AceType::MakeRefPtr<ButtonPattern>()); });
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest032
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest032, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::EXIT_POP;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest033
 * @tc.desc: Test OnCustomAnimationFinish function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest033, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    PageTransitionType type = PageTransitionType::EXIT_PUSH;
    preTopNavDestination->SetTransitionType(type);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    navigationPattern->OnCustomAnimationFinish(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest034
 * @tc.desc: Test UpdatePreNavDesZIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest034, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination);
}

/**
 * @tc.name: NavigationPatternTest035
 * @tc.desc: Test UpdatePreNavDesZIndex function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest035, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(newTopNavDestination, nullptr);
    navigationPattern->UpdatePreNavDesZIndex(preTopNavDestination, newTopNavDestination);
}

/**
 * @tc.name: NavigationPatternTest036
 * @tc.desc: Test SyncWithJsStackIfNeeded function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest036, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->needSyncWithJsStack_ = false;
    navigationPattern->SyncWithJsStackIfNeeded();
}

/**
 * @tc.name: NavigationPatternTest037
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest037, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest038
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest038, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);

    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    preTopNavDestination->SetContentNode(navigationContentNode);

    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest039
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest039, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);

    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = nullptr;
    preTopNavDestination->SetContentNode(navigationContentNode);

    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    bool isPopPage = true;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest040
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest040, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    NavDestinationMode mode = NavDestinationMode::STANDARD;
    newTopNavDestination->SetNavDestinationMode(mode);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest041
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest041, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    NavDestinationMode mode = NavDestinationMode::DIALOG;
    newTopNavDestination->SetNavDestinationMode(mode);
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest042
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest042, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    auto navigationContentNode = FrameNode::GetOrCreateFrameNode(V2::NAVIGATION_CONTENT_ETS_TAG, 12,
        []() { return AceType::MakeRefPtr<ButtonPattern>(); });
    preTopNavDestination->SetContentNode(navigationContentNode);
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest043
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest043, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto frameNode_test = AceType::MakeRefPtr<FrameNode>(V2::ROW_COMPONENT_TAG, -1, AceType::MakeRefPtr<Pattern>());
    auto parent = AceType::WeakClaim(AceType::RawPtr(frameNode_test));
    preTopNavDestination->SetParent(parent);
    preTopNavDestination->SetContentNode(nullptr);
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest044
 * @tc.desc: Test TransitionWithOutAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest044, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    bool needVisible = false;
    navigationPattern->TransitionWithOutAnimation(preTopNavDestination, newTopNavDestination, isPopPage, needVisible);
}

/**
 * @tc.name: NavigationPatternTest045
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest045, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest046
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest046, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = nullptr;
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest047
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest047, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(false);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_SHOW), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest048
 * @tc.desc: Test FireNavDestinationStateChange function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest048, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(navigationPattern->navigationStack_, nullptr);
    NavPathList cacheNodes;
    auto tempNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navDestinationPattern = tempNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->SetIsOnShow(true);
    cacheNodes.emplace_back(std::make_pair("pageOne", tempNode));
    navigationPattern->navigationStack_->SetNavPathList(cacheNodes);

    EXPECT_EQ(navigationPattern->FireNavDestinationStateChange(NavDestinationLifecycle::ON_HIDE), STANDARD_INDEX);
}

/**
 * @tc.name: NavigationPatternTest049
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest049, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = nullptr;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest050
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest050, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 44, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    navigationPattern->isCustomAnimation_ = true;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest051
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest051, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = nullptr;
    auto newTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(newTopNavDestination, nullptr);
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest052
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest052, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = nullptr;
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest053
 * @tc.desc: Test TransitionWithAnimation function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest053, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::NavigationPattern>();
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigation->SetNavBarNode(navBarNode);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    auto preTopNavDestination = NavDestinationGroupNode::GetOrCreateGroupNode(
        V2::NAVDESTINATION_VIEW_ETS_TAG, 33, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(preTopNavDestination, nullptr);
    auto newTopNavDestination = nullptr;
    navigationPattern->isCustomAnimation_ = true;
    navigationPattern->navigationMode_ = NavigationMode::STACK;
    bool isPopPage = false;
    navigationPattern->TransitionWithAnimation(preTopNavDestination, newTopNavDestination, isPopPage);
}

/**
 * @tc.name: NavigationPatternTest054
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest054, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = true;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest055
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest055, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = false;
    navigationPattern->userSetNavBarWidthFlag_ = true;
    navigationPattern->userSetNavBarRangeFlag_ = true;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest056
 * @tc.desc: Test OnHover function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest056, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->isInDividerDrag_ = false;
    navigationPattern->userSetNavBarWidthFlag_ = false;
    navigationPattern->userSetNavBarRangeFlag_ = false;
    bool isHover = false;
    navigationPattern->OnHover(isHover);
}

/**
 * @tc.name: NavigationPatternTest057
 * @tc.desc: Test AddDividerHotZoneRect function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationPatternTest057, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    navigationPattern->realDividerWidth_ = 0.0f;
    navigationPattern->AddDividerHotZoneRect();
}

/**
 * @tc.name: HandleBack001
 * @tc.desc: Test HandleBack and match all conditions of "!isOverride && !isLastChild".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, HandleBack001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    bool isLastChild = true, isOverride = true;
    EXPECT_TRUE(isLastChild && isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);

    isOverride = false;
    EXPECT_TRUE(isLastChild && !isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);

    isLastChild = false;
    EXPECT_TRUE(!isLastChild && !isOverride);
    navigationNode->HandleBack(nullptr, isLastChild, isOverride);
}

/**
 * @tc.name: HandleBack002
 * @tc.desc: Test HandleBack and match all conditions of "isLastChild &&...".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, HandleBack002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    bool isLastChild = false, isOverride = true;
    EXPECT_TRUE(!isLastChild && isOverride);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    isLastChild = true;
    EXPECT_TRUE(isLastChild && isOverride);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    EXPECT_NE(navigationPattern->GetNavigationMode(), NavigationMode::STACK);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    navigationPattern->navigationMode_ = NavigationMode::STACK;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::STACK);
    auto layoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_FALSE(layoutProperty->GetHideNavBar().value_or(false));
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    layoutProperty->propHideNavBar_ = true;
    EXPECT_TRUE(layoutProperty->GetHideNavBar().value_or(false));
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);

    navigationPattern->navigationMode_ = NavigationMode::SPLIT;
    EXPECT_EQ(navigationPattern->GetNavigationMode(), NavigationMode::SPLIT);
    navigationNode->HandleBack(navDestinationNode, isLastChild, isOverride);
}

/**
 * @tc.name: TransitionWithPop001
 * @tc.desc: Test TransitionWithPop and match all conditions of "isLastChild" and "isNavBar".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithPop001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 7, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->backButton_ = backButtonNode;
    preNode->titleBarNode_ = titleBarNode;

    RefPtr<FrameNode> curNode1 = nullptr;
    bool isNavBar = false;
    auto preTitleNode = AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode());
    ASSERT_NE(preTitleNode, nullptr);
    EXPECT_NE(preTitleNode->GetBackButton(), nullptr);
    EXPECT_EQ(curNode1, nullptr);
    EXPECT_FALSE(isNavBar);
    navigationNode->TransitionWithPop(preNode, curNode1, isNavBar);

    auto curNode2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    ASSERT_NE(curNode2, nullptr);
    auto curNavDestinationTest = AceType::DynamicCast<NavDestinationGroupNode>(curNode2);
    ASSERT_NE(curNavDestinationTest, nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNavDestinationTest->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPop(preNode, curNode2, isNavBar);

    isNavBar = true;
    auto curNode3 = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    EXPECT_TRUE(isNavBar);
    ASSERT_NE(curNode3, nullptr);
    curNode3->titleBarNode_ = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", 66, []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto navBarNodeTest = AceType::DynamicCast<NavBarNode>(curNode3);
    ASSERT_NE(navBarNodeTest, nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(navBarNodeTest->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPop(preNode, curNode3, isNavBar);
}

/**
 * @tc.name: TransitionWithPop002
 * @tc.desc: Test TransitionWithPop and match the logic of the callback as follows:
 *               shallowBuilder is true/false
 *               IsCacheNode return true/false
 *               GetContentNode return true/false
 *           In addition, the conditions GetTransitionType return true/false have been covered by the last case
 *           TransitionWithPop001, which is affected by the curNode.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithPop002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 66, AceType::MakeRefPtr<TitleBarPattern>());
    auto backButtonNode = FrameNode::CreateFrameNode(
        V2::BACK_BUTTON_ETS_TAG, 7, AceType::MakeRefPtr<ButtonPattern>());
    titleBarNode->backButton_ = backButtonNode;
    preNode->titleBarNode_ = titleBarNode;

    preNode->isCacheNode_ = true;
    auto preTitleNode = AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode());
    ASSERT_NE(preTitleNode, nullptr);
    EXPECT_NE(preTitleNode->GetBackButton(), nullptr);
    EXPECT_TRUE(preNode->IsCacheNode());
    navigationNode->TransitionWithPop(preNode, nullptr, false);

    preNode->isCacheNode_ = false;
    auto prePattern = preNode->GetPattern<NavDestinationPattern>();
    ASSERT_NE(prePattern, nullptr);
    prePattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("temp", 234, AceType::MakeRefPtr<ButtonPattern>()); });
    EXPECT_NE(prePattern->GetShallowBuilder(), nullptr);
    EXPECT_FALSE(preNode->IsCacheNode());
    EXPECT_EQ(preNode->GetContentNode(), nullptr);
    navigationNode->TransitionWithPop(preNode, nullptr, false);

    preNode->contentNode_ = FrameNode::CreateFrameNode("temp", 235, AceType::MakeRefPtr<ButtonPattern>());
    EXPECT_NE(preNode->GetContentNode(), nullptr);
    navigationNode->TransitionWithPop(preNode, nullptr, false);
}

/**
 * @tc.name: TransitionWithPush001
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is false
 *               needSetInvisible is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithPush001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = false;
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make needSetInvisible false
    auto curNode = preNode;
    ASSERT_NE(curNode, nullptr);
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithPush002
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is true
 *               needSetInvisible is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithPush002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = true;
    // Make needSetInvisible true
    auto preNode = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", 301, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 401, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;
    curNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is true
    EXPECT_TRUE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithPush003
 * @tc.desc: Test TransitionWithPush and match the logic as follows:
 *               isNavBar is false
 *               needSetInvisible is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithPush003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));
    auto titleBarNode = AceType::MakeRefPtr<TitleBarNode>("TitleBarNode", 201, AceType::MakeRefPtr<TitleBarPattern>());

    bool isNavBar = false;
    // Make needSetInvisible true
    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 302, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make preTitleNode and curTitleNode not NULL
    preNode->titleBarNode_ = titleBarNode;
    curNode->titleBarNode_ = titleBarNode;

    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(preNode->GetTitleBarNode()), nullptr);
    EXPECT_NE(AceType::DynamicCast<TitleBarNode>(curNode->GetTitleBarNode()), nullptr);
    navigationNode->TransitionWithPush(preNode, curNode, isNavBar);
}

/**
 * @tc.name: TransitionWithReplace001
 * @tc.desc: Test TransitionWithReplace and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, TransitionWithReplace001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode1 = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto curNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 3, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });

    bool isNavBar = true;
    EXPECT_NE(preNode1, nullptr);
    EXPECT_NE(curNode, nullptr);
    // Make sure isNavBar is true
    EXPECT_TRUE(isNavBar);
    navigationNode->TransitionWithReplace(preNode1, curNode, isNavBar);

    isNavBar = false;
    // Make sure isNavBar is false
    EXPECT_FALSE(isNavBar);
    // Make sure navDestination is false
    EXPECT_EQ(AceType::DynamicCast<NavDestinationGroupNode>(preNode1), nullptr);
    navigationNode->TransitionWithReplace(preNode1, curNode, isNavBar);

    auto preNode2 = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 4, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    // Make sure navDestination is true
    EXPECT_NE(AceType::DynamicCast<NavDestinationGroupNode>(preNode2), nullptr);
    navigationNode->TransitionWithReplace(preNode2, curNode, isNavBar);
}

/**
 * @tc.name: DealNavigationExit001
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return false
 *               isNavBar is false
 *               shallowBuilder is false
 *               GetContentNode is false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, DealNavigationExit001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 301, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    preNode->eventHub_ = nullptr;
    bool isNavBar = false;

    EXPECT_EQ(preNode->GetEventHub<EventHub>(), nullptr);
    EXPECT_FALSE(isNavBar);
    // Make sure navDestination is true
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_EQ(navDestinationNode->GetPattern<NavDestinationPattern>()->GetShallowBuilder(), nullptr);
    EXPECT_EQ(navDestinationNode->GetContentNode(), nullptr);
    navigationNode->DealNavigationExit(preNode, isNavBar, true);
    preNode->eventHub_ = preNode->GetPattern<NavDestinationPattern>()->CreateEventHub();
}

/**
 * @tc.name: DealNavigationExit002
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return true
 *               isNavBar is true
 *               isAnimated is false
 *               shallowBuilder is true
 *               GetContentNode is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, DealNavigationExit002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto prePattern = preNode->GetPattern<NavDestinationPattern>();
    prePattern->shallowBuilder_ = AceType::MakeRefPtr<ShallowBuilder>(
        []() { return FrameNode::CreateFrameNode("shallowBuilder", 301, AceType::MakeRefPtr<ButtonPattern>()); });
    preNode->contentNode_ = FrameNode::CreateFrameNode("button", 401, AceType::MakeRefPtr<ButtonPattern>());
    bool isNavBar = true, isAnimated = false;

    EXPECT_NE(preNode->GetEventHub<EventHub>(), nullptr);
    EXPECT_TRUE(isNavBar && !isAnimated);
    // Make sure navDestination is true
    auto navDestinationNode = AceType::DynamicCast<NavDestinationGroupNode>(preNode);
    ASSERT_NE(navDestinationNode, nullptr);
    EXPECT_NE(navDestinationNode->GetPattern<NavDestinationPattern>()->GetShallowBuilder(), nullptr);
    EXPECT_NE(navDestinationNode->GetContentNode(), nullptr);
    navigationNode->DealNavigationExit(preNode, isNavBar, isAnimated);
}

/**
 * @tc.name: DealNavigationExit003
 * @tc.desc: Test DealNavigationExit and make the logic as follows:
 *               GetEventHub return true
 *               isNavBar is true
 *               isAnimated is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, DealNavigationExit003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto preNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    bool isNavBar = true, isAnimated = true;

    EXPECT_NE(preNode->GetEventHub<EventHub>(), nullptr);
    EXPECT_TRUE(isNavBar && isAnimated);
    navigationNode->DealNavigationExit(preNode, isNavBar, isAnimated);
}

/**
 * @tc.name: UpdateNavDestinationVisibility001
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index < lastStandardIndex_
 *               GetCustomNode is remainChild
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto remainChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    navigationNode->lastStandardIndex_ = 0;
    int32_t index = 1;
    size_t destinationSize = 1;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    navDestinationPattern->customNode_ = remainChild;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_FALSE(index == static_cast<int32_t>(destinationSize) - 1);
    EXPECT_FALSE(index < navigationNode->lastStandardIndex_);
    EXPECT_TRUE(navDestinationPattern->GetCustomNode() == remainChild);
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, remainChild, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility002
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is destinationSize - 1
 *               hasChanged is true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility002, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 0;
    size_t destinationSize = 1;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_EQ(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_TRUE(CheckNeedMeasure(navDestinationNode->GetLayoutProperty()->GetPropertyChangeFlag()));
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, nullptr, index, destinationSize);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility003
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is destinationSize - 1
 *               hasChanged is false
 *               IsAutoHeight return false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility003, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 0;
    // Make index destinationSize - 1
    size_t destinationSize = 1;
    // Make hasChanged false
    navDestinationNode->GetLayoutProperty()->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_EQ(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_FALSE(CheckNeedMeasure(navDestinationNode->GetLayoutProperty()->GetPropertyChangeFlag()));
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    EXPECT_FALSE(NavigationLayoutAlgorithm::IsAutoHeight(navigationLayoutProperty));
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, nullptr, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility004
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is destinationSize - 1
 *               hasChanged is false
 *               IsAutoHeight return true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility004, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 0;
    // Make index destinationSize - 1
    size_t destinationSize = 1;
    // Make hasChanged false
    navDestinationNode->GetLayoutProperty()->propertyChangeFlag_ = PROPERTY_UPDATE_NORMAL;
    // Make IsAutoHeight return true
    auto navigationLayoutProperty = navigationNode->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->calcLayoutConstraint_ = std::make_unique<MeasureProperty>();
    auto& calcLayoutConstraint = navigationLayoutProperty->GetCalcLayoutConstraint();
    ASSERT_TRUE(calcLayoutConstraint);
    auto calcSize = CalcSize();
    calcSize.height_ = CalcLength("auto");
    calcLayoutConstraint->selfIdealSize = calcSize;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_EQ(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_FALSE(CheckNeedMeasure(navDestinationNode->GetLayoutProperty()->GetPropertyChangeFlag()));
    EXPECT_TRUE(NavigationLayoutAlgorithm::IsAutoHeight(navigationLayoutProperty));
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, nullptr, index, destinationSize);
    EXPECT_TRUE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility005
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index is less than lastStandardIndex_
 *               IsOnAnimation return true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility005, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 1;
    // Make index not destinationSize - 1
    size_t destinationSize = 1;
    // Make index less than lastStandardIndex_
    navigationNode->lastStandardIndex_ = 2;
    // Make IsOnAnimation return true
    navDestinationNode->isOnAnimation_ = true;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_NE(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_TRUE(index < navigationNode->lastStandardIndex_);
    EXPECT_TRUE(navDestinationNode->IsOnAnimation());
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, nullptr, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility006
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index is less than lastStandardIndex_
 *               IsOnAnimation return false
 *               GetIsOnShow return false
 *               GetCustomNode is remainChild
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility006, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto remainChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 1;
    // Make index not destinationSize - 1
    size_t destinationSize = 1;
    // Make index less than lastStandardIndex_
    navigationNode->lastStandardIndex_ = 2;
    // Make IsOnAnimation return false
    navDestinationNode->isOnAnimation_ = false;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    // Make GetIsOnShow return false
    navDestinationPattern->isOnShow_ = false;
    // Make GetCustomNode is remainChild
    navDestinationPattern->customNode_ = remainChild;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_NE(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_TRUE(index < navigationNode->lastStandardIndex_);
    EXPECT_FALSE(navDestinationNode->IsOnAnimation());
    EXPECT_FALSE(navDestinationPattern->GetIsOnShow());
    EXPECT_TRUE(navDestinationPattern->GetCustomNode() == remainChild);
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, remainChild, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility007
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index is less than lastStandardIndex_
 *               IsOnAnimation return false
 *               GetIsOnShow return true
 *               GetCustomNode is not remainChild
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility007, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto remainChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 1;
    // Make index not destinationSize - 1
    size_t destinationSize = 1;
    // Make index less than lastStandardIndex_
    navigationNode->lastStandardIndex_ = 2;
    // Make IsOnAnimation return false
    navDestinationNode->isOnAnimation_ = false;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    // Make GetIsOnShow return true
    navDestinationPattern->isOnShow_ = true;
    // Make GetCustomNode is not remainChild
    navDestinationPattern->customNode_ = nullptr;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_NE(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_TRUE(index < navigationNode->lastStandardIndex_);
    EXPECT_FALSE(navDestinationNode->IsOnAnimation());
    EXPECT_TRUE(navDestinationPattern->GetIsOnShow());
    EXPECT_TRUE(navDestinationPattern->GetCustomNode() != remainChild);
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, remainChild, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility008
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index is not less than lastStandardIndex_
 *               GetCustomNode is not remainChild
 *               IsOnAnimation return true
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility008, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto remainChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 1;
    // Make index not destinationSize - 1
    size_t destinationSize = 1;
    // Make index not less than lastStandardIndex_
    navigationNode->lastStandardIndex_ = 1;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    // Make GetCustomNode is not remainChild
    navDestinationPattern->customNode_ = nullptr;
    // Make IsOnAnimation return true
    navDestinationNode->isOnAnimation_ = true;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_NE(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_FALSE(index < navigationNode->lastStandardIndex_);
    EXPECT_TRUE(navDestinationPattern->GetCustomNode() != remainChild);
    EXPECT_TRUE(navDestinationNode->IsOnAnimation());
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, remainChild, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: UpdateNavDestinationVisibility009
 * @tc.desc: Test UpdateNavDestinationVisibility and make the logic as follows:
 *               index is not destinationSize - 1
 *               index is not less than lastStandardIndex_
 *               GetCustomNode is not remainChild
 *               IsOnAnimation return false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateNavDestinationVisibility009, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto navDestinationNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 201, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto remainChild = NavDestinationGroupNode::GetOrCreateGroupNode(
        "navDestinationNode", 202, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    int32_t index = 1;
    // Make index not destinationSize - 1
    size_t destinationSize = 1;
    // Make index not less than lastStandardIndex_
    navigationNode->lastStandardIndex_ = 1;
    auto navDestinationPattern = navDestinationNode->GetPattern<NavDestinationPattern>();
    // Make GetCustomNode is not remainChild
    navDestinationPattern->customNode_ = nullptr;
    // Make IsOnAnimation return false
    navDestinationNode->isOnAnimation_ = false;

    EXPECT_NE(navDestinationNode->GetEventHub<NavDestinationEventHub>(), nullptr);
    EXPECT_NE(index, static_cast<int32_t>(destinationSize) - 1);
    EXPECT_FALSE(index < navigationNode->lastStandardIndex_);
    EXPECT_TRUE(navDestinationPattern->GetCustomNode() != remainChild);
    EXPECT_FALSE(navDestinationNode->IsOnAnimation());
    bool ret = navigationNode->UpdateNavDestinationVisibility(navDestinationNode, remainChild, index, destinationSize);
    EXPECT_FALSE(ret);
}

/**
 * @tc.name: OnDetachFromMainTree001
 * @tc.desc: Test OnDetachFromMainTree and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto prePattern = navigationNode->GetPattern();
    EXPECT_NE(AceType::DynamicCast<NavigationPattern>(prePattern), nullptr);
    navigationNode->OnDetachFromMainTree(false);

    navigationNode->pattern_ = AceType::MakeRefPtr<NavDestinationPattern>();
    EXPECT_EQ(AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern()), nullptr);
    navigationNode->OnDetachFromMainTree(false);
    // Reset pattern_ or crash will happen in ~NavigationGroupNode()
    navigationNode->pattern_ = prePattern;
    ASSERT_EQ(AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern()), prePattern);
}

/**
 * @tc.name: OnAttachToMainTree001
 * @tc.desc: Test OnAttachToMainTree and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, OnAttachToMainTree001, TestSize.Level1)
{
    auto navigationNode = NavigationGroupNode::GetOrCreateGroupNode(
        "navigationNode", 101, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationPattern = navigationNode->GetPattern<NavigationPattern>();
    RefPtr<NavigationStack> navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationPattern->SetNavigationStack(std::move(navigationStack));

    auto prePattern = navigationNode->GetPattern();
    EXPECT_NE(AceType::DynamicCast<NavigationPattern>(prePattern), nullptr);
    navigationNode->OnAttachToMainTree(false);

    navigationNode->pattern_ = AceType::MakeRefPtr<NavDestinationPattern>();
    EXPECT_EQ(AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern()), nullptr);
    navigationNode->OnAttachToMainTree(false);
    // Reset pattern_ or crash will happen in ~NavigationGroupNode()
    navigationNode->pattern_ = prePattern;
    ASSERT_EQ(AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern()), prePattern);
}

/**
 * @tc.name: UpdateOldBarItems001
 * @tc.desc: Test UpdateOldBarItems and cover all conditions in for loop.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateOldBarItems001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    // Create four new BarItems with different attributes
    std::vector<NG::BarItem> toolBarItems;
    // Make newChildrenSize 4
    NG::BarItem newBar1, newBar2, newBar3, newBar4;
    newBar3.text = "text";
    newBar3.icon = "icon";
    newBar4.text = "text";
    newBar4.icon = "icon";
    toolBarItems.push_back(newBar1);
    toolBarItems.push_back(newBar2);
    toolBarItems.push_back(newBar3);
    toolBarItems.push_back(newBar4);
    // Make prevChildrenSize 4
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    EXPECT_FALSE(navBarNode->GetPrevToolBarIsCustom().value_or(false));
    // Create four old BarItemNodes with different attributes
    auto oldBar1 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 101);
    auto oldBar2 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 102);
    oldBar2->text_ = FrameNode::CreateFrameNode("text", 201, AceType::MakeRefPtr<TextPattern>());
    oldBar2->icon_ = FrameNode::CreateFrameNode("image", 301, AceType::MakeRefPtr<ImagePattern>());
    auto oldBar3 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 103);
    // Make frameNode_ not NULL or crash will happen in Pattern::OnModifyDone
    ASSERT_NE(oldBar3->pattern_, nullptr);
    oldBar3->pattern_->frameNode_ = oldBar3;
    auto oldBar4 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 104);
    oldBar4->text_ = FrameNode::CreateFrameNode("text", 202, AceType::MakeRefPtr<TextPattern>());
    oldBar4->icon_ = FrameNode::CreateFrameNode("image", 302, AceType::MakeRefPtr<ImagePattern>());
    auto preToolBarNode = navBarNode->GetPreToolBarNode();
    ASSERT_NE(preToolBarNode, nullptr);
    preToolBarNode->children_.emplace_back(oldBar1);
    preToolBarNode->children_.emplace_back(oldBar2);
    preToolBarNode->children_.emplace_back(oldBar3);
    preToolBarNode->children_.emplace_back(oldBar4);
    navigationModel.SetToolBarItems(std::move(toolBarItems));
}

/**
 * @tc.name: UpdateOldBarItems002
 * @tc.desc: Test UpdateOldBarItems and cover all conditions outside for loop.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, UpdateOldBarItems002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    // Make newChildrenSize 1
    // Mkae newBarItem not NULL
    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBar1;
    toolBarItems.push_back(newBar1);
    // Make prevChildrenSize 1
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    EXPECT_FALSE(navBarNode->GetPrevToolBarIsCustom().value_or(false));
    // Create an old BarItemNode with different attributes
    auto oldBar1 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 101);
    auto preToolBarNode = navBarNode->GetPreToolBarNode();
    ASSERT_NE(preToolBarNode, nullptr);
    preToolBarNode->children_.emplace_back(oldBar1);
    navigationModel.SetToolBarItems(std::move(toolBarItems));

    // Make newChildrenSize 2 and prevChildrenSize 1
    NG::BarItem newBar2;
    toolBarItems.push_back(newBar2);
    navigationModel.SetToolBarItems(std::move(toolBarItems));

    // Make newChildrenSize 2 and prevChildrenSize 3
    auto oldBar2 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 102);
    auto oldBar3 = AceType::MakeRefPtr<BarItemNode>(V2::BAR_ITEM_ETS_TAG, 103);
    preToolBarNode->children_.emplace_back(oldBar2);
    preToolBarNode->children_.emplace_back(oldBar3);
    navigationModel.SetToolBarItems(std::move(toolBarItems));
}

/**
 * @tc.name: SetToolbarConfiguration001
 * @tc.desc: Test SetToolbarConfiguration and cover all conditions of "GetPrevToolBarIsCustom.value_or".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetToolbarConfiguration001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    // Make GetPrevToolBarIsCustom.value_or return false
    navBarNode->propPrevToolBarIsCustom_ = false;
    EXPECT_FALSE(navBarNode->GetPrevToolBarIsCustom().value_or(false));
    auto toolbarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetPreToolBarNode());
    ASSERT_NE(toolbarNode, nullptr);
    EXPECT_EQ(toolbarNode->GetToolbarContainerNode(), nullptr);
    std::vector<NG::BarItem> toolBarItems;
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    // // Make containerNode not NULL
    toolbarNode->toolbarContainerNode_ = FrameNode::CreateFrameNode("text", 101, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(toolbarNode->GetToolbarContainerNode(), nullptr);
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    navBarNode->propPrevToolBarIsCustom_ = true;
    EXPECT_TRUE(navBarNode->GetPrevToolBarIsCustom().value_or(false));
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: SetToolbarConfiguration002
 * @tc.desc: Test SetToolbarConfiguration and cover all conditions of "LessThanAPIVersion".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetToolbarConfiguration002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    std::vector<NG::BarItem> toolBarItems;
    auto context = PipelineBase::GetCurrentContext();
    ASSERT_NE(context, nullptr);
    int32_t preVersion = context->GetMinPlatformVersion();
    context->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN) - 1;
    EXPECT_TRUE(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN));
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    context->minPlatformVersion_ = static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN) + 1;
    EXPECT_FALSE(Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN));
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
    context->minPlatformVersion_ = preVersion;
    EXPECT_EQ(preVersion, context->GetMinPlatformVersion());
}

/**
 * @tc.name: SetToolbarConfiguration003
 * @tc.desc: Test SetToolbarConfiguration and cover all conditions of "LessThanAPIVersion".
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetToolbarConfiguration003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBar1;
    toolBarItems.push_back(newBar1);
    EXPECT_TRUE(toolBarItems.size() <= MAXIMUM_TOOLBAR_ITEMS_IN_BAR);
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR];
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));
    EXPECT_TRUE(toolBarItems.size() > MAXIMUM_TOOLBAR_ITEMS_IN_BAR);
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: RegisterToolbarHotZoneEvent001
 * @tc.desc: Test RegisterToolbarHotZoneEvent and cover all conditions of the event callback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, RegisterToolbarHotZoneEvent001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR + 1];
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));
    EXPECT_TRUE(toolBarItems.size() > MAXIMUM_TOOLBAR_ITEMS_IN_BAR);
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    // Get the event callback defined in RegisterToolbarHotZoneEvent
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto toolBarNode = AceType::DynamicCast<NavToolbarNode>(navBarNode->GetPreToolBarNode());
    ASSERT_NE(toolBarNode, nullptr);
    ASSERT_FALSE(toolBarNode->children_.empty());
    auto containerNode = toolBarNode->children_.back();
    ASSERT_NE(containerNode, nullptr);
    ASSERT_FALSE(containerNode->children_.empty());
    auto toolBarItemNode = AceType::DynamicCast<FrameNode>(containerNode->children_.back());
    ASSERT_NE(toolBarItemNode, nullptr);
    auto gestureEventHub = toolBarItemNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub->clickEventActuator_, nullptr);
    auto event = gestureEventHub->clickEventActuator_->GetClickEvent();
    ASSERT_NE(event, nullptr);

    GestureEvent gestureEvent;
    EXPECT_NE(gestureEvent.GetSourceDevice(), SourceType::KEYBOARD);
    event(gestureEvent);
    gestureEvent.deviceType_ = SourceType::KEYBOARD;
    EXPECT_EQ(gestureEvent.GetSourceDevice(), SourceType::KEYBOARD);
    event(gestureEvent);
}

/**
 * @tc.name: CreateToolbarItemInContainer001
 * @tc.desc: Test CreateToolbarItemInContainer and cover all conditions (1st).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, CreateToolbarItemInContainer001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto eventHub = navigationGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = true;
    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR > 3 ? MAXIMUM_TOOLBAR_ITEMS_IN_BAR : 3];
    newBars[1].text = "";
    newBars[1].icon = "";
    newBars[1].action = []() {};
    newBars[1].status = NG::NavToolbarItemStatus::DISABLED;
    newBars[2].text = "text";
    newBars[2].icon = "icon";
    newBars[2].status = NG::NavToolbarItemStatus::ACTIVE;
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));

    EXPECT_FALSE(toolBarItems.size() > MAXIMUM_TOOLBAR_ITEMS_IN_BAR);
    EXPECT_FALSE(newBars[0].text.has_value());
    EXPECT_FALSE(newBars[0].icon.has_value());
    EXPECT_EQ(newBars[0].action, nullptr);
    EXPECT_NE(newBars[0].status, NG::NavToolbarItemStatus::DISABLED);
    EXPECT_TRUE(newBars[1].text.has_value() && newBars[1].text.value().empty());
    EXPECT_TRUE(newBars[1].icon.has_value() && newBars[1].icon.value().empty());
    EXPECT_NE(newBars[1].action, nullptr);
    EXPECT_EQ(newBars[1].status, NG::NavToolbarItemStatus::DISABLED);
    EXPECT_TRUE(newBars[2].text.has_value() && !newBars[2].text.value().empty());
    EXPECT_TRUE(newBars[2].icon.has_value() && !newBars[2].icon.value().empty());
    EXPECT_EQ(newBars[2].status, NG::NavToolbarItemStatus::ACTIVE);
    EXPECT_FALSE(newBars[2].activeIcon.has_value());
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: CreateToolbarItemInContainer002
 * @tc.desc: Test CreateToolbarItemInContainer and cover all conditions (2td).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, CreateToolbarItemInContainer002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto eventHub = navigationGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = false;
    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR > 3 ? MAXIMUM_TOOLBAR_ITEMS_IN_BAR : 3];
    newBars[0].activeIcon = "";
    newBars[0].status = NG::NavToolbarItemStatus::ACTIVE;
    newBars[1].activeIcon = "activeIcon";
    newBars[1].status = NG::NavToolbarItemStatus::ACTIVE;
    newBars[2].activeIcon = "activeIcon";
    newBars[2].icon = "";
    newBars[2].status = NG::NavToolbarItemStatus::ACTIVE;
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));

    EXPECT_EQ(newBars[0].status, NG::NavToolbarItemStatus::ACTIVE);
    EXPECT_TRUE(newBars[0].activeIcon.has_value() && newBars[0].activeIcon.value().empty());
    EXPECT_EQ(newBars[1].status, NG::NavToolbarItemStatus::ACTIVE);
    EXPECT_TRUE(newBars[1].activeIcon.has_value() && !newBars[1].activeIcon.value().empty());
    EXPECT_FALSE(newBars[1].icon.has_value());
    EXPECT_EQ(newBars[2].status, NG::NavToolbarItemStatus::ACTIVE);
    EXPECT_TRUE(newBars[2].activeIcon.has_value() && !newBars[2].activeIcon.value().empty());
    EXPECT_TRUE(newBars[2].icon.has_value() && newBars[2].icon.value().empty());
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: CreateToolbarItemInContainer003
 * @tc.desc: Test CreateToolbarItemInContainer and cover all conditions (3th).
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, CreateToolbarItemInContainer003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR > 1 ? MAXIMUM_TOOLBAR_ITEMS_IN_BAR : 1];
    newBars[0].activeIcon = "activeIcon";
    newBars[0].icon = "icon";
    newBars[0].status = NG::NavToolbarItemStatus::ACTIVE;
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));

    EXPECT_EQ(newBars[0].status, NG::NavToolbarItemStatus::ACTIVE);
    EXPECT_TRUE(newBars[0].activeIcon.has_value() && !newBars[0].activeIcon.value().empty());
    EXPECT_TRUE(newBars[0].icon.has_value() && !newBars[0].icon.value().empty());
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: BuildToolbarMoreItemNode001
 * @tc.desc: Test BuildToolbarMoreItemNode and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, BuildToolbarMoreItemNode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto eventHub = navigationGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    eventHub->enabled_ = true;
    std::vector<NG::BarItem> toolBarItems;
    NG::BarItem newBars[MAXIMUM_TOOLBAR_ITEMS_IN_BAR + 1];
    toolBarItems.insert(toolBarItems.end(), std::begin(newBars), std::end(newBars));
    EXPECT_TRUE(eventHub->IsEnabled());
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));

    eventHub->enabled_ = false;
    EXPECT_FALSE(eventHub->IsEnabled());
    navigationModel.SetToolbarConfiguration(std::move(toolBarItems));
}

/**
 * @tc.name: ParseCommonTitle001
 * @tc.desc: Test ParseCommonTitle and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, ParseCommonTitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    bool hasSubTitle = true, hasMainTitle = true, ignoreMainTitle = false;
    navBarNode->propPrevTitleIsCustom_ = false;
    EXPECT_TRUE(hasSubTitle && hasMainTitle);
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(false));
    EXPECT_FALSE(ignoreMainTitle);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);

    // Make mainTitle true
    titleBarNode->title_ = FrameNode::CreateFrameNode("title", 101, AceType::MakeRefPtr<TextPattern>());
    // Make subTitle true
    titleBarNode->subtitle_ = FrameNode::CreateFrameNode("subTitle", 102, AceType::MakeRefPtr<TextPattern>());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetTitle()), nullptr);
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetSubtitle()), nullptr);
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);

    // Make !hasMainTitle true
    hasMainTitle = false;
    EXPECT_TRUE(hasSubTitle && !hasMainTitle);
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);

    hasMainTitle = true;
    ignoreMainTitle = true;
    // Make !hasSubTitle true
    hasSubTitle = false;
    EXPECT_TRUE(!hasSubTitle && hasMainTitle);
    EXPECT_TRUE(ignoreMainTitle);
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);
}

/**
 * @tc.name: ParseCommonTitle002
 * @tc.desc: Test ParseCommonTitle and make the logic as follows:
 *               1. GetPrevTitleIsCustomValue return false
 *               2. GetPrevTitleIsCustomValue return true
 *                  HasTitleHeight reutrn false
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, ParseCommonTitle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    bool hasSubTitle = true, hasMainTitle = true, ignoreMainTitle = false;
    // Make GetPrevTitleIsCustomValue return false
    navBarNode->propPrevTitleIsCustom_ = false;
    EXPECT_TRUE(hasSubTitle && hasMainTitle);
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(false));
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);

    // Make GetPrevTitleIsCustomValue return true
    navBarNode->propPrevTitleIsCustom_ = true;
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);

    // Make GetPrevTitleIsCustomValue return true
    navBarNode->propPrevTitleIsCustom_ = true;
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    // Make HasTitleHeight return true
    titleBarLayoutProperty->propTitleHeight_ = Dimension();
    EXPECT_TRUE(titleBarLayoutProperty->HasTitleHeight());
    navigationModel.ParseCommonTitle(hasSubTitle, hasMainTitle, "", "", ignoreMainTitle);
}

/**
 * @tc.name: SetCustomTitle001
 * @tc.desc: Test SetCustomTitle and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetCustomTitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    // Make GetPrevTitleIsCustomValue return false
    navBarNode->propPrevTitleIsCustom_ = false;
    titleBarNode->title_ = nullptr;
    auto customTitle = FrameNode::CreateFrameNode("customTitle", 101, AceType::MakeRefPtr<TextPattern>());
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(false));
    navigationModel.SetCustomTitle(customTitle);

    // Make GetPrevTitleIsCustomValue return true
    navBarNode->propPrevTitleIsCustom_ = true;
    titleBarNode->title_ = FrameNode::CreateFrameNode("title", 102, AceType::MakeRefPtr<TextPattern>());
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    navigationModel.SetCustomTitle(customTitle);

    // Make GetPrevTitleIsCustomValue return true
    navBarNode->propPrevTitleIsCustom_ = true;
    // Make GetId return GetId
    titleBarNode->title_ = customTitle;
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    navigationModel.SetCustomTitle(customTitle);
}

/**
 * @tc.name: SetTitleHeight001
 * @tc.desc: Test SetTitleHeight and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetTitleHeight001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    EXPECT_NE(titleBarLayoutProperty, nullptr);

    bool isValid = false;
    EXPECT_FALSE(isValid);
    navigationModel.SetTitleHeight(Dimension(), isValid);

    // Make !isValid true
    isValid = true;
    EXPECT_TRUE(isValid);
    navigationModel.SetTitleHeight(Dimension(), isValid);
}

/**
 * @tc.name: SetTitleMode001
 * @tc.desc: Test SetTitleMode and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetTitleMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto navigationEventHub = navigationGroupNode->GetEventHub<EventHub>();
    ASSERT_NE(navigationEventHub, nullptr);

    // Make !IsEnabled return false
    navigationEventHub->enabled_ = true;
    EXPECT_FALSE(titleBarLayoutProperty->GetTitleHeight().has_value());
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton()), nullptr);
    EXPECT_TRUE(navigationEventHub->IsEnabled());
    navigationModel.SetTitleMode(NavigationTitleMode::MINI);

    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->backButton_);
    ASSERT_NE(backButtonNode, nullptr);
    auto gestureEventHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub->clickEventActuator_, nullptr);
    auto event = gestureEventHub->clickEventActuator_->GetClickEvent();
    ASSERT_NE(event, nullptr);
    GestureEvent gestureEvent;
    event(gestureEvent);

    // Make !IsEnabled return true
    navigationEventHub->enabled_ = false;
    titleBarNode->backButton_ = nullptr;
    EXPECT_EQ(AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton()), nullptr);
    EXPECT_FALSE(navigationEventHub->IsEnabled());
    navigationModel.SetTitleMode(NavigationTitleMode::MINI);
}

/**
 * @tc.name: SetTitleMode002
 * @tc.desc: Test SetTitleMode and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetTitleMode002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    NavigationTitleMode mode = NavigationTitleMode::MINI;
    // Make backButtonNode not nullptr
    titleBarNode->backButton_ = FrameNode::CreateFrameNode("button", 101, AceType::MakeRefPtr<ButtonPattern>());
    EXPECT_NE(AceType::DynamicCast<FrameNode>(titleBarNode->GetBackButton()), nullptr);
    navigationModel.SetTitleMode(mode);

    // Make mode not MINI
    mode = NavigationTitleMode::FREE;
    EXPECT_NE(mode, NavigationTitleMode::MINI);
    navigationModel.SetTitleMode(mode);

    // Make has_value return true
    titleBarLayoutProperty->propTitleHeight_ = Dimension();
    EXPECT_TRUE(titleBarLayoutProperty->GetTitleHeight().has_value());
    navigationModel.SetTitleMode(mode);
}

/**
 * @tc.name: SetTitleMode003
 * @tc.desc: Test SetTitleMode and cover all conditions outside the clickCallback.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetTitleMode003, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);
    auto navigationEventHub = navigationGroupNode->GetEventHub<EventHub>();

    NavigationTitleMode mode = NavigationTitleMode::MINI;
    navigationEventHub->enabled_ = true;
    EXPECT_FALSE(titleBarLayoutProperty->GetTitleHeight().has_value());
    EXPECT_EQ(titleBarNode->GetBackButton(), nullptr);
    EXPECT_EQ(mode, NavigationTitleMode::MINI);
    EXPECT_TRUE(navigationEventHub->IsEnabled());
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);

    navigationEventHub->enabled_ = false;
    titleBarNode->backButton_ = nullptr;
    EXPECT_EQ(titleBarNode->GetBackButton(), nullptr);
    EXPECT_FALSE(navigationEventHub->IsEnabled());
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);

    EXPECT_NE(titleBarNode->GetBackButton(), nullptr);
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);

    mode = NavigationTitleMode::FREE;
    EXPECT_NE(mode, NavigationTitleMode::MINI);
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);

    titleBarLayoutProperty->propTitleHeight_ = Dimension();
    EXPECT_TRUE(titleBarLayoutProperty->GetTitleHeight().has_value());
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);
}

/**
 * @tc.name: SetTitleMode004
 * @tc.desc: Test SetTitleMode and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetTitleMode004, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);

    NavigationTitleMode mode = NavigationTitleMode::MINI;
    EXPECT_EQ(titleBarNode->GetBackButton(), nullptr);
    NavigationModelNG::SetTitleMode(&(*frameNode), mode);

    auto backButtonNode = AceType::DynamicCast<FrameNode>(titleBarNode->backButton_);
    ASSERT_NE(backButtonNode, nullptr);
    auto gestureEventHub = backButtonNode->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureEventHub->clickEventActuator_, nullptr);
    auto event = gestureEventHub->clickEventActuator_->GetClickEvent();
    ASSERT_NE(event, nullptr);
    GestureEvent gestureEvent;
    event(gestureEvent);
}

/**
 * @tc.name: SetHideNavBar001
 * @tc.desc: Test SetHideNavBar and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetHideNavBar001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    EXPECT_FALSE(navigationLayoutProperty->GetHideNavBar().has_value());
    navigationModel.SetHideNavBar(false);

    navigationLayoutProperty->propHideNavBar_ = false;
    EXPECT_TRUE(navigationLayoutProperty->GetHideNavBar().has_value());
    navigationModel.SetHideNavBar(false);
}

/**
 * @tc.name: SetHideNavBar002
 * @tc.desc: Test SetHideNavBar and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetHideNavBar002, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);
    auto navigationLayoutProperty = navigationGroupNode->GetLayoutProperty<NavigationLayoutProperty>();
    ASSERT_NE(navigationLayoutProperty, nullptr);

    EXPECT_FALSE(navigationLayoutProperty->GetHideNavBar().has_value());
    NavigationModelNG::SetHideNavBar(&(*frameNode), false);

    navigationLayoutProperty->propHideNavBar_ = false;
    EXPECT_TRUE(navigationLayoutProperty->GetHideNavBar().has_value());
    NavigationModelNG::SetHideNavBar(&(*frameNode), false);
}

/**
 * @tc.name: SetCustomMenu001
 * @tc.desc: Test SetCustomMenu and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetCustomMenu001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);

    auto customNode = FrameNode::CreateFrameNode("menu", 101, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    EXPECT_EQ(navBarNode->GetMenu(), nullptr);
    navigationModel.SetCustomMenu(customNode);

    navBarNode->menu_ = FrameNode::CreateFrameNode("menu", 102, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(navBarNode->GetMenu(), nullptr);
    EXPECT_NE(customNode->GetId(), navBarNode->GetMenu()->GetId());
    navigationModel.SetCustomMenu(customNode);

    EXPECT_EQ(customNode->GetId(), navBarNode->GetMenu()->GetId());
    navigationModel.SetCustomMenu(customNode);
}

/**
 * @tc.name: SetNavBarWidth001
 * @tc.desc: Test SetNavBarWidth and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetNavBarWidth001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navigationPattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    Dimension value = 250.0_vp;
    navigationPattern->initNavBarWidthValue_ = value;
    // Make GetInitNavBarWidth return value
    EXPECT_EQ(navigationPattern->GetInitNavBarWidth(), value);
    navigationModel.SetNavBarWidth(value);

    // Make GetInitNavBarWidth return not value
    navigationPattern->initNavBarWidthValue_ = 200.0_vp;
    EXPECT_NE(navigationPattern->GetInitNavBarWidth(), value);
    navigationModel.SetNavBarWidth(value);
}

/**
 * @tc.name: SetNavigationStack001
 * @tc.desc: Test SetNavigationStack and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetNavigationStack001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto pattern = navigationGroupNode->GetPattern<NavigationPattern>();
    ASSERT_NE(pattern, nullptr);

    pattern->navigationStack_ = nullptr;
    EXPECT_EQ(pattern->GetNavigationStack(), nullptr);
    navigationModel.SetNavigationStack();

    EXPECT_NE(pattern->GetNavigationStack(), nullptr);
    navigationModel.SetNavigationStack();

    pattern->navigationStack_ = nullptr;
    EXPECT_EQ(pattern->GetNavigationStack(), nullptr);
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigationModel.SetNavigationStack(navigationStack);

    EXPECT_NE(pattern->GetNavigationStack(), nullptr);
    navigationModel.SetNavigationStack(navigationStack);

    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [](RefPtr<NG::NavigationStack> stack) {
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    pattern->navigationStack_ = nullptr;
    EXPECT_EQ(pattern->GetNavigationStack(), nullptr);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);

    EXPECT_NE(pattern->GetNavigationStack(), nullptr);
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
}

/**
 * @tc.name: SetSubtitle001
 * @tc.desc: Test SetSubtitle and cover all conditions.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, SetSubtitle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitle("navigationModel", false);

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleBarNode = AceType::DynamicCast<TitleBarNode>(navBarNode->GetTitleBarNode());
    ASSERT_NE(titleBarNode, nullptr);
    auto titleBarLayoutProperty = titleBarNode->GetLayoutProperty<TitleBarLayoutProperty>();
    ASSERT_NE(titleBarLayoutProperty, nullptr);

    navBarNode->propPrevTitleIsCustom_ = false;
    EXPECT_FALSE(navBarNode->GetPrevTitleIsCustomValue(false));
    EXPECT_EQ(titleBarNode->GetSubtitle(), nullptr);
    NavigationModelNG::SetSubtitle(&(*frameNode), "");

    navBarNode->propPrevTitleIsCustom_ = true;
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    EXPECT_FALSE(titleBarLayoutProperty->HasTitleHeight());
    EXPECT_NE(titleBarNode->GetSubtitle(), nullptr);
    NavigationModelNG::SetSubtitle(&(*frameNode), "");

    navBarNode->propPrevTitleIsCustom_ = true;
    titleBarLayoutProperty->propTitleHeight_ = Dimension();
    EXPECT_TRUE(navBarNode->GetPrevTitleIsCustomValue(false));
    EXPECT_TRUE(titleBarLayoutProperty->HasTitleHeight());
    NavigationModelNG::SetSubtitle(&(*frameNode), "");
}

/**
 * @tc.name: NavigationLoadPage001
 * @tc.desc: Test navigation page load success or not.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLoadPage001, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationNode, nullptr);
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto navigationStack = pattern->GetNavigationStack();

    /**
     * @tc.steps:step2. set navigation route add add pageOne to navigation stack
     */
    auto route = AceType::MakeRefPtr<MockNavigationRoute>("");
    EXPECT_NE(route, nullptr);
    MockContainer::Current()->SetNavigationRoute(route);
    std::string name = "pageOne";
    navigationStack->Push(name, 0);

    /**
     * @tc.steps: step3. load pageOne
     * @tc.expected: step3. navigationRoute names size is one
     */
    EXPECT_NE(pattern, nullptr);
    pattern->UpdateNavPathList();
    EXPECT_EQ(route->GetPageNames().size(), 1);

    /**
     * @tc.steps: step4. push pageOne
     * @tc.expected: step4. navigation route name size is one
     */
    navigationStack->Push("pageOne", 1);
    pattern->UpdateNavPathList();
    EXPECT_EQ(route->GetPageNames().size(), 1);
}

/**
 * @tc.name: NavigationLoadPage002
 * @tc.desc: Test navigation page load success or not.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLoadPage002, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationNode, nullptr);
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto navigationStack = pattern->GetNavigationStack();

    /**
     * @tc.steps:step2. set navigation route add add error page to navigation stack
     */
    auto route = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(route);
    navigationStack->Push("error", 0);

    /**
     * @tc.steps: step3. load pageOne
     * @tc.expected: step3. navigationRoute names size is zero
     */
    EXPECT_NE(pattern, nullptr);
    pattern->UpdateNavPathList();
    EXPECT_EQ(route->GetPageNames().size(), 0);
}

/**
 * @tc.name: NavigationLoadPage003
 * @tc.desc: Test navigation page load success or not.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLoadPage003, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationNode, nullptr);
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto navigationStack = pattern->GetNavigationStack();

    /**
     * @tc.steps:step2. set navigation route add add pageOne to navigation stack
     */
    auto route = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(route);
    navigationStack->Push("error", 0);

    /**
     * @tc.steps: step3. create pageOne destination
     * @tc.expected: step3. navigation name is empty
     */
    EXPECT_NE(pattern, nullptr);
    auto destinationNode = AceType::DynamicCast<FrameNode>(pattern->GenerateUINodeByIndex(0));
    EXPECT_NE(destinationNode, nullptr);
    auto destinationPattern = AceType::DynamicCast<NavDestinationPattern>(destinationNode->GetPattern());
    EXPECT_NE(destinationPattern, nullptr);
    EXPECT_TRUE(destinationPattern->GetName().empty());
}

/**
 * @tc.name: NavigationLoadPage004
 * @tc.desc: Test navigation page load success or not.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationLoadPage004, TestSize.Level1)
{
    /**
     * @tc.steps:step1. create navigation node and set navigation stack
     */
    MockPipelineContextGetTheme();
    NavigationModelNG navigationModel;
    navigationModel.Create();

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto navigationNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationNode, nullptr);
    auto stackCreator = []() -> RefPtr<MockNavigationStack> {
        return AceType::MakeRefPtr<MockNavigationStack>();
    };
    auto stackUpdater = [&navigationModel](RefPtr<NG::NavigationStack> stack) {
        navigationModel.SetNavigationStackProvided(false);
        auto mockStack = AceType::DynamicCast<MockNavigationStack>(stack);
        ASSERT_NE(mockStack, nullptr);
    };
    navigationModel.SetNavigationStackWithCreatorAndUpdater(stackCreator, stackUpdater);
    auto pattern = AceType::DynamicCast<NavigationPattern>(navigationNode->GetPattern());
    auto navigationStack = pattern->GetNavigationStack();

    /**
     * @tc.steps:step2. set navigation route add add pageOne to navigation stack add push pageOne
     */
    auto route = AceType::MakeRefPtr<MockNavigationRoute>("");
    MockContainer::Current()->SetNavigationRoute(route);
    navigationStack->Push("pageOne", 0);

    /**
     * @tc.steps: step3. create pageOne destination
     * @tc.expected: step3. navdestination name is pageOne
     */
    auto destinationNode = AceType::DynamicCast<FrameNode>(pattern->GenerateUINodeByIndex(0));
    EXPECT_NE(destinationNode, nullptr);
    auto destinationPattern = AceType::DynamicCast<NavDestinationPattern>(destinationNode->GetPattern());
    EXPECT_NE(destinationPattern, nullptr);
    EXPECT_EQ(destinationPattern->GetName(), "pageOne");
}
} // namespace OHOS::Ace::NG
