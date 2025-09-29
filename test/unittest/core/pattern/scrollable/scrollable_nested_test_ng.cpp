/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "scrollable_nested_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#define protected public
#define private public
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/components_ng/pattern/overlay/sheet_view.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr float WINDOW_WIDTH = 720.f;
    constexpr float WINDOW_HEIGHT = 1280.f;
    constexpr float SCROLLABLE_WIDTH = 240.f;
    constexpr float SCROLLABLE_HEIGHT = 400.f;
    constexpr float SCROLL_HEAD_HEIGHT = 200.f;
    constexpr float LIST_ITEM_HEIGHT = 600.f;
    constexpr uint64_t MS = 1000 * 1000;
}
void ScrollableNestedTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
    MockAnimationManager::Enable(true);
}

void ScrollableNestedTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ScrollableNestedTestNg::SetUp()
{
}

void ScrollableNestedTestNg::TearDown()
{
    MockAnimationManager::GetInstance().Reset();
}

RefPtr<Scrollable> ScrollableNestedTestNg::GetScrollable(RefPtr<FrameNode> node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto pattern = node->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    CHECK_NULL_RETURN(pattern->scrollableEvent_, nullptr);
    return pattern->scrollableEvent_->scrollable_;
}

void ScrollableNestedTestNg::DragStart(RefPtr<Scrollable> scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->HandleTouchDown();
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    (*(scrollable->panRecognizerNG_->onActionStart_))(info);
}

void ScrollableNestedTestNg::DragUpdate(RefPtr<Scrollable> scrollable, float offset)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(offset);
    (*(scrollable->panRecognizerNG_->onActionUpdate_))(info);
}

void ScrollableNestedTestNg::DragEnd(RefPtr<Scrollable> scrollable, float velocity)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainVelocity(velocity);
    (*(scrollable->panRecognizerNG_->onActionEnd_))(info);
    scrollable->HandleTouchUp();
}

RefPtr<FrameNode> CreatScrollNestedList(EdgeEffect scrollEdgeEffect, EdgeEffect listEdgeEffect,
    NestedScrollOptions nestedOptions)
{
    ScrollModelNG scrollModel;
    scrollModel.Create();
    scrollModel.SetEdgeEffect(scrollEdgeEffect, false);
    ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
        ColumnModelNG colModel;
        colModel.Create(Dimension(0), nullptr, "");
            ColumnModelNG colModel2;
            colModel2.Create(Dimension(0), nullptr, "");
            ViewAbstract::SetHeight(CalcLength(SCROLL_HEAD_HEIGHT));
            ViewStackProcessor::GetInstance()->Pop();

            ListModelNG listModel;
            listModel.Create();
            listModel.SetEdgeEffect(listEdgeEffect, false);
            listModel.SetNestedScroll(nestedOptions);
            ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
            ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
                ListItemModelNG itemModel;
                itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
                ViewAbstract::SetHeight(CalcLength(LIST_ITEM_HEIGHT));
                ViewStackProcessor::GetInstance()->Pop();
            ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto rootNode = AceType::DynamicCast<FrameNode>(element);
    return rootNode;
}

/**
 * @tc.name: NestedScrollTest001
 * @tc.desc: List scroll to edge, OnScrollFrameBegin return 0, not stop fling animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and set SetOnScrollFrameBegin,
     */
    ListModelNG listModel;
    listModel.Create();
    listModel.SetEdgeEffect(EdgeEffect::NONE, false);
    ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
        ListItemModelNG itemModel;
        itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
        ViewAbstract::SetHeight(CalcLength(450));
        ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto listNode = AceType::DynamicCast<FrameNode>(element);
    FlushUITasks(listNode);

    auto listPattern = listNode->GetPattern<ListPattern>();
    auto eventHub = listNode->GetOrCreateEventHub<ListEventHub>();
    eventHub->SetOnScrollFrameBegin([weak = AceType::WeakClaim(AceType::RawPtr(listPattern))]
        (Dimension dy, ScrollState state) {
        auto pattern = weak.Upgrade();
        ScrollFrameResult result;
        float offset = dy.Value();
        if ((Positive(offset) && pattern->IsAtBottom()) || (Negative(offset) && pattern->IsAtTop())) {
            result.offset = Dimension(0);
        } else {
            result.offset = dy;
        }
        return result;
    });

    /**
     * @tc.steps: step2. Scroll to bottom
     * @tc.expected: not stop fling animation
     */
    auto scrollable = GetScrollable(listNode);
    DragStart(scrollable);
    DragUpdate(scrollable, -100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, -100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, -1200);
    FlushUITasks(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: not stop fling animation
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, 100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, 1200);
    FlushUITasks(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);
}

