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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "water_flow_test_ng.h"

#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/waterflow/layout/top_down/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

namespace OHOS::Ace::NG {
/**
 * @tc.name: WaterFlowLayoutInfoTest002
 * @tc.desc: Test functions in WaterFlowLayoutInfo.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowLayoutInfoTest002, TestSize.Level1)
{
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

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
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

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
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

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
    CreateWaterFlow();
    CreateWaterFlowItems();
    CreateDone();

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
    WaterFlowModelNG model = CreateWaterFlow();
    ViewAbstract::SetWidth(CalcLength(WATER_FLOW_WIDTH));
    ViewAbstract::SetHeight(CalcLength(200.f));
    model.SetColumnsTemplate("1fr 1fr 1fr");
    CreateWaterFlowItems();
    CreateDone();
    pattern_->UpdateStartIndex(8);
    FlushUITasks();
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(10000, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->FirstIdx(), 0);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 0);

    /**
     * @tc.steps: step1. create waterFlow
     * @tc.steps: step2. scroll down to a remote position
     * @tc.expected: startIndex_ = TOTAL_LINE_NUMBER * 2 - 1, endIndex_ = TOTAL_LINE_NUMBER * 2 - 1.
     */
    pattern_->SetAnimateCanOverScroll(true);
    pattern_->UpdateCurrentOffset(-99999, SCROLL_FROM_UPDATE);
    FlushUITasks();
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

    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScroll(onScroll);
    CreateWaterFlowItems();
    CreateDone();
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onWillScroll and onDidScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 5);
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

    WaterFlowModelNG model = CreateWaterFlow();
    model.SetOnScroll(onScroll);
    model.SetLayoutDirection(FlexDirection::ROW);
    CreateWaterFlowItems();
    CreateDone();
    eventHub_->SetOnWillScroll(std::move(onWillScroll));
    eventHub_->SetOnDidScroll(std::move(onDidScroll));

    /**
     * @tc.steps: step1. finger moves down at top
     * @tc.expected: Trigger onScroll with SCROLL state
     */
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    FlushUITasks();
    EXPECT_TRUE(isOnScrollCallBack);
    EXPECT_TRUE(isOnWillScrollCallBack);
    EXPECT_TRUE(isOnDidScrollCallBack);
    EXPECT_EQ(offsetY.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(willScrollOffset.Value(), ITEM_MAIN_SIZE * 5);
    EXPECT_EQ(didScrollOffset.Value(), ITEM_MAIN_SIZE * 5);
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(80);
    CreateDone();
    auto info = pattern_->layoutInfo_;

    ScrollToIndex(50, false, ScrollAlign::CENTER);
    EXPECT_EQ(info->startIndex_, 43);
    EXPECT_EQ(GetChildY(frameNode_, 45), -50.0f);
    auto child = GetChildFrameNode(frameNode_, 49);
    child->layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(300.0)));
    child->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    FlushUITasks();
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetFooter(GetDefaultHeaderBuilder());
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(50);
    CreateDone();
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
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, false);
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetRowsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(5));
    for (int32_t i = 0; i < TOTAL_LINE_NUMBER; i++) {
        WaterFlowItemModelNG waterFlowItemModel;
        waterFlowItemModel.Create();
        ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
        ViewAbstract::SetHeight(CalcLength(Dimension(ITEM_MAIN_SIZE)));
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();

    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    /**
     * @tc.steps: Test IsAllCrossReachEnd function
     * @tc.expected: step1. Check whether the return value is correct.
     */
    auto reached = info->IsAllCrossReachEnd(ITEM_MAIN_SIZE);
    EXPECT_TRUE(reached);
    reached = info->IsAllCrossReachEnd(WATER_FLOW_HEIGHT);
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr 1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER);
    CreateDone();
    EXPECT_TRUE(pattern_->layoutInfo_->itemStart_);
    EXPECT_TRUE(pattern_->layoutInfo_->itemEnd_);
    EXPECT_TRUE(pattern_->layoutInfo_->offsetEnd_);
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    if (info) {
        EXPECT_EQ(info->maxHeight_, 500);
    }
    EXPECT_EQ(pattern_->layoutInfo_->lastMainSize_, 800);

    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(ITEM_MAIN_SIZE), { 100, 0 }));
    EXPECT_TRUE(IsEqual(pattern_->GetOverScrollOffset(3 * ITEM_MAIN_SIZE), { 300, 0 }));
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
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
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
    pattern_->ScrollTo(ITEM_MAIN_SIZE * 5);
    EXPECT_TRUE(isOnWillScrollCallBack);
}

