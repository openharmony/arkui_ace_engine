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

#include "core/components_ng/pattern/list/list_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float INDEXER_WIDTH = 40.0f;
} // namespace

class IndexerLayoutTestNg : public IndexerTestNg {
public:
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

    std::u16string GetArrayValueTexts()
    {
        std::u16string arrayValueTexts;
        int32_t totalChildCount = frameNode_->GetTotalChildCount();
        for (int32_t index = 0; index < totalChildCount; index++) {
            auto textLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, index);
            std::u16string text = textLayoutProperty->GetContent().value_or(u"");
            arrayValueTexts += text == u"•" ? u"." : text; // avoid EXPECT error
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
    auto listNode = AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetLastChild()->GetFirstChild());
    auto listItemNode = AceType::DynamicCast<FrameNode>(listNode->GetFirstChild());
    auto textNode = AceType::DynamicCast<FrameNode>(listItemNode->GetFirstChild());
    auto textLayoutProperty = textNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(textLayoutProperty->GetTextColor().value(), Color::BLUE);
    auto listPaintProperty = listNode->GetPaintProperty<ScrollablePaintProperty>();
    EXPECT_NE(listPaintProperty, nullptr);
    EXPECT_FALSE(listPaintProperty->GetFadingEdgeValue(true));
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
 * @tc.name: Font001
 * @tc.desc: Test SelectedFont/PopupFont/Font default theme
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Font001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    // defaultFont
    auto defaultFont = indexerTheme_->GetDefaultTextStyle();
    auto itemLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 0);
    EXPECT_EQ(itemLayoutProperty->GetFontSize(), defaultFont.GetFontSize());
    EXPECT_EQ(itemLayoutProperty->GetFontFamily(), defaultFont.GetFontFamilies());
    EXPECT_EQ(itemLayoutProperty->GetFontWeight(), defaultFont.GetFontWeight());
    EXPECT_EQ(itemLayoutProperty->GetItalicFontStyle(), defaultFont.GetFontStyle());
    // selectedFont
    pattern_->OnChildHover(0, true);
    auto selectedFont = indexerTheme_->GetSelectTextStyle();
    EXPECT_EQ(itemLayoutProperty->GetFontSize(), selectedFont.GetFontSize());
    EXPECT_EQ(itemLayoutProperty->GetFontFamily(), selectedFont.GetFontFamilies());
    EXPECT_EQ(itemLayoutProperty->GetFontWeight(), selectedFont.GetFontWeight());
    EXPECT_EQ(itemLayoutProperty->GetItalicFontStyle(), selectedFont.GetFontStyle());
    // popupTextFont
    auto popupTextFont = indexerTheme_->GetPopupTextStyle();
    auto letterNode = pattern_->GetLetterNode();
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(letterLayoutProperty->GetFontSize(), popupTextFont.GetFontSize());
    EXPECT_EQ(letterLayoutProperty->GetFontFamily(), popupTextFont.GetFontFamilies());
    EXPECT_EQ(letterLayoutProperty->GetFontWeight(), popupTextFont.GetFontWeight());
    EXPECT_EQ(letterLayoutProperty->GetItalicFontStyle(), popupTextFont.GetFontStyle());
}

