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
std::vector<std::string> CREATE_ARRAY = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O",
    "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };
std::vector<std::string> CREATE_ARRAY_1 = { "A", "B", "C", "D", "E", "F", "G", "H", "I"};
std::vector<std::string> CREATE_ARRAY_2 = { "#", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L"};
} // namespace
 
class IndexerPatternTestNg : public IndexerTestNg {
public:
};

/**
 * @tc.name: IndexerPatternNg001
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color(0x00000000));
    model.SetColor(Color(0x00000000));
    model.SetPopupColor(Color(0x00000000));
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(true);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50)); //50 is the horizontal space of popupNode
    model.SetSelected(0);
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color(0x00000000));
    model.SetPopupSelectedColor(Color(0x00000000));
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24)); //24 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(20.0_vp); //20.0_vp is the width of item
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    pattern_->selected_ = 5; // 5 is the index of item
    EXPECT_EQ(accessibilityProperty_->GetText(), "F");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 20);  //20 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 20); //20 is the height of item
}

/**
 * @tc.name: IndexerPatternNg002
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color(0x00000000));
    model.SetColor(Color(0x00000000));
    model.SetPopupColor(Color(0x00000000));
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(true);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));                 //50 is the horizontal space of popupNode
    model.SetSelected(5);                                         //5 is the index of item
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color(0x00000000));
    model.SetPopupSelectedColor(Color(0x00000000));
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24)); //24 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(28.0_vp); //28.0_vp is the itemSize of indexer
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "F");

    pattern_->selected_ = 0;
    EXPECT_EQ(accessibilityProperty_->GetText(), "A");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 28);  //28 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 28); //28 is the height of item
}

/**
 * @tc.name: IndexerPatternNg003
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::BLACK);
    model.SetColor(Color::BLUE);
    model.SetPopupColor(Color::GRAY);
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(false);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));                 //50 is the horizontal space of popupNode
    model.SetSelected(10);                                        //10 is the index of item
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::RED);
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24)); //24 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(28.0_vp); //28.0_vp is the itemSize of indexer
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "K");

    pattern_->selected_ = 12; //12 is the index of item
    EXPECT_EQ(accessibilityProperty_->GetText(), "M");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 28);  //28 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 28); //28 is the height of item
}

/**
 * @tc.name: IndexerPatternNg004
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY, 0);
    model.SetSelectedColor(Color::GRAY);
    model.SetColor(Color::GRAY);
    model.SetPopupColor(Color::WHITE);
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(false);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));                 //50 is the horizontal space of popupNode
    model.SetSelected(25);                                        //25 is the index of item
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::RED);
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24)); //24 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(5.0_vp); //5.0_vp is the itemSize of indexer
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "Z");

    pattern_->selected_ = 8; //8 is the index of item
    EXPECT_EQ(accessibilityProperty_->GetText(), "I");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 5);  //5 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 5); //5 is the height of item
}

/**
 * @tc.name: IndexerPatternNg005
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetSelectedColor(Color::GRAY);
    model.SetColor(Color::GRAY);
    model.SetPopupColor(Color::WHITE);
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(false);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));                 //50 is the horizontal space of popupNode
    model.SetSelected(2);                                         //25 is the index of item
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::RED);
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(24)); //24 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(15.0_vp); //15.0_vp is the itemSize of indexer
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY_1.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "C");

    pattern_->selected_ = 8; //8 is the index of item
    EXPECT_EQ(accessibilityProperty_->GetText(), "I");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 15);  //15 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 15); //15 is the height of item
}

/**
 * @tc.name: IndexerPatternNg006
 * @tc.desc: Test indexer layoutAlgorithm GetMaxItemWidth function.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer and get frameNode.
     */
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetSelectedColor(Color::BLACK);
    model.SetColor(Color::BLACK);
    model.SetPopupColor(Color::BLACK);
    model.SetSelectedBackgroundColor(Color(0x00000000));
    model.SetPopupBackground(Color(0x00000000));
    model.SetUsingPopup(false);
    model.SetAlignStyle(0);
    model.SetPopupHorizontalSpace(Dimension(50));                 //50 is the horizontal space of popupNode
    model.SetSelected(10);                                        //10 is the index of item
    model.SetPopupPositionX(Dimension(-96.f, DimensionUnit::VP)); //-96.f is the left space of popupNode
    model.SetPopupPositionY(Dimension(48.f, DimensionUnit::VP));  //48.f is the top space of popupNode
    model.SetPopupItemBackground(Color::BLACK);
    model.SetPopupSelectedColor(Color::BLACK);
    model.SetPopupUnselectedColor(Color(0x00000000));
    model.SetFontSize(Dimension(14)); //14 is the fontSize of item
    model.SetFontWeight(FontWeight::MEDIUM);
    model.SetAdaptiveWidth(true);
    model.SetItemSize(2.0_vp); //2.0_vp is the itemSize of indexer
    CreateDone();

    /**
     * @tc.steps: step2.  get layoutWrapper and indexerLayoutAlgorithm.
     * @tc.expected: step2. get layoutWrapper success.
     */
    EXPECT_EQ(frameNode_->GetChildren().size(), CREATE_ARRAY_2.size());
    pattern_->ApplyIndexChanged(true, true);
    EXPECT_EQ(accessibilityProperty_->GetText(), "J");

    pattern_->selected_ = 0;
    EXPECT_EQ(accessibilityProperty_->GetText(), "#");

    /**
     * @tc.steps: step3.  get itemSize.
     * @tc.expected: step3. check whether the itemSize value is correct.
     */
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 2);  //2 is the width of item
    EXPECT_EQ(GetChildHeight(frameNode_, 0), 2); //2 is the height of item
}

