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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        TabsItemDivider divider;
        model.SetDivider(divider);
        CreateSingleItemWithoutBuilder([](TabContentModelNG tabContentModel) {}, 0);
    });
    tabBarLayoutProperty_->UpdateTabBarMode(TabBarMode::SCROLLABLE);
    auto pr = tabBarPattern_->tabBarType_.emplace(std::make_pair(1, true));
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
    tabBarPattern_->SetLabelStyle(labelStyle, 0);
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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
    Create([](TabsModelNG model) {
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 0);
        CreateSingleItem([](TabContentModelNG tabContentModel) {
            tabContentModel.SetTabBarStyle(TabBarStyle::BOTTOMTABBATSTYLE);
        }, 1);
    });

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
} // namespace OHOS::Ace::NG
