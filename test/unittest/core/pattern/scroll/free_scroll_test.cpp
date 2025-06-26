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
namespace {
constexpr float X = -3000;
constexpr float Y = -3000;
constexpr float CONTENT_W = 2000;
constexpr float CONTENT_H = 2000;
constexpr float SMALL_CONTENT_W = 100;
constexpr float SMALL_CONTENT_H = 50;
} // namespace

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
    CreateFreeContent({ CONTENT_W, CONTENT_H });
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
    CreateFreeContent({ contentWidth, CONTENT_H });
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
    CreateFreeContent({ CONTENT_W, CONTENT_H });
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
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_TRUE(pattern_->offset_);
    pattern_->currentOffset_ = 20.0f;

    layoutProperty_->UpdateAxis(Axis::VERTICAL);
    pattern_->OnModifyDone();
    ASSERT_FALSE(pattern_->offset_);
    ASSERT_EQ(pattern_->currentOffset_, 0);
}

/**
 * @tc.name: OverScroll001
 * @tc.desc: Test overScroll
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, OverScroll001, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_TRUE(pattern_->offset_);
    pattern_->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);

    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(X, Y));

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::NONE, true, EffectEdge::ALL);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(WIDTH - CONTENT_W, HEIGHT - CONTENT_H).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::START);
    pattern_->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(WIDTH - CONTENT_W, HEIGHT - CONTENT_H).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::END);
    pattern_->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0), OffsetF(X, Y));
}

/**
 * @tc.name: OverScroll002
 * @tc.desc: Test overScroll when content is smaller than viewport
 * @tc.type: FUNC
 */
HWTEST_F(FreeScrollTest, OverScroll002, TestSize.Level1)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    CreateFreeContent({ SMALL_CONTENT_W, SMALL_CONTENT_H });
    CreateScrollDone();
    ASSERT_TRUE(pattern_->offset_);
    pattern_->offset_->Set(OffsetF { X, Y });
    FlushUITasks(frameNode_);

    constexpr float alignX = (WIDTH - SMALL_CONTENT_W) / 2;
    constexpr float alignY = (HEIGHT - SMALL_CONTENT_H) / 2;

    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(X + alignX, Y + alignY).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::FADE, true, EffectEdge::ALL);
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::START);
    pattern_->offset_->Set(OffsetF { X, -Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY - Y).ToString());

    ScrollModelNG::SetEdgeEffect(frameNode_.GetRawPtr(), EdgeEffect::SPRING, true, EffectEdge::END);
    pattern_->offset_->Set(OffsetF { -X, -Y });
    FlushUITasks(frameNode_);
    EXPECT_EQ(GetChildOffset(frameNode_, 0).ToString(), OffsetF(alignX, alignY).ToString());
}
} // namespace OHOS::Ace::NG