/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {
void TabsTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    auto tabTheme = AceType::MakeRefPtr<TabTheme>();
    tabTheme->defaultTabBarName_ = "tabBarItemName";
    tabTheme->tabBarDefaultWidth_ = Dimension(TABBAR_DEFAULT_WIDTH);
    tabTheme->tabBarDefaultHeight_ = Dimension(TABBAR_DEFAULT_HEIGHT);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(tabTheme));
}

void TabsTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void TabsTestNg::SetUp() {}

void TabsTestNg::TearDown()
{
    frameNode_ = nullptr;
    pattern_ = nullptr;
    layoutProperty_ = nullptr;

    swiperNode_ = nullptr;
    swiperPattern_ = nullptr;
    swiperLayoutProperty_ = nullptr;
    swiperPaintProperty_ = nullptr;
    swiperController_ = nullptr;

    tabBarNode_ = nullptr;
    tabBarPattern_ = nullptr;
    tabBarLayoutProperty_ = nullptr;
    tabBarPaintProperty_ = nullptr;
    tabBarAccessibilityProperty_ = nullptr;

    dividerNode_ = nullptr;
    dividerRenderProperty_ = nullptr;
}

void TabsTestNg::GetInstance()
{
    // tabs
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    frameNode_ = AceType::DynamicCast<TabsNode>(element);
    pattern_ = frameNode_->GetPattern<TabsPattern>();
    layoutProperty_ = frameNode_->GetLayoutProperty<TabsLayoutProperty>();
    // swiper>tabContent
    swiperNode_= AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    swiperLayoutProperty_ = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    swiperPaintProperty_ = swiperNode_->GetPaintProperty<SwiperPaintProperty>();
    swiperController_ = swiperPattern_->GetSwiperController();
    // tabBar
    tabBarNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabBar());
    tabBarPattern_ = tabBarNode_->GetPattern<TabBarPattern>();
    tabBarLayoutProperty_ = tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>();
    tabBarPaintProperty_ = tabBarNode_->GetPaintProperty<TabBarPaintProperty>();
    tabBarAccessibilityProperty_ = tabBarNode_->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    // divider
    dividerNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetDivider());
    dividerRenderProperty_ = dividerNode_->GetPaintProperty<DividerRenderProperty>();
}

void TabsTestNg::Create(const std::function<void(TabsModelNG)>& callback, BarPosition barPosition, int32_t index)
{
    TabsModelNG model;
    model.Create(barPosition, index, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    if (callback) {
        callback(model);
    }
    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode->GetOrCreateFocusHub();
    model.Pop();
    GetInstance();
    FlushLayoutTask(frameNode_);
}

void TabsTestNg::CreateWithItem(
    const std::function<void(TabsModelNG)>& callback, BarPosition barPosition, int32_t index)
{
    Create(
        [callback](TabsModelNG model) {
            if (callback) {
                callback(model);
            }
            CreateItem(TABCONTENT_NUMBER);
        },
        barPosition, index);
}

void TabsTestNg::CreateItem(int32_t itemNumber)
{
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    int32_t nodeId = 0;
    for (int32_t index = 0; index < itemNumber; index++) {
        TabContentModelNG model;
        model.Create();
        auto tabBarItemFunc = TabBarItemBuilder();
        model.SetTabBar("", "", std::move(tabBarItemFunc), true);
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
        tabContentNode->UpdateRecycleElmtId(nodeId); // for AddChildToGroup
        tabContentNode->GetTabBarItemId(); // for AddTabBarItem
        tabContentNode->SetParent(weakTab); // for AddTabBarItem
        model.Pop();
        nodeId++;
    }
}

TabBarBuilderFunc TabsTestNg::TabBarItemBuilder()
{
    return []() {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
        ViewAbstract::SetWidth(CalcLength(10.f));
        ViewAbstract::SetHeight(CalcLength(10.f));
    };
}

/**
 * @tc.name: TabsModelSetDivider001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetDivider001, TestSize.Level1)
{
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
    divider.isNull = false;

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
    EXPECT_EQ(layoutProperty->GetDivider()->isNull, false);

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
}

/**
 * @tc.name: TabsModelSetDivider002
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetDivider002, TestSize.Level1)
{
    TabsModelNG tabsModel;
    TabsItemDivider divider;
    divider.isNull = true;

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
    EXPECT_EQ(layoutProperty->GetDivider()->isNull, true);

    auto clone = layoutProperty->Clone();
    clone.Reset();
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    layoutProperty->ToJsonValue(json);
    ASSERT_NE(json, nullptr);
}

/**
 * @tc.name: TabsModelSetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetFadingEdge001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_TRUE(tabBarPaintProperty->GetFadingEdgeValue());

    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabsFrameNode->ToJsonValue(json);

    auto fadingEdgeJson = json->GetValue("fadingEdge");
    EXPECT_NE(fadingEdgeJson, nullptr);
}

/**
 * @tc.name: TabsModelMeasure001
 * @tc.desc: Test Divider Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

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
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, geometryNode3, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    auto dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), 0);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), layoutSize);

    instance.SetIsVertical(true);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), layoutSize);
    EXPECT_EQ(dividerOffset.GetY(), 0);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    dividerOffset = dividerLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(dividerOffset.GetX(), 0);
    EXPECT_EQ(dividerOffset.GetY(), 0);
    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(true);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(false);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
}

/**
 * @tc.name: TabsModelMeasure002
 * @tc.desc: Test Tabs Measure and Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.maxSize = FIRST_ITEM_SIZE;
    layoutConstrain.percentReference = FIRST_ITEM_SIZE;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, swiperGeometryNode, swiperNode->GetLayoutProperty());

    auto swipeLayoutAlgorithm = swiperNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(swipeLayoutAlgorithm, nullptr);
    swiperLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(swipeLayoutAlgorithm));

    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(SWIPER_WIDTH)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(0.0f)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(TABBAR_WIDTH)));

    RefPtr<GeometryNode> tabbarChildGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarChild =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabbarChildGeometryNode, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->AppendChild(tabBarChild);
    tabBarLayoutWrapper->AppendChild(tabBarChild);
    tabBarLayoutWrapper->AppendChild(tabBarChild);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    auto tabBarSize = tabBarLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabBarSize.Width(), FIRST_ITEM_WIDTH);
    EXPECT_EQ(tabBarSize.Height(), TABBAR_WIDTH);

    auto swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), TABBAR_WIDTH);

    auto swiperSize = swiperLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(swiperSize.Width(), FIRST_ITEM_WIDTH);
    EXPECT_EQ(swiperSize.Height(), SWIPER_WIDTH);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), SWIPER_WIDTH);

    swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabsModelMeasure003
 * @tc.desc: Test Tabs Measure and Layout when is vertical.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIsVertical(true);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.maxSize = FIRST_ITEM_SIZE;
    layoutConstrain.percentReference = FIRST_ITEM_SIZE;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> swiperGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, swiperGeometryNode, swiperNode->GetLayoutProperty());

    auto swipeLayoutAlgorithm = swiperNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(swipeLayoutAlgorithm, nullptr);
    swiperLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(swipeLayoutAlgorithm));

    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(SWIPER_WIDTH), CalcLength(FIRST_ITEM_WIDTH)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(0.0f), CalcLength(FIRST_ITEM_WIDTH)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TABBAR_WIDTH), CalcLength(FIRST_ITEM_WIDTH)));

    RefPtr<GeometryNode> tabbarChildGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarChild =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabbarChildGeometryNode, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->AppendChild(tabBarChild);
    tabBarLayoutWrapper->AppendChild(tabBarChild);
    tabBarLayoutWrapper->AppendChild(tabBarChild);

    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), 0.0f);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    auto tabBarSize = tabBarLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabBarSize.Width(), TABBAR_WIDTH);
    EXPECT_EQ(tabBarSize.Height(), FIRST_ITEM_WIDTH);

    auto swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), TABBAR_WIDTH);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);

    auto swiperSize = swiperLayoutWrapper->GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(swiperSize.Width(), SWIPER_WIDTH);
    EXPECT_EQ(swiperSize.Height(), FIRST_ITEM_WIDTH);

    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabbarOffset = tabBarLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabbarOffset.GetX(), SWIPER_WIDTH);
    EXPECT_EQ(tabbarOffset.GetY(), 0.0f);

    swiperOffset = swiperLayoutWrapper->GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(swiperOffset.GetX(), 0.0f);
    EXPECT_EQ(swiperOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabsModelMeasure004
 * @tc.desc: Test Tabs Measure and Layout when the ideaSize is infinity.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelMeasure004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    instance.SetIsVertical(true);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    layoutConstrain.selfIdealSize.SetSize(SizeF(FIRST_ITEM_WIDTH, INFINITY_NUM));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabsSize = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabsSize.Width(), 0.0f);
    EXPECT_EQ(tabsSize.Height(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(SizeF(INFINITY_NUM, FIRST_ITEM_HEIGHT));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsSize = layoutWrapper.GetGeometryNode()->GetFrameSize();
    EXPECT_EQ(tabsSize.Width(), 0.0f);
    EXPECT_EQ(tabsSize.Height(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(NEGTIVE_SIZE);
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    auto tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);

    layoutConstrain.selfIdealSize.SetSize(FIRST_ITEM_SIZE);
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.maxSize = SizeF(FIRST_ITEM_SIZE);
    childLayoutConstraint.minSize = SizeF(0.0f, 0.0f);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(0));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> tabbarGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabbarGeometryNode, tabBarNode->GetLayoutProperty());

    auto tabbarLayoutAlgorithm = tabBarNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    tabBarLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));

    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(TABBAR_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);

    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(1));
    ASSERT_NE(dividerNode, nullptr);
    RefPtr<GeometryNode> dividerGeometryNode = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, dividerGeometryNode, dividerNode->GetLayoutProperty());

    auto dividerLayoutAlgorithm = dividerNode->GetPattern<Pattern>()->CreateLayoutAlgorithm();
    ASSERT_NE(dividerLayoutAlgorithm, nullptr);
    dividerLayoutWrapper->SetLayoutAlgorithm(
        AccessibilityManager::MakeRefPtr<LayoutAlgorithmWrapper>(dividerLayoutAlgorithm));

    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(0.0f), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);

    tabsOffset = layoutWrapper.GetGeometryNode()->GetMarginFrameOffset();
    EXPECT_EQ(tabsOffset.GetX(), 0.0f);
    EXPECT_EQ(tabsOffset.GetY(), 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasure001
 * @tc.desc: Test Divider Measure.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    float layoutSize_test = 5000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    layoutConstraintVaild.parentIdealSize.SetSize(SizeF(layoutSize_test, layoutSize_test));
    LayoutConstraintF layoutConstraintVaild_test;
    layoutConstraintVaild_test.minSize.SetSizeT(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    for (int32_t i = 0; i <= 2; i++) {
        auto tabBarNode_test = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
        ASSERT_NE(tabBarNode_test, nullptr);
        RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test, geometryNode3, tabBarNode->GetLayoutProperty());
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(tabBarLayoutWrapper);
    }

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabsLayoutAlgorithm->Measure(&layoutWrapper);
                tabBarLayoutAlgorithm->Measure(&layoutWrapper);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateAxis(Axis::VERTICAL);
                tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
            }
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
            tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
            ->UpdateLayoutConstraint(layoutConstraintVaild_test);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
        tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout001
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    float layoutSize_test = 5000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    layoutConstraintVaild.parentIdealSize.SetSize(SizeF(layoutSize_test, layoutSize_test));
    LayoutConstraintF layoutConstraintVaild_test;
    layoutConstraintVaild_test.minSize.SetSizeT(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    for (int32_t i = 0; i <= 2; i++) {
        auto tabBarNode_test = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
        ASSERT_NE(tabBarNode_test, nullptr);
        RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test, geometryNode3, tabBarNode->GetLayoutProperty());
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(tabBarLayoutWrapper);
    }

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    int32_t indicator = -1;
    int32_t indicator_test = 0;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateIndicator(indicator_test);
    tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarLayoutAlgorithm->SetIndicator(indicator);

    float childrenMainSize = 0.0f;
    float childrenMainSize1 = 0.2f;
    float childrenMainSize_test = 0.1f;
    int32_t index = 0;
    auto axis = Axis::HORIZONTAL;
    tabBarLayoutAlgorithm->SetChildrenMainSize(childrenMainSize);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(layoutSize, layoutSize));
    layoutWrapper.GetGeometryNode()->GetFrameSize().SetMainSize(childrenMainSize_test, axis);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->Layout(&layoutWrapper);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateAxis(Axis::VERTICAL);
                tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarLayoutAlgorithm->SetIndicator(indicator_test);
                AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                    ->UpdateIndicator(indicator);
            }
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
            tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
            tabBarLayoutAlgorithm->SetChildrenMainSize(childrenMainSize1);
            layoutWrapper.GetOrCreateChildByIndex(index)->GetGeometryNode()->GetMarginFrameSize().SetMainSize(
                childrenMainSize_test, axis);
            layoutWrapper.GetOrCreateChildByIndex(indicator_test)
                ->GetGeometryNode()
                ->GetMarginFrameSize()
                .SetMainSize(childrenMainSize_test, axis);
            layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(layoutSize, layoutSize));
            AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
                ->UpdateIndicator(indicator_test);
            tabBarLayoutAlgorithm->SetIndicator(indicator);
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
            ->UpdateLayoutConstraint(layoutConstraintVaild_test);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
        tabBarLayoutAlgorithm->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetSpace001
 * @tc.desc: Test GetSpace and CalculateFrontChildrenMainSize.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetSpace001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call GetSpace and
     * CalculateFrontChildrenMainSize functions.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    int32_t indicator = 0;
    SizeF frameSize(SizeF(0.0f, 0.0f));
    auto axis = Axis::HORIZONTAL;

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarLayoutAlgorithm->GetSpace(&layoutWrapper, indicator, frameSize, axis);
            tabBarLayoutAlgorithm->CalculateFrontChildrenMainSize(
                &(j == 0 ? layoutWrapper_test : (indicator == 1 ? layoutWrapper : layoutWrapper_test)), indicator,
                axis);
            indicator = (i == 1 ? 0 : 1);
        }
    }
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider001
 * @tc.desc: Test tabs OnUpdateShowDivider.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

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
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider002
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider002, TestSize.Level2)
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
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider003, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->OnUpdateShowDivider();
    EXPECT_LT(tabsNode->GetChildren().size(), static_cast<std::size_t>(2));
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider004
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelOnUpdateShowDivider004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
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
HWTEST_F(TabsTestNg, TabsModelToJsonValue001, TestSize.Level2)
{
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
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
HWTEST_F(TabsTestNg, TabContentModelSetIndicator001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);

    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));

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
}

/**
 * @tc.name: TabContentModelSetIndicator002
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetIndicator002, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;
    Dimension width = 0.0_vp;
    Dimension borderRadius = 0.0_vp;

    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width.ToString(), width.ToString());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius.ToString(), borderRadius.ToString());
}

/**
 * @tc.name: TabContentModelCreate(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelCreate001, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    tabContentModel.Create([]() {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius001
 * @tc.desc: test SetSubTabBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSubTabBorderRadius001, TestSize.Level1)
{
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    ASSERT_NE(themeManager, nullptr);

    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<TabTheme>()));
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
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius002
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSubTabBorderRadius002, TestSize.Level1)
{
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
}

/**
 * @tc.name: TabContentModelSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSelectedMode001, TestSize.Level1)
{
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
}

/**
 * @tc.name: TabContentModelSetLabelStyle001
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle001, TestSize.Level1)
{
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
}

/**
 * @tc.name: TabContentModelSetLabelStyle002
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLabelStyle002, TestSize.Level1)
{
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
    std::vector<std::string> fontVect = { "" };
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
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle001
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelUpdateLabelStyle001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();

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
    std::vector<std::string> fontVect = { "" };
    labelStyle.fontStyle = Ace::FontStyle::NORMAL;
    tabContentModel.Create();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    EXPECT_EQ(layoutProperty->GetTextOverflow(), labelStyle.textOverflow);
    EXPECT_EQ(layoutProperty->GetMaxLines(), labelStyle.maxLines);
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize()->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize()->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy(), labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(layoutProperty->GetFontSize()->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(layoutProperty->GetFontWeight(), labelStyle.fontWeight);
    EXPECT_EQ(layoutProperty->GetFontFamily(), labelStyle.fontFamily);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle(), labelStyle.fontStyle);
}

/**
 * @tc.name: TabContentModelToJsonValue001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelToJsonValue001, TestSize.Level1)
{
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown", "unknow2" };

    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabContentFrameNode->ToJsonValue(json);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: TabContentModelAddTabBarItem001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelAddTabBarItem001, TestSize.Level1)
{
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
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode2, nullptr);
    EXPECT_EQ(tabContentFrameNode2->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern2, nullptr);
    tabContentFrameNode2->MountToParent(swiperNode);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode2, DEFAULT_NODE_SLOT, true);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap001
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto layoutAlgorithm = tabBarPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    DirtySwapConfig config;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabBarNode->GetGeometryNode(), tabBarLayoutProperty);
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
    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = true;
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(config.skipMeasure, true);
    EXPECT_EQ(config.skipLayout, false);
    config.skipLayout = true;
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(config.skipMeasure, true);
    EXPECT_EQ(config.skipLayout, true);
    config.skipMeasure = false;
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(config.skipMeasure, false);
    EXPECT_EQ(config.skipLayout, true);
    tabBarPattern->isAnimating_ = true;
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern->isAnimating_, true);
}

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
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

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->UpdateSubTabBoard();

    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
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

    tabBarPattern->indicator_ = 1;
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    IndicatorStyle style;
    tabBarPattern->SetIndicatorStyle(style, 1);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 1);

    tabBarPattern->indicator_ = 0;
    tabBarPattern->tabBarStyles_[0] = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->selectedModes_[0] = SelectedMode::BOARD;
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->UpdateSubTabBoard();
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[2]);

    tabBarPattern->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[2]);

    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[3]);

    tabBarPattern->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern->childrenMainSize_ = 5.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[3]);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[0]);

    tabBarPattern->tabItemOffsets_ = { { 1.0f, 1.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[0]);

    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern->childrenMainSize_ = 10.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern->gradientRegions_[1]);

    tabBarPattern->tabItemOffsets_ = { { -10.0f, -10.0f } };
    tabBarPattern->childrenMainSize_ = 5.0f;
    tabBarPattern->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern->gradientRegions_[1]);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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

    tabBarPattern->indicator_ = 1;
    tabBarPattern->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    IndicatorStyle indicatorStyle;
    tabBarPattern->SetIndicatorStyle(indicatorStyle, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleClick001
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick001, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick001
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleSubTabBarClick001, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
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

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

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
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto rect = tabBarLayoutProperty->GetIndicatorRect(0);
    EXPECT_EQ(rect.GetX(), 0);
}

/**
 * @tc.name: TabBarPatternGetSelectedMode001
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetSelectedMode001, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    tabBarPattern->indicator_ = 1;
    auto mode = tabBarPattern->GetSelectedMode();
    EXPECT_EQ(mode, selectedMode);
}

/**
 * @tc.name: TabBarModifierSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicator001, TestSize.Level1)
{
    RectF rect(0.0f, 0.0f, 1.0f, 1.0f);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicator(rect);
    EXPECT_EQ(tabBarModifier->indicatorLeft_->Get(), 0.0f);
    EXPECT_EQ(tabBarModifier->indicatorTop_->Get(), 0.0f);
    tabBarModifier->indicatorLeft_ = nullptr;
    tabBarModifier->indicatorTop_ = nullptr;
    tabBarModifier->SetIndicator(rect);
    EXPECT_EQ(tabBarModifier->indicatorLeft_, nullptr);
    EXPECT_EQ(tabBarModifier->indicatorTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorColor001
 * @tc.desc: test SetIndicatorColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorColor001, TestSize.Level1)
{
    LinearColor indicatorColor(Color::BLACK);
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_TRUE(tabBarModifier->indicatorColor_->Get() == indicatorColor);
    tabBarModifier->indicatorColor_ = nullptr;
    tabBarModifier->SetIndicatorColor(indicatorColor);
    EXPECT_EQ(tabBarModifier->indicatorColor_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorWidth001
 * @tc.desc: test SetIndicatorWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorWidth001, TestSize.Level1)
{
    float indicatorWidth = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_->Get(), indicatorWidth);
    tabBarModifier->indicatorWidth_ = nullptr;
    tabBarModifier->SetIndicatorWidth(indicatorWidth);
    EXPECT_EQ(tabBarModifier->indicatorWidth_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorHeight001
 * @tc.desc: test SetIndicatorHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorHeight001, TestSize.Level1)
{
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    float indicatorHeight = 1.0f;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_->Get(), indicatorHeight);
    tabBarModifier->indicatorHeight_ = nullptr;
    tabBarModifier->SetIndicatorHeight(indicatorHeight);
    EXPECT_EQ(tabBarModifier->indicatorHeight_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorBorderRadius001
 * @tc.desc: test SetIndicatorBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorBorderRadius001, TestSize.Level1)
{
    float indicatorBorderRadius = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_->Get(), indicatorBorderRadius);
    tabBarModifier->indicatorBorderRadius_ = nullptr;
    tabBarModifier->SetIndicatorBorderRadius(indicatorBorderRadius);
    EXPECT_EQ(tabBarModifier->indicatorBorderRadius_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetIndicatorMarginTop001
 * @tc.desc: test SetIndicatorMarginTop
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetIndicatorMarginTop001, TestSize.Level1)
{
    float indicatorMarginTop = 1.0f;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_->Get(), indicatorMarginTop);
    tabBarModifier->indicatorMarginTop_ = nullptr;
    tabBarModifier->SetIndicatorMarginTop(indicatorMarginTop);
    EXPECT_EQ(tabBarModifier->indicatorMarginTop_, nullptr);
}

/**
 * @tc.name: TabBarModifierSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetSelectedMode001, TestSize.Level1)
{
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetSelectedMode(selectedMode);
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    EXPECT_TRUE(tabBarModifier->hasIndicator_->Get());
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->SetSelectedMode(selectedMode);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarModifierOnDraw001
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierOnDraw001, TestSize.Level1)
{
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

    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->onDraw(context);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction001
 * @tc.desc: test GetForegroundDrawFunction
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetForegroundDrawFunction001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);

    paintProperty = tabBarPattern->CreatePaintProperty();
    auto tabBarPaintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintProperty);
    tabBarPaintProperty->UpdateFadingEdge(false);
    EXPECT_FALSE(tabBarPaintProperty->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = paintProperty->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodGetContentModifier001
 * @tc.desc: test GetContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetContentModifier001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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

    tabBarPattern->indicator_ = 1;
    auto paintMethod2 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_EQ(paintMethod2, nullptr);

    IndicatorStyle style;
    tabBarPattern->SetIndicatorStyle(style, 1);
    auto paintMethod3 = tabBarPattern->CreateNodePaintMethod();
    ASSERT_EQ(paintMethod3, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    auto contentModifier = paintMethod->GetContentModifier(&paintWrapper);
    EXPECT_NE(contentModifier, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodUpdateContentModifier001
 * @tc.desc: test UpdateContentModifier
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodUpdateContentModifier001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    paintMethod->UpdateContentModifier(&paintWrapper);
    auto tabBarPaintMethod = Ace::AceType::DynamicCast<TabBarPaintMethod>(paintMethod);
    ASSERT_NE(tabBarPaintMethod, nullptr);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);

    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), nullptr);
    paintMethod->UpdateContentModifier(&paintWrapper2);
    EXPECT_NE(tabBarPaintMethod->tabBarModifier_, nullptr);
}

/**
 * @tc.name: TabBarPaintMethodPaintGradient001
 * @tc.desc: test PaintGradient
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodPaintGradient001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());

    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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
    std::vector<bool> gradientRegions = { true, true, true, true, true };
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    auto paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);

    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, DetachPen()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).WillRepeatedly(Return());
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    drawFunction(rsCanvas);
    EXPECT_TRUE(paintMethod->gradientRegions_[0]);

    gradientRegions[0] = false;
    paintMethod = AceType::MakeRefPtr<TabBarPaintMethod>(
        tabBarModifier, gradientRegions, Color::BLACK, indicator, 0.0, selectedMode);
    ASSERT_NE(paintMethod, nullptr);
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_NE(drawFunction, nullptr);
    drawFunction(rsCanvas);
    EXPECT_FALSE(paintMethod->gradientRegions_[0]);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg001
 * @tc.desc: Test the ItemCount property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg001, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode->MountToParent(swiperNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_EQ(accessibilityProperty->GetCollectionItemCounts(), DEFAULT_ITEMCOUNT);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg002
 * @tc.desc: Test the IsScrollable property of TabBar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg002, TestSize.Level1)
{
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_TRUE(accessibilityProperty->IsScrollable());

    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());

    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED_START);
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg003
 * @tc.desc: Test the index properties of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg003, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarAccessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);
    EXPECT_EQ(tabBarAccessibilityProperty->GetBeginIndex(), DEFAULT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetCurrentIndex(), DEFAULT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetEndIndex(), DEFAULT_INDEX);

    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode->MountToParent(swiperNode);

    auto pattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(pattern, nullptr);
    pattern->SetIndicator(CURRENT_INDEX);

    EXPECT_EQ(tabBarAccessibilityProperty->GetBeginIndex(), BEGIN_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetCurrentIndex(), CURRENT_INDEX);
    EXPECT_EQ(tabBarAccessibilityProperty->GetEndIndex(), END_INDEX);
}

/**
 * @tc.name: TabBarAccessibilityPropertyTestNg004
 * @tc.desc: Test the SupportActions property of tabbar.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAccessibilityPropertyTestNg004, TestSize.Level1)
{
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    RefPtr<GeometryNode> geometryNode_ = Ace::Referenced::MakeRefPtr<GeometryNode>();
    tabBarNode->SetGeometryNode(geometryNode_);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->currentOffset_ = DEFAULT_OFFSET;
    tabBarPattern->tabItemOffsets_.emplace_back(CURRENT_OFFSET);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    accessibilityProperty->ResetSupportAction();
    std::unordered_set<AceAction> supportAceActions = accessibilityProperty->GetSupportAction();
    uint64_t actions = 0, exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_BACKWARD);
    for (auto action : supportAceActions) {
        actions |= 1UL << static_cast<uint32_t>(action);
    }
    EXPECT_EQ(actions, exptectActions);
}

/**
 * @tc.name: TabsModelSetBarOverlap001
 * @tc.desc: test SetBarOverlap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarOverlap001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto layoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto barPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(barPaintProperty, nullptr);

    /**
     * @tc.steps: steps2. SetBarOverlap true
     * @tc.expected: steps2. Check the BarOverlap property value
     */
    tabsModel.SetBarOverlap(true);
    EXPECT_TRUE(layoutProperty->GetBarOverlap().value());

    tabsModel.SetBarOverlap(false);
    EXPECT_FALSE(layoutProperty->GetBarOverlap().value());

    barPaintProperty->UpdateBarBackgroundColor(Color::RED);

    tabsModel.SetBarOverlap(true);
    EXPECT_TRUE(layoutProperty->GetBarOverlap().value());

    tabsModel.SetBarOverlap(false);
    EXPECT_FALSE(layoutProperty->GetBarOverlap().value());
}

