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
#include "test/unittest/core/pattern/waterflow/water_flow_test_ng.h"

#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: WaterFlowLayoutInfoTest002
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest002, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetStartMainPos and GetMainHeight
     * @tc.expected: step2. Check whether the return value is correct.
     */
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    int32_t crossIndex = info->items_[0].rbegin()->first;
    int32_t itemIndex = info->items_[0].rbegin()->second.rbegin()->first;
    EXPECT_EQ(info->GetStartMainPos(crossIndex + 1, itemIndex), 0.0f);
    EXPECT_EQ(info->GetMainHeight(crossIndex + 1, itemIndex), 0.0f);

    EXPECT_EQ(info->GetStartMainPos(crossIndex, itemIndex + 1), 0.0f);
    EXPECT_EQ(info->GetMainHeight(crossIndex, itemIndex + 1), 0.0f);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest003
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest003, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetMainCount function
     * @tc.expected: step2. Check whether the size is correct.
     */
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    std::size_t waterFlowItemsSize = info->items_[0].size();
    int32_t mainCount = info->GetMainCount();

    int32_t index = info->items_[0].rbegin()->first;
    info->items_[0][index + 1] = std::map<int32_t, std::pair<float, float>>();
    EXPECT_EQ(info->items_[0].size(), waterFlowItemsSize + 1);
    EXPECT_EQ(info->GetMainCount(), mainCount);

    auto lastItem = info->items_[0].begin()->second.rbegin();
    float mainSize = lastItem->second.first + lastItem->second.second - 1.0f;
    EXPECT_FALSE(info->IsAllCrossReachEnd(mainSize));

    info->ClearCacheAfterIndex(index + 1);
    EXPECT_EQ(info->items_[0].size(), waterFlowItemsSize + 1);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest004
 * @tc.desc: Test Reset functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest004, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test Reset function
     * @tc.expected: step2. Check whether the endIndex_ is correct.
     */
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    int32_t resetFrom = pattern_->layoutInfo_->endIndex_;
    info->Reset(resetFrom + 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, resetFrom);

    info->Reset(resetFrom - 1);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, resetFrom);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest005
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest005, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {});

    /**
     * @tc.steps: Test GetMaxMainHeight function
     * @tc.expected: step2. Check whether the return value is correct.
     */
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);

    float maxMainHeight = info->GetMaxMainHeight();
    int32_t crossIndex = info->items_[0].rbegin()->first;
    info->items_[0][crossIndex + 1][0] = std::pair<float, float>(1.0f, maxMainHeight);
    info->itemInfos_.clear();
    info->endPosArray_.clear();
    EXPECT_EQ(info->GetMaxMainHeight(), maxMainHeight + 1.0f);

    /**
     * @tc.steps: Test GetCrossIndexForNextItem function
     * @tc.expected: step3. Check whether the return value is correct.
     */
    info->items_[0][crossIndex + 1][1] = std::pair<float, float>(0.0f, 0.0f);
    FlowItemIndex position = info->GetCrossIndexForNextItem(0);
    EXPECT_EQ(position.crossIndex, crossIndex + 1);
    EXPECT_EQ(position.lastItemIndex, 1);
}

/**
 * @tc.name: WaterFlowTest007
 * @tc.desc: waterFlow with fixed column, scroll to index not fully showed at last line
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest007, TestSize.Level1)
{
    CreateWithItem([](WaterFlowModelNG model) {
        ViewAbstract::SetWidth(CalcLength(WATERFLOW_WIDTH));
        ViewAbstract::SetHeight(CalcLength(200.f));
        model.SetColumnsTemplate("1fr 1fr 1fr");
    });
    pattern_->UpdateStartIndex(8);
    FlushLayoutTask(frameNode_);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 4)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 5)->IsActive());
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 6)->IsActive());
}

/**
 * @tc.name: UpdateCurrentOffset003
 * @tc.desc: Test the firstIndex and endIndex after UpdateCurrentOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, UpdateCurrentOffset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.steps: step2. scroll up to a remote position
     * @tc.expected: startIndex_ = 0 endIndex_ = 0.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(10000, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->FirstIdx(), 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 0);

    /**
     * @tc.steps: step1. create waterFlow
     * @tc.steps: step2. scroll down to a remote position
     * @tc.expected: startIndex_ = TOTAL_LINE_NUMBER * 2 - 1, endIndex_ = TOTAL_LINE_NUMBER * 2 - 1.
     */
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(-99999, SCROLL_FROM_UPDATE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->layoutInfo_->FirstIdx(), 19);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 19);
}