/**
 * @tc.name: Font002
 * @tc.desc: Test SelectedFont/PopupFont/Font
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, Font002, TestSize.Level1)
{
    std::optional<Dimension> fontSize = Dimension(10);
    std::optional<FontWeight> fontWeight = FontWeight::W200;
    std::optional<std::vector<std::string>> fontFamily = std::vector<std::string>({ "abc" });
    std::optional<OHOS::Ace::FontStyle> fontStyle = OHOS::Ace::FontStyle::ITALIC;
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetSelectedFont(fontSize, fontWeight, fontFamily, fontStyle);
    model.SetPopupFont(fontSize, fontWeight, fontFamily, fontStyle);
    model.SetFont(fontSize, fontWeight, fontFamily, fontStyle);
    CreateDone();
    // defaultFont
    auto itemLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(frameNode_, 0);
    EXPECT_EQ(itemLayoutProperty->GetFontSize(), fontSize);
    EXPECT_EQ(itemLayoutProperty->GetFontFamily(), fontFamily);
    EXPECT_EQ(itemLayoutProperty->GetFontWeight(), fontWeight);
    EXPECT_EQ(itemLayoutProperty->GetItalicFontStyle(), fontStyle);
    // selectedFont
    pattern_->OnChildHover(0, true);
    EXPECT_EQ(itemLayoutProperty->GetFontSize(), fontSize);
    EXPECT_EQ(itemLayoutProperty->GetFontFamily(), fontFamily);
    EXPECT_EQ(itemLayoutProperty->GetFontWeight(), fontWeight);
    EXPECT_EQ(itemLayoutProperty->GetItalicFontStyle(), fontStyle);
    // popupTextFont
    auto letterNode = pattern_->GetLetterNode();
    auto letterLayoutProperty = letterNode->GetLayoutProperty<TextLayoutProperty>();
    EXPECT_EQ(letterLayoutProperty->GetFontSize(), fontSize);
    EXPECT_EQ(letterLayoutProperty->GetFontFamily(), fontFamily);
    EXPECT_EQ(letterLayoutProperty->GetFontWeight(), fontWeight);
    EXPECT_EQ(letterLayoutProperty->GetItalicFontStyle(), fontStyle);
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
    std::optional<Dimension> fontSize = Dimension(10);
    std::optional<FontWeight> fontWeight = FontWeight::W200;
    std::optional<std::vector<std::string>> fontFamily = std::vector<std::string>({ "abc", "def" });
    std::optional<OHOS::Ace::FontStyle> fontStyle = OHOS::Ace::FontStyle::ITALIC;
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
    model.SetSelectedFont(fontSize, fontWeight, fontFamily, fontStyle);
    model.SetPopupFont(fontSize, fontWeight, fontFamily, fontStyle);
    model.SetFont(fontSize, fontWeight, fontFamily, fontStyle);
    CreateDone();

    InspectorFilter filter;
    auto json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("selected"), "0");
    EXPECT_EQ(json->GetString("color"), "#00000000");
    EXPECT_EQ(json->GetString("selectedColor"), "#00000000");
    EXPECT_EQ(json->GetString("popupColor"), "#00000000");
    EXPECT_EQ(json->GetString("usingPopup"), "true");
    EXPECT_EQ(json->GetString("itemSize"), "24.00px");
    EXPECT_EQ(json->GetString("alignStyle"), "IndexerAlign.Left");
    EXPECT_EQ(json->GetString("popupPosition"), "");
    EXPECT_EQ(json->GetString("arrayValue"), "");
    EXPECT_EQ(json->GetString("font"), "");
    EXPECT_EQ(json->GetString("selectedFont"), "");
    EXPECT_EQ(json->GetString("popupFont"), "");
    EXPECT_EQ(json->GetString("popupItemFontSize"), "24.00px");
    EXPECT_EQ(json->GetString("popupItemFontWeight"), "FontWeight.Medium");
    EXPECT_EQ(json->GetString("autoCollapse"), "false");
    EXPECT_EQ(json->GetString("popupHorizontalSpace"), "50.00px");
    EXPECT_EQ(json->GetString("adaptiveWidth"), "false");
    EXPECT_EQ(json->GetString("enableHapticFeedback"), "true");

    model.SetAlignStyle(AceType::RawPtr(frameNode_), 1);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("alignStyle"), "IndexerAlign.Right");

    model.SetAlignStyle(AceType::RawPtr(frameNode_), 2);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("alignStyle"), "IndexerAlign.Start");

    model.SetAlignStyle(AceType::RawPtr(frameNode_), 3);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetString("alignStyle"), "IndexerAlign.End");

    std::string attr = "editable";
    filter.AddFilterAttr(attr);
    json = JsonUtil::Create(true);
    layoutProperty_->ToJsonValue(json, filter);
    EXPECT_EQ(json->ToString(), "{}");
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
    model.SetPopupTitleBackground(AceType::RawPtr(frameNode_), std::nullopt);

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
    EXPECT_FALSE(paintProperty_->GetPopupTitleBackground().has_value());
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
    model.SetPopupTitleBackground(AceType::RawPtr(frameNode_), Color::WHITE);

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
    EXPECT_EQ(paintProperty_->GetPopupTitleBackground(), Color::WHITE);
}

/**
 * @tc.name: AdaptiveWidth001
 * @tc.desc: Test AdaptiveWidth
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AdaptiveWidth001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetAdaptiveWidth(true);
    CreateDone();
    const float padding = INDEXER_PADDING_LEFT * 2;
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().Width(), INDEXER_ITEM_SIZE + padding);

    /**
     * @tc.steps: step1. Set bigger itemSize
     */
    float itemSize = INDEXER_ITEM_SIZE + 10.f;
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(itemSize));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().Width(), itemSize + padding);

    /**
     * @tc.steps: step2. Set smaller itemSize
     */
    itemSize = INDEXER_ITEM_SIZE - 10.f;
    model.SetItemSize(AceType::RawPtr(frameNode_), Dimension(itemSize));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().Width(), itemSize + padding);

    /**
     * @tc.steps: step3. Show popup
     */
    model.SetUsingPopup(AceType::RawPtr(frameNode_), true);
    model.SetOnRequestPopupData(AceType::RawPtr(frameNode_), GetPopupData());
    frameNode_->MarkModifyDone();
    FlushUITasks();
    pattern_->MoveIndexByStep(1);
    FlushUITasks();
    EXPECT_NE(pattern_->popupNode_, nullptr);
    EXPECT_EQ(frameNode_->GetGeometryNode()->GetFrameRect().Width(), itemSize + padding);
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
 * @tc.name: AutoCollapse001
 * @tc.desc: Test autoCollapse with long arrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is false
     * @tc.expected: Not fold
     */
    std::vector arrayValue = GetLongArrayValue();
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(false);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    /**
     * @tc.steps: step2. AutoCollapse is true, Set Height enough to contain short fold mode items
     * @tc.expected: Short fold
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), u"A.G.M.S.Z");

    /**
     * @tc.steps: step3. Set Height enough to contain long fold mode items
     * @tc.expected: Long fold
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
    EXPECT_EQ(GetArrayValueTexts(), u"A.E.I.M.Q.U.Z");

    /**
     * @tc.steps: step4. Set Height enough to contain all items
     * @tc.expected: Not fold
     */
    ViewAbstract::SetHeight(
        AceType::RawPtr(frameNode_), CalcLength(INDEXER_ITEM_SIZE * arrayValue.size() + INDEXER_PADDING_TOP * 2));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

