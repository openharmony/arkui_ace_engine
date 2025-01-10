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

#include "core/components/tab_bar/tab_theme.h"
#include "core/components_ng/pattern/image/image_render_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_property.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class TabsAttrTestNg : public TabsTestNg {
public:
    std::function<void()> GetDefaultBuilder()
    {
        return []() {
            RowModelNG rowModel;
            rowModel.Create(std::nullopt, nullptr, "");
            ViewAbstract::SetWidth(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)));
            ViewAbstract::SetHeight(CalcLength(Dimension(50.f)));
        };
    }

    RefPtr<FrameNode> CreateCustomNode(const std::string& tag)
    {
        auto frameNode = AceType::MakeRefPtr<FrameNode>(
            tag, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
        auto layoutProperty = frameNode->GetLayoutProperty();
        layoutProperty->UpdateUserDefinedIdealSize(
            CalcSize(CalcLength(Dimension(1.0, DimensionUnit::PERCENT)), CalcLength(Dimension(50.f))));
        return frameNode;
    }
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
    TabsModelNG model = CreateTabs(BarPosition::START, 0);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs(BarPosition::END, 1);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs(BarPosition::START, 2);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs(BarPosition::END, 3);
    model.SetIsVertical(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

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
    FlushUITasks();

    auto dividerRenderContext = dividerNode_->GetRenderContext();
    BlurStyleOption option;
    EXPECT_EQ(dividerRenderContext->GetOpacityValue(), 0.0);
    EXPECT_EQ(layoutProperty_->GetDividerValue(), divider);
    EXPECT_EQ(tabBarPattern_->animationDuration_, -1);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    EXPECT_EQ(swiperLayoutProperty_->GetDirectionValue(), Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarWidthValue(Dimension(56.f)), Dimension(-1.f));
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarHeightValue(Dimension(56.f)), Dimension(-1.f));
    auto renderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackBlurStyle().value_or(option).blurStyle, BlurStyle::NO_MATERIAL);

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
    FlushUITasks();

    EXPECT_EQ(dividerRenderContext->GetOpacityValue(), 1.0);
    EXPECT_EQ(layoutProperty_->GetDividerValue(), divider);
    EXPECT_EQ(tabBarPattern_->animationDuration_, 500);
    EXPECT_EQ(swiperPaintProperty_->GetDurationValue(400), 500);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    EXPECT_EQ(swiperLayoutProperty_->GetDirectionValue(), Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarWidthValue(Dimension(56.f)), Dimension(60.f));
    EXPECT_EQ(tabBarLayoutProperty_->GetTabBarHeightValue(Dimension(56.f)), Dimension(60.f));
    EXPECT_EQ(renderContext->GetBackBlurStyle().value_or(option).blurStyle, BlurStyle::COMPONENT_THICK);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetTabBarWidth(Dimension(10.f));
    model.SetTabBarHeight(Dimension(10.f));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetDivider(divider);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetDivider(divider);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetBarGridAlign(options);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(GetChildX(tabBarNode_, 0), 186.25);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), 273.125);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), 360);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), 446.875);
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
    TabsModelNG model = CreateTabs();
    model.SetDivider(divider);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    pattern_->OnUpdateShowDivider();
    auto childNode = frameNode_->GetChildAtIndex(1);
    EXPECT_EQ(childNode->GetTag(), V2::DIVIDER_ETS_TAG);
}

