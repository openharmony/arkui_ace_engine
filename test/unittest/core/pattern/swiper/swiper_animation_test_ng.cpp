/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
class SwiperAnimationTestNg : public SwiperTestNg {
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

void SwiperAnimationTestNg::CreateWithCustomAnimation()
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
 * @tc.name: SwiperPatternSpringAnimation001
 * @tc.desc: Swiper spring animation is playing
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation002
 * @tc.desc: StopAndResetSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    SimulateSwipe(200.0f, 2000.0f);
    FlushUITasks();
    auto visibleSize = pattern_->CalculateVisibleSize();
    auto realOffset = 0.0f;
    if (visibleSize > 0.0f) {
        realOffset = 200.0f * SwiperHelper::CalculateFriction(200.0f / visibleSize);
    }
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset / 2));

    // change attribute during animation
    layoutProperty_->UpdateLoop(true);
    pattern_->OnModifyDone();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
}

/**
 * @tc.name: SwiperPatternSpringAnimation003
 * @tc.desc: StopSpringAnimationAndFlushImmediately
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation003, TestSize.Level1)
{
    CreateDefaultSwiper();
    double dragVelocity = 2000.0;
    pattern_->springAnimation_ = nullptr;
    pattern_->currentOffset_ = 1;
    pattern_->contentMainSize_ = 1.0f;
    struct SwiperItemInfo swiperItemInfo;
    swiperItemInfo.startPos = -1.0f;
    swiperItemInfo.endPos = -1.0f;
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo));
    pattern_->PlaySpringAnimation(dragVelocity);
    pattern_->StopSpringAnimationAndFlushImmediately();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    pattern_->springAnimationIsRunning_ = true;
    pattern_->StopSpringAnimationAndFlushImmediately();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation004
 * @tc.desc: StopSpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    SimulateSwipe(100.0f, 1000.0f);
    auto visibleSize = pattern_->CalculateVisibleSize();
    auto realOffset = 0.0f;
    if (visibleSize > 0.0f) {
        realOffset = 100.0f * SwiperHelper::CalculateFriction(100.0f / visibleSize);
    }
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    pattern_->StopSpringAnimation();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearZero(GetChildX(frameNode_, 0)));

    pattern_->springOffset_ = 0.0f;
    SimulateSwipe(100.0f, 1000.0f);
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    pattern_->StopSpringAnimationImmediately();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 0), realOffset));
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternSpringAnimation005
 * @tc.desc: Test overScroll with displayCount > itemCnt
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation005, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(12);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 40.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 9), 40.0f);
    EXPECT_EQ(GetChildX(frameNode_, 9), 360.0f);
    pattern_->UpdateCurrentOffset(-200.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 9), 160.0f);
    pattern_->PlaySpringAnimation(200.0f);
    // left align because children total size < swiper
    EXPECT_EQ(
        AceType::DynamicCast<NodeAnimatablePropertyFloat>(frameNode_->GetAnimatablePropertyFloat("spring"))->Get(),
        0.0f);
}

/**
 * @tc.name: SwiperPatternSpringAnimation006
 * @tc.desc: Test overScroll with displayCount > itemCnt
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation006, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(12);
    CreateSwiperItems(10);
    CreateSwiperDone();
    EXPECT_EQ(GetChildWidth(frameNode_, 0), 40.0f);
    EXPECT_EQ(GetChildWidth(frameNode_, 9), 40.0f);
    EXPECT_EQ(GetChildX(frameNode_, 9), 360.0f);
    pattern_->UpdateCurrentOffset(200.0f);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 200.0f);
    pattern_->PlaySpringAnimation(200.0f);
    EXPECT_EQ(
        AceType::DynamicCast<NodeAnimatablePropertyFloat>(frameNode_->GetAnimatablePropertyFloat("spring"))->Get(),
        0.0f);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation001
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlayFadeAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->fadeOffset_ = 0.0f;
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->PlayFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayFadeAnimation002
 * @tc.desc: PlayFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlayFadeAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetEdgeEffect(EdgeEffect::FADE);
    model.SetLoop(false);
    CreateSwiperItems();
    CreateSwiperDone();
    SimulateSwipe(100.0f, 500.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(pattern_->fadeOffset_, 100.0f);

    EXPECT_TRUE(pattern_->fadeAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(pattern_->fadeOffset_, 50.0f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_EQ(pattern_->fadeOffset_, 0.0f);
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternStopFadeAnimation001
 * @tc.desc: StopFadeAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternStopFadeAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->fadeAnimationIsRunning_ = true;
    pattern_->StopFadeAnimation();
    EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation001
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlayPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    layoutProperty_->UpdateDirection(Axis::HORIZONTAL);
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.2f;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));

    /**
     * @tc.steps: step2. call PlayPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
        layoutProperty_->UpdateDirection(Axis::VERTICAL);
    }
}

/**
 * @tc.name: SwiperPatternUpdateOffsetAfterPropertyAnimation001
 * @tc.desc: UpdateOffsetAfterPropertyAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternUpdateOffsetAfterPropertyAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    float offset = 0.1f;

    /**
     * @tc.steps: step2. call UpdateOffsetAfterPropertyAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->UpdateOffsetAfterPropertyAnimation(offset);
}

/**
 * @tc.name: SwiperPatternOnPropertyTranslateAnimationFinish001
 * @tc.desc: OnPropertyTranslateAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternOnPropertyTranslateAnimationFinish001, TestSize.Level1)
{
    CreateDefaultSwiper();
    auto offset = OffsetF(0.1f, 0.2f);
    pattern_->propertyAnimationIsRunning_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call OnPropertyTranslateAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnPropertyTranslateAnimationFinish(offset);
        pattern_->propertyAnimationIsRunning_ = true;
    }
}

/**
 * @tc.name: SwiperPatternStopPropertyTranslateAnimation001
 * @tc.desc: StopPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternStopPropertyTranslateAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->propertyAnimationIsRunning_ = false;
    struct SwiperItemInfo swiperItemInfo1;
    swiperItemInfo1.startPos = -1.0f;
    swiperItemInfo1.endPos = -1.0f;
    swiperItemInfo1.node = nullptr;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo2.startPos = -1.0f;
    swiperItemInfo2.endPos = -1.0f;
    swiperItemInfo2.node =
        FrameNode::GetOrCreateFrameNode("Swiper", 0, []() { return AceType::MakeRefPtr<SwiperPattern>(); });
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(2, swiperItemInfo2));
    ASSERT_NE(pattern_->itemPosition_.rbegin()->second.node, nullptr);

    /**
     * @tc.steps: step2. call StopPropertyTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->StopPropertyTranslateAnimation(false);
        pattern_->propertyAnimationIsRunning_ = true;
    }
}

/**
 * @tc.name: SwiperPatternGetCurveIncludeMotion001
 * @tc.desc: GetCurveIncludeMotion
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternGetCurveIncludeMotion001, TestSize.Level1)
{
    CreateDefaultSwiper();
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(nullptr);
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);
    auto curve2 = AceType::MakeRefPtr<InterpolatingSpring>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call GetCurveIncludeMotion.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->GetCurveIncludeMotion();
                if (i == 1) {
                    curve2->UpdateVelocity(-0.1f);
                    continue;
                }
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
                curve1->UpdateVelocity(-0.1f);
            }
            curve1->UpdateVelocity(0.1f);
        }
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve2);
        curve2->UpdateVelocity(0.1f);
    }
}

/**
 * @tc.name: SwiperPatternPlayTranslateAnimation001
 * @tc.desc: PlayTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlayTranslateAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    float startPos = 0.1f;
    float endPos = 0.2f;
    int32_t nextIndex = 1;
    bool restartAutoPlay = true;
    float velocity = 0.1f;
    float mass = 0.1f;
    float stiffness = 0.2f;
    float damping = 0.3f;
    pattern_->controller_ = nullptr;
    auto curve1 = AceType::MakeRefPtr<SpringCurve>(velocity, mass, stiffness, damping);

    /**
     * @tc.steps: step2. call PlayTranslateAnimation.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
        pattern_->controller_ = AceType::MakeRefPtr<Animator>();
        frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateCurve(curve1);
    }
    pattern_->PlayTranslateAnimation(startPos, startPos, nextIndex, restartAutoPlay, velocity);
    pattern_->translateAnimationIsRunning_ = true;
    pattern_->PlayTranslateAnimation(startPos, endPos, nextIndex, restartAutoPlay, velocity);
}

/**
 * @tc.name: SwiperPatternUpdateAnimationProperty001
 * @tc.desc: UpdateAnimationProperty
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternUpdateAnimationProperty001, TestSize.Level1)
{
    CreateDefaultSwiper();
    struct SwiperItemInfo swiperItemInfo1 {
        0.1f, 0.2f
    };
    pattern_->isDragging_ = true;
    float velocity = 0.1f;

    /**
     * @tc.steps: step2. call UpdateAnimationProperty.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j >= 1; j++) {
            for (int k = 0; k <= 1; k++) {
                pattern_->UpdateAnimationProperty(velocity);
                pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo1));
                if (i == 1) {
                    velocity = -1300;
                    continue;
                }
                if (i == 1 && j == 1) {
                    break;
                }
                velocity = 0.0f;
            }
            if (i == 1) {
                pattern_->isDragging_ = false;
                continue;
            }
            velocity = 0.1f;
        }
        velocity = 1300;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToLeft001
 * @tc.desc: TriggerAnimationEndOnSwipeToLeft
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternTriggerAnimationEndOnSwipeToLeft001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToLeft.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToLeft();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnSwipeToRight001
 * @tc.desc: TriggerAnimationEndOnSwipeToRight
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternTriggerAnimationEndOnSwipeToRight001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnSwipeToRight.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->TriggerAnimationEndOnSwipeToRight();
        pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 4 }));
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAnimationStart001
 * @tc.desc: OnSpringAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternOnSpringAnimationStart001, TestSize.Level1)
{
    CreateWithArrow();
    layoutProperty_->UpdateShowIndicator(false);
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    float velocity = 200.0f;
    pattern_->itemPosition_.emplace(std::make_pair(-1, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->OnSpringAnimationStart(velocity);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnSpringAndFadeAnimationFinish001
 * @tc.desc: OnSpringAndFadeAnimationFinish
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternOnSpringAndFadeAnimationFinish001, TestSize.Level1)
{
    CreateWithArrow();
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnSpringAndFadeAnimationFinish.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = true;
        pattern_->OnSpringAndFadeAnimationFinish();
        EXPECT_FALSE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternOnFadeAnimationStart001
 * @tc.desc: OnFadeAnimationStart
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternOnFadeAnimationStart001, TestSize.Level1)
{
    CreateWithArrow();
    pattern_->itemPosition_.emplace(std::make_pair(0, SwiperItemInfo { -1, 1 }));
    pattern_->currentIndex_ = 1;

    /**
     * @tc.steps: step2. call OnFadeAnimationStart.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        pattern_->fadeAnimationIsRunning_ = false;
        pattern_->OnFadeAnimationStart();
        EXPECT_TRUE(pattern_->fadeAnimationIsRunning_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternTriggerAnimationEndOnForceStop001
 * @tc.desc: TriggerAnimationEndOnForceStop
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternTriggerAnimationEndOnForceStop001, TestSize.Level1)
{
    CreateWithArrow();
    pattern_->UpdateIndexOnSwipePageStop(1);
    pattern_->currentIndex_ = 0;
    pattern_->pauseTargetIndex_ = 2;
    pattern_->itemPosition_.clear();

    /**
     * @tc.steps: step2. call TriggerAnimationEndOnForceStop.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->TriggerAnimationEndOnForceStop();
            pattern_->currentIndex_ = 1;
        }
        frameNode_->AddChild(rightArrowNode_);
        pattern_->currentIndex_ = 0;
    }
}

/**
 * @tc.name: SwiperPatternPlayPropertyTranslateAnimation002
 * @tc.desc: PlayPropertyTranslateAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlayPropertyTranslateAnimation002, TestSize.Level1)
{
    CreateDefaultSwiper();
    float translate = 0.1f;
    int32_t nextIndex = 1;
    float velocity = 0.1f;
    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->targetIndex_ = 1;
    pattern_->itemPositionInAnimation_ = pattern_->itemPosition_;
    pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);

    /**
     * @tc.steps: step2. call HandleTouchDown.
     * @tc.expected: Related function runs ok.
     */
    pattern_->itemPositionInAnimation_.clear();
    pattern_->PlayPropertyTranslateAnimation(translate, nextIndex, velocity);
}

