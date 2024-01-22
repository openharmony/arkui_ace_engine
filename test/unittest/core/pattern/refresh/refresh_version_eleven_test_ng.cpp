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

class RefreshVersionElevenTestNg : public RefreshTestNg {
public:
};

/**
 * @tc.name: Drag001
 * @tc.desc: Test drag low version, test whole refresh movement
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, Drag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
        model.SetOnStateChange(std::move(onStateChange));
    });

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than TRIGGER_LOADING_DISTANCE
     * @tc.expected: scrollOffset_ is 1.f, onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate(1.f / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta is zero
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragUpdate(0.f);
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step5. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx()
                               / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step6. HandleDragEnd
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    EXPECT_FALSE(isRefreshTrigger); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);

    /**
     * @tc.steps: step7. The front end set isRefreshing to false
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: Drag002
 * @tc.desc: Test drag low version, test cancel refresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, Drag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: CustomDrag001
 * @tc.desc: Test drag with customBuilder_ low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, CustomDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    bool isRefreshTrigger = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshing = [&isRefreshTrigger]() { isRefreshTrigger = true; };
    auto onStateChange = [&refreshStatus](const int32_t param) { refreshStatus = static_cast<RefreshStatus>(param); };
    Create([onRefreshing, onStateChange](RefreshModelNG model) {
        model.SetOnRefreshing(std::move(onRefreshing));
        model.SetOnStateChange(std::move(onStateChange));
        model.SetCustomBuilder(CreateCustomNode());
    });

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: scrollOffset_ default is 0.f, refreshStatus_ default is 0.f INACTIVE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than TRIGGER_LOADING_DISTANCE
     * @tc.expected: scrollOffset_ is 1.f, onStateChange event triggered and refreshStatus is DRAG
     */
    pattern_->HandleDragUpdate(1.f / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate(((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx())
                               / pattern_->CalculateFriction());
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step5. HandleDragEnd
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    EXPECT_FALSE(isRefreshTrigger); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_TRUE(isRefreshTrigger);

    /**
     * @tc.steps: step6. The front end set isRefreshing to false
     * @tc.expected: onStateChange event triggered and refreshStatus is REFRESH, onRefreshing event triggered
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: CustomDrag002
 * @tc.desc: Test drag with customBuilder_ low version, test cancel refresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, CustomDrag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create([](RefreshModelNG model) {
        model.SetCustomBuilder(CreateCustomNode());
    });
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, AttrRefreshing001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create([](RefreshModelNG model) { model.SetCustomBuilder(CreateCustomNode()); });

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: AttrRefreshing002
 * @tc.desc: Test attr refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshVersionElevenTestNg, AttrRefreshing002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    Create();

    /**
     * @tc.steps: step1. IsRefreshing: true -> false
     * @tc.expected: refreshStatus_ == INACTIVE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. IsRefreshing: false -> true
     * @tc.expected: refreshStatus_ == REFRESH
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}
} // namespace OHOS::Ace::NG
