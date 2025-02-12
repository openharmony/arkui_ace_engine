/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

void ScrollableAxisTestNg::AxisDragStart(RefPtr<Scrollable> scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->HandleTouchDown();
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetInputEventType(InputEventType::AXIS);
    (*(scrollable->panRecognizerNG_->onActionStart_))(info);
}

void ScrollableAxisTestNg::AxisDragUpdate(RefPtr<Scrollable> scrollable, float offset)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(offset);
    info.SetInputEventType(InputEventType::AXIS);
    (*(scrollable->panRecognizerNG_->onActionUpdate_))(info);
}

void ScrollableAxisTestNg::AxisDragEnd(RefPtr<Scrollable> scrollable, float velocity)
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

void ScrollableAxisTestNg::DragStart(RefPtr<Scrollable> scrollable)
{
    CHECK_NULL_VOID(scrollable);
    scrollable->HandleTouchDown();
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    (*(scrollable->panRecognizerNG_->onActionStart_))(info);
}

void ScrollableAxisTestNg::DragUpdate(RefPtr<Scrollable> scrollable, float offset)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(offset);
    (*(scrollable->panRecognizerNG_->onActionUpdate_))(info);
}

void ScrollableAxisTestNg::DragEnd(RefPtr<Scrollable> scrollable, float velocity, double mainDelta)
{
    CHECK_NULL_VOID(scrollable);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_);
    CHECK_NULL_VOID(scrollable->panRecognizerNG_->onActionStart_);
    GestureEvent info = GestureEvent();
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(velocity);
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
     * @tc.steps: step2. Trigger the drag event.
     * @tc.expected: The position of axisAnimator is correct.
     */
    auto scrollable = GetScrollable(listNode);
    scrollable->InitAxisAnimator();
    ASSERT_NE(scrollable, nullptr);
    scrollable->context_ = PipelineContext::GetCurrentContext();
    auto context = scrollable->context_.Upgrade();
    ASSERT_NE(context, nullptr);
    auto eventHub = listNode->GetEventHub<ListEventHub>();
    auto startEventTrigger = false;
    eventHub->SetOnScrollStart([&startEventTrigger]() { startEventTrigger = true; });
    AxisDragStart(scrollable);
    ASSERT_NE(scrollable->axisAnimator_, nullptr);
    auto axisScrollMotion = scrollable->axisAnimator_->axisScrollMotion_;
    ASSERT_NE(axisScrollMotion, nullptr);
    EXPECT_FALSE(startEventTrigger);
    EXPECT_FLOAT_EQ(axisScrollMotion->currentPos_, 0.f);

    context->SetVsyncTime(1);
    AxisDragUpdate(scrollable, -100.f);
    ASSERT_NE(scrollable->axisAnimator_->axisScrollAnimator_, nullptr);
    EXPECT_TRUE(startEventTrigger);
    auto startPos = axisScrollMotion->startPos_;
    EXPECT_FLOAT_EQ(startPos, 0.f);
    auto finalPos = axisScrollMotion->finalPos_;
    EXPECT_FLOAT_EQ(finalPos, startPos - 100.f);

    context->SetVsyncTime(2);
    auto lastFinalPos = finalPos;
    AxisDragUpdate(scrollable, -620.f);
    startPos = axisScrollMotion->startPos_;
    EXPECT_FLOAT_EQ(startPos, -100.f);
    finalPos = axisScrollMotion->finalPos_;
    EXPECT_FLOAT_EQ(finalPos, lastFinalPos - 620.f);
    auto distance = axisScrollMotion->distance_;
    auto currentPos = axisScrollMotion->currentPos_;
    EXPECT_FLOAT_EQ(distance, finalPos - currentPos);

    AxisDragEnd(scrollable, -500.f);
    EXPECT_FLOAT_EQ(scrollable->lastGestureVelocity_, 0.f);
}

