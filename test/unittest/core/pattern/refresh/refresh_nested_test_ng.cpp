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
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t TICK = 2;
constexpr float CONTENT_MAIN_SIZE = 1000.f;
constexpr float LIST_HEIGHT = 400.f;
constexpr float SWIPER_HEIGHT = 400.f;
constexpr int32_t TEXT_NUMBER = 5;
constexpr float TOP_CONTENT_HEIGHT = 200.f;
constexpr float VERTICAL_SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - SCROLL_HEIGHT;
} // namespace

class RefreshNestedTestNg : public RefreshTestNg {
public:
    static void SetUpTestSuite();
    static void TearDownTestSuite();
    ScrollModelNG CreateScroll();
    ScrollModelNG CreateNestScroll();
    void CreateContent(float mainSize = CONTENT_MAIN_SIZE);
    void CreateNestedSwiper();
    ListModelNG CreateNestedList();
    AssertionResult Position(const RefPtr<FrameNode>& frameNode, float expectOffset) override;

    RefPtr<FrameNode> scrollNode_;
    RefPtr<ScrollPattern> scrollPattern_;
    RefPtr<FrameNode> nestNode_;
    RefPtr<ScrollPattern> nestPattern_;
    RefPtr<FrameNode> swiperNode_;
    RefPtr<SwiperPattern> swiperPattern_;
    RefPtr<FrameNode> listNode_;
    RefPtr<ListPattern> listPattern_;
};

void RefreshNestedTestNg::SetUpTestSuite()
{
    RefreshTestNg::SetUpTestSuite();
    MockPipelineContext::pipeline_->SetMinPlatformVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    AceApplicationInfo::GetInstance().SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
}

void RefreshNestedTestNg::TearDownTestSuite()
{
    RefreshTestNg::TearDownTestSuite();
}

ScrollModelNG RefreshNestedTestNg::CreateScroll()
{
    ScrollModelNG model;
    model.Create();
    auto proxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(proxy);
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    scrollNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    scrollPattern_ = scrollNode_->GetPattern<ScrollPattern>();
    return model;
}

ScrollModelNG RefreshNestedTestNg::CreateNestScroll()
{
    ScrollModelNG model;
    model.Create();
    auto proxy = model.CreateScrollBarProxy();
    model.SetScrollBarProxy(proxy);
    ViewAbstract::SetWidth(CalcLength(SCROLL_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLL_HEIGHT));
    nestNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    nestPattern_ = nestNode_->GetPattern<ScrollPattern>();
    return model;
}

void RefreshNestedTestNg::CreateContent(float mainSize)
{
    ColumnModelNG colModel;
    colModel.Create(Dimension(0), nullptr, "");
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(mainSize));
}

void RefreshNestedTestNg::CreateNestedSwiper()
{
    SwiperModelNG model;
    model.Create();
    model.SetDirection(Axis::VERTICAL);
    model.SetLoop(false);
    ViewAbstract::SetWidth(CalcLength(REFRESH_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SWIPER_HEIGHT));
    swiperNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    swiperPattern_ = swiperNode_->GetPattern<SwiperPattern>();
    for (int32_t index = 0; index < TEXT_NUMBER; index++) {
        RefreshTestNg::CreateText();
    }
    ViewStackProcessor::GetInstance()->Pop();
}

ListModelNG RefreshNestedTestNg::CreateNestedList()
{
    ListModelNG listModel;
    listModel.Create();
    listModel.SetEdgeEffect(EdgeEffect::NONE, true);
    ViewAbstract::SetWidth(CalcLength(REFRESH_WIDTH));
    ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
    {
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
        ViewStackProcessor::GetInstance()->Pop();
    }
    listNode_ = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    listPattern_ = listNode_->GetPattern<ListPattern>();
    ViewStackProcessor::GetInstance()->Pop();
    return listModel;
}

AssertionResult RefreshNestedTestNg::Position(const RefPtr<FrameNode>& frameNode, float expectOffset)
{
    return IsEqual(GetChildY(frameNode, 0), expectOffset);
}