/**
 * @tc.name: SwiperPatternPlaySpringAnimation001
 * @tc.desc: PlaySpringAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternPlaySpringAnimation001, TestSize.Level1)
{
    CreateDefaultSwiper();
    pattern_->contentMainSize_ = 1.0f;
    pattern_->itemPosition_.clear();
    layoutProperty_->UpdatePrevMargin(Dimension(0.0f));
    layoutProperty_->UpdateNextMargin(Dimension(0.0f));
    double dragVelocity = 0.1f;

    /**
     * @tc.steps: step2. call PlaySpringAnimation.
     * @tc.expected: Related function runs ok.
     */
    pattern_->PlaySpringAnimation(dragVelocity);
}

/**
 * @tc.name: SwiperAutoLinearAnimationNeedReset001
 * @tc.desc: AutoLinearAnimationNeedReset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperAutoLinearAnimationNeedReset001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Empty items
     * @tc.expected: AutoLinearAnimationNeedReset return false
     */
    CreateSwiper();
    CreateSwiperDone();
    EXPECT_TRUE(pattern_->itemPosition_.empty());
    EXPECT_FALSE(pattern_->AutoLinearAnimationNeedReset(1.f));
}

/**
 * @tc.name: SwiperAutoLinearAnimationNeedReset002
 * @tc.desc: AutoLinearAnimationNeedReset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperAutoLinearAnimationNeedReset002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has items, but !IsAutoLinear
     * @tc.expected: AutoLinearAnimationNeedReset return false
     */
    CreateDefaultSwiper();
    EXPECT_FALSE(pattern_->AutoLinearAnimationNeedReset(1.f));
}

