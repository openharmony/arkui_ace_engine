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

#include "indexer_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float INDEXER_WIDTH = 40.0f;
} // namespace

class IndexerLayoutTestNg : public IndexerTestNg {
public:
    AssertionResult IsEqual(const BorderRadiusProperty& actual, const BorderRadiusProperty& expected)
    {
        if (NearEqual(actual, expected)) {
            return AssertionSuccess();
        }
        return AssertionFailure() << "Actual: " << actual.ToString() << " Expected: " << expected.ToString();
    }

    void GetRenderContext()
    {
        auto itemNode = GetChildFrameNode(frameNode_, 0);
        indexerRenderContext_ = frameNode_->GetRenderContext();
        itemRenderContext_ = itemNode->GetRenderContext();
        if (pattern_->popupNode_) {
            auto listNode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
            auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
            auto letterNode = pattern_->GetLetterNode();
            popupRenderContext_ = pattern_->popupNode_->GetRenderContext();
            popupItemRenderContext_ = listItemNode->GetRenderContext();
            letterNodeRenderContext_ = letterNode->GetRenderContext();
        }
    }

    std::string GetArrayValueTexts()
    {
        std::string arrayValueTexts = "";
        int32_t totalChildCount = frameNode_->GetTotalChildCount();
        for (int32_t index = 0; index < totalChildCount; index++) {
            auto textLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, index);
            std::string text = textLayoutProperty->GetContent().value();
            arrayValueTexts += text == "•" ? "." : text;
        }
        return arrayValueTexts;
    }

    RefPtr<RenderContext> indexerRenderContext_;
    RefPtr<RenderContext> itemRenderContext_;
    RefPtr<RenderContext> popupRenderContext_;
    RefPtr<RenderContext> popupItemRenderContext_;
    RefPtr<RenderContext> letterNodeRenderContext_;
};

