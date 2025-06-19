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

#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"

#include "core/event/touch_event.h"
namespace OHOS::Ace::NG {

class ScrollGestureTest : public ScrollTestNg {
public:
    void TriggerFreeScroll(const Offset& delta)
    {
        GestureEvent gesture;
        gesture.SetSourceTool(SourceTool::FINGER);
        gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
        gesture.SetGlobalPoint(Point(1, 1));
        gesture.SetGlobalLocation({ 1, 1 });
        gesture.SetLocalLocation({ 1, 1 });
        gesture.SetDelta(delta);
        ASSERT_TRUE(pattern_->freePanGesture_->onActionUpdate_);
        auto&& func = *(pattern_->freePanGesture_->onActionUpdate_);
        func(gesture);
    }
};

/**
 * @tc.name: FreeScroll001
 * @tc.desc: Test gesture recognizer override when axis == FREE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollGestureTest, RecognizerOverride001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateScrollDone();
    ASSERT_TRUE(pattern_->freePanGesture_);

    OffsetF of { 1, 1 };
    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    scrollHandler->CollectScrollableTouchTarget(of, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), pattern_->freePanGesture_);
    EXPECT_EQ(*res.begin(), pattern_->freePanGesture_);
    ASSERT_TRUE(pattern_->freePanGesture_->onActionUpdate_);
}

/**
 * @tc.name: FreeScroll001
 * @tc.desc: Test Scroll with Axis::FREE
 * @tc.type: FUNC
 */
HWTEST_F(ScrollGestureTest, FreeScroll001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ 2000, 2000 });
    CreateScrollDone();

    TriggerFreeScroll({ -100, -100 });

    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -100.0f);
    EXPECT_EQ(GetChildY(frameNode_, 0), -100.0f);
}
} // namespace OHOS::Ace::NG