/**
 * @tc.name: SwiperAutoLinearAnimationNeedReset003
 * @tc.desc: AutoLinearAnimationNeedReset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperAutoLinearAnimationNeedReset003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Has items and IsAutoLinear
     */
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. translate <= 0
     * @tc.expected: AutoLinearAnimationNeedReset return false
     */
    EXPECT_FALSE(pattern_->AutoLinearAnimationNeedReset(0.f));

    /**
     * @tc.steps: step3. translate > 0, but endPos - CalculateVisibleSize() > translate
     * @tc.expected: AutoLinearAnimationNeedReset return false
     */
    EXPECT_FALSE(pattern_->AutoLinearAnimationNeedReset(1.f));

    /**
     * @tc.steps: step4. translate > 0 and endPos - CalculateVisibleSize() < translate
     * @tc.expected: AutoLinearAnimationNeedReset return false
     */
    ChangeIndex(3);
    EXPECT_FALSE(pattern_->AutoLinearAnimationNeedReset(SWIPER_WIDTH * 100 + 1.f));
}

/**
 * @tc.name: SwipeCustomAnimationTest001
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwipeCustomAnimationTest001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set SetCustomContentTransition interface
     */
    CreateWithCustomAnimation();

    /**
     * @tc.steps: step2. set loop to true, displayCount to 2 and swipeByGroup to true, init itemPosition map info.
     */
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->UpdateDisplayCount(2);
    layoutProperty_->UpdateSwipeByGroup(true);

    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    swiperItemInfo1.startPos = 0.0f;
    swiperItemInfo1.endPos = SWIPER_WIDTH / 2;
    swiperItemInfo2.startPos = SWIPER_WIDTH / 2;
    swiperItemInfo2.endPos = SWIPER_WIDTH;
    pattern_->itemPosition_.clear();
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo2));

    /**
     * @tc.steps: step3. set different offset, calculate and update itemPositionInAnimation info.
     */
    auto offset1 = -10.0f;
    pattern_->HandleSwiperCustomAnimation(offset1);
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[3].startPos, SWIPER_WIDTH * 3 / 2 + offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[3].endPos, SWIPER_WIDTH * 2 + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset2 = 20.0f;
    pattern_->HandleSwiperCustomAnimation(offset2);
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].startPos, offset1 + offset2 - SWIPER_WIDTH);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].endPos, offset1 + offset2 - SWIPER_WIDTH / 2);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset3 = -10.0f;
    pattern_->HandleSwiperCustomAnimation(offset3);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].startPos, 0.0f);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[0].endPos, SWIPER_WIDTH / 2);
}

