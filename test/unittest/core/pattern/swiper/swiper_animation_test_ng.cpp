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
constexpr int32_t SWIPE_FOUR = 4;
} // namespace

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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
 * @tc.name: SwiperPatternSpringAnimation007
 * @tc.desc: Test spring animation multiple interupting and restart.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, SwiperPatternSpringAnimation007, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetLoop(false);
    CreateSwiperItems(5);
    CreateSwiperDone();
    controller_->ChangeIndex(4, false);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 4), 0.0f);
    // swiper to left, trigger spring animation
    SimulateSwipe(-100.0f, -100.0f);
    FlushUITasks();
    auto visibleSize = pattern_->CalculateVisibleSize();
    ASSERT_TRUE(visibleSize > 0.0f);
    auto realOffset = -100.0f * SwiperHelper::CalculateFriction(100.0f / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset / 2));

    // swipe again during spring animation
    auto tempSpringOffset = pattern_->EstimateSpringOffset(realOffset / 2) - 100;
    SimulateSwipe(-100.0f, -100.0f);
    FlushUITasks();
    realOffset = tempSpringOffset * SwiperHelper::CalculateFriction(std::abs(tempSpringOffset) / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset / 2));

    // swipe again during spring animation
    tempSpringOffset = pattern_->EstimateSpringOffset(realOffset / 2) - 100;
    SimulateSwipe(-100.0f, -100.0f);
    FlushUITasks();
    realOffset = tempSpringOffset * SwiperHelper::CalculateFriction(std::abs(tempSpringOffset) / visibleSize);
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset));
    EXPECT_TRUE(pattern_->springAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), realOffset / 2));

    // check offset after spring animation finished
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->springAnimationIsRunning_);
    FlushUITasks();
    EXPECT_TRUE(NearEqual(GetChildX(frameNode_, 4), 0.0f));
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
    CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
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
    EXPECT_TRUE(frameNode_);
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

