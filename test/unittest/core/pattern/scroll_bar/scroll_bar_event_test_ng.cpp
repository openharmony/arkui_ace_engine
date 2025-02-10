/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

#include "scroll_bar_test_ng.h"
#include "test/mock/base/mock_task_executor.h"

namespace OHOS::Ace::NG {

class ScrollBarEventTestNg : public ScrollBarTestNg {
public:
    void HandleDragStart(GestureEvent info)
    {
        auto handleDragStart = *(pattern_->panRecognizer_->onActionStart_);
        handleDragStart(info);
    }

    void HandleDragUpdate(GestureEvent info)
    {
        auto handleDragUpdate = *(pattern_->panRecognizer_->onActionUpdate_);
        handleDragUpdate(info);
    }

    void HandleDragEnd(GestureEvent info)
    {
        auto handleDragEnd = *(pattern_->panRecognizer_->onActionEnd_);
        handleDragEnd(info);
    }

    void HandleMouseEvent(MouseInfo info)
    {
        auto handleMouseEvent = pattern_->mouseEvent_->GetOnMouseEventFunc();
        handleMouseEvent(info);
    }

    void HandleClickEvent()
    {
        ClickInfo info(1);
        auto handleClickEvent = pattern_->clickRecognizer_->onClick_;
        handleClickEvent(info);
    }