/**
 * @tc.name: SwipeCustomAnimationTest002
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwipeCustomAnimationTest002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. create swiper and set SetCustomContentTransition interface
     */
    CreateWithCustomAnimation();

    /**
     * @tc.steps: step2. set loop to true, itemSpace to 10, prevMargin to 20, nextMargin to 30,
     * init itemPosition map info.
     */
    layoutProperty_->UpdateLoop(true);
    auto itemSpace = 10.0f;
    auto prevMargin = 20.0f;
    auto nextMargin = 30.0f;
    layoutProperty_->UpdateItemSpace(Dimension(itemSpace));
    layoutProperty_->UpdatePrevMargin(Dimension(prevMargin));
    layoutProperty_->UpdateNextMargin(Dimension(nextMargin));

    auto mainAxisLength = SWIPER_WIDTH - prevMargin - nextMargin - itemSpace * 2;
    struct SwiperItemInfo swiperItemInfo1;
    struct SwiperItemInfo swiperItemInfo2;
    struct SwiperItemInfo swiperItemInfo3;
    swiperItemInfo1.startPos = -mainAxisLength - itemSpace;
    swiperItemInfo1.endPos = -itemSpace;
    swiperItemInfo2.startPos = 0.0f;
    swiperItemInfo2.endPos = mainAxisLength;
    swiperItemInfo3.startPos = mainAxisLength + itemSpace;
    swiperItemInfo3.endPos = mainAxisLength * 2 + itemSpace;
    pattern_->itemPosition_.clear();
    pattern_->itemPosition_.emplace(std::make_pair(3, swiperItemInfo1));
    pattern_->itemPosition_.emplace(std::make_pair(0, swiperItemInfo2));
    pattern_->itemPosition_.emplace(std::make_pair(1, swiperItemInfo3));

    /**
     * @tc.steps: step3. set different offset, calculate and update itemPositionInAnimation info.
     */
    auto offset1 = -400.0f;
    pattern_->HandleSwiperCustomAnimation(offset1);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].startPos, mainAxisLength * 2 + itemSpace * 2 + offset1);
    EXPECT_EQ(pattern_->itemPositionInAnimation_[2].endPos, mainAxisLength * 3 + itemSpace * 2 + offset1);
    pattern_->itemPosition_ = pattern_->itemPositionInAnimation_;

    auto offset2 = 500.0f;
    pattern_->HandleSwiperCustomAnimation(offset2);
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(1) == pattern_->itemPositionInAnimation_.end());
    EXPECT_TRUE(pattern_->itemPositionInAnimation_.find(2) == pattern_->itemPositionInAnimation_.end());
    EXPECT_FALSE(pattern_->itemPositionInAnimation_.find(3) == pattern_->itemPositionInAnimation_.end());
    EXPECT_EQ(
        pattern_->itemPositionInAnimation_.find(3)->second.startPos, -itemSpace - mainAxisLength + offset1 + offset2);
    EXPECT_EQ(pattern_->itemPositionInAnimation_.find(3)->second.endPos, -itemSpace + offset1 + offset2);
}

