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

#include "test/mock/core/animation/mock_animation_manager.h"
#include "test/unittest/core/pattern/scroll/scroll_test_ng.h"

#include "core/components_ng/pattern/scroll/zoom_controller.h"
#include "core/event/touch_event.h"
namespace OHOS::Ace::NG {
namespace {
constexpr float CONTENT_W = 2000;
constexpr float CONTENT_H = 2000;
} // namespace

class ScrollZoomTest : public ScrollTestNg {
public:
    static void SetUpTestSuite()
    {
        ScrollTestNg::SetUpTestSuite();
        MockAnimationManager::Enable(true);
    }
    static void TearDownTestSuite()
    {
        ScrollTestNg::TearDownTestSuite();
        MockAnimationManager::Enable(false);
    }

    static GestureEvent MakePinchGesture(float scale, const Offset& center = { 0, 0 })
    {
        GestureEvent gesture;
        gesture.SetSourceTool(SourceTool::FINGER);
        gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
        gesture.SetGlobalPoint(Point(1, 1));
        gesture.SetGlobalLocation({ 1, 1 });
        gesture.SetLocalLocation({ 1, 1 });
        FingerInfo info;
        info.localLocation_ = center;
        std::list<FingerInfo> fingerList { info };
        gesture.SetFingerList(fingerList);
        gesture.SetScale(scale);
        return gesture;
    }

    void PinchStart(float scale)
    {
        const auto& controller = pattern_->zoomCtrl_;
        auto gesture = MakePinchGesture(scale);
        ASSERT_TRUE(controller && controller->pinchGesture_);
        ASSERT_TRUE(controller->pinchGesture_->onActionStart_);
        auto&& func = *(controller->pinchGesture_->onActionStart_);
        func(gesture);
    }
    void PinchUpdate(float scale, const Offset& center = { 0, 0 })
    {
        const auto& controller = pattern_->zoomCtrl_;
        auto gesture = MakePinchGesture(scale, center);
        ASSERT_TRUE(controller && controller->pinchGesture_);
        ASSERT_TRUE(controller->pinchGesture_->onActionUpdate_);
        auto&& func = *(controller->pinchGesture_->onActionUpdate_);
        func(gesture);
    }
    void PinchEnd(const Offset& center = { 0, 0 })
    {
        const auto& controller = pattern_->zoomCtrl_;
        auto gesture = MakePinchGesture(1.0, center);
        ASSERT_TRUE(controller && controller->pinchGesture_);
        ASSERT_TRUE(controller->pinchGesture_->onActionEnd_);
        auto&& func = *(controller->pinchGesture_->onActionEnd_);
        func(gesture);
    }
};

/**
 * @tc.name: ZoomScaleTest001
 * @tc.desc: Test set and reset zoomScale
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest, ZoomScaleTest001)
{
    /**
     * @tc.step: step1. Create Scroll, set zoomScale to 2.0f;
     * @tc.expected: scrollPattern zoomScale is 2.0f;
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetZoomScale(2.0f);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    EXPECT_EQ(pattern_->zoomScale_.value(), 2.0f);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Height(), CONTENT_H * 2.0f);
    EXPECT_EQ(pattern_->GetChildrenExpandedSize().Width(), CONTENT_W * 2.0f);

    /**
     * @tc.step: step2. Create Scroll, reset zoomScale;
     * @tc.expected: scrollPattern zoomScale is nullopt;
     */
    ScrollModelNG::ResetZoomScale(AceType::RawPtr(frameNode_));
    FlushUITasks();
    EXPECT_EQ(pattern_->zoomScale_, std::nullopt);
    EXPECT_EQ(pattern_->viewPortExtent_.Height(), CONTENT_H);
    EXPECT_EQ(pattern_->viewPortExtent_.Width(), CONTENT_W);
}