/**
 * @tc.name: TabContentModelSetIndicator001
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetIndicator001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IndicatorStyle indicator;
    indicator.color = Color::BLACK;
    indicator.height = 10.0_vp;
    indicator.width = 20.0_vp;
    indicator.borderRadius = 2.0_vp;
    indicator.marginTop = 3.0_vp;
    tabContentPattern->SetIndicatorStyle(indicator);
    FlushUITasks();
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    tabContentModel.Pop();
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    tabContentModel.SetTabBar("", "", std::nullopt, nullptr, true); // SetTabBar without builder
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(0); // for AddChildToGroup
    tabContentNode->GetTabBarItemId();      // for AddTabBarItem
    tabContentNode->SetParent(weakTab);     // for AddTabBarItem
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto imageNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto textNode = GetChildFrameNode(colNode, 1);
    EXPECT_EQ(textNode->GetTag(), V2::TEXT_ETS_TAG);
}

/**
 * @tc.name: TabContentModel002
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModel002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    TabBarSymbol tabBarSymbol;
    tabContentModel.SetTabBar("", "", tabBarSymbol, nullptr, true);
    tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(0); // for AddChildToGroup
    tabContentNode->GetTabBarItemId();      // for AddTabBarItem
    tabContentNode->SetParent(weakTab);     // for AddTabBarItem
    tabContentModel.AddTabBarItem(tabContentFrameNode, 0, true);
    ViewStackProcessor::GetInstance()->PopContainer();
    CreateTabsDone(model);
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto symbolNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(symbolNode->GetTag(), V2::SYMBOL_ETS_TAG);

    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOn = tabTheme->GetBottomTabSymbolOn();
    EXPECT_EQ(symbolProperty->GetSymbolColorListValue({})[0], defaultColorOn);
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
    TabsModelNG model = CreateTabs();
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    model = CreateTabs();
    model.SetBarOverlap(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FALSE(layoutProperty_->GetBarOverlap().value());

    model = CreateTabs();
    model.SetBarOverlap(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext->UpdateBackgroundColor(Color::RED);
    EXPECT_TRUE(layoutProperty_->GetBarOverlap().value());

    model = CreateTabs();
    model.SetBarOverlap(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    renderContext->UpdateBackgroundColor(Color::RED);
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
    TabsModelNG model = CreateTabs();
    model.SetBarBackgroundColor(Color::RED);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto renderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(renderContext->GetBackgroundColor().value_or(Color::BLACK), Color::RED);
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
    TabsModelNG model = CreateTabs();
    model.SetWidthAuto(true);
    model.SetHeightAuto(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(layoutProperty_->GetWidthAutoValue(false));
    EXPECT_TRUE(layoutProperty_->GetHeightAutoValue(false));
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
    TabsModelNG model = CreateTabs();
    bool duration = true;
    for (int i = 0; i <= 1; i++) {
        model.SetAnimationDuration(duration);
        duration = false;
    }
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    const std::string tag = "TabsID";
    int32_t nodeId = 1;
    auto frameNode = TabsModelNG::GetOrCreateTabsNode(tag, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
    ASSERT_NE(frameNode, nullptr);
}

/**
 * @tc.name: TabsModelNg001
 * @tc.desc: Tabs Model NG.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelNg001, TestSize.Level1)
{
    auto onGestureSwipe = [](int32_t index, const AnimationCallbackInfo& info) {};
    TabsModelNG model = CreateTabs();
    model.SetOnGestureSwipe(std::move(onGestureSwipe));
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetScrollable(true);
    model.SetScrollable(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
}

/**
 * @tc.name: TabsModelSetClipEdge001
 * @tc.desc: test SetClipEdge
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetClipEdge001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetClipEdge(true);
    model.SetClipEdge(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetPadding(padding);
    tabContentModel.Pop();
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetLayoutMode(layoutMode);
    tabContentModel.Pop();
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetVerticalAlign(verticalAlign);
    tabContentModel.Pop();
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetSymmetricExtensible(isExtensible);
    tabContentModel.Pop();
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    model.SetBarAdaptiveHeight(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
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
     * @tc.steps: steps1. Default ScrollableBarModeOptions
     * @tc.expected: The items are compact and centered
     */
    ScrollableBarModeOptions option;
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetScrollableBarModeOptions(option);
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    float halfTabsWidth = TABS_WIDTH / 2;
    EXPECT_EQ(GetChildX(tabBarNode_, 0), halfTabsWidth - BARITEM_SIZE * 2);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), halfTabsWidth - BARITEM_SIZE);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), halfTabsWidth);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), halfTabsWidth + BARITEM_SIZE);

    /**
     * @tc.steps: steps2. Set margin and ALWAYS_AVERAGE_SPLIT
     * @tc.expected: The items are evenly distributed
     */
    float margin = 10.f;
    option.margin = Dimension(margin);
    option.nonScrollableLayoutStyle = LayoutStyle::ALWAYS_AVERAGE_SPLIT;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    float interval = (halfTabsWidth - margin) / 2;
    EXPECT_EQ(GetChildX(tabBarNode_, 0), margin);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), halfTabsWidth - interval);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), halfTabsWidth);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), halfTabsWidth + interval);

    /**
     * @tc.steps: steps3. Set SPACE_BETWEEN_OR_CENTER, and total items width not exceed halfTabsWidth
     * @tc.expected: The items are compact and centered in halfTabsWidth
     */
    option.margin = Dimension(0.f);
    option.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    interval = halfTabsWidth / TABCONTENT_NUMBER;
    EXPECT_EQ(GetChildX(tabBarNode_, 0), halfTabsWidth - interval * 2);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), halfTabsWidth - interval);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), halfTabsWidth);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), halfTabsWidth + interval);

    /**
     * @tc.steps: steps4. Set SPACE_BETWEEN_OR_CENTER, and total items width exceed halfTabsWidth
     * @tc.expected: The items are evenly distributed
     */
    option.margin = Dimension(0.f);
    option.nonScrollableLayoutStyle = LayoutStyle::SPACE_BETWEEN_OR_CENTER;
    const float tabsWidth = BARITEM_SIZE * (TABCONTENT_NUMBER + 1);
    ViewAbstract::SetWidth(AceType::RawPtr(frameNode_), CalcLength(tabsWidth));
    tabBarLayoutProperty_->UpdateScrollableBarModeOptions(option);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    halfTabsWidth = tabsWidth / 2;
    EXPECT_EQ(GetChildX(tabBarNode_, 0), halfTabsWidth - BARITEM_SIZE * 2);
    EXPECT_EQ(GetChildX(tabBarNode_, 1), halfTabsWidth - BARITEM_SIZE);
    EXPECT_EQ(GetChildX(tabBarNode_, 2), halfTabsWidth);
    EXPECT_EQ(GetChildX(tabBarNode_, 3), halfTabsWidth + BARITEM_SIZE);
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
    TabsModelNG model = CreateTabs();
    model.SetBarGridAlign(BarGridColumnOptions);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

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
    TabsModelNG model = CreateTabs();
    model.SetAnimationDuration(duration);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FLOAT_EQ(duration, 1);

    /**
     * @tc.steps: step2. Test function SetAnimationDuration.
     * @tc.expected: Related function runs ok.
     */
    duration = -1;
    model = CreateTabs();
    model.SetAnimationDuration(duration);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_FLOAT_EQ(duration, -1);
}