/**
 * @tc.name: Style001
 * @tc.desc: Test style with default value
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Style001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    pattern_->OnChildHover(0, true);
    GetRenderContext();
    auto itemRadiusSize = indexerTheme_->GetHoverRadiusSize();
    auto popupBackgroundColor = indexerTheme_->GetPopupBackgroundColor();
    BorderRadiusProperty expectItemBorderRadius(itemRadiusSize);
    BorderRadiusProperty expectPopupBorderRadius =
        BorderRadiusProperty(Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP));
    EXPECT_FALSE(indexerRenderContext_->GetBorderRadius().has_value());
    EXPECT_TRUE(IsEqual(itemRenderContext_->GetBorderRadius().value(), expectItemBorderRadius));
    EXPECT_TRUE(IsEqual(popupRenderContext_->GetBorderRadius().value(), expectPopupBorderRadius));
    EXPECT_FALSE(popupItemRenderContext_->GetBorderRadius().has_value());
    EXPECT_EQ(letterNodeRenderContext_->GetBackgroundColor().value(), popupBackgroundColor);
}

/**
 * @tc.name: Style002
 * @tc.desc: Test style
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Style002, TestSize.Level1)
{
    auto indexerBorderRadius = Dimension(10.f);
    auto itemBorderRadius = Dimension(5.f);
    auto popupBorderRadius = Dimension(20.f);
    auto popupItemBorderRadius = Dimension(15.f);
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetIndexerBorderRadius(indexerBorderRadius);
    model.SetItemBorderRadius(itemBorderRadius);
    model.SetPopupBorderRadius(popupBorderRadius);
    model.SetPopupItemBorderRadius(popupItemBorderRadius);
    model.SetPopupBackground(Color::RED);
    model.SetPopupUnselectedColor(Color::BLUE);
    CreateDone();
    pattern_->OnChildHover(1, true);
    GetRenderContext();
    auto itemRadiusSize = indexerTheme_->GetHoverRadiusSize();
    BorderRadiusProperty expectItemBorderRadius(itemRadiusSize);
    BorderRadiusProperty expectPopupBorderRadius =
        BorderRadiusProperty(Dimension(BUBBLE_BOX_RADIUS, DimensionUnit::VP));
    EXPECT_FALSE(indexerRenderContext_->GetBorderRadius().has_value());
    EXPECT_TRUE(IsEqual(itemRenderContext_->GetBorderRadius().value(), expectItemBorderRadius));
    EXPECT_TRUE(IsEqual(popupRenderContext_->GetBorderRadius().value(), expectPopupBorderRadius));
    EXPECT_FALSE(popupItemRenderContext_->GetBorderRadius().has_value());
    EXPECT_EQ(letterNodeRenderContext_->GetBackgroundColor().value(), Color::RED);
    auto listNode = pattern_->popupNode_->GetLastChild()->GetFirstChild();
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color::BLUE);
}

/**
 * @tc.name: Style003
 * @tc.desc: Test style with default value in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Style003, TestSize.Level1)
{
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    pattern_->OnChildHover(0, true);
    GetRenderContext();
    auto popupTitleBackground = indexerTheme_->GetPopupTitleBackground();
    BorderRadiusProperty expectBorderRadius =
        BorderRadiusProperty(Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP));
    BorderRadiusProperty expectItemBorderRadius =
        BorderRadiusProperty(Dimension(INDEXER_ITEM_DEFAULT_RADIUS, DimensionUnit::VP));
    BorderRadiusProperty expectPopupBorderRadius = BorderRadiusProperty(Dimension(BUBBLE_RADIUS, DimensionUnit::VP));
    BorderRadiusProperty expectPopupItemBorderRadius =
        BorderRadiusProperty(Dimension(BUBBLE_ITEM_RADIUS, DimensionUnit::VP));
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    EXPECT_TRUE(IsEqual(indexerRenderContext_->GetBorderRadius().value(), expectBorderRadius));
    EXPECT_TRUE(IsEqual(itemRenderContext_->GetBorderRadius().value(), expectItemBorderRadius));
    EXPECT_TRUE(IsEqual(popupRenderContext_->GetBorderRadius().value(), expectPopupBorderRadius));
    EXPECT_TRUE(IsEqual(popupItemRenderContext_->GetBorderRadius().value(), expectPopupItemBorderRadius));
    EXPECT_EQ(popupRenderContext_->GetBackBlurStyle().value(), styleOption);
    EXPECT_EQ(letterNodeRenderContext_->GetBackgroundColor().value(), popupTitleBackground);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: Style004
 * @tc.desc: Test style in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Style004, TestSize.Level1)
{
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    auto indexerBorderRadius = Dimension(10.f);
    auto itemBorderRadius = Dimension(5.f);
    auto popupBorderRadius = Dimension(20.f);
    auto popupItemBorderRadius = Dimension(15.f);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::REGULAR;
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetIndexerBorderRadius(indexerBorderRadius);
    model.SetItemBorderRadius(itemBorderRadius);
    model.SetPopupBorderRadius(popupBorderRadius);
    model.SetPopupItemBorderRadius(popupItemBorderRadius);
    model.SetPopupBackgroundBlurStyle(styleOption);
    model.SetPopupTitleBackground(Color::RED);
    CreateDone();
    pattern_->OnChildHover(0, true);
    GetRenderContext();
    BorderRadiusProperty expectBorderRadius(indexerBorderRadius);
    BorderRadiusProperty expectItemBorderRadius(itemBorderRadius);
    BorderRadiusProperty expectPopupBorderRadius(popupBorderRadius);
    BorderRadiusProperty expectPopupItemBorderRadius(popupItemBorderRadius);
    EXPECT_TRUE(IsEqual(indexerRenderContext_->GetBorderRadius().value(), expectBorderRadius));
    EXPECT_TRUE(IsEqual(itemRenderContext_->GetBorderRadius().value(), expectItemBorderRadius));
    EXPECT_TRUE(IsEqual(popupRenderContext_->GetBorderRadius().value(), expectPopupBorderRadius));
    EXPECT_TRUE(IsEqual(popupItemRenderContext_->GetBorderRadius().value(), expectPopupItemBorderRadius));
    EXPECT_EQ(popupRenderContext_->GetBackBlurStyle().value(), styleOption);
    EXPECT_EQ(letterNodeRenderContext_->GetBackgroundColor().value(), Color::RED);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerModelNGTest001
 * @tc.desc: Test Create func with special arg
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create with normal arg.
     */
    CreateIndexer(GetLongArrayValue(), 5);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), GetLongArrayValue());
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 5);

    /**
     * @tc.steps: step2. Set selected < 0.
     * @tc.expected: The selected would be 0.
     */
    ClearOldNodes();
    CreateIndexer(GetLongArrayValue(), -1);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);

    /**
     * @tc.steps: step3. Set selected > array size.
     * @tc.expected: The selected would be 0.
     */
    ClearOldNodes();
    CreateIndexer(GetLongArrayValue(), GetLongArrayValue().size() + 11);
    CreateDone();
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
}

