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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/divider/divider_layout_property.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_spring_effect.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class TabBarTestNg : public TabsTestNg {
public:
    RefPtr<RenderContext> GetBarItemRenderContext(int32_t index)
    {
        auto columnNode = GetChildFrameNode(tabBarNode_, index);
        auto columnNodeRenderContext = columnNode->GetRenderContext();
        return columnNodeRenderContext;
    }
};

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard001
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateSubTabBoard001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto pipeline = frameNode_->GetContext();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarPattern_->UpdateSubTabBoard(0);
    pipeline->fontScale_ = BIG_FONT_SIZE_SCALE;
    tabBarPattern_->UpdateSubTabBoard(0);

    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    pipeline->fontScale_ = LARGE_FONT_SIZE_SCALE;
    tabBarPattern_->UpdateSubTabBoard(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    pipeline->fontScale_ = MAX_FONT_SIZE_SCALE;
    tabBarPattern_->UpdateSubTabBoard(tabBarPattern_->indicator_);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    IndicatorStyle style;
    tabBarPattern_->SetIndicatorStyle(style, 1);
    tabBarPattern_->UpdateSubTabBoard(tabBarPattern_->indicator_);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->UpdateSubTabBoard(tabBarPattern_->indicator_);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard(tabBarPattern_->indicator_);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->tabBarStyles_[0] = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->selectedModes_[0] = SelectedMode::BOARD;
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->UpdateSubTabBoard(tabBarPattern_->indicator_);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    pipeline->fontScale_ = 1.f;
}

/**
 * @tc.name: TabBarPatternUpdateSubTabBoard002
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateSubTabBoard002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        tabContentModel.SetTabBar("text", IMAGE_SRC_URL, std::nullopt, nullptr, true);
        tabContentModel.SetSelectedMode(SelectedMode::BOARD);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps1: Test Default selected item
     * @tc.expected: The selected item would show bgColor
     */
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::GRAY));
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::BLACK.BlendOpacity(0.0f)));

    /**
     * @tc.steps2: Change selected item
     * @tc.expected: Would change bgColor
     */
    ChangeIndex(1);
    EXPECT_TRUE(CurrentIndex(1));
    EXPECT_TRUE(VerifyBackgroundColor(0, Color::BLACK.BlendOpacity(0.0f)));
    EXPECT_TRUE(VerifyBackgroundColor(1, Color::GRAY));
}