/**
 * @tc.name: TabsModelSetAnimationDuration003
 * @tc.desc: test SetAnimationDuration
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelSetAnimationDuration003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultDuration = tabTheme->GetTabContentAnimationDuration();

    /**
     * @tc.steps: step2. Test function SetAnimationDuration in APIVersion 10.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_10);
    ASSERT_FALSE(tabBarPattern_->GetAnimationDuration().has_value());
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    /**
     * @tc.steps: step3. Test function SetAnimationDuration in APIVersion 11.
     * @tc.expected: Related function runs ok.
     */
    pipeline->SetMinPlatformVersion(PLATFORM_VERSION_11);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), defaultDuration);
    tabBarPattern_->animationDuration_.reset();

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 0);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(1);
    tabBarPattern_->UpdateAnimationDuration();
    EXPECT_FLOAT_EQ(tabBarPattern_->GetAnimationDuration().value_or(-1), 1);
    tabBarPattern_->animationDuration_.reset();
    tabBarPattern_->SetAnimationDuration(-1);
    tabBarPattern_->UpdateAnimationDuration();
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    swiperLayoutProperty_->UpdateIndex(1);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
    CreateTabs(BarPosition::START, 1);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(swiperNode_->TotalChildCount(), 4);
}

/**
 * @tc.name: TabsModelPop001
 * @tc.desc: test SetDivider
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelPop001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);
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
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. Get tabs pattern to create layoutAlgorithm, and call measure and layout functions.
     * @tc.expected: step1. related function is called.
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
    TabsModelNG model = CreateTabs(BarPosition::START, 1);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(swiperNode_->TotalChildCount(), TABCONTENT_NUMBER);
    EXPECT_EQ(frameNode_->GetIndex(), 1);

    ClearOldNodes();
    model = CreateTabs(BarPosition::START, 2);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetIndex(), 2);

    ClearOldNodes();
    model = CreateTabs(BarPosition::START, -1);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetIndex(), 0);
}

/**
 * @tc.name: TabContentModelAddTabBarItem001
 * @tc.desc: test method with isRTL && useLocalizedPadding_ and LayoutMode::HORIZONTAL in BOTTOMTABBATSTYLE
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto tabContentModel = CreateTabContent();
    tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabContentModel.SetLayoutMode(LayoutMode::HORIZONTAL);
    bool onApplyCalled = false;
    std::string modeValue = "";
    TabBarSymbol tabBarSymbol;
    tabBarSymbol.onApply = [&onApplyCalled, &modeValue](WeakPtr<NG::FrameNode> node, std::string mode) {
        onApplyCalled = true;
        modeValue = mode;
    };
    tabBarSymbol.selectedFlag = true;
    tabContentModel.SetTabBar("", "", tabBarSymbol, nullptr, true);
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    auto tabContentPattern = tabContentNode->GetPattern<TabContentPattern>();
    tabContentPattern->useLocalizedPadding_ = true;
    PaddingProperty padding;
    padding.left = CalcLength(10.0);
    padding.right = CalcLength(20.0);
    tabContentPattern->SetPadding(padding);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    /**
     * @tc.steps: step1. check if columnNode padding was correctly swapped and onApply is called.
     */
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentNode->GetTabBarItemId());
    auto finalPadding = columnNode->GetLayoutProperty()->padding_.get();
    EXPECT_EQ(finalPadding->left, CalcLength(20.0));
    EXPECT_EQ(finalPadding->right, CalcLength(10.0));
    auto linearLayoutProperty = columnNode->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(linearLayoutProperty->IsVertical());
    EXPECT_TRUE(onApplyCalled);
    EXPECT_EQ(modeValue, "selected");
}

