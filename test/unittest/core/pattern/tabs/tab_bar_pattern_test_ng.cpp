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

#include "core/components_ng/pattern/text/text_layout_property.h"
#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"

namespace OHOS::Ace::NG {

namespace {} // namespace

class TabBarPatternTestNg : public TabsTestNg {
public:
};

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

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
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

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
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

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
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

    auto maskNode1 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT));
    auto imageNode1 = AceType::DynamicCast<FrameNode>(maskNode1->GetChildren().front());

    auto maskNode2 = AceType::DynamicCast<FrameNode>(
        tabBarNode_->GetChildAtIndex(tabBarNode_->GetChildren().size() - TEST_SELECTED_MASK_COUNT + 1));
    auto imageNode2 = AceType::DynamicCast<FrameNode>(maskNode2->GetChildren().front());

    tabBarPattern_->PlayMaskAnimation(selectedImageSize, originalSelectedMaskOffset, selectedIndex, unselectedImageSize,
        originalUnselectedMaskOffset, unselectedIndex);
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
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. default translate is 0, test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
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
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_LT(options.y.ConvertToPx(), 10.0f);
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(options.y.ConvertToPx(), 0.0f);
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
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();

    /**
     * @tc.steps: step2. start hide tab bar, test function StartShowTabBar.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_GT(options.y.ConvertToPx(), 0.0f);
    tabBarPattern_->StartShowTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_LT(options.y.ConvertToPx(), size);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(options.y.ConvertToPx(), 0.0f);
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

    /**
     * @tc.steps: step2. default translate is 0, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_LT(options.y.ConvertToPx(), 0.0f);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(options.y.ConvertToPx(), -size);

    /**
     * @tc.steps: step3. Translate equals tab bar size, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::GetInstance().SetTicks(2);
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

    /**
     * @tc.steps: step2. default translate is 0, test function StartHideTabBar.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_GT(options.y.ConvertToPx(), 0.0f);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(options.y.ConvertToPx(), size);
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
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->StartHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_GT(options.y.ConvertToPx(), 0.0f);
    tabBarPattern_->StopHideTabBar();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_LT(options.y.ConvertToPx(), size);
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

    /**
     * @tc.steps: step2.Set offset to 10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto opacity = renderContext->GetOpacityValue(1.0f);
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(options.y.ConvertToPx(), - offset1);
    EXPECT_EQ(opacity, 1.0f - offset1 / size);

    /**
     * @tc.steps: step3.Set offset to 26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    auto offset2 = Dimension(26.0f, DimensionUnit::VP).ConvertToPx();
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_LT(options.y.ConvertToPx(), - (offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(options.y.ConvertToPx(), - size);
    EXPECT_EQ(opacity, 0.0f);

    /**
     * @tc.steps: step4.Set offset to -10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset1);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(options.y.ConvertToPx(), - size + offset1);
    EXPECT_EQ(opacity, offset1 / size);

    /**
     * @tc.steps: step5.Set offset to -26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_GT(options.y.ConvertToPx(), - size + (offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    opacity = renderContext->GetOpacityValue(1.0f);
    EXPECT_EQ(options.y.ConvertToPx(), 0.0f);
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

    /**
     * @tc.steps: step2.Set offset to 10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto offset1 = 10.0f;
    tabBarPattern_->UpdateTabBarHiddenOffset(offset1);
    auto renderContext = tabBarNode_->GetRenderContext();
    auto options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    auto size = renderContext->GetPaintRectWithoutTransform().Height();
    EXPECT_EQ(options.y.ConvertToPx(), offset1);

    /**
     * @tc.steps: step3.Set offset to 26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    MockAnimationManager::Enable(true);
    MockAnimationManager::GetInstance().SetTicks(2);
    auto offset2 = Dimension(26.0f, DimensionUnit::VP).ConvertToPx();
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_GT(options.y.ConvertToPx(), offset1 + offset2);
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarHiding_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(options.y.ConvertToPx(), size);

    /**
     * @tc.steps: step4.Set offset to -10.0f, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset1);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(options.y.ConvertToPx(), size - offset1);

    /**
     * @tc.steps: step5.Set offset to -26.0_vp, test function UpdateTabBarOffset.
     * @tc.expected: Related function runs ok.
     */
    auto pipeline = frameNode_->GetContext();
    pipeline->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockAnimationManager::GetInstance().SetTicks(2);
    tabBarPattern_->UpdateTabBarHiddenOffset(-offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_LT(options.y.ConvertToPx(), size - (offset1 + offset2));
    tabBarPattern_->UpdateTabBarHiddenOffset(offset2);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(tabBarPattern_->isTabBarShowing_);
    options = renderContext->GetTransformTranslateValue(TranslateOptions(0.0f, 0.0f, 0.0f));
    EXPECT_EQ(options.y.ConvertToPx(), 0.0f);
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
} // namespace OHOS::Ace::NG
