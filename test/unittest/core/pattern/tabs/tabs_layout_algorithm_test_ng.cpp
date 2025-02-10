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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {
class TabsLayoutAlgorithmTest : public TabsTestNg {};

/**
 * @tc.name: TabsSize001
 * @tc.desc: Test tabs size
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsSize001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);

    // Tabs
    EXPECT_EQ(frameNode_->GetTag(), V2::TABS_ETS_TAG);
    EXPECT_TRUE(IsEqual(frameNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, TABS_HEIGHT)));

    // TabBar
    EXPECT_EQ(tabBarNode_->GetTag(), V2::TAB_BAR_ETS_TAG);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, TAB_BAR_SIZE)));
    EXPECT_EQ(tabBarNode_->GetTotalChildCount(), TABCONTENT_NUMBER + MASK_COUNT);
    float barItemWidth = TABS_WIDTH / TABCONTENT_NUMBER;
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 0), RectF(0, 0, barItemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 1), RectF(barItemWidth * 1, 0, barItemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 2), RectF(barItemWidth * 2, 0, barItemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 3), RectF(barItemWidth * 3, 0, barItemWidth, TAB_BAR_SIZE)));
    // TabBar Item
    auto barItem = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(barItem->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(barItem->GetTotalChildCount(), 2);
    auto imageNode = GetChildFrameNode(barItem, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto textNode = GetChildFrameNode(barItem, 1);
    EXPECT_EQ(textNode->GetTag(), V2::TEXT_ETS_TAG);

    // Divider
    EXPECT_EQ(dividerNode_->GetTag(), V2::DIVIDER_ETS_TAG);
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameRect(), RectF(0, TAB_BAR_SIZE, TABS_WIDTH, 0)));

    // Swiper
    EXPECT_EQ(swiperNode_->GetTag(), V2::SWIPER_ETS_TAG);
    EXPECT_TRUE(IsEqual(swiperNode_->GetGeometryNode()->GetFrameRect(),
        RectF(0, TAB_BAR_SIZE, TABS_WIDTH, TABS_HEIGHT - TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(swiperNode_, 0), RectF(0, 0, TABS_WIDTH, TABS_HEIGHT - TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(swiperNode_, 1), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(swiperNode_, 2), RectF()));
    EXPECT_TRUE(IsEqual(GetChildRect(swiperNode_, 3), RectF()));
}

/**
 * @tc.name: BarPosition001
 * @tc.desc: Test Tabs BarPosition and vertical, affect the tabBar position
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, BarPosition001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set BarPosition::START and Vertical:false
     * @tc.expected: The tabBar would at the top of tabs
     */
    BarPosition barPosition = BarPosition::START;
    TabsModelNG model = CreateTabs(barPosition);
    CreateTabContents();
    CreateTabsDone(model);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, TABS_WIDTH, TAB_BAR_SIZE)));

    /**
     * @tc.steps: step2. Set BarPosition::END and Vertical:false
     * @tc.expected: The tabBar would at the bottom of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    FlushUITasks();
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::HORIZONTAL);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(),
        RectF(0, TABS_HEIGHT - TAB_BAR_SIZE, TABS_WIDTH, TAB_BAR_SIZE)));

    /**
     * @tc.steps: step3. Set BarPosition::START and Vertical:true
     * @tc.expected: The tabBar would at the left of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::START);
    model.SetIsVertical(AceType::RawPtr(frameNode_), true);
    FlushUITasks();
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(), RectF(0, 0, TAB_BAR_SIZE, TABS_HEIGHT)));

    /**
     * @tc.steps: step4. Set BarPosition::END and Vertical:true
     * @tc.expected: The tabBar would at the right of tabs
     */
    model.SetTabBarPosition(AceType::RawPtr(frameNode_), BarPosition::END);
    FlushUITasks();
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameRect(),
        RectF(TABS_WIDTH - TAB_BAR_SIZE, 0, TAB_BAR_SIZE, TABS_HEIGHT)));
}