/**
 * @tc.name: ZoomScaleTest002
 * @tc.desc: Test zoom scale two-way binding
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest, ZoomScaleTest002)
{
    /**
     * @tc.step: step1. Create Scroll, set max and min scale.
     * @tc.expected: scrollPattern pinch gesture initiated.
     */
    float currScale = 1.0f;
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.0f);
    model.SetZoomScaleChangeEvent([&currScale](float scale) { currScale = scale; });
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_NE(pattern_->zoomCtrl_, nullptr);
    ASSERT_NE(pattern_->zoomCtrl_->pinchGesture_, nullptr);
    EXPECT_EQ(pattern_->zoomCtrl_->pinchGesture_->GetRecognizerType(), GestureTypeName::PINCH_GESTURE);
    EXPECT_TRUE(pattern_->zoomCtrl_->pinchGesture_->IsSystemGesture());

    /**
     * @tc.step: step2. pinch update;
     * @tc.expected: current scale updated;
     */
    PinchStart(1.0f);
    PinchUpdate(2.0f);
    EXPECT_EQ(currScale, 2.0f);
    FlushUITasks();

    /**
     * @tc.step: step3. update zoom scale from user.
     * @tc.expected: ZoomScaleChangeEvent not callback.
     */
    ScrollModelNG::SetZoomScale(AceType::RawPtr(frameNode_), 1.0f);
    FlushUITasks();
    EXPECT_EQ(currScale, 2.0f);
}
/**
 * @tc.name: ZoomScaleTest003
 * @tc.desc: Test GetItemRect
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest, ZoomScaleTest003)
{
    /**
     * @tc.step: step1. Create Scroll, set zoomScale to 2.0f;
     * @tc.expected: scrollPattern zoomScale is 2.0f;
     */
    constexpr float margin = 100;
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetZoomScale(2.0f);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    ViewAbstract::SetMargin(CalcLength(margin));
    CreateScrollDone();
    EXPECT_EQ(pattern_->zoomScale_.value(), 2.0f);
    EXPECT_EQ(pattern_->viewPortExtent_.Height(), (CONTENT_H + margin + margin) * 2.0f);
    EXPECT_EQ(pattern_->viewPortExtent_.Width(), (CONTENT_W + margin + margin) * 2.0f);
    auto rect = pattern_->GetItemRect(0);
    EXPECT_EQ(rect.Height(), CONTENT_H * 2.0f);
    EXPECT_EQ(rect.Width(), CONTENT_W * 2.0f);
    EXPECT_EQ(rect.Left(), margin * 2.0f);
    EXPECT_EQ(rect.Top(), margin * 2.0f);
}

/**
 * @tc.name: MaxMinZoomScaleTest001
 * @tc.desc: Test set max an min zoom scale.
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest,  MaxMinZoomScaleTest001)
{
    /**
     * @tc.step: step1. Create Scroll, set max an min zoom scale.
     * @tc.expected: pinch gesture initiated.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.5f);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_NE(pattern_->zoomCtrl_, nullptr);
    EXPECT_NE(pattern_->zoomCtrl_->pinchGesture_, nullptr);

    /**
     * @tc.step: step2. set max less than min zoom scale;
     * @tc.expected: scrollPattern zoomScale is nullopt;
     */
    ScrollModelNG::SetMinZoomScale(AceType::RawPtr(frameNode_), 1.0f);
    ScrollModelNG::SetMaxZoomScale(AceType::RawPtr(frameNode_), 1.0f);
    pattern_->OnModifyDone();
    EXPECT_EQ(pattern_->zoomCtrl_, nullptr);
}

/**
 * @tc.name: MaxMinZoomScaleTest002
 * @tc.desc: Test pinch gesture
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest,  MaxMinZoomScaleTest002)
{
    /**
     * @tc.step: step1. Create Scroll, set max an min zoom scale.
     * @tc.expected: pinch gesture initiated.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.0f);
    model.SetEnableBouncesZoom(false);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_NE(pattern_->zoomCtrl_, nullptr);
    EXPECT_NE(pattern_->zoomCtrl_->pinchGesture_, nullptr);

    /**
     * @tc.step: step2. Pinch to scale scroll view;
     * @tc.expected: scroll view scaled;
     */
    PinchStart(1.0f);
    PinchUpdate(2.0f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 2.0f);
    PinchUpdate(2.3f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 2.0f);
    PinchUpdate(0.4f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 0.5f);

    /**
     * @tc.step: step3. set maxZoomScale less than minZoomScale.
     * @tc.expected: scroll view not scale.
     */
    ScrollModelNG::SetMaxZoomScale(AceType::RawPtr(frameNode_), 0.5f);
    ScrollModelNG::SetMinZoomScale(AceType::RawPtr(frameNode_), 2.0f);
    PinchStart(1.0f);
    PinchUpdate(2.3f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 0.5f);
    PinchUpdate(1.0f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 0.5f);
    PinchUpdate(0.4f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 0.5f);

    /**
     * @tc.step: step4. set maxZoomScale and minZoomScale zero.
     * @tc.expected: scroll view not scale.
     */
    ScrollModelNG::SetMaxZoomScale(AceType::RawPtr(frameNode_), 0.0f);
    ScrollModelNG::SetMinZoomScale(AceType::RawPtr(frameNode_), 0.0f);
    EXPECT_EQ(pattern_->maxZoomScale_, 1.0f);
    EXPECT_EQ(pattern_->minZoomScale_, 1.0f);

    /**
     * @tc.step: step5. set maxZoomScale and minZoomScale negative.
     * @tc.expected: scroll view not scale.
     */
    ScrollModelNG::SetMaxZoomScale(AceType::RawPtr(frameNode_), -1.0f);
    ScrollModelNG::SetMinZoomScale(AceType::RawPtr(frameNode_), -1.0f);
    EXPECT_EQ(pattern_->maxZoomScale_, 1.0f);
    EXPECT_EQ(pattern_->minZoomScale_, 1.0f);
}