    void HandleLongPress()
    {
        GestureEvent info;
        auto handleLongPress = *(pattern_->longPressRecognizer_->onAction_);
        handleLongPress(info);
    }
};

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Test ScrollBar about HandleDrag, the scrollBar and scroll position will change by drag
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(460.f, 0, SCROLL_BAR_CHILD_WIDTH, SCROLL_HEIGHT)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_HEIGHT);          // 200.f
    EXPECT_EQ(scrollableDistance, SCROLL_HEIGHT - SCROLL_BAR_CHILD_HEIGHT); // 640.f

    /**
     * @tc.steps: step1. HandleDragStart, drag on scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(SCROLL_WIDTH - 1.f, 1.f));
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, drag up
     * @tc.expected: Can not scroll up because at top
     */
    float delta = SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragUpdate, drag down
     * @tc.expected: Scroll down
     */
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    float expectOffset = delta * controlDistance / scrollableDistance;
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset); // 50.f

    /**
     * @tc.steps: step4. HandleDragUpdate, drag down continue
     * @tc.expected: Scroll down
     */
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta * 2);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset * 2); // 100.f

    /**
     * @tc.steps: step5. HandleDragUpdate, drag up
     * @tc.expected: Scroll up
     */
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset); // 50.f

    /**
     * @tc.steps: step6. HandleDragEnd, drag end
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset);
}

/**
 * @tc.name: HandleDrag002
 * @tc.desc: Test ScrollBar about HandleDrag with InputEventType::AXIS
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag002, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateScrollBarChild();
    CreateDone();
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();

    /**
     * @tc.steps: step1. HandleDragStart, mouse wheel on scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(SCROLL_WIDTH - 1.f, 1.f));
    info.SetInputEventType(InputEventType::AXIS);
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, mouse wheel down
     * @tc.expected: Scroll down
     */
    float delta = -SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    float expectBarPosition = -delta / controlDistance * scrollableDistance;
    EXPECT_EQ(pattern_->GetCurrentPosition(), expectBarPosition); // 512.f
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), -delta);

    /**
     * @tc.steps: step3. HandleDragUpdate, mouse wheel down continue
     * @tc.expected: Scroll down
     */
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance); // 640.f
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), controlDistance);

    /**
     * @tc.steps: step4. HandleDragUpdate, mouse wheel up
     * @tc.expected: Scroll up
     */
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance - expectBarPosition); // 138
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), controlDistance + delta);              // 40.f

    /**
     * @tc.steps: step5. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance - expectBarPosition); // 138
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), controlDistance + delta);              // 40.f
}

/**
 * @tc.name: HandleDrag003
 * @tc.desc: Test ScrollBar about HandleDrag in HORIZONTAL Layout and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag003, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateStack(Alignment::BOTTOM_CENTER);
    CreateScroll(CONTENT_MAIN_SIZE, Axis::HORIZONTAL);
    CreateScrollBar(true, true, Axis::HORIZONTAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(0.f, 780.f, SCROLL_WIDTH, SCROLL_BAR_CHILD_WIDTH)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_WIDTH);          // 520.f
    EXPECT_EQ(scrollableDistance, SCROLL_WIDTH - SCROLL_BAR_CHILD_HEIGHT); // 320.f
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance);

    /**
     * @tc.steps: step1. HandleDragStart, drag on scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(1.f, SCROLL_HEIGHT - 1.f));
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, drag left
     * @tc.expected: Scroll left
     */
    float delta = SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    EXPECT_TRUE(IsEqual(GetChildOffset(frameNode_, 0), OffsetF(delta, 0.f)));

    /**
     * @tc.steps: step3. HandleDragUpdate, drag left continue
     * @tc.expected: Scroll left
     */
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);

    /**
     * @tc.steps: step4. HandleDragUpdate, drag right
     * @tc.expected: Scroll right
     */
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);

    /**
     * @tc.steps: step5. HandleDragEnd, drag end
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
}

/**
 * @tc.name: HandleDrag004
 * @tc.desc: Test ScrollBar about HandleDrag with InputEventType::AXIS in unScrollable Scroll, can not scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag004, TestSize.Level1)
{
    CreateStack();
    CreateScroll(SCROLL_HEIGHT);
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    float scrollableDistance = scrollPattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0.f);

    /**
     * @tc.steps: step1. HandleDragStart, mouse wheel scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(SCROLL_WIDTH - 1.f, 1.f));
    info.SetInputEventType(InputEventType::AXIS);
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, mouse wheel down
     * @tc.expected: Not scroll
     */
    float delta = -SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: HandleDrag005
 * @tc.desc: Test ScrollBar about HandleDrag in unScrollable Scroll, can not scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag005, TestSize.Level1)
{
    CreateStack();
    CreateScroll(SCROLL_HEIGHT);
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    float scrollableDistance = scrollPattern_->GetScrollableDistance();
    EXPECT_EQ(scrollableDistance, 0.f);

    /**
     * @tc.steps: step1. HandleDragStart, mouse wheel scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(SCROLL_WIDTH - 1.f, 1.f));
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragUpdate, mouse wheel down
     * @tc.expected: Not scroll
     */
    float delta = SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);
}

/**
 * @tc.name: HandleDrag006
 * @tc.desc: Test ScrollBar about HandleDrag with velocity
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDrag006, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. HandleDragEnd with velocity
     * @tc.expected: Trigger animation
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(SCROLL_WIDTH - 1.f, 1.f));
    HandleDragStart(info);
    float delta = SCROLL_BAR_CHILD_HEIGHT;
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushUITasks();
    info.SetMainVelocity(1200.f);
    HandleDragEnd(info);
    pattern_->frictionMotion_->NotifyListener(0.f);
    FlushUITasks();
    EXPECT_TRUE(pattern_->frictionController_->IsRunning());

    /**
     * @tc.steps: step2. HandleDragEnd with velocity again
     * @tc.expected: Trigger animation
     */
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushUITasks();
    HandleDragEnd(info);
    FlushUITasks();
    EXPECT_TRUE(pattern_->frictionController_->IsRunning());
}