/**
 * @tc.name: InitIndex001
 * @tc.desc: Test init index, affect the swiper show item
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, InitIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Set init index is 0
     * @tc.expected: The swiper show the first item
     */
    TabsModelNG model = CreateTabs(BarPosition::START, 0);
    CreateTabContents();
    CreateTabsDone(model);
    EXPECT_TRUE(CurrentIndex(0));

    /**
     * @tc.steps: step2. Set init index is 1
     * @tc.expected: The swiper show the second item
     */
    layoutProperty_->UpdateIndexSetByUser(1);
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step3. Set init index is -1
     * @tc.expected: The swiper show item is not change
     */
    layoutProperty_->UpdateIndexSetByUser(-1);
    FlushUITasks();
    EXPECT_TRUE(CurrentIndex(1));
}

/**
 * @tc.name: TabBarMode_Fixed001
 * @tc.desc: The tabBar items always average split barWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabBarMode_Fixed001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set total tabBar items width < TABS_WIDTH
     * @tc.expected: The tabBar items always average split barWidth
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder();
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarModeValue(TabBarMode::FIXED), TabBarMode::FIXED);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().Width(), TABS_WIDTH);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 1), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 2), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 3), TABS_WIDTH / TABCONTENT_NUMBER);

    /**
     * @tc.steps: steps2. Set total tabBar items width > TABS_WIDTH
     * @tc.expected: The tabBar items always average split barWidth
     */
    auto barItem = GetChildFrameNode(tabBarNode_, 2);
    ViewAbstract::SetWidth(AceType::RawPtr(barItem), CalcLength(10000.0f));
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 1), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 2), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 3), TABS_WIDTH / TABCONTENT_NUMBER);
}

/**
 * @tc.name: TabBarMode_Fixed002
 * @tc.desc: The tabBar items always average split barHeight
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabBarMode_Fixed002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set total tabBar items height < TABS_HEIGHT
     * @tc.expected: The tabBar items always average split barHeight
     */
    TabsModelNG model = CreateTabs();
    model.SetIsVertical(true);
    CreateTabContentsWithBuilder();
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarModeValue(TabBarMode::FIXED), TabBarMode::FIXED);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().Height(), TABS_HEIGHT);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 0), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 1), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 2), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 3), TABS_HEIGHT / TABCONTENT_NUMBER);

    /**
     * @tc.steps: steps2. Set total tabBar items height > TABS_HEIGHT
     * @tc.expected: The tabBar items always average split barHeight
     */
    auto barItem = GetChildFrameNode(tabBarNode_, 2);
    ViewAbstract::SetHeight(AceType::RawPtr(barItem), CalcLength(10000.0f));
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(tabBarNode_, 0), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 1), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 2), TABS_HEIGHT / TABCONTENT_NUMBER);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 3), TABS_HEIGHT / TABCONTENT_NUMBER);
}

/**
 * @tc.name: TabBarMode_Scrollable001
 * @tc.desc: TabBar items width is its actual width
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabBarMode_Scrollable001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set total tabBar items width < TABS_WIDTH
     * @tc.expected: TabBar items width is its actual width
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContentsWithBuilder();
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarModeValue(TabBarMode::FIXED), TabBarMode::SCROLLABLE);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().Width(), TABS_WIDTH);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 1), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 2), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 3), BAR_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Set total tabBar items width > TABS_WIDTH
     * @tc.expected: TabBar items width is its actual width
     */
    auto barItem = GetChildFrameNode(tabBarNode_, 2);
    ViewAbstract::SetWidth(AceType::RawPtr(barItem), CalcLength(10000.0f));
    FlushUITasks();
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 1), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 2), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildWidth(tabBarNode_, 3), BAR_ITEM_SIZE);
}

/**
 * @tc.name: TabBarMode_Scrollable002
 * @tc.desc: TabBar items height is its actual height
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabBarMode_Scrollable002, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Set total tabBar items height < TABS_HEIGHT
     * @tc.expected: TabBar items height is its actual height
     */
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(true);
    CreateTabContentsWithBuilder();
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->axis_, Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarModeValue(TabBarMode::FIXED), TabBarMode::SCROLLABLE);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().Height(), TABS_HEIGHT);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 0), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 1), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 2), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 3), BAR_ITEM_SIZE);

    /**
     * @tc.steps: steps2. Set total tabBar items height > TABS_HEIGHT
     * @tc.expected: TabBar items height is its actual height
     */
    auto barItem = GetChildFrameNode(tabBarNode_, 2);
    ViewAbstract::SetHeight(AceType::RawPtr(barItem), CalcLength(10000.0f));
    FlushUITasks();
    EXPECT_EQ(GetChildHeight(tabBarNode_, 0), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 1), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 2), BAR_ITEM_SIZE);
    EXPECT_EQ(GetChildHeight(tabBarNode_, 3), BAR_ITEM_SIZE);
}

