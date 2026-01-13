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

#include "swiper_test_ng.h"
#include "test/mock/core/pattern/mock_nestable_scroll_container.h"

#include "core/components_ng/pattern/swiper/swiper_change_event.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float DRAG_DELTA = 400.0f;
} // namespace

class SwiperEventTestTwoNg : public SwiperTestNg {
public:
    void HandleDrag(GestureEvent info);
    void HandleDragStart(GestureEvent info);
    void HandleDragUpdate(GestureEvent info);
    void HandleDragEnd(GestureEvent info);
    void HandleDragCancel();
    GestureEvent CreateDragInfo(bool moveDirection);
};

void SwiperEventTestTwoNg::HandleDrag(GestureEvent info)
{
    HandleDragStart(info);
    HandleDragUpdate(info);
    HandleDragEnd(info);
}

void SwiperEventTestTwoNg::HandleDragStart(GestureEvent info)
{
    pattern_->panEvent_->GetActionStartEventFunc()(info);
}

void SwiperEventTestTwoNg::HandleDragUpdate(GestureEvent info)
{
    pattern_->panEvent_->GetActionUpdateEventFunc()(info);
    FlushUITasks();
}

void SwiperEventTestTwoNg::HandleDragEnd(GestureEvent info)
{
    pattern_->panEvent_->GetActionEndEventFunc()(info);
    FlushUITasks();
}

void SwiperEventTestTwoNg::HandleDragCancel()
{
    pattern_->panEvent_->GetActionCancelEventFunc()();
    FlushUITasks();
}

GestureEvent SwiperEventTestTwoNg::CreateDragInfo(bool moveDirection)
{
    int32_t invert = AceApplicationInfo::GetInstance().IsRightToLeft() ? -1 : 1;
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::TOUCHPAD);
    info.SetGlobalLocation(Offset(100.f, 100.f));
    info.SetMainDelta(invert * (moveDirection ? -DRAG_DELTA : DRAG_DELTA));
    info.SetMainVelocity(invert * (moveDirection ? -2000.f : 2000.f));
    return info;
}

/**
 * @tc.name: OnScrollStartEnd001
 * @tc.desc: test OnScrollStartRecursive/OnScrollEndRecursive
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnScrollStartEnd001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);
    EXPECT_CALL(*mockScroll, OnScrollStartRecursive).Times(1);
    EXPECT_CALL(*mockScroll, GetAxis).Times(1).WillOnce(Return(Axis::HORIZONTAL));
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->isDragging_ = false;
    pattern_->currentIndex_ = 3;
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    /**
     * @tc.steps: step1. Scroll start
     */
    pattern_->OnScrollStartRecursive(pattern_, 5.0f, 0.0f);
    EXPECT_TRUE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 3);

    /**
     * @tc.steps: step2. Scroll end
     */
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(1);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);

    /**
     * @tc.steps: step3. Scroll end when AnimationRunning
     * @tc.expected: Can not HandleDragEnd
     */
    pattern_->targetIndex_ = 1;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);
}

/**
 * @tc.name: OnScrollStartEnd002
 * @tc.desc: test OnScrollStartRecursive/OnScrollEndRecursive when DisableSwipe
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnScrollStartEnd002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisableSwipe(true);
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::NONE);
    CreateSwiperItems();
    CreateSwiperDone();
    auto mockScroll = AceType::MakeRefPtr<MockNestableScrollContainer>();
    auto mockScrollNode = FrameNode::CreateFrameNode("MockScroll", -1, mockScroll);
    frameNode_->MountToParent(mockScrollNode);
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_FIRST,
        .backward = NestedScrollMode::SELF_FIRST,
    };
    pattern_->SetNestedScroll(nestedOpt);
    pattern_->isDragging_ = false;
    pattern_->currentIndex_ = 3;
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    /**
     * @tc.steps: step1. Scroll start
     * @tc.expected: Can not start because of DisableSwipe
     */
    pattern_->OnScrollStartRecursive(pattern_, 5.0f, 0.0f);
    EXPECT_FALSE(pattern_->childScrolling_);
    EXPECT_EQ(pattern_->gestureSwipeIndex_, 0);

    /**
     * @tc.steps: step2. Scroll end
     */
    EXPECT_CALL(*mockScroll, OnScrollEndRecursive).Times(0);
    EXPECT_CALL(*mockScroll, HandleScrollVelocity).Times(0);
    pattern_->parent_ = mockScroll;
    pattern_->OnScrollEndRecursive(std::nullopt);
    EXPECT_FALSE(pattern_->childScrolling_);
}