/**
 * @tc.name: TabBarPatternUpdateGradientRegions001
 * @tc.desc: test UpdateGradientRegions
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateGradientRegions001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    SizeF size(5.0f, 5.0f);
    tabBarNode_->GetGeometryNode()->SetFrameSize(size);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);

    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->visibleItemPosition_[0] = { 1.0f, 2.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[2]);

    tabBarPattern_->visibleItemPosition_[2] = { 3.0, 4.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[3]);

    tabBarPattern_->visibleItemPosition_[3] = { 4.0f, 5.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[3]);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern_->scrollMargin_ = 1.0f;

    tabBarPattern_->visibleItemPosition_[0] = { 0.0f, 1.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->visibleItemPosition_[0] = { 1.0f, 2.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[0]);

    tabBarPattern_->visibleItemPosition_[3] = { 3.0f, 4.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_FALSE(tabBarPattern_->gradientRegions_[1]);

    tabBarPattern_->visibleItemPosition_[3] = { 4.0f, 5.0f };
    tabBarPattern_->UpdateGradientRegions();
    EXPECT_TRUE(tabBarPattern_->gradientRegions_[1]);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode001
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetSelectedMode001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->GetSelectedMode(), SelectedMode::INDICATOR);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);

    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator);
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[1], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternSetSelectedMode002
 * @tc.desc: test SetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetSelectedMode002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_EQ(tabBarPattern_->GetSelectedMode(), SelectedMode::INDICATOR);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->selectedModes_.size()), TABCONTENT_NUMBER);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0, true);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->selectedModes_.size()), 5);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1, false);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->selectedModes_.size()), 5);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 10, true);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->selectedModes_.size()), 6);
    EXPECT_EQ(tabBarPattern_->selectedModes_[5], SelectedMode::INDICATOR);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 10, false);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->selectedModes_.size()), 7);
    EXPECT_EQ(tabBarPattern_->selectedModes_[6], SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarPatternSetIndicatorStyle001
 * @tc.desc: test SetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetIndicatorStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->indicatorStyles_.size()), TABCONTENT_NUMBER);

    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0, true);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->indicatorStyles_.size()), 5);

    tabBarPattern_->SetIndicatorStyle(indicator, 1, false);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->indicatorStyles_.size()), 5);

    tabBarPattern_->SetIndicatorStyle(indicator, 10, true);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->indicatorStyles_.size()), 6);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[5], indicator);

    tabBarPattern_->SetIndicatorStyle(indicator, 10, false);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->indicatorStyles_.size()), 7);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[6], indicator);
}

/**
 * @tc.name: TabBarPatternSetTabBarStyle001
 * @tc.desc: test tab bar SetTabBarStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetTabBarStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarStyles_.size()), TABCONTENT_NUMBER);

    TabBarStyle tabBarStyle = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->SetTabBarStyle(tabBarStyle, 0, true);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], tabBarStyle);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarStyles_.size()), 5);

    tabBarPattern_->SetTabBarStyle(tabBarStyle, 1, false);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[1], tabBarStyle);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarStyles_.size()), 5);

    tabBarPattern_->SetTabBarStyle(tabBarStyle, 10, true);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarStyles_.size()), 6);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[5], tabBarStyle);

    tabBarPattern_->SetTabBarStyle(tabBarStyle, 10, false);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarStyles_.size()), 7);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[6], tabBarStyle);
}

/**
 * @tc.name: TabBarPatternSetBottomTabBarStyle001
 * @tc.desc: test tab bar SetBottomTabBarStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetBottomTabBarStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->bottomTabBarStyles_.size()), TABCONTENT_NUMBER);

    BottomTabBarStyle bottomTabBarStyle;
    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 0, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->bottomTabBarStyles_.size()), 5);

    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 1, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->bottomTabBarStyles_.size()), 5);

    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 10, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->bottomTabBarStyles_.size()), 6);

    tabBarPattern_->SetBottomTabBarStyle(bottomTabBarStyle, 10, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->bottomTabBarStyles_.size()), 7);
}

/**
 * @tc.name: TabBarPatternSetIconStyle001
 * @tc.desc: test tab bar SetIconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetIconStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->iconStyles_.size()), TABCONTENT_NUMBER);

    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->iconStyles_.size()), 5);

    tabBarPattern_->SetIconStyle(iconStyle, 1, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->iconStyles_.size()), 5);

    tabBarPattern_->SetIconStyle(iconStyle, 10, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->iconStyles_.size()), 6);

    tabBarPattern_->SetIconStyle(iconStyle, 10, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->iconStyles_.size()), 7);
}

/**
 * @tc.name: TabBarPatternSetSymbol001
 * @tc.desc: test tab bar SetSymbol
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetSymbol001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->symbolArray_.size()), TABCONTENT_NUMBER);

    TabBarSymbol symbol;
    tabBarPattern_->SetSymbol(symbol, 0, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->symbolArray_.size()), 5);

    tabBarPattern_->SetSymbol(symbol, 1, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->symbolArray_.size()), 5);

    tabBarPattern_->SetSymbol(symbol, 10, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->symbolArray_.size()), 6);

    tabBarPattern_->SetSymbol(symbol, 10, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->symbolArray_.size()), 7);
}

/**
 * @tc.name: TabBarPatternAddTabBarItemId001
 * @tc.desc: test tab bar AddTabBarItemId
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternAddTabBarItemId001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarItemIds_.size()), TABCONTENT_NUMBER);

    int32_t tabBarItemId = 1;
    tabBarPattern_->AddTabBarItemId(tabBarItemId, 0, true);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarItemIds_.size()), 5);
    EXPECT_EQ(tabBarPattern_->tabBarItemIds_[0], tabBarItemId);

    tabBarItemId = 2;
    tabBarPattern_->AddTabBarItemId(tabBarItemId, 1, false);
    EXPECT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarItemIds_.size()), 5);
    EXPECT_EQ(tabBarPattern_->tabBarItemIds_[1], tabBarItemId);

    tabBarItemId = 3;
    tabBarPattern_->AddTabBarItemId(tabBarItemId, 10, true);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarItemIds_.size()), 6);
    EXPECT_EQ(tabBarPattern_->tabBarItemIds_[5], tabBarItemId);

    tabBarItemId = 4;
    tabBarPattern_->AddTabBarItemId(tabBarItemId, 10, false);
    ASSERT_EQ(static_cast<int32_t>(tabBarPattern_->tabBarItemIds_.size()), 7);
    EXPECT_EQ(tabBarPattern_->tabBarItemIds_[6], tabBarItemId);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator001
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateIndicator001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::NOSTYLE);
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::BOTTOMTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::VERTICAL);
    tabBarPattern_->tabBarType_[0] = TabBarParamType::CUSTOM_BUILDER;
    tabBarPattern_->UpdateIndicator(0);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    EXPECT_EQ(tabBarLayoutProperty_->GetAxisValue(), Axis::HORIZONTAL);
    tabBarPattern_->tabBarType_[0] = TabBarParamType::NORMAL;
    tabBarPattern_->UpdateIndicator(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->UpdateIndicator(0);
    FlushUITasks();
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation001
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayPressAnimation001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    IndicatorStyle indicatorStyle;
    tabBarPattern_->SetIndicatorStyle(indicatorStyle, 0);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetSelectedMode(SelectedMode::BOARD, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::BOARD);
    tabBarPattern_->PlayPressAnimation(0, Color::TRANSPARENT, AnimationType::PRESS);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternGetIndicatorRect001
 * @tc.desc: test GetIndicatorRect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetIndicatorRect001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentsWithBuilder(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto rect = tabBarLayoutProperty_->GetIndicatorRect(0);
    EXPECT_EQ(rect.GetX(), 85.f);
}

/**
 * @tc.name: TabBarPatternGetSelectedMode001
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetSelectedMode001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->indicator_ = 1;
    auto mode = tabBarPattern_->GetSelectedMode();
    EXPECT_EQ(mode, SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish001
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish002
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. call MaskAnimationFinish function.
     * @tc.expected: step2. expect The function is run ok.
     */
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternChangeMask001
 * @tc.desc: test ChangeMask
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternChangeMask001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. call ChangeMask function.
     * @tc.expected: step2. expect The function is run ok.
     */
    auto tabBarGeometryNode = tabBarNode_->GetGeometryNode();
    auto tabBarOffset = tabBarGeometryNode->GetMarginFrameOffset();
    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 1.0f, TEST_MASK_MIDDLE_RADIUS_RATIO, true);
    tabBarPattern_->ChangeMask(TEST_TAB_BAR_INDEX, 1.0f, tabBarOffset, 0.99f, TEST_MASK_MIDDLE_RADIUS_RATIO, false);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);

    auto selectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT;
    auto selectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(selectedmaskPosition));
    auto selectedImageNode = AceType::DynamicCast<FrameNode>(selectedMaskNode->GetChildren().front());
    auto selectedImageRenderContext = selectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(selectedImageRenderContext->GetOpacity().value(), 1.0f);
    auto unselectedmaskPosition = tabBarNode_->GetChildren().size() - TEST_UNSELECTED_MASK_COUNT;
    auto unselectedMaskNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(unselectedmaskPosition));
    auto unSelectedImageNode = AceType::DynamicCast<FrameNode>(unselectedMaskNode->GetChildren().front());
    auto unSelectedImageRenderContext = unSelectedImageNode->GetRenderContext();
    EXPECT_DOUBLE_EQ(unSelectedImageRenderContext->GetOpacity().value(), 0.99f);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor001
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateImageColor001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build two bottom style tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. call UpdateImageColor function.
     * @tc.expected: step2. expect The function is run ok.
     */
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabsModelSetTabBarWidth001
 * @tc.desc: test SetTabBarWidth
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabsModelSetTabBarWidth001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function SetTabBarWidth and SetTabBarHeight When tabBarWidth and tabBarHeight change.
     * @tc.expected: Related functions run ok.
     */
    TabsModelNG model = CreateTabs();
    Dimension tabBarWidth = 10.0_vp;
    Dimension tabBarHeight = 3.0_vp;
    for (int i = 0; i <= 1; i++) {
        model.SetTabBarWidth(tabBarWidth);
        model.SetTabBarHeight(tabBarHeight);
        tabBarWidth = -1.0_vp;
        tabBarHeight = -1.0_vp;
    }
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: TabBarPatternInitClick001
 * @tc.desc: test InitClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitClick001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    auto info = GestureEvent();
    tabBarPattern_->clickEvents_.begin()->second->callback_(info);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternFocusIndexChange001
 * @tc.desc: test FocusIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternFocusIndexChange001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    int32_t index = 1;
    std::optional<int32_t> animation_test = 1;

    /**
     * @tc.steps: step2. Test function FocusIndexChange.
     * @tc.expected: Related functions run ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->FocusIndexChange(index);
        tabBarPattern_->animationDuration_ = animation_test;
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternFocusIndexChange002
 * @tc.desc: test FocusIndexChange jumpIndex_
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternFocusIndexChange002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. FocusIndexChange index.
     * @tc.expected: test jumpIndex_.
     */
    for (int index = 0; index <= TABCONTENT_NUMBER; index++) {
        tabBarPattern_->FocusIndexChange(index);
        EXPECT_EQ(tabBarPattern_->jumpIndex_, index);
    }
}