/**
 * @tc.name: ShowNextAnimation
 * @tc.desc: Start property animation with showNext.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowNextAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(2);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);

    controller_->ShowNext();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), -420.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: ShowNextAnimation
 * @tc.desc: Start frame animation with showNext when has capture nodes, and interupt with showNext.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowNextAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(2);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);

    // has capture nodes, use frame animation.
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    // interupt animation with another showNext
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    // expecting restart frame animation from index 1
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), -200.0f);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), -420.0f);
    EXPECT_EQ(pattern_->currentIndex_, 2);
}

/**
 * @tc.name: ShowNextAnimation
 * @tc.desc: Start frame animation with showNext when targetIndex not available in itemPosition,
 *           and interupt with showNext.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowNextAnimation003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(3);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), -420.0f);

    // swiper has 3 child nodes and margin value, use frame animation also.
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 2);
    EXPECT_EQ(GetChildX(frameNode_, 0), -200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    // interupt animation with another showNext
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), -420.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);

    // expecting restart frame animation from index 1
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 3); // should be 2, don't know why is 3
    EXPECT_EQ(GetChildX(frameNode_, 1), -200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 240.0f);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 1), -420.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 460.0f);
    EXPECT_EQ(pattern_->currentIndex_, 2);
}

/**
 * @tc.name: ShowNextAnimation
 * @tc.desc: Change to last item with showNext and interupt it with partly refresh
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowNextAnimation004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateIndex(0);
    CreateSwiperItems(2);
    CreateSwiperDone();
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);

    controller_->ShowNext();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(
            GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty(), OffsetF(-240.0f, 0.0f));
    }
    EXPECT_EQ(pattern_->currentIndex_, 0);

    TouchLocationInfo touch(0);
    pattern_->HandleTouchDown({ touch });
    FlushUITasks();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    // stop animation with partly refresh
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(SWIPER_HEIGHT)));
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateIndex(0);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 0);
    EXPECT_EQ(pattern_->currentIndex_, 0);
    pattern_->HandleTouchUp();

    // check showNext function
    controller_->ShowNext();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);
    EXPECT_EQ(pattern_->currentIndex_, 1);
}

/**
 * @tc.name: ShowPreviousAnimation
 * @tc.desc: Start property animation with showPrevious.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowPreviousAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(2);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);

    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 680.0f);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(pattern_->currentIndex_, -1);
}

/**
 * @tc.name: ShowPreviousAnimation
 * @tc.desc: Start frame animation with showPrevious when has capture nodes, and interupt with showPrevious.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowPreviousAnimation002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(2);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);

    // has capture nodes, use frame animation.
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 680.0f);

    // interupt animation with another ShowPrevious
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(pattern_->currentIndex_, -1);

    // expecting restart frame animation from index -1
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 680.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);
    EXPECT_EQ(pattern_->currentIndex_, -2);
}

/**
 * @tc.name: ShowPreviousAnimation
 * @tc.desc: Start frame animation with showPrevious when targetIndex not available in itemPosition,
 *           and interupt with showPrevious.
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowPreviousAnimation003, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems(3);
    CreateSwiperDone();
    float margin = 20.0f;
    layoutProperty_->UpdatePrevMargin(Dimension(margin));
    layoutProperty_->UpdateNextMargin(Dimension(margin));
    layoutProperty_->UpdateLoop(true);
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 0), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), -420.0f);

    // swiper has 3 child nodes and margin value, use frame animation also.
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 3); // should be 2, don't know why is 3
    EXPECT_EQ(GetChildX(frameNode_, 0), 240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), -200.0f);

    // interupt animation with another ShowPrevious
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 2), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 0), 460.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), -420.0f);
    EXPECT_EQ(pattern_->currentIndex_, -1);

    // expecting restart frame animation from index -1
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 3); // should be 2, don't know why is 3
    EXPECT_EQ(GetChildX(frameNode_, 1), -200.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 240.0f);

    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    EXPECT_FALSE(pattern_->translateAnimationIsRunning_);
    FlushUITasks();
    EXPECT_EQ(pattern_->itemPosition_.size(), 3);
    EXPECT_EQ(GetChildX(frameNode_, 0), -420.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 20.0f);
    EXPECT_EQ(GetChildX(frameNode_, 2), 460.0f);
    EXPECT_EQ(pattern_->currentIndex_, -2);
}

/**
 * @tc.name: ShowPreviousAnimation
 * @tc.desc: Change to last item with showPrevious and interupt it with partly refresh
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, ShowPreviousAnimation004, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateIndex(1);
    CreateSwiperItems(2);
    CreateSwiperDone();
    frameNode_->MarkModifyDone();
    FlushUITasks();

    EXPECT_TRUE(pattern_->isVisibleArea_);
    EXPECT_EQ(GetChildX(frameNode_, 1), 0.0f);

    controller_->ShowPrevious();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    for (int i = 0; i < 2; ++i) {
        EXPECT_EQ(
            GetChildFrameNode(frameNode_, i)->GetRenderContext()->GetTranslateXYProperty(), OffsetF(240.0f, 0.0f));
    }
    EXPECT_EQ(pattern_->currentIndex_, 1);

    TouchLocationInfo touch(0);
    pattern_->HandleTouchDown({ touch });
    FlushUITasks();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), -240.0f);
    EXPECT_EQ(GetChildX(frameNode_, 1), 240.0f);

    // stop animation with partly refresh
    layoutProperty_->UpdateUserDefinedIdealSize(CalcSize(CalcLength(400.0f), CalcLength(SWIPER_HEIGHT)));
    layoutProperty_->UpdateLoop(false);
    layoutProperty_->UpdateIndex(1);
    frameNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    frameNode_->MarkModifyDone();
    FlushUITasks();
    EXPECT_EQ(GetChildX(frameNode_, 1), 0);
    EXPECT_EQ(pattern_->currentIndex_, 1);
    pattern_->HandleTouchUp();

    // check ShowPrevious function
    controller_->ShowPrevious();
    EXPECT_TRUE(pattern_->propertyAnimationIsRunning_);
    MockAnimationManager::GetInstance().Tick();
    MockAnimationManager::GetInstance().Tick();
    EXPECT_FALSE(pattern_->propertyAnimationIsRunning_);
    EXPECT_EQ(GetChildX(frameNode_, 0), 0.0f);
    EXPECT_EQ(pattern_->currentIndex_, 0);
}

/**
 * @tc.name: StopAnimate001
 * @tc.desc: Test change index with animate, and force stop when animate running
 * @tc.desc: Would change index decided by currentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, StopAnimate001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    model.SetDisplayCount(2);
    model.SetSwipeByGroup(true);
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. ShowNext and force stop animate when currentOffset not more than half of swiper width
     * @tc.expected: The currentIndex would not change
     */
    MockAnimationManager::GetInstance().SetTicks(3);
    controller_->ShowNext();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    TouchLocationInfo touch(0);
    pattern_->HandleTouchDown({ touch });
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step2. ShowNext and force stop animate when currentOffset more than half of swiper width
     * @tc.expected: The currentIndex would change
     */
    controller_->ShowNext();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_TRUE(CurrentIndex(2));

    /**
     * @tc.steps: step3. ShowPrevious and force stop animate when currentOffset not more than half of swiper width
     * @tc.expected: The currentIndex would not change
     */
    controller_->ShowPrevious();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_TRUE(CurrentIndex(2));

    /**
     * @tc.steps: step4. ShowPrevious and force stop animate when currentOffset more than half of swiper width
     * @tc.expected: The currentIndex would change
     */
    controller_->ShowPrevious();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: StopAnimate002
 * @tc.desc: Test change index with animate, and force stop when animate running
 * @tc.desc: Would change index decided by currentOffset
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, StopAnimate002, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();

    /**
     * @tc.steps: step1. ShowNext and force stop animate when currentOffset not more than half of swiper width
     * @tc.expected: The currentIndex would not change
     */
    MockAnimationManager::GetInstance().SetTicks(3);
    controller_->ShowNext();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    TouchLocationInfo touch(0);
    pattern_->HandleTouchDown({ touch });
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);

    /**
     * @tc.steps: step2. ShowNext and force stop animate when currentOffset more than half of swiper width
     * @tc.expected: The currentIndex would change
     */
    controller_->ShowNext();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step3. ShowPrevious and force stop animate when currentOffset not more than half of swiper width
     * @tc.expected: The currentIndex would not change
     */
    controller_->ShowPrevious();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_TRUE(CurrentIndex(1));

    /**
     * @tc.steps: step4. ShowPrevious and force stop animate when currentOffset more than half of swiper width
     * @tc.expected: The currentIndex would change
     */
    controller_->ShowPrevious();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    MockAnimationManager::GetInstance().Tick();
    FlushUITasks();
    pattern_->HandleTouchDown({ touch });
    EXPECT_EQ(pattern_->GetCurrentShownIndex(), 0);
}

