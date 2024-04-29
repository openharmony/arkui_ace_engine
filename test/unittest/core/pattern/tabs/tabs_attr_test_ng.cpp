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
 * @tc.name: TabsModelSetFadingEdge001
 * @tc.desc: test SetFadingEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetFadingEdge001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetFadingEdge(true);
    });
    EXPECT_EQ(frameNode_->GetTag(), V2::TABS_ETS_TAG);
    EXPECT_EQ(tabBarNode_->GetTag(), V2::TAB_BAR_ETS_TAG);
    EXPECT_TRUE(tabBarPaintProperty_->GetFadingEdgeValue());

    auto json = JsonUtil::Create(true);
    frameNode_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("fadingEdge"), "true");
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider001
 * @tc.desc: Test tabs OnUpdateShowDivider.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelOnUpdateShowDivider001, TestSize.Level1)
{
    Color color = Color::RED;
    TabsItemDivider divider;
    divider.color = color;
    CreateWithItem([divider](TabsModelNG model) { model.SetDivider(divider); });

    pattern_->OnUpdateShowDivider();
    auto dividerColor = dividerRenderProperty_->GetDividerColor();
    EXPECT_EQ(dividerColor.value().ColorToString(), color.ColorToString());
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider002
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelOnUpdateShowDivider002, TestSize.Level2)
{
    auto pattern = AceType::MakeRefPtr<TabsPattern>();
    pattern->OnUpdateShowDivider();
    EXPECT_EQ(pattern->GetHostFrameSize(), std::nullopt);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider003
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelOnUpdateShowDivider003, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
    pattern_->OnUpdateShowDivider();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 3);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider004
 * @tc.desc: Test tabs OnUpdateShowDivider when pattern_ without host
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelOnUpdateShowDivider004, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    pattern_->OnUpdateShowDivider();
    auto childNode = frameNode_->GetChildAtIndex(1);
    EXPECT_EQ(childNode->GetTag(), V2::DIVIDER_ETS_TAG);
}