/**
 * @tc.name: TabBarPatternFocusIndexChange003
 * @tc.desc: test FocusIndexChange targetIndex_
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternFocusIndexChange003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto itemWidth = 200.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }
    tabBarNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
    EXPECT_TRUE(tabBarPattern_->CanScroll());

    /**
     * @tc.steps: step2. FocusIndexChange index.
     * @tc.expected: test targetIndex_.
     */
    tabBarPattern_->animationDuration_ = 300;
    for (int index = 0; index <= TABCONTENT_NUMBER; index++) {
        tabBarPattern_->FocusIndexChange(index);
        EXPECT_EQ(tabBarPattern_->targetIndex_, index);
    }
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish003
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternMaskAnimationFinish003, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function MaskAnimationFinish.
     * @tc.expected: Related functions run ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t selectedIndex = -1;
    bool isSelected = true;
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, selectedIndex, isSelected);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarDistributedTest001
 * @tc.desc: Test the distributed capability of TabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarDistributedTest001, TestSize.Level1)
{
    TabsItemDivider divider;
    TabsModelNG model = CreateTabs();
    model.SetDivider(divider);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    restoreInfo_ = R"({"Index":1})";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
    restoreInfo_ = "invalid_json_string";
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 1);
}

/**
 * @tc.name: TabBarPatternPlayPressAnimation002
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayPressAnimation002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    int32_t index = 1;
    auto pressColor = Color();
    pressColor.SetValue(1);
    auto animationType = AnimationType::HOVERTOPRESS;
    IndicatorStyle indicatorStyle1;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    indicatorStyle2.color = Color::RED;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1, indicatorStyle2 };

    /**
     * @tc.steps: step2. Test function PlayPressAnimation.
     * @tc.expected: Related functions run ok.
     */
    for (int32_t i = 0; i <= 1; i++) {
        tabBarPattern_->PlayPressAnimation(index, pressColor, animationType);
        animationType = AnimationType::HOVER;
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect001
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
    ASSERT_NE(frameNode_, nullptr);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight001
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateTextColorAndFontWeight001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabContents(1);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, TabBarParamType::CUSTOM_BUILDER));
    ASSERT_TRUE(pr.second);
    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight and UpdateImageColor.
     * @tc.expected: Related functions run ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight002
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateTextColorAndFontWeight002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabContents(1);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    for (int i = 0; i <= 1; i++) {
        AceType::DynamicCast<FrameNode>(
            AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
            ->layoutProperty_ = AceType::MakeRefPtr<TextLayoutProperty>();
        ASSERT_NE(AceType::DynamicCast<FrameNode>(
                      AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(i))->GetChildren().back())
                      ->layoutProperty_,
            nullptr);
    }

    /**
     * @tc.steps: step2. Test function UpdateTextColorAndFontWeight.
     * @tc.expected: Related function runs ok.
     */
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
}

