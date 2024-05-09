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

#include "refresh_test_ng.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"

namespace OHOS::Ace::NG {

constexpr float WIDTH = 480.f;
constexpr float SWIPER_HEIGHT = 400.f;
constexpr float SCROLL_HEIGHT = 400.f;
constexpr float TEXT_HEIGHT = 200.f;
constexpr int32_t TEXT_NUMBER = 5;

void RefreshTestNg::SetUpTestSuite()
{
    TestNG::SetUpTestSuite();
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    PipelineContext::GetCurrentContext()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<RefreshTheme>()));
}

void RefreshTestNg::TearDownTestSuite()
{
    TestNG::TearDownTestSuite();
}

void RefreshTestNg::SetUp() {}

void RefreshTestNg::TearDown()
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TEN));
    frameNode_ = nullptr;
    pattern_ = nullptr;
    eventHub_ = nullptr;
    layoutProperty_ = nullptr;
    accessibilityProperty_ = nullptr;
    swiper_ = nullptr;
    swiperPattern_ = nullptr;
    scroll_ = nullptr;
    scrollPattern_ = nullptr;
}

void RefreshTestNg::GetInstance()
{
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    frameNode_ = AceType::DynamicCast<FrameNode>(element);
    pattern_ = frameNode_->GetPattern<RefreshPattern>();
    eventHub_ = frameNode_->GetEventHub<RefreshEventHub>();
    layoutProperty_ = frameNode_->GetLayoutProperty<RefreshLayoutProperty>();
    accessibilityProperty_ = frameNode_->GetAccessibilityProperty<RefreshAccessibilityProperty>();
}

void RefreshTestNg::Create(const std::function<void(RefreshModelNG)>& callback)
{
    RefreshModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(REFRESH_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    ViewStackProcessor::GetInstance()->Finish();
    FlushLayoutTask(frameNode_);
}

void RefreshTestNg::CreateRefresh(const std::function<void(RefreshModelNG)>& callback)
{
    RefreshModelNG model;
    model.Create();
    ViewAbstract::SetHeight(CalcLength(REFRESH_HEIGHT));
    if (callback) {
        callback(model);
    }
    GetInstance();
    ViewStackProcessor::GetInstance()->Pop();
}

void RefreshTestNg::CreateScroll()
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    TextModelNG model;
    model.Create("text");
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(TEXT_HEIGHT));
    ViewStackProcessor::GetInstance()->Pop();
    CreateRefresh([this](RefreshModelNG model) { CreateNestedSwiper(); });
    ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    scroll_ = AceType::DynamicCast<FrameNode>(element);
    scrollPattern_ = scroll_->GetPattern<ScrollPattern>();
    ViewStackProcessor::GetInstance()->Finish();
    FlushLayoutTask(scroll_);
}

void RefreshTestNg::CreateNestedSwiper()
{
    SwiperModelNG model;
    model.Create();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(false);
    ViewAbstract::SetWidth(CalcLength(WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    for (int32_t index = 0; index < TEXT_NUMBER; index++) {
        TextModelNG model;
        model.Create("text");
        ViewStackProcessor::GetInstance()->Pop();
    }
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->GetMainElementNode();
    swiper_ = AceType::DynamicCast<FrameNode>(element);
    swiperPattern_ = swiper_->GetPattern<SwiperPattern>();
    ViewStackProcessor::GetInstance()->Pop();
    FlushLayoutTask(swiper_);
    auto children = swiper_->GetChildren();
}

RefPtr<FrameNode> RefreshTestNg::CreateCustomNode()
{
    auto frameNode = AceType::MakeRefPtr<FrameNode>("test", 0, AceType::MakeRefPtr<Pattern>());
    auto layoutProperty = frameNode->GetLayoutProperty();
    layoutProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(CUSTOM_NODE_WIDTH), CalcLength(CUSTOM_NODE_HEIGHT)));
    return frameNode;
}