/**
 * @tc.name: TabsModelToJsonValue001
 * @tc.desc: Test tabs ToJsonValue when host has not child.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelToJsonValue001, TestSize.Level2)
{
    CreateWithItem([](TabsModelNG model) {});
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    frameNode_->ToJsonValue(json, filter);
    auto dividerJson = json->GetValue("divider");
    EXPECT_TRUE(dividerJson->IsNull());
}

/**
 * @tc.name: TabContentModelSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetIndicator001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IndicatorStyle indicator;
    indicator.color = Color::BLACK;
    indicator.height = 10.0_vp;
    indicator.width = 20.0_vp;
    indicator.borderRadius = 2.0_vp;
    indicator.marginTop = 3.0_vp;
    tabContentPattern->SetIndicatorStyle(indicator);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().color, Color::BLACK);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().height, 10.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 20.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 2.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().marginTop, 3.0_vp);
}

/**
 * @tc.name: TabContentModelSetIndicator002
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetIndicator002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    tabContentPattern->SetIndicatorStyle(IndicatorStyle());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 0.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 0.0_vp);
}

/**
 * @tc.name: TabContentModelCreate(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelCreate001, TestSize.Level1)
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
HWTEST_F(TabsAttrTestNg, TabContentModelSetSubTabBorderRadius001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);
}

/**
 * @tc.name: TabContentModelSetSubTabBorderRadius002
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetSubTabBorderRadius002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);
}

/**
 * @tc.name: TabContentModelSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetSelectedMode001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabContentModelSetLabelStyle001
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetLabelStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    LabelStyle labelStyle;
    tabContentPattern->SetLabelStyle(labelStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().selectedColor, std::nullopt);
}

/**
 * @tc.name: TabContentModelSetLabelStyle002
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetLabelStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
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
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetLabelStyle(labelStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().textOverflow, labelStyle.textOverflow);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxLines, labelStyle.maxLines);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().minFontSize->ToString(), labelStyle.minFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().maxFontSize->ToString(), labelStyle.maxFontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().heightAdaptivePolicy, labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontSize->ToString(), labelStyle.fontSize->ToString());
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontWeight, labelStyle.fontWeight);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontFamily, labelStyle.fontFamily);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().fontStyle, labelStyle.fontStyle);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().unselectedColor, labelStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetLabelStyle().selectedColor, labelStyle.selectedColor);
}

/**
 * @tc.name: TabContentModelSetIconStyle001
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetIconStyle001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, std::nullopt);
}

/**
 * @tc.name: TabContentModelSetIconStyle002
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetIconStyle002, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, iconStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, iconStyle.selectedColor);
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle001
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelUpdateLabelStyle001, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
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
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
        }, 0);
    });
    EXPECT_EQ(layoutProperty->GetTextOverflow(), labelStyle.textOverflow);
    EXPECT_EQ(layoutProperty->GetMaxLines(), labelStyle.maxLines);
    EXPECT_EQ(layoutProperty->GetAdaptMinFontSize(), labelStyle.minFontSize);
    EXPECT_EQ(layoutProperty->GetAdaptMaxFontSize(), labelStyle.maxFontSize);
    EXPECT_EQ(layoutProperty->GetHeightAdaptivePolicy(), labelStyle.heightAdaptivePolicy);
    EXPECT_EQ(layoutProperty->GetFontSize(), labelStyle.fontSize);
    EXPECT_EQ(layoutProperty->GetFontWeight(), labelStyle.fontWeight);
    EXPECT_EQ(layoutProperty->GetFontFamily(), labelStyle.fontFamily);
    EXPECT_EQ(layoutProperty->GetItalicFontStyle(), labelStyle.fontStyle);
}

/**
 * @tc.name: TabContentModelUpdateLabelStyle002
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelUpdateLabelStyle002, TestSize.Level1)
{
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    LabelStyle labelStyle;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
        }, 0);
    });
    EXPECT_FALSE(layoutProperty->GetTextOverflow().has_value());
    EXPECT_FALSE(layoutProperty->GetMaxLines().has_value());
    EXPECT_FALSE(layoutProperty->GetAdaptMinFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetAdaptMaxFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetHeightAdaptivePolicy().has_value());
    EXPECT_FALSE(layoutProperty->GetFontSize().has_value());
    EXPECT_FALSE(layoutProperty->GetFontWeight().has_value());
    EXPECT_FALSE(layoutProperty->GetFontFamily().has_value());
    EXPECT_FALSE(layoutProperty->GetItalicFontStyle().has_value());
}

/**
 * @tc.name: TabContentModelToJsonValue001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelToJsonValue001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    labelStyle.maxLines = 0;
    labelStyle.minFontSize = 0.0_vp;
    labelStyle.maxFontSize = 0.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MAX_LINES_FIRST;
    labelStyle.fontSize = 0.0_vp;
    labelStyle.fontWeight = FontWeight::NORMAL;
    labelStyle.fontFamily = { "unknown", "unknow2" };
    tabContentPattern->SetLabelStyle(labelStyle);
    std::unique_ptr<JsonValue> json = std::make_unique<JsonValue>();
    tabContentFrameNode->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: TabContentModel001
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModel001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. SetTabBar without builder
     * @tc.expected: tabbarnode has default textNode and imageNode
     */
    Create([](TabsModelNG model) {
        auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
        TabContentModelNG tabContentModel;
        tabContentModel.Create();
        tabContentModel.SetTabBar("", "", nullptr, true); // SetTabBar without builder
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
        auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
        auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
        tabContentNode->UpdateRecycleElmtId(0); // for AddChildToGroup
        tabContentNode->GetTabBarItemId();           // for AddTabBarItem
        tabContentNode->SetParent(weakTab);          // for AddTabBarItem
        tabContentModel.Pop();
    });
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 1);

    auto imageNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
}