/**
 * @tc.name: TabBarPatternInitScrollable002
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollable->SetAxis(Axis::HORIZONTAL);
    auto scrollableEvent = AceType::MakeRefPtr<ScrollableEvent>(Axis::HORIZONTAL);
    scrollableEvent->SetAxis(Axis::VERTICAL);
    scrollableEvent->SetScrollable(scrollable);
    tabBarPattern_->scrollableEvent_ = scrollableEvent;

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        swiperController_->GetTabBarFinishCallback()();
        scrollableEvent->SetScrollable(nullptr);
        tabBarPattern_->scrollableEvent_ = scrollableEvent;
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternInitScrollable003
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->visibleItemPosition_[0] = { -1.0f, -1.0f };
    }
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_START);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    int32_t source = SCROLL_FROM_UPDATE;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitScrollable(gestureHub);
        scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
        scrollable->callback_(0.1, source);
        tabBarPattern_->axis_ = Axis::VERTICAL;
        tabBarPattern_->visibleItemPosition_.clear();
        tabBarPattern_->visibleItemPosition_[0] = { -1.0f, -1.0f };
        tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 2.0f));
    }
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation001
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayMaskAnimation001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

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
    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternPlayTabBarTranslateAnimation001
 * @tc.desc: test PlayTabBarTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayTabBarTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function PlayTabBarTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    AnimationOption option = AnimationOption();
    float targetOffset = 0.3f;
    tabBarPattern_->PlayTabBarTranslateAnimation(option, targetOffset);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternPlayIndicatorTranslateAnimation001
 * @tc.desc: test PlayIndicatorTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayIndicatorTranslateAnimation001, TestSize.Level1)
{
    /**
     * @tc.steps: step2. Test function PlayIndicatorTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    AnimationOption option = AnimationOption();
    RectF originalPaintRect = RectF(0.1f, 0.0f, 0.2f, 0.0f);
    RectF targetPaintRect = RectF(0.3f, 0.0f, 0.2f, 0.0f);
    float targetOffset = 0.3f;
    tabBarPattern_->PlayIndicatorTranslateAnimation(option, originalPaintRect, targetPaintRect, targetOffset);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);

    targetOffset = -0.2f;
    tabBarPattern_->PlayIndicatorTranslateAnimation(option, originalPaintRect, targetPaintRect, targetOffset);
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect002
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternTriggerTranslateAnimation001
 * @tc.desc: test TriggerTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternTriggerTranslateAnimation001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    int32_t currentIndex = 0;
    int32_t targetIndex = 1;
    tabBarPattern_->scrollEffect_ = AceType::MakeRefPtr<ScrollEdgeEffect>();
    tabBarNode_->GetGeometryNode()->SetFrameSize(SizeF(1.0f, 1.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex - 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));
    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(targetIndex + 1))
        ->GetGeometryNode()
        ->SetFrameSize(SizeF(0.0f, 0.0f));

    /**
     * @tc.steps: step2. Test function TriggerTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->changeByClick_ = true;
    tabBarPattern_->TriggerTranslateAnimation(currentIndex, targetIndex);
    EXPECT_FALSE(tabBarPattern_->translateAnimationIsRunning_);
}

/**
 * @tc.name: TabsModelSetOnTabBarClick001
 * @tc.desc: Tabs SetOnTabBarClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabsModelSetOnTabBarClick001, TestSize.Level1)
{
    /**
     * @tc.steps: steps2. SetOnTabBarClick
     * @tc.expected: steps2. Check the result of SetOnTabBarClick
     */
    TabsModelNG model = CreateTabs();
    model.SetOnTabBarClick([](const BaseEventInfo* info) {});
    model.SetOnTabBarClick([](const BaseEventInfo* info) {});
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
    EXPECT_NE(pattern_->onTabBarClickEvent_, nullptr);
}

/**
 * @tc.name: TabBarPatternInitScrollable004
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                tabBarPattern_->InitScrollable(gestureHub);
                ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
                auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
                scrollable->callback_(0.1, SCROLL_FROM_NONE);
                tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
                tabBarPattern_->axis_ = Axis::HORIZONTAL;
            }
            tabBarPattern_->axis_ = Axis::VERTICAL;
            tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
            tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }
        tabBarPattern_->visibleItemPosition_[0] = { -1.0f, -1.0f };
    }
    tabBarPattern_->axis_ = Axis::VERTICAL;
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_AXIS);
    scrollable->callback_(1.1, SCROLL_FROM_AXIS);
    EXPECT_EQ(tabBarPattern_->GetTabBarStyle(), TabBarStyle::BOTTOMTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternGetIndicatorStyle001
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetIndicatorStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyleWithBuilder(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyleWithBuilder(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. GetIndicatorStyle
     * @tc.expected: steps2. Check the result of GetIndicatorStyle
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->swiperStartIndex_ = 0;
    IndicatorStyle indicator;
    tabBarPattern_->SetIndicatorStyle(indicator, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator);
    IndicatorStyle indicator1;
    indicator1.width = -1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    auto firstRect = tabBarLayoutProperty_->GetIndicatorRect(0);
    EXPECT_EQ(firstRect.GetY(), 33.f);
    auto secondRect = tabBarLayoutProperty_->GetIndicatorRect(1);
    EXPECT_EQ(secondRect.GetY(), 33.f);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->turnPageRate_ = -0.9f;
    IndicatorStyle indicator2;
    OffsetF indicatorOffset;
    tabBarPattern_->GetIndicatorStyle(indicator2, indicatorOffset, firstRect);
    EXPECT_EQ(indicatorOffset.GetY(), 33.f);
    indicator1.width = 1.0_vp;
    tabBarPattern_->SetIndicatorStyle(indicator1, 1);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[1], indicator1);
    tabBarPattern_->GetIndicatorStyle(indicator2, indicatorOffset, firstRect);
    tabBarPattern_->turnPageRate_ = 0.9f;
    IndicatorStyle indicator3;
    tabBarPattern_->GetIndicatorStyle(indicator3, indicatorOffset, firstRect);
    tabBarPattern_->SetIndicatorStyle(indicator3, 0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_[0], indicator3);
}

/**
 * @tc.name: TabBarPatternCheckSwiperDisable001
 * @tc.desc: test CheckSwiperDisable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternCheckSwiperDisable001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. CheckSwiperDisable
     * @tc.expected: steps2. Check the result of CheckSwiperDisable
     */
    EXPECT_EQ(tabBarPattern_->CheckSwiperDisable(), false);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator001
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 0);
    EXPECT_EQ(tabBarPattern_->selectedModes_[0], SelectedMode::INDICATOR);
    tabBarPattern_->SetSelectedMode(SelectedMode::INDICATOR, 1);
    EXPECT_EQ(tabBarPattern_->selectedModes_[1], SelectedMode::INDICATOR);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(2.0f);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-2.0f);
    EXPECT_EQ(tabBarPattern_->turnPageRate_, 0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.9f);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarOnAttachToMainTree001.
 * @tc.desc: Test the OnAttachToMainTree function in the TabContentNode class.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarOnAttachToMainTree001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    TabContentModelNG tabContentModel = CreateTabContent();
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    tabContentFrameNode->OnAttachToMainTree(true);
    EXPECT_FALSE(tabContentFrameNode->useOffscreenProcess_);

    auto pipeline = PipelineContext::GetCurrentContext();
    tabContentFrameNode->OnDetachFromMainTree(true, AceType::RawPtr(pipeline));
    EXPECT_TRUE(CurrentIndex(0));
}

