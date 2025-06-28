/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "list_test_ng.h"

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

void ListItemGroupPatternTestNg::SetUp() {}

void ListItemGroupPatternTestNg::TearDown() {}

/**
 * @tc.name: GetStartListItemIndex001
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex001, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    RefPtr<NG::UINode> footerNode;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_FOOTER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.footerMainSize_ = 0.0f;
    listItemGroupPattern.AddFooter(footerNode);
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex002
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex002, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    RefPtr<NG::UINode> footerNode;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_FOOTER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.footerMainSize_ = 1.0f;
    listItemGroupPattern.AddFooter(footerNode);
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex003
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex003, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = 1.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex004
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex004, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = -1.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex005
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex005, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = -1.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex006
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex006, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = 5.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex007
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex007, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = -5.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex008
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex008, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = 5.0;
    listItemGroupPattern.headerMainSize_ = -1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex009
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex009, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = 0;
    listItemGroupPattern.startHeaderPos_ = -5.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex010
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex010, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::IN_HEADER_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.itemDisplayStartIndex_ = -1;
    listItemGroupPattern.startHeaderPos_ = 1.0;
    listItemGroupPattern.headerMainSize_ = 1.0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex011
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex011, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_EQ(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex012
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex012, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex013
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex013, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex014
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex014, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex015
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex015, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex016
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex016, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 1.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex017
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex017, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 1.0;
    listItemGroupPattern.itemTotalCount_ = 0;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: GetStartListItemIndex018
 * @tc.desc: Test GetStartListItemIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetStartListItemIndex018, TestSize.Level1)
{
    RefPtr<ShallowBuilder> shallowBuilder = nullptr;
    V2::ListItemGroupStyle style = V2::ListItemGroupStyle::NONE;
    ListItemGroupPattern listItemGroupPattern(shallowBuilder, style);
    auto startArea = ListItemGroupArea::NONE_AREA;
    VisibleContentInfo startInfo = { startArea, -1 };
    listItemGroupPattern.headerMainSize_ = 0.0;
    listItemGroupPattern.footerMainSize_ = 0.0;
    listItemGroupPattern.itemTotalCount_ = -1;
    auto result = listItemGroupPattern.GetStartListItemIndex();
    EXPECT_NE(result.area, startInfo.area);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test ListItemGroupPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    layoutWrapper->layoutAlgorithm_ = nullptr;

    /**
     * @tc.steps: step2. Set the dirtySwapConfig's skipMeasure and skipLayout to true
     */
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = true;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return false
     */
    auto result = listItemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test ListItemGroupPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    RefPtr<ListItemGroupLayoutAlgorithm> listItemGroupLayoutAlgorithm =
        AceType::MakeRefPtr<ListItemGroupLayoutAlgorithm>(0, 0, 2);
    listItemGroupLayoutAlgorithm->itemPosition_[0] = { 2, 2.0f, 4.0f, true };
    RefPtr<ListItemGroupLayoutProperty> listItemGroupLayoutProperty =
        AceType::MakeRefPtr<ListItemGroupLayoutProperty>();
    V2::ItemDivider itemDivider;
    listItemGroupLayoutProperty->UpdateDivider(itemDivider);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    frameNode->layoutProperty_ = listItemGroupLayoutProperty;
    frameNode->accessibilityProperty_ = nullptr;
    listItemGroupPattern->frameNode_ = frameNode;
    auto layoutWrapper = frameNode->CreateLayoutWrapper(true, true);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(listItemGroupLayoutAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step2. Set the dirtySwapConfig's skipMeasure to true and skipLayout to false
     */
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return true
     */
    auto result = listItemGroupPattern->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetOrCreateListChildrenMainSize001
 * @tc.desc: Test ListItemGroupPattern GetOrCreateListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetOrCreateListChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step2. Set the listItemGroupPattern's childrenSize_
     */
    std::vector<float> mainSize = { 1.0f, 2.0f, 3.0f };
    listItemGroupPattern->childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);

    /**
     * @tc.steps: step3. Call the GetOrCreateListChildrenMainSize
     * @tc.expected: The function result return childrenSize_
     */
    auto result = listItemGroupPattern->GetOrCreateListChildrenMainSize();
    EXPECT_EQ(result->childrenSize_.back(), 3.0f);
    EXPECT_EQ(result->defaultSize_, 2.0f);
}