/**
 * @tc.name: TabContentModelAddTabBarItem002
 * @tc.desc: test method with Symbol and myIndex dont eq indicator and with onApply
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabContentModel1 = CreateTabContent();
    tabContentModel1.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    auto tabContentModel2 = CreateTabContent();
    std::string modeValue = "";
    bool onApplyCalled = false;
    TabBarSymbol tabBarSymbol;
    tabBarSymbol.onApply = [&onApplyCalled, &modeValue](WeakPtr<NG::FrameNode> node, std::string mode) {
        onApplyCalled = true;
        modeValue = mode;
    };
    tabContentModel2.SetTabBar("", "", tabBarSymbol, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    /**
     * @tc.steps: step1. Symbol has value and check onApplyCalled is called under myIndex dont eq indicator.
     */
    EXPECT_TRUE(onApplyCalled);
    EXPECT_EQ(modeValue, "normal");
}

/**
 * @tc.name: TabContentModelAddTabBarItem003
 * @tc.desc: test method with Symbol and myIndex dont eq indicator and without onApply
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabContentModel1 = CreateTabContent();
    tabContentModel1.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    auto tabContentModel2 = CreateTabContent();
    TabBarSymbol tabBarSymbol;
    tabBarSymbol.onApply = nullptr;
    tabContentModel2.SetTabBar("", "", tabBarSymbol, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    /**
     * @tc.steps: step1. Symbol has value and check myIndex dont eq indicator and without onApply.
     */
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto symbolNode = GetChildFrameNode(columnNode, 0);
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOff = tabTheme->GetBottomTabSymbolOff();
    EXPECT_EQ(symbolProperty->GetSymbolColorListValue({})[0], defaultColorOff);
}

/**
 * @tc.name: TabContentModelAddTabBarItem004
 * @tc.desc: test method with Symbol modifierOnApply != nullptr and selectedFlag false
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);
    auto tabContentModel = CreateTabContent();
    bool onApplyCalled = false;
    std::string modeValue = "";
    TabBarSymbol tabBarSymbol;
    tabBarSymbol.onApply = [&onApplyCalled, &modeValue](WeakPtr<NG::FrameNode> node, std::string mode) {
        onApplyCalled = true;
        modeValue = mode;
    };
    tabBarSymbol.selectedFlag = false;
    tabContentModel.SetTabBar("", "", tabBarSymbol, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    /**
     * @tc.steps: step1. check if onApply is called and value is set correctly.
     */
    EXPECT_TRUE(onApplyCalled);
    EXPECT_EQ(modeValue, "normal");
}

