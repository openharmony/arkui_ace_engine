/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "list_nested_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#define protected public
#define private public
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/refresh/refresh_model_ng.h"
#include "core/components_ng/pattern/refresh/refresh_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr float SCROLLABLE_WIDTH = 240.f;
    constexpr float SCROLLABLE_HEIGHT = 400.f;
}
void ListNestedTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
}

void ListNestedTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ListNestedTestNg::SetUp()
{
}

void ListNestedTestNg::TearDown()
{
}

RefPtr<Scrollable> ListNestedTestNg::GetScrollable(RefPtr<FrameNode> node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto pattern = node->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    CHECK_NULL_RETURN(pattern->scrollableEvent_, nullptr);
    return pattern->scrollableEvent_->scrollable_;
}

void ListNestedTestNg::DragStart(RefPtr<Scrollable> scrollable)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    (*(scrollable->panRecognizerNG_->onActionStart_))(info);
}

void ListNestedTestNg::DragUpdate(RefPtr<Scrollable> scrollable, float offset)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(offset);
    (*(scrollable->panRecognizerNG_->onActionUpdate_))(info);
}

void ListNestedTestNg::DragEnd(RefPtr<Scrollable> scrollable, float velocity)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainVelocity(velocity);
    (*(scrollable->panRecognizerNG_->onActionEnd_))(info);
}

/**
 * @tc.name: NestedScrollTest001
 * @tc.desc: List scroll to edge, OnScrollFrameBegin return 0, not stop fling animation
 * @tc.type: FUNC
 */
HWTEST_F(ListNestedTestNg, NestedScrollTest001, TestSize.Level1)
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
    FlushLayoutTask(listNode);

    auto listPattern = listNode->GetPattern<ListPattern>();
    auto eventHub = listNode->GetEventHub<ListEventHub>();
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
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, -100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, -1200);
    FlushLayoutTask(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: not stop fling animation
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, 100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, 1200);
    FlushLayoutTask(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);
}

/**
 * @tc.name: NestedScrollTest002
 * @tc.desc: Refresh nested List, List scroll to edge, OnScrollFrameBegin return 0, not stop fling animation
 * @tc.type: FUNC
 */
HWTEST_F(ListNestedTestNg, NestedScrollTest002, TestSize.Level1)
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
    FlushLayoutTask(rootNode);

    auto listNode = GetChildFrameNode(rootNode, 1);
    auto listPattern = listNode->GetPattern<ListPattern>();
    auto eventHub = listNode->GetEventHub<ListEventHub>();
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
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, -100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, -1200);
    FlushLayoutTask(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);

    /**
     * @tc.steps: step3. Scroll to top
     * @tc.expected: not stop fling animation
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragUpdate(scrollable, 100);
    FlushLayoutTask(listNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FALSE(scrollable->canOverScroll_);
    DragEnd(scrollable, 1200);
    FlushLayoutTask(listNode);
    EXPECT_FALSE(scrollable->canOverScroll_);
}

/**
 * @tc.name: NestedScrollTest003
 * @tc.desc: Scroll nested List
 * @tc.type: FUNC
 */
HWTEST_F(ListNestedTestNg, NestedScrollTest003, TestSize.Level1)
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
    FlushLayoutTask(rootNode);

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
    FlushLayoutTask(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 50);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -100);
    DragUpdate(scrollable, -100);
    FlushLayoutTask(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 100);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -100);

    /**
     * @tc.steps: step2. Scroll to top
     * @tc.expected: self scroll first
     */
    DragStart(scrollable);
    DragUpdate(scrollable, 150);
    FlushLayoutTask(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -50);
    DragUpdate(scrollable, 150);
    FlushLayoutTask(rootNode);
    EXPECT_FLOAT_EQ(listPattern->currentOffset_, 0);
    EXPECT_FLOAT_EQ(scrollPattern->currentOffset_, -0);
}
} // namespace OHOS::Ace::NG