/**
 * @tc.name: RefreshNestedSwiper001
 * @tc.desc: Test Refresh nested Swiper with selfOnly mode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshNestedSwiper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    Create([this](RefreshModelNG model) { CreateNestedSwiper(); });
    ASSERT_NE(swiperPattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);

    /**
     * @tc.steps: step2. Test OnScrollStartRecursive.
     * @tc.expected: isSourceFromAnimation_ of refresh  is false, the nestedOption of swiper is PARENT_FIRST and SELF_FIRST.
     */
    swiperPattern_->OnScrollStartRecursive(0.f, 0.f);
    EXPECT_FALSE(pattern_->isSourceFromAnimation_);
    auto swiperNestedOption = swiperPattern_->GetNestedScroll();
    EXPECT_EQ(swiperNestedOption.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(swiperNestedOption.backward, NestedScrollMode::SELF_FIRST);

    /**
     * @tc.steps: step3. Test HandleScrollVelocity.
     * @tc.expected: The result of swiper is TRUE, the result of refresh is FALSE.
     */
    auto result = swiperPattern_->HandleScrollVelocity(5.f);
    EXPECT_TRUE(result);
    result = pattern_->HandleScrollVelocity(5.f);
    EXPECT_FALSE(result);

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
    result = swiperPattern_->HandleScrollVelocity(0.f);
    EXPECT_TRUE(result);
    result = pattern_->HandleScrollVelocity(0.f);
    EXPECT_TRUE(result);

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
 * @tc.desc: Test Refresh nested Swiper
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshNestedSwiper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper, and set SELF_FIRST to the nested mode of swiper.
     */
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateScroll();
    ASSERT_NE(swiperPattern_, nullptr);
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(scrollPattern_, nullptr);
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
    swiperPattern_->OnScrollStartRecursive(0.f, 0.f);
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
    auto result = swiperPattern_->HandleScrollVelocity(0.f);
    EXPECT_TRUE(result);
    result = pattern_->HandleScrollVelocity(0.f);
    EXPECT_FALSE(result);

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
 * @tc.desc: test HandleScroll  when NestedScrollMode is SELF_ONLY.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshPatternHandleScroll001, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh([this](RefreshModelNG model) {});
    ASSERT_NE(pattern_, nullptr);
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    pattern_->scrollOffset_ = 5.f;
    pattern_->parent_ = mockScroll;
    EXPECT_CALL(*mockScroll, HandleScroll(-5.f, SCROLL_FROM_UPDATE, NestedState::CHILD_SCROLL, 0.f))
        .Times(0)
        .WillOnce(Return(ScrollResult { .remain = 5.f, .reachEdge = true }));
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
 * @tc.desc: test HandleScroll  when NestedScrollMode is PARENT_FIRST.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshPatternHandleScroll002, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh([this](RefreshModelNG model) {});
    ASSERT_NE(pattern_, nullptr);
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
 * @tc.desc: test HandleScroll  when NestedScrollMode is SELF_FIRST.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshPatternHandleScroll003, TestSize.Level1)
{
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateRefresh([this](RefreshModelNG model) {});
    ASSERT_NE(pattern_, nullptr);
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

/**
 * @tc.name: PullDownRatio001
 * @tc.desc: Test PullDownRatio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, PullDownRatio001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Refresh
     * @tc.expected: layoutProperty_ is not nullptr
     */
    Create([](RefreshModelNG model) {});
    ASSERT_NE(layoutProperty_, nullptr);

    /**
     * @tc.steps: step2. Set PullDownRatio to 1.0f
     * @tc.expected: CalculatePullDownRatio return to 1.0f
     */
    layoutProperty_->UpdatePullDownRatio(1.0f);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 1.0f);

    /**
     * @tc.steps: step3. Set PullDownRatio to 0.5f
     * @tc.expected: CalculatePullDownRatio return to 0.5f
     */
    layoutProperty_->UpdatePullDownRatio(0.5f);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 0.5f);

    /**
     * @tc.steps: step4. Set PullDownRatio to 0.f
     * @tc.expected: CalculatePullDownRatio return to 0.f
     */
    layoutProperty_->UpdatePullDownRatio(0.f);
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 0.f);

    /**
     * @tc.steps: step5. Reset PullDownRatio
     * @tc.expected: CalculatePullDownRatio return to 1.f
     */
    layoutProperty_->ResetPullDownRatio();
    EXPECT_EQ(pattern_->CalculatePullDownRatio(), 1.0f);
}

