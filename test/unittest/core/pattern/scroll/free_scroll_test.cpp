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

class FreeScrollTest : public ScrollTestNg {
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
 * @tc.name: RecognizerOverride001
 * @tc.desc: Test gesture recognizer override when axis == FREE
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, RecognizerOverride001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateScrollDone();
    ASSERT_TRUE(pattern_->freePanGesture_);

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
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
HWTEST_F(FreeScrollTest, FreeScroll001, TestSize.Level1)
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

/**
 * @tc.name: Properties001
 * @tc.desc: check property values with Axis::Free (main axis should be horizontal)
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, Properties001, TestSize.Level1)
{
    constexpr float contentWidth = 1000;
    ScrollModelNG model = CreateScroll();
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ contentWidth, 2000 });
    CreateScrollDone();

    EXPECT_EQ(pattern_->scrollableDistance_, contentWidth - WIDTH);
    EXPECT_EQ(pattern_->viewPortLength_, WIDTH);
}

/**
 * @tc.name: ModeChange001
 * @tc.desc: Test Scroll axis change
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, ModeChange001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ 2000, 2000 });
    CreateScrollDone();

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    EXPECT_EQ(*link.begin(), pattern_->freePanGesture_);
    EXPECT_EQ(*res.begin(), pattern_->freePanGesture_);
    ASSERT_TRUE(pattern_->freePanGesture_->onActionUpdate_);

    res.clear();
    link.clear();
    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    ASSERT_FALSE(pattern_->freePanGesture_);
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link);
    EXPECT_EQ(link.size(), 1);
    ASSERT_EQ(*link.begin(), scrollHandler->GetScrollable()->panRecognizerNG_);
}

/**
 * @tc.name: ModeChange002
 * @tc.desc: Test offset reset
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, ModeChange002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ 2000, 2000 });
    CreateScrollDone();

    pattern_->crossOffset_ = 50.0;
    pattern_->currentOffset_ = 20.0;

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->crossOffset_, 0);
    EXPECT_EQ(pattern_->currentOffset_, 0);
}
} // namespace OHOS::Ace::NG