/**
 * @tc.name: NestedScrollTest002
 * @tc.desc: Refresh nested List, List scroll to edge, OnScrollFrameBegin return 0, not stop fling animation
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List and set SetOnScrollFrameBegin,
     */
    RefreshModelNG refreshModel;
    refreshModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
        ListModelNG listModel;
        listModel.Create();
        listModel.SetEdgeEffect(EdgeEffect::NONE, false);
        ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
        ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
            ListItemModelNG itemModel;
            itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
            ViewAbstract::SetHeight(CalcLength(450));
            ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto rootNode = AceType::DynamicCast<FrameNode>(element);
    FlushUITasks(rootNode);

    auto listNode = GetChildFrameNode(rootNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto eventHub = listNode->GetOrCreateEventHub<ListEventHub>();
    eventHub->SetOnScrollFrameBegin([weak = AceType::WeakClaim(AceType::RawPtr(listPattern))]
        (Dimension dy, ScrollState state) {
        auto pattern = weak.Upgrade();
        ScrollFrameResult result;
        float offset = dy.Value();
        if ((Positive(offset) && pattern->IsAtBottom()) || (Negative(offset) && pattern->IsAtTop())) {
            result.offset = Dimension(0);
        } else {
            result.offset = dy;
        }
        return result;
    });

    /**
     * @tc.steps: step2. Scroll to bottom
     * @tc.expected: not stop fling animation
     */
    auto scrollable = GetScrollable(listNode);
    DragStart(scrollable);
    DragUpdate(scrollable, -100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, -100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, -1200);
    FlushUITasks(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: not stop fling animation
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, 100);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, 1200);
    FlushUITasks(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);
}

/**
 * @tc.name: NestedScrollTest003
 * @tc.desc: Scroll nested List
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    ScrollModelNG scrollModel;
    scrollModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
        ListModelNG listModel;
        listModel.Create();
        listModel.SetEdgeEffect(EdgeEffect::NONE, false);
        listModel.SetNestedScroll(NestedScrollOptions {
            .forward = NestedScrollMode::PARENT_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        });
        ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
        ViewAbstract::SetHeight(CalcLength(500));
            ListItemModelNG itemModel;
            itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
            ViewAbstract::SetHeight(CalcLength(600));
            ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto rootNode = AceType::DynamicCast<FrameNode>(element);
    FlushUITasks(rootNode);

    auto listNode = GetChildFrameNode(rootNode, 0);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();

    /**
     * @tc.steps: step2. Scroll to bottom
     * @tc.expected: parent scroll first
     */
    auto scrollable = GetScrollable(listNode);
    DragStart(scrollable);
    DragUpdate(scrollable, -150);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -100);
    DragUpdate(scrollable, -100);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 100);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -100);

    /**
     * @tc.steps: step2. Scroll to top
     * @tc.expected: self scroll first
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 150);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -50);
    DragUpdate(scrollable, 150);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -0);
}

/**
 * @tc.name: NestedScrollTest004
 * @tc.desc: Scroll nested List
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE, NestedScrollOptions {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    scrollScrollable->ratio_ = 0;
    scrollPattern->ratio_ = 0;

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent scroll first
     */
    auto listScrollable = GetScrollable(listNode);
    DragStart(listScrollable);
    DragUpdate(listScrollable, -150);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -150);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent reach bottom, child scroll
     */
    DragUpdate(listScrollable, -150);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 100);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step3. Scroll forward
     * @tc.expected: parent and child reach bottom, parent over scroll
     */
    DragUpdate(listScrollable, -150);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -250);

    /**
     * @tc.steps: step4. Scroll backward
     * @tc.expected: parent out of bottom, parent scroll
     */
    DragUpdate(listScrollable, 25);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -225);

    /**
     * @tc.steps: step5. Scroll backward
     * @tc.expected: parent scroll at bottom, child scroll
     */
    DragUpdate(listScrollable, 50);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 175);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);
}

