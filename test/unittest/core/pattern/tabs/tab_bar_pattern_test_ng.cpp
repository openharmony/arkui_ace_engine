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
#include "test/mock/base/mock_task_executor.h"

#include "core/components_ng/pattern/text/text_layout_property.h"

namespace OHOS::Ace::NG {
class TabBarPatternTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    float GetTabBarPosition();
};

void TabBarPatternTestNg::SetUpTestSuite()
{
    TabsTestNg::SetUpTestSuite();
    MockAnimationManager::Enable(true);
    const int32_t ticks = 2;
    MockAnimationManager::GetInstance().SetTicks(ticks);
}

void TabBarPatternTestNg::TearDownTestSuite()
{
    TabsTestNg::TearDownTestSuite();
    MockAnimationManager::GetInstance().Reset();
    MockAnimationManager::Enable(false);
}

float TabBarPatternTestNg::GetTabBarPosition()
{
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    return options.y.ConvertToPx();
}

/**
 * @tc.name: TabBarPatternUpdateBottomTabBarImageColor001
 * @tc.desc: test UpdateBottomTabBarImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateBottomTabBarImageColor001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    std::vector<int32_t> selectedIndexes(1, 1);

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->UpdateBottomTabBarImageColor(selectedIndexes, maskIndex);
        maskIndex = 1;
    }
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateBottomTabBarImageColor002
 * @tc.desc: test UpdateBottomTabBarImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateBottomTabBarImageColor002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    std::vector<int32_t> selectedIndexes(1, 1);

    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->UpdateBottomTabBarImageColor(selectedIndexes, maskIndex);
        maskIndex = 1;
    }
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 1);
}
/**
 * @tc.name: TabBarPatternUpdateBottomTabBarImageColor003
 * @tc.desc: test UpdateBottomTabBarImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateBottomTabBarImageColor003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    std::vector<int32_t> selectedIndexes(1, 1);

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->UpdateBottomTabBarImageColor(selectedIndexes, maskIndex);
        maskIndex = 1;
    }
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 1);
}
/**
 * @tc.name: TabBarPatternUpdateBottomTabBarImageColor004
 * @tc.desc: test UpdateBottomTabBarImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateBottomTabBarImageColor004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
    std::vector<int32_t> selectedIndexes(1, 1);

    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    int32_t maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->UpdateBottomTabBarImageColor(selectedIndexes, maskIndex);
        maskIndex = 1;
    }
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset002
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
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
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode_->Clean(false, false);
    }
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset003
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset003, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
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
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode_->Clean(false, false);
    }
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: TabBarPatternGetBottomTabBarImageSizeAndOffset004
 * @tc.desc: test GetBottomTabBarImageSizeAndOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternGetBottomTabBarImageSizeAndOffset004, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(1);
    CreateTabsDone(model);
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
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
            unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
        maskIndex = 1;
    }

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
            V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    maskIndex = 0;
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            tabBarPattern_->GetBottomTabBarImageSizeAndOffset(selectedIndexes, maskIndex, selectedImageSize,
                unselectedImageSize, originalSelectedMaskOffset, originalUnselectedMaskOffset);
            maskIndex = 1;
        }
        tabBarNode_->Clean(false, false);
    }
    EXPECT_TRUE(frameNode_);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish004
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternMaskAnimationFinish004, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish005
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternMaskAnimationFinish005, TestSize.Level1)
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
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternMaskAnimationFinish006
 * @tc.desc: test MaskAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternMaskAnimationFinish006, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 0, false);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->MaskAnimationFinish(tabBarNode_, 1, true);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight003
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight003, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight004
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight004, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    EXPECT_TRUE(pattern_);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight005
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight005, TestSize.Level1)
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
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight006
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight006, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight007
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight007, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight008
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight008, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight009
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight009, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight010
 * @tc.desc: test UpdateTextColorAndFontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight010, TestSize.Level1)
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
    LabelStyle labelStyle;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    int32_t index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight011
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight011, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight012
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight012, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight013
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight013, TestSize.Level1)
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
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight014
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight014, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.selectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor002
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateImageColor002, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor003
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateImageColor003, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor004
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateImageColor004, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarPatternUpdateImageColor005
 * @tc.desc: test UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateImageColor005, TestSize.Level1)
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
    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->UpdateImageColor(0);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(0), nullptr);
    tabBarPattern_->UpdateImageColor(1);
    EXPECT_NE(tabBarNode_->GetChildAtIndex(1), nullptr);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
    tabBarPattern_->SetMaskAnimationByCreate(false);
    EXPECT_EQ(tabBarPattern_->IsMaskAnimationByCreate(), false);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight015
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight015, TestSize.Level1)
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
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight016
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight016, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight017
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight017, TestSize.Level1)
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
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight018
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight018, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    labelStyle.unselectedColor = Color::WHITE;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight019
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight019, TestSize.Level1)
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
    LabelStyle labelStyle;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight020
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight020, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight021
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight021, TestSize.Level1)
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
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternUpdateTextColorAndFontWeight022
 * @tc.desc: test UpdateTextColorAndFontWeight and UpdateImageColor
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTextColorAndFontWeight022, TestSize.Level1)
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
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    LabelStyle labelStyle;
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    index = 0;
    tabBarPattern_->UpdateTextColorAndFontWeight(index);
    tabBarPattern_->UpdateImageColor(index);
    EXPECT_EQ(tabBarPattern_->labelStyles_.size(), 1);
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation002
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternPlayMaskAnimation002, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 4);
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation003
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternPlayMaskAnimation003, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.unselectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
    EXPECT_TRUE(tabBarPattern_);
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation004
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternPlayMaskAnimation004, TestSize.Level1)
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
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::WHITE;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 4);
}

/**
 * @tc.name: TabBarPatternPlayMaskAnimation005
 * @tc.desc: test PlayMaskAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternPlayMaskAnimation005, TestSize.Level1)
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
    IconStyle iconStyle;
    tabBarPattern_->SetIconStyle(iconStyle, 0);
    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
    EXPECT_EQ(tabBarPattern_->iconStyles_.size(), 4);
}

/**
 * @tc.name: TabBarPatternStartShowTabBarTest001
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartShowTabBarTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. default translate is 0, test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    MockAnimationManager::GetInstance().Tick();

    /**
     * @tc.steps: step3. Set translate to a value greater than 0, test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext->UpdateTransformTranslate(TranslateOptions(0.0f, 10.0f, 0.0f));
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    EXPECT_LT(GetTabBarPosition(), 10.0f);
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartShowTabBarTest002
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartShowTabBarTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. start hide tab bar, test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_LT(GetTabBarPosition(), size);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest001
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. default translate is 0, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_LT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), -size);

    /**
     * @tc.steps: step3. Translate equals tab bar size, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    MockAnimationManager::GetInstance().Tick();
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest002
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. default translate is 0, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), size);
}

/**
 * @tc.name: TabBarPatternStopHideTabBarTest001
 * @tc.desc: test StopHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStopHideTabBarTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Not start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StopHideTabBar();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);

    /**
     * @tc.steps: step3. Start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->StopHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_LT(GetTabBarPosition(), size);
}

/**
 * @tc.name: TabBarPatternUpdateTabBarOffsetTest001
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTabBarOffsetTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Set offset to 10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), -offset1);
    EXPECT_EQ(opacity, 1.0f - offset1 / size);

    /**
     * @tc.steps: step3.Set offset to 26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset2 = Dimension(26.0f, DimensionUnit::VP).ConvertToPx();
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_LT(GetTabBarPosition(), -(offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(GetTabBarPosition(), -size);
    EXPECT_EQ(opacity, 0.0f);

    /**
     * @tc.steps: step4.Set offset to -10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset1);
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(GetTabBarPosition(), -size + offset1);
    EXPECT_EQ(opacity, offset1 / size);

    /**
     * @tc.steps: step5.Set offset to -26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    EXPECT_GT(GetTabBarPosition(), -size + (offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
    EXPECT_EQ(opacity, 1.0f);
}

/**
 * @tc.name: TabBarPatternUpdateTabBarOffsetTest002
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternUpdateTabBarOffsetTest002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Set offset to 10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), offset1);

    /**
     * @tc.steps: step3.Set offset to 26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset2 = Dimension(26.0f, DimensionUnit::VP).ConvertToPx();
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), offset1 + offset2);
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_EQ(GetTabBarPosition(), size);

    /**
     * @tc.steps: step4.Set offset to -10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset1);
    EXPECT_EQ(GetTabBarPosition(), size - offset1);

    /**
     * @tc.steps: step5.Set offset to -26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    EXPECT_LT(GetTabBarPosition(), size - (offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternSetTabBarTranslateAndOpacityTest001
 * @tc.desc: test SetTabBarTranslate and SetTabBarOpacity
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternSetTabBarTranslateAndOpacityTest001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2.Set translate and opacity, test function SetTabBarTranslate and SetTabBarOpacity.
     * @tc.expected: Related function runs ok.
     */
    auto options = TranslateOptions(10.f, 10.f, 1.0f);
    tabBarPattern_->SetTabBarTranslate(options);
    auto opacity = 0.5f;
    tabBarPattern_->SetTabBarOpacity(opacity);
    auto renderContext = tabBarNode_->GetRenderContext();
    EXPECT_EQ(options, renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f)));
    EXPECT_EQ(opacity, renderContext->GetOpacityValue(1.0f));
}