/**
 * @tc.name: TabsEventHubChangeEvent001
 * @tc.desc: Tabs OnChangeEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsEventHubChangeEvent001, TestSize.Level1)
{
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
    divider.isNull = false;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetOnChangeEvent([](const BaseEventInfo* info) {});
    tabsModel.SetDivider(divider);
    auto frameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    ASSERT_NE(pattern->onIndexChangeEvent_, nullptr);
}

void BuildTabBar(const RefPtr<TabsNode>& tabsNode, TabBarStyle tabBarStyle1, TabBarStyle tabBarStyle2)
{
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    tabContentPattern->SetTabBarStyle(tabBarStyle1);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, 0, false);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern2, nullptr);
    tabContentFrameNode2->MountToParent(swiperNode);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    tabContentPattern2->SetTabBarStyle(tabBarStyle2);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel2.AddTabBarItem(tabContentFrameNode2, 1, false);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange001
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange002
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange003
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange004
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a sub style tabbar and a bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange005
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two sub style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish001
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, 0, true);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->MaskAnimationFinish(tabBarNode, 1, false);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish002
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, 0, false);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->MaskAnimationFinish(tabBarNode, 1, true);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternChangeMask001
 * @tc.desc: test ChangeMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternChangeMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call ChangeMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    auto tabBarGeometryNode = tabBarNode->GetGeometryNode();
    ASSERT_NE(tabBarGeometryNode, nullptr);
    auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();

    auto mockRenderContext1 = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext1, nullptr);
    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode->GetChildAtIndex(tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    ASSERT_NE(maskNode1, nullptr);
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());
    ASSERT_NE(imageNode1, nullptr);
    imageNode1->renderContext_ = mockRenderContext1;
    EXPECT_CALL(*mockRenderContext1, SetVisible(_)).Times(1);

    auto mockRenderContext2 = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext2, nullptr);
    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode->GetChildAtIndex(tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    ASSERT_NE(maskNode2, nullptr);
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());
    ASSERT_NE(imageNode2, nullptr);
    imageNode2->renderContext_ = mockRenderContext2;
    EXPECT_CALL(*mockRenderContext2, SetVisible(_)).Times(1);

    tabBarPattern->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 1.0f, TEST_MASK_MIDDLE_RADIUS_RATIO, true);
    tabBarPattern->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 0.99f, TEST_MASK_MIDDLE_RADIUS_RATIO, false);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    ASSERT_NE(selectedImageNode, nullptr);
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    ASSERT_NE(selectedImageRenderContext, nullptr);
    EXPECT_DOUBLE_EQ(selectedImageRenderContext->GetOpacity().value(), 1.0f);
    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    auto unSelectedImageNode = AceType::DynamicCast<FrameNode>(unselectedMaskNode->GetChildren().front());
    ASSERT_NE(unSelectedImageNode, nullptr);
    auto unSelectedImageRenderContext = unSelectedImageNode->GetRenderContext();
    ASSERT_NE(unSelectedImageRenderContext, nullptr);
    EXPECT_DOUBLE_EQ(unSelectedImageRenderContext->GetOpacity().value(), 0.99f);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor001
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateImageColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. call UpdateImageColor function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern->UpdateImageColor(0);
    EXPECT_NE(tabBarNode->GetChildAtIndex(0), nullptr);
    tabBarPattern->UpdateImageColor(1);
    EXPECT_NE(tabBarNode->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
    tabBarPattern->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask001
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateSelectedMask and UpdateUnselectedMask.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateSelectedMask(0);
    tabBarLayoutProperty->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarLayoutProperty);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step3. call LayoutMask function.
     * @tc.expected: step3. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask002
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build selectedMaskNode and unselectedMaskNode.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
    EXPECT_EQ(tabBarLayoutProperty->GetSelectedMask().value_or(-1), -1);
    EXPECT_EQ(tabBarLayoutProperty->GetUnselectedMask().value_or(-1), -1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask003
 * @tc.desc: test LayoutMask
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build layoutWrapper.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. call LayoutMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, {});
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint001
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode and ideaSize.
     */

    LayoutConstraintF childConstraint = LayoutConstraintF();
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    std::optional<int32_t> tabBarTestId_(tabsFrameNode->GetTabBarId());
    auto tabBarNode = GroupNode::GetFrameNode(V2::TAB_BAR_ETS_TAG, tabBarTestId_.value());
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);

    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::HORIZONTAL;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->UpdateChildConstraint(
                    childConstraint, tabBarProperty, ideaSize, childCount, axis);
                axis = Axis::VERTICAL;
            }
            tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            axis = Axis::HORIZONTAL;
        }
        tabBarProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
        tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    }
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight002
 * @tc.desc: test MeasureMaxHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureMaxHeight002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    SizeF frameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. call MeasureMaxHeight function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths002
 * @tc.desc: test MeasureItemWidths
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureItemWidths002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());

    /**
     * @tc.steps: step2. call MeasureItemWidths function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);

    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, 5);
    EXPECT_EQ(tabBarLayoutAlgorithm->maxHeight_, 0);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003
 * @tc.desc: test HandleAlwaysAverageSplitLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. call HandleAlwaysAverageSplitLayoutStyle function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);

    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002
 * @tc.desc: test HandleSpaceBetweenOrCenterLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    SizeF frameSize(SizeF(0.0f, 0.0f));
    /**
     * @tc.steps: step2. call HandleSpaceBetweenOrCenterLayoutStyle function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridSizeType002
 * @tc.desc: test GetGridSizeType
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetGridSizeType002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    /**
     * @tc.steps: step2. call GetGridSizeType function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->GetGridSizeType(FIRST_ITEM_SIZE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateBackChildrenMainSize001
 * @tc.desc: test CalculateBackChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateBackChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. call UpdateSelectedMask and UpdateUnselectedMask.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateSelectedMask(0);
    tabBarLayoutProperty->UpdateUnselectedMask(1);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarLayoutProperty);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    int32_t indicator = -2;
    auto axis = Axis::HORIZONTAL;

    /**
     * @tc.steps: step2. build selectedMaskNode.
     */
    for (int i = 0; i <= 2; i++) {
        auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
        auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
        ASSERT_NE(selectedMaskNode, nullptr);
        RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper = AceType::MakeRefPtr<LayoutWrapperNode>(
            selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
        layoutWrapper.AppendChild(selectedMaskLayoutWrapper);
    }

    /**
     * @tc.steps: step3. call CalculateBackChildrenMainSize function.
     * @tc.expected: The function is run ok.
     */
    for (int i = 0; i <= 1; i++) {
        ASSERT_FLOAT_EQ(tabBarLayoutAlgorithm->CalculateBackChildrenMainSize(&layoutWrapper, indicator, axis), 0.0f);
        indicator = -1;
    }
}

