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
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

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
 * @tc.name: TabBarPatternHandleBottomTabBarChange006
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange006, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange007
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange007, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange008
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange008, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarChange009
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarChange009, TestSize.Level1)
{
    /**
     * @tc.steps: step2. call HandleBottomTabBarChange function.
     * @tc.expected: step2. expect The function is run ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->indicator_ = 0;
    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->HandleBottomTabBarChange(1);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick001
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick002
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick003
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick004
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);

    /**
     * @tc.steps: step2. Test function HandleBottomTabBarClick.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->HandleBottomTabBarClick(selectedIndex, unselectedIndex);
}

/**
 * @tc.name: TabBarPatternHandleBottomTabBarClick005
 * @tc.desc: test HandleBottomTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternHandleBottomTabBarClick005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t selectedIndex = 1;
    int32_t unselectedIndex = 1;
    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);

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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t index = 1;
    SizeF size(0.1f, 0.2f);
    tabBarNode_->GetGeometryNode()->SetFrameSize(size);
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
    tabBarPattern_->visibleItemPosition_[0] = { 0.1f, 0.2f };

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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabContents(1);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));

    /**
     * @tc.steps: steps2. HandleTouchEvent
     * @tc.expected: steps2. Check the number of tabBarNode_ TotalChildCount
     */
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    touchLocationInfo.SetLocalLocation(Offset(0.f, 0.f));
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    tabbarLayoutAlgorithm->childCount_ = 2;
    tabbarLayoutAlgorithm->contentMainSize_ = TABS_WIDTH;

    /**
     * @tc.steps: steps2. HandleAlwaysAverageSplitLayoutStyle.
     * @tc.expected: steps2. Check itemWidths after HandleAlwaysAverageSplitLayoutStyle by using different itemWidths.
     */
    float itemWidth1 = 400.0f;
    tabbarLayoutAlgorithm->visibleItemLength_.clear();
    tabbarLayoutAlgorithm->visibleItemLength_[0] = itemWidth1;
    tabbarLayoutAlgorithm->visibleItemLength_[1] = itemWidth1;
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[0], itemWidth1);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[1], itemWidth1);

    float itemWidth2 = 300.0f;
    tabbarLayoutAlgorithm->visibleItemLength_[0] = itemWidth2;
    tabbarLayoutAlgorithm->visibleItemLength_[1] = itemWidth2;
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[0], TABS_WIDTH / tabbarLayoutAlgorithm->childCount_);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[1], TABS_WIDTH / tabbarLayoutAlgorithm->childCount_);

    tabbarLayoutAlgorithm->visibleItemLength_[0] = itemWidth1;
    tabbarLayoutAlgorithm->visibleItemLength_[1] = itemWidth2;
    tabbarLayoutAlgorithm->HandleAlwaysAverageSplitLayoutStyle(&layoutWrapper);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[0], itemWidth1);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[1], TABS_WIDTH - itemWidth1);
}

/**
 * @tc.name: TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001
 * @tc.desc: Test the HandleSpaceBetweenOrCenterLayoutStyle function in the TabBarLayoutAlgorithm class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarLayoutAlgorithmHandleSpaceBetweenOrCenterLayoutStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabbarLayoutAlgorithm =
        AceType::DynamicCast<TabBarLayoutAlgorithm>(tabBarNode_->GetPattern<TabBarPattern>()->CreateLayoutAlgorithm());
    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper = LayoutWrapperNode(tabBarNode_, geometryNode, tabBarNode_->GetLayoutProperty());
    layoutWrapper.SetLayoutAlgorithm(AceType::MakeRefPtr<LayoutAlgorithmWrapper>(tabbarLayoutAlgorithm));
    auto childLayoutConstraint = layoutWrapper.GetLayoutProperty()->CreateChildConstraint();
    childLayoutConstraint.selfIdealSize = OptionalSizeF(FIRST_ITEM_SIZE);
    auto layoutProperty = tabBarLayoutProperty_;
    tabbarLayoutAlgorithm->childCount_ = 2;

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
    tabbarLayoutAlgorithm->visibleChildrenMainSize_ = 100000.0f;
    tabbarLayoutAlgorithm->contentMainSize_ = TABS_WIDTH;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper);
    EXPECT_FALSE(tabbarLayoutAlgorithm->useItemWidth_);

    tabbarLayoutAlgorithm->visibleItemLength_.clear();
    tabbarLayoutAlgorithm->visibleItemLength_[0] = 0.0f;
    tabbarLayoutAlgorithm->visibleItemLength_[1] = 2.0f;
    tabbarLayoutAlgorithm->visibleChildrenMainSize_ = 2.0f;
    tabbarLayoutAlgorithm->HandleSpaceBetweenOrCenterLayoutStyle(&layoutWrapper);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[0], 179.0f);
    EXPECT_EQ(tabbarLayoutAlgorithm->visibleItemLength_[1], 181.0f);
}
} // namespace OHOS::Ace::NG