/**
 * @tc.name: InBarRegion001
 * @tc.desc: Test InBarRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, InBarRegion001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(IsEqual(pattern_->childRect_, RectF(0, 0, SCROLL_BAR_CHILD_WIDTH, SCROLL_BAR_CHILD_HEIGHT)));
    EXPECT_TRUE(pattern_->scrollableEvent_->InBarRegion(PointF(), SourceType::TOUCH));
    EXPECT_FALSE(pattern_->scrollableEvent_->InBarRegion(PointF(0, SCROLL_BAR_CHILD_HEIGHT + 1.f), SourceType::TOUCH));
}

/**
 * @tc.name: InBarRegion002
 * @tc.desc: Test InBarRegion without scrollBar child in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, InBarRegion002, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();
    EXPECT_TRUE(IsEqual(pattern_->scrollBar_->hoverRegion_, Rect(8.f, 0, 8.f, 640.f)));
    EXPECT_TRUE(IsEqual(pattern_->scrollBar_->touchRegion_, Rect(-16.f, 0, 32.f, 640.f)));
    EXPECT_TRUE(pattern_->scrollableEvent_->InBarRegion(PointF(), SourceType::TOUCH));
    EXPECT_FALSE(pattern_->scrollableEvent_->InBarRegion(PointF(-20.f, 0), SourceType::TOUCH));
    EXPECT_TRUE(pattern_->scrollableEvent_->InBarRegion(PointF(8.f, 0), SourceType::MOUSE));
    EXPECT_FALSE(pattern_->scrollableEvent_->InBarRegion(PointF(), SourceType::MOUSE));
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: BarCollectTouchTarget001
 * @tc.desc: Test BarCollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, BarCollectTouchTarget001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();

    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    pattern_->scrollableEvent_->BarCollectTouchTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode_, nullptr, responseLinkResult);
    EXPECT_FLOAT_EQ(pattern_->panRecognizer_->GetCoordinateOffset().GetX(), coordinateOffset.GetX());
    EXPECT_FLOAT_EQ(pattern_->panRecognizer_->GetCoordinateOffset().GetY(), coordinateOffset.GetY());
    EXPECT_EQ(result.size(), 1);
}

/**
 * @tc.name: BarCollectTouchTarget002
 * @tc.desc: Test BarCollectTouchTarget in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, BarCollectTouchTarget002, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateDone();

    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    pattern_->scrollableEvent_->BarCollectTouchTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode_, nullptr, responseLinkResult);
    EXPECT_EQ(result.size(), 1);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: BarCollectLongPressTarget001
 * @tc.desc: Test BarCollectLongPressTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, BarCollectLongPressTarget001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    ResponseLinkResult responseLinkResult;
    auto frameNode = AceType::MakeRefPtr<FrameNode>(V2::LIST_ETS_TAG, -1, AceType::MakeRefPtr<Pattern>());
    pattern_->scrollableEvent_->BarCollectLongPressTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode, nullptr, responseLinkResult);
    EXPECT_FLOAT_EQ(pattern_->longPressRecognizer_->GetCoordinateOffset().GetX(), coordinateOffset.GetX());
    EXPECT_FLOAT_EQ(pattern_->longPressRecognizer_->GetCoordinateOffset().GetY(), coordinateOffset.GetY());
    EXPECT_EQ(result.size(), 2);
}

/**
 * @tc.name: InBarRectRegion001
 * @tc.desc: Test InBarRectRegion
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, InBarRectRegion001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    EXPECT_TRUE(pattern_->scrollableEvent_->InBarRectRegion(PointF(), SourceType::KEYBOARD));
}

/**
 * @tc.name: ScrollScrollBar001
 * @tc.desc: Test scrollCallback event in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, ScrollScrollBar001, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    auto scrollCallback = pattern_->scrollBar_->GetScrollPositionCallback();
    scrollCallback(-100.f, SCROLL_FROM_BAR);
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 100.f);

    auto scrollEnd = pattern_->scrollBar_->GetScrollEndCallback();
    scrollEnd();
    FlushUITasks();

    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: HoverScrollBar001
 * @tc.desc: Test Hover event in VERSION_TWELVE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HoverScrollBar001, TestSize.Level1)
{
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. DisplayMode::ON, hover or not hover
     * @tc.expected: Always show scrollBar
     */
    auto inputHub = pattern_->GetInputHub();
    auto onHover = inputHub->hoverEventActuator_->inputEvents_.front()->GetOnHoverFunc();
    HoverInfo info;
    onHover(true, info);
    auto scrollBarRenderContext = frameNode_->GetRenderContext();
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);
    onHover(false, info);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);

    /**
     * @tc.steps: step2. DisplayMode::AUTO, hover or not hover
     * @tc.expected: Show scrollBar when hover, hide when not hover
     */
    pattern_->displayMode_ = DisplayMode::AUTO;
    onHover(true, info);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);
    onHover(false, info);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 0);

    /**
     * @tc.steps: step3. Press scrollBar
     * @tc.expected: Show scrollBar
     */
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset());
    HandleMouseEvent(mouseInfo);
    EXPECT_TRUE(pattern_->isMousePressed_);
    onHover(false, info);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);

    /**
     * @tc.steps: step4. When isScrolling_
     * @tc.expected: Show scrollBar
     */
    pattern_->isScrolling_ = true;
    onHover(false, info);
    EXPECT_EQ(scrollBarRenderContext->GetOpacityValue(), 1);

    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: HandleClickEvent001
 * @tc.desc: HandleClickEvent
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleClickEvent001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. Click in scrollBar
     * @tc.expected: Can not scroll
     */
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset());
    HandleMouseEvent(mouseInfo);
    HandleClickEvent();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step2. Click below scrollBar
     * @tc.expected: Scroll down
     */
    mouseInfo.SetLocalLocation(Offset(0, SCROLL_BAR_CHILD_HEIGHT + 1.f));
    HandleMouseEvent(mouseInfo);
    HandleClickEvent();
    FlushUITasks();
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. Click above scrollBar
     * @tc.expected: Scroll up
     */
    // scroll down
    pattern_->UpdateCurrentOffset(1.f, SCROLL_FROM_BAR);
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), 1.f);
    // click above scrollBar
    mouseInfo.SetLocalLocation(Offset());
    HandleMouseEvent(mouseInfo);
    HandleClickEvent();
    FlushUITasks();
    EXPECT_GT(scrollPattern_->GetTotalOffset(), 0.f);
    EXPECT_LT(scrollPattern_->GetTotalOffset(), 1.f);
}