/**
 * @tc.name: GetOrCreateListChildrenMainSize002
 * @tc.desc: Test ListItemGroupPattern GetOrCreateListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetOrCreateListChildrenMainSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set the listItemGroupPattern's childrenSize_ to nullptr and set context
     */
    listItemGroupPattern->childrenSize_ = nullptr;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->pixelRoundMode_ = PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE;
    frameNode->context_ = AceType::RawPtr(context);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step3. Call the GetOrCreateListChildrenMainSize
     * @tc.expected: The childrenSize_'s isRoundingMode_ return true
     */
    listItemGroupPattern->GetOrCreateListChildrenMainSize();
    frameNode->context_ = nullptr;
    EXPECT_TRUE(listItemGroupPattern->childrenSize_->isRoundingMode_);
}

/**
 * @tc.name: SetListChildrenMainSize001
 * @tc.desc: Test ListItemGroupPattern SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, SetListChildrenMainSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set the context and context's pixelRoundMode_ is PIXEL_ROUND_AFTER_MEASURE
     */
    listItemGroupPattern->childrenSize_ = nullptr;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->pixelRoundMode_ = PixelRoundMode::PIXEL_ROUND_AFTER_MEASURE;
    frameNode->context_ = AceType::RawPtr(context);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step3. Call the SetListChildrenMainSize
     * @tc.expected: The childrenSize_'s isRoundingMode_ return true
     */
    std::vector<float> mainSize = { 1.0f, 2.0f, 3.0f };
    listItemGroupPattern->SetListChildrenMainSize(2.0f, mainSize);
    frameNode->context_ = nullptr;
    EXPECT_TRUE(listItemGroupPattern->childrenSize_->isRoundingMode_);
}

/**
 * @tc.name: SetListChildrenMainSize002
 * @tc.desc: Test ListItemGroupPattern SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, SetListChildrenMainSize002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set the context and context's pixelRoundMode_ is PIXEL_ROUND_ON_LAYOUT_FINISH
     */
    listItemGroupPattern->childrenSize_ = nullptr;
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    context->pixelRoundMode_ = PixelRoundMode::PIXEL_ROUND_ON_LAYOUT_FINISH;
    frameNode->context_ = AceType::RawPtr(context);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step3. Call the SetListChildrenMainSize
     * @tc.expected: The childrenSize_'s isRoundingMode_ return false
     */
    std::vector<float> mainSize = { 1.0f, 2.0f, 3.0f };
    listItemGroupPattern->SetListChildrenMainSize(2.0f, mainSize);
    frameNode->context_ = nullptr;
    EXPECT_FALSE(listItemGroupPattern->childrenSize_->isRoundingMode_);
}

/**
 * @tc.name: SetListChildrenMainSize003
 * @tc.desc: Test ListItemGroupPattern SetListChildrenMainSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, SetListChildrenMainSize003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step2. Set pipeline is not exist and set the listItemGroupPattern's childrenSize_ to nullptr
     */
    listItemGroupPattern->childrenSize_ = nullptr;
    listItemGroupPattern->frameNode_ = nullptr;

    /**
     * @tc.steps: step3. Call the SetListChildrenMainSize
     * @tc.expected: The childrenSize_'s isRoundingMode_ return false
     */
    std::vector<float> mainSize = { 1.0f, 2.0f, 3.0f };
    listItemGroupPattern->SetListChildrenMainSize(2.0f, mainSize);
    EXPECT_FALSE(listItemGroupPattern->childrenSize_->isRoundingMode_);
}

/**
 * @tc.name: OnChildrenSizeChanged001
 * @tc.desc: Test ListItemGroupPattern OnChildrenSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, OnChildrenSizeChanged001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. Set listItemGroupPattern's posMap_ is nullptr
     */
    listItemGroupPattern->posMap_ = nullptr;

    /**
     * @tc.steps: step3. Call the OnChildrenSizeChanged
     * @tc.expected: The listItemGroupPattern's posMap_ is exist
     */
    listItemGroupPattern->OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_CHILD_SIZE);
    EXPECT_NE(listItemGroupPattern->posMap_, nullptr);
}