/**
 * @tc.name: RefreshNestedSwiper001
 * @tc.desc: Test Refresh nested Swiper with selfOnly mode in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshNestedSwiper001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper.
     */
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
HWTEST_F(RefreshNestedTestNg, RefreshNestedSwiper002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Construct the structure of Refresh and Swiper, and set SELF_FIRST to the nested mode of swiper.
     */
    CreateScroll();
    {
        CreateContent();
        {
            RefreshTestNg::CreateText();
            CreateRefresh();
            {
                CreateNestedSwiper();
            }
        }
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
HWTEST_F(RefreshNestedTestNg, RefreshPatternHandleScroll001, TestSize.Level1)
{
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
HWTEST_F(RefreshNestedTestNg, RefreshPatternHandleScroll002, TestSize.Level1)
{
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
HWTEST_F(RefreshNestedTestNg, RefreshPatternHandleScroll003, TestSize.Level1)
{
    RefreshModelNG model;
    model.Create();
    GetRefresh();
    ViewStackProcessor::GetInstance()->Finish();

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
 * @tc.name: RefreshScroll001
 * @tc.desc: Drag scroll down over the top, will trigger refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshScroll001, TestSize.Level1)
{
    CreateRefresh();
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    DragStart(scrollNode_, Offset());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG
     */
    DragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal refreshOffset
     * @tc.expected: OVER_DRAG
     */
    DragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    DragEnd(0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshScroll002
 * @tc.desc: UnScrollable scroll and !alwaysEnabled, drag scroll down over the top, will trigger refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshScroll002, TestSize.Level1)
{
    bool alwaysEnabled = false;
    CreateRefresh();
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, alwaysEnabled);
    CreateDone();

    /**
     * @tc.steps: step1. Drag scroll down over the top
     * @tc.expected: Will trigger refreshing
     */
    DragAction(scrollNode_, Offset(), TRIGGER_REFRESH_DISTANCE, 0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshScrollNest001
 * @tc.desc: Create nest scroll, drag scroll down over the top, will trigger refreshing when has no EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshScrollNest001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateRefresh();
    {
        CreateScroll();
        {
            CreateContent(TOP_CONTENT_HEIGHT + SCROLL_HEIGHT);
            {
                CreateContent(TOP_CONTENT_HEIGHT);
                ViewStackProcessor::GetInstance()->Pop();
                ScrollModelNG nestModel = CreateNestScroll();
                nestModel.SetNestedScroll(nestedOpt);
                {
                    CreateContent();
                }
            }
        }
    }
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    DragStart(nestNode_, Offset());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG
     */
    DragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DRAG);

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal refreshOffset
     * @tc.expected: OVER_DRAG
     */
    DragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    DragEnd(0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshScrollNest002
 * @tc.desc: Create nest scroll, drag scroll down over the top, will not trigger refreshing when has EdgeEffect
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, DISABLED_RefreshScrollNest002, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateRefresh();
    CreateScroll();
    CreateContent(TOP_CONTENT_HEIGHT + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_HEIGHT);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    nestModel.SetEdgeEffect(EdgeEffect::SPRING, true);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragStart
     * @tc.expected: Nothing changed
     */
    DragStart(nestNode_, Offset());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_TRUE(Position(nestNode_, 0));

    /**
     * @tc.steps: step2. HandleDragUpdate, the delta less than or equal TRIGGER_LOADING_DISTANCE
     * @tc.expected: DRAG
     */
    DragUpdate(TRIGGER_LOADING_DISTANCE / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_TRUE(Position(nestNode_, TRIGGER_LOADING_DISTANCE));

    /**
     * @tc.steps: step3. HandleDragUpdate, the delta(Plus previous delta) greater than or equal refreshOffset
     * @tc.expected: OVER_DRAG
     */
    DragUpdate((TRIGGER_REFRESH_DISTANCE - TRIGGER_LOADING_DISTANCE) / pattern_->CalculatePullDownRatio());
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_TRUE(Position(nestNode_, TRIGGER_REFRESH_DISTANCE));

    /**
     * @tc.steps: step4. HandleDragEnd
     * @tc.expected: REFRESH
     */
    DragEnd(0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    EXPECT_TRUE(Position(nestNode_, TRIGGER_REFRESH_DISTANCE));
}

/**
 * @tc.name: RefreshScrollNest003
 * @tc.desc: Test onScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshScrollNest003, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateRefresh();
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    int32_t stopCount = 0;
    model.SetOnScrollStop([&stopCount]() { ++stopCount; });
    CreateContent(TOP_CONTENT_HEIGHT + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_HEIGHT);
    ViewStackProcessor::GetInstance()->Pop();
    ScrollModelNG nestModel = CreateNestScroll();
    int32_t nestStopCount = 0;
    nestModel.SetOnScrollStop([&nestStopCount]() { ++nestStopCount; });
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Drag down child scroll
     * @tc.expected: trigger outer scroll onScrollStop
     */
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::INACTIVE);
    float dragDelta = 100.f;
    float velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_GT(pattern_->scrollOffset_, 0.f);
    EXPECT_TRUE(Position(scrollNode_, 0));
    EXPECT_TRUE(Position(nestNode_, 0));
    MockAnimationManager::GetInstance().Tick();
    FlushLayoutTask(scrollNode_);
    EXPECT_EQ(nestStopCount, 1);
    EXPECT_EQ(stopCount, 1);
}

/**
 * @tc.name: ScrollRefreshNest001
 * @tc.desc: Scroll > Refresh > nest, nest still could affect parent scroll
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, ScrollRefreshNest001, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    {
        CreateContent(TOP_CONTENT_HEIGHT + SCROLL_HEIGHT);
        {
            CreateContent(TOP_CONTENT_HEIGHT);
            ViewStackProcessor::GetInstance()->Pop();
            CreateRefresh();
            {
                ScrollModelNG nestModel = CreateNestScroll();
                nestModel.SetNestedScroll(nestedOpt);
                {
                    CreateContent();
                }
            }
        }
    }
    CreateDone();

    /**
     * @tc.steps: step1. Drag up the nest
     * @tc.expected: Scrolling parent because forward is PARENT_FIRST
     */
    float dragDelta = -10.f;
    float velocityDelta = -TOP_CONTENT_HEIGHT - dragDelta;
    MockAnimationManager::GetInstance().SetTicks(TICK);
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(scrollNode_, dragDelta));
    EXPECT_TRUE(TickPosition(scrollNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(scrollNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(scrollPattern_->IsAtBottom());

    /**
     * @tc.steps: step2. Continue drag up the nest
     * @tc.expected: Scrolling nest because parent is at bottom
     */
    dragDelta = -100.f;
    velocityDelta = -VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(scrollNode_, -TOP_CONTENT_HEIGHT));
    EXPECT_TRUE(Position(nestNode_, dragDelta));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta));
    EXPECT_TRUE(nestPattern_->IsAtBottom());

    /**
     * @tc.steps: step3. Drag down the nest
     * @tc.expected: Scrolling nest because backward is SELF_FIRST
     */
    dragDelta = 100.f;
    velocityDelta = VERTICAL_SCROLLABLE_DISTANCE - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(scrollNode_, -TOP_CONTENT_HEIGHT));
    EXPECT_TRUE(Position(nestNode_, dragDelta - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, dragDelta + velocityDelta / TICK - VERTICAL_SCROLLABLE_DISTANCE));
    EXPECT_TRUE(TickPosition(nestNode_, 0));
    EXPECT_TRUE(nestPattern_->IsAtTop());

    /**
     * @tc.steps: step4. Continue drag down the nest
     * @tc.expected: Scrolling parent because nest is at top
     */
    dragDelta = 10.f;
    velocityDelta = TOP_CONTENT_HEIGHT - dragDelta;
    DragAction(nestNode_, Offset(), dragDelta, velocityDelta);
    EXPECT_TRUE(Position(nestNode_, 0));
    EXPECT_TRUE(Position(scrollNode_, -TOP_CONTENT_HEIGHT + dragDelta));
    EXPECT_TRUE(TickPosition(scrollNode_, dragDelta + velocityDelta / TICK - TOP_CONTENT_HEIGHT));
    EXPECT_TRUE(TickPosition(scrollNode_, 0));
    EXPECT_TRUE(scrollPattern_->IsAtTop());
}

/**
 * @tc.name: ScrollRefreshNest002
 * @tc.desc: Scroll > Refresh > nest, drag scroll down over the top, will trigger refreshing
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, ScrollRefreshNest002, TestSize.Level1)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    CreateScroll();
    CreateContent(TOP_CONTENT_HEIGHT + SCROLL_HEIGHT);
    CreateContent(TOP_CONTENT_HEIGHT);
    ViewStackProcessor::GetInstance()->Pop();
    CreateRefresh();
    ScrollModelNG nestModel = CreateNestScroll();
    nestModel.SetNestedScroll(nestedOpt);
    CreateContent();
    CreateDone();

    /**
     * @tc.steps: step1. Drag scroll down over the top
     * @tc.expected: Will trigger refreshing
     */
    DragAction(nestNode_, Offset(), TRIGGER_REFRESH_DISTANCE, 0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
}

/**
 * @tc.name: RefreshListNested001
 * @tc.desc: In Refresh-List scene, update NestedScrollMode while dragging
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshListNested001, TestSize.Level1)
{
    CreateRefresh();
    ListModelNG listModel = CreateNestedList();
    CreateDone();
    EXPECT_EQ(listPattern_->nestedScroll_.forward, NestedScrollMode::SELF_ONLY);
    EXPECT_EQ(listPattern_->nestedScroll_.backward, NestedScrollMode::SELF_ONLY);
    DragStart(listNode_, Offset(0, 0));
    EXPECT_EQ(listPattern_->nestedScroll_.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(listPattern_->nestedScroll_.backward, NestedScrollMode::SELF_FIRST);
    listPattern_->SetNestedScroll(NestedScrollOptions {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    });
    EXPECT_EQ(listPattern_->nestedScroll_.forward, NestedScrollMode::PARENT_FIRST);
    EXPECT_EQ(listPattern_->nestedScroll_.backward, NestedScrollMode::SELF_FIRST);
    listPattern_->SetNestedScroll(NestedScrollOptions {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::PARENT_FIRST,
    });
    EXPECT_EQ(listPattern_->nestedScroll_.forward, NestedScrollMode::SELF_FIRST);
    EXPECT_EQ(listPattern_->nestedScroll_.backward, NestedScrollMode::PARENT_FIRST);
}

/**
 * @tc.name: RefreshListNested002
 * @tc.desc: In Refresh-List scene, drag end after slide up greater than TRIGGER_REFRESH_DISTANCE in REFRESH status
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshListNested002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh-list scene
     */
    RefreshModelNG refreshModel = CreateRefresh();
    refreshModel.SetPullDownRatio(1.0f);
    CreateNestedList();
    CreateDone();

    /**
     * @tc.steps: step2. pull down, the delta is TRIGGER_REFRESH_DISTANCE
     * @tc.expected: refreshStatus_ is REFRESH
     */
    DragStart(listNode_, Offset(0, 0));
    DragUpdate(TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::OVER_DRAG);

    /**
     * @tc.steps: step3. drag end
     * @tc.expected: refreshStatus_ is REFRESH
     */
    DragEnd(0);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);

    /**
     * @tc.steps: step4. slide up, the delta is TRIGGER_REFRESH_DISTANCE
     * @tc.expected: refreshStatus_ is REFRESH, and scrollOffset is 0
     */
    DragStart(listNode_, Offset(0, TRIGGER_REFRESH_WITH_TEXT_DISTANCE));
    DragUpdate(-TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step5. continue to slide up, list is over edge
     * @tc.expected: refreshStatus_ is REFRESH, and scrollOffset is 0
     */
    DragUpdate(-TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::REFRESH);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);

    /**
     * @tc.steps: step3. drag end, trigger refresh's OnScrollEndRecursive and HandleDragEnd
     * @tc.expected: refreshStatus_ is DONE
     */
    DragEnd(0.f);
    EXPECT_EQ(pattern_->refreshStatus_, RefreshStatus::DONE);
    EXPECT_EQ(pattern_->scrollOffset_, 0.f);
}

