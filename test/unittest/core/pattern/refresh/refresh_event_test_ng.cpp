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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SWIPER_HEIGHT = 400.f;
constexpr float SCROLL_HEIGHT = 400.f;
constexpr int32_t TEXT_NUMBER = 5;
} // namespace

class RefreshEventTestNg : public RefreshTestNg {
public:
    void CreateScroll()
    {
        ScrollModelNG scrollModel;
        scrollModel.Create();
        ViewAbstract::SetWidth(CalcLength(WIDTH));
        ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
        scrollNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        scrollPattern_ = scrollNode_->GetPattern<ScrollPattern>();
    }

    void CreateColumn()
    {
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
    }

    void CreateNestedSwiper()
    {
        SwiperModelNG model;
        model.Create();
        model.SetDirection(Axis::VERTICAL);
        model.SetLoop(false);
        ViewAbstract::SetWidth(CalcLength(WIDTH));
        ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
        swiperNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
        for (int32_t index = 0; index < TEXT_NUMBER; index++) {
            CreateText();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }

    RefPtr<FrameNode> swiperNode_;
    RefPtr<SwiperPattern> swiperPattern_;

    RefPtr<FrameNode> scrollNode_;
    RefPtr<ScrollPattern> scrollPattern_;
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RATIO);
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
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f) / RATIO);
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
    CreateScroll();
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RATIO);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / RATIO);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RATIO);
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / RATIO);
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    EXPECT_EQ(pattern_->GetTriggerRefreshDisTance(), TRIGGER_REFRESH_WITH_TEXT_DISTANCE);

    /**
     * @tc.steps: step2. Test refresh action
     * @tc.expected: Would refresh when drag delta greater than TRIGGER_REFRESH_WITH_TEXT_DISTANCE
     */
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_WITH_TEXT_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() /
                               pattern_->CalculatePullDownRatio());
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);
    EXPECT_EQ(offset, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Trigger onStateChangeEvent/onOffsetChangeEvent
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(refreshStatus, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: Trigger onRefreshingEvent/onStateChangeEvent/onOffsetChangeEvent
     */
    EXPECT_FALSE(isRefreshTriggered); // no trigger refresh before
    pattern_->HandleDragEnd(0.f);
    EXPECT_TRUE(isRefreshTriggered);
    EXPECT_EQ(refreshStatus, RefreshStatus::REFRESH);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: Trigger onStateChangeEvent/onOffsetChangeEvent
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(refreshStatus, RefreshStatus::DONE);
    EXPECT_EQ(offset, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
}

/**
 * @tc.name: VersionTwelveHandleDrag003
 * @tc.desc: Test whole refresh action with RefreshOffset in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, VersionTwelveHandleDrag003, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    const Dimension refreshOffset = Dimension(100.f);
    RefreshModelNG model = CreateRefresh();
    model.SetRefreshOffset(refreshOffset);
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal refreshOffset
     * @tc.expected: OVER_DRAG, scrollOffset_ is refreshOffset
     */
    pattern_->HandleDragUpdate(
        (refreshOffset - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, refreshOffset.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, refreshOffset.ConvertToPx());

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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate(
        (TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: INACTIVE
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());
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
    pattern_->HandleDragUpdate(TRIGGER_LOADING_DISTANCE.ConvertToPx() / pullDownRatio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal TRIGGER_REFRESH_DISTANCE
     * @tc.expected: OVER_DRAG, scrollOffset_ is TRIGGER_REFRESH_DISTANCE
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / pullDownRatio);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE.ConvertToPx());

    /**
     * @tc.steps: step5. The frontEnd set isRefreshing to false
     * @tc.expected: DONE
     */
    layoutProperty_->UpdateIsRefreshing(false);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
}

/**
 * @tc.name: RefreshNestedSwiper001
 * @tc.desc: Test Refresh nested Swiper with selfOnly mode in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, RefreshNestedSwiper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh();
    CreateNestedSwiper();
    CreateDone();

    /**
     * @tc.steps: step2. Test OnScrollStartRecursive.
     * @tc.expected: isSourceFromAnimation_ of refresh  is false,
     *               the nestedOption of swiper is PARENT_FIRST and SELF_FIRST.
     */
    swiperPattern_->OnScrollStartRecursive(swiperPattern_, 0.f, 0.f);
    EXPECT_FALSE(pattern_->isSourceFromAnimation_);
    auto swiperNestedOption = swiperPattern_->GetNestedScroll();
    EXPECT_EQ(swiperNestedOption.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(swiperNestedOption.backward, NestedScrollMode::SELF_FIRST);

    /**
     * @tc.steps: step3. Test HandleScrollVelocity.
     * @tc.expected: The result of swiper is TRUE, the result of refresh is FALSE.
     */
    EXPECT_TRUE(swiperPattern_->HandleScrollVelocity(5.f));
    EXPECT_TRUE(pattern_->HandleScrollVelocity(5.f));
    EXPECT_FALSE(pattern_->HandleScrollVelocity(-5.f));

    /**
     * @tc.steps: step4. Test HandleScroll, the offset is 20.f.
     * @tc.expected: The scrollOffset_ of refresh is the sum of lastScrollOffset and 20.f * pullDownRatio.
     */
    auto lastScrollOffset = pattern_->scrollOffset_;
    auto pullDownRatio = pattern_->CalculatePullDownRatio();
    swiperPattern_->HandleScroll(static_cast<float>(20.f), SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, lastScrollOffset + 20.f * pullDownRatio);

    /**
     * @tc.steps: step5. Test HandleScrollVelocity, offset is 20.f and the scrollOffset_ of refresh is positive.
     * @tc.expected: The result of swiper is TRUE, the result of refresh is TRUE.
     */
    EXPECT_TRUE(swiperPattern_->HandleScrollVelocity(0.f));
    EXPECT_TRUE(pattern_->HandleScrollVelocity(0.f));

    /**
     * @tc.steps: step6. Test HandleScroll, the offset is 40.f.
     * @tc.expected: The scrollOffset_ of refresh is 0.f,
     *               and the currentDelta_ of swiper is lastDelta - (-40.f + lastScrollOffset / pullDownRatio).
     */
    lastScrollOffset = pattern_->scrollOffset_;
    auto lastDelta = swiperPattern_->currentDelta_;
    pullDownRatio = pattern_->CalculatePullDownRatio();
    swiperPattern_->HandleScroll(static_cast<float>(-40.f), SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(swiperPattern_->currentDelta_, lastDelta);
    swiperPattern_->HandleScroll(static_cast<float>(-20.f), SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
    EXPECT_EQ(swiperPattern_->currentDelta_, 20.f);
}

/**
 * @tc.name: RefreshNestedSwiper002
 * @tc.desc: Test Refresh nested Swiper in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, RefreshNestedSwiper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper, and set SELF_FIRST to the nested mode of swiper.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateScroll();
    {
        CreateColumn();
        {
            CreateText();
            CreateRefresh();
            {
                CreateNestedSwiper();
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();
    swiperPattern_->SetNestedScroll(NestedScrollOptions({
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    }));

    /**
     * @tc.steps: step2. Test OnScrollStartRecursive.
     * @tc.expected: isSourceFromAnimation_ of refresh  is false,
     *               the nestedOption of swiper is PARENT_FIRST and SELF_FIRST,
     *               the nestedOption of refresh is SELF_FIRST.
     */
    swiperPattern_->OnScrollStartRecursive(swiperPattern_, 0.f, 0.f);
    EXPECT_FALSE(pattern_->isSourceFromAnimation_);
    auto swiperNestedOption = swiperPattern_->GetNestedScroll();
    EXPECT_EQ(swiperNestedOption.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(swiperNestedOption.backward, NestedScrollMode::SELF_FIRST);
    auto refreshNestedOption = pattern_->GetNestedScroll();
    EXPECT_EQ(refreshNestedOption.forward, NestedScrollMode::SELF_FIRST);
    EXPECT_EQ(refreshNestedOption.backward, NestedScrollMode::SELF_FIRST);

    /**
     * @tc.steps: step3. Test HandleScrollVelocity.
     * @tc.expected: The result of swiper is TRUE, the result of refresh is FALSE.
     */
    EXPECT_TRUE(swiperPattern_->HandleScrollVelocity(0.f));
    EXPECT_FALSE(pattern_->HandleScrollVelocity(0.f));

    /**
     * @tc.steps: step4. Test HandleScroll, the offset is -20.f.
     * @tc.expected: The currentOffset_ of scroll is -20.f.
     */
    swiperPattern_->HandleScroll(static_cast<float>(-20.f), SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(scrollPattern_->currentOffset_, -20.f);

    /**
     * @tc.steps: step5. Test HandleScroll, the offset is 40.f.
     * @tc.expected: The scrollOffset_ of refresh is the sum of lastScrollOffset and 20.f * pullDownRatio.
     */
    auto lastScrollOffset = pattern_->scrollOffset_;
    auto pullDownRatio = pattern_->CalculatePullDownRatio();
    swiperPattern_->HandleScroll(static_cast<float>(40.f), SCROLL_FROM_UPDATE, NestedState::GESTURE, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, lastScrollOffset + 20.f * pullDownRatio);
}

/**
 * @tc.name: RefreshPatternHandleScroll001
 * @tc.desc: test HandleScroll  when NestedScrollMode is SELF_ONLY in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, RefreshPatternHandleScroll001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh();
    CreateDone();

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    pattern_->scrollOffset_ = 5.f;
    pattern_->parent_ = mockScroll;
    auto res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);

    auto lastScrollOffset = pattern_->scrollOffset_;
    auto pullDownRatio = pattern_->CalculatePullDownRatio();
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, lastScrollOffset + 5.f * pullDownRatio);

    pattern_->scrollOffset_ = 0.f;
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 5.f);
}

/**
 * @tc.name: RefreshPatternHandleScroll002
 * @tc.desc: test HandleScroll  when NestedScrollMode is PARENT_FIRST in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, RefreshPatternHandleScroll002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh();
    CreateDone();

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    pattern_->scrollOffset_ = 5.f;
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::PARENT_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    EXPECT_CALL(*mockScroll, HandleScroll(-5.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = -5.f, .reachEdge = true }));
    auto res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);

    auto lastScrollOffset = pattern_->scrollOffset_;
    auto pullDownRatio = pattern_->CalculatePullDownRatio();
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, lastScrollOffset + 5.f * pullDownRatio);

    pattern_->scrollOffset_ = 0.f;
    EXPECT_CALL(*mockScroll, HandleScroll(-5.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 0.f, .reachEdge = true }));
    res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);
}

/**
 * @tc.name: RefreshPatternHandleScroll003
 * @tc.desc: test HandleScroll  when NestedScrollMode is SELF_FIRST in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshEventTestNg, RefreshPatternHandleScroll003, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    RefreshModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(REFRESH_HEIGHT));
    GetRefresh();
    ViewStackProcessor::GetInstance()->Pop();

    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    pattern_->scrollOffset_ = 5.f;
    pattern_->parent_ = mockScroll;
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    EXPECT_CALL(*mockScroll, HandleScroll(0.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 0.f, .reachEdge = true }));
    auto res = pattern_->HandleScroll(-5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);

    auto lastScrollOffset = pattern_->scrollOffset_;
    auto pullDownRatio = pattern_->CalculatePullDownRatio();
    EXPECT_CALL(*mockScroll, HandleScroll(5.f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 0.f, .reachEdge = true }));
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    lastScrollOffset = pattern_->scrollOffset_;
    pullDownRatio = pattern_->CalculatePullDownRatio();
    EXPECT_CALL(*mockScroll, HandleScroll(5.f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f))
        .Times(1)
        .WillOnce(Return(ScrollResult { .remain = 5.f, .reachEdge = true }));
    res = pattern_->HandleScroll(5.0f, SCROLL_FROM_UPDATE, NestedState::CHILD_OVER_SCROLL, 0.f);
    EXPECT_EQ(res.remain, 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, lastScrollOffset + 5.f * pullDownRatio);
}
} // namespace OHOS::Ace::NG