/**
 * @tc.name: IndexerPatternNg007
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetUsingPopup(true);
    model.SetIndexerBorderRadius(Dimension(5)); //5 is the radius of item
    CreateDone();

    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(5); //5 is the radius of item
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(16)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(16)); //16 is the radius of item
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(16), Dimension(16), Dimension(16), Dimension(16) }; //16 is the radius of item
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(BUBBLE_RADIUS, DimensionUnit::VP);
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupBorderRadius
     * @tc.expected: columnRenderContext BorderRadiusValue is Dimension(28)
     */
    styleOption.blurStyle = BlurStyle::REGULAR;
    paintProperty_->UpdatePopupBorderRadius(Dimension(28)); //28 is the radius of item
    paintProperty_->UpdatePopupBackgroundBlurStyle(styleOption);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(28), Dimension(28), Dimension(28), Dimension(28) }; //28 is the radius of item
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPatternNg008
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetUsingPopup(true);
    model.SetItemBorderRadius(Dimension(5));       //5 is the radius of item
    model.SetIndexerBorderRadius(Dimension(5));    //5 is the radius of indexer
    model.SetPopupItemBorderRadius(Dimension(10)); //10 is the radius of popup item
    model.SetPopupBorderRadius(Dimension(20));     //20 is the radius of popup
    CreateDone();

    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    auto definedPopupRadius = paintProperty_->GetPopupBorderRadiusValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    paintProperty_->UpdatePopupBorderRadius(definedPopupRadius);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(5); //5 is the radius of item
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(16)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(16)); //16 is the radius of item
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(16), Dimension(16), Dimension(16), Dimension(16) }; //16 is the radius of item
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(20); //20 is the radius of popup
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_REGULAR;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupBorderRadius
     * @tc.expected: columnRenderContext BorderRadiusValue is Dimension(28)
     */
    styleOption.blurStyle = BlurStyle::REGULAR;
    paintProperty_->UpdatePopupBorderRadius(Dimension(28)); //28 is the radius of item
    paintProperty_->UpdatePopupBackgroundBlurStyle(styleOption);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(28), Dimension(28), Dimension(28), Dimension(28) }; //28 is the radius of item
    EXPECT_TRUE(columnRenderContext->HasBorderRadius());
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPatternNg009
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::BACKGROUND_THICK;
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_2, 0);
    model.SetUsingPopup(true);
    model.SetIndexerBorderRadius(Dimension(10)); //10 is the radius of indexer
    model.SetPopupBorderRadius(Dimension(30));   //30 is the radius of popup
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    CreateDone();

    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    auto definedPopupRadius = paintProperty_->GetPopupBorderRadiusValue();
    auto blurStyle = paintProperty_->GetPopupBackgroundBlurStyleValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    paintProperty_->UpdatePopupBorderRadius(definedPopupRadius);
    paintProperty_->UpdatePopupBackgroundBlurStyle(blurStyle);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(10); //10 is the radius of item
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(33)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(33)); //33 is the radius of item
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(33), Dimension(33), Dimension(33), Dimension(33) }; //33 is the radius of item
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(30); //30 is the radius of popup
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::BACKGROUND_THICK;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupBorderRadius
     * @tc.expected: columnRenderContext BorderRadiusValue is Dimension(8)
     */
    styleOption.blurStyle = BlurStyle::REGULAR;
    paintProperty_->UpdatePopupBorderRadius(Dimension(8)); //8 is the radius of item
    paintProperty_->UpdatePopupBackgroundBlurStyle(styleOption);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(8), Dimension(8), Dimension(8), Dimension(8) }; //8 is the radius of item
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPatternNg010
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::BACKGROUND_THICK;
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetUsingPopup(true);
    model.SetIndexerBorderRadius(Dimension(-1)); //-1 is the radius of indexer
    model.SetPopupBorderRadius(Dimension(-1));   //-1 is the radius of popup
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    CreateDone();
    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    auto definedPopupRadius = paintProperty_->GetPopupBorderRadiusValue();
    auto blurStyle = paintProperty_->GetPopupBackgroundBlurStyleValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    paintProperty_->UpdatePopupBorderRadius(definedPopupRadius);
    paintProperty_->UpdatePopupBackgroundBlurStyle(blurStyle);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(-1); //-1 is the radius of item
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(0)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(0));
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(0), Dimension(0), Dimension(0), Dimension(0) };
    EXPECT_TRUE(indexerRenderContext->HasBorderRadius());
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(-1); //-1 is the radius of popup
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::BACKGROUND_THICK;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupBorderRadius
     * @tc.expected: columnRenderContext BorderRadiusValue is Dimension(8)
     */
    styleOption.blurStyle = BlurStyle::REGULAR;
    paintProperty_->UpdatePopupBorderRadius(Dimension(8)); //8 is the radius of item
    paintProperty_->UpdatePopupBackgroundBlurStyle(styleOption);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(8), Dimension(8), Dimension(8), Dimension(8) }; //8 is the radius of item
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPatternNg011
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg011, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::BACKGROUND_THICK;
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetUsingPopup(true);
    model.SetIndexerBorderRadius(Dimension(-1)); //-1 is the radius of indexer
    model.SetPopupBorderRadius(Dimension(-1));   //-1 is the radius of popup
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    model.SetPopupTitleBackground(Color::BLACK);
    CreateDone();
    pattern_->autoCollapse_ = false;
    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    auto definedPopupRadius = paintProperty_->GetPopupBorderRadiusValue();
    auto blurStyle = paintProperty_->GetPopupBackgroundBlurStyleValue();
    auto color = paintProperty_->GetPopupTitleBackgroundValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    paintProperty_->UpdatePopupBorderRadius(definedPopupRadius);
    paintProperty_->UpdatePopupBackgroundBlurStyle(blurStyle);
    paintProperty_->UpdatePopupTitleBackground(color);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(-1); //-1 is the radius of item
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(0)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(0));
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(0), Dimension(0), Dimension(0), Dimension(0) };
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(-1); //-1 is the radius of popup
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::BACKGROUND_THICK;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupTitleBackground
     * @tc.expected: PopupTitleBackground is Black
     */
    auto letterRenderContext =
        AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetFirstChild()->GetFirstChild())->GetRenderContext();
    EXPECT_EQ(letterRenderContext->GetBackgroundColorValue(Color::BLACK), Color::BLACK);
    paintProperty_->UpdatePopupTitleBackground(Color::BLUE);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(letterRenderContext->GetBackgroundColorValue(Color::BLUE), Color::BLUE);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: IndexerPatternNg012
 * @tc.desc: Test indexer pattern.
 * @tc.type: FUNC
 */