/**
 * @tc.name: Divider001
 * @tc.desc: Test divider
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, Divider001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Not set divider
     * @tc.expected: Not show divider
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, 0)));

    /**
     * @tc.steps: steps2. Set Divider
     * @tc.expected: Has divider
     */
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(4);
    divider.startMargin = Dimension(5);
    divider.endMargin = Dimension(5);
    divider.color = Color::BLUE;
    divider.isNull = false;
    model.SetDivider(AceType::RawPtr(frameNode_), divider);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(710.0f, 4.0f)));

    /**
     * @tc.steps: steps3. Set Divider and isNull is true
     * @tc.expected: Create a new divider replace
     */
    divider.isNull = true;
    model.SetDivider(AceType::RawPtr(frameNode_), divider);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(710.0f, 1.0f)));
}

/**
 * @tc.name: BarGridAlign001
 * @tc.desc: Test Tabs BarGridAlign
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, BarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Default
     * @tc.expected: TabBarItem width are full of tabsWidth
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents();
    CreateTabsDone(model);
    float itemWidth = TABS_WIDTH / TABCONTENT_NUMBER;
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 0), RectF(0, 0, itemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 1), RectF(itemWidth, 0, itemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 2), RectF(itemWidth * 2, 0, itemWidth, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 3), RectF(itemWidth * 3, 0, itemWidth, TAB_BAR_SIZE)));

    /**
     * @tc.steps: steps2. Set BarGridColumnOptions, tabsWidth is md
     * @tc.expected: TabBarItem position changed
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(800.0f));
    BarGridColumnOptions options;
    options.sm = 4;
    options.md = 3;
    options.lg = 4;
    options.gutter = Dimension(5);
    options.margin = Dimension(10);
    model.SetBarGridAlign(AceType::RawPtr(frameNode_), options);
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 0), RectF(0, 0, 200.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 1), RectF(200.0f, 0, 200.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 2), RectF(400.0f, 0, 200.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 3), RectF(600.0f, 0, 200.0f, TAB_BAR_SIZE)));

    /**
     * @tc.steps: steps3. TabsWidth is sm
     * @tc.expected: TabBarItem position changed
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(400.0f));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 0), RectF(10.0f, 0, 95.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 1), RectF(105.0f, 0, 95.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 2), RectF(200.0f, 0, 95.0f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 3), RectF(295.0f, 0, 95.0f, TAB_BAR_SIZE)));

    /**
     * @tc.steps: steps4. TabsWidth is lg
     * @tc.expected: TabBarItem position changed
     */
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(900.0f));
    FlushUITasks();
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 0), RectF(305.0f, 0, 72.5f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 1), RectF(377.5f, 0, 72.5f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 2), RectF(450.0f, 0, 72.5f, TAB_BAR_SIZE)));
    EXPECT_TRUE(IsEqual(GetChildRect(tabBarNode_, 3), RectF(522.5f, 0, 72.5f, TAB_BAR_SIZE)));
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure001
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabsFrameSize is layoutSize.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure002
 * @tc.desc: test Measure when virtical is true and width is auto
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetWidthAuto(true);
    model.SetHeightAuto(false);
    model.SetIsVertical(true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABBAR_WIDTH + DIVIDER_STROKE_WIDTH + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure003
 * @tc.desc: test Measure when virtical is false and height is auto
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetWidthAuto(false);
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABBAR_HEIGHT + DIVIDER_STROKE_WIDTH + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure004
 * @tc.desc: test if width is adaptived when barOverlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    model.SetBarOverlap(true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), DIVIDER_STROKE_WIDTH + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure005
 * @tc.desc: test if height is adaptived when barOverlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    model.SetBarOverlap(true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), DIVIDER_STROKE_WIDTH + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure006
 * @tc.desc: test if width is adaptived when tabs has padding
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING + TABBAR_WIDTH + SWIPER_WIDTH + TABS_PADDING);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure007
 * @tc.desc: test if height is adaptived when tabs has padding
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING + TABBAR_HEIGHT + TABS_PADDING + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure008
 * @tc.desc: test if width is adaptived when tabs has border
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING + TABBAR_WIDTH + SWIPER_WIDTH + TABS_PADDING);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure009
 * @tc.desc: test if height is adaptived when tabs has border
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING + TABBAR_HEIGHT + TABS_PADDING + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure010
 * @tc.desc: test Measure when tabBar is default and width is auto
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(tabBarNode_->GetGeometryNode()->GetMarginFrameSize().Width());
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TAB_BAR_SIZE + DIVIDER_STROKE_WIDTH + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure011
 * @tc.desc: test Measure when tabBar is default and height is auto
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    divider.strokeWidth = 10.0_vp;
    model.SetDivider(divider);
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);

    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(tabBarNode_->GetGeometryNode()->GetMarginFrameSize().Height());
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TAB_BAR_SIZE + DIVIDER_STROKE_WIDTH + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure012
 * @tc.desc: test if width is adaptived when tabs has padding and border
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING * 4 + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure013
 * @tc.desc: test if height is adaptived when tabs has padding and border
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING * 4 + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure014
 * @tc.desc: test if width is adaptived when tabs has padding and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING * 2 + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure015
 * @tc.desc: test if height is adaptived when tabs has padding and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING * 2 + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure016
 * @tc.desc: test if width is adaptived when tabs has border and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameWidth(TABBAR_WIDTH);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING * 2 + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure017
 * @tc.desc: test if height is adaptived when tabs has border and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    dividerLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    dividerLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    geometryNode3->SetFrameHeight(TABBAR_HEIGHT);
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING * 2 + SWIPER_HEIGHT);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure018
 * @tc.desc: test if width is adaptived when tabs has padding and border, and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetIsVertical(true);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameWidth(SWIPER_WIDTH);

    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs width is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), TABS_PADDING * 4 + SWIPER_WIDTH);
    EXPECT_EQ(tabsFrameSize.Height(), layoutSize);
}