/**
 * @tc.name: OnChildrenSizeChanged002
 * @tc.desc: Test ListItemGroupPattern OnChildrenSizeChanged
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, OnChildrenSizeChanged002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. Set listItemGroupPattern's posMap_
     */
    listItemGroupPattern->posMap_ = AceType::MakeRefPtr<ListPositionMap>();

    /**
     * @tc.steps: step3. Call the OnChildrenSizeChanged
     * @tc.expected: The listItemGroupPattern's posMap's dirty is LIST_UPDATE_DEFAULT_SIZE
     */
    listItemGroupPattern->OnChildrenSizeChanged({ -1, -1, -1 }, LIST_UPDATE_DEFAULT_SIZE);
    EXPECT_EQ(listItemGroupPattern->posMap_->dirty_, LIST_UPDATE_DEFAULT_SIZE);
}

/**
 * @tc.name: ResetChildrenSize001
 * @tc.desc: Test ListItemGroupPattern ResetChildrenSize
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, ResetChildrenSize001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);
    listItemGroupPattern->frameNode_ = frameNode;

    /**
     * @tc.steps: step2. Set listItemGroupPattern's childrenSize_
     */
    std::vector<float> mainSize = { 1.0f, 2.0f, 3.0f };
    listItemGroupPattern->childrenSize_ = AceType::MakeRefPtr<ListChildrenMainSize>(mainSize, 2.0f);

    /**
     * @tc.steps: step3. Call the ResetChildrenSize
     * @tc.expected: The listItemGroupPattern's posMap_'s dirty is LIST_UPDATE_CHILD_SIZE
     */
    listItemGroupPattern->ResetChildrenSize();
    EXPECT_EQ(listItemGroupPattern->posMap_->dirty_, LIST_UPDATE_CHILD_SIZE);
}

/**
 * @tc.name: UpdateCachedIndex001
 * @tc.desc: Test ListItemGroupPattern UpdateCachedIndex
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, UpdateCachedIndex001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    listItemGroupPattern->frameNode_ = nullptr;

    /**
     * @tc.steps: step2. Set listItemGroupPattern's forwardCachedIndex_ and backwardCachedIndex_
     */
    listItemGroupPattern->forwardCachedIndex_ = 2;
    listItemGroupPattern->backwardCachedIndex_ = INT_MIN;

    /**
     * @tc.steps: step3. Call the UpdateCachedIndex
     * @tc.expected: The listItemGroupPattern's forwardCachedIndex_ and backwardCachedIndex_ is changed
     */
    listItemGroupPattern->UpdateCachedIndex(true, false, 2, 4);
    EXPECT_EQ(listItemGroupPattern->forwardCachedIndex_, -1);
    EXPECT_EQ(listItemGroupPattern->backwardCachedIndex_, INT_MAX);
}