/**
 * @tc.name: AutoCollapse002
 * @tc.desc: Test autoCollapse with long arrayValue and "#"
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is false
     * @tc.expected: Not fold
     */
    std::vector arrayValue = GetLongArrayValue();
    arrayValue.insert(arrayValue.begin(), "#");
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(false);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(GetArrayValueTexts(), u"#ABCDEFGHIJKLMNOPQRSTUVWXYZ");

    /**
     * @tc.steps: step2. AutoCollapse is true
     * @tc.expected: Short fold
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT + INDEXER_ITEM_SIZE));
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), u"#A.G.M.S.Z");

    /**
     * @tc.steps: step3. Set Height enough to contain long fold mode items
     * @tc.expected: Long fold
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT + INDEXER_ITEM_SIZE));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
    EXPECT_EQ(GetArrayValueTexts(), u"#A.E.I.M.Q.U.Z");

    /**
     * @tc.steps: step4. Set Height enough to contain all items
     * @tc.expected: Not fold
     */
    ViewAbstract::SetHeight(
        AceType::RawPtr(frameNode_), CalcLength(INDEXER_ITEM_SIZE * arrayValue.size() + INDEXER_PADDING_TOP * 2));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"#ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

/**
 * @tc.name: AutoCollapse003
 * @tc.desc: Test autoCollapse with mid arrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is true
     * @tc.expected: Not fold
     */
    std::vector arrayValue = GetMidArrayValue();
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(true);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHIJKLM");

    /**
     * @tc.steps: step2. Set Height enough to contain short fold mode items
     * @tc.expected: Short fold
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), u"A.D.G.J.M");
}

/**
 * @tc.name: AutoCollapse004
 * @tc.desc: Test autoCollapse with short arrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is true
     * @tc.expected: Not fold
     */
    std::vector arrayValue = GetShortArrayValue();
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(true);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHI");
}