/**
 * @tc.name: TabsModelSetBarOverlap001
 * @tc.desc: test SetBarOverlap
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetBarOverlap001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarOverlap true
     * @tc.expected: steps2. Check the BarOverlap property value
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(true);
    });
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(false);
    });
    EXPECT_FALSE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(true);
    });
    tabBarPaintProperty_->UpdateBarBackgroundColor(Color::RED);
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    CreateWithItem([](TabsModelNG model) {
        model.SetBarOverlap(false);
    });
    tabBarPaintProperty_->UpdateBarBackgroundColor(Color::RED);
    EXPECT_FALSE(layoutProperty_->GetBarOverlap().value());
}

/**
 * @tc.name: TabsModelSetBarBackgroundColor001
 * @tc.desc: test SetBarBackgroundColor
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetBarBackgroundColor001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarBackgroundColor true
     * @tc.expected: steps2. Check the BarBarBackgroundColor property value
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarBackgroundColor(Color::RED);
    });
    EXPECT_EQ(tabBarPaintProperty_->GetBarBackgroundColor().value_or(Color::BLACK), Color::RED);
}

/**
 * @tc.name: TabsModelSetWidthAuto001
 * @tc.desc: test SetWidthAuto and SetHeightAuto
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetWidthAuto001, TestSize.Level1)
{
 /**
  * @tc.steps: step1. Test function SetWidthAuto and SetHeightAuto When isAuto is true.
  * @tc.expected: Related functions run ok.
  */
    CreateWithItem([](TabsModelNG model) {
        model.SetWidthAuto(true);
        model.SetHeightAuto(true);
    });
    auto tabsLayoutProperty = layoutProperty_;
    EXPECT_TRUE(tabsLayoutProperty->GetWidthAutoValue(false));
    EXPECT_TRUE(tabsLayoutProperty->GetHeightAutoValue(false));
}

/**
 * @tc.name: TabsModelSetAnimationDuration001
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetAnimationDuration001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {
        bool duration = true;
        for (int i = 0; i <= 1; i++) {
            model.SetAnimationDuration(duration);
            duration = false;
        }
    });
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode001
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelGetOrCreateTabsNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function TabsModelGetOrCreateTabsNode.
     * @tc.expected: Related function runs ok.
     */
    CreateWithItem([](TabsModelNG model) {});
    const std::string tag = "TabsID";
    int32_t nodeId = 1;
    auto frameNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TabsModelSetOnChange001
 * @tc.desc: test SetOnChange
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetOnChange001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetOnChange(nullptr);
    });

    /**
     * @tc.steps: step2. Test function SetOnChange.
     * @tc.expected: Related function runs ok.
     */
    ASSERT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: TabsModelNg001
 * @tc.desc: Tabs Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelNg001, TestSize.Level1)
{
    auto onGestureSwipe = [](int32_t index, const AnimationCallbackInfo& info) {};
    CreateWithItem([=](TabsModelNG model) {
        model.SetOnGestureSwipe(std::move(onGestureSwipe));
    });
    auto eventHub = swiperNode_->GetEventHub<SwiperEventHub>();
    EXPECT_NE(eventHub->gestureSwipeEvent_, nullptr);
}

