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

#include "scroll_test_ng.h"

namespace OHOS::Ace::NG {
namespace {} // namespace

class ScrolleEffectTestNg : public ScrollTestNg {
public:
};

/**
 * @tc.name: SpringEffect001
 * @tc.desc: Test SpringEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, SpringEffect001, TestSize.Level1)
{
    auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    springEffect->ProcessScrollOver(0.0);

    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    springEffect = AceType::DynamicCast<ScrollSpringEffect>(pattern_->GetScrollEdgeEffect());
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    springEffect->SetScrollable(scrollable);
    springEffect->ProcessScrollOver(0.0);

    scrollable->MarkAvailable(false);
    springEffect->ProcessScrollOver(0.0);

    pattern_->SetDirection(FlexDirection::ROW_REVERSE);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    springEffect->ProcessScrollOver(0.0);
}

/**
 * @tc.name: SpringEffect002
 * @tc.desc: Test SpringEffect
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, SpringEffect002, TestSize.Level1)
{
    auto springEffect = AceType::MakeRefPtr<ScrollSpringEffect>();
    springEffect->ProcessSpringUpdate();

    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    springEffect = AceType::DynamicCast<ScrollSpringEffect>(pattern_->GetScrollEdgeEffect());
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    springEffect->SetScrollable(scrollable);
    springEffect->ProcessSpringUpdate();

    scrollable->MarkAvailable(false);
    springEffect->ProcessSpringUpdate();

    pattern_->SetDirection(FlexDirection::ROW_REVERSE);
    pattern_->SetEdgeEffect(EdgeEffect::SPRING);
    springEffect->ProcessSpringUpdate();
    EXPECT_TRUE(springEffect->scrollable_->isSpringAnimationStop_);
}

/**
 * @tc.name: ScrollFadeEffect001
 * @tc.desc: Test the correlation function in ScrollFadeEffect under different conditions.
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, ScrollFadeEffect001, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollEdgeEffect->SetScrollable(scrollable);

    /**
     * @tc.steps: step1. call InitialEdgeEffect()
     */
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    /**
     * @tc.steps: step2. call HandleOverScroll(), overScroll is 0
     * @tc.expected: do nothing
     */
    const SizeF viewPort(SCROLL_WIDTH, SCROLL_HEIGHT);
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 0.f, viewPort);

    /**
     * @tc.steps: step3. call HandleOverScroll()
     */
    scrollFadeEffect->fadeController_ = nullptr;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, -1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);
    ASSERT_NE(scrollFadeEffect->fadeController_, nullptr);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);

    scrollFadeEffect->scrollable_->currentVelocity_ = 0.0;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, 1.f, viewPort);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::RIGHT);

    /**
     * @tc.steps: step4. scrollable_ is null, call HandleOverScroll()
     */
    scrollFadeEffect->scrollable_ = nullptr;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.f, viewPort);

    /**
     * @tc.steps: step5. Call CalculateOverScroll()
     */
    // minExtent:  0
    // maxExtent: ITEM_HEIGHT * 2
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_HEIGHT, true), 0.0));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_HEIGHT * 2, true), 0.0));

    UpdateCurrentOffset(-ITEM_HEIGHT);
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_HEIGHT, true), 0.0));

    pattern_->currentOffset_ = ITEM_HEIGHT;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT, true), -ITEM_HEIGHT));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), -ITEM_HEIGHT));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_HEIGHT * 2, true), 0.0));

    pattern_->currentOffset_ = -ITEM_HEIGHT;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT * 2, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(0.0, true), 0.0));
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(-ITEM_HEIGHT, true), 0.0));

    // over scroll
    pattern_->currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT * 2, true), ITEM_HEIGHT));

    // crash the bottom
    pattern_->currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT, true), ITEM_HEIGHT));
    pattern_->currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT, false), 0.0));
    pattern_->currentOffset_ = -ITEM_HEIGHT * 3;
    EXPECT_TRUE(NearEqual(scrollFadeEffect->CalculateOverScroll(ITEM_HEIGHT * 3, false), 0.0));
}