/**
 * @tc.name: AxisAnimatorTest002
 * @tc.desc: test the interception of the axis drag event by the vsync time.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableAxisTestNg, AxisDragTest002, TestSize.Level1)
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
    ASSERT_NE(listNode, nullptr);
    auto listLayoutProperty = listNode->GetLayoutProperty<ListLayoutProperty>();
    ASSERT_NE(listLayoutProperty, nullptr);
    auto listPattern = listNode->GetPattern<ListPattern>();
    ASSERT_NE(listPattern, nullptr);

    /**
     * @tc.steps: step2. Trigger the drag start event.
     * @tc.expected: The position of axisAnimator is correct.
     */
    auto scrollable = GetScrollable(listNode);
    ASSERT_NE(scrollable, nullptr);
    scrollable->InitAxisAnimator();
    scrollable->context_ = PipelineContext::GetCurrentContext();
    auto context = scrollable->context_.Upgrade();
    ASSERT_NE(context, nullptr);
    AxisDragStart(scrollable);
    ASSERT_NE(scrollable->axisAnimator_, nullptr);
    auto axisScrollMotion = scrollable->axisAnimator_->axisScrollMotion_;
    ASSERT_NE(axisScrollMotion, nullptr);
    EXPECT_FLOAT_EQ(axisScrollMotion->currentPos_, 0.f);

    /**
     * @tc.steps: step3. Modify the vysnc time and trigger the drag update event.
     * @tc.expected: The drag update event can be executed and the lastAxisVsyncTime_ is correct.
     */
    EXPECT_EQ(scrollable->lastAxisVsyncTime_, 0);
    context->SetVsyncTime(1);
    AxisDragUpdate(scrollable, -100.f);
    ASSERT_NE(scrollable->axisAnimator_->axisScrollAnimator_, nullptr);
    EXPECT_EQ(scrollable->lastAxisVsyncTime_, 1);
    context->SetVsyncTime(2);
    AxisDragUpdate(scrollable, -100.f);
    EXPECT_EQ(scrollable->lastAxisVsyncTime_, 2);

    /**
     * @tc.steps: step4. Modify the ScrollSnapAlign of list and the vysnc time.
     * @tc.expected: The drag update event can be executed and the lastAxisVsyncTime_ is correct.
     */
    listLayoutProperty->UpdateScrollSnapAlign(ScrollSnapAlign::START);
    EXPECT_EQ(scrollable->GetSnapType(), SnapType::LIST_SNAP);
    context->SetVsyncTime(2);
    AxisDragUpdate(scrollable, -100.f);
    EXPECT_EQ(scrollable->lastAxisVsyncTime_, 2);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::NONE);
    context->SetVsyncTime(3);
    AxisDragUpdate(scrollable, -100.f);
    EXPECT_EQ(scrollable->lastAxisVsyncTime_, 3);
    EXPECT_EQ(scrollable->snapDirection_, SnapDirection::BACKWARD);
}

/**
 * @tc.name: DragEnd001
 * @tc.desc: Test the lastMainDelta_ of DragEnd
 * @tc.type: FUNC
 */
HWTEST_F(ScrollableAxisTestNg, DragEnd001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create List.
     * @tc.expected: Create List successfully.
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
    auto scrollable = GetScrollable(listNode);
    ASSERT_NE(scrollable, nullptr);
    EXPECT_EQ(scrollable->lastMainDelta_, 0.0);

    /**
     * @tc.steps: step2. Trigger the drag update event.
     * @tc.expected: The lastMainDelta_ of scrollable is correct.
     */
    DragUpdate(scrollable, 100.0);
    EXPECT_EQ(scrollable->lastMainDelta_, 100.0);
    auto lastMainDelta = scrollable->lastMainDelta_;

    /**
     * @tc.steps: step3. Trigger the drag end event.
     * @tc.expected: The lastMainDelta_ of scrollable has not changed.
     */
    DragEnd(scrollable, 50.0);
    EXPECT_EQ(scrollable->lastMainDelta_, lastMainDelta);
    lastMainDelta = scrollable->lastMainDelta_;

    /**
     * @tc.steps: step4. Trigger the drag end event again.
     * @tc.expected: the lastMainDelta_ of scrollable has changed.
     */
    DragEnd(scrollable, 50, 200.0);
    EXPECT_NE(scrollable->lastMainDelta_, lastMainDelta);
    EXPECT_EQ(scrollable->lastMainDelta_, 200.0);
}
} // namespace OHOS::Ace::NG
