/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

class TabsAttrTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: Interface001
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Interface001, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition is default, index is default, vertical is default
     * @tc.expected: TabBar is at top, show first tabContent(size > 0), swiper is HORIZONTAL
     */
    CreateWithItem([](TabsModelNG model) {}, BarPosition::START, 0);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().GetY(), 0);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 0);
    EXPECT_GT(GetChildWidth(swiperNode_, 0), 0);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::HORIZONTAL);
}

/**
 * @tc.name: Interface002
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Interface002, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition is END, index is 1, vertical is default
     * @tc.expected: TabBar is at bottom, show second tabContent(size > 0)
     */
    CreateWithItem([](TabsModelNG model) {}, BarPosition::END, 1);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().GetY(), TABS_HEIGHT - TABBAR_DEFAULT_HEIGHT);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 1);
    EXPECT_GT(GetChildWidth(swiperNode_, 1), 0);
}

/**
 * @tc.name: Interface003
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Interface003, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition is default, index is -1, vertical is true
     * @tc.expected: TabBar is at left, show third tabContent(size > 0), swiper is VERTICAL
     */
    CreateWithItem([](TabsModelNG model) { model.SetIsVertical(true); }, BarPosition::START, 2);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().GetX(), 0);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 2);
    EXPECT_GT(GetChildWidth(swiperNode_, 2), 0);
    EXPECT_EQ(swiperPattern_->GetDirection(), Axis::VERTICAL);
}

/**
 * @tc.name: Interface004
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Interface004, TestSize.Level1)
{
    /**
     * @tc.cases: BarPosition is END, index is TABCONTENT_NUMBER, vertical is true
     * @tc.expected: TabBar is at right, show fourth tabContent(size > 0)
     */
    CreateWithItem([](TabsModelNG model) { model.SetIsVertical(true); }, BarPosition::END, 3);
    EXPECT_EQ(tabBarNode_->GetGeometryNode()->GetFrameRect().GetX(), TABS_WIDTH - TABBAR_DEFAULT_WIDTH);
    EXPECT_EQ(swiperPattern_->GetCurrentShownIndex(), 3);
    EXPECT_GT(GetChildWidth(swiperNode_, 3), 0);
}

/**
 * @tc.name: Interface005
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Interface005, TestSize.Level1)
{
    /**
     * @tc.cases: create tabs
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 0, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    CreateItem(TABCONTENT_NUMBER);
    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode_ = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode_->GetOrCreateFocusHub();
    model.Pop();
    GetInstance();
    FlushLayoutTask(frameNode_);

    /**
     * @tc.cases: set invalid properties
     * @tc.expected: tabs properties equals expected value
     */
    TabsItemDivider divider;
    divider.isNull = true;
    divider.strokeWidth = Dimension(1.0f);
    model.SetDivider(AceType::RawPtr(frameNode_), divider);
    model.SetAnimationDuration(AceType::RawPtr(frameNode_), -1);
    model.SetIsVertical(AceType::RawPtr(frameNode_), false);
    model.SetTabBarHeight(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetTabBarWidth(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetBarOverlap(AceType::RawPtr(frameNode_), false);
    FlushLayoutTask(frameNode_);

    auto dividerRenderContext = dividerNode_->GetRenderContext();
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(dividerRenderContext->GetOpacityValue(), 0.0);
    EXPECT_EQ(layoutProperty_->GetDividerValue(), divider);
    EXPECT_EQ(tabBarPattern_->animationDuration_, -1);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    EXPECT_EQ(swiperLayoutProperty_->GetDirectionValue(), Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarWidthValue(Dimension(56.f)), Dimension(-1.f));
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarHeightValue(Dimension(56.f)), Dimension(-1.f));
    EXPECT_FALSE(tabBarRenderContext->HasFrontSaturate());

    /**
     * @tc.steps3: set valid properties
     * @tc.expected: tabs properties equals expected value
     */
    divider.isNull = false;
    model.SetDivider(AceType::RawPtr(frameNode_), divider);
    model.SetAnimationDuration(AceType::RawPtr(frameNode_), 500);
    model.SetIsVertical(AceType::RawPtr(frameNode_), true);
    model.SetTabBarHeight(AceType::RawPtr(frameNode_), Dimension(60.f));
    model.SetTabBarWidth(AceType::RawPtr(frameNode_), Dimension(60.f));
    model.SetBarOverlap(AceType::RawPtr(frameNode_), true);
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(dividerRenderContext->GetOpacityValue(), 1.0);
    EXPECT_EQ(layoutProperty_->GetDividerValue(), divider);
    EXPECT_EQ(tabBarPattern_->animationDuration_, 500);
    EXPECT_EQ(swiperPaintProperty_->GetDurationValue(400), 500);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    EXPECT_EQ(swiperLayoutProperty_->GetDirectionValue(), Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarWidthValue(Dimension(56.f)), Dimension(60.f));
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarHeightValue(Dimension(56.f)), Dimension(60.f));
    EXPECT_EQ(tabBarRenderContext->GetFrontSaturateValue(BAR_SATURATE), BAR_SATURATE);
}