/**
 * @tc.name: OnChange001
 * @tc.desc: Test OnChange event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnChange001, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onChange = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnChange(std::move(onChange));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNext();
    EXPECT_EQ(currentIndex, 1);

    /**
     * @tc.steps: step2. Show previous page
     * @tc.expected: currentIndex change to 0
     */
    ShowPrevious();
    EXPECT_EQ(currentIndex, 0);
}

/**
 * @tc.name: OnAnimation001
 * @tc.desc: Test OnAnimationStart OnAnimationEnd event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnAnimation001, TestSize.Level1)
{
    bool isAnimationStart = false;
    auto onAnimationStart = [&isAnimationStart](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        isAnimationStart = true;
    };
    bool isAnimationEnd = false;
    auto onAnimationEnd = [&isAnimationEnd](
                              int32_t index, const AnimationCallbackInfo& info) { isAnimationEnd = true; };
    SwiperModelNG model = CreateSwiper();
    model.SetOnAnimationStart(std::move(onAnimationStart));
    model.SetOnAnimationEnd(std::move(onAnimationEnd));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: Animation event will be called
     */
    ShowNext();
    EXPECT_TRUE(isAnimationStart);
    EXPECT_TRUE(isAnimationEnd);
}

/**
 * @tc.name: UpdateSwiperPanEvent001
 * @tc.desc: Test UpdateSwiperPanEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, UpdateSwiperPanEvent001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. DisableSwipe default is false
     * @tc.expected: Has panEvent_
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_FALSE(pattern_->IsDisableSwipe());
    EXPECT_NE(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step2. Set DisableSwip to true
     * @tc.expected: Has no panEvent_
     */
    layoutProperty_->UpdateDisableSwipe(true);
    frameNode_->MarkModifyDone();
    EXPECT_EQ(pattern_->panEvent_, nullptr);

    /**
     * @tc.steps: step3. When is dragging
     * @tc.expected: Stop dragging
     */
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    GestureEvent info = CreateDragInfo(true);
    HandleDragStart(info);
    EXPECT_TRUE(pattern_->isTouchDown_);
    layoutProperty_->UpdateDisableSwipe(true);
    frameNode_->MarkModifyDone();
    EXPECT_FALSE(pattern_->isTouchDown_);
}