/**
 * @tc.name: CheckDataChangeOutOfStart001
 * @tc.desc: Test ListItemGroupPattern CheckDataChangeOutOfStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, CheckDataChangeOutOfStart001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set count to 0
     * @tc.expected: The result of calling the function is false
     */
    auto result = listItemGroupPattern->CheckDataChangeOutOfStart(0, 0, 0, 0);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step3. Set count to be greater than 0 and index to be less than endIndex
     * and listItemGroupPattern's isStackFromEnd_ to true
     * @tc.expected: The result of calling the function is false
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    result = listItemGroupPattern->CheckDataChangeOutOfStart(2, 3, 3, 5);
    EXPECT_FALSE(result);

    /**
     * @tc.steps: step4. Set listPattern maintainVisibleContentPosition_ to false
     * @tc.expected: The result of calling the function is false
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->SetMaintainVisibleContentPosition(false);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(node, nullptr);
    frameNode->parent_ = node;
    listItemGroupPattern->frameNode_ = frameNode;
    result = listItemGroupPattern->CheckDataChangeOutOfStart(2, 3, 2, 2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: CheckDataChangeOutOfStart002
 * @tc.desc: Test ListItemGroupPattern CheckDataChangeOutOfStart
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, CheckDataChangeOutOfStart002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto frameNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(frameNode, nullptr);

    /**
     * @tc.steps: step2. Set listPattern maintainVisibleContentPosition_ to true
     * and startIndex to be 0 and index not to be 0
     * @tc.expected: The result of calling the function is true
     */
    RefPtr<ListPattern> listPattern = AceType::MakeRefPtr<ListPattern>();
    listPattern->SetMaintainVisibleContentPosition(true);
    auto node = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, listPattern);
    ASSERT_NE(node, nullptr);
    frameNode->parent_ = node;
    listItemGroupPattern->frameNode_ = frameNode;
    auto result = listItemGroupPattern->CheckDataChangeOutOfStart(0, 3, 0, 0);
    EXPECT_TRUE(result);

    /**
     * @tc.steps: step3. Set listPattern maintainVisibleContentPosition_ to true and listItemGroupPattern's
     * isStackFromEnd_ true and startIndex and index to be 0, and count to be less than 0
     * @tc.expected: The result of calling the function is true
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    result = listItemGroupPattern->CheckDataChangeOutOfStart(0, -1, 0, -1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: GetCurrentFocusIndices001
 * @tc.desc: Test ListItemGroupPattern GetCurrentFocusIndices
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetCurrentFocusIndices001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set curItemPattern to listpattern and header_ and footer_ to customnode
     */
    auto curPattern = AceType::MakeRefPtr<ListPattern>();
    auto node = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2
     * @tc.expected: The result of calling the function is false and curIndexInGroup has not changed
     */
    int32_t curIndexInGroup = 2;
    auto result = listItemGroupPattern->GetCurrentFocusIndices(curFrame, curPattern, curIndexInGroup);
    EXPECT_EQ(curIndexInGroup, 2);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: AdjustFocusStepForRtl001
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to RTL and isStackFromEnd_ to false
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::RTL;
    listItemGroupPattern->isStackFromEnd_ = false;

    /**
     * @tc.steps: step3. Set step to LEFT and isVertical to false
     * @tc.expected: The step return RIGHT
     */
    FocusStep step = FocusStep::LEFT;
    listItemGroupPattern->AdjustFocusStepForRtl(step, false);
    EXPECT_EQ(step, FocusStep::RIGHT);
}

/**
 * @tc.name: AdjustFocusStepForRtl002
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to RTL and isStackFromEnd_ to false
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::RTL;
    listItemGroupPattern->isStackFromEnd_ = false;

    /**
     * @tc.steps: step3. Set step to RIGHT and isVertical to true
     * @tc.expected: The step return LEFT
     */
    FocusStep step = FocusStep::RIGHT;
    listItemGroupPattern->AdjustFocusStepForRtl(step, true);
    EXPECT_EQ(step, FocusStep::LEFT);
}

/**
 * @tc.name: AdjustFocusStepForRtl003
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to LTR and isStackFromEnd_ to true
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::LTR;
    listItemGroupPattern->isStackFromEnd_ = true;

    /**
     * @tc.steps: step3. Set step to UP and isVertical to false
     * @tc.expected: The step return DOWN
     */
    FocusStep step = FocusStep::UP;
    listItemGroupPattern->AdjustFocusStepForRtl(step, false);
    EXPECT_EQ(step, FocusStep::DOWN);
}

/**
 * @tc.name: AdjustFocusStepForRtl004
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to RTL and isStackFromEnd_ to true
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::RTL;
    listItemGroupPattern->isStackFromEnd_ = true;

    /**
     * @tc.steps: step3. Set step to DOWN and isVertical to false
     * @tc.expected: The step return UP
     */
    FocusStep step = FocusStep::DOWN;
    listItemGroupPattern->AdjustFocusStepForRtl(step, false);
    EXPECT_EQ(step, FocusStep::UP);
}

/**
 * @tc.name: AdjustFocusStepForRtl005
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to LTR and isStackFromEnd_ to false
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::LTR;
    listItemGroupPattern->isStackFromEnd_ = false;

    /**
     * @tc.steps: step3. Set step to NONE and isVertical to false
     * @tc.expected: The step is not changed
     */
    FocusStep step = FocusStep::NONE;
    listItemGroupPattern->AdjustFocusStepForRtl(step, false);
    EXPECT_EQ(step, FocusStep::NONE);
}