/**
 * @tc.name: TabsModelSetScrollable001
 * @tc.desc: test SetScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetScrollable001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetScrollable(true);
        model.SetScrollable(false);
    });
}

/**
 * @tc.name: TabsModelSetClipEdge001
 * @tc.desc: test SetClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetClipEdge001, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {
        model.SetClipEdge(true);
        model.SetClipEdge(false);
    });
}

/**
 * @tc.name: TabContentModelSetPadding001
 * @tc.desc: Test the SetPadding function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetPadding001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetPadding(padding);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

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
HWTEST_F(TabsAttrTestNg, TabContentModelSetLayoutMode001, TestSize.Level1)
{
    LayoutMode layoutMode = LayoutMode::AUTO;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetLayoutMode(layoutMode);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. SetLayoutMode.
     * @tc.expected: steps2. Check if the value set for layoutMode was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().layoutMode, layoutMode);
}

/**
 * @tc.name: TabContentModelSetVerticalAlign001
 * @tc.desc: Test the SetVerticalAlign function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetVerticalAlign001, TestSize.Level1)
{
    FlexAlign verticalAlign = FlexAlign::CENTER;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetVerticalAlign(verticalAlign);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

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
HWTEST_F(TabsAttrTestNg, TabContentModelSetSymmetricExtensible001, TestSize.Level1)
{
    bool isExtensible = true;
    Create([=](TabsModelNG model) {
        CreateSingleItem([=](TabContentModelNG tabContentModel) {
            tabContentModel.SetSymmetricExtensible(isExtensible);
        }, 0);
    });
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: steps2. SetSymmetricExtensible.
     * @tc.expected: steps2. Check the result of SetSymmetricExtensible.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().symmetricExtensible, isExtensible);
}

/**
 * @tc.name: TabsModelSetBarAdaptiveHeight001
 * @tc.desc: Test the SetBarAdaptiveHeight function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetBarAdaptiveHeight001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetBarAdaptiveHeight.
     * @tc.expected: steps2. Check the result of SetBarAdaptiveHeight.
     */
    CreateWithItem([](TabsModelNG model) {
        model.SetBarAdaptiveHeight(false);
    });
    EXPECT_TRUE(tabBarLayoutProperty_->GetBarAdaptiveHeight());
}

/**
 * @tc.name: TabsModelSetScrollableBarModeOptions001
 * @tc.desc: Test the SetScrollableBarModeOptions function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetScrollableBarModeOptions001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetScrollableBarModeOptions.
     * @tc.expected: steps2. Check if the SetScrollableBarModeOptions function successfully sets
     *                       ScrollableBarModeOptions.
     */
    ScrollableBarModeOptions option;
    option.margin = 0.0_vp;
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_CENTER;
    CreateWithItem([option](TabsModelNG model) {
        model.SetScrollableBarModeOptions(option);
    });
    EXPECT_EQ(tabBarLayoutProperty_->GetScrollableBarModeOptions(), option);
}

/**
 * @tc.name: TabsModelSetBarGridAlign001
 * @tc.desc: Test the SetBarGridAlign function in the TabsModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetBarGridAlign001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. Create BarGridColumnOptions and assign them initial values.
     */
    BarGridColumnOptions BarGridColumnOptions;
    BarGridColumnOptions.sm = -1;
    BarGridColumnOptions.md = -1;
    BarGridColumnOptions.lg = -1;
    BarGridColumnOptions.gutter = 0.0_vp;
    BarGridColumnOptions.margin = 0.0_vp;
    CreateWithItem([BarGridColumnOptions](TabsModelNG model) {
        model.SetBarGridAlign(BarGridColumnOptions);
    });

    /**
     * @tc.steps: steps3. SetBarGridAlign.
     * @tc.expected: steps3. Check if the SetBarGridAlign function has successfully set BarGridColumnOptions.
     */
    EXPECT_EQ(tabBarLayoutProperty_->GetBarGridAlign(), BarGridColumnOptions);
}

