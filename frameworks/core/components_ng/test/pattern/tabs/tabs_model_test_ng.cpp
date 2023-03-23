/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

#define private public
#define protected public

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_model_ng.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/components_ng/pattern/tabs/tabs_pattern.h"
#include "core/components_ng/test/mock/rosen/mock_canvas.h"
#include "core/components_ng/test/mock/theme/mock_theme_manager.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/pipeline_ng/test/mock/mock_pipeline_base.h"

using namespace testing;
using namespace testing::ext;

namespace OHOS::Ace::NG {
namespace {
    constexpr float FIRST_ITEM_WIDTH = 100.0f;
    constexpr float FIRST_ITEM_HEIGHT = 50.0f;
    const SizeF FIRST_ITEM_SIZE(FIRST_ITEM_WIDTH, FIRST_ITEM_HEIGHT);
} // namespace
class TabsModelTestNG : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static void MockPipelineContextGetTheme();
};

void TabsModelTestNG::SetUpTestCase() {}

void TabsModelTestNG::TearDownTestCase() {}

void TabsModelTestNG::SetUp()
{
    MockPipelineBase::SetUp();
}

void TabsModelTestNG::TearDown()
{
    MockPipelineBase::TearDown();
}

void TabsModelTestNG::MockPipelineContextGetTheme()
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));
}