/**
 * @tc.name: SwipeCustomAnimationTest003
 * @tc.desc: Test check itemPositionInAnimation map info
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwipeCustomAnimationTest003, TestSize.Level1)
{
    bool isTrigger = false;
    auto onContentDidScroll = [&isTrigger](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        isTrigger = true;
    };
    SwiperModelNG model = CreateSwiper();
    SwiperContentAnimatedTransition transitionInfo;
    transitionInfo.timeout = 0;
    transitionInfo.transition = [](const RefPtr<SwiperContentTransitionProxy>& proxy) {};
    model.SetLoop(false);
    model.SetEdgeEffect(EdgeEffect::FADE);
    model.SetCustomContentTransition(transitionInfo);
    model.SetOnContentDidScroll(std::move(onContentDidScroll));
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step2. set isDragging to true
     */
    pattern_->isDragging_ = true;

    /**
     * @tc.steps: step3. calculate and update itemPositionInAnimation info.
     */
    auto offset1 = -10.0f;
    pattern_->UpdateCurrentOffset(offset1);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), offset1);
    EXPECT_TRUE(isTrigger);

    isTrigger = false;
    auto offset2 = 20.0f;
    pattern_->UpdateCurrentOffset(offset2);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);
    EXPECT_TRUE(isTrigger);

    /**
     * @tc.steps: step4. set different offset without edge effect, calculate and update itemPositionInAnimation info.
     */
    paintProperty_->UpdateEdgeEffect(EdgeEffect::NONE);

    pattern_->UpdateCurrentOffset(offset1);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), offset1);

    pattern_->UpdateCurrentOffset(offset2);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.f);

    /**
     * @tc.steps: step5. set different offset in spring edge effect, calculate and update itemPositionInAnimation info.
     */
    paintProperty_->UpdateEdgeEffect(EdgeEffect::SPRING);

    pattern_->UpdateCurrentOffset(offset1);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), offset1);

    pattern_->UpdateCurrentOffset(offset2);
    FlushUITasks();
    EXPECT_GT(GetChildX(frameNode_, 0), 0.f);
    EXPECT_LT(GetChildX(frameNode_, 0), offset2 + offset1);
}

