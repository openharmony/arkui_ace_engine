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

#include "core/components_ng/pattern/dialog/dialog_layout_property.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabBarEventTestNg : public TabsTestNg {
public:
    void LongPress(Offset location);
    void DragTo(Offset location);
};

void TabBarEventTestNg::LongPress(Offset location)
{
    auto handleLongPressEvent = tabBarPattern_->longPressEvent_->GetGestureEventFunc();
    GestureEvent info;
    info.SetLocalLocation(location);
    handleLongPressEvent(info);
}

void TabBarEventTestNg::DragTo(Offset location)
{
    auto dragUpdate = tabBarPattern_->dragEvent_->GetActionUpdateEventFunc();
    GestureEvent info;
    info.SetLocalLocation(location);
    dragUpdate(info);
}

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
    tabBarPattern_->tabBarType_.emplace(std::make_pair(1, TabBarParamType::CUSTOM_BUILDER));

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

/**
 * @tc.name: Drag001
 * @tc.desc: test Press to drag barItem
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, Drag001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto pipeline = frameNode_->GetContext();
    pipeline->fontScale_ = BIG_FONT_SIZE_SCALE; // for InitLongPressEvent
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    const Offset firstItemPoint = Offset(180.f, 30.f);
    const Offset secondItemPoint = Offset(540.f, 30.f);
    const Offset outOfTabBarPoint = Offset(540.f, 200.f);

    /**
     * @tc.steps: step1. Long press on barItem(index:0)
     * @tc.expected: Show dialog
     */
    HandleMouseEvent(MouseAction::MOVE, firstItemPoint);
    HandleHoverEvent(true);
    HandleTouchEvent(TouchType::DOWN, firstItemPoint);
    LongPress(firstItemPoint);
    EXPECT_NE(tabBarPattern_->dialogNode_, nullptr);

    /**
     * @tc.steps: step2. Drag to itSelf
     * @tc.expected: moveIndex_ be set
     */
    DragTo(firstItemPoint);
    EXPECT_EQ(tabBarPattern_->moveIndex_, 0);
    EXPECT_NE(tabBarPattern_->dialogNode_, nullptr);

    /**
     * @tc.steps: step3. Drag to barItem(index:1)
     * @tc.expected: moveIndex_ changed
     */
    DragTo(secondItemPoint);
    EXPECT_EQ(tabBarPattern_->moveIndex_, 1);
    EXPECT_NE(tabBarPattern_->dialogNode_, nullptr);

    /**
     * @tc.steps: step4. Drag to outSide
     * @tc.expected: Nothing changed
     */
    DragTo(outOfTabBarPoint);
    EXPECT_EQ(tabBarPattern_->moveIndex_, 1);
    EXPECT_NE(tabBarPattern_->dialogNode_, nullptr);

    /**
     * @tc.steps: step5. Release press
     * @tc.expected: Hide dialog
     */
    HandleTouchEvent(TouchType::UP, outOfTabBarPoint);
    EXPECT_EQ(tabBarPattern_->dialogNode_, nullptr);
    pipeline->fontScale_ = 1.f;
}

/**
 * @tc.name: DialogStyle001
 * @tc.desc: test Dailog style
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, DialogStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto pipeline = frameNode_->GetContext();
    pipeline->fontScale_ = BIG_FONT_SIZE_SCALE; // for InitLongPressEvent
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    const Offset firstItemPoint = Offset(180.f, 30.f);

    /**
     * @tc.steps: step1. Press/TouchUp to show/hide dialog, Set BIG_FONT_SIZE_SCALE
     * @tc.expected: Dialog width changed
     */
    LongPress(firstItemPoint);
    auto dialog = tabBarPattern_->dialogNode_;
    auto dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
    EXPECT_EQ(dialogLayoutProp->GetWidthValue().ConvertToPx(), BIG_DIALOG_WIDTH);

    /**
     * @tc.steps: step2. Set MAX_FONT_SIZE_SCALE
     * @tc.expected: Dialog width changed
     */
    pipeline->fontScale_ = MAX_FONT_SIZE_SCALE;
    LongPress(firstItemPoint);
    dialog = tabBarPattern_->dialogNode_;
    dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
    EXPECT_EQ(dialogLayoutProp->GetWidthValue().ConvertToPx(), MAX_DIALOG_WIDTH);

    /**
     * @tc.steps: step3. Set LARGE_FONT_SIZE_SCALE
     * @tc.expected: Dialog width changed
     */
    pipeline->fontScale_ = LARGE_FONT_SIZE_SCALE;
    LongPress(firstItemPoint);
    dialog = tabBarPattern_->dialogNode_;
    dialogLayoutProp = AceType::DynamicCast<DialogLayoutProperty>(dialog->GetLayoutProperty());
    EXPECT_EQ(dialogLayoutProp->GetWidthValue().ConvertToPx(), BIG_DIALOG_WIDTH);
    pipeline->fontScale_ = 1.f;
}