/**
 * @tc.name: AdjustFocusStepForRtl006
 * @tc.desc: Test ListItemGroupPattern AdjustFocusStepForRtl
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, AdjustFocusStepForRtl006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set listItemGroupPattern's layoutDirection_ to RTL and isStackFromEnd_ to true
     */
    listItemGroupPattern->layoutDirection_ = TextDirection::RTL;
    listItemGroupPattern->isStackFromEnd_ = true;

    /**
     * @tc.steps: step3. Set step to RIGHT and isVertical to true
     * @tc.expected: The step is not changed
     */
    FocusStep step = FocusStep::RIGHT;
    listItemGroupPattern->AdjustFocusStepForRtl(step, true);
    EXPECT_EQ(step, FocusStep::RIGHT);
}

/**
 * @tc.name: HandleForwardStep001
 * @tc.desc: Test ListItemGroupPattern HandleForwardStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleForwardStep001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set header_ and footer_ to customnode and isStackFromEnd_ to true
     * set lanes_ to 3 and itemTotalCount_ to 4
     */
    auto node = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 3;
    listItemGroupPattern->itemTotalCount_ = 4;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 3, moveStep to 1 and nextIndex to 2
     * @tc.expected: The moveStep to be 3 and nextIndex to be 5
     */
    int32_t moveStep = 1;
    int32_t nextIndex = 2;
    listItemGroupPattern->HandleForwardStep(curFrame, 3, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 3);
    EXPECT_EQ(nextIndex, 5);
}

/**
 * @tc.name: HandleForwardStep002
 * @tc.desc: Test ListItemGroupPattern HandleForwardStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleForwardStep002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set header_ and footer_ to customnode and isStackFromEnd_ to false
     * set lanes_ to 2 and itemTotalCount_ to 5
     */
    auto node = CustomNode::CreateCustomNode(1, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;
    listItemGroupPattern->isStackFromEnd_ = false;
    listItemGroupPattern->lanes_ = 2;
    listItemGroupPattern->itemTotalCount_ = 5;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 1 and nextIndex to 6
     * @tc.expected: The moveStep to be 2 and nextIndex to be 4
     */
    int32_t moveStep = 1;
    int32_t nextIndex = 6;
    listItemGroupPattern->HandleForwardStep(curFrame, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 2);
    EXPECT_EQ(nextIndex, 4);
}

/**
 * @tc.name: HandleBackwardStep001
 * @tc.desc: Test ListItemGroupPattern HandleBackwardStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleBackwardStep001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set header_ and footer_ to customnode and isStackFromEnd_ to true
     * set lanes_ to 3 and itemTotalCount_ to 4
     */
    auto node = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 3;
    listItemGroupPattern->itemTotalCount_ = 4;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 1 and nextIndex to 2
     * @tc.expected: The moveStep to be -3 and nextIndex to be 0
     */
    int32_t moveStep = 1;
    int32_t nextIndex = 2;
    listItemGroupPattern->HandleBackwardStep(curFrame, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, -3);
    EXPECT_EQ(nextIndex, 0);
}

/**
 * @tc.name: HandleBackwardStep002
 * @tc.desc: Test ListItemGroupPattern HandleBackwardStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleBackwardStep002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set header_ and footer_ to customnode and isStackFromEnd_ to false
     * set lanes_ to 3 and itemTotalCount_ to 5
     */
    auto node = CustomNode::CreateCustomNode(1, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;
    listItemGroupPattern->isStackFromEnd_ = false;
    listItemGroupPattern->lanes_ = 3;
    listItemGroupPattern->itemTotalCount_ = 5;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 3, moveStep to 1 and nextIndex to 2
     * @tc.expected: The moveStep to be -3 and nextIndex to be 0
     */
    int32_t moveStep = 1;
    int32_t nextIndex = 2;
    listItemGroupPattern->HandleBackwardStep(curFrame, 3, moveStep, nextIndex);
    EXPECT_EQ(moveStep, -3);
    EXPECT_EQ(nextIndex, 0);
}