/**
 * @tc.name: TabsModelSetBarBackgroundColor001
 * @tc.desc: test SetBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);

    /**
     * @tc.steps: steps2. SetBarBackgroundColor true
     * @tc.expected: steps2. Check the BarBarBackgroundColor property value
     */
    Color color = Color::RED;
    tabsModel.SetBarBackgroundColor(color);
    EXPECT_EQ(tabBarPaintProperty->GetBarBackgroundColor().value_or(Color::BLACK), color);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: TabBar Accessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, PerformActionTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabBar frameNode and pattern, set callback function.
     * @tc.expected: Related function is called.
     */
    auto controller = AceType::MakeRefPtr<SwiperController>();
    ASSERT_NE(controller, nullptr);
    auto frameNode =
        FrameNode::GetOrCreateFrameNode(V2::TAB_BAR_ETS_TAG, ViewStackProcessor::GetInstance()->ClaimNodeId(),
            [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });
    ASSERT_NE(frameNode, nullptr);
    auto tabBarPattern = frameNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    tabBarPattern->SetAccessibilityAction();

    /**
     * @tc.steps: step2. Get tabBar accessibilityProperty to call callback function.
     * @tc.expected: Related function is called.
     */
    auto tabBarAccessibilityProperty = frameNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(tabBarAccessibilityProperty, nullptr);

    /**
     * @tc.steps: step3. When tabBar TabBarMode is FIXED and child is null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step4. When tabBar TabBarMode is SCROLLABLE and child is null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step5. When tabBar TabBarMode is SCROLLABLE and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    columnNode1->MountToParent(frameNode);

    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    columnNode2->MountToParent(frameNode);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());

    /**
     * @tc.steps: step6. When tabBar TabBarMode is FIXED and child is not null, call the callback function in
     *                   tabBarAccessibilityProperty.
     * @tc.expected: Related function is called.
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollForward());
    EXPECT_TRUE(tabBarAccessibilityProperty->ActActionScrollBackward());
}

/**
 * @tc.name: TabsModelSetTabBarWidth001
 * @tc.desc: test SetTabBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetTabBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    Dimension tabBarWidth = 10.0_vp;
    Dimension tabBarHeight = 3.0_vp;

    /**
     * @tc.steps: step2. Test function SetTabBarWidth and SetTabBarHeight When tabBarWidth and tabBarHeight change.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabsModel.SetTabBarWidth(tabBarWidth);
        tabsModel.SetTabBarHeight(tabBarHeight);
        tabBarWidth = -1.0_vp;
        tabBarHeight = -1.0_vp;
    }
}

/**
 * @tc.name: TabsModelSetAnimationDuration001
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    bool duration = true;

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabsModel.SetAnimationDuration(duration);
        duration = false;
    }
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode001
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelGetOrCreateTabsNode001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    const std::string tag = "TabsID";
    int32_t nodeId = 1;

    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
}

/**
 * @tc.name: TabBarPatternInitClick001
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->clickEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitClick(gestureHub);
        tabBarPattern->clickEvent_ = AceType::MakeRefPtr<ClickEvent>([](GestureEvent&) {});
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable001
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto axis_test = Axis::HORIZONTAL;
    tabBarPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(axis_test);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->InitScrollable(gestureHub);
            tabBarPattern->axis_ = Axis::VERTICAL;
        }
        tabBarPattern->scrollableEvent_ = nullptr;
    }
}

/**
 * @tc.name: TabBarPatternInitTouche001
 * @tc.desc: test InitTouch, InitHoverEvent and InitMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTouche001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->touchEvent_ = AceType::MakeRefPtr<TouchEventImpl>([](TouchEventInfo&) {});
    tabBarPattern->hoverEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});
    tabBarPattern->mouseEvent_ = AceType::MakeRefPtr<InputEvent>([](MouseInfo&) {});

    /**
     * @tc.steps: step2. Test function InitTouch, InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->InitTouch(gestureHub);
    tabBarPattern->InitHoverEvent();
    tabBarPattern->InitMouseEvent();
}

/**
 * @tc.name: TabBarPatternHandleMouseEvent001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->HandleMouseEvent(info);
        }
        tabBarPattern->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarmodifieronDraw002
 * @tc.desc: test onDraw
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifieronDraw002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabBarmodifier
     */

    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    ASSERT_NE(tabBarModifier, nullptr);

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    /**
     * @tc.steps: step2. Test function onDraw.
     * @tc.expected: Related function runs ok.
     */
    float height = 1.0f;
    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    tabBarModifier->hasIndicator_ = nullptr;
    tabBarModifier->indicator_.SetHeight(height);
    tabBarModifier->onDraw(context);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent002
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->Clean(false, false);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function GetBottomTabBarImageSizeAndOffset.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    tabBarPattern->HandleMouseEvent(info);
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }

    Offset s1(0.1, 0.1);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset001
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    std::vector<int32_t> selectedIndexes(1, 1);
    float selectedImageSize = 1.0f;
    float unselectedImageSize = 1.1f;
    OffsetF originalSelectedMaskOffset(1.0f, 1.1f);
    OffsetF originalUnselectedMaskOffset(0.0f, 1.0f);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode->Clean(false, false);
    }
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent003
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    Offset s1(0.2, 0.2);
    Offset s2(0.3, 0.3);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    info.SetLocalLocation(s1);
    tabBarPattern->tabItemOffsets_ = { c1, c2, c3 };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleMouseEvent(info);
        info.SetLocalLocation(s2);
    }
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick001
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleBottomTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick002
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleSubTabBarClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto layoutProperty = AceType::MakeRefPtr<TabBarLayoutProperty>();
    int32_t index = 1;
    SizeF size(0.1f, 0.2f);
    tabBarNode->GetGeometryNode()->SetFrameSize(size);
    tabBarPattern->SetChildrenMainSize(0.3f);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->currentIndex_ = 0;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->axis_ = Axis::HORIZONTAL;

    int32_t nodeId = 1;
    for (int i = 0; i <= 4; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    tabBarNode->GetGeometryNode()->GetFrameSize().SetMainSize(2.0f, Axis::HORIZONTAL);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index));
    auto childGeometryNode = childFrameNode->GetGeometryNode();
    childGeometryNode->GetMarginFrameSize().SetMainSize(1.0f, Axis::HORIZONTAL);
    auto childFrameNode1 = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(index - 1));
    auto childGeometryNode1 = childFrameNode1->GetGeometryNode();
    auto childFrameSize1 = childGeometryNode1->GetMarginFrameSize();
    childFrameSize1.SetMainSize(0.1f, Axis::HORIZONTAL);
    OffsetF c1(0.1f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);

    /**
     * @tc.steps: step2. Test function HandleSubTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern->HandleSubTabBarClick(layoutProperty, index);
        layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternOnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarLayoutProperty->UpdateIndicator(2);
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent001
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode->TotalChildCount(), 2);
}

/**
 * @tc.name: TabBarmodifierPaintIndicator001
 * @tc.desc: test PaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarmodifierPaintIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabBarmodifier
     */

    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, AttachBrush(_)).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DetachBrush()).WillRepeatedly(ReturnRef(rsCanvas));
    EXPECT_CALL(rsCanvas, DrawRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, DrawRoundRect(_)).Times(AnyNumber());
    EXPECT_CALL(rsCanvas, Restore()).Times(AnyNumber());

    DrawingContext context { rsCanvas, 10.0f, 10.0f };
    RectF indicator(0.0f, 0.0f, 1.0f, 1.0f);
    tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});
    tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 1.0f; }, [](const float&) {});

    /**
     * @tc.steps: step2. Test function PaintIndicator.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarModifier->PaintIndicator(context, indicator);
        tabBarModifier->indicatorHeight_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorWidth_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorMarginTop_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
        tabBarModifier->indicatorBorderRadius_->SetUpCallbacks([]() { return 0.0f; }, [](const float&) {});
    }
}

/**
 * @tc.name: TabBarPatternHandleHoverEvent001
 * @tc.desc: test HandleHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleHoverEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    bool isHover = true;
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverEvent.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleHoverEvent(isHover);
                isHover = false;
                tabBarPattern->hoverIndex_ = {};
            }
            tabBarPattern->hoverIndex_ = hoverIndex_test;
        }
        isHover = true;
        tabBarPattern->hoverIndex_ = {};
    }

    isHover = false;
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = {};
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleHoverEvent(isHover);
        tabBarPattern->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabBarPatternHandleHoverOnEvent001
 * @tc.desc: test HandleHoverOnEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleHoverOnEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    std::optional<int32_t> hoverIndex_test(0);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = hoverIndex_test;

    /**
     * @tc.steps: step2. Test function HandleHoverOnEvent.
     * @tc.expected: Related functions run ok.
     */
    IndicatorStyle style;
    style.color = Color::BLACK;
    tabBarPattern->hoverIndex_ = hoverIndex_test;
    tabBarPattern->touchingIndex_ = {};
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetSelectedMode(SelectedMode::BOARD, 0);
    tabBarPattern->SetIndicatorStyle(style, 0);

    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleHoverOnEvent(0);
        tabBarPattern->AddTabBarItemType(1, true);
    }
}

/**
 * @tc.name: TabsModelSetOnChange001
 * @tc.desc: test SetOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetOnChange001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. Test function SetOnChange.
     * @tc.expected: Related function runs ok.
     */
    tabsModel.SetOnChange(nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
}

/**
 * @tc.name: TabsModelNg001
 * @tc.desc: Tabs Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelNg001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    /**
     * @tc.steps: step2.1. Test SetOnAnimationStart function.
     * @tc.expected:eventHub->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    tabsModel.SetOnAnimationStart(std::move(onAnimationStart));
    EXPECT_NE(pattern->animationStartEvent_, nullptr);

    /**
     * @tc.steps: step2.2. Test SetOnAnimationEnd function.
     * @tc.expected:pattern->animationEndEvent_ not null.
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    tabsModel.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);

    /**
     * @tc.steps: step2.3. Test SetOnGestureSwipe function.
     * @tc.expected:eventHub->gestureSwipeEvent_ not null.
     */
    auto onGestureSwipe = [](int32_t index, const AnimationCallbackInfo& info) {};
    tabsModel.SetOnGestureSwipe(std::move(onGestureSwipe));
    EXPECT_NE(eventHub->gestureSwipeEvent_, nullptr);
}

/**
 * @tc.name: TabsModelSetScrollable001
 * @tc.desc: test SetScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. Test function SetScrollable.
     * @tc.expected: Related function runs ok.
     */
    tabsModel.SetScrollable(true);
    tabsModel.SetScrollable(false);
}

/**
 * @tc.name: TabsModelSetClipEdge001
 * @tc.desc: test SetClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetClipEdge001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: step2. Test function SetClipEdge.
     * @tc.expected: Related function runs ok.
     */
    tabsModel.SetClipEdge(true);
    tabsModel.SetClipEdge(false);
}
/**
 * @tc.name: TabBarPatternOnKeyEvent002
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    KeyCode code = KeyCode::KEY_CLEAR;
    KeyAction action = KeyAction::CLICK;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);

    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->OnKeyEvent(event);
                event.action = KeyAction::DOWN;
                event.code = KeyCode::KEY_DPAD_LEFT;
            }
            event.code = KeyCode::KEY_DPAD_UP;
        }
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->OnKeyEvent(event);
                event.code = KeyCode::KEY_DPAD_RIGHT;
            }
            event.code = KeyCode::KEY_DPAD_DOWN;
        }
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    }
    event.code = KeyCode::KEY_TAB;
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->OnKeyEvent(event);
        tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(-2);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent002
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    EXPECT_EQ(swiperNode->TotalChildCount(), 2);

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    tabBarPattern->HandleTouchEvent(touchLocationInfo);
    EXPECT_EQ(tabBarNode->TotalChildCount(), 2);
}

/**
 * @tc.name: TabBarPatternFocusIndexChange001
 * @tc.desc: test FocusIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternFocusIndexChange001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    std::optional<int32_t> animation_test = 1;

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->FocusIndexChange(index);
        tabBarPattern->animationDuration_ = animation_test;
    }
}

/**
 * @tc.name: TabBarPatternOnModifyDone001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->OnModifyDone();
        tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternHandleClick002
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function HandleClick.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleClick(info);
                tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::FIXED);
            }
            tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
        }
        tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    }

    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    auto springController = AceType::MakeRefPtr<Animator>();
    springController->SetTempo(0.1f);
    springController->status_ = Animator::Status::RUNNING;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleClick(info);
        tabBarPattern->scrollableEvent_ = scrollableEvent;
    }

    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->HandleClick(info);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish003
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternMaskAnimationFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t selectedIndex = -1;
    bool isSelected = true;

    /**
     * @tc.steps: step2. Test function MaskAnimationFinish.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->MaskAnimationFinish(tabBarNode, selectedIndex, isSelected);
}

/**
 * @tc.name: TabBarDistributedTest001
 * @tc.desc: Test the distributed capability of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarDistributedTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutProperty = tabBarPattern->GetLayoutProperty<TabsLayoutProperty>();

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern->UpdateIndicator(0);
    std::string ret = tabBarPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    restoreInfo_ = R"({"Index":1})";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    restoreInfo_ = "invalid_json_string";
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternHandleTouchDown001
 * @tc.desc: test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchDown001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetRemoveSwiperEventCallback(nullptr);
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchDown.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchDown(index);
        tabBarPattern->swiperController_->SetRemoveSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern->SetTouching(false);
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchUp(index);
        tabBarPattern->swiperController_->SetAddSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchUp002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    tabBarPattern->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern->SetTouching(true);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->hoverIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern->hoverIndex_.value(), 1);
    tabBarPattern->touchingIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern->touchingIndex_.value(), 1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleTouchUp(index);
                tabBarPattern->SetTouching(true);
                tabBarPattern->swiperController_->SetAddSwiperEventCallback([]() {});
                tabBarPattern->hoverIndex_.reset();
                EXPECT_FALSE(tabBarPattern->hoverIndex_.has_value());
            }
            tabBarPattern->touchingIndex_.emplace(0);
        }
        tabBarPattern->hoverIndex_.emplace(1);
    }

    tabBarPattern->hoverIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchUp(index);
        tabBarPattern->SetTouching(true);
        tabBarPattern->hoverIndex_.emplace(1);
    }
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation002
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayPressAnimation002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 1;
    auto pressColor = Color();
    pressColor.SetValue(1);
    auto animationType = AnimationType::HOVERTOPRESS;
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function PlayPressAnimation.
     * @tc.expected: Related functions run ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern->PlayPressAnimation(index, pressColor, animationType);
        animationType = AnimationType::HOVER;
    }
}

/**
 * @tc.name: TabBarPatternStopTabBarTranslateAnimation001
 * @tc.desc: test StopTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternStopTabBarTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function StopTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->StopTabBarTranslateAnimation();
    }
    EXPECT_FALSE(tabBarPattern->tabBarTranslateAnimation_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect001
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);

    tabBarPattern->tabBarType_.emplace(std::make_pair(1, true));

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchEvent(touchLocationInfo);
        tabBarPattern->tabBarType_.clear();
        tabBarNode->RemoveChildAtIndex(1);
    }
    EXPECT_EQ(tabBarNode->TotalChildCount(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColor001
 * @tc.desc: test UpdateTextColor and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 0;
    auto pr = tabBarPattern->tabBarType_.emplace(std::make_pair(1, true));
    ASSERT_TRUE(pr.second);
    /**
     * @tc.steps: step2. Test function UpdateTextColor and UpdateImageColor.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->UpdateTextColor(index);
    tabBarPattern->UpdateImageColor(index);
}

/**
 * @tc.name: TabBarPatternUpdateTextColor002
 * @tc.desc: test UpdateTextColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateTextColor002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t index = 0;
    for (int i = 0; i <= 1; i++) {
        AceType::DynamicCast<FrameNode>(
            AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(i))->GetChildren().back())
            ->layoutProperty_ = AceType::MakeRefPtr<TextLayoutProperty>();
        ASSERT_NE(AceType::DynamicCast<FrameNode>(
                      AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(i))->GetChildren().back())
                      ->layoutProperty_,
            nullptr);
    }

    /**
     * @tc.steps: step2. Test function UpdateTextColor.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->UpdateTextColor(index);
}

/**
 * @tc.name: TabBarPatternInitClick002
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitClick002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->clickEvent_ = nullptr;
    auto info = GestureEvent();

    /**
     * @tc.steps: step2. Test function InitClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->InitClick(gestureHub);
    tabBarPattern->clickEvent_->callback_(info);
}

/**
 * @tc.name: TabBarPatternInitScrollable002
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitScrollable(gestureHub);
        tabBarPattern->swiperController_->tabBarFinishCallback_();
        scrollableEvent->SetScrollable(nullptr);
        tabBarPattern->scrollableEvent_ = scrollableEvent;
    }
}

/**
 * @tc.name: TabBarPatternInitScrollable003
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern->axis_ = Axis::VERTICAL;
            tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_START);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    int32_t source = SCROLL_FROM_UPDATE;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->InitScrollable(gestureHub);
        scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
        scrollable->callback_(0.1, source);
        tabBarPattern->axis_ = Axis::VERTICAL;
        tabBarPattern->tabItemOffsets_.clear();
        tabBarPattern->tabItemOffsets_ = { { 1.0f, -1.0f } };
        tabBarNode->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 2.0f));
    }
}

/**
 * @tc.name: TabBarPatternInitHoverEvent001
 * @tc.desc: test InitHoverEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitHoverEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->hoverEvent_ = nullptr;
    tabBarPattern->mouseEvent_ = nullptr;
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function InitHoverEvent and InitMouseEvent.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern->InitHoverEvent();
    tabBarPattern->InitMouseEvent();
    ASSERT_NE(tabBarPattern->hoverEvent_, nullptr);
    ASSERT_NE(tabBarPattern->mouseEvent_, nullptr);
    tabBarPattern->hoverEvent_->onHoverCallback_(true);
    tabBarPattern->mouseEvent_->onMouseCallback_(info);
}

/**
 * @tc.name: TabBarPatternInitOnKeyEvent001
 * @tc.desc: test InitOnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitOnKeyEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto focusHub = tabBarNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);
    auto event = KeyEvent();
    auto paintRect = RoundRect();

    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->InitOnKeyEvent(focusHub);
    focusHub->ProcessOnKeyEventInternal(event);
    focusHub->getInnerFocusRectFunc_(paintRect);
}

/*
 * @tc.name: TabBarPatternHandleMouseEvent004
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleMouseEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto info = MouseInfo();

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), -1);
    tabBarPattern->hoverIndex_.emplace(1);
    tabBarPattern->tabItemOffsets_ = { c1, c2, c3, c4 };
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    IndicatorStyle indicatorStyle3;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    indicatorStyle3.color = Color::BLUE;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
        TabBarStyle::NOSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2, indicatorStyle3 };

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern->HandleMouseEvent(info);
            info.SetLocalLocation(s2);
            ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), 2);
            tabBarPattern->hoverIndex_.reset();
        }
        tabBarPattern->hoverIndex_.emplace(1);
        tabBarPattern->touchingIndex_.emplace(1);
    }

    Offset s3(0.2, 0.2);
    info.SetLocalLocation(s3);
    ASSERT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    info.SetAction(MouseAction::MOVE);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleMouseEvent(info);
                tabBarPattern->touchingIndex_.reset();
                tabBarPattern->hoverIndex_ = 1;
            }
            tabBarPattern->hoverIndex_.reset();
        }
        tabBarPattern->hoverIndex_.emplace(0);
        info.SetAction(MouseAction::WINDOW_ENTER);
    }

    info.SetAction(MouseAction::WINDOW_LEAVE);
    tabBarPattern->HandleMouseEvent(info);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent003
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function OnKeyEvent.
     * @tc.expected: Related functions run ok.
     */
    KeyCode code = KeyCode::KEY_DPAD_LEFT;
    KeyAction action = KeyAction::DOWN;
    std::vector<KeyCode> pressedCodes;
    pressedCodes.emplace_back(KeyCode::KEY_0);
    pressedCodes.emplace_back(KeyCode::KEY_1);
    int32_t repeatTime = 1;
    int64_t timeStamp = 0;
    std::chrono::milliseconds milliseconds(timeStamp);
    TimeStamp time(milliseconds);
    int32_t metaKey = 1;
    int64_t deviceId = 1;
    SourceType sourceType = SourceType::NONE;
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>()->UpdateIndicator(1);
    auto event = KeyEvent(code, action, pressedCodes, repeatTime, time, metaKey, deviceId, sourceType, {});
    tabBarPattern->OnKeyEvent(event);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout002
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateTabBarMode(TabBarMode::FIXED);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);

    tabBarLayoutAlgorithm->Layout(&layoutWrapper);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayout003
 * @tc.desc: Test Divider Layout.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayout003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call Layout function.
     * @tc.expected: Related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    ASSERT_NE(geometryNode, nullptr);
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    auto layoutWrapper1 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper1, nullptr);
    auto layoutWrapper2 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper2, nullptr);
    auto layoutWrapper3 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper3, nullptr);
    auto layoutWrapper4 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper4, nullptr);
    auto layoutWrapper5 = AceType::MakeRefPtr<LayoutWrapperNode>(
        tabBarNode, geometryNode, tabBarNode->GetLayoutProperty<TabBarLayoutProperty>());
    ASSERT_NE(layoutWrapper5, nullptr);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateIndicator(1);
    tabBarLayoutAlgorithm->indicator_ = 0;
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(0.1f, 0.2f));
    tabBarLayoutAlgorithm->childrenMainSize_ = 0.3f;
    layoutWrapper.AppendChild(layoutWrapper1);
    layoutWrapper.AppendChild(layoutWrapper2);
    layoutWrapper.AppendChild(layoutWrapper3);
    layoutWrapper.AppendChild(layoutWrapper4);
    layoutWrapper.AppendChild(layoutWrapper5);
    layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarLayoutAlgorithm->Layout(&layoutWrapper);
                tabBarLayoutAlgorithm->indicator_ = 2;
                tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
            }
            layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
            layoutWrapper1->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
            layoutWrapper2->GetGeometryNode()->SetFrameSize(SizeF(0.0f, 0.0f));
        }
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::VERTICAL);
    }

    layoutWrapper3->GetGeometryNode()->SetFrameSize(SizeF(2.0f, 2.0f));
    for (int i = 0; i <= 1; i++) {
        tabBarLayoutAlgorithm->Layout(&layoutWrapper);
        AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty())->UpdateAxis(Axis::HORIZONTAL);
    }
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation001
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayMaskAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function PlayMaskAnimation.
     * @tc.expected: Related function runs ok.
     */
    float selectedImageSize = 0.1f;
    OffsetF originalSelectedMaskOffset(0.1f, 0.2f);
    int32_t selectedIndex = 1;
    float unselectedImageSize = 0.2f;
    OffsetF originalUnselectedMaskOffset(0.1f, 0.2f);
    int32_t unselectedIndex = 1;

    auto mockRenderContext1 = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext1, nullptr);
    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode->GetChildAtIndex(tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    ASSERT_NE(maskNode1, nullptr);
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());
    ASSERT_NE(imageNode1, nullptr);
    imageNode1->renderContext_ = mockRenderContext1;
    EXPECT_CALL(*mockRenderContext1, SetVisible(_)).Times(1);

    auto mockRenderContext2 = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext2, nullptr);
    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode->GetChildAtIndex(tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    ASSERT_NE(maskNode2, nullptr);
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());
    ASSERT_NE(imageNode2, nullptr);
    imageNode2->renderContext_ = mockRenderContext2;
    EXPECT_CALL(*mockRenderContext2, SetVisible(_)).Times(1);

    tabBarPattern->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent004
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleTouchEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarNode1 = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode1, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabsNode1 =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, 1, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    tabBarNode->AddChild(tabsNode1);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(1.0f, 1.0f));
    tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern->HandleTouchEvent(touchLocationInfo);
        touchLocationInfo.SetLocalLocation(Offset(-1.0f, -1.0f));
    }
    EXPECT_EQ(tabBarNode->TotalChildCount(), 3);
    tabBarPattern->touchingIndex_ = 1;
    touchLocationInfo.SetTouchType(TouchType::UP);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->HandleTouchEvent(touchLocationInfo);
                tabBarPattern->touchingIndex_ = 1;
                touchLocationInfo.SetTouchType(TouchType::CANCEL);
            }
            touchLocationInfo.SetTouchType(TouchType::DOWN);
        }
        tabBarPattern->touchingIndex_.reset();
    }
}