/**
 * @tc.name: Drag001
 * @tc.desc: Test drag low version, test whole refresh movement
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag001, TestSize.Level1)
{
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
    pattern_->HandleDragUpdate(1.f / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx() / RADIO);
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
 * @tc.name: Drag002
 * @tc.desc: Test drag low version, test cancel refresh
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: Drag003
 * @tc.desc: Test drag low version, test HandleDragCancel func
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, Drag003, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() - 1.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);
    pattern_->HandleDragCancel();
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
}

/**
 * @tc.name: CustomDrag001
 * @tc.desc: Test drag with customBuilder_ low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, CustomDrag001, TestSize.Level1)
{
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
    pattern_->HandleDragUpdate(1.f / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, 1.f);
    EXPECT_EQ(refreshStatus, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 16.f(Plus previous delta), onStateChange event is not triggered
     */
    refreshStatus = RefreshStatus::INACTIVE; // for verify onStateChange event
    pattern_->HandleDragUpdate((TRIGGER_LOADING_DISTANCE.ConvertToPx() - 1.f) / RADIO);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_LOADING_DISTANCE.ConvertToPx());
    EXPECT_EQ(refreshStatus, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step4. HandleDragUpdate, the delta greater than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: scrollOffset_ is 64.f(Plus previous delta),
     *               onStateChange event triggered and refreshStatus is OVER_DRAG
     */
    pattern_->HandleDragUpdate(((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE).ConvertToPx()) / RADIO);
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
HWTEST_F(RefreshTestNg, CustomDrag002, TestSize.Level1)
{
    /**
     * @tc.cases: HandleDrag delta less than TRIGGER_REFRESH_DISTANCE
     * @tc.expected: Would not trigger refresh
     */
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
 * @tc.name: AddCustomBuilderNode001
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode001, TestSize.Level1)
{
    auto builder = CreateCustomNode();
    Create([&builder](RefreshModelNG model) { model.SetCustomBuilder(builder); });

    /**
     * @tc.steps: step1. Add same custom node
     * @tc.expected: would not replace node
     */
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);

    /**
     * @tc.steps: step2. Add diff custom node
     * @tc.expected: would replace node
     */
    builder = AceType::MakeRefPtr<FrameNode>("test", -1, AceType::MakeRefPtr<Pattern>());
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);
}

/**
 * @tc.name: AddCustomBuilderNode002
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh
     * @tc.expected: init progress node.
     */
    Create([](RefreshModelNG model) { model.SetProgressColor(Color::BLUE); });
    EXPECT_EQ(layoutProperty_->GetProgressColor(), Color::BLUE);
    auto builder = CreateCustomNode();
    pattern_->AddCustomBuilderNode(builder);
    EXPECT_EQ(GetChildFrameNode(frameNode_, 0), builder);
    EXPECT_NE(pattern_->progressChild_, nullptr);

    /**
     * @tc.steps: step2. init child node
     * @tc.expected: remove progress child.
     */
    int32_t childrenSize = frameNode_->GetChildren().size();
    pattern_->InitChildNode();
    EXPECT_EQ(pattern_->progressChild_, nullptr);
    EXPECT_EQ(frameNode_->GetChildren().size(), childrenSize - 1);

    /**
     * @tc.steps: step3. set null custom node
     * @tc.expected: isCustomBuilderExist_ is false, customBuilder_ is nullptr.
     */
    pattern_->AddCustomBuilderNode(nullptr);
    EXPECT_FALSE(pattern_->isCustomBuilderExist_);
    EXPECT_EQ(pattern_->customBuilder_, nullptr);
}

/**
 * @tc.name: AddCustomBuilderNode003
 * @tc.desc: Test AddCustomBuilderNode
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AddCustomBuilderNode003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh with child node
     */
    auto builder = CreateCustomNode();
    RefreshModelNG model;
    model.Create();
    model.SetCustomBuilder(builder);
    {
        TextModelNG model;
        model.Create("text");
        ViewStackProcessor::GetInstance()->Pop();
    }
    GetInstance();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(frameNode_->TotalChildCount(), 2);

    /**
     * @tc.steps: step2. set isCustomBuilderExist_ = false
     * @tc.expected: Check frameNode child node size.
     */
    pattern_->AddCustomBuilderNode(nullptr);
    EXPECT_FALSE(pattern_->isCustomBuilderExist_);
    pattern_->InitChildNode();
    EXPECT_EQ(frameNode_->TotalChildCount(), 3);
}