/**
 * @tc.name: AutoCollapse005
 * @tc.desc: Test autoCollapse with enough and insufficient height
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, AutoCollapse005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is true
     * @tc.expected: Not fold
     */
    std::vector arrayValue = GetMidArrayValue();
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(true);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHIJKLM");

    /**
     * @tc.steps: step2. Set Height more than the height of all item
     * @tc.expected: item height is equal with item size
     */
    ViewAbstract::SetHeight(
        AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT + INDEXER_THIRTEEN_CHARACTERS_CHECK));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::NONE);
    EXPECT_EQ(GetArrayValueTexts(), u"ABCDEFGHIJKLM");
    EXPECT_EQ(pattern_->maxContentHeight_, (INDEXER_ITEM_SIZE + 1) * INDEXER_THIRTEEN_CHARACTERS_CHECK);
    EXPECT_EQ(pattern_->itemHeight_, INDEXER_ITEM_SIZE);

    /**
     * @tc.steps: step3. Set Height less than the height of all item but more than the height of five mode
     * @tc.expected: item height is equal with item size
     */
    ViewAbstract::SetHeight(
        AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT - INDEXER_THIRTEEN_CHARACTERS_CHECK));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->maxContentHeight_, (INDEXER_ITEM_SIZE - 1) * INDEXER_THIRTEEN_CHARACTERS_CHECK);
    EXPECT_EQ(pattern_->itemHeight_, INDEXER_ITEM_SIZE - 1);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), u"A.D.G.J.M");
    EXPECT_EQ(pattern_->maxContentHeight_, (INDEXER_ITEM_SIZE - 1) * INDEXER_THIRTEEN_CHARACTERS_CHECK);
    EXPECT_EQ(pattern_->itemHeight_, INDEXER_ITEM_SIZE);

    /**
     * @tc.steps: step4. Set Height less than the height of five mode
     * @tc.expected: item height is the average of the height without padding
     */
    ViewAbstract::SetHeight(
        AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT - INDEXER_NINE_CHARACTERS_CHECK));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(GetArrayValueTexts(), u"A.D.G.J.M");
    EXPECT_EQ(pattern_->maxContentHeight_, (INDEXER_ITEM_SIZE - 1) * INDEXER_NINE_CHARACTERS_CHECK);
    EXPECT_EQ(pattern_->itemHeight_, INDEXER_ITEM_SIZE - 1);
}

/**
 * @tc.name: InitializingSelected001
 * @tc.desc: Test the initializing Selected in diff IndexerCollapsingMode
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, InitializingSelected001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is false
     * @tc.expected: Not fold, the initializing Selected is correct
     */
    std::vector arrayValue = GetLongArrayValue();
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(false);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    model.SetSelected(AceType::RawPtr(frameNode_), 1);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");

    /**
     * @tc.steps: step2. AutoCollapse is true
     * @tc.expected: Short fold, the initializing Selected is correct
     */
    // "A•G•M•S•Z"
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");
    // select A
    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");
    // select •
    model.SetSelected(AceType::RawPtr(frameNode_), 2);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");
    // select •
    model.SetSelected(AceType::RawPtr(frameNode_), 5);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");

    /**
     * @tc.steps: step3. Set Height enough to contain long fold mode items
     * @tc.expected: Long fold, the initializing Selected is correct
     */
    // "A.E.I.M.Q.U.Z"
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
    EXPECT_EQ(pattern_->GetSelected(), 3);
    EXPECT_EQ(accessibilityProperty_->GetText(), "F");

    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    model.SetSelected(AceType::RawPtr(frameNode_), 1);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");
}

