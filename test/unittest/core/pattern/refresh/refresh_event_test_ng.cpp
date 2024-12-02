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
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/loading_progress/loading_progress_paint_property.h"

namespace OHOS::Ace::NG {
class RefreshEventTestNg : public RefreshTestNg {
public:
};

/**
 * @tc.name: VersionTenHandleDrag001
 * @tc.desc: Test whole refresh action in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenHandleDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTenHandleDrag002
 * @tc.desc: Test whole refresh action event in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenHandleDrag002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    bool isRefreshTriggered = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshingEvent = [&isRefreshTriggered]() { isRefreshTriggered = true; };
    auto onStateChangeEvent = [&refreshStatus](
                                  const int32_t value) { refreshStatus = static_cast<RefreshStatus>(value); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshingEvent));
    model.SetOnStateChange(std::move(onStateChangeEvent));
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTenHandleDrag003
 * @tc.desc: Test cancel refresh in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenHandleDrag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - 1.f) / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragCancel();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: VersionTenCustomHandleDrag001
 * @tc.desc: Test whole refresh action with customBuilder_ in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenCustomHandleDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(CreateCustomNode());
    model.SetIsCustomBuilderExist(true);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTenCustomHandleDrag002
 * @tc.desc: Test whole refresh action event with customBuilder_ in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenCustomHandleDrag002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    bool isRefreshTriggered = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshingEvent = [&isRefreshTriggered]() { isRefreshTriggered = true; };
    auto onStateChangeEvent = [&refreshStatus](
                                  const int32_t value) { refreshStatus = static_cast<RefreshStatus>(value); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshingEvent));
    model.SetOnStateChange(std::move(onStateChangeEvent));
    model.SetCustomBuilder(CreateCustomNode());
    model.SetIsCustomBuilderExist(true);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTenCustomHandleDrag003
 * @tc.desc: Test refresh other condition in low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTenCustomHandleDrag003, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. Set isRefreshing_
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->isRefreshing_);

    /**
     * @tc.steps: step2. When isRefreshing, HandleDrag again
     * @tc.expected: Still REFRESH
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: VersionElevenHandleDrag001
 * @tc.desc: Test whole refresh action in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenHandleDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionElevenHandleDrag002
 * @tc.desc: Test whole refresh action event in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenHandleDrag002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    bool isRefreshTriggered = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshingEvent = [&isRefreshTriggered]() { isRefreshTriggered = true; };
    auto onStateChangeEvent = [&refreshStatus](
                                  const int32_t value) { refreshStatus = static_cast<RefreshStatus>(value); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshingEvent));
    model.SetOnStateChange(std::move(onStateChangeEvent));
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionElevenHandleDrag003
 * @tc.desc: Test whole refresh with LoadingText in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenHandleDrag003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. When has LoadingText
     * @tc.expected: The refresh distance become TRIGGER_REFRESH_WITH_TEXT_DISTANCE
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    RefreshModelNG model = CreateRefresh();
    model.SetLoadingText("loadingText");
    CreateDone();
    EXPECT_EQ(pattern_->GetTriggerRefreshDisTance().ConvertToPx(), TRIGGER_REFRESH_WITH_TEXT_DISTANCE);

    /**
     * @tc.steps: step2. Test refresh action
     * @tc.expected: Would refresh when drag delta greater than TRIGGER_REFRESH_WITH_TEXT_DISTANCE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_WITH_TEXT_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: VersionElevenHandleDrag004
 * @tc.desc: Test refresh other condition in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenHandleDrag004, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    CreateRefresh();
    CreateDone();

    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step1. Tee delta is 0
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragUpdate(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: VersionElevenHandleDrag005
 * @tc.desc: Test refresh other condition in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenHandleDrag005, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. Set isRefreshing_
     */
    layoutProperty_->UpdateIsRefreshing(true);
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_TRUE(pattern_->isRefreshing_);