/**
 * @tc.name: NestedScrollTest005
 * @tc.desc: Scroll nested List
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest005, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::NONE, EdgeEffect::SPRING, NestedScrollOptions {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);
    listScrollable->ratio_ = 0;
    listPattern->ratio_ = 0;

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent scroll first
     */
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent reach bottom, child scroll
     */
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step3. Scroll forward
     * @tc.expected: parent and child reach bottom, child over scroll
     */
    DragUpdate(listScrollable, -50);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 250);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step4. Scroll backward
     * @tc.expected: parent out of bottom, parent scroll
     */
    DragUpdate(listScrollable, 25);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 225);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step5. Scroll backward
     * @tc.expected: parent scroll at bottom, child scroll
     */
    DragUpdate(listScrollable, 50);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 175);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);
}

/**
 * @tc.name: NestedScrollTest006
 * @tc.desc: Swiper nested List
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest006, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    SwiperModelNG scrollModel;
    scrollModel.Create();
    ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
    ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
        ListModelNG listModel;
        listModel.Create();
        listModel.SetListDirection(Axis::HORIZONTAL);
        listModel.SetEdgeEffect(EdgeEffect::NONE, false);
        listModel.SetNestedScroll(NestedScrollOptions {
            .forward = NestedScrollMode::SELF_FIRST,
            .backward = NestedScrollMode::SELF_FIRST,
        });
        ViewAbstract::SetWidth(CalcLength(SCROLLABLE_WIDTH));
        ViewAbstract::SetHeight(CalcLength(SCROLLABLE_HEIGHT));
            ListItemModelNG itemModel;
            itemModel.Create([](int32_t) {}, V2::ListItemStyle::NONE);
            ViewAbstract::SetWidth(CalcLength(300));
            ViewStackProcessor::GetInstance()->Pop();
        ViewStackProcessor::GetInstance()->Pop();
    RefPtr<UINode> element = ViewStackProcessor::GetInstance()->Finish();
    auto rootNode = AceType::DynamicCast<FrameNode>(element);
    FlushUITasks(rootNode);

    auto listNode = GetChildFrameNode(rootNode, 0);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto swiperPattern = rootNode->GetPattern<SwiperPattern>();
    auto listScrollable = GetScrollable(listNode);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: child scroll first
     */
    DragStart(listScrollable);
    DragUpdate(listScrollable, -30);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 30);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: child reach left, parent over scroll
     */
    DragUpdate(listScrollable, -100);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 60);
    EXPECT_TRUE(swiperPattern->IsOutOfEnd());

    /**
     * @tc.steps: step3. Scroll backward
     * @tc.expected: parent over scroll, parent scroll first
     */
    DragUpdate(listScrollable, 20);
    FlushUITasks(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 60);
    EXPECT_TRUE(swiperPattern->IsOutOfEnd());
}

/**
 * @tc.name: NestedScrollTest007
 * @tc.desc: Scroll nested List
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest007, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::NONE, EdgeEffect::NONE, NestedScrollOptions {
        .forward = NestedScrollMode::PARALLEL,
        .backward = NestedScrollMode::PARALLEL,
    });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent scroll first
     */
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent reach bottom, child scroll
     */
    DragUpdate(listScrollable, 200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 0);
}