/**
 * @tc.name: InitializingSelected002
 * @tc.desc: Test the initializing Selected in diff IndexerCollapsingMode with "#"
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, InitializingSelected002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. AutoCollapse is false
     * @tc.expected: Not fold, the initializing Selected is correct
     */
    std::vector arrayValue = GetLongArrayValue();
    arrayValue.insert(arrayValue.begin(), "#");
    IndexerModelNG model = CreateIndexer(arrayValue, 0);
    model.SetAutoCollapse(false);
    CreateDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::INVALID);
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "#");

    model.SetSelected(AceType::RawPtr(frameNode_), 1);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    /**
     * @tc.steps: step2. AutoCollapse is true
     * @tc.expected: Short fold, the initializing Selected is correct
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(SHORT_INDEXER_HEIGHT));
    model.SetAutoCollapse(AceType::RawPtr(frameNode_), true);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::FIVE);
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "#");

    model.SetSelected(AceType::RawPtr(frameNode_), 2);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 2);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");

    /**
     * @tc.steps: step3. Set Height enough to contain long fold mode items
     * @tc.expected: Long fold, the initializing Selected is correct
     */
    ViewAbstract::SetHeight(AceType::RawPtr(frameNode_), CalcLength(LONG_INDEXER_HEIGHT + INDEXER_ITEM_SIZE));
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->lastCollapsingMode_, IndexerCollapsingMode::SEVEN);
    EXPECT_EQ(pattern_->GetSelected(), 2);
    EXPECT_EQ(accessibilityProperty_->GetText(), "B");

    model.SetSelected(AceType::RawPtr(frameNode_), 0);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(accessibilityProperty_->GetText(), "#");

    model.SetSelected(AceType::RawPtr(frameNode_), 1);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");
}

/**
 * @tc.name: ArrayValue001
 * @tc.desc: Test the initializing ArrayValue
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, ArrayValue001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Change ArrayValue
     * @tc.expected: The items number changed
     */
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 26);

    model.SetArrayValue(AceType::RawPtr(frameNode_), GetShortArrayValue());
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 9);

    /**
     * @tc.steps: step1. Change ArrayValue when show popup
     * @tc.expected: The items number changed
     */
    pattern_->MoveIndexByStep(1);
    EXPECT_EQ(pattern_->GetSelected(), 1);
    EXPECT_NE(pattern_->popupNode_, nullptr);
    EXPECT_TRUE(layoutProperty_->GetIsPopupValue(false));
    model.SetArrayValue(AceType::RawPtr(frameNode_), GetMidArrayValue());
    frameNode_->MarkModifyDone();
    FlushUITasks();
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->GetSelected(), 0);
    EXPECT_EQ(frameNode_->GetTotalChildCount(), 14); // items + popup
    EXPECT_TRUE(layoutProperty_->GetIsPopupValue(false));
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

