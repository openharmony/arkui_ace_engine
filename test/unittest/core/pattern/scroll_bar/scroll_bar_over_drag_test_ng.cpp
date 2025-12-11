/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "scroll_bar_test_ng.h"
#include "test/mock/core/common/mock_container.h"
#include "test/mock/core/pipeline/mock_pipeline_context.h"

#include "core/components_ng/pattern/scroll/scroll_edge_effect.h"
#include "core/components_ng/pattern/scroll/scroll_model_ng.h"
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float MAIN_DELTA = 10.0f;
constexpr float MAIN_VELOCITY = 10000.0f;
constexpr int32_t TICK = 2;
constexpr float SCROLLABLE_DISTANCE = CONTENT_MAIN_SIZE - SCROLL_HEIGHT;
constexpr uint64_t TIME_1 = 1000 * 1000 * 1;
constexpr uint64_t TIME_2 = 1000 * 1000 * 2 + 1;
} // namespace
class MockScrollSpringEffect : public ScrollEdgeEffect {
public:
    MockScrollSpringEffect() : ScrollEdgeEffect(EdgeEffect::SPRING) {}
    MOCK_METHOD(void, ProcessScrollOver, (double), (override));
};
class ScrollBarOverDragTestNg : public ScrollBarTestNg {
public:
    void InitScrollBar();
    void InitScrollBarWithChild();
    void InitNestedScrollWithChild(bool isNestedScroll = false, NestedScrollOptions nestedOpt = {},
        Axis axis = Axis::VERTICAL, bool scrollBarHasChild = true);

private:
    RefPtr<FrameNode> parentScrollNode_;
    RefPtr<ScrollPattern> parentScrollPattern_;
};

void ScrollBarOverDragTestNg::InitScrollBar()
{
    CreateStack();
    CreateScroll();
    ScrollModelNG::SetEdgeEffect(AceType::RawPtr(scrollNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);
    scrollPattern_->OnModifyDone();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();
    auto currentContext = PipelineContext::GetCurrentContext();
    frameNode_->context_ = AceType::RawPtr(currentContext);
}

void ScrollBarOverDragTestNg::InitScrollBarWithChild()
{
    CreateStack();
    CreateScroll();
    ScrollModelNG::SetEdgeEffect(AceType::RawPtr(scrollNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);
    scrollPattern_->OnModifyDone();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    auto currentContext = PipelineContext::GetCurrentContext();
    frameNode_->context_ = AceType::RawPtr(currentContext);
}

void ScrollBarOverDragTestNg::InitNestedScrollWithChild(
    bool isNestedScroll, NestedScrollOptions nestedOpt, Axis axis, bool scrollBarHasChild)
{
    CreateStack();
    ScrollModelNG model;
    model.Create();
    auto scrollBarProxy = model.CreateScrollBarProxy();
    model.SetAxis(axis);
    model.SetDisplayMode(static_cast<int>(DisplayMode::OFF));
    model.SetScrollBarProxy(scrollBarProxy);
    ViewAbstract::SetWidth(CalcLength(FILL_LENGTH));
    ViewAbstract::SetHeight(CalcLength(FILL_LENGTH));
    parentScrollNode_ = CreateMainFrameNode();
    parentScrollPattern_ = parentScrollNode_->GetPattern<ScrollPattern>();
    ScrollModelNG::SetEdgeEffect(AceType::RawPtr(parentScrollNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);

    CreateStack();
    CreateScroll();
    ScrollModelNG::SetEdgeEffect(AceType::RawPtr(scrollNode_), EdgeEffect::SPRING, true, EffectEdge::ALL);
    ScrollModelNG::SetNestedScroll(AceType::RawPtr(scrollNode_), nestedOpt);
    scrollPattern_->OnModifyDone();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    ScrollBarModelNG::SetEnableNestedScroll(AceType::RawPtr(frameNode_), isNestedScroll);
    if (scrollBarHasChild) {
        CreateScrollBarChild();
    }
    CreateDone();
    auto currentContext = PipelineContext::GetCurrentContext();
    frameNode_->context_ = AceType::RawPtr(currentContext);
}

/**
 * @tc.name: OverDragTest001
 * @tc.desc: Dragging the finger upwards and crossing the boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, OverDragTest001, TestSize.Level1)
{
    InitScrollBarWithChild();

    GestureEvent info;
    info.SetMainDelta(-MAIN_DELTA);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);

    pattern_->HandleDragEnd(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
}

/**
 * @tc.name: OverDragTest002
 * @tc.desc: Dragging downwards quickly and crossing the boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, OverDragTest002, TestSize.Level1)
{
    InitScrollBarWithChild();

    float ratio = pattern_->GetControlDistance() / pattern_->GetScrollableDistance();
    GestureEvent info;
    info.SetMainVelocity(MAIN_VELOCITY);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    /**
     * @tc.steps: step1. Drag middle.
     */
    info.SetMainDelta(MAIN_DELTA);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), -MAIN_DELTA * ratio);
    /**
     * @tc.steps: step2. Drag over boundary.
     */
    info.SetMainDelta(SCROLL_HEIGHT);

    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), -SCROLLABLE_DISTANCE);

    pattern_->HandleDragEnd(info);
}