/**
 * @tc.name: RefreshListNested003
 * @tc.desc: In Refresh-List scene, add custom node on DragUpdate status
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshListNested003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh-list scene
     */
    RefreshModelNG refreshModel = CreateRefresh();
    refreshModel.SetPullDownRatio(1.0f);
    refreshModel.SetLoadingText("loadingText");
    CreateNestedList();
    CreateDone();

    /**
     * @tc.steps: step2. pull down, the delta is TRIGGER_REFRESH_DISTANCE
     * @tc.expected: list's translation is TRIGGER_REFRESH_DISTANCE
     */
    DragStart(listNode_, Offset(0, 0));
    DragUpdate(TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(listNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), TRIGGER_REFRESH_DISTANCE);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);

    /**
     * @tc.steps: step3. add custom node
     * @tc.expected: refreshStatus_ is REFRESH
     */
    pattern_->AddCustomBuilderNode(CreateCustomNode());
    frameNode_->MarkModifyDone();
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(listNode_->GetRenderContext()->GetTransformTranslate()->y.Value(), 0.f);
    EXPECT_EQ(pattern_->scrollOffset_, TRIGGER_REFRESH_DISTANCE);
}

/**
 * @tc.name: RefreshListListNested001
 * @tc.desc: In Refresh-List-List scene, EdgeEffect is NONE and backward mode is SELF_FIRST
 * @tc.type: FUNC
 */
