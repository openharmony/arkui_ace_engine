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
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragUpdate, drag down
     * @tc.expected: Scroll down
     */
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    float expectOffset = delta * controlDistance / scrollableDistance;
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset); // 50.f

    /**
     * @tc.steps: step4. HandleDragUpdate, drag down continue
     * @tc.expected: Scroll down
     */
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta * 2);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset * 2); // 100.f

    /**
     * @tc.steps: step5. HandleDragUpdate, drag up
     * @tc.expected: Scroll up
     */
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), expectOffset); // 50.f

    /**
     * @tc.steps: step6. HandleDragEnd, drag end
     */
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_, true);
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
    FlushLayoutTask(stackNode_, true);
    float expectBarPosition = -delta / controlDistance * scrollableDistance;
    EXPECT_EQ(pattern_->GetCurrentPosition(), expectBarPosition); // 512.f
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), -delta);

    /**
     * @tc.steps: step3. HandleDragUpdate, mouse wheel down continue
     * @tc.expected: Scroll down
     */
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance); // 640.f
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), controlDistance);

    /**
     * @tc.steps: step4. HandleDragUpdate, mouse wheel up
     * @tc.expected: Scroll up
     */
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), scrollableDistance - expectBarPosition); // 138
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), controlDistance + delta);              // 40.f

    /**
     * @tc.steps: step5. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_, true);
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
    CreateDone(stackNode_);
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
    info.SetMainDelta(delta);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);

    /**
     * @tc.steps: step3. HandleDragUpdate, drag left continue
     * @tc.expected: Scroll left
     */
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);

    /**
     * @tc.steps: step4. HandleDragUpdate, drag right
     * @tc.expected: Scroll right
     */
    info.SetMainDelta(-delta);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);

    /**
     * @tc.steps: step5. HandleDragEnd, drag end
     */
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_);
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
    FlushLayoutTask(stackNode_, true);
    EXPECT_EQ(pattern_->GetCurrentPosition(), 0.f);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_, true);
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
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 0.f);

    /**
     * @tc.steps: step3. HandleDragEnd, mouse wheel end
     */
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(pattern_->GetCurrentPosition(), delta);
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
    FlushLayoutTask(stackNode_);
    info.SetMainVelocity(1200.f);
    HandleDragEnd(info);
    pattern_->frictionMotion_->NotifyListener(0.f);
    FlushLayoutTask(stackNode_);
    EXPECT_TRUE(pattern_->frictionController_->IsRunning());

    /**
     * @tc.steps: step2. HandleDragEnd with velocity again
     * @tc.expected: Trigger animation
     */
    HandleDragStart(info);
    HandleDragUpdate(info);
    FlushLayoutTask(stackNode_);
    HandleDragEnd(info);
    FlushLayoutTask(stackNode_);
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
    FlushLayoutTask(stackNode_);
    EXPECT_EQ(scrollPattern_->GetTotalOffset(), 100.f);

    auto scrollEnd = pattern_->scrollBar_->GetScrollEndCallback();
    scrollEnd();
    FlushLayoutTask(stackNode_);

    Container::Current()->SetApiTargetVersion(apiTargetVersion);
}
} // namespace OHOS::Ace::NG