/**
 * @tc.name: SetTabBarTranslate001
 * @tc.desc: test SetTabBarTranslate
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, SetTabBarTranslate001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    /**
     * @tc.steps: step2.Set translate, test function SetTabBarTranslate.
     * @tc.expected: userDefinedTranslateY_ is 10.
     */
    auto options = TranslateOptions(0.0f, 10.f, 0.0f);
    tabBarPattern_->SetTabBarTranslate(options, true);
    EXPECT_EQ(tabBarPattern_->userDefinedTranslateY_, 10.f);
}

/**
 * @tc.name: StartShowTabBar001
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, StartShowTabBar001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext->UpdateTransformTranslate(TranslateOptions(0.0f, 1.0f, 0.0f));
    tabBarPattern_->isTabBarHiding_ = false;
    tabBarPattern_->tabBarState_ = TabBarState::HIDE;
    tabBarPattern_->StartShowTabBar(2000);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    EXPECT_LT(GetTabBarPosition(), 10.0f);
}

/**
 * @tc.name: StartShowTabBar002
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, StartShowTabBar002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext->UpdateTransformTranslate(TranslateOptions(0.0f, 100.0f, 0.0f));
    tabBarPattern_->isTabBarHiding_ = false;
    tabBarPattern_->tabBarState_ = TabBarState::SHOW;
    tabBarPattern_->StartShowTabBar(2000);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    EXPECT_GT(GetTabBarPosition(), 10.0f);
}

/**
 * @tc.name: StartShowTabBar003
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, StartShowTabBar003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext->UpdateTransformTranslate(TranslateOptions(0.0f, 1.0f, 0.0f));
    tabBarPattern_->isTabBarHiding_ = false;
    tabBarPattern_->tabBarState_ = TabBarState::SHOW;
    tabBarPattern_->StartShowTabBar(2000);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    EXPECT_LT(GetTabBarPosition(), 10.0f);
}

/**
 * @tc.name: CancelShowTabBar
 * @tc.desc: test StartShowTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, CancelShowTabBar, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    bool taskExecuted = false;
    tabBarPattern_->showTabBarTask_.Reset([&taskExecuted]() { taskExecuted = true; });
    tabBarPattern_->CancelShowTabBar();
    // MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->showTabBarTask_);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest003
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest004
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->axis_ = Axis::VERTICAL;
    bool taskExecuted = false;
    tabBarPattern_->showTabBarTask_.Reset([&taskExecuted]() { taskExecuted = true; });
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest005
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->axis_ = Axis::VERTICAL;
    bool taskExecuted = false;
    tabBarPattern_->showTabBarTask_.Reset([&taskExecuted]() { taskExecuted = true; });
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest006
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->showTabBarTask_.Reset(nullptr);
    tabBarPattern_->isTabBarShowing_ = true;
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: TabBarPatternStartHideTabBarTest007
 * @tc.desc: test StartHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, TabBarPatternStartHideTabBarTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2. Test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->showTabBarTask_.Reset(nullptr);
    tabBarPattern_->isTabBarShowing_ = false;
    tabBarPattern_->isTabBarHiding_ = true;
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_EQ(GetTabBarPosition(), 0.0f);
}

/**
 * @tc.name: StopHideTabBarTest001
 * @tc.desc: test StopHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, StopHideTabBarTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Not start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StopHideTabBar();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);

    /**
     * @tc.steps: step3. Start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->StopHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_LT(GetTabBarPosition(), size);
}

/**
 * @tc.name: StopHideTabBarTest002
 * @tc.desc: test StopHideTabBar
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, StopHideTabBarTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs(BarPosition::END);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Not start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StopHideTabBar();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);

    /**
     * @tc.steps: step3. Start hide tab bar, test function StopHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    EXPECT_GT(GetTabBarPosition(), 0.0f);
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->StopHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), size);
}

/**
 * @tc.name: UpdateTabBarOffsetTest001
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateTabBarOffsetTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: Test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(GetTabBarPosition(), -offset1);
    EXPECT_EQ(opacity, 1.0f - offset1 / size);
}

/**
 * @tc.name: UpdateTabBarOffsetTest002
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateTabBarOffsetTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->axis_ = Axis::VERTICAL;
    tabBarPattern_->showTabBarTask_.Reset(nullptr);
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_NE(GetTabBarPosition(), -offset1);
    EXPECT_NE(opacity, 1.0f - offset1 / size);
}

/**
 * @tc.name: UpdateTabBarOffsetTest003
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateTabBarOffsetTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    bool taskExecuted = false;
    tabBarPattern_->showTabBarTask_.Reset([&taskExecuted]() { taskExecuted = true; });
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_NE(GetTabBarPosition(), -offset1);
    EXPECT_NE(opacity, 1.0f - offset1 / size);
}

/**
 * @tc.name: UpdateTabBarOffsetTest004
 * @tc.desc: test UpdateTabBarOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateTabBarOffsetTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRectSmallSize(tabBarNode_);

    /**
     * @tc.steps: step2.Test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->showTabBarTask_.Reset(nullptr);
    tabBarPattern_->isTabBarShowing_ = false;
    tabBarPattern_->isTabBarHiding_ = false;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_NE(GetTabBarPosition(), -offset1);
    EXPECT_NE(opacity, 20.0f - offset1 / size);
}

/**
 * @tc.name: HandleMoveAway001
 * @tc.desc: test HandleMoveAway
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleMoveAway001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function HandleMoveAway.
     * @tc.expected: Related function runs ok.
     */
    auto index = 10.0f;
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    tabBarPattern_->isTabBarFocusActive_ = false;
    tabBarPattern_->focusIndicator_ = 20.0f;
    tabBarPattern_->HandleMoveAway(index);
    EXPECT_EQ(GetTabBarPosition(), 0);
}

