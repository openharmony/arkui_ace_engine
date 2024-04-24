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

#include "tabs_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabBarEventTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange001
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange002
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange003
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a bottom style tabbar and a sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange004
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build a sub style tabbar and a bottom style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange005
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two sub style tabbar.
     */
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    });

    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003
 * @tc.desc: test HandleAlwaysAverageSplitLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty<TabBarLayoutProperty>());
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperLayoutProperty_);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
    tabBarLayoutAlgorithm->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper, FIRST_ITEM_SIZE, 5);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002
 * @tc.desc: test HandleSpaceBetweenOrCenterLayoutStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    LayoutWrapperNode layoutWrapper_test =
        LayoutWrapperNode(tabBarNode_, geometryNode, tabBarLayoutProperty_);
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);

    RefPtr<GeometryNode> geometryNode1 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> swiperLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(swiperNode_, geometryNode1, swiperNode_->GetLayoutProperty());
    swiperLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    swiperLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(swiperLayoutWrapper);

    auto tabBarLayoutAlgorithm = AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
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
 * @tc.name: TabBarPatternHandleBottomTabBarClick001
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleSubTabBarClick002
 * @tc.desc: test HandleSubTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleSubTabBarClick002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    int32_t index = 1;
    SizeF size(0.1f, 0.2f);
    tabBarNode_->GetGeometryNode()->SetFrameSize(size);
    tabBarPattern_->SetChildrenMainSize(0.3f);
    auto swiperFrameNode = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    auto swiperPattern = swiperFrameNode->GetPattern<SwiperPattern>();
    swiperPattern->currentIndex_ = 0;
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;

    int32_t nodeId = 1;
    for (int i = 0; i <= 4; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    tabBarNode_->GetGeometryNode()->GetFrameSize().SetMainSize(2.0f, Axis::HORIZONTAL);
    auto childFrameNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
    auto childGeometryNode = childFrameNode->GetGeometryNode();
    childGeometryNode->GetMarginFrameSize().SetMainSize(1.0f, Axis::HORIZONTAL);
    auto childFrameNode1 = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index - 1));
    auto childGeometryNode1 = childFrameNode1->GetGeometryNode();
    auto childFrameSize1 = childGeometryNode1->GetMarginFrameSize();
    childFrameSize1.SetMainSize(0.1f, Axis::HORIZONTAL);
    OffsetF c1(0.1f, 0.2f);
    tabBarPattern_->tabItemOffsets_.emplace_back(c1);

    /**
     * @tc.steps: step2. Test function HandleSubTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern_->HandleSubTabBarClick(tabBarLayoutProperty_, index);
        tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchDown001
 * @tc.desc: test HandleTouchDown
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleTouchDown001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->swiperController_->SetRemoveSwiperEventCallback(nullptr);
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchDown.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 1;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchDown(index);
        tabBarPattern_->swiperController_->SetRemoveSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp001
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleTouchUp001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern_->SetTouching(false);
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 1;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchUp(index);
        tabBarPattern_->swiperController_->SetAddSwiperEventCallback([]() {});
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchUp002
 * @tc.desc: test HandleTouchUp
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleTouchUp002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 1;
    tabBarPattern_->swiperController_->SetAddSwiperEventCallback(nullptr);
    tabBarPattern_->SetTouching(true);
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function HandleTouchUp.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->hoverIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value(), 1);
    tabBarPattern_->touchingIndex_.emplace(1);
    EXPECT_EQ(tabBarPattern_->touchingIndex_.value(), 1);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->HandleTouchUp(index);
                tabBarPattern_->SetTouching(true);
                tabBarPattern_->swiperController_->SetAddSwiperEventCallback([]() {});
                tabBarPattern_->hoverIndex_.reset();
                EXPECT_FALSE(tabBarPattern_->hoverIndex_.has_value());
            }
            tabBarPattern_->touchingIndex_.emplace(0);
        }
        tabBarPattern_->hoverIndex_.emplace(1);
    }

    tabBarPattern_->hoverIndex_.reset();
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchUp(index);
        tabBarPattern_->SetTouching(true);
        tabBarPattern_->hoverIndex_.emplace(1);
    }
}

/**
 * @tc.name: TabBarPatternHandleTouchEvent003
 * @tc.desc: test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleTouchEvent003, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->tabItemOffsets_ = { { -1.0f, -1.0f }, { 1.0f, 1.0f }, { 2.0f, 2.0f } };
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->HandleTouchEvent(touchLocationInfo);
        tabBarPattern_->tabBarType_.clear();
        tabBarNode_->RemoveChildAtIndex(1);
    }
    EXPECT_EQ(tabBarNode_->TotalChildCount(), 1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
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
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto layoutProperty = tabBarLayoutProperty_;
    int32_t childCount = 2;

    /**
     * @tc.steps: steps2. Create two children for layoutWrapper.
     */
    auto tabBarNode_test = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_TAB_BAR_INDEX));
    ASSERT_NE(tabBarNode_test, nullptr);
    RefPtr<GeometryNode> geometryNode3 = AceType::MakeRefPtr<GeometryNode>();
    RefPtr<LayoutWrapperNode> tabBarLayoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_test, geometryNode3, tabBarNode_test->GetLayoutProperty());
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateLayoutConstraint(childLayoutConstraint);
    tabBarLayoutWrapper->GetLayoutProperty()->UpdateUserDefinedIdealSize(
        CalcSize(CalcLength(FIRST_ITEM_WIDTH), CalcLength(FIRST_ITEM_HEIGHT)));
    layoutWrapper.AppendChild(tabBarLayoutWrapper);
    auto tabBarNode_test1 = AceType::DynamicCast<FrameNode>(frameNode_->GetChildAtIndex(TEST_TAB_BAR_INDEX));
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
 * @tc.name: TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002
 * @tc.desc: Test the HandleAlwaysAverageSplitLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleAlwaysAverageSplitLayoutStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarPattern_->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
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
} // namespace OHOS::Ace::NG