/**
 * @tc.name: ScrollFadeEffect002
 * @tc.desc: Test
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, ScrollFadeEffect002, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollFadeEffect->InitialEdgeEffect();

    Testing::MockCanvas rsCanvas;
    EXPECT_CALL(rsCanvas, Restore()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Save()).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Translate(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Scale(_, _)).Times(AtLeast(1));
    EXPECT_CALL(rsCanvas, Rotate(_)).Times(AtLeast(1));
    OffsetF offset = OffsetF(0, 0);
    scrollFadeEffect->fadePainter_->SetOpacity(0);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::UP;
    scrollFadeEffect->Paint(rsCanvas, SizeF(1, 1), offset);
    scrollFadeEffect->fadePainter_->SetOpacity(1);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::DOWN;
    scrollFadeEffect->Paint(rsCanvas, SizeF(0, 1), offset);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::LEFT;
    scrollFadeEffect->Paint(rsCanvas, SizeF(1, 0), offset);
    scrollFadeEffect->fadePainter_->direction_ = OverScrollDirection::RIGHT;
    scrollFadeEffect->Paint(rsCanvas, SizeF(0, 0), offset);
    SUCCEED();
}

/**
 * @tc.name: ScrollFadeEffect003
 * @tc.desc: Test SetPaintDirection in different situations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, ScrollFadeEffect003, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollEdgeEffect->SetScrollable(scrollable);

    /**
     * @tc.steps: step1. call InitialEdgeEffect()
     */
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    /**
     * @tc.steps: step2. overScroll is 0.001, call SetPaintDirection()
     */
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 0.001f, true);

    /**
     * @tc.steps: step3. call SetPaintDirection() and axis is vertical.
     */
    scrollFadeEffect->fadeController_ = nullptr;
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, -1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, 1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);

    /**
     * @tc.steps: step4. call SetPaintDirection() and axis is horizontal.
     */
    scrollFadeEffect->scrollable_->currentVelocity_ = 0.0;
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);

    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::RIGHT);
}

/**
 * @tc.name: ScrollFadeEffect004
 * @tc.desc: Test SetPaintDirection in different situations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, ScrollFadeEffect004, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollEdgeEffect->SetScrollable(scrollable);

    /**
     * @tc.steps: step1. call InitialEdgeEffect()
     */
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    /**
     * @tc.steps: step2. call SetPaintDirection() and axis is vertical.
     */
    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, 1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::DOWN);

    scrollFadeEffect->SetPaintDirection(Axis::VERTICAL, -1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);

    /**
     * @tc.steps: step3. call SetPaintDirection() and axis is horizontal.
     */
    scrollFadeEffect->scrollable_->currentVelocity_ = 1000.0;
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, 1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::RIGHT);

    scrollFadeEffect->scrollable_->currentVelocity_ = 0.0;
    scrollFadeEffect->SetPaintDirection(Axis::HORIZONTAL, -1.f, true);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);
}

/**
 * @tc.name: ScrollFadeEffect005
 * @tc.desc: Test HandleOverScroll in different situations.
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, ScrollFadeEffect005, TestSize.Level1)
{
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    RefPtr<ScrollEdgeEffect> scrollEdgeEffect = pattern_->GetScrollEdgeEffect();
    auto scrollable = AceType::MakeRefPtr<Scrollable>();
    scrollEdgeEffect->SetScrollable(scrollable);

    /**
     * @tc.steps: step1. call InitialEdgeEffect()
     */
    auto scrollFadeEffect = AceType::DynamicCast<ScrollFadeEffect>(scrollEdgeEffect);
    scrollEdgeEffect->InitialEdgeEffect();
    EXPECT_EQ(scrollFadeEffect->fadeColor_, Color::GRAY);
    scrollFadeEffect->fadeController_->DecelerateListener(1.0);

    /**
     * @tc.steps: step2. call HandleOverScroll(), axis is vertical and isScrollFromUpdate is false.
     * @tc.expected: do nothing
     */
    const SizeF viewPort(SCROLL_WIDTH, SCROLL_HEIGHT);
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, 0.f, viewPort);

    /**
     * @tc.steps: step3. call HandleOverScroll(), axis is vertical and isScrollFromUpdate is true.
     */
    scrollFadeEffect->fadeController_ = nullptr;
    scrollFadeEffect->HandleOverScroll(Axis::VERTICAL, -1.f, viewPort, true, false);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::UP);
    ASSERT_NE(scrollFadeEffect->fadeController_, nullptr);

    /**
     * @tc.steps: step4. call HandleOverScroll(), axis is horizontal and isScrollFromUpdate is true.
     */
    scrollFadeEffect->scrollable_->currentVelocity_ = 0.0;
    scrollFadeEffect->HandleOverScroll(Axis::HORIZONTAL, -1.f, viewPort, true, false);
    EXPECT_EQ(scrollFadeEffect->fadePainter_->direction_, OverScrollDirection::LEFT);
}