/**
 * @tc.name: TabBarPatternPlayTranslateAnimation001
 * @tc.desc: test PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    float startPos = 0.1f;
    float endPos = 0.2f;
    float targetCurrentOffset = 0.3f;
    auto offset = 0.1f;
    tabBarPattern->currentOffset_ = offset;
    tabBarPattern->PlayTranslateAnimation(startPos, endPos, targetCurrentOffset);
    EXPECT_FALSE(tabBarPattern->indicatorAnimationIsRunning_);
    EXPECT_FALSE(tabBarPattern->translateAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
}

/**
 * @tc.name: TabBarPatternPlayTabBarTranslateAnimation001
 * @tc.desc: test PlayTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternPlayTabBarTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    int32_t targetIndex = 1;
    tabBarPattern->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    tabBarNode->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    tabBarPattern->childrenMainSize_ = 0.1f;
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto tabsNode = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode->AddChild(tabsNode);
    }
    AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(targetIndex + 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Test function PlayTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern->PlayTabBarTranslateAnimation(targetIndex);
    EXPECT_FALSE(tabBarPattern->tabBarTranslateAnimationIsRunning_);
}

void FocusTest(const RefPtr<TabBarLayoutProperty>& tabBarLayoutProperty, const RefPtr<TabBarPattern>& tabBarPattern)
{
    KeyEvent event;
    event.action = KeyAction::DOWN;

    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_SPACE;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_LEFT;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_ENTER;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_TAB;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    event.code = KeyCode::KEY_DPAD_DOWN;
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
    event.code = KeyCode::KEY_DPAD_UP;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabBarPatternOnKeyEvent004
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_MOVE_HOME;
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE);
    tabBarPattern->focusIndicator_ = 1;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    event.code = KeyCode::KEY_MOVE_END;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_TRUE(tabBarPattern->OnKeyEvent(event));

    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent005
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent006
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent006, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = true;

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->SetFirstFocus(true);
    FocusTest(tabBarLayoutProperty, tabBarPattern);
}

/**
 * @tc.name: TabBarPatternOnKeyEvent007
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnKeyEvent007, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::NOSTYLE, TabBarStyle::NOSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. OnKeyEvent
     * @tc.expected: steps2. Check the result of OnKeyEvent
     */
    tabsNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::END);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    pipeline->isFocusActive_ = false;
    event.code = KeyCode::KEY_DPAD_RIGHT;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));

    pipeline->isFocusActive_ = true;
    event.code = KeyCode::KEY_A;
    tabBarPattern->focusIndicator_ = 0;
    EXPECT_FALSE(tabBarPattern->OnKeyEvent(event));
}

/**
 * @tc.name: TabsPatternGetScopeFocusAlgorithm001
 * @tc.desc: test GetScopeFocusAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetScopeFocusAlgorithm001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition001
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarPattern->AdjustFocusPosition();
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition002
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(1.0f, 1.0f);
    OffsetF c2(100.0f, 100.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternCreateNodePaintMethod001
 * @tc.desc: test CreateNodePaintMethod
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCreateNodePaintMethod001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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

    /**
     * @tc.steps: steps2. CreateNodePaintMethod
     * @tc.expected: steps2. Check the result of CreateNodePaintMethod
     */
    auto tabBarRenderContext = tabBarFrameNode->GetRenderContext();
    ASSERT_NE(tabBarRenderContext, nullptr);
    tabBarRenderContext->UpdateBackgroundColor(Color::RED);
    auto paintMethod = tabBarPattern->CreateNodePaintMethod();
    ASSERT_NE(paintMethod, nullptr);
    EXPECT_EQ(tabBarRenderContext->GetBackgroundColor().value(), Color::RED);
}

/**
 * @tc.name: TabsModelSetOnTabBarClick001
 * @tc.desc: Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetOnTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: steps2. SetOnTabBarClick
     * @tc.expected: steps2. Check the result of SetOnTabBarClick
     */
    tabsModel.SetOnTabBarClick([](const BaseEventInfo* info) {});
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabsNode, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_NE(pattern->onTabBarClickEvent_, nullptr);

    tabsModel.SetOnTabBarClick([](const BaseEventInfo* info) {});
    EXPECT_NE(pattern->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternGetNextFocusNode001
 * @tc.desc: test GetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetOrCreateFocusHub();
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto swiperFocusNode = swiperNode->GetFocusHub();
    ASSERT_NE(swiperFocusNode, nullptr);
    auto tabBarFocusNode = tabBarNode->GetFocusHub();
    ASSERT_NE(tabBarFocusNode, nullptr);

    /**
     * @tc.steps: steps2. GetNextFocusNode
     * @tc.expected: steps2. Check the result of GetNextFocusNode
     */
    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN, tabBarFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::UP, tabBarFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT, tabBarFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::UP, tabBarFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, tabBarFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, tabBarFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::UP_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::START);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::LEFT_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::DOWN_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::UP, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateTabBarPosition(BarPosition::END);
    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT, swiperFocusNode);
    tabsPattern->GetNextFocusNode(FocusStep::RIGHT_END, swiperFocusNode);
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);
}

/**
 * @tc.name: TabBarPatternInitScrollable004
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern->axis_ = Axis::VERTICAL;
            tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern->tabItemOffsets_ = { { -1.0f, -1.0f } };
    }
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->currentOffset_ = DEFAULT_OFFSET;
    auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_AXIS);
    scrollable->callback_(1.1, SCROLL_FROM_AXIS);
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle001
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->swiperStartIndex_ = 0;
    IndicatorStyle indicator;
    tabBarPattern->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator);
    IndicatorStyle indicator1;
    indicator1.width = -1.0_vp;
    tabBarPattern->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[1], indicator1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->turnPageRate_ = -0.9f;
    IndicatorStyle indicator2;
    tabBarPattern->GetIndicatorStyle(indicator2);
    indicator1.width = 1.0_vp;
    tabBarPattern->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[1], indicator1);
    tabBarPattern->GetIndicatorStyle(indicator2);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->turnPageRate_ = 0.9f;
    IndicatorStyle indicator3;
    tabBarPattern->GetIndicatorStyle(indicator3);
    tabBarPattern->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator3);
    tabBarPattern->indicator_ = -1;
    tabBarPattern->GetIndicatorStyle(indicator2);
    tabBarPattern->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[1], indicator1);
    tabBarPattern->GetIndicatorStyle(indicator3);
    tabBarPattern->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern->indicatorStyles_[0], indicator3);
}

/**
 * @tc.name: TabBarPatternCheckSwiperDisable001
 * @tc.desc: test CheckSwiperDisable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCheckSwiperDisable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. CheckSwiperDisable
     * @tc.expected: steps2. Check the result of CheckSwiperDisable
     */
    EXPECT_EQ(tabBarPattern->CheckSwiperDisable(), false);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator001
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->ApplyTurnPageRateToIndicator(2.0f);
    tabBarPattern->ApplyTurnPageRateToIndicator(-2.0f);
    EXPECT_EQ(tabBarPattern->turnPageRate_, 0.0f);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->ApplyTurnPageRateToIndicator(0.9f);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.9f);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.9f);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutMask004
 * @tc.desc: Test the LayoutMask function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutMask004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabsModel.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateSelectedMask(0);
    tabBarLayoutProperty->UpdateUnselectedMask(1);
    std::vector<OffsetF> childOffsetDelta = { OffsetF(), OffsetF() };
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarLayoutProperty);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));

    /**
     * @tc.steps: step2. build selectedMaskNode and unselectedMaskNode.
     */
    auto selectedmaskPosition = tabBarNode->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(selectedmaskPosition));
    ASSERT_NE(selectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> selectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(selectedMaskNode, geometryNode1, selectedMaskNode->GetLayoutProperty());
    layoutWrapper.AppendChild(selectedMaskLayoutWrapper);

    auto unselectedmaskPosition = tabBarNode->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode->GetChildAtIndex(unselectedmaskPosition));
    ASSERT_NE(unselectedMaskNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    auto unselectedProperty = unselectedMaskNode->GetLayoutProperty();
    RefPtr<LayoutWrapperNode> unselectedMaskLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(unselectedMaskNode, geometryNode2, unselectedProperty);
    layoutWrapper.AppendChild(unselectedMaskLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a child named imageLayoutWrapper for currentWrapper.
     */
    auto currentWrapper = selectedMaskLayoutWrapper;
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    ASSERT_NE(imageNode, nullptr);
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(imageLayoutProperty, nullptr);
    selectedMaskLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: step4. call LayoutMask function.
     * @tc.expected: step4. expect The function is run ok.
     */
    auto mockRenderContext = AceType::MakeRefPtr<MockRenderContext>();
    ASSERT_NE(mockRenderContext, nullptr);
    imageNode->renderContext_ = mockRenderContext;
    EXPECT_CALL(*mockRenderContext, SetVisible(_)).Times(1);

    tabBarLayoutAlgorithm->LayoutMask(&layoutWrapper, childOffsetDelta);
    EXPECT_EQ(tabBarLayoutProperty->GetSelectedMask().value_or(-1), 0);
    EXPECT_EQ(tabBarLayoutProperty->GetUnselectedMask().value_or(-1), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetGridWidth001
 * @tc.desc: Test the GetGridWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetGridWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);

    /**
     * @tc.steps: steps2. Create different conditions for GetGridWidth.
     */
    int32_t columns = -10;
    auto frameSize = SizeF(1.0f, 1.0f);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(tabBarNode->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);
    BarGridColumnOptions option;
    float resultWidth1 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);
    columns = 10;
    float resultWidth2 = tabbarLayoutAlgorithm->GetGridWidth(option, frameSize, columns);

    /**
     * @tc.steps: steps3. GetGridWidth.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_EQ(resultWidth1, 0.0f);
    EXPECT_EQ(resultWidth2, columns * frameSize.Width() / XS_COLUMN_NUM);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyBarGridAlign001
 * @tc.desc: Test the ApplyBarGridAlign function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplyBarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);

    /**
     * @tc.steps: steps2. Create different conditions for ApplyBarGridAlign.
     */
    BarGridColumnOptions option;
    option.sm = 6;
    instance.SetBarGridAlign(option);
    auto frameSize = SizeF(400.0f, 400.0f);
    float result1 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.md = 10;
    instance.SetBarGridAlign(option);
    frameSize = SizeF(800.0f, 800.0f);
    float result2 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 16;
    instance.SetBarGridAlign(option);
    frameSize = SizeF(1000.0f, 1000.0f);
    float result3 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = -2;
    instance.SetBarGridAlign(option);
    float result4 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);
    option.lg = 2;
    instance.SetBarGridAlign(option);
    float result5 = tabbarLayoutAlgorithm->ApplyBarGridAlign(tabBarProperty, frameSize);

    /**
     * @tc.steps: steps3. ApplyBarGridAlign.
     * @tc.expected: steps3. Cexpect The function is run ok.
     */
    EXPECT_EQ(result1, 0.0f);
    EXPECT_EQ(result2, 0.0f);
    EXPECT_EQ(result3, 0.0f);
    EXPECT_EQ(result4, 0.0f);
    float columnWidth = frameSize.Width() / LG_COLUMN_NUM;
    float expectedWidth = (LG_COLUMN_NUM - option.lg) * columnWidth / 2;
    EXPECT_EQ(NearEqual(result5, expectedWidth), true);
}

