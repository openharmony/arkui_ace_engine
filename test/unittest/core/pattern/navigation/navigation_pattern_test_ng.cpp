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

#define protected public
#define private public
#include "base/ressched/ressched_report.h"
#include "base/perfmonitor/perf_monitor.h"
#include "test/mock/base/mock_task_executor.h"
#include "core/components/button/button_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/pattern/button/button_pattern.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/navigation/bar_item_node.h"
#include "core/components_ng/pattern/navigation/bar_item_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/title_bar_pattern.h"
#include "core/components_ng/pattern/navigation/tool_bar_layout_algorithm.h"
#include "core/components_ng/pattern/navigation/tool_bar_node.h"
#include "core/components_ng/pattern/navigation/tool_bar_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#include "test/mock/core/common/mock_container.h"

using namespace testing;
using namespace testing::ext;
namespace OHOS::Ace::NG {
namespace {
const InspectorFilter filter;
constexpr Dimension DEFAULT_NAVBAR_WIDTH = 240.0_vp;
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

RefPtr<NavigationBarTheme> CreateAndBindNavigationBarTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto navigationTheme = AceType::MakeRefPtr<NavigationBarTheme>();
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(navigationTheme));
    EXPECT_CALL(*themeManager, GetTheme(_, _)).WillRepeatedly(Return(navigationTheme));
    return navigationTheme;
}
} // namespace

class NavigationPatternTestNg : public testing::Test {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    void MockPipelineContextGetTheme();
    static void RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width = DEFAULT_ROOT_WIDTH);
};

void NavigationPatternTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
}

void NavigationPatternTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void NavigationPatternTestNg::RunMeasureAndLayout(RefPtr<LayoutWrapperNode>& layoutWrapper, float width)
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

void NavigationPatternTestNg::MockPipelineContextGetTheme()
{
    CreateAndBindNavigationBarTheme();
}