/**
 * @tc.name: TabBarPatternInitScrollable005
 * @tc.desc: test InitScrollable
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitScrollable005, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);

    /**
     * @tc.steps: step2. Test function InitScrollable in different conditons.
     * @tc.expected: Related function is called.
     */

    tabBarPattern_->InitScrollable(gestureHub);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    ASSERT_NE(tabBarPattern_->scrollableEvent_, nullptr);
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    tabBarPattern_->scrollableEvent_->scrollable_ = nullptr;
    scrollable->callback_(0.1, SCROLL_FROM_NONE);
    EXPECT_EQ(tabBarPattern_->scrollableEvent_->scrollable_, nullptr);
}

/*
 * @tc.name: TabBarPatternCalculateSelectedIndex001
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternCalculateSelectedIndex001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    SizeF size(4.0f, 4.0f);
    tabBarNode_->GetGeometryNode()->SetFrameSize(size);
    auto info = MouseInfo();
    Offset s1(0.1, 1.1);
    info.SetLocalLocation(s1);

    /**
     * @tc.steps: step2. Test function HandleMouseEvent.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->visibleItemPosition_.clear();
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), -1);

    tabBarPattern_->visibleItemPosition_[0] = { 0.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->visibleItemPosition_[2] = { 2.0f, 3.0f };
    tabBarPattern_->visibleItemPosition_[3] = { 3.0f, 4.0f };
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 0);
    tabBarPattern_->isRTL_ = true;
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 3);
    tabBarLayoutProperty_->UpdateAxis(Axis::VERTICAL);
    EXPECT_EQ(tabBarPattern_->CalculateSelectedIndex(info.GetLocalLocation()), 1);
}

/**
 * @tc.name: TabBarPatternIsAtBottom001
 * @tc.desc: test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternIsAtBottom001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function IsAtBottom001.
     * @tc.expected: Related functions run ok.
     */
    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->IsAtBottom();
    EXPECT_FALSE(tabBarPattern_->IsAtBottom());
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator002
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::NOSTYLE;
    auto tabBarStyles2 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 2;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = -1;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 0);
}

/**
 * @tc.name: TabBarPatternApplyTurnPageRateToIndicator003
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternApplyTurnPageRateToIndicator003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabsDone(model);

    /**
     * @tc.steps: steps2. ApplyTurnPageRateToIndicator
     * @tc.expected: steps2. Check the result of ApplyTurnPageRateToIndicator
     */
    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles1 = TabBarStyle::SUBTABBATSTYLE;
    auto tabBarStyles2 = TabBarStyle::NOSTYLE;
    auto selectedMode1 = SelectedMode::INDICATOR;
    auto selectedMode2 = SelectedMode::BOARD;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles1);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode1);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 1);
    tabBarPattern_->selectedModes_.push_back(selectedMode2);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.0f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, 0);

    /**
     * @tc.steps: steps3. ApplyTurnPageRateToIndicator
     * @tc.expected: steps3. Check the result of ApplyTurnPageRateToIndicator
     */

    tabBarPattern_->swiperStartIndex_ = 0;
    auto tabBarStyles3 = TabBarStyle::SUBTABBATSTYLE;
    auto selectedMode3 = SelectedMode::INDICATOR;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyles3);
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->selectedModes_.push_back(selectedMode3);
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.7f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
    tabBarPattern_->swiperStartIndex_ = 0;
    tabBarPattern_->turnPageRate_ = 0.5f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(-0.5f);
    EXPECT_EQ(tabBarPattern_->swiperStartIndex_, -1);
}

/**
 * @tc.name: TabBarPatternUpdateIndicator002
 * @tc.desc: test UpdateIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateIndicator002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetFadingEdge(true);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    EXPECT_TRUE(tabBarPaintProperty_->GetFadingEdgeValue());

    /**
     * @tc.steps: steps2. UpdateIndicator
     * @tc.expected: steps2. Check the result of UpdateIndicator
     */
    tabBarPattern_->indicator_ = 0;
    auto tabBarStyle1 = TabBarStyle::NOSTYLE;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_.push_back(tabBarStyle1);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE, 0);
    tabBarPattern_->UpdateIndicator(0);
    tabBarPattern_->isTouchingSwiper_ = false;
    tabBarPattern_->UpdateIndicator(0);
}

/**
 * @tc.name: TabBarPatternOnRestoreInfo001
 * @tc.desc: Test the TabBarPatternOnRestoreInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternOnRestoreInfo001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. Set Indicator.
     * @tc.expected: Function ProvideRestoreInfo is called.
     */
    tabBarPattern_->UpdateIndicator(0);
    std::string ret = tabBarPattern_->ProvideRestoreInfo();
    EXPECT_TRUE(ret == R"({"Index":0})");

    /**
     * @tc.steps: step3. Function OnRestoreInfo is called.
     * @tc.expected: Passing invalid & valid JSON format.
     */
    std::string restoreInfo_ = R"({"Index":0})";
    auto info = JsonUtil::ParseJsonString(restoreInfo_);
    auto jsonIsOn = info->GetValue("Index");
    tabBarPattern_->SetTabBarStyle(TabBarStyle::NOSTYLE, 0);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    tabBarPattern_->SetAnimationDuration(1);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    swiperController_ = nullptr;
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
    auto columnNode1 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode1->MountToParent(tabBarNode_);
    auto columnNode2 =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    columnNode2->MountToParent(tabBarNode_);
    pattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarLayoutProperty_->GetIndicator().value_or(0), 0);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect003
 * @tc.desc: test SetEdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);

    /**
     * @tc.steps: step2. Test function SetEdgeEffect.
     * @tc.expected: Related function runs ok.
     */
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->SetEdgeEffect(gestureHub);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: Divider001
 * @tc.desc: Test Divider001, has style when items size more than 1
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, Divider001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has items
     * @tc.expected: Has divider style
     */
    TabsItemDivider divider;
    divider.color = Color::RED;
    divider.strokeWidth = Dimension(10.f);
    TabsModelNG model = CreateTabs();
    model.SetDivider(divider);
    CreateTabContents(2);
    CreateTabsDone(model);
    EXPECT_EQ(dividerRenderProperty_->GetDividerColor(), Color::RED);
    auto dividerLayoutProperty = dividerNode_->GetLayoutProperty<DividerLayoutProperty>();
    EXPECT_EQ(dividerLayoutProperty->GetStrokeWidth(), Dimension(10.f));
}