/**
 * @tc.name: HandleLongPress001
 * @tc.desc: HandleLongPress, Press scrollBar will scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleLongPress001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. Press below scrollBar
     * @tc.expected: Scroll down
     */
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(-100.f, SCROLL_BAR_CHILD_HEIGHT + 1.f));
    HandleMouseEvent(mouseInfo);
    HandleLongPress();
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_TRUE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step2. Press in scrollBar
     * @tc.expected: Can not scroll
     */
    mouseInfo.SetLocalLocation(Offset());
    HandleMouseEvent(mouseInfo);
    HandleLongPress();
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_FALSE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step3. Press above scrollBar
     * @tc.expected: Scroll up
     */
    mouseInfo.SetLocalLocation(Offset(0, -1.f));
    HandleMouseEvent(mouseInfo);
    HandleLongPress();
    EXPECT_TRUE(pattern_->scrollingUp_);
    EXPECT_FALSE(pattern_->scrollingDown_);
}

/**
 * @tc.name: HandleLongPress002
 * @tc.desc: HandleLongPress
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleLongPress002, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. When scrollingUp_
     * @tc.expected: Can not scroll down
     */
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(-100.f, SCROLL_BAR_CHILD_HEIGHT + 1.f));
    HandleMouseEvent(mouseInfo);
    pattern_->scrollingUp_ = true;
    HandleLongPress();
    EXPECT_TRUE(pattern_->scrollingUp_);
    EXPECT_FALSE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step2. When scrollingDown_
     * @tc.expected: Can not scroll up
     */
    mouseInfo.SetLocalLocation(Offset(0, -1.f));
    HandleMouseEvent(mouseInfo);
    pattern_->scrollingUp_ = false;
    pattern_->scrollingDown_ = true;
    HandleLongPress();
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_TRUE(pattern_->scrollingDown_);
}