/**
 * @tc.name: Bar001
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Bar001, TestSize.Level1)
{
    /**
     * @tc.cases: BarMode is default
     * @tc.expected: TabBarItem width is average of TABS_WIDTH, barWidth is TABS_WIDTH
     */
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), TABS_WIDTH / TABCONTENT_NUMBER);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, TABBAR_DEFAULT_HEIGHT)));
}

/**
 * @tc.name: Bar002
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Bar002, TestSize.Level1)
{
    /**
     * @tc.cases: BarMode is SCROLLABLE
     * @tc.expected: TabBarItem width is its actual width
     */
    CreateWithItem([](TabsModelNG model) { model.SetTabBarMode(TabBarMode::SCROLLABLE); });
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), 10.f);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, TABBAR_DEFAULT_HEIGHT)));
}

/**
 * @tc.name: Bar003
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Bar003, TestSize.Level1)
{
    /**
     * @tc.cases: Set BarWidth 10, set barHeight 10
     * @tc.expected: TabBarItem width is average of 10, barWidth is 10, barHeight is 10
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetTabBarWidth(Dimension(10.f));
        model.SetTabBarHeight(Dimension(10.f));
    });
    EXPECT_EQ(GetChildWidth(tabBarNode_, 0), 10.f / TABCONTENT_NUMBER);
    EXPECT_TRUE(IsEqual(tabBarNode_->GetGeometryNode()->GetFrameSize(), SizeF(10.f, 10.f)));
}

/**
 * @tc.name: Divider001
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Divider001, TestSize.Level1)
{
    /**
     * @tc.cases: No set divider
     * @tc.expected: No show divider
     */
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(TABS_WIDTH, 0.f))); // (720.f, 0.f)
}

/**
 * @tc.name: Divider002
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Divider002, TestSize.Level1)
{
    /**
     * @tc.cases: Set Divider
     * @tc.expected: Has divider
     */
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(4);
    divider.startMargin = Dimension(5);
    divider.endMargin = Dimension(5);
    divider.color = Color::BLUE;
    divider.isNull = false;
    CreateWithItem([divider](TabsModelNG model) { model.SetDivider(divider); });
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(710.f, 4.f)));
}

/**
 * @tc.name: Divider003
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, Divider003, TestSize.Level1)
{
    /**
     * @tc.cases: Set Divider and isNull is true
     * @tc.expected: Has divider and create a new divider replace
     */
    TabsItemDivider divider;
    divider.strokeWidth = Dimension(4);
    divider.startMargin = Dimension(5);
    divider.endMargin = Dimension(5);
    divider.color = Color::BLUE;
    divider.isNull = true;
    CreateWithItem([divider](TabsModelNG model) { model.SetDivider(divider); });
    EXPECT_TRUE(IsEqual(dividerNode_->GetGeometryNode()->GetFrameSize(), SizeF(720.f, 1.f)));
}

/**
 * @tc.name: BarGridAlign001
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, BarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.cases: Default
     * @tc.expected: TabBarItem position is default
     */
    CreateWithItem([](TabsModelNG model) {});
    EXPECT_EQ(GetChildX(tabBarNode_, 0), TABS_WIDTH / TABCONTENT_NUMBER * 0);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), TABS_WIDTH / TABCONTENT_NUMBER * 1);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), TABS_WIDTH / TABCONTENT_NUMBER * 2);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), TABS_WIDTH / TABCONTENT_NUMBER * 3);
}

/**
 * @tc.name: BarGridAlign002
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, BarGridAlign002, TestSize.Level1)
{
    /**
     * @tc.cases: Set BarGridColumnOptions
     * @tc.expected: TabBarItem position changed
     */
    BarGridColumnOptions options;
    options.md = 4;
    options.gutter = Dimension(5);
    options.margin = Dimension(10);
    CreateWithItem([options](TabsModelNG model) { model.SetBarGridAlign(options); });
    EXPECT_EQ(GetChildX(tabBarNode_, 0), 186.25);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), 273.125);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 360);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), 446.875);
}

/**
 * @tc.name: BarGridAlign003
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, BarGridAlign003, TestSize.Level1)
{
    /**
     * @tc.cases: Set BarGridColumnOptions
     * @tc.expected: TabBarItem position changed
     */
    TabsModelNG model;
    model.Create(BarPosition::START, 1, nullptr, nullptr);
    ViewAbstract::SetWidth(CalcLength(TABS_WIDTH));
    ViewAbstract::SetHeight(CalcLength(TABS_HEIGHT));
    CreateItem(TABCONTENT_NUMBER);
    auto tabNode = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto tabBarNode_ = AceType::DynamicCast<FrameNode>(tabNode->GetTabBar());
    tabBarNode_->GetOrCreateFocusHub();

    frameNode_ = AceType::DynamicCast<TabsNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    swiperNode_ = AceType::DynamicCast<FrameNode>(frameNode_->GetTabs());
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(swiperNode_->TotalChildCount(), TABCONTENT_NUMBER);

    model.SetIndex(2);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetIndex(), 2);

    model.SetIndex(-1);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->GetIndex(), 0);
}
} // namespace OHOS::Ace::NG