/**
 * @tc.name: TabBarBlurStyle001
 * @tc.desc: test TabBarBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarBlurStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_THICK;
    model.SetBarBackgroundBlurStyle(styleOption);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The blurstyle is COMPONENT_THICK.
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->blurStyle, BlurStyle::COMPONENT_THICK);
}

/**
 * @tc.name: TabBarBlurStyle002
 * @tc.desc: test BarBlurStyleOption
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarBlurStyle002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_THIRTEEN));
    BlurStyleOption styleOption;
    styleOption.colorMode = ThemeColorMode::LIGHT;
    styleOption.scale = 0.5;
    model.SetBarBackgroundBlurStyle(styleOption);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2. update blurstyle
     * @tc.expected: step2. expect The colorMode is LIGHT and the scale is 0.5.
     */
    auto tabBarRenderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->colorMode, ThemeColorMode::LIGHT);
    EXPECT_EQ(tabBarRenderContext->GetBackBlurStyle()->scale, 0.5);
}

/**
 * @tc.name: SetTabBarStyle001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, SetTabBarStyle001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();

    /**
     * @tc.steps: step1. step1.SetTabBarStyle Set TabBarStyle to TabBarStyle: SUBTABBATSTYLE
     * @tc.steps: sCall the GetTabBarStyle interface under the TabContentModelNG
     * @tc.expected: Equal to TabBarStyle: SUBTABBATSTYLE.
     */
    const std::string text_test = "text_test";
    tabContentPattern->SetTabBar(text_test, "", std::nullopt, nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
    tabContentPattern->SetTabBar(text_test, "", std::nullopt, nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);

    tabContentPattern->SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(tabContentPattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

/**
 * @tc.name: TabBarPatternProvideRestoreInfo003
 * @tc.desc: test Measure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternProvideRestoreInfo003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    TabsItemDivider divider;
    model.SetDivider(divider);
    CreateTabsDone(model);

    /**
     * @tc.steps: step1.1. Constructing TabBarPattern class pointers
     * @tc.expected:tabBarPattern_->ProvideRestoreInfo() not null.
     */
    EXPECT_TRUE(tabBarPattern_->ProvideRestoreInfo() != "");
}

/**
 * @tc.name: TabContentModelAddTabBarItem001
 * @tc.desc: test AddTabBarItem
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabContentModelAddTabBarItem001, TestSize.Level1)
{
    const std::string text_test = "text_test";
    TabContentModelNG tabContentModel;
    tabContentModel.Create();
    auto tabContentFrameNode = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern = tabContentFrameNode->GetPattern<TabContentPattern>();
    TabsModelNG tabsModel;
    tabsModel.Create(BarPosition::START, 1, nullptr, nullptr);
    tabContentFrameNode->GetTabBarItemId();
    tabContentFrameNode->MountToParent(swiperNode_);
    tabContentPattern->SetTabBar(text_test, "", std::nullopt, nullptr);
    EXPECT_EQ(tabContentPattern->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode, DEFAULT_NODE_SLOT, true);

    TabContentModelNG tabContentModel2;
    tabContentModel2.Create();
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(ViewStackProcessor::GetInstance()->Finish());
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    tabContentFrameNode2->MountToParent(swiperNode_);
    tabContentPattern2->SetTabBar(text_test, "", std::nullopt, nullptr);
    EXPECT_EQ(tabContentPattern2->GetTabBarParam().GetText(), text_test);
    tabContentModel.AddTabBarItem(tabContentFrameNode2, DEFAULT_NODE_SLOT, true);
}

/**
 * @tc.name: TabBarPatternInitLongPressEvent001
 * @tc.desc: test InitLongPressEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitLongPressEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->longPressEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitLongPressEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitLongPressEvent(gestureHub);
        tabBarPattern_->longPressEvent_ = AceType::MakeRefPtr<LongPressEvent>([](GestureEvent&) {});
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternInitDragEvent001
 * @tc.desc: test InitDragEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternInitDragEvent001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->dragEvent_ = nullptr;

    /**
     * @tc.steps: step2. Test function InitDragEvent.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->InitDragEvent(gestureHub);
        tabBarPattern_->dragEvent_ = AceType::MakeRefPtr<DragEvent>(nullptr, [](GestureEvent&) {}, nullptr, nullptr);
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternUpdateSymbolStats001
 * @tc.desc: Test UpdateSymbolStats method
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateSymbolStats001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    TabBarSymbol tabBarSymbol;
    bool onApplyCalled = false;
    std::string modeValue = "";
    tabBarSymbol.selectedFlag = true;
    tabBarSymbol.onApply = [&onApplyCalled, &modeValue](WeakPtr<NG::FrameNode> node, std::string mode) {
        onApplyCalled = true;
        modeValue = mode;
    };
    TabBarSymbol tabBarSymbol1;
    bool onApplyCalled1 = false;
    std::string modeValue1 = "";
    tabBarSymbol1.onApply = [&onApplyCalled1, &modeValue1](WeakPtr<NG::FrameNode> node, std::string mode) {
        onApplyCalled1 = true;
        modeValue1 = mode;
    };
    tabBarPattern_->symbolArray_ = { tabBarSymbol, tabBarSymbol1 };
    CreateTabContents(2);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto tabContentFrameNode2 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 1));
    ASSERT_NE(tabContentFrameNode2, nullptr);
    auto tabContentPattern1 = tabContentFrameNode1->GetPattern<TabContentPattern>();
    auto tabContentPattern2 = tabContentFrameNode2->GetPattern<TabContentPattern>();
    tabContentPattern1->SetTabBar("", "", tabBarSymbol, nullptr);
    tabContentPattern2->SetTabBar("", "", tabBarSymbol1, nullptr);
    CreateTabsDone(model);

    int32_t index = 0;
    int32_t preIndex = 1;
    tabBarPattern_->UpdateSymbolStats(index, preIndex);
    auto columnNode1 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode1->GetTabBarItemId());
    auto symbolNode1 = GetChildFrameNode(columnNode1, 0);
    auto symbolProperty1 = symbolNode1->GetLayoutProperty<TextLayoutProperty>();
    auto columnNode2 = FrameNode::GetFrameNode(V2::COLUMN_ETS_TAG, tabContentFrameNode2->GetTabBarItemId());
    auto symbolNode2 = GetChildFrameNode(columnNode2, 0);
    auto symbolProperty2 = symbolNode2->GetLayoutProperty<TextLayoutProperty>();
    auto pipeline = frameNode_->GetContext();
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    auto defaultColorOn = tabTheme->GetBottomTabSymbolOn();
    auto defaultColorOff = tabTheme->GetBottomTabSymbolOff();
    EXPECT_EQ(symbolProperty1->GetSymbolColorListValue({})[0], defaultColorOn);
    EXPECT_EQ(symbolProperty2->GetSymbolColorListValue({})[0], defaultColorOff);
    EXPECT_TRUE(onApplyCalled);
    EXPECT_TRUE(onApplyCalled1);
    EXPECT_EQ(modeValue, "selected");
    EXPECT_EQ(modeValue1, "normal");
}

/**
 * @tc.name: TabBarPatternUpdateSymbolEffect001
 * @tc.desc: Test UpdateSymbolEffect method
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternUpdateSymbolEffect001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    TabBarSymbol tabBarSymbol;
    tabBarPattern_->symbolArray_ = { tabBarSymbol };
    CreateTabContents(1);
    auto tabContentFrameNode1 = AceType::DynamicCast<TabContentNode>(GetChildFrameNode(swiperNode_, 0));
    ASSERT_NE(tabContentFrameNode1, nullptr);
    auto tabContentPattern1 = tabContentFrameNode1->GetPattern<TabContentPattern>();
    tabContentPattern1->SetTabBar("", "", tabBarSymbol, nullptr);
    CreateTabsDone(model);

    tabBarPattern_->UpdateSymbolEffect(0);
    auto columnNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    auto symbolNode = AceType::DynamicCast<FrameNode>(columnNode->GetChildren().front());
    auto symbolLayoutProperty = symbolNode->GetLayoutProperty<TextLayoutProperty>();
    auto updatedOptions = symbolLayoutProperty->GetSymbolEffectOptionsValue(SymbolEffectOptions());
    EXPECT_FALSE(updatedOptions.GetIsTxtActive());
}

/**
 * @tc.name: TabBarPatternGetSelectedMode002
 * @tc.desc: test GetSelectedMode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternGetSelectedMode002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    tabBarPattern_->indicator_ = 3;
    EXPECT_EQ(tabBarPattern_->GetSelectedMode(), SelectedMode::INDICATOR);
}

/**
 * @tc.name: TabBarPatternPlayIndicatorTranslateAnimation002
 * @tc.desc: Test translateWidth prop callback is called in NearZero(indicatorEndPos_ - indicatorStartPos_) condition.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayIndicatorTranslateAnimation002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->indicatorAnimationIsRunning_ = false;
    AnimationOption option = AnimationOption();
    option.SetDuration(300);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f));
    option.SetFillMode(FillMode::FORWARDS);
    RectF originalPaintRect(10.0f, 10.0f, 100.0f, 20.0f);
    RectF targetPaintRect(10.0f, 10.0f, 100.0f, 20.0f);
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->PlayIndicatorTranslateAnimation(option, originalPaintRect, targetPaintRect, 0.0f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->indicatorAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FLOAT_EQ(tabBarPattern_->indicatorStartPos_, originalPaintRect.Width());
    EXPECT_FLOAT_EQ(tabBarPattern_->indicatorEndPos_, targetPaintRect.Width());
    tabBarPattern_->isAnimating_ = true;
    auto widthProperty =
        AceType::DynamicCast<NodeAnimatablePropertyFloat>(tabBarNode_->GetAnimatablePropertyFloat("translateWidth"));
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);
    EXPECT_NEAR(widthProperty->Get(), tabBarPattern_->indicatorEndPos_, 0.001f);

    auto animatableProperty = AceType::DynamicCast<AnimatablePropertyFloat>(widthProperty->GetProperty());
    auto updateCallback = animatableProperty->GetUpdateCallback();
    tabBarPattern_->currentIndicatorOffset_ = 10.0f;
    ASSERT_NE(updateCallback, nullptr);
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->currentIndicatorOffset_, 10.0f, 0.001f);

    tabBarPattern_->isAnimating_ = false;
    tabBarPattern_->indicatorEndPos_ = 110.0f;
    tabBarPattern_->indicatorStartPos_ = 120.0f;
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->currentIndicatorOffset_, 10.0f, 0.001f);

    tabBarPattern_->isAnimating_ = true;
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->turnPageRate_, 12.0f, 0.001f);
}

/**
 * @tc.name: TabBarPatternPlayIndicatorTranslateAnimation003
 * @tc.desc: Test indicatorOffset prop callback is called without NearZero(indicatorEndPos_ - indicatorStartPos_).
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternPlayIndicatorTranslateAnimation003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    tabBarPattern_->indicatorAnimationIsRunning_ = false;
    AnimationOption option = AnimationOption();
    option.SetDuration(300);
    option.SetCurve(AceType::MakeRefPtr<CubicCurve>(0.2f, 0.0f, 0.1f, 1.0f));
    option.SetFillMode(FillMode::FORWARDS);
    RectF originalPaintRect(10.0f, 10.0f, 100.0f, 20.0f);
    RectF targetPaintRect(100.0f, 10.0f, 100.0f, 20.0f);
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->PlayIndicatorTranslateAnimation(option, originalPaintRect, targetPaintRect, 0.0f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->indicatorAnimationIsRunning_);
    auto widthProperty =
        AceType::DynamicCast<NodeAnimatablePropertyFloat>(tabBarNode_->GetAnimatablePropertyFloat("indicatorOffset"));
    EXPECT_NEAR(widthProperty->Get(), 150.0f, 0.001f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->indicatorAnimationIsRunning_);

    auto animatableProperty = AceType::DynamicCast<AnimatablePropertyFloat>(widthProperty->GetProperty());
    auto updateCallback = animatableProperty->GetUpdateCallback();
    ASSERT_NE(updateCallback, nullptr);
    tabBarPattern_->currentIndicatorOffset_ = 10.0f;
    tabBarPattern_->isAnimating_ = true;
    tabBarPattern_->indicatorStartPos_ = 110.0f;
    tabBarPattern_->indicatorEndPos_ = 110.0f;
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->currentIndicatorOffset_, 10.0f, 0.001f);

    tabBarPattern_->isAnimating_ = false;
    tabBarPattern_->indicatorStartPos_ = 110.0f;
    tabBarPattern_->indicatorEndPos_ = 120.0f;
    tabBarPattern_->currentIndicatorOffset_ = 10.0f;
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->currentIndicatorOffset_, 10.0f, 0.001f);

    tabBarPattern_->isAnimating_ = true;
    updateCallback(0.0f);
    EXPECT_NEAR(tabBarPattern_->turnPageRate_, -11.0f, 0.001f);
}

/**
 * @tc.name: TabBarPatternSetEdgeEffect004
 * @tc.desc: test SetEdgeEffect callback
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternSetEdgeEffect004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto eventHub = AceType::MakeRefPtr<EventHub>();
    auto gestureHub = AceType::MakeRefPtr<GestureEventHub>(eventHub);
    tabBarPattern_->scrollEffect_ = nullptr;
    tabBarPattern_->SetEdgeEffect(gestureHub);
    auto scrollEffect = AceType::DynamicCast<ScrollSpringEffect>(tabBarPattern_->scrollEffect_);
    ASSERT_NE(scrollEffect, nullptr);
    auto outBoundaryCallback = scrollEffect->outBoundaryCallback_;
    EXPECT_TRUE(outBoundaryCallback());
    auto currentPositionCallback = scrollEffect->currentPositionCallback_;
    auto leadingCallback = scrollEffect->leadingCallback_;
    auto trailingCallback = scrollEffect->trailingCallback_;
    tabBarPattern_->scrollMargin_ = 10.0f;
    tabBarPattern_->currentDelta_ = 20.0f;
    tabBarPattern_->visibleItemPosition_[0] = { 0, 50 };
    tabBarPattern_->visibleItemPosition_[1] = { 50, 100 };
    tabBarPattern_->visibleItemPosition_[2] = { 100, 150 };
    tabBarPattern_->visibleItemPosition_[3] = { 150, 200 };
    EXPECT_EQ(currentPositionCallback(), 20.0);
    EXPECT_EQ(leadingCallback(), 510.0);
    EXPECT_EQ(trailingCallback(), 10.0);

    tabBarPattern_->isRTL_ = true;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    EXPECT_EQ(currentPositionCallback(), 540.0);

    tabBarPattern_->visibleItemPosition_.clear();
    EXPECT_EQ(currentPositionCallback(), 30.0);
    EXPECT_EQ(leadingCallback(), 710.0);
}

/**
 * @tc.name: TabBarPatternToJsonValue001
 * @tc.desc: Test the ToJsonValue.
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabBarPatternToJsonValue001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    IndicatorStyle style1;
    style1.height = Dimension(10);
    IndicatorStyle style2;
    style2.height = Dimension(15);
    tabBarPattern_->selectedModes_ = { SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern_->indicatorStyles_ = { style1, style2 };
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE, TabBarStyle::SUBTABBATSTYLE };

    tabBarPattern_->ToJsonValue(json, filter);
    EXPECT_FALSE(filter.IsFastFilter());

    filter.AddFilterAttr("id");
    tabBarPattern_->ToJsonValue(json, filter);
    EXPECT_TRUE(filter.IsFastFilter());
}

/**
 * @tc.name: TabsPatternHandleBottomTabBarAnimation001
 * @tc.desc: test HandleBottomTabBarAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarTestNg, TabsPatternHandleBottomTabBarAnimation001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
    CreateTabsDone(model);
    bool changeCallBacked = false;
    auto callback = [&changeCallBacked](int32_t preIndex, int32_t currentIndex) { changeCallBacked = true; };
    bool callIndexChanged = false;
    auto callback1 = [&callIndexChanged](int32_t index) { callIndexChanged = true; };
    pattern_->onChangeEvent_ = std::make_shared<ChangeEventWithPreIndex>(callback);
    pattern_->onIndexChangeEvent_ = std::make_shared<ChangeEvent>(callback1);
    tabBarPattern_->HandleBottomTabBarAnimation(1);
    EXPECT_TRUE(changeCallBacked);
    EXPECT_TRUE(callIndexChanged);

    callIndexChanged = false;
    changeCallBacked = false;
    tabBarPattern_->HandleBottomTabBarAnimation(0);
    EXPECT_FALSE(changeCallBacked);
    EXPECT_FALSE(callIndexChanged);

    callIndexChanged = false;
    changeCallBacked = false;
    pattern_->onChangeEvent_ = nullptr;
    tabBarPattern_->HandleBottomTabBarAnimation(1);
    EXPECT_FALSE(changeCallBacked);
    EXPECT_TRUE(callIndexChanged);

    callIndexChanged = false;
    changeCallBacked = false;
    pattern_->onIndexChangeEvent_ = nullptr;
    tabBarPattern_->HandleBottomTabBarAnimation(1);
    EXPECT_FALSE(changeCallBacked);
    EXPECT_FALSE(callIndexChanged);
}
} // namespace OHOS::Ace::NG