/**
 * @tc.name: HandleCrossAxisRightOrDownStep001
 * @tc.desc: Test ListItemGroupPattern HandleCrossAxisRightOrDownStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleCrossAxisRightOrDownStep001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set isStackFromEnd_ to true, lanes_ to 1 and itemTotalCount_ to 4
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 1;
    listItemGroupPattern->itemTotalCount_ = 4;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 3 and nextIndex to 4
     * @tc.expected: The moveStep to be 1 and nextIndex to be 2
     */
    int32_t moveStep = 3;
    int32_t nextIndex = 4;
    auto result = listItemGroupPattern->HandleCrossAxisRightOrDownStep(false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 1);
    EXPECT_EQ(nextIndex, 2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCrossAxisRightOrDownStep002
 * @tc.desc: Test ListItemGroupPattern HandleCrossAxisRightOrDownStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleCrossAxisRightOrDownStep002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set isStackFromEnd_ to true, lanes_ to 2 and itemTotalCount_ to 6
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 2;
    listItemGroupPattern->itemTotalCount_ = 6;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 3 and nextIndex to 1
     * @tc.expected: The moveStep to be 1 and nextIndex to be 3
     */
    int32_t moveStep = 3;
    int32_t nextIndex = 1;
    auto result = listItemGroupPattern->HandleCrossAxisRightOrDownStep(false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 1);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCrossAxisRightOrDownStep003
 * @tc.desc: Test ListItemGroupPattern HandleCrossAxisRightOrDownStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleCrossAxisRightOrDownStep003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set isStackFromEnd_ to false, lanes_ to 2 and itemTotalCount_ to 6
     */
    listItemGroupPattern->isStackFromEnd_ = false;
    listItemGroupPattern->lanes_ = 3;
    listItemGroupPattern->itemTotalCount_ = 4;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 3, moveStep to 3 and nextIndex to 1
     * @tc.expected: The moveStep to be 1 and nextIndex to be 3
     */
    int32_t moveStep = 3;
    int32_t nextIndex = 1;
    auto result = listItemGroupPattern->HandleCrossAxisRightOrDownStep(true, 3, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 1);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCrossAxisLeftOrUpStep001
 * @tc.desc: Test ListItemGroupPattern HandleCrossAxisLeftOrUpStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleCrossAxisLeftOrUpStep001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set isStackFromEnd_ to true, lanes_ to 1 and itemTotalCount_ to 5
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 1;
    listItemGroupPattern->itemTotalCount_ = 5;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 3 and nextIndex to 4
     * @tc.expected: The moveStep to be -1 and nextIndex to be 2
     */
    int32_t moveStep = 3;
    int32_t nextIndex = 4;
    auto result = listItemGroupPattern->HandleCrossAxisLeftOrUpStep(false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, -1);
    EXPECT_EQ(nextIndex, 2);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: HandleCrossAxisLeftOrUpStep002
 * @tc.desc: Test ListItemGroupPattern HandleCrossAxisLeftOrUpStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, HandleCrossAxisLeftOrUpStep002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 2, listItemGroupPattern);
    ASSERT_NE(curFrame, nullptr);

    /**
     * @tc.steps: step2. Set isStackFromEnd_ to true, lanes_ to 2 and itemTotalCount_ to 7
     */
    listItemGroupPattern->isStackFromEnd_ = true;
    listItemGroupPattern->lanes_ = 2;
    listItemGroupPattern->itemTotalCount_ = 7;

    /**
     * @tc.steps: step3. Set curIndexInGroup to 2, moveStep to 3 and nextIndex to 1
     * @tc.expected: The moveStep to be -1 and nextIndex to be 1
     */
    int32_t moveStep = 3;
    int32_t nextIndex = 1;
    auto result = listItemGroupPattern->HandleCrossAxisLeftOrUpStep(true, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, -1);
    EXPECT_EQ(nextIndex, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DetermineSingleLaneStep001
 * @tc.desc: Test ListItemGroupPattern DetermineSingleLaneStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, DetermineSingleLaneStep001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curPattern = AceType::MakeRefPtr<ListPattern>();
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, curPattern);
    ASSERT_NE(curFrame, nullptr);
    auto ListItemGroupNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(ListItemGroupNode, nullptr);
    ListItemGroupNode->parent_ = curFrame;
    listItemGroupPattern->frameNode_ = ListItemGroupNode;

    /**
     * @tc.steps: step2. Set step to RIGHT, isVertical to false and itemTotalCount_ to 2
     * and set moveStep to 2 and nextIndex to 2
     */
    int32_t moveStep = 2;
    int32_t nextIndex = 2;

    /**
     * @tc.steps: step3. Call the DetermineSingleLaneStep function
     * @tc.expected: The function result returns true, the moveStep to be 1 and nextIndex to be 3
     */
    auto result = listItemGroupPattern->DetermineSingleLaneStep(FocusStep::RIGHT, false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 1);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DetermineSingleLaneStep002
 * @tc.desc: Test ListItemGroupPattern DetermineSingleLaneStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, DetermineSingleLaneStep002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curPattern = AceType::MakeRefPtr<ListPattern>();
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, curPattern);
    ASSERT_NE(curFrame, nullptr);
    auto ListItemGroupNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(ListItemGroupNode, nullptr);
    ListItemGroupNode->parent_ = curFrame;
    listItemGroupPattern->frameNode_ = ListItemGroupNode;

    /**
     * @tc.steps: step2. Set step to LEFT, isVertical to false and itemTotalCount_ to 2
     * and set moveStep to 2 and nextIndex to 2
     */
    int32_t moveStep = 2;
    int32_t nextIndex = 2;

    /**
     * @tc.steps: step3. Call the DetermineSingleLaneStep function
     * @tc.expected: The function result returns true, the moveStep to be -1 and nextIndex to be 1
     */
    auto result = listItemGroupPattern->DetermineSingleLaneStep(FocusStep::LEFT, false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, -1);
    EXPECT_EQ(nextIndex, 1);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: DetermineSingleLaneStep003
 * @tc.desc: Test ListItemGroupPattern DetermineSingleLaneStep
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, DetermineSingleLaneStep003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);

    /**
     * @tc.steps: step2. Set step to DOWN, isVertical to false and itemTotalCount_ to 2
     * and set moveStep to 1 and nextIndex to 3
     */
    int32_t moveStep = 1;
    int32_t nextIndex = 3;

    /**
     * @tc.steps: step3. Call the DetermineSingleLaneStep function
     * @tc.expected: The function result returns false, the moveStep and nextIndex is not changed
     */
    auto result = listItemGroupPattern->DetermineSingleLaneStep(FocusStep::DOWN, false, 2, moveStep, nextIndex);
    EXPECT_EQ(moveStep, 1);
    EXPECT_EQ(nextIndex, 3);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetNextFocusNode001
 * @tc.desc: Test ListItemGroupPattern GetNextFocusNode
 * @tc.type: FUNC
 */