/**
 * @tc.name: EstimateTotalHeight001
 * @tc.desc: Test EstimateTotalHeight.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, EstimateTotalHeight001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 4);
    CreateDone();
    FlushUITasks();
    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    EXPECT_EQ(info->startIndex_, 0);
    EXPECT_EQ(info->endIndex_, 10);

    int32_t childCount = 0;
    for (const auto& item : info->items_[0]) {
        childCount += item.second.size();
    }
    EXPECT_EQ(info->EstimateTotalHeight(), info->GetMaxMainHeight() / childCount * info->childrenCount_);

    pattern_->UpdateCurrentOffset(-5000.f, SCROLL_FROM_UPDATE);
    FlushUITasks();
    EXPECT_EQ(info->startIndex_, 31);
    EXPECT_EQ(info->endIndex_, TOTAL_LINE_NUMBER * 4 - 1);
    EXPECT_EQ(info->EstimateTotalHeight(), info->maxHeight_);
}

/**
 * @tc.name: ScrollToIndex004
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    /**
     * @tc.steps: step1. scrollToIndex without animation
     * @tc.expected: GetTotalOffset is right
     */
    std::optional<float> extraOffset = 0.f;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 100.f);

    extraOffset = -200.f;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 0.f);

    ScrollToIndex(27, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1500.f);

    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1300.f);

    extraOffset = 200.f;
    ScrollToIndex(2, false, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 300.f);

    ScrollToIndex(27, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1500.f);

    ScrollToIndex(LAST_ITEM, false, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetTotalOffset(), 1500.f);
}

/**
 * @tc.name: ScrollToIndex005
 * @tc.desc: Test ScrollToIndex with extraOffset
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ScrollToIndex005, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    /**
     * @tc.steps: step1. scrollToIndex with animation
     * @tc.expected: finalPosition_ is right
     */
    std::optional<float> extraOffset = 0.f;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 100.f);

    extraOffset = -200.f;
    ScrollToIndex(2, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -100.f);

    ScrollToIndex(27, true, ScrollAlign::START, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1800.f);

    extraOffset = 200.f;
    ScrollToIndex(2, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), -400.f);

    ScrollToIndex(27, true, ScrollAlign::END, extraOffset);
    EXPECT_FLOAT_EQ(pattern_->GetFinalPosition(), 1600.f);
}