/**
 * @tc.name: TabsModelSetDivider001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelSetDivider001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));

    TabsModelNG tabsModel;
    TabsItemDivider divider;
    Dimension strokeWidth = 10.0_vp;
    Dimension startMargin = 3.0_vp;
    Dimension endMargin = 4.0_vp;
    Color color = Color::BLACK;
    
    divider.strokeWidth = strokeWidth;
    divider.startMargin = startMargin;
    divider.endMargin = endMargin;
    divider.color = color;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetDivider(divider);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    EXPECT_EQ(dividerNode->GetTag(), V2::DIVIDER_ETS_TAG);
    auto layoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetDivider()->color.ColorToString(), color.ColorToString());
    EXPECT_EQ(layoutProperty->GetDivider()->strokeWidth.ToString(), strokeWidth.ToString());
    EXPECT_EQ(layoutProperty->GetDivider()->startMargin.ToString(), startMargin.ToString());
    EXPECT_EQ(layoutProperty->GetDivider()->endMargin.ToString(), endMargin.ToString());

    auto clone = layoutProperty->Clone();
    clone.Reset();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);

    auto dividerJson = json->GetValue("divider");
    ASSERT_NE(dividerJson, nullptr);
    layoutProperty->Reset();
    layoutProperty->ToJsonValue(json);
    tabsModel.Pop();

    TabsItemDivider divider2;
    EXPECT_FALSE(divider == divider2);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabsModelSetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelSetFadingEdge001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_TRUE(tabBarPaintProperty->GetFadingEdgeValue());

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabsFrameNode->ToJsonValue(json);

    auto fadingEdgeJson = json->GetValue("fadingEdge");
    EXPECT_NE(fadingEdgeJson, nullptr);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabsModelMeasure001
 * @tc.desc: Test Divider Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapper layoutWrapper = LayoutWrapper(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF LayoutConstraintVaild;
    float layoutSize = 10000.0f;
    LayoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateLayoutConstraint(
        LayoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(0));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<LayoutWrapper> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<LayoutWrapper> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(dividerNode, geometryNode, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(2));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<LayoutWrapper> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapper>(swiperNode, geometryNode, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    auto dividerOffect = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffect.GetX(), 0);
    EXPECT_EQ(dividerOffect.GetY(), layoutSize);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffect = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffect.GetX(), 0);
    EXPECT_EQ(dividerOffect.GetY(), 0);

    instance.SetIsVertical(true);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffect = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffect.GetX(), 0);
    EXPECT_EQ(dividerOffect.GetY(), 0);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffect = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffect.GetX(), layoutSize);
    EXPECT_EQ(dividerOffect.GetY(), 0);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider001
 * @tc.desc: Test tabs OnUpdateShowDivider.
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelOnUpdateShowDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    MockPipelineContextGetTheme();

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);

    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    pattern->OnUpdateShowDivider();

    auto dividerNode = tabsFrameNode->GetChildAtIndex(1);
    ASSERT_NE(dividerNode, nullptr);
    auto dividerFrameNode = AceType::DynamicCast<FrameNode>(dividerNode);

    auto dividerRenderProperty = dividerFrameNode->GetPaintProperty<DividerRenderProperty>();
    ASSERT_NE(dividerRenderProperty, nullptr);
    auto dividerColor = dividerRenderProperty->GetDividerColor();
    EXPECT_EQ(dividerColor.value().ColorToString(), color.ColorToString());
    
    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider002
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelOnUpdateShowDivider002, TestSize.Level2)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    EXPECT_EQ(pattern->GetHostFrameSize(), std::nullopt);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider003
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelOnUpdateShowDivider003, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
        V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    EXPECT_LT(tabsNode->GetChildren().size(), 2);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider004
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelOnUpdateShowDivider004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
        V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);

    bool hasTabBarNode = tabsNode->HasTabBarNode();
    auto controller = AceType::MakeRefPtr<SwiperController>();
    auto tabBarId = tabsNode->GetTabBarId();
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TAB_BAR_ETS_TAG, tabBarId, [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });
    ASSERT_NE(tabBarNode, nullptr);

    if (!hasTabBarNode) {
        tabBarNode->MountToParent(tabsNode);
    }

    bool hasSwiperNode = tabsNode->HasSwiperNode();
    auto swiperId = tabsNode->GetSwiperId();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    ASSERT_NE(swiperNode, nullptr);

    if (!hasSwiperNode) {
        swiperNode->MountToParent(tabsNode);
    }
    
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    auto childNode = tabsNode->GetChildAtIndex(1);
    ASSERT_NE(childNode, nullptr);
    EXPECT_NE(childNode->GetTag(), V2::DIVIDER_ETS_TAG);
}

/**
 * @tc.name: TabsModelToJsonValue001
 * @tc.desc: Test tabs ToJsonValue when host has not child.
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabsModelToJsonValue001, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
        V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabsNode->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
    auto dividerJson = json->GetValue("divider");
    ASSERT_NE(dividerJson, nullptr);
    EXPECT_TRUE(dividerJson->IsNull());
}

/**
 * @tc.name: TabContentModelSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetIndicator001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));

    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;
    Color color = Color::BLACK;
    Dimension height = 10.0_vp;
    Dimension width = 20.0_vp;
    Dimension borderRadius = 2.0_vp;
    Dimension marginTop = 3.0_vp;

    indicator.color = color;
    indicator.height = height;
    indicator.width = width;
    indicator.borderRadius = borderRadius;
    indicator.marginTop = marginTop;

    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().color.ColorToString(), color.ColorToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().height.ToString(), height.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width.ToString(), width.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius.ToString(), borderRadius.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().marginTop.ToString(), marginTop.ToString());

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetIndicator002
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetIndicator002, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;
    Color color = Color::WHITE;
    Dimension height = 0.0_vp;
    Dimension width = 0.0_vp;
    Dimension borderRadius = 0.0_vp;
    Dimension marginTop = 0.0_vp;

    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().color.ColorToString(), color.ColorToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().height.ToString(), height.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width.ToString(), width.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius.ToString(), borderRadius.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().marginTop.ToString(), marginTop.ToString());

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius001
 * @tc.desc: test SetSubTabBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetSubTabBorderRadius001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    MockPipelineBase::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_))
        .WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));

    TabContentModelNG tabContentModel;
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentModel.Create();
    tabContentModel.SetBoard(boardStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius.ToString(), boardStyle.borderRadius.ToString());

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
    MockPipelineBase::GetCurrent()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius002
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetSubTabBorderRadius002, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentModel.Create();
    tabContentModel.SetBoard(boardStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius.ToString(), boardStyle.borderRadius.ToString());

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetSelectedMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetLabelStyle001
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetLabelStyle001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    LabelStyle labelStyle;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);

    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, std::nullopt);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelSetLabelStyle002
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelSetLabelStyle002, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown" };
    std::vector<std::string> fontVect = {""};
    labelStyle.fontStyle = Ace::FontStyle::NORMAL;

    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, labelStyle.textOverflow);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, labelStyle.maxLines);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, labelStyle.fontWeight);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, labelStyle.fontFamily);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, labelStyle.fontStyle);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabContentModelToJsonValue001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabContentModelToJsonValue001, TestSize.Level1)
{
    MockPipelineContextGetTheme();

    TabContentModelNG tabContentModel;

    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabContentFrameNode->ToJsonValue(json);
    EXPECT_NE(json, nullptr);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternAddTabBarItem001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternAddTabBarItem001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto layoutAlgorithm = tabBarPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    DirtySwapConfig config;
    auto layoutWrapper = AceType::MakeRefPtr<LayoutWrapper>(tabBarNode, tabBarNode->GetGeometryNode(),
        tabBarLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false, false);
    ASSERT_NE(algorithmWrapper, nullptr);

    layoutWrapper->SetLayoutAlgorithm(algorithmWrapper);
    EXPECT_EQ(layoutWrapper->layoutAlgorithm_, algorithmWrapper);
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->UpdateSubTabBoard();
    
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabBarPattern->UpdateSubTabBoard();

    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->UpdateSubTabBoard();

    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetTabBarMode(TabBarMode::SCROLLABLE);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_EQ(tabsNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabItemOffsets_ = {{-1.0f, -1.0f}};
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[2]);

    tabBarPattern->tabItemOffsets_ = {{10.0f, 10.0f}};
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[3]);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->tabItemOffsets_ = {{-1.0f, -1.0f}};
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[0]);

    tabBarPattern->tabItemOffsets_ = {{10.0f, 10.0f}};
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[1]);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);

    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    tabBarPattern->SetIndicatorStyle(indicator, 1);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[1], indicator);
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);

    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    auto selectedMode = tabBarPattern->GetSelectedMode();
    EXPECT_EQ(selectedMode, SelectedMode::INDICATOR);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::NOSTYLE);
    tabBarPattern->UpdateIndicator(0);

    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarType_[0] = true;
    tabBarPattern->UpdateIndicator(0);

    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->tabBarType_[0] = false;
    tabBarPattern->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternHandleClick001
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternHandleClick001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_))
        .WillRepeatedly(Return());

    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_EQ(tabsNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_ = {{0.0f, 0.0f}, {10.0f, 10.0f}};
    
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick001
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternHandleSubTabBarClick001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_))
        .WillRepeatedly(Return());

    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabItemOffsets_ = {{0.0f, 0.0f}, {10.0f, 10.0f}};

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[1], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->HandleClick(info);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleSubTabBarClick(tabBarLayoutProperty, 1);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), AddScheduleTask(_))
        .WillRepeatedly(Return(0));
    EXPECT_CALL(*MockPipelineBase::GetCurrent(), RemoveScheduleTask(_))
        .WillRepeatedly(Return());

    const std::string text_test = "text_test";
    
    TabContentModelNG tabContentModel;

    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = tabsNode->GetTabs();
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildren().front());
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto rect = tabBarLayoutProperty->GetIndicatorRect(0);
    ASSERT_EQ(rect.GetX(), 0);
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicator001, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicator(rect);
    EXPECT_EQ(tabBarModifier->indicatorLeft_->Get(), 0.0f);
    EXPECT_EQ(tabBarModifier->indicatorTop_->Get(), 0.0f);
}

/**
 * @tc.name: TabBarModifierSetIndicatorColor001
 * @tc.desc: test SetIndicatorColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicatorColor001, TestSize.Level1)
{
    LinearColor indicatorColor(Color::BLACK);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_TRUE(tabBarModifier->indicatorColor_->Get() == indicatorColor);
}

/**
 * @tc.name: TabBarModifierSetIndicatorWidth001
 * @tc.desc: test SetIndicatorWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicatorWidth001, TestSize.Level1)
{
    float indicatorWidth = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
}

/**
 * @tc.name: TabBarModifierSetIndicatorHeight001
 * @tc.desc: test SetIndicatorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicatorHeight001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    float indicatorHeight = 1.0f;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
}

/**
 * @tc.name: TabBarModifierSetIndicatorBorderRadius001
 * @tc.desc: test SetIndicatorBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicatorBorderRadius001, TestSize.Level1)
{
    float indicatorBorderRadius = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);
}

/**
 * @tc.name: TabBarModifierSetIndicatorMarginTop001
 * @tc.desc: test SetIndicatorMarginTop
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetIndicatorMarginTop001, TestSize.Level1)
{
    float indicatorMarginTop = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
}

/**
 * @tc.name: TabBarModifierSetActiveMode001
 * @tc.desc: test SetActiveMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierSetActiveMode001, TestSize.Level1)
{
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetSelectedMode(selectedMode);
    EXPECT_TRUE(tabBarModifier->hasIndicator_);
}

/**
 * @tc.name: TabBarModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarModifierOnDraw001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    EXPECT_FALSE(tabBarModifier == nullptr);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    float indicatorHeight = 1.0f;
    float indicatorWidth = 1.0f;
    float indicatorMarginTop = 1.0f;
    float indicatorBorderRadius = 1.0f;

    tabBarModifier->SetSelectedMode(SelectedMode::INDICATOR);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);

    indicatorHeight = -1.0f;
    indicatorWidth = -1.0f;
    indicatorMarginTop = -1.0f;
    indicatorBorderRadius = -1.0f;

    tabBarModifier->SetSelectedMode(SelectedMode::INDICATOR);
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    tabBarModifier->onDraw(context);

    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);
    
    tabBarModifier->SetSelectedMode(SelectedMode::BOARD);
    tabBarModifier->onDraw(context);
    EXPECT_FALSE(tabBarModifier->hasIndicator_->Get());

    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction001
 * @tc.desc: test GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    auto paintMethod2 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod2, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);

    paintProperty = tabBarPattern->CreatePaintProperty();
    auto tabBarPaintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintProperty);
    tabBarPaintProperty->UpdateFadingEdge(false);
    EXPECT_FALSE(tabBarPaintProperty->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = paintProperty->Clone();
    EXPECT_NE(clone, nullptr);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetContentModifier001
 * @tc.desc: test GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    auto contentModifier = paintMethod->GetContentModifier(&paintWrapper);
    EXPECT_NE(contentModifier, nullptr);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPaintMethodUpdateContentModifier001
 * @tc.desc: test UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPaintMethodUpdateContentModifier001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto tabBarPaintMethod = Ace::AceType::DynamicCast<TabBarPaintMethod>(paintMethod);
    ASSERT_NE(tabBarPaintMethod, nullptr);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}

/**
 * @tc.name: TabBarPaintMethodPaintGradient001
 * @tc.desc: test PaintGradient
 * @tc.type: FUNC
 */
HWTEST_F(TabsModelTestNG, TabBarPaintMethodPaintGradient001, TestSize.Level1)
{
    MockPipelineContextGetTheme();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildren().front());
    ASSERT_NE(tabBarFrameNode, nullptr);
    EXPECT_EQ(tabBarFrameNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPattern = tabBarFrameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto paintProperty = tabBarPattern->CreatePaintProperty();
    ASSERT_NE(paintProperty, nullptr);
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    tabBarPattern->SetSelectedMode(selectedMode, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], selectedMode);
    std::vector<bool> gradientRegions = {true, true, true, true, true};
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(tabBarModifier, gradientRegions, Color::BLACK,
        indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    drawFunction(rsCanvas);
    EXPECT_TRUE(paintMethod->gradientRegions_[0]);

    gradientRegions[0] = false;
    paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(tabBarModifier, gradientRegions, Color::BLACK,
        indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(),
        paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_NE(drawFunction, nullptr);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);

    // Involution
    PipelineContext::GetCurrentContext()->SetThemeManager(nullptr);
}
}