/**
 * @tc.name: NavigationPatternTest_006
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_006, TestSize.Level1)
{
    MockPipelineContextGetTheme();
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationPatternTest_007
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_007, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPLIT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationPatternTest_008
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_008, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationPatternTest_009
 * @tc.desc: Test Navigation DoAnimation
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_009, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK after OnModifyDone
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->OnModifyDone();
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:STACK in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    auto layoutWrapper3 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper3, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:AUTO, expect navigationMode_:SPILT in SPLIT_WIDTH case after OnModifyDone
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::AUTO);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    pattern->OnModifyDone();
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper3, static_cast<float>(SPLIT_WIDTH.ConvertToPx()));
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationPatternTest_011
 * @tc.desc: Test Navigation OnHover
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_011, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_012, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_013, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_014, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_015, TestSize.Level1)
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
    auto hub = host->GetOrCreateEventHub<EventHub>();
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
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_016, TestSize.Level1)
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
    auto hub = host->GetOrCreateEventHub<EventHub>();
    ASSERT_NE(hub, nullptr);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    ASSERT_NE(gestureHub, nullptr);
    pattern->InitDividerPanEvent(gestureHub);
    ASSERT_NE(pattern->panEvent_, nullptr);
    GestureEvent event;
    pattern->panEvent_->GetActionStartEventFunc()(event);
    pattern->panEvent_->GetActionUpdateEventFunc()(event);
    pattern->panEvent_->GetActionEndEventFunc()(event);
    pattern->panEvent_->GetActionCancelEventFunc()();
    EXPECT_NE(pattern->panEvent_, nullptr);
}

/**
 * @tc.name: NavigationLayoutTest_001
 * @tc.desc: Test Navigation Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationLayoutTest_001, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationModel.SetUsrNavigationMode(NavigationMode::STACK);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);
}

/**
 * @tc.name: NavigationLayoutTest_002
 * @tc.desc: Test Navigation Measure and Layout
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationLayoutTest_002, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);

    // SetUsrNavigationMode:SPLIT, expect navigationMode_:SPLIT
    navigationModel.SetUsrNavigationMode(NavigationMode::SPLIT);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    auto layoutWrapper1 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper1, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper1);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::SPLIT);

    // SetUsrNavigationMode:STACK, expect navigationMode_:STACK
    navigationLayoutProperty->UpdateUsrNavigationMode(NavigationMode::STACK);
    pattern->SetNavigationMode(NavigationMode::AUTO);
    auto layoutWrapper2 = frameNode->CreateLayoutWrapper();
    ASSERT_NE(layoutWrapper2, nullptr);
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper2);
    EXPECT_EQ(pattern->navigationMode_, NavigationMode::STACK);
}

/**
 * @tc.name: NavigationModelNGTest001
 * @tc.desc: Test Navigation Model
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationModelNGTest001, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationModelNGTest002, TestSize.Level1)
{
    NavigationModelNG navigationModel;
    RefPtr<PixelMap> pixMap = nullptr;
    NG::BarItem bar;
    std::vector<NG::BarItem> toolBarItems;
    std::vector<std::string> nameList;
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    ImageOption imageOption;
    nameList.push_back("");
    nameList.push_back("");
    imageOption.isValidImage = true;
    imageOption.noPixMap = true;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetTitleHeight(SPLIT_WIDTH);
    navigationModel.SetSubtitle("navigationModel");
    navigationModel.SetHideNavBar(true);
    navigationModel.SetBackButtonIcon(iconSymbol, "navigationModel", imageOption, pixMap, nameList);
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
    ASSERT_NE(titleBarLayoutProperty->GetBackIconSymbol(), nullptr);
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
HWTEST_F(NavigationPatternTestNg, NavigationModelNGTest003, TestSize.Level1)
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
    auto navigationEventHub = AceType::DynamicCast<NavigationEventHub>(frameNode->GetOrCreateEventHub<EventHub>());
    ASSERT_NE(navigationEventHub, nullptr);
    navigationEventHub->SetOnNavBarStateChange(std::move(onChange));
    EXPECT_TRUE(isSelected);
}

/**
 * @tc.name: NavigationPatternTest_010
 * @tc.desc: Test NavigationPatternTest
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_010, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationLayoutAlgorithm001, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationModelNG001, TestSize.Level1)
{
    auto elementRegister = ElementRegister::GetInstance();
    auto navigationUniqueId = elementRegister->MakeUniqueId();
    auto navigation = NavigationGroupNode::GetOrCreateGroupNode(
        V2::NAVIGATION_VIEW_ETS_TAG, navigationUniqueId, []() { return AceType::MakeRefPtr<NavigationPattern>(); });
    auto navigationStack = AceType::MakeRefPtr<NavigationStack>();
    navigation->GetPattern<NavigationPattern>()->SetNavigationStack(std::move(navigationStack));
    auto contentNode = NavDestinationGroupNode::GetOrCreateGroupNode(
        "NavDestination", elementRegister->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<NavDestinationPattern>(); });
    auto navBarNode = NavBarNode::GetOrCreateNavBarNode(
        "navBarNode", elementRegister->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto dividerNode = FrameNode::GetOrCreateFrameNode(
        "dividerNode", elementRegister->MakeUniqueId(), []() { return AceType::MakeRefPtr<DividerPattern>(); });
    navigation->navBarNode_ = navBarNode;
    navigation->contentNode_ = contentNode;
    navigation->dividerNode_ = dividerNode;

    auto navigationLayoutProperty = navigation->GetLayoutProperty<NavigationLayoutProperty>();
    navigationLayoutProperty->propNavigationMode_ = NavigationMode::AUTO;

    auto* stack = ViewStackProcessor::GetInstance();
    stack->reservedNodeId_ = navigationUniqueId;
    NavigationModelNG model;
    model.Create();
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::AUTO);

    navigation->navBarNode_ = nullptr;
    navBarNode = NavBarNode::GetOrCreateNavBarNode(
        V2::NAVBAR_ETS_TAG, elementRegister->MakeUniqueId(), []() { return AceType::MakeRefPtr<NavBarPattern>(); });
    auto titleBarNode = TitleBarNode::GetOrCreateTitleBarNode(
        "titleBarNode", elementRegister->MakeUniqueId(), []() { return AceType::MakeRefPtr<TitleBarPattern>(); });
    auto navBarContentNode = FrameNode::GetOrCreateFrameNode(
        "navBarContentNode", elementRegister->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    auto toolBarNode = FrameNode::GetOrCreateFrameNode(
        "toolBarNode", elementRegister->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<LinearLayoutPattern>(false); });

    navBarNode->titleBarNode_ = titleBarNode;
    navBarNode->contentNode_ = navBarContentNode;
    navBarNode->toolBarNode_ = toolBarNode;

    stack->reservedNodeId_ = navigationUniqueId;
    model.Create();
    ASSERT_EQ(navigationLayoutProperty->propNavigationMode_.value(), NavigationMode::AUTO);
}

/**
 * @tc.name: NavigationModelNG005
 * @tc.desc: Test ToolbarLayoutAlgorithm::Measure
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationModelNG005, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(toolBarWrapper);
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
HWTEST_F(NavigationPatternTestNg, NavigationModelNG006, TestSize.Level1)
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
    ASSERT_NE(preTopNavDestination->GetOrCreateEventHub<NavDestinationEventHub>(), nullptr);

    navigationPattern->CheckTopNavPathChange(preTopNavPath, newTopNavPath);
    ASSERT_FALSE(preNavDestinationPattern->isOnShow_);
}

/**
 * @tc.name: NavigationToolbarTest001
 * @tc.desc: Test the old toolBar function with the new toolbar measure algorithm.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationToolbarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation theme to set toolbar specifications.
     */
    auto navigationTheme = CreateAndBindNavigationBarTheme();
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);

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
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest001, TestSize.Level1)
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
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest002, TestSize.Level1)
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
    auto itemEventHub = barItemNode->GetOrCreateEventHub<BarItemEventHub>();
    EXPECT_NE(itemEventHub, nullptr);
    EXPECT_FALSE(itemEventHub->IsEnabled());
}

