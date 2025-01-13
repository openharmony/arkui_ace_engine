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

#include "scrollable_axis_test_ng.h"

#include "test/mock/base/mock_task_executor.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/common/mock_theme_manager.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"
#define protected public
#define private public
#include "core/components_ng/pattern/list/list_item_model_ng.h"
#include "core/components_ng/pattern/list/list_model_ng.h"
#include "core/components_ng/pattern/list/list_pattern.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_model_ng.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float SCROLLABLE_WIDTH = 240.f;
constexpr float SCROLLABLE_HEIGHT = 400.f;
} // namespace
void ScrollableAxisTestNg::SetUpTestSuite()
{
    MockPipelineContext::SetUp();
    MockContainer::SetUp();
    MockContainer::Current()->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    MockPipelineContext::GetCurrent()->SetUseFlushUITasks(true);
}

void ScrollableAxisTestNg::TearDownTestSuite()
{
    MockPipelineContext::TearDown();
    MockContainer::TearDown();
}

void ScrollableAxisTestNg::SetUp() {}

void ScrollableAxisTestNg::TearDown() {}

RefPtr<Scrollable> ScrollableAxisTestNg::GetScrollable(RefPtr<FrameNode> node)
{
    CHECK_NULL_RETURN(node, nullptr);
    auto pattern = node->GetPattern<ScrollablePattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    CHECK_NULL_RETURN(pattern->scrollableEvent_, nullptr);
    return pattern->scrollableEvent_->scrollable_;
}

void ScrollableAxisTestNg::DragStart(RefPtr<Scrollable> scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->HandleTouchDown();
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    (*(scrollable->panRecognizerNG_->onActionStart_))(info);
}

void ScrollableAxisTestNg::DragUpdate(RefPtr<Scrollable> scrollable, float offset)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(offset);
    info.SetInputEventType(InputEventType::AXIS);
    (*(scrollable->panRecognizerNG_->onActionUpdate_))(info);
}

void ScrollableAxisTestNg::DragEnd(RefPtr<Scrollable> scrollable, float velocity)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainVelocity(velocity);
    info.SetInputEventType(InputEventType::AXIS);
    (*(scrollable->panRecognizerNG_->onActionEnd_))(info);
    scrollable->HandleTouchUp();
}

/**
 * @tc.name: AxisDragTest001
 * @tc.desc: test the drag event by mouse wheel.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableAxisTestNg, AxisDragTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List.
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

    /**
     * @tc.steps: step2. trigger the drag event.
     * @tc.expected: the position of axisAnimator is correct.
     */
    auto scrollable = GetScrollable(listNode);
    ASSERT_NE(scrollable, nullptr);
    scrollable->context_ = PipelineContext::GetCurrentContext();
    auto context = scrollable->context_.Upgrade();
    ASSERT_NE(context, nullptr);
    auto eventHub = listNode->GetEventHub<ListEventHub>();
    auto startEventTrigger = false;
    eventHub->SetOnScrollStart([&startEventTrigger]() { startEventTrigger = true; });
    DragStart(scrollable);
    ASSERT_NE(scrollable->axisAnimator_, nullptr);
    auto axisScrollMotion = scrollable->axisAnimator_->axisScrollMotion_;
    ASSERT_NE(axisScrollMotion, nullptr);
    EXPECT_FALSE(startEventTrigger);
    EXPECT_FLOAT_EQ(axisScrollMotion->currentPos_, 0.f);

    context->SetVsyncTime(1);
    DragUpdate(scrollable, -100.f);
    ASSERT_NE(scrollable->axisAnimator_->axisScrollAnimator_, nullptr);
    EXPECT_TRUE(startEventTrigger);
    auto startPos = axisScrollMotion->startPos_;
    EXPECT_FLOAT_EQ(startPos, 0.f);
    auto finalPos = axisScrollMotion->finalPos_;
    EXPECT_FLOAT_EQ(finalPos, startPos - 100.f);

    context->SetVsyncTime(2);
    auto lastFinalPos = finalPos;
    DragUpdate(scrollable, -620.f);
    startPos = axisScrollMotion->startPos_;
    EXPECT_FLOAT_EQ(startPos, -100.f);
    finalPos = axisScrollMotion->finalPos_;
    EXPECT_FLOAT_EQ(finalPos, lastFinalPos - 620.f);
    auto distance = axisScrollMotion->distance_;
    auto currentPos = axisScrollMotion->currentPos_;
    EXPECT_FLOAT_EQ(distance, finalPos - currentPos);

    DragEnd(scrollable, -500.f);
    EXPECT_FLOAT_EQ(scrollable->lastGestureVelocity_, 0.f);
}
} // namespace OHOS::Ace::NG