/**
 * @tc.name: NeedFastAnimation001
 * @tc.desc: Test NeedFastAnimation
 * @tc.desc: Test NeedFastAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, NeedFastAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);

    EXPECT_FALSE(pattern_->NeedFastAnimation());

    pattern_->SetJumpAnimationMode(TabAnimateMode::CONTENT_FIRST);
    EXPECT_FALSE(pattern_->NeedFastAnimation());

    pattern_->SetJumpAnimationMode(TabAnimateMode::ACTION_FIRST);
    EXPECT_FALSE(pattern_->NeedFastAnimation());

    pattern_->SetJumpAnimationMode(TabAnimateMode::NO_ANIMATION);
    EXPECT_FALSE(pattern_->NeedFastAnimation());

    pattern_->SetJumpAnimationMode(TabAnimateMode::CONTENT_FIRST_WITH_JUMP);
    EXPECT_TRUE(pattern_->NeedFastAnimation());

    pattern_->SetJumpAnimationMode(TabAnimateMode::ACTION_FIRST_WITH_JUMP);
    EXPECT_TRUE(pattern_->NeedFastAnimation());
}

/**
 * @tc.name: FastAnimation001
 * @tc.desc: Test FastAnimation
 * @tc.desc: Test FastAnimation
 * @tc.type: FUNC
 */
HWTEST_F(SwiperAnimationTestNg, FastAnimation001, TestSize.Level1)
{
    SwiperModelNG model = CreateSwiper();
    CreateSwiperItems();
    CreateSwiperDone();
    ASSERT_NE(pattern_, nullptr);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    pattern_->currentIndex_ = 0;
    pattern_->FastAnimation(pattern_->currentIndex_);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    pattern_->currentIndex_ = 0;
    pattern_->FastAnimation(SWIPE_ONE);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    pattern_->currentIndex_ = 0;
    pattern_->FastAnimation(SWIPE_THREE);
    EXPECT_EQ(pattern_->currentIndex_, 0);

    pattern_->currentIndex_ = 0;
    pattern_->FastAnimation(SWIPE_FOUR);
    EXPECT_EQ(pattern_->currentIndex_, SWIPE_ONE);

    pattern_->currentIndex_ = SWIPE_FOUR;
    pattern_->FastAnimation(-SWIPE_THREE);
    EXPECT_EQ(pattern_->currentIndex_, SWIPE_ONE);

    pattern_->currentIndex_ = SWIPE_FOUR;
    pattern_->FastAnimation(-SWIPE_FOUR);
    EXPECT_EQ(pattern_->currentIndex_, SWIPE_ONE);
}
} // namespace OHOS::Ace::NG