/**
 * @tc.name: TabsModelSetAnimationDuration002
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetAnimationDuration002, TestSize.Level1)
{
    float duration = 1;
    CreateWithItem([duration](TabsModelNG model) {
        model.SetAnimationDuration(duration);
    });
    EXPECT_FLOAT_EQ(duration, 1);

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    duration = -1;
    CreateWithItem([duration](TabsModelNG model) {
        model.SetAnimationDuration(duration);
    });
    EXPECT_FLOAT_EQ(duration, -1);
}

/**
 * @tc.name: TabsModelSetAnimationDuration003
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetAnimationDuration003, TestSize.Level1)
{
    CreateWithItem([](TabsModelNG model) {});
    auto pipeline = PipelineContext::GetCurrentContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultDuration = tabTheme->GetTabContentAnimationDuration();

    /**
     * @tc.steps: step2. Test function SetAnimationDuration in APIVersion 10.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    ASSERT_FALSE(tabBarPattern_->GetAnimationDuration().has_value());
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    /**
     * @tc.steps: step3. Test function SetAnimationDuration in APIVersion 11.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
}

/**
 * @tc.name: TabsModelNGSetIndex001
 * @tc.desc: Test the SetIndex function in the TabsModelNG class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelNGSetIndex001, TestSize.Level2)
{
    /**
     * @tc.steps: steps2. GetScrollableBarModeOptions.
     * @tc.expected: steps2. Check the result of GetScrollableBarModeOptions.
     */
    CreateWithItem([](TabsModelNG model) {});
    swiperLayoutProperty_->UpdateIndex(1);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
    CreateWithItem([](TabsModelNG model) {}, BarPosition::START, 1);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
}

/**
 * @tc.name: TabsModelPop001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelPop001, TestSize.Level1)
{
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        }, 1);
    }, BarPosition::END);
    tabBarNode_->eventHub_ = AceType::MakeRefPtr<EventHub>();
    tabBarNode_->eventHub_->focusHub_ = AceType::MakeRefPtr<FocusHub>(tabBarNode_->eventHub_);
    ASSERT_NE(tabBarNode_->eventHub_->focusHub_, nullptr);
    tabBarPattern_->OnModifyDone();
    tabBarPattern_->swiperController_->removeTabBarEventCallback_();
    tabBarPattern_->swiperController_->addTabBarEventCallback_();
    EXPECT_NE(tabBarPattern_->swiperController_, nullptr);
}

/**
 * @tc.name: TabContentModelCreate2(std::function<void()>&& deepRenderFunc)
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelCreate002, TestSize.Level1)
{
    TabContentModelNG tabContentModel;
    auto deepRenderFunc = []() { AceType::MakeRefPtr<FrameNode>("test", 1, AceType::MakeRefPtr<Pattern>()); };
    tabContentModel.Create(deepRenderFunc);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    TabsModelNG Mode1NG;
    Mode1NG.Create(BarPosition::END, 0, nullptr, nullptr);
    tabContentPattern->shallowBuilder_->deepRenderFunc_();
}

/**
 * @tc.name: TabsModelGetOrCreateTabsNode002
 * @tc.desc: test GetOrCreateTabsNode
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelGetOrCreateTabsNode002, TestSize.Level1)
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
    auto frameNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
    auto tabsNode2 =
        TabsModelNG::GetOrCreateTabsNode("TabsID2", nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(tabsNode2, nullptr);
}

/**
* @tc.name: TabsModelMeasure007
* @tc.desc: test Measure
* @tc.type: FUNC
*/
HWTEST_F(TabsAttrTestNg, TabsModelMeasure007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize all properties of tabs.
     */
    CreateWithItem([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
    });

    /**
     * @tc.steps: step1. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step1. related function is called.
     */
    auto tabsLayoutAlgorithm = pattern_->CreateLayoutAlgorithm();

    RefPtr<GeometryNode> geometryNode = AceType::MakeRefPtr<GeometryNode>();
    LayoutWrapperNode layoutWrapper =
        LayoutWrapperNode(frameNode_, geometryNode, frameNode_->GetLayoutProperty());
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
     * @tc.steps: step1. Set currentChildCount_ Value is 0
     * @tc.expected: step1. After calling the Measure interface, layoutWrapper GetTotalChildCount() -2 <=0
     */
    layoutWrapper.currentChildCount_ = 0;
    tabsLayoutAlgorithm->Measure(&layoutWrapper);
    tabsLayoutAlgorithm->Layout(&layoutWrapper);
    EXPECT_TRUE(layoutWrapper.GetTotalChildCount() - 2 <= 0);
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