HWTEST_F(RefreshNestedTestNg, RefreshListListNested001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create refresh-list-list scene
     */
    RefreshModelNG refreshModel = CreateRefresh();
    std::optional<float> pullDownRatio = 1.0f;
    refreshModel.SetPullDownRatio(pullDownRatio);
    {
        ListModelNG listModel;
        listModel.Create();
        listModel.SetEdgeEffect(EdgeEffect::NONE, false);
        listModel.SetNestedScroll(NestedScrollOptions {
            .forward = NestedScrollMode::PARENT_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        });
        ViewAbstract::SetWidth(CalcLength(REFRESH_WIDTH));
        ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT));
        {
            ListItemModelNG itemModel;
            itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
            ViewAbstract::SetHeight(CalcLength(450));
            {
                ListModelNG listModelTwo;
                listModelTwo.Create();
                listModelTwo.SetEdgeEffect(EdgeEffect::NONE, false);
                listModelTwo.SetNestedScroll(NestedScrollOptions {
                    .forward = NestedScrollMode::PARENT_FIRST,
                    .backward = NestedScrollMode::SELF_FIRST,
                });
                ViewAbstract::SetWidth(CalcLength(REFRESH_WIDTH));
                ViewAbstract::SetHeight(CalcLength(LIST_HEIGHT / 2));
                {
                    ListItemModelNG itemModelTwo;
                    itemModelTwo.Create([](int32_t) {}, V2::ListItemStyle::NONE);
                    ViewAbstract::SetHeight(CalcLength(225));
                    ViewStackProcessor::GetInstance()->Pop();
                }
                ViewStackProcessor::GetInstance()->Pop();
            }
            ViewStackProcessor::GetInstance()->Pop();
        }
        ViewStackProcessor::GetInstance()->Pop();
    }
    CreateDone();

    /**
     * @tc.steps: step2. get second list node
     */
    auto firstListNode = GetChildFrameNode(frameNode_, 1);
    auto firstItemNode = GetChildFrameNode(firstListNode, 0);
    auto secondListNode = GetChildFrameNode(firstItemNode, 0);

    /**
     * @tc.steps: step3. scroll second list to trigger refresh
     * @tc.expected: drag offset is equal with refresh's refresh offset
     */
    DragStart(secondListNode, Offset(0, 0));
    DragUpdate(10);
    FlushLayoutTask(frameNode_);
    EXPECT_EQ(pattern_->scrollOffset_, 10);
}
} // namespace OHOS::Ace::NG
