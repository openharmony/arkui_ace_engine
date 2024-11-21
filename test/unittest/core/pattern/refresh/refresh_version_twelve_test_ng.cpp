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
#include "test/mock/core/pipeline/mock_pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr Dimension TEN_OFFSET = 10.0_vp;
constexpr Dimension ZERO_OFFSET = 0.0_vp;
constexpr Dimension MINUS_OFFSET = -1.0_vp;
constexpr Dimension DRAG_OFFSET = 640.0_vp;
constexpr Dimension OVERDRAG_OFFSET = 32.0_vp;
constexpr Dimension DRAG_NE_OFFSET = -640.0_vp;
constexpr Dimension ONE_OFFSET = 1.0_vp;
} // namespace

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
    CreateRefresh();
    CreateDone();

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
    CreateRefresh();
    CreateDone();

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
    CreateRefresh();
    CreateDone();

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
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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
    pattern_->HandleDragUpdate((OVERDRAG_OFFSET).ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(CreateCustomNode());
    CreateDone();

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
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(CreateCustomNode());
    CreateDone();

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
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
}

/**
 * @tc.name: AttrPullToRefresh04
 * @tc.desc: Test attr RefreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrPullToRefresh04, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    float offset;
    auto onOffsetChange = [&offset](const float param) { offset = param; };
    RefreshModelNG model = CreateRefresh();
    model.SetOnOffsetChange(std::move(onOffsetChange));
    CreateDone();

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
 * @tc.name: AttrRefreshOffset06
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset06, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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
    pattern_->HandleDragUpdate((OVERDRAG_OFFSET).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset07
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset07, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -640vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(DRAG_NE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset08
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset08, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset09
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset09, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 64vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(TRIGGER_REFRESH_DISTANCE);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */

    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset10
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset10, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset11
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset11, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 0vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(ZERO_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset12
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset12, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -1vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(MINUS_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset13
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset13, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 1vp
     * @tc.expected: refreshOffset_: -> 1vp
     */
    layoutProperty_->UpdateRefreshOffset(ONE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, ONE_OFFSET);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset14
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset14, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 10vp
     * @tc.expected: refreshOffset_: -> 10vp
     */
    layoutProperty_->UpdateRefreshOffset(TEN_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TEN_OFFSET);
    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, false);
}

/**
 * @tc.name: AttrRefreshOffset15
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset15, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -640vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(DRAG_NE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset16
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset16, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset17
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset17, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 64vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(TRIGGER_REFRESH_DISTANCE);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset18
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset18, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset19
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset19, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 0vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(ZERO_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset20
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset20, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -1vp
     * @tc.expected: refreshOffset_: -> -1vp
     */
    layoutProperty_->UpdateRefreshOffset(MINUS_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset21
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset21, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 1vp
     * @tc.expected: refreshOffset_: -> 1vp
     */
    layoutProperty_->UpdateRefreshOffset(ONE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, ONE_OFFSET);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset22
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset22, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 10vp
     * @tc.expected: refreshOffset_: -> 10vp
     */
    layoutProperty_->UpdateRefreshOffset(TEN_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TEN_OFFSET);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, true);
}

/**
 * @tc.name: AttrRefreshOffset23
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset23, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -640vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(DRAG_NE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset24
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset24, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset25
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset25, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 64vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(TRIGGER_REFRESH_DISTANCE);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset26
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset26, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

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

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset27
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset27, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 0vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(ZERO_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset28
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset28, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> -1vp
     * @tc.expected: refreshOffset_: -> 64vp
     */
    layoutProperty_->UpdateRefreshOffset(MINUS_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
}

/**
 * @tc.name: AttrRefreshOffset29
 * @tc.desc: Test attr RefreshOffset UpdatePullToRefresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionTwelveTestNg, AttrRefreshOffset29, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnStateChange(std::move(onStateChange));
    CreateDone();

    /**
     * @tc.steps: step1. refreshOffset_: -> 1vp
     * @tc.expected: refreshOffset_: -> 1vp
     */
    layoutProperty_->UpdateRefreshOffset(ONE_OFFSET);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);

    EXPECT_EQ(pattern_->refreshOffset_, ONE_OFFSET);

    /**
     * @tc.steps: step2. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. UpdatePullToRefresh, the delta greater than OVERDRAG_OFFSET
     * @tc.expected: EXPECT is OFFSET_VALUE
     *               FlushLayoutTask
     */
    layoutProperty_->UpdatePullToRefresh(0);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->pullToRefresh_, 0);
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
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("promptText");
    CreateDone();
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
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("");
    CreateDone();
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}
} // namespace OHOS::Ace::NG
