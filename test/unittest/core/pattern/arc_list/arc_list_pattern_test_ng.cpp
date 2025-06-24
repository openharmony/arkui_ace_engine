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

#include "arc_list_test_ng.h"

#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar.h"
#include "core/components_ng/pattern/arc_scroll/inner/arc_scroll_bar_overlay_modifier.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float ARC_LIST_DRAG_OVER_RATES = 0.6f;
} // namespace

class ArcListPatternTestNg : public ArcListTestNg {
public:
};

/**
 * @tc.name: OnDirtyLayoutWrapperSwap001
 * @tc.desc: Test ArcListPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, OnDirtyLayoutWrapperSwap001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
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
    auto result = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: OnDirtyLayoutWrapperSwap002
 * @tc.desc: Test ArcListPattern OnDirtyLayoutWrapperSwap
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, OnDirtyLayoutWrapperSwap002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto layoutWrapper = frameNode_->CreateLayoutWrapper(true, true);
    RefPtr<ArcListLayoutAlgorithm> arcListLayoutAlgorithm = AceType::MakeRefPtr<ArcListLayoutAlgorithm>(0, 2);
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    std::map<int32_t, ListItemInfo> itemPosition = { std::make_pair(0, info) };
    arcListLayoutAlgorithm->SetItemsPosition(itemPosition);
    arcListLayoutAlgorithm->SetStartHeaderPos(2.0f);
    arcListLayoutAlgorithm->SetHeaderOffset(1.0f);
    arcListLayoutAlgorithm->SetOldHeaderSize(3.0f);
    arcListLayoutAlgorithm->SetOldFirstItemSize(2.0f);
    arcListLayoutAlgorithm->SetHeaderStayNear(false);
    RefPtr<LayoutAlgorithmWrapper> layoutAlgorithmWrapper =
        AceType::MakeRefPtr<LayoutAlgorithmWrapper>(arcListLayoutAlgorithm);
    layoutWrapper->layoutAlgorithm_ = layoutAlgorithmWrapper;

    /**
     * @tc.steps: step2. Set the dirtySwapConfig's skipMeasure and skipLayout to true
     */
    DirtySwapConfig dirtySwapConfig;
    dirtySwapConfig.skipMeasure = true;
    dirtySwapConfig.skipLayout = false;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return true
     */
    auto result = pattern_->OnDirtyLayoutWrapperSwap(layoutWrapper, dirtySwapConfig);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ScrollListForFocus
 * @tc.desc: Test ArcListPattern ScrollListForFocus
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ScrollListForFocus, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);
    RefPtr<PipelineContext> context = AceType::MakeRefPtr<PipelineContext>();
    frameNode_->context_ = AceType::RawPtr(context);

    /**
     * @tc.steps: step2. Set the isScrollEnd_ to false
     */
    pattern_->isScrollEnd_ = false;

    /**
     * @tc.steps: step3. Call the OnDirtyLayoutWrapperSwap
     * @tc.expected: The function result return true and the isScrollEnd_ to true
     */
    auto result = pattern_->ScrollListForFocus(2, 1, 2);
    frameNode_->context_ = nullptr;
    EXPECT_TRUE(pattern_->isScrollEnd_);
    EXPECT_TRUE(result);
}

/**
 * @tc.name: ToJsonValue
 * @tc.desc: Test ArcListPattern ToJsonValue
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, ToJsonValue, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    auto json = JsonUtil::Create(true);
    InspectorFilter filter;

    /**
     * @tc.steps: step2. Set the itemPosition_ of pattern
     * and set startIndex_ to 10
     */
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->startIndex_ = 10;

    /**
     * @tc.steps: step3. Call the ToJsonValue
     * @tc.expected: The value with the key "itemStartPos" becomes "3.0f"
     */
    pattern_->ToJsonValue(json, filter);
    EXPECT_EQ(json->GetInt("startIndex"), 10);
    EXPECT_EQ(json->GetDouble("itemStartPos"), 2.0);
    EXPECT_EQ(json->GetString("digitalCrownSensitivity"), "CrownSensitivity.MEDIUM");
}

/**
 * @tc.name: GetItemDisplayInfo
 * @tc.desc: Test ArcListPattern GetItemDisplayInfo
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetItemDisplayInfo, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    RefPtr<ListLayoutProperty> listLayoutProperty = AceType::MakeRefPtr<ListLayoutProperty>();
    listLayoutProperty->UpdateSpace(Dimension(2.0f));
    LayoutConstraintF layoutConstraintF;
    layoutConstraintF.maxSize = { 6, 6 };
    listLayoutProperty->contentConstraint_ = layoutConstraintF;

    /**
     * @tc.steps: step2. Set the value of the second key of the itemPosition_
     */
    ListItemInfo info = { 2, 2.0f, 4.0f, true };
    pattern_->itemPosition_[2] = info;
    pattern_->SetFriction(FRICTION);
    pattern_->scrollStartMidIndex_ = 3;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->spaceWidth_ = 4.0f;
    pattern_->itemStartIndex_ = -20;
    frameNode_->layoutProperty_ = listLayoutProperty;

    /**
     * @tc.steps: step3. Call the GetItemDisplayInfo
     * @tc.expected: The result of info is value of default
     */
    auto result = pattern_->GetItemDisplayInfo(3);
    EXPECT_EQ(result.offsetY, 0.0f);
}