/**
 * @tc.name: MouseAxisEventWithPageFlipMode001
 * @tc.desc: PageFlipMode property test with CONTINUOUS mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, AttrPageFlipModeTest001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    // default mode is PageFlipMode::CONTINUOUS(0)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 0);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-10.f);
    auto panEvent = frameNode_->GetEventHub<EventHub>()
        ->gestureEventHub_->panEventActuator_->panEvents_.front();
    panEvent->actionStart_(info);
    EXPECT_TRUE(pattern_->isFirstAxisAction_);
    panEvent->actionUpdate_(info);
    EXPECT_FALSE(pattern_->isFirstAxisAction_);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    pattern_->propertyAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 2);
}

/**
 * @tc.name: MouseAxisEventWithPageFlipMode002
 * @tc.desc: PageFlipMode property test with SINGLE mode
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, AttrPageFlipModeTest002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetPageFlipMode(1);
    CreateSwiperItems();
    CreateSwiperDone();
    // mode is PageFlipMode::SINGLE(1)
    EXPECT_EQ(pattern_->GetPageFlipMode(), 1);
    GestureEvent info;
    info.SetInputEventType(InputEventType::AXIS);
    info.SetSourceTool(SourceTool::MOUSE);
    info.SetMainDelta(-10.f);
    auto panEvent = frameNode_->GetEventHub<EventHub>()
        ->gestureEventHub_->panEventActuator_->panEvents_.front();
    panEvent->actionStart_(info);
    EXPECT_TRUE(pattern_->isFirstAxisAction_);
    // axis update event will flip page, and isFirstAxisAction_ will be marked
    panEvent->actionUpdate_(info);
    EXPECT_FALSE(pattern_->isFirstAxisAction_);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    // propertyAnimation running will block page flipping
    pattern_->propertyAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    // frameAnimation running will block page flipping
    pattern_->propertyAnimationIsRunning_ = false;
    pattern_->translateAnimationIsRunning_ = true;
    panEvent->actionUpdate_(info);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: OnUnselected001
 * @tc.desc: Test OnUnselected event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnUnselected001, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onUnselected = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnUnselected(std::move(onUnselected));
    CreateSwiperItems(6);
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNext();
    EXPECT_EQ(currentIndex, 0);
    ShowNext();
    EXPECT_EQ(currentIndex, 1);
    /**
     * @tc.steps: step2. Set the two parameter values of the FireSelecteEvent method to be the same
     * @tc.expected: The value of unselectedIndex_ is 2
     */
    pattern_->unselectedIndex_ = 2;
    pattern_->FireUnselectedEvent(3, 3);
    EXPECT_EQ(pattern_->unselectedIndex_, 2);

    /**
     * @tc.steps: step3. Set the two parameter values of the FireSelecteEvent method to be different
     * @tc.expected: The value of selectedIndex_ is 3
     */
    pattern_->FireUnselectedEvent(3, 4);
    EXPECT_EQ(pattern_->unselectedIndex_, 3);
}

/**
 * @tc.name: onScrollStateChanged001
 * @tc.desc: Test onScrollStateChanged event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, onScrollStateChanged001, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onScrollStateChanged = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnScrollStateChanged(std::move(onScrollStateChanged));
    CreateSwiperItems(6);
    CreateSwiperDone();

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(-20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->scrollState_, ScrollState::SCROLL);

    info.SetMainVelocity(-1000.0f);
    info.SetMainDelta(0.0f);
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->scrollState_, ScrollState::IDLE);
}

/**
 * @tc.name: onScrollStateChanged002
 * @tc.desc: Test onScrollStateChanged event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, onScrollStateChanged002, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onScrollStateChanged = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnScrollStateChanged(std::move(onScrollStateChanged));
    CreateSwiperItems(6);
    CreateSwiperDone();

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(-20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->scrollState_, ScrollState::SCROLL);

    info.SetMainDelta(0.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->scrollState_, ScrollState::SCROLL);

    HandleDragEnd(info);
    EXPECT_EQ(pattern_->scrollState_, ScrollState::IDLE);
}

/**
 * @tc.name: MarginIgnoreBlankDragTest001
 * @tc.desc: Test Swiper IgnoreBlank with drag. When totalcount equal to displaycount, ignoreBlankOffset_ will be 0.f.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, MarginIgnoreBlankDragTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop false, totalcount equal to displaycount.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetPreviousMargin(Dimension(PRE_MARGIN), true);
    model.SetNextMargin(Dimension(0.f), true);
    model.SetDisplayCount(4);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);

    /**
     * @tc.steps: step2. drag over end.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);

    info.SetMainDelta(-SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);

    /**
     * @tc.steps: step3. drag over start.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    info.SetMainDelta(SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);
}

/**
 * @tc.name: MarginIgnoreBlankDragTest002
 * @tc.desc: Test Swiper IgnoreBlank with drag.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, MarginIgnoreBlankDragTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. CreateWith SetLoop false, index = 1.
     * @tc.expected: ignoreBlankOffset_ will be NEXT_MARGIN.
     */
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetNextMargin(Dimension(NEXT_MARGIN), true);
    model.SetDisplayCount(3);
    model.SetIndex(1);
    CreateSwiperItems();
    CreateSwiperDone();
    EXPECT_EQ(pattern_->ignoreBlankOffset_, NEXT_MARGIN);

    /**
     * @tc.steps: step2. drag over start.
     * @tc.expected: ignoreBlankOffset_ will be 0.f.
     */
    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(SWIPER_WIDTH);
    HandleDrag(info);
    EXPECT_EQ(pattern_->ignoreBlankOffset_, 0.f);
}