/**
 * @tc.name: Cache002
 * @tc.desc: Test cache item layout position
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Cache002, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });
    model.SetCachedCount(3);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();

    ScrollToIndex(30, false, ScrollAlign::START);
    const auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 28);
    EXPECT_EQ(info->endIndex_, 39);
    const std::list<int32_t> preloadList = { 40, 41, 42 };
    EXPECT_EQ(pattern_->preloadItems_, preloadList);
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    EXPECT_TRUE(GetChildFrameNode(frameNode_, 40));
    EXPECT_EQ(GetChildWidth(frameNode_, 40), (WATER_FLOW_WIDTH - 10.0f) / 2.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 40), 850.0f);
    EXPECT_EQ(GetChildY(frameNode_, 26), -320.0f);

    UpdateCurrentOffset(300.0f);
    EXPECT_EQ(info->startIndex_, 24);
    EXPECT_EQ(info->endIndex_, 35);
    // item in cache range shouldn't be created yet
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22));
    PipelineContext::GetCurrentContext()->OnIdle(INT64_MAX);
    ASSERT_TRUE(GetChildFrameNode(frameNode_, 22));
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22)->IsActive());
    FlushUITasks();
    EXPECT_EQ(GetChildY(frameNode_, 22), -340.0f);
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 22)->IsActive());
}

/**
 * @tc.name: Refresh002
 * @tc.desc: Test WaterFlow nested in refresh. Currently have different friction from SW mode
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, Refresh002, TestSize.Level1)
{
    MockAnimationManager::GetInstance().SetTicks(1);
    MockAnimationManager::GetInstance().Reset();
    RefreshModelNG refreshModel;
    refreshModel.Create();
    auto refreshNode = AceType::DynamicCast<FrameNode>(ViewStackProcessor::GetInstance()->GetMainElementNode());
    auto model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(3);
    CreateDone();

    GestureEvent info;
    info.SetMainVelocity(-1200.f);
    info.SetMainDelta(-100.f);
    auto scrollable = pattern_->GetScrollableEvent()->GetScrollable();
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -31.505754);

    EXPECT_TRUE(pattern_->OutBoundaryCallback());
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -60.800022);

    MockAnimationManager::GetInstance().TickByVelocity(-100.0f);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -160.80002);
    // swipe in the opposite direction
    info.SetMainVelocity(1200.f);
    info.SetMainDelta(200.f);
    scrollable->HandleTouchDown();
    scrollable->HandleDragStart(info);
    scrollable->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -128.9174);
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 0.0f);
    scrollable->HandleTouchUp();
    scrollable->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_FLOAT_EQ(GetChildY(frameNode_, 0), -96.869041);
    MockAnimationManager::GetInstance().TickByVelocity(1000.0f);
    FlushUITasks();
    EXPECT_TRUE(NearZero(GetChildY(frameNode_, 0)));
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 800);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearZero(GetChildY(frameNode_, 0)));
    // can't enter the refreshing status when refresh updates scroll offset by animation source
    EXPECT_EQ(frameNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 0);
    EXPECT_TRUE(MockAnimationManager::GetInstance().AllFinished());
}

/**
 * @tc.name: WaterFlowTest016
 * @tc.desc: Test prevOffset_ when update offset repeatedly in one frame.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest016, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(20);
    CreateDone();
    UpdateCurrentOffset(-500.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 17);
    EXPECT_EQ(pattern_->GetPrevOffset(), -500.0f);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -500.0f);

    pattern_->UpdateCurrentOffset(-10.0f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -510.0f);
    EXPECT_EQ(pattern_->GetPrevOffset(), -500.0f);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -510.0f);
    EXPECT_EQ(pattern_->GetPrevOffset(), -510.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 18);

    pattern_->UpdateCurrentOffset(-10.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(-5.0f, SCROLL_FROM_UPDATE);
    pattern_->UpdateCurrentOffset(20.0f, SCROLL_FROM_UPDATE);
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -505.0f);
    EXPECT_EQ(pattern_->GetPrevOffset(), -510.0f);
    FlushUITasks();
    EXPECT_EQ(pattern_->layoutInfo_->Offset(), -505.0f);
    EXPECT_EQ(pattern_->GetPrevOffset(), -505.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 7);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 18);
}

/**
 * @tc.name: WaterFlowTest017.
 * @tc.desc: Test endIndex when there has a flowItem with a height of 0 at the end.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest017, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr");
    CreateWaterFlowItems(10);
    CreateDone();
    AddItemsAtSlot(2, 0.0f, 10);
    UpdateCurrentOffset(-1500.0f);
    EXPECT_EQ(pattern_->layoutInfo_->startIndex_, 5);
    EXPECT_EQ(pattern_->layoutInfo_->endIndex_, 11);
    EXPECT_EQ(GetChildY(frameNode_, 9), WATER_FLOW_HEIGHT - GetChildHeight(frameNode_, 9));
    EXPECT_EQ(GetChildY(frameNode_, 10), WATER_FLOW_HEIGHT);
    EXPECT_EQ(GetChildY(frameNode_, 11), WATER_FLOW_HEIGHT);
}

/**
 * @tc.name: WaterFlowTest018.
 * @tc.desc: Test layout after changing the dataSource.
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, WaterFlowTest018, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(30);
    CreateDone();

    auto info = AceType::DynamicCast<WaterFlowLayoutInfo>(pattern_->layoutInfo_);
    // slide to bottom.
    UpdateCurrentOffset(-4500.0f);
    EXPECT_EQ(info->startIndex_, 19);
    EXPECT_EQ(info->endIndex_, 29);
    EXPECT_EQ(info->GetContentHeight(), 2300.0f);
    EXPECT_EQ(info->items_[0][0].size() + info->items_[0][1].size(), 30);

    // slide backward.
    UpdateCurrentOffset(1000.0f);
    EXPECT_EQ(info->startIndex_, 7);
    EXPECT_EQ(info->endIndex_, 17);
    EXPECT_EQ(info->GetContentHeight(), 2300.0f);

    // delete a flowItem.
    frameNode_->RemoveChildAtIndex(20);
    frameNode_->ChildrenUpdatedFrom(20);
    pattern_->MarkDirtyNodeSelf();
    FlushUITasks();
    EXPECT_EQ(info->startIndex_, 7);
    EXPECT_EQ(info->endIndex_, 17);
    EXPECT_EQ(info->items_[0][0].size() + info->items_[0][1].size(), 20);
    EXPECT_EQ(info->GetContentHeight(), 1600.0f);

    // slide forward.
    UpdateCurrentOffset(-1000.0f);
    EXPECT_EQ(info->startIndex_, 19);
    EXPECT_EQ(info->endIndex_, 28);
    EXPECT_EQ(info->GetContentHeight(), 2300.0f);
    EXPECT_EQ(info->items_[0][0].size() + info->items_[0][1].size(), 29);
}

/*
 * @tc.name: ShowCache003
 * @tc.desc: Test cache items immediately changing layout
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTestNg, ShowCache003, TestSize.Level1)
{
    auto model = CreateWaterFlow();
    CreateItemsInRepeat(50, [](int32_t i) { return i % 2 ? 100.0f : 200.0f; });
    model.SetCachedCount(3, true);
    model.SetColumnsTemplate("1fr 1fr");
    model.SetRowsGap(Dimension(10));
    model.SetColumnsGap(Dimension(10));
    CreateDone();

    ASSERT_TRUE(GetChildFrameNode(frameNode_, 13));
    EXPECT_EQ(GetChildY(frameNode_, 13), 960.0f);
    EXPECT_EQ(GetChildX(frameNode_, 13), 245.0f);

    UpdateCurrentOffset(-300.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);

    layoutProperty_->UpdateColumnsTemplate("1fr");
    FlushUITasks();
    const auto info = pattern_->layoutInfo_;
    EXPECT_EQ(info->startIndex_, 1);
    EXPECT_EQ(info->endIndex_, 6);
    EXPECT_EQ(GetChildWidth(frameNode_, 1), 480.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 9), 480.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 1190.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -300.0f);

    UpdateCurrentOffset(-50.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -350.0f);
    EXPECT_EQ(GetChildY(frameNode_, 9), 1140.0f);
}

class WaterFlowTopDownScrollerTestNg : public WaterFlowTestNg, public testing::WithParamInterface<bool> {};

/**
 * @tc.name: ScrollToIndex_Align001
 * @tc.desc: Test ScrollToIndex with ScrollAlign::START
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollToIndex_Align001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::START;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    EXPECT_TRUE(pattern_->IsAtTop());

    // Scroll to the first item in row in view
    ScrollToIndex(2, smooth, align);
    EXPECT_TRUE(TickPosition(-100.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(4, smooth, align);
    EXPECT_TRUE(TickPosition(-200.0f));

    // Scroll to the item out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(TickPosition(-800.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll with invalid index
    ScrollToIndex(-100, smooth, align);
    EXPECT_TRUE(TickPosition(0));
    ScrollToIndex(100, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    EXPECT_TRUE(TickPosition(-800.0f));
}

/**
 * @tc.name: ScrollToIndex_Align002
 * @tc.desc: Test ScrollToIndex with ScrollAlign::CENTER
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollToIndex_Align002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::CENTER;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row in view
    ScrollToIndex(6, smooth, align);
    EXPECT_TRUE(TickPosition(-50.0f));

    // Scroll to the last item in row in view
    ScrollToIndex(8, smooth, align);
    EXPECT_TRUE(TickPosition(-150.0f));

    // Scroll to the item out of view
    ScrollToIndex(15, smooth, align);
    EXPECT_TRUE(TickPosition(-800.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    EXPECT_TRUE(TickPosition(-800.0f));
}

/**
 * @tc.name: ScrollToIndex_Align003
 * @tc.desc: Test ScrollToIndex with ScrollAlign::END
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollToIndex_Align003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::END;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row in view
    ScrollToIndex(3, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(14, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(13, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth && SystemProperties::WaterFlowUseSegmentedLayout()) {
        EXPECT_TRUE(TickPosition(0));
    } else {
        EXPECT_TRUE(TickPosition(-800.0f));
    }
}

/**
 * @tc.name: ScrollToIndex_Align004
 * @tc.desc: Test ScrollToIndex with ScrollAlign::AUTO
 * @tc.desc: Scroll to (first/inView/outOfView/last) item (with/without) animation
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollToIndex_Align004, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    // Scroll to the first item
    bool smooth = GetParam();
    ScrollAlign align = ScrollAlign::AUTO;
    ScrollToIndex(0, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row in view
    ScrollToIndex(3, smooth, align);
    EXPECT_TRUE(TickPosition(0));

    // Scroll to the first item in row out of view
    ScrollToIndex(14, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll to the last item in row out of view
    ScrollToIndex(13, smooth, align);
    EXPECT_TRUE(TickPosition(-300.0f));

    // Scroll back
    ScrollToIndex(1, smooth, align);
    if (smooth) {
        EXPECT_TRUE(TickPosition(-300.0f));
    } else {
        EXPECT_TRUE(TickPosition(0));
    }

    // Scroll to the last item
    ScrollToIndex(LAST_ITEM, smooth, align);
    if (smooth && SystemProperties::WaterFlowUseSegmentedLayout()) {
        EXPECT_TRUE(TickPosition(-300.0f));
    } else {
        EXPECT_TRUE(TickPosition(-800.0f));
    }
}

/**
 * @tc.name: AnimateTo001
 * @tc.desc: Test AnimateTo Function.
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, AnimateTo001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    bool smooth = GetParam();
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(10000.0f), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(-800.0f));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 0, nullptr, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: AnimateTo002
 * @tc.desc: Test AnimateTo with duration animation
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, AnimateTo002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. AnimateTo the position in the scroll
     * @tc.expected: AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can not over scroll
     */
    AnimateTo(Dimension(10000.0f), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(-800.0f));

    /**
     * @tc.steps: step3. AnimateTo the top
     * @tc.expected: AnimateTo the top
     */
    AnimateTo(Dimension(0), 1000.0f, Curves::EASE, false);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollBy001
 * @tc.desc: Test ScrollBy
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollBy001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. ScrollBy the position
     * @tc.expected: ScrollBy the position
     */
    bool smooth = GetParam();
    ScrollBy(0, ITEM_MAIN_SIZE, smooth);
    EXPECT_TRUE(TickPosition(-ITEM_MAIN_SIZE));

    /**
     * @tc.steps: step2. ScrollBy the position over the scroll
     * @tc.expected: ScrollBy the bottom, can not over scroll
     */
    ScrollBy(0, 10000.0f, smooth);
    EXPECT_TRUE(TickPosition(-800.0f));

    /**
     * @tc.steps: step3. ScrollBy the position 0
     * @tc.expected: Not scroll
     */
    ScrollBy(0, 0, smooth);
    EXPECT_TRUE(TickPosition(-800.0f));

    /**
     * @tc.steps: step4. ScrollBy the position to top
     * @tc.expected: ScrollBy the top
     */
    ScrollBy(0, -1000.0f, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollToEdge001
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollToEdge001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    bool smooth = GetParam();
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, smooth);
    EXPECT_TRUE(TickPosition(-800.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, smooth);
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: ScrollPage001
 * @tc.desc: Test ScrollPage
 * @tc.type: FUNC
 */
HWTEST_P(WaterFlowTopDownScrollerTestNg, ScrollPage001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. ScrollPage down
     * @tc.expected: Scroll down
     */
    bool smooth = GetParam();
    ScrollPage(false, smooth);
    EXPECT_TRUE(TickPosition(-WATER_FLOW_HEIGHT));

    /**
     * @tc.steps: step2. ScrollPage up
     * @tc.expected: Scroll up
     */
    ScrollPage(true, smooth);
    EXPECT_TRUE(TickPosition(0));
}

INSTANTIATE_TEST_SUITE_P(Smooth, WaterFlowTopDownScrollerTestNg, testing::Bool());

/**
 * @tc.name: AnimateTo003
 * @tc.desc: Test AnimateTo with duration animation, canOverScroll
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTopDownScrollerTestNg, AnimateTo003, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. AnimateTo the position over the scroll
     * @tc.expected: AnimateTo the bottom, can over scroll
     */
    MockAnimationManager::GetInstance().SetTicks(5);
    bool canOverScroll = true;
    bool smooth = false;
    AnimateTo(Dimension(1000.0f), 1000.0f, Curves::EASE, smooth, canOverScroll);
    EXPECT_TRUE(TickPosition(-200.0f));
    EXPECT_TRUE(TickPosition(-400.0f));
    EXPECT_TRUE(TickPosition(-600.0f));
    EXPECT_TRUE(TickPosition(-800.0f)); // Tick doesn't advance new animations created within the same tick
    EXPECT_TRUE(TickPosition(-1000.0f));
    EXPECT_TRUE(TickPosition(-960.0f));
    EXPECT_TRUE(TickPosition(-920.0f));
    EXPECT_TRUE(TickPosition(-880.0f));
    EXPECT_TRUE(TickPosition(-840.0f));
    EXPECT_TRUE(TickPosition(-800.0f));
}