/**
 * @tc.name: IndexerModelNGTest002
 * @tc.desc: Test all the properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetSelectedColor(Color(0x00000000));
    model.SetColor(Color(0x00000000));
    model.SetPopupColor(Color(0x00000000));
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(true);
    model.SetItemSize(Dimension(24));
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(Color(0x00000000));
    model.SetPopupSelectedColor(Color(0x00000000));
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24));
    model.SetFontWeight(FontWeight::MEDIUM);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), GetLongArrayValue());
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color(0x00000000));
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color(0x00000000));
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color(0x00000000));
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
    auto json = JsonUtil::Create(true);
    InspectorFilter filter;
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_NE(json, nullptr);
}

/**
 * @tc.name: IndexerModelNGTest003
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetSelectedColor(std::nullopt);
    model.SetColor(std::nullopt);
    model.SetPopupColor(std::nullopt);
    model.SetItemSize(Dimension(-1));
    model.SetSelected(-1);
    model.SetPopupPositionX(std::nullopt);
    model.SetPopupPositionY(std::nullopt);
    model.SetSelectedBackgroundColor(std::nullopt);
    model.SetPopupBackground(std::nullopt);
    model.SetPopupSelectedColor(std::nullopt);
    model.SetPopupUnselectedColor(std::nullopt);
    model.SetPopupItemBackground(std::nullopt);
    model.SetPopupHorizontalSpace(Dimension(-1));
    model.SetFontSize(Dimension());
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_FALSE(layoutProperty_->GetSelectedColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupColor().has_value());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_FALSE(layoutProperty_->GetPopupPositionX().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupPositionY().has_value());
    EXPECT_FALSE(paintProperty_->GetSelectedBackgroundColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerModelNGTest004
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest004, TestSize.Level1)
{
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::COMPONENT_REGULAR;
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetPopupItemBorderRadius(Dimension(24));
    model.SetPopupBorderRadius(Dimension(28));
    model.SetItemBorderRadius(Dimension(12));
    model.SetIndexerBorderRadius(Dimension(16));
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    model.SetPopupTitleBackground(Color(0x00000000));
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_EQ(paintProperty_->GetPopupItemBorderRadiusValue(), Dimension(24));
    EXPECT_EQ(paintProperty_->GetPopupBorderRadiusValue(), Dimension(28));
    EXPECT_EQ(paintProperty_->GetItemBorderRadiusValue(), Dimension(12));
    EXPECT_EQ(paintProperty_->GetIndexerBorderRadiusValue(), Dimension(16));
    EXPECT_EQ(paintProperty_->GetPopupBackgroundBlurStyleValue(), indexerBlurStyle);
    EXPECT_EQ(paintProperty_->GetPopupTitleBackgroundValue(), Color(0x00000000));
}

/**
 * @tc.name: IndexerModelNGTest005
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest005, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetPopupTitleBackground(std::nullopt);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_FALSE(paintProperty_->GetPopupTitleBackground().has_value());
}

/**
 * @tc.name: IndexerModelNGTest006
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer.
     */
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    model.SetFontSize(AceType::RawPtr(frameNode_), Dimension());
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetPopupUnselectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupItemBackground(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetSelectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupBackground(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetSelected(AceType::RawPtr(frameNode_), -1);
    model.SetPopupSelectedColor(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(-1));
    model.SetPopupPositionX(AceType::RawPtr(frameNode_), std::nullopt);
    model.SetPopupPositionY(AceType::RawPtr(frameNode_), std::nullopt);

    EXPECT_FALSE(layoutProperty_->GetSelectedColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetColor().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupColor().has_value());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(INDEXER_ITEM_SIZE, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_FALSE(layoutProperty_->GetPopupPositionX().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupPositionY().has_value());
    EXPECT_FALSE(paintProperty_->GetSelectedBackgroundColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupBackground().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupSelectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupUnselectedColor().has_value());
    EXPECT_FALSE(paintProperty_->GetPopupItemBackground().has_value());
    EXPECT_FALSE(layoutProperty_->GetPopupHorizontalSpace().has_value());
    EXPECT_FALSE(layoutProperty_->GetFontSize().has_value());
}

/**
 * @tc.name: IndexerModelNGTest007
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer.
     */
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    CreateDone();
    model.SetSelectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetSelectedBackgroundColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupBackground(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetUsingPopup(AceType::RawPtr(frameNode_), true);
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(24));
    model.SetAlignStyle(AceType::RawPtr(frameNode_), 0);
    model.SetPopupHorizontalSpace(AceType::RawPtr(frameNode_), Dimension(50));
    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    model.SetPopupPositionX(AceType::RawPtr(frameNode_), Dimension(-96.f, DimensionUnit::VP));
    model.SetPopupPositionY(AceType::RawPtr(frameNode_), Dimension(48.f, DimensionUnit::VP));
    model.SetPopupItemBackground(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupSelectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetPopupUnselectedColor(AceType::RawPtr(frameNode_), Color::WHITE);
    model.SetFontSize(AceType::RawPtr(frameNode_), Dimension(24));
    model.SetFontWeight(AceType::RawPtr(frameNode_), FontWeight::MEDIUM);

    EXPECT_EQ(layoutProperty_->GetArrayValueValue(), GetLongArrayValue());
    EXPECT_EQ(layoutProperty_->GetSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetPopupColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetSelectedBackgroundColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupBackgroundValue(), Color::WHITE);
    EXPECT_TRUE(layoutProperty_->GetUsingPopupValue());
    EXPECT_EQ(layoutProperty_->GetItemSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetAlignStyleValue(), AlignStyle::LEFT);
    EXPECT_EQ(layoutProperty_->GetPopupHorizontalSpaceValue(), Dimension(50));
    EXPECT_EQ(layoutProperty_->GetSelectedValue(), 0);
    EXPECT_EQ(layoutProperty_->GetPopupPositionXValue(), Dimension(-96.f, DimensionUnit::VP));
    EXPECT_EQ(layoutProperty_->GetPopupPositionYValue(), Dimension(48.f, DimensionUnit::VP));
    EXPECT_EQ(paintProperty_->GetPopupItemBackgroundValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupSelectedColorValue(), Color::WHITE);
    EXPECT_EQ(paintProperty_->GetPopupUnselectedColorValue(), Color::WHITE);
    EXPECT_EQ(layoutProperty_->GetFontSizeValue(), Dimension(24));
    EXPECT_EQ(layoutProperty_->GetFontWeightValue(), FontWeight::MEDIUM);
}

/**
 * @tc.name: IndexerModelNGTest008
 * @tc.desc: Test newly added properties of indexer.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, IndexerModelNGTest008, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAdaptiveWidth(true);
    CreateDone();

    /**
     * @tc.steps: step1. Get properties.
     * @tc.expected: Properties are correct.
     */
    EXPECT_TRUE(layoutProperty_->GetAdaptiveWidthValue());
}

/**
 * @tc.name: OnModifyDone001
 * @tc.desc: Test OnModifyDone
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, OnModifyDone001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    CreateDone();

    /**
     * @tc.steps: step1. change UsingPopup
     * @tc.expected: would trigger RemoveBubble
     */
    model.SetUsingPopup(AceType::RawPtr(frameNode_), false);
    pattern_->OnModifyDone(); // trigger RemoveBubble
    EXPECT_FALSE(pattern_->isPopup_);
    EXPECT_EQ(pattern_->popupNode_, nullptr);
}