/**
 * @tc.name: onWillScrollAndOnDidScroll001
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnWillScrollAndOnDidScroll001, TestSize.Level1)
{
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    CalcDimension offsetY;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](CalcDimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState = ScrollState::IDLE;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    CreateWithItem([onScroll](WaterFlowModelNG model) { model.SetOnScroll(onScroll); });
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onWillScroll and onDidScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: onScroll
 * @tc.desc: Test onScroll event
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OnWillScrollAndOnDidScroll002, TestSize.Level1)
{
    bool isOnScrollCallBack = false;
    bool isOnWillScrollCallBack = false;
    bool isOnDidScrollCallBack = false;

    CalcDimension offsetY;
    ScrollState scrollState = ScrollState::IDLE;
    auto onScroll = [&offsetY, &scrollState, &isOnScrollCallBack](CalcDimension offset, ScrollState state) {
        offsetY = offset;
        scrollState = state;
        isOnScrollCallBack = true;
    };
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
    Dimension didScrollOffset;
    ScrollState didScrollState = ScrollState::IDLE;
    auto onDidScroll = [&didScrollOffset, &didScrollState, &isOnDidScrollCallBack](
                           Dimension offset, ScrollState state) {
        didScrollOffset = offset;
        didScrollState = state;
        isOnDidScrollCallBack = true;
    };

    CreateWithItem([onScroll](WaterFlowModelNG model) {
        model.SetOnScroll(onScroll);
        model.SetLayoutDirection(FlexDirection::ROW);
    });
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_HEIGHT * 5);
    EXPECT_EQ(scrollState, willScrollState);
    EXPECT_EQ(scrollState, didScrollState);
}

/**
 * @tc.name: ModifyItem001
 * @tc.desc: Test WaterFlow reacting to child height change.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ModifyItem002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Calling the ScrollToIndex interface to set values to 20 and true.
     * @tc.expected: pattern_->targetIndex_ is 20
     */
    CreateWithItem([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(80);
    });
    auto info = pattern_->layoutInfo_;

    pattern_->ScrollToIndex(50, false, ScrollAlign::CENTER);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 43);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    auto child = GetChildFrameNode(frameNode_, 49);
    child->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(300.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(info->startIndex_, 43);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    EXPECT_EQ(GetChildHeight(frameNode_, 49), 300.0f);
}

/**
 * @tc.name: OverScroll001
 * @tc.desc: Test overScroll past limits
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, OverScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow
     * @tc.expected: startIndex_ = 0 endIndex_ = 10.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        model.SetFooter(GetDefaultHeaderBuilder());
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateItem(50);
    });
    pattern_->SetAnimateCanOverScroll(true);
    auto info = pattern_->layoutInfo_;
    for (int i = 0; i < 50; ++i) {
        UpdateCurrentOffset(500.0f);
        EXPECT_EQ(info->startIndex_, 0);
        EXPECT_GT(info->Offset(), 0.0f);
    }
    EXPECT_GT(info->Offset(), 2500.0f);
    UpdateCurrentOffset(-25500.0f);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);
    pattern_->ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
    FlushLayoutTask(frameNode_);
    for (int i = 0; i < 50; ++i) {
        UpdateCurrentOffset(-200.0f);
        EXPECT_EQ(info->endIndex_, std::max(49, info->footerIndex_));
        EXPECT_EQ(info->BottomFinalPos(800.0f), -3050.0f);
    }
    EXPECT_LT(info->Offset(), -4000.0f);
}

/**
 * @tc.name: WaterFlowLayoutInfoTest001
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest001, TestSize.Level1)
{
    Create([](WaterFlowModelNG model) {
        model.SetRowsTemplate("1fr 1fr");
        model.SetRowsGap(Dimension(5));
        for (int32_t i = 0; i < TOTAL_LINE_NUMBER; i++) {
            WaterFlowItemModelNG waterFlowItemModel;
            waterFlowItemModel.Create();
            ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
            ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_HEIGHT)));
            ViewStackProcessor::GetInstance()->Pop();
        }
    });

    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    /**
     * @tc.steps: Test IsAllCrossReachEnd function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = info->IsAllCrossReachEnd(ITEM_HEIGHT);
    EXPECT_TRUE(reached);
    reached = info->IsAllCrossReachEnd(WATERFLOW_HEIGHT);
    EXPECT_TRUE(reached);

    /**
     * @tc.steps: Test GetEndIndexByOffset function
     * @tc.expected: step2. Check whether the return value is correct.
     */
    auto offset = info->GetEndIndexByOffset(0);
    EXPECT_EQ(0, offset);
    offset = info->GetEndIndexByOffset(-100.f);
    EXPECT_EQ(1, offset);
}

/**
 * @tc.name: WaterFlowTest012
 * @tc.desc: Test GetOverScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest012, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create waterFlow that is less than one screen
     * @tc.expected: itemStart_ = true  itemEnd_ = true.
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER);
    });
    EXPECT_TRUE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_->offsetEnd_);
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    if (info) {
        EXPECT_EQ(info->maxHeight_, 500);
    }
    EXPECT_EQ(pattern_->layoutInfo_->lastMainSize_, 800);

    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_HEIGHT), { 100, 100 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(3 * ITEM_HEIGHT), { 300, 300 }));
}

/**
 * @tc.name: PositionController100
 * @tc.desc: Test PositionController AnimateTo and ScrollTo
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, PositionController100, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List Item
     */
    Create([](WaterFlowModelNG model) {
        model.SetColumnsTemplate("1fr 1fr");
        CreateItem(TOTAL_LINE_NUMBER * 2);
    });
    auto controller = pattern_->positionController_;
    /**
     * @tc.steps: step8. Test AnimateTo function
     * @tc.expected: pattern_->isAnimationStop_ is false
     */
    pattern_->AnimateTo(1.5, 1.f, Curves::LINEAR, false, false);
    EXPECT_FALSE(pattern_->isAnimationStop_);

	/**
     * @tc.steps: step8. test event
     * @tc.expected: return the scroll event is ture.
     */
    bool isOnWillScrollCallBack = false;
    Dimension willScrollOffset;
    ScrollState willScrollState;
    auto onWillScroll = [&willScrollOffset, &willScrollState, &isOnWillScrollCallBack](
                            Dimension offset, ScrollState state, ScrollSource source) {
        willScrollOffset = offset;
        willScrollState = state;
        isOnWillScrollCallBack = true;
        ScrollFrameResult result;
        result.offset = offset;
        return result;
    };
	
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    pattern_->ScrollTo(ITEM_HEIGHT * 5);
    EXPECT_TRUE(isOnWillScrollCallBack);
}
} // namespace OHOS::Ace::NG