/**
 * @tc.name: HandleLongPress003
 * @tc.desc: HandleLongPress, When use other mouse action, stop scroll
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleLongPress003, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. Press below scrollBar
     * @tc.expected: Scroll down
     */
    MouseInfo mouseInfo;
    mouseInfo.SetButton(MouseButton::LEFT_BUTTON);
    mouseInfo.SetAction(MouseAction::PRESS);
    mouseInfo.SetLocalLocation(Offset(-100.f, SCROLL_BAR_CHILD_HEIGHT + 1.f));
    HandleMouseEvent(mouseInfo);
    HandleLongPress();
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_TRUE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step2. Mouse move
     * @tc.expected: Stop scroll
     */
    mouseInfo.SetAction(MouseAction::MOVE);
    HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_FALSE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step3. Press below scrollBar
     * @tc.expected: Scroll down
     */
    mouseInfo.SetAction(MouseAction::PRESS);
    HandleMouseEvent(mouseInfo);
    HandleLongPress();
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_TRUE(pattern_->scrollingDown_);

    /**
     * @tc.steps: step4. Press by other button
     * @tc.expected: Stop scroll
     */
    mouseInfo.SetButton(MouseButton::RIGHT_BUTTON);
    HandleMouseEvent(mouseInfo);
    EXPECT_FALSE(pattern_->scrollingUp_);
    EXPECT_FALSE(pattern_->scrollingDown_);
}

/**
 * @tc.name: HandleOnHover001
 * @tc.desc: Test mouse onhover show bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleOnHover001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create CreateScrollBar and MouseInfo.
     * @tc.expected: create CreateScrollBar and MouseInfo created successfully.
     */
    const int32_t apiTargetVersion = Container::Current()->GetApiTargetVersion();
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateScrollBarChild();
    CreateDone();
    pattern_->SetControlDistance(1.f);
    pattern_->CreateScrollBarOverlayModifier();
    auto context = PipelineContext::GetCurrentContext();
    EXPECT_NE(context, nullptr);
    if (context->taskExecutor_ == nullptr) {
        context->taskExecutor_ = AceType::MakeRefPtr<MockTaskExecutor>();
    }
    EXPECT_NE(context->taskExecutor_, nullptr);

    /**
     * @tc.steps: step2. Test not hover on bar.
     * @tc.expect: Opacity = 0 .
     */
    pattern_->InitMouseEvent();
    pattern_->SetScrollBar(DisplayMode::AUTO);
    HoverInfo info;
    auto inputHub = pattern_->GetInputHub();
    auto& inputEvents = pattern_->GetEventHub<EventHub>()->GetInputEventHub()->hoverEventActuator_->inputEvents_;
    EXPECT_TRUE(inputEvents.size() > 1);
    for (const auto& callback : inputEvents) {
        if (callback) {
            (*callback)(false, info);
        }
    }
    EXPECT_EQ(pattern_->opacity_, 0);

    /**
     * @tc.steps: step2. Test hover on bar.
     * @tc.expect: Opacity = UINT8_MAX .
     */
    for (const auto& callback : inputEvents) {
        if (callback) {
            (*callback)(true, info);
        }
    }
    EXPECT_EQ(pattern_->opacity_, UINT8_MAX);
    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}