/**
 * @tc.name: OnModifyDone002
 * @tc.desc: Test OnModifyDone when autoCollapse is close
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, OnModifyDone002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(false);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(GetArrayValueTexts(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

/**
 * @tc.name: OnModifyDone003
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 5+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, OnModifyDone003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), "A.G.M.S.Z");
}

/**
 * @tc.name: AutoCollapse001
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and mode is 7+1
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(6, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 60.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), "A.G.M.S.Z");
}

/**
 * @tc.name: AutoCollapse002
 * @tc.desc: Test OnModifyDone when autoCollapse is open, item size is larger than pattern height
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(2000, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), "A.G.M.S.Z");
}

/**
 * @tc.name: AutoCollapse003
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and created arrayValue size is less than 9
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetShortArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), "ABCDEFGHI");
}

/**
 * @tc.name: AutoCollapse004
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse004, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetShortArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), "ABCDEFGHI");
}

/**
 * @tc.name: AutoCollapse005
 * @tc.desc: Test OnModifyDone when autoCollapse is open, and arrayValue size is more than 9,
 *           pattern height is not enough to contain all items
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse005, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetAutoCollapseArrayValue(), 0);
    model.SetAutoCollapse(true);
    model.SetItemSize(Dimension(10, DimensionUnit::VP));
    pattern_->maxContentHeight_ = 100.f;
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), "#A.C.F.I.L");
}

/**
 * @tc.name: PopUpLayout001
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, PopUpLayout001, TestSize.Level1)
{
    /**
     * @tc.case: case1: popup position is default.
     */
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-96), Dimension(48)));

    /**
     * @tc.case: case2: popup position is custom.
     */
    std::optional<Dimension> xOpt = Dimension(30);
    std::optional<Dimension> yOpt = Dimension(20);
    model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutProperty2 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty2, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-66), Dimension(20)));

    /**
     * @tc.case: case3: popup horizontal space is custom.
     */
    ClearOldNodes();
    xOpt = Dimension(30);
    yOpt = Dimension(20);
    model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetPopupHorizontalSpace(Dimension(50));
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutProperty3 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty3, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(-106), Dimension(20)));

    /**
     * @tc.case: case4: align is left.
     */
    ClearOldNodes();
    xOpt = Dimension(30);
    yOpt = Dimension(-20);
    model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetAlignStyle(0);
    model.SetUsingPopup(true);
    model.SetPopupPositionX(xOpt);
    model.SetPopupPositionY(yOpt);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutProperty4 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    ASSERT_NE(indexerLayoutProperty4, nullptr);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty4, 40);
    EXPECT_EQ(offset, OffsetT<Dimension>(Dimension(50), Dimension(-20)));
}