/**
 * @tc.name: HandleMoveAway002
 * @tc.desc: test HandleMoveAway
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleMoveAway002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function HandleMoveAway.
     * @tc.expected: Related function runs ok.
     */
    auto index = 10.0f;
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->isTabBarFocusActive_ = false;
    tabBarPattern_->focusIndicator_ = 20.0f;
    tabBarPattern_->HandleMoveAway(index);
    EXPECT_EQ(GetTabBarPosition(), 0);
}

/**
 * @tc.name: HandleMoveAway003
 * @tc.desc: test HandleMoveAway
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleMoveAway003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function HandleMoveAway.
     * @tc.expected: Related function runs ok.
     */
    auto index = 10.0f;
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->isTabBarFocusActive_ = true;
    tabBarPattern_->focusIndicator_ = 20.0f;
    tabBarPattern_->HandleMoveAway(index);
    EXPECT_EQ(GetTabBarPosition(), 0);
}

/**
 * @tc.name: HandleMoveAway004
 * @tc.desc: test HandleMoveAway
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleMoveAway004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function HandleMoveAway.
     * @tc.expected: Related function runs ok.
     */
    auto index = 10.0f;
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->isTabBarFocusActive_ = true;
    tabBarPattern_->focusIndicator_ = 10.0f;
    tabBarPattern_->HandleMoveAway(index);
    EXPECT_EQ(GetTabBarPosition(), 0);
}