/**
 * @tc.name: HandleDragEnd001
 * @tc.desc: Test ScrollBar about HandleDragEnd in HORIZONTAL Layout and RTL Layout
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, HandleDragEnd001, TestSize.Level1)
{
    AceApplicationInfo::GetInstance().isRightToLeft_ = true;
    CreateStack(Alignment::BOTTOM_CENTER);
    CreateScroll(CONTENT_MAIN_SIZE, Axis::HORIZONTAL);
    CreateScrollBar(true, true, Axis::HORIZONTAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 0), RectF(0, 0, SCROLL_WIDTH, SCROLL_HEIGHT)));
    EXPECT_TRUE(IsEqual(GetChildRect(stackNode_, 1), RectF(0.f, 780.f, SCROLL_WIDTH, SCROLL_BAR_CHILD_WIDTH)));
    float controlDistance = pattern_->GetControlDistance();
    float scrollableDistance = pattern_->GetScrollableDistance();
    EXPECT_EQ(controlDistance, CONTENT_MAIN_SIZE - SCROLL_WIDTH);          // 520.f
    EXPECT_EQ(scrollableDistance, SCROLL_WIDTH - SCROLL_BAR_CHILD_HEIGHT); // 320.f
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance);

    /**
     * @tc.steps: step1. HandleDragStart, drag on scrollBar
     */
    GestureEvent info;
    info.SetGlobalPoint(Point(1.f, SCROLL_HEIGHT - 1.f));
    HandleDragStart(info);

    /**
     * @tc.steps: step2. HandleDragEnd, drag left
     * @tc.expected: Scroll left
     */
    info.SetMainVelocity(-1000.f);
    HandleDragEnd(info);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_LE(pattern_->GetCurrentPosition(), 60.f);

    /**
     * @tc.steps: step2. HandleDragEnd, drag right
     * @tc.expected: Scroll right
     */
    info.SetMainVelocity(1000.f);
    HandleDragEnd(info);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance);
}

/**
 * @tc.name: IsScrolling001
 * @tc.desc: Test isScrolling in scrollBar without child
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, IsScrolling001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateDone();
    EXPECT_FALSE(pattern_->isScrolling_);

    /**
     * @tc.steps: step2. inner scrollbar HandleDragStart
     * @tc.expected: isScrolling_ is true
     */
    GestureEvent info;
    pattern_->scrollBar_->HandleDragStart(info);
    EXPECT_TRUE(pattern_->isScrolling_);

    /**
     * @tc.steps: step2. inner scrollbar HandleDragEnd
     * @tc.expected: isScrolling_ is false
     */
    info.SetMainVelocity(-1000.f);
    pattern_->scrollBar_->HandleDragEnd(info);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->isScrolling_);
}

/**
 * @tc.name: PanDirection001
 * @tc.desc: Test ScrollBar PanDirection with axis changing
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, PanDirection001, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::ON);
    CreateScrollBarChild();
    CreateDone();
    EXPECT_EQ(pattern_->panRecognizer_->direction_.type, PanDirection::VERTICAL);
    
    /**
     * @tc.steps: step1. change scrollbar axis to HORIZONTAL
     * @tc.expected: scrollBar panDirection is HORIZONTAL
     */
    layoutProperty_->UpdateAxis(Axis::HORIZONTAL);
    pattern_->OnModifyDone();
    FlushUITasks();
    EXPECT_EQ(pattern_->panRecognizer_->direction_.type, PanDirection::HORIZONTAL);
}