/**
 * @tc.name: TabBarLayoutAlgorithmConfigHorizontal001
 * @tc.desc: Test the ConfigHorizontal function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmConfigHorizontal001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    instance.SetBarGridAlign(option);
    auto frameSize = SizeF(1000.0f, 1000.0f);

    /**
     * @tc.steps: steps3. ConfigHorizontal.
     * @tc.expected: steps3. Check the results of ConfigHorizontal under different conditions.
     */
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    childCount = 1;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    ScrollableBarModeOptions options;
    options.margin = 0.0_vp;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    layoutProperty->UpdateBarAdaptiveHeight(true);
    tabbarLayoutAlgorithm->ConfigHorizontal(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->scrollMargin_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto frameSize = SizeF(20.0f, 20.0f);
    int32_t childCount = 2;
    tabbarLayoutAlgorithm->childrenMainSize_ = 10000.0f;
    tabbarLayoutAlgorithm->scrollMargin_ = 10000.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);

    /**
     * @tc.steps: steps2. HandleAlwaysAverageSplitLayoutStyle.
     * @tc.expected: steps2. Check itemWidths after HandleAlwaysAverageSplitLayoutStyle by using different itemWidths.
     */
    frameSize = SizeF(0.0f, 0.0f);
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();

    float itemWidth = 1000.0f;
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);

    itemWidth = 10.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);

    itemWidth = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(itemWidth);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], itemWidth);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[1], itemWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001
 * @tc.desc: Test the HandleSpaceBetweenOrCenterLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    int32_t childCount = 2;

    /**
     * @tc.steps: steps2. Create two children for layoutWrapper.
     */
    auto tabBarNode_test = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode_test, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test, geometryNode3, tabBarNode_test->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);
    auto tabBarNode_test1 = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode_test1, nullptr);
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test1, geometryNode4, tabBarNode_test1->GetLayoutProperty());
    tabBarLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper1);

    /**
     * @tc.steps: steps3.  Create a padding and assign it an initial value.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    layoutProperty->UpdatePadding(padding);

    /**
     * @tc.steps: steps4.  Create different conditions for entering a branch for HandleSpaceBetweenOrCenterLayoutStyle.
     */
    tabbarLayoutAlgorithm->childrenMainSize_ = 100000.0f;
    auto frameSize = SizeF(150.0f, 150.0f);
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(2.0f);
    tabbarLayoutAlgorithm->childrenMainSize_ = 149.5f;
    tabbarLayoutAlgorithm->scrollMargin_ = 1.0f;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);
    tabbarLayoutAlgorithm->childrenMainSize_ = 10.0f;
    tabbarLayoutAlgorithm->scrollMargin_ = 2.0f;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper, frameSize, childCount);

    /**
     * @tc.steps: steps5. HandleSpaceBetweenOrCenterLayoutStyle.
     * @tc.expected: steps5. Check the result of childrenMainSize.
     */
    EXPECT_EQ(tabbarLayoutAlgorithm->childrenMainSize_, 6.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureItemWidths001
 * @tc.desc: Test the MeasureItemWidths function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureItemWidths001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(imageLayoutProperty, nullptr);
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);
    int32_t childCount = 3;
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->scrollMargin_ = 0.0f;

    /**
     * @tc.steps: steps5.MeasureItemWidths.
     * @tc.expected: steps5. Testing childrenMainSize under MeasureItemWidths Value of.
     */
    tabbarLayoutAlgorithm->MeasureItemWidths(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->childrenMainSize_, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmMeasureMaxHeight001
 * @tc.desc: Test the MeasureMaxHeight function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmMeasureMaxHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    tabbarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: steps2. Set itemWidths_ Clear and reassign and
     *                    Create two children named columnLayoutWrapper using a loop for layoutWrapper.
     */
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
    for (int32_t i = 0; i < 2; i++) {
        auto columnNode =
            FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
                []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        ASSERT_NE(columnNode, nullptr);
        RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> columnLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
        columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
        columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
        layoutWrapper.AppendChild(columnLayoutWrapper);
    }

    /**
     * @tc.steps: steps3.MeasureMaxHeight.
     * @tc.expected: steps3. Test itemWidths under MeasureMaxHeight Value of.
     */
    int32_t childCount = 2;
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(2.0f);
    tabbarLayoutAlgorithm->MeasureMaxHeight(&layoutWrapper, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], 10.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplyLayoutMode001
 * @tc.desc: Test the ApplyLayoutMode function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplyLayoutMode001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto bottomTabBarStyle = tabBarPattern->GetBottomTabBarStyle(0);

    /**
     * @tc.steps: steps2. Create two children named columnLayoutWrapper and columnLayoutWrapper1 for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode3, columnNode1->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode4, columnNode2->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);

    /**
     * @tc.steps: steps3. Using a loop to create two children named textLayoutWrapper for columnLayoutWrapper.
     */
    for (int32_t i = 0; i < 2; i++) {
        auto textId = ElementRegister::GetInstance()->MakeUniqueId();
        auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
        RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
        RefPtr<LayoutWrapperNode> textLayoutWrapper =
            AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode5, textNode->GetLayoutProperty());
        columnLayoutWrapper->AppendChild(textLayoutWrapper);
    }
    float allocatedWidth = 0.0f;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps4. ApplyLayoutMode.
     * @tc.expected: steps4. Create different conditions and check the result of ApplyLayoutMode.
     */
    bottomTabBarStyle.layoutMode = LayoutMode::VERTICAL;
    tabBarPattern->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    bottomTabBarStyle.layoutMode = LayoutMode::AUTO;
    tabBarPattern->SetBottomTabBarStyle(bottomTabBarStyle, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 200000.0f;
    tabbarLayoutAlgorithm->ApplyLayoutMode(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_FALSE(linearLayoutProperty->IsVertical());
}

/**
 * @tc.name: TabBarLayoutAlgorithmLayoutChildren001
 * @tc.desc: Test the LayoutChildren function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmLayoutChildren001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(tabBarNode->GetLayoutProperty());

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);
    layoutProperty->UpdatePadding(padding);
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    layoutWrapper.currentChildCount_ = 5;
    auto frameSize = SizeF(0.0f, 0.0f);
    auto axis = Axis::HORIZONTAL;
    tabbarLayoutAlgorithm->childrenMainSize_ = 10000.0f;
    OffsetF childOffset(0.0f, 0.0f);
    tabbarLayoutAlgorithm->LayoutChildren(&layoutWrapper, frameSize, axis, childOffset);

    /**
     * @tc.steps: steps3. LayoutChildren.
     * @tc.expected: steps3. Verify childrenMainSize under LayoutChildren Value of.
     */
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetX(), childOffset.GetX());
    EXPECT_EQ(tabbarLayoutAlgorithm->tabItemOffset_[0].GetY(), childOffset.GetY());
}

/**
 * @tc.name: TabBarLayoutAlgorithmGetContentWidth001
 * @tc.desc: Test the GetContentWidth function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmGetContentWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto frameSize = SizeF(0.0f, 0.0f);

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(200.0_vp);
    padding.right = CalcLength(200.0_vp);
    padding.top = CalcLength(200.0_vp);
    padding.bottom = CalcLength(200.0_vp);

    /**
     * @tc.steps: steps3. GetContentWidth.
     * @tc.expected: steps3. Check the result of GetContentWidth.
     */
    layoutProperty->UpdatePadding(padding);
    float resultWidth = tabbarLayoutAlgorithm->GetContentWidth(layoutProperty, frameSize);
    EXPECT_EQ(resultWidth, 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible001
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children named columnLayoutWrapper1, columnLayoutWrapper2,
     *                    and columnLayoutWrapper3 for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);

    /**
     * @tc.steps: steps3. Test ApplySymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 0.0f;
    int32_t childCount = 1;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_NE(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    childCount = 3;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 3);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_.size(), 1);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);

    /**
     * @tc.steps: steps4. ApplySymmetricExtensible.
     * @tc.expected: steps4. Check the result of ApplySymmetricExtensible.
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW_REVERSE);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    allocatedWidth = 100000.0f;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], allocatedWidth);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(imageLayoutProperty, nullptr);
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    float allocatedWidth = 0.0f;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(10.0f);
    std::vector<float> spaceRequests;
    spaceRequests.clear();
    spaceRequests.emplace_back(10.0f);
    std::vector<float> leftBuffers;
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    std::vector<float> rightBuffers;
    rightBuffers.clear();
    rightBuffers.emplace_back(10.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    leftBuffers.clear();
    leftBuffers.emplace_back(0.0f);
    leftBuffers.emplace_back(0.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(0.0f);
    rightBuffers.emplace_back(0.0f);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. erify itemWidths in CalculateItemWidthsForSymmetricExtensible Value of.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarPaintMethodGetForegroundDrawFunction002
 * @tc.desc: Test the GetForegroundDrawFunction function in the TabBarPaintMethod class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPaintMethodGetForegroundDrawFunction002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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
    auto geometryNode = tabBarFrameNode->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 20.0f;
    padding.right = 20.0f;
    padding.top = 20.0f;
    padding.bottom = 20.0f;
    geometryNode->UpdatePaddingWithBorder(padding);
    PaintWrapper paintWrapper(tabBarFrameNode->GetRenderContext(), geometryNode, paintProperty);
    auto drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper);
    ASSERT_NE(drawFunction, nullptr);

    paintProperty = tabBarPattern->CreatePaintProperty();
    auto tabBarPaintProperty = AceType::DynamicCast<TabBarPaintProperty>(paintProperty);
    tabBarPaintProperty->UpdateFadingEdge(false);

    /**
     * @tc.steps: steps3. GetForegroundDrawFunction.
     * @tc.expected: steps3. expect The function is run ok.
     */
    EXPECT_FALSE(tabBarPaintProperty->GetFadingEdgeValue());
    PaintWrapper paintWrapper2(tabBarFrameNode->GetRenderContext(), tabBarFrameNode->GetGeometryNode(), paintProperty);
    drawFunction = paintMethod->GetForegroundDrawFunction(&paintWrapper2);
    ASSERT_EQ(drawFunction, nullptr);
    auto clone = paintProperty->Clone();
    EXPECT_NE(clone, nullptr);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto frameSize = SizeF(3000.0f, 3000.0f);
    tabbarLayoutAlgorithm->scrollMargin_ = 0.0f;
    int32_t childCount = 1;

    /**
     * @tc.steps: steps2. HandleAlwaysAverageSplitLayoutStyle.
     * @tc.expected: steps2. Check itemWidths in CalculateItemWidthsForSymmetricExtensible Value of.
     */
    tabbarLayoutAlgorithm->childrenMainSize_ = 0.0f;
    tabbarLayoutAlgorithm->itemWidths_.clear();
    tabbarLayoutAlgorithm->itemWidths_.emplace_back(0.0f);
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, frameSize, childCount);
    EXPECT_EQ(tabbarLayoutAlgorithm->itemWidths_[0], 3000.0f);
}

/**
 * @tc.name: TabContentModelAddTabBarItem002
 * @tc.desc: Test the AddTabBarItem function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelAddTabBarItem002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
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

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->UpdateSubTabBoard();

    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), selectedMode);
    tabContentFrameNode->GetTabBarItemId();

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);

    /**
     * @tc.steps: steps2. AddTabBarItem.
     * @tc.expected: steps2. expect The function is run ok.
     */
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetLayoutMode(LayoutMode::HORIZONTAL);
    tabContentPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, false);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
}

/**
 * @tc.name: TabContentModelSetPadding001
 * @tc.desc: Test the SetPadding function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    tabContentModel.Create();
    tabContentModel.SetPadding(padding);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    /**
     * @tc.steps: steps3. SetPadding.
     * @tc.expected: steps3. Check if the setting value for padding was successful.
     */
    EXPECT_EQ(tabContentPattern->GetPadding().left, padding.left);
    EXPECT_EQ(tabContentPattern->GetPadding().right, padding.right);
    EXPECT_EQ(tabContentPattern->GetPadding().top, padding.top);
    EXPECT_EQ(tabContentPattern->GetPadding().bottom, padding.bottom);
}

/**
 * @tc.name: TabContentModelSetLayoutMode001
 * @tc.desc: Test the SetLayoutMode function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetLayoutMode001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;
    LayoutMode layoutMode = LayoutMode::AUTO;
    tabContentModel.Create();
    tabContentModel.SetLayoutMode(layoutMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    /**
     * @tc.steps: steps2. SetLayoutMode.
     * @tc.expected: steps2. Check if the value set for layoutMode was successful.
     */
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().layoutMode, layoutMode);
}

/**
 * @tc.name: TabContentModelSetVerticalAlign001
 * @tc.desc: Test the SetVerticalAlign function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetVerticalAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;
    FlexAlign verticalAlign = FlexAlign::CENTER;
    tabContentModel.Create();
    tabContentModel.SetVerticalAlign(verticalAlign);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    /**
     * @tc.steps: steps2. SetVerticalAlign.
     * @tc.expected: steps2. Check if the value set for verticalAlign was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().verticalAlign, verticalAlign);
}

/**
 * @tc.name: TabContentModelSetSymmetricExtensible001
 * @tc.desc: Test the SetSymmetricExtensible function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelSetSymmetricExtensible001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;
    bool isExtensible = true;
    tabContentModel.Create();
    tabContentModel.SetSymmetricExtensible(isExtensible);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);

    /**
     * @tc.steps: steps2. SetSymmetricExtensible.
     * @tc.expected: steps2. Check the result of SetSymmetricExtensible.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().symmetricExtensible, isExtensible);
}

/**
 * @tc.name: TabContentNodelConvertFlexAlignToString001
 * @tc.desc: Test the ConvertFlexAlignToString function in the TabContentNodel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentNodelConvertFlexAlignToString001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    FlexAlign verticalAlign = FlexAlign::FLEX_START;
    tabContentFrameNode->ConvertFlexAlignToString(verticalAlign);
    verticalAlign = FlexAlign::FLEX_END;
    tabContentFrameNode->ConvertFlexAlignToString(verticalAlign);

    /**
     * @tc.steps: steps2. ConvertFlexAlignToString.
     * @tc.expected: steps2. Check the result of ConvertFlexAlignToString.
     */
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentFrameNode->ConvertFlexAlignToString(verticalAlign), "VerticalAlign.Bottom");
}

/**
 * @tc.name: TabContentNodelConvertLayoutModeToString001
 * @tc.desc: Test the ConvertLayoutModeToString function in the TabContentNodel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabContentNodelConvertLayoutModeToString001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());

    /**
     * @tc.steps: steps2. Set different values for layoutMode to enter different branches.
     */
    LayoutMode layoutMode = LayoutMode::VERTICAL;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);
    layoutMode = LayoutMode::HORIZONTAL;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);
    layoutMode = LayoutMode::AUTO;
    tabContentFrameNode->ConvertLayoutModeToString(layoutMode);

    /**
     * @tc.steps: steps3. ConvertLayoutModeToString.
     * @tc.expected: steps3. Check the result of ConvertLayoutModeToString.
     */
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentFrameNode->ConvertLayoutModeToString(layoutMode), "LayoutMode.AUTO");
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: Test the AdjustFocusPosition function in the TabBarPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(0.0f, 0.0f);
    OffsetF c2(10.0f, 10.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->tabItemOffsets_.emplace_back(c2);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto geometryNode = tabBarNode->GetGeometryNode();

    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    MarginPropertyF padding;
    padding.left = 10000.0f;
    padding.right = 10000.0f;
    padding.top = 10000.0f;
    padding.bottom = 10000.0f;
    geometryNode->UpdatePaddingWithBorder(padding);

    /**
     * @tc.steps: steps3. AdjustFocusPosition.
     * @tc.expected: steps3. Check the value of TabBarStyle under the AdjustFocusPosition function.
     */
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->currentOffset_, padding.left);
}

/**
 * @tc.name: TabsModelSetBarAdaptiveHeight001
 * @tc.desc: Test the SetBarAdaptiveHeight function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarAdaptiveHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    bool barAdaptiveHeight = false;
    tabsModel.SetBarAdaptiveHeight(barAdaptiveHeight);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. SetBarAdaptiveHeight.
     * @tc.expected: steps2. Check the result of SetBarAdaptiveHeight.
     */
    EXPECT_TRUE(tabBarLayoutProperty->GetBarAdaptiveHeight());
}

/**
 * @tc.name: TabsModelSetScrollableBarModeOptions001
 * @tc.desc: Test the SetScrollableBarModeOptions function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetScrollableBarModeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);

    /**
     * @tc.steps: steps2. SetScrollableBarModeOptions.
     * @tc.expected: steps2. Check if the SetScrollableBarModeOptions function successfully sets
     *                       ScrollableBarModeOptions.
     */
    ScrollableBarModeOptions option;
    option.margin = 0.0_vp;
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabsModel.SetScrollableBarModeOptions(option);
    EXPECT_EQ(tabBarProperty->GetScrollableBarModeOptions(), option);
}

/**
 * @tc.name: TabsModelSetBarGridAlign001
 * @tc.desc: Test the SetBarGridAlign function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetBarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);

    /**
     * @tc.steps: steps2. Create BarGridColumnOptions and assign them initial values.
     */
    BarGridColumnOptions BarGridColumnOptions;
    BarGridColumnOptions.sm = -1;
    BarGridColumnOptions.md = -1;
    BarGridColumnOptions.lg = -1;
    BarGridColumnOptions.gutter = 0.0_vp;
    BarGridColumnOptions.margin = 0.0_vp;
    tabsModel.SetBarGridAlign(BarGridColumnOptions);

    /**
     * @tc.steps: steps3. SetBarGridAlign.
     * @tc.expected: steps3. Check if the SetBarGridAlign function has successfully set BarGridColumnOptions.
     */
    EXPECT_EQ(tabBarProperty->GetBarGridAlign(), BarGridColumnOptions);
}

/**
 * @tc.name: TabsNodeToJsonValue001
 * @tc.desc: Test the ToJsonValue function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeToJsonValue001, TestSize.Level2)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabsNode->tabBarId_ = tabsNode->GetTabBarId();

    /**
     * @tc.steps: steps2. Create ScrollableBarModeOptions and assign them different values to enter different branches.
     */
    ScrollableBarModeOptions options;
    options.margin = 0.0_vp;
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabsNode->ToJsonValue(json);
    options.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabsNode->ToJsonValue(json);
    options.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    tabBarLayoutProperty->UpdateScrollableBarModeOptions(options);
    tabsNode->ToJsonValue(json);

    /**
     * @tc.steps: steps3. ToJsonValue.
     * @tc.expected: steps3. Check the result of ToJsonValue.
     */
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: TabsNodeGetScrollableBarModeOptions001
 * @tc.desc: Test the GetScrollableBarModeOptions function in the TabsNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsNodeGetScrollableBarModeOptions001, TestSize.Level2)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScrollableBarModeOptions.
     * @tc.expected: steps2. Check the result of GetScrollableBarModeOptions.
     */
    tabsNode->GetScrollableBarModeOptions();
    tabsNode->tabBarId_ = tabsNode->GetTabBarId();
    ScrollableBarModeOptions option = tabsNode->GetScrollableBarModeOptions();
    EXPECT_EQ(option.margin.Value(), 0.0f);
    EXPECT_EQ(option.nonScrollableLayoutStyle, LayoutStyle::ALWAYS_CENTER);
    tabsNode->tabBarId_ = {};
    option = tabsNode->GetScrollableBarModeOptions();
    EXPECT_EQ(option.margin.Value(), 0.0f);
    EXPECT_EQ(option.nonScrollableLayoutStyle, LayoutStyle::ALWAYS_CENTER);
}