/**
 * @tc.name: GetNextFocusNode001
 * @tc.desc: test GetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. build tabbar.
     */
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    /**
     * @tc.steps: step2.Test function GetNextFocusNode.
     * @tc.expected: Related function runs ok.
     */
    auto step = FocusStep::RIGHT;
    tabBarPattern_->tabBarStyle_ = TabBarStyle::SUBTABBATSTYLE;
    tabBarPattern_->isTabBarFocusActive_ = true;
    tabBarPattern_->focusIndicator_ = 10.0f;
    tabBarPattern_->GetNextFocusNode(step);
    EXPECT_EQ(tabBarPattern_->focusIndicator_, 10.0f);
}

/**
 * @tc.name: IndicatorOffsetTest001
 * @tc.desc: test currentIndicatorOffset
 * @tc.type: FUNC
 */
 HWTEST_F(TabBarPatternTestNg, IndicatorOffsetTest001, TestSize.Level1)
 {
    TabsModelNG model = CreateTabs();
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        TabContentModelNG tabContentModel = CreateTabContent();
        tabContentModel.SetTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
        tabContentModel.SetTabBar("text", std::nullopt, std::nullopt, nullptr, false);
        ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->StopGetAccessRecording();
    }
    CreateTabsDone(model);

    /**
     * @tc.steps: step2.Set tabBarMode to scrollable and axis to horizontal, init child item width.
     */
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    tabBarLayoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    auto itemWidth = 300.0f;
    for (int32_t index = 0; index < TABCONTENT_NUMBER; index++) {
        auto child = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(index));
        ViewAbstract::SetWidth(AceType::RawPtr(child), CalcLength(itemWidth));
    }

    /**
     * @tc.steps: step3.FlushUITask, check visibleItemPosition_ and currentIndicatorOffset_.
     */
    FlushUITasks(tabBarNode_);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, 0.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 300.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, 600.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, 900.0f);
    EXPECT_EQ(tabBarPattern_->currentIndicatorOffset_, 150.0f);

    /**
     * @tc.steps: step4.Click to 1, check visibleItemPosition_ and currentIndicatorOffset_.
     */
    HandleClick(1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 0);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, -90.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 210.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 2);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, 510.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, 810.0f);
    EXPECT_EQ(tabBarPattern_->currentIndicatorOffset_, 360.0f);

    /**
     * @tc.steps: step5.Click to 2, check visibleItemPosition_ and currentIndicatorOffset_.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    HandleClick(2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(tabBarPattern_->currentIndicatorOffset_, 360.0f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->first, 1);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.startPos, -90.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.begin()->second.endPos, 210.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->first, 3);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.startPos, 510.0f);
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.rbegin()->second.endPos, 810.0f);
    EXPECT_EQ(tabBarPattern_->currentIndicatorOffset_, 360.0f);
}
/**
 * @tc.name: AddTabBarItemCallBack
 * @tc.desc: test AddTabBarItemCallBack
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, AddTabBarItemCallBack, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    EXPECT_NE(tabBarItemNode, nullptr);
    auto columnProperty = tabBarItemNode->GetAccessibilityProperty<AccessibilityProperty>();
    EXPECT_NE(columnProperty, nullptr);
    tabBarPattern_->AddTabBarItemCallBack(tabBarItemNode);

    auto columnNode =
        FrameNode::GetOrCreateFrameNode(V2::COLUMN_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
            []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    EXPECT_NE(columnNode, nullptr);
    auto columnProperty1 = columnNode->GetAccessibilityProperty<AccessibilityProperty>();
    EXPECT_NE(columnProperty1, nullptr);
    tabBarPattern_->AddTabBarItemCallBack(columnNode);
}
/**
 * @tc.name: GetOverScrollInfo
 * @tc.desc: test GetOverScrollInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetOverScrollInfo, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    tabBarPattern_->visibleItemPosition_.clear();
    EXPECT_EQ(tabBarPattern_->visibleItemPosition_.empty(), true);
    auto result = tabBarPattern_->GetOverScrollInfo(tabBarPattern_->GetContentSize());
    EXPECT_EQ(result.first, 0.0f);
    EXPECT_EQ(result.second, 0.0f);
}
/**
 * @tc.name: HandleMouseEvent
 * @tc.desc: test HandleMouseEvent
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleMouseEvent, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    int32_t nodeId = 1;
    for (int i = 0; i <= 2; i++) {
        auto frameNode_ = TabsModelNG::GetOrCreateTabsNode(
        V2::TABS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<TabsPattern>(); });
        tabBarNode_->AddChild(frameNode_);
    }
    MouseInfo mouseInfo;
    mouseInfo.SetAction(MouseAction::WINDOW_LEAVE);
    tabBarPattern_->hoverIndex_.emplace(1);
    tabBarPattern_->HandleMouseEvent(mouseInfo);
    EXPECT_EQ(tabBarPattern_->indicator_, 0);
}
/**
 * @tc.name: ResetOnForceMeasure001
 * @tc.desc: test ResetOnForceMeasure
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, ResetOnForceMeasure001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    tabBarPattern_->ResetOnForceMeasure(5);
    tabBarPattern_->ResetOnForceMeasure(6);
    EXPECT_EQ(tabBarPattern_->jumpIndex_, 6);

    tabBarPattern_->indicatorStyles_.clear();
    IndicatorStyle indicatorStyle1;
    tabBarPattern_->indicatorStyles_ = { indicatorStyle1 };
    indicatorStyle1.color = Color::BLACK;
    tabBarPattern_->selectedModes_.clear();
    tabBarPattern_->ResetOnForceMeasure(0);
    EXPECT_EQ(tabBarPattern_->jumpIndex_, 0);

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { 5, 0.0f };
    tabBarPattern_->ResetOnForceMeasure(6);
    EXPECT_EQ(tabBarPattern_->jumpIndex_, 6);
}
/**
 * @tc.name: ResetOnForceMeasure002
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, ResetOnForceMeasure002, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->ResetOnForceMeasure(6);

    LabelStyle labelStyle;
    labelStyle.fontWeight = FontWeight::NORMAL;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE };
    auto tabBarItemNode = AceType::DynamicCast<FrameNode>(tabBarNode_->GetChildAtIndex(0));
    tabBarPattern_->SetLabelStyle(tabBarItemNode->GetId(), labelStyle);
    tabBarPattern_->ResetOnForceMeasure(6);
    EXPECT_EQ(tabBarPattern_->jumpIndex_, 6);
}
/**
 * @tc.name: UpdateBackBlurStyle
 * @tc.desc: test UpdateBackBlurStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateBackBlurStyle, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    auto container = Container::Current();
    container->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    auto pipeline = frameNode_->GetContext();
    EXPECT_NE(pipeline, nullptr);
    auto tabTheme = pipeline->GetTheme<TabTheme>();
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);

    tabTheme->bottomTabBackgroundBlurStyle_=11;
    auto defaultBlurStyle = static_cast<BlurStyle>(tabTheme->GetBottomTabBackgroundBlurStyle());
    EXPECT_NE(defaultBlurStyle, BlurStyle::NO_MATERIAL);
    auto renderContext = tabBarNode_->GetRenderContext();
    renderContext ->UpdateBackBlurStyle(std::nullopt);
    renderContext ->UpdateBackBlurRadius(Dimension());
    renderContext ->UpdateBackgroundEffect(std::nullopt);
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);

    tabTheme->bottomTabBackgroundBlurStyle_=0;
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);

    tabTheme->bottomTabBackgroundBlurStyle_=11;
    model.SetBarOverlap(AceType::RawPtr(frameNode_), true);
    EXPECT_EQ(renderContext->GetBackBlurStyle().has_value(), true);
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);

    tabTheme->bottomTabBackgroundBlurStyle_=11;
    renderContext->UpdateBackBlurStyle(std::nullopt);
    auto radius = Dimension(10.0f);
    renderContext->UpdateBackBlurRadius(radius);
    EXPECT_EQ(renderContext->GetBackBlurRadius().has_value(), false);
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);

    tabTheme->bottomTabBackgroundBlurStyle_=11;
    renderContext->UpdateBackBlurStyle(std::nullopt);
    renderContext->UpdateBackBlurRadius(Dimension());
    EffectOption effectOption;
    effectOption.policy = BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE;
    renderContext->UpdateBackgroundEffect(effectOption);
    EXPECT_EQ(renderContext->GetBackgroundEffect().has_value(), true);
    tabBarPattern_->UpdateBackBlurStyle(tabTheme);
}
/**
 * @tc.name: UpdatePaintIndicator
 * @tc.desc: test UpdatePaintIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdatePaintIndicator, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);
    MockPaintRect(tabBarNode_);

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->visibleItemPosition_[2] = { 1.0f, 2.0f };
    tabBarPattern_->UpdatePaintIndicator(2, true);
    EXPECT_NE(tabBarPattern_->visibleItemPosition_.find(2), tabBarPattern_->visibleItemPosition_.end());
    

    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->UpdatePaintIndicator(0, true);
    EXPECT_NE(tabBarPattern_->tabBarStyles_[0], TabBarStyle::SUBTABBATSTYLE);
}
/**
 * @tc.name: OnDirtyLayoutWrapperSwap
 * @tc.desc: test OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, OnDirtyLayoutWrapperSwap, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    DirtySwapConfig config;
    config.skipMeasure = true;
    config.skipLayout = true;
    auto layoutWrapper =
        AceType::MakeRefPtr<LayoutWrapperNode>(tabBarNode_, tabBarNode_->GetGeometryNode(), tabBarLayoutProperty_);
    EXPECT_EQ(tabBarPattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, config), false);
}
/**
 * @tc.name: HandleClick
 * @tc.desc: test HandleClick
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleClick, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    auto scrollable = tabBarPattern_->scrollableEvent_->GetScrollable();
    scrollable->GetSpringProperty();
    scrollable->state_ = Scrollable::AnimationState::SPRING;
    EXPECT_NE(tabBarPattern_->scrollableEvent_->GetScrollable(), nullptr);
    EXPECT_NE(tabBarPattern_->IsOutOfBoundary(), true);
    HandleClick(1); // click second tabBarItem

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    HandleClick(5);

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::BOTTOMTABBATSTYLE };
    HandleClick(5);
}
/**
 * @tc.name: HandleBottomTabBarChange001
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleBottomTabBarChange001, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->HandleBottomTabBarChange(-1);
    EXPECT_NE(tabBarPattern_->indicator_, -1);
}
/**
 * @tc.name: HandleBottomTabBarChange002
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleBottomTabBarChange002, TestSize.Level1)
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

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::SUBTABBATSTYLE };

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->ResetOnForceMeasure(1);
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE };

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->ResetOnForceMeasure(1);
    tabBarPattern_->HandleBottomTabBarChange(0);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}
/**
 * @tc.name: HandleBottomTabBarChange003
 * @tc.desc: test HandleBottomTabBarChange
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleBottomTabBarChange003, TestSize.Level1)
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

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
    TabBarStyle::BOTTOMTABBATSTYLE };

    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->ResetOnForceMeasure(1);
    tabBarPattern_->HandleBottomTabBarChange(2);
    EXPECT_EQ(tabBarPattern_->indicator_, 1);
}
/**
 * @tc.name: PlayPressAnimation
 * @tc.desc: test PlayPressAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, PlayPressAnimation, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    frameNode_->GetContext()->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWENTY));
    tabBarPattern_->tabBarStyle_ = TabBarStyle::BOTTOMTABBATSTYLE;
    EXPECT_EQ(Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE), true);
    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::PRESS);

    tabBarPattern_->PlayPressAnimation(0, Color::BLACK, AnimationType::HOVER);

    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE, TabBarStyle::BOTTOMTABBATSTYLE,
    TabBarStyle::BOTTOMTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD };
    tabBarPattern_->PlayPressAnimation(1, Color::BLACK, AnimationType::HOVER);
    EXPECT_EQ(tabBarPattern_->tabBarStyles_.size(), 3);

    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    IndicatorStyle indicatorStyle;
    indicatorStyle.color = Color::BLACK;
    tabBarPattern_->indicatorStyles_ = { indicatorStyle };
    tabBarPattern_->PlayPressAnimation(1, Color::BLACK, AnimationType::HOVER);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_.size(), 1);
}
/**
 * @tc.name: UpdateSubTabBoard
 * @tc.desc: test UpdateSubTabBoard
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, UpdateSubTabBoard, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->indicatorStyles_.clear();
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD };
    tabBarPattern_->UpdateSubTabBoard(1);
    EXPECT_EQ(tabBarPattern_->selectedModes_.size(), 1);

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->tabBarStyles_.clear();
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::SUBTABBATSTYLE };
    IndicatorStyle indicatorStyle;
    indicatorStyle.color = Color::BLACK;
    tabBarPattern_->indicatorStyles_ = { indicatorStyle };
    tabBarPattern_->UpdateSubTabBoard(0);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_.size(), 1);
}
/**
 * @tc.name: CalculateTargetOffset
 * @tc.desc: test CalculateTargetOffset
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, CalculateTargetOffset, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->visibleItemPosition_[0] = { -1.0f, 1.0f };
    tabBarPattern_->visibleItemPosition_[1] = { 1.0f, 2.0f };
    tabBarPattern_->CalculateTargetOffset(0);
    EXPECT_NE(tabBarPattern_->visibleItemPosition_.find(0), tabBarPattern_->visibleItemPosition_.end());

    tabBarPattern_->visibleItemPosition_.clear();
    tabBarPattern_->scrollMargin_ = 365.0f;
    tabBarPattern_->CalculateTargetOffset(1);
    auto backChildrenMainSize = tabBarPattern_->CalculateBackChildrenMainSize(1);
    auto space = tabBarPattern_->GetSpace(1);
    EXPECT_EQ(LessOrEqual(backChildrenMainSize, space), false);
}
/**
 * @tc.name: GetIndicatorStyle
 * @tc.desc: test GetIndicatorStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, GetIndicatorStyle, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->axis_ = Axis::HORIZONTAL;
    tabBarPattern_->isTouchingSwiper_ = true;
    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->swiperStartIndex_ = 1;
    IndicatorStyle indicatorStyle;
    indicatorStyle.color = Color::BLACK;
    tabBarPattern_->indicatorStyles_ = { indicatorStyle };
    auto firstRect = tabBarLayoutProperty_->GetIndicatorRect(0);
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE, TabBarStyle::SUBTABBATSTYLE };
    tabBarPattern_->selectedModes_ = { SelectedMode::BOARD, SelectedMode::INDICATOR };
    IndicatorStyle indicator;
    OffsetF indicatorOffset;
    EXPECT_EQ(tabBarPattern_->IsValidIndex(tabBarPattern_->swiperStartIndex_), true);
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset, firstRect);

    IndicatorStyle indicatorStyle1;
    indicatorStyle1.color = Color::BLACK;
    IndicatorStyle indicatorStyle2;
    indicatorStyle1.color = Color::BLACK;
    tabBarPattern_->indicatorStyles_ = { indicatorStyle, indicatorStyle1, indicatorStyle2 };
    tabBarPattern_->GetIndicatorStyle(indicator, indicatorOffset, firstRect);
    EXPECT_EQ(tabBarPattern_->indicatorStyles_.size() >= 2, true);
}
/**
 * @tc.name: OnRestoreInfo
 * @tc.desc: test OnRestoreInfo
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, OnRestoreInfo, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    std::string restoreInfo_ = R"({"Index":2})";
    auto info = JsonUtil::ParseJsonString(restoreInfo_);
    tabBarPattern_->indicator_ = 2;
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE, TabBarStyle::SUBTABBATSTYLE };
    EXPECT_EQ(tabBarPattern_->tabBarStyles_.size(), 2);
    tabBarPattern_->OnRestoreInfo(restoreInfo_);

    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE, TabBarStyle::SUBTABBATSTYLE,
    TabBarStyle::BOTTOMTABBATSTYLE };
    pattern_->SetAnimateMode(TabAnimateMode::NO_ANIMATION);
    tabBarPattern_->OnRestoreInfo(restoreInfo_);
    EXPECT_EQ(tabBarPattern_->GetAnimationDuration().has_value(), true);
}
/**
 * @tc.name: FromJson
 * @tc.desc: test FromJson
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, FromJson, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    InspectorFilter filter;
    IndicatorStyle style1;
    style1.height = Dimension(12);
    IndicatorStyle style2;
    style2.height = Dimension(16);
    tabBarPattern_->selectedModes_ = { SelectedMode::INDICATOR, SelectedMode::BOARD };
    tabBarPattern_->indicatorStyles_ = { style1, style2 };
    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE, TabBarStyle::SUBTABBATSTYLE };

    auto json = JsonUtil::Create(true);
    tabBarPattern_->ToJsonValue(json, filter);
    tabBarPattern_->FromJson(json);
    auto tabBarStyles = JsonUtil::ParseJsonString(json->GetString("tabBarStyles"));
    EXPECT_EQ(tabBarStyles->GetArraySize(), 2);
}
/**
 * @tc.name: ApplyTurnPageRateToIndicator
 * @tc.desc: test ApplyTurnPageRateToIndicator
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, ApplyTurnPageRateToIndicator, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContentTabBarStyle(TabBarStyle::SUBTABBATSTYLE);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->ApplyTurnPageRateToIndicator(0.9f);

    tabBarPattern_->turnPageRate_ = 0.5f;
    EXPECT_EQ(tabBarPattern_->turnPageRate_ <= 0.673f, true);
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.9f);

    tabBarPattern_->turnPageRate_ = 0.9f;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.3f);

    tabBarPattern_->isRTL_ = true;
    tabBarPattern_->ApplyTurnPageRateToIndicator(0.3f);
    EXPECT_EQ(tabBarPattern_->currentIndicatorOffset_, 360);
}
/**
 * @tc.name: HandleBottomTabBarAnimation
 * @tc.desc: test HandleBottomTabBarAnimation
 * @tc.type: FUNC
 */