/**
 * @tc.name: ScrollableEvent001
 * @tc.desc: test position when out of Boundary
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, ScrollableEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    // Set tabs width less than total barItems width, make tabBar scrollable
    const float tabsWidth = BARITEM_SIZE * (TABCONTENT_NUMBER - 1);
    ViewAbstract::SetWidth(CalcLength(tabsWidth));
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Drag out of left Boundary
     * @tc.expected: The friction take effect
     */
    float outOffset = 1.f;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { outOffset, outOffset + BARITEM_SIZE };
    tabBarPattern_->visibleItemPosition_[2] = { outOffset + BARITEM_SIZE * 2, outOffset + tabsWidth };
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    float dragOffset = 100.f;
    scrollable->UpdateScrollPosition(dragOffset, SCROLL_FROM_UPDATE);
    EXPECT_GT(tabBarPattern_->currentDelta_, 0.0f);
    EXPECT_LT(tabBarPattern_->currentDelta_, dragOffset);

    /**
     * @tc.steps: step2. Drag out of right Boundary
     * @tc.expected: The friction take effect
     */
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[1] = { -outOffset, -outOffset + BARITEM_SIZE };
    tabBarPattern_->visibleItemPosition_[TABCONTENT_NUMBER - 1] = { -outOffset + BARITEM_SIZE * 2,
        -outOffset + tabsWidth };
    dragOffset = -100.f;
    scrollable->UpdateScrollPosition(dragOffset, SCROLL_FROM_UPDATE);
    EXPECT_LT(tabBarPattern_->currentDelta_, 0.0f);
    EXPECT_GT(tabBarPattern_->currentDelta_, dragOffset);
}

/**
 * @tc.name: ScrollableEvent002
 * @tc.desc: Scroll tabBar by SCROLL_FROM_AXIS
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, ScrollableEvent002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    // Set tabs width less than total barItems width, make scrollable
    ViewAbstract::SetWidth(CalcLength(BARITEM_SIZE));
    CreateTabContentsWithBuilder(2);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Scroll to right, not out of Boundary
     * @tc.expected: The scrollOffset not changed by AdjustOffset
     */
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->UpdateScrollPosition(-BARITEM_SIZE / 2, SCROLL_FROM_AXIS);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, -BARITEM_SIZE / 2);

    /**
     * @tc.steps: step2. Scroll to right out of Boundary
     * @tc.expected: Can not out of Boundary by AdjustOffset
     */
    scrollable->UpdateScrollPosition(-BARITEM_SIZE * 2, SCROLL_FROM_AXIS);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);

    /**
     * @tc.steps: step3. Scroll to left out of Boundary
     * @tc.expected: Can not out of Boundary by AdjustOffset
     */
    scrollable->UpdateScrollPosition(BARITEM_SIZE * 2, SCROLL_FROM_AXIS);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
}

/**
 * @tc.name: TabBarItemClickEventTest001
 * @tc.desc: Test AddTabBarItemClickEvent and verify the click event callback.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarItemClickEventTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents();
    CreateTabsDone(model);
    auto tabBarItem = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(1));
    EXPECT_EQ(tabBarItem->GetTag(), "Column");
    /**
     * @tc.steps: step1. tabBarItem1 click and expect index eq 1
     */
    GestureEvent info;
    info.SetLocalLocation(Offset(200.f, 30.f));
    auto eventHub = tabBarItem->GetOrCreateGestureEventHub();
    (*eventHub->clickEventActuator_->clickEvents_.front())(info);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
}

/**
 * @tc.name: HandleSubTabBarClick003
 * @tc.desc: test CanScroll without visibleItemPosition_
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, HandleSubTabBarClick003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    bool finishCalled = false;
    AnimationOption option;
    auto finishCallback = [&finishCalled]() { finishCalled = true; };
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::FIXED);
    tabBarPattern_->animationDuration_ = 3;
    tabBarPattern_->indicatorAnimationIsRunning_ = true;
    tabBarPattern_->translateAnimationIsRunning_ = true;
    tabBarPattern_->tabbarIndicatorAnimation_ = AnimationUtils::StartAnimation(option, [&]() {}, finishCallback);
    /**
     * @tc.steps: step1. handle HandleSubTabBarClick and TriggerTranslateAnimation method.
     */
    tabBarPattern_->HandleSubTabBarClick(tabBarLayoutProperty_, 1);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
    EXPECT_FALSE(tabBarPattern_->translateAnimationIsRunning_);
    EXPECT_EQ(tabBarPattern_->targetIndex_.value_or(0), 0);
    EXPECT_EQ(tabBarPattern_->jumpIndex_.value_or(0), 0);
    EXPECT_EQ(tabBarPattern_->animationTargetIndex_, 1);
    EXPECT_TRUE(finishCalled);
}