/**
 * @tc.name: BubbleSize001
 * @tc.desc: Test UpdateBubbleSize function, the Bubble size will change in diff PlatformVersion
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, BubbleSize001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();

    /**
     * @tc.steps: step1. childPressIndex_ less than 0.
     * @tc.expected: verify size.
     */
    const int32_t popupDataSize = 2;
    const int32_t popupSize = popupDataSize + 1;
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(
        pattern_->popupNode_->GetGeometryNode()->GetFrameSize(), SizeF(BUBBLE_BOX_SIZE, BUBBLE_BOX_SIZE * popupSize)));

    /**
     * @tc.steps: step2. VERSION_TWELVE
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->popupNode_->GetGeometryNode()->GetFrameSize(),
        SizeF(BUBBLE_BOX_SIZE, (BUBBLE_ITEM_SIZE + BUBBLE_DIVIDER_SIZE) * popupSize + BUBBLE_DIVIDER_SIZE)));
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: BubbleSize002
 * @tc.desc: Test UpdateBubbleSize function, the BubbleSize would less than maxSize
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, BubbleSize002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    // PopupData size greater than maxItemsSize
    model.SetOnRequestPopupData(GetMorePopupData2());
    CreateDone();

    /**
     * @tc.steps: step1. has popListData and popListData size equal INDEXER_BUBBLE_MAXSIZE.
     * @tc.expected: verify size.
     */
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->popupNode_->GetGeometryNode()->GetFrameSize(),
        SizeF(BUBBLE_BOX_SIZE, BUBBLE_BOX_SIZE * (INDEXER_BUBBLE_MAXSIZE + 1))));

    /**
     * @tc.steps: step2. VERSION_TWELVE
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(
        pattern_->popupNode_->GetGeometryNode()->GetFrameSize(), SizeF(BUBBLE_BOX_SIZE, BUBBLE_COLUMN_MAX_SIZE)));
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: BubbleSize003
 * @tc.desc: Test UpdateBubbleSize function with AutoCollapse, the maxItemsSize is different
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, BubbleSize003, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetMorePopupData());
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    frameNode_->MarkModifyDone();

    /**
     * @tc.steps: step1. has popListData and popListData size equal INDEXER_BUBBLE_MAXSIZE.
     * @tc.expected: verify size.
     */
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->popupNode_->GetGeometryNode()->GetFrameSize(),
        SizeF(BUBBLE_BOX_SIZE, BUBBLE_BOX_SIZE * INDEXER_BUBBLE_MAXSIZE_COLLAPSED)));

    /**
     * @tc.steps: step2. VERSION_TWELVE
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    pattern_->MoveIndexByStep(1);
    OnPopupTouchDown(TouchType::DOWN); // trigger UpdateBubbleSize
    FlushUITasks();
    EXPECT_TRUE(IsEqual(pattern_->popupNode_->GetGeometryNode()->GetFrameSize(),
        SizeF(BUBBLE_BOX_SIZE, BUBBLE_COLLAPSE_COLUMN_MAX_SIZE)));
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: DrawPopupListGradient001
 * @tc.desc: Test DrawPopupListGradient, when Popup is long that can scroll,
 * the popup will change color in diff position
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, DrawPopupListGradient001, TestSize.Level1)
{
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetMorePopupData2());
    CreateDone();

    /**
     * @tc.steps: step1. Show popupNode_, list at top
     * @tc.expected: Colors.size is 3
     */
    pattern_->MoveIndexByOffset(Offset(0, 10));
    FlushUITasks();
    auto stackNode = AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetLastChild());
    auto stackRenderContext = stackNode->GetRenderContext();
    auto listNode = AceType::DynamicCast<FrameNode>(stackNode->GetFirstChild());
    auto listPattern = listNode->GetPattern<ListPattern>();
    EXPECT_TRUE(listPattern->IsAtTop());
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);

    /**
     * @tc.steps: step2. list scroll to middle
     * @tc.expected: Colors.size is 4
     */
    listPattern->ScrollTo(20);
    FlushUITasks();
    EXPECT_FALSE(listPattern->IsAtTop());
    EXPECT_FALSE(listPattern->IsAtBottom());
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 4);

    /**
     * @tc.steps: step3. list scroll to bottom
     * @tc.expected: Colors.size is 3
     */
    listPattern->ScrollTo(100);
    FlushUITasks();
    EXPECT_TRUE(listPattern->IsAtBottom());
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);

    /**
     * @tc.steps: step4. list scroll back to top
     * @tc.expected: Colors.size is 3
     */
    listPattern->ScrollTo(0);
    FlushUITasks();
    EXPECT_TRUE(listPattern->IsAtTop());
    EXPECT_EQ(stackRenderContext->GetLinearGradientValue(Gradient()).GetColors().size(), 3);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: PopupClickStyle001
 * @tc.desc: Test ChangeListItemsSelectedStyle, the text color will change by click
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, PopupClickStyle001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetPopupSelectedColor(Color::GREEN);
    model.SetPopupUnselectedColor(Color::BLUE);
    model.SetPopupItemBackground(Color::GRAY);
    CreateDone();

    /**
     * @tc.steps: step1. Show popupNode_
     */
    pattern_->MoveIndexByStep(1);
    auto firstListItemNode = GetListItemNode(0);
    auto firstTextLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(firstListItemNode, 0);
    auto secondListItemNode = GetListItemNode(1);
    auto secondTextLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(secondListItemNode, 0);

    /**
     * @tc.steps: step2. Click popupNode_ first item
     * @tc.expected: The first item color changed
     */
    float clickIndex = 0;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::GREEN);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    ListItemClick(clickIndex, TouchType::MOVE);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::GREEN);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::BLUE);

    /**
     * @tc.steps: step3. Click popupNode_ second item
     * @tc.expected: The second item color changed
     */
    clickIndex = 1;
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::GREEN);
    ListItemClick(clickIndex, TouchType::MOVE);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::GREEN);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(firstTextLayoutProperty->GetTextColor().value(), Color::BLUE);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::BLUE);
}