HWTEST_F(TabBarPatternTestNg, HandleBottomTabBarAnimation, TestSize.Level1)
{
    TabsModelNG model = CreateTabs();
    model.SetTabBarMode(TabBarMode::SCROLLABLE);
    model.SetIsVertical(false);
    CreateTabContents(TABCONTENT_NUMBER);
    CreateTabsDone(model);

    tabBarPattern_->tabBarStyles_ = { TabBarStyle::NOSTYLE };
    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->HandleBottomTabBarAnimation(1);
    EXPECT_EQ(tabBarPattern_->indicator_, tabBarPattern_->tabBarStyles_.size());

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarAnimation(1);

    tabBarPattern_->indicator_ = -1;
    tabBarPattern_->HandleBottomTabBarAnimation(1);

    tabBarPattern_->indicator_ = 0;
    tabBarPattern_->HandleBottomTabBarAnimation(-1);

    tabBarPattern_->tabBarStyles_ = { TabBarStyle::BOTTOMTABBATSTYLE, TabBarStyle::NOSTYLE };
    tabBarPattern_->indicator_ = 1;
    tabBarPattern_->HandleBottomTabBarAnimation(1);
    EXPECT_NE(tabBarPattern_->tabBarStyles_[1], TabBarStyle::BOTTOMTABBATSTYLE);
}
} // namespace OHOS::Ace::NG