/**
 * @tc.name: OverDragTest003
 * @tc.desc: Throwing and sliding fingers downwards across the boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, OverDragTest003, TestSize.Level1)
{
    InitScrollBarWithChild();
    auto mockScrollSpringEffect = AceType::MakeRefPtr<MockScrollSpringEffect>();
    scrollPattern_->scrollEffect_ = mockScrollSpringEffect;
    EXPECT_CALL(*mockScrollSpringEffect, ProcessScrollOver(_)).Times(1);

    float ratio = pattern_->GetControlDistance() / pattern_->GetScrollableDistance();
    GestureEvent info;
    info.SetMainDelta(MAIN_DELTA + MAIN_DELTA);
    info.SetMainVelocity(MAIN_VELOCITY);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    PipelineContext::GetCurrentContext()->SetVsyncTime(TIME_1);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), -(MAIN_DELTA + MAIN_DELTA) * ratio);

    PipelineContext::GetCurrentContext()->SetVsyncTime(TIME_2);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().SetTicks(TICK);
    pattern_->HandleDragEnd(info);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->frictionMotion_->NotifyListener(MAIN_DELTA);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
}

/**
 * @tc.name: NestedScrollOverDragTest001
 * @tc.desc: Dragging the finger upwards and crossing the boundary when mode is SELF_ONLY.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, NestedScrollOverDragTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize not nested scroll with child. Mode is SELF_ONLY.
     */
    InitNestedScrollWithChild();
    
    GestureEvent info;
    info.SetMainDelta(-MAIN_DELTA);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);

    pattern_->HandleDragEnd(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);

    /**
     * @tc.steps: step2. Set enable nested scroll.
     */
    ScrollBarModelNG::SetEnableNestedScroll(AceType::RawPtr(frameNode_), true);
    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);

    pattern_->HandleDragEnd(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);
}

/**
 * @tc.name: NestedScrollOverDragTest002
 * @tc.desc: Dragging the finger upwards and crossing the boundary when mode is SELF_FIRST.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, NestedScrollOverDragTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize not nested scroll with child. Mode is SELF_FIRST.
     */
    InitNestedScrollWithChild(
        false, { .forward = NestedScrollMode::SELF_FIRST, .backward = NestedScrollMode::SELF_FIRST });

    GestureEvent info;
    info.SetMainDelta(-MAIN_DELTA);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);

    pattern_->HandleDragEnd(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);

    /**
     * @tc.steps: step2. Set enable nested scroll.
     */
    ScrollBarModelNG::SetEnableNestedScroll(AceType::RawPtr(frameNode_), true);
    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), MAIN_DELTA);

    pattern_->HandleDragEnd(info);
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), .0f);
    EXPECT_EQ(parentScrollPattern_->GetCurrentPosition(), .0f);
}

/**
 * @tc.name: CheckRestartSpringTest001
 * @tc.desc: Dragging the finger downwards and crossing the boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, CheckRestartSpringTest001, TestSize.Level1)
{
    auto container = AceType::DynamicCast<Container>(MockContainer::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY_THREE);
    InitScrollBar();
    auto mockScrollSpringEffect = AceType::MakeRefPtr<MockScrollSpringEffect>();
    scrollPattern_->scrollEffect_ = mockScrollSpringEffect;
    EXPECT_CALL(*mockScrollSpringEffect, ProcessScrollOver(_)).Times(0);

    GestureEvent info;
    info.SetMainDelta(-MAIN_DELTA);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->scrollBar_->HandleDragStart(info);
    pattern_->scrollBar_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);

    scrollPattern_->CheckRestartSpring(false);
}

/**
 * @tc.name: CheckRestartSpringTest002
 * @tc.desc: Dragging the finger downwards and crossing the boundary.
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarOverDragTestNg, CheckRestartSpringTest002, TestSize.Level1)
{
    auto container = AceType::DynamicCast<Container>(MockContainer::Current());
    ASSERT_NE(container, nullptr);
    container->SetApiTargetVersion((int32_t)PlatformVersion::VERSION_TWENTY_THREE);
    InitScrollBarWithChild();
    auto mockScrollSpringEffect = AceType::MakeRefPtr<MockScrollSpringEffect>();
    scrollPattern_->scrollEffect_ = mockScrollSpringEffect;
    EXPECT_CALL(*mockScrollSpringEffect, ProcessScrollOver(_)).Times(0);

    GestureEvent info;
    info.SetMainDelta(-MAIN_DELTA);
    info.SetInputEventType(InputEventType::TOUCH_SCREEN);

    pattern_->HandleDragStart(info);
    pattern_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetCurrentPosition(), MAIN_DELTA);
    scrollPattern_->CheckRestartSpring(false);

    pattern_->isTouchScreen_ = false;
    pattern_->frictionController_ = AceType::MakeRefPtr<Animator>("test");
    EXPECT_TRUE(scrollPattern_->ScrollBarIdle());
}
} // namespace OHOS::Ace::NG