/**
 * @tc.name: ScrollToEdge002
 * @tc.desc: Test ScrollToEdge
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTopDownScrollerTestNg, ScrollToEdge002, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. SCROLL_BOTTOM
     * @tc.expected: Scroll to bottom with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_BOTTOM, 200.0f);
    EXPECT_TRUE(Position(-800.0f));

    /**
     * @tc.steps: step2. SCROLL_TOP
     * @tc.expected: Scroll to top with animation
     */
    ScrollToEdge(ScrollEdgeType::SCROLL_TOP, 200.0f);
    EXPECT_TRUE(Position(0));
}

/**
 * @tc.name: Fling001
 * @tc.desc: Test Fling
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTopDownScrollerTestNg, Fling001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();

    /**
     * @tc.steps: step1. Fling, the flingVelocity greater than 0
     * @tc.expected: Scroll down
     */
    MockAnimationManager::GetInstance().SetTicks(2);
    const float finalPosition = 100.f;
    const float flingVelocity = finalPosition * FRICTION * FRICTION_SCALE;
    Fling(flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / 2));
    EXPECT_TRUE(TickPosition(-finalPosition));

    /**
     * @tc.steps: step2. Fling, the flingVelocity less than 0
     * @tc.expected: Scroll up
     */
    Fling(-flingVelocity);
    EXPECT_TRUE(TickPosition(-finalPosition / 2));
    EXPECT_TRUE(TickPosition(0));
}

