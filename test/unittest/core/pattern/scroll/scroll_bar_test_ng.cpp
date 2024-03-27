/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float BAR_WIDTH = 10.f;
} // namespace

class ScrolleBarTestNg : public ScrollTestNg {
public:
    void CreateWithBar();
    void ClickBar(Offset point);
};

void ScrolleBarTestNg::CreateWithBar()
{
    CreateWithContent([](ScrollModelNG model) {
        model.SetDisplayMode(static_cast<int>(DisplayMode::ON));
        model.SetScrollBarWidth(Dimension(BAR_WIDTH));
    });
    scrollBar_ = pattern_->GetScrollBar();
}

void ScrolleBarTestNg::ClickBar(Offset point)
{
    GestureEvent info;
    info.SetLocalLocation(point);
    pattern_->HandleClickEvent(info); // will trigger CheckBarDirection
}

/**
 * @tc.name: ClickBar001
 * @tc.desc: Test CheckBarDirection by HandleClickEvent, component will scroll by click bar
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, ClickBar001, TestSize.Level1)
{
    CreateWithBar();
    EXPECT_TRUE(IsEqual(scrollBar_->GetTouchRegion(), Rect(470.f, 0.f, 10.f, 640.f)));
    const float pointInBarX = scrollBar_->GetTouchRegion().Left() + BAR_WIDTH / 2;
    pattern_->isMousePressed_ = true;

    /**
     * @tc.steps: step1. Click not in bar
     * @tc.expected: Not scroll
     */
    ClickBar(Offset::Zero());
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));

    /**
     * @tc.steps: step2. Click in bar
     * @tc.expected: Not scroll
     */
    ClickBar(Offset(pointInBarX, 10.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, 0.f));

    /**
     * @tc.steps: step3. Click below bar
     * @tc.expected: Scroll page down
     */
    ClickBar(Offset(pointInBarX, 700.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, SCROLL_HEIGHT)); // 800.f

    /**
     * @tc.steps: step4. Scroll down and Click above bar
     * @tc.expected: Scroll page up
     */
    ScrollTo(ITEM_HEIGHT);
    ClickBar(Offset(pointInBarX, 1.f));
    EXPECT_TRUE(IsEqual(pattern_->finalPosition_, ITEM_HEIGHT - SCROLL_HEIGHT)); // -700.f
}

/**
 * @tc.name: HandleDrag001
 * @tc.desc: Test handleDrag
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, HandleDrag001, TestSize.Level1)
{
    CreateWithBar();
    auto HandleDragStart = *(scrollBar_->panRecognizer_->onActionStart_);
    auto HandleDragUpdate = *(scrollBar_->panRecognizer_->onActionUpdate_);
    auto HandleDragEnd = *(scrollBar_->panRecognizer_->onActionEnd_);

    /**
     * @tc.steps: step1. HandleDrag with Velocity
     * @tc.expected: PlayMotion
     */
    GestureEvent info;
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);

    HandleDragUpdate(info);
    info.SetMainVelocity(1000.f);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsRunning());

    /**
     * @tc.steps: step2. HandleDrag with Velocity again
     * @tc.expected: trigger ProcessFrictionMotion and PlayMotion
     */
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);

    HandleDragUpdate(info);
    info.SetMainVelocity(1000.f);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsRunning());
    scrollBar_->ProcessFrictionMotion(10.f);
    EXPECT_EQ(scrollBar_->frictionPosition_, 10.f);

    /**
     * @tc.steps: step3. HandleDragStart with Velocity:0 or InputEventType::AXIS
     * @tc.expected: Not PlayMotion
     */
    HandleDragStart(info);
    EXPECT_TRUE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());

    HandleDragUpdate(info);
    info.SetMainVelocity(0.f);
    HandleDragEnd(info);
    EXPECT_FALSE(scrollBar_->isDriving_);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());

    info.SetMainVelocity(1000.f);
    info.SetInputEventType(InputEventType::AXIS);
    HandleDragEnd(info);
    EXPECT_TRUE(scrollBar_->frictionController_->IsStopped());
}

/**
 * @tc.name: OnCollectTouchTarget001
 * @tc.desc: Test OnCollectTouchTarget
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleBarTestNg, OnCollectTouchTarget001, TestSize.Level1)
{
    CreateWithBar();
    OffsetF coordinateOffset;
    GetEventTargetImpl getEventTargetImpl;
    TouchTestResult result;
    pattern_->scrollableEvent_->BarCollectTouchTarget(
        coordinateOffset, getEventTargetImpl, result, frameNode_, nullptr);
    EXPECT_EQ(result.size(), 1);
}
} // namespace OHOS::Ace::NG