/**
 * @tc.name: HandleSubTabBarClick004
 * @tc.desc: test HandleSubTabBarClick with tabsPattern->GetIsCustomAnimation() && indicator == index
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, HandleSubTabBarClick004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->changeByClick_ = false;
    pattern_->isCustomAnimation_ = false;
    tabBarLayoutProperty_->UpdateIndicator(1);
    tabBarPattern_->HandleSubTabBarClick(tabBarLayoutProperty_, 1);
    EXPECT_FALSE(tabBarPattern_->changeByClick_);
}

/**
 * @tc.name: HandleSubTabBarClick005
 * @tc.desc: test HandleSubTabBarClick with tabsPattern->IsCustomAnimation()
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, HandleSubTabBarClick005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->changeByClick_ = false;
    tabBarPattern_->isAnimating_ = false;
    pattern_->isCustomAnimation_ = true;
    swiperPattern_->currentIndex_ = 0;
    swiperPattern_->customAnimationToIndex_ = 0;
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->animationDuration_ = 3;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE,
        TabBarStyle::SUBTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE };
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    /**
     * @tc.steps: step1. call method in tabsPattern->GetIsCustomAnimation() and TriggerTranslateAnimation.
     */
    tabBarPattern_->HandleSubTabBarClick(tabBarLayoutProperty_, 1);
    EXPECT_EQ(swiperPattern_->customAnimationToIndex_, 1);
    EXPECT_TRUE(tabBarPattern_->isAnimating_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->indicatorAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
}

/**
 * @tc.name: HandleTouchEvent004
 * @tc.desc: Test HandleTouchEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, HandleTouchEvent004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    /**
     * @tc.steps: step1. call callback method in InitTouch and hadlemouse events with tabBarType_ second is true
     */
    TouchEventInfo info = TouchEventInfo("touch");
    TouchLocationInfo touchLocationInfo = TouchLocationInfo(1);
    touchLocationInfo.SetLocalLocation(Offset(200.0, 30.0));
    touchLocationInfo.SetTouchType(TouchType::DOWN);
    info.AddTouchLocationInfo(std::move(touchLocationInfo));
    auto eventHub = tabBarNode_->GetOrCreateGestureEventHub();
    auto actuator = eventHub->touchEventActuator_;
    auto events = actuator->touchEvents_;
    events.front()->callback_(info);
    tabBarPattern_->tabBarType_ = { { 0, TabBarParamType::NORMAL }, { 1, TabBarParamType::CUSTOM_BUILDER } };
    tabBarPattern_->HandleHoverEvent(true);
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::MOVE);
    mouseInfo.SetLocalLocation(Offset(200.0, 30.0));
    tabBarPattern_->HandleMouseEvent(mouseInfo);
    tabBarPattern_->isTouchingSwiper_ = true;
    EXPECT_EQ(tabBarPattern_->touchingIndex_.value(), 1);
    EXPECT_EQ(tabBarPattern_->hoverIndex_.value_or(0), 0);
    EXPECT_FALSE(tabBarPattern_->isHover_);
    swiperController_->surfaceChangeCallback_();
    EXPECT_FALSE(tabBarPattern_->isTouchingSwiper_);
}

/**
 * @tc.name: TabBarPatternCanScroll001
 * @tc.desc: test TabBarPatternCanScroll without visibleItemPosition_
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternCanScroll001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    /**
     * @tc.steps: step1. trigger CanScroll without visibleItemPosition_.
     */
    EXPECT_NE(tabBarLayoutProperty_->GetTabBarModeValue(TabBarMode::FIXED), TabBarMode::FIXED);
    EXPECT_FALSE(tabBarPattern_->CanScroll());
}

/**
 * @tc.name: TabBarPatternOnKeyEvent001
 * @tc.desc: test OnKeyEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarEventTestNg, TabBarPatternOnKeyEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::NOSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::NOSTYLE);
    CreateTabsDone(model);
    auto pipeline = frameNode_->GetContext();
    pipeline->isFocusActive_ = true;
    /**
     * @tc.steps: step1. call OnKeyEvent use Axis::HORIZONTAL and KeyCode::KEY_TAB and isCustomAnimation_ is true
     */
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    KeyEvent event;
    event.action = KeyAction::DOWN;
    event.code = KeyCode::KEY_TAB;
    pattern_->isCustomAnimation_ = true;
    EXPECT_TRUE(tabBarPattern_->OnKeyEvent(event));
    EXPECT_EQ(swiperPattern_->customAnimationToIndex_, 1);
    /**
     * @tc.steps: step2. call OnKeyEvent use other code
     */
    event.code = KeyCode::KEY_9;
    EXPECT_FALSE(tabBarPattern_->OnKeyEvent(event));
}
} // namespace OHOS::Ace::NG
