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
#include "test/mock/core/animation/mock_animation_manager.h"

#include "core/animation/spring_curve.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t SWIPE_ONE = 1;
constexpr int32_t SWIPE_THREE = 3;
} // namespace

class SwiperAnimationTestTwoNg : public SwiperTestNg {
public:
    static void SetUpTestSuite()
    {
        SwiperTestNg::SetUpTestSuite();
        MockAnimationManager::Enable(true);
        MockAnimationManager::GetInstance().SetTicks(2);
    }
    void CreateWithCustomAnimation();

    void SimulateSwipe(float offset, float velocity)
    {
        GestureEvent event;
        event.SetMainVelocity(velocity);
        event.SetMainDelta(offset);
        TouchLocationInfo touch(0);
        pattern_->HandleTouchDown({ touch });
        pattern_->panEvent_->actionStart_(event);
        pattern_->panEvent_->actionUpdate_(event);
        FlushUITasks();

        pattern_->HandleTouchUp();
        pattern_->panEvent_->actionEnd_(event);
    }
};

void SwiperAnimationTestTwoNg::CreateWithCustomAnimation()
{
    SwiperModelNG model = CreateSwiper();
    SwiperContentAnimatedTransition transitionInfo;
    transitionInfo.timeout = 0;
    transitionInfo.transition = [](const RefPtr<SwiperContentTransitionProxy>& proxy) {};
    model.SetCustomContentTransition(transitionInfo);
    auto onContentDidScroll = [](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {};
    model.SetOnContentDidScroll(std::move(onContentDidScroll));
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->contentMainSize_ = SWIPER_WIDTH;
    EXPECT_TRUE(pattern_->SupportSwiperCustomAnimation());
}

/**
 * @tc.name: GetCurrentIndex001
 * @tc.desc: Test GetCurrentIndex
 * @tc.desc: Test GetCurrentIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, GetCurrentIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);

    pattern_->targetIndex_ = SWIPE_ONE;
    pattern_->fastCurrentIndex_ = SWIPE_ONE;
    pattern_->currentIndex_ = 0;
    EXPECT_EQ(pattern_->GetCurrentIndex(true), SWIPE_ONE);

    pattern_->targetIndex_ = 0;
    pattern_->fastCurrentIndex_ = SWIPE_ONE;
    pattern_->currentIndex_ = 0;
    EXPECT_EQ(pattern_->GetCurrentIndex(true), pattern_->currentIndex_);
}

/**
 * @tc.name: IsInFastAnimation001
 * @tc.desc: Test IsInFastAnimation
 * @tc.desc: Test IsInFastAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, IsInFastAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);

    EXPECT_FALSE(pattern_->IsInFastAnimation());

    pattern_->tabAnimationMode_ = TabAnimateMode::CONTENT_FIRST_WITH_JUMP;
    pattern_->targetIndex_.reset();
    pattern_->propertyAnimationIsRunning_ = true;
    EXPECT_TRUE(pattern_->IsInFastAnimation());
    pattern_->propertyAnimationIsRunning_ = false;
    EXPECT_FALSE(pattern_->IsInFastAnimation());

    pattern_->targetIndex_ = 1;
    EXPECT_TRUE(pattern_->IsInFastAnimation());
    pattern_->propertyAnimationIsRunning_ = true;
    EXPECT_TRUE(pattern_->IsInFastAnimation());
    pattern_->propertyAnimationIsRunning_ = false;
    EXPECT_TRUE(pattern_->IsInFastAnimation());
}

/**
 * @tc.name: ComputeTargetIndex001
 * @tc.desc: Test ComputeTargetIndex
 * @tc.desc: Test ComputeTargetIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, ComputeTargetIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);

    int32_t targetIndex = 0;
    pattern_->targetIndex_ = SWIPE_ONE;
    pattern_->currentIndex_ = 0;
    EXPECT_TRUE(pattern_->ComputeTargetIndex(0, targetIndex));
    EXPECT_FALSE(pattern_->ComputeTargetIndex(SWIPE_ONE, targetIndex));
}

/**
 * @tc.name: ChangeIndex001
 * @tc.desc: Test ChangeIndex and SetSwiperToIndex
 * @tc.desc: Test ChangeIndex and SetSwiperToIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, ChangeIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    ASSERT_NE(controller_, nullptr);

    pattern_->targetIndex_ = SWIPE_ONE;
    pattern_->currentIndex_ = 0;
    controller_->ChangeIndex(SWIPE_ONE, SwiperAnimationMode::NO_ANIMATION);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);

    pattern_->targetIndex_ = SWIPE_ONE;
    pattern_->currentIndex_ = 0;
    controller_->ChangeIndex(SWIPE_THREE, SwiperAnimationMode::NO_ANIMATION);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, SWIPE_THREE), 0.0f);

    ASSERT_NE(frameNode_, nullptr);
    FrameNode* frameNode = static_cast<FrameNode*>(Referenced::RawPtr(frameNode_));
    ASSERT_NE(frameNode, nullptr);
    model.SetSwiperToIndex(frameNode, SWIPE_ONE, SwiperAnimationMode::NO_ANIMATION);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, SWIPE_ONE), 0.0f);
}

/**
 * @tc.name: CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, CalcComingIndex001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    GestureEvent event;
    event.SetMainDelta(-10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(-10.0f), 1);
    event.SetMainVelocity(0.0f);
    pattern_->HandleTouchUp();
    pattern_->panEvent_->actionEnd_(event);

    event.SetMainDelta(10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(10.0f), 3);
}

/**
 * @tc.name: CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, CalcComingIndex002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    GestureEvent event;
    event.SetMainDelta(10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(10.0f), 0);
    event.SetMainVelocity(0.0f);
    pattern_->HandleTouchUp();
    pattern_->panEvent_->actionEnd_(event);

    pattern_->SwipeToWithoutAnimation(3);
    FlushUITasks();

    event.SetMainDelta(-10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(-10.0f), 3);
}

/**
 * @tc.name: CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, CalcComingIndex003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    GestureEvent event;
    event.SetMainDelta(-10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(-10.0f), 2);
    event.SetMainVelocity(0.0f);
    pattern_->HandleTouchUp();
    pattern_->panEvent_->actionEnd_(event);

    event.SetMainDelta(10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(10.0f), 4);
}

/**
 * @tc.name: CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.desc: Test CalcComingIndex
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, CalcComingIndex004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems(5);
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    GestureEvent event;
    event.SetMainDelta(10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(10.0f), 0);
    event.SetMainVelocity(0.0f);
    pattern_->HandleTouchUp();
    pattern_->panEvent_->actionEnd_(event);

    pattern_->SwipeToWithoutAnimation(4);
    FlushUITasks();

    event.SetMainDelta(-10.0f);
    pattern_->panEvent_->actionStart_(event);
    pattern_->panEvent_->actionUpdate_(event);
    FlushUITasks();
    EXPECT_EQ(pattern_->CalcComingIndex(-10.0f), 4);
}

/**
 * @tc.name: CalcWillScrollOffset
 * @tc.desc: Test CalcWillScrollOffset
 * @tc.desc: Test CalcWillScrollOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestTwoNg, CalcWillScrollOffset001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    EXPECT_EQ(pattern_->CalcWillScrollOffset(1), 480.0f);
}
} // namespace OHOS::Ace::NG