/**
 * @tc.name: TabContentModelAddTabBarItem005
 * @tc.desc: test method with imageSourceInfo.IsSvg() && myIndex == indicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    iconStyle.unselectedColor = Color::BLACK;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    auto tabContentModel = CreateTabContent();
    tabContentModel.SetTabBar("test", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    tabContentModel2.SetTabBar("", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. check if SvgFillColor is called and value is set correctly.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode->GetTabBarItemId());
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto iconNode = GetChildFrameNode(columnNode, 0);
    auto iconNode1 = GetChildFrameNode(columnNode1, 0);
    auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty->GetSvgFillColor().value(), Color::WHITE);
    auto imagePaintProperty1 = iconNode1->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty1->GetSvgFillColor().value(), Color::BLACK);
}

/**
 * @tc.name: TabContentModelAddTabBarItem006
 * @tc.desc: test method with imageSourceInfo.IsSvg() && myIndex == indicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem006, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabContentModel = CreateTabContent();
    tabContentModel.SetTabBar("test", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    tabContentModel2.SetTabBar("", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    /**
     * @tc.steps: step1. check if SvgFillColor is called and value is set correctly.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode->GetTabBarItemId());
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto iconNode = GetChildFrameNode(columnNode, 0);
    auto iconNode1 = GetChildFrameNode(columnNode1, 0);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOff = tabTheme->GetBottomTabIconOff();
    auto defaultColorOn = tabTheme->GetBottomTabIconOn();
    auto imagePaintProperty = iconNode->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty->GetSvgFillColor().value(), defaultColorOn);
    auto imagePaintProperty1 = iconNode1->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty1->GetSvgFillColor().value(), defaultColorOff);
}

/**
 * @tc.name: TabContentModelAddTabBarItem007
 * @tc.desc: test method with ComponentContent
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem007, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabContentModel = CreateTabContent();
    RefPtr<FrameNode> tabBarNode1 = CreateCustomNode("tabbar1");
    tabContentModel.SetTabBar("", "", std::nullopt, nullptr, true);
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    frameNodePattern->SetTabBarWithContent(tabBarNode1);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    tabContentModel2.SetTabBar("", "", std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode->GetTabBarItemId());
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    EXPECT_EQ(columnNode->GetChildren().size(), 1);
    EXPECT_EQ(columnNode1->GetChildren().size(), 2);
}

/**
 * @tc.name: TabContentModelAddTabBarItem008
 * @tc.desc: test method with ComponentContent
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelAddTabBarItem008, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto tabContentModel = CreateTabContent();
    RefPtr<FrameNode> tabBarNode1 = CreateCustomNode("tabbar1");
    tabContentModel.SetTabBar("", "", std::nullopt, nullptr, true);
    auto frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    frameNodePattern->SetTabBarWithContent(tabBarNode1);
    ViewStackProcessor::GetInstance()->Pop();
    frameNodePattern->SetTabBarWithContent(nullptr);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    RefPtr<FrameNode> tabBarNode2 = CreateCustomNode("tabbar2");
    tabContentModel2.SetTabBar("", "", std::nullopt, nullptr, true);
    frameNodePattern = ViewStackProcessor::GetInstance()->GetMainFrameNodePattern<TabContentPattern>();
    frameNodePattern->SetTabBarWithContent(tabBarNode2);
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<FrameNode> tabBarNode3 = CreateCustomNode("tabbar3");
    frameNodePattern->SetTabBarWithContent(tabBarNode3);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto columnNode = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode->GetTabBarItemId());
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    EXPECT_EQ(columnNode->GetChildren().size(), 2);
    EXPECT_EQ(columnNode1->GetChildren().size(), 1);
}

/**
 * @tc.name: TabContentModelSetAttr001
 * @tc.desc: use CreateFrameNode create node and set attrs sucessfully
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelSetAttr001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(swiperNode_));
    auto elmtId = GetElmtId();
    ViewStackProcessor::GetInstance()->StartGetAccessRecordingFor(elmtId);
    TabContentModelNG tabContentModel1;
    auto frameNode = tabContentModel1.CreateFrameNode(elmtId);
    ViewStackProcessor::GetInstance()->Push(frameNode);
    auto contentNode = AceType::DynamicCast<TabContentNode>(frameNode);
    IndicatorStyle indicatorStyle1;
    indicatorStyle1.color = Color::BLACK;
    tabContentModel1.SetIndicator(indicatorStyle1);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::CLIP;
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::BLACK;
    std::string test = "999";
    auto tabBarItemFunc = TabBarItemBuilder();
    tabContentModel1.SetBoard(boardStyle);
    tabContentModel1.SetCustomTabBar(AceType::RawPtr(frameNode), AceType::RawPtr(tabBarNode_));
    tabContentModel1.SetSelectedMode(SelectedMode::INDICATOR);
    tabContentModel1.SetLabelStyle(labelStyle);
    tabContentModel1.SetIconStyle(iconStyle);
    tabContentModel1.SetUseLocalizedPadding(true);
    tabContentModel1.SetId(test);
    tabContentModel1.SetTabBarBuilder(AceType::RawPtr(frameNode), std::move(tabBarItemFunc));
    tabContentModel1.SetTabBarLabel(AceType::RawPtr(frameNode), test);
    contentNode->UpdateRecycleElmtId(elmtId);
    contentNode->GetTabBarItemId();
    contentNode->MountToParent(swiperNode_);
    ViewStackProcessor::GetInstance()->GetMainElementNode()->onMainTree_ = true;
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    EXPECT_EQ(tabContentPattern->indicatorStyle_.color, Color::BLACK);
    EXPECT_EQ(tabContentPattern->tabBarParam_.GetTabBarStyle(), TabBarStyle::NOSTYLE);
    EXPECT_EQ(tabContentPattern->boardStyle_.borderRadius, 10.0_vp);
    EXPECT_EQ(tabContentPattern->selectedMode_, SelectedMode::INDICATOR);
    EXPECT_EQ(tabContentPattern->labelStyle_.textOverflow, TextOverflow::CLIP);
    EXPECT_EQ(tabContentPattern->iconStyle_.unselectedColor, Color::BLACK);
    EXPECT_TRUE(tabContentPattern->useLocalizedPadding_);
    EXPECT_EQ(tabContentPattern->tabBarInspectorId_, test);
    EXPECT_EQ(tabContentPattern->tabBarParam_.text_, test);
}

/**
 * @tc.name: GetTabBarTextByIndex001
 * @tc.desc: Test GetTabBarTextByIndex
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, GetTabBarTextByIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto text = pattern_->GetTabBarTextByIndex(1);
    EXPECT_EQ(text, "tabBarItemName");
}

/**
 * @tc.name: SetOnTabBarClickEvent001
 * @tc.desc: Test Tabs SetOnTabBarClick with nullptr jsEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, SetOnTabBarClickEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetOnTabBarClick(nullptr);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabsModelOnUpdateShowDivider005
 * @tc.desc: Test tabs OnUpdateShowDivider LE CHILDREN_MIN_SIZE.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsModelOnUpdateShowDivider005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    frameNode_->RemoveChildAtIndex(0);
    frameNode_->RemoveChildAtIndex(0);
    pattern_->OnUpdateShowDivider();
    EXPECT_EQ(frameNode_->GetChildren().size(), 1);
}

/**
 * @tc.name: TabsPatternProvideRestoreInfo001
 * @tc.desc: Test TabsPattern::ProvideRestoreInfo.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabsPatternProvideRestoreInfo001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    std::string restoreInfo = pattern_->ProvideRestoreInfo();
    auto jsonObj = JsonUtil::ParseJsonString(restoreInfo);
    ASSERT_NE(jsonObj, nullptr);
    EXPECT_TRUE(jsonObj->Contains("Index"));
}

/**
 * @tc.name: BeforeCreateLayoutWrapper001
 * @tc.desc: test BeforeCreateLayoutWrapper001 with childrenUpdatedFrom_ = 1 and SetMaskAnimationByCreate true
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, BeforeCreateLayoutWrapper001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    tabBarPattern_->SetMaskAnimationByCreate(true);
    swiperNode_->childrenUpdatedFrom_ = 1;
    layoutProperty_->UpdateIndexSetByUser(2);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto swiperLayoutProperty = swiperNode_->GetLayoutProperty<SwiperLayoutProperty>();
    EXPECT_EQ(swiperLayoutProperty->GetIndex(), 2);
}

/**
 * @tc.name: PageFlipModeTest001
 * @tc.desc: PageFlipMode property test
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, PageFlipModeTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    // default mode is PageFlipMode::CONTINUOUS(0)
    EXPECT_EQ(swiperPattern_->GetPageFlipMode(), 0);
    // mode is PageFlipMode::SINGLE(0)
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 1);
    EXPECT_EQ(swiperPattern_->GetPageFlipMode(), 1);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), -1);
    EXPECT_EQ(swiperPattern_->GetPageFlipMode(), 0);
    // exceeding the enum range will reset to default
    model.SetPageFlipMode(AceType::RawPtr(frameNode_), 100);
    EXPECT_EQ(swiperPattern_->GetPageFlipMode(), 0);
}

/**
 * @tc.name: TabContentModelLabelStyle001
 * @tc.desc: test LabelStyle attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelLabelStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::START, 1);
    auto tabContentModel1 = CreateTabContent();
    tabContentModel1.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    tabContentModel1.SetTabBar("text1", "", std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    tabContentModel2.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    tabContentModel2.SetTabBar("text2", "", std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. check default label style.
     */
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode2, nullptr);
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto columnNode2 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode2->GetTabBarItemId());
    auto textNode1 = GetChildFrameNode(columnNode1, 1);
    auto textNode2 = GetChildFrameNode(columnNode2, 1);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto textLayoutProperty1 = textNode1->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty1->GetContent().value(), u"text1");
    EXPECT_EQ(textLayoutProperty1->GetFontWeight(), FontWeight::NORMAL);
    EXPECT_EQ(textLayoutProperty1->GetTextColor(), tabTheme->GetSubTabTextOffColor());
    auto textLayoutProperty2 = textNode2->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty2->GetContent().value(), u"text2");
    EXPECT_EQ(textLayoutProperty2->GetFontWeight(), FontWeight::MEDIUM);
    EXPECT_EQ(textLayoutProperty2->GetTextColor(), tabTheme->GetSubTabTextOnColor());

    /**
     * @tc.steps: step2. check label style after swipeTo.
     */
    SwipeToWithoutAnimation(0);
    EXPECT_EQ(textLayoutProperty1->GetFontWeight(), FontWeight::MEDIUM);
    EXPECT_EQ(textLayoutProperty1->GetTextColor(), tabTheme->GetSubTabTextOnColor());
    EXPECT_EQ(textLayoutProperty2->GetFontWeight(), FontWeight::NORMAL);
    EXPECT_EQ(textLayoutProperty2->GetTextColor(), tabTheme->GetSubTabTextOffColor());
}