/**
 * @tc.name: FadeController001
 * @tc.desc: Test scroll_fade_controller
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, FadeController001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
    ASSERT_NE(fadeController, nullptr);
    double param1 = 10.f;
    double param2 = -10.0;
    auto callback = [&param1, &param2](double parameter1, double parameter2) {
        param1 = parameter1;
        param2 = parameter2;
    };
    fadeController->SetCallback(callback);

    /**
     * @tc.steps: step2. Verify the ProcessAbsorb function and callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(100.0);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.3);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0325);
    EXPECT_EQ(fadeController->state_, OverScrollState::ABSORB);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, 0.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);
    EXPECT_EQ(param1, fadeController->opacity_);
    EXPECT_EQ(param2, fadeController->scaleSize_);

    /**
     * @tc.steps: step2. When OverScrollState is ABSORB, call the callback function in fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->opacityCeil_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step3. When OverScrollState is RECEDE, call the ProcessRecede function and callback function in
     *                   fadeController.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    fadeController->ProcessRecede(1000);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);
    fadeController->ProcessRecede(1000);
    EXPECT_EQ(fadeController->pullDistance_, 0.0);

    /**
     * @tc.steps: step4. When OverScrollState is IDLE, call the ProcessPull function and callback function in
     *                   fadeController.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    EXPECT_EQ(fadeController->opacityFloor_, 0.3);
    EXPECT_EQ(fadeController->opacityCeil_, 0.0);
    EXPECT_EQ(fadeController->scaleSizeFloor_, 3.25);
    EXPECT_EQ(fadeController->scaleSizeCeil_, 0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step5. When OverScrollState is PULL, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    fadeController->ProcessAbsorb(-10.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, -29.7);
    EXPECT_EQ(fadeController->scaleSize_, -321.75);
    fadeController->controller_->NotifyStopListener();
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
    fadeController->ProcessAbsorb(100.0);
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(param1, 2940.3);
    EXPECT_EQ(param2, 31853.25);
}

/**
 * @tc.name: FadeController002
 * @tc.desc: Test scroll_fade_controller
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, FadeController002, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
    ASSERT_NE(fadeController, nullptr);
    double param1 = 10.f;
    double param2 = -10.0;
    auto callback = [&param1, &param2](double parameter1, double parameter2) {
        param1 = parameter1;
        param2 = parameter2;
    };
    fadeController->SetCallback(callback);

    /**
     * @tc.steps: step2. When OverScrollState is IDLE, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->state_ = OverScrollState::IDLE;
    fadeController->ProcessAbsorb(1.0);
    fadeController->decele_->NotifyListener(100.0);
    EXPECT_EQ(fadeController->opacity_, 0.3);
    EXPECT_EQ(fadeController->scaleSize_, 3.25);

    /**
     * @tc.steps: step3. When OverScrollState is PULL, call the ProcessPull function and callback function in
     *                   fadeController.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    fadeController->controller_->NotifyStopListener();
    fadeController->state_ = OverScrollState::PULL;
    fadeController->ProcessPull(1.0, 1.0, 1.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step4. When OverScrollState is PULL, call the ProcessRecede function and callback function in
     *                   fadeController.
     * @tc.expected: step4. Check whether relevant parameters are correct.
     */
    fadeController->controller_ = nullptr;
    fadeController->ProcessRecede(10);
    EXPECT_EQ(fadeController->state_, OverScrollState::RECEDE);

    /**
     * @tc.steps: step5. When OverScrollState is 0, call the Initialize function and callback function in
     *                   fadeController.
     * @tc.expected: step5. Check whether relevant parameters are correct.
     */
    int value = 4;
    OverScrollState data = static_cast<OverScrollState>(value);
    fadeController->state_ = data;
    fadeController->ProcessAbsorb(1.0);
}