/**
 * @tc.name: GetInfo001
 * @tc.desc: Test non-action GetCurrentOffset/GetScrollDirection/IsAtEnd/GetItemRect
 * @tc.type: FUNC
 */
HWTEST_F(WaterFlowTopDownScrollerTestNg, GetInfo001, TestSize.Level1)
{
    WaterFlowModelNG model = CreateWaterFlow();
    model.SetColumnsTemplate("1fr 1fr");
    CreateWaterFlowItems(TOTAL_LINE_NUMBER * 2);
    CreateDone();
    EXPECT_EQ(GetScrollDirection(), Axis::VERTICAL);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset()));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect(0, 0, WATER_FLOW_WIDTH / 2, ITEM_MAIN_SIZE)));
    EXPECT_TRUE(IsEqual(GetItemRect(15), Rect()));

    /**
     * @tc.steps: step1. AnimateTo the position
     */
    AnimateTo(Dimension(ITEM_MAIN_SIZE), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, ITEM_MAIN_SIZE)));
    EXPECT_FALSE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(0), Rect()));
    EXPECT_TRUE(IsEqual(GetItemRect(1), Rect(WATER_FLOW_WIDTH / 2, -ITEM_MAIN_SIZE, WATER_FLOW_WIDTH / 2, 200.0f)));
    EXPECT_TRUE(IsEqual(GetItemRect(15), Rect()));

    /**
     * @tc.steps: step2. AnimateTo bottom
     */
    AnimateTo(Dimension(10000.0f), 0, nullptr, false);
    EXPECT_TRUE(IsEqual(GetCurrentOffset(), Offset(0, 800.0f)));
    EXPECT_TRUE(IsAtEnd());
    EXPECT_TRUE(IsEqual(GetItemRect(5), Rect()));
    EXPECT_TRUE(IsEqual(GetItemRect(15), Rect(0, 300.0f, 240.0f, 200.0f)));
}
} // namespace OHOS::Ace::NG