/**
 * @tc.name: TabContentModelIconStyle001
 * @tc.desc: test IconStyle attribute.
 * @tc.type: FUNC
 */
HWTEST_F(TabsAttrTestNg, TabContentModelIconStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END, 1);
    auto tabContentModel1 = CreateTabContent();
    tabContentModel1.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabContentModel1.SetTabBar("svg1", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();

    auto tabContentModel2 = CreateTabContent();
    tabContentModel2.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    tabContentModel2.SetTabBar("svg2", IMAGE_SRC_URL, std::nullopt, nullptr, true);
    ViewStackProcessor::GetInstance()->Pop();
    ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    CreateTabsDone(model);

    /**
     * @tc.steps: step1. check default icon style.
     */
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode2, nullptr);
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto columnNode2 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode2->GetTabBarItemId());
    auto iconNode1 = GetChildFrameNode(columnNode1, 0);
    auto iconNode2 = GetChildFrameNode(columnNode2, 0);
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto imagePaintProperty1 = iconNode1->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty1->GetSvgFillColor().value(), tabTheme->GetBottomTabIconOff());
    auto imagePaintProperty2 = iconNode2->GetPaintProperty<ImageRenderProperty>();
    EXPECT_EQ(imagePaintProperty2->GetSvgFillColor().value(), tabTheme->GetBottomTabIconOn());

    /**
     * @tc.steps: step2. check icon style after swipeTo.
     */
    SwipeToWithoutAnimation(0);
    EXPECT_EQ(imagePaintProperty1->GetSvgFillColor().value(), tabTheme->GetBottomTabIconOn());
    EXPECT_EQ(imagePaintProperty2->GetSvgFillColor().value(), tabTheme->GetBottomTabIconOff());
}
} // namespace OHOS::Ace::NG