/**
 * @tc.name: MaxMinZoomScaleTest003
 * @tc.desc: Test pinch gesture
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest,  MaxMinZoomScaleTest003)
{
    /**
     * @tc.step: step1. Create Scroll, set max an min zoom scale.
     * @tc.expected: pinch gesture initiated.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.0f);
    model.SetEnableBouncesZoom(true);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_NE(pattern_->zoomCtrl_, nullptr);
    EXPECT_NE(pattern_->zoomCtrl_->pinchGesture_, nullptr);

    /**
     * @tc.step: step2. Pinch to scale scroll view;
     * @tc.expected: scroll view scaled;
     */
    PinchStart(1.0f);
    PinchUpdate(2.3f);
    EXPECT_GT(pattern_->zoomScale_.value(), 2.0f);
    EXPECT_LT(pattern_->zoomScale_.value(), 2.3f);
    PinchUpdate(1.5f);
    EXPECT_EQ(pattern_->zoomScale_.value(), 1.5f);
    PinchUpdate(0.4f);
    EXPECT_GT(pattern_->zoomScale_.value(), 0.4f);
    EXPECT_LT(pattern_->zoomScale_.value(), 0.5f);

    /**
     * @tc.step: step3. Pinch End
     * @tc.expected: Bounces to min zoom;
     */
    PinchEnd();
    EXPECT_EQ(pattern_->zoomScale_.value(), 0.5f);
}

/**
 * @tc.name: ZoomCenterTest001
 * @tc.desc: Test zoom center
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest,  ZoomCenterTest001)
{
    /**
     * @tc.step: step1. Create Scroll, set max an min zoom scale.
     * @tc.expected: pinch gesture initiated.
     */
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.5f);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();
    ASSERT_NE(pattern_->zoomCtrl_, nullptr);
    EXPECT_NE(pattern_->zoomCtrl_->pinchGesture_, nullptr);

    /**
     * @tc.step: step2. Pinch update
     * @tc.expected: currentOffset_ updated.
     */
    PinchStart(1.0f);
    PinchUpdate(1.5f, { 1000.0, 1000.0 }); /* 1000.0: center offset */
    FlushUITasks();
    EXPECT_EQ(pattern_->currentOffset_, -500.0); /* -500.0: current offset */
}

/**
 * @tc.name: CollectScrollableTouchTarget001
 * @tc.desc: Test CollectScrollableTouchTarget
 * @tc.type: FUNC
 */
TEST_F(ScrollZoomTest, CollectScrollableTouchTarget001)
{
    ScrollModelNG model = CreateScroll();
    model.SetEdgeEffect(EdgeEffect::SPRING, true);
    model.SetAxis(Axis::FREE);
    model.SetMinZoomScale(0.5f);
    model.SetMaxZoomScale(2.5f);
    CreateFreeContent({ CONTENT_W, CONTENT_H });
    CreateScrollDone();

    TouchTestResult res;
    ResponseLinkResult link;
    auto scrollHandler = pattern_->GetScrollableEvent();
    scrollHandler->CollectScrollableTouchTarget({}, nullptr, res, frameNode_, nullptr, link, 1);
    EXPECT_EQ(link.size(), 2); /* 2: result count */
    EXPECT_EQ(res.size(), 1);
    EXPECT_EQ(*res.begin(), pattern_->gestureGroup_);
}
} // namespace OHOS::Ace::NG