/**
 * @tc.name: AttrRefreshing001
 * @tc.desc: Test attr refreshing with custom node low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing001, TestSize.Level1)
{
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
 * @tc.desc: Test attr refreshing low version
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AttrRefreshing002, TestSize.Level1)
{
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

/**
 * @tc.name: AccessibilityProperty001
 * @tc.desc: Test IsScrollable and SetSpecificSupportAction.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, AccessibilityProperty001, TestSize.Level1)
{
    Create();

    /**
     * @tc.steps: step1. When IsScrollable() == true
     * @tc.expected: Trigger AddSupportAction()
     */
    EXPECT_TRUE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    uint64_t exptectActions = 0;
    exptectActions |= 1UL << static_cast<uint32_t>(AceAction::ACTION_SCROLL_FORWARD);
    EXPECT_EQ(GetActions(accessibilityProperty_), exptectActions);

    /**
     * @tc.steps: step2. When IsScrollable() == false
     * @tc.expected: Nothing happend
     */
    pattern_->isRefreshing_ = true;
    EXPECT_FALSE(accessibilityProperty_->IsScrollable());
    accessibilityProperty_->ResetSupportAction(); // Trigger SetSpecificSupportAction
    EXPECT_EQ(GetActions(accessibilityProperty_), 0);
}

/**
 * @tc.name: PerformActionTest001
 * @tc.desc: RefreshAccessibility PerformAction test ScrollForward and ScrollBackward.
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, PerformActionTest001, TestSize.Level1)
{
    Create(); // trigger SetAccessibilityAction()

    /**
     * @tc.steps: step1. pattern->IsRefreshing() == false
     * @tc.expected: return
     */
    pattern_->isRefreshing_ = false;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());

    /**
     * @tc.steps: step2. pattern->IsRefreshing() == true
     * @tc.expected: Trigger HandleDragStart() ...
     */
    pattern_->isRefreshing_ = true;
    EXPECT_TRUE(accessibilityProperty_->ActActionScrollForward());
}

/**
 * @tc.name: OnKeyEvent001
 * @tc.desc: OnKeyEvent return false
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, OnKeyEvent001, TestSize.Level1)
{
    Create();

    /**
     * @tc.steps: step1. KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN)));

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_UNKNOWN
     */
    EXPECT_FALSE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_UNKNOWN }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
}

/**
 * @tc.name: OnKeyEvent002
 * @tc.desc: OnKeyEvent return true
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, OnKeyEvent002, TestSize.Level1)
{
    bool isTrigger = false;
    auto onRefreshing = [&isTrigger]() { isTrigger = true; };
    Create([onRefreshing](RefreshModelNG model) { model.SetOnRefreshing(std::move(onRefreshing)); });

    /**
     * @tc.steps: step1. KeyCode::KEY_F5
     * @tc.expected: trigger onRefresh event
     */
    EXPECT_TRUE(pattern_->OnKeyEvent(KeyEvent(KeyCode::KEY_F5, KeyAction::UNKNOWN)));
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step2. IsCombinationKey and KeyCode::KEY_R
     * @tc.expected: no trigger onRefresh event
     */
    isTrigger = false;
    EXPECT_TRUE(pattern_->OnKeyEvent(
        KeyEvent(KeyCode::KEY_UNKNOWN, KeyAction::UNKNOWN, { KeyCode::KEY_CTRL_LEFT, KeyCode::KEY_R }, 0,
            TimeStamp(std::chrono::milliseconds(0)), 0, 0, SourceType::KEYBOARD, {})));
    EXPECT_FALSE(isTrigger);
}

/**
 * @tc.name: Frame Scene TEST
 * @tc.desc: Test frame ratio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, RefreshDragFrameRatio001, TestSize.Level1)
{
    Create();
    auto renderContext = AceType::MakeRefPtr<MockRenderContext>();
    frameNode_->renderContext_ = renderContext;
    // CalcExpectedFrameRate will be called
    pattern_->HandleDragStart();
    pattern_->HandleDragUpdate(0.0f);
    pattern_->HandleDragEnd(0.0f);
}

/**
 * @tc.name: GetTargetOffset001
 * @tc.desc: Test frame ratio
 * @tc.type: FUNC
 */
HWTEST_F(RefreshTestNg, GetTargetOffset001, TestSize.Level1)
{
    Create([](RefreshModelNG model) {});
    pattern_->HandleDragStart();
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), 0.f);
    pattern_->HandleDragUpdate(TRIGGER_REFRESH_DISTANCE.ConvertToPx() / RADIO);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE.ConvertToPx());
    pattern_->HandleDragEnd(0.f);
    EXPECT_FLOAT_EQ(pattern_->GetTargetOffset(), TRIGGER_REFRESH_DISTANCE.ConvertToPx());
}
} // namespace OHOS::Ace::NG