/**
 * @tc.name: OnScrollStartStop001
 * @tc.desc: Test OnScrollStart and OnScrollStart in drag scrollBar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, OnScrollStartStop001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Initialize variables and callback
     * @tc.expected: Variables initialized successfully.
     */
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateDone();

    int32_t isScrollStartCalled = 0;
    OnScrollStartEvent scrollStart = [&isScrollStartCalled]() { isScrollStartCalled++; };
    int32_t isScrollStopCalled = 0;
    int32_t stopHasStart = 0;
    OnScrollStopEvent scrollStop = [&isScrollStopCalled, &isScrollStartCalled, &stopHasStart]() {
        if (isScrollStartCalled - isScrollStopCalled == 1) {
            stopHasStart++;
        }
        isScrollStopCalled++;
    };
    auto eventHub = scrollNode_->GetEventHub<ScrollEventHub>();
    EXPECT_NE(eventHub, nullptr);
    eventHub->SetOnScrollStart(std::move(scrollStart));
    eventHub->SetOnScrollStop(std::move(scrollStop));

    /**
     * @tc.steps: step2. scrollBar dragStart
     * @tc.expected: isScrollStartCalled should be 1.
     */
    GestureEvent info;
    pattern_->scrollBar_->HandleDragStart(info);
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 0);

    /**
     * @tc.steps: step3. scrollBar dragUpdate.
     * @tc.expected: isScrollStartCalled should be 1.
     */
    info.SetMainDelta(10.f);
    pattern_->scrollBar_->HandleDragUpdate(info);
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 0);

    /**
     * @tc.steps: step4. scrollBar dragEnd.
     * @tc.expected: isScrollStopCalled should be 1.
     */
    info.SetMainVelocity(0.f);
    pattern_->scrollBar_->HandleDragEnd(info);
    FlushUITasks();
    EXPECT_EQ(isScrollStartCalled, 1);
    EXPECT_EQ(isScrollStopCalled, 1);
    EXPECT_EQ(stopHasStart, 1);
}

/**
 * @tc.name: IsScrollSnapTrigger001
 * @tc.desc: Test drag scrollbar with scroll snap
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, IsScrollSnapTrigger001, TestSize.Level1)
{
    Container::Current()->SetApiTargetVersion(static_cast<int32_t>(PlatformVersion::VERSION_TWELVE));
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    scrollPattern_->SetEnablePaging(ScrollPagingStatus::VALID);
    CreateDone();

    /**
     * @tc.steps: step1. scroll set enablePaging and scrollBar dragStart
     * @tc.expected: IsScrollSnapTrigger should be true.
     */
    GestureEvent info;
    pattern_->scrollBar_->HandleDragStart(info);
    EXPECT_TRUE(pattern_->scrollBarProxy_->IsScrollSnapTrigger());

    /**
     * @tc.steps: step2. scrollBar dragEnd.
     * @tc.expected: trigger scroll snap animation.
     */
    info.SetMainDelta(10.f);
    info.SetMainVelocity(1000.f);
    pattern_->scrollBar_->HandleDragEnd(info);
    auto scrollable = scrollPattern_->GetScrollable();
    EXPECT_EQ(scrollable->state_, Scrollable::AnimationState::SNAP);
}

/**
 * @tc.name: IsScrollSnapTrigger002
 * @tc.desc: Test drag scrollbar
 * @tc.type: FUNC
 */
HWTEST_F(ScrollBarEventTestNg, IsScrollSnapTrigger002, TestSize.Level1)
{
    CreateStack();
    CreateScroll();
    CreateScrollBar(true, true, Axis::VERTICAL, DisplayMode::AUTO);
    CreateScrollBarChild();
    CreateDone();

    /**
     * @tc.steps: step1. scroll set enablePaging and scrollBar dragStart
     * @tc.expected: IsScrollSnapTrigger should be true.
     */
    GestureEvent info;
    pattern_->HandleDragStart(info);
    EXPECT_TRUE(pattern_->scrollBarProxy_->IsScrollSnapTrigger());
    info.SetMainDelta(10.f);
    info.SetMainVelocity(0.f);
    pattern_->HandleDragEnd(info);
    EXPECT_FALSE(pattern_->scrollBarProxy_->IsScrollSnapTrigger());

    /**
     * @tc.steps: step2. scrollBar dragEnd.
     * @tc.expected: trigger scroll snap animation.
     */
    pattern_->HandleDragStart(info);
    EXPECT_TRUE(pattern_->scrollBarProxy_->IsScrollSnapTrigger());
    info.SetMainVelocity(1000.f);
    pattern_->HandleDragEnd(info);
    EXPECT_TRUE(pattern_->scrollBarProxy_->IsScrollSnapTrigger());
}
} // namespace OHOS::Ace::NG