/**
 * @tc.name: OnContentWillScroll001
 * @tc.desc: Test Swiper onContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnContentWillScroll001, TestSize.Level1)
{
    auto onContentWillScroll = [](const SwiperContentWillScrollResult& result) {
        if (result.currentIndex == 0 && result.comingIndex == 1) {
            return false;
        }
        return true;
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnContentWillScroll(std::move(onContentWillScroll));
    model.SetIndex(0);
    CreateSwiperItems();
    CreateSwiperDone();

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(-20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_.begin()->first, 0);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);

    info.SetMainDelta(20.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 20.0f);
}

/**
 * @tc.name: OnContentWillScroll002
 * @tc.desc: Test Swiper onContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnContentWillScroll002, TestSize.Level1)
{
    auto onContentWillScroll = [](const SwiperContentWillScrollResult& result) {
        if (result.currentIndex == 0 && result.comingIndex == 1) {
            return false;
        }
        return true;
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnContentWillScroll(std::move(onContentWillScroll));
    model.SetIndex(0);
    CreateSwiperItems();
    CreateSwiperDone();

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 20.0f);

    info.SetMainDelta(-20.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 20.0f);

    info.SetMainDelta(20.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 40.0f);

    info.SetMainVelocity(-1000.0f);
    info.SetMainDelta(0.0f);
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->itemPosition_.begin()->first, 0);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);

    info.SetMainVelocity(0.0f);
    info.SetMainDelta(300.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 300.0f);

    info.SetMainVelocity(-1000.0f);
    info.SetMainDelta(0.0f);
    HandleDragEnd(info);
    EXPECT_EQ(pattern_->itemPosition_.begin()->first, -1);
    EXPECT_EQ(pattern_->itemPosition_[-1].startPos, 0.0f);
}

/**
 * @tc.name: OnContentWillScroll003
 * @tc.desc: Test Swiper onContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnContentWillScroll003, TestSize.Level1)
{
    auto onContentWillScroll = [](const SwiperContentWillScrollResult& result) {
        if (result.currentIndex == 0 && result.comingIndex == 2) {
            return false;
        }
        return true;
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnContentWillScroll(std::move(onContentWillScroll));
    model.SetIndex(0);
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(5);
    CreateSwiperDone();

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(-20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_.begin()->first, 0);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);

    info.SetMainDelta(20.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 20.0f);

    pattern_->ChangeIndex(4, false);
    FlushUITasks();
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(100.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[4].startPos, 100.0f);
}

/**
 * @tc.name: OnContentWillScroll004
 * @tc.desc: Test Swiper onContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnContentWillScroll004, TestSize.Level1)
{
    auto onContentWillScroll = [](const SwiperContentWillScrollResult& result) {
        if (result.currentIndex == 0 && result.comingIndex == 3) {
            return false;
        }
        return true;
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnContentWillScroll(std::move(onContentWillScroll));
    model.SetIndex(0);
    CreateSwiperItems();
    CreateSwiperDone();

    layoutProperty_->UpdateLayoutDirection(TextDirection::RTL);

    GestureEvent info = CreateDragInfo(true);
    info.SetMainVelocity(0);
    info.SetGlobalLocation(Offset(0.f, 0.f));
    info.SetMainDelta(-20.0f);
    HandleDragStart(info);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_.begin()->first, 0);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, 0.0f);

    info.SetMainDelta(20.0f);
    HandleDragUpdate(info);
    EXPECT_EQ(pattern_->itemPosition_[0].startPos, -20.0f);
}

/**
 * @tc.name: OnContentWillScroll005
 * @tc.desc: Test Swiper onContentWillScroll
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnContentWillScroll005, TestSize.Level1)
{
    auto onContentWillScroll = [](const SwiperContentWillScrollResult& result) {
        if (result.currentIndex == 0 && result.comingIndex == 2) {
            return false;
        }
        return true;
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnContentWillScroll(std::move(onContentWillScroll));
    model.SetIndex(0);
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    model.SetPreviousMargin(Dimension(50.0_px), false);
    model.SetNextMargin(Dimension(50.0_px), false);
    model.SetItemSpace(Dimension(40.0_px));
    CreateSwiperItems(10);
    CreateSwiperDone();

    pattern_->ShowNext(true);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_[1].startPos, 170.0f);

    pattern_->ShowPrevious(true);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_[-2].endPos, 130.0f);
}

/**
 * @tc.name: OnSelected001
 * @tc.desc: Test OnSelected event
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnSelected001, TestSize.Level1)
{
    int32_t currentIndex = 0;
    auto onSelected = [&currentIndex](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        currentIndex = swiperInfo->GetIndex();
    };
    SwiperModelNG model = CreateSwiper();
    model.SetOnSelected(std::move(onSelected));
    CreateSwiperItems(6);
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Show next page
     * @tc.expected: currentIndex change to 1
     */
    ShowNext();
    EXPECT_EQ(currentIndex, 1);
}