/**
 * @tc.name: TabsLayoutAlgorithmMeasure019
 * @tc.desc: test if height is adaptived when tabs has padding and border, and overlap is true
 * @tc.type: FUNC
 */
HWTEST_F(TabsLayoutAlgorithmTest, TabsLayoutAlgorithmMeasure019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    TabsModelNG model = CreateTabs();
    model.SetHeightAuto(true);
    model.SetIsVertical(false);
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step2. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
    LayoutConstraintF layoutConstraintVaild;

    float layoutSize = 10000.0f;
    layoutConstraintVaild.selfIdealSize.SetSize(SizeF(layoutSize, layoutSize));
    AceType::DynamicCast<TabsLayoutProperty>(layoutWrapper.GetLayoutProperty())
        ->UpdateLayoutConstraint(layoutConstraintVaild);
    PaddingProperty padding;
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(Dimension(20, DimensionUnit::VP));

    layoutWrapper.GetLayoutProperty()->UpdatePadding(padding);
    layoutWrapper.GetLayoutProperty()->UpdateBorderWidth(borderWidth);
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabsLayoutAlgorithm));
    layoutWrapper.GetLayoutProperty()->UpdateContentConstraint();

    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    geometryNode1->SetFrameHeight(SWIPER_HEIGHT);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));

    layoutWrapper.AppendChild(swiperLayoutWrapper);
    auto dividerNode = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_DIVIDER_INDEX));
    RefPtr<GeometryNode> geometryNode2 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> dividerLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(dividerNode, geometryNode2, dividerNode->GetLayoutProperty());
    layoutWrapper.AppendChild(dividerLayoutWrapper);

    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();

    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, geometryNode3, tabBarNode_->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);

    /**
     * @tc.steps: step3. Call Measure interface.
     * @tc.expected: step3. After calling the Measure interface, tabs height is adaptived.
     */
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    auto tabsFrameSize = geometryNode->GetMarginFrameSize();
    EXPECT_EQ(tabsFrameSize.Width(), layoutSize);
    EXPECT_EQ(tabsFrameSize.Height(), TABS_PADDING * 4 + SWIPER_HEIGHT);
}
} // namespace OHOS::Ace::NG