/**
 * @tc.name: PopupClickStyle002
 * @tc.desc: Test ChangeListItemsSelectedStyle with AutoCollapse,
 * the text color will change by click except first item
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, PopupClickStyle002, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    model.SetPopupSelectedColor(Color::GREEN);
    model.SetPopupUnselectedColor(Color::BLUE);
    model.SetPopupItemBackground(Color::GRAY);
    model.SetAutoCollapse(true);
    ViewAbstract::SetHeight(CalcLength(SHORT_INDEXER_HEIGHT));
    CreateDone();
    frameNode_->MarkModifyDone();

    /**
     * @tc.steps: step1. Show popupNode_
     * @tc.expected: The first item is letter, has no clickListener
     */
    pattern_->MoveIndexByStep(1);
    auto firstListItemNode = GetListItemNode(0);
    auto gesture = firstListItemNode->GetOrCreateGestureEventHub();
    EXPECT_EQ(gesture->touchEventActuator_, nullptr);

    /**
     * @tc.steps: step2. Click popupNode_ second item
     * @tc.expected: The second item color changed
     */
    float clickIndex = 1;
    auto secondListItemNode = GetListItemNode(clickIndex);
    auto secondTextLayoutProperty = GetChildLayoutProperty<TextLayoutProperty>(secondListItemNode, 0);
    ListItemClick(clickIndex, TouchType::DOWN);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::GREEN);
    ListItemClick(clickIndex, TouchType::UP);
    EXPECT_EQ(secondTextLayoutProperty->GetTextColor().value(), Color::BLUE);
}

/**
 * @tc.name: OnPopupHoverStyle001
 * @tc.desc: Test OnPopupHover, visibility will change by hover
 * @tc.type: FUNC
 */
HWTEST_F(IndexerLayoutTestNg, OnPopupHoverStyle001, TestSize.Level1)
{
    IndexerModelNG model = CreateIndexer(GetLongArrayValue(), 0);
    model.SetUsingPopup(true);
    model.SetOnRequestPopupData(GetPopupData());
    CreateDone();
    pattern_->MoveIndexByStep(1);
    GetRenderContext();

    /**
     * @tc.steps: step1. Hover
     * @tc.expected: Show
     */
    pattern_->OnPopupHover(true);
    EXPECT_EQ(popupRenderContext_->GetOpacityValue(), 1.f);
    auto layoutProperty = pattern_->popupNode_->GetLayoutProperty<LinearLayoutProperty>();
    EXPECT_FALSE(layoutProperty->GetVisibility().has_value());

    /**
     * @tc.steps: step2. No hover
     * @tc.expected: Hide
     */
    pattern_->OnPopupHover(false);
    pattern_->StartBubbleDisappearAnimation();
    EXPECT_EQ(popupRenderContext_->GetOpacityValue(), 0.f);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::GONE);

    /**
     * @tc.steps: step3. Hover
     * @tc.expected: Show
     */
    pattern_->OnPopupHover(true);
    EXPECT_EQ(popupRenderContext_->GetOpacityValue(), 1.f);
    EXPECT_EQ(layoutProperty->GetVisibility(), VisibleType::VISIBLE);
}
} // namespace OHOS::Ace::NG