/**
 * @tc.name: FadeController003
 * @tc.desc: Test scroll_fade_controller
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, FadeController003, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Create ScrollFadeController and set callback function.
     */
    auto fadeController = AceType::MakeRefPtr<ScrollFadeController>();
    ASSERT_NE(fadeController, nullptr);
    double param1 = 10.f;
    double param2 = -10.0;
    auto callback = [&param1, &param2](double parameter1, double parameter2) {
        param1 = parameter1;
        param2 = parameter2;
    };
    fadeController->SetCallback(callback);

    /**
     * @tc.steps: step2. When OverScrollState is PULL, call the ProcessAbsorb function and callback function in
     *                   fadeController.
     * @tc.expected: step2. Check whether relevant parameters are correct.
     */
    fadeController->controller_ = nullptr;
    fadeController->state_ = OverScrollState::PULL;
    fadeController->ProcessAbsorb(10);
    fadeController->ProcessRecede(10);
    EXPECT_EQ(fadeController->state_, OverScrollState::PULL);
    fadeController->ProcessPull(1.0, 0.0, 1.0);

    /**
     * @tc.steps: step3. When OverScrollState is IDLE, call the DecelerateListener function and callback function in
     *                   fadeController.
     * @tc.expected: step3. Check whether relevant parameters are correct.
     */
    fadeController->state_ = OverScrollState::IDLE;
    fadeController->ProcessAbsorb(-10);
    fadeController->callback_ = nullptr;
    fadeController->DecelerateListener(0.0);
    EXPECT_EQ(fadeController->state_, OverScrollState::IDLE);
}

/**
 * @tc.name: EdgeEffectOption001
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, EdgeEffectOption001, TestSize.Level1)
{
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        CreateContent(VIEW_LINE_NUMBER);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_FALSE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption002
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, EdgeEffectOption002, TestSize.Level1)
{
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        CreateContent(VIEW_LINE_NUMBER);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption003
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, EdgeEffectOption003, TestSize.Level1)
{
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, false);
        // 20 is childNumber.
        CreateContent(20);
    });
    EXPECT_FALSE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: EdgeEffectOption004
 * @tc.desc: Test EdgeEffectOption
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, EdgeEffectOption004, TestSize.Level1)
{
    Create([](ScrollModelNG model) {
        model.SetEdgeEffect(EdgeEffect::SPRING, true);
        // 20 is childNumber.
        CreateContent(20);
    });
    EXPECT_TRUE(pattern_->GetAlwaysEnabled());
    EXPECT_TRUE(pattern_->GetScrollableEvent()->GetEnabled());
}

/**
 * @tc.name: AttrEdgeEffect001
 * @tc.desc: Test attribute about edgeEffect,
 * @tc.type: FUNC
 */
HWTEST_F(ScrolleEffectTestNg, AttrEdgeEffect001, TestSize.Level1)
{
    /**
     * @tc.steps: step1. Text default value: NONE
     */
    CreateWithContent();
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::NONE);

    /**
     * @tc.steps: step2. Text set value: SPRING
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::SPRING, true); });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::SPRING);

    /**
     * @tc.steps: step3. Text set width value: FADE
     */
    CreateWithContent([](ScrollModelNG model) { model.SetEdgeEffect(EdgeEffect::FADE, true); });
    EXPECT_EQ(pattern_->GetEdgeEffect(), EdgeEffect::FADE);
}
} // namespace OHOS::Ace::NG