/**
 * @tc.name: NestedScrollTest008
 * @tc.desc: Scroll nested List, Scroll spring animate back to top, remain velocity start list fling animation.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest008, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE, NestedScrollOptions {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    scrollScrollable->InitFriction(FRICTION);
    scrollScrollable->ratio_ = 0;
    scrollPattern->ratio_ = 0;

    /**
     * @tc.steps: step2. Scroll backward
     * @tc.expected: parent over scroll
     */
    auto listScrollable = GetScrollable(listNode);
    listScrollable->InitFriction(FRICTION);
    DragStart(listScrollable);
    DragUpdate(listScrollable, 100);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 100);

    /**
     * @tc.steps: step3. Scroll forward
     * @tc.expected: parent and child reach bottom, parent over scroll
     */
    MockAnimationManager::GetInstance().SetTicks(2);
    listScrollable->lastMainDelta_ = 0.0;
    DragEnd(listScrollable, 1000);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 100);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 50);

    /*
     * @tc.steps: step4. TickByVelocity
     * @tc.expected: Scroll spring animate back to top, remain velocity start list fling animation.
     */
    MockPipelineContext::GetCurrent()->SetVsyncTime(scrollScrollable->lastVsyncTime_ + 30 * MS);
    MockAnimationManager::GetInstance().TickByVelocity(-60);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 0);

    /*
     * @tc.steps: step5. Tick
     * @tc.expected: start list fling animation.
     */
    float distance = 2000 / (SLOW_FRICTION * -FRICTION_SCALE);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, distance / 2 - 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -(distance - 200));
}

/**
 * @tc.name: NestedScrollTest009
 * @tc.desc: Scroll nested List, touch scroll trigger list animate stop
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, NestedScrollTest009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List, edge effect is none
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE, NestedScrollOptions {
        .forward = NestedScrollMode::PARENT_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    scrollScrollable->InitFriction(FRICTION);
    scrollScrollable->ratio_ = 0;
    scrollPattern->ratio_ = 0;

    bool listOnScrollStart = false;
    bool scrollOnScrollStart = false;
    bool listOnScrollStop = false;
    bool scrollOnScrollStop = false;
    ListModelNG::SetOnScrollStart(AceType::RawPtr(listNode), [&listOnScrollStart]() {
        listOnScrollStart = true;
    });
    ScrollModelNG::SetOnScrollStart(AceType::RawPtr(rootNode), [&scrollOnScrollStart]() {
        scrollOnScrollStart = true;
    });
    ListModelNG::SetOnScrollStop(AceType::RawPtr(listNode), [&listOnScrollStop]() {
        listOnScrollStop = true;
    });
    ScrollModelNG::SetOnScrollStop(AceType::RawPtr(rootNode), [&scrollOnScrollStop]() {
        scrollOnScrollStop = true;
    });

    /**
     * @tc.steps: step2. Scroll forward
     * @tc.expected: parent process scroll
     */
    auto listScrollable = GetScrollable(listNode);
    listScrollable->InitFriction(FRICTION);
    DragStart(listScrollable);
    DragUpdate(listScrollable, -10);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -10);

    /**
     * @tc.steps: step3. DragEnd with velocity
     * @tc.expected: start fling animation
     */
    MockAnimationManager::GetInstance().SetTicks(3);
    listScrollable->lastMainDelta_ = 0.0;
    DragEnd(listScrollable, -420);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -10);
    EXPECT_TRUE(listOnScrollStart);
    EXPECT_TRUE(scrollOnScrollStart);

    MockPipelineContext::GetCurrent()->SetVsyncTime(GetSysTimestamp());
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -50);
    MockPipelineContext::GetCurrent()->SetVsyncTime(scrollPattern->nestedScrollTimestamp_ + 50 * MS);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -90);

    /**
     * @tc.steps: step4. Scroll touch down
     * @tc.expected: list stop animation
     */
    TouchEventInfo touchEvent = TouchEventInfo("unknown");
    scrollPattern->OnTouchDown(touchEvent);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_TRUE(listOnScrollStop);
    EXPECT_TRUE(scrollOnScrollStop);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -90);
}