HWTEST_F(IndexerPatternTestNg, IndexerPatternNg012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create indexer when apiTargetVersion is PlatformVersion::VERSION_TWELVE
     * @tc.expected: BorderRadiusValue is Dimension(INDEXER_DEFAULT_RADIUS, DimensionUnit::VP)
     */
    int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    BlurStyleOption indexerBlurStyle;
    indexerBlurStyle.blurStyle = BlurStyle::COMPONENT_ULTRA_THIN;
    IndexerModelNG model = CreateIndexer(CREATE_ARRAY_1, 0);
    model.SetUsingPopup(true);
    model.SetIndexerBorderRadius(Dimension(0));
    model.SetPopupBorderRadius(Dimension(0));
    model.SetPopupBackgroundBlurStyle(indexerBlurStyle);
    model.SetPopupTitleBackground(Color::GRAY);
    CreateDone();
    pattern_->autoCollapse_ = false;
    auto definedRadius = paintProperty_->GetIndexerBorderRadiusValue();
    auto definedPopupRadius = paintProperty_->GetPopupBorderRadiusValue();
    auto blurStyle = paintProperty_->GetPopupBackgroundBlurStyleValue();
    auto color = paintProperty_->GetPopupTitleBackgroundValue();
    paintProperty_->UpdateIndexerBorderRadius(definedRadius);
    paintProperty_->UpdatePopupBorderRadius(definedPopupRadius);
    paintProperty_->UpdatePopupBackgroundBlurStyle(blurStyle);
    paintProperty_->UpdatePopupTitleBackground(color);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    auto indexerRenderContext = frameNode_->GetRenderContext();
    auto indexerRadius = Dimension(0);
    BorderRadiusProperty expectValue = { indexerRadius, indexerRadius, indexerRadius, indexerRadius };
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);

    /**
     * @tc.steps: step2. UpdateIndexerBorderRadius
     * @tc.expected: indexerRenderContext BorderRadiusValue is Dimension(100)
     */
    paintProperty_->UpdateIndexerBorderRadius(Dimension(100)); // 100 is the radius of item
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    expectValue = { Dimension(100), Dimension(100), Dimension(100), Dimension(100) }; // 100 is the radius of item
    EXPECT_EQ(indexerRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    auto radius = Dimension(0);
    auto columnRenderContext = pattern_->popupNode_->GetRenderContext();
    expectValue = { radius, radius, radius, radius };
    EXPECT_EQ(columnRenderContext->GetBorderRadiusValue(expectValue), expectValue);
    BlurStyleOption styleOption;
    styleOption.blurStyle = BlurStyle::COMPONENT_ULTRA_THIN;
    EXPECT_EQ(columnRenderContext->GetBackBlurStyle().value(), styleOption);

    /**
     * @tc.steps: step3. UpdatePopupTitleBackground
     * @tc.expected: PopupTitleBackground is RED
     */
    auto letterRenderContext =
        AceType::DynamicCast<FrameNode>(pattern_->popupNode_->GetFirstChild()->GetFirstChild())->GetRenderContext();
    EXPECT_EQ(letterRenderContext->GetBackgroundColorValue(), Color::GRAY);
    paintProperty_->UpdatePopupTitleBackground(Color::RED);
    pattern_->OnChildHover(1, true);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(letterRenderContext->GetBackgroundColorValue(), Color::RED);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}
} // namespace OHOS::Ace::NG
