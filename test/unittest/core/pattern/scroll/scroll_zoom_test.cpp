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

    static GestureEvent MakePinchGesture(float scale)
    {
        GestureEvent gesture;
        gesture.SetSourceTool(SourceTool::FINGER);
        gesture.SetInputEventType(InputEventType::TOUCH_SCREEN);
        gesture.SetGlobalPoint(Point(1, 1));
        gesture.SetGlobalLocation({ 1, 1 });
        gesture.SetLocalLocation({ 1, 1 });
        gesture.SetScale(scale);
        return gesture;
    }

    void PinchStart(float scale)
    {
        const auto& controller = pattern_->zoomCtrl_;
        auto gesture = MakePinchGesture(scale);
        ASSERT_TRUE(controller && controller->pinchGesture_);
        ASSERT_TRUE(controller->pinchGesture_->onActionStartId_);
        auto&& func = *(controller->pinchGesture_->onActionStartId_);
        func(gesture);
    }
    void PinchUpdate(float scale)
    {
        const auto& controller = pattern_->zoomCtrl_;
        auto gesture = MakePinchGesture(scale);
        ASSERT_TRUE(controller && controller->pinchGesture_);
        ASSERT_TRUE(controller->pinchGesture_->onActionUpdateId_);
        auto&& func = *(controller->pinchGesture_->onActionUpdateId_);
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
    EXPECT_EQ(pattern_->viewPortExtent_.Height(), CONTENT_H * 2.0f);
    EXPECT_EQ(pattern_->viewPortExtent_.Width(), CONTENT_W * 2.0f);

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
} // namespace OHOS::Ace::NG
