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

#include "gtest/gtest.h"

#define protected public
#define private public
#include "base/json/json_util.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/custom/custom_node.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/navigation/nav_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/nav_bar_node.h"
#include "core/components_ng/pattern/navigation/nav_bar_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/components_ng/pattern/navigation/navigation_layout_property.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_layout_property.h"
#include "core/components_ng/pattern/navigation/title_bar_node.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigator/navigator_event_hub.h"
#include "core/components_ng/pattern/navigator/navigator_pattern.h"
#include "core/components_ng/pattern/navrouter/navdestination_group_node.h"
#include "core/components_ng/pattern/navrouter/navdestination_layout_algorithm.h"
#include "core/components_ng/pattern/navrouter/navdestination_model.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
#include "core/components_ng/pattern/navrouter/navdestination_pattern.h"
#include "core/components_ng/pattern/navrouter/navrouter_event_hub.h"
#include "core/components_ng/pattern/navrouter/navrouter_group_node.h"
#include "core/components_ng/pattern/navrouter/navrouter_model.h"
#include "core/components_ng/pattern/navrouter/navrouter_model_ng.h"
#include "core/components_ng/pattern/navrouter/navrouter_pattern.h"
#include "core/components_ng/pattern/stack/stack_layout_algorithm.h"
#include "core/components_ng/pattern/stack/stack_layout_property.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TEST_DATA = 10;
const std::string NAVIGATION_TITLE = "NavigationTestNg";
const std::string TEST_TAG = "test";
constexpr Dimension SPLIT_WIDTH = 520.0_vp;
constexpr Dimension STACK_WIDTH = 510.0_vp;
constexpr float HEIGHT = 1000.0f;
constexpr float DEFAULT_ROOT_HEIGHT = 800.f;
constexpr float DEFAULT_ROOT_WIDTH = 480.f;
} // namespace

class NavigationTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapper>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
};

void NavigationTestNg::SetUpTestSuite()
{
    MockPipelineBase::SetUp();
}

void NavigationTestNg::TearDownTestSuite()
{
    MockPipelineBase::TearDown();
}

void NavigationTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapper>& layoutWrapper, float width)
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
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<NavigationBarTheme>()));
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
    NavigationModelNG navigationModel;
    navigationModel.Create();
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
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
    ASSERT_NE(layoutWrapper, nullptr);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    std::vector<DirtySwapConfig> configValue;
    configValue.push_back(config);
    config.skipLayout = false;
    configValue.push_back(config);
    config.skipMeasure = false;
    configValue.push_back(config);
    config.skipLayout = true;
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
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(frameNode, geometryNode, frameNode->GetLayoutProperty());
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
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    auto res = navigationGroupNode.GetFrameNode(TEST_TAG, nodeId);
    EXPECT_EQ(res, nullptr);
    navigationGroupNode.GetOrCreateGroupNode(TEST_TAG, nodeId, nullptr);
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
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    std::unique_ptr<JsonValue> json = JsonUtil::Create(true);
    json->isRoot_ = true;
    ASSERT_NE(json, nullptr);
    RefPtr<NavBarNode> navBarNode = AceType::MakeRefPtr<OHOS::Ace::NG::NavBarNode>(TEST_TAG, nodeId, patternCreator);
    navigationGroupNode.SetNavBarNode(navBarNode);
    ASSERT_NE(AceType::DynamicCast<OHOS::Ace::NG::NavBarNode>(navigationGroupNode.GetNavBarNode()), nullptr);
    navigationGroupNode.ToJsonValue(json);
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
    navigationModel.SetTitle("NavigationTestNg", false);
    int32_t nodeId = TEST_DATA;
    auto patternCreator = AceType::MakeRefPtr<OHOS::Ace::NG::Pattern>();
    NavigationGroupNode navigationGroupNode(TEST_TAG, nodeId, patternCreator);
    RefPtr<FrameNode> frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->Finish());
    RefPtr<NavigationPattern> pattern = frameNode->GetPattern<NavigationPattern>();
    navigationGroupNode.pattern_ = pattern;
    ASSERT_NE(AceType::DynamicCast<NavigationPattern>(navigationGroupNode.GetPattern()), nullptr);
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
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    navigationModel.SetTitle("navigationModel", false);
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    auto frameNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(frameNode, nullptr);
    auto navigationGroupNode = AceType::DynamicCast<NavigationGroupNode>(frameNode);
    ASSERT_NE(navigationGroupNode, nullptr);
    auto navBarNode = AceType::DynamicCast<NavBarNode>(navigationGroupNode->GetNavBarNode());
    ASSERT_NE(navBarNode, nullptr);
    auto titleNode = navBarNode->GetTitle();
    ASSERT_NE(titleNode, nullptr);
    auto subTitleNode = navBarNode->GetSubtitle();
    ASSERT_NE(subTitleNode, nullptr);
    navigationModel.SetTitle("navigationView", false);
    auto newSubTitleNode = navBarNode->GetSubtitle();
    ASSERT_EQ(newSubTitleNode, nullptr);
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
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
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
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper4 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper4, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper4, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
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
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

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
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
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
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    navigationModel.SetNavBarPosition(NavBarPosition::START);
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
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
    RefPtr<FrameNode> frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

    NavigationTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
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
    navigationModel.SetTitleHeight(SPLIT_WIDTH);
    navigationModel.SetSubtitle("navigationModel");
    navigationModel.SetHideNavBar(true);
    navigationModel.SetBackButtonIcon("navigationModel", true, pixMap);
    navigationModel.SetHideBackButton(true);
    navigationModel.NeedSetItems();
    navigationModel.SetToolBarItems(std::move(toolBarItems));

    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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
    layoutProperty->propDestinationChange_ = false;
    pattern->GetTitleBarRenderContext();
    ASSERT_FALSE(layoutProperty->propDestinationChange_.value());

    layoutProperty->propDestinationChange_ = true;
    pattern->GetTitleBarRenderContext();
    ASSERT_TRUE(layoutProperty->propDestinationChange_.value());

    pattern->navigationMode_ = NavigationMode::AUTO;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::AUTO);
    pattern->navigationMode_ = NavigationMode::SPLIT;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
    pattern->navigationMode_ = NavigationMode::STACK;
    pattern->DoAnimation(NavigationMode::AUTO);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::STACK);
    pattern->navigationMode_ = NavigationMode::STACK;
    pattern->DoAnimation(NavigationMode::STACK);
    ASSERT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    ASSERT_EQ(pattern->navigationStack_, nullptr);
    pattern->navigationStack_ = AceType::MakeRefPtr<NavigationStack>();
    ASSERT_NE(pattern->navigationStack_, nullptr);
    pattern->preNavPathList_.emplace_back(std::make_pair("test3", tempNode));
    pattern->navPathList_.emplace_back(std::make_pair("test", tempNode));
    pattern->navPathList_.emplace_back(std::make_pair("test4", tempNode));
    pattern->navigationStack_->navPathList_.emplace_back(std::make_pair("test", tempNode));
    pattern->navigationStack_->navPathList_.emplace_back(std::make_pair("test3", nullptr));
    pattern->navigationStack_->navPathList_.emplace_back(std::make_pair("test2", nullptr));
    pattern->OnModifyDone();

    pattern->navPathList_.clear();
    pattern->navigationStack_->navPathList_.clear();
    pattern->navPathList_.emplace_back(std::make_pair("test", nullptr));
    pattern->navigationStack_->navPathList_.emplace_back(std::make_pair("test2", nullptr));
    pattern->navigationStack_->navPathList_.emplace_back(std::make_pair("test", tempNode));
    pattern->OnModifyDone();
    /**
     * @tc.steps: step3. construct layoutWrapper and set properties of layoutProperty, test OnDirtyLayoutWrapperSwap.
     * @tc.expected: check whether the properties is correct.
     */
    auto geometryNode = navigation->geometryNode_;
    auto layout = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(AceType::WeakClaim(AceType::RawPtr(navigation)), geometryNode, layout);
    auto algorithm = AceType::MakeRefPtr<LayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(algorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    auto navigationLayoutAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    layoutAlgorithmWrapper->layoutAlgorithm_ = navigationLayoutAlgorithm;
    navigationLayoutAlgorithm->navigationMode_ = NavigationMode::SPLIT;

    DirtySwapConfig config;
    config.skipMeasure = false;
    config.frameSizeChange = true;

    layout->propUsrNavigationMode_ = NavigationMode::AUTO;
    pattern->navigationMode_ = NavigationMode::SPLIT;
    layout->propVisibility_ = VisibleType::INVISIBLE;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_FALSE(navigation->isModeChange_);

    layout->propVisibility_ = VisibleType::VISIBLE;
    navigationLayoutAlgorithm->navigationMode_ = NavigationMode::SPLIT;
    layout->propHideNavBar_ = true;
    pattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    ASSERT_EQ(navBarNode->GetLayoutProperty<NavBarLayoutProperty>()->propVisibility_.value(), VisibleType::GONE);
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
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        "navigation", 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", 22, []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 33, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 44, []() { return AceType::MakeRefPtr<NavBarPattern>(); });

    navigation->navBarNode_ = navBarNode;
    auto geometryNode = navigation->geometryNode_;
    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        AceType::WeakClaim(AceType::RawPtr(navigation)), geometryNode, navigationLayoutProperty);

    auto algorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    /**
     * @tc.steps: step2. change properties of navigationLayoutProperty, test LayoutNavBar.
     * @tc.expected: check whether the properties is correct.
     */
    navigationLayoutProperty->propHideNavBar_ = true;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::SPLIT;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    navigation->children_.push_back(navBarNode);
    ASSERT_EQ(navigation->children_.size(), 1);
    auto navBarGeometryNode = navBarNode->geometryNode_;
    auto navBarLayoutProperty = navBarNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto navBarWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        AceType::WeakClaim(AceType::RawPtr(navBarNode)), navBarGeometryNode, navBarLayoutProperty);
    layoutWrapper->childrenMap_[0] = navBarWrapper;
    layoutWrapper->currentChildCount_ = 1;

    navigationLayoutProperty->propHideNavBar_ = false;
    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::END;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));

    navigationLayoutProperty->propNavBarPosition_ = NavBarPosition::START;
    navigationLayoutProperty->propDestinationChange_ = true;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::STACK;
    navigation->isModeChange_ = true;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_TRUE(navigation->isModeChange_);
    /**
     * @tc.steps: step3. set navigation->dividerNode_ change properties of navigationLayoutProperty,
     *                   test LayoutDivider.
     * @tc.expected: check whether the properties is correct.
     */
    navigation->dividerNode_ = dividerNode;
    navigation->children_.push_back(dividerNode);
    ASSERT_EQ(navigation->children_.size(), 2);
    auto dividerGeometryNode = dividerNode->geometryNode_;
    auto dividerLayoutProperty = dividerNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto dividerWrapper = AceType::MakeRefPtr<LayoutWrapper>(
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
    navigation->contentNode_ = contentNode;
    navigation->children_.push_back(contentNode);
    ASSERT_EQ(navigation->children_.size(), 3);
    auto contentGeometryNode = contentNode->geometryNode_;
    auto contentLayoutProperty = contentNode->GetLayoutProperty<NavBarLayoutProperty>();
    auto contentWrapper = AceType::MakeRefPtr<LayoutWrapper>(
        AceType::WeakClaim(AceType::RawPtr(contentNode)), contentGeometryNode, contentLayoutProperty);
    layoutWrapper->childrenMap_[2] = contentWrapper;
    layoutWrapper->currentChildCount_ = 3;
    navigationLayoutProperty->propDestinationChange_ = true;
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::STACK;
    algorithm->Layout(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::STACK);
    ASSERT_EQ(navigationLayoutProperty->propDestinationChange_.value(), true);

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

    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::SPLIT;
    algorithm->navigationMode_ = NavigationMode::SPLIT;
    algorithm->usrNavigationMode_ = NavigationMode::SPLIT;
    auto tempAlgorithm = AceType::MakeRefPtr<NavigationLayoutAlgorithm>();
    auto layoutAlgorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tempAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_NE(layoutWrapper->layoutAlgorithm_, nullptr);
    ASSERT_EQ(algorithm->navigationMode_, NavigationMode::SPLIT);
    ASSERT_EQ(algorithm->usrNavigationMode_, NavigationMode::SPLIT);
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::SPLIT);
    ASSERT_TRUE(navigationLayoutProperty->propHideNavBar_.value());

    navigation->contentNode_ =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 66, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    navigationLayoutProperty->propUsrNavigationMode_ = NavigationMode::STACK;
    navigationLayoutProperty->propDestinationChange_ = false;
    algorithm->Measure(AceType::RawPtr(layoutWrapper));
    ASSERT_EQ(navigationLayoutProperty->propDestinationChange_.value(), false);
    ASSERT_EQ(algorithm->navigationMode_, NavigationMode::STACK);
    ASSERT_EQ(algorithm->usrNavigationMode_, NavigationMode::STACK);
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::STACK);
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
 * @tc.name: NavigationModelNG002
 * @tc.desc: Test NavigationPatternTest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationTestNg, NavigationModelNG002, TestSize.Level1)
{
    auto title = CustomNode::CreateCustomNode(11, "customNode");
    auto navBarNode =
        NavBarNode::GetOrCreateNavBarNode("navBarNode", 22, []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, 11, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navBarNode->title_ = title;

    NavigationModelNG model;
    model.SetTitle("title");
    ASSERT_EQ(navBarNode->propTitleNodeOperation_.value(), ChildNodeOperation::REPLACE);
}
} // namespace OHOS::Ace::NG
