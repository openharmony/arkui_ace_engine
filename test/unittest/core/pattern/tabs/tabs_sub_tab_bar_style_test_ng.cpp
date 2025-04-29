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
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"

namespace OHOS::Ace::NG {
class TabsSubTabBarStyleTestNg : public TabsTestNg {
public:
};

/**
 * @tc.name: TabsSubTabBarStyleModelTest001
 * @tc.desc: test the node can be saved in the pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentPattern->SetCustomStyleNode(frameNode);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest002
 * @tc.desc: test the node can be saved in the pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest003
 * @tc.desc: Test Tabs attr
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest003, TestSize.Level1)
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
    model.SetBarOverlap(AceType::RawPtr(frameNode_), false);
    FlushUITasks();

    auto dividerRenderContext = dividerNode_->GetRenderContext();
    BlurStyleOption option;
    EXPECT_EQ(dividerRenderContext->GetOpacityValue(), 0.0);
    EXPECT_EQ(layoutProperty_->GetDividerValue(), divider);
    EXPECT_EQ(tabBarPattern_->animationDuration_, -1);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    EXPECT_EQ(swiperLayoutProperty_->GetDirectionValue(), Axis::HORIZONTAL);
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest004
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set indicator to tab content.
     * @tc.expected: set the indicator successfully.
     */
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest005
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set indicator to tab content.
     * @tc.expected: set the indicator successfully.
     */
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

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest006
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set IndicatorStyle to tab content.
     * @tc.expected: set the IndicatorStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    tabContentPattern->SetIndicatorStyle(IndicatorStyle());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 0.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 0.0_vp);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest007
 * @tc.desc: test SetIndicator with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set IndicatorStyle to tab content.
     * @tc.expected: set the IndicatorStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    tabContentPattern->SetIndicatorStyle(IndicatorStyle());
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().width, 0.0_vp);
    EXPECT_EQ(tabContentPattern->GetIndicatorStyle().borderRadius, 0.0_vp);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest008
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. create a TabContentModelNG and set the frameNode to tab content.
     * @tc.expected: create a TabContentModelNG and set the frameNode to tab content successfully.
     */
    TabContentModelNG tabContentModel;
    tabContentModel.Create([]() {});
    tabContentModel.SetCustomStyleNode(frameNode);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest009
 * @tc.desc: Test Create(std::function<void()>&& deepRenderFunc)
 * @tc.type：FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tabContentModel.
     * @tc.expected: create a tabContentModel successfully.
     */
    TabContentModelNG tabContentModel;
    tabContentModel.Create([]() {});
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    ASSERT_NE(tabContentFrameNode, nullptr);

    /**
     * @tc.steps: step2. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest010
 * @tc.desc: test SetSubTabBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set BoardStyle to tab content.
     * @tc.expected: set the BoardStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest011
 * @tc.desc: test SetSubTabBorderRadius
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set BoardStyle to tab content.
     * @tc.expected: set the BoardStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest012
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set BoardStyle to tab content.
     * @tc.expected: set the BoardStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest013
 * @tc.desc: test SetSubTabBorderRadius with getTheme once
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest013, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set BoardStyle to tab content.
     * @tc.expected: set the BoardStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    BoardStyle boardStyle;
    boardStyle.borderRadius = 10.0_vp;
    tabContentPattern->SetBoardStyle(boardStyle);
    auto board = tabContentPattern->GetBoardStyle();
    EXPECT_EQ(board.borderRadius, boardStyle.borderRadius);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest014
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest014, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set default SelectedMode to tab content.
     * @tc.expected: SelectedMode = SelectedMode::INDICATOR.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest015
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest015, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set default SelectedMode to tab content.
     * @tc.expected: SelectedMode = SelectedMode::INDICATOR.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    EXPECT_EQ(tabContentPattern->GetSelectedMode(), SelectedMode::INDICATOR);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest016
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest016, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set LabelStyle to tab content.
     * @tc.expected: set the LabelStyle successfully.
     */
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest017
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest017, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set LabelStyle to tab content.
     * @tc.expected: set the LabelStyle successfully.
     */
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

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest018
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest018, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set LabelStyle to tab content.
     * @tc.expected: set the LabelStyle successfully.
     */
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest019
 * @tc.desc: test SetLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest019, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set IndicatorStyle to tab content.
     * @tc.expected: set the IndicatorStyle successfully.
     */
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

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest020
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest020, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set IconStyle to tab content.
     * @tc.expected: set the IconStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, std::nullopt);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest021
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest021, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set IndicatorStyle to tab content.
     * @tc.expected: set the IndicatorStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, std::nullopt);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, std::nullopt);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest022
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest022, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. set IconStyle to tab content.
     * @tc.expected: set the IconStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, iconStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, iconStyle.selectedColor);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest023
 * @tc.desc: test SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest023, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. set IconStyle to tab content.
     * @tc.expected: set the IconStyle successfully.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabContentPattern->SetIconStyle(iconStyle);
    EXPECT_EQ(tabContentPattern->GetIconStyle().unselectedColor, iconStyle.unselectedColor);
    EXPECT_EQ(tabContentPattern->GetIconStyle().selectedColor, iconStyle.selectedColor);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest024
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest024, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. init LabelStyle.
     * @tc.expected: init LabelStyle successfully.
     */
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

    /**
     * @tc.steps: step3. set the frameNode and labelStyle to tab content.
     * @tc.expected: set the frameNode and labelStyle to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    tabContentModel.SetCustomStyleNode(frameNode);
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest025
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest025, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init LabelStyle.
     * @tc.expected: init LabelStyle successfully.
     */
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

    /**
     * @tc.steps: step2. create a tab.
     * @tc.expected: create a tab successfully.
     */
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

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest026
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest026, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. init LabelStyle.
     * @tc.expected: init LabelStyle successfully.
     */
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    LabelStyle labelStyle;

    /**
     * @tc.steps: step3. set the frameNode and labelStyle to tab content.
     * @tc.expected: set the frameNode and labelStyle to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
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

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest027
 * @tc.desc: test UpdateLabelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest027, TestSize.Level1)
{
    /**
     * @tc.steps: step1. init LabelStyle.
     * @tc.expected: init LabelStyle successfully.
     */
    auto layoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    LabelStyle labelStyle;

    /**
     * @tc.steps: step2. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.UpdateLabelStyle(labelStyle, layoutProperty);
    tabContentModel.Pop();
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

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest029
 * @tc.desc: test SetIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest029, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
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
    InspectorFilter filter;
    tabContentFrameNode->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);

    std::string attr = "id";
    filter.AddFilterAttr(attr);
    json = JsonUtil::Create(true);
    tabContentFrameNode->ToJsonValue(json, filter);
    EXPECT_EQ(json->ToString(), "{\"id\":\"\",\"isLayoutDirtyMarked\":false,\"isRenderDirtyMarked\":false,"
    "\"isMeasureBoundary\":false,\"hasPendingRequest\":false,\"isFirstBuilding\":false}");

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest030
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest030, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. SetTabBar without builder
     * @tc.expected: tabbarnode has default textNode and imageNode
     */
    TabsModelNG model = CreateTabs();
    auto tabFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto weakTab = AceType::WeakClaim(AceType::RawPtr(tabFrameNode));
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    tabContentModel.SetTabBar("", "", std::nullopt, nullptr, true);
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    tabContentModel.SetCustomStyleNode(frameNode);
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(0);
    tabContentNode->GetTabBarItemId();
    tabContentNode->SetParent(weakTab);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. check the tag of frame node.
     * @tc.expected: check the tag of frame node correctly.
     */
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto imageNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto textNode = GetChildFrameNode(colNode, 1);
    EXPECT_EQ(textNode->GetTag(), frameNode->GetTag());

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest031
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest031, TestSize.Level1)
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
    tabContentModel.SetTabBar("", "", std::nullopt, nullptr, true);
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(0);
    tabContentNode->GetTabBarItemId();
    tabContentNode->SetParent(weakTab);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. check the tag of frame node.
     * @tc.expected: check the tag of frame node correctly.
     */
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto imageNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(imageNode->GetTag(), V2::IMAGE_ETS_TAG);
    auto textNode = GetChildFrameNode(colNode, 1);
    EXPECT_EQ(textNode->GetTag(), V2::TEXT_ETS_TAG);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest032
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest032, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
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
    tabContentModel.SetCustomStyleNode(frameNode);
    auto tabContentFrameNode = ViewStackProcessor::GetInstance()->GetMainElementNode();
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(tabContentFrameNode);
    tabContentNode->UpdateRecycleElmtId(0);
    tabContentNode->GetTabBarItemId();
    tabContentNode->SetParent(weakTab);
    tabContentModel.AddTabBarItem(tabContentFrameNode, 0, true);
    ViewStackProcessor::GetInstance()->PopContainer();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. check the tag of frame node.
     * @tc.expected: check the tag of frame node correctly.
     */
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto symbolNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(symbolNode->GetTag(), V2::SYMBOL_ETS_TAG);

    /**
     * @tc.steps: step4. check the SymbolColorListValue of frame node.
     * @tc.expected: check the SymbolColorListValue of frame node correctly.
     */
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOn = tabTheme->GetBottomTabSymbolOn();
    EXPECT_EQ(symbolProperty->GetSymbolColorListValue({})[0], defaultColorOn);

    /**
     * @tc.steps: step5. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest033
 * @tc.desc: test TabsModel
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest033, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
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
    tabContentNode->UpdateRecycleElmtId(0);
    tabContentNode->GetTabBarItemId();
    tabContentNode->SetParent(weakTab);
    tabContentModel.AddTabBarItem(tabContentFrameNode, 0, true);
    ViewStackProcessor::GetInstance()->PopContainer();
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. check the tag of frame node.
     * @tc.expected: check the tag of frame node correctly.
     */
    auto colNode = GetChildFrameNode(tabBarNode_, 0);
    EXPECT_EQ(colNode->GetTag(), V2::COLUMN_ETS_TAG);
    EXPECT_EQ(colNode->GetTotalChildCount(), 2);

    auto symbolNode = GetChildFrameNode(colNode, 0);
    EXPECT_EQ(symbolNode->GetTag(), V2::SYMBOL_ETS_TAG);

    /**
     * @tc.steps: step3. check the SymbolColorListValue of frame node.
     * @tc.expected: check the SymbolColorListValue of frame node correctly.
     */
    auto symbolProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOn = tabTheme->GetBottomTabSymbolOn();
    EXPECT_EQ(symbolProperty->GetSymbolColorListValue({})[0], defaultColorOn);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest034
 * @tc.desc: Test the SetPadding function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest034, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);
    /**
     * @tc.steps: steps2. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);

    /**
     * @tc.steps: step3. set the frameNode and padding to tab content.
     * @tc.expected: set the frameNode and padding to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetPadding(padding);
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps4. SetPadding.
     * @tc.expected: steps4. Check if the setting value for padding was successful.
     */
    EXPECT_EQ(tabContentPattern->GetPadding().left, padding.left);
    EXPECT_EQ(tabContentPattern->GetPadding().right, padding.right);
    EXPECT_EQ(tabContentPattern->GetPadding().top, padding.top);
    EXPECT_EQ(tabContentPattern->GetPadding().bottom, padding.bottom);

    /**
     * @tc.steps: step5. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest035
 * @tc.desc: Test the SetPadding function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest035, TestSize.Level1)
{
    /**
     * @tc.steps: steps1. Create padding and assign initial values to it.
     */
    PaddingProperty padding;
    padding.left = CalcLength(20.0_vp);
    padding.right = CalcLength(20.0_vp);
    padding.top = CalcLength(20.0_vp);
    padding.bottom = CalcLength(20.0_vp);
    /**
     * @tc.steps: step2. create a tab and set padding to the tab content.
     * @tc.expected: create a tab and set padding to the tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetPadding(padding);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps3. SetPadding.
     * @tc.expected: steps3. Check if the setting value for padding was successful.
     */
    EXPECT_EQ(tabContentPattern->GetPadding().left, padding.left);
    EXPECT_EQ(tabContentPattern->GetPadding().right, padding.right);
    EXPECT_EQ(tabContentPattern->GetPadding().top, padding.top);
    EXPECT_EQ(tabContentPattern->GetPadding().bottom, padding.bottom);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest036
 * @tc.desc: Test the SetLayoutMode function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest036, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode and the LayoutMode to tab content.
     * @tc.expected: set the frameNode and the LayoutMode to tab content successfully.
     */
    LayoutMode layoutMode = LayoutMode::AUTO;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetLayoutMode(layoutMode);
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps3. SetLayoutMode.
     * @tc.expected: steps3. Check if the value set for layoutMode was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().layoutMode, layoutMode);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest037
 * @tc.desc: Test the SetLayoutMode function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest037, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab and set LayoutMode.
     * @tc.expected: create a tab and set LayoutMode successfully.
     */
    LayoutMode layoutMode = LayoutMode::AUTO;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetLayoutMode(layoutMode);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps2. SetLayoutMode.
     * @tc.expected: steps2. Check if the value set for layoutMode was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().layoutMode, layoutMode);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest038
 * @tc.desc: Test the SetVerticalAlign function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest038, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode and the FlexAlign to tab content.
     * @tc.expected: set the frameNode and the FlexAlign to tab content successfully.
     */
    FlexAlign verticalAlign = FlexAlign::CENTER;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetVerticalAlign(verticalAlign);
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps3. SetVerticalAlign.
     * @tc.expected: steps2. Check if the value set for verticalAlign was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().verticalAlign, verticalAlign);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest039
 * @tc.desc: Test the SetVerticalAlign function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest039, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set the FlexAlign to tab content.
     * @tc.expected: set the FlexAlign to tab content successfully.
     */
    FlexAlign verticalAlign = FlexAlign::CENTER;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetVerticalAlign(verticalAlign);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps2. SetVerticalAlign.
     * @tc.expected: steps2. Check if the value set for verticalAlign was successful.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().verticalAlign, verticalAlign);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest040
 * @tc.desc: Test the SetSymmetricExtensible function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest040, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode and SymmetricExtensible to tab content.
     * @tc.expected: set the frameNode and SymmetricExtensible to tab content successfully.
     */
    bool isExtensible = true;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetSymmetricExtensible(isExtensible);
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps3. SetSymmetricExtensible.
     * @tc.expected: steps3. Check the result of SetSymmetricExtensible.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().symmetricExtensible, isExtensible);

    /**
     * @tc.steps: step4. check the frameNode.
     * @tc.expected: true.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest041
 * @tc.desc: Test the SetSymmetricExtensible function in the TabContentModel class.
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest041, TestSize.Level1)
{
    /**
     * @tc.steps: step1. set SymmetricExtensible to tab content.
     * @tc.expected: set SymmetricExtensible to tab content successfully.
     */
    bool isExtensible = true;
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetSymmetricExtensible(isExtensible);
    tabContentModel.Pop();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);

    /**
     * @tc.steps: steps2. SetSymmetricExtensible.
     * @tc.expected: steps2. Check the result of SetSymmetricExtensible.
     */
    EXPECT_EQ(tabContentPattern->GetBottomTabBarStyle().symmetricExtensible, isExtensible);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: false.
     */
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest042
 * @tc.desc: test the node can be saved in the pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest042, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a frameNode.
     * @tc.expected: step1. create a frameNode successfully.
     */
    auto frameNode = FrameNode::CreateFrameNode(
        V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. set the frameNode to tab content.
     * @tc.expected: set the frameNode to tab content successfully.
     */
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    tabContentModel.SetCustomStyleNode(frameNode);
    tabContentModel.Pop();
    CreateTabsDone(model);

    /**
     * @tc.steps: step3. check the frameNode.
     * @tc.expected: true.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode, nullptr);
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    tabContentPattern->SetCustomStyleNode(frameNode);
    EXPECT_TRUE(tabContentPattern->HasSubTabBarStyleNode());
}

/**
 * @tc.name: TabsSubTabBarStyleModelTest043
 * @tc.desc: test the node can be saved in the pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabsSubTabBarStyleTestNg, TabsSubTabBarStyleModelTest043, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create a tab.
     * @tc.expected: create a tab successfully.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. check the frameNode.
     * @tc.expected: false.
     */
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = GetChildPattern<TabContentPattern>(swiperNode_, 0);
    ASSERT_NE(tabContentPattern, nullptr);
    EXPECT_FALSE(tabContentPattern->HasSubTabBarStyleNode());
}
} // namespace OHOS::Ace::NG
