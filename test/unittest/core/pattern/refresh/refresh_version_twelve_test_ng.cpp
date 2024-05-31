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

#include "refresh_test_ng.h"

namespace OHOS::Ace::NG {

namespace {} // namespace
constexpr Dimension TEN_OFFSET = 10.0_vp;
constexpr Dimension ZERO_OFFSET = 0.0_vp;
constexpr Dimension MINUS_OFFSET = -1.0_vp;
constexpr Dimension DRAG_OFFSET = 640.0_vp;
constexpr Dimension OVERDRAG_OFFSET = 32.0_vp;

class RefreshVersionTwelveTestNg : public RefreshTestNg {
public:
};
/**
 * @tc.name: AttrRefreshOffset01
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset01, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create();

    /**
     * @tc.steps: step1. UpdateRefreshOffset: 64vp -> 10vp
     * @tc.expected: refreshOffset_ == 10vp
     */
    layoutProperty_->UpdateRefreshOffset(TEN_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshOffset_, TEN_OFFSET);
}

/**
 * @tc.name: AttrRefreshOffset02
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset02, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create();

    /**
     * @tc.steps: step1. UpdateRefreshOffset: 64vp -> 0vp
     * @tc.expected: refreshOffset_ == 64vp
     */
    layoutProperty_->UpdateRefreshOffset(ZERO_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);
}

/**
 * @tc.name: AttrRefreshOffset03
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset03, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create();

    /**
     * @tc.steps: step1. UpdateRefreshOffset: 64vp -> -1vp
     * @tc.expected: refreshOffset_ == 64vp
     */
    layoutProperty_->UpdateRefreshOffset(MINUS_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);
}


/**
 * @tc.name: AttrRefreshOffset04
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset04, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnStateChange(std::move(onStateChange));
    });

    /**
     * @tc.steps: step1. refreshOffset_: -> 640vp
     * @tc.expected: refreshOffset_: -> 640vp
     */
    layoutProperty_->UpdateRefreshOffset(DRAG_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshOffset_, DRAG_OFFSET);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),but refreshOffset_ = 640vp,
     *               onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx()
                               / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
}

/**
 * @tc.name: AttrRefreshOffset05
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset05, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnStateChange(std::move(onStateChange));
    });

        /**
     * @tc.steps: step1. refreshOffset_: -> 32vp
     * @tc.expected: refreshOffset_: -> 32vp
     */
    layoutProperty_->UpdateRefreshOffset(OVERDRAG_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshOffset_, OVERDRAG_OFFSET);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: scrollOffset_ is 32.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((OVERDRAG_OFFSET).ConvertToPx()
                               / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
}

/**
 * @tc.name: AttrPullToRefresh01
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh01, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create([](RefreshModelNG model) {
        model.SetCustomBuilder(CreateCustomNode());
    });

    /**
     * @tc.steps: step1. PullToRefresh: false -> true
     * @tc.expected: pullToRefresh_ == true
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrPullToRefresh02
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh02, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create([](RefreshModelNG model) {
        model.SetCustomBuilder(CreateCustomNode());
    });

    /**
     * @tc.steps: step1. PullToRefresh: -> false
     * @tc.expected: pullToRefresh_ == false
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrPullToRefresh03
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh03, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnStateChange(std::move(onStateChange));
    });

    /**
     * @tc.steps: step1. PullToRefresh: -> false
     * @tc.expected: pullToRefresh_ == false
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),but pullToRefresh_ == false,
     *               onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx()
                               / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
}

/**
 * @tc.name: AttrPullToRefresh04
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh04, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnStateChange(std::move(onStateChange));
    });

    /**
     * @tc.steps: step1. PullToRefresh: -> true
     * @tc.expected: pullToRefresh_ == true
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta), pullToRefresh_ == true,
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx()
                               / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
}

/**
 * @tc.name: AttrPullToRefresh05
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh05, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTrigger = false;
    float offset;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onOffsetChange = [&offset](const float param) { offset = param; };
    Create(
        [onRefreshing, onOffsetChange](RefreshModelNG model) { model.SetOnOffsetChange(std::move(onOffsetChange)); });

    /**
     * @tc.steps: step1. PullToRefresh: -> false
     * @tc.expected: pullToRefresh_ == false
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: offset is 0.f
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(offset, 0.f);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: offset is 64.f
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(Dimension(offset, DimensionUnit::VP), TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta -TRIGGER_LOADING_DISTANCE
     * @tc.expected: offset is 48.f
     */
    pattern_->HandleDragUpdate(-(TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(Dimension(offset, DimensionUnit::VP), TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE);
}

/**
 * @tc.name: RefreshWithText001
 * @tc.desc: Test drag with a text
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, RefreshWithText001, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would trigger refresh
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create([](RefreshModelNG model) {model.SetLoadingText("promptText"); });
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: RefreshWithText002
 * @tc.desc: Test drag with a text
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, RefreshWithText002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would trigger refresh
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create([](RefreshModelNG model) {model.SetLoadingText(""); });
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}
} // namespace OHOS::Ace::NG