/**
 * @tc.name: TabBarLayoutAlgorithmApplySymmetricExtensible002
 * @tc.desc: Test the ApplySymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmApplySymmetricExtensible002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(1000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(2000.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(3000.0f);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create three children for layoutWrapper in sequence.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper1 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    columnLayoutWrapper1->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper1->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper1);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper2 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode2, geometryNode3, columnNode2->GetLayoutProperty());
    columnLayoutWrapper2->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper2->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper2);
    auto columnNode3 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    RefPtr<GeometryNode> geometryNode7 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper3 =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode3, geometryNode7, columnNode3->GetLayoutProperty());
    columnLayoutWrapper3->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper3->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper3);
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper1->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);

    /**
     * @tc.steps: steps3. ApplySymmetricExtensible.
     * @tc.expected: steps3. Check the value of itemWidths under the ApplySymmetricExtensible function.
     */
    float allocatedWidth = 0.0f;
    int32_t childCount = 3;
    tabBarLayoutAlgorithm->ApplySymmetricExtensible(&layoutWrapper, allocatedWidth, childCount);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 0.0f);
}

/**
 * @tc.name: TabBarLayoutAlgorithmAdjustFixedItem001
 * @tc.desc: Test the AdjustFixedItem function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmAdjustFixedItem001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabsModel.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto axis = Axis::HORIZONTAL;
    auto frameSize = OptionalSizeF(0.0f, 0.0f);

    /**
     * @tc.steps: step2. Create a child named childwrapper for layoutWrapper.
     */
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> childWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode1, geometryNode2, columnNode1->GetLayoutProperty());
    childWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    childWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(childWrapper);

    /**
     * @tc.steps: steps3. AdjustFixedItem.
     * @tc.expected: steps3. Check the result of AdjustFixedItem.
     */
    childWrapper->GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    axis = Axis::VERTICAL;
    tabBarLayoutAlgorithm->AdjustFixedItem(childWrapper, frameSize, axis);
    EXPECT_EQ(childWrapper->GetGeometryNode()->GetFrameSize(), SizeF(0.0f, 0.0f));
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure001
 * @tc.desc: Test the Measure function in the TabsLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabsModel
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: steps2. Test Measure by using different conditions.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;
    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: step3. Create a child named swiperLayoutWrapper for layoutWrapper.
     */
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateTabBarPosition(BarPosition::START);
    layoutWrapper.GetGeometryNode()->SetFrameSize(SizeF(10000.0f, 10000.0f));
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(true);

    /**
     * @tc.steps: steps4. Measure.
     * @tc.expected: steps4. Check the result of BarOverlap.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_TRUE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
    tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->UpdateBarOverlap(false);
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    EXPECT_FALSE(tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>()->GetBarOverlap().value());
}

/**
 * @tc.name: TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002
 * @tc.desc: Test the CalculateItemWidthsForSymmetricExtensible function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCalculateItemWidthsForSymmetricExtensible002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create tabsModel.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabBarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Create a child for layoutWrapper.
     */
    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode, nullptr);
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> columnLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(columnNode, geometryNode2, columnNode->GetLayoutProperty());
    columnLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    columnLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(columnLayoutWrapper);

    /**
     * @tc.steps: steps3. Create a first child named imageLayoutWrapper for columnLayoutWrapper.
     */
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    RefPtr<GeometryNode> geometryNode5 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> imageLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(imageNode, geometryNode5, imageNode->GetLayoutProperty());
    auto imageLayoutProperty = AceType::DynamicCast<ImageLayoutProperty>(imageLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(imageLayoutProperty, nullptr);
    columnLayoutWrapper->AppendChild(imageLayoutWrapper);

    /**
     * @tc.steps: steps4. Create a second child named textLayoutWrapper for columnLayoutWrapper.
     */
    auto linearLayoutProperty = AceType::DynamicCast<LinearLayoutProperty>(columnLayoutWrapper->GetLayoutProperty());
    ASSERT_NE(linearLayoutProperty, nullptr);
    auto textId = ElementRegister::GetInstance()->MakeUniqueId();
    auto textNode = FrameNode::CreateFrameNode(V2::TEXT_ETS_TAG, textId, AceType::MakeRefPtr<TextPattern>());
    RefPtr<GeometryNode> geometryNode4 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> textLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(textNode, geometryNode4, textNode->GetLayoutProperty());
    columnLayoutWrapper->AppendChild(textLayoutWrapper);

    /**
     * @tc.steps: steps5. Test CalculateItemWidthsForSymmetricExtensible by using different conditions.
     */
    float allocatedWidth = 100.0f;
    int32_t childCount = 2;
    std::vector<float> spaceRequests;
    std::vector<float> leftBuffers;
    std::vector<float> rightBuffers;
    tabBarLayoutAlgorithm->itemWidths_.clear();
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    tabBarLayoutAlgorithm->itemWidths_.emplace_back(100.0f);
    spaceRequests.clear();
    spaceRequests.emplace_back(100.0f);
    spaceRequests.emplace_back(100.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(100.0f);
    leftBuffers.emplace_back(100.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(100.0f);
    rightBuffers.emplace_back(100.0f);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    spaceRequests.clear();
    spaceRequests.emplace_back(0.0f);
    spaceRequests.emplace_back(0.0f);
    leftBuffers.clear();
    leftBuffers.emplace_back(10.0f);
    leftBuffers.emplace_back(10.0f);
    rightBuffers.clear();
    rightBuffers.emplace_back(30.0f);
    rightBuffers.emplace_back(30.0f);
    linearLayoutProperty->UpdateFlexDirection(FlexDirection::ROW);

    /**
     * @tc.steps: steps6. CalculateItemWidthsForSymmetricExtensible.
     * @tc.expected: steps6. Check the value of itemWidths in the CalculateItemWidthsForSymmetricExtensible function.
     */
    tabBarLayoutAlgorithm->CalculateItemWidthsForSymmetricExtensible(
        &layoutWrapper, childCount, spaceRequests, leftBuffers, rightBuffers, allocatedWidth);
    EXPECT_EQ(tabBarLayoutAlgorithm->itemWidths_[0], 60.0f);
}

/**
 * @tc.name: TabBarOnAttachToMainTree001.
 * @tc.desc: Test the OnAttachToMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarOnAttachToMainTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContentNode.
     */
    TabContentModelNG tabContentModel;
    LabelStyle labelStyle;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    /**
     * @tc.steps: step2. Invoke OnAttachToMainTree.
     */
    tabContentFrameNode->useOffscreenProcess_ = false;
    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_EQ(tabContentFrameNode->useOffscreenProcess_, false);
    tabContentFrameNode->useOffscreenProcess_ = true;
    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_EQ(tabContentFrameNode->useOffscreenProcess_, true);
}

/**
 * @tc.name: TabBarAddChildToGroup001.
 * @tc.desc: Test the AddChildToGroup function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, AddChildToGroup001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContentNode.
     */

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
    divider.isNull = false;

    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);

    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    /**
     * @tc.steps: step2. Invoke OnAttachToMainTree.
     */

    tabsNode->AddChildToGroup(tabContentFrameNode, 1);
    EXPECT_NE(tabsNode, nullptr);
    tabsNode->swiperChildren_.insert(1);
    tabsNode->swiperChildren_.insert(2);
    tabsNode->AddChildToGroup(tabContentFrameNode, 1);
    EXPECT_NE(tabsNode, nullptr);
    auto tabBarNodeswiper =
        FrameNode::GetOrCreateFrameNode("test", 2, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    tabsNode->children_.clear();
    tabsNode->children_.push_back(tabBarNodeswiper);
    tabContentFrameNode->nodeId_ = 0;
    tabsNode->AddChildToGroup(tabContentFrameNode, 1);
    EXPECT_NE(tabBarNodeswiper, nullptr);
}

/**
 * @tc.name: OnDetachFromMainTree001.
 * @tc.desc: Test the OnDetachFromMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, OnDetachFromMainTree001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create TabContentNode.
     */
    TabContentModelNG tabContentModel;
    LabelStyle labelStyle;
    tabContentModel.Create();
    tabContentModel.SetLabelStyle(labelStyle);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto* stack = ViewStackProcessor::GetInstance();
    ASSERT_NE(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    auto controller = AceType::MakeRefPtr<SwiperController>();
    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarId = tabsNode->GetTabBarId();
    auto tabBarNode = FrameNode::GetOrCreateFrameNode(
        V2::TAB_BAR_ETS_TAG, tabBarId, [controller]() { return AceType::MakeRefPtr<TabBarPattern>(controller); });
    ASSERT_NE(tabBarNode, nullptr);
    tabContentFrameNode->MountToParent(tabsNode);
    auto tabBarNodeswiper =
        FrameNode::GetOrCreateFrameNode("test", 1, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    tabsNode->children_.clear();
    tabsNode->children_.push_back(tabBarNodeswiper);
    auto swiper = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    auto swiperPattern = AceType::DynamicCast<SwiperPattern>(swiper->GetPattern());
    /**
     * @tc.steps: step2. Invoke OnDetachFromMainTree.
     */

    tabContentFrameNode->OnDetachFromMainTree(true);
    EXPECT_NE(tabContentFrameNode, nullptr);
    swiperPattern->currentIndex_ = 1;
    tabContentFrameNode->OnDetachFromMainTree(true);
    EXPECT_NE(tabContentFrameNode, nullptr);
}

/**
 * @tc.name: SetOnChangeEvent001.
 * @tc.desc: Test the SetOnChangeEvent function in the TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

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
    pattern->onChangeEvent_ = std::make_shared<ChangeEvent>();
    pattern->SetOnChangeEvent([](const BaseEventInfo* info) {});
    ASSERT_NE(tabsFrameNode, nullptr);
    ASSERT_NE(pattern, nullptr);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->FireChangeEvent();
    ASSERT_NE(pattern, nullptr);
}

/**
 * @tc.name: TabPatternOnModifyDone001.
 * @tc.desc: test OnModifyDone in TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabPatternOnModifyDone001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabspattern.
     * @tc.expected: step2. creat tabspattern.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabspattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabspattern, nullptr);

    /**
     * @tc.steps: step3. invoke OnModifyDone and onChangeEvent_.
     * @tc.expected: step3. related function is called.
     */

    tabspattern->OnModifyDone();
    ASSERT_NE(tabspattern, nullptr);
    tabspattern->onChangeEvent_ = std::make_shared<ChangeEvent>();
    tabspattern->OnModifyDone();
    ASSERT_NE(tabspattern, nullptr);
}

/**
 * @tc.name: SetOnIndexChangeEvent001.
 * @tc.desc: test SetOnIndexChangeEvent in TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnIndexChangeEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. Get tabspattern.
     * @tc.expected: step2. creat tabspattern.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabspattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabspattern, nullptr);

    /**
     * @tc.steps: step3. invoke OnModifyDone and onChangeEvent_.
     * @tc.expected: step3. related function is called.
     */
    tabspattern->onIndexChangeEvent_ = std::make_shared<ChangeEvent>();
    tabspattern->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    ASSERT_NE(tabspattern, nullptr);
    tabspattern->onIndexChangeEvent_ = nullptr;
    tabspattern->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    ASSERT_NE(tabspattern, nullptr);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->FireChangeEvent();
    ASSERT_NE(tabspattern, nullptr);
}

/**
 * @tc.name: TabsModelSetAnimationDuration002
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    float duration = 1;

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    tabsModel.SetAnimationDuration(duration);
    EXPECT_FLOAT_EQ(duration, 1);
    duration = -1;
    tabsModel.SetAnimationDuration(duration);
    EXPECT_FLOAT_EQ(duration, -1);
}

/**
 * @tc.name: TabsModelSetAnimationDuration003
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelSetAnimationDuration003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    ASSERT_NE(tabTheme, nullptr);
    auto defaultDuration = tabTheme->GetTabContentAnimationDuration();

    /**
     * @tc.steps: step2. Test function SetAnimationDuration in APIVersion 10.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    ASSERT_FALSE(tabBarPattern->GetAnimationDuration().has_value());
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern->animationDuration_.reset();

    /**
     * @tc.steps: step3. Test function SetAnimationDuration in APIVersion 11.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern->animationDuration_.reset();

    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern->animationDuration_.reset();
    tabsModel.SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern->animationDuration_.reset();
}

/**
 * @tc.name: SetOnChangeEvent002.
 * @tc.desc: Test the SetOnChangeEvent function in the TabsPattern class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnChangeEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */

    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step2. set different conditions and invoke SetOnChangeEvent.
     * @tc.expected: step2. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabspattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabspattern, nullptr);
    tabspattern->onIndexChangeEvent_ = nullptr;
    tabspattern->SetOnIndexChangeEvent([](const BaseEventInfo* info) {});
    ASSERT_NE(tabspattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabBar());
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->FireChangeEvent();
    ASSERT_NE(tabspattern, nullptr);
    tabBarPattern->isMaskAnimationByCreate_ = true;
    swiperPattern->FireChangeEvent();
    ASSERT_NE(tabspattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    swiperPattern->FireChangeEvent();
    ASSERT_NE(tabspattern, nullptr);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    swiperPattern->FireChangeEvent();
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(Axis::HORIZONTAL), Axis::HORIZONTAL);
    tabBarPattern->changeByClick_ = true;
    swiperPattern->FireChangeEvent();
    ASSERT_NE(tabspattern, nullptr);
    tabspattern->SetOnTabBarClickEvent([](const BaseEventInfo* info) {});
    auto onTabBarClickEvent = tabspattern->GetTabBarClickEvent();
    (*onTabBarClickEvent)(1);
    EXPECT_NE(tabspattern->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternHandleClick003
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick003, TestSize.Level1)
{
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

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    info.SetSourceDevice(SourceType::KEYBOARD);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::HORIZONTAL);

    tabBarPattern->indicator_ = 1;
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarPattern->indicator_, 1);
    info.deviceType_ = SourceType::NONE;
    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(tabBarPattern->tabItemOffsets_.empty(), false);
}

/**
 * @tc.name: SetSpecificSupportAction
 * @tc.desc: Test the SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarAPSetSpecificSupportAction001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. creat accessibilityProperty in class.
     * @tc.expected: Successfully created.
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();
    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    /**
     * @tc.steps: step2. invoke SetSpecificSupportAction.
     * @tc.expected: Related function is called.
     */
    accessibilityProperty->SetSpecificSupportAction();
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    auto frameNode = accessibilityProperty->host_.Upgrade();
    ASSERT_NE(frameNode, nullptr);
    auto tabBarPattern = frameNode->GetPattern<TabBarPattern>();
    tabBarPattern->currentOffset_ = 1.0f;
    tabBarPattern->tabItemOffsets_ = { { 10.0f, 10.0f } };
    accessibilityProperty->SetSpecificSupportAction();
    EXPECT_TRUE(accessibilityProperty->IsScrollable());
}

/**
 * @tc.name: TabBarPatternGetInnerFocusPaintRect001
 * @tc.desc: test GetInnerFocusPaintRect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetInnerFocusPaintRect001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto focusHub = tabBarNode->GetOrCreateFocusHub();
    ASSERT_NE(focusHub, nullptr);

    /**
     * @tc.steps: step2. Test function InitOnKeyEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    tabBarPattern->isFirstFocus_ = true;
    auto event = KeyEvent();
    auto paintRect = RoundRect();
    tabBarPattern->GetInnerFocusPaintRect(paintRect);
    EXPECT_EQ(tabBarPattern->isFirstFocus_, true);
}

/**
 * @tc.name: TabBarPatternInitScrollable005
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitScrollable005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable in different conditons.
     * @tc.expected: Related function is called.
     */

    tabBarPattern->InitScrollable(gestureHub);
    ASSERT_NE(tabBarPattern->scrollableEvent_, nullptr);
    auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    ASSERT_NE(tabBarPattern->scrollableEvent_, nullptr);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    tabBarPattern->scrollableEvent_->scrollable_ = nullptr;
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    EXPECT_EQ(tabBarPattern->scrollableEvent_->scrollable_, nullptr);
}

/**
 * @tc.name: TabBarPatternHandleClick005
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick005, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    RefPtr<Scrollable> scrollable = AceType::MakeRefPtr<Scrollable>();
    ASSERT_NE(scrollable, nullptr);
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern->scrollableEvent_ = scrollableEvent;

    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    layoutProperty->UpdateAxis(Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. Test function HandleClick.
     * @tc.expected: Related functions run ok.
     */
    info.deviceType_ = SourceType::KEYBOARD;
    tabBarPattern->HandleClick(info);
    EXPECT_EQ(info.deviceType_, SourceType::KEYBOARD);
}

/**
 * @tc.name: TabsModelNGSetIndex001
 * @tc.desc: Test the SetIndex function in the TabsModelNG class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelNGSetIndex001, TestSize.Level2)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);
    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(1);
    auto swiperNodechild1 =
        FrameNode::GetOrCreateFrameNode("test1", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(swiperNodechild1, nullptr);
    auto swiperNodechild2 =
        FrameNode::GetOrCreateFrameNode("test2", 2, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(swiperNodechild2, nullptr);

    swiperNode->children_.clear();
    swiperNode->children_.push_back(swiperNodechild1);
    swiperNode->children_.push_back(swiperNodechild2);
    auto tabContentNum = swiperNode->TotalChildCount();
    EXPECT_EQ(tabContentNum, 2);
    /**
     * @tc.steps: steps2. GetScrollableBarModeOptions.
     * @tc.expected: steps2. Check the result of GetScrollableBarModeOptions.
     */
    tabsModel.SetIndex(1);
    EXPECT_EQ(tabContentNum, 2);
}