HWTEST_F(ListItemGroupPatternTestNg, GetNextFocusNode001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    RefPtr<ShallowBuilder> shallowBuilder = AceType::MakeRefPtr<ShallowBuilder>(nullptr);
    RefPtr<ListItemGroupPattern> listItemGroupPattern =
        AceType::MakeRefPtr<ListItemGroupPattern>(shallowBuilder, V2::ListItemGroupStyle::CARD);
    auto curPattern = AceType::MakeRefPtr<ListPattern>();
    auto curFrame = FrameNode::CreateFrameNode(V2::LIST_ETS_TAG, 2, curPattern);
    ASSERT_NE(curFrame, nullptr);
    auto ListItemGroupNode = FrameNode::CreateFrameNode(V2::LIST_ITEM_GROUP_ETS_TAG, 1, listItemGroupPattern);
    ASSERT_NE(ListItemGroupNode, nullptr);
    ListItemGroupNode->parent_ = curFrame;
    listItemGroupPattern->frameNode_ = ListItemGroupNode;
    WeakPtr<FrameNode> weakFrameNode = std::move(curFrame);
    auto weakNode = AceType::MakeRefPtr<FocusHub>(weakFrameNode);
    WeakPtr<FocusHub> currentFocusNode = std::move(weakNode);

    /**
     * @tc.steps: step2. Set curItemPattern to listpattern and header_ and footer_ to customnode
     */
    auto node = CustomNode::CreateCustomNode(2, "test");
    ASSERT_NE(node, nullptr);
    listItemGroupPattern->header_ = node;
    listItemGroupPattern->footer_ = node;

    /**
     * @tc.steps: step3. Set step to UP
     * Set GetCurrentFocusIndices function to return false
     * @tc.expected: The result of calling the function is nullptr
     */
    auto res = listItemGroupPattern->GetNextFocusNode(FocusStep::UP, currentFocusNode);
    auto result = res.Upgrade();
    EXPECT_EQ(result, nullptr);
}
} // namespace OHOS::Ace::NG