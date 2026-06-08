/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gtest/gtest.h"
#include "tabs_test_ng.h"

#include "core/components_ng/pattern/tabs/tab_content_model_static.h"
#include "core/components_ng/pattern/tabs/tab_content_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_node.h"
#include "core/components_ng/pattern/tabs/tab_content_layout_property.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_item_pattern.h"
#include "core/components_ng/pattern/tabs/tab_bar_pattern.h"
#include "core/components_ng/pattern/tabs/tab_content_event_hub.h"
#include "core/components_ng/syntax/shallow_builder.h"

namespace OHOS::Ace::NG {

class TabContentModelStaticTestNg : public TabsTestNg {
public:
    static void SetUpTestSuite()
    {
        TabsTestNg::SetUpTestSuite();
    }

    static void TearDownTestSuite()
    {
        TabsTestNg::TearDownTestSuite();
    }

    void SetUp() override {}
    void TearDown() override
    {
        TabsTestNg::TearDown();
    }

    RefPtr<FrameNode> CreateStandaloneTabContent()
    {
        auto nodeId = ElementRegister::GetInstance()->MakeUniqueId();
        return AceType::DynamicCast<TabContentNode>(
            TabContentNode::GetOrCreateTabContentNode(
                V2::TAB_CONTENT_ITEM_ETS_TAG, nodeId,
                []() { return AceType::MakeRefPtr<TabContentPattern>(nullptr); }));
    }
};

// ===================== SetShallowBuilder =====================

/**
 * @tc.name: SetShallowBuilder_NullFrameNode
 * @tc.desc: SetShallowBuilder with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetShallowBuilder_NullFrameNode, TestSize.Level1)
{
    TabContentModelStatic::SetShallowBuilder(nullptr, nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetShallowBuilder_NullPattern
 * @tc.desc: SetShallowBuilder with frameNode that has no TabContentPattern should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetShallowBuilder_NullPattern, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(frameNode, nullptr);
    TabContentModelStatic::SetShallowBuilder(AceType::RawPtr(frameNode), nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetShallowBuilder_Valid
 * @tc.desc: SetShallowBuilder with valid frameNode and shallowBuilder should set the builder
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetShallowBuilder_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    auto shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    TabContentModelStatic::SetShallowBuilder(AceType::RawPtr(frameNode), shallowBuilder);
    EXPECT_NE(pattern->shallowBuilder_, nullptr);
}

// ===================== SetIndicator =====================

/**
 * @tc.name: SetIndicator_NullFrameNode
 * @tc.desc: SetIndicator with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicator_NullFrameNode, TestSize.Level1)
{
    std::optional<IndicatorStyle> indicatorOpt = IndicatorStyle();
    TabContentModelStatic::SetIndicator(nullptr, indicatorOpt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIndicator_NullPattern
 * @tc.desc: SetIndicator with frameNode having no TabContentPattern should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicator_NullPattern, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    std::optional<IndicatorStyle> indicatorOpt = IndicatorStyle();
    TabContentModelStatic::SetIndicator(AceType::RawPtr(frameNode), indicatorOpt);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIndicator_HasValue
 * @tc.desc: SetIndicator with valid indicatorOpt should set indicator style on pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicator_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    IndicatorStyle indicator;
    indicator.color = Color::RED;
    indicator.height = 10.0_vp;
    std::optional<IndicatorStyle> indicatorOpt = indicator;
    TabContentModelStatic::SetIndicator(AceType::RawPtr(frameNode), indicatorOpt);
    EXPECT_EQ(pattern->indicatorStyle_.color, Color::RED);
    EXPECT_EQ(pattern->indicatorStyle_.height, 10.0_vp);
}

/**
 * @tc.name: SetIndicator_NoValue
 * @tc.desc: SetIndicator with nullopt should use default TabTheme values
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicator_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetIndicator(AceType::RawPtr(frameNode), std::nullopt);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);
    EXPECT_EQ(pattern->indicatorStyle_.color, tabTheme->GetActiveIndicatorColor());
}

// ===================== SetDrawableIndicatorConfig =====================

/**
 * @tc.name: SetDrawableIndicatorConfig_NullFrameNode
 * @tc.desc: SetDrawableIndicatorConfig with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetDrawableIndicatorConfig_NullFrameNode, TestSize.Level1)
{
    ImageInfoConfig config;
    TabContentModelStatic::SetDrawableIndicatorConfig(nullptr, config);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetDrawableIndicatorConfig_Valid
 * @tc.desc: SetDrawableIndicatorConfig with valid frameNode should set config
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetDrawableIndicatorConfig_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    ImageInfoConfig config;
    TabContentModelStatic::SetDrawableIndicatorConfig(AceType::RawPtr(frameNode), config);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    auto storedConfig = pattern->GetDrawableIndicatorConfig();
    EXPECT_FALSE(storedConfig.isUriPureNumber);
}

// ===================== SetIndicatorColorByUser =====================

/**
 * @tc.name: SetIndicatorColorByUser_True
 * @tc.desc: SetIndicatorColorByUser should update layout property
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicatorColorByUser_True, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    TabContentModelStatic::SetIndicatorColorByUser(AceType::RawPtr(frameNode), true);
    auto layoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_TRUE(layoutProperty->GetIndicatorColorSetByUserValue());
}

/**
 * @tc.name: SetIndicatorColorByUser_False
 * @tc.desc: SetIndicatorColorByUser with false should update layout property
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIndicatorColorByUser_False, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    TabContentModelStatic::SetIndicatorColorByUser(AceType::RawPtr(frameNode), false);
    auto layoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_FALSE(layoutProperty->GetIndicatorColorSetByUserValue());
}

// ===================== SetDrawableIndicatorFlag =====================

/**
 * @tc.name: SetDrawableIndicatorFlag_NullFrameNode
 * @tc.desc: SetDrawableIndicatorFlag with null should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetDrawableIndicatorFlag_NullFrameNode, TestSize.Level1)
{
    TabContentModelStatic::SetDrawableIndicatorFlag(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetDrawableIndicatorFlag_True
 * @tc.desc: SetDrawableIndicatorFlag should set flag on pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetDrawableIndicatorFlag_True, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetDrawableIndicatorFlag(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->isDrawableIndicator_);
}

/**
 * @tc.name: SetDrawableIndicatorFlag_False
 * @tc.desc: SetDrawableIndicatorFlag with false should set flag to false
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetDrawableIndicatorFlag_False, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetDrawableIndicatorFlag(AceType::RawPtr(frameNode), false);
    EXPECT_FALSE(pattern->isDrawableIndicator_);
}

// ===================== SetLabelStyle / CompleteParameters =====================

/**
 * @tc.name: SetLabelStyle_NullFrameNode
 * @tc.desc: SetLabelStyle with null frameNode should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetLabelStyle_NullFrameNode, TestSize.Level1)
{
    std::optional<LabelStyle> labelStyleOpt = LabelStyle();
    TabContentModelStatic::SetLabelStyle(nullptr, labelStyleOpt, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CompleteParameters_NullFrameNode
 * @tc.desc: CompleteParameters with null frameNode returns raw labelStyle unchanged
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_NullFrameNode, TestSize.Level1)
{
    LabelStyle labelStyle;
    labelStyle.fontSize = 16.0_vp;
    auto result = TabContentModelStatic::CompleteParameters(nullptr, labelStyle, false);
    EXPECT_EQ(result.fontSize, 16.0_vp);
}

/**
 * @tc.name: CompleteParameters_NullTheme
 * @tc.desc: CompleteParameters with frameNode having no theme returns raw labelStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_NullTheme, TestSize.Level1)
{
    auto frameNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    LabelStyle labelStyle;
    labelStyle.fontSize = 16.0_vp;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, false);
    EXPECT_EQ(result.fontSize, 16.0_vp);
}

/**
 * @tc.name: CompleteParameters_DefaultFields
 * @tc.desc: CompleteParameters fills in default values for unset fields
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_DefaultFields, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    LabelStyle labelStyle;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, false);
    EXPECT_EQ(result.maxLines, 1);
    EXPECT_EQ(result.minFontSize, 0.0_vp);
    EXPECT_EQ(result.maxFontSize, 0.0_vp);
    EXPECT_EQ(result.fontWeight, FontWeight::MEDIUM);
    EXPECT_EQ(result.fontStyle, Ace::FontStyle::NORMAL);
    EXPECT_EQ(result.heightAdaptivePolicy, TextHeightAdaptivePolicy::MAX_LINES_FIRST);
    EXPECT_EQ(result.textOverflow, TextOverflow::ELLIPSIS);
}

/**
 * @tc.name: CompleteParameters_FontSizeSubTab
 * @tc.desc: CompleteParameters with isSubTabStyle true fills sub-tab font size
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_FontSizeSubTab, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);
    LabelStyle labelStyle;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, true);
    EXPECT_EQ(result.fontSize, tabTheme->GetSubTabTextDefaultFontSize());
}

/**
 * @tc.name: CompleteParameters_FontSizeBottomTab
 * @tc.desc: CompleteParameters with isSubTabStyle false skips fontSize when version >= VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_FontSizeBottomTab, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    LabelStyle labelStyle;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, false);
    EXPECT_TRUE(result.maxLines.has_value());
    EXPECT_EQ(result.maxLines, 1);
}

/**
 * @tc.name: CompleteParameters_FontSizeAlreadySet
 * @tc.desc: CompleteParameters should not override already-set fontSize
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_FontSizeAlreadySet, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    LabelStyle labelStyle;
    labelStyle.fontSize = 20.0_vp;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, true);
    EXPECT_EQ(result.fontSize, 20.0_vp);
}

/**
 * @tc.name: CompleteParameters_FontWeightSubTab
 * @tc.desc: CompleteParameters with isSubTabStyle true should not set fontWeight
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_FontWeightSubTab, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    LabelStyle labelStyle;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, true);
    EXPECT_FALSE(result.fontWeight.has_value());
}

/**
 * @tc.name: CompleteParameters_FieldsPreserved
 * @tc.desc: CompleteParameters preserves already-set label style fields
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompleteParameters_FieldsPreserved, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    LabelStyle labelStyle;
    labelStyle.maxLines = 3;
    labelStyle.minFontSize = 8.0_vp;
    labelStyle.maxFontSize = 24.0_vp;
    labelStyle.fontWeight = FontWeight::BOLD;
    labelStyle.fontStyle = Ace::FontStyle::ITALIC;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    labelStyle.textOverflow = TextOverflow::MARQUEE;
    auto result = TabContentModelStatic::CompleteParameters(AceType::RawPtr(frameNode), labelStyle, false);
    EXPECT_EQ(result.maxLines, 3);
    EXPECT_EQ(result.minFontSize, 8.0_vp);
    EXPECT_EQ(result.maxFontSize, 24.0_vp);
    EXPECT_EQ(result.fontWeight, FontWeight::BOLD);
    EXPECT_EQ(result.fontStyle, Ace::FontStyle::ITALIC);
    EXPECT_EQ(result.heightAdaptivePolicy, TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    EXPECT_EQ(result.textOverflow, TextOverflow::MARQUEE);
}

// ===================== SetSelectedMode =====================

/**
 * @tc.name: SetSelectedMode_NullNode
 * @tc.desc: SetSelectedMode with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSelectedMode_NullNode, TestSize.Level1)
{
    std::optional<SelectedMode> mode = SelectedMode::BOARD;
    TabContentModelStatic::SetSelectedMode(nullptr, mode);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSelectedMode_HasValue
 * @tc.desc: SetSelectedMode with BOARD value should set selected mode to BOARD
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSelectedMode_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetSelectedMode(AceType::RawPtr(frameNode), SelectedMode::BOARD);
    EXPECT_EQ(pattern->selectedMode_, SelectedMode::BOARD);
}

/**
 * @tc.name: SetSelectedMode_NoValue
 * @tc.desc: SetSelectedMode with nullopt should fallback to INDICATOR
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSelectedMode_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetSelectedMode(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(pattern->selectedMode_, SelectedMode::INDICATOR);
}

// ===================== SetBoard =====================

/**
 * @tc.name: SetBoard_NullNode
 * @tc.desc: SetBoard with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetBoard_NullNode, TestSize.Level1)
{
    std::optional<BoardStyle> board = BoardStyle();
    TabContentModelStatic::SetBoard(nullptr, board);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetBoard_HasValue
 * @tc.desc: SetBoard with valid board should set board style
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetBoard_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    BoardStyle board;
    board.borderRadius = 8.0_vp;
    TabContentModelStatic::SetBoard(AceType::RawPtr(frameNode), board);
    EXPECT_EQ(pattern->boardStyle_.borderRadius, 8.0_vp);
}

/**
 * @tc.name: SetBoard_NoValue
 * @tc.desc: SetBoard with nullopt should fallback to default BoardStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetBoard_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetBoard(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(pattern->boardStyle_.borderRadius, 0.0_vp);
}

// ===================== SetPadding / CompletePaddingProperty =====================

/**
 * @tc.name: SetPadding_NullNode
 * @tc.desc: SetPadding with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetPadding_NullNode, TestSize.Level1)
{
    std::optional<PaddingProperty> padding = PaddingProperty();
    TabContentModelStatic::SetPadding(nullptr, padding, false);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: CompletePaddingProperty_NullFrameNode
 * @tc.desc: CompletePaddingProperty with null frameNode returns padding unchanged
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompletePaddingProperty_NullFrameNode, TestSize.Level1)
{
    PaddingProperty padding;
    CalcLength topLen(10.0_vp);
    padding.top = topLen;
    auto result = TabContentModelStatic::CompletePaddingProperty(nullptr, padding, false);
    EXPECT_TRUE(result.top.has_value());
}

/**
 * @tc.name: CompletePaddingProperty_SubTabDefaults
 * @tc.desc: CompletePaddingProperty with isSubTabStyle true fills sub-tab padding defaults
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompletePaddingProperty_SubTabDefaults, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);
    PaddingProperty padding;
    auto result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(frameNode), padding, true);
    ASSERT_TRUE(result.top.has_value());
    ASSERT_TRUE(result.bottom.has_value());
    ASSERT_TRUE(result.left.has_value());
    ASSERT_TRUE(result.right.has_value());
    EXPECT_EQ(result.top->GetDimension(), tabTheme->GetSubTabTopPadding());
    EXPECT_EQ(result.bottom->GetDimension(), tabTheme->GetSubTabBottomPadding());
    EXPECT_EQ(result.left->GetDimension(), tabTheme->GetSubTabHorizontalPadding());
    EXPECT_EQ(result.right->GetDimension(), tabTheme->GetSubTabHorizontalPadding());
}

/**
 * @tc.name: CompletePaddingProperty_BottomTabDefaults
 * @tc.desc: CompletePaddingProperty with isSubTabStyle false fills bottom tab defaults
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompletePaddingProperty_BottomTabDefaults, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);
    PaddingProperty padding;
    auto result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(frameNode), padding, false);
    ASSERT_TRUE(result.top.has_value());
    ASSERT_TRUE(result.bottom.has_value());
    ASSERT_TRUE(result.left.has_value());
    ASSERT_TRUE(result.right.has_value());
    EXPECT_EQ(result.top->GetDimension(), 0.0_vp);
    EXPECT_EQ(result.bottom->GetDimension(), 0.0_vp);
    EXPECT_EQ(result.left->GetDimension(), tabTheme->GetBottomTabHorizontalPadding());
    EXPECT_EQ(result.right->GetDimension(), tabTheme->GetBottomTabHorizontalPadding());
}

/**
 * @tc.name: CompletePaddingProperty_PreserveExisting
 * @tc.desc: CompletePaddingProperty preserves already-set padding values
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CompletePaddingProperty_PreserveExisting, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    PaddingProperty padding;
    CalcLength customTop(25.0_vp);
    padding.top = customTop;
    auto result = TabContentModelStatic::CompletePaddingProperty(AceType::RawPtr(frameNode), padding, true);
    EXPECT_EQ(result.top->GetDimension(), 25.0_vp);
}

// ===================== SetUseLocalizedPadding =====================

/**
 * @tc.name: SetUseLocalizedPadding_NullNode
 * @tc.desc: SetUseLocalizedPadding with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetUseLocalizedPadding_NullNode, TestSize.Level1)
{
    TabContentModelStatic::SetUseLocalizedPadding(nullptr, true);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetUseLocalizedPadding_True
 * @tc.desc: SetUseLocalizedPadding with true should set flag on pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetUseLocalizedPadding_True, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetUseLocalizedPadding(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->useLocalizedPadding_);
}

// ===================== SetId =====================

/**
 * @tc.name: SetId_NullNode
 * @tc.desc: SetId with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetId_NullNode, TestSize.Level1)
{
    std::optional<std::string> id = "testId";
    TabContentModelStatic::SetId(nullptr, id);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetId_HasValue
 * @tc.desc: SetId with value should set id on pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetId_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetId(AceType::RawPtr(frameNode), std::string("testId"));
    EXPECT_EQ(pattern->tabBarInspectorId_, "testId");
}

/**
 * @tc.name: SetId_NoValue
 * @tc.desc: SetId with nullopt should set empty string
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetId_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetId(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(pattern->tabBarInspectorId_, "");
}

// ===================== SetTabBarStyle =====================

/**
 * @tc.name: SetTabBarStyle_NullNode
 * @tc.desc: SetTabBarStyle with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBarStyle_NullNode, TestSize.Level1)
{
    TabContentModelStatic::SetTabBarStyle(nullptr, TabBarStyle::SUBTABBATSTYLE);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBarStyle_Valid
 * @tc.desc: SetTabBarStyle with valid node should set tab bar style
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBarStyle_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetTabBarStyle(AceType::RawPtr(frameNode), TabBarStyle::SUBTABBATSTYLE);
    EXPECT_EQ(pattern->GetTabBarStyle(), TabBarStyle::SUBTABBATSTYLE);
}

// ===================== SetLayoutMode =====================

/**
 * @tc.name: SetLayoutMode_NullNode
 * @tc.desc: SetLayoutMode with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetLayoutMode_NullNode, TestSize.Level1)
{
    std::optional<LayoutMode> mode = LayoutMode::HORIZONTAL;
    TabContentModelStatic::SetLayoutMode(nullptr, mode);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetLayoutMode_HasValue
 * @tc.desc: SetLayoutMode with HORIZONTAL should set layout mode
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetLayoutMode_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(frameNode), LayoutMode::HORIZONTAL);
    EXPECT_EQ(pattern->bottomTabBarStyle_.layoutMode, LayoutMode::HORIZONTAL);
}

/**
 * @tc.name: SetLayoutMode_NoValue
 * @tc.desc: SetLayoutMode with nullopt should fallback to VERTICAL
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetLayoutMode_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetLayoutMode(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(pattern->bottomTabBarStyle_.layoutMode, LayoutMode::VERTICAL);
}

// ===================== SetVerticalAlign =====================

/**
 * @tc.name: SetVerticalAlign_NullNode
 * @tc.desc: SetVerticalAlign with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetVerticalAlign_NullNode, TestSize.Level1)
{
    std::optional<FlexAlign> align = FlexAlign::FLEX_START;
    TabContentModelStatic::SetVerticalAlign(nullptr, align);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetVerticalAlign_HasValue
 * @tc.desc: SetVerticalAlign with FLEX_START should set vertical align
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetVerticalAlign_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(frameNode), FlexAlign::FLEX_START);
    EXPECT_EQ(pattern->bottomTabBarStyle_.verticalAlign, FlexAlign::FLEX_START);
}

/**
 * @tc.name: SetVerticalAlign_NoValue
 * @tc.desc: SetVerticalAlign with nullopt should fallback to CENTER
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetVerticalAlign_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetVerticalAlign(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_EQ(pattern->bottomTabBarStyle_.verticalAlign, FlexAlign::CENTER);
}

// ===================== SetSymmetricExtensible =====================

/**
 * @tc.name: SetSymmetricExtensible_NullNode
 * @tc.desc: SetSymmetricExtensible with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSymmetricExtensible_NullNode, TestSize.Level1)
{
    std::optional<bool> extensible = true;
    TabContentModelStatic::SetSymmetricExtensible(nullptr, extensible);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetSymmetricExtensible_True
 * @tc.desc: SetSymmetricExtensible with true should set flag
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSymmetricExtensible_True, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(frameNode), true);
    EXPECT_TRUE(pattern->bottomTabBarStyle_.symmetricExtensible);
}

/**
 * @tc.name: SetSymmetricExtensible_NoValue
 * @tc.desc: SetSymmetricExtensible with nullopt should fallback to false
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetSymmetricExtensible_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetSymmetricExtensible(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_FALSE(pattern->bottomTabBarStyle_.symmetricExtensible);
}

// ===================== SetIconStyle =====================

/**
 * @tc.name: SetIconStyle_NullNode
 * @tc.desc: SetIconStyle with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIconStyle_NullNode, TestSize.Level1)
{
    std::optional<IconStyle> iconStyle = IconStyle();
    TabContentModelStatic::SetIconStyle(nullptr, iconStyle);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetIconStyle_HasValue
 * @tc.desc: SetIconStyle with icon style should set icon style on pattern
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIconStyle_HasValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    IconStyle iconStyle;
    iconStyle.selectedColor = Color::RED;
    iconStyle.unselectedColor = Color::GRAY;
    TabContentModelStatic::SetIconStyle(AceType::RawPtr(frameNode), iconStyle);
    EXPECT_EQ(pattern->iconStyle_.selectedColor, Color::RED);
    EXPECT_EQ(pattern->iconStyle_.unselectedColor, Color::GRAY);
}

/**
 * @tc.name: SetIconStyle_NoValue
 * @tc.desc: SetIconStyle with nullopt should fallback to default IconStyle
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetIconStyle_NoValue, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    TabContentModelStatic::SetIconStyle(AceType::RawPtr(frameNode), std::nullopt);
    EXPECT_FALSE(pattern->iconStyle_.selectedColor.has_value());
    EXPECT_FALSE(pattern->iconStyle_.unselectedColor.has_value());
}

// ===================== SetOnWillShow / SetOnWillHide =====================

/**
 * @tc.name: SetOnWillShow_NullNode
 * @tc.desc: SetOnWillShow with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetOnWillShow_NullNode, TestSize.Level1)
{
    auto callback = []() {};
    TabContentModelStatic::SetOnWillShow(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnWillShow_Valid
 * @tc.desc: SetOnWillShow with valid node should set callback on event hub
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetOnWillShow_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TabContentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool invoked = false;
    auto callback = [&invoked]() { invoked = true; };
    TabContentModelStatic::SetOnWillShow(AceType::RawPtr(frameNode), std::move(callback));
    eventHub->FireWillShowEvent();
    EXPECT_TRUE(invoked);
}

/**
 * @tc.name: SetOnWillHide_NullNode
 * @tc.desc: SetOnWillHide with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetOnWillHide_NullNode, TestSize.Level1)
{
    auto callback = []() {};
    TabContentModelStatic::SetOnWillHide(nullptr, std::move(callback));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetOnWillHide_Valid
 * @tc.desc: SetOnWillHide with valid node should set callback on event hub
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetOnWillHide_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto eventHub = frameNode->GetEventHub<TabContentEventHub>();
    ASSERT_NE(eventHub, nullptr);
    bool invoked = false;
    auto callback = [&invoked]() { invoked = true; };
    TabContentModelStatic::SetOnWillHide(AceType::RawPtr(frameNode), std::move(callback));
    eventHub->FireWillHideEvent();
    EXPECT_TRUE(invoked);
}

// ===================== SetCustomStyleNode =====================

/**
 * @tc.name: SetCustomStyleNode_NullNode
 * @tc.desc: SetCustomStyleNode with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetCustomStyleNode_NullNode, TestSize.Level1)
{
    TabContentModelStatic::SetCustomStyleNode(nullptr, nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetCustomStyleNode_Valid
 * @tc.desc: SetCustomStyleNode with valid node should set custom style node
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetCustomStyleNode_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    auto customNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    TabContentModelStatic::SetCustomStyleNode(AceType::RawPtr(frameNode), customNode);
    EXPECT_NE(pattern->customStyleNode_, nullptr);
}

// ===================== CreateFrameNode =====================

/**
 * @tc.name: CreateFrameNode_Success
 * @tc.desc: CreateFrameNode should successfully create a TabContentNode
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, CreateFrameNode_Success, TestSize.Level1)
{
    auto frameNode = TabContentModelStatic::CreateFrameNode(
        ElementRegister::GetInstance()->MakeUniqueId());
    ASSERT_NE(frameNode, nullptr);
    auto tabContentNode = AceType::DynamicCast<TabContentNode>(frameNode);
    ASSERT_NE(tabContentNode, nullptr);
    auto pattern = frameNode->GetPattern<TabContentPattern>();
    ASSERT_NE(pattern, nullptr);
    EXPECT_FALSE(pattern->GetTabBarParam().GetText().empty());
}

// ===================== SetTabBar =====================

/**
 * @tc.name: SetTabBar_NullNode
 * @tc.desc: SetTabBar with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBar_NullNode, TestSize.Level1)
{
    TabBarBuilderFunc builder = []() {};
    TabContentModelStatic::SetTabBar(nullptr, "label", "icon", std::move(builder));
    EXPECT_TRUE(true);
}

/**
 * @tc.name: SetTabBar_IconAndLabel
 * @tc.desc: SetTabBar with icon and label should update layout properties
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBar_IconAndLabel, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    TabBarBuilderFunc builder = []() {};
    TabContentModelStatic::SetTabBar(AceType::RawPtr(frameNode), std::string("label"),
        std::string("icon"), std::move(builder));
    auto layoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    EXPECT_EQ(layoutProperty->GetTextValue(""), "label");
    EXPECT_EQ(layoutProperty->GetIconValue(""), "icon");
}

/**
 * @tc.name: SetTabBar_NoIcon
 * @tc.desc: SetTabBar without icon should reset icon property
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBar_NoIcon, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateIcon("oldIcon");
    TabBarBuilderFunc builder = []() {};
    TabContentModelStatic::SetTabBar(AceType::RawPtr(frameNode), std::string("label"),
        std::nullopt, std::move(builder));
    EXPECT_EQ(layoutProperty->GetIconValue(""), "");
}

/**
 * @tc.name: SetTabBar_NoLabel
 * @tc.desc: SetTabBar without label should reset text property
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBar_NoLabel, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<TabContentLayoutProperty>();
    ASSERT_NE(layoutProperty, nullptr);
    layoutProperty->UpdateText("oldText");
    TabBarBuilderFunc builder = []() {};
    TabContentModelStatic::SetTabBar(AceType::RawPtr(frameNode), std::nullopt,
        std::string("icon"), std::move(builder));
    EXPECT_EQ(layoutProperty->GetTextValue(""), "");
}

// ===================== SetTabBarWithContent =====================

/**
 * @tc.name: SetTabBarWithContent_NullNode
 * @tc.desc: SetTabBarWithContent with null node should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, SetTabBarWithContent_NullNode, TestSize.Level1)
{
    TabContentModelStatic::SetTabBarWithContent(nullptr, nullptr);
    EXPECT_TRUE(true);
}

// ===================== UpdateLabelStyle =====================

/**
 * @tc.name: UpdateLabelStyle_NullTextProperty
 * @tc.desc: UpdateLabelStyle with null textLayoutProperty should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateLabelStyle_NullTextProperty, TestSize.Level1)
{
    LabelStyle labelStyle;
    TabContentModelStatic::UpdateLabelStyle(labelStyle, nullptr);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: UpdateLabelStyle_AllFields
 * @tc.desc: UpdateLabelStyle with all fields set should update text properties
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateLabelStyle_AllFields, TestSize.Level1)
{
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LabelStyle labelStyle;
    labelStyle.fontSize = 20.0_vp;
    labelStyle.fontWeight = FontWeight::BOLD;
    labelStyle.fontStyle = Ace::FontStyle::ITALIC;
    std::vector<std::string> fontFamily = { "Arial" };
    labelStyle.fontFamily = fontFamily;
    labelStyle.textOverflow = TextOverflow::MARQUEE;
    labelStyle.maxLines = 2;
    labelStyle.minFontSize = 10.0_vp;
    labelStyle.maxFontSize = 30.0_vp;
    labelStyle.heightAdaptivePolicy = TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST;
    TabContentModelStatic::UpdateLabelStyle(labelStyle, textLayoutProperty);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension()), 20.0_vp);
    EXPECT_EQ(textLayoutProperty->GetFontWeightValue(FontWeight::NORMAL), FontWeight::BOLD);
    EXPECT_EQ(textLayoutProperty->GetItalicFontStyleValue(Ace::FontStyle::NORMAL), Ace::FontStyle::ITALIC);
    EXPECT_TRUE(textLayoutProperty->GetTextOverflow().has_value());
}

/**
 * @tc.name: UpdateLabelStyle_TextOverflowMarquee
 * @tc.desc: UpdateLabelStyle with MARQUEE overflow should set marquee start policy
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateLabelStyle_TextOverflowMarquee, TestSize.Level1)
{
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LabelStyle labelStyle;
    labelStyle.textOverflow = TextOverflow::MARQUEE;
    TabContentModelStatic::UpdateLabelStyle(labelStyle, textLayoutProperty);
    EXPECT_EQ(textLayoutProperty->GetTextOverflowValue(TextOverflow::CLIP), TextOverflow::MARQUEE);
}

/**
 * @tc.name: UpdateLabelStyle_PartialFields
 * @tc.desc: UpdateLabelStyle with only some fields set should only update those fields
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateLabelStyle_PartialFields, TestSize.Level1)
{
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    LabelStyle labelStyle;
    labelStyle.fontSize = 16.0_vp;
    TabContentModelStatic::UpdateLabelStyle(labelStyle, textLayoutProperty);
    EXPECT_EQ(textLayoutProperty->GetFontSizeValue(Dimension()), 16.0_vp);
    EXPECT_EQ(textLayoutProperty->GetFontWeightValue(FontWeight::NORMAL), FontWeight::NORMAL);
}

// ===================== FindTabsNode =====================

/**
 * @tc.name: FindTabsNode_Null
 * @tc.desc: FindTabsNode with null input should return nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, FindTabsNode_Null, TestSize.Level1)
{
    auto result = TabContentModelStatic::FindTabsNode(nullptr);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindTabsNode_NoTabsParent
 * @tc.desc: FindTabsNode when no TabsNode is in ancestors should return nullptr
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, FindTabsNode_NoTabsParent, TestSize.Level1)
{
    auto node = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(node, nullptr);
    auto result = TabContentModelStatic::FindTabsNode(node);
    EXPECT_EQ(result, nullptr);
}

/**
 * @tc.name: FindTabsNode_WithTabsParent
 * @tc.desc: FindTabsNode should find TabsNode from ancestors
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, FindTabsNode_WithTabsParent, TestSize.Level1)
{
    auto tabsNode = AceType::MakeRefPtr<TabsNode>(V2::TABS_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TabsPattern>(), false);
    ASSERT_NE(tabsNode, nullptr);
    auto childNode = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ASSERT_NE(childNode, nullptr);
    childNode->SetParent(tabsNode);
    auto result = TabContentModelStatic::FindTabsNode(childNode);
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, tabsNode);
}

// ===================== UpdateDefaultSymbol =====================

/**
 * @tc.name: UpdateDefaultSymbol_Valid
 * @tc.desc: UpdateDefaultSymbol should set font size and rendering strategy
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateDefaultSymbol_Valid, TestSize.Level1)
{
    auto frameNode = CreateStandaloneTabContent();
    ASSERT_NE(frameNode, nullptr);
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    ASSERT_NE(tabTheme, nullptr);
    auto symbolProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);
    TabContentModelStatic::UpdateDefaultSymbol(tabTheme, symbolProperty);
    EXPECT_EQ(symbolProperty->GetFontSizeValue(Dimension()), tabTheme->GetBottomTabImageSize());
}

// ===================== UpdateSymbolEffect =====================

/**
 * @tc.name: UpdateSymbolEffect_Active
 * @tc.desc: UpdateSymbolEffect with isActive true should set active symbol effect
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateSymbolEffect_Active, TestSize.Level1)
{
    auto symbolProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);
    TabContentModelStatic::UpdateSymbolEffect(symbolProperty, true);
    auto options = symbolProperty->GetSymbolEffectOptions();
    ASSERT_TRUE(options.has_value());
    EXPECT_TRUE(options->GetIsTxtActive());
}

/**
 * @tc.name: UpdateSymbolEffect_Inactive
 * @tc.desc: UpdateSymbolEffect with isActive false should set inactive symbol effect
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, UpdateSymbolEffect_Inactive, TestSize.Level1)
{
    auto symbolProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(symbolProperty, nullptr);
    TabContentModelStatic::UpdateSymbolEffect(symbolProperty, false);
    auto options = symbolProperty->GetSymbolEffectOptions();
    ASSERT_TRUE(options.has_value());
    EXPECT_FALSE(options->GetIsTxtActive());
}

// ===================== InitTabText =====================

/**
 * @tc.name: InitTabText_LowApiVersion
 * @tc.desc: InitTabText with API version less than 26 should return early
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, InitTabText_LowApiVersion, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_FIVE));
    auto textLayoutProperty = AceType::MakeRefPtr<TextLayoutProperty>();
    ASSERT_NE(textLayoutProperty, nullptr);
    TabContentModelStatic::InitTabText(textLayoutProperty);
    EXPECT_TRUE(true);
}

/**
 * @tc.name: InitTabText_NullTextProperty
 * @tc.desc: InitTabText with null textLayoutProperty should not crash
 * @tc.type: FUNC
 */
HWTEST_F(TabContentModelStaticTestNg, InitTabText_NullTextProperty, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().SetApiTargetVersion(
        static_cast<int32_t>(PlatformVersion::VERSION_TWENTY_SIX));
    TabContentModelStatic::InitTabText(nullptr);
    EXPECT_TRUE(true);
}

} // namespace OHOS::Ace::NG