/**
 * @tc.name: TabContentNode::GetOrCreateTabContentNode
 * @tc.desc: Test TabContentNode::GetOrCreateTabContentNode
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, GetOrCreateTabContentNode001, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    tabContentModel.Create([]() {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto TabContentNode1 =
        TabContentNode::GetOrCreateTabContentNode("test", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(TabContentNode1, nullptr);
    auto TabContentNode2 =
        TabContentNode::GetOrCreateTabContentNode("test", 1, []() { return AceType::MakeRefPtr<Pattern>(); });
    ASSERT_NE(TabContentNode1, nullptr);
}

/**
 * @tc.name: TabBarPatternHandleClick006
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternHandleClick006, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::HORIZONTAL);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    auto host = tabBarPattern->GetHost();
    ASSERT_NE(host, nullptr);
    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    tabBarPattern->scrollableEvent_ = scrollableEvent;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    layoutProperty->UpdateAxis(Axis::HORIZONTAL);
    /**
     * @tc.steps: step2. Test function HandleClick.
     * @tc.expected: Related functions run ok.
     */
    info.deviceType_ = SourceType::MOUSE;
    tabBarPattern->scrollableEvent_->scrollable_ = AceType::MakeRefPtr<Scrollable>();
    auto scrollable = tabBarPattern->scrollableEvent_->GetScrollable();

    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    tabBarPattern->HandleClick(info);
    EXPECT_NE(tabBarPattern->scrollableEvent_->GetScrollable(), nullptr);
    EXPECT_NE(tabBarPattern->scrollableEvent_->GetScrollable()->IsSpringStopped(), false);
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED_START);
    tabBarPattern->HandleClick(info);
    EXPECT_NE(tabBarPattern->scrollableEvent_->GetScrollable(), nullptr);
    EXPECT_NE(tabBarPattern->scrollableEvent_->GetScrollable()->IsSpringStopped(), false);
}

/*
 * @tc.name: TabBarPatternCalculateSelectedIndex001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternCalculateSelectedIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto info = MouseInfo();
    Offset s1(0.1, 0.1);
    Offset s2(0.4, 0.4);
    OffsetF c0(0.0f, 0.0f);
    OffsetF c1(0.1f, 0.1f);
    OffsetF c2(0.2f, 0.2f);
    OffsetF c3(0.3f, 0.3f);
    OffsetF c4(0.4f, 0.4f);
    info.SetLocalLocation(s1);
    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */

    tabBarPattern->hoverIndex_.emplace(1);
    tabBarPattern->tabItemOffsets_ = { c1, c2, c3, c4 };
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->isRTL_ = true;
    tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_EQ(tabBarPattern->isRTL_, true);
    tabBarPattern->tabItemOffsets_ = { c0, c2, c3, c4 };
    tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation());
    EXPECT_EQ(tabBarPattern->CalculateSelectedIndex(info.GetLocalLocation()), -1);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle002
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternGetIndicatorStyle002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern->indicatorStyles_.clear();
    IndicatorStyle indicator;
    IndicatorStyle indicator2;
    tabBarPattern->indicator_ = -1;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->indicator_, -1);
    tabBarPattern->indicator_ = 0;
    tabBarPattern->GetIndicatorStyle(indicator);
    tabBarPattern->indicatorStyles_.push_back(indicator2);
    tabBarPattern->indicatorStyles_.push_back(indicator);
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->indicator_, 0);
    indicator.width.SetValue(1.0);
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(indicator.width.Value(), 0);
    tabBarPattern->isTouchingSwiper_ = false;
    tabBarPattern->GetIndicatorStyle(indicator);
    tabBarPattern->axis_ = Axis::FREE;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->axis_, Axis::FREE);
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->isTouchingSwiper_, true);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->axis_, Axis::HORIZONTAL);
    tabBarPattern->turnPageRate_ = 2.0f;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->turnPageRate_, 1.0f);
    tabBarPattern->swiperStartIndex_ = 1;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, 1);
    tabBarPattern->swiperStartIndex_ = 1;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabBarStyles_ = { tabBarStyles1, tabBarStyles2 };
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, 1);
    tabBarPattern->swiperStartIndex_ = -1;
    tabBarPattern->GetIndicatorStyle(indicator);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternOnModifyDone002
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnModifyDone002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateAxis(Axis::VERTICAL);
    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */

    tabBarPattern->OnModifyDone();
    EXPECT_NE(tabBarPattern, nullptr);
    auto layoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    EXPECT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->OnModifyDone();
    tabBarNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode->eventHub_);
    ASSERT_NE(tabBarNode->eventHub_->focusHub_, nullptr);
    tabsModel.Pop();
    EXPECT_NE(tabBarNode->eventHub_->focusHub_, nullptr);
    tabBarPattern->OnModifyDone();
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->swiperController_->removeTabBarEventCallback_();
    tabBarPattern->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern->swiperController_, nullptr);
}

/**
 * @tc.name: TabBarPatternIsAtBottom001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternIsAtBottom001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function IsAtBottom001.
     * @tc.expected: Related functions run ok.
     */

    tabBarPattern->tabItemOffsets_.clear();
    tabBarPattern->IsAtBottom();
    EXPECT_EQ(tabBarPattern->IsAtBottom(), false);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator002
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern->tabBarStyles_.clear();
    tabBarPattern->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern->selectedModes_.clear();
    tabBarPattern->selectedModes_.push_back(selectedMode1);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
    tabBarPattern->selectedModes_.clear();
    tabBarPattern->selectedModes_.push_back(selectedMode2);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->swiperStartIndex_ = 1;
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->swiperStartIndex_ = 2;
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->swiperStartIndex_ = -1;
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator003
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternApplyTurnPageRateToIndicator003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::SUBTABBATSTYLE;
    auto tabBarStyles2 = TabBarStyle::NOSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern->tabBarStyles_.clear();
    tabBarPattern->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern->selectedModes_.clear();
    tabBarPattern->selectedModes_.push_back(selectedMode1);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern->selectedModes_.push_back(selectedMode2);
    tabBarPattern->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, 0);

    /**
     * @tc.steps: steps3. ApplyTurnPageRateToIndicator
     * @tc.expected: steps3. Check the result of ApplyTurnPageRateToIndicator
     */

    tabBarPattern->swiperStartIndex_ = 0;
    auto tabBarStyles3 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode3 = SelectedMode::INDICATOR;
    tabBarPattern->tabBarStyles_.clear();
    tabBarPattern->tabBarStyles_.push_back(tabBarStyles3);
    tabBarPattern->selectedModes_.clear();
    tabBarPattern->selectedModes_.push_back(selectedMode3);
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->turnPageRate_ = 0.5f;
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
    tabBarPattern->swiperStartIndex_ = 0;
    tabBarPattern->turnPageRate_ = 0.5f;
    tabBarPattern->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent001
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTurnPageRateEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->turnPageRate_ = 1.0f;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    tabBarPattern->turnPageRate_ = 0.5f;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_NE(tabBarPattern, nullptr);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator002
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternUpdateIndicator002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto tabBarPaintProperty = tabBarNode->GetPaintProperty<TabBarPaintProperty>();
    ASSERT_NE(tabBarPaintProperty, nullptr);
    EXPECT_EQ(tabBarPaintProperty->GetFadingEdgeValue(), fadingEdge);

    /**
     * @tc.steps: steps2. UpdateIndicator
     * @tc.expected: steps2. Check the result of UpdateIndicator
     */

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->indicator_ = 0;
    auto tabBarStyle1 = TabBarStyle::NOSTYLE;
    tabBarPattern->tabBarStyles_.clear();
    tabBarPattern->tabBarStyles_.push_back(tabBarStyle1);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern->UpdateIndicator(0);
    tabBarPattern->isTouchingSwiper_ = false;
    tabBarPattern->UpdateIndicator(0);
    EXPECT_NE(tabBarPattern, nullptr);
}

/**
 * @tc.name: TabsModelPop001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelPop001, TestSize.Level1)
{
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);
    tabBarNode->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode->eventHub_);
    ASSERT_NE(tabBarNode->eventHub_->focusHub_, nullptr);
    tabsModel.Pop();
    EXPECT_NE(tabBarNode->eventHub_->focusHub_, nullptr);
    tabBarPattern->OnModifyDone();
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->swiperController_->removeTabBarEventCallback_();
    tabBarPattern->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern->swiperController_, nullptr);
}

/**
 * @tc.name: TabContentModelCreate2(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsTestNg, TabContentModelCreate002, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    auto deepRenderFunc = []() { AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    tabContentModel.Create(deepRenderFunc);

    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    auto parentnode =
        FrameNode::CreateFrameNode(V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId, AceType::MakeRefPtr<Pattern>(), true);
    TabsModelNG Mode1NG;
    Mode1NG.Create(BarPosition::END, 0, nullptr, nullptr);
    EXPECT_NE(ViewStackProcessor::GetInstance()->Finish(), nullptr);
    tabContentPattern->shallowBuilder_->deepRenderFunc_();
    ASSERT_NE(tabContentPattern, nullptr);
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode002
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsModelGetOrCreateTabsNode002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */

    TabsModelNG tabsModel;
    const std::string tag = "TabsID";
    int32_t nodeId = 1;

    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    auto tabsNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode, nullptr);
    auto tabsNode2 =
        TabsModelNG::GetOrCreateTabsNode("TabsID2", nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode2, nullptr);
}

/**
 * @tc.name: TabBarPatternOnRestoreInfo001
 * @tc.desc: Test the TabBarPatternOnRestoreInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnRestoreInfo001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create frameNode and get pattern.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarPattern->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabsLayoutProperty = tabBarPattern->GetLayoutProperty<TabsLayoutProperty>();

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern->UpdateIndicator(0);
    std::string ret = tabBarPattern->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    auto info = JsonUtil::ParseJsonString(restoreInfo_);
    auto jsonIsOn = info->GetValue("Index");
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    tabBarPattern->SetAnimationDuration(1);
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    tabBarPattern->swiperController_ = nullptr;
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode1, nullptr);
    columnNode1->MountToParent(tabBarNode);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    ASSERT_NE(columnNode2, nullptr);
    columnNode2->MountToParent(tabBarNode);
    pattern->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternInitTurnPageRateEvent002
 * @tc.desc: test InitTurnPageRateEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternInitTurnPageRateEvent002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    BuildTabBar(tabsNode, TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps2. InitTurnPageRateEvent
     * @tc.expected: steps2. Check the result of InitTurnPageRateEvent
     */

    tabBarPattern->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    AnimationCallbackInfo info;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->isTouchingSwiper_ = false;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->isTouchingSwiper_ = true;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);
    EXPECT_NE(tabBarPattern, nullptr);
    tabBarPattern->turnPageRate_ = 2.0f;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern->turnPageRate_ = 1.0f;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern->turnPageRate_ = 0.0f;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    tabBarPattern->turnPageRate_ = -1.0f;
    (*(tabBarPattern->animationEndEvent_))(testswipingIndex, info);
    EXPECT_NE(tabBarPattern, nullptr);
}

/**
 * @tc.name: TabBarPatternOnDirtyLayoutWrapperSwap002
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternOnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    TabsModelNG tabsModel;
    bool fadingEdge = true;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetFadingEdge(fadingEdge);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsFrameNode, nullptr);
    EXPECT_EQ(tabsFrameNode->GetTag(), V2::TABS_ETS_TAG);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    EXPECT_EQ(tabBarNode->GetTag(), V2::TAB_BAR_ETS_TAG);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto layoutAlgorithm = tabBarPattern->CreateLayoutAlgorithm();
    ASSERT_NE(layoutAlgorithm, nullptr);
    DirtySwapConfig config;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, tabBarNode->GetGeometryNode(), tabBarLayoutProperty);
    ASSERT_NE(layoutWrapper, nullptr);
    auto algorithmWrapper = AceType::MakeRefPtr<LayoutAlgorithmWrapper>(layoutAlgorithm, false, false);
    ASSERT_NE(algorithmWrapper, nullptr);
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper->GetLayoutProperty());
    ASSERT_NE(layoutProperty, nullptr);

    layoutWrapper->SetLayoutAlgorithm(algorithmWrapper);
    EXPECT_EQ(layoutWrapper->layoutAlgorithm_, algorithmWrapper);
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern->indicator_, 0);

    /**
     * @tc.steps: step2. creat different conditions and invoke OnDirtyLayoutWrapperSwap.
     * @tc.expected: step2. expect The function is run ok.
     */
    config.skipMeasure = false;
    tabBarPattern->isTouchingSwiper_ = true;
    layoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, config);
    EXPECT_EQ(tabBarPattern->isTouchingSwiper_, true);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect003
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternSetEdgeEffect003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create TabBarPattern
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
    EXPECT_NE(tabBarPattern, nullptr);
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode and ideaSize.
     */

    LayoutConstraintF childConstraint = LayoutConstraintF();
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);
    tabBarProperty->UpdateTabBarMode(TabBarMode::FIXED);
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarProperty, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarProperty->GetTabBarMode().value(), TabBarMode::FIXED);
    tabBarProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarProperty, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarProperty->GetTabBarMode().value(), TabBarMode::SCROLLABLE);
}

/**
 * @tc.name: TabBarBlurStyle001
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarBlurStyle001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabsModel.
     */

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 0, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    auto pipeline = PipelineContext::GetCurrentContext();
    ASSERT_NE(pipeline, nullptr);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);

    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    auto tabBarRenderContext = tabBarNode->GetRenderContext();
    ASSERT_NE(tabBarRenderContext, nullptr);
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
        tabBarRenderContext->UpdateBackBlurStyle(styleOption);
    }
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
 * @tc.name: TabBarLayoutAlgorithmCheckMarqueeForScrollable001
 * @tc.desc: Test the CheckMarqueeForScrollable function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmCheckMarqueeForScrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    ASSERT_NE(tabbarLayoutAlgorithm, nullptr);
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode, geometryNode, tabBarNode->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto layoutProperty = AceType::DynamicCast<TabBarLayoutProperty>(layoutWrapper.GetLayoutProperty());
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. Create different input parameters.
     */
    layoutProperty->UpdateTabBarMode(TabBarMode::FIXED);
    int32_t childCount = 0;
    BarGridColumnOptions option;
    option.lg = 2;
    instance.SetBarGridAlign(option);

    /**
     * @tc.steps: steps3. CheckMarqueeForScrollable.
     * @tc.expected: steps3. Check the results of CheckMarqueeForScrollable under different conditions.
     */
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
    childCount = 1;
    tabbarLayoutAlgorithm->CheckMarqueeForScrollable(&layoutWrapper, childCount);
    EXPECT_NE(tabbarLayoutAlgorithm, nullptr);
}

/**
* @tc.name: InitScrollable001
* @tc.desc: test AdjustFocusPosition
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, InitScrollable001, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Create tabsModel
    */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    auto axis_test = Axis::HORIZONTAL;
    tabBarPattern->scrollableEvent_ = AceType::MakeRefPtr<ScrollableEvent>(axis_test);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);

    auto pattern = AceType::DynamicCast<TabBarPattern>(tabBarPattern);
    /**
    * @tc.steps: step2. Clear tabitemOffsets_ InitScrollable is called after data in
    * @tc.expected: TabItem Offsets_ Value is empty
    */

    pattern->tabItemOffsets_.clear();
    tabBarPattern->InitScrollable(gestureHub);
    tabBarPattern->axis_ = Axis::VERTICAL;
    ASSERT_TRUE(pattern->tabItemOffsets_.empty());
}

/**
* @tc.name: AdjustFocusPosition005
* @tc.desc: test AdjustFocusPosition
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, AdjustFocusPosition005, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Create tabsModel
    */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarPattern->focusIndicator_ = -10;
    tabBarPattern->AdjustFocusPosition();
    /**
    * @tc.steps: steps2. GetScopeFocusAlgorithm
    * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
    */
    tabBarPattern->AdjustFocusPosition();
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);
    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->focusIndicator_ = -2;
    tabBarPattern->AdjustFocusPosition();
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
* @tc.name: DumpAdvanceInfo005
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, DumpAdvanceInfo005, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Create tabsModel
    */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    /**
    * @tc.steps: steps1. Set axis_ Axis: HORIZONTAL
    * @tc.expected: Calling DumpAdvanceInfo() expects HORIZONTAL
    */
    tabBarPattern->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern->axis_, Axis::HORIZONTAL);
    /**
    * @tc.steps: steps1. Set axis_ Axis: VERTICAL
    * @tc.expected: Calling DumpAdvanceInfo() expects VERTICAL
        */
    tabBarPattern->axis_ = Axis::VERTICAL;
    tabBarPattern->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern->axis_, Axis::VERTICAL);
    /**
    * @tc.steps: steps1. Set axis_ Axis: FREE
    * @tc.expected: Calling DumpAdvanceInfo() expects FREE
    */
    tabBarPattern->axis_ = Axis::FREE;
    tabBarPattern->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern->axis_, Axis::FREE);
    /**
    * @tc.steps: steps1. Set axis_ Axis: NONE
    * @tc.expected: Calling DumpAdvanceInfo() expects NONE
    */
    tabBarPattern->axis_ = Axis::NONE;
    tabBarPattern->DumpAdvanceInfo();
    ASSERT_EQ(tabBarPattern->axis_, Axis::NONE);
}

/**
* @tc.name: Layout001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, Layout001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Create TabContentNode.
    */
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
    divider.isNull = false;

    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(100);
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabsModel.SetDivider(divider);

    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);

    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();
    ASSERT_NE(tabsLayoutAlgorithm, nullptr);

    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstrain;
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstrain);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();;
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    ASSERT_NE(&layoutWrapper, nullptr);

    /**
    * @tc.steps: step1. Calling the Layout interface.
    * @tc.expected: TestTrovoid is not equal to nullptr.
    */
    auto wrapper = static_cast<LayoutWrapper*>(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(wrapper);
    ASSERT_NE(wrapper, nullptr);
}

/**
* @tc.name: ProvideRestoreInfo001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, ProvideRestoreInfo001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. create frameNode and get pattern.
    */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    /**
    * @tc.steps: step1. Calling the ProvideRestoreInfo interface.
    * @tc.expected: TestTrovoid is not equal to nullpyt.
    */
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    string testTrovid = tabBarPattern->ProvideRestoreInfo();
    ASSERT_TRUE(!testTrovid.empty());
}

/**
* @tc.name: Pop001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, Pop001, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Construct TabContentModelNG object
    */
    TabContentModelNG tabContentModel;
    IndicatorStyle indicator;

    /**
    * @tc.steps: step1. Construct TabContentModelNG object
    * @tc.expected: Calling the pop interface, the tabContentModel object is not empty
    */
    tabContentModel.Create();
    tabContentModel.SetIndicator(indicator);
    tabContentModel.Pop();
    EXPECT_NE(&tabContentModel, nullptr);
}