/**
 * @tc.name: NavigationToolbarConfigurationTest003
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest003, TestSize.Level1)
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
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    bar.activeIconSymbol = iconSymbol;
    bar.iconSymbol = iconSymbol;
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
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::ACTIVE);
    EXPECT_NE(barItemPattern->GetActiveIconSymbol(), nullptr);
    EXPECT_NE(barItemPattern->GetInitialIconSymbol(), nullptr);
}

/**
 * @tc.name: NavigationToolbarConfigurationTest004
 * @tc.desc: Test the SetToolbarConfiguration function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest004, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);

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
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create navigation theme to set toolbar specifications.
     */
    auto navigationTheme = CreateAndBindNavigationBarTheme();
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);

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
HWTEST_F(NavigationPatternTestNg, NavigationToolbarConfigurationTest006, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper);

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
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::INITIAL);
    barItemPattern->UpdateBarItemActiveStatusResource();
    EXPECT_EQ(barItemPattern->GetCurrentIconStatus(), ToolbarIconStatus::ACTIVE);
}

/**
 * @tc.name: NavigationModelNG009
 * @tc.desc: Test NavigationPattern::OnDirtyLayoutWrapperSwap && UpdateTitleModeChangeEventHub
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationModelNG009, TestSize.Level1)
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
 * @tc.name: NavigationFocusTest001
 * @tc.desc: Test NavigationPattern::OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationFocusTest001, TestSize.Level1)
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
 * @tc.name: NavDestinationDialogTest002
 * @tc.desc: Test window lifecycle event
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavDestinationDialogTest002, TestSize.Level1)
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
    navigationPattern->NotifyDialogChange(NavDestinationLifecycle::ON_SHOW, true);
    auto navDestinationPatternA = AceType::DynamicCast<NavDestinationPattern>(navDestinationA->GetPattern());
    EXPECT_NE(navDestinationPatternA, nullptr);
    auto navDestinationPatternB = AceType::DynamicCast<NavDestinationPattern>(navDestinationB->GetPattern());
    EXPECT_NE(navDestinationPatternB, nullptr);
    EXPECT_TRUE(navDestinationPatternB->GetIsOnShow());
    EXPECT_TRUE(navDestinationPatternA->GetIsOnShow());
}

/**
 * @tc.name: NavigationInterceptionTest005
 * @tc.desc: Test navigation interception
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationInterceptionTest005, TestSize.Level1)
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
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper, maxWidth);

    /**
     * @tc.steps:step3. set navigation mode callback and set navigation width is 500
     * @tc.expected: step3.trigger current navigation mode is stack
     */
    mockStack->SetInterceptionModeCallback([](NavigationMode mode) {
        EXPECT_EQ(mode, NavigationMode::STACK);
    });
    const int32_t stackWidth = 500;
    NavigationPatternTestNg::RunMeasureAndLayout(layoutWrapper, stackWidth);
}