/**
 * @tc.name: SheetNestedScroll001
 * @tc.desc: Sheet nested Scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, SheetNestedScroll001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create sheet page.
     */
    auto themeManager = AceType::MakeRefPtr<MockThemeManager>();
    MockPipelineContext::GetCurrent()->SetThemeManager(themeManager);
    EXPECT_CALL(*themeManager, GetTheme(_)).WillRepeatedly(Return(AceType::MakeRefPtr<SheetTheme>()));
    int32_t apiTargetVersion = AceApplicationInfo::GetInstance().GetApiTargetVersion();
    int32_t minPlatformVersion = MockPipelineContext::GetCurrentContext()->GetMinPlatformVersion();
    AceApplicationInfo::GetInstance().SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWELVE);
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion((int32_t)PlatformVersion::VERSION_TWELVE);

    auto builder = FrameNode::CreateFrameNode(V2::COLUMN_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    ViewAbstract::SetHeight(AceType::RawPtr(builder), CalcLength(WINDOW_HEIGHT + 200));
    ViewAbstract::SetWidth(AceType::RawPtr(builder), CalcLength(WINDOW_WIDTH));
    auto callback = [](const std::string&) {};
    SheetStyle style;
    auto sheetNode = SheetView::CreateSheetPage(0, "", builder, builder, std::move(callback), style);
    ASSERT_NE(sheetNode, nullptr);
    auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
    ASSERT_NE(sheetPattern, nullptr);
    auto scrollNode = sheetPattern->GetSheetScrollNode();
    ASSERT_NE(scrollNode, nullptr);
    auto scrollPattern = scrollNode->GetPattern<ScrollPattern>();
    ASSERT_NE(scrollPattern, nullptr);
    FlushUITasks(sheetNode);

    /**
     * @tc.steps: step2. Scroll 100
     * @tc.expected: Scroll offset is 100
     */
    auto scrollable = GetScrollable(scrollNode);
    DragStart(scrollable);
    DragUpdate(scrollable, -100);
    FlushUITasks(sheetNode);
    EXPECT_FLOAT_EQ(scrollPattern->GetTotalOffset(), 100);

    /**
     * @tc.steps: step3. Scroll -200
     * @tc.expected: Scroll offset is 0, Sheet offset is 100
     */
    DragUpdate(scrollable, 200);
    FlushUITasks(sheetNode);
    EXPECT_FLOAT_EQ(scrollPattern->GetTotalOffset(), 0);
    EXPECT_FLOAT_EQ(sheetPattern->currentOffset_, 100);

    /**
     * @tc.steps: step3. Scroll 100
     * @tc.expected: Scroll offset is 0, Sheet offset is 100
     */
    DragUpdate(scrollable, -100);
    FlushUITasks(sheetNode);
    EXPECT_FLOAT_EQ(scrollPattern->GetTotalOffset(), 0);
    EXPECT_FLOAT_EQ(sheetPattern->currentOffset_, 0);

    AceApplicationInfo::GetInstance().SetApiTargetVersion(apiTargetVersion);
    MockPipelineContext::GetCurrentContext()->SetMinPlatformVersion(minPlatformVersion);
}

/**
 * @tc.name: BackToTopNestedScrollTest001
 * @tc.desc: Set pipeline onShow_ is false for scroll nested List, NOT scroll back to top.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, BackToTopNestedScrollTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE,
        NestedScrollOptions {
            .forward = NestedScrollMode::PARALLEL,
            .backward = NestedScrollMode::PARALLEL,
        });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);
    /**
     * @tc.steps: step2. Scroll backward and call OnStatusBarClick when pipeline onShow_ is false.
     * @tc.expected: Neither the list nor the scroll is scrolling.
     */
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    scrollPattern->OnStatusBarClick();
    listPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step3. Set backToTop to true and call OnStatusBarClick when pipeline onShow_ is false.
     * @tc.expected: Neither the list nor the scroll is scrolling.
     */
    listPattern->backToTop_ = true;
    scrollPattern->backToTop_ = true;
    MockAnimationManager::GetInstance().SetTicks(1);
    scrollPattern->OnStatusBarClick();
    listPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);
}