/**
 * @tc.name: PopUpLayout002
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, PopUpLayout002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto userDefinePositionX = Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionRightX = userDefinePositionX + INDEXER_WIDTH / 2;
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionLeftX = -userDefinePositionX + INDEXER_WIDTH / 2 - bubbleSize;

    /**
     * case: case1: popup position is left.
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::LEFT);
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));

    /**
     * case: case2: popup position is right.
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::RIGHT);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));
}

/**
 * @tc.name: PopUpLayout003
 * @tc.desc: Test indexer layoutAlgorithm GetPositionOfPopupNode function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, PopUpLayout003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 2);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    auto indexerLayoutAlgorithm = AceType::DynamicCast<IndexerLayoutAlgorithm>(pattern_->CreateLayoutAlgorithm());
    auto indexerLayoutProperty1 = pattern_->GetLayoutProperty<IndexerLayoutProperty>();
    auto userDefinePositionX = Dimension(NG::BUBBLE_POSITION_X, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionRightX = userDefinePositionX + INDEXER_WIDTH / 2;
    auto bubbleSize = Dimension(BUBBLE_BOX_SIZE, DimensionUnit::VP).ConvertToPx();
    auto userDefinePositionLeftX = -userDefinePositionX + INDEXER_WIDTH / 2 - bubbleSize;

    /**
     * case: case1: popup position is default(END) and layoutDirection is RTL
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::RTL);
    auto offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));

    /**
     * case: case2: popup position is default(END) and layoutDirection is LTR
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::LTR);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));

    /**
     * case: case3: popup position is START and layoutDirection is RTL
     */
    indexerLayoutProperty1->UpdateAlignStyle(NG::AlignStyle::START);
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::RTL);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionLeftX));

    /**
     * case: case4: popup position is START and layoutDirection is LTR
     */
    indexerLayoutProperty1->UpdateLayoutDirection(TextDirection::LTR);
    offset = indexerLayoutAlgorithm->GetPositionOfPopupNode(indexerLayoutProperty1, INDEXER_WIDTH);
    EXPECT_EQ(offset.GetX(), Dimension(userDefinePositionRightX));
}
} // namespace OHOS::Ace::NG