/**
 * @tc.name: NavigationSetSymbolMenusTest001
 * @tc.desc: Test the SetMenuItems function
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationSetSymbolMenusTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. initialize navigation with BarItem in active status.
     */
    NavigationModelNG navigationModel;
    NG::BarItem bar;
    bar.text = "text";
    bar.icon = "icon";
    bar.action = []() {};
    auto onApply = [](WeakPtr<NG::FrameNode> frameNode) {
        auto node = frameNode.Upgrade();
        EXPECT_NE(node, nullptr);
    };
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = onApply;
    bar.iconSymbol = iconSymbol;
    std::vector<NG::BarItem> toolBarItems;
    toolBarItems.push_back(bar);
    navigationModel.Create();
    navigationModel.SetNavigationStack();
    navigationModel.SetMenuItems(std::move(toolBarItems));

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

    auto navBarPattern = navBarNode->GetPattern<NavBarPattern>();
    ASSERT_NE(navBarPattern, nullptr);

    auto navBarMenus = navBarPattern->GetTitleBarMenuItems();
    ASSERT_NE(navBarMenus.size(), 0);

    auto navBarItem = navBarMenus.front();
    ASSERT_NE(navBarItem.iconSymbol, nullptr);
}

/**
 * @tc.name: NavigationPatternTest_017
 * @tc.desc: Test OnLanguageConfigurationUpdate function.
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_017, TestSize.Level1)
{
    NavigationModelNG model;
    model.Create();
    model.SetNavigationStack();
    auto navigation =
        AceType::DynamicCast<NavigationGroupNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(navigation, nullptr);
    auto navigationPattern = navigation->GetPattern<NavigationPattern>();
    ASSERT_NE(navigationPattern, nullptr);

    /**
     * @tc.steps: step1. set to RightToLeft mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the pattern->isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    navigationPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(navigationPattern->isRightToLeft_, true);

    /**
     * @tc.steps: step2. set to LeftToRight mode, call OnLanguageConfigurationUpdate, then get current isRightToLeft_.
     * @tc.expected: check whether the pattern->isRightToLeft_ is correct.
     */
    AceApplicationInfo::GetInstance().isRightToLeft_ = false;
    navigationPattern->OnLanguageConfigurationUpdate();
    EXPECT_EQ(navigationPattern->isRightToLeft_, false);
}

/**
 * @tc.name: NavigationPatternTest_018
 * @tc.desc: Test Ability_or_page_switch and report to RSS
 * @tc.type: FUNC
 */
HWTEST_F(NavigationPatternTestNg, NavigationPatternTest_018, TestSize.Level1)
{
    EXPECT_NE(ResSchedReport::GetInstance().keyEventCountMS, 156);
    PerfMonitor::GetPerfMonitor()->Start("ABILITY_OR_PAGE_SWITCH", PerfActionType::UNKNOWN_ACTION, "");
    ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_start");
    EXPECT_EQ(ResSchedReport::GetInstance().keyEventCountMS, 156);

    ResSchedReport::GetInstance().keyEventCountMS = -1;
    EXPECT_NE(ResSchedReport::GetInstance().keyEventCountMS, 156);
    PerfMonitor::GetPerfMonitor()->End("ABILITY_OR_PAGE_SWITCH", PerfActionType::UNKNOWN_ACTION);
    ResSchedReport::GetInstance().ResSchedDataReport("ability_or_page_switch_end");
    EXPECT_EQ(ResSchedReport::GetInstance().keyEventCountMS, 156);
    EXPECT_NE(ResSchedReport::GetInstance().loadPageOn_, true);
    ResSchedReport::GetInstance().TriggerModuleSerializer();
    EXPECT_EQ(ResSchedReport::GetInstance().loadPageOn_, true);
}
} // namespace OHOS::Ace::NG