/**
 * @tc.name: BackToTopNestedScrollTest002
 * @tc.desc: Set backToTop for scroll nested List, Scroll spring animate back to top.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, BackToTopNestedScrollTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE,
        NestedScrollOptions {
            .forward = NestedScrollMode::PARALLEL,
            .backward = NestedScrollMode::PARALLEL,
        });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);
    /**
     * @tc.steps: step2. Scroll backward and call OnStatusBarClick when pipeline onShow_ and onFocus_ is true.
     * @tc.expected: Neither the list nor the scroll is scrolling.
     */
    MockPipelineContext::GetCurrent()->onShow_ = true;
    MockPipelineContext::GetCurrent()->onFocus_ = true;
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    scrollPattern->OnStatusBarClick();
    listPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step3. Set listPattern backToTop is true.
     * @tc.expected: Only list scroll to top.
     */
    listPattern->backToTop_ = true;
    MockAnimationManager::GetInstance().SetTicks(1);
    listPattern->OnStatusBarClick();
    scrollPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    MockAnimationManager::GetInstance().Tick();
    // skip large offset when backToTop
    EXPECT_TRUE(listPattern->isNeedCheckOffset_);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FALSE(listPattern->isNeedCheckOffset_);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);

    /**
     * @tc.steps: step4. Set scrollPattern backToTop is true.
     * @tc.expected: Scroll component scroll back to top.
     */
    scrollPattern->backToTop_ = true;
    MockAnimationManager::GetInstance().SetTicks(1);
    scrollPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
}

/**
 * @tc.name: BackToTopNestedScrollTest003
 * @tc.desc: Set both backToTop of nested scroll components and scroll to the top.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, BackToTopNestedScrollTest003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE,
        NestedScrollOptions {
            .forward = NestedScrollMode::PARALLEL,
            .backward = NestedScrollMode::PARALLEL,
        });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);

    /**
     * @tc.steps: step2. Scroll backward, set both listPattern and scrollPattern backToTop to true.
     * @tc.expected: Both list and scroll component scroll to top.
     */
    MockPipelineContext::GetCurrent()->onShow_ = true;
    MockPipelineContext::GetCurrent()->onFocus_ = true;
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    listPattern->backToTop_ = true;
    scrollPattern->backToTop_ = true;
    MockAnimationManager::GetInstance().SetTicks(1);
    scrollPattern->OnStatusBarClick();
    listPattern->OnStatusBarClick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, 0);
}

/**
 * @tc.name: BackToTopNestedScrollTest004
 * @tc.desc: Set backToTop for scroll nested List,  touch stop animation.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableNestedTestNg, BackToTopNestedScrollTest004, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create Scroll nested List
     */
    auto rootNode = CreatScrollNestedList(EdgeEffect::SPRING, EdgeEffect::NONE,
        NestedScrollOptions {
            .forward = NestedScrollMode::PARALLEL,
            .backward = NestedScrollMode::PARALLEL,
        });
    FlushUITasks(rootNode);

    auto colNode = GetChildFrameNode(rootNode, 0);
    auto listNode = GetChildFrameNode(colNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto scrollPattern = rootNode->GetPattern<ScrollPattern>();
    auto scrollScrollable = GetScrollable(rootNode);
    auto listScrollable = GetScrollable(listNode);

    bool listOnScrollStop = false;
    bool scrollOnScrollStop = false;
    ListModelNG::SetOnScrollStop(AceType::RawPtr(listNode), [&listOnScrollStop]() { listOnScrollStop = true; });
    ScrollModelNG::SetOnScrollStop(AceType::RawPtr(rootNode), [&scrollOnScrollStop]() { scrollOnScrollStop = true; });
    /**
     * @tc.steps: step2. When scroll back to top, touch scroll and list trigger animate stop.
     * @tc.expected: Scroll and list stop animation.
     */
    MockPipelineContext::GetCurrent()->onShow_ = true;
    MockPipelineContext::GetCurrent()->onFocus_ = true;
    DragStart(listScrollable);
    DragUpdate(listScrollable, -200);
    listScrollable->lastMainDelta_ = 0.0;
    DragEnd(listScrollable, 0);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    listPattern->backToTop_ = true;
    scrollPattern->backToTop_ = true;
    scrollPattern->OnStatusBarClick();
    listPattern->OnStatusBarClick();

    TouchEventInfo touchEvent = TouchEventInfo("unknown");
    listPattern->OnTouchDown(touchEvent);
    scrollPattern->OnTouchDown(touchEvent);
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_TRUE(listOnScrollStop);
    EXPECT_TRUE(scrollOnScrollStop);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks(rootNode);
    FlushUITasks(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 200);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -200);
}
} // namespace OHOS::Ace::NG