/**
 * @tc.name: FireSelectedEvent001
 * @tc.desc: Test FireSelectedEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, FireSelectedEvent001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetOnSelected(std::move(nullptr));
    CreateSwiperItems(6);
    CreateSwiperDone();

    /**
     * @tc.steps: step1. Set the two parameter values of the FireSelecteEvent method to be the same
     * @tc.expected: The value of selectedIndex_ is 2
     */
    pattern_->selectedIndex_ = 2;
    pattern_->FireSelectedEvent(3, 3);
    EXPECT_EQ(pattern_->selectedIndex_, 2);

    /**
     * @tc.steps: step2. Set the two parameter values of the FireSelecteEvent method to be different
     * @tc.expected: The value of selectedIndex_ is 4
     */
    pattern_->FireSelectedEvent(3, 4);
    EXPECT_EQ(pattern_->selectedIndex_, 4);
}

/**
 * @tc.name: FireSelectedEvent002
 * @tc.desc: Test FireSelectedEvent
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, FireSelectedEvent002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetOnSelected(std::move(nullptr));
    CreateSwiperItems(6);
    CreateSwiperDone();

    pattern_->selectedIndex_ = 2;
    pattern_->jumpOnChange_ = true;
    pattern_->FireSelectedEvent(3, 4);
    EXPECT_EQ(pattern_->selectedIndex_, 2);

    pattern_->jumpOnChange_ = false;
    pattern_->FireSelectedEvent(3, 4);
    EXPECT_EQ(pattern_->selectedIndex_, 4);

    pattern_->fastAnimationRunning_ = false;
    pattern_->FireSelectedEvent(3, 3);
    EXPECT_EQ(pattern_->selectedIndex_, 4);

    pattern_->fastAnimationRunning_ = true;
    pattern_->FireSelectedEvent(3, 3);
    EXPECT_EQ(pattern_->selectedIndex_, 3);
}

/**
 * @tc.name: OnIndexChange002
 * @tc.desc: Test OnIndexChange
 * @tc.type: FUNC
 */
HWTEST_F(SwiperEventTestTwoNg, OnIndexChange002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetOnSelected(std::move(nullptr));
    CreateSwiperItems(6);
    CreateSwiperDone();

    pattern_->oldIndex_ = 3;
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateIndex(3);
    pattern_->fastAnimationRunning_ = true;
    pattern_->OnIndexChange(true);
    EXPECT_TRUE(pattern_->fastAnimationChange_);

    pattern_->fastAnimationRunning_ = false;
    pattern_->OnIndexChange(true);
    EXPECT_FALSE(pattern_->fastAnimationChange_);
}
} // namespace OHOS::Ace::NG