/**
 * @tc.name: SwiperPattern0009
 * @tc.desc: Test pattern StopAndResetSpringAnimation.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPattern0009, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateDefaultSwiper();
    pattern_->springAnimationIsRunning_ = true;
    pattern_->StopAndResetSpringAnimation();
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
}

/**
 * @tc.name: SwiperPattern0010
 * @tc.desc: Test pattern SetIsIndicatorCustomSize.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPattern0010, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Default value
     */
    CreateDefaultSwiper();
    bool isCustomSize = true;
    pattern_->SetIsIndicatorCustomSize(isCustomSize);
    EXPECT_TRUE(pattern_->isCustomSize_);
}

/**
 * @tc.name: SwiperPatternSwipeTo001
 * @tc.desc: SwipeTo
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSwipeTo001, TestSize.Level1)
{
    CreateWithArrow();
    int32_t index = -1;
    layoutProperty_->UpdateLoop(true);
    pattern_->currentIndex_ = 1;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateShowIndicator(false);
    layoutProperty_->UpdateMinSize(Dimension(1));
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);

    /**
     * @tc.steps: step2. call SwipeTo.
     * @tc.expected: Related function runs ok.
     */
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(0);
                continue;
            }
            pattern_->itemPosition_.emplace(std::make_pair(1, SwiperItemInfo { 1, 2 }));
            pattern_->itemPosition_.emplace(std::make_pair(-2, SwiperItemInfo { 1, 2 }));
            frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateDuration(400);
        }
        pattern_->isVisible_ = true;
    }

    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                pattern_->rightButtonId_ = 1;
                continue;
            }
            pattern_->SwipeTo(index);
            index = 2;
        }
        index = -1;
    }

    pattern_->rightButtonId_.reset();
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateDisplayCount(1);
    pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(false);
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            pattern_->SwipeTo(index);
            if (i == 1) {
                break;
            }
            pattern_->GetLayoutProperty<SwiperLayoutProperty>()->UpdateLoop(true);
            pattern_->currentIndex_ = 0;
        }
        pattern_->currentIndex_ = 1;
    }

    pattern_->propertyAnimationIsRunning_ = true;
    pattern_->SwipeTo(index);
    layoutProperty_->UpdateIsCustomAnimation(true);
    pattern_->SwipeTo(1);
    pattern_->TriggerCustomContentTransitionEvent(0, 1);
    pattern_->OnCustomAnimationFinish(0, 1, false);
}