    /**
     * @tc.steps: step2. When isRefreshing, HandleDrag again
     * @tc.expected: Still REFRESH
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionElevenCustomHandleDrag001
 * @tc.desc: Test whole refresh action with customBuilder_ in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenCustomHandleDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    RefreshModelNG model = CreateRefresh();
    model.SetCustomBuilder(CreateCustomNode());
    model.SetIsCustomBuilderExist(true);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionElevenCustomHandleDrag002
 * @tc.desc: Test whole refresh action event with customBuilder_ in VERSION_ELEVEN
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionElevenCustomHandleDrag002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_ELEVEN));
    bool isRefreshTriggered = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    auto onRefreshingEvent = [&isRefreshTriggered]() { isRefreshTriggered = true; };
    auto onStateChangeEvent = [&refreshStatus](
                                  const int32_t value) { refreshStatus = static_cast<RefreshStatus>(value); };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshingEvent));
    model.SetOnStateChange(std::move(onStateChangeEvent));
    model.SetCustomBuilder(CreateCustomNode());
    model.SetIsCustomBuilderExist(true);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTwelveHandleDrag001
 * @tc.desc: Test whole refresh action in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTwelveHandleDrag002
 * @tc.desc: Test whole refresh action event in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    bool isRefreshTriggered = false;
    RefreshStatus refreshStatus = RefreshStatus::INACTIVE;
    float offset = 0.f;
    auto onRefreshingEvent = [&isRefreshTriggered]() { isRefreshTriggered = true; };
    auto onStateChangeEvent = [&refreshStatus](
                                  const int32_t value) { refreshStatus = static_cast<RefreshStatus>(value); };
    auto onOffsetChangeEvent = [&offset](const float value) { offset = value; };
    RefreshModelNG model = CreateRefresh();
    model.SetOnRefreshing(std::move(onRefreshingEvent));
    model.SetOnStateChange(std::move(onStateChangeEvent));
    model.SetOnOffsetChange(std::move(onOffsetChangeEvent));
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);
    EXPECT_EQ(offset, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent/onOffsetChangeEvent
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    EXPECT_EQ(offset, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent/onOffsetChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent/onOffsetChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent/onOffsetChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE);
}

/**
 * @tc.name: VersionTwelveHandleDrag003
 * @tc.desc: Test whole refresh action with RefreshOffset in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag003, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    const float refreshOffset = 100.f;
    RefreshModelNG model = CreateRefresh();
    model.SetRefreshOffset(Dimension(refreshOffset));
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal refreshOffset
     * @tc.expected: OVER_DRAG, scrollOffset_ is refreshOffset
     */
    pattern_->HandleDragUpdate((refreshOffset - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, refreshOffset);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, refreshOffset);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTwelveHandleDrag004
 * @tc.desc: Test whole refresh action with pullToRefresh in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag004, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    model.SetPullToRefresh(false); // will not refresh
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: INACTIVE
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);
}

/**
 * @tc.name: VersionTwelveHandleDrag005
 * @tc.desc: Test whole refresh action with PullDownRatio in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag005, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    const float pullDownRatio = 0.5f;
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(pullDownRatio);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE / pullDownRatio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pullDownRatio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: VersionTwelveHandleDragUpdate001
 * @tc.desc: Refresh should processing all delta each slip before reaching the original position
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDragUpdate001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    const float pullDownRatio = 0.637474f;
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(pullDownRatio);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragUpdate in the forward direction
     * @tc.expected: result.remain is 0.f
     */
    pattern_->scrollOffset_ = 278.047150f; // random value to make sure refresh's not in the original position
    ScrollResult result = pattern_->HandleDragUpdate(2.0f);
    EXPECT_EQ(result.remain, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate in the opposite direction
     * @tc.expected: result.remain is 0.f
     */
    result = pattern_->HandleDragUpdate(-10.562789f);
    EXPECT_EQ(result.remain, 0.f);
}

/**
 * @tc.name: VersionTwelveHandleDragEnd001
 * @tc.desc: LoadingProgress should be RECYCLE status after dragEnd in the position of great or equal with refreshOffset
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDragEnd001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    const float pullDownRatio = 1.0f;
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(pullDownRatio);
    CreateDone();
    auto progressPaintProperty = pattern_->progressChild_->GetPaintProperty<LoadingProgressPaintProperty>();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: LoadingProgress' RefreshAnimationState is FOLLOW_HAND
     */
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(progressPaintProperty->GetRefreshAnimationState(), RefreshAnimationState::FOLLOW_HAND);

    /**
     * @tc.steps: step3. HandleDragEnd, and start animation
     * @tc.expected: LoadingProgress' RefreshAnimationState is FOLLOW_TO_RECYCLE
     */
    MockAnimationManager::GetInstance().SetTicks(1);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(progressPaintProperty->GetRefreshAnimationState(), RefreshAnimationState::FOLLOW_TO_RECYCLE);

    /**
     * @tc.steps: step4. End refreshing before animation finished
     * @tc.expected: LoadingProgress' RefreshAnimationState is RECYCLE
     */
    pattern_->isRefreshing_ = false;
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(progressPaintProperty->GetRefreshAnimationState(), RefreshAnimationState::RECYCLE);
}

/**
 * @tc.name: HandleScrollVelocityTest001
 * @tc.desc: Test HandleScrollVelocity method
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, HandleScrollVelocityTest001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(1);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta is equal to TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_LOADING_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta is equal to negative TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is 0.f
     */
    pattern_->HandleDragUpdate(- TRIGGER_LOADING_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step4. HandleScrollVelocity
     * @tc.expected: INACTIVE
     */
    pattern_->HandleScrollVelocity(-100.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
}

/**
 * @tc.name: HandleScrollVelocityTest002
 * @tc.desc: Test HandleScrollVelocity method
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, HandleScrollVelocityTest002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model = CreateRefresh();
    model.SetPullDownRatio(1);
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta is equal to TRIGGER_REFRESH_DISTANCE
     * @tc.expected: DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step3. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);
    EXPECT_TRUE(pattern_->isRefreshing_);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta is equal to negative TRIGGER_REFRESH_DISTANCE
     * @tc.expected: REFRESH, scrollOffset_ is 0.f
     */
    pattern_->HandleDragUpdate(- TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step5. HandleScrollVelocity
     * @tc.expected: INACTIVE
     */
    pattern_->HandleScrollVelocity(-100.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_FALSE(pattern_->isRefreshing_);
}
} // namespace OHOS::Ace::NG