/**
 * @tc.name: StartSnapAnimation
 * @tc.desc: Test ArcListPattern StartSnapAnimation
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, StartSnapAnimation, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the needed values
     */
    pattern_->startIndex_ = 0;
    pattern_->startMainPos_ = 20.0f;
    pattern_->currentDelta_ = 2.0f;
    pattern_->endMainPos_ = 15.0f;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->isStackFromEnd_ = false;

    /**
     * @tc.steps: step3. Call the StartSnapAnimation
     * @tc.expected: The result return false
     */
    SnapAnimationOptions snapAnimationOptions;
    auto result = pattern_->StartSnapAnimation(snapAnimationOptions);
    EXPECT_FALSE(result);
}

/**
 * @tc.name: GetScrollUpdateFriction
 * @tc.desc: Test ArcListPattern GetScrollUpdateFriction
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, GetScrollUpdateFriction, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the contentMainSize_ to 7.2f
     */
    pattern_->contentMainSize_ = 7.2f;

    /**
     * @tc.steps: step3. Call the StartSnapAnimation
     * @tc.expected: The result return ARC_LIST_DRAG_OVER_RATES
     */
    auto result = pattern_->GetScrollUpdateFriction(-6.0f);
    EXPECT_EQ(result, ARC_LIST_DRAG_OVER_RATES);
}

/**
 * @tc.name: HandleScrollBarOutBoundary001
 * @tc.desc: Test ArcListPattern HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, HandleScrollBarOutBoundary001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the IsOutOfBoundary function to return true
     * and set isScrollable_ to false
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->startIndex_ = 0;
    pattern_->endIndex_ = 6;
    pattern_->startMainPos_ = 20.0f;
    pattern_->endMainPos_ = 30.0f;
    pattern_->contentMainSize_ = 8.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->isStackFromEnd_ = false;
    pattern_->isScrollable_ = false;
    pattern_->scrollBarOutBoundaryExtent_ = 2.0f;

    /**
     * @tc.steps: step3. Call the HandleScrollBarOutBoundary
     * @tc.expected: The scrollBarOutBoundaryExtent_ be 0
     */
    pattern_->HandleScrollBarOutBoundary();
    EXPECT_EQ(pattern_->scrollBarOutBoundaryExtent_, 0);
}

/**
 * @tc.name: HandleScrollBarOutBoundary002
 * @tc.desc: Test ArcListPattern HandleScrollBarOutBoundary
 * @tc.type: FUNC
 */
HWTEST_F(ArcListPatternTestNg, HandleScrollBarOutBoundary002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the objects for test preparation
     */
    ListModelNG model = CreateList();
    CreateListItems(DEFAULT_ITEM_COUNT);
    CreateDone();
    pattern_->SetPredictSnapOffset(100.0);

    /**
     * @tc.steps: step2. Set the IsOutOfBoundary function to return true
     * and set isScrollable_ to true and it's the else if branch of the function that goes in
     */
    ListItemGroupLayoutInfo itemGroupInfo = { true, true };
    ListItemInfo info = { 2, 2.0f, 4.0f, true, false, 1.0f, 2.0f, itemGroupInfo };
    std::map<int32_t, ListItemInfo> itemPosition = { { 0, info } };
    pattern_->itemPosition_ = itemPosition;
    pattern_->scrollBar_ = AceType::MakeRefPtr<ScrollBar>(DisplayMode::AUTO);
    pattern_->startIndex_ = 2;
    pattern_->endIndex_ = 6;
    pattern_->maxListItemIndex_ = 6;
    pattern_->startMainPos_ = 20.0f;
    pattern_->endMainPos_ = 25.0f;
    pattern_->contentMainSize_ = 50.0f;
    pattern_->contentEndOffset_ = 4.0f;
    pattern_->contentStartOffset_ = 2.0f;
    pattern_->centerIndex_ = 0;
    pattern_->isStackFromEnd_ = false;
    pattern_->isScrollable_ = true;
    pattern_->scrollBarOutBoundaryExtent_ = 1.0f;

    /**
     * @tc.steps: step3. Call the HandleScrollBarOutBoundary
     * @tc.expected: The scrollBarOutBoundaryExtent_ be -1
     */
    pattern_->HandleScrollBarOutBoundary();
    EXPECT_EQ(pattern_->scrollBarOutBoundaryExtent_, -1);
}
} // namespace OHOS::Ace::NG