/**
 * @tc.name: SwiperPatternAutoPlay001
 * @tc.desc: StopAutoPlay and StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternAutoPlay001, TestSize.Level1)
{
    CreateDefaultSwiper();
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    pattern_->isVisible_ = true;

    /**
     * @tc.steps: step2. call InitTouchEvent.
     * @tc.expected: Related function runs ok.
     */
    pattern_->StopAutoPlay();
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: SwiperPatternAutoPlay002
 * @tc.desc: StartAutoPlay
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternAutoPlay002, TestSize.Level1)
{
    CreateWithArrow();
    frameNode_->GetPaintProperty<SwiperPaintProperty>()->UpdateAutoPlay(true);
    layoutProperty_->UpdateLoop(true);
    layoutProperty_->ResetDisplayCount();
    layoutProperty_->ResetMinSize();
    layoutProperty_->UpdateDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
    pattern_->isVisible_ = true;
    pattern_->isIndicatorLongPress_ = false;
    pattern_->leftButtonId_.reset();
    pattern_->rightButtonId_.reset();
    layoutProperty_->UpdateShowIndicator(false);

    /**
     * @tc.steps: step2. call StartAutoPlay.
     * @tc.expected: Related functions run ok.
     */
    pattern_->StartAutoPlay();
}

/**
 * @tc.name: StopTranslateAnimation001
 * @tc.desc: Swipe with animate, than forceStop animation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, StopTranslateAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems();
    CreateSwiperDone();
    pattern_->isVisibleArea_ = true;

    /**
     * @tc.steps: step1. ShowPrevious with animate, than forceStop animation
     */
    pattern_->ShowPrevious();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 2), -480.0f);
    EXPECT_EQ(GetChildX(frameNode_, 3), -240.0f);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(
            GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty(), OffsetF(240.0f, 0.0f));
    }
    pattern_->FinishAnimation();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    // jumped to final position
    EXPECT_EQ(pattern_->currentIndex_, -2);
    EXPECT_EQ(GetChildX(frameNode_, 2), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 3), 240.0f);

    /**
     * @tc.steps: step2. ShowNext with animate
     */
    pattern_->ShowNext();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    for (int i = 0; i < 4; ++i) {
        EXPECT_EQ(
            GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty(), OffsetF(-240.0f, 0.0f));
    }
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    FlushUITasks();
    EXPECT_FALSE(GetChildFrameNode(frameNode_, 3)->IsActive());
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}
} // namespace OHOS::Ace::NG