/**
* @tc.name: SetTabBarStyle001
* @tc.desc: test AddTabBarItem
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, SetTabBarStyle001, TestSize.Level1)
{
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

    /**
    * @tc.steps: step1. step1.SetTabBarStyle Set TabBarStyle to TabBarStyle: SUBTABBATSTYLE
    * @tc.steps: sCall the GetTabBarStyle interface under the TabContentModelNG
    * @tc.expected: Equal to TabBarStyle: SUBTABBATSTYLE.
    */
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
* @tc.name: SetEdgeEffect002
* @tc.desc: test SetEdgeEffect
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, SetEdgeEffect002, TestSize.Level1)
{
    /**
    * @tc.steps: steps1. Create TabBarPattern
    */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    tabsModel.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    tabBarNode->GetLayoutProperty<TabBarLayoutProperty>()->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
    * @tc.steps: step1. Test function SetEdgeEffect.
    * @tc.expected: SetEdgeEffect calling interface.
    */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    ASSERT_NE(gestureHub, nullptr);
    tabBarPattern->SetEdgeEffect(gestureHub);
    EXPECT_NE(tabBarPattern, nullptr);
    /**
    * @tc.steps: step1. Set scrollEffect_ Value is empty.
    * @tc.expected: SetEdgeEffect calling interface
    */
    tabBarPattern->scrollEffect_ = nullptr;
    tabBarPattern->SetEdgeEffect(gestureHub);
}

/**
* @tc.name: Create003
* @tc.desc: test SetEdgeEffect
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, Create003, TestSize.Level1)
{
    /**
    * @tc.steps: step1. Construct TabContentModelNG object
    */
    auto controller = AceType::MakeRefPtr<SwiperController>();
    TabsModelNG Mode1NG;
    int32_t testIndex = 0;

    /**
    * @tc.steps: step2. Test function Create.
    * @tc.expected: TestIndex greater than or equal to 0
    */
    Mode1NG.Create(BarPosition::END, testIndex, nullptr, controller);
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();

    auto tabsNode =
        TabsModelNG::GetOrCreateTabsNode(V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });

    auto swiperId = tabsNode->GetSwiperId();
    auto swiperNode = FrameNode::GetOrCreateFrameNode(
        V2::SWIPER_ETS_TAG, swiperId, []() { return AceType::MakeRefPtr<SwiperPattern>(); });

    auto swiperPaintProperty = swiperNode->GetPaintProperty<SwiperPaintProperty>();
    swiperPaintProperty->UpdateEdgeEffect(EdgeEffect::SPRING);

    ViewStackProcessor::GetInstance()->Push(tabsNode);
    ViewStackProcessor::GetInstance()->Push(tabsNode);
    auto tabsFrameNode = AceType::DynamicCast<FrameNode>(tabsNode);

    auto tabsLayoutProperty = tabsFrameNode->GetLayoutProperty<TabsLayoutProperty>();
    EXPECT_TRUE(testIndex >= 0);
}

/**
 * @tc.name: TabsPatternParseJsonString002
 * @tc.desc: test ParseJsonString
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternOnRestoreInfo002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    /**
     * @tc.steps: step1. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    tabsPattern->OnRestoreInfo("");
    auto info = JsonUtil::ParseJsonString("");
    EXPECT_FALSE(info->IsObject());
}

/**
* @tc.name: TabsModelMeasure007
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabsModelMeasure007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);

    /**
     * @tc.steps: step1. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step1. related function is called.
     */
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto pattern = tabsFrameNode->GetPattern<TabsPattern>();
    auto tabsLayoutAlgorithm = pattern->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabsFrameNode, geometryNode, tabsFrameNode->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode, geometryNode1, swiperNode->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode, geometryNode3, tabBarNode->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step1. Set currentChildCount_ Value is 0
     * @tc.expected: step1. After calling the Measure interface, layoutWrapper GetTotalChildCount() -2 <=0
     */
    layoutWrapper.currentChildCount_ = 0;
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(layoutWrapper.GetTotalChildCount() - 2 <= 0);
}

/**
* @tc.name: TabBarPatternProvideRestoreInfo003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabBarPatternProvideRestoreInfo003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step1.1. Constructing TabBarPattern class pointers
     * @tc.expected:tabBarPattern->ProvideRestoreInfo() not null.
     */
    EXPECT_TRUE(tabBarPattern->ProvideRestoreInfo() != "");
}

/**
* @tc.name: TabBarPatternBeforeCreateLayoutWrapper003
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabBarPatternBeforeCreateLayoutWrapper003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    tabBarPattern->BeforeCreateLayoutWrapper();
    /**
     * @tc.steps: step1.1. Constructing TabBarPattern class pointers
     * @tc.expected:tabBarPattern not null.
     */
    ASSERT_NE(tabBarPattern, nullptr);
}

/**
* @tc.name: TabsPatternSetOnAnimationEnd002
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabsPatternSetOnAnimationEnd002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetTabs());
    ASSERT_NE(swiperNode, nullptr);

    auto eventHub = swiperNode->GetEventHub<SwiperEventHub>();
    ASSERT_NE(eventHub, nullptr);
    auto pattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(pattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step1. Test SetOnAnimationStart function.
     * @tc.expected:eventHub->animationStartEvent_ not null.
     */
    auto onAnimationStart = [](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {};
    tabsModel.SetOnAnimationStart(std::move(onAnimationStart));

    /**
     * @tc.steps: step2.2. Test SetOnAnimationEnd function.
     * @tc.expected:pattern->animationEndEvent_ not null.
     */
    tabBarPattern->InitTurnPageRateEvent();
    int32_t testswipingIndex = 1;
    float testturnPageRate = 1.0f;
    tabBarPattern->swiperController_->turnPageRateCallback_(testswipingIndex, testturnPageRate);

    /**
     * @tc.steps: step1. Convert lvalue to rvalue reference using std:: move()
     */
    auto onAnimationEnd = [](int32_t index, const AnimationCallbackInfo& info) {};
    tabsModel.SetOnAnimationEnd(std::move(onAnimationEnd));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);

    pattern->SetAnimationEndEvent(std::move(*tabBarPattern->animationEndEvent_));
    EXPECT_NE(pattern->animationEndEvent_, nullptr);
}

/**
* @tc.name: TabBarPatternSetSpecificSupportAction002
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsTestNg, TabBarPatternSetSpecificSupportAction002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    TabsItemDivider divider;
    instance.SetDivider(divider);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    auto accessibilityProperty = tabBarNode->GetAccessibilityProperty<TabBarAccessibilityProperty>();
    ASSERT_NE(accessibilityProperty, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step2. invoke SetSpecificSupportAction.
     * @tc.expected: Related function is called.
     */
    TabContentModelNG tabContentModel1;
    tabContentModel1.Create();

    auto tabContentFrameNode1 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode1, nullptr);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();

    auto tabContentFrameNode2 =
        AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    ASSERT_NE(tabContentFrameNode2, nullptr);

    accessibilityProperty->SetSpecificSupportAction();
    EXPECT_FALSE(accessibilityProperty->IsScrollable());
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);

    tabContentFrameNode1->MountToParent(swiperNode);
    tabContentFrameNode2->MountToParent(swiperNode);
    auto frameNode = accessibilityProperty->host_.Upgrade();
    ASSERT_NE(frameNode, nullptr);

    accessibilityProperty->SetSpecificSupportAction();
    EXPECT_FALSE(tabBarPattern->IsAtBottom());
}

/**
 * @tc.name: TabsPatternGetAxis003
 * @tc.desc: test GetAxis
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetAxis003, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel.
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);

    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    tabsLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::HORIZONTAL);

    tabsLayoutProperty->UpdateAxis(Axis::VERTICAL);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::VERTICAL);

    tabsLayoutProperty->UpdateAxis(Axis::FREE);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::FREE);

    tabsLayoutProperty->UpdateAxis(Axis::NONE);
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_EQ(tabsLayoutProperty->GetAxis().value(), Axis::NONE);
}

/**
 * @tc.name: TabsPatternGetScopeFocusAlgorithm004
 * @tc.desc: test GetScopeFocusAlgorithm
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabsPatternGetScopeFocusAlgorithm004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    auto tabsLayoutProperty = tabsNode->GetLayoutProperty<TabsLayoutProperty>();
    ASSERT_NE(tabsLayoutProperty, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);

    tabsLayoutProperty->Reset();
    tabsPattern->GetScopeFocusAlgorithm();
    EXPECT_FALSE(tabsLayoutProperty->GetAxis().has_value());
}

/**
 * @tc.name: TabBarModifierSetSelectedMode002
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarModifierSetSelectedMode002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Select mode as BOARD
     */
    SelectedMode selectedMode = SelectedMode::BOARD;
    auto tabBarModifier = AceType::MakeRefPtr<TabBarModifier>();
    tabBarModifier->SetSelectedMode(selectedMode);
    ASSERT_NE(tabBarModifier->hasIndicator_, nullptr);
    tabBarModifier->hasIndicator_ = nullptr;

    /**
     * @tc.steps: steps2.Calling the SetSelectedMode interface to pass in SelectedMode:: BOARD
     * @tc.expected: steps2. TabBarModifier -> has Indicator_ nullptr
     */
    tabBarModifier->SetSelectedMode(selectedMode);
    EXPECT_EQ(tabBarModifier->hasIndicator_, nullptr);
}

/**
 * @tc.name: TabBarPatternAdjustFocusPosition003
 * @tc.desc: test AdjustFocusPosition
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarPatternAdjustFocusPosition004, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::END, 0, nullptr, nullptr);
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);

    /**
     * @tc.steps: steps2. GetScopeFocusAlgorithm
     * @tc.expected: steps2. Check the result of GetScopeFocusAlgorithm
     */
    tabBarPattern->AdjustFocusPosition();
    tabBarLayoutProperty->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    tabBarPattern->axis_ = Axis::HORIZONTAL;
    tabBarPattern->tabItemOffsets_.clear();
    OffsetF c1(-1.0f, -1.0f);

    tabBarPattern->tabItemOffsets_.emplace_back(c1);
    tabBarPattern->focusIndicator_ = 0;
    tabBarPattern->AdjustFocusPosition();
    tabBarPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);

    /**
     * @tc.steps: steps3. Set TabBarStyle: NOSTYLE
     * @tc.expected: Expected value is TabBarStyle: NOSTYLE
     */
    tabBarPattern->SetTabBarStyle(TabBarStyle::NOSTYLE);
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::NOSTYLE);

    tabBarPattern->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    EXPECT_EQ(tabBarPattern->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarLayoutAlgorithmUpdateChildConstraint002
 * @tc.desc: test UpdateChildConstraint
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, TabBarLayoutAlgorithmUpdateChildConstraint003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabBarNode and ideaSize.
     */
    LayoutConstraintF childConstraint = LayoutConstraintF();
    TabsModelNG instance;
    instance.Create(BarPosition::START, 1, nullptr, nullptr);
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsFrameNode, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);
    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern->CreateLayoutAlgorithm());
    ASSERT_NE(tabBarLayoutAlgorithm, nullptr);
    auto tabBarProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarProperty, nullptr);
    tabBarProperty->UpdateTabBarMode(TabBarMode::FIXED);

    /**
     * @tc.steps: step2. Set width and height
     */
    float width = 1.0;
    float height = 2.0;
    auto ideaSize = SizeF(width, height);
    int32_t childCount = 1;
    auto axis = Axis::FREE;
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;

    /**
     * @tc.steps: step2. call UpdateChildConstraint function.
     * @tc.expected: The function is run ok.
     */
    tabBarProperty->UpdateTabBarMode(TabBarMode::FIXED_START);
    tabBarLayoutAlgorithm->UpdateChildConstraint(childConstraint, tabBarProperty, ideaSize, childCount, axis);
    EXPECT_EQ(tabBarProperty->GetTabBarMode().value(), TabBarMode::FIXED_START);
}

/**
 * @tc.name: CustomAnimationTest001
 * @tc.desc: test custom animation disable swipe
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, CustomAnimationTest001, TestSize.Level1)
{
    const std::string text_test = "text_test";

    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, INDEX_ONE, nullptr, nullptr);
    tabsModel.SetIsCustomAnimation(true);
    tabsModel.SetOnCustomAnimation([](int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;
        transitionInfo.transition = [](const RefPtr<TabContentTransitionProxy>& proxy) {};
        return transitionInfo;
    });
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabsNode, nullptr);
    EXPECT_EQ(tabsNode->GetTag(), V2::TABS_ETS_TAG);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    EXPECT_EQ(swiperNode->GetTag(), V2::SWIPER_ETS_TAG);

    TabContentModelNG tabContentModel;
    SelectedMode selectedMode = SelectedMode::INDICATOR;
    tabContentModel.Create();
    tabContentModel.SetSelectedMode(selectedMode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);
    EXPECT_EQ(tabContentFrameNode->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);
    tabContentFrameNode->GetTabBarItemId();
    tabContentFrameNode->MountToParent(swiperNode);
    tabContentPattern->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    tabContentModel2.SetSelectedMode(selectedMode);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode2, nullptr);
    EXPECT_EQ(tabContentFrameNode2->GetTag(), V2::TAB_CONTENT_ITEM_ETS_TAG);
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern2, nullptr);
    EXPECT_EQ(tabContentPattern2->GetSelectedMode(), SelectedMode::INDICATOR);
    tabContentFrameNode2->GetTabBarItemId();
    tabContentFrameNode2->MountToParent(swiperNode);
    tabContentPattern2->SetTabBar(text_test, "", nullptr);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel2.AddTabBarItem(tabContentFrameNode2, DEFAULT_NODE_SLOT, true);

    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);

    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    auto tabBarLayoutProperty = tabBarNode->GetLayoutProperty<TabBarLayoutProperty>();
    ASSERT_NE(tabBarLayoutProperty, nullptr);
    tabBarLayoutProperty->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern->tabItemOffsets_ = { { 0.0f, 0.0f }, { 10.0f, 10.0f } };

    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    auto swiperLayoutProperty = swiperNode->GetLayoutProperty<SwiperLayoutProperty>();
    ASSERT_NE(swiperLayoutProperty, nullptr);
    swiperLayoutProperty->UpdateIndex(INDEX_ONE);

    GestureEvent info;
    Offset offset(1, 1);
    info.SetLocalLocation(offset);
    tabBarLayoutProperty->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern->HandleClick(info);

    EXPECT_EQ(swiperPattern->IsDisableSwipe(), true);
    EXPECT_EQ(swiperPattern->customAnimationToIndex_.has_value(), true);

    swiperPattern->OnCustomAnimationFinish(INDEX_ONE, INDEX_ZERO, false);
    EXPECT_EQ(swiperPattern->customAnimationToIndex_.has_value(), false);

    swiperPattern->SwipeTo(INDEX_ONE);
    EXPECT_EQ(swiperPattern->customAnimationToIndex_.has_value(), true);
}

/**
 * @tc.name: CustomAnimationTest002
 * @tc.desc: test custom animation set undefined
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, CustomAnimationTest002, TestSize.Level1)
{
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    model.SetIsCustomAnimation(false);

    for (int32_t index = 0; index < 3; index++) {
        TabContentModelNG tabContentModel;
        tabContentModel.Create();
        ViewStackProcessor::GetInstance()->Pop();
    }

    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto tabsFrameNode = AceType::DynamicCast<TabsNode>(element);

    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsFrameNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);

    EXPECT_EQ(swiperPattern->IsDisableSwipe(), false);
}

/**
 * @tc.name: SetOnContentWillChangeTest001
 * @tc.desc: test onContentWillChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsTestNg, SetOnContentWillChangeTest001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create tabsModel
     */
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);

    /**
     * @tc.steps: steps2. Get frameNode and pattern.
     * @tc.expected: tabsNode, tabsPattern, swiperNode, swiperPattern, tabBarNode, tabBarPattern not null.
     */
    auto tabsNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    ASSERT_NE(tabsNode, nullptr);
    auto tabsPattern = tabsNode->GetPattern<TabsPattern>();
    ASSERT_NE(tabsPattern, nullptr);
    auto swiperNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_SWIPER_INDEX));
    ASSERT_NE(swiperNode, nullptr);
    auto swiperPattern = swiperNode->GetPattern<SwiperPattern>();
    ASSERT_NE(swiperPattern, nullptr);
    auto tabBarNode = AceType::DynamicCast<FrameNode>(tabsNode->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode, nullptr);
    auto tabBarPattern = tabBarNode->GetPattern<TabBarPattern>();
    ASSERT_NE(tabBarPattern, nullptr);

    /**
     * @tc.steps: step3. Set onContentWillChange callback.
     * @tc.expected: tabsPattern->GetInterceptStatus() is true.
     */
    auto callback = [](int32_t currentIndex, int32_t comingIndex) -> bool { return true; };
    tabsModel.SetOnContentWillChange(std::move(callback));
    EXPECT_EQ(tabsPattern->GetInterceptStatus(), true);

    /**
     * @tc.steps: step4. Execute intercept callback.
     * @tc.expected:
     *     tabsPattern->OnContentWillChange(CURRENT_INDEX, BEGIN_INDEX) return true.
     *     swiperPattern->ContentWillChange(BEGIN_INDEX) return true.
     *     swiperPattern->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX) return true.
     *     tabBarPattern->ContentWillChange(BEGIN_INDEX) return true.
     *     tabBarPattern->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX) return true.
     */
    auto ret = tabsPattern->OnContentWillChange(CURRENT_INDEX, BEGIN_INDEX);
    EXPECT_EQ(ret.value(), true);
    EXPECT_EQ(swiperPattern->ContentWillChange(BEGIN_INDEX), true);
    EXPECT_EQ(swiperPattern->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX), true);
    EXPECT_EQ(tabBarPattern->ContentWillChange(BEGIN_INDEX), true);
    EXPECT_EQ(tabBarPattern->ContentWillChange(CURRENT_INDEX, BEGIN_INDEX), true);
}
} // namespace OHOS::Ace::NG
